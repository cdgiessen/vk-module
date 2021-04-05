# What does vulkan.hpp get wrong?

Here I have written up my thoughts on exactly what I think `vulkan.hpp` gets wrong. I understand that so many things influence decisions, so this is not finger pointing or laying blame. It is looking at what currently (as of time of writing) `vulkan.hpp` does and why that specific aspect could be improved.

While not required, it is suggested that reader look through the Application Interface section of the Loader and Layer Interface document.

<https://github.com/KhronosGroup/Vulkan-Loader/blob/master/loader/LoaderAndLayerInterface.md#application-interface-to-the-loader>

1. `vulkan.hpp` tries to be flexible in how it handles loading function pointers for you. I posit that this flexibility hurts more than it helps by creating a multi-step and complex setup process that is very easy to misuse (setup incorrectly) and allows for sub-optimal API usage without complaint. Good API design tries to make it difficult to use the API incorrectly and the easy path is the fast path.

Arguments:

* A.
Context: While the reasons that graphics API's must load function pointers is many, in Vulkan, the `Vulkan-Loader` library (vulkan-1.dll, libvulkan.so) sits between applications and drivers to manages this. The downside is that applications link to the `Vulkan-Loader`, not the driver and thus every Vulkan function must pass through the `Vulkan-Loader` first. What complicates matters is that there are two types of functions in Vulkan, Instance and Device. Instance functions are only implemented by the `Vulkan-Loader` while Device functions are implemented by the drivers. But since applications link to the `Vulkan-Loader`, every Device function called must first pass through the loader. Most of the time an application is calling Device functions, so the extra indirection that is added is non-trivial. Thankfully, the API designers were well aware of such an issue and created the `vkGetDeviceProcAddr` function. It is used to query the *driver's* functions, completely bypassing the `Vulkan-Loader`, leading to 2-5% performance improvement.
The `README.md` (main documentation page) states that providing a `VkDevice` to `vk::DispatchLoaderDynamic` is said to be optional. If you do not not provide a Device, `vulkan.hpp` will have to make all Device functions pass through the `Vulkan-Loader` unnecessarily. Fixing this is only one line of code, but the documentation remarks that its optional. Not adding this line of code leaves 2-5% on the table yet there is no external indication that it is happening, as its all internal to the `vk::DispatchLoaderDynamic`. All the Device functions will work, just slower than they have to. Good API design usually agrees that making the 'good' path the easy path is important, and letting this happen runs counter to that.
