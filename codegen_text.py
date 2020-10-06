static_vector = '''
#include <stdint.h>
#include <new>

namespace vk::detail {
template<typename T>
struct fixed_vector
{
    explicit fixed_vector() noexcept {}
    explicit fixed_vector(uint32_t count) noexcept
    {
        _count = count;
        _data = new (std::nothrow) T[count];
        for (uint32_t i = 0; i < count; i++)
            _data[i] = T(); // some vulkan structs have default values, so must be initialized
    }
    ~fixed_vector() noexcept { delete _data; }
    fixed_vector(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (uint32_t i = 0; i < value.count; i++)
            _data[i] = value[i];
    }
    fixed_vector& operator=(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (uint32_t i = 0; i < value.count; i++)
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

    [[nodiscard]] uint32_t size() noexcept { return _count; }
    [[nodiscard]] uint32_t size() const noexcept { return _count; }
    [[nodiscard]] bool empty() noexcept { return _count == 0; }
    [[nodiscard]] bool empty() const noexcept { return _count == 0; }
    [[nodiscard]] const T* data() noexcept { return _data; }
    [[nodiscard]] T* data() const noexcept { return _data; }

    [[nodiscard]] T& operator[](uint32_t count) & noexcept { return _data[count]; }
    [[nodiscard]] T const& operator[](uint32_t count) const& noexcept { return _data[count]; }

    [[nodiscard]] const T* begin() const noexcept { return _data + 0; }
    [[nodiscard]] T* begin() noexcept { return _data + 0; }
    [[nodiscard]] const T* end() const noexcept { return _data + _count; }
    [[nodiscard]] T* end() noexcept { return _data + _count; }

  private:
    uint32_t _count = 0; // vulkan uses uint32_t everywhere, makes this inline with the API
    T* _data = nullptr;
};
} // namespace vk::detail

'''

bitmask_flags_macro = '''
#define DECLARE_ENUM_FLAG_OPERATORS(FLAG_TYPE, FLAG_BITS, BASE_NAME)                \\
                                                                                    \\
struct FLAG_TYPE {                                                                  \\
    using base_type = typename std::underlying_type_t<FLAG_BITS>;                   \\
    base_type flags = static_cast<base_type>(0);                                    \\
                                                                                    \\
    constexpr explicit FLAG_TYPE() noexcept = default;                              \\
    constexpr explicit FLAG_TYPE(base_type in) noexcept: flags(in){ }               \\
    constexpr FLAG_TYPE(FLAG_BITS in) noexcept: flags(static_cast<base_type>(in)){ }\\
    constexpr bool operator==(FLAG_TYPE const& right) const { return flags == right.flags;}\\
    constexpr bool operator!=(FLAG_TYPE const& right) const { return flags != right.flags;}\\
    constexpr explicit operator bool() const noexcept {                             \\
      return flags != 0;                                                            \\
    }                                                                               \\
    constexpr explicit operator BASE_NAME() const noexcept {                        \\
        return static_cast<BASE_NAME>(flags);                                       \\
    }                                                                               \\
};                                                                                  \\
constexpr FLAG_TYPE operator|(FLAG_TYPE a, FLAG_TYPE b) noexcept {                  \\
    return static_cast<FLAG_TYPE>(a.flags | b.flags);                               \\
}                                                                                   \\
constexpr FLAG_TYPE operator&(FLAG_TYPE a, FLAG_TYPE b) noexcept {                  \\
    return static_cast<FLAG_TYPE>(a.flags & b.flags);                               \\
}                                                                                   \\
constexpr FLAG_TYPE operator^(FLAG_TYPE a, FLAG_TYPE b) noexcept {                  \\
    return static_cast<FLAG_TYPE>(a.flags ^ b.flags);                               \\
}                                                                                   \\
constexpr FLAG_TYPE operator~(FLAG_TYPE a) noexcept {                               \\
    return static_cast<FLAG_TYPE>(~a.flags);                                        \\
}                                                                                   \\
constexpr FLAG_TYPE& operator|=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {               \\
    a.flags = (a.flags | b.flags);                                                  \\
    return a;                                                                       \\
}                                                                                   \\
constexpr FLAG_TYPE& operator&=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {               \\
    a.flags = (a.flags & b.flags);                                                  \\
    return a;                                                                       \\
}                                                                                   \\
constexpr FLAG_TYPE operator^=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                \\
    a.flags = (a.flags ^ b.flags);                                                  \\
    return a;                                                                       \\
}                                                                                   \\
constexpr FLAG_TYPE operator|(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = FLAG_TYPE::base_type;                                                 \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) | static_cast<T>(b));           \\
}                                                                                   \\
constexpr FLAG_TYPE operator&(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = FLAG_TYPE::base_type;                                                 \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) & static_cast<T>(b));           \\
}                                                                                   \\
constexpr FLAG_TYPE operator~(FLAG_BITS key) noexcept {                             \\
    using T = FLAG_TYPE::base_type;                                                 \\
    return static_cast<FLAG_TYPE>(~static_cast<T>(key));                            \\
}                                                                                   \\
constexpr FLAG_TYPE operator^(FLAG_BITS a, FLAG_BITS b) noexcept {                  \\
    using T = FLAG_TYPE::base_type;                                                 \\
    return static_cast<FLAG_TYPE>(static_cast<T>(a) ^ static_cast<T>(b));           \\
}                                                                                   \\
'''

vulkan_loader_text = '''
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
    // Used to enable RAII vk::Loader behavior
    struct LoadAtConstruction {};

    explicit Loader() noexcept {}
    explicit Loader(LoadAtConstruction load) noexcept {
        init();
    }
    explicit Loader(PFN_vkGetInstanceProcAddr get_instance_proc_addr) noexcept : 
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
        return *this;
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
'''
