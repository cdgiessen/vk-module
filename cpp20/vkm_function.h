#pragma once
// clang-format off
#include <span>
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
#include <tuple>

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
            _count = std::exchange(other._count, 0);
            _data = std::exchange(other._data, nullptr);
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

    const T* operator-> () const noexcept { assert (_result == Result::Success); return &_value; }
	T*       operator-> ()       noexcept { assert (_result == Result::Success); return &_value; }
	const T& operator* () const& noexcept { assert (_result == Result::Success); return _value; }
	T&       operator* () &      noexcept { assert (_result == Result::Success); return _value; }
	T&&      operator* () &&	 noexcept { assert (_result == Result::Success); return std::move (_value); }
	const T&  value () const&    noexcept { assert (_result == Result::Success); return _value; }
	T&        value () &         noexcept { assert (_result == Result::Success); return _value; }
	const T&& value () const&&   noexcept { assert (_result == Result::Success); return std::move(_value); }
	T&&       value () &&        noexcept { assert (_result == Result::Success); return std::move(_value); }

    Result error() const noexcept { assert (_result != Result::Success); return _result; }
    Result raw_result() const noexcept { return _result; }

    bool has_value () const noexcept { return _result == Result::Success; }
	explicit operator bool () const noexcept { return _result == Result::Success; }
    bool operator!() const noexcept { return _result != Result::Success; }

    template <size_t N>
    auto const& get() const noexcept {
       if constexpr (N == 0) return _value;
       else if constexpr (N == 1) return _result;
    }
    template <size_t N>
    auto& get() noexcept {
       if constexpr (N == 0) return _value;
       else if constexpr (N == 1) return _result;
    }

private:
    T _value;
    Result _result = Result::Success;
};

} //namespace vk

namespace std {
    template<typename T>
    struct tuple_size<vk::expected<T>>: std::integral_constant<size_t, 2> {};
    template<typename T> struct tuple_element<0, vk::expected<T>> { using type = T; };
    template<typename T> struct tuple_element<1, vk::expected<T>> { using type = vk::Result; };
}

namespace vk {

struct GlobalFunctions {
    PFN_vkCreateInstance pfn_CreateInstance = nullptr;
    PFN_vkGetInstanceProcAddr pfn_GetInstanceProcAddr = nullptr;
    PFN_vkEnumerateInstanceExtensionProperties pfn_EnumerateInstanceExtensionProperties = nullptr;
    PFN_vkEnumerateInstanceLayerProperties pfn_EnumerateInstanceLayerProperties = nullptr;
    PFN_vkEnumerateInstanceVersion pfn_EnumerateInstanceVersion = nullptr;
    [[nodiscard]] expected<Instance> CreateInstance(const InstanceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] PFN_vkVoidFunction GetInstanceProcAddr(Instance instance, const char* pName) const;
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateInstanceExtensionProperties(const char* pLayerName) const;
    [[nodiscard]] expected<detail::fixed_vector<LayerProperties>> EnumerateInstanceLayerProperties() const;
    [[nodiscard]] expected<uint32_t> EnumerateInstanceVersion() const;
    explicit GlobalFunctions() noexcept;
    explicit GlobalFunctions(DynamicLibrary const& library) noexcept;
};
struct InstanceFunctions {
    Instance instance;
    PFN_vkDestroyInstance pfn_DestroyInstance = nullptr;
    PFN_vkEnumeratePhysicalDevices pfn_EnumeratePhysicalDevices = nullptr;
    PFN_vkGetDeviceProcAddr pfn_GetDeviceProcAddr = nullptr;
    PFN_vkGetInstanceProcAddr pfn_GetInstanceProcAddr = nullptr;
    PFN_vkGetPhysicalDeviceProperties pfn_GetPhysicalDeviceProperties = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties pfn_GetPhysicalDeviceQueueFamilyProperties = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties pfn_GetPhysicalDeviceMemoryProperties = nullptr;
    PFN_vkGetPhysicalDeviceFeatures pfn_GetPhysicalDeviceFeatures = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties pfn_GetPhysicalDeviceFormatProperties = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties pfn_GetPhysicalDeviceImageFormatProperties = nullptr;
    PFN_vkCreateDevice pfn_CreateDevice = nullptr;
    PFN_vkEnumerateDeviceExtensionProperties pfn_EnumerateDeviceExtensionProperties = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties pfn_GetPhysicalDeviceSparseImageFormatProperties = nullptr;
    PFN_vkEnumeratePhysicalDeviceGroups pfn_EnumeratePhysicalDeviceGroups = nullptr;
    PFN_vkGetPhysicalDeviceFeatures2 pfn_GetPhysicalDeviceFeatures2 = nullptr;
    PFN_vkGetPhysicalDeviceProperties2 pfn_GetPhysicalDeviceProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceFormatProperties2 pfn_GetPhysicalDeviceFormatProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 pfn_GetPhysicalDeviceImageFormatProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 pfn_GetPhysicalDeviceQueueFamilyProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceMemoryProperties2 pfn_GetPhysicalDeviceMemoryProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 pfn_GetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
    PFN_vkGetPhysicalDeviceExternalBufferProperties pfn_GetPhysicalDeviceExternalBufferProperties = nullptr;
    PFN_vkGetPhysicalDeviceExternalFenceProperties pfn_GetPhysicalDeviceExternalFenceProperties = nullptr;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties pfn_GetPhysicalDeviceExternalSemaphoreProperties = nullptr;
    PFN_vkDestroySurfaceKHR pfn_DestroySurfaceKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR pfn_GetPhysicalDeviceSurfaceSupportKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR pfn_GetPhysicalDeviceSurfaceFormatsKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR pfn_GetPhysicalDeviceSurfacePresentModesKHR = nullptr;
    PFN_vkGetPhysicalDevicePresentRectanglesKHR pfn_GetPhysicalDevicePresentRectanglesKHR = nullptr;
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR pfn_GetPhysicalDeviceDisplayPropertiesKHR = nullptr;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR pfn_GetDisplayPlaneSupportedDisplaysKHR = nullptr;
    PFN_vkGetDisplayModePropertiesKHR pfn_GetDisplayModePropertiesKHR = nullptr;
    PFN_vkCreateDisplayModeKHR pfn_CreateDisplayModeKHR = nullptr;
    PFN_vkGetDisplayPlaneCapabilitiesKHR pfn_GetDisplayPlaneCapabilitiesKHR = nullptr;
    PFN_vkCreateDisplayPlaneSurfaceKHR pfn_CreateDisplayPlaneSurfaceKHR = nullptr;
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    PFN_vkCreateXlibSurfaceKHR pfn_CreateXlibSurfaceKHR = nullptr;
    PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR pfn_GetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    PFN_vkCreateXcbSurfaceKHR pfn_CreateXcbSurfaceKHR = nullptr;
    PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR pfn_GetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    PFN_vkCreateWaylandSurfaceKHR pfn_CreateWaylandSurfaceKHR = nullptr;
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR pfn_GetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkCreateAndroidSurfaceKHR pfn_CreateAndroidSurfaceKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkCreateWin32SurfaceKHR pfn_CreateWin32SurfaceKHR = nullptr;
    PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR pfn_GetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkCreateDebugReportCallbackEXT pfn_CreateDebugReportCallbackEXT = nullptr;
    PFN_vkDestroyDebugReportCallbackEXT pfn_DestroyDebugReportCallbackEXT = nullptr;
    PFN_vkDebugReportMessageEXT pfn_DebugReportMessageEXT = nullptr;
#if defined(VK_USE_PLATFORM_GGP)
    PFN_vkCreateStreamDescriptorSurfaceGGP pfn_CreateStreamDescriptorSurfaceGGP = nullptr;
#endif // defined(VK_USE_PLATFORM_GGP)
    PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV = nullptr;
#if defined(VK_USE_PLATFORM_VI_NN)
    PFN_vkCreateViSurfaceNN pfn_CreateViSurfaceNN = nullptr;
#endif // defined(VK_USE_PLATFORM_VI_NN)
    PFN_vkReleaseDisplayEXT pfn_ReleaseDisplayEXT = nullptr;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    PFN_vkAcquireXlibDisplayEXT pfn_AcquireXlibDisplayEXT = nullptr;
    PFN_vkGetRandROutputDisplayEXT pfn_GetRandROutputDisplayEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT pfn_GetPhysicalDeviceSurfaceCapabilities2EXT = nullptr;
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = nullptr;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR pfn_GetPhysicalDeviceSurfaceCapabilities2KHR = nullptr;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR pfn_GetPhysicalDeviceSurfaceFormats2KHR = nullptr;
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR pfn_GetPhysicalDeviceDisplayProperties2KHR = nullptr;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR = nullptr;
    PFN_vkGetDisplayModeProperties2KHR pfn_GetDisplayModeProperties2KHR = nullptr;
    PFN_vkGetDisplayPlaneCapabilities2KHR pfn_GetDisplayPlaneCapabilities2KHR = nullptr;
#if defined(VK_USE_PLATFORM_IOS_MVK)
    PFN_vkCreateIOSSurfaceMVK pfn_CreateIOSSurfaceMVK = nullptr;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    PFN_vkCreateMacOSSurfaceMVK pfn_CreateMacOSSurfaceMVK = nullptr;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
    PFN_vkCreateDebugUtilsMessengerEXT pfn_CreateDebugUtilsMessengerEXT = nullptr;
    PFN_vkDestroyDebugUtilsMessengerEXT pfn_DestroyDebugUtilsMessengerEXT = nullptr;
    PFN_vkSubmitDebugUtilsMessageEXT pfn_SubmitDebugUtilsMessageEXT = nullptr;
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT pfn_GetPhysicalDeviceMultisamplePropertiesEXT = nullptr;
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT = nullptr;
#if defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkCreateImagePipeSurfaceFUCHSIA pfn_CreateImagePipeSurfaceFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
    PFN_vkCreateMetalSurfaceEXT pfn_CreateMetalSurfaceEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
    PFN_vkGetPhysicalDeviceToolPropertiesEXT pfn_GetPhysicalDeviceToolPropertiesEXT = nullptr;
    PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV = nullptr;
    PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT pfn_GetPhysicalDeviceSurfacePresentModes2EXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkCreateHeadlessSurfaceEXT pfn_CreateHeadlessSurfaceEXT = nullptr;
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    PFN_vkCreateDirectFBSurfaceEXT pfn_CreateDirectFBSurfaceEXT = nullptr;
    PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    void DestroyInstance(const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDevice>> EnumeratePhysicalDevices() const;
    [[nodiscard]] PFN_vkVoidFunction GetDeviceProcAddr(Device device, const char* pName) const;
    [[nodiscard]] PFN_vkVoidFunction GetInstanceProcAddr(const char* pName) const;
    [[nodiscard]] PhysicalDeviceProperties GetPhysicalDeviceProperties(PhysicalDevice physicalDevice) const;
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(PhysicalDevice physicalDevice) const;
    [[nodiscard]] PhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(PhysicalDevice physicalDevice) const;
    [[nodiscard]] PhysicalDeviceFeatures GetPhysicalDeviceFeatures(PhysicalDevice physicalDevice) const;
    [[nodiscard]] FormatProperties GetPhysicalDeviceFormatProperties(PhysicalDevice physicalDevice, Format format) const;
    [[nodiscard]] expected<ImageFormatProperties> GetPhysicalDeviceImageFormatProperties(PhysicalDevice physicalDevice, Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags) const;
    [[nodiscard]] expected<Device> CreateDevice(PhysicalDevice physicalDevice, const DeviceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(PhysicalDevice physicalDevice, const char* pLayerName) const;
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetPhysicalDeviceSparseImageFormatProperties(PhysicalDevice physicalDevice, Format format, ImageType type, SampleCountFlagBits samples, ImageUsageFlags usage, ImageTiling tiling) const;
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceGroupProperties>> EnumeratePhysicalDeviceGroups() const;
    [[nodiscard]] PhysicalDeviceFeatures2 GetPhysicalDeviceFeatures2(PhysicalDevice physicalDevice) const;
    [[nodiscard]] PhysicalDeviceProperties2 GetPhysicalDeviceProperties2(PhysicalDevice physicalDevice) const;
    [[nodiscard]] FormatProperties2 GetPhysicalDeviceFormatProperties2(PhysicalDevice physicalDevice, Format format) const;
    [[nodiscard]] expected<ImageFormatProperties2> GetPhysicalDeviceImageFormatProperties2(PhysicalDevice physicalDevice, const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const;
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetPhysicalDeviceQueueFamilyProperties2(PhysicalDevice physicalDevice) const;
    [[nodiscard]] PhysicalDeviceMemoryProperties2 GetPhysicalDeviceMemoryProperties2(PhysicalDevice physicalDevice) const;
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetPhysicalDeviceSparseImageFormatProperties2(PhysicalDevice physicalDevice, const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const;
    [[nodiscard]] ExternalBufferProperties GetPhysicalDeviceExternalBufferProperties(PhysicalDevice physicalDevice, const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const;
    [[nodiscard]] ExternalFenceProperties GetPhysicalDeviceExternalFenceProperties(PhysicalDevice physicalDevice, const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const;
    [[nodiscard]] ExternalSemaphoreProperties GetPhysicalDeviceExternalSemaphoreProperties(PhysicalDevice physicalDevice, const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const;
    void DestroySurfaceKHR(SurfaceKHR surface, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<Bool32> GetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, SurfaceKHR surface) const;
    [[nodiscard]] expected<SurfaceCapabilitiesKHR> GetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice physicalDevice, SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice physicalDevice, SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice physicalDevice, SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPhysicalDevicePresentRectanglesKHR(PhysicalDevice physicalDevice, SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetPhysicalDeviceDisplayPropertiesKHR(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetPhysicalDeviceDisplayPlanePropertiesKHR(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(PhysicalDevice physicalDevice, uint32_t planeIndex) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(PhysicalDevice physicalDevice, DisplayKHR display) const;
    [[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(PhysicalDevice physicalDevice, DisplayKHR display, const DisplayModeCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(PhysicalDevice physicalDevice, DisplayModeKHR mode, uint32_t planeIndex) const;
    [[nodiscard]] expected<SurfaceKHR> CreateDisplayPlaneSurfaceKHR(const DisplaySurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    [[nodiscard]] expected<SurfaceKHR> CreateXlibSurfaceKHR(const XlibSurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    [[nodiscard]] VkBool32 GetPhysicalDeviceXlibPresentationSupportKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display&  dpy, VisualID visualID) const;
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    [[nodiscard]] expected<SurfaceKHR> CreateXcbSurfaceKHR(const XcbSurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    [[nodiscard]] VkBool32 GetPhysicalDeviceXcbPresentationSupportKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t&  connection, xcb_visualid_t visual_id) const;
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    [[nodiscard]] expected<SurfaceKHR> CreateWaylandSurfaceKHR(const WaylandSurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    [[nodiscard]] wl_display GetPhysicalDeviceWaylandPresentationSupportKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const;
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    [[nodiscard]] expected<SurfaceKHR> CreateAndroidSurfaceKHR(const AndroidSurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<SurfaceKHR> CreateWin32SurfaceKHR(const Win32SurfaceCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] VkBool32 GetPhysicalDeviceWin32PresentationSupportKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    [[nodiscard]] expected<DebugReportCallbackEXT> CreateDebugReportCallbackEXT(const DebugReportCallbackCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyDebugReportCallbackEXT(DebugReportCallbackEXT callback, const AllocationCallbacks* pAllocator = nullptr) const;
    void DebugReportMessageEXT(DebugReportFlagsEXT flags, DebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage) const;
#if defined(VK_USE_PLATFORM_GGP)
    [[nodiscard]] expected<SurfaceKHR> CreateStreamDescriptorSurfaceGGP(const StreamDescriptorSurfaceCreateInfoGGP&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_GGP
    [[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetPhysicalDeviceExternalImageFormatPropertiesNV(PhysicalDevice physicalDevice, Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags, ExternalMemoryHandleTypeFlagsNV externalHandleType) const;
#if defined(VK_USE_PLATFORM_VI_NN)
    [[nodiscard]] expected<SurfaceKHR> CreateViSurfaceNN(const ViSurfaceCreateInfoNN&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_VI_NN
    [[nodiscard]] Result ReleaseDisplayEXT(PhysicalDevice physicalDevice, DisplayKHR display) const;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] Result AcquireXlibDisplayEXT(PhysicalDevice physicalDevice, Display&  dpy, DisplayKHR display) const;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(PhysicalDevice physicalDevice, Display&  dpy, RROutput rrOutput) const;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
    [[nodiscard]] expected<SurfaceCapabilities2EXT> GetPhysicalDeviceSurfaceCapabilities2EXT(PhysicalDevice physicalDevice, SurfaceKHR surface) const;
    [[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t&  pCounterCount, PerformanceCounterKHR* pCounters, PerformanceCounterDescriptionKHR* pCounterDescriptions) const;
    [[nodiscard]] uint32_t GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(PhysicalDevice physicalDevice, const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const;
    [[nodiscard]] expected<SurfaceCapabilities2KHR> GetPhysicalDeviceSurfaceCapabilities2KHR(PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetPhysicalDeviceSurfaceFormats2KHR(PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetPhysicalDeviceDisplayProperties2KHR(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetPhysicalDeviceDisplayPlaneProperties2KHR(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(PhysicalDevice physicalDevice, DisplayKHR display) const;
    [[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(PhysicalDevice physicalDevice, const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const;
#if defined(VK_USE_PLATFORM_IOS_MVK)
    [[nodiscard]] expected<SurfaceKHR> CreateIOSSurfaceMVK(const IOSSurfaceCreateInfoMVK&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    [[nodiscard]] expected<SurfaceKHR> CreateMacOSSurfaceMVK(const MacOSSurfaceCreateInfoMVK&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_MACOS_MVK
    [[nodiscard]] expected<DebugUtilsMessengerEXT> CreateDebugUtilsMessengerEXT(const DebugUtilsMessengerCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyDebugUtilsMessengerEXT(DebugUtilsMessengerEXT messenger, const AllocationCallbacks* pAllocator = nullptr) const;
    void SubmitDebugUtilsMessageEXT(DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, DebugUtilsMessageTypeFlagsEXT messageTypes, const DebugUtilsMessengerCallbackDataEXT&  pCallbackData) const;
    [[nodiscard]] MultisamplePropertiesEXT GetPhysicalDeviceMultisamplePropertiesEXT(PhysicalDevice physicalDevice, SampleCountFlagBits samples) const;
    [[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetPhysicalDeviceCalibrateableTimeDomainsEXT(PhysicalDevice physicalDevice) const;
#if defined(VK_USE_PLATFORM_FUCHSIA)
    [[nodiscard]] expected<SurfaceKHR> CreateImagePipeSurfaceFUCHSIA(const ImagePipeSurfaceCreateInfoFUCHSIA&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_METAL_EXT)
    [[nodiscard]] expected<SurfaceKHR> CreateMetalSurfaceEXT(const MetalSurfaceCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_METAL_EXT
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetPhysicalDeviceToolPropertiesEXT(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetPhysicalDeviceCooperativeMatrixPropertiesNV(PhysicalDevice physicalDevice) const;
    [[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(PhysicalDevice physicalDevice) const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModes2EXT(PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    [[nodiscard]] expected<SurfaceKHR> CreateHeadlessSurfaceEXT(const HeadlessSurfaceCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] expected<SurfaceKHR> CreateDirectFBSurfaceEXT(const DirectFBSurfaceCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] IDirectFB GetPhysicalDeviceDirectFBPresentationSupportEXT(PhysicalDevice physicalDevice, uint32_t queueFamilyIndex) const;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
    explicit InstanceFunctions() noexcept;
    explicit InstanceFunctions(GlobalFunctions const& global_functions, Instance instance) noexcept;
};
struct DeviceFunctions {
    Device device;
    PFN_vkDestroyDevice pfn_DestroyDevice = nullptr;
    PFN_vkGetDeviceQueue pfn_GetDeviceQueue = nullptr;
    PFN_vkQueueSubmit pfn_QueueSubmit = nullptr;
    PFN_vkQueueWaitIdle pfn_QueueWaitIdle = nullptr;
    PFN_vkDeviceWaitIdle pfn_DeviceWaitIdle = nullptr;
    PFN_vkAllocateMemory pfn_AllocateMemory = nullptr;
    PFN_vkFreeMemory pfn_FreeMemory = nullptr;
    PFN_vkMapMemory pfn_MapMemory = nullptr;
    PFN_vkUnmapMemory pfn_UnmapMemory = nullptr;
    PFN_vkFlushMappedMemoryRanges pfn_FlushMappedMemoryRanges = nullptr;
    PFN_vkInvalidateMappedMemoryRanges pfn_InvalidateMappedMemoryRanges = nullptr;
    PFN_vkGetDeviceMemoryCommitment pfn_GetDeviceMemoryCommitment = nullptr;
    PFN_vkGetBufferMemoryRequirements pfn_GetBufferMemoryRequirements = nullptr;
    PFN_vkBindBufferMemory pfn_BindBufferMemory = nullptr;
    PFN_vkGetImageMemoryRequirements pfn_GetImageMemoryRequirements = nullptr;
    PFN_vkBindImageMemory pfn_BindImageMemory = nullptr;
    PFN_vkGetImageSparseMemoryRequirements pfn_GetImageSparseMemoryRequirements = nullptr;
    PFN_vkQueueBindSparse pfn_QueueBindSparse = nullptr;
    PFN_vkCreateFence pfn_CreateFence = nullptr;
    PFN_vkDestroyFence pfn_DestroyFence = nullptr;
    PFN_vkResetFences pfn_ResetFences = nullptr;
    PFN_vkGetFenceStatus pfn_GetFenceStatus = nullptr;
    PFN_vkWaitForFences pfn_WaitForFences = nullptr;
    PFN_vkCreateSemaphore pfn_CreateSemaphore = nullptr;
    PFN_vkDestroySemaphore pfn_DestroySemaphore = nullptr;
    PFN_vkCreateEvent pfn_CreateEvent = nullptr;
    PFN_vkDestroyEvent pfn_DestroyEvent = nullptr;
    PFN_vkGetEventStatus pfn_GetEventStatus = nullptr;
    PFN_vkSetEvent pfn_SetEvent = nullptr;
    PFN_vkResetEvent pfn_ResetEvent = nullptr;
    PFN_vkCreateQueryPool pfn_CreateQueryPool = nullptr;
    PFN_vkDestroyQueryPool pfn_DestroyQueryPool = nullptr;
    PFN_vkGetQueryPoolResults pfn_GetQueryPoolResults = nullptr;
    PFN_vkCreateBuffer pfn_CreateBuffer = nullptr;
    PFN_vkDestroyBuffer pfn_DestroyBuffer = nullptr;
    PFN_vkCreateBufferView pfn_CreateBufferView = nullptr;
    PFN_vkDestroyBufferView pfn_DestroyBufferView = nullptr;
    PFN_vkCreateImage pfn_CreateImage = nullptr;
    PFN_vkDestroyImage pfn_DestroyImage = nullptr;
    PFN_vkGetImageSubresourceLayout pfn_GetImageSubresourceLayout = nullptr;
    PFN_vkCreateImageView pfn_CreateImageView = nullptr;
    PFN_vkDestroyImageView pfn_DestroyImageView = nullptr;
    PFN_vkCreateShaderModule pfn_CreateShaderModule = nullptr;
    PFN_vkDestroyShaderModule pfn_DestroyShaderModule = nullptr;
    PFN_vkCreatePipelineCache pfn_CreatePipelineCache = nullptr;
    PFN_vkDestroyPipelineCache pfn_DestroyPipelineCache = nullptr;
    PFN_vkGetPipelineCacheData pfn_GetPipelineCacheData = nullptr;
    PFN_vkMergePipelineCaches pfn_MergePipelineCaches = nullptr;
    PFN_vkCreateGraphicsPipelines pfn_CreateGraphicsPipelines = nullptr;
    PFN_vkCreateComputePipelines pfn_CreateComputePipelines = nullptr;
    PFN_vkDestroyPipeline pfn_DestroyPipeline = nullptr;
    PFN_vkCreatePipelineLayout pfn_CreatePipelineLayout = nullptr;
    PFN_vkDestroyPipelineLayout pfn_DestroyPipelineLayout = nullptr;
    PFN_vkCreateSampler pfn_CreateSampler = nullptr;
    PFN_vkDestroySampler pfn_DestroySampler = nullptr;
    PFN_vkCreateDescriptorSetLayout pfn_CreateDescriptorSetLayout = nullptr;
    PFN_vkDestroyDescriptorSetLayout pfn_DestroyDescriptorSetLayout = nullptr;
    PFN_vkCreateDescriptorPool pfn_CreateDescriptorPool = nullptr;
    PFN_vkDestroyDescriptorPool pfn_DestroyDescriptorPool = nullptr;
    PFN_vkResetDescriptorPool pfn_ResetDescriptorPool = nullptr;
    PFN_vkAllocateDescriptorSets pfn_AllocateDescriptorSets = nullptr;
    PFN_vkFreeDescriptorSets pfn_FreeDescriptorSets = nullptr;
    PFN_vkUpdateDescriptorSets pfn_UpdateDescriptorSets = nullptr;
    PFN_vkCreateFramebuffer pfn_CreateFramebuffer = nullptr;
    PFN_vkDestroyFramebuffer pfn_DestroyFramebuffer = nullptr;
    PFN_vkCreateRenderPass pfn_CreateRenderPass = nullptr;
    PFN_vkDestroyRenderPass pfn_DestroyRenderPass = nullptr;
    PFN_vkGetRenderAreaGranularity pfn_GetRenderAreaGranularity = nullptr;
    PFN_vkCreateCommandPool pfn_CreateCommandPool = nullptr;
    PFN_vkDestroyCommandPool pfn_DestroyCommandPool = nullptr;
    PFN_vkResetCommandPool pfn_ResetCommandPool = nullptr;
    PFN_vkAllocateCommandBuffers pfn_AllocateCommandBuffers = nullptr;
    PFN_vkFreeCommandBuffers pfn_FreeCommandBuffers = nullptr;
    PFN_vkBeginCommandBuffer pfn_BeginCommandBuffer = nullptr;
    PFN_vkEndCommandBuffer pfn_EndCommandBuffer = nullptr;
    PFN_vkResetCommandBuffer pfn_ResetCommandBuffer = nullptr;
    PFN_vkCmdBindPipeline pfn_CmdBindPipeline = nullptr;
    PFN_vkCmdSetViewport pfn_CmdSetViewport = nullptr;
    PFN_vkCmdSetScissor pfn_CmdSetScissor = nullptr;
    PFN_vkCmdSetLineWidth pfn_CmdSetLineWidth = nullptr;
    PFN_vkCmdSetDepthBias pfn_CmdSetDepthBias = nullptr;
    PFN_vkCmdSetBlendConstants pfn_CmdSetBlendConstants = nullptr;
    PFN_vkCmdSetDepthBounds pfn_CmdSetDepthBounds = nullptr;
    PFN_vkCmdSetStencilCompareMask pfn_CmdSetStencilCompareMask = nullptr;
    PFN_vkCmdSetStencilWriteMask pfn_CmdSetStencilWriteMask = nullptr;
    PFN_vkCmdSetStencilReference pfn_CmdSetStencilReference = nullptr;
    PFN_vkCmdBindDescriptorSets pfn_CmdBindDescriptorSets = nullptr;
    PFN_vkCmdBindIndexBuffer pfn_CmdBindIndexBuffer = nullptr;
    PFN_vkCmdBindVertexBuffers pfn_CmdBindVertexBuffers = nullptr;
    PFN_vkCmdDraw pfn_CmdDraw = nullptr;
    PFN_vkCmdDrawIndexed pfn_CmdDrawIndexed = nullptr;
    PFN_vkCmdDrawIndirect pfn_CmdDrawIndirect = nullptr;
    PFN_vkCmdDrawIndexedIndirect pfn_CmdDrawIndexedIndirect = nullptr;
    PFN_vkCmdDispatch pfn_CmdDispatch = nullptr;
    PFN_vkCmdDispatchIndirect pfn_CmdDispatchIndirect = nullptr;
    PFN_vkCmdCopyBuffer pfn_CmdCopyBuffer = nullptr;
    PFN_vkCmdCopyImage pfn_CmdCopyImage = nullptr;
    PFN_vkCmdBlitImage pfn_CmdBlitImage = nullptr;
    PFN_vkCmdCopyBufferToImage pfn_CmdCopyBufferToImage = nullptr;
    PFN_vkCmdCopyImageToBuffer pfn_CmdCopyImageToBuffer = nullptr;
    PFN_vkCmdUpdateBuffer pfn_CmdUpdateBuffer = nullptr;
    PFN_vkCmdFillBuffer pfn_CmdFillBuffer = nullptr;
    PFN_vkCmdClearColorImage pfn_CmdClearColorImage = nullptr;
    PFN_vkCmdClearDepthStencilImage pfn_CmdClearDepthStencilImage = nullptr;
    PFN_vkCmdClearAttachments pfn_CmdClearAttachments = nullptr;
    PFN_vkCmdResolveImage pfn_CmdResolveImage = nullptr;
    PFN_vkCmdSetEvent pfn_CmdSetEvent = nullptr;
    PFN_vkCmdResetEvent pfn_CmdResetEvent = nullptr;
    PFN_vkCmdWaitEvents pfn_CmdWaitEvents = nullptr;
    PFN_vkCmdPipelineBarrier pfn_CmdPipelineBarrier = nullptr;
    PFN_vkCmdBeginQuery pfn_CmdBeginQuery = nullptr;
    PFN_vkCmdEndQuery pfn_CmdEndQuery = nullptr;
    PFN_vkCmdResetQueryPool pfn_CmdResetQueryPool = nullptr;
    PFN_vkCmdWriteTimestamp pfn_CmdWriteTimestamp = nullptr;
    PFN_vkCmdCopyQueryPoolResults pfn_CmdCopyQueryPoolResults = nullptr;
    PFN_vkCmdPushConstants pfn_CmdPushConstants = nullptr;
    PFN_vkCmdBeginRenderPass pfn_CmdBeginRenderPass = nullptr;
    PFN_vkCmdNextSubpass pfn_CmdNextSubpass = nullptr;
    PFN_vkCmdEndRenderPass pfn_CmdEndRenderPass = nullptr;
    PFN_vkCmdExecuteCommands pfn_CmdExecuteCommands = nullptr;
    PFN_vkBindBufferMemory2 pfn_BindBufferMemory2 = nullptr;
    PFN_vkBindImageMemory2 pfn_BindImageMemory2 = nullptr;
    PFN_vkGetDeviceGroupPeerMemoryFeatures pfn_GetDeviceGroupPeerMemoryFeatures = nullptr;
    PFN_vkCmdSetDeviceMask pfn_CmdSetDeviceMask = nullptr;
    PFN_vkCmdDispatchBase pfn_CmdDispatchBase = nullptr;
    PFN_vkGetBufferMemoryRequirements2 pfn_GetBufferMemoryRequirements2 = nullptr;
    PFN_vkGetImageMemoryRequirements2 pfn_GetImageMemoryRequirements2 = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2 pfn_GetImageSparseMemoryRequirements2 = nullptr;
    PFN_vkTrimCommandPool pfn_TrimCommandPool = nullptr;
    PFN_vkGetDeviceQueue2 pfn_GetDeviceQueue2 = nullptr;
    PFN_vkCreateSamplerYcbcrConversion pfn_CreateSamplerYcbcrConversion = nullptr;
    PFN_vkDestroySamplerYcbcrConversion pfn_DestroySamplerYcbcrConversion = nullptr;
    PFN_vkCreateDescriptorUpdateTemplate pfn_CreateDescriptorUpdateTemplate = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplate pfn_DestroyDescriptorUpdateTemplate = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplate pfn_UpdateDescriptorSetWithTemplate = nullptr;
    PFN_vkGetDescriptorSetLayoutSupport pfn_GetDescriptorSetLayoutSupport = nullptr;
    PFN_vkCmdDrawIndirectCount pfn_CmdDrawIndirectCount = nullptr;
    PFN_vkCmdDrawIndexedIndirectCount pfn_CmdDrawIndexedIndirectCount = nullptr;
    PFN_vkCreateRenderPass2 pfn_CreateRenderPass2 = nullptr;
    PFN_vkCmdBeginRenderPass2 pfn_CmdBeginRenderPass2 = nullptr;
    PFN_vkCmdNextSubpass2 pfn_CmdNextSubpass2 = nullptr;
    PFN_vkCmdEndRenderPass2 pfn_CmdEndRenderPass2 = nullptr;
    PFN_vkResetQueryPool pfn_ResetQueryPool = nullptr;
    PFN_vkGetSemaphoreCounterValue pfn_GetSemaphoreCounterValue = nullptr;
    PFN_vkWaitSemaphores pfn_WaitSemaphores = nullptr;
    PFN_vkSignalSemaphore pfn_SignalSemaphore = nullptr;
    PFN_vkGetBufferOpaqueCaptureAddress pfn_GetBufferOpaqueCaptureAddress = nullptr;
    PFN_vkGetBufferDeviceAddress pfn_GetBufferDeviceAddress = nullptr;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress pfn_GetDeviceMemoryOpaqueCaptureAddress = nullptr;
    PFN_vkCreateSwapchainKHR pfn_CreateSwapchainKHR = nullptr;
    PFN_vkDestroySwapchainKHR pfn_DestroySwapchainKHR = nullptr;
    PFN_vkGetSwapchainImagesKHR pfn_GetSwapchainImagesKHR = nullptr;
    PFN_vkAcquireNextImageKHR pfn_AcquireNextImageKHR = nullptr;
    PFN_vkQueuePresentKHR pfn_QueuePresentKHR = nullptr;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR pfn_GetDeviceGroupPresentCapabilitiesKHR = nullptr;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR pfn_GetDeviceGroupSurfacePresentModesKHR = nullptr;
    PFN_vkAcquireNextImage2KHR pfn_AcquireNextImage2KHR = nullptr;
    PFN_vkCreateSharedSwapchainsKHR pfn_CreateSharedSwapchainsKHR = nullptr;
    PFN_vkDebugMarkerSetObjectNameEXT pfn_DebugMarkerSetObjectNameEXT = nullptr;
    PFN_vkDebugMarkerSetObjectTagEXT pfn_DebugMarkerSetObjectTagEXT = nullptr;
    PFN_vkCmdDebugMarkerBeginEXT pfn_CmdDebugMarkerBeginEXT = nullptr;
    PFN_vkCmdDebugMarkerEndEXT pfn_CmdDebugMarkerEndEXT = nullptr;
    PFN_vkCmdDebugMarkerInsertEXT pfn_CmdDebugMarkerInsertEXT = nullptr;
    PFN_vkCmdBindTransformFeedbackBuffersEXT pfn_CmdBindTransformFeedbackBuffersEXT = nullptr;
    PFN_vkCmdBeginTransformFeedbackEXT pfn_CmdBeginTransformFeedbackEXT = nullptr;
    PFN_vkCmdEndTransformFeedbackEXT pfn_CmdEndTransformFeedbackEXT = nullptr;
    PFN_vkCmdBeginQueryIndexedEXT pfn_CmdBeginQueryIndexedEXT = nullptr;
    PFN_vkCmdEndQueryIndexedEXT pfn_CmdEndQueryIndexedEXT = nullptr;
    PFN_vkCmdDrawIndirectByteCountEXT pfn_CmdDrawIndirectByteCountEXT = nullptr;
    PFN_vkGetImageViewHandleNVX pfn_GetImageViewHandleNVX = nullptr;
    PFN_vkGetImageViewAddressNVX pfn_GetImageViewAddressNVX = nullptr;
    PFN_vkGetShaderInfoAMD pfn_GetShaderInfoAMD = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryWin32HandleNV pfn_GetMemoryWin32HandleNV = nullptr;
    PFN_vkGetMemoryWin32HandleKHR pfn_GetMemoryWin32HandleKHR = nullptr;
    PFN_vkGetMemoryWin32HandlePropertiesKHR pfn_GetMemoryWin32HandlePropertiesKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryFdKHR pfn_GetMemoryFdKHR = nullptr;
    PFN_vkGetMemoryFdPropertiesKHR pfn_GetMemoryFdPropertiesKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetSemaphoreWin32HandleKHR pfn_GetSemaphoreWin32HandleKHR = nullptr;
    PFN_vkImportSemaphoreWin32HandleKHR pfn_ImportSemaphoreWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetSemaphoreFdKHR pfn_GetSemaphoreFdKHR = nullptr;
    PFN_vkImportSemaphoreFdKHR pfn_ImportSemaphoreFdKHR = nullptr;
    PFN_vkCmdPushDescriptorSetKHR pfn_CmdPushDescriptorSetKHR = nullptr;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR pfn_CmdPushDescriptorSetWithTemplateKHR = nullptr;
    PFN_vkCmdBeginConditionalRenderingEXT pfn_CmdBeginConditionalRenderingEXT = nullptr;
    PFN_vkCmdEndConditionalRenderingEXT pfn_CmdEndConditionalRenderingEXT = nullptr;
    PFN_vkCmdSetViewportWScalingNV pfn_CmdSetViewportWScalingNV = nullptr;
    PFN_vkDisplayPowerControlEXT pfn_DisplayPowerControlEXT = nullptr;
    PFN_vkRegisterDeviceEventEXT pfn_RegisterDeviceEventEXT = nullptr;
    PFN_vkRegisterDisplayEventEXT pfn_RegisterDisplayEventEXT = nullptr;
    PFN_vkGetSwapchainCounterEXT pfn_GetSwapchainCounterEXT = nullptr;
    PFN_vkGetRefreshCycleDurationGOOGLE pfn_GetRefreshCycleDurationGOOGLE = nullptr;
    PFN_vkGetPastPresentationTimingGOOGLE pfn_GetPastPresentationTimingGOOGLE = nullptr;
    PFN_vkCmdSetDiscardRectangleEXT pfn_CmdSetDiscardRectangleEXT = nullptr;
    PFN_vkSetHdrMetadataEXT pfn_SetHdrMetadataEXT = nullptr;
    PFN_vkGetSwapchainStatusKHR pfn_GetSwapchainStatusKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetFenceWin32HandleKHR pfn_GetFenceWin32HandleKHR = nullptr;
    PFN_vkImportFenceWin32HandleKHR pfn_ImportFenceWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetFenceFdKHR pfn_GetFenceFdKHR = nullptr;
    PFN_vkImportFenceFdKHR pfn_ImportFenceFdKHR = nullptr;
    PFN_vkAcquireProfilingLockKHR pfn_AcquireProfilingLockKHR = nullptr;
    PFN_vkReleaseProfilingLockKHR pfn_ReleaseProfilingLockKHR = nullptr;
    PFN_vkSetDebugUtilsObjectNameEXT pfn_SetDebugUtilsObjectNameEXT = nullptr;
    PFN_vkSetDebugUtilsObjectTagEXT pfn_SetDebugUtilsObjectTagEXT = nullptr;
    PFN_vkQueueBeginDebugUtilsLabelEXT pfn_QueueBeginDebugUtilsLabelEXT = nullptr;
    PFN_vkQueueEndDebugUtilsLabelEXT pfn_QueueEndDebugUtilsLabelEXT = nullptr;
    PFN_vkQueueInsertDebugUtilsLabelEXT pfn_QueueInsertDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdBeginDebugUtilsLabelEXT pfn_CmdBeginDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdEndDebugUtilsLabelEXT pfn_CmdEndDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdInsertDebugUtilsLabelEXT pfn_CmdInsertDebugUtilsLabelEXT = nullptr;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID pfn_GetAndroidHardwareBufferPropertiesANDROID = nullptr;
    PFN_vkGetMemoryAndroidHardwareBufferANDROID pfn_GetMemoryAndroidHardwareBufferANDROID = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkCmdSetSampleLocationsEXT pfn_CmdSetSampleLocationsEXT = nullptr;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkDestroyAccelerationStructureKHR pfn_DestroyAccelerationStructureKHR = nullptr;
    PFN_vkGetAccelerationStructureMemoryRequirementsKHR pfn_GetAccelerationStructureMemoryRequirementsKHR = nullptr;
    PFN_vkBindAccelerationStructureMemoryKHR pfn_BindAccelerationStructureMemoryKHR = nullptr;
    PFN_vkCmdCopyAccelerationStructureKHR pfn_CmdCopyAccelerationStructureKHR = nullptr;
    PFN_vkCopyAccelerationStructureKHR pfn_CopyAccelerationStructureKHR = nullptr;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR pfn_CmdCopyAccelerationStructureToMemoryKHR = nullptr;
    PFN_vkCopyAccelerationStructureToMemoryKHR pfn_CopyAccelerationStructureToMemoryKHR = nullptr;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR pfn_CmdCopyMemoryToAccelerationStructureKHR = nullptr;
    PFN_vkCopyMemoryToAccelerationStructureKHR pfn_CopyMemoryToAccelerationStructureKHR = nullptr;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR pfn_CmdWriteAccelerationStructuresPropertiesKHR = nullptr;
    PFN_vkWriteAccelerationStructuresPropertiesKHR pfn_WriteAccelerationStructuresPropertiesKHR = nullptr;
    PFN_vkCmdTraceRaysKHR pfn_CmdTraceRaysKHR = nullptr;
    PFN_vkGetRayTracingShaderGroupHandlesKHR pfn_GetRayTracingShaderGroupHandlesKHR = nullptr;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
    PFN_vkCreateRayTracingPipelinesKHR pfn_CreateRayTracingPipelinesKHR = nullptr;
    PFN_vkCmdTraceRaysIndirectKHR pfn_CmdTraceRaysIndirectKHR = nullptr;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR pfn_GetDeviceAccelerationStructureCompatibilityKHR = nullptr;
    PFN_vkCreateAccelerationStructureKHR pfn_CreateAccelerationStructureKHR = nullptr;
    PFN_vkCmdBuildAccelerationStructureKHR pfn_CmdBuildAccelerationStructureKHR = nullptr;
    PFN_vkCmdBuildAccelerationStructureIndirectKHR pfn_CmdBuildAccelerationStructureIndirectKHR = nullptr;
    PFN_vkBuildAccelerationStructureKHR pfn_BuildAccelerationStructureKHR = nullptr;
    PFN_vkGetAccelerationStructureDeviceAddressKHR pfn_GetAccelerationStructureDeviceAddressKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkGetImageDrmFormatModifierPropertiesEXT pfn_GetImageDrmFormatModifierPropertiesEXT = nullptr;
    PFN_vkCreateValidationCacheEXT pfn_CreateValidationCacheEXT = nullptr;
    PFN_vkDestroyValidationCacheEXT pfn_DestroyValidationCacheEXT = nullptr;
    PFN_vkGetValidationCacheDataEXT pfn_GetValidationCacheDataEXT = nullptr;
    PFN_vkMergeValidationCachesEXT pfn_MergeValidationCachesEXT = nullptr;
    PFN_vkCmdBindShadingRateImageNV pfn_CmdBindShadingRateImageNV = nullptr;
    PFN_vkCmdSetViewportShadingRatePaletteNV pfn_CmdSetViewportShadingRatePaletteNV = nullptr;
    PFN_vkCmdSetCoarseSampleOrderNV pfn_CmdSetCoarseSampleOrderNV = nullptr;
    PFN_vkCompileDeferredNV pfn_CompileDeferredNV = nullptr;
    PFN_vkCreateAccelerationStructureNV pfn_CreateAccelerationStructureNV = nullptr;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV pfn_GetAccelerationStructureMemoryRequirementsNV = nullptr;
    PFN_vkCmdCopyAccelerationStructureNV pfn_CmdCopyAccelerationStructureNV = nullptr;
    PFN_vkCmdBuildAccelerationStructureNV pfn_CmdBuildAccelerationStructureNV = nullptr;
    PFN_vkCmdTraceRaysNV pfn_CmdTraceRaysNV = nullptr;
    PFN_vkGetAccelerationStructureHandleNV pfn_GetAccelerationStructureHandleNV = nullptr;
    PFN_vkCreateRayTracingPipelinesNV pfn_CreateRayTracingPipelinesNV = nullptr;
    PFN_vkGetMemoryHostPointerPropertiesEXT pfn_GetMemoryHostPointerPropertiesEXT = nullptr;
    PFN_vkCmdWriteBufferMarkerAMD pfn_CmdWriteBufferMarkerAMD = nullptr;
    PFN_vkGetCalibratedTimestampsEXT pfn_GetCalibratedTimestampsEXT = nullptr;
    PFN_vkCmdDrawMeshTasksNV pfn_CmdDrawMeshTasksNV = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectNV pfn_CmdDrawMeshTasksIndirectNV = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectCountNV pfn_CmdDrawMeshTasksIndirectCountNV = nullptr;
    PFN_vkCmdSetExclusiveScissorNV pfn_CmdSetExclusiveScissorNV = nullptr;
    PFN_vkCmdSetCheckpointNV pfn_CmdSetCheckpointNV = nullptr;
    PFN_vkGetQueueCheckpointDataNV pfn_GetQueueCheckpointDataNV = nullptr;
    PFN_vkInitializePerformanceApiINTEL pfn_InitializePerformanceApiINTEL = nullptr;
    PFN_vkUninitializePerformanceApiINTEL pfn_UninitializePerformanceApiINTEL = nullptr;
    PFN_vkCmdSetPerformanceMarkerINTEL pfn_CmdSetPerformanceMarkerINTEL = nullptr;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL pfn_CmdSetPerformanceStreamMarkerINTEL = nullptr;
    PFN_vkCmdSetPerformanceOverrideINTEL pfn_CmdSetPerformanceOverrideINTEL = nullptr;
    PFN_vkAcquirePerformanceConfigurationINTEL pfn_AcquirePerformanceConfigurationINTEL = nullptr;
    PFN_vkReleasePerformanceConfigurationINTEL pfn_ReleasePerformanceConfigurationINTEL = nullptr;
    PFN_vkQueueSetPerformanceConfigurationINTEL pfn_QueueSetPerformanceConfigurationINTEL = nullptr;
    PFN_vkGetPerformanceParameterINTEL pfn_GetPerformanceParameterINTEL = nullptr;
    PFN_vkSetLocalDimmingAMD pfn_SetLocalDimmingAMD = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkAcquireFullScreenExclusiveModeEXT pfn_AcquireFullScreenExclusiveModeEXT = nullptr;
    PFN_vkReleaseFullScreenExclusiveModeEXT pfn_ReleaseFullScreenExclusiveModeEXT = nullptr;
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT pfn_GetDeviceGroupSurfacePresentModes2EXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkCmdSetLineStippleEXT pfn_CmdSetLineStippleEXT = nullptr;
    PFN_vkCmdSetCullModeEXT pfn_CmdSetCullModeEXT = nullptr;
    PFN_vkCmdSetFrontFaceEXT pfn_CmdSetFrontFaceEXT = nullptr;
    PFN_vkCmdSetPrimitiveTopologyEXT pfn_CmdSetPrimitiveTopologyEXT = nullptr;
    PFN_vkCmdSetViewportWithCountEXT pfn_CmdSetViewportWithCountEXT = nullptr;
    PFN_vkCmdSetScissorWithCountEXT pfn_CmdSetScissorWithCountEXT = nullptr;
    PFN_vkCmdBindVertexBuffers2EXT pfn_CmdBindVertexBuffers2EXT = nullptr;
    PFN_vkCmdSetDepthTestEnableEXT pfn_CmdSetDepthTestEnableEXT = nullptr;
    PFN_vkCmdSetDepthWriteEnableEXT pfn_CmdSetDepthWriteEnableEXT = nullptr;
    PFN_vkCmdSetDepthCompareOpEXT pfn_CmdSetDepthCompareOpEXT = nullptr;
    PFN_vkCmdSetDepthBoundsTestEnableEXT pfn_CmdSetDepthBoundsTestEnableEXT = nullptr;
    PFN_vkCmdSetStencilTestEnableEXT pfn_CmdSetStencilTestEnableEXT = nullptr;
    PFN_vkCmdSetStencilOpEXT pfn_CmdSetStencilOpEXT = nullptr;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCreateDeferredOperationKHR pfn_CreateDeferredOperationKHR = nullptr;
    PFN_vkDestroyDeferredOperationKHR pfn_DestroyDeferredOperationKHR = nullptr;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR pfn_GetDeferredOperationMaxConcurrencyKHR = nullptr;
    PFN_vkGetDeferredOperationResultKHR pfn_GetDeferredOperationResultKHR = nullptr;
    PFN_vkDeferredOperationJoinKHR pfn_DeferredOperationJoinKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkGetPipelineExecutablePropertiesKHR pfn_GetPipelineExecutablePropertiesKHR = nullptr;
    PFN_vkGetPipelineExecutableStatisticsKHR pfn_GetPipelineExecutableStatisticsKHR = nullptr;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR pfn_GetPipelineExecutableInternalRepresentationsKHR = nullptr;
    PFN_vkCmdExecuteGeneratedCommandsNV pfn_CmdExecuteGeneratedCommandsNV = nullptr;
    PFN_vkCmdPreprocessGeneratedCommandsNV pfn_CmdPreprocessGeneratedCommandsNV = nullptr;
    PFN_vkCmdBindPipelineShaderGroupNV pfn_CmdBindPipelineShaderGroupNV = nullptr;
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV pfn_GetGeneratedCommandsMemoryRequirementsNV = nullptr;
    PFN_vkCreateIndirectCommandsLayoutNV pfn_CreateIndirectCommandsLayoutNV = nullptr;
    PFN_vkDestroyIndirectCommandsLayoutNV pfn_DestroyIndirectCommandsLayoutNV = nullptr;
    PFN_vkCreatePrivateDataSlotEXT pfn_CreatePrivateDataSlotEXT = nullptr;
    PFN_vkDestroyPrivateDataSlotEXT pfn_DestroyPrivateDataSlotEXT = nullptr;
    PFN_vkSetPrivateDataEXT pfn_SetPrivateDataEXT = nullptr;
    PFN_vkGetPrivateDataEXT pfn_GetPrivateDataEXT = nullptr;
    PFN_vkCmdCopyBuffer2KHR pfn_CmdCopyBuffer2KHR = nullptr;
    PFN_vkCmdCopyImage2KHR pfn_CmdCopyImage2KHR = nullptr;
    PFN_vkCmdBlitImage2KHR pfn_CmdBlitImage2KHR = nullptr;
    PFN_vkCmdCopyBufferToImage2KHR pfn_CmdCopyBufferToImage2KHR = nullptr;
    PFN_vkCmdCopyImageToBuffer2KHR pfn_CmdCopyImageToBuffer2KHR = nullptr;
    PFN_vkCmdResolveImage2KHR pfn_CmdResolveImage2KHR = nullptr;
    void DestroyDevice(const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Queue GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const;
    [[nodiscard]] Result QueueSubmit(Queue queue, uint32_t submitCount, const SubmitInfo* pSubmits, Fence fence) const;
    [[nodiscard]] Result QueueSubmit(Queue queue, std::span<SubmitInfo> Submits, Fence fence) const;
    [[nodiscard]] Result QueueWaitIdle(Queue queue) const;
    [[nodiscard]] Result DeviceWaitIdle() const;
    [[nodiscard]] expected<DeviceMemory> AllocateMemory(const MemoryAllocateInfo&  pAllocateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void FreeMemory(DeviceMemory memory, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<void*> MapMemory(DeviceMemory memory, DeviceSize offset, DeviceSize size, MemoryMapFlags flags) const;
    void UnmapMemory(DeviceMemory memory) const;
    [[nodiscard]] Result FlushMappedMemoryRanges(uint32_t memoryRangeCount, const MappedMemoryRange* pMemoryRanges) const;
    [[nodiscard]] Result FlushMappedMemoryRanges(std::span<MappedMemoryRange> MemoryRanges) const;
    [[nodiscard]] Result InvalidateMappedMemoryRanges(uint32_t memoryRangeCount, const MappedMemoryRange* pMemoryRanges) const;
    [[nodiscard]] Result InvalidateMappedMemoryRanges(std::span<MappedMemoryRange> MemoryRanges) const;
    [[nodiscard]] DeviceSize GetDeviceMemoryCommitment(DeviceMemory memory) const;
    [[nodiscard]] MemoryRequirements GetBufferMemoryRequirements(Buffer buffer) const;
    [[nodiscard]] Result BindBufferMemory(Buffer buffer, DeviceMemory memory, DeviceSize memoryOffset) const;
    [[nodiscard]] MemoryRequirements GetImageMemoryRequirements(Image image) const;
    [[nodiscard]] Result BindImageMemory(Image image, DeviceMemory memory, DeviceSize memoryOffset) const;
    [[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements> GetImageSparseMemoryRequirements(Image image) const;
    [[nodiscard]] Result QueueBindSparse(Queue queue, uint32_t bindInfoCount, const BindSparseInfo* pBindInfo, Fence fence) const;
    [[nodiscard]] Result QueueBindSparse(Queue queue, std::span<BindSparseInfo> BindInfo, Fence fence) const;
    [[nodiscard]] expected<Fence> CreateFence(const FenceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyFence(Fence fence, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result ResetFences(uint32_t fenceCount, const Fence* pFences) const;
    [[nodiscard]] Result ResetFences(std::span<Fence> Fences) const;
    [[nodiscard]] Result GetFenceStatus(Fence fence) const;
    [[nodiscard]] Result WaitForFences(uint32_t fenceCount, const Fence* pFences, Bool32 waitAll, uint64_t timeout) const;
    [[nodiscard]] Result WaitForFences(std::span<Fence> Fences, Bool32 waitAll, uint64_t timeout) const;
    [[nodiscard]] expected<Semaphore> CreateSemaphore(const SemaphoreCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroySemaphore(Semaphore semaphore, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<Event> CreateEvent(const EventCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyEvent(Event event, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result GetEventStatus(Event event) const;
    [[nodiscard]] Result SetEvent(Event event) const;
    [[nodiscard]] Result ResetEvent(Event event) const;
    [[nodiscard]] expected<QueryPool> CreateQueryPool(const QueryPoolCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyQueryPool(QueryPool queryPool, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result GetQueryPoolResults(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, DeviceSize stride, QueryResultFlags flags) const;
    [[nodiscard]] Result GetQueryPoolResults(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, std::span<std::byte> Data, DeviceSize stride, QueryResultFlags flags) const;
    [[nodiscard]] expected<Buffer> CreateBuffer(const BufferCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyBuffer(Buffer buffer, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<BufferView> CreateBufferView(const BufferViewCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyBufferView(BufferView bufferView, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<Image> CreateImage(const ImageCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyImage(Image image, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] SubresourceLayout GetImageSubresourceLayout(Image image, const ImageSubresource&  pSubresource) const;
    [[nodiscard]] expected<ImageView> CreateImageView(const ImageViewCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyImageView(ImageView imageView, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<ShaderModule> CreateShaderModule(const ShaderModuleCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyShaderModule(ShaderModule shaderModule, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<PipelineCache> CreatePipelineCache(const PipelineCacheCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyPipelineCache(PipelineCache pipelineCache, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetPipelineCacheData(PipelineCache pipelineCache) const;
    [[nodiscard]] Result MergePipelineCaches(PipelineCache dstCache, uint32_t srcCacheCount, const PipelineCache* pSrcCaches) const;
    [[nodiscard]] Result MergePipelineCaches(PipelineCache dstCache, std::span<PipelineCache> SrcCaches) const;
    [[nodiscard]] Result CreateGraphicsPipelines(PipelineCache pipelineCache, uint32_t createInfoCount, const GraphicsPipelineCreateInfo* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines) const;
    [[nodiscard]] Result CreateGraphicsPipelines(PipelineCache pipelineCache, std::span<GraphicsPipelineCreateInfo> CreateInfos, const AllocationCallbacks* pAllocator, std::span<Pipeline> Pipelines) const;
    [[nodiscard]] Result CreateComputePipelines(PipelineCache pipelineCache, uint32_t createInfoCount, const ComputePipelineCreateInfo* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines) const;
    [[nodiscard]] Result CreateComputePipelines(PipelineCache pipelineCache, std::span<ComputePipelineCreateInfo> CreateInfos, const AllocationCallbacks* pAllocator, std::span<Pipeline> Pipelines) const;
    void DestroyPipeline(Pipeline pipeline, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<PipelineLayout> CreatePipelineLayout(const PipelineLayoutCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyPipelineLayout(PipelineLayout pipelineLayout, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<Sampler> CreateSampler(const SamplerCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroySampler(Sampler sampler, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<DescriptorSetLayout> CreateDescriptorSetLayout(const DescriptorSetLayoutCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyDescriptorSetLayout(DescriptorSetLayout descriptorSetLayout, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<DescriptorPool> CreateDescriptorPool(const DescriptorPoolCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyDescriptorPool(DescriptorPool descriptorPool, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result ResetDescriptorPool(DescriptorPool descriptorPool, DescriptorPoolResetFlags flags) const;
    [[nodiscard]] Result AllocateDescriptorSets(const DescriptorSetAllocateInfo&  pAllocateInfo, DescriptorSet* pDescriptorSets) const;
    [[nodiscard]] Result FreeDescriptorSets(DescriptorPool descriptorPool, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets) const;
    [[nodiscard]] Result FreeDescriptorSets(DescriptorPool descriptorPool, std::span<DescriptorSet> DescriptorSets) const;
    void UpdateDescriptorSets(uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const CopyDescriptorSet* pDescriptorCopies) const;
    void UpdateDescriptorSets(std::span<WriteDescriptorSet> DescriptorWrites, std::span<CopyDescriptorSet> DescriptorCopies) const;
    [[nodiscard]] expected<Framebuffer> CreateFramebuffer(const FramebufferCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyFramebuffer(Framebuffer framebuffer, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<RenderPass> CreateRenderPass(const RenderPassCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyRenderPass(RenderPass renderPass, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Extent2D GetRenderAreaGranularity(RenderPass renderPass) const;
    [[nodiscard]] expected<CommandPool> CreateCommandPool(const CommandPoolCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyCommandPool(CommandPool commandPool, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result ResetCommandPool(CommandPool commandPool, CommandPoolResetFlags flags) const;
    [[nodiscard]] Result AllocateCommandBuffers(const CommandBufferAllocateInfo&  pAllocateInfo, CommandBuffer* pCommandBuffers) const;
    void FreeCommandBuffers(CommandPool commandPool, uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers) const;
    void FreeCommandBuffers(CommandPool commandPool, std::span<CommandBuffer> CommandBuffers) const;
    [[nodiscard]] Result BeginCommandBuffer(CommandBuffer commandBuffer, const CommandBufferBeginInfo&  pBeginInfo) const;
    [[nodiscard]] Result EndCommandBuffer(CommandBuffer commandBuffer) const;
    [[nodiscard]] Result ResetCommandBuffer(CommandBuffer commandBuffer, CommandBufferResetFlags flags) const;
    void CmdBindPipeline(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, Pipeline pipeline) const;
    void CmdSetViewport(CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const Viewport* pViewports) const;
    void CmdSetViewport(CommandBuffer commandBuffer, uint32_t firstViewport, std::span<Viewport> Viewports) const;
    void CmdSetScissor(CommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const Rect2D* pScissors) const;
    void CmdSetScissor(CommandBuffer commandBuffer, uint32_t firstScissor, std::span<Rect2D> Scissors) const;
    void CmdSetLineWidth(CommandBuffer commandBuffer, float lineWidth) const;
    void CmdSetDepthBias(CommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const;
    void CmdSetBlendConstants(CommandBuffer commandBuffer, const float blendConstants[4]) const;
    void CmdSetDepthBounds(CommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) const;
    void CmdSetStencilCompareMask(CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t compareMask) const;
    void CmdSetStencilWriteMask(CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t writeMask) const;
    void CmdSetStencilReference(CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t reference) const;
    void CmdBindDescriptorSets(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) const;
    void CmdBindDescriptorSets(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, std::span<DescriptorSet> DescriptorSets, std::span<uint32_t> DynamicOffsets) const;
    void CmdBindIndexBuffer(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, IndexType indexType) const;
    void CmdBindVertexBuffers(CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets) const;
    void CmdBindVertexBuffers(CommandBuffer commandBuffer, uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets) const;
    void CmdDraw(CommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;
    void CmdDrawIndexed(CommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const;
    void CmdDrawIndirect(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    void CmdDrawIndexedIndirect(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    void CmdDispatch(CommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
    void CmdDispatchIndirect(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset) const;
    void CmdCopyBuffer(CommandBuffer commandBuffer, Buffer srcBuffer, Buffer dstBuffer, uint32_t regionCount, const BufferCopy* pRegions) const;
    void CmdCopyBuffer(CommandBuffer commandBuffer, Buffer srcBuffer, Buffer dstBuffer, std::span<BufferCopy> Regions) const;
    void CmdCopyImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageCopy* pRegions) const;
    void CmdCopyImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageCopy> Regions) const;
    void CmdBlitImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageBlit* pRegions, Filter filter) const;
    void CmdBlitImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageBlit> Regions, Filter filter) const;
    void CmdCopyBufferToImage(CommandBuffer commandBuffer, Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const BufferImageCopy* pRegions) const;
    void CmdCopyBufferToImage(CommandBuffer commandBuffer, Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, std::span<BufferImageCopy> Regions) const;
    void CmdCopyImageToBuffer(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, uint32_t regionCount, const BufferImageCopy* pRegions) const;
    void CmdCopyImageToBuffer(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, std::span<BufferImageCopy> Regions) const;
    void CmdUpdateBuffer(CommandBuffer commandBuffer, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize dataSize, const void* pData) const;
    void CmdUpdateBuffer(CommandBuffer commandBuffer, Buffer dstBuffer, DeviceSize dstOffset, std::span<std::byte> Data) const;
    void CmdFillBuffer(CommandBuffer commandBuffer, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize size, uint32_t data) const;
    void CmdClearColorImage(CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const;
    void CmdClearColorImage(CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, std::span<ImageSubresourceRange> Ranges) const;
    void CmdClearDepthStencilImage(CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const;
    void CmdClearDepthStencilImage(CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, std::span<ImageSubresourceRange> Ranges) const;
    void CmdClearAttachments(CommandBuffer commandBuffer, uint32_t attachmentCount, const ClearAttachment* pAttachments, uint32_t rectCount, const ClearRect* pRects) const;
    void CmdClearAttachments(CommandBuffer commandBuffer, std::span<ClearAttachment> Attachments, std::span<ClearRect> Rects) const;
    void CmdResolveImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageResolve* pRegions) const;
    void CmdResolveImage(CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageResolve> Regions) const;
    void CmdSetEvent(CommandBuffer commandBuffer, Event event, PipelineStageFlags stageMask) const;
    void CmdResetEvent(CommandBuffer commandBuffer, Event event, PipelineStageFlags stageMask) const;
    void CmdWaitEvents(CommandBuffer commandBuffer, uint32_t eventCount, const Event* pEvents, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const;
    void CmdWaitEvents(CommandBuffer commandBuffer, std::span<Event> Events, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, std::span<MemoryBarrier> MemoryBarriers, std::span<BufferMemoryBarrier> BufferMemoryBarriers, std::span<ImageMemoryBarrier> ImageMemoryBarriers) const;
    void CmdPipelineBarrier(CommandBuffer commandBuffer, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const;
    void CmdPipelineBarrier(CommandBuffer commandBuffer, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, std::span<MemoryBarrier> MemoryBarriers, std::span<BufferMemoryBarrier> BufferMemoryBarriers, std::span<ImageMemoryBarrier> ImageMemoryBarriers) const;
    void CmdBeginQuery(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, QueryControlFlags flags) const;
    void CmdEndQuery(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query) const;
    void CmdResetQueryPool(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const;
    void CmdWriteTimestamp(CommandBuffer commandBuffer, PipelineStageFlagBits pipelineStage, QueryPool queryPool, uint32_t query) const;
    void CmdCopyQueryPoolResults(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize stride, QueryResultFlags flags) const;
    void CmdPushConstants(CommandBuffer commandBuffer, PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) const;
    void CmdPushConstants(CommandBuffer commandBuffer, PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, std::span<std::byte> Values) const;
    void CmdBeginRenderPass(CommandBuffer commandBuffer, const RenderPassBeginInfo&  pRenderPassBegin, SubpassContents contents) const;
    void CmdNextSubpass(CommandBuffer commandBuffer, SubpassContents contents) const;
    void CmdEndRenderPass(CommandBuffer commandBuffer) const;
    void CmdExecuteCommands(CommandBuffer commandBuffer, uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers) const;
    void CmdExecuteCommands(CommandBuffer commandBuffer, std::span<CommandBuffer> CommandBuffers) const;
    [[nodiscard]] Result BindBufferMemory2(uint32_t bindInfoCount, const BindBufferMemoryInfo* pBindInfos) const;
    [[nodiscard]] Result BindBufferMemory2(std::span<BindBufferMemoryInfo> BindInfos) const;
    [[nodiscard]] Result BindImageMemory2(uint32_t bindInfoCount, const BindImageMemoryInfo* pBindInfos) const;
    [[nodiscard]] Result BindImageMemory2(std::span<BindImageMemoryInfo> BindInfos) const;
    [[nodiscard]] PeerMemoryFeatureFlags GetDeviceGroupPeerMemoryFeatures(uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex) const;
    void CmdSetDeviceMask(CommandBuffer commandBuffer, uint32_t deviceMask) const;
    void CmdDispatchBase(CommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
    [[nodiscard]] MemoryRequirements2 GetBufferMemoryRequirements2(const BufferMemoryRequirementsInfo2&  pInfo) const;
    [[nodiscard]] MemoryRequirements2 GetImageMemoryRequirements2(const ImageMemoryRequirementsInfo2&  pInfo) const;
    [[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements2> GetImageSparseMemoryRequirements2(const ImageSparseMemoryRequirementsInfo2&  pInfo) const;
    void TrimCommandPool(CommandPool commandPool, CommandPoolTrimFlags flags) const;
    [[nodiscard]] Queue GetDeviceQueue2(const DeviceQueueInfo2&  pQueueInfo) const;
    [[nodiscard]] expected<SamplerYcbcrConversion> CreateSamplerYcbcrConversion(const SamplerYcbcrConversionCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroySamplerYcbcrConversion(SamplerYcbcrConversion ycbcrConversion, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<DescriptorUpdateTemplate> CreateDescriptorUpdateTemplate(const DescriptorUpdateTemplateCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyDescriptorUpdateTemplate(DescriptorUpdateTemplate descriptorUpdateTemplate, const AllocationCallbacks* pAllocator = nullptr) const;
    void UpdateDescriptorSetWithTemplate(DescriptorSet descriptorSet, DescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) const;
    [[nodiscard]] DescriptorSetLayoutSupport GetDescriptorSetLayoutSupport(const DescriptorSetLayoutCreateInfo&  pCreateInfo) const;
    void CmdDrawIndirectCount(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    void CmdDrawIndexedIndirectCount(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    [[nodiscard]] expected<RenderPass> CreateRenderPass2(const RenderPassCreateInfo2&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void CmdBeginRenderPass2(CommandBuffer commandBuffer, const RenderPassBeginInfo&  pRenderPassBegin, const SubpassBeginInfo&  pSubpassBeginInfo) const;
    void CmdNextSubpass2(CommandBuffer commandBuffer, const SubpassBeginInfo&  pSubpassBeginInfo, const SubpassEndInfo&  pSubpassEndInfo) const;
    void CmdEndRenderPass2(CommandBuffer commandBuffer, const SubpassEndInfo&  pSubpassEndInfo) const;
    void ResetQueryPool(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const;
    [[nodiscard]] expected<uint64_t> GetSemaphoreCounterValue(Semaphore semaphore) const;
    [[nodiscard]] Result WaitSemaphores(const SemaphoreWaitInfo&  pWaitInfo, uint64_t timeout) const;
    [[nodiscard]] Result SignalSemaphore(const SemaphoreSignalInfo&  pSignalInfo) const;
    [[nodiscard]] uint64_t GetBufferOpaqueCaptureAddress(const BufferDeviceAddressInfo&  pInfo) const;
    [[nodiscard]] VkDeviceAddress GetBufferDeviceAddress(const BufferDeviceAddressInfo&  pInfo) const;
    [[nodiscard]] uint64_t GetDeviceMemoryOpaqueCaptureAddress(const DeviceMemoryOpaqueCaptureAddressInfo&  pInfo) const;
    [[nodiscard]] expected<SwapchainKHR> CreateSwapchainKHR(const SwapchainCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroySwapchainKHR(SwapchainKHR swapchain, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<Image>> GetSwapchainImagesKHR(SwapchainKHR swapchain) const;
    [[nodiscard]] expected<uint32_t> AcquireNextImageKHR(SwapchainKHR swapchain, uint64_t timeout, Semaphore semaphore, Fence fence) const;
    [[nodiscard]] Result QueuePresentKHR(Queue queue, const PresentInfoKHR&  pPresentInfo) const;
    [[nodiscard]] expected<DeviceGroupPresentCapabilitiesKHR> GetDeviceGroupPresentCapabilitiesKHR() const;
    [[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface) const;
    [[nodiscard]] expected<uint32_t> AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo) const;
    [[nodiscard]] Result CreateSharedSwapchainsKHR(uint32_t swapchainCount, const SwapchainCreateInfoKHR* pCreateInfos, const AllocationCallbacks* pAllocator, SwapchainKHR* pSwapchains) const;
    [[nodiscard]] Result CreateSharedSwapchainsKHR(std::span<SwapchainCreateInfoKHR> CreateInfos, const AllocationCallbacks* pAllocator, std::span<SwapchainKHR> Swapchains) const;
    [[nodiscard]] Result DebugMarkerSetObjectNameEXT(const DebugMarkerObjectNameInfoEXT&  pNameInfo) const;
    [[nodiscard]] Result DebugMarkerSetObjectTagEXT(const DebugMarkerObjectTagInfoEXT&  pTagInfo) const;
    void CmdDebugMarkerBeginEXT(CommandBuffer commandBuffer, const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const;
    void CmdDebugMarkerEndEXT(CommandBuffer commandBuffer) const;
    void CmdDebugMarkerInsertEXT(CommandBuffer commandBuffer, const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const;
    void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes) const;
    void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer, uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets, std::span<DeviceSize> Sizes) const;
    void CmdBeginTransformFeedbackEXT(CommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const;
    void CmdBeginTransformFeedbackEXT(CommandBuffer commandBuffer, uint32_t firstCounterBuffer, std::span<Buffer> CounterBuffers, std::span<DeviceSize> CounterBufferOffsets) const;
    void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const;
    void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer, uint32_t firstCounterBuffer, std::span<Buffer> CounterBuffers, std::span<DeviceSize> CounterBufferOffsets) const;
    void CmdBeginQueryIndexedEXT(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, QueryControlFlags flags, uint32_t index) const;
    void CmdEndQueryIndexedEXT(CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, uint32_t index) const;
    void CmdDrawIndirectByteCountEXT(CommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, Buffer counterBuffer, DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const;
    [[nodiscard]] uint32_t GetImageViewHandleNVX(const ImageViewHandleInfoNVX&  pInfo) const;
    [[nodiscard]] expected<ImageViewAddressPropertiesNVX> GetImageViewAddressNVX(ImageView imageView) const;
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetShaderInfoAMD(Pipeline pipeline, ShaderStageFlagBits shaderStage, ShaderInfoTypeAMD infoType) const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<HANDLE> GetMemoryWin32HandleNV(DeviceMemory memory, ExternalMemoryHandleTypeFlagsNV handleType) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<HANDLE> GetMemoryWin32HandleKHR(const MemoryGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<MemoryWin32HandlePropertiesKHR> GetMemoryWin32HandlePropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, HANDLE handle) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    [[nodiscard]] expected<int> GetMemoryFdKHR(const MemoryGetFdInfoKHR&  pGetFdInfo) const;
    [[nodiscard]] expected<MemoryFdPropertiesKHR> GetMemoryFdPropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, int fd) const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<HANDLE> GetSemaphoreWin32HandleKHR(const SemaphoreGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result ImportSemaphoreWin32HandleKHR(const ImportSemaphoreWin32HandleInfoKHR&  pImportSemaphoreWin32HandleInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    [[nodiscard]] expected<int> GetSemaphoreFdKHR(const SemaphoreGetFdInfoKHR&  pGetFdInfo) const;
    [[nodiscard]] Result ImportSemaphoreFdKHR(const ImportSemaphoreFdInfoKHR&  pImportSemaphoreFdInfo) const;
    void CmdPushDescriptorSetKHR(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites) const;
    void CmdPushDescriptorSetKHR(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, std::span<WriteDescriptorSet> DescriptorWrites) const;
    void CmdPushDescriptorSetWithTemplateKHR(CommandBuffer commandBuffer, DescriptorUpdateTemplate descriptorUpdateTemplate, PipelineLayout layout, uint32_t set, const void* pData) const;
    void CmdBeginConditionalRenderingEXT(CommandBuffer commandBuffer, const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const;
    void CmdEndConditionalRenderingEXT(CommandBuffer commandBuffer) const;
    void CmdSetViewportWScalingNV(CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const ViewportWScalingNV* pViewportWScalings) const;
    void CmdSetViewportWScalingNV(CommandBuffer commandBuffer, uint32_t firstViewport, std::span<ViewportWScalingNV> ViewportWScalings) const;
    [[nodiscard]] Result DisplayPowerControlEXT(DisplayKHR display, const DisplayPowerInfoEXT&  pDisplayPowerInfo) const;
    [[nodiscard]] expected<Fence> RegisterDeviceEventEXT(const DeviceEventInfoEXT&  pDeviceEventInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<Fence> RegisterDisplayEventEXT(DisplayKHR display, const DisplayEventInfoEXT&  pDisplayEventInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<uint64_t> GetSwapchainCounterEXT(SwapchainKHR swapchain, SurfaceCounterFlagBitsEXT counter) const;
    [[nodiscard]] expected<RefreshCycleDurationGOOGLE> GetRefreshCycleDurationGOOGLE(SwapchainKHR swapchain) const;
    [[nodiscard]] expected<detail::fixed_vector<PastPresentationTimingGOOGLE>> GetPastPresentationTimingGOOGLE(SwapchainKHR swapchain) const;
    void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const Rect2D* pDiscardRectangles) const;
    void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer, uint32_t firstDiscardRectangle, std::span<Rect2D> DiscardRectangles) const;
    void SetHdrMetadataEXT(uint32_t swapchainCount, const SwapchainKHR* pSwapchains, const HdrMetadataEXT* pMetadata) const;
    void SetHdrMetadataEXT(std::span<SwapchainKHR> Swapchains, std::span<HdrMetadataEXT> Metadata) const;
    [[nodiscard]] Result GetSwapchainStatusKHR(SwapchainKHR swapchain) const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<HANDLE> GetFenceWin32HandleKHR(const FenceGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result ImportFenceWin32HandleKHR(const ImportFenceWin32HandleInfoKHR&  pImportFenceWin32HandleInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    [[nodiscard]] expected<int> GetFenceFdKHR(const FenceGetFdInfoKHR&  pGetFdInfo) const;
    [[nodiscard]] Result ImportFenceFdKHR(const ImportFenceFdInfoKHR&  pImportFenceFdInfo) const;
    [[nodiscard]] Result AcquireProfilingLockKHR(const AcquireProfilingLockInfoKHR&  pInfo) const;
    void ReleaseProfilingLockKHR() const;
    [[nodiscard]] Result SetDebugUtilsObjectNameEXT(const DebugUtilsObjectNameInfoEXT&  pNameInfo) const;
    [[nodiscard]] Result SetDebugUtilsObjectTagEXT(const DebugUtilsObjectTagInfoEXT&  pTagInfo) const;
    void QueueBeginDebugUtilsLabelEXT(Queue queue, const DebugUtilsLabelEXT&  pLabelInfo) const;
    void QueueEndDebugUtilsLabelEXT(Queue queue) const;
    void QueueInsertDebugUtilsLabelEXT(Queue queue, const DebugUtilsLabelEXT&  pLabelInfo) const;
    void CmdBeginDebugUtilsLabelEXT(CommandBuffer commandBuffer, const DebugUtilsLabelEXT&  pLabelInfo) const;
    void CmdEndDebugUtilsLabelEXT(CommandBuffer commandBuffer) const;
    void CmdInsertDebugUtilsLabelEXT(CommandBuffer commandBuffer, const DebugUtilsLabelEXT&  pLabelInfo) const;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    [[nodiscard]] expected<AndroidHardwareBufferPropertiesANDROID> GetAndroidHardwareBufferPropertiesANDROID(const AHardwareBuffer&  buffer) const;
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    [[nodiscard]] expected<AHardwareBuffer*> GetMemoryAndroidHardwareBufferANDROID(const MemoryGetAndroidHardwareBufferInfoANDROID&  pInfo) const;
#endif // VK_USE_PLATFORM_ANDROID_KHR
    void CmdSetSampleLocationsEXT(CommandBuffer commandBuffer, const SampleLocationsInfoEXT&  pSampleLocationsInfo) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void DestroyAccelerationStructureKHR(AccelerationStructureKHR accelerationStructure, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] MemoryRequirements2 GetAccelerationStructureMemoryRequirementsKHR(const AccelerationStructureMemoryRequirementsInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result BindAccelerationStructureMemoryKHR(uint32_t bindInfoCount, const BindAccelerationStructureMemoryInfoKHR* pBindInfos) const;
    [[nodiscard]] Result BindAccelerationStructureMemoryKHR(std::span<BindAccelerationStructureMemoryInfoKHR> BindInfos) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdCopyAccelerationStructureKHR(CommandBuffer commandBuffer, const CopyAccelerationStructureInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdCopyAccelerationStructureToMemoryKHR(CommandBuffer commandBuffer, const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdCopyMemoryToAccelerationStructureKHR(CommandBuffer commandBuffer, const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer, uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const;
    void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer, std::span<AccelerationStructureKHR> AccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result WriteAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, size_t dataSize, void* pData, size_t stride) const;
    [[nodiscard]] Result WriteAccelerationStructuresPropertiesKHR(std::span<AccelerationStructureKHR> AccelerationStructures, QueryType queryType, std::span<std::byte> Data, size_t stride) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdTraceRaysKHR(CommandBuffer commandBuffer, const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result GetRayTracingShaderGroupHandlesKHR(Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) const;
    [[nodiscard]] Result GetRayTracingShaderGroupHandlesKHR(Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, std::span<std::byte> Data) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result GetRayTracingCaptureReplayShaderGroupHandlesKHR(Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) const;
    [[nodiscard]] Result GetRayTracingCaptureReplayShaderGroupHandlesKHR(Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, std::span<std::byte> Data) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result CreateRayTracingPipelinesKHR(PipelineCache pipelineCache, uint32_t createInfoCount, const RayTracingPipelineCreateInfoKHR* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines) const;
    [[nodiscard]] Result CreateRayTracingPipelinesKHR(PipelineCache pipelineCache, std::span<RayTracingPipelineCreateInfoKHR> CreateInfos, const AllocationCallbacks* pAllocator, std::span<Pipeline> Pipelines) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdTraceRaysIndirectKHR(CommandBuffer commandBuffer, const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, Buffer buffer, DeviceSize offset) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result GetDeviceAccelerationStructureCompatibilityKHR(const AccelerationStructureVersionKHR&  version) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] expected<AccelerationStructureKHR> CreateAccelerationStructureKHR(const AccelerationStructureCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdBuildAccelerationStructureKHR(CommandBuffer commandBuffer, uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const;
    void CmdBuildAccelerationStructureKHR(CommandBuffer commandBuffer, std::span<AccelerationStructureBuildGeometryInfoKHR> Infos, std::span<AccelerationStructureBuildOffsetInfoKHR> pOffsetInfos) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void CmdBuildAccelerationStructureIndirectKHR(CommandBuffer commandBuffer, const AccelerationStructureBuildGeometryInfoKHR&  pInfo, Buffer indirectBuffer, DeviceSize indirectOffset, uint32_t indirectStride) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result BuildAccelerationStructureKHR(uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const;
    [[nodiscard]] Result BuildAccelerationStructureKHR(std::span<AccelerationStructureBuildGeometryInfoKHR> Infos, std::span<AccelerationStructureBuildOffsetInfoKHR> pOffsetInfos) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] VkDeviceAddress GetAccelerationStructureDeviceAddressKHR(const AccelerationStructureDeviceAddressInfoKHR&  pInfo) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
    [[nodiscard]] expected<ImageDrmFormatModifierPropertiesEXT> GetImageDrmFormatModifierPropertiesEXT(Image image) const;
    [[nodiscard]] expected<ValidationCacheEXT> CreateValidationCacheEXT(const ValidationCacheCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyValidationCacheEXT(ValidationCacheEXT validationCache, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<void*>> GetValidationCacheDataEXT(ValidationCacheEXT validationCache) const;
    [[nodiscard]] Result MergeValidationCachesEXT(ValidationCacheEXT dstCache, uint32_t srcCacheCount, const ValidationCacheEXT* pSrcCaches) const;
    [[nodiscard]] Result MergeValidationCachesEXT(ValidationCacheEXT dstCache, std::span<ValidationCacheEXT> SrcCaches) const;
    void CmdBindShadingRateImageNV(CommandBuffer commandBuffer, ImageView imageView, ImageLayout imageLayout) const;
    void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const ShadingRatePaletteNV* pShadingRatePalettes) const;
    void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer, uint32_t firstViewport, std::span<ShadingRatePaletteNV> ShadingRatePalettes) const;
    void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer, CoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const CoarseSampleOrderCustomNV* pCustomSampleOrders) const;
    void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer, CoarseSampleOrderTypeNV sampleOrderType, std::span<CoarseSampleOrderCustomNV> CustomSampleOrders) const;
    [[nodiscard]] Result CompileDeferredNV(Pipeline pipeline, uint32_t shader) const;
    [[nodiscard]] expected<AccelerationStructureNV> CreateAccelerationStructureNV(const AccelerationStructureCreateInfoNV&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] MemoryRequirements2KHR GetAccelerationStructureMemoryRequirementsNV(const AccelerationStructureMemoryRequirementsInfoNV&  pInfo) const;
    void CmdCopyAccelerationStructureNV(CommandBuffer commandBuffer, AccelerationStructureKHR dst, AccelerationStructureKHR src, CopyAccelerationStructureModeKHR mode) const;
    void CmdBuildAccelerationStructureNV(CommandBuffer commandBuffer, const AccelerationStructureInfoNV&  pInfo, Buffer instanceData, DeviceSize instanceOffset, Bool32 update, AccelerationStructureKHR dst, AccelerationStructureKHR src, Buffer scratch, DeviceSize scratchOffset) const;
    void CmdTraceRaysNV(CommandBuffer commandBuffer, Buffer raygenShaderBindingTableBuffer, DeviceSize raygenShaderBindingOffset, Buffer missShaderBindingTableBuffer, DeviceSize missShaderBindingOffset, DeviceSize missShaderBindingStride, Buffer hitShaderBindingTableBuffer, DeviceSize hitShaderBindingOffset, DeviceSize hitShaderBindingStride, Buffer callableShaderBindingTableBuffer, DeviceSize callableShaderBindingOffset, DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) const;
    [[nodiscard]] Result GetAccelerationStructureHandleNV(AccelerationStructureKHR accelerationStructure, size_t dataSize, void* pData) const;
    [[nodiscard]] Result GetAccelerationStructureHandleNV(AccelerationStructureKHR accelerationStructure, std::span<std::byte> Data) const;
    [[nodiscard]] Result CreateRayTracingPipelinesNV(PipelineCache pipelineCache, uint32_t createInfoCount, const RayTracingPipelineCreateInfoNV* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines) const;
    [[nodiscard]] Result CreateRayTracingPipelinesNV(PipelineCache pipelineCache, std::span<RayTracingPipelineCreateInfoNV> CreateInfos, const AllocationCallbacks* pAllocator, std::span<Pipeline> Pipelines) const;
    [[nodiscard]] expected<MemoryHostPointerPropertiesEXT> GetMemoryHostPointerPropertiesEXT(ExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer) const;
    void CmdWriteBufferMarkerAMD(CommandBuffer commandBuffer, PipelineStageFlagBits pipelineStage, Buffer dstBuffer, DeviceSize dstOffset, uint32_t marker) const;
    [[nodiscard]] expected<uint64_t> GetCalibratedTimestampsEXT(uint32_t timestampCount, const CalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps) const;
    [[nodiscard]] expected<uint64_t> GetCalibratedTimestampsEXT(std::span<CalibratedTimestampInfoEXT> TimestampInfos, std::span<uint64_t> Timestamps) const;
    void CmdDrawMeshTasksNV(CommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) const;
    void CmdDrawMeshTasksIndirectNV(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    void CmdDrawMeshTasksIndirectCountNV(CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    void CmdSetExclusiveScissorNV(CommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const Rect2D* pExclusiveScissors) const;
    void CmdSetExclusiveScissorNV(CommandBuffer commandBuffer, uint32_t firstExclusiveScissor, std::span<Rect2D> ExclusiveScissors) const;
    void CmdSetCheckpointNV(CommandBuffer commandBuffer, const void* pCheckpointMarker) const;
    [[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetQueueCheckpointDataNV(Queue queue) const;
    [[nodiscard]] Result InitializePerformanceApiINTEL(const InitializePerformanceApiInfoINTEL&  pInitializeInfo) const;
    void UninitializePerformanceApiINTEL() const;
    [[nodiscard]] Result CmdSetPerformanceMarkerINTEL(CommandBuffer commandBuffer, const PerformanceMarkerInfoINTEL&  pMarkerInfo) const;
    [[nodiscard]] Result CmdSetPerformanceStreamMarkerINTEL(CommandBuffer commandBuffer, const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const;
    [[nodiscard]] Result CmdSetPerformanceOverrideINTEL(CommandBuffer commandBuffer, const PerformanceOverrideInfoINTEL&  pOverrideInfo) const;
    [[nodiscard]] expected<PerformanceConfigurationINTEL> AcquirePerformanceConfigurationINTEL(const PerformanceConfigurationAcquireInfoINTEL&  pAcquireInfo) const;
    [[nodiscard]] Result ReleasePerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) const;
    [[nodiscard]] Result QueueSetPerformanceConfigurationINTEL(Queue queue, PerformanceConfigurationINTEL configuration) const;
    [[nodiscard]] expected<PerformanceValueINTEL> GetPerformanceParameterINTEL(PerformanceParameterTypeINTEL parameter) const;
    void SetLocalDimmingAMD(SwapchainKHR swapChain, Bool32 localDimmingEnable) const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result AcquireFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result ReleaseFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
#endif // VK_USE_PLATFORM_WIN32_KHR
    void CmdSetLineStippleEXT(CommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) const;
    void CmdSetCullModeEXT(CommandBuffer commandBuffer, CullModeFlags cullMode) const;
    void CmdSetFrontFaceEXT(CommandBuffer commandBuffer, FrontFace frontFace) const;
    void CmdSetPrimitiveTopologyEXT(CommandBuffer commandBuffer, PrimitiveTopology primitiveTopology) const;
    void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer, uint32_t viewportCount, const Viewport* pViewports) const;
    void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer, std::span<Viewport> Viewports) const;
    void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer, uint32_t scissorCount, const Rect2D* pScissors) const;
    void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer, std::span<Rect2D> Scissors) const;
    void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes, const DeviceSize* pStrides) const;
    void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer, uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets, std::span<DeviceSize> Sizes, std::span<DeviceSize> Strides) const;
    void CmdSetDepthTestEnableEXT(CommandBuffer commandBuffer, Bool32 depthTestEnable) const;
    void CmdSetDepthWriteEnableEXT(CommandBuffer commandBuffer, Bool32 depthWriteEnable) const;
    void CmdSetDepthCompareOpEXT(CommandBuffer commandBuffer, CompareOp depthCompareOp) const;
    void CmdSetDepthBoundsTestEnableEXT(CommandBuffer commandBuffer, Bool32 depthBoundsTestEnable) const;
    void CmdSetStencilTestEnableEXT(CommandBuffer commandBuffer, Bool32 stencilTestEnable) const;
    void CmdSetStencilOpEXT(CommandBuffer commandBuffer, StencilFaceFlags faceMask, StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] expected<DeferredOperationKHR> CreateDeferredOperationKHR(const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    void DestroyDeferredOperationKHR(DeferredOperationKHR operation, const AllocationCallbacks* pAllocator = nullptr) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] uint32_t GetDeferredOperationMaxConcurrencyKHR(DeferredOperationKHR operation) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result GetDeferredOperationResultKHR(DeferredOperationKHR operation) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result DeferredOperationJoinKHR(DeferredOperationKHR operation) const;
#endif // VK_ENABLE_BETA_EXTENSIONS
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutablePropertiesKHR>> GetPipelineExecutablePropertiesKHR(const PipelineInfoKHR&  pPipelineInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutableStatisticKHR>> GetPipelineExecutableStatisticsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<PipelineExecutableInternalRepresentationKHR>> GetPipelineExecutableInternalRepresentationsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const;
    void CmdExecuteGeneratedCommandsNV(CommandBuffer commandBuffer, Bool32 isPreprocessed, const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const;
    void CmdPreprocessGeneratedCommandsNV(CommandBuffer commandBuffer, const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const;
    void CmdBindPipelineShaderGroupNV(CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, Pipeline pipeline, uint32_t groupIndex) const;
    [[nodiscard]] MemoryRequirements2 GetGeneratedCommandsMemoryRequirementsNV(const GeneratedCommandsMemoryRequirementsInfoNV&  pInfo) const;
    [[nodiscard]] expected<IndirectCommandsLayoutNV> CreateIndirectCommandsLayoutNV(const IndirectCommandsLayoutCreateInfoNV&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyIndirectCommandsLayoutNV(IndirectCommandsLayoutNV indirectCommandsLayout, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<PrivateDataSlotEXT> CreatePrivateDataSlotEXT(const PrivateDataSlotCreateInfoEXT&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    void DestroyPrivateDataSlotEXT(PrivateDataSlotEXT privateDataSlot, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] Result SetPrivateDataEXT(ObjectType objectType, uint64_t objectHandle, PrivateDataSlotEXT privateDataSlot, uint64_t data) const;
    [[nodiscard]] uint64_t GetPrivateDataEXT(ObjectType objectType, uint64_t objectHandle, PrivateDataSlotEXT privateDataSlot) const;
    void CmdCopyBuffer2KHR(CommandBuffer commandBuffer, const CopyBufferInfo2KHR&  pCopyBufferInfo) const;
    void CmdCopyImage2KHR(CommandBuffer commandBuffer, const CopyImageInfo2KHR&  pCopyImageInfo) const;
    void CmdBlitImage2KHR(CommandBuffer commandBuffer, const BlitImageInfo2KHR&  pBlitImageInfo) const;
    void CmdCopyBufferToImage2KHR(CommandBuffer commandBuffer, const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const;
    void CmdCopyImageToBuffer2KHR(CommandBuffer commandBuffer, const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const;
    void CmdResolveImage2KHR(CommandBuffer commandBuffer, const ResolveImageInfo2KHR&  pResolveImageInfo) const;
    explicit DeviceFunctions() noexcept;
    explicit DeviceFunctions(InstanceFunctions const& instance_functions, Device device) noexcept;
};
struct PhysicalDeviceFunctions {
    InstanceFunctions const* instance_functions;
    PhysicalDevice physicaldevice;
    PhysicalDeviceFunctions() noexcept;
    PhysicalDeviceFunctions(InstanceFunctions const& instance_functions, PhysicalDevice const physicaldevice) noexcept;
    [[nodiscard]] PhysicalDeviceProperties GetProperties() const;
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetQueueFamilyProperties() const;
    [[nodiscard]] PhysicalDeviceMemoryProperties GetMemoryProperties() const;
    [[nodiscard]] PhysicalDeviceFeatures GetFeatures() const;
    [[nodiscard]] FormatProperties GetFormatProperties(Format format) const;
    [[nodiscard]] expected<ImageFormatProperties> GetImageFormatProperties(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags) const;
    [[nodiscard]] expected<Device> CreateDevice(const DeviceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(const char* pLayerName) const;
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetSparseImageFormatProperties(Format format, ImageType type, SampleCountFlagBits samples, ImageUsageFlags usage, ImageTiling tiling) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetDisplayPropertiesKHR() const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetDisplayPlanePropertiesKHR() const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(uint32_t planeIndex) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(DisplayKHR display) const;
    [[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(DisplayKHR display, const DisplayModeCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const;
    [[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(DisplayModeKHR mode, uint32_t planeIndex) const;
    [[nodiscard]] expected<Bool32> GetSurfaceSupportKHR(uint32_t queueFamilyIndex, SurfaceKHR surface) const;
    [[nodiscard]] expected<SurfaceCapabilitiesKHR> GetSurfaceCapabilitiesKHR(SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetSurfaceFormatsKHR(SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModesKHR(SurfaceKHR surface) const;
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    [[nodiscard]] wl_display GetWaylandPresentationSupportKHR(uint32_t queueFamilyIndex) const;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] VkBool32 GetWin32PresentationSupportKHR(uint32_t queueFamilyIndex) const;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    [[nodiscard]] VkBool32 GetXlibPresentationSupportKHR(uint32_t queueFamilyIndex, Display&  dpy, VisualID visualID) const;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    [[nodiscard]] VkBool32 GetXcbPresentationSupportKHR(uint32_t queueFamilyIndex, xcb_connection_t&  connection, xcb_visualid_t visual_id) const;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] IDirectFB GetDirectFBPresentationSupportEXT(uint32_t queueFamilyIndex) const;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    [[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetExternalImageFormatPropertiesNV(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags, ExternalMemoryHandleTypeFlagsNV externalHandleType) const;
    [[nodiscard]] PhysicalDeviceFeatures2 GetFeatures2() const;
    [[nodiscard]] PhysicalDeviceProperties2 GetProperties2() const;
    [[nodiscard]] FormatProperties2 GetFormatProperties2(Format format) const;
    [[nodiscard]] expected<ImageFormatProperties2> GetImageFormatProperties2(const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const;
    [[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetQueueFamilyProperties2() const;
    [[nodiscard]] PhysicalDeviceMemoryProperties2 GetMemoryProperties2() const;
    [[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetSparseImageFormatProperties2(const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const;
    [[nodiscard]] ExternalBufferProperties GetExternalBufferProperties(const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const;
    [[nodiscard]] ExternalSemaphoreProperties GetExternalSemaphoreProperties(const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const;
    [[nodiscard]] ExternalFenceProperties GetExternalFenceProperties(const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const;
    [[nodiscard]] Result ReleaseDisplayEXT(DisplayKHR display) const;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] Result AcquireXlibDisplayEXT(Display&  dpy, DisplayKHR display) const;
    [[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(Display&  dpy, RROutput rrOutput) const;
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    [[nodiscard]] expected<SurfaceCapabilities2EXT> GetSurfaceCapabilities2EXT(SurfaceKHR surface) const;
    [[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPresentRectanglesKHR(SurfaceKHR surface) const;
    [[nodiscard]] MultisamplePropertiesEXT GetMultisamplePropertiesEXT(SampleCountFlagBits samples) const;
    [[nodiscard]] expected<SurfaceCapabilities2KHR> GetSurfaceCapabilities2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetSurfaceFormats2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetDisplayProperties2KHR() const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetDisplayPlaneProperties2KHR() const;
    [[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(DisplayKHR display) const;
    [[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetCalibrateableTimeDomainsEXT() const;
    [[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetCooperativeMatrixPropertiesNV() const;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    [[nodiscard]] Result EnumerateQueueFamilyPerformanceQueryCountersKHR(uint32_t queueFamilyIndex, uint32_t&  pCounterCount, PerformanceCounterKHR* pCounters, PerformanceCounterDescriptionKHR* pCounterDescriptions) const;
    [[nodiscard]] uint32_t GetQueueFamilyPerformanceQueryPassesKHR(const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const;
    [[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetSupportedFramebufferMixedSamplesCombinationsNV() const;
    [[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetToolPropertiesEXT() const;
};
struct QueueFunctions {
    DeviceFunctions const* device_functions;
    Queue queue;
    QueueFunctions() noexcept;
    QueueFunctions(DeviceFunctions const& device_functions, Queue const queue) noexcept;
    [[nodiscard]] Result Submit(uint32_t submitCount, const SubmitInfo* pSubmits, Fence fence) const;
    [[nodiscard]] Result Submit(std::span<SubmitInfo> Submits, Fence fence) const;
    [[nodiscard]] Result WaitIdle() const;
    [[nodiscard]] Result BindSparse(uint32_t bindInfoCount, const BindSparseInfo* pBindInfo, Fence fence) const;
    [[nodiscard]] Result BindSparse(std::span<BindSparseInfo> BindInfo, Fence fence) const;
    [[nodiscard]] Result PresentKHR(const PresentInfoKHR&  pPresentInfo) const;
    void BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const;
    void EndDebugUtilsLabelEXT() const;
    void InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const;
    [[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetCheckpointDataNV() const;
    [[nodiscard]] Result SetPerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) const;
};
struct CommandBufferFunctions {
    DeviceFunctions const* device_functions;
    CommandBuffer commandbuffer;
    CommandBufferFunctions() noexcept;
    CommandBufferFunctions(DeviceFunctions const& device_functions, CommandBuffer const commandbuffer) noexcept;
    [[nodiscard]] Result Begin(const CommandBufferBeginInfo&  pBeginInfo) const;
    [[nodiscard]] Result End() const;
    [[nodiscard]] Result Reset(CommandBufferResetFlags flags) const;
    CommandBufferFunctions const& BindPipeline(PipelineBindPoint pipelineBindPoint, Pipeline pipeline) const;
    CommandBufferFunctions const& SetViewport(uint32_t firstViewport, uint32_t viewportCount, const Viewport* pViewports) const;
    CommandBufferFunctions const& SetViewport(uint32_t firstViewport, std::span<Viewport> Viewports) const;
    CommandBufferFunctions const& SetScissor(uint32_t firstScissor, uint32_t scissorCount, const Rect2D* pScissors) const;
    CommandBufferFunctions const& SetScissor(uint32_t firstScissor, std::span<Rect2D> Scissors) const;
    CommandBufferFunctions const& SetLineWidth(float lineWidth) const;
    CommandBufferFunctions const& SetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const;
    CommandBufferFunctions const& SetBlendConstants(const float blendConstants[4]) const;
    CommandBufferFunctions const& SetDepthBounds(float minDepthBounds, float maxDepthBounds) const;
    CommandBufferFunctions const& SetStencilCompareMask(StencilFaceFlags faceMask, uint32_t compareMask) const;
    CommandBufferFunctions const& SetStencilWriteMask(StencilFaceFlags faceMask, uint32_t writeMask) const;
    CommandBufferFunctions const& SetStencilReference(StencilFaceFlags faceMask, uint32_t reference) const;
    CommandBufferFunctions const& BindDescriptorSets(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) const;
    CommandBufferFunctions const& BindDescriptorSets(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, std::span<DescriptorSet> DescriptorSets, std::span<uint32_t> DynamicOffsets) const;
    CommandBufferFunctions const& BindIndexBuffer(Buffer buffer, DeviceSize offset, IndexType indexType) const;
    CommandBufferFunctions const& BindVertexBuffers(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets) const;
    CommandBufferFunctions const& BindVertexBuffers(uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets) const;
    CommandBufferFunctions const& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;
    CommandBufferFunctions const& DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const;
    CommandBufferFunctions const& DrawIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    CommandBufferFunctions const& DrawIndexedIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    CommandBufferFunctions const& Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
    CommandBufferFunctions const& DispatchIndirect(Buffer buffer, DeviceSize offset) const;
    CommandBufferFunctions const& CopyBuffer(Buffer srcBuffer, Buffer dstBuffer, uint32_t regionCount, const BufferCopy* pRegions) const;
    CommandBufferFunctions const& CopyBuffer(Buffer srcBuffer, Buffer dstBuffer, std::span<BufferCopy> Regions) const;
    CommandBufferFunctions const& CopyImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageCopy* pRegions) const;
    CommandBufferFunctions const& CopyImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageCopy> Regions) const;
    CommandBufferFunctions const& BlitImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageBlit* pRegions, Filter filter) const;
    CommandBufferFunctions const& BlitImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageBlit> Regions, Filter filter) const;
    CommandBufferFunctions const& CopyBufferToImage(Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const BufferImageCopy* pRegions) const;
    CommandBufferFunctions const& CopyBufferToImage(Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, std::span<BufferImageCopy> Regions) const;
    CommandBufferFunctions const& CopyImageToBuffer(Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, uint32_t regionCount, const BufferImageCopy* pRegions) const;
    CommandBufferFunctions const& CopyImageToBuffer(Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, std::span<BufferImageCopy> Regions) const;
    CommandBufferFunctions const& UpdateBuffer(Buffer dstBuffer, DeviceSize dstOffset, DeviceSize dataSize, const void* pData) const;
    CommandBufferFunctions const& UpdateBuffer(Buffer dstBuffer, DeviceSize dstOffset, std::span<std::byte> Data) const;
    CommandBufferFunctions const& FillBuffer(Buffer dstBuffer, DeviceSize dstOffset, DeviceSize size, uint32_t data) const;
    CommandBufferFunctions const& ClearColorImage(Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const;
    CommandBufferFunctions const& ClearColorImage(Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, std::span<ImageSubresourceRange> Ranges) const;
    CommandBufferFunctions const& ClearDepthStencilImage(Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, uint32_t rangeCount, const ImageSubresourceRange* pRanges) const;
    CommandBufferFunctions const& ClearDepthStencilImage(Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, std::span<ImageSubresourceRange> Ranges) const;
    CommandBufferFunctions const& ClearAttachments(uint32_t attachmentCount, const ClearAttachment* pAttachments, uint32_t rectCount, const ClearRect* pRects) const;
    CommandBufferFunctions const& ClearAttachments(std::span<ClearAttachment> Attachments, std::span<ClearRect> Rects) const;
    CommandBufferFunctions const& ResolveImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageResolve* pRegions) const;
    CommandBufferFunctions const& ResolveImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, std::span<ImageResolve> Regions) const;
    CommandBufferFunctions const& SetEvent(Event event, PipelineStageFlags stageMask) const;
    CommandBufferFunctions const& ResetEvent(Event event, PipelineStageFlags stageMask) const;
    CommandBufferFunctions const& WaitEvents(uint32_t eventCount, const Event* pEvents, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const;
    CommandBufferFunctions const& WaitEvents(std::span<Event> Events, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, std::span<MemoryBarrier> MemoryBarriers, std::span<BufferMemoryBarrier> BufferMemoryBarriers, std::span<ImageMemoryBarrier> ImageMemoryBarriers) const;
    CommandBufferFunctions const& PipelineBarrier(PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers) const;
    CommandBufferFunctions const& PipelineBarrier(PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, std::span<MemoryBarrier> MemoryBarriers, std::span<BufferMemoryBarrier> BufferMemoryBarriers, std::span<ImageMemoryBarrier> ImageMemoryBarriers) const;
    CommandBufferFunctions const& BeginQuery(QueryPool queryPool, uint32_t query, QueryControlFlags flags) const;
    CommandBufferFunctions const& EndQuery(QueryPool queryPool, uint32_t query) const;
    CommandBufferFunctions const& BeginConditionalRenderingEXT(const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const;
    CommandBufferFunctions const& EndConditionalRenderingEXT() const;
    CommandBufferFunctions const& ResetQueryPool(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const;
    CommandBufferFunctions const& WriteTimestamp(PipelineStageFlagBits pipelineStage, QueryPool queryPool, uint32_t query) const;
    CommandBufferFunctions const& CopyQueryPoolResults(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize stride, QueryResultFlags flags) const;
    CommandBufferFunctions const& PushConstants(PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) const;
    CommandBufferFunctions const& PushConstants(PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, std::span<std::byte> Values) const;
    CommandBufferFunctions const& BeginRenderPass(const RenderPassBeginInfo&  pRenderPassBegin, SubpassContents contents) const;
    CommandBufferFunctions const& NextSubpass(SubpassContents contents) const;
    CommandBufferFunctions const& EndRenderPass() const;
    CommandBufferFunctions const& ExecuteCommands(uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers) const;
    CommandBufferFunctions const& ExecuteCommands(std::span<CommandBuffer> CommandBuffers) const;
    CommandBufferFunctions const& DebugMarkerBeginEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const;
    CommandBufferFunctions const& DebugMarkerEndEXT() const;
    CommandBufferFunctions const& DebugMarkerInsertEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const;
    CommandBufferFunctions const& ExecuteGeneratedCommandsNV(Bool32 isPreprocessed, const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const;
    CommandBufferFunctions const& PreprocessGeneratedCommandsNV(const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const;
    CommandBufferFunctions const& BindPipelineShaderGroupNV(PipelineBindPoint pipelineBindPoint, Pipeline pipeline, uint32_t groupIndex) const;
    CommandBufferFunctions const& PushDescriptorSetKHR(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites) const;
    CommandBufferFunctions const& PushDescriptorSetKHR(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, std::span<WriteDescriptorSet> DescriptorWrites) const;
    CommandBufferFunctions const& SetDeviceMask(uint32_t deviceMask) const;
    CommandBufferFunctions const& DispatchBase(uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const;
    CommandBufferFunctions const& PushDescriptorSetWithTemplateKHR(DescriptorUpdateTemplate descriptorUpdateTemplate, PipelineLayout layout, uint32_t set, const void* pData) const;
    CommandBufferFunctions const& SetViewportWScalingNV(uint32_t firstViewport, uint32_t viewportCount, const ViewportWScalingNV* pViewportWScalings) const;
    CommandBufferFunctions const& SetViewportWScalingNV(uint32_t firstViewport, std::span<ViewportWScalingNV> ViewportWScalings) const;
    CommandBufferFunctions const& SetDiscardRectangleEXT(uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const Rect2D* pDiscardRectangles) const;
    CommandBufferFunctions const& SetDiscardRectangleEXT(uint32_t firstDiscardRectangle, std::span<Rect2D> DiscardRectangles) const;
    CommandBufferFunctions const& SetSampleLocationsEXT(const SampleLocationsInfoEXT&  pSampleLocationsInfo) const;
    CommandBufferFunctions const& BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const;
    CommandBufferFunctions const& EndDebugUtilsLabelEXT() const;
    CommandBufferFunctions const& InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const;
    CommandBufferFunctions const& WriteBufferMarkerAMD(PipelineStageFlagBits pipelineStage, Buffer dstBuffer, DeviceSize dstOffset, uint32_t marker) const;
    CommandBufferFunctions const& BeginRenderPass2(const RenderPassBeginInfo&  pRenderPassBegin, const SubpassBeginInfo&  pSubpassBeginInfo) const;
    CommandBufferFunctions const& NextSubpass2(const SubpassBeginInfo&  pSubpassBeginInfo, const SubpassEndInfo&  pSubpassEndInfo) const;
    CommandBufferFunctions const& EndRenderPass2(const SubpassEndInfo&  pSubpassEndInfo) const;
    CommandBufferFunctions const& DrawIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    CommandBufferFunctions const& DrawIndexedIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    CommandBufferFunctions const& SetCheckpointNV(const void* pCheckpointMarker) const;
    CommandBufferFunctions const& BindTransformFeedbackBuffersEXT(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes) const;
    CommandBufferFunctions const& BindTransformFeedbackBuffersEXT(uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets, std::span<DeviceSize> Sizes) const;
    CommandBufferFunctions const& BeginTransformFeedbackEXT(uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const;
    CommandBufferFunctions const& BeginTransformFeedbackEXT(uint32_t firstCounterBuffer, std::span<Buffer> CounterBuffers, std::span<DeviceSize> CounterBufferOffsets) const;
    CommandBufferFunctions const& EndTransformFeedbackEXT(uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets) const;
    CommandBufferFunctions const& EndTransformFeedbackEXT(uint32_t firstCounterBuffer, std::span<Buffer> CounterBuffers, std::span<DeviceSize> CounterBufferOffsets) const;
    CommandBufferFunctions const& BeginQueryIndexedEXT(QueryPool queryPool, uint32_t query, QueryControlFlags flags, uint32_t index) const;
    CommandBufferFunctions const& EndQueryIndexedEXT(QueryPool queryPool, uint32_t query, uint32_t index) const;
    CommandBufferFunctions const& DrawIndirectByteCountEXT(uint32_t instanceCount, uint32_t firstInstance, Buffer counterBuffer, DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const;
    CommandBufferFunctions const& SetExclusiveScissorNV(uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const Rect2D* pExclusiveScissors) const;
    CommandBufferFunctions const& SetExclusiveScissorNV(uint32_t firstExclusiveScissor, std::span<Rect2D> ExclusiveScissors) const;
    CommandBufferFunctions const& BindShadingRateImageNV(ImageView imageView, ImageLayout imageLayout) const;
    CommandBufferFunctions const& SetViewportShadingRatePaletteNV(uint32_t firstViewport, uint32_t viewportCount, const ShadingRatePaletteNV* pShadingRatePalettes) const;
    CommandBufferFunctions const& SetViewportShadingRatePaletteNV(uint32_t firstViewport, std::span<ShadingRatePaletteNV> ShadingRatePalettes) const;
    CommandBufferFunctions const& SetCoarseSampleOrderNV(CoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const CoarseSampleOrderCustomNV* pCustomSampleOrders) const;
    CommandBufferFunctions const& SetCoarseSampleOrderNV(CoarseSampleOrderTypeNV sampleOrderType, std::span<CoarseSampleOrderCustomNV> CustomSampleOrders) const;
    CommandBufferFunctions const& DrawMeshTasksNV(uint32_t taskCount, uint32_t firstTask) const;
    CommandBufferFunctions const& DrawMeshTasksIndirectNV(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
    CommandBufferFunctions const& DrawMeshTasksIndirectCountNV(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const;
    CommandBufferFunctions const& CopyAccelerationStructureNV(AccelerationStructureKHR dst, AccelerationStructureKHR src, CopyAccelerationStructureModeKHR mode) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) const;
    CommandBufferFunctions const& CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const;
    CommandBufferFunctions const& CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const;
    CommandBufferFunctions const& WriteAccelerationStructuresPropertiesKHR(uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const;
    CommandBufferFunctions const& WriteAccelerationStructuresPropertiesKHR(std::span<AccelerationStructureKHR> AccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& BuildAccelerationStructureNV(const AccelerationStructureInfoNV&  pInfo, Buffer instanceData, DeviceSize instanceOffset, Bool32 update, AccelerationStructureKHR dst, AccelerationStructureKHR src, Buffer scratch, DeviceSize scratchOffset) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) const;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysNV(Buffer raygenShaderBindingTableBuffer, DeviceSize raygenShaderBindingOffset, Buffer missShaderBindingTableBuffer, DeviceSize missShaderBindingOffset, DeviceSize missShaderBindingStride, Buffer hitShaderBindingTableBuffer, DeviceSize hitShaderBindingOffset, DeviceSize hitShaderBindingStride, Buffer callableShaderBindingTableBuffer, DeviceSize callableShaderBindingOffset, DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& TraceRaysIndirectKHR(const StridedBufferRegionKHR&  pRaygenShaderBindingTable, const StridedBufferRegionKHR&  pMissShaderBindingTable, const StridedBufferRegionKHR&  pHitShaderBindingTable, const StridedBufferRegionKHR&  pCallableShaderBindingTable, Buffer buffer, DeviceSize offset) const;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    [[nodiscard]] Result SetPerformanceMarkerINTEL(const PerformanceMarkerInfoINTEL&  pMarkerInfo) const;
    [[nodiscard]] Result SetPerformanceStreamMarkerINTEL(const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const;
    [[nodiscard]] Result SetPerformanceOverrideINTEL(const PerformanceOverrideInfoINTEL&  pOverrideInfo) const;
    CommandBufferFunctions const& SetLineStippleEXT(uint32_t lineStippleFactor, uint16_t lineStipplePattern) const;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& BuildAccelerationStructureKHR(uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) const;
    CommandBufferFunctions const& BuildAccelerationStructureKHR(std::span<AccelerationStructureBuildGeometryInfoKHR> Infos, std::span<AccelerationStructureBuildOffsetInfoKHR> pOffsetInfos) const;
    CommandBufferFunctions const& BuildAccelerationStructureIndirectKHR(const AccelerationStructureBuildGeometryInfoKHR&  pInfo, Buffer indirectBuffer, DeviceSize indirectOffset, uint32_t indirectStride) const;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    CommandBufferFunctions const& SetCullModeEXT(CullModeFlags cullMode) const;
    CommandBufferFunctions const& SetFrontFaceEXT(FrontFace frontFace) const;
    CommandBufferFunctions const& SetPrimitiveTopologyEXT(PrimitiveTopology primitiveTopology) const;
    CommandBufferFunctions const& SetViewportWithCountEXT(uint32_t viewportCount, const Viewport* pViewports) const;
    CommandBufferFunctions const& SetViewportWithCountEXT(std::span<Viewport> Viewports) const;
    CommandBufferFunctions const& SetScissorWithCountEXT(uint32_t scissorCount, const Rect2D* pScissors) const;
    CommandBufferFunctions const& SetScissorWithCountEXT(std::span<Rect2D> Scissors) const;
    CommandBufferFunctions const& BindVertexBuffers2EXT(uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes, const DeviceSize* pStrides) const;
    CommandBufferFunctions const& BindVertexBuffers2EXT(uint32_t firstBinding, std::span<Buffer> Buffers, std::span<DeviceSize> Offsets, std::span<DeviceSize> Sizes, std::span<DeviceSize> Strides) const;
    CommandBufferFunctions const& SetDepthTestEnableEXT(Bool32 depthTestEnable) const;
    CommandBufferFunctions const& SetDepthWriteEnableEXT(Bool32 depthWriteEnable) const;
    CommandBufferFunctions const& SetDepthCompareOpEXT(CompareOp depthCompareOp) const;
    CommandBufferFunctions const& SetDepthBoundsTestEnableEXT(Bool32 depthBoundsTestEnable) const;
    CommandBufferFunctions const& SetStencilTestEnableEXT(Bool32 stencilTestEnable) const;
    CommandBufferFunctions const& SetStencilOpEXT(StencilFaceFlags faceMask, StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp) const;
    CommandBufferFunctions const& CopyBuffer2KHR(const CopyBufferInfo2KHR&  pCopyBufferInfo) const;
    CommandBufferFunctions const& CopyImage2KHR(const CopyImageInfo2KHR&  pCopyImageInfo) const;
    CommandBufferFunctions const& BlitImage2KHR(const BlitImageInfo2KHR&  pBlitImageInfo) const;
    CommandBufferFunctions const& CopyBufferToImage2KHR(const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const;
    CommandBufferFunctions const& CopyImageToBuffer2KHR(const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const;
    CommandBufferFunctions const& ResolveImage2KHR(const ResolveImageInfo2KHR&  pResolveImageInfo) const;
};
} // namespace vk
// clang-format on
