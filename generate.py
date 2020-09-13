

import xml.etree.ElementTree
import re

'''
todo list

handles are a thing, decide what to do
member arrays (+ vk constants -> int's)
dispatchable handles (instance, physdevice, device, queue, command buffer)
create separate versions for C++20 and C++14  
generate test code for flags
create dll/so vulkan loader


In progress
move platform entities together to reduce the #if-def bloat

Done: 
functions
bitfields...
platform specific entities
to_string for enums/flags/bitmasks
type safe enums/flags/bitmasks
fp dispatch table objects
extensions -- need to be gotten from 'features'
enum/flags with members from extensions (need 'features' stuff)
variables with double arrays eg [3][4]
return types as vk::Result
extension function tables
remove disabled extension types
'''

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

class BaseType:
    def __init__(self, node):
        self.name = node.find('name').text
        self.type = None
        if node.find('type') is not None:
            self.type = node.find('type').text
            self.default_value = base_type_default_values[self.type]

    def print(self, file):
        if self.type is not None:
            file.write(f'using {self.name[2:]} = {self.type};\n')

class FuncPointer:
    def __init__(self, node):
        self.name = node.find('name').text
        self.text = ''
        for t in node.itertext():
            self.text += t

    def print(self, file):
        file.write(self.text + '\n')

class MacroDefine:
    def __init__(self, node):
        self.name = node.find("name")
        self.text = ''
        for t in node.itertext():
            self.text += t
        self.text += '\n'

    def print(self, file):
        file.write(self.text)


def MorphVkEnumName(name, enum_name_len):
    n_part = name.title().split('_')[enum_name_len:]
    if n_part[-1] == "Bit":
        n_part = n_part[:-1]
    if n_part[-1].upper() in vendor_abbreviations:
        n_part[-1] = n_part[-1].upper()
    return ''.join(n_part)

def MorphVkBitaskName(name, bitmask_name_len):
    n_part = name.title().split('_')[bitmask_name_len:]
    if n_part[-1] == "Bit":
        n_part = n_part[:-1]
    if n_part[-1].upper() in vendor_abbreviations:
        n_part[-1] = n_part[-1].upper()
    return ''.join(n_part)

def PlatformGuardHeader(file, guard):
    if guard is not None:
        file.write('#if defined({})\n'.format(guard))

def PlatformGuardFooter(file, guard):
    if guard is not None:
        file.write('#endif // {}\n'.format(guard))

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

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else: 
            file.write(f"enum class {self.name[2:]} : {self.underlying_type} {{\n")
            for name, value in self.values.items():
                file.write(f'    e{MorphVkEnumName(name, self.enum_name_len)} = {str(value)},\n')
            file.write('};\n')
        PlatformGuardFooter(file, self.platform)
    
    def print_string(self, file):
        if self.alias is None:
            PlatformGuardHeader(file, self.platform)
            file.write(f'const char * to_string({self.name[2:]} val) ' + '{\n')
            file.write('    switch(val) {\n')
            for name, value in self.values.items():
                out_name = MorphVkEnumName(name, self.enum_name_len)
                file.write(f'        case({self.name[2:]}::e{out_name}): return \"e{out_name}\";\n')
            file.write('        default: return "UNKNOWN";\n    }\n}\n')
            PlatformGuardFooter(file, self.platform)


class Bitmask:
    def __init__(self, node):
        self.name = node.get('name')
        self.flags_name = self.name.replace('Bits', 's')
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
                value = 'e' + \
                    MorphVkBitaskName(elem.get('alias'), self.bitmask_name_len)
            self.values[value] = elem.get('name')

    def fill_ext_bitmasks(self, bitmask_ext_dict):
        for ext_bit in bitmask_ext_dict:
            self.values[str(1 << ext_bit.bitpos)] = ext_bit.name

    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write(f'using {self.name} = {self.alias[2:]};\n')
        else:
            file.write('enum class ' + self.name[2:] + ': uint32_t {\n')
            for bitpos, name in self.values.items():
                file.write(f"    e{MorphVkBitaskName(name, self.bitmask_name_len)} = {bitpos},\n")
            file.write('};\n')
        PlatformGuardFooter(file, self.platform)

    def print_string(self, file):
        if self.alias is None:
            PlatformGuardHeader(file, self.platform)
            file.write('const char * to_string(' + self.name[2:] + ' val) {\n')
            file.write('    switch(val) {\n')
            for bitpos, name in self.values.items():
                try:
                    out_val = int(bitpos)
                    out_name = MorphVkBitaskName(name, self.bitmask_name_len)
                    file.write(f'        case({self.name[2:]}::e{out_name}): return \"e{out_name}\";\n')
                except ValueError:
                    pass
            file.write('        default: return "UNKNOWN";\n    }\n}\n')
            file.write(f'std::string to_string({self.flags_name[2:]} flag){{\n')
            file.write(f'    if (flag.flags == 0) return \"None\";\n')
            file.write(f'    std::string out;\n')
            for bitpos, name in self.values.items():
                try:
                    out_val = int(bitpos)
                    out_name = MorphVkBitaskName(name, self.bitmask_name_len)
                    file.write(f'    if (flag & {self.name[2:]}::e{out_name}) out += \"e{out_name} | \";\n')
                except ValueError:
                    pass
            file.write(f'    return out.substr(0, out.size() - 3);\n}};\n')
            PlatformGuardFooter(file, self.platform)

            

class EmptyBitmask:
    def __init__(self, name):
        self.name = name
        self.flags_name = self.name.replace('Bits', 's')
        self.platform = None
    
    def fill_ext_bitmasks(self, bitmask_ext_dict):
        pass
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or self.flags_name in ext_types:
            self.platform = platform
    
    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        file.write(f'enum class {self.name[2:]}: uint32_t {{ }};\n')
        PlatformGuardFooter(file, self.platform)

    def print_string(self, file):
        PlatformGuardHeader(file, self.platform)
        file.write(f'const char * to_string({self.name[2:]} val) {{\n')
        file.write('    switch(val) {\n')
        file.write('        default: return "UNKNOWN";\n    }\n}\n')
        file.write(f'std::string to_string({self.flags_name[2:]} flag){{\n')
        file.write(f'    if (flag.flags == 0) return \"None\";\n')
        file.write(f'    return "Unknown";\n}};\n')
        PlatformGuardFooter(file, self.platform)



bitmask_flags_macro = '''
#define DECLARE_ENUM_FLAG_OPERATORS(FLAG_TYPE, FLAG_BITS, BASE_NAME)                \\
                                                                                    \\
struct FLAG_TYPE {                                                                  \\
    using base_type = typename std::underlying_type_t<FLAG_BITS>;                   \\
    base_type flags = static_cast<base_type>(0);                                    \\
                                                                                    \\
    constexpr explicit FLAG_TYPE() noexcept = default;                              \\
    constexpr explicit FLAG_TYPE(base_type in) noexcept: flags(in){ }               \\
    constexpr FLAG_TYPE(FLAG_BITS in) noexcept: flags(static_cast<base_type>(in)){ }   \\
    constexpr bool operator==(FLAG_TYPE const& right) const = default;              \\
    constexpr explicit operator bool() const noexcept {                             \\
      return flags != 0;                                                            \\
    }                                                                               \\
    constexpr explicit operator BASE_NAME() const noexcept {                        \\
        return static_cast<BASE_NAME>(flags);                                       \\
    }                                                                               \\
    constexpr FLAG_TYPE operator|(FLAG_TYPE b) noexcept {                           \\
        return static_cast<FLAG_TYPE>(flags | b.flags);                             \\
    }                                                                               \\
    constexpr FLAG_TYPE& operator|=(FLAG_TYPE b) noexcept {                         \\
        flags = (flags | b.flags);                                                  \\
        return *this;                                                               \\
    }                                                                               \\
    constexpr FLAG_TYPE operator&(FLAG_TYPE b) noexcept {                           \\
        return static_cast<FLAG_TYPE>(flags & b.flags);                             \\
    }                                                                               \\
    constexpr FLAG_TYPE& operator&=(FLAG_TYPE b) noexcept {                         \\
        flags = (flags & b.flags);                                                  \\
        return *this;                                                               \\
    }                                                                               \\
    constexpr FLAG_TYPE operator~() noexcept {                                      \\
        return static_cast<FLAG_TYPE>(~flags);                                      \\
    }                                                                               \\
    constexpr FLAG_TYPE operator^(FLAG_TYPE b) noexcept {                           \\
        return static_cast<FLAG_TYPE>(flags ^ b.flags);                             \\
    }                                                                               \\
    constexpr FLAG_TYPE operator^=(FLAG_TYPE b) noexcept {                          \\
        flags = (flags ^ b.flags);                                                  \\
        return *this;                                                               \\
    }                                                                               \\
    constexpr FLAG_TYPE& operator^=(FLAG_BITS b) noexcept {                         \\
        flags = (flags ^ static_cast<base_type>(b));                                \\
        return *this;                                                               \\
    }                                                                               \\
};                                                                                  \\
                                                                                    \\
constexpr FLAG_TYPE operator|(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) | static_cast<T>(b));           \\
}                                                                                   \\
constexpr FLAG_TYPE operator|(FLAG_BITS a, FLAG_TYPE b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) | b.flags);                     \\
}                                                                                   \\
constexpr FLAG_TYPE operator&(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) & static_cast<T>(b));           \\
}                                                                                   \\
constexpr FLAG_TYPE operator&(FLAG_BITS a, FLAG_TYPE b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) & b.flags);                     \\
}                                                                                   \\
constexpr FLAG_TYPE operator~(FLAG_BITS key) noexcept {                             \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(~static_cast<T>(key));                            \\
}                                                                                   \\
constexpr FLAG_TYPE operator^(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) ^ static_cast<T>(b));           \\
}                                                                                   \\
constexpr FLAG_TYPE operator^(FLAG_BITS a, FLAG_TYPE b) noexcept {                  \\
    using T = std::underlying_type_t<FLAG_BITS>;                                    \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) ^ b.flags);                     \\
}                                                                                   \\
'''

class Flags:
    def __init__(self, node):
        if node.find('name') is not None:
            self.name = node.find('name').text
            self.alias = None
        else:
            self.name = node.get('name')
            self.alias = node.get('alias')

        self.flags_name = self.name.replace('Flags', 'FlagBits')
        self.requires = node.get('requires')
        self.need_empty = False
        if self.alias is None and self.requires is None:
            self.need_empty = True
        self.platform = None

    def check_platform(self, platform, ext_types):
        if (self.alias is not None and self.alias in ext_types) or self.name in ext_types:
            self.platform = platform

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is None:
            file.write(f'DECLARE_ENUM_FLAG_OPERATORS({self.name[2:]}, {self.flags_name[2:]}, {self.name})\n')
        else:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        PlatformGuardFooter(file, self.platform)

class ApiConstant:
    def __init__(self, node):
        self.name = node.get('name')
        self.value = node.get('value')
        self.alias = node.get('alias')

    def print(self, file):
        if self.alias is not None:
            file.write(f'constexpr auto {self.name[3:]} = {self.alias[3:]};\n')
        elif self.value is not None:
            file.write(f'constexpr size_t {self.name[3:]} = {self.value};\n')

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

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        elif self.dispatchable:
            file.write(f'class {self.name[2:]} {{\n')
            file.write(f'    {self.name} handle = VK_NULL_HANDLE;\n')
            file.write(f'    public:\n')
            file.write(f'    {self.name} get() const {{ return handle; }}\n')
            file.write(f'    explicit operator bool() const {{return handle != VK_NULL_HANDLE;}};\n')
            file.write(f'    bool operator!() {{ return handle == VK_NULL_HANDLE; }}\n')
            file.write('};\n')
        else:
            file.write(f'class {self.name[2:]} {{\n')
            file.write(f'    {self.name} handle = VK_NULL_HANDLE;\n')
            file.write(f'    public:\n')
            file.write(f'    {self.name} get() {{ return handle; }}\n')
            file.write(f'    explicit operator bool() const {{return handle != VK_NULL_HANDLE;}};\n')
            file.write(f'    bool operator!() {{ return handle == VK_NULL_HANDLE; }}\n')
            file.write('};\n')
        PlatformGuardFooter(file, self.platform)
    
    def print_static_asserts(self, file):
        if self.alias is None:
            PlatformGuardHeader(file, self.platform)
            if self.dispatchable:
                file.write(f'static_assert( sizeof({self.name[2:]}) == sizeof({self.name}),')
                file.write(f'"Must maintain size between handles");\n')
            else:
                file.write(f'static_assert( sizeof({self.name[2:]}) == sizeof({self.name}),')
                file.write(f'"Must maintain size between handles");\n')
            PlatformGuardFooter(file, self.platform)


class Variable:
    def __init__(self, node, constants, handles, default_values):
        self.name = node.find('name').text
        self.sType_values = node.get('values')

        # attributes
        self.optional = node.get('optional')
        self.len_attrib = node.get('len')

        # type characteristics
        self.is_const = False
        self.is_ptr = False
        self.is_double_ptr = False
        self.is_const_double_ptr = False
        self.array_lengths = []  # multi-dimentional
        self.default_value = None
        self.is_comparable = True

        self.base_type = node.find('type').text
        self.base_type_modified = self.base_type
        if self.base_type_modified[:2] == 'Vk':
            self.base_type_modified = self.base_type_modified[2:]

        if node.find('comment') is not None:
            node.remove(node.find('comment'))

        type_list = ' '.join(node.itertext()).split()

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
            self.is_ptr = True
            cur += 1
        if type_list[cur] == '**':
            self.is_double_ptr = True
            cur += 1
        if type_list[cur] == 'const*':
            self.is_const_double_ptr = True
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
            if arr_len in constants:
                arr_len = arr_len[3:]
            self.array_lengths.append(arr_len)

        if self.base_type in default_values:
            self.default_value = default_values[self.base_type]
        if self.name == 'sType' and self.sType_values is not None:
            self.default_value = f'StructureType::e{MorphVkEnumName(self.sType_values, 3)}'

        self.is_handle = self.base_type in handles

        if self.is_handle or self.is_ptr or self.is_double_ptr or self.is_const_double_ptr:
            self.is_comparable = False

    def get_base_type(self):
        type_decl = ''
        if self.is_const:
            type_decl += 'const '
        type_decl += self.base_type_modified
        if self.is_ptr:
            type_decl += '*'
        if self.is_double_ptr:
            type_decl += '**'
        if self.is_const_double_ptr:
            type_decl += ' const*'
        return type_decl
    
    def get_vk_base_type(self):
        type_decl = ''
        if self.is_const:
            type_decl += 'const '
        type_decl += self.base_type
        if self.is_ptr:
            type_decl += '*'
        if self.is_double_ptr:
            type_decl += '**'
        if self.is_const_double_ptr:
            type_decl += ' const*'
        return type_decl

    def get_init(self):
        init = ''
        if self.is_ptr or self.is_double_ptr:
            init += ' = nullptr'
        elif self.default_value is not None:
            if len(self.array_lengths) > 0:
                init += ' = {}'
            else:
                init += f' = {self.default_value}'
        return init

    def get_base_type_only(self):
        type_decl = self.get_base_type()
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_vk_base_type_only(self):
        type_decl = self.get_vk_base_type()
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_full_type(self, make_const_ref = False):
        type_decl = self.get_base_type() + ' '
        if make_const_ref:
            type_decl += 'const& '
        type_decl += self.name
        for arr in self.array_lengths:
            type_decl += f'[{arr}]'
        return type_decl

    def get_parameter_decl(self, default_init):
        type_decl = self.get_full_type()
        if default_init:
            type_decl += self.get_init()
        return type_decl

    def print_struct_decl(self, file, default_init):
        type_decl = self.get_full_type()
        if default_init:
            type_decl += self.get_init()
        file.write(f'    {type_decl};\n')


class Union:
    def __init__(self, node, constants, handles, default_values):
        self.name = node.get('name')
        self.members = []
        self.platform = None
        self.returnedonly = node.get('returnedonly') is not None
        for member in node.findall('member'):
            self.members.append(Variable(member, constants, handles, default_values))

        self.is_comparable = True
        for member in self.members:
            if not member.is_comparable:
                self.is_comparable = False
                break

    def check_platform(self, platform, ext_types):
        if self.name in ext_types:
            self.platform = platform

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        file.write('union ' + self.name[2:] + ' {\n')
        for member in self.members:
            member.print_struct_decl(file, False)
        if self.is_comparable:
            file.write(f'    constexpr bool operator==({self.name[2:]} const& value) const {{\n')
            file.write('        return ')
            is_first = True
            for member in self.members:
                if is_first:
                    is_first = False
                else:
                    file.write('&& ')
                if len(member.array_lengths) > 0:
                    str_out = ''
                    for l in member.array_lengths:
                        for i in range(0, int(l)):
                            if i > 0 and int(l) > 1 and i < int(l):
                                str_out += ' && '
                            str_out += f'{member.name}[{str(i)}] == value.{member.name}[{str(i)}]'
                        str_out += '\n        '
                    file.write(str_out)
                else:
                    file.write(f'{member.name} == value.{member.name} ')
            file.write(';}\n')
        file.write('};\n')
        PlatformGuardFooter(file, self.platform)
    
    def print_static_asserts(self, file):
        file.write('') # no checks yet

class Struct:
    def __init__(self, node, constants, handles, default_values):
        self.name = node.get('name')
        self.alias = node.get('alias')
        self.members = []
        self.platform = None
        self.returnedonly = node.get('returnedonly') is not None
        self.structextends = node.get('structextends')

        for member in node.findall('member'):
            self.members.append(
                Variable(member, constants, handles, default_values))

        self.is_comparable = True
        for member in self.members:
            if not member.is_comparable:
                self.is_comparable = False
    
    def check_platform(self, platform, ext_types):
        if self.name in ext_types or (self.alias is not None and self.alias in ext_types):
            self.platform = platform

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write(f'using {self.name[2:]} = {self.alias[2:]};\n')
        else:
            file.write(f'struct {self.name[2:]} {{\n')
            for member in self.members:
                member.print_struct_decl(file, True)

            if self.is_comparable:
                file.write(f'    constexpr bool operator==({self.name[2:]} const& other) const = default;\n')
            file.write(f'    operator {self.name} const &() const noexcept {{\n')
            file.write(f'        return *reinterpret_cast<const {self.name}*>(this);\n    }}\n')
            file.write(f'    operator {self.name} &() noexcept {{\n')
            file.write(f'        return *reinterpret_cast<{self.name}*>(this);\n    }}\n')
            file.write('};\n')
        PlatformGuardFooter(file, self.platform)
        
    def print_static_asserts(self, file):
        PlatformGuardHeader(file, self.platform)
        file.write(f'static_assert( sizeof({self.name[2:]}) == sizeof({self.name}), "Must maintain size between types" );\n')
        file.write(f'static_assert( std::is_standard_layout<{self.name[2:]}>::value, "Must be a standard layout type" );\n')
        PlatformGuardFooter(file, self.platform)


class Function:
    def __init__(self, node, constants, handles, dispatchable_handles, default_values):
        self.success_codes = []
        self.error_codes = []
        if node.get('successcodes') is not None:
            self.success_codes = node.get('successcodes').split(',')
        if node.get('errorcodes') is not None:
            self.error_codes = node.get('errorcodes').split(',')

        self.alias = None
        self.return_type = None
        self.platform = None
        proto = node.find('proto')
        if proto is not None:
            self.name = proto.find('name').text
            self.return_type = proto.find('type').text
        else:
            self.name = node.get('name')
            self.alias = node.get('alias')
        
        self.parameters = []
        for param in node.findall('param'):
            self.parameters.append( Variable(param, constants, handles, default_values))
        self.dispatch_type = None
        if len(self.parameters) > 0:
            self.free_function = self.parameters[0].base_type not in dispatchable_handles
            if self.name == 'vkGetInstanceProcAddr':
                self.dispatch_type = None
            elif self.name == 'vkGetDeviceProcAddr':
                self.dispatch_type = "instance"
            elif self.parameters[0].base_type == 'VkInstance' or self.parameters[0].base_type == 'VkPhysicalDevice':  
                self.dispatch_type = "instance"
            elif self.free_function:
                self.dispatch_type = "global"
            else:
                self.dispatch_type = "device"
        if self.name is not None:
            self.func_prototype = "PFN_" + self.name;

    def check_platform(self, platform, ext_functions):
        if self.name in ext_functions:
            self.platform = platform

    def print(self, file, handle=None, indent=''):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write(f'const auto {self.name[2:]} = {self.alias[2:]};\n')
        else:
            if self.return_type == 'VkResult':
                file.write(f'{indent}Result {self.name[2:]}(')
            else:
                file.write(f'{indent}{self.return_type} {self.name[2:]}(')
            is_first = True
            for param in self.parameters[1:] if handle is not None else self.parameters:
                if not is_first:
                    file.write(f',\n{indent}    {param.get_parameter_decl(False)}')
                else:
                    is_first = False
                    file.write(f'\n{indent}    {param.get_full_type(not self.free_function)}')
            file.write(') {\n')

            file.write(f'{indent}    return ')
            if self.return_type == 'VkResult':
                file.write('static_cast<Result>(')
            file.write(f'pfn_{self.name[2:]}(')

            is_first = True
            for param in self.parameters:
                if not is_first:
                    file.write(f',\n{indent}        ')
                else:
                    is_first = False
                    if handle is not None:
                        file.write('get()')
                        continue
                if param.is_handle and not param.is_ptr:
                    file.write(param.name + '.get()')
                elif param.is_ptr:
                    file.write(f'reinterpret_cast<{param.get_vk_base_type_only()}>({param.name})')
                elif param.base_type not in base_type_default_values.keys():
                    file.write(f'static_cast<{param.get_vk_base_type_only()}>({param.name})')
                else:
                    file.write(param.name)
            if self.return_type == 'VkResult':
                file.write(')')
            file.write(');\n')
            file.write(indent + '}\n')

        PlatformGuardFooter(file, self.platform)

    def print_function_def(self, file):
        if self.alias is not None:
            return
        file.write(f'using VKFN_{self.name[2:]} = {self.return_type} (*) (')
        first_param = True
        for param in self.parameters:
            if not first_param:
                file.write(", ")
            else:
                first_param = False
            file.write(param.get_vk_base_type())
        file.write(");\n")

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
        self.functions.extend([func for func in functions if func.name in self.commands])

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
        
def StartPlatformDefBlock(file, name, is_started):
    if not is_started:
        file.write(f'#if defined({name})\n')
        is_started = True
    return is_started

def EndPlatformDefBlock(file, name, is_started):
    if is_started:
        file.write(f'#endif //{name}\n')

class DispatchTable:
    def __init__(self, dispatch_type, name, ext_or_feature_list):
        self.name = name
        self.function_dict = {}
        for ext_or_feature in ext_or_feature_list:
            for require in ext_or_feature.requires: 
                func_dict = {}
                for func in require.functions:
                    if func.dispatch_type == dispatch_type:
                        func_dict[func.name] = func
                if len(func_dict) > 0:
                    if ext_or_feature.name not in self.function_dict:
                        self.function_dict[ext_or_feature.name] = {}
                    self.function_dict[ext_or_feature.name].update(func_dict) 
        
        if dispatch_type == "global":
            self.init_func_sig = 'PFN_vkGetInstanceProcAddr get_instance_proc_addr'
            self.dispatch_handle = ''
            self.gpa = "get_instance_proc_addr"
            self.gpa_val = 'nullptr'
        elif dispatch_type == "instance":
            self.init_func_sig = 'PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance const& instance'
            self.dispatch_handle = '        VkInstance inst = instance.get();\n'
            self.gpa = "get_instance_proc_addr"
            self.gpa_val = 'inst'
        elif dispatch_type == "device":
            self.init_func_sig = 'PFN_vkGetDeviceProcAddr get_device_proc_addr, Device const& device'
            self.dispatch_handle = '        VkDevice dev = device.get();\n'
            self.gpa = "get_device_proc_addr"
            self.gpa_val = 'dev'

    def print(self, file):
        if len(self.function_dict.keys()) == 0:
            return
        if len(self.function_dict.keys()) == 1:
            guard = list(self.function_dict.keys())[0]
            func_list = list(self.function_dict.values())[0]
            PlatformGuardHeader(file, guard)
            file.write('struct ' + self.name + ' {\n')
            file.write('private:\n')
            [ file.write(f'    {func.func_prototype} pfn_{func.name[2:]};\n') for func in func_list.values()]
            file.write('public:\n')
            [ func.print(file, indent='    ') for func in func_list.values()]
            file.write(f'    {self.name}({self.init_func_sig}) {{\n')
            file.write(self.dispatch_handle)
            for func in func_list.values():
                file.write(f'        pfn_{func.name[2:]} = ')
                file.write(f'reinterpret_cast<{func.func_prototype}>({self.gpa}({self.gpa_val},\"{func.name}\"));\n')
            file.write('    };\n};\n')  
            PlatformGuardFooter(file, guard)  
            return
        file.write('struct ' + self.name + ' {\n')
        #function pointers
        file.write('private:\n')
        for feature_name, functions in self.function_dict.items():
            has_element = False
            for func in functions.values():
                has_element = StartPlatformDefBlock(file, feature_name, has_element)
                file.write(f'    {func.func_prototype} pfn_{func.name[2:]};\n')
            EndPlatformDefBlock(file, feature_name, has_element)
        #functions
        file.write('public:\n')
        for feature_name, functions in self.function_dict.items():
            has_element = False
            for func in functions.values():
                has_element = StartPlatformDefBlock(file, feature_name, has_element)
                func.print(file, indent='    ')
            EndPlatformDefBlock(file, feature_name, has_element)
        #constructor
        file.write(f'    {self.name}({self.init_func_sig}) {{\n')
        file.write(self.dispatch_handle)
        for feature_name, functions in self.function_dict.items():
            has_element = False
            for func in functions.values():
                has_element = StartPlatformDefBlock(file, feature_name, has_element)
                file.write(f'        pfn_{func.name[2:]} = ')
                file.write(f'reinterpret_cast<{func.func_prototype}>({self.gpa}({self.gpa_val},\"{func.name}\"));\n')
            EndPlatformDefBlock(file, feature_name, has_element)
        file.write('    };\n};\n')

class BindingGenerator:
    def __init__(self, root):

        self.platforms = {}
        self.macro_defines = []
        self.api_constants = {}
        self.default_values = {}
        self.base_types = []
        self.func_pointers = []
        self.handles = {}
        self.dispatchable_handles = []
        self.enum_dict = {}
        self.flags_dict = {}
        self.bitmask_dict = {}
        self.struct_union_list = []
        self.functions = []
        self.vk_feature_levels = []
        self.ext_list = []
        self.dispatch_tables = []
        
        for platform in root.find('platforms'):
            self.platforms[platform.get('name')] = platform.get('protect')

        for key, value in base_type_default_values.items():
            self.default_values[key] = value

        for enum in root.findall("enums"):
            if enum.attrib.get('name') == "API Constants":
                for constant in enum.iter():
                    api_constant = ApiConstant(constant)
                    if api_constant.name not in ['VK_TRUE', 'VK_FALSE']:
                        self.api_constants[api_constant.name] = api_constant
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
            elif category == 'union':
                self.struct_union_list.append(Union(xml_type, self.api_constants, self.handles, self.default_values))
            elif category == 'struct':
                self.struct_union_list.append(Struct(xml_type, self.api_constants, self.handles, self.default_values))

        #fixup the list so that members using a type appear after that type is defined
        outer_counter = 0
        inner_counter = 0
        while outer_counter < len(self.struct_union_list):
            moved = False
            for m in self.struct_union_list[outer_counter].members:
                inner_counter = outer_counter
                for t2 in self.struct_union_list[outer_counter:]:
                    if m.base_type == t2.name and inner_counter > outer_counter:
                        self.struct_union_list.insert(outer_counter, self.struct_union_list.pop(inner_counter))
                        moved = True
                    inner_counter = inner_counter + 1
            if not moved:
                outer_counter = outer_counter + 1

        # determine which structures are comparable
        for struct_or_union in self.struct_union_list:
            if not struct_or_union.is_comparable:
                continue
            comparable = True
            for member in struct_or_union.members:
                for sub_type in self.struct_union_list:
                    if member.base_type == sub_type.name:
                        if not sub_type.is_comparable:
                            comparable = False
                            break
            struct_or_union.is_comparable = comparable

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
                self.functions.append(
                    Function(command, self.api_constants, self.handles, self.dispatchable_handles, self.default_values)) 

        for ext in root.find('extensions'):
            if ext.tag == 'extension':
                new_ext = Extension(ext, self.platforms)
                if new_ext.supported == 'vulkan':
                    for require in new_ext.requires:
                        require.check_platform(new_ext.platform, self.enum_dict, self.flags_dict, self.bitmask_dict, 
                            self.struct_union_list, self.functions)
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
                            for struct_or_union in self.struct_union_list:
                                if struct_or_union.name == req_type:
                                    self.struct_union_list.remove(struct_or_union)

    
        for feature in root.findall('feature'):
            feat_level = VulkanFeatureLevel(feature)
            for require in feat_level.requires:
                require.fill_enums(self.enum_dict)
                require.fill_bitmasks(self.bitmask_dict)
                require.fill_functions(self.functions)
            self.vk_feature_levels.append(feat_level)

        self.dispatch_tables.append(DispatchTable("global", "GlobalFunctions", self.vk_feature_levels))
        self.dispatch_tables.append(DispatchTable("instance", "InstanceFunctions", self.vk_feature_levels))
        self.dispatch_tables.append(DispatchTable("device", "DeviceFunctions", self.vk_feature_levels))

        for ext in self.ext_list:
            self.dispatch_tables.append(DispatchTable(ext.ext_type, f'{ext.name}_dispatch_table', [ext]))

    def print(self, file):
        [ constant.print(file) for constant in self.api_constants.values() ]
        [ base_type.print(file) for base_type in self.base_types ]
        [ enum.print(file) for enum in self.enum_dict.values()]
        [ bitmask.print(file) for bitmask in self.bitmask_dict.values()]
        file.write(bitmask_flags_macro + '\n')
        [ flag.print(file) for flag in self.flags_dict.values() ]
        [ handle.print(file) for handle in self.handles.values() ]
        [ struct_or_union.print(file) for struct_or_union in self.struct_union_list ]
        [ dispatch_table.print(file) for dispatch_table in self.dispatch_tables ]
 
    def print_string(self, file):
        [ enum.print_string(file) for enum in self.enum_dict.values()]
        [ bitmask.print_string(file) for bitmask in self.bitmask_dict.values()]
        
    def print_static_asserts(self, file):
        [ struct_or_union.print_static_asserts(file) for struct_or_union in self.struct_union_list ]
        [ handle.print_static_asserts(file) for handle in self.handles.values() ]

def main():

    tree = xml.etree.ElementTree.parse('registry/vk.xml')
    root = tree.getroot()

    for tag in root.find('tags'):
        vendor_abbreviations.append(tag.get('name'))

    bindings = BindingGenerator(root)

    with open('include/vkpp.h', 'w') as main_file:
        main_file.write('#pragma once\n')
        main_file.write('// clang-format off\n')
        main_file.write('#include <stdint.h>\n')
        main_file.write('#include <span>\n')
        main_file.write('#define VK_ENABLE_BETA_EXTENSIONS\n')
        main_file.write('#include <vulkan/vulkan.h>\n')
        main_file.write('namespace vk {\n')
        bindings.print(main_file)
        main_file.write('} // namespace vk\n')
        main_file.write('// clang-format on\n')

    with open('include/vkpp_string.h', 'w') as string_helpers:
        string_helpers.write('#pragma once\n')
        string_helpers.write('// clang-format off\n')
        string_helpers.write('#include "vkpp.h"\n')
        string_helpers.write('namespace vk {\n')
        bindings.print_string(string_helpers)
        string_helpers.write('} // namespace vk\n')
        string_helpers.write('// clang-format on\n')
    
    with open('tests/static_asserts.h', 'w') as static_asserts:
        static_asserts.write('#pragma once\n')
        static_asserts.write('// clang-format off\n')
        static_asserts.write('#include "vkpp.h"\n')
        static_asserts.write('#include <type_traits>\n')
        static_asserts.write('namespace vk {\n')
        bindings.print_static_asserts(static_asserts)
        static_asserts.write('} // namespace vk\n')
        static_asserts.write('// clang-format on\n')


if __name__ == "__main__":
    main()
