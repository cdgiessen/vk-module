#pragma once
// clang-format off
#include "vkm_core.h"
#include <string>
namespace vk {
const char * to_string(Result val);
const char * to_string(PipelineCacheCreateFlagBits val);
std::string to_string(PipelineCacheCreateFlags flag);
const char * to_string(QueueFlagBits val);
std::string to_string(QueueFlags flag);
const char * to_string(CullModeFlagBits val);
std::string to_string(CullModeFlags flag);
const char * to_string(RenderPassCreateFlagBits val);
std::string to_string(RenderPassCreateFlags flag);
const char * to_string(DeviceQueueCreateFlagBits val);
std::string to_string(DeviceQueueCreateFlags flag);
const char * to_string(MemoryPropertyFlagBits val);
std::string to_string(MemoryPropertyFlags flag);
const char * to_string(MemoryHeapFlagBits val);
std::string to_string(MemoryHeapFlags flag);
const char * to_string(AccessFlagBits val);
std::string to_string(AccessFlags flag);
const char * to_string(BufferUsageFlagBits val);
std::string to_string(BufferUsageFlags flag);
const char * to_string(BufferCreateFlagBits val);
std::string to_string(BufferCreateFlags flag);
const char * to_string(ShaderStageFlagBits val);
std::string to_string(ShaderStageFlags flag);
const char * to_string(ImageUsageFlagBits val);
std::string to_string(ImageUsageFlags flag);
const char * to_string(ImageCreateFlagBits val);
std::string to_string(ImageCreateFlags flag);
const char * to_string(ImageViewCreateFlagBits val);
std::string to_string(ImageViewCreateFlags flag);
const char * to_string(SamplerCreateFlagBits val);
std::string to_string(SamplerCreateFlags flag);
const char * to_string(PipelineCreateFlagBits val);
std::string to_string(PipelineCreateFlags flag);
const char * to_string(PipelineShaderStageCreateFlagBits val);
std::string to_string(PipelineShaderStageCreateFlags flag);
const char * to_string(ColorComponentFlagBits val);
std::string to_string(ColorComponentFlags flag);
const char * to_string(FenceCreateFlagBits val);
std::string to_string(FenceCreateFlags flag);
const char * to_string(SemaphoreCreateFlagBits val);
std::string to_string(SemaphoreCreateFlags flag);
const char * to_string(FormatFeatureFlagBits val);
std::string to_string(FormatFeatureFlags flag);
const char * to_string(QueryControlFlagBits val);
std::string to_string(QueryControlFlags flag);
const char * to_string(QueryResultFlagBits val);
std::string to_string(QueryResultFlags flag);
const char * to_string(CommandBufferUsageFlagBits val);
std::string to_string(CommandBufferUsageFlags flag);
const char * to_string(QueryPipelineStatisticFlagBits val);
std::string to_string(QueryPipelineStatisticFlags flag);
const char * to_string(ImageAspectFlagBits val);
std::string to_string(ImageAspectFlags flag);
const char * to_string(SparseImageFormatFlagBits val);
std::string to_string(SparseImageFormatFlags flag);
const char * to_string(SparseMemoryBindFlagBits val);
std::string to_string(SparseMemoryBindFlags flag);
const char * to_string(PipelineStageFlagBits val);
std::string to_string(PipelineStageFlags flag);
const char * to_string(CommandPoolCreateFlagBits val);
std::string to_string(CommandPoolCreateFlags flag);
const char * to_string(CommandPoolResetFlagBits val);
std::string to_string(CommandPoolResetFlags flag);
const char * to_string(CommandBufferResetFlagBits val);
std::string to_string(CommandBufferResetFlags flag);
const char * to_string(SampleCountFlagBits val);
std::string to_string(SampleCountFlags flag);
const char * to_string(AttachmentDescriptionFlagBits val);
std::string to_string(AttachmentDescriptionFlags flag);
const char * to_string(StencilFaceFlagBits val);
std::string to_string(StencilFaceFlags flag);
const char * to_string(DescriptorPoolCreateFlagBits val);
std::string to_string(DescriptorPoolCreateFlags flag);
const char * to_string(DependencyFlagBits val);
std::string to_string(DependencyFlags flag);
const char * to_string(SemaphoreWaitFlagBits val);
std::string to_string(SemaphoreWaitFlags flag);
const char * to_string(DisplayPlaneAlphaFlagBitsKHR val);
std::string to_string(DisplayPlaneAlphaFlagsKHR flag);
const char * to_string(CompositeAlphaFlagBitsKHR val);
std::string to_string(CompositeAlphaFlagsKHR flag);
const char * to_string(SurfaceTransformFlagBitsKHR val);
std::string to_string(SurfaceTransformFlagsKHR flag);
const char * to_string(DebugReportFlagBitsEXT val);
std::string to_string(DebugReportFlagsEXT flag);
const char * to_string(ExternalMemoryHandleTypeFlagBitsNV val);
std::string to_string(ExternalMemoryHandleTypeFlagsNV flag);
const char * to_string(ExternalMemoryFeatureFlagBitsNV val);
std::string to_string(ExternalMemoryFeatureFlagsNV flag);
const char * to_string(SubgroupFeatureFlagBits val);
std::string to_string(SubgroupFeatureFlags flag);
const char * to_string(IndirectCommandsLayoutUsageFlagBitsNV val);
std::string to_string(IndirectCommandsLayoutUsageFlagsNV flag);
const char * to_string(IndirectStateFlagBitsNV val);
std::string to_string(IndirectStateFlagsNV flag);
const char * to_string(PrivateDataSlotCreateFlagBitsEXT val);
std::string to_string(PrivateDataSlotCreateFlagsEXT flag);
const char * to_string(DescriptorSetLayoutCreateFlagBits val);
std::string to_string(DescriptorSetLayoutCreateFlags flag);
const char * to_string(ExternalMemoryHandleTypeFlagBits val);
std::string to_string(ExternalMemoryHandleTypeFlags flag);
const char * to_string(ExternalMemoryFeatureFlagBits val);
std::string to_string(ExternalMemoryFeatureFlags flag);
const char * to_string(ExternalSemaphoreHandleTypeFlagBits val);
std::string to_string(ExternalSemaphoreHandleTypeFlags flag);
const char * to_string(ExternalSemaphoreFeatureFlagBits val);
std::string to_string(ExternalSemaphoreFeatureFlags flag);
const char * to_string(SemaphoreImportFlagBits val);
std::string to_string(SemaphoreImportFlags flag);
const char * to_string(ExternalFenceHandleTypeFlagBits val);
std::string to_string(ExternalFenceHandleTypeFlags flag);
const char * to_string(ExternalFenceFeatureFlagBits val);
std::string to_string(ExternalFenceFeatureFlags flag);
const char * to_string(FenceImportFlagBits val);
std::string to_string(FenceImportFlags flag);
const char * to_string(SurfaceCounterFlagBitsEXT val);
std::string to_string(SurfaceCounterFlagsEXT flag);
const char * to_string(PeerMemoryFeatureFlagBits val);
std::string to_string(PeerMemoryFeatureFlags flag);
const char * to_string(MemoryAllocateFlagBits val);
std::string to_string(MemoryAllocateFlags flag);
const char * to_string(DeviceGroupPresentModeFlagBitsKHR val);
std::string to_string(DeviceGroupPresentModeFlagsKHR flag);
const char * to_string(SwapchainCreateFlagBitsKHR val);
std::string to_string(SwapchainCreateFlagsKHR flag);
const char * to_string(SubpassDescriptionFlagBits val);
std::string to_string(SubpassDescriptionFlags flag);
const char * to_string(DebugUtilsMessageSeverityFlagBitsEXT val);
std::string to_string(DebugUtilsMessageSeverityFlagsEXT flag);
const char * to_string(DebugUtilsMessageTypeFlagBitsEXT val);
std::string to_string(DebugUtilsMessageTypeFlagsEXT flag);
const char * to_string(DescriptorBindingFlagBits val);
std::string to_string(DescriptorBindingFlags flag);
const char * to_string(ConditionalRenderingFlagBitsEXT val);
std::string to_string(ConditionalRenderingFlagsEXT flag);
const char * to_string(ResolveModeFlagBits val);
std::string to_string(ResolveModeFlags flag);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryInstanceFlagBitsKHR val);
std::string to_string(GeometryInstanceFlagsKHR flag);
const char * to_string(GeometryFlagBitsKHR val);
std::string to_string(GeometryFlagsKHR flag);
const char * to_string(BuildAccelerationStructureFlagBitsKHR val);
std::string to_string(BuildAccelerationStructureFlagsKHR flag);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(FramebufferCreateFlagBits val);
std::string to_string(FramebufferCreateFlags flag);
const char * to_string(DeviceDiagnosticsConfigFlagBitsNV val);
std::string to_string(DeviceDiagnosticsConfigFlagsNV flag);
const char * to_string(PipelineCreationFeedbackFlagBitsEXT val);
std::string to_string(PipelineCreationFeedbackFlagsEXT flag);
const char * to_string(PerformanceCounterDescriptionFlagBitsKHR val);
std::string to_string(PerformanceCounterDescriptionFlagsKHR flag);
const char * to_string(AcquireProfilingLockFlagBitsKHR val);
std::string to_string(AcquireProfilingLockFlagsKHR flag);
const char * to_string(ShaderCorePropertiesFlagBitsAMD val);
std::string to_string(ShaderCorePropertiesFlagsAMD flag);
const char * to_string(ShaderModuleCreateFlagBits val);
std::string to_string(ShaderModuleCreateFlags flag);
const char * to_string(PipelineCompilerControlFlagBitsAMD val);
std::string to_string(PipelineCompilerControlFlagsAMD flag);
const char * to_string(ToolPurposeFlagBitsEXT val);
std::string to_string(ToolPurposeFlagsEXT flag);
const char * to_string(QueryPoolCreateFlagBits val);
const char * to_string(PipelineLayoutCreateFlagBits val);
const char * to_string(PipelineDepthStencilStateCreateFlagBits val);
const char * to_string(PipelineDynamicStateCreateFlagBits val);
const char * to_string(PipelineColorBlendStateCreateFlagBits val);
const char * to_string(PipelineMultisampleStateCreateFlagBits val);
const char * to_string(PipelineRasterizationStateCreateFlagBits val);
const char * to_string(PipelineViewportStateCreateFlagBits val);
const char * to_string(PipelineTessellationStateCreateFlagBits val);
const char * to_string(PipelineInputAssemblyStateCreateFlagBits val);
const char * to_string(PipelineVertexInputStateCreateFlagBits val);
const char * to_string(BufferViewCreateFlagBits val);
const char * to_string(InstanceCreateFlagBits val);
const char * to_string(DeviceCreateFlagBits val);
const char * to_string(EventCreateFlagBits val);
const char * to_string(MemoryMapFlagBits val);
const char * to_string(DescriptorPoolResetFlagBits val);
const char * to_string(DescriptorUpdateTemplateCreateFlagBits val);
const char * to_string(DisplayModeCreateFlagBitsKHR val);
const char * to_string(DisplaySurfaceCreateFlagBitsKHR val);
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
const char * to_string(AndroidSurfaceCreateFlagBitsKHR val);
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
const char * to_string(ViSurfaceCreateFlagBitsNN val);
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
const char * to_string(WaylandSurfaceCreateFlagBitsKHR val);
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(Win32SurfaceCreateFlagBitsKHR val);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
const char * to_string(XlibSurfaceCreateFlagBitsKHR val);
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
const char * to_string(XcbSurfaceCreateFlagBitsKHR val);
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
const char * to_string(DirectFBSurfaceCreateFlagBitsEXT val);
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
const char * to_string(IOSSurfaceCreateFlagBitsMVK val);
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
const char * to_string(MacOSSurfaceCreateFlagBitsMVK val);
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
const char * to_string(MetalSurfaceCreateFlagBitsEXT val);
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
const char * to_string(ImagePipeSurfaceCreateFlagBitsFUCHSIA val);
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
const char * to_string(StreamDescriptorSurfaceCreateFlagBitsGGP val);
#endif // defined(VK_USE_PLATFORM_GGP)
const char * to_string(HeadlessSurfaceCreateFlagBitsEXT val);
const char * to_string(CommandPoolTrimFlagBits val);
const char * to_string(PipelineViewportSwizzleStateCreateFlagBitsNV val);
const char * to_string(PipelineDiscardRectangleStateCreateFlagBitsEXT val);
const char * to_string(PipelineCoverageToColorStateCreateFlagBitsNV val);
const char * to_string(PipelineCoverageModulationStateCreateFlagBitsNV val);
const char * to_string(PipelineCoverageReductionStateCreateFlagBitsNV val);
const char * to_string(ValidationCacheCreateFlagBitsEXT val);
const char * to_string(DebugUtilsMessengerCreateFlagBitsEXT val);
const char * to_string(DebugUtilsMessengerCallbackDataFlagBitsEXT val);
const char * to_string(DeviceMemoryReportFlagBitsEXT val);
const char * to_string(PipelineRasterizationConservativeStateCreateFlagBitsEXT val);
const char * to_string(PipelineRasterizationStateStreamCreateFlagBitsEXT val);
const char * to_string(PipelineRasterizationDepthClipStateCreateFlagBitsEXT val);
} // namespace vk
// clang-format on
