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

#include "vulkan/vulkan.h"
#include "vulkan/vulkan_string.h"

#include <assert.h>
#include <cstring>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <GLFW/glfw3.h>

constexpr uint32_t width = 512;
constexpr uint32_t height = 512;

struct RendererContext
{
    GLFWwindow* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical_device;
    VkDevice device;
    VkDeviceDispatchTable functions;
    VkQueue graphics_queue;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchain_images;
    uint32_t image_count = 0;
    std::vector<VkImageView> swapchain_image_views;
    VkFormat swapchain_img_format;
    VkRenderPass render_pass;
    std::vector<VkFramebuffer> framebuffers;
    VkPipelineLayout pipeline_layout;
    VkPipeline pipeline;
    VkCommandPool cmd_pool;
    std::vector<VkCommandBuffer> cmd_buffers;
    uint32_t current_frame = 0;
    std::vector<VkFence> fences;
    std::vector<VkSemaphore> available_semaphores;
    std::vector<VkSemaphore> finished_semaphores;

    operator VkDevice() { return device; }
    VkDeviceDispatchTable* operator->() { return &functions; }
};
void check_res(bool result, const char* msg)
{
    if (!result) {
        std::cerr << msg << "\n";
        assert(false);
    }
}
void check_res(VkResult result, const char* msg)
{
    if (result != VkResult::Success) {
        std::cerr << msg << ": Result = " << to_string(result) << "\n";
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
VkSurfaceKHR create_surface_glfw(VkInstance instance, GLFWwindow* window)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult err = glfwCreateWindowSurface(instance, window, NULL, &surface);
    if (err != VkResult::Success) {
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
    return surface;
}

// Helper for robustly executing the two-call pattern
// NOTE: doesn't work on functions that dont return VkResult
template<typename T, typename F, typename... Ts>
auto GetVectorInit(F&& f, T init, Ts&&... ts) -> std::vector<T>
{
    uint32_t count = 0;
    std::vector<T> results;
    VkResult err;
    do {
        err = f(ts..., &count, nullptr);
        check_res(err, "failed to get size");
        results.resize(count, init);
        err = f(ts..., &count, results.data());
        results.resize(count);
    } while (err == VK_INCOMPLETE);
    check_res(err, "failed to get data");
    return results;
}

template<typename T, typename F, typename... Ts>
auto GetVector(F&& f, Ts&&... ts) -> std::vector<T>
{
    return GetVectorInit(f, T(), ts...);
}

void create_renderer_context(RendererContext& context)
{

    check_res(vkInitializeLoaderLibrary(), "Failed to initialize the loader library");

    context.window = create_window_glfw("Sample Triangle", false);
    check_res(context.window != nullptr, "Failed to create glfw window");

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    VkInstanceCreateInfo inst_info{};
    inst_info.enabledExtensionCount = glfw_extension_count;
    inst_info.ppEnabledExtensionNames = glfw_extensions;

    auto layer_props = GetVector<VkLayerProperties>(vkEnumerateInstanceLayerProperties);

    const char* layer_names[] = { "VK_LAYER_KHRONOS_validation" };
    for (auto& layer : layer_props) {
        if (std::strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0) {
            inst_info.ppEnabledLayerNames = layer_names;
            inst_info.enabledLayerCount = 1;
            break;
        }
    }

    check_res(vkCreateInstance(&inst_info, nullptr, &context.instance), "Failed to init Vulkan Instance");

    vkInitializeInstanceFunctions(context.instance);

    context.surface = create_surface_glfw(context.instance, context.window);
    check_res(context.surface != VK_NULL_HANDLE, "Failed to create glfw surface");

    auto physical_devices = GetVector<VkPhysicalDevice>(vkEnumeratePhysicalDevices, context.instance);

    context.physical_device = physical_devices[0]; // get first physical device returned
    VkBool32 suppprted = 0;
    check_res(vkGetPhysicalDeviceSurfaceSupportKHR(context.physical_device, 0, context.surface, &suppprted),
              "Failed to query surface support");
    check_res(suppprted, "Surface doesn't support present");
}

void create_device_context(RendererContext& context)
{
    const char* extensions[] = { "VK_KHR_swapchain" };
    float priority = 1.f;
    VkDeviceQueueCreateInfo queue_infos;
    queue_infos.pQueuePriorities = &priority;
    queue_infos.queueCount = 1;
    queue_infos.queueFamilyIndex = 0;
    VkDeviceCreateInfo info;
    info.enabledExtensionCount = 1;
    info.ppEnabledExtensionNames = extensions;
    info.queueCreateInfoCount = 1;
    info.pQueueCreateInfos = &queue_infos;
    check_res(vkCreateDevice(context.physical_device, &info, nullptr, &context.device), "Failed to create a vulkan device");

    vkInitializeDeviceDispatchTable(context.device, context.functions);
}

void setup_queues(RendererContext& context)
{
    uint32_t queue_family_size = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(context.physical_device, &queue_family_size, nullptr);
    std::vector<VkQueueFamilyProperties> queue_family_props(queue_family_size);
    vkGetPhysicalDeviceQueueFamilyProperties(context.physical_device, &queue_family_size, queue_family_props.data());

    uint32_t graphics_queue_family = 0;
    for (uint32_t i = 0; i < queue_family_props.size(); i++) {
        if (queue_family_props[0].queueFlags & VkQueueFlagBits::Graphics && queue_family_props[0].queueCount > 0) {
            graphics_queue_family = i;
            break;
        }
    }
    check_res(graphics_queue_family == 0, "First queue isn't the graphics queue, implicit assumptions failed");

    context->vkGetDeviceQueue(context.device, graphics_queue_family, 0, &context.graphics_queue);
}

void setup_swapchain(RendererContext& context)
{
    auto surf_formats =
      GetVector<VkSurfaceFormatKHR>(vkGetPhysicalDeviceSurfaceFormatsKHR, context.physical_device, context.surface);

    VkSurfaceCapabilitiesKHR surf_caps;
    check_res(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context.physical_device, context.surface, &surf_caps),
              "Failed to get surface capabilities");

    context.swapchain_img_format = surf_formats[0].format;
    context.image_count = 3;

    VkSwapchainCreateInfoKHR info;
    info.surface = context.surface;
    info.minImageCount = 3;
    info.imageFormat = context.swapchain_img_format;
    info.imageColorSpace = surf_formats[0].colorSpace;
    info.imageExtent = { width, height };
    info.imageArrayLayers = 1;
    info.imageUsage = VkImageUsageFlagBits::ColorAttachment;
    info.imageSharingMode = VkSharingMode::Exclusive;
    info.pQueueFamilyIndices = nullptr;
    info.preTransform = surf_caps.currentTransform;
    info.compositeAlpha = VkCompositeAlphaFlagBitsKHR::OpaqueBitKHR;
    info.presentMode = VkPresentModeKHR::FifoKHR;

    check_res(context->vkCreateSwapchainKHR(context, &info, nullptr, &context.swapchain), "Unable to create Swapchain");

    context.swapchain_images = GetVector<VkImage>(context->vkGetSwapchainImagesKHR, context.device, context.swapchain);

    for (auto& image : context.swapchain_images) {
        VkImageViewCreateInfo view_info;
        view_info.image = image;
        view_info.viewType = VkImageViewType::e2D;
        view_info.format = context.swapchain_img_format;
        view_info.subresourceRange = { VkImageAspectFlagBits::Color, 0, 1, 0, 1 };
        VkImageView view;
        check_res(context->vkCreateImageView(context, &view_info, nullptr, &view), "Failed to create swapchain image view");

        context.swapchain_image_views.push_back(view);
    }
}

void setup_renderpass(RendererContext& context)
{
    VkAttachmentDescription desc;
    desc.format = context.swapchain_img_format;
    desc.samples = VkSampleCountFlagBits::e1;
    desc.loadOp = VkAttachmentLoadOp::Clear;
    desc.storeOp = VkAttachmentStoreOp::Store;
    desc.stencilLoadOp = VkAttachmentLoadOp::DontCare;
    desc.stencilStoreOp = VkAttachmentStoreOp::DontCare;
    desc.initialLayout = VkImageLayout::Undefined;
    desc.finalLayout = VkImageLayout::PresentSrcKHR;

    VkAttachmentReference ref{ 0, VkImageLayout::ColorAttachmentOptimal };
    VkSubpassDescription sub_desc;
    sub_desc.pipelineBindPoint = VkPipelineBindPoint::Graphics;
    sub_desc.pColorAttachments = &ref;
    sub_desc.colorAttachmentCount = 1;
    VkSubpassDependency dep;
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VkPipelineStageFlagBits::ColorAttachmentOutput;
    dep.dstStageMask = VkPipelineStageFlagBits::ColorAttachmentOutput;
    dep.dstAccessMask = VkAccessFlagBits::ColorAttachmentRead | VkAccessFlagBits::ColorAttachmentWrite;

    VkRenderPassCreateInfo info;
    info.attachmentCount = 1;
    info.pAttachments = &desc;
    info.dependencyCount = 1;
    info.pDependencies = &dep;
    info.subpassCount = 1;
    info.pSubpasses = &sub_desc;
    check_res(context->vkCreateRenderPass(context, &info, nullptr, &context.render_pass), "Failed to create renderpass");
}
void create_framebuffers(RendererContext& context)
{
    for (auto& view : context.swapchain_image_views) {
        VkFramebufferCreateInfo info;
        info.renderPass = context.render_pass;
        info.attachmentCount = 1;
        info.pAttachments = &view;
        info.width = width;
        info.height = height;
        info.layers = 1;
        VkFramebuffer framebuffer;
        check_res(context->vkCreateFramebuffer(context, &info, nullptr, &framebuffer), "Failed to create framebuffer");
        context.framebuffers.push_back(framebuffer);
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

VkShaderModule create_shader_module(RendererContext& context, std::string const& filename)
{
    auto code = read_file(filename);
    VkShaderModule mod;
    VkShaderModuleCreateInfo info;
    info.codeSize = code.size();
    info.pCode = reinterpret_cast<const uint32_t*>(code.data());
    check_res(context->vkCreateShaderModule(context, &info, nullptr, &mod), "Failed to create shader module");
    return mod;
}

void create_pipeline(RendererContext& context)
{
    VkShaderModule vert = create_shader_module(context, "vert.spv");
    VkShaderModule frag = create_shader_module(context, "frag.spv");
    VkPipelineLayoutCreateInfo p_info_cr;
    check_res(context->vkCreatePipelineLayout(context, &p_info_cr, nullptr, &context.pipeline_layout),
              "Failed to create pipeline layout");

    VkViewport viewport = { 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f };
    VkRect2D scissor = { { 0, 0 }, { width, height } };
    VkPipelineShaderStageCreateInfo vert_stage;
    vert_stage.stage = VkShaderStageFlagBits::Vertex;
    vert_stage.module = vert;
    vert_stage.pName = "main";
    VkPipelineShaderStageCreateInfo frag_stage;
    frag_stage.stage = VkShaderStageFlagBits::Fragment;
    frag_stage.module = frag;
    frag_stage.pName = "main";
    VkPipelineShaderStageCreateInfo shaders[2] = { vert_stage, frag_stage };
    VkPipelineVertexInputStateCreateInfo vert_input;
    VkPipelineInputAssemblyStateCreateInfo input_assembly;
    input_assembly.topology = VkPrimitiveTopology::TriangleList;
    VkPipelineViewportStateCreateInfo viewport_state;
    viewport_state.viewportCount = 1;
    viewport_state.pViewports = &viewport;
    viewport_state.scissorCount = 1;
    viewport_state.pScissors = &scissor;
    VkPipelineRasterizationStateCreateInfo rasterization;
    rasterization.polygonMode = VkPolygonMode::Fill;
    rasterization.cullMode = VkCullModeFlagBits::Back;
    rasterization.frontFace = VkFrontFace::Clockwise;
    rasterization.lineWidth = 1.f;
    VkPipelineMultisampleStateCreateInfo multisample;
    multisample.rasterizationSamples = VkSampleCountFlagBits::e1;
    multisample.sampleShadingEnable = false;
    VkPipelineColorBlendAttachmentState blend_attachment;
    blend_attachment.blendEnable = false;
    blend_attachment.colorWriteMask =
      VkColorComponentFlagBits::R | VkColorComponentFlagBits::G | VkColorComponentFlagBits::B | VkColorComponentFlagBits::A;
    VkPipelineColorBlendStateCreateInfo color_blend;
    color_blend.logicOpEnable = false;
    color_blend.pAttachments = &blend_attachment;
    color_blend.attachmentCount = 1;

    VkDynamicState states[2] = { VkDynamicState::Viewport, VkDynamicState::Scissor };
    VkPipelineDynamicStateCreateInfo dynamic_state;
    dynamic_state.dynamicStateCount = 2;
    dynamic_state.pDynamicStates = states;

    VkGraphicsPipelineCreateInfo info;
    info.renderPass = context.render_pass;
    info.layout = context.pipeline_layout;
    info.stageCount = 2;
    info.pStages = &shaders[0];
    info.pVertexInputState = &vert_input;
    info.pInputAssemblyState = &input_assembly;
    info.pViewportState = &viewport_state;
    info.pRasterizationState = &rasterization;
    info.pMultisampleState = &multisample;
    info.pColorBlendState = &color_blend;
    info.pDynamicState = &dynamic_state;

    check_res(context->vkCreateGraphicsPipelines(context, VK_NULL_HANDLE, 1, &info, nullptr, &context.pipeline),
              "Failed to create graphipcs pipeline");
    context->vkDestroyShaderModule(context, vert, nullptr);
    context->vkDestroyShaderModule(context, frag, nullptr);
}

void create_command_buffers(RendererContext& context)
{
    VkCommandPoolCreateInfo pool_info;
    check_res(context->vkCreateCommandPool(context, &pool_info, nullptr, &context.cmd_pool), "Failed to create command pool");

    VkCommandBufferAllocateInfo alloc_info;
    alloc_info.commandPool = context.cmd_pool;
    alloc_info.level = VkCommandBufferLevel::Primary;
    alloc_info.commandBufferCount = context.image_count;
    context.cmd_buffers.resize(3);
    check_res(context->vkAllocateCommandBuffers(context, &alloc_info, context.cmd_buffers.data()),
              "Failed to create command buffers");

    int i = 0;
    for (auto& cmd_buf : context.cmd_buffers) {

        VkCommandBufferBeginInfo begin_info{};
        check_res(context->vkBeginCommandBuffer(cmd_buf, &begin_info), "Failed to begin command buffer");

        VkViewport viewport = { 0.f, 0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 1.f };
        VkRect2D scissor = { { 0, 0 }, { width, height } };
        VkClearValue clear_colors = { { 0.f, 0.f, 0.f, 1.f } };

        VkRenderPassBeginInfo renderpass_info;
        renderpass_info.renderPass = context.render_pass;
        renderpass_info.framebuffer = context.framebuffers[i++];
        renderpass_info.renderArea = scissor;
        renderpass_info.clearValueCount = 4;
        renderpass_info.pClearValues = &clear_colors;

        context->vkCmdBeginRenderPass(cmd_buf, &renderpass_info, VkSubpassContents::Inline);
        context->vkCmdBindPipeline(cmd_buf, VkPipelineBindPoint::Graphics, context.pipeline);
        context->vkCmdSetViewport(cmd_buf, 0, 1, &viewport);
        context->vkCmdSetScissor(cmd_buf, 0, 1, &scissor);
        context->vkCmdDraw(cmd_buf, 3, 1, 0, 0);
        context->vkCmdEndRenderPass(cmd_buf);
        check_res(context->vkEndCommandBuffer(cmd_buf), "Failed to end command buffer");
    }
}

void setup_sync_objects(RendererContext& context)
{
    context.fences.resize(context.image_count);
    context.available_semaphores.resize(context.image_count);
    context.finished_semaphores.resize(context.image_count);
    for (uint32_t i = 0; i < context.image_count; i++) {
        VkFenceCreateInfo fence_info;
        fence_info.flags = VkFenceCreateFlagBits::Signaled;
        check_res(context->vkCreateFence(context, &fence_info, nullptr, &context.fences[i]), "Failed to create fence");
        VkSemaphoreCreateInfo sem_info;
        check_res(context->vkCreateSemaphore(context, &sem_info, nullptr, &context.available_semaphores[i]),
                  "Failed to create semaphore");
        check_res(context->vkCreateSemaphore(context, &sem_info, nullptr, &context.finished_semaphores[i]),
                  "Failed to create semaphore");
    }
}

void recreate_swapchain(RendererContext& context)
{
    check_res(context->vkQueueWaitIdle(context.graphics_queue), "");
    context->vkDestroyCommandPool(context, context.cmd_pool, nullptr);

    for (auto& framebuffer : context.framebuffers) {
        context->vkDestroyFramebuffer(context, framebuffer, nullptr);
    }
    for (auto& image_view : context.swapchain_image_views) {
        context->vkDestroyImageView(context, image_view, nullptr);
    }

    setup_swapchain(context);
    create_framebuffers(context);
    create_command_buffers(context);
}

void draw_frame(RendererContext& context)
{
    check_res(context->vkWaitForFences(context, 1, &context.fences[context.current_frame], true, UINT64_MAX),
              "Failed to wait for fence");

    check_res(context->vkResetFences(context, 1, &context.fences[context.current_frame]), "Failed to reset fence");

    uint32_t image_index;
    auto image_index_ret = context->vkAcquireNextImageKHR(
      context, context.swapchain, UINT64_MAX, context.available_semaphores[context.current_frame], nullptr, &image_index);
    if (image_index_ret == VkResult::ErrorOutOfDateKHR) {
        return recreate_swapchain(context);
    } else if (image_index_ret != VkResult::Success && image_index_ret != VkResult::SuboptimalKHR) {
        std::cerr << "failed to acquire swapchain image. Error " << to_string(image_index_ret) << "\n";
    }
    VkPipelineStageFlags dst_stage_mask = VkPipelineStageFlagBits::ColorAttachmentOutput;
    VkSubmitInfo submit_info;
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = &context.available_semaphores[context.current_frame];
    submit_info.pWaitDstStageMask = &dst_stage_mask;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &context.cmd_buffers[image_index];
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = &context.finished_semaphores[context.current_frame];
    check_res(context->vkQueueSubmit(context.graphics_queue, 1, &submit_info, context.fences[context.current_frame]),
              "Failed to submit command buffer");

    VkPresentInfoKHR present_info;
    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = &context.finished_semaphores[context.current_frame];
    present_info.swapchainCount = 1;
    present_info.pSwapchains = &context.swapchain;
    present_info.pImageIndices = &image_index;
    auto present_ret = context->vkQueuePresentKHR(context.graphics_queue, &present_info);
    if (present_ret == VkResult::ErrorOutOfDateKHR || present_ret == VkResult::SuboptimalKHR) {
        return recreate_swapchain(context);
    }
    check_res(present_ret, "Failed to present");

    context.current_frame = (context.current_frame + 1) % context.image_count;
}

void destroy_device(RendererContext& context)
{
    for (auto& sem : context.available_semaphores) {
        context->vkDestroySemaphore(context, sem, nullptr);
    }
    for (auto& sem : context.finished_semaphores) {
        context->vkDestroySemaphore(context, sem, nullptr);
    }
    for (auto& fence : context.fences) {
        context->vkDestroyFence(context, fence, nullptr);
    }
    context->vkDestroyCommandPool(context, context.cmd_pool, nullptr);
    for (auto& framebuffer : context.framebuffers) {
        context->vkDestroyFramebuffer(context, framebuffer, nullptr);
    }
    context->vkDestroyPipeline(context, context.pipeline, nullptr);
    context->vkDestroyPipelineLayout(context, context.pipeline_layout, nullptr);
    context->vkDestroyRenderPass(context, context.render_pass, nullptr);
    for (auto& image_view : context.swapchain_image_views) {
        context->vkDestroyImageView(context, image_view, nullptr);
    }
    context->vkDestroySwapchainKHR(context, context.swapchain, nullptr);
    context->vkDestroyDevice(context, nullptr);
}

void destroy_renderer(RendererContext& context)
{
    vkDestroySurfaceKHR(context.instance, context.surface, nullptr);
    vkDestroyInstance(context.instance, nullptr);
    destroy_window_glfw(context.window);
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
    check_res(context->vkQueueWaitIdle(context.graphics_queue), "Couldn't wait to shut down");
    destroy_device(context);
    destroy_renderer(context);
    return 0;
}