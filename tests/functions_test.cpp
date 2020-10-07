
#include <catch2/catch.hpp>
#include "vkm_function.h"

TEST_CASE("Global Function Usage", "[vk-module.functions]")
{
    vk::DynamicLibrary library;
    vk::Result res = library.init();
    REQUIRE(library.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(library);
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
    auto inst_ret = free_funcs.CreateInstance(info);
    REQUIRE(inst_ret.raw_result() == vk::Result::Success);
}

TEST_CASE("Manual .init()", "[vk-module.functions]")
{
    vk::DynamicLibrary library;
    vk::Result res = library.init();
    REQUIRE(library.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(library);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Constructor init", "[vk-module.functions]")
{
    vk::DynamicLibrary library(vk::DynamicLibrary::LoadAtConstruction{});
    REQUIRE(library.is_init());
    vk::GlobalFunctions free_funcs(library);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Pass vkGetInstanceProcAddr to constructor", "[vk-module.functions]")
{
    vk::DynamicLibrary library(vkGetInstanceProcAddr);
    REQUIRE(library.is_init());
    vk::GlobalFunctions free_funcs(library);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}
TEST_CASE("Pass vkGetInstanceProcAddr to init", "[vk-module.functions]")
{
    vk::DynamicLibrary library;
    vk::Result res = library.init(vkGetInstanceProcAddr);
    REQUIRE(library.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(library);
    REQUIRE(free_funcs.pfn_CreateInstance != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceExtensionProperties != nullptr);
    REQUIRE(free_funcs.pfn_EnumerateInstanceLayerProperties != nullptr);
#if defined(VK_VERSION_1_1)
    REQUIRE(free_funcs.pfn_EnumerateInstanceVersion != nullptr);
#endif
}

TEST_CASE("Create instance functions", "[vk-module.functions]")
{
    vk::DynamicLibrary library(vkGetInstanceProcAddr);
    vk::GlobalFunctions free_funcs(library);

    vk::InstanceCreateInfo info;
    auto ret = free_funcs.CreateInstance(info);
    if (!ret) return;
    REQUIRE(ret.raw_result() == vk::Result::Success);
    vk::Instance inst = ret.value();

    vk::InstanceFunctions inst_funcs(free_funcs, inst);
    REQUIRE(inst_funcs.pfn_EnumeratePhysicalDevices != nullptr);
    uint32_t count = 0;
    vk::Result result = inst_funcs.EnumeratePhysicalDevices(count, nullptr);
    std::vector<vk::PhysicalDevice> phys_devices(count);
    result = inst_funcs.EnumeratePhysicalDevices(count, phys_devices.data());
    REQUIRE(result == vk::Result::Success);
}