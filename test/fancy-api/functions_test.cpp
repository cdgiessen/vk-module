/*
 * Copyright 2021 Charles Giessen (cdgiessen@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <catch2/catch.hpp>
#include "vk_module.h"

TEST_CASE("Global Function Usage", "[vk-module.functions]")
{
    vk::DynamicLibrary library;
    vk::Result res = library.init();
    REQUIRE(library.is_init());
    REQUIRE(res == vk::Result::Success);
    vk::GlobalFunctions free_funcs(library);
    auto layers_ret = free_funcs.EnumerateInstanceLayerProperties();
    REQUIRE(layers_ret.raw_result() == vk::Result::Success);

    auto exts_ret = free_funcs.EnumerateInstanceExtensionProperties(nullptr);
    REQUIRE(exts_ret.raw_result() == vk::Result::Success);
    uint32_t version = free_funcs.EnumerateInstanceVersion().value();

    vk::ApplicationInfo app_info;
    app_info.apiVersion = version;
    vk::InstanceCreateInfo info;
    info.pApplicationInfo = &app_info;
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
#include <vulkan/vulkan.h>

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
    vk::DynamicLibrary library{ vkGetInstanceProcAddr };
    vk::GlobalFunctions free_funcs(library);

    vk::InstanceCreateInfo info;
    auto ret = free_funcs.CreateInstance(info);
    if (!ret)
        return;
    REQUIRE(ret.raw_result() == vk::Result::Success);
    vk::Instance inst = ret.value();

    vk::InstanceFunctions inst_funcs(free_funcs, inst);
    REQUIRE(inst_funcs.pfn_EnumeratePhysicalDevices != nullptr);
    auto devices_ret = inst_funcs.EnumeratePhysicalDevices();
    REQUIRE(devices_ret.raw_result() == vk::Result::Success);
}