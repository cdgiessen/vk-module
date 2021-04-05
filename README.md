# Charles Custom C++ Vulkan Bindings

My (WIP) C++ bindings for the Vulkan Graphics API. These replace the existing C and C++ headers, so they are completely independent.

## Contents

Currently there are projects

* vk-simple - C++ API that is like the C API with a handful of QoL improvements
* vk-module - (experimental) A Vulkan C++20 Module, and a different take on `vulkan.hpp`

### vk-simple

NOTE: This is unfinished and not suitable for production use. Reasons:

* Doesn't compile because types from system headers aren't handled.
* Not updated to 1.2.170 which added 64 bit flags.
* No test suite to verify code quality. Will need CI setup as well.

Takes the current C headers and adds a few quality of life improvements while staying faithful to the original C API.

Improvements:

* Enums and Bitfields use enum classes, makes it impossible to use the wrong enum.
* sType parameters are initialized to their correct value.
* Structs always initialize all values to zero (except sType). Prevents uninitialized memory bugs.
* Add an API to automatically load function pointers with the following benefits:
  * Function pointers are known to be faster than using the exported Vulkan functions.
  * No compile time dependency on the Vulkan-Loader. It is loaded at runtime instead.
  * Automatically querying function pointers from extensions
  * Removes the need to use an external library such as [volk](https://github.com/zeux/volk) to accomplish this task

Notes:

* This aims to be a production ready solution
* The goal of these bindings is to bridge the gap between the simplicity of the C API and the type safety of `vulkan.hpp`.
* I am not planning on adding additional features, but am open to simple QoL suggestions.

### vk-module

NOTE: This is considered experimental and not suitable for production use.

`vulkan.hpp` offers many useful features while also containing several drawbacks. These bindings are my attempt at creating an expressive and convenient Vulkan interface in C++ while addressing what I consider to be `vulkan.hpp`s shortcomings. While no API is perfect, `vulkan.hpp` is a vast improvement over the C API in developer quality of life and safety, which should not be understated.

The main concerns I have with `vulkan.hpp` are:

1. Poor function pointer loading interface & implementation
2. Slow compile times
3. Lack of (perceived) stability
4. Single file supports multiple C++ standards

None of these are deal breakers and as of writing the `vulkan.hpp` developers are exploring solutions to the most egregious in the list, slow compile times.
For further details about why these are a problem and how I address them, look at the `discussion.md` in the misc folder.

#### Main differences between `vk-module` and `vulkan.hpp`

* C++20 only. No support for older standards. Features like modules, concepts, and three-way comparison aren't behind a macro guard.
* Streamlined function loading interface
  * Only one way to load and use functions which is easier to explain and doesn't have any performance overhead.
  * Supports multi-gpu without changing all the underlying code. (unless you chose to manually include the dispatcher in every function call)
* Use `Expected<T>` for error handling instead of exceptions. Functions which return `VkResult` in the C API now return `Expected<T>` and contain either the desired value or a `vk::Result`
* Independence from the C-API. Types are binary compatible with their C counterparts, allowing the API to work without also including `vulkan.h` first.
  * Because many popular libraries use a C interface, the `vk_module_interop.h` header exists to bridge the gap between the two. Currently it handles conversions between enums, bitfields, and handles.
  * Because of issues with forward declaration, handles are defined in the `vk_module.h` and is the only C API currently required for interop to work.
* Address Sanitizer (ASAN) suppression is built into the API. Some drivers are known to create false positives in ASAN which spam the log with a huge volume of reports. By selectively disabling ASAN before calling into the Vulkan API and then re-enabling it after, `vk-module` eliminates this headache.  
* A much more opinionated API. There should be one way to do something and the API shouldn't be afraid to assert a 'correct' idea of how to use the API. The benefit of this is a smaller API that strives to be self-consistent. The hidden benefit is that the implementation is significantly simpler and shorter. `vulkan.hpp` is well over 90k lines of code, `vk_module.h` is 20k.
* Aim for solutions that give 80% of the benefit at 20% the cost, such as templates. They solve problems but also introduce more compilation overhead, so a conscious effort was made to use alternative solutions when it made sense.

#### Known Issues

* Does not support platform specific WSI related functions. An application must use SDL, GLFW, or equivalent library to create a VkSurfaceKHR
* `Expected<T>` is a homebrew solution and making error handling enjoyable in vulkan is tough. May change this later on
* Dependence on many standard libraries. No plan to remove or change this. Creating replacements for those standard library features just adds possible places for subtle bugs while introduction friction. (Ie, some say this is an issue, but I see the costs outweighing the benefits)
* pNext chains have no helper code. Need to write the StructuredChain replacement.
* API is big, fat, and wide. Very likely there are inconsistencies and errors lurking in the shadows.

## History

Work began on this project in April 2020. These bindings started for 2 main reasons.

* C++20 has just been finalized which contains a new way to manage C++ code, modules.  
* `vulkan.hpp` is probably the vulkan tool/project which almost everyone knows about and has the biggest range of opinions, from staunch supporters to dug-in detractors.

The discussion in various online chat groups led me to believe there may be a way to kill two birds with one stone, write C++20 module that are better Vulkan C++ bindings.

With that in mind, Work began on this project in April 2020. Over the spring and summer, the `generator.py` script was written to parse `vk.xml` and generate the `vk-module` bindings. It was a great learning project as it involved exploring python in detail and the xml document.

As the project currently stands (April 2021), I didn't know how wrong I was. Firstly, modules are still experimental or very recently released in C++20 compilers. Suffice to say, they aren't ready for primetime. Secondly, `vulkan.hpp`'s problems are SIGNIFICANTLY more complicated than I could of imagined. There are many concerns the developers must balance: performance, safety, implementation complexity, interface simplicity, interoperability with the C API, then finding out just how little room there is to work with. Not to mention the moving target that is `vk.xml` which changes and breaks previous assumptions about what the bindings API design space is. This isn't to say these challenges aren't insurmountable, but is incredibly difficult to find a balance that doesn't leave me defeated in some aspect.
