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

import vulkan_module;

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <assert.h>

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
    vk::InstanceFunctions instance_functions;
    vk::PhysicalDevice physical_device;
    vk::PhysicalDeviceFunctions physical_device_functions;
    vk::Device device;
    vk::DeviceFunctions functions;
    vk::Queue graphics_queue;
    vk::QueueFunctions queue_functions;
    vk::SwapchainKHR swapchain;
    std::vector<vk::Image> swapchain_images;
    uint32_t image_count = 0;
    std::vector<vk::ImageView> swapchain_image_views;
    vk::SurfaceFormatKHR swapchain_surface_format;
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

    vk::DeviceFunctions* operator->() { return &functions; }
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

    context.window = create_window_glfw("Vulkan Module Triangle", false);
    check_res(context.window != nullptr, "Failed to create glfw window");

    vk::GlobalFunctions global_functions = vk::GlobalFunctions(context.library);

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    vk::InstanceCreateInfo inst_info{};
    inst_info.setEnabledExtensionCount(glfw_extension_count);
    inst_info.setPpEnabledExtensionNames(glfw_extensions);

    auto layers = global_functions.EnumerateInstanceLayerProperties().value();
    const char* layer_names[] = { "VK_LAYER_KHRONOS_validation" };
    for (auto& layer : layers) {
        if (std::string(layer.layerName) == std::string("VK_LAYER_KHRONOS_validation")) {
            // inst_builder.addEnabledLayerNames("VK_LAYER_KHRONOS_validation");
            inst_info.ppEnabledLayerNames = layer_names;
            break;
        }
    }

    context.instance = global_functions.CreateInstance(inst_info).value();
    context.instance_functions = vk::InstanceFunctions(global_functions, context.instance);

    context.surface = create_surface_glfw(context.instance.get(), context.window);
    check_res(context.surface.valid(), "Failed to create glfw surface");

    context.physical_device =
      context.instance_functions.EnumeratePhysicalDevices().value().at(0); // get first physical device returned
    context.physical_device_functions = vk::PhysicalDeviceFunctions(context.instance_functions, context.physical_device);

    // needed to make the validation layers shut up
    auto surface_ret = context.physical_device_functions.GetSurfaceSupportKHR(0, context.surface);
    check_res(surface_ret.has_value(), "Failed to query surface support");
    check_res(surface_ret.value(), "Surface doesn't support present");
}

void create_device_context(RendererContext& context)
{
    const char* extensions[] = { "VK_KHR_swapchain" };
    context.device =
      context.physical_device_functions
        .CreateDevice(vk::DeviceCreateInfo{}
                        .setEnabledExtensionCount(1)
                        .setPpEnabledExtensionNames(extensions)
                        .setPQueueCreateInfos({ vk::DeviceQueueCreateInfo{}.setQueueFamilyIndex(0).setPQueuePriorities({ 1.f }) }))
        .value();
    context.functions = vk::DeviceFunctions(context.instance_functions, context.device);
    context.physical_device_functions = context.physical_device_functions;
}

void setup_queues(RendererContext& context)
{
    auto queue_family_props = context.physical_device_functions.GetQueueFamilyProperties();
    uint32_t graphics_queue_family = 0;
    for (uint32_t i = 0; i < queue_family_props.size(); i++) {
        if (queue_family_props[0].queueFlags & vk::QueueFlagBits::Graphics && queue_family_props[0].queueCount > 0) {
            graphics_queue_family = i;
            break;
        }
    }

    check_res(graphics_queue_family == 0, "First queue isn't the graphics queue, implicit assumptions failed");

    context.graphics_queue = context->GetDeviceQueue(graphics_queue_family, 0);
    context.queue_functions = vk::QueueFunctions(context.functions, context.graphics_queue);
}

void setup_swapchain(RendererContext& context)
{
    auto caps = context.physical_device_functions.GetSurfaceCapabilitiesKHR(context.surface).value();
    context.swapchain_surface_format = context.physical_device_functions.GetSurfaceFormatsKHR(context.surface).value().at(0);
    context.image_count = 3;
    context.swapchain = context.functions
                          .CreateSwapchainKHR(vk::SwapchainCreateInfoKHR{
                            .surface = context.surface,
                            .minImageCount = 3,
                            .imageFormat = context.swapchain_surface_format.format,
                            .imageColorSpace = context.swapchain_surface_format.colorSpace,
                            .imageExtent = { width, height },
                            .imageArrayLayers = 1,
                            .imageUsage = vk::ImageUsageFlagBits::ColorAttachment,
                            .imageSharingMode = vk::SharingMode::Exclusive,
                            .pQueueFamilyIndices = nullptr,
                            .preTransform = caps.currentTransform,
                            .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::OpaqueBitKHR,
                            .presentMode = vk::PresentModeKHR::FifoKHR,
                          })
                          .value();
    context.swapchain_images = context->GetSwapchainImagesKHR(context.swapchain).value();

    for (auto& image : context.swapchain_images) {
        context.swapchain_image_views.push_back(
          context.functions
            .CreateImageView(vk::ImageViewCreateInfo{
              .image = image,
              .viewType = vk::ImageViewType::e2D,
              .format = context.swapchain_surface_format.format,
              .subresourceRange = { .aspectMask = vk::ImageAspectFlagBits::Color, .levelCount = 1, .layerCount = 1 } })
            .value());
    }
}

void setup_renderpass(RendererContext& context)
{
    auto attach_desc = vk::AttachmentDescription{}
                         .setFormat(context.swapchain_surface_format.format)
                         .setSamples(vk::SampleCountFlagBits::e1)
                         .setLoadOp(vk::AttachmentLoadOp::Clear)
                         .setStoreOp(vk::AttachmentStoreOp::Store)
                         .setStencilLoadOp(vk::AttachmentLoadOp::DontCare)
                         .setStencilStoreOp(vk::AttachmentStoreOp::DontCare)
                         .setInitialLayout(vk::ImageLayout::Undefined)
                         .setFinalLayout(vk::ImageLayout::PresentSrcKHR);
    auto subpass_desc =
      vk::SubpassDescription{}
        .setPipelineBindPoint(vk::PipelineBindPoint::Graphics)
        .setPColorAttachments({ vk::AttachmentReference{}.setAttachment(0).setLayout(vk::ImageLayout::ColorAttachmentOptimal) });
    auto subpass_dep = vk::SubpassDependency{}
                         .setSrcSubpass(vk::SUBPASS_EXTERNAL)
                         .setDstSubpass(0)
                         .setSrcStageMask(vk::PipelineStageFlagBits::ColorAttachmentOutput)
                         .setDstStageMask(vk::PipelineStageFlagBits::ColorAttachmentOutput)
                         .setDstAccessMask(vk::AccessFlagBits::ColorAttachmentRead | vk::AccessFlagBits::ColorAttachmentWrite);
    context.render_pass = context.functions
                            .CreateRenderPass(vk::RenderPassCreateInfo{}
                                                .setPAttachments({ attach_desc })
                                                .setPSubpasses({ subpass_desc })
                                                .setPDependencies({ subpass_dep }))
                            .value();
}
void create_framebuffers(RendererContext& context)
{
    auto framebuffer =
      vk::FramebufferCreateInfo{}.setRenderPass(context.render_pass).setWidth(width).setHeight(height).setLayers(1);
    for (auto& view : context.swapchain_image_views) {
        context.framebuffers.push_back(context.functions.CreateFramebuffer(framebuffer.setPAttachments({ view })).value());
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

vk::ShaderModule create_shader_module(RendererContext& context, std::string const& filename)
{
    auto code = read_file(filename);
    return context.functions
      .CreateShaderModule({ .codeSize = code.size(), .pCode = reinterpret_cast<const uint32_t*>(code.data()) })
      .value();
}

void create_pipeline(RendererContext& context)
{
    vk::ShaderModule vert = create_shader_module(context, "vert.spv");
    vk::ShaderModule frag = create_shader_module(context, "frag.spv");

    context.pipeline_layout = context->CreatePipelineLayout({ .setLayoutCount = 0, .pushConstantRangeCount = 0 }).value();

    float blend_constant[4] = { 0.f, 0.f, 0.f, 0.f };
    context.pipeline =
      context.functions
        .CreateGraphicsPipelines(
          nullptr,
          { vk::GraphicsPipelineCreateInfo{}
              .setPStages(
                { vk::PipelineShaderStageCreateInfo{}.setStage(vk::ShaderStageFlagBits::Vertex).setModule(vert).setPName("main"),
                  vk::PipelineShaderStageCreateInfo{}
                    .setStage(vk::ShaderStageFlagBits::Fragment)
                    .setModule(frag)
                    .setPName("main") })
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
              .setPColorBlendState(
                vk::PipelineColorBlendStateCreateInfo{}
                  .setLogicOpEnable(false)
                  .setPAttachments({ vk::PipelineColorBlendAttachmentState{}.setBlendEnable(false).setColorWriteMask(
                    vk::ColorComponentFlagBits::R | vk::ColorComponentFlagBits::G | vk::ColorComponentFlagBits::B |
                    vk::ColorComponentFlagBits::A) })
                  .setBlendConstants(blend_constant))
              .setPDynamicState(
                vk::PipelineDynamicStateCreateInfo{}.setPDynamicStates({ vk::DynamicState::Viewport, vk::DynamicState::Scissor }))
              .setLayout(context.pipeline_layout)
              .setRenderPass(context.render_pass) })
        .value()[0];

    context->DestroyShaderModule(vert);
    context->DestroyShaderModule(frag);
}

void create_command_buffers(RendererContext& context)
{
    context.cmd_pool = context->CreateCommandPool({ .queueFamilyIndex = 0 }).value();
    context.cmd_buffers =
      context.functions
        .AllocateCommandBuffers(
          { .commandPool = context.cmd_pool, .level = vk::CommandBufferLevel::Primary, .commandBufferCount = context.image_count })
        .value();

    for (uint32_t i = 0; i < context.cmd_buffers.size(); i++) {
        vk::CommandBufferFunctions funcs(context.functions, context.cmd_buffers[i]);
        check_res(funcs.Begin({}), "Failed to begin command buffer");

        vk::Rect2D scissor = { .offset = { 0, 0 }, .extent = { width, height } };
        check_res(funcs
                    .BeginRenderPass(vk::RenderPassBeginInfo{}
                                       .setRenderPass(context.render_pass)
                                       .setFramebuffer(context.framebuffers[i])
                                       .setRenderArea(scissor)
                                       .setPClearValues({ vk::ClearValue{ .color = { { 0.f, 0.f, 0.f, 1.f } } } }),
                                     vk::SubpassContents::Inline)
                    .BindPipeline(vk::PipelineBindPoint::Graphics, context.pipeline)
                    .SetViewport(0, vk::Viewport{ 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f })
                    .SetScissor(0, scissor)
                    .Draw(3, 1, 0, 0)
                    .EndRenderPass()
                    .End(),
                  "Failed to end command buffer");
    }
}

void setup_sync_objects(RendererContext& context)
{
    context.fences.resize(context.image_count);
    context.available_semaphores.resize(context.image_count);
    context.finished_semaphores.resize(context.image_count);
    for (uint32_t i = 0; i < context.image_count; i++) {
        context.fences[i] = context->CreateFence({ .flags = vk::FenceCreateFlagBits::Signaled }).value();
        context.available_semaphores[i] = context->CreateSemaphore({}).value();
        context.finished_semaphores[i] = context->CreateSemaphore({}).value();
    }
}

void recreate_swapchain(RendererContext& context)
{
    check_res(context.queue_functions.WaitIdle(), "");
    context->DestroyCommandPool(context.cmd_pool);

    for (auto& framebuffer : context.framebuffers) {
        context->DestroyFramebuffer(framebuffer);
    }
    for (auto& image_view : context.swapchain_image_views) {
        context->DestroyImageView(image_view);
    }

    setup_swapchain(context);
    create_framebuffers(context);
    create_command_buffers(context);
}

void draw_frame(RendererContext& context)
{
    check_res(context->WaitForFences({ context.fences[context.current_frame] }, true, UINT64_MAX), "Failed to wait for fence");

    check_res(context->ResetFences({ context.fences[context.current_frame] }), "Failed to reset fence");

    auto image_index_ret =
      context->AcquireNextImageKHR(context.swapchain, UINT64_MAX, context.available_semaphores[context.current_frame], nullptr);
    if (image_index_ret.raw_result() == vk::Result::ErrorOutOfDateKHR) {
        return recreate_swapchain(context);
    } else if (image_index_ret.raw_result() != vk::Result::Success && image_index_ret.raw_result() != vk::Result::SuboptimalKHR) {
        std::cerr << "failed to acquire swapchain image. Error " << vk::to_string(image_index_ret.raw_result()) << "\n";
    }

    check_res(context.queue_functions.Submit(vk::SubmitInfo{}
                                               .setPWaitSemaphores({ context.available_semaphores[context.current_frame] })
                                               .setPWaitDstStageMask({ vk::PipelineStageFlagBits::ColorAttachmentOutput })
                                               .setPCommandBuffers({ context.cmd_buffers[image_index_ret.value()] })
                                               .setPSignalSemaphores({ context.finished_semaphores[context.current_frame] }),
                                             context.fences[context.current_frame]),
              "Failed to submit command buffer");

    auto present_ret =
      context.queue_functions.PresentKHR(vk::PresentInfoKHR{}
                                           .setPWaitSemaphores({ context.finished_semaphores[context.current_frame] })
                                           .setPSwapchains({ context.swapchain })
                                           .setPImageIndices({ image_index_ret.value() }));
    if (present_ret == vk::Result::ErrorOutOfDateKHR || present_ret == vk::Result::SuboptimalKHR) {
        return recreate_swapchain(context);
    }
    check_res(present_ret, "Failed to present");

    context.current_frame = (context.current_frame + 1) % context.image_count;
}

void destroy_device(RendererContext& context)
{
    for (auto& sem : context.available_semaphores) {
        context->DestroySemaphore(sem);
    }
    for (auto& sem : context.finished_semaphores) {
        context->DestroySemaphore(sem);
    }
    for (auto& fence : context.fences) {
        context->DestroyFence(fence);
    }
    context->DestroyCommandPool(context.cmd_pool);
    for (auto& framebuffer : context.framebuffers) {
        context->DestroyFramebuffer(framebuffer);
    }
    context->DestroyPipeline(context.pipeline);
    context->DestroyPipelineLayout(context.pipeline_layout);
    context->DestroyRenderPass(context.render_pass);
    for (auto& image_view : context.swapchain_image_views) {
        context->DestroyImageView(image_view);
    }
    context->DestroySwapchainKHR(context.swapchain);
    context->DestroyDevice();
}

void destroy_renderer(RendererContext& renderer)
{
    renderer.instance_functions.DestroySurfaceKHR(renderer.surface);
    renderer.instance_functions.DestroyInstance();
    destroy_window_glfw(renderer.window);
}

int main()
{
    RendererContext context;

    create_renderer_context(context);
    create_device_context(context);
    setup_queues(context);
    setup_swapchain(context);
    setup_renderpass(context);
    create_framebuffers(context);
    create_pipeline(context);
    create_command_buffers(context);
    setup_sync_objects(context);

    while (!glfwWindowShouldClose(context.window)) {
        glfwPollEvents();
        draw_frame(context);
    }
    check_res(context.queue_functions.WaitIdle(), "Couldn't wait to shut down");
    destroy_device(context);
    destroy_renderer(context);
    return 0;
}