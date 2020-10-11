#pragma once
// clang-format off
#include "vkm_core.h"

#if !defined(VULKAN_CUSTOM_ASSERT)
#include <cassert>
#define VULKAN_CUSTOM_ASSERT assert
#endif

#if defined(_WIN32)
    typedef struct HINSTANCE__ * HINSTANCE;
    #if defined( _WIN64 )
    typedef int64_t( __stdcall * FARPROC )();
    #else
    typedef int( __stdcall * FARPROC )();
    #endif
    extern "C" __declspec( dllimport ) HINSTANCE __stdcall LoadLibraryA( char const * lpLibFileName );
    extern "C" __declspec( dllimport ) int __stdcall FreeLibrary( HINSTANCE hLibModule );
    extern "C" __declspec( dllimport ) FARPROC __stdcall GetProcAddress( HINSTANCE hModule, const char * lpProcName );
#elif defined(__linux__) || defined(__APPLE__)
    #include <dlfcn.h>
#endif
namespace vk {
class DynamicLibrary {
    public:
    // Used to enable RAII vk::DynamicLibrary behavior
    struct LoadAtConstruction {};

    explicit DynamicLibrary() noexcept {}
    explicit DynamicLibrary([[maybe_unused]] LoadAtConstruction load) noexcept {
        init();
    }
    explicit DynamicLibrary(PFN_vkGetInstanceProcAddr GetInstanceProcAddr) noexcept : 
        get_instance_proc_addr(GetInstanceProcAddr) { }
    ~DynamicLibrary() noexcept {
        close();
    }
    DynamicLibrary(DynamicLibrary const& other) = delete;
    DynamicLibrary& operator=(DynamicLibrary const& other) = delete;
    DynamicLibrary(DynamicLibrary && other) noexcept: library(other.library), get_instance_proc_addr(other.get_instance_proc_addr) {
        other.get_instance_proc_addr = 0;
        other.library = 0;
    }
    DynamicLibrary& operator=(DynamicLibrary && other) noexcept {
        if (this != &other)
        {
            close();
            library = other.library; 
            get_instance_proc_addr = other.get_instance_proc_addr;
            other.get_instance_proc_addr = 0;
            other.library = 0;
        }
        return *this;
    }

    vk::Result init(PFN_vkGetInstanceProcAddr GetInstanceProcAddr = nullptr) noexcept {
        if (GetInstanceProcAddr != nullptr) {
            get_instance_proc_addr = GetInstanceProcAddr;
            return vk::Result::Success;
        }
#if defined(__linux__)
        library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
        if (!library) library = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
        library = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
#elif defined(_WIN32)
        library = ::LoadLibraryA("vulkan-1.dll");
#endif
        if (library == 0) return vk::Result::ErrorInitializationFailed;
        Load(get_instance_proc_addr, "vkGetInstanceProcAddr");
        if (get_instance_proc_addr == nullptr) return vk::Result::ErrorInitializationFailed;
        return vk::Result::Success;
    }
    void close() noexcept {
        if (library != nullptr) {
#if defined(__linux__) || defined(__APPLE__)
            dlclose(library);
#elif defined(_WIN32)
            ::FreeLibrary(library);
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
        func_dest = reinterpret_cast<T>(::GetProcAddress(library, func_name));
#endif
    }

#if defined(__linux__) || defined(__APPLE__)
    void *library = nullptr;
#elif defined(_WIN32)
    ::HINSTANCE library = nullptr;
#endif

    PFN_vkGetInstanceProcAddr get_instance_proc_addr = nullptr;
    
};


} // namespace vk

#include <stdint.h>
#include <new>
#include <utility>

namespace vk::detail {
/* Array data structure where the length is determined at construction time.
 * Cannot resize, add, or delete elements from.
 * Used for returning a collection from the Vulkan API
 * Does not throw any exceptions
 */
template<typename T>
struct fixed_vector
{
    explicit fixed_vector() noexcept {}
    explicit fixed_vector(size_t count) noexcept
    {
        _count = count;
        _data = new (std::nothrow) T[count];
        for (size_t i = 0; i < count; i++)
            _data[i] = T(); // some vulkan structs have default values, so must be initialized
    }
    ~fixed_vector() noexcept { delete _data; }
    fixed_vector(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (size_t i = 0; i < value.count; i++)
            _data[i] = value[i];
    }
    fixed_vector& operator=(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (size_t i = 0; i < value.count; i++)
            _data[i] = value[i];
    }
    fixed_vector(fixed_vector&& other) noexcept
      : _count(std::exchange(other._count, 0))
      , _data(std::exchange(other._data, nullptr))
    {}
    fixed_vector& operator=(fixed_vector&& other) noexcept
    {
        if (this != &other) {
            delete _data;
            _count(std::exchange(other._count, 0));
            _data(std::exchange(other._data, nullptr));
        }
        return *this;
    }

    [[nodiscard]] size_t size() noexcept { return _count; }
    [[nodiscard]] size_t size() const noexcept { return _count; }
    [[nodiscard]] bool empty() noexcept { return _count == 0; }
    [[nodiscard]] bool empty() const noexcept { return _count == 0; }
    [[nodiscard]] T* data() noexcept { return _data; }
    [[nodiscard]] const T* data() const noexcept { return _data; }
    void shrink(size_t count) noexcept { if (count < _count) _count = count;}

    [[nodiscard]] T& operator[](size_t count) & noexcept { return _data[count]; }
    [[nodiscard]] T const& operator[](size_t count) const& noexcept { return _data[count]; }

    [[nodiscard]] const T* begin() const noexcept { return _data + 0; }
    [[nodiscard]] T* begin() noexcept { return _data + 0; }
    [[nodiscard]] const T* end() const noexcept { return _data + _count; }
    [[nodiscard]] T* end() noexcept { return _data + _count; }

  private:
    size_t _count = 0;
    T* _data = nullptr;
};
} // namespace vk::detail
namespace vk {


/* Return type for Vulkan Module API functions which return a value or values
 * Holds a T value or a vk::Result for indicating the error
 * Do not use with success codes other than zero
 * Example in function definition
 * vk::expected<vk::Buffer> CreateBuffer(const BufferCreateInfo& pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) { ... }
 * Example usage:
 * auto buffer_return  = CreateBuffer( ... );
 * if (!buffer_return)
 *     error_exit("Failed to create buffer", buffer_return.error());
 * vk::Buffer buffer = buffer_return.value(); //Get value now that we've check for errors
 */
template<typename T>
struct expected {
	explicit expected (T const& value, Result result) noexcept: _value{ value}, _result{ result } {}
	explicit expected (T&& value, Result result) noexcept: _value{ std::move(value) }, _result{ result } {}

    const T* operator-> () const noexcept { assert (_result); return &_value; }
	T*       operator-> ()       noexcept { assert (_result); return &_value; }
	const T& operator* () const& noexcept { assert (_result); return _value; }
	T&       operator* () &      noexcept { assert (_result); return _value; }
	T&&      operator* () &&	 noexcept { assert (_result); return std::move (_value); }
	const T&  value () const&    noexcept { assert (_result); return _value; }
	T&        value () &         noexcept { assert (_result); return _value; }
	const T&& value () const&&   noexcept { assert (_result); return std::move(_value); }
	T&&       value () &&        noexcept { assert (_result); return std::move(_value); }

    Result error() const noexcept { assert (_result != Result::Success); return _result; }
    Result raw_result() const noexcept { return _result; }

    bool has_value () const noexcept { return _result == Result::Success; }
	explicit operator bool () const noexcept { return _result == Result::Success; }

private:
    T _value;
    Result _result = Result::Success;
};


struct GlobalFunctions {
#if defined(VK_VERSION_1_0)
    PFN_vkCreateInstance pfn_CreateInstance;
    PFN_vkGetInstanceProcAddr pfn_GetInstanceProcAddr;
    PFN_vkEnumerateInstanceExtensionProperties pfn_EnumerateInstanceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties pfn_EnumerateInstanceLayerProperties;
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    PFN_vkEnumerateInstanceVersion pfn_EnumerateInstanceVersion;
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_0)
    [[nodiscard]] expected<Instance> CreateInstance(const InstanceCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Instance pInstance;
        vk::Result result = static_cast<Result>(pfn_CreateInstance(reinterpret_cast<const VkInstanceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkInstance*>(&pInstance)));
        return expected<Instance>(pInstance, result);
    }
    [[nodiscard]] PFN_vkVoidFunction GetInstanceProcAddr(Instance instance, 
        const char* pName) const {
        return pfn_GetInstanceProcAddr(instance.get(),
            pName);
    }
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateInstanceExtensionProperties(const char* pLayerName) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_EnumerateInstanceExtensionProperties(pLayerName,
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<ExtensionProperties>{}, result);
        detail::fixed_vector<ExtensionProperties> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_EnumerateInstanceExtensionProperties(pLayerName,
            &pPropertyCount,
            reinterpret_cast<VkExtensionProperties*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<LayerProperties>> EnumerateInstanceLayerProperties() const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_EnumerateInstanceLayerProperties(&pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<LayerProperties>{}, result);
        detail::fixed_vector<LayerProperties> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_EnumerateInstanceLayerProperties(&pPropertyCount,
            reinterpret_cast<VkLayerProperties*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] expected<uint32_t> EnumerateInstanceVersion() const {
        if (pfn_EnumerateInstanceVersion == 0) return expected<uint32_t>(VK_MAKE_VERSION(1,0,0), Result::Success);
        uint32_t pApiVersion;
        vk::Result result = static_cast<Result>(pfn_EnumerateInstanceVersion(&pApiVersion));
        return expected<uint32_t>(pApiVersion, result);
    }
#endif //defined(VK_VERSION_1_1)
    explicit GlobalFunctions() noexcept {}
    explicit GlobalFunctions(DynamicLibrary const& library) noexcept {
    PFN_vkGetInstanceProcAddr get_instance_proc_addr = library.get();
#if defined(VK_VERSION_1_0)
        pfn_CreateInstance = reinterpret_cast<PFN_vkCreateInstance>(get_instance_proc_addr(nullptr,"vkCreateInstance"));
        pfn_GetInstanceProcAddr = get_instance_proc_addr;
        pfn_EnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceExtensionProperties"));
        pfn_EnumerateInstanceLayerProperties = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceLayerProperties"));
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
        pfn_EnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceVersion"));
#endif //defined(VK_VERSION_1_1)
    };
};
struct InstanceFunctions {
    Instance instance;
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
    void DestroyInstance(const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyInstance(instance.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDevice>> EnumeratePhysicalDevices() const {
        uint32_t pPhysicalDeviceCount = 0;
        vk::Result result = static_cast<Result>(pfn_EnumeratePhysicalDevices(instance.get(),
            &pPhysicalDeviceCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDevice>{}, result);
        detail::fixed_vector<PhysicalDevice> pPhysicalDevices{pPhysicalDeviceCount};
        result = static_cast<Result>(pfn_EnumeratePhysicalDevices(instance.get(),
            &pPhysicalDeviceCount,
            reinterpret_cast<VkPhysicalDevice*>(pPhysicalDevices.data())));
        if (pPhysicalDeviceCount < pPhysicalDevices.size()) pPhysicalDevices.shrink(pPhysicalDeviceCount);
        return expected(std::move(pPhysicalDevices), result);
    }
    [[nodiscard]] PFN_vkVoidFunction GetDeviceProcAddr(Device device, 
        const char* pName) const {
        return pfn_GetDeviceProcAddr(device.get(),
            pName);
    }
    [[nodiscard]] PFN_vkVoidFunction GetInstanceProcAddr(const char* pName) const {
        return pfn_GetInstanceProcAddr(instance.get(),
            pName);
    }
    [[nodiscard]] PhysicalDeviceProperties GetPhysicalDeviceProperties(PhysicalDevice physicalDevice) const {
        PhysicalDeviceProperties pProperties;
        pfn_GetPhysicalDeviceProperties(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties*>(&pProperties));
        return pProperties;
    }
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(PhysicalDevice physicalDevice) const {
        uint32_t pQueueFamilyPropertyCount = 0;
        pfn_GetPhysicalDeviceQueueFamilyProperties(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            nullptr);
        detail::fixed_vector<QueueFamilyProperties> pQueueFamilyProperties{pQueueFamilyPropertyCount};
        pfn_GetPhysicalDeviceQueueFamilyProperties(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties*>(pQueueFamilyProperties.data()));
        if (pQueueFamilyPropertyCount < pQueueFamilyProperties.size()) pQueueFamilyProperties.shrink(pQueueFamilyPropertyCount);
        return pQueueFamilyProperties;
    }
    [[nodiscard]] PhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(PhysicalDevice physicalDevice) const {
        PhysicalDeviceMemoryProperties pMemoryProperties;
        pfn_GetPhysicalDeviceMemoryProperties(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties*>(&pMemoryProperties));
        return pMemoryProperties;
    }
    [[nodiscard]] PhysicalDeviceFeatures GetPhysicalDeviceFeatures(PhysicalDevice physicalDevice) const {
        PhysicalDeviceFeatures pFeatures;
        pfn_GetPhysicalDeviceFeatures(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures*>(&pFeatures));
        return pFeatures;
    }
    [[nodiscard]] FormatProperties GetPhysicalDeviceFormatProperties(PhysicalDevice physicalDevice, 
        Format format) const {
        FormatProperties pFormatProperties;
        pfn_GetPhysicalDeviceFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties*>(&pFormatProperties));
        return pFormatProperties;
    }
    [[nodiscard]] expected<ImageFormatProperties> GetPhysicalDeviceImageFormatProperties(PhysicalDevice physicalDevice, 
        Format format, 
        ImageType type, 
        ImageTiling tiling, 
        ImageUsageFlags usage, 
        ImageCreateFlags flags) const {
        ImageFormatProperties pImageFormatProperties;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceImageFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            reinterpret_cast<VkImageFormatProperties*>(&pImageFormatProperties)));
        return expected<ImageFormatProperties>(pImageFormatProperties, result);
    }
    [[nodiscard]] expected<Device> CreateDevice(PhysicalDevice physicalDevice, 
        const DeviceCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Device pDevice;
        vk::Result result = static_cast<Result>(pfn_CreateDevice(physicalDevice.get(),
            reinterpret_cast<const VkDeviceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDevice*>(&pDevice)));
        return expected<Device>(pDevice, result);
    }
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(PhysicalDevice physicalDevice, 
        const char* pLayerName) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_EnumerateDeviceExtensionProperties(physicalDevice.get(),
            pLayerName,
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<ExtensionProperties>{}, result);
        detail::fixed_vector<ExtensionProperties> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_EnumerateDeviceExtensionProperties(physicalDevice.get(),
            pLayerName,
            &pPropertyCount,
            reinterpret_cast<VkExtensionProperties*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetPhysicalDeviceSparseImageFormatProperties(PhysicalDevice physicalDevice, 
        Format format, 
        ImageType type, 
        SampleCountFlagBits samples, 
        ImageUsageFlags usage, 
        ImageTiling tiling) const {
        uint32_t pPropertyCount = 0;
        pfn_GetPhysicalDeviceSparseImageFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkSampleCountFlagBits>(samples),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageTiling>(tiling),
            &pPropertyCount,
            nullptr);
        detail::fixed_vector<SparseImageFormatProperties> pProperties{pPropertyCount};
        pfn_GetPhysicalDeviceSparseImageFormatProperties(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkSampleCountFlagBits>(samples),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageTiling>(tiling),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties*>(pProperties.data()));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return pProperties;
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceGroupProperties>> EnumeratePhysicalDeviceGroups() const {
        uint32_t pPhysicalDeviceGroupCount = 0;
        vk::Result result = static_cast<Result>(pfn_EnumeratePhysicalDeviceGroups(instance.get(),
            &pPhysicalDeviceGroupCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDeviceGroupProperties>{}, result);
        detail::fixed_vector<PhysicalDeviceGroupProperties> pPhysicalDeviceGroupProperties{pPhysicalDeviceGroupCount};
        result = static_cast<Result>(pfn_EnumeratePhysicalDeviceGroups(instance.get(),
            &pPhysicalDeviceGroupCount,
            reinterpret_cast<VkPhysicalDeviceGroupProperties*>(pPhysicalDeviceGroupProperties.data())));
        if (pPhysicalDeviceGroupCount < pPhysicalDeviceGroupProperties.size()) pPhysicalDeviceGroupProperties.shrink(pPhysicalDeviceGroupCount);
        return expected(std::move(pPhysicalDeviceGroupProperties), result);
    }
    [[nodiscard]] PhysicalDeviceFeatures2 GetPhysicalDeviceFeatures2(PhysicalDevice physicalDevice) const {
        PhysicalDeviceFeatures2 pFeatures;
        pfn_GetPhysicalDeviceFeatures2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceFeatures2*>(&pFeatures));
        return pFeatures;
    }
    [[nodiscard]] PhysicalDeviceProperties2 GetPhysicalDeviceProperties2(PhysicalDevice physicalDevice) const {
        PhysicalDeviceProperties2 pProperties;
        pfn_GetPhysicalDeviceProperties2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceProperties2*>(&pProperties));
        return pProperties;
    }
    [[nodiscard]] FormatProperties2 GetPhysicalDeviceFormatProperties2(PhysicalDevice physicalDevice, 
        Format format) const {
        FormatProperties2 pFormatProperties;
        pfn_GetPhysicalDeviceFormatProperties2(physicalDevice.get(),
            static_cast<VkFormat>(format),
            reinterpret_cast<VkFormatProperties2*>(&pFormatProperties));
        return pFormatProperties;
    }
    [[nodiscard]] expected<ImageFormatProperties2> GetPhysicalDeviceImageFormatProperties2(PhysicalDevice physicalDevice, 
        const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const {
        ImageFormatProperties2 pImageFormatProperties;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceImageFormatProperties2(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceImageFormatInfo2*>(&pImageFormatInfo),
            reinterpret_cast<VkImageFormatProperties2*>(&pImageFormatProperties)));
        return expected<ImageFormatProperties2>(pImageFormatProperties, result);
    }
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetPhysicalDeviceQueueFamilyProperties2(PhysicalDevice physicalDevice) const {
        uint32_t pQueueFamilyPropertyCount = 0;
        pfn_GetPhysicalDeviceQueueFamilyProperties2(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            nullptr);
        detail::fixed_vector<QueueFamilyProperties2> pQueueFamilyProperties{pQueueFamilyPropertyCount};
        pfn_GetPhysicalDeviceQueueFamilyProperties2(physicalDevice.get(),
            &pQueueFamilyPropertyCount,
            reinterpret_cast<VkQueueFamilyProperties2*>(pQueueFamilyProperties.data()));
        if (pQueueFamilyPropertyCount < pQueueFamilyProperties.size()) pQueueFamilyProperties.shrink(pQueueFamilyPropertyCount);
        return pQueueFamilyProperties;
    }
    [[nodiscard]] PhysicalDeviceMemoryProperties2 GetPhysicalDeviceMemoryProperties2(PhysicalDevice physicalDevice) const {
        PhysicalDeviceMemoryProperties2 pMemoryProperties;
        pfn_GetPhysicalDeviceMemoryProperties2(physicalDevice.get(),
            reinterpret_cast<VkPhysicalDeviceMemoryProperties2*>(&pMemoryProperties));
        return pMemoryProperties;
    }
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetPhysicalDeviceSparseImageFormatProperties2(PhysicalDevice physicalDevice, 
        const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const {
        uint32_t pPropertyCount = 0;
        pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2*>(&pFormatInfo),
            &pPropertyCount,
            nullptr);
        detail::fixed_vector<SparseImageFormatProperties2> pProperties{pPropertyCount};
        pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSparseImageFormatInfo2*>(&pFormatInfo),
            &pPropertyCount,
            reinterpret_cast<VkSparseImageFormatProperties2*>(pProperties.data()));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return pProperties;
    }
    [[nodiscard]] ExternalBufferProperties GetPhysicalDeviceExternalBufferProperties(PhysicalDevice physicalDevice, 
        const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const {
        ExternalBufferProperties pExternalBufferProperties;
        pfn_GetPhysicalDeviceExternalBufferProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalBufferInfo*>(&pExternalBufferInfo),
            reinterpret_cast<VkExternalBufferProperties*>(&pExternalBufferProperties));
        return pExternalBufferProperties;
    }
    [[nodiscard]] ExternalFenceProperties GetPhysicalDeviceExternalFenceProperties(PhysicalDevice physicalDevice, 
        const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const {
        ExternalFenceProperties pExternalFenceProperties;
        pfn_GetPhysicalDeviceExternalFenceProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalFenceInfo*>(&pExternalFenceInfo),
            reinterpret_cast<VkExternalFenceProperties*>(&pExternalFenceProperties));
        return pExternalFenceProperties;
    }
    [[nodiscard]] ExternalSemaphoreProperties GetPhysicalDeviceExternalSemaphoreProperties(PhysicalDevice physicalDevice, 
        const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const {
        ExternalSemaphoreProperties pExternalSemaphoreProperties;
        pfn_GetPhysicalDeviceExternalSemaphoreProperties(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceExternalSemaphoreInfo*>(&pExternalSemaphoreInfo),
            reinterpret_cast<VkExternalSemaphoreProperties*>(&pExternalSemaphoreProperties));
        return pExternalSemaphoreProperties;
    }
#endif //defined(VK_VERSION_1_1)
#if defined(VK_KHR_surface)
    void DestroySurfaceKHR(SurfaceKHR surface, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroySurfaceKHR(instance.get(),
            surface.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<Bool32> GetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex, 
        SurfaceKHR surface) const {
        Bool32 pSupported;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            surface.get(),
            &pSupported));
        return expected<Bool32>(pSupported, result);
    }
    [[nodiscard]] expected<SurfaceCapabilitiesKHR> GetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice physicalDevice, 
        SurfaceKHR surface) const {
        SurfaceCapabilitiesKHR pSurfaceCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilitiesKHR*>(&pSurfaceCapabilities)));
        return expected<SurfaceCapabilitiesKHR>(pSurfaceCapabilities, result);
    }
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice physicalDevice, 
        SurfaceKHR surface) const {
        uint32_t pSurfaceFormatCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(),
            surface.get(),
            &pSurfaceFormatCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<SurfaceFormatKHR>{}, result);
        detail::fixed_vector<SurfaceFormatKHR> pSurfaceFormats{pSurfaceFormatCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.get(),
            surface.get(),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormatKHR*>(pSurfaceFormats.data())));
        if (pSurfaceFormatCount < pSurfaceFormats.size()) pSurfaceFormats.shrink(pSurfaceFormatCount);
        return expected(std::move(pSurfaceFormats), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice physicalDevice, 
        SurfaceKHR surface) const {
        uint32_t pPresentModeCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(),
            surface.get(),
            &pPresentModeCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PresentModeKHR>{}, result);
        detail::fixed_vector<PresentModeKHR> pPresentModes{pPresentModeCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.get(),
            surface.get(),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes.data())));
        if (pPresentModeCount < pPresentModes.size()) pPresentModes.shrink(pPresentModeCount);
        return expected(std::move(pPresentModes), result);
    }
#endif //defined(VK_KHR_surface)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    [[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPhysicalDevicePresentRectanglesKHR(PhysicalDevice physicalDevice, 
        SurfaceKHR surface) const {
        uint32_t pRectCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDevicePresentRectanglesKHR(physicalDevice.get(),
            surface.get(),
            &pRectCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<Rect2D>{}, result);
        detail::fixed_vector<Rect2D> pRects{pRectCount};
        result = static_cast<Result>(pfn_GetPhysicalDevicePresentRectanglesKHR(physicalDevice.get(),
            surface.get(),
            &pRectCount,
            reinterpret_cast<VkRect2D*>(pRects.data())));
        if (pRectCount < pRects.size()) pRects.shrink(pRectCount);
        return expected(std::move(pRects), result);
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if defined(VK_KHR_display)
    [[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetPhysicalDeviceDisplayPropertiesKHR(PhysicalDevice physicalDevice) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayPropertiesKHR>{}, result);
        detail::fixed_vector<DisplayPropertiesKHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPropertiesKHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetPhysicalDeviceDisplayPlanePropertiesKHR(PhysicalDevice physicalDevice) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayPlanePropertiesKHR>{}, result);
        detail::fixed_vector<DisplayPlanePropertiesKHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlanePropertiesKHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(PhysicalDevice physicalDevice, 
        uint32_t planeIndex) const {
        uint32_t pDisplayCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice.get(),
            planeIndex,
            &pDisplayCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayKHR>{}, result);
        detail::fixed_vector<DisplayKHR> pDisplays{pDisplayCount};
        result = static_cast<Result>(pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice.get(),
            planeIndex,
            &pDisplayCount,
            reinterpret_cast<VkDisplayKHR*>(pDisplays.data())));
        if (pDisplayCount < pDisplays.size()) pDisplays.shrink(pDisplayCount);
        return expected(std::move(pDisplays), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(PhysicalDevice physicalDevice, 
        DisplayKHR display) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetDisplayModePropertiesKHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayModePropertiesKHR>{}, result);
        detail::fixed_vector<DisplayModePropertiesKHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetDisplayModePropertiesKHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModePropertiesKHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(PhysicalDevice physicalDevice, 
        DisplayKHR display, 
        const DisplayModeCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DisplayModeKHR pMode;
        vk::Result result = static_cast<Result>(pfn_CreateDisplayModeKHR(physicalDevice.get(),
            display.get(),
            reinterpret_cast<const VkDisplayModeCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDisplayModeKHR*>(&pMode)));
        return expected<DisplayModeKHR>(pMode, result);
    }
    [[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(PhysicalDevice physicalDevice, 
        DisplayModeKHR mode, 
        uint32_t planeIndex) const {
        DisplayPlaneCapabilitiesKHR pCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetDisplayPlaneCapabilitiesKHR(physicalDevice.get(),
            mode.get(),
            planeIndex,
            reinterpret_cast<VkDisplayPlaneCapabilitiesKHR*>(&pCapabilities)));
        return expected<DisplayPlaneCapabilitiesKHR>(pCapabilities, result);
    }
    [[nodiscard]] expected<SurfaceKHR> CreateDisplayPlaneSurfaceKHR(const DisplaySurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateDisplayPlaneSurfaceKHR(instance.get(),
            reinterpret_cast<const VkDisplaySurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_KHR_display)
#if defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateXlibSurfaceKHR(const XlibSurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateXlibSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXlibSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXlibPresentationSupportKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex, 
        Display&  dpy, 
        VisualID visualID) const {
        return pfn_GetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<Display*>(&dpy),
            static_cast<VisualID>(visualID));
    }
#endif //defined(VK_USE_PLATFORM_XLIB_KHR) && (defined(VK_KHR_xlib_surface))
#if defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateXcbSurfaceKHR(const XcbSurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateXcbSurfaceKHR(instance.get(),
            reinterpret_cast<const VkXcbSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceXcbPresentationSupportKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex, 
        xcb_connection_t&  connection, 
        xcb_visualid_t visual_id) const {
        return pfn_GetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<xcb_connection_t*>(&connection),
            static_cast<xcb_visualid_t>(visual_id));
    }
#endif //defined(VK_USE_PLATFORM_XCB_KHR) && (defined(VK_KHR_xcb_surface))
#if defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateWaylandSurfaceKHR(const WaylandSurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateWaylandSurfaceKHR(instance.get(),
            reinterpret_cast<const VkWaylandSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
    [[nodiscard]] wl_display GetPhysicalDeviceWaylandPresentationSupportKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex) const {
        wl_display display;
        vk::Result result = pfn_GetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<wl_display*>(&display));
        return expected<wl_display>(display, result);
    }
#endif //defined(VK_USE_PLATFORM_WAYLAND_KHR) && (defined(VK_KHR_wayland_surface))
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateAndroidSurfaceKHR(const AndroidSurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateAndroidSurfaceKHR(instance.get(),
            reinterpret_cast<const VkAndroidSurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_KHR_android_surface))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateWin32SurfaceKHR(const Win32SurfaceCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateWin32SurfaceKHR(instance.get(),
            reinterpret_cast<const VkWin32SurfaceCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
    [[nodiscard]] VkBool32 GetPhysicalDeviceWin32PresentationSupportKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex) const {
        return pfn_GetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice.get(),
            queueFamilyIndex);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_win32_surface))
#if defined(VK_EXT_debug_report)
    [[nodiscard]] expected<DebugReportCallbackEXT> CreateDebugReportCallbackEXT(const DebugReportCallbackCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DebugReportCallbackEXT pCallback;
        vk::Result result = static_cast<Result>(pfn_CreateDebugReportCallbackEXT(instance.get(),
            reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugReportCallbackEXT*>(&pCallback)));
        return expected<DebugReportCallbackEXT>(pCallback, result);
    }
    void DestroyDebugReportCallbackEXT(DebugReportCallbackEXT callback, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDebugReportCallbackEXT(instance.get(),
            callback.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void DebugReportMessageEXT(DebugReportFlagsEXT flags, 
        DebugReportObjectTypeEXT objectType, 
        uint64_t object, 
        size_t location, 
        int32_t messageCode, 
        const char* pLayerPrefix, 
        const char* pMessage) const {
        pfn_DebugReportMessageEXT(instance.get(),
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
    [[nodiscard]] expected<SurfaceKHR> CreateStreamDescriptorSurfaceGGP(const StreamDescriptorSurfaceCreateInfoGGP&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateStreamDescriptorSurfaceGGP(instance.get(),
            reinterpret_cast<const VkStreamDescriptorSurfaceCreateInfoGGP*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_GGP) && (defined(VK_GGP_stream_descriptor_surface))
#if defined(VK_NV_external_memory_capabilities)
    [[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetPhysicalDeviceExternalImageFormatPropertiesNV(PhysicalDevice physicalDevice, 
        Format format, 
        ImageType type, 
        ImageTiling tiling, 
        ImageUsageFlags usage, 
        ImageCreateFlags flags, 
        ExternalMemoryHandleTypeFlagsNV externalHandleType) const {
        ExternalImageFormatPropertiesNV pExternalImageFormatProperties;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice.get(),
            static_cast<VkFormat>(format),
            static_cast<VkImageType>(type),
            static_cast<VkImageTiling>(tiling),
            static_cast<VkImageUsageFlags>(usage),
            static_cast<VkImageCreateFlags>(flags),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(externalHandleType),
            reinterpret_cast<VkExternalImageFormatPropertiesNV*>(&pExternalImageFormatProperties)));
        return expected<ExternalImageFormatPropertiesNV>(pExternalImageFormatProperties, result);
    }
#endif //defined(VK_NV_external_memory_capabilities)
#if defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateViSurfaceNN(const ViSurfaceCreateInfoNN&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateViSurfaceNN(instance.get(),
            reinterpret_cast<const VkViSurfaceCreateInfoNN*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_VI_NN) && (defined(VK_NN_vi_surface))
#if defined(VK_EXT_direct_mode_display)
    [[nodiscard]] Result ReleaseDisplayEXT(PhysicalDevice physicalDevice, 
        DisplayKHR display) const {
        return static_cast<Result>(pfn_ReleaseDisplayEXT(physicalDevice.get(),
            display.get()));
    }
#endif //defined(VK_EXT_direct_mode_display)
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
    [[nodiscard]] Result AcquireXlibDisplayEXT(PhysicalDevice physicalDevice, 
        Display&  dpy, 
        DisplayKHR display) const {
        return static_cast<Result>(pfn_AcquireXlibDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            display.get()));
    }
    [[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(PhysicalDevice physicalDevice, 
        Display&  dpy, 
        RROutput rrOutput) const {
        DisplayKHR pDisplay;
        vk::Result result = static_cast<Result>(pfn_GetRandROutputDisplayEXT(physicalDevice.get(),
            reinterpret_cast<Display*>(&dpy),
            static_cast<RROutput>(rrOutput),
            reinterpret_cast<VkDisplayKHR*>(&pDisplay)));
        return expected<DisplayKHR>(pDisplay, result);
    }
#endif //defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT) && (defined(VK_EXT_acquire_xlib_display))
#if defined(VK_EXT_display_surface_counter)
    [[nodiscard]] expected<SurfaceCapabilities2EXT> GetPhysicalDeviceSurfaceCapabilities2EXT(PhysicalDevice physicalDevice, 
        SurfaceKHR surface) const {
        SurfaceCapabilities2EXT pSurfaceCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice.get(),
            surface.get(),
            reinterpret_cast<VkSurfaceCapabilities2EXT*>(&pSurfaceCapabilities)));
        return expected<SurfaceCapabilities2EXT>(pSurfaceCapabilities, result);
    }
#endif //defined(VK_EXT_display_surface_counter)
#if defined(VK_KHR_performance_query)
    [[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex, 
        uint32_t&  pCounterCount, 
        PerformanceCounterKHR* pCounters, 
        PerformanceCounterDescriptionKHR* pCounterDescriptions) const {
        return static_cast<Result>(pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice.get(),
            queueFamilyIndex,
            &pCounterCount,
            reinterpret_cast<VkPerformanceCounterKHR*>(pCounters),
            reinterpret_cast<VkPerformanceCounterDescriptionKHR*>(pCounterDescriptions)));
    }
    [[nodiscard]] uint32_t GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(PhysicalDevice physicalDevice, 
        const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const {
        uint32_t pNumPasses;
        pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice.get(),
            reinterpret_cast<const VkQueryPoolPerformanceCreateInfoKHR*>(&pPerformanceQueryCreateInfo),
            &pNumPasses);
        return pNumPasses;
    }
#endif //defined(VK_KHR_performance_query)
#if defined(VK_KHR_get_surface_capabilities2)
    [[nodiscard]] expected<SurfaceCapabilities2KHR> GetPhysicalDeviceSurfaceCapabilities2KHR(PhysicalDevice physicalDevice, 
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        SurfaceCapabilities2KHR pSurfaceCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkSurfaceCapabilities2KHR*>(&pSurfaceCapabilities)));
        return expected<SurfaceCapabilities2KHR>(pSurfaceCapabilities, result);
    }
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetPhysicalDeviceSurfaceFormats2KHR(PhysicalDevice physicalDevice, 
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        uint32_t pSurfaceFormatCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pSurfaceFormatCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<SurfaceFormat2KHR>{}, result);
        detail::fixed_vector<SurfaceFormat2KHR> pSurfaceFormats{pSurfaceFormatCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pSurfaceFormatCount,
            reinterpret_cast<VkSurfaceFormat2KHR*>(pSurfaceFormats.data())));
        if (pSurfaceFormatCount < pSurfaceFormats.size()) pSurfaceFormats.shrink(pSurfaceFormatCount);
        return expected(std::move(pSurfaceFormats), result);
    }
#endif //defined(VK_KHR_get_surface_capabilities2)
#if defined(VK_KHR_get_display_properties2)
    [[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetPhysicalDeviceDisplayProperties2KHR(PhysicalDevice physicalDevice) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayProperties2KHR>{}, result);
        detail::fixed_vector<DisplayProperties2KHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayProperties2KHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetPhysicalDeviceDisplayPlaneProperties2KHR(PhysicalDevice physicalDevice) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayPlaneProperties2KHR>{}, result);
        detail::fixed_vector<DisplayPlaneProperties2KHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayPlaneProperties2KHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(PhysicalDevice physicalDevice, 
        DisplayKHR display) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetDisplayModeProperties2KHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<DisplayModeProperties2KHR>{}, result);
        detail::fixed_vector<DisplayModeProperties2KHR> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetDisplayModeProperties2KHR(physicalDevice.get(),
            display.get(),
            &pPropertyCount,
            reinterpret_cast<VkDisplayModeProperties2KHR*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(PhysicalDevice physicalDevice, 
        const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const {
        DisplayPlaneCapabilities2KHR pCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetDisplayPlaneCapabilities2KHR(physicalDevice.get(),
            reinterpret_cast<const VkDisplayPlaneInfo2KHR*>(&pDisplayPlaneInfo),
            reinterpret_cast<VkDisplayPlaneCapabilities2KHR*>(&pCapabilities)));
        return expected<DisplayPlaneCapabilities2KHR>(pCapabilities, result);
    }
#endif //defined(VK_KHR_get_display_properties2)
#if defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateIOSSurfaceMVK(const IOSSurfaceCreateInfoMVK&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateIOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkIOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_IOS_MVK) && (defined(VK_MVK_ios_surface))
#if defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateMacOSSurfaceMVK(const MacOSSurfaceCreateInfoMVK&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateMacOSSurfaceMVK(instance.get(),
            reinterpret_cast<const VkMacOSSurfaceCreateInfoMVK*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_MACOS_MVK) && (defined(VK_MVK_macos_surface))
#if defined(VK_EXT_debug_utils)
    [[nodiscard]] expected<DebugUtilsMessengerEXT> CreateDebugUtilsMessengerEXT(const DebugUtilsMessengerCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DebugUtilsMessengerEXT pMessenger;
        vk::Result result = static_cast<Result>(pfn_CreateDebugUtilsMessengerEXT(instance.get(),
            reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDebugUtilsMessengerEXT*>(&pMessenger)));
        return expected<DebugUtilsMessengerEXT>(pMessenger, result);
    }
    void DestroyDebugUtilsMessengerEXT(DebugUtilsMessengerEXT messenger, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDebugUtilsMessengerEXT(instance.get(),
            messenger.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void SubmitDebugUtilsMessageEXT(DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
        DebugUtilsMessageTypeFlagsEXT messageTypes, 
        const DebugUtilsMessengerCallbackDataEXT&  pCallbackData) const {
        pfn_SubmitDebugUtilsMessageEXT(instance.get(),
            static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity),
            static_cast<VkDebugUtilsMessageTypeFlagsEXT>(messageTypes),
            reinterpret_cast<const VkDebugUtilsMessengerCallbackDataEXT*>(&pCallbackData));
    }
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_EXT_sample_locations)
    [[nodiscard]] MultisamplePropertiesEXT GetPhysicalDeviceMultisamplePropertiesEXT(PhysicalDevice physicalDevice, 
        SampleCountFlagBits samples) const {
        MultisamplePropertiesEXT pMultisampleProperties;
        pfn_GetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice.get(),
            static_cast<VkSampleCountFlagBits>(samples),
            reinterpret_cast<VkMultisamplePropertiesEXT*>(&pMultisampleProperties));
        return pMultisampleProperties;
    }
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_EXT_calibrated_timestamps)
    [[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetPhysicalDeviceCalibrateableTimeDomainsEXT(PhysicalDevice physicalDevice) const {
        uint32_t pTimeDomainCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice.get(),
            &pTimeDomainCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<TimeDomainEXT>{}, result);
        detail::fixed_vector<TimeDomainEXT> pTimeDomains{pTimeDomainCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice.get(),
            &pTimeDomainCount,
            reinterpret_cast<VkTimeDomainEXT*>(pTimeDomains.data())));
        if (pTimeDomainCount < pTimeDomains.size()) pTimeDomains.shrink(pTimeDomainCount);
        return expected(std::move(pTimeDomains), result);
    }
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateImagePipeSurfaceFUCHSIA(const ImagePipeSurfaceCreateInfoFUCHSIA&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateImagePipeSurfaceFUCHSIA(instance.get(),
            reinterpret_cast<const VkImagePipeSurfaceCreateInfoFUCHSIA*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_FUCHSIA) && (defined(VK_FUCHSIA_imagepipe_surface))
#if defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateMetalSurfaceEXT(const MetalSurfaceCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateMetalSurfaceEXT(instance.get(),
            reinterpret_cast<const VkMetalSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_USE_PLATFORM_METAL_EXT) && (defined(VK_EXT_metal_surface))
#if defined(VK_EXT_tooling_info)
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetPhysicalDeviceToolPropertiesEXT(PhysicalDevice physicalDevice) const {
        uint32_t pToolCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceToolPropertiesEXT(physicalDevice.get(),
            &pToolCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>{}, result);
        detail::fixed_vector<PhysicalDeviceToolPropertiesEXT> pToolProperties{pToolCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceToolPropertiesEXT(physicalDevice.get(),
            &pToolCount,
            reinterpret_cast<VkPhysicalDeviceToolPropertiesEXT*>(pToolProperties.data())));
        if (pToolCount < pToolProperties.size()) pToolProperties.shrink(pToolCount);
        return expected(std::move(pToolProperties), result);
    }
#endif //defined(VK_EXT_tooling_info)
#if defined(VK_NV_cooperative_matrix)
    [[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetPhysicalDeviceCooperativeMatrixPropertiesNV(PhysicalDevice physicalDevice) const {
        uint32_t pPropertyCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice.get(),
            &pPropertyCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<CooperativeMatrixPropertiesNV>{}, result);
        detail::fixed_vector<CooperativeMatrixPropertiesNV> pProperties{pPropertyCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice.get(),
            &pPropertyCount,
            reinterpret_cast<VkCooperativeMatrixPropertiesNV*>(pProperties.data())));
        if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
        return expected(std::move(pProperties), result);
    }
#endif //defined(VK_NV_cooperative_matrix)
#if defined(VK_NV_coverage_reduction_mode)
    [[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(PhysicalDevice physicalDevice) const {
        uint32_t pCombinationCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice.get(),
            &pCombinationCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<FramebufferMixedSamplesCombinationNV>{}, result);
        detail::fixed_vector<FramebufferMixedSamplesCombinationNV> pCombinations{pCombinationCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice.get(),
            &pCombinationCount,
            reinterpret_cast<VkFramebufferMixedSamplesCombinationNV*>(pCombinations.data())));
        if (pCombinationCount < pCombinations.size()) pCombinations.shrink(pCombinationCount);
        return expected(std::move(pCombinations), result);
    }
#endif //defined(VK_NV_coverage_reduction_mode)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModes2EXT(PhysicalDevice physicalDevice, 
        const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        uint32_t pPresentModeCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pPresentModeCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PresentModeKHR>{}, result);
        detail::fixed_vector<PresentModeKHR> pPresentModes{pPresentModeCount};
        result = static_cast<Result>(pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            &pPresentModeCount,
            reinterpret_cast<VkPresentModeKHR*>(pPresentModes.data())));
        if (pPresentModeCount < pPresentModes.size()) pPresentModes.shrink(pPresentModeCount);
        return expected(std::move(pPresentModes), result);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_EXT_headless_surface)
    [[nodiscard]] expected<SurfaceKHR> CreateHeadlessSurfaceEXT(const HeadlessSurfaceCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateHeadlessSurfaceEXT(instance.get(),
            reinterpret_cast<const VkHeadlessSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
#endif //defined(VK_EXT_headless_surface)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    [[nodiscard]] expected<SurfaceKHR> CreateDirectFBSurfaceEXT(const DirectFBSurfaceCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SurfaceKHR pSurface;
        vk::Result result = static_cast<Result>(pfn_CreateDirectFBSurfaceEXT(instance.get(),
            reinterpret_cast<const VkDirectFBSurfaceCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSurfaceKHR*>(&pSurface)));
        return expected<SurfaceKHR>(pSurface, result);
    }
    [[nodiscard]] IDirectFB GetPhysicalDeviceDirectFBPresentationSupportEXT(PhysicalDevice physicalDevice, 
        uint32_t queueFamilyIndex) const {
        IDirectFB dfb;
        vk::Result result = pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice.get(),
            queueFamilyIndex,
            reinterpret_cast<IDirectFB*>(&dfb));
        return expected<IDirectFB>(dfb, result);
    }
#endif //defined(VK_USE_PLATFORM_DIRECTFB_EXT) && (defined(VK_EXT_directfb_surface))
    explicit InstanceFunctions() noexcept {}
    explicit InstanceFunctions(GlobalFunctions const& global_functions, Instance instance) noexcept 
        :instance(instance) { 
    PFN_vkGetInstanceProcAddr get_instance_proc_addr = global_functions.pfn_GetInstanceProcAddr;
#if defined(VK_VERSION_1_0)
        pfn_DestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(get_instance_proc_addr(instance.get(),"vkDestroyInstance"));
        pfn_EnumeratePhysicalDevices = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(get_instance_proc_addr(instance.get(),"vkEnumeratePhysicalDevices"));
        pfn_GetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(get_instance_proc_addr(instance.get(),"vkGetDeviceProcAddr"));
        pfn_GetInstanceProcAddr = get_instance_proc_addr;
        pfn_GetPhysicalDeviceProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceProperties"));
        pfn_GetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceQueueFamilyProperties"));
        pfn_GetPhysicalDeviceMemoryProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceMemoryProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceMemoryProperties"));
        pfn_GetPhysicalDeviceFeatures = reinterpret_cast<PFN_vkGetPhysicalDeviceFeatures>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFeatures"));
        pfn_GetPhysicalDeviceFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceFormatProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceFormatProperties"));
        pfn_GetPhysicalDeviceImageFormatProperties = reinterpret_cast<PFN_vkGetPhysicalDeviceImageFormatProperties>(get_instance_proc_addr(instance.get(),"vkGetPhysicalDeviceImageFormatProperties"));
        pfn_CreateDevice = reinterpret_cast<PFN_vkCreateDevice>(get_instance_proc_addr(instance.get(),"vkCreateDevice"));
        pfn_EnumerateDeviceExtensionProperties = reinterpret_cast<PFN_vkEnumerateDeviceExtensionProperties>(get_instance_proc_addr(instance.get(),"vkEnumerateDeviceExtensionProperties"));
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
    Device device;
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
#if defined(VK_KHR_copy_commands2)
    PFN_vkCmdCopyBuffer2KHR pfn_CmdCopyBuffer2KHR;
    PFN_vkCmdCopyImage2KHR pfn_CmdCopyImage2KHR;
    PFN_vkCmdBlitImage2KHR pfn_CmdBlitImage2KHR;
    PFN_vkCmdCopyBufferToImage2KHR pfn_CmdCopyBufferToImage2KHR;
    PFN_vkCmdCopyImageToBuffer2KHR pfn_CmdCopyImageToBuffer2KHR;
    PFN_vkCmdResolveImage2KHR pfn_CmdResolveImage2KHR;
#endif //defined(VK_KHR_copy_commands2)
#if defined(VK_VERSION_1_0)
    void DestroyDevice(const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDevice(device.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Queue GetDeviceQueue(uint32_t queueFamilyIndex, 
        uint32_t queueIndex) const {
        Queue pQueue;
        pfn_GetDeviceQueue(device.get(),
            queueFamilyIndex,
            queueIndex,
            reinterpret_cast<VkQueue*>(&pQueue));
        return pQueue;
    }
    [[nodiscard]] Result QueueSubmit(Queue queue, 
        uint32_t submitCount, 
        const SubmitInfo* pSubmits, 
        Fence fence) const {
        return static_cast<Result>(pfn_QueueSubmit(queue.get(),
            submitCount,
            reinterpret_cast<const VkSubmitInfo*>(pSubmits),
            fence.get()));
    }
    [[nodiscard]] Result QueueWaitIdle(Queue queue) const {
        return static_cast<Result>(pfn_QueueWaitIdle(queue.get()));
    }
    [[nodiscard]] Result DeviceWaitIdle() const {
        return static_cast<Result>(pfn_DeviceWaitIdle(device.get()));
    }
    [[nodiscard]] expected<DeviceMemory> AllocateMemory(const MemoryAllocateInfo&  pAllocateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DeviceMemory pMemory;
        vk::Result result = static_cast<Result>(pfn_AllocateMemory(device.get(),
            reinterpret_cast<const VkMemoryAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDeviceMemory*>(&pMemory)));
        return expected<DeviceMemory>(pMemory, result);
    }
    void FreeMemory(DeviceMemory memory, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_FreeMemory(device.get(),
            memory.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<void*> MapMemory(DeviceMemory memory, 
        DeviceSize offset, 
        DeviceSize size, 
        MemoryMapFlags flags) const {
        void* ppData;
        vk::Result result = static_cast<Result>(pfn_MapMemory(device.get(),
            memory.get(),
            offset,
            size,
            static_cast<VkMemoryMapFlags>(flags),
            reinterpret_cast<void**>(&ppData)));
        return expected<void*>(ppData, result);
    }
    void UnmapMemory(DeviceMemory memory) const {
        pfn_UnmapMemory(device.get(),
            memory.get());
    }
    [[nodiscard]] Result FlushMappedMemoryRanges(uint32_t memoryRangeCount, 
        const MappedMemoryRange* pMemoryRanges) const {
        return static_cast<Result>(pfn_FlushMappedMemoryRanges(device.get(),
            memoryRangeCount,
            reinterpret_cast<const VkMappedMemoryRange*>(pMemoryRanges)));
    }
    [[nodiscard]] Result InvalidateMappedMemoryRanges(uint32_t memoryRangeCount, 
        const MappedMemoryRange* pMemoryRanges) const {
        return static_cast<Result>(pfn_InvalidateMappedMemoryRanges(device.get(),
            memoryRangeCount,
            reinterpret_cast<const VkMappedMemoryRange*>(pMemoryRanges)));
    }
    [[nodiscard]] DeviceSize GetDeviceMemoryCommitment(DeviceMemory memory) const {
        DeviceSize pCommittedMemoryInBytes;
        pfn_GetDeviceMemoryCommitment(device.get(),
            memory.get(),
            &pCommittedMemoryInBytes);
        return pCommittedMemoryInBytes;
    }
    [[nodiscard]] MemoryRequirements GetBufferMemoryRequirements(Buffer buffer) const {
        MemoryRequirements pMemoryRequirements;
        pfn_GetBufferMemoryRequirements(device.get(),
            buffer.get(),
            reinterpret_cast<VkMemoryRequirements*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] Result BindBufferMemory(Buffer buffer, 
        DeviceMemory memory, 
        DeviceSize memoryOffset) const {
        return static_cast<Result>(pfn_BindBufferMemory(device.get(),
            buffer.get(),
            memory.get(),
            memoryOffset));
    }
    [[nodiscard]] MemoryRequirements GetImageMemoryRequirements(Image image) const {
        MemoryRequirements pMemoryRequirements;
        pfn_GetImageMemoryRequirements(device.get(),
            image.get(),
            reinterpret_cast<VkMemoryRequirements*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] Result BindImageMemory(Image image, 
        DeviceMemory memory, 
        DeviceSize memoryOffset) const {
        return static_cast<Result>(pfn_BindImageMemory(device.get(),
            image.get(),
            memory.get(),
            memoryOffset));
    }
    [[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements> GetImageSparseMemoryRequirements(Image image) const {
        uint32_t pSparseMemoryRequirementCount = 0;
        pfn_GetImageSparseMemoryRequirements(device.get(),
            image.get(),
            &pSparseMemoryRequirementCount,
            nullptr);
        detail::fixed_vector<SparseImageMemoryRequirements> pSparseMemoryRequirements{pSparseMemoryRequirementCount};
        pfn_GetImageSparseMemoryRequirements(device.get(),
            image.get(),
            &pSparseMemoryRequirementCount,
            reinterpret_cast<VkSparseImageMemoryRequirements*>(pSparseMemoryRequirements.data()));
        if (pSparseMemoryRequirementCount < pSparseMemoryRequirements.size()) pSparseMemoryRequirements.shrink(pSparseMemoryRequirementCount);
        return pSparseMemoryRequirements;
    }
    [[nodiscard]] Result QueueBindSparse(Queue queue, 
        uint32_t bindInfoCount, 
        const BindSparseInfo* pBindInfo, 
        Fence fence) const {
        return static_cast<Result>(pfn_QueueBindSparse(queue.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindSparseInfo*>(pBindInfo),
            fence.get()));
    }
    [[nodiscard]] expected<Fence> CreateFence(const FenceCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Fence pFence;
        vk::Result result = static_cast<Result>(pfn_CreateFence(device.get(),
            reinterpret_cast<const VkFenceCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
        return expected<Fence>(pFence, result);
    }
    void DestroyFence(Fence fence, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyFence(device.get(),
            fence.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetFences(uint32_t fenceCount, 
        const Fence* pFences) const {
        return static_cast<Result>(pfn_ResetFences(device.get(),
            fenceCount,
            reinterpret_cast<const VkFence*>(pFences)));
    }
    [[nodiscard]] Result GetFenceStatus(Fence fence) const {
        return static_cast<Result>(pfn_GetFenceStatus(device.get(),
            fence.get()));
    }
    [[nodiscard]] Result WaitForFences(uint32_t fenceCount, 
        const Fence* pFences, 
        Bool32 waitAll, 
        uint64_t timeout) const {
        return static_cast<Result>(pfn_WaitForFences(device.get(),
            fenceCount,
            reinterpret_cast<const VkFence*>(pFences),
            waitAll,
            timeout));
    }
    [[nodiscard]] expected<Semaphore> CreateSemaphore(const SemaphoreCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Semaphore pSemaphore;
        vk::Result result = static_cast<Result>(pfn_CreateSemaphore(device.get(),
            reinterpret_cast<const VkSemaphoreCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSemaphore*>(&pSemaphore)));
        return expected<Semaphore>(pSemaphore, result);
    }
    void DestroySemaphore(Semaphore semaphore, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroySemaphore(device.get(),
            semaphore.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<Event> CreateEvent(const EventCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Event pEvent;
        vk::Result result = static_cast<Result>(pfn_CreateEvent(device.get(),
            reinterpret_cast<const VkEventCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkEvent*>(&pEvent)));
        return expected<Event>(pEvent, result);
    }
    void DestroyEvent(Event event, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyEvent(device.get(),
            event.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetEventStatus(Event event) const {
        return static_cast<Result>(pfn_GetEventStatus(device.get(),
            event.get()));
    }
    [[nodiscard]] Result SetEvent(Event event) const {
        return static_cast<Result>(pfn_SetEvent(device.get(),
            event.get()));
    }
    [[nodiscard]] Result ResetEvent(Event event) const {
        return static_cast<Result>(pfn_ResetEvent(device.get(),
            event.get()));
    }
    [[nodiscard]] expected<QueryPool> CreateQueryPool(const QueryPoolCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        QueryPool pQueryPool;
        vk::Result result = static_cast<Result>(pfn_CreateQueryPool(device.get(),
            reinterpret_cast<const VkQueryPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkQueryPool*>(&pQueryPool)));
        return expected<QueryPool>(pQueryPool, result);
    }
    void DestroyQueryPool(QueryPool queryPool, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyQueryPool(device.get(),
            queryPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result GetQueryPoolResults(QueryPool queryPool, 
        uint32_t firstQuery, 
        uint32_t queryCount, 
        size_t dataSize, 
        void* pData, 
        DeviceSize stride, 
        QueryResultFlags flags) const {
        return static_cast<Result>(pfn_GetQueryPoolResults(device.get(),
            queryPool.get(),
            firstQuery,
            queryCount,
            dataSize,
            reinterpret_cast<void*>(pData),
            stride,
            static_cast<VkQueryResultFlags>(flags)));
    }
    [[nodiscard]] expected<Buffer> CreateBuffer(const BufferCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Buffer pBuffer;
        vk::Result result = static_cast<Result>(pfn_CreateBuffer(device.get(),
            reinterpret_cast<const VkBufferCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkBuffer*>(&pBuffer)));
        return expected<Buffer>(pBuffer, result);
    }
    void DestroyBuffer(Buffer buffer, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyBuffer(device.get(),
            buffer.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<BufferView> CreateBufferView(const BufferViewCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        BufferView pView;
        vk::Result result = static_cast<Result>(pfn_CreateBufferView(device.get(),
            reinterpret_cast<const VkBufferViewCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkBufferView*>(&pView)));
        return expected<BufferView>(pView, result);
    }
    void DestroyBufferView(BufferView bufferView, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyBufferView(device.get(),
            bufferView.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<Image> CreateImage(const ImageCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Image pImage;
        vk::Result result = static_cast<Result>(pfn_CreateImage(device.get(),
            reinterpret_cast<const VkImageCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkImage*>(&pImage)));
        return expected<Image>(pImage, result);
    }
    void DestroyImage(Image image, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyImage(device.get(),
            image.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] SubresourceLayout GetImageSubresourceLayout(Image image, 
        const ImageSubresource&  pSubresource) const {
        SubresourceLayout pLayout;
        pfn_GetImageSubresourceLayout(device.get(),
            image.get(),
            reinterpret_cast<const VkImageSubresource*>(&pSubresource),
            reinterpret_cast<VkSubresourceLayout*>(&pLayout));
        return pLayout;
    }
    [[nodiscard]] expected<ImageView> CreateImageView(const ImageViewCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        ImageView pView;
        vk::Result result = static_cast<Result>(pfn_CreateImageView(device.get(),
            reinterpret_cast<const VkImageViewCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkImageView*>(&pView)));
        return expected<ImageView>(pView, result);
    }
    void DestroyImageView(ImageView imageView, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyImageView(device.get(),
            imageView.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<ShaderModule> CreateShaderModule(const ShaderModuleCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        ShaderModule pShaderModule;
        vk::Result result = static_cast<Result>(pfn_CreateShaderModule(device.get(),
            reinterpret_cast<const VkShaderModuleCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkShaderModule*>(&pShaderModule)));
        return expected<ShaderModule>(pShaderModule, result);
    }
    void DestroyShaderModule(ShaderModule shaderModule, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyShaderModule(device.get(),
            shaderModule.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<PipelineCache> CreatePipelineCache(const PipelineCacheCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        PipelineCache pPipelineCache;
        vk::Result result = static_cast<Result>(pfn_CreatePipelineCache(device.get(),
            reinterpret_cast<const VkPipelineCacheCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipelineCache*>(&pPipelineCache)));
        return expected<PipelineCache>(pPipelineCache, result);
    }
    void DestroyPipelineCache(PipelineCache pipelineCache, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyPipelineCache(device.get(),
            pipelineCache.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetPipelineCacheData(PipelineCache pipelineCache) const {
        size_t pDataSize = 0;
        vk::Result result = static_cast<Result>(pfn_GetPipelineCacheData(device.get(),
            pipelineCache.get(),
            &pDataSize,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
        detail::fixed_vector<void*> pData{pDataSize};
        result = static_cast<Result>(pfn_GetPipelineCacheData(device.get(),
            pipelineCache.get(),
            &pDataSize,
            reinterpret_cast<void*>(pData.data())));
        if (pDataSize < pData.size()) pData.shrink(pDataSize);
        return expected(std::move(pData), result);
    }
    [[nodiscard]] Result MergePipelineCaches(PipelineCache dstCache, 
        uint32_t srcCacheCount, 
        const PipelineCache* pSrcCaches) const {
        return static_cast<Result>(pfn_MergePipelineCaches(device.get(),
            dstCache.get(),
            srcCacheCount,
            reinterpret_cast<const VkPipelineCache*>(pSrcCaches)));
    }
    [[nodiscard]] Result CreateGraphicsPipelines(PipelineCache pipelineCache, 
        uint32_t createInfoCount, 
        const GraphicsPipelineCreateInfo* pCreateInfos, 
        const AllocationCallbacks* pAllocator, 
        Pipeline* pPipelines) const {
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
        Pipeline* pPipelines) const {
        return static_cast<Result>(pfn_CreateComputePipelines(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkComputePipelineCreateInfo*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
    void DestroyPipeline(Pipeline pipeline, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyPipeline(device.get(),
            pipeline.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<PipelineLayout> CreatePipelineLayout(const PipelineLayoutCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        PipelineLayout pPipelineLayout;
        vk::Result result = static_cast<Result>(pfn_CreatePipelineLayout(device.get(),
            reinterpret_cast<const VkPipelineLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipelineLayout*>(&pPipelineLayout)));
        return expected<PipelineLayout>(pPipelineLayout, result);
    }
    void DestroyPipelineLayout(PipelineLayout pipelineLayout, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyPipelineLayout(device.get(),
            pipelineLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<Sampler> CreateSampler(const SamplerCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Sampler pSampler;
        vk::Result result = static_cast<Result>(pfn_CreateSampler(device.get(),
            reinterpret_cast<const VkSamplerCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSampler*>(&pSampler)));
        return expected<Sampler>(pSampler, result);
    }
    void DestroySampler(Sampler sampler, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroySampler(device.get(),
            sampler.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<DescriptorSetLayout> CreateDescriptorSetLayout(const DescriptorSetLayoutCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DescriptorSetLayout pSetLayout;
        vk::Result result = static_cast<Result>(pfn_CreateDescriptorSetLayout(device.get(),
            reinterpret_cast<const VkDescriptorSetLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorSetLayout*>(&pSetLayout)));
        return expected<DescriptorSetLayout>(pSetLayout, result);
    }
    void DestroyDescriptorSetLayout(DescriptorSetLayout descriptorSetLayout, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDescriptorSetLayout(device.get(),
            descriptorSetLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<DescriptorPool> CreateDescriptorPool(const DescriptorPoolCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DescriptorPool pDescriptorPool;
        vk::Result result = static_cast<Result>(pfn_CreateDescriptorPool(device.get(),
            reinterpret_cast<const VkDescriptorPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorPool*>(&pDescriptorPool)));
        return expected<DescriptorPool>(pDescriptorPool, result);
    }
    void DestroyDescriptorPool(DescriptorPool descriptorPool, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDescriptorPool(device.get(),
            descriptorPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetDescriptorPool(DescriptorPool descriptorPool, 
        DescriptorPoolResetFlags flags) const {
        return static_cast<Result>(pfn_ResetDescriptorPool(device.get(),
            descriptorPool.get(),
            static_cast<VkDescriptorPoolResetFlags>(flags)));
    }
    [[nodiscard]] Result AllocateDescriptorSets(const DescriptorSetAllocateInfo&  pAllocateInfo, 
        DescriptorSet* pDescriptorSets) const {
        return static_cast<Result>(pfn_AllocateDescriptorSets(device.get(),
            reinterpret_cast<const VkDescriptorSetAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<VkDescriptorSet*>(pDescriptorSets)));
    }
    [[nodiscard]] Result FreeDescriptorSets(DescriptorPool descriptorPool, 
        uint32_t descriptorSetCount, 
        const DescriptorSet* pDescriptorSets) const {
        return static_cast<Result>(pfn_FreeDescriptorSets(device.get(),
            descriptorPool.get(),
            descriptorSetCount,
            reinterpret_cast<const VkDescriptorSet*>(pDescriptorSets)));
    }
    void UpdateDescriptorSets(uint32_t descriptorWriteCount, 
        const WriteDescriptorSet* pDescriptorWrites, 
        uint32_t descriptorCopyCount, 
        const CopyDescriptorSet* pDescriptorCopies) const {
        pfn_UpdateDescriptorSets(device.get(),
            descriptorWriteCount,
            reinterpret_cast<const VkWriteDescriptorSet*>(pDescriptorWrites),
            descriptorCopyCount,
            reinterpret_cast<const VkCopyDescriptorSet*>(pDescriptorCopies));
    }
    [[nodiscard]] expected<Framebuffer> CreateFramebuffer(const FramebufferCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Framebuffer pFramebuffer;
        vk::Result result = static_cast<Result>(pfn_CreateFramebuffer(device.get(),
            reinterpret_cast<const VkFramebufferCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFramebuffer*>(&pFramebuffer)));
        return expected<Framebuffer>(pFramebuffer, result);
    }
    void DestroyFramebuffer(Framebuffer framebuffer, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyFramebuffer(device.get(),
            framebuffer.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<RenderPass> CreateRenderPass(const RenderPassCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        RenderPass pRenderPass;
        vk::Result result = static_cast<Result>(pfn_CreateRenderPass(device.get(),
            reinterpret_cast<const VkRenderPassCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkRenderPass*>(&pRenderPass)));
        return expected<RenderPass>(pRenderPass, result);
    }
    void DestroyRenderPass(RenderPass renderPass, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyRenderPass(device.get(),
            renderPass.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Extent2D GetRenderAreaGranularity(RenderPass renderPass) const {
        Extent2D pGranularity;
        pfn_GetRenderAreaGranularity(device.get(),
            renderPass.get(),
            reinterpret_cast<VkExtent2D*>(&pGranularity));
        return pGranularity;
    }
    [[nodiscard]] expected<CommandPool> CreateCommandPool(const CommandPoolCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        CommandPool pCommandPool;
        vk::Result result = static_cast<Result>(pfn_CreateCommandPool(device.get(),
            reinterpret_cast<const VkCommandPoolCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkCommandPool*>(&pCommandPool)));
        return expected<CommandPool>(pCommandPool, result);
    }
    void DestroyCommandPool(CommandPool commandPool, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyCommandPool(device.get(),
            commandPool.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result ResetCommandPool(CommandPool commandPool, 
        CommandPoolResetFlags flags) const {
        return static_cast<Result>(pfn_ResetCommandPool(device.get(),
            commandPool.get(),
            static_cast<VkCommandPoolResetFlags>(flags)));
    }
    [[nodiscard]] Result AllocateCommandBuffers(const CommandBufferAllocateInfo&  pAllocateInfo, 
        CommandBuffer* pCommandBuffers) const {
        return static_cast<Result>(pfn_AllocateCommandBuffers(device.get(),
            reinterpret_cast<const VkCommandBufferAllocateInfo*>(&pAllocateInfo),
            reinterpret_cast<VkCommandBuffer*>(pCommandBuffers)));
    }
    void FreeCommandBuffers(CommandPool commandPool, 
        uint32_t commandBufferCount, 
        const CommandBuffer* pCommandBuffers) const {
        pfn_FreeCommandBuffers(device.get(),
            commandPool.get(),
            commandBufferCount,
            reinterpret_cast<const VkCommandBuffer*>(pCommandBuffers));
    }
    [[nodiscard]] Result BeginCommandBuffer(CommandBuffer commandBuffer, 
        const CommandBufferBeginInfo&  pBeginInfo) const {
        return static_cast<Result>(pfn_BeginCommandBuffer(commandBuffer.get(),
            reinterpret_cast<const VkCommandBufferBeginInfo*>(&pBeginInfo)));
    }
    [[nodiscard]] Result EndCommandBuffer(CommandBuffer commandBuffer) const {
        return static_cast<Result>(pfn_EndCommandBuffer(commandBuffer.get()));
    }
    [[nodiscard]] Result ResetCommandBuffer(CommandBuffer commandBuffer, 
        CommandBufferResetFlags flags) const {
        return static_cast<Result>(pfn_ResetCommandBuffer(commandBuffer.get(),
            static_cast<VkCommandBufferResetFlags>(flags)));
    }
    void CmdBindPipeline(CommandBuffer commandBuffer, 
        PipelineBindPoint pipelineBindPoint, 
        Pipeline pipeline) const {
        pfn_CmdBindPipeline(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get());
    }
    void CmdSetViewport(CommandBuffer commandBuffer, 
        uint32_t firstViewport, 
        uint32_t viewportCount, 
        const Viewport* pViewports) const {
        pfn_CmdSetViewport(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void CmdSetScissor(CommandBuffer commandBuffer, 
        uint32_t firstScissor, 
        uint32_t scissorCount, 
        const Rect2D* pScissors) const {
        pfn_CmdSetScissor(commandBuffer.get(),
            firstScissor,
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void CmdSetLineWidth(CommandBuffer commandBuffer, 
        float lineWidth) const {
        pfn_CmdSetLineWidth(commandBuffer.get(),
            lineWidth);
    }
    void CmdSetDepthBias(CommandBuffer commandBuffer, 
        float depthBiasConstantFactor, 
        float depthBiasClamp, 
        float depthBiasSlopeFactor) const {
        pfn_CmdSetDepthBias(commandBuffer.get(),
            depthBiasConstantFactor,
            depthBiasClamp,
            depthBiasSlopeFactor);
    }
    void CmdSetBlendConstants(CommandBuffer commandBuffer, 
        const float blendConstants[4]) const {
        pfn_CmdSetBlendConstants(commandBuffer.get(),
            blendConstants);
    }
    void CmdSetDepthBounds(CommandBuffer commandBuffer, 
        float minDepthBounds, 
        float maxDepthBounds) const {
        pfn_CmdSetDepthBounds(commandBuffer.get(),
            minDepthBounds,
            maxDepthBounds);
    }
    void CmdSetStencilCompareMask(CommandBuffer commandBuffer, 
        StencilFaceFlags faceMask, 
        uint32_t compareMask) const {
        pfn_CmdSetStencilCompareMask(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            compareMask);
    }
    void CmdSetStencilWriteMask(CommandBuffer commandBuffer, 
        StencilFaceFlags faceMask, 
        uint32_t writeMask) const {
        pfn_CmdSetStencilWriteMask(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            writeMask);
    }
    void CmdSetStencilReference(CommandBuffer commandBuffer, 
        StencilFaceFlags faceMask, 
        uint32_t reference) const {
        pfn_CmdSetStencilReference(commandBuffer.get(),
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
        const uint32_t* pDynamicOffsets) const {
        pfn_CmdBindDescriptorSets(commandBuffer.get(),
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
        IndexType indexType) const {
        pfn_CmdBindIndexBuffer(commandBuffer.get(),
            buffer.get(),
            offset,
            static_cast<VkIndexType>(indexType));
    }
    void CmdBindVertexBuffers(CommandBuffer commandBuffer, 
        uint32_t firstBinding, 
        uint32_t bindingCount, 
        const Buffer* pBuffers, 
        const DeviceSize* pOffsets) const {
        pfn_CmdBindVertexBuffers(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets);
    }
    void CmdDraw(CommandBuffer commandBuffer, 
        uint32_t vertexCount, 
        uint32_t instanceCount, 
        uint32_t firstVertex, 
        uint32_t firstInstance) const {
        pfn_CmdDraw(commandBuffer.get(),
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
        uint32_t firstInstance) const {
        pfn_CmdDrawIndexed(commandBuffer.get(),
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
        uint32_t stride) const {
        pfn_CmdDrawIndirect(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDrawIndexedIndirect(CommandBuffer commandBuffer, 
        Buffer buffer, 
        DeviceSize offset, 
        uint32_t drawCount, 
        uint32_t stride) const {
        pfn_CmdDrawIndexedIndirect(commandBuffer.get(),
            buffer.get(),
            offset,
            drawCount,
            stride);
    }
    void CmdDispatch(CommandBuffer commandBuffer, 
        uint32_t groupCountX, 
        uint32_t groupCountY, 
        uint32_t groupCountZ) const {
        pfn_CmdDispatch(commandBuffer.get(),
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    void CmdDispatchIndirect(CommandBuffer commandBuffer, 
        Buffer buffer, 
        DeviceSize offset) const {
        pfn_CmdDispatchIndirect(commandBuffer.get(),
            buffer.get(),
            offset);
    }
    void CmdCopyBuffer(CommandBuffer commandBuffer, 
        Buffer srcBuffer, 
        Buffer dstBuffer, 
        uint32_t regionCount, 
        const BufferCopy* pRegions) const {
        pfn_CmdCopyBuffer(commandBuffer.get(),
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
        const ImageCopy* pRegions) const {
        pfn_CmdCopyImage(commandBuffer.get(),
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
        Filter filter) const {
        pfn_CmdBlitImage(commandBuffer.get(),
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
        const BufferImageCopy* pRegions) const {
        pfn_CmdCopyBufferToImage(commandBuffer.get(),
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
        const BufferImageCopy* pRegions) const {
        pfn_CmdCopyImageToBuffer(commandBuffer.get(),
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
        const void* pData) const {
        pfn_CmdUpdateBuffer(commandBuffer.get(),
            dstBuffer.get(),
            dstOffset,
            dataSize,
            reinterpret_cast<const void*>(pData));
    }
    void CmdFillBuffer(CommandBuffer commandBuffer, 
        Buffer dstBuffer, 
        DeviceSize dstOffset, 
        DeviceSize size, 
        uint32_t data) const {
        pfn_CmdFillBuffer(commandBuffer.get(),
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
        const ImageSubresourceRange* pRanges) const {
        pfn_CmdClearColorImage(commandBuffer.get(),
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
        const ImageSubresourceRange* pRanges) const {
        pfn_CmdClearDepthStencilImage(commandBuffer.get(),
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
        const ClearRect* pRects) const {
        pfn_CmdClearAttachments(commandBuffer.get(),
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
        const ImageResolve* pRegions) const {
        pfn_CmdResolveImage(commandBuffer.get(),
            srcImage.get(),
            static_cast<VkImageLayout>(srcImageLayout),
            dstImage.get(),
            static_cast<VkImageLayout>(dstImageLayout),
            regionCount,
            reinterpret_cast<const VkImageResolve*>(pRegions));
    }
    void CmdSetEvent(CommandBuffer commandBuffer, 
        Event event, 
        PipelineStageFlags stageMask) const {
        pfn_CmdSetEvent(commandBuffer.get(),
            event.get(),
            static_cast<VkPipelineStageFlags>(stageMask));
    }
    void CmdResetEvent(CommandBuffer commandBuffer, 
        Event event, 
        PipelineStageFlags stageMask) const {
        pfn_CmdResetEvent(commandBuffer.get(),
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
        const ImageMemoryBarrier* pImageMemoryBarriers) const {
        pfn_CmdWaitEvents(commandBuffer.get(),
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
        const ImageMemoryBarrier* pImageMemoryBarriers) const {
        pfn_CmdPipelineBarrier(commandBuffer.get(),
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
        QueryControlFlags flags) const {
        pfn_CmdBeginQuery(commandBuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags));
    }
    void CmdEndQuery(CommandBuffer commandBuffer, 
        QueryPool queryPool, 
        uint32_t query) const {
        pfn_CmdEndQuery(commandBuffer.get(),
            queryPool.get(),
            query);
    }
    void CmdResetQueryPool(CommandBuffer commandBuffer, 
        QueryPool queryPool, 
        uint32_t firstQuery, 
        uint32_t queryCount) const {
        pfn_CmdResetQueryPool(commandBuffer.get(),
            queryPool.get(),
            firstQuery,
            queryCount);
    }
    void CmdWriteTimestamp(CommandBuffer commandBuffer, 
        PipelineStageFlagBits pipelineStage, 
        QueryPool queryPool, 
        uint32_t query) const {
        pfn_CmdWriteTimestamp(commandBuffer.get(),
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
        QueryResultFlags flags) const {
        pfn_CmdCopyQueryPoolResults(commandBuffer.get(),
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
        const void* pValues) const {
        pfn_CmdPushConstants(commandBuffer.get(),
            layout.get(),
            static_cast<VkShaderStageFlags>(stageFlags),
            offset,
            size,
            reinterpret_cast<const void*>(pValues));
    }
    void CmdBeginRenderPass(CommandBuffer commandBuffer, 
        const RenderPassBeginInfo&  pRenderPassBegin, 
        SubpassContents contents) const {
        pfn_CmdBeginRenderPass(commandBuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            static_cast<VkSubpassContents>(contents));
    }
    void CmdNextSubpass(CommandBuffer commandBuffer, 
        SubpassContents contents) const {
        pfn_CmdNextSubpass(commandBuffer.get(),
            static_cast<VkSubpassContents>(contents));
    }
    void CmdEndRenderPass(CommandBuffer commandBuffer) const {
        pfn_CmdEndRenderPass(commandBuffer.get());
    }
    void CmdExecuteCommands(CommandBuffer commandBuffer, 
        uint32_t commandBufferCount, 
        const CommandBuffer* pCommandBuffers) const {
        pfn_CmdExecuteCommands(commandBuffer.get(),
            commandBufferCount,
            reinterpret_cast<const VkCommandBuffer*>(pCommandBuffers));
    }
#endif //defined(VK_VERSION_1_0)
#if defined(VK_VERSION_1_1)
    [[nodiscard]] Result BindBufferMemory2(uint32_t bindInfoCount, 
        const BindBufferMemoryInfo* pBindInfos) const {
        return static_cast<Result>(pfn_BindBufferMemory2(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindBufferMemoryInfo*>(pBindInfos)));
    }
    [[nodiscard]] Result BindImageMemory2(uint32_t bindInfoCount, 
        const BindImageMemoryInfo* pBindInfos) const {
        return static_cast<Result>(pfn_BindImageMemory2(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindImageMemoryInfo*>(pBindInfos)));
    }
    [[nodiscard]] PeerMemoryFeatureFlags GetDeviceGroupPeerMemoryFeatures(uint32_t heapIndex, 
        uint32_t localDeviceIndex, 
        uint32_t remoteDeviceIndex) const {
        PeerMemoryFeatureFlags pPeerMemoryFeatures;
        pfn_GetDeviceGroupPeerMemoryFeatures(device.get(),
            heapIndex,
            localDeviceIndex,
            remoteDeviceIndex,
            reinterpret_cast<VkPeerMemoryFeatureFlags*>(&pPeerMemoryFeatures));
        return pPeerMemoryFeatures;
    }
    void CmdSetDeviceMask(CommandBuffer commandBuffer, 
        uint32_t deviceMask) const {
        pfn_CmdSetDeviceMask(commandBuffer.get(),
            deviceMask);
    }
    void CmdDispatchBase(CommandBuffer commandBuffer, 
        uint32_t baseGroupX, 
        uint32_t baseGroupY, 
        uint32_t baseGroupZ, 
        uint32_t groupCountX, 
        uint32_t groupCountY, 
        uint32_t groupCountZ) const {
        pfn_CmdDispatchBase(commandBuffer.get(),
            baseGroupX,
            baseGroupY,
            baseGroupZ,
            groupCountX,
            groupCountY,
            groupCountZ);
    }
    [[nodiscard]] MemoryRequirements2 GetBufferMemoryRequirements2(const BufferMemoryRequirementsInfo2&  pInfo) const {
        MemoryRequirements2 pMemoryRequirements;
        pfn_GetBufferMemoryRequirements2(device.get(),
            reinterpret_cast<const VkBufferMemoryRequirementsInfo2*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] MemoryRequirements2 GetImageMemoryRequirements2(const ImageMemoryRequirementsInfo2&  pInfo) const {
        MemoryRequirements2 pMemoryRequirements;
        pfn_GetImageMemoryRequirements2(device.get(),
            reinterpret_cast<const VkImageMemoryRequirementsInfo2*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements2> GetImageSparseMemoryRequirements2(const ImageSparseMemoryRequirementsInfo2&  pInfo) const {
        uint32_t pSparseMemoryRequirementCount = 0;
        pfn_GetImageSparseMemoryRequirements2(device.get(),
            reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2*>(&pInfo),
            &pSparseMemoryRequirementCount,
            nullptr);
        detail::fixed_vector<SparseImageMemoryRequirements2> pSparseMemoryRequirements{pSparseMemoryRequirementCount};
        pfn_GetImageSparseMemoryRequirements2(device.get(),
            reinterpret_cast<const VkImageSparseMemoryRequirementsInfo2*>(&pInfo),
            &pSparseMemoryRequirementCount,
            reinterpret_cast<VkSparseImageMemoryRequirements2*>(pSparseMemoryRequirements.data()));
        if (pSparseMemoryRequirementCount < pSparseMemoryRequirements.size()) pSparseMemoryRequirements.shrink(pSparseMemoryRequirementCount);
        return pSparseMemoryRequirements;
    }
    void TrimCommandPool(CommandPool commandPool, 
        CommandPoolTrimFlags flags) const {
        pfn_TrimCommandPool(device.get(),
            commandPool.get(),
            static_cast<VkCommandPoolTrimFlags>(flags));
    }
    [[nodiscard]] Queue GetDeviceQueue2(const DeviceQueueInfo2&  pQueueInfo) const {
        Queue pQueue;
        pfn_GetDeviceQueue2(device.get(),
            reinterpret_cast<const VkDeviceQueueInfo2*>(&pQueueInfo),
            reinterpret_cast<VkQueue*>(&pQueue));
        return pQueue;
    }
    [[nodiscard]] expected<SamplerYcbcrConversion> CreateSamplerYcbcrConversion(const SamplerYcbcrConversionCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SamplerYcbcrConversion pYcbcrConversion;
        vk::Result result = static_cast<Result>(pfn_CreateSamplerYcbcrConversion(device.get(),
            reinterpret_cast<const VkSamplerYcbcrConversionCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSamplerYcbcrConversion*>(&pYcbcrConversion)));
        return expected<SamplerYcbcrConversion>(pYcbcrConversion, result);
    }
    void DestroySamplerYcbcrConversion(SamplerYcbcrConversion ycbcrConversion, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroySamplerYcbcrConversion(device.get(),
            ycbcrConversion.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<DescriptorUpdateTemplate> CreateDescriptorUpdateTemplate(const DescriptorUpdateTemplateCreateInfo&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        DescriptorUpdateTemplate pDescriptorUpdateTemplate;
        vk::Result result = static_cast<Result>(pfn_CreateDescriptorUpdateTemplate(device.get(),
            reinterpret_cast<const VkDescriptorUpdateTemplateCreateInfo*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDescriptorUpdateTemplate*>(&pDescriptorUpdateTemplate)));
        return expected<DescriptorUpdateTemplate>(pDescriptorUpdateTemplate, result);
    }
    void DestroyDescriptorUpdateTemplate(DescriptorUpdateTemplate descriptorUpdateTemplate, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDescriptorUpdateTemplate(device.get(),
            descriptorUpdateTemplate.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    void UpdateDescriptorSetWithTemplate(DescriptorSet descriptorSet, 
        DescriptorUpdateTemplate descriptorUpdateTemplate, 
        const void* pData) const {
        pfn_UpdateDescriptorSetWithTemplate(device.get(),
            descriptorSet.get(),
            descriptorUpdateTemplate.get(),
            reinterpret_cast<const void*>(pData));
    }
    [[nodiscard]] DescriptorSetLayoutSupport GetDescriptorSetLayoutSupport(const DescriptorSetLayoutCreateInfo&  pCreateInfo) const {
        DescriptorSetLayoutSupport pSupport;
        pfn_GetDescriptorSetLayoutSupport(device.get(),
            reinterpret_cast<const VkDescriptorSetLayoutCreateInfo*>(&pCreateInfo),
            reinterpret_cast<VkDescriptorSetLayoutSupport*>(&pSupport));
        return pSupport;
    }
#endif //defined(VK_VERSION_1_1)
#if defined(VK_VERSION_1_2)
    void CmdDrawIndirectCount(CommandBuffer commandBuffer, 
        Buffer buffer, 
        DeviceSize offset, 
        Buffer countBuffer, 
        DeviceSize countBufferOffset, 
        uint32_t maxDrawCount, 
        uint32_t stride) const {
        pfn_CmdDrawIndirectCount(commandBuffer.get(),
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
        uint32_t stride) const {
        pfn_CmdDrawIndexedIndirectCount(commandBuffer.get(),
            buffer.get(),
            offset,
            countBuffer.get(),
            countBufferOffset,
            maxDrawCount,
            stride);
    }
    [[nodiscard]] expected<RenderPass> CreateRenderPass2(const RenderPassCreateInfo2&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        RenderPass pRenderPass;
        vk::Result result = static_cast<Result>(pfn_CreateRenderPass2(device.get(),
            reinterpret_cast<const VkRenderPassCreateInfo2*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkRenderPass*>(&pRenderPass)));
        return expected<RenderPass>(pRenderPass, result);
    }
    void CmdBeginRenderPass2(CommandBuffer commandBuffer, 
        const RenderPassBeginInfo&  pRenderPassBegin, 
        const SubpassBeginInfo&  pSubpassBeginInfo) const {
        pfn_CmdBeginRenderPass2(commandBuffer.get(),
            reinterpret_cast<const VkRenderPassBeginInfo*>(&pRenderPassBegin),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo));
    }
    void CmdNextSubpass2(CommandBuffer commandBuffer, 
        const SubpassBeginInfo&  pSubpassBeginInfo, 
        const SubpassEndInfo&  pSubpassEndInfo) const {
        pfn_CmdNextSubpass2(commandBuffer.get(),
            reinterpret_cast<const VkSubpassBeginInfo*>(&pSubpassBeginInfo),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void CmdEndRenderPass2(CommandBuffer commandBuffer, 
        const SubpassEndInfo&  pSubpassEndInfo) const {
        pfn_CmdEndRenderPass2(commandBuffer.get(),
            reinterpret_cast<const VkSubpassEndInfo*>(&pSubpassEndInfo));
    }
    void ResetQueryPool(QueryPool queryPool, 
        uint32_t firstQuery, 
        uint32_t queryCount) const {
        pfn_ResetQueryPool(device.get(),
            queryPool.get(),
            firstQuery,
            queryCount);
    }
    [[nodiscard]] expected<uint64_t> GetSemaphoreCounterValue(Semaphore semaphore) const {
        uint64_t pValue;
        vk::Result result = static_cast<Result>(pfn_GetSemaphoreCounterValue(device.get(),
            semaphore.get(),
            &pValue));
        return expected<uint64_t>(pValue, result);
    }
    [[nodiscard]] Result WaitSemaphores(const SemaphoreWaitInfo&  pWaitInfo, 
        uint64_t timeout) const {
        return static_cast<Result>(pfn_WaitSemaphores(device.get(),
            reinterpret_cast<const VkSemaphoreWaitInfo*>(&pWaitInfo),
            timeout));
    }
    [[nodiscard]] Result SignalSemaphore(const SemaphoreSignalInfo&  pSignalInfo) const {
        return static_cast<Result>(pfn_SignalSemaphore(device.get(),
            reinterpret_cast<const VkSemaphoreSignalInfo*>(&pSignalInfo)));
    }
    [[nodiscard]] uint64_t GetBufferOpaqueCaptureAddress(const BufferDeviceAddressInfo&  pInfo) const {
        return pfn_GetBufferOpaqueCaptureAddress(device.get(),
            reinterpret_cast<const VkBufferDeviceAddressInfo*>(&pInfo));
    }
    [[nodiscard]] VkDeviceAddress GetBufferDeviceAddress(const BufferDeviceAddressInfo&  pInfo) const {
        return pfn_GetBufferDeviceAddress(device.get(),
            reinterpret_cast<const VkBufferDeviceAddressInfo*>(&pInfo));
    }
    [[nodiscard]] uint64_t GetDeviceMemoryOpaqueCaptureAddress(const DeviceMemoryOpaqueCaptureAddressInfo&  pInfo) const {
        return pfn_GetDeviceMemoryOpaqueCaptureAddress(device.get(),
            reinterpret_cast<const VkDeviceMemoryOpaqueCaptureAddressInfo*>(&pInfo));
    }
#endif //defined(VK_VERSION_1_2)
#if defined(VK_KHR_swapchain)
    [[nodiscard]] expected<SwapchainKHR> CreateSwapchainKHR(const SwapchainCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        SwapchainKHR pSwapchain;
        vk::Result result = static_cast<Result>(pfn_CreateSwapchainKHR(device.get(),
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(&pSwapchain)));
        return expected<SwapchainKHR>(pSwapchain, result);
    }
    void DestroySwapchainKHR(SwapchainKHR swapchain, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroySwapchainKHR(device.get(),
            swapchain.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<detail::fixed_vector<Image>> GetSwapchainImagesKHR(SwapchainKHR swapchain) const {
        uint32_t pSwapchainImageCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetSwapchainImagesKHR(device.get(),
            swapchain.get(),
            &pSwapchainImageCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<Image>{}, result);
        detail::fixed_vector<Image> pSwapchainImages{pSwapchainImageCount};
        result = static_cast<Result>(pfn_GetSwapchainImagesKHR(device.get(),
            swapchain.get(),
            &pSwapchainImageCount,
            reinterpret_cast<VkImage*>(pSwapchainImages.data())));
        if (pSwapchainImageCount < pSwapchainImages.size()) pSwapchainImages.shrink(pSwapchainImageCount);
        return expected(std::move(pSwapchainImages), result);
    }
    [[nodiscard]] expected<uint32_t> AcquireNextImageKHR(SwapchainKHR swapchain, 
        uint64_t timeout, 
        Semaphore semaphore, 
        Fence fence) const {
        uint32_t pImageIndex;
        vk::Result result = static_cast<Result>(pfn_AcquireNextImageKHR(device.get(),
            swapchain.get(),
            timeout,
            semaphore.get(),
            fence.get(),
            &pImageIndex));
        return expected<uint32_t>(pImageIndex, result);
    }
    [[nodiscard]] Result QueuePresentKHR(Queue queue, 
        const PresentInfoKHR&  pPresentInfo) const {
        return static_cast<Result>(pfn_QueuePresentKHR(queue.get(),
            reinterpret_cast<const VkPresentInfoKHR*>(&pPresentInfo)));
    }
#endif //defined(VK_KHR_swapchain)
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
    [[nodiscard]] expected<DeviceGroupPresentCapabilitiesKHR> GetDeviceGroupPresentCapabilitiesKHR() const {
        DeviceGroupPresentCapabilitiesKHR pDeviceGroupPresentCapabilities;
        vk::Result result = static_cast<Result>(pfn_GetDeviceGroupPresentCapabilitiesKHR(device.get(),
            reinterpret_cast<VkDeviceGroupPresentCapabilitiesKHR*>(&pDeviceGroupPresentCapabilities)));
        return expected<DeviceGroupPresentCapabilitiesKHR>(pDeviceGroupPresentCapabilities, result);
    }
    [[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface) const {
        DeviceGroupPresentModeFlagsKHR pModes;
        vk::Result result = static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModesKHR(device.get(),
            surface.get(),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
        return expected<DeviceGroupPresentModeFlagsKHR>(pModes, result);
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_surface))
#if (defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
    [[nodiscard]] expected<uint32_t> AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo) const {
        uint32_t pImageIndex;
        vk::Result result = static_cast<Result>(pfn_AcquireNextImage2KHR(device.get(),
            reinterpret_cast<const VkAcquireNextImageInfoKHR*>(&pAcquireInfo),
            &pImageIndex));
        return expected<uint32_t>(pImageIndex, result);
    }
#endif //(defined(VK_KHR_swapchain) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_device_group) && defined(VK_KHR_swapchain))
#if defined(VK_KHR_display_swapchain)
    [[nodiscard]] Result CreateSharedSwapchainsKHR(uint32_t swapchainCount, 
        const SwapchainCreateInfoKHR* pCreateInfos, 
        const AllocationCallbacks* pAllocator, 
        SwapchainKHR* pSwapchains) const {
        return static_cast<Result>(pfn_CreateSharedSwapchainsKHR(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainCreateInfoKHR*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkSwapchainKHR*>(pSwapchains)));
    }
#endif //defined(VK_KHR_display_swapchain)
#if defined(VK_EXT_debug_marker)
    [[nodiscard]] Result DebugMarkerSetObjectNameEXT(const DebugMarkerObjectNameInfoEXT&  pNameInfo) const {
        return static_cast<Result>(pfn_DebugMarkerSetObjectNameEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectNameInfoEXT*>(&pNameInfo)));
    }
    [[nodiscard]] Result DebugMarkerSetObjectTagEXT(const DebugMarkerObjectTagInfoEXT&  pTagInfo) const {
        return static_cast<Result>(pfn_DebugMarkerSetObjectTagEXT(device.get(),
            reinterpret_cast<const VkDebugMarkerObjectTagInfoEXT*>(&pTagInfo)));
    }
    void CmdDebugMarkerBeginEXT(CommandBuffer commandBuffer, 
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
        pfn_CmdDebugMarkerBeginEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
    void CmdDebugMarkerEndEXT(CommandBuffer commandBuffer) const {
        pfn_CmdDebugMarkerEndEXT(commandBuffer.get());
    }
    void CmdDebugMarkerInsertEXT(CommandBuffer commandBuffer, 
        const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
        pfn_CmdDebugMarkerInsertEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugMarkerMarkerInfoEXT*>(&pMarkerInfo));
    }
#endif //defined(VK_EXT_debug_marker)
#if defined(VK_EXT_transform_feedback)
    void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer, 
        uint32_t firstBinding, 
        uint32_t bindingCount, 
        const Buffer* pBuffers, 
        const DeviceSize* pOffsets, 
        const DeviceSize* pSizes) const {
        pfn_CmdBindTransformFeedbackBuffersEXT(commandBuffer.get(),
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
        const DeviceSize* pCounterBufferOffsets) const {
        pfn_CmdBeginTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer, 
        uint32_t firstCounterBuffer, 
        uint32_t counterBufferCount, 
        const Buffer* pCounterBuffers, 
        const DeviceSize* pCounterBufferOffsets) const {
        pfn_CmdEndTransformFeedbackEXT(commandBuffer.get(),
            firstCounterBuffer,
            counterBufferCount,
            reinterpret_cast<const VkBuffer*>(pCounterBuffers),
            pCounterBufferOffsets);
    }
    void CmdBeginQueryIndexedEXT(CommandBuffer commandBuffer, 
        QueryPool queryPool, 
        uint32_t query, 
        QueryControlFlags flags, 
        uint32_t index) const {
        pfn_CmdBeginQueryIndexedEXT(commandBuffer.get(),
            queryPool.get(),
            query,
            static_cast<VkQueryControlFlags>(flags),
            index);
    }
    void CmdEndQueryIndexedEXT(CommandBuffer commandBuffer, 
        QueryPool queryPool, 
        uint32_t query, 
        uint32_t index) const {
        pfn_CmdEndQueryIndexedEXT(commandBuffer.get(),
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
        uint32_t vertexStride) const {
        pfn_CmdDrawIndirectByteCountEXT(commandBuffer.get(),
            instanceCount,
            firstInstance,
            counterBuffer.get(),
            counterBufferOffset,
            counterOffset,
            vertexStride);
    }
#endif //defined(VK_EXT_transform_feedback)
#if defined(VK_NVX_image_view_handle)
    [[nodiscard]] uint32_t GetImageViewHandleNVX(const ImageViewHandleInfoNVX&  pInfo) const {
        return pfn_GetImageViewHandleNVX(device.get(),
            reinterpret_cast<const VkImageViewHandleInfoNVX*>(&pInfo));
    }
    [[nodiscard]] expected<ImageViewAddressPropertiesNVX> GetImageViewAddressNVX(ImageView imageView) const {
        ImageViewAddressPropertiesNVX pProperties;
        vk::Result result = static_cast<Result>(pfn_GetImageViewAddressNVX(device.get(),
            imageView.get(),
            reinterpret_cast<VkImageViewAddressPropertiesNVX*>(&pProperties)));
        return expected<ImageViewAddressPropertiesNVX>(pProperties, result);
    }
#endif //defined(VK_NVX_image_view_handle)
#if defined(VK_AMD_shader_info)
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetShaderInfoAMD(Pipeline pipeline, 
        ShaderStageFlagBits shaderStage, 
        ShaderInfoTypeAMD infoType) const {
        size_t pInfoSize = 0;
        vk::Result result = static_cast<Result>(pfn_GetShaderInfoAMD(device.get(),
            pipeline.get(),
            static_cast<VkShaderStageFlagBits>(shaderStage),
            static_cast<VkShaderInfoTypeAMD>(infoType),
            &pInfoSize,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
        detail::fixed_vector<void*> pInfo{pInfoSize};
        result = static_cast<Result>(pfn_GetShaderInfoAMD(device.get(),
            pipeline.get(),
            static_cast<VkShaderStageFlagBits>(shaderStage),
            static_cast<VkShaderInfoTypeAMD>(infoType),
            &pInfoSize,
            reinterpret_cast<void*>(pInfo.data())));
        if (pInfoSize < pInfo.size()) pInfo.shrink(pInfoSize);
        return expected(std::move(pInfo), result);
    }
#endif //defined(VK_AMD_shader_info)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
    [[nodiscard]] expected<HANDLE> GetMemoryWin32HandleNV(DeviceMemory memory, 
        ExternalMemoryHandleTypeFlagsNV handleType) const {
        HANDLE pHandle;
        vk::Result result = static_cast<Result>(pfn_GetMemoryWin32HandleNV(device.get(),
            memory.get(),
            static_cast<VkExternalMemoryHandleTypeFlagsNV>(handleType),
            reinterpret_cast<HANDLE*>(&pHandle)));
        return expected<HANDLE>(pHandle, result);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_NV_external_memory_win32))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
    [[nodiscard]] expected<HANDLE> GetMemoryWin32HandleKHR(const MemoryGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
        HANDLE pHandle;
        vk::Result result = static_cast<Result>(pfn_GetMemoryWin32HandleKHR(device.get(),
            reinterpret_cast<const VkMemoryGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
        return expected<HANDLE>(pHandle, result);
    }
    [[nodiscard]] expected<MemoryWin32HandlePropertiesKHR> GetMemoryWin32HandlePropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, 
        HANDLE handle) const {
        MemoryWin32HandlePropertiesKHR pMemoryWin32HandleProperties;
        vk::Result result = static_cast<Result>(pfn_GetMemoryWin32HandlePropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            static_cast<HANDLE>(handle),
            reinterpret_cast<VkMemoryWin32HandlePropertiesKHR*>(&pMemoryWin32HandleProperties)));
        return expected<MemoryWin32HandlePropertiesKHR>(pMemoryWin32HandleProperties, result);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_memory_win32))
#if defined(VK_KHR_external_memory_fd)
    [[nodiscard]] expected<int> GetMemoryFdKHR(const MemoryGetFdInfoKHR&  pGetFdInfo) const {
        int pFd;
        vk::Result result = static_cast<Result>(pfn_GetMemoryFdKHR(device.get(),
            reinterpret_cast<const VkMemoryGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
        return expected<int>(pFd, result);
    }
    [[nodiscard]] expected<MemoryFdPropertiesKHR> GetMemoryFdPropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, 
        int fd) const {
        MemoryFdPropertiesKHR pMemoryFdProperties;
        vk::Result result = static_cast<Result>(pfn_GetMemoryFdPropertiesKHR(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            fd,
            reinterpret_cast<VkMemoryFdPropertiesKHR*>(&pMemoryFdProperties)));
        return expected<MemoryFdPropertiesKHR>(pMemoryFdProperties, result);
    }
#endif //defined(VK_KHR_external_memory_fd)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
    [[nodiscard]] expected<HANDLE> GetSemaphoreWin32HandleKHR(const SemaphoreGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
        HANDLE pHandle;
        vk::Result result = static_cast<Result>(pfn_GetSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
        return expected<HANDLE>(pHandle, result);
    }
    [[nodiscard]] Result ImportSemaphoreWin32HandleKHR(const ImportSemaphoreWin32HandleInfoKHR&  pImportSemaphoreWin32HandleInfo) const {
        return static_cast<Result>(pfn_ImportSemaphoreWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportSemaphoreWin32HandleInfoKHR*>(&pImportSemaphoreWin32HandleInfo)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_semaphore_win32))
#if defined(VK_KHR_external_semaphore_fd)
    [[nodiscard]] expected<int> GetSemaphoreFdKHR(const SemaphoreGetFdInfoKHR&  pGetFdInfo) const {
        int pFd;
        vk::Result result = static_cast<Result>(pfn_GetSemaphoreFdKHR(device.get(),
            reinterpret_cast<const VkSemaphoreGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
        return expected<int>(pFd, result);
    }
    [[nodiscard]] Result ImportSemaphoreFdKHR(const ImportSemaphoreFdInfoKHR&  pImportSemaphoreFdInfo) const {
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
        const WriteDescriptorSet* pDescriptorWrites) const {
        pfn_CmdPushDescriptorSetKHR(commandBuffer.get(),
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
        const void* pData) const {
        pfn_CmdPushDescriptorSetWithTemplateKHR(commandBuffer.get(),
            descriptorUpdateTemplate.get(),
            layout.get(),
            set,
            reinterpret_cast<const void*>(pData));
    }
#endif //(defined(VK_KHR_push_descriptor) && defined(VK_VERSION_1_1)) || (defined(VK_KHR_push_descriptor) && defined(VK_KHR_descriptor_update_template)) || (defined(VK_KHR_descriptor_update_template) && defined(VK_KHR_push_descriptor))
#if defined(VK_EXT_conditional_rendering)
    void CmdBeginConditionalRenderingEXT(CommandBuffer commandBuffer, 
        const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const {
        pfn_CmdBeginConditionalRenderingEXT(commandBuffer.get(),
            reinterpret_cast<const VkConditionalRenderingBeginInfoEXT*>(&pConditionalRenderingBegin));
    }
    void CmdEndConditionalRenderingEXT(CommandBuffer commandBuffer) const {
        pfn_CmdEndConditionalRenderingEXT(commandBuffer.get());
    }
#endif //defined(VK_EXT_conditional_rendering)
#if defined(VK_NV_clip_space_w_scaling)
    void CmdSetViewportWScalingNV(CommandBuffer commandBuffer, 
        uint32_t firstViewport, 
        uint32_t viewportCount, 
        const ViewportWScalingNV* pViewportWScalings) const {
        pfn_CmdSetViewportWScalingNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkViewportWScalingNV*>(pViewportWScalings));
    }
#endif //defined(VK_NV_clip_space_w_scaling)
#if defined(VK_EXT_display_control)
    [[nodiscard]] Result DisplayPowerControlEXT(DisplayKHR display, 
        const DisplayPowerInfoEXT&  pDisplayPowerInfo) const {
        return static_cast<Result>(pfn_DisplayPowerControlEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayPowerInfoEXT*>(&pDisplayPowerInfo)));
    }
    [[nodiscard]] expected<Fence> RegisterDeviceEventEXT(const DeviceEventInfoEXT&  pDeviceEventInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Fence pFence;
        vk::Result result = static_cast<Result>(pfn_RegisterDeviceEventEXT(device.get(),
            reinterpret_cast<const VkDeviceEventInfoEXT*>(&pDeviceEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
        return expected<Fence>(pFence, result);
    }
    [[nodiscard]] expected<Fence> RegisterDisplayEventEXT(DisplayKHR display, 
        const DisplayEventInfoEXT&  pDisplayEventInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        Fence pFence;
        vk::Result result = static_cast<Result>(pfn_RegisterDisplayEventEXT(device.get(),
            display.get(),
            reinterpret_cast<const VkDisplayEventInfoEXT*>(&pDisplayEventInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkFence*>(&pFence)));
        return expected<Fence>(pFence, result);
    }
    [[nodiscard]] expected<uint64_t> GetSwapchainCounterEXT(SwapchainKHR swapchain, 
        SurfaceCounterFlagBitsEXT counter) const {
        uint64_t pCounterValue;
        vk::Result result = static_cast<Result>(pfn_GetSwapchainCounterEXT(device.get(),
            swapchain.get(),
            static_cast<VkSurfaceCounterFlagBitsEXT>(counter),
            &pCounterValue));
        return expected<uint64_t>(pCounterValue, result);
    }
#endif //defined(VK_EXT_display_control)
#if defined(VK_GOOGLE_display_timing)
    [[nodiscard]] expected<RefreshCycleDurationGOOGLE> GetRefreshCycleDurationGOOGLE(SwapchainKHR swapchain) const {
        RefreshCycleDurationGOOGLE pDisplayTimingProperties;
        vk::Result result = static_cast<Result>(pfn_GetRefreshCycleDurationGOOGLE(device.get(),
            swapchain.get(),
            reinterpret_cast<VkRefreshCycleDurationGOOGLE*>(&pDisplayTimingProperties)));
        return expected<RefreshCycleDurationGOOGLE>(pDisplayTimingProperties, result);
    }
    [[nodiscard]] expected<detail::fixed_vector<PastPresentationTimingGOOGLE>> GetPastPresentationTimingGOOGLE(SwapchainKHR swapchain) const {
        uint32_t pPresentationTimingCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPastPresentationTimingGOOGLE(device.get(),
            swapchain.get(),
            &pPresentationTimingCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PastPresentationTimingGOOGLE>{}, result);
        detail::fixed_vector<PastPresentationTimingGOOGLE> pPresentationTimings{pPresentationTimingCount};
        result = static_cast<Result>(pfn_GetPastPresentationTimingGOOGLE(device.get(),
            swapchain.get(),
            &pPresentationTimingCount,
            reinterpret_cast<VkPastPresentationTimingGOOGLE*>(pPresentationTimings.data())));
        if (pPresentationTimingCount < pPresentationTimings.size()) pPresentationTimings.shrink(pPresentationTimingCount);
        return expected(std::move(pPresentationTimings), result);
    }
#endif //defined(VK_GOOGLE_display_timing)
#if defined(VK_EXT_discard_rectangles)
    void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer, 
        uint32_t firstDiscardRectangle, 
        uint32_t discardRectangleCount, 
        const Rect2D* pDiscardRectangles) const {
        pfn_CmdSetDiscardRectangleEXT(commandBuffer.get(),
            firstDiscardRectangle,
            discardRectangleCount,
            reinterpret_cast<const VkRect2D*>(pDiscardRectangles));
    }
#endif //defined(VK_EXT_discard_rectangles)
#if defined(VK_EXT_hdr_metadata)
    void SetHdrMetadataEXT(uint32_t swapchainCount, 
        const SwapchainKHR* pSwapchains, 
        const HdrMetadataEXT* pMetadata) const {
        pfn_SetHdrMetadataEXT(device.get(),
            swapchainCount,
            reinterpret_cast<const VkSwapchainKHR*>(pSwapchains),
            reinterpret_cast<const VkHdrMetadataEXT*>(pMetadata));
    }
#endif //defined(VK_EXT_hdr_metadata)
#if defined(VK_KHR_shared_presentable_image)
    [[nodiscard]] Result GetSwapchainStatusKHR(SwapchainKHR swapchain) const {
        return static_cast<Result>(pfn_GetSwapchainStatusKHR(device.get(),
            swapchain.get()));
    }
#endif //defined(VK_KHR_shared_presentable_image)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
    [[nodiscard]] expected<HANDLE> GetFenceWin32HandleKHR(const FenceGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
        HANDLE pHandle;
        vk::Result result = static_cast<Result>(pfn_GetFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkFenceGetWin32HandleInfoKHR*>(&pGetWin32HandleInfo),
            reinterpret_cast<HANDLE*>(&pHandle)));
        return expected<HANDLE>(pHandle, result);
    }
    [[nodiscard]] Result ImportFenceWin32HandleKHR(const ImportFenceWin32HandleInfoKHR&  pImportFenceWin32HandleInfo) const {
        return static_cast<Result>(pfn_ImportFenceWin32HandleKHR(device.get(),
            reinterpret_cast<const VkImportFenceWin32HandleInfoKHR*>(&pImportFenceWin32HandleInfo)));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_KHR_external_fence_win32))
#if defined(VK_KHR_external_fence_fd)
    [[nodiscard]] expected<int> GetFenceFdKHR(const FenceGetFdInfoKHR&  pGetFdInfo) const {
        int pFd;
        vk::Result result = static_cast<Result>(pfn_GetFenceFdKHR(device.get(),
            reinterpret_cast<const VkFenceGetFdInfoKHR*>(&pGetFdInfo),
            &pFd));
        return expected<int>(pFd, result);
    }
    [[nodiscard]] Result ImportFenceFdKHR(const ImportFenceFdInfoKHR&  pImportFenceFdInfo) const {
        return static_cast<Result>(pfn_ImportFenceFdKHR(device.get(),
            reinterpret_cast<const VkImportFenceFdInfoKHR*>(&pImportFenceFdInfo)));
    }
#endif //defined(VK_KHR_external_fence_fd)
#if defined(VK_KHR_performance_query)
    [[nodiscard]] Result AcquireProfilingLockKHR(const AcquireProfilingLockInfoKHR&  pInfo) const {
        return static_cast<Result>(pfn_AcquireProfilingLockKHR(device.get(),
            reinterpret_cast<const VkAcquireProfilingLockInfoKHR*>(&pInfo)));
    }
    void ReleaseProfilingLockKHR() const {
        pfn_ReleaseProfilingLockKHR(device.get());
    }
#endif //defined(VK_KHR_performance_query)
#if defined(VK_EXT_debug_utils)
    [[nodiscard]] Result SetDebugUtilsObjectNameEXT(const DebugUtilsObjectNameInfoEXT&  pNameInfo) const {
        return static_cast<Result>(pfn_SetDebugUtilsObjectNameEXT(device.get(),
            reinterpret_cast<const VkDebugUtilsObjectNameInfoEXT*>(&pNameInfo)));
    }
    [[nodiscard]] Result SetDebugUtilsObjectTagEXT(const DebugUtilsObjectTagInfoEXT&  pTagInfo) const {
        return static_cast<Result>(pfn_SetDebugUtilsObjectTagEXT(device.get(),
            reinterpret_cast<const VkDebugUtilsObjectTagInfoEXT*>(&pTagInfo)));
    }
    void QueueBeginDebugUtilsLabelEXT(Queue queue, 
        const DebugUtilsLabelEXT&  pLabelInfo) const {
        pfn_QueueBeginDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void QueueEndDebugUtilsLabelEXT(Queue queue) const {
        pfn_QueueEndDebugUtilsLabelEXT(queue.get());
    }
    void QueueInsertDebugUtilsLabelEXT(Queue queue, 
        const DebugUtilsLabelEXT&  pLabelInfo) const {
        pfn_QueueInsertDebugUtilsLabelEXT(queue.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void CmdBeginDebugUtilsLabelEXT(CommandBuffer commandBuffer, 
        const DebugUtilsLabelEXT&  pLabelInfo) const {
        pfn_CmdBeginDebugUtilsLabelEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
    void CmdEndDebugUtilsLabelEXT(CommandBuffer commandBuffer) const {
        pfn_CmdEndDebugUtilsLabelEXT(commandBuffer.get());
    }
    void CmdInsertDebugUtilsLabelEXT(CommandBuffer commandBuffer, 
        const DebugUtilsLabelEXT&  pLabelInfo) const {
        pfn_CmdInsertDebugUtilsLabelEXT(commandBuffer.get(),
            reinterpret_cast<const VkDebugUtilsLabelEXT*>(&pLabelInfo));
    }
#endif //defined(VK_EXT_debug_utils)
#if defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
    [[nodiscard]] expected<AndroidHardwareBufferPropertiesANDROID> GetAndroidHardwareBufferPropertiesANDROID(const AHardwareBuffer&  buffer) const {
        AndroidHardwareBufferPropertiesANDROID pProperties;
        vk::Result result = static_cast<Result>(pfn_GetAndroidHardwareBufferPropertiesANDROID(device.get(),
            &buffer,
            reinterpret_cast<VkAndroidHardwareBufferPropertiesANDROID*>(&pProperties)));
        return expected<AndroidHardwareBufferPropertiesANDROID>(pProperties, result);
    }
    [[nodiscard]] expected<AHardwareBuffer*> GetMemoryAndroidHardwareBufferANDROID(const MemoryGetAndroidHardwareBufferInfoANDROID&  pInfo) const {
        AHardwareBuffer* pBuffer;
        vk::Result result = static_cast<Result>(pfn_GetMemoryAndroidHardwareBufferANDROID(device.get(),
            reinterpret_cast<const VkMemoryGetAndroidHardwareBufferInfoANDROID*>(&pInfo),
            &pBuffer));
        return expected<AHardwareBuffer*>(pBuffer, result);
    }
#endif //defined(VK_USE_PLATFORM_ANDROID_KHR) && (defined(VK_ANDROID_external_memory_android_hardware_buffer))
#if defined(VK_EXT_sample_locations)
    void CmdSetSampleLocationsEXT(CommandBuffer commandBuffer, 
        const SampleLocationsInfoEXT&  pSampleLocationsInfo) const {
        pfn_CmdSetSampleLocationsEXT(commandBuffer.get(),
            reinterpret_cast<const VkSampleLocationsInfoEXT*>(&pSampleLocationsInfo));
    }
#endif //defined(VK_EXT_sample_locations)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
    void DestroyAccelerationStructureKHR(AccelerationStructureKHR accelerationStructure, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyAccelerationStructureKHR(device.get(),
            accelerationStructure.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] MemoryRequirements2 GetAccelerationStructureMemoryRequirementsKHR(const AccelerationStructureMemoryRequirementsInfoKHR&  pInfo) const {
        MemoryRequirements2 pMemoryRequirements;
        pfn_GetAccelerationStructureMemoryRequirementsKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoKHR*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] Result BindAccelerationStructureMemoryKHR(uint32_t bindInfoCount, 
        const BindAccelerationStructureMemoryInfoKHR* pBindInfos) const {
        return static_cast<Result>(pfn_BindAccelerationStructureMemoryKHR(device.get(),
            bindInfoCount,
            reinterpret_cast<const VkBindAccelerationStructureMemoryInfoKHR*>(pBindInfos)));
    }
    void CmdCopyAccelerationStructureKHR(CommandBuffer commandBuffer, 
        const CopyAccelerationStructureInfoKHR&  pInfo) const {
        pfn_CmdCopyAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) const {
        return static_cast<Result>(pfn_CopyAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdCopyAccelerationStructureToMemoryKHR(CommandBuffer commandBuffer, 
        const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
        pfn_CmdCopyAccelerationStructureToMemoryKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
        return static_cast<Result>(pfn_CopyAccelerationStructureToMemoryKHR(device.get(),
            reinterpret_cast<const VkCopyAccelerationStructureToMemoryInfoKHR*>(&pInfo)));
    }
    void CmdCopyMemoryToAccelerationStructureKHR(CommandBuffer commandBuffer, 
        const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
        pfn_CmdCopyMemoryToAccelerationStructureKHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo));
    }
    [[nodiscard]] Result CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
        return static_cast<Result>(pfn_CopyMemoryToAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkCopyMemoryToAccelerationStructureInfoKHR*>(&pInfo)));
    }
    void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer, 
        uint32_t accelerationStructureCount, 
        const AccelerationStructureKHR* pAccelerationStructures, 
        QueryType queryType, 
        QueryPool queryPool, 
        uint32_t firstQuery) const {
        pfn_CmdWriteAccelerationStructuresPropertiesKHR(commandBuffer.get(),
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
        size_t stride) const {
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
        uint32_t depth) const {
        pfn_CmdTraceRaysKHR(commandBuffer.get(),
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
        void* pData) const {
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
        void* pData) const {
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
        Pipeline* pPipelines) const {
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
        DeviceSize offset) const {
        pfn_CmdTraceRaysIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pRaygenShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pMissShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pHitShaderBindingTable),
            reinterpret_cast<const VkStridedBufferRegionKHR*>(&pCallableShaderBindingTable),
            buffer.get(),
            offset);
    }
    [[nodiscard]] Result GetDeviceAccelerationStructureCompatibilityKHR(const AccelerationStructureVersionKHR&  version) const {
        return static_cast<Result>(pfn_GetDeviceAccelerationStructureCompatibilityKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureVersionKHR*>(&version)));
    }
    [[nodiscard]] expected<AccelerationStructureKHR> CreateAccelerationStructureKHR(const AccelerationStructureCreateInfoKHR&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        AccelerationStructureKHR pAccelerationStructure;
        vk::Result result = static_cast<Result>(pfn_CreateAccelerationStructureKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoKHR*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureKHR*>(&pAccelerationStructure)));
        return expected<AccelerationStructureKHR>(pAccelerationStructure, result);
    }
    void CmdBuildAccelerationStructureKHR(CommandBuffer commandBuffer, 
        uint32_t infoCount, 
        const AccelerationStructureBuildGeometryInfoKHR* pInfos, 
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const {
        pfn_CmdBuildAccelerationStructureKHR(commandBuffer.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    void CmdBuildAccelerationStructureIndirectKHR(CommandBuffer commandBuffer, 
        const AccelerationStructureBuildGeometryInfoKHR&  pInfo, 
        Buffer indirectBuffer, 
        DeviceSize indirectOffset, 
        uint32_t indirectStride) const {
        pfn_CmdBuildAccelerationStructureIndirectKHR(commandBuffer.get(),
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(&pInfo),
            indirectBuffer.get(),
            indirectOffset,
            indirectStride);
    }
    [[nodiscard]] Result BuildAccelerationStructureKHR(uint32_t infoCount, 
        const AccelerationStructureBuildGeometryInfoKHR* pInfos, 
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const {
        return static_cast<Result>(pfn_BuildAccelerationStructureKHR(device.get(),
            infoCount,
            reinterpret_cast<const VkAccelerationStructureBuildGeometryInfoKHR*>(pInfos),
            reinterpret_cast<const VkAccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos)));
    }
    [[nodiscard]] VkDeviceAddress GetAccelerationStructureDeviceAddressKHR(const AccelerationStructureDeviceAddressInfoKHR&  pInfo) const {
        return pfn_GetAccelerationStructureDeviceAddressKHR(device.get(),
            reinterpret_cast<const VkAccelerationStructureDeviceAddressInfoKHR*>(&pInfo));
    }
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_ray_tracing))
#if defined(VK_EXT_image_drm_format_modifier)
    [[nodiscard]] expected<ImageDrmFormatModifierPropertiesEXT> GetImageDrmFormatModifierPropertiesEXT(Image image) const {
        ImageDrmFormatModifierPropertiesEXT pProperties;
        vk::Result result = static_cast<Result>(pfn_GetImageDrmFormatModifierPropertiesEXT(device.get(),
            image.get(),
            reinterpret_cast<VkImageDrmFormatModifierPropertiesEXT*>(&pProperties)));
        return expected<ImageDrmFormatModifierPropertiesEXT>(pProperties, result);
    }
#endif //defined(VK_EXT_image_drm_format_modifier)
#if defined(VK_EXT_validation_cache)
    [[nodiscard]] expected<ValidationCacheEXT> CreateValidationCacheEXT(const ValidationCacheCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        ValidationCacheEXT pValidationCache;
        vk::Result result = static_cast<Result>(pfn_CreateValidationCacheEXT(device.get(),
            reinterpret_cast<const VkValidationCacheCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkValidationCacheEXT*>(&pValidationCache)));
        return expected<ValidationCacheEXT>(pValidationCache, result);
    }
    void DestroyValidationCacheEXT(ValidationCacheEXT validationCache, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyValidationCacheEXT(device.get(),
            validationCache.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetValidationCacheDataEXT(ValidationCacheEXT validationCache) const {
        size_t pDataSize = 0;
        vk::Result result = static_cast<Result>(pfn_GetValidationCacheDataEXT(device.get(),
            validationCache.get(),
            &pDataSize,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
        detail::fixed_vector<void*> pData{pDataSize};
        result = static_cast<Result>(pfn_GetValidationCacheDataEXT(device.get(),
            validationCache.get(),
            &pDataSize,
            reinterpret_cast<void*>(pData.data())));
        if (pDataSize < pData.size()) pData.shrink(pDataSize);
        return expected(std::move(pData), result);
    }
    [[nodiscard]] Result MergeValidationCachesEXT(ValidationCacheEXT dstCache, 
        uint32_t srcCacheCount, 
        const ValidationCacheEXT* pSrcCaches) const {
        return static_cast<Result>(pfn_MergeValidationCachesEXT(device.get(),
            dstCache.get(),
            srcCacheCount,
            reinterpret_cast<const VkValidationCacheEXT*>(pSrcCaches)));
    }
#endif //defined(VK_EXT_validation_cache)
#if defined(VK_NV_shading_rate_image)
    void CmdBindShadingRateImageNV(CommandBuffer commandBuffer, 
        ImageView imageView, 
        ImageLayout imageLayout) const {
        pfn_CmdBindShadingRateImageNV(commandBuffer.get(),
            imageView.get(),
            static_cast<VkImageLayout>(imageLayout));
    }
    void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer, 
        uint32_t firstViewport, 
        uint32_t viewportCount, 
        const ShadingRatePaletteNV* pShadingRatePalettes) const {
        pfn_CmdSetViewportShadingRatePaletteNV(commandBuffer.get(),
            firstViewport,
            viewportCount,
            reinterpret_cast<const VkShadingRatePaletteNV*>(pShadingRatePalettes));
    }
    void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer, 
        CoarseSampleOrderTypeNV sampleOrderType, 
        uint32_t customSampleOrderCount, 
        const CoarseSampleOrderCustomNV* pCustomSampleOrders) const {
        pfn_CmdSetCoarseSampleOrderNV(commandBuffer.get(),
            static_cast<VkCoarseSampleOrderTypeNV>(sampleOrderType),
            customSampleOrderCount,
            reinterpret_cast<const VkCoarseSampleOrderCustomNV*>(pCustomSampleOrders));
    }
#endif //defined(VK_NV_shading_rate_image)
#if defined(VK_NV_ray_tracing)
    [[nodiscard]] Result CompileDeferredNV(Pipeline pipeline, 
        uint32_t shader) const {
        return static_cast<Result>(pfn_CompileDeferredNV(device.get(),
            pipeline.get(),
            shader));
    }
    [[nodiscard]] expected<AccelerationStructureNV> CreateAccelerationStructureNV(const AccelerationStructureCreateInfoNV&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        AccelerationStructureNV pAccelerationStructure;
        vk::Result result = static_cast<Result>(pfn_CreateAccelerationStructureNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkAccelerationStructureNV*>(&pAccelerationStructure)));
        return expected<AccelerationStructureNV>(pAccelerationStructure, result);
    }
    [[nodiscard]] MemoryRequirements2KHR GetAccelerationStructureMemoryRequirementsNV(const AccelerationStructureMemoryRequirementsInfoNV&  pInfo) const {
        MemoryRequirements2KHR pMemoryRequirements;
        pfn_GetAccelerationStructureMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkAccelerationStructureMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2KHR*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    void CmdCopyAccelerationStructureNV(CommandBuffer commandBuffer, 
        AccelerationStructureKHR dst, 
        AccelerationStructureKHR src, 
        CopyAccelerationStructureModeKHR mode) const {
        pfn_CmdCopyAccelerationStructureNV(commandBuffer.get(),
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
        DeviceSize scratchOffset) const {
        pfn_CmdBuildAccelerationStructureNV(commandBuffer.get(),
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
        uint32_t depth) const {
        pfn_CmdTraceRaysNV(commandBuffer.get(),
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
        void* pData) const {
        return static_cast<Result>(pfn_GetAccelerationStructureHandleNV(device.get(),
            accelerationStructure.get(),
            dataSize,
            reinterpret_cast<void*>(pData)));
    }
    [[nodiscard]] Result CreateRayTracingPipelinesNV(PipelineCache pipelineCache, 
        uint32_t createInfoCount, 
        const RayTracingPipelineCreateInfoNV* pCreateInfos, 
        const AllocationCallbacks* pAllocator, 
        Pipeline* pPipelines) const {
        return static_cast<Result>(pfn_CreateRayTracingPipelinesNV(device.get(),
            pipelineCache.get(),
            createInfoCount,
            reinterpret_cast<const VkRayTracingPipelineCreateInfoNV*>(pCreateInfos),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPipeline*>(pPipelines)));
    }
#endif //defined(VK_NV_ray_tracing)
#if defined(VK_EXT_external_memory_host)
    [[nodiscard]] expected<MemoryHostPointerPropertiesEXT> GetMemoryHostPointerPropertiesEXT(ExternalMemoryHandleTypeFlagBits handleType, 
        const void* pHostPointer) const {
        MemoryHostPointerPropertiesEXT pMemoryHostPointerProperties;
        vk::Result result = static_cast<Result>(pfn_GetMemoryHostPointerPropertiesEXT(device.get(),
            static_cast<VkExternalMemoryHandleTypeFlagBits>(handleType),
            reinterpret_cast<const void*>(pHostPointer),
            reinterpret_cast<VkMemoryHostPointerPropertiesEXT*>(&pMemoryHostPointerProperties)));
        return expected<MemoryHostPointerPropertiesEXT>(pMemoryHostPointerProperties, result);
    }
#endif //defined(VK_EXT_external_memory_host)
#if defined(VK_AMD_buffer_marker)
    void CmdWriteBufferMarkerAMD(CommandBuffer commandBuffer, 
        PipelineStageFlagBits pipelineStage, 
        Buffer dstBuffer, 
        DeviceSize dstOffset, 
        uint32_t marker) const {
        pfn_CmdWriteBufferMarkerAMD(commandBuffer.get(),
            static_cast<VkPipelineStageFlagBits>(pipelineStage),
            dstBuffer.get(),
            dstOffset,
            marker);
    }
#endif //defined(VK_AMD_buffer_marker)
#if defined(VK_EXT_calibrated_timestamps)
    [[nodiscard]] expected<uint64_t> GetCalibratedTimestampsEXT(uint32_t timestampCount, 
        const CalibratedTimestampInfoEXT* pTimestampInfos, 
        uint64_t* pTimestamps) const {
        uint64_t pMaxDeviation;
        vk::Result result = static_cast<Result>(pfn_GetCalibratedTimestampsEXT(device.get(),
            timestampCount,
            reinterpret_cast<const VkCalibratedTimestampInfoEXT*>(pTimestampInfos),
            pTimestamps,
            &pMaxDeviation));
        return expected<uint64_t>(pMaxDeviation, result);
    }
#endif //defined(VK_EXT_calibrated_timestamps)
#if defined(VK_NV_mesh_shader)
    void CmdDrawMeshTasksNV(CommandBuffer commandBuffer, 
        uint32_t taskCount, 
        uint32_t firstTask) const {
        pfn_CmdDrawMeshTasksNV(commandBuffer.get(),
            taskCount,
            firstTask);
    }
    void CmdDrawMeshTasksIndirectNV(CommandBuffer commandBuffer, 
        Buffer buffer, 
        DeviceSize offset, 
        uint32_t drawCount, 
        uint32_t stride) const {
        pfn_CmdDrawMeshTasksIndirectNV(commandBuffer.get(),
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
        uint32_t stride) const {
        pfn_CmdDrawMeshTasksIndirectCountNV(commandBuffer.get(),
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
        const Rect2D* pExclusiveScissors) const {
        pfn_CmdSetExclusiveScissorNV(commandBuffer.get(),
            firstExclusiveScissor,
            exclusiveScissorCount,
            reinterpret_cast<const VkRect2D*>(pExclusiveScissors));
    }
#endif //defined(VK_NV_scissor_exclusive)
#if defined(VK_NV_device_diagnostic_checkpoints)
    void CmdSetCheckpointNV(CommandBuffer commandBuffer, 
        const void* pCheckpointMarker) const {
        pfn_CmdSetCheckpointNV(commandBuffer.get(),
            reinterpret_cast<const void*>(pCheckpointMarker));
    }
    [[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetQueueCheckpointDataNV(Queue queue) const {
        uint32_t pCheckpointDataCount = 0;
        pfn_GetQueueCheckpointDataNV(queue.get(),
            &pCheckpointDataCount,
            nullptr);
        detail::fixed_vector<CheckpointDataNV> pCheckpointData{pCheckpointDataCount};
        pfn_GetQueueCheckpointDataNV(queue.get(),
            &pCheckpointDataCount,
            reinterpret_cast<VkCheckpointDataNV*>(pCheckpointData.data()));
        if (pCheckpointDataCount < pCheckpointData.size()) pCheckpointData.shrink(pCheckpointDataCount);
        return pCheckpointData;
    }
#endif //defined(VK_NV_device_diagnostic_checkpoints)
#if defined(VK_INTEL_performance_query)
    [[nodiscard]] Result InitializePerformanceApiINTEL(const InitializePerformanceApiInfoINTEL&  pInitializeInfo) const {
        return static_cast<Result>(pfn_InitializePerformanceApiINTEL(device.get(),
            reinterpret_cast<const VkInitializePerformanceApiInfoINTEL*>(&pInitializeInfo)));
    }
    void UninitializePerformanceApiINTEL() const {
        pfn_UninitializePerformanceApiINTEL(device.get());
    }
    [[nodiscard]] Result CmdSetPerformanceMarkerINTEL(CommandBuffer commandBuffer, 
        const PerformanceMarkerInfoINTEL&  pMarkerInfo) const {
        return static_cast<Result>(pfn_CmdSetPerformanceMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceStreamMarkerINTEL(CommandBuffer commandBuffer, 
        const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const {
        return static_cast<Result>(pfn_CmdSetPerformanceStreamMarkerINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceStreamMarkerInfoINTEL*>(&pMarkerInfo)));
    }
    [[nodiscard]] Result CmdSetPerformanceOverrideINTEL(CommandBuffer commandBuffer, 
        const PerformanceOverrideInfoINTEL&  pOverrideInfo) const {
        return static_cast<Result>(pfn_CmdSetPerformanceOverrideINTEL(commandBuffer.get(),
            reinterpret_cast<const VkPerformanceOverrideInfoINTEL*>(&pOverrideInfo)));
    }
    [[nodiscard]] expected<PerformanceConfigurationINTEL> AcquirePerformanceConfigurationINTEL(const PerformanceConfigurationAcquireInfoINTEL&  pAcquireInfo) const {
        PerformanceConfigurationINTEL pConfiguration;
        vk::Result result = static_cast<Result>(pfn_AcquirePerformanceConfigurationINTEL(device.get(),
            reinterpret_cast<const VkPerformanceConfigurationAcquireInfoINTEL*>(&pAcquireInfo),
            reinterpret_cast<VkPerformanceConfigurationINTEL*>(&pConfiguration)));
        return expected<PerformanceConfigurationINTEL>(pConfiguration, result);
    }
    [[nodiscard]] Result ReleasePerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) const {
        return static_cast<Result>(pfn_ReleasePerformanceConfigurationINTEL(device.get(),
            configuration.get()));
    }
    [[nodiscard]] Result QueueSetPerformanceConfigurationINTEL(Queue queue, 
        PerformanceConfigurationINTEL configuration) const {
        return static_cast<Result>(pfn_QueueSetPerformanceConfigurationINTEL(queue.get(),
            configuration.get()));
    }
    [[nodiscard]] expected<PerformanceValueINTEL> GetPerformanceParameterINTEL(PerformanceParameterTypeINTEL parameter) const {
        PerformanceValueINTEL pValue;
        vk::Result result = static_cast<Result>(pfn_GetPerformanceParameterINTEL(device.get(),
            static_cast<VkPerformanceParameterTypeINTEL>(parameter),
            reinterpret_cast<VkPerformanceValueINTEL*>(&pValue)));
        return expected<PerformanceValueINTEL>(pValue, result);
    }
#endif //defined(VK_INTEL_performance_query)
#if defined(VK_AMD_display_native_hdr)
    void SetLocalDimmingAMD(SwapchainKHR swapChain, 
        Bool32 localDimmingEnable) const {
        pfn_SetLocalDimmingAMD(device.get(),
            swapChain.get(),
            localDimmingEnable);
    }
#endif //defined(VK_AMD_display_native_hdr)
#if defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
    [[nodiscard]] Result AcquireFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const {
        return static_cast<Result>(pfn_AcquireFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
    [[nodiscard]] Result ReleaseFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const {
        return static_cast<Result>(pfn_ReleaseFullScreenExclusiveModeEXT(device.get(),
            swapchain.get()));
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && (defined(VK_EXT_full_screen_exclusive))
#if defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
    [[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        DeviceGroupPresentModeFlagsKHR pModes;
        vk::Result result = static_cast<Result>(pfn_GetDeviceGroupSurfacePresentModes2EXT(device.get(),
            reinterpret_cast<const VkPhysicalDeviceSurfaceInfo2KHR*>(&pSurfaceInfo),
            reinterpret_cast<VkDeviceGroupPresentModeFlagsKHR*>(&pModes)));
        return expected<DeviceGroupPresentModeFlagsKHR>(pModes, result);
    }
#endif //defined(VK_USE_PLATFORM_WIN32_KHR) && ((defined(VK_EXT_full_screen_exclusive) && defined(VK_KHR_device_group)) || (defined(VK_EXT_full_screen_exclusive) && defined(VK_VERSION_1_1)))
#if defined(VK_EXT_line_rasterization)
    void CmdSetLineStippleEXT(CommandBuffer commandBuffer, 
        uint32_t lineStippleFactor, 
        uint16_t lineStipplePattern) const {
        pfn_CmdSetLineStippleEXT(commandBuffer.get(),
            lineStippleFactor,
            lineStipplePattern);
    }
#endif //defined(VK_EXT_line_rasterization)
#if defined(VK_EXT_extended_dynamic_state)
    void CmdSetCullModeEXT(CommandBuffer commandBuffer, 
        CullModeFlags cullMode) const {
        pfn_CmdSetCullModeEXT(commandBuffer.get(),
            static_cast<VkCullModeFlags>(cullMode));
    }
    void CmdSetFrontFaceEXT(CommandBuffer commandBuffer, 
        FrontFace frontFace) const {
        pfn_CmdSetFrontFaceEXT(commandBuffer.get(),
            static_cast<VkFrontFace>(frontFace));
    }
    void CmdSetPrimitiveTopologyEXT(CommandBuffer commandBuffer, 
        PrimitiveTopology primitiveTopology) const {
        pfn_CmdSetPrimitiveTopologyEXT(commandBuffer.get(),
            static_cast<VkPrimitiveTopology>(primitiveTopology));
    }
    void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer, 
        uint32_t viewportCount, 
        const Viewport* pViewports) const {
        pfn_CmdSetViewportWithCountEXT(commandBuffer.get(),
            viewportCount,
            reinterpret_cast<const VkViewport*>(pViewports));
    }
    void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer, 
        uint32_t scissorCount, 
        const Rect2D* pScissors) const {
        pfn_CmdSetScissorWithCountEXT(commandBuffer.get(),
            scissorCount,
            reinterpret_cast<const VkRect2D*>(pScissors));
    }
    void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer, 
        uint32_t firstBinding, 
        uint32_t bindingCount, 
        const Buffer* pBuffers, 
        const DeviceSize* pOffsets, 
        const DeviceSize* pSizes, 
        const DeviceSize* pStrides) const {
        pfn_CmdBindVertexBuffers2EXT(commandBuffer.get(),
            firstBinding,
            bindingCount,
            reinterpret_cast<const VkBuffer*>(pBuffers),
            pOffsets,
            pSizes,
            pStrides);
    }
    void CmdSetDepthTestEnableEXT(CommandBuffer commandBuffer, 
        Bool32 depthTestEnable) const {
        pfn_CmdSetDepthTestEnableEXT(commandBuffer.get(),
            depthTestEnable);
    }
    void CmdSetDepthWriteEnableEXT(CommandBuffer commandBuffer, 
        Bool32 depthWriteEnable) const {
        pfn_CmdSetDepthWriteEnableEXT(commandBuffer.get(),
            depthWriteEnable);
    }
    void CmdSetDepthCompareOpEXT(CommandBuffer commandBuffer, 
        CompareOp depthCompareOp) const {
        pfn_CmdSetDepthCompareOpEXT(commandBuffer.get(),
            static_cast<VkCompareOp>(depthCompareOp));
    }
    void CmdSetDepthBoundsTestEnableEXT(CommandBuffer commandBuffer, 
        Bool32 depthBoundsTestEnable) const {
        pfn_CmdSetDepthBoundsTestEnableEXT(commandBuffer.get(),
            depthBoundsTestEnable);
    }
    void CmdSetStencilTestEnableEXT(CommandBuffer commandBuffer, 
        Bool32 stencilTestEnable) const {
        pfn_CmdSetStencilTestEnableEXT(commandBuffer.get(),
            stencilTestEnable);
    }
    void CmdSetStencilOpEXT(CommandBuffer commandBuffer, 
        StencilFaceFlags faceMask, 
        StencilOp failOp, 
        StencilOp passOp, 
        StencilOp depthFailOp, 
        CompareOp compareOp) const {
        pfn_CmdSetStencilOpEXT(commandBuffer.get(),
            static_cast<VkStencilFaceFlags>(faceMask),
            static_cast<VkStencilOp>(failOp),
            static_cast<VkStencilOp>(passOp),
            static_cast<VkStencilOp>(depthFailOp),
            static_cast<VkCompareOp>(compareOp));
    }
#endif //defined(VK_EXT_extended_dynamic_state)
#if defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
    [[nodiscard]] expected<DeferredOperationKHR> CreateDeferredOperationKHR(const AllocationCallbacks* pAllocator = nullptr) const {
        DeferredOperationKHR pDeferredOperation;
        vk::Result result = static_cast<Result>(pfn_CreateDeferredOperationKHR(device.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkDeferredOperationKHR*>(&pDeferredOperation)));
        return expected<DeferredOperationKHR>(pDeferredOperation, result);
    }
    void DestroyDeferredOperationKHR(DeferredOperationKHR operation, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyDeferredOperationKHR(device.get(),
            operation.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] uint32_t GetDeferredOperationMaxConcurrencyKHR(DeferredOperationKHR operation) const {
        return pfn_GetDeferredOperationMaxConcurrencyKHR(device.get(),
            operation.get());
    }
    [[nodiscard]] Result GetDeferredOperationResultKHR(DeferredOperationKHR operation) const {
        return static_cast<Result>(pfn_GetDeferredOperationResultKHR(device.get(),
            operation.get()));
    }
    [[nodiscard]] Result DeferredOperationJoinKHR(DeferredOperationKHR operation) const {
        return static_cast<Result>(pfn_DeferredOperationJoinKHR(device.get(),
            operation.get()));
    }
#endif //defined(VK_ENABLE_BETA_EXTENSIONS) && (defined(VK_KHR_deferred_host_operations))
#if defined(VK_KHR_pipeline_executable_properties)
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutablePropertiesKHR>> GetPipelineExecutablePropertiesKHR(const PipelineInfoKHR&  pPipelineInfo) const {
        uint32_t pExecutableCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPipelineExecutablePropertiesKHR(device.get(),
            reinterpret_cast<const VkPipelineInfoKHR*>(&pPipelineInfo),
            &pExecutableCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutablePropertiesKHR>{}, result);
        detail::fixed_vector<PipelineExecutablePropertiesKHR> pProperties{pExecutableCount};
        result = static_cast<Result>(pfn_GetPipelineExecutablePropertiesKHR(device.get(),
            reinterpret_cast<const VkPipelineInfoKHR*>(&pPipelineInfo),
            &pExecutableCount,
            reinterpret_cast<VkPipelineExecutablePropertiesKHR*>(pProperties.data())));
        if (pExecutableCount < pProperties.size()) pProperties.shrink(pExecutableCount);
        return expected(std::move(pProperties), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutableStatisticKHR>> GetPipelineExecutableStatisticsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const {
        uint32_t pStatisticCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPipelineExecutableStatisticsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pStatisticCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutableStatisticKHR>{}, result);
        detail::fixed_vector<PipelineExecutableStatisticKHR> pStatistics{pStatisticCount};
        result = static_cast<Result>(pfn_GetPipelineExecutableStatisticsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pStatisticCount,
            reinterpret_cast<VkPipelineExecutableStatisticKHR*>(pStatistics.data())));
        if (pStatisticCount < pStatistics.size()) pStatistics.shrink(pStatisticCount);
        return expected(std::move(pStatistics), result);
    }
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutableInternalRepresentationKHR>> GetPipelineExecutableInternalRepresentationsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const {
        uint32_t pInternalRepresentationCount = 0;
        vk::Result result = static_cast<Result>(pfn_GetPipelineExecutableInternalRepresentationsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pInternalRepresentationCount,
            nullptr));
        if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutableInternalRepresentationKHR>{}, result);
        detail::fixed_vector<PipelineExecutableInternalRepresentationKHR> pInternalRepresentations{pInternalRepresentationCount};
        result = static_cast<Result>(pfn_GetPipelineExecutableInternalRepresentationsKHR(device.get(),
            reinterpret_cast<const VkPipelineExecutableInfoKHR*>(&pExecutableInfo),
            &pInternalRepresentationCount,
            reinterpret_cast<VkPipelineExecutableInternalRepresentationKHR*>(pInternalRepresentations.data())));
        if (pInternalRepresentationCount < pInternalRepresentations.size()) pInternalRepresentations.shrink(pInternalRepresentationCount);
        return expected(std::move(pInternalRepresentations), result);
    }
#endif //defined(VK_KHR_pipeline_executable_properties)
#if defined(VK_NV_device_generated_commands)
    void CmdExecuteGeneratedCommandsNV(CommandBuffer commandBuffer, 
        Bool32 isPreprocessed, 
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
        pfn_CmdExecuteGeneratedCommandsNV(commandBuffer.get(),
            isPreprocessed,
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdPreprocessGeneratedCommandsNV(CommandBuffer commandBuffer, 
        const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
        pfn_CmdPreprocessGeneratedCommandsNV(commandBuffer.get(),
            reinterpret_cast<const VkGeneratedCommandsInfoNV*>(&pGeneratedCommandsInfo));
    }
    void CmdBindPipelineShaderGroupNV(CommandBuffer commandBuffer, 
        PipelineBindPoint pipelineBindPoint, 
        Pipeline pipeline, 
        uint32_t groupIndex) const {
        pfn_CmdBindPipelineShaderGroupNV(commandBuffer.get(),
            static_cast<VkPipelineBindPoint>(pipelineBindPoint),
            pipeline.get(),
            groupIndex);
    }
    [[nodiscard]] MemoryRequirements2 GetGeneratedCommandsMemoryRequirementsNV(const GeneratedCommandsMemoryRequirementsInfoNV&  pInfo) const {
        MemoryRequirements2 pMemoryRequirements;
        pfn_GetGeneratedCommandsMemoryRequirementsNV(device.get(),
            reinterpret_cast<const VkGeneratedCommandsMemoryRequirementsInfoNV*>(&pInfo),
            reinterpret_cast<VkMemoryRequirements2*>(&pMemoryRequirements));
        return pMemoryRequirements;
    }
    [[nodiscard]] expected<IndirectCommandsLayoutNV> CreateIndirectCommandsLayoutNV(const IndirectCommandsLayoutCreateInfoNV&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        IndirectCommandsLayoutNV pIndirectCommandsLayout;
        vk::Result result = static_cast<Result>(pfn_CreateIndirectCommandsLayoutNV(device.get(),
            reinterpret_cast<const VkIndirectCommandsLayoutCreateInfoNV*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkIndirectCommandsLayoutNV*>(&pIndirectCommandsLayout)));
        return expected<IndirectCommandsLayoutNV>(pIndirectCommandsLayout, result);
    }
    void DestroyIndirectCommandsLayoutNV(IndirectCommandsLayoutNV indirectCommandsLayout, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyIndirectCommandsLayoutNV(device.get(),
            indirectCommandsLayout.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
#endif //defined(VK_NV_device_generated_commands)
#if defined(VK_EXT_private_data)
    [[nodiscard]] expected<PrivateDataSlotEXT> CreatePrivateDataSlotEXT(const PrivateDataSlotCreateInfoEXT&  pCreateInfo, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        PrivateDataSlotEXT pPrivateDataSlot;
        vk::Result result = static_cast<Result>(pfn_CreatePrivateDataSlotEXT(device.get(),
            reinterpret_cast<const VkPrivateDataSlotCreateInfoEXT*>(&pCreateInfo),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator),
            reinterpret_cast<VkPrivateDataSlotEXT*>(&pPrivateDataSlot)));
        return expected<PrivateDataSlotEXT>(pPrivateDataSlot, result);
    }
    void DestroyPrivateDataSlotEXT(PrivateDataSlotEXT privateDataSlot, 
        const AllocationCallbacks* pAllocator = nullptr) const {
        pfn_DestroyPrivateDataSlotEXT(device.get(),
            privateDataSlot.get(),
            reinterpret_cast<const VkAllocationCallbacks*>(pAllocator));
    }
    [[nodiscard]] Result SetPrivateDataEXT(ObjectType objectType, 
        uint64_t objectHandle, 
        PrivateDataSlotEXT privateDataSlot, 
        uint64_t data) const {
        return static_cast<Result>(pfn_SetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            data));
    }
    [[nodiscard]] uint64_t GetPrivateDataEXT(ObjectType objectType, 
        uint64_t objectHandle, 
        PrivateDataSlotEXT privateDataSlot) const {
        uint64_t pData;
        pfn_GetPrivateDataEXT(device.get(),
            static_cast<VkObjectType>(objectType),
            objectHandle,
            privateDataSlot.get(),
            &pData);
        return pData;
    }
#endif //defined(VK_EXT_private_data)
#if defined(VK_KHR_copy_commands2)
    void CmdCopyBuffer2KHR(CommandBuffer commandBuffer, 
        const CopyBufferInfo2KHR&  pCopyBufferInfo) const {
        pfn_CmdCopyBuffer2KHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyBufferInfo2KHR*>(&pCopyBufferInfo));
    }
    void CmdCopyImage2KHR(CommandBuffer commandBuffer, 
        const CopyImageInfo2KHR&  pCopyImageInfo) const {
        pfn_CmdCopyImage2KHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyImageInfo2KHR*>(&pCopyImageInfo));
    }
    void CmdBlitImage2KHR(CommandBuffer commandBuffer, 
        const BlitImageInfo2KHR&  pBlitImageInfo) const {
        pfn_CmdBlitImage2KHR(commandBuffer.get(),
            reinterpret_cast<const VkBlitImageInfo2KHR*>(&pBlitImageInfo));
    }
    void CmdCopyBufferToImage2KHR(CommandBuffer commandBuffer, 
        const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const {
        pfn_CmdCopyBufferToImage2KHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyBufferToImageInfo2KHR*>(&pCopyBufferToImageInfo));
    }
    void CmdCopyImageToBuffer2KHR(CommandBuffer commandBuffer, 
        const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const {
        pfn_CmdCopyImageToBuffer2KHR(commandBuffer.get(),
            reinterpret_cast<const VkCopyImageToBufferInfo2KHR*>(&pCopyImageToBufferInfo));
    }
    void CmdResolveImage2KHR(CommandBuffer commandBuffer, 
        const ResolveImageInfo2KHR&  pResolveImageInfo) const {
        pfn_CmdResolveImage2KHR(commandBuffer.get(),
            reinterpret_cast<const VkResolveImageInfo2KHR*>(&pResolveImageInfo));
    }
#endif //defined(VK_KHR_copy_commands2)
    explicit DeviceFunctions() noexcept {}
    explicit DeviceFunctions(InstanceFunctions const& instance_functions, Device device) noexcept 
        :device(device) { 
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
#if defined(VK_KHR_copy_commands2)
        pfn_CmdCopyBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyBuffer2KHR>(get_device_proc_addr(device.get(),"vkCmdCopyBuffer2KHR"));
        pfn_CmdCopyImage2KHR = reinterpret_cast<PFN_vkCmdCopyImage2KHR>(get_device_proc_addr(device.get(),"vkCmdCopyImage2KHR"));
        pfn_CmdBlitImage2KHR = reinterpret_cast<PFN_vkCmdBlitImage2KHR>(get_device_proc_addr(device.get(),"vkCmdBlitImage2KHR"));
        pfn_CmdCopyBufferToImage2KHR = reinterpret_cast<PFN_vkCmdCopyBufferToImage2KHR>(get_device_proc_addr(device.get(),"vkCmdCopyBufferToImage2KHR"));
        pfn_CmdCopyImageToBuffer2KHR = reinterpret_cast<PFN_vkCmdCopyImageToBuffer2KHR>(get_device_proc_addr(device.get(),"vkCmdCopyImageToBuffer2KHR"));
        pfn_CmdResolveImage2KHR = reinterpret_cast<PFN_vkCmdResolveImage2KHR>(get_device_proc_addr(device.get(),"vkCmdResolveImage2KHR"));
#endif //defined(VK_KHR_copy_commands2)
    };
};
struct PhysicalDeviceFunctions {
    InstanceFunctions const* instance_functions;
    PhysicalDevice physicaldevice;
    PhysicalDeviceFunctions() noexcept {}
    PhysicalDeviceFunctions(InstanceFunctions const& instance_functions, PhysicalDevice const physicaldevice) noexcept
        :instance_functions(&instance_functions), physicaldevice(physicaldevice){}
    [[nodiscard]] PhysicalDeviceProperties GetProperties() const {
        return instance_functions->GetPhysicalDeviceProperties(physicaldevice); }
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetQueueFamilyProperties() const {
        return instance_functions->GetPhysicalDeviceQueueFamilyProperties(physicaldevice); }
    [[nodiscard]] PhysicalDeviceMemoryProperties GetMemoryProperties() const {
        return instance_functions->GetPhysicalDeviceMemoryProperties(physicaldevice); }
    [[nodiscard]] PhysicalDeviceFeatures GetFeatures() const {
        return instance_functions->GetPhysicalDeviceFeatures(physicaldevice); }
    [[nodiscard]] FormatProperties GetFormatProperties(Format format) const {
        return instance_functions->GetPhysicalDeviceFormatProperties(physicaldevice, format); }
    [[nodiscard]] expected<ImageFormatProperties> GetImageFormatProperties(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags) const {
        return instance_functions->GetPhysicalDeviceImageFormatProperties(physicaldevice, format, type, tiling, usage, flags); }
    [[nodiscard]] expected<Device> CreateDevice(const DeviceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const {
        return instance_functions->CreateDevice(physicaldevice, pCreateInfo, pAllocator); }
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(const char* pLayerName) const {
        return instance_functions->EnumerateDeviceExtensionProperties(physicaldevice, pLayerName); }
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetSparseImageFormatProperties(Format format, ImageType type, SampleCountFlagBits samples, ImageUsageFlags usage, ImageTiling tiling) const {
        return instance_functions->GetPhysicalDeviceSparseImageFormatProperties(physicaldevice, format, type, samples, usage, tiling); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetDisplayPropertiesKHR() const {
        return instance_functions->GetPhysicalDeviceDisplayPropertiesKHR(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetDisplayPlanePropertiesKHR() const {
        return instance_functions->GetPhysicalDeviceDisplayPlanePropertiesKHR(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(uint32_t planeIndex) const {
        return instance_functions->GetDisplayPlaneSupportedDisplaysKHR(physicaldevice, planeIndex); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(DisplayKHR display) const {
        return instance_functions->GetDisplayModePropertiesKHR(physicaldevice, display); }
    [[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(DisplayKHR display, const DisplayModeCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const {
        return instance_functions->CreateDisplayModeKHR(physicaldevice, display, pCreateInfo, pAllocator); }
    [[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(DisplayModeKHR mode, uint32_t planeIndex) const {
        return instance_functions->GetDisplayPlaneCapabilitiesKHR(physicaldevice, mode, planeIndex); }
    [[nodiscard]] expected<Bool32> GetSurfaceSupportKHR(uint32_t queueFamilyIndex, SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDeviceSurfaceSupportKHR(physicaldevice, queueFamilyIndex, surface); }
    [[nodiscard]] expected<SurfaceCapabilitiesKHR> GetSurfaceCapabilitiesKHR(SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDeviceSurfaceCapabilitiesKHR(physicaldevice, surface); }
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetSurfaceFormatsKHR(SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDeviceSurfaceFormatsKHR(physicaldevice, surface); }
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModesKHR(SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDeviceSurfacePresentModesKHR(physicaldevice, surface); }
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    [[nodiscard]] wl_display GetWaylandPresentationSupportKHR(uint32_t queueFamilyIndex) const {
        return instance_functions->GetPhysicalDeviceWaylandPresentationSupportKHR(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] VkBool32 GetWin32PresentationSupportKHR(uint32_t queueFamilyIndex) const {
        return instance_functions->GetPhysicalDeviceWin32PresentationSupportKHR(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    [[nodiscard]] VkBool32 GetXlibPresentationSupportKHR(uint32_t queueFamilyIndex, Display&  dpy, VisualID visualID) const {
        return instance_functions->GetPhysicalDeviceXlibPresentationSupportKHR(physicaldevice, queueFamilyIndex, dpy, visualID); }
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    [[nodiscard]] VkBool32 GetXcbPresentationSupportKHR(uint32_t queueFamilyIndex, xcb_connection_t&  connection, xcb_visualid_t visual_id) const {
        return instance_functions->GetPhysicalDeviceXcbPresentationSupportKHR(physicaldevice, queueFamilyIndex, connection, visual_id); }
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] IDirectFB GetDirectFBPresentationSupportEXT(uint32_t queueFamilyIndex) const {
        return instance_functions->GetPhysicalDeviceDirectFBPresentationSupportEXT(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetExternalImageFormatPropertiesNV(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags, ExternalMemoryHandleTypeFlagsNV externalHandleType) const {
        return instance_functions->GetPhysicalDeviceExternalImageFormatPropertiesNV(physicaldevice, format, type, tiling, usage, flags, externalHandleType); }
    [[nodiscard]] PhysicalDeviceFeatures2 GetFeatures2() const {
        return instance_functions->GetPhysicalDeviceFeatures2(physicaldevice); }
    [[nodiscard]] PhysicalDeviceProperties2 GetProperties2() const {
        return instance_functions->GetPhysicalDeviceProperties2(physicaldevice); }
    [[nodiscard]] FormatProperties2 GetFormatProperties2(Format format) const {
        return instance_functions->GetPhysicalDeviceFormatProperties2(physicaldevice, format); }
    [[nodiscard]] expected<ImageFormatProperties2> GetImageFormatProperties2(const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const {
        return instance_functions->GetPhysicalDeviceImageFormatProperties2(physicaldevice, pImageFormatInfo); }
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetQueueFamilyProperties2() const {
        return instance_functions->GetPhysicalDeviceQueueFamilyProperties2(physicaldevice); }
    [[nodiscard]] PhysicalDeviceMemoryProperties2 GetMemoryProperties2() const {
        return instance_functions->GetPhysicalDeviceMemoryProperties2(physicaldevice); }
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetSparseImageFormatProperties2(const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const {
        return instance_functions->GetPhysicalDeviceSparseImageFormatProperties2(physicaldevice, pFormatInfo); }
    [[nodiscard]] ExternalBufferProperties GetExternalBufferProperties(const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const {
        return instance_functions->GetPhysicalDeviceExternalBufferProperties(physicaldevice, pExternalBufferInfo); }
    [[nodiscard]] ExternalSemaphoreProperties GetExternalSemaphoreProperties(const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const {
        return instance_functions->GetPhysicalDeviceExternalSemaphoreProperties(physicaldevice, pExternalSemaphoreInfo); }
    [[nodiscard]] ExternalFenceProperties GetExternalFenceProperties(const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const {
        return instance_functions->GetPhysicalDeviceExternalFenceProperties(physicaldevice, pExternalFenceInfo); }
    [[nodiscard]] Result ReleaseDisplayEXT(DisplayKHR display) const {
        return instance_functions->ReleaseDisplayEXT(physicaldevice, display); }
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] Result AcquireXlibDisplayEXT(Display&  dpy, DisplayKHR display) const {
        return instance_functions->AcquireXlibDisplayEXT(physicaldevice, dpy, display); }
    [[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(Display&  dpy, RROutput rrOutput) const {
        return instance_functions->GetRandROutputDisplayEXT(physicaldevice, dpy, rrOutput); }
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] expected<SurfaceCapabilities2EXT> GetSurfaceCapabilities2EXT(SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDeviceSurfaceCapabilities2EXT(physicaldevice, surface); }
    [[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPresentRectanglesKHR(SurfaceKHR surface) const {
        return instance_functions->GetPhysicalDevicePresentRectanglesKHR(physicaldevice, surface); }
    [[nodiscard]] MultisamplePropertiesEXT GetMultisamplePropertiesEXT(SampleCountFlagBits samples) const {
        return instance_functions->GetPhysicalDeviceMultisamplePropertiesEXT(physicaldevice, samples); }
    [[nodiscard]] expected<SurfaceCapabilities2KHR> GetSurfaceCapabilities2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        return instance_functions->GetPhysicalDeviceSurfaceCapabilities2KHR(physicaldevice, pSurfaceInfo); }
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetSurfaceFormats2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        return instance_functions->GetPhysicalDeviceSurfaceFormats2KHR(physicaldevice, pSurfaceInfo); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetDisplayProperties2KHR() const {
        return instance_functions->GetPhysicalDeviceDisplayProperties2KHR(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetDisplayPlaneProperties2KHR() const {
        return instance_functions->GetPhysicalDeviceDisplayPlaneProperties2KHR(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(DisplayKHR display) const {
        return instance_functions->GetDisplayModeProperties2KHR(physicaldevice, display); }
    [[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const {
        return instance_functions->GetDisplayPlaneCapabilities2KHR(physicaldevice, pDisplayPlaneInfo); }
    [[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetCalibrateableTimeDomainsEXT() const {
        return instance_functions->GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetCooperativeMatrixPropertiesNV() const {
        return instance_functions->GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicaldevice); }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
        return instance_functions->GetPhysicalDeviceSurfacePresentModes2EXT(physicaldevice, pSurfaceInfo); }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(uint32_t queueFamilyIndex, uint32_t&  pCounterCount, PerformanceCounterKHR* pCounters, PerformanceCounterDescriptionKHR* pCounterDescriptions) const {
        return instance_functions->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicaldevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions); }
    [[nodiscard]] uint32_t GetQueueFamilyPerformanceQueryPassesKHR(const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const {
        return instance_functions->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicaldevice, pPerformanceQueryCreateInfo); }
    [[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetSupportedFramebufferMixedSamplesCombinationsNV() const {
        return instance_functions->GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicaldevice); }
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetToolPropertiesEXT() const {
        return instance_functions->GetPhysicalDeviceToolPropertiesEXT(physicaldevice); }
};
struct QueueFunctions {
    DeviceFunctions const* device_functions;
    Queue queue;
    QueueFunctions() noexcept {}
    QueueFunctions(DeviceFunctions const& device_functions, Queue const queue) noexcept
        :device_functions(&device_functions), queue(queue){}
    [[nodiscard]] Result Submit(uint32_t submitCount, const SubmitInfo* pSubmits, Fence fence) const {
        return device_functions->QueueSubmit(queue, submitCount, pSubmits, fence); }
    [[nodiscard]] Result WaitIdle() const {
        return device_functions->QueueWaitIdle(queue); }
    [[nodiscard]] Result BindSparse(uint32_t bindInfoCount, const BindSparseInfo* pBindInfo, Fence fence) const {
        return device_functions->QueueBindSparse(queue, bindInfoCount, pBindInfo, fence); }
    [[nodiscard]] Result PresentKHR(const PresentInfoKHR&  pPresentInfo) const {
        return device_functions->QueuePresentKHR(queue, pPresentInfo); }
    void BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
        device_functions->QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo); }
    void EndDebugUtilsLabelEXT() const {
        device_functions->QueueEndDebugUtilsLabelEXT(queue); }
    void InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
        device_functions->QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo); }
    [[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetCheckpointDataNV() const {
        return device_functions->GetQueueCheckpointDataNV(queue); }
    [[nodiscard]] Result SetPerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) const {
        return device_functions->QueueSetPerformanceConfigurationINTEL(queue, configuration); }
};
struct CommandBufferFunctions {
    DeviceFunctions const* device_functions;
    CommandBuffer commandbuffer;
    CommandBufferFunctions() noexcept {}
    CommandBufferFunctions(DeviceFunctions const& device_functions, CommandBuffer const commandbuffer) noexcept
        :device_functions(&device_functions), commandbuffer(commandbuffer){}
    [[nodiscard]] Result Begin(const CommandBufferBeginInfo&  pBeginInfo) const {
        return device_functions->BeginCommandBuffer(commandbuffer, pBeginInfo); }
    [[nodiscard]] Result End() const {
        return device_functions->EndCommandBuffer(commandbuffer); }
    [[nodiscard]] Result Reset(CommandBufferResetFlags flags) const {
        return device_functions->ResetCommandBuffer(commandbuffer, flags); }
    CommandBufferFunctions const& BindPipeline(PipelineBindPoint pipelineBindPoint, Pipeline pipeline) const {
        device_functions->CmdBindPipeline(commandbuffer, pipelineBindPoint, pipeline);
        return *this; }
    CommandBufferFunctions const& SetViewport(uint32_t firstViewport, uint32_t viewportCount, const Viewport* pViewports) const {
        device_functions->CmdSetViewport(commandbuffer, firstViewport, viewportCount, pViewports);
        return *this; }
    CommandBufferFunctions const& SetScissor(uint32_t firstScissor, uint32_t scissorCount, const Rect2D* pScissors) const {
        device_functions->CmdSetScissor(commandbuffer, firstScissor, scissorCount, pScissors);
        return *this; }
    CommandBufferFunctions const& SetLineWidth(float lineWidth) const {
        device_functions->CmdSetLineWidth(commandbuffer, lineWidth);
        return *this; }
    CommandBufferFunctions const& SetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const {
        device_functions->CmdSetDepthBias(commandbuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
        return *this; }
    CommandBufferFunctions const& SetBlendConstants(const float blendConstants[4]) const {
        device_functions->CmdSetBlendConstants(commandbuffer, blendConstants);
        return *this; }
    CommandBufferFunctions const& SetDepthBounds(float minDepthBounds, float maxDepthBounds) const {
        device_functions->CmdSetDepthBounds(commandbuffer, minDepthBounds, maxDepthBounds);
        return *this; }
    CommandBufferFunctions const& SetStencilCompareMask(StencilFaceFlags faceMask, uint32_t compareMask) const {
        device_functions->CmdSetStencilCompareMask(commandbuffer, faceMask, compareMask);
        return *this; }
    CommandBufferFunctions const& SetStencilWriteMask(StencilFaceFlags faceMask, uint32_t writeMask) const {
        device_functions->CmdSetStencilWriteMask(commandbuffer, faceMask, writeMask);
        return *this; }
    CommandBufferFunctions const& SetStencilReference(StencilFaceFlags faceMask, uint32_t reference) const {
        device_functions->CmdSetStencilReference(commandbuffer, faceMask, reference);
        return *this; }
    CommandBufferFunctions const& BindDescriptorSets(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) const {
        device_functions->CmdBindDescriptorSets(commandbuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
        return *this; }
    CommandBufferFunctions const& BindIndexBuffer(Buffer buffer, DeviceSize offset, IndexType indexType) const {
        device_functions->CmdBindIndexBuffer(commandbuffer, buffer, offset, indexType);
        return *this; }
    CommandBufferFunctions const& BindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets) const {
        device_functions->CmdBindVertexBuffers(commandbuffer, firstBinding, bindingCount, pBuffers, pOffsets);
        return *this; }
    CommandBufferFunctions const& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const {
        device_functions->CmdDraw(commandbuffer, vertexCount, instanceCount, firstVertex, firstInstance);
        return *this; }
    CommandBufferFunctions const& DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const {
        device_functions->CmdDrawIndexed(commandbuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
        return *this; }
    CommandBufferFunctions const& DrawIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
        device_functions->CmdDrawIndirect(commandbuffer, buffer, offset, drawCount, stride);
        return *this; }
    CommandBufferFunctions const& DrawIndexedIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
        device_functions->CmdDrawIndexedIndirect(commandbuffer, buffer, offset, drawCount, stride);
        return *this; }
    CommandBufferFunctions const& Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const {
        device_functions->CmdDispatch(commandbuffer, groupCountX, groupCountY, groupCountZ);
        return *this; }
    CommandBufferFunctions const& DispatchIndirect(Buffer buffer, DeviceSize offset) const {
        device_functions->CmdDispatchIndirect(commandbuffer, buffer, offset);
        return *this; }
    CommandBufferFunctions const& CopyBuffer(Buffer srcBuffer, Buffer dstBuffer, uint32_t regionCount, const BufferCopy* pRegions) const {
        device_functions->CmdCopyBuffer(commandbuffer, srcBuffer, dstBuffer, regionCount, pRegions);
        return *this; }
    CommandBufferFunctions const& CopyImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageCopy* pRegions) const {
        device_functions->CmdCopyImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
        return *this; }
    CommandBufferFunctions const& BlitImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageBlit* pRegions, Filter filter) const {
        device_functions->CmdBlitImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
        return *this; }
    CommandBufferFunctions const& CopyBufferToImage(Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const BufferImageCopy* pRegions) const {
        device_functions->CmdCopyBufferToImage(commandbuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
        return *this; }
    CommandBufferFunctions const& CopyImageToBuffer(Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, uint32_t regionCount, const BufferImageCopy* pRegions) const {
        device_functions->CmdCopyImageToBuffer(commandbuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
        return *this; }
    CommandBufferFunctions const& UpdateBuffer(Buffer dstBuffer, DeviceSize dstOffset, DeviceSize dataSize, const void* pData) const {
        device_functions->CmdUpdateBuffer(commandbuffer, dstBuffer, dstOffset, dataSize, pData);
        return *this; }
    CommandBufferFunctions const& FillBuffer(Buffer dstBuffer, DeviceSize dstOffset, DeviceSize size, uint32_t data) const {
        device_functions->CmdFillBuffer(commandbuffer, dstBuffer, dstOffset, size, data);
        return *this; }
    CommandBufferFunctions const& ClearColorImage(Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const {
        device_functions->CmdClearColorImage(commandbuffer, image, imageLayout, pColor, rangeCount, pRanges);
        return *this; }
    CommandBufferFunctions const& ClearDepthStencilImage(Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const {
        device_functions->CmdClearDepthStencilImage(commandbuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
        return *this; }
    CommandBufferFunctions const& ClearAttachments(uint32_t attachmentCount, const ClearAttachment* pAttachments, uint32_t rectCount, const ClearRect* pRects) const {
        device_functions->CmdClearAttachments(commandbuffer, attachmentCount, pAttachments, rectCount, pRects);
        return *this; }
    CommandBufferFunctions const& ResolveImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageResolve* pRegions) const {
        device_functions->CmdResolveImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
        return *this; }
    CommandBufferFunctions const& SetEvent(Event event, PipelineStageFlags stageMask) const {
        device_functions->CmdSetEvent(commandbuffer, event, stageMask);
        return *this; }
    CommandBufferFunctions const& ResetEvent(Event event, PipelineStageFlags stageMask) const {
        device_functions->CmdResetEvent(commandbuffer, event, stageMask);
        return *this; }
    CommandBufferFunctions const& WaitEvents(uint32_t eventCount, const Event* pEvents, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const {
        device_functions->CmdWaitEvents(commandbuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
        return *this; }
    CommandBufferFunctions const& PipelineBarrier(PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const {
        device_functions->CmdPipelineBarrier(commandbuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
        return *this; }
    CommandBufferFunctions const& BeginQuery(QueryPool queryPool, uint32_t query, QueryControlFlags flags) const {
        device_functions->CmdBeginQuery(commandbuffer, queryPool, query, flags);
        return *this; }
    CommandBufferFunctions const& EndQuery(QueryPool queryPool, uint32_t query) const {
        device_functions->CmdEndQuery(commandbuffer, queryPool, query);
        return *this; }
    CommandBufferFunctions const& BeginConditionalRenderingEXT(const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const {
        device_functions->CmdBeginConditionalRenderingEXT(commandbuffer, pConditionalRenderingBegin);
        return *this; }
    CommandBufferFunctions const& EndConditionalRenderingEXT() const {
        device_functions->CmdEndConditionalRenderingEXT(commandbuffer);
        return *this; }
    CommandBufferFunctions const& ResetQueryPool(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const {
        device_functions->CmdResetQueryPool(commandbuffer, queryPool, firstQuery, queryCount);
        return *this; }
    CommandBufferFunctions const& WriteTimestamp(PipelineStageFlagBits pipelineStage, QueryPool queryPool, uint32_t query) const {
        device_functions->CmdWriteTimestamp(commandbuffer, pipelineStage, queryPool, query);
        return *this; }
    CommandBufferFunctions const& CopyQueryPoolResults(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize stride, QueryResultFlags flags) const {
        device_functions->CmdCopyQueryPoolResults(commandbuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
        return *this; }
    CommandBufferFunctions const& PushConstants(PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) const {
        device_functions->CmdPushConstants(commandbuffer, layout, stageFlags, offset, size, pValues);
        return *this; }
    CommandBufferFunctions const& BeginRenderPass(const RenderPassBeginInfo&  pRenderPassBegin, SubpassContents contents) const {
        device_functions->CmdBeginRenderPass(commandbuffer, pRenderPassBegin, contents);
        return *this; }
    CommandBufferFunctions const& NextSubpass(SubpassContents contents) const {
        device_functions->CmdNextSubpass(commandbuffer, contents);
        return *this; }
    CommandBufferFunctions const& EndRenderPass() const {
        device_functions->CmdEndRenderPass(commandbuffer);
        return *this; }
    CommandBufferFunctions const& ExecuteCommands(uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers) const {
        device_functions->CmdExecuteCommands(commandbuffer, commandBufferCount, pCommandBuffers);
        return *this; }
    CommandBufferFunctions const& DebugMarkerBeginEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
        device_functions->CmdDebugMarkerBeginEXT(commandbuffer, pMarkerInfo);
        return *this; }
    CommandBufferFunctions const& DebugMarkerEndEXT() const {
        device_functions->CmdDebugMarkerEndEXT(commandbuffer);
        return *this; }
    CommandBufferFunctions const& DebugMarkerInsertEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
        device_functions->CmdDebugMarkerInsertEXT(commandbuffer, pMarkerInfo);
        return *this; }
    CommandBufferFunctions const& ExecuteGeneratedCommandsNV(Bool32 isPreprocessed, const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
        device_functions->CmdExecuteGeneratedCommandsNV(commandbuffer, isPreprocessed, pGeneratedCommandsInfo);
        return *this; }
    CommandBufferFunctions const& PreprocessGeneratedCommandsNV(const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
        device_functions->CmdPreprocessGeneratedCommandsNV(commandbuffer, pGeneratedCommandsInfo);
        return *this; }
    CommandBufferFunctions const& BindPipelineShaderGroupNV(PipelineBindPoint pipelineBindPoint, Pipeline pipeline, uint32_t groupIndex) const {
        device_functions->CmdBindPipelineShaderGroupNV(commandbuffer, pipelineBindPoint, pipeline, groupIndex);
        return *this; }
    CommandBufferFunctions const& PushDescriptorSetKHR(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites) const {
        device_functions->CmdPushDescriptorSetKHR(commandbuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
        return *this; }
    CommandBufferFunctions const& SetDeviceMask(uint32_t deviceMask) const {
        device_functions->CmdSetDeviceMask(commandbuffer, deviceMask);
        return *this; }
    CommandBufferFunctions const& DispatchBase(uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const {
        device_functions->CmdDispatchBase(commandbuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
        return *this; }
    CommandBufferFunctions const& PushDescriptorSetWithTemplateKHR(DescriptorUpdateTemplate descriptorUpdateTemplate, PipelineLayout layout, uint32_t set, const void* pData) const {
        device_functions->CmdPushDescriptorSetWithTemplateKHR(commandbuffer, descriptorUpdateTemplate, layout, set, pData);
        return *this; }
    CommandBufferFunctions const& SetViewportWScalingNV(uint32_t firstViewport, uint32_t viewportCount, const ViewportWScalingNV* pViewportWScalings) const {
        device_functions->CmdSetViewportWScalingNV(commandbuffer, firstViewport, viewportCount, pViewportWScalings);
        return *this; }
    CommandBufferFunctions const& SetDiscardRectangleEXT(uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const Rect2D* pDiscardRectangles) const {
        device_functions->CmdSetDiscardRectangleEXT(commandbuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
        return *this; }
    CommandBufferFunctions const& SetSampleLocationsEXT(const SampleLocationsInfoEXT&  pSampleLocationsInfo) const {
        device_functions->CmdSetSampleLocationsEXT(commandbuffer, pSampleLocationsInfo);
        return *this; }
    CommandBufferFunctions const& BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
        device_functions->CmdBeginDebugUtilsLabelEXT(commandbuffer, pLabelInfo);
        return *this; }
    CommandBufferFunctions const& EndDebugUtilsLabelEXT() const {
        device_functions->CmdEndDebugUtilsLabelEXT(commandbuffer);
        return *this; }
    CommandBufferFunctions const& InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
        device_functions->CmdInsertDebugUtilsLabelEXT(commandbuffer, pLabelInfo);
        return *this; }
    CommandBufferFunctions const& WriteBufferMarkerAMD(PipelineStageFlagBits pipelineStage, Buffer dstBuffer, DeviceSize dstOffset, uint32_t marker) const {
        device_functions->CmdWriteBufferMarkerAMD(commandbuffer, pipelineStage, dstBuffer, dstOffset, marker);
        return *this; }
    CommandBufferFunctions const& BeginRenderPass2(const RenderPassBeginInfo&  pRenderPassBegin, const SubpassBeginInfo&  pSubpassBeginInfo) const {
        device_functions->CmdBeginRenderPass2(commandbuffer, pRenderPassBegin, pSubpassBeginInfo);
        return *this; }
    CommandBufferFunctions const& NextSubpass2(const SubpassBeginInfo&  pSubpassBeginInfo, const SubpassEndInfo&  pSubpassEndInfo) const {
        device_functions->CmdNextSubpass2(commandbuffer, pSubpassBeginInfo, pSubpassEndInfo);
        return *this; }
    CommandBufferFunctions const& EndRenderPass2(const SubpassEndInfo&  pSubpassEndInfo) const {
        device_functions->CmdEndRenderPass2(commandbuffer, pSubpassEndInfo);
        return *this; }
    CommandBufferFunctions const& DrawIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
        device_functions->CmdDrawIndirectCount(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
        return *this; }
    CommandBufferFunctions const& DrawIndexedIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
        device_functions->CmdDrawIndexedIndirectCount(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
        return *this; }
    CommandBufferFunctions const& SetCheckpointNV(const void* pCheckpointMarker) const {
        device_functions->CmdSetCheckpointNV(commandbuffer, pCheckpointMarker);
        return *this; }
    CommandBufferFunctions const& BindTransformFeedbackBuffersEXT(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes) const {
        device_functions->CmdBindTransformFeedbackBuffersEXT(commandbuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
        return *this; }
    CommandBufferFunctions const& BeginTransformFeedbackEXT(uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const {
        device_functions->CmdBeginTransformFeedbackEXT(commandbuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
        return *this; }
    CommandBufferFunctions const& EndTransformFeedbackEXT(uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const {
        device_functions->CmdEndTransformFeedbackEXT(commandbuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
        return *this; }
    CommandBufferFunctions const& BeginQueryIndexedEXT(QueryPool queryPool, uint32_t query, QueryControlFlags flags, uint32_t index) const {
        device_functions->CmdBeginQueryIndexedEXT(commandbuffer, queryPool, query, flags, index);
        return *this; }
    CommandBufferFunctions const& EndQueryIndexedEXT(QueryPool queryPool, uint32_t query, uint32_t index) const {
        device_functions->CmdEndQueryIndexedEXT(commandbuffer, queryPool, query, index);
        return *this; }
    CommandBufferFunctions const& DrawIndirectByteCountEXT(uint32_t instanceCount, uint32_t firstInstance, Buffer counterBuffer, DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const {
        device_functions->CmdDrawIndirectByteCountEXT(commandbuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
        return *this; }
    CommandBufferFunctions const& SetExclusiveScissorNV(uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const Rect2D* pExclusiveScissors) const {
        device_functions->CmdSetExclusiveScissorNV(commandbuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
        return *this; }
    CommandBufferFunctions const& BindShadingRateImageNV(ImageView imageView, ImageLayout imageLayout) const {
        device_functions->CmdBindShadingRateImageNV(commandbuffer, imageView, imageLayout);
        return *this; }
    CommandBufferFunctions const& SetViewportShadingRatePaletteNV(uint32_t firstViewport, uint32_t viewportCount, const ShadingRatePaletteNV* pShadingRatePalettes) const {
        device_functions->CmdSetViewportShadingRatePaletteNV(commandbuffer, firstViewport, viewportCount, pShadingRatePalettes);
        return *this; }
    CommandBufferFunctions const& SetCoarseSampleOrderNV(CoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const CoarseSampleOrderCustomNV* pCustomSampleOrders) const {
        device_functions->CmdSetCoarseSampleOrderNV(commandbuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
        return *this; }
    CommandBufferFunctions const& DrawMeshTasksNV(uint32_t taskCount, uint32_t firstTask) const {
        device_functions->CmdDrawMeshTasksNV(commandbuffer, taskCount, firstTask);
        return *this; }
    CommandBufferFunctions const& DrawMeshTasksIndirectNV(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
        device_functions->CmdDrawMeshTasksIndirectNV(commandbuffer, buffer, offset, drawCount, stride);
        return *this; }
    CommandBufferFunctions const& DrawMeshTasksIndirectCountNV(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
        device_functions->CmdDrawMeshTasksIndirectCountNV(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
        return *this; }
    CommandBufferFunctions const& CopyAccelerationStructureNV(AccelerationStructureKHR dst, AccelerationStructureKHR src, CopyAccelerationStructureModeKHR mode) const {
        device_functions->CmdCopyAccelerationStructureNV(commandbuffer, dst, src, mode);
        return *this; }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) const {
        device_functions->CmdCopyAccelerationStructureKHR(commandbuffer, pInfo);
        return *this; }
    CommandBufferFunctions const& CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
        device_functions->CmdCopyAccelerationStructureToMemoryKHR(commandbuffer, pInfo);
        return *this; }
    CommandBufferFunctions const& CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
        device_functions->CmdCopyMemoryToAccelerationStructureKHR(commandbuffer, pInfo);
        return *this; }
    CommandBufferFunctions const& WriteAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const {
        device_functions->CmdWriteAccelerationStructuresPropertiesKHR(commandbuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
        return *this; }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& BuildAccelerationStructureNV(const AccelerationStructureInfoNV&  pInfo, Buffer instanceData, DeviceSize instanceOffset, Bool32 update, AccelerationStructureKHR dst, AccelerationStructureKHR src, Buffer scratch, DeviceSize scratchOffset) const {
        device_functions->CmdBuildAccelerationStructureNV(commandbuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
        return *this; }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) const {
        device_functions->CmdTraceRaysKHR(commandbuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
        return *this; }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysNV(Buffer raygenShaderBindingTableBuffer, DeviceSize raygenShaderBindingOffset, Buffer missShaderBindingTableBuffer, DeviceSize missShaderBindingOffset, DeviceSize missShaderBindingStride, Buffer hitShaderBindingTableBuffer, DeviceSize hitShaderBindingOffset, DeviceSize hitShaderBindingStride, Buffer callableShaderBindingTableBuffer, DeviceSize callableShaderBindingOffset, DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) const {
        device_functions->CmdTraceRaysNV(commandbuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
        return *this; }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysIndirectKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, Buffer buffer, DeviceSize offset) const {
        device_functions->CmdTraceRaysIndirectKHR(commandbuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, buffer, offset);
        return *this; }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result SetPerformanceMarkerINTEL(const PerformanceMarkerInfoINTEL&  pMarkerInfo) const {
        return device_functions->CmdSetPerformanceMarkerINTEL(commandbuffer, pMarkerInfo); }
    [[nodiscard]] Result SetPerformanceStreamMarkerINTEL(const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const {
        return device_functions->CmdSetPerformanceStreamMarkerINTEL(commandbuffer, pMarkerInfo); }
    [[nodiscard]] Result SetPerformanceOverrideINTEL(const PerformanceOverrideInfoINTEL&  pOverrideInfo) const {
        return device_functions->CmdSetPerformanceOverrideINTEL(commandbuffer, pOverrideInfo); }
    CommandBufferFunctions const& SetLineStippleEXT(uint32_t lineStippleFactor, uint16_t lineStipplePattern) const {
        device_functions->CmdSetLineStippleEXT(commandbuffer, lineStippleFactor, lineStipplePattern);
        return *this; }
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& BuildAccelerationStructureKHR(uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const {
        device_functions->CmdBuildAccelerationStructureKHR(commandbuffer, infoCount, pInfos, ppOffsetInfos);
        return *this; }
    CommandBufferFunctions const& BuildAccelerationStructureIndirectKHR(const AccelerationStructureBuildGeometryInfoKHR&  pInfo, Buffer indirectBuffer, DeviceSize indirectOffset, uint32_t indirectStride) const {
        device_functions->CmdBuildAccelerationStructureIndirectKHR(commandbuffer, pInfo, indirectBuffer, indirectOffset, indirectStride);
        return *this; }
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& SetCullModeEXT(CullModeFlags cullMode) const {
        device_functions->CmdSetCullModeEXT(commandbuffer, cullMode);
        return *this; }
    CommandBufferFunctions const& SetFrontFaceEXT(FrontFace frontFace) const {
        device_functions->CmdSetFrontFaceEXT(commandbuffer, frontFace);
        return *this; }
    CommandBufferFunctions const& SetPrimitiveTopologyEXT(PrimitiveTopology primitiveTopology) const {
        device_functions->CmdSetPrimitiveTopologyEXT(commandbuffer, primitiveTopology);
        return *this; }
    CommandBufferFunctions const& SetViewportWithCountEXT(uint32_t viewportCount, const Viewport* pViewports) const {
        device_functions->CmdSetViewportWithCountEXT(commandbuffer, viewportCount, pViewports);
        return *this; }
    CommandBufferFunctions const& SetScissorWithCountEXT(uint32_t scissorCount, const Rect2D* pScissors) const {
        device_functions->CmdSetScissorWithCountEXT(commandbuffer, scissorCount, pScissors);
        return *this; }
    CommandBufferFunctions const& BindVertexBuffers2EXT(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes, const DeviceSize* pStrides) const {
        device_functions->CmdBindVertexBuffers2EXT(commandbuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
        return *this; }
    CommandBufferFunctions const& SetDepthTestEnableEXT(Bool32 depthTestEnable) const {
        device_functions->CmdSetDepthTestEnableEXT(commandbuffer, depthTestEnable);
        return *this; }
    CommandBufferFunctions const& SetDepthWriteEnableEXT(Bool32 depthWriteEnable) const {
        device_functions->CmdSetDepthWriteEnableEXT(commandbuffer, depthWriteEnable);
        return *this; }
    CommandBufferFunctions const& SetDepthCompareOpEXT(CompareOp depthCompareOp) const {
        device_functions->CmdSetDepthCompareOpEXT(commandbuffer, depthCompareOp);
        return *this; }
    CommandBufferFunctions const& SetDepthBoundsTestEnableEXT(Bool32 depthBoundsTestEnable) const {
        device_functions->CmdSetDepthBoundsTestEnableEXT(commandbuffer, depthBoundsTestEnable);
        return *this; }
    CommandBufferFunctions const& SetStencilTestEnableEXT(Bool32 stencilTestEnable) const {
        device_functions->CmdSetStencilTestEnableEXT(commandbuffer, stencilTestEnable);
        return *this; }
    CommandBufferFunctions const& SetStencilOpEXT(StencilFaceFlags faceMask, StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp) const {
        device_functions->CmdSetStencilOpEXT(commandbuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
        return *this; }
    CommandBufferFunctions const& CopyBuffer2KHR(const CopyBufferInfo2KHR&  pCopyBufferInfo) const {
        device_functions->CmdCopyBuffer2KHR(commandbuffer, pCopyBufferInfo);
        return *this; }
    CommandBufferFunctions const& CopyImage2KHR(const CopyImageInfo2KHR&  pCopyImageInfo) const {
        device_functions->CmdCopyImage2KHR(commandbuffer, pCopyImageInfo);
        return *this; }
    CommandBufferFunctions const& BlitImage2KHR(const BlitImageInfo2KHR&  pBlitImageInfo) const {
        device_functions->CmdBlitImage2KHR(commandbuffer, pBlitImageInfo);
        return *this; }
    CommandBufferFunctions const& CopyBufferToImage2KHR(const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const {
        device_functions->CmdCopyBufferToImage2KHR(commandbuffer, pCopyBufferToImageInfo);
        return *this; }
    CommandBufferFunctions const& CopyImageToBuffer2KHR(const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const {
        device_functions->CmdCopyImageToBuffer2KHR(commandbuffer, pCopyImageToBufferInfo);
        return *this; }
    CommandBufferFunctions const& ResolveImage2KHR(const ResolveImageInfo2KHR&  pResolveImageInfo) const {
        device_functions->CmdResolveImage2KHR(commandbuffer, pResolveImageInfo);
        return *this; }
};
} // namespace vk
// clang-format on
