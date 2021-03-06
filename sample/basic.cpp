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

#include <iostream>
#include <vector>
#include <array>
#include "vk_module.h"

int main()
{
    vk::DynamicLibrary library;
    vk::Result res = library.init();
    if (res != vk::Result::Success) {
        std::cout << "couldn't init vulkan library\n";
        return -1;
    }
    vk::GlobalFunctions free_funcs(library);

    auto layer_props_ret = free_funcs.EnumerateInstanceLayerProperties();
    if (!layer_props_ret) {
        std::cout << "couldn't get layer props: " << vk::to_string(layer_props_ret.raw_result()) << "\n";
        return -1;
    }
    std::cout << "count " << layer_props_ret.value().size() << "\n";
    for (auto& prop : layer_props_ret.value())
        std::cout << prop.layerName << "\n";

    vk::Instance inst = free_funcs.CreateInstance({}).value();
    if (res != vk::Result::Success) {
        std::cout << "failed to create instance\n";
        return static_cast<int>(res);
    }

    if (inst && !(!inst))
        std::cout << "should print this\n";
    else
        std::cout << "shouldn't print this\n";

    vk::InstanceFunctions inst_funcs(free_funcs, inst);
    auto phys_devices_ret = inst_funcs.EnumeratePhysicalDevices();
    if (!phys_devices_ret)
        return -1;
    if (phys_devices_ret.value().size() == 0) {
        std::cout << "failed to get phys devices\n";
        return -100;
    }

    vk::PhysicalDevice phys_dev = phys_devices_ret.value()[0];
    vk::PhysicalDeviceFunctions phys_dev_funcs(inst_funcs, phys_dev);

    vk::ImageCreateFlags img_flags = vk::ImageCreateFlagBits::SparseBinding;
    auto img_props_res = phys_dev_funcs.GetImageFormatProperties(
      vk::Format::Undefined, vk::ImageType::e1D, vk::ImageTiling::Optimal, vk::ImageUsageFlagBits::TransferDst, img_flags);
    if (!img_props_res)
        return -1;
    vk::SwapchainCreateInfoKHR swap_info;
    swap_info.preTransform = vk::SurfaceTransformFlagBitsKHR::IdentityBitKHR;
    /*
     Should not compile.
     vk::SurfaceTransformFlagsKHR transform_flags;
     swap_info.preTransform = transform_flags;
    */

    float priority;
    vk::DeviceQueueCreateInfo queue_info;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &priority;
    vk::DeviceCreateInfo dev_create_info;
    dev_create_info.queueCreateInfoCount = 1;
    dev_create_info.pQueueCreateInfos = &queue_info;
    auto dev_res = inst_funcs.CreateDevice(phys_dev, dev_create_info);
    if (!dev_res)
        return -1;
    vk::Device device = dev_res.value();
    vk::DeviceFunctions device_functions(inst_funcs, device);

    uint32_t queue_indices = 0;
    vk::BufferCreateInfo buffer_info{ .size = 100,
                                      .usage = vk::BufferUsageFlagBits::IndexBuffer,
                                      .sharingMode = vk::SharingMode::Exclusive,
                                      .queueFamilyIndexCount = 1,
                                      .pQueueFamilyIndices = &queue_indices };
    auto buf_res = device_functions.CreateBuffer(buffer_info, nullptr);
    if (!buf_res)
        return -1;
    vk::Buffer buffer = buf_res.value();
    device_functions.DestroyBuffer(buffer);
    vk::CommandPoolCreateInfo pool_info{ .flags = vk::CommandPoolCreateFlagBits::ResetCommandBuffer };
    auto cmd_pool = device_functions.CreateCommandPool(pool_info).value();
    vk::CommandBufferAllocateInfo alloc_info{
        .commandPool = cmd_pool,
        .level = vk::CommandBufferLevel::Primary,
        .commandBufferCount = 1,
    };

    auto [cmds, alloc_ret] = device_functions.AllocateCommandBuffers(alloc_info);
    if (alloc_ret != vk::Result::Success) {
        return -1;
    }
    vk::CommandBuffer cmd_buf = cmds[0];
    vk::CommandBufferFunctions cmd_buf_functions{ device_functions, cmd_buf };
    auto begin_ret = cmd_buf_functions.Begin({});
    if (begin_ret != vk::Result::Success)
        return -1;

    vk::RenderPass renderpass;
    vk::Framebuffer framebuffer;
    vk::ClearValue clear_color{ .color = { { 0, 0, 0, 1 } } };
    vk::Rect2D scissor{ { 0, 0 }, { 100, 100 } };
    vk::Viewport viewport{ 0.f, 0.f, 1.f, 1.f, 0.f, 1.f };

    auto ret = cmd_buf_functions
                 .BeginRenderPass({ .renderPass = renderpass,
                                    .framebuffer = framebuffer,
                                    .renderArea = scissor,
                                    .clearValueCount = 1,
                                    .pClearValues = &clear_color },
                                  vk::SubpassContents::Inline)
                 .SetViewport(0, { viewport, viewport })
                 .SetScissor(0, { scissor })
                 .BindVertexBuffers(0, { buffer }, 0)
                 .BindIndexBuffer(buffer, 0, vk::IndexType::Uint16)
                 .Draw(10, 1, 0, 0)
                 .EndRenderPass()
                 .End();
    if (ret == vk::Result::Success) {
        std::cout << "success recording command buffer\n";
    } else {
        std::cout << "error: " << vk::to_string(ret) << '\n';
        return -1;
    }

    auto [fence, fence_ret] = device_functions.CreateFence({});
    if (fence_ret == vk::Result::Success) {
        std::cout << "success recording command buffer\n";
    }
    return 0;
}