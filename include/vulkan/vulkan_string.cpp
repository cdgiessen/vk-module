/*
 * Copyright 2021 Charles Giessen (cdgiessen@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
// clang-format off
#include "vulkan_string.h"
#define UNUSED_VARIABLE(x) (void)(x)
const char * to_string(VkAttachmentLoadOp val) {
    switch(val) {
        case(VkAttachmentLoadOp::Load): return "Load";
        case(VkAttachmentLoadOp::Clear): return "Clear";
        case(VkAttachmentLoadOp::DontCare): return "DontCare";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkAttachmentStoreOp val) {
    switch(val) {
        case(VkAttachmentStoreOp::Store): return "Store";
        case(VkAttachmentStoreOp::DontCare): return "DontCare";
        case(VkAttachmentStoreOp::NoneQCOM): return "NoneQCOM";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkBlendFactor val) {
    switch(val) {
        case(VkBlendFactor::Zero): return "Zero";
        case(VkBlendFactor::One): return "One";
        case(VkBlendFactor::SrcColor): return "SrcColor";
        case(VkBlendFactor::OneMinusSrcColor): return "OneMinusSrcColor";
        case(VkBlendFactor::DstColor): return "DstColor";
        case(VkBlendFactor::OneMinusDstColor): return "OneMinusDstColor";
        case(VkBlendFactor::SrcAlpha): return "SrcAlpha";
        case(VkBlendFactor::OneMinusSrcAlpha): return "OneMinusSrcAlpha";
        case(VkBlendFactor::DstAlpha): return "DstAlpha";
        case(VkBlendFactor::OneMinusDstAlpha): return "OneMinusDstAlpha";
        case(VkBlendFactor::ConstantColor): return "ConstantColor";
        case(VkBlendFactor::OneMinusConstantColor): return "OneMinusConstantColor";
        case(VkBlendFactor::ConstantAlpha): return "ConstantAlpha";
        case(VkBlendFactor::OneMinusConstantAlpha): return "OneMinusConstantAlpha";
        case(VkBlendFactor::SrcAlphaSaturate): return "SrcAlphaSaturate";
        case(VkBlendFactor::Src1Color): return "Src1Color";
        case(VkBlendFactor::OneMinusSrc1Color): return "OneMinusSrc1Color";
        case(VkBlendFactor::Src1Alpha): return "Src1Alpha";
        case(VkBlendFactor::OneMinusSrc1Alpha): return "OneMinusSrc1Alpha";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkBlendOp val) {
    switch(val) {
        case(VkBlendOp::Add): return "Add";
        case(VkBlendOp::Subtract): return "Subtract";
        case(VkBlendOp::ReverseSubtract): return "ReverseSubtract";
        case(VkBlendOp::Min): return "Min";
        case(VkBlendOp::Max): return "Max";
        case(VkBlendOp::ZeroEXT): return "ZeroEXT";
        case(VkBlendOp::SrcEXT): return "SrcEXT";
        case(VkBlendOp::DstEXT): return "DstEXT";
        case(VkBlendOp::SrcOverEXT): return "SrcOverEXT";
        case(VkBlendOp::DstOverEXT): return "DstOverEXT";
        case(VkBlendOp::SrcInEXT): return "SrcInEXT";
        case(VkBlendOp::DstInEXT): return "DstInEXT";
        case(VkBlendOp::SrcOutEXT): return "SrcOutEXT";
        case(VkBlendOp::DstOutEXT): return "DstOutEXT";
        case(VkBlendOp::SrcAtopEXT): return "SrcAtopEXT";
        case(VkBlendOp::DstAtopEXT): return "DstAtopEXT";
        case(VkBlendOp::XorEXT): return "XorEXT";
        case(VkBlendOp::MultiplyEXT): return "MultiplyEXT";
        case(VkBlendOp::ScreenEXT): return "ScreenEXT";
        case(VkBlendOp::OverlayEXT): return "OverlayEXT";
        case(VkBlendOp::DarkenEXT): return "DarkenEXT";
        case(VkBlendOp::LightenEXT): return "LightenEXT";
        case(VkBlendOp::ColordodgeEXT): return "ColordodgeEXT";
        case(VkBlendOp::ColorburnEXT): return "ColorburnEXT";
        case(VkBlendOp::HardlightEXT): return "HardlightEXT";
        case(VkBlendOp::SoftlightEXT): return "SoftlightEXT";
        case(VkBlendOp::DifferenceEXT): return "DifferenceEXT";
        case(VkBlendOp::ExclusionEXT): return "ExclusionEXT";
        case(VkBlendOp::InvertEXT): return "InvertEXT";
        case(VkBlendOp::InvertRgbEXT): return "InvertRgbEXT";
        case(VkBlendOp::LineardodgeEXT): return "LineardodgeEXT";
        case(VkBlendOp::LinearburnEXT): return "LinearburnEXT";
        case(VkBlendOp::VividlightEXT): return "VividlightEXT";
        case(VkBlendOp::LinearlightEXT): return "LinearlightEXT";
        case(VkBlendOp::PinlightEXT): return "PinlightEXT";
        case(VkBlendOp::HardmixEXT): return "HardmixEXT";
        case(VkBlendOp::HslHueEXT): return "HslHueEXT";
        case(VkBlendOp::HslSaturationEXT): return "HslSaturationEXT";
        case(VkBlendOp::HslColorEXT): return "HslColorEXT";
        case(VkBlendOp::HslLuminosityEXT): return "HslLuminosityEXT";
        case(VkBlendOp::PlusEXT): return "PlusEXT";
        case(VkBlendOp::PlusClampedEXT): return "PlusClampedEXT";
        case(VkBlendOp::PlusClampedAlphaEXT): return "PlusClampedAlphaEXT";
        case(VkBlendOp::PlusDarkerEXT): return "PlusDarkerEXT";
        case(VkBlendOp::MinusEXT): return "MinusEXT";
        case(VkBlendOp::MinusClampedEXT): return "MinusClampedEXT";
        case(VkBlendOp::ContrastEXT): return "ContrastEXT";
        case(VkBlendOp::InvertOvgEXT): return "InvertOvgEXT";
        case(VkBlendOp::RedEXT): return "RedEXT";
        case(VkBlendOp::GreenEXT): return "GreenEXT";
        case(VkBlendOp::BlueEXT): return "BlueEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkBorderColor val) {
    switch(val) {
        case(VkBorderColor::FloatTransparentBlack): return "FloatTransparentBlack";
        case(VkBorderColor::IntTransparentBlack): return "IntTransparentBlack";
        case(VkBorderColor::FloatOpaqueBlack): return "FloatOpaqueBlack";
        case(VkBorderColor::IntOpaqueBlack): return "IntOpaqueBlack";
        case(VkBorderColor::FloatOpaqueWhite): return "FloatOpaqueWhite";
        case(VkBorderColor::IntOpaqueWhite): return "IntOpaqueWhite";
        case(VkBorderColor::FloatCustomEXT): return "FloatCustomEXT";
        case(VkBorderColor::IntCustomEXT): return "IntCustomEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPipelineCacheHeaderVersion val) {
    switch(val) {
        case(VkPipelineCacheHeaderVersion::One): return "One";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkComponentSwizzle val) {
    switch(val) {
        case(VkComponentSwizzle::Identity): return "Identity";
        case(VkComponentSwizzle::Zero): return "Zero";
        case(VkComponentSwizzle::One): return "One";
        case(VkComponentSwizzle::R): return "R";
        case(VkComponentSwizzle::G): return "G";
        case(VkComponentSwizzle::B): return "B";
        case(VkComponentSwizzle::A): return "A";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCommandBufferLevel val) {
    switch(val) {
        case(VkCommandBufferLevel::Primary): return "Primary";
        case(VkCommandBufferLevel::Secondary): return "Secondary";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCompareOp val) {
    switch(val) {
        case(VkCompareOp::Never): return "Never";
        case(VkCompareOp::Less): return "Less";
        case(VkCompareOp::Equal): return "Equal";
        case(VkCompareOp::LessOrEqual): return "LessOrEqual";
        case(VkCompareOp::Greater): return "Greater";
        case(VkCompareOp::NotEqual): return "NotEqual";
        case(VkCompareOp::GreaterOrEqual): return "GreaterOrEqual";
        case(VkCompareOp::Always): return "Always";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDescriptorType val) {
    switch(val) {
        case(VkDescriptorType::Sampler): return "Sampler";
        case(VkDescriptorType::CombinedImageSampler): return "CombinedImageSampler";
        case(VkDescriptorType::SampledImage): return "SampledImage";
        case(VkDescriptorType::StorageImage): return "StorageImage";
        case(VkDescriptorType::UniformTexelBuffer): return "UniformTexelBuffer";
        case(VkDescriptorType::StorageTexelBuffer): return "StorageTexelBuffer";
        case(VkDescriptorType::UniformBuffer): return "UniformBuffer";
        case(VkDescriptorType::StorageBuffer): return "StorageBuffer";
        case(VkDescriptorType::UniformBufferDynamic): return "UniformBufferDynamic";
        case(VkDescriptorType::StorageBufferDynamic): return "StorageBufferDynamic";
        case(VkDescriptorType::InputAttachment): return "InputAttachment";
        case(VkDescriptorType::InlineUniformBlockEXT): return "InlineUniformBlockEXT";
        case(VkDescriptorType::AccelerationStructureKHR): return "AccelerationStructureKHR";
        case(VkDescriptorType::AccelerationStructureNV): return "AccelerationStructureNV";
        case(VkDescriptorType::MutableVALVE): return "MutableVALVE";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDynamicState val) {
    switch(val) {
        case(VkDynamicState::Viewport): return "Viewport";
        case(VkDynamicState::Scissor): return "Scissor";
        case(VkDynamicState::LineWidth): return "LineWidth";
        case(VkDynamicState::DepthBias): return "DepthBias";
        case(VkDynamicState::BlendConstants): return "BlendConstants";
        case(VkDynamicState::DepthBounds): return "DepthBounds";
        case(VkDynamicState::StencilCompareMask): return "StencilCompareMask";
        case(VkDynamicState::StencilWriteMask): return "StencilWriteMask";
        case(VkDynamicState::StencilReference): return "StencilReference";
        case(VkDynamicState::ViewportWScalingNV): return "ViewportWScalingNV";
        case(VkDynamicState::DiscardRectangleEXT): return "DiscardRectangleEXT";
        case(VkDynamicState::SampleLocationsEXT): return "SampleLocationsEXT";
        case(VkDynamicState::RayTracingPipelineStackSizeKHR): return "RayTracingPipelineStackSizeKHR";
        case(VkDynamicState::ViewportShadingRatePaletteNV): return "ViewportShadingRatePaletteNV";
        case(VkDynamicState::ViewportCoarseSampleOrderNV): return "ViewportCoarseSampleOrderNV";
        case(VkDynamicState::ExclusiveScissorNV): return "ExclusiveScissorNV";
        case(VkDynamicState::FragmentShadingRateKHR): return "FragmentShadingRateKHR";
        case(VkDynamicState::LineStippleEXT): return "LineStippleEXT";
        case(VkDynamicState::CullModeEXT): return "CullModeEXT";
        case(VkDynamicState::FrontFaceEXT): return "FrontFaceEXT";
        case(VkDynamicState::PrimitiveTopologyEXT): return "PrimitiveTopologyEXT";
        case(VkDynamicState::ViewportWithCountEXT): return "ViewportWithCountEXT";
        case(VkDynamicState::ScissorWithCountEXT): return "ScissorWithCountEXT";
        case(VkDynamicState::VertexInputBindingStrideEXT): return "VertexInputBindingStrideEXT";
        case(VkDynamicState::DepthTestEnableEXT): return "DepthTestEnableEXT";
        case(VkDynamicState::DepthWriteEnableEXT): return "DepthWriteEnableEXT";
        case(VkDynamicState::DepthCompareOpEXT): return "DepthCompareOpEXT";
        case(VkDynamicState::DepthBoundsTestEnableEXT): return "DepthBoundsTestEnableEXT";
        case(VkDynamicState::StencilTestEnableEXT): return "StencilTestEnableEXT";
        case(VkDynamicState::StencilOpEXT): return "StencilOpEXT";
        case(VkDynamicState::VertexInputEXT): return "VertexInputEXT";
        case(VkDynamicState::PatchControlPointsEXT): return "PatchControlPointsEXT";
        case(VkDynamicState::RasterizerDiscardEnableEXT): return "RasterizerDiscardEnableEXT";
        case(VkDynamicState::DepthBiasEnableEXT): return "DepthBiasEnableEXT";
        case(VkDynamicState::LogicOpEXT): return "LogicOpEXT";
        case(VkDynamicState::PrimitiveRestartEnableEXT): return "PrimitiveRestartEnableEXT";
        case(VkDynamicState::ColorWriteEnableEXT): return "ColorWriteEnableEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPolygonMode val) {
    switch(val) {
        case(VkPolygonMode::Fill): return "Fill";
        case(VkPolygonMode::Line): return "Line";
        case(VkPolygonMode::Point): return "Point";
        case(VkPolygonMode::FillRectangleNV): return "FillRectangleNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFormat val) {
    switch(val) {
        case(VkFormat::Undefined): return "Undefined";
        case(VkFormat::R4G4UnormPack8): return "R4G4UnormPack8";
        case(VkFormat::R4G4B4A4UnormPack16): return "R4G4B4A4UnormPack16";
        case(VkFormat::B4G4R4A4UnormPack16): return "B4G4R4A4UnormPack16";
        case(VkFormat::R5G6B5UnormPack16): return "R5G6B5UnormPack16";
        case(VkFormat::B5G6R5UnormPack16): return "B5G6R5UnormPack16";
        case(VkFormat::R5G5B5A1UnormPack16): return "R5G5B5A1UnormPack16";
        case(VkFormat::B5G5R5A1UnormPack16): return "B5G5R5A1UnormPack16";
        case(VkFormat::A1R5G5B5UnormPack16): return "A1R5G5B5UnormPack16";
        case(VkFormat::R8Unorm): return "R8Unorm";
        case(VkFormat::R8Snorm): return "R8Snorm";
        case(VkFormat::R8Uscaled): return "R8Uscaled";
        case(VkFormat::R8Sscaled): return "R8Sscaled";
        case(VkFormat::R8Uint): return "R8Uint";
        case(VkFormat::R8Sint): return "R8Sint";
        case(VkFormat::R8Srgb): return "R8Srgb";
        case(VkFormat::R8G8Unorm): return "R8G8Unorm";
        case(VkFormat::R8G8Snorm): return "R8G8Snorm";
        case(VkFormat::R8G8Uscaled): return "R8G8Uscaled";
        case(VkFormat::R8G8Sscaled): return "R8G8Sscaled";
        case(VkFormat::R8G8Uint): return "R8G8Uint";
        case(VkFormat::R8G8Sint): return "R8G8Sint";
        case(VkFormat::R8G8Srgb): return "R8G8Srgb";
        case(VkFormat::R8G8B8Unorm): return "R8G8B8Unorm";
        case(VkFormat::R8G8B8Snorm): return "R8G8B8Snorm";
        case(VkFormat::R8G8B8Uscaled): return "R8G8B8Uscaled";
        case(VkFormat::R8G8B8Sscaled): return "R8G8B8Sscaled";
        case(VkFormat::R8G8B8Uint): return "R8G8B8Uint";
        case(VkFormat::R8G8B8Sint): return "R8G8B8Sint";
        case(VkFormat::R8G8B8Srgb): return "R8G8B8Srgb";
        case(VkFormat::B8G8R8Unorm): return "B8G8R8Unorm";
        case(VkFormat::B8G8R8Snorm): return "B8G8R8Snorm";
        case(VkFormat::B8G8R8Uscaled): return "B8G8R8Uscaled";
        case(VkFormat::B8G8R8Sscaled): return "B8G8R8Sscaled";
        case(VkFormat::B8G8R8Uint): return "B8G8R8Uint";
        case(VkFormat::B8G8R8Sint): return "B8G8R8Sint";
        case(VkFormat::B8G8R8Srgb): return "B8G8R8Srgb";
        case(VkFormat::R8G8B8A8Unorm): return "R8G8B8A8Unorm";
        case(VkFormat::R8G8B8A8Snorm): return "R8G8B8A8Snorm";
        case(VkFormat::R8G8B8A8Uscaled): return "R8G8B8A8Uscaled";
        case(VkFormat::R8G8B8A8Sscaled): return "R8G8B8A8Sscaled";
        case(VkFormat::R8G8B8A8Uint): return "R8G8B8A8Uint";
        case(VkFormat::R8G8B8A8Sint): return "R8G8B8A8Sint";
        case(VkFormat::R8G8B8A8Srgb): return "R8G8B8A8Srgb";
        case(VkFormat::B8G8R8A8Unorm): return "B8G8R8A8Unorm";
        case(VkFormat::B8G8R8A8Snorm): return "B8G8R8A8Snorm";
        case(VkFormat::B8G8R8A8Uscaled): return "B8G8R8A8Uscaled";
        case(VkFormat::B8G8R8A8Sscaled): return "B8G8R8A8Sscaled";
        case(VkFormat::B8G8R8A8Uint): return "B8G8R8A8Uint";
        case(VkFormat::B8G8R8A8Sint): return "B8G8R8A8Sint";
        case(VkFormat::B8G8R8A8Srgb): return "B8G8R8A8Srgb";
        case(VkFormat::A8B8G8R8UnormPack32): return "A8B8G8R8UnormPack32";
        case(VkFormat::A8B8G8R8SnormPack32): return "A8B8G8R8SnormPack32";
        case(VkFormat::A8B8G8R8UscaledPack32): return "A8B8G8R8UscaledPack32";
        case(VkFormat::A8B8G8R8SscaledPack32): return "A8B8G8R8SscaledPack32";
        case(VkFormat::A8B8G8R8UintPack32): return "A8B8G8R8UintPack32";
        case(VkFormat::A8B8G8R8SintPack32): return "A8B8G8R8SintPack32";
        case(VkFormat::A8B8G8R8SrgbPack32): return "A8B8G8R8SrgbPack32";
        case(VkFormat::A2R10G10B10UnormPack32): return "A2R10G10B10UnormPack32";
        case(VkFormat::A2R10G10B10SnormPack32): return "A2R10G10B10SnormPack32";
        case(VkFormat::A2R10G10B10UscaledPack32): return "A2R10G10B10UscaledPack32";
        case(VkFormat::A2R10G10B10SscaledPack32): return "A2R10G10B10SscaledPack32";
        case(VkFormat::A2R10G10B10UintPack32): return "A2R10G10B10UintPack32";
        case(VkFormat::A2R10G10B10SintPack32): return "A2R10G10B10SintPack32";
        case(VkFormat::A2B10G10R10UnormPack32): return "A2B10G10R10UnormPack32";
        case(VkFormat::A2B10G10R10SnormPack32): return "A2B10G10R10SnormPack32";
        case(VkFormat::A2B10G10R10UscaledPack32): return "A2B10G10R10UscaledPack32";
        case(VkFormat::A2B10G10R10SscaledPack32): return "A2B10G10R10SscaledPack32";
        case(VkFormat::A2B10G10R10UintPack32): return "A2B10G10R10UintPack32";
        case(VkFormat::A2B10G10R10SintPack32): return "A2B10G10R10SintPack32";
        case(VkFormat::R16Unorm): return "R16Unorm";
        case(VkFormat::R16Snorm): return "R16Snorm";
        case(VkFormat::R16Uscaled): return "R16Uscaled";
        case(VkFormat::R16Sscaled): return "R16Sscaled";
        case(VkFormat::R16Uint): return "R16Uint";
        case(VkFormat::R16Sint): return "R16Sint";
        case(VkFormat::R16Sfloat): return "R16Sfloat";
        case(VkFormat::R16G16Unorm): return "R16G16Unorm";
        case(VkFormat::R16G16Snorm): return "R16G16Snorm";
        case(VkFormat::R16G16Uscaled): return "R16G16Uscaled";
        case(VkFormat::R16G16Sscaled): return "R16G16Sscaled";
        case(VkFormat::R16G16Uint): return "R16G16Uint";
        case(VkFormat::R16G16Sint): return "R16G16Sint";
        case(VkFormat::R16G16Sfloat): return "R16G16Sfloat";
        case(VkFormat::R16G16B16Unorm): return "R16G16B16Unorm";
        case(VkFormat::R16G16B16Snorm): return "R16G16B16Snorm";
        case(VkFormat::R16G16B16Uscaled): return "R16G16B16Uscaled";
        case(VkFormat::R16G16B16Sscaled): return "R16G16B16Sscaled";
        case(VkFormat::R16G16B16Uint): return "R16G16B16Uint";
        case(VkFormat::R16G16B16Sint): return "R16G16B16Sint";
        case(VkFormat::R16G16B16Sfloat): return "R16G16B16Sfloat";
        case(VkFormat::R16G16B16A16Unorm): return "R16G16B16A16Unorm";
        case(VkFormat::R16G16B16A16Snorm): return "R16G16B16A16Snorm";
        case(VkFormat::R16G16B16A16Uscaled): return "R16G16B16A16Uscaled";
        case(VkFormat::R16G16B16A16Sscaled): return "R16G16B16A16Sscaled";
        case(VkFormat::R16G16B16A16Uint): return "R16G16B16A16Uint";
        case(VkFormat::R16G16B16A16Sint): return "R16G16B16A16Sint";
        case(VkFormat::R16G16B16A16Sfloat): return "R16G16B16A16Sfloat";
        case(VkFormat::R32Uint): return "R32Uint";
        case(VkFormat::R32Sint): return "R32Sint";
        case(VkFormat::R32Sfloat): return "R32Sfloat";
        case(VkFormat::R32G32Uint): return "R32G32Uint";
        case(VkFormat::R32G32Sint): return "R32G32Sint";
        case(VkFormat::R32G32Sfloat): return "R32G32Sfloat";
        case(VkFormat::R32G32B32Uint): return "R32G32B32Uint";
        case(VkFormat::R32G32B32Sint): return "R32G32B32Sint";
        case(VkFormat::R32G32B32Sfloat): return "R32G32B32Sfloat";
        case(VkFormat::R32G32B32A32Uint): return "R32G32B32A32Uint";
        case(VkFormat::R32G32B32A32Sint): return "R32G32B32A32Sint";
        case(VkFormat::R32G32B32A32Sfloat): return "R32G32B32A32Sfloat";
        case(VkFormat::R64Uint): return "R64Uint";
        case(VkFormat::R64Sint): return "R64Sint";
        case(VkFormat::R64Sfloat): return "R64Sfloat";
        case(VkFormat::R64G64Uint): return "R64G64Uint";
        case(VkFormat::R64G64Sint): return "R64G64Sint";
        case(VkFormat::R64G64Sfloat): return "R64G64Sfloat";
        case(VkFormat::R64G64B64Uint): return "R64G64B64Uint";
        case(VkFormat::R64G64B64Sint): return "R64G64B64Sint";
        case(VkFormat::R64G64B64Sfloat): return "R64G64B64Sfloat";
        case(VkFormat::R64G64B64A64Uint): return "R64G64B64A64Uint";
        case(VkFormat::R64G64B64A64Sint): return "R64G64B64A64Sint";
        case(VkFormat::R64G64B64A64Sfloat): return "R64G64B64A64Sfloat";
        case(VkFormat::B10G11R11UfloatPack32): return "B10G11R11UfloatPack32";
        case(VkFormat::E5B9G9R9UfloatPack32): return "E5B9G9R9UfloatPack32";
        case(VkFormat::D16Unorm): return "D16Unorm";
        case(VkFormat::X8D24UnormPack32): return "X8D24UnormPack32";
        case(VkFormat::D32Sfloat): return "D32Sfloat";
        case(VkFormat::S8Uint): return "S8Uint";
        case(VkFormat::D16UnormS8Uint): return "D16UnormS8Uint";
        case(VkFormat::D24UnormS8Uint): return "D24UnormS8Uint";
        case(VkFormat::D32SfloatS8Uint): return "D32SfloatS8Uint";
        case(VkFormat::Bc1RgbUnormBlock): return "Bc1RgbUnormBlock";
        case(VkFormat::Bc1RgbSrgbBlock): return "Bc1RgbSrgbBlock";
        case(VkFormat::Bc1RgbaUnormBlock): return "Bc1RgbaUnormBlock";
        case(VkFormat::Bc1RgbaSrgbBlock): return "Bc1RgbaSrgbBlock";
        case(VkFormat::Bc2UnormBlock): return "Bc2UnormBlock";
        case(VkFormat::Bc2SrgbBlock): return "Bc2SrgbBlock";
        case(VkFormat::Bc3UnormBlock): return "Bc3UnormBlock";
        case(VkFormat::Bc3SrgbBlock): return "Bc3SrgbBlock";
        case(VkFormat::Bc4UnormBlock): return "Bc4UnormBlock";
        case(VkFormat::Bc4SnormBlock): return "Bc4SnormBlock";
        case(VkFormat::Bc5UnormBlock): return "Bc5UnormBlock";
        case(VkFormat::Bc5SnormBlock): return "Bc5SnormBlock";
        case(VkFormat::Bc6HUfloatBlock): return "Bc6HUfloatBlock";
        case(VkFormat::Bc6HSfloatBlock): return "Bc6HSfloatBlock";
        case(VkFormat::Bc7UnormBlock): return "Bc7UnormBlock";
        case(VkFormat::Bc7SrgbBlock): return "Bc7SrgbBlock";
        case(VkFormat::Etc2R8G8B8UnormBlock): return "Etc2R8G8B8UnormBlock";
        case(VkFormat::Etc2R8G8B8SrgbBlock): return "Etc2R8G8B8SrgbBlock";
        case(VkFormat::Etc2R8G8B8A1UnormBlock): return "Etc2R8G8B8A1UnormBlock";
        case(VkFormat::Etc2R8G8B8A1SrgbBlock): return "Etc2R8G8B8A1SrgbBlock";
        case(VkFormat::Etc2R8G8B8A8UnormBlock): return "Etc2R8G8B8A8UnormBlock";
        case(VkFormat::Etc2R8G8B8A8SrgbBlock): return "Etc2R8G8B8A8SrgbBlock";
        case(VkFormat::EacR11UnormBlock): return "EacR11UnormBlock";
        case(VkFormat::EacR11SnormBlock): return "EacR11SnormBlock";
        case(VkFormat::EacR11G11UnormBlock): return "EacR11G11UnormBlock";
        case(VkFormat::EacR11G11SnormBlock): return "EacR11G11SnormBlock";
        case(VkFormat::Astc4X4UnormBlock): return "Astc4X4UnormBlock";
        case(VkFormat::Astc4X4SrgbBlock): return "Astc4X4SrgbBlock";
        case(VkFormat::Astc5X4UnormBlock): return "Astc5X4UnormBlock";
        case(VkFormat::Astc5X4SrgbBlock): return "Astc5X4SrgbBlock";
        case(VkFormat::Astc5X5UnormBlock): return "Astc5X5UnormBlock";
        case(VkFormat::Astc5X5SrgbBlock): return "Astc5X5SrgbBlock";
        case(VkFormat::Astc6X5UnormBlock): return "Astc6X5UnormBlock";
        case(VkFormat::Astc6X5SrgbBlock): return "Astc6X5SrgbBlock";
        case(VkFormat::Astc6X6UnormBlock): return "Astc6X6UnormBlock";
        case(VkFormat::Astc6X6SrgbBlock): return "Astc6X6SrgbBlock";
        case(VkFormat::Astc8X5UnormBlock): return "Astc8X5UnormBlock";
        case(VkFormat::Astc8X5SrgbBlock): return "Astc8X5SrgbBlock";
        case(VkFormat::Astc8X6UnormBlock): return "Astc8X6UnormBlock";
        case(VkFormat::Astc8X6SrgbBlock): return "Astc8X6SrgbBlock";
        case(VkFormat::Astc8X8UnormBlock): return "Astc8X8UnormBlock";
        case(VkFormat::Astc8X8SrgbBlock): return "Astc8X8SrgbBlock";
        case(VkFormat::Astc10X5UnormBlock): return "Astc10X5UnormBlock";
        case(VkFormat::Astc10X5SrgbBlock): return "Astc10X5SrgbBlock";
        case(VkFormat::Astc10X6UnormBlock): return "Astc10X6UnormBlock";
        case(VkFormat::Astc10X6SrgbBlock): return "Astc10X6SrgbBlock";
        case(VkFormat::Astc10X8UnormBlock): return "Astc10X8UnormBlock";
        case(VkFormat::Astc10X8SrgbBlock): return "Astc10X8SrgbBlock";
        case(VkFormat::Astc10X10UnormBlock): return "Astc10X10UnormBlock";
        case(VkFormat::Astc10X10SrgbBlock): return "Astc10X10SrgbBlock";
        case(VkFormat::Astc12X10UnormBlock): return "Astc12X10UnormBlock";
        case(VkFormat::Astc12X10SrgbBlock): return "Astc12X10SrgbBlock";
        case(VkFormat::Astc12X12UnormBlock): return "Astc12X12UnormBlock";
        case(VkFormat::Astc12X12SrgbBlock): return "Astc12X12SrgbBlock";
        case(VkFormat::Pvrtc12BppUnormBlockIMG): return "Pvrtc12BppUnormBlockIMG";
        case(VkFormat::Pvrtc14BppUnormBlockIMG): return "Pvrtc14BppUnormBlockIMG";
        case(VkFormat::Pvrtc22BppUnormBlockIMG): return "Pvrtc22BppUnormBlockIMG";
        case(VkFormat::Pvrtc24BppUnormBlockIMG): return "Pvrtc24BppUnormBlockIMG";
        case(VkFormat::Pvrtc12BppSrgbBlockIMG): return "Pvrtc12BppSrgbBlockIMG";
        case(VkFormat::Pvrtc14BppSrgbBlockIMG): return "Pvrtc14BppSrgbBlockIMG";
        case(VkFormat::Pvrtc22BppSrgbBlockIMG): return "Pvrtc22BppSrgbBlockIMG";
        case(VkFormat::Pvrtc24BppSrgbBlockIMG): return "Pvrtc24BppSrgbBlockIMG";
        case(VkFormat::Astc4X4SfloatBlockEXT): return "Astc4X4SfloatBlockEXT";
        case(VkFormat::Astc5X4SfloatBlockEXT): return "Astc5X4SfloatBlockEXT";
        case(VkFormat::Astc5X5SfloatBlockEXT): return "Astc5X5SfloatBlockEXT";
        case(VkFormat::Astc6X5SfloatBlockEXT): return "Astc6X5SfloatBlockEXT";
        case(VkFormat::Astc6X6SfloatBlockEXT): return "Astc6X6SfloatBlockEXT";
        case(VkFormat::Astc8X5SfloatBlockEXT): return "Astc8X5SfloatBlockEXT";
        case(VkFormat::Astc8X6SfloatBlockEXT): return "Astc8X6SfloatBlockEXT";
        case(VkFormat::Astc8X8SfloatBlockEXT): return "Astc8X8SfloatBlockEXT";
        case(VkFormat::Astc10X5SfloatBlockEXT): return "Astc10X5SfloatBlockEXT";
        case(VkFormat::Astc10X6SfloatBlockEXT): return "Astc10X6SfloatBlockEXT";
        case(VkFormat::Astc10X8SfloatBlockEXT): return "Astc10X8SfloatBlockEXT";
        case(VkFormat::Astc10X10SfloatBlockEXT): return "Astc10X10SfloatBlockEXT";
        case(VkFormat::Astc12X10SfloatBlockEXT): return "Astc12X10SfloatBlockEXT";
        case(VkFormat::Astc12X12SfloatBlockEXT): return "Astc12X12SfloatBlockEXT";
        case(VkFormat::G8B8R82Plane444UnormEXT): return "G8B8R82Plane444UnormEXT";
        case(VkFormat::G10X6B10X6R10X62Plane444Unorm3Pack16EXT): return "G10X6B10X6R10X62Plane444Unorm3Pack16EXT";
        case(VkFormat::G12X4B12X4R12X42Plane444Unorm3Pack16EXT): return "G12X4B12X4R12X42Plane444Unorm3Pack16EXT";
        case(VkFormat::G16B16R162Plane444UnormEXT): return "G16B16R162Plane444UnormEXT";
        case(VkFormat::A4R4G4B4UnormPack16EXT): return "A4R4G4B4UnormPack16EXT";
        case(VkFormat::A4B4G4R4UnormPack16EXT): return "A4B4G4R4UnormPack16EXT";
        case(VkFormat::G8B8G8R8422Unorm): return "G8B8G8R8422Unorm";
        case(VkFormat::B8G8R8G8422Unorm): return "B8G8R8G8422Unorm";
        case(VkFormat::G8B8R83Plane420Unorm): return "G8B8R83Plane420Unorm";
        case(VkFormat::G8B8R82Plane420Unorm): return "G8B8R82Plane420Unorm";
        case(VkFormat::G8B8R83Plane422Unorm): return "G8B8R83Plane422Unorm";
        case(VkFormat::G8B8R82Plane422Unorm): return "G8B8R82Plane422Unorm";
        case(VkFormat::G8B8R83Plane444Unorm): return "G8B8R83Plane444Unorm";
        case(VkFormat::R10X6UnormPack16): return "R10X6UnormPack16";
        case(VkFormat::R10X6G10X6Unorm2Pack16): return "R10X6G10X6Unorm2Pack16";
        case(VkFormat::R10X6G10X6B10X6A10X6Unorm4Pack16): return "R10X6G10X6B10X6A10X6Unorm4Pack16";
        case(VkFormat::G10X6B10X6G10X6R10X6422Unorm4Pack16): return "G10X6B10X6G10X6R10X6422Unorm4Pack16";
        case(VkFormat::B10X6G10X6R10X6G10X6422Unorm4Pack16): return "B10X6G10X6R10X6G10X6422Unorm4Pack16";
        case(VkFormat::G10X6B10X6R10X63Plane420Unorm3Pack16): return "G10X6B10X6R10X63Plane420Unorm3Pack16";
        case(VkFormat::G10X6B10X6R10X62Plane420Unorm3Pack16): return "G10X6B10X6R10X62Plane420Unorm3Pack16";
        case(VkFormat::G10X6B10X6R10X63Plane422Unorm3Pack16): return "G10X6B10X6R10X63Plane422Unorm3Pack16";
        case(VkFormat::G10X6B10X6R10X62Plane422Unorm3Pack16): return "G10X6B10X6R10X62Plane422Unorm3Pack16";
        case(VkFormat::G10X6B10X6R10X63Plane444Unorm3Pack16): return "G10X6B10X6R10X63Plane444Unorm3Pack16";
        case(VkFormat::R12X4UnormPack16): return "R12X4UnormPack16";
        case(VkFormat::R12X4G12X4Unorm2Pack16): return "R12X4G12X4Unorm2Pack16";
        case(VkFormat::R12X4G12X4B12X4A12X4Unorm4Pack16): return "R12X4G12X4B12X4A12X4Unorm4Pack16";
        case(VkFormat::G12X4B12X4G12X4R12X4422Unorm4Pack16): return "G12X4B12X4G12X4R12X4422Unorm4Pack16";
        case(VkFormat::B12X4G12X4R12X4G12X4422Unorm4Pack16): return "B12X4G12X4R12X4G12X4422Unorm4Pack16";
        case(VkFormat::G12X4B12X4R12X43Plane420Unorm3Pack16): return "G12X4B12X4R12X43Plane420Unorm3Pack16";
        case(VkFormat::G12X4B12X4R12X42Plane420Unorm3Pack16): return "G12X4B12X4R12X42Plane420Unorm3Pack16";
        case(VkFormat::G12X4B12X4R12X43Plane422Unorm3Pack16): return "G12X4B12X4R12X43Plane422Unorm3Pack16";
        case(VkFormat::G12X4B12X4R12X42Plane422Unorm3Pack16): return "G12X4B12X4R12X42Plane422Unorm3Pack16";
        case(VkFormat::G12X4B12X4R12X43Plane444Unorm3Pack16): return "G12X4B12X4R12X43Plane444Unorm3Pack16";
        case(VkFormat::G16B16G16R16422Unorm): return "G16B16G16R16422Unorm";
        case(VkFormat::B16G16R16G16422Unorm): return "B16G16R16G16422Unorm";
        case(VkFormat::G16B16R163Plane420Unorm): return "G16B16R163Plane420Unorm";
        case(VkFormat::G16B16R162Plane420Unorm): return "G16B16R162Plane420Unorm";
        case(VkFormat::G16B16R163Plane422Unorm): return "G16B16R163Plane422Unorm";
        case(VkFormat::G16B16R162Plane422Unorm): return "G16B16R162Plane422Unorm";
        case(VkFormat::G16B16R163Plane444Unorm): return "G16B16R163Plane444Unorm";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFrontFace val) {
    switch(val) {
        case(VkFrontFace::CounterClockwise): return "CounterClockwise";
        case(VkFrontFace::Clockwise): return "Clockwise";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkImageLayout val) {
    switch(val) {
        case(VkImageLayout::Undefined): return "Undefined";
        case(VkImageLayout::General): return "General";
        case(VkImageLayout::ColorAttachmentOptimal): return "ColorAttachmentOptimal";
        case(VkImageLayout::DepthStencilAttachmentOptimal): return "DepthStencilAttachmentOptimal";
        case(VkImageLayout::DepthStencilReadOnlyOptimal): return "DepthStencilReadOnlyOptimal";
        case(VkImageLayout::ShaderReadOnlyOptimal): return "ShaderReadOnlyOptimal";
        case(VkImageLayout::TransferSrcOptimal): return "TransferSrcOptimal";
        case(VkImageLayout::TransferDstOptimal): return "TransferDstOptimal";
        case(VkImageLayout::Preinitialized): return "Preinitialized";
        case(VkImageLayout::PresentSrcKHR): return "PresentSrcKHR";
        case(VkImageLayout::VideoDecodeDstKHR): return "VideoDecodeDstKHR";
        case(VkImageLayout::VideoDecodeSrcKHR): return "VideoDecodeSrcKHR";
        case(VkImageLayout::VideoDecodeDpbKHR): return "VideoDecodeDpbKHR";
        case(VkImageLayout::VideoEncodeDstKHR): return "VideoEncodeDstKHR";
        case(VkImageLayout::VideoEncodeSrcKHR): return "VideoEncodeSrcKHR";
        case(VkImageLayout::VideoEncodeDpbKHR): return "VideoEncodeDpbKHR";
        case(VkImageLayout::SharedPresentKHR): return "SharedPresentKHR";
        case(VkImageLayout::ShadingRateOptimalNV): return "ShadingRateOptimalNV";
        case(VkImageLayout::FragmentDensityMapOptimalEXT): return "FragmentDensityMapOptimalEXT";
        case(VkImageLayout::ReadOnlyOptimalKHR): return "ReadOnlyOptimalKHR";
        case(VkImageLayout::AttachmentOptimalKHR): return "AttachmentOptimalKHR";
        case(VkImageLayout::DepthReadOnlyStencilAttachmentOptimal): return "DepthReadOnlyStencilAttachmentOptimal";
        case(VkImageLayout::DepthAttachmentStencilReadOnlyOptimal): return "DepthAttachmentStencilReadOnlyOptimal";
        case(VkImageLayout::DepthAttachmentOptimal): return "DepthAttachmentOptimal";
        case(VkImageLayout::DepthReadOnlyOptimal): return "DepthReadOnlyOptimal";
        case(VkImageLayout::StencilAttachmentOptimal): return "StencilAttachmentOptimal";
        case(VkImageLayout::StencilReadOnlyOptimal): return "StencilReadOnlyOptimal";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkImageTiling val) {
    switch(val) {
        case(VkImageTiling::Optimal): return "Optimal";
        case(VkImageTiling::Linear): return "Linear";
        case(VkImageTiling::DrmFormatModifierEXT): return "DrmFormatModifierEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkImageType val) {
    switch(val) {
        case(VkImageType::e1D): return "e1D";
        case(VkImageType::e2D): return "e2D";
        case(VkImageType::e3D): return "e3D";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkImageViewType val) {
    switch(val) {
        case(VkImageViewType::e1D): return "e1D";
        case(VkImageViewType::e2D): return "e2D";
        case(VkImageViewType::e3D): return "e3D";
        case(VkImageViewType::Cube): return "Cube";
        case(VkImageViewType::e1DArray): return "e1DArray";
        case(VkImageViewType::e2DArray): return "e2DArray";
        case(VkImageViewType::CubeArray): return "CubeArray";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSharingMode val) {
    switch(val) {
        case(VkSharingMode::Exclusive): return "Exclusive";
        case(VkSharingMode::Concurrent): return "Concurrent";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkIndexType val) {
    switch(val) {
        case(VkIndexType::Uint16): return "Uint16";
        case(VkIndexType::Uint32): return "Uint32";
        case(VkIndexType::NoneKHR): return "NoneKHR";
        case(VkIndexType::Uint8EXT): return "Uint8EXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkLogicOp val) {
    switch(val) {
        case(VkLogicOp::Clear): return "Clear";
        case(VkLogicOp::And): return "And";
        case(VkLogicOp::AndReverse): return "AndReverse";
        case(VkLogicOp::Copy): return "Copy";
        case(VkLogicOp::AndInverted): return "AndInverted";
        case(VkLogicOp::NoOp): return "NoOp";
        case(VkLogicOp::Xor): return "Xor";
        case(VkLogicOp::Or): return "Or";
        case(VkLogicOp::Nor): return "Nor";
        case(VkLogicOp::Equivalent): return "Equivalent";
        case(VkLogicOp::Invert): return "Invert";
        case(VkLogicOp::OrReverse): return "OrReverse";
        case(VkLogicOp::CopyInverted): return "CopyInverted";
        case(VkLogicOp::OrInverted): return "OrInverted";
        case(VkLogicOp::Nand): return "Nand";
        case(VkLogicOp::Set): return "Set";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPhysicalDeviceType val) {
    switch(val) {
        case(VkPhysicalDeviceType::Other): return "Other";
        case(VkPhysicalDeviceType::IntegratedGpu): return "IntegratedGpu";
        case(VkPhysicalDeviceType::DiscreteGpu): return "DiscreteGpu";
        case(VkPhysicalDeviceType::VirtualGpu): return "VirtualGpu";
        case(VkPhysicalDeviceType::Cpu): return "Cpu";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPipelineBindPoint val) {
    switch(val) {
        case(VkPipelineBindPoint::Graphics): return "Graphics";
        case(VkPipelineBindPoint::Compute): return "Compute";
        case(VkPipelineBindPoint::RayTracingKHR): return "RayTracingKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPrimitiveTopology val) {
    switch(val) {
        case(VkPrimitiveTopology::PointList): return "PointList";
        case(VkPrimitiveTopology::LineList): return "LineList";
        case(VkPrimitiveTopology::LineStrip): return "LineStrip";
        case(VkPrimitiveTopology::TriangleList): return "TriangleList";
        case(VkPrimitiveTopology::TriangleStrip): return "TriangleStrip";
        case(VkPrimitiveTopology::TriangleFan): return "TriangleFan";
        case(VkPrimitiveTopology::LineListWithAdjacency): return "LineListWithAdjacency";
        case(VkPrimitiveTopology::LineStripWithAdjacency): return "LineStripWithAdjacency";
        case(VkPrimitiveTopology::TriangleListWithAdjacency): return "TriangleListWithAdjacency";
        case(VkPrimitiveTopology::TriangleStripWithAdjacency): return "TriangleStripWithAdjacency";
        case(VkPrimitiveTopology::PatchList): return "PatchList";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkQueryType val) {
    switch(val) {
        case(VkQueryType::Occlusion): return "Occlusion";
        case(VkQueryType::PipelineStatistics): return "PipelineStatistics";
        case(VkQueryType::Timestamp): return "Timestamp";
        case(VkQueryType::ResultStatusOnlyKHR): return "ResultStatusOnlyKHR";
        case(VkQueryType::VideoEncodeBitstreamBufferRangeKHR): return "VideoEncodeBitstreamBufferRangeKHR";
        case(VkQueryType::TransformFeedbackStreamEXT): return "TransformFeedbackStreamEXT";
        case(VkQueryType::PerformanceQueryKHR): return "PerformanceQueryKHR";
        case(VkQueryType::AccelerationStructureCompactedSizeKHR): return "AccelerationStructureCompactedSizeKHR";
        case(VkQueryType::AccelerationStructureSerializationSizeKHR): return "AccelerationStructureSerializationSizeKHR";
        case(VkQueryType::AccelerationStructureCompactedSizeNV): return "AccelerationStructureCompactedSizeNV";
        case(VkQueryType::PerformanceQueryINTEL): return "PerformanceQueryINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSubpassContents val) {
    switch(val) {
        case(VkSubpassContents::Inline): return "Inline";
        case(VkSubpassContents::SecondaryCommandBuffers): return "SecondaryCommandBuffers";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkResult val) {
    switch(val) {
        case(VkResult::Success): return "Success";
        case(VkResult::NotReady): return "NotReady";
        case(VkResult::Timeout): return "Timeout";
        case(VkResult::EventSet): return "EventSet";
        case(VkResult::EventReset): return "EventReset";
        case(VkResult::Incomplete): return "Incomplete";
        case(VkResult::ErrorOutOfHostMemory): return "ErrorOutOfHostMemory";
        case(VkResult::ErrorOutOfDeviceMemory): return "ErrorOutOfDeviceMemory";
        case(VkResult::ErrorInitializationFailed): return "ErrorInitializationFailed";
        case(VkResult::ErrorDeviceLost): return "ErrorDeviceLost";
        case(VkResult::ErrorMemoryMapFailed): return "ErrorMemoryMapFailed";
        case(VkResult::ErrorLayerNotPresent): return "ErrorLayerNotPresent";
        case(VkResult::ErrorExtensionNotPresent): return "ErrorExtensionNotPresent";
        case(VkResult::ErrorFeatureNotPresent): return "ErrorFeatureNotPresent";
        case(VkResult::ErrorIncompatibleDriver): return "ErrorIncompatibleDriver";
        case(VkResult::ErrorTooManyObjects): return "ErrorTooManyObjects";
        case(VkResult::ErrorFormatNotSupported): return "ErrorFormatNotSupported";
        case(VkResult::ErrorFragmentedPool): return "ErrorFragmentedPool";
        case(VkResult::ErrorUnknown): return "ErrorUnknown";
        case(VkResult::ErrorSurfaceLostKHR): return "ErrorSurfaceLostKHR";
        case(VkResult::ErrorNativeWindowInUseKHR): return "ErrorNativeWindowInUseKHR";
        case(VkResult::SuboptimalKHR): return "SuboptimalKHR";
        case(VkResult::ErrorOutOfDateKHR): return "ErrorOutOfDateKHR";
        case(VkResult::ErrorIncompatibleDisplayKHR): return "ErrorIncompatibleDisplayKHR";
        case(VkResult::ErrorValidationFailedEXT): return "ErrorValidationFailedEXT";
        case(VkResult::ErrorInvalidShaderNV): return "ErrorInvalidShaderNV";
        case(VkResult::ErrorInvalidDrmFormatModifierPlaneLayoutEXT): return "ErrorInvalidDrmFormatModifierPlaneLayoutEXT";
        case(VkResult::ErrorNotPermittedEXT): return "ErrorNotPermittedEXT";
        case(VkResult::ErrorFullScreenExclusiveModeLostEXT): return "ErrorFullScreenExclusiveModeLostEXT";
        case(VkResult::ThreadIdleKHR): return "ThreadIdleKHR";
        case(VkResult::ThreadDoneKHR): return "ThreadDoneKHR";
        case(VkResult::OperationDeferredKHR): return "OperationDeferredKHR";
        case(VkResult::OperationNotDeferredKHR): return "OperationNotDeferredKHR";
        case(VkResult::PipelineCompileRequiredEXT): return "PipelineCompileRequiredEXT";
        case(VkResult::ErrorOutOfPoolMemory): return "ErrorOutOfPoolMemory";
        case(VkResult::ErrorInvalidExternalHandle): return "ErrorInvalidExternalHandle";
        case(VkResult::ErrorFragmentation): return "ErrorFragmentation";
        case(VkResult::ErrorInvalidOpaqueCaptureAddress): return "ErrorInvalidOpaqueCaptureAddress";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkStencilOp val) {
    switch(val) {
        case(VkStencilOp::Keep): return "Keep";
        case(VkStencilOp::Zero): return "Zero";
        case(VkStencilOp::Replace): return "Replace";
        case(VkStencilOp::IncrementAndClamp): return "IncrementAndClamp";
        case(VkStencilOp::DecrementAndClamp): return "DecrementAndClamp";
        case(VkStencilOp::Invert): return "Invert";
        case(VkStencilOp::IncrementAndWrap): return "IncrementAndWrap";
        case(VkStencilOp::DecrementAndWrap): return "DecrementAndWrap";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkStructureType val) {
    switch(val) {
        case(VkStructureType::ApplicationInfo): return "ApplicationInfo";
        case(VkStructureType::InstanceCreateInfo): return "InstanceCreateInfo";
        case(VkStructureType::DeviceQueueCreateInfo): return "DeviceQueueCreateInfo";
        case(VkStructureType::DeviceCreateInfo): return "DeviceCreateInfo";
        case(VkStructureType::SubmitInfo): return "SubmitInfo";
        case(VkStructureType::MemoryAllocateInfo): return "MemoryAllocateInfo";
        case(VkStructureType::MappedMemoryRange): return "MappedMemoryRange";
        case(VkStructureType::BindSparseInfo): return "BindSparseInfo";
        case(VkStructureType::FenceCreateInfo): return "FenceCreateInfo";
        case(VkStructureType::SemaphoreCreateInfo): return "SemaphoreCreateInfo";
        case(VkStructureType::EventCreateInfo): return "EventCreateInfo";
        case(VkStructureType::QueryPoolCreateInfo): return "QueryPoolCreateInfo";
        case(VkStructureType::BufferCreateInfo): return "BufferCreateInfo";
        case(VkStructureType::BufferViewCreateInfo): return "BufferViewCreateInfo";
        case(VkStructureType::ImageCreateInfo): return "ImageCreateInfo";
        case(VkStructureType::ImageViewCreateInfo): return "ImageViewCreateInfo";
        case(VkStructureType::ShaderModuleCreateInfo): return "ShaderModuleCreateInfo";
        case(VkStructureType::PipelineCacheCreateInfo): return "PipelineCacheCreateInfo";
        case(VkStructureType::PipelineShaderStageCreateInfo): return "PipelineShaderStageCreateInfo";
        case(VkStructureType::PipelineVertexInputStateCreateInfo): return "PipelineVertexInputStateCreateInfo";
        case(VkStructureType::PipelineInputAssemblyStateCreateInfo): return "PipelineInputAssemblyStateCreateInfo";
        case(VkStructureType::PipelineTessellationStateCreateInfo): return "PipelineTessellationStateCreateInfo";
        case(VkStructureType::PipelineViewportStateCreateInfo): return "PipelineViewportStateCreateInfo";
        case(VkStructureType::PipelineRasterizationStateCreateInfo): return "PipelineRasterizationStateCreateInfo";
        case(VkStructureType::PipelineMultisampleStateCreateInfo): return "PipelineMultisampleStateCreateInfo";
        case(VkStructureType::PipelineDepthStencilStateCreateInfo): return "PipelineDepthStencilStateCreateInfo";
        case(VkStructureType::PipelineColorBlendStateCreateInfo): return "PipelineColorBlendStateCreateInfo";
        case(VkStructureType::PipelineDynamicStateCreateInfo): return "PipelineDynamicStateCreateInfo";
        case(VkStructureType::GraphicsPipelineCreateInfo): return "GraphicsPipelineCreateInfo";
        case(VkStructureType::ComputePipelineCreateInfo): return "ComputePipelineCreateInfo";
        case(VkStructureType::PipelineLayoutCreateInfo): return "PipelineLayoutCreateInfo";
        case(VkStructureType::SamplerCreateInfo): return "SamplerCreateInfo";
        case(VkStructureType::DescriptorSetLayoutCreateInfo): return "DescriptorSetLayoutCreateInfo";
        case(VkStructureType::DescriptorPoolCreateInfo): return "DescriptorPoolCreateInfo";
        case(VkStructureType::DescriptorSetAllocateInfo): return "DescriptorSetAllocateInfo";
        case(VkStructureType::WriteDescriptorSet): return "WriteDescriptorSet";
        case(VkStructureType::CopyDescriptorSet): return "CopyDescriptorSet";
        case(VkStructureType::FramebufferCreateInfo): return "FramebufferCreateInfo";
        case(VkStructureType::RenderPassCreateInfo): return "RenderPassCreateInfo";
        case(VkStructureType::CommandPoolCreateInfo): return "CommandPoolCreateInfo";
        case(VkStructureType::CommandBufferAllocateInfo): return "CommandBufferAllocateInfo";
        case(VkStructureType::CommandBufferInheritanceInfo): return "CommandBufferInheritanceInfo";
        case(VkStructureType::CommandBufferBeginInfo): return "CommandBufferBeginInfo";
        case(VkStructureType::RenderPassBeginInfo): return "RenderPassBeginInfo";
        case(VkStructureType::BufferMemoryBarrier): return "BufferMemoryBarrier";
        case(VkStructureType::ImageMemoryBarrier): return "ImageMemoryBarrier";
        case(VkStructureType::MemoryBarrier): return "MemoryBarrier";
        case(VkStructureType::LoaderInstanceCreateInfo): return "LoaderInstanceCreateInfo";
        case(VkStructureType::LoaderDeviceCreateInfo): return "LoaderDeviceCreateInfo";
        case(VkStructureType::SwapchainCreateInfoKHR): return "SwapchainCreateInfoKHR";
        case(VkStructureType::PresentInfoKHR): return "PresentInfoKHR";
        case(VkStructureType::DeviceGroupPresentCapabilitiesKHR): return "DeviceGroupPresentCapabilitiesKHR";
        case(VkStructureType::ImageSwapchainCreateInfoKHR): return "ImageSwapchainCreateInfoKHR";
        case(VkStructureType::BindImageMemorySwapchainInfoKHR): return "BindImageMemorySwapchainInfoKHR";
        case(VkStructureType::AcquireNextImageInfoKHR): return "AcquireNextImageInfoKHR";
        case(VkStructureType::DeviceGroupPresentInfoKHR): return "DeviceGroupPresentInfoKHR";
        case(VkStructureType::DeviceGroupSwapchainCreateInfoKHR): return "DeviceGroupSwapchainCreateInfoKHR";
        case(VkStructureType::DisplayModeCreateInfoKHR): return "DisplayModeCreateInfoKHR";
        case(VkStructureType::DisplaySurfaceCreateInfoKHR): return "DisplaySurfaceCreateInfoKHR";
        case(VkStructureType::DisplayPresentInfoKHR): return "DisplayPresentInfoKHR";
        case(VkStructureType::XlibSurfaceCreateInfoKHR): return "XlibSurfaceCreateInfoKHR";
        case(VkStructureType::XcbSurfaceCreateInfoKHR): return "XcbSurfaceCreateInfoKHR";
        case(VkStructureType::WaylandSurfaceCreateInfoKHR): return "WaylandSurfaceCreateInfoKHR";
        case(VkStructureType::AndroidSurfaceCreateInfoKHR): return "AndroidSurfaceCreateInfoKHR";
        case(VkStructureType::Win32SurfaceCreateInfoKHR): return "Win32SurfaceCreateInfoKHR";
        case(VkStructureType::DebugReportCallbackCreateInfoEXT): return "DebugReportCallbackCreateInfoEXT";
        case(VkStructureType::PipelineRasterizationStateRasterizationOrderAMD): return "PipelineRasterizationStateRasterizationOrderAMD";
        case(VkStructureType::DebugMarkerObjectNameInfoEXT): return "DebugMarkerObjectNameInfoEXT";
        case(VkStructureType::DebugMarkerObjectTagInfoEXT): return "DebugMarkerObjectTagInfoEXT";
        case(VkStructureType::DebugMarkerMarkerInfoEXT): return "DebugMarkerMarkerInfoEXT";
        case(VkStructureType::VideoProfileKHR): return "VideoProfileKHR";
        case(VkStructureType::VideoCapabilitiesKHR): return "VideoCapabilitiesKHR";
        case(VkStructureType::VideoPictureResourceKHR): return "VideoPictureResourceKHR";
        case(VkStructureType::VideoGetMemoryPropertiesKHR): return "VideoGetMemoryPropertiesKHR";
        case(VkStructureType::VideoBindMemoryKHR): return "VideoBindMemoryKHR";
        case(VkStructureType::VideoSessionCreateInfoKHR): return "VideoSessionCreateInfoKHR";
        case(VkStructureType::VideoSessionParametersCreateInfoKHR): return "VideoSessionParametersCreateInfoKHR";
        case(VkStructureType::VideoSessionParametersUpdateInfoKHR): return "VideoSessionParametersUpdateInfoKHR";
        case(VkStructureType::VideoBeginCodingInfoKHR): return "VideoBeginCodingInfoKHR";
        case(VkStructureType::VideoEndCodingInfoKHR): return "VideoEndCodingInfoKHR";
        case(VkStructureType::VideoCodingControlInfoKHR): return "VideoCodingControlInfoKHR";
        case(VkStructureType::VideoReferenceSlotKHR): return "VideoReferenceSlotKHR";
        case(VkStructureType::VideoQueueFamilyProperties2KHR): return "VideoQueueFamilyProperties2KHR";
        case(VkStructureType::VideoProfilesKHR): return "VideoProfilesKHR";
        case(VkStructureType::PhysicalDeviceVideoFormatInfoKHR): return "PhysicalDeviceVideoFormatInfoKHR";
        case(VkStructureType::VideoFormatPropertiesKHR): return "VideoFormatPropertiesKHR";
        case(VkStructureType::VideoDecodeInfoKHR): return "VideoDecodeInfoKHR";
        case(VkStructureType::VideoEncodeInfoKHR): return "VideoEncodeInfoKHR";
        case(VkStructureType::VideoEncodeRateControlInfoKHR): return "VideoEncodeRateControlInfoKHR";
        case(VkStructureType::DedicatedAllocationImageCreateInfoNV): return "DedicatedAllocationImageCreateInfoNV";
        case(VkStructureType::DedicatedAllocationBufferCreateInfoNV): return "DedicatedAllocationBufferCreateInfoNV";
        case(VkStructureType::DedicatedAllocationMemoryAllocateInfoNV): return "DedicatedAllocationMemoryAllocateInfoNV";
        case(VkStructureType::PhysicalDeviceTransformFeedbackFeaturesEXT): return "PhysicalDeviceTransformFeedbackFeaturesEXT";
        case(VkStructureType::PhysicalDeviceTransformFeedbackPropertiesEXT): return "PhysicalDeviceTransformFeedbackPropertiesEXT";
        case(VkStructureType::PipelineRasterizationStateStreamCreateInfoEXT): return "PipelineRasterizationStateStreamCreateInfoEXT";
        case(VkStructureType::ImageViewHandleInfoNVX): return "ImageViewHandleInfoNVX";
        case(VkStructureType::ImageViewAddressPropertiesNVX): return "ImageViewAddressPropertiesNVX";
        case(VkStructureType::VideoEncodeH264CapabilitiesEXT): return "VideoEncodeH264CapabilitiesEXT";
        case(VkStructureType::VideoEncodeH264SessionCreateInfoEXT): return "VideoEncodeH264SessionCreateInfoEXT";
        case(VkStructureType::VideoEncodeH264SessionParametersCreateInfoEXT): return "VideoEncodeH264SessionParametersCreateInfoEXT";
        case(VkStructureType::VideoEncodeH264SessionParametersAddInfoEXT): return "VideoEncodeH264SessionParametersAddInfoEXT";
        case(VkStructureType::VideoEncodeH264VclFrameInfoEXT): return "VideoEncodeH264VclFrameInfoEXT";
        case(VkStructureType::VideoEncodeH264DpbSlotInfoEXT): return "VideoEncodeH264DpbSlotInfoEXT";
        case(VkStructureType::VideoEncodeH264NaluSliceEXT): return "VideoEncodeH264NaluSliceEXT";
        case(VkStructureType::VideoEncodeH264EmitPictureParametersEXT): return "VideoEncodeH264EmitPictureParametersEXT";
        case(VkStructureType::VideoEncodeH264ProfileEXT): return "VideoEncodeH264ProfileEXT";
        case(VkStructureType::VideoDecodeH264CapabilitiesEXT): return "VideoDecodeH264CapabilitiesEXT";
        case(VkStructureType::VideoDecodeH264SessionCreateInfoEXT): return "VideoDecodeH264SessionCreateInfoEXT";
        case(VkStructureType::VideoDecodeH264PictureInfoEXT): return "VideoDecodeH264PictureInfoEXT";
        case(VkStructureType::VideoDecodeH264MvcEXT): return "VideoDecodeH264MvcEXT";
        case(VkStructureType::VideoDecodeH264ProfileEXT): return "VideoDecodeH264ProfileEXT";
        case(VkStructureType::VideoDecodeH264SessionParametersCreateInfoEXT): return "VideoDecodeH264SessionParametersCreateInfoEXT";
        case(VkStructureType::VideoDecodeH264SessionParametersAddInfoEXT): return "VideoDecodeH264SessionParametersAddInfoEXT";
        case(VkStructureType::VideoDecodeH264DpbSlotInfoEXT): return "VideoDecodeH264DpbSlotInfoEXT";
        case(VkStructureType::TextureLodGatherFormatPropertiesAMD): return "TextureLodGatherFormatPropertiesAMD";
        case(VkStructureType::StreamDescriptorSurfaceCreateInfoGGP): return "StreamDescriptorSurfaceCreateInfoGGP";
        case(VkStructureType::PhysicalDeviceCornerSampledImageFeaturesNV): return "PhysicalDeviceCornerSampledImageFeaturesNV";
        case(VkStructureType::ExternalMemoryImageCreateInfoNV): return "ExternalMemoryImageCreateInfoNV";
        case(VkStructureType::ExportMemoryAllocateInfoNV): return "ExportMemoryAllocateInfoNV";
        case(VkStructureType::ImportMemoryWin32HandleInfoNV): return "ImportMemoryWin32HandleInfoNV";
        case(VkStructureType::ExportMemoryWin32HandleInfoNV): return "ExportMemoryWin32HandleInfoNV";
        case(VkStructureType::Win32KeyedMutexAcquireReleaseInfoNV): return "Win32KeyedMutexAcquireReleaseInfoNV";
        case(VkStructureType::ValidationFlagsEXT): return "ValidationFlagsEXT";
        case(VkStructureType::ViSurfaceCreateInfoNN): return "ViSurfaceCreateInfoNN";
        case(VkStructureType::PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT): return "PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT";
        case(VkStructureType::ImageViewAstcDecodeModeEXT): return "ImageViewAstcDecodeModeEXT";
        case(VkStructureType::PhysicalDeviceAstcDecodeFeaturesEXT): return "PhysicalDeviceAstcDecodeFeaturesEXT";
        case(VkStructureType::ImportMemoryWin32HandleInfoKHR): return "ImportMemoryWin32HandleInfoKHR";
        case(VkStructureType::ExportMemoryWin32HandleInfoKHR): return "ExportMemoryWin32HandleInfoKHR";
        case(VkStructureType::MemoryWin32HandlePropertiesKHR): return "MemoryWin32HandlePropertiesKHR";
        case(VkStructureType::MemoryGetWin32HandleInfoKHR): return "MemoryGetWin32HandleInfoKHR";
        case(VkStructureType::ImportMemoryFdInfoKHR): return "ImportMemoryFdInfoKHR";
        case(VkStructureType::MemoryFdPropertiesKHR): return "MemoryFdPropertiesKHR";
        case(VkStructureType::MemoryGetFdInfoKHR): return "MemoryGetFdInfoKHR";
        case(VkStructureType::Win32KeyedMutexAcquireReleaseInfoKHR): return "Win32KeyedMutexAcquireReleaseInfoKHR";
        case(VkStructureType::ImportSemaphoreWin32HandleInfoKHR): return "ImportSemaphoreWin32HandleInfoKHR";
        case(VkStructureType::ExportSemaphoreWin32HandleInfoKHR): return "ExportSemaphoreWin32HandleInfoKHR";
        case(VkStructureType::D3D12FenceSubmitInfoKHR): return "D3D12FenceSubmitInfoKHR";
        case(VkStructureType::SemaphoreGetWin32HandleInfoKHR): return "SemaphoreGetWin32HandleInfoKHR";
        case(VkStructureType::ImportSemaphoreFdInfoKHR): return "ImportSemaphoreFdInfoKHR";
        case(VkStructureType::SemaphoreGetFdInfoKHR): return "SemaphoreGetFdInfoKHR";
        case(VkStructureType::PhysicalDevicePushDescriptorPropertiesKHR): return "PhysicalDevicePushDescriptorPropertiesKHR";
        case(VkStructureType::CommandBufferInheritanceConditionalRenderingInfoEXT): return "CommandBufferInheritanceConditionalRenderingInfoEXT";
        case(VkStructureType::PhysicalDeviceConditionalRenderingFeaturesEXT): return "PhysicalDeviceConditionalRenderingFeaturesEXT";
        case(VkStructureType::ConditionalRenderingBeginInfoEXT): return "ConditionalRenderingBeginInfoEXT";
        case(VkStructureType::PresentRegionsKHR): return "PresentRegionsKHR";
        case(VkStructureType::PipelineViewportWScalingStateCreateInfoNV): return "PipelineViewportWScalingStateCreateInfoNV";
        case(VkStructureType::SurfaceCapabilities2EXT): return "SurfaceCapabilities2EXT";
        case(VkStructureType::DisplayPowerInfoEXT): return "DisplayPowerInfoEXT";
        case(VkStructureType::DeviceEventInfoEXT): return "DeviceEventInfoEXT";
        case(VkStructureType::DisplayEventInfoEXT): return "DisplayEventInfoEXT";
        case(VkStructureType::SwapchainCounterCreateInfoEXT): return "SwapchainCounterCreateInfoEXT";
        case(VkStructureType::PresentTimesInfoGOOGLE): return "PresentTimesInfoGOOGLE";
        case(VkStructureType::PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX): return "PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX";
        case(VkStructureType::PipelineViewportSwizzleStateCreateInfoNV): return "PipelineViewportSwizzleStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceDiscardRectanglePropertiesEXT): return "PhysicalDeviceDiscardRectanglePropertiesEXT";
        case(VkStructureType::PipelineDiscardRectangleStateCreateInfoEXT): return "PipelineDiscardRectangleStateCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceConservativeRasterizationPropertiesEXT): return "PhysicalDeviceConservativeRasterizationPropertiesEXT";
        case(VkStructureType::PipelineRasterizationConservativeStateCreateInfoEXT): return "PipelineRasterizationConservativeStateCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceDepthClipEnableFeaturesEXT): return "PhysicalDeviceDepthClipEnableFeaturesEXT";
        case(VkStructureType::PipelineRasterizationDepthClipStateCreateInfoEXT): return "PipelineRasterizationDepthClipStateCreateInfoEXT";
        case(VkStructureType::HdrMetadataEXT): return "HdrMetadataEXT";
        case(VkStructureType::SharedPresentSurfaceCapabilitiesKHR): return "SharedPresentSurfaceCapabilitiesKHR";
        case(VkStructureType::ImportFenceWin32HandleInfoKHR): return "ImportFenceWin32HandleInfoKHR";
        case(VkStructureType::ExportFenceWin32HandleInfoKHR): return "ExportFenceWin32HandleInfoKHR";
        case(VkStructureType::FenceGetWin32HandleInfoKHR): return "FenceGetWin32HandleInfoKHR";
        case(VkStructureType::ImportFenceFdInfoKHR): return "ImportFenceFdInfoKHR";
        case(VkStructureType::FenceGetFdInfoKHR): return "FenceGetFdInfoKHR";
        case(VkStructureType::PhysicalDevicePerformanceQueryFeaturesKHR): return "PhysicalDevicePerformanceQueryFeaturesKHR";
        case(VkStructureType::PhysicalDevicePerformanceQueryPropertiesKHR): return "PhysicalDevicePerformanceQueryPropertiesKHR";
        case(VkStructureType::QueryPoolPerformanceCreateInfoKHR): return "QueryPoolPerformanceCreateInfoKHR";
        case(VkStructureType::PerformanceQuerySubmitInfoKHR): return "PerformanceQuerySubmitInfoKHR";
        case(VkStructureType::AcquireProfilingLockInfoKHR): return "AcquireProfilingLockInfoKHR";
        case(VkStructureType::PerformanceCounterKHR): return "PerformanceCounterKHR";
        case(VkStructureType::PerformanceCounterDescriptionKHR): return "PerformanceCounterDescriptionKHR";
        case(VkStructureType::PhysicalDeviceSurfaceInfo2KHR): return "PhysicalDeviceSurfaceInfo2KHR";
        case(VkStructureType::SurfaceCapabilities2KHR): return "SurfaceCapabilities2KHR";
        case(VkStructureType::SurfaceFormat2KHR): return "SurfaceFormat2KHR";
        case(VkStructureType::DisplayProperties2KHR): return "DisplayProperties2KHR";
        case(VkStructureType::DisplayPlaneProperties2KHR): return "DisplayPlaneProperties2KHR";
        case(VkStructureType::DisplayModeProperties2KHR): return "DisplayModeProperties2KHR";
        case(VkStructureType::DisplayPlaneInfo2KHR): return "DisplayPlaneInfo2KHR";
        case(VkStructureType::DisplayPlaneCapabilities2KHR): return "DisplayPlaneCapabilities2KHR";
        case(VkStructureType::IosSurfaceCreateInfoMVK): return "IosSurfaceCreateInfoMVK";
        case(VkStructureType::MacosSurfaceCreateInfoMVK): return "MacosSurfaceCreateInfoMVK";
        case(VkStructureType::DebugUtilsObjectNameInfoEXT): return "DebugUtilsObjectNameInfoEXT";
        case(VkStructureType::DebugUtilsObjectTagInfoEXT): return "DebugUtilsObjectTagInfoEXT";
        case(VkStructureType::DebugUtilsLabelEXT): return "DebugUtilsLabelEXT";
        case(VkStructureType::DebugUtilsMessengerCallbackDataEXT): return "DebugUtilsMessengerCallbackDataEXT";
        case(VkStructureType::DebugUtilsMessengerCreateInfoEXT): return "DebugUtilsMessengerCreateInfoEXT";
        case(VkStructureType::AndroidHardwareBufferUsageANDROID): return "AndroidHardwareBufferUsageANDROID";
        case(VkStructureType::AndroidHardwareBufferPropertiesANDROID): return "AndroidHardwareBufferPropertiesANDROID";
        case(VkStructureType::AndroidHardwareBufferFormatPropertiesANDROID): return "AndroidHardwareBufferFormatPropertiesANDROID";
        case(VkStructureType::ImportAndroidHardwareBufferInfoANDROID): return "ImportAndroidHardwareBufferInfoANDROID";
        case(VkStructureType::MemoryGetAndroidHardwareBufferInfoANDROID): return "MemoryGetAndroidHardwareBufferInfoANDROID";
        case(VkStructureType::ExternalFormatANDROID): return "ExternalFormatANDROID";
        case(VkStructureType::PhysicalDeviceInlineUniformBlockFeaturesEXT): return "PhysicalDeviceInlineUniformBlockFeaturesEXT";
        case(VkStructureType::PhysicalDeviceInlineUniformBlockPropertiesEXT): return "PhysicalDeviceInlineUniformBlockPropertiesEXT";
        case(VkStructureType::WriteDescriptorSetInlineUniformBlockEXT): return "WriteDescriptorSetInlineUniformBlockEXT";
        case(VkStructureType::DescriptorPoolInlineUniformBlockCreateInfoEXT): return "DescriptorPoolInlineUniformBlockCreateInfoEXT";
        case(VkStructureType::SampleLocationsInfoEXT): return "SampleLocationsInfoEXT";
        case(VkStructureType::RenderPassSampleLocationsBeginInfoEXT): return "RenderPassSampleLocationsBeginInfoEXT";
        case(VkStructureType::PipelineSampleLocationsStateCreateInfoEXT): return "PipelineSampleLocationsStateCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceSampleLocationsPropertiesEXT): return "PhysicalDeviceSampleLocationsPropertiesEXT";
        case(VkStructureType::MultisamplePropertiesEXT): return "MultisamplePropertiesEXT";
        case(VkStructureType::PhysicalDeviceBlendOperationAdvancedFeaturesEXT): return "PhysicalDeviceBlendOperationAdvancedFeaturesEXT";
        case(VkStructureType::PhysicalDeviceBlendOperationAdvancedPropertiesEXT): return "PhysicalDeviceBlendOperationAdvancedPropertiesEXT";
        case(VkStructureType::PipelineColorBlendAdvancedStateCreateInfoEXT): return "PipelineColorBlendAdvancedStateCreateInfoEXT";
        case(VkStructureType::PipelineCoverageToColorStateCreateInfoNV): return "PipelineCoverageToColorStateCreateInfoNV";
        case(VkStructureType::WriteDescriptorSetAccelerationStructureKHR): return "WriteDescriptorSetAccelerationStructureKHR";
        case(VkStructureType::AccelerationStructureBuildGeometryInfoKHR): return "AccelerationStructureBuildGeometryInfoKHR";
        case(VkStructureType::AccelerationStructureDeviceAddressInfoKHR): return "AccelerationStructureDeviceAddressInfoKHR";
        case(VkStructureType::AccelerationStructureGeometryAabbsDataKHR): return "AccelerationStructureGeometryAabbsDataKHR";
        case(VkStructureType::AccelerationStructureGeometryInstancesDataKHR): return "AccelerationStructureGeometryInstancesDataKHR";
        case(VkStructureType::AccelerationStructureGeometryTrianglesDataKHR): return "AccelerationStructureGeometryTrianglesDataKHR";
        case(VkStructureType::AccelerationStructureGeometryKHR): return "AccelerationStructureGeometryKHR";
        case(VkStructureType::AccelerationStructureVersionInfoKHR): return "AccelerationStructureVersionInfoKHR";
        case(VkStructureType::CopyAccelerationStructureInfoKHR): return "CopyAccelerationStructureInfoKHR";
        case(VkStructureType::CopyAccelerationStructureToMemoryInfoKHR): return "CopyAccelerationStructureToMemoryInfoKHR";
        case(VkStructureType::CopyMemoryToAccelerationStructureInfoKHR): return "CopyMemoryToAccelerationStructureInfoKHR";
        case(VkStructureType::PhysicalDeviceAccelerationStructureFeaturesKHR): return "PhysicalDeviceAccelerationStructureFeaturesKHR";
        case(VkStructureType::PhysicalDeviceAccelerationStructurePropertiesKHR): return "PhysicalDeviceAccelerationStructurePropertiesKHR";
        case(VkStructureType::AccelerationStructureCreateInfoKHR): return "AccelerationStructureCreateInfoKHR";
        case(VkStructureType::AccelerationStructureBuildSizesInfoKHR): return "AccelerationStructureBuildSizesInfoKHR";
        case(VkStructureType::PhysicalDeviceRayTracingPipelineFeaturesKHR): return "PhysicalDeviceRayTracingPipelineFeaturesKHR";
        case(VkStructureType::PhysicalDeviceRayTracingPipelinePropertiesKHR): return "PhysicalDeviceRayTracingPipelinePropertiesKHR";
        case(VkStructureType::RayTracingPipelineCreateInfoKHR): return "RayTracingPipelineCreateInfoKHR";
        case(VkStructureType::RayTracingShaderGroupCreateInfoKHR): return "RayTracingShaderGroupCreateInfoKHR";
        case(VkStructureType::RayTracingPipelineInterfaceCreateInfoKHR): return "RayTracingPipelineInterfaceCreateInfoKHR";
        case(VkStructureType::PhysicalDeviceRayQueryFeaturesKHR): return "PhysicalDeviceRayQueryFeaturesKHR";
        case(VkStructureType::PipelineCoverageModulationStateCreateInfoNV): return "PipelineCoverageModulationStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV): return "PhysicalDeviceShaderSmBuiltinsFeaturesNV";
        case(VkStructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV): return "PhysicalDeviceShaderSmBuiltinsPropertiesNV";
        case(VkStructureType::DrmFormatModifierPropertiesListEXT): return "DrmFormatModifierPropertiesListEXT";
        case(VkStructureType::PhysicalDeviceImageDrmFormatModifierInfoEXT): return "PhysicalDeviceImageDrmFormatModifierInfoEXT";
        case(VkStructureType::ImageDrmFormatModifierListCreateInfoEXT): return "ImageDrmFormatModifierListCreateInfoEXT";
        case(VkStructureType::ImageDrmFormatModifierExplicitCreateInfoEXT): return "ImageDrmFormatModifierExplicitCreateInfoEXT";
        case(VkStructureType::ImageDrmFormatModifierPropertiesEXT): return "ImageDrmFormatModifierPropertiesEXT";
        case(VkStructureType::ValidationCacheCreateInfoEXT): return "ValidationCacheCreateInfoEXT";
        case(VkStructureType::ShaderModuleValidationCacheCreateInfoEXT): return "ShaderModuleValidationCacheCreateInfoEXT";
        case(VkStructureType::PhysicalDevicePortabilitySubsetFeaturesKHR): return "PhysicalDevicePortabilitySubsetFeaturesKHR";
        case(VkStructureType::PhysicalDevicePortabilitySubsetPropertiesKHR): return "PhysicalDevicePortabilitySubsetPropertiesKHR";
        case(VkStructureType::PipelineViewportShadingRateImageStateCreateInfoNV): return "PipelineViewportShadingRateImageStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceShadingRateImageFeaturesNV): return "PhysicalDeviceShadingRateImageFeaturesNV";
        case(VkStructureType::PhysicalDeviceShadingRateImagePropertiesNV): return "PhysicalDeviceShadingRateImagePropertiesNV";
        case(VkStructureType::PipelineViewportCoarseSampleOrderStateCreateInfoNV): return "PipelineViewportCoarseSampleOrderStateCreateInfoNV";
        case(VkStructureType::RayTracingPipelineCreateInfoNV): return "RayTracingPipelineCreateInfoNV";
        case(VkStructureType::AccelerationStructureCreateInfoNV): return "AccelerationStructureCreateInfoNV";
        case(VkStructureType::GeometryNV): return "GeometryNV";
        case(VkStructureType::GeometryTrianglesNV): return "GeometryTrianglesNV";
        case(VkStructureType::GeometryAabbNV): return "GeometryAabbNV";
        case(VkStructureType::BindAccelerationStructureMemoryInfoNV): return "BindAccelerationStructureMemoryInfoNV";
        case(VkStructureType::WriteDescriptorSetAccelerationStructureNV): return "WriteDescriptorSetAccelerationStructureNV";
        case(VkStructureType::AccelerationStructureMemoryRequirementsInfoNV): return "AccelerationStructureMemoryRequirementsInfoNV";
        case(VkStructureType::PhysicalDeviceRayTracingPropertiesNV): return "PhysicalDeviceRayTracingPropertiesNV";
        case(VkStructureType::RayTracingShaderGroupCreateInfoNV): return "RayTracingShaderGroupCreateInfoNV";
        case(VkStructureType::AccelerationStructureInfoNV): return "AccelerationStructureInfoNV";
        case(VkStructureType::PhysicalDeviceRepresentativeFragmentTestFeaturesNV): return "PhysicalDeviceRepresentativeFragmentTestFeaturesNV";
        case(VkStructureType::PipelineRepresentativeFragmentTestStateCreateInfoNV): return "PipelineRepresentativeFragmentTestStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceImageViewImageFormatInfoEXT): return "PhysicalDeviceImageViewImageFormatInfoEXT";
        case(VkStructureType::FilterCubicImageViewImageFormatPropertiesEXT): return "FilterCubicImageViewImageFormatPropertiesEXT";
        case(VkStructureType::DeviceQueueGlobalPriorityCreateInfoEXT): return "DeviceQueueGlobalPriorityCreateInfoEXT";
        case(VkStructureType::ImportMemoryHostPointerInfoEXT): return "ImportMemoryHostPointerInfoEXT";
        case(VkStructureType::MemoryHostPointerPropertiesEXT): return "MemoryHostPointerPropertiesEXT";
        case(VkStructureType::PhysicalDeviceExternalMemoryHostPropertiesEXT): return "PhysicalDeviceExternalMemoryHostPropertiesEXT";
        case(VkStructureType::PhysicalDeviceShaderClockFeaturesKHR): return "PhysicalDeviceShaderClockFeaturesKHR";
        case(VkStructureType::PipelineCompilerControlCreateInfoAMD): return "PipelineCompilerControlCreateInfoAMD";
        case(VkStructureType::CalibratedTimestampInfoEXT): return "CalibratedTimestampInfoEXT";
        case(VkStructureType::PhysicalDeviceShaderCorePropertiesAMD): return "PhysicalDeviceShaderCorePropertiesAMD";
        case(VkStructureType::VideoDecodeH265CapabilitiesEXT): return "VideoDecodeH265CapabilitiesEXT";
        case(VkStructureType::VideoDecodeH265SessionCreateInfoEXT): return "VideoDecodeH265SessionCreateInfoEXT";
        case(VkStructureType::VideoDecodeH265SessionParametersCreateInfoEXT): return "VideoDecodeH265SessionParametersCreateInfoEXT";
        case(VkStructureType::VideoDecodeH265SessionParametersAddInfoEXT): return "VideoDecodeH265SessionParametersAddInfoEXT";
        case(VkStructureType::VideoDecodeH265ProfileEXT): return "VideoDecodeH265ProfileEXT";
        case(VkStructureType::VideoDecodeH265PictureInfoEXT): return "VideoDecodeH265PictureInfoEXT";
        case(VkStructureType::VideoDecodeH265DpbSlotInfoEXT): return "VideoDecodeH265DpbSlotInfoEXT";
        case(VkStructureType::DeviceMemoryOverallocationCreateInfoAMD): return "DeviceMemoryOverallocationCreateInfoAMD";
        case(VkStructureType::PhysicalDeviceVertexAttributeDivisorPropertiesEXT): return "PhysicalDeviceVertexAttributeDivisorPropertiesEXT";
        case(VkStructureType::PipelineVertexInputDivisorStateCreateInfoEXT): return "PipelineVertexInputDivisorStateCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceVertexAttributeDivisorFeaturesEXT): return "PhysicalDeviceVertexAttributeDivisorFeaturesEXT";
        case(VkStructureType::PresentFrameTokenGGP): return "PresentFrameTokenGGP";
        case(VkStructureType::PipelineCreationFeedbackCreateInfoEXT): return "PipelineCreationFeedbackCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceComputeShaderDerivativesFeaturesNV): return "PhysicalDeviceComputeShaderDerivativesFeaturesNV";
        case(VkStructureType::PhysicalDeviceMeshShaderFeaturesNV): return "PhysicalDeviceMeshShaderFeaturesNV";
        case(VkStructureType::PhysicalDeviceMeshShaderPropertiesNV): return "PhysicalDeviceMeshShaderPropertiesNV";
        case(VkStructureType::PhysicalDeviceFragmentShaderBarycentricFeaturesNV): return "PhysicalDeviceFragmentShaderBarycentricFeaturesNV";
        case(VkStructureType::PhysicalDeviceShaderImageFootprintFeaturesNV): return "PhysicalDeviceShaderImageFootprintFeaturesNV";
        case(VkStructureType::PipelineViewportExclusiveScissorStateCreateInfoNV): return "PipelineViewportExclusiveScissorStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceExclusiveScissorFeaturesNV): return "PhysicalDeviceExclusiveScissorFeaturesNV";
        case(VkStructureType::CheckpointDataNV): return "CheckpointDataNV";
        case(VkStructureType::QueueFamilyCheckpointPropertiesNV): return "QueueFamilyCheckpointPropertiesNV";
        case(VkStructureType::PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL): return "PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL";
        case(VkStructureType::QueryPoolPerformanceQueryCreateInfoINTEL): return "QueryPoolPerformanceQueryCreateInfoINTEL";
        case(VkStructureType::InitializePerformanceApiInfoINTEL): return "InitializePerformanceApiInfoINTEL";
        case(VkStructureType::PerformanceMarkerInfoINTEL): return "PerformanceMarkerInfoINTEL";
        case(VkStructureType::PerformanceStreamMarkerInfoINTEL): return "PerformanceStreamMarkerInfoINTEL";
        case(VkStructureType::PerformanceOverrideInfoINTEL): return "PerformanceOverrideInfoINTEL";
        case(VkStructureType::PerformanceConfigurationAcquireInfoINTEL): return "PerformanceConfigurationAcquireInfoINTEL";
        case(VkStructureType::PhysicalDevicePciBusInfoPropertiesEXT): return "PhysicalDevicePciBusInfoPropertiesEXT";
        case(VkStructureType::DisplayNativeHdrSurfaceCapabilitiesAMD): return "DisplayNativeHdrSurfaceCapabilitiesAMD";
        case(VkStructureType::SwapchainDisplayNativeHdrCreateInfoAMD): return "SwapchainDisplayNativeHdrCreateInfoAMD";
        case(VkStructureType::ImagepipeSurfaceCreateInfoFUCHSIA): return "ImagepipeSurfaceCreateInfoFUCHSIA";
        case(VkStructureType::PhysicalDeviceShaderTerminateInvocationFeaturesKHR): return "PhysicalDeviceShaderTerminateInvocationFeaturesKHR";
        case(VkStructureType::MetalSurfaceCreateInfoEXT): return "MetalSurfaceCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT): return "PhysicalDeviceFragmentDensityMapFeaturesEXT";
        case(VkStructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT): return "PhysicalDeviceFragmentDensityMapPropertiesEXT";
        case(VkStructureType::RenderPassFragmentDensityMapCreateInfoEXT): return "RenderPassFragmentDensityMapCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT): return "PhysicalDeviceSubgroupSizeControlPropertiesEXT";
        case(VkStructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT): return "PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT): return "PhysicalDeviceSubgroupSizeControlFeaturesEXT";
        case(VkStructureType::FragmentShadingRateAttachmentInfoKHR): return "FragmentShadingRateAttachmentInfoKHR";
        case(VkStructureType::PipelineFragmentShadingRateStateCreateInfoKHR): return "PipelineFragmentShadingRateStateCreateInfoKHR";
        case(VkStructureType::PhysicalDeviceFragmentShadingRatePropertiesKHR): return "PhysicalDeviceFragmentShadingRatePropertiesKHR";
        case(VkStructureType::PhysicalDeviceFragmentShadingRateFeaturesKHR): return "PhysicalDeviceFragmentShadingRateFeaturesKHR";
        case(VkStructureType::PhysicalDeviceFragmentShadingRateKHR): return "PhysicalDeviceFragmentShadingRateKHR";
        case(VkStructureType::PhysicalDeviceShaderCoreProperties2AMD): return "PhysicalDeviceShaderCoreProperties2AMD";
        case(VkStructureType::PhysicalDeviceCoherentMemoryFeaturesAMD): return "PhysicalDeviceCoherentMemoryFeaturesAMD";
        case(VkStructureType::PhysicalDeviceShaderImageAtomicInt64FeaturesEXT): return "PhysicalDeviceShaderImageAtomicInt64FeaturesEXT";
        case(VkStructureType::PhysicalDeviceMemoryBudgetPropertiesEXT): return "PhysicalDeviceMemoryBudgetPropertiesEXT";
        case(VkStructureType::PhysicalDeviceMemoryPriorityFeaturesEXT): return "PhysicalDeviceMemoryPriorityFeaturesEXT";
        case(VkStructureType::MemoryPriorityAllocateInfoEXT): return "MemoryPriorityAllocateInfoEXT";
        case(VkStructureType::SurfaceProtectedCapabilitiesKHR): return "SurfaceProtectedCapabilitiesKHR";
        case(VkStructureType::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV): return "PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV";
        case(VkStructureType::PhysicalDeviceBufferDeviceAddressFeaturesEXT): return "PhysicalDeviceBufferDeviceAddressFeaturesEXT";
        case(VkStructureType::BufferDeviceAddressCreateInfoEXT): return "BufferDeviceAddressCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceToolPropertiesEXT): return "PhysicalDeviceToolPropertiesEXT";
        case(VkStructureType::ValidationFeaturesEXT): return "ValidationFeaturesEXT";
        case(VkStructureType::PhysicalDeviceCooperativeMatrixFeaturesNV): return "PhysicalDeviceCooperativeMatrixFeaturesNV";
        case(VkStructureType::CooperativeMatrixPropertiesNV): return "CooperativeMatrixPropertiesNV";
        case(VkStructureType::PhysicalDeviceCooperativeMatrixPropertiesNV): return "PhysicalDeviceCooperativeMatrixPropertiesNV";
        case(VkStructureType::PhysicalDeviceCoverageReductionModeFeaturesNV): return "PhysicalDeviceCoverageReductionModeFeaturesNV";
        case(VkStructureType::PipelineCoverageReductionStateCreateInfoNV): return "PipelineCoverageReductionStateCreateInfoNV";
        case(VkStructureType::FramebufferMixedSamplesCombinationNV): return "FramebufferMixedSamplesCombinationNV";
        case(VkStructureType::PhysicalDeviceFragmentShaderInterlockFeaturesEXT): return "PhysicalDeviceFragmentShaderInterlockFeaturesEXT";
        case(VkStructureType::PhysicalDeviceYcbcrImageArraysFeaturesEXT): return "PhysicalDeviceYcbcrImageArraysFeaturesEXT";
        case(VkStructureType::SurfaceFullScreenExclusiveInfoEXT): return "SurfaceFullScreenExclusiveInfoEXT";
        case(VkStructureType::SurfaceCapabilitiesFullScreenExclusiveEXT): return "SurfaceCapabilitiesFullScreenExclusiveEXT";
        case(VkStructureType::SurfaceFullScreenExclusiveWin32InfoEXT): return "SurfaceFullScreenExclusiveWin32InfoEXT";
        case(VkStructureType::HeadlessSurfaceCreateInfoEXT): return "HeadlessSurfaceCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceLineRasterizationFeaturesEXT): return "PhysicalDeviceLineRasterizationFeaturesEXT";
        case(VkStructureType::PipelineRasterizationLineStateCreateInfoEXT): return "PipelineRasterizationLineStateCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceLineRasterizationPropertiesEXT): return "PhysicalDeviceLineRasterizationPropertiesEXT";
        case(VkStructureType::PhysicalDeviceShaderAtomicFloatFeaturesEXT): return "PhysicalDeviceShaderAtomicFloatFeaturesEXT";
        case(VkStructureType::PhysicalDeviceIndexTypeUint8FeaturesEXT): return "PhysicalDeviceIndexTypeUint8FeaturesEXT";
        case(VkStructureType::PhysicalDeviceExtendedDynamicStateFeaturesEXT): return "PhysicalDeviceExtendedDynamicStateFeaturesEXT";
        case(VkStructureType::PhysicalDevicePipelineExecutablePropertiesFeaturesKHR): return "PhysicalDevicePipelineExecutablePropertiesFeaturesKHR";
        case(VkStructureType::PipelineInfoKHR): return "PipelineInfoKHR";
        case(VkStructureType::PipelineExecutablePropertiesKHR): return "PipelineExecutablePropertiesKHR";
        case(VkStructureType::PipelineExecutableInfoKHR): return "PipelineExecutableInfoKHR";
        case(VkStructureType::PipelineExecutableStatisticKHR): return "PipelineExecutableStatisticKHR";
        case(VkStructureType::PipelineExecutableInternalRepresentationKHR): return "PipelineExecutableInternalRepresentationKHR";
        case(VkStructureType::PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT): return "PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT";
        case(VkStructureType::PhysicalDeviceDeviceGeneratedCommandsPropertiesNV): return "PhysicalDeviceDeviceGeneratedCommandsPropertiesNV";
        case(VkStructureType::GraphicsShaderGroupCreateInfoNV): return "GraphicsShaderGroupCreateInfoNV";
        case(VkStructureType::GraphicsPipelineShaderGroupsCreateInfoNV): return "GraphicsPipelineShaderGroupsCreateInfoNV";
        case(VkStructureType::IndirectCommandsLayoutTokenNV): return "IndirectCommandsLayoutTokenNV";
        case(VkStructureType::IndirectCommandsLayoutCreateInfoNV): return "IndirectCommandsLayoutCreateInfoNV";
        case(VkStructureType::GeneratedCommandsInfoNV): return "GeneratedCommandsInfoNV";
        case(VkStructureType::GeneratedCommandsMemoryRequirementsInfoNV): return "GeneratedCommandsMemoryRequirementsInfoNV";
        case(VkStructureType::PhysicalDeviceDeviceGeneratedCommandsFeaturesNV): return "PhysicalDeviceDeviceGeneratedCommandsFeaturesNV";
        case(VkStructureType::PhysicalDeviceInheritedViewportScissorFeaturesNV): return "PhysicalDeviceInheritedViewportScissorFeaturesNV";
        case(VkStructureType::CommandBufferInheritanceViewportScissorInfoNV): return "CommandBufferInheritanceViewportScissorInfoNV";
        case(VkStructureType::PhysicalDeviceTexelBufferAlignmentFeaturesEXT): return "PhysicalDeviceTexelBufferAlignmentFeaturesEXT";
        case(VkStructureType::PhysicalDeviceTexelBufferAlignmentPropertiesEXT): return "PhysicalDeviceTexelBufferAlignmentPropertiesEXT";
        case(VkStructureType::CommandBufferInheritanceRenderPassTransformInfoQCOM): return "CommandBufferInheritanceRenderPassTransformInfoQCOM";
        case(VkStructureType::RenderPassTransformBeginInfoQCOM): return "RenderPassTransformBeginInfoQCOM";
        case(VkStructureType::PhysicalDeviceDeviceMemoryReportFeaturesEXT): return "PhysicalDeviceDeviceMemoryReportFeaturesEXT";
        case(VkStructureType::DeviceDeviceMemoryReportCreateInfoEXT): return "DeviceDeviceMemoryReportCreateInfoEXT";
        case(VkStructureType::DeviceMemoryReportCallbackDataEXT): return "DeviceMemoryReportCallbackDataEXT";
        case(VkStructureType::PhysicalDeviceRobustness2FeaturesEXT): return "PhysicalDeviceRobustness2FeaturesEXT";
        case(VkStructureType::PhysicalDeviceRobustness2PropertiesEXT): return "PhysicalDeviceRobustness2PropertiesEXT";
        case(VkStructureType::SamplerCustomBorderColorCreateInfoEXT): return "SamplerCustomBorderColorCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceCustomBorderColorPropertiesEXT): return "PhysicalDeviceCustomBorderColorPropertiesEXT";
        case(VkStructureType::PhysicalDeviceCustomBorderColorFeaturesEXT): return "PhysicalDeviceCustomBorderColorFeaturesEXT";
        case(VkStructureType::PipelineLibraryCreateInfoKHR): return "PipelineLibraryCreateInfoKHR";
        case(VkStructureType::PhysicalDevicePrivateDataFeaturesEXT): return "PhysicalDevicePrivateDataFeaturesEXT";
        case(VkStructureType::DevicePrivateDataCreateInfoEXT): return "DevicePrivateDataCreateInfoEXT";
        case(VkStructureType::PrivateDataSlotCreateInfoEXT): return "PrivateDataSlotCreateInfoEXT";
        case(VkStructureType::PhysicalDevicePipelineCreationCacheControlFeaturesEXT): return "PhysicalDevicePipelineCreationCacheControlFeaturesEXT";
        case(VkStructureType::PhysicalDeviceDiagnosticsConfigFeaturesNV): return "PhysicalDeviceDiagnosticsConfigFeaturesNV";
        case(VkStructureType::DeviceDiagnosticsConfigCreateInfoNV): return "DeviceDiagnosticsConfigCreateInfoNV";
        case(VkStructureType::MemoryBarrier2KHR): return "MemoryBarrier2KHR";
        case(VkStructureType::BufferMemoryBarrier2KHR): return "BufferMemoryBarrier2KHR";
        case(VkStructureType::ImageMemoryBarrier2KHR): return "ImageMemoryBarrier2KHR";
        case(VkStructureType::DependencyInfoKHR): return "DependencyInfoKHR";
        case(VkStructureType::SubmitInfo2KHR): return "SubmitInfo2KHR";
        case(VkStructureType::SemaphoreSubmitInfoKHR): return "SemaphoreSubmitInfoKHR";
        case(VkStructureType::CommandBufferSubmitInfoKHR): return "CommandBufferSubmitInfoKHR";
        case(VkStructureType::PhysicalDeviceSynchronization2FeaturesKHR): return "PhysicalDeviceSynchronization2FeaturesKHR";
        case(VkStructureType::QueueFamilyCheckpointProperties2NV): return "QueueFamilyCheckpointProperties2NV";
        case(VkStructureType::CheckpointData2NV): return "CheckpointData2NV";
        case(VkStructureType::PhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR): return "PhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR";
        case(VkStructureType::PhysicalDeviceFragmentShadingRateEnumsPropertiesNV): return "PhysicalDeviceFragmentShadingRateEnumsPropertiesNV";
        case(VkStructureType::PhysicalDeviceFragmentShadingRateEnumsFeaturesNV): return "PhysicalDeviceFragmentShadingRateEnumsFeaturesNV";
        case(VkStructureType::PipelineFragmentShadingRateEnumStateCreateInfoNV): return "PipelineFragmentShadingRateEnumStateCreateInfoNV";
        case(VkStructureType::PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT): return "PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT";
        case(VkStructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT): return "PhysicalDeviceFragmentDensityMap2FeaturesEXT";
        case(VkStructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT): return "PhysicalDeviceFragmentDensityMap2PropertiesEXT";
        case(VkStructureType::CopyCommandTransformInfoQCOM): return "CopyCommandTransformInfoQCOM";
        case(VkStructureType::PhysicalDeviceImageRobustnessFeaturesEXT): return "PhysicalDeviceImageRobustnessFeaturesEXT";
        case(VkStructureType::PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR): return "PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR";
        case(VkStructureType::CopyBufferInfo2KHR): return "CopyBufferInfo2KHR";
        case(VkStructureType::CopyImageInfo2KHR): return "CopyImageInfo2KHR";
        case(VkStructureType::CopyBufferToImageInfo2KHR): return "CopyBufferToImageInfo2KHR";
        case(VkStructureType::CopyImageToBufferInfo2KHR): return "CopyImageToBufferInfo2KHR";
        case(VkStructureType::BlitImageInfo2KHR): return "BlitImageInfo2KHR";
        case(VkStructureType::ResolveImageInfo2KHR): return "ResolveImageInfo2KHR";
        case(VkStructureType::BufferCopy2KHR): return "BufferCopy2KHR";
        case(VkStructureType::ImageCopy2KHR): return "ImageCopy2KHR";
        case(VkStructureType::ImageBlit2KHR): return "ImageBlit2KHR";
        case(VkStructureType::BufferImageCopy2KHR): return "BufferImageCopy2KHR";
        case(VkStructureType::ImageResolve2KHR): return "ImageResolve2KHR";
        case(VkStructureType::PhysicalDevice4444FormatsFeaturesEXT): return "PhysicalDevice4444FormatsFeaturesEXT";
        case(VkStructureType::DirectfbSurfaceCreateInfoEXT): return "DirectfbSurfaceCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceMutableDescriptorTypeFeaturesVALVE): return "PhysicalDeviceMutableDescriptorTypeFeaturesVALVE";
        case(VkStructureType::MutableDescriptorTypeCreateInfoVALVE): return "MutableDescriptorTypeCreateInfoVALVE";
        case(VkStructureType::PhysicalDeviceVertexInputDynamicStateFeaturesEXT): return "PhysicalDeviceVertexInputDynamicStateFeaturesEXT";
        case(VkStructureType::VertexInputBindingDescription2EXT): return "VertexInputBindingDescription2EXT";
        case(VkStructureType::VertexInputAttributeDescription2EXT): return "VertexInputAttributeDescription2EXT";
        case(VkStructureType::ImportMemoryZirconHandleInfoFUCHSIA): return "ImportMemoryZirconHandleInfoFUCHSIA";
        case(VkStructureType::MemoryZirconHandlePropertiesFUCHSIA): return "MemoryZirconHandlePropertiesFUCHSIA";
        case(VkStructureType::MemoryGetZirconHandleInfoFUCHSIA): return "MemoryGetZirconHandleInfoFUCHSIA";
        case(VkStructureType::ImportSemaphoreZirconHandleInfoFUCHSIA): return "ImportSemaphoreZirconHandleInfoFUCHSIA";
        case(VkStructureType::SemaphoreGetZirconHandleInfoFUCHSIA): return "SemaphoreGetZirconHandleInfoFUCHSIA";
        case(VkStructureType::PhysicalDeviceExtendedDynamicState2FeaturesEXT): return "PhysicalDeviceExtendedDynamicState2FeaturesEXT";
        case(VkStructureType::ScreenSurfaceCreateInfoQNX): return "ScreenSurfaceCreateInfoQNX";
        case(VkStructureType::PhysicalDeviceColorWriteEnableFeaturesEXT): return "PhysicalDeviceColorWriteEnableFeaturesEXT";
        case(VkStructureType::PipelineColorWriteCreateInfoEXT): return "PipelineColorWriteCreateInfoEXT";
        case(VkStructureType::PhysicalDeviceSubgroupProperties): return "PhysicalDeviceSubgroupProperties";
        case(VkStructureType::BindBufferMemoryInfo): return "BindBufferMemoryInfo";
        case(VkStructureType::BindImageMemoryInfo): return "BindImageMemoryInfo";
        case(VkStructureType::PhysicalDevice16BitStorageFeatures): return "PhysicalDevice16BitStorageFeatures";
        case(VkStructureType::MemoryDedicatedRequirements): return "MemoryDedicatedRequirements";
        case(VkStructureType::MemoryDedicatedAllocateInfo): return "MemoryDedicatedAllocateInfo";
        case(VkStructureType::MemoryAllocateFlagsInfo): return "MemoryAllocateFlagsInfo";
        case(VkStructureType::DeviceGroupRenderPassBeginInfo): return "DeviceGroupRenderPassBeginInfo";
        case(VkStructureType::DeviceGroupCommandBufferBeginInfo): return "DeviceGroupCommandBufferBeginInfo";
        case(VkStructureType::DeviceGroupSubmitInfo): return "DeviceGroupSubmitInfo";
        case(VkStructureType::DeviceGroupBindSparseInfo): return "DeviceGroupBindSparseInfo";
        case(VkStructureType::BindBufferMemoryDeviceGroupInfo): return "BindBufferMemoryDeviceGroupInfo";
        case(VkStructureType::BindImageMemoryDeviceGroupInfo): return "BindImageMemoryDeviceGroupInfo";
        case(VkStructureType::PhysicalDeviceGroupProperties): return "PhysicalDeviceGroupProperties";
        case(VkStructureType::DeviceGroupDeviceCreateInfo): return "DeviceGroupDeviceCreateInfo";
        case(VkStructureType::BufferMemoryRequirementsInfo2): return "BufferMemoryRequirementsInfo2";
        case(VkStructureType::ImageMemoryRequirementsInfo2): return "ImageMemoryRequirementsInfo2";
        case(VkStructureType::ImageSparseMemoryRequirementsInfo2): return "ImageSparseMemoryRequirementsInfo2";
        case(VkStructureType::MemoryRequirements2): return "MemoryRequirements2";
        case(VkStructureType::SparseImageMemoryRequirements2): return "SparseImageMemoryRequirements2";
        case(VkStructureType::PhysicalDeviceFeatures2): return "PhysicalDeviceFeatures2";
        case(VkStructureType::PhysicalDeviceProperties2): return "PhysicalDeviceProperties2";
        case(VkStructureType::FormatProperties2): return "FormatProperties2";
        case(VkStructureType::ImageFormatProperties2): return "ImageFormatProperties2";
        case(VkStructureType::PhysicalDeviceImageFormatInfo2): return "PhysicalDeviceImageFormatInfo2";
        case(VkStructureType::QueueFamilyProperties2): return "QueueFamilyProperties2";
        case(VkStructureType::PhysicalDeviceMemoryProperties2): return "PhysicalDeviceMemoryProperties2";
        case(VkStructureType::SparseImageFormatProperties2): return "SparseImageFormatProperties2";
        case(VkStructureType::PhysicalDeviceSparseImageFormatInfo2): return "PhysicalDeviceSparseImageFormatInfo2";
        case(VkStructureType::PhysicalDevicePointClippingProperties): return "PhysicalDevicePointClippingProperties";
        case(VkStructureType::RenderPassInputAttachmentAspectCreateInfo): return "RenderPassInputAttachmentAspectCreateInfo";
        case(VkStructureType::ImageViewUsageCreateInfo): return "ImageViewUsageCreateInfo";
        case(VkStructureType::PipelineTessellationDomainOriginStateCreateInfo): return "PipelineTessellationDomainOriginStateCreateInfo";
        case(VkStructureType::RenderPassMultiviewCreateInfo): return "RenderPassMultiviewCreateInfo";
        case(VkStructureType::PhysicalDeviceMultiviewFeatures): return "PhysicalDeviceMultiviewFeatures";
        case(VkStructureType::PhysicalDeviceMultiviewProperties): return "PhysicalDeviceMultiviewProperties";
        case(VkStructureType::PhysicalDeviceVariablePointersFeatures): return "PhysicalDeviceVariablePointersFeatures";
        case(VkStructureType::ProtectedSubmitInfo): return "ProtectedSubmitInfo";
        case(VkStructureType::PhysicalDeviceProtectedMemoryFeatures): return "PhysicalDeviceProtectedMemoryFeatures";
        case(VkStructureType::PhysicalDeviceProtectedMemoryProperties): return "PhysicalDeviceProtectedMemoryProperties";
        case(VkStructureType::DeviceQueueInfo2): return "DeviceQueueInfo2";
        case(VkStructureType::SamplerYcbcrConversionCreateInfo): return "SamplerYcbcrConversionCreateInfo";
        case(VkStructureType::SamplerYcbcrConversionInfo): return "SamplerYcbcrConversionInfo";
        case(VkStructureType::BindImagePlaneMemoryInfo): return "BindImagePlaneMemoryInfo";
        case(VkStructureType::ImagePlaneMemoryRequirementsInfo): return "ImagePlaneMemoryRequirementsInfo";
        case(VkStructureType::PhysicalDeviceSamplerYcbcrConversionFeatures): return "PhysicalDeviceSamplerYcbcrConversionFeatures";
        case(VkStructureType::SamplerYcbcrConversionImageFormatProperties): return "SamplerYcbcrConversionImageFormatProperties";
        case(VkStructureType::DescriptorUpdateTemplateCreateInfo): return "DescriptorUpdateTemplateCreateInfo";
        case(VkStructureType::PhysicalDeviceExternalImageFormatInfo): return "PhysicalDeviceExternalImageFormatInfo";
        case(VkStructureType::ExternalImageFormatProperties): return "ExternalImageFormatProperties";
        case(VkStructureType::PhysicalDeviceExternalBufferInfo): return "PhysicalDeviceExternalBufferInfo";
        case(VkStructureType::ExternalBufferProperties): return "ExternalBufferProperties";
        case(VkStructureType::PhysicalDeviceIdProperties): return "PhysicalDeviceIdProperties";
        case(VkStructureType::ExternalMemoryBufferCreateInfo): return "ExternalMemoryBufferCreateInfo";
        case(VkStructureType::ExternalMemoryImageCreateInfo): return "ExternalMemoryImageCreateInfo";
        case(VkStructureType::ExportMemoryAllocateInfo): return "ExportMemoryAllocateInfo";
        case(VkStructureType::PhysicalDeviceExternalFenceInfo): return "PhysicalDeviceExternalFenceInfo";
        case(VkStructureType::ExternalFenceProperties): return "ExternalFenceProperties";
        case(VkStructureType::ExportFenceCreateInfo): return "ExportFenceCreateInfo";
        case(VkStructureType::ExportSemaphoreCreateInfo): return "ExportSemaphoreCreateInfo";
        case(VkStructureType::PhysicalDeviceExternalSemaphoreInfo): return "PhysicalDeviceExternalSemaphoreInfo";
        case(VkStructureType::ExternalSemaphoreProperties): return "ExternalSemaphoreProperties";
        case(VkStructureType::PhysicalDeviceMaintenance3Properties): return "PhysicalDeviceMaintenance3Properties";
        case(VkStructureType::DescriptorSetLayoutSupport): return "DescriptorSetLayoutSupport";
        case(VkStructureType::PhysicalDeviceShaderDrawParametersFeatures): return "PhysicalDeviceShaderDrawParametersFeatures";
        case(VkStructureType::PhysicalDeviceVulkan11Features): return "PhysicalDeviceVulkan11Features";
        case(VkStructureType::PhysicalDeviceVulkan11Properties): return "PhysicalDeviceVulkan11Properties";
        case(VkStructureType::PhysicalDeviceVulkan12Features): return "PhysicalDeviceVulkan12Features";
        case(VkStructureType::PhysicalDeviceVulkan12Properties): return "PhysicalDeviceVulkan12Properties";
        case(VkStructureType::ImageFormatListCreateInfo): return "ImageFormatListCreateInfo";
        case(VkStructureType::AttachmentDescription2): return "AttachmentDescription2";
        case(VkStructureType::AttachmentReference2): return "AttachmentReference2";
        case(VkStructureType::SubpassDescription2): return "SubpassDescription2";
        case(VkStructureType::SubpassDependency2): return "SubpassDependency2";
        case(VkStructureType::RenderPassCreateInfo2): return "RenderPassCreateInfo2";
        case(VkStructureType::SubpassBeginInfo): return "SubpassBeginInfo";
        case(VkStructureType::SubpassEndInfo): return "SubpassEndInfo";
        case(VkStructureType::PhysicalDevice8BitStorageFeatures): return "PhysicalDevice8BitStorageFeatures";
        case(VkStructureType::PhysicalDeviceDriverProperties): return "PhysicalDeviceDriverProperties";
        case(VkStructureType::PhysicalDeviceShaderAtomicInt64Features): return "PhysicalDeviceShaderAtomicInt64Features";
        case(VkStructureType::PhysicalDeviceShaderFloat16Int8Features): return "PhysicalDeviceShaderFloat16Int8Features";
        case(VkStructureType::PhysicalDeviceFloatControlsProperties): return "PhysicalDeviceFloatControlsProperties";
        case(VkStructureType::DescriptorSetLayoutBindingFlagsCreateInfo): return "DescriptorSetLayoutBindingFlagsCreateInfo";
        case(VkStructureType::PhysicalDeviceDescriptorIndexingFeatures): return "PhysicalDeviceDescriptorIndexingFeatures";
        case(VkStructureType::PhysicalDeviceDescriptorIndexingProperties): return "PhysicalDeviceDescriptorIndexingProperties";
        case(VkStructureType::DescriptorSetVariableDescriptorCountAllocateInfo): return "DescriptorSetVariableDescriptorCountAllocateInfo";
        case(VkStructureType::DescriptorSetVariableDescriptorCountLayoutSupport): return "DescriptorSetVariableDescriptorCountLayoutSupport";
        case(VkStructureType::PhysicalDeviceDepthStencilResolveProperties): return "PhysicalDeviceDepthStencilResolveProperties";
        case(VkStructureType::SubpassDescriptionDepthStencilResolve): return "SubpassDescriptionDepthStencilResolve";
        case(VkStructureType::PhysicalDeviceScalarBlockLayoutFeatures): return "PhysicalDeviceScalarBlockLayoutFeatures";
        case(VkStructureType::ImageStencilUsageCreateInfo): return "ImageStencilUsageCreateInfo";
        case(VkStructureType::PhysicalDeviceSamplerFilterMinmaxProperties): return "PhysicalDeviceSamplerFilterMinmaxProperties";
        case(VkStructureType::SamplerReductionModeCreateInfo): return "SamplerReductionModeCreateInfo";
        case(VkStructureType::PhysicalDeviceVulkanMemoryModelFeatures): return "PhysicalDeviceVulkanMemoryModelFeatures";
        case(VkStructureType::PhysicalDeviceImagelessFramebufferFeatures): return "PhysicalDeviceImagelessFramebufferFeatures";
        case(VkStructureType::FramebufferAttachmentsCreateInfo): return "FramebufferAttachmentsCreateInfo";
        case(VkStructureType::FramebufferAttachmentImageInfo): return "FramebufferAttachmentImageInfo";
        case(VkStructureType::RenderPassAttachmentBeginInfo): return "RenderPassAttachmentBeginInfo";
        case(VkStructureType::PhysicalDeviceUniformBufferStandardLayoutFeatures): return "PhysicalDeviceUniformBufferStandardLayoutFeatures";
        case(VkStructureType::PhysicalDeviceShaderSubgroupExtendedTypesFeatures): return "PhysicalDeviceShaderSubgroupExtendedTypesFeatures";
        case(VkStructureType::PhysicalDeviceSeparateDepthStencilLayoutsFeatures): return "PhysicalDeviceSeparateDepthStencilLayoutsFeatures";
        case(VkStructureType::AttachmentReferenceStencilLayout): return "AttachmentReferenceStencilLayout";
        case(VkStructureType::AttachmentDescriptionStencilLayout): return "AttachmentDescriptionStencilLayout";
        case(VkStructureType::PhysicalDeviceHostQueryResetFeatures): return "PhysicalDeviceHostQueryResetFeatures";
        case(VkStructureType::PhysicalDeviceTimelineSemaphoreFeatures): return "PhysicalDeviceTimelineSemaphoreFeatures";
        case(VkStructureType::PhysicalDeviceTimelineSemaphoreProperties): return "PhysicalDeviceTimelineSemaphoreProperties";
        case(VkStructureType::SemaphoreTypeCreateInfo): return "SemaphoreTypeCreateInfo";
        case(VkStructureType::TimelineSemaphoreSubmitInfo): return "TimelineSemaphoreSubmitInfo";
        case(VkStructureType::SemaphoreWaitInfo): return "SemaphoreWaitInfo";
        case(VkStructureType::SemaphoreSignalInfo): return "SemaphoreSignalInfo";
        case(VkStructureType::PhysicalDeviceBufferDeviceAddressFeatures): return "PhysicalDeviceBufferDeviceAddressFeatures";
        case(VkStructureType::BufferDeviceAddressInfo): return "BufferDeviceAddressInfo";
        case(VkStructureType::BufferOpaqueCaptureAddressCreateInfo): return "BufferOpaqueCaptureAddressCreateInfo";
        case(VkStructureType::MemoryOpaqueCaptureAddressAllocateInfo): return "MemoryOpaqueCaptureAddressAllocateInfo";
        case(VkStructureType::DeviceMemoryOpaqueCaptureAddressInfo): return "DeviceMemoryOpaqueCaptureAddressInfo";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSystemAllocationScope val) {
    switch(val) {
        case(VkSystemAllocationScope::Command): return "Command";
        case(VkSystemAllocationScope::Object): return "Object";
        case(VkSystemAllocationScope::Cache): return "Cache";
        case(VkSystemAllocationScope::Device): return "Device";
        case(VkSystemAllocationScope::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkInternalAllocationType val) {
    switch(val) {
        case(VkInternalAllocationType::Executable): return "Executable";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSamplerAddressMode val) {
    switch(val) {
        case(VkSamplerAddressMode::Repeat): return "Repeat";
        case(VkSamplerAddressMode::MirroredRepeat): return "MirroredRepeat";
        case(VkSamplerAddressMode::ClampToEdge): return "ClampToEdge";
        case(VkSamplerAddressMode::ClampToBorder): return "ClampToBorder";
        case(VkSamplerAddressMode::MirrorClampToEdge): return "MirrorClampToEdge";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFilter val) {
    switch(val) {
        case(VkFilter::Nearest): return "Nearest";
        case(VkFilter::Linear): return "Linear";
        case(VkFilter::CubicIMG): return "CubicIMG";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSamplerMipmapMode val) {
    switch(val) {
        case(VkSamplerMipmapMode::Nearest): return "Nearest";
        case(VkSamplerMipmapMode::Linear): return "Linear";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkVertexInputRate val) {
    switch(val) {
        case(VkVertexInputRate::Vertex): return "Vertex";
        case(VkVertexInputRate::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkObjectType val) {
    switch(val) {
        case(VkObjectType::Unknown): return "Unknown";
        case(VkObjectType::Instance): return "Instance";
        case(VkObjectType::PhysicalDevice): return "PhysicalDevice";
        case(VkObjectType::Device): return "Device";
        case(VkObjectType::Queue): return "Queue";
        case(VkObjectType::Semaphore): return "Semaphore";
        case(VkObjectType::CommandBuffer): return "CommandBuffer";
        case(VkObjectType::Fence): return "Fence";
        case(VkObjectType::DeviceMemory): return "DeviceMemory";
        case(VkObjectType::Buffer): return "Buffer";
        case(VkObjectType::Image): return "Image";
        case(VkObjectType::Event): return "Event";
        case(VkObjectType::QueryPool): return "QueryPool";
        case(VkObjectType::BufferView): return "BufferView";
        case(VkObjectType::ImageView): return "ImageView";
        case(VkObjectType::ShaderModule): return "ShaderModule";
        case(VkObjectType::PipelineCache): return "PipelineCache";
        case(VkObjectType::PipelineLayout): return "PipelineLayout";
        case(VkObjectType::RenderPass): return "RenderPass";
        case(VkObjectType::Pipeline): return "Pipeline";
        case(VkObjectType::DescriptorSetLayout): return "DescriptorSetLayout";
        case(VkObjectType::Sampler): return "Sampler";
        case(VkObjectType::DescriptorPool): return "DescriptorPool";
        case(VkObjectType::DescriptorSet): return "DescriptorSet";
        case(VkObjectType::Framebuffer): return "Framebuffer";
        case(VkObjectType::CommandPool): return "CommandPool";
        case(VkObjectType::SurfaceKHR): return "SurfaceKHR";
        case(VkObjectType::SwapchainKHR): return "SwapchainKHR";
        case(VkObjectType::DisplayKHR): return "DisplayKHR";
        case(VkObjectType::DisplayModeKHR): return "DisplayModeKHR";
        case(VkObjectType::DebugReportCallbackEXT): return "DebugReportCallbackEXT";
        case(VkObjectType::VideoSessionKHR): return "VideoSessionKHR";
        case(VkObjectType::VideoSessionParametersKHR): return "VideoSessionParametersKHR";
        case(VkObjectType::DebugUtilsMessengerEXT): return "DebugUtilsMessengerEXT";
        case(VkObjectType::AccelerationStructureKHR): return "AccelerationStructureKHR";
        case(VkObjectType::ValidationCacheEXT): return "ValidationCacheEXT";
        case(VkObjectType::AccelerationStructureNV): return "AccelerationStructureNV";
        case(VkObjectType::PerformanceConfigurationINTEL): return "PerformanceConfigurationINTEL";
        case(VkObjectType::DeferredOperationKHR): return "DeferredOperationKHR";
        case(VkObjectType::IndirectCommandsLayoutNV): return "IndirectCommandsLayoutNV";
        case(VkObjectType::PrivateDataSlotEXT): return "PrivateDataSlotEXT";
        case(VkObjectType::SamplerYcbcrConversion): return "SamplerYcbcrConversion";
        case(VkObjectType::DescriptorUpdateTemplate): return "DescriptorUpdateTemplate";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkIndirectCommandsTokenTypeNV val) {
    switch(val) {
        case(VkIndirectCommandsTokenTypeNV::ShaderGroupNV): return "ShaderGroupNV";
        case(VkIndirectCommandsTokenTypeNV::StateFlagsNV): return "StateFlagsNV";
        case(VkIndirectCommandsTokenTypeNV::IndexBufferNV): return "IndexBufferNV";
        case(VkIndirectCommandsTokenTypeNV::VertexBufferNV): return "VertexBufferNV";
        case(VkIndirectCommandsTokenTypeNV::PushConstantNV): return "PushConstantNV";
        case(VkIndirectCommandsTokenTypeNV::DrawIndexedNV): return "DrawIndexedNV";
        case(VkIndirectCommandsTokenTypeNV::DrawNV): return "DrawNV";
        case(VkIndirectCommandsTokenTypeNV::DrawTasksNV): return "DrawTasksNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDescriptorUpdateTemplateType val) {
    switch(val) {
        case(VkDescriptorUpdateTemplateType::DescriptorSet): return "DescriptorSet";
        case(VkDescriptorUpdateTemplateType::PushDescriptorsKHR): return "PushDescriptorsKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkViewportCoordinateSwizzleNV val) {
    switch(val) {
        case(VkViewportCoordinateSwizzleNV::PositiveXNV): return "PositiveXNV";
        case(VkViewportCoordinateSwizzleNV::NegativeXNV): return "NegativeXNV";
        case(VkViewportCoordinateSwizzleNV::PositiveYNV): return "PositiveYNV";
        case(VkViewportCoordinateSwizzleNV::NegativeYNV): return "NegativeYNV";
        case(VkViewportCoordinateSwizzleNV::PositiveZNV): return "PositiveZNV";
        case(VkViewportCoordinateSwizzleNV::NegativeZNV): return "NegativeZNV";
        case(VkViewportCoordinateSwizzleNV::PositiveWNV): return "PositiveWNV";
        case(VkViewportCoordinateSwizzleNV::NegativeWNV): return "NegativeWNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDiscardRectangleModeEXT val) {
    switch(val) {
        case(VkDiscardRectangleModeEXT::InclusiveEXT): return "InclusiveEXT";
        case(VkDiscardRectangleModeEXT::ExclusiveEXT): return "ExclusiveEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPointClippingBehavior val) {
    switch(val) {
        case(VkPointClippingBehavior::AllClipPlanes): return "AllClipPlanes";
        case(VkPointClippingBehavior::UserClipPlanesOnly): return "UserClipPlanesOnly";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCoverageModulationModeNV val) {
    switch(val) {
        case(VkCoverageModulationModeNV::NoneNV): return "NoneNV";
        case(VkCoverageModulationModeNV::RgbNV): return "RgbNV";
        case(VkCoverageModulationModeNV::AlphaNV): return "AlphaNV";
        case(VkCoverageModulationModeNV::RgbaNV): return "RgbaNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCoverageReductionModeNV val) {
    switch(val) {
        case(VkCoverageReductionModeNV::MergeNV): return "MergeNV";
        case(VkCoverageReductionModeNV::TruncateNV): return "TruncateNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkValidationCacheHeaderVersionEXT val) {
    switch(val) {
        case(VkValidationCacheHeaderVersionEXT::OneEXT): return "OneEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkShaderInfoTypeAMD val) {
    switch(val) {
        case(VkShaderInfoTypeAMD::StatisticsAMD): return "StatisticsAMD";
        case(VkShaderInfoTypeAMD::BinaryAMD): return "BinaryAMD";
        case(VkShaderInfoTypeAMD::DisassemblyAMD): return "DisassemblyAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkQueueGlobalPriorityEXT val) {
    switch(val) {
        case(VkQueueGlobalPriorityEXT::LowEXT): return "LowEXT";
        case(VkQueueGlobalPriorityEXT::MediumEXT): return "MediumEXT";
        case(VkQueueGlobalPriorityEXT::HighEXT): return "HighEXT";
        case(VkQueueGlobalPriorityEXT::RealtimeEXT): return "RealtimeEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkTimeDomainEXT val) {
    switch(val) {
        case(VkTimeDomainEXT::DeviceEXT): return "DeviceEXT";
        case(VkTimeDomainEXT::ClockMonotonicEXT): return "ClockMonotonicEXT";
        case(VkTimeDomainEXT::ClockMonotonicRawEXT): return "ClockMonotonicRawEXT";
        case(VkTimeDomainEXT::QueryPerformanceCounterEXT): return "QueryPerformanceCounterEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkConservativeRasterizationModeEXT val) {
    switch(val) {
        case(VkConservativeRasterizationModeEXT::DisabledEXT): return "DisabledEXT";
        case(VkConservativeRasterizationModeEXT::OverestimateEXT): return "OverestimateEXT";
        case(VkConservativeRasterizationModeEXT::UnderestimateEXT): return "UnderestimateEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSemaphoreType val) {
    switch(val) {
        case(VkSemaphoreType::Binary): return "Binary";
        case(VkSemaphoreType::Timeline): return "Timeline";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkBuildAccelerationStructureModeKHR val) {
    switch(val) {
        case(VkBuildAccelerationStructureModeKHR::BuildKHR): return "BuildKHR";
        case(VkBuildAccelerationStructureModeKHR::UpdateKHR): return "UpdateKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCopyAccelerationStructureModeKHR val) {
    switch(val) {
        case(VkCopyAccelerationStructureModeKHR::CloneKHR): return "CloneKHR";
        case(VkCopyAccelerationStructureModeKHR::CompactKHR): return "CompactKHR";
        case(VkCopyAccelerationStructureModeKHR::SerializeKHR): return "SerializeKHR";
        case(VkCopyAccelerationStructureModeKHR::DeserializeKHR): return "DeserializeKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkAccelerationStructureTypeKHR val) {
    switch(val) {
        case(VkAccelerationStructureTypeKHR::TopLevelKHR): return "TopLevelKHR";
        case(VkAccelerationStructureTypeKHR::BottomLevelKHR): return "BottomLevelKHR";
        case(VkAccelerationStructureTypeKHR::GenericKHR): return "GenericKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkGeometryTypeKHR val) {
    switch(val) {
        case(VkGeometryTypeKHR::TrianglesKHR): return "TrianglesKHR";
        case(VkGeometryTypeKHR::AabbsKHR): return "AabbsKHR";
        case(VkGeometryTypeKHR::InstancesKHR): return "InstancesKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkRayTracingShaderGroupTypeKHR val) {
    switch(val) {
        case(VkRayTracingShaderGroupTypeKHR::GeneralKHR): return "GeneralKHR";
        case(VkRayTracingShaderGroupTypeKHR::TrianglesHitGroupKHR): return "TrianglesHitGroupKHR";
        case(VkRayTracingShaderGroupTypeKHR::ProceduralHitGroupKHR): return "ProceduralHitGroupKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkAccelerationStructureMemoryRequirementsTypeNV val) {
    switch(val) {
        case(VkAccelerationStructureMemoryRequirementsTypeNV::ObjectNV): return "ObjectNV";
        case(VkAccelerationStructureMemoryRequirementsTypeNV::BuildScratchNV): return "BuildScratchNV";
        case(VkAccelerationStructureMemoryRequirementsTypeNV::UpdateScratchNV): return "UpdateScratchNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkAccelerationStructureBuildTypeKHR val) {
    switch(val) {
        case(VkAccelerationStructureBuildTypeKHR::HostKHR): return "HostKHR";
        case(VkAccelerationStructureBuildTypeKHR::DeviceKHR): return "DeviceKHR";
        case(VkAccelerationStructureBuildTypeKHR::HostOrDeviceKHR): return "HostOrDeviceKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkAccelerationStructureCompatibilityKHR val) {
    switch(val) {
        case(VkAccelerationStructureCompatibilityKHR::CompatibleKHR): return "CompatibleKHR";
        case(VkAccelerationStructureCompatibilityKHR::IncompatibleKHR): return "IncompatibleKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkShaderGroupShaderKHR val) {
    switch(val) {
        case(VkShaderGroupShaderKHR::GeneralKHR): return "GeneralKHR";
        case(VkShaderGroupShaderKHR::ClosestHitKHR): return "ClosestHitKHR";
        case(VkShaderGroupShaderKHR::AnyHitKHR): return "AnyHitKHR";
        case(VkShaderGroupShaderKHR::IntersectionKHR): return "IntersectionKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkMemoryOverallocationBehaviorAMD val) {
    switch(val) {
        case(VkMemoryOverallocationBehaviorAMD::DefaultAMD): return "DefaultAMD";
        case(VkMemoryOverallocationBehaviorAMD::AllowedAMD): return "AllowedAMD";
        case(VkMemoryOverallocationBehaviorAMD::DisallowedAMD): return "DisallowedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkScopeNV val) {
    switch(val) {
        case(VkScopeNV::DeviceNV): return "DeviceNV";
        case(VkScopeNV::WorkgroupNV): return "WorkgroupNV";
        case(VkScopeNV::SubgroupNV): return "SubgroupNV";
        case(VkScopeNV::QueueFamilyNV): return "QueueFamilyNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkComponentTypeNV val) {
    switch(val) {
        case(VkComponentTypeNV::Float16NV): return "Float16NV";
        case(VkComponentTypeNV::Float32NV): return "Float32NV";
        case(VkComponentTypeNV::Float64NV): return "Float64NV";
        case(VkComponentTypeNV::Sint8NV): return "Sint8NV";
        case(VkComponentTypeNV::Sint16NV): return "Sint16NV";
        case(VkComponentTypeNV::Sint32NV): return "Sint32NV";
        case(VkComponentTypeNV::Sint64NV): return "Sint64NV";
        case(VkComponentTypeNV::Uint8NV): return "Uint8NV";
        case(VkComponentTypeNV::Uint16NV): return "Uint16NV";
        case(VkComponentTypeNV::Uint32NV): return "Uint32NV";
        case(VkComponentTypeNV::Uint64NV): return "Uint64NV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceCounterScopeKHR val) {
    switch(val) {
        case(VkPerformanceCounterScopeKHR::CommandBufferKHR): return "CommandBufferKHR";
        case(VkPerformanceCounterScopeKHR::RenderPassKHR): return "RenderPassKHR";
        case(VkPerformanceCounterScopeKHR::CommandKHR): return "CommandKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceCounterUnitKHR val) {
    switch(val) {
        case(VkPerformanceCounterUnitKHR::GenericKHR): return "GenericKHR";
        case(VkPerformanceCounterUnitKHR::PercentageKHR): return "PercentageKHR";
        case(VkPerformanceCounterUnitKHR::NanosecondsKHR): return "NanosecondsKHR";
        case(VkPerformanceCounterUnitKHR::BytesKHR): return "BytesKHR";
        case(VkPerformanceCounterUnitKHR::BytesPerSecondKHR): return "BytesPerSecondKHR";
        case(VkPerformanceCounterUnitKHR::KelvinKHR): return "KelvinKHR";
        case(VkPerformanceCounterUnitKHR::WattsKHR): return "WattsKHR";
        case(VkPerformanceCounterUnitKHR::VoltsKHR): return "VoltsKHR";
        case(VkPerformanceCounterUnitKHR::AmpsKHR): return "AmpsKHR";
        case(VkPerformanceCounterUnitKHR::HertzKHR): return "HertzKHR";
        case(VkPerformanceCounterUnitKHR::CyclesKHR): return "CyclesKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceCounterStorageKHR val) {
    switch(val) {
        case(VkPerformanceCounterStorageKHR::Int32KHR): return "Int32KHR";
        case(VkPerformanceCounterStorageKHR::Int64KHR): return "Int64KHR";
        case(VkPerformanceCounterStorageKHR::Uint32KHR): return "Uint32KHR";
        case(VkPerformanceCounterStorageKHR::Uint64KHR): return "Uint64KHR";
        case(VkPerformanceCounterStorageKHR::Float32KHR): return "Float32KHR";
        case(VkPerformanceCounterStorageKHR::Float64KHR): return "Float64KHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceConfigurationTypeINTEL val) {
    switch(val) {
        case(VkPerformanceConfigurationTypeINTEL::CommandQueueMetricsDiscoveryActivatedINTEL): return "CommandQueueMetricsDiscoveryActivatedINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkQueryPoolSamplingModeINTEL val) {
    switch(val) {
        case(VkQueryPoolSamplingModeINTEL::ManualINTEL): return "ManualINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceOverrideTypeINTEL val) {
    switch(val) {
        case(VkPerformanceOverrideTypeINTEL::NullHardwareINTEL): return "NullHardwareINTEL";
        case(VkPerformanceOverrideTypeINTEL::FlushGpuCachesINTEL): return "FlushGpuCachesINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceParameterTypeINTEL val) {
    switch(val) {
        case(VkPerformanceParameterTypeINTEL::HwCountersSupportedINTEL): return "HwCountersSupportedINTEL";
        case(VkPerformanceParameterTypeINTEL::StreamMarkerValidBitsINTEL): return "StreamMarkerValidBitsINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPerformanceValueTypeINTEL val) {
    switch(val) {
        case(VkPerformanceValueTypeINTEL::Uint32INTEL): return "Uint32INTEL";
        case(VkPerformanceValueTypeINTEL::Uint64INTEL): return "Uint64INTEL";
        case(VkPerformanceValueTypeINTEL::FloatINTEL): return "FloatINTEL";
        case(VkPerformanceValueTypeINTEL::BoolINTEL): return "BoolINTEL";
        case(VkPerformanceValueTypeINTEL::StringINTEL): return "StringINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkLineRasterizationModeEXT val) {
    switch(val) {
        case(VkLineRasterizationModeEXT::DefaultEXT): return "DefaultEXT";
        case(VkLineRasterizationModeEXT::RectangularEXT): return "RectangularEXT";
        case(VkLineRasterizationModeEXT::BresenhamEXT): return "BresenhamEXT";
        case(VkLineRasterizationModeEXT::RectangularSmoothEXT): return "RectangularSmoothEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFragmentShadingRateNV val) {
    switch(val) {
        case(VkFragmentShadingRateNV::e1InvocationPerPixelNV): return "e1InvocationPerPixelNV";
        case(VkFragmentShadingRateNV::e1InvocationPer1X2PixelsNV): return "e1InvocationPer1X2PixelsNV";
        case(VkFragmentShadingRateNV::e1InvocationPer2X1PixelsNV): return "e1InvocationPer2X1PixelsNV";
        case(VkFragmentShadingRateNV::e1InvocationPer2X2PixelsNV): return "e1InvocationPer2X2PixelsNV";
        case(VkFragmentShadingRateNV::e1InvocationPer2X4PixelsNV): return "e1InvocationPer2X4PixelsNV";
        case(VkFragmentShadingRateNV::e1InvocationPer4X2PixelsNV): return "e1InvocationPer4X2PixelsNV";
        case(VkFragmentShadingRateNV::e1InvocationPer4X4PixelsNV): return "e1InvocationPer4X4PixelsNV";
        case(VkFragmentShadingRateNV::e2InvocationsPerPixelNV): return "e2InvocationsPerPixelNV";
        case(VkFragmentShadingRateNV::e4InvocationsPerPixelNV): return "e4InvocationsPerPixelNV";
        case(VkFragmentShadingRateNV::e8InvocationsPerPixelNV): return "e8InvocationsPerPixelNV";
        case(VkFragmentShadingRateNV::e16InvocationsPerPixelNV): return "e16InvocationsPerPixelNV";
        case(VkFragmentShadingRateNV::NoInvocationsNV): return "NoInvocationsNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFragmentShadingRateTypeNV val) {
    switch(val) {
        case(VkFragmentShadingRateTypeNV::FragmentSizeNV): return "FragmentSizeNV";
        case(VkFragmentShadingRateTypeNV::EnumsNV): return "EnumsNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkColorSpaceKHR val) {
    switch(val) {
        case(VkColorSpaceKHR::SrgbNonlinearKHR): return "SrgbNonlinearKHR";
        case(VkColorSpaceKHR::DisplayP3NonlinearEXT): return "DisplayP3NonlinearEXT";
        case(VkColorSpaceKHR::ExtendedSrgbLinearEXT): return "ExtendedSrgbLinearEXT";
        case(VkColorSpaceKHR::DisplayP3LinearEXT): return "DisplayP3LinearEXT";
        case(VkColorSpaceKHR::DciP3NonlinearEXT): return "DciP3NonlinearEXT";
        case(VkColorSpaceKHR::Bt709LinearEXT): return "Bt709LinearEXT";
        case(VkColorSpaceKHR::Bt709NonlinearEXT): return "Bt709NonlinearEXT";
        case(VkColorSpaceKHR::Bt2020LinearEXT): return "Bt2020LinearEXT";
        case(VkColorSpaceKHR::Hdr10St2084EXT): return "Hdr10St2084EXT";
        case(VkColorSpaceKHR::DolbyvisionEXT): return "DolbyvisionEXT";
        case(VkColorSpaceKHR::Hdr10HlgEXT): return "Hdr10HlgEXT";
        case(VkColorSpaceKHR::AdobergbLinearEXT): return "AdobergbLinearEXT";
        case(VkColorSpaceKHR::AdobergbNonlinearEXT): return "AdobergbNonlinearEXT";
        case(VkColorSpaceKHR::PassThroughEXT): return "PassThroughEXT";
        case(VkColorSpaceKHR::ExtendedSrgbNonlinearEXT): return "ExtendedSrgbNonlinearEXT";
        case(VkColorSpaceKHR::DisplayNativeAMD): return "DisplayNativeAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPresentModeKHR val) {
    switch(val) {
        case(VkPresentModeKHR::ImmediateKHR): return "ImmediateKHR";
        case(VkPresentModeKHR::MailboxKHR): return "MailboxKHR";
        case(VkPresentModeKHR::FifoKHR): return "FifoKHR";
        case(VkPresentModeKHR::FifoRelaxedKHR): return "FifoRelaxedKHR";
        case(VkPresentModeKHR::SharedDemandRefreshKHR): return "SharedDemandRefreshKHR";
        case(VkPresentModeKHR::SharedContinuousRefreshKHR): return "SharedContinuousRefreshKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDebugReportObjectTypeEXT val) {
    switch(val) {
        case(VkDebugReportObjectTypeEXT::UnknownEXT): return "UnknownEXT";
        case(VkDebugReportObjectTypeEXT::InstanceEXT): return "InstanceEXT";
        case(VkDebugReportObjectTypeEXT::PhysicalDeviceEXT): return "PhysicalDeviceEXT";
        case(VkDebugReportObjectTypeEXT::DeviceEXT): return "DeviceEXT";
        case(VkDebugReportObjectTypeEXT::QueueEXT): return "QueueEXT";
        case(VkDebugReportObjectTypeEXT::SemaphoreEXT): return "SemaphoreEXT";
        case(VkDebugReportObjectTypeEXT::CommandBufferEXT): return "CommandBufferEXT";
        case(VkDebugReportObjectTypeEXT::FenceEXT): return "FenceEXT";
        case(VkDebugReportObjectTypeEXT::DeviceMemoryEXT): return "DeviceMemoryEXT";
        case(VkDebugReportObjectTypeEXT::BufferEXT): return "BufferEXT";
        case(VkDebugReportObjectTypeEXT::ImageEXT): return "ImageEXT";
        case(VkDebugReportObjectTypeEXT::EventEXT): return "EventEXT";
        case(VkDebugReportObjectTypeEXT::QueryPoolEXT): return "QueryPoolEXT";
        case(VkDebugReportObjectTypeEXT::BufferViewEXT): return "BufferViewEXT";
        case(VkDebugReportObjectTypeEXT::ImageViewEXT): return "ImageViewEXT";
        case(VkDebugReportObjectTypeEXT::ShaderModuleEXT): return "ShaderModuleEXT";
        case(VkDebugReportObjectTypeEXT::PipelineCacheEXT): return "PipelineCacheEXT";
        case(VkDebugReportObjectTypeEXT::PipelineLayoutEXT): return "PipelineLayoutEXT";
        case(VkDebugReportObjectTypeEXT::RenderPassEXT): return "RenderPassEXT";
        case(VkDebugReportObjectTypeEXT::PipelineEXT): return "PipelineEXT";
        case(VkDebugReportObjectTypeEXT::DescriptorSetLayoutEXT): return "DescriptorSetLayoutEXT";
        case(VkDebugReportObjectTypeEXT::SamplerEXT): return "SamplerEXT";
        case(VkDebugReportObjectTypeEXT::DescriptorPoolEXT): return "DescriptorPoolEXT";
        case(VkDebugReportObjectTypeEXT::DescriptorSetEXT): return "DescriptorSetEXT";
        case(VkDebugReportObjectTypeEXT::FramebufferEXT): return "FramebufferEXT";
        case(VkDebugReportObjectTypeEXT::CommandPoolEXT): return "CommandPoolEXT";
        case(VkDebugReportObjectTypeEXT::SurfaceKhrEXT): return "SurfaceKhrEXT";
        case(VkDebugReportObjectTypeEXT::SwapchainKhrEXT): return "SwapchainKhrEXT";
        case(VkDebugReportObjectTypeEXT::DebugReportCallbackExtEXT): return "DebugReportCallbackExtEXT";
        case(VkDebugReportObjectTypeEXT::DisplayKhrEXT): return "DisplayKhrEXT";
        case(VkDebugReportObjectTypeEXT::DisplayModeKhrEXT): return "DisplayModeKhrEXT";
        case(VkDebugReportObjectTypeEXT::ValidationCacheExtEXT): return "ValidationCacheExtEXT";
        case(VkDebugReportObjectTypeEXT::SamplerYcbcrConversionEXT): return "SamplerYcbcrConversionEXT";
        case(VkDebugReportObjectTypeEXT::DescriptorUpdateTemplateEXT): return "DescriptorUpdateTemplateEXT";
        case(VkDebugReportObjectTypeEXT::AccelerationStructureKhrEXT): return "AccelerationStructureKhrEXT";
        case(VkDebugReportObjectTypeEXT::AccelerationStructureNvEXT): return "AccelerationStructureNvEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDeviceMemoryReportEventTypeEXT val) {
    switch(val) {
        case(VkDeviceMemoryReportEventTypeEXT::AllocateEXT): return "AllocateEXT";
        case(VkDeviceMemoryReportEventTypeEXT::FreeEXT): return "FreeEXT";
        case(VkDeviceMemoryReportEventTypeEXT::ImportEXT): return "ImportEXT";
        case(VkDeviceMemoryReportEventTypeEXT::UnimportEXT): return "UnimportEXT";
        case(VkDeviceMemoryReportEventTypeEXT::AllocationFailedEXT): return "AllocationFailedEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkRasterizationOrderAMD val) {
    switch(val) {
        case(VkRasterizationOrderAMD::StrictAMD): return "StrictAMD";
        case(VkRasterizationOrderAMD::RelaxedAMD): return "RelaxedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkValidationCheckEXT val) {
    switch(val) {
        case(VkValidationCheckEXT::AllEXT): return "AllEXT";
        case(VkValidationCheckEXT::ShadersEXT): return "ShadersEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkValidationFeatureEnableEXT val) {
    switch(val) {
        case(VkValidationFeatureEnableEXT::GpuAssistedEXT): return "GpuAssistedEXT";
        case(VkValidationFeatureEnableEXT::GpuAssistedReserveBindingSlotEXT): return "GpuAssistedReserveBindingSlotEXT";
        case(VkValidationFeatureEnableEXT::BestPracticesEXT): return "BestPracticesEXT";
        case(VkValidationFeatureEnableEXT::DebugPrintfEXT): return "DebugPrintfEXT";
        case(VkValidationFeatureEnableEXT::SynchronizationValidationEXT): return "SynchronizationValidationEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkValidationFeatureDisableEXT val) {
    switch(val) {
        case(VkValidationFeatureDisableEXT::AllEXT): return "AllEXT";
        case(VkValidationFeatureDisableEXT::ShadersEXT): return "ShadersEXT";
        case(VkValidationFeatureDisableEXT::ThreadSafetyEXT): return "ThreadSafetyEXT";
        case(VkValidationFeatureDisableEXT::ApiParametersEXT): return "ApiParametersEXT";
        case(VkValidationFeatureDisableEXT::ObjectLifetimesEXT): return "ObjectLifetimesEXT";
        case(VkValidationFeatureDisableEXT::CoreChecksEXT): return "CoreChecksEXT";
        case(VkValidationFeatureDisableEXT::UniqueHandlesEXT): return "UniqueHandlesEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDisplayPowerStateEXT val) {
    switch(val) {
        case(VkDisplayPowerStateEXT::OffEXT): return "OffEXT";
        case(VkDisplayPowerStateEXT::SuspendEXT): return "SuspendEXT";
        case(VkDisplayPowerStateEXT::OnEXT): return "OnEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDeviceEventTypeEXT val) {
    switch(val) {
        case(VkDeviceEventTypeEXT::DisplayHotplugEXT): return "DisplayHotplugEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDisplayEventTypeEXT val) {
    switch(val) {
        case(VkDisplayEventTypeEXT::FirstPixelOutEXT): return "FirstPixelOutEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkTessellationDomainOrigin val) {
    switch(val) {
        case(VkTessellationDomainOrigin::UpperLeft): return "UpperLeft";
        case(VkTessellationDomainOrigin::LowerLeft): return "LowerLeft";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSamplerYcbcrModelConversion val) {
    switch(val) {
        case(VkSamplerYcbcrModelConversion::RgbIdentity): return "RgbIdentity";
        case(VkSamplerYcbcrModelConversion::YcbcrIdentity): return "YcbcrIdentity";
        case(VkSamplerYcbcrModelConversion::Ycbcr709): return "Ycbcr709";
        case(VkSamplerYcbcrModelConversion::Ycbcr601): return "Ycbcr601";
        case(VkSamplerYcbcrModelConversion::Ycbcr2020): return "Ycbcr2020";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSamplerYcbcrRange val) {
    switch(val) {
        case(VkSamplerYcbcrRange::ItuFull): return "ItuFull";
        case(VkSamplerYcbcrRange::ItuNarrow): return "ItuNarrow";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkChromaLocation val) {
    switch(val) {
        case(VkChromaLocation::CositedEven): return "CositedEven";
        case(VkChromaLocation::Midpoint): return "Midpoint";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkSamplerReductionMode val) {
    switch(val) {
        case(VkSamplerReductionMode::WeightedAverage): return "WeightedAverage";
        case(VkSamplerReductionMode::Min): return "Min";
        case(VkSamplerReductionMode::Max): return "Max";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkBlendOverlapEXT val) {
    switch(val) {
        case(VkBlendOverlapEXT::UncorrelatedEXT): return "UncorrelatedEXT";
        case(VkBlendOverlapEXT::DisjointEXT): return "DisjointEXT";
        case(VkBlendOverlapEXT::ConjointEXT): return "ConjointEXT";
        default: return "UNKNOWN";
    }
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(VkFullScreenExclusiveEXT val) {
    switch(val) {
        case(VkFullScreenExclusiveEXT::DefaultEXT): return "DefaultEXT";
        case(VkFullScreenExclusiveEXT::AllowedEXT): return "AllowedEXT";
        case(VkFullScreenExclusiveEXT::DisallowedEXT): return "DisallowedEXT";
        case(VkFullScreenExclusiveEXT::ApplicationControlledEXT): return "ApplicationControlledEXT";
        default: return "UNKNOWN";
    }
}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(VkShaderFloatControlsIndependence val) {
    switch(val) {
        case(VkShaderFloatControlsIndependence::e32BitOnly): return "e32BitOnly";
        case(VkShaderFloatControlsIndependence::All): return "All";
        case(VkShaderFloatControlsIndependence::None): return "None";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkFragmentShadingRateCombinerOpKHR val) {
    switch(val) {
        case(VkFragmentShadingRateCombinerOpKHR::KeepKHR): return "KeepKHR";
        case(VkFragmentShadingRateCombinerOpKHR::ReplaceKHR): return "ReplaceKHR";
        case(VkFragmentShadingRateCombinerOpKHR::MinKHR): return "MinKHR";
        case(VkFragmentShadingRateCombinerOpKHR::MaxKHR): return "MaxKHR";
        case(VkFragmentShadingRateCombinerOpKHR::MulKHR): return "MulKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkVendorId val) {
    switch(val) {
        case(VkVendorId::VIV): return "VIV";
        case(VkVendorId::VSI): return "VSI";
        case(VkVendorId::Kazan): return "Kazan";
        case(VkVendorId::Codeplay): return "Codeplay";
        case(VkVendorId::MESA): return "MESA";
        case(VkVendorId::Pocl): return "Pocl";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkDriverId val) {
    switch(val) {
        case(VkDriverId::AmdProprietary): return "AmdProprietary";
        case(VkDriverId::AmdOpenSource): return "AmdOpenSource";
        case(VkDriverId::MesaRadv): return "MesaRadv";
        case(VkDriverId::NvidiaProprietary): return "NvidiaProprietary";
        case(VkDriverId::IntelProprietaryWindows): return "IntelProprietaryWindows";
        case(VkDriverId::IntelOpenSourceMESA): return "IntelOpenSourceMESA";
        case(VkDriverId::ImaginationProprietary): return "ImaginationProprietary";
        case(VkDriverId::QualcommProprietary): return "QualcommProprietary";
        case(VkDriverId::ArmProprietary): return "ArmProprietary";
        case(VkDriverId::GoogleSwiftshader): return "GoogleSwiftshader";
        case(VkDriverId::GgpProprietary): return "GgpProprietary";
        case(VkDriverId::BroadcomProprietary): return "BroadcomProprietary";
        case(VkDriverId::MesaLlvmpipe): return "MesaLlvmpipe";
        case(VkDriverId::Moltenvk): return "Moltenvk";
        case(VkDriverId::CoreaviProprietary): return "CoreaviProprietary";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkShadingRatePaletteEntryNV val) {
    switch(val) {
        case(VkShadingRatePaletteEntryNV::NoInvocationsNV): return "NoInvocationsNV";
        case(VkShadingRatePaletteEntryNV::e16InvocationsPerPixelNV): return "e16InvocationsPerPixelNV";
        case(VkShadingRatePaletteEntryNV::e8InvocationsPerPixelNV): return "e8InvocationsPerPixelNV";
        case(VkShadingRatePaletteEntryNV::e4InvocationsPerPixelNV): return "e4InvocationsPerPixelNV";
        case(VkShadingRatePaletteEntryNV::e2InvocationsPerPixelNV): return "e2InvocationsPerPixelNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPerPixelNV): return "e1InvocationPerPixelNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer2X1PixelsNV): return "e1InvocationPer2X1PixelsNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer1X2PixelsNV): return "e1InvocationPer1X2PixelsNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer2X2PixelsNV): return "e1InvocationPer2X2PixelsNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer4X2PixelsNV): return "e1InvocationPer4X2PixelsNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer2X4PixelsNV): return "e1InvocationPer2X4PixelsNV";
        case(VkShadingRatePaletteEntryNV::e1InvocationPer4X4PixelsNV): return "e1InvocationPer4X4PixelsNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkCoarseSampleOrderTypeNV val) {
    switch(val) {
        case(VkCoarseSampleOrderTypeNV::DefaultNV): return "DefaultNV";
        case(VkCoarseSampleOrderTypeNV::CustomNV): return "CustomNV";
        case(VkCoarseSampleOrderTypeNV::PixelMajorNV): return "PixelMajorNV";
        case(VkCoarseSampleOrderTypeNV::SampleMajorNV): return "SampleMajorNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(VkPipelineExecutableStatisticFormatKHR val) {
    switch(val) {
        case(VkPipelineExecutableStatisticFormatKHR::Bool32KHR): return "Bool32KHR";
        case(VkPipelineExecutableStatisticFormatKHR::Int64KHR): return "Int64KHR";
        case(VkPipelineExecutableStatisticFormatKHR::Uint64KHR): return "Uint64KHR";
        case(VkPipelineExecutableStatisticFormatKHR::Float64KHR): return "Float64KHR";
        default: return "UNKNOWN";
    }
}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkQueryResultStatusKHR val) {
    switch(val) {
        case(VkQueryResultStatusKHR::ErrorKHR): return "ErrorKHR";
        case(VkQueryResultStatusKHR::NotReadyKHR): return "NotReadyKHR";
        case(VkQueryResultStatusKHR::CompleteKHR): return "CompleteKHR";
        default: return "UNKNOWN";
    }
}
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkPipelineCacheCreateFlagBits val) {
    switch(val) {
        case(VkPipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT): return "ExternallySynchronizedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineCacheCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT) out += "ExternallySynchronizedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkQueueFlagBits val) {
    switch(val) {
        case(VkQueueFlagBits::Graphics): return "Graphics";
        case(VkQueueFlagBits::Compute): return "Compute";
        case(VkQueueFlagBits::Transfer): return "Transfer";
        case(VkQueueFlagBits::SparseBinding): return "SparseBinding";
        case(VkQueueFlagBits::VideoDecodeBitKHR): return "VideoDecodeBitKHR";
        case(VkQueueFlagBits::VideoEncodeBitKHR): return "VideoEncodeBitKHR";
        case(VkQueueFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkQueueFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkQueueFlagBits::Graphics) out += "Graphics | ";
    if (flag & VkQueueFlagBits::Compute) out += "Compute | ";
    if (flag & VkQueueFlagBits::Transfer) out += "Transfer | ";
    if (flag & VkQueueFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & VkQueueFlagBits::VideoDecodeBitKHR) out += "VideoDecodeBitKHR | ";
    if (flag & VkQueueFlagBits::VideoEncodeBitKHR) out += "VideoEncodeBitKHR | ";
    if (flag & VkQueueFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCullModeFlagBits val) {
    switch(val) {
        case(VkCullModeFlagBits::None): return "None";
        case(VkCullModeFlagBits::Front): return "Front";
        case(VkCullModeFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCullModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCullModeFlagBits::None) out += "None | ";
    if (flag & VkCullModeFlagBits::Front) out += "Front | ";
    if (flag & VkCullModeFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkRenderPassCreateFlagBits val) {
    switch(val) {
        case(VkRenderPassCreateFlagBits::TransformBitQCOM): return "TransformBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkRenderPassCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkRenderPassCreateFlagBits::TransformBitQCOM) out += "TransformBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDeviceQueueCreateFlagBits val) {
    switch(val) {
        case(VkDeviceQueueCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDeviceQueueCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDeviceQueueCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkMemoryPropertyFlagBits val) {
    switch(val) {
        case(VkMemoryPropertyFlagBits::DeviceLocal): return "DeviceLocal";
        case(VkMemoryPropertyFlagBits::HostVisible): return "HostVisible";
        case(VkMemoryPropertyFlagBits::HostCoherent): return "HostCoherent";
        case(VkMemoryPropertyFlagBits::HostCached): return "HostCached";
        case(VkMemoryPropertyFlagBits::LazilyAllocated): return "LazilyAllocated";
        case(VkMemoryPropertyFlagBits::DeviceCoherentBitAMD): return "DeviceCoherentBitAMD";
        case(VkMemoryPropertyFlagBits::DeviceUncachedBitAMD): return "DeviceUncachedBitAMD";
        case(VkMemoryPropertyFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkMemoryPropertyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkMemoryPropertyFlagBits::DeviceLocal) out += "DeviceLocal | ";
    if (flag & VkMemoryPropertyFlagBits::HostVisible) out += "HostVisible | ";
    if (flag & VkMemoryPropertyFlagBits::HostCoherent) out += "HostCoherent | ";
    if (flag & VkMemoryPropertyFlagBits::HostCached) out += "HostCached | ";
    if (flag & VkMemoryPropertyFlagBits::LazilyAllocated) out += "LazilyAllocated | ";
    if (flag & VkMemoryPropertyFlagBits::DeviceCoherentBitAMD) out += "DeviceCoherentBitAMD | ";
    if (flag & VkMemoryPropertyFlagBits::DeviceUncachedBitAMD) out += "DeviceUncachedBitAMD | ";
    if (flag & VkMemoryPropertyFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkMemoryHeapFlagBits val) {
    switch(val) {
        case(VkMemoryHeapFlagBits::DeviceLocal): return "DeviceLocal";
        case(VkMemoryHeapFlagBits::MultiInstance): return "MultiInstance";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkMemoryHeapFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkMemoryHeapFlagBits::DeviceLocal) out += "DeviceLocal | ";
    if (flag & VkMemoryHeapFlagBits::MultiInstance) out += "MultiInstance | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkAccessFlagBits val) {
    switch(val) {
        case(VkAccessFlagBits::NoneKHR): return "NoneKHR";
        case(VkAccessFlagBits::IndexRead): return "IndexRead";
        case(VkAccessFlagBits::VertexAttributeRead): return "VertexAttributeRead";
        case(VkAccessFlagBits::UniformRead): return "UniformRead";
        case(VkAccessFlagBits::InputAttachmentRead): return "InputAttachmentRead";
        case(VkAccessFlagBits::ShaderRead): return "ShaderRead";
        case(VkAccessFlagBits::ShaderWrite): return "ShaderWrite";
        case(VkAccessFlagBits::ColorAttachmentRead): return "ColorAttachmentRead";
        case(VkAccessFlagBits::ColorAttachmentWrite): return "ColorAttachmentWrite";
        case(VkAccessFlagBits::DepthStencilAttachmentRead): return "DepthStencilAttachmentRead";
        case(VkAccessFlagBits::DepthStencilAttachmentWrite): return "DepthStencilAttachmentWrite";
        case(VkAccessFlagBits::TransferRead): return "TransferRead";
        case(VkAccessFlagBits::TransferWrite): return "TransferWrite";
        case(VkAccessFlagBits::HostRead): return "HostRead";
        case(VkAccessFlagBits::HostWrite): return "HostWrite";
        case(VkAccessFlagBits::MemoryRead): return "MemoryRead";
        case(VkAccessFlagBits::MemoryWrite): return "MemoryWrite";
        case(VkAccessFlagBits::TransformFeedbackWriteBitEXT): return "TransformFeedbackWriteBitEXT";
        case(VkAccessFlagBits::TransformFeedbackCounterReadBitEXT): return "TransformFeedbackCounterReadBitEXT";
        case(VkAccessFlagBits::TransformFeedbackCounterWriteBitEXT): return "TransformFeedbackCounterWriteBitEXT";
        case(VkAccessFlagBits::ConditionalRenderingReadBitEXT): return "ConditionalRenderingReadBitEXT";
        case(VkAccessFlagBits::ColorAttachmentReadNoncoherentBitEXT): return "ColorAttachmentReadNoncoherentBitEXT";
        case(VkAccessFlagBits::AccelerationStructureReadBitKHR): return "AccelerationStructureReadBitKHR";
        case(VkAccessFlagBits::AccelerationStructureWriteBitKHR): return "AccelerationStructureWriteBitKHR";
        case(VkAccessFlagBits::ShadingRateImageReadBitNV): return "ShadingRateImageReadBitNV";
        case(VkAccessFlagBits::FragmentDensityMapReadBitEXT): return "FragmentDensityMapReadBitEXT";
        case(VkAccessFlagBits::CommandPreprocessReadBitNV): return "CommandPreprocessReadBitNV";
        case(VkAccessFlagBits::CommandPreprocessWriteBitNV): return "CommandPreprocessWriteBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkAccessFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkAccessFlagBits::NoneKHR) out += "NoneKHR | ";
    if (flag & VkAccessFlagBits::IndexRead) out += "IndexRead | ";
    if (flag & VkAccessFlagBits::VertexAttributeRead) out += "VertexAttributeRead | ";
    if (flag & VkAccessFlagBits::UniformRead) out += "UniformRead | ";
    if (flag & VkAccessFlagBits::InputAttachmentRead) out += "InputAttachmentRead | ";
    if (flag & VkAccessFlagBits::ShaderRead) out += "ShaderRead | ";
    if (flag & VkAccessFlagBits::ShaderWrite) out += "ShaderWrite | ";
    if (flag & VkAccessFlagBits::ColorAttachmentRead) out += "ColorAttachmentRead | ";
    if (flag & VkAccessFlagBits::ColorAttachmentWrite) out += "ColorAttachmentWrite | ";
    if (flag & VkAccessFlagBits::DepthStencilAttachmentRead) out += "DepthStencilAttachmentRead | ";
    if (flag & VkAccessFlagBits::DepthStencilAttachmentWrite) out += "DepthStencilAttachmentWrite | ";
    if (flag & VkAccessFlagBits::TransferRead) out += "TransferRead | ";
    if (flag & VkAccessFlagBits::TransferWrite) out += "TransferWrite | ";
    if (flag & VkAccessFlagBits::HostRead) out += "HostRead | ";
    if (flag & VkAccessFlagBits::HostWrite) out += "HostWrite | ";
    if (flag & VkAccessFlagBits::MemoryRead) out += "MemoryRead | ";
    if (flag & VkAccessFlagBits::MemoryWrite) out += "MemoryWrite | ";
    if (flag & VkAccessFlagBits::TransformFeedbackWriteBitEXT) out += "TransformFeedbackWriteBitEXT | ";
    if (flag & VkAccessFlagBits::TransformFeedbackCounterReadBitEXT) out += "TransformFeedbackCounterReadBitEXT | ";
    if (flag & VkAccessFlagBits::TransformFeedbackCounterWriteBitEXT) out += "TransformFeedbackCounterWriteBitEXT | ";
    if (flag & VkAccessFlagBits::ConditionalRenderingReadBitEXT) out += "ConditionalRenderingReadBitEXT | ";
    if (flag & VkAccessFlagBits::ColorAttachmentReadNoncoherentBitEXT) out += "ColorAttachmentReadNoncoherentBitEXT | ";
    if (flag & VkAccessFlagBits::AccelerationStructureReadBitKHR) out += "AccelerationStructureReadBitKHR | ";
    if (flag & VkAccessFlagBits::AccelerationStructureWriteBitKHR) out += "AccelerationStructureWriteBitKHR | ";
    if (flag & VkAccessFlagBits::ShadingRateImageReadBitNV) out += "ShadingRateImageReadBitNV | ";
    if (flag & VkAccessFlagBits::FragmentDensityMapReadBitEXT) out += "FragmentDensityMapReadBitEXT | ";
    if (flag & VkAccessFlagBits::CommandPreprocessReadBitNV) out += "CommandPreprocessReadBitNV | ";
    if (flag & VkAccessFlagBits::CommandPreprocessWriteBitNV) out += "CommandPreprocessWriteBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkBufferUsageFlagBits val) {
    switch(val) {
        case(VkBufferUsageFlagBits::TransferSrc): return "TransferSrc";
        case(VkBufferUsageFlagBits::TransferDst): return "TransferDst";
        case(VkBufferUsageFlagBits::UniformTexelBuffer): return "UniformTexelBuffer";
        case(VkBufferUsageFlagBits::StorageTexelBuffer): return "StorageTexelBuffer";
        case(VkBufferUsageFlagBits::UniformBuffer): return "UniformBuffer";
        case(VkBufferUsageFlagBits::StorageBuffer): return "StorageBuffer";
        case(VkBufferUsageFlagBits::IndexBuffer): return "IndexBuffer";
        case(VkBufferUsageFlagBits::VertexBuffer): return "VertexBuffer";
        case(VkBufferUsageFlagBits::IndirectBuffer): return "IndirectBuffer";
        case(VkBufferUsageFlagBits::VideoDecodeSrcBitKHR): return "VideoDecodeSrcBitKHR";
        case(VkBufferUsageFlagBits::VideoDecodeDstBitKHR): return "VideoDecodeDstBitKHR";
        case(VkBufferUsageFlagBits::VideoEncodeDstBitKHR): return "VideoEncodeDstBitKHR";
        case(VkBufferUsageFlagBits::VideoEncodeSrcBitKHR): return "VideoEncodeSrcBitKHR";
        case(VkBufferUsageFlagBits::TransformFeedbackBufferBitEXT): return "TransformFeedbackBufferBitEXT";
        case(VkBufferUsageFlagBits::TransformFeedbackCounterBufferBitEXT): return "TransformFeedbackCounterBufferBitEXT";
        case(VkBufferUsageFlagBits::ConditionalRenderingBitEXT): return "ConditionalRenderingBitEXT";
        case(VkBufferUsageFlagBits::AccelerationStructureBuildInputReadOnlyBitKHR): return "AccelerationStructureBuildInputReadOnlyBitKHR";
        case(VkBufferUsageFlagBits::AccelerationStructureStorageBitKHR): return "AccelerationStructureStorageBitKHR";
        case(VkBufferUsageFlagBits::ShaderBindingTableBitKHR): return "ShaderBindingTableBitKHR";
        case(VkBufferUsageFlagBits::ShaderDeviceAddress): return "ShaderDeviceAddress";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkBufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkBufferUsageFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & VkBufferUsageFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & VkBufferUsageFlagBits::UniformTexelBuffer) out += "UniformTexelBuffer | ";
    if (flag & VkBufferUsageFlagBits::StorageTexelBuffer) out += "StorageTexelBuffer | ";
    if (flag & VkBufferUsageFlagBits::UniformBuffer) out += "UniformBuffer | ";
    if (flag & VkBufferUsageFlagBits::StorageBuffer) out += "StorageBuffer | ";
    if (flag & VkBufferUsageFlagBits::IndexBuffer) out += "IndexBuffer | ";
    if (flag & VkBufferUsageFlagBits::VertexBuffer) out += "VertexBuffer | ";
    if (flag & VkBufferUsageFlagBits::IndirectBuffer) out += "IndirectBuffer | ";
    if (flag & VkBufferUsageFlagBits::VideoDecodeSrcBitKHR) out += "VideoDecodeSrcBitKHR | ";
    if (flag & VkBufferUsageFlagBits::VideoDecodeDstBitKHR) out += "VideoDecodeDstBitKHR | ";
    if (flag & VkBufferUsageFlagBits::VideoEncodeDstBitKHR) out += "VideoEncodeDstBitKHR | ";
    if (flag & VkBufferUsageFlagBits::VideoEncodeSrcBitKHR) out += "VideoEncodeSrcBitKHR | ";
    if (flag & VkBufferUsageFlagBits::TransformFeedbackBufferBitEXT) out += "TransformFeedbackBufferBitEXT | ";
    if (flag & VkBufferUsageFlagBits::TransformFeedbackCounterBufferBitEXT) out += "TransformFeedbackCounterBufferBitEXT | ";
    if (flag & VkBufferUsageFlagBits::ConditionalRenderingBitEXT) out += "ConditionalRenderingBitEXT | ";
    if (flag & VkBufferUsageFlagBits::AccelerationStructureBuildInputReadOnlyBitKHR) out += "AccelerationStructureBuildInputReadOnlyBitKHR | ";
    if (flag & VkBufferUsageFlagBits::AccelerationStructureStorageBitKHR) out += "AccelerationStructureStorageBitKHR | ";
    if (flag & VkBufferUsageFlagBits::ShaderBindingTableBitKHR) out += "ShaderBindingTableBitKHR | ";
    if (flag & VkBufferUsageFlagBits::ShaderDeviceAddress) out += "ShaderDeviceAddress | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkBufferCreateFlagBits val) {
    switch(val) {
        case(VkBufferCreateFlagBits::SparseBinding): return "SparseBinding";
        case(VkBufferCreateFlagBits::SparseResidency): return "SparseResidency";
        case(VkBufferCreateFlagBits::SparseAliased): return "SparseAliased";
        case(VkBufferCreateFlagBits::Protected): return "Protected";
        case(VkBufferCreateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkBufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkBufferCreateFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & VkBufferCreateFlagBits::SparseResidency) out += "SparseResidency | ";
    if (flag & VkBufferCreateFlagBits::SparseAliased) out += "SparseAliased | ";
    if (flag & VkBufferCreateFlagBits::Protected) out += "Protected | ";
    if (flag & VkBufferCreateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkShaderStageFlagBits val) {
    switch(val) {
        case(VkShaderStageFlagBits::Vertex): return "Vertex";
        case(VkShaderStageFlagBits::TessellationControl): return "TessellationControl";
        case(VkShaderStageFlagBits::TessellationEvaluation): return "TessellationEvaluation";
        case(VkShaderStageFlagBits::Geometry): return "Geometry";
        case(VkShaderStageFlagBits::Fragment): return "Fragment";
        case(VkShaderStageFlagBits::Compute): return "Compute";
        case(VkShaderStageFlagBits::RaygenBitKHR): return "RaygenBitKHR";
        case(VkShaderStageFlagBits::AnyHitBitKHR): return "AnyHitBitKHR";
        case(VkShaderStageFlagBits::ClosestHitBitKHR): return "ClosestHitBitKHR";
        case(VkShaderStageFlagBits::MissBitKHR): return "MissBitKHR";
        case(VkShaderStageFlagBits::IntersectionBitKHR): return "IntersectionBitKHR";
        case(VkShaderStageFlagBits::CallableBitKHR): return "CallableBitKHR";
        case(VkShaderStageFlagBits::TaskBitNV): return "TaskBitNV";
        case(VkShaderStageFlagBits::MeshBitNV): return "MeshBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkShaderStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkShaderStageFlagBits::Vertex) out += "Vertex | ";
    if (flag & VkShaderStageFlagBits::TessellationControl) out += "TessellationControl | ";
    if (flag & VkShaderStageFlagBits::TessellationEvaluation) out += "TessellationEvaluation | ";
    if (flag & VkShaderStageFlagBits::Geometry) out += "Geometry | ";
    if (flag & VkShaderStageFlagBits::Fragment) out += "Fragment | ";
    if (flag & VkShaderStageFlagBits::Compute) out += "Compute | ";
    if (flag & VkShaderStageFlagBits::RaygenBitKHR) out += "RaygenBitKHR | ";
    if (flag & VkShaderStageFlagBits::AnyHitBitKHR) out += "AnyHitBitKHR | ";
    if (flag & VkShaderStageFlagBits::ClosestHitBitKHR) out += "ClosestHitBitKHR | ";
    if (flag & VkShaderStageFlagBits::MissBitKHR) out += "MissBitKHR | ";
    if (flag & VkShaderStageFlagBits::IntersectionBitKHR) out += "IntersectionBitKHR | ";
    if (flag & VkShaderStageFlagBits::CallableBitKHR) out += "CallableBitKHR | ";
    if (flag & VkShaderStageFlagBits::TaskBitNV) out += "TaskBitNV | ";
    if (flag & VkShaderStageFlagBits::MeshBitNV) out += "MeshBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkImageUsageFlagBits val) {
    switch(val) {
        case(VkImageUsageFlagBits::TransferSrc): return "TransferSrc";
        case(VkImageUsageFlagBits::TransferDst): return "TransferDst";
        case(VkImageUsageFlagBits::Sampled): return "Sampled";
        case(VkImageUsageFlagBits::Storage): return "Storage";
        case(VkImageUsageFlagBits::ColorAttachment): return "ColorAttachment";
        case(VkImageUsageFlagBits::DepthStencilAttachment): return "DepthStencilAttachment";
        case(VkImageUsageFlagBits::TransientAttachment): return "TransientAttachment";
        case(VkImageUsageFlagBits::InputAttachment): return "InputAttachment";
        case(VkImageUsageFlagBits::VideoDecodeDstBitKHR): return "VideoDecodeDstBitKHR";
        case(VkImageUsageFlagBits::VideoDecodeSrcBitKHR): return "VideoDecodeSrcBitKHR";
        case(VkImageUsageFlagBits::VideoDecodeDpbBitKHR): return "VideoDecodeDpbBitKHR";
        case(VkImageUsageFlagBits::VideoEncodeDstBitKHR): return "VideoEncodeDstBitKHR";
        case(VkImageUsageFlagBits::VideoEncodeSrcBitKHR): return "VideoEncodeSrcBitKHR";
        case(VkImageUsageFlagBits::VideoEncodeDpbBitKHR): return "VideoEncodeDpbBitKHR";
        case(VkImageUsageFlagBits::ShadingRateImageBitNV): return "ShadingRateImageBitNV";
        case(VkImageUsageFlagBits::FragmentDensityMapBitEXT): return "FragmentDensityMapBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkImageUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkImageUsageFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & VkImageUsageFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & VkImageUsageFlagBits::Sampled) out += "Sampled | ";
    if (flag & VkImageUsageFlagBits::Storage) out += "Storage | ";
    if (flag & VkImageUsageFlagBits::ColorAttachment) out += "ColorAttachment | ";
    if (flag & VkImageUsageFlagBits::DepthStencilAttachment) out += "DepthStencilAttachment | ";
    if (flag & VkImageUsageFlagBits::TransientAttachment) out += "TransientAttachment | ";
    if (flag & VkImageUsageFlagBits::InputAttachment) out += "InputAttachment | ";
    if (flag & VkImageUsageFlagBits::VideoDecodeDstBitKHR) out += "VideoDecodeDstBitKHR | ";
    if (flag & VkImageUsageFlagBits::VideoDecodeSrcBitKHR) out += "VideoDecodeSrcBitKHR | ";
    if (flag & VkImageUsageFlagBits::VideoDecodeDpbBitKHR) out += "VideoDecodeDpbBitKHR | ";
    if (flag & VkImageUsageFlagBits::VideoEncodeDstBitKHR) out += "VideoEncodeDstBitKHR | ";
    if (flag & VkImageUsageFlagBits::VideoEncodeSrcBitKHR) out += "VideoEncodeSrcBitKHR | ";
    if (flag & VkImageUsageFlagBits::VideoEncodeDpbBitKHR) out += "VideoEncodeDpbBitKHR | ";
    if (flag & VkImageUsageFlagBits::ShadingRateImageBitNV) out += "ShadingRateImageBitNV | ";
    if (flag & VkImageUsageFlagBits::FragmentDensityMapBitEXT) out += "FragmentDensityMapBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkImageCreateFlagBits val) {
    switch(val) {
        case(VkImageCreateFlagBits::SparseBinding): return "SparseBinding";
        case(VkImageCreateFlagBits::SparseResidency): return "SparseResidency";
        case(VkImageCreateFlagBits::SparseAliased): return "SparseAliased";
        case(VkImageCreateFlagBits::MutableFormat): return "MutableFormat";
        case(VkImageCreateFlagBits::CubeCompatible): return "CubeCompatible";
        case(VkImageCreateFlagBits::CornerSampledBitNV): return "CornerSampledBitNV";
        case(VkImageCreateFlagBits::SampleLocationsCompatibleDepthBitEXT): return "SampleLocationsCompatibleDepthBitEXT";
        case(VkImageCreateFlagBits::SubsampledBitEXT): return "SubsampledBitEXT";
        case(VkImageCreateFlagBits::Alias): return "Alias";
        case(VkImageCreateFlagBits::SplitInstanceBindRegions): return "SplitInstanceBindRegions";
        case(VkImageCreateFlagBits::e2DArrayCompatible): return "e2DArrayCompatible";
        case(VkImageCreateFlagBits::BlockTexelViewCompatible): return "BlockTexelViewCompatible";
        case(VkImageCreateFlagBits::ExtendedUsage): return "ExtendedUsage";
        case(VkImageCreateFlagBits::Protected): return "Protected";
        case(VkImageCreateFlagBits::Disjoint): return "Disjoint";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkImageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkImageCreateFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & VkImageCreateFlagBits::SparseResidency) out += "SparseResidency | ";
    if (flag & VkImageCreateFlagBits::SparseAliased) out += "SparseAliased | ";
    if (flag & VkImageCreateFlagBits::MutableFormat) out += "MutableFormat | ";
    if (flag & VkImageCreateFlagBits::CubeCompatible) out += "CubeCompatible | ";
    if (flag & VkImageCreateFlagBits::CornerSampledBitNV) out += "CornerSampledBitNV | ";
    if (flag & VkImageCreateFlagBits::SampleLocationsCompatibleDepthBitEXT) out += "SampleLocationsCompatibleDepthBitEXT | ";
    if (flag & VkImageCreateFlagBits::SubsampledBitEXT) out += "SubsampledBitEXT | ";
    if (flag & VkImageCreateFlagBits::Alias) out += "Alias | ";
    if (flag & VkImageCreateFlagBits::SplitInstanceBindRegions) out += "SplitInstanceBindRegions | ";
    if (flag & VkImageCreateFlagBits::e2DArrayCompatible) out += "e2DArrayCompatible | ";
    if (flag & VkImageCreateFlagBits::BlockTexelViewCompatible) out += "BlockTexelViewCompatible | ";
    if (flag & VkImageCreateFlagBits::ExtendedUsage) out += "ExtendedUsage | ";
    if (flag & VkImageCreateFlagBits::Protected) out += "Protected | ";
    if (flag & VkImageCreateFlagBits::Disjoint) out += "Disjoint | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkImageViewCreateFlagBits val) {
    switch(val) {
        case(VkImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT): return "FragmentDensityMapDynamicBitEXT";
        case(VkImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT): return "FragmentDensityMapDeferredBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkImageViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT) out += "FragmentDensityMapDynamicBitEXT | ";
    if (flag & VkImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT) out += "FragmentDensityMapDeferredBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSamplerCreateFlagBits val) {
    switch(val) {
        case(VkSamplerCreateFlagBits::SubsampledBitEXT): return "SubsampledBitEXT";
        case(VkSamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT): return "SubsampledCoarseReconstructionBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSamplerCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSamplerCreateFlagBits::SubsampledBitEXT) out += "SubsampledBitEXT | ";
    if (flag & VkSamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT) out += "SubsampledCoarseReconstructionBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPipelineCreateFlagBits val) {
    switch(val) {
        case(VkPipelineCreateFlagBits::DisableOptimization): return "DisableOptimization";
        case(VkPipelineCreateFlagBits::AllowDerivatives): return "AllowDerivatives";
        case(VkPipelineCreateFlagBits::Derivative): return "Derivative";
        case(VkPipelineCreateFlagBits::RayTracingNoNullAnyHitShadersBitKHR): return "RayTracingNoNullAnyHitShadersBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingNoNullClosestHitShadersBitKHR): return "RayTracingNoNullClosestHitShadersBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingNoNullMissShadersBitKHR): return "RayTracingNoNullMissShadersBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingNoNullIntersectionShadersBitKHR): return "RayTracingNoNullIntersectionShadersBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingSkipTrianglesBitKHR): return "RayTracingSkipTrianglesBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingSkipAabbsBitKHR): return "RayTracingSkipAabbsBitKHR";
        case(VkPipelineCreateFlagBits::RayTracingShaderGroupHandleCaptureReplayBitKHR): return "RayTracingShaderGroupHandleCaptureReplayBitKHR";
        case(VkPipelineCreateFlagBits::DeferCompileBitNV): return "DeferCompileBitNV";
        case(VkPipelineCreateFlagBits::CaptureStatisticsBitKHR): return "CaptureStatisticsBitKHR";
        case(VkPipelineCreateFlagBits::CaptureInternalRepresentationsBitKHR): return "CaptureInternalRepresentationsBitKHR";
        case(VkPipelineCreateFlagBits::IndirectBindableBitNV): return "IndirectBindableBitNV";
        case(VkPipelineCreateFlagBits::LibraryBitKHR): return "LibraryBitKHR";
        case(VkPipelineCreateFlagBits::FailOnPipelineCompileRequiredBitEXT): return "FailOnPipelineCompileRequiredBitEXT";
        case(VkPipelineCreateFlagBits::EarlyReturnOnFailureBitEXT): return "EarlyReturnOnFailureBitEXT";
        case(VkPipelineCreateFlagBits::ViewIndexFromDeviceIndex): return "ViewIndexFromDeviceIndex";
        case(VkPipelineCreateFlagBits::DispatchBase): return "DispatchBase";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineCreateFlagBits::DisableOptimization) out += "DisableOptimization | ";
    if (flag & VkPipelineCreateFlagBits::AllowDerivatives) out += "AllowDerivatives | ";
    if (flag & VkPipelineCreateFlagBits::Derivative) out += "Derivative | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingNoNullAnyHitShadersBitKHR) out += "RayTracingNoNullAnyHitShadersBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingNoNullClosestHitShadersBitKHR) out += "RayTracingNoNullClosestHitShadersBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingNoNullMissShadersBitKHR) out += "RayTracingNoNullMissShadersBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingNoNullIntersectionShadersBitKHR) out += "RayTracingNoNullIntersectionShadersBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingSkipTrianglesBitKHR) out += "RayTracingSkipTrianglesBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingSkipAabbsBitKHR) out += "RayTracingSkipAabbsBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::RayTracingShaderGroupHandleCaptureReplayBitKHR) out += "RayTracingShaderGroupHandleCaptureReplayBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::DeferCompileBitNV) out += "DeferCompileBitNV | ";
    if (flag & VkPipelineCreateFlagBits::CaptureStatisticsBitKHR) out += "CaptureStatisticsBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::CaptureInternalRepresentationsBitKHR) out += "CaptureInternalRepresentationsBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::IndirectBindableBitNV) out += "IndirectBindableBitNV | ";
    if (flag & VkPipelineCreateFlagBits::LibraryBitKHR) out += "LibraryBitKHR | ";
    if (flag & VkPipelineCreateFlagBits::FailOnPipelineCompileRequiredBitEXT) out += "FailOnPipelineCompileRequiredBitEXT | ";
    if (flag & VkPipelineCreateFlagBits::EarlyReturnOnFailureBitEXT) out += "EarlyReturnOnFailureBitEXT | ";
    if (flag & VkPipelineCreateFlagBits::ViewIndexFromDeviceIndex) out += "ViewIndexFromDeviceIndex | ";
    if (flag & VkPipelineCreateFlagBits::DispatchBase) out += "DispatchBase | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPipelineShaderStageCreateFlagBits val) {
    switch(val) {
        case(VkPipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT): return "AllowVaryingSubgroupSizeBitEXT";
        case(VkPipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT): return "RequireFullSubgroupsBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineShaderStageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT) out += "AllowVaryingSubgroupSizeBitEXT | ";
    if (flag & VkPipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT) out += "RequireFullSubgroupsBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkColorComponentFlagBits val) {
    switch(val) {
        case(VkColorComponentFlagBits::R): return "R";
        case(VkColorComponentFlagBits::G): return "G";
        case(VkColorComponentFlagBits::B): return "B";
        case(VkColorComponentFlagBits::A): return "A";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkColorComponentFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkColorComponentFlagBits::R) out += "R | ";
    if (flag & VkColorComponentFlagBits::G) out += "G | ";
    if (flag & VkColorComponentFlagBits::B) out += "B | ";
    if (flag & VkColorComponentFlagBits::A) out += "A | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkFenceCreateFlagBits val) {
    switch(val) {
        case(VkFenceCreateFlagBits::Signaled): return "Signaled";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkFenceCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkFenceCreateFlagBits::Signaled) out += "Signaled | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkFormatFeatureFlagBits val) {
    switch(val) {
        case(VkFormatFeatureFlagBits::SampledImage): return "SampledImage";
        case(VkFormatFeatureFlagBits::StorageImage): return "StorageImage";
        case(VkFormatFeatureFlagBits::StorageImageAtomic): return "StorageImageAtomic";
        case(VkFormatFeatureFlagBits::UniformTexelBuffer): return "UniformTexelBuffer";
        case(VkFormatFeatureFlagBits::StorageTexelBuffer): return "StorageTexelBuffer";
        case(VkFormatFeatureFlagBits::StorageTexelBufferAtomic): return "StorageTexelBufferAtomic";
        case(VkFormatFeatureFlagBits::VertexBuffer): return "VertexBuffer";
        case(VkFormatFeatureFlagBits::ColorAttachment): return "ColorAttachment";
        case(VkFormatFeatureFlagBits::ColorAttachmentBlend): return "ColorAttachmentBlend";
        case(VkFormatFeatureFlagBits::DepthStencilAttachment): return "DepthStencilAttachment";
        case(VkFormatFeatureFlagBits::BlitSrc): return "BlitSrc";
        case(VkFormatFeatureFlagBits::BlitDst): return "BlitDst";
        case(VkFormatFeatureFlagBits::SampledImageFilterLinear): return "SampledImageFilterLinear";
        case(VkFormatFeatureFlagBits::SampledImageFilterCubicBitIMG): return "SampledImageFilterCubicBitIMG";
        case(VkFormatFeatureFlagBits::VideoDecodeOutputBitKHR): return "VideoDecodeOutputBitKHR";
        case(VkFormatFeatureFlagBits::VideoDecodeDpbBitKHR): return "VideoDecodeDpbBitKHR";
        case(VkFormatFeatureFlagBits::VideoEncodeInputBitKHR): return "VideoEncodeInputBitKHR";
        case(VkFormatFeatureFlagBits::VideoEncodeDpbBitKHR): return "VideoEncodeDpbBitKHR";
        case(VkFormatFeatureFlagBits::AccelerationStructureVertexBufferBitKHR): return "AccelerationStructureVertexBufferBitKHR";
        case(VkFormatFeatureFlagBits::FragmentDensityMapBitEXT): return "FragmentDensityMapBitEXT";
        case(VkFormatFeatureFlagBits::FragmentShadingRateAttachmentBitKHR): return "FragmentShadingRateAttachmentBitKHR";
        case(VkFormatFeatureFlagBits::TransferSrc): return "TransferSrc";
        case(VkFormatFeatureFlagBits::TransferDst): return "TransferDst";
        case(VkFormatFeatureFlagBits::MidpointChromaSamples): return "MidpointChromaSamples";
        case(VkFormatFeatureFlagBits::SampledImageYcbcrConversionLinearFilter): return "SampledImageYcbcrConversionLinearFilter";
        case(VkFormatFeatureFlagBits::SampledImageYcbcrConversionSeparateReconstructionFilter): return "SampledImageYcbcrConversionSeparateReconstructionFilter";
        case(VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicit): return "SampledImageYcbcrConversionChromaReconstructionExplicit";
        case(VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicitForceable): return "SampledImageYcbcrConversionChromaReconstructionExplicitForceable";
        case(VkFormatFeatureFlagBits::Disjoint): return "Disjoint";
        case(VkFormatFeatureFlagBits::CositedChromaSamples): return "CositedChromaSamples";
        case(VkFormatFeatureFlagBits::SampledImageFilterMinmax): return "SampledImageFilterMinmax";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkFormatFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkFormatFeatureFlagBits::SampledImage) out += "SampledImage | ";
    if (flag & VkFormatFeatureFlagBits::StorageImage) out += "StorageImage | ";
    if (flag & VkFormatFeatureFlagBits::StorageImageAtomic) out += "StorageImageAtomic | ";
    if (flag & VkFormatFeatureFlagBits::UniformTexelBuffer) out += "UniformTexelBuffer | ";
    if (flag & VkFormatFeatureFlagBits::StorageTexelBuffer) out += "StorageTexelBuffer | ";
    if (flag & VkFormatFeatureFlagBits::StorageTexelBufferAtomic) out += "StorageTexelBufferAtomic | ";
    if (flag & VkFormatFeatureFlagBits::VertexBuffer) out += "VertexBuffer | ";
    if (flag & VkFormatFeatureFlagBits::ColorAttachment) out += "ColorAttachment | ";
    if (flag & VkFormatFeatureFlagBits::ColorAttachmentBlend) out += "ColorAttachmentBlend | ";
    if (flag & VkFormatFeatureFlagBits::DepthStencilAttachment) out += "DepthStencilAttachment | ";
    if (flag & VkFormatFeatureFlagBits::BlitSrc) out += "BlitSrc | ";
    if (flag & VkFormatFeatureFlagBits::BlitDst) out += "BlitDst | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageFilterLinear) out += "SampledImageFilterLinear | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageFilterCubicBitIMG) out += "SampledImageFilterCubicBitIMG | ";
    if (flag & VkFormatFeatureFlagBits::VideoDecodeOutputBitKHR) out += "VideoDecodeOutputBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::VideoDecodeDpbBitKHR) out += "VideoDecodeDpbBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::VideoEncodeInputBitKHR) out += "VideoEncodeInputBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::VideoEncodeDpbBitKHR) out += "VideoEncodeDpbBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::AccelerationStructureVertexBufferBitKHR) out += "AccelerationStructureVertexBufferBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::FragmentDensityMapBitEXT) out += "FragmentDensityMapBitEXT | ";
    if (flag & VkFormatFeatureFlagBits::FragmentShadingRateAttachmentBitKHR) out += "FragmentShadingRateAttachmentBitKHR | ";
    if (flag & VkFormatFeatureFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & VkFormatFeatureFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & VkFormatFeatureFlagBits::MidpointChromaSamples) out += "MidpointChromaSamples | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageYcbcrConversionLinearFilter) out += "SampledImageYcbcrConversionLinearFilter | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageYcbcrConversionSeparateReconstructionFilter) out += "SampledImageYcbcrConversionSeparateReconstructionFilter | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicit) out += "SampledImageYcbcrConversionChromaReconstructionExplicit | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicitForceable) out += "SampledImageYcbcrConversionChromaReconstructionExplicitForceable | ";
    if (flag & VkFormatFeatureFlagBits::Disjoint) out += "Disjoint | ";
    if (flag & VkFormatFeatureFlagBits::CositedChromaSamples) out += "CositedChromaSamples | ";
    if (flag & VkFormatFeatureFlagBits::SampledImageFilterMinmax) out += "SampledImageFilterMinmax | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkQueryControlFlagBits val) {
    switch(val) {
        case(VkQueryControlFlagBits::Precise): return "Precise";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkQueryControlFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkQueryControlFlagBits::Precise) out += "Precise | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkQueryResultFlagBits val) {
    switch(val) {
        case(VkQueryResultFlagBits::e64): return "e64";
        case(VkQueryResultFlagBits::Wait): return "Wait";
        case(VkQueryResultFlagBits::WithAvailability): return "WithAvailability";
        case(VkQueryResultFlagBits::Partial): return "Partial";
        case(VkQueryResultFlagBits::WithStatusBitKHR): return "WithStatusBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkQueryResultFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkQueryResultFlagBits::e64) out += "e64 | ";
    if (flag & VkQueryResultFlagBits::Wait) out += "Wait | ";
    if (flag & VkQueryResultFlagBits::WithAvailability) out += "WithAvailability | ";
    if (flag & VkQueryResultFlagBits::Partial) out += "Partial | ";
    if (flag & VkQueryResultFlagBits::WithStatusBitKHR) out += "WithStatusBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCommandBufferUsageFlagBits val) {
    switch(val) {
        case(VkCommandBufferUsageFlagBits::OneTimeSubmit): return "OneTimeSubmit";
        case(VkCommandBufferUsageFlagBits::RenderPassContinue): return "RenderPassContinue";
        case(VkCommandBufferUsageFlagBits::SimultaneousUse): return "SimultaneousUse";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCommandBufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCommandBufferUsageFlagBits::OneTimeSubmit) out += "OneTimeSubmit | ";
    if (flag & VkCommandBufferUsageFlagBits::RenderPassContinue) out += "RenderPassContinue | ";
    if (flag & VkCommandBufferUsageFlagBits::SimultaneousUse) out += "SimultaneousUse | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkQueryPipelineStatisticFlagBits val) {
    switch(val) {
        case(VkQueryPipelineStatisticFlagBits::InputAssemblyVertices): return "InputAssemblyVertices";
        case(VkQueryPipelineStatisticFlagBits::InputAssemblyPrimitives): return "InputAssemblyPrimitives";
        case(VkQueryPipelineStatisticFlagBits::VertexShaderInvocations): return "VertexShaderInvocations";
        case(VkQueryPipelineStatisticFlagBits::GeometryShaderInvocations): return "GeometryShaderInvocations";
        case(VkQueryPipelineStatisticFlagBits::GeometryShaderPrimitives): return "GeometryShaderPrimitives";
        case(VkQueryPipelineStatisticFlagBits::ClippingInvocations): return "ClippingInvocations";
        case(VkQueryPipelineStatisticFlagBits::ClippingPrimitives): return "ClippingPrimitives";
        case(VkQueryPipelineStatisticFlagBits::FragmentShaderInvocations): return "FragmentShaderInvocations";
        case(VkQueryPipelineStatisticFlagBits::TessellationControlShaderPatches): return "TessellationControlShaderPatches";
        case(VkQueryPipelineStatisticFlagBits::TessellationEvaluationShaderInvocations): return "TessellationEvaluationShaderInvocations";
        case(VkQueryPipelineStatisticFlagBits::ComputeShaderInvocations): return "ComputeShaderInvocations";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkQueryPipelineStatisticFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkQueryPipelineStatisticFlagBits::InputAssemblyVertices) out += "InputAssemblyVertices | ";
    if (flag & VkQueryPipelineStatisticFlagBits::InputAssemblyPrimitives) out += "InputAssemblyPrimitives | ";
    if (flag & VkQueryPipelineStatisticFlagBits::VertexShaderInvocations) out += "VertexShaderInvocations | ";
    if (flag & VkQueryPipelineStatisticFlagBits::GeometryShaderInvocations) out += "GeometryShaderInvocations | ";
    if (flag & VkQueryPipelineStatisticFlagBits::GeometryShaderPrimitives) out += "GeometryShaderPrimitives | ";
    if (flag & VkQueryPipelineStatisticFlagBits::ClippingInvocations) out += "ClippingInvocations | ";
    if (flag & VkQueryPipelineStatisticFlagBits::ClippingPrimitives) out += "ClippingPrimitives | ";
    if (flag & VkQueryPipelineStatisticFlagBits::FragmentShaderInvocations) out += "FragmentShaderInvocations | ";
    if (flag & VkQueryPipelineStatisticFlagBits::TessellationControlShaderPatches) out += "TessellationControlShaderPatches | ";
    if (flag & VkQueryPipelineStatisticFlagBits::TessellationEvaluationShaderInvocations) out += "TessellationEvaluationShaderInvocations | ";
    if (flag & VkQueryPipelineStatisticFlagBits::ComputeShaderInvocations) out += "ComputeShaderInvocations | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkImageAspectFlagBits val) {
    switch(val) {
        case(VkImageAspectFlagBits::Color): return "Color";
        case(VkImageAspectFlagBits::Depth): return "Depth";
        case(VkImageAspectFlagBits::Stencil): return "Stencil";
        case(VkImageAspectFlagBits::Metadata): return "Metadata";
        case(VkImageAspectFlagBits::MemoryPlane0BitEXT): return "MemoryPlane0BitEXT";
        case(VkImageAspectFlagBits::MemoryPlane1BitEXT): return "MemoryPlane1BitEXT";
        case(VkImageAspectFlagBits::MemoryPlane2BitEXT): return "MemoryPlane2BitEXT";
        case(VkImageAspectFlagBits::MemoryPlane3BitEXT): return "MemoryPlane3BitEXT";
        case(VkImageAspectFlagBits::Plane0): return "Plane0";
        case(VkImageAspectFlagBits::Plane1): return "Plane1";
        case(VkImageAspectFlagBits::Plane2): return "Plane2";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkImageAspectFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkImageAspectFlagBits::Color) out += "Color | ";
    if (flag & VkImageAspectFlagBits::Depth) out += "Depth | ";
    if (flag & VkImageAspectFlagBits::Stencil) out += "Stencil | ";
    if (flag & VkImageAspectFlagBits::Metadata) out += "Metadata | ";
    if (flag & VkImageAspectFlagBits::MemoryPlane0BitEXT) out += "MemoryPlane0BitEXT | ";
    if (flag & VkImageAspectFlagBits::MemoryPlane1BitEXT) out += "MemoryPlane1BitEXT | ";
    if (flag & VkImageAspectFlagBits::MemoryPlane2BitEXT) out += "MemoryPlane2BitEXT | ";
    if (flag & VkImageAspectFlagBits::MemoryPlane3BitEXT) out += "MemoryPlane3BitEXT | ";
    if (flag & VkImageAspectFlagBits::Plane0) out += "Plane0 | ";
    if (flag & VkImageAspectFlagBits::Plane1) out += "Plane1 | ";
    if (flag & VkImageAspectFlagBits::Plane2) out += "Plane2 | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSparseImageFormatFlagBits val) {
    switch(val) {
        case(VkSparseImageFormatFlagBits::SingleMiptail): return "SingleMiptail";
        case(VkSparseImageFormatFlagBits::AlignedMipSize): return "AlignedMipSize";
        case(VkSparseImageFormatFlagBits::NonstandardBlockSize): return "NonstandardBlockSize";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSparseImageFormatFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSparseImageFormatFlagBits::SingleMiptail) out += "SingleMiptail | ";
    if (flag & VkSparseImageFormatFlagBits::AlignedMipSize) out += "AlignedMipSize | ";
    if (flag & VkSparseImageFormatFlagBits::NonstandardBlockSize) out += "NonstandardBlockSize | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSparseMemoryBindFlagBits val) {
    switch(val) {
        case(VkSparseMemoryBindFlagBits::Metadata): return "Metadata";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSparseMemoryBindFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSparseMemoryBindFlagBits::Metadata) out += "Metadata | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPipelineStageFlagBits val) {
    switch(val) {
        case(VkPipelineStageFlagBits::NoneKHR): return "NoneKHR";
        case(VkPipelineStageFlagBits::DrawIndirect): return "DrawIndirect";
        case(VkPipelineStageFlagBits::VertexInput): return "VertexInput";
        case(VkPipelineStageFlagBits::VertexShader): return "VertexShader";
        case(VkPipelineStageFlagBits::TessellationControlShader): return "TessellationControlShader";
        case(VkPipelineStageFlagBits::TessellationEvaluationShader): return "TessellationEvaluationShader";
        case(VkPipelineStageFlagBits::GeometryShader): return "GeometryShader";
        case(VkPipelineStageFlagBits::FragmentShader): return "FragmentShader";
        case(VkPipelineStageFlagBits::EarlyFragmentTests): return "EarlyFragmentTests";
        case(VkPipelineStageFlagBits::LateFragmentTests): return "LateFragmentTests";
        case(VkPipelineStageFlagBits::ColorAttachmentOutput): return "ColorAttachmentOutput";
        case(VkPipelineStageFlagBits::ComputeShader): return "ComputeShader";
        case(VkPipelineStageFlagBits::Transfer): return "Transfer";
        case(VkPipelineStageFlagBits::BottomOfPipe): return "BottomOfPipe";
        case(VkPipelineStageFlagBits::Host): return "Host";
        case(VkPipelineStageFlagBits::AllGraphics): return "AllGraphics";
        case(VkPipelineStageFlagBits::AllCommands): return "AllCommands";
        case(VkPipelineStageFlagBits::TransformFeedbackBitEXT): return "TransformFeedbackBitEXT";
        case(VkPipelineStageFlagBits::ConditionalRenderingBitEXT): return "ConditionalRenderingBitEXT";
        case(VkPipelineStageFlagBits::AccelerationStructureBuildBitKHR): return "AccelerationStructureBuildBitKHR";
        case(VkPipelineStageFlagBits::RayTracingShaderBitKHR): return "RayTracingShaderBitKHR";
        case(VkPipelineStageFlagBits::ShadingRateImageBitNV): return "ShadingRateImageBitNV";
        case(VkPipelineStageFlagBits::TaskShaderBitNV): return "TaskShaderBitNV";
        case(VkPipelineStageFlagBits::MeshShaderBitNV): return "MeshShaderBitNV";
        case(VkPipelineStageFlagBits::FragmentDensityProcessBitEXT): return "FragmentDensityProcessBitEXT";
        case(VkPipelineStageFlagBits::CommandPreprocessBitNV): return "CommandPreprocessBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineStageFlagBits::NoneKHR) out += "NoneKHR | ";
    if (flag & VkPipelineStageFlagBits::DrawIndirect) out += "DrawIndirect | ";
    if (flag & VkPipelineStageFlagBits::VertexInput) out += "VertexInput | ";
    if (flag & VkPipelineStageFlagBits::VertexShader) out += "VertexShader | ";
    if (flag & VkPipelineStageFlagBits::TessellationControlShader) out += "TessellationControlShader | ";
    if (flag & VkPipelineStageFlagBits::TessellationEvaluationShader) out += "TessellationEvaluationShader | ";
    if (flag & VkPipelineStageFlagBits::GeometryShader) out += "GeometryShader | ";
    if (flag & VkPipelineStageFlagBits::FragmentShader) out += "FragmentShader | ";
    if (flag & VkPipelineStageFlagBits::EarlyFragmentTests) out += "EarlyFragmentTests | ";
    if (flag & VkPipelineStageFlagBits::LateFragmentTests) out += "LateFragmentTests | ";
    if (flag & VkPipelineStageFlagBits::ColorAttachmentOutput) out += "ColorAttachmentOutput | ";
    if (flag & VkPipelineStageFlagBits::ComputeShader) out += "ComputeShader | ";
    if (flag & VkPipelineStageFlagBits::Transfer) out += "Transfer | ";
    if (flag & VkPipelineStageFlagBits::BottomOfPipe) out += "BottomOfPipe | ";
    if (flag & VkPipelineStageFlagBits::Host) out += "Host | ";
    if (flag & VkPipelineStageFlagBits::AllGraphics) out += "AllGraphics | ";
    if (flag & VkPipelineStageFlagBits::AllCommands) out += "AllCommands | ";
    if (flag & VkPipelineStageFlagBits::TransformFeedbackBitEXT) out += "TransformFeedbackBitEXT | ";
    if (flag & VkPipelineStageFlagBits::ConditionalRenderingBitEXT) out += "ConditionalRenderingBitEXT | ";
    if (flag & VkPipelineStageFlagBits::AccelerationStructureBuildBitKHR) out += "AccelerationStructureBuildBitKHR | ";
    if (flag & VkPipelineStageFlagBits::RayTracingShaderBitKHR) out += "RayTracingShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits::ShadingRateImageBitNV) out += "ShadingRateImageBitNV | ";
    if (flag & VkPipelineStageFlagBits::TaskShaderBitNV) out += "TaskShaderBitNV | ";
    if (flag & VkPipelineStageFlagBits::MeshShaderBitNV) out += "MeshShaderBitNV | ";
    if (flag & VkPipelineStageFlagBits::FragmentDensityProcessBitEXT) out += "FragmentDensityProcessBitEXT | ";
    if (flag & VkPipelineStageFlagBits::CommandPreprocessBitNV) out += "CommandPreprocessBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCommandPoolCreateFlagBits val) {
    switch(val) {
        case(VkCommandPoolCreateFlagBits::Transient): return "Transient";
        case(VkCommandPoolCreateFlagBits::ResetCommandBuffer): return "ResetCommandBuffer";
        case(VkCommandPoolCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCommandPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCommandPoolCreateFlagBits::Transient) out += "Transient | ";
    if (flag & VkCommandPoolCreateFlagBits::ResetCommandBuffer) out += "ResetCommandBuffer | ";
    if (flag & VkCommandPoolCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCommandPoolResetFlagBits val) {
    switch(val) {
        case(VkCommandPoolResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCommandPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCommandPoolResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCommandBufferResetFlagBits val) {
    switch(val) {
        case(VkCommandBufferResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCommandBufferResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCommandBufferResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSampleCountFlagBits val) {
    switch(val) {
        case(VkSampleCountFlagBits::e1): return "e1";
        case(VkSampleCountFlagBits::e2): return "e2";
        case(VkSampleCountFlagBits::e4): return "e4";
        case(VkSampleCountFlagBits::e8): return "e8";
        case(VkSampleCountFlagBits::e16): return "e16";
        case(VkSampleCountFlagBits::e32): return "e32";
        case(VkSampleCountFlagBits::e64): return "e64";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSampleCountFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSampleCountFlagBits::e1) out += "e1 | ";
    if (flag & VkSampleCountFlagBits::e2) out += "e2 | ";
    if (flag & VkSampleCountFlagBits::e4) out += "e4 | ";
    if (flag & VkSampleCountFlagBits::e8) out += "e8 | ";
    if (flag & VkSampleCountFlagBits::e16) out += "e16 | ";
    if (flag & VkSampleCountFlagBits::e32) out += "e32 | ";
    if (flag & VkSampleCountFlagBits::e64) out += "e64 | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkAttachmentDescriptionFlagBits val) {
    switch(val) {
        case(VkAttachmentDescriptionFlagBits::MayAlias): return "MayAlias";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkAttachmentDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkAttachmentDescriptionFlagBits::MayAlias) out += "MayAlias | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkStencilFaceFlagBits val) {
    switch(val) {
        case(VkStencilFaceFlagBits::Front): return "Front";
        case(VkStencilFaceFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkStencilFaceFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkStencilFaceFlagBits::Front) out += "Front | ";
    if (flag & VkStencilFaceFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDescriptorPoolCreateFlagBits val) {
    switch(val) {
        case(VkDescriptorPoolCreateFlagBits::FreeDescriptorSet): return "FreeDescriptorSet";
        case(VkDescriptorPoolCreateFlagBits::HostOnlyBitVALVE): return "HostOnlyBitVALVE";
        case(VkDescriptorPoolCreateFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDescriptorPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDescriptorPoolCreateFlagBits::FreeDescriptorSet) out += "FreeDescriptorSet | ";
    if (flag & VkDescriptorPoolCreateFlagBits::HostOnlyBitVALVE) out += "HostOnlyBitVALVE | ";
    if (flag & VkDescriptorPoolCreateFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDependencyFlagBits val) {
    switch(val) {
        case(VkDependencyFlagBits::ByRegion): return "ByRegion";
        case(VkDependencyFlagBits::DeviceGroup): return "DeviceGroup";
        case(VkDependencyFlagBits::ViewLocal): return "ViewLocal";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDependencyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDependencyFlagBits::ByRegion) out += "ByRegion | ";
    if (flag & VkDependencyFlagBits::DeviceGroup) out += "DeviceGroup | ";
    if (flag & VkDependencyFlagBits::ViewLocal) out += "ViewLocal | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSemaphoreWaitFlagBits val) {
    switch(val) {
        case(VkSemaphoreWaitFlagBits::Any): return "Any";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSemaphoreWaitFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSemaphoreWaitFlagBits::Any) out += "Any | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDisplayPlaneAlphaFlagBitsKHR val) {
    switch(val) {
        case(VkDisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(VkDisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR): return "GlobalBitKHR";
        case(VkDisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR): return "PerPixelBitKHR";
        case(VkDisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR): return "PerPixelPremultipliedBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDisplayPlaneAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & VkDisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR) out += "GlobalBitKHR | ";
    if (flag & VkDisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR) out += "PerPixelBitKHR | ";
    if (flag & VkDisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR) out += "PerPixelPremultipliedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkCompositeAlphaFlagBitsKHR val) {
    switch(val) {
        case(VkCompositeAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(VkCompositeAlphaFlagBitsKHR::PreMultipliedBitKHR): return "PreMultipliedBitKHR";
        case(VkCompositeAlphaFlagBitsKHR::PostMultipliedBitKHR): return "PostMultipliedBitKHR";
        case(VkCompositeAlphaFlagBitsKHR::InheritBitKHR): return "InheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkCompositeAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkCompositeAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & VkCompositeAlphaFlagBitsKHR::PreMultipliedBitKHR) out += "PreMultipliedBitKHR | ";
    if (flag & VkCompositeAlphaFlagBitsKHR::PostMultipliedBitKHR) out += "PostMultipliedBitKHR | ";
    if (flag & VkCompositeAlphaFlagBitsKHR::InheritBitKHR) out += "InheritBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSurfaceTransformFlagBitsKHR val) {
    switch(val) {
        case(VkSurfaceTransformFlagBitsKHR::IdentityBitKHR): return "IdentityBitKHR";
        case(VkSurfaceTransformFlagBitsKHR::Rotate90BitKHR): return "Rotate90BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::Rotate180BitKHR): return "Rotate180BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::Rotate270BitKHR): return "Rotate270BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::HorizontalMirrorBitKHR): return "HorizontalMirrorBitKHR";
        case(VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate90BitKHR): return "HorizontalMirrorRotate90BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate180BitKHR): return "HorizontalMirrorRotate180BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate270BitKHR): return "HorizontalMirrorRotate270BitKHR";
        case(VkSurfaceTransformFlagBitsKHR::InheritBitKHR): return "InheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSurfaceTransformFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSurfaceTransformFlagBitsKHR::IdentityBitKHR) out += "IdentityBitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::Rotate90BitKHR) out += "Rotate90BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::Rotate180BitKHR) out += "Rotate180BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::Rotate270BitKHR) out += "Rotate270BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::HorizontalMirrorBitKHR) out += "HorizontalMirrorBitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate90BitKHR) out += "HorizontalMirrorRotate90BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate180BitKHR) out += "HorizontalMirrorRotate180BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate270BitKHR) out += "HorizontalMirrorRotate270BitKHR | ";
    if (flag & VkSurfaceTransformFlagBitsKHR::InheritBitKHR) out += "InheritBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDebugReportFlagBitsEXT val) {
    switch(val) {
        case(VkDebugReportFlagBitsEXT::InformationBitEXT): return "InformationBitEXT";
        case(VkDebugReportFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(VkDebugReportFlagBitsEXT::PerformanceWarningBitEXT): return "PerformanceWarningBitEXT";
        case(VkDebugReportFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        case(VkDebugReportFlagBitsEXT::DebugBitEXT): return "DebugBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDebugReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDebugReportFlagBitsEXT::InformationBitEXT) out += "InformationBitEXT | ";
    if (flag & VkDebugReportFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & VkDebugReportFlagBitsEXT::PerformanceWarningBitEXT) out += "PerformanceWarningBitEXT | ";
    if (flag & VkDebugReportFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    if (flag & VkDebugReportFlagBitsEXT::DebugBitEXT) out += "DebugBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalMemoryHandleTypeFlagBitsNV val) {
    switch(val) {
        case(VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV): return "OpaqueWin32BitNV";
        case(VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV): return "OpaqueWin32KmtBitNV";
        case(VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV): return "D3D11ImageBitNV";
        case(VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV): return "D3D11ImageKmtBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalMemoryHandleTypeFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV) out += "OpaqueWin32BitNV | ";
    if (flag & VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV) out += "OpaqueWin32KmtBitNV | ";
    if (flag & VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV) out += "D3D11ImageBitNV | ";
    if (flag & VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV) out += "D3D11ImageKmtBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalMemoryFeatureFlagBitsNV val) {
    switch(val) {
        case(VkExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV): return "DedicatedOnlyBitNV";
        case(VkExternalMemoryFeatureFlagBitsNV::ExportableBitNV): return "ExportableBitNV";
        case(VkExternalMemoryFeatureFlagBitsNV::ImportableBitNV): return "ImportableBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalMemoryFeatureFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV) out += "DedicatedOnlyBitNV | ";
    if (flag & VkExternalMemoryFeatureFlagBitsNV::ExportableBitNV) out += "ExportableBitNV | ";
    if (flag & VkExternalMemoryFeatureFlagBitsNV::ImportableBitNV) out += "ImportableBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSubgroupFeatureFlagBits val) {
    switch(val) {
        case(VkSubgroupFeatureFlagBits::Basic): return "Basic";
        case(VkSubgroupFeatureFlagBits::Vote): return "Vote";
        case(VkSubgroupFeatureFlagBits::Arithmetic): return "Arithmetic";
        case(VkSubgroupFeatureFlagBits::Ballot): return "Ballot";
        case(VkSubgroupFeatureFlagBits::Shuffle): return "Shuffle";
        case(VkSubgroupFeatureFlagBits::ShuffleRelative): return "ShuffleRelative";
        case(VkSubgroupFeatureFlagBits::Clustered): return "Clustered";
        case(VkSubgroupFeatureFlagBits::Quad): return "Quad";
        case(VkSubgroupFeatureFlagBits::PartitionedBitNV): return "PartitionedBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSubgroupFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSubgroupFeatureFlagBits::Basic) out += "Basic | ";
    if (flag & VkSubgroupFeatureFlagBits::Vote) out += "Vote | ";
    if (flag & VkSubgroupFeatureFlagBits::Arithmetic) out += "Arithmetic | ";
    if (flag & VkSubgroupFeatureFlagBits::Ballot) out += "Ballot | ";
    if (flag & VkSubgroupFeatureFlagBits::Shuffle) out += "Shuffle | ";
    if (flag & VkSubgroupFeatureFlagBits::ShuffleRelative) out += "ShuffleRelative | ";
    if (flag & VkSubgroupFeatureFlagBits::Clustered) out += "Clustered | ";
    if (flag & VkSubgroupFeatureFlagBits::Quad) out += "Quad | ";
    if (flag & VkSubgroupFeatureFlagBits::PartitionedBitNV) out += "PartitionedBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkIndirectCommandsLayoutUsageFlagBitsNV val) {
    switch(val) {
        case(VkIndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV): return "ExplicitPreprocessBitNV";
        case(VkIndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV): return "IndexedSequencesBitNV";
        case(VkIndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV): return "UnorderedSequencesBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkIndirectCommandsLayoutUsageFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkIndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV) out += "ExplicitPreprocessBitNV | ";
    if (flag & VkIndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV) out += "IndexedSequencesBitNV | ";
    if (flag & VkIndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV) out += "UnorderedSequencesBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkIndirectStateFlagBitsNV val) {
    switch(val) {
        case(VkIndirectStateFlagBitsNV::FlagFrontfaceBitNV): return "FlagFrontfaceBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkIndirectStateFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkIndirectStateFlagBitsNV::FlagFrontfaceBitNV) out += "FlagFrontfaceBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPrivateDataSlotCreateFlagBitsEXT val) { UNUSED_VARIABLE(val); return "UNKNOWN"; }
inline std::string to_string(VkPrivateDataSlotCreateFlagsEXT flag){ UNUSED_VARIABLE(flag); return "UNKNOWN"; }
const char * to_string(VkDescriptorSetLayoutCreateFlagBits val) {
    switch(val) {
        case(VkDescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR): return "PushDescriptorBitKHR";
        case(VkDescriptorSetLayoutCreateFlagBits::HostOnlyPoolBitVALVE): return "HostOnlyPoolBitVALVE";
        case(VkDescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool): return "UpdateAfterBindPool";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDescriptorSetLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR) out += "PushDescriptorBitKHR | ";
    if (flag & VkDescriptorSetLayoutCreateFlagBits::HostOnlyPoolBitVALVE) out += "HostOnlyPoolBitVALVE | ";
    if (flag & VkDescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool) out += "UpdateAfterBindPool | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalMemoryHandleTypeFlagBits val) {
    switch(val) {
        case(VkExternalMemoryHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(VkExternalMemoryHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(VkExternalMemoryHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(VkExternalMemoryHandleTypeFlagBits::D3D11Texture): return "D3D11Texture";
        case(VkExternalMemoryHandleTypeFlagBits::D3D11TextureKmt): return "D3D11TextureKmt";
        case(VkExternalMemoryHandleTypeFlagBits::D3D12Heap): return "D3D12Heap";
        case(VkExternalMemoryHandleTypeFlagBits::D3D12Resource): return "D3D12Resource";
        case(VkExternalMemoryHandleTypeFlagBits::DmaBufBitEXT): return "DmaBufBitEXT";
        case(VkExternalMemoryHandleTypeFlagBits::AndroidHardwareBufferBitANDROID): return "AndroidHardwareBufferBitANDROID";
        case(VkExternalMemoryHandleTypeFlagBits::HostAllocationBitEXT): return "HostAllocationBitEXT";
        case(VkExternalMemoryHandleTypeFlagBits::HostMappedForeignMemoryBitEXT): return "HostMappedForeignMemoryBitEXT";
        case(VkExternalMemoryHandleTypeFlagBits::ZirconVmoBitFUCHSIA): return "ZirconVmoBitFUCHSIA";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalMemoryHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalMemoryHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::D3D11Texture) out += "D3D11Texture | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::D3D11TextureKmt) out += "D3D11TextureKmt | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::D3D12Heap) out += "D3D12Heap | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::D3D12Resource) out += "D3D12Resource | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::DmaBufBitEXT) out += "DmaBufBitEXT | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::AndroidHardwareBufferBitANDROID) out += "AndroidHardwareBufferBitANDROID | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::HostAllocationBitEXT) out += "HostAllocationBitEXT | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::HostMappedForeignMemoryBitEXT) out += "HostMappedForeignMemoryBitEXT | ";
    if (flag & VkExternalMemoryHandleTypeFlagBits::ZirconVmoBitFUCHSIA) out += "ZirconVmoBitFUCHSIA | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalMemoryFeatureFlagBits val) {
    switch(val) {
        case(VkExternalMemoryFeatureFlagBits::DedicatedOnly): return "DedicatedOnly";
        case(VkExternalMemoryFeatureFlagBits::Exportable): return "Exportable";
        case(VkExternalMemoryFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalMemoryFeatureFlagBits::DedicatedOnly) out += "DedicatedOnly | ";
    if (flag & VkExternalMemoryFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & VkExternalMemoryFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalSemaphoreHandleTypeFlagBits val) {
    switch(val) {
        case(VkExternalSemaphoreHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(VkExternalSemaphoreHandleTypeFlagBits::D3D12Fence): return "D3D12Fence";
        case(VkExternalSemaphoreHandleTypeFlagBits::SyncFd): return "SyncFd";
        case(VkExternalSemaphoreHandleTypeFlagBits::ZirconEventBitFUCHSIA): return "ZirconEventBitFUCHSIA";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalSemaphoreHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::D3D12Fence) out += "D3D12Fence | ";
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    if (flag & VkExternalSemaphoreHandleTypeFlagBits::ZirconEventBitFUCHSIA) out += "ZirconEventBitFUCHSIA | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalSemaphoreFeatureFlagBits val) {
    switch(val) {
        case(VkExternalSemaphoreFeatureFlagBits::Exportable): return "Exportable";
        case(VkExternalSemaphoreFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalSemaphoreFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalSemaphoreFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & VkExternalSemaphoreFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSemaphoreImportFlagBits val) {
    switch(val) {
        case(VkSemaphoreImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSemaphoreImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSemaphoreImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalFenceHandleTypeFlagBits val) {
    switch(val) {
        case(VkExternalFenceHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(VkExternalFenceHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(VkExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(VkExternalFenceHandleTypeFlagBits::SyncFd): return "SyncFd";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalFenceHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalFenceHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & VkExternalFenceHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & VkExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & VkExternalFenceHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkExternalFenceFeatureFlagBits val) {
    switch(val) {
        case(VkExternalFenceFeatureFlagBits::Exportable): return "Exportable";
        case(VkExternalFenceFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkExternalFenceFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkExternalFenceFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & VkExternalFenceFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkFenceImportFlagBits val) {
    switch(val) {
        case(VkFenceImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkFenceImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkFenceImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSurfaceCounterFlagBitsEXT val) {
    switch(val) {
        case(VkSurfaceCounterFlagBitsEXT::VblankBitEXT): return "VblankBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSurfaceCounterFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSurfaceCounterFlagBitsEXT::VblankBitEXT) out += "VblankBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPeerMemoryFeatureFlagBits val) {
    switch(val) {
        case(VkPeerMemoryFeatureFlagBits::CopySrc): return "CopySrc";
        case(VkPeerMemoryFeatureFlagBits::CopyDst): return "CopyDst";
        case(VkPeerMemoryFeatureFlagBits::GenericSrc): return "GenericSrc";
        case(VkPeerMemoryFeatureFlagBits::GenericDst): return "GenericDst";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPeerMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPeerMemoryFeatureFlagBits::CopySrc) out += "CopySrc | ";
    if (flag & VkPeerMemoryFeatureFlagBits::CopyDst) out += "CopyDst | ";
    if (flag & VkPeerMemoryFeatureFlagBits::GenericSrc) out += "GenericSrc | ";
    if (flag & VkPeerMemoryFeatureFlagBits::GenericDst) out += "GenericDst | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkMemoryAllocateFlagBits val) {
    switch(val) {
        case(VkMemoryAllocateFlagBits::DeviceMask): return "DeviceMask";
        case(VkMemoryAllocateFlagBits::DeviceAddress): return "DeviceAddress";
        case(VkMemoryAllocateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkMemoryAllocateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkMemoryAllocateFlagBits::DeviceMask) out += "DeviceMask | ";
    if (flag & VkMemoryAllocateFlagBits::DeviceAddress) out += "DeviceAddress | ";
    if (flag & VkMemoryAllocateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDeviceGroupPresentModeFlagBitsKHR val) {
    switch(val) {
        case(VkDeviceGroupPresentModeFlagBitsKHR::LocalBitKHR): return "LocalBitKHR";
        case(VkDeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR): return "RemoteBitKHR";
        case(VkDeviceGroupPresentModeFlagBitsKHR::SumBitKHR): return "SumBitKHR";
        case(VkDeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR): return "LocalMultiDeviceBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDeviceGroupPresentModeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDeviceGroupPresentModeFlagBitsKHR::LocalBitKHR) out += "LocalBitKHR | ";
    if (flag & VkDeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR) out += "RemoteBitKHR | ";
    if (flag & VkDeviceGroupPresentModeFlagBitsKHR::SumBitKHR) out += "SumBitKHR | ";
    if (flag & VkDeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR) out += "LocalMultiDeviceBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSwapchainCreateFlagBitsKHR val) {
    switch(val) {
        case(VkSwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR): return "SplitInstanceBindRegionsBitKHR";
        case(VkSwapchainCreateFlagBitsKHR::ProtectedBitKHR): return "ProtectedBitKHR";
        case(VkSwapchainCreateFlagBitsKHR::MutableFormatBitKHR): return "MutableFormatBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSwapchainCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR) out += "SplitInstanceBindRegionsBitKHR | ";
    if (flag & VkSwapchainCreateFlagBitsKHR::ProtectedBitKHR) out += "ProtectedBitKHR | ";
    if (flag & VkSwapchainCreateFlagBitsKHR::MutableFormatBitKHR) out += "MutableFormatBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSubpassDescriptionFlagBits val) {
    switch(val) {
        case(VkSubpassDescriptionFlagBits::PerViewAttributesBitNVX): return "PerViewAttributesBitNVX";
        case(VkSubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX): return "PerViewPositionXOnlyBitNVX";
        case(VkSubpassDescriptionFlagBits::FragmentRegionBitQCOM): return "FragmentRegionBitQCOM";
        case(VkSubpassDescriptionFlagBits::ShaderResolveBitQCOM): return "ShaderResolveBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSubpassDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSubpassDescriptionFlagBits::PerViewAttributesBitNVX) out += "PerViewAttributesBitNVX | ";
    if (flag & VkSubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX) out += "PerViewPositionXOnlyBitNVX | ";
    if (flag & VkSubpassDescriptionFlagBits::FragmentRegionBitQCOM) out += "FragmentRegionBitQCOM | ";
    if (flag & VkSubpassDescriptionFlagBits::ShaderResolveBitQCOM) out += "ShaderResolveBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDebugUtilsMessageSeverityFlagBitsEXT val) {
    switch(val) {
        case(VkDebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT): return "VerboseBitEXT";
        case(VkDebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT): return "InfoBitEXT";
        case(VkDebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(VkDebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDebugUtilsMessageSeverityFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT) out += "VerboseBitEXT | ";
    if (flag & VkDebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT) out += "InfoBitEXT | ";
    if (flag & VkDebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & VkDebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDebugUtilsMessageTypeFlagBitsEXT val) {
    switch(val) {
        case(VkDebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT): return "GeneralBitEXT";
        case(VkDebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT): return "ValidationBitEXT";
        case(VkDebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT): return "PerformanceBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDebugUtilsMessageTypeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT) out += "GeneralBitEXT | ";
    if (flag & VkDebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT) out += "ValidationBitEXT | ";
    if (flag & VkDebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT) out += "PerformanceBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDescriptorBindingFlagBits val) {
    switch(val) {
        case(VkDescriptorBindingFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        case(VkDescriptorBindingFlagBits::UpdateUnusedWhilePending): return "UpdateUnusedWhilePending";
        case(VkDescriptorBindingFlagBits::PartiallyBound): return "PartiallyBound";
        case(VkDescriptorBindingFlagBits::VariableDescriptorCount): return "VariableDescriptorCount";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDescriptorBindingFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDescriptorBindingFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    if (flag & VkDescriptorBindingFlagBits::UpdateUnusedWhilePending) out += "UpdateUnusedWhilePending | ";
    if (flag & VkDescriptorBindingFlagBits::PartiallyBound) out += "PartiallyBound | ";
    if (flag & VkDescriptorBindingFlagBits::VariableDescriptorCount) out += "VariableDescriptorCount | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkConditionalRenderingFlagBitsEXT val) {
    switch(val) {
        case(VkConditionalRenderingFlagBitsEXT::InvertedBitEXT): return "InvertedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkConditionalRenderingFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkConditionalRenderingFlagBitsEXT::InvertedBitEXT) out += "InvertedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkResolveModeFlagBits val) {
    switch(val) {
        case(VkResolveModeFlagBits::None): return "None";
        case(VkResolveModeFlagBits::SampleZero): return "SampleZero";
        case(VkResolveModeFlagBits::Average): return "Average";
        case(VkResolveModeFlagBits::Min): return "Min";
        case(VkResolveModeFlagBits::Max): return "Max";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkResolveModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkResolveModeFlagBits::None) out += "None | ";
    if (flag & VkResolveModeFlagBits::SampleZero) out += "SampleZero | ";
    if (flag & VkResolveModeFlagBits::Average) out += "Average | ";
    if (flag & VkResolveModeFlagBits::Min) out += "Min | ";
    if (flag & VkResolveModeFlagBits::Max) out += "Max | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkGeometryInstanceFlagBitsKHR val) {
    switch(val) {
        case(VkGeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR): return "TriangleFacingCullDisableBitKHR";
        case(VkGeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR): return "TriangleFrontCounterclockwiseBitKHR";
        case(VkGeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR): return "ForceOpaqueBitKHR";
        case(VkGeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR): return "ForceNoOpaqueBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkGeometryInstanceFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkGeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR) out += "TriangleFacingCullDisableBitKHR | ";
    if (flag & VkGeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR) out += "TriangleFrontCounterclockwiseBitKHR | ";
    if (flag & VkGeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR) out += "ForceOpaqueBitKHR | ";
    if (flag & VkGeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR) out += "ForceNoOpaqueBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkGeometryFlagBitsKHR val) {
    switch(val) {
        case(VkGeometryFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(VkGeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR): return "NoDuplicateAnyHitInvocationBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkGeometryFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkGeometryFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & VkGeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR) out += "NoDuplicateAnyHitInvocationBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkBuildAccelerationStructureFlagBitsKHR val) {
    switch(val) {
        case(VkBuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR): return "AllowUpdateBitKHR";
        case(VkBuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR): return "AllowCompactionBitKHR";
        case(VkBuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR): return "PreferFastTraceBitKHR";
        case(VkBuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR): return "PreferFastBuildBitKHR";
        case(VkBuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR): return "LowMemoryBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkBuildAccelerationStructureFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkBuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR) out += "AllowUpdateBitKHR | ";
    if (flag & VkBuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR) out += "AllowCompactionBitKHR | ";
    if (flag & VkBuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR) out += "PreferFastTraceBitKHR | ";
    if (flag & VkBuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR) out += "PreferFastBuildBitKHR | ";
    if (flag & VkBuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR) out += "LowMemoryBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkAccelerationStructureCreateFlagBitsKHR val) {
    switch(val) {
        case(VkAccelerationStructureCreateFlagBitsKHR::DeviceAddressCaptureReplayBitKHR): return "DeviceAddressCaptureReplayBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkAccelerationStructureCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkAccelerationStructureCreateFlagBitsKHR::DeviceAddressCaptureReplayBitKHR) out += "DeviceAddressCaptureReplayBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkFramebufferCreateFlagBits val) {
    switch(val) {
        case(VkFramebufferCreateFlagBits::Imageless): return "Imageless";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkFramebufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkFramebufferCreateFlagBits::Imageless) out += "Imageless | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkDeviceDiagnosticsConfigFlagBitsNV val) {
    switch(val) {
        case(VkDeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV): return "EnableShaderDebugInfoBitNV";
        case(VkDeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV): return "EnableResourceTrackingBitNV";
        case(VkDeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV): return "EnableAutomaticCheckpointsBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkDeviceDiagnosticsConfigFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkDeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV) out += "EnableShaderDebugInfoBitNV | ";
    if (flag & VkDeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV) out += "EnableResourceTrackingBitNV | ";
    if (flag & VkDeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV) out += "EnableAutomaticCheckpointsBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPipelineCreationFeedbackFlagBitsEXT val) {
    switch(val) {
        case(VkPipelineCreationFeedbackFlagBitsEXT::ValidBitEXT): return "ValidBitEXT";
        case(VkPipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT): return "ApplicationPipelineCacheHitBitEXT";
        case(VkPipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT): return "BasePipelineAccelerationBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineCreationFeedbackFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineCreationFeedbackFlagBitsEXT::ValidBitEXT) out += "ValidBitEXT | ";
    if (flag & VkPipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT) out += "ApplicationPipelineCacheHitBitEXT | ";
    if (flag & VkPipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT) out += "BasePipelineAccelerationBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPerformanceCounterDescriptionFlagBitsKHR val) {
    switch(val) {
        case(VkPerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingBitKHR): return "PerformanceImpactingBitKHR";
        case(VkPerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedBitKHR): return "ConcurrentlyImpactedBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPerformanceCounterDescriptionFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingBitKHR) out += "PerformanceImpactingBitKHR | ";
    if (flag & VkPerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedBitKHR) out += "ConcurrentlyImpactedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkAcquireProfilingLockFlagBitsKHR val) { UNUSED_VARIABLE(val); return "UNKNOWN"; }
inline std::string to_string(VkAcquireProfilingLockFlagsKHR flag){ UNUSED_VARIABLE(flag); return "UNKNOWN"; }
const char * to_string(VkShaderCorePropertiesFlagBitsAMD val) { UNUSED_VARIABLE(val); return "UNKNOWN"; }
inline std::string to_string(VkShaderCorePropertiesFlagsAMD flag){ UNUSED_VARIABLE(flag); return "UNKNOWN"; }
const char * to_string(VkShaderModuleCreateFlagBits val) { UNUSED_VARIABLE(val); return "UNKNOWN"; }
inline std::string to_string(VkShaderModuleCreateFlags flag){ UNUSED_VARIABLE(flag); return "UNKNOWN"; }
const char * to_string(VkPipelineCompilerControlFlagBitsAMD val) { UNUSED_VARIABLE(val); return "UNKNOWN"; }
inline std::string to_string(VkPipelineCompilerControlFlagsAMD flag){ UNUSED_VARIABLE(flag); return "UNKNOWN"; }
const char * to_string(VkToolPurposeFlagBitsEXT val) {
    switch(val) {
        case(VkToolPurposeFlagBitsEXT::ValidationBitEXT): return "ValidationBitEXT";
        case(VkToolPurposeFlagBitsEXT::ProfilingBitEXT): return "ProfilingBitEXT";
        case(VkToolPurposeFlagBitsEXT::TracingBitEXT): return "TracingBitEXT";
        case(VkToolPurposeFlagBitsEXT::AdditionalFeaturesBitEXT): return "AdditionalFeaturesBitEXT";
        case(VkToolPurposeFlagBitsEXT::ModifyingFeaturesBitEXT): return "ModifyingFeaturesBitEXT";
        case(VkToolPurposeFlagBitsEXT::DebugReportingBitEXT): return "DebugReportingBitEXT";
        case(VkToolPurposeFlagBitsEXT::DebugMarkersBitEXT): return "DebugMarkersBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkToolPurposeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkToolPurposeFlagBitsEXT::ValidationBitEXT) out += "ValidationBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::ProfilingBitEXT) out += "ProfilingBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::TracingBitEXT) out += "TracingBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::AdditionalFeaturesBitEXT) out += "AdditionalFeaturesBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::ModifyingFeaturesBitEXT) out += "ModifyingFeaturesBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::DebugReportingBitEXT) out += "DebugReportingBitEXT | ";
    if (flag & VkToolPurposeFlagBitsEXT::DebugMarkersBitEXT) out += "DebugMarkersBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkAccessFlagBits2KHR val) {
    switch(val) {
        case(VkAccessFlagBits2KHR::e2NoneKHR): return "e2NoneKHR";
        case(VkAccessFlagBits2KHR::e2IndirectCommandReadBitKHR): return "e2IndirectCommandReadBitKHR";
        case(VkAccessFlagBits2KHR::e2IndexReadBitKHR): return "e2IndexReadBitKHR";
        case(VkAccessFlagBits2KHR::e2VertexAttributeReadBitKHR): return "e2VertexAttributeReadBitKHR";
        case(VkAccessFlagBits2KHR::e2UniformReadBitKHR): return "e2UniformReadBitKHR";
        case(VkAccessFlagBits2KHR::e2InputAttachmentReadBitKHR): return "e2InputAttachmentReadBitKHR";
        case(VkAccessFlagBits2KHR::e2ShaderReadBitKHR): return "e2ShaderReadBitKHR";
        case(VkAccessFlagBits2KHR::e2ShaderWriteBitKHR): return "e2ShaderWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2ColorAttachmentReadBitKHR): return "e2ColorAttachmentReadBitKHR";
        case(VkAccessFlagBits2KHR::e2ColorAttachmentWriteBitKHR): return "e2ColorAttachmentWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2DepthStencilAttachmentReadBitKHR): return "e2DepthStencilAttachmentReadBitKHR";
        case(VkAccessFlagBits2KHR::e2DepthStencilAttachmentWriteBitKHR): return "e2DepthStencilAttachmentWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2TransferReadBitKHR): return "e2TransferReadBitKHR";
        case(VkAccessFlagBits2KHR::e2TransferWriteBitKHR): return "e2TransferWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2HostReadBitKHR): return "e2HostReadBitKHR";
        case(VkAccessFlagBits2KHR::e2HostWriteBitKHR): return "e2HostWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2MemoryReadBitKHR): return "e2MemoryReadBitKHR";
        case(VkAccessFlagBits2KHR::e2MemoryWriteBitKHR): return "e2MemoryWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2ShaderSampledReadBitKHR): return "e2ShaderSampledReadBitKHR";
        case(VkAccessFlagBits2KHR::e2ShaderStorageReadBitKHR): return "e2ShaderStorageReadBitKHR";
        case(VkAccessFlagBits2KHR::e2ShaderStorageWriteBitKHR): return "e2ShaderStorageWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2VideoDecodeReadBitKHR): return "e2VideoDecodeReadBitKHR";
        case(VkAccessFlagBits2KHR::e2VideoDecodeWriteBitKHR): return "e2VideoDecodeWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2VideoEncodeReadBitKHR): return "e2VideoEncodeReadBitKHR";
        case(VkAccessFlagBits2KHR::e2VideoEncodeWriteBitKHR): return "e2VideoEncodeWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2TransformFeedbackWriteBitEXT): return "e2TransformFeedbackWriteBitEXT";
        case(VkAccessFlagBits2KHR::e2TransformFeedbackCounterReadBitEXT): return "e2TransformFeedbackCounterReadBitEXT";
        case(VkAccessFlagBits2KHR::e2TransformFeedbackCounterWriteBitEXT): return "e2TransformFeedbackCounterWriteBitEXT";
        case(VkAccessFlagBits2KHR::e2ConditionalRenderingReadBitEXT): return "e2ConditionalRenderingReadBitEXT";
        case(VkAccessFlagBits2KHR::e2CommandPreprocessReadBitNV): return "e2CommandPreprocessReadBitNV";
        case(VkAccessFlagBits2KHR::e2CommandPreprocessWriteBitNV): return "e2CommandPreprocessWriteBitNV";
        case(VkAccessFlagBits2KHR::e2FragmentShadingRateAttachmentReadBitKHR): return "e2FragmentShadingRateAttachmentReadBitKHR";
        case(VkAccessFlagBits2KHR::e2AccelerationStructureReadBitKHR): return "e2AccelerationStructureReadBitKHR";
        case(VkAccessFlagBits2KHR::e2AccelerationStructureWriteBitKHR): return "e2AccelerationStructureWriteBitKHR";
        case(VkAccessFlagBits2KHR::e2FragmentDensityMapReadBitEXT): return "e2FragmentDensityMapReadBitEXT";
        case(VkAccessFlagBits2KHR::e2ColorAttachmentReadNoncoherentBitEXT): return "e2ColorAttachmentReadNoncoherentBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkAccessFlags2KHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkAccessFlagBits2KHR::e2NoneKHR) out += "e2NoneKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2IndirectCommandReadBitKHR) out += "e2IndirectCommandReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2IndexReadBitKHR) out += "e2IndexReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2VertexAttributeReadBitKHR) out += "e2VertexAttributeReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2UniformReadBitKHR) out += "e2UniformReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2InputAttachmentReadBitKHR) out += "e2InputAttachmentReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ShaderReadBitKHR) out += "e2ShaderReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ShaderWriteBitKHR) out += "e2ShaderWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ColorAttachmentReadBitKHR) out += "e2ColorAttachmentReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ColorAttachmentWriteBitKHR) out += "e2ColorAttachmentWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2DepthStencilAttachmentReadBitKHR) out += "e2DepthStencilAttachmentReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2DepthStencilAttachmentWriteBitKHR) out += "e2DepthStencilAttachmentWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2TransferReadBitKHR) out += "e2TransferReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2TransferWriteBitKHR) out += "e2TransferWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2HostReadBitKHR) out += "e2HostReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2HostWriteBitKHR) out += "e2HostWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2MemoryReadBitKHR) out += "e2MemoryReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2MemoryWriteBitKHR) out += "e2MemoryWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ShaderSampledReadBitKHR) out += "e2ShaderSampledReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ShaderStorageReadBitKHR) out += "e2ShaderStorageReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2ShaderStorageWriteBitKHR) out += "e2ShaderStorageWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2VideoDecodeReadBitKHR) out += "e2VideoDecodeReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2VideoDecodeWriteBitKHR) out += "e2VideoDecodeWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2VideoEncodeReadBitKHR) out += "e2VideoEncodeReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2VideoEncodeWriteBitKHR) out += "e2VideoEncodeWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2TransformFeedbackWriteBitEXT) out += "e2TransformFeedbackWriteBitEXT | ";
    if (flag & VkAccessFlagBits2KHR::e2TransformFeedbackCounterReadBitEXT) out += "e2TransformFeedbackCounterReadBitEXT | ";
    if (flag & VkAccessFlagBits2KHR::e2TransformFeedbackCounterWriteBitEXT) out += "e2TransformFeedbackCounterWriteBitEXT | ";
    if (flag & VkAccessFlagBits2KHR::e2ConditionalRenderingReadBitEXT) out += "e2ConditionalRenderingReadBitEXT | ";
    if (flag & VkAccessFlagBits2KHR::e2CommandPreprocessReadBitNV) out += "e2CommandPreprocessReadBitNV | ";
    if (flag & VkAccessFlagBits2KHR::e2CommandPreprocessWriteBitNV) out += "e2CommandPreprocessWriteBitNV | ";
    if (flag & VkAccessFlagBits2KHR::e2FragmentShadingRateAttachmentReadBitKHR) out += "e2FragmentShadingRateAttachmentReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2AccelerationStructureReadBitKHR) out += "e2AccelerationStructureReadBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2AccelerationStructureWriteBitKHR) out += "e2AccelerationStructureWriteBitKHR | ";
    if (flag & VkAccessFlagBits2KHR::e2FragmentDensityMapReadBitEXT) out += "e2FragmentDensityMapReadBitEXT | ";
    if (flag & VkAccessFlagBits2KHR::e2ColorAttachmentReadNoncoherentBitEXT) out += "e2ColorAttachmentReadNoncoherentBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkPipelineStageFlagBits2KHR val) {
    switch(val) {
        case(VkPipelineStageFlagBits2KHR::e2NoneKHR): return "e2NoneKHR";
        case(VkPipelineStageFlagBits2KHR::e2TopOfPipeBitKHR): return "e2TopOfPipeBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2DrawIndirectBitKHR): return "e2DrawIndirectBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2VertexInputBitKHR): return "e2VertexInputBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2VertexShaderBitKHR): return "e2VertexShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2TessellationControlShaderBitKHR): return "e2TessellationControlShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2TessellationEvaluationShaderBitKHR): return "e2TessellationEvaluationShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2GeometryShaderBitKHR): return "e2GeometryShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2FragmentShaderBitKHR): return "e2FragmentShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2EarlyFragmentTestsBitKHR): return "e2EarlyFragmentTestsBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2LateFragmentTestsBitKHR): return "e2LateFragmentTestsBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2ColorAttachmentOutputBitKHR): return "e2ColorAttachmentOutputBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2ComputeShaderBitKHR): return "e2ComputeShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2AllTransferBitKHR): return "e2AllTransferBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2BottomOfPipeBitKHR): return "e2BottomOfPipeBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2HostBitKHR): return "e2HostBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2AllGraphicsBitKHR): return "e2AllGraphicsBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2AllCommandsBitKHR): return "e2AllCommandsBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2CopyBitKHR): return "e2CopyBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2ResolveBitKHR): return "e2ResolveBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2BlitBitKHR): return "e2BlitBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2ClearBitKHR): return "e2ClearBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2IndexInputBitKHR): return "e2IndexInputBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2VertexAttributeInputBitKHR): return "e2VertexAttributeInputBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2PreRasterizationShadersBitKHR): return "e2PreRasterizationShadersBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2VideoDecodeBitKHR): return "e2VideoDecodeBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2VideoEncodeBitKHR): return "e2VideoEncodeBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2TransformFeedbackBitEXT): return "e2TransformFeedbackBitEXT";
        case(VkPipelineStageFlagBits2KHR::e2ConditionalRenderingBitEXT): return "e2ConditionalRenderingBitEXT";
        case(VkPipelineStageFlagBits2KHR::e2CommandPreprocessBitNV): return "e2CommandPreprocessBitNV";
        case(VkPipelineStageFlagBits2KHR::e2FragmentShadingRateAttachmentBitKHR): return "e2FragmentShadingRateAttachmentBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2AccelerationStructureBuildBitKHR): return "e2AccelerationStructureBuildBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2RayTracingShaderBitKHR): return "e2RayTracingShaderBitKHR";
        case(VkPipelineStageFlagBits2KHR::e2FragmentDensityProcessBitEXT): return "e2FragmentDensityProcessBitEXT";
        case(VkPipelineStageFlagBits2KHR::e2TaskShaderBitNV): return "e2TaskShaderBitNV";
        case(VkPipelineStageFlagBits2KHR::e2MeshShaderBitNV): return "e2MeshShaderBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkPipelineStageFlags2KHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkPipelineStageFlagBits2KHR::e2NoneKHR) out += "e2NoneKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2TopOfPipeBitKHR) out += "e2TopOfPipeBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2DrawIndirectBitKHR) out += "e2DrawIndirectBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2VertexInputBitKHR) out += "e2VertexInputBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2VertexShaderBitKHR) out += "e2VertexShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2TessellationControlShaderBitKHR) out += "e2TessellationControlShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2TessellationEvaluationShaderBitKHR) out += "e2TessellationEvaluationShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2GeometryShaderBitKHR) out += "e2GeometryShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2FragmentShaderBitKHR) out += "e2FragmentShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2EarlyFragmentTestsBitKHR) out += "e2EarlyFragmentTestsBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2LateFragmentTestsBitKHR) out += "e2LateFragmentTestsBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2ColorAttachmentOutputBitKHR) out += "e2ColorAttachmentOutputBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2ComputeShaderBitKHR) out += "e2ComputeShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2AllTransferBitKHR) out += "e2AllTransferBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2BottomOfPipeBitKHR) out += "e2BottomOfPipeBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2HostBitKHR) out += "e2HostBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2AllGraphicsBitKHR) out += "e2AllGraphicsBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2AllCommandsBitKHR) out += "e2AllCommandsBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2CopyBitKHR) out += "e2CopyBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2ResolveBitKHR) out += "e2ResolveBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2BlitBitKHR) out += "e2BlitBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2ClearBitKHR) out += "e2ClearBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2IndexInputBitKHR) out += "e2IndexInputBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2VertexAttributeInputBitKHR) out += "e2VertexAttributeInputBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2PreRasterizationShadersBitKHR) out += "e2PreRasterizationShadersBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2VideoDecodeBitKHR) out += "e2VideoDecodeBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2VideoEncodeBitKHR) out += "e2VideoEncodeBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2TransformFeedbackBitEXT) out += "e2TransformFeedbackBitEXT | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2ConditionalRenderingBitEXT) out += "e2ConditionalRenderingBitEXT | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2CommandPreprocessBitNV) out += "e2CommandPreprocessBitNV | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2FragmentShadingRateAttachmentBitKHR) out += "e2FragmentShadingRateAttachmentBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2AccelerationStructureBuildBitKHR) out += "e2AccelerationStructureBuildBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2RayTracingShaderBitKHR) out += "e2RayTracingShaderBitKHR | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2FragmentDensityProcessBitEXT) out += "e2FragmentDensityProcessBitEXT | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2TaskShaderBitNV) out += "e2TaskShaderBitNV | ";
    if (flag & VkPipelineStageFlagBits2KHR::e2MeshShaderBitNV) out += "e2MeshShaderBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkSubmitFlagBitsKHR val) {
    switch(val) {
        case(VkSubmitFlagBitsKHR::ProtectedBitKHR): return "ProtectedBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkSubmitFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkSubmitFlagBitsKHR::ProtectedBitKHR) out += "ProtectedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkEventCreateFlagBits val) {
    switch(val) {
        case(VkEventCreateFlagBits::DeviceOnlyBitKHR): return "DeviceOnlyBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkEventCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkEventCreateFlagBits::DeviceOnlyBitKHR) out += "DeviceOnlyBitKHR | ";
    return out.substr(0, out.size() - 3);
}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(VkVideoCodecOperationFlagBitsKHR val) {
    switch(val) {
        case(VkVideoCodecOperationFlagBitsKHR::InvalidBitKHR): return "InvalidBitKHR";
        case(VkVideoCodecOperationFlagBitsKHR::EncodeH264BitEXT): return "EncodeH264BitEXT";
        case(VkVideoCodecOperationFlagBitsKHR::DecodeH264BitEXT): return "DecodeH264BitEXT";
        case(VkVideoCodecOperationFlagBitsKHR::DecodeH265BitEXT): return "DecodeH265BitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoCodecOperationFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoCodecOperationFlagBitsKHR::InvalidBitKHR) out += "InvalidBitKHR | ";
    if (flag & VkVideoCodecOperationFlagBitsKHR::EncodeH264BitEXT) out += "EncodeH264BitEXT | ";
    if (flag & VkVideoCodecOperationFlagBitsKHR::DecodeH264BitEXT) out += "DecodeH264BitEXT | ";
    if (flag & VkVideoCodecOperationFlagBitsKHR::DecodeH265BitEXT) out += "DecodeH265BitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoChromaSubsamplingFlagBitsKHR val) {
    switch(val) {
        case(VkVideoChromaSubsamplingFlagBitsKHR::InvalidBitKHR): return "InvalidBitKHR";
        case(VkVideoChromaSubsamplingFlagBitsKHR::MonochromeBitKHR): return "MonochromeBitKHR";
        case(VkVideoChromaSubsamplingFlagBitsKHR::e420BitKHR): return "e420BitKHR";
        case(VkVideoChromaSubsamplingFlagBitsKHR::e422BitKHR): return "e422BitKHR";
        case(VkVideoChromaSubsamplingFlagBitsKHR::e444BitKHR): return "e444BitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoChromaSubsamplingFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoChromaSubsamplingFlagBitsKHR::InvalidBitKHR) out += "InvalidBitKHR | ";
    if (flag & VkVideoChromaSubsamplingFlagBitsKHR::MonochromeBitKHR) out += "MonochromeBitKHR | ";
    if (flag & VkVideoChromaSubsamplingFlagBitsKHR::e420BitKHR) out += "e420BitKHR | ";
    if (flag & VkVideoChromaSubsamplingFlagBitsKHR::e422BitKHR) out += "e422BitKHR | ";
    if (flag & VkVideoChromaSubsamplingFlagBitsKHR::e444BitKHR) out += "e444BitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoComponentBitDepthFlagBitsKHR val) {
    switch(val) {
        case(VkVideoComponentBitDepthFlagBitsKHR::InvalidKHR): return "InvalidKHR";
        case(VkVideoComponentBitDepthFlagBitsKHR::e8BitKHR): return "e8BitKHR";
        case(VkVideoComponentBitDepthFlagBitsKHR::e10BitKHR): return "e10BitKHR";
        case(VkVideoComponentBitDepthFlagBitsKHR::e12BitKHR): return "e12BitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoComponentBitDepthFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoComponentBitDepthFlagBitsKHR::InvalidKHR) out += "InvalidKHR | ";
    if (flag & VkVideoComponentBitDepthFlagBitsKHR::e8BitKHR) out += "e8BitKHR | ";
    if (flag & VkVideoComponentBitDepthFlagBitsKHR::e10BitKHR) out += "e10BitKHR | ";
    if (flag & VkVideoComponentBitDepthFlagBitsKHR::e12BitKHR) out += "e12BitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoCapabilitiesFlagBitsKHR val) {
    switch(val) {
        case(VkVideoCapabilitiesFlagBitsKHR::ProtectedContentBitKHR): return "ProtectedContentBitKHR";
        case(VkVideoCapabilitiesFlagBitsKHR::SeparateReferenceImagesBitKHR): return "SeparateReferenceImagesBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoCapabilitiesFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoCapabilitiesFlagBitsKHR::ProtectedContentBitKHR) out += "ProtectedContentBitKHR | ";
    if (flag & VkVideoCapabilitiesFlagBitsKHR::SeparateReferenceImagesBitKHR) out += "SeparateReferenceImagesBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoSessionCreateFlagBitsKHR val) {
    switch(val) {
        case(VkVideoSessionCreateFlagBitsKHR::DefaultKHR): return "DefaultKHR";
        case(VkVideoSessionCreateFlagBitsKHR::ProtectedContentBitKHR): return "ProtectedContentBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoSessionCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoSessionCreateFlagBitsKHR::DefaultKHR) out += "DefaultKHR | ";
    if (flag & VkVideoSessionCreateFlagBitsKHR::ProtectedContentBitKHR) out += "ProtectedContentBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoCodingQualityPresetFlagBitsKHR val) {
    switch(val) {
        case(VkVideoCodingQualityPresetFlagBitsKHR::DefaultBitKHR): return "DefaultBitKHR";
        case(VkVideoCodingQualityPresetFlagBitsKHR::NormalBitKHR): return "NormalBitKHR";
        case(VkVideoCodingQualityPresetFlagBitsKHR::PowerBitKHR): return "PowerBitKHR";
        case(VkVideoCodingQualityPresetFlagBitsKHR::QualityBitKHR): return "QualityBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoCodingQualityPresetFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoCodingQualityPresetFlagBitsKHR::DefaultBitKHR) out += "DefaultBitKHR | ";
    if (flag & VkVideoCodingQualityPresetFlagBitsKHR::NormalBitKHR) out += "NormalBitKHR | ";
    if (flag & VkVideoCodingQualityPresetFlagBitsKHR::PowerBitKHR) out += "PowerBitKHR | ";
    if (flag & VkVideoCodingQualityPresetFlagBitsKHR::QualityBitKHR) out += "QualityBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoDecodeH264FieldLayoutFlagBitsEXT val) {
    switch(val) {
        case(VkVideoDecodeH264FieldLayoutFlagBitsEXT::OnlyEXT): return "OnlyEXT";
        case(VkVideoDecodeH264FieldLayoutFlagBitsEXT::LineInterlacedPlaneBitEXT): return "LineInterlacedPlaneBitEXT";
        case(VkVideoDecodeH264FieldLayoutFlagBitsEXT::SeparateInterlacedPlaneBitEXT): return "SeparateInterlacedPlaneBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoDecodeH264FieldLayoutFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoDecodeH264FieldLayoutFlagBitsEXT::OnlyEXT) out += "OnlyEXT | ";
    if (flag & VkVideoDecodeH264FieldLayoutFlagBitsEXT::LineInterlacedPlaneBitEXT) out += "LineInterlacedPlaneBitEXT | ";
    if (flag & VkVideoDecodeH264FieldLayoutFlagBitsEXT::SeparateInterlacedPlaneBitEXT) out += "SeparateInterlacedPlaneBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoCodingControlFlagBitsKHR val) {
    switch(val) {
        case(VkVideoCodingControlFlagBitsKHR::DefaultKHR): return "DefaultKHR";
        case(VkVideoCodingControlFlagBitsKHR::ResetBitKHR): return "ResetBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoCodingControlFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoCodingControlFlagBitsKHR::DefaultKHR) out += "DefaultKHR | ";
    if (flag & VkVideoCodingControlFlagBitsKHR::ResetBitKHR) out += "ResetBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoDecodeFlagBitsKHR val) {
    switch(val) {
        case(VkVideoDecodeFlagBitsKHR::DefaultKHR): return "DefaultKHR";
        case(VkVideoDecodeFlagBitsKHR::Reserved0BitKHR): return "Reserved0BitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoDecodeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoDecodeFlagBitsKHR::DefaultKHR) out += "DefaultKHR | ";
    if (flag & VkVideoDecodeFlagBitsKHR::Reserved0BitKHR) out += "Reserved0BitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeFlagBitsKHR val) {
    switch(val) {
        case(VkVideoEncodeFlagBitsKHR::DefaultKHR): return "DefaultKHR";
        case(VkVideoEncodeFlagBitsKHR::Reserved0BitKHR): return "Reserved0BitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeFlagBitsKHR::DefaultKHR) out += "DefaultKHR | ";
    if (flag & VkVideoEncodeFlagBitsKHR::Reserved0BitKHR) out += "Reserved0BitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeRateControlFlagBitsKHR val) {
    switch(val) {
        case(VkVideoEncodeRateControlFlagBitsKHR::DefaultKHR): return "DefaultKHR";
        case(VkVideoEncodeRateControlFlagBitsKHR::ResetBitKHR): return "ResetBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeRateControlFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeRateControlFlagBitsKHR::DefaultKHR) out += "DefaultKHR | ";
    if (flag & VkVideoEncodeRateControlFlagBitsKHR::ResetBitKHR) out += "ResetBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeRateControlModeFlagBitsKHR val) {
    switch(val) {
        case(VkVideoEncodeRateControlModeFlagBitsKHR::NoneBitKHR): return "NoneBitKHR";
        case(VkVideoEncodeRateControlModeFlagBitsKHR::CbrBitKHR): return "CbrBitKHR";
        case(VkVideoEncodeRateControlModeFlagBitsKHR::VbrBitKHR): return "VbrBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeRateControlModeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeRateControlModeFlagBitsKHR::NoneBitKHR) out += "NoneBitKHR | ";
    if (flag & VkVideoEncodeRateControlModeFlagBitsKHR::CbrBitKHR) out += "CbrBitKHR | ";
    if (flag & VkVideoEncodeRateControlModeFlagBitsKHR::VbrBitKHR) out += "VbrBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeH264CapabilitiesFlagBitsEXT val) {
    switch(val) {
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::CabacBitEXT): return "CabacBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::CavlcBitEXT): return "CavlcBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::WeightedBiPredImplicitBitEXT): return "WeightedBiPredImplicitBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::Transform8X8BitEXT): return "Transform8X8BitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::ChromaQpOffsetBitEXT): return "ChromaQpOffsetBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::SecondChromaQpOffsetBitEXT): return "SecondChromaQpOffsetBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterDisabledBitEXT): return "DeblockingFilterDisabledBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterEnabledBitEXT): return "DeblockingFilterEnabledBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterPartialBitEXT): return "DeblockingFilterPartialBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::MultipleSlicePerFrameBitEXT): return "MultipleSlicePerFrameBitEXT";
        case(VkVideoEncodeH264CapabilitiesFlagBitsEXT::EvenlyDistributedSliceSizeBitEXT): return "EvenlyDistributedSliceSizeBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeH264CapabilitiesFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::CabacBitEXT) out += "CabacBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::CavlcBitEXT) out += "CavlcBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::WeightedBiPredImplicitBitEXT) out += "WeightedBiPredImplicitBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::Transform8X8BitEXT) out += "Transform8X8BitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::ChromaQpOffsetBitEXT) out += "ChromaQpOffsetBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::SecondChromaQpOffsetBitEXT) out += "SecondChromaQpOffsetBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterDisabledBitEXT) out += "DeblockingFilterDisabledBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterEnabledBitEXT) out += "DeblockingFilterEnabledBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterPartialBitEXT) out += "DeblockingFilterPartialBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::MultipleSlicePerFrameBitEXT) out += "MultipleSlicePerFrameBitEXT | ";
    if (flag & VkVideoEncodeH264CapabilitiesFlagBitsEXT::EvenlyDistributedSliceSizeBitEXT) out += "EvenlyDistributedSliceSizeBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeH264InputModeFlagBitsEXT val) {
    switch(val) {
        case(VkVideoEncodeH264InputModeFlagBitsEXT::FrameBitEXT): return "FrameBitEXT";
        case(VkVideoEncodeH264InputModeFlagBitsEXT::SliceBitEXT): return "SliceBitEXT";
        case(VkVideoEncodeH264InputModeFlagBitsEXT::NonVclBitEXT): return "NonVclBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeH264InputModeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeH264InputModeFlagBitsEXT::FrameBitEXT) out += "FrameBitEXT | ";
    if (flag & VkVideoEncodeH264InputModeFlagBitsEXT::SliceBitEXT) out += "SliceBitEXT | ";
    if (flag & VkVideoEncodeH264InputModeFlagBitsEXT::NonVclBitEXT) out += "NonVclBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeH264OutputModeFlagBitsEXT val) {
    switch(val) {
        case(VkVideoEncodeH264OutputModeFlagBitsEXT::FrameBitEXT): return "FrameBitEXT";
        case(VkVideoEncodeH264OutputModeFlagBitsEXT::SliceBitEXT): return "SliceBitEXT";
        case(VkVideoEncodeH264OutputModeFlagBitsEXT::NonVclBitEXT): return "NonVclBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeH264OutputModeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeH264OutputModeFlagBitsEXT::FrameBitEXT) out += "FrameBitEXT | ";
    if (flag & VkVideoEncodeH264OutputModeFlagBitsEXT::SliceBitEXT) out += "SliceBitEXT | ";
    if (flag & VkVideoEncodeH264OutputModeFlagBitsEXT::NonVclBitEXT) out += "NonVclBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(VkVideoEncodeH264CreateFlagBitsEXT val) {
    switch(val) {
        case(VkVideoEncodeH264CreateFlagBitsEXT::DefaultEXT): return "DefaultEXT";
        case(VkVideoEncodeH264CreateFlagBitsEXT::Reserved0BitEXT): return "Reserved0BitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(VkVideoEncodeH264CreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & VkVideoEncodeH264CreateFlagBitsEXT::DefaultEXT) out += "DefaultEXT | ";
    if (flag & VkVideoEncodeH264CreateFlagBitsEXT::Reserved0BitEXT) out += "Reserved0BitEXT | ";
    return out.substr(0, out.size() - 3);
}
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
