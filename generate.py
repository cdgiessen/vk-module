
import xml.etree.ElementTree
import re
from codegen_text import *

#globals that are initialized near beginning of xml parsing
vendor_abbreviations = []
base_type_implicit_conversions = {}
api_constants = {}

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

def MorphVkEnumName(name, enum_name_len):
    n_part = name.title().split('_')[enum_name_len:]
    if n_part[-1] == "Bit":
        n_part = n_part[:-1]
    if n_part[-1].upper() in vendor_abbreviations:
        n_part[-1] = n_part[-1].upper()
    return ''.join(n_part)

def PrintConsecutivePlatforms(file, in_list, function_name, *args, **kwargs):
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
        getattr(item, function_name)(file, *args, **kwargs)
    if prev_platform is not None:
        file.write(f'#endif // defined({prev_platform})\n')

def TrimVkFromType(in_string):
    return in_string[2:] if in_string[:2] == 'Vk' or in_string[:2] == 'vk' else in_string

def TrimVkFromPFN(in_string):
    return f'PFN_{in_string[6:]}' if in_string[:6] == 'PFN_vk' else in_string

def TrimVkFromAll(in_string):
    return TrimVkFromType(TrimVkFromPFN(in_string))

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

class Enum:
    def __init__(self, node):
        self.name = node.get('name')
        self.underlying_type = 'uint32_t'  # for ABI
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
            
    def print_string(self, file):
        if self.alias is not None:
            return
        file.write(f'inline const char * to_string({self.name[2:]} val) {{\n')
        file.write(f'    switch(val) {{\n')
        for name in self.values.keys():
            out_name = MorphVkEnumName(name, self.enum_name_len)
            if out_name[0].isnumeric():
                out_name = f'e{out_name}'
            file.write(f'        case({self.name[2:]}::{out_name}): return \"{out_name}\";\n')
        file.write('        default: return "UNKNOWN";\n    }\n}\n')

    def print_c_interop(self, file):
        if self.alias is None:
            file.write(f'constexpr {self.name} to_c({self.name[2:]} value) {{ return static_cast<{self.name}>(value);}}\n')
            file.write(f'constexpr {self.name[2:]} from_c({self.name} value) {{ return static_cast<{self.name[2:]}>(value);}}\n')

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
        self.underlying_type = 'uint32_t'  # for ABI
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
            file.write(f'inline const char * to_string({self.name[2:]} val) {{\n')
            file.write('    switch(val) {\n')
            for bitpos, name in self.values.items():
                if not RepresentsIntOrHex(bitpos):
                    continue
                out_name = MorphVkEnumName(name, self.bitmask_name_len)
                if out_name[0].isnumeric():
                    out_name = f'e{out_name}'
                file.write(f'        case({self.name[2:]}::{out_name}): return \"{out_name}\";\n')

            file.write('        default: return "UNKNOWN";\n    }\n}\n')
            file.write(f'inline std::string to_string({self.flags_name[2:]} flag){{\n')
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

    def print_c_interop(self, file):
        if self.alias is None:
            file.write(f'constexpr {self.name} to_c({self.name[2:]} value) {{ return static_cast<{self.name}>(value);}}\n')
            file.write(f'constexpr {self.name[2:]} from_c({self.name} value) {{ return static_cast<{self.name[2:]}>(value);}}\n')

class EmptyBitmask:
    def __init__(self, name):
        self.name = name
        self.flags_name = self.name.replace('Bits', 's')
        self.underlying_type = 'uint32_t'
        self.platform = None
    
    def fill_ext_bitmasks(self, bitmask_ext_dict):
        pass
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or self.flags_name in ext_types:
            self.platform = platform

    def print_base(self, file):
        file.write(f'enum class {self.name[2:]}: {self.underlying_type} {{ }};\n')

    def print_string(self, file):
        file.write(f'inline const char * to_string({self.name[2:]} val) {{\n')
        file.write('    switch(val) {\n')
        file.write('        default: return "UNKNOWN";\n    }\n}\n')
        file.write(f'inline std::string to_string({self.flags_name[2:]} flag){{\n')
        file.write(f'    if (flag.flags == 0) return \"None\";\n')
        file.write(f'    return "Unknown";\n}}\n')

    def print_c_interop(self, file):
        pass

class Flags:
    def __init__(self, node):
        if node.find('name') is not None:
            self.name = node.find('name').text
            self.alias = None
        else:
            self.name = node.get('name')
            self.alias = node.get('alias')

        self.underlying_type = 'uint32_t'
        self.flags_name = self.name.replace('Flags', 'FlagBits')
        self.requires = node.get('requires')
        self.need_empty = False
        if self.alias is None and self.requires is None:
            self.need_empty = True
        self.platform = None

    def check_platform(self, platform, ext_types):
        if (self.alias is not None and self.alias in ext_types) or self.name in ext_types:
            self.platform = platform

    def print_base(self, file):
        if self.alias is None:
            file.write(f'DECLARE_ENUM_FLAG_OPERATORS({self.name[2:]}, {self.flags_name[2:]}, {self.underlying_type})\n')
        else:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')

    def print_c_interop(self, file):
        if self.alias is None:
            file.write(f'constexpr {self.name} to_c({self.name[2:]} value) {{ return static_cast<{self.name}>(value);}}\n')

class Handle:
    def __init__(self, node):
        self.name = None
        if node.find('name') is not None:
            self.name = node.find('name').text
            self.dispatchable = node.find('type').text == 'VK_DEFINE_HANDLE' #else is a nondispatchable handle 
            self.dispatchable_text = node.find('type').text
            self.parent = node.get('parent')
        self.alias = node.get('alias')
        if self.alias is not None:
            self.name = node.get('name')
        self.platform = None
        
    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform

    def print_vk_handle(self, file):
        if self.alias is None:
            file.write(f'{self.dispatchable_text}({self.name})\n')
        else:
            file.write(f'using {self.name} = {self.alias};\n')

    def print_base(self, file):
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            file.write(f'''
class {self.name[2:]} {{
    {self.name} handle = 0;
    public:
    {self.name[2:]}() = default;
    {self.name[2:]}([[maybe_unused]] std::nullptr_t none) noexcept {{}}
    explicit {self.name[2:]}({self.name} handle) noexcept : handle(handle){{}}
    {self.name} get() {{ return handle; }}
    explicit operator bool() const {{return handle != 0;}};
    bool operator!() {{ return handle == 0; }}
}};
''')
    
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
        if self.len_attrib is not None:
            if self.len_attrib[:9] == 'latexmath':
                self.len_attrib = re.search(r'\{[A-Za-z]*\}', self.len_attrib).group()[1:-1]
        self.alt_len = node.get('altlen')
        self.length_ref = None

        # type characteristics
        self.is_const = False
        self.pointer_type = 'none'
        self.array_lengths = []
        self.default_value = None
        self.is_equatable = True
        self.bitfield = None
        self.is_ref_eligible = False
           
        self.base_type = node.find('type').text
        self.base_type_modified = TrimVkFromAll(self.base_type)
        # special case cause of bitfields
        if self.base_type_modified == 'GeometryInstanceFlagsKHR':
            self.base_type_modified = 'uint32_t'

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
            self.pointer_type = 'single'
            cur += 1
        if type_list[cur] == '**':
            self.pointer_type = 'double'
            cur += 1
        if type_list[cur] == 'const*':
            self.pointer_type = 'const double'
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

        self.is_equatable = not (self.is_handle or self.is_ptr())

        self.is_ref_eligible = (not self.optional or self.optional != 'true') and (self.len_attrib is None) \
            and ((self.pointer_type == 'single' and self.base_type != "void") or (self.pointer_type == 'double'))

        self.value_category = 'value'
        if self.name in ['sType', 'pNext']:
            self.value_category = self.name

        elif self.len_attrib is None and self.pointer_type == 'single' and self.base_type == 'void':
            self.value_category = 'user_ptr'
        elif not self.optional and self.len_attrib is None and self.pointer_type == 'single' and self.base_type != 'void':
            self.value_category = 'single_ptr'
        elif self.len_attrib is not None and self.len_attrib.find('null-terminated') == -1 and self.pointer_type == 'single':
            self.value_category = 'vector'
        elif self.len_attrib is not None and self.len_attrib.find('null-terminated') == -1 and self.pointer_type in ['double', 'const double']:
            self.value_category = 'vector_of_vector'
        elif self.pointer_type == 'single' and self.optional and self.len_attrib is None:
            self.value_category = 'optional_ptr'
        elif len(self.array_lengths) > 0 and self.len_attrib is None:
            self.value_category = 'array'
        elif self.len_attrib == 'null-terminated':        
            self.value_category = 'string'
        elif self.len_attrib is not None and self.len_attrib.find(',null-terminated') != -1:
            self.value_category = 'vector_of_string'
            self.len_attrib = self.len_attrib[0: self.len_attrib.find(',')]
        # 'len_param' category set by parent object (struct/function)
        # this is because a Variable doesn't know if other variables use it    

    def is_ptr(self):
        return self.pointer_type != 'none'

    def is_double_ptr(self):
        return self.pointer_type in ['double', 'const double']

    def get_base_type(self):
        if self.base_type == 'void' and self.is_ptr():
            return 'std::byte'
        return self.base_type_modified

    def get_span_type(self):
        out = ''
        if self.base_type == 'void' and self.is_ptr():
            out = 'std::byte'
        elif self.is_double_ptr():
            out = f'{self.base_type_modified}*'
        else:
            out = self.base_type_modified
        if self.is_const:
            out = 'const ' + out
        return out

    def get_type_decl(self, use_references=False, downgrade_ptr_type=False):
        type_decl = 'const ' if self.is_const else ''
        type_decl += self.base_type_modified
        if downgrade_ptr_type:
            if self.pointer_type == 'double':
                type_decl += '*'
            elif self.pointer_type == 'const double':
                type_decl += 'const*'
        else:
            if use_references and self.is_ref_eligible:
                type_decl += '& '
            else:
                if self.pointer_type == 'single':
                    type_decl += '*'
                elif self.pointer_type == 'double':
                    type_decl += '**'
                elif self.pointer_type == 'const double':
                    type_decl += '* const*'
        return type_decl

    def get_type_decl_w_arr(self):
        type_decl = self.get_type_decl()
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_parameter_decl(self, use_references):
        type_decl = f'{self.get_type_decl(use_references=use_references)} '
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
        type_decl = self.get_parameter_decl(use_references=False)
        if default_init and self.bitfield is None:
            type_decl += self.get_init()
        type_decl += ';'
        return type_decl

    def get_builder_parameter_decl(self):
        type_decl = ''
        if len(self.array_lengths) > 0:
            if len(self.array_lengths) == 1:
                type_decl = f'std::array<{self.base_type_modified}, {self.array_lengths[0]}>'
            else:
                type_decl += f'{self.base_type_modified}'
                for length in self.array_lengths:
                    type_decl = f'std::array<{type_decl}, {length}>'
        else:
            type_decl += self.get_base_type()
        type_decl += f' {self.name}'
        return type_decl

def get_struct_len_attrib_names(variables):
    names = set()
    for var in variables:
        if var.len_attrib is not None:
            names.add(var.len_attrib)
    return names

def get_function_len_attrib_names(variables):
    names = set()
    for var in variables:
        if var.len_attrib is not None and var.optional is None:
            names.add(var.len_attrib)
    return names

def print_custom_equivalence(file, member_list, name):
    file.write(f'    constexpr bool operator==({name} const& value) const {{\n')
    comp_str = ''
    counter = 0
    for member in member_list:
        if len(member.array_lengths) == 1:
            if f'VK_{member.array_lengths[0]}' in api_constants:
                length = int(api_constants[f'VK_{member.array_lengths[0]}'].value)
            else:
                length = int(member.array_lengths[0])
            comp_str += f'        for(uint32_t i = 0; i < {length}; i++)\n'
            comp_str += f'            is_equal &= {member.name}[i] == value.{member.name}[i];\n'
        elif len(member.array_lengths) == 2:
            comp_str += f'        for(uint32_t i = 0; i < {int(member.array_lengths[0])}; i++)\n'
            comp_str += f'            for(uint32_t j = 0; j < {int(member.array_lengths[1])}; j++)\n'
            comp_str += f'                is_equal &= {member.name}[i][j] == value.{member.name}[i][j];\n'
        else:
            counter = counter + 1
    if comp_str != '':
        file.write('        bool is_equal = true;\n')
        file.write(f'        {comp_str}')
        file.write('        return is_equal')
        if counter > 0: #if there are non array members to compare
            file.write(' && ')
    else:
        file.write('        return ')
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

def MakeBuilderFunctionNames(in_str):
    if in_str.find('ppEnabled') != -1:
        return in_str[2:]
    if in_str[0] == 'p' and in_str[1].isupper():
        return in_str[1:]
    else:
        return in_str[0:1].capitalize() + in_str[1:]

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

        self.is_equatable = True
        for member in self.members:
            if not member.is_equatable:
                self.is_equatable = False
                break

        self.vector_members = get_struct_len_attrib_names(self.members)
        for member in self.members:
            if member.name in self.vector_members:
                member.value_category = 'len_param'
                for member_in in self.members:
                    if member_in.len_attrib == member.name:
                        if member.length_ref is None:
                            member.length_ref = member_in.name
        
        self.is_trivial = True
        for member in self.members:
            if member.value_category != 'value':
                self.is_trivial = False
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or (self.alias is not None and self.alias in ext_types):
            self.platform = platform

    def check_builder(self, functions):
        for function in functions:
            pass

    def print_base(self, file, cpp20mode = True):
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            should_init = self.category == 'struct' #members should default_init in structs but not unions
            file.write(f'{self.category} {self.name[2:]} {{\n')
            for member in self.members:
                if self.name == 'VkDeviceCreateInfo' and member.name in ['ppEnabledLayerNames', 'enabledLayerCount']:
                    file.write('/*deprecated*/')
                file.write(f'    {member.get_struct_member_decl(default_init=should_init)}\n')
            if self.is_equatable:
                print_custom_equivalence(file, self.members, self.name[2:])
            file.write('};\n')

    def print_builder(self, file):
        if self.alias is not None or self.is_trivial or self.returnedonly:
            return
        file.write(f'class {self.name[2:]}Builder {{\n')
        file.write(f'    {self.name[2:]} m_data;\n')

        for member in self.members:
            if self.name == 'VkDeviceCreateInfo' and member.name in ['ppEnabledLayerNames', 'enabledLayerCount']:
                continue
            elif member.value_category in ['sType', 'len_param', 'value']:
                continue
            elif member.value_category == 'pNext':
                file.write(f'    std::vector<void*> pNext;\n')
            elif member.value_category == 'single_ptr':
                file.write(f'    {member.get_base_type()} m_{member.name};\n')
            elif member.value_category == 'vector':
                file.write(f'    std::vector<{member.get_base_type()}> m_{member.name};\n')
            elif member.value_category == 'vector_of_vector':
                file.write(f'    std::vector<std::vector<{member.get_base_type()}>> m_{member.name};\n')
                file.write(f'    std::vector<{member.get_base_type()}*> m_{member.name}_ptr;\n')
            elif member.value_category == 'optional_ptr':
                file.write(f'    detail::optional<{member.get_base_type()}> m_{member.name};\n')
            elif member.value_category == 'string':
                file.write(f'    std::string m_{member.name};\n')
            elif member.value_category == 'vector_of_string':
                file.write(f'    std::vector<std::string> m_{member.name};\n')
                file.write(f'    std::vector<const char *> m_{member.name}_c_str;\n')
                
        file.write(f'    public:\n')
        file.write(f'    {self.name[2:]}Builder() noexcept{{}}\n')
        file.write(f'    {self.name[2:]}Builder({self.name[2:]} data) noexcept : m_data(data) {{}}\n')

        for member in self.members:
            if self.name == 'VkDeviceCreateInfo' and member.name in ['ppEnabledLayerNames', 'enabledLayerCount']:
                continue
            
            elif member.value_category in ['sType', 'len_param']:
                continue
            elif member.value_category == 'pNext':
                pass
            elif member.value_category == 'single_ptr':
                file.write(f'    {self.name[2:]}Builder& set{MakeBuilderFunctionNames(member.name)}({member.get_builder_parameter_decl()}) {{ ')
                file.write(f'this->m_{member.name} = {member.name}; return *this; }}\n')
            elif member.value_category == 'vector':
                file.write(f'    {self.name[2:]}Builder& add{MakeBuilderFunctionNames(member.name)}({member.get_builder_parameter_decl()}) {{ ')
                file.write(f'this->m_{member.name}.push_back({member.name}); return *this; }}\n')
            elif member.value_category == 'vector_of_vector':
                file.write(f'    {self.name[2:]}Builder& add{MakeBuilderFunctionNames(member.name)}(std::vector<{member.get_base_type()}> {member.name}) {{')
                file.write(f'this->m_{member.name}.push_back({member.name}); return *this; }}\n')
            elif member.value_category == 'optional_ptr':
                file.write(f'    {self.name[2:]}Builder& set{MakeBuilderFunctionNames(member.name)}({member.get_builder_parameter_decl()}) {{ ')
                file.write(f'this->m_{member.name} = {member.name}; return *this; }}\n')
            elif member.value_category == 'array':
                file.write(f'    {self.name[2:]}Builder& set{MakeBuilderFunctionNames(member.name)}({member.get_builder_parameter_decl()}) {{ ')
                if len(member.array_lengths) == 1:
                    file.write(f'for(uint32_t i = 0; i < {member.array_lengths[0]}; i++) this->m_data.{member.name}[i] = {member.name}[i]; return *this; }}\n')
                if len(member.array_lengths) == 2:
                    file.write(f'\n        for(uint32_t i = 0; i < {member.array_lengths[0]}; i++){{ for(uint32_t j = 0; j < {member.array_lengths[1]}; j++){{\n')
                    file.write(f'        this->m_data.{member.name}[i][j] = {member.name}[i][j];}}}} return *this; }}\n')
            elif member.value_category == 'value':
                file.write(f'    {self.name[2:]}Builder& set{MakeBuilderFunctionNames(member.name)}({member.get_builder_parameter_decl()}) {{ ')
                file.write(f'this->m_data.{member.name} = {member.name}; return *this; }}\n')
            elif member.value_category == 'string':
                file.write(f'    {self.name[2:]}Builder& add{MakeBuilderFunctionNames(member.name)}(std::string {member.name}) {{ ')
                file.write(f'this->m_{member.name} = {member.name}; return *this; }}\n')
            elif member.value_category == 'vector_of_string':
                file.write(f'    {self.name[2:]}Builder& add{MakeBuilderFunctionNames(member.name)}(std::string {member.name}) {{')
                file.write(f'this->m_{member.name}.push_back({member.name}); return *this; }}\n')
        
        file.write(f'    {self.name[2:]} build() {{\n')
        file.write(f'        {self.name[2:]} out{{m_data}};\n')
        for member in self.members:
            if self.name == 'VkDeviceCreateInfo' and member.name in ['ppEnabledLayerNames', 'enabledLayerCount']:
                continue
            elif member.value_category in ['sType', 'value']:
                continue
            elif member.name == 'pNext':
                #needs special handling
                pass
            elif member.value_category == 'len_param':
                if member.name == 'rasterizationSamples':
                    #Aaaaaaa stupid latexmath and using a flag bits to do vector lengths
                    pass
                else:
                    file.write(f'        out.{member.name} = (uint32_t)m_{member.length_ref}.size();\n')
            elif member.value_category == 'single_ptr':
                file.write(f'        out.{member.name} = &m_{member.name};\n')
            elif member.value_category == 'vector':
                file.write(f'        out.{member.name} = m_{member.name}.data();\n')
            elif member.value_category == 'vector_of_vector':
                file.write(f'        m_{member.name}_ptr.clear(); m_{member.name}_ptr.reserve(m_{member.name}.size());\n')
                file.write(f'        for(auto& val : m_{member.name}) {{ m_{member.name}_ptr.push_back(val.data()); }}\n')
                file.write(f'        out.{member.name} = m_{member.name}_ptr.data();\n')
            elif member.value_category == 'optional_ptr':
                file.write(f'        out.{member.name} = m_{member.name}.ptr_or_nullptr();\n')
            elif member.value_category == 'string':
                file.write(f'        out.{member.name} = m_{member.name}.data();\n')
            elif member.value_category == 'vector_of_string':
                file.write(f'        m_{member.name}_c_str.clear(); m_{member.name}_c_str.reserve(m_{member.name}.size());\n')
                file.write(f'        for(auto& val : m_{member.name}) {{ m_{member.name}_c_str.push_back(val.c_str()); }}\n')
                file.write(f'        out.{member.name} = m_{member.name}_c_str.data();\n')
        file.write(f'        return out; }}\n')
        file.write(f'}};\n')

    def print_static_asserts(self, file):
        if self.category == 'struct':
            file.write(f'static_assert( sizeof(vk::{self.name[2:]}) == sizeof({self.name}), "Must maintain size between types" );\n')
            file.write(f'static_assert( std::is_standard_layout<vk::{self.name[2:]}>::value, "Must be a standard layout type" );\n')

class Function:
    def __init__(self, node, handles, dispatchable_handles, default_values):
        self.success_codes = node.get('successcodes', default='').split(',')
        self.error_codes = node.get('errorcodes', default='').split(',')

        self.platform = None
        proto = node.find('proto')
        self.name = proto.find('name').text if proto is not None else node.get('name')
        self.alias = node.get('alias') if proto is None else None
        self.return_type = proto.find('type').text if proto is not None else None

        self.pfn_name = f'pfn_{self.name[2:]}'
        self.pfn_type = f'PFN_{self.name[2:]}'

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
        
        self.span_params = get_function_len_attrib_names(self.parameters)
        for param in self.parameters:
            if param.name in self.span_params:
                param.value_category = 'len_param'

        self.function_category = 'basic'
        self.full_return_type = None
        self.modified_param_list = self.parameters
        
        if len(self.parameters) > 0 and self.parameters[-1].is_ptr() \
            and not self.parameters[-1].is_const and self.parameters[-1].len_attrib is None:
            self.function_category = 'single_query'
            self.query_name = self.parameters[-1].name
            self.modified_param_list = self.parameters[:-1]
            self.query_type = TrimVkFromType(self.parameters[-1].get_type_decl(downgrade_ptr_type=True))
            if self.return_type != 'void':
                self.full_return_type = f'expected<{self.query_type}>'
                self.return_statement = f'return expected<{self.query_type}>({self.query_name}, result);\n'
            else:
                self.full_return_type = f'{self.query_type}'
                self.return_statement = f'return {self.query_name};\n'
        elif self.name in ['vkCreateGraphicsPipelines', 'vkCreateComputePipelines', 'vkAllocateDescriptorSets', 'vkAllocateCommandBuffers']:
            self.function_category = 'multi_query'
            self.modified_param_list = self.parameters[:-1]
            self.query_type = TrimVkFromType(self.parameters[-1].get_type_decl(downgrade_ptr_type=self.parameters[-1].base_type != 'void'))
            self.query_name = self.parameters[-1].name
            self.count_name = self.parameters[-1].len_attrib.replace('->', '.')
            if self.return_type != 'void':
                self.full_return_type = f'expected<detail::fixed_vector<{self.query_type}>>'
                self.return_statement = f'return expected<detail::fixed_vector<{self.query_type}>>(std::move({self.query_name}), result);\n'
            else:
                self.full_return_type = f'detail::fixed_vector<{self.query_type}>'
                self.return_statement = f'return detail::fixed_vector<{self.query_type}>;\n'
        elif len(self.parameters) > 1 and self.parameters[-1].is_ptr() and not self.parameters[-1].is_const and self.parameters[-1].len_attrib is not None:
            if self.parameters[-2].optional is not None and self.parameters[-2].optional == 'false,true':
                self.function_category = 'enumeration' 
                self.modified_param_list = self.parameters[:-2]
                self.query_type = self.parameters[-1].get_type_decl(downgrade_ptr_type=self.parameters[-1].base_type != 'void')
                self.base_query_type =self.parameters[-1].get_type_decl()
                self.query_name = self.parameters[-1].name
                self.count_type = self.parameters[-2].base_type
                self.count_name = self.parameters[-2].name
                if self.return_type != 'void':
                    self.full_return_type = f'expected<detail::fixed_vector<{self.query_type}>>'
                    self.return_statement = f'return expected(std::move({self.query_name}), result);\n'
                else: # void
                    self.full_return_type = f'detail::fixed_vector<{self.query_type}>'
                    self.return_statement = f'return {self.query_name};\n'
        
        #autogen doesn't handle these functions
        if self.name in ['vkGetRayTracingShaderGroupHandlesKHR', 'vkGetAccelerationStructureHandleNV','vkGetRayTracingCaptureReplayShaderGroupHandlesKHR']:
            self.function_category = 'basic'
            return

    def check_platform(self, platform, ext_functions):
        if self.name in ext_functions:
            self.platform = platform
    
    def print_pfn_variable_decl(self, file):
        file.write(f'    detail::{self.pfn_type} {self.pfn_name} = nullptr;\n')

    def print_get_pfn_statement(self, file, gpa_name, gpa_val):
        file.write(f'    pfn_{self.name[2:]} = ')
        file.write(f'reinterpret_cast<detail::{self.pfn_type}>({gpa_name}({gpa_val},\"{self.name}\"));\n')

    def print_pfn_func_decl(self, file):
        if self.alias is not None:
            file.write(f'using {self.pfn_type} = PFN_{TrimVkFromType(self.alias)};\n')
            return
        file.write(f'using {self.pfn_type} = {TrimVkFromAll(self.return_type)} (*) (')
        for param in self.parameters:
            if param != self.parameters[0]:
                file.write(', ')                
            file.write(f'{param.get_parameter_decl(use_references=False)}')
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
        else:
            return_type += f'{TrimVkFromAll(self.return_type)} '
        return return_type

    def print_name(self, file, replace_list = []):
        print_function_name = self.name[2:]
        for str_from in replace_list:
            print_function_name = print_function_name.replace(str_from, '')
        file.write(f'{print_function_name}')

    def print_parameters(self, file, parameter_list, break_between=True, print_defaults=False):
        should_print_comma = False #prevents printing of a comma before the first real parameter
        index = -1
        for param in parameter_list:
            index = index + 1
            if param != parameter_list[0]:
                if param.name not in self.span_params: 
                    if should_print_comma:
                        file.write(', ')
                        if break_between:
                            file.write(f'\n    ')
                
            if param.name in self.span_params: 
                continue            
            elif param.len_attrib is not None and param.len_attrib in self.span_params:
                file.write(f'detail::span<{param.get_span_type()}> {param.name[1:]}')
            else:
                file.write(f'{param.get_parameter_decl(use_references=True)}')
            if param.optional == "true":
                all_optional = True
                for inner_param in parameter_list[index:]:
                    if not inner_param.optional:
                        all_optional = False
                        break
                if all_optional:
                    if param.is_ptr() and param.len_attrib not in self.span_params:
                        file.write(f' = nullptr')
                    else:
                        file.write(' = {}')
            should_print_comma = True

    def print_c_api_call(self, file, dispatch_handle = None, dispatch_handle_name = None, pfn_source=None, last_arg=None, init_result=None):
        if self.return_type != 'void':
            if init_result == 'init_result': 
                file.write(f'    Result result = ')
            elif init_result == 'assign_result':
                file.write(f'    result = ')

        if pfn_source is not None:
            file.write(f'{pfn_source}->')
        file.write(f'{self.pfn_name}(')

        for param in self.parameters:
            if param == self.parameters[0]:
                if dispatch_handle is not None and f'{dispatch_handle}' == self.dispatch_handle:
                    file.write(f'{dispatch_handle_name}')
                    continue
            else:
                file.write(f',\n        ')

            param_name = f'{param.name}'
            if param.len_attrib in self.span_params:
                param_name = f'{param_name[1:]}.data()' 
            # the last argument
            if last_arg is not None and param == self.parameters[-1]:
                file.write(last_arg)
            elif param.is_handle and not param.is_ptr():
                file.write(param.name)
            elif param.base_type not in base_type_default_values.keys() and param.base_type not in base_type_implicit_conversions:
                if param.is_ptr():
                    if param.is_ref_eligible:
                        file.write('&')
                    file.write(f'{param_name}')
                else:
                    file.write(f'{param_name}')
            else:
                if param.is_ref_eligible:
                    file.write('&')
                file.write(param_name)
        file.write(');\n')

    def inner_print_function(self, file, dispatch_handle = None, dispatch_handle_name = None, pfn_source=None):
        file.write(f'{self.get_return_type(full_return_type=self.full_return_type)}')
        self.print_name(file)
        parameter_list = self.modified_param_list
        if dispatch_handle is not None and f'{dispatch_handle}' == self.dispatch_handle:
            parameter_list = parameter_list[1:]
        file.write('(')
        self.print_parameters(file, parameter_list, print_defaults=True)
        file.write(') const {\n')
        file.write('    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE\n')
        if self.name == 'vkEnumerateInstanceVersion':
            #early return because 1.0 doesn't support the function, will be null and shouldn't cause a crash
            file.write(f'    if (pfn_EnumerateInstanceVersion == 0) return expected<uint32_t>(make_vk_version(1,0,0), Result::Success);\n')
        for param in self.parameters:
            if param.name in self.span_params:
                for inner_param in self.parameters:
                    if inner_param.len_attrib is not None and inner_param.len_attrib == param.name:
                        file.write(f'    {param.get_base_type()} {param.name} = {inner_param.name[1:]}.size();\n')
                        break

        if self.function_category == 'basic':
            file.write(f'    ')
            if self.return_type != 'void':
                file.write(f'return ')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source)
        if self.function_category == 'single_query':
            file.write(f'    {self.query_type} {self.query_name};\n    ')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, init_result='init_result')
            file.write(f'    {self.return_statement}')
        elif self.function_category == 'multi_query':
            file.write(f'    detail::fixed_vector<{self.query_type}> {self.query_name}{{{self.count_name}}};\n')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, last_arg=f'{self.query_name}.data()', init_result='init_result')
            file.write(f'    {self.return_statement}')
        elif self.function_category == 'enumeration':
            file.write(f'    {self.count_type} {self.count_name} = 0;\n    ')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, 'nullptr', init_result='init_result')
            if self.return_type != 'void':
                file.write(f'    if (result < Result::Success) return expected(detail::fixed_vector<{self.query_type}>{{}}, result);\n')
            file.write(f'    detail::fixed_vector<{self.query_type}> {self.query_name}{{{self.count_name}}};\n')
            self.print_c_api_call(file, dispatch_handle, dispatch_handle_name, pfn_source, last_arg=f'{self.query_name}.data()',init_result='assign_result')
            file.write(f'    if ({self.count_name} < {self.query_name}.size()) {self.query_name}.shrink({self.count_name});\n')
            file.write(f'    {self.return_statement}')

        file.write(f'}}\n')

    def print_function(self, file, dispatch_handle = None, dispatch_handle_name = None, pfn_source=None, cpp20mode=False):
        if self.alias is not None:
            file.write(f'const auto {self.name[2:]} = {self.alias[2:]};\n')
            return
        self.inner_print_function(file, dispatch_handle, dispatch_handle_name, pfn_source)

    def inner_print_forwarding_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=[], \
            pfn_source=None, make_void_return_this=None):
        if make_void_return_this is not None and self.return_type == 'void':
            file.write(f'{self.get_return_type(replace_list, make_void_return_this)}')
        else:
            file.write(f'{self.get_return_type(replace_list,  self.full_return_type)}')

        self.print_name(file, replace_list)
        file.write('(')
       
        self.print_parameters(file, self.modified_param_list[1:], break_between=False)
        file.write(') const {\n')
        file.write(f'    ')
        if self.return_type != 'void' or self.full_return_type != None:
            file.write(f'return ')
        file.write(f'{pfn_source}->{self.name[2:]}(')
        #print parameters in call to source
        for param in self.modified_param_list:
            if param == self.modified_param_list[0]:
                file.write(f'{dispatch_handle_name}')
            else:
                if param.name in self.span_params:
                    continue
                elif param.len_attrib is not None and param.len_attrib in self.span_params:
                    file.write(f', {param.name[1:]}')
                    continue
                file.write(f', {param.name}')
        
        file.write(f');')
        if self.return_type == 'void' and make_void_return_this is not None:
            file.write(f'\n    return *this;')
        file.write(f' }}\n')

    def print_forwarding_function(self, file, dispatch_handle = None, dispatch_handle_name = None, replace_list=None, \
            pfn_source=None, make_void_return_this=None, cpp20mode=False):
        if self.alias is not None:
            file.write(f'const auto {self.name[2:]} = {self.alias[2:]};\n')
            return
        self.inner_print_forwarding_function(file, dispatch_handle, dispatch_handle_name, replace_list, pfn_source, make_void_return_this)

class FuncPointer:
    def __init__(self, node):
        self.name = node.find('name').text
        self.text = ''
        for t in node.itertext():
            t.replace('VkBool32', 'Bool32')
            self.text += TrimVkFromAll(t.replace('VkBool32', 'Bool32'))

    def print_base(self, file):
        file.write(self.text + '\n')

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
    enum_value = -enum_value if direction == '-' else enum_value
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
        [enum_dict[key].fill_ext_enums(self.enum_dict[key]) for key in self.enum_dict.keys()]

    def fill_bitmasks(self, bitmask_dict):
        [bitmask_dict[key].fill_ext_bitmasks(self.bitmask_dict[key]) for key in self.bitmask_dict.keys()]
    
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

        self.gpa_type = 'PFN_GetDeviceProcAddr' if self.dispatch_type  == 'device' else 'PFN_GetInstanceProcAddr'
        self.gpa_name = 'get_device_proc_addr'  if self.dispatch_type == 'device' else 'get_instance_proc_addr'
        self.dispatch_handle = f'Vk{self.dispatch_type.title()}' if self.dispatch_type != 'global' else None
        self.gpa_val = f'{self.dispatch_type}' if self.dispatch_type != 'global' else 'nullptr'

    def print_definition(self, file, cpp20mode):                
        file.write(f'struct {self.name}Functions {{\n')
        #function pointers
        if self.dispatch_type != 'global':
            file.write(f'    {self.dispatch_type.title()} {self.dispatch_type};\n')
        PrintConsecutivePlatforms(file, self.functions.values(), 'print_pfn_variable_decl')

        #functions
        PrintConsecutivePlatforms(file, self.functions.values(), "print_function", dispatch_handle=self.dispatch_handle\
            ,dispatch_handle_name=self.dispatch_type, cpp20mode=cpp20mode)
             
        #constructor
        file.write(f'{self.name}Functions() noexcept {{}}\n')   
        if self.dispatch_type == 'global':
            file.write(f'explicit {self.name}Functions(DynamicLibrary const& library) noexcept {{\n')
            file.write(f'    detail::{self.gpa_type} {self.gpa_name} = reinterpret_cast<detail::PFN_GetInstanceProcAddr>(library.get());\n')
        elif self.dispatch_type == 'instance':
            file.write(f'explicit {self.name}Functions(GlobalFunctions const& global_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept \n')
            file.write(f'    :{self.dispatch_type}({self.dispatch_type}) {{ \n')
            file.write(f'    detail::{self.gpa_type} {self.gpa_name} = global_functions.pfn_GetInstanceProcAddr;\n')
        elif self.dispatch_type == 'device':
            file.write(f'explicit {self.name}Functions(InstanceFunctions const& instance_functions, {self.dispatch_type.title()} {self.dispatch_type}) noexcept ')
            if self.name == 'Device':
                file.write(f'\n    :{self.dispatch_type}({self.dispatch_type}) {{\n')
            else:
                file.write('{\n')
            file.write(f'    detail::{self.gpa_type} {self.gpa_name} = instance_functions.pfn_GetDeviceProcAddr;\n')
        PrintConsecutivePlatforms(file, self.functions.values(), "print_get_pfn_statement", self.gpa_name, self.gpa_val)
        file.write('}\n')
        file.write('};\n')

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
        file.write(f'''    struct {self.type_name}Functions {{
    {self.functions_type} const* {self.functions_name};
    {self.type_name} {self.var_name};
    {self.type_name}Functions() noexcept {{}}
    {self.type_name}Functions({self.functions_type} const& {self.functions_name}, {self.type_name} const {self.var_name}) noexcept:
    {self.functions_name}{{&{self.functions_name}}}, {self.var_name}{{{self.var_name}}} {{}}''')
        PrintConsecutivePlatforms(file, self.functions, "print_forwarding_function", dispatch_handle=self.name, dispatch_handle_name=self.var_name, replace_list=self.replace_list, \
                pfn_source=self.functions_name, make_void_return_this=command_buffer_return_type, cpp20mode=cpp20mode)
        file.write('};\n')
            
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
            if not structure.is_equatable:
                continue
            comparable = True
            for member in structure.members:
                for sub_type in self.structures:
                    if member.base_type == sub_type.name:
                        if not sub_type.is_equatable:
                            comparable = False
                            break
            structure.is_equatable = comparable

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

        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkPhysicalDevice', 'instance',['PhysicalDevice'], self.functions))
        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkQueue', 'device',['Queue'], self.functions))
        self.dispatchable_handle_tables.append(DispatchableHandleDispatchTable('VkCommandBuffer', 'device',['Cmd', 'CommandBuffer'], self.functions))
  

def print_bindings(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vk_module.h', 'w') as vkm:
        vkm.write(vk_module_file_header)
        #definitions
        PrintConsecutivePlatforms(vkm, api_constants.values(), 'print_base')
        PrintConsecutivePlatforms(vkm, bindings.base_types, 'print_base')
        PrintConsecutivePlatforms(vkm, bindings.enum_dict.values(), 'print_base')
        PrintConsecutivePlatforms(vkm, bindings.bitmask_dict.values(), 'print_base')
        vkm.write(bitmask_flags_macro + '\n')
        PrintConsecutivePlatforms(vkm, bindings.flags_dict.values(), 'print_base')
        vkm.write('} //namespace vk\n')
        [ handle.print_vk_handle(vkm) for handle in bindings.handles.values() ]
        vkm.write('namespace vk {\n')
        
        PrintConsecutivePlatforms(vkm, bindings.handles.values(), 'print_base')

        vkm.write('struct DebugUtilsMessengerCallbackDataEXT;\n')
        vkm.write('struct DeviceMemoryReportCallbackDataEXT;\n')
        PrintConsecutivePlatforms(vkm, bindings.func_pointers, 'print_base')
        PrintConsecutivePlatforms(vkm, bindings.structures, 'print_base', cpp20mode)
        vkm.write('namespace detail {\n')
        PrintConsecutivePlatforms(vkm, bindings.functions, 'print_pfn_func_decl')
        vkm.write('} //namespace detail\n')

        #dispatch function objects
        vkm.write(vulkan_library_text + '\n')

        [ dispatch_table.print_definition(vkm, cpp20mode) for dispatch_table in bindings.dispatch_tables ]
        [ table.print_definition(vkm, cpp20mode) for table in bindings.dispatchable_handle_tables ]
        PrintConsecutivePlatforms(vkm, bindings.structures, 'print_builder')

        #to_string
        vkm.write('#pragma warning( push )\n')
        vkm.write('#pragma warning( disable : 4065 )\n')
        PrintConsecutivePlatforms(vkm, bindings.enum_dict.values(), 'print_string')
        PrintConsecutivePlatforms(vkm, bindings.bitmask_dict.values(), 'print_string')
        vkm.write('#pragma warning( pop )\n')

        vkm.write('} // namespace vk\n// clang-format on\n')

def print_c_interop(bindings, cpp20mode, cpp20str):
    with open(f'cpp{cpp20str}/vk_module_interop.h', 'w') as c_interop:
        c_interop.write('#pragma once\n// clang-format off\n')
        c_interop.write('#include <vulkan/vulkan.h>\n')
        c_interop.write('#include "vk_module.h"\n')
        c_interop.write('namespace vk {\n')
        PrintConsecutivePlatforms(c_interop, bindings.enum_dict.values(), 'print_c_interop')
        PrintConsecutivePlatforms(c_interop, bindings.bitmask_dict.values(), 'print_c_interop')
        PrintConsecutivePlatforms(c_interop, bindings.flags_dict.values(), 'print_c_interop')
        #PrintConsecutivePlatforms(c_interop, bindings.structures, 'print_c_interop')
        c_interop.write('} // namespace vk\n// clang-format on\n')

def main():
    tree = xml.etree.ElementTree.parse('registry/vk.xml')
    root = tree.getroot()

    for tag in root.find('tags'):
        vendor_abbreviations.append(tag.get('name'))

    bindings = BindingGenerator(root)
    print_bindings(bindings, False, '17')
    print_bindings(bindings, True, '20')

    print_c_interop(bindings, False, '17')
    print_c_interop(bindings, True, '20')

    with open('tests/static_asserts.h', 'w') as static_asserts:
        static_asserts.write('#pragma once\n')
        static_asserts.write('// clang-format off\n')
        static_asserts.write('#include "vk_module.h"\n')
        static_asserts.write('#include <type_traits>\n')
        static_asserts.write('#include "vulkan/vulkan.h"\n')
        PrintConsecutivePlatforms(static_asserts, bindings.structures, 'print_static_asserts')
        PrintConsecutivePlatforms(static_asserts, bindings.handles.values(), 'print_static_asserts')
        static_asserts.write('// clang-format on\n')

if __name__ == "__main__":
    main()
