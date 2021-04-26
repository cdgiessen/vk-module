/*
 * Copyright 2021 Charles Giessen (cdgiessen@gmail.com)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
// clang-format off
#include "vulkan.h"


#if defined(_WIN32)
    using HINSTANCE = struct HINSTANCE__ *;
    #if defined( _WIN64 )
    using FARPROC = int64_t( __stdcall * )();
    #else
    using FARPROC = typedef int( __stdcall * )();
    #endif
    extern "C" __declspec( dllimport ) HINSTANCE __stdcall LoadLibraryA( char const * lpLibFileName );
    extern "C" __declspec( dllimport ) int __stdcall FreeLibrary( HINSTANCE hLibModule );
    extern "C" __declspec( dllimport ) FARPROC __stdcall GetProcAddress( HINSTANCE hModule, const char * lpProcName );
#elif defined(__linux__) || defined(__APPLE__)
    #include <dlfcn.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
void *library = nullptr;
#elif defined(_WIN32)
::HINSTANCE library = nullptr;
#endif

void* LibraryLoadFunction(const char* name) {
#if defined(__linux__) || defined(__APPLE__)
    return dlsym(library, name);
#elif defined(_WIN32)
    return ::GetProcAddress(library, name);
#endif
}
void LoadGetInstanceProcAddr(){
    vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(LibraryLoadFunction("vkGetInstanceProcAddr"));
}
void LoadGlobalFunctions() {
    if (vkGetInstanceProcAddr == VK_NULL_HANDLE) return;
    vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkCreateInstance"));
    vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceExtensionProperties"));
    vkEnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceLayerProperties"));
    vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(vkGetInstanceProcAddr(VK_NULL_HANDLE, "vkEnumerateInstanceVersion"));
}

VkResult vkInitializeLoaderLibrary(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr){
    if(pfn_vkGetInstanceProcAddr != VK_NULL_HANDLE){
        vkGetInstanceProcAddr = pfn_vkGetInstanceProcAddr;
        LoadGlobalFunctions();
        return VkResult::Success;
    }

#if defined(__linux__)
    library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
    if (!library) library = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
    library = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
#elif defined(_WIN32)
    library = ::LoadLibraryA("vulkan-1.dll");
#endif
    if (library == 0) return VkResult::ErrorInitializationFailed;
    LoadGetInstanceProcAddr();
    LoadGlobalFunctions();
    if (vkGetInstanceProcAddr == nullptr) return VkResult::ErrorInitializationFailed;
    return VkResult::Success;
}

void vkCloseLoaderLibrary(){
    if (library != nullptr) {
#if defined(__linux__) || defined(__APPLE__)
        dlclose(library);
#elif defined(_WIN32)
        ::FreeLibrary(library);
#endif
        library = 0;
        vkGetInstanceProcAddr = VK_NULL_HANDLE;
    }
}
#if defined(__GNUC__)
#if defined(VK_SIMPLE_USE_DEFAULT_VISIBILITY)
#	pragma GCC visibility push(default)
#else
#	pragma GCC visibility push(hidden)
#endif
#endif
PFN_vkCreateInstance vkCreateInstance;
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
PFN_vkDestroyInstance vkDestroyInstance;
PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
PFN_vkCreateDevice vkCreateDevice;
PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
#if defined(VK_USE_PLATFORM_XLIB_KHR)
PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
#if defined(VK_USE_PLATFORM_GGP)
PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif // defined(VK_USE_PLATFORM_GGP)
PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#if defined(VK_USE_PLATFORM_VI_NN)
PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif // defined(VK_USE_PLATFORM_VI_NN)
PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
#if defined(VK_USE_PLATFORM_IOS_MVK)
PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#if defined(VK_USE_PLATFORM_FUCHSIA)
PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV;
PFN_vkGetWinrtDisplayNV vkGetWinrtDisplayNV;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
void vkInitializeInstanceFunctions (VkInstance Instance) {
    vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(vkGetInstanceProcAddr(Instance, "vkDestroyInstance"));
    vkEnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDevices"));
    vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(vkGetInstanceProcAddr(Instance, "vkGetDeviceProcAddr"));
    vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(vkGetInstanceProcAddr(Instance, "vkGetInstanceProcAddr"));
    vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceProperties"));
    vkGetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
    vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMemoryProperties"));
    vkGetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFeatures"));
    vkGetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFormatProperties"));
    vkGetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceImageFormatProperties"));
    vkCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(vkGetInstanceProcAddr(Instance, "vkCreateDevice"));
    vkEnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(vkGetInstanceProcAddr(Instance, "vkEnumerateDeviceExtensionProperties"));
    vkGetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties"));
    vkEnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDeviceGroups"));
    vkGetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFeatures2"));
    vkGetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceProperties2"));
    vkGetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFormatProperties2"));
    vkGetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceImageFormatProperties2"));
    vkGetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyProperties2"));
    vkGetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMemoryProperties2"));
    vkGetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties2"));
    vkGetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalBufferProperties"));
    vkGetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalFenceProperties"));
    vkGetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalSemaphoreProperties"));
    vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkDestroySurfaceKHR"));
    vkGetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceSupportKHR"));
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
    vkGetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
    vkGetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
    vkGetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDevicePresentRectanglesKHR"));
    vkGetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPropertiesKHR"));
    vkGetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
    vkGetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneSupportedDisplaysKHR"));
    vkGetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayModePropertiesKHR"));
    vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(vkGetInstanceProcAddr(Instance, "vkCreateDisplayModeKHR"));
    vkGetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneCapabilitiesKHR"));
    vkCreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateDisplayPlaneSurfaceKHR"));
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateXlibSurfaceKHR"));
    vkGetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateXcbSurfaceKHR"));
    vkGetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateWaylandSurfaceKHR"));
    vkGetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    vkCreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateAndroidSurfaceKHR"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateWin32SurfaceKHR"));
    vkGetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugReportCallbackEXT"));
    vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugReportCallbackEXT"));
    vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(Instance, "vkDebugReportMessageEXT"));
#if defined(VK_USE_PLATFORM_GGP)
    vkCreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(vkGetInstanceProcAddr(Instance, "vkCreateStreamDescriptorSurfaceGGP"));
#endif // defined(VK_USE_PLATFORM_GGP)
    vkGetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#if defined(VK_USE_PLATFORM_VI_NN)
    vkCreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(vkGetInstanceProcAddr(Instance, "vkCreateViSurfaceNN"));
#endif // defined(VK_USE_PLATFORM_VI_NN)
    vkReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkReleaseDisplayEXT"));
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    vkAcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkAcquireXlibDisplayEXT"));
    vkGetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkGetRandROutputDisplayEXT"));
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    vkGetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
    vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
    vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
    vkGetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
    vkGetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceFormats2KHR"));
    vkGetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayProperties2KHR"));
    vkGetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
    vkGetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayModeProperties2KHR"));
    vkGetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneCapabilities2KHR"));
#if defined(VK_USE_PLATFORM_IOS_MVK)
    vkCreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(vkGetInstanceProcAddr(Instance, "vkCreateIOSSurfaceMVK"));
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    vkCreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(vkGetInstanceProcAddr(Instance, "vkCreateMacOSSurfaceMVK"));
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
    vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT"));
    vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugUtilsMessengerEXT"));
    vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(vkGetInstanceProcAddr(Instance, "vkSubmitDebugUtilsMessageEXT"));
    vkGetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT"));
    vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#if defined(VK_USE_PLATFORM_FUCHSIA)
    vkCreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(vkGetInstanceProcAddr(Instance, "vkCreateImagePipeSurfaceFUCHSIA"));
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
    vkCreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateMetalSurfaceEXT"));
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
    vkGetPhysicalDeviceFragmentShadingRatesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR"));
    vkGetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceToolPropertiesEXT"));
    vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
    vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkCreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateHeadlessSurfaceEXT"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkAcquireWinrtDisplayNV = reinterpret_cast<PFN_vkAcquireWinrtDisplayNV>(vkGetInstanceProcAddr(Instance, "vkAcquireWinrtDisplayNV"));
    vkGetWinrtDisplayNV = reinterpret_cast<PFN_vkGetWinrtDisplayNV>(vkGetInstanceProcAddr(Instance, "vkGetWinrtDisplayNV"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    vkCreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDirectFBSurfaceEXT"));
    vkGetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
};
void vkInitializeDeviceFunctions (VkDevice Device) {
    vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(vkGetDeviceProcAddr(Device, "vkDestroyDevice"));
    vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue"));
    vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(vkGetDeviceProcAddr(Device, "vkQueueSubmit"));
    vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(vkGetDeviceProcAddr(Device, "vkQueueWaitIdle"));
    vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(vkGetDeviceProcAddr(Device, "vkDeviceWaitIdle"));
    vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(vkGetDeviceProcAddr(Device, "vkAllocateMemory"));
    vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(vkGetDeviceProcAddr(Device, "vkFreeMemory"));
    vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(vkGetDeviceProcAddr(Device, "vkMapMemory"));
    vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(vkGetDeviceProcAddr(Device, "vkUnmapMemory"));
    vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkFlushMappedMemoryRanges"));
    vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkInvalidateMappedMemoryRanges"));
    vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryCommitment"));
    vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements"));
    vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory"));
    vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements"));
    vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(vkGetDeviceProcAddr(Device, "vkBindImageMemory"));
    vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements"));
    vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(vkGetDeviceProcAddr(Device, "vkQueueBindSparse"));
    vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(vkGetDeviceProcAddr(Device, "vkCreateFence"));
    vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(vkGetDeviceProcAddr(Device, "vkDestroyFence"));
    vkResetFences = reinterpret_cast<PFN_vkResetFences>(vkGetDeviceProcAddr(Device, "vkResetFences"));
    vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(vkGetDeviceProcAddr(Device, "vkGetFenceStatus"));
    vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(vkGetDeviceProcAddr(Device, "vkWaitForFences"));
    vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(vkGetDeviceProcAddr(Device, "vkCreateSemaphore"));
    vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(vkGetDeviceProcAddr(Device, "vkDestroySemaphore"));
    vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(vkGetDeviceProcAddr(Device, "vkCreateEvent"));
    vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(vkGetDeviceProcAddr(Device, "vkDestroyEvent"));
    vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(vkGetDeviceProcAddr(Device, "vkGetEventStatus"));
    vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(vkGetDeviceProcAddr(Device, "vkSetEvent"));
    vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(vkGetDeviceProcAddr(Device, "vkResetEvent"));
    vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(vkGetDeviceProcAddr(Device, "vkCreateQueryPool"));
    vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(vkGetDeviceProcAddr(Device, "vkDestroyQueryPool"));
    vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkGetQueryPoolResults"));
    vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(vkGetDeviceProcAddr(Device, "vkCreateBuffer"));
    vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(vkGetDeviceProcAddr(Device, "vkDestroyBuffer"));
    vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(vkGetDeviceProcAddr(Device, "vkCreateBufferView"));
    vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(vkGetDeviceProcAddr(Device, "vkDestroyBufferView"));
    vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(vkGetDeviceProcAddr(Device, "vkCreateImage"));
    vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(vkGetDeviceProcAddr(Device, "vkDestroyImage"));
    vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(vkGetDeviceProcAddr(Device, "vkGetImageSubresourceLayout"));
    vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(vkGetDeviceProcAddr(Device, "vkCreateImageView"));
    vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(vkGetDeviceProcAddr(Device, "vkDestroyImageView"));
    vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(vkGetDeviceProcAddr(Device, "vkCreateShaderModule"));
    vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(vkGetDeviceProcAddr(Device, "vkDestroyShaderModule"));
    vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(vkGetDeviceProcAddr(Device, "vkCreatePipelineCache"));
    vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineCache"));
    vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(vkGetDeviceProcAddr(Device, "vkGetPipelineCacheData"));
    vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(vkGetDeviceProcAddr(Device, "vkMergePipelineCaches"));
    vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(vkGetDeviceProcAddr(Device, "vkCreateGraphicsPipelines"));
    vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(vkGetDeviceProcAddr(Device, "vkCreateComputePipelines"));
    vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(vkGetDeviceProcAddr(Device, "vkDestroyPipeline"));
    vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(vkGetDeviceProcAddr(Device, "vkCreatePipelineLayout"));
    vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineLayout"));
    vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(vkGetDeviceProcAddr(Device, "vkCreateSampler"));
    vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(vkGetDeviceProcAddr(Device, "vkDestroySampler"));
    vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorSetLayout"));
    vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorSetLayout"));
    vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorPool"));
    vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorPool"));
    vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(vkGetDeviceProcAddr(Device, "vkResetDescriptorPool"));
    vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkAllocateDescriptorSets"));
    vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(vkGetDeviceProcAddr(Device, "vkFreeDescriptorSets"));
    vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSets"));
    vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(vkGetDeviceProcAddr(Device, "vkCreateFramebuffer"));
    vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(vkGetDeviceProcAddr(Device, "vkDestroyFramebuffer"));
    vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass"));
    vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(vkGetDeviceProcAddr(Device, "vkDestroyRenderPass"));
    vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(vkGetDeviceProcAddr(Device, "vkGetRenderAreaGranularity"));
    vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(vkGetDeviceProcAddr(Device, "vkCreateCommandPool"));
    vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(vkGetDeviceProcAddr(Device, "vkDestroyCommandPool"));
    vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(vkGetDeviceProcAddr(Device, "vkResetCommandPool"));
    vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(vkGetDeviceProcAddr(Device, "vkAllocateCommandBuffers"));
    vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(vkGetDeviceProcAddr(Device, "vkFreeCommandBuffers"));
    vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(vkGetDeviceProcAddr(Device, "vkBeginCommandBuffer"));
    vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(vkGetDeviceProcAddr(Device, "vkEndCommandBuffer"));
    vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(vkGetDeviceProcAddr(Device, "vkResetCommandBuffer"));
    vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(vkGetDeviceProcAddr(Device, "vkCmdBindPipeline"));
    vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(vkGetDeviceProcAddr(Device, "vkCmdSetViewport"));
    vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(vkGetDeviceProcAddr(Device, "vkCmdSetScissor"));
    vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(vkGetDeviceProcAddr(Device, "vkCmdSetLineWidth"));
    vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBias"));
    vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(vkGetDeviceProcAddr(Device, "vkCmdSetBlendConstants"));
    vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBounds"));
    vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilCompareMask"));
    vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilWriteMask"));
    vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilReference"));
    vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(vkGetDeviceProcAddr(Device, "vkCmdBindDescriptorSets"));
    vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(vkGetDeviceProcAddr(Device, "vkCmdBindIndexBuffer"));
    vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers"));
    vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(vkGetDeviceProcAddr(Device, "vkCmdDraw"));
    vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexed"));
    vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirect"));
    vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirect"));
    vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(vkGetDeviceProcAddr(Device, "vkCmdDispatch"));
    vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDispatchIndirect"));
    vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer"));
    vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage"));
    vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage"));
    vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage"));
    vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer"));
    vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(vkGetDeviceProcAddr(Device, "vkCmdUpdateBuffer"));
    vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(vkGetDeviceProcAddr(Device, "vkCmdFillBuffer"));
    vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(vkGetDeviceProcAddr(Device, "vkCmdClearColorImage"));
    vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(vkGetDeviceProcAddr(Device, "vkCmdClearDepthStencilImage"));
    vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(vkGetDeviceProcAddr(Device, "vkCmdClearAttachments"));
    vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage"));
    vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(vkGetDeviceProcAddr(Device, "vkCmdSetEvent"));
    vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(vkGetDeviceProcAddr(Device, "vkCmdResetEvent"));
    vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(vkGetDeviceProcAddr(Device, "vkCmdWaitEvents"));
    vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(vkGetDeviceProcAddr(Device, "vkCmdPipelineBarrier"));
    vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(vkGetDeviceProcAddr(Device, "vkCmdBeginQuery"));
    vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(vkGetDeviceProcAddr(Device, "vkCmdEndQuery"));
    vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(vkGetDeviceProcAddr(Device, "vkCmdResetQueryPool"));
    vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(vkGetDeviceProcAddr(Device, "vkCmdWriteTimestamp"));
    vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkCmdCopyQueryPoolResults"));
    vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(vkGetDeviceProcAddr(Device, "vkCmdPushConstants"));
    vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass"));
    vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass"));
    vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass"));
    vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(vkGetDeviceProcAddr(Device, "vkCmdExecuteCommands"));
    vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory2"));
    vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(vkGetDeviceProcAddr(Device, "vkBindImageMemory2"));
    vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPeerMemoryFeatures"));
    vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(vkGetDeviceProcAddr(Device, "vkCmdSetDeviceMask"));
    vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(vkGetDeviceProcAddr(Device, "vkCmdDispatchBase"));
    vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements2"));
    vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements2"));
    vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements2"));
    vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(vkGetDeviceProcAddr(Device, "vkTrimCommandPool"));
    vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue2"));
    vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkCreateSamplerYcbcrConversion"));
    vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkDestroySamplerYcbcrConversion"));
    vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorUpdateTemplate"));
    vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorUpdateTemplate"));
    vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSetWithTemplate"));
    vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(vkGetDeviceProcAddr(Device, "vkGetDescriptorSetLayoutSupport"));
    vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectCount"));
    vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirectCount"));
    vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass2"));
    vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass2"));
    vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass2"));
    vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass2"));
    vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(vkGetDeviceProcAddr(Device, "vkResetQueryPool"));
    vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreCounterValue"));
    vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(vkGetDeviceProcAddr(Device, "vkWaitSemaphores"));
    vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(vkGetDeviceProcAddr(Device, "vkSignalSemaphore"));
    vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferOpaqueCaptureAddress"));
    vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferDeviceAddress"));
    vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryOpaqueCaptureAddress"));
    vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(vkGetDeviceProcAddr(Device, "vkCreateSwapchainKHR"));
    vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(vkGetDeviceProcAddr(Device, "vkDestroySwapchainKHR"));
    vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainImagesKHR"));
    vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImageKHR"));
    vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(vkGetDeviceProcAddr(Device, "vkQueuePresentKHR"));
    vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPresentCapabilitiesKHR"));
    vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModesKHR"));
    vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImage2KHR"));
    vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(vkGetDeviceProcAddr(Device, "vkCreateSharedSwapchainsKHR"));
    vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectNameEXT"));
    vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectTagEXT"));
    vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerBeginEXT"));
    vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerEndEXT"));
    vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerInsertEXT"));
    vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(vkGetDeviceProcAddr(Device, "vkCmdBindTransformFeedbackBuffersEXT"));
    vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginTransformFeedbackEXT"));
    vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndTransformFeedbackEXT"));
    vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginQueryIndexedEXT"));
    vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndQueryIndexedEXT"));
    vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectByteCountEXT"));
    vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewHandleNVX"));
    vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewAddressNVX"));
    vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(vkGetDeviceProcAddr(Device, "vkGetShaderInfoAMD"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleNV"));
    vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleKHR"));
    vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdKHR"));
    vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdPropertiesKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreWin32HandleKHR"));
    vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreFdKHR"));
    vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreFdKHR"));
    vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetKHR"));
    vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetWithTemplateKHR"));
    vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginConditionalRenderingEXT"));
    vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndConditionalRenderingEXT"));
    vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWScalingNV"));
    vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(vkGetDeviceProcAddr(Device, "vkDisplayPowerControlEXT"));
    vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDeviceEventEXT"));
    vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDisplayEventEXT"));
    vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(vkGetDeviceProcAddr(Device, "vkGetSwapchainCounterEXT"));
    vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetRefreshCycleDurationGOOGLE"));
    vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetPastPresentationTimingGOOGLE"));
    vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDiscardRectangleEXT"));
    vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(vkGetDeviceProcAddr(Device, "vkSetHdrMetadataEXT"));
    vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainStatusKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceWin32HandleKHR"));
    vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceFdKHR"));
    vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceFdKHR"));
    vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkAcquireProfilingLockKHR"));
    vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkReleaseProfilingLockKHR"));
    vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectNameEXT"));
    vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectTagEXT"));
    vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueBeginDebugUtilsLabelEXT"));
    vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueEndDebugUtilsLabelEXT"));
    vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueInsertDebugUtilsLabelEXT"));
    vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginDebugUtilsLabelEXT"));
    vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndDebugUtilsLabelEXT"));
    vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdInsertDebugUtilsLabelEXT"));
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(vkGetDeviceProcAddr(Device, "vkGetAndroidHardwareBufferPropertiesANDROID"));
    vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(vkGetDeviceProcAddr(Device, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetSampleLocationsEXT"));
    vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureKHR"));
    vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureKHR"));
    vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureKHR"));
    vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureToMemoryKHR"));
    vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureToMemoryKHR"));
    vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyMemoryToAccelerationStructureKHR"));
    vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyMemoryToAccelerationStructureKHR"));
    vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
    vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkWriteAccelerationStructuresPropertiesKHR"));
    vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
    vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureKHR"));
    vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresKHR"));
    vkCmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresIndirectKHR"));
    vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkBuildAccelerationStructuresKHR"));
    vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureDeviceAddressKHR"));
    vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureBuildSizesKHR"));
    vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysKHR"));
    vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupHandlesKHR"));
    vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
    vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesKHR"));
    vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysIndirectKHR"));
    vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupStackSizeKHR"));
    vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetRayTracingPipelineStackSizeKHR"));
    vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetImageDrmFormatModifierPropertiesEXT"));
    vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkCreateValidationCacheEXT"));
    vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkDestroyValidationCacheEXT"));
    vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(vkGetDeviceProcAddr(Device, "vkGetValidationCacheDataEXT"));
    vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(vkGetDeviceProcAddr(Device, "vkMergeValidationCachesEXT"));
    vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(vkGetDeviceProcAddr(Device, "vkCmdBindShadingRateImageNV"));
    vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportShadingRatePaletteNV"));
    vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCoarseSampleOrderNV"));
    vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(vkGetDeviceProcAddr(Device, "vkCompileDeferredNV"));
    vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureNV"));
    vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureNV"));
    vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureMemoryRequirementsNV"));
    vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(vkGetDeviceProcAddr(Device, "vkBindAccelerationStructureMemoryNV"));
    vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureNV"));
    vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesNV"));
    vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructureNV"));
    vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysNV"));
    vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureHandleNV"));
    vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesNV"));
    vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetMemoryHostPointerPropertiesEXT"));
    vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(vkGetDeviceProcAddr(Device, "vkCmdWriteBufferMarkerAMD"));
    vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(vkGetDeviceProcAddr(Device, "vkGetCalibratedTimestampsEXT"));
    vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksNV"));
    vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectNV"));
    vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectCountNV"));
    vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(vkGetDeviceProcAddr(Device, "vkCmdSetExclusiveScissorNV"));
    vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCheckpointNV"));
    vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(vkGetDeviceProcAddr(Device, "vkGetQueueCheckpointDataNV"));
    vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkInitializePerformanceApiINTEL"));
    vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkUninitializePerformanceApiINTEL"));
    vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceMarkerINTEL"));
    vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceStreamMarkerINTEL"));
    vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceOverrideINTEL"));
    vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkAcquirePerformanceConfigurationINTEL"));
    vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkReleasePerformanceConfigurationINTEL"));
    vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkQueueSetPerformanceConfigurationINTEL"));
    vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(vkGetDeviceProcAddr(Device, "vkGetPerformanceParameterINTEL"));
    vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(vkGetDeviceProcAddr(Device, "vkSetLocalDimmingAMD"));
    vkCmdSetFragmentShadingRateKHR = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkAcquireFullScreenExclusiveModeEXT"));
    vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkReleaseFullScreenExclusiveModeEXT"));
    vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetLineStippleEXT"));
    vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetCullModeEXT"));
    vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetFrontFaceEXT"));
    vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetPrimitiveTopologyEXT"));
    vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWithCountEXT"));
    vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetScissorWithCountEXT"));
    vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers2EXT"));
    vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthTestEnableEXT"));
    vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthWriteEnableEXT"));
    vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthCompareOpEXT"));
    vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBoundsTestEnableEXT"));
    vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilTestEnableEXT"));
    vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilOpEXT"));
    vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkCreateDeferredOperationKHR"));
    vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkDestroyDeferredOperationKHR"));
    vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationMaxConcurrencyKHR"));
    vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationResultKHR"));
    vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(vkGetDeviceProcAddr(Device, "vkDeferredOperationJoinKHR"));
    vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutablePropertiesKHR"));
    vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableStatisticsKHR"));
    vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableInternalRepresentationsKHR"));
    vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdExecuteGeneratedCommandsNV"));
    vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdPreprocessGeneratedCommandsNV"));
    vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(vkGetDeviceProcAddr(Device, "vkCmdBindPipelineShaderGroupNV"));
    vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetGeneratedCommandsMemoryRequirementsNV"));
    vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkCreateIndirectCommandsLayoutNV"));
    vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkDestroyIndirectCommandsLayoutNV"));
    vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkCreatePrivateDataSlotEXT"));
    vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkDestroyPrivateDataSlotEXT"));
    vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkSetPrivateDataEXT"));
    vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkGetPrivateDataEXT"));
    vkCmdSetFragmentShadingRateEnumNV = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateEnumNV>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateEnumNV"));
    vkCmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer2KHR"));
    vkCmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage2KHR"));
    vkCmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage2KHR"));
    vkCmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage2KHR"));
    vkCmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer2KHR"));
    vkCmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage2KHR"));
};
void vkInitializeDeviceDispatchTable (VkDevice Device, VkDeviceDispatchTable & table) {
    table.vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(vkGetDeviceProcAddr(Device, "vkDestroyDevice"));
    table.vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue"));
    table.vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(vkGetDeviceProcAddr(Device, "vkQueueSubmit"));
    table.vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(vkGetDeviceProcAddr(Device, "vkQueueWaitIdle"));
    table.vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(vkGetDeviceProcAddr(Device, "vkDeviceWaitIdle"));
    table.vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(vkGetDeviceProcAddr(Device, "vkAllocateMemory"));
    table.vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(vkGetDeviceProcAddr(Device, "vkFreeMemory"));
    table.vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(vkGetDeviceProcAddr(Device, "vkMapMemory"));
    table.vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(vkGetDeviceProcAddr(Device, "vkUnmapMemory"));
    table.vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkFlushMappedMemoryRanges"));
    table.vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkInvalidateMappedMemoryRanges"));
    table.vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryCommitment"));
    table.vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements"));
    table.vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory"));
    table.vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements"));
    table.vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(vkGetDeviceProcAddr(Device, "vkBindImageMemory"));
    table.vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements"));
    table.vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(vkGetDeviceProcAddr(Device, "vkQueueBindSparse"));
    table.vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(vkGetDeviceProcAddr(Device, "vkCreateFence"));
    table.vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(vkGetDeviceProcAddr(Device, "vkDestroyFence"));
    table.vkResetFences = reinterpret_cast<PFN_vkResetFences>(vkGetDeviceProcAddr(Device, "vkResetFences"));
    table.vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(vkGetDeviceProcAddr(Device, "vkGetFenceStatus"));
    table.vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(vkGetDeviceProcAddr(Device, "vkWaitForFences"));
    table.vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(vkGetDeviceProcAddr(Device, "vkCreateSemaphore"));
    table.vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(vkGetDeviceProcAddr(Device, "vkDestroySemaphore"));
    table.vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(vkGetDeviceProcAddr(Device, "vkCreateEvent"));
    table.vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(vkGetDeviceProcAddr(Device, "vkDestroyEvent"));
    table.vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(vkGetDeviceProcAddr(Device, "vkGetEventStatus"));
    table.vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(vkGetDeviceProcAddr(Device, "vkSetEvent"));
    table.vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(vkGetDeviceProcAddr(Device, "vkResetEvent"));
    table.vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(vkGetDeviceProcAddr(Device, "vkCreateQueryPool"));
    table.vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(vkGetDeviceProcAddr(Device, "vkDestroyQueryPool"));
    table.vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkGetQueryPoolResults"));
    table.vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(vkGetDeviceProcAddr(Device, "vkCreateBuffer"));
    table.vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(vkGetDeviceProcAddr(Device, "vkDestroyBuffer"));
    table.vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(vkGetDeviceProcAddr(Device, "vkCreateBufferView"));
    table.vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(vkGetDeviceProcAddr(Device, "vkDestroyBufferView"));
    table.vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(vkGetDeviceProcAddr(Device, "vkCreateImage"));
    table.vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(vkGetDeviceProcAddr(Device, "vkDestroyImage"));
    table.vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(vkGetDeviceProcAddr(Device, "vkGetImageSubresourceLayout"));
    table.vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(vkGetDeviceProcAddr(Device, "vkCreateImageView"));
    table.vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(vkGetDeviceProcAddr(Device, "vkDestroyImageView"));
    table.vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(vkGetDeviceProcAddr(Device, "vkCreateShaderModule"));
    table.vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(vkGetDeviceProcAddr(Device, "vkDestroyShaderModule"));
    table.vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(vkGetDeviceProcAddr(Device, "vkCreatePipelineCache"));
    table.vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineCache"));
    table.vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(vkGetDeviceProcAddr(Device, "vkGetPipelineCacheData"));
    table.vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(vkGetDeviceProcAddr(Device, "vkMergePipelineCaches"));
    table.vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(vkGetDeviceProcAddr(Device, "vkCreateGraphicsPipelines"));
    table.vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(vkGetDeviceProcAddr(Device, "vkCreateComputePipelines"));
    table.vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(vkGetDeviceProcAddr(Device, "vkDestroyPipeline"));
    table.vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(vkGetDeviceProcAddr(Device, "vkCreatePipelineLayout"));
    table.vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineLayout"));
    table.vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(vkGetDeviceProcAddr(Device, "vkCreateSampler"));
    table.vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(vkGetDeviceProcAddr(Device, "vkDestroySampler"));
    table.vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorSetLayout"));
    table.vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorSetLayout"));
    table.vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorPool"));
    table.vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorPool"));
    table.vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(vkGetDeviceProcAddr(Device, "vkResetDescriptorPool"));
    table.vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkAllocateDescriptorSets"));
    table.vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(vkGetDeviceProcAddr(Device, "vkFreeDescriptorSets"));
    table.vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSets"));
    table.vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(vkGetDeviceProcAddr(Device, "vkCreateFramebuffer"));
    table.vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(vkGetDeviceProcAddr(Device, "vkDestroyFramebuffer"));
    table.vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass"));
    table.vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(vkGetDeviceProcAddr(Device, "vkDestroyRenderPass"));
    table.vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(vkGetDeviceProcAddr(Device, "vkGetRenderAreaGranularity"));
    table.vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(vkGetDeviceProcAddr(Device, "vkCreateCommandPool"));
    table.vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(vkGetDeviceProcAddr(Device, "vkDestroyCommandPool"));
    table.vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(vkGetDeviceProcAddr(Device, "vkResetCommandPool"));
    table.vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(vkGetDeviceProcAddr(Device, "vkAllocateCommandBuffers"));
    table.vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(vkGetDeviceProcAddr(Device, "vkFreeCommandBuffers"));
    table.vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(vkGetDeviceProcAddr(Device, "vkBeginCommandBuffer"));
    table.vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(vkGetDeviceProcAddr(Device, "vkEndCommandBuffer"));
    table.vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(vkGetDeviceProcAddr(Device, "vkResetCommandBuffer"));
    table.vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(vkGetDeviceProcAddr(Device, "vkCmdBindPipeline"));
    table.vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(vkGetDeviceProcAddr(Device, "vkCmdSetViewport"));
    table.vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(vkGetDeviceProcAddr(Device, "vkCmdSetScissor"));
    table.vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(vkGetDeviceProcAddr(Device, "vkCmdSetLineWidth"));
    table.vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBias"));
    table.vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(vkGetDeviceProcAddr(Device, "vkCmdSetBlendConstants"));
    table.vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBounds"));
    table.vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilCompareMask"));
    table.vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilWriteMask"));
    table.vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilReference"));
    table.vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(vkGetDeviceProcAddr(Device, "vkCmdBindDescriptorSets"));
    table.vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(vkGetDeviceProcAddr(Device, "vkCmdBindIndexBuffer"));
    table.vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers"));
    table.vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(vkGetDeviceProcAddr(Device, "vkCmdDraw"));
    table.vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexed"));
    table.vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirect"));
    table.vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirect"));
    table.vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(vkGetDeviceProcAddr(Device, "vkCmdDispatch"));
    table.vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDispatchIndirect"));
    table.vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer"));
    table.vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage"));
    table.vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage"));
    table.vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage"));
    table.vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer"));
    table.vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(vkGetDeviceProcAddr(Device, "vkCmdUpdateBuffer"));
    table.vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(vkGetDeviceProcAddr(Device, "vkCmdFillBuffer"));
    table.vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(vkGetDeviceProcAddr(Device, "vkCmdClearColorImage"));
    table.vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(vkGetDeviceProcAddr(Device, "vkCmdClearDepthStencilImage"));
    table.vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(vkGetDeviceProcAddr(Device, "vkCmdClearAttachments"));
    table.vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage"));
    table.vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(vkGetDeviceProcAddr(Device, "vkCmdSetEvent"));
    table.vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(vkGetDeviceProcAddr(Device, "vkCmdResetEvent"));
    table.vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(vkGetDeviceProcAddr(Device, "vkCmdWaitEvents"));
    table.vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(vkGetDeviceProcAddr(Device, "vkCmdPipelineBarrier"));
    table.vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(vkGetDeviceProcAddr(Device, "vkCmdBeginQuery"));
    table.vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(vkGetDeviceProcAddr(Device, "vkCmdEndQuery"));
    table.vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(vkGetDeviceProcAddr(Device, "vkCmdResetQueryPool"));
    table.vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(vkGetDeviceProcAddr(Device, "vkCmdWriteTimestamp"));
    table.vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkCmdCopyQueryPoolResults"));
    table.vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(vkGetDeviceProcAddr(Device, "vkCmdPushConstants"));
    table.vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass"));
    table.vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass"));
    table.vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass"));
    table.vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(vkGetDeviceProcAddr(Device, "vkCmdExecuteCommands"));
    table.vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory2"));
    table.vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(vkGetDeviceProcAddr(Device, "vkBindImageMemory2"));
    table.vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPeerMemoryFeatures"));
    table.vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(vkGetDeviceProcAddr(Device, "vkCmdSetDeviceMask"));
    table.vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(vkGetDeviceProcAddr(Device, "vkCmdDispatchBase"));
    table.vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements2"));
    table.vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements2"));
    table.vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements2"));
    table.vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(vkGetDeviceProcAddr(Device, "vkTrimCommandPool"));
    table.vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue2"));
    table.vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkCreateSamplerYcbcrConversion"));
    table.vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkDestroySamplerYcbcrConversion"));
    table.vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorUpdateTemplate"));
    table.vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorUpdateTemplate"));
    table.vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSetWithTemplate"));
    table.vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(vkGetDeviceProcAddr(Device, "vkGetDescriptorSetLayoutSupport"));
    table.vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectCount"));
    table.vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirectCount"));
    table.vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass2"));
    table.vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass2"));
    table.vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass2"));
    table.vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass2"));
    table.vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(vkGetDeviceProcAddr(Device, "vkResetQueryPool"));
    table.vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreCounterValue"));
    table.vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(vkGetDeviceProcAddr(Device, "vkWaitSemaphores"));
    table.vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(vkGetDeviceProcAddr(Device, "vkSignalSemaphore"));
    table.vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferOpaqueCaptureAddress"));
    table.vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferDeviceAddress"));
    table.vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryOpaqueCaptureAddress"));
    table.vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(vkGetDeviceProcAddr(Device, "vkCreateSwapchainKHR"));
    table.vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(vkGetDeviceProcAddr(Device, "vkDestroySwapchainKHR"));
    table.vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainImagesKHR"));
    table.vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImageKHR"));
    table.vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(vkGetDeviceProcAddr(Device, "vkQueuePresentKHR"));
    table.vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPresentCapabilitiesKHR"));
    table.vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModesKHR"));
    table.vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImage2KHR"));
    table.vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(vkGetDeviceProcAddr(Device, "vkCreateSharedSwapchainsKHR"));
    table.vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectNameEXT"));
    table.vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectTagEXT"));
    table.vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerBeginEXT"));
    table.vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerEndEXT"));
    table.vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerInsertEXT"));
    table.vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(vkGetDeviceProcAddr(Device, "vkCmdBindTransformFeedbackBuffersEXT"));
    table.vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginTransformFeedbackEXT"));
    table.vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndTransformFeedbackEXT"));
    table.vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginQueryIndexedEXT"));
    table.vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndQueryIndexedEXT"));
    table.vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectByteCountEXT"));
    table.vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewHandleNVX"));
    table.vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewAddressNVX"));
    table.vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(vkGetDeviceProcAddr(Device, "vkGetShaderInfoAMD"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleNV"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdKHR"));
    table.vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdPropertiesKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreFdKHR"));
    table.vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreFdKHR"));
    table.vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetKHR"));
    table.vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetWithTemplateKHR"));
    table.vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginConditionalRenderingEXT"));
    table.vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndConditionalRenderingEXT"));
    table.vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWScalingNV"));
    table.vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(vkGetDeviceProcAddr(Device, "vkDisplayPowerControlEXT"));
    table.vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDeviceEventEXT"));
    table.vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDisplayEventEXT"));
    table.vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(vkGetDeviceProcAddr(Device, "vkGetSwapchainCounterEXT"));
    table.vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetRefreshCycleDurationGOOGLE"));
    table.vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetPastPresentationTimingGOOGLE"));
    table.vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDiscardRectangleEXT"));
    table.vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(vkGetDeviceProcAddr(Device, "vkSetHdrMetadataEXT"));
    table.vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainStatusKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceFdKHR"));
    table.vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceFdKHR"));
    table.vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkAcquireProfilingLockKHR"));
    table.vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkReleaseProfilingLockKHR"));
    table.vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectNameEXT"));
    table.vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectTagEXT"));
    table.vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueBeginDebugUtilsLabelEXT"));
    table.vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueEndDebugUtilsLabelEXT"));
    table.vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueInsertDebugUtilsLabelEXT"));
    table.vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginDebugUtilsLabelEXT"));
    table.vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndDebugUtilsLabelEXT"));
    table.vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdInsertDebugUtilsLabelEXT"));
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    table.vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(vkGetDeviceProcAddr(Device, "vkGetAndroidHardwareBufferPropertiesANDROID"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    table.vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(vkGetDeviceProcAddr(Device, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    table.vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetSampleLocationsEXT"));
    table.vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureKHR"));
    table.vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureKHR"));
    table.vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureKHR"));
    table.vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureToMemoryKHR"));
    table.vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureToMemoryKHR"));
    table.vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyMemoryToAccelerationStructureKHR"));
    table.vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyMemoryToAccelerationStructureKHR"));
    table.vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
    table.vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkWriteAccelerationStructuresPropertiesKHR"));
    table.vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
    table.vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureKHR"));
    table.vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresKHR"));
    table.vkCmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresIndirectKHR"));
    table.vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkBuildAccelerationStructuresKHR"));
    table.vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureDeviceAddressKHR"));
    table.vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureBuildSizesKHR"));
    table.vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysKHR"));
    table.vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupHandlesKHR"));
    table.vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
    table.vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesKHR"));
    table.vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysIndirectKHR"));
    table.vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupStackSizeKHR"));
    table.vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetRayTracingPipelineStackSizeKHR"));
    table.vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetImageDrmFormatModifierPropertiesEXT"));
    table.vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkCreateValidationCacheEXT"));
    table.vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkDestroyValidationCacheEXT"));
    table.vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(vkGetDeviceProcAddr(Device, "vkGetValidationCacheDataEXT"));
    table.vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(vkGetDeviceProcAddr(Device, "vkMergeValidationCachesEXT"));
    table.vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(vkGetDeviceProcAddr(Device, "vkCmdBindShadingRateImageNV"));
    table.vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportShadingRatePaletteNV"));
    table.vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCoarseSampleOrderNV"));
    table.vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(vkGetDeviceProcAddr(Device, "vkCompileDeferredNV"));
    table.vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureNV"));
    table.vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureNV"));
    table.vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureMemoryRequirementsNV"));
    table.vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(vkGetDeviceProcAddr(Device, "vkBindAccelerationStructureMemoryNV"));
    table.vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureNV"));
    table.vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesNV"));
    table.vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructureNV"));
    table.vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysNV"));
    table.vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureHandleNV"));
    table.vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesNV"));
    table.vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetMemoryHostPointerPropertiesEXT"));
    table.vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(vkGetDeviceProcAddr(Device, "vkCmdWriteBufferMarkerAMD"));
    table.vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(vkGetDeviceProcAddr(Device, "vkGetCalibratedTimestampsEXT"));
    table.vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksNV"));
    table.vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectNV"));
    table.vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectCountNV"));
    table.vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(vkGetDeviceProcAddr(Device, "vkCmdSetExclusiveScissorNV"));
    table.vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCheckpointNV"));
    table.vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(vkGetDeviceProcAddr(Device, "vkGetQueueCheckpointDataNV"));
    table.vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkInitializePerformanceApiINTEL"));
    table.vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkUninitializePerformanceApiINTEL"));
    table.vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceMarkerINTEL"));
    table.vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceStreamMarkerINTEL"));
    table.vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceOverrideINTEL"));
    table.vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkAcquirePerformanceConfigurationINTEL"));
    table.vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkReleasePerformanceConfigurationINTEL"));
    table.vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkQueueSetPerformanceConfigurationINTEL"));
    table.vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(vkGetDeviceProcAddr(Device, "vkGetPerformanceParameterINTEL"));
    table.vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(vkGetDeviceProcAddr(Device, "vkSetLocalDimmingAMD"));
    table.vkCmdSetFragmentShadingRateKHR = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkAcquireFullScreenExclusiveModeEXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkReleaseFullScreenExclusiveModeEXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetLineStippleEXT"));
    table.vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetCullModeEXT"));
    table.vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetFrontFaceEXT"));
    table.vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetPrimitiveTopologyEXT"));
    table.vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWithCountEXT"));
    table.vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetScissorWithCountEXT"));
    table.vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers2EXT"));
    table.vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthTestEnableEXT"));
    table.vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthWriteEnableEXT"));
    table.vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthCompareOpEXT"));
    table.vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBoundsTestEnableEXT"));
    table.vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilTestEnableEXT"));
    table.vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilOpEXT"));
    table.vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkCreateDeferredOperationKHR"));
    table.vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkDestroyDeferredOperationKHR"));
    table.vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationMaxConcurrencyKHR"));
    table.vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationResultKHR"));
    table.vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(vkGetDeviceProcAddr(Device, "vkDeferredOperationJoinKHR"));
    table.vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutablePropertiesKHR"));
    table.vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableStatisticsKHR"));
    table.vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableInternalRepresentationsKHR"));
    table.vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdExecuteGeneratedCommandsNV"));
    table.vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdPreprocessGeneratedCommandsNV"));
    table.vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(vkGetDeviceProcAddr(Device, "vkCmdBindPipelineShaderGroupNV"));
    table.vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetGeneratedCommandsMemoryRequirementsNV"));
    table.vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkCreateIndirectCommandsLayoutNV"));
    table.vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkDestroyIndirectCommandsLayoutNV"));
    table.vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkCreatePrivateDataSlotEXT"));
    table.vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkDestroyPrivateDataSlotEXT"));
    table.vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkSetPrivateDataEXT"));
    table.vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkGetPrivateDataEXT"));
    table.vkCmdSetFragmentShadingRateEnumNV = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateEnumNV>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateEnumNV"));
    table.vkCmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer2KHR"));
    table.vkCmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage2KHR"));
    table.vkCmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage2KHR"));
    table.vkCmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage2KHR"));
    table.vkCmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer2KHR"));
    table.vkCmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage2KHR"));
};
#if defined(__GNUC__)
#	pragma GCC visibility pop
#endif

// clang-format on
