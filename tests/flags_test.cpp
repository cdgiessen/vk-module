
#include <catch2/catch.hpp>
#include "vkpp_core.h"

TEST_CASE("Flags bitwise operation", "[vk-module.flags]") {

    REQUIRE((vk::BufferCreateFlagBits::SparseBinding | vk::BufferCreateFlagBits::SparseResidency).flags == 3);
    REQUIRE((vk::BufferCreateFlagBits::SparseBinding & vk::BufferCreateFlagBits::SparseBinding).flags == 1U);
    REQUIRE((vk::BufferCreateFlagBits::SparseBinding ^ vk::BufferCreateFlagBits::SparseResidency).flags == 3);
    REQUIRE((~(vk::BufferCreateFlagBits::SparseResidency)).flags == 0xfffffffd);

    vk::BufferCreateFlags flags;
    flags = ~vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 0xfffffffe);
    flags = vk::BufferCreateFlagBits::SparseResidency;
    REQUIRE(flags.flags == 2);
    flags |= vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 3);
    flags &= vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 1);
    flags ^= vk::BufferCreateFlagBits::SparseAliased;
    REQUIRE(flags.flags == 5);

    flags = flags | vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 5);
    flags = flags & vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 1);
    flags = vk::BufferCreateFlagBits::SparseResidency | flags;
    REQUIRE(flags.flags == 3);
    flags |= flags;
    REQUIRE(flags.flags == 3);
    flags = vk::BufferCreateFlagBits::SparseBinding & flags;
    REQUIRE(flags.flags == 1);
    flags &= flags;
    REQUIRE(flags.flags == 1);
    flags = ~flags;
    REQUIRE(flags.flags == 0xfffffffe);
    flags = vk::BufferCreateFlagBits::SparseResidency;
    flags = vk::BufferCreateFlagBits::SparseBinding ^ flags;
    REQUIRE(flags.flags == 3);
    flags = flags ^ vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 2);
    flags ^= flags;
    REQUIRE(flags.flags == 0);
}