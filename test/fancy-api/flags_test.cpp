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

TEST_CASE("Flags bitwise operation", "[vk-module.flags]")
{

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
    flags |= vk::BufferCreateFlags(3U);
    REQUIRE(flags.flags == 3);
    flags = vk::BufferCreateFlagBits::SparseBinding & flags;
    REQUIRE(flags.flags == 1);
    flags &= vk::BufferCreateFlags(1U);
    REQUIRE(flags.flags == 1);
    flags = ~flags;
    REQUIRE(flags.flags == 0xfffffffe);
    flags = vk::BufferCreateFlagBits::SparseResidency;
    flags = vk::BufferCreateFlagBits::SparseBinding ^ flags;
    REQUIRE(flags.flags == 3);
    flags = flags ^ vk::BufferCreateFlagBits::SparseBinding;
    REQUIRE(flags.flags == 2);
    flags ^= vk::BufferCreateFlags(2U);
    REQUIRE(flags.flags == 0);

    // VkImageUsageFlagBits c_flag_bits = c_enum(vk::ImageUsageFlagBits::TransferDst);
    // REQUIRE(c_flag_bits == 2);
}