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

#include "vk_module.h"
#include "vk_module_interop.h"

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

constexpr uint32_t width = 512;
constexpr uint32_t height = 512;

struct RendererContext
{
    vk::DynamicLibrary library;
    GLFWwindow* window;
    vk::Instance instance;
    vk::SurfaceKHR surface;
    vk::InstanceFunctions functions;
    vk::PhysicalDevice physical_device;
    vk::PhysicalDeviceFunctions physical_device_functions;
};

struct DeviceContext
{
    vk::Device device;
    vk::DeviceFunctions functions;
    vk::PhysicalDeviceFunctions physical_device_functions;
    vk::Queue graphics_queue;
    vk::QueueFunctions queue_functions;
    vk::SurfaceKHR surface;
    vk::SwapchainKHR swapchain;
    std::vector<vk::Image> swapchain_images;
    uint32_t image_count = 0;
    std::vector<vk::ImageView> swapchain_image_views;
    vk::Format swapchain_img_format;
    vk::RenderPass render_pass;
    std::vector<vk::Framebuffer> framebuffers;
    vk::PipelineLayout pipeline_layout;
    vk::Pipeline pipeline;
    vk::CommandPool cmd_pool;
    std::vector<vk::CommandBuffer> cmd_buffers;
    uint32_t current_frame = 0;
    std::vector<vk::Fence> fences;
    std::vector<vk::Semaphore> available_semaphores;
    std::vector<vk::Semaphore> finished_semaphores;
};
void check_res(bool result, const char* msg)
{
    if (!result) {
        std::cerr << msg << "\n";
        assert(false);
    }
}
void check_res(vk::Result result, const char* msg)
{
    if (result != vk::Result::Success) {
        std::cerr << msg << ": Result = " << vk::to_string(result) << "\n";
        assert(false);
    }
}
template<typename T>
void check_res(vk::expected<T> const& expected, const char* msg)
{
    if (!expected) {
        std::cerr << msg << ": Result = " << vk::to_string(expected.error()) << "\n";
        assert(false);
    }
}

GLFWwindow* create_window_glfw(const char* window_name = "", bool resize = true)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    if (!resize)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow(width, height, window_name, NULL, NULL);
}
void destroy_window_glfw(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
vk::SurfaceKHR create_surface_glfw(VkInstance instance, GLFWwindow* window)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult err = glfwCreateWindowSurface(instance, window, NULL, &surface);
    if (err) {
        const char* error_msg;
        int ret = glfwGetError(&error_msg);
        if (ret != 0) {
            std::cerr << ret << " ";
            if (error_msg != nullptr)
                std::cerr << error_msg;
            std::cerr << "\n";
        }
        surface = VK_NULL_HANDLE;
    }
    return vk::SurfaceKHR{ surface };
}

void create_renderer_context(RendererContext& context)
{
    check_res(context.library.init(), "Failed to init vulkan library");

    context.window = create_window_glfw("Sample Triangle", false);
    check_res(context.window != nullptr, "Failed to create glfw window");

    vk::GlobalFunctions global_functions = vk::GlobalFunctions(context.library);

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    vk::InstanceCreateInfo inst_info{};
    inst_info.setEnabledExtensionCount(glfw_extension_count);
    inst_info.setPpEnabledExtensionNames(glfw_extensions);

    auto [layers, layers_ret] = global_functions.EnumerateInstanceLayerProperties();
    check_res(layers_ret, "Couldn't get layers\n");
    const char* layer_names[] = { "VK_LAYER_KHRONOS_validation" };
    for (auto& layer : layers) {
        if (std::string(layer.layerName) == std::string("VK_LAYER_KHRONOS_validation")) {
            // inst_builder.addEnabledLayerNames("VK_LAYER_KHRONOS_validation");
            inst_info.ppEnabledLayerNames = layer_names;
            break;
        }
    }

    auto [instance, instance_ret] = global_functions.CreateInstance(inst_info);

    check_res(instance_ret, "Failed to init Vulkan Instance");

    context.instance = instance;
    context.functions = vk::InstanceFunctions(global_functions, context.instance);

    context.surface = create_surface_glfw(instance.get(), context.window);
    check_res(!!context.surface, "Failed to create glfw surface");

    auto [physical_devices, physical_devices_ret] = context.functions.EnumeratePhysicalDevices();
    check_res(physical_devices_ret, "Failed to  get physical devices");
    check_res(physical_devices.size() > 0, "No capable physical devices found");

    context.physical_device = physical_devices[0]; // get first physical device returned
    context.physical_device_functions = vk::PhysicalDeviceFunctions(context.functions, context.physical_device);

    auto [surface_supported, support_ret] = context.physical_device_functions.GetSurfaceSupportKHR(0, context.surface);
    check_res(support_ret, "Failed to query surface support");
    check_res(surface_supported, "Surface doesn't support present");
}

void create_device_context(RendererContext& render_context, DeviceContext& device_context)
{
    const char* extensions[] = { "VK_KHR_swapchain" };
    auto device_ret = render_context.functions.CreateDevice(
      render_context.physical_device,
      vk::DeviceCreateInfo{}
        .setEnabledExtensionCount(1)
        .setPpEnabledExtensionNames(extensions)
        .setPQueueCreateInfos({ vk::DeviceQueueCreateInfo{}.setQueueFamilyIndex(0).setPQueuePriorities({ 1.f }) }));
    check_res(device_ret, "Failed to create a vulkan device");

    device_context.device = device_ret.value();
    device_context.functions = vk::DeviceFunctions(render_context.functions, device_context.device);
    device_context.surface = render_context.surface;
    device_context.physical_device_functions = render_context.physical_device_functions;
}

void setup_queues(DeviceContext& device, vk::PhysicalDeviceFunctions const& phys_dev_funcs)
{
    auto queue_family_props = phys_dev_funcs.GetQueueFamilyProperties();
    uint32_t graphics_queue_family = 0;
    for (uint32_t i = 0; i < queue_family_props.size(); i++) {
        if (queue_family_props[0].queueFlags & vk::QueueFlagBits::Graphics && queue_family_props[0].queueCount > 0) {
            graphics_queue_family = i;
            break;
        }
    }

    check_res(graphics_queue_family == 0, "First queue isn't the graphics queue, implicit assumptions failed");

    device.graphics_queue = device.functions.GetDeviceQueue(graphics_queue_family, 0);
    device.queue_functions = vk::QueueFunctions(device.functions, device.graphics_queue);
}

void setup_swapchain(DeviceContext& device)
{
    auto [surf_formats, surf_formats_ret] = device.physical_device_functions.GetSurfaceFormatsKHR(device.surface);
    check_res(surf_formats_ret, "Failed to get surface formats");
    check_res(surf_formats.size() > 0, "No surface formats available");

    device.swapchain_img_format = surf_formats[0].format;

    device.image_count = 3;
    auto [swapchain, swap_ret] = device.functions.CreateSwapchainKHR(vk::SwapchainCreateInfoKHR{
      .surface = device.surface,
      .minImageCount = 3,
      .imageFormat = device.swapchain_img_format,
      .imageColorSpace = surf_formats[0].colorSpace,
      .imageExtent = { width, height },
      .imageArrayLayers = 1,
      .imageUsage = vk::ImageUsageFlagBits::ColorAttachment,
      .imageSharingMode = vk::SharingMode::Exclusive,
      .pQueueFamilyIndices = nullptr,
      .preTransform = vk::SurfaceTransformFlagBitsKHR::IdentityBitKHR,
      .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::OpaqueBitKHR,
      .presentMode = vk::PresentModeKHR::FifoKHR,
    });
    check_res(swap_ret, "Unable to create Swapchain");

    device.swapchain = swapchain;

    auto swap_images_ret = device.functions.GetSwapchainImagesKHR(device.swapchain);
    check_res(swap_images_ret, "Failed to get swapchain Images");

    for (auto& image : swap_images_ret.value()) {
        device.swapchain_images.push_back(image);
        auto [view, ret] = device.functions.CreateImageView(vk::ImageViewCreateInfo{
          .image = image,
          .viewType = vk::ImageViewType::e2D,
          .format = device.swapchain_img_format,
          .subresourceRange = { .aspectMask = vk::ImageAspectFlagBits::Color, .levelCount = 1, .layerCount = 1 } });
        check_res(ret, "Failed to create swapchain image view");

        device.swapchain_image_views.push_back(view);
    }
}

void setup_renderpass(DeviceContext& device)
{
    auto rp_ret = device.functions.CreateRenderPass(
      vk::RenderPassCreateInfo{}
        .setPAttachments({ vk::AttachmentDescription{}
                             .setFormat(device.swapchain_img_format)
                             .setSamples(vk::SampleCountFlagBits::e1)
                             .setLoadOp(vk::AttachmentLoadOp::Clear)
                             .setStoreOp(vk::AttachmentStoreOp::Store)
                             .setStencilLoadOp(vk::AttachmentLoadOp::DontCare)
                             .setStencilStoreOp(vk::AttachmentStoreOp::DontCare)
                             .setInitialLayout(vk::ImageLayout::Undefined)
                             .setFinalLayout(vk::ImageLayout::PresentSrcKHR) })

        .setPSubpasses({ vk::SubpassDescription{}
                           .setPipelineBindPoint(vk::PipelineBindPoint::Graphics)
                           .setPColorAttachments(
                             { vk::AttachmentReference{}.setAttachment(0).setLayout(vk::ImageLayout::ColorAttachmentOptimal) }) })

        .setPDependencies(
          { vk::SubpassDependency{}
              .setSrcSubpass(vk::SUBPASS_EXTERNAL)
              .setDstSubpass(0)
              .setSrcStageMask(vk::PipelineStageFlagBits::ColorAttachmentOutput)
              .setDstStageMask(vk::PipelineStageFlagBits::ColorAttachmentOutput)
              .setDstAccessMask(vk::AccessFlagBits::ColorAttachmentRead | vk::AccessFlagBits::ColorAttachmentWrite) }));

    check_res(rp_ret, "Failed to create renderpass");
    device.render_pass = rp_ret.value();
}
void create_framebuffers(DeviceContext& device)
{
    for (auto& view : device.swapchain_image_views) {
        auto ret = device.functions.CreateFramebuffer(vk::FramebufferCreateInfo{}
                                                        .setRenderPass(device.render_pass)
                                                        .setPAttachments({ view })
                                                        .setWidth(width)
                                                        .setHeight(height)
                                                        .setLayers(1));
        check_res(ret, "Failed to create framebuffer");
        device.framebuffers.push_back(ret.value());
    }
}

std::vector<char> read_file(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    check_res(file.is_open(), "Failed to open shader file");

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);
    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(file_size));
    file.close();
    return buffer;
}

vk::ShaderModule create_shader_module(DeviceContext& device, std::string const& filename)
{
    auto code = read_file(filename);
    auto [module, ret] =
      device.functions.CreateShaderModule({ .codeSize = code.size(), .pCode = reinterpret_cast<const uint32_t*>(code.data()) });
    check_res(ret, "Failed to create shader module");
    return module;
}

void create_pipeline(DeviceContext& device)
{
    vk::ShaderModule vert = create_shader_module(device, "vert.spv");
    vk::ShaderModule frag = create_shader_module(device, "frag.spv");
    auto pipeline_layout_ret = device.functions.CreatePipelineLayout({ .setLayoutCount = 0, .pushConstantRangeCount = 0 });
    check_res(pipeline_layout_ret, "Failed to create pipeline layout");
    device.pipeline_layout = pipeline_layout_ret.value();

    float blend_constant[4] = { 0.f, 0.f, 0.f, 0.f };

    auto [pipelines, pipeline_ret] = device.functions.CreateGraphicsPipelines(
      nullptr,
      { vk::GraphicsPipelineCreateInfo{}
          .setPStages(
            { vk::PipelineShaderStageCreateInfo{}.setStage(vk::ShaderStageFlagBits::Vertex).setModule(vert).setPName("main"),
              vk::PipelineShaderStageCreateInfo{}.setStage(vk::ShaderStageFlagBits::Fragment).setModule(frag).setPName("main") })
          .setPVertexInputState(vk::PipelineVertexInputStateCreateInfo{})
          .setPInputAssemblyState(vk::PipelineInputAssemblyStateCreateInfo{}.setTopology(vk::PrimitiveTopology::TriangleList))
          .setPViewportState(vk::PipelineViewportStateCreateInfo{}
                               .setPViewports({ { 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f } })
                               .setPScissors({ { .offset = { 0, 0 }, .extent = { width, height } } }))
          .setPRasterizationState(vk::PipelineRasterizationStateCreateInfo{}
                                    .setPolygonMode(vk::PolygonMode::Fill)
                                    .setCullMode(vk::CullModeFlagBits::Back)
                                    .setFrontFace(vk::FrontFace::Clockwise)
                                    .setLineWidth(1.f))
          .setPMultisampleState(vk::PipelineMultisampleStateCreateInfo{}
                                  .setRasterizationSamples(vk::SampleCountFlagBits::e1)
                                  .setSampleShadingEnable(false))
          .setPColorBlendState(vk::PipelineColorBlendStateCreateInfo{}
                                 .setLogicOpEnable(false)
                                 .setPAttachments({ vk::PipelineColorBlendAttachmentState{}.setBlendEnable(false).setColorWriteMask(
                                   vk::ColorComponentFlagBits::R | vk::ColorComponentFlagBits::G | vk::ColorComponentFlagBits::B |
                                   vk::ColorComponentFlagBits::A) })
                                 .setBlendConstants(blend_constant))
          .setPDynamicState(
            vk::PipelineDynamicStateCreateInfo{}.setPDynamicStates({ vk::DynamicState::Viewport, vk::DynamicState::Scissor }))
          .setLayout(pipeline_layout_ret.value())
          .setRenderPass(device.render_pass) });

    check_res(pipeline_ret, "Failed to create graphipcs pipeline");
    device.pipeline = pipelines[0];
    device.functions.DestroyShaderModule(vert);
    device.functions.DestroyShaderModule(frag);
}

void create_command_buffers(DeviceContext& device)
{
    auto cmd_pool_ret = device.functions.CreateCommandPool({ .queueFamilyIndex = 0 });
    check_res(cmd_pool_ret, "Failed to create command pool");

    device.cmd_pool = cmd_pool_ret.value();
    auto [cmds, cmd_ret] = device.functions.AllocateCommandBuffers(
      { .commandPool = device.cmd_pool, .level = vk::CommandBufferLevel::Primary, .commandBufferCount = device.image_count });
    check_res(cmd_ret, "Failed to create command buffers");
    device.cmd_buffers = std::vector<vk::CommandBuffer>(cmds.begin(), cmds.end());

    for (uint32_t i = 0; i < device.cmd_buffers.size(); i++) {
        vk::CommandBufferFunctions funcs(device.functions, device.cmd_buffers[i]);
        cmd_ret = funcs.Begin({});
        check_res(cmd_ret, "Failed to begin command buffer");

        vk::Viewport viewport = { 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f };
        vk::Rect2D scissor = { .offset = { 0, 0 }, .extent = { width, height } };
        funcs
          .BeginRenderPass(vk::RenderPassBeginInfo{ .renderPass = device.render_pass,
                                                    .framebuffer = device.framebuffers[i],
                                                    .renderArea = scissor }
                             .setPClearValues({ vk::ClearValue{ .color = { { 0.f, 0.f, 0.f, 1.f } } } }),
                           vk::SubpassContents::Inline)
          .BindPipeline(vk::PipelineBindPoint::Graphics, device.pipeline)
          .SetViewport(0, viewport)
          .SetViewport(0, { viewport })
          .SetScissor(0, vk::Rect2D{ .offset = { 0, 0 }, .extent = { width, height } })
          .Draw(3, 1, 0, 0)
          .EndRenderPass();
        cmd_ret = funcs.End();
        check_res(cmd_ret, "Failed to end command buffer");
    }
}

void setup_sync_objects(DeviceContext& device)
{
    device.fences.resize(device.image_count);
    device.available_semaphores.resize(device.image_count);
    device.finished_semaphores.resize(device.image_count);
    for (uint32_t i = 0; i < device.image_count; i++) {
        auto [fence, fence_ret] = device.functions.CreateFence({ .flags = vk::FenceCreateFlagBits::Signaled });
        check_res(fence_ret, "Failed to create fence");
        auto [avail_sem, avail_sem_ret] = device.functions.CreateSemaphore({});
        check_res(avail_sem_ret, "Failed to create semaphore");
        auto [finish_sem, finish_sem_ret] = device.functions.CreateSemaphore({});
        check_res(finish_sem_ret, "Failed to create semaphore");

        device.fences[i] = fence;
        device.available_semaphores[i] = avail_sem;
        device.finished_semaphores[i] = finish_sem;
    }
}

void recreate_swapchain(DeviceContext& device)
{
    check_res(device.queue_functions.WaitIdle(), "");
    device.functions.DestroyCommandPool(device.cmd_pool);

    for (auto& framebuffer : device.framebuffers) {
        device.functions.DestroyFramebuffer(framebuffer);
    }
    for (auto& image_view : device.swapchain_image_views) {
        device.functions.DestroyImageView(image_view);
    }

    setup_swapchain(device);
    create_framebuffers(device);
    create_command_buffers(device);
}

void draw_frame(DeviceContext& device)
{
    auto fence_ret = device.functions.WaitForFences({ device.fences[device.current_frame] }, true, UINT64_MAX);
    check_res(fence_ret, "Failed to wait for fence");

    fence_ret = device.functions.ResetFences({ device.fences[device.current_frame] });
    check_res(fence_ret, "Failed to reset fence");

    auto image_index_ret = device.functions.AcquireNextImageKHR(
      device.swapchain, UINT64_MAX, device.available_semaphores[device.current_frame], nullptr);
    if (image_index_ret.raw_result() == vk::Result::ErrorOutOfDateKHR) {
        return recreate_swapchain(device);
    } else if (image_index_ret.raw_result() != vk::Result::Success && image_index_ret.raw_result() != vk::Result::SuboptimalKHR) {
        std::cerr << "failed to acquire swapchain image. Error " << vk::to_string(image_index_ret.raw_result()) << "\n";
    }

    auto submit_ret = device.queue_functions.Submit(vk::SubmitInfo{}
                                                      .setPWaitSemaphores({ device.available_semaphores[device.current_frame] })
                                                      .setPWaitDstStageMask({ vk::PipelineStageFlagBits::ColorAttachmentOutput })
                                                      .setPCommandBuffers({ device.cmd_buffers[image_index_ret.value()] })
                                                      .setPSignalSemaphores({ device.finished_semaphores[device.current_frame] }),
                                                    device.fences[device.current_frame]);
    check_res(submit_ret, "Failed to submit command buffer");

    auto present_ret = device.queue_functions.PresentKHR(vk::PresentInfoKHR{}
                                                           .setPWaitSemaphores({ device.finished_semaphores[device.current_frame] })
                                                           .setPSwapchains({ device.swapchain })
                                                           .setPImageIndices({ image_index_ret.value() }));
    if (present_ret == vk::Result::ErrorOutOfDateKHR || present_ret == vk::Result::SuboptimalKHR) {
        return recreate_swapchain(device);
    }
    check_res(present_ret, "Failed to present");

    device.current_frame = (device.current_frame + 1) % device.image_count;
}

void destroy_device(DeviceContext& device)
{
    for (auto& sem : device.available_semaphores) {
        device.functions.DestroySemaphore(sem);
    }
    for (auto& sem : device.finished_semaphores) {
        device.functions.DestroySemaphore(sem);
    }
    for (auto& fence : device.fences) {
        device.functions.DestroyFence(fence);
    }
    device.functions.DestroyCommandPool(device.cmd_pool);
    for (auto& framebuffer : device.framebuffers) {
        device.functions.DestroyFramebuffer(framebuffer);
    }
    device.functions.DestroyPipeline(device.pipeline);
    device.functions.DestroyPipelineLayout(device.pipeline_layout);
    device.functions.DestroyRenderPass(device.render_pass);
    for (auto& image_view : device.swapchain_image_views) {
        device.functions.DestroyImageView(image_view);
    }
    device.functions.DestroySwapchainKHR(device.swapchain);
    device.functions.DestroyDevice();
}

void destroy_renderer(RendererContext& renderer)
{
    renderer.functions.DestroySurfaceKHR(renderer.surface);
    renderer.functions.DestroyInstance();
    destroy_window_glfw(renderer.window);
}

int main()
{
    RendererContext context;
    DeviceContext device;

    create_renderer_context(context);
    create_device_context(context, device);
    setup_queues(device, context.physical_device_functions);
    setup_swapchain(device);
    setup_renderpass(device);
    create_framebuffers(device);
    create_pipeline(device);
    create_command_buffers(device);
    setup_sync_objects(device);

    while (!glfwWindowShouldClose(context.window)) {
        glfwPollEvents();
        draw_frame(device);
    }
    check_res(device.queue_functions.WaitIdle(), "Couldn't wait to shut down");
    destroy_device(device);
    destroy_renderer(context);
    return 0;
}