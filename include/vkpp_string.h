#pragma once
// clang-format off
#include "vkpp.h"
namespace vk {
const char * to_string(AttachmentLoadOp val) {
    switch(val) {
        case(AttachmentLoadOp::eLoad): return "eLoad";
        case(AttachmentLoadOp::eClear): return "eClear";
        case(AttachmentLoadOp::eDontCare): return "eDontCare";
        default: return "UNKNOWN";
    }
}
const char * to_string(AttachmentStoreOp val) {
    switch(val) {
        case(AttachmentStoreOp::eStore): return "eStore";
        case(AttachmentStoreOp::eDontCare): return "eDontCare";
        case(AttachmentStoreOp::eNoneQCOM): return "eNoneQCOM";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendFactor val) {
    switch(val) {
        case(BlendFactor::eZero): return "eZero";
        case(BlendFactor::eOne): return "eOne";
        case(BlendFactor::eSrcColor): return "eSrcColor";
        case(BlendFactor::eOneMinusSrcColor): return "eOneMinusSrcColor";
        case(BlendFactor::eDstColor): return "eDstColor";
        case(BlendFactor::eOneMinusDstColor): return "eOneMinusDstColor";
        case(BlendFactor::eSrcAlpha): return "eSrcAlpha";
        case(BlendFactor::eOneMinusSrcAlpha): return "eOneMinusSrcAlpha";
        case(BlendFactor::eDstAlpha): return "eDstAlpha";
        case(BlendFactor::eOneMinusDstAlpha): return "eOneMinusDstAlpha";
        case(BlendFactor::eConstantColor): return "eConstantColor";
        case(BlendFactor::eOneMinusConstantColor): return "eOneMinusConstantColor";
        case(BlendFactor::eConstantAlpha): return "eConstantAlpha";
        case(BlendFactor::eOneMinusConstantAlpha): return "eOneMinusConstantAlpha";
        case(BlendFactor::eSrcAlphaSaturate): return "eSrcAlphaSaturate";
        case(BlendFactor::eSrc1Color): return "eSrc1Color";
        case(BlendFactor::eOneMinusSrc1Color): return "eOneMinusSrc1Color";
        case(BlendFactor::eSrc1Alpha): return "eSrc1Alpha";
        case(BlendFactor::eOneMinusSrc1Alpha): return "eOneMinusSrc1Alpha";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendOp val) {
    switch(val) {
        case(BlendOp::eAdd): return "eAdd";
        case(BlendOp::eSubtract): return "eSubtract";
        case(BlendOp::eReverseSubtract): return "eReverseSubtract";
        case(BlendOp::eMin): return "eMin";
        case(BlendOp::eMax): return "eMax";
        case(BlendOp::eZeroEXT): return "eZeroEXT";
        case(BlendOp::eSrcEXT): return "eSrcEXT";
        case(BlendOp::eDstEXT): return "eDstEXT";
        case(BlendOp::eSrcOverEXT): return "eSrcOverEXT";
        case(BlendOp::eDstOverEXT): return "eDstOverEXT";
        case(BlendOp::eSrcInEXT): return "eSrcInEXT";
        case(BlendOp::eDstInEXT): return "eDstInEXT";
        case(BlendOp::eSrcOutEXT): return "eSrcOutEXT";
        case(BlendOp::eDstOutEXT): return "eDstOutEXT";
        case(BlendOp::eSrcAtopEXT): return "eSrcAtopEXT";
        case(BlendOp::eDstAtopEXT): return "eDstAtopEXT";
        case(BlendOp::eXorEXT): return "eXorEXT";
        case(BlendOp::eMultiplyEXT): return "eMultiplyEXT";
        case(BlendOp::eScreenEXT): return "eScreenEXT";
        case(BlendOp::eOverlayEXT): return "eOverlayEXT";
        case(BlendOp::eDarkenEXT): return "eDarkenEXT";
        case(BlendOp::eLightenEXT): return "eLightenEXT";
        case(BlendOp::eColordodgeEXT): return "eColordodgeEXT";
        case(BlendOp::eColorburnEXT): return "eColorburnEXT";
        case(BlendOp::eHardlightEXT): return "eHardlightEXT";
        case(BlendOp::eSoftlightEXT): return "eSoftlightEXT";
        case(BlendOp::eDifferenceEXT): return "eDifferenceEXT";
        case(BlendOp::eExclusionEXT): return "eExclusionEXT";
        case(BlendOp::eInvertEXT): return "eInvertEXT";
        case(BlendOp::eInvertRgbEXT): return "eInvertRgbEXT";
        case(BlendOp::eLineardodgeEXT): return "eLineardodgeEXT";
        case(BlendOp::eLinearburnEXT): return "eLinearburnEXT";
        case(BlendOp::eVividlightEXT): return "eVividlightEXT";
        case(BlendOp::eLinearlightEXT): return "eLinearlightEXT";
        case(BlendOp::ePinlightEXT): return "ePinlightEXT";
        case(BlendOp::eHardmixEXT): return "eHardmixEXT";
        case(BlendOp::eHslHueEXT): return "eHslHueEXT";
        case(BlendOp::eHslSaturationEXT): return "eHslSaturationEXT";
        case(BlendOp::eHslColorEXT): return "eHslColorEXT";
        case(BlendOp::eHslLuminosityEXT): return "eHslLuminosityEXT";
        case(BlendOp::ePlusEXT): return "ePlusEXT";
        case(BlendOp::ePlusClampedEXT): return "ePlusClampedEXT";
        case(BlendOp::ePlusClampedAlphaEXT): return "ePlusClampedAlphaEXT";
        case(BlendOp::ePlusDarkerEXT): return "ePlusDarkerEXT";
        case(BlendOp::eMinusEXT): return "eMinusEXT";
        case(BlendOp::eMinusClampedEXT): return "eMinusClampedEXT";
        case(BlendOp::eContrastEXT): return "eContrastEXT";
        case(BlendOp::eInvertOvgEXT): return "eInvertOvgEXT";
        case(BlendOp::eRedEXT): return "eRedEXT";
        case(BlendOp::eGreenEXT): return "eGreenEXT";
        case(BlendOp::eBlueEXT): return "eBlueEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(BorderColor val) {
    switch(val) {
        case(BorderColor::eFloatTransparentBlack): return "eFloatTransparentBlack";
        case(BorderColor::eIntTransparentBlack): return "eIntTransparentBlack";
        case(BorderColor::eFloatOpaqueBlack): return "eFloatOpaqueBlack";
        case(BorderColor::eIntOpaqueBlack): return "eIntOpaqueBlack";
        case(BorderColor::eFloatOpaqueWhite): return "eFloatOpaqueWhite";
        case(BorderColor::eIntOpaqueWhite): return "eIntOpaqueWhite";
        case(BorderColor::eFloatCustomEXT): return "eFloatCustomEXT";
        case(BorderColor::eIntCustomEXT): return "eIntCustomEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineCacheHeaderVersion val) {
    switch(val) {
        case(PipelineCacheHeaderVersion::eOne): return "eOne";
        default: return "UNKNOWN";
    }
}
const char * to_string(ComponentSwizzle val) {
    switch(val) {
        case(ComponentSwizzle::eIdentity): return "eIdentity";
        case(ComponentSwizzle::eZero): return "eZero";
        case(ComponentSwizzle::eOne): return "eOne";
        case(ComponentSwizzle::eR): return "eR";
        case(ComponentSwizzle::eG): return "eG";
        case(ComponentSwizzle::eB): return "eB";
        case(ComponentSwizzle::eA): return "eA";
        default: return "UNKNOWN";
    }
}
const char * to_string(CommandBufferLevel val) {
    switch(val) {
        case(CommandBufferLevel::ePrimary): return "ePrimary";
        case(CommandBufferLevel::eSecondary): return "eSecondary";
        default: return "UNKNOWN";
    }
}
const char * to_string(CompareOp val) {
    switch(val) {
        case(CompareOp::eNever): return "eNever";
        case(CompareOp::eLess): return "eLess";
        case(CompareOp::eEqual): return "eEqual";
        case(CompareOp::eLessOrEqual): return "eLessOrEqual";
        case(CompareOp::eGreater): return "eGreater";
        case(CompareOp::eNotEqual): return "eNotEqual";
        case(CompareOp::eGreaterOrEqual): return "eGreaterOrEqual";
        case(CompareOp::eAlways): return "eAlways";
        default: return "UNKNOWN";
    }
}
const char * to_string(DescriptorType val) {
    switch(val) {
        case(DescriptorType::eSampler): return "eSampler";
        case(DescriptorType::eCombinedImageSampler): return "eCombinedImageSampler";
        case(DescriptorType::eSampledImage): return "eSampledImage";
        case(DescriptorType::eStorageImage): return "eStorageImage";
        case(DescriptorType::eUniformTexelBuffer): return "eUniformTexelBuffer";
        case(DescriptorType::eStorageTexelBuffer): return "eStorageTexelBuffer";
        case(DescriptorType::eUniformBuffer): return "eUniformBuffer";
        case(DescriptorType::eStorageBuffer): return "eStorageBuffer";
        case(DescriptorType::eUniformBufferDynamic): return "eUniformBufferDynamic";
        case(DescriptorType::eStorageBufferDynamic): return "eStorageBufferDynamic";
        case(DescriptorType::eInputAttachment): return "eInputAttachment";
        case(DescriptorType::eInlineUniformBlockEXT): return "eInlineUniformBlockEXT";
        case(DescriptorType::eAccelerationStructureKHR): return "eAccelerationStructureKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(DynamicState val) {
    switch(val) {
        case(DynamicState::eViewport): return "eViewport";
        case(DynamicState::eScissor): return "eScissor";
        case(DynamicState::eLineWidth): return "eLineWidth";
        case(DynamicState::eDepthBias): return "eDepthBias";
        case(DynamicState::eBlendConstants): return "eBlendConstants";
        case(DynamicState::eDepthBounds): return "eDepthBounds";
        case(DynamicState::eStencilCompareMask): return "eStencilCompareMask";
        case(DynamicState::eStencilWriteMask): return "eStencilWriteMask";
        case(DynamicState::eStencilReference): return "eStencilReference";
        case(DynamicState::eViewportWScalingNV): return "eViewportWScalingNV";
        case(DynamicState::eDiscardRectangleEXT): return "eDiscardRectangleEXT";
        case(DynamicState::eSampleLocationsEXT): return "eSampleLocationsEXT";
        case(DynamicState::eViewportShadingRatePaletteNV): return "eViewportShadingRatePaletteNV";
        case(DynamicState::eViewportCoarseSampleOrderNV): return "eViewportCoarseSampleOrderNV";
        case(DynamicState::eExclusiveScissorNV): return "eExclusiveScissorNV";
        case(DynamicState::eLineStippleEXT): return "eLineStippleEXT";
        case(DynamicState::eCullModeEXT): return "eCullModeEXT";
        case(DynamicState::eFrontFaceEXT): return "eFrontFaceEXT";
        case(DynamicState::ePrimitiveTopologyEXT): return "ePrimitiveTopologyEXT";
        case(DynamicState::eViewportWithCountEXT): return "eViewportWithCountEXT";
        case(DynamicState::eScissorWithCountEXT): return "eScissorWithCountEXT";
        case(DynamicState::eVertexInputBindingStrideEXT): return "eVertexInputBindingStrideEXT";
        case(DynamicState::eDepthTestEnableEXT): return "eDepthTestEnableEXT";
        case(DynamicState::eDepthWriteEnableEXT): return "eDepthWriteEnableEXT";
        case(DynamicState::eDepthCompareOpEXT): return "eDepthCompareOpEXT";
        case(DynamicState::eDepthBoundsTestEnableEXT): return "eDepthBoundsTestEnableEXT";
        case(DynamicState::eStencilTestEnableEXT): return "eStencilTestEnableEXT";
        case(DynamicState::eStencilOpEXT): return "eStencilOpEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PolygonMode val) {
    switch(val) {
        case(PolygonMode::eFill): return "eFill";
        case(PolygonMode::eLine): return "eLine";
        case(PolygonMode::ePoint): return "ePoint";
        case(PolygonMode::eFillRectangleNV): return "eFillRectangleNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(Format val) {
    switch(val) {
        case(Format::eUndefined): return "eUndefined";
        case(Format::eR4G4UnormPack8): return "eR4G4UnormPack8";
        case(Format::eR4G4B4A4UnormPack16): return "eR4G4B4A4UnormPack16";
        case(Format::eB4G4R4A4UnormPack16): return "eB4G4R4A4UnormPack16";
        case(Format::eR5G6B5UnormPack16): return "eR5G6B5UnormPack16";
        case(Format::eB5G6R5UnormPack16): return "eB5G6R5UnormPack16";
        case(Format::eR5G5B5A1UnormPack16): return "eR5G5B5A1UnormPack16";
        case(Format::eB5G5R5A1UnormPack16): return "eB5G5R5A1UnormPack16";
        case(Format::eA1R5G5B5UnormPack16): return "eA1R5G5B5UnormPack16";
        case(Format::eR8Unorm): return "eR8Unorm";
        case(Format::eR8Snorm): return "eR8Snorm";
        case(Format::eR8Uscaled): return "eR8Uscaled";
        case(Format::eR8Sscaled): return "eR8Sscaled";
        case(Format::eR8Uint): return "eR8Uint";
        case(Format::eR8Sint): return "eR8Sint";
        case(Format::eR8Srgb): return "eR8Srgb";
        case(Format::eR8G8Unorm): return "eR8G8Unorm";
        case(Format::eR8G8Snorm): return "eR8G8Snorm";
        case(Format::eR8G8Uscaled): return "eR8G8Uscaled";
        case(Format::eR8G8Sscaled): return "eR8G8Sscaled";
        case(Format::eR8G8Uint): return "eR8G8Uint";
        case(Format::eR8G8Sint): return "eR8G8Sint";
        case(Format::eR8G8Srgb): return "eR8G8Srgb";
        case(Format::eR8G8B8Unorm): return "eR8G8B8Unorm";
        case(Format::eR8G8B8Snorm): return "eR8G8B8Snorm";
        case(Format::eR8G8B8Uscaled): return "eR8G8B8Uscaled";
        case(Format::eR8G8B8Sscaled): return "eR8G8B8Sscaled";
        case(Format::eR8G8B8Uint): return "eR8G8B8Uint";
        case(Format::eR8G8B8Sint): return "eR8G8B8Sint";
        case(Format::eR8G8B8Srgb): return "eR8G8B8Srgb";
        case(Format::eB8G8R8Unorm): return "eB8G8R8Unorm";
        case(Format::eB8G8R8Snorm): return "eB8G8R8Snorm";
        case(Format::eB8G8R8Uscaled): return "eB8G8R8Uscaled";
        case(Format::eB8G8R8Sscaled): return "eB8G8R8Sscaled";
        case(Format::eB8G8R8Uint): return "eB8G8R8Uint";
        case(Format::eB8G8R8Sint): return "eB8G8R8Sint";
        case(Format::eB8G8R8Srgb): return "eB8G8R8Srgb";
        case(Format::eR8G8B8A8Unorm): return "eR8G8B8A8Unorm";
        case(Format::eR8G8B8A8Snorm): return "eR8G8B8A8Snorm";
        case(Format::eR8G8B8A8Uscaled): return "eR8G8B8A8Uscaled";
        case(Format::eR8G8B8A8Sscaled): return "eR8G8B8A8Sscaled";
        case(Format::eR8G8B8A8Uint): return "eR8G8B8A8Uint";
        case(Format::eR8G8B8A8Sint): return "eR8G8B8A8Sint";
        case(Format::eR8G8B8A8Srgb): return "eR8G8B8A8Srgb";
        case(Format::eB8G8R8A8Unorm): return "eB8G8R8A8Unorm";
        case(Format::eB8G8R8A8Snorm): return "eB8G8R8A8Snorm";
        case(Format::eB8G8R8A8Uscaled): return "eB8G8R8A8Uscaled";
        case(Format::eB8G8R8A8Sscaled): return "eB8G8R8A8Sscaled";
        case(Format::eB8G8R8A8Uint): return "eB8G8R8A8Uint";
        case(Format::eB8G8R8A8Sint): return "eB8G8R8A8Sint";
        case(Format::eB8G8R8A8Srgb): return "eB8G8R8A8Srgb";
        case(Format::eA8B8G8R8UnormPack32): return "eA8B8G8R8UnormPack32";
        case(Format::eA8B8G8R8SnormPack32): return "eA8B8G8R8SnormPack32";
        case(Format::eA8B8G8R8UscaledPack32): return "eA8B8G8R8UscaledPack32";
        case(Format::eA8B8G8R8SscaledPack32): return "eA8B8G8R8SscaledPack32";
        case(Format::eA8B8G8R8UintPack32): return "eA8B8G8R8UintPack32";
        case(Format::eA8B8G8R8SintPack32): return "eA8B8G8R8SintPack32";
        case(Format::eA8B8G8R8SrgbPack32): return "eA8B8G8R8SrgbPack32";
        case(Format::eA2R10G10B10UnormPack32): return "eA2R10G10B10UnormPack32";
        case(Format::eA2R10G10B10SnormPack32): return "eA2R10G10B10SnormPack32";
        case(Format::eA2R10G10B10UscaledPack32): return "eA2R10G10B10UscaledPack32";
        case(Format::eA2R10G10B10SscaledPack32): return "eA2R10G10B10SscaledPack32";
        case(Format::eA2R10G10B10UintPack32): return "eA2R10G10B10UintPack32";
        case(Format::eA2R10G10B10SintPack32): return "eA2R10G10B10SintPack32";
        case(Format::eA2B10G10R10UnormPack32): return "eA2B10G10R10UnormPack32";
        case(Format::eA2B10G10R10SnormPack32): return "eA2B10G10R10SnormPack32";
        case(Format::eA2B10G10R10UscaledPack32): return "eA2B10G10R10UscaledPack32";
        case(Format::eA2B10G10R10SscaledPack32): return "eA2B10G10R10SscaledPack32";
        case(Format::eA2B10G10R10UintPack32): return "eA2B10G10R10UintPack32";
        case(Format::eA2B10G10R10SintPack32): return "eA2B10G10R10SintPack32";
        case(Format::eR16Unorm): return "eR16Unorm";
        case(Format::eR16Snorm): return "eR16Snorm";
        case(Format::eR16Uscaled): return "eR16Uscaled";
        case(Format::eR16Sscaled): return "eR16Sscaled";
        case(Format::eR16Uint): return "eR16Uint";
        case(Format::eR16Sint): return "eR16Sint";
        case(Format::eR16Sfloat): return "eR16Sfloat";
        case(Format::eR16G16Unorm): return "eR16G16Unorm";
        case(Format::eR16G16Snorm): return "eR16G16Snorm";
        case(Format::eR16G16Uscaled): return "eR16G16Uscaled";
        case(Format::eR16G16Sscaled): return "eR16G16Sscaled";
        case(Format::eR16G16Uint): return "eR16G16Uint";
        case(Format::eR16G16Sint): return "eR16G16Sint";
        case(Format::eR16G16Sfloat): return "eR16G16Sfloat";
        case(Format::eR16G16B16Unorm): return "eR16G16B16Unorm";
        case(Format::eR16G16B16Snorm): return "eR16G16B16Snorm";
        case(Format::eR16G16B16Uscaled): return "eR16G16B16Uscaled";
        case(Format::eR16G16B16Sscaled): return "eR16G16B16Sscaled";
        case(Format::eR16G16B16Uint): return "eR16G16B16Uint";
        case(Format::eR16G16B16Sint): return "eR16G16B16Sint";
        case(Format::eR16G16B16Sfloat): return "eR16G16B16Sfloat";
        case(Format::eR16G16B16A16Unorm): return "eR16G16B16A16Unorm";
        case(Format::eR16G16B16A16Snorm): return "eR16G16B16A16Snorm";
        case(Format::eR16G16B16A16Uscaled): return "eR16G16B16A16Uscaled";
        case(Format::eR16G16B16A16Sscaled): return "eR16G16B16A16Sscaled";
        case(Format::eR16G16B16A16Uint): return "eR16G16B16A16Uint";
        case(Format::eR16G16B16A16Sint): return "eR16G16B16A16Sint";
        case(Format::eR16G16B16A16Sfloat): return "eR16G16B16A16Sfloat";
        case(Format::eR32Uint): return "eR32Uint";
        case(Format::eR32Sint): return "eR32Sint";
        case(Format::eR32Sfloat): return "eR32Sfloat";
        case(Format::eR32G32Uint): return "eR32G32Uint";
        case(Format::eR32G32Sint): return "eR32G32Sint";
        case(Format::eR32G32Sfloat): return "eR32G32Sfloat";
        case(Format::eR32G32B32Uint): return "eR32G32B32Uint";
        case(Format::eR32G32B32Sint): return "eR32G32B32Sint";
        case(Format::eR32G32B32Sfloat): return "eR32G32B32Sfloat";
        case(Format::eR32G32B32A32Uint): return "eR32G32B32A32Uint";
        case(Format::eR32G32B32A32Sint): return "eR32G32B32A32Sint";
        case(Format::eR32G32B32A32Sfloat): return "eR32G32B32A32Sfloat";
        case(Format::eR64Uint): return "eR64Uint";
        case(Format::eR64Sint): return "eR64Sint";
        case(Format::eR64Sfloat): return "eR64Sfloat";
        case(Format::eR64G64Uint): return "eR64G64Uint";
        case(Format::eR64G64Sint): return "eR64G64Sint";
        case(Format::eR64G64Sfloat): return "eR64G64Sfloat";
        case(Format::eR64G64B64Uint): return "eR64G64B64Uint";
        case(Format::eR64G64B64Sint): return "eR64G64B64Sint";
        case(Format::eR64G64B64Sfloat): return "eR64G64B64Sfloat";
        case(Format::eR64G64B64A64Uint): return "eR64G64B64A64Uint";
        case(Format::eR64G64B64A64Sint): return "eR64G64B64A64Sint";
        case(Format::eR64G64B64A64Sfloat): return "eR64G64B64A64Sfloat";
        case(Format::eB10G11R11UfloatPack32): return "eB10G11R11UfloatPack32";
        case(Format::eE5B9G9R9UfloatPack32): return "eE5B9G9R9UfloatPack32";
        case(Format::eD16Unorm): return "eD16Unorm";
        case(Format::eX8D24UnormPack32): return "eX8D24UnormPack32";
        case(Format::eD32Sfloat): return "eD32Sfloat";
        case(Format::eS8Uint): return "eS8Uint";
        case(Format::eD16UnormS8Uint): return "eD16UnormS8Uint";
        case(Format::eD24UnormS8Uint): return "eD24UnormS8Uint";
        case(Format::eD32SfloatS8Uint): return "eD32SfloatS8Uint";
        case(Format::eBc1RgbUnormBlock): return "eBc1RgbUnormBlock";
        case(Format::eBc1RgbSrgbBlock): return "eBc1RgbSrgbBlock";
        case(Format::eBc1RgbaUnormBlock): return "eBc1RgbaUnormBlock";
        case(Format::eBc1RgbaSrgbBlock): return "eBc1RgbaSrgbBlock";
        case(Format::eBc2UnormBlock): return "eBc2UnormBlock";
        case(Format::eBc2SrgbBlock): return "eBc2SrgbBlock";
        case(Format::eBc3UnormBlock): return "eBc3UnormBlock";
        case(Format::eBc3SrgbBlock): return "eBc3SrgbBlock";
        case(Format::eBc4UnormBlock): return "eBc4UnormBlock";
        case(Format::eBc4SnormBlock): return "eBc4SnormBlock";
        case(Format::eBc5UnormBlock): return "eBc5UnormBlock";
        case(Format::eBc5SnormBlock): return "eBc5SnormBlock";
        case(Format::eBc6HUfloatBlock): return "eBc6HUfloatBlock";
        case(Format::eBc6HSfloatBlock): return "eBc6HSfloatBlock";
        case(Format::eBc7UnormBlock): return "eBc7UnormBlock";
        case(Format::eBc7SrgbBlock): return "eBc7SrgbBlock";
        case(Format::eEtc2R8G8B8UnormBlock): return "eEtc2R8G8B8UnormBlock";
        case(Format::eEtc2R8G8B8SrgbBlock): return "eEtc2R8G8B8SrgbBlock";
        case(Format::eEtc2R8G8B8A1UnormBlock): return "eEtc2R8G8B8A1UnormBlock";
        case(Format::eEtc2R8G8B8A1SrgbBlock): return "eEtc2R8G8B8A1SrgbBlock";
        case(Format::eEtc2R8G8B8A8UnormBlock): return "eEtc2R8G8B8A8UnormBlock";
        case(Format::eEtc2R8G8B8A8SrgbBlock): return "eEtc2R8G8B8A8SrgbBlock";
        case(Format::eEacR11UnormBlock): return "eEacR11UnormBlock";
        case(Format::eEacR11SnormBlock): return "eEacR11SnormBlock";
        case(Format::eEacR11G11UnormBlock): return "eEacR11G11UnormBlock";
        case(Format::eEacR11G11SnormBlock): return "eEacR11G11SnormBlock";
        case(Format::eAstc4X4UnormBlock): return "eAstc4X4UnormBlock";
        case(Format::eAstc4X4SrgbBlock): return "eAstc4X4SrgbBlock";
        case(Format::eAstc5X4UnormBlock): return "eAstc5X4UnormBlock";
        case(Format::eAstc5X4SrgbBlock): return "eAstc5X4SrgbBlock";
        case(Format::eAstc5X5UnormBlock): return "eAstc5X5UnormBlock";
        case(Format::eAstc5X5SrgbBlock): return "eAstc5X5SrgbBlock";
        case(Format::eAstc6X5UnormBlock): return "eAstc6X5UnormBlock";
        case(Format::eAstc6X5SrgbBlock): return "eAstc6X5SrgbBlock";
        case(Format::eAstc6X6UnormBlock): return "eAstc6X6UnormBlock";
        case(Format::eAstc6X6SrgbBlock): return "eAstc6X6SrgbBlock";
        case(Format::eAstc8X5UnormBlock): return "eAstc8X5UnormBlock";
        case(Format::eAstc8X5SrgbBlock): return "eAstc8X5SrgbBlock";
        case(Format::eAstc8X6UnormBlock): return "eAstc8X6UnormBlock";
        case(Format::eAstc8X6SrgbBlock): return "eAstc8X6SrgbBlock";
        case(Format::eAstc8X8UnormBlock): return "eAstc8X8UnormBlock";
        case(Format::eAstc8X8SrgbBlock): return "eAstc8X8SrgbBlock";
        case(Format::eAstc10X5UnormBlock): return "eAstc10X5UnormBlock";
        case(Format::eAstc10X5SrgbBlock): return "eAstc10X5SrgbBlock";
        case(Format::eAstc10X6UnormBlock): return "eAstc10X6UnormBlock";
        case(Format::eAstc10X6SrgbBlock): return "eAstc10X6SrgbBlock";
        case(Format::eAstc10X8UnormBlock): return "eAstc10X8UnormBlock";
        case(Format::eAstc10X8SrgbBlock): return "eAstc10X8SrgbBlock";
        case(Format::eAstc10X10UnormBlock): return "eAstc10X10UnormBlock";
        case(Format::eAstc10X10SrgbBlock): return "eAstc10X10SrgbBlock";
        case(Format::eAstc12X10UnormBlock): return "eAstc12X10UnormBlock";
        case(Format::eAstc12X10SrgbBlock): return "eAstc12X10SrgbBlock";
        case(Format::eAstc12X12UnormBlock): return "eAstc12X12UnormBlock";
        case(Format::eAstc12X12SrgbBlock): return "eAstc12X12SrgbBlock";
        case(Format::ePvrtc12BppUnormBlockIMG): return "ePvrtc12BppUnormBlockIMG";
        case(Format::ePvrtc14BppUnormBlockIMG): return "ePvrtc14BppUnormBlockIMG";
        case(Format::ePvrtc22BppUnormBlockIMG): return "ePvrtc22BppUnormBlockIMG";
        case(Format::ePvrtc24BppUnormBlockIMG): return "ePvrtc24BppUnormBlockIMG";
        case(Format::ePvrtc12BppSrgbBlockIMG): return "ePvrtc12BppSrgbBlockIMG";
        case(Format::ePvrtc14BppSrgbBlockIMG): return "ePvrtc14BppSrgbBlockIMG";
        case(Format::ePvrtc22BppSrgbBlockIMG): return "ePvrtc22BppSrgbBlockIMG";
        case(Format::ePvrtc24BppSrgbBlockIMG): return "ePvrtc24BppSrgbBlockIMG";
        case(Format::eAstc4X4SfloatBlockEXT): return "eAstc4X4SfloatBlockEXT";
        case(Format::eAstc5X4SfloatBlockEXT): return "eAstc5X4SfloatBlockEXT";
        case(Format::eAstc5X5SfloatBlockEXT): return "eAstc5X5SfloatBlockEXT";
        case(Format::eAstc6X5SfloatBlockEXT): return "eAstc6X5SfloatBlockEXT";
        case(Format::eAstc6X6SfloatBlockEXT): return "eAstc6X6SfloatBlockEXT";
        case(Format::eAstc8X5SfloatBlockEXT): return "eAstc8X5SfloatBlockEXT";
        case(Format::eAstc8X6SfloatBlockEXT): return "eAstc8X6SfloatBlockEXT";
        case(Format::eAstc8X8SfloatBlockEXT): return "eAstc8X8SfloatBlockEXT";
        case(Format::eAstc10X5SfloatBlockEXT): return "eAstc10X5SfloatBlockEXT";
        case(Format::eAstc10X6SfloatBlockEXT): return "eAstc10X6SfloatBlockEXT";
        case(Format::eAstc10X8SfloatBlockEXT): return "eAstc10X8SfloatBlockEXT";
        case(Format::eAstc10X10SfloatBlockEXT): return "eAstc10X10SfloatBlockEXT";
        case(Format::eAstc12X10SfloatBlockEXT): return "eAstc12X10SfloatBlockEXT";
        case(Format::eAstc12X12SfloatBlockEXT): return "eAstc12X12SfloatBlockEXT";
        case(Format::eAstc3X3X3UnormBlockEXT): return "eAstc3X3X3UnormBlockEXT";
        case(Format::eAstc3X3X3SrgbBlockEXT): return "eAstc3X3X3SrgbBlockEXT";
        case(Format::eAstc3X3X3SfloatBlockEXT): return "eAstc3X3X3SfloatBlockEXT";
        case(Format::eAstc4X3X3UnormBlockEXT): return "eAstc4X3X3UnormBlockEXT";
        case(Format::eAstc4X3X3SrgbBlockEXT): return "eAstc4X3X3SrgbBlockEXT";
        case(Format::eAstc4X3X3SfloatBlockEXT): return "eAstc4X3X3SfloatBlockEXT";
        case(Format::eAstc4X4X3UnormBlockEXT): return "eAstc4X4X3UnormBlockEXT";
        case(Format::eAstc4X4X3SrgbBlockEXT): return "eAstc4X4X3SrgbBlockEXT";
        case(Format::eAstc4X4X3SfloatBlockEXT): return "eAstc4X4X3SfloatBlockEXT";
        case(Format::eAstc4X4X4UnormBlockEXT): return "eAstc4X4X4UnormBlockEXT";
        case(Format::eAstc4X4X4SrgbBlockEXT): return "eAstc4X4X4SrgbBlockEXT";
        case(Format::eAstc4X4X4SfloatBlockEXT): return "eAstc4X4X4SfloatBlockEXT";
        case(Format::eAstc5X4X4UnormBlockEXT): return "eAstc5X4X4UnormBlockEXT";
        case(Format::eAstc5X4X4SrgbBlockEXT): return "eAstc5X4X4SrgbBlockEXT";
        case(Format::eAstc5X4X4SfloatBlockEXT): return "eAstc5X4X4SfloatBlockEXT";
        case(Format::eAstc5X5X4UnormBlockEXT): return "eAstc5X5X4UnormBlockEXT";
        case(Format::eAstc5X5X4SrgbBlockEXT): return "eAstc5X5X4SrgbBlockEXT";
        case(Format::eAstc5X5X4SfloatBlockEXT): return "eAstc5X5X4SfloatBlockEXT";
        case(Format::eAstc5X5X5UnormBlockEXT): return "eAstc5X5X5UnormBlockEXT";
        case(Format::eAstc5X5X5SrgbBlockEXT): return "eAstc5X5X5SrgbBlockEXT";
        case(Format::eAstc5X5X5SfloatBlockEXT): return "eAstc5X5X5SfloatBlockEXT";
        case(Format::eAstc6X5X5UnormBlockEXT): return "eAstc6X5X5UnormBlockEXT";
        case(Format::eAstc6X5X5SrgbBlockEXT): return "eAstc6X5X5SrgbBlockEXT";
        case(Format::eAstc6X5X5SfloatBlockEXT): return "eAstc6X5X5SfloatBlockEXT";
        case(Format::eAstc6X6X5UnormBlockEXT): return "eAstc6X6X5UnormBlockEXT";
        case(Format::eAstc6X6X5SrgbBlockEXT): return "eAstc6X6X5SrgbBlockEXT";
        case(Format::eAstc6X6X5SfloatBlockEXT): return "eAstc6X6X5SfloatBlockEXT";
        case(Format::eAstc6X6X6UnormBlockEXT): return "eAstc6X6X6UnormBlockEXT";
        case(Format::eAstc6X6X6SrgbBlockEXT): return "eAstc6X6X6SrgbBlockEXT";
        case(Format::eAstc6X6X6SfloatBlockEXT): return "eAstc6X6X6SfloatBlockEXT";
        case(Format::eA4R4G4B4UnormPack16EXT): return "eA4R4G4B4UnormPack16EXT";
        case(Format::eA4B4G4R4UnormPack16EXT): return "eA4B4G4R4UnormPack16EXT";
        case(Format::eG8B8G8R8422Unorm): return "eG8B8G8R8422Unorm";
        case(Format::eB8G8R8G8422Unorm): return "eB8G8R8G8422Unorm";
        case(Format::eG8B8R83Plane420Unorm): return "eG8B8R83Plane420Unorm";
        case(Format::eG8B8R82Plane420Unorm): return "eG8B8R82Plane420Unorm";
        case(Format::eG8B8R83Plane422Unorm): return "eG8B8R83Plane422Unorm";
        case(Format::eG8B8R82Plane422Unorm): return "eG8B8R82Plane422Unorm";
        case(Format::eG8B8R83Plane444Unorm): return "eG8B8R83Plane444Unorm";
        case(Format::eR10X6UnormPack16): return "eR10X6UnormPack16";
        case(Format::eR10X6G10X6Unorm2Pack16): return "eR10X6G10X6Unorm2Pack16";
        case(Format::eR10X6G10X6B10X6A10X6Unorm4Pack16): return "eR10X6G10X6B10X6A10X6Unorm4Pack16";
        case(Format::eG10X6B10X6G10X6R10X6422Unorm4Pack16): return "eG10X6B10X6G10X6R10X6422Unorm4Pack16";
        case(Format::eB10X6G10X6R10X6G10X6422Unorm4Pack16): return "eB10X6G10X6R10X6G10X6422Unorm4Pack16";
        case(Format::eG10X6B10X6R10X63Plane420Unorm3Pack16): return "eG10X6B10X6R10X63Plane420Unorm3Pack16";
        case(Format::eG10X6B10X6R10X62Plane420Unorm3Pack16): return "eG10X6B10X6R10X62Plane420Unorm3Pack16";
        case(Format::eG10X6B10X6R10X63Plane422Unorm3Pack16): return "eG10X6B10X6R10X63Plane422Unorm3Pack16";
        case(Format::eG10X6B10X6R10X62Plane422Unorm3Pack16): return "eG10X6B10X6R10X62Plane422Unorm3Pack16";
        case(Format::eG10X6B10X6R10X63Plane444Unorm3Pack16): return "eG10X6B10X6R10X63Plane444Unorm3Pack16";
        case(Format::eR12X4UnormPack16): return "eR12X4UnormPack16";
        case(Format::eR12X4G12X4Unorm2Pack16): return "eR12X4G12X4Unorm2Pack16";
        case(Format::eR12X4G12X4B12X4A12X4Unorm4Pack16): return "eR12X4G12X4B12X4A12X4Unorm4Pack16";
        case(Format::eG12X4B12X4G12X4R12X4422Unorm4Pack16): return "eG12X4B12X4G12X4R12X4422Unorm4Pack16";
        case(Format::eB12X4G12X4R12X4G12X4422Unorm4Pack16): return "eB12X4G12X4R12X4G12X4422Unorm4Pack16";
        case(Format::eG12X4B12X4R12X43Plane420Unorm3Pack16): return "eG12X4B12X4R12X43Plane420Unorm3Pack16";
        case(Format::eG12X4B12X4R12X42Plane420Unorm3Pack16): return "eG12X4B12X4R12X42Plane420Unorm3Pack16";
        case(Format::eG12X4B12X4R12X43Plane422Unorm3Pack16): return "eG12X4B12X4R12X43Plane422Unorm3Pack16";
        case(Format::eG12X4B12X4R12X42Plane422Unorm3Pack16): return "eG12X4B12X4R12X42Plane422Unorm3Pack16";
        case(Format::eG12X4B12X4R12X43Plane444Unorm3Pack16): return "eG12X4B12X4R12X43Plane444Unorm3Pack16";
        case(Format::eG16B16G16R16422Unorm): return "eG16B16G16R16422Unorm";
        case(Format::eB16G16R16G16422Unorm): return "eB16G16R16G16422Unorm";
        case(Format::eG16B16R163Plane420Unorm): return "eG16B16R163Plane420Unorm";
        case(Format::eG16B16R162Plane420Unorm): return "eG16B16R162Plane420Unorm";
        case(Format::eG16B16R163Plane422Unorm): return "eG16B16R163Plane422Unorm";
        case(Format::eG16B16R162Plane422Unorm): return "eG16B16R162Plane422Unorm";
        case(Format::eG16B16R163Plane444Unorm): return "eG16B16R163Plane444Unorm";
        default: return "UNKNOWN";
    }
}
const char * to_string(FrontFace val) {
    switch(val) {
        case(FrontFace::eCounterClockwise): return "eCounterClockwise";
        case(FrontFace::eClockwise): return "eClockwise";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageLayout val) {
    switch(val) {
        case(ImageLayout::eUndefined): return "eUndefined";
        case(ImageLayout::eGeneral): return "eGeneral";
        case(ImageLayout::eColorAttachmentOptimal): return "eColorAttachmentOptimal";
        case(ImageLayout::eDepthStencilAttachmentOptimal): return "eDepthStencilAttachmentOptimal";
        case(ImageLayout::eDepthStencilReadOnlyOptimal): return "eDepthStencilReadOnlyOptimal";
        case(ImageLayout::eShaderReadOnlyOptimal): return "eShaderReadOnlyOptimal";
        case(ImageLayout::eTransferSrcOptimal): return "eTransferSrcOptimal";
        case(ImageLayout::eTransferDstOptimal): return "eTransferDstOptimal";
        case(ImageLayout::ePreinitialized): return "ePreinitialized";
        case(ImageLayout::ePresentSrcKHR): return "ePresentSrcKHR";
        case(ImageLayout::eSharedPresentKHR): return "eSharedPresentKHR";
        case(ImageLayout::eShadingRateOptimalNV): return "eShadingRateOptimalNV";
        case(ImageLayout::eFragmentDensityMapOptimalEXT): return "eFragmentDensityMapOptimalEXT";
        case(ImageLayout::eDepthReadOnlyStencilAttachmentOptimal): return "eDepthReadOnlyStencilAttachmentOptimal";
        case(ImageLayout::eDepthAttachmentStencilReadOnlyOptimal): return "eDepthAttachmentStencilReadOnlyOptimal";
        case(ImageLayout::eDepthAttachmentOptimal): return "eDepthAttachmentOptimal";
        case(ImageLayout::eDepthReadOnlyOptimal): return "eDepthReadOnlyOptimal";
        case(ImageLayout::eStencilAttachmentOptimal): return "eStencilAttachmentOptimal";
        case(ImageLayout::eStencilReadOnlyOptimal): return "eStencilReadOnlyOptimal";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageTiling val) {
    switch(val) {
        case(ImageTiling::eOptimal): return "eOptimal";
        case(ImageTiling::eLinear): return "eLinear";
        case(ImageTiling::eDrmFormatModifierEXT): return "eDrmFormatModifierEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageType val) {
    switch(val) {
        case(ImageType::e1D): return "e1D";
        case(ImageType::e2D): return "e2D";
        case(ImageType::e3D): return "e3D";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageViewType val) {
    switch(val) {
        case(ImageViewType::e1D): return "e1D";
        case(ImageViewType::e2D): return "e2D";
        case(ImageViewType::e3D): return "e3D";
        case(ImageViewType::eCube): return "eCube";
        case(ImageViewType::e1DArray): return "e1DArray";
        case(ImageViewType::e2DArray): return "e2DArray";
        case(ImageViewType::eCubeArray): return "eCubeArray";
        default: return "UNKNOWN";
    }
}
const char * to_string(SharingMode val) {
    switch(val) {
        case(SharingMode::eExclusive): return "eExclusive";
        case(SharingMode::eConcurrent): return "eConcurrent";
        default: return "UNKNOWN";
    }
}
const char * to_string(IndexType val) {
    switch(val) {
        case(IndexType::eUint16): return "eUint16";
        case(IndexType::eUint32): return "eUint32";
        case(IndexType::eNoneKHR): return "eNoneKHR";
        case(IndexType::eUint8EXT): return "eUint8EXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(LogicOp val) {
    switch(val) {
        case(LogicOp::eClear): return "eClear";
        case(LogicOp::eAnd): return "eAnd";
        case(LogicOp::eAndReverse): return "eAndReverse";
        case(LogicOp::eCopy): return "eCopy";
        case(LogicOp::eAndInverted): return "eAndInverted";
        case(LogicOp::eNoOp): return "eNoOp";
        case(LogicOp::eXor): return "eXor";
        case(LogicOp::eOr): return "eOr";
        case(LogicOp::eNor): return "eNor";
        case(LogicOp::eEquivalent): return "eEquivalent";
        case(LogicOp::eInvert): return "eInvert";
        case(LogicOp::eOrReverse): return "eOrReverse";
        case(LogicOp::eCopyInverted): return "eCopyInverted";
        case(LogicOp::eOrInverted): return "eOrInverted";
        case(LogicOp::eNand): return "eNand";
        case(LogicOp::eSet): return "eSet";
        default: return "UNKNOWN";
    }
}
const char * to_string(PhysicalDeviceType val) {
    switch(val) {
        case(PhysicalDeviceType::eOther): return "eOther";
        case(PhysicalDeviceType::eIntegratedGpu): return "eIntegratedGpu";
        case(PhysicalDeviceType::eDiscreteGpu): return "eDiscreteGpu";
        case(PhysicalDeviceType::eVirtualGpu): return "eVirtualGpu";
        case(PhysicalDeviceType::eCpu): return "eCpu";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineBindPoint val) {
    switch(val) {
        case(PipelineBindPoint::eGraphics): return "eGraphics";
        case(PipelineBindPoint::eCompute): return "eCompute";
        case(PipelineBindPoint::eRayTracingKHR): return "eRayTracingKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PrimitiveTopology val) {
    switch(val) {
        case(PrimitiveTopology::ePointList): return "ePointList";
        case(PrimitiveTopology::eLineList): return "eLineList";
        case(PrimitiveTopology::eLineStrip): return "eLineStrip";
        case(PrimitiveTopology::eTriangleList): return "eTriangleList";
        case(PrimitiveTopology::eTriangleStrip): return "eTriangleStrip";
        case(PrimitiveTopology::eTriangleFan): return "eTriangleFan";
        case(PrimitiveTopology::eLineListWithAdjacency): return "eLineListWithAdjacency";
        case(PrimitiveTopology::eLineStripWithAdjacency): return "eLineStripWithAdjacency";
        case(PrimitiveTopology::eTriangleListWithAdjacency): return "eTriangleListWithAdjacency";
        case(PrimitiveTopology::eTriangleStripWithAdjacency): return "eTriangleStripWithAdjacency";
        case(PrimitiveTopology::ePatchList): return "ePatchList";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueryType val) {
    switch(val) {
        case(QueryType::eOcclusion): return "eOcclusion";
        case(QueryType::ePipelineStatistics): return "ePipelineStatistics";
        case(QueryType::eTimestamp): return "eTimestamp";
        case(QueryType::eReserved8): return "eReserved8";
        case(QueryType::eReserved4): return "eReserved4";
        case(QueryType::eTransformFeedbackStreamEXT): return "eTransformFeedbackStreamEXT";
        case(QueryType::ePerformanceQueryKHR): return "ePerformanceQueryKHR";
        case(QueryType::eAccelerationStructureCompactedSizeKHR): return "eAccelerationStructureCompactedSizeKHR";
        case(QueryType::eAccelerationStructureSerializationSizeKHR): return "eAccelerationStructureSerializationSizeKHR";
        case(QueryType::ePerformanceQueryINTEL): return "ePerformanceQueryINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(SubpassContents val) {
    switch(val) {
        case(SubpassContents::eInline): return "eInline";
        case(SubpassContents::eSecondaryCommandBuffers): return "eSecondaryCommandBuffers";
        default: return "UNKNOWN";
    }
}
const char * to_string(Result val) {
    switch(val) {
        case(Result::eSuccess): return "eSuccess";
        case(Result::eNotReady): return "eNotReady";
        case(Result::eTimeout): return "eTimeout";
        case(Result::eEventSet): return "eEventSet";
        case(Result::eEventReset): return "eEventReset";
        case(Result::eIncomplete): return "eIncomplete";
        case(Result::eErrorOutOfHostMemory): return "eErrorOutOfHostMemory";
        case(Result::eErrorOutOfDeviceMemory): return "eErrorOutOfDeviceMemory";
        case(Result::eErrorInitializationFailed): return "eErrorInitializationFailed";
        case(Result::eErrorDeviceLost): return "eErrorDeviceLost";
        case(Result::eErrorMemoryMapFailed): return "eErrorMemoryMapFailed";
        case(Result::eErrorLayerNotPresent): return "eErrorLayerNotPresent";
        case(Result::eErrorExtensionNotPresent): return "eErrorExtensionNotPresent";
        case(Result::eErrorFeatureNotPresent): return "eErrorFeatureNotPresent";
        case(Result::eErrorIncompatibleDriver): return "eErrorIncompatibleDriver";
        case(Result::eErrorTooManyObjects): return "eErrorTooManyObjects";
        case(Result::eErrorFormatNotSupported): return "eErrorFormatNotSupported";
        case(Result::eErrorFragmentedPool): return "eErrorFragmentedPool";
        case(Result::eErrorUnknown): return "eErrorUnknown";
        case(Result::eErrorSurfaceLostKHR): return "eErrorSurfaceLostKHR";
        case(Result::eErrorNativeWindowInUseKHR): return "eErrorNativeWindowInUseKHR";
        case(Result::eSuboptimalKHR): return "eSuboptimalKHR";
        case(Result::eErrorOutOfDateKHR): return "eErrorOutOfDateKHR";
        case(Result::eErrorIncompatibleDisplayKHR): return "eErrorIncompatibleDisplayKHR";
        case(Result::eErrorValidationFailedEXT): return "eErrorValidationFailedEXT";
        case(Result::eErrorInvalidShaderNV): return "eErrorInvalidShaderNV";
        case(Result::eErrorIncompatibleVersionKHR): return "eErrorIncompatibleVersionKHR";
        case(Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT): return "eErrorInvalidDrmFormatModifierPlaneLayoutEXT";
        case(Result::eErrorNotPermittedEXT): return "eErrorNotPermittedEXT";
        case(Result::eErrorFullScreenExclusiveModeLostEXT): return "eErrorFullScreenExclusiveModeLostEXT";
        case(Result::eThreadIdleKHR): return "eThreadIdleKHR";
        case(Result::eThreadDoneKHR): return "eThreadDoneKHR";
        case(Result::eOperationDeferredKHR): return "eOperationDeferredKHR";
        case(Result::eOperationNotDeferredKHR): return "eOperationNotDeferredKHR";
        case(Result::ePipelineCompileRequiredEXT): return "ePipelineCompileRequiredEXT";
        case(Result::eErrorOutOfPoolMemory): return "eErrorOutOfPoolMemory";
        case(Result::eErrorInvalidExternalHandle): return "eErrorInvalidExternalHandle";
        case(Result::eErrorFragmentation): return "eErrorFragmentation";
        case(Result::eErrorInvalidOpaqueCaptureAddress): return "eErrorInvalidOpaqueCaptureAddress";
        default: return "UNKNOWN";
    }
}
const char * to_string(StencilOp val) {
    switch(val) {
        case(StencilOp::eKeep): return "eKeep";
        case(StencilOp::eZero): return "eZero";
        case(StencilOp::eReplace): return "eReplace";
        case(StencilOp::eIncrementAndClamp): return "eIncrementAndClamp";
        case(StencilOp::eDecrementAndClamp): return "eDecrementAndClamp";
        case(StencilOp::eInvert): return "eInvert";
        case(StencilOp::eIncrementAndWrap): return "eIncrementAndWrap";
        case(StencilOp::eDecrementAndWrap): return "eDecrementAndWrap";
        default: return "UNKNOWN";
    }
}
const char * to_string(StructureType val) {
    switch(val) {
        case(StructureType::eApplicationInfo): return "eApplicationInfo";
        case(StructureType::eInstanceCreateInfo): return "eInstanceCreateInfo";
        case(StructureType::eDeviceQueueCreateInfo): return "eDeviceQueueCreateInfo";
        case(StructureType::eDeviceCreateInfo): return "eDeviceCreateInfo";
        case(StructureType::eSubmitInfo): return "eSubmitInfo";
        case(StructureType::eMemoryAllocateInfo): return "eMemoryAllocateInfo";
        case(StructureType::eMappedMemoryRange): return "eMappedMemoryRange";
        case(StructureType::eBindSparseInfo): return "eBindSparseInfo";
        case(StructureType::eFenceCreateInfo): return "eFenceCreateInfo";
        case(StructureType::eSemaphoreCreateInfo): return "eSemaphoreCreateInfo";
        case(StructureType::eEventCreateInfo): return "eEventCreateInfo";
        case(StructureType::eQueryPoolCreateInfo): return "eQueryPoolCreateInfo";
        case(StructureType::eBufferCreateInfo): return "eBufferCreateInfo";
        case(StructureType::eBufferViewCreateInfo): return "eBufferViewCreateInfo";
        case(StructureType::eImageCreateInfo): return "eImageCreateInfo";
        case(StructureType::eImageViewCreateInfo): return "eImageViewCreateInfo";
        case(StructureType::eShaderModuleCreateInfo): return "eShaderModuleCreateInfo";
        case(StructureType::ePipelineCacheCreateInfo): return "ePipelineCacheCreateInfo";
        case(StructureType::ePipelineShaderStageCreateInfo): return "ePipelineShaderStageCreateInfo";
        case(StructureType::ePipelineVertexInputStateCreateInfo): return "ePipelineVertexInputStateCreateInfo";
        case(StructureType::ePipelineInputAssemblyStateCreateInfo): return "ePipelineInputAssemblyStateCreateInfo";
        case(StructureType::ePipelineTessellationStateCreateInfo): return "ePipelineTessellationStateCreateInfo";
        case(StructureType::ePipelineViewportStateCreateInfo): return "ePipelineViewportStateCreateInfo";
        case(StructureType::ePipelineRasterizationStateCreateInfo): return "ePipelineRasterizationStateCreateInfo";
        case(StructureType::ePipelineMultisampleStateCreateInfo): return "ePipelineMultisampleStateCreateInfo";
        case(StructureType::ePipelineDepthStencilStateCreateInfo): return "ePipelineDepthStencilStateCreateInfo";
        case(StructureType::ePipelineColorBlendStateCreateInfo): return "ePipelineColorBlendStateCreateInfo";
        case(StructureType::ePipelineDynamicStateCreateInfo): return "ePipelineDynamicStateCreateInfo";
        case(StructureType::eGraphicsPipelineCreateInfo): return "eGraphicsPipelineCreateInfo";
        case(StructureType::eComputePipelineCreateInfo): return "eComputePipelineCreateInfo";
        case(StructureType::ePipelineLayoutCreateInfo): return "ePipelineLayoutCreateInfo";
        case(StructureType::eSamplerCreateInfo): return "eSamplerCreateInfo";
        case(StructureType::eDescriptorSetLayoutCreateInfo): return "eDescriptorSetLayoutCreateInfo";
        case(StructureType::eDescriptorPoolCreateInfo): return "eDescriptorPoolCreateInfo";
        case(StructureType::eDescriptorSetAllocateInfo): return "eDescriptorSetAllocateInfo";
        case(StructureType::eWriteDescriptorSet): return "eWriteDescriptorSet";
        case(StructureType::eCopyDescriptorSet): return "eCopyDescriptorSet";
        case(StructureType::eFramebufferCreateInfo): return "eFramebufferCreateInfo";
        case(StructureType::eRenderPassCreateInfo): return "eRenderPassCreateInfo";
        case(StructureType::eCommandPoolCreateInfo): return "eCommandPoolCreateInfo";
        case(StructureType::eCommandBufferAllocateInfo): return "eCommandBufferAllocateInfo";
        case(StructureType::eCommandBufferInheritanceInfo): return "eCommandBufferInheritanceInfo";
        case(StructureType::eCommandBufferBeginInfo): return "eCommandBufferBeginInfo";
        case(StructureType::eRenderPassBeginInfo): return "eRenderPassBeginInfo";
        case(StructureType::eBufferMemoryBarrier): return "eBufferMemoryBarrier";
        case(StructureType::eImageMemoryBarrier): return "eImageMemoryBarrier";
        case(StructureType::eMemoryBarrier): return "eMemoryBarrier";
        case(StructureType::eLoaderInstanceCreateInfo): return "eLoaderInstanceCreateInfo";
        case(StructureType::eLoaderDeviceCreateInfo): return "eLoaderDeviceCreateInfo";
        case(StructureType::eSwapchainCreateInfoKHR): return "eSwapchainCreateInfoKHR";
        case(StructureType::ePresentInfoKHR): return "ePresentInfoKHR";
        case(StructureType::eDeviceGroupPresentCapabilitiesKHR): return "eDeviceGroupPresentCapabilitiesKHR";
        case(StructureType::eImageSwapchainCreateInfoKHR): return "eImageSwapchainCreateInfoKHR";
        case(StructureType::eBindImageMemorySwapchainInfoKHR): return "eBindImageMemorySwapchainInfoKHR";
        case(StructureType::eAcquireNextImageInfoKHR): return "eAcquireNextImageInfoKHR";
        case(StructureType::eDeviceGroupPresentInfoKHR): return "eDeviceGroupPresentInfoKHR";
        case(StructureType::eDeviceGroupSwapchainCreateInfoKHR): return "eDeviceGroupSwapchainCreateInfoKHR";
        case(StructureType::eDisplayModeCreateInfoKHR): return "eDisplayModeCreateInfoKHR";
        case(StructureType::eDisplaySurfaceCreateInfoKHR): return "eDisplaySurfaceCreateInfoKHR";
        case(StructureType::eDisplayPresentInfoKHR): return "eDisplayPresentInfoKHR";
        case(StructureType::eXlibSurfaceCreateInfoKHR): return "eXlibSurfaceCreateInfoKHR";
        case(StructureType::eXcbSurfaceCreateInfoKHR): return "eXcbSurfaceCreateInfoKHR";
        case(StructureType::eWaylandSurfaceCreateInfoKHR): return "eWaylandSurfaceCreateInfoKHR";
        case(StructureType::eAndroidSurfaceCreateInfoKHR): return "eAndroidSurfaceCreateInfoKHR";
        case(StructureType::eWin32SurfaceCreateInfoKHR): return "eWin32SurfaceCreateInfoKHR";
        case(StructureType::eNativeBufferANDROID): return "eNativeBufferANDROID";
        case(StructureType::eSwapchainImageCreateInfoANDROID): return "eSwapchainImageCreateInfoANDROID";
        case(StructureType::ePhysicalDevicePresentationPropertiesANDROID): return "ePhysicalDevicePresentationPropertiesANDROID";
        case(StructureType::eDebugReportCallbackCreateInfoEXT): return "eDebugReportCallbackCreateInfoEXT";
        case(StructureType::ePipelineRasterizationStateRasterizationOrderAMD): return "ePipelineRasterizationStateRasterizationOrderAMD";
        case(StructureType::eDebugMarkerObjectNameInfoEXT): return "eDebugMarkerObjectNameInfoEXT";
        case(StructureType::eDebugMarkerObjectTagInfoEXT): return "eDebugMarkerObjectTagInfoEXT";
        case(StructureType::eDebugMarkerMarkerInfoEXT): return "eDebugMarkerMarkerInfoEXT";
        case(StructureType::eDedicatedAllocationImageCreateInfoNV): return "eDedicatedAllocationImageCreateInfoNV";
        case(StructureType::eDedicatedAllocationBufferCreateInfoNV): return "eDedicatedAllocationBufferCreateInfoNV";
        case(StructureType::eDedicatedAllocationMemoryAllocateInfoNV): return "eDedicatedAllocationMemoryAllocateInfoNV";
        case(StructureType::ePhysicalDeviceTransformFeedbackFeaturesEXT): return "ePhysicalDeviceTransformFeedbackFeaturesEXT";
        case(StructureType::ePhysicalDeviceTransformFeedbackPropertiesEXT): return "ePhysicalDeviceTransformFeedbackPropertiesEXT";
        case(StructureType::ePipelineRasterizationStateStreamCreateInfoEXT): return "ePipelineRasterizationStateStreamCreateInfoEXT";
        case(StructureType::eImageViewHandleInfoNVX): return "eImageViewHandleInfoNVX";
        case(StructureType::eImageViewAddressPropertiesNVX): return "eImageViewAddressPropertiesNVX";
        case(StructureType::eTextureLodGatherFormatPropertiesAMD): return "eTextureLodGatherFormatPropertiesAMD";
        case(StructureType::eStreamDescriptorSurfaceCreateInfoGGP): return "eStreamDescriptorSurfaceCreateInfoGGP";
        case(StructureType::ePhysicalDeviceCornerSampledImageFeaturesNV): return "ePhysicalDeviceCornerSampledImageFeaturesNV";
        case(StructureType::eExternalMemoryImageCreateInfoNV): return "eExternalMemoryImageCreateInfoNV";
        case(StructureType::eExportMemoryAllocateInfoNV): return "eExportMemoryAllocateInfoNV";
        case(StructureType::eImportMemoryWin32HandleInfoNV): return "eImportMemoryWin32HandleInfoNV";
        case(StructureType::eExportMemoryWin32HandleInfoNV): return "eExportMemoryWin32HandleInfoNV";
        case(StructureType::eWin32KeyedMutexAcquireReleaseInfoNV): return "eWin32KeyedMutexAcquireReleaseInfoNV";
        case(StructureType::eValidationFlagsEXT): return "eValidationFlagsEXT";
        case(StructureType::eViSurfaceCreateInfoNN): return "eViSurfaceCreateInfoNN";
        case(StructureType::ePhysicalDeviceTextureCompressionAstcHdrFeaturesEXT): return "ePhysicalDeviceTextureCompressionAstcHdrFeaturesEXT";
        case(StructureType::eImageViewAstcDecodeModeEXT): return "eImageViewAstcDecodeModeEXT";
        case(StructureType::ePhysicalDeviceAstcDecodeFeaturesEXT): return "ePhysicalDeviceAstcDecodeFeaturesEXT";
        case(StructureType::eImportMemoryWin32HandleInfoKHR): return "eImportMemoryWin32HandleInfoKHR";
        case(StructureType::eExportMemoryWin32HandleInfoKHR): return "eExportMemoryWin32HandleInfoKHR";
        case(StructureType::eMemoryWin32HandlePropertiesKHR): return "eMemoryWin32HandlePropertiesKHR";
        case(StructureType::eMemoryGetWin32HandleInfoKHR): return "eMemoryGetWin32HandleInfoKHR";
        case(StructureType::eImportMemoryFdInfoKHR): return "eImportMemoryFdInfoKHR";
        case(StructureType::eMemoryFdPropertiesKHR): return "eMemoryFdPropertiesKHR";
        case(StructureType::eMemoryGetFdInfoKHR): return "eMemoryGetFdInfoKHR";
        case(StructureType::eWin32KeyedMutexAcquireReleaseInfoKHR): return "eWin32KeyedMutexAcquireReleaseInfoKHR";
        case(StructureType::eImportSemaphoreWin32HandleInfoKHR): return "eImportSemaphoreWin32HandleInfoKHR";
        case(StructureType::eExportSemaphoreWin32HandleInfoKHR): return "eExportSemaphoreWin32HandleInfoKHR";
        case(StructureType::eD3D12FenceSubmitInfoKHR): return "eD3D12FenceSubmitInfoKHR";
        case(StructureType::eSemaphoreGetWin32HandleInfoKHR): return "eSemaphoreGetWin32HandleInfoKHR";
        case(StructureType::eImportSemaphoreFdInfoKHR): return "eImportSemaphoreFdInfoKHR";
        case(StructureType::eSemaphoreGetFdInfoKHR): return "eSemaphoreGetFdInfoKHR";
        case(StructureType::ePhysicalDevicePushDescriptorPropertiesKHR): return "ePhysicalDevicePushDescriptorPropertiesKHR";
        case(StructureType::eCommandBufferInheritanceConditionalRenderingInfoEXT): return "eCommandBufferInheritanceConditionalRenderingInfoEXT";
        case(StructureType::ePhysicalDeviceConditionalRenderingFeaturesEXT): return "ePhysicalDeviceConditionalRenderingFeaturesEXT";
        case(StructureType::eConditionalRenderingBeginInfoEXT): return "eConditionalRenderingBeginInfoEXT";
        case(StructureType::ePresentRegionsKHR): return "ePresentRegionsKHR";
        case(StructureType::ePipelineViewportWScalingStateCreateInfoNV): return "ePipelineViewportWScalingStateCreateInfoNV";
        case(StructureType::eSurfaceCapabilities2EXT): return "eSurfaceCapabilities2EXT";
        case(StructureType::eDisplayPowerInfoEXT): return "eDisplayPowerInfoEXT";
        case(StructureType::eDeviceEventInfoEXT): return "eDeviceEventInfoEXT";
        case(StructureType::eDisplayEventInfoEXT): return "eDisplayEventInfoEXT";
        case(StructureType::eSwapchainCounterCreateInfoEXT): return "eSwapchainCounterCreateInfoEXT";
        case(StructureType::ePresentTimesInfoGOOGLE): return "ePresentTimesInfoGOOGLE";
        case(StructureType::ePhysicalDeviceMultiviewPerViewAttributesPropertiesNVX): return "ePhysicalDeviceMultiviewPerViewAttributesPropertiesNVX";
        case(StructureType::ePipelineViewportSwizzleStateCreateInfoNV): return "ePipelineViewportSwizzleStateCreateInfoNV";
        case(StructureType::ePhysicalDeviceDiscardRectanglePropertiesEXT): return "ePhysicalDeviceDiscardRectanglePropertiesEXT";
        case(StructureType::ePipelineDiscardRectangleStateCreateInfoEXT): return "ePipelineDiscardRectangleStateCreateInfoEXT";
        case(StructureType::ePhysicalDeviceConservativeRasterizationPropertiesEXT): return "ePhysicalDeviceConservativeRasterizationPropertiesEXT";
        case(StructureType::ePipelineRasterizationConservativeStateCreateInfoEXT): return "ePipelineRasterizationConservativeStateCreateInfoEXT";
        case(StructureType::ePhysicalDeviceDepthClipEnableFeaturesEXT): return "ePhysicalDeviceDepthClipEnableFeaturesEXT";
        case(StructureType::ePipelineRasterizationDepthClipStateCreateInfoEXT): return "ePipelineRasterizationDepthClipStateCreateInfoEXT";
        case(StructureType::eHdrMetadataEXT): return "eHdrMetadataEXT";
        case(StructureType::eSharedPresentSurfaceCapabilitiesKHR): return "eSharedPresentSurfaceCapabilitiesKHR";
        case(StructureType::eImportFenceWin32HandleInfoKHR): return "eImportFenceWin32HandleInfoKHR";
        case(StructureType::eExportFenceWin32HandleInfoKHR): return "eExportFenceWin32HandleInfoKHR";
        case(StructureType::eFenceGetWin32HandleInfoKHR): return "eFenceGetWin32HandleInfoKHR";
        case(StructureType::eImportFenceFdInfoKHR): return "eImportFenceFdInfoKHR";
        case(StructureType::eFenceGetFdInfoKHR): return "eFenceGetFdInfoKHR";
        case(StructureType::ePhysicalDevicePerformanceQueryFeaturesKHR): return "ePhysicalDevicePerformanceQueryFeaturesKHR";
        case(StructureType::ePhysicalDevicePerformanceQueryPropertiesKHR): return "ePhysicalDevicePerformanceQueryPropertiesKHR";
        case(StructureType::eQueryPoolPerformanceCreateInfoKHR): return "eQueryPoolPerformanceCreateInfoKHR";
        case(StructureType::ePerformanceQuerySubmitInfoKHR): return "ePerformanceQuerySubmitInfoKHR";
        case(StructureType::eAcquireProfilingLockInfoKHR): return "eAcquireProfilingLockInfoKHR";
        case(StructureType::ePerformanceCounterKHR): return "ePerformanceCounterKHR";
        case(StructureType::ePerformanceCounterDescriptionKHR): return "ePerformanceCounterDescriptionKHR";
        case(StructureType::ePhysicalDeviceSurfaceInfo2KHR): return "ePhysicalDeviceSurfaceInfo2KHR";
        case(StructureType::eSurfaceCapabilities2KHR): return "eSurfaceCapabilities2KHR";
        case(StructureType::eSurfaceFormat2KHR): return "eSurfaceFormat2KHR";
        case(StructureType::eDisplayProperties2KHR): return "eDisplayProperties2KHR";
        case(StructureType::eDisplayPlaneProperties2KHR): return "eDisplayPlaneProperties2KHR";
        case(StructureType::eDisplayModeProperties2KHR): return "eDisplayModeProperties2KHR";
        case(StructureType::eDisplayPlaneInfo2KHR): return "eDisplayPlaneInfo2KHR";
        case(StructureType::eDisplayPlaneCapabilities2KHR): return "eDisplayPlaneCapabilities2KHR";
        case(StructureType::eIosSurfaceCreateInfoMVK): return "eIosSurfaceCreateInfoMVK";
        case(StructureType::eMacosSurfaceCreateInfoMVK): return "eMacosSurfaceCreateInfoMVK";
        case(StructureType::eDebugUtilsObjectNameInfoEXT): return "eDebugUtilsObjectNameInfoEXT";
        case(StructureType::eDebugUtilsObjectTagInfoEXT): return "eDebugUtilsObjectTagInfoEXT";
        case(StructureType::eDebugUtilsLabelEXT): return "eDebugUtilsLabelEXT";
        case(StructureType::eDebugUtilsMessengerCallbackDataEXT): return "eDebugUtilsMessengerCallbackDataEXT";
        case(StructureType::eDebugUtilsMessengerCreateInfoEXT): return "eDebugUtilsMessengerCreateInfoEXT";
        case(StructureType::eAndroidHardwareBufferUsageANDROID): return "eAndroidHardwareBufferUsageANDROID";
        case(StructureType::eAndroidHardwareBufferPropertiesANDROID): return "eAndroidHardwareBufferPropertiesANDROID";
        case(StructureType::eAndroidHardwareBufferFormatPropertiesANDROID): return "eAndroidHardwareBufferFormatPropertiesANDROID";
        case(StructureType::eImportAndroidHardwareBufferInfoANDROID): return "eImportAndroidHardwareBufferInfoANDROID";
        case(StructureType::eMemoryGetAndroidHardwareBufferInfoANDROID): return "eMemoryGetAndroidHardwareBufferInfoANDROID";
        case(StructureType::eExternalFormatANDROID): return "eExternalFormatANDROID";
        case(StructureType::ePhysicalDeviceInlineUniformBlockFeaturesEXT): return "ePhysicalDeviceInlineUniformBlockFeaturesEXT";
        case(StructureType::ePhysicalDeviceInlineUniformBlockPropertiesEXT): return "ePhysicalDeviceInlineUniformBlockPropertiesEXT";
        case(StructureType::eWriteDescriptorSetInlineUniformBlockEXT): return "eWriteDescriptorSetInlineUniformBlockEXT";
        case(StructureType::eDescriptorPoolInlineUniformBlockCreateInfoEXT): return "eDescriptorPoolInlineUniformBlockCreateInfoEXT";
        case(StructureType::eSampleLocationsInfoEXT): return "eSampleLocationsInfoEXT";
        case(StructureType::eRenderPassSampleLocationsBeginInfoEXT): return "eRenderPassSampleLocationsBeginInfoEXT";
        case(StructureType::ePipelineSampleLocationsStateCreateInfoEXT): return "ePipelineSampleLocationsStateCreateInfoEXT";
        case(StructureType::ePhysicalDeviceSampleLocationsPropertiesEXT): return "ePhysicalDeviceSampleLocationsPropertiesEXT";
        case(StructureType::eMultisamplePropertiesEXT): return "eMultisamplePropertiesEXT";
        case(StructureType::ePhysicalDeviceBlendOperationAdvancedFeaturesEXT): return "ePhysicalDeviceBlendOperationAdvancedFeaturesEXT";
        case(StructureType::ePhysicalDeviceBlendOperationAdvancedPropertiesEXT): return "ePhysicalDeviceBlendOperationAdvancedPropertiesEXT";
        case(StructureType::ePipelineColorBlendAdvancedStateCreateInfoEXT): return "ePipelineColorBlendAdvancedStateCreateInfoEXT";
        case(StructureType::ePipelineCoverageToColorStateCreateInfoNV): return "ePipelineCoverageToColorStateCreateInfoNV";
        case(StructureType::eBindAccelerationStructureMemoryInfoKHR): return "eBindAccelerationStructureMemoryInfoKHR";
        case(StructureType::eWriteDescriptorSetAccelerationStructureKHR): return "eWriteDescriptorSetAccelerationStructureKHR";
        case(StructureType::eAccelerationStructureBuildGeometryInfoKHR): return "eAccelerationStructureBuildGeometryInfoKHR";
        case(StructureType::eAccelerationStructureCreateGeometryTypeInfoKHR): return "eAccelerationStructureCreateGeometryTypeInfoKHR";
        case(StructureType::eAccelerationStructureDeviceAddressInfoKHR): return "eAccelerationStructureDeviceAddressInfoKHR";
        case(StructureType::eAccelerationStructureGeometryAabbsDataKHR): return "eAccelerationStructureGeometryAabbsDataKHR";
        case(StructureType::eAccelerationStructureGeometryInstancesDataKHR): return "eAccelerationStructureGeometryInstancesDataKHR";
        case(StructureType::eAccelerationStructureGeometryTrianglesDataKHR): return "eAccelerationStructureGeometryTrianglesDataKHR";
        case(StructureType::eAccelerationStructureGeometryKHR): return "eAccelerationStructureGeometryKHR";
        case(StructureType::eAccelerationStructureMemoryRequirementsInfoKHR): return "eAccelerationStructureMemoryRequirementsInfoKHR";
        case(StructureType::eAccelerationStructureVersionKHR): return "eAccelerationStructureVersionKHR";
        case(StructureType::eCopyAccelerationStructureInfoKHR): return "eCopyAccelerationStructureInfoKHR";
        case(StructureType::eCopyAccelerationStructureToMemoryInfoKHR): return "eCopyAccelerationStructureToMemoryInfoKHR";
        case(StructureType::eCopyMemoryToAccelerationStructureInfoKHR): return "eCopyMemoryToAccelerationStructureInfoKHR";
        case(StructureType::ePhysicalDeviceRayTracingFeaturesKHR): return "ePhysicalDeviceRayTracingFeaturesKHR";
        case(StructureType::ePhysicalDeviceRayTracingPropertiesKHR): return "ePhysicalDeviceRayTracingPropertiesKHR";
        case(StructureType::eRayTracingPipelineCreateInfoKHR): return "eRayTracingPipelineCreateInfoKHR";
        case(StructureType::eRayTracingShaderGroupCreateInfoKHR): return "eRayTracingShaderGroupCreateInfoKHR";
        case(StructureType::eAccelerationStructureCreateInfoKHR): return "eAccelerationStructureCreateInfoKHR";
        case(StructureType::eRayTracingPipelineInterfaceCreateInfoKHR): return "eRayTracingPipelineInterfaceCreateInfoKHR";
        case(StructureType::ePipelineCoverageModulationStateCreateInfoNV): return "ePipelineCoverageModulationStateCreateInfoNV";
        case(StructureType::ePhysicalDeviceShaderSmBuiltinsFeaturesNV): return "ePhysicalDeviceShaderSmBuiltinsFeaturesNV";
        case(StructureType::ePhysicalDeviceShaderSmBuiltinsPropertiesNV): return "ePhysicalDeviceShaderSmBuiltinsPropertiesNV";
        case(StructureType::eDrmFormatModifierPropertiesListEXT): return "eDrmFormatModifierPropertiesListEXT";
        case(StructureType::eDrmFormatModifierPropertiesEXT): return "eDrmFormatModifierPropertiesEXT";
        case(StructureType::ePhysicalDeviceImageDrmFormatModifierInfoEXT): return "ePhysicalDeviceImageDrmFormatModifierInfoEXT";
        case(StructureType::eImageDrmFormatModifierListCreateInfoEXT): return "eImageDrmFormatModifierListCreateInfoEXT";
        case(StructureType::eImageDrmFormatModifierExplicitCreateInfoEXT): return "eImageDrmFormatModifierExplicitCreateInfoEXT";
        case(StructureType::eImageDrmFormatModifierPropertiesEXT): return "eImageDrmFormatModifierPropertiesEXT";
        case(StructureType::eValidationCacheCreateInfoEXT): return "eValidationCacheCreateInfoEXT";
        case(StructureType::eShaderModuleValidationCacheCreateInfoEXT): return "eShaderModuleValidationCacheCreateInfoEXT";
        case(StructureType::ePipelineViewportShadingRateImageStateCreateInfoNV): return "ePipelineViewportShadingRateImageStateCreateInfoNV";
        case(StructureType::ePhysicalDeviceShadingRateImageFeaturesNV): return "ePhysicalDeviceShadingRateImageFeaturesNV";
        case(StructureType::ePhysicalDeviceShadingRateImagePropertiesNV): return "ePhysicalDeviceShadingRateImagePropertiesNV";
        case(StructureType::ePipelineViewportCoarseSampleOrderStateCreateInfoNV): return "ePipelineViewportCoarseSampleOrderStateCreateInfoNV";
        case(StructureType::eRayTracingPipelineCreateInfoNV): return "eRayTracingPipelineCreateInfoNV";
        case(StructureType::eAccelerationStructureCreateInfoNV): return "eAccelerationStructureCreateInfoNV";
        case(StructureType::eGeometryNV): return "eGeometryNV";
        case(StructureType::eGeometryTrianglesNV): return "eGeometryTrianglesNV";
        case(StructureType::eGeometryAabbNV): return "eGeometryAabbNV";
        case(StructureType::eAccelerationStructureMemoryRequirementsInfoNV): return "eAccelerationStructureMemoryRequirementsInfoNV";
        case(StructureType::ePhysicalDeviceRayTracingPropertiesNV): return "ePhysicalDeviceRayTracingPropertiesNV";
        case(StructureType::eRayTracingShaderGroupCreateInfoNV): return "eRayTracingShaderGroupCreateInfoNV";
        case(StructureType::eAccelerationStructureInfoNV): return "eAccelerationStructureInfoNV";
        case(StructureType::ePhysicalDeviceRepresentativeFragmentTestFeaturesNV): return "ePhysicalDeviceRepresentativeFragmentTestFeaturesNV";
        case(StructureType::ePipelineRepresentativeFragmentTestStateCreateInfoNV): return "ePipelineRepresentativeFragmentTestStateCreateInfoNV";
        case(StructureType::ePhysicalDeviceImageViewImageFormatInfoEXT): return "ePhysicalDeviceImageViewImageFormatInfoEXT";
        case(StructureType::eFilterCubicImageViewImageFormatPropertiesEXT): return "eFilterCubicImageViewImageFormatPropertiesEXT";
        case(StructureType::eDeviceQueueGlobalPriorityCreateInfoEXT): return "eDeviceQueueGlobalPriorityCreateInfoEXT";
        case(StructureType::eImportMemoryHostPointerInfoEXT): return "eImportMemoryHostPointerInfoEXT";
        case(StructureType::eMemoryHostPointerPropertiesEXT): return "eMemoryHostPointerPropertiesEXT";
        case(StructureType::ePhysicalDeviceExternalMemoryHostPropertiesEXT): return "ePhysicalDeviceExternalMemoryHostPropertiesEXT";
        case(StructureType::ePhysicalDeviceShaderClockFeaturesKHR): return "ePhysicalDeviceShaderClockFeaturesKHR";
        case(StructureType::ePipelineCompilerControlCreateInfoAMD): return "ePipelineCompilerControlCreateInfoAMD";
        case(StructureType::eCalibratedTimestampInfoEXT): return "eCalibratedTimestampInfoEXT";
        case(StructureType::ePhysicalDeviceShaderCorePropertiesAMD): return "ePhysicalDeviceShaderCorePropertiesAMD";
        case(StructureType::eDeviceMemoryOverallocationCreateInfoAMD): return "eDeviceMemoryOverallocationCreateInfoAMD";
        case(StructureType::ePhysicalDeviceVertexAttributeDivisorPropertiesEXT): return "ePhysicalDeviceVertexAttributeDivisorPropertiesEXT";
        case(StructureType::ePipelineVertexInputDivisorStateCreateInfoEXT): return "ePipelineVertexInputDivisorStateCreateInfoEXT";
        case(StructureType::ePhysicalDeviceVertexAttributeDivisorFeaturesEXT): return "ePhysicalDeviceVertexAttributeDivisorFeaturesEXT";
        case(StructureType::ePresentFrameTokenGGP): return "ePresentFrameTokenGGP";
        case(StructureType::ePipelineCreationFeedbackCreateInfoEXT): return "ePipelineCreationFeedbackCreateInfoEXT";
        case(StructureType::ePhysicalDeviceComputeShaderDerivativesFeaturesNV): return "ePhysicalDeviceComputeShaderDerivativesFeaturesNV";
        case(StructureType::ePhysicalDeviceMeshShaderFeaturesNV): return "ePhysicalDeviceMeshShaderFeaturesNV";
        case(StructureType::ePhysicalDeviceMeshShaderPropertiesNV): return "ePhysicalDeviceMeshShaderPropertiesNV";
        case(StructureType::ePhysicalDeviceFragmentShaderBarycentricFeaturesNV): return "ePhysicalDeviceFragmentShaderBarycentricFeaturesNV";
        case(StructureType::ePhysicalDeviceShaderImageFootprintFeaturesNV): return "ePhysicalDeviceShaderImageFootprintFeaturesNV";
        case(StructureType::ePipelineViewportExclusiveScissorStateCreateInfoNV): return "ePipelineViewportExclusiveScissorStateCreateInfoNV";
        case(StructureType::ePhysicalDeviceExclusiveScissorFeaturesNV): return "ePhysicalDeviceExclusiveScissorFeaturesNV";
        case(StructureType::eCheckpointDataNV): return "eCheckpointDataNV";
        case(StructureType::eQueueFamilyCheckpointPropertiesNV): return "eQueueFamilyCheckpointPropertiesNV";
        case(StructureType::ePhysicalDeviceShaderIntegerFunctions2FeaturesINTEL): return "ePhysicalDeviceShaderIntegerFunctions2FeaturesINTEL";
        case(StructureType::eQueryPoolPerformanceQueryCreateInfoINTEL): return "eQueryPoolPerformanceQueryCreateInfoINTEL";
        case(StructureType::eInitializePerformanceApiInfoINTEL): return "eInitializePerformanceApiInfoINTEL";
        case(StructureType::ePerformanceMarkerInfoINTEL): return "ePerformanceMarkerInfoINTEL";
        case(StructureType::ePerformanceStreamMarkerInfoINTEL): return "ePerformanceStreamMarkerInfoINTEL";
        case(StructureType::ePerformanceOverrideInfoINTEL): return "ePerformanceOverrideInfoINTEL";
        case(StructureType::ePerformanceConfigurationAcquireInfoINTEL): return "ePerformanceConfigurationAcquireInfoINTEL";
        case(StructureType::ePhysicalDevicePciBusInfoPropertiesEXT): return "ePhysicalDevicePciBusInfoPropertiesEXT";
        case(StructureType::eDisplayNativeHdrSurfaceCapabilitiesAMD): return "eDisplayNativeHdrSurfaceCapabilitiesAMD";
        case(StructureType::eSwapchainDisplayNativeHdrCreateInfoAMD): return "eSwapchainDisplayNativeHdrCreateInfoAMD";
        case(StructureType::eImagepipeSurfaceCreateInfoFUCHSIA): return "eImagepipeSurfaceCreateInfoFUCHSIA";
        case(StructureType::eMetalSurfaceCreateInfoEXT): return "eMetalSurfaceCreateInfoEXT";
        case(StructureType::ePhysicalDeviceFragmentDensityMapFeaturesEXT): return "ePhysicalDeviceFragmentDensityMapFeaturesEXT";
        case(StructureType::ePhysicalDeviceFragmentDensityMapPropertiesEXT): return "ePhysicalDeviceFragmentDensityMapPropertiesEXT";
        case(StructureType::eRenderPassFragmentDensityMapCreateInfoEXT): return "eRenderPassFragmentDensityMapCreateInfoEXT";
        case(StructureType::ePhysicalDeviceSubgroupSizeControlPropertiesEXT): return "ePhysicalDeviceSubgroupSizeControlPropertiesEXT";
        case(StructureType::ePipelineShaderStageRequiredSubgroupSizeCreateInfoEXT): return "ePipelineShaderStageRequiredSubgroupSizeCreateInfoEXT";
        case(StructureType::ePhysicalDeviceSubgroupSizeControlFeaturesEXT): return "ePhysicalDeviceSubgroupSizeControlFeaturesEXT";
        case(StructureType::ePhysicalDeviceShaderCoreProperties2AMD): return "ePhysicalDeviceShaderCoreProperties2AMD";
        case(StructureType::ePhysicalDeviceCoherentMemoryFeaturesAMD): return "ePhysicalDeviceCoherentMemoryFeaturesAMD";
        case(StructureType::ePhysicalDeviceMemoryBudgetPropertiesEXT): return "ePhysicalDeviceMemoryBudgetPropertiesEXT";
        case(StructureType::ePhysicalDeviceMemoryPriorityFeaturesEXT): return "ePhysicalDeviceMemoryPriorityFeaturesEXT";
        case(StructureType::eMemoryPriorityAllocateInfoEXT): return "eMemoryPriorityAllocateInfoEXT";
        case(StructureType::eSurfaceProtectedCapabilitiesKHR): return "eSurfaceProtectedCapabilitiesKHR";
        case(StructureType::ePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV): return "ePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV";
        case(StructureType::ePhysicalDeviceBufferDeviceAddressFeaturesEXT): return "ePhysicalDeviceBufferDeviceAddressFeaturesEXT";
        case(StructureType::eBufferDeviceAddressCreateInfoEXT): return "eBufferDeviceAddressCreateInfoEXT";
        case(StructureType::ePhysicalDeviceToolPropertiesEXT): return "ePhysicalDeviceToolPropertiesEXT";
        case(StructureType::eValidationFeaturesEXT): return "eValidationFeaturesEXT";
        case(StructureType::ePhysicalDeviceCooperativeMatrixFeaturesNV): return "ePhysicalDeviceCooperativeMatrixFeaturesNV";
        case(StructureType::eCooperativeMatrixPropertiesNV): return "eCooperativeMatrixPropertiesNV";
        case(StructureType::ePhysicalDeviceCooperativeMatrixPropertiesNV): return "ePhysicalDeviceCooperativeMatrixPropertiesNV";
        case(StructureType::ePhysicalDeviceCoverageReductionModeFeaturesNV): return "ePhysicalDeviceCoverageReductionModeFeaturesNV";
        case(StructureType::ePipelineCoverageReductionStateCreateInfoNV): return "ePipelineCoverageReductionStateCreateInfoNV";
        case(StructureType::eFramebufferMixedSamplesCombinationNV): return "eFramebufferMixedSamplesCombinationNV";
        case(StructureType::ePhysicalDeviceFragmentShaderInterlockFeaturesEXT): return "ePhysicalDeviceFragmentShaderInterlockFeaturesEXT";
        case(StructureType::ePhysicalDeviceYcbcrImageArraysFeaturesEXT): return "ePhysicalDeviceYcbcrImageArraysFeaturesEXT";
        case(StructureType::eSurfaceFullScreenExclusiveInfoEXT): return "eSurfaceFullScreenExclusiveInfoEXT";
        case(StructureType::eSurfaceCapabilitiesFullScreenExclusiveEXT): return "eSurfaceCapabilitiesFullScreenExclusiveEXT";
        case(StructureType::eSurfaceFullScreenExclusiveWin32InfoEXT): return "eSurfaceFullScreenExclusiveWin32InfoEXT";
        case(StructureType::eHeadlessSurfaceCreateInfoEXT): return "eHeadlessSurfaceCreateInfoEXT";
        case(StructureType::ePhysicalDeviceLineRasterizationFeaturesEXT): return "ePhysicalDeviceLineRasterizationFeaturesEXT";
        case(StructureType::ePipelineRasterizationLineStateCreateInfoEXT): return "ePipelineRasterizationLineStateCreateInfoEXT";
        case(StructureType::ePhysicalDeviceLineRasterizationPropertiesEXT): return "ePhysicalDeviceLineRasterizationPropertiesEXT";
        case(StructureType::ePhysicalDeviceShaderAtomicFloatFeaturesEXT): return "ePhysicalDeviceShaderAtomicFloatFeaturesEXT";
        case(StructureType::ePhysicalDeviceIndexTypeUint8FeaturesEXT): return "ePhysicalDeviceIndexTypeUint8FeaturesEXT";
        case(StructureType::ePhysicalDeviceExtendedDynamicStateFeaturesEXT): return "ePhysicalDeviceExtendedDynamicStateFeaturesEXT";
        case(StructureType::eDeferredOperationInfoKHR): return "eDeferredOperationInfoKHR";
        case(StructureType::ePhysicalDevicePipelineExecutablePropertiesFeaturesKHR): return "ePhysicalDevicePipelineExecutablePropertiesFeaturesKHR";
        case(StructureType::ePipelineInfoKHR): return "ePipelineInfoKHR";
        case(StructureType::ePipelineExecutablePropertiesKHR): return "ePipelineExecutablePropertiesKHR";
        case(StructureType::ePipelineExecutableInfoKHR): return "ePipelineExecutableInfoKHR";
        case(StructureType::ePipelineExecutableStatisticKHR): return "ePipelineExecutableStatisticKHR";
        case(StructureType::ePipelineExecutableInternalRepresentationKHR): return "ePipelineExecutableInternalRepresentationKHR";
        case(StructureType::ePhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT): return "ePhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT";
        case(StructureType::ePhysicalDeviceDeviceGeneratedCommandsPropertiesNV): return "ePhysicalDeviceDeviceGeneratedCommandsPropertiesNV";
        case(StructureType::eGraphicsShaderGroupCreateInfoNV): return "eGraphicsShaderGroupCreateInfoNV";
        case(StructureType::eGraphicsPipelineShaderGroupsCreateInfoNV): return "eGraphicsPipelineShaderGroupsCreateInfoNV";
        case(StructureType::eIndirectCommandsLayoutTokenNV): return "eIndirectCommandsLayoutTokenNV";
        case(StructureType::eIndirectCommandsLayoutCreateInfoNV): return "eIndirectCommandsLayoutCreateInfoNV";
        case(StructureType::eGeneratedCommandsInfoNV): return "eGeneratedCommandsInfoNV";
        case(StructureType::eGeneratedCommandsMemoryRequirementsInfoNV): return "eGeneratedCommandsMemoryRequirementsInfoNV";
        case(StructureType::ePhysicalDeviceDeviceGeneratedCommandsFeaturesNV): return "ePhysicalDeviceDeviceGeneratedCommandsFeaturesNV";
        case(StructureType::ePhysicalDeviceTexelBufferAlignmentFeaturesEXT): return "ePhysicalDeviceTexelBufferAlignmentFeaturesEXT";
        case(StructureType::ePhysicalDeviceTexelBufferAlignmentPropertiesEXT): return "ePhysicalDeviceTexelBufferAlignmentPropertiesEXT";
        case(StructureType::eCommandBufferInheritanceRenderPassTransformInfoQCOM): return "eCommandBufferInheritanceRenderPassTransformInfoQCOM";
        case(StructureType::eRenderPassTransformBeginInfoQCOM): return "eRenderPassTransformBeginInfoQCOM";
        case(StructureType::ePhysicalDeviceRobustness2FeaturesEXT): return "ePhysicalDeviceRobustness2FeaturesEXT";
        case(StructureType::ePhysicalDeviceRobustness2PropertiesEXT): return "ePhysicalDeviceRobustness2PropertiesEXT";
        case(StructureType::eSamplerCustomBorderColorCreateInfoEXT): return "eSamplerCustomBorderColorCreateInfoEXT";
        case(StructureType::ePhysicalDeviceCustomBorderColorPropertiesEXT): return "ePhysicalDeviceCustomBorderColorPropertiesEXT";
        case(StructureType::ePhysicalDeviceCustomBorderColorFeaturesEXT): return "ePhysicalDeviceCustomBorderColorFeaturesEXT";
        case(StructureType::ePipelineLibraryCreateInfoKHR): return "ePipelineLibraryCreateInfoKHR";
        case(StructureType::ePhysicalDevicePrivateDataFeaturesEXT): return "ePhysicalDevicePrivateDataFeaturesEXT";
        case(StructureType::eDevicePrivateDataCreateInfoEXT): return "eDevicePrivateDataCreateInfoEXT";
        case(StructureType::ePrivateDataSlotCreateInfoEXT): return "ePrivateDataSlotCreateInfoEXT";
        case(StructureType::ePhysicalDevicePipelineCreationCacheControlFeaturesEXT): return "ePhysicalDevicePipelineCreationCacheControlFeaturesEXT";
        case(StructureType::ePhysicalDeviceDiagnosticsConfigFeaturesNV): return "ePhysicalDeviceDiagnosticsConfigFeaturesNV";
        case(StructureType::eDeviceDiagnosticsConfigCreateInfoNV): return "eDeviceDiagnosticsConfigCreateInfoNV";
        case(StructureType::eReservedQCOM): return "eReservedQCOM";
        case(StructureType::ePhysicalDeviceFragmentDensityMap2FeaturesEXT): return "ePhysicalDeviceFragmentDensityMap2FeaturesEXT";
        case(StructureType::ePhysicalDeviceFragmentDensityMap2PropertiesEXT): return "ePhysicalDeviceFragmentDensityMap2PropertiesEXT";
        case(StructureType::ePhysicalDeviceImageRobustnessFeaturesEXT): return "ePhysicalDeviceImageRobustnessFeaturesEXT";
        case(StructureType::ePhysicalDevice4444FormatsFeaturesEXT): return "ePhysicalDevice4444FormatsFeaturesEXT";
        case(StructureType::eDirectfbSurfaceCreateInfoEXT): return "eDirectfbSurfaceCreateInfoEXT";
        case(StructureType::ePhysicalDeviceSubgroupProperties): return "ePhysicalDeviceSubgroupProperties";
        case(StructureType::eBindBufferMemoryInfo): return "eBindBufferMemoryInfo";
        case(StructureType::eBindImageMemoryInfo): return "eBindImageMemoryInfo";
        case(StructureType::ePhysicalDevice16BitStorageFeatures): return "ePhysicalDevice16BitStorageFeatures";
        case(StructureType::eMemoryDedicatedRequirements): return "eMemoryDedicatedRequirements";
        case(StructureType::eMemoryDedicatedAllocateInfo): return "eMemoryDedicatedAllocateInfo";
        case(StructureType::eMemoryAllocateFlagsInfo): return "eMemoryAllocateFlagsInfo";
        case(StructureType::eDeviceGroupRenderPassBeginInfo): return "eDeviceGroupRenderPassBeginInfo";
        case(StructureType::eDeviceGroupCommandBufferBeginInfo): return "eDeviceGroupCommandBufferBeginInfo";
        case(StructureType::eDeviceGroupSubmitInfo): return "eDeviceGroupSubmitInfo";
        case(StructureType::eDeviceGroupBindSparseInfo): return "eDeviceGroupBindSparseInfo";
        case(StructureType::eBindBufferMemoryDeviceGroupInfo): return "eBindBufferMemoryDeviceGroupInfo";
        case(StructureType::eBindImageMemoryDeviceGroupInfo): return "eBindImageMemoryDeviceGroupInfo";
        case(StructureType::ePhysicalDeviceGroupProperties): return "ePhysicalDeviceGroupProperties";
        case(StructureType::eDeviceGroupDeviceCreateInfo): return "eDeviceGroupDeviceCreateInfo";
        case(StructureType::eBufferMemoryRequirementsInfo2): return "eBufferMemoryRequirementsInfo2";
        case(StructureType::eImageMemoryRequirementsInfo2): return "eImageMemoryRequirementsInfo2";
        case(StructureType::eImageSparseMemoryRequirementsInfo2): return "eImageSparseMemoryRequirementsInfo2";
        case(StructureType::eMemoryRequirements2): return "eMemoryRequirements2";
        case(StructureType::eSparseImageMemoryRequirements2): return "eSparseImageMemoryRequirements2";
        case(StructureType::ePhysicalDeviceFeatures2): return "ePhysicalDeviceFeatures2";
        case(StructureType::ePhysicalDeviceProperties2): return "ePhysicalDeviceProperties2";
        case(StructureType::eFormatProperties2): return "eFormatProperties2";
        case(StructureType::eImageFormatProperties2): return "eImageFormatProperties2";
        case(StructureType::ePhysicalDeviceImageFormatInfo2): return "ePhysicalDeviceImageFormatInfo2";
        case(StructureType::eQueueFamilyProperties2): return "eQueueFamilyProperties2";
        case(StructureType::ePhysicalDeviceMemoryProperties2): return "ePhysicalDeviceMemoryProperties2";
        case(StructureType::eSparseImageFormatProperties2): return "eSparseImageFormatProperties2";
        case(StructureType::ePhysicalDeviceSparseImageFormatInfo2): return "ePhysicalDeviceSparseImageFormatInfo2";
        case(StructureType::ePhysicalDevicePointClippingProperties): return "ePhysicalDevicePointClippingProperties";
        case(StructureType::eRenderPassInputAttachmentAspectCreateInfo): return "eRenderPassInputAttachmentAspectCreateInfo";
        case(StructureType::eImageViewUsageCreateInfo): return "eImageViewUsageCreateInfo";
        case(StructureType::ePipelineTessellationDomainOriginStateCreateInfo): return "ePipelineTessellationDomainOriginStateCreateInfo";
        case(StructureType::eRenderPassMultiviewCreateInfo): return "eRenderPassMultiviewCreateInfo";
        case(StructureType::ePhysicalDeviceMultiviewFeatures): return "ePhysicalDeviceMultiviewFeatures";
        case(StructureType::ePhysicalDeviceMultiviewProperties): return "ePhysicalDeviceMultiviewProperties";
        case(StructureType::ePhysicalDeviceVariablePointersFeatures): return "ePhysicalDeviceVariablePointersFeatures";
        case(StructureType::eProtectedSubmitInfo): return "eProtectedSubmitInfo";
        case(StructureType::ePhysicalDeviceProtectedMemoryFeatures): return "ePhysicalDeviceProtectedMemoryFeatures";
        case(StructureType::ePhysicalDeviceProtectedMemoryProperties): return "ePhysicalDeviceProtectedMemoryProperties";
        case(StructureType::eDeviceQueueInfo2): return "eDeviceQueueInfo2";
        case(StructureType::eSamplerYcbcrConversionCreateInfo): return "eSamplerYcbcrConversionCreateInfo";
        case(StructureType::eSamplerYcbcrConversionInfo): return "eSamplerYcbcrConversionInfo";
        case(StructureType::eBindImagePlaneMemoryInfo): return "eBindImagePlaneMemoryInfo";
        case(StructureType::eImagePlaneMemoryRequirementsInfo): return "eImagePlaneMemoryRequirementsInfo";
        case(StructureType::ePhysicalDeviceSamplerYcbcrConversionFeatures): return "ePhysicalDeviceSamplerYcbcrConversionFeatures";
        case(StructureType::eSamplerYcbcrConversionImageFormatProperties): return "eSamplerYcbcrConversionImageFormatProperties";
        case(StructureType::eDescriptorUpdateTemplateCreateInfo): return "eDescriptorUpdateTemplateCreateInfo";
        case(StructureType::ePhysicalDeviceExternalImageFormatInfo): return "ePhysicalDeviceExternalImageFormatInfo";
        case(StructureType::eExternalImageFormatProperties): return "eExternalImageFormatProperties";
        case(StructureType::ePhysicalDeviceExternalBufferInfo): return "ePhysicalDeviceExternalBufferInfo";
        case(StructureType::eExternalBufferProperties): return "eExternalBufferProperties";
        case(StructureType::ePhysicalDeviceIdProperties): return "ePhysicalDeviceIdProperties";
        case(StructureType::eExternalMemoryBufferCreateInfo): return "eExternalMemoryBufferCreateInfo";
        case(StructureType::eExternalMemoryImageCreateInfo): return "eExternalMemoryImageCreateInfo";
        case(StructureType::eExportMemoryAllocateInfo): return "eExportMemoryAllocateInfo";
        case(StructureType::ePhysicalDeviceExternalFenceInfo): return "ePhysicalDeviceExternalFenceInfo";
        case(StructureType::eExternalFenceProperties): return "eExternalFenceProperties";
        case(StructureType::eExportFenceCreateInfo): return "eExportFenceCreateInfo";
        case(StructureType::eExportSemaphoreCreateInfo): return "eExportSemaphoreCreateInfo";
        case(StructureType::ePhysicalDeviceExternalSemaphoreInfo): return "ePhysicalDeviceExternalSemaphoreInfo";
        case(StructureType::eExternalSemaphoreProperties): return "eExternalSemaphoreProperties";
        case(StructureType::ePhysicalDeviceMaintenance3Properties): return "ePhysicalDeviceMaintenance3Properties";
        case(StructureType::eDescriptorSetLayoutSupport): return "eDescriptorSetLayoutSupport";
        case(StructureType::ePhysicalDeviceShaderDrawParametersFeatures): return "ePhysicalDeviceShaderDrawParametersFeatures";
        case(StructureType::ePhysicalDeviceVulkan11Features): return "ePhysicalDeviceVulkan11Features";
        case(StructureType::ePhysicalDeviceVulkan11Properties): return "ePhysicalDeviceVulkan11Properties";
        case(StructureType::ePhysicalDeviceVulkan12Features): return "ePhysicalDeviceVulkan12Features";
        case(StructureType::ePhysicalDeviceVulkan12Properties): return "ePhysicalDeviceVulkan12Properties";
        case(StructureType::eImageFormatListCreateInfo): return "eImageFormatListCreateInfo";
        case(StructureType::eAttachmentDescription2): return "eAttachmentDescription2";
        case(StructureType::eAttachmentReference2): return "eAttachmentReference2";
        case(StructureType::eSubpassDescription2): return "eSubpassDescription2";
        case(StructureType::eSubpassDependency2): return "eSubpassDependency2";
        case(StructureType::eRenderPassCreateInfo2): return "eRenderPassCreateInfo2";
        case(StructureType::eSubpassBeginInfo): return "eSubpassBeginInfo";
        case(StructureType::eSubpassEndInfo): return "eSubpassEndInfo";
        case(StructureType::ePhysicalDevice8BitStorageFeatures): return "ePhysicalDevice8BitStorageFeatures";
        case(StructureType::ePhysicalDeviceDriverProperties): return "ePhysicalDeviceDriverProperties";
        case(StructureType::ePhysicalDeviceShaderAtomicInt64Features): return "ePhysicalDeviceShaderAtomicInt64Features";
        case(StructureType::ePhysicalDeviceShaderFloat16Int8Features): return "ePhysicalDeviceShaderFloat16Int8Features";
        case(StructureType::ePhysicalDeviceFloatControlsProperties): return "ePhysicalDeviceFloatControlsProperties";
        case(StructureType::eDescriptorSetLayoutBindingFlagsCreateInfo): return "eDescriptorSetLayoutBindingFlagsCreateInfo";
        case(StructureType::ePhysicalDeviceDescriptorIndexingFeatures): return "ePhysicalDeviceDescriptorIndexingFeatures";
        case(StructureType::ePhysicalDeviceDescriptorIndexingProperties): return "ePhysicalDeviceDescriptorIndexingProperties";
        case(StructureType::eDescriptorSetVariableDescriptorCountAllocateInfo): return "eDescriptorSetVariableDescriptorCountAllocateInfo";
        case(StructureType::eDescriptorSetVariableDescriptorCountLayoutSupport): return "eDescriptorSetVariableDescriptorCountLayoutSupport";
        case(StructureType::ePhysicalDeviceDepthStencilResolveProperties): return "ePhysicalDeviceDepthStencilResolveProperties";
        case(StructureType::eSubpassDescriptionDepthStencilResolve): return "eSubpassDescriptionDepthStencilResolve";
        case(StructureType::ePhysicalDeviceScalarBlockLayoutFeatures): return "ePhysicalDeviceScalarBlockLayoutFeatures";
        case(StructureType::eImageStencilUsageCreateInfo): return "eImageStencilUsageCreateInfo";
        case(StructureType::ePhysicalDeviceSamplerFilterMinmaxProperties): return "ePhysicalDeviceSamplerFilterMinmaxProperties";
        case(StructureType::eSamplerReductionModeCreateInfo): return "eSamplerReductionModeCreateInfo";
        case(StructureType::ePhysicalDeviceVulkanMemoryModelFeatures): return "ePhysicalDeviceVulkanMemoryModelFeatures";
        case(StructureType::ePhysicalDeviceImagelessFramebufferFeatures): return "ePhysicalDeviceImagelessFramebufferFeatures";
        case(StructureType::eFramebufferAttachmentsCreateInfo): return "eFramebufferAttachmentsCreateInfo";
        case(StructureType::eFramebufferAttachmentImageInfo): return "eFramebufferAttachmentImageInfo";
        case(StructureType::eRenderPassAttachmentBeginInfo): return "eRenderPassAttachmentBeginInfo";
        case(StructureType::ePhysicalDeviceUniformBufferStandardLayoutFeatures): return "ePhysicalDeviceUniformBufferStandardLayoutFeatures";
        case(StructureType::ePhysicalDeviceShaderSubgroupExtendedTypesFeatures): return "ePhysicalDeviceShaderSubgroupExtendedTypesFeatures";
        case(StructureType::ePhysicalDeviceSeparateDepthStencilLayoutsFeatures): return "ePhysicalDeviceSeparateDepthStencilLayoutsFeatures";
        case(StructureType::eAttachmentReferenceStencilLayout): return "eAttachmentReferenceStencilLayout";
        case(StructureType::eAttachmentDescriptionStencilLayout): return "eAttachmentDescriptionStencilLayout";
        case(StructureType::ePhysicalDeviceHostQueryResetFeatures): return "ePhysicalDeviceHostQueryResetFeatures";
        case(StructureType::ePhysicalDeviceTimelineSemaphoreFeatures): return "ePhysicalDeviceTimelineSemaphoreFeatures";
        case(StructureType::ePhysicalDeviceTimelineSemaphoreProperties): return "ePhysicalDeviceTimelineSemaphoreProperties";
        case(StructureType::eSemaphoreTypeCreateInfo): return "eSemaphoreTypeCreateInfo";
        case(StructureType::eTimelineSemaphoreSubmitInfo): return "eTimelineSemaphoreSubmitInfo";
        case(StructureType::eSemaphoreWaitInfo): return "eSemaphoreWaitInfo";
        case(StructureType::eSemaphoreSignalInfo): return "eSemaphoreSignalInfo";
        case(StructureType::ePhysicalDeviceBufferDeviceAddressFeatures): return "ePhysicalDeviceBufferDeviceAddressFeatures";
        case(StructureType::eBufferDeviceAddressInfo): return "eBufferDeviceAddressInfo";
        case(StructureType::eBufferOpaqueCaptureAddressCreateInfo): return "eBufferOpaqueCaptureAddressCreateInfo";
        case(StructureType::eMemoryOpaqueCaptureAddressAllocateInfo): return "eMemoryOpaqueCaptureAddressAllocateInfo";
        case(StructureType::eDeviceMemoryOpaqueCaptureAddressInfo): return "eDeviceMemoryOpaqueCaptureAddressInfo";
        default: return "UNKNOWN";
    }
}
const char * to_string(SystemAllocationScope val) {
    switch(val) {
        case(SystemAllocationScope::eCommand): return "eCommand";
        case(SystemAllocationScope::eObject): return "eObject";
        case(SystemAllocationScope::eCache): return "eCache";
        case(SystemAllocationScope::eDevice): return "eDevice";
        case(SystemAllocationScope::eInstance): return "eInstance";
        default: return "UNKNOWN";
    }
}
const char * to_string(InternalAllocationType val) {
    switch(val) {
        case(InternalAllocationType::eExecutable): return "eExecutable";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerAddressMode val) {
    switch(val) {
        case(SamplerAddressMode::eRepeat): return "eRepeat";
        case(SamplerAddressMode::eMirroredRepeat): return "eMirroredRepeat";
        case(SamplerAddressMode::eClampToEdge): return "eClampToEdge";
        case(SamplerAddressMode::eClampToBorder): return "eClampToBorder";
        case(SamplerAddressMode::eMirrorClampToEdge): return "eMirrorClampToEdge";
        default: return "UNKNOWN";
    }
}
const char * to_string(Filter val) {
    switch(val) {
        case(Filter::eNearest): return "eNearest";
        case(Filter::eLinear): return "eLinear";
        case(Filter::eCubicIMG): return "eCubicIMG";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerMipmapMode val) {
    switch(val) {
        case(SamplerMipmapMode::eNearest): return "eNearest";
        case(SamplerMipmapMode::eLinear): return "eLinear";
        default: return "UNKNOWN";
    }
}
const char * to_string(VertexInputRate val) {
    switch(val) {
        case(VertexInputRate::eVertex): return "eVertex";
        case(VertexInputRate::eInstance): return "eInstance";
        default: return "UNKNOWN";
    }
}
const char * to_string(ObjectType val) {
    switch(val) {
        case(ObjectType::eUnknown): return "eUnknown";
        case(ObjectType::eInstance): return "eInstance";
        case(ObjectType::ePhysicalDevice): return "ePhysicalDevice";
        case(ObjectType::eDevice): return "eDevice";
        case(ObjectType::eQueue): return "eQueue";
        case(ObjectType::eSemaphore): return "eSemaphore";
        case(ObjectType::eCommandBuffer): return "eCommandBuffer";
        case(ObjectType::eFence): return "eFence";
        case(ObjectType::eDeviceMemory): return "eDeviceMemory";
        case(ObjectType::eBuffer): return "eBuffer";
        case(ObjectType::eImage): return "eImage";
        case(ObjectType::eEvent): return "eEvent";
        case(ObjectType::eQueryPool): return "eQueryPool";
        case(ObjectType::eBufferView): return "eBufferView";
        case(ObjectType::eImageView): return "eImageView";
        case(ObjectType::eShaderModule): return "eShaderModule";
        case(ObjectType::ePipelineCache): return "ePipelineCache";
        case(ObjectType::ePipelineLayout): return "ePipelineLayout";
        case(ObjectType::eRenderPass): return "eRenderPass";
        case(ObjectType::ePipeline): return "ePipeline";
        case(ObjectType::eDescriptorSetLayout): return "eDescriptorSetLayout";
        case(ObjectType::eSampler): return "eSampler";
        case(ObjectType::eDescriptorPool): return "eDescriptorPool";
        case(ObjectType::eDescriptorSet): return "eDescriptorSet";
        case(ObjectType::eFramebuffer): return "eFramebuffer";
        case(ObjectType::eCommandPool): return "eCommandPool";
        case(ObjectType::eSurfaceKHR): return "eSurfaceKHR";
        case(ObjectType::eSwapchainKHR): return "eSwapchainKHR";
        case(ObjectType::eDisplayKHR): return "eDisplayKHR";
        case(ObjectType::eDisplayModeKHR): return "eDisplayModeKHR";
        case(ObjectType::eDebugReportCallbackEXT): return "eDebugReportCallbackEXT";
        case(ObjectType::eDebugUtilsMessengerEXT): return "eDebugUtilsMessengerEXT";
        case(ObjectType::eAccelerationStructureKHR): return "eAccelerationStructureKHR";
        case(ObjectType::eValidationCacheEXT): return "eValidationCacheEXT";
        case(ObjectType::ePerformanceConfigurationINTEL): return "ePerformanceConfigurationINTEL";
        case(ObjectType::eDeferredOperationKHR): return "eDeferredOperationKHR";
        case(ObjectType::eIndirectCommandsLayoutNV): return "eIndirectCommandsLayoutNV";
        case(ObjectType::ePrivateDataSlotEXT): return "ePrivateDataSlotEXT";
        case(ObjectType::eSamplerYcbcrConversion): return "eSamplerYcbcrConversion";
        case(ObjectType::eDescriptorUpdateTemplate): return "eDescriptorUpdateTemplate";
        default: return "UNKNOWN";
    }
}
const char * to_string(IndirectCommandsTokenTypeNV val) {
    switch(val) {
        case(IndirectCommandsTokenTypeNV::eShaderGroupNV): return "eShaderGroupNV";
        case(IndirectCommandsTokenTypeNV::eStateFlagsNV): return "eStateFlagsNV";
        case(IndirectCommandsTokenTypeNV::eIndexBufferNV): return "eIndexBufferNV";
        case(IndirectCommandsTokenTypeNV::eVertexBufferNV): return "eVertexBufferNV";
        case(IndirectCommandsTokenTypeNV::ePushConstantNV): return "ePushConstantNV";
        case(IndirectCommandsTokenTypeNV::eDrawIndexedNV): return "eDrawIndexedNV";
        case(IndirectCommandsTokenTypeNV::eDrawNV): return "eDrawNV";
        case(IndirectCommandsTokenTypeNV::eDrawTasksNV): return "eDrawTasksNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(DescriptorUpdateTemplateType val) {
    switch(val) {
        case(DescriptorUpdateTemplateType::eDescriptorSet): return "eDescriptorSet";
        case(DescriptorUpdateTemplateType::ePushDescriptorsKHR): return "ePushDescriptorsKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(ViewportCoordinateSwizzleNV val) {
    switch(val) {
        case(ViewportCoordinateSwizzleNV::ePositiveXNV): return "ePositiveXNV";
        case(ViewportCoordinateSwizzleNV::eNegativeXNV): return "eNegativeXNV";
        case(ViewportCoordinateSwizzleNV::ePositiveYNV): return "ePositiveYNV";
        case(ViewportCoordinateSwizzleNV::eNegativeYNV): return "eNegativeYNV";
        case(ViewportCoordinateSwizzleNV::ePositiveZNV): return "ePositiveZNV";
        case(ViewportCoordinateSwizzleNV::eNegativeZNV): return "eNegativeZNV";
        case(ViewportCoordinateSwizzleNV::ePositiveWNV): return "ePositiveWNV";
        case(ViewportCoordinateSwizzleNV::eNegativeWNV): return "eNegativeWNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(DiscardRectangleModeEXT val) {
    switch(val) {
        case(DiscardRectangleModeEXT::eInclusiveEXT): return "eInclusiveEXT";
        case(DiscardRectangleModeEXT::eExclusiveEXT): return "eExclusiveEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PointClippingBehavior val) {
    switch(val) {
        case(PointClippingBehavior::eAllClipPlanes): return "eAllClipPlanes";
        case(PointClippingBehavior::eUserClipPlanesOnly): return "eUserClipPlanesOnly";
        default: return "UNKNOWN";
    }
}
const char * to_string(CoverageModulationModeNV val) {
    switch(val) {
        case(CoverageModulationModeNV::eNoneNV): return "eNoneNV";
        case(CoverageModulationModeNV::eRgbNV): return "eRgbNV";
        case(CoverageModulationModeNV::eAlphaNV): return "eAlphaNV";
        case(CoverageModulationModeNV::eRgbaNV): return "eRgbaNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(CoverageReductionModeNV val) {
    switch(val) {
        case(CoverageReductionModeNV::eMergeNV): return "eMergeNV";
        case(CoverageReductionModeNV::eTruncateNV): return "eTruncateNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationCacheHeaderVersionEXT val) {
    switch(val) {
        case(ValidationCacheHeaderVersionEXT::eOneEXT): return "eOneEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ShaderInfoTypeAMD val) {
    switch(val) {
        case(ShaderInfoTypeAMD::eStatisticsAMD): return "eStatisticsAMD";
        case(ShaderInfoTypeAMD::eBinaryAMD): return "eBinaryAMD";
        case(ShaderInfoTypeAMD::eDisassemblyAMD): return "eDisassemblyAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueueGlobalPriorityEXT val) {
    switch(val) {
        case(QueueGlobalPriorityEXT::eLowEXT): return "eLowEXT";
        case(QueueGlobalPriorityEXT::eMediumEXT): return "eMediumEXT";
        case(QueueGlobalPriorityEXT::eHighEXT): return "eHighEXT";
        case(QueueGlobalPriorityEXT::eRealtimeEXT): return "eRealtimeEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(TimeDomainEXT val) {
    switch(val) {
        case(TimeDomainEXT::eDeviceEXT): return "eDeviceEXT";
        case(TimeDomainEXT::eClockMonotonicEXT): return "eClockMonotonicEXT";
        case(TimeDomainEXT::eClockMonotonicRawEXT): return "eClockMonotonicRawEXT";
        case(TimeDomainEXT::eQueryPerformanceCounterEXT): return "eQueryPerformanceCounterEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ConservativeRasterizationModeEXT val) {
    switch(val) {
        case(ConservativeRasterizationModeEXT::eDisabledEXT): return "eDisabledEXT";
        case(ConservativeRasterizationModeEXT::eOverestimateEXT): return "eOverestimateEXT";
        case(ConservativeRasterizationModeEXT::eUnderestimateEXT): return "eUnderestimateEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(SemaphoreType val) {
    switch(val) {
        case(SemaphoreType::eBinary): return "eBinary";
        case(SemaphoreType::eTimeline): return "eTimeline";
        default: return "UNKNOWN";
    }
}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(CopyAccelerationStructureModeKHR val) {
    switch(val) {
        case(CopyAccelerationStructureModeKHR::eCloneKHR): return "eCloneKHR";
        case(CopyAccelerationStructureModeKHR::eCompactKHR): return "eCompactKHR";
        case(CopyAccelerationStructureModeKHR::eSerializeKHR): return "eSerializeKHR";
        case(CopyAccelerationStructureModeKHR::eDeserializeKHR): return "eDeserializeKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureTypeKHR val) {
    switch(val) {
        case(AccelerationStructureTypeKHR::eTopLevelKHR): return "eTopLevelKHR";
        case(AccelerationStructureTypeKHR::eBottomLevelKHR): return "eBottomLevelKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryTypeKHR val) {
    switch(val) {
        case(GeometryTypeKHR::eTrianglesKHR): return "eTrianglesKHR";
        case(GeometryTypeKHR::eAabbsKHR): return "eAabbsKHR";
        case(GeometryTypeKHR::eInstancesKHR): return "eInstancesKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(RayTracingShaderGroupTypeKHR val) {
    switch(val) {
        case(RayTracingShaderGroupTypeKHR::eGeneralKHR): return "eGeneralKHR";
        case(RayTracingShaderGroupTypeKHR::eTrianglesHitGroupKHR): return "eTrianglesHitGroupKHR";
        case(RayTracingShaderGroupTypeKHR::eProceduralHitGroupKHR): return "eProceduralHitGroupKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureMemoryRequirementsTypeKHR val) {
    switch(val) {
        case(AccelerationStructureMemoryRequirementsTypeKHR::eObjectKHR): return "eObjectKHR";
        case(AccelerationStructureMemoryRequirementsTypeKHR::eBuildScratchKHR): return "eBuildScratchKHR";
        case(AccelerationStructureMemoryRequirementsTypeKHR::eUpdateScratchKHR): return "eUpdateScratchKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureBuildTypeKHR val) {
    switch(val) {
        case(AccelerationStructureBuildTypeKHR::eHostKHR): return "eHostKHR";
        case(AccelerationStructureBuildTypeKHR::eDeviceKHR): return "eDeviceKHR";
        case(AccelerationStructureBuildTypeKHR::eHostOrDeviceKHR): return "eHostOrDeviceKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
const char * to_string(MemoryOverallocationBehaviorAMD val) {
    switch(val) {
        case(MemoryOverallocationBehaviorAMD::eDefaultAMD): return "eDefaultAMD";
        case(MemoryOverallocationBehaviorAMD::eAllowedAMD): return "eAllowedAMD";
        case(MemoryOverallocationBehaviorAMD::eDisallowedAMD): return "eDisallowedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(ScopeNV val) {
    switch(val) {
        case(ScopeNV::eDeviceNV): return "eDeviceNV";
        case(ScopeNV::eWorkgroupNV): return "eWorkgroupNV";
        case(ScopeNV::eSubgroupNV): return "eSubgroupNV";
        case(ScopeNV::eQueueFamilyNV): return "eQueueFamilyNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(ComponentTypeNV val) {
    switch(val) {
        case(ComponentTypeNV::eFloat16NV): return "eFloat16NV";
        case(ComponentTypeNV::eFloat32NV): return "eFloat32NV";
        case(ComponentTypeNV::eFloat64NV): return "eFloat64NV";
        case(ComponentTypeNV::eSint8NV): return "eSint8NV";
        case(ComponentTypeNV::eSint16NV): return "eSint16NV";
        case(ComponentTypeNV::eSint32NV): return "eSint32NV";
        case(ComponentTypeNV::eSint64NV): return "eSint64NV";
        case(ComponentTypeNV::eUint8NV): return "eUint8NV";
        case(ComponentTypeNV::eUint16NV): return "eUint16NV";
        case(ComponentTypeNV::eUint32NV): return "eUint32NV";
        case(ComponentTypeNV::eUint64NV): return "eUint64NV";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterScopeKHR val) {
    switch(val) {
        case(PerformanceCounterScopeKHR::eCommandBufferKHR): return "eCommandBufferKHR";
        case(PerformanceCounterScopeKHR::eRenderPassKHR): return "eRenderPassKHR";
        case(PerformanceCounterScopeKHR::eCommandKHR): return "eCommandKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterUnitKHR val) {
    switch(val) {
        case(PerformanceCounterUnitKHR::eGenericKHR): return "eGenericKHR";
        case(PerformanceCounterUnitKHR::ePercentageKHR): return "ePercentageKHR";
        case(PerformanceCounterUnitKHR::eNanosecondsKHR): return "eNanosecondsKHR";
        case(PerformanceCounterUnitKHR::eBytesKHR): return "eBytesKHR";
        case(PerformanceCounterUnitKHR::eBytesPerSecondKHR): return "eBytesPerSecondKHR";
        case(PerformanceCounterUnitKHR::eKelvinKHR): return "eKelvinKHR";
        case(PerformanceCounterUnitKHR::eWattsKHR): return "eWattsKHR";
        case(PerformanceCounterUnitKHR::eVoltsKHR): return "eVoltsKHR";
        case(PerformanceCounterUnitKHR::eAmpsKHR): return "eAmpsKHR";
        case(PerformanceCounterUnitKHR::eHertzKHR): return "eHertzKHR";
        case(PerformanceCounterUnitKHR::eCyclesKHR): return "eCyclesKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterStorageKHR val) {
    switch(val) {
        case(PerformanceCounterStorageKHR::eInt32KHR): return "eInt32KHR";
        case(PerformanceCounterStorageKHR::eInt64KHR): return "eInt64KHR";
        case(PerformanceCounterStorageKHR::eUint32KHR): return "eUint32KHR";
        case(PerformanceCounterStorageKHR::eUint64KHR): return "eUint64KHR";
        case(PerformanceCounterStorageKHR::eFloat32KHR): return "eFloat32KHR";
        case(PerformanceCounterStorageKHR::eFloat64KHR): return "eFloat64KHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceConfigurationTypeINTEL val) {
    switch(val) {
        case(PerformanceConfigurationTypeINTEL::eCommandQueueMetricsDiscoveryActivatedINTEL): return "eCommandQueueMetricsDiscoveryActivatedINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueryPoolSamplingModeINTEL val) {
    switch(val) {
        case(QueryPoolSamplingModeINTEL::eManualINTEL): return "eManualINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceOverrideTypeINTEL val) {
    switch(val) {
        case(PerformanceOverrideTypeINTEL::eNullHardwareINTEL): return "eNullHardwareINTEL";
        case(PerformanceOverrideTypeINTEL::eFlushGpuCachesINTEL): return "eFlushGpuCachesINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceParameterTypeINTEL val) {
    switch(val) {
        case(PerformanceParameterTypeINTEL::eHwCountersSupportedINTEL): return "eHwCountersSupportedINTEL";
        case(PerformanceParameterTypeINTEL::eStreamMarkerValidBitsINTEL): return "eStreamMarkerValidBitsINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceValueTypeINTEL val) {
    switch(val) {
        case(PerformanceValueTypeINTEL::eUint32INTEL): return "eUint32INTEL";
        case(PerformanceValueTypeINTEL::eUint64INTEL): return "eUint64INTEL";
        case(PerformanceValueTypeINTEL::eFloatINTEL): return "eFloatINTEL";
        case(PerformanceValueTypeINTEL::eBoolINTEL): return "eBoolINTEL";
        case(PerformanceValueTypeINTEL::eStringINTEL): return "eStringINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(LineRasterizationModeEXT val) {
    switch(val) {
        case(LineRasterizationModeEXT::eDefaultEXT): return "eDefaultEXT";
        case(LineRasterizationModeEXT::eRectangularEXT): return "eRectangularEXT";
        case(LineRasterizationModeEXT::eBresenhamEXT): return "eBresenhamEXT";
        case(LineRasterizationModeEXT::eRectangularSmoothEXT): return "eRectangularSmoothEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ColorSpaceKHR val) {
    switch(val) {
        case(ColorSpaceKHR::eSrgbNonlinearKHR): return "eSrgbNonlinearKHR";
        case(ColorSpaceKHR::eDisplayP3NonlinearEXT): return "eDisplayP3NonlinearEXT";
        case(ColorSpaceKHR::eExtendedSrgbLinearEXT): return "eExtendedSrgbLinearEXT";
        case(ColorSpaceKHR::eDisplayP3LinearEXT): return "eDisplayP3LinearEXT";
        case(ColorSpaceKHR::eDciP3NonlinearEXT): return "eDciP3NonlinearEXT";
        case(ColorSpaceKHR::eBt709LinearEXT): return "eBt709LinearEXT";
        case(ColorSpaceKHR::eBt709NonlinearEXT): return "eBt709NonlinearEXT";
        case(ColorSpaceKHR::eBt2020LinearEXT): return "eBt2020LinearEXT";
        case(ColorSpaceKHR::eHdr10St2084EXT): return "eHdr10St2084EXT";
        case(ColorSpaceKHR::eDolbyvisionEXT): return "eDolbyvisionEXT";
        case(ColorSpaceKHR::eHdr10HlgEXT): return "eHdr10HlgEXT";
        case(ColorSpaceKHR::eAdobergbLinearEXT): return "eAdobergbLinearEXT";
        case(ColorSpaceKHR::eAdobergbNonlinearEXT): return "eAdobergbNonlinearEXT";
        case(ColorSpaceKHR::ePassThroughEXT): return "ePassThroughEXT";
        case(ColorSpaceKHR::eExtendedSrgbNonlinearEXT): return "eExtendedSrgbNonlinearEXT";
        case(ColorSpaceKHR::eDisplayNativeAMD): return "eDisplayNativeAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(PresentModeKHR val) {
    switch(val) {
        case(PresentModeKHR::eImmediateKHR): return "eImmediateKHR";
        case(PresentModeKHR::eMailboxKHR): return "eMailboxKHR";
        case(PresentModeKHR::eFifoKHR): return "eFifoKHR";
        case(PresentModeKHR::eFifoRelaxedKHR): return "eFifoRelaxedKHR";
        case(PresentModeKHR::eSharedDemandRefreshKHR): return "eSharedDemandRefreshKHR";
        case(PresentModeKHR::eSharedContinuousRefreshKHR): return "eSharedContinuousRefreshKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(DebugReportObjectTypeEXT val) {
    switch(val) {
        case(DebugReportObjectTypeEXT::eUnknownEXT): return "eUnknownEXT";
        case(DebugReportObjectTypeEXT::eInstanceEXT): return "eInstanceEXT";
        case(DebugReportObjectTypeEXT::ePhysicalDeviceEXT): return "ePhysicalDeviceEXT";
        case(DebugReportObjectTypeEXT::eDeviceEXT): return "eDeviceEXT";
        case(DebugReportObjectTypeEXT::eQueueEXT): return "eQueueEXT";
        case(DebugReportObjectTypeEXT::eSemaphoreEXT): return "eSemaphoreEXT";
        case(DebugReportObjectTypeEXT::eCommandBufferEXT): return "eCommandBufferEXT";
        case(DebugReportObjectTypeEXT::eFenceEXT): return "eFenceEXT";
        case(DebugReportObjectTypeEXT::eDeviceMemoryEXT): return "eDeviceMemoryEXT";
        case(DebugReportObjectTypeEXT::eBufferEXT): return "eBufferEXT";
        case(DebugReportObjectTypeEXT::eImageEXT): return "eImageEXT";
        case(DebugReportObjectTypeEXT::eEventEXT): return "eEventEXT";
        case(DebugReportObjectTypeEXT::eQueryPoolEXT): return "eQueryPoolEXT";
        case(DebugReportObjectTypeEXT::eBufferViewEXT): return "eBufferViewEXT";
        case(DebugReportObjectTypeEXT::eImageViewEXT): return "eImageViewEXT";
        case(DebugReportObjectTypeEXT::eShaderModuleEXT): return "eShaderModuleEXT";
        case(DebugReportObjectTypeEXT::ePipelineCacheEXT): return "ePipelineCacheEXT";
        case(DebugReportObjectTypeEXT::ePipelineLayoutEXT): return "ePipelineLayoutEXT";
        case(DebugReportObjectTypeEXT::eRenderPassEXT): return "eRenderPassEXT";
        case(DebugReportObjectTypeEXT::ePipelineEXT): return "ePipelineEXT";
        case(DebugReportObjectTypeEXT::eDescriptorSetLayoutEXT): return "eDescriptorSetLayoutEXT";
        case(DebugReportObjectTypeEXT::eSamplerEXT): return "eSamplerEXT";
        case(DebugReportObjectTypeEXT::eDescriptorPoolEXT): return "eDescriptorPoolEXT";
        case(DebugReportObjectTypeEXT::eDescriptorSetEXT): return "eDescriptorSetEXT";
        case(DebugReportObjectTypeEXT::eFramebufferEXT): return "eFramebufferEXT";
        case(DebugReportObjectTypeEXT::eCommandPoolEXT): return "eCommandPoolEXT";
        case(DebugReportObjectTypeEXT::eSurfaceKhrEXT): return "eSurfaceKhrEXT";
        case(DebugReportObjectTypeEXT::eSwapchainKhrEXT): return "eSwapchainKhrEXT";
        case(DebugReportObjectTypeEXT::eDebugReportCallbackExtEXT): return "eDebugReportCallbackExtEXT";
        case(DebugReportObjectTypeEXT::eDisplayKhrEXT): return "eDisplayKhrEXT";
        case(DebugReportObjectTypeEXT::eDisplayModeKhrEXT): return "eDisplayModeKhrEXT";
        case(DebugReportObjectTypeEXT::eValidationCacheExtEXT): return "eValidationCacheExtEXT";
        case(DebugReportObjectTypeEXT::eSamplerYcbcrConversionEXT): return "eSamplerYcbcrConversionEXT";
        case(DebugReportObjectTypeEXT::eDescriptorUpdateTemplateEXT): return "eDescriptorUpdateTemplateEXT";
        case(DebugReportObjectTypeEXT::eAccelerationStructureKhrEXT): return "eAccelerationStructureKhrEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(RasterizationOrderAMD val) {
    switch(val) {
        case(RasterizationOrderAMD::eStrictAMD): return "eStrictAMD";
        case(RasterizationOrderAMD::eRelaxedAMD): return "eRelaxedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationCheckEXT val) {
    switch(val) {
        case(ValidationCheckEXT::eAllEXT): return "eAllEXT";
        case(ValidationCheckEXT::eShadersEXT): return "eShadersEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationFeatureEnableEXT val) {
    switch(val) {
        case(ValidationFeatureEnableEXT::eGpuAssistedEXT): return "eGpuAssistedEXT";
        case(ValidationFeatureEnableEXT::eGpuAssistedReserveBindingSlotEXT): return "eGpuAssistedReserveBindingSlotEXT";
        case(ValidationFeatureEnableEXT::eBestPracticesEXT): return "eBestPracticesEXT";
        case(ValidationFeatureEnableEXT::eDebugPrintfEXT): return "eDebugPrintfEXT";
        case(ValidationFeatureEnableEXT::eSynchronizationValidationEXT): return "eSynchronizationValidationEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationFeatureDisableEXT val) {
    switch(val) {
        case(ValidationFeatureDisableEXT::eAllEXT): return "eAllEXT";
        case(ValidationFeatureDisableEXT::eShadersEXT): return "eShadersEXT";
        case(ValidationFeatureDisableEXT::eThreadSafetyEXT): return "eThreadSafetyEXT";
        case(ValidationFeatureDisableEXT::eApiParametersEXT): return "eApiParametersEXT";
        case(ValidationFeatureDisableEXT::eObjectLifetimesEXT): return "eObjectLifetimesEXT";
        case(ValidationFeatureDisableEXT::eCoreChecksEXT): return "eCoreChecksEXT";
        case(ValidationFeatureDisableEXT::eUniqueHandlesEXT): return "eUniqueHandlesEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DisplayPowerStateEXT val) {
    switch(val) {
        case(DisplayPowerStateEXT::eOffEXT): return "eOffEXT";
        case(DisplayPowerStateEXT::eSuspendEXT): return "eSuspendEXT";
        case(DisplayPowerStateEXT::eOnEXT): return "eOnEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DeviceEventTypeEXT val) {
    switch(val) {
        case(DeviceEventTypeEXT::eDisplayHotplugEXT): return "eDisplayHotplugEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DisplayEventTypeEXT val) {
    switch(val) {
        case(DisplayEventTypeEXT::eFirstPixelOutEXT): return "eFirstPixelOutEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(TessellationDomainOrigin val) {
    switch(val) {
        case(TessellationDomainOrigin::eUpperLeft): return "eUpperLeft";
        case(TessellationDomainOrigin::eLowerLeft): return "eLowerLeft";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerYcbcrModelConversion val) {
    switch(val) {
        case(SamplerYcbcrModelConversion::eRgbIdentity): return "eRgbIdentity";
        case(SamplerYcbcrModelConversion::eYcbcrIdentity): return "eYcbcrIdentity";
        case(SamplerYcbcrModelConversion::eYcbcr709): return "eYcbcr709";
        case(SamplerYcbcrModelConversion::eYcbcr601): return "eYcbcr601";
        case(SamplerYcbcrModelConversion::eYcbcr2020): return "eYcbcr2020";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerYcbcrRange val) {
    switch(val) {
        case(SamplerYcbcrRange::eItuFull): return "eItuFull";
        case(SamplerYcbcrRange::eItuNarrow): return "eItuNarrow";
        default: return "UNKNOWN";
    }
}
const char * to_string(ChromaLocation val) {
    switch(val) {
        case(ChromaLocation::eCositedEven): return "eCositedEven";
        case(ChromaLocation::eMidpoint): return "eMidpoint";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerReductionMode val) {
    switch(val) {
        case(SamplerReductionMode::eWeightedAverage): return "eWeightedAverage";
        case(SamplerReductionMode::eMin): return "eMin";
        case(SamplerReductionMode::eMax): return "eMax";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendOverlapEXT val) {
    switch(val) {
        case(BlendOverlapEXT::eUncorrelatedEXT): return "eUncorrelatedEXT";
        case(BlendOverlapEXT::eDisjointEXT): return "eDisjointEXT";
        case(BlendOverlapEXT::eConjointEXT): return "eConjointEXT";
        default: return "UNKNOWN";
    }
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(FullScreenExclusiveEXT val) {
    switch(val) {
        case(FullScreenExclusiveEXT::eDefaultEXT): return "eDefaultEXT";
        case(FullScreenExclusiveEXT::eAllowedEXT): return "eAllowedEXT";
        case(FullScreenExclusiveEXT::eDisallowedEXT): return "eDisallowedEXT";
        case(FullScreenExclusiveEXT::eApplicationControlledEXT): return "eApplicationControlledEXT";
        default: return "UNKNOWN";
    }
}
#endif // VK_USE_PLATFORM_WIN32_KHR
const char * to_string(ShaderFloatControlsIndependence val) {
    switch(val) {
        case(ShaderFloatControlsIndependence::e32BitOnly): return "e32BitOnly";
        case(ShaderFloatControlsIndependence::eAll): return "eAll";
        case(ShaderFloatControlsIndependence::eNone): return "eNone";
        default: return "UNKNOWN";
    }
}
const char * to_string(VendorId val) {
    switch(val) {
        case(VendorId::eVIV): return "eVIV";
        case(VendorId::eVSI): return "eVSI";
        case(VendorId::eKazan): return "eKazan";
        case(VendorId::eCodeplay): return "eCodeplay";
        case(VendorId::eMESA): return "eMESA";
        default: return "UNKNOWN";
    }
}
const char * to_string(DriverId val) {
    switch(val) {
        case(DriverId::eAmdProprietary): return "eAmdProprietary";
        case(DriverId::eAmdOpenSource): return "eAmdOpenSource";
        case(DriverId::eMesaRadv): return "eMesaRadv";
        case(DriverId::eNvidiaProprietary): return "eNvidiaProprietary";
        case(DriverId::eIntelProprietaryWindows): return "eIntelProprietaryWindows";
        case(DriverId::eIntelOpenSourceMESA): return "eIntelOpenSourceMESA";
        case(DriverId::eImaginationProprietary): return "eImaginationProprietary";
        case(DriverId::eQualcommProprietary): return "eQualcommProprietary";
        case(DriverId::eArmProprietary): return "eArmProprietary";
        case(DriverId::eGoogleSwiftshader): return "eGoogleSwiftshader";
        case(DriverId::eGgpProprietary): return "eGgpProprietary";
        case(DriverId::eBroadcomProprietary): return "eBroadcomProprietary";
        case(DriverId::eMesaLlvmpipe): return "eMesaLlvmpipe";
        case(DriverId::eMoltenvk): return "eMoltenvk";
        default: return "UNKNOWN";
    }
}
const char * to_string(ShadingRatePaletteEntryNV val) {
    switch(val) {
        case(ShadingRatePaletteEntryNV::eNoInvocationsNV): return "eNoInvocationsNV";
        case(ShadingRatePaletteEntryNV::e16InvocationsPerPixelNV): return "e16InvocationsPerPixelNV";
        case(ShadingRatePaletteEntryNV::e8InvocationsPerPixelNV): return "e8InvocationsPerPixelNV";
        case(ShadingRatePaletteEntryNV::e4InvocationsPerPixelNV): return "e4InvocationsPerPixelNV";
        case(ShadingRatePaletteEntryNV::e2InvocationsPerPixelNV): return "e2InvocationsPerPixelNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPerPixelNV): return "e1InvocationPerPixelNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer2X1PixelsNV): return "e1InvocationPer2X1PixelsNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer1X2PixelsNV): return "e1InvocationPer1X2PixelsNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer2X2PixelsNV): return "e1InvocationPer2X2PixelsNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer4X2PixelsNV): return "e1InvocationPer4X2PixelsNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer2X4PixelsNV): return "e1InvocationPer2X4PixelsNV";
        case(ShadingRatePaletteEntryNV::e1InvocationPer4X4PixelsNV): return "e1InvocationPer4X4PixelsNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(CoarseSampleOrderTypeNV val) {
    switch(val) {
        case(CoarseSampleOrderTypeNV::eDefaultNV): return "eDefaultNV";
        case(CoarseSampleOrderTypeNV::eCustomNV): return "eCustomNV";
        case(CoarseSampleOrderTypeNV::ePixelMajorNV): return "ePixelMajorNV";
        case(CoarseSampleOrderTypeNV::eSampleMajorNV): return "eSampleMajorNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineExecutableStatisticFormatKHR val) {
    switch(val) {
        case(PipelineExecutableStatisticFormatKHR::eBool32KHR): return "eBool32KHR";
        case(PipelineExecutableStatisticFormatKHR::eInt64KHR): return "eInt64KHR";
        case(PipelineExecutableStatisticFormatKHR::eUint64KHR): return "eUint64KHR";
        case(PipelineExecutableStatisticFormatKHR::eFloat64KHR): return "eFloat64KHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineCacheCreateFlagBits val) {
    switch(val) {
        case(PipelineCacheCreateFlagBits::eExternallySynchronizedBitEXT): return "eExternallySynchronizedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCacheCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCacheCreateFlagBits::eExternallySynchronizedBitEXT) out += "eExternallySynchronizedBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CullModeFlagBits val) {
    switch(val) {
        case(CullModeFlagBits::eNone): return "eNone";
        case(CullModeFlagBits::eFront): return "eFront";
        case(CullModeFlagBits::eBack): return "eBack";
        default: return "UNKNOWN";
    }
}
std::string to_string(CullModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CullModeFlagBits::eNone) out += "eNone | ";
    if (flag & CullModeFlagBits::eFront) out += "eFront | ";
    if (flag & CullModeFlagBits::eBack) out += "eBack | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(QueueFlagBits val) {
    switch(val) {
        case(QueueFlagBits::eGraphics): return "eGraphics";
        case(QueueFlagBits::eCompute): return "eCompute";
        case(QueueFlagBits::eTransfer): return "eTransfer";
        case(QueueFlagBits::eSparseBinding): return "eSparseBinding";
        case(QueueFlagBits::eReserved6BitKHR): return "eReserved6BitKHR";
        case(QueueFlagBits::eReserved5BitKHR): return "eReserved5BitKHR";
        case(QueueFlagBits::eProtected): return "eProtected";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueueFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueueFlagBits::eGraphics) out += "eGraphics | ";
    if (flag & QueueFlagBits::eCompute) out += "eCompute | ";
    if (flag & QueueFlagBits::eTransfer) out += "eTransfer | ";
    if (flag & QueueFlagBits::eSparseBinding) out += "eSparseBinding | ";
    if (flag & QueueFlagBits::eReserved6BitKHR) out += "eReserved6BitKHR | ";
    if (flag & QueueFlagBits::eReserved5BitKHR) out += "eReserved5BitKHR | ";
    if (flag & QueueFlagBits::eProtected) out += "eProtected | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(RenderPassCreateFlagBits val) {
    switch(val) {
        case(RenderPassCreateFlagBits::eReserved0BitKHR): return "eReserved0BitKHR";
        case(RenderPassCreateFlagBits::eTransformBitQCOM): return "eTransformBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(RenderPassCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & RenderPassCreateFlagBits::eReserved0BitKHR) out += "eReserved0BitKHR | ";
    if (flag & RenderPassCreateFlagBits::eTransformBitQCOM) out += "eTransformBitQCOM | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DeviceQueueCreateFlagBits val) {
    switch(val) {
        case(DeviceQueueCreateFlagBits::eProtected): return "eProtected";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceQueueCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceQueueCreateFlagBits::eProtected) out += "eProtected | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(MemoryPropertyFlagBits val) {
    switch(val) {
        case(MemoryPropertyFlagBits::eDeviceLocal): return "eDeviceLocal";
        case(MemoryPropertyFlagBits::eHostVisible): return "eHostVisible";
        case(MemoryPropertyFlagBits::eHostCoherent): return "eHostCoherent";
        case(MemoryPropertyFlagBits::eHostCached): return "eHostCached";
        case(MemoryPropertyFlagBits::eLazilyAllocated): return "eLazilyAllocated";
        case(MemoryPropertyFlagBits::eDeviceCoherentBitAMD): return "eDeviceCoherentBitAMD";
        case(MemoryPropertyFlagBits::eDeviceUncachedBitAMD): return "eDeviceUncachedBitAMD";
        case(MemoryPropertyFlagBits::eProtected): return "eProtected";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryPropertyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryPropertyFlagBits::eDeviceLocal) out += "eDeviceLocal | ";
    if (flag & MemoryPropertyFlagBits::eHostVisible) out += "eHostVisible | ";
    if (flag & MemoryPropertyFlagBits::eHostCoherent) out += "eHostCoherent | ";
    if (flag & MemoryPropertyFlagBits::eHostCached) out += "eHostCached | ";
    if (flag & MemoryPropertyFlagBits::eLazilyAllocated) out += "eLazilyAllocated | ";
    if (flag & MemoryPropertyFlagBits::eDeviceCoherentBitAMD) out += "eDeviceCoherentBitAMD | ";
    if (flag & MemoryPropertyFlagBits::eDeviceUncachedBitAMD) out += "eDeviceUncachedBitAMD | ";
    if (flag & MemoryPropertyFlagBits::eProtected) out += "eProtected | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(MemoryHeapFlagBits val) {
    switch(val) {
        case(MemoryHeapFlagBits::eDeviceLocal): return "eDeviceLocal";
        case(MemoryHeapFlagBits::eReserved2BitKHR): return "eReserved2BitKHR";
        case(MemoryHeapFlagBits::eMultiInstance): return "eMultiInstance";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryHeapFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryHeapFlagBits::eDeviceLocal) out += "eDeviceLocal | ";
    if (flag & MemoryHeapFlagBits::eReserved2BitKHR) out += "eReserved2BitKHR | ";
    if (flag & MemoryHeapFlagBits::eMultiInstance) out += "eMultiInstance | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(AccessFlagBits val) {
    switch(val) {
        case(AccessFlagBits::eIndirectCommandRead): return "eIndirectCommandRead";
        case(AccessFlagBits::eIndexRead): return "eIndexRead";
        case(AccessFlagBits::eVertexAttributeRead): return "eVertexAttributeRead";
        case(AccessFlagBits::eUniformRead): return "eUniformRead";
        case(AccessFlagBits::eInputAttachmentRead): return "eInputAttachmentRead";
        case(AccessFlagBits::eShaderRead): return "eShaderRead";
        case(AccessFlagBits::eShaderWrite): return "eShaderWrite";
        case(AccessFlagBits::eColorAttachmentRead): return "eColorAttachmentRead";
        case(AccessFlagBits::eColorAttachmentWrite): return "eColorAttachmentWrite";
        case(AccessFlagBits::eDepthStencilAttachmentRead): return "eDepthStencilAttachmentRead";
        case(AccessFlagBits::eDepthStencilAttachmentWrite): return "eDepthStencilAttachmentWrite";
        case(AccessFlagBits::eTransferRead): return "eTransferRead";
        case(AccessFlagBits::eTransferWrite): return "eTransferWrite";
        case(AccessFlagBits::eHostRead): return "eHostRead";
        case(AccessFlagBits::eHostWrite): return "eHostWrite";
        case(AccessFlagBits::eMemoryRead): return "eMemoryRead";
        case(AccessFlagBits::eMemoryWrite): return "eMemoryWrite";
        case(AccessFlagBits::eReserved30BitKHR): return "eReserved30BitKHR";
        case(AccessFlagBits::eReserved28BitKHR): return "eReserved28BitKHR";
        case(AccessFlagBits::eReserved29BitKHR): return "eReserved29BitKHR";
        case(AccessFlagBits::eTransformFeedbackWriteBitEXT): return "eTransformFeedbackWriteBitEXT";
        case(AccessFlagBits::eTransformFeedbackCounterReadBitEXT): return "eTransformFeedbackCounterReadBitEXT";
        case(AccessFlagBits::eTransformFeedbackCounterWriteBitEXT): return "eTransformFeedbackCounterWriteBitEXT";
        case(AccessFlagBits::eConditionalRenderingReadBitEXT): return "eConditionalRenderingReadBitEXT";
        case(AccessFlagBits::eColorAttachmentReadNoncoherentBitEXT): return "eColorAttachmentReadNoncoherentBitEXT";
        case(AccessFlagBits::eAccelerationStructureReadBitKHR): return "eAccelerationStructureReadBitKHR";
        case(AccessFlagBits::eAccelerationStructureWriteBitKHR): return "eAccelerationStructureWriteBitKHR";
        case(AccessFlagBits::eShadingRateImageReadBitNV): return "eShadingRateImageReadBitNV";
        case(AccessFlagBits::eFragmentDensityMapReadBitEXT): return "eFragmentDensityMapReadBitEXT";
        case(AccessFlagBits::eCommandPreprocessReadBitNV): return "eCommandPreprocessReadBitNV";
        case(AccessFlagBits::eCommandPreprocessWriteBitNV): return "eCommandPreprocessWriteBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(AccessFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AccessFlagBits::eIndirectCommandRead) out += "eIndirectCommandRead | ";
    if (flag & AccessFlagBits::eIndexRead) out += "eIndexRead | ";
    if (flag & AccessFlagBits::eVertexAttributeRead) out += "eVertexAttributeRead | ";
    if (flag & AccessFlagBits::eUniformRead) out += "eUniformRead | ";
    if (flag & AccessFlagBits::eInputAttachmentRead) out += "eInputAttachmentRead | ";
    if (flag & AccessFlagBits::eShaderRead) out += "eShaderRead | ";
    if (flag & AccessFlagBits::eShaderWrite) out += "eShaderWrite | ";
    if (flag & AccessFlagBits::eColorAttachmentRead) out += "eColorAttachmentRead | ";
    if (flag & AccessFlagBits::eColorAttachmentWrite) out += "eColorAttachmentWrite | ";
    if (flag & AccessFlagBits::eDepthStencilAttachmentRead) out += "eDepthStencilAttachmentRead | ";
    if (flag & AccessFlagBits::eDepthStencilAttachmentWrite) out += "eDepthStencilAttachmentWrite | ";
    if (flag & AccessFlagBits::eTransferRead) out += "eTransferRead | ";
    if (flag & AccessFlagBits::eTransferWrite) out += "eTransferWrite | ";
    if (flag & AccessFlagBits::eHostRead) out += "eHostRead | ";
    if (flag & AccessFlagBits::eHostWrite) out += "eHostWrite | ";
    if (flag & AccessFlagBits::eMemoryRead) out += "eMemoryRead | ";
    if (flag & AccessFlagBits::eMemoryWrite) out += "eMemoryWrite | ";
    if (flag & AccessFlagBits::eReserved30BitKHR) out += "eReserved30BitKHR | ";
    if (flag & AccessFlagBits::eReserved28BitKHR) out += "eReserved28BitKHR | ";
    if (flag & AccessFlagBits::eReserved29BitKHR) out += "eReserved29BitKHR | ";
    if (flag & AccessFlagBits::eTransformFeedbackWriteBitEXT) out += "eTransformFeedbackWriteBitEXT | ";
    if (flag & AccessFlagBits::eTransformFeedbackCounterReadBitEXT) out += "eTransformFeedbackCounterReadBitEXT | ";
    if (flag & AccessFlagBits::eTransformFeedbackCounterWriteBitEXT) out += "eTransformFeedbackCounterWriteBitEXT | ";
    if (flag & AccessFlagBits::eConditionalRenderingReadBitEXT) out += "eConditionalRenderingReadBitEXT | ";
    if (flag & AccessFlagBits::eColorAttachmentReadNoncoherentBitEXT) out += "eColorAttachmentReadNoncoherentBitEXT | ";
    if (flag & AccessFlagBits::eAccelerationStructureReadBitKHR) out += "eAccelerationStructureReadBitKHR | ";
    if (flag & AccessFlagBits::eAccelerationStructureWriteBitKHR) out += "eAccelerationStructureWriteBitKHR | ";
    if (flag & AccessFlagBits::eShadingRateImageReadBitNV) out += "eShadingRateImageReadBitNV | ";
    if (flag & AccessFlagBits::eFragmentDensityMapReadBitEXT) out += "eFragmentDensityMapReadBitEXT | ";
    if (flag & AccessFlagBits::eCommandPreprocessReadBitNV) out += "eCommandPreprocessReadBitNV | ";
    if (flag & AccessFlagBits::eCommandPreprocessWriteBitNV) out += "eCommandPreprocessWriteBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(BufferUsageFlagBits val) {
    switch(val) {
        case(BufferUsageFlagBits::eTransferSrc): return "eTransferSrc";
        case(BufferUsageFlagBits::eTransferDst): return "eTransferDst";
        case(BufferUsageFlagBits::eUniformTexelBuffer): return "eUniformTexelBuffer";
        case(BufferUsageFlagBits::eStorageTexelBuffer): return "eStorageTexelBuffer";
        case(BufferUsageFlagBits::eUniformBuffer): return "eUniformBuffer";
        case(BufferUsageFlagBits::eStorageBuffer): return "eStorageBuffer";
        case(BufferUsageFlagBits::eIndexBuffer): return "eIndexBuffer";
        case(BufferUsageFlagBits::eVertexBuffer): return "eVertexBuffer";
        case(BufferUsageFlagBits::eIndirectBuffer): return "eIndirectBuffer";
        case(BufferUsageFlagBits::eReserved15BitKHR): return "eReserved15BitKHR";
        case(BufferUsageFlagBits::eReserved16BitKHR): return "eReserved16BitKHR";
        case(BufferUsageFlagBits::eReserved13BitKHR): return "eReserved13BitKHR";
        case(BufferUsageFlagBits::eReserved14BitKHR): return "eReserved14BitKHR";
        case(BufferUsageFlagBits::eTransformFeedbackBufferBitEXT): return "eTransformFeedbackBufferBitEXT";
        case(BufferUsageFlagBits::eTransformFeedbackCounterBufferBitEXT): return "eTransformFeedbackCounterBufferBitEXT";
        case(BufferUsageFlagBits::eConditionalRenderingBitEXT): return "eConditionalRenderingBitEXT";
        case(BufferUsageFlagBits::eRayTracingBitKHR): return "eRayTracingBitKHR";
        case(BufferUsageFlagBits::eReserved19BitKHR): return "eReserved19BitKHR";
        case(BufferUsageFlagBits::eReserved20BitKHR): return "eReserved20BitKHR";
        case(BufferUsageFlagBits::eReserved18BitQCOM): return "eReserved18BitQCOM";
        case(BufferUsageFlagBits::eShaderDeviceAddress): return "eShaderDeviceAddress";
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BufferUsageFlagBits::eTransferSrc) out += "eTransferSrc | ";
    if (flag & BufferUsageFlagBits::eTransferDst) out += "eTransferDst | ";
    if (flag & BufferUsageFlagBits::eUniformTexelBuffer) out += "eUniformTexelBuffer | ";
    if (flag & BufferUsageFlagBits::eStorageTexelBuffer) out += "eStorageTexelBuffer | ";
    if (flag & BufferUsageFlagBits::eUniformBuffer) out += "eUniformBuffer | ";
    if (flag & BufferUsageFlagBits::eStorageBuffer) out += "eStorageBuffer | ";
    if (flag & BufferUsageFlagBits::eIndexBuffer) out += "eIndexBuffer | ";
    if (flag & BufferUsageFlagBits::eVertexBuffer) out += "eVertexBuffer | ";
    if (flag & BufferUsageFlagBits::eIndirectBuffer) out += "eIndirectBuffer | ";
    if (flag & BufferUsageFlagBits::eReserved15BitKHR) out += "eReserved15BitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved16BitKHR) out += "eReserved16BitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved13BitKHR) out += "eReserved13BitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved14BitKHR) out += "eReserved14BitKHR | ";
    if (flag & BufferUsageFlagBits::eTransformFeedbackBufferBitEXT) out += "eTransformFeedbackBufferBitEXT | ";
    if (flag & BufferUsageFlagBits::eTransformFeedbackCounterBufferBitEXT) out += "eTransformFeedbackCounterBufferBitEXT | ";
    if (flag & BufferUsageFlagBits::eConditionalRenderingBitEXT) out += "eConditionalRenderingBitEXT | ";
    if (flag & BufferUsageFlagBits::eRayTracingBitKHR) out += "eRayTracingBitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved19BitKHR) out += "eReserved19BitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved20BitKHR) out += "eReserved20BitKHR | ";
    if (flag & BufferUsageFlagBits::eReserved18BitQCOM) out += "eReserved18BitQCOM | ";
    if (flag & BufferUsageFlagBits::eShaderDeviceAddress) out += "eShaderDeviceAddress | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(BufferCreateFlagBits val) {
    switch(val) {
        case(BufferCreateFlagBits::eSparseBinding): return "eSparseBinding";
        case(BufferCreateFlagBits::eSparseResidency): return "eSparseResidency";
        case(BufferCreateFlagBits::eSparseAliased): return "eSparseAliased";
        case(BufferCreateFlagBits::eProtected): return "eProtected";
        case(BufferCreateFlagBits::eDeviceAddressCaptureReplay): return "eDeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BufferCreateFlagBits::eSparseBinding) out += "eSparseBinding | ";
    if (flag & BufferCreateFlagBits::eSparseResidency) out += "eSparseResidency | ";
    if (flag & BufferCreateFlagBits::eSparseAliased) out += "eSparseAliased | ";
    if (flag & BufferCreateFlagBits::eProtected) out += "eProtected | ";
    if (flag & BufferCreateFlagBits::eDeviceAddressCaptureReplay) out += "eDeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ShaderStageFlagBits val) {
    switch(val) {
        case(ShaderStageFlagBits::eVertex): return "eVertex";
        case(ShaderStageFlagBits::eTessellationControl): return "eTessellationControl";
        case(ShaderStageFlagBits::eTessellationEvaluation): return "eTessellationEvaluation";
        case(ShaderStageFlagBits::eGeometry): return "eGeometry";
        case(ShaderStageFlagBits::eFragment): return "eFragment";
        case(ShaderStageFlagBits::eCompute): return "eCompute";
        case(ShaderStageFlagBits::eRaygenBitKHR): return "eRaygenBitKHR";
        case(ShaderStageFlagBits::eAnyHitBitKHR): return "eAnyHitBitKHR";
        case(ShaderStageFlagBits::eClosestHitBitKHR): return "eClosestHitBitKHR";
        case(ShaderStageFlagBits::eMissBitKHR): return "eMissBitKHR";
        case(ShaderStageFlagBits::eIntersectionBitKHR): return "eIntersectionBitKHR";
        case(ShaderStageFlagBits::eCallableBitKHR): return "eCallableBitKHR";
        case(ShaderStageFlagBits::eTaskBitNV): return "eTaskBitNV";
        case(ShaderStageFlagBits::eMeshBitNV): return "eMeshBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ShaderStageFlagBits::eVertex) out += "eVertex | ";
    if (flag & ShaderStageFlagBits::eTessellationControl) out += "eTessellationControl | ";
    if (flag & ShaderStageFlagBits::eTessellationEvaluation) out += "eTessellationEvaluation | ";
    if (flag & ShaderStageFlagBits::eGeometry) out += "eGeometry | ";
    if (flag & ShaderStageFlagBits::eFragment) out += "eFragment | ";
    if (flag & ShaderStageFlagBits::eCompute) out += "eCompute | ";
    if (flag & ShaderStageFlagBits::eRaygenBitKHR) out += "eRaygenBitKHR | ";
    if (flag & ShaderStageFlagBits::eAnyHitBitKHR) out += "eAnyHitBitKHR | ";
    if (flag & ShaderStageFlagBits::eClosestHitBitKHR) out += "eClosestHitBitKHR | ";
    if (flag & ShaderStageFlagBits::eMissBitKHR) out += "eMissBitKHR | ";
    if (flag & ShaderStageFlagBits::eIntersectionBitKHR) out += "eIntersectionBitKHR | ";
    if (flag & ShaderStageFlagBits::eCallableBitKHR) out += "eCallableBitKHR | ";
    if (flag & ShaderStageFlagBits::eTaskBitNV) out += "eTaskBitNV | ";
    if (flag & ShaderStageFlagBits::eMeshBitNV) out += "eMeshBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ImageUsageFlagBits val) {
    switch(val) {
        case(ImageUsageFlagBits::eTransferSrc): return "eTransferSrc";
        case(ImageUsageFlagBits::eTransferDst): return "eTransferDst";
        case(ImageUsageFlagBits::eSampled): return "eSampled";
        case(ImageUsageFlagBits::eStorage): return "eStorage";
        case(ImageUsageFlagBits::eColorAttachment): return "eColorAttachment";
        case(ImageUsageFlagBits::eDepthStencilAttachment): return "eDepthStencilAttachment";
        case(ImageUsageFlagBits::eTransientAttachment): return "eTransientAttachment";
        case(ImageUsageFlagBits::eInputAttachment): return "eInputAttachment";
        case(ImageUsageFlagBits::eReserved13BitKHR): return "eReserved13BitKHR";
        case(ImageUsageFlagBits::eReserved14BitKHR): return "eReserved14BitKHR";
        case(ImageUsageFlagBits::eReserved15BitKHR): return "eReserved15BitKHR";
        case(ImageUsageFlagBits::eReserved10BitKHR): return "eReserved10BitKHR";
        case(ImageUsageFlagBits::eReserved11BitKHR): return "eReserved11BitKHR";
        case(ImageUsageFlagBits::eReserved12BitKHR): return "eReserved12BitKHR";
        case(ImageUsageFlagBits::eShadingRateImageBitNV): return "eShadingRateImageBitNV";
        case(ImageUsageFlagBits::eReserved16BitQCOM): return "eReserved16BitQCOM";
        case(ImageUsageFlagBits::eReserved17BitQCOM): return "eReserved17BitQCOM";
        case(ImageUsageFlagBits::eFragmentDensityMapBitEXT): return "eFragmentDensityMapBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageUsageFlagBits::eTransferSrc) out += "eTransferSrc | ";
    if (flag & ImageUsageFlagBits::eTransferDst) out += "eTransferDst | ";
    if (flag & ImageUsageFlagBits::eSampled) out += "eSampled | ";
    if (flag & ImageUsageFlagBits::eStorage) out += "eStorage | ";
    if (flag & ImageUsageFlagBits::eColorAttachment) out += "eColorAttachment | ";
    if (flag & ImageUsageFlagBits::eDepthStencilAttachment) out += "eDepthStencilAttachment | ";
    if (flag & ImageUsageFlagBits::eTransientAttachment) out += "eTransientAttachment | ";
    if (flag & ImageUsageFlagBits::eInputAttachment) out += "eInputAttachment | ";
    if (flag & ImageUsageFlagBits::eReserved13BitKHR) out += "eReserved13BitKHR | ";
    if (flag & ImageUsageFlagBits::eReserved14BitKHR) out += "eReserved14BitKHR | ";
    if (flag & ImageUsageFlagBits::eReserved15BitKHR) out += "eReserved15BitKHR | ";
    if (flag & ImageUsageFlagBits::eReserved10BitKHR) out += "eReserved10BitKHR | ";
    if (flag & ImageUsageFlagBits::eReserved11BitKHR) out += "eReserved11BitKHR | ";
    if (flag & ImageUsageFlagBits::eReserved12BitKHR) out += "eReserved12BitKHR | ";
    if (flag & ImageUsageFlagBits::eShadingRateImageBitNV) out += "eShadingRateImageBitNV | ";
    if (flag & ImageUsageFlagBits::eReserved16BitQCOM) out += "eReserved16BitQCOM | ";
    if (flag & ImageUsageFlagBits::eReserved17BitQCOM) out += "eReserved17BitQCOM | ";
    if (flag & ImageUsageFlagBits::eFragmentDensityMapBitEXT) out += "eFragmentDensityMapBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ImageCreateFlagBits val) {
    switch(val) {
        case(ImageCreateFlagBits::eSparseBinding): return "eSparseBinding";
        case(ImageCreateFlagBits::eSparseResidency): return "eSparseResidency";
        case(ImageCreateFlagBits::eSparseAliased): return "eSparseAliased";
        case(ImageCreateFlagBits::eMutableFormat): return "eMutableFormat";
        case(ImageCreateFlagBits::eCubeCompatible): return "eCubeCompatible";
        case(ImageCreateFlagBits::eCornerSampledBitNV): return "eCornerSampledBitNV";
        case(ImageCreateFlagBits::eSampleLocationsCompatibleDepthBitEXT): return "eSampleLocationsCompatibleDepthBitEXT";
        case(ImageCreateFlagBits::eSubsampledBitEXT): return "eSubsampledBitEXT";
        case(ImageCreateFlagBits::eAlias): return "eAlias";
        case(ImageCreateFlagBits::eSplitInstanceBindRegions): return "eSplitInstanceBindRegions";
        case(ImageCreateFlagBits::e2DArrayCompatible): return "e2DArrayCompatible";
        case(ImageCreateFlagBits::eBlockTexelViewCompatible): return "eBlockTexelViewCompatible";
        case(ImageCreateFlagBits::eExtendedUsage): return "eExtendedUsage";
        case(ImageCreateFlagBits::eProtected): return "eProtected";
        case(ImageCreateFlagBits::eDisjoint): return "eDisjoint";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageCreateFlagBits::eSparseBinding) out += "eSparseBinding | ";
    if (flag & ImageCreateFlagBits::eSparseResidency) out += "eSparseResidency | ";
    if (flag & ImageCreateFlagBits::eSparseAliased) out += "eSparseAliased | ";
    if (flag & ImageCreateFlagBits::eMutableFormat) out += "eMutableFormat | ";
    if (flag & ImageCreateFlagBits::eCubeCompatible) out += "eCubeCompatible | ";
    if (flag & ImageCreateFlagBits::eCornerSampledBitNV) out += "eCornerSampledBitNV | ";
    if (flag & ImageCreateFlagBits::eSampleLocationsCompatibleDepthBitEXT) out += "eSampleLocationsCompatibleDepthBitEXT | ";
    if (flag & ImageCreateFlagBits::eSubsampledBitEXT) out += "eSubsampledBitEXT | ";
    if (flag & ImageCreateFlagBits::eAlias) out += "eAlias | ";
    if (flag & ImageCreateFlagBits::eSplitInstanceBindRegions) out += "eSplitInstanceBindRegions | ";
    if (flag & ImageCreateFlagBits::e2DArrayCompatible) out += "e2DArrayCompatible | ";
    if (flag & ImageCreateFlagBits::eBlockTexelViewCompatible) out += "eBlockTexelViewCompatible | ";
    if (flag & ImageCreateFlagBits::eExtendedUsage) out += "eExtendedUsage | ";
    if (flag & ImageCreateFlagBits::eProtected) out += "eProtected | ";
    if (flag & ImageCreateFlagBits::eDisjoint) out += "eDisjoint | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ImageViewCreateFlagBits val) {
    switch(val) {
        case(ImageViewCreateFlagBits::eFragmentDensityMapDynamicBitEXT): return "eFragmentDensityMapDynamicBitEXT";
        case(ImageViewCreateFlagBits::eFragmentDensityMapDeferredBitEXT): return "eFragmentDensityMapDeferredBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageViewCreateFlagBits::eFragmentDensityMapDynamicBitEXT) out += "eFragmentDensityMapDynamicBitEXT | ";
    if (flag & ImageViewCreateFlagBits::eFragmentDensityMapDeferredBitEXT) out += "eFragmentDensityMapDeferredBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SamplerCreateFlagBits val) {
    switch(val) {
        case(SamplerCreateFlagBits::eSubsampledBitEXT): return "eSubsampledBitEXT";
        case(SamplerCreateFlagBits::eSubsampledCoarseReconstructionBitEXT): return "eSubsampledCoarseReconstructionBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(SamplerCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SamplerCreateFlagBits::eSubsampledBitEXT) out += "eSubsampledBitEXT | ";
    if (flag & SamplerCreateFlagBits::eSubsampledCoarseReconstructionBitEXT) out += "eSubsampledCoarseReconstructionBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PipelineCreateFlagBits val) {
    switch(val) {
        case(PipelineCreateFlagBits::eDisableOptimization): return "eDisableOptimization";
        case(PipelineCreateFlagBits::eAllowDerivatives): return "eAllowDerivatives";
        case(PipelineCreateFlagBits::eDerivative): return "eDerivative";
        case(PipelineCreateFlagBits::eRayTracingNoNullAnyHitShadersBitKHR): return "eRayTracingNoNullAnyHitShadersBitKHR";
        case(PipelineCreateFlagBits::eRayTracingNoNullClosestHitShadersBitKHR): return "eRayTracingNoNullClosestHitShadersBitKHR";
        case(PipelineCreateFlagBits::eRayTracingNoNullMissShadersBitKHR): return "eRayTracingNoNullMissShadersBitKHR";
        case(PipelineCreateFlagBits::eRayTracingNoNullIntersectionShadersBitKHR): return "eRayTracingNoNullIntersectionShadersBitKHR";
        case(PipelineCreateFlagBits::eRayTracingSkipTrianglesBitKHR): return "eRayTracingSkipTrianglesBitKHR";
        case(PipelineCreateFlagBits::eRayTracingSkipAabbsBitKHR): return "eRayTracingSkipAabbsBitKHR";
        case(PipelineCreateFlagBits::eDeferCompileBitNV): return "eDeferCompileBitNV";
        case(PipelineCreateFlagBits::eReserved19BitKHR): return "eReserved19BitKHR";
        case(PipelineCreateFlagBits::eCaptureStatisticsBitKHR): return "eCaptureStatisticsBitKHR";
        case(PipelineCreateFlagBits::eCaptureInternalRepresentationsBitKHR): return "eCaptureInternalRepresentationsBitKHR";
        case(PipelineCreateFlagBits::eIndirectBindableBitNV): return "eIndirectBindableBitNV";
        case(PipelineCreateFlagBits::eLibraryBitKHR): return "eLibraryBitKHR";
        case(PipelineCreateFlagBits::eFailOnPipelineCompileRequiredBitEXT): return "eFailOnPipelineCompileRequiredBitEXT";
        case(PipelineCreateFlagBits::eEarlyReturnOnFailureBitEXT): return "eEarlyReturnOnFailureBitEXT";
        case(PipelineCreateFlagBits::eViewIndexFromDeviceIndex): return "eViewIndexFromDeviceIndex";
        case(PipelineCreateFlagBits::eDispatchBase): return "eDispatchBase";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCreateFlagBits::eDisableOptimization) out += "eDisableOptimization | ";
    if (flag & PipelineCreateFlagBits::eAllowDerivatives) out += "eAllowDerivatives | ";
    if (flag & PipelineCreateFlagBits::eDerivative) out += "eDerivative | ";
    if (flag & PipelineCreateFlagBits::eRayTracingNoNullAnyHitShadersBitKHR) out += "eRayTracingNoNullAnyHitShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::eRayTracingNoNullClosestHitShadersBitKHR) out += "eRayTracingNoNullClosestHitShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::eRayTracingNoNullMissShadersBitKHR) out += "eRayTracingNoNullMissShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::eRayTracingNoNullIntersectionShadersBitKHR) out += "eRayTracingNoNullIntersectionShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::eRayTracingSkipTrianglesBitKHR) out += "eRayTracingSkipTrianglesBitKHR | ";
    if (flag & PipelineCreateFlagBits::eRayTracingSkipAabbsBitKHR) out += "eRayTracingSkipAabbsBitKHR | ";
    if (flag & PipelineCreateFlagBits::eDeferCompileBitNV) out += "eDeferCompileBitNV | ";
    if (flag & PipelineCreateFlagBits::eReserved19BitKHR) out += "eReserved19BitKHR | ";
    if (flag & PipelineCreateFlagBits::eCaptureStatisticsBitKHR) out += "eCaptureStatisticsBitKHR | ";
    if (flag & PipelineCreateFlagBits::eCaptureInternalRepresentationsBitKHR) out += "eCaptureInternalRepresentationsBitKHR | ";
    if (flag & PipelineCreateFlagBits::eIndirectBindableBitNV) out += "eIndirectBindableBitNV | ";
    if (flag & PipelineCreateFlagBits::eLibraryBitKHR) out += "eLibraryBitKHR | ";
    if (flag & PipelineCreateFlagBits::eFailOnPipelineCompileRequiredBitEXT) out += "eFailOnPipelineCompileRequiredBitEXT | ";
    if (flag & PipelineCreateFlagBits::eEarlyReturnOnFailureBitEXT) out += "eEarlyReturnOnFailureBitEXT | ";
    if (flag & PipelineCreateFlagBits::eViewIndexFromDeviceIndex) out += "eViewIndexFromDeviceIndex | ";
    if (flag & PipelineCreateFlagBits::eDispatchBase) out += "eDispatchBase | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PipelineShaderStageCreateFlagBits val) {
    switch(val) {
        case(PipelineShaderStageCreateFlagBits::eReserved2BitNV): return "eReserved2BitNV";
        case(PipelineShaderStageCreateFlagBits::eAllowVaryingSubgroupSizeBitEXT): return "eAllowVaryingSubgroupSizeBitEXT";
        case(PipelineShaderStageCreateFlagBits::eRequireFullSubgroupsBitEXT): return "eRequireFullSubgroupsBitEXT";
        case(PipelineShaderStageCreateFlagBits::eReserved3BitKHR): return "eReserved3BitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineShaderStageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineShaderStageCreateFlagBits::eReserved2BitNV) out += "eReserved2BitNV | ";
    if (flag & PipelineShaderStageCreateFlagBits::eAllowVaryingSubgroupSizeBitEXT) out += "eAllowVaryingSubgroupSizeBitEXT | ";
    if (flag & PipelineShaderStageCreateFlagBits::eRequireFullSubgroupsBitEXT) out += "eRequireFullSubgroupsBitEXT | ";
    if (flag & PipelineShaderStageCreateFlagBits::eReserved3BitKHR) out += "eReserved3BitKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ColorComponentFlagBits val) {
    switch(val) {
        case(ColorComponentFlagBits::eR): return "eR";
        case(ColorComponentFlagBits::eG): return "eG";
        case(ColorComponentFlagBits::eB): return "eB";
        case(ColorComponentFlagBits::eA): return "eA";
        default: return "UNKNOWN";
    }
}
std::string to_string(ColorComponentFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ColorComponentFlagBits::eR) out += "eR | ";
    if (flag & ColorComponentFlagBits::eG) out += "eG | ";
    if (flag & ColorComponentFlagBits::eB) out += "eB | ";
    if (flag & ColorComponentFlagBits::eA) out += "eA | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(FenceCreateFlagBits val) {
    switch(val) {
        case(FenceCreateFlagBits::eSignaled): return "eSignaled";
        default: return "UNKNOWN";
    }
}
std::string to_string(FenceCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceCreateFlagBits::eSignaled) out += "eSignaled | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SemaphoreCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
};
const char * to_string(FormatFeatureFlagBits val) {
    switch(val) {
        case(FormatFeatureFlagBits::eSampledImage): return "eSampledImage";
        case(FormatFeatureFlagBits::eStorageImage): return "eStorageImage";
        case(FormatFeatureFlagBits::eStorageImageAtomic): return "eStorageImageAtomic";
        case(FormatFeatureFlagBits::eUniformTexelBuffer): return "eUniformTexelBuffer";
        case(FormatFeatureFlagBits::eStorageTexelBuffer): return "eStorageTexelBuffer";
        case(FormatFeatureFlagBits::eStorageTexelBufferAtomic): return "eStorageTexelBufferAtomic";
        case(FormatFeatureFlagBits::eVertexBuffer): return "eVertexBuffer";
        case(FormatFeatureFlagBits::eColorAttachment): return "eColorAttachment";
        case(FormatFeatureFlagBits::eColorAttachmentBlend): return "eColorAttachmentBlend";
        case(FormatFeatureFlagBits::eDepthStencilAttachment): return "eDepthStencilAttachment";
        case(FormatFeatureFlagBits::eBlitSrc): return "eBlitSrc";
        case(FormatFeatureFlagBits::eBlitDst): return "eBlitDst";
        case(FormatFeatureFlagBits::eSampledImageFilterLinear): return "eSampledImageFilterLinear";
        case(FormatFeatureFlagBits::eSampledImageFilterCubicBitIMG): return "eSampledImageFilterCubicBitIMG";
        case(FormatFeatureFlagBits::eReserved27BitKHR): return "eReserved27BitKHR";
        case(FormatFeatureFlagBits::eReserved28BitKHR): return "eReserved28BitKHR";
        case(FormatFeatureFlagBits::eReserved25BitKHR): return "eReserved25BitKHR";
        case(FormatFeatureFlagBits::eReserved26BitKHR): return "eReserved26BitKHR";
        case(FormatFeatureFlagBits::eAccelerationStructureVertexBufferBitKHR): return "eAccelerationStructureVertexBufferBitKHR";
        case(FormatFeatureFlagBits::eFragmentDensityMapBitEXT): return "eFragmentDensityMapBitEXT";
        case(FormatFeatureFlagBits::eAmdReserved30): return "eAmdReserved30";
        case(FormatFeatureFlagBits::eTransferSrc): return "eTransferSrc";
        case(FormatFeatureFlagBits::eTransferDst): return "eTransferDst";
        case(FormatFeatureFlagBits::eMidpointChromaSamples): return "eMidpointChromaSamples";
        case(FormatFeatureFlagBits::eSampledImageYcbcrConversionLinearFilter): return "eSampledImageYcbcrConversionLinearFilter";
        case(FormatFeatureFlagBits::eSampledImageYcbcrConversionSeparateReconstructionFilter): return "eSampledImageYcbcrConversionSeparateReconstructionFilter";
        case(FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicit): return "eSampledImageYcbcrConversionChromaReconstructionExplicit";
        case(FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicitForceable): return "eSampledImageYcbcrConversionChromaReconstructionExplicitForceable";
        case(FormatFeatureFlagBits::eDisjoint): return "eDisjoint";
        case(FormatFeatureFlagBits::eCositedChromaSamples): return "eCositedChromaSamples";
        case(FormatFeatureFlagBits::eSampledImageFilterMinmax): return "eSampledImageFilterMinmax";
        default: return "UNKNOWN";
    }
}
std::string to_string(FormatFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FormatFeatureFlagBits::eSampledImage) out += "eSampledImage | ";
    if (flag & FormatFeatureFlagBits::eStorageImage) out += "eStorageImage | ";
    if (flag & FormatFeatureFlagBits::eStorageImageAtomic) out += "eStorageImageAtomic | ";
    if (flag & FormatFeatureFlagBits::eUniformTexelBuffer) out += "eUniformTexelBuffer | ";
    if (flag & FormatFeatureFlagBits::eStorageTexelBuffer) out += "eStorageTexelBuffer | ";
    if (flag & FormatFeatureFlagBits::eStorageTexelBufferAtomic) out += "eStorageTexelBufferAtomic | ";
    if (flag & FormatFeatureFlagBits::eVertexBuffer) out += "eVertexBuffer | ";
    if (flag & FormatFeatureFlagBits::eColorAttachment) out += "eColorAttachment | ";
    if (flag & FormatFeatureFlagBits::eColorAttachmentBlend) out += "eColorAttachmentBlend | ";
    if (flag & FormatFeatureFlagBits::eDepthStencilAttachment) out += "eDepthStencilAttachment | ";
    if (flag & FormatFeatureFlagBits::eBlitSrc) out += "eBlitSrc | ";
    if (flag & FormatFeatureFlagBits::eBlitDst) out += "eBlitDst | ";
    if (flag & FormatFeatureFlagBits::eSampledImageFilterLinear) out += "eSampledImageFilterLinear | ";
    if (flag & FormatFeatureFlagBits::eSampledImageFilterCubicBitIMG) out += "eSampledImageFilterCubicBitIMG | ";
    if (flag & FormatFeatureFlagBits::eReserved27BitKHR) out += "eReserved27BitKHR | ";
    if (flag & FormatFeatureFlagBits::eReserved28BitKHR) out += "eReserved28BitKHR | ";
    if (flag & FormatFeatureFlagBits::eReserved25BitKHR) out += "eReserved25BitKHR | ";
    if (flag & FormatFeatureFlagBits::eReserved26BitKHR) out += "eReserved26BitKHR | ";
    if (flag & FormatFeatureFlagBits::eAccelerationStructureVertexBufferBitKHR) out += "eAccelerationStructureVertexBufferBitKHR | ";
    if (flag & FormatFeatureFlagBits::eFragmentDensityMapBitEXT) out += "eFragmentDensityMapBitEXT | ";
    if (flag & FormatFeatureFlagBits::eAmdReserved30) out += "eAmdReserved30 | ";
    if (flag & FormatFeatureFlagBits::eTransferSrc) out += "eTransferSrc | ";
    if (flag & FormatFeatureFlagBits::eTransferDst) out += "eTransferDst | ";
    if (flag & FormatFeatureFlagBits::eMidpointChromaSamples) out += "eMidpointChromaSamples | ";
    if (flag & FormatFeatureFlagBits::eSampledImageYcbcrConversionLinearFilter) out += "eSampledImageYcbcrConversionLinearFilter | ";
    if (flag & FormatFeatureFlagBits::eSampledImageYcbcrConversionSeparateReconstructionFilter) out += "eSampledImageYcbcrConversionSeparateReconstructionFilter | ";
    if (flag & FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicit) out += "eSampledImageYcbcrConversionChromaReconstructionExplicit | ";
    if (flag & FormatFeatureFlagBits::eSampledImageYcbcrConversionChromaReconstructionExplicitForceable) out += "eSampledImageYcbcrConversionChromaReconstructionExplicitForceable | ";
    if (flag & FormatFeatureFlagBits::eDisjoint) out += "eDisjoint | ";
    if (flag & FormatFeatureFlagBits::eCositedChromaSamples) out += "eCositedChromaSamples | ";
    if (flag & FormatFeatureFlagBits::eSampledImageFilterMinmax) out += "eSampledImageFilterMinmax | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(QueryControlFlagBits val) {
    switch(val) {
        case(QueryControlFlagBits::ePrecise): return "ePrecise";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryControlFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryControlFlagBits::ePrecise) out += "ePrecise | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(QueryResultFlagBits val) {
    switch(val) {
        case(QueryResultFlagBits::e64): return "e64";
        case(QueryResultFlagBits::eWait): return "eWait";
        case(QueryResultFlagBits::eWithAvailability): return "eWithAvailability";
        case(QueryResultFlagBits::ePartial): return "ePartial";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryResultFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryResultFlagBits::e64) out += "e64 | ";
    if (flag & QueryResultFlagBits::eWait) out += "eWait | ";
    if (flag & QueryResultFlagBits::eWithAvailability) out += "eWithAvailability | ";
    if (flag & QueryResultFlagBits::ePartial) out += "ePartial | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CommandBufferUsageFlagBits val) {
    switch(val) {
        case(CommandBufferUsageFlagBits::eOneTimeSubmit): return "eOneTimeSubmit";
        case(CommandBufferUsageFlagBits::eRenderPassContinue): return "eRenderPassContinue";
        case(CommandBufferUsageFlagBits::eSimultaneousUse): return "eSimultaneousUse";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandBufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferUsageFlagBits::eOneTimeSubmit) out += "eOneTimeSubmit | ";
    if (flag & CommandBufferUsageFlagBits::eRenderPassContinue) out += "eRenderPassContinue | ";
    if (flag & CommandBufferUsageFlagBits::eSimultaneousUse) out += "eSimultaneousUse | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(QueryPipelineStatisticFlagBits val) {
    switch(val) {
        case(QueryPipelineStatisticFlagBits::eInputAssemblyVertices): return "eInputAssemblyVertices";
        case(QueryPipelineStatisticFlagBits::eInputAssemblyPrimitives): return "eInputAssemblyPrimitives";
        case(QueryPipelineStatisticFlagBits::eVertexShaderInvocations): return "eVertexShaderInvocations";
        case(QueryPipelineStatisticFlagBits::eGeometryShaderInvocations): return "eGeometryShaderInvocations";
        case(QueryPipelineStatisticFlagBits::eGeometryShaderPrimitives): return "eGeometryShaderPrimitives";
        case(QueryPipelineStatisticFlagBits::eClippingInvocations): return "eClippingInvocations";
        case(QueryPipelineStatisticFlagBits::eClippingPrimitives): return "eClippingPrimitives";
        case(QueryPipelineStatisticFlagBits::eFragmentShaderInvocations): return "eFragmentShaderInvocations";
        case(QueryPipelineStatisticFlagBits::eTessellationControlShaderPatches): return "eTessellationControlShaderPatches";
        case(QueryPipelineStatisticFlagBits::eTessellationEvaluationShaderInvocations): return "eTessellationEvaluationShaderInvocations";
        case(QueryPipelineStatisticFlagBits::eComputeShaderInvocations): return "eComputeShaderInvocations";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryPipelineStatisticFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryPipelineStatisticFlagBits::eInputAssemblyVertices) out += "eInputAssemblyVertices | ";
    if (flag & QueryPipelineStatisticFlagBits::eInputAssemblyPrimitives) out += "eInputAssemblyPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::eVertexShaderInvocations) out += "eVertexShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::eGeometryShaderInvocations) out += "eGeometryShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::eGeometryShaderPrimitives) out += "eGeometryShaderPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::eClippingInvocations) out += "eClippingInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::eClippingPrimitives) out += "eClippingPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::eFragmentShaderInvocations) out += "eFragmentShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::eTessellationControlShaderPatches) out += "eTessellationControlShaderPatches | ";
    if (flag & QueryPipelineStatisticFlagBits::eTessellationEvaluationShaderInvocations) out += "eTessellationEvaluationShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::eComputeShaderInvocations) out += "eComputeShaderInvocations | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ImageAspectFlagBits val) {
    switch(val) {
        case(ImageAspectFlagBits::eColor): return "eColor";
        case(ImageAspectFlagBits::eDepth): return "eDepth";
        case(ImageAspectFlagBits::eStencil): return "eStencil";
        case(ImageAspectFlagBits::eMetadata): return "eMetadata";
        case(ImageAspectFlagBits::eMemoryPlane0BitEXT): return "eMemoryPlane0BitEXT";
        case(ImageAspectFlagBits::eMemoryPlane1BitEXT): return "eMemoryPlane1BitEXT";
        case(ImageAspectFlagBits::eMemoryPlane2BitEXT): return "eMemoryPlane2BitEXT";
        case(ImageAspectFlagBits::eMemoryPlane3BitEXT): return "eMemoryPlane3BitEXT";
        case(ImageAspectFlagBits::ePlane0): return "ePlane0";
        case(ImageAspectFlagBits::ePlane1): return "ePlane1";
        case(ImageAspectFlagBits::ePlane2): return "ePlane2";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageAspectFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageAspectFlagBits::eColor) out += "eColor | ";
    if (flag & ImageAspectFlagBits::eDepth) out += "eDepth | ";
    if (flag & ImageAspectFlagBits::eStencil) out += "eStencil | ";
    if (flag & ImageAspectFlagBits::eMetadata) out += "eMetadata | ";
    if (flag & ImageAspectFlagBits::eMemoryPlane0BitEXT) out += "eMemoryPlane0BitEXT | ";
    if (flag & ImageAspectFlagBits::eMemoryPlane1BitEXT) out += "eMemoryPlane1BitEXT | ";
    if (flag & ImageAspectFlagBits::eMemoryPlane2BitEXT) out += "eMemoryPlane2BitEXT | ";
    if (flag & ImageAspectFlagBits::eMemoryPlane3BitEXT) out += "eMemoryPlane3BitEXT | ";
    if (flag & ImageAspectFlagBits::ePlane0) out += "ePlane0 | ";
    if (flag & ImageAspectFlagBits::ePlane1) out += "ePlane1 | ";
    if (flag & ImageAspectFlagBits::ePlane2) out += "ePlane2 | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SparseImageFormatFlagBits val) {
    switch(val) {
        case(SparseImageFormatFlagBits::eSingleMiptail): return "eSingleMiptail";
        case(SparseImageFormatFlagBits::eAlignedMipSize): return "eAlignedMipSize";
        case(SparseImageFormatFlagBits::eNonstandardBlockSize): return "eNonstandardBlockSize";
        default: return "UNKNOWN";
    }
}
std::string to_string(SparseImageFormatFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseImageFormatFlagBits::eSingleMiptail) out += "eSingleMiptail | ";
    if (flag & SparseImageFormatFlagBits::eAlignedMipSize) out += "eAlignedMipSize | ";
    if (flag & SparseImageFormatFlagBits::eNonstandardBlockSize) out += "eNonstandardBlockSize | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SparseMemoryBindFlagBits val) {
    switch(val) {
        case(SparseMemoryBindFlagBits::eMetadata): return "eMetadata";
        default: return "UNKNOWN";
    }
}
std::string to_string(SparseMemoryBindFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseMemoryBindFlagBits::eMetadata) out += "eMetadata | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PipelineStageFlagBits val) {
    switch(val) {
        case(PipelineStageFlagBits::eTopOfPipe): return "eTopOfPipe";
        case(PipelineStageFlagBits::eDrawIndirect): return "eDrawIndirect";
        case(PipelineStageFlagBits::eVertexInput): return "eVertexInput";
        case(PipelineStageFlagBits::eVertexShader): return "eVertexShader";
        case(PipelineStageFlagBits::eTessellationControlShader): return "eTessellationControlShader";
        case(PipelineStageFlagBits::eTessellationEvaluationShader): return "eTessellationEvaluationShader";
        case(PipelineStageFlagBits::eGeometryShader): return "eGeometryShader";
        case(PipelineStageFlagBits::eFragmentShader): return "eFragmentShader";
        case(PipelineStageFlagBits::eEarlyFragmentTests): return "eEarlyFragmentTests";
        case(PipelineStageFlagBits::eLateFragmentTests): return "eLateFragmentTests";
        case(PipelineStageFlagBits::eColorAttachmentOutput): return "eColorAttachmentOutput";
        case(PipelineStageFlagBits::eComputeShader): return "eComputeShader";
        case(PipelineStageFlagBits::eTransfer): return "eTransfer";
        case(PipelineStageFlagBits::eBottomOfPipe): return "eBottomOfPipe";
        case(PipelineStageFlagBits::eHost): return "eHost";
        case(PipelineStageFlagBits::eAllGraphics): return "eAllGraphics";
        case(PipelineStageFlagBits::eAllCommands): return "eAllCommands";
        case(PipelineStageFlagBits::eReserved27BitKHR): return "eReserved27BitKHR";
        case(PipelineStageFlagBits::eReserved26BitKHR): return "eReserved26BitKHR";
        case(PipelineStageFlagBits::eTransformFeedbackBitEXT): return "eTransformFeedbackBitEXT";
        case(PipelineStageFlagBits::eConditionalRenderingBitEXT): return "eConditionalRenderingBitEXT";
        case(PipelineStageFlagBits::eRayTracingShaderBitKHR): return "eRayTracingShaderBitKHR";
        case(PipelineStageFlagBits::eAccelerationStructureBuildBitKHR): return "eAccelerationStructureBuildBitKHR";
        case(PipelineStageFlagBits::eShadingRateImageBitNV): return "eShadingRateImageBitNV";
        case(PipelineStageFlagBits::eTaskShaderBitNV): return "eTaskShaderBitNV";
        case(PipelineStageFlagBits::eMeshShaderBitNV): return "eMeshShaderBitNV";
        case(PipelineStageFlagBits::eFragmentDensityProcessBitEXT): return "eFragmentDensityProcessBitEXT";
        case(PipelineStageFlagBits::eCommandPreprocessBitNV): return "eCommandPreprocessBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineStageFlagBits::eTopOfPipe) out += "eTopOfPipe | ";
    if (flag & PipelineStageFlagBits::eDrawIndirect) out += "eDrawIndirect | ";
    if (flag & PipelineStageFlagBits::eVertexInput) out += "eVertexInput | ";
    if (flag & PipelineStageFlagBits::eVertexShader) out += "eVertexShader | ";
    if (flag & PipelineStageFlagBits::eTessellationControlShader) out += "eTessellationControlShader | ";
    if (flag & PipelineStageFlagBits::eTessellationEvaluationShader) out += "eTessellationEvaluationShader | ";
    if (flag & PipelineStageFlagBits::eGeometryShader) out += "eGeometryShader | ";
    if (flag & PipelineStageFlagBits::eFragmentShader) out += "eFragmentShader | ";
    if (flag & PipelineStageFlagBits::eEarlyFragmentTests) out += "eEarlyFragmentTests | ";
    if (flag & PipelineStageFlagBits::eLateFragmentTests) out += "eLateFragmentTests | ";
    if (flag & PipelineStageFlagBits::eColorAttachmentOutput) out += "eColorAttachmentOutput | ";
    if (flag & PipelineStageFlagBits::eComputeShader) out += "eComputeShader | ";
    if (flag & PipelineStageFlagBits::eTransfer) out += "eTransfer | ";
    if (flag & PipelineStageFlagBits::eBottomOfPipe) out += "eBottomOfPipe | ";
    if (flag & PipelineStageFlagBits::eHost) out += "eHost | ";
    if (flag & PipelineStageFlagBits::eAllGraphics) out += "eAllGraphics | ";
    if (flag & PipelineStageFlagBits::eAllCommands) out += "eAllCommands | ";
    if (flag & PipelineStageFlagBits::eReserved27BitKHR) out += "eReserved27BitKHR | ";
    if (flag & PipelineStageFlagBits::eReserved26BitKHR) out += "eReserved26BitKHR | ";
    if (flag & PipelineStageFlagBits::eTransformFeedbackBitEXT) out += "eTransformFeedbackBitEXT | ";
    if (flag & PipelineStageFlagBits::eConditionalRenderingBitEXT) out += "eConditionalRenderingBitEXT | ";
    if (flag & PipelineStageFlagBits::eRayTracingShaderBitKHR) out += "eRayTracingShaderBitKHR | ";
    if (flag & PipelineStageFlagBits::eAccelerationStructureBuildBitKHR) out += "eAccelerationStructureBuildBitKHR | ";
    if (flag & PipelineStageFlagBits::eShadingRateImageBitNV) out += "eShadingRateImageBitNV | ";
    if (flag & PipelineStageFlagBits::eTaskShaderBitNV) out += "eTaskShaderBitNV | ";
    if (flag & PipelineStageFlagBits::eMeshShaderBitNV) out += "eMeshShaderBitNV | ";
    if (flag & PipelineStageFlagBits::eFragmentDensityProcessBitEXT) out += "eFragmentDensityProcessBitEXT | ";
    if (flag & PipelineStageFlagBits::eCommandPreprocessBitNV) out += "eCommandPreprocessBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CommandPoolCreateFlagBits val) {
    switch(val) {
        case(CommandPoolCreateFlagBits::eTransient): return "eTransient";
        case(CommandPoolCreateFlagBits::eResetCommandBuffer): return "eResetCommandBuffer";
        case(CommandPoolCreateFlagBits::eProtected): return "eProtected";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolCreateFlagBits::eTransient) out += "eTransient | ";
    if (flag & CommandPoolCreateFlagBits::eResetCommandBuffer) out += "eResetCommandBuffer | ";
    if (flag & CommandPoolCreateFlagBits::eProtected) out += "eProtected | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CommandPoolResetFlagBits val) {
    switch(val) {
        case(CommandPoolResetFlagBits::eReleaseResources): return "eReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolResetFlagBits::eReleaseResources) out += "eReleaseResources | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CommandBufferResetFlagBits val) {
    switch(val) {
        case(CommandBufferResetFlagBits::eReleaseResources): return "eReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandBufferResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferResetFlagBits::eReleaseResources) out += "eReleaseResources | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SampleCountFlagBits val) {
    switch(val) {
        case(SampleCountFlagBits::e1): return "e1";
        case(SampleCountFlagBits::e2): return "e2";
        case(SampleCountFlagBits::e4): return "e4";
        case(SampleCountFlagBits::e8): return "e8";
        case(SampleCountFlagBits::e16): return "e16";
        case(SampleCountFlagBits::e32): return "e32";
        case(SampleCountFlagBits::e64): return "e64";
        default: return "UNKNOWN";
    }
}
std::string to_string(SampleCountFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SampleCountFlagBits::e1) out += "e1 | ";
    if (flag & SampleCountFlagBits::e2) out += "e2 | ";
    if (flag & SampleCountFlagBits::e4) out += "e4 | ";
    if (flag & SampleCountFlagBits::e8) out += "e8 | ";
    if (flag & SampleCountFlagBits::e16) out += "e16 | ";
    if (flag & SampleCountFlagBits::e32) out += "e32 | ";
    if (flag & SampleCountFlagBits::e64) out += "e64 | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(AttachmentDescriptionFlagBits val) {
    switch(val) {
        case(AttachmentDescriptionFlagBits::eMayAlias): return "eMayAlias";
        default: return "UNKNOWN";
    }
}
std::string to_string(AttachmentDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AttachmentDescriptionFlagBits::eMayAlias) out += "eMayAlias | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(StencilFaceFlagBits val) {
    switch(val) {
        case(StencilFaceFlagBits::eFront): return "eFront";
        case(StencilFaceFlagBits::eBack): return "eBack";
        default: return "UNKNOWN";
    }
}
std::string to_string(StencilFaceFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & StencilFaceFlagBits::eFront) out += "eFront | ";
    if (flag & StencilFaceFlagBits::eBack) out += "eBack | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DescriptorPoolCreateFlagBits val) {
    switch(val) {
        case(DescriptorPoolCreateFlagBits::eFreeDescriptorSet): return "eFreeDescriptorSet";
        case(DescriptorPoolCreateFlagBits::eUpdateAfterBind): return "eUpdateAfterBind";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorPoolCreateFlagBits::eFreeDescriptorSet) out += "eFreeDescriptorSet | ";
    if (flag & DescriptorPoolCreateFlagBits::eUpdateAfterBind) out += "eUpdateAfterBind | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DependencyFlagBits val) {
    switch(val) {
        case(DependencyFlagBits::eByRegion): return "eByRegion";
        case(DependencyFlagBits::eDeviceGroup): return "eDeviceGroup";
        case(DependencyFlagBits::eViewLocal): return "eViewLocal";
        default: return "UNKNOWN";
    }
}
std::string to_string(DependencyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DependencyFlagBits::eByRegion) out += "eByRegion | ";
    if (flag & DependencyFlagBits::eDeviceGroup) out += "eDeviceGroup | ";
    if (flag & DependencyFlagBits::eViewLocal) out += "eViewLocal | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SemaphoreWaitFlagBits val) {
    switch(val) {
        case(SemaphoreWaitFlagBits::eAny): return "eAny";
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreWaitFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreWaitFlagBits::eAny) out += "eAny | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DisplayPlaneAlphaFlagBitsKHR val) {
    switch(val) {
        case(DisplayPlaneAlphaFlagBitsKHR::eOpaqueBitKHR): return "eOpaqueBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::eGlobalBitKHR): return "eGlobalBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::ePerPixelBitKHR): return "ePerPixelBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::ePerPixelPremultipliedBitKHR): return "ePerPixelPremultipliedBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplayPlaneAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DisplayPlaneAlphaFlagBitsKHR::eOpaqueBitKHR) out += "eOpaqueBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::eGlobalBitKHR) out += "eGlobalBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::ePerPixelBitKHR) out += "ePerPixelBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::ePerPixelPremultipliedBitKHR) out += "ePerPixelPremultipliedBitKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(CompositeAlphaFlagBitsKHR val) {
    switch(val) {
        case(CompositeAlphaFlagBitsKHR::eOpaqueBitKHR): return "eOpaqueBitKHR";
        case(CompositeAlphaFlagBitsKHR::ePreMultipliedBitKHR): return "ePreMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::ePostMultipliedBitKHR): return "ePostMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::eInheritBitKHR): return "eInheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(CompositeAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CompositeAlphaFlagBitsKHR::eOpaqueBitKHR) out += "eOpaqueBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::ePreMultipliedBitKHR) out += "ePreMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::ePostMultipliedBitKHR) out += "ePostMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::eInheritBitKHR) out += "eInheritBitKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SurfaceTransformFlagBitsKHR val) {
    switch(val) {
        case(SurfaceTransformFlagBitsKHR::eIdentityBitKHR): return "eIdentityBitKHR";
        case(SurfaceTransformFlagBitsKHR::eRotate90BitKHR): return "eRotate90BitKHR";
        case(SurfaceTransformFlagBitsKHR::eRotate180BitKHR): return "eRotate180BitKHR";
        case(SurfaceTransformFlagBitsKHR::eRotate270BitKHR): return "eRotate270BitKHR";
        case(SurfaceTransformFlagBitsKHR::eHorizontalMirrorBitKHR): return "eHorizontalMirrorBitKHR";
        case(SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90BitKHR): return "eHorizontalMirrorRotate90BitKHR";
        case(SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180BitKHR): return "eHorizontalMirrorRotate180BitKHR";
        case(SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270BitKHR): return "eHorizontalMirrorRotate270BitKHR";
        case(SurfaceTransformFlagBitsKHR::eInheritBitKHR): return "eInheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(SurfaceTransformFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SurfaceTransformFlagBitsKHR::eIdentityBitKHR) out += "eIdentityBitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eRotate90BitKHR) out += "eRotate90BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eRotate180BitKHR) out += "eRotate180BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eRotate270BitKHR) out += "eRotate270BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eHorizontalMirrorBitKHR) out += "eHorizontalMirrorBitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90BitKHR) out += "eHorizontalMirrorRotate90BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180BitKHR) out += "eHorizontalMirrorRotate180BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270BitKHR) out += "eHorizontalMirrorRotate270BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::eInheritBitKHR) out += "eInheritBitKHR | ";
    return out.substr(0, out.size() - 3);
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
const char * to_string(SwapchainImageUsageFlagBitsANDROID val) {
    switch(val) {
        case(SwapchainImageUsageFlagBitsANDROID::eSharedBitANDROID): return "eSharedBitANDROID";
        default: return "UNKNOWN";
    }
}
std::string to_string(SwapchainImageUsageFlagsANDROID flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SwapchainImageUsageFlagBitsANDROID::eSharedBitANDROID) out += "eSharedBitANDROID | ";
    return out.substr(0, out.size() - 3);
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
const char * to_string(DebugReportFlagBitsEXT val) {
    switch(val) {
        case(DebugReportFlagBitsEXT::eInformationBitEXT): return "eInformationBitEXT";
        case(DebugReportFlagBitsEXT::eWarningBitEXT): return "eWarningBitEXT";
        case(DebugReportFlagBitsEXT::ePerformanceWarningBitEXT): return "ePerformanceWarningBitEXT";
        case(DebugReportFlagBitsEXT::eErrorBitEXT): return "eErrorBitEXT";
        case(DebugReportFlagBitsEXT::eDebugBitEXT): return "eDebugBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugReportFlagBitsEXT::eInformationBitEXT) out += "eInformationBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::eWarningBitEXT) out += "eWarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::ePerformanceWarningBitEXT) out += "ePerformanceWarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::eErrorBitEXT) out += "eErrorBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::eDebugBitEXT) out += "eDebugBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalMemoryHandleTypeFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32BitNV): return "eOpaqueWin32BitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32KmtBitNV): return "eOpaqueWin32KmtBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::eD3D11ImageBitNV): return "eD3D11ImageBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::eD3D11ImageKmtBitNV): return "eD3D11ImageKmtBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryHandleTypeFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32BitNV) out += "eOpaqueWin32BitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::eOpaqueWin32KmtBitNV) out += "eOpaqueWin32KmtBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::eD3D11ImageBitNV) out += "eD3D11ImageBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::eD3D11ImageKmtBitNV) out += "eD3D11ImageKmtBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalMemoryFeatureFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBitsNV::eDedicatedOnlyBitNV): return "eDedicatedOnlyBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::eExportableBitNV): return "eExportableBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::eImportableBitNV): return "eImportableBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryFeatureFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBitsNV::eDedicatedOnlyBitNV) out += "eDedicatedOnlyBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::eExportableBitNV) out += "eExportableBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::eImportableBitNV) out += "eImportableBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SubgroupFeatureFlagBits val) {
    switch(val) {
        case(SubgroupFeatureFlagBits::eBasic): return "eBasic";
        case(SubgroupFeatureFlagBits::eVote): return "eVote";
        case(SubgroupFeatureFlagBits::eArithmetic): return "eArithmetic";
        case(SubgroupFeatureFlagBits::eBallot): return "eBallot";
        case(SubgroupFeatureFlagBits::eShuffle): return "eShuffle";
        case(SubgroupFeatureFlagBits::eShuffleRelative): return "eShuffleRelative";
        case(SubgroupFeatureFlagBits::eClustered): return "eClustered";
        case(SubgroupFeatureFlagBits::eQuad): return "eQuad";
        case(SubgroupFeatureFlagBits::ePartitionedBitNV): return "ePartitionedBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(SubgroupFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SubgroupFeatureFlagBits::eBasic) out += "eBasic | ";
    if (flag & SubgroupFeatureFlagBits::eVote) out += "eVote | ";
    if (flag & SubgroupFeatureFlagBits::eArithmetic) out += "eArithmetic | ";
    if (flag & SubgroupFeatureFlagBits::eBallot) out += "eBallot | ";
    if (flag & SubgroupFeatureFlagBits::eShuffle) out += "eShuffle | ";
    if (flag & SubgroupFeatureFlagBits::eShuffleRelative) out += "eShuffleRelative | ";
    if (flag & SubgroupFeatureFlagBits::eClustered) out += "eClustered | ";
    if (flag & SubgroupFeatureFlagBits::eQuad) out += "eQuad | ";
    if (flag & SubgroupFeatureFlagBits::ePartitionedBitNV) out += "ePartitionedBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(IndirectCommandsLayoutUsageFlagBitsNV val) {
    switch(val) {
        case(IndirectCommandsLayoutUsageFlagBitsNV::eExplicitPreprocessBitNV): return "eExplicitPreprocessBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::eIndexedSequencesBitNV): return "eIndexedSequencesBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::eUnorderedSequencesBitNV): return "eUnorderedSequencesBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(IndirectCommandsLayoutUsageFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::eExplicitPreprocessBitNV) out += "eExplicitPreprocessBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::eIndexedSequencesBitNV) out += "eIndexedSequencesBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::eUnorderedSequencesBitNV) out += "eUnorderedSequencesBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(IndirectStateFlagBitsNV val) {
    switch(val) {
        case(IndirectStateFlagBitsNV::eFlagFrontfaceBitNV): return "eFlagFrontfaceBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(IndirectStateFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectStateFlagBitsNV::eFlagFrontfaceBitNV) out += "eFlagFrontfaceBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PrivateDataSlotCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PrivateDataSlotCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
};
const char * to_string(DescriptorSetLayoutCreateFlagBits val) {
    switch(val) {
        case(DescriptorSetLayoutCreateFlagBits::ePushDescriptorBitKHR): return "ePushDescriptorBitKHR";
        case(DescriptorSetLayoutCreateFlagBits::eUpdateAfterBindPool): return "eUpdateAfterBindPool";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorSetLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorSetLayoutCreateFlagBits::ePushDescriptorBitKHR) out += "ePushDescriptorBitKHR | ";
    if (flag & DescriptorSetLayoutCreateFlagBits::eUpdateAfterBindPool) out += "eUpdateAfterBindPool | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalMemoryHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalMemoryHandleTypeFlagBits::eOpaqueFd): return "eOpaqueFd";
        case(ExternalMemoryHandleTypeFlagBits::eOpaqueWin32): return "eOpaqueWin32";
        case(ExternalMemoryHandleTypeFlagBits::eOpaqueWin32Kmt): return "eOpaqueWin32Kmt";
        case(ExternalMemoryHandleTypeFlagBits::eD3D11Texture): return "eD3D11Texture";
        case(ExternalMemoryHandleTypeFlagBits::eD3D11TextureKmt): return "eD3D11TextureKmt";
        case(ExternalMemoryHandleTypeFlagBits::eD3D12Heap): return "eD3D12Heap";
        case(ExternalMemoryHandleTypeFlagBits::eD3D12Resource): return "eD3D12Resource";
        case(ExternalMemoryHandleTypeFlagBits::eDmaBufBitEXT): return "eDmaBufBitEXT";
        case(ExternalMemoryHandleTypeFlagBits::eAndroidHardwareBufferBitANDROID): return "eAndroidHardwareBufferBitANDROID";
        case(ExternalMemoryHandleTypeFlagBits::eHostAllocationBitEXT): return "eHostAllocationBitEXT";
        case(ExternalMemoryHandleTypeFlagBits::eHostMappedForeignMemoryBitEXT): return "eHostMappedForeignMemoryBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryHandleTypeFlagBits::eOpaqueFd) out += "eOpaqueFd | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eOpaqueWin32) out += "eOpaqueWin32 | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eOpaqueWin32Kmt) out += "eOpaqueWin32Kmt | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eD3D11Texture) out += "eD3D11Texture | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eD3D11TextureKmt) out += "eD3D11TextureKmt | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eD3D12Heap) out += "eD3D12Heap | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eD3D12Resource) out += "eD3D12Resource | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eDmaBufBitEXT) out += "eDmaBufBitEXT | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eAndroidHardwareBufferBitANDROID) out += "eAndroidHardwareBufferBitANDROID | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eHostAllocationBitEXT) out += "eHostAllocationBitEXT | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::eHostMappedForeignMemoryBitEXT) out += "eHostMappedForeignMemoryBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalMemoryFeatureFlagBits val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBits::eDedicatedOnly): return "eDedicatedOnly";
        case(ExternalMemoryFeatureFlagBits::eExportable): return "eExportable";
        case(ExternalMemoryFeatureFlagBits::eImportable): return "eImportable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBits::eDedicatedOnly) out += "eDedicatedOnly | ";
    if (flag & ExternalMemoryFeatureFlagBits::eExportable) out += "eExportable | ";
    if (flag & ExternalMemoryFeatureFlagBits::eImportable) out += "eImportable | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalSemaphoreHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreHandleTypeFlagBits::eOpaqueFd): return "eOpaqueFd";
        case(ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32): return "eOpaqueWin32";
        case(ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32Kmt): return "eOpaqueWin32Kmt";
        case(ExternalSemaphoreHandleTypeFlagBits::eD3D12Fence): return "eD3D12Fence";
        case(ExternalSemaphoreHandleTypeFlagBits::eSyncFd): return "eSyncFd";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalSemaphoreHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreHandleTypeFlagBits::eOpaqueFd) out += "eOpaqueFd | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32) out += "eOpaqueWin32 | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::eOpaqueWin32Kmt) out += "eOpaqueWin32Kmt | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::eD3D12Fence) out += "eD3D12Fence | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::eSyncFd) out += "eSyncFd | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalSemaphoreFeatureFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreFeatureFlagBits::eExportable): return "eExportable";
        case(ExternalSemaphoreFeatureFlagBits::eImportable): return "eImportable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalSemaphoreFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreFeatureFlagBits::eExportable) out += "eExportable | ";
    if (flag & ExternalSemaphoreFeatureFlagBits::eImportable) out += "eImportable | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SemaphoreImportFlagBits val) {
    switch(val) {
        case(SemaphoreImportFlagBits::eTemporary): return "eTemporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreImportFlagBits::eTemporary) out += "eTemporary | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalFenceHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalFenceHandleTypeFlagBits::eOpaqueFd): return "eOpaqueFd";
        case(ExternalFenceHandleTypeFlagBits::eOpaqueWin32): return "eOpaqueWin32";
        case(ExternalFenceHandleTypeFlagBits::eOpaqueWin32Kmt): return "eOpaqueWin32Kmt";
        case(ExternalFenceHandleTypeFlagBits::eSyncFd): return "eSyncFd";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalFenceHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceHandleTypeFlagBits::eOpaqueFd) out += "eOpaqueFd | ";
    if (flag & ExternalFenceHandleTypeFlagBits::eOpaqueWin32) out += "eOpaqueWin32 | ";
    if (flag & ExternalFenceHandleTypeFlagBits::eOpaqueWin32Kmt) out += "eOpaqueWin32Kmt | ";
    if (flag & ExternalFenceHandleTypeFlagBits::eSyncFd) out += "eSyncFd | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ExternalFenceFeatureFlagBits val) {
    switch(val) {
        case(ExternalFenceFeatureFlagBits::eExportable): return "eExportable";
        case(ExternalFenceFeatureFlagBits::eImportable): return "eImportable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalFenceFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceFeatureFlagBits::eExportable) out += "eExportable | ";
    if (flag & ExternalFenceFeatureFlagBits::eImportable) out += "eImportable | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(FenceImportFlagBits val) {
    switch(val) {
        case(FenceImportFlagBits::eTemporary): return "eTemporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(FenceImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceImportFlagBits::eTemporary) out += "eTemporary | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SurfaceCounterFlagBitsEXT val) {
    switch(val) {
        case(SurfaceCounterFlagBitsEXT::eVblankEXT): return "eVblankEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(SurfaceCounterFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SurfaceCounterFlagBitsEXT::eVblankEXT) out += "eVblankEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PeerMemoryFeatureFlagBits val) {
    switch(val) {
        case(PeerMemoryFeatureFlagBits::eCopySrc): return "eCopySrc";
        case(PeerMemoryFeatureFlagBits::eCopyDst): return "eCopyDst";
        case(PeerMemoryFeatureFlagBits::eGenericSrc): return "eGenericSrc";
        case(PeerMemoryFeatureFlagBits::eGenericDst): return "eGenericDst";
        default: return "UNKNOWN";
    }
}
std::string to_string(PeerMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PeerMemoryFeatureFlagBits::eCopySrc) out += "eCopySrc | ";
    if (flag & PeerMemoryFeatureFlagBits::eCopyDst) out += "eCopyDst | ";
    if (flag & PeerMemoryFeatureFlagBits::eGenericSrc) out += "eGenericSrc | ";
    if (flag & PeerMemoryFeatureFlagBits::eGenericDst) out += "eGenericDst | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(MemoryAllocateFlagBits val) {
    switch(val) {
        case(MemoryAllocateFlagBits::eDeviceMask): return "eDeviceMask";
        case(MemoryAllocateFlagBits::eDeviceAddress): return "eDeviceAddress";
        case(MemoryAllocateFlagBits::eDeviceAddressCaptureReplay): return "eDeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryAllocateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryAllocateFlagBits::eDeviceMask) out += "eDeviceMask | ";
    if (flag & MemoryAllocateFlagBits::eDeviceAddress) out += "eDeviceAddress | ";
    if (flag & MemoryAllocateFlagBits::eDeviceAddressCaptureReplay) out += "eDeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DeviceGroupPresentModeFlagBitsKHR val) {
    switch(val) {
        case(DeviceGroupPresentModeFlagBitsKHR::eLocalBitKHR): return "eLocalBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::eRemoteBitKHR): return "eRemoteBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::eSumBitKHR): return "eSumBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::eLocalMultiDeviceBitKHR): return "eLocalMultiDeviceBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceGroupPresentModeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceGroupPresentModeFlagBitsKHR::eLocalBitKHR) out += "eLocalBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::eRemoteBitKHR) out += "eRemoteBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::eSumBitKHR) out += "eSumBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::eLocalMultiDeviceBitKHR) out += "eLocalMultiDeviceBitKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SwapchainCreateFlagBitsKHR val) {
    switch(val) {
        case(SwapchainCreateFlagBitsKHR::eSplitInstanceBindRegionsBitKHR): return "eSplitInstanceBindRegionsBitKHR";
        case(SwapchainCreateFlagBitsKHR::eProtectedBitKHR): return "eProtectedBitKHR";
        case(SwapchainCreateFlagBitsKHR::eMutableFormatBitKHR): return "eMutableFormatBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(SwapchainCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SwapchainCreateFlagBitsKHR::eSplitInstanceBindRegionsBitKHR) out += "eSplitInstanceBindRegionsBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::eProtectedBitKHR) out += "eProtectedBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::eMutableFormatBitKHR) out += "eMutableFormatBitKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(SubpassDescriptionFlagBits val) {
    switch(val) {
        case(SubpassDescriptionFlagBits::ePerViewAttributesBitNVX): return "ePerViewAttributesBitNVX";
        case(SubpassDescriptionFlagBits::ePerViewPositionXOnlyBitNVX): return "ePerViewPositionXOnlyBitNVX";
        case(SubpassDescriptionFlagBits::eFragmentRegionBitQCOM): return "eFragmentRegionBitQCOM";
        case(SubpassDescriptionFlagBits::eShaderResolveBitQCOM): return "eShaderResolveBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(SubpassDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SubpassDescriptionFlagBits::ePerViewAttributesBitNVX) out += "ePerViewAttributesBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::ePerViewPositionXOnlyBitNVX) out += "ePerViewPositionXOnlyBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::eFragmentRegionBitQCOM) out += "eFragmentRegionBitQCOM | ";
    if (flag & SubpassDescriptionFlagBits::eShaderResolveBitQCOM) out += "eShaderResolveBitQCOM | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DebugUtilsMessageSeverityFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageSeverityFlagBitsEXT::eVerboseBitEXT): return "eVerboseBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::eInfoBitEXT): return "eInfoBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::eWarningBitEXT): return "eWarningBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::eErrorBitEXT): return "eErrorBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessageSeverityFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::eVerboseBitEXT) out += "eVerboseBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::eInfoBitEXT) out += "eInfoBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::eWarningBitEXT) out += "eWarningBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::eErrorBitEXT) out += "eErrorBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DebugUtilsMessageTypeFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageTypeFlagBitsEXT::eGeneralBitEXT): return "eGeneralBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::eValidationBitEXT): return "eValidationBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::ePerformanceBitEXT): return "ePerformanceBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessageTypeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::eGeneralBitEXT) out += "eGeneralBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::eValidationBitEXT) out += "eValidationBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::ePerformanceBitEXT) out += "ePerformanceBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DescriptorBindingFlagBits val) {
    switch(val) {
        case(DescriptorBindingFlagBits::eUpdateAfterBind): return "eUpdateAfterBind";
        case(DescriptorBindingFlagBits::eUpdateUnusedWhilePending): return "eUpdateUnusedWhilePending";
        case(DescriptorBindingFlagBits::ePartiallyBound): return "ePartiallyBound";
        case(DescriptorBindingFlagBits::eVariableDescriptorCount): return "eVariableDescriptorCount";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorBindingFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorBindingFlagBits::eUpdateAfterBind) out += "eUpdateAfterBind | ";
    if (flag & DescriptorBindingFlagBits::eUpdateUnusedWhilePending) out += "eUpdateUnusedWhilePending | ";
    if (flag & DescriptorBindingFlagBits::ePartiallyBound) out += "ePartiallyBound | ";
    if (flag & DescriptorBindingFlagBits::eVariableDescriptorCount) out += "eVariableDescriptorCount | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ConditionalRenderingFlagBitsEXT val) {
    switch(val) {
        case(ConditionalRenderingFlagBitsEXT::eInvertedBitEXT): return "eInvertedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ConditionalRenderingFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ConditionalRenderingFlagBitsEXT::eInvertedBitEXT) out += "eInvertedBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(ResolveModeFlagBits val) {
    switch(val) {
        case(ResolveModeFlagBits::eNone): return "eNone";
        case(ResolveModeFlagBits::eSampleZero): return "eSampleZero";
        case(ResolveModeFlagBits::eAverage): return "eAverage";
        case(ResolveModeFlagBits::eMin): return "eMin";
        case(ResolveModeFlagBits::eMax): return "eMax";
        default: return "UNKNOWN";
    }
}
std::string to_string(ResolveModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ResolveModeFlagBits::eNone) out += "eNone | ";
    if (flag & ResolveModeFlagBits::eSampleZero) out += "eSampleZero | ";
    if (flag & ResolveModeFlagBits::eAverage) out += "eAverage | ";
    if (flag & ResolveModeFlagBits::eMin) out += "eMin | ";
    if (flag & ResolveModeFlagBits::eMax) out += "eMax | ";
    return out.substr(0, out.size() - 3);
};
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryInstanceFlagBitsKHR val) {
    switch(val) {
        case(GeometryInstanceFlagBitsKHR::eTriangleFacingCullDisableBitKHR): return "eTriangleFacingCullDisableBitKHR";
        case(GeometryInstanceFlagBitsKHR::eTriangleFrontCounterclockwiseBitKHR): return "eTriangleFrontCounterclockwiseBitKHR";
        case(GeometryInstanceFlagBitsKHR::eForceOpaqueBitKHR): return "eForceOpaqueBitKHR";
        case(GeometryInstanceFlagBitsKHR::eForceNoOpaqueBitKHR): return "eForceNoOpaqueBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(GeometryInstanceFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryInstanceFlagBitsKHR::eTriangleFacingCullDisableBitKHR) out += "eTriangleFacingCullDisableBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::eTriangleFrontCounterclockwiseBitKHR) out += "eTriangleFrontCounterclockwiseBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::eForceOpaqueBitKHR) out += "eForceOpaqueBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::eForceNoOpaqueBitKHR) out += "eForceNoOpaqueBitKHR | ";
    return out.substr(0, out.size() - 3);
};
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryFlagBitsKHR val) {
    switch(val) {
        case(GeometryFlagBitsKHR::eOpaqueBitKHR): return "eOpaqueBitKHR";
        case(GeometryFlagBitsKHR::eNoDuplicateAnyHitInvocationBitKHR): return "eNoDuplicateAnyHitInvocationBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(GeometryFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryFlagBitsKHR::eOpaqueBitKHR) out += "eOpaqueBitKHR | ";
    if (flag & GeometryFlagBitsKHR::eNoDuplicateAnyHitInvocationBitKHR) out += "eNoDuplicateAnyHitInvocationBitKHR | ";
    return out.substr(0, out.size() - 3);
};
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(BuildAccelerationStructureFlagBitsKHR val) {
    switch(val) {
        case(BuildAccelerationStructureFlagBitsKHR::eAllowUpdateBitKHR): return "eAllowUpdateBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::eAllowCompactionBitKHR): return "eAllowCompactionBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::ePreferFastTraceBitKHR): return "ePreferFastTraceBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::ePreferFastBuildBitKHR): return "ePreferFastBuildBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::eLowMemoryBitKHR): return "eLowMemoryBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(BuildAccelerationStructureFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BuildAccelerationStructureFlagBitsKHR::eAllowUpdateBitKHR) out += "eAllowUpdateBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::eAllowCompactionBitKHR) out += "eAllowCompactionBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::ePreferFastTraceBitKHR) out += "ePreferFastTraceBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::ePreferFastBuildBitKHR) out += "ePreferFastBuildBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::eLowMemoryBitKHR) out += "eLowMemoryBitKHR | ";
    return out.substr(0, out.size() - 3);
};
#endif // VK_ENABLE_BETA_EXTENSIONS
const char * to_string(FramebufferCreateFlagBits val) {
    switch(val) {
        case(FramebufferCreateFlagBits::eImageless): return "eImageless";
        default: return "UNKNOWN";
    }
}
std::string to_string(FramebufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FramebufferCreateFlagBits::eImageless) out += "eImageless | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(DeviceDiagnosticsConfigFlagBitsNV val) {
    switch(val) {
        case(DeviceDiagnosticsConfigFlagBitsNV::eEnableShaderDebugInfoBitNV): return "eEnableShaderDebugInfoBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::eEnableResourceTrackingBitNV): return "eEnableResourceTrackingBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::eEnableAutomaticCheckpointsBitNV): return "eEnableAutomaticCheckpointsBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceDiagnosticsConfigFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::eEnableShaderDebugInfoBitNV) out += "eEnableShaderDebugInfoBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::eEnableResourceTrackingBitNV) out += "eEnableResourceTrackingBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::eEnableAutomaticCheckpointsBitNV) out += "eEnableAutomaticCheckpointsBitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PipelineCreationFeedbackFlagBitsEXT val) {
    switch(val) {
        case(PipelineCreationFeedbackFlagBitsEXT::eValidBitEXT): return "eValidBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::eApplicationPipelineCacheHitBitEXT): return "eApplicationPipelineCacheHitBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::eBasePipelineAccelerationBitEXT): return "eBasePipelineAccelerationBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCreationFeedbackFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCreationFeedbackFlagBitsEXT::eValidBitEXT) out += "eValidBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::eApplicationPipelineCacheHitBitEXT) out += "eApplicationPipelineCacheHitBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::eBasePipelineAccelerationBitEXT) out += "eBasePipelineAccelerationBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PerformanceCounterDescriptionFlagBitsKHR val) {
    switch(val) {
        case(PerformanceCounterDescriptionFlagBitsKHR::ePerformanceImpactingKHR): return "ePerformanceImpactingKHR";
        case(PerformanceCounterDescriptionFlagBitsKHR::eConcurrentlyImpactedKHR): return "eConcurrentlyImpactedKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(PerformanceCounterDescriptionFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::ePerformanceImpactingKHR) out += "ePerformanceImpactingKHR | ";
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::eConcurrentlyImpactedKHR) out += "eConcurrentlyImpactedKHR | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(AcquireProfilingLockFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(AcquireProfilingLockFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
};
const char * to_string(ShaderCorePropertiesFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderCorePropertiesFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
};
const char * to_string(ShaderModuleCreateFlagBits val) {
    switch(val) {
        case(ShaderModuleCreateFlagBits::eReserved0BitNV): return "eReserved0BitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderModuleCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ShaderModuleCreateFlagBits::eReserved0BitNV) out += "eReserved0BitNV | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(PipelineCompilerControlFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCompilerControlFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
};
const char * to_string(ToolPurposeFlagBitsEXT val) {
    switch(val) {
        case(ToolPurposeFlagBitsEXT::eValidationBitEXT): return "eValidationBitEXT";
        case(ToolPurposeFlagBitsEXT::eProfilingBitEXT): return "eProfilingBitEXT";
        case(ToolPurposeFlagBitsEXT::eTracingBitEXT): return "eTracingBitEXT";
        case(ToolPurposeFlagBitsEXT::eAdditionalFeaturesBitEXT): return "eAdditionalFeaturesBitEXT";
        case(ToolPurposeFlagBitsEXT::eModifyingFeaturesBitEXT): return "eModifyingFeaturesBitEXT";
        case(ToolPurposeFlagBitsEXT::eDebugReportingBitEXT): return "eDebugReportingBitEXT";
        case(ToolPurposeFlagBitsEXT::eDebugMarkersBitEXT): return "eDebugMarkersBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ToolPurposeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ToolPurposeFlagBitsEXT::eValidationBitEXT) out += "eValidationBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eProfilingBitEXT) out += "eProfilingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eTracingBitEXT) out += "eTracingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eAdditionalFeaturesBitEXT) out += "eAdditionalFeaturesBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eModifyingFeaturesBitEXT) out += "eModifyingFeaturesBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eDebugReportingBitEXT) out += "eDebugReportingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::eDebugMarkersBitEXT) out += "eDebugMarkersBitEXT | ";
    return out.substr(0, out.size() - 3);
};
const char * to_string(QueryPoolCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineLayoutCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineDepthStencilStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDepthStencilStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineDynamicStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDynamicStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineColorBlendStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineColorBlendStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineMultisampleStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineMultisampleStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineRasterizationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineViewportStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineViewportStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineTessellationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineTessellationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineInputAssemblyStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineInputAssemblyStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineVertexInputStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineVertexInputStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(BufferViewCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(InstanceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(InstanceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DeviceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(EventCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(EventCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(MemoryMapFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryMapFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DescriptorPoolResetFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DescriptorUpdateTemplateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorUpdateTemplateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DisplayModeCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplayModeCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DisplaySurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplaySurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
const char * to_string(AndroidSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(AndroidSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_VI_NN)
const char * to_string(ViSurfaceCreateFlagBitsNN val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ViSurfaceCreateFlagsNN flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_VI_NN
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
const char * to_string(WaylandSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(WaylandSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(Win32SurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(Win32SurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
const char * to_string(XlibSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(XlibSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
const char * to_string(XcbSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(XcbSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
const char * to_string(DirectFBSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DirectFBSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_IOS_MVK)
const char * to_string(IOSSurfaceCreateFlagBitsMVK val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(IOSSurfaceCreateFlagsMVK flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
const char * to_string(MacOSSurfaceCreateFlagBitsMVK val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(MacOSSurfaceCreateFlagsMVK flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_MACOS_MVK
#if defined(VK_USE_PLATFORM_METAL_EXT)
const char * to_string(MetalSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(MetalSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_METAL_EXT
#if defined(VK_USE_PLATFORM_FUCHSIA)
const char * to_string(ImagePipeSurfaceCreateFlagBitsFUCHSIA val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ImagePipeSurfaceCreateFlagsFUCHSIA flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_GGP)
const char * to_string(StreamDescriptorSurfaceCreateFlagBitsGGP val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(StreamDescriptorSurfaceCreateFlagsGGP flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
#endif // VK_USE_PLATFORM_GGP
const char * to_string(HeadlessSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(HeadlessSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(CommandPoolTrimFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolTrimFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineViewportSwizzleStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineViewportSwizzleStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineDiscardRectangleStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDiscardRectangleStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineCoverageToColorStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageToColorStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineCoverageModulationStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageModulationStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineCoverageReductionStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageReductionStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(ValidationCacheCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ValidationCacheCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DebugUtilsMessengerCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessengerCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(DebugUtilsMessengerCallbackDataFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessengerCallbackDataFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineRasterizationConservativeStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationConservativeStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineRasterizationStateStreamCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationStateStreamCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
const char * to_string(PipelineRasterizationDepthClipStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationDepthClipStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
};
} // namespace vk
// clang-format on
