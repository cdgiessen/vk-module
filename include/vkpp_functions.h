#pragma once
// clang-format off
#include "vkpp_core.h"

#if !defined(VULKAN_CUSTOM_ASSERT)
#include <cassert>
#define VULKAN_CUSTOM_ASSERT assert
#endif

#if defined(WIN32)
    #define VC_EXTRALEAN
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #if defined(MemoryBarrier)
        #undef MemoryBarrier
    #endif
#elif defined(__linux__) || defined(__APPLE__)
    #include <dlfcn.h>
#endif
namespace vk {
class Loader {
    public:
    Loader(bool init_at_construction = false) noexcept {
        if(init_at_construction){
            init();
        }
    }
    Loader(PFN_vkGetInstanceProcAddr get_instance_proc_addr) noexcept : 
        get_instance_proc_addr(get_instance_proc_addr) { }
    ~Loader() noexcept {
        close();
    }
    Loader(Loader const& other) = delete;
    Loader& operator=(Loader const& other) = delete;
    Loader(Loader && other) noexcept: library(other.library), get_instance_proc_addr(other.get_instance_proc_addr) {
        other.get_instance_proc_addr = 0;
        other.library = 0;
    }
    Loader& operator=(Loader && other) noexcept {
        if (this != &other)
        {
            close();
            library = other.library; 
            get_instance_proc_addr = other.get_instance_proc_addr;
            other.get_instance_proc_addr = 0;
            other.library = 0;
        }
    }

    vk::Result init(PFN_vkGetInstanceProcAddr get_instance_proc_addr = nullptr) noexcept {
        if (get_instance_proc_addr != nullptr) {
            this->get_instance_proc_addr = get_instance_proc_addr;
            return vk::Result::Success;
        }
#if defined(__linux__)
        library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
        if (!library) library = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
        library = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
#elif defined(_WIN32)
        library = LoadLibrary(TEXT("vulkan-1.dll"));
#endif
        if (library == 0) return vk::Result::ErrorInitializationFailed;
        Load(this->get_instance_proc_addr, "vkGetInstanceProcAddr");
        if (this->get_instance_proc_addr == nullptr) return vk::Result::ErrorInitializationFailed;
        return vk::Result::Success;
    }
    void close() noexcept {
        if (library != nullptr) {
#if defined(__linux__) || defined(__APPLE__)
            dlclose(library);
#elif defined(_WIN32)
            FreeLibrary(library);
#endif
        library = 0;
        }
    }

    // Check if vulkan is loaded and ready for use
    [[nodiscard]] bool is_init() const noexcept { return get_instance_proc_addr != 0; }

    // Get `vkGetInstanceProcAddr` if it was loaded, 0 if not
    [[nodiscard]] PFN_vkGetInstanceProcAddr get() const noexcept {
        assert(get_instance_proc_addr != nullptr && "Must call init() before use");
        return get_instance_proc_addr;
    }

private:
    
    template <typename T>
    void Load(T &func_dest, const char *func_name) {
#if defined(__linux__) || defined(__APPLE__)
        func_dest = reinterpret_cast<T>(dlsym(library, func_name));
#elif defined(_WIN32)
        func_dest = reinterpret_cast<T>(GetProcAddress(library, func_name));
#endif
    }

#if defined(__linux__) || defined(__APPLE__)
    void *library = nullptr;
#elif defined(_WIN32)
    HMODULE library = nullptr;
#endif

    PFN_vkGetInstanceProcAddr get_instance_proc_addr = nullptr;
    
};

struct GlobalFunctions {
#if defined(VK_VERSION_1_0)
    PFN_vkCreateInstance pfn_CreateInstance;
    PFN_vkEnumerateInstanceExtensionProperties pfn_EnumerateInstanceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties pfn_EnumerateInstanceLayerProperties;
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    PFN_vkEnumerateInstanceVersion pfn_EnumerateInstanceVersion;
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_0)
    [[nodiscard]] Result CreateInstance(const InstanceCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Instance&  pInstance) {
        return static_cast<Result>(pfn_CreateInstance(reinterpret_cast<const VkInstanceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkInstance*>(&pInstance)));
    }
    [[nodiscard]] Result EnumerateInstanceExtensionProperties(const char* pLayerName,
        uint32_t&  pPropertyCount,
        ExtensionProperties* pProperties) {
        return static_cast<Result>(pfn_EnumerateInstanceExtensionProperties(pLayerName,
            &pPropertyCount,
            reinterpret_cast<VkExtensionProperties*>(pProperties)));
    }
    [[nodiscard]] Result EnumerateInstanceLayerProperties(uint32_t&  pPropertyCount,
        LayerProperties* pProperties) {
        return static_cast<Result>(pfn_EnumerateInstanceLayerProperties(&pPropertyCount,
            reinterpret_cast<VkLayerProperties*>(pProperties)));
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] Result EnumerateInstanceVersion(uint32_t&  pApiVersion) {
        return static_cast<Result>(pfn_EnumerateInstanceVersion(&pApiVersion));
    }
#endif //defined(VK_VERSION_1_1)
    GlobalFunctions(Loader const& loader) {
    PFN_vkGetInstanceProcAddr get_instance_proc_addr = loader.get();
#if defined(VK_VERSION_1_0)
        pfn_CreateInstance = reinterpret_cast<PFN_vkCreateInstance>(get_instance_proc_addr(nullptr,"vkCreateInstance"));
        pfn_EnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceExtensionProperties"));
        pfn_EnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceLayerProperties"));
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
        pfn_EnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceVersion"));
#endif //defined(VK_VERSION_1_1)
    };
};
struct InstanceFunctions {
    Instance const instance;
#if defined(VK_VERSION_1_0)
    PFN_vkDestroyInstance pfn_DestroyInstance;
    PFN_vkEnumeratePhysicalDevices pfn_EnumeratePhysicalDevices;
    PFN_vkGetDeviceProcAddr pfn_GetDeviceProcAddr;
    PFN_vkGetInstanceProcAddr pfn_GetInstanceProcAddr;
    PFN_vkGetPhysicalDeviceProperties pfn_GetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties pfn_GetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties pfn_GetPhysicalDeviceMemoryProperties;
    PFN_vkGetPhysicalDeviceFeatures pfn_GetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFormatProperties pfn_GetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties pfn_GetPhysicalDeviceImageFormatProperties;
    PFN_vkCreateDevice pfn_CreateDevice;
    PFN_vkEnumerateDeviceExtensionProperties pfn_EnumerateDeviceExtensionProperties;
    PFN_vkEnumerateDeviceLayerProperties pfn_EnumerateDeviceLayerProperties;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties pfn_GetPhysicalDeviceSparseImageFormatProperties;
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    PFN_vkEnumeratePhysicalDeviceGroups pfn_EnumeratePhysicalDeviceGroups;
    PFN_vkGetPhysicalDeviceFeatures2 pfn_GetPhysicalDeviceFeatures2;
    PFN_vkGetPhysicalDeviceProperties2 pfn_GetPhysicalDeviceProperties2;
    PFN_vkGetPhysicalDeviceFormatProperties2 pfn_GetPhysicalDeviceFormatProperties2;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 pfn_GetPhysicalDeviceImageFormatProperties2;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 pfn_GetPhysicalDeviceQueueFamilyProperties2;
    PFN_vkGetPhysicalDeviceMemoryProperties2 pfn_GetPhysicalDeviceMemoryProperties2;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 pfn_GetPhysicalDeviceSparseImageFormatProperties2;
    PFN_vkGetPhysicalDeviceExternalBufferProperties pfn_GetPhysicalDeviceExternalBufferProperties;
    PFN_vkGetPhysicalDeviceExternalFenceProperties pfn_GetPhysicalDeviceExternalFenceProperties;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties pfn_GetPhysicalDeviceExternalSemaphoreProperties;
#endif //defined(VK_VERSION_1_1)
#if defined(VK_KHR_surface)
    PFN_vkDestroySurfaceKHR pfn_DestroySurfaceKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfn_GetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_GetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_GetPhysicalDeviceSurfacePresentModesKHR;
#endif //defined(VK_KHR_surface)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    PFN_vkGetPhysicalDevicePresentRectanglesKHR pfn_GetPhysicalDevicePresentRectanglesKHR;
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if defined(VK_KHR_display)
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR pfn_GetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR pfn_GetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetDisplayModePropertiesKHR pfn_GetDisplayModePropertiesKHR;
    PFN_vkCreateDisplayModeKHR pfn_CreateDisplayModeKHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR pfn_GetDisplayPlaneCapabilitiesKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR pfn_CreateDisplayPlaneSurfaceKHR;
#endif //defined(VK_KHR_display)
#if defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
    PFN_vkCreateXlibSurfaceKHR pfn_CreateXlibSurfaceKHR;
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR pfn_GetPhysicalDeviceXlibPresentationSupportKHR;
#endif //defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
#if defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
    PFN_vkCreateXcbSurfaceKHR pfn_CreateXcbSurfaceKHR;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR pfn_GetPhysicalDeviceXcbPresentationSupportKHR;
#endif //defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
    PFN_vkCreateWaylandSurfaceKHR pfn_CreateWaylandSurfaceKHR;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR pfn_GetPhysicalDeviceWaylandPresentationSupportKHR;
#endif //defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
    PFN_vkCreateAndroidSurfaceKHR pfn_CreateAndroidSurfaceKHR;
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
    PFN_vkCreateWin32SurfaceKHR pfn_CreateWin32SurfaceKHR;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR pfn_GetPhysicalDeviceWin32PresentationSupportKHR;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
#if defined(VK_EXT_debug_report)
    PFN_vkCreateDebugReportCallbackEXT pfn_CreateDebugReportCallbackEXT;
    PFN_vkDestroyDebugReportCallbackEXT pfn_DestroyDebugReportCallbackEXT;
    PFN_vkDebugReportMessageEXT pfn_DebugReportMessageEXT;
#endif //defined(VK_EXT_debug_report)
#if defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
    PFN_vkCreateStreamDescriptorSurfaceGGP pfn_CreateStreamDescriptorSurfaceGGP;
#endif //defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
#if defined(VK_NV_external_memory_capabilities)
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV;
#endif //defined(VK_NV_external_memory_capabilities)
#if defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
    PFN_vkCreateViSurfaceNN pfn_CreateViSurfaceNN;
#endif //defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
#if defined(VK_EXT_direct_mode_display)
    PFN_vkReleaseDisplayEXT pfn_ReleaseDisplayEXT;
#endif //defined(VK_EXT_direct_mode_display)
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
    PFN_vkAcquireXlibDisplayEXT pfn_AcquireXlibDisplayEXT;
    PFN_vkGetRandROutputDisplayEXT pfn_GetRandROutputDisplayEXT;
#endif //defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
#if defined(VK_EXT_display_surface_counter)
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT pfn_GetPhysicalDeviceSurfaceCapabilities2EXT;
#endif //defined(VK_EXT_display_surface_counter)
#if defined(VK_KHR_performance_query)
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
#endif //defined(VK_KHR_performance_query)
#if defined(VK_KHR_get_surface_capabilities2)
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR pfn_GetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR pfn_GetPhysicalDeviceSurfaceFormats2KHR;
#endif //defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_get_display_properties2)
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR pfn_GetPhysicalDeviceDisplayProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR;
    PFN_vkGetDisplayModeProperties2KHR pfn_GetDisplayModeProperties2KHR;
    PFN_vkGetDisplayPlaneCapabilities2KHR pfn_GetDisplayPlaneCapabilities2KHR;
#endif //defined(VK_KHR_get_display_properties2)
#if defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
    PFN_vkCreateIOSSurfaceMVK pfn_CreateIOSSurfaceMVK;
#endif //defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
#if defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
    PFN_vkCreateMacOSSurfaceMVK pfn_CreateMacOSSurfaceMVK;
#endif //defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
#if defined(VK_EXT_debug_utils)
    PFN_vkCreateDebugUtilsMessengerEXT pfn_CreateDebugUtilsMessengerEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT pfn_DestroyDebugUtilsMessengerEXT;
    PFN_vkSubmitDebugUtilsMessageEXT pfn_SubmitDebugUtilsMessageEXT;
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_EXT_sample_locations)
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT pfn_GetPhysicalDeviceMultisamplePropertiesEXT;
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_EXT_calibrated_timestamps)
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT;
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
    PFN_vkCreateImagePipeSurfaceFUCHSIA pfn_CreateImagePipeSurfaceFUCHSIA;
#endif //defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
#if defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
    PFN_vkCreateMetalSurfaceEXT pfn_CreateMetalSurfaceEXT;
#endif //defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
#if defined(VK_EXT_tooling_info)
    PFN_vkGetPhysicalDeviceToolPropertiesEXT pfn_GetPhysicalDeviceToolPropertiesEXT;
#endif //defined(VK_EXT_tooling_info)
#if defined(VK_NV_cooperative_matrix)
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV;
#endif //defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_coverage_reduction_mode)
    PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#endif //defined(VK_NV_coverage_reduction_mode)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT pfn_GetPhysicalDeviceSurfacePresentModes2EXT;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_EXT_headless_surface)
    PFN_vkCreateHeadlessSurfaceEXT pfn_CreateHeadlessSurfaceEXT;
#endif //defined(VK_EXT_headless_surface)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    PFN_vkCreateDirectFBSurfaceEXT pfn_CreateDirectFBSurfaceEXT;
    PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif //defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
#if defined(VK_VERSION_1_0)
    void DestroyInstance(const AllocationCallbacks* pAllocator) {
        return pfn_DestroyInstance(instance.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result EnumeratePhysicalDevices(uint32_t&  pPhysicalDeviceCount,
        PhysicalDevice* pPhysicalDevices) {
        return static_cast<Result>(pfn_EnumeratePhysicalDevices(instance.get(),
            &pPhysicalDeviceCount,
            reinterpret_cast<VkPhysicalDevice*>(pPhysicalDevices)));
    }
    [[nodiscard]] PFN_vkVoidFunction GetDeviceProcAddr(Device device,
        const char* pName) {
        return pfn_GetDeviceProcAddr(device.get(),
            pName);
    }
    [[nodiscard]] PFN_vkVoidFunction GetInstanceProcAddr(const char* pName) {
        return pfn_GetInstanceProcAddr(instance.get(),
            pName);
    }
    void GetPhysicalDeviceProperties(PhysicalDevice physicalDevice,
        PhysicalDeviceProperties&  pProperties) {
        return pfn_GetPhysicalDeviceProperties(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties*>(&pProperties));
    }
    void GetPhysicalDeviceQueueFamilyProperties(PhysicalDevice physicalDevice,
        uint32_t&  pQueueFamilyPropertyCount,
        QueueFamilyProperties* pQueueFamilyProperties) {
        return pfn_GetPhysicalDeviceQueueFamilyProperties(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties*>(pQueueFamilyProperties));
    }
    void GetPhysicalDeviceMemoryProperties(PhysicalDevice physicalDevice,
        PhysicalDeviceMemoryProperties&  pMemoryProperties) {
        return pfn_GetPhysicalDeviceMemoryProperties(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties*>(&pMemoryProperties));
    }
    void GetPhysicalDeviceFeatures(PhysicalDevice physicalDevice,
        PhysicalDeviceFeatures&  pFeatures) {
        return pfn_GetPhysicalDeviceFeatures(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures*>(&pFeatures));
    }
    void GetPhysicalDeviceFormatProperties(PhysicalDevice physicalDevice,
        Format format,
        FormatProperties&  pFormatProperties) {
        return pfn_GetPhysicalDeviceFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties*>(&pFormatProperties));
    }
    [[nodiscard]] Result GetPhysicalDeviceImageFormatProperties(PhysicalDevice physicalDevice,
        Format format,
        ImageType type,
        ImageTiling tiling,
        ImageUsageFlags usage,
        ImageCreateFlags flags,
        ImageFormatProperties&  pImageFormatProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceImageFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            reinterpret_cast<VkImageFormatProperties*>(&pImageFormatProperties)));
    }
    [[nodiscard]] Result CreateDevice(PhysicalDevice physicalDevice,
        const DeviceCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Device&  pDevice) {
        return static_cast<Result>(pfn_CreateDevice(physicalDevice.get(),
            reinterpret_cast<const VkDeviceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDevice*>(&pDevice)));
    }
    [[nodiscard]] Result EnumerateDeviceExtensionProperties(PhysicalDevice physicalDevice,
        const char* pLayerName,
        uint32_t&  pPropertyCount,
        ExtensionProperties* pProperties) {
        return static_cast<Result>(pfn_EnumerateDeviceExtensionProperties(physicalDevice.get(),
            pLayerName,
            &pPropertyCount,
            reinterpret_cast<VkExtensionProperties*>(pProperties)));
    }
    [[nodiscard]] Result EnumerateDeviceLayerProperties(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        LayerProperties* pProperties) {
        return static_cast<Result>(pfn_EnumerateDeviceLayerProperties(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkLayerProperties*>(pProperties)));
    }
    void GetPhysicalDeviceSparseImageFormatProperties(PhysicalDevice physicalDevice,
        Format format,
        ImageType type,
        SampleCountFlagBits samples,
        ImageUsageFlags usage,
        ImageTiling tiling,
        uint32_t&  pPropertyCount,
        SparseImageFormatProperties* pProperties) {
        return pfn_GetPhysicalDeviceSparseImageFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkSampleCountFlagBits>(samples),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageTiling>(tiling),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties*>(pProperties));
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] Result EnumeratePhysicalDeviceGroups(uint32_t&  pPhysicalDeviceGroupCount,
        PhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) {
        return static_cast<Result>(pfn_EnumeratePhysicalDeviceGroups(instance.get(),
            &pPhysicalDeviceGroupCount,
            reinterpret_cast<VkPhysicalDeviceGroupProperties*>(pPhysicalDeviceGroupProperties)));
    }
    void GetPhysicalDeviceFeatures2(PhysicalDevice physicalDevice,
        PhysicalDeviceFeatures2&  pFeatures) {
        return pfn_GetPhysicalDeviceFeatures2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures2*>(&pFeatures));
    }
    void GetPhysicalDeviceProperties2(PhysicalDevice physicalDevice,
        PhysicalDeviceProperties2&  pProperties) {
        return pfn_GetPhysicalDeviceProperties2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties2*>(&pProperties));
    }
    void GetPhysicalDeviceFormatProperties2(PhysicalDevice physicalDevice,
        Format format,
        FormatProperties2&  pFormatProperties) {
        return pfn_GetPhysicalDeviceFormatProperties2(physicalDevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties2*>(&pFormatProperties));
    }
    [[nodiscard]] Result GetPhysicalDeviceImageFormatProperties2(PhysicalDevice physicalDevice,
        const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo,
        ImageFormatProperties2&  pImageFormatProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceImageFormatProperties2(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2*>(&pImageFormatInfo),
            reinterpret_cast<VkImageFormatProperties2*>(&pImageFormatProperties)));
    }
    void GetPhysicalDeviceQueueFamilyProperties2(PhysicalDevice physicalDevice,
        uint32_t&  pQueueFamilyPropertyCount,
        QueueFamilyProperties2* pQueueFamilyProperties) {
        return pfn_GetPhysicalDeviceQueueFamilyProperties2(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties2*>(pQueueFamilyProperties));
    }
    void GetPhysicalDeviceMemoryProperties2(PhysicalDevice physicalDevice,
        PhysicalDeviceMemoryProperties2&  pMemoryProperties) {
        return pfn_GetPhysicalDeviceMemoryProperties2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties2*>(&pMemoryProperties));
    }
    void GetPhysicalDeviceSparseImageFormatProperties2(PhysicalDevice physicalDevice,
        const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo,
        uint32_t&  pPropertyCount,
        SparseImageFormatProperties2* pProperties) {
        return pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2*>(&pFormatInfo),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties2*>(pProperties));
    }
    void GetPhysicalDeviceExternalBufferProperties(PhysicalDevice physicalDevice,
        const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo,
        ExternalBufferProperties&  pExternalBufferProperties) {
        return pfn_GetPhysicalDeviceExternalBufferProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo*>(&pExternalBufferInfo),
            reinterpret_cast<VkExternalBufferProperties*>(&pExternalBufferProperties));
    }
    void GetPhysicalDeviceExternalFenceProperties(PhysicalDevice physicalDevice,
        const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo,
        ExternalFenceProperties&  pExternalFenceProperties) {
        return pfn_GetPhysicalDeviceExternalFenceProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo*>(&pExternalFenceInfo),
            reinterpret_cast<VkExternalFenceProperties*>(&pExternalFenceProperties));
    }
    void GetPhysicalDeviceExternalSemaphoreProperties(PhysicalDevice physicalDevice,
        const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo,
        ExternalSemaphoreProperties&  pExternalSemaphoreProperties) {
        return pfn_GetPhysicalDeviceExternalSemaphoreProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo*>(&pExternalSemaphoreInfo),
            reinterpret_cast<VkExternalSemaphoreProperties*>(&pExternalSemaphoreProperties));
    }
#endif //defined(VK_VERSION_1_1)
#if defined(VK_KHR_surface)
    void DestroySurfaceKHR(SurfaceKHR surface,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySurfaceKHR(instance.get(),
            surface.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        SurfaceKHR surface,
        Bool32&  pSupported) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            surface.get(),
            &pSupported));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        SurfaceCapabilitiesKHR&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormatKHR* pSurfaceFormats) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(),
            surface.get(),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormatKHR*>(pSurfaceFormats)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        uint32_t&  pPresentModeCount,
        PresentModeKHR* pPresentModes) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(),
            surface.get(),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes)));
    }
#endif //defined(VK_KHR_surface)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    [[nodiscard]] Result GetPhysicalDevicePresentRectanglesKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        uint32_t&  pRectCount,
        Rect2D* pRects) {
        return static_cast<Result>(pfn_GetPhysicalDevicePresentRectanglesKHR(physicalDevice.get(),
            surface.get(),
            &pRectCount,
            reinterpret_cast<VkRect2D*>(pRects)));
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if defined(VK_KHR_display)
    [[nodiscard]] Result GetPhysicalDeviceDisplayPropertiesKHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPhysicalDeviceDisplayPlanePropertiesKHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPlanePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlanePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneSupportedDisplaysKHR(PhysicalDevice physicalDevice,
        uint32_t planeIndex,
        uint32_t&  pDisplayCount,
        DisplayKHR* pDisplays) {
        return static_cast<Result>(pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice.get(),
            planeIndex,
            &pDisplayCount,
            reinterpret_cast<VkDisplayKHR*>(pDisplays)));
    }
    [[nodiscard]] Result GetDisplayModePropertiesKHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetDisplayModePropertiesKHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result CreateDisplayModeKHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        const DisplayModeCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DisplayModeKHR&  pMode) {
        return static_cast<Result>(pfn_CreateDisplayModeKHR(physicalDevice.get(),
            display.get(),
            reinterpret_cast<const VkDisplayModeCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDisplayModeKHR*>(&pMode)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilitiesKHR(PhysicalDevice physicalDevice,
        DisplayModeKHR mode,
        uint32_t planeIndex,
        DisplayPlaneCapabilitiesKHR&  pCapabilities) {
        return static_cast<Result>(pfn_GetDisplayPlaneCapabilitiesKHR(physicalDevice.get(),
            mode.get(),
            planeIndex,
            reinterpret_cast<VkDisplayPlaneCapabilitiesKHR*>(&pCapabilities)));
    }
    [[nodiscard]] Result CreateDisplayPlaneSurfaceKHR(const DisplaySurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateDisplayPlaneSurfaceKHR(instance.get(),
            reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_KHR_display)
#if defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
    [[nodiscard]] Result CreateXlibSurfaceKHR(const XlibSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateXlibSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXlibSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXlibPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        Display&  dpy,
        VisualID visualID) {
        return pfn_GetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<Display*>(&dpy),
            static_cast<VisualID>(visualID));
    }
#endif //defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
#if defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
    [[nodiscard]] Result CreateXcbSurfaceKHR(const XcbSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateXcbSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXcbSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXcbPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        xcb_connection_t&  connection,
        xcb_visualid_t visual_id) {
        return pfn_GetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<xcb_connection_t*>(&connection),
            static_cast<xcb_visualid_t>(visual_id));
    }
#endif //defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
    [[nodiscard]] Result CreateWaylandSurfaceKHR(const WaylandSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateWaylandSurfaceKHR(instance.get(),
            reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceWaylandPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        wl_display&  display) {
        return pfn_GetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<wl_display*>(&display));
    }
#endif //defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
    [[nodiscard]] Result CreateAndroidSurfaceKHR(const AndroidSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateAndroidSurfaceKHR(instance.get(),
            reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
    [[nodiscard]] Result CreateWin32SurfaceKHR(const Win32SurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateWin32SurfaceKHR(instance.get(),
            reinterpret_cast<const VkWin32SurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceWin32PresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex) {
        return pfn_GetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
#if defined(VK_EXT_debug_report)
    [[nodiscard]] Result CreateDebugReportCallbackEXT(const DebugReportCallbackCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DebugReportCallbackEXT&  pCallback) {
        return static_cast<Result>(pfn_CreateDebugReportCallbackEXT(instance.get(),
            reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugReportCallbackEXT*>(&pCallback)));
    }
    void DestroyDebugReportCallbackEXT(DebugReportCallbackEXT callback,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDebugReportCallbackEXT(instance.get(),
            callback.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void DebugReportMessageEXT(DebugReportFlagsEXT flags,
        DebugReportObjectTypeEXT objectType,
        uint64_t object,
        size_t location,
        int32_t messageCode,
        const char* pLayerPrefix,
        const char* pMessage) {
        return pfn_DebugReportMessageEXT(instance.get(),
            static_cast<VkDebugReportFlagsEXT>(flags),
            static_cast<VkDebugReportObjectTypeEXT>(objectType),
            object,
            location,
            messageCode,
            pLayerPrefix,
            pMessage);
    }
#endif //defined(VK_EXT_debug_report)
#if defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
    [[nodiscard]] Result CreateStreamDescriptorSurfaceGGP(const StreamDescriptorSurfaceCreateInfoGGP&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateStreamDescriptorSurfaceGGP(instance.get(),
            reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
#if defined(VK_NV_external_memory_capabilities)
    [[nodiscard]] Result GetPhysicalDeviceExternalImageFormatPropertiesNV(PhysicalDevice physicalDevice,
        Format format,
        ImageType type,
        ImageTiling tiling,
        ImageUsageFlags usage,
        ImageCreateFlags flags,
        ExternalMemoryHandleTypeFlagsNV externalHandleType,
        ExternalImageFormatPropertiesNV&  pExternalImageFormatProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(externalHandleType),
            reinterpret_cast<VkExternalImageFormatPropertiesNV*>(&pExternalImageFormatProperties)));
    }
#endif //defined(VK_NV_external_memory_capabilities)
#if defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
    [[nodiscard]] Result CreateViSurfaceNN(const ViSurfaceCreateInfoNN&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateViSurfaceNN(instance.get(),
            reinterpret_cast<const VkViSurfaceCreateInfoNN*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
#if defined(VK_EXT_direct_mode_display)
    [[nodiscard]] Result ReleaseDisplayEXT(PhysicalDevice physicalDevice,
        DisplayKHR display) {
        return static_cast<Result>(pfn_ReleaseDisplayEXT(physicalDevice.get(),
            display.get()));
    }
#endif //defined(VK_EXT_direct_mode_display)
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
    [[nodiscard]] Result AcquireXlibDisplayEXT(PhysicalDevice physicalDevice,
        Display&  dpy,
        DisplayKHR display) {
        return static_cast<Result>(pfn_AcquireXlibDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            display.get()));
    }
    [[nodiscard]] Result GetRandROutputDisplayEXT(PhysicalDevice physicalDevice,
        Display&  dpy,
        RROutput rrOutput,
        DisplayKHR&  pDisplay) {
        return static_cast<Result>(pfn_GetRandROutputDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            static_cast<RROutput>(rrOutput),
            reinterpret_cast<VkDisplayKHR*>(&pDisplay)));
    }
#endif //defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
#if defined(VK_EXT_display_surface_counter)
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilities2EXT(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        SurfaceCapabilities2EXT&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilities2EXT*>(&pSurfaceCapabilities)));
    }
#endif //defined(VK_EXT_display_surface_counter)
#if defined(VK_KHR_performance_query)
    [[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        uint32_t&  pCounterCount,
        PerformanceCounterKHR* pCounters,
        PerformanceCounterDescriptionKHR* pCounterDescriptions) {
        return static_cast<Result>(pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice.get(),
            queueFamilyIndex,
            &pCounterCount,
            reinterpret_cast<VkPerformanceCounterKHR*>(pCounters),
            reinterpret_cast<VkPerformanceCounterDescriptionKHR*>(pCounterDescriptions)));
    }
    void GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(PhysicalDevice physicalDevice,
        const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo,
        uint32_t&  pNumPasses) {
        return pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice.get(),
            reinterpret_cast<const VkQueryPoolPerformanceCreateInfoKHR*>(&pPerformanceQueryCreateInfo),
            &pNumPasses);
    }
#endif //defined(VK_KHR_performance_query)
#if defined(VK_KHR_get_surface_capabilities2)
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilities2KHR(PhysicalDevice physicalDevice,
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        SurfaceCapabilities2KHR&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkSurfaceCapabilities2KHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceFormats2KHR(PhysicalDevice physicalDevice,
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormat2KHR* pSurfaceFormats) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormat2KHR*>(pSurfaceFormats)));
    }
#endif //defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_get_display_properties2)
    [[nodiscard]] Result GetPhysicalDeviceDisplayProperties2KHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPhysicalDeviceDisplayPlaneProperties2KHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPlaneProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlaneProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayModeProperties2KHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModeProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetDisplayModeProperties2KHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModeProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilities2KHR(PhysicalDevice physicalDevice,
        const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo,
        DisplayPlaneCapabilities2KHR&  pCapabilities) {
        return static_cast<Result>(pfn_GetDisplayPlaneCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkDisplayPlaneInfo2KHR*>(&pDisplayPlaneInfo),
            reinterpret_cast<VkDisplayPlaneCapabilities2KHR*>(&pCapabilities)));
    }
#endif //defined(VK_KHR_get_display_properties2)
#if defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
    [[nodiscard]] Result CreateIOSSurfaceMVK(const IOSSurfaceCreateInfoMVK&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateIOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkIOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
#if defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
    [[nodiscard]] Result CreateMacOSSurfaceMVK(const MacOSSurfaceCreateInfoMVK&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateMacOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
#if defined(VK_EXT_debug_utils)
    [[nodiscard]] Result CreateDebugUtilsMessengerEXT(const DebugUtilsMessengerCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DebugUtilsMessengerEXT&  pMessenger) {
        return static_cast<Result>(pfn_CreateDebugUtilsMessengerEXT(instance.get(),
            reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugUtilsMessengerEXT*>(&pMessenger)));
    }
    void DestroyDebugUtilsMessengerEXT(DebugUtilsMessengerEXT messenger,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDebugUtilsMessengerEXT(instance.get(),
            messenger.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void SubmitDebugUtilsMessageEXT(DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        DebugUtilsMessageTypeFlagsEXT messageTypes,
        const DebugUtilsMessengerCallbackDataEXT&  pCallbackData) {
        return pfn_SubmitDebugUtilsMessageEXT(instance.get(),
            static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity),
            static_cast<VkDebugUtilsMessageTypeFlagsEXT>(messageTypes),
            reinterpret_cast<const VkDebugUtilsMessengerCallbackDataEXT*>(&pCallbackData));
    }
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_EXT_sample_locations)
    void GetPhysicalDeviceMultisamplePropertiesEXT(PhysicalDevice physicalDevice,
        SampleCountFlagBits samples,
        MultisamplePropertiesEXT&  pMultisampleProperties) {
        return pfn_GetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice.get(),
            static_cast<VkSampleCountFlagBits>(samples),
            reinterpret_cast<VkMultisamplePropertiesEXT*>(&pMultisampleProperties));
    }
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_EXT_calibrated_timestamps)
    [[nodiscard]] Result GetPhysicalDeviceCalibrateableTimeDomainsEXT(PhysicalDevice physicalDevice,
        uint32_t&  pTimeDomainCount,
        TimeDomainEXT* pTimeDomains) {
        return static_cast<Result>(pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice.get(),
            &pTimeDomainCount,
            reinterpret_cast<VkTimeDomainEXT*>(pTimeDomains)));
    }
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
    [[nodiscard]] Result CreateImagePipeSurfaceFUCHSIA(const ImagePipeSurfaceCreateInfoFUCHSIA&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateImagePipeSurfaceFUCHSIA(instance.get(),
            reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
#if defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
    [[nodiscard]] Result CreateMetalSurfaceEXT(const MetalSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateMetalSurfaceEXT(instance.get(),
            reinterpret_cast<const VkMetalSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
#if defined(VK_EXT_tooling_info)
    [[nodiscard]] Result GetPhysicalDeviceToolPropertiesEXT(PhysicalDevice physicalDevice,
        uint32_t&  pToolCount,
        PhysicalDeviceToolPropertiesEXT* pToolProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceToolPropertiesEXT(physicalDevice.get(),
            &pToolCount,
            reinterpret_cast<VkPhysicalDeviceToolPropertiesEXT*>(pToolProperties)));
    }
#endif //defined(VK_EXT_tooling_info)
#if defined(VK_NV_cooperative_matrix)
    [[nodiscard]] Result GetPhysicalDeviceCooperativeMatrixPropertiesNV(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        CooperativeMatrixPropertiesNV* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkCooperativeMatrixPropertiesNV*>(pProperties)));
    }
#endif //defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_coverage_reduction_mode)
    [[nodiscard]] Result GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(PhysicalDevice physicalDevice,
        uint32_t&  pCombinationCount,
        FramebufferMixedSamplesCombinationNV* pCombinations) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice.get(),
            &pCombinationCount,
            reinterpret_cast<VkFramebufferMixedSamplesCombinationNV*>(pCombinations)));
    }
#endif //defined(VK_NV_coverage_reduction_mode)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    [[nodiscard]] Result GetPhysicalDeviceSurfacePresentModes2EXT(PhysicalDevice physicalDevice,
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        uint32_t&  pPresentModeCount,
        PresentModeKHR* pPresentModes) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_EXT_headless_surface)
    [[nodiscard]] Result CreateHeadlessSurfaceEXT(const HeadlessSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateHeadlessSurfaceEXT(instance.get(),
            reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
#endif //defined(VK_EXT_headless_surface)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    [[nodiscard]] Result CreateDirectFBSurfaceEXT(const DirectFBSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateDirectFBSurfaceEXT(instance.get(),
            reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceDirectFBPresentationSupportEXT(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        IDirectFB&  dfb) {
        return pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<IDirectFB*>(&dfb));
    }
#endif //defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    InstanceFunctions(Loader const& loader, Instance instance):instance(instance) { 
    PFN_vkGetInstanceProcAddr get_instance_proc_addr = loader.get();
#if defined(VK_VERSION_1_0)
        pfn_DestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(get_instance_proc_addr(instance.get(),"vkDestroyInstance"));
        pfn_EnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(get_instance_proc_addr(instance.get(),"vkEnumeratePhysicalDevices"));
        pfn_GetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(get_instance_proc_addr(instance.get(),"vkGetDeviceProcAddr"));
        pfn_GetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(get_instance_proc_addr(instance.get(),"vkGetInstanceProcAddr"));
        pfn_GetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceProperties"));
        pfn_GetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceQueueFamilyProperties"));
        pfn_GetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceMemoryProperties"));
        pfn_GetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFeatures"));
        pfn_GetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFormatProperties"));
        pfn_GetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceImageFormatProperties"));
        pfn_CreateDevice = reinterpret_cast<PFN_vkCreateDevice>(get_instance_proc_addr(instance.get(),"vkCreateDevice"));
        pfn_EnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(get_instance_proc_addr(instance.get(),"vkEnumerateDeviceExtensionProperties"));
        pfn_EnumerateDeviceLayerProperties = reinterpret_cast<PFN_vkEnumerateDeviceLayerProperties>(get_instance_proc_addr(instance.get(),"vkEnumerateDeviceLayerProperties"));
        pfn_GetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSparseImageFormatProperties"));
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
        pfn_EnumeratePhysicalDeviceGroups = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(get_instance_proc_addr(instance.get(),"vkEnumeratePhysicalDeviceGroups"));
        pfn_GetPhysicalDeviceFeatures2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFeatures2"));
        pfn_GetPhysicalDeviceProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceProperties2"));
        pfn_GetPhysicalDeviceFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFormatProperties2"));
        pfn_GetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceImageFormatProperties2"));
        pfn_GetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceQueueFamilyProperties2"));
        pfn_GetPhysicalDeviceMemoryProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceMemoryProperties2"));
        pfn_GetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<PFN_vkGetPhysicalDeviceSparseImageFormatProperties2>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSparseImageFormatProperties2"));
        pfn_GetPhysicalDeviceExternalBufferProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalBufferProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceExternalBufferProperties"));
        pfn_GetPhysicalDeviceExternalFenceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalFenceProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceExternalFenceProperties"));
        pfn_GetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalSemaphoreProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceExternalSemaphoreProperties"));
#endif //defined(VK_VERSION_1_1)
#if defined(VK_KHR_surface)
        pfn_DestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(get_instance_proc_addr(instance.get(),"vkDestroySurfaceKHR"));
        pfn_GetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceSupportKHR"));
        pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
        pfn_GetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceFormatsKHR"));
        pfn_GetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfacePresentModesKHR"));
#endif //defined(VK_KHR_surface)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
        pfn_GetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<PFN_vkGetPhysicalDevicePresentRectanglesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDevicePresentRectanglesKHR"));
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if defined(VK_KHR_display)
        pfn_GetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPropertiesKHR"));
        pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
        pfn_GetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneSupportedDisplaysKHR"));
        pfn_GetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayModePropertiesKHR"));
        pfn_CreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(get_instance_proc_addr(instance.get(),"vkCreateDisplayModeKHR"));
        pfn_GetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneCapabilitiesKHR"));
        pfn_CreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateDisplayPlaneSurfaceKHR"));
#endif //defined(VK_KHR_display)
#if defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
        pfn_CreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateXlibSurfaceKHR"));
        pfn_GetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif //defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
#if defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
        pfn_CreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateXcbSurfaceKHR"));
        pfn_GetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif //defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
        pfn_CreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateWaylandSurfaceKHR"));
        pfn_GetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif //defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
        pfn_CreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateAndroidSurfaceKHR"));
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
        pfn_CreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateWin32SurfaceKHR"));
        pfn_GetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
#if defined(VK_EXT_debug_report)
        pfn_CreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(get_instance_proc_addr(instance.get(),"vkCreateDebugReportCallbackEXT"));
        pfn_DestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(get_instance_proc_addr(instance.get(),"vkDestroyDebugReportCallbackEXT"));
        pfn_DebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(get_instance_proc_addr(instance.get(),"vkDebugReportMessageEXT"));
#endif //defined(VK_EXT_debug_report)
#if defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
        pfn_CreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(get_instance_proc_addr(instance.get(),"vkCreateStreamDescriptorSurfaceGGP"));
#endif //defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
#if defined(VK_NV_external_memory_capabilities)
        pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#endif //defined(VK_NV_external_memory_capabilities)
#if defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
        pfn_CreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(get_instance_proc_addr(instance.get(),"vkCreateViSurfaceNN"));
#endif //defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
#if defined(VK_EXT_direct_mode_display)
        pfn_ReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(get_instance_proc_addr(instance.get(),"vkReleaseDisplayEXT"));
#endif //defined(VK_EXT_direct_mode_display)
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
        pfn_AcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(get_instance_proc_addr(instance.get(),"vkAcquireXlibDisplayEXT"));
        pfn_GetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(get_instance_proc_addr(instance.get(),"vkGetRandROutputDisplayEXT"));
#endif //defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
#if defined(VK_EXT_display_surface_counter)
        pfn_GetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
#endif //defined(VK_EXT_display_surface_counter)
#if defined(VK_KHR_performance_query)
        pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(get_instance_proc_addr(instance.get(),"vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
        pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
#endif //defined(VK_KHR_performance_query)
#if defined(VK_KHR_get_surface_capabilities2)
        pfn_GetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
        pfn_GetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceFormats2KHR"));
#endif //defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_get_display_properties2)
        pfn_GetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayProperties2KHR"));
        pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
        pfn_GetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayModeProperties2KHR"));
        pfn_GetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneCapabilities2KHR"));
#endif //defined(VK_KHR_get_display_properties2)
#if defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
        pfn_CreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(get_instance_proc_addr(instance.get(),"vkCreateIOSSurfaceMVK"));
#endif //defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
#if defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
        pfn_CreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(get_instance_proc_addr(instance.get(),"vkCreateMacOSSurfaceMVK"));
#endif //defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
#if defined(VK_EXT_debug_utils)
        pfn_CreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(get_instance_proc_addr(instance.get(),"vkCreateDebugUtilsMessengerEXT"));
        pfn_DestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(get_instance_proc_addr(instance.get(),"vkDestroyDebugUtilsMessengerEXT"));
        pfn_SubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(get_instance_proc_addr(instance.get(),"vkSubmitDebugUtilsMessageEXT"));
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_EXT_sample_locations)
        pfn_GetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceMultisamplePropertiesEXT"));
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_EXT_calibrated_timestamps)
        pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
        pfn_CreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(get_instance_proc_addr(instance.get(),"vkCreateImagePipeSurfaceFUCHSIA"));
#endif //defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
#if defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
        pfn_CreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateMetalSurfaceEXT"));
#endif //defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
#if defined(VK_EXT_tooling_info)
        pfn_GetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceToolPropertiesEXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceToolPropertiesEXT"));
#endif //defined(VK_EXT_tooling_info)
#if defined(VK_NV_cooperative_matrix)
        pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
#endif //defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_coverage_reduction_mode)
        pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#endif //defined(VK_NV_coverage_reduction_mode)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
        pfn_GetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_EXT_headless_surface)
        pfn_CreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateHeadlessSurfaceEXT"));
#endif //defined(VK_EXT_headless_surface)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
        pfn_CreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateDirectFBSurfaceEXT"));
        pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif //defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    };
};
struct DeviceFunctions {
    Device const device;
#if defined(VK_VERSION_1_0)
    PFN_vkDestroyDevice pfn_DestroyDevice;
    PFN_vkGetDeviceQueue pfn_GetDeviceQueue;
    PFN_vkQueueSubmit pfn_QueueSubmit;
    PFN_vkQueueWaitIdle pfn_QueueWaitIdle;
    PFN_vkDeviceWaitIdle pfn_DeviceWaitIdle;
    PFN_vkAllocateMemory pfn_AllocateMemory;
    PFN_vkFreeMemory pfn_FreeMemory;
    PFN_vkMapMemory pfn_MapMemory;
    PFN_vkUnmapMemory pfn_UnmapMemory;
    PFN_vkFlushMappedMemoryRanges pfn_FlushMappedMemoryRanges;
    PFN_vkInvalidateMappedMemoryRanges pfn_InvalidateMappedMemoryRanges;
    PFN_vkGetDeviceMemoryCommitment pfn_GetDeviceMemoryCommitment;
    PFN_vkGetBufferMemoryRequirements pfn_GetBufferMemoryRequirements;
    PFN_vkBindBufferMemory pfn_BindBufferMemory;
    PFN_vkGetImageMemoryRequirements pfn_GetImageMemoryRequirements;
    PFN_vkBindImageMemory pfn_BindImageMemory;
    PFN_vkGetImageSparseMemoryRequirements pfn_GetImageSparseMemoryRequirements;
    PFN_vkQueueBindSparse pfn_QueueBindSparse;
    PFN_vkCreateFence pfn_CreateFence;
    PFN_vkDestroyFence pfn_DestroyFence;
    PFN_vkResetFences pfn_ResetFences;
    PFN_vkGetFenceStatus pfn_GetFenceStatus;
    PFN_vkWaitForFences pfn_WaitForFences;
    PFN_vkCreateSemaphore pfn_CreateSemaphore;
    PFN_vkDestroySemaphore pfn_DestroySemaphore;
    PFN_vkCreateEvent pfn_CreateEvent;
    PFN_vkDestroyEvent pfn_DestroyEvent;
    PFN_vkGetEventStatus pfn_GetEventStatus;
    PFN_vkSetEvent pfn_SetEvent;
    PFN_vkResetEvent pfn_ResetEvent;
    PFN_vkCreateQueryPool pfn_CreateQueryPool;
    PFN_vkDestroyQueryPool pfn_DestroyQueryPool;
    PFN_vkGetQueryPoolResults pfn_GetQueryPoolResults;
    PFN_vkCreateBuffer pfn_CreateBuffer;
    PFN_vkDestroyBuffer pfn_DestroyBuffer;
    PFN_vkCreateBufferView pfn_CreateBufferView;
    PFN_vkDestroyBufferView pfn_DestroyBufferView;
    PFN_vkCreateImage pfn_CreateImage;
    PFN_vkDestroyImage pfn_DestroyImage;
    PFN_vkGetImageSubresourceLayout pfn_GetImageSubresourceLayout;
    PFN_vkCreateImageView pfn_CreateImageView;
    PFN_vkDestroyImageView pfn_DestroyImageView;
    PFN_vkCreateShaderModule pfn_CreateShaderModule;
    PFN_vkDestroyShaderModule pfn_DestroyShaderModule;
    PFN_vkCreatePipelineCache pfn_CreatePipelineCache;
    PFN_vkDestroyPipelineCache pfn_DestroyPipelineCache;
    PFN_vkGetPipelineCacheData pfn_GetPipelineCacheData;
    PFN_vkMergePipelineCaches pfn_MergePipelineCaches;
    PFN_vkCreateGraphicsPipelines pfn_CreateGraphicsPipelines;
    PFN_vkCreateComputePipelines pfn_CreateComputePipelines;
    PFN_vkDestroyPipeline pfn_DestroyPipeline;
    PFN_vkCreatePipelineLayout pfn_CreatePipelineLayout;
    PFN_vkDestroyPipelineLayout pfn_DestroyPipelineLayout;
    PFN_vkCreateSampler pfn_CreateSampler;
    PFN_vkDestroySampler pfn_DestroySampler;
    PFN_vkCreateDescriptorSetLayout pfn_CreateDescriptorSetLayout;
    PFN_vkDestroyDescriptorSetLayout pfn_DestroyDescriptorSetLayout;
    PFN_vkCreateDescriptorPool pfn_CreateDescriptorPool;
    PFN_vkDestroyDescriptorPool pfn_DestroyDescriptorPool;
    PFN_vkResetDescriptorPool pfn_ResetDescriptorPool;
    PFN_vkAllocateDescriptorSets pfn_AllocateDescriptorSets;
    PFN_vkFreeDescriptorSets pfn_FreeDescriptorSets;
    PFN_vkUpdateDescriptorSets pfn_UpdateDescriptorSets;
    PFN_vkCreateFramebuffer pfn_CreateFramebuffer;
    PFN_vkDestroyFramebuffer pfn_DestroyFramebuffer;
    PFN_vkCreateRenderPass pfn_CreateRenderPass;
    PFN_vkDestroyRenderPass pfn_DestroyRenderPass;
    PFN_vkGetRenderAreaGranularity pfn_GetRenderAreaGranularity;
    PFN_vkCreateCommandPool pfn_CreateCommandPool;
    PFN_vkDestroyCommandPool pfn_DestroyCommandPool;
    PFN_vkResetCommandPool pfn_ResetCommandPool;
    PFN_vkAllocateCommandBuffers pfn_AllocateCommandBuffers;
    PFN_vkFreeCommandBuffers pfn_FreeCommandBuffers;
    PFN_vkBeginCommandBuffer pfn_BeginCommandBuffer;
    PFN_vkEndCommandBuffer pfn_EndCommandBuffer;
    PFN_vkResetCommandBuffer pfn_ResetCommandBuffer;
    PFN_vkCmdBindPipeline pfn_CmdBindPipeline;
    PFN_vkCmdSetViewport pfn_CmdSetViewport;
    PFN_vkCmdSetScissor pfn_CmdSetScissor;
    PFN_vkCmdSetLineWidth pfn_CmdSetLineWidth;
    PFN_vkCmdSetDepthBias pfn_CmdSetDepthBias;
    PFN_vkCmdSetBlendConstants pfn_CmdSetBlendConstants;
    PFN_vkCmdSetDepthBounds pfn_CmdSetDepthBounds;
    PFN_vkCmdSetStencilCompareMask pfn_CmdSetStencilCompareMask;
    PFN_vkCmdSetStencilWriteMask pfn_CmdSetStencilWriteMask;
    PFN_vkCmdSetStencilReference pfn_CmdSetStencilReference;
    PFN_vkCmdBindDescriptorSets pfn_CmdBindDescriptorSets;
    PFN_vkCmdBindIndexBuffer pfn_CmdBindIndexBuffer;
    PFN_vkCmdBindVertexBuffers pfn_CmdBindVertexBuffers;
    PFN_vkCmdDraw pfn_CmdDraw;
    PFN_vkCmdDrawIndexed pfn_CmdDrawIndexed;
    PFN_vkCmdDrawIndirect pfn_CmdDrawIndirect;
    PFN_vkCmdDrawIndexedIndirect pfn_CmdDrawIndexedIndirect;
    PFN_vkCmdDispatch pfn_CmdDispatch;
    PFN_vkCmdDispatchIndirect pfn_CmdDispatchIndirect;
    PFN_vkCmdCopyBuffer pfn_CmdCopyBuffer;
    PFN_vkCmdCopyImage pfn_CmdCopyImage;
    PFN_vkCmdBlitImage pfn_CmdBlitImage;
    PFN_vkCmdCopyBufferToImage pfn_CmdCopyBufferToImage;
    PFN_vkCmdCopyImageToBuffer pfn_CmdCopyImageToBuffer;
    PFN_vkCmdUpdateBuffer pfn_CmdUpdateBuffer;
    PFN_vkCmdFillBuffer pfn_CmdFillBuffer;
    PFN_vkCmdClearColorImage pfn_CmdClearColorImage;
    PFN_vkCmdClearDepthStencilImage pfn_CmdClearDepthStencilImage;
    PFN_vkCmdClearAttachments pfn_CmdClearAttachments;
    PFN_vkCmdResolveImage pfn_CmdResolveImage;
    PFN_vkCmdSetEvent pfn_CmdSetEvent;
    PFN_vkCmdResetEvent pfn_CmdResetEvent;
    PFN_vkCmdWaitEvents pfn_CmdWaitEvents;
    PFN_vkCmdPipelineBarrier pfn_CmdPipelineBarrier;
    PFN_vkCmdBeginQuery pfn_CmdBeginQuery;
    PFN_vkCmdEndQuery pfn_CmdEndQuery;
    PFN_vkCmdResetQueryPool pfn_CmdResetQueryPool;
    PFN_vkCmdWriteTimestamp pfn_CmdWriteTimestamp;
    PFN_vkCmdCopyQueryPoolResults pfn_CmdCopyQueryPoolResults;
    PFN_vkCmdPushConstants pfn_CmdPushConstants;
    PFN_vkCmdBeginRenderPass pfn_CmdBeginRenderPass;
    PFN_vkCmdNextSubpass pfn_CmdNextSubpass;
    PFN_vkCmdEndRenderPass pfn_CmdEndRenderPass;
    PFN_vkCmdExecuteCommands pfn_CmdExecuteCommands;
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    PFN_vkBindBufferMemory2 pfn_BindBufferMemory2;
    PFN_vkBindImageMemory2 pfn_BindImageMemory2;
    PFN_vkGetDeviceGroupPeerMemoryFeatures pfn_GetDeviceGroupPeerMemoryFeatures;
    PFN_vkCmdSetDeviceMask pfn_CmdSetDeviceMask;
    PFN_vkCmdDispatchBase pfn_CmdDispatchBase;
    PFN_vkGetBufferMemoryRequirements2 pfn_GetBufferMemoryRequirements2;
    PFN_vkGetImageMemoryRequirements2 pfn_GetImageMemoryRequirements2;
    PFN_vkGetImageSparseMemoryRequirements2 pfn_GetImageSparseMemoryRequirements2;
    PFN_vkTrimCommandPool pfn_TrimCommandPool;
    PFN_vkGetDeviceQueue2 pfn_GetDeviceQueue2;
    PFN_vkCreateSamplerYcbcrConversion pfn_CreateSamplerYcbcrConversion;
    PFN_vkDestroySamplerYcbcrConversion pfn_DestroySamplerYcbcrConversion;
    PFN_vkCreateDescriptorUpdateTemplate pfn_CreateDescriptorUpdateTemplate;
    PFN_vkDestroyDescriptorUpdateTemplate pfn_DestroyDescriptorUpdateTemplate;
    PFN_vkUpdateDescriptorSetWithTemplate pfn_UpdateDescriptorSetWithTemplate;
    PFN_vkGetDescriptorSetLayoutSupport pfn_GetDescriptorSetLayoutSupport;
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
    PFN_vkCmdDrawIndirectCount pfn_CmdDrawIndirectCount;
    PFN_vkCmdDrawIndexedIndirectCount pfn_CmdDrawIndexedIndirectCount;
    PFN_vkCreateRenderPass2 pfn_CreateRenderPass2;
    PFN_vkCmdBeginRenderPass2 pfn_CmdBeginRenderPass2;
    PFN_vkCmdNextSubpass2 pfn_CmdNextSubpass2;
    PFN_vkCmdEndRenderPass2 pfn_CmdEndRenderPass2;
    PFN_vkResetQueryPool pfn_ResetQueryPool;
    PFN_vkGetSemaphoreCounterValue pfn_GetSemaphoreCounterValue;
    PFN_vkWaitSemaphores pfn_WaitSemaphores;
    PFN_vkSignalSemaphore pfn_SignalSemaphore;
    PFN_vkGetBufferOpaqueCaptureAddress pfn_GetBufferOpaqueCaptureAddress;
    PFN_vkGetBufferDeviceAddress pfn_GetBufferDeviceAddress;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress pfn_GetDeviceMemoryOpaqueCaptureAddress;
#endif //defined(VK_VERSION_1_2)
#if defined(VK_KHR_swapchain)
    PFN_vkCreateSwapchainKHR pfn_CreateSwapchainKHR;
    PFN_vkDestroySwapchainKHR pfn_DestroySwapchainKHR;
    PFN_vkGetSwapchainImagesKHR pfn_GetSwapchainImagesKHR;
    PFN_vkAcquireNextImageKHR pfn_AcquireNextImageKHR;
    PFN_vkQueuePresentKHR pfn_QueuePresentKHR;
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR pfn_GetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR pfn_GetDeviceGroupSurfacePresentModesKHR;
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    PFN_vkAcquireNextImage2KHR pfn_AcquireNextImage2KHR;
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
#if defined(VK_KHR_display_swapchain)
    PFN_vkCreateSharedSwapchainsKHR pfn_CreateSharedSwapchainsKHR;
#endif //defined(VK_KHR_display_swapchain)
#if defined(VK_EXT_debug_marker)
    PFN_vkDebugMarkerSetObjectNameEXT pfn_DebugMarkerSetObjectNameEXT;
    PFN_vkDebugMarkerSetObjectTagEXT pfn_DebugMarkerSetObjectTagEXT;
    PFN_vkCmdDebugMarkerBeginEXT pfn_CmdDebugMarkerBeginEXT;
    PFN_vkCmdDebugMarkerEndEXT pfn_CmdDebugMarkerEndEXT;
    PFN_vkCmdDebugMarkerInsertEXT pfn_CmdDebugMarkerInsertEXT;
#endif //defined(VK_EXT_debug_marker)
#if defined(VK_EXT_transform_feedback)
    PFN_vkCmdBindTransformFeedbackBuffersEXT pfn_CmdBindTransformFeedbackBuffersEXT;
    PFN_vkCmdBeginTransformFeedbackEXT pfn_CmdBeginTransformFeedbackEXT;
    PFN_vkCmdEndTransformFeedbackEXT pfn_CmdEndTransformFeedbackEXT;
    PFN_vkCmdBeginQueryIndexedEXT pfn_CmdBeginQueryIndexedEXT;
    PFN_vkCmdEndQueryIndexedEXT pfn_CmdEndQueryIndexedEXT;
    PFN_vkCmdDrawIndirectByteCountEXT pfn_CmdDrawIndirectByteCountEXT;
#endif //defined(VK_EXT_transform_feedback)
#if defined(VK_NVX_image_view_handle)
    PFN_vkGetImageViewHandleNVX pfn_GetImageViewHandleNVX;
    PFN_vkGetImageViewAddressNVX pfn_GetImageViewAddressNVX;
#endif //defined(VK_NVX_image_view_handle)
#if defined(VK_AMD_shader_info)
    PFN_vkGetShaderInfoAMD pfn_GetShaderInfoAMD;
#endif //defined(VK_AMD_shader_info)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
    PFN_vkGetMemoryWin32HandleNV pfn_GetMemoryWin32HandleNV;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
    PFN_vkGetMemoryWin32HandleKHR pfn_GetMemoryWin32HandleKHR;
    PFN_vkGetMemoryWin32HandlePropertiesKHR pfn_GetMemoryWin32HandlePropertiesKHR;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
#if defined(VK_KHR_external_memory_fd)
    PFN_vkGetMemoryFdKHR pfn_GetMemoryFdKHR;
    PFN_vkGetMemoryFdPropertiesKHR pfn_GetMemoryFdPropertiesKHR;
#endif //defined(VK_KHR_external_memory_fd)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
    PFN_vkGetSemaphoreWin32HandleKHR pfn_GetSemaphoreWin32HandleKHR;
    PFN_vkImportSemaphoreWin32HandleKHR pfn_ImportSemaphoreWin32HandleKHR;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
#if defined(VK_KHR_external_semaphore_fd)
    PFN_vkGetSemaphoreFdKHR pfn_GetSemaphoreFdKHR;
    PFN_vkImportSemaphoreFdKHR pfn_ImportSemaphoreFdKHR;
#endif //defined(VK_KHR_external_semaphore_fd)
#if defined(VK_KHR_push_descriptor)
    PFN_vkCmdPushDescriptorSetKHR pfn_CmdPushDescriptorSetKHR;
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
    PFN_vkCmdPushDescriptorSetWithTemplateKHR pfn_CmdPushDescriptorSetWithTemplateKHR;
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
#if defined(VK_EXT_conditional_rendering)
    PFN_vkCmdBeginConditionalRenderingEXT pfn_CmdBeginConditionalRenderingEXT;
    PFN_vkCmdEndConditionalRenderingEXT pfn_CmdEndConditionalRenderingEXT;
#endif //defined(VK_EXT_conditional_rendering)
#if defined(VK_NV_clip_space_w_scaling)
    PFN_vkCmdSetViewportWScalingNV pfn_CmdSetViewportWScalingNV;
#endif //defined(VK_NV_clip_space_w_scaling)
#if defined(VK_EXT_display_control)
    PFN_vkDisplayPowerControlEXT pfn_DisplayPowerControlEXT;
    PFN_vkRegisterDeviceEventEXT pfn_RegisterDeviceEventEXT;
    PFN_vkRegisterDisplayEventEXT pfn_RegisterDisplayEventEXT;
    PFN_vkGetSwapchainCounterEXT pfn_GetSwapchainCounterEXT;
#endif //defined(VK_EXT_display_control)
#if defined(VK_GOOGLE_display_timing)
    PFN_vkGetRefreshCycleDurationGOOGLE pfn_GetRefreshCycleDurationGOOGLE;
    PFN_vkGetPastPresentationTimingGOOGLE pfn_GetPastPresentationTimingGOOGLE;
#endif //defined(VK_GOOGLE_display_timing)
#if defined(VK_EXT_discard_rectangles)
    PFN_vkCmdSetDiscardRectangleEXT pfn_CmdSetDiscardRectangleEXT;
#endif //defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_hdr_metadata)
    PFN_vkSetHdrMetadataEXT pfn_SetHdrMetadataEXT;
#endif //defined(VK_EXT_hdr_metadata)
#if defined(VK_KHR_shared_presentable_image)
    PFN_vkGetSwapchainStatusKHR pfn_GetSwapchainStatusKHR;
#endif //defined(VK_KHR_shared_presentable_image)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
    PFN_vkGetFenceWin32HandleKHR pfn_GetFenceWin32HandleKHR;
    PFN_vkImportFenceWin32HandleKHR pfn_ImportFenceWin32HandleKHR;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
#if defined(VK_KHR_external_fence_fd)
    PFN_vkGetFenceFdKHR pfn_GetFenceFdKHR;
    PFN_vkImportFenceFdKHR pfn_ImportFenceFdKHR;
#endif //defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_performance_query)
    PFN_vkAcquireProfilingLockKHR pfn_AcquireProfilingLockKHR;
    PFN_vkReleaseProfilingLockKHR pfn_ReleaseProfilingLockKHR;
#endif //defined(VK_KHR_performance_query)
#if defined(VK_EXT_debug_utils)
    PFN_vkSetDebugUtilsObjectNameEXT pfn_SetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT pfn_SetDebugUtilsObjectTagEXT;
    PFN_vkQueueBeginDebugUtilsLabelEXT pfn_QueueBeginDebugUtilsLabelEXT;
    PFN_vkQueueEndDebugUtilsLabelEXT pfn_QueueEndDebugUtilsLabelEXT;
    PFN_vkQueueInsertDebugUtilsLabelEXT pfn_QueueInsertDebugUtilsLabelEXT;
    PFN_vkCmdBeginDebugUtilsLabelEXT pfn_CmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdEndDebugUtilsLabelEXT pfn_CmdEndDebugUtilsLabelEXT;
    PFN_vkCmdInsertDebugUtilsLabelEXT pfn_CmdInsertDebugUtilsLabelEXT;
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID pfn_GetAndroidHardwareBufferPropertiesANDROID;
    PFN_vkGetMemoryAndroidHardwareBufferANDROID pfn_GetMemoryAndroidHardwareBufferANDROID;
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
#if defined(VK_EXT_sample_locations)
    PFN_vkCmdSetSampleLocationsEXT pfn_CmdSetSampleLocationsEXT;
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
    PFN_vkDestroyAccelerationStructureKHR pfn_DestroyAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureMemoryRequirementsKHR pfn_GetAccelerationStructureMemoryRequirementsKHR;
    PFN_vkBindAccelerationStructureMemoryKHR pfn_BindAccelerationStructureMemoryKHR;
    PFN_vkCmdCopyAccelerationStructureKHR pfn_CmdCopyAccelerationStructureKHR;
    PFN_vkCopyAccelerationStructureKHR pfn_CopyAccelerationStructureKHR;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR pfn_CmdCopyAccelerationStructureToMemoryKHR;
    PFN_vkCopyAccelerationStructureToMemoryKHR pfn_CopyAccelerationStructureToMemoryKHR;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR pfn_CmdCopyMemoryToAccelerationStructureKHR;
    PFN_vkCopyMemoryToAccelerationStructureKHR pfn_CopyMemoryToAccelerationStructureKHR;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR pfn_CmdWriteAccelerationStructuresPropertiesKHR;
    PFN_vkWriteAccelerationStructuresPropertiesKHR pfn_WriteAccelerationStructuresPropertiesKHR;
    PFN_vkCmdTraceRaysKHR pfn_CmdTraceRaysKHR;
    PFN_vkGetRayTracingShaderGroupHandlesKHR pfn_GetRayTracingShaderGroupHandlesKHR;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR;
    PFN_vkCreateRayTracingPipelinesKHR pfn_CreateRayTracingPipelinesKHR;
    PFN_vkCmdTraceRaysIndirectKHR pfn_CmdTraceRaysIndirectKHR;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR pfn_GetDeviceAccelerationStructureCompatibilityKHR;
    PFN_vkCreateAccelerationStructureKHR pfn_CreateAccelerationStructureKHR;
    PFN_vkCmdBuildAccelerationStructureKHR pfn_CmdBuildAccelerationStructureKHR;
    PFN_vkCmdBuildAccelerationStructureIndirectKHR pfn_CmdBuildAccelerationStructureIndirectKHR;
    PFN_vkBuildAccelerationStructureKHR pfn_BuildAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_GetAccelerationStructureDeviceAddressKHR;
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
#if defined(VK_EXT_image_drm_format_modifier)
    PFN_vkGetImageDrmFormatModifierPropertiesEXT pfn_GetImageDrmFormatModifierPropertiesEXT;
#endif //defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_validation_cache)
    PFN_vkCreateValidationCacheEXT pfn_CreateValidationCacheEXT;
    PFN_vkDestroyValidationCacheEXT pfn_DestroyValidationCacheEXT;
    PFN_vkGetValidationCacheDataEXT pfn_GetValidationCacheDataEXT;
    PFN_vkMergeValidationCachesEXT pfn_MergeValidationCachesEXT;
#endif //defined(VK_EXT_validation_cache)
#if defined(VK_NV_shading_rate_image)
    PFN_vkCmdBindShadingRateImageNV pfn_CmdBindShadingRateImageNV;
    PFN_vkCmdSetViewportShadingRatePaletteNV pfn_CmdSetViewportShadingRatePaletteNV;
    PFN_vkCmdSetCoarseSampleOrderNV pfn_CmdSetCoarseSampleOrderNV;
#endif //defined(VK_NV_shading_rate_image)
#if defined(VK_NV_ray_tracing)
    PFN_vkCompileDeferredNV pfn_CompileDeferredNV;
    PFN_vkCreateAccelerationStructureNV pfn_CreateAccelerationStructureNV;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV pfn_GetAccelerationStructureMemoryRequirementsNV;
    PFN_vkCmdCopyAccelerationStructureNV pfn_CmdCopyAccelerationStructureNV;
    PFN_vkCmdBuildAccelerationStructureNV pfn_CmdBuildAccelerationStructureNV;
    PFN_vkCmdTraceRaysNV pfn_CmdTraceRaysNV;
    PFN_vkGetAccelerationStructureHandleNV pfn_GetAccelerationStructureHandleNV;
    PFN_vkCreateRayTracingPipelinesNV pfn_CreateRayTracingPipelinesNV;
#endif //defined(VK_NV_ray_tracing)
#if defined(VK_EXT_external_memory_host)
    PFN_vkGetMemoryHostPointerPropertiesEXT pfn_GetMemoryHostPointerPropertiesEXT;
#endif //defined(VK_EXT_external_memory_host)
#if defined(VK_AMD_buffer_marker)
    PFN_vkCmdWriteBufferMarkerAMD pfn_CmdWriteBufferMarkerAMD;
#endif //defined(VK_AMD_buffer_marker)
#if defined(VK_EXT_calibrated_timestamps)
    PFN_vkGetCalibratedTimestampsEXT pfn_GetCalibratedTimestampsEXT;
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_NV_mesh_shader)
    PFN_vkCmdDrawMeshTasksNV pfn_CmdDrawMeshTasksNV;
    PFN_vkCmdDrawMeshTasksIndirectNV pfn_CmdDrawMeshTasksIndirectNV;
    PFN_vkCmdDrawMeshTasksIndirectCountNV pfn_CmdDrawMeshTasksIndirectCountNV;
#endif //defined(VK_NV_mesh_shader)
#if defined(VK_NV_scissor_exclusive)
    PFN_vkCmdSetExclusiveScissorNV pfn_CmdSetExclusiveScissorNV;
#endif //defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_device_diagnostic_checkpoints)
    PFN_vkCmdSetCheckpointNV pfn_CmdSetCheckpointNV;
    PFN_vkGetQueueCheckpointDataNV pfn_GetQueueCheckpointDataNV;
#endif //defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_INTEL_performance_query)
    PFN_vkInitializePerformanceApiINTEL pfn_InitializePerformanceApiINTEL;
    PFN_vkUninitializePerformanceApiINTEL pfn_UninitializePerformanceApiINTEL;
    PFN_vkCmdSetPerformanceMarkerINTEL pfn_CmdSetPerformanceMarkerINTEL;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL pfn_CmdSetPerformanceStreamMarkerINTEL;
    PFN_vkCmdSetPerformanceOverrideINTEL pfn_CmdSetPerformanceOverrideINTEL;
    PFN_vkAcquirePerformanceConfigurationINTEL pfn_AcquirePerformanceConfigurationINTEL;
    PFN_vkReleasePerformanceConfigurationINTEL pfn_ReleasePerformanceConfigurationINTEL;
    PFN_vkQueueSetPerformanceConfigurationINTEL pfn_QueueSetPerformanceConfigurationINTEL;
    PFN_vkGetPerformanceParameterINTEL pfn_GetPerformanceParameterINTEL;
#endif //defined(VK_INTEL_performance_query)
#if defined(VK_AMD_display_native_hdr)
    PFN_vkSetLocalDimmingAMD pfn_SetLocalDimmingAMD;
#endif //defined(VK_AMD_display_native_hdr)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    PFN_vkAcquireFullScreenExclusiveModeEXT pfn_AcquireFullScreenExclusiveModeEXT;
    PFN_vkReleaseFullScreenExclusiveModeEXT pfn_ReleaseFullScreenExclusiveModeEXT;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT pfn_GetDeviceGroupSurfacePresentModes2EXT;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
#if defined(VK_EXT_line_rasterization)
    PFN_vkCmdSetLineStippleEXT pfn_CmdSetLineStippleEXT;
#endif //defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_extended_dynamic_state)
    PFN_vkCmdSetCullModeEXT pfn_CmdSetCullModeEXT;
    PFN_vkCmdSetFrontFaceEXT pfn_CmdSetFrontFaceEXT;
    PFN_vkCmdSetPrimitiveTopologyEXT pfn_CmdSetPrimitiveTopologyEXT;
    PFN_vkCmdSetViewportWithCountEXT pfn_CmdSetViewportWithCountEXT;
    PFN_vkCmdSetScissorWithCountEXT pfn_CmdSetScissorWithCountEXT;
    PFN_vkCmdBindVertexBuffers2EXT pfn_CmdBindVertexBuffers2EXT;
    PFN_vkCmdSetDepthTestEnableEXT pfn_CmdSetDepthTestEnableEXT;
    PFN_vkCmdSetDepthWriteEnableEXT pfn_CmdSetDepthWriteEnableEXT;
    PFN_vkCmdSetDepthCompareOpEXT pfn_CmdSetDepthCompareOpEXT;
    PFN_vkCmdSetDepthBoundsTestEnableEXT pfn_CmdSetDepthBoundsTestEnableEXT;
    PFN_vkCmdSetStencilTestEnableEXT pfn_CmdSetStencilTestEnableEXT;
    PFN_vkCmdSetStencilOpEXT pfn_CmdSetStencilOpEXT;
#endif //defined(VK_EXT_extended_dynamic_state)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
    PFN_vkCreateDeferredOperationKHR pfn_CreateDeferredOperationKHR;
    PFN_vkDestroyDeferredOperationKHR pfn_DestroyDeferredOperationKHR;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR pfn_GetDeferredOperationMaxConcurrencyKHR;
    PFN_vkGetDeferredOperationResultKHR pfn_GetDeferredOperationResultKHR;
    PFN_vkDeferredOperationJoinKHR pfn_DeferredOperationJoinKHR;
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
#if defined(VK_KHR_pipeline_executable_properties)
    PFN_vkGetPipelineExecutablePropertiesKHR pfn_GetPipelineExecutablePropertiesKHR;
    PFN_vkGetPipelineExecutableStatisticsKHR pfn_GetPipelineExecutableStatisticsKHR;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR pfn_GetPipelineExecutableInternalRepresentationsKHR;
#endif //defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_NV_device_generated_commands)
    PFN_vkCmdExecuteGeneratedCommandsNV pfn_CmdExecuteGeneratedCommandsNV;
    PFN_vkCmdPreprocessGeneratedCommandsNV pfn_CmdPreprocessGeneratedCommandsNV;
    PFN_vkCmdBindPipelineShaderGroupNV pfn_CmdBindPipelineShaderGroupNV;
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV pfn_GetGeneratedCommandsMemoryRequirementsNV;
    PFN_vkCreateIndirectCommandsLayoutNV pfn_CreateIndirectCommandsLayoutNV;
    PFN_vkDestroyIndirectCommandsLayoutNV pfn_DestroyIndirectCommandsLayoutNV;
#endif //defined(VK_NV_device_generated_commands)
#if defined(VK_EXT_private_data)
    PFN_vkCreatePrivateDataSlotEXT pfn_CreatePrivateDataSlotEXT;
    PFN_vkDestroyPrivateDataSlotEXT pfn_DestroyPrivateDataSlotEXT;
    PFN_vkSetPrivateDataEXT pfn_SetPrivateDataEXT;
    PFN_vkGetPrivateDataEXT pfn_GetPrivateDataEXT;
#endif //defined(VK_EXT_private_data)
#if defined(VK_VERSION_1_0)
    void DestroyDevice(const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDevice(device.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void GetDeviceQueue(uint32_t queueFamilyIndex,
        uint32_t queueIndex,
        Queue&  pQueue) {
        return pfn_GetDeviceQueue(device.get(),
            queueFamilyIndex,
            queueIndex,
            reinterpret_cast<VkQueue*>(&pQueue));
    }
    [[nodiscard]] Result QueueSubmit(Queue queue,
        uint32_t submitCount,
        const SubmitInfo* pSubmits,
        Fence fence) {
        return static_cast<Result>(pfn_QueueSubmit(queue.get(),
            submitCount,
            reinterpret_cast<const VkSubmitInfo*>(pSubmits),
            fence.get()));
    }
    [[nodiscard]] Result QueueWaitIdle(Queue queue) {
        return static_cast<Result>(pfn_QueueWaitIdle(queue.get()));
    }
    [[nodiscard]] Result DeviceWaitIdle() {
        return static_cast<Result>(pfn_DeviceWaitIdle(device.get()));
    }
    [[nodiscard]] Result AllocateMemory(const MemoryAllocateInfo&  pAllocateInfo,
        const AllocationCallbacks* pAllocator,
        DeviceMemory&  pMemory) {
        return static_cast<Result>(pfn_AllocateMemory(device.get(),
            reinterpret_cast<const VkMemoryAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDeviceMemory*>(&pMemory)));
    }
    void FreeMemory(DeviceMemory memory,
        const AllocationCallbacks* pAllocator) {
        return pfn_FreeMemory(device.get(),
            memory.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result MapMemory(DeviceMemory memory,
        DeviceSize offset,
        DeviceSize size,
        MemoryMapFlags flags,
        void** ppData) {
        return static_cast<Result>(pfn_MapMemory(device.get(),
            memory.get(),
            offset,
            size,
            static_cast<VkMemoryMapFlags>(flags),
            reinterpret_cast<void**>(ppData)));
    }
    void UnmapMemory(DeviceMemory memory) {
        return pfn_UnmapMemory(device.get(),
            memory.get());
    }
    [[nodiscard]] Result FlushMappedMemoryRanges(uint32_t memoryRangeCount,
        const MappedMemoryRange* pMemoryRanges) {
        return static_cast<Result>(pfn_FlushMappedMemoryRanges(device.get(),
            memoryRangeCount,
            reinterpret_cast<const VkMappedMemoryRange*>(pMemoryRanges)));
    }
    [[nodiscard]] Result InvalidateMappedMemoryRanges(uint32_t memoryRangeCount,
        const MappedMemoryRange* pMemoryRanges) {
        return static_cast<Result>(pfn_InvalidateMappedMemoryRanges(device.get(),
            memoryRangeCount,
            reinterpret_cast<const VkMappedMemoryRange*>(pMemoryRanges)));
    }
    void GetDeviceMemoryCommitment(DeviceMemory memory,
        DeviceSize&  pCommittedMemoryInBytes) {
        return pfn_GetDeviceMemoryCommitment(device.get(),
            memory.get(),
            &pCommittedMemoryInBytes);
    }
    void GetBufferMemoryRequirements(Buffer buffer,
        MemoryRequirements&  pMemoryRequirements) {
        return pfn_GetBufferMemoryRequirements(device.get(),
            buffer.get(),
            reinterpret_cast<VkMemoryRequirements*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result BindBufferMemory(Buffer buffer,
        DeviceMemory memory,
        DeviceSize memoryOffset) {
        return static_cast<Result>(pfn_BindBufferMemory(device.get(),
            buffer.get(),
            memory.get(),
            memoryOffset));
    }
    void GetImageMemoryRequirements(Image image,
        MemoryRequirements&  pMemoryRequirements) {
        return pfn_GetImageMemoryRequirements(device.get(),
            image.get(),
            reinterpret_cast<VkMemoryRequirements*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result BindImageMemory(Image image,
        DeviceMemory memory,
        DeviceSize memoryOffset) {
        return static_cast<Result>(pfn_BindImageMemory(device.get(),
            image.get(),
            memory.get(),
            memoryOffset));
    }
    void GetImageSparseMemoryRequirements(Image image,
        uint32_t&  pSparseMemoryRequirementCount,
        SparseImageMemoryRequirements* pSparseMemoryRequirements) {
        return pfn_GetImageSparseMemoryRequirements(device.get(),
            image.get(),
            &pSparseMemoryRequirementCount,
            reinterpret_cast<VkSparseImageMemoryRequirements*>(pSparseMemoryRequirements));
    }
    [[nodiscard]] Result QueueBindSparse(Queue queue,
        uint32_t bindInfoCount,
        const BindSparseInfo* pBindInfo,
        Fence fence) {
        return static_cast<Result>(pfn_QueueBindSparse(queue.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindSparseInfo*>(pBindInfo),
            fence.get()));
    }
    [[nodiscard]] Result CreateFence(const FenceCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Fence&  pFence) {
        return static_cast<Result>(pfn_CreateFence(device.get(),
            reinterpret_cast<const VkFenceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
    }
    void DestroyFence(Fence fence,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyFence(device.get(),
            fence.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetFences(uint32_t fenceCount,
        const Fence* pFences) {
        return static_cast<Result>(pfn_ResetFences(device.get(),
            fenceCount,
            reinterpret_cast<const VkFence*>(pFences)));
    }
    [[nodiscard]] Result GetFenceStatus(Fence fence) {
        return static_cast<Result>(pfn_GetFenceStatus(device.get(),
            fence.get()));
    }
    [[nodiscard]] Result WaitForFences(uint32_t fenceCount,
        const Fence* pFences,
        Bool32 waitAll,
        uint64_t timeout) {
        return static_cast<Result>(pfn_WaitForFences(device.get(),
            fenceCount,
            reinterpret_cast<const VkFence*>(pFences),
            waitAll,
            timeout));
    }
    [[nodiscard]] Result CreateSemaphore(const SemaphoreCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Semaphore&  pSemaphore) {
        return static_cast<Result>(pfn_CreateSemaphore(device.get(),
            reinterpret_cast<const VkSemaphoreCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSemaphore*>(&pSemaphore)));
    }
    void DestroySemaphore(Semaphore semaphore,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySemaphore(device.get(),
            semaphore.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateEvent(const EventCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Event&  pEvent) {
        return static_cast<Result>(pfn_CreateEvent(device.get(),
            reinterpret_cast<const VkEventCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkEvent*>(&pEvent)));
    }
    void DestroyEvent(Event event,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyEvent(device.get(),
            event.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetEventStatus(Event event) {
        return static_cast<Result>(pfn_GetEventStatus(device.get(),
            event.get()));
    }
    [[nodiscard]] Result SetEvent(Event event) {
        return static_cast<Result>(pfn_SetEvent(device.get(),
            event.get()));
    }
    [[nodiscard]] Result ResetEvent(Event event) {
        return static_cast<Result>(pfn_ResetEvent(device.get(),
            event.get()));
    }
    [[nodiscard]] Result CreateQueryPool(const QueryPoolCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        QueryPool&  pQueryPool) {
        return static_cast<Result>(pfn_CreateQueryPool(device.get(),
            reinterpret_cast<const VkQueryPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkQueryPool*>(&pQueryPool)));
    }
    void DestroyQueryPool(QueryPool queryPool,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyQueryPool(device.get(),
            queryPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetQueryPoolResults(QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount,
        size_t dataSize,
        void* pData,
        DeviceSize stride,
        QueryResultFlags flags) {
        return static_cast<Result>(pfn_GetQueryPoolResults(device.get(),
            queryPool.get(),
            firstQuery,
            queryCount,
            dataSize,
            reinterpret_cast<void*>(pData),
            stride,
            static_cast<VkQueryResultFlags>(flags)));
    }
    [[nodiscard]] Result CreateBuffer(const BufferCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Buffer&  pBuffer) {
        return static_cast<Result>(pfn_CreateBuffer(device.get(),
            reinterpret_cast<const VkBufferCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkBuffer*>(&pBuffer)));
    }
    void DestroyBuffer(Buffer buffer,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyBuffer(device.get(),
            buffer.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateBufferView(const BufferViewCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        BufferView&  pView) {
        return static_cast<Result>(pfn_CreateBufferView(device.get(),
            reinterpret_cast<const VkBufferViewCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkBufferView*>(&pView)));
    }
    void DestroyBufferView(BufferView bufferView,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyBufferView(device.get(),
            bufferView.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateImage(const ImageCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Image&  pImage) {
        return static_cast<Result>(pfn_CreateImage(device.get(),
            reinterpret_cast<const VkImageCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkImage*>(&pImage)));
    }
    void DestroyImage(Image image,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyImage(device.get(),
            image.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void GetImageSubresourceLayout(Image image,
        const ImageSubresource&  pSubresource,
        SubresourceLayout&  pLayout) {
        return pfn_GetImageSubresourceLayout(device.get(),
            image.get(),
            reinterpret_cast<const VkImageSubresource*>(&pSubresource),
            reinterpret_cast<VkSubresourceLayout*>(&pLayout));
    }
    [[nodiscard]] Result CreateImageView(const ImageViewCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        ImageView&  pView) {
        return static_cast<Result>(pfn_CreateImageView(device.get(),
            reinterpret_cast<const VkImageViewCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkImageView*>(&pView)));
    }
    void DestroyImageView(ImageView imageView,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyImageView(device.get(),
            imageView.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateShaderModule(const ShaderModuleCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        ShaderModule&  pShaderModule) {
        return static_cast<Result>(pfn_CreateShaderModule(device.get(),
            reinterpret_cast<const VkShaderModuleCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkShaderModule*>(&pShaderModule)));
    }
    void DestroyShaderModule(ShaderModule shaderModule,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyShaderModule(device.get(),
            shaderModule.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreatePipelineCache(const PipelineCacheCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        PipelineCache&  pPipelineCache) {
        return static_cast<Result>(pfn_CreatePipelineCache(device.get(),
            reinterpret_cast<const VkPipelineCacheCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipelineCache*>(&pPipelineCache)));
    }
    void DestroyPipelineCache(PipelineCache pipelineCache,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyPipelineCache(device.get(),
            pipelineCache.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetPipelineCacheData(PipelineCache pipelineCache,
        size_t&  pDataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetPipelineCacheData(device.get(),
            pipelineCache.get(),
            &pDataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result MergePipelineCaches(PipelineCache dstCache,
        uint32_t srcCacheCount,
        const PipelineCache* pSrcCaches) {
        return static_cast<Result>(pfn_MergePipelineCaches(device.get(),
            dstCache.get(),
            srcCacheCount,
            reinterpret_cast<const VkPipelineCache*>(pSrcCaches)));
    }
    [[nodiscard]] Result CreateGraphicsPipelines(PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const GraphicsPipelineCreateInfo* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateGraphicsPipelines(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkGraphicsPipelineCreateInfo*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    [[nodiscard]] Result CreateComputePipelines(PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const ComputePipelineCreateInfo* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateComputePipelines(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkComputePipelineCreateInfo*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    void DestroyPipeline(Pipeline pipeline,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyPipeline(device.get(),
            pipeline.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreatePipelineLayout(const PipelineLayoutCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        PipelineLayout&  pPipelineLayout) {
        return static_cast<Result>(pfn_CreatePipelineLayout(device.get(),
            reinterpret_cast<const VkPipelineLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipelineLayout*>(&pPipelineLayout)));
    }
    void DestroyPipelineLayout(PipelineLayout pipelineLayout,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyPipelineLayout(device.get(),
            pipelineLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateSampler(const SamplerCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Sampler&  pSampler) {
        return static_cast<Result>(pfn_CreateSampler(device.get(),
            reinterpret_cast<const VkSamplerCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSampler*>(&pSampler)));
    }
    void DestroySampler(Sampler sampler,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySampler(device.get(),
            sampler.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateDescriptorSetLayout(const DescriptorSetLayoutCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DescriptorSetLayout&  pSetLayout) {
        return static_cast<Result>(pfn_CreateDescriptorSetLayout(device.get(),
            reinterpret_cast<const VkDescriptorSetLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorSetLayout*>(&pSetLayout)));
    }
    void DestroyDescriptorSetLayout(DescriptorSetLayout descriptorSetLayout,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDescriptorSetLayout(device.get(),
            descriptorSetLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateDescriptorPool(const DescriptorPoolCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DescriptorPool&  pDescriptorPool) {
        return static_cast<Result>(pfn_CreateDescriptorPool(device.get(),
            reinterpret_cast<const VkDescriptorPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorPool*>(&pDescriptorPool)));
    }
    void DestroyDescriptorPool(DescriptorPool descriptorPool,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDescriptorPool(device.get(),
            descriptorPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetDescriptorPool(DescriptorPool descriptorPool,
        DescriptorPoolResetFlags flags) {
        return static_cast<Result>(pfn_ResetDescriptorPool(device.get(),
            descriptorPool.get(),
            static_cast<VkDescriptorPoolResetFlags>(flags)));
    }
    [[nodiscard]] Result AllocateDescriptorSets(const DescriptorSetAllocateInfo&  pAllocateInfo,
        DescriptorSet* pDescriptorSets) {
        return static_cast<Result>(pfn_AllocateDescriptorSets(device.get(),
            reinterpret_cast<const VkDescriptorSetAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<VkDescriptorSet*>(pDescriptorSets)));
    }
    [[nodiscard]] Result FreeDescriptorSets(DescriptorPool descriptorPool,
        uint32_t descriptorSetCount,
        const DescriptorSet* pDescriptorSets) {
        return static_cast<Result>(pfn_FreeDescriptorSets(device.get(),
            descriptorPool.get(),
            descriptorSetCount,
            reinterpret_cast<const VkDescriptorSet*>(pDescriptorSets)));
    }
    void UpdateDescriptorSets(uint32_t descriptorWriteCount,
        const WriteDescriptorSet* pDescriptorWrites,
        uint32_t descriptorCopyCount,
        const CopyDescriptorSet* pDescriptorCopies) {
        return pfn_UpdateDescriptorSets(device.get(),
            descriptorWriteCount,
            reinterpret_cast<const VkWriteDescriptorSet*>(pDescriptorWrites),
            descriptorCopyCount,
            reinterpret_cast<const VkCopyDescriptorSet*>(pDescriptorCopies));
    }
    [[nodiscard]] Result CreateFramebuffer(const FramebufferCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Framebuffer&  pFramebuffer) {
        return static_cast<Result>(pfn_CreateFramebuffer(device.get(),
            reinterpret_cast<const VkFramebufferCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFramebuffer*>(&pFramebuffer)));
    }
    void DestroyFramebuffer(Framebuffer framebuffer,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyFramebuffer(device.get(),
            framebuffer.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateRenderPass(const RenderPassCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        RenderPass&  pRenderPass) {
        return static_cast<Result>(pfn_CreateRenderPass(device.get(),
            reinterpret_cast<const VkRenderPassCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkRenderPass*>(&pRenderPass)));
    }
    void DestroyRenderPass(RenderPass renderPass,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyRenderPass(device.get(),
            renderPass.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void GetRenderAreaGranularity(RenderPass renderPass,
        Extent2D&  pGranularity) {
        return pfn_GetRenderAreaGranularity(device.get(),
            renderPass.get(),
            reinterpret_cast<VkExtent2D*>(&pGranularity));
    }
    [[nodiscard]] Result CreateCommandPool(const CommandPoolCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        CommandPool&  pCommandPool) {
        return static_cast<Result>(pfn_CreateCommandPool(device.get(),
            reinterpret_cast<const VkCommandPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkCommandPool*>(&pCommandPool)));
    }
    void DestroyCommandPool(CommandPool commandPool,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyCommandPool(device.get(),
            commandPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetCommandPool(CommandPool commandPool,
        CommandPoolResetFlags flags) {
        return static_cast<Result>(pfn_ResetCommandPool(device.get(),
            commandPool.get(),
            static_cast<VkCommandPoolResetFlags>(flags)));
    }
    [[nodiscard]] Result AllocateCommandBuffers(const CommandBufferAllocateInfo&  pAllocateInfo,
        CommandBuffer* pCommandBuffers) {
        return static_cast<Result>(pfn_AllocateCommandBuffers(device.get(),
            reinterpret_cast<const VkCommandBufferAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<VkCommandBuffer*>(pCommandBuffers)));
    }
    void FreeCommandBuffers(CommandPool commandPool,
        uint32_t commandBufferCount,
        const CommandBuffer* pCommandBuffers) {
        return pfn_FreeCommandBuffers(device.get(),
            commandPool.get(),
            commandBufferCount,
            reinterpret_cast<const VkCommandBuffer*>(pCommandBuffers));
    }
    [[nodiscard]] Result BeginCommandBuffer(CommandBuffer commandBuffer,
        const CommandBufferBeginInfo&  pBeginInfo) {
        return static_cast<Result>(pfn_BeginCommandBuffer(commandBuffer.get(),
            reinterpret_cast<const VkCommandBufferBeginInfo*>(&pBeginInfo)));
    }
    [[nodiscard]] Result EndCommandBuffer(CommandBuffer commandBuffer) {
        return static_cast<Result>(pfn_EndCommandBuffer(commandBuffer.get()));
    }
    [[nodiscard]] Result ResetCommandBuffer(CommandBuffer commandBuffer,
        CommandBufferResetFlags flags) {
        return static_cast<Result>(pfn_ResetCommandBuffer(commandBuffer.get(),
            static_cast<VkCommandBufferResetFlags>(flags)));
    }
    void CmdBindPipeline(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        Pipeline pipeline) {
        return pfn_CmdBindPipeline(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get());
    }
    void CmdSetViewport(CommandBuffer commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        const Viewport* pViewports) {
        return pfn_CmdSetViewport(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void CmdSetScissor(CommandBuffer commandBuffer,
        uint32_t firstScissor,
        uint32_t scissorCount,
        const Rect2D* pScissors) {
        return pfn_CmdSetScissor(commandBuffer.get(),
            firstScissor,
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void CmdSetLineWidth(CommandBuffer commandBuffer,
        float lineWidth) {
        return pfn_CmdSetLineWidth(commandBuffer.get(),
            lineWidth);
    }
    void CmdSetDepthBias(CommandBuffer commandBuffer,
        float depthBiasConstantFactor,
        float depthBiasClamp,
        float depthBiasSlopeFactor) {
        return pfn_CmdSetDepthBias(commandBuffer.get(),
            depthBiasConstantFactor,
            depthBiasClamp,
            depthBiasSlopeFactor);
    }
    void CmdSetBlendConstants(CommandBuffer commandBuffer,
        const float blendConstants[4]) {
        return pfn_CmdSetBlendConstants(commandBuffer.get(),
            blendConstants);
    }
    void CmdSetDepthBounds(CommandBuffer commandBuffer,
        float minDepthBounds,
        float maxDepthBounds) {
        return pfn_CmdSetDepthBounds(commandBuffer.get(),
            minDepthBounds,
            maxDepthBounds);
    }
    void CmdSetStencilCompareMask(CommandBuffer commandBuffer,
        StencilFaceFlags faceMask,
        uint32_t compareMask) {
        return pfn_CmdSetStencilCompareMask(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            compareMask);
    }
    void CmdSetStencilWriteMask(CommandBuffer commandBuffer,
        StencilFaceFlags faceMask,
        uint32_t writeMask) {
        return pfn_CmdSetStencilWriteMask(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            writeMask);
    }
    void CmdSetStencilReference(CommandBuffer commandBuffer,
        StencilFaceFlags faceMask,
        uint32_t reference) {
        return pfn_CmdSetStencilReference(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            reference);
    }
    void CmdBindDescriptorSets(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        PipelineLayout layout,
        uint32_t firstSet,
        uint32_t descriptorSetCount,
        const DescriptorSet* pDescriptorSets,
        uint32_t dynamicOffsetCount,
        const uint32_t* pDynamicOffsets) {
        return pfn_CmdBindDescriptorSets(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            layout.get(),
            firstSet,
            descriptorSetCount,
            reinterpret_cast<const VkDescriptorSet*>(pDescriptorSets),
            dynamicOffsetCount,
            pDynamicOffsets);
    }
    void CmdBindIndexBuffer(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        IndexType indexType) {
        return pfn_CmdBindIndexBuffer(commandBuffer.get(),
            buffer.get(),
            offset,
            static_cast<VkIndexType>(indexType));
    }
    void CmdBindVertexBuffers(CommandBuffer commandBuffer,
        uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets) {
        return pfn_CmdBindVertexBuffers(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets);
    }
    void CmdDraw(CommandBuffer commandBuffer,
        uint32_t vertexCount,
        uint32_t instanceCount,
        uint32_t firstVertex,
        uint32_t firstInstance) {
        return pfn_CmdDraw(commandBuffer.get(),
            vertexCount,
            instanceCount,
            firstVertex,
            firstInstance);
    }
    void CmdDrawIndexed(CommandBuffer commandBuffer,
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t firstInstance) {
        return pfn_CmdDrawIndexed(commandBuffer.get(),
            indexCount,
            instanceCount,
            firstIndex,
            vertexOffset,
            firstInstance);
    }
    void CmdDrawIndirect(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return pfn_CmdDrawIndirect(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDrawIndexedIndirect(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return pfn_CmdDrawIndexedIndirect(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDispatch(CommandBuffer commandBuffer,
        uint32_t groupCountX,
        uint32_t groupCountY,
        uint32_t groupCountZ) {
        return pfn_CmdDispatch(commandBuffer.get(),
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    void CmdDispatchIndirect(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset) {
        return pfn_CmdDispatchIndirect(commandBuffer.get(),
            buffer.get(),
            offset);
    }
    void CmdCopyBuffer(CommandBuffer commandBuffer,
        Buffer srcBuffer,
        Buffer dstBuffer,
        uint32_t regionCount,
        const BufferCopy* pRegions) {
        return pfn_CmdCopyBuffer(commandBuffer.get(),
            srcBuffer.get(),
            dstBuffer.get(),
            regionCount,
            reinterpret_cast<const VkBufferCopy*>(pRegions));
    }
    void CmdCopyImage(CommandBuffer commandBuffer,
        Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageCopy* pRegions) {
        return pfn_CmdCopyImage(commandBuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageCopy*>(pRegions));
    }
    void CmdBlitImage(CommandBuffer commandBuffer,
        Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageBlit* pRegions,
        Filter filter) {
        return pfn_CmdBlitImage(commandBuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageBlit*>(pRegions),
            static_cast<VkFilter>(filter));
    }
    void CmdCopyBufferToImage(CommandBuffer commandBuffer,
        Buffer srcBuffer,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const BufferImageCopy* pRegions) {
        return pfn_CmdCopyBufferToImage(commandBuffer.get(),
            srcBuffer.get(),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkBufferImageCopy*>(pRegions));
    }
    void CmdCopyImageToBuffer(CommandBuffer commandBuffer,
        Image srcImage,
        ImageLayout srcImageLayout,
        Buffer dstBuffer,
        uint32_t regionCount,
        const BufferImageCopy* pRegions) {
        return pfn_CmdCopyImageToBuffer(commandBuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstBuffer.get(),
            regionCount,
            reinterpret_cast<const VkBufferImageCopy*>(pRegions));
    }
    void CmdUpdateBuffer(CommandBuffer commandBuffer,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize dataSize,
        const void* pData) {
        return pfn_CmdUpdateBuffer(commandBuffer.get(),
            dstBuffer.get(),
            dstOffset,
            dataSize,
            reinterpret_cast<const void*>(pData));
    }
    void CmdFillBuffer(CommandBuffer commandBuffer,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize size,
        uint32_t data) {
        return pfn_CmdFillBuffer(commandBuffer.get(),
            dstBuffer.get(),
            dstOffset,
            size,
            data);
    }
    void CmdClearColorImage(CommandBuffer commandBuffer,
        Image image,
        ImageLayout imageLayout,
        const ClearColorValue&  pColor,
        uint32_t rangeCount,
        const ImageSubresourceRange* pRanges) {
        return pfn_CmdClearColorImage(commandBuffer.get(),
            image.get(),
            static_cast<VkImageLayout>(imageLayout),
            reinterpret_cast<const VkClearColorValue*>(&pColor),
            rangeCount,
            reinterpret_cast<const VkImageSubresourceRange*>(pRanges));
    }
    void CmdClearDepthStencilImage(CommandBuffer commandBuffer,
        Image image,
        ImageLayout imageLayout,
        const ClearDepthStencilValue&  pDepthStencil,
        uint32_t rangeCount,
        const ImageSubresourceRange* pRanges) {
        return pfn_CmdClearDepthStencilImage(commandBuffer.get(),
            image.get(),
            static_cast<VkImageLayout>(imageLayout),
            reinterpret_cast<const VkClearDepthStencilValue*>(&pDepthStencil),
            rangeCount,
            reinterpret_cast<const VkImageSubresourceRange*>(pRanges));
    }
    void CmdClearAttachments(CommandBuffer commandBuffer,
        uint32_t attachmentCount,
        const ClearAttachment* pAttachments,
        uint32_t rectCount,
        const ClearRect* pRects) {
        return pfn_CmdClearAttachments(commandBuffer.get(),
            attachmentCount,
            reinterpret_cast<const VkClearAttachment*>(pAttachments),
            rectCount,
            reinterpret_cast<const VkClearRect*>(pRects));
    }
    void CmdResolveImage(CommandBuffer commandBuffer,
        Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageResolve* pRegions) {
        return pfn_CmdResolveImage(commandBuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageResolve*>(pRegions));
    }
    void CmdSetEvent(CommandBuffer commandBuffer,
        Event event,
        PipelineStageFlags stageMask) {
        return pfn_CmdSetEvent(commandBuffer.get(),
            event.get(),
            static_cast<VkPipelineStageFlags>(stageMask));
    }
    void CmdResetEvent(CommandBuffer commandBuffer,
        Event event,
        PipelineStageFlags stageMask) {
        return pfn_CmdResetEvent(commandBuffer.get(),
            event.get(),
            static_cast<VkPipelineStageFlags>(stageMask));
    }
    void CmdWaitEvents(CommandBuffer commandBuffer,
        uint32_t eventCount,
        const Event* pEvents,
        PipelineStageFlags srcStageMask,
        PipelineStageFlags dstStageMask,
        uint32_t memoryBarrierCount,
        const MemoryBarrier* pMemoryBarriers,
        uint32_t bufferMemoryBarrierCount,
        const BufferMemoryBarrier* pBufferMemoryBarriers,
        uint32_t imageMemoryBarrierCount,
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return pfn_CmdWaitEvents(commandBuffer.get(),
            eventCount,
            reinterpret_cast<const VkEvent*>(pEvents),
            static_cast<VkPipelineStageFlags>(srcStageMask),
            static_cast<VkPipelineStageFlags>(dstStageMask),
            memoryBarrierCount,
            reinterpret_cast<const VkMemoryBarrier*>(pMemoryBarriers),
            bufferMemoryBarrierCount,
            reinterpret_cast<const VkBufferMemoryBarrier*>(pBufferMemoryBarriers),
            imageMemoryBarrierCount,
            reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void CmdPipelineBarrier(CommandBuffer commandBuffer,
        PipelineStageFlags srcStageMask,
        PipelineStageFlags dstStageMask,
        DependencyFlags dependencyFlags,
        uint32_t memoryBarrierCount,
        const MemoryBarrier* pMemoryBarriers,
        uint32_t bufferMemoryBarrierCount,
        const BufferMemoryBarrier* pBufferMemoryBarriers,
        uint32_t imageMemoryBarrierCount,
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return pfn_CmdPipelineBarrier(commandBuffer.get(),
            static_cast<VkPipelineStageFlags>(srcStageMask),
            static_cast<VkPipelineStageFlags>(dstStageMask),
            static_cast<VkDependencyFlags>(dependencyFlags),
            memoryBarrierCount,
            reinterpret_cast<const VkMemoryBarrier*>(pMemoryBarriers),
            bufferMemoryBarrierCount,
            reinterpret_cast<const VkBufferMemoryBarrier*>(pBufferMemoryBarriers),
            imageMemoryBarrierCount,
            reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void CmdBeginQuery(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query,
        QueryControlFlags flags) {
        return pfn_CmdBeginQuery(commandBuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags));
    }
    void CmdEndQuery(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query) {
        return pfn_CmdEndQuery(commandBuffer.get(),
            queryPool.get(),
            query);
    }
    void CmdResetQueryPool(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount) {
        return pfn_CmdResetQueryPool(commandBuffer.get(),
            queryPool.get(),
            firstQuery,
            queryCount);
    }
    void CmdWriteTimestamp(CommandBuffer commandBuffer,
        PipelineStageFlagBits pipelineStage,
        QueryPool queryPool,
        uint32_t query) {
        return pfn_CmdWriteTimestamp(commandBuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            queryPool.get(),
            query);
    }
    void CmdCopyQueryPoolResults(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize stride,
        QueryResultFlags flags) {
        return pfn_CmdCopyQueryPoolResults(commandBuffer.get(),
            queryPool.get(),
            firstQuery,
            queryCount,
            dstBuffer.get(),
            dstOffset,
            stride,
            static_cast<VkQueryResultFlags>(flags));
    }
    void CmdPushConstants(CommandBuffer commandBuffer,
        PipelineLayout layout,
        ShaderStageFlags stageFlags,
        uint32_t offset,
        uint32_t size,
        const void* pValues) {
        return pfn_CmdPushConstants(commandBuffer.get(),
            layout.get(),
            static_cast<VkShaderStageFlags>(stageFlags),
            offset,
            size,
            reinterpret_cast<const void*>(pValues));
    }
    void CmdBeginRenderPass(CommandBuffer commandBuffer,
        const RenderPassBeginInfo&  pRenderPassBegin,
        SubpassContents contents) {
        return pfn_CmdBeginRenderPass(commandBuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            static_cast<VkSubpassContents>(contents));
    }
    void CmdNextSubpass(CommandBuffer commandBuffer,
        SubpassContents contents) {
        return pfn_CmdNextSubpass(commandBuffer.get(),
            static_cast<VkSubpassContents>(contents));
    }
    void CmdEndRenderPass(CommandBuffer commandBuffer) {
        return pfn_CmdEndRenderPass(commandBuffer.get());
    }
    void CmdExecuteCommands(CommandBuffer commandBuffer,
        uint32_t commandBufferCount,
        const CommandBuffer* pCommandBuffers) {
        return pfn_CmdExecuteCommands(commandBuffer.get(),
            commandBufferCount,
            reinterpret_cast<const VkCommandBuffer*>(pCommandBuffers));
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] Result BindBufferMemory2(uint32_t bindInfoCount,
        const BindBufferMemoryInfo* pBindInfos) {
        return static_cast<Result>(pfn_BindBufferMemory2(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindBufferMemoryInfo*>(pBindInfos)));
    }
    [[nodiscard]] Result BindImageMemory2(uint32_t bindInfoCount,
        const BindImageMemoryInfo* pBindInfos) {
        return static_cast<Result>(pfn_BindImageMemory2(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindImageMemoryInfo*>(pBindInfos)));
    }
    void GetDeviceGroupPeerMemoryFeatures(uint32_t heapIndex,
        uint32_t localDeviceIndex,
        uint32_t remoteDeviceIndex,
        PeerMemoryFeatureFlags&  pPeerMemoryFeatures) {
        return pfn_GetDeviceGroupPeerMemoryFeatures(device.get(),
            heapIndex,
            localDeviceIndex,
            remoteDeviceIndex,
            reinterpret_cast<VkPeerMemoryFeatureFlags*>(&pPeerMemoryFeatures));
    }
    void CmdSetDeviceMask(CommandBuffer commandBuffer,
        uint32_t deviceMask) {
        return pfn_CmdSetDeviceMask(commandBuffer.get(),
            deviceMask);
    }
    void CmdDispatchBase(CommandBuffer commandBuffer,
        uint32_t baseGroupX,
        uint32_t baseGroupY,
        uint32_t baseGroupZ,
        uint32_t groupCountX,
        uint32_t groupCountY,
        uint32_t groupCountZ) {
        return pfn_CmdDispatchBase(commandBuffer.get(),
            baseGroupX,
            baseGroupY,
            baseGroupZ,
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    void GetBufferMemoryRequirements2(const BufferMemoryRequirementsInfo2&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetBufferMemoryRequirements2(device.get(),
            reinterpret_cast<const VkBufferMemoryRequirementsInfo2*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    void GetImageMemoryRequirements2(const ImageMemoryRequirementsInfo2&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetImageMemoryRequirements2(device.get(),
            reinterpret_cast<const VkImageMemoryRequirementsInfo2*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    void GetImageSparseMemoryRequirements2(const ImageSparseMemoryRequirementsInfo2&  pInfo,
        uint32_t&  pSparseMemoryRequirementCount,
        SparseImageMemoryRequirements2* pSparseMemoryRequirements) {
        return pfn_GetImageSparseMemoryRequirements2(device.get(),
            reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2*>(&pInfo),
            &pSparseMemoryRequirementCount,
            reinterpret_cast<VkSparseImageMemoryRequirements2*>(pSparseMemoryRequirements));
    }
    void TrimCommandPool(CommandPool commandPool,
        CommandPoolTrimFlags flags) {
        return pfn_TrimCommandPool(device.get(),
            commandPool.get(),
            static_cast<VkCommandPoolTrimFlags>(flags));
    }
    void GetDeviceQueue2(const DeviceQueueInfo2&  pQueueInfo,
        Queue&  pQueue) {
        return pfn_GetDeviceQueue2(device.get(),
            reinterpret_cast<const VkDeviceQueueInfo2*>(&pQueueInfo),
            reinterpret_cast<VkQueue*>(&pQueue));
    }
    [[nodiscard]] Result CreateSamplerYcbcrConversion(const SamplerYcbcrConversionCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SamplerYcbcrConversion&  pYcbcrConversion) {
        return static_cast<Result>(pfn_CreateSamplerYcbcrConversion(device.get(),
            reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSamplerYcbcrConversion*>(&pYcbcrConversion)));
    }
    void DestroySamplerYcbcrConversion(SamplerYcbcrConversion ycbcrConversion,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySamplerYcbcrConversion(device.get(),
            ycbcrConversion.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result CreateDescriptorUpdateTemplate(const DescriptorUpdateTemplateCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DescriptorUpdateTemplate&  pDescriptorUpdateTemplate) {
        return static_cast<Result>(pfn_CreateDescriptorUpdateTemplate(device.get(),
            reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorUpdateTemplate*>(&pDescriptorUpdateTemplate)));
    }
    void DestroyDescriptorUpdateTemplate(DescriptorUpdateTemplate descriptorUpdateTemplate,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDescriptorUpdateTemplate(device.get(),
            descriptorUpdateTemplate.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void UpdateDescriptorSetWithTemplate(DescriptorSet descriptorSet,
        DescriptorUpdateTemplate descriptorUpdateTemplate,
        const void* pData) {
        return pfn_UpdateDescriptorSetWithTemplate(device.get(),
            descriptorSet.get(),
            descriptorUpdateTemplate.get(),
            reinterpret_cast<const void*>(pData));
    }
    void GetDescriptorSetLayoutSupport(const DescriptorSetLayoutCreateInfo&  pCreateInfo,
        DescriptorSetLayoutSupport&  pSupport) {
        return pfn_GetDescriptorSetLayoutSupport(device.get(),
            reinterpret_cast<const VkDescriptorSetLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<VkDescriptorSetLayoutSupport*>(&pSupport));
    }
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
    void CmdDrawIndirectCount(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return pfn_CmdDrawIndirectCount(commandBuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    void CmdDrawIndexedIndirectCount(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return pfn_CmdDrawIndexedIndirectCount(commandBuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    [[nodiscard]] Result CreateRenderPass2(const RenderPassCreateInfo2&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        RenderPass&  pRenderPass) {
        return static_cast<Result>(pfn_CreateRenderPass2(device.get(),
            reinterpret_cast<const VkRenderPassCreateInfo2*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkRenderPass*>(&pRenderPass)));
    }
    void CmdBeginRenderPass2(CommandBuffer commandBuffer,
        const RenderPassBeginInfo&  pRenderPassBegin,
        const SubpassBeginInfo&  pSubpassBeginInfo) {
        return pfn_CmdBeginRenderPass2(commandBuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo));
    }
    void CmdNextSubpass2(CommandBuffer commandBuffer,
        const SubpassBeginInfo&  pSubpassBeginInfo,
        const SubpassEndInfo&  pSubpassEndInfo) {
        return pfn_CmdNextSubpass2(commandBuffer.get(),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void CmdEndRenderPass2(CommandBuffer commandBuffer,
        const SubpassEndInfo&  pSubpassEndInfo) {
        return pfn_CmdEndRenderPass2(commandBuffer.get(),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void ResetQueryPool(QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount) {
        return pfn_ResetQueryPool(device.get(),
            queryPool.get(),
            firstQuery,
            queryCount);
    }
    [[nodiscard]] Result GetSemaphoreCounterValue(Semaphore semaphore,
        uint64_t&  pValue) {
        return static_cast<Result>(pfn_GetSemaphoreCounterValue(device.get(),
            semaphore.get(),
            &pValue));
    }
    [[nodiscard]] Result WaitSemaphores(const SemaphoreWaitInfo&  pWaitInfo,
        uint64_t timeout) {
        return static_cast<Result>(pfn_WaitSemaphores(device.get(),
            reinterpret_cast<const VkSemaphoreWaitInfo*>(&pWaitInfo),
            timeout));
    }
    [[nodiscard]] Result SignalSemaphore(const SemaphoreSignalInfo&  pSignalInfo) {
        return static_cast<Result>(pfn_SignalSemaphore(device.get(),
            reinterpret_cast<const VkSemaphoreSignalInfo*>(&pSignalInfo)));
    }
    [[nodiscard]] uint64_t GetBufferOpaqueCaptureAddress(const BufferDeviceAddressInfo&  pInfo) {
        return pfn_GetBufferOpaqueCaptureAddress(device.get(),
            reinterpret_cast<const VkBufferDeviceAddressInfo*>(&pInfo));
    }
    [[nodiscard]] VkDeviceAddress GetBufferDeviceAddress(const BufferDeviceAddressInfo&  pInfo) {
        return pfn_GetBufferDeviceAddress(device.get(),
            reinterpret_cast<const VkBufferDeviceAddressInfo*>(&pInfo));
    }
    [[nodiscard]] uint64_t GetDeviceMemoryOpaqueCaptureAddress(const DeviceMemoryOpaqueCaptureAddressInfo&  pInfo) {
        return pfn_GetDeviceMemoryOpaqueCaptureAddress(device.get(),
            reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo*>(&pInfo));
    }
#endif //defined(VK_VERSION_1_2)
#if defined(VK_KHR_swapchain)
    [[nodiscard]] Result CreateSwapchainKHR(const SwapchainCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SwapchainKHR&  pSwapchain) {
        return static_cast<Result>(pfn_CreateSwapchainKHR(device.get(),
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(&pSwapchain)));
    }
    void DestroySwapchainKHR(SwapchainKHR swapchain,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySwapchainKHR(device.get(),
            swapchain.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetSwapchainImagesKHR(SwapchainKHR swapchain,
        uint32_t&  pSwapchainImageCount,
        Image* pSwapchainImages) {
        return static_cast<Result>(pfn_GetSwapchainImagesKHR(device.get(),
            swapchain.get(),
            &pSwapchainImageCount,
            reinterpret_cast<VkImage*>(pSwapchainImages)));
    }
    [[nodiscard]] Result AcquireNextImageKHR(SwapchainKHR swapchain,
        uint64_t timeout,
        Semaphore semaphore,
        Fence fence,
        uint32_t&  pImageIndex) {
        return static_cast<Result>(pfn_AcquireNextImageKHR(device.get(),
            swapchain.get(),
            timeout,
            semaphore.get(),
            fence.get(),
            &pImageIndex));
    }
    [[nodiscard]] Result QueuePresentKHR(Queue queue,
        const PresentInfoKHR&  pPresentInfo) {
        return static_cast<Result>(pfn_QueuePresentKHR(queue.get(),
            reinterpret_cast<const VkPresentInfoKHR*>(&pPresentInfo)));
    }
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    [[nodiscard]] Result GetDeviceGroupPresentCapabilitiesKHR(DeviceGroupPresentCapabilitiesKHR&  pDeviceGroupPresentCapabilities) {
        return static_cast<Result>(pfn_GetDeviceGroupPresentCapabilitiesKHR(device.get(),
            reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR*>(&pDeviceGroupPresentCapabilities)));
    }
    [[nodiscard]] Result GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface,
        DeviceGroupPresentModeFlagsKHR&  pModes) {
        return static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModesKHR(device.get(),
            surface.get(),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    [[nodiscard]] Result AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo,
        uint32_t&  pImageIndex) {
        return static_cast<Result>(pfn_AcquireNextImage2KHR(device.get(),
            reinterpret_cast<const VkAcquireNextImageInfoKHR*>(&pAcquireInfo),
            &pImageIndex));
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
#if defined(VK_KHR_display_swapchain)
    [[nodiscard]] Result CreateSharedSwapchainsKHR(uint32_t swapchainCount,
        const SwapchainCreateInfoKHR* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        SwapchainKHR* pSwapchains) {
        return static_cast<Result>(pfn_CreateSharedSwapchainsKHR(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(pSwapchains)));
    }
#endif //defined(VK_KHR_display_swapchain)
#if defined(VK_EXT_debug_marker)
    [[nodiscard]] Result DebugMarkerSetObjectNameEXT(const DebugMarkerObjectNameInfoEXT&  pNameInfo) {
        return static_cast<Result>(pfn_DebugMarkerSetObjectNameEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectNameInfoEXT*>(&pNameInfo)));
    }
    [[nodiscard]] Result DebugMarkerSetObjectTagEXT(const DebugMarkerObjectTagInfoEXT&  pTagInfo) {
        return static_cast<Result>(pfn_DebugMarkerSetObjectTagEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectTagInfoEXT*>(&pTagInfo)));
    }
    void CmdDebugMarkerBeginEXT(CommandBuffer commandBuffer,
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return pfn_CmdDebugMarkerBeginEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    void CmdDebugMarkerEndEXT(CommandBuffer commandBuffer) {
        return pfn_CmdDebugMarkerEndEXT(commandBuffer.get());
    }
    void CmdDebugMarkerInsertEXT(CommandBuffer commandBuffer,
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return pfn_CmdDebugMarkerInsertEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
#endif //defined(VK_EXT_debug_marker)
#if defined(VK_EXT_transform_feedback)
    void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer,
        uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes) {
        return pfn_CmdBindTransformFeedbackBuffersEXT(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes);
    }
    void CmdBeginTransformFeedbackEXT(CommandBuffer commandBuffer,
        uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return pfn_CmdBeginTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer,
        uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return pfn_CmdEndTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdBeginQueryIndexedEXT(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query,
        QueryControlFlags flags,
        uint32_t index) {
        return pfn_CmdBeginQueryIndexedEXT(commandBuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags),
            index);
    }
    void CmdEndQueryIndexedEXT(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query,
        uint32_t index) {
        return pfn_CmdEndQueryIndexedEXT(commandBuffer.get(),
            queryPool.get(),
            query,
            index);
    }
    void CmdDrawIndirectByteCountEXT(CommandBuffer commandBuffer,
        uint32_t instanceCount,
        uint32_t firstInstance,
        Buffer counterBuffer,
        DeviceSize counterBufferOffset,
        uint32_t counterOffset,
        uint32_t vertexStride) {
        return pfn_CmdDrawIndirectByteCountEXT(commandBuffer.get(),
            instanceCount,
            firstInstance,
            counterBuffer.get(),
            counterBufferOffset,
            counterOffset,
            vertexStride);
    }
#endif //defined(VK_EXT_transform_feedback)
#if defined(VK_NVX_image_view_handle)
    [[nodiscard]] uint32_t GetImageViewHandleNVX(const ImageViewHandleInfoNVX&  pInfo) {
        return pfn_GetImageViewHandleNVX(device.get(),
            reinterpret_cast<const VkImageViewHandleInfoNVX*>(&pInfo));
    }
    [[nodiscard]] Result GetImageViewAddressNVX(ImageView imageView,
        ImageViewAddressPropertiesNVX&  pProperties) {
        return static_cast<Result>(pfn_GetImageViewAddressNVX(device.get(),
            imageView.get(),
            reinterpret_cast<VkImageViewAddressPropertiesNVX*>(&pProperties)));
    }
#endif //defined(VK_NVX_image_view_handle)
#if defined(VK_AMD_shader_info)
    [[nodiscard]] Result GetShaderInfoAMD(Pipeline pipeline,
        ShaderStageFlagBits shaderStage,
        ShaderInfoTypeAMD infoType,
        size_t&  pInfoSize,
        void* pInfo) {
        return static_cast<Result>(pfn_GetShaderInfoAMD(device.get(),
            pipeline.get(),
            static_cast<VkShaderStageFlagBits>(shaderStage),
            static_cast<VkShaderInfoTypeAMD>(infoType),
            &pInfoSize,
            reinterpret_cast<void*>(pInfo)));
    }
#endif //defined(VK_AMD_shader_info)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
    [[nodiscard]] Result GetMemoryWin32HandleNV(DeviceMemory memory,
        ExternalMemoryHandleTypeFlagsNV handleType,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetMemoryWin32HandleNV(device.get(),
            memory.get(),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(handleType),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
    [[nodiscard]] Result GetMemoryWin32HandleKHR(const MemoryGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetMemoryWin32HandleKHR(device.get(),
            reinterpret_cast<const VkMemoryGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result GetMemoryWin32HandlePropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType,
        HANDLE handle,
        MemoryWin32HandlePropertiesKHR&  pMemoryWin32HandleProperties) {
        return static_cast<Result>(pfn_GetMemoryWin32HandlePropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            static_cast<HANDLE>(handle),
            reinterpret_cast<VkMemoryWin32HandlePropertiesKHR*>(&pMemoryWin32HandleProperties)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
#if defined(VK_KHR_external_memory_fd)
    [[nodiscard]] Result GetMemoryFdKHR(const MemoryGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetMemoryFdKHR(device.get(),
            reinterpret_cast<const VkMemoryGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result GetMemoryFdPropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType,
        int fd,
        MemoryFdPropertiesKHR&  pMemoryFdProperties) {
        return static_cast<Result>(pfn_GetMemoryFdPropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            fd,
            reinterpret_cast<VkMemoryFdPropertiesKHR*>(&pMemoryFdProperties)));
    }
#endif //defined(VK_KHR_external_memory_fd)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
    [[nodiscard]] Result GetSemaphoreWin32HandleKHR(const SemaphoreGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result ImportSemaphoreWin32HandleKHR(const ImportSemaphoreWin32HandleInfoKHR&  pImportSemaphoreWin32HandleInfo) {
        return static_cast<Result>(pfn_ImportSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportSemaphoreWin32HandleInfoKHR*>(&pImportSemaphoreWin32HandleInfo)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
#if defined(VK_KHR_external_semaphore_fd)
    [[nodiscard]] Result GetSemaphoreFdKHR(const SemaphoreGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetSemaphoreFdKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result ImportSemaphoreFdKHR(const ImportSemaphoreFdInfoKHR&  pImportSemaphoreFdInfo) {
        return static_cast<Result>(pfn_ImportSemaphoreFdKHR(device.get(),
            reinterpret_cast<const VkImportSemaphoreFdInfoKHR*>(&pImportSemaphoreFdInfo)));
    }
#endif //defined(VK_KHR_external_semaphore_fd)
#if defined(VK_KHR_push_descriptor)
    void CmdPushDescriptorSetKHR(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        PipelineLayout layout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        const WriteDescriptorSet* pDescriptorWrites) {
        return pfn_CmdPushDescriptorSetKHR(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            layout.get(),
            set,
            descriptorWriteCount,
            reinterpret_cast<const VkWriteDescriptorSet*>(pDescriptorWrites));
    }
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
    void CmdPushDescriptorSetWithTemplateKHR(CommandBuffer commandBuffer,
        DescriptorUpdateTemplate descriptorUpdateTemplate,
        PipelineLayout layout,
        uint32_t set,
        const void* pData) {
        return pfn_CmdPushDescriptorSetWithTemplateKHR(commandBuffer.get(),
            descriptorUpdateTemplate.get(),
            layout.get(),
            set,
            reinterpret_cast<const void*>(pData));
    }
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
#if defined(VK_EXT_conditional_rendering)
    void CmdBeginConditionalRenderingEXT(CommandBuffer commandBuffer,
        const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) {
        return pfn_CmdBeginConditionalRenderingEXT(commandBuffer.get(),
            reinterpret_cast<const VkConditionalRenderingBeginInfoEXT*>(&pConditionalRenderingBegin));
    }
    void CmdEndConditionalRenderingEXT(CommandBuffer commandBuffer) {
        return pfn_CmdEndConditionalRenderingEXT(commandBuffer.get());
    }
#endif //defined(VK_EXT_conditional_rendering)
#if defined(VK_NV_clip_space_w_scaling)
    void CmdSetViewportWScalingNV(CommandBuffer commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        const ViewportWScalingNV* pViewportWScalings) {
        return pfn_CmdSetViewportWScalingNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewportWScalingNV*>(pViewportWScalings));
    }
#endif //defined(VK_NV_clip_space_w_scaling)
#if defined(VK_EXT_display_control)
    [[nodiscard]] Result DisplayPowerControlEXT(DisplayKHR display,
        const DisplayPowerInfoEXT&  pDisplayPowerInfo) {
        return static_cast<Result>(pfn_DisplayPowerControlEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayPowerInfoEXT*>(&pDisplayPowerInfo)));
    }
    [[nodiscard]] Result RegisterDeviceEventEXT(const DeviceEventInfoEXT&  pDeviceEventInfo,
        const AllocationCallbacks* pAllocator,
        Fence&  pFence) {
        return static_cast<Result>(pfn_RegisterDeviceEventEXT(device.get(),
            reinterpret_cast<const VkDeviceEventInfoEXT*>(&pDeviceEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
    }
    [[nodiscard]] Result RegisterDisplayEventEXT(DisplayKHR display,
        const DisplayEventInfoEXT&  pDisplayEventInfo,
        const AllocationCallbacks* pAllocator,
        Fence&  pFence) {
        return static_cast<Result>(pfn_RegisterDisplayEventEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayEventInfoEXT*>(&pDisplayEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
    }
    [[nodiscard]] Result GetSwapchainCounterEXT(SwapchainKHR swapchain,
        SurfaceCounterFlagBitsEXT counter,
        uint64_t&  pCounterValue) {
        return static_cast<Result>(pfn_GetSwapchainCounterEXT(device.get(),
            swapchain.get(),
            static_cast<VkSurfaceCounterFlagBitsEXT>(counter),
            &pCounterValue));
    }
#endif //defined(VK_EXT_display_control)
#if defined(VK_GOOGLE_display_timing)
    [[nodiscard]] Result GetRefreshCycleDurationGOOGLE(SwapchainKHR swapchain,
        RefreshCycleDurationGOOGLE&  pDisplayTimingProperties) {
        return static_cast<Result>(pfn_GetRefreshCycleDurationGOOGLE(device.get(),
            swapchain.get(),
            reinterpret_cast<VkRefreshCycleDurationGOOGLE*>(&pDisplayTimingProperties)));
    }
    [[nodiscard]] Result GetPastPresentationTimingGOOGLE(SwapchainKHR swapchain,
        uint32_t&  pPresentationTimingCount,
        PastPresentationTimingGOOGLE* pPresentationTimings) {
        return static_cast<Result>(pfn_GetPastPresentationTimingGOOGLE(device.get(),
            swapchain.get(),
            &pPresentationTimingCount,
            reinterpret_cast<VkPastPresentationTimingGOOGLE*>(pPresentationTimings)));
    }
#endif //defined(VK_GOOGLE_display_timing)
#if defined(VK_EXT_discard_rectangles)
    void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer,
        uint32_t firstDiscardRectangle,
        uint32_t discardRectangleCount,
        const Rect2D* pDiscardRectangles) {
        return pfn_CmdSetDiscardRectangleEXT(commandBuffer.get(),
            firstDiscardRectangle,
            discardRectangleCount,
            reinterpret_cast<const VkRect2D*>(pDiscardRectangles));
    }
#endif //defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_hdr_metadata)
    void SetHdrMetadataEXT(uint32_t swapchainCount,
        const SwapchainKHR* pSwapchains,
        const HdrMetadataEXT* pMetadata) {
        return pfn_SetHdrMetadataEXT(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainKHR*>(pSwapchains),
            reinterpret_cast<const VkHdrMetadataEXT*>(pMetadata));
    }
#endif //defined(VK_EXT_hdr_metadata)
#if defined(VK_KHR_shared_presentable_image)
    [[nodiscard]] Result GetSwapchainStatusKHR(SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_GetSwapchainStatusKHR(device.get(),
            swapchain.get()));
    }
#endif //defined(VK_KHR_shared_presentable_image)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
    [[nodiscard]] Result GetFenceWin32HandleKHR(const FenceGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkFenceGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result ImportFenceWin32HandleKHR(const ImportFenceWin32HandleInfoKHR&  pImportFenceWin32HandleInfo) {
        return static_cast<Result>(pfn_ImportFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportFenceWin32HandleInfoKHR*>(&pImportFenceWin32HandleInfo)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
#if defined(VK_KHR_external_fence_fd)
    [[nodiscard]] Result GetFenceFdKHR(const FenceGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetFenceFdKHR(device.get(),
            reinterpret_cast<const VkFenceGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result ImportFenceFdKHR(const ImportFenceFdInfoKHR&  pImportFenceFdInfo) {
        return static_cast<Result>(pfn_ImportFenceFdKHR(device.get(),
            reinterpret_cast<const VkImportFenceFdInfoKHR*>(&pImportFenceFdInfo)));
    }
#endif //defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_performance_query)
    [[nodiscard]] Result AcquireProfilingLockKHR(const AcquireProfilingLockInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_AcquireProfilingLockKHR(device.get(),
            reinterpret_cast<const VkAcquireProfilingLockInfoKHR*>(&pInfo)));
    }
    void ReleaseProfilingLockKHR() {
        return pfn_ReleaseProfilingLockKHR(device.get());
    }
#endif //defined(VK_KHR_performance_query)
#if defined(VK_EXT_debug_utils)
    [[nodiscard]] Result SetDebugUtilsObjectNameEXT(const DebugUtilsObjectNameInfoEXT&  pNameInfo) {
        return static_cast<Result>(pfn_SetDebugUtilsObjectNameEXT(device.get(),
            reinterpret_cast<const VkDebugUtilsObjectNameInfoEXT*>(&pNameInfo)));
    }
    [[nodiscard]] Result SetDebugUtilsObjectTagEXT(const DebugUtilsObjectTagInfoEXT&  pTagInfo) {
        return static_cast<Result>(pfn_SetDebugUtilsObjectTagEXT(device.get(),
            reinterpret_cast<const VkDebugUtilsObjectTagInfoEXT*>(&pTagInfo)));
    }
    void QueueBeginDebugUtilsLabelEXT(Queue queue,
        const DebugUtilsLabelEXT&  pLabelInfo) {
        return pfn_QueueBeginDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void QueueEndDebugUtilsLabelEXT(Queue queue) {
        return pfn_QueueEndDebugUtilsLabelEXT(queue.get());
    }
    void QueueInsertDebugUtilsLabelEXT(Queue queue,
        const DebugUtilsLabelEXT&  pLabelInfo) {
        return pfn_QueueInsertDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void CmdBeginDebugUtilsLabelEXT(CommandBuffer commandBuffer,
        const DebugUtilsLabelEXT&  pLabelInfo) {
        return pfn_CmdBeginDebugUtilsLabelEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void CmdEndDebugUtilsLabelEXT(CommandBuffer commandBuffer) {
        return pfn_CmdEndDebugUtilsLabelEXT(commandBuffer.get());
    }
    void CmdInsertDebugUtilsLabelEXT(CommandBuffer commandBuffer,
        const DebugUtilsLabelEXT&  pLabelInfo) {
        return pfn_CmdInsertDebugUtilsLabelEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    [[nodiscard]] Result GetAndroidHardwareBufferPropertiesANDROID(const AHardwareBuffer&  buffer,
        AndroidHardwareBufferPropertiesANDROID&  pProperties) {
        return static_cast<Result>(pfn_GetAndroidHardwareBufferPropertiesANDROID(device.get(),
            &buffer,
            reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID*>(&pProperties)));
    }
    [[nodiscard]] Result GetMemoryAndroidHardwareBufferANDROID(const MemoryGetAndroidHardwareBufferInfoANDROID&  pInfo,
        AHardwareBuffer** pBuffer) {
        return static_cast<Result>(pfn_GetMemoryAndroidHardwareBufferANDROID(device.get(),
            reinterpret_cast<const VkMemoryGetAndroidHardwareBufferInfoANDROID*>(&pInfo),
            pBuffer));
    }
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
#if defined(VK_EXT_sample_locations)
    void CmdSetSampleLocationsEXT(CommandBuffer commandBuffer,
        const SampleLocationsInfoEXT&  pSampleLocationsInfo) {
        return pfn_CmdSetSampleLocationsEXT(commandBuffer.get(),
            reinterpret_cast<const VkSampleLocationsInfoEXT*>(&pSampleLocationsInfo));
    }
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
    void DestroyAccelerationStructureKHR(AccelerationStructureKHR accelerationStructure,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyAccelerationStructureKHR(device.get(),
            accelerationStructure.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void GetAccelerationStructureMemoryRequirementsKHR(const AccelerationStructureMemoryRequirementsInfoKHR&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetAccelerationStructureMemoryRequirementsKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoKHR*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result BindAccelerationStructureMemoryKHR(uint32_t bindInfoCount,
        const BindAccelerationStructureMemoryInfoKHR* pBindInfos) {
        return static_cast<Result>(pfn_BindAccelerationStructureMemoryKHR(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindAccelerationStructureMemoryInfoKHR*>(pBindInfos)));
    }
    void CmdCopyAccelerationStructureKHR(CommandBuffer commandBuffer,
        const CopyAccelerationStructureInfoKHR&  pInfo) {
        return pfn_CmdCopyAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdCopyAccelerationStructureToMemoryKHR(CommandBuffer commandBuffer,
        const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) {
        return pfn_CmdCopyAccelerationStructureToMemoryKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyAccelerationStructureToMemoryKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo)));
    }
    void CmdCopyMemoryToAccelerationStructureKHR(CommandBuffer commandBuffer,
        const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) {
        return pfn_CmdCopyMemoryToAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyMemoryToAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer,
        uint32_t accelerationStructureCount,
        const AccelerationStructureKHR* pAccelerationStructures,
        QueryType queryType,
        QueryPool queryPool,
        uint32_t firstQuery) {
        return pfn_CmdWriteAccelerationStructuresPropertiesKHR(commandBuffer.get(),
            accelerationStructureCount,
            reinterpret_cast<const VkAccelerationStructureKHR*>(pAccelerationStructures),
            static_cast<VkQueryType>(queryType),
            queryPool.get(),
            firstQuery);
    }
    [[nodiscard]] Result WriteAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount,
        const AccelerationStructureKHR* pAccelerationStructures,
        QueryType queryType,
        size_t dataSize,
        void* pData,
        size_t stride) {
        return static_cast<Result>(pfn_WriteAccelerationStructuresPropertiesKHR(device.get(),
            accelerationStructureCount,
            reinterpret_cast<const VkAccelerationStructureKHR*>(pAccelerationStructures),
            static_cast<VkQueryType>(queryType),
            dataSize,
            reinterpret_cast<void*>(pData),
            stride));
    }
    void CmdTraceRaysKHR(CommandBuffer commandBuffer,
        const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return pfn_CmdTraceRaysKHR(commandBuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            width,
            height,
            depth);
    }
    [[nodiscard]] Result GetRayTracingShaderGroupHandlesKHR(Pipeline pipeline,
        uint32_t firstGroup,
        uint32_t groupCount,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetRayTracingShaderGroupHandlesKHR(device.get(),
            pipeline.get(),
            firstGroup,
            groupCount,
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result GetRayTracingCaptureReplayShaderGroupHandlesKHR(Pipeline pipeline,
        uint32_t firstGroup,
        uint32_t groupCount,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR(device.get(),
            pipeline.get(),
            firstGroup,
            groupCount,
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result CreateRayTracingPipelinesKHR(PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const RayTracingPipelineCreateInfoKHR* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateRayTracingPipelinesKHR(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    void CmdTraceRaysIndirectKHR(CommandBuffer commandBuffer,
        const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        Buffer buffer,
        DeviceSize offset) {
        return pfn_CmdTraceRaysIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            buffer.get(),
            offset);
    }
    [[nodiscard]] Result GetDeviceAccelerationStructureCompatibilityKHR(const AccelerationStructureVersionKHR&  version) {
        return static_cast<Result>(pfn_GetDeviceAccelerationStructureCompatibilityKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureVersionKHR*>(&version)));
    }
    [[nodiscard]] Result CreateAccelerationStructureKHR(const AccelerationStructureCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        AccelerationStructureKHR&  pAccelerationStructure) {
        return static_cast<Result>(pfn_CreateAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureKHR*>(&pAccelerationStructure)));
    }
    void CmdBuildAccelerationStructureKHR(CommandBuffer commandBuffer,
        uint32_t infoCount,
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return pfn_CmdBuildAccelerationStructureKHR(commandBuffer.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    void CmdBuildAccelerationStructureIndirectKHR(CommandBuffer commandBuffer,
        const AccelerationStructureBuildGeometryInfoKHR&  pInfo,
        Buffer indirectBuffer,
        DeviceSize indirectOffset,
        uint32_t indirectStride) {
        return pfn_CmdBuildAccelerationStructureIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(&pInfo),
            indirectBuffer.get(),
            indirectOffset,
            indirectStride);
    }
    [[nodiscard]] Result BuildAccelerationStructureKHR(uint32_t infoCount,
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return static_cast<Result>(pfn_BuildAccelerationStructureKHR(device.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos)));
    }
    [[nodiscard]] VkDeviceAddress GetAccelerationStructureDeviceAddressKHR(const AccelerationStructureDeviceAddressInfoKHR&  pInfo) {
        return pfn_GetAccelerationStructureDeviceAddressKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureDeviceAddressInfoKHR*>(&pInfo));
    }
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
#if defined(VK_EXT_image_drm_format_modifier)
    [[nodiscard]] Result GetImageDrmFormatModifierPropertiesEXT(Image image,
        ImageDrmFormatModifierPropertiesEXT&  pProperties) {
        return static_cast<Result>(pfn_GetImageDrmFormatModifierPropertiesEXT(device.get(),
            image.get(),
            reinterpret_cast<VkImageDrmFormatModifierPropertiesEXT*>(&pProperties)));
    }
#endif //defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_validation_cache)
    [[nodiscard]] Result CreateValidationCacheEXT(const ValidationCacheCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        ValidationCacheEXT&  pValidationCache) {
        return static_cast<Result>(pfn_CreateValidationCacheEXT(device.get(),
            reinterpret_cast<const VkValidationCacheCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkValidationCacheEXT*>(&pValidationCache)));
    }
    void DestroyValidationCacheEXT(ValidationCacheEXT validationCache,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyValidationCacheEXT(device.get(),
            validationCache.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetValidationCacheDataEXT(ValidationCacheEXT validationCache,
        size_t&  pDataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetValidationCacheDataEXT(device.get(),
            validationCache.get(),
            &pDataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result MergeValidationCachesEXT(ValidationCacheEXT dstCache,
        uint32_t srcCacheCount,
        const ValidationCacheEXT* pSrcCaches) {
        return static_cast<Result>(pfn_MergeValidationCachesEXT(device.get(),
            dstCache.get(),
            srcCacheCount,
            reinterpret_cast<const VkValidationCacheEXT*>(pSrcCaches)));
    }
#endif //defined(VK_EXT_validation_cache)
#if defined(VK_NV_shading_rate_image)
    void CmdBindShadingRateImageNV(CommandBuffer commandBuffer,
        ImageView imageView,
        ImageLayout imageLayout) {
        return pfn_CmdBindShadingRateImageNV(commandBuffer.get(),
            imageView.get(),
            static_cast<VkImageLayout>(imageLayout));
    }
    void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        const ShadingRatePaletteNV* pShadingRatePalettes) {
        return pfn_CmdSetViewportShadingRatePaletteNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkShadingRatePaletteNV*>(pShadingRatePalettes));
    }
    void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer,
        CoarseSampleOrderTypeNV sampleOrderType,
        uint32_t customSampleOrderCount,
        const CoarseSampleOrderCustomNV* pCustomSampleOrders) {
        return pfn_CmdSetCoarseSampleOrderNV(commandBuffer.get(),
            static_cast<VkCoarseSampleOrderTypeNV>(sampleOrderType),
            customSampleOrderCount,
            reinterpret_cast<const VkCoarseSampleOrderCustomNV*>(pCustomSampleOrders));
    }
#endif //defined(VK_NV_shading_rate_image)
#if defined(VK_NV_ray_tracing)
    [[nodiscard]] Result CompileDeferredNV(Pipeline pipeline,
        uint32_t shader) {
        return static_cast<Result>(pfn_CompileDeferredNV(device.get(),
            pipeline.get(),
            shader));
    }
    [[nodiscard]] Result CreateAccelerationStructureNV(const AccelerationStructureCreateInfoNV&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        AccelerationStructureNV&  pAccelerationStructure) {
        return static_cast<Result>(pfn_CreateAccelerationStructureNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureNV*>(&pAccelerationStructure)));
    }
    void GetAccelerationStructureMemoryRequirementsNV(const AccelerationStructureMemoryRequirementsInfoNV&  pInfo,
        MemoryRequirements2KHR&  pMemoryRequirements) {
        return pfn_GetAccelerationStructureMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2KHR*>(&pMemoryRequirements));
    }
    void CmdCopyAccelerationStructureNV(CommandBuffer commandBuffer,
        AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        CopyAccelerationStructureModeKHR mode) {
        return pfn_CmdCopyAccelerationStructureNV(commandBuffer.get(),
            dst.get(),
            src.get(),
            static_cast<VkCopyAccelerationStructureModeKHR>(mode));
    }
    void CmdBuildAccelerationStructureNV(CommandBuffer commandBuffer,
        const AccelerationStructureInfoNV&  pInfo,
        Buffer instanceData,
        DeviceSize instanceOffset,
        Bool32 update,
        AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        Buffer scratch,
        DeviceSize scratchOffset) {
        return pfn_CmdBuildAccelerationStructureNV(commandBuffer.get(),
            reinterpret_cast<const VkAccelerationStructureInfoNV*>(&pInfo),
            instanceData.get(),
            instanceOffset,
            update,
            dst.get(),
            src.get(),
            scratch.get(),
            scratchOffset);
    }
    void CmdTraceRaysNV(CommandBuffer commandBuffer,
        Buffer raygenShaderBindingTableBuffer,
        DeviceSize raygenShaderBindingOffset,
        Buffer missShaderBindingTableBuffer,
        DeviceSize missShaderBindingOffset,
        DeviceSize missShaderBindingStride,
        Buffer hitShaderBindingTableBuffer,
        DeviceSize hitShaderBindingOffset,
        DeviceSize hitShaderBindingStride,
        Buffer callableShaderBindingTableBuffer,
        DeviceSize callableShaderBindingOffset,
        DeviceSize callableShaderBindingStride,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return pfn_CmdTraceRaysNV(commandBuffer.get(),
            raygenShaderBindingTableBuffer.get(),
            raygenShaderBindingOffset,
            missShaderBindingTableBuffer.get(),
            missShaderBindingOffset,
            missShaderBindingStride,
            hitShaderBindingTableBuffer.get(),
            hitShaderBindingOffset,
            hitShaderBindingStride,
            callableShaderBindingTableBuffer.get(),
            callableShaderBindingOffset,
            callableShaderBindingStride,
            width,
            height,
            depth);
    }
    [[nodiscard]] Result GetAccelerationStructureHandleNV(AccelerationStructureKHR accelerationStructure,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetAccelerationStructureHandleNV(device.get(),
            accelerationStructure.get(),
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result CreateRayTracingPipelinesNV(PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const RayTracingPipelineCreateInfoNV* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateRayTracingPipelinesNV(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkRayTracingPipelineCreateInfoNV*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
#endif //defined(VK_NV_ray_tracing)
#if defined(VK_EXT_external_memory_host)
    [[nodiscard]] Result GetMemoryHostPointerPropertiesEXT(ExternalMemoryHandleTypeFlagBits handleType,
        const void* pHostPointer,
        MemoryHostPointerPropertiesEXT&  pMemoryHostPointerProperties) {
        return static_cast<Result>(pfn_GetMemoryHostPointerPropertiesEXT(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            reinterpret_cast<const void*>(pHostPointer),
            reinterpret_cast<VkMemoryHostPointerPropertiesEXT*>(&pMemoryHostPointerProperties)));
    }
#endif //defined(VK_EXT_external_memory_host)
#if defined(VK_AMD_buffer_marker)
    void CmdWriteBufferMarkerAMD(CommandBuffer commandBuffer,
        PipelineStageFlagBits pipelineStage,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        uint32_t marker) {
        return pfn_CmdWriteBufferMarkerAMD(commandBuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            dstBuffer.get(),
            dstOffset,
            marker);
    }
#endif //defined(VK_AMD_buffer_marker)
#if defined(VK_EXT_calibrated_timestamps)
    [[nodiscard]] Result GetCalibratedTimestampsEXT(uint32_t timestampCount,
        const CalibratedTimestampInfoEXT* pTimestampInfos,
        uint64_t* pTimestamps,
        uint64_t&  pMaxDeviation) {
        return static_cast<Result>(pfn_GetCalibratedTimestampsEXT(device.get(),
            timestampCount,
            reinterpret_cast<const VkCalibratedTimestampInfoEXT*>(pTimestampInfos),
            pTimestamps,
            &pMaxDeviation));
    }
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_NV_mesh_shader)
    void CmdDrawMeshTasksNV(CommandBuffer commandBuffer,
        uint32_t taskCount,
        uint32_t firstTask) {
        return pfn_CmdDrawMeshTasksNV(commandBuffer.get(),
            taskCount,
            firstTask);
    }
    void CmdDrawMeshTasksIndirectNV(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return pfn_CmdDrawMeshTasksIndirectNV(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDrawMeshTasksIndirectCountNV(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return pfn_CmdDrawMeshTasksIndirectCountNV(commandBuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
#endif //defined(VK_NV_mesh_shader)
#if defined(VK_NV_scissor_exclusive)
    void CmdSetExclusiveScissorNV(CommandBuffer commandBuffer,
        uint32_t firstExclusiveScissor,
        uint32_t exclusiveScissorCount,
        const Rect2D* pExclusiveScissors) {
        return pfn_CmdSetExclusiveScissorNV(commandBuffer.get(),
            firstExclusiveScissor,
            exclusiveScissorCount,
            reinterpret_cast<const VkRect2D*>(pExclusiveScissors));
    }
#endif //defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_device_diagnostic_checkpoints)
    void CmdSetCheckpointNV(CommandBuffer commandBuffer,
        const void* pCheckpointMarker) {
        return pfn_CmdSetCheckpointNV(commandBuffer.get(),
            reinterpret_cast<const void*>(pCheckpointMarker));
    }
    void GetQueueCheckpointDataNV(Queue queue,
        uint32_t&  pCheckpointDataCount,
        CheckpointDataNV* pCheckpointData) {
        return pfn_GetQueueCheckpointDataNV(queue.get(),
            &pCheckpointDataCount,
            reinterpret_cast<VkCheckpointDataNV*>(pCheckpointData));
    }
#endif //defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_INTEL_performance_query)
    [[nodiscard]] Result InitializePerformanceApiINTEL(const InitializePerformanceApiInfoINTEL&  pInitializeInfo) {
        return static_cast<Result>(pfn_InitializePerformanceApiINTEL(device.get(),
            reinterpret_cast<const VkInitializePerformanceApiInfoINTEL*>(&pInitializeInfo)));
    }
    void UninitializePerformanceApiINTEL() {
        return pfn_UninitializePerformanceApiINTEL(device.get());
    }
    [[nodiscard]] Result CmdSetPerformanceMarkerINTEL(CommandBuffer commandBuffer,
        const PerformanceMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceStreamMarkerINTEL(CommandBuffer commandBuffer,
        const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceStreamMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceOverrideINTEL(CommandBuffer commandBuffer,
        const PerformanceOverrideInfoINTEL&  pOverrideInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceOverrideINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceOverrideInfoINTEL*>(&pOverrideInfo)));
    }
    [[nodiscard]] Result AcquirePerformanceConfigurationINTEL(const PerformanceConfigurationAcquireInfoINTEL&  pAcquireInfo,
        PerformanceConfigurationINTEL&  pConfiguration) {
        return static_cast<Result>(pfn_AcquirePerformanceConfigurationINTEL(device.get(),
            reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL*>(&pAcquireInfo),
            reinterpret_cast<VkPerformanceConfigurationINTEL*>(&pConfiguration)));
    }
    [[nodiscard]] Result ReleasePerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) {
        return static_cast<Result>(pfn_ReleasePerformanceConfigurationINTEL(device.get(),
            configuration.get()));
    }
    [[nodiscard]] Result QueueSetPerformanceConfigurationINTEL(Queue queue,
        PerformanceConfigurationINTEL configuration) {
        return static_cast<Result>(pfn_QueueSetPerformanceConfigurationINTEL(queue.get(),
            configuration.get()));
    }
    [[nodiscard]] Result GetPerformanceParameterINTEL(PerformanceParameterTypeINTEL parameter,
        PerformanceValueINTEL&  pValue) {
        return static_cast<Result>(pfn_GetPerformanceParameterINTEL(device.get(),
            static_cast<VkPerformanceParameterTypeINTEL>(parameter),
            reinterpret_cast<VkPerformanceValueINTEL*>(&pValue)));
    }
#endif //defined(VK_INTEL_performance_query)
#if defined(VK_AMD_display_native_hdr)
    void SetLocalDimmingAMD(SwapchainKHR swapChain,
        Bool32 localDimmingEnable) {
        return pfn_SetLocalDimmingAMD(device.get(),
            swapChain.get(),
            localDimmingEnable);
    }
#endif //defined(VK_AMD_display_native_hdr)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    [[nodiscard]] Result AcquireFullScreenExclusiveModeEXT(SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_AcquireFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
    [[nodiscard]] Result ReleaseFullScreenExclusiveModeEXT(SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_ReleaseFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    [[nodiscard]] Result GetDeviceGroupSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        DeviceGroupPresentModeFlagsKHR&  pModes) {
        return static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModes2EXT(device.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
#if defined(VK_EXT_line_rasterization)
    void CmdSetLineStippleEXT(CommandBuffer commandBuffer,
        uint32_t lineStippleFactor,
        uint16_t lineStipplePattern) {
        return pfn_CmdSetLineStippleEXT(commandBuffer.get(),
            lineStippleFactor,
            lineStipplePattern);
    }
#endif //defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_extended_dynamic_state)
    void CmdSetCullModeEXT(CommandBuffer commandBuffer,
        CullModeFlags cullMode) {
        return pfn_CmdSetCullModeEXT(commandBuffer.get(),
            static_cast<VkCullModeFlags>(cullMode));
    }
    void CmdSetFrontFaceEXT(CommandBuffer commandBuffer,
        FrontFace frontFace) {
        return pfn_CmdSetFrontFaceEXT(commandBuffer.get(),
            static_cast<VkFrontFace>(frontFace));
    }
    void CmdSetPrimitiveTopologyEXT(CommandBuffer commandBuffer,
        PrimitiveTopology primitiveTopology) {
        return pfn_CmdSetPrimitiveTopologyEXT(commandBuffer.get(),
            static_cast<VkPrimitiveTopology>(primitiveTopology));
    }
    void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer,
        uint32_t viewportCount,
        const Viewport* pViewports) {
        return pfn_CmdSetViewportWithCountEXT(commandBuffer.get(),
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer,
        uint32_t scissorCount,
        const Rect2D* pScissors) {
        return pfn_CmdSetScissorWithCountEXT(commandBuffer.get(),
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer,
        uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes,
        const DeviceSize* pStrides) {
        return pfn_CmdBindVertexBuffers2EXT(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes,
            pStrides);
    }
    void CmdSetDepthTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthTestEnable) {
        return pfn_CmdSetDepthTestEnableEXT(commandBuffer.get(),
            depthTestEnable);
    }
    void CmdSetDepthWriteEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthWriteEnable) {
        return pfn_CmdSetDepthWriteEnableEXT(commandBuffer.get(),
            depthWriteEnable);
    }
    void CmdSetDepthCompareOpEXT(CommandBuffer commandBuffer,
        CompareOp depthCompareOp) {
        return pfn_CmdSetDepthCompareOpEXT(commandBuffer.get(),
            static_cast<VkCompareOp>(depthCompareOp));
    }
    void CmdSetDepthBoundsTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthBoundsTestEnable) {
        return pfn_CmdSetDepthBoundsTestEnableEXT(commandBuffer.get(),
            depthBoundsTestEnable);
    }
    void CmdSetStencilTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 stencilTestEnable) {
        return pfn_CmdSetStencilTestEnableEXT(commandBuffer.get(),
            stencilTestEnable);
    }
    void CmdSetStencilOpEXT(CommandBuffer commandBuffer,
        StencilFaceFlags faceMask,
        StencilOp failOp,
        StencilOp passOp,
        StencilOp depthFailOp,
        CompareOp compareOp) {
        return pfn_CmdSetStencilOpEXT(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            static_cast<VkStencilOp>(failOp),
            static_cast<VkStencilOp>(passOp),
            static_cast<VkStencilOp>(depthFailOp),
            static_cast<VkCompareOp>(compareOp));
    }
#endif //defined(VK_EXT_extended_dynamic_state)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
    [[nodiscard]] Result CreateDeferredOperationKHR(const AllocationCallbacks* pAllocator,
        DeferredOperationKHR&  pDeferredOperation) {
        return static_cast<Result>(pfn_CreateDeferredOperationKHR(device.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDeferredOperationKHR*>(&pDeferredOperation)));
    }
    void DestroyDeferredOperationKHR(DeferredOperationKHR operation,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDeferredOperationKHR(device.get(),
            operation.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] uint32_t GetDeferredOperationMaxConcurrencyKHR(DeferredOperationKHR operation) {
        return pfn_GetDeferredOperationMaxConcurrencyKHR(device.get(),
            operation.get());
    }
    [[nodiscard]] Result GetDeferredOperationResultKHR(DeferredOperationKHR operation) {
        return static_cast<Result>(pfn_GetDeferredOperationResultKHR(device.get(),
            operation.get()));
    }
    [[nodiscard]] Result DeferredOperationJoinKHR(DeferredOperationKHR operation) {
        return static_cast<Result>(pfn_DeferredOperationJoinKHR(device.get(),
            operation.get()));
    }
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
#if defined(VK_KHR_pipeline_executable_properties)
    [[nodiscard]] Result GetPipelineExecutablePropertiesKHR(const PipelineInfoKHR&  pPipelineInfo,
        uint32_t&  pExecutableCount,
        PipelineExecutablePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPipelineExecutablePropertiesKHR(device.get(),
            reinterpret_cast<const VkPipelineInfoKHR*>(&pPipelineInfo),
            &pExecutableCount,
            reinterpret_cast<VkPipelineExecutablePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPipelineExecutableStatisticsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo,
        uint32_t&  pStatisticCount,
        PipelineExecutableStatisticKHR* pStatistics) {
        return static_cast<Result>(pfn_GetPipelineExecutableStatisticsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pStatisticCount,
            reinterpret_cast<VkPipelineExecutableStatisticKHR*>(pStatistics)));
    }
    [[nodiscard]] Result GetPipelineExecutableInternalRepresentationsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo,
        uint32_t&  pInternalRepresentationCount,
        PipelineExecutableInternalRepresentationKHR* pInternalRepresentations) {
        return static_cast<Result>(pfn_GetPipelineExecutableInternalRepresentationsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pInternalRepresentationCount,
            reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR*>(pInternalRepresentations)));
    }
#endif //defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_NV_device_generated_commands)
    void CmdExecuteGeneratedCommandsNV(CommandBuffer commandBuffer,
        Bool32 isPreprocessed,
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return pfn_CmdExecuteGeneratedCommandsNV(commandBuffer.get(),
            isPreprocessed,
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdPreprocessGeneratedCommandsNV(CommandBuffer commandBuffer,
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return pfn_CmdPreprocessGeneratedCommandsNV(commandBuffer.get(),
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdBindPipelineShaderGroupNV(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        Pipeline pipeline,
        uint32_t groupIndex) {
        return pfn_CmdBindPipelineShaderGroupNV(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get(),
            groupIndex);
    }
    void GetGeneratedCommandsMemoryRequirementsNV(const GeneratedCommandsMemoryRequirementsInfoNV&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetGeneratedCommandsMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result CreateIndirectCommandsLayoutNV(const IndirectCommandsLayoutCreateInfoNV&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        IndirectCommandsLayoutNV&  pIndirectCommandsLayout) {
        return static_cast<Result>(pfn_CreateIndirectCommandsLayoutNV(device.get(),
            reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkIndirectCommandsLayoutNV*>(&pIndirectCommandsLayout)));
    }
    void DestroyIndirectCommandsLayoutNV(IndirectCommandsLayoutNV indirectCommandsLayout,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyIndirectCommandsLayoutNV(device.get(),
            indirectCommandsLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
#endif //defined(VK_NV_device_generated_commands)
#if defined(VK_EXT_private_data)
    [[nodiscard]] Result CreatePrivateDataSlotEXT(const PrivateDataSlotCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        PrivateDataSlotEXT&  pPrivateDataSlot) {
        return static_cast<Result>(pfn_CreatePrivateDataSlotEXT(device.get(),
            reinterpret_cast<const VkPrivateDataSlotCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPrivateDataSlotEXT*>(&pPrivateDataSlot)));
    }
    void DestroyPrivateDataSlotEXT(PrivateDataSlotEXT privateDataSlot,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyPrivateDataSlotEXT(device.get(),
            privateDataSlot.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result SetPrivateDataEXT(ObjectType objectType,
        uint64_t objectHandle,
        PrivateDataSlotEXT privateDataSlot,
        uint64_t data) {
        return static_cast<Result>(pfn_SetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            data));
    }
    void GetPrivateDataEXT(ObjectType objectType,
        uint64_t objectHandle,
        PrivateDataSlotEXT privateDataSlot,
        uint64_t&  pData) {
        return pfn_GetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            &pData);
    }
#endif //defined(VK_EXT_private_data)
    DeviceFunctions(InstanceFunctions const& instance_functions, Device device){
    PFN_vkGetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
#if defined(VK_VERSION_1_0)
        pfn_DestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(get_device_proc_addr(device.get(),"vkDestroyDevice"));
        pfn_GetDeviceQueue = reinterpret_cast<PFN_vkGetDeviceQueue>(get_device_proc_addr(device.get(),"vkGetDeviceQueue"));
        pfn_QueueSubmit = reinterpret_cast<PFN_vkQueueSubmit>(get_device_proc_addr(device.get(),"vkQueueSubmit"));
        pfn_QueueWaitIdle = reinterpret_cast<PFN_vkQueueWaitIdle>(get_device_proc_addr(device.get(),"vkQueueWaitIdle"));
        pfn_DeviceWaitIdle = reinterpret_cast<PFN_vkDeviceWaitIdle>(get_device_proc_addr(device.get(),"vkDeviceWaitIdle"));
        pfn_AllocateMemory = reinterpret_cast<PFN_vkAllocateMemory>(get_device_proc_addr(device.get(),"vkAllocateMemory"));
        pfn_FreeMemory = reinterpret_cast<PFN_vkFreeMemory>(get_device_proc_addr(device.get(),"vkFreeMemory"));
        pfn_MapMemory = reinterpret_cast<PFN_vkMapMemory>(get_device_proc_addr(device.get(),"vkMapMemory"));
        pfn_UnmapMemory = reinterpret_cast<PFN_vkUnmapMemory>(get_device_proc_addr(device.get(),"vkUnmapMemory"));
        pfn_FlushMappedMemoryRanges = reinterpret_cast<PFN_vkFlushMappedMemoryRanges>(get_device_proc_addr(device.get(),"vkFlushMappedMemoryRanges"));
        pfn_InvalidateMappedMemoryRanges = reinterpret_cast<PFN_vkInvalidateMappedMemoryRanges>(get_device_proc_addr(device.get(),"vkInvalidateMappedMemoryRanges"));
        pfn_GetDeviceMemoryCommitment = reinterpret_cast<PFN_vkGetDeviceMemoryCommitment>(get_device_proc_addr(device.get(),"vkGetDeviceMemoryCommitment"));
        pfn_GetBufferMemoryRequirements = reinterpret_cast<PFN_vkGetBufferMemoryRequirements>(get_device_proc_addr(device.get(),"vkGetBufferMemoryRequirements"));
        pfn_BindBufferMemory = reinterpret_cast<PFN_vkBindBufferMemory>(get_device_proc_addr(device.get(),"vkBindBufferMemory"));
        pfn_GetImageMemoryRequirements = reinterpret_cast<PFN_vkGetImageMemoryRequirements>(get_device_proc_addr(device.get(),"vkGetImageMemoryRequirements"));
        pfn_BindImageMemory = reinterpret_cast<PFN_vkBindImageMemory>(get_device_proc_addr(device.get(),"vkBindImageMemory"));
        pfn_GetImageSparseMemoryRequirements = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements>(get_device_proc_addr(device.get(),"vkGetImageSparseMemoryRequirements"));
        pfn_QueueBindSparse = reinterpret_cast<PFN_vkQueueBindSparse>(get_device_proc_addr(device.get(),"vkQueueBindSparse"));
        pfn_CreateFence = reinterpret_cast<PFN_vkCreateFence>(get_device_proc_addr(device.get(),"vkCreateFence"));
        pfn_DestroyFence = reinterpret_cast<PFN_vkDestroyFence>(get_device_proc_addr(device.get(),"vkDestroyFence"));
        pfn_ResetFences = reinterpret_cast<PFN_vkResetFences>(get_device_proc_addr(device.get(),"vkResetFences"));
        pfn_GetFenceStatus = reinterpret_cast<PFN_vkGetFenceStatus>(get_device_proc_addr(device.get(),"vkGetFenceStatus"));
        pfn_WaitForFences = reinterpret_cast<PFN_vkWaitForFences>(get_device_proc_addr(device.get(),"vkWaitForFences"));
        pfn_CreateSemaphore = reinterpret_cast<PFN_vkCreateSemaphore>(get_device_proc_addr(device.get(),"vkCreateSemaphore"));
        pfn_DestroySemaphore = reinterpret_cast<PFN_vkDestroySemaphore>(get_device_proc_addr(device.get(),"vkDestroySemaphore"));
        pfn_CreateEvent = reinterpret_cast<PFN_vkCreateEvent>(get_device_proc_addr(device.get(),"vkCreateEvent"));
        pfn_DestroyEvent = reinterpret_cast<PFN_vkDestroyEvent>(get_device_proc_addr(device.get(),"vkDestroyEvent"));
        pfn_GetEventStatus = reinterpret_cast<PFN_vkGetEventStatus>(get_device_proc_addr(device.get(),"vkGetEventStatus"));
        pfn_SetEvent = reinterpret_cast<PFN_vkSetEvent>(get_device_proc_addr(device.get(),"vkSetEvent"));
        pfn_ResetEvent = reinterpret_cast<PFN_vkResetEvent>(get_device_proc_addr(device.get(),"vkResetEvent"));
        pfn_CreateQueryPool = reinterpret_cast<PFN_vkCreateQueryPool>(get_device_proc_addr(device.get(),"vkCreateQueryPool"));
        pfn_DestroyQueryPool = reinterpret_cast<PFN_vkDestroyQueryPool>(get_device_proc_addr(device.get(),"vkDestroyQueryPool"));
        pfn_GetQueryPoolResults = reinterpret_cast<PFN_vkGetQueryPoolResults>(get_device_proc_addr(device.get(),"vkGetQueryPoolResults"));
        pfn_CreateBuffer = reinterpret_cast<PFN_vkCreateBuffer>(get_device_proc_addr(device.get(),"vkCreateBuffer"));
        pfn_DestroyBuffer = reinterpret_cast<PFN_vkDestroyBuffer>(get_device_proc_addr(device.get(),"vkDestroyBuffer"));
        pfn_CreateBufferView = reinterpret_cast<PFN_vkCreateBufferView>(get_device_proc_addr(device.get(),"vkCreateBufferView"));
        pfn_DestroyBufferView = reinterpret_cast<PFN_vkDestroyBufferView>(get_device_proc_addr(device.get(),"vkDestroyBufferView"));
        pfn_CreateImage = reinterpret_cast<PFN_vkCreateImage>(get_device_proc_addr(device.get(),"vkCreateImage"));
        pfn_DestroyImage = reinterpret_cast<PFN_vkDestroyImage>(get_device_proc_addr(device.get(),"vkDestroyImage"));
        pfn_GetImageSubresourceLayout = reinterpret_cast<PFN_vkGetImageSubresourceLayout>(get_device_proc_addr(device.get(),"vkGetImageSubresourceLayout"));
        pfn_CreateImageView = reinterpret_cast<PFN_vkCreateImageView>(get_device_proc_addr(device.get(),"vkCreateImageView"));
        pfn_DestroyImageView = reinterpret_cast<PFN_vkDestroyImageView>(get_device_proc_addr(device.get(),"vkDestroyImageView"));
        pfn_CreateShaderModule = reinterpret_cast<PFN_vkCreateShaderModule>(get_device_proc_addr(device.get(),"vkCreateShaderModule"));
        pfn_DestroyShaderModule = reinterpret_cast<PFN_vkDestroyShaderModule>(get_device_proc_addr(device.get(),"vkDestroyShaderModule"));
        pfn_CreatePipelineCache = reinterpret_cast<PFN_vkCreatePipelineCache>(get_device_proc_addr(device.get(),"vkCreatePipelineCache"));
        pfn_DestroyPipelineCache = reinterpret_cast<PFN_vkDestroyPipelineCache>(get_device_proc_addr(device.get(),"vkDestroyPipelineCache"));
        pfn_GetPipelineCacheData = reinterpret_cast<PFN_vkGetPipelineCacheData>(get_device_proc_addr(device.get(),"vkGetPipelineCacheData"));
        pfn_MergePipelineCaches = reinterpret_cast<PFN_vkMergePipelineCaches>(get_device_proc_addr(device.get(),"vkMergePipelineCaches"));
        pfn_CreateGraphicsPipelines = reinterpret_cast<PFN_vkCreateGraphicsPipelines>(get_device_proc_addr(device.get(),"vkCreateGraphicsPipelines"));
        pfn_CreateComputePipelines = reinterpret_cast<PFN_vkCreateComputePipelines>(get_device_proc_addr(device.get(),"vkCreateComputePipelines"));
        pfn_DestroyPipeline = reinterpret_cast<PFN_vkDestroyPipeline>(get_device_proc_addr(device.get(),"vkDestroyPipeline"));
        pfn_CreatePipelineLayout = reinterpret_cast<PFN_vkCreatePipelineLayout>(get_device_proc_addr(device.get(),"vkCreatePipelineLayout"));
        pfn_DestroyPipelineLayout = reinterpret_cast<PFN_vkDestroyPipelineLayout>(get_device_proc_addr(device.get(),"vkDestroyPipelineLayout"));
        pfn_CreateSampler = reinterpret_cast<PFN_vkCreateSampler>(get_device_proc_addr(device.get(),"vkCreateSampler"));
        pfn_DestroySampler = reinterpret_cast<PFN_vkDestroySampler>(get_device_proc_addr(device.get(),"vkDestroySampler"));
        pfn_CreateDescriptorSetLayout = reinterpret_cast<PFN_vkCreateDescriptorSetLayout>(get_device_proc_addr(device.get(),"vkCreateDescriptorSetLayout"));
        pfn_DestroyDescriptorSetLayout = reinterpret_cast<PFN_vkDestroyDescriptorSetLayout>(get_device_proc_addr(device.get(),"vkDestroyDescriptorSetLayout"));
        pfn_CreateDescriptorPool = reinterpret_cast<PFN_vkCreateDescriptorPool>(get_device_proc_addr(device.get(),"vkCreateDescriptorPool"));
        pfn_DestroyDescriptorPool = reinterpret_cast<PFN_vkDestroyDescriptorPool>(get_device_proc_addr(device.get(),"vkDestroyDescriptorPool"));
        pfn_ResetDescriptorPool = reinterpret_cast<PFN_vkResetDescriptorPool>(get_device_proc_addr(device.get(),"vkResetDescriptorPool"));
        pfn_AllocateDescriptorSets = reinterpret_cast<PFN_vkAllocateDescriptorSets>(get_device_proc_addr(device.get(),"vkAllocateDescriptorSets"));
        pfn_FreeDescriptorSets = reinterpret_cast<PFN_vkFreeDescriptorSets>(get_device_proc_addr(device.get(),"vkFreeDescriptorSets"));
        pfn_UpdateDescriptorSets = reinterpret_cast<PFN_vkUpdateDescriptorSets>(get_device_proc_addr(device.get(),"vkUpdateDescriptorSets"));
        pfn_CreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(get_device_proc_addr(device.get(),"vkCreateFramebuffer"));
        pfn_DestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(get_device_proc_addr(device.get(),"vkDestroyFramebuffer"));
        pfn_CreateRenderPass = reinterpret_cast<PFN_vkCreateRenderPass>(get_device_proc_addr(device.get(),"vkCreateRenderPass"));
        pfn_DestroyRenderPass = reinterpret_cast<PFN_vkDestroyRenderPass>(get_device_proc_addr(device.get(),"vkDestroyRenderPass"));
        pfn_GetRenderAreaGranularity = reinterpret_cast<PFN_vkGetRenderAreaGranularity>(get_device_proc_addr(device.get(),"vkGetRenderAreaGranularity"));
        pfn_CreateCommandPool = reinterpret_cast<PFN_vkCreateCommandPool>(get_device_proc_addr(device.get(),"vkCreateCommandPool"));
        pfn_DestroyCommandPool = reinterpret_cast<PFN_vkDestroyCommandPool>(get_device_proc_addr(device.get(),"vkDestroyCommandPool"));
        pfn_ResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(get_device_proc_addr(device.get(),"vkResetCommandPool"));
        pfn_AllocateCommandBuffers = reinterpret_cast<PFN_vkAllocateCommandBuffers>(get_device_proc_addr(device.get(),"vkAllocateCommandBuffers"));
        pfn_FreeCommandBuffers = reinterpret_cast<PFN_vkFreeCommandBuffers>(get_device_proc_addr(device.get(),"vkFreeCommandBuffers"));
        pfn_BeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(get_device_proc_addr(device.get(),"vkBeginCommandBuffer"));
        pfn_EndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(get_device_proc_addr(device.get(),"vkEndCommandBuffer"));
        pfn_ResetCommandBuffer = reinterpret_cast<PFN_vkResetCommandBuffer>(get_device_proc_addr(device.get(),"vkResetCommandBuffer"));
        pfn_CmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(get_device_proc_addr(device.get(),"vkCmdBindPipeline"));
        pfn_CmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(get_device_proc_addr(device.get(),"vkCmdSetViewport"));
        pfn_CmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(get_device_proc_addr(device.get(),"vkCmdSetScissor"));
        pfn_CmdSetLineWidth = reinterpret_cast<PFN_vkCmdSetLineWidth>(get_device_proc_addr(device.get(),"vkCmdSetLineWidth"));
        pfn_CmdSetDepthBias = reinterpret_cast<PFN_vkCmdSetDepthBias>(get_device_proc_addr(device.get(),"vkCmdSetDepthBias"));
        pfn_CmdSetBlendConstants = reinterpret_cast<PFN_vkCmdSetBlendConstants>(get_device_proc_addr(device.get(),"vkCmdSetBlendConstants"));
        pfn_CmdSetDepthBounds = reinterpret_cast<PFN_vkCmdSetDepthBounds>(get_device_proc_addr(device.get(),"vkCmdSetDepthBounds"));
        pfn_CmdSetStencilCompareMask = reinterpret_cast<PFN_vkCmdSetStencilCompareMask>(get_device_proc_addr(device.get(),"vkCmdSetStencilCompareMask"));
        pfn_CmdSetStencilWriteMask = reinterpret_cast<PFN_vkCmdSetStencilWriteMask>(get_device_proc_addr(device.get(),"vkCmdSetStencilWriteMask"));
        pfn_CmdSetStencilReference = reinterpret_cast<PFN_vkCmdSetStencilReference>(get_device_proc_addr(device.get(),"vkCmdSetStencilReference"));
        pfn_CmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(get_device_proc_addr(device.get(),"vkCmdBindDescriptorSets"));
        pfn_CmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(get_device_proc_addr(device.get(),"vkCmdBindIndexBuffer"));
        pfn_CmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(get_device_proc_addr(device.get(),"vkCmdBindVertexBuffers"));
        pfn_CmdDraw = reinterpret_cast<PFN_vkCmdDraw>(get_device_proc_addr(device.get(),"vkCmdDraw"));
        pfn_CmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(get_device_proc_addr(device.get(),"vkCmdDrawIndexed"));
        pfn_CmdDrawIndirect = reinterpret_cast<PFN_vkCmdDrawIndirect>(get_device_proc_addr(device.get(),"vkCmdDrawIndirect"));
        pfn_CmdDrawIndexedIndirect = reinterpret_cast<PFN_vkCmdDrawIndexedIndirect>(get_device_proc_addr(device.get(),"vkCmdDrawIndexedIndirect"));
        pfn_CmdDispatch = reinterpret_cast<PFN_vkCmdDispatch>(get_device_proc_addr(device.get(),"vkCmdDispatch"));
        pfn_CmdDispatchIndirect = reinterpret_cast<PFN_vkCmdDispatchIndirect>(get_device_proc_addr(device.get(),"vkCmdDispatchIndirect"));
        pfn_CmdCopyBuffer = reinterpret_cast<PFN_vkCmdCopyBuffer>(get_device_proc_addr(device.get(),"vkCmdCopyBuffer"));
        pfn_CmdCopyImage = reinterpret_cast<PFN_vkCmdCopyImage>(get_device_proc_addr(device.get(),"vkCmdCopyImage"));
        pfn_CmdBlitImage = reinterpret_cast<PFN_vkCmdBlitImage>(get_device_proc_addr(device.get(),"vkCmdBlitImage"));
        pfn_CmdCopyBufferToImage = reinterpret_cast<PFN_vkCmdCopyBufferToImage>(get_device_proc_addr(device.get(),"vkCmdCopyBufferToImage"));
        pfn_CmdCopyImageToBuffer = reinterpret_cast<PFN_vkCmdCopyImageToBuffer>(get_device_proc_addr(device.get(),"vkCmdCopyImageToBuffer"));
        pfn_CmdUpdateBuffer = reinterpret_cast<PFN_vkCmdUpdateBuffer>(get_device_proc_addr(device.get(),"vkCmdUpdateBuffer"));
        pfn_CmdFillBuffer = reinterpret_cast<PFN_vkCmdFillBuffer>(get_device_proc_addr(device.get(),"vkCmdFillBuffer"));
        pfn_CmdClearColorImage = reinterpret_cast<PFN_vkCmdClearColorImage>(get_device_proc_addr(device.get(),"vkCmdClearColorImage"));
        pfn_CmdClearDepthStencilImage = reinterpret_cast<PFN_vkCmdClearDepthStencilImage>(get_device_proc_addr(device.get(),"vkCmdClearDepthStencilImage"));
        pfn_CmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(get_device_proc_addr(device.get(),"vkCmdClearAttachments"));
        pfn_CmdResolveImage = reinterpret_cast<PFN_vkCmdResolveImage>(get_device_proc_addr(device.get(),"vkCmdResolveImage"));
        pfn_CmdSetEvent = reinterpret_cast<PFN_vkCmdSetEvent>(get_device_proc_addr(device.get(),"vkCmdSetEvent"));
        pfn_CmdResetEvent = reinterpret_cast<PFN_vkCmdResetEvent>(get_device_proc_addr(device.get(),"vkCmdResetEvent"));
        pfn_CmdWaitEvents = reinterpret_cast<PFN_vkCmdWaitEvents>(get_device_proc_addr(device.get(),"vkCmdWaitEvents"));
        pfn_CmdPipelineBarrier = reinterpret_cast<PFN_vkCmdPipelineBarrier>(get_device_proc_addr(device.get(),"vkCmdPipelineBarrier"));
        pfn_CmdBeginQuery = reinterpret_cast<PFN_vkCmdBeginQuery>(get_device_proc_addr(device.get(),"vkCmdBeginQuery"));
        pfn_CmdEndQuery = reinterpret_cast<PFN_vkCmdEndQuery>(get_device_proc_addr(device.get(),"vkCmdEndQuery"));
        pfn_CmdResetQueryPool = reinterpret_cast<PFN_vkCmdResetQueryPool>(get_device_proc_addr(device.get(),"vkCmdResetQueryPool"));
        pfn_CmdWriteTimestamp = reinterpret_cast<PFN_vkCmdWriteTimestamp>(get_device_proc_addr(device.get(),"vkCmdWriteTimestamp"));
        pfn_CmdCopyQueryPoolResults = reinterpret_cast<PFN_vkCmdCopyQueryPoolResults>(get_device_proc_addr(device.get(),"vkCmdCopyQueryPoolResults"));
        pfn_CmdPushConstants = reinterpret_cast<PFN_vkCmdPushConstants>(get_device_proc_addr(device.get(),"vkCmdPushConstants"));
        pfn_CmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(get_device_proc_addr(device.get(),"vkCmdBeginRenderPass"));
        pfn_CmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(get_device_proc_addr(device.get(),"vkCmdNextSubpass"));
        pfn_CmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(get_device_proc_addr(device.get(),"vkCmdEndRenderPass"));
        pfn_CmdExecuteCommands = reinterpret_cast<PFN_vkCmdExecuteCommands>(get_device_proc_addr(device.get(),"vkCmdExecuteCommands"));
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
        pfn_BindBufferMemory2 = reinterpret_cast<PFN_vkBindBufferMemory2>(get_device_proc_addr(device.get(),"vkBindBufferMemory2"));
        pfn_BindImageMemory2 = reinterpret_cast<PFN_vkBindImageMemory2>(get_device_proc_addr(device.get(),"vkBindImageMemory2"));
        pfn_GetDeviceGroupPeerMemoryFeatures = reinterpret_cast<PFN_vkGetDeviceGroupPeerMemoryFeatures>(get_device_proc_addr(device.get(),"vkGetDeviceGroupPeerMemoryFeatures"));
        pfn_CmdSetDeviceMask = reinterpret_cast<PFN_vkCmdSetDeviceMask>(get_device_proc_addr(device.get(),"vkCmdSetDeviceMask"));
        pfn_CmdDispatchBase = reinterpret_cast<PFN_vkCmdDispatchBase>(get_device_proc_addr(device.get(),"vkCmdDispatchBase"));
        pfn_GetBufferMemoryRequirements2 = reinterpret_cast<PFN_vkGetBufferMemoryRequirements2>(get_device_proc_addr(device.get(),"vkGetBufferMemoryRequirements2"));
        pfn_GetImageMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageMemoryRequirements2>(get_device_proc_addr(device.get(),"vkGetImageMemoryRequirements2"));
        pfn_GetImageSparseMemoryRequirements2 = reinterpret_cast<PFN_vkGetImageSparseMemoryRequirements2>(get_device_proc_addr(device.get(),"vkGetImageSparseMemoryRequirements2"));
        pfn_TrimCommandPool = reinterpret_cast<PFN_vkTrimCommandPool>(get_device_proc_addr(device.get(),"vkTrimCommandPool"));
        pfn_GetDeviceQueue2 = reinterpret_cast<PFN_vkGetDeviceQueue2>(get_device_proc_addr(device.get(),"vkGetDeviceQueue2"));
        pfn_CreateSamplerYcbcrConversion = reinterpret_cast<PFN_vkCreateSamplerYcbcrConversion>(get_device_proc_addr(device.get(),"vkCreateSamplerYcbcrConversion"));
        pfn_DestroySamplerYcbcrConversion = reinterpret_cast<PFN_vkDestroySamplerYcbcrConversion>(get_device_proc_addr(device.get(),"vkDestroySamplerYcbcrConversion"));
        pfn_CreateDescriptorUpdateTemplate = reinterpret_cast<PFN_vkCreateDescriptorUpdateTemplate>(get_device_proc_addr(device.get(),"vkCreateDescriptorUpdateTemplate"));
        pfn_DestroyDescriptorUpdateTemplate = reinterpret_cast<PFN_vkDestroyDescriptorUpdateTemplate>(get_device_proc_addr(device.get(),"vkDestroyDescriptorUpdateTemplate"));
        pfn_UpdateDescriptorSetWithTemplate = reinterpret_cast<PFN_vkUpdateDescriptorSetWithTemplate>(get_device_proc_addr(device.get(),"vkUpdateDescriptorSetWithTemplate"));
        pfn_GetDescriptorSetLayoutSupport = reinterpret_cast<PFN_vkGetDescriptorSetLayoutSupport>(get_device_proc_addr(device.get(),"vkGetDescriptorSetLayoutSupport"));
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
        pfn_CmdDrawIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndirectCount>(get_device_proc_addr(device.get(),"vkCmdDrawIndirectCount"));
        pfn_CmdDrawIndexedIndirectCount = reinterpret_cast<PFN_vkCmdDrawIndexedIndirectCount>(get_device_proc_addr(device.get(),"vkCmdDrawIndexedIndirectCount"));
        pfn_CreateRenderPass2 = reinterpret_cast<PFN_vkCreateRenderPass2>(get_device_proc_addr(device.get(),"vkCreateRenderPass2"));
        pfn_CmdBeginRenderPass2 = reinterpret_cast<PFN_vkCmdBeginRenderPass2>(get_device_proc_addr(device.get(),"vkCmdBeginRenderPass2"));
        pfn_CmdNextSubpass2 = reinterpret_cast<PFN_vkCmdNextSubpass2>(get_device_proc_addr(device.get(),"vkCmdNextSubpass2"));
        pfn_CmdEndRenderPass2 = reinterpret_cast<PFN_vkCmdEndRenderPass2>(get_device_proc_addr(device.get(),"vkCmdEndRenderPass2"));
        pfn_ResetQueryPool = reinterpret_cast<PFN_vkResetQueryPool>(get_device_proc_addr(device.get(),"vkResetQueryPool"));
        pfn_GetSemaphoreCounterValue = reinterpret_cast<PFN_vkGetSemaphoreCounterValue>(get_device_proc_addr(device.get(),"vkGetSemaphoreCounterValue"));
        pfn_WaitSemaphores = reinterpret_cast<PFN_vkWaitSemaphores>(get_device_proc_addr(device.get(),"vkWaitSemaphores"));
        pfn_SignalSemaphore = reinterpret_cast<PFN_vkSignalSemaphore>(get_device_proc_addr(device.get(),"vkSignalSemaphore"));
        pfn_GetBufferOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetBufferOpaqueCaptureAddress>(get_device_proc_addr(device.get(),"vkGetBufferOpaqueCaptureAddress"));
        pfn_GetBufferDeviceAddress = reinterpret_cast<PFN_vkGetBufferDeviceAddress>(get_device_proc_addr(device.get(),"vkGetBufferDeviceAddress"));
        pfn_GetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<PFN_vkGetDeviceMemoryOpaqueCaptureAddress>(get_device_proc_addr(device.get(),"vkGetDeviceMemoryOpaqueCaptureAddress"));
#endif //defined(VK_VERSION_1_2)
#if defined(VK_KHR_swapchain)
        pfn_CreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(get_device_proc_addr(device.get(),"vkCreateSwapchainKHR"));
        pfn_DestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(get_device_proc_addr(device.get(),"vkDestroySwapchainKHR"));
        pfn_GetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(get_device_proc_addr(device.get(),"vkGetSwapchainImagesKHR"));
        pfn_AcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(get_device_proc_addr(device.get(),"vkAcquireNextImageKHR"));
        pfn_QueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(get_device_proc_addr(device.get(),"vkQueuePresentKHR"));
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
        pfn_GetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupPresentCapabilitiesKHR"));
        pfn_GetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupSurfacePresentModesKHR"));
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
        pfn_AcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(get_device_proc_addr(device.get(),"vkAcquireNextImage2KHR"));
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
#if defined(VK_KHR_display_swapchain)
        pfn_CreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(get_device_proc_addr(device.get(),"vkCreateSharedSwapchainsKHR"));
#endif //defined(VK_KHR_display_swapchain)
#if defined(VK_EXT_debug_marker)
        pfn_DebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(get_device_proc_addr(device.get(),"vkDebugMarkerSetObjectNameEXT"));
        pfn_DebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(get_device_proc_addr(device.get(),"vkDebugMarkerSetObjectTagEXT"));
        pfn_CmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerBeginEXT"));
        pfn_CmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerEndEXT"));
        pfn_CmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerInsertEXT"));
#endif //defined(VK_EXT_debug_marker)
#if defined(VK_EXT_transform_feedback)
        pfn_CmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(get_device_proc_addr(device.get(),"vkCmdBindTransformFeedbackBuffersEXT"));
        pfn_CmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(get_device_proc_addr(device.get(),"vkCmdBeginTransformFeedbackEXT"));
        pfn_CmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(get_device_proc_addr(device.get(),"vkCmdEndTransformFeedbackEXT"));
        pfn_CmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(get_device_proc_addr(device.get(),"vkCmdBeginQueryIndexedEXT"));
        pfn_CmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(get_device_proc_addr(device.get(),"vkCmdEndQueryIndexedEXT"));
        pfn_CmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(get_device_proc_addr(device.get(),"vkCmdDrawIndirectByteCountEXT"));
#endif //defined(VK_EXT_transform_feedback)
#if defined(VK_NVX_image_view_handle)
        pfn_GetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(get_device_proc_addr(device.get(),"vkGetImageViewHandleNVX"));
        pfn_GetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(get_device_proc_addr(device.get(),"vkGetImageViewAddressNVX"));
#endif //defined(VK_NVX_image_view_handle)
#if defined(VK_AMD_shader_info)
        pfn_GetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(get_device_proc_addr(device.get(),"vkGetShaderInfoAMD"));
#endif //defined(VK_AMD_shader_info)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
        pfn_GetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandleNV"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
        pfn_GetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandleKHR"));
        pfn_GetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandlePropertiesKHR"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
#if defined(VK_KHR_external_memory_fd)
        pfn_GetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(get_device_proc_addr(device.get(),"vkGetMemoryFdKHR"));
        pfn_GetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(get_device_proc_addr(device.get(),"vkGetMemoryFdPropertiesKHR"));
#endif //defined(VK_KHR_external_memory_fd)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
        pfn_GetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetSemaphoreWin32HandleKHR"));
        pfn_ImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(get_device_proc_addr(device.get(),"vkImportSemaphoreWin32HandleKHR"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
#if defined(VK_KHR_external_semaphore_fd)
        pfn_GetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(get_device_proc_addr(device.get(),"vkGetSemaphoreFdKHR"));
        pfn_ImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(get_device_proc_addr(device.get(),"vkImportSemaphoreFdKHR"));
#endif //defined(VK_KHR_external_semaphore_fd)
#if defined(VK_KHR_push_descriptor)
        pfn_CmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(get_device_proc_addr(device.get(),"vkCmdPushDescriptorSetKHR"));
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
        pfn_CmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(get_device_proc_addr(device.get(),"vkCmdPushDescriptorSetWithTemplateKHR"));
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
#if defined(VK_EXT_conditional_rendering)
        pfn_CmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(get_device_proc_addr(device.get(),"vkCmdBeginConditionalRenderingEXT"));
        pfn_CmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(get_device_proc_addr(device.get(),"vkCmdEndConditionalRenderingEXT"));
#endif //defined(VK_EXT_conditional_rendering)
#if defined(VK_NV_clip_space_w_scaling)
        pfn_CmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(get_device_proc_addr(device.get(),"vkCmdSetViewportWScalingNV"));
#endif //defined(VK_NV_clip_space_w_scaling)
#if defined(VK_EXT_display_control)
        pfn_DisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(get_device_proc_addr(device.get(),"vkDisplayPowerControlEXT"));
        pfn_RegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(get_device_proc_addr(device.get(),"vkRegisterDeviceEventEXT"));
        pfn_RegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(get_device_proc_addr(device.get(),"vkRegisterDisplayEventEXT"));
        pfn_GetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(get_device_proc_addr(device.get(),"vkGetSwapchainCounterEXT"));
#endif //defined(VK_EXT_display_control)
#if defined(VK_GOOGLE_display_timing)
        pfn_GetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(get_device_proc_addr(device.get(),"vkGetRefreshCycleDurationGOOGLE"));
        pfn_GetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(get_device_proc_addr(device.get(),"vkGetPastPresentationTimingGOOGLE"));
#endif //defined(VK_GOOGLE_display_timing)
#if defined(VK_EXT_discard_rectangles)
        pfn_CmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(get_device_proc_addr(device.get(),"vkCmdSetDiscardRectangleEXT"));
#endif //defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_hdr_metadata)
        pfn_SetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(get_device_proc_addr(device.get(),"vkSetHdrMetadataEXT"));
#endif //defined(VK_EXT_hdr_metadata)
#if defined(VK_KHR_shared_presentable_image)
        pfn_GetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(get_device_proc_addr(device.get(),"vkGetSwapchainStatusKHR"));
#endif //defined(VK_KHR_shared_presentable_image)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
        pfn_GetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetFenceWin32HandleKHR"));
        pfn_ImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(get_device_proc_addr(device.get(),"vkImportFenceWin32HandleKHR"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
#if defined(VK_KHR_external_fence_fd)
        pfn_GetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(get_device_proc_addr(device.get(),"vkGetFenceFdKHR"));
        pfn_ImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(get_device_proc_addr(device.get(),"vkImportFenceFdKHR"));
#endif //defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_performance_query)
        pfn_AcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(get_device_proc_addr(device.get(),"vkAcquireProfilingLockKHR"));
        pfn_ReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(get_device_proc_addr(device.get(),"vkReleaseProfilingLockKHR"));
#endif //defined(VK_KHR_performance_query)
#if defined(VK_EXT_debug_utils)
        pfn_SetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(get_device_proc_addr(device.get(),"vkSetDebugUtilsObjectNameEXT"));
        pfn_SetDebugUtilsObjectTagEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectTagEXT>(get_device_proc_addr(device.get(),"vkSetDebugUtilsObjectTagEXT"));
        pfn_QueueBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueBeginDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkQueueBeginDebugUtilsLabelEXT"));
        pfn_QueueEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueEndDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkQueueEndDebugUtilsLabelEXT"));
        pfn_QueueInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkQueueInsertDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkQueueInsertDebugUtilsLabelEXT"));
        pfn_CmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkCmdBeginDebugUtilsLabelEXT"));
        pfn_CmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkCmdEndDebugUtilsLabelEXT"));
        pfn_CmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(get_device_proc_addr(device.get(),"vkCmdInsertDebugUtilsLabelEXT"));
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
        pfn_GetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(get_device_proc_addr(device.get(),"vkGetAndroidHardwareBufferPropertiesANDROID"));
        pfn_GetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(get_device_proc_addr(device.get(),"vkGetMemoryAndroidHardwareBufferANDROID"));
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
#if defined(VK_EXT_sample_locations)
        pfn_CmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(get_device_proc_addr(device.get(),"vkCmdSetSampleLocationsEXT"));
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
        pfn_DestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkDestroyAccelerationStructureKHR"));
        pfn_GetAccelerationStructureMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsKHR>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureMemoryRequirementsKHR"));
        pfn_BindAccelerationStructureMemoryKHR = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryKHR>(get_device_proc_addr(device.get(),"vkBindAccelerationStructureMemoryKHR"));
        pfn_CmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureKHR"));
        pfn_CopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCopyAccelerationStructureKHR"));
        pfn_CmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureToMemoryKHR"));
        pfn_CopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device.get(),"vkCopyAccelerationStructureToMemoryKHR"));
        pfn_CmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdCopyMemoryToAccelerationStructureKHR"));
        pfn_CopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCopyMemoryToAccelerationStructureKHR"));
        pfn_CmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device.get(),"vkCmdWriteAccelerationStructuresPropertiesKHR"));
        pfn_WriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device.get(),"vkWriteAccelerationStructuresPropertiesKHR"));
        pfn_CmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(get_device_proc_addr(device.get(),"vkCmdTraceRaysKHR"));
        pfn_GetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(get_device_proc_addr(device.get(),"vkGetRayTracingShaderGroupHandlesKHR"));
        pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(get_device_proc_addr(device.get(),"vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
        pfn_CreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(get_device_proc_addr(device.get(),"vkCreateRayTracingPipelinesKHR"));
        pfn_CmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(get_device_proc_addr(device.get(),"vkCmdTraceRaysIndirectKHR"));
        pfn_GetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(get_device_proc_addr(device.get(),"vkGetDeviceAccelerationStructureCompatibilityKHR"));
        pfn_CreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCreateAccelerationStructureKHR"));
        pfn_CmdBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureKHR"));
        pfn_CmdBuildAccelerationStructureIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureIndirectKHR>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureIndirectKHR"));
        pfn_BuildAccelerationStructureKHR = reinterpret_cast<PFN_vkBuildAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkBuildAccelerationStructureKHR"));
        pfn_GetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureDeviceAddressKHR"));
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
#if defined(VK_EXT_image_drm_format_modifier)
        pfn_GetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(get_device_proc_addr(device.get(),"vkGetImageDrmFormatModifierPropertiesEXT"));
#endif //defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_validation_cache)
        pfn_CreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(get_device_proc_addr(device.get(),"vkCreateValidationCacheEXT"));
        pfn_DestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(get_device_proc_addr(device.get(),"vkDestroyValidationCacheEXT"));
        pfn_GetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(get_device_proc_addr(device.get(),"vkGetValidationCacheDataEXT"));
        pfn_MergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(get_device_proc_addr(device.get(),"vkMergeValidationCachesEXT"));
#endif //defined(VK_EXT_validation_cache)
#if defined(VK_NV_shading_rate_image)
        pfn_CmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(get_device_proc_addr(device.get(),"vkCmdBindShadingRateImageNV"));
        pfn_CmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(get_device_proc_addr(device.get(),"vkCmdSetViewportShadingRatePaletteNV"));
        pfn_CmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(get_device_proc_addr(device.get(),"vkCmdSetCoarseSampleOrderNV"));
#endif //defined(VK_NV_shading_rate_image)
#if defined(VK_NV_ray_tracing)
        pfn_CompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(get_device_proc_addr(device.get(),"vkCompileDeferredNV"));
        pfn_CreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCreateAccelerationStructureNV"));
        pfn_GetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureMemoryRequirementsNV"));
        pfn_CmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureNV"));
        pfn_CmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureNV"));
        pfn_CmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(get_device_proc_addr(device.get(),"vkCmdTraceRaysNV"));
        pfn_GetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureHandleNV"));
        pfn_CreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(get_device_proc_addr(device.get(),"vkCreateRayTracingPipelinesNV"));
#endif //defined(VK_NV_ray_tracing)
#if defined(VK_EXT_external_memory_host)
        pfn_GetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(get_device_proc_addr(device.get(),"vkGetMemoryHostPointerPropertiesEXT"));
#endif //defined(VK_EXT_external_memory_host)
#if defined(VK_AMD_buffer_marker)
        pfn_CmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(get_device_proc_addr(device.get(),"vkCmdWriteBufferMarkerAMD"));
#endif //defined(VK_AMD_buffer_marker)
#if defined(VK_EXT_calibrated_timestamps)
        pfn_GetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(get_device_proc_addr(device.get(),"vkGetCalibratedTimestampsEXT"));
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_NV_mesh_shader)
        pfn_CmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksNV"));
        pfn_CmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksIndirectNV"));
        pfn_CmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksIndirectCountNV"));
#endif //defined(VK_NV_mesh_shader)
#if defined(VK_NV_scissor_exclusive)
        pfn_CmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(get_device_proc_addr(device.get(),"vkCmdSetExclusiveScissorNV"));
#endif //defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_device_diagnostic_checkpoints)
        pfn_CmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(get_device_proc_addr(device.get(),"vkCmdSetCheckpointNV"));
        pfn_GetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(get_device_proc_addr(device.get(),"vkGetQueueCheckpointDataNV"));
#endif //defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_INTEL_performance_query)
        pfn_InitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(get_device_proc_addr(device.get(),"vkInitializePerformanceApiINTEL"));
        pfn_UninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(get_device_proc_addr(device.get(),"vkUninitializePerformanceApiINTEL"));
        pfn_CmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceMarkerINTEL"));
        pfn_CmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceStreamMarkerINTEL"));
        pfn_CmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceOverrideINTEL"));
        pfn_AcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkAcquirePerformanceConfigurationINTEL"));
        pfn_ReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkReleasePerformanceConfigurationINTEL"));
        pfn_QueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkQueueSetPerformanceConfigurationINTEL"));
        pfn_GetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(get_device_proc_addr(device.get(),"vkGetPerformanceParameterINTEL"));
#endif //defined(VK_INTEL_performance_query)
#if defined(VK_AMD_display_native_hdr)
        pfn_SetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(get_device_proc_addr(device.get(),"vkSetLocalDimmingAMD"));
#endif //defined(VK_AMD_display_native_hdr)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
        pfn_AcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(get_device_proc_addr(device.get(),"vkAcquireFullScreenExclusiveModeEXT"));
        pfn_ReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(get_device_proc_addr(device.get(),"vkReleaseFullScreenExclusiveModeEXT"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
        pfn_GetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(get_device_proc_addr(device.get(),"vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
#if defined(VK_EXT_line_rasterization)
        pfn_CmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(get_device_proc_addr(device.get(),"vkCmdSetLineStippleEXT"));
#endif //defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_extended_dynamic_state)
        pfn_CmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(get_device_proc_addr(device.get(),"vkCmdSetCullModeEXT"));
        pfn_CmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(get_device_proc_addr(device.get(),"vkCmdSetFrontFaceEXT"));
        pfn_CmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(get_device_proc_addr(device.get(),"vkCmdSetPrimitiveTopologyEXT"));
        pfn_CmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(get_device_proc_addr(device.get(),"vkCmdSetViewportWithCountEXT"));
        pfn_CmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(get_device_proc_addr(device.get(),"vkCmdSetScissorWithCountEXT"));
        pfn_CmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(get_device_proc_addr(device.get(),"vkCmdBindVertexBuffers2EXT"));
        pfn_CmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthTestEnableEXT"));
        pfn_CmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthWriteEnableEXT"));
        pfn_CmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthCompareOpEXT"));
        pfn_CmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthBoundsTestEnableEXT"));
        pfn_CmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetStencilTestEnableEXT"));
        pfn_CmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(get_device_proc_addr(device.get(),"vkCmdSetStencilOpEXT"));
#endif //defined(VK_EXT_extended_dynamic_state)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
        pfn_CreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(get_device_proc_addr(device.get(),"vkCreateDeferredOperationKHR"));
        pfn_DestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(get_device_proc_addr(device.get(),"vkDestroyDeferredOperationKHR"));
        pfn_GetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(get_device_proc_addr(device.get(),"vkGetDeferredOperationMaxConcurrencyKHR"));
        pfn_GetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(get_device_proc_addr(device.get(),"vkGetDeferredOperationResultKHR"));
        pfn_DeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(get_device_proc_addr(device.get(),"vkDeferredOperationJoinKHR"));
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
#if defined(VK_KHR_pipeline_executable_properties)
        pfn_GetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutablePropertiesKHR"));
        pfn_GetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutableStatisticsKHR"));
        pfn_GetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutableInternalRepresentationsKHR"));
#endif //defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_NV_device_generated_commands)
        pfn_CmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(get_device_proc_addr(device.get(),"vkCmdExecuteGeneratedCommandsNV"));
        pfn_CmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(get_device_proc_addr(device.get(),"vkCmdPreprocessGeneratedCommandsNV"));
        pfn_CmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(get_device_proc_addr(device.get(),"vkCmdBindPipelineShaderGroupNV"));
        pfn_GetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(get_device_proc_addr(device.get(),"vkGetGeneratedCommandsMemoryRequirementsNV"));
        pfn_CreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(get_device_proc_addr(device.get(),"vkCreateIndirectCommandsLayoutNV"));
        pfn_DestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(get_device_proc_addr(device.get(),"vkDestroyIndirectCommandsLayoutNV"));
#endif //defined(VK_NV_device_generated_commands)
#if defined(VK_EXT_private_data)
        pfn_CreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(get_device_proc_addr(device.get(),"vkCreatePrivateDataSlotEXT"));
        pfn_DestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(get_device_proc_addr(device.get(),"vkDestroyPrivateDataSlotEXT"));
        pfn_SetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(get_device_proc_addr(device.get(),"vkSetPrivateDataEXT"));
        pfn_GetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(get_device_proc_addr(device.get(),"vkGetPrivateDataEXT"));
#endif //defined(VK_EXT_private_data)
    };
};
#if defined(VK_KHR_surface)
struct VK_KHR_surface_dispatch_table {
    PFN_vkDestroySurfaceKHR pfn_DestroySurfaceKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfn_GetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_GetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_GetPhysicalDeviceSurfacePresentModesKHR;
public:
    void DestroySurfaceKHR(Instance instance,
        SurfaceKHR surface,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySurfaceKHR(instance.get(),
            surface.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        SurfaceKHR surface,
        Bool32&  pSupported) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            surface.get(),
            &pSupported));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        SurfaceCapabilitiesKHR&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormatKHR* pSurfaceFormats) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(),
            surface.get(),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormatKHR*>(pSurfaceFormats)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        uint32_t&  pPresentModeCount,
        PresentModeKHR* pPresentModes) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(),
            surface.get(),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes)));
    }
    VK_KHR_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_DestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(get_instance_proc_addr(instance.get(),"vkDestroySurfaceKHR"));
        pfn_GetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceSupportKHR"));
        pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
        pfn_GetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormatsKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceFormatsKHR"));
        pfn_GetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfacePresentModesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfacePresentModesKHR"));
    };
};
#endif //defined(VK_KHR_surface)
struct VK_KHR_swapchain_dispatch_tableFunctions {
    Device const device;
#if defined(VK_KHR_swapchain)
    PFN_vkCreateSwapchainKHR pfn_CreateSwapchainKHR;
    PFN_vkDestroySwapchainKHR pfn_DestroySwapchainKHR;
    PFN_vkGetSwapchainImagesKHR pfn_GetSwapchainImagesKHR;
    PFN_vkAcquireNextImageKHR pfn_AcquireNextImageKHR;
    PFN_vkQueuePresentKHR pfn_QueuePresentKHR;
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR pfn_GetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR pfn_GetDeviceGroupSurfacePresentModesKHR;
    PFN_vkAcquireNextImage2KHR pfn_AcquireNextImage2KHR;
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
#if defined(VK_KHR_swapchain)
    [[nodiscard]] Result CreateSwapchainKHR(const SwapchainCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SwapchainKHR&  pSwapchain) {
        return static_cast<Result>(pfn_CreateSwapchainKHR(device.get(),
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(&pSwapchain)));
    }
    void DestroySwapchainKHR(SwapchainKHR swapchain,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroySwapchainKHR(device.get(),
            swapchain.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetSwapchainImagesKHR(SwapchainKHR swapchain,
        uint32_t&  pSwapchainImageCount,
        Image* pSwapchainImages) {
        return static_cast<Result>(pfn_GetSwapchainImagesKHR(device.get(),
            swapchain.get(),
            &pSwapchainImageCount,
            reinterpret_cast<VkImage*>(pSwapchainImages)));
    }
    [[nodiscard]] Result AcquireNextImageKHR(SwapchainKHR swapchain,
        uint64_t timeout,
        Semaphore semaphore,
        Fence fence,
        uint32_t&  pImageIndex) {
        return static_cast<Result>(pfn_AcquireNextImageKHR(device.get(),
            swapchain.get(),
            timeout,
            semaphore.get(),
            fence.get(),
            &pImageIndex));
    }
    [[nodiscard]] Result QueuePresentKHR(Queue queue,
        const PresentInfoKHR&  pPresentInfo) {
        return static_cast<Result>(pfn_QueuePresentKHR(queue.get(),
            reinterpret_cast<const VkPresentInfoKHR*>(&pPresentInfo)));
    }
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    [[nodiscard]] Result GetDeviceGroupPresentCapabilitiesKHR(DeviceGroupPresentCapabilitiesKHR&  pDeviceGroupPresentCapabilities) {
        return static_cast<Result>(pfn_GetDeviceGroupPresentCapabilitiesKHR(device.get(),
            reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR*>(&pDeviceGroupPresentCapabilities)));
    }
    [[nodiscard]] Result GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface,
        DeviceGroupPresentModeFlagsKHR&  pModes) {
        return static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModesKHR(device.get(),
            surface.get(),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
    }
    [[nodiscard]] Result AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo,
        uint32_t&  pImageIndex) {
        return static_cast<Result>(pfn_AcquireNextImage2KHR(device.get(),
            reinterpret_cast<const VkAcquireNextImageInfoKHR*>(&pAcquireInfo),
            &pImageIndex));
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    VK_KHR_swapchain_dispatch_tableFunctions(InstanceFunctions const& instance_functions, Device device){
    PFN_vkGetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
#if defined(VK_KHR_swapchain)
        pfn_CreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(get_device_proc_addr(device.get(),"vkCreateSwapchainKHR"));
        pfn_DestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(get_device_proc_addr(device.get(),"vkDestroySwapchainKHR"));
        pfn_GetSwapchainImagesKHR = reinterpret_cast<PFN_vkGetSwapchainImagesKHR>(get_device_proc_addr(device.get(),"vkGetSwapchainImagesKHR"));
        pfn_AcquireNextImageKHR = reinterpret_cast<PFN_vkAcquireNextImageKHR>(get_device_proc_addr(device.get(),"vkAcquireNextImageKHR"));
        pfn_QueuePresentKHR = reinterpret_cast<PFN_vkQueuePresentKHR>(get_device_proc_addr(device.get(),"vkQueuePresentKHR"));
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
        pfn_GetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupPresentCapabilitiesKHR"));
        pfn_GetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupSurfacePresentModesKHR"));
        pfn_AcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(get_device_proc_addr(device.get(),"vkAcquireNextImage2KHR"));
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1))
    };
};
#if defined(VK_KHR_display)
struct VK_KHR_display_dispatch_table {
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR pfn_GetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR pfn_GetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetDisplayModePropertiesKHR pfn_GetDisplayModePropertiesKHR;
    PFN_vkCreateDisplayModeKHR pfn_CreateDisplayModeKHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR pfn_GetDisplayPlaneCapabilitiesKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR pfn_CreateDisplayPlaneSurfaceKHR;
public:
    [[nodiscard]] Result GetPhysicalDeviceDisplayPropertiesKHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPhysicalDeviceDisplayPlanePropertiesKHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPlanePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlanePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneSupportedDisplaysKHR(PhysicalDevice physicalDevice,
        uint32_t planeIndex,
        uint32_t&  pDisplayCount,
        DisplayKHR* pDisplays) {
        return static_cast<Result>(pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice.get(),
            planeIndex,
            &pDisplayCount,
            reinterpret_cast<VkDisplayKHR*>(pDisplays)));
    }
    [[nodiscard]] Result GetDisplayModePropertiesKHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetDisplayModePropertiesKHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result CreateDisplayModeKHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        const DisplayModeCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DisplayModeKHR&  pMode) {
        return static_cast<Result>(pfn_CreateDisplayModeKHR(physicalDevice.get(),
            display.get(),
            reinterpret_cast<const VkDisplayModeCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDisplayModeKHR*>(&pMode)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilitiesKHR(PhysicalDevice physicalDevice,
        DisplayModeKHR mode,
        uint32_t planeIndex,
        DisplayPlaneCapabilitiesKHR&  pCapabilities) {
        return static_cast<Result>(pfn_GetDisplayPlaneCapabilitiesKHR(physicalDevice.get(),
            mode.get(),
            planeIndex,
            reinterpret_cast<VkDisplayPlaneCapabilitiesKHR*>(&pCapabilities)));
    }
    [[nodiscard]] Result CreateDisplayPlaneSurfaceKHR(Instance instance,
        const DisplaySurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateDisplayPlaneSurfaceKHR(instance.get(),
            reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_KHR_display_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_GetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPropertiesKHR"));
        pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
        pfn_GetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<PFN_vkGetDisplayPlaneSupportedDisplaysKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneSupportedDisplaysKHR"));
        pfn_GetDisplayModePropertiesKHR = reinterpret_cast<PFN_vkGetDisplayModePropertiesKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayModePropertiesKHR"));
        pfn_CreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(get_instance_proc_addr(instance.get(),"vkCreateDisplayModeKHR"));
        pfn_GetDisplayPlaneCapabilitiesKHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilitiesKHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneCapabilitiesKHR"));
        pfn_CreateDisplayPlaneSurfaceKHR = reinterpret_cast<PFN_vkCreateDisplayPlaneSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateDisplayPlaneSurfaceKHR"));
    };
};
#endif //defined(VK_KHR_display)
#if defined(VK_KHR_display_swapchain)
struct VK_KHR_display_swapchain_dispatch_table {
    PFN_vkCreateSharedSwapchainsKHR pfn_CreateSharedSwapchainsKHR;
public:
    [[nodiscard]] Result CreateSharedSwapchainsKHR(Device device,
        uint32_t swapchainCount,
        const SwapchainCreateInfoKHR* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        SwapchainKHR* pSwapchains) {
        return static_cast<Result>(pfn_CreateSharedSwapchainsKHR(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(pSwapchains)));
    }
    VK_KHR_display_swapchain_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(get_device_proc_addr(device.get(),"vkCreateSharedSwapchainsKHR"));
    };
};
#endif //defined(VK_KHR_display_swapchain)
#if defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
struct VK_KHR_xlib_surface_dispatch_table {
    PFN_vkCreateXlibSurfaceKHR pfn_CreateXlibSurfaceKHR;
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR pfn_GetPhysicalDeviceXlibPresentationSupportKHR;
public:
    [[nodiscard]] Result CreateXlibSurfaceKHR(Instance instance,
        const XlibSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateXlibSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXlibSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXlibPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        Display&  dpy,
        VisualID visualID) {
        return pfn_GetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<Display*>(&dpy),
            static_cast<VisualID>(visualID));
    }
    VK_KHR_xlib_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateXlibSurfaceKHR"));
        pfn_GetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceXlibPresentationSupportKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
#if defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
struct VK_KHR_xcb_surface_dispatch_table {
    PFN_vkCreateXcbSurfaceKHR pfn_CreateXcbSurfaceKHR;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR pfn_GetPhysicalDeviceXcbPresentationSupportKHR;
public:
    [[nodiscard]] Result CreateXcbSurfaceKHR(Instance instance,
        const XcbSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateXcbSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXcbSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXcbPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        xcb_connection_t&  connection,
        xcb_visualid_t visual_id) {
        return pfn_GetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<xcb_connection_t*>(&connection),
            static_cast<xcb_visualid_t>(visual_id));
    }
    VK_KHR_xcb_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateXcbSurfaceKHR"));
        pfn_GetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceXcbPresentationSupportKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
struct VK_KHR_wayland_surface_dispatch_table {
    PFN_vkCreateWaylandSurfaceKHR pfn_CreateWaylandSurfaceKHR;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR pfn_GetPhysicalDeviceWaylandPresentationSupportKHR;
public:
    [[nodiscard]] Result CreateWaylandSurfaceKHR(Instance instance,
        const WaylandSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateWaylandSurfaceKHR(instance.get(),
            reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceWaylandPresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        wl_display&  display) {
        return pfn_GetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<wl_display*>(&display));
    }
    VK_KHR_wayland_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateWaylandSurfaceKHR"));
        pfn_GetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
struct VK_KHR_android_surface_dispatch_table {
    PFN_vkCreateAndroidSurfaceKHR pfn_CreateAndroidSurfaceKHR;
public:
    [[nodiscard]] Result CreateAndroidSurfaceKHR(Instance instance,
        const AndroidSurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateAndroidSurfaceKHR(instance.get(),
            reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_KHR_android_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateAndroidSurfaceKHR = reinterpret_cast<PFN_vkCreateAndroidSurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateAndroidSurfaceKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
struct VK_KHR_win32_surface_dispatch_table {
    PFN_vkCreateWin32SurfaceKHR pfn_CreateWin32SurfaceKHR;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR pfn_GetPhysicalDeviceWin32PresentationSupportKHR;
public:
    [[nodiscard]] Result CreateWin32SurfaceKHR(Instance instance,
        const Win32SurfaceCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateWin32SurfaceKHR(instance.get(),
            reinterpret_cast<const VkWin32SurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceWin32PresentationSupportKHR(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex) {
        return pfn_GetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex);
    }
    VK_KHR_win32_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(get_instance_proc_addr(instance.get(),"vkCreateWin32SurfaceKHR"));
        pfn_GetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceWin32PresentationSupportKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
#if defined(VK_EXT_debug_report)
struct VK_EXT_debug_report_dispatch_table {
    PFN_vkCreateDebugReportCallbackEXT pfn_CreateDebugReportCallbackEXT;
    PFN_vkDestroyDebugReportCallbackEXT pfn_DestroyDebugReportCallbackEXT;
    PFN_vkDebugReportMessageEXT pfn_DebugReportMessageEXT;
public:
    [[nodiscard]] Result CreateDebugReportCallbackEXT(Instance instance,
        const DebugReportCallbackCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DebugReportCallbackEXT&  pCallback) {
        return static_cast<Result>(pfn_CreateDebugReportCallbackEXT(instance.get(),
            reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugReportCallbackEXT*>(&pCallback)));
    }
    void DestroyDebugReportCallbackEXT(Instance instance,
        DebugReportCallbackEXT callback,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDebugReportCallbackEXT(instance.get(),
            callback.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void DebugReportMessageEXT(Instance instance,
        DebugReportFlagsEXT flags,
        DebugReportObjectTypeEXT objectType,
        uint64_t object,
        size_t location,
        int32_t messageCode,
        const char* pLayerPrefix,
        const char* pMessage) {
        return pfn_DebugReportMessageEXT(instance.get(),
            static_cast<VkDebugReportFlagsEXT>(flags),
            static_cast<VkDebugReportObjectTypeEXT>(objectType),
            object,
            location,
            messageCode,
            pLayerPrefix,
            pMessage);
    }
    VK_EXT_debug_report_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(get_instance_proc_addr(instance.get(),"vkCreateDebugReportCallbackEXT"));
        pfn_DestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(get_instance_proc_addr(instance.get(),"vkDestroyDebugReportCallbackEXT"));
        pfn_DebugReportMessageEXT = reinterpret_cast<PFN_vkDebugReportMessageEXT>(get_instance_proc_addr(instance.get(),"vkDebugReportMessageEXT"));
    };
};
#endif //defined(VK_EXT_debug_report)
#if defined(VK_EXT_debug_marker)
struct VK_EXT_debug_marker_dispatch_table {
    PFN_vkDebugMarkerSetObjectNameEXT pfn_DebugMarkerSetObjectNameEXT;
    PFN_vkDebugMarkerSetObjectTagEXT pfn_DebugMarkerSetObjectTagEXT;
    PFN_vkCmdDebugMarkerBeginEXT pfn_CmdDebugMarkerBeginEXT;
    PFN_vkCmdDebugMarkerEndEXT pfn_CmdDebugMarkerEndEXT;
    PFN_vkCmdDebugMarkerInsertEXT pfn_CmdDebugMarkerInsertEXT;
public:
    [[nodiscard]] Result DebugMarkerSetObjectNameEXT(Device device,
        const DebugMarkerObjectNameInfoEXT&  pNameInfo) {
        return static_cast<Result>(pfn_DebugMarkerSetObjectNameEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectNameInfoEXT*>(&pNameInfo)));
    }
    [[nodiscard]] Result DebugMarkerSetObjectTagEXT(Device device,
        const DebugMarkerObjectTagInfoEXT&  pTagInfo) {
        return static_cast<Result>(pfn_DebugMarkerSetObjectTagEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectTagInfoEXT*>(&pTagInfo)));
    }
    void CmdDebugMarkerBeginEXT(CommandBuffer commandBuffer,
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return pfn_CmdDebugMarkerBeginEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    void CmdDebugMarkerEndEXT(CommandBuffer commandBuffer) {
        return pfn_CmdDebugMarkerEndEXT(commandBuffer.get());
    }
    void CmdDebugMarkerInsertEXT(CommandBuffer commandBuffer,
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return pfn_CmdDebugMarkerInsertEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    VK_EXT_debug_marker_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_DebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(get_device_proc_addr(device.get(),"vkDebugMarkerSetObjectNameEXT"));
        pfn_DebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(get_device_proc_addr(device.get(),"vkDebugMarkerSetObjectTagEXT"));
        pfn_CmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerBeginEXT"));
        pfn_CmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerEndEXT"));
        pfn_CmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(get_device_proc_addr(device.get(),"vkCmdDebugMarkerInsertEXT"));
    };
};
#endif //defined(VK_EXT_debug_marker)
#if defined(VK_EXT_transform_feedback)
struct VK_EXT_transform_feedback_dispatch_table {
    PFN_vkCmdBindTransformFeedbackBuffersEXT pfn_CmdBindTransformFeedbackBuffersEXT;
    PFN_vkCmdBeginTransformFeedbackEXT pfn_CmdBeginTransformFeedbackEXT;
    PFN_vkCmdEndTransformFeedbackEXT pfn_CmdEndTransformFeedbackEXT;
    PFN_vkCmdBeginQueryIndexedEXT pfn_CmdBeginQueryIndexedEXT;
    PFN_vkCmdEndQueryIndexedEXT pfn_CmdEndQueryIndexedEXT;
    PFN_vkCmdDrawIndirectByteCountEXT pfn_CmdDrawIndirectByteCountEXT;
public:
    void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer,
        uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes) {
        return pfn_CmdBindTransformFeedbackBuffersEXT(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes);
    }
    void CmdBeginTransformFeedbackEXT(CommandBuffer commandBuffer,
        uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return pfn_CmdBeginTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer,
        uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return pfn_CmdEndTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdBeginQueryIndexedEXT(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query,
        QueryControlFlags flags,
        uint32_t index) {
        return pfn_CmdBeginQueryIndexedEXT(commandBuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags),
            index);
    }
    void CmdEndQueryIndexedEXT(CommandBuffer commandBuffer,
        QueryPool queryPool,
        uint32_t query,
        uint32_t index) {
        return pfn_CmdEndQueryIndexedEXT(commandBuffer.get(),
            queryPool.get(),
            query,
            index);
    }
    void CmdDrawIndirectByteCountEXT(CommandBuffer commandBuffer,
        uint32_t instanceCount,
        uint32_t firstInstance,
        Buffer counterBuffer,
        DeviceSize counterBufferOffset,
        uint32_t counterOffset,
        uint32_t vertexStride) {
        return pfn_CmdDrawIndirectByteCountEXT(commandBuffer.get(),
            instanceCount,
            firstInstance,
            counterBuffer.get(),
            counterBufferOffset,
            counterOffset,
            vertexStride);
    }
    VK_EXT_transform_feedback_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdBindTransformFeedbackBuffersEXT = reinterpret_cast<PFN_vkCmdBindTransformFeedbackBuffersEXT>(get_device_proc_addr(device.get(),"vkCmdBindTransformFeedbackBuffersEXT"));
        pfn_CmdBeginTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdBeginTransformFeedbackEXT>(get_device_proc_addr(device.get(),"vkCmdBeginTransformFeedbackEXT"));
        pfn_CmdEndTransformFeedbackEXT = reinterpret_cast<PFN_vkCmdEndTransformFeedbackEXT>(get_device_proc_addr(device.get(),"vkCmdEndTransformFeedbackEXT"));
        pfn_CmdBeginQueryIndexedEXT = reinterpret_cast<PFN_vkCmdBeginQueryIndexedEXT>(get_device_proc_addr(device.get(),"vkCmdBeginQueryIndexedEXT"));
        pfn_CmdEndQueryIndexedEXT = reinterpret_cast<PFN_vkCmdEndQueryIndexedEXT>(get_device_proc_addr(device.get(),"vkCmdEndQueryIndexedEXT"));
        pfn_CmdDrawIndirectByteCountEXT = reinterpret_cast<PFN_vkCmdDrawIndirectByteCountEXT>(get_device_proc_addr(device.get(),"vkCmdDrawIndirectByteCountEXT"));
    };
};
#endif //defined(VK_EXT_transform_feedback)
#if defined(VK_NVX_image_view_handle)
struct VK_NVX_image_view_handle_dispatch_table {
    PFN_vkGetImageViewHandleNVX pfn_GetImageViewHandleNVX;
    PFN_vkGetImageViewAddressNVX pfn_GetImageViewAddressNVX;
public:
    [[nodiscard]] uint32_t GetImageViewHandleNVX(Device device,
        const ImageViewHandleInfoNVX&  pInfo) {
        return pfn_GetImageViewHandleNVX(device.get(),
            reinterpret_cast<const VkImageViewHandleInfoNVX*>(&pInfo));
    }
    [[nodiscard]] Result GetImageViewAddressNVX(Device device,
        ImageView imageView,
        ImageViewAddressPropertiesNVX&  pProperties) {
        return static_cast<Result>(pfn_GetImageViewAddressNVX(device.get(),
            imageView.get(),
            reinterpret_cast<VkImageViewAddressPropertiesNVX*>(&pProperties)));
    }
    VK_NVX_image_view_handle_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetImageViewHandleNVX = reinterpret_cast<PFN_vkGetImageViewHandleNVX>(get_device_proc_addr(device.get(),"vkGetImageViewHandleNVX"));
        pfn_GetImageViewAddressNVX = reinterpret_cast<PFN_vkGetImageViewAddressNVX>(get_device_proc_addr(device.get(),"vkGetImageViewAddressNVX"));
    };
};
#endif //defined(VK_NVX_image_view_handle)
#if defined(VK_AMD_shader_info)
struct VK_AMD_shader_info_dispatch_table {
    PFN_vkGetShaderInfoAMD pfn_GetShaderInfoAMD;
public:
    [[nodiscard]] Result GetShaderInfoAMD(Device device,
        Pipeline pipeline,
        ShaderStageFlagBits shaderStage,
        ShaderInfoTypeAMD infoType,
        size_t&  pInfoSize,
        void* pInfo) {
        return static_cast<Result>(pfn_GetShaderInfoAMD(device.get(),
            pipeline.get(),
            static_cast<VkShaderStageFlagBits>(shaderStage),
            static_cast<VkShaderInfoTypeAMD>(infoType),
            &pInfoSize,
            reinterpret_cast<void*>(pInfo)));
    }
    VK_AMD_shader_info_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetShaderInfoAMD = reinterpret_cast<PFN_vkGetShaderInfoAMD>(get_device_proc_addr(device.get(),"vkGetShaderInfoAMD"));
    };
};
#endif //defined(VK_AMD_shader_info)
#if defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
struct VK_GGP_stream_descriptor_surface_dispatch_table {
    PFN_vkCreateStreamDescriptorSurfaceGGP pfn_CreateStreamDescriptorSurfaceGGP;
public:
    [[nodiscard]] Result CreateStreamDescriptorSurfaceGGP(Instance instance,
        const StreamDescriptorSurfaceCreateInfoGGP&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateStreamDescriptorSurfaceGGP(instance.get(),
            reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_GGP_stream_descriptor_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateStreamDescriptorSurfaceGGP = reinterpret_cast<PFN_vkCreateStreamDescriptorSurfaceGGP>(get_instance_proc_addr(instance.get(),"vkCreateStreamDescriptorSurfaceGGP"));
    };
};
#endif //defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
#if defined(VK_NV_external_memory_capabilities)
struct VK_NV_external_memory_capabilities_dispatch_table {
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV;
public:
    [[nodiscard]] Result GetPhysicalDeviceExternalImageFormatPropertiesNV(PhysicalDevice physicalDevice,
        Format format,
        ImageType type,
        ImageTiling tiling,
        ImageUsageFlags usage,
        ImageCreateFlags flags,
        ExternalMemoryHandleTypeFlagsNV externalHandleType,
        ExternalImageFormatPropertiesNV&  pExternalImageFormatProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(externalHandleType),
            reinterpret_cast<VkExternalImageFormatPropertiesNV*>(&pExternalImageFormatProperties)));
    }
    VK_NV_external_memory_capabilities_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
    };
};
#endif //defined(VK_NV_external_memory_capabilities)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
struct VK_NV_external_memory_win32_dispatch_table {
    PFN_vkGetMemoryWin32HandleNV pfn_GetMemoryWin32HandleNV;
public:
    [[nodiscard]] Result GetMemoryWin32HandleNV(Device device,
        DeviceMemory memory,
        ExternalMemoryHandleTypeFlagsNV handleType,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetMemoryWin32HandleNV(device.get(),
            memory.get(),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(handleType),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    VK_NV_external_memory_win32_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetMemoryWin32HandleNV = reinterpret_cast<PFN_vkGetMemoryWin32HandleNV>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandleNV"));
    };
};
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
struct VK_KHR_device_group_dispatch_tableFunctions {
    Device const device;
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR pfn_GetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR pfn_GetDeviceGroupSurfacePresentModesKHR;
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    PFN_vkAcquireNextImage2KHR pfn_AcquireNextImage2KHR;
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    [[nodiscard]] Result GetDeviceGroupPresentCapabilitiesKHR(DeviceGroupPresentCapabilitiesKHR&  pDeviceGroupPresentCapabilities) {
        return static_cast<Result>(pfn_GetDeviceGroupPresentCapabilitiesKHR(device.get(),
            reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR*>(&pDeviceGroupPresentCapabilities)));
    }
    [[nodiscard]] Result GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface,
        DeviceGroupPresentModeFlagsKHR&  pModes) {
        return static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModesKHR(device.get(),
            surface.get(),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
    }
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    [[nodiscard]] Result AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo,
        uint32_t&  pImageIndex) {
        return static_cast<Result>(pfn_AcquireNextImage2KHR(device.get(),
            reinterpret_cast<const VkAcquireNextImageInfoKHR*>(&pAcquireInfo),
            &pImageIndex));
    }
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    VK_KHR_device_group_dispatch_tableFunctions(InstanceFunctions const& instance_functions, Device device){
    PFN_vkGetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
#if (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
        pfn_GetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<PFN_vkGetDeviceGroupPresentCapabilitiesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupPresentCapabilitiesKHR"));
        pfn_GetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModesKHR>(get_device_proc_addr(device.get(),"vkGetDeviceGroupSurfacePresentModesKHR"));
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
        pfn_AcquireNextImage2KHR = reinterpret_cast<PFN_vkAcquireNextImage2KHR>(get_device_proc_addr(device.get(),"vkAcquireNextImage2KHR"));
#endif //(defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    };
};
#if defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
struct VK_NN_vi_surface_dispatch_table {
    PFN_vkCreateViSurfaceNN pfn_CreateViSurfaceNN;
public:
    [[nodiscard]] Result CreateViSurfaceNN(Instance instance,
        const ViSurfaceCreateInfoNN&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateViSurfaceNN(instance.get(),
            reinterpret_cast<const VkViSurfaceCreateInfoNN*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_NN_vi_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateViSurfaceNN = reinterpret_cast<PFN_vkCreateViSurfaceNN>(get_instance_proc_addr(instance.get(),"vkCreateViSurfaceNN"));
    };
};
#endif //defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
struct VK_KHR_external_memory_win32_dispatch_table {
    PFN_vkGetMemoryWin32HandleKHR pfn_GetMemoryWin32HandleKHR;
    PFN_vkGetMemoryWin32HandlePropertiesKHR pfn_GetMemoryWin32HandlePropertiesKHR;
public:
    [[nodiscard]] Result GetMemoryWin32HandleKHR(Device device,
        const MemoryGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetMemoryWin32HandleKHR(device.get(),
            reinterpret_cast<const VkMemoryGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result GetMemoryWin32HandlePropertiesKHR(Device device,
        ExternalMemoryHandleTypeFlagBits handleType,
        HANDLE handle,
        MemoryWin32HandlePropertiesKHR&  pMemoryWin32HandleProperties) {
        return static_cast<Result>(pfn_GetMemoryWin32HandlePropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            static_cast<HANDLE>(handle),
            reinterpret_cast<VkMemoryWin32HandlePropertiesKHR*>(&pMemoryWin32HandleProperties)));
    }
    VK_KHR_external_memory_win32_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetMemoryWin32HandleKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandleKHR"));
        pfn_GetMemoryWin32HandlePropertiesKHR = reinterpret_cast<PFN_vkGetMemoryWin32HandlePropertiesKHR>(get_device_proc_addr(device.get(),"vkGetMemoryWin32HandlePropertiesKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
#if defined(VK_KHR_external_memory_fd)
struct VK_KHR_external_memory_fd_dispatch_table {
    PFN_vkGetMemoryFdKHR pfn_GetMemoryFdKHR;
    PFN_vkGetMemoryFdPropertiesKHR pfn_GetMemoryFdPropertiesKHR;
public:
    [[nodiscard]] Result GetMemoryFdKHR(Device device,
        const MemoryGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetMemoryFdKHR(device.get(),
            reinterpret_cast<const VkMemoryGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result GetMemoryFdPropertiesKHR(Device device,
        ExternalMemoryHandleTypeFlagBits handleType,
        int fd,
        MemoryFdPropertiesKHR&  pMemoryFdProperties) {
        return static_cast<Result>(pfn_GetMemoryFdPropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            fd,
            reinterpret_cast<VkMemoryFdPropertiesKHR*>(&pMemoryFdProperties)));
    }
    VK_KHR_external_memory_fd_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetMemoryFdKHR = reinterpret_cast<PFN_vkGetMemoryFdKHR>(get_device_proc_addr(device.get(),"vkGetMemoryFdKHR"));
        pfn_GetMemoryFdPropertiesKHR = reinterpret_cast<PFN_vkGetMemoryFdPropertiesKHR>(get_device_proc_addr(device.get(),"vkGetMemoryFdPropertiesKHR"));
    };
};
#endif //defined(VK_KHR_external_memory_fd)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
struct VK_KHR_external_semaphore_win32_dispatch_table {
    PFN_vkGetSemaphoreWin32HandleKHR pfn_GetSemaphoreWin32HandleKHR;
    PFN_vkImportSemaphoreWin32HandleKHR pfn_ImportSemaphoreWin32HandleKHR;
public:
    [[nodiscard]] Result GetSemaphoreWin32HandleKHR(Device device,
        const SemaphoreGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result ImportSemaphoreWin32HandleKHR(Device device,
        const ImportSemaphoreWin32HandleInfoKHR&  pImportSemaphoreWin32HandleInfo) {
        return static_cast<Result>(pfn_ImportSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportSemaphoreWin32HandleInfoKHR*>(&pImportSemaphoreWin32HandleInfo)));
    }
    VK_KHR_external_semaphore_win32_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkGetSemaphoreWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetSemaphoreWin32HandleKHR"));
        pfn_ImportSemaphoreWin32HandleKHR = reinterpret_cast<PFN_vkImportSemaphoreWin32HandleKHR>(get_device_proc_addr(device.get(),"vkImportSemaphoreWin32HandleKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
#if defined(VK_KHR_external_semaphore_fd)
struct VK_KHR_external_semaphore_fd_dispatch_table {
    PFN_vkGetSemaphoreFdKHR pfn_GetSemaphoreFdKHR;
    PFN_vkImportSemaphoreFdKHR pfn_ImportSemaphoreFdKHR;
public:
    [[nodiscard]] Result GetSemaphoreFdKHR(Device device,
        const SemaphoreGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetSemaphoreFdKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result ImportSemaphoreFdKHR(Device device,
        const ImportSemaphoreFdInfoKHR&  pImportSemaphoreFdInfo) {
        return static_cast<Result>(pfn_ImportSemaphoreFdKHR(device.get(),
            reinterpret_cast<const VkImportSemaphoreFdInfoKHR*>(&pImportSemaphoreFdInfo)));
    }
    VK_KHR_external_semaphore_fd_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetSemaphoreFdKHR = reinterpret_cast<PFN_vkGetSemaphoreFdKHR>(get_device_proc_addr(device.get(),"vkGetSemaphoreFdKHR"));
        pfn_ImportSemaphoreFdKHR = reinterpret_cast<PFN_vkImportSemaphoreFdKHR>(get_device_proc_addr(device.get(),"vkImportSemaphoreFdKHR"));
    };
};
#endif //defined(VK_KHR_external_semaphore_fd)
struct VK_KHR_push_descriptor_dispatch_tableFunctions {
    Device const device;
#if defined(VK_KHR_push_descriptor)
    PFN_vkCmdPushDescriptorSetKHR pfn_CmdPushDescriptorSetKHR;
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    PFN_vkCmdPushDescriptorSetWithTemplateKHR pfn_CmdPushDescriptorSetWithTemplateKHR;
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
#if defined(VK_KHR_push_descriptor)
    void CmdPushDescriptorSetKHR(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        PipelineLayout layout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        const WriteDescriptorSet* pDescriptorWrites) {
        return pfn_CmdPushDescriptorSetKHR(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            layout.get(),
            set,
            descriptorWriteCount,
            reinterpret_cast<const VkWriteDescriptorSet*>(pDescriptorWrites));
    }
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    void CmdPushDescriptorSetWithTemplateKHR(CommandBuffer commandBuffer,
        DescriptorUpdateTemplate descriptorUpdateTemplate,
        PipelineLayout layout,
        uint32_t set,
        const void* pData) {
        return pfn_CmdPushDescriptorSetWithTemplateKHR(commandBuffer.get(),
            descriptorUpdateTemplate.get(),
            layout.get(),
            set,
            reinterpret_cast<const void*>(pData));
    }
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    VK_KHR_push_descriptor_dispatch_tableFunctions(InstanceFunctions const& instance_functions, Device device){
    PFN_vkGetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
#if defined(VK_KHR_push_descriptor)
        pfn_CmdPushDescriptorSetKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetKHR>(get_device_proc_addr(device.get(),"vkCmdPushDescriptorSetKHR"));
#endif //defined(VK_KHR_push_descriptor)
#if (defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
        pfn_CmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(get_device_proc_addr(device.get(),"vkCmdPushDescriptorSetWithTemplateKHR"));
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template))
    };
};
#if defined(VK_EXT_conditional_rendering)
struct VK_EXT_conditional_rendering_dispatch_table {
    PFN_vkCmdBeginConditionalRenderingEXT pfn_CmdBeginConditionalRenderingEXT;
    PFN_vkCmdEndConditionalRenderingEXT pfn_CmdEndConditionalRenderingEXT;
public:
    void CmdBeginConditionalRenderingEXT(CommandBuffer commandBuffer,
        const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) {
        return pfn_CmdBeginConditionalRenderingEXT(commandBuffer.get(),
            reinterpret_cast<const VkConditionalRenderingBeginInfoEXT*>(&pConditionalRenderingBegin));
    }
    void CmdEndConditionalRenderingEXT(CommandBuffer commandBuffer) {
        return pfn_CmdEndConditionalRenderingEXT(commandBuffer.get());
    }
    VK_EXT_conditional_rendering_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdBeginConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdBeginConditionalRenderingEXT>(get_device_proc_addr(device.get(),"vkCmdBeginConditionalRenderingEXT"));
        pfn_CmdEndConditionalRenderingEXT = reinterpret_cast<PFN_vkCmdEndConditionalRenderingEXT>(get_device_proc_addr(device.get(),"vkCmdEndConditionalRenderingEXT"));
    };
};
#endif //defined(VK_EXT_conditional_rendering)
#if (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
struct VK_KHR_descriptor_update_template_dispatch_table {
    PFN_vkCmdPushDescriptorSetWithTemplateKHR pfn_CmdPushDescriptorSetWithTemplateKHR;
public:
    void CmdPushDescriptorSetWithTemplateKHR(CommandBuffer commandBuffer,
        DescriptorUpdateTemplate descriptorUpdateTemplate,
        PipelineLayout layout,
        uint32_t set,
        const void* pData) {
        return pfn_CmdPushDescriptorSetWithTemplateKHR(commandBuffer.get(),
            descriptorUpdateTemplate.get(),
            layout.get(),
            set,
            reinterpret_cast<const void*>(pData));
    }
    VK_KHR_descriptor_update_template_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<PFN_vkCmdPushDescriptorSetWithTemplateKHR>(get_device_proc_addr(device.get(),"vkCmdPushDescriptorSetWithTemplateKHR"));
    };
};
#endif //(defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
#if defined(VK_NV_clip_space_w_scaling)
struct VK_NV_clip_space_w_scaling_dispatch_table {
    PFN_vkCmdSetViewportWScalingNV pfn_CmdSetViewportWScalingNV;
public:
    void CmdSetViewportWScalingNV(CommandBuffer commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        const ViewportWScalingNV* pViewportWScalings) {
        return pfn_CmdSetViewportWScalingNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewportWScalingNV*>(pViewportWScalings));
    }
    VK_NV_clip_space_w_scaling_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetViewportWScalingNV = reinterpret_cast<PFN_vkCmdSetViewportWScalingNV>(get_device_proc_addr(device.get(),"vkCmdSetViewportWScalingNV"));
    };
};
#endif //defined(VK_NV_clip_space_w_scaling)
#if defined(VK_EXT_direct_mode_display)
struct VK_EXT_direct_mode_display_dispatch_table {
    PFN_vkReleaseDisplayEXT pfn_ReleaseDisplayEXT;
public:
    [[nodiscard]] Result ReleaseDisplayEXT(PhysicalDevice physicalDevice,
        DisplayKHR display) {
        return static_cast<Result>(pfn_ReleaseDisplayEXT(physicalDevice.get(),
            display.get()));
    }
    VK_EXT_direct_mode_display_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_ReleaseDisplayEXT = reinterpret_cast<PFN_vkReleaseDisplayEXT>(get_instance_proc_addr(instance.get(),"vkReleaseDisplayEXT"));
    };
};
#endif //defined(VK_EXT_direct_mode_display)
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
struct VK_EXT_acquire_xlib_display_dispatch_table {
    PFN_vkAcquireXlibDisplayEXT pfn_AcquireXlibDisplayEXT;
    PFN_vkGetRandROutputDisplayEXT pfn_GetRandROutputDisplayEXT;
public:
    [[nodiscard]] Result AcquireXlibDisplayEXT(PhysicalDevice physicalDevice,
        Display&  dpy,
        DisplayKHR display) {
        return static_cast<Result>(pfn_AcquireXlibDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            display.get()));
    }
    [[nodiscard]] Result GetRandROutputDisplayEXT(PhysicalDevice physicalDevice,
        Display&  dpy,
        RROutput rrOutput,
        DisplayKHR&  pDisplay) {
        return static_cast<Result>(pfn_GetRandROutputDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            static_cast<RROutput>(rrOutput),
            reinterpret_cast<VkDisplayKHR*>(&pDisplay)));
    }
    VK_EXT_acquire_xlib_display_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_AcquireXlibDisplayEXT = reinterpret_cast<PFN_vkAcquireXlibDisplayEXT>(get_instance_proc_addr(instance.get(),"vkAcquireXlibDisplayEXT"));
        pfn_GetRandROutputDisplayEXT = reinterpret_cast<PFN_vkGetRandROutputDisplayEXT>(get_instance_proc_addr(instance.get(),"vkGetRandROutputDisplayEXT"));
    };
};
#endif //defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
#if defined(VK_EXT_display_surface_counter)
struct VK_EXT_display_surface_counter_dispatch_table {
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT pfn_GetPhysicalDeviceSurfaceCapabilities2EXT;
public:
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilities2EXT(PhysicalDevice physicalDevice,
        SurfaceKHR surface,
        SurfaceCapabilities2EXT&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilities2EXT*>(&pSurfaceCapabilities)));
    }
    VK_EXT_display_surface_counter_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_GetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
    };
};
#endif //defined(VK_EXT_display_surface_counter)
#if defined(VK_EXT_display_control)
struct VK_EXT_display_control_dispatch_table {
    PFN_vkDisplayPowerControlEXT pfn_DisplayPowerControlEXT;
    PFN_vkRegisterDeviceEventEXT pfn_RegisterDeviceEventEXT;
    PFN_vkRegisterDisplayEventEXT pfn_RegisterDisplayEventEXT;
    PFN_vkGetSwapchainCounterEXT pfn_GetSwapchainCounterEXT;
public:
    [[nodiscard]] Result DisplayPowerControlEXT(Device device,
        DisplayKHR display,
        const DisplayPowerInfoEXT&  pDisplayPowerInfo) {
        return static_cast<Result>(pfn_DisplayPowerControlEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayPowerInfoEXT*>(&pDisplayPowerInfo)));
    }
    [[nodiscard]] Result RegisterDeviceEventEXT(Device device,
        const DeviceEventInfoEXT&  pDeviceEventInfo,
        const AllocationCallbacks* pAllocator,
        Fence&  pFence) {
        return static_cast<Result>(pfn_RegisterDeviceEventEXT(device.get(),
            reinterpret_cast<const VkDeviceEventInfoEXT*>(&pDeviceEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
    }
    [[nodiscard]] Result RegisterDisplayEventEXT(Device device,
        DisplayKHR display,
        const DisplayEventInfoEXT&  pDisplayEventInfo,
        const AllocationCallbacks* pAllocator,
        Fence&  pFence) {
        return static_cast<Result>(pfn_RegisterDisplayEventEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayEventInfoEXT*>(&pDisplayEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
    }
    [[nodiscard]] Result GetSwapchainCounterEXT(Device device,
        SwapchainKHR swapchain,
        SurfaceCounterFlagBitsEXT counter,
        uint64_t&  pCounterValue) {
        return static_cast<Result>(pfn_GetSwapchainCounterEXT(device.get(),
            swapchain.get(),
            static_cast<VkSurfaceCounterFlagBitsEXT>(counter),
            &pCounterValue));
    }
    VK_EXT_display_control_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_DisplayPowerControlEXT = reinterpret_cast<PFN_vkDisplayPowerControlEXT>(get_device_proc_addr(device.get(),"vkDisplayPowerControlEXT"));
        pfn_RegisterDeviceEventEXT = reinterpret_cast<PFN_vkRegisterDeviceEventEXT>(get_device_proc_addr(device.get(),"vkRegisterDeviceEventEXT"));
        pfn_RegisterDisplayEventEXT = reinterpret_cast<PFN_vkRegisterDisplayEventEXT>(get_device_proc_addr(device.get(),"vkRegisterDisplayEventEXT"));
        pfn_GetSwapchainCounterEXT = reinterpret_cast<PFN_vkGetSwapchainCounterEXT>(get_device_proc_addr(device.get(),"vkGetSwapchainCounterEXT"));
    };
};
#endif //defined(VK_EXT_display_control)
#if defined(VK_GOOGLE_display_timing)
struct VK_GOOGLE_display_timing_dispatch_table {
    PFN_vkGetRefreshCycleDurationGOOGLE pfn_GetRefreshCycleDurationGOOGLE;
    PFN_vkGetPastPresentationTimingGOOGLE pfn_GetPastPresentationTimingGOOGLE;
public:
    [[nodiscard]] Result GetRefreshCycleDurationGOOGLE(Device device,
        SwapchainKHR swapchain,
        RefreshCycleDurationGOOGLE&  pDisplayTimingProperties) {
        return static_cast<Result>(pfn_GetRefreshCycleDurationGOOGLE(device.get(),
            swapchain.get(),
            reinterpret_cast<VkRefreshCycleDurationGOOGLE*>(&pDisplayTimingProperties)));
    }
    [[nodiscard]] Result GetPastPresentationTimingGOOGLE(Device device,
        SwapchainKHR swapchain,
        uint32_t&  pPresentationTimingCount,
        PastPresentationTimingGOOGLE* pPresentationTimings) {
        return static_cast<Result>(pfn_GetPastPresentationTimingGOOGLE(device.get(),
            swapchain.get(),
            &pPresentationTimingCount,
            reinterpret_cast<VkPastPresentationTimingGOOGLE*>(pPresentationTimings)));
    }
    VK_GOOGLE_display_timing_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetRefreshCycleDurationGOOGLE = reinterpret_cast<PFN_vkGetRefreshCycleDurationGOOGLE>(get_device_proc_addr(device.get(),"vkGetRefreshCycleDurationGOOGLE"));
        pfn_GetPastPresentationTimingGOOGLE = reinterpret_cast<PFN_vkGetPastPresentationTimingGOOGLE>(get_device_proc_addr(device.get(),"vkGetPastPresentationTimingGOOGLE"));
    };
};
#endif //defined(VK_GOOGLE_display_timing)
#if defined(VK_EXT_discard_rectangles)
struct VK_EXT_discard_rectangles_dispatch_table {
    PFN_vkCmdSetDiscardRectangleEXT pfn_CmdSetDiscardRectangleEXT;
public:
    void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer,
        uint32_t firstDiscardRectangle,
        uint32_t discardRectangleCount,
        const Rect2D* pDiscardRectangles) {
        return pfn_CmdSetDiscardRectangleEXT(commandBuffer.get(),
            firstDiscardRectangle,
            discardRectangleCount,
            reinterpret_cast<const VkRect2D*>(pDiscardRectangles));
    }
    VK_EXT_discard_rectangles_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetDiscardRectangleEXT = reinterpret_cast<PFN_vkCmdSetDiscardRectangleEXT>(get_device_proc_addr(device.get(),"vkCmdSetDiscardRectangleEXT"));
    };
};
#endif //defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_hdr_metadata)
struct VK_EXT_hdr_metadata_dispatch_table {
    PFN_vkSetHdrMetadataEXT pfn_SetHdrMetadataEXT;
public:
    void SetHdrMetadataEXT(Device device,
        uint32_t swapchainCount,
        const SwapchainKHR* pSwapchains,
        const HdrMetadataEXT* pMetadata) {
        return pfn_SetHdrMetadataEXT(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainKHR*>(pSwapchains),
            reinterpret_cast<const VkHdrMetadataEXT*>(pMetadata));
    }
    VK_EXT_hdr_metadata_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_SetHdrMetadataEXT = reinterpret_cast<PFN_vkSetHdrMetadataEXT>(get_device_proc_addr(device.get(),"vkSetHdrMetadataEXT"));
    };
};
#endif //defined(VK_EXT_hdr_metadata)
#if defined(VK_KHR_shared_presentable_image)
struct VK_KHR_shared_presentable_image_dispatch_table {
    PFN_vkGetSwapchainStatusKHR pfn_GetSwapchainStatusKHR;
public:
    [[nodiscard]] Result GetSwapchainStatusKHR(Device device,
        SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_GetSwapchainStatusKHR(device.get(),
            swapchain.get()));
    }
    VK_KHR_shared_presentable_image_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetSwapchainStatusKHR = reinterpret_cast<PFN_vkGetSwapchainStatusKHR>(get_device_proc_addr(device.get(),"vkGetSwapchainStatusKHR"));
    };
};
#endif //defined(VK_KHR_shared_presentable_image)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
struct VK_KHR_external_fence_win32_dispatch_table {
    PFN_vkGetFenceWin32HandleKHR pfn_GetFenceWin32HandleKHR;
    PFN_vkImportFenceWin32HandleKHR pfn_ImportFenceWin32HandleKHR;
public:
    [[nodiscard]] Result GetFenceWin32HandleKHR(Device device,
        const FenceGetWin32HandleInfoKHR&  pGetWin32HandleInfo,
        HANDLE&  pHandle) {
        return static_cast<Result>(pfn_GetFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkFenceGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
    }
    [[nodiscard]] Result ImportFenceWin32HandleKHR(Device device,
        const ImportFenceWin32HandleInfoKHR&  pImportFenceWin32HandleInfo) {
        return static_cast<Result>(pfn_ImportFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportFenceWin32HandleInfoKHR*>(&pImportFenceWin32HandleInfo)));
    }
    VK_KHR_external_fence_win32_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetFenceWin32HandleKHR = reinterpret_cast<PFN_vkGetFenceWin32HandleKHR>(get_device_proc_addr(device.get(),"vkGetFenceWin32HandleKHR"));
        pfn_ImportFenceWin32HandleKHR = reinterpret_cast<PFN_vkImportFenceWin32HandleKHR>(get_device_proc_addr(device.get(),"vkImportFenceWin32HandleKHR"));
    };
};
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
#if defined(VK_KHR_external_fence_fd)
struct VK_KHR_external_fence_fd_dispatch_table {
    PFN_vkGetFenceFdKHR pfn_GetFenceFdKHR;
    PFN_vkImportFenceFdKHR pfn_ImportFenceFdKHR;
public:
    [[nodiscard]] Result GetFenceFdKHR(Device device,
        const FenceGetFdInfoKHR&  pGetFdInfo,
        int&  pFd) {
        return static_cast<Result>(pfn_GetFenceFdKHR(device.get(),
            reinterpret_cast<const VkFenceGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
    }
    [[nodiscard]] Result ImportFenceFdKHR(Device device,
        const ImportFenceFdInfoKHR&  pImportFenceFdInfo) {
        return static_cast<Result>(pfn_ImportFenceFdKHR(device.get(),
            reinterpret_cast<const VkImportFenceFdInfoKHR*>(&pImportFenceFdInfo)));
    }
    VK_KHR_external_fence_fd_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetFenceFdKHR = reinterpret_cast<PFN_vkGetFenceFdKHR>(get_device_proc_addr(device.get(),"vkGetFenceFdKHR"));
        pfn_ImportFenceFdKHR = reinterpret_cast<PFN_vkImportFenceFdKHR>(get_device_proc_addr(device.get(),"vkImportFenceFdKHR"));
    };
};
#endif //defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_performance_query)
struct VK_KHR_performance_query_dispatch_table {
    PFN_vkAcquireProfilingLockKHR pfn_AcquireProfilingLockKHR;
    PFN_vkReleaseProfilingLockKHR pfn_ReleaseProfilingLockKHR;
public:
    [[nodiscard]] Result AcquireProfilingLockKHR(Device device,
        const AcquireProfilingLockInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_AcquireProfilingLockKHR(device.get(),
            reinterpret_cast<const VkAcquireProfilingLockInfoKHR*>(&pInfo)));
    }
    void ReleaseProfilingLockKHR(Device device) {
        return pfn_ReleaseProfilingLockKHR(device.get());
    }
    VK_KHR_performance_query_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_AcquireProfilingLockKHR = reinterpret_cast<PFN_vkAcquireProfilingLockKHR>(get_device_proc_addr(device.get(),"vkAcquireProfilingLockKHR"));
        pfn_ReleaseProfilingLockKHR = reinterpret_cast<PFN_vkReleaseProfilingLockKHR>(get_device_proc_addr(device.get(),"vkReleaseProfilingLockKHR"));
    };
};
#endif //defined(VK_KHR_performance_query)
#if defined(VK_KHR_get_surface_capabilities2)
struct VK_KHR_get_surface_capabilities2_dispatch_table {
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR pfn_GetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR pfn_GetPhysicalDeviceSurfaceFormats2KHR;
public:
    [[nodiscard]] Result GetPhysicalDeviceSurfaceCapabilities2KHR(PhysicalDevice physicalDevice,
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        SurfaceCapabilities2KHR&  pSurfaceCapabilities) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkSurfaceCapabilities2KHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetPhysicalDeviceSurfaceFormats2KHR(PhysicalDevice physicalDevice,
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormat2KHR* pSurfaceFormats) {
        return static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormat2KHR*>(pSurfaceFormats)));
    }
    VK_KHR_get_surface_capabilities2_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_GetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
        pfn_GetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceSurfaceFormats2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceSurfaceFormats2KHR"));
    };
};
#endif //defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_get_display_properties2)
struct VK_KHR_get_display_properties2_dispatch_table {
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR pfn_GetPhysicalDeviceDisplayProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR;
    PFN_vkGetDisplayModeProperties2KHR pfn_GetDisplayModeProperties2KHR;
    PFN_vkGetDisplayPlaneCapabilities2KHR pfn_GetDisplayPlaneCapabilities2KHR;
public:
    [[nodiscard]] Result GetPhysicalDeviceDisplayProperties2KHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPhysicalDeviceDisplayPlaneProperties2KHR(PhysicalDevice physicalDevice,
        uint32_t&  pPropertyCount,
        DisplayPlaneProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlaneProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayModeProperties2KHR(PhysicalDevice physicalDevice,
        DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModeProperties2KHR* pProperties) {
        return static_cast<Result>(pfn_GetDisplayModeProperties2KHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModeProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilities2KHR(PhysicalDevice physicalDevice,
        const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo,
        DisplayPlaneCapabilities2KHR&  pCapabilities) {
        return static_cast<Result>(pfn_GetDisplayPlaneCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkDisplayPlaneInfo2KHR*>(&pDisplayPlaneInfo),
            reinterpret_cast<VkDisplayPlaneCapabilities2KHR*>(&pCapabilities)));
    }
    VK_KHR_get_display_properties2_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_GetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayProperties2KHR"));
        pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
        pfn_GetDisplayModeProperties2KHR = reinterpret_cast<PFN_vkGetDisplayModeProperties2KHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayModeProperties2KHR"));
        pfn_GetDisplayPlaneCapabilities2KHR = reinterpret_cast<PFN_vkGetDisplayPlaneCapabilities2KHR>(get_instance_proc_addr(instance.get(),"vkGetDisplayPlaneCapabilities2KHR"));
    };
};
#endif //defined(VK_KHR_get_display_properties2)
#if defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
struct VK_MVK_ios_surface_dispatch_table {
    PFN_vkCreateIOSSurfaceMVK pfn_CreateIOSSurfaceMVK;
public:
    [[nodiscard]] Result CreateIOSSurfaceMVK(Instance instance,
        const IOSSurfaceCreateInfoMVK&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateIOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkIOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_MVK_ios_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateIOSSurfaceMVK = reinterpret_cast<PFN_vkCreateIOSSurfaceMVK>(get_instance_proc_addr(instance.get(),"vkCreateIOSSurfaceMVK"));
    };
};
#endif //defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
#if defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
struct VK_MVK_macos_surface_dispatch_table {
    PFN_vkCreateMacOSSurfaceMVK pfn_CreateMacOSSurfaceMVK;
public:
    [[nodiscard]] Result CreateMacOSSurfaceMVK(Instance instance,
        const MacOSSurfaceCreateInfoMVK&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateMacOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_MVK_macos_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateMacOSSurfaceMVK = reinterpret_cast<PFN_vkCreateMacOSSurfaceMVK>(get_instance_proc_addr(instance.get(),"vkCreateMacOSSurfaceMVK"));
    };
};
#endif //defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
#if defined(VK_EXT_debug_utils)
struct VK_EXT_debug_utils_dispatch_table {
    PFN_vkCreateDebugUtilsMessengerEXT pfn_CreateDebugUtilsMessengerEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT pfn_DestroyDebugUtilsMessengerEXT;
    PFN_vkSubmitDebugUtilsMessageEXT pfn_SubmitDebugUtilsMessageEXT;
public:
    [[nodiscard]] Result CreateDebugUtilsMessengerEXT(Instance instance,
        const DebugUtilsMessengerCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DebugUtilsMessengerEXT&  pMessenger) {
        return static_cast<Result>(pfn_CreateDebugUtilsMessengerEXT(instance.get(),
            reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugUtilsMessengerEXT*>(&pMessenger)));
    }
    void DestroyDebugUtilsMessengerEXT(Instance instance,
        DebugUtilsMessengerEXT messenger,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDebugUtilsMessengerEXT(instance.get(),
            messenger.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void SubmitDebugUtilsMessageEXT(Instance instance,
        DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        DebugUtilsMessageTypeFlagsEXT messageTypes,
        const DebugUtilsMessengerCallbackDataEXT&  pCallbackData) {
        return pfn_SubmitDebugUtilsMessageEXT(instance.get(),
            static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity),
            static_cast<VkDebugUtilsMessageTypeFlagsEXT>(messageTypes),
            reinterpret_cast<const VkDebugUtilsMessengerCallbackDataEXT*>(&pCallbackData));
    }
    VK_EXT_debug_utils_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(get_instance_proc_addr(instance.get(),"vkCreateDebugUtilsMessengerEXT"));
        pfn_DestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(get_instance_proc_addr(instance.get(),"vkDestroyDebugUtilsMessengerEXT"));
        pfn_SubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(get_instance_proc_addr(instance.get(),"vkSubmitDebugUtilsMessageEXT"));
    };
};
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
struct VK_ANDROID_external_memory_android_hardware_buffer_dispatch_table {
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID pfn_GetAndroidHardwareBufferPropertiesANDROID;
    PFN_vkGetMemoryAndroidHardwareBufferANDROID pfn_GetMemoryAndroidHardwareBufferANDROID;
public:
    [[nodiscard]] Result GetAndroidHardwareBufferPropertiesANDROID(Device device,
        const AHardwareBuffer&  buffer,
        AndroidHardwareBufferPropertiesANDROID&  pProperties) {
        return static_cast<Result>(pfn_GetAndroidHardwareBufferPropertiesANDROID(device.get(),
            &buffer,
            reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID*>(&pProperties)));
    }
    [[nodiscard]] Result GetMemoryAndroidHardwareBufferANDROID(Device device,
        const MemoryGetAndroidHardwareBufferInfoANDROID&  pInfo,
        AHardwareBuffer** pBuffer) {
        return static_cast<Result>(pfn_GetMemoryAndroidHardwareBufferANDROID(device.get(),
            reinterpret_cast<const VkMemoryGetAndroidHardwareBufferInfoANDROID*>(&pInfo),
            pBuffer));
    }
    VK_ANDROID_external_memory_android_hardware_buffer_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<PFN_vkGetAndroidHardwareBufferPropertiesANDROID>(get_device_proc_addr(device.get(),"vkGetAndroidHardwareBufferPropertiesANDROID"));
        pfn_GetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<PFN_vkGetMemoryAndroidHardwareBufferANDROID>(get_device_proc_addr(device.get(),"vkGetMemoryAndroidHardwareBufferANDROID"));
    };
};
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
#if defined(VK_EXT_sample_locations)
struct VK_EXT_sample_locations_dispatch_table {
    PFN_vkCmdSetSampleLocationsEXT pfn_CmdSetSampleLocationsEXT;
public:
    void CmdSetSampleLocationsEXT(CommandBuffer commandBuffer,
        const SampleLocationsInfoEXT&  pSampleLocationsInfo) {
        return pfn_CmdSetSampleLocationsEXT(commandBuffer.get(),
            reinterpret_cast<const VkSampleLocationsInfoEXT*>(&pSampleLocationsInfo));
    }
    VK_EXT_sample_locations_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetSampleLocationsEXT = reinterpret_cast<PFN_vkCmdSetSampleLocationsEXT>(get_device_proc_addr(device.get(),"vkCmdSetSampleLocationsEXT"));
    };
};
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
struct VK_KHR_ray_tracing_dispatch_table {
    PFN_vkDestroyAccelerationStructureKHR pfn_DestroyAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureMemoryRequirementsKHR pfn_GetAccelerationStructureMemoryRequirementsKHR;
    PFN_vkBindAccelerationStructureMemoryKHR pfn_BindAccelerationStructureMemoryKHR;
    PFN_vkCmdCopyAccelerationStructureKHR pfn_CmdCopyAccelerationStructureKHR;
    PFN_vkCopyAccelerationStructureKHR pfn_CopyAccelerationStructureKHR;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR pfn_CmdCopyAccelerationStructureToMemoryKHR;
    PFN_vkCopyAccelerationStructureToMemoryKHR pfn_CopyAccelerationStructureToMemoryKHR;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR pfn_CmdCopyMemoryToAccelerationStructureKHR;
    PFN_vkCopyMemoryToAccelerationStructureKHR pfn_CopyMemoryToAccelerationStructureKHR;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR pfn_CmdWriteAccelerationStructuresPropertiesKHR;
    PFN_vkWriteAccelerationStructuresPropertiesKHR pfn_WriteAccelerationStructuresPropertiesKHR;
    PFN_vkCmdTraceRaysKHR pfn_CmdTraceRaysKHR;
    PFN_vkGetRayTracingShaderGroupHandlesKHR pfn_GetRayTracingShaderGroupHandlesKHR;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR;
    PFN_vkCreateRayTracingPipelinesKHR pfn_CreateRayTracingPipelinesKHR;
    PFN_vkCmdTraceRaysIndirectKHR pfn_CmdTraceRaysIndirectKHR;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR pfn_GetDeviceAccelerationStructureCompatibilityKHR;
    PFN_vkCreateAccelerationStructureKHR pfn_CreateAccelerationStructureKHR;
    PFN_vkCmdBuildAccelerationStructureKHR pfn_CmdBuildAccelerationStructureKHR;
    PFN_vkCmdBuildAccelerationStructureIndirectKHR pfn_CmdBuildAccelerationStructureIndirectKHR;
    PFN_vkBuildAccelerationStructureKHR pfn_BuildAccelerationStructureKHR;
    PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_GetAccelerationStructureDeviceAddressKHR;
public:
    void DestroyAccelerationStructureKHR(Device device,
        AccelerationStructureKHR accelerationStructure,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyAccelerationStructureKHR(device.get(),
            accelerationStructure.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void GetAccelerationStructureMemoryRequirementsKHR(Device device,
        const AccelerationStructureMemoryRequirementsInfoKHR&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetAccelerationStructureMemoryRequirementsKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoKHR*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result BindAccelerationStructureMemoryKHR(Device device,
        uint32_t bindInfoCount,
        const BindAccelerationStructureMemoryInfoKHR* pBindInfos) {
        return static_cast<Result>(pfn_BindAccelerationStructureMemoryKHR(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindAccelerationStructureMemoryInfoKHR*>(pBindInfos)));
    }
    void CmdCopyAccelerationStructureKHR(CommandBuffer commandBuffer,
        const CopyAccelerationStructureInfoKHR&  pInfo) {
        return pfn_CmdCopyAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureKHR(Device device,
        const CopyAccelerationStructureInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdCopyAccelerationStructureToMemoryKHR(CommandBuffer commandBuffer,
        const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) {
        return pfn_CmdCopyAccelerationStructureToMemoryKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureToMemoryKHR(Device device,
        const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyAccelerationStructureToMemoryKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo)));
    }
    void CmdCopyMemoryToAccelerationStructureKHR(CommandBuffer commandBuffer,
        const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) {
        return pfn_CmdCopyMemoryToAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyMemoryToAccelerationStructureKHR(Device device,
        const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) {
        return static_cast<Result>(pfn_CopyMemoryToAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer,
        uint32_t accelerationStructureCount,
        const AccelerationStructureKHR* pAccelerationStructures,
        QueryType queryType,
        QueryPool queryPool,
        uint32_t firstQuery) {
        return pfn_CmdWriteAccelerationStructuresPropertiesKHR(commandBuffer.get(),
            accelerationStructureCount,
            reinterpret_cast<const VkAccelerationStructureKHR*>(pAccelerationStructures),
            static_cast<VkQueryType>(queryType),
            queryPool.get(),
            firstQuery);
    }
    [[nodiscard]] Result WriteAccelerationStructuresPropertiesKHR(Device device,
        uint32_t accelerationStructureCount,
        const AccelerationStructureKHR* pAccelerationStructures,
        QueryType queryType,
        size_t dataSize,
        void* pData,
        size_t stride) {
        return static_cast<Result>(pfn_WriteAccelerationStructuresPropertiesKHR(device.get(),
            accelerationStructureCount,
            reinterpret_cast<const VkAccelerationStructureKHR*>(pAccelerationStructures),
            static_cast<VkQueryType>(queryType),
            dataSize,
            reinterpret_cast<void*>(pData),
            stride));
    }
    void CmdTraceRaysKHR(CommandBuffer commandBuffer,
        const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return pfn_CmdTraceRaysKHR(commandBuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            width,
            height,
            depth);
    }
    [[nodiscard]] Result GetRayTracingShaderGroupHandlesKHR(Device device,
        Pipeline pipeline,
        uint32_t firstGroup,
        uint32_t groupCount,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetRayTracingShaderGroupHandlesKHR(device.get(),
            pipeline.get(),
            firstGroup,
            groupCount,
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result GetRayTracingCaptureReplayShaderGroupHandlesKHR(Device device,
        Pipeline pipeline,
        uint32_t firstGroup,
        uint32_t groupCount,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR(device.get(),
            pipeline.get(),
            firstGroup,
            groupCount,
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result CreateRayTracingPipelinesKHR(Device device,
        PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const RayTracingPipelineCreateInfoKHR* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateRayTracingPipelinesKHR(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkRayTracingPipelineCreateInfoKHR*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    void CmdTraceRaysIndirectKHR(CommandBuffer commandBuffer,
        const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        Buffer buffer,
        DeviceSize offset) {
        return pfn_CmdTraceRaysIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            buffer.get(),
            offset);
    }
    [[nodiscard]] Result GetDeviceAccelerationStructureCompatibilityKHR(Device device,
        const AccelerationStructureVersionKHR&  version) {
        return static_cast<Result>(pfn_GetDeviceAccelerationStructureCompatibilityKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureVersionKHR*>(&version)));
    }
    [[nodiscard]] Result CreateAccelerationStructureKHR(Device device,
        const AccelerationStructureCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        AccelerationStructureKHR&  pAccelerationStructure) {
        return static_cast<Result>(pfn_CreateAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureKHR*>(&pAccelerationStructure)));
    }
    void CmdBuildAccelerationStructureKHR(CommandBuffer commandBuffer,
        uint32_t infoCount,
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return pfn_CmdBuildAccelerationStructureKHR(commandBuffer.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    void CmdBuildAccelerationStructureIndirectKHR(CommandBuffer commandBuffer,
        const AccelerationStructureBuildGeometryInfoKHR&  pInfo,
        Buffer indirectBuffer,
        DeviceSize indirectOffset,
        uint32_t indirectStride) {
        return pfn_CmdBuildAccelerationStructureIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(&pInfo),
            indirectBuffer.get(),
            indirectOffset,
            indirectStride);
    }
    [[nodiscard]] Result BuildAccelerationStructureKHR(Device device,
        uint32_t infoCount,
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return static_cast<Result>(pfn_BuildAccelerationStructureKHR(device.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos)));
    }
    [[nodiscard]] VkDeviceAddress GetAccelerationStructureDeviceAddressKHR(Device device,
        const AccelerationStructureDeviceAddressInfoKHR&  pInfo) {
        return pfn_GetAccelerationStructureDeviceAddressKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureDeviceAddressInfoKHR*>(&pInfo));
    }
    VK_KHR_ray_tracing_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_DestroyAccelerationStructureKHR = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkDestroyAccelerationStructureKHR"));
        pfn_GetAccelerationStructureMemoryRequirementsKHR = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsKHR>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureMemoryRequirementsKHR"));
        pfn_BindAccelerationStructureMemoryKHR = reinterpret_cast<PFN_vkBindAccelerationStructureMemoryKHR>(get_device_proc_addr(device.get(),"vkBindAccelerationStructureMemoryKHR"));
        pfn_CmdCopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureKHR"));
        pfn_CopyAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCopyAccelerationStructureKHR"));
        pfn_CmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureToMemoryKHR"));
        pfn_CopyAccelerationStructureToMemoryKHR = reinterpret_cast<PFN_vkCopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device.get(),"vkCopyAccelerationStructureToMemoryKHR"));
        pfn_CmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdCopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdCopyMemoryToAccelerationStructureKHR"));
        pfn_CopyMemoryToAccelerationStructureKHR = reinterpret_cast<PFN_vkCopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCopyMemoryToAccelerationStructureKHR"));
        pfn_CmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkCmdWriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device.get(),"vkCmdWriteAccelerationStructuresPropertiesKHR"));
        pfn_WriteAccelerationStructuresPropertiesKHR = reinterpret_cast<PFN_vkWriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device.get(),"vkWriteAccelerationStructuresPropertiesKHR"));
        pfn_CmdTraceRaysKHR = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(get_device_proc_addr(device.get(),"vkCmdTraceRaysKHR"));
        pfn_GetRayTracingShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(get_device_proc_addr(device.get(),"vkGetRayTracingShaderGroupHandlesKHR"));
        pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR>(get_device_proc_addr(device.get(),"vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
        pfn_CreateRayTracingPipelinesKHR = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(get_device_proc_addr(device.get(),"vkCreateRayTracingPipelinesKHR"));
        pfn_CmdTraceRaysIndirectKHR = reinterpret_cast<PFN_vkCmdTraceRaysIndirectKHR>(get_device_proc_addr(device.get(),"vkCmdTraceRaysIndirectKHR"));
        pfn_GetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<PFN_vkGetDeviceAccelerationStructureCompatibilityKHR>(get_device_proc_addr(device.get(),"vkGetDeviceAccelerationStructureCompatibilityKHR"));
        pfn_CreateAccelerationStructureKHR = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCreateAccelerationStructureKHR"));
        pfn_CmdBuildAccelerationStructureKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureKHR"));
        pfn_CmdBuildAccelerationStructureIndirectKHR = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureIndirectKHR>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureIndirectKHR"));
        pfn_BuildAccelerationStructureKHR = reinterpret_cast<PFN_vkBuildAccelerationStructureKHR>(get_device_proc_addr(device.get(),"vkBuildAccelerationStructureKHR"));
        pfn_GetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureDeviceAddressKHR"));
    };
};
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
#if defined(VK_EXT_image_drm_format_modifier)
struct VK_EXT_image_drm_format_modifier_dispatch_table {
    PFN_vkGetImageDrmFormatModifierPropertiesEXT pfn_GetImageDrmFormatModifierPropertiesEXT;
public:
    [[nodiscard]] Result GetImageDrmFormatModifierPropertiesEXT(Device device,
        Image image,
        ImageDrmFormatModifierPropertiesEXT&  pProperties) {
        return static_cast<Result>(pfn_GetImageDrmFormatModifierPropertiesEXT(device.get(),
            image.get(),
            reinterpret_cast<VkImageDrmFormatModifierPropertiesEXT*>(&pProperties)));
    }
    VK_EXT_image_drm_format_modifier_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<PFN_vkGetImageDrmFormatModifierPropertiesEXT>(get_device_proc_addr(device.get(),"vkGetImageDrmFormatModifierPropertiesEXT"));
    };
};
#endif //defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_validation_cache)
struct VK_EXT_validation_cache_dispatch_table {
    PFN_vkCreateValidationCacheEXT pfn_CreateValidationCacheEXT;
    PFN_vkDestroyValidationCacheEXT pfn_DestroyValidationCacheEXT;
    PFN_vkGetValidationCacheDataEXT pfn_GetValidationCacheDataEXT;
    PFN_vkMergeValidationCachesEXT pfn_MergeValidationCachesEXT;
public:
    [[nodiscard]] Result CreateValidationCacheEXT(Device device,
        const ValidationCacheCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        ValidationCacheEXT&  pValidationCache) {
        return static_cast<Result>(pfn_CreateValidationCacheEXT(device.get(),
            reinterpret_cast<const VkValidationCacheCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkValidationCacheEXT*>(&pValidationCache)));
    }
    void DestroyValidationCacheEXT(Device device,
        ValidationCacheEXT validationCache,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyValidationCacheEXT(device.get(),
            validationCache.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetValidationCacheDataEXT(Device device,
        ValidationCacheEXT validationCache,
        size_t&  pDataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetValidationCacheDataEXT(device.get(),
            validationCache.get(),
            &pDataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result MergeValidationCachesEXT(Device device,
        ValidationCacheEXT dstCache,
        uint32_t srcCacheCount,
        const ValidationCacheEXT* pSrcCaches) {
        return static_cast<Result>(pfn_MergeValidationCachesEXT(device.get(),
            dstCache.get(),
            srcCacheCount,
            reinterpret_cast<const VkValidationCacheEXT*>(pSrcCaches)));
    }
    VK_EXT_validation_cache_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CreateValidationCacheEXT = reinterpret_cast<PFN_vkCreateValidationCacheEXT>(get_device_proc_addr(device.get(),"vkCreateValidationCacheEXT"));
        pfn_DestroyValidationCacheEXT = reinterpret_cast<PFN_vkDestroyValidationCacheEXT>(get_device_proc_addr(device.get(),"vkDestroyValidationCacheEXT"));
        pfn_GetValidationCacheDataEXT = reinterpret_cast<PFN_vkGetValidationCacheDataEXT>(get_device_proc_addr(device.get(),"vkGetValidationCacheDataEXT"));
        pfn_MergeValidationCachesEXT = reinterpret_cast<PFN_vkMergeValidationCachesEXT>(get_device_proc_addr(device.get(),"vkMergeValidationCachesEXT"));
    };
};
#endif //defined(VK_EXT_validation_cache)
#if defined(VK_NV_shading_rate_image)
struct VK_NV_shading_rate_image_dispatch_table {
    PFN_vkCmdBindShadingRateImageNV pfn_CmdBindShadingRateImageNV;
    PFN_vkCmdSetViewportShadingRatePaletteNV pfn_CmdSetViewportShadingRatePaletteNV;
    PFN_vkCmdSetCoarseSampleOrderNV pfn_CmdSetCoarseSampleOrderNV;
public:
    void CmdBindShadingRateImageNV(CommandBuffer commandBuffer,
        ImageView imageView,
        ImageLayout imageLayout) {
        return pfn_CmdBindShadingRateImageNV(commandBuffer.get(),
            imageView.get(),
            static_cast<VkImageLayout>(imageLayout));
    }
    void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer,
        uint32_t firstViewport,
        uint32_t viewportCount,
        const ShadingRatePaletteNV* pShadingRatePalettes) {
        return pfn_CmdSetViewportShadingRatePaletteNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkShadingRatePaletteNV*>(pShadingRatePalettes));
    }
    void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer,
        CoarseSampleOrderTypeNV sampleOrderType,
        uint32_t customSampleOrderCount,
        const CoarseSampleOrderCustomNV* pCustomSampleOrders) {
        return pfn_CmdSetCoarseSampleOrderNV(commandBuffer.get(),
            static_cast<VkCoarseSampleOrderTypeNV>(sampleOrderType),
            customSampleOrderCount,
            reinterpret_cast<const VkCoarseSampleOrderCustomNV*>(pCustomSampleOrders));
    }
    VK_NV_shading_rate_image_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdBindShadingRateImageNV = reinterpret_cast<PFN_vkCmdBindShadingRateImageNV>(get_device_proc_addr(device.get(),"vkCmdBindShadingRateImageNV"));
        pfn_CmdSetViewportShadingRatePaletteNV = reinterpret_cast<PFN_vkCmdSetViewportShadingRatePaletteNV>(get_device_proc_addr(device.get(),"vkCmdSetViewportShadingRatePaletteNV"));
        pfn_CmdSetCoarseSampleOrderNV = reinterpret_cast<PFN_vkCmdSetCoarseSampleOrderNV>(get_device_proc_addr(device.get(),"vkCmdSetCoarseSampleOrderNV"));
    };
};
#endif //defined(VK_NV_shading_rate_image)
#if defined(VK_NV_ray_tracing)
struct VK_NV_ray_tracing_dispatch_table {
    PFN_vkCompileDeferredNV pfn_CompileDeferredNV;
    PFN_vkCreateAccelerationStructureNV pfn_CreateAccelerationStructureNV;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV pfn_GetAccelerationStructureMemoryRequirementsNV;
    PFN_vkCmdCopyAccelerationStructureNV pfn_CmdCopyAccelerationStructureNV;
    PFN_vkCmdBuildAccelerationStructureNV pfn_CmdBuildAccelerationStructureNV;
    PFN_vkCmdTraceRaysNV pfn_CmdTraceRaysNV;
    PFN_vkGetAccelerationStructureHandleNV pfn_GetAccelerationStructureHandleNV;
    PFN_vkCreateRayTracingPipelinesNV pfn_CreateRayTracingPipelinesNV;
public:
    [[nodiscard]] Result CompileDeferredNV(Device device,
        Pipeline pipeline,
        uint32_t shader) {
        return static_cast<Result>(pfn_CompileDeferredNV(device.get(),
            pipeline.get(),
            shader));
    }
    [[nodiscard]] Result CreateAccelerationStructureNV(Device device,
        const AccelerationStructureCreateInfoNV&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        AccelerationStructureNV&  pAccelerationStructure) {
        return static_cast<Result>(pfn_CreateAccelerationStructureNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureNV*>(&pAccelerationStructure)));
    }
    void GetAccelerationStructureMemoryRequirementsNV(Device device,
        const AccelerationStructureMemoryRequirementsInfoNV&  pInfo,
        MemoryRequirements2KHR&  pMemoryRequirements) {
        return pfn_GetAccelerationStructureMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2KHR*>(&pMemoryRequirements));
    }
    void CmdCopyAccelerationStructureNV(CommandBuffer commandBuffer,
        AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        CopyAccelerationStructureModeKHR mode) {
        return pfn_CmdCopyAccelerationStructureNV(commandBuffer.get(),
            dst.get(),
            src.get(),
            static_cast<VkCopyAccelerationStructureModeKHR>(mode));
    }
    void CmdBuildAccelerationStructureNV(CommandBuffer commandBuffer,
        const AccelerationStructureInfoNV&  pInfo,
        Buffer instanceData,
        DeviceSize instanceOffset,
        Bool32 update,
        AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        Buffer scratch,
        DeviceSize scratchOffset) {
        return pfn_CmdBuildAccelerationStructureNV(commandBuffer.get(),
            reinterpret_cast<const VkAccelerationStructureInfoNV*>(&pInfo),
            instanceData.get(),
            instanceOffset,
            update,
            dst.get(),
            src.get(),
            scratch.get(),
            scratchOffset);
    }
    void CmdTraceRaysNV(CommandBuffer commandBuffer,
        Buffer raygenShaderBindingTableBuffer,
        DeviceSize raygenShaderBindingOffset,
        Buffer missShaderBindingTableBuffer,
        DeviceSize missShaderBindingOffset,
        DeviceSize missShaderBindingStride,
        Buffer hitShaderBindingTableBuffer,
        DeviceSize hitShaderBindingOffset,
        DeviceSize hitShaderBindingStride,
        Buffer callableShaderBindingTableBuffer,
        DeviceSize callableShaderBindingOffset,
        DeviceSize callableShaderBindingStride,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return pfn_CmdTraceRaysNV(commandBuffer.get(),
            raygenShaderBindingTableBuffer.get(),
            raygenShaderBindingOffset,
            missShaderBindingTableBuffer.get(),
            missShaderBindingOffset,
            missShaderBindingStride,
            hitShaderBindingTableBuffer.get(),
            hitShaderBindingOffset,
            hitShaderBindingStride,
            callableShaderBindingTableBuffer.get(),
            callableShaderBindingOffset,
            callableShaderBindingStride,
            width,
            height,
            depth);
    }
    [[nodiscard]] Result GetAccelerationStructureHandleNV(Device device,
        AccelerationStructureKHR accelerationStructure,
        size_t dataSize,
        void* pData) {
        return static_cast<Result>(pfn_GetAccelerationStructureHandleNV(device.get(),
            accelerationStructure.get(),
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result CreateRayTracingPipelinesNV(Device device,
        PipelineCache pipelineCache,
        uint32_t createInfoCount,
        const RayTracingPipelineCreateInfoNV* pCreateInfos,
        const AllocationCallbacks* pAllocator,
        Pipeline* pPipelines) {
        return static_cast<Result>(pfn_CreateRayTracingPipelinesNV(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkRayTracingPipelineCreateInfoNV*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    VK_NV_ray_tracing_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CompileDeferredNV = reinterpret_cast<PFN_vkCompileDeferredNV>(get_device_proc_addr(device.get(),"vkCompileDeferredNV"));
        pfn_CreateAccelerationStructureNV = reinterpret_cast<PFN_vkCreateAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCreateAccelerationStructureNV"));
        pfn_GetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<PFN_vkGetAccelerationStructureMemoryRequirementsNV>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureMemoryRequirementsNV"));
        pfn_CmdCopyAccelerationStructureNV = reinterpret_cast<PFN_vkCmdCopyAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCmdCopyAccelerationStructureNV"));
        pfn_CmdBuildAccelerationStructureNV = reinterpret_cast<PFN_vkCmdBuildAccelerationStructureNV>(get_device_proc_addr(device.get(),"vkCmdBuildAccelerationStructureNV"));
        pfn_CmdTraceRaysNV = reinterpret_cast<PFN_vkCmdTraceRaysNV>(get_device_proc_addr(device.get(),"vkCmdTraceRaysNV"));
        pfn_GetAccelerationStructureHandleNV = reinterpret_cast<PFN_vkGetAccelerationStructureHandleNV>(get_device_proc_addr(device.get(),"vkGetAccelerationStructureHandleNV"));
        pfn_CreateRayTracingPipelinesNV = reinterpret_cast<PFN_vkCreateRayTracingPipelinesNV>(get_device_proc_addr(device.get(),"vkCreateRayTracingPipelinesNV"));
    };
};
#endif //defined(VK_NV_ray_tracing)
#if defined(VK_EXT_external_memory_host)
struct VK_EXT_external_memory_host_dispatch_table {
    PFN_vkGetMemoryHostPointerPropertiesEXT pfn_GetMemoryHostPointerPropertiesEXT;
public:
    [[nodiscard]] Result GetMemoryHostPointerPropertiesEXT(Device device,
        ExternalMemoryHandleTypeFlagBits handleType,
        const void* pHostPointer,
        MemoryHostPointerPropertiesEXT&  pMemoryHostPointerProperties) {
        return static_cast<Result>(pfn_GetMemoryHostPointerPropertiesEXT(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            reinterpret_cast<const void*>(pHostPointer),
            reinterpret_cast<VkMemoryHostPointerPropertiesEXT*>(&pMemoryHostPointerProperties)));
    }
    VK_EXT_external_memory_host_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetMemoryHostPointerPropertiesEXT = reinterpret_cast<PFN_vkGetMemoryHostPointerPropertiesEXT>(get_device_proc_addr(device.get(),"vkGetMemoryHostPointerPropertiesEXT"));
    };
};
#endif //defined(VK_EXT_external_memory_host)
#if defined(VK_AMD_buffer_marker)
struct VK_AMD_buffer_marker_dispatch_table {
    PFN_vkCmdWriteBufferMarkerAMD pfn_CmdWriteBufferMarkerAMD;
public:
    void CmdWriteBufferMarkerAMD(CommandBuffer commandBuffer,
        PipelineStageFlagBits pipelineStage,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        uint32_t marker) {
        return pfn_CmdWriteBufferMarkerAMD(commandBuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            dstBuffer.get(),
            dstOffset,
            marker);
    }
    VK_AMD_buffer_marker_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdWriteBufferMarkerAMD = reinterpret_cast<PFN_vkCmdWriteBufferMarkerAMD>(get_device_proc_addr(device.get(),"vkCmdWriteBufferMarkerAMD"));
    };
};
#endif //defined(VK_AMD_buffer_marker)
#if defined(VK_EXT_calibrated_timestamps)
struct VK_EXT_calibrated_timestamps_dispatch_table {
    PFN_vkGetCalibratedTimestampsEXT pfn_GetCalibratedTimestampsEXT;
public:
    [[nodiscard]] Result GetCalibratedTimestampsEXT(Device device,
        uint32_t timestampCount,
        const CalibratedTimestampInfoEXT* pTimestampInfos,
        uint64_t* pTimestamps,
        uint64_t&  pMaxDeviation) {
        return static_cast<Result>(pfn_GetCalibratedTimestampsEXT(device.get(),
            timestampCount,
            reinterpret_cast<const VkCalibratedTimestampInfoEXT*>(pTimestampInfos),
            pTimestamps,
            &pMaxDeviation));
    }
    VK_EXT_calibrated_timestamps_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetCalibratedTimestampsEXT = reinterpret_cast<PFN_vkGetCalibratedTimestampsEXT>(get_device_proc_addr(device.get(),"vkGetCalibratedTimestampsEXT"));
    };
};
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_NV_mesh_shader)
struct VK_NV_mesh_shader_dispatch_table {
    PFN_vkCmdDrawMeshTasksNV pfn_CmdDrawMeshTasksNV;
    PFN_vkCmdDrawMeshTasksIndirectNV pfn_CmdDrawMeshTasksIndirectNV;
    PFN_vkCmdDrawMeshTasksIndirectCountNV pfn_CmdDrawMeshTasksIndirectCountNV;
public:
    void CmdDrawMeshTasksNV(CommandBuffer commandBuffer,
        uint32_t taskCount,
        uint32_t firstTask) {
        return pfn_CmdDrawMeshTasksNV(commandBuffer.get(),
            taskCount,
            firstTask);
    }
    void CmdDrawMeshTasksIndirectNV(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return pfn_CmdDrawMeshTasksIndirectNV(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDrawMeshTasksIndirectCountNV(CommandBuffer commandBuffer,
        Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return pfn_CmdDrawMeshTasksIndirectCountNV(commandBuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    VK_NV_mesh_shader_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdDrawMeshTasksNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksNV"));
        pfn_CmdDrawMeshTasksIndirectNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksIndirectNV"));
        pfn_CmdDrawMeshTasksIndirectCountNV = reinterpret_cast<PFN_vkCmdDrawMeshTasksIndirectCountNV>(get_device_proc_addr(device.get(),"vkCmdDrawMeshTasksIndirectCountNV"));
    };
};
#endif //defined(VK_NV_mesh_shader)
#if defined(VK_NV_scissor_exclusive)
struct VK_NV_scissor_exclusive_dispatch_table {
    PFN_vkCmdSetExclusiveScissorNV pfn_CmdSetExclusiveScissorNV;
public:
    void CmdSetExclusiveScissorNV(CommandBuffer commandBuffer,
        uint32_t firstExclusiveScissor,
        uint32_t exclusiveScissorCount,
        const Rect2D* pExclusiveScissors) {
        return pfn_CmdSetExclusiveScissorNV(commandBuffer.get(),
            firstExclusiveScissor,
            exclusiveScissorCount,
            reinterpret_cast<const VkRect2D*>(pExclusiveScissors));
    }
    VK_NV_scissor_exclusive_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetExclusiveScissorNV = reinterpret_cast<PFN_vkCmdSetExclusiveScissorNV>(get_device_proc_addr(device.get(),"vkCmdSetExclusiveScissorNV"));
    };
};
#endif //defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_device_diagnostic_checkpoints)
struct VK_NV_device_diagnostic_checkpoints_dispatch_table {
    PFN_vkCmdSetCheckpointNV pfn_CmdSetCheckpointNV;
    PFN_vkGetQueueCheckpointDataNV pfn_GetQueueCheckpointDataNV;
public:
    void CmdSetCheckpointNV(CommandBuffer commandBuffer,
        const void* pCheckpointMarker) {
        return pfn_CmdSetCheckpointNV(commandBuffer.get(),
            reinterpret_cast<const void*>(pCheckpointMarker));
    }
    void GetQueueCheckpointDataNV(Queue queue,
        uint32_t&  pCheckpointDataCount,
        CheckpointDataNV* pCheckpointData) {
        return pfn_GetQueueCheckpointDataNV(queue.get(),
            &pCheckpointDataCount,
            reinterpret_cast<VkCheckpointDataNV*>(pCheckpointData));
    }
    VK_NV_device_diagnostic_checkpoints_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetCheckpointNV = reinterpret_cast<PFN_vkCmdSetCheckpointNV>(get_device_proc_addr(device.get(),"vkCmdSetCheckpointNV"));
        pfn_GetQueueCheckpointDataNV = reinterpret_cast<PFN_vkGetQueueCheckpointDataNV>(get_device_proc_addr(device.get(),"vkGetQueueCheckpointDataNV"));
    };
};
#endif //defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_INTEL_performance_query)
struct VK_INTEL_performance_query_dispatch_table {
    PFN_vkInitializePerformanceApiINTEL pfn_InitializePerformanceApiINTEL;
    PFN_vkUninitializePerformanceApiINTEL pfn_UninitializePerformanceApiINTEL;
    PFN_vkCmdSetPerformanceMarkerINTEL pfn_CmdSetPerformanceMarkerINTEL;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL pfn_CmdSetPerformanceStreamMarkerINTEL;
    PFN_vkCmdSetPerformanceOverrideINTEL pfn_CmdSetPerformanceOverrideINTEL;
    PFN_vkAcquirePerformanceConfigurationINTEL pfn_AcquirePerformanceConfigurationINTEL;
    PFN_vkReleasePerformanceConfigurationINTEL pfn_ReleasePerformanceConfigurationINTEL;
    PFN_vkQueueSetPerformanceConfigurationINTEL pfn_QueueSetPerformanceConfigurationINTEL;
    PFN_vkGetPerformanceParameterINTEL pfn_GetPerformanceParameterINTEL;
public:
    [[nodiscard]] Result InitializePerformanceApiINTEL(Device device,
        const InitializePerformanceApiInfoINTEL&  pInitializeInfo) {
        return static_cast<Result>(pfn_InitializePerformanceApiINTEL(device.get(),
            reinterpret_cast<const VkInitializePerformanceApiInfoINTEL*>(&pInitializeInfo)));
    }
    void UninitializePerformanceApiINTEL(Device device) {
        return pfn_UninitializePerformanceApiINTEL(device.get());
    }
    [[nodiscard]] Result CmdSetPerformanceMarkerINTEL(CommandBuffer commandBuffer,
        const PerformanceMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceStreamMarkerINTEL(CommandBuffer commandBuffer,
        const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceStreamMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceOverrideINTEL(CommandBuffer commandBuffer,
        const PerformanceOverrideInfoINTEL&  pOverrideInfo) {
        return static_cast<Result>(pfn_CmdSetPerformanceOverrideINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceOverrideInfoINTEL*>(&pOverrideInfo)));
    }
    [[nodiscard]] Result AcquirePerformanceConfigurationINTEL(Device device,
        const PerformanceConfigurationAcquireInfoINTEL&  pAcquireInfo,
        PerformanceConfigurationINTEL&  pConfiguration) {
        return static_cast<Result>(pfn_AcquirePerformanceConfigurationINTEL(device.get(),
            reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL*>(&pAcquireInfo),
            reinterpret_cast<VkPerformanceConfigurationINTEL*>(&pConfiguration)));
    }
    [[nodiscard]] Result ReleasePerformanceConfigurationINTEL(Device device,
        PerformanceConfigurationINTEL configuration) {
        return static_cast<Result>(pfn_ReleasePerformanceConfigurationINTEL(device.get(),
            configuration.get()));
    }
    [[nodiscard]] Result QueueSetPerformanceConfigurationINTEL(Queue queue,
        PerformanceConfigurationINTEL configuration) {
        return static_cast<Result>(pfn_QueueSetPerformanceConfigurationINTEL(queue.get(),
            configuration.get()));
    }
    [[nodiscard]] Result GetPerformanceParameterINTEL(Device device,
        PerformanceParameterTypeINTEL parameter,
        PerformanceValueINTEL&  pValue) {
        return static_cast<Result>(pfn_GetPerformanceParameterINTEL(device.get(),
            static_cast<VkPerformanceParameterTypeINTEL>(parameter),
            reinterpret_cast<VkPerformanceValueINTEL*>(&pValue)));
    }
    VK_INTEL_performance_query_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_InitializePerformanceApiINTEL = reinterpret_cast<PFN_vkInitializePerformanceApiINTEL>(get_device_proc_addr(device.get(),"vkInitializePerformanceApiINTEL"));
        pfn_UninitializePerformanceApiINTEL = reinterpret_cast<PFN_vkUninitializePerformanceApiINTEL>(get_device_proc_addr(device.get(),"vkUninitializePerformanceApiINTEL"));
        pfn_CmdSetPerformanceMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceMarkerINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceMarkerINTEL"));
        pfn_CmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceStreamMarkerINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceStreamMarkerINTEL"));
        pfn_CmdSetPerformanceOverrideINTEL = reinterpret_cast<PFN_vkCmdSetPerformanceOverrideINTEL>(get_device_proc_addr(device.get(),"vkCmdSetPerformanceOverrideINTEL"));
        pfn_AcquirePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkAcquirePerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkAcquirePerformanceConfigurationINTEL"));
        pfn_ReleasePerformanceConfigurationINTEL = reinterpret_cast<PFN_vkReleasePerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkReleasePerformanceConfigurationINTEL"));
        pfn_QueueSetPerformanceConfigurationINTEL = reinterpret_cast<PFN_vkQueueSetPerformanceConfigurationINTEL>(get_device_proc_addr(device.get(),"vkQueueSetPerformanceConfigurationINTEL"));
        pfn_GetPerformanceParameterINTEL = reinterpret_cast<PFN_vkGetPerformanceParameterINTEL>(get_device_proc_addr(device.get(),"vkGetPerformanceParameterINTEL"));
    };
};
#endif //defined(VK_INTEL_performance_query)
#if defined(VK_AMD_display_native_hdr)
struct VK_AMD_display_native_hdr_dispatch_table {
    PFN_vkSetLocalDimmingAMD pfn_SetLocalDimmingAMD;
public:
    void SetLocalDimmingAMD(Device device,
        SwapchainKHR swapChain,
        Bool32 localDimmingEnable) {
        return pfn_SetLocalDimmingAMD(device.get(),
            swapChain.get(),
            localDimmingEnable);
    }
    VK_AMD_display_native_hdr_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_SetLocalDimmingAMD = reinterpret_cast<PFN_vkSetLocalDimmingAMD>(get_device_proc_addr(device.get(),"vkSetLocalDimmingAMD"));
    };
};
#endif //defined(VK_AMD_display_native_hdr)
#if defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
struct VK_FUCHSIA_imagepipe_surface_dispatch_table {
    PFN_vkCreateImagePipeSurfaceFUCHSIA pfn_CreateImagePipeSurfaceFUCHSIA;
public:
    [[nodiscard]] Result CreateImagePipeSurfaceFUCHSIA(Instance instance,
        const ImagePipeSurfaceCreateInfoFUCHSIA&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateImagePipeSurfaceFUCHSIA(instance.get(),
            reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_FUCHSIA_imagepipe_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateImagePipeSurfaceFUCHSIA = reinterpret_cast<PFN_vkCreateImagePipeSurfaceFUCHSIA>(get_instance_proc_addr(instance.get(),"vkCreateImagePipeSurfaceFUCHSIA"));
    };
};
#endif //defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
#if defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
struct VK_EXT_metal_surface_dispatch_table {
    PFN_vkCreateMetalSurfaceEXT pfn_CreateMetalSurfaceEXT;
public:
    [[nodiscard]] Result CreateMetalSurfaceEXT(Instance instance,
        const MetalSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateMetalSurfaceEXT(instance.get(),
            reinterpret_cast<const VkMetalSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_EXT_metal_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateMetalSurfaceEXT = reinterpret_cast<PFN_vkCreateMetalSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateMetalSurfaceEXT"));
    };
};
#endif //defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
struct VK_EXT_full_screen_exclusive_dispatch_tableFunctions {
    Device const device;
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    PFN_vkAcquireFullScreenExclusiveModeEXT pfn_AcquireFullScreenExclusiveModeEXT;
    PFN_vkReleaseFullScreenExclusiveModeEXT pfn_ReleaseFullScreenExclusiveModeEXT;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT pfn_GetDeviceGroupSurfacePresentModes2EXT;
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    [[nodiscard]] Result AcquireFullScreenExclusiveModeEXT(SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_AcquireFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
    [[nodiscard]] Result ReleaseFullScreenExclusiveModeEXT(SwapchainKHR swapchain) {
        return static_cast<Result>(pfn_ReleaseFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    [[nodiscard]] Result GetDeviceGroupSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        DeviceGroupPresentModeFlagsKHR&  pModes) {
        return static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModes2EXT(device.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    VK_EXT_full_screen_exclusive_dispatch_tableFunctions(InstanceFunctions const& instance_functions, Device device){
    PFN_vkGetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
        pfn_AcquireFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkAcquireFullScreenExclusiveModeEXT>(get_device_proc_addr(device.get(),"vkAcquireFullScreenExclusiveModeEXT"));
        pfn_ReleaseFullScreenExclusiveModeEXT = reinterpret_cast<PFN_vkReleaseFullScreenExclusiveModeEXT>(get_device_proc_addr(device.get(),"vkReleaseFullScreenExclusiveModeEXT"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
        pfn_GetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<PFN_vkGetDeviceGroupSurfacePresentModes2EXT>(get_device_proc_addr(device.get(),"vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    };
};
#if defined(VK_EXT_headless_surface)
struct VK_EXT_headless_surface_dispatch_table {
    PFN_vkCreateHeadlessSurfaceEXT pfn_CreateHeadlessSurfaceEXT;
public:
    [[nodiscard]] Result CreateHeadlessSurfaceEXT(Instance instance,
        const HeadlessSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateHeadlessSurfaceEXT(instance.get(),
            reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    VK_EXT_headless_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateHeadlessSurfaceEXT = reinterpret_cast<PFN_vkCreateHeadlessSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateHeadlessSurfaceEXT"));
    };
};
#endif //defined(VK_EXT_headless_surface)
#if defined(VK_EXT_line_rasterization)
struct VK_EXT_line_rasterization_dispatch_table {
    PFN_vkCmdSetLineStippleEXT pfn_CmdSetLineStippleEXT;
public:
    void CmdSetLineStippleEXT(CommandBuffer commandBuffer,
        uint32_t lineStippleFactor,
        uint16_t lineStipplePattern) {
        return pfn_CmdSetLineStippleEXT(commandBuffer.get(),
            lineStippleFactor,
            lineStipplePattern);
    }
    VK_EXT_line_rasterization_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetLineStippleEXT = reinterpret_cast<PFN_vkCmdSetLineStippleEXT>(get_device_proc_addr(device.get(),"vkCmdSetLineStippleEXT"));
    };
};
#endif //defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_extended_dynamic_state)
struct VK_EXT_extended_dynamic_state_dispatch_table {
    PFN_vkCmdSetCullModeEXT pfn_CmdSetCullModeEXT;
    PFN_vkCmdSetFrontFaceEXT pfn_CmdSetFrontFaceEXT;
    PFN_vkCmdSetPrimitiveTopologyEXT pfn_CmdSetPrimitiveTopologyEXT;
    PFN_vkCmdSetViewportWithCountEXT pfn_CmdSetViewportWithCountEXT;
    PFN_vkCmdSetScissorWithCountEXT pfn_CmdSetScissorWithCountEXT;
    PFN_vkCmdBindVertexBuffers2EXT pfn_CmdBindVertexBuffers2EXT;
    PFN_vkCmdSetDepthTestEnableEXT pfn_CmdSetDepthTestEnableEXT;
    PFN_vkCmdSetDepthWriteEnableEXT pfn_CmdSetDepthWriteEnableEXT;
    PFN_vkCmdSetDepthCompareOpEXT pfn_CmdSetDepthCompareOpEXT;
    PFN_vkCmdSetDepthBoundsTestEnableEXT pfn_CmdSetDepthBoundsTestEnableEXT;
    PFN_vkCmdSetStencilTestEnableEXT pfn_CmdSetStencilTestEnableEXT;
    PFN_vkCmdSetStencilOpEXT pfn_CmdSetStencilOpEXT;
public:
    void CmdSetCullModeEXT(CommandBuffer commandBuffer,
        CullModeFlags cullMode) {
        return pfn_CmdSetCullModeEXT(commandBuffer.get(),
            static_cast<VkCullModeFlags>(cullMode));
    }
    void CmdSetFrontFaceEXT(CommandBuffer commandBuffer,
        FrontFace frontFace) {
        return pfn_CmdSetFrontFaceEXT(commandBuffer.get(),
            static_cast<VkFrontFace>(frontFace));
    }
    void CmdSetPrimitiveTopologyEXT(CommandBuffer commandBuffer,
        PrimitiveTopology primitiveTopology) {
        return pfn_CmdSetPrimitiveTopologyEXT(commandBuffer.get(),
            static_cast<VkPrimitiveTopology>(primitiveTopology));
    }
    void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer,
        uint32_t viewportCount,
        const Viewport* pViewports) {
        return pfn_CmdSetViewportWithCountEXT(commandBuffer.get(),
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer,
        uint32_t scissorCount,
        const Rect2D* pScissors) {
        return pfn_CmdSetScissorWithCountEXT(commandBuffer.get(),
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer,
        uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes,
        const DeviceSize* pStrides) {
        return pfn_CmdBindVertexBuffers2EXT(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes,
            pStrides);
    }
    void CmdSetDepthTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthTestEnable) {
        return pfn_CmdSetDepthTestEnableEXT(commandBuffer.get(),
            depthTestEnable);
    }
    void CmdSetDepthWriteEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthWriteEnable) {
        return pfn_CmdSetDepthWriteEnableEXT(commandBuffer.get(),
            depthWriteEnable);
    }
    void CmdSetDepthCompareOpEXT(CommandBuffer commandBuffer,
        CompareOp depthCompareOp) {
        return pfn_CmdSetDepthCompareOpEXT(commandBuffer.get(),
            static_cast<VkCompareOp>(depthCompareOp));
    }
    void CmdSetDepthBoundsTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 depthBoundsTestEnable) {
        return pfn_CmdSetDepthBoundsTestEnableEXT(commandBuffer.get(),
            depthBoundsTestEnable);
    }
    void CmdSetStencilTestEnableEXT(CommandBuffer commandBuffer,
        Bool32 stencilTestEnable) {
        return pfn_CmdSetStencilTestEnableEXT(commandBuffer.get(),
            stencilTestEnable);
    }
    void CmdSetStencilOpEXT(CommandBuffer commandBuffer,
        StencilFaceFlags faceMask,
        StencilOp failOp,
        StencilOp passOp,
        StencilOp depthFailOp,
        CompareOp compareOp) {
        return pfn_CmdSetStencilOpEXT(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            static_cast<VkStencilOp>(failOp),
            static_cast<VkStencilOp>(passOp),
            static_cast<VkStencilOp>(depthFailOp),
            static_cast<VkCompareOp>(compareOp));
    }
    VK_EXT_extended_dynamic_state_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdSetCullModeEXT = reinterpret_cast<PFN_vkCmdSetCullModeEXT>(get_device_proc_addr(device.get(),"vkCmdSetCullModeEXT"));
        pfn_CmdSetFrontFaceEXT = reinterpret_cast<PFN_vkCmdSetFrontFaceEXT>(get_device_proc_addr(device.get(),"vkCmdSetFrontFaceEXT"));
        pfn_CmdSetPrimitiveTopologyEXT = reinterpret_cast<PFN_vkCmdSetPrimitiveTopologyEXT>(get_device_proc_addr(device.get(),"vkCmdSetPrimitiveTopologyEXT"));
        pfn_CmdSetViewportWithCountEXT = reinterpret_cast<PFN_vkCmdSetViewportWithCountEXT>(get_device_proc_addr(device.get(),"vkCmdSetViewportWithCountEXT"));
        pfn_CmdSetScissorWithCountEXT = reinterpret_cast<PFN_vkCmdSetScissorWithCountEXT>(get_device_proc_addr(device.get(),"vkCmdSetScissorWithCountEXT"));
        pfn_CmdBindVertexBuffers2EXT = reinterpret_cast<PFN_vkCmdBindVertexBuffers2EXT>(get_device_proc_addr(device.get(),"vkCmdBindVertexBuffers2EXT"));
        pfn_CmdSetDepthTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthTestEnableEXT"));
        pfn_CmdSetDepthWriteEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthWriteEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthWriteEnableEXT"));
        pfn_CmdSetDepthCompareOpEXT = reinterpret_cast<PFN_vkCmdSetDepthCompareOpEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthCompareOpEXT"));
        pfn_CmdSetDepthBoundsTestEnableEXT = reinterpret_cast<PFN_vkCmdSetDepthBoundsTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetDepthBoundsTestEnableEXT"));
        pfn_CmdSetStencilTestEnableEXT = reinterpret_cast<PFN_vkCmdSetStencilTestEnableEXT>(get_device_proc_addr(device.get(),"vkCmdSetStencilTestEnableEXT"));
        pfn_CmdSetStencilOpEXT = reinterpret_cast<PFN_vkCmdSetStencilOpEXT>(get_device_proc_addr(device.get(),"vkCmdSetStencilOpEXT"));
    };
};
#endif //defined(VK_EXT_extended_dynamic_state)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
struct VK_KHR_deferred_host_operations_dispatch_table {
    PFN_vkCreateDeferredOperationKHR pfn_CreateDeferredOperationKHR;
    PFN_vkDestroyDeferredOperationKHR pfn_DestroyDeferredOperationKHR;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR pfn_GetDeferredOperationMaxConcurrencyKHR;
    PFN_vkGetDeferredOperationResultKHR pfn_GetDeferredOperationResultKHR;
    PFN_vkDeferredOperationJoinKHR pfn_DeferredOperationJoinKHR;
public:
    [[nodiscard]] Result CreateDeferredOperationKHR(Device device,
        const AllocationCallbacks* pAllocator,
        DeferredOperationKHR&  pDeferredOperation) {
        return static_cast<Result>(pfn_CreateDeferredOperationKHR(device.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDeferredOperationKHR*>(&pDeferredOperation)));
    }
    void DestroyDeferredOperationKHR(Device device,
        DeferredOperationKHR operation,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyDeferredOperationKHR(device.get(),
            operation.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] uint32_t GetDeferredOperationMaxConcurrencyKHR(Device device,
        DeferredOperationKHR operation) {
        return pfn_GetDeferredOperationMaxConcurrencyKHR(device.get(),
            operation.get());
    }
    [[nodiscard]] Result GetDeferredOperationResultKHR(Device device,
        DeferredOperationKHR operation) {
        return static_cast<Result>(pfn_GetDeferredOperationResultKHR(device.get(),
            operation.get()));
    }
    [[nodiscard]] Result DeferredOperationJoinKHR(Device device,
        DeferredOperationKHR operation) {
        return static_cast<Result>(pfn_DeferredOperationJoinKHR(device.get(),
            operation.get()));
    }
    VK_KHR_deferred_host_operations_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CreateDeferredOperationKHR = reinterpret_cast<PFN_vkCreateDeferredOperationKHR>(get_device_proc_addr(device.get(),"vkCreateDeferredOperationKHR"));
        pfn_DestroyDeferredOperationKHR = reinterpret_cast<PFN_vkDestroyDeferredOperationKHR>(get_device_proc_addr(device.get(),"vkDestroyDeferredOperationKHR"));
        pfn_GetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<PFN_vkGetDeferredOperationMaxConcurrencyKHR>(get_device_proc_addr(device.get(),"vkGetDeferredOperationMaxConcurrencyKHR"));
        pfn_GetDeferredOperationResultKHR = reinterpret_cast<PFN_vkGetDeferredOperationResultKHR>(get_device_proc_addr(device.get(),"vkGetDeferredOperationResultKHR"));
        pfn_DeferredOperationJoinKHR = reinterpret_cast<PFN_vkDeferredOperationJoinKHR>(get_device_proc_addr(device.get(),"vkDeferredOperationJoinKHR"));
    };
};
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
#if defined(VK_KHR_pipeline_executable_properties)
struct VK_KHR_pipeline_executable_properties_dispatch_table {
    PFN_vkGetPipelineExecutablePropertiesKHR pfn_GetPipelineExecutablePropertiesKHR;
    PFN_vkGetPipelineExecutableStatisticsKHR pfn_GetPipelineExecutableStatisticsKHR;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR pfn_GetPipelineExecutableInternalRepresentationsKHR;
public:
    [[nodiscard]] Result GetPipelineExecutablePropertiesKHR(Device device,
        const PipelineInfoKHR&  pPipelineInfo,
        uint32_t&  pExecutableCount,
        PipelineExecutablePropertiesKHR* pProperties) {
        return static_cast<Result>(pfn_GetPipelineExecutablePropertiesKHR(device.get(),
            reinterpret_cast<const VkPipelineInfoKHR*>(&pPipelineInfo),
            &pExecutableCount,
            reinterpret_cast<VkPipelineExecutablePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetPipelineExecutableStatisticsKHR(Device device,
        const PipelineExecutableInfoKHR&  pExecutableInfo,
        uint32_t&  pStatisticCount,
        PipelineExecutableStatisticKHR* pStatistics) {
        return static_cast<Result>(pfn_GetPipelineExecutableStatisticsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pStatisticCount,
            reinterpret_cast<VkPipelineExecutableStatisticKHR*>(pStatistics)));
    }
    [[nodiscard]] Result GetPipelineExecutableInternalRepresentationsKHR(Device device,
        const PipelineExecutableInfoKHR&  pExecutableInfo,
        uint32_t&  pInternalRepresentationCount,
        PipelineExecutableInternalRepresentationKHR* pInternalRepresentations) {
        return static_cast<Result>(pfn_GetPipelineExecutableInternalRepresentationsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pInternalRepresentationCount,
            reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR*>(pInternalRepresentations)));
    }
    VK_KHR_pipeline_executable_properties_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_GetPipelineExecutablePropertiesKHR = reinterpret_cast<PFN_vkGetPipelineExecutablePropertiesKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutablePropertiesKHR"));
        pfn_GetPipelineExecutableStatisticsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableStatisticsKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutableStatisticsKHR"));
        pfn_GetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<PFN_vkGetPipelineExecutableInternalRepresentationsKHR>(get_device_proc_addr(device.get(),"vkGetPipelineExecutableInternalRepresentationsKHR"));
    };
};
#endif //defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_NV_device_generated_commands)
struct VK_NV_device_generated_commands_dispatch_table {
    PFN_vkCmdExecuteGeneratedCommandsNV pfn_CmdExecuteGeneratedCommandsNV;
    PFN_vkCmdPreprocessGeneratedCommandsNV pfn_CmdPreprocessGeneratedCommandsNV;
    PFN_vkCmdBindPipelineShaderGroupNV pfn_CmdBindPipelineShaderGroupNV;
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV pfn_GetGeneratedCommandsMemoryRequirementsNV;
    PFN_vkCreateIndirectCommandsLayoutNV pfn_CreateIndirectCommandsLayoutNV;
    PFN_vkDestroyIndirectCommandsLayoutNV pfn_DestroyIndirectCommandsLayoutNV;
public:
    void CmdExecuteGeneratedCommandsNV(CommandBuffer commandBuffer,
        Bool32 isPreprocessed,
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return pfn_CmdExecuteGeneratedCommandsNV(commandBuffer.get(),
            isPreprocessed,
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdPreprocessGeneratedCommandsNV(CommandBuffer commandBuffer,
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return pfn_CmdPreprocessGeneratedCommandsNV(commandBuffer.get(),
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdBindPipelineShaderGroupNV(CommandBuffer commandBuffer,
        PipelineBindPoint pipelineBindPoint,
        Pipeline pipeline,
        uint32_t groupIndex) {
        return pfn_CmdBindPipelineShaderGroupNV(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get(),
            groupIndex);
    }
    void GetGeneratedCommandsMemoryRequirementsNV(Device device,
        const GeneratedCommandsMemoryRequirementsInfoNV&  pInfo,
        MemoryRequirements2&  pMemoryRequirements) {
        return pfn_GetGeneratedCommandsMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
    }
    [[nodiscard]] Result CreateIndirectCommandsLayoutNV(Device device,
        const IndirectCommandsLayoutCreateInfoNV&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        IndirectCommandsLayoutNV&  pIndirectCommandsLayout) {
        return static_cast<Result>(pfn_CreateIndirectCommandsLayoutNV(device.get(),
            reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkIndirectCommandsLayoutNV*>(&pIndirectCommandsLayout)));
    }
    void DestroyIndirectCommandsLayoutNV(Device device,
        IndirectCommandsLayoutNV indirectCommandsLayout,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyIndirectCommandsLayoutNV(device.get(),
            indirectCommandsLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    VK_NV_device_generated_commands_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CmdExecuteGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdExecuteGeneratedCommandsNV>(get_device_proc_addr(device.get(),"vkCmdExecuteGeneratedCommandsNV"));
        pfn_CmdPreprocessGeneratedCommandsNV = reinterpret_cast<PFN_vkCmdPreprocessGeneratedCommandsNV>(get_device_proc_addr(device.get(),"vkCmdPreprocessGeneratedCommandsNV"));
        pfn_CmdBindPipelineShaderGroupNV = reinterpret_cast<PFN_vkCmdBindPipelineShaderGroupNV>(get_device_proc_addr(device.get(),"vkCmdBindPipelineShaderGroupNV"));
        pfn_GetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<PFN_vkGetGeneratedCommandsMemoryRequirementsNV>(get_device_proc_addr(device.get(),"vkGetGeneratedCommandsMemoryRequirementsNV"));
        pfn_CreateIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkCreateIndirectCommandsLayoutNV>(get_device_proc_addr(device.get(),"vkCreateIndirectCommandsLayoutNV"));
        pfn_DestroyIndirectCommandsLayoutNV = reinterpret_cast<PFN_vkDestroyIndirectCommandsLayoutNV>(get_device_proc_addr(device.get(),"vkDestroyIndirectCommandsLayoutNV"));
    };
};
#endif //defined(VK_NV_device_generated_commands)
#if defined(VK_EXT_private_data)
struct VK_EXT_private_data_dispatch_table {
    PFN_vkCreatePrivateDataSlotEXT pfn_CreatePrivateDataSlotEXT;
    PFN_vkDestroyPrivateDataSlotEXT pfn_DestroyPrivateDataSlotEXT;
    PFN_vkSetPrivateDataEXT pfn_SetPrivateDataEXT;
    PFN_vkGetPrivateDataEXT pfn_GetPrivateDataEXT;
public:
    [[nodiscard]] Result CreatePrivateDataSlotEXT(Device device,
        const PrivateDataSlotCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        PrivateDataSlotEXT&  pPrivateDataSlot) {
        return static_cast<Result>(pfn_CreatePrivateDataSlotEXT(device.get(),
            reinterpret_cast<const VkPrivateDataSlotCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPrivateDataSlotEXT*>(&pPrivateDataSlot)));
    }
    void DestroyPrivateDataSlotEXT(Device device,
        PrivateDataSlotEXT privateDataSlot,
        const AllocationCallbacks* pAllocator) {
        return pfn_DestroyPrivateDataSlotEXT(device.get(),
            privateDataSlot.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result SetPrivateDataEXT(Device device,
        ObjectType objectType,
        uint64_t objectHandle,
        PrivateDataSlotEXT privateDataSlot,
        uint64_t data) {
        return static_cast<Result>(pfn_SetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            data));
    }
    void GetPrivateDataEXT(Device device,
        ObjectType objectType,
        uint64_t objectHandle,
        PrivateDataSlotEXT privateDataSlot,
        uint64_t&  pData) {
        return pfn_GetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            &pData);
    }
    VK_EXT_private_data_dispatch_table(PFN_vkGetDeviceProcAddr get_device_proc_addr, Device device) {
        pfn_CreatePrivateDataSlotEXT = reinterpret_cast<PFN_vkCreatePrivateDataSlotEXT>(get_device_proc_addr(device.get(),"vkCreatePrivateDataSlotEXT"));
        pfn_DestroyPrivateDataSlotEXT = reinterpret_cast<PFN_vkDestroyPrivateDataSlotEXT>(get_device_proc_addr(device.get(),"vkDestroyPrivateDataSlotEXT"));
        pfn_SetPrivateDataEXT = reinterpret_cast<PFN_vkSetPrivateDataEXT>(get_device_proc_addr(device.get(),"vkSetPrivateDataEXT"));
        pfn_GetPrivateDataEXT = reinterpret_cast<PFN_vkGetPrivateDataEXT>(get_device_proc_addr(device.get(),"vkGetPrivateDataEXT"));
    };
};
#endif //defined(VK_EXT_private_data)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
struct VK_EXT_directfb_surface_dispatch_table {
    PFN_vkCreateDirectFBSurfaceEXT pfn_CreateDirectFBSurfaceEXT;
    PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT;
public:
    [[nodiscard]] Result CreateDirectFBSurfaceEXT(Instance instance,
        const DirectFBSurfaceCreateInfoEXT&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        SurfaceKHR&  pSurface) {
        return static_cast<Result>(pfn_CreateDirectFBSurfaceEXT(instance.get(),
            reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceDirectFBPresentationSupportEXT(PhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex,
        IDirectFB&  dfb) {
        return pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<IDirectFB*>(&dfb));
    }
    VK_EXT_directfb_surface_dispatch_table(PFN_vkGetInstanceProcAddr get_instance_proc_addr, Instance instance) {
        pfn_CreateDirectFBSurfaceEXT = reinterpret_cast<PFN_vkCreateDirectFBSurfaceEXT>(get_instance_proc_addr(instance.get(),"vkCreateDirectFBSurfaceEXT"));
        pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
    };
};
#endif //defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
struct PhysicalDeviceFunctions {
    InstanceFunctions const* instance_functions;
    PhysicalDevice const physicaldevice;
    PhysicalDeviceFunctions(InstanceFunctions const& instance_functions, PhysicalDevice const physicaldevice)
        :instance_functions(&instance_functions), physicaldevice(physicaldevice){}
    void GetProperties(PhysicalDeviceProperties&  pProperties) {
        return instance_functions->pfn_GetPhysicalDeviceProperties(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties*>(&pProperties));
    }
    void GetQueueFamilyProperties(uint32_t&  pQueueFamilyPropertyCount,
        QueueFamilyProperties* pQueueFamilyProperties) {
        return instance_functions->pfn_GetPhysicalDeviceQueueFamilyProperties(physicaldevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties*>(pQueueFamilyProperties));
    }
    void GetMemoryProperties(PhysicalDeviceMemoryProperties&  pMemoryProperties) {
        return instance_functions->pfn_GetPhysicalDeviceMemoryProperties(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties*>(&pMemoryProperties));
    }
    void GetFeatures(PhysicalDeviceFeatures&  pFeatures) {
        return instance_functions->pfn_GetPhysicalDeviceFeatures(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures*>(&pFeatures));
    }
    void GetFormatProperties(Format format,
        FormatProperties&  pFormatProperties) {
        return instance_functions->pfn_GetPhysicalDeviceFormatProperties(physicaldevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties*>(&pFormatProperties));
    }
    [[nodiscard]] Result GetImageFormatProperties(Format format,
        ImageType type,
        ImageTiling tiling,
        ImageUsageFlags usage,
        ImageCreateFlags flags,
        ImageFormatProperties&  pImageFormatProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceImageFormatProperties(physicaldevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            reinterpret_cast<VkImageFormatProperties*>(&pImageFormatProperties)));
    }
    [[nodiscard]] Result CreateDevice(const DeviceCreateInfo&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        Device&  pDevice) {
        return static_cast<Result>(instance_functions->pfn_CreateDevice(physicaldevice.get(),
            reinterpret_cast<const VkDeviceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDevice*>(&pDevice)));
    }
    [[nodiscard]] Result EnumerateDeviceLayerProperties(uint32_t&  pPropertyCount,
        LayerProperties* pProperties) {
        return static_cast<Result>(instance_functions->pfn_EnumerateDeviceLayerProperties(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkLayerProperties*>(pProperties)));
    }
    [[nodiscard]] Result EnumerateDeviceExtensionProperties(const char* pLayerName,
        uint32_t&  pPropertyCount,
        ExtensionProperties* pProperties) {
        return static_cast<Result>(instance_functions->pfn_EnumerateDeviceExtensionProperties(physicaldevice.get(),
            pLayerName,
            &pPropertyCount,
            reinterpret_cast<VkExtensionProperties*>(pProperties)));
    }
    void GetSparseImageFormatProperties(Format format,
        ImageType type,
        SampleCountFlagBits samples,
        ImageUsageFlags usage,
        ImageTiling tiling,
        uint32_t&  pPropertyCount,
        SparseImageFormatProperties* pProperties) {
        return instance_functions->pfn_GetPhysicalDeviceSparseImageFormatProperties(physicaldevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkSampleCountFlagBits>(samples),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageTiling>(tiling),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties*>(pProperties));
    }
    [[nodiscard]] Result GetDisplayPropertiesKHR(uint32_t&  pPropertyCount,
        DisplayPropertiesKHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlanePropertiesKHR(uint32_t&  pPropertyCount,
        DisplayPlanePropertiesKHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlanePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneSupportedDisplaysKHR(uint32_t planeIndex,
        uint32_t&  pDisplayCount,
        DisplayKHR* pDisplays) {
        return static_cast<Result>(instance_functions->pfn_GetDisplayPlaneSupportedDisplaysKHR(physicaldevice.get(),
            planeIndex,
            &pDisplayCount,
            reinterpret_cast<VkDisplayKHR*>(pDisplays)));
    }
    [[nodiscard]] Result GetDisplayModePropertiesKHR(DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModePropertiesKHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetDisplayModePropertiesKHR(physicaldevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModePropertiesKHR*>(pProperties)));
    }
    [[nodiscard]] Result CreateDisplayModeKHR(DisplayKHR display,
        const DisplayModeCreateInfoKHR&  pCreateInfo,
        const AllocationCallbacks* pAllocator,
        DisplayModeKHR&  pMode) {
        return static_cast<Result>(instance_functions->pfn_CreateDisplayModeKHR(physicaldevice.get(),
            display.get(),
            reinterpret_cast<const VkDisplayModeCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDisplayModeKHR*>(&pMode)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilitiesKHR(DisplayModeKHR mode,
        uint32_t planeIndex,
        DisplayPlaneCapabilitiesKHR&  pCapabilities) {
        return static_cast<Result>(instance_functions->pfn_GetDisplayPlaneCapabilitiesKHR(physicaldevice.get(),
            mode.get(),
            planeIndex,
            reinterpret_cast<VkDisplayPlaneCapabilitiesKHR*>(&pCapabilities)));
    }
    [[nodiscard]] Result GetSurfaceSupportKHR(uint32_t queueFamilyIndex,
        SurfaceKHR surface,
        Bool32&  pSupported) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceSupportKHR(physicaldevice.get(),
            queueFamilyIndex,
            surface.get(),
            &pSupported));
    }
    [[nodiscard]] Result GetSurfaceCapabilitiesKHR(SurfaceKHR surface,
        SurfaceCapabilitiesKHR&  pSurfaceCapabilities) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR(physicaldevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetSurfaceFormatsKHR(SurfaceKHR surface,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormatKHR* pSurfaceFormats) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicaldevice.get(),
            surface.get(),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormatKHR*>(pSurfaceFormats)));
    }
    [[nodiscard]] Result GetSurfacePresentModesKHR(SurfaceKHR surface,
        uint32_t&  pPresentModeCount,
        PresentModeKHR* pPresentModes) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicaldevice.get(),
            surface.get(),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes)));
    }
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    [[nodiscard]] VkBool32 GetWaylandPresentationSupportKHR(uint32_t queueFamilyIndex,
        wl_display&  display) {
        return instance_functions->pfn_GetPhysicalDeviceWaylandPresentationSupportKHR(physicaldevice.get(),
            queueFamilyIndex,
            reinterpret_cast<wl_display*>(&display));
    }
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] VkBool32 GetWin32PresentationSupportKHR(uint32_t queueFamilyIndex) {
        return instance_functions->pfn_GetPhysicalDeviceWin32PresentationSupportKHR(physicaldevice.get(),
            queueFamilyIndex);
    }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    [[nodiscard]] VkBool32 GetXlibPresentationSupportKHR(uint32_t queueFamilyIndex,
        Display&  dpy,
        VisualID visualID) {
        return instance_functions->pfn_GetPhysicalDeviceXlibPresentationSupportKHR(physicaldevice.get(),
            queueFamilyIndex,
            reinterpret_cast<Display*>(&dpy),
            static_cast<VisualID>(visualID));
    }
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    [[nodiscard]] VkBool32 GetXcbPresentationSupportKHR(uint32_t queueFamilyIndex,
        xcb_connection_t&  connection,
        xcb_visualid_t visual_id) {
        return instance_functions->pfn_GetPhysicalDeviceXcbPresentationSupportKHR(physicaldevice.get(),
            queueFamilyIndex,
            reinterpret_cast<xcb_connection_t*>(&connection),
            static_cast<xcb_visualid_t>(visual_id));
    }
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] VkBool32 GetDirectFBPresentationSupportEXT(uint32_t queueFamilyIndex,
        IDirectFB&  dfb) {
        return instance_functions->pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT(physicaldevice.get(),
            queueFamilyIndex,
            reinterpret_cast<IDirectFB*>(&dfb));
    }
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] Result GetExternalImageFormatPropertiesNV(Format format,
        ImageType type,
        ImageTiling tiling,
        ImageUsageFlags usage,
        ImageCreateFlags flags,
        ExternalMemoryHandleTypeFlagsNV externalHandleType,
        ExternalImageFormatPropertiesNV&  pExternalImageFormatProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV(physicaldevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(externalHandleType),
            reinterpret_cast<VkExternalImageFormatPropertiesNV*>(&pExternalImageFormatProperties)));
    }
    void GetFeatures2(PhysicalDeviceFeatures2&  pFeatures) {
        return instance_functions->pfn_GetPhysicalDeviceFeatures2(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures2*>(&pFeatures));
    }
    void GetProperties2(PhysicalDeviceProperties2&  pProperties) {
        return instance_functions->pfn_GetPhysicalDeviceProperties2(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties2*>(&pProperties));
    }
    void GetFormatProperties2(Format format,
        FormatProperties2&  pFormatProperties) {
        return instance_functions->pfn_GetPhysicalDeviceFormatProperties2(physicaldevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties2*>(&pFormatProperties));
    }
    [[nodiscard]] Result GetImageFormatProperties2(const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo,
        ImageFormatProperties2&  pImageFormatProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceImageFormatProperties2(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2*>(&pImageFormatInfo),
            reinterpret_cast<VkImageFormatProperties2*>(&pImageFormatProperties)));
    }
    void GetQueueFamilyProperties2(uint32_t&  pQueueFamilyPropertyCount,
        QueueFamilyProperties2* pQueueFamilyProperties) {
        return instance_functions->pfn_GetPhysicalDeviceQueueFamilyProperties2(physicaldevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties2*>(pQueueFamilyProperties));
    }
    void GetMemoryProperties2(PhysicalDeviceMemoryProperties2&  pMemoryProperties) {
        return instance_functions->pfn_GetPhysicalDeviceMemoryProperties2(physicaldevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties2*>(&pMemoryProperties));
    }
    void GetSparseImageFormatProperties2(const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo,
        uint32_t&  pPropertyCount,
        SparseImageFormatProperties2* pProperties) {
        return instance_functions->pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2*>(&pFormatInfo),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties2*>(pProperties));
    }
    void GetExternalBufferProperties(const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo,
        ExternalBufferProperties&  pExternalBufferProperties) {
        return instance_functions->pfn_GetPhysicalDeviceExternalBufferProperties(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo*>(&pExternalBufferInfo),
            reinterpret_cast<VkExternalBufferProperties*>(&pExternalBufferProperties));
    }
    void GetExternalSemaphoreProperties(const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo,
        ExternalSemaphoreProperties&  pExternalSemaphoreProperties) {
        return instance_functions->pfn_GetPhysicalDeviceExternalSemaphoreProperties(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo*>(&pExternalSemaphoreInfo),
            reinterpret_cast<VkExternalSemaphoreProperties*>(&pExternalSemaphoreProperties));
    }
    void GetExternalFenceProperties(const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo,
        ExternalFenceProperties&  pExternalFenceProperties) {
        return instance_functions->pfn_GetPhysicalDeviceExternalFenceProperties(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo*>(&pExternalFenceInfo),
            reinterpret_cast<VkExternalFenceProperties*>(&pExternalFenceProperties));
    }
    [[nodiscard]] Result ReleaseDisplayEXT(DisplayKHR display) {
        return static_cast<Result>(instance_functions->pfn_ReleaseDisplayEXT(physicaldevice.get(),
            display.get()));
    }
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] Result AcquireXlibDisplayEXT(Display&  dpy,
        DisplayKHR display) {
        return static_cast<Result>(instance_functions->pfn_AcquireXlibDisplayEXT(physicaldevice.get(),
            reinterpret_cast<Display*>(&dpy),
            display.get()));
    }
    [[nodiscard]] Result GetRandROutputDisplayEXT(Display&  dpy,
        RROutput rrOutput,
        DisplayKHR&  pDisplay) {
        return static_cast<Result>(instance_functions->pfn_GetRandROutputDisplayEXT(physicaldevice.get(),
            reinterpret_cast<Display*>(&dpy),
            static_cast<RROutput>(rrOutput),
            reinterpret_cast<VkDisplayKHR*>(&pDisplay)));
    }
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] Result GetSurfaceCapabilities2EXT(SurfaceKHR surface,
        SurfaceCapabilities2EXT&  pSurfaceCapabilities) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceCapabilities2EXT(physicaldevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilities2EXT*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetPresentRectanglesKHR(SurfaceKHR surface,
        uint32_t&  pRectCount,
        Rect2D* pRects) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDevicePresentRectanglesKHR(physicaldevice.get(),
            surface.get(),
            &pRectCount,
            reinterpret_cast<VkRect2D*>(pRects)));
    }
    void GetMultisamplePropertiesEXT(SampleCountFlagBits samples,
        MultisamplePropertiesEXT&  pMultisampleProperties) {
        return instance_functions->pfn_GetPhysicalDeviceMultisamplePropertiesEXT(physicaldevice.get(),
            static_cast<VkSampleCountFlagBits>(samples),
            reinterpret_cast<VkMultisamplePropertiesEXT*>(&pMultisampleProperties));
    }
    [[nodiscard]] Result GetSurfaceCapabilities2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        SurfaceCapabilities2KHR&  pSurfaceCapabilities) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceCapabilities2KHR(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkSurfaceCapabilities2KHR*>(&pSurfaceCapabilities)));
    }
    [[nodiscard]] Result GetSurfaceFormats2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        uint32_t&  pSurfaceFormatCount,
        SurfaceFormat2KHR* pSurfaceFormats) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormat2KHR*>(pSurfaceFormats)));
    }
    [[nodiscard]] Result GetDisplayProperties2KHR(uint32_t&  pPropertyCount,
        DisplayProperties2KHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceDisplayProperties2KHR(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneProperties2KHR(uint32_t&  pPropertyCount,
        DisplayPlaneProperties2KHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlaneProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayModeProperties2KHR(DisplayKHR display,
        uint32_t&  pPropertyCount,
        DisplayModeProperties2KHR* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetDisplayModeProperties2KHR(physicaldevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModeProperties2KHR*>(pProperties)));
    }
    [[nodiscard]] Result GetDisplayPlaneCapabilities2KHR(const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo,
        DisplayPlaneCapabilities2KHR&  pCapabilities) {
        return static_cast<Result>(instance_functions->pfn_GetDisplayPlaneCapabilities2KHR(physicaldevice.get(),
            reinterpret_cast<const VkDisplayPlaneInfo2KHR*>(&pDisplayPlaneInfo),
            reinterpret_cast<VkDisplayPlaneCapabilities2KHR*>(&pCapabilities)));
    }
    [[nodiscard]] Result GetCalibrateableTimeDomainsEXT(uint32_t&  pTimeDomainCount,
        TimeDomainEXT* pTimeDomains) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicaldevice.get(),
            &pTimeDomainCount,
            reinterpret_cast<VkTimeDomainEXT*>(pTimeDomains)));
    }
    [[nodiscard]] Result GetCooperativeMatrixPropertiesNV(uint32_t&  pPropertyCount,
        CooperativeMatrixPropertiesNV* pProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicaldevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkCooperativeMatrixPropertiesNV*>(pProperties)));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result GetSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo,
        uint32_t&  pPresentModeCount,
        PresentModeKHR* pPresentModes) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicaldevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes)));
    }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(uint32_t queueFamilyIndex,
        uint32_t&  pCounterCount,
        PerformanceCounterKHR* pCounters,
        PerformanceCounterDescriptionKHR* pCounterDescriptions) {
        return static_cast<Result>(instance_functions->pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicaldevice.get(),
            queueFamilyIndex,
            &pCounterCount,
            reinterpret_cast<VkPerformanceCounterKHR*>(pCounters),
            reinterpret_cast<VkPerformanceCounterDescriptionKHR*>(pCounterDescriptions)));
    }
    void GetQueueFamilyPerformanceQueryPassesKHR(const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo,
        uint32_t&  pNumPasses) {
        return instance_functions->pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicaldevice.get(),
            reinterpret_cast<const VkQueryPoolPerformanceCreateInfoKHR*>(&pPerformanceQueryCreateInfo),
            &pNumPasses);
    }
    [[nodiscard]] Result GetSupportedFramebufferMixedSamplesCombinationsNV(uint32_t&  pCombinationCount,
        FramebufferMixedSamplesCombinationNV* pCombinations) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicaldevice.get(),
            &pCombinationCount,
            reinterpret_cast<VkFramebufferMixedSamplesCombinationNV*>(pCombinations)));
    }
    [[nodiscard]] Result GetToolPropertiesEXT(uint32_t&  pToolCount,
        PhysicalDeviceToolPropertiesEXT* pToolProperties) {
        return static_cast<Result>(instance_functions->pfn_GetPhysicalDeviceToolPropertiesEXT(physicaldevice.get(),
            &pToolCount,
            reinterpret_cast<VkPhysicalDeviceToolPropertiesEXT*>(pToolProperties)));
    }
};
struct QueueFunctions {
    DeviceFunctions const* device_functions;
    Queue const queue;
    QueueFunctions(DeviceFunctions const& device_functions, Queue const queue)
        :device_functions(&device_functions), queue(queue){}
    [[nodiscard]] Result Submit(uint32_t submitCount,
        const SubmitInfo* pSubmits,
        Fence fence) {
        return static_cast<Result>(device_functions->pfn_QueueSubmit(queue.get(),
            submitCount,
            reinterpret_cast<const VkSubmitInfo*>(pSubmits),
            fence.get()));
    }
    [[nodiscard]] Result WaitIdle() {
        return static_cast<Result>(device_functions->pfn_QueueWaitIdle(queue.get()));
    }
    [[nodiscard]] Result BindSparse(uint32_t bindInfoCount,
        const BindSparseInfo* pBindInfo,
        Fence fence) {
        return static_cast<Result>(device_functions->pfn_QueueBindSparse(queue.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindSparseInfo*>(pBindInfo),
            fence.get()));
    }
    [[nodiscard]] Result PresentKHR(const PresentInfoKHR&  pPresentInfo) {
        return static_cast<Result>(device_functions->pfn_QueuePresentKHR(queue.get(),
            reinterpret_cast<const VkPresentInfoKHR*>(&pPresentInfo)));
    }
    void BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) {
        return device_functions->pfn_QueueBeginDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void EndDebugUtilsLabelEXT() {
        return device_functions->pfn_QueueEndDebugUtilsLabelEXT(queue.get());
    }
    void InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) {
        return device_functions->pfn_QueueInsertDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void GetCheckpointDataNV(uint32_t&  pCheckpointDataCount,
        CheckpointDataNV* pCheckpointData) {
        return device_functions->pfn_GetQueueCheckpointDataNV(queue.get(),
            &pCheckpointDataCount,
            reinterpret_cast<VkCheckpointDataNV*>(pCheckpointData));
    }
    [[nodiscard]] Result SetPerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) {
        return static_cast<Result>(device_functions->pfn_QueueSetPerformanceConfigurationINTEL(queue.get(),
            configuration.get()));
    }
};
struct CommandBufferFunctions {
    DeviceFunctions const* device_functions;
    CommandBuffer const commandbuffer;
    CommandBufferFunctions(DeviceFunctions const& device_functions, CommandBuffer const commandbuffer)
        :device_functions(&device_functions), commandbuffer(commandbuffer){}
    [[nodiscard]] Result Begin(const CommandBufferBeginInfo&  pBeginInfo) {
        return static_cast<Result>(device_functions->pfn_BeginCommandBuffer(commandbuffer.get(),
            reinterpret_cast<const VkCommandBufferBeginInfo*>(&pBeginInfo)));
    }
    [[nodiscard]] Result End() {
        return static_cast<Result>(device_functions->pfn_EndCommandBuffer(commandbuffer.get()));
    }
    [[nodiscard]] Result Reset(CommandBufferResetFlags flags) {
        return static_cast<Result>(device_functions->pfn_ResetCommandBuffer(commandbuffer.get(),
            static_cast<VkCommandBufferResetFlags>(flags)));
    }
    void BindPipeline(PipelineBindPoint pipelineBindPoint,
        Pipeline pipeline) {
        return device_functions->pfn_CmdBindPipeline(commandbuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get());
    }
    void SetViewport(uint32_t firstViewport,
        uint32_t viewportCount,
        const Viewport* pViewports) {
        return device_functions->pfn_CmdSetViewport(commandbuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void SetScissor(uint32_t firstScissor,
        uint32_t scissorCount,
        const Rect2D* pScissors) {
        return device_functions->pfn_CmdSetScissor(commandbuffer.get(),
            firstScissor,
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void SetLineWidth(float lineWidth) {
        return device_functions->pfn_CmdSetLineWidth(commandbuffer.get(),
            lineWidth);
    }
    void SetDepthBias(float depthBiasConstantFactor,
        float depthBiasClamp,
        float depthBiasSlopeFactor) {
        return device_functions->pfn_CmdSetDepthBias(commandbuffer.get(),
            depthBiasConstantFactor,
            depthBiasClamp,
            depthBiasSlopeFactor);
    }
    void SetBlendConstants(const float blendConstants[4]) {
        return device_functions->pfn_CmdSetBlendConstants(commandbuffer.get(),
            blendConstants);
    }
    void SetDepthBounds(float minDepthBounds,
        float maxDepthBounds) {
        return device_functions->pfn_CmdSetDepthBounds(commandbuffer.get(),
            minDepthBounds,
            maxDepthBounds);
    }
    void SetStencilCompareMask(StencilFaceFlags faceMask,
        uint32_t compareMask) {
        return device_functions->pfn_CmdSetStencilCompareMask(commandbuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            compareMask);
    }
    void SetStencilWriteMask(StencilFaceFlags faceMask,
        uint32_t writeMask) {
        return device_functions->pfn_CmdSetStencilWriteMask(commandbuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            writeMask);
    }
    void SetStencilReference(StencilFaceFlags faceMask,
        uint32_t reference) {
        return device_functions->pfn_CmdSetStencilReference(commandbuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            reference);
    }
    void BindDescriptorSets(PipelineBindPoint pipelineBindPoint,
        PipelineLayout layout,
        uint32_t firstSet,
        uint32_t descriptorSetCount,
        const DescriptorSet* pDescriptorSets,
        uint32_t dynamicOffsetCount,
        const uint32_t* pDynamicOffsets) {
        return device_functions->pfn_CmdBindDescriptorSets(commandbuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            layout.get(),
            firstSet,
            descriptorSetCount,
            reinterpret_cast<const VkDescriptorSet*>(pDescriptorSets),
            dynamicOffsetCount,
            pDynamicOffsets);
    }
    void BindIndexBuffer(Buffer buffer,
        DeviceSize offset,
        IndexType indexType) {
        return device_functions->pfn_CmdBindIndexBuffer(commandbuffer.get(),
            buffer.get(),
            offset,
            static_cast<VkIndexType>(indexType));
    }
    void BindVertexBuffers(uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets) {
        return device_functions->pfn_CmdBindVertexBuffers(commandbuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets);
    }
    void Draw(uint32_t vertexCount,
        uint32_t instanceCount,
        uint32_t firstVertex,
        uint32_t firstInstance) {
        return device_functions->pfn_CmdDraw(commandbuffer.get(),
            vertexCount,
            instanceCount,
            firstVertex,
            firstInstance);
    }
    void DrawIndexed(uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t firstInstance) {
        return device_functions->pfn_CmdDrawIndexed(commandbuffer.get(),
            indexCount,
            instanceCount,
            firstIndex,
            vertexOffset,
            firstInstance);
    }
    void DrawIndirect(Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawIndirect(commandbuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void DrawIndexedIndirect(Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawIndexedIndirect(commandbuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void Dispatch(uint32_t groupCountX,
        uint32_t groupCountY,
        uint32_t groupCountZ) {
        return device_functions->pfn_CmdDispatch(commandbuffer.get(),
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    void DispatchIndirect(Buffer buffer,
        DeviceSize offset) {
        return device_functions->pfn_CmdDispatchIndirect(commandbuffer.get(),
            buffer.get(),
            offset);
    }
    void CopyBuffer(Buffer srcBuffer,
        Buffer dstBuffer,
        uint32_t regionCount,
        const BufferCopy* pRegions) {
        return device_functions->pfn_CmdCopyBuffer(commandbuffer.get(),
            srcBuffer.get(),
            dstBuffer.get(),
            regionCount,
            reinterpret_cast<const VkBufferCopy*>(pRegions));
    }
    void CopyImage(Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageCopy* pRegions) {
        return device_functions->pfn_CmdCopyImage(commandbuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageCopy*>(pRegions));
    }
    void BlitImage(Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageBlit* pRegions,
        Filter filter) {
        return device_functions->pfn_CmdBlitImage(commandbuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageBlit*>(pRegions),
            static_cast<VkFilter>(filter));
    }
    void CopyBufferToImage(Buffer srcBuffer,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const BufferImageCopy* pRegions) {
        return device_functions->pfn_CmdCopyBufferToImage(commandbuffer.get(),
            srcBuffer.get(),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkBufferImageCopy*>(pRegions));
    }
    void CopyImageToBuffer(Image srcImage,
        ImageLayout srcImageLayout,
        Buffer dstBuffer,
        uint32_t regionCount,
        const BufferImageCopy* pRegions) {
        return device_functions->pfn_CmdCopyImageToBuffer(commandbuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstBuffer.get(),
            regionCount,
            reinterpret_cast<const VkBufferImageCopy*>(pRegions));
    }
    void UpdateBuffer(Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize dataSize,
        const void* pData) {
        return device_functions->pfn_CmdUpdateBuffer(commandbuffer.get(),
            dstBuffer.get(),
            dstOffset,
            dataSize,
            reinterpret_cast<const void*>(pData));
    }
    void FillBuffer(Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize size,
        uint32_t data) {
        return device_functions->pfn_CmdFillBuffer(commandbuffer.get(),
            dstBuffer.get(),
            dstOffset,
            size,
            data);
    }
    void ClearColorImage(Image image,
        ImageLayout imageLayout,
        const ClearColorValue&  pColor,
        uint32_t rangeCount,
        const ImageSubresourceRange* pRanges) {
        return device_functions->pfn_CmdClearColorImage(commandbuffer.get(),
            image.get(),
            static_cast<VkImageLayout>(imageLayout),
            reinterpret_cast<const VkClearColorValue*>(&pColor),
            rangeCount,
            reinterpret_cast<const VkImageSubresourceRange*>(pRanges));
    }
    void ClearDepthStencilImage(Image image,
        ImageLayout imageLayout,
        const ClearDepthStencilValue&  pDepthStencil,
        uint32_t rangeCount,
        const ImageSubresourceRange* pRanges) {
        return device_functions->pfn_CmdClearDepthStencilImage(commandbuffer.get(),
            image.get(),
            static_cast<VkImageLayout>(imageLayout),
            reinterpret_cast<const VkClearDepthStencilValue*>(&pDepthStencil),
            rangeCount,
            reinterpret_cast<const VkImageSubresourceRange*>(pRanges));
    }
    void ClearAttachments(uint32_t attachmentCount,
        const ClearAttachment* pAttachments,
        uint32_t rectCount,
        const ClearRect* pRects) {
        return device_functions->pfn_CmdClearAttachments(commandbuffer.get(),
            attachmentCount,
            reinterpret_cast<const VkClearAttachment*>(pAttachments),
            rectCount,
            reinterpret_cast<const VkClearRect*>(pRects));
    }
    void ResolveImage(Image srcImage,
        ImageLayout srcImageLayout,
        Image dstImage,
        ImageLayout dstImageLayout,
        uint32_t regionCount,
        const ImageResolve* pRegions) {
        return device_functions->pfn_CmdResolveImage(commandbuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageResolve*>(pRegions));
    }
    void SetEvent(Event event,
        PipelineStageFlags stageMask) {
        return device_functions->pfn_CmdSetEvent(commandbuffer.get(),
            event.get(),
            static_cast<VkPipelineStageFlags>(stageMask));
    }
    void ResetEvent(Event event,
        PipelineStageFlags stageMask) {
        return device_functions->pfn_CmdResetEvent(commandbuffer.get(),
            event.get(),
            static_cast<VkPipelineStageFlags>(stageMask));
    }
    void WaitEvents(uint32_t eventCount,
        const Event* pEvents,
        PipelineStageFlags srcStageMask,
        PipelineStageFlags dstStageMask,
        uint32_t memoryBarrierCount,
        const MemoryBarrier* pMemoryBarriers,
        uint32_t bufferMemoryBarrierCount,
        const BufferMemoryBarrier* pBufferMemoryBarriers,
        uint32_t imageMemoryBarrierCount,
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return device_functions->pfn_CmdWaitEvents(commandbuffer.get(),
            eventCount,
            reinterpret_cast<const VkEvent*>(pEvents),
            static_cast<VkPipelineStageFlags>(srcStageMask),
            static_cast<VkPipelineStageFlags>(dstStageMask),
            memoryBarrierCount,
            reinterpret_cast<const VkMemoryBarrier*>(pMemoryBarriers),
            bufferMemoryBarrierCount,
            reinterpret_cast<const VkBufferMemoryBarrier*>(pBufferMemoryBarriers),
            imageMemoryBarrierCount,
            reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void PipelineBarrier(PipelineStageFlags srcStageMask,
        PipelineStageFlags dstStageMask,
        DependencyFlags dependencyFlags,
        uint32_t memoryBarrierCount,
        const MemoryBarrier* pMemoryBarriers,
        uint32_t bufferMemoryBarrierCount,
        const BufferMemoryBarrier* pBufferMemoryBarriers,
        uint32_t imageMemoryBarrierCount,
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return device_functions->pfn_CmdPipelineBarrier(commandbuffer.get(),
            static_cast<VkPipelineStageFlags>(srcStageMask),
            static_cast<VkPipelineStageFlags>(dstStageMask),
            static_cast<VkDependencyFlags>(dependencyFlags),
            memoryBarrierCount,
            reinterpret_cast<const VkMemoryBarrier*>(pMemoryBarriers),
            bufferMemoryBarrierCount,
            reinterpret_cast<const VkBufferMemoryBarrier*>(pBufferMemoryBarriers),
            imageMemoryBarrierCount,
            reinterpret_cast<const VkImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void BeginQuery(QueryPool queryPool,
        uint32_t query,
        QueryControlFlags flags) {
        return device_functions->pfn_CmdBeginQuery(commandbuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags));
    }
    void EndQuery(QueryPool queryPool,
        uint32_t query) {
        return device_functions->pfn_CmdEndQuery(commandbuffer.get(),
            queryPool.get(),
            query);
    }
    void BeginConditionalRenderingEXT(const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) {
        return device_functions->pfn_CmdBeginConditionalRenderingEXT(commandbuffer.get(),
            reinterpret_cast<const VkConditionalRenderingBeginInfoEXT*>(&pConditionalRenderingBegin));
    }
    void EndConditionalRenderingEXT() {
        return device_functions->pfn_CmdEndConditionalRenderingEXT(commandbuffer.get());
    }
    void ResetQueryPool(QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount) {
        return device_functions->pfn_CmdResetQueryPool(commandbuffer.get(),
            queryPool.get(),
            firstQuery,
            queryCount);
    }
    void WriteTimestamp(PipelineStageFlagBits pipelineStage,
        QueryPool queryPool,
        uint32_t query) {
        return device_functions->pfn_CmdWriteTimestamp(commandbuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            queryPool.get(),
            query);
    }
    void CopyQueryPoolResults(QueryPool queryPool,
        uint32_t firstQuery,
        uint32_t queryCount,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        DeviceSize stride,
        QueryResultFlags flags) {
        return device_functions->pfn_CmdCopyQueryPoolResults(commandbuffer.get(),
            queryPool.get(),
            firstQuery,
            queryCount,
            dstBuffer.get(),
            dstOffset,
            stride,
            static_cast<VkQueryResultFlags>(flags));
    }
    void PushConstants(PipelineLayout layout,
        ShaderStageFlags stageFlags,
        uint32_t offset,
        uint32_t size,
        const void* pValues) {
        return device_functions->pfn_CmdPushConstants(commandbuffer.get(),
            layout.get(),
            static_cast<VkShaderStageFlags>(stageFlags),
            offset,
            size,
            reinterpret_cast<const void*>(pValues));
    }
    void BeginRenderPass(const RenderPassBeginInfo&  pRenderPassBegin,
        SubpassContents contents) {
        return device_functions->pfn_CmdBeginRenderPass(commandbuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            static_cast<VkSubpassContents>(contents));
    }
    void NextSubpass(SubpassContents contents) {
        return device_functions->pfn_CmdNextSubpass(commandbuffer.get(),
            static_cast<VkSubpassContents>(contents));
    }
    void EndRenderPass() {
        return device_functions->pfn_CmdEndRenderPass(commandbuffer.get());
    }
    void ExecuteCommands(uint32_t commandBufferCount,
        const CommandBuffer* pCommandBuffers) {
        return device_functions->pfn_CmdExecuteCommands(commandbuffer.get(),
            commandBufferCount,
            reinterpret_cast<const VkCommandBuffer*>(pCommandBuffers));
    }
    void DebugMarkerBeginEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return device_functions->pfn_CmdDebugMarkerBeginEXT(commandbuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    void DebugMarkerEndEXT() {
        return device_functions->pfn_CmdDebugMarkerEndEXT(commandbuffer.get());
    }
    void DebugMarkerInsertEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) {
        return device_functions->pfn_CmdDebugMarkerInsertEXT(commandbuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    void ExecuteGeneratedCommandsNV(Bool32 isPreprocessed,
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return device_functions->pfn_CmdExecuteGeneratedCommandsNV(commandbuffer.get(),
            isPreprocessed,
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void PreprocessGeneratedCommandsNV(const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) {
        return device_functions->pfn_CmdPreprocessGeneratedCommandsNV(commandbuffer.get(),
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void BindPipelineShaderGroupNV(PipelineBindPoint pipelineBindPoint,
        Pipeline pipeline,
        uint32_t groupIndex) {
        return device_functions->pfn_CmdBindPipelineShaderGroupNV(commandbuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get(),
            groupIndex);
    }
    void PushDescriptorSetKHR(PipelineBindPoint pipelineBindPoint,
        PipelineLayout layout,
        uint32_t set,
        uint32_t descriptorWriteCount,
        const WriteDescriptorSet* pDescriptorWrites) {
        return device_functions->pfn_CmdPushDescriptorSetKHR(commandbuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            layout.get(),
            set,
            descriptorWriteCount,
            reinterpret_cast<const VkWriteDescriptorSet*>(pDescriptorWrites));
    }
    void SetDeviceMask(uint32_t deviceMask) {
        return device_functions->pfn_CmdSetDeviceMask(commandbuffer.get(),
            deviceMask);
    }
    void DispatchBase(uint32_t baseGroupX,
        uint32_t baseGroupY,
        uint32_t baseGroupZ,
        uint32_t groupCountX,
        uint32_t groupCountY,
        uint32_t groupCountZ) {
        return device_functions->pfn_CmdDispatchBase(commandbuffer.get(),
            baseGroupX,
            baseGroupY,
            baseGroupZ,
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    void PushDescriptorSetWithTemplateKHR(DescriptorUpdateTemplate descriptorUpdateTemplate,
        PipelineLayout layout,
        uint32_t set,
        const void* pData) {
        return device_functions->pfn_CmdPushDescriptorSetWithTemplateKHR(commandbuffer.get(),
            descriptorUpdateTemplate.get(),
            layout.get(),
            set,
            reinterpret_cast<const void*>(pData));
    }
    void SetViewportWScalingNV(uint32_t firstViewport,
        uint32_t viewportCount,
        const ViewportWScalingNV* pViewportWScalings) {
        return device_functions->pfn_CmdSetViewportWScalingNV(commandbuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewportWScalingNV*>(pViewportWScalings));
    }
    void SetDiscardRectangleEXT(uint32_t firstDiscardRectangle,
        uint32_t discardRectangleCount,
        const Rect2D* pDiscardRectangles) {
        return device_functions->pfn_CmdSetDiscardRectangleEXT(commandbuffer.get(),
            firstDiscardRectangle,
            discardRectangleCount,
            reinterpret_cast<const VkRect2D*>(pDiscardRectangles));
    }
    void SetSampleLocationsEXT(const SampleLocationsInfoEXT&  pSampleLocationsInfo) {
        return device_functions->pfn_CmdSetSampleLocationsEXT(commandbuffer.get(),
            reinterpret_cast<const VkSampleLocationsInfoEXT*>(&pSampleLocationsInfo));
    }
    void BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) {
        return device_functions->pfn_CmdBeginDebugUtilsLabelEXT(commandbuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void EndDebugUtilsLabelEXT() {
        return device_functions->pfn_CmdEndDebugUtilsLabelEXT(commandbuffer.get());
    }
    void InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) {
        return device_functions->pfn_CmdInsertDebugUtilsLabelEXT(commandbuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void WriteBufferMarkerAMD(PipelineStageFlagBits pipelineStage,
        Buffer dstBuffer,
        DeviceSize dstOffset,
        uint32_t marker) {
        return device_functions->pfn_CmdWriteBufferMarkerAMD(commandbuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            dstBuffer.get(),
            dstOffset,
            marker);
    }
    void BeginRenderPass2(const RenderPassBeginInfo&  pRenderPassBegin,
        const SubpassBeginInfo&  pSubpassBeginInfo) {
        return device_functions->pfn_CmdBeginRenderPass2(commandbuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo));
    }
    void NextSubpass2(const SubpassBeginInfo&  pSubpassBeginInfo,
        const SubpassEndInfo&  pSubpassEndInfo) {
        return device_functions->pfn_CmdNextSubpass2(commandbuffer.get(),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void EndRenderPass2(const SubpassEndInfo&  pSubpassEndInfo) {
        return device_functions->pfn_CmdEndRenderPass2(commandbuffer.get(),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void DrawIndirectCount(Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawIndirectCount(commandbuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    void DrawIndexedIndirectCount(Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawIndexedIndirectCount(commandbuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    void SetCheckpointNV(const void* pCheckpointMarker) {
        return device_functions->pfn_CmdSetCheckpointNV(commandbuffer.get(),
            reinterpret_cast<const void*>(pCheckpointMarker));
    }
    void BindTransformFeedbackBuffersEXT(uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes) {
        return device_functions->pfn_CmdBindTransformFeedbackBuffersEXT(commandbuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes);
    }
    void BeginTransformFeedbackEXT(uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return device_functions->pfn_CmdBeginTransformFeedbackEXT(commandbuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void EndTransformFeedbackEXT(uint32_t firstCounterBuffer,
        uint32_t counterBufferCount,
        const Buffer* pCounterBuffers,
        const DeviceSize* pCounterBufferOffsets) {
        return device_functions->pfn_CmdEndTransformFeedbackEXT(commandbuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void BeginQueryIndexedEXT(QueryPool queryPool,
        uint32_t query,
        QueryControlFlags flags,
        uint32_t index) {
        return device_functions->pfn_CmdBeginQueryIndexedEXT(commandbuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags),
            index);
    }
    void EndQueryIndexedEXT(QueryPool queryPool,
        uint32_t query,
        uint32_t index) {
        return device_functions->pfn_CmdEndQueryIndexedEXT(commandbuffer.get(),
            queryPool.get(),
            query,
            index);
    }
    void DrawIndirectByteCountEXT(uint32_t instanceCount,
        uint32_t firstInstance,
        Buffer counterBuffer,
        DeviceSize counterBufferOffset,
        uint32_t counterOffset,
        uint32_t vertexStride) {
        return device_functions->pfn_CmdDrawIndirectByteCountEXT(commandbuffer.get(),
            instanceCount,
            firstInstance,
            counterBuffer.get(),
            counterBufferOffset,
            counterOffset,
            vertexStride);
    }
    void SetExclusiveScissorNV(uint32_t firstExclusiveScissor,
        uint32_t exclusiveScissorCount,
        const Rect2D* pExclusiveScissors) {
        return device_functions->pfn_CmdSetExclusiveScissorNV(commandbuffer.get(),
            firstExclusiveScissor,
            exclusiveScissorCount,
            reinterpret_cast<const VkRect2D*>(pExclusiveScissors));
    }
    void BindShadingRateImageNV(ImageView imageView,
        ImageLayout imageLayout) {
        return device_functions->pfn_CmdBindShadingRateImageNV(commandbuffer.get(),
            imageView.get(),
            static_cast<VkImageLayout>(imageLayout));
    }
    void SetViewportShadingRatePaletteNV(uint32_t firstViewport,
        uint32_t viewportCount,
        const ShadingRatePaletteNV* pShadingRatePalettes) {
        return device_functions->pfn_CmdSetViewportShadingRatePaletteNV(commandbuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkShadingRatePaletteNV*>(pShadingRatePalettes));
    }
    void SetCoarseSampleOrderNV(CoarseSampleOrderTypeNV sampleOrderType,
        uint32_t customSampleOrderCount,
        const CoarseSampleOrderCustomNV* pCustomSampleOrders) {
        return device_functions->pfn_CmdSetCoarseSampleOrderNV(commandbuffer.get(),
            static_cast<VkCoarseSampleOrderTypeNV>(sampleOrderType),
            customSampleOrderCount,
            reinterpret_cast<const VkCoarseSampleOrderCustomNV*>(pCustomSampleOrders));
    }
    void DrawMeshTasksNV(uint32_t taskCount,
        uint32_t firstTask) {
        return device_functions->pfn_CmdDrawMeshTasksNV(commandbuffer.get(),
            taskCount,
            firstTask);
    }
    void DrawMeshTasksIndirectNV(Buffer buffer,
        DeviceSize offset,
        uint32_t drawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawMeshTasksIndirectNV(commandbuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void DrawMeshTasksIndirectCountNV(Buffer buffer,
        DeviceSize offset,
        Buffer countBuffer,
        DeviceSize countBufferOffset,
        uint32_t maxDrawCount,
        uint32_t stride) {
        return device_functions->pfn_CmdDrawMeshTasksIndirectCountNV(commandbuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    void CopyAccelerationStructureNV(AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        CopyAccelerationStructureModeKHR mode) {
        return device_functions->pfn_CmdCopyAccelerationStructureNV(commandbuffer.get(),
            dst.get(),
            src.get(),
            static_cast<VkCopyAccelerationStructureModeKHR>(mode));
    }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) {
        return device_functions->pfn_CmdCopyAccelerationStructureKHR(commandbuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo));
    }
    void CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) {
        return device_functions->pfn_CmdCopyAccelerationStructureToMemoryKHR(commandbuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo));
    }
    void CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) {
        return device_functions->pfn_CmdCopyMemoryToAccelerationStructureKHR(commandbuffer.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo));
    }
    void WriteAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount,
        const AccelerationStructureKHR* pAccelerationStructures,
        QueryType queryType,
        QueryPool queryPool,
        uint32_t firstQuery) {
        return device_functions->pfn_CmdWriteAccelerationStructuresPropertiesKHR(commandbuffer.get(),
            accelerationStructureCount,
            reinterpret_cast<const VkAccelerationStructureKHR*>(pAccelerationStructures),
            static_cast<VkQueryType>(queryType),
            queryPool.get(),
            firstQuery);
    }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    void BuildAccelerationStructureNV(const AccelerationStructureInfoNV&  pInfo,
        Buffer instanceData,
        DeviceSize instanceOffset,
        Bool32 update,
        AccelerationStructureKHR dst,
        AccelerationStructureKHR src,
        Buffer scratch,
        DeviceSize scratchOffset) {
        return device_functions->pfn_CmdBuildAccelerationStructureNV(commandbuffer.get(),
            reinterpret_cast<const VkAccelerationStructureInfoNV*>(&pInfo),
            instanceData.get(),
            instanceOffset,
            update,
            dst.get(),
            src.get(),
            scratch.get(),
            scratchOffset);
    }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void TraceRaysKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return device_functions->pfn_CmdTraceRaysKHR(commandbuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            width,
            height,
            depth);
    }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    void TraceRaysNV(Buffer raygenShaderBindingTableBuffer,
        DeviceSize raygenShaderBindingOffset,
        Buffer missShaderBindingTableBuffer,
        DeviceSize missShaderBindingOffset,
        DeviceSize missShaderBindingStride,
        Buffer hitShaderBindingTableBuffer,
        DeviceSize hitShaderBindingOffset,
        DeviceSize hitShaderBindingStride,
        Buffer callableShaderBindingTableBuffer,
        DeviceSize callableShaderBindingOffset,
        DeviceSize callableShaderBindingStride,
        uint32_t width,
        uint32_t height,
        uint32_t depth) {
        return device_functions->pfn_CmdTraceRaysNV(commandbuffer.get(),
            raygenShaderBindingTableBuffer.get(),
            raygenShaderBindingOffset,
            missShaderBindingTableBuffer.get(),
            missShaderBindingOffset,
            missShaderBindingStride,
            hitShaderBindingTableBuffer.get(),
            hitShaderBindingOffset,
            hitShaderBindingStride,
            callableShaderBindingTableBuffer.get(),
            callableShaderBindingOffset,
            callableShaderBindingStride,
            width,
            height,
            depth);
    }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void TraceRaysIndirectKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable,
        const StridedBufferRegionKHR&  pMissShaderBindingTable,
        const StridedBufferRegionKHR&  pHitShaderBindingTable,
        const StridedBufferRegionKHR&  pCallableShaderBindingTable,
        Buffer buffer,
        DeviceSize offset) {
        return device_functions->pfn_CmdTraceRaysIndirectKHR(commandbuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            buffer.get(),
            offset);
    }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result SetPerformanceMarkerINTEL(const PerformanceMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(device_functions->pfn_CmdSetPerformanceMarkerINTEL(commandbuffer.get(),
            reinterpret_cast<const VkPerformanceMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result SetPerformanceStreamMarkerINTEL(const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) {
        return static_cast<Result>(device_functions->pfn_CmdSetPerformanceStreamMarkerINTEL(commandbuffer.get(),
            reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result SetPerformanceOverrideINTEL(const PerformanceOverrideInfoINTEL&  pOverrideInfo) {
        return static_cast<Result>(device_functions->pfn_CmdSetPerformanceOverrideINTEL(commandbuffer.get(),
            reinterpret_cast<const VkPerformanceOverrideInfoINTEL*>(&pOverrideInfo)));
    }
    void SetLineStippleEXT(uint32_t lineStippleFactor,
        uint16_t lineStipplePattern) {
        return device_functions->pfn_CmdSetLineStippleEXT(commandbuffer.get(),
            lineStippleFactor,
            lineStipplePattern);
    }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void BuildAccelerationStructureKHR(uint32_t infoCount,
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return device_functions->pfn_CmdBuildAccelerationStructureKHR(commandbuffer.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    void BuildAccelerationStructureIndirectKHR(const AccelerationStructureBuildGeometryInfoKHR&  pInfo,
        Buffer indirectBuffer,
        DeviceSize indirectOffset,
        uint32_t indirectStride) {
        return device_functions->pfn_CmdBuildAccelerationStructureIndirectKHR(commandbuffer.get(),
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(&pInfo),
            indirectBuffer.get(),
            indirectOffset,
            indirectStride);
    }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    void SetCullModeEXT(CullModeFlags cullMode) {
        return device_functions->pfn_CmdSetCullModeEXT(commandbuffer.get(),
            static_cast<VkCullModeFlags>(cullMode));
    }
    void SetFrontFaceEXT(FrontFace frontFace) {
        return device_functions->pfn_CmdSetFrontFaceEXT(commandbuffer.get(),
            static_cast<VkFrontFace>(frontFace));
    }
    void SetPrimitiveTopologyEXT(PrimitiveTopology primitiveTopology) {
        return device_functions->pfn_CmdSetPrimitiveTopologyEXT(commandbuffer.get(),
            static_cast<VkPrimitiveTopology>(primitiveTopology));
    }
    void SetViewportWithCountEXT(uint32_t viewportCount,
        const Viewport* pViewports) {
        return device_functions->pfn_CmdSetViewportWithCountEXT(commandbuffer.get(),
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void SetScissorWithCountEXT(uint32_t scissorCount,
        const Rect2D* pScissors) {
        return device_functions->pfn_CmdSetScissorWithCountEXT(commandbuffer.get(),
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void BindVertexBuffers2EXT(uint32_t firstBinding,
        uint32_t bindingCount,
        const Buffer* pBuffers,
        const DeviceSize* pOffsets,
        const DeviceSize* pSizes,
        const DeviceSize* pStrides) {
        return device_functions->pfn_CmdBindVertexBuffers2EXT(commandbuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes,
            pStrides);
    }
    void SetDepthTestEnableEXT(Bool32 depthTestEnable) {
        return device_functions->pfn_CmdSetDepthTestEnableEXT(commandbuffer.get(),
            depthTestEnable);
    }
    void SetDepthWriteEnableEXT(Bool32 depthWriteEnable) {
        return device_functions->pfn_CmdSetDepthWriteEnableEXT(commandbuffer.get(),
            depthWriteEnable);
    }
    void SetDepthCompareOpEXT(CompareOp depthCompareOp) {
        return device_functions->pfn_CmdSetDepthCompareOpEXT(commandbuffer.get(),
            static_cast<VkCompareOp>(depthCompareOp));
    }
    void SetDepthBoundsTestEnableEXT(Bool32 depthBoundsTestEnable) {
        return device_functions->pfn_CmdSetDepthBoundsTestEnableEXT(commandbuffer.get(),
            depthBoundsTestEnable);
    }
    void SetStencilTestEnableEXT(Bool32 stencilTestEnable) {
        return device_functions->pfn_CmdSetStencilTestEnableEXT(commandbuffer.get(),
            stencilTestEnable);
    }
    void SetStencilOpEXT(StencilFaceFlags faceMask,
        StencilOp failOp,
        StencilOp passOp,
        StencilOp depthFailOp,
        CompareOp compareOp) {
        return device_functions->pfn_CmdSetStencilOpEXT(commandbuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            static_cast<VkStencilOp>(failOp),
            static_cast<VkStencilOp>(passOp),
            static_cast<VkStencilOp>(depthFailOp),
            static_cast<VkCompareOp>(compareOp));
    }
};
} // namespace vk
// clang-format on
