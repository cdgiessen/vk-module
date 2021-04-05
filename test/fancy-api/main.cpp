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

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vk_module.h"
TEST_CASE("test static vector", "[vk-module.fixed_vector]")
{
    vk::detail::fixed_vector<vk::ExtensionProperties> a;
    REQUIRE(a.size() == 0);

    uint32_t size = 10;
    vk::detail::fixed_vector<vk::ExtensionProperties> b(size);
    REQUIRE(b.size() == size);
    vk::ExtensionProperties ext;
    auto hi_str = "hi";
    for (int i = 0; i < vk::MAX_EXTENSION_NAME_SIZE; i++) {
        ext.extensionName[i] = hi_str[i];
        if (ext.extensionName[i] == '\0' || hi_str[i] == '\0')
            break;
    }
    b[0] = ext;
    REQUIRE(strncmp(hi_str, b[0].extensionName, vk::MAX_EXTENSION_NAME_SIZE) == 0);

    vk::detail::fixed_vector<uint32_t> c(4);
    c[0] = 0U;
    c[1] = 1U;
    c[2] = 2U;
    c[3] = 3U;
    for (uint32_t i = 0; i < c.size(); i++) {
        REQUIRE(c[i] == i);
    }
    uint32_t counter = 0;
    for (auto& x : c) {
        counter += x;
    }
    REQUIRE(counter == 6);
}

TEST_CASE("Union operations", "[vk-module.union]")
{
    vk::ClearColorValue x, y;
    x.float32[0] = 1.f;
    y.uint32[0] = 1;
    REQUIRE((x == y) == false);
    REQUIRE((x != y) == true);
}
TEST_CASE("Struct operations", "[vk-module.struct]")
{
    vk::Extent2D extent = { 100, 200 };
    REQUIRE(extent.width == 100);
    REQUIRE(extent.height == 200);
}