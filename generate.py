

import xml.etree.ElementTree
import re

'''
todo list

handles are a thing, decide what to do
make flags and flag bits separate // separate, but more scaffolding needed
deal with aliases?
member arrays (+ vk constants -> int's)
variables with bitfields

extensions -- need to be gotten from 'features'
functions -- basic
variables with double arrays eg [3][4]
platform specific entities - done: struct, union, function
dispatchable handles (instance, physdevice, device, queue, command buffer)

Done: enum/flags with members from extensions (need 'features' stuff)
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
    'size_t': '0',
    'bool': 'false'
}


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


def PlatformGuardHeader(file, guard):
    if guard is not None:
        file.write('#if defined({})\n'.format(guard))


def PlatformGuardFooter(file, guard):
    if guard is not None:
        file.write('#endif // {}\n'.format(guard))


def EnumExtValue(ext_num, offset, direction):
    enum_value = 1000000000 + 1000 * (ext_num - 1) + offset
    if direction == '-':
        enum_value = -enum_value
    return enum_value


class Enum:
    class Value:
        def __init__(self, vk_name, enum_name_len, value):
            self.vk_name = vk_name
            self.name = MorphVkEnumName(vk_name, enum_name_len)
            self.value = value

    def __init__(self, node, ext_enums):
        self.vk_name = node.get('name')  # for internal use
        self.name = node.get('name')[2:]  # for output
        self.alias = node.get('alias')
        if self.alias is not None:
            self.alias = self.alias[2:]
            return
        if node.tag == 'type':
            return  # forward declaration

        enum_name_len = len(re.findall('[A-Z][^A-Z]+', self.vk_name))
        if self.vk_name == 'VkResult':
            enum_name_len = 1

        self.values = []
        for elem in node:
            if elem.get('name') is not None and elem.get('value') is not None:
                self.values.append(Enum.Value(
                    elem.get('name'), enum_name_len, elem.get('value')))

        if self.vk_name in ext_enums:
            for ext_enum in ext_enums[self.vk_name]:
                self.values.append(Enum.Value(
                    ext_enum.name, enum_name_len, ext_enum.value))

    def print(self, file):
        if self.alias is not None:
            file.write('using ' + self.name + ' = ' + self.alias + ';\n')
        elif hasattr(self, 'values'):
            file.write('enum class ' + self.name + ' {\n')
            for elem in self.values:
                file.write("    e" + elem.name + ' = ' +
                           str(elem.value) + ",\n")
            file.write('};\n')


class Bitmask:
    class Value:
        def __init__(self, vk_name, bitmask_name_len):
            self.vk_name = vk_name
            self.name = MorphVkEnumName(vk_name, bitmask_name_len)

    def __init__(self, node, ext_bitmasks):
        self.vk_name = node.get('name')
        self.name = self.vk_name[2:]
        self.values = {}
        self.alias = None
        bitmask_name_len = len(re.findall('[A-Z]+[^A-Z]*', self.vk_name)) - 2

        for elem in node:
            value = elem.get('value')
            if elem.get('bitpos') is not None:
                value = str(1 << int(elem.get('bitpos')))
            elif elem.get('alias') is not None:
                value = 'e' + \
                    MorphVkEnumName(elem.get('alias'), bitmask_name_len)
            self.values[value] = Bitmask.Value(
                elem.get('name'), bitmask_name_len)

        if self.vk_name in ext_bitmasks:
            for ext_bitmask in ext_bitmasks[self.vk_name]:
                self.values[str(1 << ext_bitmask.bitpos)] = Bitmask.Value(
                    ext_bitmask.name, bitmask_name_len)

    def print(self, file):
        if self.alias is not None:
            file.write('using ' + self.name + ' = ' + self.alias + ';\n')
        else:
            file.write('enum class ' + self.name + ': uint32_t {\n')
            for bitpos, elem in self.values.items():
                file.write("    e" + elem.name + ' = ' + bitpos + ",\n")
            file.write('};\n')


class Flags:
    def __init__(self, node):
        self.vk_name = node.get('name')
        self.name = None
        self.values = []
        self.alias = None

        if node.find('name') is not None:
            self.name = node.find('name').text[2:]
        else:
            self.name = node.get('name')[2:]
            self.alias = node.get('alias')[2:]

    def print(self, file):
        file.write('using ' + self.name + ' = uint32_t;\n')


class ApiConstant:
    def __init__(self, node):
        self.vk_name = node.get('name')
        self.name = node.get('name')[3:]
        self.value = node.get('value')
        self.alias = node.get('alias')

    def print(self, file):
        if self.value is not None:
            file.write('constexpr size_t ' + self.name +
                       ' = ' + self.value + ';\n')
        if self.alias is not None:
            file.write('constexpr auto ' + self.name +
                       ' = ' + self.alias[3:] + ';\n')


class Handle:
    def __init__(self, node):
        self.name = None
        if node.find('name') is not None:
            self.vk_name = node.find('name').text
            self.name = self.vk_name[2:]
            if node.find('type').text == 'VK_DEFINE_HANDLE':
                self.dispatchable = True
            elif node.find('type').text == 'VK_DEFINE_NON_DISPATCHABLE_HANDLE':
                self.dispatchable = False
            self.parent = node.get('parent')
        self.alias = node.get('alias')
        if self.alias is not None:
            self.vk_name = node.get('name')
            self.name = self.vk_name[2:]


class DispatchHandle:
    def __init__(self, handle):
        self.vk_name = handle.vk_name
        self.name = handle.name
        self.functions = []

    def print(self, file):
        file.write('struct ' + self.name + ' {\n')
        file.write('    ' + self.vk_name + ' handle;\n')
        file.write('    ' + self.vk_name + ' get() { return handle; }\n')
        for function in self.functions:
            function.print(file, self, '    ')
        file.write('};\n')


class NonDispatchHandle:
    def __init__(self, handle):
        self.vk_name = handle.vk_name
        self.name = handle.name

    def print(self, file):
        file.write('class ' + self.name + ' {\n')
        file.write('   ' + self.vk_name + ' handle = VK_NULL_HANDLE;\n')
        file.write('   public:\n')
        file.write('   ' + self.vk_name + ' get() { return handle; }\n')
        file.write('};\n')


class HandleAlias:
    def __init__(self, handle):
        self.vk_name = handle.vk_name
        self.name = handle.name
        self.alias = handle.alias

    def print(self, file):
        file.write('using ' + self.name +
                   ' = ' + self.alias[2:] + ';\n')


class Variable:
    def __init__(self, node, constants, handles, default_values):
        self.name = node.find('name').text
        self.sType_values = node.get('values')
        self.is_opt = node.get('optional')
        self.len_mem_name = node.get('len')
        self.noautovalidity = node.get('noautovalidity')
        self.array_length = None
        self.default_value = None

        edited_node = node
        if edited_node.find('comment') is not None:
            edited_node.remove(edited_node.find('comment'))

        type_text = ''.join(edited_node.itertext())

        array_len = node.find('enum')
        if array_len is not None:
            self.array_length = array_len.text

        bracket_contents = re.search('(?<=\\[)[a-zA-Z0-9_]+(?=\\])', type_text)
        if bracket_contents is not None:
            self.array_length = bracket_contents.string[bracket_contents.start(
            ):bracket_contents.end()]
        if self.array_length in constants:
            self.array_length = self.array_length[3:]
        self.is_ptr = False
        for t in edited_node.itertext():
            if '*' in t:
                self.is_ptr = True

        self.vk_base_type = node.find('type').text
        self.base_type = self.vk_base_type
        if self.vk_base_type[:2] == 'Vk':
            self.base_type = self.base_type[2:]

        if self.base_type == 'Bool32':
            self.base_type = 'bool'
        if self.base_type in default_values:
            self.default_value = default_values[self.base_type]
        if self.name == 'sType' and self.sType_values is not None:
            self.default_value = 'StructureType::e' + \
                MorphVkEnumName(self.sType_values, 3)

        self.is_handle = self.vk_base_type in handles

    def get_base_type_decl(self):
        type_decl = self.vk_base_type
        if self.is_ptr:
            type_decl += '*'
        if self.array_length is not None:
            type_decl += '[' + self.array_length + ']'
        return type_decl

    def get_decl(self, default_init):
        type_decl = self.base_type
        if self.is_ptr:
            type_decl += '*'
        type_decl += ' ' + self.name
        if self.array_length is not None:
            type_decl += '[' + self.array_length + ']'
        if default_init:
            if self.is_ptr:
                type_decl += ' = nullptr'
            elif self.default_value is not None:
                if self.array_length is not None:
                    type_decl += ' = {}'
                else:
                    type_decl += ' = ' + self.default_value
        return type_decl

    def print_decl(self, file, default_init):
        type_decl = self.get_decl(default_init)

        file.write('    ' + type_decl + ';\n')


class Union:
    def __init__(self, node, constants, handles, default_values, ext_types):
        self.vk_name = node.get('name')
        self.name = node.get('name')[2:]
        self.platform = None
        if self.vk_name in ext_types:
            self.platform = ext_types[self.vk_name].platform_def
        self.members = []
        for member in node.findall('member'):
            self.members.append(
                Variable(member, constants, handles, default_values))

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        file.write('union ' + self.name + ' {\n')
        for member in self.members:
            member.print_decl(file, False)
        file.write('};\n')
        PlatformGuardFooter(file, self.platform)


class Struct:
    def __init__(self, node, constants, handles, default_values, ext_types):
        self.vk_name = node.get('name')
        self.name = node.get('name')[2:]
        self.alias = node.get('alias')
        self.members = []
        self.platform = None
        if self.vk_name in ext_types and self.alias is None:
            self.platform = ext_types[self.vk_name].platform_def
        elif self.alias in ext_types:
            self.platform = ext_types[self.alias].platform_def

        for member in node.findall('member'):
            self.members.append(
                Variable(member, constants, handles, default_values))

    def print(self, file):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write('using ' + self.name + ' = ' + self.alias[2:] + ';\n')
        else:
            file.write('struct ' + self.name + ' {\n')
            for member in self.members:
                member.print_decl(file, True)
            file.write('};\n')
        PlatformGuardFooter(file, self.platform)


class Function:
    def __init__(self, node, constants, handles, default_values, ext_functions):
        self.success_codes = []
        self.error_codes = []
        if node.get('successcodes') is not None:
            self.success_codes = node.get('successcodes').split(',')
        if node.get('errorcodes') is not None:
            self.error_codes = node.get('errorcodes').split(',')

        self.alias = None
        proto = node.find('proto')
        if proto is not None:
            self.vk_name = proto.find('name').text
            self.name = proto.find('name').text[2:]
            self.return_type = proto.find('type').text
        else:
            self.vk_name = node.find('name')
            self.name = node.get('name')[2:]
            self.alias = node.get('alias')
        self.platform = None
        if self.vk_name in ext_functions:
            self.platform = ext_functions[self.vk_name].platform_def

        self.parameters = []
        for param in node.findall('param'):
            self.parameters.append(
                Variable(param, constants, handles, default_values))

    def print(self, file, handle, indent=''):
        PlatformGuardHeader(file, self.platform)
        if self.alias is not None:
            file.write('const auto ' + self.name +
                       ' = ' + self.alias[2:] + ';\n')
        else:
            file.write(indent + self.return_type + ' ' + self.name + '(')
            is_first = True
            for param in self.parameters[1:] if handle is not None else self.parameters:
                if not is_first:
                    file.write(',' + indent)
                else:
                    is_first = False
                file.write('\n' + indent + '    ' + param.get_decl(False))
            file.write(') {\n')
            file.write(indent + '    return ' + self.vk_name + '(')

            is_first = True
            for param in self.parameters:
                if not is_first:
                    file.write(',')
                else:
                    is_first = False
                    if handle is not None:
                        file.write('get()')
                        continue
                if param.is_handle and not param.is_ptr:
                    file.write(param.name + '.get()')
                else:
                    if param.is_ptr:
                        file.write(' reinterpret_cast<')
                    else:
                        file.write(' static_cast<')
                    file.write(param.get_base_type_decl() +
                               '>(' + param.name + ')')
            file.write(');\n')
            file.write(indent + '}\n')

        PlatformGuardFooter(file, self.platform)


class ExtEnum:
    def __init__(self, name, value, extends):
        self.name = name
        self.value = value
        self.extends = extends


class ExtBitmask:
    def __init__(self, name, bitpos, extends):
        self.name = name
        self.bitpos = bitpos
        self.extends = extends


class Extension:
    def __init__(self, node, platforms):
        self.name = node.get('name')
        self.ext_num = int(node.get('number'))
        self.ext_type = node.get('type')
        self.supported = node.get('supported')
        self.requires = node.get('requires')
        self.types = []
        self.functions = []
        self.constants = {}
        self.enum_values = []
        self.bitmask_values = []
        self.platform_def = None
        if node.get('platform') in platforms:
            self.platform_def = platforms[node.get('platform')]

        for requires in node.findall('require'):
            for e_type in requires.findall('type'):
                self.types.append(e_type.get('name'))
            for function in requires.findall('command'):
                self.functions.append(function.get('name'))

            for enum in requires.findall('enum'):
                extends = enum.get('extends')
                name = enum.get('name')
                value = enum.get('value')
                bitpos = enum.get('bitpos')
                offset = enum.get('offset')

                if value is None and bitpos is not None:
                    value = 1 << int(bitpos)

                if offset is not None:
                    offset = int(offset)
                if extends is not None:
                    if offset is not None:
                        enum_value = EnumExtValue(
                            self.ext_num, offset, enum.get('dir'))
                        self.enum_values.append(
                            ExtEnum(name, enum_value, extends))
                    elif bitpos is not None:
                        self.bitmask_values.append(
                            ExtBitmask(name, int(bitpos), extends))
                else:
                    self.constants[name] = value


class FuncPointer:
    def __init__(self, node):
        self.name = node.find('name').text
        self.text = ''
        for t in node.itertext():
            self.text += t

    def print(self, file):
        file.write(self.text + '\n')


class BaseType:
    def __init__(self, node):
        self.name = node.find('name').text[2:]
        self.type = node.find('type').text
        if self.type in base_type_default_values:
            self.default_value = base_type_default_values[self.type]

    def print(self, file):
        file.write('using ' + self.name + ' = ' + self.type + ';\n')


class BindingGenerator:
    def __init__(self, root):

        self.platforms = {}
        self.macro_defines = []
        self.api_constants = {}
        self.default_values = {}
        self.base_types = []
        self.func_pointers = []
        self.handles = []
        self.dispatchable_handles = {}
        self.non_dispatchable_handles = {}
        self.alias_handle_list = []
        self.enum_list = []
        self.bitmask_list = []
        self.flags_list = []
        self.union_list = []
        self.struct_list = []
        self.functions = []
        self.free_functions = []
        self.ext_list = []
        self.ext_enums = {}
        self.ext_bitmasks = {}
        self.ext_types = {}
        self.ext_functions = {}

        for platform in root.find('platforms'):
            self.platforms[platform.get('name')] = platform.get('protect')

        for key, value in base_type_default_values.items():
            self.default_values[key] = value

        for ext in root.find('extensions'):
            if ext.tag == 'extension':
                extension = Extension(ext, self.platforms)
                self.ext_list.append(extension)
                for enum in extension.enum_values:
                    if enum.extends not in self.ext_enums:
                        self.ext_enums[enum.extends] = []
                    self.ext_enums[enum.extends].append(enum)
                for bitmask in extension.bitmask_values:
                    if bitmask.extends not in self.ext_bitmasks:
                        self.ext_bitmasks[bitmask.extends] = []
                    self.ext_bitmasks[bitmask.extends].append(bitmask)
                for item in extension.types:
                    self.ext_types[item] = extension
                for item in extension.functions:
                    self.ext_functions[item] = extension

        for feature in root.findall('feature'):
            for require in feature.findall('require'):
                for r_enum in require.findall('enum'):
                    name = r_enum.get('name')
                    extends = r_enum.get('extends')
                    ext_num = r_enum.get('extnumber')
                    offset = r_enum.get('offset')
                    value = r_enum.get('value')
                    bitpos = r_enum.get('bitpos')
                    if offset is not None:
                        offset = int(offset)
                    if extends is not None:
                        if extends not in self.ext_enums:
                            self.ext_enums[extends] = []
                        if offset is not None:
                            enum_value = EnumExtValue(
                                int(ext_num), offset, r_enum.get('dir'))
                            self.ext_enums[extends].append(
                                ExtEnum(name, enum_value, extends))
                        elif value is not None:  # core enums
                            self.ext_enums[extends].append(
                                ExtEnum(name, value, extends))
                        elif bitpos is not None:
                            if extends not in self.ext_bitmasks:
                                self.ext_bitmasks[extends] = []
                            self.ext_bitmasks[extends].append(
                                ExtBitmask(name, int(bitpos), extends))
                    else:
                        api_constant = ApiConstant(r_enum)
                        self.api_constants[api_constant.vk_name] = api_constant

        for enum in root.findall("enums"):
            if enum.attrib.get('name') == "API Constants":
                for constant in enum.iter():
                    api_constant = ApiConstant(constant)
                    if api_constant.vk_name not in ['VK_TRUE', 'VK_FALSE']:
                        self.api_constants[api_constant.vk_name] = api_constant

        for enum in root.findall("enums"):
            if enum.get('type') == 'enum':
                e = Enum(enum, self.ext_enums)
                self.enum_list.append(e)
                self.default_values[e.name] = str('static_cast<'+e.name+'>(0)')

            elif enum.get('type') == 'bitmask':
                b = Bitmask(enum, self.ext_bitmasks)
                self.bitmask_list.append(b)
                self.default_values[b.name] = str('static_cast<'+b.name+'>(0)')

        for xml_type in root.find('types'):
            category = xml_type.get('category')
            if category == 'define':
                self.macro_defines.append(MacroDefine(xml_type))
            elif category == 'basetype':
                base_type = BaseType(xml_type)
                self.base_types.append(base_type)
                self.default_values[base_type.name] = base_type.default_value
            elif category == 'funcpointer':
                self.func_pointers.append(FuncPointer(xml_type))
            elif category == 'enum':
                self.enum_list.append(Enum(xml_type, self.ext_enums))
            elif category == 'bitmask':
                f = Flags(xml_type)
                self.flags_list.append(f)
                self.default_values[f.name] = str('static_cast<'+f.name+'>(0)')
            elif category == 'handle':
                handle = Handle(xml_type)
                self.handles.append(handle.vk_name)
                if handle.alias is not None:
                    self.alias_handle_list.append(HandleAlias(handle))
                elif handle.dispatchable:
                    self.dispatchable_handles[handle.vk_name] = DispatchHandle(
                        handle)
                elif not handle.dispatchable:
                    self.non_dispatchable_handles[handle.vk_name] = NonDispatchHandle(
                        handle)
            elif category == 'union':
                self.union_list.append(
                    Union(xml_type, self.api_constants, self.handles, self.default_values, self.ext_types))
            elif category == 'struct':
                self.struct_list.append(
                    Struct(xml_type, self.api_constants, self.handles, self.default_values, self.ext_types))

        for commands in root.findall('commands'):
            for command in commands.findall('command'):
                self.functions.append(
                    Function(command, self.api_constants, self.handles, self.default_values, self.ext_functions))

        for func in self.functions:
            if len(func.parameters) > 0 and func.parameters[0].vk_base_type in self.dispatchable_handles:
                self.dispatchable_handles[func.parameters[0].vk_base_type].functions.append(
                    func)
            else:
                self.free_functions.append(func)

    def print(self, file):
        for macros in self.macro_defines:
            macros.print(file)
        for constant in self.api_constants.values():
            constant.print(file)
        for base_type in self.base_types:
            base_type.print(file)
        # for func_pointer in self.func_pointers:
        #    func_pointer.print(file)
        for enum in self.enum_list:
            enum.print(file)
        for bitmask in self.bitmask_list:
            bitmask.print(file)
        for flags in self.flags_list:
            flags.print(file)
        for handle in self.non_dispatchable_handles.values():
            handle.print(file)
        for handle in self.alias_handle_list:
            handle.print(file)
        for union in self.union_list:
            union.print(file)
        for struct in self.struct_list:
            struct.print(file)
        for function in self.free_functions:
            function.print(file, None)
        for handle in self.dispatchable_handles.values():
            handle.print(file)


def main():
    tree = xml.etree.ElementTree.parse(
        'external/Vulkan-Headers/registry/vk.xml')
    root = tree.getroot()

    for tag in root.find('tags'):
        vendor_abbreviations.append(tag.get('name'))

    bindings = BindingGenerator(root)

    file = open('include/vk-binding.h', 'w')
    file.write('#pragma once\n')
    file.write('// clang-format off\n')
    file.write('#include <cstdint>\n')
    file.write('#include <vulkan/vulkan.h>\n')
    file.write('namespace vk {\n')
    bindings.print(file)
    file.write('} // namespace vk\n')
    file.write('// clang-format on\n')
    file.close()


if __name__ == "__main__":
    main()
