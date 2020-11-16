
import xml.etree.ElementTree
import re
from codegen_text import *

vendor_abbreviations = []

base_type_default_values = {
    'void*': 'nullptr',
    'char': '0',
    'uint8_t': '0',
    'uint16_t': '0',
    'uint32_t': '0',
    'uint64_t': '0',
    'int32_t': '0',
    'int64_t': '0',
    'int': '0',
    'float': '0.f',
    'double': '0.0',
    'size_t': '0'
}

base_type_implicit_conversions = {}

class ApiConstant:
    def __init__(self, node):
        self.name = node.get('name')
        self.value = node.get('value')
        self.alias = node.get('alias')

    def print_base(self, file):
        if self.alias is not None:
            file.write(f'constexpr auto {self.name[3:]} = {self.alias[3:]};\n')
        elif self.value is not None:
            file.write(f'constexpr auto {self.name[3:]} = {self.value};\n')

api_constants = {}

class BaseType:
    def __init__(self, node):
        self.name = node.find('name').text
        self.type = None
        if node.find('type') is not None:
            self.type = node.find('type').text
            self.default_value = base_type_default_values[self.type]

    def print_base(self, file):
        if self.type is not None:
            file.write(f'using {self.name[2:]} = {self.type};\n')
    def print_vk_base(self, file):
        if self.type is not None:
            file.write(f'using {self.name} = {self.type};\n')

class FuncPointer:
    def __init__(self, node):
        self.name = node.find('name').text
        self.text = ''
        for t in node.itertext():
            self.text += t

    def print_base(self, file):
        file.write(self.text + '\n')

class MacroDefine:
    def __init__(self, node):
        self.should_print = True
        self.name = node.find("name")
        self.text = ''
        for t in node.itertext():
            if t in ['VK_API_VERSION', 'VK_API_VERSION_1_0', 'VK_API_VERSION_1_1', \
                'VK_API_VERSION_1_2', 'VK_HEADER_VERSION', 'VK_HEADER_VERSION_COMPLETE']:
                self.should_print = False
            self.text += t
        self.text += '\n'

    def print_base(self, file):
        if self.should_print:
            file.write(self.text)

def MorphVkEnumName(name, enum_name_len):
    n_part = name.title().split('_')[enum_name_len:]
    if n_part[-1] == "Bit":
        n_part = n_part[:-1]
    if n_part[-1].upper() in vendor_abbreviations:
        n_part[-1] = n_part[-1].upper()
    return ''.join(n_part)

def PlatformGuardHeader(file, guard, should_print=True):
    if should_print and guard is not None:
        file.write(f'#if defined({guard})\n')

def PlatformGuardFooter(file, guard, should_print=True):
    if should_print and guard is not None:
        file.write(f'#endif // {guard}\n')

def PrintConsecutivePlatforms(file, in_list, function_name, cpp20mode = None):
    prev_platform = None
    for item in in_list:
        if getattr(item, 'platform', None) is not None:
            if prev_platform != item.platform:
                if prev_platform is not None:
                    file.write(f'#endif // defined({prev_platform})\n')
                if item.platform is not None:
                    file.write(f'#if defined({item.platform})\n')
            prev_platform = item.platform
        else:
            if prev_platform is not None:
                file.write(f'#endif // defined({prev_platform})\n')
            prev_platform = None
        if cpp20mode is not None:
            getattr(item, function_name)(file, cpp20mode)
        else:
            getattr(item, function_name)(file)
    if prev_platform is not None:
        file.write(f'#endif // defined({prev_platform})\n')

class Enum:
    def __init__(self, node):
        self.name = node.get('name')
        self.underlying_type = 'int32_t'  # for ABI
        self.values = {}
        self.platform = None
        self.alias = node.get('alias')
        if self.alias is not None:
            return
        
        self.enum_name_len = len(re.findall('[A-Z][^A-Z]+', self.name))
        if self.name == 'VkResult':
            self.enum_name_len = 1
            self.underlying_type = 'int32_t'

        for elem in node:
            if elem.get('name') is not None and elem.get('value') is not None:
                self.values[elem.get('name')] = elem.get('value')
                
    def fill_ext_enums(self, enum_ext_list):
        for ext_enum in enum_ext_list:
            self.values[ext_enum.name] = ext_enum.value
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform
    
    def print_c_decl(self, file):
        if self.alias is None:
            file.write(f'enum {self.name} : {self.underlying_type};\n')

    def print_to_c_enum(self, file):
        if self.alias is None and len(self.values) > 0:
            file.write(f'constexpr {self.name} c_enum({self.name[2:]} val) {{ return static_cast<{self.name}>(val);}}\n')
   
    def print_base(self, file):
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            file.write(f"enum class {self.name[2:]} : {self.underlying_type} {{\n")
            for name, value in self.values.items():
                out_name = MorphVkEnumName(name, self.enum_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                file.write(f'    {out_name} = {str(value)},\n')
            file.write('};\n')
            if self.name == "VkResult":
                file.write('inline ')
                self.print_string_defs(file)
                file.write('constexpr bool operator !(Result res) { return res != Result::Success; }\n')
        
    def print_string(self, file):
        if self.alias is not None:
            return
        file.write(f'const char * to_string({self.name[2:]} val);\n')

    def print_string_defs(self, file):
        if self.alias is not None:
            return
        file.write(f'const char * to_string({self.name[2:]} val) {{\n')
        file.write(f'    switch(val) {{\n')
        for name in self.values.keys():
            out_name = MorphVkEnumName(name, self.enum_name_len)
            if out_name[0].isnumeric():
                out_name = f'e{out_name}'
            file.write(f'        case({self.name[2:]}::{out_name}): return \"{out_name}\";\n')
        file.write('        default: return "UNKNOWN";\n    }\n}\n')

def RepresentsIntOrHex(s):
    try: 
        int(s)
        int(s, 16)
        return True
    except ValueError:
        return False

class Bitmask:
    def __init__(self, node):
        self.name = node.get('name')
        self.flags_name = self.name.replace('Bits', 's')
        self.underlying_type = 'int32_t'  # for ABI
        self.values = {}
        self.bitmask_name_len = len(re.findall('[A-Z]+[^A-Z]*', self.name)) - 2
        if self.name[-4:] != "Bits": #ie an extension bitmask
            self.bitmask_name_len = self.bitmask_name_len - 1

        self.alias = node.get('alias')
        self.platform = None

        for elem in node:
            value = elem.get('value')
            if elem.get('bitpos') is not None:
                value = str(1 << int(elem.get('bitpos')))
            elif elem.get('alias') is not None:
                if elem.get('name') == "VK_STENCIL_FRONT_AND_BACK":
                    continue #ugly special case
                out_name = MorphVkEnumName(elem.get("alias"), self.bitmask_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                value = out_name
            self.values[value] = elem.get('name')

    def fill_ext_bitmasks(self, bitmask_ext_dict):
        for ext_bit in bitmask_ext_dict:
            self.values[str(1 << ext_bit.bitpos)] = ext_bit.name

    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform

    def print_c_decl(self, file):
        if self.alias is None:
            file.write(f'enum {self.name} : {self.underlying_type};\n')

    def print_to_c_enum(self, file):
        if self.alias is None and len(self.values) > 0:
            file.write(f'constexpr {self.name} c_enum({self.name[2:]} val) {{ return static_cast<{self.name}>(val);}}\n')
            
    def print_base(self, file):
        if self.alias is not None:
            file.write(f'using {self.name} = {self.alias[2:]};\n')
        else:
            file.write(f'enum class {self.name[2:]}: {self.underlying_type} {{\n')
            for bitpos, name in self.values.items():
                out_name = MorphVkEnumName(name, self.bitmask_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                file.write(f"    {out_name} = {bitpos},\n")
            file.write('};\n')
      
    def print_string(self, file):
        if self.alias is None:
            file.write(f'const char * to_string({self.name[2:]} val);\n')
            file.write(f'std::string to_string({self.flags_name[2:]} flag);\n')
            
    def print_string_defs(self, file):
        if self.alias is None:
            file.write(f'const char * to_string({self.name[2:]} val) {{\n')
            file.write('    switch(val) {\n')
            for bitpos, name in self.values.items():
                if not RepresentsIntOrHex(bitpos):
                    continue
                out_name = MorphVkEnumName(name, self.bitmask_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                file.write(f'        case({self.name[2:]}::{out_name}): return \"{out_name}\";\n')

            file.write('        default: return "UNKNOWN";\n    }\n}\n')
            file.write(f'std::string to_string({self.flags_name[2:]} flag){{\n')
            file.write(f'    if (flag.flags == 0) return \"None\";\n')
            file.write(f'    std::string out;\n')
            for bitpos, name in self.values.items():
                if not RepresentsIntOrHex(bitpos):
                    continue
                out_name = MorphVkEnumName(name, self.bitmask_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                file.write(f'    if (flag & {self.name[2:]}::{out_name}) out += \"{out_name} | \";\n')
                
            file.write(f'    return out.substr(0, out.size() - 3);\n}}\n')
           

class EmptyBitmask:
    def __init__(self, name):
        self.name = name
        self.flags_name = self.name.replace('Bits', 's')
        self.underlying_type = 'int32_t'
        self.platform = None
    
    def fill_ext_bitmasks(self, bitmask_ext_dict):
        pass
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or self.flags_name in ext_types:
            self.platform = platform

    def print_c_decl(self, file):
        file.write(f'enum {self.name} : {self.underlying_type};\n')
    
    def print_to_c_enum(self, file):
        file.write(f'constexpr {self.name} c_enum({self.name[2:]} val) {{ return static_cast<{self.name}>(val);}}\n')
     
    def print_base(self, file):
        file.write(f'enum class {self.name[2:]}: {self.underlying_type} {{ }};\n')

    def print_string(self, file):
        file.write(f'const char * to_string({self.name[2:]} val);\n')

    def print_string_defs(self, file):
        file.write(f'const char * to_string({self.name[2:]} val) {{\n')
        file.write('    switch(val) {\n')
        file.write('        default: return "UNKNOWN";\n    }\n}\n')
        file.write(f'std::string to_string({self.flags_name[2:]} flag){{\n')
        file.write(f'    if (flag.flags == 0) return \"None\";\n')
        file.write(f'    return "Unknown";\n}}\n')

class Flags:
    def __init__(self, node):
        if node.find('name') is not None:
            self.name = node.find('name').text
            self.alias = None
        else:
            self.name = node.get('name')
            self.alias = node.get('alias')

        self.underlying_type = 'VkFlags'
        self.flags_name = self.name.replace('Flags', 'FlagBits')
        self.requires = node.get('requires')
        self.need_empty = False
        if self.alias is None and self.requires is None:
            self.need_empty = True
        self.platform = None

    def check_platform(self, platform, ext_types):
        if (self.alias is not None and self.alias in ext_types) or self.name in ext_types:
            self.platform = platform

    def print_c_decl(self, file):
        file.write(f'using {self.name} = {self.underlying_type};\n')
    
    def print_to_c_enum(self, file):
        if self.alias is None:
            file.write(f'constexpr {self.name} c_enum({self.name[2:]} val) {{ return static_cast<{self.name}>(val);}}\n')

    def print_base(self, file):
        if self.alias is None:
            file.write(f'DECLARE_ENUM_FLAG_OPERATORS({self.name[2:]}, {self.flags_name[2:]}, {self.underlying_type})\n')
        else:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')

class Handle:
    def __init__(self, node):
        self.name = None
        if node.find('name') is not None:
            self.name = node.find('name').text
            if node.find('type').text == 'VK_DEFINE_HANDLE':
                self.dispatchable = True
            elif node.find('type').text == 'VK_DEFINE_NON_DISPATCHABLE_HANDLE':
                self.dispatchable = False
            self.parent = node.get('parent')
        self.alias = node.get('alias')
        if self.alias is not None:
            self.name = node.get('name')
        self.platform = None
        
    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform

    def print_handle_define(self, file):
        if self.alias is None:
            if self.dispatchable:
                file.write(f'VK_DEFINE_HANDLE({self.name})\n')
            else:
                file.write(f'VK_DEFINE_NON_DISPATCHABLE_HANDLE({self.name})\n')
        else:
            file.write(f'using {self.name} = {self.alias};\n')

    def print_base(self, file):
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            file.write(f'class {self.name[2:]} {{\n')
            file.write(f'    {self.name} handle = 0;\n')
            file.write(f'    public:\n')
            file.write(f'    explicit {self.name[2:]}() = default;\n')
            file.write(f'    explicit {self.name[2:]}({self.name} handle):handle(handle){{}}\n')
            file.write(f'    {self.name[2:]}([[maybe_unused]] std::nullptr_t none){{}}\n')
            file.write(f'    {self.name} get() const {{ return handle; }}\n')
            file.write(f'    explicit operator bool() const {{return handle != 0;}};\n')
            file.write(f'    bool operator!() {{ return handle == 0; }}\n')
            file.write('};\n')
    
    def print_static_asserts(self, file):
        if self.alias is None:
            if self.dispatchable:
                file.write(f'static_assert( sizeof(vk::{self.name[2:]}) == sizeof({self.name}),')
                file.write(f'"Must maintain size between handles");\n')
            else:
                file.write(f'static_assert( sizeof(vk::{self.name[2:]}) == sizeof({self.name}),')
                file.write(f'"Must maintain size between handles");\n')


class Variable:
    def __init__(self, node, handles, default_values):
        self.name = node.find('name').text
        self.sType_values = node.get('values')

        # attributes
        self.optional = node.get('optional')
        self.len_attrib = node.get('len')

        # type characteristics
        self.is_const = False
        self.is_single_ptr = False
        self.is_double_ptr = False
        self.is_const_double_ptr = False
        self.array_lengths = []  # multi-dimensional
        self.default_value = None
        self.is_comparable = True
        self.bitfield = None
        self.is_ref_eligible = False

        self.base_type = node.find('type').text
        self.base_type_modified = self.base_type
        if self.base_type_modified[:2] == 'Vk':
            self.base_type_modified = self.base_type_modified[2:]
        # special case cause of bitfields
        if self.base_type_modified == 'GeometryInstanceFlagsKHR':
            self.base_type_modified = 'VkGeometryInstanceFlagsKHR'

        if node.find('comment') is not None:
            node.remove(node.find('comment'))

        self.raw_xml_text = ' '.join(node.itertext())
        type_list = self.raw_xml_text.split()

        # type parsing
        cur = 0
        if type_list[cur] == 'const':
            self.is_const = True
            cur += 1
        if type_list[cur] == 'struct':
            cur += 1
        if type_list[cur] == self.base_type:
            cur += 1
        if type_list[cur] == '*':
            self.is_single_ptr = True
            cur += 1
        if type_list[cur] == '**':
            self.is_double_ptr = True
            cur += 1
        if type_list[cur] == 'const*':
            self.is_const_double_ptr = True
            self.is_single_ptr = False
            cur += 1
        if type_list[cur] == self.name:
            cur += 1

        while len(type_list) > cur:
            if type_list[cur] == '[':
                cur += 1
                arr_len = type_list[cur]
                cur += 2
            elif len(type_list[cur]) > 0 and type_list[cur][0] == '[':
                next_bracket = 1
                for t in type_list[cur][1:]:
                    if t == ']':
                        break
                    next_bracket += 1
                arr_len = type_list[cur][1:next_bracket]
                type_list[cur] = type_list[cur][next_bracket + 1:]
            else:
                break
            if arr_len in api_constants:
                arr_len = arr_len[3:]
            self.array_lengths.append(arr_len)
        for t in type_list:
            if len(t) > 0 and t[0] == ':':
                self.bitfield = t[1:]
        if self.base_type in default_values:
            self.default_value = default_values[self.base_type]
        if self.name == 'sType' and self.sType_values is not None:
            out_name = MorphVkEnumName(self.sType_values, 3)
            if out_name[0].isnumeric():
                out_name = f'e{out_name}'
            self.default_value = f'StructureType::{out_name}'

        self.is_handle = self.base_type in handles

        if self.is_handle or self.is_ptr():
            self.is_comparable = False

        if (not self.optional or self.optional != 'true') and (self.len_attrib is None) \
            and ((self.is_single_ptr and self.base_type != "void") or (self.is_double_ptr)):
            self.is_ref_eligible = True

    def is_ptr(self):
        return self.is_single_ptr or self.is_double_ptr or self.is_const_double_ptr

    def get_base_type(self):
        if self.base_type == 'void' and self.is_ptr():
            return 'std::byte'
        return self.base_type_modified

    def get_type_decl(self, use_vk_type=True, use_references=False, downgrade_ptr_type=False):
        type_decl = ''
        type_decl += 'const ' if self.is_const else ''
        type_decl += self.base_type_modified if use_vk_type else self.base_type
        if downgrade_ptr_type:
            type_decl += '*' if self.is_double_ptr else ''
            type_decl += 'const*' if self.is_const_double_ptr else ''
        else:
            if use_references and self.is_ref_eligible:
                type_decl += '& '
            else:
                type_decl += '*' if self.is_single_ptr else ''
                type_decl += '**' if self.is_double_ptr else ''
                type_decl += '* const*' if self.is_const_double_ptr else ''
        return type_decl

    def get_type_decl_w_arr(self):
        type_decl = self.get_type_decl(use_vk_type=False)
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_parameter_decl(self, use_references = False):
        local_use_refs = use_references
        type_decl = f'{self.get_type_decl(use_references=local_use_refs)} '
        type_decl += self.name
        if self.bitfield is not None:
            type_decl += f':{self.bitfield}'
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_init(self):
        if self.is_ptr():
            return ' = nullptr'
        elif len(self.array_lengths) > 0:
            return ''
        elif self.default_value is not None:
            return f'{{{self.default_value}}}'
        else:
            return '{}'

    def get_struct_member_decl(self, default_init):
        type_decl = self.get_parameter_decl()
        if default_init and self.bitfield is None:
            type_decl += self.get_init()
        type_decl += ';'
        return type_decl

def print_custom_comparator(file, member_list, name):
    file.write(f'    constexpr bool operator==({name} const& value) const {{\n')
    file.write('        bool is_equal = true;\n')
    counter = 0
    for member in member_list:
        if len(member.array_lengths) == 1:
            if f'VK_{member.array_lengths[0]}' in api_constants:
                length = int(api_constants[f'VK_{member.array_lengths[0]}'].value)
            else:
                length = int(member.array_lengths[0])
            file.write(f'        for(size_t i = 0; i < {length}; i++)\n')
            file.write(f'            is_equal &= {member.name}[i] == value.{member.name}[i];\n')
        elif len(member.array_lengths) == 2:
            file.write(f'        for(size_t i = 0; i < {int(member.array_lengths[0])}; i++)\n')
            file.write(f'            for(size_t j = 0; j < {int(member.array_lengths[1])}; j++)\n')
            file.write(f'                is_equal &= {member.name}[i][j] == value.{member.name}[i][j];\n')
        else:
            counter = counter + 1
    file.write('        return is_equal')
    if counter > 0: #if there are non array members to compare
        file.write(' && ')
    is_first = True
    counter = 0
    for member in member_list:
        if len(member.array_lengths) > 0:
            continue
        if is_first:
            is_first = False
        else:
            file.write('&& ')
        file.write(f'{member.name} == value.{member.name} ')
        counter = counter + len(str(member.name))*2 + 10
        if counter > 120:
            file.write('\n        ') # break it up
            counter = 0
    file.write(';}\n')
    file.write(f'    constexpr bool operator!=({name} const& value) const {{return !(*this == value);}}\n')

# Contains both structs and unions
class Structure:
    def __init__(self, node, handles, default_values):
        self.name = node.get('name')
        self.alias = node.get('alias')
        self.category = node.get('category') # struct or union
        self.members = []
        self.platform = None
        self.returnedonly = node.get('returnedonly') is not None
        self.structextends = node.get('structextends')

        for member in node.findall('member'):
            self.members.append(Variable(member, handles, default_values))

        self.is_comparable = True
        for member in self.members:
            if not member.is_comparable:
                self.is_comparable = False
                break
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or (self.alias is not None and self.alias in ext_types):
            self.platform = platform
    
    def print_c_forward_decl(self, file):
        if self.alias is None:
            file.write(f'{self.category} {self.name};\n')
        else:
            file.write(f'using {self.name} = {self.alias};\n')

    def print_base(self, file, cpp20mode = True):
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            should_init = self.category == 'struct' #members should default_init in structs but not unions
            file.write(f'{self.category} {self.name[2:]} {{\n')
            for member in self.members:
                if self.name == 'VkDeviceCreateInfo' and member.name in ['ppEnabledLayerNames', 'enabledLayerCount']:
                    file.write('[[deprecated]]')
                file.write(f'    {member.get_struct_member_decl(default_init=should_init)}\n')
            if self.is_comparable:
                if self.category == 'union':
                    print_custom_comparator(file, self.members, self.name[2:])
                elif cpp20mode:
                    file.write(f'    constexpr bool operator==({self.name[2:]} const& other) const = default;\n')
                else:
                    print_custom_comparator(file, self.members, self.name[2:])
            file.write('};\n')

    def print_static_asserts(self, file):
        if self.category == 'struct':
            file.write(f'static_assert( sizeof(vk::{self.name[2:]}) == sizeof({self.name}), "Must maintain size between types" );\n')
            file.write(f'static_assert( std::is_standard_layout<vk::{self.name[2:]}>::value, "Must be a standard layout type" );\n')

class Function:
    def __init__(self, node, handles, dispatchable_handles, default_values):
        self.success_codes = []
        self.error_codes = []
        if node.get('successcodes') is not None:
            self.success_codes = node.get('successcodes').split(',')
        if node.get('errorcodes') is not None:
            self.error_codes = node.get('errorcodes').split(',')

        self.platform = None
        proto = node.find('proto')
        self.name = proto.find('name').text if proto is not None else node.get('name')
        self.alias = node.get('alias') if proto is None else None
        self.return_type = proto.find('type').text if proto is not None else None

        if self.name is not None:
            self.func_prototype = f'PFN_{self.name}'

        self.parameters = []
        for param in node.findall('param'):
            self.parameters.append( Variable(param, handles, default_values))
        self.dispatch_type = None
        if len(self.parameters) > 0:
            self.free_function = self.parameters[0].base_type not in dispatchable_handles
            
            if self.name == 'vkGetInstanceProcAddr' or self.free_function:
                self.dispatch_type = 'global'
            elif self.name == 'vkGetDeviceProcAddr' or self.parameters[0].base_type in ['VkInstance', 'VkPhysicalDevice']:
                self.dispatch_type = 'instance'
            else:
                self.dispatch_type = 'device'

        self.dispatch_handle = None
        if len(self.parameters) > 0 and self.parameters[0].base_type in dispatchable_handles:
            self.dispatch_handle = self.parameters[0].base_type
        
        self.span_params = set()
        for param in self.parameters:
            if param.len_attrib is not None and param.len_attrib != "null-terminated" and param.optional is None:
                len_attrib = param.len_attrib
                for inner_param in self.parameters:
                    if inner_param.name == len_attrib:
                        self.span_params.add(len_attrib)

        self.is_value_query = len(self.parameters) > 0 and self.parameters[-1].is_ptr() \
            and not self.parameters[-1].is_const and self.parameters[-1].len_attrib is None
        self.is_enumeration_function = len(self.parameters) > 1 and self.parameters[-1].is_ptr() and not self.parameters[-1].is_const\
            and self.parameters[-2].optional is not None and self.parameters[-2].optional == 'false,true'
        self.query_type = None
        self.query_name = None
        self.full_return_type = None
        self.modified_param_list = self.parameters
        if self.is_value_query:
            self.modified_param_list = self.parameters[:-1]
            self.query_type = self.parameters[-1].get_type_decl(downgrade_ptr_type=True)
            if self.query_type[:2] == 'vk':
                self.query_type = self.query_type[:2]
            self.query_name = self.parameters[-1].name
            if self.return_type == 'VkResult':
                self.full_return_type = f'expected<{self.query_type}>'
                self.return_statement = f'return expected<{self.query_type}>({self.query_name}, result);\n'
            else:
                self.full_return_type = f'{self.query_type}'
                self.return_statement = f'return {self.query_name};\n'
        if self.is_enumeration_function:
            self.modified_param_list = self.parameters[:-2]
            self.query_type = self.parameters[-1].get_type_decl(downgrade_ptr_type=self.parameters[-1].base_type != 'void')
            self.base_query_type =self.parameters[-1].get_type_decl(use_vk_type=False)
            self.query_name = self.parameters[-1].name
            self.count_type = self.parameters[-2].base_type
            self.count_name = self.parameters[-2].name
            if self.return_type == 'VkResult':
                self.full_return_type = f'expected<detail::fixed_vector<{self.query_type}>>'
            else: # void
                self.full_return_type = f'detail::fixed_vector<{self.query_type}>'
        
    def check_platform(self, platform, ext_functions):
        if self.name in ext_functions:
            self.platform = platform
    
    def print_pfn_variable_decl(self, file):
        file.write(f'    {self.func_prototype} pfn_{self.name[2:]} = nullptr;\n')

    def print_c_func_pointer(self, file):
        if self.alias is not None:
            file.write(f'using PFN_{self.name} = PFN_{self.alias};\n')
            return
        file.write(f'using PFN_{self.name} = {self.return_type} (*) (')
        for param in self.parameters:
            if param != self.parameters[0]:
                file.write(', ')
            file.write(param.raw_xml_text)
        file.write(");\n")

    def get_return_type(self, replace_list=None, full_return_type=None):
        print_function_name = self.name[2:]
        if replace_list is not None:
            for str_from in replace_list:
                if print_function_name.find(str_from) != -1:
                    print_function_name = print_function_name.replace(str_from, '')
        return_type = ''
        if self.return_type != 'void' or self.full_return_type != None: 
            return_type += '[[nodiscard]] '

        if full_return_type is not None:
            return_type += f'{full_return_type} '
        elif self.return_type == 'VkResult':
            return_type += f'Result '
        else:
            return_type += f'{self.return_type} '
        return return_type

    def print_name(self, file, replace_list):
        print_function_name = self.name[2:]
        if replace_list is not None:
            for str_from in replace_list:
                if print_function_name.find(str_from) != -1:
                    print_function_name = print_function_name.replace(str_from, '')
        file.write(f'{print_function_name}')

    def print_parameters(self, file, parameter_list, break_between=True, condense_spans=False, print_defaults=False):
        should_print_comma = False #prevents printing of a comma before the first real parameter
        for param in parameter_list:
            if param != parameter_list[0]:
                if condense_spans == False or param.name not in self.span_params: 
                    if should_print_comma:
                        file.write(', ')
                        if break_between:
                            file.write(f'\n    ')
                
            if condense_spans and param.name in self.span_params: 
                continue            
            elif condense_spans and param.len_attrib is not None and param.len_attrib in self.span_params:
                file.write(f'std::span<{param.get_base_type()}> {param.name[1:]}')
            else:
                file.write(f'{param.get_parameter_decl(use_references=True)}')
            if print_defaults and param.name == 'pAllocator' and param == parameter_list[-1]:
                file.write(f' = nullptr')
            should_print_comma = True

    def print_c_api_call(self, file, dispatch_handle = None, dispatch_handle_name = None, pfn_source=None, last_arg=None, condense_spans=False):
        if self.return_type == 'VkResult':
            file.write('static_cast<Result>(')
        if pfn_source is not None:
            file.write(f'{pfn_source}->')
        file.write(f'pfn_{self.name[2:]}(')

        for param in self.parameters:
            if param == self.parameters[0]:
                if dispatch_handle is not None and f'{dispatch_handle}' == self.dispatch_handle:
                    file.write(f'{dispatch_handle_name}.get()')
                    continue
            else:
                file.write(f',\n        ')

            param_name = f'{param.name}'
            if condense_spans and param.len_attrib in self.span_params:
                param_name = f'{param_name[1:]}.data()' 
            # the last argument
            if last_arg is not None and param == self.parameters[-1]:
                file.write(last_arg)
            elif param.is_handle and not param.is_ptr():
                file.write(param.name + '.get()')
            elif param.base_type not in base_type_default_values.keys() and param.base_type not in base_type_implicit_conversions:
                if param.is_ptr():
                    file.write(f'reinterpret_cast<{param.get_type_decl_w_arr()}>(')
                    if param.is_ref_eligible:
                        file.write('&')
                    file.write(f'{param_name})')
                else:
                    file.write(f'static_cast<{param.get_type_decl_w_arr()}>({param_name})')
            else:
                if param.is_ref_eligible:
                    file.write('&')
                file.write(param_name)
        if self.return_type == 'VkResult':
            file.write(')')
        file.write(');\n')

    def inner_print_definition(self, file, dispatch_handle = None, replace_list=None, make_void_return_this=None, print_spans=False):
        parameter_list = self.modified_param_list
        if dispatch_handle is not None and f'{dispatch_handle}' == self.dispatch_handle:
            parameter_list = parameter_list[1:]
        if make_void_return_this is not None and self.return_type == 'void':
            file.write(f'    {self.get_return_type(replace_list, make_void_return_this)}')
        else:
            file.write(f'    {self.get_return_type(replace_list, self.full_return_type)}')
        self.print_name(file, replace_list)
        file.write('(')
        self.print_parameters(file, parameter_list, break_between=False, condense_spans=print_spans, print_defaults=True)
        file.write(') const;\n')

    def print_definition(self, file, dispatch_handle = None, replace_list=None, make_void_return_this=None, cpp20mode=False):
        if self.alias is not None:
            return
        self.inner_print_definition(file, dispatch_handle, replace_list, make_void_return_this, print_spans=False)
        if cpp20mode and len(self.span_params) > 0:
            self.inner_print_definition(file, dispatch_handle, replace_list, make_void_return_this, print_spans=True)
 
    def inner_print_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=None, \
            struct_source='', pfn_source=None, make_void_return_this=None, print_spans=False):
        file.write(f'{self.get_return_type(replace_list, self.full_return_type)}')
        file.write(f'{struct_source}::')
        self.print_name(file, replace_list)
        parameter_list = self.modified_param_list
        if dispatch_handle is not None and f'{dispatch_handle}' == self.dispatch_handle:
            parameter_list = parameter_list[1:]
        file.write('(')
        self.print_parameters(file, parameter_list, condense_spans=print_spans)
        file.write(') const {\n')
        if self.name == 'vkEnumerateInstanceVersion':
            #early return because 1.0 doesn't support the function, will be null and shouldn't cause a crash
            file.write(f'    if (pfn_EnumerateInstanceVersion == 0) return expected<uint32_t>(VK_MAKE_VERSION(1,0,0), Result::Success);\n')
        if print_spans:
            for param in self.parameters:
                if param.name in self.span_params:
                    file.write(f'    {param.get_base_type()} {param.name} = ')
                    for inner_param in self.parameters:
                        if inner_param.len_attrib is not None and inner_param.len_attrib == param.name:
                            if f'{param.get_base_type()}' in ['uint32_t', 'int32_t']:
                                file.write(f'static_cast<{param.get_base_type()}>({inner_param.name[1:]}.size());\n')
                            else:
                                file.write(f'{inner_param.name[1:]}.size();\n')
                            break
        
        if self.is_value_query:
            file.write(f'    {self.query_type} {self.query_name};\n    ')
            if self.return_type != 'void':
                file.write(f'vk::Result result = ')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, condense_spans=print_spans)
            file.write(f'    {self.return_statement}')
        elif self.is_enumeration_function:
            if self.return_type == 'void':
                file.write(f'    {self.count_type} {self.count_name} = 0;\n    ')
                self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, 'nullptr')
                file.write(f'    detail::fixed_vector<{self.query_type}> {self.query_name}{{{self.count_name}}};\n    ')
                self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, f'reinterpret_cast<{self.base_query_type}>({self.query_name}.data())', condense_spans=print_spans)
                file.write(f'    if ({self.count_name} < {self.query_name}.size()) {self.query_name}.shrink({self.count_name});\n')
                file.write(f'    return {self.query_name};\n')
            else:
                file.write(f'    {self.count_type} {self.count_name} = 0;\n')
                file.write(f'    vk::Result result = ')
                self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, 'nullptr')
                file.write(f'    if (result < Result::Success) return expected(detail::fixed_vector<{self.query_type}>{{}}, result);\n')
                file.write(f'    detail::fixed_vector<{self.query_type}> {self.query_name}{{{self.count_name}}};\n')
                file.write(f'    result = ')
                self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, f'reinterpret_cast<{self.base_query_type}>({self.query_name}.data())', condense_spans=print_spans)
                file.write(f'    if ({self.count_name} < {self.query_name}.size()) {self.query_name}.shrink({self.count_name});\n')
                file.write(f'    return expected(std::move({self.query_name}), result);\n')
        else:
            file.write(f'    ')
            if self.return_type != 'void':
                file.write(f'return ')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, condense_spans=print_spans)

        file.write(f'}}\n')

    def print_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=None, \
            struct_source='', pfn_source=None, make_void_return_this=None, cpp20mode=False):
        if self.alias is not None:
            file.write(f'const auto {self.name[2:]} = {self.alias[2:]};\n')
            return
        self.inner_print_function(file, dispatch_handle, dispatch_handle_name, replace_list, struct_source, pfn_source, make_void_return_this, print_spans=False)
        if cpp20mode and len(self.span_params) > 0:
            self.inner_print_function(file, dispatch_handle, dispatch_handle_name, replace_list, struct_source, pfn_source, make_void_return_this, print_spans=True)

    def print_forwarding_function_call(self, file, parameter_list, dispatch_handle_name, print_spans):
        for param in parameter_list:
            if param == parameter_list[0]:
                file.write(f'{dispatch_handle_name}')
            else:
                if print_spans:
                    if param.name in self.span_params:
                        continue
                    elif param.len_attrib is not None and param.len_attrib in self.span_params:
                        file.write(f', {param.name[1:]}')
                        continue
                file.write(f', {param.name}')

    def inner_print_forwarding_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=None, \
            struct_source='', pfn_source=None, make_void_return_this=None, print_spans=False):
        if make_void_return_this is not None and self.return_type == 'void':
            file.write(f'{self.get_return_type(replace_list, make_void_return_this)}')
        else:
            file.write(f'{self.get_return_type(replace_list,  self.full_return_type)}')

        file.write(f'{struct_source}::')
        self.print_name(file, replace_list)
        file.write('(')
       
        self.print_parameters(file, self.modified_param_list[1:], break_between=False, condense_spans=print_spans)
        file.write(') const {\n')
        file.write(f'    ')
        if self.return_type != 'void' or self.full_return_type != None:
            file.write(f'return ')
        file.write(f'{pfn_source}->{self.name[2:]}(')
        self.print_forwarding_function_call(file, self.modified_param_list, dispatch_handle_name, print_spans)
        file.write(f');')
        if self.return_type == 'void' and make_void_return_this is not None:
            file.write(f'\n    return *this;')
        file.write(f' }}\n')

    def print_forwarding_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=None, \
            struct_source='', pfn_source=None, make_void_return_this=None, cpp20mode=False):
        if self.alias is not None:
            file.write(f'const auto {self.name[2:]} = {self.alias[2:]};\n')
            return
        self.inner_print_forwarding_function(file, dispatch_handle, dispatch_handle_name, replace_list, struct_source, pfn_source, make_void_return_this, print_spans=False)
        if cpp20mode and len(self.span_params) > 0:
            self.inner_print_forwarding_function(file, dispatch_handle, dispatch_handle_name, replace_list, struct_source, pfn_source, make_void_return_this, print_spans=True)

class ExtEnum:
    def __init__(self, name, value):
        self.name = name
        self.value = value

class ExtBitmask:
    def __init__(self, name, bitpos):
        self.name = name
        self.bitpos = bitpos

def EnumExtValue(ext_num, offset, direction):
    enum_value = 1000000000 + 1000 * (ext_num - 1) + offset
    if direction == '-':
        enum_value = -enum_value
    return enum_value

def AppendToDictOfLists(dict, key, val):
    if key not in dict:
        dict[key] = [] 
    dict[key].append(val)

class Requires:
    def __init__(self, node, ext_num = None):
        self.feature = node.get('feature')
        self.extension = node.get('extension')
        self.enum_dict = {}
        self.bitmask_dict = {}
        self.types = set()
        self.commands = set()
        self.functions = []
       
        for e_type in node.findall('type'):
            self.types.add(e_type.get('name'))
        for command in node.findall('command'):
            self.commands.add(command.get('name'))

        for enum in node.findall('enum'):
            extends = enum.get('extends')
            if extends is None:
                continue
            name = enum.get('name')
            value = enum.get('value')
            bitpos = enum.get('bitpos')
            offset = enum.get('offset')
            extnumber = enum.get('extnumber')

            if offset is not None:
                offset = int(offset)

            if value is not None:  # core enums
                AppendToDictOfLists(self.enum_dict, extends, ExtEnum(name, value))
            elif offset is not None:
                if extnumber is None and ext_num is not None:
                    extnumber = ext_num
                enum_value = EnumExtValue(int(extnumber), offset, enum.get('dir'))
                AppendToDictOfLists(self.enum_dict, extends, ExtEnum(name, enum_value))
            elif bitpos is not None:
                AppendToDictOfLists(self.bitmask_dict, extends, ExtBitmask(name, int(bitpos)))

    def fill_functions(self, functions):
        self.functions.extend([function for function in functions if function.name in self.commands])

    def fill_enums(self, enum_dict):
        for key in self.enum_dict.keys():
            enum_dict[key].fill_ext_enums(self.enum_dict[key])

    def fill_bitmasks(self, bitmask_dict):
        for key in self.bitmask_dict.keys():
            bitmask_dict[key].fill_ext_bitmasks(self.bitmask_dict[key])
    
    def check_platform(self, platform, enum_dict, flags_dict, bitmask_dict, structures, functions):
        [enum.check_platform(platform, self.types) for enum in enum_dict.values()]
        [flag.check_platform(platform, self.types) for flag in flags_dict.values()]
        [bitmask.check_platform(platform, self.types) for bitmask in bitmask_dict.values()]
        [struct.check_platform(platform, self.types) for struct in structures]
        [function.check_platform(platform, self.commands) for function in functions]

class Extension:
    def __init__(self, node, platforms):
        self.name = node.get('name')
        self.ext_num = int(node.get('number'))
        self.ext_type = node.get('type')
        self.supported = node.get('supported')
        self.platform = None
        if node.get('platform') is not None:
            self.platform = platforms[node.get('platform')]
        self.requires = []
        for requires in node.findall('require'):
            self.requires.append(Requires(requires, self.ext_num))

class VulkanFeatureLevel:
    def __init__(self,node):
        self.api = node.get('api')
        self.name = node.get('name')
        self.number = node.get('number')
        self.requires = []
        for require in node.findall('require'):
            self.requires.append(Requires(require))

class DispatchTable:   
    def __init__(self, name, dispatch_type, ext_or_feature_list):
        self.name = name
        self.dispatch_type = dispatch_type
        self.functions = {}
        for ext_or_feature in ext_or_feature_list:
            for require in ext_or_feature.requires: 
                for function in require.functions:
                    if function.dispatch_type == dispatch_type or dispatch_type == 'instance' and function.name == 'vkGetInstanceProcAddr':
                        self.functions[function.name] = function

        self.gpa_type = 'PFN_vkGetDeviceProcAddr' if self.dispatch_type  == 'device' else 'PFN_vkGetInstanceProcAddr'
        self.gpa_name = 'get_device_proc_addr'  if self.dispatch_type == 'device' else 'get_instance_proc_addr'
        self.dispatch_handle = f'Vk{self.dispatch_type.title()}' if self.dispatch_type != 'global' else None
        self.gpa_val = f'{self.dispatch_type}.get()' if self.dispatch_type != 'global' else 'nullptr'

    def print_definition(self, file, cpp20mode):
        if len(self.functions) == 0:
            return
                
        file.write(f'struct {self.name}Functions {{\n')
        #function pointers
        if self.dispatch_type != 'global':
            file.write(f'    {self.dispatch_type.title()} {self.dispatch_type};\n')
        PrintConsecutivePlatforms(file, self.functions.values(), 'print_pfn_variable_decl')

        #functions
        for function in self.functions.values():
            PlatformGuardHeader(file, function.platform)
            function.print_definition(file, dispatch_handle=self.dispatch_handle, cpp20mode=cpp20mode)
            PlatformGuardFooter(file, function.platform)
             
        #constructor
        file.write(f'    explicit {self.name}Functions() noexcept;\n')   
        if self.dispatch_type == 'global':
            file.write(f'    explicit {self.name}Functions(DynamicLibrary const& library) noexcept;\n')
        elif self.dispatch_type == 'instance':
            file.write(f'    explicit {self.name}Functions(GlobalFunctions const& global_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept;\n')
        elif self.dispatch_type == 'device':
            file.write(f'    explicit {self.name}Functions(InstanceFunctions const& instance_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept;\n')
        file.write('};\n')

    def print_base(self, file, cpp20mode):
        if len(self.functions) == 0:
            return
                
        #functions
        for function in self.functions.values():
            PlatformGuardHeader(file, function.platform)
            function.print_function(file, dispatch_handle=self.dispatch_handle, dispatch_handle_name=self.dispatch_type, struct_source=f'{self.name}Functions', cpp20mode=cpp20mode)
            PlatformGuardFooter(file, function.platform)

        #constructor
        file.write(f'{self.name}Functions::{self.name}Functions() noexcept {{}}\n')   
        if self.dispatch_type == 'global':
            file.write(f'{self.name}Functions::{self.name}Functions(DynamicLibrary const& library) noexcept {{\n')
            file.write(f'    {self.gpa_type} {self.gpa_name} = library.get();\n')
        elif self.dispatch_type == 'instance':
            file.write(f'{self.name}Functions::{self.name}Functions(GlobalFunctions const& global_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept \n')
            file.write(f'    :{self.dispatch_type}({self.dispatch_type}) {{ \n')
            file.write(f'    {self.gpa_type} {self.gpa_name} = global_functions.pfn_GetInstanceProcAddr;\n')
        elif self.dispatch_type == 'device':
            file.write(f'{self.name}Functions::{self.name}Functions(InstanceFunctions const& instance_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept ')
            if self.name == 'Device':
                file.write(f'\n    :{self.dispatch_type}({self.dispatch_type}) {{\n')
            else:
                file.write('{\n')
            file.write(f'    {self.gpa_type} {self.gpa_name} = instance_functions.pfn_GetDeviceProcAddr;\n')
        for function in self.functions.values():
            PlatformGuardHeader(file, function.platform) 
            file.write(f'    pfn_{function.name[2:]} = ')
            if function.name == 'vkGetInstanceProcAddr': 
                file.write(f'{self.gpa_name};\n') #had a crash here once, may not be needed.
            else:
                file.write(f'reinterpret_cast<{function.func_prototype}>({self.gpa_name}({self.gpa_val},\"{function.name}\"));\n')
            PlatformGuardFooter(file, function.platform)
        file.write('}\n')

class DispatchableHandleDispatchTable:
    def __init__(self, name, dispatch_type, replace_list, functions):
        self.name = name
        self.dispatch_type = dispatch_type
        self.replace_list = replace_list
        self.functions = []
    
        for function in functions:
            if function.dispatch_handle == name:
                self.functions.append(function)

        self.functions_type = f'{self.dispatch_type.title()}Functions'
        self.functions_name = f'{self.dispatch_type}_functions'
        self.type_name = self.name[2:]
        self.var_name = self.name[2:].lower()

    def print_definition(self, file, cpp20mode):
        command_buffer_return_type = f'{self.type_name}Functions const&' if self.type_name == 'CommandBuffer' else None
        file.write(f'struct {self.type_name}Functions {{\n')
        file.write(f'    {self.functions_type} const* {self.functions_name};\n')
        file.write(f'    {self.type_name} {self.var_name};\n')   
        file.write(f'    {self.type_name}Functions() noexcept;\n')
        file.write(f'    {self.type_name}Functions({self.functions_type} const& {self.functions_name}, {self.type_name} const {self.var_name}) noexcept;\n')
        prev_platform = None
        for function in self.functions:
            if prev_platform != function.platform:
                if prev_platform is not None:
                    file.write(f'#endif // defined({prev_platform})\n')
                if function.platform is not None:
                    file.write(f'#if defined({function.platform})\n')
            prev_platform = function.platform
            function.print_definition(file, dispatch_handle=self.name, replace_list=self.replace_list, \
                make_void_return_this=command_buffer_return_type, cpp20mode=cpp20mode)
        if prev_platform is not None:
            file.write(f'#endif // defined({prev_platform})\n')
        file.write('};\n')
    
    def print_base(self, file, cpp20mode):
        command_buffer_return_type = f'{self.type_name}Functions const&' if self.type_name == 'CommandBuffer' else None
        file.write(f'{self.type_name}Functions::{self.type_name}Functions() noexcept {{}}\n')
        file.write(f'{self.type_name}Functions::{self.type_name}Functions({self.functions_type} const& {self.functions_name}, {self.type_name} const {self.var_name}) noexcept\n')
        file.write(f'    :{self.functions_name}(&{self.functions_name}), {self.var_name}({self.var_name}){{}}\n')
        prev_platform = None
        for function in self.functions:
            if prev_platform != function.platform:
                if prev_platform is not None:
                    file.write(f'#endif // defined({prev_platform})\n')
                if function.platform is not None:
                    file.write(f'#if defined({function.platform})\n')
            prev_platform = function.platform
            function.print_forwarding_function(file, dispatch_handle=self.name, dispatch_handle_name=self.var_name, replace_list=self.replace_list, \
                struct_source=f'{self.type_name}Functions', pfn_source=self.functions_name, make_void_return_this=command_buffer_return_type, cpp20mode=cpp20mode)
        if prev_platform is not None:
            file.write(f'#endif // defined({prev_platform})\n')
        
class BindingGenerator:
    def __init__(self, root):

        self.platforms = {}
        self.default_values = {}
        self.macro_defines = []
        self.base_types = []
        self.func_pointers = []
        self.flags_dict = {}
        self.enum_dict = {}
        self.handles = {}
        self.dispatchable_handles = []
        self.structures = []
        self.bitmask_dict = {}
        self.functions = []
        self.vk_feature_levels = []
        self.ext_list = []
        self.dispatch_tables = []
        self.dispatchable_handle_tables = []
        
        for platform in root.find('platforms'):
            self.platforms[platform.get('name')] = platform.get('protect')

        for key, value in base_type_default_values.items():
            self.default_values[key] = value

        for enum in root.findall("enums"):
            if enum.attrib.get('name') == "API Constants":
                for constant in enum.iter():
                    api_constant = ApiConstant(constant)
                    if api_constant.name not in ['VK_TRUE', 'VK_FALSE']:
                        api_constants[api_constant.name] = api_constant
                break

        for xml_type in root.find('types'):
            category = xml_type.get('category')
            if category == 'define':
                self.macro_defines.append(MacroDefine(xml_type))
            elif category == 'basetype':
                base_type = BaseType(xml_type)
                self.base_types.append(base_type)
                if base_type.type is not None:
                    self.default_values[base_type.name] = base_type.default_value
                if base_type.name not in base_type_implicit_conversions:
                    base_type_implicit_conversions[base_type.name] = base_type.type
            elif category == 'funcpointer':
                self.func_pointers.append(FuncPointer(xml_type))
            elif category == 'bitmask':
                flag = Flags(xml_type)
                self.flags_dict[flag.name] = flag
            elif category == 'enum':
                enum = Enum(xml_type)
                if enum.name.find('Flag') == -1 or enum.name.find('FlagBits') == -1:
                    self.enum_dict[enum.name] = Enum(xml_type)
                self.default_values[enum.name] = f'static_cast<{enum.name[2:]}>(0)'
            elif category == 'handle':
                handle = Handle(xml_type)
                self.handles[handle.name] = handle
                if handle.alias is None and handle.dispatchable:
                    self.dispatchable_handles.append(handle.name)
            elif category == 'union' or category == 'struct':
                self.structures.append(Structure(xml_type, self.handles, self.default_values))

        #fixup the list so that members using a type appear after that type is defined
        outer_counter = 0
        inner_counter = 0
        while outer_counter < len(self.structures):
            moved = False
            for m in self.structures[outer_counter].members:
                inner_counter = outer_counter
                for t2 in self.structures[outer_counter:]:
                    if m.base_type == t2.name and inner_counter > outer_counter:
                        self.structures.insert(outer_counter, self.structures.pop(inner_counter))
                        moved = True
                    inner_counter = inner_counter + 1
            if not moved:
                outer_counter = outer_counter + 1

        # determine which structures are comparable
        for structure in self.structures:
            if not structure.is_comparable:
                continue
            comparable = True
            for member in structure.members:
                for sub_type in self.structures:
                    if member.base_type == sub_type.name:
                        if not sub_type.is_comparable:
                            comparable = False
                            break
            structure.is_comparable = comparable

        for enum in root.findall("enums"):
            if enum.get('type') == 'enum':
                self.enum_dict[enum.get('name')] = Enum(enum)
            elif enum.get('type') == 'bitmask':
                self.bitmask_dict[enum.get('name')] = Bitmask(enum)

        # add in flags which have no bitmask
        for f in self.flags_dict.values():
            if f.need_empty and f.flags_name not in self.bitmask_dict:
                self.bitmask_dict[f.flags_name] = EmptyBitmask(f.flags_name)

        for commands in root.findall('commands'):
            for command in commands.findall('command'):
                new_function = Function(command, self.handles, self.dispatchable_handles, self.default_values)
                if new_function.name not in ['vkEnumerateDeviceLayerProperties']:
                    self.functions.append(new_function)

        for ext in root.find('extensions'):
            if ext.tag == 'extension':
                new_ext = Extension(ext, self.platforms)
                if new_ext.supported == 'vulkan':
                    for require in new_ext.requires:
                        require.check_platform(new_ext.platform, self.enum_dict, self.flags_dict, self.bitmask_dict, 
                            self.structures, self.functions)
                        require.fill_enums(self.enum_dict)
                        require.fill_bitmasks(self.bitmask_dict)
                        require.fill_functions(self.functions)
                    self.ext_list.append(new_ext)
                elif new_ext.supported == 'disabled':
                    for require in new_ext.requires:
                        for req_type in require.types:
                            if req_type in self.enum_dict:
                                self.enum_dict.pop(req_type)
                            if req_type in self.bitmask_dict:
                                self.bitmask_dict.pop(req_type)
                            if req_type in self.flags_dict:
                                self.flags_dict.pop(req_type) 
                            for structure in self.structures:
                                if structure.name == req_type:
                                    self.structures.remove(structure)
                        for command in require.commands:
                            for function in self.functions:
                                if function.name == command:
                                    self.functions.remove(function)
        for feature in root.findall('feature'):
            feat_level = VulkanFeatureLevel(feature)
            for require in feat_level.requires:
                require.fill_enums(self.enum_dict)
                require.fill_bitmasks(self.bitmask_dict)
                require.fill_functions(self.functions)
            self.vk_feature_levels.append(feat_level)
        
        features_and_extensions = self.vk_feature_levels
        features_and_extensions.extend(self.ext_list)

        self.dispatch_tables.append(DispatchTable("Global", "global", features_and_extensions))
        self.dispatch_tables.append(DispatchTable("Instance", "instance", features_and_extensions))
        self.dispatch_tables.append(DispatchTable("Device", "device", features_and_extensions))

        # for ext in self.ext_list:
        #     self.dispatch_tables.append(DispatchTable(f'{ext.name}_dispatch_table', ext.ext_type, [ext]))

        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkPhysicalDevice', 'instance',['PhysicalDevice'], self.functions))
        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkQueue', 'device',['Queue'], self.functions))
        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkCommandBuffer', 'device',['Cmd', 'CommandBuffer'], self.functions))
  


def print_vkm_main(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vkm.h', 'w') as vkm:
        vkm.write('#pragma once\n')
        vkm.write('#include "vkm_core.h"\n')
        vkm.write('#include "vkm_function.h"\n')
        vkm.write('#include "vkm_string.h"\n')
   
def print_vkm_core(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vkm_core.h', 'w') as vkm_core:
        vkm_core.write('#pragma once\n// clang-format off\n')
        vkm_core.write('#include <stdint.h>\n')
        vkm_core.write('#include <cstddef>\n')
        vkm_core.write('#include "vkm_c_defs.h"\n')
        vkm_core.write('namespace vk {\n')
        PrintConsecutivePlatforms(vkm_core, api_constants.values(), 'print_base')
        PrintConsecutivePlatforms(vkm_core, bindings.base_types, 'print_base')
        PrintConsecutivePlatforms(vkm_core, bindings.enum_dict.values(), 'print_base')
        PrintConsecutivePlatforms(vkm_core, bindings.bitmask_dict.values(), 'print_base')
        vkm_core.write(bitmask_flags_macro + '\n')
        PrintConsecutivePlatforms(vkm_core, bindings.flags_dict.values(), 'print_base')
        PrintConsecutivePlatforms(vkm_core, bindings.handles.values(), 'print_base')
        PrintConsecutivePlatforms(vkm_core, bindings.structures, 'print_base', cpp20mode)
        vkm_core.write('} // namespace vk\n// clang-format on\n')

def print_vkm_function(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vkm_function.h', 'w') as vkm_function:
        vkm_function.write('#pragma once\n// clang-format off\n')
        if cpp20mode:
            vkm_function.write('#include <span>\n')
        vkm_function.write('#include "vkm_core.h"\n')
        vkm_function.write(vulkan_library_text + '\n')
        vkm_function.write(fixed_vector_text + '\n')
        vkm_function.write(vulkan_expected_type + '\n')
        [ dispatch_table.print_definition(vkm_function, cpp20mode) for dispatch_table in bindings.dispatch_tables ]
        [ table.print_definition(vkm_function, cpp20mode) for table in bindings.dispatchable_handle_tables ]
        vkm_function.write('} // namespace vk\n// clang-format on\n')
    
    with open(f'cpp{cpp20str}/vkm_function.cpp', 'w') as vkm_function:
        vkm_function.write('#include "vkm_function.h"\n')
        vkm_function.write('namespace vk {\n')
        [ dispatch_table.print_base(vkm_function, cpp20mode) for dispatch_table in bindings.dispatch_tables ]
        [ table.print_base(vkm_function, cpp20mode) for table in bindings.dispatchable_handle_tables ]
        vkm_function.write('} // namespace vk\n// clang-format on\n')

def print_vkm_string(bindings, cpp20mode, cpp20str):
    removed_result = bindings.enum_dict.copy()
    removed_result.pop('VkResult')
    with open(f'cpp{cpp20str}/vkm_string.h', 'w') as string_decl:
        string_decl.write('#pragma once\n// clang-format off\n')
        string_decl.write('#include "vkm_core.h"\n')
        string_decl.write('#include <string>\n')
        string_decl.write('namespace vk {\n')
        PrintConsecutivePlatforms(string_decl, removed_result.values(), 'print_string')
        PrintConsecutivePlatforms(string_decl, bindings.bitmask_dict.values(), 'print_string')
        string_decl.write('} // namespace vk\n// clang-format on\n')

    with open(f'cpp{cpp20str}/vkm_string.cpp', 'w') as string_def:
        string_def.write('// clang-format off\n')
        string_def.write('#include "vkm_string.h"\n')
        string_def.write('namespace vk {\n')
        string_def.write('#if defined(WIN32)\n')
        string_def.write('#pragma warning( disable : 4065 )\n')
        string_def.write('#endif //defined(WIN32)\n')
        PrintConsecutivePlatforms(string_def, removed_result.values(), 'print_string_defs')
        PrintConsecutivePlatforms(string_def, bindings.bitmask_dict.values(), 'print_string_defs')
        string_def.write('} // namespace vk\n// clang-format on\n')

def print_c_definitions(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vkm_c_defs.h', 'w') as c_defs:
        c_defs.write('#pragma once\n// clang-format off\n')
        c_defs.write('#include "vk_platform.h"\n')
        c_defs.write('#define VK_ENABLE_BETA_EXTENSIONS\n')
        [ define.print_base(c_defs) for define in bindings.macro_defines ]
        PrintConsecutivePlatforms(c_defs, bindings.base_types, 'print_vk_base')
        PrintConsecutivePlatforms(c_defs, bindings.enum_dict.values(), 'print_c_decl')
        PrintConsecutivePlatforms(c_defs, bindings.bitmask_dict.values(), 'print_c_decl')
        PrintConsecutivePlatforms(c_defs, bindings.flags_dict.values(), 'print_c_decl')
        PrintConsecutivePlatforms(c_defs, bindings.handles.values(), 'print_handle_define')
        PrintConsecutivePlatforms(c_defs, bindings.structures, 'print_c_forward_decl')
        PrintConsecutivePlatforms(c_defs, bindings.func_pointers, 'print_base')
        PrintConsecutivePlatforms(c_defs, bindings.functions, 'print_c_func_pointer')
        c_defs.write('// clang-format on\n')


def print_bindings_version(bindings, cpp20mode, cpp20str):
    print_vkm_main(bindings, cpp20mode, cpp20str)
    print_vkm_core(bindings, cpp20mode, cpp20str)
    print_c_definitions(bindings, cpp20mode, cpp20str)
    print_vkm_function(bindings, cpp20mode, cpp20str)
    print_vkm_string(bindings, cpp20mode, cpp20str)

def main():
    tree = xml.etree.ElementTree.parse('registry/vk.xml')
    root = tree.getroot()

    for tag in root.find('tags'):
        vendor_abbreviations.append(tag.get('name'))

    bindings = BindingGenerator(root)
    print_bindings_version(bindings, False, '17')
    print_bindings_version(bindings, True, '20')

    with open('tests/static_asserts.h', 'w') as static_asserts:
        static_asserts.write('#pragma once\n')
        static_asserts.write('// clang-format off\n')
        static_asserts.write('#include "vkm_core.h"\n')
        static_asserts.write('#include <type_traits>\n')
        static_asserts.write('#include "vulkan/vulkan.h"\n')
        PrintConsecutivePlatforms(static_asserts, bindings.structures, 'print_static_asserts')
        PrintConsecutivePlatforms(static_asserts, bindings.handles.values(), 'print_static_asserts')
        static_asserts.write('// clang-format on\n')

if __name__ == "__main__":
    main()
