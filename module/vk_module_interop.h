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
#pragma once
// clang-format off
#include "vulkan/vulkan.h"
#include "vk_module.h"
namespace vk {
constexpr VkAttachmentLoadOp to_c(AttachmentLoadOp value) { return static_cast<VkAttachmentLoadOp>(value);}
constexpr AttachmentLoadOp from_c(VkAttachmentLoadOp value) { return static_cast<AttachmentLoadOp>(value);}
constexpr VkAttachmentStoreOp to_c(AttachmentStoreOp value) { return static_cast<VkAttachmentStoreOp>(value);}
constexpr AttachmentStoreOp from_c(VkAttachmentStoreOp value) { return static_cast<AttachmentStoreOp>(value);}
constexpr VkBlendFactor to_c(BlendFactor value) { return static_cast<VkBlendFactor>(value);}
constexpr BlendFactor from_c(VkBlendFactor value) { return static_cast<BlendFactor>(value);}
constexpr VkBlendOp to_c(BlendOp value) { return static_cast<VkBlendOp>(value);}
constexpr BlendOp from_c(VkBlendOp value) { return static_cast<BlendOp>(value);}
constexpr VkBorderColor to_c(BorderColor value) { return static_cast<VkBorderColor>(value);}
constexpr BorderColor from_c(VkBorderColor value) { return static_cast<BorderColor>(value);}
constexpr VkPipelineCacheHeaderVersion to_c(PipelineCacheHeaderVersion value) { return static_cast<VkPipelineCacheHeaderVersion>(value);}
constexpr PipelineCacheHeaderVersion from_c(VkPipelineCacheHeaderVersion value) { return static_cast<PipelineCacheHeaderVersion>(value);}
constexpr VkComponentSwizzle to_c(ComponentSwizzle value) { return static_cast<VkComponentSwizzle>(value);}
constexpr ComponentSwizzle from_c(VkComponentSwizzle value) { return static_cast<ComponentSwizzle>(value);}
constexpr VkCommandBufferLevel to_c(CommandBufferLevel value) { return static_cast<VkCommandBufferLevel>(value);}
constexpr CommandBufferLevel from_c(VkCommandBufferLevel value) { return static_cast<CommandBufferLevel>(value);}
constexpr VkCompareOp to_c(CompareOp value) { return static_cast<VkCompareOp>(value);}
constexpr CompareOp from_c(VkCompareOp value) { return static_cast<CompareOp>(value);}
constexpr VkDescriptorType to_c(DescriptorType value) { return static_cast<VkDescriptorType>(value);}
constexpr DescriptorType from_c(VkDescriptorType value) { return static_cast<DescriptorType>(value);}
constexpr VkDynamicState to_c(DynamicState value) { return static_cast<VkDynamicState>(value);}
constexpr DynamicState from_c(VkDynamicState value) { return static_cast<DynamicState>(value);}
constexpr VkPolygonMode to_c(PolygonMode value) { return static_cast<VkPolygonMode>(value);}
constexpr PolygonMode from_c(VkPolygonMode value) { return static_cast<PolygonMode>(value);}
constexpr VkFormat to_c(Format value) { return static_cast<VkFormat>(value);}
constexpr Format from_c(VkFormat value) { return static_cast<Format>(value);}
constexpr VkFrontFace to_c(FrontFace value) { return static_cast<VkFrontFace>(value);}
constexpr FrontFace from_c(VkFrontFace value) { return static_cast<FrontFace>(value);}
constexpr VkImageLayout to_c(ImageLayout value) { return static_cast<VkImageLayout>(value);}
constexpr ImageLayout from_c(VkImageLayout value) { return static_cast<ImageLayout>(value);}
constexpr VkImageTiling to_c(ImageTiling value) { return static_cast<VkImageTiling>(value);}
constexpr ImageTiling from_c(VkImageTiling value) { return static_cast<ImageTiling>(value);}
constexpr VkImageType to_c(ImageType value) { return static_cast<VkImageType>(value);}
constexpr ImageType from_c(VkImageType value) { return static_cast<ImageType>(value);}
constexpr VkImageViewType to_c(ImageViewType value) { return static_cast<VkImageViewType>(value);}
constexpr ImageViewType from_c(VkImageViewType value) { return static_cast<ImageViewType>(value);}
constexpr VkSharingMode to_c(SharingMode value) { return static_cast<VkSharingMode>(value);}
constexpr SharingMode from_c(VkSharingMode value) { return static_cast<SharingMode>(value);}
constexpr VkIndexType to_c(IndexType value) { return static_cast<VkIndexType>(value);}
constexpr IndexType from_c(VkIndexType value) { return static_cast<IndexType>(value);}
constexpr VkLogicOp to_c(LogicOp value) { return static_cast<VkLogicOp>(value);}
constexpr LogicOp from_c(VkLogicOp value) { return static_cast<LogicOp>(value);}
constexpr VkPhysicalDeviceType to_c(PhysicalDeviceType value) { return static_cast<VkPhysicalDeviceType>(value);}
constexpr PhysicalDeviceType from_c(VkPhysicalDeviceType value) { return static_cast<PhysicalDeviceType>(value);}
constexpr VkPipelineBindPoint to_c(PipelineBindPoint value) { return static_cast<VkPipelineBindPoint>(value);}
constexpr PipelineBindPoint from_c(VkPipelineBindPoint value) { return static_cast<PipelineBindPoint>(value);}
constexpr VkPrimitiveTopology to_c(PrimitiveTopology value) { return static_cast<VkPrimitiveTopology>(value);}
constexpr PrimitiveTopology from_c(VkPrimitiveTopology value) { return static_cast<PrimitiveTopology>(value);}
constexpr VkQueryType to_c(QueryType value) { return static_cast<VkQueryType>(value);}
constexpr QueryType from_c(VkQueryType value) { return static_cast<QueryType>(value);}
constexpr VkSubpassContents to_c(SubpassContents value) { return static_cast<VkSubpassContents>(value);}
constexpr SubpassContents from_c(VkSubpassContents value) { return static_cast<SubpassContents>(value);}
constexpr VkResult to_c(Result value) { return static_cast<VkResult>(value);}
constexpr Result from_c(VkResult value) { return static_cast<Result>(value);}
constexpr VkStencilOp to_c(StencilOp value) { return static_cast<VkStencilOp>(value);}
constexpr StencilOp from_c(VkStencilOp value) { return static_cast<StencilOp>(value);}
constexpr VkStructureType to_c(StructureType value) { return static_cast<VkStructureType>(value);}
constexpr StructureType from_c(VkStructureType value) { return static_cast<StructureType>(value);}
constexpr VkSystemAllocationScope to_c(SystemAllocationScope value) { return static_cast<VkSystemAllocationScope>(value);}
constexpr SystemAllocationScope from_c(VkSystemAllocationScope value) { return static_cast<SystemAllocationScope>(value);}
constexpr VkInternalAllocationType to_c(InternalAllocationType value) { return static_cast<VkInternalAllocationType>(value);}
constexpr InternalAllocationType from_c(VkInternalAllocationType value) { return static_cast<InternalAllocationType>(value);}
constexpr VkSamplerAddressMode to_c(SamplerAddressMode value) { return static_cast<VkSamplerAddressMode>(value);}
constexpr SamplerAddressMode from_c(VkSamplerAddressMode value) { return static_cast<SamplerAddressMode>(value);}
constexpr VkFilter to_c(Filter value) { return static_cast<VkFilter>(value);}
constexpr Filter from_c(VkFilter value) { return static_cast<Filter>(value);}
constexpr VkSamplerMipmapMode to_c(SamplerMipmapMode value) { return static_cast<VkSamplerMipmapMode>(value);}
constexpr SamplerMipmapMode from_c(VkSamplerMipmapMode value) { return static_cast<SamplerMipmapMode>(value);}
constexpr VkVertexInputRate to_c(VertexInputRate value) { return static_cast<VkVertexInputRate>(value);}
constexpr VertexInputRate from_c(VkVertexInputRate value) { return static_cast<VertexInputRate>(value);}
constexpr VkObjectType to_c(ObjectType value) { return static_cast<VkObjectType>(value);}
constexpr ObjectType from_c(VkObjectType value) { return static_cast<ObjectType>(value);}
constexpr VkIndirectCommandsTokenTypeNV to_c(IndirectCommandsTokenTypeNV value) { return static_cast<VkIndirectCommandsTokenTypeNV>(value);}
constexpr IndirectCommandsTokenTypeNV from_c(VkIndirectCommandsTokenTypeNV value) { return static_cast<IndirectCommandsTokenTypeNV>(value);}
constexpr VkDescriptorUpdateTemplateType to_c(DescriptorUpdateTemplateType value) { return static_cast<VkDescriptorUpdateTemplateType>(value);}
constexpr DescriptorUpdateTemplateType from_c(VkDescriptorUpdateTemplateType value) { return static_cast<DescriptorUpdateTemplateType>(value);}
constexpr VkViewportCoordinateSwizzleNV to_c(ViewportCoordinateSwizzleNV value) { return static_cast<VkViewportCoordinateSwizzleNV>(value);}
constexpr ViewportCoordinateSwizzleNV from_c(VkViewportCoordinateSwizzleNV value) { return static_cast<ViewportCoordinateSwizzleNV>(value);}
constexpr VkDiscardRectangleModeEXT to_c(DiscardRectangleModeEXT value) { return static_cast<VkDiscardRectangleModeEXT>(value);}
constexpr DiscardRectangleModeEXT from_c(VkDiscardRectangleModeEXT value) { return static_cast<DiscardRectangleModeEXT>(value);}
constexpr VkPointClippingBehavior to_c(PointClippingBehavior value) { return static_cast<VkPointClippingBehavior>(value);}
constexpr PointClippingBehavior from_c(VkPointClippingBehavior value) { return static_cast<PointClippingBehavior>(value);}
constexpr VkCoverageModulationModeNV to_c(CoverageModulationModeNV value) { return static_cast<VkCoverageModulationModeNV>(value);}
constexpr CoverageModulationModeNV from_c(VkCoverageModulationModeNV value) { return static_cast<CoverageModulationModeNV>(value);}
constexpr VkCoverageReductionModeNV to_c(CoverageReductionModeNV value) { return static_cast<VkCoverageReductionModeNV>(value);}
constexpr CoverageReductionModeNV from_c(VkCoverageReductionModeNV value) { return static_cast<CoverageReductionModeNV>(value);}
constexpr VkValidationCacheHeaderVersionEXT to_c(ValidationCacheHeaderVersionEXT value) { return static_cast<VkValidationCacheHeaderVersionEXT>(value);}
constexpr ValidationCacheHeaderVersionEXT from_c(VkValidationCacheHeaderVersionEXT value) { return static_cast<ValidationCacheHeaderVersionEXT>(value);}
constexpr VkShaderInfoTypeAMD to_c(ShaderInfoTypeAMD value) { return static_cast<VkShaderInfoTypeAMD>(value);}
constexpr ShaderInfoTypeAMD from_c(VkShaderInfoTypeAMD value) { return static_cast<ShaderInfoTypeAMD>(value);}
constexpr VkQueueGlobalPriorityEXT to_c(QueueGlobalPriorityEXT value) { return static_cast<VkQueueGlobalPriorityEXT>(value);}
constexpr QueueGlobalPriorityEXT from_c(VkQueueGlobalPriorityEXT value) { return static_cast<QueueGlobalPriorityEXT>(value);}
constexpr VkTimeDomainEXT to_c(TimeDomainEXT value) { return static_cast<VkTimeDomainEXT>(value);}
constexpr TimeDomainEXT from_c(VkTimeDomainEXT value) { return static_cast<TimeDomainEXT>(value);}
constexpr VkConservativeRasterizationModeEXT to_c(ConservativeRasterizationModeEXT value) { return static_cast<VkConservativeRasterizationModeEXT>(value);}
constexpr ConservativeRasterizationModeEXT from_c(VkConservativeRasterizationModeEXT value) { return static_cast<ConservativeRasterizationModeEXT>(value);}
constexpr VkSemaphoreType to_c(SemaphoreType value) { return static_cast<VkSemaphoreType>(value);}
constexpr SemaphoreType from_c(VkSemaphoreType value) { return static_cast<SemaphoreType>(value);}
constexpr VkBuildAccelerationStructureModeKHR to_c(BuildAccelerationStructureModeKHR value) { return static_cast<VkBuildAccelerationStructureModeKHR>(value);}
constexpr BuildAccelerationStructureModeKHR from_c(VkBuildAccelerationStructureModeKHR value) { return static_cast<BuildAccelerationStructureModeKHR>(value);}
constexpr VkCopyAccelerationStructureModeKHR to_c(CopyAccelerationStructureModeKHR value) { return static_cast<VkCopyAccelerationStructureModeKHR>(value);}
constexpr CopyAccelerationStructureModeKHR from_c(VkCopyAccelerationStructureModeKHR value) { return static_cast<CopyAccelerationStructureModeKHR>(value);}
constexpr VkAccelerationStructureTypeKHR to_c(AccelerationStructureTypeKHR value) { return static_cast<VkAccelerationStructureTypeKHR>(value);}
constexpr AccelerationStructureTypeKHR from_c(VkAccelerationStructureTypeKHR value) { return static_cast<AccelerationStructureTypeKHR>(value);}
constexpr VkGeometryTypeKHR to_c(GeometryTypeKHR value) { return static_cast<VkGeometryTypeKHR>(value);}
constexpr GeometryTypeKHR from_c(VkGeometryTypeKHR value) { return static_cast<GeometryTypeKHR>(value);}
constexpr VkRayTracingShaderGroupTypeKHR to_c(RayTracingShaderGroupTypeKHR value) { return static_cast<VkRayTracingShaderGroupTypeKHR>(value);}
constexpr RayTracingShaderGroupTypeKHR from_c(VkRayTracingShaderGroupTypeKHR value) { return static_cast<RayTracingShaderGroupTypeKHR>(value);}
constexpr VkAccelerationStructureMemoryRequirementsTypeNV to_c(AccelerationStructureMemoryRequirementsTypeNV value) { return static_cast<VkAccelerationStructureMemoryRequirementsTypeNV>(value);}
constexpr AccelerationStructureMemoryRequirementsTypeNV from_c(VkAccelerationStructureMemoryRequirementsTypeNV value) { return static_cast<AccelerationStructureMemoryRequirementsTypeNV>(value);}
constexpr VkAccelerationStructureBuildTypeKHR to_c(AccelerationStructureBuildTypeKHR value) { return static_cast<VkAccelerationStructureBuildTypeKHR>(value);}
constexpr AccelerationStructureBuildTypeKHR from_c(VkAccelerationStructureBuildTypeKHR value) { return static_cast<AccelerationStructureBuildTypeKHR>(value);}
constexpr VkAccelerationStructureCompatibilityKHR to_c(AccelerationStructureCompatibilityKHR value) { return static_cast<VkAccelerationStructureCompatibilityKHR>(value);}
constexpr AccelerationStructureCompatibilityKHR from_c(VkAccelerationStructureCompatibilityKHR value) { return static_cast<AccelerationStructureCompatibilityKHR>(value);}
constexpr VkShaderGroupShaderKHR to_c(ShaderGroupShaderKHR value) { return static_cast<VkShaderGroupShaderKHR>(value);}
constexpr ShaderGroupShaderKHR from_c(VkShaderGroupShaderKHR value) { return static_cast<ShaderGroupShaderKHR>(value);}
constexpr VkMemoryOverallocationBehaviorAMD to_c(MemoryOverallocationBehaviorAMD value) { return static_cast<VkMemoryOverallocationBehaviorAMD>(value);}
constexpr MemoryOverallocationBehaviorAMD from_c(VkMemoryOverallocationBehaviorAMD value) { return static_cast<MemoryOverallocationBehaviorAMD>(value);}
constexpr VkScopeNV to_c(ScopeNV value) { return static_cast<VkScopeNV>(value);}
constexpr ScopeNV from_c(VkScopeNV value) { return static_cast<ScopeNV>(value);}
constexpr VkComponentTypeNV to_c(ComponentTypeNV value) { return static_cast<VkComponentTypeNV>(value);}
constexpr ComponentTypeNV from_c(VkComponentTypeNV value) { return static_cast<ComponentTypeNV>(value);}
constexpr VkPerformanceCounterScopeKHR to_c(PerformanceCounterScopeKHR value) { return static_cast<VkPerformanceCounterScopeKHR>(value);}
constexpr PerformanceCounterScopeKHR from_c(VkPerformanceCounterScopeKHR value) { return static_cast<PerformanceCounterScopeKHR>(value);}
constexpr VkPerformanceCounterUnitKHR to_c(PerformanceCounterUnitKHR value) { return static_cast<VkPerformanceCounterUnitKHR>(value);}
constexpr PerformanceCounterUnitKHR from_c(VkPerformanceCounterUnitKHR value) { return static_cast<PerformanceCounterUnitKHR>(value);}
constexpr VkPerformanceCounterStorageKHR to_c(PerformanceCounterStorageKHR value) { return static_cast<VkPerformanceCounterStorageKHR>(value);}
constexpr PerformanceCounterStorageKHR from_c(VkPerformanceCounterStorageKHR value) { return static_cast<PerformanceCounterStorageKHR>(value);}
constexpr VkPerformanceConfigurationTypeINTEL to_c(PerformanceConfigurationTypeINTEL value) { return static_cast<VkPerformanceConfigurationTypeINTEL>(value);}
constexpr PerformanceConfigurationTypeINTEL from_c(VkPerformanceConfigurationTypeINTEL value) { return static_cast<PerformanceConfigurationTypeINTEL>(value);}
constexpr VkQueryPoolSamplingModeINTEL to_c(QueryPoolSamplingModeINTEL value) { return static_cast<VkQueryPoolSamplingModeINTEL>(value);}
constexpr QueryPoolSamplingModeINTEL from_c(VkQueryPoolSamplingModeINTEL value) { return static_cast<QueryPoolSamplingModeINTEL>(value);}
constexpr VkPerformanceOverrideTypeINTEL to_c(PerformanceOverrideTypeINTEL value) { return static_cast<VkPerformanceOverrideTypeINTEL>(value);}
constexpr PerformanceOverrideTypeINTEL from_c(VkPerformanceOverrideTypeINTEL value) { return static_cast<PerformanceOverrideTypeINTEL>(value);}
constexpr VkPerformanceParameterTypeINTEL to_c(PerformanceParameterTypeINTEL value) { return static_cast<VkPerformanceParameterTypeINTEL>(value);}
constexpr PerformanceParameterTypeINTEL from_c(VkPerformanceParameterTypeINTEL value) { return static_cast<PerformanceParameterTypeINTEL>(value);}
constexpr VkPerformanceValueTypeINTEL to_c(PerformanceValueTypeINTEL value) { return static_cast<VkPerformanceValueTypeINTEL>(value);}
constexpr PerformanceValueTypeINTEL from_c(VkPerformanceValueTypeINTEL value) { return static_cast<PerformanceValueTypeINTEL>(value);}
constexpr VkLineRasterizationModeEXT to_c(LineRasterizationModeEXT value) { return static_cast<VkLineRasterizationModeEXT>(value);}
constexpr LineRasterizationModeEXT from_c(VkLineRasterizationModeEXT value) { return static_cast<LineRasterizationModeEXT>(value);}
constexpr VkFragmentShadingRateNV to_c(FragmentShadingRateNV value) { return static_cast<VkFragmentShadingRateNV>(value);}
constexpr FragmentShadingRateNV from_c(VkFragmentShadingRateNV value) { return static_cast<FragmentShadingRateNV>(value);}
constexpr VkFragmentShadingRateTypeNV to_c(FragmentShadingRateTypeNV value) { return static_cast<VkFragmentShadingRateTypeNV>(value);}
constexpr FragmentShadingRateTypeNV from_c(VkFragmentShadingRateTypeNV value) { return static_cast<FragmentShadingRateTypeNV>(value);}
constexpr VkProvokingVertexModeEXT to_c(ProvokingVertexModeEXT value) { return static_cast<VkProvokingVertexModeEXT>(value);}
constexpr ProvokingVertexModeEXT from_c(VkProvokingVertexModeEXT value) { return static_cast<ProvokingVertexModeEXT>(value);}
constexpr VkColorSpaceKHR to_c(ColorSpaceKHR value) { return static_cast<VkColorSpaceKHR>(value);}
constexpr ColorSpaceKHR from_c(VkColorSpaceKHR value) { return static_cast<ColorSpaceKHR>(value);}
constexpr VkPresentModeKHR to_c(PresentModeKHR value) { return static_cast<VkPresentModeKHR>(value);}
constexpr PresentModeKHR from_c(VkPresentModeKHR value) { return static_cast<PresentModeKHR>(value);}
constexpr VkDebugReportObjectTypeEXT to_c(DebugReportObjectTypeEXT value) { return static_cast<VkDebugReportObjectTypeEXT>(value);}
constexpr DebugReportObjectTypeEXT from_c(VkDebugReportObjectTypeEXT value) { return static_cast<DebugReportObjectTypeEXT>(value);}
constexpr VkDeviceMemoryReportEventTypeEXT to_c(DeviceMemoryReportEventTypeEXT value) { return static_cast<VkDeviceMemoryReportEventTypeEXT>(value);}
constexpr DeviceMemoryReportEventTypeEXT from_c(VkDeviceMemoryReportEventTypeEXT value) { return static_cast<DeviceMemoryReportEventTypeEXT>(value);}
constexpr VkRasterizationOrderAMD to_c(RasterizationOrderAMD value) { return static_cast<VkRasterizationOrderAMD>(value);}
constexpr RasterizationOrderAMD from_c(VkRasterizationOrderAMD value) { return static_cast<RasterizationOrderAMD>(value);}
constexpr VkValidationCheckEXT to_c(ValidationCheckEXT value) { return static_cast<VkValidationCheckEXT>(value);}
constexpr ValidationCheckEXT from_c(VkValidationCheckEXT value) { return static_cast<ValidationCheckEXT>(value);}
constexpr VkValidationFeatureEnableEXT to_c(ValidationFeatureEnableEXT value) { return static_cast<VkValidationFeatureEnableEXT>(value);}
constexpr ValidationFeatureEnableEXT from_c(VkValidationFeatureEnableEXT value) { return static_cast<ValidationFeatureEnableEXT>(value);}
constexpr VkValidationFeatureDisableEXT to_c(ValidationFeatureDisableEXT value) { return static_cast<VkValidationFeatureDisableEXT>(value);}
constexpr ValidationFeatureDisableEXT from_c(VkValidationFeatureDisableEXT value) { return static_cast<ValidationFeatureDisableEXT>(value);}
constexpr VkDisplayPowerStateEXT to_c(DisplayPowerStateEXT value) { return static_cast<VkDisplayPowerStateEXT>(value);}
constexpr DisplayPowerStateEXT from_c(VkDisplayPowerStateEXT value) { return static_cast<DisplayPowerStateEXT>(value);}
constexpr VkDeviceEventTypeEXT to_c(DeviceEventTypeEXT value) { return static_cast<VkDeviceEventTypeEXT>(value);}
constexpr DeviceEventTypeEXT from_c(VkDeviceEventTypeEXT value) { return static_cast<DeviceEventTypeEXT>(value);}
constexpr VkDisplayEventTypeEXT to_c(DisplayEventTypeEXT value) { return static_cast<VkDisplayEventTypeEXT>(value);}
constexpr DisplayEventTypeEXT from_c(VkDisplayEventTypeEXT value) { return static_cast<DisplayEventTypeEXT>(value);}
constexpr VkTessellationDomainOrigin to_c(TessellationDomainOrigin value) { return static_cast<VkTessellationDomainOrigin>(value);}
constexpr TessellationDomainOrigin from_c(VkTessellationDomainOrigin value) { return static_cast<TessellationDomainOrigin>(value);}
constexpr VkSamplerYcbcrModelConversion to_c(SamplerYcbcrModelConversion value) { return static_cast<VkSamplerYcbcrModelConversion>(value);}
constexpr SamplerYcbcrModelConversion from_c(VkSamplerYcbcrModelConversion value) { return static_cast<SamplerYcbcrModelConversion>(value);}
constexpr VkSamplerYcbcrRange to_c(SamplerYcbcrRange value) { return static_cast<VkSamplerYcbcrRange>(value);}
constexpr SamplerYcbcrRange from_c(VkSamplerYcbcrRange value) { return static_cast<SamplerYcbcrRange>(value);}
constexpr VkChromaLocation to_c(ChromaLocation value) { return static_cast<VkChromaLocation>(value);}
constexpr ChromaLocation from_c(VkChromaLocation value) { return static_cast<ChromaLocation>(value);}
constexpr VkSamplerReductionMode to_c(SamplerReductionMode value) { return static_cast<VkSamplerReductionMode>(value);}
constexpr SamplerReductionMode from_c(VkSamplerReductionMode value) { return static_cast<SamplerReductionMode>(value);}
constexpr VkBlendOverlapEXT to_c(BlendOverlapEXT value) { return static_cast<VkBlendOverlapEXT>(value);}
constexpr BlendOverlapEXT from_c(VkBlendOverlapEXT value) { return static_cast<BlendOverlapEXT>(value);}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkFullScreenExclusiveEXT to_c(FullScreenExclusiveEXT value) { return static_cast<VkFullScreenExclusiveEXT>(value);}
constexpr FullScreenExclusiveEXT from_c(VkFullScreenExclusiveEXT value) { return static_cast<FullScreenExclusiveEXT>(value);}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkShaderFloatControlsIndependence to_c(ShaderFloatControlsIndependence value) { return static_cast<VkShaderFloatControlsIndependence>(value);}
constexpr ShaderFloatControlsIndependence from_c(VkShaderFloatControlsIndependence value) { return static_cast<ShaderFloatControlsIndependence>(value);}
constexpr VkFragmentShadingRateCombinerOpKHR to_c(FragmentShadingRateCombinerOpKHR value) { return static_cast<VkFragmentShadingRateCombinerOpKHR>(value);}
constexpr FragmentShadingRateCombinerOpKHR from_c(VkFragmentShadingRateCombinerOpKHR value) { return static_cast<FragmentShadingRateCombinerOpKHR>(value);}
constexpr VkVendorId to_c(VendorId value) { return static_cast<VkVendorId>(value);}
constexpr VendorId from_c(VkVendorId value) { return static_cast<VendorId>(value);}
constexpr VkDriverId to_c(DriverId value) { return static_cast<VkDriverId>(value);}
constexpr DriverId from_c(VkDriverId value) { return static_cast<DriverId>(value);}
constexpr VkShadingRatePaletteEntryNV to_c(ShadingRatePaletteEntryNV value) { return static_cast<VkShadingRatePaletteEntryNV>(value);}
constexpr ShadingRatePaletteEntryNV from_c(VkShadingRatePaletteEntryNV value) { return static_cast<ShadingRatePaletteEntryNV>(value);}
constexpr VkCoarseSampleOrderTypeNV to_c(CoarseSampleOrderTypeNV value) { return static_cast<VkCoarseSampleOrderTypeNV>(value);}
constexpr CoarseSampleOrderTypeNV from_c(VkCoarseSampleOrderTypeNV value) { return static_cast<CoarseSampleOrderTypeNV>(value);}
constexpr VkPipelineExecutableStatisticFormatKHR to_c(PipelineExecutableStatisticFormatKHR value) { return static_cast<VkPipelineExecutableStatisticFormatKHR>(value);}
constexpr PipelineExecutableStatisticFormatKHR from_c(VkPipelineExecutableStatisticFormatKHR value) { return static_cast<PipelineExecutableStatisticFormatKHR>(value);}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
constexpr VkQueryResultStatusKHR to_c(QueryResultStatusKHR value) { return static_cast<VkQueryResultStatusKHR>(value);}
constexpr QueryResultStatusKHR from_c(VkQueryResultStatusKHR value) { return static_cast<QueryResultStatusKHR>(value);}
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
constexpr VkAccelerationStructureMotionInstanceTypeNV to_c(AccelerationStructureMotionInstanceTypeNV value) { return static_cast<VkAccelerationStructureMotionInstanceTypeNV>(value);}
constexpr AccelerationStructureMotionInstanceTypeNV from_c(VkAccelerationStructureMotionInstanceTypeNV value) { return static_cast<AccelerationStructureMotionInstanceTypeNV>(value);}
constexpr VkPipelineCacheCreateFlagBits to_c(PipelineCacheCreateFlagBits value) { return static_cast<VkPipelineCacheCreateFlagBits>(value);}
constexpr PipelineCacheCreateFlagBits from_c(VkPipelineCacheCreateFlagBits value) { return static_cast<PipelineCacheCreateFlagBits>(value);}
constexpr VkQueueFlagBits to_c(QueueFlagBits value) { return static_cast<VkQueueFlagBits>(value);}
constexpr QueueFlagBits from_c(VkQueueFlagBits value) { return static_cast<QueueFlagBits>(value);}
constexpr VkCullModeFlagBits to_c(CullModeFlagBits value) { return static_cast<VkCullModeFlagBits>(value);}
constexpr CullModeFlagBits from_c(VkCullModeFlagBits value) { return static_cast<CullModeFlagBits>(value);}
constexpr VkRenderPassCreateFlagBits to_c(RenderPassCreateFlagBits value) { return static_cast<VkRenderPassCreateFlagBits>(value);}
constexpr RenderPassCreateFlagBits from_c(VkRenderPassCreateFlagBits value) { return static_cast<RenderPassCreateFlagBits>(value);}
constexpr VkDeviceQueueCreateFlagBits to_c(DeviceQueueCreateFlagBits value) { return static_cast<VkDeviceQueueCreateFlagBits>(value);}
constexpr DeviceQueueCreateFlagBits from_c(VkDeviceQueueCreateFlagBits value) { return static_cast<DeviceQueueCreateFlagBits>(value);}
constexpr VkMemoryPropertyFlagBits to_c(MemoryPropertyFlagBits value) { return static_cast<VkMemoryPropertyFlagBits>(value);}
constexpr MemoryPropertyFlagBits from_c(VkMemoryPropertyFlagBits value) { return static_cast<MemoryPropertyFlagBits>(value);}
constexpr VkMemoryHeapFlagBits to_c(MemoryHeapFlagBits value) { return static_cast<VkMemoryHeapFlagBits>(value);}
constexpr MemoryHeapFlagBits from_c(VkMemoryHeapFlagBits value) { return static_cast<MemoryHeapFlagBits>(value);}
constexpr VkAccessFlagBits to_c(AccessFlagBits value) { return static_cast<VkAccessFlagBits>(value);}
constexpr AccessFlagBits from_c(VkAccessFlagBits value) { return static_cast<AccessFlagBits>(value);}
constexpr VkBufferUsageFlagBits to_c(BufferUsageFlagBits value) { return static_cast<VkBufferUsageFlagBits>(value);}
constexpr BufferUsageFlagBits from_c(VkBufferUsageFlagBits value) { return static_cast<BufferUsageFlagBits>(value);}
constexpr VkBufferCreateFlagBits to_c(BufferCreateFlagBits value) { return static_cast<VkBufferCreateFlagBits>(value);}
constexpr BufferCreateFlagBits from_c(VkBufferCreateFlagBits value) { return static_cast<BufferCreateFlagBits>(value);}
constexpr VkShaderStageFlagBits to_c(ShaderStageFlagBits value) { return static_cast<VkShaderStageFlagBits>(value);}
constexpr ShaderStageFlagBits from_c(VkShaderStageFlagBits value) { return static_cast<ShaderStageFlagBits>(value);}
constexpr VkImageUsageFlagBits to_c(ImageUsageFlagBits value) { return static_cast<VkImageUsageFlagBits>(value);}
constexpr ImageUsageFlagBits from_c(VkImageUsageFlagBits value) { return static_cast<ImageUsageFlagBits>(value);}
constexpr VkImageCreateFlagBits to_c(ImageCreateFlagBits value) { return static_cast<VkImageCreateFlagBits>(value);}
constexpr ImageCreateFlagBits from_c(VkImageCreateFlagBits value) { return static_cast<ImageCreateFlagBits>(value);}
constexpr VkImageViewCreateFlagBits to_c(ImageViewCreateFlagBits value) { return static_cast<VkImageViewCreateFlagBits>(value);}
constexpr ImageViewCreateFlagBits from_c(VkImageViewCreateFlagBits value) { return static_cast<ImageViewCreateFlagBits>(value);}
constexpr VkSamplerCreateFlagBits to_c(SamplerCreateFlagBits value) { return static_cast<VkSamplerCreateFlagBits>(value);}
constexpr SamplerCreateFlagBits from_c(VkSamplerCreateFlagBits value) { return static_cast<SamplerCreateFlagBits>(value);}
constexpr VkPipelineCreateFlagBits to_c(PipelineCreateFlagBits value) { return static_cast<VkPipelineCreateFlagBits>(value);}
constexpr PipelineCreateFlagBits from_c(VkPipelineCreateFlagBits value) { return static_cast<PipelineCreateFlagBits>(value);}
constexpr VkPipelineShaderStageCreateFlagBits to_c(PipelineShaderStageCreateFlagBits value) { return static_cast<VkPipelineShaderStageCreateFlagBits>(value);}
constexpr PipelineShaderStageCreateFlagBits from_c(VkPipelineShaderStageCreateFlagBits value) { return static_cast<PipelineShaderStageCreateFlagBits>(value);}
constexpr VkColorComponentFlagBits to_c(ColorComponentFlagBits value) { return static_cast<VkColorComponentFlagBits>(value);}
constexpr ColorComponentFlagBits from_c(VkColorComponentFlagBits value) { return static_cast<ColorComponentFlagBits>(value);}
constexpr VkFenceCreateFlagBits to_c(FenceCreateFlagBits value) { return static_cast<VkFenceCreateFlagBits>(value);}
constexpr FenceCreateFlagBits from_c(VkFenceCreateFlagBits value) { return static_cast<FenceCreateFlagBits>(value);}
constexpr VkSemaphoreCreateFlagBits to_c(SemaphoreCreateFlagBits value) { return static_cast<VkSemaphoreCreateFlagBits>(value);}
constexpr SemaphoreCreateFlagBits from_c(VkSemaphoreCreateFlagBits value) { return static_cast<SemaphoreCreateFlagBits>(value);}
constexpr VkFormatFeatureFlagBits to_c(FormatFeatureFlagBits value) { return static_cast<VkFormatFeatureFlagBits>(value);}
constexpr FormatFeatureFlagBits from_c(VkFormatFeatureFlagBits value) { return static_cast<FormatFeatureFlagBits>(value);}
constexpr VkQueryControlFlagBits to_c(QueryControlFlagBits value) { return static_cast<VkQueryControlFlagBits>(value);}
constexpr QueryControlFlagBits from_c(VkQueryControlFlagBits value) { return static_cast<QueryControlFlagBits>(value);}
constexpr VkQueryResultFlagBits to_c(QueryResultFlagBits value) { return static_cast<VkQueryResultFlagBits>(value);}
constexpr QueryResultFlagBits from_c(VkQueryResultFlagBits value) { return static_cast<QueryResultFlagBits>(value);}
constexpr VkCommandBufferUsageFlagBits to_c(CommandBufferUsageFlagBits value) { return static_cast<VkCommandBufferUsageFlagBits>(value);}
constexpr CommandBufferUsageFlagBits from_c(VkCommandBufferUsageFlagBits value) { return static_cast<CommandBufferUsageFlagBits>(value);}
constexpr VkQueryPipelineStatisticFlagBits to_c(QueryPipelineStatisticFlagBits value) { return static_cast<VkQueryPipelineStatisticFlagBits>(value);}
constexpr QueryPipelineStatisticFlagBits from_c(VkQueryPipelineStatisticFlagBits value) { return static_cast<QueryPipelineStatisticFlagBits>(value);}
constexpr VkImageAspectFlagBits to_c(ImageAspectFlagBits value) { return static_cast<VkImageAspectFlagBits>(value);}
constexpr ImageAspectFlagBits from_c(VkImageAspectFlagBits value) { return static_cast<ImageAspectFlagBits>(value);}
constexpr VkSparseImageFormatFlagBits to_c(SparseImageFormatFlagBits value) { return static_cast<VkSparseImageFormatFlagBits>(value);}
constexpr SparseImageFormatFlagBits from_c(VkSparseImageFormatFlagBits value) { return static_cast<SparseImageFormatFlagBits>(value);}
constexpr VkSparseMemoryBindFlagBits to_c(SparseMemoryBindFlagBits value) { return static_cast<VkSparseMemoryBindFlagBits>(value);}
constexpr SparseMemoryBindFlagBits from_c(VkSparseMemoryBindFlagBits value) { return static_cast<SparseMemoryBindFlagBits>(value);}
constexpr VkPipelineStageFlagBits to_c(PipelineStageFlagBits value) { return static_cast<VkPipelineStageFlagBits>(value);}
constexpr PipelineStageFlagBits from_c(VkPipelineStageFlagBits value) { return static_cast<PipelineStageFlagBits>(value);}
constexpr VkCommandPoolCreateFlagBits to_c(CommandPoolCreateFlagBits value) { return static_cast<VkCommandPoolCreateFlagBits>(value);}
constexpr CommandPoolCreateFlagBits from_c(VkCommandPoolCreateFlagBits value) { return static_cast<CommandPoolCreateFlagBits>(value);}
constexpr VkCommandPoolResetFlagBits to_c(CommandPoolResetFlagBits value) { return static_cast<VkCommandPoolResetFlagBits>(value);}
constexpr CommandPoolResetFlagBits from_c(VkCommandPoolResetFlagBits value) { return static_cast<CommandPoolResetFlagBits>(value);}
constexpr VkCommandBufferResetFlagBits to_c(CommandBufferResetFlagBits value) { return static_cast<VkCommandBufferResetFlagBits>(value);}
constexpr CommandBufferResetFlagBits from_c(VkCommandBufferResetFlagBits value) { return static_cast<CommandBufferResetFlagBits>(value);}
constexpr VkSampleCountFlagBits to_c(SampleCountFlagBits value) { return static_cast<VkSampleCountFlagBits>(value);}
constexpr SampleCountFlagBits from_c(VkSampleCountFlagBits value) { return static_cast<SampleCountFlagBits>(value);}
constexpr VkAttachmentDescriptionFlagBits to_c(AttachmentDescriptionFlagBits value) { return static_cast<VkAttachmentDescriptionFlagBits>(value);}
constexpr AttachmentDescriptionFlagBits from_c(VkAttachmentDescriptionFlagBits value) { return static_cast<AttachmentDescriptionFlagBits>(value);}
constexpr VkStencilFaceFlagBits to_c(StencilFaceFlagBits value) { return static_cast<VkStencilFaceFlagBits>(value);}
constexpr StencilFaceFlagBits from_c(VkStencilFaceFlagBits value) { return static_cast<StencilFaceFlagBits>(value);}
constexpr VkDescriptorPoolCreateFlagBits to_c(DescriptorPoolCreateFlagBits value) { return static_cast<VkDescriptorPoolCreateFlagBits>(value);}
constexpr DescriptorPoolCreateFlagBits from_c(VkDescriptorPoolCreateFlagBits value) { return static_cast<DescriptorPoolCreateFlagBits>(value);}
constexpr VkDependencyFlagBits to_c(DependencyFlagBits value) { return static_cast<VkDependencyFlagBits>(value);}
constexpr DependencyFlagBits from_c(VkDependencyFlagBits value) { return static_cast<DependencyFlagBits>(value);}
constexpr VkSemaphoreWaitFlagBits to_c(SemaphoreWaitFlagBits value) { return static_cast<VkSemaphoreWaitFlagBits>(value);}
constexpr SemaphoreWaitFlagBits from_c(VkSemaphoreWaitFlagBits value) { return static_cast<SemaphoreWaitFlagBits>(value);}
constexpr VkDisplayPlaneAlphaFlagBitsKHR to_c(DisplayPlaneAlphaFlagBitsKHR value) { return static_cast<VkDisplayPlaneAlphaFlagBitsKHR>(value);}
constexpr DisplayPlaneAlphaFlagBitsKHR from_c(VkDisplayPlaneAlphaFlagBitsKHR value) { return static_cast<DisplayPlaneAlphaFlagBitsKHR>(value);}
constexpr VkCompositeAlphaFlagBitsKHR to_c(CompositeAlphaFlagBitsKHR value) { return static_cast<VkCompositeAlphaFlagBitsKHR>(value);}
constexpr CompositeAlphaFlagBitsKHR from_c(VkCompositeAlphaFlagBitsKHR value) { return static_cast<CompositeAlphaFlagBitsKHR>(value);}
constexpr VkSurfaceTransformFlagBitsKHR to_c(SurfaceTransformFlagBitsKHR value) { return static_cast<VkSurfaceTransformFlagBitsKHR>(value);}
constexpr SurfaceTransformFlagBitsKHR from_c(VkSurfaceTransformFlagBitsKHR value) { return static_cast<SurfaceTransformFlagBitsKHR>(value);}
constexpr VkDebugReportFlagBitsEXT to_c(DebugReportFlagBitsEXT value) { return static_cast<VkDebugReportFlagBitsEXT>(value);}
constexpr DebugReportFlagBitsEXT from_c(VkDebugReportFlagBitsEXT value) { return static_cast<DebugReportFlagBitsEXT>(value);}
constexpr VkExternalMemoryHandleTypeFlagBitsNV to_c(ExternalMemoryHandleTypeFlagBitsNV value) { return static_cast<VkExternalMemoryHandleTypeFlagBitsNV>(value);}
constexpr ExternalMemoryHandleTypeFlagBitsNV from_c(VkExternalMemoryHandleTypeFlagBitsNV value) { return static_cast<ExternalMemoryHandleTypeFlagBitsNV>(value);}
constexpr VkExternalMemoryFeatureFlagBitsNV to_c(ExternalMemoryFeatureFlagBitsNV value) { return static_cast<VkExternalMemoryFeatureFlagBitsNV>(value);}
constexpr ExternalMemoryFeatureFlagBitsNV from_c(VkExternalMemoryFeatureFlagBitsNV value) { return static_cast<ExternalMemoryFeatureFlagBitsNV>(value);}
constexpr VkSubgroupFeatureFlagBits to_c(SubgroupFeatureFlagBits value) { return static_cast<VkSubgroupFeatureFlagBits>(value);}
constexpr SubgroupFeatureFlagBits from_c(VkSubgroupFeatureFlagBits value) { return static_cast<SubgroupFeatureFlagBits>(value);}
constexpr VkIndirectCommandsLayoutUsageFlagBitsNV to_c(IndirectCommandsLayoutUsageFlagBitsNV value) { return static_cast<VkIndirectCommandsLayoutUsageFlagBitsNV>(value);}
constexpr IndirectCommandsLayoutUsageFlagBitsNV from_c(VkIndirectCommandsLayoutUsageFlagBitsNV value) { return static_cast<IndirectCommandsLayoutUsageFlagBitsNV>(value);}
constexpr VkIndirectStateFlagBitsNV to_c(IndirectStateFlagBitsNV value) { return static_cast<VkIndirectStateFlagBitsNV>(value);}
constexpr IndirectStateFlagBitsNV from_c(VkIndirectStateFlagBitsNV value) { return static_cast<IndirectStateFlagBitsNV>(value);}
constexpr VkPrivateDataSlotCreateFlagBitsEXT to_c(PrivateDataSlotCreateFlagBitsEXT value) { return static_cast<VkPrivateDataSlotCreateFlagBitsEXT>(value);}
constexpr PrivateDataSlotCreateFlagBitsEXT from_c(VkPrivateDataSlotCreateFlagBitsEXT value) { return static_cast<PrivateDataSlotCreateFlagBitsEXT>(value);}
constexpr VkDescriptorSetLayoutCreateFlagBits to_c(DescriptorSetLayoutCreateFlagBits value) { return static_cast<VkDescriptorSetLayoutCreateFlagBits>(value);}
constexpr DescriptorSetLayoutCreateFlagBits from_c(VkDescriptorSetLayoutCreateFlagBits value) { return static_cast<DescriptorSetLayoutCreateFlagBits>(value);}
constexpr VkExternalMemoryHandleTypeFlagBits to_c(ExternalMemoryHandleTypeFlagBits value) { return static_cast<VkExternalMemoryHandleTypeFlagBits>(value);}
constexpr ExternalMemoryHandleTypeFlagBits from_c(VkExternalMemoryHandleTypeFlagBits value) { return static_cast<ExternalMemoryHandleTypeFlagBits>(value);}
constexpr VkExternalMemoryFeatureFlagBits to_c(ExternalMemoryFeatureFlagBits value) { return static_cast<VkExternalMemoryFeatureFlagBits>(value);}
constexpr ExternalMemoryFeatureFlagBits from_c(VkExternalMemoryFeatureFlagBits value) { return static_cast<ExternalMemoryFeatureFlagBits>(value);}
constexpr VkExternalSemaphoreHandleTypeFlagBits to_c(ExternalSemaphoreHandleTypeFlagBits value) { return static_cast<VkExternalSemaphoreHandleTypeFlagBits>(value);}
constexpr ExternalSemaphoreHandleTypeFlagBits from_c(VkExternalSemaphoreHandleTypeFlagBits value) { return static_cast<ExternalSemaphoreHandleTypeFlagBits>(value);}
constexpr VkExternalSemaphoreFeatureFlagBits to_c(ExternalSemaphoreFeatureFlagBits value) { return static_cast<VkExternalSemaphoreFeatureFlagBits>(value);}
constexpr ExternalSemaphoreFeatureFlagBits from_c(VkExternalSemaphoreFeatureFlagBits value) { return static_cast<ExternalSemaphoreFeatureFlagBits>(value);}
constexpr VkSemaphoreImportFlagBits to_c(SemaphoreImportFlagBits value) { return static_cast<VkSemaphoreImportFlagBits>(value);}
constexpr SemaphoreImportFlagBits from_c(VkSemaphoreImportFlagBits value) { return static_cast<SemaphoreImportFlagBits>(value);}
constexpr VkExternalFenceHandleTypeFlagBits to_c(ExternalFenceHandleTypeFlagBits value) { return static_cast<VkExternalFenceHandleTypeFlagBits>(value);}
constexpr ExternalFenceHandleTypeFlagBits from_c(VkExternalFenceHandleTypeFlagBits value) { return static_cast<ExternalFenceHandleTypeFlagBits>(value);}
constexpr VkExternalFenceFeatureFlagBits to_c(ExternalFenceFeatureFlagBits value) { return static_cast<VkExternalFenceFeatureFlagBits>(value);}
constexpr ExternalFenceFeatureFlagBits from_c(VkExternalFenceFeatureFlagBits value) { return static_cast<ExternalFenceFeatureFlagBits>(value);}
constexpr VkFenceImportFlagBits to_c(FenceImportFlagBits value) { return static_cast<VkFenceImportFlagBits>(value);}
constexpr FenceImportFlagBits from_c(VkFenceImportFlagBits value) { return static_cast<FenceImportFlagBits>(value);}
constexpr VkSurfaceCounterFlagBitsEXT to_c(SurfaceCounterFlagBitsEXT value) { return static_cast<VkSurfaceCounterFlagBitsEXT>(value);}
constexpr SurfaceCounterFlagBitsEXT from_c(VkSurfaceCounterFlagBitsEXT value) { return static_cast<SurfaceCounterFlagBitsEXT>(value);}
constexpr VkPeerMemoryFeatureFlagBits to_c(PeerMemoryFeatureFlagBits value) { return static_cast<VkPeerMemoryFeatureFlagBits>(value);}
constexpr PeerMemoryFeatureFlagBits from_c(VkPeerMemoryFeatureFlagBits value) { return static_cast<PeerMemoryFeatureFlagBits>(value);}
constexpr VkMemoryAllocateFlagBits to_c(MemoryAllocateFlagBits value) { return static_cast<VkMemoryAllocateFlagBits>(value);}
constexpr MemoryAllocateFlagBits from_c(VkMemoryAllocateFlagBits value) { return static_cast<MemoryAllocateFlagBits>(value);}
constexpr VkDeviceGroupPresentModeFlagBitsKHR to_c(DeviceGroupPresentModeFlagBitsKHR value) { return static_cast<VkDeviceGroupPresentModeFlagBitsKHR>(value);}
constexpr DeviceGroupPresentModeFlagBitsKHR from_c(VkDeviceGroupPresentModeFlagBitsKHR value) { return static_cast<DeviceGroupPresentModeFlagBitsKHR>(value);}
constexpr VkSwapchainCreateFlagBitsKHR to_c(SwapchainCreateFlagBitsKHR value) { return static_cast<VkSwapchainCreateFlagBitsKHR>(value);}
constexpr SwapchainCreateFlagBitsKHR from_c(VkSwapchainCreateFlagBitsKHR value) { return static_cast<SwapchainCreateFlagBitsKHR>(value);}
constexpr VkSubpassDescriptionFlagBits to_c(SubpassDescriptionFlagBits value) { return static_cast<VkSubpassDescriptionFlagBits>(value);}
constexpr SubpassDescriptionFlagBits from_c(VkSubpassDescriptionFlagBits value) { return static_cast<SubpassDescriptionFlagBits>(value);}
constexpr VkDebugUtilsMessageSeverityFlagBitsEXT to_c(DebugUtilsMessageSeverityFlagBitsEXT value) { return static_cast<VkDebugUtilsMessageSeverityFlagBitsEXT>(value);}
constexpr DebugUtilsMessageSeverityFlagBitsEXT from_c(VkDebugUtilsMessageSeverityFlagBitsEXT value) { return static_cast<DebugUtilsMessageSeverityFlagBitsEXT>(value);}
constexpr VkDebugUtilsMessageTypeFlagBitsEXT to_c(DebugUtilsMessageTypeFlagBitsEXT value) { return static_cast<VkDebugUtilsMessageTypeFlagBitsEXT>(value);}
constexpr DebugUtilsMessageTypeFlagBitsEXT from_c(VkDebugUtilsMessageTypeFlagBitsEXT value) { return static_cast<DebugUtilsMessageTypeFlagBitsEXT>(value);}
constexpr VkDescriptorBindingFlagBits to_c(DescriptorBindingFlagBits value) { return static_cast<VkDescriptorBindingFlagBits>(value);}
constexpr DescriptorBindingFlagBits from_c(VkDescriptorBindingFlagBits value) { return static_cast<DescriptorBindingFlagBits>(value);}
constexpr VkConditionalRenderingFlagBitsEXT to_c(ConditionalRenderingFlagBitsEXT value) { return static_cast<VkConditionalRenderingFlagBitsEXT>(value);}
constexpr ConditionalRenderingFlagBitsEXT from_c(VkConditionalRenderingFlagBitsEXT value) { return static_cast<ConditionalRenderingFlagBitsEXT>(value);}
constexpr VkResolveModeFlagBits to_c(ResolveModeFlagBits value) { return static_cast<VkResolveModeFlagBits>(value);}
constexpr ResolveModeFlagBits from_c(VkResolveModeFlagBits value) { return static_cast<ResolveModeFlagBits>(value);}
constexpr VkGeometryInstanceFlagBitsKHR to_c(GeometryInstanceFlagBitsKHR value) { return static_cast<VkGeometryInstanceFlagBitsKHR>(value);}
constexpr GeometryInstanceFlagBitsKHR from_c(VkGeometryInstanceFlagBitsKHR value) { return static_cast<GeometryInstanceFlagBitsKHR>(value);}
constexpr VkGeometryFlagBitsKHR to_c(GeometryFlagBitsKHR value) { return static_cast<VkGeometryFlagBitsKHR>(value);}
constexpr GeometryFlagBitsKHR from_c(VkGeometryFlagBitsKHR value) { return static_cast<GeometryFlagBitsKHR>(value);}
constexpr VkBuildAccelerationStructureFlagBitsKHR to_c(BuildAccelerationStructureFlagBitsKHR value) { return static_cast<VkBuildAccelerationStructureFlagBitsKHR>(value);}
constexpr BuildAccelerationStructureFlagBitsKHR from_c(VkBuildAccelerationStructureFlagBitsKHR value) { return static_cast<BuildAccelerationStructureFlagBitsKHR>(value);}
constexpr VkAccelerationStructureCreateFlagBitsKHR to_c(AccelerationStructureCreateFlagBitsKHR value) { return static_cast<VkAccelerationStructureCreateFlagBitsKHR>(value);}
constexpr AccelerationStructureCreateFlagBitsKHR from_c(VkAccelerationStructureCreateFlagBitsKHR value) { return static_cast<AccelerationStructureCreateFlagBitsKHR>(value);}
constexpr VkFramebufferCreateFlagBits to_c(FramebufferCreateFlagBits value) { return static_cast<VkFramebufferCreateFlagBits>(value);}
constexpr FramebufferCreateFlagBits from_c(VkFramebufferCreateFlagBits value) { return static_cast<FramebufferCreateFlagBits>(value);}
constexpr VkDeviceDiagnosticsConfigFlagBitsNV to_c(DeviceDiagnosticsConfigFlagBitsNV value) { return static_cast<VkDeviceDiagnosticsConfigFlagBitsNV>(value);}
constexpr DeviceDiagnosticsConfigFlagBitsNV from_c(VkDeviceDiagnosticsConfigFlagBitsNV value) { return static_cast<DeviceDiagnosticsConfigFlagBitsNV>(value);}
constexpr VkPipelineCreationFeedbackFlagBitsEXT to_c(PipelineCreationFeedbackFlagBitsEXT value) { return static_cast<VkPipelineCreationFeedbackFlagBitsEXT>(value);}
constexpr PipelineCreationFeedbackFlagBitsEXT from_c(VkPipelineCreationFeedbackFlagBitsEXT value) { return static_cast<PipelineCreationFeedbackFlagBitsEXT>(value);}
constexpr VkPerformanceCounterDescriptionFlagBitsKHR to_c(PerformanceCounterDescriptionFlagBitsKHR value) { return static_cast<VkPerformanceCounterDescriptionFlagBitsKHR>(value);}
constexpr PerformanceCounterDescriptionFlagBitsKHR from_c(VkPerformanceCounterDescriptionFlagBitsKHR value) { return static_cast<PerformanceCounterDescriptionFlagBitsKHR>(value);}
constexpr VkAcquireProfilingLockFlagBitsKHR to_c(AcquireProfilingLockFlagBitsKHR value) { return static_cast<VkAcquireProfilingLockFlagBitsKHR>(value);}
constexpr AcquireProfilingLockFlagBitsKHR from_c(VkAcquireProfilingLockFlagBitsKHR value) { return static_cast<AcquireProfilingLockFlagBitsKHR>(value);}
constexpr VkShaderCorePropertiesFlagBitsAMD to_c(ShaderCorePropertiesFlagBitsAMD value) { return static_cast<VkShaderCorePropertiesFlagBitsAMD>(value);}
constexpr ShaderCorePropertiesFlagBitsAMD from_c(VkShaderCorePropertiesFlagBitsAMD value) { return static_cast<ShaderCorePropertiesFlagBitsAMD>(value);}
constexpr VkShaderModuleCreateFlagBits to_c(ShaderModuleCreateFlagBits value) { return static_cast<VkShaderModuleCreateFlagBits>(value);}
constexpr ShaderModuleCreateFlagBits from_c(VkShaderModuleCreateFlagBits value) { return static_cast<ShaderModuleCreateFlagBits>(value);}
constexpr VkPipelineCompilerControlFlagBitsAMD to_c(PipelineCompilerControlFlagBitsAMD value) { return static_cast<VkPipelineCompilerControlFlagBitsAMD>(value);}
constexpr PipelineCompilerControlFlagBitsAMD from_c(VkPipelineCompilerControlFlagBitsAMD value) { return static_cast<PipelineCompilerControlFlagBitsAMD>(value);}
constexpr VkToolPurposeFlagBitsEXT to_c(ToolPurposeFlagBitsEXT value) { return static_cast<VkToolPurposeFlagBitsEXT>(value);}
constexpr ToolPurposeFlagBitsEXT from_c(VkToolPurposeFlagBitsEXT value) { return static_cast<ToolPurposeFlagBitsEXT>(value);}
constexpr VkAccessFlagBits2KHR to_c(AccessFlagBits2KHR value) { return static_cast<VkAccessFlagBits2KHR>(value);}
constexpr AccessFlagBits2KHR from_c(VkAccessFlagBits2KHR value) { return static_cast<AccessFlagBits2KHR>(value);}
constexpr VkPipelineStageFlagBits2KHR to_c(PipelineStageFlagBits2KHR value) { return static_cast<VkPipelineStageFlagBits2KHR>(value);}
constexpr PipelineStageFlagBits2KHR from_c(VkPipelineStageFlagBits2KHR value) { return static_cast<PipelineStageFlagBits2KHR>(value);}
constexpr VkSubmitFlagBitsKHR to_c(SubmitFlagBitsKHR value) { return static_cast<VkSubmitFlagBitsKHR>(value);}
constexpr SubmitFlagBitsKHR from_c(VkSubmitFlagBitsKHR value) { return static_cast<SubmitFlagBitsKHR>(value);}
constexpr VkEventCreateFlagBits to_c(EventCreateFlagBits value) { return static_cast<VkEventCreateFlagBits>(value);}
constexpr EventCreateFlagBits from_c(VkEventCreateFlagBits value) { return static_cast<EventCreateFlagBits>(value);}
constexpr VkPipelineLayoutCreateFlagBits to_c(PipelineLayoutCreateFlagBits value) { return static_cast<VkPipelineLayoutCreateFlagBits>(value);}
constexpr PipelineLayoutCreateFlagBits from_c(VkPipelineLayoutCreateFlagBits value) { return static_cast<PipelineLayoutCreateFlagBits>(value);}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
constexpr VkVideoCodecOperationFlagBitsKHR to_c(VideoCodecOperationFlagBitsKHR value) { return static_cast<VkVideoCodecOperationFlagBitsKHR>(value);}
constexpr VideoCodecOperationFlagBitsKHR from_c(VkVideoCodecOperationFlagBitsKHR value) { return static_cast<VideoCodecOperationFlagBitsKHR>(value);}
constexpr VkVideoChromaSubsamplingFlagBitsKHR to_c(VideoChromaSubsamplingFlagBitsKHR value) { return static_cast<VkVideoChromaSubsamplingFlagBitsKHR>(value);}
constexpr VideoChromaSubsamplingFlagBitsKHR from_c(VkVideoChromaSubsamplingFlagBitsKHR value) { return static_cast<VideoChromaSubsamplingFlagBitsKHR>(value);}
constexpr VkVideoComponentBitDepthFlagBitsKHR to_c(VideoComponentBitDepthFlagBitsKHR value) { return static_cast<VkVideoComponentBitDepthFlagBitsKHR>(value);}
constexpr VideoComponentBitDepthFlagBitsKHR from_c(VkVideoComponentBitDepthFlagBitsKHR value) { return static_cast<VideoComponentBitDepthFlagBitsKHR>(value);}
constexpr VkVideoCapabilityFlagBitsKHR to_c(VideoCapabilityFlagBitsKHR value) { return static_cast<VkVideoCapabilityFlagBitsKHR>(value);}
constexpr VideoCapabilityFlagBitsKHR from_c(VkVideoCapabilityFlagBitsKHR value) { return static_cast<VideoCapabilityFlagBitsKHR>(value);}
constexpr VkVideoSessionCreateFlagBitsKHR to_c(VideoSessionCreateFlagBitsKHR value) { return static_cast<VkVideoSessionCreateFlagBitsKHR>(value);}
constexpr VideoSessionCreateFlagBitsKHR from_c(VkVideoSessionCreateFlagBitsKHR value) { return static_cast<VideoSessionCreateFlagBitsKHR>(value);}
constexpr VkVideoCodingQualityPresetFlagBitsKHR to_c(VideoCodingQualityPresetFlagBitsKHR value) { return static_cast<VkVideoCodingQualityPresetFlagBitsKHR>(value);}
constexpr VideoCodingQualityPresetFlagBitsKHR from_c(VkVideoCodingQualityPresetFlagBitsKHR value) { return static_cast<VideoCodingQualityPresetFlagBitsKHR>(value);}
constexpr VkVideoDecodeH264PictureLayoutFlagBitsEXT to_c(VideoDecodeH264PictureLayoutFlagBitsEXT value) { return static_cast<VkVideoDecodeH264PictureLayoutFlagBitsEXT>(value);}
constexpr VideoDecodeH264PictureLayoutFlagBitsEXT from_c(VkVideoDecodeH264PictureLayoutFlagBitsEXT value) { return static_cast<VideoDecodeH264PictureLayoutFlagBitsEXT>(value);}
constexpr VkVideoCodingControlFlagBitsKHR to_c(VideoCodingControlFlagBitsKHR value) { return static_cast<VkVideoCodingControlFlagBitsKHR>(value);}
constexpr VideoCodingControlFlagBitsKHR from_c(VkVideoCodingControlFlagBitsKHR value) { return static_cast<VideoCodingControlFlagBitsKHR>(value);}
constexpr VkVideoDecodeFlagBitsKHR to_c(VideoDecodeFlagBitsKHR value) { return static_cast<VkVideoDecodeFlagBitsKHR>(value);}
constexpr VideoDecodeFlagBitsKHR from_c(VkVideoDecodeFlagBitsKHR value) { return static_cast<VideoDecodeFlagBitsKHR>(value);}
constexpr VkVideoEncodeFlagBitsKHR to_c(VideoEncodeFlagBitsKHR value) { return static_cast<VkVideoEncodeFlagBitsKHR>(value);}
constexpr VideoEncodeFlagBitsKHR from_c(VkVideoEncodeFlagBitsKHR value) { return static_cast<VideoEncodeFlagBitsKHR>(value);}
constexpr VkVideoEncodeRateControlFlagBitsKHR to_c(VideoEncodeRateControlFlagBitsKHR value) { return static_cast<VkVideoEncodeRateControlFlagBitsKHR>(value);}
constexpr VideoEncodeRateControlFlagBitsKHR from_c(VkVideoEncodeRateControlFlagBitsKHR value) { return static_cast<VideoEncodeRateControlFlagBitsKHR>(value);}
constexpr VkVideoEncodeRateControlModeFlagBitsKHR to_c(VideoEncodeRateControlModeFlagBitsKHR value) { return static_cast<VkVideoEncodeRateControlModeFlagBitsKHR>(value);}
constexpr VideoEncodeRateControlModeFlagBitsKHR from_c(VkVideoEncodeRateControlModeFlagBitsKHR value) { return static_cast<VideoEncodeRateControlModeFlagBitsKHR>(value);}
constexpr VkVideoEncodeH264CapabilityFlagBitsEXT to_c(VideoEncodeH264CapabilityFlagBitsEXT value) { return static_cast<VkVideoEncodeH264CapabilityFlagBitsEXT>(value);}
constexpr VideoEncodeH264CapabilityFlagBitsEXT from_c(VkVideoEncodeH264CapabilityFlagBitsEXT value) { return static_cast<VideoEncodeH264CapabilityFlagBitsEXT>(value);}
constexpr VkVideoEncodeH264InputModeFlagBitsEXT to_c(VideoEncodeH264InputModeFlagBitsEXT value) { return static_cast<VkVideoEncodeH264InputModeFlagBitsEXT>(value);}
constexpr VideoEncodeH264InputModeFlagBitsEXT from_c(VkVideoEncodeH264InputModeFlagBitsEXT value) { return static_cast<VideoEncodeH264InputModeFlagBitsEXT>(value);}
constexpr VkVideoEncodeH264OutputModeFlagBitsEXT to_c(VideoEncodeH264OutputModeFlagBitsEXT value) { return static_cast<VkVideoEncodeH264OutputModeFlagBitsEXT>(value);}
constexpr VideoEncodeH264OutputModeFlagBitsEXT from_c(VkVideoEncodeH264OutputModeFlagBitsEXT value) { return static_cast<VideoEncodeH264OutputModeFlagBitsEXT>(value);}
constexpr VkVideoEncodeH264CreateFlagBitsEXT to_c(VideoEncodeH264CreateFlagBitsEXT value) { return static_cast<VkVideoEncodeH264CreateFlagBitsEXT>(value);}
constexpr VideoEncodeH264CreateFlagBitsEXT from_c(VkVideoEncodeH264CreateFlagBitsEXT value) { return static_cast<VideoEncodeH264CreateFlagBitsEXT>(value);}
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_USE_PLATFORM_FUCHSIA)
constexpr VkImageFormatConstraintsFlagBitsFUCHSIA to_c(ImageFormatConstraintsFlagBitsFUCHSIA value) { return static_cast<VkImageFormatConstraintsFlagBitsFUCHSIA>(value);}
constexpr ImageFormatConstraintsFlagBitsFUCHSIA from_c(VkImageFormatConstraintsFlagBitsFUCHSIA value) { return static_cast<ImageFormatConstraintsFlagBitsFUCHSIA>(value);}
constexpr VkImageConstraintsInfoFlagBitsFUCHSIA to_c(ImageConstraintsInfoFlagBitsFUCHSIA value) { return static_cast<VkImageConstraintsInfoFlagBitsFUCHSIA>(value);}
constexpr ImageConstraintsInfoFlagBitsFUCHSIA from_c(VkImageConstraintsInfoFlagBitsFUCHSIA value) { return static_cast<ImageConstraintsInfoFlagBitsFUCHSIA>(value);}
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
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
constexpr VkFramebufferCreateFlags to_c(FramebufferCreateFlags value) { return static_cast<VkFramebufferCreateFlags>(value.flags);}
constexpr VkQueryPoolCreateFlags to_c(QueryPoolCreateFlags value) { return static_cast<VkQueryPoolCreateFlags>(value.flags);}
constexpr VkRenderPassCreateFlags to_c(RenderPassCreateFlags value) { return static_cast<VkRenderPassCreateFlags>(value.flags);}
constexpr VkSamplerCreateFlags to_c(SamplerCreateFlags value) { return static_cast<VkSamplerCreateFlags>(value.flags);}
constexpr VkPipelineLayoutCreateFlags to_c(PipelineLayoutCreateFlags value) { return static_cast<VkPipelineLayoutCreateFlags>(value.flags);}
constexpr VkPipelineCacheCreateFlags to_c(PipelineCacheCreateFlags value) { return static_cast<VkPipelineCacheCreateFlags>(value.flags);}
constexpr VkPipelineDepthStencilStateCreateFlags to_c(PipelineDepthStencilStateCreateFlags value) { return static_cast<VkPipelineDepthStencilStateCreateFlags>(value.flags);}
constexpr VkPipelineDynamicStateCreateFlags to_c(PipelineDynamicStateCreateFlags value) { return static_cast<VkPipelineDynamicStateCreateFlags>(value.flags);}
constexpr VkPipelineColorBlendStateCreateFlags to_c(PipelineColorBlendStateCreateFlags value) { return static_cast<VkPipelineColorBlendStateCreateFlags>(value.flags);}
constexpr VkPipelineMultisampleStateCreateFlags to_c(PipelineMultisampleStateCreateFlags value) { return static_cast<VkPipelineMultisampleStateCreateFlags>(value.flags);}
constexpr VkPipelineRasterizationStateCreateFlags to_c(PipelineRasterizationStateCreateFlags value) { return static_cast<VkPipelineRasterizationStateCreateFlags>(value.flags);}
constexpr VkPipelineViewportStateCreateFlags to_c(PipelineViewportStateCreateFlags value) { return static_cast<VkPipelineViewportStateCreateFlags>(value.flags);}
constexpr VkPipelineTessellationStateCreateFlags to_c(PipelineTessellationStateCreateFlags value) { return static_cast<VkPipelineTessellationStateCreateFlags>(value.flags);}
constexpr VkPipelineInputAssemblyStateCreateFlags to_c(PipelineInputAssemblyStateCreateFlags value) { return static_cast<VkPipelineInputAssemblyStateCreateFlags>(value.flags);}
constexpr VkPipelineVertexInputStateCreateFlags to_c(PipelineVertexInputStateCreateFlags value) { return static_cast<VkPipelineVertexInputStateCreateFlags>(value.flags);}
constexpr VkPipelineShaderStageCreateFlags to_c(PipelineShaderStageCreateFlags value) { return static_cast<VkPipelineShaderStageCreateFlags>(value.flags);}
constexpr VkDescriptorSetLayoutCreateFlags to_c(DescriptorSetLayoutCreateFlags value) { return static_cast<VkDescriptorSetLayoutCreateFlags>(value.flags);}
constexpr VkBufferViewCreateFlags to_c(BufferViewCreateFlags value) { return static_cast<VkBufferViewCreateFlags>(value.flags);}
constexpr VkInstanceCreateFlags to_c(InstanceCreateFlags value) { return static_cast<VkInstanceCreateFlags>(value.flags);}
constexpr VkDeviceCreateFlags to_c(DeviceCreateFlags value) { return static_cast<VkDeviceCreateFlags>(value.flags);}
constexpr VkDeviceQueueCreateFlags to_c(DeviceQueueCreateFlags value) { return static_cast<VkDeviceQueueCreateFlags>(value.flags);}
constexpr VkQueueFlags to_c(QueueFlags value) { return static_cast<VkQueueFlags>(value.flags);}
constexpr VkMemoryPropertyFlags to_c(MemoryPropertyFlags value) { return static_cast<VkMemoryPropertyFlags>(value.flags);}
constexpr VkMemoryHeapFlags to_c(MemoryHeapFlags value) { return static_cast<VkMemoryHeapFlags>(value.flags);}
constexpr VkAccessFlags to_c(AccessFlags value) { return static_cast<VkAccessFlags>(value.flags);}
constexpr VkBufferUsageFlags to_c(BufferUsageFlags value) { return static_cast<VkBufferUsageFlags>(value.flags);}
constexpr VkBufferCreateFlags to_c(BufferCreateFlags value) { return static_cast<VkBufferCreateFlags>(value.flags);}
constexpr VkShaderStageFlags to_c(ShaderStageFlags value) { return static_cast<VkShaderStageFlags>(value.flags);}
constexpr VkImageUsageFlags to_c(ImageUsageFlags value) { return static_cast<VkImageUsageFlags>(value.flags);}
constexpr VkImageCreateFlags to_c(ImageCreateFlags value) { return static_cast<VkImageCreateFlags>(value.flags);}
constexpr VkImageViewCreateFlags to_c(ImageViewCreateFlags value) { return static_cast<VkImageViewCreateFlags>(value.flags);}
constexpr VkPipelineCreateFlags to_c(PipelineCreateFlags value) { return static_cast<VkPipelineCreateFlags>(value.flags);}
constexpr VkColorComponentFlags to_c(ColorComponentFlags value) { return static_cast<VkColorComponentFlags>(value.flags);}
constexpr VkFenceCreateFlags to_c(FenceCreateFlags value) { return static_cast<VkFenceCreateFlags>(value.flags);}
constexpr VkSemaphoreCreateFlags to_c(SemaphoreCreateFlags value) { return static_cast<VkSemaphoreCreateFlags>(value.flags);}
constexpr VkFormatFeatureFlags to_c(FormatFeatureFlags value) { return static_cast<VkFormatFeatureFlags>(value.flags);}
constexpr VkQueryControlFlags to_c(QueryControlFlags value) { return static_cast<VkQueryControlFlags>(value.flags);}
constexpr VkQueryResultFlags to_c(QueryResultFlags value) { return static_cast<VkQueryResultFlags>(value.flags);}
constexpr VkShaderModuleCreateFlags to_c(ShaderModuleCreateFlags value) { return static_cast<VkShaderModuleCreateFlags>(value.flags);}
constexpr VkEventCreateFlags to_c(EventCreateFlags value) { return static_cast<VkEventCreateFlags>(value.flags);}
constexpr VkCommandPoolCreateFlags to_c(CommandPoolCreateFlags value) { return static_cast<VkCommandPoolCreateFlags>(value.flags);}
constexpr VkCommandPoolResetFlags to_c(CommandPoolResetFlags value) { return static_cast<VkCommandPoolResetFlags>(value.flags);}
constexpr VkCommandBufferResetFlags to_c(CommandBufferResetFlags value) { return static_cast<VkCommandBufferResetFlags>(value.flags);}
constexpr VkCommandBufferUsageFlags to_c(CommandBufferUsageFlags value) { return static_cast<VkCommandBufferUsageFlags>(value.flags);}
constexpr VkQueryPipelineStatisticFlags to_c(QueryPipelineStatisticFlags value) { return static_cast<VkQueryPipelineStatisticFlags>(value.flags);}
constexpr VkMemoryMapFlags to_c(MemoryMapFlags value) { return static_cast<VkMemoryMapFlags>(value.flags);}
constexpr VkImageAspectFlags to_c(ImageAspectFlags value) { return static_cast<VkImageAspectFlags>(value.flags);}
constexpr VkSparseMemoryBindFlags to_c(SparseMemoryBindFlags value) { return static_cast<VkSparseMemoryBindFlags>(value.flags);}
constexpr VkSparseImageFormatFlags to_c(SparseImageFormatFlags value) { return static_cast<VkSparseImageFormatFlags>(value.flags);}
constexpr VkSubpassDescriptionFlags to_c(SubpassDescriptionFlags value) { return static_cast<VkSubpassDescriptionFlags>(value.flags);}
constexpr VkPipelineStageFlags to_c(PipelineStageFlags value) { return static_cast<VkPipelineStageFlags>(value.flags);}
constexpr VkSampleCountFlags to_c(SampleCountFlags value) { return static_cast<VkSampleCountFlags>(value.flags);}
constexpr VkAttachmentDescriptionFlags to_c(AttachmentDescriptionFlags value) { return static_cast<VkAttachmentDescriptionFlags>(value.flags);}
constexpr VkStencilFaceFlags to_c(StencilFaceFlags value) { return static_cast<VkStencilFaceFlags>(value.flags);}
constexpr VkCullModeFlags to_c(CullModeFlags value) { return static_cast<VkCullModeFlags>(value.flags);}
constexpr VkDescriptorPoolCreateFlags to_c(DescriptorPoolCreateFlags value) { return static_cast<VkDescriptorPoolCreateFlags>(value.flags);}
constexpr VkDescriptorPoolResetFlags to_c(DescriptorPoolResetFlags value) { return static_cast<VkDescriptorPoolResetFlags>(value.flags);}
constexpr VkDependencyFlags to_c(DependencyFlags value) { return static_cast<VkDependencyFlags>(value.flags);}
constexpr VkSubgroupFeatureFlags to_c(SubgroupFeatureFlags value) { return static_cast<VkSubgroupFeatureFlags>(value.flags);}
constexpr VkIndirectCommandsLayoutUsageFlagsNV to_c(IndirectCommandsLayoutUsageFlagsNV value) { return static_cast<VkIndirectCommandsLayoutUsageFlagsNV>(value.flags);}
constexpr VkIndirectStateFlagsNV to_c(IndirectStateFlagsNV value) { return static_cast<VkIndirectStateFlagsNV>(value.flags);}
constexpr VkGeometryFlagsKHR to_c(GeometryFlagsKHR value) { return static_cast<VkGeometryFlagsKHR>(value.flags);}
constexpr VkGeometryInstanceFlagsKHR to_c(GeometryInstanceFlagsKHR value) { return static_cast<VkGeometryInstanceFlagsKHR>(value.flags);}
constexpr VkBuildAccelerationStructureFlagsKHR to_c(BuildAccelerationStructureFlagsKHR value) { return static_cast<VkBuildAccelerationStructureFlagsKHR>(value.flags);}
constexpr VkPrivateDataSlotCreateFlagsEXT to_c(PrivateDataSlotCreateFlagsEXT value) { return static_cast<VkPrivateDataSlotCreateFlagsEXT>(value.flags);}
constexpr VkAccelerationStructureCreateFlagsKHR to_c(AccelerationStructureCreateFlagsKHR value) { return static_cast<VkAccelerationStructureCreateFlagsKHR>(value.flags);}
constexpr VkDescriptorUpdateTemplateCreateFlags to_c(DescriptorUpdateTemplateCreateFlags value) { return static_cast<VkDescriptorUpdateTemplateCreateFlags>(value.flags);}
constexpr VkPipelineCreationFeedbackFlagsEXT to_c(PipelineCreationFeedbackFlagsEXT value) { return static_cast<VkPipelineCreationFeedbackFlagsEXT>(value.flags);}
constexpr VkPerformanceCounterDescriptionFlagsKHR to_c(PerformanceCounterDescriptionFlagsKHR value) { return static_cast<VkPerformanceCounterDescriptionFlagsKHR>(value.flags);}
constexpr VkAcquireProfilingLockFlagsKHR to_c(AcquireProfilingLockFlagsKHR value) { return static_cast<VkAcquireProfilingLockFlagsKHR>(value.flags);}
constexpr VkSemaphoreWaitFlags to_c(SemaphoreWaitFlags value) { return static_cast<VkSemaphoreWaitFlags>(value.flags);}
constexpr VkPipelineCompilerControlFlagsAMD to_c(PipelineCompilerControlFlagsAMD value) { return static_cast<VkPipelineCompilerControlFlagsAMD>(value.flags);}
constexpr VkShaderCorePropertiesFlagsAMD to_c(ShaderCorePropertiesFlagsAMD value) { return static_cast<VkShaderCorePropertiesFlagsAMD>(value.flags);}
constexpr VkDeviceDiagnosticsConfigFlagsNV to_c(DeviceDiagnosticsConfigFlagsNV value) { return static_cast<VkDeviceDiagnosticsConfigFlagsNV>(value.flags);}
constexpr VkAccessFlags2KHR to_c(AccessFlags2KHR value) { return static_cast<VkAccessFlags2KHR>(value.flags);}
constexpr VkPipelineStageFlags2KHR to_c(PipelineStageFlags2KHR value) { return static_cast<VkPipelineStageFlags2KHR>(value.flags);}
constexpr VkAccelerationStructureMotionInfoFlagsNV to_c(AccelerationStructureMotionInfoFlagsNV value) { return static_cast<VkAccelerationStructureMotionInfoFlagsNV>(value.flags);}
constexpr VkAccelerationStructureMotionInstanceFlagsNV to_c(AccelerationStructureMotionInstanceFlagsNV value) { return static_cast<VkAccelerationStructureMotionInstanceFlagsNV>(value.flags);}
constexpr VkCompositeAlphaFlagsKHR to_c(CompositeAlphaFlagsKHR value) { return static_cast<VkCompositeAlphaFlagsKHR>(value.flags);}
constexpr VkDisplayPlaneAlphaFlagsKHR to_c(DisplayPlaneAlphaFlagsKHR value) { return static_cast<VkDisplayPlaneAlphaFlagsKHR>(value.flags);}
constexpr VkSurfaceTransformFlagsKHR to_c(SurfaceTransformFlagsKHR value) { return static_cast<VkSurfaceTransformFlagsKHR>(value.flags);}
constexpr VkSwapchainCreateFlagsKHR to_c(SwapchainCreateFlagsKHR value) { return static_cast<VkSwapchainCreateFlagsKHR>(value.flags);}
constexpr VkDisplayModeCreateFlagsKHR to_c(DisplayModeCreateFlagsKHR value) { return static_cast<VkDisplayModeCreateFlagsKHR>(value.flags);}
constexpr VkDisplaySurfaceCreateFlagsKHR to_c(DisplaySurfaceCreateFlagsKHR value) { return static_cast<VkDisplaySurfaceCreateFlagsKHR>(value.flags);}
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
constexpr VkAndroidSurfaceCreateFlagsKHR to_c(AndroidSurfaceCreateFlagsKHR value) { return static_cast<VkAndroidSurfaceCreateFlagsKHR>(value.flags);}
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
constexpr VkViSurfaceCreateFlagsNN to_c(ViSurfaceCreateFlagsNN value) { return static_cast<VkViSurfaceCreateFlagsNN>(value.flags);}
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
constexpr VkWaylandSurfaceCreateFlagsKHR to_c(WaylandSurfaceCreateFlagsKHR value) { return static_cast<VkWaylandSurfaceCreateFlagsKHR>(value.flags);}
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
constexpr VkWin32SurfaceCreateFlagsKHR to_c(Win32SurfaceCreateFlagsKHR value) { return static_cast<VkWin32SurfaceCreateFlagsKHR>(value.flags);}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
constexpr VkXlibSurfaceCreateFlagsKHR to_c(XlibSurfaceCreateFlagsKHR value) { return static_cast<VkXlibSurfaceCreateFlagsKHR>(value.flags);}
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
constexpr VkXcbSurfaceCreateFlagsKHR to_c(XcbSurfaceCreateFlagsKHR value) { return static_cast<VkXcbSurfaceCreateFlagsKHR>(value.flags);}
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
constexpr VkDirectFBSurfaceCreateFlagsEXT to_c(DirectFBSurfaceCreateFlagsEXT value) { return static_cast<VkDirectFBSurfaceCreateFlagsEXT>(value.flags);}
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
constexpr VkIOSSurfaceCreateFlagsMVK to_c(IOSSurfaceCreateFlagsMVK value) { return static_cast<VkIOSSurfaceCreateFlagsMVK>(value.flags);}
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
constexpr VkMacOSSurfaceCreateFlagsMVK to_c(MacOSSurfaceCreateFlagsMVK value) { return static_cast<VkMacOSSurfaceCreateFlagsMVK>(value.flags);}
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
constexpr VkMetalSurfaceCreateFlagsEXT to_c(MetalSurfaceCreateFlagsEXT value) { return static_cast<VkMetalSurfaceCreateFlagsEXT>(value.flags);}
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
constexpr VkImagePipeSurfaceCreateFlagsFUCHSIA to_c(ImagePipeSurfaceCreateFlagsFUCHSIA value) { return static_cast<VkImagePipeSurfaceCreateFlagsFUCHSIA>(value.flags);}
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
constexpr VkStreamDescriptorSurfaceCreateFlagsGGP to_c(StreamDescriptorSurfaceCreateFlagsGGP value) { return static_cast<VkStreamDescriptorSurfaceCreateFlagsGGP>(value.flags);}
#endif // defined(VK_USE_PLATFORM_GGP)
constexpr VkHeadlessSurfaceCreateFlagsEXT to_c(HeadlessSurfaceCreateFlagsEXT value) { return static_cast<VkHeadlessSurfaceCreateFlagsEXT>(value.flags);}
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
constexpr VkScreenSurfaceCreateFlagsQNX to_c(ScreenSurfaceCreateFlagsQNX value) { return static_cast<VkScreenSurfaceCreateFlagsQNX>(value.flags);}
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
constexpr VkPeerMemoryFeatureFlags to_c(PeerMemoryFeatureFlags value) { return static_cast<VkPeerMemoryFeatureFlags>(value.flags);}
constexpr VkMemoryAllocateFlags to_c(MemoryAllocateFlags value) { return static_cast<VkMemoryAllocateFlags>(value.flags);}
constexpr VkDeviceGroupPresentModeFlagsKHR to_c(DeviceGroupPresentModeFlagsKHR value) { return static_cast<VkDeviceGroupPresentModeFlagsKHR>(value.flags);}
constexpr VkDebugReportFlagsEXT to_c(DebugReportFlagsEXT value) { return static_cast<VkDebugReportFlagsEXT>(value.flags);}
constexpr VkCommandPoolTrimFlags to_c(CommandPoolTrimFlags value) { return static_cast<VkCommandPoolTrimFlags>(value.flags);}
constexpr VkExternalMemoryHandleTypeFlagsNV to_c(ExternalMemoryHandleTypeFlagsNV value) { return static_cast<VkExternalMemoryHandleTypeFlagsNV>(value.flags);}
constexpr VkExternalMemoryFeatureFlagsNV to_c(ExternalMemoryFeatureFlagsNV value) { return static_cast<VkExternalMemoryFeatureFlagsNV>(value.flags);}
constexpr VkExternalMemoryHandleTypeFlags to_c(ExternalMemoryHandleTypeFlags value) { return static_cast<VkExternalMemoryHandleTypeFlags>(value.flags);}
constexpr VkExternalMemoryFeatureFlags to_c(ExternalMemoryFeatureFlags value) { return static_cast<VkExternalMemoryFeatureFlags>(value.flags);}
constexpr VkExternalSemaphoreHandleTypeFlags to_c(ExternalSemaphoreHandleTypeFlags value) { return static_cast<VkExternalSemaphoreHandleTypeFlags>(value.flags);}
constexpr VkExternalSemaphoreFeatureFlags to_c(ExternalSemaphoreFeatureFlags value) { return static_cast<VkExternalSemaphoreFeatureFlags>(value.flags);}
constexpr VkSemaphoreImportFlags to_c(SemaphoreImportFlags value) { return static_cast<VkSemaphoreImportFlags>(value.flags);}
constexpr VkExternalFenceHandleTypeFlags to_c(ExternalFenceHandleTypeFlags value) { return static_cast<VkExternalFenceHandleTypeFlags>(value.flags);}
constexpr VkExternalFenceFeatureFlags to_c(ExternalFenceFeatureFlags value) { return static_cast<VkExternalFenceFeatureFlags>(value.flags);}
constexpr VkFenceImportFlags to_c(FenceImportFlags value) { return static_cast<VkFenceImportFlags>(value.flags);}
constexpr VkSurfaceCounterFlagsEXT to_c(SurfaceCounterFlagsEXT value) { return static_cast<VkSurfaceCounterFlagsEXT>(value.flags);}
constexpr VkPipelineViewportSwizzleStateCreateFlagsNV to_c(PipelineViewportSwizzleStateCreateFlagsNV value) { return static_cast<VkPipelineViewportSwizzleStateCreateFlagsNV>(value.flags);}
constexpr VkPipelineDiscardRectangleStateCreateFlagsEXT to_c(PipelineDiscardRectangleStateCreateFlagsEXT value) { return static_cast<VkPipelineDiscardRectangleStateCreateFlagsEXT>(value.flags);}
constexpr VkPipelineCoverageToColorStateCreateFlagsNV to_c(PipelineCoverageToColorStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageToColorStateCreateFlagsNV>(value.flags);}
constexpr VkPipelineCoverageModulationStateCreateFlagsNV to_c(PipelineCoverageModulationStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageModulationStateCreateFlagsNV>(value.flags);}
constexpr VkPipelineCoverageReductionStateCreateFlagsNV to_c(PipelineCoverageReductionStateCreateFlagsNV value) { return static_cast<VkPipelineCoverageReductionStateCreateFlagsNV>(value.flags);}
constexpr VkValidationCacheCreateFlagsEXT to_c(ValidationCacheCreateFlagsEXT value) { return static_cast<VkValidationCacheCreateFlagsEXT>(value.flags);}
constexpr VkDebugUtilsMessageSeverityFlagsEXT to_c(DebugUtilsMessageSeverityFlagsEXT value) { return static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(value.flags);}
constexpr VkDebugUtilsMessageTypeFlagsEXT to_c(DebugUtilsMessageTypeFlagsEXT value) { return static_cast<VkDebugUtilsMessageTypeFlagsEXT>(value.flags);}
constexpr VkDebugUtilsMessengerCreateFlagsEXT to_c(DebugUtilsMessengerCreateFlagsEXT value) { return static_cast<VkDebugUtilsMessengerCreateFlagsEXT>(value.flags);}
constexpr VkDebugUtilsMessengerCallbackDataFlagsEXT to_c(DebugUtilsMessengerCallbackDataFlagsEXT value) { return static_cast<VkDebugUtilsMessengerCallbackDataFlagsEXT>(value.flags);}
constexpr VkDeviceMemoryReportFlagsEXT to_c(DeviceMemoryReportFlagsEXT value) { return static_cast<VkDeviceMemoryReportFlagsEXT>(value.flags);}
constexpr VkPipelineRasterizationConservativeStateCreateFlagsEXT to_c(PipelineRasterizationConservativeStateCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationConservativeStateCreateFlagsEXT>(value.flags);}
constexpr VkDescriptorBindingFlags to_c(DescriptorBindingFlags value) { return static_cast<VkDescriptorBindingFlags>(value.flags);}
constexpr VkConditionalRenderingFlagsEXT to_c(ConditionalRenderingFlagsEXT value) { return static_cast<VkConditionalRenderingFlagsEXT>(value.flags);}
constexpr VkResolveModeFlags to_c(ResolveModeFlags value) { return static_cast<VkResolveModeFlags>(value.flags);}
constexpr VkPipelineRasterizationStateStreamCreateFlagsEXT to_c(PipelineRasterizationStateStreamCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationStateStreamCreateFlagsEXT>(value.flags);}
constexpr VkPipelineRasterizationDepthClipStateCreateFlagsEXT to_c(PipelineRasterizationDepthClipStateCreateFlagsEXT value) { return static_cast<VkPipelineRasterizationDepthClipStateCreateFlagsEXT>(value.flags);}
constexpr VkToolPurposeFlagsEXT to_c(ToolPurposeFlagsEXT value) { return static_cast<VkToolPurposeFlagsEXT>(value.flags);}
constexpr VkSubmitFlagsKHR to_c(SubmitFlagsKHR value) { return static_cast<VkSubmitFlagsKHR>(value.flags);}
#if defined(VK_USE_PLATFORM_FUCHSIA)
constexpr VkImageFormatConstraintsFlagsFUCHSIA to_c(ImageFormatConstraintsFlagsFUCHSIA value) { return static_cast<VkImageFormatConstraintsFlagsFUCHSIA>(value.flags);}
constexpr VkImageConstraintsInfoFlagsFUCHSIA to_c(ImageConstraintsInfoFlagsFUCHSIA value) { return static_cast<VkImageConstraintsInfoFlagsFUCHSIA>(value.flags);}
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
constexpr VkVideoCodecOperationFlagsKHR to_c(VideoCodecOperationFlagsKHR value) { return static_cast<VkVideoCodecOperationFlagsKHR>(value.flags);}
constexpr VkVideoCapabilityFlagsKHR to_c(VideoCapabilityFlagsKHR value) { return static_cast<VkVideoCapabilityFlagsKHR>(value.flags);}
constexpr VkVideoSessionCreateFlagsKHR to_c(VideoSessionCreateFlagsKHR value) { return static_cast<VkVideoSessionCreateFlagsKHR>(value.flags);}
constexpr VkVideoBeginCodingFlagsKHR to_c(VideoBeginCodingFlagsKHR value) { return static_cast<VkVideoBeginCodingFlagsKHR>(value.flags);}
constexpr VkVideoEndCodingFlagsKHR to_c(VideoEndCodingFlagsKHR value) { return static_cast<VkVideoEndCodingFlagsKHR>(value.flags);}
constexpr VkVideoCodingQualityPresetFlagsKHR to_c(VideoCodingQualityPresetFlagsKHR value) { return static_cast<VkVideoCodingQualityPresetFlagsKHR>(value.flags);}
constexpr VkVideoCodingControlFlagsKHR to_c(VideoCodingControlFlagsKHR value) { return static_cast<VkVideoCodingControlFlagsKHR>(value.flags);}
constexpr VkVideoDecodeFlagsKHR to_c(VideoDecodeFlagsKHR value) { return static_cast<VkVideoDecodeFlagsKHR>(value.flags);}
constexpr VkVideoDecodeH264PictureLayoutFlagsEXT to_c(VideoDecodeH264PictureLayoutFlagsEXT value) { return static_cast<VkVideoDecodeH264PictureLayoutFlagsEXT>(value.flags);}
constexpr VkVideoDecodeH264CreateFlagsEXT to_c(VideoDecodeH264CreateFlagsEXT value) { return static_cast<VkVideoDecodeH264CreateFlagsEXT>(value.flags);}
constexpr VkVideoDecodeH265CreateFlagsEXT to_c(VideoDecodeH265CreateFlagsEXT value) { return static_cast<VkVideoDecodeH265CreateFlagsEXT>(value.flags);}
constexpr VkVideoEncodeFlagsKHR to_c(VideoEncodeFlagsKHR value) { return static_cast<VkVideoEncodeFlagsKHR>(value.flags);}
constexpr VkVideoEncodeRateControlFlagsKHR to_c(VideoEncodeRateControlFlagsKHR value) { return static_cast<VkVideoEncodeRateControlFlagsKHR>(value.flags);}
constexpr VkVideoEncodeRateControlModeFlagsKHR to_c(VideoEncodeRateControlModeFlagsKHR value) { return static_cast<VkVideoEncodeRateControlModeFlagsKHR>(value.flags);}
constexpr VkVideoChromaSubsamplingFlagsKHR to_c(VideoChromaSubsamplingFlagsKHR value) { return static_cast<VkVideoChromaSubsamplingFlagsKHR>(value.flags);}
constexpr VkVideoComponentBitDepthFlagsKHR to_c(VideoComponentBitDepthFlagsKHR value) { return static_cast<VkVideoComponentBitDepthFlagsKHR>(value.flags);}
constexpr VkVideoEncodeH264CapabilityFlagsEXT to_c(VideoEncodeH264CapabilityFlagsEXT value) { return static_cast<VkVideoEncodeH264CapabilityFlagsEXT>(value.flags);}
constexpr VkVideoEncodeH264InputModeFlagsEXT to_c(VideoEncodeH264InputModeFlagsEXT value) { return static_cast<VkVideoEncodeH264InputModeFlagsEXT>(value.flags);}
constexpr VkVideoEncodeH264OutputModeFlagsEXT to_c(VideoEncodeH264OutputModeFlagsEXT value) { return static_cast<VkVideoEncodeH264OutputModeFlagsEXT>(value.flags);}
constexpr VkVideoEncodeH264CreateFlagsEXT to_c(VideoEncodeH264CreateFlagsEXT value) { return static_cast<VkVideoEncodeH264CreateFlagsEXT>(value.flags);}
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
} // namespace vk
// clang-format on
