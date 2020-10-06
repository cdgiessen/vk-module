#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vkm_core.h"
#include "vkm_vector.h"

TEST_CASE("test static vector", "[vk-module.fixed_vector]")
{
    vk::detail::fixed_vector<vk::ExtensionProperties> a;
    REQUIRE(a.size() == 0);

    uint32_t size = 10;
    vk::detail::fixed_vector<vk::ExtensionProperties> b(size);
    REQUIRE(b.size() == size);
    vk::ExtensionProperties ext;
    auto hi_str = "hi";
    strncpy(ext.extensionName, hi_str, vk::MAX_EXTENSION_NAME_SIZE);
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
    int counter = 0;
    for (auto& x : c) {
        counter += x;
    }
    REQUIRE(counter == 6);
}