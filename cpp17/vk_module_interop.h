#pragma once
// clang-format off
#include <vulkan/vulkan.h>
#include "vk_module.h"
namespace vk {
constexpr VkAttachmentLoadOp to_c(AttachmentLoadOp value) { return static_cast<VkAttachmentLoadOp>(value);}
constexpr VkAttachmentStoreOp to_c(AttachmentStoreOp value) { return static_cast<VkAttachmentStoreOp>(value);}
constexpr VkBlendFactor to_c(BlendFactor value) { return static_cast<VkBlendFactor>(value);}
constexpr VkBlendOp to_c(BlendOp value) { return static_cast<VkBlendOp>(value);}
constexpr VkBorderColor to_c(BorderColor value) { return static_cast<VkBorderColor>(value);}
constexpr VkPipelineCacheHeaderVersion to_c(PipelineCacheHeaderVersion value) { return static_cast<VkPipelineCacheHeaderVersion>(value);}
constexpr VkComponentSwizzle to_c(ComponentSwizzle value) { return static_cast<VkComponentSwizzle>(value);}
constexpr VkCommandBufferLevel to_c(CommandBufferLevel value) { return static_cast<VkCommandBufferLevel>(value);}
constexpr VkCompareOp to_c(CompareOp value) { return static_cast<VkCompareOp>(value);}
constexpr VkDescriptorType to_c(DescriptorType value) { return static_cast<VkDescriptorType>(value);}
constexpr VkDynamicState to_c(DynamicState value) { return static_cast<VkDynamicState>(value);}
constexpr VkPolygonMode to_c(PolygonMode value) { return static_cast<VkPolygonMode>(value);}
constexpr VkFormat to_c(Format value) { return static_cast<VkFormat>(value);}
constexpr VkFrontFace to_c(FrontFace value) { return static_cast<VkFrontFace>(value);}
constexpr VkImageLayout to_c(ImageLayout value) { return static_cast<VkImageLayout>(value);}
constexpr VkImageTiling to_c(ImageTiling value) { return static_cast<VkImageTiling>(value);}
constexpr VkImageType to_c(ImageType value) { return static_cast<VkImageType>(value);}
constexpr VkImageViewType to_c(ImageViewType value) { return static_cast<VkImageViewType>(value);}
constexpr VkSharingMode to_c(SharingMode value) { return static_cast<VkSharingMode>(value);}
constexpr VkIndexType to_c(IndexType value) { return static_cast<VkIndexType>(value);}
constexpr VkLogicOp to_c(LogicOp value) { return static_cast<VkLogicOp>(value);}
constexpr VkPhysicalDeviceType to_c(PhysicalDeviceType value) { return static_cast<VkPhysicalDeviceType>(value);}
constexpr VkPipelineBindPoint to_c(PipelineBindPoint value) { return static_cast<VkPipelineBindPoint>(value);}
constexpr VkPrimitiveTopology to_c(PrimitiveTopology value) { return static_cast<VkPrimitiveTopology>(value);}
constexpr VkQueryType to_c(QueryType value) { return static_cast<VkQueryType>(value);}
constexpr VkSubpassContents to_c(SubpassContents value) { return static_cast<VkSubpassContents>(value);}
constexpr VkResult to_c(Result value) { return static_cast<VkResult>(value);}
constexpr VkStencilOp to_c(StencilOp value) { return static_cast<VkStencilOp>(value);}
constexpr VkStructureType to_c(StructureType value) { return static_cast<VkStructureType>(value);}
constexpr VkSystemAllocationScope to_c(SystemAllocationScope value) { return static_cast<VkSystemAllocationScope>(value);}
constexpr VkInternalAllocationType to_c(InternalAllocationType value) { return static_cast<VkInternalAllocationType>(value);}
constexpr VkSamplerAddressMode to_c(SamplerAddressMode value) { return static_cast<VkSamplerAddressMode>(value);}
constexpr VkFilter to_c(Filter value) { return static_cast<VkFilter>(value);}
constexpr VkSamplerMipmapMode to_c(SamplerMipmapMode value) { return static_cast<VkSamplerMipmapMode>(value);}
constexpr VkVertexInputRate to_c(VertexInputRate value) { return static_cast<VkVertexInputRate>(value);}
constexpr VkObjectType to_c(ObjectType value) { return static_cast<VkObjectType>(value);}
constexpr VkIndirectCommandsTokenTypeNV to_c(IndirectCommandsTokenTypeNV value) { return static_cast<VkIndirectCommandsTokenTypeNV>(value);}
constexpr VkDescriptorUpdateTemplateType to_c(DescriptorUpdateTemplateType value) { return static_cast<VkDescriptorUpdateTemplateType>(value);}
constexpr VkViewportCoordinateSwizzleNV to_c(ViewportCoordinateSwizzleNV value) { return static_cast<VkViewportCoordinateSwizzleNV>(value);}
constexpr VkDiscardRectangleModeEXT to_c(DiscardRectangleModeEXT value) { return static_cast<VkDiscardRectangleModeEXT>(value);}
constexpr VkPointClippingBehavior to_c(PointClippingBehavior value) { return static_cast<VkPointClippingBehavior>(value);}
constexpr VkCoverageModulationModeNV to_c(CoverageModulationModeNV value) { return static_cast<VkCoverageModulationModeNV>(value);}
constexpr VkCoverageReductionModeNV to_c(CoverageReductionModeNV value) { return static_cast<VkCoverageReductionModeNV>(value);}
constexpr VkValidationCacheHeaderVersionEXT to_c(ValidationCacheHeaderVersionEXT value) { return static_cast<VkValidationCacheHeaderVersionEXT>(value);}
constexpr VkShaderInfoTypeAMD to_c(ShaderInfoTypeAMD value) { return static_cast<VkShaderInfoTypeAMD>(value);}
constexpr VkQueueGlobalPriorityEXT to_c(QueueGlobalPriorityEXT value) { return static_cast<VkQueueGlobalPriorityEXT>(value);}
constexpr VkTimeDomainEXT to_c(TimeDomainEXT value) { return static_cast<VkTimeDomainEXT>(value);}
constexpr VkConservativeRasterizationModeEXT to_c(ConservativeRasterizationModeEXT value) { return static_cast<VkConservativeRasterizationModeEXT>(value);}
constexpr VkSemaphoreType to_c(SemaphoreType value) { return static_cast<VkSemaphoreType>(value);}
constexpr VkBuildAccelerationStructureModeKHR to_c(BuildAccelerationStructureModeKHR value) { return static_cast<VkBuildAccelerationStructureModeKHR>(value);}
constexpr VkCopyAccelerationStructureModeKHR to_c(CopyAccelerationStructureModeKHR value) { return static_cast<VkCopyAccelerationStructureModeKHR>(value);}
constexpr VkAccelerationStructureTypeKHR to_c(AccelerationStructureTypeKHR value) { return static_cast<VkAccelerationStructureTypeKHR>(value);}
constexpr VkGeometryTypeKHR to_c(GeometryTypeKHR value) { return static_cast<VkGeometryTypeKHR>(value);}
constexpr VkRayTracingShaderGroupTypeKHR to_c(RayTracingShaderGroupTypeKHR value) { return static_cast<VkRayTracingShaderGroupTypeKHR>(value);}
constexpr VkAccelerationStructureMemoryRequirementsTypeNV to_c(AccelerationStructureMemoryRequirementsTypeNV value) { return static_cast<VkAccelerationStructureMemoryRequirementsTypeNV>(value);}
constexpr VkAccelerationStructureBuildTypeKHR to_c(AccelerationStructureBuildTypeKHR value) { return static_cast<VkAccelerationStructureBuildTypeKHR>(value);}
constexpr VkAccelerationStructureCompatibilityKHR to_c(AccelerationStructureCompatibilityKHR value) { return static_cast<VkAccelerationStructureCompatibilityKHR>(value);}
constexpr VkShaderGroupShaderKHR to_c(ShaderGroupShaderKHR value) { return static_cast<VkShaderGroupShaderKHR>(value);}
constexpr VkMemoryOverallocationBehaviorAMD to_c(MemoryOverallocationBehaviorAMD value) { return static_cast<VkMemoryOverallocationBehaviorAMD>(value);}
constexpr VkScopeNV to_c(ScopeNV value) { return static_cast<VkScopeNV>(value);}
constexpr VkComponentTypeNV to_c(ComponentTypeNV value) { return static_cast<VkComponentTypeNV>(value);}
constexpr VkPerformanceCounterScopeKHR to_c(PerformanceCounterScopeKHR value) { return static_cast<VkPerformanceCounterScopeKHR>(value);}
constexpr VkPerformanceCounterUnitKHR to_c(PerformanceCounterUnitKHR value) { return static_cast<VkPerformanceCounterUnitKHR>(value);}
constexpr VkPerformanceCounterStorageKHR to_c(PerformanceCounterStorageKHR value) { return static_cast<VkPerformanceCounterStorageKHR>(value);}
constexpr VkPerformanceConfigurationTypeINTEL to_c(PerformanceConfigurationTypeINTEL value) { return static_cast<VkPerformanceConfigurationTypeINTEL>(value);}
constexpr VkQueryPoolSamplingModeINTEL to_c(QueryPoolSamplingModeINTEL value) { return static_cast<VkQueryPoolSamplingModeINTEL>(value);}
constexpr VkPerformanceOverrideTypeINTEL to_c(PerformanceOverrideTypeINTEL value) { return static_cast<VkPerformanceOverrideTypeINTEL>(value);}
constexpr VkPerformanceParameterTypeINTEL to_c(PerformanceParameterTypeINTEL value) { return static_cast<VkPerformanceParameterTypeINTEL>(value);}
constexpr VkPerformanceValueTypeINTEL to_c(PerformanceValueTypeINTEL value) { return static_cast<VkPerformanceValueTypeINTEL>(value);}
constexpr VkLineRasterizationModeEXT to_c(LineRasterizationModeEXT value) { return static_cast<VkLineRasterizationModeEXT>(value);}
constexpr VkFragmentShadingRateNV to_c(FragmentShadingRateNV value) { return static_cast<VkFragmentShadingRateNV>(value);}
constexpr VkFragmentShadingRateTypeNV to_c(FragmentShadingRateTypeNV value) { return static_cast<VkFragmentShadingRateTypeNV>(value);}
constexpr VkColorSpaceKHR to_c(ColorSpaceKHR value) { return static_cast<VkColorSpaceKHR>(value);}
constexpr VkPresentModeKHR to_c(PresentModeKHR value) { return static_cast<VkPresentModeKHR>(value);}
constexpr VkDebugReportObjectTypeEXT to_c(DebugReportObjectTypeEXT value) { return static_cast<VkDebugReportObjectTypeEXT>(value);}
constexpr VkDeviceMemoryReportEventTypeEXT to_c(DeviceMemoryReportEventTypeEXT value) { return static_cast<VkDeviceMemoryReportEventTypeEXT>(value);}
constexpr VkRasterizationOrderAMD to_c(RasterizationOrderAMD value) { return static_cast<VkRasterizationOrderAMD>(value);}
constexpr VkValidationCheckEXT to_c(ValidationCheckEXT value) { return static_cast<VkValidationCheckEXT>(value);}
constexpr VkValidationFeatureEnableEXT to_c(ValidationFeatureEnableEXT value) { return static_cast<VkValidationFeatureEnableEXT>(value);}
constexpr VkValidationFeatureDisableEXT to_c(ValidationFeatureDisableEXT value) { return static_cast<VkValidationFeatureDisableEXT>(value);}
constexpr VkDisplayPowerStateEXT to_c(DisplayPowerStateEXT value) { return static_cast<VkDisplayPowerStateEXT>(value);}
constexpr VkDeviceEventTypeEXT to_c(DeviceEventTypeEXT value) { return static_cast<VkDeviceEventTypeEXT>(value);}
constexpr VkDisplayEventTypeEXT to_c(DisplayEventTypeEXT value) { return static_cast<VkDisplayEventTypeEXT>(value);}
constexpr VkTessellationDomainOrigin to_c(TessellationDomainOrigin value) { return static_cast<VkTessellationDomainOrigin>(value);}
constexpr VkSamplerYcbcrModelConversion to_c(SamplerYcbcrModelConversion value) { return static_cast<VkSamplerYcbcrModelConversion>(value);}
constexpr VkSamplerYcbcrRange to_c(SamplerYcbcrRange value) { return static_cast<VkSamplerYcbcrRange>(value);}
constexpr VkChromaLocation to_c(ChromaLocation value) { return static_cast<VkChromaLocation>(value);}
constexpr VkSamplerReductionMode to_c(SamplerReductionMode value) { return static_cast<VkSamplerReductionMode>(value);}
constexpr VkBlendOverlapEXT to_c(BlendOverlapEXT value) { return static_cast<VkBlendOverlapEXT>(value);}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkFullScreenExclusiveEXT to_c(FullScreenExclusiveEXT value) { return static_cast<VkFullScreenExclusiveEXT>(value);}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkShaderFloatControlsIndependence to_c(ShaderFloatControlsIndependence value) { return static_cast<VkShaderFloatControlsIndependence>(value);}
constexpr VkFragmentShadingRateCombinerOpKHR to_c(FragmentShadingRateCombinerOpKHR value) { return static_cast<VkFragmentShadingRateCombinerOpKHR>(value);}
constexpr VkVendorId to_c(VendorId value) { return static_cast<VkVendorId>(value);}
constexpr VkDriverId to_c(DriverId value) { return static_cast<VkDriverId>(value);}
constexpr VkShadingRatePaletteEntryNV to_c(ShadingRatePaletteEntryNV value) { return static_cast<VkShadingRatePaletteEntryNV>(value);}
constexpr VkCoarseSampleOrderTypeNV to_c(CoarseSampleOrderTypeNV value) { return static_cast<VkCoarseSampleOrderTypeNV>(value);}
constexpr VkPipelineExecutableStatisticFormatKHR to_c(PipelineExecutableStatisticFormatKHR value) { return static_cast<VkPipelineExecutableStatisticFormatKHR>(value);}
constexpr VkPipelineCacheCreateFlagBits to_c(PipelineCacheCreateFlagBits value) { return static_cast<VkPipelineCacheCreateFlagBits>(value);}
constexpr VkQueueFlagBits to_c(QueueFlagBits value) { return static_cast<VkQueueFlagBits>(value);}
constexpr VkCullModeFlagBits to_c(CullModeFlagBits value) { return static_cast<VkCullModeFlagBits>(value);}
constexpr VkRenderPassCreateFlagBits to_c(RenderPassCreateFlagBits value) { return static_cast<VkRenderPassCreateFlagBits>(value);}
constexpr VkDeviceQueueCreateFlagBits to_c(DeviceQueueCreateFlagBits value) { return static_cast<VkDeviceQueueCreateFlagBits>(value);}
constexpr VkMemoryPropertyFlagBits to_c(MemoryPropertyFlagBits value) { return static_cast<VkMemoryPropertyFlagBits>(value);}
constexpr VkMemoryHeapFlagBits to_c(MemoryHeapFlagBits value) { return static_cast<VkMemoryHeapFlagBits>(value);}
constexpr VkAccessFlagBits to_c(AccessFlagBits value) { return static_cast<VkAccessFlagBits>(value);}
constexpr VkBufferUsageFlagBits to_c(BufferUsageFlagBits value) { return static_cast<VkBufferUsageFlagBits>(value);}
constexpr VkBufferCreateFlagBits to_c(BufferCreateFlagBits value) { return static_cast<VkBufferCreateFlagBits>(value);}
constexpr VkShaderStageFlagBits to_c(ShaderStageFlagBits value) { return static_cast<VkShaderStageFlagBits>(value);}
constexpr VkImageUsageFlagBits to_c(ImageUsageFlagBits value) { return static_cast<VkImageUsageFlagBits>(value);}
constexpr VkImageCreateFlagBits to_c(ImageCreateFlagBits value) { return static_cast<VkImageCreateFlagBits>(value);}
constexpr VkImageViewCreateFlagBits to_c(ImageViewCreateFlagBits value) { return static_cast<VkImageViewCreateFlagBits>(value);}
constexpr VkSamplerCreateFlagBits to_c(SamplerCreateFlagBits value) { return static_cast<VkSamplerCreateFlagBits>(value);}
constexpr VkPipelineCreateFlagBits to_c(PipelineCreateFlagBits value) { return static_cast<VkPipelineCreateFlagBits>(value);}
constexpr VkPipelineShaderStageCreateFlagBits to_c(PipelineShaderStageCreateFlagBits value) { return static_cast<VkPipelineShaderStageCreateFlagBits>(value);}
constexpr VkColorComponentFlagBits to_c(ColorComponentFlagBits value) { return static_cast<VkColorComponentFlagBits>(value);}
constexpr VkFenceCreateFlagBits to_c(FenceCreateFlagBits value) { return static_cast<VkFenceCreateFlagBits>(value);}
constexpr VkFormatFeatureFlagBits to_c(FormatFeatureFlagBits value) { return static_cast<VkFormatFeatureFlagBits>(value);}
constexpr VkQueryControlFlagBits to_c(QueryControlFlagBits value) { return static_cast<VkQueryControlFlagBits>(value);}
constexpr VkQueryResultFlagBits to_c(QueryResultFlagBits value) { return static_cast<VkQueryResultFlagBits>(value);}
constexpr VkCommandBufferUsageFlagBits to_c(CommandBufferUsageFlagBits value) { return static_cast<VkCommandBufferUsageFlagBits>(value);}
constexpr VkQueryPipelineStatisticFlagBits to_c(QueryPipelineStatisticFlagBits value) { return static_cast<VkQueryPipelineStatisticFlagBits>(value);}
constexpr VkImageAspectFlagBits to_c(ImageAspectFlagBits value) { return static_cast<VkImageAspectFlagBits>(value);}
constexpr VkSparseImageFormatFlagBits to_c(SparseImageFormatFlagBits value) { return static_cast<VkSparseImageFormatFlagBits>(value);}
constexpr VkSparseMemoryBindFlagBits to_c(SparseMemoryBindFlagBits value) { return static_cast<VkSparseMemoryBindFlagBits>(value);}
constexpr VkPipelineStageFlagBits to_c(PipelineStageFlagBits value) { return static_cast<VkPipelineStageFlagBits>(value);}
constexpr VkCommandPoolCreateFlagBits to_c(CommandPoolCreateFlagBits value) { return static_cast<VkCommandPoolCreateFlagBits>(value);}
constexpr VkCommandPoolResetFlagBits to_c(CommandPoolResetFlagBits value) { return static_cast<VkCommandPoolResetFlagBits>(value);}
constexpr VkCommandBufferResetFlagBits to_c(CommandBufferResetFlagBits value) { return static_cast<VkCommandBufferResetFlagBits>(value);}
constexpr VkSampleCountFlagBits to_c(SampleCountFlagBits value) { return static_cast<VkSampleCountFlagBits>(value);}
constexpr VkAttachmentDescriptionFlagBits to_c(AttachmentDescriptionFlagBits value) { return static_cast<VkAttachmentDescriptionFlagBits>(value);}
constexpr VkStencilFaceFlagBits to_c(StencilFaceFlagBits value) { return static_cast<VkStencilFaceFlagBits>(value);}
constexpr VkDescriptorPoolCreateFlagBits to_c(DescriptorPoolCreateFlagBits value) { return static_cast<VkDescriptorPoolCreateFlagBits>(value);}
constexpr VkDependencyFlagBits to_c(DependencyFlagBits value) { return static_cast<VkDependencyFlagBits>(value);}
constexpr VkSemaphoreWaitFlagBits to_c(SemaphoreWaitFlagBits value) { return static_cast<VkSemaphoreWaitFlagBits>(value);}
constexpr VkDisplayPlaneAlphaFlagBitsKHR to_c(DisplayPlaneAlphaFlagBitsKHR value) { return static_cast<VkDisplayPlaneAlphaFlagBitsKHR>(value);}
constexpr VkCompositeAlphaFlagBitsKHR to_c(CompositeAlphaFlagBitsKHR value) { return static_cast<VkCompositeAlphaFlagBitsKHR>(value);}
constexpr VkSurfaceTransformFlagBitsKHR to_c(SurfaceTransformFlagBitsKHR value) { return static_cast<VkSurfaceTransformFlagBitsKHR>(value);}
constexpr VkDebugReportFlagBitsEXT to_c(DebugReportFlagBitsEXT value) { return static_cast<VkDebugReportFlagBitsEXT>(value);}
constexpr VkExternalMemoryHandleTypeFlagBitsNV to_c(ExternalMemoryHandleTypeFlagBitsNV value) { return static_cast<VkExternalMemoryHandleTypeFlagBitsNV>(value);}
constexpr VkExternalMemoryFeatureFlagBitsNV to_c(ExternalMemoryFeatureFlagBitsNV value) { return static_cast<VkExternalMemoryFeatureFlagBitsNV>(value);}
constexpr VkSubgroupFeatureFlagBits to_c(SubgroupFeatureFlagBits value) { return static_cast<VkSubgroupFeatureFlagBits>(value);}
constexpr VkIndirectCommandsLayoutUsageFlagBitsNV to_c(IndirectCommandsLayoutUsageFlagBitsNV value) { return static_cast<VkIndirectCommandsLayoutUsageFlagBitsNV>(value);}
constexpr VkIndirectStateFlagBitsNV to_c(IndirectStateFlagBitsNV value) { return static_cast<VkIndirectStateFlagBitsNV>(value);}
constexpr VkPrivateDataSlotCreateFlagBitsEXT to_c(PrivateDataSlotCreateFlagBitsEXT value) { return static_cast<VkPrivateDataSlotCreateFlagBitsEXT>(value);}
constexpr VkDescriptorSetLayoutCreateFlagBits to_c(DescriptorSetLayoutCreateFlagBits value) { return static_cast<VkDescriptorSetLayoutCreateFlagBits>(value);}
constexpr VkExternalMemoryHandleTypeFlagBits to_c(ExternalMemoryHandleTypeFlagBits value) { return static_cast<VkExternalMemoryHandleTypeFlagBits>(value);}
constexpr VkExternalMemoryFeatureFlagBits to_c(ExternalMemoryFeatureFlagBits value) { return static_cast<VkExternalMemoryFeatureFlagBits>(value);}
constexpr VkExternalSemaphoreHandleTypeFlagBits to_c(ExternalSemaphoreHandleTypeFlagBits value) { return static_cast<VkExternalSemaphoreHandleTypeFlagBits>(value);}
constexpr VkExternalSemaphoreFeatureFlagBits to_c(ExternalSemaphoreFeatureFlagBits value) { return static_cast<VkExternalSemaphoreFeatureFlagBits>(value);}
constexpr VkSemaphoreImportFlagBits to_c(SemaphoreImportFlagBits value) { return static_cast<VkSemaphoreImportFlagBits>(value);}
constexpr VkExternalFenceHandleTypeFlagBits to_c(ExternalFenceHandleTypeFlagBits value) { return static_cast<VkExternalFenceHandleTypeFlagBits>(value);}
constexpr VkExternalFenceFeatureFlagBits to_c(ExternalFenceFeatureFlagBits value) { return static_cast<VkExternalFenceFeatureFlagBits>(value);}
constexpr VkFenceImportFlagBits to_c(FenceImportFlagBits value) { return static_cast<VkFenceImportFlagBits>(value);}
constexpr VkSurfaceCounterFlagBitsEXT to_c(SurfaceCounterFlagBitsEXT value) { return static_cast<VkSurfaceCounterFlagBitsEXT>(value);}
constexpr VkPeerMemoryFeatureFlagBits to_c(PeerMemoryFeatureFlagBits value) { return static_cast<VkPeerMemoryFeatureFlagBits>(value);}
constexpr VkMemoryAllocateFlagBits to_c(MemoryAllocateFlagBits value) { return static_cast<VkMemoryAllocateFlagBits>(value);}
constexpr VkDeviceGroupPresentModeFlagBitsKHR to_c(DeviceGroupPresentModeFlagBitsKHR value) { return static_cast<VkDeviceGroupPresentModeFlagBitsKHR>(value);}
constexpr VkSwapchainCreateFlagBitsKHR to_c(SwapchainCreateFlagBitsKHR value) { return static_cast<VkSwapchainCreateFlagBitsKHR>(value);}
constexpr VkSubpassDescriptionFlagBits to_c(SubpassDescriptionFlagBits value) { return static_cast<VkSubpassDescriptionFlagBits>(value);}
constexpr VkDebugUtilsMessageSeverityFlagBitsEXT to_c(DebugUtilsMessageSeverityFlagBitsEXT value) { return static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(value);}
constexpr VkDebugUtilsMessageTypeFlagBitsEXT to_c(DebugUtilsMessageTypeFlagBitsEXT value) { return static_cast<VkDebugUtilsMessageTypeFlagBitsEXT>(value);}
constexpr VkDescriptorBindingFlagBits to_c(DescriptorBindingFlagBits value) { return static_cast<VkDescriptorBindingFlagBits>(value);}
constexpr VkConditionalRenderingFlagBitsEXT to_c(ConditionalRenderingFlagBitsEXT value) { return static_cast<VkConditionalRenderingFlagBitsEXT>(value);}
constexpr VkResolveModeFlagBits to_c(ResolveModeFlagBits value) { return static_cast<VkResolveModeFlagBits>(value);}
constexpr VkGeometryInstanceFlagBitsKHR to_c(GeometryInstanceFlagBitsKHR value) { return static_cast<VkGeometryInstanceFlagBitsKHR>(value);}
constexpr VkGeometryFlagBitsKHR to_c(GeometryFlagBitsKHR value) { return static_cast<VkGeometryFlagBitsKHR>(value);}
constexpr VkBuildAccelerationStructureFlagBitsKHR to_c(BuildAccelerationStructureFlagBitsKHR value) { return static_cast<VkBuildAccelerationStructureFlagBitsKHR>(value);}
constexpr VkAccelerationStructureCreateFlagBitsKHR to_c(AccelerationStructureCreateFlagBitsKHR value) { return static_cast<VkAccelerationStructureCreateFlagBitsKHR>(value);}
constexpr VkFramebufferCreateFlagBits to_c(FramebufferCreateFlagBits value) { return static_cast<VkFramebufferCreateFlagBits>(value);}
constexpr VkDeviceDiagnosticsConfigFlagBitsNV to_c(DeviceDiagnosticsConfigFlagBitsNV value) { return static_cast<VkDeviceDiagnosticsConfigFlagBitsNV>(value);}
constexpr VkPipelineCreationFeedbackFlagBitsEXT to_c(PipelineCreationFeedbackFlagBitsEXT value) { return static_cast<VkPipelineCreationFeedbackFlagBitsEXT>(value);}
constexpr VkPerformanceCounterDescriptionFlagBitsKHR to_c(PerformanceCounterDescriptionFlagBitsKHR value) { return static_cast<VkPerformanceCounterDescriptionFlagBitsKHR>(value);}
constexpr VkAcquireProfilingLockFlagBitsKHR to_c(AcquireProfilingLockFlagBitsKHR value) { return static_cast<VkAcquireProfilingLockFlagBitsKHR>(value);}
constexpr VkShaderCorePropertiesFlagBitsAMD to_c(ShaderCorePropertiesFlagBitsAMD value) { return static_cast<VkShaderCorePropertiesFlagBitsAMD>(value);}
constexpr VkShaderModuleCreateFlagBits to_c(ShaderModuleCreateFlagBits value) { return static_cast<VkShaderModuleCreateFlagBits>(value);}
constexpr VkPipelineCompilerControlFlagBitsAMD to_c(PipelineCompilerControlFlagBitsAMD value) { return static_cast<VkPipelineCompilerControlFlagBitsAMD>(value);}
constexpr VkToolPurposeFlagBitsEXT to_c(ToolPurposeFlagBitsEXT value) { return static_cast<VkToolPurposeFlagBitsEXT>(value);}
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
constexpr VkFramebufferCreateFlags to_c(FramebufferCreateFlags value) { return static_cast<VkFramebufferCreateFlags>(value);}
constexpr VkQueryPoolCreateFlags to_c(QueryPoolCreateFlags value) { return static_cast<VkQueryPoolCreateFlags>(value);}
constexpr VkRenderPassCreateFlags to_c(RenderPassCreateFlags value) { return static_cast<VkRenderPassCreateFlags>(value);}
constexpr VkSamplerCreateFlags to_c(SamplerCreateFlags value) { return static_cast<VkSamplerCreateFlags>(value);}
constexpr VkPipelineLayoutCreateFlags to_c(PipelineLayoutCreateFlags value) { return static_cast<VkPipelineLayoutCreateFlags>(value);}
constexpr VkPipelineCacheCreateFlags to_c(PipelineCacheCreateFlags value) { return static_cast<VkPipelineCacheCreateFlags>(value);}
constexpr VkPipelineDepthStencilStateCreateFlags to_c(PipelineDepthStencilStateCreateFlags value) { return static_cast<VkPipelineDepthStencilStateCreateFlags>(value);}
constexpr VkPipelineDynamicStateCreateFlags to_c(PipelineDynamicStateCreateFlags value) { return static_cast<VkPipelineDynamicStateCreateFlags>(value);}
constexpr VkPipelineColorBlendStateCreateFlags to_c(PipelineColorBlendStateCreateFlags value) { return static_cast<VkPipelineColorBlendStateCreateFlags>(value);}
constexpr VkPipelineMultisampleStateCreateFlags to_c(PipelineMultisampleStateCreateFlags value) { return static_cast<VkPipelineMultisampleStateCreateFlags>(value);}
constexpr VkPipelineRasterizationStateCreateFlags to_c(PipelineRasterizationStateCreateFlags value) { return static_cast<VkPipelineRasterizationStateCreateFlags>(value);}
constexpr VkPipelineViewportStateCreateFlags to_c(PipelineViewportStateCreateFlags value) { return static_cast<VkPipelineViewportStateCreateFlags>(value);}
constexpr VkPipelineTessellationStateCreateFlags to_c(PipelineTessellationStateCreateFlags value) { return static_cast<VkPipelineTessellationStateCreateFlags>(value);}
constexpr VkPipelineInputAssemblyStateCreateFlags to_c(PipelineInputAssemblyStateCreateFlags value) { return static_cast<VkPipelineInputAssemblyStateCreateFlags>(value);}
constexpr VkPipelineVertexInputStateCreateFlags to_c(PipelineVertexInputStateCreateFlags value) { return static_cast<VkPipelineVertexInputStateCreateFlags>(value);}
constexpr VkPipelineShaderStageCreateFlags to_c(PipelineShaderStageCreateFlags value) { return static_cast<VkPipelineShaderStageCreateFlags>(value);}
constexpr VkDescriptorSetLayoutCreateFlags to_c(DescriptorSetLayoutCreateFlags value) { return static_cast<VkDescriptorSetLayoutCreateFlags>(value);}
constexpr VkBufferViewCreateFlags to_c(BufferViewCreateFlags value) { return static_cast<VkBufferViewCreateFlags>(value);}
constexpr VkInstanceCreateFlags to_c(InstanceCreateFlags value) { return static_cast<VkInstanceCreateFlags>(value);}
constexpr VkDeviceCreateFlags to_c(DeviceCreateFlags value) { return static_cast<VkDeviceCreateFlags>(value);}
constexpr VkDeviceQueueCreateFlags to_c(DeviceQueueCreateFlags value) { return static_cast<VkDeviceQueueCreateFlags>(value);}
constexpr VkQueueFlags to_c(QueueFlags value) { return static_cast<VkQueueFlags>(value);}
constexpr VkMemoryPropertyFlags to_c(MemoryPropertyFlags value) { return static_cast<VkMemoryPropertyFlags>(value);}
constexpr VkMemoryHeapFlags to_c(MemoryHeapFlags value) { return static_cast<VkMemoryHeapFlags>(value);}
constexpr VkAccessFlags to_c(AccessFlags value) { return static_cast<VkAccessFlags>(value);}
constexpr VkBufferUsageFlags to_c(BufferUsageFlags value) { return static_cast<VkBufferUsageFlags>(value);}
constexpr VkBufferCreateFlags to_c(BufferCreateFlags value) { return static_cast<VkBufferCreateFlags>(value);}
constexpr VkShaderStageFlags to_c(ShaderStageFlags value) { return static_cast<VkShaderStageFlags>(value);}
constexpr VkImageUsageFlags to_c(ImageUsageFlags value) { return static_cast<VkImageUsageFlags>(value);}
constexpr VkImageCreateFlags to_c(ImageCreateFlags value) { return static_cast<VkImageCreateFlags>(value);}
constexpr VkImageViewCreateFlags to_c(ImageViewCreateFlags value) { return static_cast<VkImageViewCreateFlags>(value);}
constexpr VkPipelineCreateFlags to_c(PipelineCreateFlags value) { return static_cast<VkPipelineCreateFlags>(value);}
constexpr VkColorComponentFlags to_c(ColorComponentFlags value) { return static_cast<VkColorComponentFlags>(value);}
constexpr VkFenceCreateFlags to_c(FenceCreateFlags value) { return static_cast<VkFenceCreateFlags>(value);}
constexpr VkSemaphoreCreateFlags to_c(SemaphoreCreateFlags value) { return static_cast<VkSemaphoreCreateFlags>(value);}
constexpr VkFormatFeatureFlags to_c(FormatFeatureFlags value) { return static_cast<VkFormatFeatureFlags>(value);}
constexpr VkQueryControlFlags to_c(QueryControlFlags value) { return static_cast<VkQueryControlFlags>(value);}
constexpr VkQueryResultFlags to_c(QueryResultFlags value) { return static_cast<VkQueryResultFlags>(value);}
constexpr VkShaderModuleCreateFlags to_c(ShaderModuleCreateFlags value) { return static_cast<VkShaderModuleCreateFlags>(value);}
constexpr VkEventCreateFlags to_c(EventCreateFlags value) { return static_cast<VkEventCreateFlags>(value);}
constexpr VkCommandPoolCreateFlags to_c(CommandPoolCreateFlags value) { return static_cast<VkCommandPoolCreateFlags>(value);}
constexpr VkCommandPoolResetFlags to_c(CommandPoolResetFlags value) { return static_cast<VkCommandPoolResetFlags>(value);}
constexpr VkCommandBufferResetFlags to_c(CommandBufferResetFlags value) { return static_cast<VkCommandBufferResetFlags>(value);}
constexpr VkCommandBufferUsageFlags to_c(CommandBufferUsageFlags value) { return static_cast<VkCommandBufferUsageFlags>(value);}
constexpr VkQueryPipelineStatisticFlags to_c(QueryPipelineStatisticFlags value) { return static_cast<VkQueryPipelineStatisticFlags>(value);}
constexpr VkMemoryMapFlags to_c(MemoryMapFlags value) { return static_cast<VkMemoryMapFlags>(value);}
constexpr VkImageAspectFlags to_c(ImageAspectFlags value) { return static_cast<VkImageAspectFlags>(value);}
constexpr VkSparseMemoryBindFlags to_c(SparseMemoryBindFlags value) { return static_cast<VkSparseMemoryBindFlags>(value);}
constexpr VkSparseImageFormatFlags to_c(SparseImageFormatFlags value) { return static_cast<VkSparseImageFormatFlags>(value);}
constexpr VkSubpassDescriptionFlags to_c(SubpassDescriptionFlags value) { return static_cast<VkSubpassDescriptionFlags>(value);}
constexpr VkPipelineStageFlags to_c(PipelineStageFlags value) { return static_cast<VkPipelineStageFlags>(value);}
constexpr VkSampleCountFlags to_c(SampleCountFlags value) { return static_cast<VkSampleCountFlags>(value);}
constexpr VkAttachmentDescriptionFlags to_c(AttachmentDescriptionFlags value) { return static_cast<VkAttachmentDescriptionFlags>(value);}
constexpr VkStencilFaceFlags to_c(StencilFaceFlags value) { return static_cast<VkStencilFaceFlags>(value);}
constexpr VkCullModeFlags to_c(CullModeFlags value) { return static_cast<VkCullModeFlags>(value);}
constexpr VkDescriptorPoolCreateFlags to_c(DescriptorPoolCreateFlags value) { return static_cast<VkDescriptorPoolCreateFlags>(value);}
constexpr VkDescriptorPoolResetFlags to_c(DescriptorPoolResetFlags value) { return static_cast<VkDescriptorPoolResetFlags>(value);}
constexpr VkDependencyFlags to_c(DependencyFlags value) { return static_cast<VkDependencyFlags>(value);}
constexpr VkSubgroupFeatureFlags to_c(SubgroupFeatureFlags value) { return static_cast<VkSubgroupFeatureFlags>(value);}
constexpr VkIndirectCommandsLayoutUsageFlagsNV to_c(IndirectCommandsLayoutUsageFlagsNV value) { return static_cast<VkIndirectCommandsLayoutUsageFlagsNV>(value);}
constexpr VkIndirectStateFlagsNV to_c(IndirectStateFlagsNV value) { return static_cast<VkIndirectStateFlagsNV>(value);}
constexpr VkGeometryFlagsKHR to_c(GeometryFlagsKHR value) { return static_cast<VkGeometryFlagsKHR>(value);}
constexpr VkGeometryInstanceFlagsKHR to_c(GeometryInstanceFlagsKHR value) { return static_cast<VkGeometryInstanceFlagsKHR>(value);}
constexpr VkBuildAccelerationStructureFlagsKHR to_c(BuildAccelerationStructureFlagsKHR value) { return static_cast<VkBuildAccelerationStructureFlagsKHR>(value);}
constexpr VkPrivateDataSlotCreateFlagsEXT to_c(PrivateDataSlotCreateFlagsEXT value) { return static_cast<VkPrivateDataSlotCreateFlagsEXT>(value);}
constexpr VkAccelerationStructureCreateFlagsKHR to_c(AccelerationStructureCreateFlagsKHR value) { return static_cast<VkAccelerationStructureCreateFlagsKHR>(value);}
constexpr VkDescriptorUpdateTemplateCreateFlags to_c(DescriptorUpdateTemplateCreateFlags value) { return static_cast<VkDescriptorUpdateTemplateCreateFlags>(value);}
constexpr VkPipelineCreationFeedbackFlagsEXT to_c(PipelineCreationFeedbackFlagsEXT value) { return static_cast<VkPipelineCreationFeedbackFlagsEXT>(value);}
constexpr VkPerformanceCounterDescriptionFlagsKHR to_c(PerformanceCounterDescriptionFlagsKHR value) { return static_cast<VkPerformanceCounterDescriptionFlagsKHR>(value);}
constexpr VkAcquireProfilingLockFlagsKHR to_c(AcquireProfilingLockFlagsKHR value) { return static_cast<VkAcquireProfilingLockFlagsKHR>(value);}
constexpr VkSemaphoreWaitFlags to_c(SemaphoreWaitFlags value) { return static_cast<VkSemaphoreWaitFlags>(value);}
constexpr VkPipelineCompilerControlFlagsAMD to_c(PipelineCompilerControlFlagsAMD value) { return static_cast<VkPipelineCompilerControlFlagsAMD>(value);}
constexpr VkShaderCorePropertiesFlagsAMD to_c(ShaderCorePropertiesFlagsAMD value) { return static_cast<VkShaderCorePropertiesFlagsAMD>(value);}
constexpr VkDeviceDiagnosticsConfigFlagsNV to_c(DeviceDiagnosticsConfigFlagsNV value) { return static_cast<VkDeviceDiagnosticsConfigFlagsNV>(value);}
constexpr VkCompositeAlphaFlagsKHR to_c(CompositeAlphaFlagsKHR value) { return static_cast<VkCompositeAlphaFlagsKHR>(value);}
constexpr VkDisplayPlaneAlphaFlagsKHR to_c(DisplayPlaneAlphaFlagsKHR value) { return static_cast<VkDisplayPlaneAlphaFlagsKHR>(value);}
constexpr VkSurfaceTransformFlagsKHR to_c(SurfaceTransformFlagsKHR value) { return static_cast<VkSurfaceTransformFlagsKHR>(value);}
constexpr VkSwapchainCreateFlagsKHR to_c(SwapchainCreateFlagsKHR value) { return static_cast<VkSwapchainCreateFlagsKHR>(value);}
constexpr VkDisplayModeCreateFlagsKHR to_c(DisplayModeCreateFlagsKHR value) { return static_cast<VkDisplayModeCreateFlagsKHR>(value);}
constexpr VkDisplaySurfaceCreateFlagsKHR to_c(DisplaySurfaceCreateFlagsKHR value) { return static_cast<VkDisplaySurfaceCreateFlagsKHR>(value);}
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
constexpr VkAndroidSurfaceCreateFlagsKHR to_c(AndroidSurfaceCreateFlagsKHR value) { return static_cast<VkAndroidSurfaceCreateFlagsKHR>(value);}
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
constexpr VkViSurfaceCreateFlagsNN to_c(ViSurfaceCreateFlagsNN value) { return static_cast<VkViSurfaceCreateFlagsNN>(value);}
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
constexpr VkWaylandSurfaceCreateFlagsKHR to_c(WaylandSurfaceCreateFlagsKHR value) { return static_cast<VkWaylandSurfaceCreateFlagsKHR>(value);}
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkWin32SurfaceCreateFlagsKHR to_c(Win32SurfaceCreateFlagsKHR value) { return static_cast<VkWin32SurfaceCreateFlagsKHR>(value);}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
constexpr VkXlibSurfaceCreateFlagsKHR to_c(XlibSurfaceCreateFlagsKHR value) { return static_cast<VkXlibSurfaceCreateFlagsKHR>(value);}
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
constexpr VkXcbSurfaceCreateFlagsKHR to_c(XcbSurfaceCreateFlagsKHR value) { return static_cast<VkXcbSurfaceCreateFlagsKHR>(value);}
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
constexpr VkDirectFBSurfaceCreateFlagsEXT to_c(DirectFBSurfaceCreateFlagsEXT value) { return static_cast<VkDirectFBSurfaceCreateFlagsEXT>(value);}
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
constexpr VkIOSSurfaceCreateFlagsMVK to_c(IOSSurfaceCreateFlagsMVK value) { return static_cast<VkIOSSurfaceCreateFlagsMVK>(value);}
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
constexpr VkMacOSSurfaceCreateFlagsMVK to_c(MacOSSurfaceCreateFlagsMVK value) { return static_cast<VkMacOSSurfaceCreateFlagsMVK>(value);}
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
constexpr VkMetalSurfaceCreateFlagsEXT to_c(MetalSurfaceCreateFlagsEXT value) { return static_cast<VkMetalSurfaceCreateFlagsEXT>(value);}
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
constexpr VkImagePipeSurfaceCreateFlagsFUCHSIA to_c(ImagePipeSurfaceCreateFlagsFUCHSIA value) { return static_cast<VkImagePipeSurfaceCreateFlagsFUCHSIA>(value);}
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
constexpr VkStreamDescriptorSurfaceCreateFlagsGGP to_c(StreamDescriptorSurfaceCreateFlagsGGP value) { return static_cast<VkStreamDescriptorSurfaceCreateFlagsGGP>(value);}
#endif // defined(VK_USE_PLATFORM_GGP)
constexpr VkHeadlessSurfaceCreateFlagsEXT to_c(HeadlessSurfaceCreateFlagsEXT value) { return static_cast<VkHeadlessSurfaceCreateFlagsEXT>(value);}
constexpr VkPeerMemoryFeatureFlags to_c(PeerMemoryFeatureFlags value) { return static_cast<VkPeerMemoryFeatureFlags>(value);}
constexpr VkMemoryAllocateFlags to_c(MemoryAllocateFlags value) { return static_cast<VkMemoryAllocateFlags>(value);}
constexpr VkDeviceGroupPresentModeFlagsKHR to_c(DeviceGroupPresentModeFlagsKHR value) { return static_cast<VkDeviceGroupPresentModeFlagsKHR>(value);}
constexpr VkDebugReportFlagsEXT to_c(DebugReportFlagsEXT value) { return static_cast<VkDebugReportFlagsEXT>(value);}
constexpr VkCommandPoolTrimFlags to_c(CommandPoolTrimFlags value) { return static_cast<VkCommandPoolTrimFlags>(value);}
constexpr VkExternalMemoryHandleTypeFlagsNV to_c(ExternalMemoryHandleTypeFlagsNV value) { return static_cast<VkExternalMemoryHandleTypeFlagsNV>(value);}
constexpr VkExternalMemoryFeatureFlagsNV to_c(ExternalMemoryFeatureFlagsNV value) { return static_cast<VkExternalMemoryFeatureFlagsNV>(value);}
constexpr VkExternalMemoryHandleTypeFlags to_c(ExternalMemoryHandleTypeFlags value) { return static_cast<VkExternalMemoryHandleTypeFlags>(value);}
constexpr VkExternalMemoryFeatureFlags to_c(ExternalMemoryFeatureFlags value) { return static_cast<VkExternalMemoryFeatureFlags>(value);}
constexpr VkExternalSemaphoreHandleTypeFlags to_c(ExternalSemaphoreHandleTypeFlags value) { return static_cast<VkExternalSemaphoreHandleTypeFlags>(value);}
constexpr VkExternalSemaphoreFeatureFlags to_c(ExternalSemaphoreFeatureFlags value) { return static_cast<VkExternalSemaphoreFeatureFlags>(value);}
constexpr VkSemaphoreImportFlags to_c(SemaphoreImportFlags value) { return static_cast<VkSemaphoreImportFlags>(value);}
constexpr VkExternalFenceHandleTypeFlags to_c(ExternalFenceHandleTypeFlags value) { return static_cast<VkExternalFenceHandleTypeFlags>(value);}
constexpr VkExternalFenceFeatureFlags to_c(ExternalFenceFeatureFlags value) { return static_cast<VkExternalFenceFeatureFlags>(value);}
constexpr VkFenceImportFlags to_c(FenceImportFlags value) { return static_cast<VkFenceImportFlags>(value);}
constexpr VkSurfaceCounterFlagsEXT to_c(SurfaceCounterFlagsEXT value) { return static_cast<VkSurfaceCounterFlagsEXT>(value);}
constexpr VkPipelineViewportSwizzleStateCreateFlagsNV to_c(PipelineViewportSwizzleStateCreateFlagsNV value) { return static_cast<VkPipelineViewportSwizzleStateCreateFlagsNV>(value);}
constexpr VkPipelineDiscardRectangleStateCreateFlagsEXT to_c(PipelineDiscardRectangleStateCreateFlagsEXT value) { return static_cast<VkPipelineDiscardRectangleStateCreateFlagsEXT>(value);}
constexpr VkPipelineCoverageToColorStateCreateFlagsNV to_c(PipelineCoverageToColorStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageToColorStateCreateFlagsNV>(value);}
constexpr VkPipelineCoverageModulationStateCreateFlagsNV to_c(PipelineCoverageModulationStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageModulationStateCreateFlagsNV>(value);}
constexpr VkPipelineCoverageReductionStateCreateFlagsNV to_c(PipelineCoverageReductionStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageReductionStateCreateFlagsNV>(value);}
constexpr VkValidationCacheCreateFlagsEXT to_c(ValidationCacheCreateFlagsEXT value) { return static_cast<VkValidationCacheCreateFlagsEXT>(value);}
constexpr VkDebugUtilsMessageSeverityFlagsEXT to_c(DebugUtilsMessageSeverityFlagsEXT value) { return static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(value);}
constexpr VkDebugUtilsMessageTypeFlagsEXT to_c(DebugUtilsMessageTypeFlagsEXT value) { return static_cast<VkDebugUtilsMessageTypeFlagsEXT>(value);}
constexpr VkDebugUtilsMessengerCreateFlagsEXT to_c(DebugUtilsMessengerCreateFlagsEXT value) { return static_cast<VkDebugUtilsMessengerCreateFlagsEXT>(value);}
constexpr VkDebugUtilsMessengerCallbackDataFlagsEXT to_c(DebugUtilsMessengerCallbackDataFlagsEXT value) { return static_cast<VkDebugUtilsMessengerCallbackDataFlagsEXT>(value);}
constexpr VkDeviceMemoryReportFlagsEXT to_c(DeviceMemoryReportFlagsEXT value) { return static_cast<VkDeviceMemoryReportFlagsEXT>(value);}
constexpr VkPipelineRasterizationConservativeStateCreateFlagsEXT to_c(PipelineRasterizationConservativeStateCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationConservativeStateCreateFlagsEXT>(value);}
constexpr VkDescriptorBindingFlags to_c(DescriptorBindingFlags value) { return static_cast<VkDescriptorBindingFlags>(value);}
constexpr VkConditionalRenderingFlagsEXT to_c(ConditionalRenderingFlagsEXT value) { return static_cast<VkConditionalRenderingFlagsEXT>(value);}
constexpr VkResolveModeFlags to_c(ResolveModeFlags value) { return static_cast<VkResolveModeFlags>(value);}
constexpr VkPipelineRasterizationStateStreamCreateFlagsEXT to_c(PipelineRasterizationStateStreamCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationStateStreamCreateFlagsEXT>(value);}
constexpr VkPipelineRasterizationDepthClipStateCreateFlagsEXT to_c(PipelineRasterizationDepthClipStateCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationDepthClipStateCreateFlagsEXT>(value);}
constexpr VkToolPurposeFlagsEXT to_c(ToolPurposeFlagsEXT value) { return static_cast<VkToolPurposeFlagsEXT>(value);}
} // namespace vk
// clang-format on
