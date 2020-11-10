#pragma once
// clang-format off
namespace vk::detail {
enum VkAttachmentLoadOp : uint32_t;
enum VkAttachmentStoreOp : uint32_t;
enum VkBlendFactor : uint32_t;
enum VkBlendOp : uint32_t;
enum VkBorderColor : uint32_t;
enum VkPipelineCacheHeaderVersion : uint32_t;
enum VkComponentSwizzle : uint32_t;
enum VkCommandBufferLevel : uint32_t;
enum VkCompareOp : uint32_t;
enum VkDescriptorType : uint32_t;
enum VkDynamicState : uint32_t;
enum VkPolygonMode : uint32_t;
enum VkFormat : uint32_t;
enum VkFrontFace : uint32_t;
enum VkImageLayout : uint32_t;
enum VkImageTiling : uint32_t;
enum VkImageType : uint32_t;
enum VkImageViewType : uint32_t;
enum VkSharingMode : uint32_t;
enum VkIndexType : uint32_t;
enum VkLogicOp : uint32_t;
enum VkPhysicalDeviceType : uint32_t;
enum VkPipelineBindPoint : uint32_t;
enum VkPrimitiveTopology : uint32_t;
enum VkQueryType : uint32_t;
enum VkSubpassContents : uint32_t;
enum VkResult : int32_t;
enum VkStencilOp : uint32_t;
enum VkStructureType : uint32_t;
enum VkSystemAllocationScope : uint32_t;
enum VkInternalAllocationType : uint32_t;
enum VkSamplerAddressMode : uint32_t;
enum VkFilter : uint32_t;
enum VkSamplerMipmapMode : uint32_t;
enum VkVertexInputRate : uint32_t;
enum VkObjectType : uint32_t;
enum VkIndirectCommandsTokenTypeNV : uint32_t;
enum VkDescriptorUpdateTemplateType : uint32_t;
enum VkViewportCoordinateSwizzleNV : uint32_t;
enum VkDiscardRectangleModeEXT : uint32_t;
enum VkPointClippingBehavior : uint32_t;
enum VkCoverageModulationModeNV : uint32_t;
enum VkCoverageReductionModeNV : uint32_t;
enum VkValidationCacheHeaderVersionEXT : uint32_t;
enum VkShaderInfoTypeAMD : uint32_t;
enum VkQueueGlobalPriorityEXT : uint32_t;
enum VkTimeDomainEXT : uint32_t;
enum VkConservativeRasterizationModeEXT : uint32_t;
enum VkSemaphoreType : uint32_t;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkCopyAccelerationStructureModeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkAccelerationStructureTypeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkGeometryTypeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkRayTracingShaderGroupTypeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkAccelerationStructureMemoryRequirementsTypeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkAccelerationStructureBuildTypeKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkMemoryOverallocationBehaviorAMD : uint32_t;
enum VkScopeNV : uint32_t;
enum VkComponentTypeNV : uint32_t;
enum VkPerformanceCounterScopeKHR : uint32_t;
enum VkPerformanceCounterUnitKHR : uint32_t;
enum VkPerformanceCounterStorageKHR : uint32_t;
enum VkPerformanceConfigurationTypeINTEL : uint32_t;
enum VkQueryPoolSamplingModeINTEL : uint32_t;
enum VkPerformanceOverrideTypeINTEL : uint32_t;
enum VkPerformanceParameterTypeINTEL : uint32_t;
enum VkPerformanceValueTypeINTEL : uint32_t;
enum VkLineRasterizationModeEXT : uint32_t;
enum VkColorSpaceKHR : uint32_t;
enum VkPresentModeKHR : uint32_t;
enum VkDebugReportObjectTypeEXT : uint32_t;
enum VkDeviceMemoryReportEventTypeEXT : uint32_t;
enum VkRasterizationOrderAMD : uint32_t;
enum VkValidationCheckEXT : uint32_t;
enum VkValidationFeatureEnableEXT : uint32_t;
enum VkValidationFeatureDisableEXT : uint32_t;
enum VkDisplayPowerStateEXT : uint32_t;
enum VkDeviceEventTypeEXT : uint32_t;
enum VkDisplayEventTypeEXT : uint32_t;
enum VkTessellationDomainOrigin : uint32_t;
enum VkSamplerYcbcrModelConversion : uint32_t;
enum VkSamplerYcbcrRange : uint32_t;
enum VkChromaLocation : uint32_t;
enum VkSamplerReductionMode : uint32_t;
enum VkBlendOverlapEXT : uint32_t;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum VkFullScreenExclusiveEXT : uint32_t;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
enum VkShaderFloatControlsIndependence : uint32_t;
enum VkVendorId : uint32_t;
enum VkDriverId : uint32_t;
enum VkShadingRatePaletteEntryNV : uint32_t;
enum VkCoarseSampleOrderTypeNV : uint32_t;
enum VkPipelineExecutableStatisticFormatKHR : uint32_t;
enum VkPipelineCacheCreateFlagBits : uint32_t;
enum VkQueueFlagBits : uint32_t;
enum VkCullModeFlagBits : uint32_t;
enum VkRenderPassCreateFlagBits : uint32_t;
enum VkDeviceQueueCreateFlagBits : uint32_t;
enum VkMemoryPropertyFlagBits : uint32_t;
enum VkMemoryHeapFlagBits : uint32_t;
enum VkAccessFlagBits : uint32_t;
enum VkBufferUsageFlagBits : uint32_t;
enum VkBufferCreateFlagBits : uint32_t;
enum VkShaderStageFlagBits : uint32_t;
enum VkImageUsageFlagBits : uint32_t;
enum VkImageCreateFlagBits : uint32_t;
enum VkImageViewCreateFlagBits : uint32_t;
enum VkSamplerCreateFlagBits : uint32_t;
enum VkPipelineCreateFlagBits : uint32_t;
enum VkPipelineShaderStageCreateFlagBits : uint32_t;
enum VkColorComponentFlagBits : uint32_t;
enum VkFenceCreateFlagBits : uint32_t;
enum VkSemaphoreCreateFlagBits : uint32_t;
enum VkFormatFeatureFlagBits : uint32_t;
enum VkQueryControlFlagBits : uint32_t;
enum VkQueryResultFlagBits : uint32_t;
enum VkCommandBufferUsageFlagBits : uint32_t;
enum VkQueryPipelineStatisticFlagBits : uint32_t;
enum VkImageAspectFlagBits : uint32_t;
enum VkSparseImageFormatFlagBits : uint32_t;
enum VkSparseMemoryBindFlagBits : uint32_t;
enum VkPipelineStageFlagBits : uint32_t;
enum VkCommandPoolCreateFlagBits : uint32_t;
enum VkCommandPoolResetFlagBits : uint32_t;
enum VkCommandBufferResetFlagBits : uint32_t;
enum VkSampleCountFlagBits : uint32_t;
enum VkAttachmentDescriptionFlagBits : uint32_t;
enum VkStencilFaceFlagBits : uint32_t;
enum VkDescriptorPoolCreateFlagBits : uint32_t;
enum VkDependencyFlagBits : uint32_t;
enum VkSemaphoreWaitFlagBits : uint32_t;
enum VkDisplayPlaneAlphaFlagBitsKHR : uint32_t;
enum VkCompositeAlphaFlagBitsKHR : uint32_t;
enum VkSurfaceTransformFlagBitsKHR : uint32_t;
enum VkDebugReportFlagBitsEXT : uint32_t;
enum VkExternalMemoryHandleTypeFlagBitsNV : uint32_t;
enum VkExternalMemoryFeatureFlagBitsNV : uint32_t;
enum VkSubgroupFeatureFlagBits : uint32_t;
enum VkIndirectCommandsLayoutUsageFlagBitsNV : uint32_t;
enum VkIndirectStateFlagBitsNV : uint32_t;
enum VkPrivateDataSlotCreateFlagBitsEXT : uint32_t;
enum VkDescriptorSetLayoutCreateFlagBits : uint32_t;
enum VkExternalMemoryHandleTypeFlagBits : uint32_t;
enum VkExternalMemoryFeatureFlagBits : uint32_t;
enum VkExternalSemaphoreHandleTypeFlagBits : uint32_t;
enum VkExternalSemaphoreFeatureFlagBits : uint32_t;
enum VkSemaphoreImportFlagBits : uint32_t;
enum VkExternalFenceHandleTypeFlagBits : uint32_t;
enum VkExternalFenceFeatureFlagBits : uint32_t;
enum VkFenceImportFlagBits : uint32_t;
enum VkSurfaceCounterFlagBitsEXT : uint32_t;
enum VkPeerMemoryFeatureFlagBits : uint32_t;
enum VkMemoryAllocateFlagBits : uint32_t;
enum VkDeviceGroupPresentModeFlagBitsKHR : uint32_t;
enum VkSwapchainCreateFlagBitsKHR : uint32_t;
enum VkSubpassDescriptionFlagBits : uint32_t;
enum VkDebugUtilsMessageSeverityFlagBitsEXT : uint32_t;
enum VkDebugUtilsMessageTypeFlagBitsEXT : uint32_t;
enum VkDescriptorBindingFlagBits : uint32_t;
enum VkConditionalRenderingFlagBitsEXT : uint32_t;
enum VkResolveModeFlagBits : uint32_t;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkGeometryInstanceFlagBitsKHR : uint32_t;
enum VkGeometryFlagBitsKHR : uint32_t;
enum VkBuildAccelerationStructureFlagBitsKHR : uint32_t;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
enum VkFramebufferCreateFlagBits : uint32_t;
enum VkDeviceDiagnosticsConfigFlagBitsNV : uint32_t;
enum VkPipelineCreationFeedbackFlagBitsEXT : uint32_t;
enum VkPerformanceCounterDescriptionFlagBitsKHR : uint32_t;
enum VkAcquireProfilingLockFlagBitsKHR : uint32_t;
enum VkShaderCorePropertiesFlagBitsAMD : uint32_t;
enum VkShaderModuleCreateFlagBits : uint32_t;
enum VkPipelineCompilerControlFlagBitsAMD : uint32_t;
enum VkToolPurposeFlagBitsEXT : uint32_t;
enum VkQueryPoolCreateFlagBits : uint32_t;
enum VkPipelineLayoutCreateFlagBits : uint32_t;
enum VkPipelineDepthStencilStateCreateFlagBits : uint32_t;
enum VkPipelineDynamicStateCreateFlagBits : uint32_t;
enum VkPipelineColorBlendStateCreateFlagBits : uint32_t;
enum VkPipelineMultisampleStateCreateFlagBits : uint32_t;
enum VkPipelineRasterizationStateCreateFlagBits : uint32_t;
enum VkPipelineViewportStateCreateFlagBits : uint32_t;
enum VkPipelineTessellationStateCreateFlagBits : uint32_t;
enum VkPipelineInputAssemblyStateCreateFlagBits : uint32_t;
enum VkPipelineVertexInputStateCreateFlagBits : uint32_t;
enum VkBufferViewCreateFlagBits : uint32_t;
enum VkInstanceCreateFlagBits : uint32_t;
enum VkDeviceCreateFlagBits : uint32_t;
enum VkEventCreateFlagBits : uint32_t;
enum VkMemoryMapFlagBits : uint32_t;
enum VkDescriptorPoolResetFlagBits : uint32_t;
enum VkDescriptorUpdateTemplateCreateFlagBits : uint32_t;
enum VkDisplayModeCreateFlagBitsKHR : uint32_t;
enum VkDisplaySurfaceCreateFlagBitsKHR : uint32_t;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
enum VkAndroidSurfaceCreateFlagBitsKHR : uint32_t;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
enum VkViSurfaceCreateFlagBitsNN : uint32_t;
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
enum VkWaylandSurfaceCreateFlagBitsKHR : uint32_t;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum VkWin32SurfaceCreateFlagBitsKHR : uint32_t;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
enum VkXlibSurfaceCreateFlagBitsKHR : uint32_t;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
enum VkXcbSurfaceCreateFlagBitsKHR : uint32_t;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
enum VkDirectFBSurfaceCreateFlagBitsEXT : uint32_t;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
enum VkIOSSurfaceCreateFlagBitsMVK : uint32_t;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
enum VkMacOSSurfaceCreateFlagBitsMVK : uint32_t;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
enum VkMetalSurfaceCreateFlagBitsEXT : uint32_t;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
enum VkImagePipeSurfaceCreateFlagBitsFUCHSIA : uint32_t;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
enum VkStreamDescriptorSurfaceCreateFlagBitsGGP : uint32_t;
#endif // defined(VK_USE_PLATFORM_GGP)
enum VkHeadlessSurfaceCreateFlagBitsEXT : uint32_t;
enum VkCommandPoolTrimFlagBits : uint32_t;
enum VkPipelineViewportSwizzleStateCreateFlagBitsNV : uint32_t;
enum VkPipelineDiscardRectangleStateCreateFlagBitsEXT : uint32_t;
enum VkPipelineCoverageToColorStateCreateFlagBitsNV : uint32_t;
enum VkPipelineCoverageModulationStateCreateFlagBitsNV : uint32_t;
enum VkPipelineCoverageReductionStateCreateFlagBitsNV : uint32_t;
enum VkValidationCacheCreateFlagBitsEXT : uint32_t;
enum VkDebugUtilsMessengerCreateFlagBitsEXT : uint32_t;
enum VkDebugUtilsMessengerCallbackDataFlagBitsEXT : uint32_t;
enum VkDeviceMemoryReportFlagBitsEXT : uint32_t;
enum VkPipelineRasterizationConservativeStateCreateFlagBitsEXT : uint32_t;
enum VkPipelineRasterizationStateStreamCreateFlagBitsEXT : uint32_t;
enum VkPipelineRasterizationDepthClipStateCreateFlagBitsEXT : uint32_t;
struct VkBaseOutStructure;
struct VkBaseInStructure;
struct VkOffset2D;
struct VkOffset3D;
struct VkExtent2D;
struct VkExtent3D;
struct VkViewport;
struct VkRect2D;
struct VkClearRect;
struct VkComponentMapping;
struct VkPhysicalDeviceSparseProperties;
struct VkPhysicalDeviceLimits;
struct VkPhysicalDeviceProperties;
struct VkExtensionProperties;
struct VkLayerProperties;
struct VkApplicationInfo;
struct VkAllocationCallbacks;
struct VkDeviceQueueCreateInfo;
struct VkPhysicalDeviceFeatures;
struct VkDeviceCreateInfo;
struct VkInstanceCreateInfo;
struct VkQueueFamilyProperties;
struct VkMemoryHeap;
struct VkMemoryType;
struct VkPhysicalDeviceMemoryProperties;
struct VkMemoryAllocateInfo;
struct VkMemoryRequirements;
struct VkSparseImageFormatProperties;
struct VkSparseImageMemoryRequirements;
struct VkMappedMemoryRange;
struct VkFormatProperties;
struct VkImageFormatProperties;
struct VkDescriptorBufferInfo;
struct VkDescriptorImageInfo;
struct VkWriteDescriptorSet;
struct VkCopyDescriptorSet;
struct VkBufferCreateInfo;
struct VkBufferViewCreateInfo;
struct VkImageSubresource;
struct VkImageSubresourceLayers;
struct VkImageSubresourceRange;
struct VkMemoryBarrier;
struct VkBufferMemoryBarrier;
struct VkImageMemoryBarrier;
struct VkImageCreateInfo;
struct VkSubresourceLayout;
struct VkImageViewCreateInfo;
struct VkBufferCopy;
struct VkSparseMemoryBind;
struct VkSparseImageMemoryBind;
struct VkSparseBufferMemoryBindInfo;
struct VkSparseImageOpaqueMemoryBindInfo;
struct VkSparseImageMemoryBindInfo;
struct VkBindSparseInfo;
struct VkImageCopy;
struct VkImageBlit;
struct VkBufferImageCopy;
struct VkImageResolve;
struct VkShaderModuleCreateInfo;
struct VkDescriptorSetLayoutBinding;
struct VkDescriptorSetLayoutCreateInfo;
struct VkDescriptorPoolSize;
struct VkDescriptorPoolCreateInfo;
struct VkDescriptorSetAllocateInfo;
struct VkSpecializationMapEntry;
struct VkSpecializationInfo;
struct VkPipelineShaderStageCreateInfo;
struct VkComputePipelineCreateInfo;
struct VkVertexInputBindingDescription;
struct VkVertexInputAttributeDescription;
struct VkPipelineVertexInputStateCreateInfo;
struct VkPipelineInputAssemblyStateCreateInfo;
struct VkPipelineTessellationStateCreateInfo;
struct VkPipelineViewportStateCreateInfo;
struct VkPipelineRasterizationStateCreateInfo;
struct VkPipelineMultisampleStateCreateInfo;
struct VkPipelineColorBlendAttachmentState;
struct VkPipelineColorBlendStateCreateInfo;
struct VkPipelineDynamicStateCreateInfo;
struct VkStencilOpState;
struct VkPipelineDepthStencilStateCreateInfo;
struct VkGraphicsPipelineCreateInfo;
struct VkPipelineCacheCreateInfo;
struct VkPushConstantRange;
struct VkPipelineLayoutCreateInfo;
struct VkSamplerCreateInfo;
struct VkCommandPoolCreateInfo;
struct VkCommandBufferAllocateInfo;
struct VkCommandBufferInheritanceInfo;
struct VkCommandBufferBeginInfo;
struct VkClearDepthStencilValue;
union VkClearColorValue;
union VkClearValue;
struct VkRenderPassBeginInfo;
struct VkClearAttachment;
struct VkAttachmentDescription;
struct VkAttachmentReference;
struct VkSubpassDescription;
struct VkSubpassDependency;
struct VkRenderPassCreateInfo;
struct VkEventCreateInfo;
struct VkFenceCreateInfo;
struct VkSemaphoreCreateInfo;
struct VkQueryPoolCreateInfo;
struct VkFramebufferCreateInfo;
struct VkDrawIndirectCommand;
struct VkDrawIndexedIndirectCommand;
struct VkDispatchIndirectCommand;
struct VkSubmitInfo;
struct VkDisplayPropertiesKHR;
struct VkDisplayPlanePropertiesKHR;
struct VkDisplayModeParametersKHR;
struct VkDisplayModePropertiesKHR;
struct VkDisplayModeCreateInfoKHR;
struct VkDisplayPlaneCapabilitiesKHR;
struct VkDisplaySurfaceCreateInfoKHR;
struct VkDisplayPresentInfoKHR;
struct VkSurfaceCapabilitiesKHR;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkAndroidSurfaceCreateInfoKHR;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
struct VkViSurfaceCreateInfoNN;
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
struct VkWaylandSurfaceCreateInfoKHR;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkWin32SurfaceCreateInfoKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
struct VkXlibSurfaceCreateInfoKHR;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
struct VkXcbSurfaceCreateInfoKHR;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
struct VkDirectFBSurfaceCreateInfoEXT;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct VkImagePipeSurfaceCreateInfoFUCHSIA;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
struct VkStreamDescriptorSurfaceCreateInfoGGP;
#endif // defined(VK_USE_PLATFORM_GGP)
struct VkSurfaceFormatKHR;
struct VkSwapchainCreateInfoKHR;
struct VkPresentInfoKHR;
struct VkDebugReportCallbackCreateInfoEXT;
struct VkValidationFlagsEXT;
struct VkValidationFeaturesEXT;
struct VkPipelineRasterizationStateRasterizationOrderAMD;
struct VkDebugMarkerObjectNameInfoEXT;
struct VkDebugMarkerObjectTagInfoEXT;
struct VkDebugMarkerMarkerInfoEXT;
struct VkDedicatedAllocationImageCreateInfoNV;
struct VkDedicatedAllocationBufferCreateInfoNV;
struct VkDedicatedAllocationMemoryAllocateInfoNV;
struct VkExternalImageFormatPropertiesNV;
struct VkExternalMemoryImageCreateInfoNV;
struct VkExportMemoryAllocateInfoNV;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryWin32HandleInfoNV;
struct VkExportMemoryWin32HandleInfoNV;
struct VkWin32KeyedMutexAcquireReleaseInfoNV;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV;
struct VkDevicePrivateDataCreateInfoEXT;
struct VkPrivateDataSlotCreateInfoEXT;
struct VkPhysicalDevicePrivateDataFeaturesEXT;
struct VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV;
struct VkGraphicsShaderGroupCreateInfoNV;
struct VkGraphicsPipelineShaderGroupsCreateInfoNV;
struct VkBindShaderGroupIndirectCommandNV;
struct VkBindIndexBufferIndirectCommandNV;
struct VkBindVertexBufferIndirectCommandNV;
struct VkSetStateFlagsIndirectCommandNV;
struct VkIndirectCommandsStreamNV;
struct VkIndirectCommandsLayoutTokenNV;
struct VkIndirectCommandsLayoutCreateInfoNV;
struct VkGeneratedCommandsInfoNV;
struct VkGeneratedCommandsMemoryRequirementsInfoNV;
struct VkPhysicalDeviceFeatures2;
struct VkPhysicalDeviceProperties2;
struct VkFormatProperties2;
struct VkImageFormatProperties2;
struct VkPhysicalDeviceImageFormatInfo2;
struct VkQueueFamilyProperties2;
struct VkPhysicalDeviceMemoryProperties2;
struct VkSparseImageFormatProperties2;
struct VkPhysicalDeviceSparseImageFormatInfo2;
struct VkPhysicalDevicePushDescriptorPropertiesKHR;
struct VkConformanceVersion;
struct VkPhysicalDeviceDriverProperties;
struct VkRectLayerKHR;
struct VkPresentRegionKHR;
struct VkPresentRegionsKHR;
struct VkPhysicalDeviceVariablePointersFeatures;
struct VkExternalMemoryProperties;
struct VkPhysicalDeviceExternalImageFormatInfo;
struct VkExternalImageFormatProperties;
struct VkPhysicalDeviceExternalBufferInfo;
struct VkExternalBufferProperties;
struct VkPhysicalDeviceIDProperties;
struct VkExternalMemoryImageCreateInfo;
struct VkExternalMemoryBufferCreateInfo;
struct VkExportMemoryAllocateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryWin32HandleInfoKHR;
struct VkExportMemoryWin32HandleInfoKHR;
struct VkMemoryWin32HandlePropertiesKHR;
struct VkMemoryGetWin32HandleInfoKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryFdInfoKHR;
struct VkMemoryFdPropertiesKHR;
struct VkMemoryGetFdInfoKHR;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkWin32KeyedMutexAcquireReleaseInfoKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDeviceExternalSemaphoreInfo;
struct VkExternalSemaphoreProperties;
struct VkExportSemaphoreCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportSemaphoreWin32HandleInfoKHR;
struct VkExportSemaphoreWin32HandleInfoKHR;
struct VkD3D12FenceSubmitInfoKHR;
struct VkSemaphoreGetWin32HandleInfoKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportSemaphoreFdInfoKHR;
struct VkSemaphoreGetFdInfoKHR;
struct VkPhysicalDeviceExternalFenceInfo;
struct VkExternalFenceProperties;
struct VkExportFenceCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportFenceWin32HandleInfoKHR;
struct VkExportFenceWin32HandleInfoKHR;
struct VkFenceGetWin32HandleInfoKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportFenceFdInfoKHR;
struct VkFenceGetFdInfoKHR;
struct VkPhysicalDeviceMultiviewFeatures;
struct VkPhysicalDeviceMultiviewProperties;
struct VkRenderPassMultiviewCreateInfo;
struct VkSurfaceCapabilities2EXT;
struct VkDisplayPowerInfoEXT;
struct VkDeviceEventInfoEXT;
struct VkDisplayEventInfoEXT;
struct VkSwapchainCounterCreateInfoEXT;
struct VkPhysicalDeviceGroupProperties;
struct VkMemoryAllocateFlagsInfo;
struct VkBindBufferMemoryInfo;
struct VkBindBufferMemoryDeviceGroupInfo;
struct VkBindImageMemoryInfo;
struct VkBindImageMemoryDeviceGroupInfo;
struct VkDeviceGroupRenderPassBeginInfo;
struct VkDeviceGroupCommandBufferBeginInfo;
struct VkDeviceGroupSubmitInfo;
struct VkDeviceGroupBindSparseInfo;
struct VkDeviceGroupPresentCapabilitiesKHR;
struct VkImageSwapchainCreateInfoKHR;
struct VkBindImageMemorySwapchainInfoKHR;
struct VkAcquireNextImageInfoKHR;
struct VkDeviceGroupPresentInfoKHR;
struct VkDeviceGroupDeviceCreateInfo;
struct VkDeviceGroupSwapchainCreateInfoKHR;
struct VkDescriptorUpdateTemplateEntry;
struct VkDescriptorUpdateTemplateCreateInfo;
struct VkXYColorEXT;
struct VkHdrMetadataEXT;
struct VkDisplayNativeHdrSurfaceCapabilitiesAMD;
struct VkSwapchainDisplayNativeHdrCreateInfoAMD;
struct VkRefreshCycleDurationGOOGLE;
struct VkPastPresentationTimingGOOGLE;
struct VkPresentTimeGOOGLE;
struct VkPresentTimesInfoGOOGLE;
#if defined(VK_USE_PLATFORM_IOS_MVK)
struct VkIOSSurfaceCreateInfoMVK;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
struct VkMacOSSurfaceCreateInfoMVK;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
struct VkMetalSurfaceCreateInfoEXT;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
struct VkViewportWScalingNV;
struct VkPipelineViewportWScalingStateCreateInfoNV;
struct VkViewportSwizzleNV;
struct VkPipelineViewportSwizzleStateCreateInfoNV;
struct VkPhysicalDeviceDiscardRectanglePropertiesEXT;
struct VkPipelineDiscardRectangleStateCreateInfoEXT;
struct VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;
struct VkInputAttachmentAspectReference;
struct VkRenderPassInputAttachmentAspectCreateInfo;
struct VkPhysicalDeviceSurfaceInfo2KHR;
struct VkSurfaceCapabilities2KHR;
struct VkSurfaceFormat2KHR;
struct VkDisplayProperties2KHR;
struct VkDisplayPlaneProperties2KHR;
struct VkDisplayModeProperties2KHR;
struct VkDisplayPlaneInfo2KHR;
struct VkDisplayPlaneCapabilities2KHR;
struct VkSharedPresentSurfaceCapabilitiesKHR;
struct VkPhysicalDevice16BitStorageFeatures;
struct VkPhysicalDeviceSubgroupProperties;
struct VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures;
struct VkBufferMemoryRequirementsInfo2;
struct VkImageMemoryRequirementsInfo2;
struct VkImageSparseMemoryRequirementsInfo2;
struct VkMemoryRequirements2;
struct VkSparseImageMemoryRequirements2;
struct VkPhysicalDevicePointClippingProperties;
struct VkMemoryDedicatedRequirements;
struct VkMemoryDedicatedAllocateInfo;
struct VkImageViewUsageCreateInfo;
struct VkPipelineTessellationDomainOriginStateCreateInfo;
struct VkSamplerYcbcrConversionInfo;
struct VkSamplerYcbcrConversionCreateInfo;
struct VkBindImagePlaneMemoryInfo;
struct VkImagePlaneMemoryRequirementsInfo;
struct VkPhysicalDeviceSamplerYcbcrConversionFeatures;
struct VkSamplerYcbcrConversionImageFormatProperties;
struct VkTextureLODGatherFormatPropertiesAMD;
struct VkConditionalRenderingBeginInfoEXT;
struct VkProtectedSubmitInfo;
struct VkPhysicalDeviceProtectedMemoryFeatures;
struct VkPhysicalDeviceProtectedMemoryProperties;
struct VkDeviceQueueInfo2;
struct VkPipelineCoverageToColorStateCreateInfoNV;
struct VkPhysicalDeviceSamplerFilterMinmaxProperties;
struct VkSampleLocationEXT;
struct VkSampleLocationsInfoEXT;
struct VkAttachmentSampleLocationsEXT;
struct VkSubpassSampleLocationsEXT;
struct VkRenderPassSampleLocationsBeginInfoEXT;
struct VkPipelineSampleLocationsStateCreateInfoEXT;
struct VkPhysicalDeviceSampleLocationsPropertiesEXT;
struct VkMultisamplePropertiesEXT;
struct VkSamplerReductionModeCreateInfo;
struct VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT;
struct VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT;
struct VkPipelineColorBlendAdvancedStateCreateInfoEXT;
struct VkPhysicalDeviceInlineUniformBlockFeaturesEXT;
struct VkPhysicalDeviceInlineUniformBlockPropertiesEXT;
struct VkWriteDescriptorSetInlineUniformBlockEXT;
struct VkDescriptorPoolInlineUniformBlockCreateInfoEXT;
struct VkPipelineCoverageModulationStateCreateInfoNV;
struct VkImageFormatListCreateInfo;
struct VkValidationCacheCreateInfoEXT;
struct VkShaderModuleValidationCacheCreateInfoEXT;
struct VkPhysicalDeviceMaintenance3Properties;
struct VkDescriptorSetLayoutSupport;
struct VkPhysicalDeviceShaderDrawParametersFeatures;
struct VkPhysicalDeviceShaderFloat16Int8Features;
struct VkPhysicalDeviceFloatControlsProperties;
struct VkPhysicalDeviceHostQueryResetFeatures;
struct VkShaderResourceUsageAMD;
struct VkShaderStatisticsInfoAMD;
struct VkDeviceQueueGlobalPriorityCreateInfoEXT;
struct VkDebugUtilsObjectNameInfoEXT;
struct VkDebugUtilsObjectTagInfoEXT;
struct VkDebugUtilsLabelEXT;
struct VkDebugUtilsMessengerCreateInfoEXT;
struct VkDebugUtilsMessengerCallbackDataEXT;
struct VkPhysicalDeviceDeviceMemoryReportFeaturesEXT;
struct VkDeviceDeviceMemoryReportCreateInfoEXT;
struct VkDeviceMemoryReportCallbackDataEXT;
struct VkImportMemoryHostPointerInfoEXT;
struct VkMemoryHostPointerPropertiesEXT;
struct VkPhysicalDeviceExternalMemoryHostPropertiesEXT;
struct VkPhysicalDeviceConservativeRasterizationPropertiesEXT;
struct VkCalibratedTimestampInfoEXT;
struct VkPhysicalDeviceShaderCorePropertiesAMD;
struct VkPhysicalDeviceShaderCoreProperties2AMD;
struct VkPipelineRasterizationConservativeStateCreateInfoEXT;
struct VkPhysicalDeviceDescriptorIndexingFeatures;
struct VkPhysicalDeviceDescriptorIndexingProperties;
struct VkDescriptorSetLayoutBindingFlagsCreateInfo;
struct VkDescriptorSetVariableDescriptorCountAllocateInfo;
struct VkDescriptorSetVariableDescriptorCountLayoutSupport;
struct VkAttachmentDescription2;
struct VkAttachmentReference2;
struct VkSubpassDescription2;
struct VkSubpassDependency2;
struct VkRenderPassCreateInfo2;
struct VkSubpassBeginInfo;
struct VkSubpassEndInfo;
struct VkPhysicalDeviceTimelineSemaphoreFeatures;
struct VkPhysicalDeviceTimelineSemaphoreProperties;
struct VkSemaphoreTypeCreateInfo;
struct VkTimelineSemaphoreSubmitInfo;
struct VkSemaphoreWaitInfo;
struct VkSemaphoreSignalInfo;
struct VkVertexInputBindingDivisorDescriptionEXT;
struct VkPipelineVertexInputDivisorStateCreateInfoEXT;
struct VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT;
struct VkPhysicalDevicePCIBusInfoPropertiesEXT;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkImportAndroidHardwareBufferInfoANDROID;
struct VkAndroidHardwareBufferUsageANDROID;
struct VkAndroidHardwareBufferPropertiesANDROID;
struct VkMemoryGetAndroidHardwareBufferInfoANDROID;
struct VkAndroidHardwareBufferFormatPropertiesANDROID;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkCommandBufferInheritanceConditionalRenderingInfoEXT;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkExternalFormatANDROID;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkPhysicalDevice8BitStorageFeatures;
struct VkPhysicalDeviceConditionalRenderingFeaturesEXT;
struct VkPhysicalDeviceVulkanMemoryModelFeatures;
struct VkPhysicalDeviceShaderAtomicInt64Features;
struct VkPhysicalDeviceShaderAtomicFloatFeaturesEXT;
struct VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT;
struct VkQueueFamilyCheckpointPropertiesNV;
struct VkCheckpointDataNV;
struct VkPhysicalDeviceDepthStencilResolveProperties;
struct VkSubpassDescriptionDepthStencilResolve;
struct VkImageViewASTCDecodeModeEXT;
struct VkPhysicalDeviceASTCDecodeFeaturesEXT;
struct VkPhysicalDeviceTransformFeedbackFeaturesEXT;
struct VkPhysicalDeviceTransformFeedbackPropertiesEXT;
struct VkPipelineRasterizationStateStreamCreateInfoEXT;
struct VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV;
struct VkPipelineRepresentativeFragmentTestStateCreateInfoNV;
struct VkPhysicalDeviceExclusiveScissorFeaturesNV;
struct VkPipelineViewportExclusiveScissorStateCreateInfoNV;
struct VkPhysicalDeviceCornerSampledImageFeaturesNV;
struct VkPhysicalDeviceComputeShaderDerivativesFeaturesNV;
struct VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV;
struct VkPhysicalDeviceShaderImageFootprintFeaturesNV;
struct VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;
struct VkShadingRatePaletteNV;
struct VkPipelineViewportShadingRateImageStateCreateInfoNV;
struct VkPhysicalDeviceShadingRateImageFeaturesNV;
struct VkPhysicalDeviceShadingRateImagePropertiesNV;
struct VkCoarseSampleLocationNV;
struct VkCoarseSampleOrderCustomNV;
struct VkPipelineViewportCoarseSampleOrderStateCreateInfoNV;
struct VkPhysicalDeviceMeshShaderFeaturesNV;
struct VkPhysicalDeviceMeshShaderPropertiesNV;
struct VkDrawMeshTasksIndirectCommandNV;
struct VkRayTracingShaderGroupCreateInfoNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkRayTracingShaderGroupCreateInfoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkRayTracingPipelineCreateInfoNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkRayTracingPipelineInterfaceCreateInfoKHR;
struct VkPipelineLibraryCreateInfoKHR;
struct VkRayTracingPipelineCreateInfoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkGeometryTrianglesNV;
struct VkGeometryAABBNV;
struct VkGeometryDataNV;
struct VkGeometryNV;
struct VkAccelerationStructureInfoNV;
struct VkAccelerationStructureCreateInfoNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkBindAccelerationStructureMemoryInfoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkWriteDescriptorSetAccelerationStructureKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkAccelerationStructureMemoryRequirementsInfoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkAccelerationStructureMemoryRequirementsInfoNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDeviceRayTracingFeaturesKHR;
struct VkPhysicalDeviceRayTracingPropertiesKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDeviceRayTracingPropertiesNV;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkStridedBufferRegionKHR;
struct VkTraceRaysIndirectCommandKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkDrmFormatModifierPropertiesEXT;
struct VkDrmFormatModifierPropertiesListEXT;
struct VkPhysicalDeviceImageDrmFormatModifierInfoEXT;
struct VkImageDrmFormatModifierListCreateInfoEXT;
struct VkImageDrmFormatModifierExplicitCreateInfoEXT;
struct VkImageDrmFormatModifierPropertiesEXT;
struct VkImageStencilUsageCreateInfo;
struct VkDeviceMemoryOverallocationCreateInfoAMD;
struct VkPhysicalDeviceFragmentDensityMapFeaturesEXT;
struct VkPhysicalDeviceFragmentDensityMap2FeaturesEXT;
struct VkPhysicalDeviceFragmentDensityMapPropertiesEXT;
struct VkPhysicalDeviceFragmentDensityMap2PropertiesEXT;
struct VkRenderPassFragmentDensityMapCreateInfoEXT;
struct VkPhysicalDeviceScalarBlockLayoutFeatures;
struct VkSurfaceProtectedCapabilitiesKHR;
struct VkPhysicalDeviceUniformBufferStandardLayoutFeatures;
struct VkPhysicalDeviceDepthClipEnableFeaturesEXT;
struct VkPipelineRasterizationDepthClipStateCreateInfoEXT;
struct VkPhysicalDeviceMemoryBudgetPropertiesEXT;
struct VkPhysicalDeviceMemoryPriorityFeaturesEXT;
struct VkMemoryPriorityAllocateInfoEXT;
struct VkPhysicalDeviceBufferDeviceAddressFeatures;
struct VkPhysicalDeviceBufferDeviceAddressFeaturesEXT;
struct VkBufferDeviceAddressInfo;
struct VkBufferOpaqueCaptureAddressCreateInfo;
struct VkBufferDeviceAddressCreateInfoEXT;
struct VkPhysicalDeviceImageViewImageFormatInfoEXT;
struct VkFilterCubicImageViewImageFormatPropertiesEXT;
struct VkPhysicalDeviceImagelessFramebufferFeatures;
struct VkFramebufferAttachmentImageInfo;
struct VkFramebufferAttachmentsCreateInfo;
struct VkRenderPassAttachmentBeginInfo;
struct VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT;
struct VkPhysicalDeviceCooperativeMatrixFeaturesNV;
struct VkPhysicalDeviceCooperativeMatrixPropertiesNV;
struct VkCooperativeMatrixPropertiesNV;
struct VkPhysicalDeviceYcbcrImageArraysFeaturesEXT;
struct VkImageViewHandleInfoNVX;
struct VkImageViewAddressPropertiesNVX;
#if defined(VK_USE_PLATFORM_GGP)
struct VkPresentFrameTokenGGP;
#endif // defined(VK_USE_PLATFORM_GGP)
struct VkPipelineCreationFeedbackEXT;
struct VkPipelineCreationFeedbackCreateInfoEXT;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkSurfaceFullScreenExclusiveInfoEXT;
struct VkSurfaceFullScreenExclusiveWin32InfoEXT;
struct VkSurfaceCapabilitiesFullScreenExclusiveEXT;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDevicePerformanceQueryFeaturesKHR;
struct VkPhysicalDevicePerformanceQueryPropertiesKHR;
struct VkPerformanceCounterKHR;
struct VkPerformanceCounterDescriptionKHR;
struct VkQueryPoolPerformanceCreateInfoKHR;
union VkPerformanceCounterResultKHR;
struct VkAcquireProfilingLockInfoKHR;
struct VkPerformanceQuerySubmitInfoKHR;
struct VkHeadlessSurfaceCreateInfoEXT;
struct VkPhysicalDeviceCoverageReductionModeFeaturesNV;
struct VkPipelineCoverageReductionStateCreateInfoNV;
struct VkFramebufferMixedSamplesCombinationNV;
struct VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL;
union VkPerformanceValueDataINTEL;
struct VkPerformanceValueINTEL;
struct VkInitializePerformanceApiInfoINTEL;
struct VkQueryPoolPerformanceQueryCreateInfoINTEL;
struct VkPerformanceMarkerInfoINTEL;
struct VkPerformanceStreamMarkerInfoINTEL;
struct VkPerformanceOverrideInfoINTEL;
struct VkPerformanceConfigurationAcquireInfoINTEL;
struct VkPhysicalDeviceShaderClockFeaturesKHR;
struct VkPhysicalDeviceIndexTypeUint8FeaturesEXT;
struct VkPhysicalDeviceShaderSMBuiltinsPropertiesNV;
struct VkPhysicalDeviceShaderSMBuiltinsFeaturesNV;
struct VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT;
struct VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures;
struct VkAttachmentReferenceStencilLayout;
struct VkAttachmentDescriptionStencilLayout;
struct VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR;
struct VkPipelineInfoKHR;
struct VkPipelineExecutablePropertiesKHR;
struct VkPipelineExecutableInfoKHR;
union VkPipelineExecutableStatisticValueKHR;
struct VkPipelineExecutableStatisticKHR;
struct VkPipelineExecutableInternalRepresentationKHR;
struct VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
struct VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT;
struct VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT;
struct VkPhysicalDeviceSubgroupSizeControlFeaturesEXT;
struct VkPhysicalDeviceSubgroupSizeControlPropertiesEXT;
struct VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
struct VkMemoryOpaqueCaptureAddressAllocateInfo;
struct VkDeviceMemoryOpaqueCaptureAddressInfo;
struct VkPhysicalDeviceLineRasterizationFeaturesEXT;
struct VkPhysicalDeviceLineRasterizationPropertiesEXT;
struct VkPipelineRasterizationLineStateCreateInfoEXT;
struct VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT;
struct VkPhysicalDeviceVulkan11Features;
struct VkPhysicalDeviceVulkan11Properties;
struct VkPhysicalDeviceVulkan12Features;
struct VkPhysicalDeviceVulkan12Properties;
struct VkPipelineCompilerControlCreateInfoAMD;
struct VkPhysicalDeviceCoherentMemoryFeaturesAMD;
struct VkPhysicalDeviceToolPropertiesEXT;
struct VkSamplerCustomBorderColorCreateInfoEXT;
struct VkPhysicalDeviceCustomBorderColorPropertiesEXT;
struct VkPhysicalDeviceCustomBorderColorFeaturesEXT;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
union VkDeviceOrHostAddressKHR;
union VkDeviceOrHostAddressConstKHR;
struct VkAccelerationStructureGeometryTrianglesDataKHR;
struct VkAccelerationStructureGeometryAabbsDataKHR;
struct VkAccelerationStructureGeometryInstancesDataKHR;
union VkAccelerationStructureGeometryDataKHR;
struct VkAccelerationStructureGeometryKHR;
struct VkAccelerationStructureBuildGeometryInfoKHR;
struct VkAccelerationStructureBuildOffsetInfoKHR;
struct VkAccelerationStructureCreateGeometryTypeInfoKHR;
struct VkAccelerationStructureCreateInfoKHR;
struct VkAabbPositionsKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkTransformMatrixKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkAccelerationStructureInstanceKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkAccelerationStructureDeviceAddressInfoKHR;
struct VkAccelerationStructureVersionKHR;
struct VkCopyAccelerationStructureInfoKHR;
struct VkCopyAccelerationStructureToMemoryInfoKHR;
struct VkCopyMemoryToAccelerationStructureInfoKHR;
struct VkDeferredOperationInfoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDeviceExtendedDynamicStateFeaturesEXT;
struct VkRenderPassTransformBeginInfoQCOM;
struct VkCommandBufferInheritanceRenderPassTransformInfoQCOM;
struct VkPhysicalDeviceDiagnosticsConfigFeaturesNV;
struct VkDeviceDiagnosticsConfigCreateInfoNV;
struct VkPhysicalDeviceRobustness2FeaturesEXT;
struct VkPhysicalDeviceRobustness2PropertiesEXT;
struct VkPhysicalDeviceImageRobustnessFeaturesEXT;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDevicePortabilitySubsetFeaturesKHR;
struct VkPhysicalDevicePortabilitySubsetPropertiesKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDevice4444FormatsFeaturesEXT;
struct VkBufferCopy2KHR;
struct VkImageCopy2KHR;
struct VkImageBlit2KHR;
struct VkBufferImageCopy2KHR;
struct VkImageResolve2KHR;
struct VkCopyBufferInfo2KHR;
struct VkCopyImageInfo2KHR;
struct VkBlitImageInfo2KHR;
struct VkCopyBufferToImageInfo2KHR;
struct VkCopyImageToBufferInfo2KHR;
struct VkResolveImageInfo2KHR;
struct VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT;
using PFN_vkCreateInstance = VkResult (*) (const  VkInstanceCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkInstance *  pInstance);
using PFN_vkDestroyInstance = void (*) (VkInstance   instance, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkEnumeratePhysicalDevices = VkResult (*) (VkInstance   instance, uint32_t *  pPhysicalDeviceCount, VkPhysicalDevice *  pPhysicalDevices);
using PFN_vkGetDeviceProcAddr = PFN_vkVoidFunction (*) (VkDevice   device, const  char *  pName);
using PFN_vkGetInstanceProcAddr = PFN_vkVoidFunction (*) (VkInstance   instance, const  char *  pName);
using PFN_vkGetPhysicalDeviceProperties = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceProperties *  pProperties);
using PFN_vkGetPhysicalDeviceQueueFamilyProperties = void (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pQueueFamilyPropertyCount, VkQueueFamilyProperties *  pQueueFamilyProperties);
using PFN_vkGetPhysicalDeviceMemoryProperties = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceMemoryProperties *  pMemoryProperties);
using PFN_vkGetPhysicalDeviceFeatures = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceFeatures *  pFeatures);
using PFN_vkGetPhysicalDeviceFormatProperties = void (*) (VkPhysicalDevice   physicalDevice, VkFormat   format, VkFormatProperties *  pFormatProperties);
using PFN_vkGetPhysicalDeviceImageFormatProperties = VkResult (*) (VkPhysicalDevice   physicalDevice, VkFormat   format, VkImageType   type, VkImageTiling   tiling, VkImageUsageFlags   usage, VkImageCreateFlags   flags, VkImageFormatProperties *  pImageFormatProperties);
using PFN_vkCreateDevice = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkDeviceCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDevice *  pDevice);
using PFN_vkDestroyDevice = void (*) (VkDevice   device, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkEnumerateInstanceVersion = VkResult (*) (uint32_t *  pApiVersion);
using PFN_vkEnumerateInstanceLayerProperties = VkResult (*) (uint32_t *  pPropertyCount, VkLayerProperties *  pProperties);
using PFN_vkEnumerateInstanceExtensionProperties = VkResult (*) (const  char *  pLayerName, uint32_t *  pPropertyCount, VkExtensionProperties *  pProperties);
using PFN_vkEnumerateDeviceExtensionProperties = VkResult (*) (VkPhysicalDevice   physicalDevice, const  char *  pLayerName, uint32_t *  pPropertyCount, VkExtensionProperties *  pProperties);
using PFN_vkGetDeviceQueue = void (*) (VkDevice   device, uint32_t   queueFamilyIndex, uint32_t   queueIndex, VkQueue *  pQueue);
using PFN_vkQueueSubmit = VkResult (*) (VkQueue   queue, uint32_t   submitCount, const  VkSubmitInfo *  pSubmits, VkFence   fence);
using PFN_vkQueueWaitIdle = VkResult (*) (VkQueue   queue);
using PFN_vkDeviceWaitIdle = VkResult (*) (VkDevice   device);
using PFN_vkAllocateMemory = VkResult (*) (VkDevice   device, const  VkMemoryAllocateInfo *  pAllocateInfo, const  VkAllocationCallbacks *  pAllocator, VkDeviceMemory *  pMemory);
using PFN_vkFreeMemory = void (*) (VkDevice   device, VkDeviceMemory   memory, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkMapMemory = VkResult (*) (VkDevice   device, VkDeviceMemory   memory, VkDeviceSize   offset, VkDeviceSize   size, VkMemoryMapFlags   flags, void **  ppData);
using PFN_vkUnmapMemory = void (*) (VkDevice   device, VkDeviceMemory   memory);
using PFN_vkFlushMappedMemoryRanges = VkResult (*) (VkDevice   device, uint32_t   memoryRangeCount, const  VkMappedMemoryRange *  pMemoryRanges);
using PFN_vkInvalidateMappedMemoryRanges = VkResult (*) (VkDevice   device, uint32_t   memoryRangeCount, const  VkMappedMemoryRange *  pMemoryRanges);
using PFN_vkGetDeviceMemoryCommitment = void (*) (VkDevice   device, VkDeviceMemory   memory, VkDeviceSize *  pCommittedMemoryInBytes);
using PFN_vkGetBufferMemoryRequirements = void (*) (VkDevice   device, VkBuffer   buffer, VkMemoryRequirements *  pMemoryRequirements);
using PFN_vkBindBufferMemory = VkResult (*) (VkDevice   device, VkBuffer   buffer, VkDeviceMemory   memory, VkDeviceSize   memoryOffset);
using PFN_vkGetImageMemoryRequirements = void (*) (VkDevice   device, VkImage   image, VkMemoryRequirements *  pMemoryRequirements);
using PFN_vkBindImageMemory = VkResult (*) (VkDevice   device, VkImage   image, VkDeviceMemory   memory, VkDeviceSize   memoryOffset);
using PFN_vkGetImageSparseMemoryRequirements = void (*) (VkDevice   device, VkImage   image, uint32_t *  pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements *  pSparseMemoryRequirements);
using PFN_vkGetPhysicalDeviceSparseImageFormatProperties = void (*) (VkPhysicalDevice   physicalDevice, VkFormat   format, VkImageType   type, VkSampleCountFlagBits   samples, VkImageUsageFlags   usage, VkImageTiling   tiling, uint32_t *  pPropertyCount, VkSparseImageFormatProperties *  pProperties);
using PFN_vkQueueBindSparse = VkResult (*) (VkQueue   queue, uint32_t   bindInfoCount, const  VkBindSparseInfo *  pBindInfo, VkFence   fence);
using PFN_vkCreateFence = VkResult (*) (VkDevice   device, const  VkFenceCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkFence *  pFence);
using PFN_vkDestroyFence = void (*) (VkDevice   device, VkFence   fence, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkResetFences = VkResult (*) (VkDevice   device, uint32_t   fenceCount, const  VkFence *  pFences);
using PFN_vkGetFenceStatus = VkResult (*) (VkDevice   device, VkFence   fence);
using PFN_vkWaitForFences = VkResult (*) (VkDevice   device, uint32_t   fenceCount, const  VkFence *  pFences, VkBool32   waitAll, uint64_t   timeout);
using PFN_vkCreateSemaphore = VkResult (*) (VkDevice   device, const  VkSemaphoreCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSemaphore *  pSemaphore);
using PFN_vkDestroySemaphore = void (*) (VkDevice   device, VkSemaphore   semaphore, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateEvent = VkResult (*) (VkDevice   device, const  VkEventCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkEvent *  pEvent);
using PFN_vkDestroyEvent = void (*) (VkDevice   device, VkEvent   event, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetEventStatus = VkResult (*) (VkDevice   device, VkEvent   event);
using PFN_vkSetEvent = VkResult (*) (VkDevice   device, VkEvent   event);
using PFN_vkResetEvent = VkResult (*) (VkDevice   device, VkEvent   event);
using PFN_vkCreateQueryPool = VkResult (*) (VkDevice   device, const  VkQueryPoolCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkQueryPool *  pQueryPool);
using PFN_vkDestroyQueryPool = void (*) (VkDevice   device, VkQueryPool   queryPool, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetQueryPoolResults = VkResult (*) (VkDevice   device, VkQueryPool   queryPool, uint32_t   firstQuery, uint32_t   queryCount, size_t   dataSize, void *  pData, VkDeviceSize   stride, VkQueryResultFlags   flags);
using PFN_vkResetQueryPool = void (*) (VkDevice   device, VkQueryPool   queryPool, uint32_t   firstQuery, uint32_t   queryCount);
using PFN_vkResetQueryPoolEXT = PFN_vkResetQueryPool;
using PFN_vkCreateBuffer = VkResult (*) (VkDevice   device, const  VkBufferCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkBuffer *  pBuffer);
using PFN_vkDestroyBuffer = void (*) (VkDevice   device, VkBuffer   buffer, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateBufferView = VkResult (*) (VkDevice   device, const  VkBufferViewCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkBufferView *  pView);
using PFN_vkDestroyBufferView = void (*) (VkDevice   device, VkBufferView   bufferView, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateImage = VkResult (*) (VkDevice   device, const  VkImageCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkImage *  pImage);
using PFN_vkDestroyImage = void (*) (VkDevice   device, VkImage   image, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetImageSubresourceLayout = void (*) (VkDevice   device, VkImage   image, const  VkImageSubresource *  pSubresource, VkSubresourceLayout *  pLayout);
using PFN_vkCreateImageView = VkResult (*) (VkDevice   device, const  VkImageViewCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkImageView *  pView);
using PFN_vkDestroyImageView = void (*) (VkDevice   device, VkImageView   imageView, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateShaderModule = VkResult (*) (VkDevice   device, const  VkShaderModuleCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkShaderModule *  pShaderModule);
using PFN_vkDestroyShaderModule = void (*) (VkDevice   device, VkShaderModule   shaderModule, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreatePipelineCache = VkResult (*) (VkDevice   device, const  VkPipelineCacheCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkPipelineCache *  pPipelineCache);
using PFN_vkDestroyPipelineCache = void (*) (VkDevice   device, VkPipelineCache   pipelineCache, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetPipelineCacheData = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, size_t *  pDataSize, void *  pData);
using PFN_vkMergePipelineCaches = VkResult (*) (VkDevice   device, VkPipelineCache   dstCache, uint32_t   srcCacheCount, const  VkPipelineCache *  pSrcCaches);
using PFN_vkCreateGraphicsPipelines = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkGraphicsPipelineCreateInfo *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
using PFN_vkCreateComputePipelines = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkComputePipelineCreateInfo *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
using PFN_vkDestroyPipeline = void (*) (VkDevice   device, VkPipeline   pipeline, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreatePipelineLayout = VkResult (*) (VkDevice   device, const  VkPipelineLayoutCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkPipelineLayout *  pPipelineLayout);
using PFN_vkDestroyPipelineLayout = void (*) (VkDevice   device, VkPipelineLayout   pipelineLayout, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateSampler = VkResult (*) (VkDevice   device, const  VkSamplerCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSampler *  pSampler);
using PFN_vkDestroySampler = void (*) (VkDevice   device, VkSampler   sampler, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateDescriptorSetLayout = VkResult (*) (VkDevice   device, const  VkDescriptorSetLayoutCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDescriptorSetLayout *  pSetLayout);
using PFN_vkDestroyDescriptorSetLayout = void (*) (VkDevice   device, VkDescriptorSetLayout   descriptorSetLayout, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateDescriptorPool = VkResult (*) (VkDevice   device, const  VkDescriptorPoolCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDescriptorPool *  pDescriptorPool);
using PFN_vkDestroyDescriptorPool = void (*) (VkDevice   device, VkDescriptorPool   descriptorPool, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkResetDescriptorPool = VkResult (*) (VkDevice   device, VkDescriptorPool   descriptorPool, VkDescriptorPoolResetFlags   flags);
using PFN_vkAllocateDescriptorSets = VkResult (*) (VkDevice   device, const  VkDescriptorSetAllocateInfo *  pAllocateInfo, VkDescriptorSet *  pDescriptorSets);
using PFN_vkFreeDescriptorSets = VkResult (*) (VkDevice   device, VkDescriptorPool   descriptorPool, uint32_t   descriptorSetCount, const  VkDescriptorSet *  pDescriptorSets);
using PFN_vkUpdateDescriptorSets = void (*) (VkDevice   device, uint32_t   descriptorWriteCount, const  VkWriteDescriptorSet *  pDescriptorWrites, uint32_t   descriptorCopyCount, const  VkCopyDescriptorSet *  pDescriptorCopies);
using PFN_vkCreateFramebuffer = VkResult (*) (VkDevice   device, const  VkFramebufferCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkFramebuffer *  pFramebuffer);
using PFN_vkDestroyFramebuffer = void (*) (VkDevice   device, VkFramebuffer   framebuffer, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateRenderPass = VkResult (*) (VkDevice   device, const  VkRenderPassCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkRenderPass *  pRenderPass);
using PFN_vkDestroyRenderPass = void (*) (VkDevice   device, VkRenderPass   renderPass, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetRenderAreaGranularity = void (*) (VkDevice   device, VkRenderPass   renderPass, VkExtent2D *  pGranularity);
using PFN_vkCreateCommandPool = VkResult (*) (VkDevice   device, const  VkCommandPoolCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkCommandPool *  pCommandPool);
using PFN_vkDestroyCommandPool = void (*) (VkDevice   device, VkCommandPool   commandPool, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkResetCommandPool = VkResult (*) (VkDevice   device, VkCommandPool   commandPool, VkCommandPoolResetFlags   flags);
using PFN_vkAllocateCommandBuffers = VkResult (*) (VkDevice   device, const  VkCommandBufferAllocateInfo *  pAllocateInfo, VkCommandBuffer *  pCommandBuffers);
using PFN_vkFreeCommandBuffers = void (*) (VkDevice   device, VkCommandPool   commandPool, uint32_t   commandBufferCount, const  VkCommandBuffer *  pCommandBuffers);
using PFN_vkBeginCommandBuffer = VkResult (*) (VkCommandBuffer   commandBuffer, const  VkCommandBufferBeginInfo *  pBeginInfo);
using PFN_vkEndCommandBuffer = VkResult (*) (VkCommandBuffer   commandBuffer);
using PFN_vkResetCommandBuffer = VkResult (*) (VkCommandBuffer   commandBuffer, VkCommandBufferResetFlags   flags);
using PFN_vkCmdBindPipeline = void (*) (VkCommandBuffer   commandBuffer, VkPipelineBindPoint   pipelineBindPoint, VkPipeline   pipeline);
using PFN_vkCmdSetViewport = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstViewport, uint32_t   viewportCount, const  VkViewport *  pViewports);
using PFN_vkCmdSetScissor = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstScissor, uint32_t   scissorCount, const  VkRect2D *  pScissors);
using PFN_vkCmdSetLineWidth = void (*) (VkCommandBuffer   commandBuffer, float   lineWidth);
using PFN_vkCmdSetDepthBias = void (*) (VkCommandBuffer   commandBuffer, float   depthBiasConstantFactor, float   depthBiasClamp, float   depthBiasSlopeFactor);
using PFN_vkCmdSetBlendConstants = void (*) (VkCommandBuffer   commandBuffer, const  float   blendConstants [4]);
using PFN_vkCmdSetDepthBounds = void (*) (VkCommandBuffer   commandBuffer, float   minDepthBounds, float   maxDepthBounds);
using PFN_vkCmdSetStencilCompareMask = void (*) (VkCommandBuffer   commandBuffer, VkStencilFaceFlags   faceMask, uint32_t   compareMask);
using PFN_vkCmdSetStencilWriteMask = void (*) (VkCommandBuffer   commandBuffer, VkStencilFaceFlags   faceMask, uint32_t   writeMask);
using PFN_vkCmdSetStencilReference = void (*) (VkCommandBuffer   commandBuffer, VkStencilFaceFlags   faceMask, uint32_t   reference);
using PFN_vkCmdBindDescriptorSets = void (*) (VkCommandBuffer   commandBuffer, VkPipelineBindPoint   pipelineBindPoint, VkPipelineLayout   layout, uint32_t   firstSet, uint32_t   descriptorSetCount, const  VkDescriptorSet *  pDescriptorSets, uint32_t   dynamicOffsetCount, const  uint32_t *  pDynamicOffsets);
using PFN_vkCmdBindIndexBuffer = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, VkIndexType   indexType);
using PFN_vkCmdBindVertexBuffers = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstBinding, uint32_t   bindingCount, const  VkBuffer *  pBuffers, const  VkDeviceSize *  pOffsets);
using PFN_vkCmdDraw = void (*) (VkCommandBuffer   commandBuffer, uint32_t   vertexCount, uint32_t   instanceCount, uint32_t   firstVertex, uint32_t   firstInstance);
using PFN_vkCmdDrawIndexed = void (*) (VkCommandBuffer   commandBuffer, uint32_t   indexCount, uint32_t   instanceCount, uint32_t   firstIndex, int32_t   vertexOffset, uint32_t   firstInstance);
using PFN_vkCmdDrawIndirect = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, uint32_t   drawCount, uint32_t   stride);
using PFN_vkCmdDrawIndexedIndirect = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, uint32_t   drawCount, uint32_t   stride);
using PFN_vkCmdDispatch = void (*) (VkCommandBuffer   commandBuffer, uint32_t   groupCountX, uint32_t   groupCountY, uint32_t   groupCountZ);
using PFN_vkCmdDispatchIndirect = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset);
using PFN_vkCmdCopyBuffer = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   srcBuffer, VkBuffer   dstBuffer, uint32_t   regionCount, const  VkBufferCopy *  pRegions);
using PFN_vkCmdCopyImage = void (*) (VkCommandBuffer   commandBuffer, VkImage   srcImage, VkImageLayout   srcImageLayout, VkImage   dstImage, VkImageLayout   dstImageLayout, uint32_t   regionCount, const  VkImageCopy *  pRegions);
using PFN_vkCmdBlitImage = void (*) (VkCommandBuffer   commandBuffer, VkImage   srcImage, VkImageLayout   srcImageLayout, VkImage   dstImage, VkImageLayout   dstImageLayout, uint32_t   regionCount, const  VkImageBlit *  pRegions, VkFilter   filter);
using PFN_vkCmdCopyBufferToImage = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   srcBuffer, VkImage   dstImage, VkImageLayout   dstImageLayout, uint32_t   regionCount, const  VkBufferImageCopy *  pRegions);
using PFN_vkCmdCopyImageToBuffer = void (*) (VkCommandBuffer   commandBuffer, VkImage   srcImage, VkImageLayout   srcImageLayout, VkBuffer   dstBuffer, uint32_t   regionCount, const  VkBufferImageCopy *  pRegions);
using PFN_vkCmdUpdateBuffer = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   dstBuffer, VkDeviceSize   dstOffset, VkDeviceSize   dataSize, const  void *  pData);
using PFN_vkCmdFillBuffer = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   dstBuffer, VkDeviceSize   dstOffset, VkDeviceSize   size, uint32_t   data);
using PFN_vkCmdClearColorImage = void (*) (VkCommandBuffer   commandBuffer, VkImage   image, VkImageLayout   imageLayout, const  VkClearColorValue *  pColor, uint32_t   rangeCount, const  VkImageSubresourceRange *  pRanges);
using PFN_vkCmdClearDepthStencilImage = void (*) (VkCommandBuffer   commandBuffer, VkImage   image, VkImageLayout   imageLayout, const  VkClearDepthStencilValue *  pDepthStencil, uint32_t   rangeCount, const  VkImageSubresourceRange *  pRanges);
using PFN_vkCmdClearAttachments = void (*) (VkCommandBuffer   commandBuffer, uint32_t   attachmentCount, const  VkClearAttachment *  pAttachments, uint32_t   rectCount, const  VkClearRect *  pRects);
using PFN_vkCmdResolveImage = void (*) (VkCommandBuffer   commandBuffer, VkImage   srcImage, VkImageLayout   srcImageLayout, VkImage   dstImage, VkImageLayout   dstImageLayout, uint32_t   regionCount, const  VkImageResolve *  pRegions);
using PFN_vkCmdSetEvent = void (*) (VkCommandBuffer   commandBuffer, VkEvent   event, VkPipelineStageFlags   stageMask);
using PFN_vkCmdResetEvent = void (*) (VkCommandBuffer   commandBuffer, VkEvent   event, VkPipelineStageFlags   stageMask);
using PFN_vkCmdWaitEvents = void (*) (VkCommandBuffer   commandBuffer, uint32_t   eventCount, const  VkEvent *  pEvents, VkPipelineStageFlags   srcStageMask, VkPipelineStageFlags   dstStageMask, uint32_t   memoryBarrierCount, const  VkMemoryBarrier *  pMemoryBarriers, uint32_t   bufferMemoryBarrierCount, const  VkBufferMemoryBarrier *  pBufferMemoryBarriers, uint32_t   imageMemoryBarrierCount, const  VkImageMemoryBarrier *  pImageMemoryBarriers);
using PFN_vkCmdPipelineBarrier = void (*) (VkCommandBuffer   commandBuffer, VkPipelineStageFlags   srcStageMask, VkPipelineStageFlags   dstStageMask, VkDependencyFlags   dependencyFlags, uint32_t   memoryBarrierCount, const  VkMemoryBarrier *  pMemoryBarriers, uint32_t   bufferMemoryBarrierCount, const  VkBufferMemoryBarrier *  pBufferMemoryBarriers, uint32_t   imageMemoryBarrierCount, const  VkImageMemoryBarrier *  pImageMemoryBarriers);
using PFN_vkCmdBeginQuery = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   query, VkQueryControlFlags   flags);
using PFN_vkCmdEndQuery = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   query);
using PFN_vkCmdBeginConditionalRenderingEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkConditionalRenderingBeginInfoEXT *  pConditionalRenderingBegin);
using PFN_vkCmdEndConditionalRenderingEXT = void (*) (VkCommandBuffer   commandBuffer);
using PFN_vkCmdResetQueryPool = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   firstQuery, uint32_t   queryCount);
using PFN_vkCmdWriteTimestamp = void (*) (VkCommandBuffer   commandBuffer, VkPipelineStageFlagBits   pipelineStage, VkQueryPool   queryPool, uint32_t   query);
using PFN_vkCmdCopyQueryPoolResults = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   firstQuery, uint32_t   queryCount, VkBuffer   dstBuffer, VkDeviceSize   dstOffset, VkDeviceSize   stride, VkQueryResultFlags   flags);
using PFN_vkCmdPushConstants = void (*) (VkCommandBuffer   commandBuffer, VkPipelineLayout   layout, VkShaderStageFlags   stageFlags, uint32_t   offset, uint32_t   size, const  void *  pValues);
using PFN_vkCmdBeginRenderPass = void (*) (VkCommandBuffer   commandBuffer, const  VkRenderPassBeginInfo *  pRenderPassBegin, VkSubpassContents   contents);
using PFN_vkCmdNextSubpass = void (*) (VkCommandBuffer   commandBuffer, VkSubpassContents   contents);
using PFN_vkCmdEndRenderPass = void (*) (VkCommandBuffer   commandBuffer);
using PFN_vkCmdExecuteCommands = void (*) (VkCommandBuffer   commandBuffer, uint32_t   commandBufferCount, const  VkCommandBuffer *  pCommandBuffers);
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_vkCreateAndroidSurfaceKHR = VkResult (*) (VkInstance   instance, const  VkAndroidSurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_vkGetPhysicalDeviceDisplayPropertiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkDisplayPropertiesKHR *  pProperties);
using PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkDisplayPlanePropertiesKHR *  pProperties);
using PFN_vkGetDisplayPlaneSupportedDisplaysKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t   planeIndex, uint32_t *  pDisplayCount, VkDisplayKHR *  pDisplays);
using PFN_vkGetDisplayModePropertiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayKHR   display, uint32_t *  pPropertyCount, VkDisplayModePropertiesKHR *  pProperties);
using PFN_vkCreateDisplayModeKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayKHR   display, const  VkDisplayModeCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDisplayModeKHR *  pMode);
using PFN_vkGetDisplayPlaneCapabilitiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayModeKHR   mode, uint32_t   planeIndex, VkDisplayPlaneCapabilitiesKHR *  pCapabilities);
using PFN_vkCreateDisplayPlaneSurfaceKHR = VkResult (*) (VkInstance   instance, const  VkDisplaySurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkCreateSharedSwapchainsKHR = VkResult (*) (VkDevice   device, uint32_t   swapchainCount, const  VkSwapchainCreateInfoKHR *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkSwapchainKHR *  pSwapchains);
using PFN_vkDestroySurfaceKHR = void (*) (VkInstance   instance, VkSurfaceKHR   surface, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetPhysicalDeviceSurfaceSupportKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, VkSurfaceKHR   surface, VkBool32 *  pSupported);
using PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkSurfaceKHR   surface, VkSurfaceCapabilitiesKHR *  pSurfaceCapabilities);
using PFN_vkGetPhysicalDeviceSurfaceFormatsKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkSurfaceKHR   surface, uint32_t *  pSurfaceFormatCount, VkSurfaceFormatKHR *  pSurfaceFormats);
using PFN_vkGetPhysicalDeviceSurfacePresentModesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkSurfaceKHR   surface, uint32_t *  pPresentModeCount, VkPresentModeKHR *  pPresentModes);
using PFN_vkCreateSwapchainKHR = VkResult (*) (VkDevice   device, const  VkSwapchainCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSwapchainKHR *  pSwapchain);
using PFN_vkDestroySwapchainKHR = void (*) (VkDevice   device, VkSwapchainKHR   swapchain, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetSwapchainImagesKHR = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain, uint32_t *  pSwapchainImageCount, VkImage *  pSwapchainImages);
using PFN_vkAcquireNextImageKHR = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain, uint64_t   timeout, VkSemaphore   semaphore, VkFence   fence, uint32_t *  pImageIndex);
using PFN_vkQueuePresentKHR = VkResult (*) (VkQueue   queue, const  VkPresentInfoKHR *  pPresentInfo);
#if defined(VK_USE_PLATFORM_VI_NN)
using PFN_vkCreateViSurfaceNN = VkResult (*) (VkInstance   instance, const  VkViSurfaceCreateInfoNN *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
using PFN_vkCreateWaylandSurfaceKHR = VkResult (*) (VkInstance   instance, const  VkWaylandSurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, struct  wl_display *  display);
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkCreateWin32SurfaceKHR = VkResult (*) (VkInstance   instance, const  VkWin32SurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
using PFN_vkCreateXlibSurfaceKHR = VkResult (*) (VkInstance   instance, const  VkXlibSurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, Display *  dpy, VisualID   visualID);
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
using PFN_vkCreateXcbSurfaceKHR = VkResult (*) (VkInstance   instance, const  VkXcbSurfaceCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, xcb_connection_t *  connection, xcb_visualid_t   visual_id);
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
using PFN_vkCreateDirectFBSurfaceEXT = VkResult (*) (VkInstance   instance, const  VkDirectFBSurfaceCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, IDirectFB *  dfb);
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
using PFN_vkCreateImagePipeSurfaceFUCHSIA = VkResult (*) (VkInstance   instance, const  VkImagePipeSurfaceCreateInfoFUCHSIA *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
using PFN_vkCreateStreamDescriptorSurfaceGGP = VkResult (*) (VkInstance   instance, const  VkStreamDescriptorSurfaceCreateInfoGGP *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_GGP)
using PFN_vkCreateDebugReportCallbackEXT = VkResult (*) (VkInstance   instance, const  VkDebugReportCallbackCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDebugReportCallbackEXT *  pCallback);
using PFN_vkDestroyDebugReportCallbackEXT = void (*) (VkInstance   instance, VkDebugReportCallbackEXT   callback, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkDebugReportMessageEXT = void (*) (VkInstance   instance, VkDebugReportFlagsEXT   flags, VkDebugReportObjectTypeEXT   objectType, uint64_t   object, size_t   location, int32_t   messageCode, const  char *  pLayerPrefix, const  char *  pMessage);
using PFN_vkDebugMarkerSetObjectNameEXT = VkResult (*) (VkDevice   device, const  VkDebugMarkerObjectNameInfoEXT *  pNameInfo);
using PFN_vkDebugMarkerSetObjectTagEXT = VkResult (*) (VkDevice   device, const  VkDebugMarkerObjectTagInfoEXT *  pTagInfo);
using PFN_vkCmdDebugMarkerBeginEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkDebugMarkerMarkerInfoEXT *  pMarkerInfo);
using PFN_vkCmdDebugMarkerEndEXT = void (*) (VkCommandBuffer   commandBuffer);
using PFN_vkCmdDebugMarkerInsertEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkDebugMarkerMarkerInfoEXT *  pMarkerInfo);
using PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV = VkResult (*) (VkPhysicalDevice   physicalDevice, VkFormat   format, VkImageType   type, VkImageTiling   tiling, VkImageUsageFlags   usage, VkImageCreateFlags   flags, VkExternalMemoryHandleTypeFlagsNV   externalHandleType, VkExternalImageFormatPropertiesNV *  pExternalImageFormatProperties);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetMemoryWin32HandleNV = VkResult (*) (VkDevice   device, VkDeviceMemory   memory, VkExternalMemoryHandleTypeFlagsNV   handleType, HANDLE *  pHandle);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkCmdExecuteGeneratedCommandsNV = void (*) (VkCommandBuffer   commandBuffer, VkBool32   isPreprocessed, const  VkGeneratedCommandsInfoNV *  pGeneratedCommandsInfo);
using PFN_vkCmdPreprocessGeneratedCommandsNV = void (*) (VkCommandBuffer   commandBuffer, const  VkGeneratedCommandsInfoNV *  pGeneratedCommandsInfo);
using PFN_vkCmdBindPipelineShaderGroupNV = void (*) (VkCommandBuffer   commandBuffer, VkPipelineBindPoint   pipelineBindPoint, VkPipeline   pipeline, uint32_t   groupIndex);
using PFN_vkGetGeneratedCommandsMemoryRequirementsNV = void (*) (VkDevice   device, const  VkGeneratedCommandsMemoryRequirementsInfoNV *  pInfo, VkMemoryRequirements2 *  pMemoryRequirements);
using PFN_vkCreateIndirectCommandsLayoutNV = VkResult (*) (VkDevice   device, const  VkIndirectCommandsLayoutCreateInfoNV *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkIndirectCommandsLayoutNV *  pIndirectCommandsLayout);
using PFN_vkDestroyIndirectCommandsLayoutNV = void (*) (VkDevice   device, VkIndirectCommandsLayoutNV   indirectCommandsLayout, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetPhysicalDeviceFeatures2 = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceFeatures2 *  pFeatures);
using PFN_vkGetPhysicalDeviceFeatures2KHR = PFN_vkGetPhysicalDeviceFeatures2;
using PFN_vkGetPhysicalDeviceProperties2 = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceProperties2 *  pProperties);
using PFN_vkGetPhysicalDeviceProperties2KHR = PFN_vkGetPhysicalDeviceProperties2;
using PFN_vkGetPhysicalDeviceFormatProperties2 = void (*) (VkPhysicalDevice   physicalDevice, VkFormat   format, VkFormatProperties2 *  pFormatProperties);
using PFN_vkGetPhysicalDeviceFormatProperties2KHR = PFN_vkGetPhysicalDeviceFormatProperties2;
using PFN_vkGetPhysicalDeviceImageFormatProperties2 = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceImageFormatInfo2 *  pImageFormatInfo, VkImageFormatProperties2 *  pImageFormatProperties);
using PFN_vkGetPhysicalDeviceImageFormatProperties2KHR = PFN_vkGetPhysicalDeviceImageFormatProperties2;
using PFN_vkGetPhysicalDeviceQueueFamilyProperties2 = void (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pQueueFamilyPropertyCount, VkQueueFamilyProperties2 *  pQueueFamilyProperties);
using PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR = PFN_vkGetPhysicalDeviceQueueFamilyProperties2;
using PFN_vkGetPhysicalDeviceMemoryProperties2 = void (*) (VkPhysicalDevice   physicalDevice, VkPhysicalDeviceMemoryProperties2 *  pMemoryProperties);
using PFN_vkGetPhysicalDeviceMemoryProperties2KHR = PFN_vkGetPhysicalDeviceMemoryProperties2;
using PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 = void (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceSparseImageFormatInfo2 *  pFormatInfo, uint32_t *  pPropertyCount, VkSparseImageFormatProperties2 *  pProperties);
using PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR = PFN_vkGetPhysicalDeviceSparseImageFormatProperties2;
using PFN_vkCmdPushDescriptorSetKHR = void (*) (VkCommandBuffer   commandBuffer, VkPipelineBindPoint   pipelineBindPoint, VkPipelineLayout   layout, uint32_t   set, uint32_t   descriptorWriteCount, const  VkWriteDescriptorSet *  pDescriptorWrites);
using PFN_vkTrimCommandPool = void (*) (VkDevice   device, VkCommandPool   commandPool, VkCommandPoolTrimFlags   flags);
using PFN_vkTrimCommandPoolKHR = PFN_vkTrimCommandPool;
using PFN_vkGetPhysicalDeviceExternalBufferProperties = void (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceExternalBufferInfo *  pExternalBufferInfo, VkExternalBufferProperties *  pExternalBufferProperties);
using PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR = PFN_vkGetPhysicalDeviceExternalBufferProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetMemoryWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkMemoryGetWin32HandleInfoKHR *  pGetWin32HandleInfo, HANDLE *  pHandle);
using PFN_vkGetMemoryWin32HandlePropertiesKHR = VkResult (*) (VkDevice   device, VkExternalMemoryHandleTypeFlagBits   handleType, HANDLE   handle, VkMemoryWin32HandlePropertiesKHR *  pMemoryWin32HandleProperties);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetMemoryFdKHR = VkResult (*) (VkDevice   device, const  VkMemoryGetFdInfoKHR *  pGetFdInfo, int *  pFd);
using PFN_vkGetMemoryFdPropertiesKHR = VkResult (*) (VkDevice   device, VkExternalMemoryHandleTypeFlagBits   handleType, int   fd, VkMemoryFdPropertiesKHR *  pMemoryFdProperties);
using PFN_vkGetPhysicalDeviceExternalSemaphoreProperties = void (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceExternalSemaphoreInfo *  pExternalSemaphoreInfo, VkExternalSemaphoreProperties *  pExternalSemaphoreProperties);
using PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = PFN_vkGetPhysicalDeviceExternalSemaphoreProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetSemaphoreWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkSemaphoreGetWin32HandleInfoKHR *  pGetWin32HandleInfo, HANDLE *  pHandle);
using PFN_vkImportSemaphoreWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkImportSemaphoreWin32HandleInfoKHR *  pImportSemaphoreWin32HandleInfo);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetSemaphoreFdKHR = VkResult (*) (VkDevice   device, const  VkSemaphoreGetFdInfoKHR *  pGetFdInfo, int *  pFd);
using PFN_vkImportSemaphoreFdKHR = VkResult (*) (VkDevice   device, const  VkImportSemaphoreFdInfoKHR *  pImportSemaphoreFdInfo);
using PFN_vkGetPhysicalDeviceExternalFenceProperties = void (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceExternalFenceInfo *  pExternalFenceInfo, VkExternalFenceProperties *  pExternalFenceProperties);
using PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR = PFN_vkGetPhysicalDeviceExternalFenceProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetFenceWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkFenceGetWin32HandleInfoKHR *  pGetWin32HandleInfo, HANDLE *  pHandle);
using PFN_vkImportFenceWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkImportFenceWin32HandleInfoKHR *  pImportFenceWin32HandleInfo);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetFenceFdKHR = VkResult (*) (VkDevice   device, const  VkFenceGetFdInfoKHR *  pGetFdInfo, int *  pFd);
using PFN_vkImportFenceFdKHR = VkResult (*) (VkDevice   device, const  VkImportFenceFdInfoKHR *  pImportFenceFdInfo);
using PFN_vkReleaseDisplayEXT = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayKHR   display);
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
using PFN_vkAcquireXlibDisplayEXT = VkResult (*) (VkPhysicalDevice   physicalDevice, Display *  dpy, VkDisplayKHR   display);
using PFN_vkGetRandROutputDisplayEXT = VkResult (*) (VkPhysicalDevice   physicalDevice, Display *  dpy, RROutput   rrOutput, VkDisplayKHR *  pDisplay);
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
using PFN_vkDisplayPowerControlEXT = VkResult (*) (VkDevice   device, VkDisplayKHR   display, const  VkDisplayPowerInfoEXT *  pDisplayPowerInfo);
using PFN_vkRegisterDeviceEventEXT = VkResult (*) (VkDevice   device, const  VkDeviceEventInfoEXT *  pDeviceEventInfo, const  VkAllocationCallbacks *  pAllocator, VkFence *  pFence);
using PFN_vkRegisterDisplayEventEXT = VkResult (*) (VkDevice   device, VkDisplayKHR   display, const  VkDisplayEventInfoEXT *  pDisplayEventInfo, const  VkAllocationCallbacks *  pAllocator, VkFence *  pFence);
using PFN_vkGetSwapchainCounterEXT = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain, VkSurfaceCounterFlagBitsEXT   counter, uint64_t *  pCounterValue);
using PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT = VkResult (*) (VkPhysicalDevice   physicalDevice, VkSurfaceKHR   surface, VkSurfaceCapabilities2EXT *  pSurfaceCapabilities);
using PFN_vkEnumeratePhysicalDeviceGroups = VkResult (*) (VkInstance   instance, uint32_t *  pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *  pPhysicalDeviceGroupProperties);
using PFN_vkEnumeratePhysicalDeviceGroupsKHR = PFN_vkEnumeratePhysicalDeviceGroups;
using PFN_vkGetDeviceGroupPeerMemoryFeatures = void (*) (VkDevice   device, uint32_t   heapIndex, uint32_t   localDeviceIndex, uint32_t   remoteDeviceIndex, VkPeerMemoryFeatureFlags *  pPeerMemoryFeatures);
using PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR = PFN_vkGetDeviceGroupPeerMemoryFeatures;
using PFN_vkBindBufferMemory2 = VkResult (*) (VkDevice   device, uint32_t   bindInfoCount, const  VkBindBufferMemoryInfo *  pBindInfos);
using PFN_vkBindBufferMemory2KHR = PFN_vkBindBufferMemory2;
using PFN_vkBindImageMemory2 = VkResult (*) (VkDevice   device, uint32_t   bindInfoCount, const  VkBindImageMemoryInfo *  pBindInfos);
using PFN_vkBindImageMemory2KHR = PFN_vkBindImageMemory2;
using PFN_vkCmdSetDeviceMask = void (*) (VkCommandBuffer   commandBuffer, uint32_t   deviceMask);
using PFN_vkCmdSetDeviceMaskKHR = PFN_vkCmdSetDeviceMask;
using PFN_vkGetDeviceGroupPresentCapabilitiesKHR = VkResult (*) (VkDevice   device, VkDeviceGroupPresentCapabilitiesKHR *  pDeviceGroupPresentCapabilities);
using PFN_vkGetDeviceGroupSurfacePresentModesKHR = VkResult (*) (VkDevice   device, VkSurfaceKHR   surface, VkDeviceGroupPresentModeFlagsKHR *  pModes);
using PFN_vkAcquireNextImage2KHR = VkResult (*) (VkDevice   device, const  VkAcquireNextImageInfoKHR *  pAcquireInfo, uint32_t *  pImageIndex);
using PFN_vkCmdDispatchBase = void (*) (VkCommandBuffer   commandBuffer, uint32_t   baseGroupX, uint32_t   baseGroupY, uint32_t   baseGroupZ, uint32_t   groupCountX, uint32_t   groupCountY, uint32_t   groupCountZ);
using PFN_vkCmdDispatchBaseKHR = PFN_vkCmdDispatchBase;
using PFN_vkGetPhysicalDevicePresentRectanglesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkSurfaceKHR   surface, uint32_t *  pRectCount, VkRect2D *  pRects);
using PFN_vkCreateDescriptorUpdateTemplate = VkResult (*) (VkDevice   device, const  VkDescriptorUpdateTemplateCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDescriptorUpdateTemplate *  pDescriptorUpdateTemplate);
using PFN_vkCreateDescriptorUpdateTemplateKHR = PFN_vkCreateDescriptorUpdateTemplate;
using PFN_vkDestroyDescriptorUpdateTemplate = void (*) (VkDevice   device, VkDescriptorUpdateTemplate   descriptorUpdateTemplate, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkDestroyDescriptorUpdateTemplateKHR = PFN_vkDestroyDescriptorUpdateTemplate;
using PFN_vkUpdateDescriptorSetWithTemplate = void (*) (VkDevice   device, VkDescriptorSet   descriptorSet, VkDescriptorUpdateTemplate   descriptorUpdateTemplate, const  void *  pData);
using PFN_vkUpdateDescriptorSetWithTemplateKHR = PFN_vkUpdateDescriptorSetWithTemplate;
using PFN_vkCmdPushDescriptorSetWithTemplateKHR = void (*) (VkCommandBuffer   commandBuffer, VkDescriptorUpdateTemplate   descriptorUpdateTemplate, VkPipelineLayout   layout, uint32_t   set, const  void *  pData);
using PFN_vkSetHdrMetadataEXT = void (*) (VkDevice   device, uint32_t   swapchainCount, const  VkSwapchainKHR *  pSwapchains, const  VkHdrMetadataEXT *  pMetadata);
using PFN_vkGetSwapchainStatusKHR = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain);
using PFN_vkGetRefreshCycleDurationGOOGLE = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain, VkRefreshCycleDurationGOOGLE *  pDisplayTimingProperties);
using PFN_vkGetPastPresentationTimingGOOGLE = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain, uint32_t *  pPresentationTimingCount, VkPastPresentationTimingGOOGLE *  pPresentationTimings);
#if defined(VK_USE_PLATFORM_IOS_MVK)
using PFN_vkCreateIOSSurfaceMVK = VkResult (*) (VkInstance   instance, const  VkIOSSurfaceCreateInfoMVK *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
using PFN_vkCreateMacOSSurfaceMVK = VkResult (*) (VkInstance   instance, const  VkMacOSSurfaceCreateInfoMVK *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
using PFN_vkCreateMetalSurfaceEXT = VkResult (*) (VkInstance   instance, const  VkMetalSurfaceCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
using PFN_vkCmdSetViewportWScalingNV = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstViewport, uint32_t   viewportCount, const  VkViewportWScalingNV *  pViewportWScalings);
using PFN_vkCmdSetDiscardRectangleEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstDiscardRectangle, uint32_t   discardRectangleCount, const  VkRect2D *  pDiscardRectangles);
using PFN_vkCmdSetSampleLocationsEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkSampleLocationsInfoEXT *  pSampleLocationsInfo);
using PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT = void (*) (VkPhysicalDevice   physicalDevice, VkSampleCountFlagBits   samples, VkMultisamplePropertiesEXT *  pMultisampleProperties);
using PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceSurfaceInfo2KHR *  pSurfaceInfo, VkSurfaceCapabilities2KHR *  pSurfaceCapabilities);
using PFN_vkGetPhysicalDeviceSurfaceFormats2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceSurfaceInfo2KHR *  pSurfaceInfo, uint32_t *  pSurfaceFormatCount, VkSurfaceFormat2KHR *  pSurfaceFormats);
using PFN_vkGetPhysicalDeviceDisplayProperties2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkDisplayProperties2KHR *  pProperties);
using PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkDisplayPlaneProperties2KHR *  pProperties);
using PFN_vkGetDisplayModeProperties2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayKHR   display, uint32_t *  pPropertyCount, VkDisplayModeProperties2KHR *  pProperties);
using PFN_vkGetDisplayPlaneCapabilities2KHR = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkDisplayPlaneInfo2KHR *  pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR *  pCapabilities);
using PFN_vkGetBufferMemoryRequirements2 = void (*) (VkDevice   device, const  VkBufferMemoryRequirementsInfo2 *  pInfo, VkMemoryRequirements2 *  pMemoryRequirements);
using PFN_vkGetBufferMemoryRequirements2KHR = PFN_vkGetBufferMemoryRequirements2;
using PFN_vkGetImageMemoryRequirements2 = void (*) (VkDevice   device, const  VkImageMemoryRequirementsInfo2 *  pInfo, VkMemoryRequirements2 *  pMemoryRequirements);
using PFN_vkGetImageMemoryRequirements2KHR = PFN_vkGetImageMemoryRequirements2;
using PFN_vkGetImageSparseMemoryRequirements2 = void (*) (VkDevice   device, const  VkImageSparseMemoryRequirementsInfo2 *  pInfo, uint32_t *  pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 *  pSparseMemoryRequirements);
using PFN_vkGetImageSparseMemoryRequirements2KHR = PFN_vkGetImageSparseMemoryRequirements2;
using PFN_vkCreateSamplerYcbcrConversion = VkResult (*) (VkDevice   device, const  VkSamplerYcbcrConversionCreateInfo *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSamplerYcbcrConversion *  pYcbcrConversion);
using PFN_vkCreateSamplerYcbcrConversionKHR = PFN_vkCreateSamplerYcbcrConversion;
using PFN_vkDestroySamplerYcbcrConversion = void (*) (VkDevice   device, VkSamplerYcbcrConversion   ycbcrConversion, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkDestroySamplerYcbcrConversionKHR = PFN_vkDestroySamplerYcbcrConversion;
using PFN_vkGetDeviceQueue2 = void (*) (VkDevice   device, const  VkDeviceQueueInfo2 *  pQueueInfo, VkQueue *  pQueue);
using PFN_vkCreateValidationCacheEXT = VkResult (*) (VkDevice   device, const  VkValidationCacheCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkValidationCacheEXT *  pValidationCache);
using PFN_vkDestroyValidationCacheEXT = void (*) (VkDevice   device, VkValidationCacheEXT   validationCache, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetValidationCacheDataEXT = VkResult (*) (VkDevice   device, VkValidationCacheEXT   validationCache, size_t *  pDataSize, void *  pData);
using PFN_vkMergeValidationCachesEXT = VkResult (*) (VkDevice   device, VkValidationCacheEXT   dstCache, uint32_t   srcCacheCount, const  VkValidationCacheEXT *  pSrcCaches);
using PFN_vkGetDescriptorSetLayoutSupport = void (*) (VkDevice   device, const  VkDescriptorSetLayoutCreateInfo *  pCreateInfo, VkDescriptorSetLayoutSupport *  pSupport);
using PFN_vkGetDescriptorSetLayoutSupportKHR = PFN_vkGetDescriptorSetLayoutSupport;
using PFN_vkGetShaderInfoAMD = VkResult (*) (VkDevice   device, VkPipeline   pipeline, VkShaderStageFlagBits   shaderStage, VkShaderInfoTypeAMD   infoType, size_t *  pInfoSize, void *  pInfo);
using PFN_vkSetLocalDimmingAMD = void (*) (VkDevice   device, VkSwapchainKHR   swapChain, VkBool32   localDimmingEnable);
using PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pTimeDomainCount, VkTimeDomainEXT *  pTimeDomains);
using PFN_vkGetCalibratedTimestampsEXT = VkResult (*) (VkDevice   device, uint32_t   timestampCount, const  VkCalibratedTimestampInfoEXT *  pTimestampInfos, uint64_t *  pTimestamps, uint64_t *  pMaxDeviation);
using PFN_vkSetDebugUtilsObjectNameEXT = VkResult (*) (VkDevice   device, const  VkDebugUtilsObjectNameInfoEXT *  pNameInfo);
using PFN_vkSetDebugUtilsObjectTagEXT = VkResult (*) (VkDevice   device, const  VkDebugUtilsObjectTagInfoEXT *  pTagInfo);
using PFN_vkQueueBeginDebugUtilsLabelEXT = void (*) (VkQueue   queue, const  VkDebugUtilsLabelEXT *  pLabelInfo);
using PFN_vkQueueEndDebugUtilsLabelEXT = void (*) (VkQueue   queue);
using PFN_vkQueueInsertDebugUtilsLabelEXT = void (*) (VkQueue   queue, const  VkDebugUtilsLabelEXT *  pLabelInfo);
using PFN_vkCmdBeginDebugUtilsLabelEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkDebugUtilsLabelEXT *  pLabelInfo);
using PFN_vkCmdEndDebugUtilsLabelEXT = void (*) (VkCommandBuffer   commandBuffer);
using PFN_vkCmdInsertDebugUtilsLabelEXT = void (*) (VkCommandBuffer   commandBuffer, const  VkDebugUtilsLabelEXT *  pLabelInfo);
using PFN_vkCreateDebugUtilsMessengerEXT = VkResult (*) (VkInstance   instance, const  VkDebugUtilsMessengerCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkDebugUtilsMessengerEXT *  pMessenger);
using PFN_vkDestroyDebugUtilsMessengerEXT = void (*) (VkInstance   instance, VkDebugUtilsMessengerEXT   messenger, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkSubmitDebugUtilsMessageEXT = void (*) (VkInstance   instance, VkDebugUtilsMessageSeverityFlagBitsEXT   messageSeverity, VkDebugUtilsMessageTypeFlagsEXT   messageTypes, const  VkDebugUtilsMessengerCallbackDataEXT *  pCallbackData);
using PFN_vkGetMemoryHostPointerPropertiesEXT = VkResult (*) (VkDevice   device, VkExternalMemoryHandleTypeFlagBits   handleType, const  void *  pHostPointer, VkMemoryHostPointerPropertiesEXT *  pMemoryHostPointerProperties);
using PFN_vkCmdWriteBufferMarkerAMD = void (*) (VkCommandBuffer   commandBuffer, VkPipelineStageFlagBits   pipelineStage, VkBuffer   dstBuffer, VkDeviceSize   dstOffset, uint32_t   marker);
using PFN_vkCreateRenderPass2 = VkResult (*) (VkDevice   device, const  VkRenderPassCreateInfo2 *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkRenderPass *  pRenderPass);
using PFN_vkCreateRenderPass2KHR = PFN_vkCreateRenderPass2;
using PFN_vkCmdBeginRenderPass2 = void (*) (VkCommandBuffer   commandBuffer, const  VkRenderPassBeginInfo *       pRenderPassBegin, const  VkSubpassBeginInfo *       pSubpassBeginInfo);
using PFN_vkCmdBeginRenderPass2KHR = PFN_vkCmdBeginRenderPass2;
using PFN_vkCmdNextSubpass2 = void (*) (VkCommandBuffer   commandBuffer, const  VkSubpassBeginInfo *       pSubpassBeginInfo, const  VkSubpassEndInfo *         pSubpassEndInfo);
using PFN_vkCmdNextSubpass2KHR = PFN_vkCmdNextSubpass2;
using PFN_vkCmdEndRenderPass2 = void (*) (VkCommandBuffer   commandBuffer, const  VkSubpassEndInfo *         pSubpassEndInfo);
using PFN_vkCmdEndRenderPass2KHR = PFN_vkCmdEndRenderPass2;
using PFN_vkGetSemaphoreCounterValue = VkResult (*) (VkDevice   device, VkSemaphore   semaphore, uint64_t *  pValue);
using PFN_vkGetSemaphoreCounterValueKHR = PFN_vkGetSemaphoreCounterValue;
using PFN_vkWaitSemaphores = VkResult (*) (VkDevice   device, const  VkSemaphoreWaitInfo *  pWaitInfo, uint64_t   timeout);
using PFN_vkWaitSemaphoresKHR = PFN_vkWaitSemaphores;
using PFN_vkSignalSemaphore = VkResult (*) (VkDevice   device, const  VkSemaphoreSignalInfo *  pSignalInfo);
using PFN_vkSignalSemaphoreKHR = PFN_vkSignalSemaphore;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_vkGetAndroidHardwareBufferPropertiesANDROID = VkResult (*) (VkDevice   device, const struct  AHardwareBuffer *  buffer, VkAndroidHardwareBufferPropertiesANDROID *  pProperties);
using PFN_vkGetMemoryAndroidHardwareBufferANDROID = VkResult (*) (VkDevice   device, const  VkMemoryGetAndroidHardwareBufferInfoANDROID *  pInfo, struct  AHardwareBuffer **  pBuffer);
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_vkCmdDrawIndirectCount = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, VkBuffer   countBuffer, VkDeviceSize   countBufferOffset, uint32_t   maxDrawCount, uint32_t   stride);
using PFN_vkCmdDrawIndirectCountKHR = PFN_vkCmdDrawIndirectCount;
using PFN_vkCmdDrawIndirectCountAMD = PFN_vkCmdDrawIndirectCount;
using PFN_vkCmdDrawIndexedIndirectCount = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, VkBuffer   countBuffer, VkDeviceSize   countBufferOffset, uint32_t   maxDrawCount, uint32_t   stride);
using PFN_vkCmdDrawIndexedIndirectCountKHR = PFN_vkCmdDrawIndexedIndirectCount;
using PFN_vkCmdDrawIndexedIndirectCountAMD = PFN_vkCmdDrawIndexedIndirectCount;
using PFN_vkCmdSetCheckpointNV = void (*) (VkCommandBuffer   commandBuffer, const  void *  pCheckpointMarker);
using PFN_vkGetQueueCheckpointDataNV = void (*) (VkQueue   queue, uint32_t *  pCheckpointDataCount, VkCheckpointDataNV *  pCheckpointData);
using PFN_vkCmdBindTransformFeedbackBuffersEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstBinding, uint32_t   bindingCount, const  VkBuffer *  pBuffers, const  VkDeviceSize *  pOffsets, const  VkDeviceSize *  pSizes);
using PFN_vkCmdBeginTransformFeedbackEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstCounterBuffer, uint32_t   counterBufferCount, const  VkBuffer *  pCounterBuffers, const  VkDeviceSize *  pCounterBufferOffsets);
using PFN_vkCmdEndTransformFeedbackEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstCounterBuffer, uint32_t   counterBufferCount, const  VkBuffer *  pCounterBuffers, const  VkDeviceSize *  pCounterBufferOffsets);
using PFN_vkCmdBeginQueryIndexedEXT = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   query, VkQueryControlFlags   flags, uint32_t   index);
using PFN_vkCmdEndQueryIndexedEXT = void (*) (VkCommandBuffer   commandBuffer, VkQueryPool   queryPool, uint32_t   query, uint32_t   index);
using PFN_vkCmdDrawIndirectByteCountEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   instanceCount, uint32_t   firstInstance, VkBuffer   counterBuffer, VkDeviceSize   counterBufferOffset, uint32_t   counterOffset, uint32_t   vertexStride);
using PFN_vkCmdSetExclusiveScissorNV = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstExclusiveScissor, uint32_t   exclusiveScissorCount, const  VkRect2D *  pExclusiveScissors);
using PFN_vkCmdBindShadingRateImageNV = void (*) (VkCommandBuffer   commandBuffer, VkImageView   imageView, VkImageLayout   imageLayout);
using PFN_vkCmdSetViewportShadingRatePaletteNV = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstViewport, uint32_t   viewportCount, const  VkShadingRatePaletteNV *  pShadingRatePalettes);
using PFN_vkCmdSetCoarseSampleOrderNV = void (*) (VkCommandBuffer   commandBuffer, VkCoarseSampleOrderTypeNV   sampleOrderType, uint32_t   customSampleOrderCount, const  VkCoarseSampleOrderCustomNV *  pCustomSampleOrders);
using PFN_vkCmdDrawMeshTasksNV = void (*) (VkCommandBuffer   commandBuffer, uint32_t   taskCount, uint32_t   firstTask);
using PFN_vkCmdDrawMeshTasksIndirectNV = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, uint32_t   drawCount, uint32_t   stride);
using PFN_vkCmdDrawMeshTasksIndirectCountNV = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   buffer, VkDeviceSize   offset, VkBuffer   countBuffer, VkDeviceSize   countBufferOffset, uint32_t   maxDrawCount, uint32_t   stride);
using PFN_vkCompileDeferredNV = VkResult (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   shader);
using PFN_vkCreateAccelerationStructureNV = VkResult (*) (VkDevice   device, const  VkAccelerationStructureCreateInfoNV *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkAccelerationStructureNV *  pAccelerationStructure);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkDestroyAccelerationStructureKHR = void (*) (VkDevice   device, VkAccelerationStructureKHR   accelerationStructure, const  VkAllocationCallbacks *  pAllocator);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkDestroyAccelerationStructureNV = PFN_vkDestroyAccelerationStructureKHR;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetAccelerationStructureMemoryRequirementsKHR = void (*) (VkDevice   device, const  VkAccelerationStructureMemoryRequirementsInfoKHR *  pInfo, VkMemoryRequirements2 *  pMemoryRequirements);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetAccelerationStructureMemoryRequirementsNV = void (*) (VkDevice   device, const  VkAccelerationStructureMemoryRequirementsInfoNV *  pInfo, VkMemoryRequirements2KHR *  pMemoryRequirements);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkBindAccelerationStructureMemoryKHR = VkResult (*) (VkDevice   device, uint32_t   bindInfoCount, const  VkBindAccelerationStructureMemoryInfoKHR *  pBindInfos);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkBindAccelerationStructureMemoryNV = PFN_vkBindAccelerationStructureMemoryKHR;
using PFN_vkCmdCopyAccelerationStructureNV = void (*) (VkCommandBuffer   commandBuffer, VkAccelerationStructureKHR   dst, VkAccelerationStructureKHR   src, VkCopyAccelerationStructureModeKHR   mode);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCmdCopyAccelerationStructureKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCopyAccelerationStructureKHR = VkResult (*) (VkDevice   device, const  VkCopyAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCmdCopyAccelerationStructureToMemoryKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyAccelerationStructureToMemoryInfoKHR *  pInfo);
using PFN_vkCopyAccelerationStructureToMemoryKHR = VkResult (*) (VkDevice   device, const  VkCopyAccelerationStructureToMemoryInfoKHR *  pInfo);
using PFN_vkCmdCopyMemoryToAccelerationStructureKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyMemoryToAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCopyMemoryToAccelerationStructureKHR = VkResult (*) (VkDevice   device, const  VkCopyMemoryToAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCmdWriteAccelerationStructuresPropertiesKHR = void (*) (VkCommandBuffer   commandBuffer, uint32_t   accelerationStructureCount, const  VkAccelerationStructureKHR *  pAccelerationStructures, VkQueryType   queryType, VkQueryPool   queryPool, uint32_t   firstQuery);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCmdWriteAccelerationStructuresPropertiesNV = PFN_vkCmdWriteAccelerationStructuresPropertiesKHR;
using PFN_vkCmdBuildAccelerationStructureNV = void (*) (VkCommandBuffer   commandBuffer, const  VkAccelerationStructureInfoNV *  pInfo, VkBuffer   instanceData, VkDeviceSize   instanceOffset, VkBool32   update, VkAccelerationStructureKHR   dst, VkAccelerationStructureKHR   src, VkBuffer   scratch, VkDeviceSize   scratchOffset);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkWriteAccelerationStructuresPropertiesKHR = VkResult (*) (VkDevice   device, uint32_t   accelerationStructureCount, const  VkAccelerationStructureKHR *  pAccelerationStructures, VkQueryType    queryType, size_t         dataSize, void *  pData, size_t   stride);
using PFN_vkCmdTraceRaysKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkStridedBufferRegionKHR *  pRaygenShaderBindingTable, const  VkStridedBufferRegionKHR *  pMissShaderBindingTable, const  VkStridedBufferRegionKHR *  pHitShaderBindingTable, const  VkStridedBufferRegionKHR *  pCallableShaderBindingTable, uint32_t   width, uint32_t   height, uint32_t   depth);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCmdTraceRaysNV = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   raygenShaderBindingTableBuffer, VkDeviceSize   raygenShaderBindingOffset, VkBuffer   missShaderBindingTableBuffer, VkDeviceSize   missShaderBindingOffset, VkDeviceSize   missShaderBindingStride, VkBuffer   hitShaderBindingTableBuffer, VkDeviceSize   hitShaderBindingOffset, VkDeviceSize   hitShaderBindingStride, VkBuffer   callableShaderBindingTableBuffer, VkDeviceSize   callableShaderBindingOffset, VkDeviceSize   callableShaderBindingStride, uint32_t   width, uint32_t   height, uint32_t   depth);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetRayTracingShaderGroupHandlesKHR = VkResult (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   firstGroup, uint32_t   groupCount, size_t   dataSize, void *  pData);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetRayTracingShaderGroupHandlesNV = PFN_vkGetRayTracingShaderGroupHandlesKHR;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = VkResult (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   firstGroup, uint32_t   groupCount, size_t   dataSize, void *  pData);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetAccelerationStructureHandleNV = VkResult (*) (VkDevice   device, VkAccelerationStructureKHR   accelerationStructure, size_t   dataSize, void *  pData);
using PFN_vkCreateRayTracingPipelinesNV = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkRayTracingPipelineCreateInfoNV *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCreateRayTracingPipelinesKHR = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkRayTracingPipelineCreateInfoKHR *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkCooperativeMatrixPropertiesNV *  pProperties);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCmdTraceRaysIndirectKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkStridedBufferRegionKHR *  pRaygenShaderBindingTable, const  VkStridedBufferRegionKHR *  pMissShaderBindingTable, const  VkStridedBufferRegionKHR *  pHitShaderBindingTable, const  VkStridedBufferRegionKHR *  pCallableShaderBindingTable, VkBuffer   buffer, VkDeviceSize   offset);
using PFN_vkGetDeviceAccelerationStructureCompatibilityKHR = VkResult (*) (VkDevice   device, const  VkAccelerationStructureVersionKHR *  version);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetImageViewHandleNVX = uint32_t (*) (VkDevice   device, const  VkImageViewHandleInfoNVX *  pInfo);
using PFN_vkGetImageViewAddressNVX = VkResult (*) (VkDevice   device, VkImageView   imageView, VkImageViewAddressPropertiesNVX *  pProperties);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceSurfaceInfo2KHR *  pSurfaceInfo, uint32_t *  pPresentModeCount, VkPresentModeKHR *  pPresentModes);
using PFN_vkGetDeviceGroupSurfacePresentModes2EXT = VkResult (*) (VkDevice   device, const  VkPhysicalDeviceSurfaceInfo2KHR *  pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR *  pModes);
using PFN_vkAcquireFullScreenExclusiveModeEXT = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain);
using PFN_vkReleaseFullScreenExclusiveModeEXT = VkResult (*) (VkDevice   device, VkSwapchainKHR   swapchain);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, uint32_t *  pCounterCount, VkPerformanceCounterKHR *  pCounters, VkPerformanceCounterDescriptionKHR *  pCounterDescriptions);
using PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = void (*) (VkPhysicalDevice   physicalDevice, const  VkQueryPoolPerformanceCreateInfoKHR *  pPerformanceQueryCreateInfo, uint32_t *  pNumPasses);
using PFN_vkAcquireProfilingLockKHR = VkResult (*) (VkDevice   device, const  VkAcquireProfilingLockInfoKHR *  pInfo);
using PFN_vkReleaseProfilingLockKHR = void (*) (VkDevice   device);
using PFN_vkGetImageDrmFormatModifierPropertiesEXT = VkResult (*) (VkDevice   device, VkImage   image, VkImageDrmFormatModifierPropertiesEXT *  pProperties);
using PFN_vkGetBufferOpaqueCaptureAddress = uint64_t (*) (VkDevice   device, const  VkBufferDeviceAddressInfo *  pInfo);
using PFN_vkGetBufferOpaqueCaptureAddressKHR = PFN_vkGetBufferOpaqueCaptureAddress;
using PFN_vkGetBufferDeviceAddress = VkDeviceAddress (*) (VkDevice   device, const  VkBufferDeviceAddressInfo *  pInfo);
using PFN_vkGetBufferDeviceAddressKHR = PFN_vkGetBufferDeviceAddress;
using PFN_vkGetBufferDeviceAddressEXT = PFN_vkGetBufferDeviceAddress;
using PFN_vkCreateHeadlessSurfaceEXT = VkResult (*) (VkInstance   instance, const  VkHeadlessSurfaceCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pCombinationCount, VkFramebufferMixedSamplesCombinationNV *  pCombinations);
using PFN_vkInitializePerformanceApiINTEL = VkResult (*) (VkDevice   device, const  VkInitializePerformanceApiInfoINTEL *  pInitializeInfo);
using PFN_vkUninitializePerformanceApiINTEL = void (*) (VkDevice   device);
using PFN_vkCmdSetPerformanceMarkerINTEL = VkResult (*) (VkCommandBuffer   commandBuffer, const  VkPerformanceMarkerInfoINTEL *  pMarkerInfo);
using PFN_vkCmdSetPerformanceStreamMarkerINTEL = VkResult (*) (VkCommandBuffer   commandBuffer, const  VkPerformanceStreamMarkerInfoINTEL *  pMarkerInfo);
using PFN_vkCmdSetPerformanceOverrideINTEL = VkResult (*) (VkCommandBuffer   commandBuffer, const  VkPerformanceOverrideInfoINTEL *  pOverrideInfo);
using PFN_vkAcquirePerformanceConfigurationINTEL = VkResult (*) (VkDevice   device, const  VkPerformanceConfigurationAcquireInfoINTEL *  pAcquireInfo, VkPerformanceConfigurationINTEL *  pConfiguration);
using PFN_vkReleasePerformanceConfigurationINTEL = VkResult (*) (VkDevice   device, VkPerformanceConfigurationINTEL   configuration);
using PFN_vkQueueSetPerformanceConfigurationINTEL = VkResult (*) (VkQueue   queue, VkPerformanceConfigurationINTEL   configuration);
using PFN_vkGetPerformanceParameterINTEL = VkResult (*) (VkDevice   device, VkPerformanceParameterTypeINTEL   parameter, VkPerformanceValueINTEL *  pValue);
using PFN_vkGetDeviceMemoryOpaqueCaptureAddress = uint64_t (*) (VkDevice   device, const  VkDeviceMemoryOpaqueCaptureAddressInfo *  pInfo);
using PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR = PFN_vkGetDeviceMemoryOpaqueCaptureAddress;
using PFN_vkGetPipelineExecutablePropertiesKHR = VkResult (*) (VkDevice                          device, const  VkPipelineInfoKHR *         pPipelineInfo, uint32_t *  pExecutableCount, VkPipelineExecutablePropertiesKHR *  pProperties);
using PFN_vkGetPipelineExecutableStatisticsKHR = VkResult (*) (VkDevice                          device, const  VkPipelineExecutableInfoKHR *   pExecutableInfo, uint32_t *  pStatisticCount, VkPipelineExecutableStatisticKHR *  pStatistics);
using PFN_vkGetPipelineExecutableInternalRepresentationsKHR = VkResult (*) (VkDevice                          device, const  VkPipelineExecutableInfoKHR *   pExecutableInfo, uint32_t *  pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR *  pInternalRepresentations);
using PFN_vkCmdSetLineStippleEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   lineStippleFactor, uint16_t   lineStipplePattern);
using PFN_vkGetPhysicalDeviceToolPropertiesEXT = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pToolCount, VkPhysicalDeviceToolPropertiesEXT *  pToolProperties);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCreateAccelerationStructureKHR = VkResult (*) (VkDevice                                             device, const  VkAccelerationStructureCreateInfoKHR *         pCreateInfo, const  VkAllocationCallbacks *        pAllocator, VkAccelerationStructureKHR *                         pAccelerationStructure);
using PFN_vkCmdBuildAccelerationStructureKHR = void (*) (VkCommandBuffer                                      commandBuffer, uint32_t   infoCount, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfos, const  VkAccelerationStructureBuildOffsetInfoKHR * const*  ppOffsetInfos);
using PFN_vkCmdBuildAccelerationStructureIndirectKHR = void (*) (VkCommandBuffer                    commandBuffer, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfo, VkBuffer                                             indirectBuffer, VkDeviceSize                                         indirectOffset, uint32_t                                             indirectStride);
using PFN_vkBuildAccelerationStructureKHR = VkResult (*) (VkDevice                                             device, uint32_t   infoCount, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfos, const  VkAccelerationStructureBuildOffsetInfoKHR * const*  ppOffsetInfos);
using PFN_vkGetAccelerationStructureDeviceAddressKHR = VkDeviceAddress (*) (VkDevice   device, const  VkAccelerationStructureDeviceAddressInfoKHR *  pInfo);
using PFN_vkCreateDeferredOperationKHR = VkResult (*) (VkDevice   device, const  VkAllocationCallbacks *  pAllocator, VkDeferredOperationKHR *  pDeferredOperation);
using PFN_vkDestroyDeferredOperationKHR = void (*) (VkDevice   device, VkDeferredOperationKHR   operation, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetDeferredOperationMaxConcurrencyKHR = uint32_t (*) (VkDevice   device, VkDeferredOperationKHR   operation);
using PFN_vkGetDeferredOperationResultKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   operation);
using PFN_vkDeferredOperationJoinKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   operation);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkCmdSetCullModeEXT = void (*) (VkCommandBuffer   commandBuffer, VkCullModeFlags   cullMode);
using PFN_vkCmdSetFrontFaceEXT = void (*) (VkCommandBuffer   commandBuffer, VkFrontFace   frontFace);
using PFN_vkCmdSetPrimitiveTopologyEXT = void (*) (VkCommandBuffer   commandBuffer, VkPrimitiveTopology   primitiveTopology);
using PFN_vkCmdSetViewportWithCountEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   viewportCount, const  VkViewport *  pViewports);
using PFN_vkCmdSetScissorWithCountEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   scissorCount, const  VkRect2D *  pScissors);
using PFN_vkCmdBindVertexBuffers2EXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   firstBinding, uint32_t   bindingCount, const  VkBuffer *  pBuffers, const  VkDeviceSize *  pOffsets, const  VkDeviceSize *  pSizes, const  VkDeviceSize *  pStrides);
using PFN_vkCmdSetDepthTestEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   depthTestEnable);
using PFN_vkCmdSetDepthWriteEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   depthWriteEnable);
using PFN_vkCmdSetDepthCompareOpEXT = void (*) (VkCommandBuffer   commandBuffer, VkCompareOp   depthCompareOp);
using PFN_vkCmdSetDepthBoundsTestEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   depthBoundsTestEnable);
using PFN_vkCmdSetStencilTestEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   stencilTestEnable);
using PFN_vkCmdSetStencilOpEXT = void (*) (VkCommandBuffer   commandBuffer, VkStencilFaceFlags   faceMask, VkStencilOp   failOp, VkStencilOp   passOp, VkStencilOp   depthFailOp, VkCompareOp   compareOp);
using PFN_vkCreatePrivateDataSlotEXT = VkResult (*) (VkDevice   device, const  VkPrivateDataSlotCreateInfoEXT *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkPrivateDataSlotEXT *  pPrivateDataSlot);
using PFN_vkDestroyPrivateDataSlotEXT = void (*) (VkDevice   device, VkPrivateDataSlotEXT   privateDataSlot, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkSetPrivateDataEXT = VkResult (*) (VkDevice   device, VkObjectType   objectType, uint64_t   objectHandle, VkPrivateDataSlotEXT   privateDataSlot, uint64_t   data);
using PFN_vkGetPrivateDataEXT = void (*) (VkDevice   device, VkObjectType   objectType, uint64_t   objectHandle, VkPrivateDataSlotEXT   privateDataSlot, uint64_t *  pData);
using PFN_vkCmdCopyBuffer2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyBufferInfo2KHR *  pCopyBufferInfo);
using PFN_vkCmdCopyImage2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyImageInfo2KHR *  pCopyImageInfo);
using PFN_vkCmdBlitImage2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkBlitImageInfo2KHR *  pBlitImageInfo);
using PFN_vkCmdCopyBufferToImage2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyBufferToImageInfo2KHR *  pCopyBufferToImageInfo);
using PFN_vkCmdCopyImageToBuffer2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyImageToBufferInfo2KHR *  pCopyImageToBufferInfo);
using PFN_vkCmdResolveImage2KHR = void (*) (VkCommandBuffer   commandBuffer, const  VkResolveImageInfo2KHR *  pResolveImageInfo);
} // namespace vk
// clang-format on
