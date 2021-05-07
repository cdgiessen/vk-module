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
// clang-format off
#pragma once
#include "vulkan.h"
#include <string>
const char * to_string(VkAttachmentLoadOp val);
const char * to_string(VkAttachmentStoreOp val);
const char * to_string(VkBlendFactor val);
const char * to_string(VkBlendOp val);
const char * to_string(VkBorderColor val);
const char * to_string(VkPipelineCacheHeaderVersion val);
const char * to_string(VkComponentSwizzle val);
const char * to_string(VkCommandBufferLevel val);
const char * to_string(VkCompareOp val);
const char * to_string(VkDescriptorType val);
const char * to_string(VkDynamicState val);
const char * to_string(VkPolygonMode val);
const char * to_string(VkFormat val);
const char * to_string(VkFrontFace val);
const char * to_string(VkImageLayout val);
const char * to_string(VkImageTiling val);
const char * to_string(VkImageType val);
const char * to_string(VkImageViewType val);
const char * to_string(VkSharingMode val);
const char * to_string(VkIndexType val);
const char * to_string(VkLogicOp val);
const char * to_string(VkPhysicalDeviceType val);
const char * to_string(VkPipelineBindPoint val);
const char * to_string(VkPrimitiveTopology val);
const char * to_string(VkQueryType val);
const char * to_string(VkSubpassContents val);
const char * to_string(VkResult val);
const char * to_string(VkStencilOp val);
const char * to_string(VkStructureType val);
const char * to_string(VkSystemAllocationScope val);
const char * to_string(VkInternalAllocationType val);
const char * to_string(VkSamplerAddressMode val);
const char * to_string(VkFilter val);
const char * to_string(VkSamplerMipmapMode val);
const char * to_string(VkVertexInputRate val);
const char * to_string(VkObjectType val);
const char * to_string(VkIndirectCommandsTokenTypeNV val);
const char * to_string(VkDescriptorUpdateTemplateType val);
const char * to_string(VkViewportCoordinateSwizzleNV val);
const char * to_string(VkDiscardRectangleModeEXT val);
const char * to_string(VkPointClippingBehavior val);
const char * to_string(VkCoverageModulationModeNV val);
const char * to_string(VkCoverageReductionModeNV val);
const char * to_string(VkValidationCacheHeaderVersionEXT val);
const char * to_string(VkShaderInfoTypeAMD val);
const char * to_string(VkQueueGlobalPriorityEXT val);
const char * to_string(VkTimeDomainEXT val);
const char * to_string(VkConservativeRasterizationModeEXT val);
const char * to_string(VkSemaphoreType val);
const char * to_string(VkBuildAccelerationStructureModeKHR val);
const char * to_string(VkCopyAccelerationStructureModeKHR val);
const char * to_string(VkAccelerationStructureTypeKHR val);
const char * to_string(VkGeometryTypeKHR val);
const char * to_string(VkRayTracingShaderGroupTypeKHR val);
const char * to_string(VkAccelerationStructureMemoryRequirementsTypeNV val);
const char * to_string(VkAccelerationStructureBuildTypeKHR val);
const char * to_string(VkAccelerationStructureCompatibilityKHR val);
const char * to_string(VkShaderGroupShaderKHR val);
const char * to_string(VkMemoryOverallocationBehaviorAMD val);
const char * to_string(VkScopeNV val);
const char * to_string(VkComponentTypeNV val);
const char * to_string(VkPerformanceCounterScopeKHR val);
const char * to_string(VkPerformanceCounterUnitKHR val);
const char * to_string(VkPerformanceCounterStorageKHR val);
const char * to_string(VkPerformanceConfigurationTypeINTEL val);
const char * to_string(VkQueryPoolSamplingModeINTEL val);
const char * to_string(VkPerformanceOverrideTypeINTEL val);
const char * to_string(VkPerformanceParameterTypeINTEL val);
const char * to_string(VkPerformanceValueTypeINTEL val);
const char * to_string(VkLineRasterizationModeEXT val);
const char * to_string(VkFragmentShadingRateNV val);
const char * to_string(VkFragmentShadingRateTypeNV val);
const char * to_string(VkColorSpaceKHR val);
const char * to_string(VkPresentModeKHR val);
const char * to_string(VkDebugReportObjectTypeEXT val);
const char * to_string(VkDeviceMemoryReportEventTypeEXT val);
const char * to_string(VkRasterizationOrderAMD val);
const char * to_string(VkValidationCheckEXT val);
const char * to_string(VkValidationFeatureEnableEXT val);
const char * to_string(VkValidationFeatureDisableEXT val);
const char * to_string(VkDisplayPowerStateEXT val);
const char * to_string(VkDeviceEventTypeEXT val);
const char * to_string(VkDisplayEventTypeEXT val);
const char * to_string(VkTessellationDomainOrigin val);
const char * to_string(VkSamplerYcbcrModelConversion val);
const char * to_string(VkSamplerYcbcrRange val);
const char * to_string(VkChromaLocation val);
const char * to_string(VkSamplerReductionMode val);
const char * to_string(VkBlendOverlapEXT val);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(VkFullScreenExclusiveEXT val);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(VkShaderFloatControlsIndependence val);
const char * to_string(VkFragmentShadingRateCombinerOpKHR val);
const char * to_string(VkVendorId val);
const char * to_string(VkDriverId val);
const char * to_string(VkShadingRatePaletteEntryNV val);
const char * to_string(VkCoarseSampleOrderTypeNV val);
const char * to_string(VkPipelineExecutableStatisticFormatKHR val);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkQueryResultStatusKHR val);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkPipelineCacheCreateFlagBits val);
std::string to_string(VkPipelineCacheCreateFlags flag);
const char * to_string(VkQueueFlagBits val);
std::string to_string(VkQueueFlags flag);
const char * to_string(VkCullModeFlagBits val);
std::string to_string(VkCullModeFlags flag);
const char * to_string(VkRenderPassCreateFlagBits val);
std::string to_string(VkRenderPassCreateFlags flag);
const char * to_string(VkDeviceQueueCreateFlagBits val);
std::string to_string(VkDeviceQueueCreateFlags flag);
const char * to_string(VkMemoryPropertyFlagBits val);
std::string to_string(VkMemoryPropertyFlags flag);
const char * to_string(VkMemoryHeapFlagBits val);
std::string to_string(VkMemoryHeapFlags flag);
const char * to_string(VkAccessFlagBits val);
std::string to_string(VkAccessFlags flag);
const char * to_string(VkBufferUsageFlagBits val);
std::string to_string(VkBufferUsageFlags flag);
const char * to_string(VkBufferCreateFlagBits val);
std::string to_string(VkBufferCreateFlags flag);
const char * to_string(VkShaderStageFlagBits val);
std::string to_string(VkShaderStageFlags flag);
const char * to_string(VkImageUsageFlagBits val);
std::string to_string(VkImageUsageFlags flag);
const char * to_string(VkImageCreateFlagBits val);
std::string to_string(VkImageCreateFlags flag);
const char * to_string(VkImageViewCreateFlagBits val);
std::string to_string(VkImageViewCreateFlags flag);
const char * to_string(VkSamplerCreateFlagBits val);
std::string to_string(VkSamplerCreateFlags flag);
const char * to_string(VkPipelineCreateFlagBits val);
std::string to_string(VkPipelineCreateFlags flag);
const char * to_string(VkPipelineShaderStageCreateFlagBits val);
std::string to_string(VkPipelineShaderStageCreateFlags flag);
const char * to_string(VkColorComponentFlagBits val);
std::string to_string(VkColorComponentFlags flag);
const char * to_string(VkFenceCreateFlagBits val);
std::string to_string(VkFenceCreateFlags flag);
const char * to_string(VkFormatFeatureFlagBits val);
std::string to_string(VkFormatFeatureFlags flag);
const char * to_string(VkQueryControlFlagBits val);
std::string to_string(VkQueryControlFlags flag);
const char * to_string(VkQueryResultFlagBits val);
std::string to_string(VkQueryResultFlags flag);
const char * to_string(VkCommandBufferUsageFlagBits val);
std::string to_string(VkCommandBufferUsageFlags flag);
const char * to_string(VkQueryPipelineStatisticFlagBits val);
std::string to_string(VkQueryPipelineStatisticFlags flag);
const char * to_string(VkImageAspectFlagBits val);
std::string to_string(VkImageAspectFlags flag);
const char * to_string(VkSparseImageFormatFlagBits val);
std::string to_string(VkSparseImageFormatFlags flag);
const char * to_string(VkSparseMemoryBindFlagBits val);
std::string to_string(VkSparseMemoryBindFlags flag);
const char * to_string(VkPipelineStageFlagBits val);
std::string to_string(VkPipelineStageFlags flag);
const char * to_string(VkCommandPoolCreateFlagBits val);
std::string to_string(VkCommandPoolCreateFlags flag);
const char * to_string(VkCommandPoolResetFlagBits val);
std::string to_string(VkCommandPoolResetFlags flag);
const char * to_string(VkCommandBufferResetFlagBits val);
std::string to_string(VkCommandBufferResetFlags flag);
const char * to_string(VkSampleCountFlagBits val);
std::string to_string(VkSampleCountFlags flag);
const char * to_string(VkAttachmentDescriptionFlagBits val);
std::string to_string(VkAttachmentDescriptionFlags flag);
const char * to_string(VkStencilFaceFlagBits val);
std::string to_string(VkStencilFaceFlags flag);
const char * to_string(VkDescriptorPoolCreateFlagBits val);
std::string to_string(VkDescriptorPoolCreateFlags flag);
const char * to_string(VkDependencyFlagBits val);
std::string to_string(VkDependencyFlags flag);
const char * to_string(VkSemaphoreWaitFlagBits val);
std::string to_string(VkSemaphoreWaitFlags flag);
const char * to_string(VkDisplayPlaneAlphaFlagBitsKHR val);
std::string to_string(VkDisplayPlaneAlphaFlagsKHR flag);
const char * to_string(VkCompositeAlphaFlagBitsKHR val);
std::string to_string(VkCompositeAlphaFlagsKHR flag);
const char * to_string(VkSurfaceTransformFlagBitsKHR val);
std::string to_string(VkSurfaceTransformFlagsKHR flag);
const char * to_string(VkDebugReportFlagBitsEXT val);
std::string to_string(VkDebugReportFlagsEXT flag);
const char * to_string(VkExternalMemoryHandleTypeFlagBitsNV val);
std::string to_string(VkExternalMemoryHandleTypeFlagsNV flag);
const char * to_string(VkExternalMemoryFeatureFlagBitsNV val);
std::string to_string(VkExternalMemoryFeatureFlagsNV flag);
const char * to_string(VkSubgroupFeatureFlagBits val);
std::string to_string(VkSubgroupFeatureFlags flag);
const char * to_string(VkIndirectCommandsLayoutUsageFlagBitsNV val);
std::string to_string(VkIndirectCommandsLayoutUsageFlagsNV flag);
const char * to_string(VkIndirectStateFlagBitsNV val);
std::string to_string(VkIndirectStateFlagsNV flag);
const char * to_string(VkPrivateDataSlotCreateFlagBitsEXT val);
std::string to_string(VkPrivateDataSlotCreateFlagsEXT flag);
const char * to_string(VkDescriptorSetLayoutCreateFlagBits val);
std::string to_string(VkDescriptorSetLayoutCreateFlags flag);
const char * to_string(VkExternalMemoryHandleTypeFlagBits val);
std::string to_string(VkExternalMemoryHandleTypeFlags flag);
const char * to_string(VkExternalMemoryFeatureFlagBits val);
std::string to_string(VkExternalMemoryFeatureFlags flag);
const char * to_string(VkExternalSemaphoreHandleTypeFlagBits val);
std::string to_string(VkExternalSemaphoreHandleTypeFlags flag);
const char * to_string(VkExternalSemaphoreFeatureFlagBits val);
std::string to_string(VkExternalSemaphoreFeatureFlags flag);
const char * to_string(VkSemaphoreImportFlagBits val);
std::string to_string(VkSemaphoreImportFlags flag);
const char * to_string(VkExternalFenceHandleTypeFlagBits val);
std::string to_string(VkExternalFenceHandleTypeFlags flag);
const char * to_string(VkExternalFenceFeatureFlagBits val);
std::string to_string(VkExternalFenceFeatureFlags flag);
const char * to_string(VkFenceImportFlagBits val);
std::string to_string(VkFenceImportFlags flag);
const char * to_string(VkSurfaceCounterFlagBitsEXT val);
std::string to_string(VkSurfaceCounterFlagsEXT flag);
const char * to_string(VkPeerMemoryFeatureFlagBits val);
std::string to_string(VkPeerMemoryFeatureFlags flag);
const char * to_string(VkMemoryAllocateFlagBits val);
std::string to_string(VkMemoryAllocateFlags flag);
const char * to_string(VkDeviceGroupPresentModeFlagBitsKHR val);
std::string to_string(VkDeviceGroupPresentModeFlagsKHR flag);
const char * to_string(VkSwapchainCreateFlagBitsKHR val);
std::string to_string(VkSwapchainCreateFlagsKHR flag);
const char * to_string(VkSubpassDescriptionFlagBits val);
std::string to_string(VkSubpassDescriptionFlags flag);
const char * to_string(VkDebugUtilsMessageSeverityFlagBitsEXT val);
std::string to_string(VkDebugUtilsMessageSeverityFlagsEXT flag);
const char * to_string(VkDebugUtilsMessageTypeFlagBitsEXT val);
std::string to_string(VkDebugUtilsMessageTypeFlagsEXT flag);
const char * to_string(VkDescriptorBindingFlagBits val);
std::string to_string(VkDescriptorBindingFlags flag);
const char * to_string(VkConditionalRenderingFlagBitsEXT val);
std::string to_string(VkConditionalRenderingFlagsEXT flag);
const char * to_string(VkResolveModeFlagBits val);
std::string to_string(VkResolveModeFlags flag);
const char * to_string(VkGeometryInstanceFlagBitsKHR val);
std::string to_string(VkGeometryInstanceFlagsKHR flag);
const char * to_string(VkGeometryFlagBitsKHR val);
std::string to_string(VkGeometryFlagsKHR flag);
const char * to_string(VkBuildAccelerationStructureFlagBitsKHR val);
std::string to_string(VkBuildAccelerationStructureFlagsKHR flag);
const char * to_string(VkAccelerationStructureCreateFlagBitsKHR val);
std::string to_string(VkAccelerationStructureCreateFlagsKHR flag);
const char * to_string(VkFramebufferCreateFlagBits val);
std::string to_string(VkFramebufferCreateFlags flag);
const char * to_string(VkDeviceDiagnosticsConfigFlagBitsNV val);
std::string to_string(VkDeviceDiagnosticsConfigFlagsNV flag);
const char * to_string(VkPipelineCreationFeedbackFlagBitsEXT val);
std::string to_string(VkPipelineCreationFeedbackFlagsEXT flag);
const char * to_string(VkPerformanceCounterDescriptionFlagBitsKHR val);
std::string to_string(VkPerformanceCounterDescriptionFlagsKHR flag);
const char * to_string(VkAcquireProfilingLockFlagBitsKHR val);
std::string to_string(VkAcquireProfilingLockFlagsKHR flag);
const char * to_string(VkShaderCorePropertiesFlagBitsAMD val);
std::string to_string(VkShaderCorePropertiesFlagsAMD flag);
const char * to_string(VkShaderModuleCreateFlagBits val);
std::string to_string(VkShaderModuleCreateFlags flag);
const char * to_string(VkPipelineCompilerControlFlagBitsAMD val);
std::string to_string(VkPipelineCompilerControlFlagsAMD flag);
const char * to_string(VkToolPurposeFlagBitsEXT val);
std::string to_string(VkToolPurposeFlagsEXT flag);
const char * to_string(VkAccessFlagBits2KHR val);
std::string to_string(VkAccessFlags2KHR flag);
const char * to_string(VkPipelineStageFlagBits2KHR val);
std::string to_string(VkPipelineStageFlags2KHR flag);
const char * to_string(VkSubmitFlagBitsKHR val);
std::string to_string(VkSubmitFlagsKHR flag);
const char * to_string(VkEventCreateFlagBits val);
std::string to_string(VkEventCreateFlags flag);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkVideoCodecOperationFlagBitsKHR val);
std::string to_string(VkVideoCodecOperationFlagsKHR flag);
const char * to_string(VkVideoChromaSubsamplingFlagBitsKHR val);
std::string to_string(VkVideoChromaSubsamplingFlagsKHR flag);
const char * to_string(VkVideoComponentBitDepthFlagBitsKHR val);
std::string to_string(VkVideoComponentBitDepthFlagsKHR flag);
const char * to_string(VkVideoCapabilitiesFlagBitsKHR val);
std::string to_string(VkVideoCapabilitiesFlagsKHR flag);
const char * to_string(VkVideoSessionCreateFlagBitsKHR val);
std::string to_string(VkVideoSessionCreateFlagsKHR flag);
const char * to_string(VkVideoCodingQualityPresetFlagBitsKHR val);
std::string to_string(VkVideoCodingQualityPresetFlagsKHR flag);
const char * to_string(VkVideoDecodeH264FieldLayoutFlagBitsEXT val);
std::string to_string(VkVideoDecodeH264FieldLayoutFlagsEXT flag);
const char * to_string(VkVideoCodingControlFlagBitsKHR val);
std::string to_string(VkVideoCodingControlFlagsKHR flag);
const char * to_string(VkVideoDecodeFlagBitsKHR val);
std::string to_string(VkVideoDecodeFlagsKHR flag);
const char * to_string(VkVideoEncodeFlagBitsKHR val);
std::string to_string(VkVideoEncodeFlagsKHR flag);
const char * to_string(VkVideoEncodeRateControlFlagBitsKHR val);
std::string to_string(VkVideoEncodeRateControlFlagsKHR flag);
const char * to_string(VkVideoEncodeRateControlModeFlagBitsKHR val);
std::string to_string(VkVideoEncodeRateControlModeFlagsKHR flag);
const char * to_string(VkVideoEncodeH264CapabilitiesFlagBitsEXT val);
std::string to_string(VkVideoEncodeH264CapabilitiesFlagsEXT flag);
const char * to_string(VkVideoEncodeH264InputModeFlagBitsEXT val);
std::string to_string(VkVideoEncodeH264InputModeFlagsEXT flag);
const char * to_string(VkVideoEncodeH264OutputModeFlagBitsEXT val);
std::string to_string(VkVideoEncodeH264OutputModeFlagsEXT flag);
const char * to_string(VkVideoEncodeH264CreateFlagBitsEXT val);
std::string to_string(VkVideoEncodeH264CreateFlagsEXT flag);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
#endif // defined(VK_USE_PLATFORM_GGP)
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)

// clang-format on
