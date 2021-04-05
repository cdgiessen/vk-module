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
#include "vulkan.h"
// clang-format off


#if defined(_WIN32)
    using HINSTANCE = struct HINSTANCE__ * HINSTANCE;
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
    if (library == 0) return VkResult::VK_ERROR_INITIALIZATION_FAILED;
    LoadGetInstanceProcAddr();
    LoadGlobalFunctions();
    if (vkGetInstanceProcAddr == nullptr) return VkResult::VK_ERROR_INITIALIZATION_FAILED;
    return VkResult::VK_SUCCESS;
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
#ifdef __GNUC__
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
PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
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
    pfn_vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(vkGetInstanceProcAddr(Instance, "vkDestroyInstance"));
    pfn_vkEnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDevices"));
    pfn_vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(vkGetInstanceProcAddr(Instance, "vkGetDeviceProcAddr"));
    pfn_vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(vkGetInstanceProcAddr(Instance, "vkGetInstanceProcAddr"));
    pfn_vkGetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceProperties"));
    pfn_vkGetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
    pfn_vkGetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMemoryProperties"));
    pfn_vkGetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFeatures"));
    pfn_vkGetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFormatProperties"));
    pfn_vkGetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceImageFormatProperties"));
    pfn_vkCreateDevice = reinterpret_cast<PFN_vkCreateDevice>(vkGetInstanceProcAddr(Instance, "vkCreateDevice"));
    pfn_vkEnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(vkGetInstanceProcAddr(Instance, "vkEnumerateDeviceExtensionProperties"));
    pfn_vkGetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties"));
    pfn_vkEnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDeviceGroups"));
    pfn_vkGetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFeatures2"));
    pfn_vkGetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceProperties2"));
    pfn_vkGetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFormatProperties2"));
    pfn_vkGetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceImageFormatProperties2"));
    pfn_vkGetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyProperties2"));
    pfn_vkGetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMemoryProperties2"));
    pfn_vkGetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSparseImageFormatProperties2"));
    pfn_vkGetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalBufferProperties"));
    pfn_vkGetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalFenceProperties"));
    pfn_vkGetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalSemaphoreProperties"));
    pfn_vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkDestroySurfaceKHR"));
    pfn_vkGetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceSupportKHR"));
    pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
    pfn_vkGetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
    pfn_vkGetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
    pfn_vkGetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDevicePresentRectanglesKHR"));
    pfn_vkGetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPropertiesKHR"));
    pfn_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
    pfn_vkGetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneSupportedDisplaysKHR"));
    pfn_vkGetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayModePropertiesKHR"));
    pfn_vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(vkGetInstanceProcAddr(Instance, "vkCreateDisplayModeKHR"));
    pfn_vkGetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneCapabilitiesKHR"));
    pfn_vkCreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateDisplayPlaneSurfaceKHR"));
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    pfn_vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateXlibSurfaceKHR"));
    pfn_vkGetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    pfn_vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateXcbSurfaceKHR"));
    pfn_vkGetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    pfn_vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateWaylandSurfaceKHR"));
    pfn_vkGetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_vkCreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateAndroidSurfaceKHR"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(Instance, "vkCreateWin32SurfaceKHR"));
    pfn_vkGetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugReportCallbackEXT"));
    pfn_vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugReportCallbackEXT"));
    pfn_vkDebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(vkGetInstanceProcAddr(Instance, "vkDebugReportMessageEXT"));
#if defined(VK_USE_PLATFORM_GGP)
    pfn_vkCreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(vkGetInstanceProcAddr(Instance, "vkCreateStreamDescriptorSurfaceGGP"));
#endif // defined(VK_USE_PLATFORM_GGP)
    pfn_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#if defined(VK_USE_PLATFORM_VI_NN)
    pfn_vkCreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(vkGetInstanceProcAddr(Instance, "vkCreateViSurfaceNN"));
#endif // defined(VK_USE_PLATFORM_VI_NN)
    pfn_vkReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkReleaseDisplayEXT"));
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    pfn_vkAcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkAcquireXlibDisplayEXT"));
    pfn_vkGetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(vkGetInstanceProcAddr(Instance, "vkGetRandROutputDisplayEXT"));
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    pfn_vkGetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
    pfn_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(vkGetInstanceProcAddr(Instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
    pfn_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
    pfn_vkGetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
    pfn_vkGetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfaceFormats2KHR"));
    pfn_vkGetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayProperties2KHR"));
    pfn_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
    pfn_vkGetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayModeProperties2KHR"));
    pfn_vkGetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(vkGetInstanceProcAddr(Instance, "vkGetDisplayPlaneCapabilities2KHR"));
#if defined(VK_USE_PLATFORM_IOS_MVK)
    pfn_vkCreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(vkGetInstanceProcAddr(Instance, "vkCreateIOSSurfaceMVK"));
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    pfn_vkCreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(vkGetInstanceProcAddr(Instance, "vkCreateMacOSSurfaceMVK"));
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
    pfn_vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT"));
    pfn_vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugUtilsMessengerEXT"));
    pfn_vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(vkGetInstanceProcAddr(Instance, "vkSubmitDebugUtilsMessageEXT"));
    pfn_vkGetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT"));
    pfn_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#if defined(VK_USE_PLATFORM_FUCHSIA)
    pfn_vkCreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(vkGetInstanceProcAddr(Instance, "vkCreateImagePipeSurfaceFUCHSIA"));
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
    pfn_vkCreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateMetalSurfaceEXT"));
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
    pfn_vkGetPhysicalDeviceFragmentShadingRatesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR"));
    pfn_vkGetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceToolPropertiesEXT"));
    pfn_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
    pfn_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkCreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateHeadlessSurfaceEXT"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkAcquireWinrtDisplayNV = reinterpret_cast<PFN_vkAcquireWinrtDisplayNV>(vkGetInstanceProcAddr(Instance, "vkAcquireWinrtDisplayNV"));
    pfn_vkGetWinrtDisplayNV = reinterpret_cast<PFN_vkGetWinrtDisplayNV>(vkGetInstanceProcAddr(Instance, "vkGetWinrtDisplayNV"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    pfn_vkCreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDirectFBSurfaceEXT"));
    pfn_vkGetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(vkGetInstanceProcAddr(Instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
};
void vkInitializeDeviceFunctions (VkDevice Device) {
    pfn_vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(vkGetDeviceProcAddr(Device, "vkDestroyDevice"));
    pfn_vkGetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue"));
    pfn_vkQueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(vkGetDeviceProcAddr(Device, "vkQueueSubmit"));
    pfn_vkQueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(vkGetDeviceProcAddr(Device, "vkQueueWaitIdle"));
    pfn_vkDeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(vkGetDeviceProcAddr(Device, "vkDeviceWaitIdle"));
    pfn_vkAllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(vkGetDeviceProcAddr(Device, "vkAllocateMemory"));
    pfn_vkFreeMemory = reinterpret_cast<PFN_vkFreeMemory>(vkGetDeviceProcAddr(Device, "vkFreeMemory"));
    pfn_vkMapMemory = reinterpret_cast<PFN_vkMapMemory>(vkGetDeviceProcAddr(Device, "vkMapMemory"));
    pfn_vkUnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(vkGetDeviceProcAddr(Device, "vkUnmapMemory"));
    pfn_vkFlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkFlushMappedMemoryRanges"));
    pfn_vkInvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(vkGetDeviceProcAddr(Device, "vkInvalidateMappedMemoryRanges"));
    pfn_vkGetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryCommitment"));
    pfn_vkGetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements"));
    pfn_vkBindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory"));
    pfn_vkGetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements"));
    pfn_vkBindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(vkGetDeviceProcAddr(Device, "vkBindImageMemory"));
    pfn_vkGetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements"));
    pfn_vkQueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(vkGetDeviceProcAddr(Device, "vkQueueBindSparse"));
    pfn_vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(vkGetDeviceProcAddr(Device, "vkCreateFence"));
    pfn_vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(vkGetDeviceProcAddr(Device, "vkDestroyFence"));
    pfn_vkResetFences = reinterpret_cast<PFN_vkResetFences>(vkGetDeviceProcAddr(Device, "vkResetFences"));
    pfn_vkGetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(vkGetDeviceProcAddr(Device, "vkGetFenceStatus"));
    pfn_vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(vkGetDeviceProcAddr(Device, "vkWaitForFences"));
    pfn_vkCreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(vkGetDeviceProcAddr(Device, "vkCreateSemaphore"));
    pfn_vkDestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(vkGetDeviceProcAddr(Device, "vkDestroySemaphore"));
    pfn_vkCreateEvent = reinterpret_cast<PFN_vkCreateEvent>(vkGetDeviceProcAddr(Device, "vkCreateEvent"));
    pfn_vkDestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(vkGetDeviceProcAddr(Device, "vkDestroyEvent"));
    pfn_vkGetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(vkGetDeviceProcAddr(Device, "vkGetEventStatus"));
    pfn_vkSetEvent = reinterpret_cast<PFN_vkSetEvent>(vkGetDeviceProcAddr(Device, "vkSetEvent"));
    pfn_vkResetEvent = reinterpret_cast<PFN_vkResetEvent>(vkGetDeviceProcAddr(Device, "vkResetEvent"));
    pfn_vkCreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(vkGetDeviceProcAddr(Device, "vkCreateQueryPool"));
    pfn_vkDestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(vkGetDeviceProcAddr(Device, "vkDestroyQueryPool"));
    pfn_vkGetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkGetQueryPoolResults"));
    pfn_vkCreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(vkGetDeviceProcAddr(Device, "vkCreateBuffer"));
    pfn_vkDestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(vkGetDeviceProcAddr(Device, "vkDestroyBuffer"));
    pfn_vkCreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(vkGetDeviceProcAddr(Device, "vkCreateBufferView"));
    pfn_vkDestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(vkGetDeviceProcAddr(Device, "vkDestroyBufferView"));
    pfn_vkCreateImage = reinterpret_cast<PFN_vkCreateImage>(vkGetDeviceProcAddr(Device, "vkCreateImage"));
    pfn_vkDestroyImage = reinterpret_cast<PFN_vkDestroyImage>(vkGetDeviceProcAddr(Device, "vkDestroyImage"));
    pfn_vkGetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(vkGetDeviceProcAddr(Device, "vkGetImageSubresourceLayout"));
    pfn_vkCreateImageView = reinterpret_cast<PFN_vkCreateImageView>(vkGetDeviceProcAddr(Device, "vkCreateImageView"));
    pfn_vkDestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(vkGetDeviceProcAddr(Device, "vkDestroyImageView"));
    pfn_vkCreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(vkGetDeviceProcAddr(Device, "vkCreateShaderModule"));
    pfn_vkDestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(vkGetDeviceProcAddr(Device, "vkDestroyShaderModule"));
    pfn_vkCreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(vkGetDeviceProcAddr(Device, "vkCreatePipelineCache"));
    pfn_vkDestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineCache"));
    pfn_vkGetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(vkGetDeviceProcAddr(Device, "vkGetPipelineCacheData"));
    pfn_vkMergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(vkGetDeviceProcAddr(Device, "vkMergePipelineCaches"));
    pfn_vkCreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(vkGetDeviceProcAddr(Device, "vkCreateGraphicsPipelines"));
    pfn_vkCreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(vkGetDeviceProcAddr(Device, "vkCreateComputePipelines"));
    pfn_vkDestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(vkGetDeviceProcAddr(Device, "vkDestroyPipeline"));
    pfn_vkCreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(vkGetDeviceProcAddr(Device, "vkCreatePipelineLayout"));
    pfn_vkDestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(vkGetDeviceProcAddr(Device, "vkDestroyPipelineLayout"));
    pfn_vkCreateSampler = reinterpret_cast<PFN_vkCreateSampler>(vkGetDeviceProcAddr(Device, "vkCreateSampler"));
    pfn_vkDestroySampler = reinterpret_cast<PFN_vkDestroySampler>(vkGetDeviceProcAddr(Device, "vkDestroySampler"));
    pfn_vkCreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorSetLayout"));
    pfn_vkDestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorSetLayout"));
    pfn_vkCreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorPool"));
    pfn_vkDestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorPool"));
    pfn_vkResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(vkGetDeviceProcAddr(Device, "vkResetDescriptorPool"));
    pfn_vkAllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkAllocateDescriptorSets"));
    pfn_vkFreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(vkGetDeviceProcAddr(Device, "vkFreeDescriptorSets"));
    pfn_vkUpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSets"));
    pfn_vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(vkGetDeviceProcAddr(Device, "vkCreateFramebuffer"));
    pfn_vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(vkGetDeviceProcAddr(Device, "vkDestroyFramebuffer"));
    pfn_vkCreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass"));
    pfn_vkDestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(vkGetDeviceProcAddr(Device, "vkDestroyRenderPass"));
    pfn_vkGetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(vkGetDeviceProcAddr(Device, "vkGetRenderAreaGranularity"));
    pfn_vkCreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(vkGetDeviceProcAddr(Device, "vkCreateCommandPool"));
    pfn_vkDestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(vkGetDeviceProcAddr(Device, "vkDestroyCommandPool"));
    pfn_vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(vkGetDeviceProcAddr(Device, "vkResetCommandPool"));
    pfn_vkAllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(vkGetDeviceProcAddr(Device, "vkAllocateCommandBuffers"));
    pfn_vkFreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(vkGetDeviceProcAddr(Device, "vkFreeCommandBuffers"));
    pfn_vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(vkGetDeviceProcAddr(Device, "vkBeginCommandBuffer"));
    pfn_vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(vkGetDeviceProcAddr(Device, "vkEndCommandBuffer"));
    pfn_vkResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(vkGetDeviceProcAddr(Device, "vkResetCommandBuffer"));
    pfn_vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(vkGetDeviceProcAddr(Device, "vkCmdBindPipeline"));
    pfn_vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(vkGetDeviceProcAddr(Device, "vkCmdSetViewport"));
    pfn_vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(vkGetDeviceProcAddr(Device, "vkCmdSetScissor"));
    pfn_vkCmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(vkGetDeviceProcAddr(Device, "vkCmdSetLineWidth"));
    pfn_vkCmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBias"));
    pfn_vkCmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(vkGetDeviceProcAddr(Device, "vkCmdSetBlendConstants"));
    pfn_vkCmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBounds"));
    pfn_vkCmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilCompareMask"));
    pfn_vkCmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilWriteMask"));
    pfn_vkCmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilReference"));
    pfn_vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(vkGetDeviceProcAddr(Device, "vkCmdBindDescriptorSets"));
    pfn_vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(vkGetDeviceProcAddr(Device, "vkCmdBindIndexBuffer"));
    pfn_vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers"));
    pfn_vkCmdDraw = reinterpret_cast<PFN_vkCmdDraw>(vkGetDeviceProcAddr(Device, "vkCmdDraw"));
    pfn_vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexed"));
    pfn_vkCmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirect"));
    pfn_vkCmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirect"));
    pfn_vkCmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(vkGetDeviceProcAddr(Device, "vkCmdDispatch"));
    pfn_vkCmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(vkGetDeviceProcAddr(Device, "vkCmdDispatchIndirect"));
    pfn_vkCmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer"));
    pfn_vkCmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage"));
    pfn_vkCmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage"));
    pfn_vkCmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage"));
    pfn_vkCmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer"));
    pfn_vkCmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(vkGetDeviceProcAddr(Device, "vkCmdUpdateBuffer"));
    pfn_vkCmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(vkGetDeviceProcAddr(Device, "vkCmdFillBuffer"));
    pfn_vkCmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(vkGetDeviceProcAddr(Device, "vkCmdClearColorImage"));
    pfn_vkCmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(vkGetDeviceProcAddr(Device, "vkCmdClearDepthStencilImage"));
    pfn_vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(vkGetDeviceProcAddr(Device, "vkCmdClearAttachments"));
    pfn_vkCmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage"));
    pfn_vkCmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(vkGetDeviceProcAddr(Device, "vkCmdSetEvent"));
    pfn_vkCmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(vkGetDeviceProcAddr(Device, "vkCmdResetEvent"));
    pfn_vkCmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(vkGetDeviceProcAddr(Device, "vkCmdWaitEvents"));
    pfn_vkCmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(vkGetDeviceProcAddr(Device, "vkCmdPipelineBarrier"));
    pfn_vkCmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(vkGetDeviceProcAddr(Device, "vkCmdBeginQuery"));
    pfn_vkCmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(vkGetDeviceProcAddr(Device, "vkCmdEndQuery"));
    pfn_vkCmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(vkGetDeviceProcAddr(Device, "vkCmdResetQueryPool"));
    pfn_vkCmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(vkGetDeviceProcAddr(Device, "vkCmdWriteTimestamp"));
    pfn_vkCmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(vkGetDeviceProcAddr(Device, "vkCmdCopyQueryPoolResults"));
    pfn_vkCmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(vkGetDeviceProcAddr(Device, "vkCmdPushConstants"));
    pfn_vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass"));
    pfn_vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass"));
    pfn_vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass"));
    pfn_vkCmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(vkGetDeviceProcAddr(Device, "vkCmdExecuteCommands"));
    pfn_vkBindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(vkGetDeviceProcAddr(Device, "vkBindBufferMemory2"));
    pfn_vkBindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(vkGetDeviceProcAddr(Device, "vkBindImageMemory2"));
    pfn_vkGetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPeerMemoryFeatures"));
    pfn_vkCmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(vkGetDeviceProcAddr(Device, "vkCmdSetDeviceMask"));
    pfn_vkCmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(vkGetDeviceProcAddr(Device, "vkCmdDispatchBase"));
    pfn_vkGetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetBufferMemoryRequirements2"));
    pfn_vkGetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageMemoryRequirements2"));
    pfn_vkGetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(vkGetDeviceProcAddr(Device, "vkGetImageSparseMemoryRequirements2"));
    pfn_vkTrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(vkGetDeviceProcAddr(Device, "vkTrimCommandPool"));
    pfn_vkGetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(vkGetDeviceProcAddr(Device, "vkGetDeviceQueue2"));
    pfn_vkCreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkCreateSamplerYcbcrConversion"));
    pfn_vkDestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(vkGetDeviceProcAddr(Device, "vkDestroySamplerYcbcrConversion"));
    pfn_vkCreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkCreateDescriptorUpdateTemplate"));
    pfn_vkDestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(vkGetDeviceProcAddr(Device, "vkDestroyDescriptorUpdateTemplate"));
    pfn_vkUpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(vkGetDeviceProcAddr(Device, "vkUpdateDescriptorSetWithTemplate"));
    pfn_vkGetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(vkGetDeviceProcAddr(Device, "vkGetDescriptorSetLayoutSupport"));
    pfn_vkCmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectCount"));
    pfn_vkCmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndexedIndirectCount"));
    pfn_vkCreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(vkGetDeviceProcAddr(Device, "vkCreateRenderPass2"));
    pfn_vkCmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdBeginRenderPass2"));
    pfn_vkCmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(vkGetDeviceProcAddr(Device, "vkCmdNextSubpass2"));
    pfn_vkCmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(vkGetDeviceProcAddr(Device, "vkCmdEndRenderPass2"));
    pfn_vkResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(vkGetDeviceProcAddr(Device, "vkResetQueryPool"));
    pfn_vkGetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreCounterValue"));
    pfn_vkWaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(vkGetDeviceProcAddr(Device, "vkWaitSemaphores"));
    pfn_vkSignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(vkGetDeviceProcAddr(Device, "vkSignalSemaphore"));
    pfn_vkGetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferOpaqueCaptureAddress"));
    pfn_vkGetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(vkGetDeviceProcAddr(Device, "vkGetBufferDeviceAddress"));
    pfn_vkGetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(vkGetDeviceProcAddr(Device, "vkGetDeviceMemoryOpaqueCaptureAddress"));
    pfn_vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(vkGetDeviceProcAddr(Device, "vkCreateSwapchainKHR"));
    pfn_vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(vkGetDeviceProcAddr(Device, "vkDestroySwapchainKHR"));
    pfn_vkGetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainImagesKHR"));
    pfn_vkAcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImageKHR"));
    pfn_vkQueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(vkGetDeviceProcAddr(Device, "vkQueuePresentKHR"));
    pfn_vkGetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupPresentCapabilitiesKHR"));
    pfn_vkGetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModesKHR"));
    pfn_vkAcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(vkGetDeviceProcAddr(Device, "vkAcquireNextImage2KHR"));
    pfn_vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(vkGetDeviceProcAddr(Device, "vkCreateSharedSwapchainsKHR"));
    pfn_vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectNameEXT"));
    pfn_vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkDebugMarkerSetObjectTagEXT"));
    pfn_vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerBeginEXT"));
    pfn_vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerEndEXT"));
    pfn_vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(vkGetDeviceProcAddr(Device, "vkCmdDebugMarkerInsertEXT"));
    pfn_vkCmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(vkGetDeviceProcAddr(Device, "vkCmdBindTransformFeedbackBuffersEXT"));
    pfn_vkCmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginTransformFeedbackEXT"));
    pfn_vkCmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndTransformFeedbackEXT"));
    pfn_vkCmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginQueryIndexedEXT"));
    pfn_vkCmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndQueryIndexedEXT"));
    pfn_vkCmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdDrawIndirectByteCountEXT"));
    pfn_vkGetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewHandleNVX"));
    pfn_vkGetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(vkGetDeviceProcAddr(Device, "vkGetImageViewAddressNVX"));
    pfn_vkGetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(vkGetDeviceProcAddr(Device, "vkGetShaderInfoAMD"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleNV"));
    pfn_vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleKHR"));
    pfn_vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdKHR"));
    pfn_vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdPropertiesKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreWin32HandleKHR"));
    pfn_vkImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreFdKHR"));
    pfn_vkImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(vkGetDeviceProcAddr(Device, "vkImportSemaphoreFdKHR"));
    pfn_vkCmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetKHR"));
    pfn_vkCmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(vkGetDeviceProcAddr(Device, "vkCmdPushDescriptorSetWithTemplateKHR"));
    pfn_vkCmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginConditionalRenderingEXT"));
    pfn_vkCmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndConditionalRenderingEXT"));
    pfn_vkCmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWScalingNV"));
    pfn_vkDisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(vkGetDeviceProcAddr(Device, "vkDisplayPowerControlEXT"));
    pfn_vkRegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDeviceEventEXT"));
    pfn_vkRegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(vkGetDeviceProcAddr(Device, "vkRegisterDisplayEventEXT"));
    pfn_vkGetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(vkGetDeviceProcAddr(Device, "vkGetSwapchainCounterEXT"));
    pfn_vkGetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetRefreshCycleDurationGOOGLE"));
    pfn_vkGetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(vkGetDeviceProcAddr(Device, "vkGetPastPresentationTimingGOOGLE"));
    pfn_vkCmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDiscardRectangleEXT"));
    pfn_vkSetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(vkGetDeviceProcAddr(Device, "vkSetHdrMetadataEXT"));
    pfn_vkGetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(vkGetDeviceProcAddr(Device, "vkGetSwapchainStatusKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceWin32HandleKHR"));
    pfn_vkImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceWin32HandleKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkGetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkGetFenceFdKHR"));
    pfn_vkImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(vkGetDeviceProcAddr(Device, "vkImportFenceFdKHR"));
    pfn_vkAcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkAcquireProfilingLockKHR"));
    pfn_vkReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(vkGetDeviceProcAddr(Device, "vkReleaseProfilingLockKHR"));
    pfn_vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectNameEXT"));
    pfn_vkSetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(vkGetDeviceProcAddr(Device, "vkSetDebugUtilsObjectTagEXT"));
    pfn_vkQueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueBeginDebugUtilsLabelEXT"));
    pfn_vkQueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueEndDebugUtilsLabelEXT"));
    pfn_vkQueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkQueueInsertDebugUtilsLabelEXT"));
    pfn_vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdBeginDebugUtilsLabelEXT"));
    pfn_vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdEndDebugUtilsLabelEXT"));
    pfn_vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(vkGetDeviceProcAddr(Device, "vkCmdInsertDebugUtilsLabelEXT"));
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_vkGetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(vkGetDeviceProcAddr(Device, "vkGetAndroidHardwareBufferPropertiesANDROID"));
    pfn_vkGetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(vkGetDeviceProcAddr(Device, "vkGetMemoryAndroidHardwareBufferANDROID"));
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_vkCmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetSampleLocationsEXT"));
    pfn_vkDestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureKHR"));
    pfn_vkCmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureKHR"));
    pfn_vkCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureKHR"));
    pfn_vkCmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureToMemoryKHR"));
    pfn_vkCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(vkGetDeviceProcAddr(Device, "vkCopyAccelerationStructureToMemoryKHR"));
    pfn_vkCmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyMemoryToAccelerationStructureKHR"));
    pfn_vkCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCopyMemoryToAccelerationStructureKHR"));
    pfn_vkCmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesKHR"));
    pfn_vkWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkWriteAccelerationStructuresPropertiesKHR"));
    pfn_vkGetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(vkGetDeviceProcAddr(Device, "vkGetDeviceAccelerationStructureCompatibilityKHR"));
    pfn_vkCreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureKHR"));
    pfn_vkCmdBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresKHR"));
    pfn_vkCmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructuresIndirectKHR"));
    pfn_vkBuildAccelerationStructuresKHR = reinterpret_cast<PFN_vkBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(Device, "vkBuildAccelerationStructuresKHR"));
    pfn_vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureDeviceAddressKHR"));
    pfn_vkGetAccelerationStructureBuildSizesKHR = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureBuildSizesKHR"));
    pfn_vkCmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysKHR"));
    pfn_vkGetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupHandlesKHR"));
    pfn_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
    pfn_vkCreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesKHR"));
    pfn_vkCmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysIndirectKHR"));
    pfn_vkGetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkGetRayTracingShaderGroupStackSizeKHR"));
    pfn_vkCmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<PFN_vkCmdSetRayTracingPipelineStackSizeKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetRayTracingPipelineStackSizeKHR"));
    pfn_vkGetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetImageDrmFormatModifierPropertiesEXT"));
    pfn_vkCreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkCreateValidationCacheEXT"));
    pfn_vkDestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(vkGetDeviceProcAddr(Device, "vkDestroyValidationCacheEXT"));
    pfn_vkGetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(vkGetDeviceProcAddr(Device, "vkGetValidationCacheDataEXT"));
    pfn_vkMergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(vkGetDeviceProcAddr(Device, "vkMergeValidationCachesEXT"));
    pfn_vkCmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(vkGetDeviceProcAddr(Device, "vkCmdBindShadingRateImageNV"));
    pfn_vkCmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportShadingRatePaletteNV"));
    pfn_vkCmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCoarseSampleOrderNV"));
    pfn_vkCompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(vkGetDeviceProcAddr(Device, "vkCompileDeferredNV"));
    pfn_vkCreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCreateAccelerationStructureNV"));
    pfn_vkDestroyAccelerationStructureNV = reinterpret_cast<PFN_vkDestroyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkDestroyAccelerationStructureNV"));
    pfn_vkGetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureMemoryRequirementsNV"));
    pfn_vkBindAccelerationStructureMemoryNV = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryNV>(vkGetDeviceProcAddr(Device, "vkBindAccelerationStructureMemoryNV"));
    pfn_vkCmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdCopyAccelerationStructureNV"));
    pfn_vkCmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesNV>(vkGetDeviceProcAddr(Device, "vkCmdWriteAccelerationStructuresPropertiesNV"));
    pfn_vkCmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(vkGetDeviceProcAddr(Device, "vkCmdBuildAccelerationStructureNV"));
    pfn_vkCmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(vkGetDeviceProcAddr(Device, "vkCmdTraceRaysNV"));
    pfn_vkGetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(vkGetDeviceProcAddr(Device, "vkGetAccelerationStructureHandleNV"));
    pfn_vkCreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(vkGetDeviceProcAddr(Device, "vkCreateRayTracingPipelinesNV"));
    pfn_vkGetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(vkGetDeviceProcAddr(Device, "vkGetMemoryHostPointerPropertiesEXT"));
    pfn_vkCmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(vkGetDeviceProcAddr(Device, "vkCmdWriteBufferMarkerAMD"));
    pfn_vkGetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(vkGetDeviceProcAddr(Device, "vkGetCalibratedTimestampsEXT"));
    pfn_vkCmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksNV"));
    pfn_vkCmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectNV"));
    pfn_vkCmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(vkGetDeviceProcAddr(Device, "vkCmdDrawMeshTasksIndirectCountNV"));
    pfn_vkCmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(vkGetDeviceProcAddr(Device, "vkCmdSetExclusiveScissorNV"));
    pfn_vkCmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(vkGetDeviceProcAddr(Device, "vkCmdSetCheckpointNV"));
    pfn_vkGetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(vkGetDeviceProcAddr(Device, "vkGetQueueCheckpointDataNV"));
    pfn_vkInitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkInitializePerformanceApiINTEL"));
    pfn_vkUninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(vkGetDeviceProcAddr(Device, "vkUninitializePerformanceApiINTEL"));
    pfn_vkCmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceMarkerINTEL"));
    pfn_vkCmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceStreamMarkerINTEL"));
    pfn_vkCmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(vkGetDeviceProcAddr(Device, "vkCmdSetPerformanceOverrideINTEL"));
    pfn_vkAcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkAcquirePerformanceConfigurationINTEL"));
    pfn_vkReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkReleasePerformanceConfigurationINTEL"));
    pfn_vkQueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(vkGetDeviceProcAddr(Device, "vkQueueSetPerformanceConfigurationINTEL"));
    pfn_vkGetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(vkGetDeviceProcAddr(Device, "vkGetPerformanceParameterINTEL"));
    pfn_vkSetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(vkGetDeviceProcAddr(Device, "vkSetLocalDimmingAMD"));
    pfn_vkCmdSetFragmentShadingRateKHR = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateKHR>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkAcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkAcquireFullScreenExclusiveModeEXT"));
    pfn_vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkReleaseFullScreenExclusiveModeEXT"));
    pfn_vkGetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(vkGetDeviceProcAddr(Device, "vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_vkCmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetLineStippleEXT"));
    pfn_vkCmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetCullModeEXT"));
    pfn_vkCmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetFrontFaceEXT"));
    pfn_vkCmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetPrimitiveTopologyEXT"));
    pfn_vkCmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetViewportWithCountEXT"));
    pfn_vkCmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetScissorWithCountEXT"));
    pfn_vkCmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(vkGetDeviceProcAddr(Device, "vkCmdBindVertexBuffers2EXT"));
    pfn_vkCmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthTestEnableEXT"));
    pfn_vkCmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthWriteEnableEXT"));
    pfn_vkCmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthCompareOpEXT"));
    pfn_vkCmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetDepthBoundsTestEnableEXT"));
    pfn_vkCmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilTestEnableEXT"));
    pfn_vkCmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(vkGetDeviceProcAddr(Device, "vkCmdSetStencilOpEXT"));
    pfn_vkCreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkCreateDeferredOperationKHR"));
    pfn_vkDestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(vkGetDeviceProcAddr(Device, "vkDestroyDeferredOperationKHR"));
    pfn_vkGetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationMaxConcurrencyKHR"));
    pfn_vkGetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(vkGetDeviceProcAddr(Device, "vkGetDeferredOperationResultKHR"));
    pfn_vkDeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(vkGetDeviceProcAddr(Device, "vkDeferredOperationJoinKHR"));
    pfn_vkGetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutablePropertiesKHR"));
    pfn_vkGetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableStatisticsKHR"));
    pfn_vkGetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(vkGetDeviceProcAddr(Device, "vkGetPipelineExecutableInternalRepresentationsKHR"));
    pfn_vkCmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdExecuteGeneratedCommandsNV"));
    pfn_vkCmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(vkGetDeviceProcAddr(Device, "vkCmdPreprocessGeneratedCommandsNV"));
    pfn_vkCmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(vkGetDeviceProcAddr(Device, "vkCmdBindPipelineShaderGroupNV"));
    pfn_vkGetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(vkGetDeviceProcAddr(Device, "vkGetGeneratedCommandsMemoryRequirementsNV"));
    pfn_vkCreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkCreateIndirectCommandsLayoutNV"));
    pfn_vkDestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(vkGetDeviceProcAddr(Device, "vkDestroyIndirectCommandsLayoutNV"));
    pfn_vkCreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkCreatePrivateDataSlotEXT"));
    pfn_vkDestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(vkGetDeviceProcAddr(Device, "vkDestroyPrivateDataSlotEXT"));
    pfn_vkSetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkSetPrivateDataEXT"));
    pfn_vkGetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(vkGetDeviceProcAddr(Device, "vkGetPrivateDataEXT"));
    pfn_vkCmdSetFragmentShadingRateEnumNV = reinterpret_cast<PFN_vkCmdSetFragmentShadingRateEnumNV>(vkGetDeviceProcAddr(Device, "vkCmdSetFragmentShadingRateEnumNV"));
    pfn_vkCmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBuffer2KHR"));
    pfn_vkCmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImage2KHR"));
    pfn_vkCmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdBlitImage2KHR"));
    pfn_vkCmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyBufferToImage2KHR"));
    pfn_vkCmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(vkGetDeviceProcAddr(Device, "vkCmdCopyImageToBuffer2KHR"));
    pfn_vkCmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(vkGetDeviceProcAddr(Device, "vkCmdResolveImage2KHR"));
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
    table.vkGetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandleKHR"));
    table.vkGetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryWin32HandlePropertiesKHR"));
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdKHR"));
    table.vkGetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(vkGetDeviceProcAddr(Device, "vkGetMemoryFdPropertiesKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table.vkGetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(vkGetDeviceProcAddr(Device, "vkGetSemaphoreWin32HandleKHR"));
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
    table.vkReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(vkGetDeviceProcAddr(Device, "vkReleaseFullScreenExclusiveModeEXT"));
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

#ifdef __GNUC__
#	pragma GCC visibility pop
#endif

// clang-format on
