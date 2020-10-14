// clang-format off
#include "vkm_string.h"
namespace vk {
#if defined(WIN32)
#pragma warning( disable : 4065 )
#endif //defined(WIN32)
const char * to_string(AttachmentLoadOp val) {
    switch(val) {
        case(AttachmentLoadOp::Load): return "Load";
        case(AttachmentLoadOp::Clear): return "Clear";
        case(AttachmentLoadOp::DontCare): return "DontCare";
        default: return "UNKNOWN";
    }
}
const char * to_string(AttachmentStoreOp val) {
    switch(val) {
        case(AttachmentStoreOp::Store): return "Store";
        case(AttachmentStoreOp::DontCare): return "DontCare";
        case(AttachmentStoreOp::NoneQCOM): return "NoneQCOM";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendFactor val) {
    switch(val) {
        case(BlendFactor::Zero): return "Zero";
        case(BlendFactor::One): return "One";
        case(BlendFactor::SrcColor): return "SrcColor";
        case(BlendFactor::OneMinusSrcColor): return "OneMinusSrcColor";
        case(BlendFactor::DstColor): return "DstColor";
        case(BlendFactor::OneMinusDstColor): return "OneMinusDstColor";
        case(BlendFactor::SrcAlpha): return "SrcAlpha";
        case(BlendFactor::OneMinusSrcAlpha): return "OneMinusSrcAlpha";
        case(BlendFactor::DstAlpha): return "DstAlpha";
        case(BlendFactor::OneMinusDstAlpha): return "OneMinusDstAlpha";
        case(BlendFactor::ConstantColor): return "ConstantColor";
        case(BlendFactor::OneMinusConstantColor): return "OneMinusConstantColor";
        case(BlendFactor::ConstantAlpha): return "ConstantAlpha";
        case(BlendFactor::OneMinusConstantAlpha): return "OneMinusConstantAlpha";
        case(BlendFactor::SrcAlphaSaturate): return "SrcAlphaSaturate";
        case(BlendFactor::Src1Color): return "Src1Color";
        case(BlendFactor::OneMinusSrc1Color): return "OneMinusSrc1Color";
        case(BlendFactor::Src1Alpha): return "Src1Alpha";
        case(BlendFactor::OneMinusSrc1Alpha): return "OneMinusSrc1Alpha";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendOp val) {
    switch(val) {
        case(BlendOp::Add): return "Add";
        case(BlendOp::Subtract): return "Subtract";
        case(BlendOp::ReverseSubtract): return "ReverseSubtract";
        case(BlendOp::Min): return "Min";
        case(BlendOp::Max): return "Max";
        case(BlendOp::ZeroEXT): return "ZeroEXT";
        case(BlendOp::SrcEXT): return "SrcEXT";
        case(BlendOp::DstEXT): return "DstEXT";
        case(BlendOp::SrcOverEXT): return "SrcOverEXT";
        case(BlendOp::DstOverEXT): return "DstOverEXT";
        case(BlendOp::SrcInEXT): return "SrcInEXT";
        case(BlendOp::DstInEXT): return "DstInEXT";
        case(BlendOp::SrcOutEXT): return "SrcOutEXT";
        case(BlendOp::DstOutEXT): return "DstOutEXT";
        case(BlendOp::SrcAtopEXT): return "SrcAtopEXT";
        case(BlendOp::DstAtopEXT): return "DstAtopEXT";
        case(BlendOp::XorEXT): return "XorEXT";
        case(BlendOp::MultiplyEXT): return "MultiplyEXT";
        case(BlendOp::ScreenEXT): return "ScreenEXT";
        case(BlendOp::OverlayEXT): return "OverlayEXT";
        case(BlendOp::DarkenEXT): return "DarkenEXT";
        case(BlendOp::LightenEXT): return "LightenEXT";
        case(BlendOp::ColordodgeEXT): return "ColordodgeEXT";
        case(BlendOp::ColorburnEXT): return "ColorburnEXT";
        case(BlendOp::HardlightEXT): return "HardlightEXT";
        case(BlendOp::SoftlightEXT): return "SoftlightEXT";
        case(BlendOp::DifferenceEXT): return "DifferenceEXT";
        case(BlendOp::ExclusionEXT): return "ExclusionEXT";
        case(BlendOp::InvertEXT): return "InvertEXT";
        case(BlendOp::InvertRgbEXT): return "InvertRgbEXT";
        case(BlendOp::LineardodgeEXT): return "LineardodgeEXT";
        case(BlendOp::LinearburnEXT): return "LinearburnEXT";
        case(BlendOp::VividlightEXT): return "VividlightEXT";
        case(BlendOp::LinearlightEXT): return "LinearlightEXT";
        case(BlendOp::PinlightEXT): return "PinlightEXT";
        case(BlendOp::HardmixEXT): return "HardmixEXT";
        case(BlendOp::HslHueEXT): return "HslHueEXT";
        case(BlendOp::HslSaturationEXT): return "HslSaturationEXT";
        case(BlendOp::HslColorEXT): return "HslColorEXT";
        case(BlendOp::HslLuminosityEXT): return "HslLuminosityEXT";
        case(BlendOp::PlusEXT): return "PlusEXT";
        case(BlendOp::PlusClampedEXT): return "PlusClampedEXT";
        case(BlendOp::PlusClampedAlphaEXT): return "PlusClampedAlphaEXT";
        case(BlendOp::PlusDarkerEXT): return "PlusDarkerEXT";
        case(BlendOp::MinusEXT): return "MinusEXT";
        case(BlendOp::MinusClampedEXT): return "MinusClampedEXT";
        case(BlendOp::ContrastEXT): return "ContrastEXT";
        case(BlendOp::InvertOvgEXT): return "InvertOvgEXT";
        case(BlendOp::RedEXT): return "RedEXT";
        case(BlendOp::GreenEXT): return "GreenEXT";
        case(BlendOp::BlueEXT): return "BlueEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(BorderColor val) {
    switch(val) {
        case(BorderColor::FloatTransparentBlack): return "FloatTransparentBlack";
        case(BorderColor::IntTransparentBlack): return "IntTransparentBlack";
        case(BorderColor::FloatOpaqueBlack): return "FloatOpaqueBlack";
        case(BorderColor::IntOpaqueBlack): return "IntOpaqueBlack";
        case(BorderColor::FloatOpaqueWhite): return "FloatOpaqueWhite";
        case(BorderColor::IntOpaqueWhite): return "IntOpaqueWhite";
        case(BorderColor::FloatCustomEXT): return "FloatCustomEXT";
        case(BorderColor::IntCustomEXT): return "IntCustomEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineCacheHeaderVersion val) {
    switch(val) {
        case(PipelineCacheHeaderVersion::One): return "One";
        default: return "UNKNOWN";
    }
}
const char * to_string(ComponentSwizzle val) {
    switch(val) {
        case(ComponentSwizzle::Identity): return "Identity";
        case(ComponentSwizzle::Zero): return "Zero";
        case(ComponentSwizzle::One): return "One";
        case(ComponentSwizzle::R): return "R";
        case(ComponentSwizzle::G): return "G";
        case(ComponentSwizzle::B): return "B";
        case(ComponentSwizzle::A): return "A";
        default: return "UNKNOWN";
    }
}
const char * to_string(CommandBufferLevel val) {
    switch(val) {
        case(CommandBufferLevel::Primary): return "Primary";
        case(CommandBufferLevel::Secondary): return "Secondary";
        default: return "UNKNOWN";
    }
}
const char * to_string(CompareOp val) {
    switch(val) {
        case(CompareOp::Never): return "Never";
        case(CompareOp::Less): return "Less";
        case(CompareOp::Equal): return "Equal";
        case(CompareOp::LessOrEqual): return "LessOrEqual";
        case(CompareOp::Greater): return "Greater";
        case(CompareOp::NotEqual): return "NotEqual";
        case(CompareOp::GreaterOrEqual): return "GreaterOrEqual";
        case(CompareOp::Always): return "Always";
        default: return "UNKNOWN";
    }
}
const char * to_string(DescriptorType val) {
    switch(val) {
        case(DescriptorType::Sampler): return "Sampler";
        case(DescriptorType::CombinedImageSampler): return "CombinedImageSampler";
        case(DescriptorType::SampledImage): return "SampledImage";
        case(DescriptorType::StorageImage): return "StorageImage";
        case(DescriptorType::UniformTexelBuffer): return "UniformTexelBuffer";
        case(DescriptorType::StorageTexelBuffer): return "StorageTexelBuffer";
        case(DescriptorType::UniformBuffer): return "UniformBuffer";
        case(DescriptorType::StorageBuffer): return "StorageBuffer";
        case(DescriptorType::UniformBufferDynamic): return "UniformBufferDynamic";
        case(DescriptorType::StorageBufferDynamic): return "StorageBufferDynamic";
        case(DescriptorType::InputAttachment): return "InputAttachment";
        case(DescriptorType::InlineUniformBlockEXT): return "InlineUniformBlockEXT";
        case(DescriptorType::AccelerationStructureKHR): return "AccelerationStructureKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(DynamicState val) {
    switch(val) {
        case(DynamicState::Viewport): return "Viewport";
        case(DynamicState::Scissor): return "Scissor";
        case(DynamicState::LineWidth): return "LineWidth";
        case(DynamicState::DepthBias): return "DepthBias";
        case(DynamicState::BlendConstants): return "BlendConstants";
        case(DynamicState::DepthBounds): return "DepthBounds";
        case(DynamicState::StencilCompareMask): return "StencilCompareMask";
        case(DynamicState::StencilWriteMask): return "StencilWriteMask";
        case(DynamicState::StencilReference): return "StencilReference";
        case(DynamicState::ViewportWScalingNV): return "ViewportWScalingNV";
        case(DynamicState::DiscardRectangleEXT): return "DiscardRectangleEXT";
        case(DynamicState::SampleLocationsEXT): return "SampleLocationsEXT";
        case(DynamicState::ViewportShadingRatePaletteNV): return "ViewportShadingRatePaletteNV";
        case(DynamicState::ViewportCoarseSampleOrderNV): return "ViewportCoarseSampleOrderNV";
        case(DynamicState::ExclusiveScissorNV): return "ExclusiveScissorNV";
        case(DynamicState::LineStippleEXT): return "LineStippleEXT";
        case(DynamicState::CullModeEXT): return "CullModeEXT";
        case(DynamicState::FrontFaceEXT): return "FrontFaceEXT";
        case(DynamicState::PrimitiveTopologyEXT): return "PrimitiveTopologyEXT";
        case(DynamicState::ViewportWithCountEXT): return "ViewportWithCountEXT";
        case(DynamicState::ScissorWithCountEXT): return "ScissorWithCountEXT";
        case(DynamicState::VertexInputBindingStrideEXT): return "VertexInputBindingStrideEXT";
        case(DynamicState::DepthTestEnableEXT): return "DepthTestEnableEXT";
        case(DynamicState::DepthWriteEnableEXT): return "DepthWriteEnableEXT";
        case(DynamicState::DepthCompareOpEXT): return "DepthCompareOpEXT";
        case(DynamicState::DepthBoundsTestEnableEXT): return "DepthBoundsTestEnableEXT";
        case(DynamicState::StencilTestEnableEXT): return "StencilTestEnableEXT";
        case(DynamicState::StencilOpEXT): return "StencilOpEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PolygonMode val) {
    switch(val) {
        case(PolygonMode::Fill): return "Fill";
        case(PolygonMode::Line): return "Line";
        case(PolygonMode::Point): return "Point";
        case(PolygonMode::FillRectangleNV): return "FillRectangleNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(Format val) {
    switch(val) {
        case(Format::Undefined): return "Undefined";
        case(Format::R4G4UnormPack8): return "R4G4UnormPack8";
        case(Format::R4G4B4A4UnormPack16): return "R4G4B4A4UnormPack16";
        case(Format::B4G4R4A4UnormPack16): return "B4G4R4A4UnormPack16";
        case(Format::R5G6B5UnormPack16): return "R5G6B5UnormPack16";
        case(Format::B5G6R5UnormPack16): return "B5G6R5UnormPack16";
        case(Format::R5G5B5A1UnormPack16): return "R5G5B5A1UnormPack16";
        case(Format::B5G5R5A1UnormPack16): return "B5G5R5A1UnormPack16";
        case(Format::A1R5G5B5UnormPack16): return "A1R5G5B5UnormPack16";
        case(Format::R8Unorm): return "R8Unorm";
        case(Format::R8Snorm): return "R8Snorm";
        case(Format::R8Uscaled): return "R8Uscaled";
        case(Format::R8Sscaled): return "R8Sscaled";
        case(Format::R8Uint): return "R8Uint";
        case(Format::R8Sint): return "R8Sint";
        case(Format::R8Srgb): return "R8Srgb";
        case(Format::R8G8Unorm): return "R8G8Unorm";
        case(Format::R8G8Snorm): return "R8G8Snorm";
        case(Format::R8G8Uscaled): return "R8G8Uscaled";
        case(Format::R8G8Sscaled): return "R8G8Sscaled";
        case(Format::R8G8Uint): return "R8G8Uint";
        case(Format::R8G8Sint): return "R8G8Sint";
        case(Format::R8G8Srgb): return "R8G8Srgb";
        case(Format::R8G8B8Unorm): return "R8G8B8Unorm";
        case(Format::R8G8B8Snorm): return "R8G8B8Snorm";
        case(Format::R8G8B8Uscaled): return "R8G8B8Uscaled";
        case(Format::R8G8B8Sscaled): return "R8G8B8Sscaled";
        case(Format::R8G8B8Uint): return "R8G8B8Uint";
        case(Format::R8G8B8Sint): return "R8G8B8Sint";
        case(Format::R8G8B8Srgb): return "R8G8B8Srgb";
        case(Format::B8G8R8Unorm): return "B8G8R8Unorm";
        case(Format::B8G8R8Snorm): return "B8G8R8Snorm";
        case(Format::B8G8R8Uscaled): return "B8G8R8Uscaled";
        case(Format::B8G8R8Sscaled): return "B8G8R8Sscaled";
        case(Format::B8G8R8Uint): return "B8G8R8Uint";
        case(Format::B8G8R8Sint): return "B8G8R8Sint";
        case(Format::B8G8R8Srgb): return "B8G8R8Srgb";
        case(Format::R8G8B8A8Unorm): return "R8G8B8A8Unorm";
        case(Format::R8G8B8A8Snorm): return "R8G8B8A8Snorm";
        case(Format::R8G8B8A8Uscaled): return "R8G8B8A8Uscaled";
        case(Format::R8G8B8A8Sscaled): return "R8G8B8A8Sscaled";
        case(Format::R8G8B8A8Uint): return "R8G8B8A8Uint";
        case(Format::R8G8B8A8Sint): return "R8G8B8A8Sint";
        case(Format::R8G8B8A8Srgb): return "R8G8B8A8Srgb";
        case(Format::B8G8R8A8Unorm): return "B8G8R8A8Unorm";
        case(Format::B8G8R8A8Snorm): return "B8G8R8A8Snorm";
        case(Format::B8G8R8A8Uscaled): return "B8G8R8A8Uscaled";
        case(Format::B8G8R8A8Sscaled): return "B8G8R8A8Sscaled";
        case(Format::B8G8R8A8Uint): return "B8G8R8A8Uint";
        case(Format::B8G8R8A8Sint): return "B8G8R8A8Sint";
        case(Format::B8G8R8A8Srgb): return "B8G8R8A8Srgb";
        case(Format::A8B8G8R8UnormPack32): return "A8B8G8R8UnormPack32";
        case(Format::A8B8G8R8SnormPack32): return "A8B8G8R8SnormPack32";
        case(Format::A8B8G8R8UscaledPack32): return "A8B8G8R8UscaledPack32";
        case(Format::A8B8G8R8SscaledPack32): return "A8B8G8R8SscaledPack32";
        case(Format::A8B8G8R8UintPack32): return "A8B8G8R8UintPack32";
        case(Format::A8B8G8R8SintPack32): return "A8B8G8R8SintPack32";
        case(Format::A8B8G8R8SrgbPack32): return "A8B8G8R8SrgbPack32";
        case(Format::A2R10G10B10UnormPack32): return "A2R10G10B10UnormPack32";
        case(Format::A2R10G10B10SnormPack32): return "A2R10G10B10SnormPack32";
        case(Format::A2R10G10B10UscaledPack32): return "A2R10G10B10UscaledPack32";
        case(Format::A2R10G10B10SscaledPack32): return "A2R10G10B10SscaledPack32";
        case(Format::A2R10G10B10UintPack32): return "A2R10G10B10UintPack32";
        case(Format::A2R10G10B10SintPack32): return "A2R10G10B10SintPack32";
        case(Format::A2B10G10R10UnormPack32): return "A2B10G10R10UnormPack32";
        case(Format::A2B10G10R10SnormPack32): return "A2B10G10R10SnormPack32";
        case(Format::A2B10G10R10UscaledPack32): return "A2B10G10R10UscaledPack32";
        case(Format::A2B10G10R10SscaledPack32): return "A2B10G10R10SscaledPack32";
        case(Format::A2B10G10R10UintPack32): return "A2B10G10R10UintPack32";
        case(Format::A2B10G10R10SintPack32): return "A2B10G10R10SintPack32";
        case(Format::R16Unorm): return "R16Unorm";
        case(Format::R16Snorm): return "R16Snorm";
        case(Format::R16Uscaled): return "R16Uscaled";
        case(Format::R16Sscaled): return "R16Sscaled";
        case(Format::R16Uint): return "R16Uint";
        case(Format::R16Sint): return "R16Sint";
        case(Format::R16Sfloat): return "R16Sfloat";
        case(Format::R16G16Unorm): return "R16G16Unorm";
        case(Format::R16G16Snorm): return "R16G16Snorm";
        case(Format::R16G16Uscaled): return "R16G16Uscaled";
        case(Format::R16G16Sscaled): return "R16G16Sscaled";
        case(Format::R16G16Uint): return "R16G16Uint";
        case(Format::R16G16Sint): return "R16G16Sint";
        case(Format::R16G16Sfloat): return "R16G16Sfloat";
        case(Format::R16G16B16Unorm): return "R16G16B16Unorm";
        case(Format::R16G16B16Snorm): return "R16G16B16Snorm";
        case(Format::R16G16B16Uscaled): return "R16G16B16Uscaled";
        case(Format::R16G16B16Sscaled): return "R16G16B16Sscaled";
        case(Format::R16G16B16Uint): return "R16G16B16Uint";
        case(Format::R16G16B16Sint): return "R16G16B16Sint";
        case(Format::R16G16B16Sfloat): return "R16G16B16Sfloat";
        case(Format::R16G16B16A16Unorm): return "R16G16B16A16Unorm";
        case(Format::R16G16B16A16Snorm): return "R16G16B16A16Snorm";
        case(Format::R16G16B16A16Uscaled): return "R16G16B16A16Uscaled";
        case(Format::R16G16B16A16Sscaled): return "R16G16B16A16Sscaled";
        case(Format::R16G16B16A16Uint): return "R16G16B16A16Uint";
        case(Format::R16G16B16A16Sint): return "R16G16B16A16Sint";
        case(Format::R16G16B16A16Sfloat): return "R16G16B16A16Sfloat";
        case(Format::R32Uint): return "R32Uint";
        case(Format::R32Sint): return "R32Sint";
        case(Format::R32Sfloat): return "R32Sfloat";
        case(Format::R32G32Uint): return "R32G32Uint";
        case(Format::R32G32Sint): return "R32G32Sint";
        case(Format::R32G32Sfloat): return "R32G32Sfloat";
        case(Format::R32G32B32Uint): return "R32G32B32Uint";
        case(Format::R32G32B32Sint): return "R32G32B32Sint";
        case(Format::R32G32B32Sfloat): return "R32G32B32Sfloat";
        case(Format::R32G32B32A32Uint): return "R32G32B32A32Uint";
        case(Format::R32G32B32A32Sint): return "R32G32B32A32Sint";
        case(Format::R32G32B32A32Sfloat): return "R32G32B32A32Sfloat";
        case(Format::R64Uint): return "R64Uint";
        case(Format::R64Sint): return "R64Sint";
        case(Format::R64Sfloat): return "R64Sfloat";
        case(Format::R64G64Uint): return "R64G64Uint";
        case(Format::R64G64Sint): return "R64G64Sint";
        case(Format::R64G64Sfloat): return "R64G64Sfloat";
        case(Format::R64G64B64Uint): return "R64G64B64Uint";
        case(Format::R64G64B64Sint): return "R64G64B64Sint";
        case(Format::R64G64B64Sfloat): return "R64G64B64Sfloat";
        case(Format::R64G64B64A64Uint): return "R64G64B64A64Uint";
        case(Format::R64G64B64A64Sint): return "R64G64B64A64Sint";
        case(Format::R64G64B64A64Sfloat): return "R64G64B64A64Sfloat";
        case(Format::B10G11R11UfloatPack32): return "B10G11R11UfloatPack32";
        case(Format::E5B9G9R9UfloatPack32): return "E5B9G9R9UfloatPack32";
        case(Format::D16Unorm): return "D16Unorm";
        case(Format::X8D24UnormPack32): return "X8D24UnormPack32";
        case(Format::D32Sfloat): return "D32Sfloat";
        case(Format::S8Uint): return "S8Uint";
        case(Format::D16UnormS8Uint): return "D16UnormS8Uint";
        case(Format::D24UnormS8Uint): return "D24UnormS8Uint";
        case(Format::D32SfloatS8Uint): return "D32SfloatS8Uint";
        case(Format::Bc1RgbUnormBlock): return "Bc1RgbUnormBlock";
        case(Format::Bc1RgbSrgbBlock): return "Bc1RgbSrgbBlock";
        case(Format::Bc1RgbaUnormBlock): return "Bc1RgbaUnormBlock";
        case(Format::Bc1RgbaSrgbBlock): return "Bc1RgbaSrgbBlock";
        case(Format::Bc2UnormBlock): return "Bc2UnormBlock";
        case(Format::Bc2SrgbBlock): return "Bc2SrgbBlock";
        case(Format::Bc3UnormBlock): return "Bc3UnormBlock";
        case(Format::Bc3SrgbBlock): return "Bc3SrgbBlock";
        case(Format::Bc4UnormBlock): return "Bc4UnormBlock";
        case(Format::Bc4SnormBlock): return "Bc4SnormBlock";
        case(Format::Bc5UnormBlock): return "Bc5UnormBlock";
        case(Format::Bc5SnormBlock): return "Bc5SnormBlock";
        case(Format::Bc6HUfloatBlock): return "Bc6HUfloatBlock";
        case(Format::Bc6HSfloatBlock): return "Bc6HSfloatBlock";
        case(Format::Bc7UnormBlock): return "Bc7UnormBlock";
        case(Format::Bc7SrgbBlock): return "Bc7SrgbBlock";
        case(Format::Etc2R8G8B8UnormBlock): return "Etc2R8G8B8UnormBlock";
        case(Format::Etc2R8G8B8SrgbBlock): return "Etc2R8G8B8SrgbBlock";
        case(Format::Etc2R8G8B8A1UnormBlock): return "Etc2R8G8B8A1UnormBlock";
        case(Format::Etc2R8G8B8A1SrgbBlock): return "Etc2R8G8B8A1SrgbBlock";
        case(Format::Etc2R8G8B8A8UnormBlock): return "Etc2R8G8B8A8UnormBlock";
        case(Format::Etc2R8G8B8A8SrgbBlock): return "Etc2R8G8B8A8SrgbBlock";
        case(Format::EacR11UnormBlock): return "EacR11UnormBlock";
        case(Format::EacR11SnormBlock): return "EacR11SnormBlock";
        case(Format::EacR11G11UnormBlock): return "EacR11G11UnormBlock";
        case(Format::EacR11G11SnormBlock): return "EacR11G11SnormBlock";
        case(Format::Astc4X4UnormBlock): return "Astc4X4UnormBlock";
        case(Format::Astc4X4SrgbBlock): return "Astc4X4SrgbBlock";
        case(Format::Astc5X4UnormBlock): return "Astc5X4UnormBlock";
        case(Format::Astc5X4SrgbBlock): return "Astc5X4SrgbBlock";
        case(Format::Astc5X5UnormBlock): return "Astc5X5UnormBlock";
        case(Format::Astc5X5SrgbBlock): return "Astc5X5SrgbBlock";
        case(Format::Astc6X5UnormBlock): return "Astc6X5UnormBlock";
        case(Format::Astc6X5SrgbBlock): return "Astc6X5SrgbBlock";
        case(Format::Astc6X6UnormBlock): return "Astc6X6UnormBlock";
        case(Format::Astc6X6SrgbBlock): return "Astc6X6SrgbBlock";
        case(Format::Astc8X5UnormBlock): return "Astc8X5UnormBlock";
        case(Format::Astc8X5SrgbBlock): return "Astc8X5SrgbBlock";
        case(Format::Astc8X6UnormBlock): return "Astc8X6UnormBlock";
        case(Format::Astc8X6SrgbBlock): return "Astc8X6SrgbBlock";
        case(Format::Astc8X8UnormBlock): return "Astc8X8UnormBlock";
        case(Format::Astc8X8SrgbBlock): return "Astc8X8SrgbBlock";
        case(Format::Astc10X5UnormBlock): return "Astc10X5UnormBlock";
        case(Format::Astc10X5SrgbBlock): return "Astc10X5SrgbBlock";
        case(Format::Astc10X6UnormBlock): return "Astc10X6UnormBlock";
        case(Format::Astc10X6SrgbBlock): return "Astc10X6SrgbBlock";
        case(Format::Astc10X8UnormBlock): return "Astc10X8UnormBlock";
        case(Format::Astc10X8SrgbBlock): return "Astc10X8SrgbBlock";
        case(Format::Astc10X10UnormBlock): return "Astc10X10UnormBlock";
        case(Format::Astc10X10SrgbBlock): return "Astc10X10SrgbBlock";
        case(Format::Astc12X10UnormBlock): return "Astc12X10UnormBlock";
        case(Format::Astc12X10SrgbBlock): return "Astc12X10SrgbBlock";
        case(Format::Astc12X12UnormBlock): return "Astc12X12UnormBlock";
        case(Format::Astc12X12SrgbBlock): return "Astc12X12SrgbBlock";
        case(Format::Pvrtc12BppUnormBlockIMG): return "Pvrtc12BppUnormBlockIMG";
        case(Format::Pvrtc14BppUnormBlockIMG): return "Pvrtc14BppUnormBlockIMG";
        case(Format::Pvrtc22BppUnormBlockIMG): return "Pvrtc22BppUnormBlockIMG";
        case(Format::Pvrtc24BppUnormBlockIMG): return "Pvrtc24BppUnormBlockIMG";
        case(Format::Pvrtc12BppSrgbBlockIMG): return "Pvrtc12BppSrgbBlockIMG";
        case(Format::Pvrtc14BppSrgbBlockIMG): return "Pvrtc14BppSrgbBlockIMG";
        case(Format::Pvrtc22BppSrgbBlockIMG): return "Pvrtc22BppSrgbBlockIMG";
        case(Format::Pvrtc24BppSrgbBlockIMG): return "Pvrtc24BppSrgbBlockIMG";
        case(Format::Astc4X4SfloatBlockEXT): return "Astc4X4SfloatBlockEXT";
        case(Format::Astc5X4SfloatBlockEXT): return "Astc5X4SfloatBlockEXT";
        case(Format::Astc5X5SfloatBlockEXT): return "Astc5X5SfloatBlockEXT";
        case(Format::Astc6X5SfloatBlockEXT): return "Astc6X5SfloatBlockEXT";
        case(Format::Astc6X6SfloatBlockEXT): return "Astc6X6SfloatBlockEXT";
        case(Format::Astc8X5SfloatBlockEXT): return "Astc8X5SfloatBlockEXT";
        case(Format::Astc8X6SfloatBlockEXT): return "Astc8X6SfloatBlockEXT";
        case(Format::Astc8X8SfloatBlockEXT): return "Astc8X8SfloatBlockEXT";
        case(Format::Astc10X5SfloatBlockEXT): return "Astc10X5SfloatBlockEXT";
        case(Format::Astc10X6SfloatBlockEXT): return "Astc10X6SfloatBlockEXT";
        case(Format::Astc10X8SfloatBlockEXT): return "Astc10X8SfloatBlockEXT";
        case(Format::Astc10X10SfloatBlockEXT): return "Astc10X10SfloatBlockEXT";
        case(Format::Astc12X10SfloatBlockEXT): return "Astc12X10SfloatBlockEXT";
        case(Format::Astc12X12SfloatBlockEXT): return "Astc12X12SfloatBlockEXT";
        case(Format::A4R4G4B4UnormPack16EXT): return "A4R4G4B4UnormPack16EXT";
        case(Format::A4B4G4R4UnormPack16EXT): return "A4B4G4R4UnormPack16EXT";
        case(Format::G8B8G8R8422Unorm): return "G8B8G8R8422Unorm";
        case(Format::B8G8R8G8422Unorm): return "B8G8R8G8422Unorm";
        case(Format::G8B8R83Plane420Unorm): return "G8B8R83Plane420Unorm";
        case(Format::G8B8R82Plane420Unorm): return "G8B8R82Plane420Unorm";
        case(Format::G8B8R83Plane422Unorm): return "G8B8R83Plane422Unorm";
        case(Format::G8B8R82Plane422Unorm): return "G8B8R82Plane422Unorm";
        case(Format::G8B8R83Plane444Unorm): return "G8B8R83Plane444Unorm";
        case(Format::R10X6UnormPack16): return "R10X6UnormPack16";
        case(Format::R10X6G10X6Unorm2Pack16): return "R10X6G10X6Unorm2Pack16";
        case(Format::R10X6G10X6B10X6A10X6Unorm4Pack16): return "R10X6G10X6B10X6A10X6Unorm4Pack16";
        case(Format::G10X6B10X6G10X6R10X6422Unorm4Pack16): return "G10X6B10X6G10X6R10X6422Unorm4Pack16";
        case(Format::B10X6G10X6R10X6G10X6422Unorm4Pack16): return "B10X6G10X6R10X6G10X6422Unorm4Pack16";
        case(Format::G10X6B10X6R10X63Plane420Unorm3Pack16): return "G10X6B10X6R10X63Plane420Unorm3Pack16";
        case(Format::G10X6B10X6R10X62Plane420Unorm3Pack16): return "G10X6B10X6R10X62Plane420Unorm3Pack16";
        case(Format::G10X6B10X6R10X63Plane422Unorm3Pack16): return "G10X6B10X6R10X63Plane422Unorm3Pack16";
        case(Format::G10X6B10X6R10X62Plane422Unorm3Pack16): return "G10X6B10X6R10X62Plane422Unorm3Pack16";
        case(Format::G10X6B10X6R10X63Plane444Unorm3Pack16): return "G10X6B10X6R10X63Plane444Unorm3Pack16";
        case(Format::R12X4UnormPack16): return "R12X4UnormPack16";
        case(Format::R12X4G12X4Unorm2Pack16): return "R12X4G12X4Unorm2Pack16";
        case(Format::R12X4G12X4B12X4A12X4Unorm4Pack16): return "R12X4G12X4B12X4A12X4Unorm4Pack16";
        case(Format::G12X4B12X4G12X4R12X4422Unorm4Pack16): return "G12X4B12X4G12X4R12X4422Unorm4Pack16";
        case(Format::B12X4G12X4R12X4G12X4422Unorm4Pack16): return "B12X4G12X4R12X4G12X4422Unorm4Pack16";
        case(Format::G12X4B12X4R12X43Plane420Unorm3Pack16): return "G12X4B12X4R12X43Plane420Unorm3Pack16";
        case(Format::G12X4B12X4R12X42Plane420Unorm3Pack16): return "G12X4B12X4R12X42Plane420Unorm3Pack16";
        case(Format::G12X4B12X4R12X43Plane422Unorm3Pack16): return "G12X4B12X4R12X43Plane422Unorm3Pack16";
        case(Format::G12X4B12X4R12X42Plane422Unorm3Pack16): return "G12X4B12X4R12X42Plane422Unorm3Pack16";
        case(Format::G12X4B12X4R12X43Plane444Unorm3Pack16): return "G12X4B12X4R12X43Plane444Unorm3Pack16";
        case(Format::G16B16G16R16422Unorm): return "G16B16G16R16422Unorm";
        case(Format::B16G16R16G16422Unorm): return "B16G16R16G16422Unorm";
        case(Format::G16B16R163Plane420Unorm): return "G16B16R163Plane420Unorm";
        case(Format::G16B16R162Plane420Unorm): return "G16B16R162Plane420Unorm";
        case(Format::G16B16R163Plane422Unorm): return "G16B16R163Plane422Unorm";
        case(Format::G16B16R162Plane422Unorm): return "G16B16R162Plane422Unorm";
        case(Format::G16B16R163Plane444Unorm): return "G16B16R163Plane444Unorm";
        default: return "UNKNOWN";
    }
}
const char * to_string(FrontFace val) {
    switch(val) {
        case(FrontFace::CounterClockwise): return "CounterClockwise";
        case(FrontFace::Clockwise): return "Clockwise";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageLayout val) {
    switch(val) {
        case(ImageLayout::Undefined): return "Undefined";
        case(ImageLayout::General): return "General";
        case(ImageLayout::ColorAttachmentOptimal): return "ColorAttachmentOptimal";
        case(ImageLayout::DepthStencilAttachmentOptimal): return "DepthStencilAttachmentOptimal";
        case(ImageLayout::DepthStencilReadOnlyOptimal): return "DepthStencilReadOnlyOptimal";
        case(ImageLayout::ShaderReadOnlyOptimal): return "ShaderReadOnlyOptimal";
        case(ImageLayout::TransferSrcOptimal): return "TransferSrcOptimal";
        case(ImageLayout::TransferDstOptimal): return "TransferDstOptimal";
        case(ImageLayout::Preinitialized): return "Preinitialized";
        case(ImageLayout::PresentSrcKHR): return "PresentSrcKHR";
        case(ImageLayout::SharedPresentKHR): return "SharedPresentKHR";
        case(ImageLayout::ShadingRateOptimalNV): return "ShadingRateOptimalNV";
        case(ImageLayout::FragmentDensityMapOptimalEXT): return "FragmentDensityMapOptimalEXT";
        case(ImageLayout::DepthReadOnlyStencilAttachmentOptimal): return "DepthReadOnlyStencilAttachmentOptimal";
        case(ImageLayout::DepthAttachmentStencilReadOnlyOptimal): return "DepthAttachmentStencilReadOnlyOptimal";
        case(ImageLayout::DepthAttachmentOptimal): return "DepthAttachmentOptimal";
        case(ImageLayout::DepthReadOnlyOptimal): return "DepthReadOnlyOptimal";
        case(ImageLayout::StencilAttachmentOptimal): return "StencilAttachmentOptimal";
        case(ImageLayout::StencilReadOnlyOptimal): return "StencilReadOnlyOptimal";
        default: return "UNKNOWN";
    }
}
const char * to_string(ImageTiling val) {
    switch(val) {
        case(ImageTiling::Optimal): return "Optimal";
        case(ImageTiling::Linear): return "Linear";
        case(ImageTiling::DrmFormatModifierEXT): return "DrmFormatModifierEXT";
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
        case(ImageViewType::Cube): return "Cube";
        case(ImageViewType::e1DArray): return "e1DArray";
        case(ImageViewType::e2DArray): return "e2DArray";
        case(ImageViewType::CubeArray): return "CubeArray";
        default: return "UNKNOWN";
    }
}
const char * to_string(SharingMode val) {
    switch(val) {
        case(SharingMode::Exclusive): return "Exclusive";
        case(SharingMode::Concurrent): return "Concurrent";
        default: return "UNKNOWN";
    }
}
const char * to_string(IndexType val) {
    switch(val) {
        case(IndexType::Uint16): return "Uint16";
        case(IndexType::Uint32): return "Uint32";
        case(IndexType::NoneKHR): return "NoneKHR";
        case(IndexType::Uint8EXT): return "Uint8EXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(LogicOp val) {
    switch(val) {
        case(LogicOp::Clear): return "Clear";
        case(LogicOp::And): return "And";
        case(LogicOp::AndReverse): return "AndReverse";
        case(LogicOp::Copy): return "Copy";
        case(LogicOp::AndInverted): return "AndInverted";
        case(LogicOp::NoOp): return "NoOp";
        case(LogicOp::Xor): return "Xor";
        case(LogicOp::Or): return "Or";
        case(LogicOp::Nor): return "Nor";
        case(LogicOp::Equivalent): return "Equivalent";
        case(LogicOp::Invert): return "Invert";
        case(LogicOp::OrReverse): return "OrReverse";
        case(LogicOp::CopyInverted): return "CopyInverted";
        case(LogicOp::OrInverted): return "OrInverted";
        case(LogicOp::Nand): return "Nand";
        case(LogicOp::Set): return "Set";
        default: return "UNKNOWN";
    }
}
const char * to_string(PhysicalDeviceType val) {
    switch(val) {
        case(PhysicalDeviceType::Other): return "Other";
        case(PhysicalDeviceType::IntegratedGpu): return "IntegratedGpu";
        case(PhysicalDeviceType::DiscreteGpu): return "DiscreteGpu";
        case(PhysicalDeviceType::VirtualGpu): return "VirtualGpu";
        case(PhysicalDeviceType::Cpu): return "Cpu";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineBindPoint val) {
    switch(val) {
        case(PipelineBindPoint::Graphics): return "Graphics";
        case(PipelineBindPoint::Compute): return "Compute";
        case(PipelineBindPoint::RayTracingKHR): return "RayTracingKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PrimitiveTopology val) {
    switch(val) {
        case(PrimitiveTopology::PointList): return "PointList";
        case(PrimitiveTopology::LineList): return "LineList";
        case(PrimitiveTopology::LineStrip): return "LineStrip";
        case(PrimitiveTopology::TriangleList): return "TriangleList";
        case(PrimitiveTopology::TriangleStrip): return "TriangleStrip";
        case(PrimitiveTopology::TriangleFan): return "TriangleFan";
        case(PrimitiveTopology::LineListWithAdjacency): return "LineListWithAdjacency";
        case(PrimitiveTopology::LineStripWithAdjacency): return "LineStripWithAdjacency";
        case(PrimitiveTopology::TriangleListWithAdjacency): return "TriangleListWithAdjacency";
        case(PrimitiveTopology::TriangleStripWithAdjacency): return "TriangleStripWithAdjacency";
        case(PrimitiveTopology::PatchList): return "PatchList";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueryType val) {
    switch(val) {
        case(QueryType::Occlusion): return "Occlusion";
        case(QueryType::PipelineStatistics): return "PipelineStatistics";
        case(QueryType::Timestamp): return "Timestamp";
        case(QueryType::TransformFeedbackStreamEXT): return "TransformFeedbackStreamEXT";
        case(QueryType::PerformanceQueryKHR): return "PerformanceQueryKHR";
        case(QueryType::AccelerationStructureCompactedSizeKHR): return "AccelerationStructureCompactedSizeKHR";
        case(QueryType::AccelerationStructureSerializationSizeKHR): return "AccelerationStructureSerializationSizeKHR";
        case(QueryType::PerformanceQueryINTEL): return "PerformanceQueryINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(SubpassContents val) {
    switch(val) {
        case(SubpassContents::Inline): return "Inline";
        case(SubpassContents::SecondaryCommandBuffers): return "SecondaryCommandBuffers";
        default: return "UNKNOWN";
    }
}
const char * to_string(StencilOp val) {
    switch(val) {
        case(StencilOp::Keep): return "Keep";
        case(StencilOp::Zero): return "Zero";
        case(StencilOp::Replace): return "Replace";
        case(StencilOp::IncrementAndClamp): return "IncrementAndClamp";
        case(StencilOp::DecrementAndClamp): return "DecrementAndClamp";
        case(StencilOp::Invert): return "Invert";
        case(StencilOp::IncrementAndWrap): return "IncrementAndWrap";
        case(StencilOp::DecrementAndWrap): return "DecrementAndWrap";
        default: return "UNKNOWN";
    }
}
const char * to_string(StructureType val) {
    switch(val) {
        case(StructureType::ApplicationInfo): return "ApplicationInfo";
        case(StructureType::InstanceCreateInfo): return "InstanceCreateInfo";
        case(StructureType::DeviceQueueCreateInfo): return "DeviceQueueCreateInfo";
        case(StructureType::DeviceCreateInfo): return "DeviceCreateInfo";
        case(StructureType::SubmitInfo): return "SubmitInfo";
        case(StructureType::MemoryAllocateInfo): return "MemoryAllocateInfo";
        case(StructureType::MappedMemoryRange): return "MappedMemoryRange";
        case(StructureType::BindSparseInfo): return "BindSparseInfo";
        case(StructureType::FenceCreateInfo): return "FenceCreateInfo";
        case(StructureType::SemaphoreCreateInfo): return "SemaphoreCreateInfo";
        case(StructureType::EventCreateInfo): return "EventCreateInfo";
        case(StructureType::QueryPoolCreateInfo): return "QueryPoolCreateInfo";
        case(StructureType::BufferCreateInfo): return "BufferCreateInfo";
        case(StructureType::BufferViewCreateInfo): return "BufferViewCreateInfo";
        case(StructureType::ImageCreateInfo): return "ImageCreateInfo";
        case(StructureType::ImageViewCreateInfo): return "ImageViewCreateInfo";
        case(StructureType::ShaderModuleCreateInfo): return "ShaderModuleCreateInfo";
        case(StructureType::PipelineCacheCreateInfo): return "PipelineCacheCreateInfo";
        case(StructureType::PipelineShaderStageCreateInfo): return "PipelineShaderStageCreateInfo";
        case(StructureType::PipelineVertexInputStateCreateInfo): return "PipelineVertexInputStateCreateInfo";
        case(StructureType::PipelineInputAssemblyStateCreateInfo): return "PipelineInputAssemblyStateCreateInfo";
        case(StructureType::PipelineTessellationStateCreateInfo): return "PipelineTessellationStateCreateInfo";
        case(StructureType::PipelineViewportStateCreateInfo): return "PipelineViewportStateCreateInfo";
        case(StructureType::PipelineRasterizationStateCreateInfo): return "PipelineRasterizationStateCreateInfo";
        case(StructureType::PipelineMultisampleStateCreateInfo): return "PipelineMultisampleStateCreateInfo";
        case(StructureType::PipelineDepthStencilStateCreateInfo): return "PipelineDepthStencilStateCreateInfo";
        case(StructureType::PipelineColorBlendStateCreateInfo): return "PipelineColorBlendStateCreateInfo";
        case(StructureType::PipelineDynamicStateCreateInfo): return "PipelineDynamicStateCreateInfo";
        case(StructureType::GraphicsPipelineCreateInfo): return "GraphicsPipelineCreateInfo";
        case(StructureType::ComputePipelineCreateInfo): return "ComputePipelineCreateInfo";
        case(StructureType::PipelineLayoutCreateInfo): return "PipelineLayoutCreateInfo";
        case(StructureType::SamplerCreateInfo): return "SamplerCreateInfo";
        case(StructureType::DescriptorSetLayoutCreateInfo): return "DescriptorSetLayoutCreateInfo";
        case(StructureType::DescriptorPoolCreateInfo): return "DescriptorPoolCreateInfo";
        case(StructureType::DescriptorSetAllocateInfo): return "DescriptorSetAllocateInfo";
        case(StructureType::WriteDescriptorSet): return "WriteDescriptorSet";
        case(StructureType::CopyDescriptorSet): return "CopyDescriptorSet";
        case(StructureType::FramebufferCreateInfo): return "FramebufferCreateInfo";
        case(StructureType::RenderPassCreateInfo): return "RenderPassCreateInfo";
        case(StructureType::CommandPoolCreateInfo): return "CommandPoolCreateInfo";
        case(StructureType::CommandBufferAllocateInfo): return "CommandBufferAllocateInfo";
        case(StructureType::CommandBufferInheritanceInfo): return "CommandBufferInheritanceInfo";
        case(StructureType::CommandBufferBeginInfo): return "CommandBufferBeginInfo";
        case(StructureType::RenderPassBeginInfo): return "RenderPassBeginInfo";
        case(StructureType::BufferMemoryBarrier): return "BufferMemoryBarrier";
        case(StructureType::ImageMemoryBarrier): return "ImageMemoryBarrier";
        case(StructureType::MemoryBarrier): return "MemoryBarrier";
        case(StructureType::LoaderInstanceCreateInfo): return "LoaderInstanceCreateInfo";
        case(StructureType::LoaderDeviceCreateInfo): return "LoaderDeviceCreateInfo";
        case(StructureType::SwapchainCreateInfoKHR): return "SwapchainCreateInfoKHR";
        case(StructureType::PresentInfoKHR): return "PresentInfoKHR";
        case(StructureType::DeviceGroupPresentCapabilitiesKHR): return "DeviceGroupPresentCapabilitiesKHR";
        case(StructureType::ImageSwapchainCreateInfoKHR): return "ImageSwapchainCreateInfoKHR";
        case(StructureType::BindImageMemorySwapchainInfoKHR): return "BindImageMemorySwapchainInfoKHR";
        case(StructureType::AcquireNextImageInfoKHR): return "AcquireNextImageInfoKHR";
        case(StructureType::DeviceGroupPresentInfoKHR): return "DeviceGroupPresentInfoKHR";
        case(StructureType::DeviceGroupSwapchainCreateInfoKHR): return "DeviceGroupSwapchainCreateInfoKHR";
        case(StructureType::DisplayModeCreateInfoKHR): return "DisplayModeCreateInfoKHR";
        case(StructureType::DisplaySurfaceCreateInfoKHR): return "DisplaySurfaceCreateInfoKHR";
        case(StructureType::DisplayPresentInfoKHR): return "DisplayPresentInfoKHR";
        case(StructureType::XlibSurfaceCreateInfoKHR): return "XlibSurfaceCreateInfoKHR";
        case(StructureType::XcbSurfaceCreateInfoKHR): return "XcbSurfaceCreateInfoKHR";
        case(StructureType::WaylandSurfaceCreateInfoKHR): return "WaylandSurfaceCreateInfoKHR";
        case(StructureType::AndroidSurfaceCreateInfoKHR): return "AndroidSurfaceCreateInfoKHR";
        case(StructureType::Win32SurfaceCreateInfoKHR): return "Win32SurfaceCreateInfoKHR";
        case(StructureType::DebugReportCallbackCreateInfoEXT): return "DebugReportCallbackCreateInfoEXT";
        case(StructureType::PipelineRasterizationStateRasterizationOrderAMD): return "PipelineRasterizationStateRasterizationOrderAMD";
        case(StructureType::DebugMarkerObjectNameInfoEXT): return "DebugMarkerObjectNameInfoEXT";
        case(StructureType::DebugMarkerObjectTagInfoEXT): return "DebugMarkerObjectTagInfoEXT";
        case(StructureType::DebugMarkerMarkerInfoEXT): return "DebugMarkerMarkerInfoEXT";
        case(StructureType::DedicatedAllocationImageCreateInfoNV): return "DedicatedAllocationImageCreateInfoNV";
        case(StructureType::DedicatedAllocationBufferCreateInfoNV): return "DedicatedAllocationBufferCreateInfoNV";
        case(StructureType::DedicatedAllocationMemoryAllocateInfoNV): return "DedicatedAllocationMemoryAllocateInfoNV";
        case(StructureType::PhysicalDeviceTransformFeedbackFeaturesEXT): return "PhysicalDeviceTransformFeedbackFeaturesEXT";
        case(StructureType::PhysicalDeviceTransformFeedbackPropertiesEXT): return "PhysicalDeviceTransformFeedbackPropertiesEXT";
        case(StructureType::PipelineRasterizationStateStreamCreateInfoEXT): return "PipelineRasterizationStateStreamCreateInfoEXT";
        case(StructureType::ImageViewHandleInfoNVX): return "ImageViewHandleInfoNVX";
        case(StructureType::ImageViewAddressPropertiesNVX): return "ImageViewAddressPropertiesNVX";
        case(StructureType::TextureLodGatherFormatPropertiesAMD): return "TextureLodGatherFormatPropertiesAMD";
        case(StructureType::StreamDescriptorSurfaceCreateInfoGGP): return "StreamDescriptorSurfaceCreateInfoGGP";
        case(StructureType::PhysicalDeviceCornerSampledImageFeaturesNV): return "PhysicalDeviceCornerSampledImageFeaturesNV";
        case(StructureType::ExternalMemoryImageCreateInfoNV): return "ExternalMemoryImageCreateInfoNV";
        case(StructureType::ExportMemoryAllocateInfoNV): return "ExportMemoryAllocateInfoNV";
        case(StructureType::ImportMemoryWin32HandleInfoNV): return "ImportMemoryWin32HandleInfoNV";
        case(StructureType::ExportMemoryWin32HandleInfoNV): return "ExportMemoryWin32HandleInfoNV";
        case(StructureType::Win32KeyedMutexAcquireReleaseInfoNV): return "Win32KeyedMutexAcquireReleaseInfoNV";
        case(StructureType::ValidationFlagsEXT): return "ValidationFlagsEXT";
        case(StructureType::ViSurfaceCreateInfoNN): return "ViSurfaceCreateInfoNN";
        case(StructureType::PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT): return "PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT";
        case(StructureType::ImageViewAstcDecodeModeEXT): return "ImageViewAstcDecodeModeEXT";
        case(StructureType::PhysicalDeviceAstcDecodeFeaturesEXT): return "PhysicalDeviceAstcDecodeFeaturesEXT";
        case(StructureType::ImportMemoryWin32HandleInfoKHR): return "ImportMemoryWin32HandleInfoKHR";
        case(StructureType::ExportMemoryWin32HandleInfoKHR): return "ExportMemoryWin32HandleInfoKHR";
        case(StructureType::MemoryWin32HandlePropertiesKHR): return "MemoryWin32HandlePropertiesKHR";
        case(StructureType::MemoryGetWin32HandleInfoKHR): return "MemoryGetWin32HandleInfoKHR";
        case(StructureType::ImportMemoryFdInfoKHR): return "ImportMemoryFdInfoKHR";
        case(StructureType::MemoryFdPropertiesKHR): return "MemoryFdPropertiesKHR";
        case(StructureType::MemoryGetFdInfoKHR): return "MemoryGetFdInfoKHR";
        case(StructureType::Win32KeyedMutexAcquireReleaseInfoKHR): return "Win32KeyedMutexAcquireReleaseInfoKHR";
        case(StructureType::ImportSemaphoreWin32HandleInfoKHR): return "ImportSemaphoreWin32HandleInfoKHR";
        case(StructureType::ExportSemaphoreWin32HandleInfoKHR): return "ExportSemaphoreWin32HandleInfoKHR";
        case(StructureType::D3D12FenceSubmitInfoKHR): return "D3D12FenceSubmitInfoKHR";
        case(StructureType::SemaphoreGetWin32HandleInfoKHR): return "SemaphoreGetWin32HandleInfoKHR";
        case(StructureType::ImportSemaphoreFdInfoKHR): return "ImportSemaphoreFdInfoKHR";
        case(StructureType::SemaphoreGetFdInfoKHR): return "SemaphoreGetFdInfoKHR";
        case(StructureType::PhysicalDevicePushDescriptorPropertiesKHR): return "PhysicalDevicePushDescriptorPropertiesKHR";
        case(StructureType::CommandBufferInheritanceConditionalRenderingInfoEXT): return "CommandBufferInheritanceConditionalRenderingInfoEXT";
        case(StructureType::PhysicalDeviceConditionalRenderingFeaturesEXT): return "PhysicalDeviceConditionalRenderingFeaturesEXT";
        case(StructureType::ConditionalRenderingBeginInfoEXT): return "ConditionalRenderingBeginInfoEXT";
        case(StructureType::PresentRegionsKHR): return "PresentRegionsKHR";
        case(StructureType::PipelineViewportWScalingStateCreateInfoNV): return "PipelineViewportWScalingStateCreateInfoNV";
        case(StructureType::SurfaceCapabilities2EXT): return "SurfaceCapabilities2EXT";
        case(StructureType::DisplayPowerInfoEXT): return "DisplayPowerInfoEXT";
        case(StructureType::DeviceEventInfoEXT): return "DeviceEventInfoEXT";
        case(StructureType::DisplayEventInfoEXT): return "DisplayEventInfoEXT";
        case(StructureType::SwapchainCounterCreateInfoEXT): return "SwapchainCounterCreateInfoEXT";
        case(StructureType::PresentTimesInfoGOOGLE): return "PresentTimesInfoGOOGLE";
        case(StructureType::PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX): return "PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX";
        case(StructureType::PipelineViewportSwizzleStateCreateInfoNV): return "PipelineViewportSwizzleStateCreateInfoNV";
        case(StructureType::PhysicalDeviceDiscardRectanglePropertiesEXT): return "PhysicalDeviceDiscardRectanglePropertiesEXT";
        case(StructureType::PipelineDiscardRectangleStateCreateInfoEXT): return "PipelineDiscardRectangleStateCreateInfoEXT";
        case(StructureType::PhysicalDeviceConservativeRasterizationPropertiesEXT): return "PhysicalDeviceConservativeRasterizationPropertiesEXT";
        case(StructureType::PipelineRasterizationConservativeStateCreateInfoEXT): return "PipelineRasterizationConservativeStateCreateInfoEXT";
        case(StructureType::PhysicalDeviceDepthClipEnableFeaturesEXT): return "PhysicalDeviceDepthClipEnableFeaturesEXT";
        case(StructureType::PipelineRasterizationDepthClipStateCreateInfoEXT): return "PipelineRasterizationDepthClipStateCreateInfoEXT";
        case(StructureType::HdrMetadataEXT): return "HdrMetadataEXT";
        case(StructureType::SharedPresentSurfaceCapabilitiesKHR): return "SharedPresentSurfaceCapabilitiesKHR";
        case(StructureType::ImportFenceWin32HandleInfoKHR): return "ImportFenceWin32HandleInfoKHR";
        case(StructureType::ExportFenceWin32HandleInfoKHR): return "ExportFenceWin32HandleInfoKHR";
        case(StructureType::FenceGetWin32HandleInfoKHR): return "FenceGetWin32HandleInfoKHR";
        case(StructureType::ImportFenceFdInfoKHR): return "ImportFenceFdInfoKHR";
        case(StructureType::FenceGetFdInfoKHR): return "FenceGetFdInfoKHR";
        case(StructureType::PhysicalDevicePerformanceQueryFeaturesKHR): return "PhysicalDevicePerformanceQueryFeaturesKHR";
        case(StructureType::PhysicalDevicePerformanceQueryPropertiesKHR): return "PhysicalDevicePerformanceQueryPropertiesKHR";
        case(StructureType::QueryPoolPerformanceCreateInfoKHR): return "QueryPoolPerformanceCreateInfoKHR";
        case(StructureType::PerformanceQuerySubmitInfoKHR): return "PerformanceQuerySubmitInfoKHR";
        case(StructureType::AcquireProfilingLockInfoKHR): return "AcquireProfilingLockInfoKHR";
        case(StructureType::PerformanceCounterKHR): return "PerformanceCounterKHR";
        case(StructureType::PerformanceCounterDescriptionKHR): return "PerformanceCounterDescriptionKHR";
        case(StructureType::PhysicalDeviceSurfaceInfo2KHR): return "PhysicalDeviceSurfaceInfo2KHR";
        case(StructureType::SurfaceCapabilities2KHR): return "SurfaceCapabilities2KHR";
        case(StructureType::SurfaceFormat2KHR): return "SurfaceFormat2KHR";
        case(StructureType::DisplayProperties2KHR): return "DisplayProperties2KHR";
        case(StructureType::DisplayPlaneProperties2KHR): return "DisplayPlaneProperties2KHR";
        case(StructureType::DisplayModeProperties2KHR): return "DisplayModeProperties2KHR";
        case(StructureType::DisplayPlaneInfo2KHR): return "DisplayPlaneInfo2KHR";
        case(StructureType::DisplayPlaneCapabilities2KHR): return "DisplayPlaneCapabilities2KHR";
        case(StructureType::IosSurfaceCreateInfoMVK): return "IosSurfaceCreateInfoMVK";
        case(StructureType::MacosSurfaceCreateInfoMVK): return "MacosSurfaceCreateInfoMVK";
        case(StructureType::DebugUtilsObjectNameInfoEXT): return "DebugUtilsObjectNameInfoEXT";
        case(StructureType::DebugUtilsObjectTagInfoEXT): return "DebugUtilsObjectTagInfoEXT";
        case(StructureType::DebugUtilsLabelEXT): return "DebugUtilsLabelEXT";
        case(StructureType::DebugUtilsMessengerCallbackDataEXT): return "DebugUtilsMessengerCallbackDataEXT";
        case(StructureType::DebugUtilsMessengerCreateInfoEXT): return "DebugUtilsMessengerCreateInfoEXT";
        case(StructureType::AndroidHardwareBufferUsageANDROID): return "AndroidHardwareBufferUsageANDROID";
        case(StructureType::AndroidHardwareBufferPropertiesANDROID): return "AndroidHardwareBufferPropertiesANDROID";
        case(StructureType::AndroidHardwareBufferFormatPropertiesANDROID): return "AndroidHardwareBufferFormatPropertiesANDROID";
        case(StructureType::ImportAndroidHardwareBufferInfoANDROID): return "ImportAndroidHardwareBufferInfoANDROID";
        case(StructureType::MemoryGetAndroidHardwareBufferInfoANDROID): return "MemoryGetAndroidHardwareBufferInfoANDROID";
        case(StructureType::ExternalFormatANDROID): return "ExternalFormatANDROID";
        case(StructureType::PhysicalDeviceInlineUniformBlockFeaturesEXT): return "PhysicalDeviceInlineUniformBlockFeaturesEXT";
        case(StructureType::PhysicalDeviceInlineUniformBlockPropertiesEXT): return "PhysicalDeviceInlineUniformBlockPropertiesEXT";
        case(StructureType::WriteDescriptorSetInlineUniformBlockEXT): return "WriteDescriptorSetInlineUniformBlockEXT";
        case(StructureType::DescriptorPoolInlineUniformBlockCreateInfoEXT): return "DescriptorPoolInlineUniformBlockCreateInfoEXT";
        case(StructureType::SampleLocationsInfoEXT): return "SampleLocationsInfoEXT";
        case(StructureType::RenderPassSampleLocationsBeginInfoEXT): return "RenderPassSampleLocationsBeginInfoEXT";
        case(StructureType::PipelineSampleLocationsStateCreateInfoEXT): return "PipelineSampleLocationsStateCreateInfoEXT";
        case(StructureType::PhysicalDeviceSampleLocationsPropertiesEXT): return "PhysicalDeviceSampleLocationsPropertiesEXT";
        case(StructureType::MultisamplePropertiesEXT): return "MultisamplePropertiesEXT";
        case(StructureType::PhysicalDeviceBlendOperationAdvancedFeaturesEXT): return "PhysicalDeviceBlendOperationAdvancedFeaturesEXT";
        case(StructureType::PhysicalDeviceBlendOperationAdvancedPropertiesEXT): return "PhysicalDeviceBlendOperationAdvancedPropertiesEXT";
        case(StructureType::PipelineColorBlendAdvancedStateCreateInfoEXT): return "PipelineColorBlendAdvancedStateCreateInfoEXT";
        case(StructureType::PipelineCoverageToColorStateCreateInfoNV): return "PipelineCoverageToColorStateCreateInfoNV";
        case(StructureType::BindAccelerationStructureMemoryInfoKHR): return "BindAccelerationStructureMemoryInfoKHR";
        case(StructureType::WriteDescriptorSetAccelerationStructureKHR): return "WriteDescriptorSetAccelerationStructureKHR";
        case(StructureType::AccelerationStructureBuildGeometryInfoKHR): return "AccelerationStructureBuildGeometryInfoKHR";
        case(StructureType::AccelerationStructureCreateGeometryTypeInfoKHR): return "AccelerationStructureCreateGeometryTypeInfoKHR";
        case(StructureType::AccelerationStructureDeviceAddressInfoKHR): return "AccelerationStructureDeviceAddressInfoKHR";
        case(StructureType::AccelerationStructureGeometryAabbsDataKHR): return "AccelerationStructureGeometryAabbsDataKHR";
        case(StructureType::AccelerationStructureGeometryInstancesDataKHR): return "AccelerationStructureGeometryInstancesDataKHR";
        case(StructureType::AccelerationStructureGeometryTrianglesDataKHR): return "AccelerationStructureGeometryTrianglesDataKHR";
        case(StructureType::AccelerationStructureGeometryKHR): return "AccelerationStructureGeometryKHR";
        case(StructureType::AccelerationStructureMemoryRequirementsInfoKHR): return "AccelerationStructureMemoryRequirementsInfoKHR";
        case(StructureType::AccelerationStructureVersionKHR): return "AccelerationStructureVersionKHR";
        case(StructureType::CopyAccelerationStructureInfoKHR): return "CopyAccelerationStructureInfoKHR";
        case(StructureType::CopyAccelerationStructureToMemoryInfoKHR): return "CopyAccelerationStructureToMemoryInfoKHR";
        case(StructureType::CopyMemoryToAccelerationStructureInfoKHR): return "CopyMemoryToAccelerationStructureInfoKHR";
        case(StructureType::PhysicalDeviceRayTracingFeaturesKHR): return "PhysicalDeviceRayTracingFeaturesKHR";
        case(StructureType::PhysicalDeviceRayTracingPropertiesKHR): return "PhysicalDeviceRayTracingPropertiesKHR";
        case(StructureType::RayTracingPipelineCreateInfoKHR): return "RayTracingPipelineCreateInfoKHR";
        case(StructureType::RayTracingShaderGroupCreateInfoKHR): return "RayTracingShaderGroupCreateInfoKHR";
        case(StructureType::AccelerationStructureCreateInfoKHR): return "AccelerationStructureCreateInfoKHR";
        case(StructureType::RayTracingPipelineInterfaceCreateInfoKHR): return "RayTracingPipelineInterfaceCreateInfoKHR";
        case(StructureType::PipelineCoverageModulationStateCreateInfoNV): return "PipelineCoverageModulationStateCreateInfoNV";
        case(StructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV): return "PhysicalDeviceShaderSmBuiltinsFeaturesNV";
        case(StructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV): return "PhysicalDeviceShaderSmBuiltinsPropertiesNV";
        case(StructureType::DrmFormatModifierPropertiesListEXT): return "DrmFormatModifierPropertiesListEXT";
        case(StructureType::DrmFormatModifierPropertiesEXT): return "DrmFormatModifierPropertiesEXT";
        case(StructureType::PhysicalDeviceImageDrmFormatModifierInfoEXT): return "PhysicalDeviceImageDrmFormatModifierInfoEXT";
        case(StructureType::ImageDrmFormatModifierListCreateInfoEXT): return "ImageDrmFormatModifierListCreateInfoEXT";
        case(StructureType::ImageDrmFormatModifierExplicitCreateInfoEXT): return "ImageDrmFormatModifierExplicitCreateInfoEXT";
        case(StructureType::ImageDrmFormatModifierPropertiesEXT): return "ImageDrmFormatModifierPropertiesEXT";
        case(StructureType::ValidationCacheCreateInfoEXT): return "ValidationCacheCreateInfoEXT";
        case(StructureType::ShaderModuleValidationCacheCreateInfoEXT): return "ShaderModuleValidationCacheCreateInfoEXT";
        case(StructureType::PhysicalDevicePortabilitySubsetFeaturesKHR): return "PhysicalDevicePortabilitySubsetFeaturesKHR";
        case(StructureType::PhysicalDevicePortabilitySubsetPropertiesKHR): return "PhysicalDevicePortabilitySubsetPropertiesKHR";
        case(StructureType::PipelineViewportShadingRateImageStateCreateInfoNV): return "PipelineViewportShadingRateImageStateCreateInfoNV";
        case(StructureType::PhysicalDeviceShadingRateImageFeaturesNV): return "PhysicalDeviceShadingRateImageFeaturesNV";
        case(StructureType::PhysicalDeviceShadingRateImagePropertiesNV): return "PhysicalDeviceShadingRateImagePropertiesNV";
        case(StructureType::PipelineViewportCoarseSampleOrderStateCreateInfoNV): return "PipelineViewportCoarseSampleOrderStateCreateInfoNV";
        case(StructureType::RayTracingPipelineCreateInfoNV): return "RayTracingPipelineCreateInfoNV";
        case(StructureType::AccelerationStructureCreateInfoNV): return "AccelerationStructureCreateInfoNV";
        case(StructureType::GeometryNV): return "GeometryNV";
        case(StructureType::GeometryTrianglesNV): return "GeometryTrianglesNV";
        case(StructureType::GeometryAabbNV): return "GeometryAabbNV";
        case(StructureType::AccelerationStructureMemoryRequirementsInfoNV): return "AccelerationStructureMemoryRequirementsInfoNV";
        case(StructureType::PhysicalDeviceRayTracingPropertiesNV): return "PhysicalDeviceRayTracingPropertiesNV";
        case(StructureType::RayTracingShaderGroupCreateInfoNV): return "RayTracingShaderGroupCreateInfoNV";
        case(StructureType::AccelerationStructureInfoNV): return "AccelerationStructureInfoNV";
        case(StructureType::PhysicalDeviceRepresentativeFragmentTestFeaturesNV): return "PhysicalDeviceRepresentativeFragmentTestFeaturesNV";
        case(StructureType::PipelineRepresentativeFragmentTestStateCreateInfoNV): return "PipelineRepresentativeFragmentTestStateCreateInfoNV";
        case(StructureType::PhysicalDeviceImageViewImageFormatInfoEXT): return "PhysicalDeviceImageViewImageFormatInfoEXT";
        case(StructureType::FilterCubicImageViewImageFormatPropertiesEXT): return "FilterCubicImageViewImageFormatPropertiesEXT";
        case(StructureType::DeviceQueueGlobalPriorityCreateInfoEXT): return "DeviceQueueGlobalPriorityCreateInfoEXT";
        case(StructureType::ImportMemoryHostPointerInfoEXT): return "ImportMemoryHostPointerInfoEXT";
        case(StructureType::MemoryHostPointerPropertiesEXT): return "MemoryHostPointerPropertiesEXT";
        case(StructureType::PhysicalDeviceExternalMemoryHostPropertiesEXT): return "PhysicalDeviceExternalMemoryHostPropertiesEXT";
        case(StructureType::PhysicalDeviceShaderClockFeaturesKHR): return "PhysicalDeviceShaderClockFeaturesKHR";
        case(StructureType::PipelineCompilerControlCreateInfoAMD): return "PipelineCompilerControlCreateInfoAMD";
        case(StructureType::CalibratedTimestampInfoEXT): return "CalibratedTimestampInfoEXT";
        case(StructureType::PhysicalDeviceShaderCorePropertiesAMD): return "PhysicalDeviceShaderCorePropertiesAMD";
        case(StructureType::DeviceMemoryOverallocationCreateInfoAMD): return "DeviceMemoryOverallocationCreateInfoAMD";
        case(StructureType::PhysicalDeviceVertexAttributeDivisorPropertiesEXT): return "PhysicalDeviceVertexAttributeDivisorPropertiesEXT";
        case(StructureType::PipelineVertexInputDivisorStateCreateInfoEXT): return "PipelineVertexInputDivisorStateCreateInfoEXT";
        case(StructureType::PhysicalDeviceVertexAttributeDivisorFeaturesEXT): return "PhysicalDeviceVertexAttributeDivisorFeaturesEXT";
        case(StructureType::PresentFrameTokenGGP): return "PresentFrameTokenGGP";
        case(StructureType::PipelineCreationFeedbackCreateInfoEXT): return "PipelineCreationFeedbackCreateInfoEXT";
        case(StructureType::PhysicalDeviceComputeShaderDerivativesFeaturesNV): return "PhysicalDeviceComputeShaderDerivativesFeaturesNV";
        case(StructureType::PhysicalDeviceMeshShaderFeaturesNV): return "PhysicalDeviceMeshShaderFeaturesNV";
        case(StructureType::PhysicalDeviceMeshShaderPropertiesNV): return "PhysicalDeviceMeshShaderPropertiesNV";
        case(StructureType::PhysicalDeviceFragmentShaderBarycentricFeaturesNV): return "PhysicalDeviceFragmentShaderBarycentricFeaturesNV";
        case(StructureType::PhysicalDeviceShaderImageFootprintFeaturesNV): return "PhysicalDeviceShaderImageFootprintFeaturesNV";
        case(StructureType::PipelineViewportExclusiveScissorStateCreateInfoNV): return "PipelineViewportExclusiveScissorStateCreateInfoNV";
        case(StructureType::PhysicalDeviceExclusiveScissorFeaturesNV): return "PhysicalDeviceExclusiveScissorFeaturesNV";
        case(StructureType::CheckpointDataNV): return "CheckpointDataNV";
        case(StructureType::QueueFamilyCheckpointPropertiesNV): return "QueueFamilyCheckpointPropertiesNV";
        case(StructureType::PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL): return "PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL";
        case(StructureType::QueryPoolPerformanceQueryCreateInfoINTEL): return "QueryPoolPerformanceQueryCreateInfoINTEL";
        case(StructureType::InitializePerformanceApiInfoINTEL): return "InitializePerformanceApiInfoINTEL";
        case(StructureType::PerformanceMarkerInfoINTEL): return "PerformanceMarkerInfoINTEL";
        case(StructureType::PerformanceStreamMarkerInfoINTEL): return "PerformanceStreamMarkerInfoINTEL";
        case(StructureType::PerformanceOverrideInfoINTEL): return "PerformanceOverrideInfoINTEL";
        case(StructureType::PerformanceConfigurationAcquireInfoINTEL): return "PerformanceConfigurationAcquireInfoINTEL";
        case(StructureType::PhysicalDevicePciBusInfoPropertiesEXT): return "PhysicalDevicePciBusInfoPropertiesEXT";
        case(StructureType::DisplayNativeHdrSurfaceCapabilitiesAMD): return "DisplayNativeHdrSurfaceCapabilitiesAMD";
        case(StructureType::SwapchainDisplayNativeHdrCreateInfoAMD): return "SwapchainDisplayNativeHdrCreateInfoAMD";
        case(StructureType::ImagepipeSurfaceCreateInfoFUCHSIA): return "ImagepipeSurfaceCreateInfoFUCHSIA";
        case(StructureType::MetalSurfaceCreateInfoEXT): return "MetalSurfaceCreateInfoEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT): return "PhysicalDeviceFragmentDensityMapFeaturesEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT): return "PhysicalDeviceFragmentDensityMapPropertiesEXT";
        case(StructureType::RenderPassFragmentDensityMapCreateInfoEXT): return "RenderPassFragmentDensityMapCreateInfoEXT";
        case(StructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT): return "PhysicalDeviceSubgroupSizeControlPropertiesEXT";
        case(StructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT): return "PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT";
        case(StructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT): return "PhysicalDeviceSubgroupSizeControlFeaturesEXT";
        case(StructureType::PhysicalDeviceShaderCoreProperties2AMD): return "PhysicalDeviceShaderCoreProperties2AMD";
        case(StructureType::PhysicalDeviceCoherentMemoryFeaturesAMD): return "PhysicalDeviceCoherentMemoryFeaturesAMD";
        case(StructureType::PhysicalDeviceShaderImageAtomicInt64FeaturesEXT): return "PhysicalDeviceShaderImageAtomicInt64FeaturesEXT";
        case(StructureType::PhysicalDeviceMemoryBudgetPropertiesEXT): return "PhysicalDeviceMemoryBudgetPropertiesEXT";
        case(StructureType::PhysicalDeviceMemoryPriorityFeaturesEXT): return "PhysicalDeviceMemoryPriorityFeaturesEXT";
        case(StructureType::MemoryPriorityAllocateInfoEXT): return "MemoryPriorityAllocateInfoEXT";
        case(StructureType::SurfaceProtectedCapabilitiesKHR): return "SurfaceProtectedCapabilitiesKHR";
        case(StructureType::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV): return "PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV";
        case(StructureType::PhysicalDeviceBufferDeviceAddressFeaturesEXT): return "PhysicalDeviceBufferDeviceAddressFeaturesEXT";
        case(StructureType::BufferDeviceAddressCreateInfoEXT): return "BufferDeviceAddressCreateInfoEXT";
        case(StructureType::PhysicalDeviceToolPropertiesEXT): return "PhysicalDeviceToolPropertiesEXT";
        case(StructureType::ValidationFeaturesEXT): return "ValidationFeaturesEXT";
        case(StructureType::PhysicalDeviceCooperativeMatrixFeaturesNV): return "PhysicalDeviceCooperativeMatrixFeaturesNV";
        case(StructureType::CooperativeMatrixPropertiesNV): return "CooperativeMatrixPropertiesNV";
        case(StructureType::PhysicalDeviceCooperativeMatrixPropertiesNV): return "PhysicalDeviceCooperativeMatrixPropertiesNV";
        case(StructureType::PhysicalDeviceCoverageReductionModeFeaturesNV): return "PhysicalDeviceCoverageReductionModeFeaturesNV";
        case(StructureType::PipelineCoverageReductionStateCreateInfoNV): return "PipelineCoverageReductionStateCreateInfoNV";
        case(StructureType::FramebufferMixedSamplesCombinationNV): return "FramebufferMixedSamplesCombinationNV";
        case(StructureType::PhysicalDeviceFragmentShaderInterlockFeaturesEXT): return "PhysicalDeviceFragmentShaderInterlockFeaturesEXT";
        case(StructureType::PhysicalDeviceYcbcrImageArraysFeaturesEXT): return "PhysicalDeviceYcbcrImageArraysFeaturesEXT";
        case(StructureType::SurfaceFullScreenExclusiveInfoEXT): return "SurfaceFullScreenExclusiveInfoEXT";
        case(StructureType::SurfaceCapabilitiesFullScreenExclusiveEXT): return "SurfaceCapabilitiesFullScreenExclusiveEXT";
        case(StructureType::SurfaceFullScreenExclusiveWin32InfoEXT): return "SurfaceFullScreenExclusiveWin32InfoEXT";
        case(StructureType::HeadlessSurfaceCreateInfoEXT): return "HeadlessSurfaceCreateInfoEXT";
        case(StructureType::PhysicalDeviceLineRasterizationFeaturesEXT): return "PhysicalDeviceLineRasterizationFeaturesEXT";
        case(StructureType::PipelineRasterizationLineStateCreateInfoEXT): return "PipelineRasterizationLineStateCreateInfoEXT";
        case(StructureType::PhysicalDeviceLineRasterizationPropertiesEXT): return "PhysicalDeviceLineRasterizationPropertiesEXT";
        case(StructureType::PhysicalDeviceShaderAtomicFloatFeaturesEXT): return "PhysicalDeviceShaderAtomicFloatFeaturesEXT";
        case(StructureType::PhysicalDeviceIndexTypeUint8FeaturesEXT): return "PhysicalDeviceIndexTypeUint8FeaturesEXT";
        case(StructureType::PhysicalDeviceExtendedDynamicStateFeaturesEXT): return "PhysicalDeviceExtendedDynamicStateFeaturesEXT";
        case(StructureType::DeferredOperationInfoKHR): return "DeferredOperationInfoKHR";
        case(StructureType::PhysicalDevicePipelineExecutablePropertiesFeaturesKHR): return "PhysicalDevicePipelineExecutablePropertiesFeaturesKHR";
        case(StructureType::PipelineInfoKHR): return "PipelineInfoKHR";
        case(StructureType::PipelineExecutablePropertiesKHR): return "PipelineExecutablePropertiesKHR";
        case(StructureType::PipelineExecutableInfoKHR): return "PipelineExecutableInfoKHR";
        case(StructureType::PipelineExecutableStatisticKHR): return "PipelineExecutableStatisticKHR";
        case(StructureType::PipelineExecutableInternalRepresentationKHR): return "PipelineExecutableInternalRepresentationKHR";
        case(StructureType::PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT): return "PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT";
        case(StructureType::PhysicalDeviceDeviceGeneratedCommandsPropertiesNV): return "PhysicalDeviceDeviceGeneratedCommandsPropertiesNV";
        case(StructureType::GraphicsShaderGroupCreateInfoNV): return "GraphicsShaderGroupCreateInfoNV";
        case(StructureType::GraphicsPipelineShaderGroupsCreateInfoNV): return "GraphicsPipelineShaderGroupsCreateInfoNV";
        case(StructureType::IndirectCommandsLayoutTokenNV): return "IndirectCommandsLayoutTokenNV";
        case(StructureType::IndirectCommandsLayoutCreateInfoNV): return "IndirectCommandsLayoutCreateInfoNV";
        case(StructureType::GeneratedCommandsInfoNV): return "GeneratedCommandsInfoNV";
        case(StructureType::GeneratedCommandsMemoryRequirementsInfoNV): return "GeneratedCommandsMemoryRequirementsInfoNV";
        case(StructureType::PhysicalDeviceDeviceGeneratedCommandsFeaturesNV): return "PhysicalDeviceDeviceGeneratedCommandsFeaturesNV";
        case(StructureType::PhysicalDeviceTexelBufferAlignmentFeaturesEXT): return "PhysicalDeviceTexelBufferAlignmentFeaturesEXT";
        case(StructureType::PhysicalDeviceTexelBufferAlignmentPropertiesEXT): return "PhysicalDeviceTexelBufferAlignmentPropertiesEXT";
        case(StructureType::CommandBufferInheritanceRenderPassTransformInfoQCOM): return "CommandBufferInheritanceRenderPassTransformInfoQCOM";
        case(StructureType::RenderPassTransformBeginInfoQCOM): return "RenderPassTransformBeginInfoQCOM";
        case(StructureType::PhysicalDeviceDeviceMemoryReportFeaturesEXT): return "PhysicalDeviceDeviceMemoryReportFeaturesEXT";
        case(StructureType::DeviceDeviceMemoryReportCreateInfoEXT): return "DeviceDeviceMemoryReportCreateInfoEXT";
        case(StructureType::DeviceMemoryReportCallbackDataEXT): return "DeviceMemoryReportCallbackDataEXT";
        case(StructureType::PhysicalDeviceRobustness2FeaturesEXT): return "PhysicalDeviceRobustness2FeaturesEXT";
        case(StructureType::PhysicalDeviceRobustness2PropertiesEXT): return "PhysicalDeviceRobustness2PropertiesEXT";
        case(StructureType::SamplerCustomBorderColorCreateInfoEXT): return "SamplerCustomBorderColorCreateInfoEXT";
        case(StructureType::PhysicalDeviceCustomBorderColorPropertiesEXT): return "PhysicalDeviceCustomBorderColorPropertiesEXT";
        case(StructureType::PhysicalDeviceCustomBorderColorFeaturesEXT): return "PhysicalDeviceCustomBorderColorFeaturesEXT";
        case(StructureType::PipelineLibraryCreateInfoKHR): return "PipelineLibraryCreateInfoKHR";
        case(StructureType::PhysicalDevicePrivateDataFeaturesEXT): return "PhysicalDevicePrivateDataFeaturesEXT";
        case(StructureType::DevicePrivateDataCreateInfoEXT): return "DevicePrivateDataCreateInfoEXT";
        case(StructureType::PrivateDataSlotCreateInfoEXT): return "PrivateDataSlotCreateInfoEXT";
        case(StructureType::PhysicalDevicePipelineCreationCacheControlFeaturesEXT): return "PhysicalDevicePipelineCreationCacheControlFeaturesEXT";
        case(StructureType::PhysicalDeviceDiagnosticsConfigFeaturesNV): return "PhysicalDeviceDiagnosticsConfigFeaturesNV";
        case(StructureType::DeviceDiagnosticsConfigCreateInfoNV): return "DeviceDiagnosticsConfigCreateInfoNV";
        case(StructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT): return "PhysicalDeviceFragmentDensityMap2FeaturesEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT): return "PhysicalDeviceFragmentDensityMap2PropertiesEXT";
        case(StructureType::PhysicalDeviceImageRobustnessFeaturesEXT): return "PhysicalDeviceImageRobustnessFeaturesEXT";
        case(StructureType::CopyBufferInfo2KHR): return "CopyBufferInfo2KHR";
        case(StructureType::CopyImageInfo2KHR): return "CopyImageInfo2KHR";
        case(StructureType::CopyBufferToImageInfo2KHR): return "CopyBufferToImageInfo2KHR";
        case(StructureType::CopyImageToBufferInfo2KHR): return "CopyImageToBufferInfo2KHR";
        case(StructureType::BlitImageInfo2KHR): return "BlitImageInfo2KHR";
        case(StructureType::ResolveImageInfo2KHR): return "ResolveImageInfo2KHR";
        case(StructureType::BufferCopy2KHR): return "BufferCopy2KHR";
        case(StructureType::ImageCopy2KHR): return "ImageCopy2KHR";
        case(StructureType::ImageBlit2KHR): return "ImageBlit2KHR";
        case(StructureType::BufferImageCopy2KHR): return "BufferImageCopy2KHR";
        case(StructureType::ImageResolve2KHR): return "ImageResolve2KHR";
        case(StructureType::PhysicalDevice4444FormatsFeaturesEXT): return "PhysicalDevice4444FormatsFeaturesEXT";
        case(StructureType::DirectfbSurfaceCreateInfoEXT): return "DirectfbSurfaceCreateInfoEXT";
        case(StructureType::PhysicalDeviceSubgroupProperties): return "PhysicalDeviceSubgroupProperties";
        case(StructureType::BindBufferMemoryInfo): return "BindBufferMemoryInfo";
        case(StructureType::BindImageMemoryInfo): return "BindImageMemoryInfo";
        case(StructureType::PhysicalDevice16BitStorageFeatures): return "PhysicalDevice16BitStorageFeatures";
        case(StructureType::MemoryDedicatedRequirements): return "MemoryDedicatedRequirements";
        case(StructureType::MemoryDedicatedAllocateInfo): return "MemoryDedicatedAllocateInfo";
        case(StructureType::MemoryAllocateFlagsInfo): return "MemoryAllocateFlagsInfo";
        case(StructureType::DeviceGroupRenderPassBeginInfo): return "DeviceGroupRenderPassBeginInfo";
        case(StructureType::DeviceGroupCommandBufferBeginInfo): return "DeviceGroupCommandBufferBeginInfo";
        case(StructureType::DeviceGroupSubmitInfo): return "DeviceGroupSubmitInfo";
        case(StructureType::DeviceGroupBindSparseInfo): return "DeviceGroupBindSparseInfo";
        case(StructureType::BindBufferMemoryDeviceGroupInfo): return "BindBufferMemoryDeviceGroupInfo";
        case(StructureType::BindImageMemoryDeviceGroupInfo): return "BindImageMemoryDeviceGroupInfo";
        case(StructureType::PhysicalDeviceGroupProperties): return "PhysicalDeviceGroupProperties";
        case(StructureType::DeviceGroupDeviceCreateInfo): return "DeviceGroupDeviceCreateInfo";
        case(StructureType::BufferMemoryRequirementsInfo2): return "BufferMemoryRequirementsInfo2";
        case(StructureType::ImageMemoryRequirementsInfo2): return "ImageMemoryRequirementsInfo2";
        case(StructureType::ImageSparseMemoryRequirementsInfo2): return "ImageSparseMemoryRequirementsInfo2";
        case(StructureType::MemoryRequirements2): return "MemoryRequirements2";
        case(StructureType::SparseImageMemoryRequirements2): return "SparseImageMemoryRequirements2";
        case(StructureType::PhysicalDeviceFeatures2): return "PhysicalDeviceFeatures2";
        case(StructureType::PhysicalDeviceProperties2): return "PhysicalDeviceProperties2";
        case(StructureType::FormatProperties2): return "FormatProperties2";
        case(StructureType::ImageFormatProperties2): return "ImageFormatProperties2";
        case(StructureType::PhysicalDeviceImageFormatInfo2): return "PhysicalDeviceImageFormatInfo2";
        case(StructureType::QueueFamilyProperties2): return "QueueFamilyProperties2";
        case(StructureType::PhysicalDeviceMemoryProperties2): return "PhysicalDeviceMemoryProperties2";
        case(StructureType::SparseImageFormatProperties2): return "SparseImageFormatProperties2";
        case(StructureType::PhysicalDeviceSparseImageFormatInfo2): return "PhysicalDeviceSparseImageFormatInfo2";
        case(StructureType::PhysicalDevicePointClippingProperties): return "PhysicalDevicePointClippingProperties";
        case(StructureType::RenderPassInputAttachmentAspectCreateInfo): return "RenderPassInputAttachmentAspectCreateInfo";
        case(StructureType::ImageViewUsageCreateInfo): return "ImageViewUsageCreateInfo";
        case(StructureType::PipelineTessellationDomainOriginStateCreateInfo): return "PipelineTessellationDomainOriginStateCreateInfo";
        case(StructureType::RenderPassMultiviewCreateInfo): return "RenderPassMultiviewCreateInfo";
        case(StructureType::PhysicalDeviceMultiviewFeatures): return "PhysicalDeviceMultiviewFeatures";
        case(StructureType::PhysicalDeviceMultiviewProperties): return "PhysicalDeviceMultiviewProperties";
        case(StructureType::PhysicalDeviceVariablePointersFeatures): return "PhysicalDeviceVariablePointersFeatures";
        case(StructureType::ProtectedSubmitInfo): return "ProtectedSubmitInfo";
        case(StructureType::PhysicalDeviceProtectedMemoryFeatures): return "PhysicalDeviceProtectedMemoryFeatures";
        case(StructureType::PhysicalDeviceProtectedMemoryProperties): return "PhysicalDeviceProtectedMemoryProperties";
        case(StructureType::DeviceQueueInfo2): return "DeviceQueueInfo2";
        case(StructureType::SamplerYcbcrConversionCreateInfo): return "SamplerYcbcrConversionCreateInfo";
        case(StructureType::SamplerYcbcrConversionInfo): return "SamplerYcbcrConversionInfo";
        case(StructureType::BindImagePlaneMemoryInfo): return "BindImagePlaneMemoryInfo";
        case(StructureType::ImagePlaneMemoryRequirementsInfo): return "ImagePlaneMemoryRequirementsInfo";
        case(StructureType::PhysicalDeviceSamplerYcbcrConversionFeatures): return "PhysicalDeviceSamplerYcbcrConversionFeatures";
        case(StructureType::SamplerYcbcrConversionImageFormatProperties): return "SamplerYcbcrConversionImageFormatProperties";
        case(StructureType::DescriptorUpdateTemplateCreateInfo): return "DescriptorUpdateTemplateCreateInfo";
        case(StructureType::PhysicalDeviceExternalImageFormatInfo): return "PhysicalDeviceExternalImageFormatInfo";
        case(StructureType::ExternalImageFormatProperties): return "ExternalImageFormatProperties";
        case(StructureType::PhysicalDeviceExternalBufferInfo): return "PhysicalDeviceExternalBufferInfo";
        case(StructureType::ExternalBufferProperties): return "ExternalBufferProperties";
        case(StructureType::PhysicalDeviceIdProperties): return "PhysicalDeviceIdProperties";
        case(StructureType::ExternalMemoryBufferCreateInfo): return "ExternalMemoryBufferCreateInfo";
        case(StructureType::ExternalMemoryImageCreateInfo): return "ExternalMemoryImageCreateInfo";
        case(StructureType::ExportMemoryAllocateInfo): return "ExportMemoryAllocateInfo";
        case(StructureType::PhysicalDeviceExternalFenceInfo): return "PhysicalDeviceExternalFenceInfo";
        case(StructureType::ExternalFenceProperties): return "ExternalFenceProperties";
        case(StructureType::ExportFenceCreateInfo): return "ExportFenceCreateInfo";
        case(StructureType::ExportSemaphoreCreateInfo): return "ExportSemaphoreCreateInfo";
        case(StructureType::PhysicalDeviceExternalSemaphoreInfo): return "PhysicalDeviceExternalSemaphoreInfo";
        case(StructureType::ExternalSemaphoreProperties): return "ExternalSemaphoreProperties";
        case(StructureType::PhysicalDeviceMaintenance3Properties): return "PhysicalDeviceMaintenance3Properties";
        case(StructureType::DescriptorSetLayoutSupport): return "DescriptorSetLayoutSupport";
        case(StructureType::PhysicalDeviceShaderDrawParametersFeatures): return "PhysicalDeviceShaderDrawParametersFeatures";
        case(StructureType::PhysicalDeviceVulkan11Features): return "PhysicalDeviceVulkan11Features";
        case(StructureType::PhysicalDeviceVulkan11Properties): return "PhysicalDeviceVulkan11Properties";
        case(StructureType::PhysicalDeviceVulkan12Features): return "PhysicalDeviceVulkan12Features";
        case(StructureType::PhysicalDeviceVulkan12Properties): return "PhysicalDeviceVulkan12Properties";
        case(StructureType::ImageFormatListCreateInfo): return "ImageFormatListCreateInfo";
        case(StructureType::AttachmentDescription2): return "AttachmentDescription2";
        case(StructureType::AttachmentReference2): return "AttachmentReference2";
        case(StructureType::SubpassDescription2): return "SubpassDescription2";
        case(StructureType::SubpassDependency2): return "SubpassDependency2";
        case(StructureType::RenderPassCreateInfo2): return "RenderPassCreateInfo2";
        case(StructureType::SubpassBeginInfo): return "SubpassBeginInfo";
        case(StructureType::SubpassEndInfo): return "SubpassEndInfo";
        case(StructureType::PhysicalDevice8BitStorageFeatures): return "PhysicalDevice8BitStorageFeatures";
        case(StructureType::PhysicalDeviceDriverProperties): return "PhysicalDeviceDriverProperties";
        case(StructureType::PhysicalDeviceShaderAtomicInt64Features): return "PhysicalDeviceShaderAtomicInt64Features";
        case(StructureType::PhysicalDeviceShaderFloat16Int8Features): return "PhysicalDeviceShaderFloat16Int8Features";
        case(StructureType::PhysicalDeviceFloatControlsProperties): return "PhysicalDeviceFloatControlsProperties";
        case(StructureType::DescriptorSetLayoutBindingFlagsCreateInfo): return "DescriptorSetLayoutBindingFlagsCreateInfo";
        case(StructureType::PhysicalDeviceDescriptorIndexingFeatures): return "PhysicalDeviceDescriptorIndexingFeatures";
        case(StructureType::PhysicalDeviceDescriptorIndexingProperties): return "PhysicalDeviceDescriptorIndexingProperties";
        case(StructureType::DescriptorSetVariableDescriptorCountAllocateInfo): return "DescriptorSetVariableDescriptorCountAllocateInfo";
        case(StructureType::DescriptorSetVariableDescriptorCountLayoutSupport): return "DescriptorSetVariableDescriptorCountLayoutSupport";
        case(StructureType::PhysicalDeviceDepthStencilResolveProperties): return "PhysicalDeviceDepthStencilResolveProperties";
        case(StructureType::SubpassDescriptionDepthStencilResolve): return "SubpassDescriptionDepthStencilResolve";
        case(StructureType::PhysicalDeviceScalarBlockLayoutFeatures): return "PhysicalDeviceScalarBlockLayoutFeatures";
        case(StructureType::ImageStencilUsageCreateInfo): return "ImageStencilUsageCreateInfo";
        case(StructureType::PhysicalDeviceSamplerFilterMinmaxProperties): return "PhysicalDeviceSamplerFilterMinmaxProperties";
        case(StructureType::SamplerReductionModeCreateInfo): return "SamplerReductionModeCreateInfo";
        case(StructureType::PhysicalDeviceVulkanMemoryModelFeatures): return "PhysicalDeviceVulkanMemoryModelFeatures";
        case(StructureType::PhysicalDeviceImagelessFramebufferFeatures): return "PhysicalDeviceImagelessFramebufferFeatures";
        case(StructureType::FramebufferAttachmentsCreateInfo): return "FramebufferAttachmentsCreateInfo";
        case(StructureType::FramebufferAttachmentImageInfo): return "FramebufferAttachmentImageInfo";
        case(StructureType::RenderPassAttachmentBeginInfo): return "RenderPassAttachmentBeginInfo";
        case(StructureType::PhysicalDeviceUniformBufferStandardLayoutFeatures): return "PhysicalDeviceUniformBufferStandardLayoutFeatures";
        case(StructureType::PhysicalDeviceShaderSubgroupExtendedTypesFeatures): return "PhysicalDeviceShaderSubgroupExtendedTypesFeatures";
        case(StructureType::PhysicalDeviceSeparateDepthStencilLayoutsFeatures): return "PhysicalDeviceSeparateDepthStencilLayoutsFeatures";
        case(StructureType::AttachmentReferenceStencilLayout): return "AttachmentReferenceStencilLayout";
        case(StructureType::AttachmentDescriptionStencilLayout): return "AttachmentDescriptionStencilLayout";
        case(StructureType::PhysicalDeviceHostQueryResetFeatures): return "PhysicalDeviceHostQueryResetFeatures";
        case(StructureType::PhysicalDeviceTimelineSemaphoreFeatures): return "PhysicalDeviceTimelineSemaphoreFeatures";
        case(StructureType::PhysicalDeviceTimelineSemaphoreProperties): return "PhysicalDeviceTimelineSemaphoreProperties";
        case(StructureType::SemaphoreTypeCreateInfo): return "SemaphoreTypeCreateInfo";
        case(StructureType::TimelineSemaphoreSubmitInfo): return "TimelineSemaphoreSubmitInfo";
        case(StructureType::SemaphoreWaitInfo): return "SemaphoreWaitInfo";
        case(StructureType::SemaphoreSignalInfo): return "SemaphoreSignalInfo";
        case(StructureType::PhysicalDeviceBufferDeviceAddressFeatures): return "PhysicalDeviceBufferDeviceAddressFeatures";
        case(StructureType::BufferDeviceAddressInfo): return "BufferDeviceAddressInfo";
        case(StructureType::BufferOpaqueCaptureAddressCreateInfo): return "BufferOpaqueCaptureAddressCreateInfo";
        case(StructureType::MemoryOpaqueCaptureAddressAllocateInfo): return "MemoryOpaqueCaptureAddressAllocateInfo";
        case(StructureType::DeviceMemoryOpaqueCaptureAddressInfo): return "DeviceMemoryOpaqueCaptureAddressInfo";
        default: return "UNKNOWN";
    }
}
const char * to_string(SystemAllocationScope val) {
    switch(val) {
        case(SystemAllocationScope::Command): return "Command";
        case(SystemAllocationScope::Object): return "Object";
        case(SystemAllocationScope::Cache): return "Cache";
        case(SystemAllocationScope::Device): return "Device";
        case(SystemAllocationScope::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
const char * to_string(InternalAllocationType val) {
    switch(val) {
        case(InternalAllocationType::Executable): return "Executable";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerAddressMode val) {
    switch(val) {
        case(SamplerAddressMode::Repeat): return "Repeat";
        case(SamplerAddressMode::MirroredRepeat): return "MirroredRepeat";
        case(SamplerAddressMode::ClampToEdge): return "ClampToEdge";
        case(SamplerAddressMode::ClampToBorder): return "ClampToBorder";
        case(SamplerAddressMode::MirrorClampToEdge): return "MirrorClampToEdge";
        default: return "UNKNOWN";
    }
}
const char * to_string(Filter val) {
    switch(val) {
        case(Filter::Nearest): return "Nearest";
        case(Filter::Linear): return "Linear";
        case(Filter::CubicIMG): return "CubicIMG";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerMipmapMode val) {
    switch(val) {
        case(SamplerMipmapMode::Nearest): return "Nearest";
        case(SamplerMipmapMode::Linear): return "Linear";
        default: return "UNKNOWN";
    }
}
const char * to_string(VertexInputRate val) {
    switch(val) {
        case(VertexInputRate::Vertex): return "Vertex";
        case(VertexInputRate::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
const char * to_string(ObjectType val) {
    switch(val) {
        case(ObjectType::Unknown): return "Unknown";
        case(ObjectType::Instance): return "Instance";
        case(ObjectType::PhysicalDevice): return "PhysicalDevice";
        case(ObjectType::Device): return "Device";
        case(ObjectType::Queue): return "Queue";
        case(ObjectType::Semaphore): return "Semaphore";
        case(ObjectType::CommandBuffer): return "CommandBuffer";
        case(ObjectType::Fence): return "Fence";
        case(ObjectType::DeviceMemory): return "DeviceMemory";
        case(ObjectType::Buffer): return "Buffer";
        case(ObjectType::Image): return "Image";
        case(ObjectType::Event): return "Event";
        case(ObjectType::QueryPool): return "QueryPool";
        case(ObjectType::BufferView): return "BufferView";
        case(ObjectType::ImageView): return "ImageView";
        case(ObjectType::ShaderModule): return "ShaderModule";
        case(ObjectType::PipelineCache): return "PipelineCache";
        case(ObjectType::PipelineLayout): return "PipelineLayout";
        case(ObjectType::RenderPass): return "RenderPass";
        case(ObjectType::Pipeline): return "Pipeline";
        case(ObjectType::DescriptorSetLayout): return "DescriptorSetLayout";
        case(ObjectType::Sampler): return "Sampler";
        case(ObjectType::DescriptorPool): return "DescriptorPool";
        case(ObjectType::DescriptorSet): return "DescriptorSet";
        case(ObjectType::Framebuffer): return "Framebuffer";
        case(ObjectType::CommandPool): return "CommandPool";
        case(ObjectType::SurfaceKHR): return "SurfaceKHR";
        case(ObjectType::SwapchainKHR): return "SwapchainKHR";
        case(ObjectType::DisplayKHR): return "DisplayKHR";
        case(ObjectType::DisplayModeKHR): return "DisplayModeKHR";
        case(ObjectType::DebugReportCallbackEXT): return "DebugReportCallbackEXT";
        case(ObjectType::DebugUtilsMessengerEXT): return "DebugUtilsMessengerEXT";
        case(ObjectType::AccelerationStructureKHR): return "AccelerationStructureKHR";
        case(ObjectType::ValidationCacheEXT): return "ValidationCacheEXT";
        case(ObjectType::PerformanceConfigurationINTEL): return "PerformanceConfigurationINTEL";
        case(ObjectType::DeferredOperationKHR): return "DeferredOperationKHR";
        case(ObjectType::IndirectCommandsLayoutNV): return "IndirectCommandsLayoutNV";
        case(ObjectType::PrivateDataSlotEXT): return "PrivateDataSlotEXT";
        case(ObjectType::SamplerYcbcrConversion): return "SamplerYcbcrConversion";
        case(ObjectType::DescriptorUpdateTemplate): return "DescriptorUpdateTemplate";
        default: return "UNKNOWN";
    }
}
const char * to_string(IndirectCommandsTokenTypeNV val) {
    switch(val) {
        case(IndirectCommandsTokenTypeNV::ShaderGroupNV): return "ShaderGroupNV";
        case(IndirectCommandsTokenTypeNV::StateFlagsNV): return "StateFlagsNV";
        case(IndirectCommandsTokenTypeNV::IndexBufferNV): return "IndexBufferNV";
        case(IndirectCommandsTokenTypeNV::VertexBufferNV): return "VertexBufferNV";
        case(IndirectCommandsTokenTypeNV::PushConstantNV): return "PushConstantNV";
        case(IndirectCommandsTokenTypeNV::DrawIndexedNV): return "DrawIndexedNV";
        case(IndirectCommandsTokenTypeNV::DrawNV): return "DrawNV";
        case(IndirectCommandsTokenTypeNV::DrawTasksNV): return "DrawTasksNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(DescriptorUpdateTemplateType val) {
    switch(val) {
        case(DescriptorUpdateTemplateType::DescriptorSet): return "DescriptorSet";
        case(DescriptorUpdateTemplateType::PushDescriptorsKHR): return "PushDescriptorsKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(ViewportCoordinateSwizzleNV val) {
    switch(val) {
        case(ViewportCoordinateSwizzleNV::PositiveXNV): return "PositiveXNV";
        case(ViewportCoordinateSwizzleNV::NegativeXNV): return "NegativeXNV";
        case(ViewportCoordinateSwizzleNV::PositiveYNV): return "PositiveYNV";
        case(ViewportCoordinateSwizzleNV::NegativeYNV): return "NegativeYNV";
        case(ViewportCoordinateSwizzleNV::PositiveZNV): return "PositiveZNV";
        case(ViewportCoordinateSwizzleNV::NegativeZNV): return "NegativeZNV";
        case(ViewportCoordinateSwizzleNV::PositiveWNV): return "PositiveWNV";
        case(ViewportCoordinateSwizzleNV::NegativeWNV): return "NegativeWNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(DiscardRectangleModeEXT val) {
    switch(val) {
        case(DiscardRectangleModeEXT::InclusiveEXT): return "InclusiveEXT";
        case(DiscardRectangleModeEXT::ExclusiveEXT): return "ExclusiveEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(PointClippingBehavior val) {
    switch(val) {
        case(PointClippingBehavior::AllClipPlanes): return "AllClipPlanes";
        case(PointClippingBehavior::UserClipPlanesOnly): return "UserClipPlanesOnly";
        default: return "UNKNOWN";
    }
}
const char * to_string(CoverageModulationModeNV val) {
    switch(val) {
        case(CoverageModulationModeNV::NoneNV): return "NoneNV";
        case(CoverageModulationModeNV::RgbNV): return "RgbNV";
        case(CoverageModulationModeNV::AlphaNV): return "AlphaNV";
        case(CoverageModulationModeNV::RgbaNV): return "RgbaNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(CoverageReductionModeNV val) {
    switch(val) {
        case(CoverageReductionModeNV::MergeNV): return "MergeNV";
        case(CoverageReductionModeNV::TruncateNV): return "TruncateNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationCacheHeaderVersionEXT val) {
    switch(val) {
        case(ValidationCacheHeaderVersionEXT::OneEXT): return "OneEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ShaderInfoTypeAMD val) {
    switch(val) {
        case(ShaderInfoTypeAMD::StatisticsAMD): return "StatisticsAMD";
        case(ShaderInfoTypeAMD::BinaryAMD): return "BinaryAMD";
        case(ShaderInfoTypeAMD::DisassemblyAMD): return "DisassemblyAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueueGlobalPriorityEXT val) {
    switch(val) {
        case(QueueGlobalPriorityEXT::LowEXT): return "LowEXT";
        case(QueueGlobalPriorityEXT::MediumEXT): return "MediumEXT";
        case(QueueGlobalPriorityEXT::HighEXT): return "HighEXT";
        case(QueueGlobalPriorityEXT::RealtimeEXT): return "RealtimeEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(TimeDomainEXT val) {
    switch(val) {
        case(TimeDomainEXT::DeviceEXT): return "DeviceEXT";
        case(TimeDomainEXT::ClockMonotonicEXT): return "ClockMonotonicEXT";
        case(TimeDomainEXT::ClockMonotonicRawEXT): return "ClockMonotonicRawEXT";
        case(TimeDomainEXT::QueryPerformanceCounterEXT): return "QueryPerformanceCounterEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ConservativeRasterizationModeEXT val) {
    switch(val) {
        case(ConservativeRasterizationModeEXT::DisabledEXT): return "DisabledEXT";
        case(ConservativeRasterizationModeEXT::OverestimateEXT): return "OverestimateEXT";
        case(ConservativeRasterizationModeEXT::UnderestimateEXT): return "UnderestimateEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(SemaphoreType val) {
    switch(val) {
        case(SemaphoreType::Binary): return "Binary";
        case(SemaphoreType::Timeline): return "Timeline";
        default: return "UNKNOWN";
    }
}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(CopyAccelerationStructureModeKHR val) {
    switch(val) {
        case(CopyAccelerationStructureModeKHR::CloneKHR): return "CloneKHR";
        case(CopyAccelerationStructureModeKHR::CompactKHR): return "CompactKHR";
        case(CopyAccelerationStructureModeKHR::SerializeKHR): return "SerializeKHR";
        case(CopyAccelerationStructureModeKHR::DeserializeKHR): return "DeserializeKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureTypeKHR val) {
    switch(val) {
        case(AccelerationStructureTypeKHR::TopLevelKHR): return "TopLevelKHR";
        case(AccelerationStructureTypeKHR::BottomLevelKHR): return "BottomLevelKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryTypeKHR val) {
    switch(val) {
        case(GeometryTypeKHR::TrianglesKHR): return "TrianglesKHR";
        case(GeometryTypeKHR::AabbsKHR): return "AabbsKHR";
        case(GeometryTypeKHR::InstancesKHR): return "InstancesKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(RayTracingShaderGroupTypeKHR val) {
    switch(val) {
        case(RayTracingShaderGroupTypeKHR::GeneralKHR): return "GeneralKHR";
        case(RayTracingShaderGroupTypeKHR::TrianglesHitGroupKHR): return "TrianglesHitGroupKHR";
        case(RayTracingShaderGroupTypeKHR::ProceduralHitGroupKHR): return "ProceduralHitGroupKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureMemoryRequirementsTypeKHR val) {
    switch(val) {
        case(AccelerationStructureMemoryRequirementsTypeKHR::ObjectKHR): return "ObjectKHR";
        case(AccelerationStructureMemoryRequirementsTypeKHR::BuildScratchKHR): return "BuildScratchKHR";
        case(AccelerationStructureMemoryRequirementsTypeKHR::UpdateScratchKHR): return "UpdateScratchKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(AccelerationStructureBuildTypeKHR val) {
    switch(val) {
        case(AccelerationStructureBuildTypeKHR::HostKHR): return "HostKHR";
        case(AccelerationStructureBuildTypeKHR::DeviceKHR): return "DeviceKHR";
        case(AccelerationStructureBuildTypeKHR::HostOrDeviceKHR): return "HostOrDeviceKHR";
        default: return "UNKNOWN";
    }
}
#endif // VK_ENABLE_BETA_EXTENSIONS
const char * to_string(MemoryOverallocationBehaviorAMD val) {
    switch(val) {
        case(MemoryOverallocationBehaviorAMD::DefaultAMD): return "DefaultAMD";
        case(MemoryOverallocationBehaviorAMD::AllowedAMD): return "AllowedAMD";
        case(MemoryOverallocationBehaviorAMD::DisallowedAMD): return "DisallowedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(ScopeNV val) {
    switch(val) {
        case(ScopeNV::DeviceNV): return "DeviceNV";
        case(ScopeNV::WorkgroupNV): return "WorkgroupNV";
        case(ScopeNV::SubgroupNV): return "SubgroupNV";
        case(ScopeNV::QueueFamilyNV): return "QueueFamilyNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(ComponentTypeNV val) {
    switch(val) {
        case(ComponentTypeNV::Float16NV): return "Float16NV";
        case(ComponentTypeNV::Float32NV): return "Float32NV";
        case(ComponentTypeNV::Float64NV): return "Float64NV";
        case(ComponentTypeNV::Sint8NV): return "Sint8NV";
        case(ComponentTypeNV::Sint16NV): return "Sint16NV";
        case(ComponentTypeNV::Sint32NV): return "Sint32NV";
        case(ComponentTypeNV::Sint64NV): return "Sint64NV";
        case(ComponentTypeNV::Uint8NV): return "Uint8NV";
        case(ComponentTypeNV::Uint16NV): return "Uint16NV";
        case(ComponentTypeNV::Uint32NV): return "Uint32NV";
        case(ComponentTypeNV::Uint64NV): return "Uint64NV";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterScopeKHR val) {
    switch(val) {
        case(PerformanceCounterScopeKHR::CommandBufferKHR): return "CommandBufferKHR";
        case(PerformanceCounterScopeKHR::RenderPassKHR): return "RenderPassKHR";
        case(PerformanceCounterScopeKHR::CommandKHR): return "CommandKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterUnitKHR val) {
    switch(val) {
        case(PerformanceCounterUnitKHR::GenericKHR): return "GenericKHR";
        case(PerformanceCounterUnitKHR::PercentageKHR): return "PercentageKHR";
        case(PerformanceCounterUnitKHR::NanosecondsKHR): return "NanosecondsKHR";
        case(PerformanceCounterUnitKHR::BytesKHR): return "BytesKHR";
        case(PerformanceCounterUnitKHR::BytesPerSecondKHR): return "BytesPerSecondKHR";
        case(PerformanceCounterUnitKHR::KelvinKHR): return "KelvinKHR";
        case(PerformanceCounterUnitKHR::WattsKHR): return "WattsKHR";
        case(PerformanceCounterUnitKHR::VoltsKHR): return "VoltsKHR";
        case(PerformanceCounterUnitKHR::AmpsKHR): return "AmpsKHR";
        case(PerformanceCounterUnitKHR::HertzKHR): return "HertzKHR";
        case(PerformanceCounterUnitKHR::CyclesKHR): return "CyclesKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceCounterStorageKHR val) {
    switch(val) {
        case(PerformanceCounterStorageKHR::Int32KHR): return "Int32KHR";
        case(PerformanceCounterStorageKHR::Int64KHR): return "Int64KHR";
        case(PerformanceCounterStorageKHR::Uint32KHR): return "Uint32KHR";
        case(PerformanceCounterStorageKHR::Uint64KHR): return "Uint64KHR";
        case(PerformanceCounterStorageKHR::Float32KHR): return "Float32KHR";
        case(PerformanceCounterStorageKHR::Float64KHR): return "Float64KHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceConfigurationTypeINTEL val) {
    switch(val) {
        case(PerformanceConfigurationTypeINTEL::CommandQueueMetricsDiscoveryActivatedINTEL): return "CommandQueueMetricsDiscoveryActivatedINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(QueryPoolSamplingModeINTEL val) {
    switch(val) {
        case(QueryPoolSamplingModeINTEL::ManualINTEL): return "ManualINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceOverrideTypeINTEL val) {
    switch(val) {
        case(PerformanceOverrideTypeINTEL::NullHardwareINTEL): return "NullHardwareINTEL";
        case(PerformanceOverrideTypeINTEL::FlushGpuCachesINTEL): return "FlushGpuCachesINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceParameterTypeINTEL val) {
    switch(val) {
        case(PerformanceParameterTypeINTEL::HwCountersSupportedINTEL): return "HwCountersSupportedINTEL";
        case(PerformanceParameterTypeINTEL::StreamMarkerValidBitsINTEL): return "StreamMarkerValidBitsINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(PerformanceValueTypeINTEL val) {
    switch(val) {
        case(PerformanceValueTypeINTEL::Uint32INTEL): return "Uint32INTEL";
        case(PerformanceValueTypeINTEL::Uint64INTEL): return "Uint64INTEL";
        case(PerformanceValueTypeINTEL::FloatINTEL): return "FloatINTEL";
        case(PerformanceValueTypeINTEL::BoolINTEL): return "BoolINTEL";
        case(PerformanceValueTypeINTEL::StringINTEL): return "StringINTEL";
        default: return "UNKNOWN";
    }
}
const char * to_string(LineRasterizationModeEXT val) {
    switch(val) {
        case(LineRasterizationModeEXT::DefaultEXT): return "DefaultEXT";
        case(LineRasterizationModeEXT::RectangularEXT): return "RectangularEXT";
        case(LineRasterizationModeEXT::BresenhamEXT): return "BresenhamEXT";
        case(LineRasterizationModeEXT::RectangularSmoothEXT): return "RectangularSmoothEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ColorSpaceKHR val) {
    switch(val) {
        case(ColorSpaceKHR::SrgbNonlinearKHR): return "SrgbNonlinearKHR";
        case(ColorSpaceKHR::DisplayP3NonlinearEXT): return "DisplayP3NonlinearEXT";
        case(ColorSpaceKHR::ExtendedSrgbLinearEXT): return "ExtendedSrgbLinearEXT";
        case(ColorSpaceKHR::DisplayP3LinearEXT): return "DisplayP3LinearEXT";
        case(ColorSpaceKHR::DciP3NonlinearEXT): return "DciP3NonlinearEXT";
        case(ColorSpaceKHR::Bt709LinearEXT): return "Bt709LinearEXT";
        case(ColorSpaceKHR::Bt709NonlinearEXT): return "Bt709NonlinearEXT";
        case(ColorSpaceKHR::Bt2020LinearEXT): return "Bt2020LinearEXT";
        case(ColorSpaceKHR::Hdr10St2084EXT): return "Hdr10St2084EXT";
        case(ColorSpaceKHR::DolbyvisionEXT): return "DolbyvisionEXT";
        case(ColorSpaceKHR::Hdr10HlgEXT): return "Hdr10HlgEXT";
        case(ColorSpaceKHR::AdobergbLinearEXT): return "AdobergbLinearEXT";
        case(ColorSpaceKHR::AdobergbNonlinearEXT): return "AdobergbNonlinearEXT";
        case(ColorSpaceKHR::PassThroughEXT): return "PassThroughEXT";
        case(ColorSpaceKHR::ExtendedSrgbNonlinearEXT): return "ExtendedSrgbNonlinearEXT";
        case(ColorSpaceKHR::DisplayNativeAMD): return "DisplayNativeAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(PresentModeKHR val) {
    switch(val) {
        case(PresentModeKHR::ImmediateKHR): return "ImmediateKHR";
        case(PresentModeKHR::MailboxKHR): return "MailboxKHR";
        case(PresentModeKHR::FifoKHR): return "FifoKHR";
        case(PresentModeKHR::FifoRelaxedKHR): return "FifoRelaxedKHR";
        case(PresentModeKHR::SharedDemandRefreshKHR): return "SharedDemandRefreshKHR";
        case(PresentModeKHR::SharedContinuousRefreshKHR): return "SharedContinuousRefreshKHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(DebugReportObjectTypeEXT val) {
    switch(val) {
        case(DebugReportObjectTypeEXT::UnknownEXT): return "UnknownEXT";
        case(DebugReportObjectTypeEXT::InstanceEXT): return "InstanceEXT";
        case(DebugReportObjectTypeEXT::PhysicalDeviceEXT): return "PhysicalDeviceEXT";
        case(DebugReportObjectTypeEXT::DeviceEXT): return "DeviceEXT";
        case(DebugReportObjectTypeEXT::QueueEXT): return "QueueEXT";
        case(DebugReportObjectTypeEXT::SemaphoreEXT): return "SemaphoreEXT";
        case(DebugReportObjectTypeEXT::CommandBufferEXT): return "CommandBufferEXT";
        case(DebugReportObjectTypeEXT::FenceEXT): return "FenceEXT";
        case(DebugReportObjectTypeEXT::DeviceMemoryEXT): return "DeviceMemoryEXT";
        case(DebugReportObjectTypeEXT::BufferEXT): return "BufferEXT";
        case(DebugReportObjectTypeEXT::ImageEXT): return "ImageEXT";
        case(DebugReportObjectTypeEXT::EventEXT): return "EventEXT";
        case(DebugReportObjectTypeEXT::QueryPoolEXT): return "QueryPoolEXT";
        case(DebugReportObjectTypeEXT::BufferViewEXT): return "BufferViewEXT";
        case(DebugReportObjectTypeEXT::ImageViewEXT): return "ImageViewEXT";
        case(DebugReportObjectTypeEXT::ShaderModuleEXT): return "ShaderModuleEXT";
        case(DebugReportObjectTypeEXT::PipelineCacheEXT): return "PipelineCacheEXT";
        case(DebugReportObjectTypeEXT::PipelineLayoutEXT): return "PipelineLayoutEXT";
        case(DebugReportObjectTypeEXT::RenderPassEXT): return "RenderPassEXT";
        case(DebugReportObjectTypeEXT::PipelineEXT): return "PipelineEXT";
        case(DebugReportObjectTypeEXT::DescriptorSetLayoutEXT): return "DescriptorSetLayoutEXT";
        case(DebugReportObjectTypeEXT::SamplerEXT): return "SamplerEXT";
        case(DebugReportObjectTypeEXT::DescriptorPoolEXT): return "DescriptorPoolEXT";
        case(DebugReportObjectTypeEXT::DescriptorSetEXT): return "DescriptorSetEXT";
        case(DebugReportObjectTypeEXT::FramebufferEXT): return "FramebufferEXT";
        case(DebugReportObjectTypeEXT::CommandPoolEXT): return "CommandPoolEXT";
        case(DebugReportObjectTypeEXT::SurfaceKhrEXT): return "SurfaceKhrEXT";
        case(DebugReportObjectTypeEXT::SwapchainKhrEXT): return "SwapchainKhrEXT";
        case(DebugReportObjectTypeEXT::DebugReportCallbackExtEXT): return "DebugReportCallbackExtEXT";
        case(DebugReportObjectTypeEXT::DisplayKhrEXT): return "DisplayKhrEXT";
        case(DebugReportObjectTypeEXT::DisplayModeKhrEXT): return "DisplayModeKhrEXT";
        case(DebugReportObjectTypeEXT::ValidationCacheExtEXT): return "ValidationCacheExtEXT";
        case(DebugReportObjectTypeEXT::SamplerYcbcrConversionEXT): return "SamplerYcbcrConversionEXT";
        case(DebugReportObjectTypeEXT::DescriptorUpdateTemplateEXT): return "DescriptorUpdateTemplateEXT";
        case(DebugReportObjectTypeEXT::AccelerationStructureKhrEXT): return "AccelerationStructureKhrEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DeviceMemoryReportEventTypeEXT val) {
    switch(val) {
        case(DeviceMemoryReportEventTypeEXT::AllocateEXT): return "AllocateEXT";
        case(DeviceMemoryReportEventTypeEXT::FreeEXT): return "FreeEXT";
        case(DeviceMemoryReportEventTypeEXT::ImportEXT): return "ImportEXT";
        case(DeviceMemoryReportEventTypeEXT::UnimportEXT): return "UnimportEXT";
        case(DeviceMemoryReportEventTypeEXT::AllocationFailedEXT): return "AllocationFailedEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(RasterizationOrderAMD val) {
    switch(val) {
        case(RasterizationOrderAMD::StrictAMD): return "StrictAMD";
        case(RasterizationOrderAMD::RelaxedAMD): return "RelaxedAMD";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationCheckEXT val) {
    switch(val) {
        case(ValidationCheckEXT::AllEXT): return "AllEXT";
        case(ValidationCheckEXT::ShadersEXT): return "ShadersEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationFeatureEnableEXT val) {
    switch(val) {
        case(ValidationFeatureEnableEXT::GpuAssistedEXT): return "GpuAssistedEXT";
        case(ValidationFeatureEnableEXT::GpuAssistedReserveBindingSlotEXT): return "GpuAssistedReserveBindingSlotEXT";
        case(ValidationFeatureEnableEXT::BestPracticesEXT): return "BestPracticesEXT";
        case(ValidationFeatureEnableEXT::DebugPrintfEXT): return "DebugPrintfEXT";
        case(ValidationFeatureEnableEXT::SynchronizationValidationEXT): return "SynchronizationValidationEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(ValidationFeatureDisableEXT val) {
    switch(val) {
        case(ValidationFeatureDisableEXT::AllEXT): return "AllEXT";
        case(ValidationFeatureDisableEXT::ShadersEXT): return "ShadersEXT";
        case(ValidationFeatureDisableEXT::ThreadSafetyEXT): return "ThreadSafetyEXT";
        case(ValidationFeatureDisableEXT::ApiParametersEXT): return "ApiParametersEXT";
        case(ValidationFeatureDisableEXT::ObjectLifetimesEXT): return "ObjectLifetimesEXT";
        case(ValidationFeatureDisableEXT::CoreChecksEXT): return "CoreChecksEXT";
        case(ValidationFeatureDisableEXT::UniqueHandlesEXT): return "UniqueHandlesEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DisplayPowerStateEXT val) {
    switch(val) {
        case(DisplayPowerStateEXT::OffEXT): return "OffEXT";
        case(DisplayPowerStateEXT::SuspendEXT): return "SuspendEXT";
        case(DisplayPowerStateEXT::OnEXT): return "OnEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DeviceEventTypeEXT val) {
    switch(val) {
        case(DeviceEventTypeEXT::DisplayHotplugEXT): return "DisplayHotplugEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(DisplayEventTypeEXT val) {
    switch(val) {
        case(DisplayEventTypeEXT::FirstPixelOutEXT): return "FirstPixelOutEXT";
        default: return "UNKNOWN";
    }
}
const char * to_string(TessellationDomainOrigin val) {
    switch(val) {
        case(TessellationDomainOrigin::UpperLeft): return "UpperLeft";
        case(TessellationDomainOrigin::LowerLeft): return "LowerLeft";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerYcbcrModelConversion val) {
    switch(val) {
        case(SamplerYcbcrModelConversion::RgbIdentity): return "RgbIdentity";
        case(SamplerYcbcrModelConversion::YcbcrIdentity): return "YcbcrIdentity";
        case(SamplerYcbcrModelConversion::Ycbcr709): return "Ycbcr709";
        case(SamplerYcbcrModelConversion::Ycbcr601): return "Ycbcr601";
        case(SamplerYcbcrModelConversion::Ycbcr2020): return "Ycbcr2020";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerYcbcrRange val) {
    switch(val) {
        case(SamplerYcbcrRange::ItuFull): return "ItuFull";
        case(SamplerYcbcrRange::ItuNarrow): return "ItuNarrow";
        default: return "UNKNOWN";
    }
}
const char * to_string(ChromaLocation val) {
    switch(val) {
        case(ChromaLocation::CositedEven): return "CositedEven";
        case(ChromaLocation::Midpoint): return "Midpoint";
        default: return "UNKNOWN";
    }
}
const char * to_string(SamplerReductionMode val) {
    switch(val) {
        case(SamplerReductionMode::WeightedAverage): return "WeightedAverage";
        case(SamplerReductionMode::Min): return "Min";
        case(SamplerReductionMode::Max): return "Max";
        default: return "UNKNOWN";
    }
}
const char * to_string(BlendOverlapEXT val) {
    switch(val) {
        case(BlendOverlapEXT::UncorrelatedEXT): return "UncorrelatedEXT";
        case(BlendOverlapEXT::DisjointEXT): return "DisjointEXT";
        case(BlendOverlapEXT::ConjointEXT): return "ConjointEXT";
        default: return "UNKNOWN";
    }
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
const char * to_string(FullScreenExclusiveEXT val) {
    switch(val) {
        case(FullScreenExclusiveEXT::DefaultEXT): return "DefaultEXT";
        case(FullScreenExclusiveEXT::AllowedEXT): return "AllowedEXT";
        case(FullScreenExclusiveEXT::DisallowedEXT): return "DisallowedEXT";
        case(FullScreenExclusiveEXT::ApplicationControlledEXT): return "ApplicationControlledEXT";
        default: return "UNKNOWN";
    }
}
#endif // VK_USE_PLATFORM_WIN32_KHR
const char * to_string(ShaderFloatControlsIndependence val) {
    switch(val) {
        case(ShaderFloatControlsIndependence::e32BitOnly): return "e32BitOnly";
        case(ShaderFloatControlsIndependence::All): return "All";
        case(ShaderFloatControlsIndependence::None): return "None";
        default: return "UNKNOWN";
    }
}
const char * to_string(VendorId val) {
    switch(val) {
        case(VendorId::VIV): return "VIV";
        case(VendorId::VSI): return "VSI";
        case(VendorId::Kazan): return "Kazan";
        case(VendorId::Codeplay): return "Codeplay";
        case(VendorId::MESA): return "MESA";
        default: return "UNKNOWN";
    }
}
const char * to_string(DriverId val) {
    switch(val) {
        case(DriverId::AmdProprietary): return "AmdProprietary";
        case(DriverId::AmdOpenSource): return "AmdOpenSource";
        case(DriverId::MesaRadv): return "MesaRadv";
        case(DriverId::NvidiaProprietary): return "NvidiaProprietary";
        case(DriverId::IntelProprietaryWindows): return "IntelProprietaryWindows";
        case(DriverId::IntelOpenSourceMESA): return "IntelOpenSourceMESA";
        case(DriverId::ImaginationProprietary): return "ImaginationProprietary";
        case(DriverId::QualcommProprietary): return "QualcommProprietary";
        case(DriverId::ArmProprietary): return "ArmProprietary";
        case(DriverId::GoogleSwiftshader): return "GoogleSwiftshader";
        case(DriverId::GgpProprietary): return "GgpProprietary";
        case(DriverId::BroadcomProprietary): return "BroadcomProprietary";
        case(DriverId::MesaLlvmpipe): return "MesaLlvmpipe";
        case(DriverId::Moltenvk): return "Moltenvk";
        default: return "UNKNOWN";
    }
}
const char * to_string(ShadingRatePaletteEntryNV val) {
    switch(val) {
        case(ShadingRatePaletteEntryNV::NoInvocationsNV): return "NoInvocationsNV";
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
        case(CoarseSampleOrderTypeNV::DefaultNV): return "DefaultNV";
        case(CoarseSampleOrderTypeNV::CustomNV): return "CustomNV";
        case(CoarseSampleOrderTypeNV::PixelMajorNV): return "PixelMajorNV";
        case(CoarseSampleOrderTypeNV::SampleMajorNV): return "SampleMajorNV";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineExecutableStatisticFormatKHR val) {
    switch(val) {
        case(PipelineExecutableStatisticFormatKHR::Bool32KHR): return "Bool32KHR";
        case(PipelineExecutableStatisticFormatKHR::Int64KHR): return "Int64KHR";
        case(PipelineExecutableStatisticFormatKHR::Uint64KHR): return "Uint64KHR";
        case(PipelineExecutableStatisticFormatKHR::Float64KHR): return "Float64KHR";
        default: return "UNKNOWN";
    }
}
const char * to_string(PipelineCacheCreateFlagBits val) {
    switch(val) {
        case(PipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT): return "ExternallySynchronizedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCacheCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT) out += "ExternallySynchronizedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(QueueFlagBits val) {
    switch(val) {
        case(QueueFlagBits::Graphics): return "Graphics";
        case(QueueFlagBits::Compute): return "Compute";
        case(QueueFlagBits::Transfer): return "Transfer";
        case(QueueFlagBits::SparseBinding): return "SparseBinding";
        case(QueueFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueueFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueueFlagBits::Graphics) out += "Graphics | ";
    if (flag & QueueFlagBits::Compute) out += "Compute | ";
    if (flag & QueueFlagBits::Transfer) out += "Transfer | ";
    if (flag & QueueFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & QueueFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CullModeFlagBits val) {
    switch(val) {
        case(CullModeFlagBits::None): return "None";
        case(CullModeFlagBits::Front): return "Front";
        case(CullModeFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
std::string to_string(CullModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CullModeFlagBits::None) out += "None | ";
    if (flag & CullModeFlagBits::Front) out += "Front | ";
    if (flag & CullModeFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(RenderPassCreateFlagBits val) {
    switch(val) {
        case(RenderPassCreateFlagBits::TransformBitQCOM): return "TransformBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(RenderPassCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & RenderPassCreateFlagBits::TransformBitQCOM) out += "TransformBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DeviceQueueCreateFlagBits val) {
    switch(val) {
        case(DeviceQueueCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceQueueCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceQueueCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(MemoryPropertyFlagBits val) {
    switch(val) {
        case(MemoryPropertyFlagBits::DeviceLocal): return "DeviceLocal";
        case(MemoryPropertyFlagBits::HostVisible): return "HostVisible";
        case(MemoryPropertyFlagBits::HostCoherent): return "HostCoherent";
        case(MemoryPropertyFlagBits::HostCached): return "HostCached";
        case(MemoryPropertyFlagBits::LazilyAllocated): return "LazilyAllocated";
        case(MemoryPropertyFlagBits::DeviceCoherentBitAMD): return "DeviceCoherentBitAMD";
        case(MemoryPropertyFlagBits::DeviceUncachedBitAMD): return "DeviceUncachedBitAMD";
        case(MemoryPropertyFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryPropertyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryPropertyFlagBits::DeviceLocal) out += "DeviceLocal | ";
    if (flag & MemoryPropertyFlagBits::HostVisible) out += "HostVisible | ";
    if (flag & MemoryPropertyFlagBits::HostCoherent) out += "HostCoherent | ";
    if (flag & MemoryPropertyFlagBits::HostCached) out += "HostCached | ";
    if (flag & MemoryPropertyFlagBits::LazilyAllocated) out += "LazilyAllocated | ";
    if (flag & MemoryPropertyFlagBits::DeviceCoherentBitAMD) out += "DeviceCoherentBitAMD | ";
    if (flag & MemoryPropertyFlagBits::DeviceUncachedBitAMD) out += "DeviceUncachedBitAMD | ";
    if (flag & MemoryPropertyFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(MemoryHeapFlagBits val) {
    switch(val) {
        case(MemoryHeapFlagBits::DeviceLocal): return "DeviceLocal";
        case(MemoryHeapFlagBits::MultiInstance): return "MultiInstance";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryHeapFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryHeapFlagBits::DeviceLocal) out += "DeviceLocal | ";
    if (flag & MemoryHeapFlagBits::MultiInstance) out += "MultiInstance | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(AccessFlagBits val) {
    switch(val) {
        case(AccessFlagBits::IndirectCommandRead): return "IndirectCommandRead";
        case(AccessFlagBits::IndexRead): return "IndexRead";
        case(AccessFlagBits::VertexAttributeRead): return "VertexAttributeRead";
        case(AccessFlagBits::UniformRead): return "UniformRead";
        case(AccessFlagBits::InputAttachmentRead): return "InputAttachmentRead";
        case(AccessFlagBits::ShaderRead): return "ShaderRead";
        case(AccessFlagBits::ShaderWrite): return "ShaderWrite";
        case(AccessFlagBits::ColorAttachmentRead): return "ColorAttachmentRead";
        case(AccessFlagBits::ColorAttachmentWrite): return "ColorAttachmentWrite";
        case(AccessFlagBits::DepthStencilAttachmentRead): return "DepthStencilAttachmentRead";
        case(AccessFlagBits::DepthStencilAttachmentWrite): return "DepthStencilAttachmentWrite";
        case(AccessFlagBits::TransferRead): return "TransferRead";
        case(AccessFlagBits::TransferWrite): return "TransferWrite";
        case(AccessFlagBits::HostRead): return "HostRead";
        case(AccessFlagBits::HostWrite): return "HostWrite";
        case(AccessFlagBits::MemoryRead): return "MemoryRead";
        case(AccessFlagBits::MemoryWrite): return "MemoryWrite";
        case(AccessFlagBits::TransformFeedbackWriteBitEXT): return "TransformFeedbackWriteBitEXT";
        case(AccessFlagBits::TransformFeedbackCounterReadBitEXT): return "TransformFeedbackCounterReadBitEXT";
        case(AccessFlagBits::TransformFeedbackCounterWriteBitEXT): return "TransformFeedbackCounterWriteBitEXT";
        case(AccessFlagBits::ConditionalRenderingReadBitEXT): return "ConditionalRenderingReadBitEXT";
        case(AccessFlagBits::ColorAttachmentReadNoncoherentBitEXT): return "ColorAttachmentReadNoncoherentBitEXT";
        case(AccessFlagBits::AccelerationStructureReadBitKHR): return "AccelerationStructureReadBitKHR";
        case(AccessFlagBits::AccelerationStructureWriteBitKHR): return "AccelerationStructureWriteBitKHR";
        case(AccessFlagBits::ShadingRateImageReadBitNV): return "ShadingRateImageReadBitNV";
        case(AccessFlagBits::FragmentDensityMapReadBitEXT): return "FragmentDensityMapReadBitEXT";
        case(AccessFlagBits::CommandPreprocessReadBitNV): return "CommandPreprocessReadBitNV";
        case(AccessFlagBits::CommandPreprocessWriteBitNV): return "CommandPreprocessWriteBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(AccessFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AccessFlagBits::IndirectCommandRead) out += "IndirectCommandRead | ";
    if (flag & AccessFlagBits::IndexRead) out += "IndexRead | ";
    if (flag & AccessFlagBits::VertexAttributeRead) out += "VertexAttributeRead | ";
    if (flag & AccessFlagBits::UniformRead) out += "UniformRead | ";
    if (flag & AccessFlagBits::InputAttachmentRead) out += "InputAttachmentRead | ";
    if (flag & AccessFlagBits::ShaderRead) out += "ShaderRead | ";
    if (flag & AccessFlagBits::ShaderWrite) out += "ShaderWrite | ";
    if (flag & AccessFlagBits::ColorAttachmentRead) out += "ColorAttachmentRead | ";
    if (flag & AccessFlagBits::ColorAttachmentWrite) out += "ColorAttachmentWrite | ";
    if (flag & AccessFlagBits::DepthStencilAttachmentRead) out += "DepthStencilAttachmentRead | ";
    if (flag & AccessFlagBits::DepthStencilAttachmentWrite) out += "DepthStencilAttachmentWrite | ";
    if (flag & AccessFlagBits::TransferRead) out += "TransferRead | ";
    if (flag & AccessFlagBits::TransferWrite) out += "TransferWrite | ";
    if (flag & AccessFlagBits::HostRead) out += "HostRead | ";
    if (flag & AccessFlagBits::HostWrite) out += "HostWrite | ";
    if (flag & AccessFlagBits::MemoryRead) out += "MemoryRead | ";
    if (flag & AccessFlagBits::MemoryWrite) out += "MemoryWrite | ";
    if (flag & AccessFlagBits::TransformFeedbackWriteBitEXT) out += "TransformFeedbackWriteBitEXT | ";
    if (flag & AccessFlagBits::TransformFeedbackCounterReadBitEXT) out += "TransformFeedbackCounterReadBitEXT | ";
    if (flag & AccessFlagBits::TransformFeedbackCounterWriteBitEXT) out += "TransformFeedbackCounterWriteBitEXT | ";
    if (flag & AccessFlagBits::ConditionalRenderingReadBitEXT) out += "ConditionalRenderingReadBitEXT | ";
    if (flag & AccessFlagBits::ColorAttachmentReadNoncoherentBitEXT) out += "ColorAttachmentReadNoncoherentBitEXT | ";
    if (flag & AccessFlagBits::AccelerationStructureReadBitKHR) out += "AccelerationStructureReadBitKHR | ";
    if (flag & AccessFlagBits::AccelerationStructureWriteBitKHR) out += "AccelerationStructureWriteBitKHR | ";
    if (flag & AccessFlagBits::ShadingRateImageReadBitNV) out += "ShadingRateImageReadBitNV | ";
    if (flag & AccessFlagBits::FragmentDensityMapReadBitEXT) out += "FragmentDensityMapReadBitEXT | ";
    if (flag & AccessFlagBits::CommandPreprocessReadBitNV) out += "CommandPreprocessReadBitNV | ";
    if (flag & AccessFlagBits::CommandPreprocessWriteBitNV) out += "CommandPreprocessWriteBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(BufferUsageFlagBits val) {
    switch(val) {
        case(BufferUsageFlagBits::TransferSrc): return "TransferSrc";
        case(BufferUsageFlagBits::TransferDst): return "TransferDst";
        case(BufferUsageFlagBits::UniformTexelBuffer): return "UniformTexelBuffer";
        case(BufferUsageFlagBits::StorageTexelBuffer): return "StorageTexelBuffer";
        case(BufferUsageFlagBits::UniformBuffer): return "UniformBuffer";
        case(BufferUsageFlagBits::StorageBuffer): return "StorageBuffer";
        case(BufferUsageFlagBits::IndexBuffer): return "IndexBuffer";
        case(BufferUsageFlagBits::VertexBuffer): return "VertexBuffer";
        case(BufferUsageFlagBits::IndirectBuffer): return "IndirectBuffer";
        case(BufferUsageFlagBits::TransformFeedbackBufferBitEXT): return "TransformFeedbackBufferBitEXT";
        case(BufferUsageFlagBits::TransformFeedbackCounterBufferBitEXT): return "TransformFeedbackCounterBufferBitEXT";
        case(BufferUsageFlagBits::ConditionalRenderingBitEXT): return "ConditionalRenderingBitEXT";
        case(BufferUsageFlagBits::RayTracingBitKHR): return "RayTracingBitKHR";
        case(BufferUsageFlagBits::ShaderDeviceAddress): return "ShaderDeviceAddress";
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BufferUsageFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & BufferUsageFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & BufferUsageFlagBits::UniformTexelBuffer) out += "UniformTexelBuffer | ";
    if (flag & BufferUsageFlagBits::StorageTexelBuffer) out += "StorageTexelBuffer | ";
    if (flag & BufferUsageFlagBits::UniformBuffer) out += "UniformBuffer | ";
    if (flag & BufferUsageFlagBits::StorageBuffer) out += "StorageBuffer | ";
    if (flag & BufferUsageFlagBits::IndexBuffer) out += "IndexBuffer | ";
    if (flag & BufferUsageFlagBits::VertexBuffer) out += "VertexBuffer | ";
    if (flag & BufferUsageFlagBits::IndirectBuffer) out += "IndirectBuffer | ";
    if (flag & BufferUsageFlagBits::TransformFeedbackBufferBitEXT) out += "TransformFeedbackBufferBitEXT | ";
    if (flag & BufferUsageFlagBits::TransformFeedbackCounterBufferBitEXT) out += "TransformFeedbackCounterBufferBitEXT | ";
    if (flag & BufferUsageFlagBits::ConditionalRenderingBitEXT) out += "ConditionalRenderingBitEXT | ";
    if (flag & BufferUsageFlagBits::RayTracingBitKHR) out += "RayTracingBitKHR | ";
    if (flag & BufferUsageFlagBits::ShaderDeviceAddress) out += "ShaderDeviceAddress | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(BufferCreateFlagBits val) {
    switch(val) {
        case(BufferCreateFlagBits::SparseBinding): return "SparseBinding";
        case(BufferCreateFlagBits::SparseResidency): return "SparseResidency";
        case(BufferCreateFlagBits::SparseAliased): return "SparseAliased";
        case(BufferCreateFlagBits::Protected): return "Protected";
        case(BufferCreateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BufferCreateFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & BufferCreateFlagBits::SparseResidency) out += "SparseResidency | ";
    if (flag & BufferCreateFlagBits::SparseAliased) out += "SparseAliased | ";
    if (flag & BufferCreateFlagBits::Protected) out += "Protected | ";
    if (flag & BufferCreateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ShaderStageFlagBits val) {
    switch(val) {
        case(ShaderStageFlagBits::Vertex): return "Vertex";
        case(ShaderStageFlagBits::TessellationControl): return "TessellationControl";
        case(ShaderStageFlagBits::TessellationEvaluation): return "TessellationEvaluation";
        case(ShaderStageFlagBits::Geometry): return "Geometry";
        case(ShaderStageFlagBits::Fragment): return "Fragment";
        case(ShaderStageFlagBits::Compute): return "Compute";
        case(ShaderStageFlagBits::RaygenBitKHR): return "RaygenBitKHR";
        case(ShaderStageFlagBits::AnyHitBitKHR): return "AnyHitBitKHR";
        case(ShaderStageFlagBits::ClosestHitBitKHR): return "ClosestHitBitKHR";
        case(ShaderStageFlagBits::MissBitKHR): return "MissBitKHR";
        case(ShaderStageFlagBits::IntersectionBitKHR): return "IntersectionBitKHR";
        case(ShaderStageFlagBits::CallableBitKHR): return "CallableBitKHR";
        case(ShaderStageFlagBits::TaskBitNV): return "TaskBitNV";
        case(ShaderStageFlagBits::MeshBitNV): return "MeshBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ShaderStageFlagBits::Vertex) out += "Vertex | ";
    if (flag & ShaderStageFlagBits::TessellationControl) out += "TessellationControl | ";
    if (flag & ShaderStageFlagBits::TessellationEvaluation) out += "TessellationEvaluation | ";
    if (flag & ShaderStageFlagBits::Geometry) out += "Geometry | ";
    if (flag & ShaderStageFlagBits::Fragment) out += "Fragment | ";
    if (flag & ShaderStageFlagBits::Compute) out += "Compute | ";
    if (flag & ShaderStageFlagBits::RaygenBitKHR) out += "RaygenBitKHR | ";
    if (flag & ShaderStageFlagBits::AnyHitBitKHR) out += "AnyHitBitKHR | ";
    if (flag & ShaderStageFlagBits::ClosestHitBitKHR) out += "ClosestHitBitKHR | ";
    if (flag & ShaderStageFlagBits::MissBitKHR) out += "MissBitKHR | ";
    if (flag & ShaderStageFlagBits::IntersectionBitKHR) out += "IntersectionBitKHR | ";
    if (flag & ShaderStageFlagBits::CallableBitKHR) out += "CallableBitKHR | ";
    if (flag & ShaderStageFlagBits::TaskBitNV) out += "TaskBitNV | ";
    if (flag & ShaderStageFlagBits::MeshBitNV) out += "MeshBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ImageUsageFlagBits val) {
    switch(val) {
        case(ImageUsageFlagBits::TransferSrc): return "TransferSrc";
        case(ImageUsageFlagBits::TransferDst): return "TransferDst";
        case(ImageUsageFlagBits::Sampled): return "Sampled";
        case(ImageUsageFlagBits::Storage): return "Storage";
        case(ImageUsageFlagBits::ColorAttachment): return "ColorAttachment";
        case(ImageUsageFlagBits::DepthStencilAttachment): return "DepthStencilAttachment";
        case(ImageUsageFlagBits::TransientAttachment): return "TransientAttachment";
        case(ImageUsageFlagBits::InputAttachment): return "InputAttachment";
        case(ImageUsageFlagBits::ShadingRateImageBitNV): return "ShadingRateImageBitNV";
        case(ImageUsageFlagBits::FragmentDensityMapBitEXT): return "FragmentDensityMapBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageUsageFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & ImageUsageFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & ImageUsageFlagBits::Sampled) out += "Sampled | ";
    if (flag & ImageUsageFlagBits::Storage) out += "Storage | ";
    if (flag & ImageUsageFlagBits::ColorAttachment) out += "ColorAttachment | ";
    if (flag & ImageUsageFlagBits::DepthStencilAttachment) out += "DepthStencilAttachment | ";
    if (flag & ImageUsageFlagBits::TransientAttachment) out += "TransientAttachment | ";
    if (flag & ImageUsageFlagBits::InputAttachment) out += "InputAttachment | ";
    if (flag & ImageUsageFlagBits::ShadingRateImageBitNV) out += "ShadingRateImageBitNV | ";
    if (flag & ImageUsageFlagBits::FragmentDensityMapBitEXT) out += "FragmentDensityMapBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ImageCreateFlagBits val) {
    switch(val) {
        case(ImageCreateFlagBits::SparseBinding): return "SparseBinding";
        case(ImageCreateFlagBits::SparseResidency): return "SparseResidency";
        case(ImageCreateFlagBits::SparseAliased): return "SparseAliased";
        case(ImageCreateFlagBits::MutableFormat): return "MutableFormat";
        case(ImageCreateFlagBits::CubeCompatible): return "CubeCompatible";
        case(ImageCreateFlagBits::CornerSampledBitNV): return "CornerSampledBitNV";
        case(ImageCreateFlagBits::SampleLocationsCompatibleDepthBitEXT): return "SampleLocationsCompatibleDepthBitEXT";
        case(ImageCreateFlagBits::SubsampledBitEXT): return "SubsampledBitEXT";
        case(ImageCreateFlagBits::Alias): return "Alias";
        case(ImageCreateFlagBits::SplitInstanceBindRegions): return "SplitInstanceBindRegions";
        case(ImageCreateFlagBits::e2DArrayCompatible): return "e2DArrayCompatible";
        case(ImageCreateFlagBits::BlockTexelViewCompatible): return "BlockTexelViewCompatible";
        case(ImageCreateFlagBits::ExtendedUsage): return "ExtendedUsage";
        case(ImageCreateFlagBits::Protected): return "Protected";
        case(ImageCreateFlagBits::Disjoint): return "Disjoint";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageCreateFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & ImageCreateFlagBits::SparseResidency) out += "SparseResidency | ";
    if (flag & ImageCreateFlagBits::SparseAliased) out += "SparseAliased | ";
    if (flag & ImageCreateFlagBits::MutableFormat) out += "MutableFormat | ";
    if (flag & ImageCreateFlagBits::CubeCompatible) out += "CubeCompatible | ";
    if (flag & ImageCreateFlagBits::CornerSampledBitNV) out += "CornerSampledBitNV | ";
    if (flag & ImageCreateFlagBits::SampleLocationsCompatibleDepthBitEXT) out += "SampleLocationsCompatibleDepthBitEXT | ";
    if (flag & ImageCreateFlagBits::SubsampledBitEXT) out += "SubsampledBitEXT | ";
    if (flag & ImageCreateFlagBits::Alias) out += "Alias | ";
    if (flag & ImageCreateFlagBits::SplitInstanceBindRegions) out += "SplitInstanceBindRegions | ";
    if (flag & ImageCreateFlagBits::e2DArrayCompatible) out += "e2DArrayCompatible | ";
    if (flag & ImageCreateFlagBits::BlockTexelViewCompatible) out += "BlockTexelViewCompatible | ";
    if (flag & ImageCreateFlagBits::ExtendedUsage) out += "ExtendedUsage | ";
    if (flag & ImageCreateFlagBits::Protected) out += "Protected | ";
    if (flag & ImageCreateFlagBits::Disjoint) out += "Disjoint | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ImageViewCreateFlagBits val) {
    switch(val) {
        case(ImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT): return "FragmentDensityMapDynamicBitEXT";
        case(ImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT): return "FragmentDensityMapDeferredBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT) out += "FragmentDensityMapDynamicBitEXT | ";
    if (flag & ImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT) out += "FragmentDensityMapDeferredBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SamplerCreateFlagBits val) {
    switch(val) {
        case(SamplerCreateFlagBits::SubsampledBitEXT): return "SubsampledBitEXT";
        case(SamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT): return "SubsampledCoarseReconstructionBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(SamplerCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SamplerCreateFlagBits::SubsampledBitEXT) out += "SubsampledBitEXT | ";
    if (flag & SamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT) out += "SubsampledCoarseReconstructionBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PipelineCreateFlagBits val) {
    switch(val) {
        case(PipelineCreateFlagBits::DisableOptimization): return "DisableOptimization";
        case(PipelineCreateFlagBits::AllowDerivatives): return "AllowDerivatives";
        case(PipelineCreateFlagBits::Derivative): return "Derivative";
        case(PipelineCreateFlagBits::RayTracingNoNullAnyHitShadersBitKHR): return "RayTracingNoNullAnyHitShadersBitKHR";
        case(PipelineCreateFlagBits::RayTracingNoNullClosestHitShadersBitKHR): return "RayTracingNoNullClosestHitShadersBitKHR";
        case(PipelineCreateFlagBits::RayTracingNoNullMissShadersBitKHR): return "RayTracingNoNullMissShadersBitKHR";
        case(PipelineCreateFlagBits::RayTracingNoNullIntersectionShadersBitKHR): return "RayTracingNoNullIntersectionShadersBitKHR";
        case(PipelineCreateFlagBits::RayTracingSkipTrianglesBitKHR): return "RayTracingSkipTrianglesBitKHR";
        case(PipelineCreateFlagBits::RayTracingSkipAabbsBitKHR): return "RayTracingSkipAabbsBitKHR";
        case(PipelineCreateFlagBits::DeferCompileBitNV): return "DeferCompileBitNV";
        case(PipelineCreateFlagBits::CaptureStatisticsBitKHR): return "CaptureStatisticsBitKHR";
        case(PipelineCreateFlagBits::CaptureInternalRepresentationsBitKHR): return "CaptureInternalRepresentationsBitKHR";
        case(PipelineCreateFlagBits::IndirectBindableBitNV): return "IndirectBindableBitNV";
        case(PipelineCreateFlagBits::LibraryBitKHR): return "LibraryBitKHR";
        case(PipelineCreateFlagBits::FailOnPipelineCompileRequiredBitEXT): return "FailOnPipelineCompileRequiredBitEXT";
        case(PipelineCreateFlagBits::EarlyReturnOnFailureBitEXT): return "EarlyReturnOnFailureBitEXT";
        case(PipelineCreateFlagBits::ViewIndexFromDeviceIndex): return "ViewIndexFromDeviceIndex";
        case(PipelineCreateFlagBits::DispatchBase): return "DispatchBase";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCreateFlagBits::DisableOptimization) out += "DisableOptimization | ";
    if (flag & PipelineCreateFlagBits::AllowDerivatives) out += "AllowDerivatives | ";
    if (flag & PipelineCreateFlagBits::Derivative) out += "Derivative | ";
    if (flag & PipelineCreateFlagBits::RayTracingNoNullAnyHitShadersBitKHR) out += "RayTracingNoNullAnyHitShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::RayTracingNoNullClosestHitShadersBitKHR) out += "RayTracingNoNullClosestHitShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::RayTracingNoNullMissShadersBitKHR) out += "RayTracingNoNullMissShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::RayTracingNoNullIntersectionShadersBitKHR) out += "RayTracingNoNullIntersectionShadersBitKHR | ";
    if (flag & PipelineCreateFlagBits::RayTracingSkipTrianglesBitKHR) out += "RayTracingSkipTrianglesBitKHR | ";
    if (flag & PipelineCreateFlagBits::RayTracingSkipAabbsBitKHR) out += "RayTracingSkipAabbsBitKHR | ";
    if (flag & PipelineCreateFlagBits::DeferCompileBitNV) out += "DeferCompileBitNV | ";
    if (flag & PipelineCreateFlagBits::CaptureStatisticsBitKHR) out += "CaptureStatisticsBitKHR | ";
    if (flag & PipelineCreateFlagBits::CaptureInternalRepresentationsBitKHR) out += "CaptureInternalRepresentationsBitKHR | ";
    if (flag & PipelineCreateFlagBits::IndirectBindableBitNV) out += "IndirectBindableBitNV | ";
    if (flag & PipelineCreateFlagBits::LibraryBitKHR) out += "LibraryBitKHR | ";
    if (flag & PipelineCreateFlagBits::FailOnPipelineCompileRequiredBitEXT) out += "FailOnPipelineCompileRequiredBitEXT | ";
    if (flag & PipelineCreateFlagBits::EarlyReturnOnFailureBitEXT) out += "EarlyReturnOnFailureBitEXT | ";
    if (flag & PipelineCreateFlagBits::ViewIndexFromDeviceIndex) out += "ViewIndexFromDeviceIndex | ";
    if (flag & PipelineCreateFlagBits::DispatchBase) out += "DispatchBase | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PipelineShaderStageCreateFlagBits val) {
    switch(val) {
        case(PipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT): return "AllowVaryingSubgroupSizeBitEXT";
        case(PipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT): return "RequireFullSubgroupsBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineShaderStageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT) out += "AllowVaryingSubgroupSizeBitEXT | ";
    if (flag & PipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT) out += "RequireFullSubgroupsBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ColorComponentFlagBits val) {
    switch(val) {
        case(ColorComponentFlagBits::R): return "R";
        case(ColorComponentFlagBits::G): return "G";
        case(ColorComponentFlagBits::B): return "B";
        case(ColorComponentFlagBits::A): return "A";
        default: return "UNKNOWN";
    }
}
std::string to_string(ColorComponentFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ColorComponentFlagBits::R) out += "R | ";
    if (flag & ColorComponentFlagBits::G) out += "G | ";
    if (flag & ColorComponentFlagBits::B) out += "B | ";
    if (flag & ColorComponentFlagBits::A) out += "A | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(FenceCreateFlagBits val) {
    switch(val) {
        case(FenceCreateFlagBits::Signaled): return "Signaled";
        default: return "UNKNOWN";
    }
}
std::string to_string(FenceCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceCreateFlagBits::Signaled) out += "Signaled | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SemaphoreCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(FormatFeatureFlagBits val) {
    switch(val) {
        case(FormatFeatureFlagBits::SampledImage): return "SampledImage";
        case(FormatFeatureFlagBits::StorageImage): return "StorageImage";
        case(FormatFeatureFlagBits::StorageImageAtomic): return "StorageImageAtomic";
        case(FormatFeatureFlagBits::UniformTexelBuffer): return "UniformTexelBuffer";
        case(FormatFeatureFlagBits::StorageTexelBuffer): return "StorageTexelBuffer";
        case(FormatFeatureFlagBits::StorageTexelBufferAtomic): return "StorageTexelBufferAtomic";
        case(FormatFeatureFlagBits::VertexBuffer): return "VertexBuffer";
        case(FormatFeatureFlagBits::ColorAttachment): return "ColorAttachment";
        case(FormatFeatureFlagBits::ColorAttachmentBlend): return "ColorAttachmentBlend";
        case(FormatFeatureFlagBits::DepthStencilAttachment): return "DepthStencilAttachment";
        case(FormatFeatureFlagBits::BlitSrc): return "BlitSrc";
        case(FormatFeatureFlagBits::BlitDst): return "BlitDst";
        case(FormatFeatureFlagBits::SampledImageFilterLinear): return "SampledImageFilterLinear";
        case(FormatFeatureFlagBits::SampledImageFilterCubicBitIMG): return "SampledImageFilterCubicBitIMG";
        case(FormatFeatureFlagBits::AccelerationStructureVertexBufferBitKHR): return "AccelerationStructureVertexBufferBitKHR";
        case(FormatFeatureFlagBits::FragmentDensityMapBitEXT): return "FragmentDensityMapBitEXT";
        case(FormatFeatureFlagBits::TransferSrc): return "TransferSrc";
        case(FormatFeatureFlagBits::TransferDst): return "TransferDst";
        case(FormatFeatureFlagBits::MidpointChromaSamples): return "MidpointChromaSamples";
        case(FormatFeatureFlagBits::SampledImageYcbcrConversionLinearFilter): return "SampledImageYcbcrConversionLinearFilter";
        case(FormatFeatureFlagBits::SampledImageYcbcrConversionSeparateReconstructionFilter): return "SampledImageYcbcrConversionSeparateReconstructionFilter";
        case(FormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicit): return "SampledImageYcbcrConversionChromaReconstructionExplicit";
        case(FormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicitForceable): return "SampledImageYcbcrConversionChromaReconstructionExplicitForceable";
        case(FormatFeatureFlagBits::Disjoint): return "Disjoint";
        case(FormatFeatureFlagBits::CositedChromaSamples): return "CositedChromaSamples";
        case(FormatFeatureFlagBits::SampledImageFilterMinmax): return "SampledImageFilterMinmax";
        default: return "UNKNOWN";
    }
}
std::string to_string(FormatFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FormatFeatureFlagBits::SampledImage) out += "SampledImage | ";
    if (flag & FormatFeatureFlagBits::StorageImage) out += "StorageImage | ";
    if (flag & FormatFeatureFlagBits::StorageImageAtomic) out += "StorageImageAtomic | ";
    if (flag & FormatFeatureFlagBits::UniformTexelBuffer) out += "UniformTexelBuffer | ";
    if (flag & FormatFeatureFlagBits::StorageTexelBuffer) out += "StorageTexelBuffer | ";
    if (flag & FormatFeatureFlagBits::StorageTexelBufferAtomic) out += "StorageTexelBufferAtomic | ";
    if (flag & FormatFeatureFlagBits::VertexBuffer) out += "VertexBuffer | ";
    if (flag & FormatFeatureFlagBits::ColorAttachment) out += "ColorAttachment | ";
    if (flag & FormatFeatureFlagBits::ColorAttachmentBlend) out += "ColorAttachmentBlend | ";
    if (flag & FormatFeatureFlagBits::DepthStencilAttachment) out += "DepthStencilAttachment | ";
    if (flag & FormatFeatureFlagBits::BlitSrc) out += "BlitSrc | ";
    if (flag & FormatFeatureFlagBits::BlitDst) out += "BlitDst | ";
    if (flag & FormatFeatureFlagBits::SampledImageFilterLinear) out += "SampledImageFilterLinear | ";
    if (flag & FormatFeatureFlagBits::SampledImageFilterCubicBitIMG) out += "SampledImageFilterCubicBitIMG | ";
    if (flag & FormatFeatureFlagBits::AccelerationStructureVertexBufferBitKHR) out += "AccelerationStructureVertexBufferBitKHR | ";
    if (flag & FormatFeatureFlagBits::FragmentDensityMapBitEXT) out += "FragmentDensityMapBitEXT | ";
    if (flag & FormatFeatureFlagBits::TransferSrc) out += "TransferSrc | ";
    if (flag & FormatFeatureFlagBits::TransferDst) out += "TransferDst | ";
    if (flag & FormatFeatureFlagBits::MidpointChromaSamples) out += "MidpointChromaSamples | ";
    if (flag & FormatFeatureFlagBits::SampledImageYcbcrConversionLinearFilter) out += "SampledImageYcbcrConversionLinearFilter | ";
    if (flag & FormatFeatureFlagBits::SampledImageYcbcrConversionSeparateReconstructionFilter) out += "SampledImageYcbcrConversionSeparateReconstructionFilter | ";
    if (flag & FormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicit) out += "SampledImageYcbcrConversionChromaReconstructionExplicit | ";
    if (flag & FormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicitForceable) out += "SampledImageYcbcrConversionChromaReconstructionExplicitForceable | ";
    if (flag & FormatFeatureFlagBits::Disjoint) out += "Disjoint | ";
    if (flag & FormatFeatureFlagBits::CositedChromaSamples) out += "CositedChromaSamples | ";
    if (flag & FormatFeatureFlagBits::SampledImageFilterMinmax) out += "SampledImageFilterMinmax | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(QueryControlFlagBits val) {
    switch(val) {
        case(QueryControlFlagBits::Precise): return "Precise";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryControlFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryControlFlagBits::Precise) out += "Precise | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(QueryResultFlagBits val) {
    switch(val) {
        case(QueryResultFlagBits::e64): return "e64";
        case(QueryResultFlagBits::Wait): return "Wait";
        case(QueryResultFlagBits::WithAvailability): return "WithAvailability";
        case(QueryResultFlagBits::Partial): return "Partial";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryResultFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryResultFlagBits::e64) out += "e64 | ";
    if (flag & QueryResultFlagBits::Wait) out += "Wait | ";
    if (flag & QueryResultFlagBits::WithAvailability) out += "WithAvailability | ";
    if (flag & QueryResultFlagBits::Partial) out += "Partial | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CommandBufferUsageFlagBits val) {
    switch(val) {
        case(CommandBufferUsageFlagBits::OneTimeSubmit): return "OneTimeSubmit";
        case(CommandBufferUsageFlagBits::RenderPassContinue): return "RenderPassContinue";
        case(CommandBufferUsageFlagBits::SimultaneousUse): return "SimultaneousUse";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandBufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferUsageFlagBits::OneTimeSubmit) out += "OneTimeSubmit | ";
    if (flag & CommandBufferUsageFlagBits::RenderPassContinue) out += "RenderPassContinue | ";
    if (flag & CommandBufferUsageFlagBits::SimultaneousUse) out += "SimultaneousUse | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(QueryPipelineStatisticFlagBits val) {
    switch(val) {
        case(QueryPipelineStatisticFlagBits::InputAssemblyVertices): return "InputAssemblyVertices";
        case(QueryPipelineStatisticFlagBits::InputAssemblyPrimitives): return "InputAssemblyPrimitives";
        case(QueryPipelineStatisticFlagBits::VertexShaderInvocations): return "VertexShaderInvocations";
        case(QueryPipelineStatisticFlagBits::GeometryShaderInvocations): return "GeometryShaderInvocations";
        case(QueryPipelineStatisticFlagBits::GeometryShaderPrimitives): return "GeometryShaderPrimitives";
        case(QueryPipelineStatisticFlagBits::ClippingInvocations): return "ClippingInvocations";
        case(QueryPipelineStatisticFlagBits::ClippingPrimitives): return "ClippingPrimitives";
        case(QueryPipelineStatisticFlagBits::FragmentShaderInvocations): return "FragmentShaderInvocations";
        case(QueryPipelineStatisticFlagBits::TessellationControlShaderPatches): return "TessellationControlShaderPatches";
        case(QueryPipelineStatisticFlagBits::TessellationEvaluationShaderInvocations): return "TessellationEvaluationShaderInvocations";
        case(QueryPipelineStatisticFlagBits::ComputeShaderInvocations): return "ComputeShaderInvocations";
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryPipelineStatisticFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryPipelineStatisticFlagBits::InputAssemblyVertices) out += "InputAssemblyVertices | ";
    if (flag & QueryPipelineStatisticFlagBits::InputAssemblyPrimitives) out += "InputAssemblyPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::VertexShaderInvocations) out += "VertexShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::GeometryShaderInvocations) out += "GeometryShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::GeometryShaderPrimitives) out += "GeometryShaderPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::ClippingInvocations) out += "ClippingInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::ClippingPrimitives) out += "ClippingPrimitives | ";
    if (flag & QueryPipelineStatisticFlagBits::FragmentShaderInvocations) out += "FragmentShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::TessellationControlShaderPatches) out += "TessellationControlShaderPatches | ";
    if (flag & QueryPipelineStatisticFlagBits::TessellationEvaluationShaderInvocations) out += "TessellationEvaluationShaderInvocations | ";
    if (flag & QueryPipelineStatisticFlagBits::ComputeShaderInvocations) out += "ComputeShaderInvocations | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ImageAspectFlagBits val) {
    switch(val) {
        case(ImageAspectFlagBits::Color): return "Color";
        case(ImageAspectFlagBits::Depth): return "Depth";
        case(ImageAspectFlagBits::Stencil): return "Stencil";
        case(ImageAspectFlagBits::Metadata): return "Metadata";
        case(ImageAspectFlagBits::MemoryPlane0BitEXT): return "MemoryPlane0BitEXT";
        case(ImageAspectFlagBits::MemoryPlane1BitEXT): return "MemoryPlane1BitEXT";
        case(ImageAspectFlagBits::MemoryPlane2BitEXT): return "MemoryPlane2BitEXT";
        case(ImageAspectFlagBits::MemoryPlane3BitEXT): return "MemoryPlane3BitEXT";
        case(ImageAspectFlagBits::Plane0): return "Plane0";
        case(ImageAspectFlagBits::Plane1): return "Plane1";
        case(ImageAspectFlagBits::Plane2): return "Plane2";
        default: return "UNKNOWN";
    }
}
std::string to_string(ImageAspectFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageAspectFlagBits::Color) out += "Color | ";
    if (flag & ImageAspectFlagBits::Depth) out += "Depth | ";
    if (flag & ImageAspectFlagBits::Stencil) out += "Stencil | ";
    if (flag & ImageAspectFlagBits::Metadata) out += "Metadata | ";
    if (flag & ImageAspectFlagBits::MemoryPlane0BitEXT) out += "MemoryPlane0BitEXT | ";
    if (flag & ImageAspectFlagBits::MemoryPlane1BitEXT) out += "MemoryPlane1BitEXT | ";
    if (flag & ImageAspectFlagBits::MemoryPlane2BitEXT) out += "MemoryPlane2BitEXT | ";
    if (flag & ImageAspectFlagBits::MemoryPlane3BitEXT) out += "MemoryPlane3BitEXT | ";
    if (flag & ImageAspectFlagBits::Plane0) out += "Plane0 | ";
    if (flag & ImageAspectFlagBits::Plane1) out += "Plane1 | ";
    if (flag & ImageAspectFlagBits::Plane2) out += "Plane2 | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SparseImageFormatFlagBits val) {
    switch(val) {
        case(SparseImageFormatFlagBits::SingleMiptail): return "SingleMiptail";
        case(SparseImageFormatFlagBits::AlignedMipSize): return "AlignedMipSize";
        case(SparseImageFormatFlagBits::NonstandardBlockSize): return "NonstandardBlockSize";
        default: return "UNKNOWN";
    }
}
std::string to_string(SparseImageFormatFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseImageFormatFlagBits::SingleMiptail) out += "SingleMiptail | ";
    if (flag & SparseImageFormatFlagBits::AlignedMipSize) out += "AlignedMipSize | ";
    if (flag & SparseImageFormatFlagBits::NonstandardBlockSize) out += "NonstandardBlockSize | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SparseMemoryBindFlagBits val) {
    switch(val) {
        case(SparseMemoryBindFlagBits::Metadata): return "Metadata";
        default: return "UNKNOWN";
    }
}
std::string to_string(SparseMemoryBindFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseMemoryBindFlagBits::Metadata) out += "Metadata | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PipelineStageFlagBits val) {
    switch(val) {
        case(PipelineStageFlagBits::TopOfPipe): return "TopOfPipe";
        case(PipelineStageFlagBits::DrawIndirect): return "DrawIndirect";
        case(PipelineStageFlagBits::VertexInput): return "VertexInput";
        case(PipelineStageFlagBits::VertexShader): return "VertexShader";
        case(PipelineStageFlagBits::TessellationControlShader): return "TessellationControlShader";
        case(PipelineStageFlagBits::TessellationEvaluationShader): return "TessellationEvaluationShader";
        case(PipelineStageFlagBits::GeometryShader): return "GeometryShader";
        case(PipelineStageFlagBits::FragmentShader): return "FragmentShader";
        case(PipelineStageFlagBits::EarlyFragmentTests): return "EarlyFragmentTests";
        case(PipelineStageFlagBits::LateFragmentTests): return "LateFragmentTests";
        case(PipelineStageFlagBits::ColorAttachmentOutput): return "ColorAttachmentOutput";
        case(PipelineStageFlagBits::ComputeShader): return "ComputeShader";
        case(PipelineStageFlagBits::Transfer): return "Transfer";
        case(PipelineStageFlagBits::BottomOfPipe): return "BottomOfPipe";
        case(PipelineStageFlagBits::Host): return "Host";
        case(PipelineStageFlagBits::AllGraphics): return "AllGraphics";
        case(PipelineStageFlagBits::AllCommands): return "AllCommands";
        case(PipelineStageFlagBits::TransformFeedbackBitEXT): return "TransformFeedbackBitEXT";
        case(PipelineStageFlagBits::ConditionalRenderingBitEXT): return "ConditionalRenderingBitEXT";
        case(PipelineStageFlagBits::RayTracingShaderBitKHR): return "RayTracingShaderBitKHR";
        case(PipelineStageFlagBits::AccelerationStructureBuildBitKHR): return "AccelerationStructureBuildBitKHR";
        case(PipelineStageFlagBits::ShadingRateImageBitNV): return "ShadingRateImageBitNV";
        case(PipelineStageFlagBits::TaskShaderBitNV): return "TaskShaderBitNV";
        case(PipelineStageFlagBits::MeshShaderBitNV): return "MeshShaderBitNV";
        case(PipelineStageFlagBits::FragmentDensityProcessBitEXT): return "FragmentDensityProcessBitEXT";
        case(PipelineStageFlagBits::CommandPreprocessBitNV): return "CommandPreprocessBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineStageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineStageFlagBits::TopOfPipe) out += "TopOfPipe | ";
    if (flag & PipelineStageFlagBits::DrawIndirect) out += "DrawIndirect | ";
    if (flag & PipelineStageFlagBits::VertexInput) out += "VertexInput | ";
    if (flag & PipelineStageFlagBits::VertexShader) out += "VertexShader | ";
    if (flag & PipelineStageFlagBits::TessellationControlShader) out += "TessellationControlShader | ";
    if (flag & PipelineStageFlagBits::TessellationEvaluationShader) out += "TessellationEvaluationShader | ";
    if (flag & PipelineStageFlagBits::GeometryShader) out += "GeometryShader | ";
    if (flag & PipelineStageFlagBits::FragmentShader) out += "FragmentShader | ";
    if (flag & PipelineStageFlagBits::EarlyFragmentTests) out += "EarlyFragmentTests | ";
    if (flag & PipelineStageFlagBits::LateFragmentTests) out += "LateFragmentTests | ";
    if (flag & PipelineStageFlagBits::ColorAttachmentOutput) out += "ColorAttachmentOutput | ";
    if (flag & PipelineStageFlagBits::ComputeShader) out += "ComputeShader | ";
    if (flag & PipelineStageFlagBits::Transfer) out += "Transfer | ";
    if (flag & PipelineStageFlagBits::BottomOfPipe) out += "BottomOfPipe | ";
    if (flag & PipelineStageFlagBits::Host) out += "Host | ";
    if (flag & PipelineStageFlagBits::AllGraphics) out += "AllGraphics | ";
    if (flag & PipelineStageFlagBits::AllCommands) out += "AllCommands | ";
    if (flag & PipelineStageFlagBits::TransformFeedbackBitEXT) out += "TransformFeedbackBitEXT | ";
    if (flag & PipelineStageFlagBits::ConditionalRenderingBitEXT) out += "ConditionalRenderingBitEXT | ";
    if (flag & PipelineStageFlagBits::RayTracingShaderBitKHR) out += "RayTracingShaderBitKHR | ";
    if (flag & PipelineStageFlagBits::AccelerationStructureBuildBitKHR) out += "AccelerationStructureBuildBitKHR | ";
    if (flag & PipelineStageFlagBits::ShadingRateImageBitNV) out += "ShadingRateImageBitNV | ";
    if (flag & PipelineStageFlagBits::TaskShaderBitNV) out += "TaskShaderBitNV | ";
    if (flag & PipelineStageFlagBits::MeshShaderBitNV) out += "MeshShaderBitNV | ";
    if (flag & PipelineStageFlagBits::FragmentDensityProcessBitEXT) out += "FragmentDensityProcessBitEXT | ";
    if (flag & PipelineStageFlagBits::CommandPreprocessBitNV) out += "CommandPreprocessBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CommandPoolCreateFlagBits val) {
    switch(val) {
        case(CommandPoolCreateFlagBits::Transient): return "Transient";
        case(CommandPoolCreateFlagBits::ResetCommandBuffer): return "ResetCommandBuffer";
        case(CommandPoolCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolCreateFlagBits::Transient) out += "Transient | ";
    if (flag & CommandPoolCreateFlagBits::ResetCommandBuffer) out += "ResetCommandBuffer | ";
    if (flag & CommandPoolCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CommandPoolResetFlagBits val) {
    switch(val) {
        case(CommandPoolResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CommandBufferResetFlagBits val) {
    switch(val) {
        case(CommandBufferResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandBufferResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
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
}
const char * to_string(AttachmentDescriptionFlagBits val) {
    switch(val) {
        case(AttachmentDescriptionFlagBits::MayAlias): return "MayAlias";
        default: return "UNKNOWN";
    }
}
std::string to_string(AttachmentDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AttachmentDescriptionFlagBits::MayAlias) out += "MayAlias | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(StencilFaceFlagBits val) {
    switch(val) {
        case(StencilFaceFlagBits::Front): return "Front";
        case(StencilFaceFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
std::string to_string(StencilFaceFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & StencilFaceFlagBits::Front) out += "Front | ";
    if (flag & StencilFaceFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DescriptorPoolCreateFlagBits val) {
    switch(val) {
        case(DescriptorPoolCreateFlagBits::FreeDescriptorSet): return "FreeDescriptorSet";
        case(DescriptorPoolCreateFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorPoolCreateFlagBits::FreeDescriptorSet) out += "FreeDescriptorSet | ";
    if (flag & DescriptorPoolCreateFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DependencyFlagBits val) {
    switch(val) {
        case(DependencyFlagBits::ByRegion): return "ByRegion";
        case(DependencyFlagBits::DeviceGroup): return "DeviceGroup";
        case(DependencyFlagBits::ViewLocal): return "ViewLocal";
        default: return "UNKNOWN";
    }
}
std::string to_string(DependencyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DependencyFlagBits::ByRegion) out += "ByRegion | ";
    if (flag & DependencyFlagBits::DeviceGroup) out += "DeviceGroup | ";
    if (flag & DependencyFlagBits::ViewLocal) out += "ViewLocal | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SemaphoreWaitFlagBits val) {
    switch(val) {
        case(SemaphoreWaitFlagBits::Any): return "Any";
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreWaitFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreWaitFlagBits::Any) out += "Any | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DisplayPlaneAlphaFlagBitsKHR val) {
    switch(val) {
        case(DisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR): return "GlobalBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR): return "PerPixelBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR): return "PerPixelPremultipliedBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplayPlaneAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR) out += "GlobalBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR) out += "PerPixelBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR) out += "PerPixelPremultipliedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(CompositeAlphaFlagBitsKHR val) {
    switch(val) {
        case(CompositeAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(CompositeAlphaFlagBitsKHR::PreMultipliedBitKHR): return "PreMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::PostMultipliedBitKHR): return "PostMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::InheritBitKHR): return "InheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(CompositeAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CompositeAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::PreMultipliedBitKHR) out += "PreMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::PostMultipliedBitKHR) out += "PostMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::InheritBitKHR) out += "InheritBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SurfaceTransformFlagBitsKHR val) {
    switch(val) {
        case(SurfaceTransformFlagBitsKHR::IdentityBitKHR): return "IdentityBitKHR";
        case(SurfaceTransformFlagBitsKHR::Rotate90BitKHR): return "Rotate90BitKHR";
        case(SurfaceTransformFlagBitsKHR::Rotate180BitKHR): return "Rotate180BitKHR";
        case(SurfaceTransformFlagBitsKHR::Rotate270BitKHR): return "Rotate270BitKHR";
        case(SurfaceTransformFlagBitsKHR::HorizontalMirrorBitKHR): return "HorizontalMirrorBitKHR";
        case(SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate90BitKHR): return "HorizontalMirrorRotate90BitKHR";
        case(SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate180BitKHR): return "HorizontalMirrorRotate180BitKHR";
        case(SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate270BitKHR): return "HorizontalMirrorRotate270BitKHR";
        case(SurfaceTransformFlagBitsKHR::InheritBitKHR): return "InheritBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(SurfaceTransformFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SurfaceTransformFlagBitsKHR::IdentityBitKHR) out += "IdentityBitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::Rotate90BitKHR) out += "Rotate90BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::Rotate180BitKHR) out += "Rotate180BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::Rotate270BitKHR) out += "Rotate270BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::HorizontalMirrorBitKHR) out += "HorizontalMirrorBitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate90BitKHR) out += "HorizontalMirrorRotate90BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate180BitKHR) out += "HorizontalMirrorRotate180BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::HorizontalMirrorRotate270BitKHR) out += "HorizontalMirrorRotate270BitKHR | ";
    if (flag & SurfaceTransformFlagBitsKHR::InheritBitKHR) out += "InheritBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DebugReportFlagBitsEXT val) {
    switch(val) {
        case(DebugReportFlagBitsEXT::InformationBitEXT): return "InformationBitEXT";
        case(DebugReportFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(DebugReportFlagBitsEXT::PerformanceWarningBitEXT): return "PerformanceWarningBitEXT";
        case(DebugReportFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        case(DebugReportFlagBitsEXT::DebugBitEXT): return "DebugBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugReportFlagBitsEXT::InformationBitEXT) out += "InformationBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::PerformanceWarningBitEXT) out += "PerformanceWarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::DebugBitEXT) out += "DebugBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalMemoryHandleTypeFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV): return "OpaqueWin32BitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV): return "OpaqueWin32KmtBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV): return "D3D11ImageBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV): return "D3D11ImageKmtBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryHandleTypeFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV) out += "OpaqueWin32BitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV) out += "OpaqueWin32KmtBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV) out += "D3D11ImageBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV) out += "D3D11ImageKmtBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalMemoryFeatureFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV): return "DedicatedOnlyBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::ExportableBitNV): return "ExportableBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::ImportableBitNV): return "ImportableBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryFeatureFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV) out += "DedicatedOnlyBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::ExportableBitNV) out += "ExportableBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::ImportableBitNV) out += "ImportableBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SubgroupFeatureFlagBits val) {
    switch(val) {
        case(SubgroupFeatureFlagBits::Basic): return "Basic";
        case(SubgroupFeatureFlagBits::Vote): return "Vote";
        case(SubgroupFeatureFlagBits::Arithmetic): return "Arithmetic";
        case(SubgroupFeatureFlagBits::Ballot): return "Ballot";
        case(SubgroupFeatureFlagBits::Shuffle): return "Shuffle";
        case(SubgroupFeatureFlagBits::ShuffleRelative): return "ShuffleRelative";
        case(SubgroupFeatureFlagBits::Clustered): return "Clustered";
        case(SubgroupFeatureFlagBits::Quad): return "Quad";
        case(SubgroupFeatureFlagBits::PartitionedBitNV): return "PartitionedBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(SubgroupFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SubgroupFeatureFlagBits::Basic) out += "Basic | ";
    if (flag & SubgroupFeatureFlagBits::Vote) out += "Vote | ";
    if (flag & SubgroupFeatureFlagBits::Arithmetic) out += "Arithmetic | ";
    if (flag & SubgroupFeatureFlagBits::Ballot) out += "Ballot | ";
    if (flag & SubgroupFeatureFlagBits::Shuffle) out += "Shuffle | ";
    if (flag & SubgroupFeatureFlagBits::ShuffleRelative) out += "ShuffleRelative | ";
    if (flag & SubgroupFeatureFlagBits::Clustered) out += "Clustered | ";
    if (flag & SubgroupFeatureFlagBits::Quad) out += "Quad | ";
    if (flag & SubgroupFeatureFlagBits::PartitionedBitNV) out += "PartitionedBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(IndirectCommandsLayoutUsageFlagBitsNV val) {
    switch(val) {
        case(IndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV): return "ExplicitPreprocessBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV): return "IndexedSequencesBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV): return "UnorderedSequencesBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(IndirectCommandsLayoutUsageFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV) out += "ExplicitPreprocessBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV) out += "IndexedSequencesBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV) out += "UnorderedSequencesBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(IndirectStateFlagBitsNV val) {
    switch(val) {
        case(IndirectStateFlagBitsNV::FlagFrontfaceBitNV): return "FlagFrontfaceBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(IndirectStateFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectStateFlagBitsNV::FlagFrontfaceBitNV) out += "FlagFrontfaceBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PrivateDataSlotCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PrivateDataSlotCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(DescriptorSetLayoutCreateFlagBits val) {
    switch(val) {
        case(DescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR): return "PushDescriptorBitKHR";
        case(DescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool): return "UpdateAfterBindPool";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorSetLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR) out += "PushDescriptorBitKHR | ";
    if (flag & DescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool) out += "UpdateAfterBindPool | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalMemoryHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalMemoryHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(ExternalMemoryHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(ExternalMemoryHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(ExternalMemoryHandleTypeFlagBits::D3D11Texture): return "D3D11Texture";
        case(ExternalMemoryHandleTypeFlagBits::D3D11TextureKmt): return "D3D11TextureKmt";
        case(ExternalMemoryHandleTypeFlagBits::D3D12Heap): return "D3D12Heap";
        case(ExternalMemoryHandleTypeFlagBits::D3D12Resource): return "D3D12Resource";
        case(ExternalMemoryHandleTypeFlagBits::DmaBufBitEXT): return "DmaBufBitEXT";
        case(ExternalMemoryHandleTypeFlagBits::AndroidHardwareBufferBitANDROID): return "AndroidHardwareBufferBitANDROID";
        case(ExternalMemoryHandleTypeFlagBits::HostAllocationBitEXT): return "HostAllocationBitEXT";
        case(ExternalMemoryHandleTypeFlagBits::HostMappedForeignMemoryBitEXT): return "HostMappedForeignMemoryBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::D3D11Texture) out += "D3D11Texture | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::D3D11TextureKmt) out += "D3D11TextureKmt | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::D3D12Heap) out += "D3D12Heap | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::D3D12Resource) out += "D3D12Resource | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::DmaBufBitEXT) out += "DmaBufBitEXT | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::AndroidHardwareBufferBitANDROID) out += "AndroidHardwareBufferBitANDROID | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::HostAllocationBitEXT) out += "HostAllocationBitEXT | ";
    if (flag & ExternalMemoryHandleTypeFlagBits::HostMappedForeignMemoryBitEXT) out += "HostMappedForeignMemoryBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalMemoryFeatureFlagBits val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBits::DedicatedOnly): return "DedicatedOnly";
        case(ExternalMemoryFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalMemoryFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBits::DedicatedOnly) out += "DedicatedOnly | ";
    if (flag & ExternalMemoryFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalMemoryFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalSemaphoreHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(ExternalSemaphoreHandleTypeFlagBits::D3D12Fence): return "D3D12Fence";
        case(ExternalSemaphoreHandleTypeFlagBits::SyncFd): return "SyncFd";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalSemaphoreHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::D3D12Fence) out += "D3D12Fence | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalSemaphoreFeatureFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalSemaphoreFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalSemaphoreFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalSemaphoreFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SemaphoreImportFlagBits val) {
    switch(val) {
        case(SemaphoreImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(SemaphoreImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalFenceHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalFenceHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(ExternalFenceHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(ExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(ExternalFenceHandleTypeFlagBits::SyncFd): return "SyncFd";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalFenceHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & ExternalFenceHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ExternalFenceFeatureFlagBits val) {
    switch(val) {
        case(ExternalFenceFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalFenceFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
std::string to_string(ExternalFenceFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalFenceFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(FenceImportFlagBits val) {
    switch(val) {
        case(FenceImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
std::string to_string(FenceImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SurfaceCounterFlagBitsEXT val) {
    switch(val) {
        case(SurfaceCounterFlagBitsEXT::VblankEXT): return "VblankEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(SurfaceCounterFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SurfaceCounterFlagBitsEXT::VblankEXT) out += "VblankEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PeerMemoryFeatureFlagBits val) {
    switch(val) {
        case(PeerMemoryFeatureFlagBits::CopySrc): return "CopySrc";
        case(PeerMemoryFeatureFlagBits::CopyDst): return "CopyDst";
        case(PeerMemoryFeatureFlagBits::GenericSrc): return "GenericSrc";
        case(PeerMemoryFeatureFlagBits::GenericDst): return "GenericDst";
        default: return "UNKNOWN";
    }
}
std::string to_string(PeerMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PeerMemoryFeatureFlagBits::CopySrc) out += "CopySrc | ";
    if (flag & PeerMemoryFeatureFlagBits::CopyDst) out += "CopyDst | ";
    if (flag & PeerMemoryFeatureFlagBits::GenericSrc) out += "GenericSrc | ";
    if (flag & PeerMemoryFeatureFlagBits::GenericDst) out += "GenericDst | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(MemoryAllocateFlagBits val) {
    switch(val) {
        case(MemoryAllocateFlagBits::DeviceMask): return "DeviceMask";
        case(MemoryAllocateFlagBits::DeviceAddress): return "DeviceAddress";
        case(MemoryAllocateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryAllocateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryAllocateFlagBits::DeviceMask) out += "DeviceMask | ";
    if (flag & MemoryAllocateFlagBits::DeviceAddress) out += "DeviceAddress | ";
    if (flag & MemoryAllocateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DeviceGroupPresentModeFlagBitsKHR val) {
    switch(val) {
        case(DeviceGroupPresentModeFlagBitsKHR::LocalBitKHR): return "LocalBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR): return "RemoteBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::SumBitKHR): return "SumBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR): return "LocalMultiDeviceBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceGroupPresentModeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceGroupPresentModeFlagBitsKHR::LocalBitKHR) out += "LocalBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR) out += "RemoteBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::SumBitKHR) out += "SumBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR) out += "LocalMultiDeviceBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SwapchainCreateFlagBitsKHR val) {
    switch(val) {
        case(SwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR): return "SplitInstanceBindRegionsBitKHR";
        case(SwapchainCreateFlagBitsKHR::ProtectedBitKHR): return "ProtectedBitKHR";
        case(SwapchainCreateFlagBitsKHR::MutableFormatBitKHR): return "MutableFormatBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(SwapchainCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR) out += "SplitInstanceBindRegionsBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::ProtectedBitKHR) out += "ProtectedBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::MutableFormatBitKHR) out += "MutableFormatBitKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(SubpassDescriptionFlagBits val) {
    switch(val) {
        case(SubpassDescriptionFlagBits::PerViewAttributesBitNVX): return "PerViewAttributesBitNVX";
        case(SubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX): return "PerViewPositionXOnlyBitNVX";
        case(SubpassDescriptionFlagBits::FragmentRegionBitQCOM): return "FragmentRegionBitQCOM";
        case(SubpassDescriptionFlagBits::ShaderResolveBitQCOM): return "ShaderResolveBitQCOM";
        default: return "UNKNOWN";
    }
}
std::string to_string(SubpassDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SubpassDescriptionFlagBits::PerViewAttributesBitNVX) out += "PerViewAttributesBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX) out += "PerViewPositionXOnlyBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::FragmentRegionBitQCOM) out += "FragmentRegionBitQCOM | ";
    if (flag & SubpassDescriptionFlagBits::ShaderResolveBitQCOM) out += "ShaderResolveBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DebugUtilsMessageSeverityFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT): return "VerboseBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT): return "InfoBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessageSeverityFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT) out += "VerboseBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT) out += "InfoBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DebugUtilsMessageTypeFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT): return "GeneralBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT): return "ValidationBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT): return "PerformanceBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessageTypeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT) out += "GeneralBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT) out += "ValidationBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT) out += "PerformanceBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DescriptorBindingFlagBits val) {
    switch(val) {
        case(DescriptorBindingFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        case(DescriptorBindingFlagBits::UpdateUnusedWhilePending): return "UpdateUnusedWhilePending";
        case(DescriptorBindingFlagBits::PartiallyBound): return "PartiallyBound";
        case(DescriptorBindingFlagBits::VariableDescriptorCount): return "VariableDescriptorCount";
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorBindingFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorBindingFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    if (flag & DescriptorBindingFlagBits::UpdateUnusedWhilePending) out += "UpdateUnusedWhilePending | ";
    if (flag & DescriptorBindingFlagBits::PartiallyBound) out += "PartiallyBound | ";
    if (flag & DescriptorBindingFlagBits::VariableDescriptorCount) out += "VariableDescriptorCount | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ConditionalRenderingFlagBitsEXT val) {
    switch(val) {
        case(ConditionalRenderingFlagBitsEXT::InvertedBitEXT): return "InvertedBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ConditionalRenderingFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ConditionalRenderingFlagBitsEXT::InvertedBitEXT) out += "InvertedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(ResolveModeFlagBits val) {
    switch(val) {
        case(ResolveModeFlagBits::None): return "None";
        case(ResolveModeFlagBits::SampleZero): return "SampleZero";
        case(ResolveModeFlagBits::Average): return "Average";
        case(ResolveModeFlagBits::Min): return "Min";
        case(ResolveModeFlagBits::Max): return "Max";
        default: return "UNKNOWN";
    }
}
std::string to_string(ResolveModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ResolveModeFlagBits::None) out += "None | ";
    if (flag & ResolveModeFlagBits::SampleZero) out += "SampleZero | ";
    if (flag & ResolveModeFlagBits::Average) out += "Average | ";
    if (flag & ResolveModeFlagBits::Min) out += "Min | ";
    if (flag & ResolveModeFlagBits::Max) out += "Max | ";
    return out.substr(0, out.size() - 3);
}
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryInstanceFlagBitsKHR val) {
    switch(val) {
        case(GeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR): return "TriangleFacingCullDisableBitKHR";
        case(GeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR): return "TriangleFrontCounterclockwiseBitKHR";
        case(GeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR): return "ForceOpaqueBitKHR";
        case(GeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR): return "ForceNoOpaqueBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(GeometryInstanceFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR) out += "TriangleFacingCullDisableBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR) out += "TriangleFrontCounterclockwiseBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR) out += "ForceOpaqueBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR) out += "ForceNoOpaqueBitKHR | ";
    return out.substr(0, out.size() - 3);
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(GeometryFlagBitsKHR val) {
    switch(val) {
        case(GeometryFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(GeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR): return "NoDuplicateAnyHitInvocationBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(GeometryFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & GeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR) out += "NoDuplicateAnyHitInvocationBitKHR | ";
    return out.substr(0, out.size() - 3);
}
#endif // VK_ENABLE_BETA_EXTENSIONS
#if defined(VK_ENABLE_BETA_EXTENSIONS)
const char * to_string(BuildAccelerationStructureFlagBitsKHR val) {
    switch(val) {
        case(BuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR): return "AllowUpdateBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR): return "AllowCompactionBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR): return "PreferFastTraceBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR): return "PreferFastBuildBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR): return "LowMemoryBitKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(BuildAccelerationStructureFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR) out += "AllowUpdateBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR) out += "AllowCompactionBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR) out += "PreferFastTraceBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR) out += "PreferFastBuildBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR) out += "LowMemoryBitKHR | ";
    return out.substr(0, out.size() - 3);
}
#endif // VK_ENABLE_BETA_EXTENSIONS
const char * to_string(FramebufferCreateFlagBits val) {
    switch(val) {
        case(FramebufferCreateFlagBits::Imageless): return "Imageless";
        default: return "UNKNOWN";
    }
}
std::string to_string(FramebufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FramebufferCreateFlagBits::Imageless) out += "Imageless | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(DeviceDiagnosticsConfigFlagBitsNV val) {
    switch(val) {
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV): return "EnableShaderDebugInfoBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV): return "EnableResourceTrackingBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV): return "EnableAutomaticCheckpointsBitNV";
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceDiagnosticsConfigFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV) out += "EnableShaderDebugInfoBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV) out += "EnableResourceTrackingBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV) out += "EnableAutomaticCheckpointsBitNV | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PipelineCreationFeedbackFlagBitsEXT val) {
    switch(val) {
        case(PipelineCreationFeedbackFlagBitsEXT::ValidBitEXT): return "ValidBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT): return "ApplicationPipelineCacheHitBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT): return "BasePipelineAccelerationBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCreationFeedbackFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCreationFeedbackFlagBitsEXT::ValidBitEXT) out += "ValidBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT) out += "ApplicationPipelineCacheHitBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT) out += "BasePipelineAccelerationBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(PerformanceCounterDescriptionFlagBitsKHR val) {
    switch(val) {
        case(PerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingKHR): return "PerformanceImpactingKHR";
        case(PerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedKHR): return "ConcurrentlyImpactedKHR";
        default: return "UNKNOWN";
    }
}
std::string to_string(PerformanceCounterDescriptionFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingKHR) out += "PerformanceImpactingKHR | ";
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedKHR) out += "ConcurrentlyImpactedKHR | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(AcquireProfilingLockFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(AcquireProfilingLockFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(ShaderCorePropertiesFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderCorePropertiesFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(ShaderModuleCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ShaderModuleCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(PipelineCompilerControlFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCompilerControlFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
const char * to_string(ToolPurposeFlagBitsEXT val) {
    switch(val) {
        case(ToolPurposeFlagBitsEXT::ValidationBitEXT): return "ValidationBitEXT";
        case(ToolPurposeFlagBitsEXT::ProfilingBitEXT): return "ProfilingBitEXT";
        case(ToolPurposeFlagBitsEXT::TracingBitEXT): return "TracingBitEXT";
        case(ToolPurposeFlagBitsEXT::AdditionalFeaturesBitEXT): return "AdditionalFeaturesBitEXT";
        case(ToolPurposeFlagBitsEXT::ModifyingFeaturesBitEXT): return "ModifyingFeaturesBitEXT";
        case(ToolPurposeFlagBitsEXT::DebugReportingBitEXT): return "DebugReportingBitEXT";
        case(ToolPurposeFlagBitsEXT::DebugMarkersBitEXT): return "DebugMarkersBitEXT";
        default: return "UNKNOWN";
    }
}
std::string to_string(ToolPurposeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ToolPurposeFlagBitsEXT::ValidationBitEXT) out += "ValidationBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::ProfilingBitEXT) out += "ProfilingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::TracingBitEXT) out += "TracingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::AdditionalFeaturesBitEXT) out += "AdditionalFeaturesBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::ModifyingFeaturesBitEXT) out += "ModifyingFeaturesBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::DebugReportingBitEXT) out += "DebugReportingBitEXT | ";
    if (flag & ToolPurposeFlagBitsEXT::DebugMarkersBitEXT) out += "DebugMarkersBitEXT | ";
    return out.substr(0, out.size() - 3);
}
const char * to_string(QueryPoolCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(QueryPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineLayoutCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineDepthStencilStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDepthStencilStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineDynamicStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDynamicStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineColorBlendStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineColorBlendStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineMultisampleStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineMultisampleStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineRasterizationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineViewportStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineViewportStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineTessellationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineTessellationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineInputAssemblyStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineInputAssemblyStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineVertexInputStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineVertexInputStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(BufferViewCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(BufferViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(InstanceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(InstanceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DeviceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(EventCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(EventCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(MemoryMapFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(MemoryMapFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DescriptorPoolResetFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DescriptorUpdateTemplateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DescriptorUpdateTemplateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DisplayModeCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplayModeCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DisplaySurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DisplaySurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
const char * to_string(AndroidSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(AndroidSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
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
}
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
}
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
}
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
}
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
}
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
}
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
}
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
}
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
}
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
}
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
}
#endif // VK_USE_PLATFORM_GGP
const char * to_string(HeadlessSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(HeadlessSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(CommandPoolTrimFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(CommandPoolTrimFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineViewportSwizzleStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineViewportSwizzleStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineDiscardRectangleStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineDiscardRectangleStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineCoverageToColorStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageToColorStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineCoverageModulationStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageModulationStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineCoverageReductionStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineCoverageReductionStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(ValidationCacheCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(ValidationCacheCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DebugUtilsMessengerCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessengerCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DebugUtilsMessengerCallbackDataFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DebugUtilsMessengerCallbackDataFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(DeviceMemoryReportFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(DeviceMemoryReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineRasterizationConservativeStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationConservativeStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineRasterizationStateStreamCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationStateStreamCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
const char * to_string(PipelineRasterizationDepthClipStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
std::string to_string(PipelineRasterizationDepthClipStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
} // namespace vk
// clang-format on
