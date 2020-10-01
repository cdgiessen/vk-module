
#include <catch2/catch.hpp>
#include "vkpp_functions.h"

TEST_CASE("Global Function Usage", "[vk-module.functions]") {
    vk::Loader loader;
    vk::Result res = loader.init();
    REQUIRE(loader.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(loader);
    uint32_t count = 0;
    res = free_funcs.EnumerateInstanceLayerProperties(count, nullptr);
    REQUIRE(res == vk::Result::Success);
    std::vector<vk::LayerProperties> layer_props(count);
    res = free_funcs.EnumerateInstanceLayerProperties(count, layer_props.data());
    REQUIRE(res == vk::Result::Success);
    count = 0;
    res = free_funcs.EnumerateInstanceExtensionProperties(nullptr, count, nullptr);
    REQUIRE(res == vk::Result::Success);
    std::vector<vk::ExtensionProperties> ext_props(count);
    res = free_funcs.EnumerateInstanceExtensionProperties(nullptr, count, ext_props.data());
    REQUIRE(res == vk::Result::Success);
    uint32_t version = 0;
    res = free_funcs.EnumerateInstanceVersion(version);

    vk::InstanceCreateInfo info;
    vk::Instance inst;
    res = free_funcs.CreateInstance(info, nullptr, inst);
    REQUIRE(res == vk::Result::Success);
}

TEST_CASE("Manual .init()", "[vk-module.functions]") {
    vk::Loader loader;
    vk::Result res = loader.init();
    REQUIRE(loader.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(loader);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Constructor init", "[vk-module.functions]") {
    vk::Loader loader(vk::Loader::LoadAtConstruction{});
    REQUIRE(loader.is_init());
    vk::GlobalFunctions free_funcs(loader);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Pass vkGetInstanceProcAddr to constructor", "[vk-module.functions]") {
    vk::Loader loader(vkGetInstanceProcAddr);
    REQUIRE(loader.is_init());
    vk::GlobalFunctions free_funcs(loader);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Pass vkGetInstanceProcAddr to init", "[vk-module.functions]") {
    vk::Loader loader;
    vk::Result res = loader.init(vkGetInstanceProcAddr);
    REQUIRE(loader.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(loader);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}

TEST_CASE("Create instance functions", "[vk-module.functions]") {
    vk::Loader loader(vkGetInstanceProcAddr);
    vk::GlobalFunctions free_funcs(loader);

    vk::InstanceCreateInfo info;
    vk::Instance inst;
    vk::Result res = free_funcs.CreateInstance(info, nullptr, inst);
    REQUIRE(res == vk::Result::Success);

    vk::InstanceFunctions inst_funcs(free_funcs, inst);
    REQUIRE(inst_funcs.pfn_EnumeratePhysicalDevices != nullptr);
    uint32_t count = 0;
    res = inst_funcs.EnumeratePhysicalDevices(count, nullptr);
    std::vector<vk::PhysicalDevice> phys_devices(count);
    res = inst_funcs.EnumeratePhysicalDevices(count, phys_devices.data());
}