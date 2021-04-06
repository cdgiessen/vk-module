# What does vulkan.hpp get wrong?

Here I have written up my thoughts on exactly what I think `vulkan.hpp` gets wrong. I understand that so many things influence decisions, so this is not finger pointing or laying blame. It is looking at what currently (as of time of writing) `vulkan.hpp` does and why that specific aspect could be improved.

While not required, it is suggested that reader look through the Application Interface section of the Loader and Layer Interface document.

<https://github.com/KhronosGroup/Vulkan-Loader/blob/master/loader/LoaderAndLayerInterface.md#application-interface-to-the-loader>


## Function pointer loading and dispatching

`vulkan.hpp` tries to be flexible in how it handles loading function pointers for you. I posit that this flexibility hurts more than it helps by creating a multi-step and complex setup process that is very easy to misuse (setup incorrectly) and allows for sub-optimal API usage without knowing. The API also makes adding multi-gpu support much more arduous than with my approach.

Context: While the reasons that graphics API's must load function pointers is many, in Vulkan, the `Vulkan-Loader` library (vulkan-1.dll, libvulkan.so) sits between applications and drivers to manages this. The downside is that applications link to the `Vulkan-Loader`, not the driver and thus every Vulkan function must pass through the `Vulkan-Loader` first. What complicates matters is that there are two types of functions in Vulkan, Instance and Device. Instance functions are only implemented by the `Vulkan-Loader` while Device functions are implemented by the drivers. But since applications link to the `Vulkan-Loader`, every Device function called must first pass through the loader. Most of the time an application is calling Device functions, so the extra indirection that is added is non-trivial. Thankfully, the API designers were well aware of such an issue and created the `vkGetDeviceProcAddr` function. It is used to query the *driver's* functions, completely bypassing the `Vulkan-Loader`, leading to 2-5% performance improvement.

Arguments:

The `README.md` (main documentation page) states that providing a `VkDevice` to `vk::DispatchLoaderDynamic` is optional. If you do not not provide a Device, `vulkan.hpp` will have to make all Device functions pass through the `Vulkan-Loader` unnecessarily. Fixing this is only one line of code (giving the dispatcher a VkDevice). Not adding this line of code leaves 2-5% on the table yet there is no external indication that it is happening, as its all internal to `vk::DispatchLoaderDynamic`. Every Device function will work, just slower than they have to. One aspect of good API design is the 'happy pit' where doing the easy thing is the right thing, and its hard to do the wrong (slow) thing. Yet `vulkan.hpp` is fine with letting users unknowingly do so.

The default way users use the dispatcher in `vulkan.hpp` is through a very convenient helper called the `VULKAN_HPP_DEFAULT_DISPATCHER` which is globally available to of `vulkan.hpp`. I can't disagree that this is more convenient for the vast majority of users because they do not have to remember to add a `vk::DispatchLoaderDynamic` to the end of every Vulkan function. But if you need multi-gpu support, you leave this happy path. Now each and every vulkan call must have the dispatcher parameter added at the end, and plumb that dispatcher through the codebase to make it accessible. I admit this isn't a "hard" argument against the current mechanism, multi-gpu support in applications is not common. But for bindings that are designed to be useable by everyone, this is very obnoxious code pattern which sacrifices some users for everyone elses benefit.

My solution is to create user visible Dispatcher objects for each dispatchable handle (Instance, PhysicalDevice, Device, Queue, and CommandBuffer). They are constructed with their handle and the parent Dispatcher. The `DynamicLibrary` loads `Vulkan-Loader` to kick off function loading. The Dispatcher for `VkInstance` is `InstanceFunctions` (IF). Every instance function is now a member function on the IF. Each dispachable handle has a `{HandleName}Functions` object. Creating the `PhysicalDeviceFunctions` (PDF) takes the `PhysicalDevice` (PD) handle and the IF. Creating a `VkDevice` needs only a PD but creating the `DeviceFunctions` (DF) need the `VkDevice` *and* the IF because `vkGetDeviceProcAddr` is an Instance function and is required. I may make it possible to use a PDF in the future for consistency. Then with a DF, creating a `QueueFunctions` and `CommandBuffersFunctions` with a DF and their respective handles is last. Generally, the functions struct could be put in an easily accessible place and/or pass it by reference.  

Example init code using this style
```c++
struct RenderContext
{
    vk::DynamicLibrary vulkan_library; //keeps the vulkan-1.dll alive
    vk::InstanceFunctions instance_functions;
    vk::DeviceFunctions device_functions; 
};

void InitRenderContext(RenderContext& context){
    // Allow loading to fail, in case the app wants to make vulkan support optional
    if (context.vulkan_library.init() != vk::Result::Success) { /* handle error */ }
    
    // GlobalFunctions is a local variable because we don't store it long term
    vk::GlobalFunctions global_functions = vk::GlobalFunctions(context.vulkan_library);
    
    // Call enumerate layers/extensions/versions & initialize instance create info

    auto [instance, instance_ret] = global_functions.CreateInstance(inst_info);
    if (!instance_ret) { /* handle error */ }

    context.instance_functions = vk::InstanceFunctions(global_functions, instance)
    
    auto [physical_devices, physical_devices_ret] = context.instance_functions.EnumeratePhysicalDevices();
    
    // Choose a physical device & setup device_info

    auto [device, device_ret] = context.instance_functions.CreateDevice(device_info);
    if (!device_ret) { /* handle error */ }

    context.device_functions = vk::DeviceFunctions(instance_functions, device);

    // Now can use all device functions by passing around a `DeviceFunctions` object
    context.device_functions.SomeVulkanFunction(paramA, paramB, ...) //don't have to pass Device or Dispatcher object

    // Or put it in a global and make it easily accessible. Multi-gpu is not possible, but at least
    // the only thing to change is passing in a `DeviceFunctions` and 
}

void DestroyContext(RenderContext& context) {
    // Instance and Device have 0 parameter destroy functions since the handle is stored in the struct
    context.device_functions.DestroyDevice();
    context.instance_functions.DestroyInstance();
}

```

The benefit of my solution is to always make the fact that you are calling function pointers explicit and make it easy to call vulkan functions from a specific Dispatcher instead of a global one. That way adding multi-gpu wont involve shoving an extra parameter into each vulkan function call made.

I also would like to think this makes the whole function loading process much more user friendly. The current instruction for `vulkan.hpp` either shows how to create a `vk::DispatchLoaderDynamic` to pass around, or demonstrates how to create a global `vk::DispatchLoaderDynamic`. The former is rather straightforward, and mirrors my initialization (save for how `vkGetInstanceProcAddr` is gotten). The latter option on the other hand isn't so simple. First, one must add `#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1` before including the header.
```c++
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>
```
Now you have to give storage for the dispatcher. Yes, its just as simple as putting the following statement in the code. No, its not clear that this is defining a global variable that `vulkan.hpp` accesses. Yes, it must appear only once.
```c++
//Put this in only one place, so not in a header file.
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE
```
Next, we need a `vk::DynamicLibrary` in which to get the `vkGetInstanceProcAddr` manually. Mind you, the `vk::DynamicLibrary` should not be a local variable because when the local function exits, the `Vulkan-Loader` will unload. Yet the documentation puts it in what appears to be a function. More than once I've seen users not know that and get bitten. With a `vk::DynamicLibrary` Then we can initialize the `VULKAN_HPP_DEFAULT_DISPATCHER`'s global functions by loading `vkGetInstanceProcAddr` from it.
```c++
vk::DynamicLoader dl;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = dl.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr");
VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);
```
Then follows instance creation and can load all the Instance functions.
```c++
vk::Instance instance = vk::createInstance({}, nullptr);
VULKAN_HPP_DEFAULT_DISPATCHER.init(instance);
```
Lastly, we can initialize the Device functions
```c++
vk::Device device = physicalDevices.createDevice({}, nullptr);
VULKAN_HPP_DEFAULT_DISPATCHER.init(device);
```
Note, this is listed as optional. I have described why it shouldn't be optional above, so I won't rehash it.

The things I want to point out is that the process of setting up the dispatcher with `vulkan.hpp` requires setting 2 macro defines, manually get the `vkGetInstanceProcAddr` from it, not unloading `vk::DynamicLibrary`, and then initializing the dispatcher with 2 required function calls, and 1 optional one. Interspersed with that is creating an instance and a device.

Constrast this with how I have users create a `vk::DynamicLibrary` (which also shouldn't be a local variable), create a `GlobalFunctions` (GF) object with it, create an instance from GF and then `InstanceFunctions` (IF), create a Device, and finally a `DeviceFunctions` from the Device and IF. There is an explicit setup process, one cannot create a Device without the required steps before it, and the code tells you the order explicitly.

Is my solution more performant and safe? No, both will call function pointers using member functions. I would like to think its more safe as you 'construct' the Function structs with the required arguments. However to make it placeable in static/global contexts I had to add default constructors, which means the structs aren't inherently safe by construction.

TODO: clarify why separating handles and function tables.
Putting member functions in the handle structs directly constrains the implementation because of the desire to not make the size of `Device` massive (sizeof(`VkDevice`) + ~100 function pointers).

## Compile times

This is a common complaint about `vulkan.hpp`. Its pretty self explanatory. Additionally, the developers are well aware of this, and are looking at C++20 modules as a possible long term solution. If the file could be split into header and implementation, that would help but I recognize that improving compile times is more art than science.

## Stability

One of the biggest issues people have had with is `vulkan.hpp` breaking user code when updating. I would suggest that since the start of 2020, it has been much better. SDK's aren't shipping with headers that don't compile, and in general the stewardship of the project I feel is better than some people give credit. However, trust is easy to lose and hard to gain. Saying "I promise I will do better next time" after 2-3 time dealing with updating and realizing that vulkan.hpp is wrong or changed the interface somehow is not enough.

I recognize that code quality is very difficult, and C++ exacerbates it. I do not feel I can create a new library to use instead of `vulkan.hpp` and then spend 2-3 years finding all the corner cases and bugs my initial implementation missed. That isn't an improvement over the original, it is in fact a regression. Library development in C++ is pretty much an expert level activity, and I recognize that while I can reason about the code in isolation pretty well, I lack a lot of experience in writing code. If you were hoping I would state "My solution is better because X" then you will be disappointed. I have spent over a hear hacking away at this project and found this problem is impossible to 'solve'. I cannot in good faith make false claims.

## Single file supports multiple C++ standards

Less of a gripe, more of a 'Breaking backwards compatibility' is nice statement.
If they could put every standard version into its own header, they would. But `vulkan.hpp` can live in a system wide include path, there would have to be named distinctly, and that isn't very nice. `vulkan.hpp` has a lot of 'use C++X features when possible, fallback when not' which makes reading the source code difficult, and no doubt complicates the generation of the code. That is multiplied by the various ENHANCED_MODE and other configuration macros.