
// clang-format off
#pragma once
#include <stdint.h>
#include <cstddef>
#include <array>
#include <new>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include "vk_platform.h"


// Compatability with compilers that don't support __has_feature
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if !defined(VK_MODULE_DISABLE_LEAK_SANITIZER_SUPPRESSION) && (__has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__) )
#include <sanitizer/lsan_interface.h>
#define VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE __lsan::ScopedDisabler lsan_scope{};
#else
#define VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
#endif

#ifndef __has_feature
#undef __has_feature
#endif


namespace vk {
constexpr uint32_t make_vk_version(uint32_t major, uint32_t minor, uint32_t patch) {
    return major << 22 | minor << 12 | patch;
}

#if !defined(VK_DEFINE_HANDLE)
#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;
#endif

#if !defined(VK_DEFINE_NON_DISPATCHABLE_HANDLE)
#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T *object;
#else
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object;
#endif
#endif
constexpr auto MAX_PHYSICAL_DEVICE_NAME_SIZE = 256;
constexpr auto UUID_SIZE = 16;
constexpr auto LUID_SIZE = 8;
constexpr auto LUID_SIZE_KHR = LUID_SIZE;
constexpr auto MAX_EXTENSION_NAME_SIZE = 256;
constexpr auto MAX_DESCRIPTION_SIZE = 256;
constexpr auto MAX_MEMORY_TYPES = 32;
constexpr auto MAX_MEMORY_HEAPS = 16;
constexpr auto LOD_CLAMP_NONE = 1000.0f;
constexpr auto REMAINING_MIP_LEVELS = (~0U);
constexpr auto REMAINING_ARRAY_LAYERS = (~0U);
constexpr auto WHOLE_SIZE = (~0ULL);
constexpr auto ATTACHMENT_UNUSED = (~0U);
constexpr auto QUEUE_FAMILY_IGNORED = (~0U);
constexpr auto QUEUE_FAMILY_EXTERNAL = (~0U-1);
constexpr auto QUEUE_FAMILY_EXTERNAL_KHR = QUEUE_FAMILY_EXTERNAL;
constexpr auto QUEUE_FAMILY_FOREIGN_EXT = (~0U-2);
constexpr auto SUBPASS_EXTERNAL = (~0U);
constexpr auto MAX_DEVICE_GROUP_SIZE = 32;
constexpr auto MAX_DEVICE_GROUP_SIZE_KHR = MAX_DEVICE_GROUP_SIZE;
constexpr auto MAX_DRIVER_NAME_SIZE = 256;
constexpr auto MAX_DRIVER_NAME_SIZE_KHR = MAX_DRIVER_NAME_SIZE;
constexpr auto MAX_DRIVER_INFO_SIZE = 256;
constexpr auto MAX_DRIVER_INFO_SIZE_KHR = MAX_DRIVER_INFO_SIZE;
constexpr auto SHADER_UNUSED_KHR = (~0U);
constexpr auto SHADER_UNUSED_NV = SHADER_UNUSED_KHR;
using SampleMask = uint32_t;
using Bool32 = uint32_t;
using Flags = uint32_t;
using DeviceSize = uint64_t;
using DeviceAddress = uint64_t;
enum class AttachmentLoadOp : uint32_t {
    Load = 0,
    Clear = 1,
    DontCare = 2,
};
enum class AttachmentStoreOp : uint32_t {
    Store = 0,
    DontCare = 1,
    NoneQCOM = 1000301000,
};
enum class BlendFactor : uint32_t {
    Zero = 0,
    One = 1,
    SrcColor = 2,
    OneMinusSrcColor = 3,
    DstColor = 4,
    OneMinusDstColor = 5,
    SrcAlpha = 6,
    OneMinusSrcAlpha = 7,
    DstAlpha = 8,
    OneMinusDstAlpha = 9,
    ConstantColor = 10,
    OneMinusConstantColor = 11,
    ConstantAlpha = 12,
    OneMinusConstantAlpha = 13,
    SrcAlphaSaturate = 14,
    Src1Color = 15,
    OneMinusSrc1Color = 16,
    Src1Alpha = 17,
    OneMinusSrc1Alpha = 18,
};
enum class BlendOp : uint32_t {
    Add = 0,
    Subtract = 1,
    ReverseSubtract = 2,
    Min = 3,
    Max = 4,
    ZeroEXT = 1000148000,
    SrcEXT = 1000148001,
    DstEXT = 1000148002,
    SrcOverEXT = 1000148003,
    DstOverEXT = 1000148004,
    SrcInEXT = 1000148005,
    DstInEXT = 1000148006,
    SrcOutEXT = 1000148007,
    DstOutEXT = 1000148008,
    SrcAtopEXT = 1000148009,
    DstAtopEXT = 1000148010,
    XorEXT = 1000148011,
    MultiplyEXT = 1000148012,
    ScreenEXT = 1000148013,
    OverlayEXT = 1000148014,
    DarkenEXT = 1000148015,
    LightenEXT = 1000148016,
    ColordodgeEXT = 1000148017,
    ColorburnEXT = 1000148018,
    HardlightEXT = 1000148019,
    SoftlightEXT = 1000148020,
    DifferenceEXT = 1000148021,
    ExclusionEXT = 1000148022,
    InvertEXT = 1000148023,
    InvertRgbEXT = 1000148024,
    LineardodgeEXT = 1000148025,
    LinearburnEXT = 1000148026,
    VividlightEXT = 1000148027,
    LinearlightEXT = 1000148028,
    PinlightEXT = 1000148029,
    HardmixEXT = 1000148030,
    HslHueEXT = 1000148031,
    HslSaturationEXT = 1000148032,
    HslColorEXT = 1000148033,
    HslLuminosityEXT = 1000148034,
    PlusEXT = 1000148035,
    PlusClampedEXT = 1000148036,
    PlusClampedAlphaEXT = 1000148037,
    PlusDarkerEXT = 1000148038,
    MinusEXT = 1000148039,
    MinusClampedEXT = 1000148040,
    ContrastEXT = 1000148041,
    InvertOvgEXT = 1000148042,
    RedEXT = 1000148043,
    GreenEXT = 1000148044,
    BlueEXT = 1000148045,
};
enum class BorderColor : uint32_t {
    FloatTransparentBlack = 0,
    IntTransparentBlack = 1,
    FloatOpaqueBlack = 2,
    IntOpaqueBlack = 3,
    FloatOpaqueWhite = 4,
    IntOpaqueWhite = 5,
    FloatCustomEXT = 1000287003,
    IntCustomEXT = 1000287004,
};
enum class PipelineCacheHeaderVersion : uint32_t {
    One = 1,
};
enum class ComponentSwizzle : uint32_t {
    Identity = 0,
    Zero = 1,
    One = 2,
    R = 3,
    G = 4,
    B = 5,
    A = 6,
};
enum class CommandBufferLevel : uint32_t {
    Primary = 0,
    Secondary = 1,
};
enum class CompareOp : uint32_t {
    Never = 0,
    Less = 1,
    Equal = 2,
    LessOrEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterOrEqual = 6,
    Always = 7,
};
enum class DescriptorType : uint32_t {
    Sampler = 0,
    CombinedImageSampler = 1,
    SampledImage = 2,
    StorageImage = 3,
    UniformTexelBuffer = 4,
    StorageTexelBuffer = 5,
    UniformBuffer = 6,
    StorageBuffer = 7,
    UniformBufferDynamic = 8,
    StorageBufferDynamic = 9,
    InputAttachment = 10,
    InlineUniformBlockEXT = 1000138000,
    AccelerationStructureKHR = 1000150000,
    AccelerationStructureNV = 1000165000,
};
enum class DynamicState : uint32_t {
    Viewport = 0,
    Scissor = 1,
    LineWidth = 2,
    DepthBias = 3,
    BlendConstants = 4,
    DepthBounds = 5,
    StencilCompareMask = 6,
    StencilWriteMask = 7,
    StencilReference = 8,
    ViewportWScalingNV = 1000087000,
    DiscardRectangleEXT = 1000099000,
    SampleLocationsEXT = 1000143000,
    RayTracingPipelineStackSizeKHR = 1000347000,
    ViewportShadingRatePaletteNV = 1000164004,
    ViewportCoarseSampleOrderNV = 1000164006,
    ExclusiveScissorNV = 1000205001,
    FragmentShadingRateKHR = 1000226000,
    LineStippleEXT = 1000259000,
    CullModeEXT = 1000267000,
    FrontFaceEXT = 1000267001,
    PrimitiveTopologyEXT = 1000267002,
    ViewportWithCountEXT = 1000267003,
    ScissorWithCountEXT = 1000267004,
    VertexInputBindingStrideEXT = 1000267005,
    DepthTestEnableEXT = 1000267006,
    DepthWriteEnableEXT = 1000267007,
    DepthCompareOpEXT = 1000267008,
    DepthBoundsTestEnableEXT = 1000267009,
    StencilTestEnableEXT = 1000267010,
    StencilOpEXT = 1000267011,
};
enum class PolygonMode : uint32_t {
    Fill = 0,
    Line = 1,
    Point = 2,
    FillRectangleNV = 1000153000,
};
enum class Format : uint32_t {
    Undefined = 0,
    R4G4UnormPack8 = 1,
    R4G4B4A4UnormPack16 = 2,
    B4G4R4A4UnormPack16 = 3,
    R5G6B5UnormPack16 = 4,
    B5G6R5UnormPack16 = 5,
    R5G5B5A1UnormPack16 = 6,
    B5G5R5A1UnormPack16 = 7,
    A1R5G5B5UnormPack16 = 8,
    R8Unorm = 9,
    R8Snorm = 10,
    R8Uscaled = 11,
    R8Sscaled = 12,
    R8Uint = 13,
    R8Sint = 14,
    R8Srgb = 15,
    R8G8Unorm = 16,
    R8G8Snorm = 17,
    R8G8Uscaled = 18,
    R8G8Sscaled = 19,
    R8G8Uint = 20,
    R8G8Sint = 21,
    R8G8Srgb = 22,
    R8G8B8Unorm = 23,
    R8G8B8Snorm = 24,
    R8G8B8Uscaled = 25,
    R8G8B8Sscaled = 26,
    R8G8B8Uint = 27,
    R8G8B8Sint = 28,
    R8G8B8Srgb = 29,
    B8G8R8Unorm = 30,
    B8G8R8Snorm = 31,
    B8G8R8Uscaled = 32,
    B8G8R8Sscaled = 33,
    B8G8R8Uint = 34,
    B8G8R8Sint = 35,
    B8G8R8Srgb = 36,
    R8G8B8A8Unorm = 37,
    R8G8B8A8Snorm = 38,
    R8G8B8A8Uscaled = 39,
    R8G8B8A8Sscaled = 40,
    R8G8B8A8Uint = 41,
    R8G8B8A8Sint = 42,
    R8G8B8A8Srgb = 43,
    B8G8R8A8Unorm = 44,
    B8G8R8A8Snorm = 45,
    B8G8R8A8Uscaled = 46,
    B8G8R8A8Sscaled = 47,
    B8G8R8A8Uint = 48,
    B8G8R8A8Sint = 49,
    B8G8R8A8Srgb = 50,
    A8B8G8R8UnormPack32 = 51,
    A8B8G8R8SnormPack32 = 52,
    A8B8G8R8UscaledPack32 = 53,
    A8B8G8R8SscaledPack32 = 54,
    A8B8G8R8UintPack32 = 55,
    A8B8G8R8SintPack32 = 56,
    A8B8G8R8SrgbPack32 = 57,
    A2R10G10B10UnormPack32 = 58,
    A2R10G10B10SnormPack32 = 59,
    A2R10G10B10UscaledPack32 = 60,
    A2R10G10B10SscaledPack32 = 61,
    A2R10G10B10UintPack32 = 62,
    A2R10G10B10SintPack32 = 63,
    A2B10G10R10UnormPack32 = 64,
    A2B10G10R10SnormPack32 = 65,
    A2B10G10R10UscaledPack32 = 66,
    A2B10G10R10SscaledPack32 = 67,
    A2B10G10R10UintPack32 = 68,
    A2B10G10R10SintPack32 = 69,
    R16Unorm = 70,
    R16Snorm = 71,
    R16Uscaled = 72,
    R16Sscaled = 73,
    R16Uint = 74,
    R16Sint = 75,
    R16Sfloat = 76,
    R16G16Unorm = 77,
    R16G16Snorm = 78,
    R16G16Uscaled = 79,
    R16G16Sscaled = 80,
    R16G16Uint = 81,
    R16G16Sint = 82,
    R16G16Sfloat = 83,
    R16G16B16Unorm = 84,
    R16G16B16Snorm = 85,
    R16G16B16Uscaled = 86,
    R16G16B16Sscaled = 87,
    R16G16B16Uint = 88,
    R16G16B16Sint = 89,
    R16G16B16Sfloat = 90,
    R16G16B16A16Unorm = 91,
    R16G16B16A16Snorm = 92,
    R16G16B16A16Uscaled = 93,
    R16G16B16A16Sscaled = 94,
    R16G16B16A16Uint = 95,
    R16G16B16A16Sint = 96,
    R16G16B16A16Sfloat = 97,
    R32Uint = 98,
    R32Sint = 99,
    R32Sfloat = 100,
    R32G32Uint = 101,
    R32G32Sint = 102,
    R32G32Sfloat = 103,
    R32G32B32Uint = 104,
    R32G32B32Sint = 105,
    R32G32B32Sfloat = 106,
    R32G32B32A32Uint = 107,
    R32G32B32A32Sint = 108,
    R32G32B32A32Sfloat = 109,
    R64Uint = 110,
    R64Sint = 111,
    R64Sfloat = 112,
    R64G64Uint = 113,
    R64G64Sint = 114,
    R64G64Sfloat = 115,
    R64G64B64Uint = 116,
    R64G64B64Sint = 117,
    R64G64B64Sfloat = 118,
    R64G64B64A64Uint = 119,
    R64G64B64A64Sint = 120,
    R64G64B64A64Sfloat = 121,
    B10G11R11UfloatPack32 = 122,
    E5B9G9R9UfloatPack32 = 123,
    D16Unorm = 124,
    X8D24UnormPack32 = 125,
    D32Sfloat = 126,
    S8Uint = 127,
    D16UnormS8Uint = 128,
    D24UnormS8Uint = 129,
    D32SfloatS8Uint = 130,
    Bc1RgbUnormBlock = 131,
    Bc1RgbSrgbBlock = 132,
    Bc1RgbaUnormBlock = 133,
    Bc1RgbaSrgbBlock = 134,
    Bc2UnormBlock = 135,
    Bc2SrgbBlock = 136,
    Bc3UnormBlock = 137,
    Bc3SrgbBlock = 138,
    Bc4UnormBlock = 139,
    Bc4SnormBlock = 140,
    Bc5UnormBlock = 141,
    Bc5SnormBlock = 142,
    Bc6HUfloatBlock = 143,
    Bc6HSfloatBlock = 144,
    Bc7UnormBlock = 145,
    Bc7SrgbBlock = 146,
    Etc2R8G8B8UnormBlock = 147,
    Etc2R8G8B8SrgbBlock = 148,
    Etc2R8G8B8A1UnormBlock = 149,
    Etc2R8G8B8A1SrgbBlock = 150,
    Etc2R8G8B8A8UnormBlock = 151,
    Etc2R8G8B8A8SrgbBlock = 152,
    EacR11UnormBlock = 153,
    EacR11SnormBlock = 154,
    EacR11G11UnormBlock = 155,
    EacR11G11SnormBlock = 156,
    Astc4X4UnormBlock = 157,
    Astc4X4SrgbBlock = 158,
    Astc5X4UnormBlock = 159,
    Astc5X4SrgbBlock = 160,
    Astc5X5UnormBlock = 161,
    Astc5X5SrgbBlock = 162,
    Astc6X5UnormBlock = 163,
    Astc6X5SrgbBlock = 164,
    Astc6X6UnormBlock = 165,
    Astc6X6SrgbBlock = 166,
    Astc8X5UnormBlock = 167,
    Astc8X5SrgbBlock = 168,
    Astc8X6UnormBlock = 169,
    Astc8X6SrgbBlock = 170,
    Astc8X8UnormBlock = 171,
    Astc8X8SrgbBlock = 172,
    Astc10X5UnormBlock = 173,
    Astc10X5SrgbBlock = 174,
    Astc10X6UnormBlock = 175,
    Astc10X6SrgbBlock = 176,
    Astc10X8UnormBlock = 177,
    Astc10X8SrgbBlock = 178,
    Astc10X10UnormBlock = 179,
    Astc10X10SrgbBlock = 180,
    Astc12X10UnormBlock = 181,
    Astc12X10SrgbBlock = 182,
    Astc12X12UnormBlock = 183,
    Astc12X12SrgbBlock = 184,
    Pvrtc12BppUnormBlockIMG = 1000054000,
    Pvrtc14BppUnormBlockIMG = 1000054001,
    Pvrtc22BppUnormBlockIMG = 1000054002,
    Pvrtc24BppUnormBlockIMG = 1000054003,
    Pvrtc12BppSrgbBlockIMG = 1000054004,
    Pvrtc14BppSrgbBlockIMG = 1000054005,
    Pvrtc22BppSrgbBlockIMG = 1000054006,
    Pvrtc24BppSrgbBlockIMG = 1000054007,
    Astc4X4SfloatBlockEXT = 1000066000,
    Astc5X4SfloatBlockEXT = 1000066001,
    Astc5X5SfloatBlockEXT = 1000066002,
    Astc6X5SfloatBlockEXT = 1000066003,
    Astc6X6SfloatBlockEXT = 1000066004,
    Astc8X5SfloatBlockEXT = 1000066005,
    Astc8X6SfloatBlockEXT = 1000066006,
    Astc8X8SfloatBlockEXT = 1000066007,
    Astc10X5SfloatBlockEXT = 1000066008,
    Astc10X6SfloatBlockEXT = 1000066009,
    Astc10X8SfloatBlockEXT = 1000066010,
    Astc10X10SfloatBlockEXT = 1000066011,
    Astc12X10SfloatBlockEXT = 1000066012,
    Astc12X12SfloatBlockEXT = 1000066013,
    A4R4G4B4UnormPack16EXT = 1000340000,
    A4B4G4R4UnormPack16EXT = 1000340001,
    G8B8G8R8422Unorm = 1000156000,
    B8G8R8G8422Unorm = 1000156001,
    G8B8R83Plane420Unorm = 1000156002,
    G8B8R82Plane420Unorm = 1000156003,
    G8B8R83Plane422Unorm = 1000156004,
    G8B8R82Plane422Unorm = 1000156005,
    G8B8R83Plane444Unorm = 1000156006,
    R10X6UnormPack16 = 1000156007,
    R10X6G10X6Unorm2Pack16 = 1000156008,
    R10X6G10X6B10X6A10X6Unorm4Pack16 = 1000156009,
    G10X6B10X6G10X6R10X6422Unorm4Pack16 = 1000156010,
    B10X6G10X6R10X6G10X6422Unorm4Pack16 = 1000156011,
    G10X6B10X6R10X63Plane420Unorm3Pack16 = 1000156012,
    G10X6B10X6R10X62Plane420Unorm3Pack16 = 1000156013,
    G10X6B10X6R10X63Plane422Unorm3Pack16 = 1000156014,
    G10X6B10X6R10X62Plane422Unorm3Pack16 = 1000156015,
    G10X6B10X6R10X63Plane444Unorm3Pack16 = 1000156016,
    R12X4UnormPack16 = 1000156017,
    R12X4G12X4Unorm2Pack16 = 1000156018,
    R12X4G12X4B12X4A12X4Unorm4Pack16 = 1000156019,
    G12X4B12X4G12X4R12X4422Unorm4Pack16 = 1000156020,
    B12X4G12X4R12X4G12X4422Unorm4Pack16 = 1000156021,
    G12X4B12X4R12X43Plane420Unorm3Pack16 = 1000156022,
    G12X4B12X4R12X42Plane420Unorm3Pack16 = 1000156023,
    G12X4B12X4R12X43Plane422Unorm3Pack16 = 1000156024,
    G12X4B12X4R12X42Plane422Unorm3Pack16 = 1000156025,
    G12X4B12X4R12X43Plane444Unorm3Pack16 = 1000156026,
    G16B16G16R16422Unorm = 1000156027,
    B16G16R16G16422Unorm = 1000156028,
    G16B16R163Plane420Unorm = 1000156029,
    G16B16R162Plane420Unorm = 1000156030,
    G16B16R163Plane422Unorm = 1000156031,
    G16B16R162Plane422Unorm = 1000156032,
    G16B16R163Plane444Unorm = 1000156033,
};
enum class FrontFace : uint32_t {
    CounterClockwise = 0,
    Clockwise = 1,
};
enum class ImageLayout : uint32_t {
    Undefined = 0,
    General = 1,
    ColorAttachmentOptimal = 2,
    DepthStencilAttachmentOptimal = 3,
    DepthStencilReadOnlyOptimal = 4,
    ShaderReadOnlyOptimal = 5,
    TransferSrcOptimal = 6,
    TransferDstOptimal = 7,
    Preinitialized = 8,
    PresentSrcKHR = 1000001002,
    SharedPresentKHR = 1000111000,
    ShadingRateOptimalNV = 1000164003,
    FragmentDensityMapOptimalEXT = 1000218000,
    DepthReadOnlyStencilAttachmentOptimal = 1000117000,
    DepthAttachmentStencilReadOnlyOptimal = 1000117001,
    DepthAttachmentOptimal = 1000241000,
    DepthReadOnlyOptimal = 1000241001,
    StencilAttachmentOptimal = 1000241002,
    StencilReadOnlyOptimal = 1000241003,
};
enum class ImageTiling : uint32_t {
    Optimal = 0,
    Linear = 1,
    DrmFormatModifierEXT = 1000158000,
};
enum class ImageType : uint32_t {
    e1D = 0,
    e2D = 1,
    e3D = 2,
};
enum class ImageViewType : uint32_t {
    e1D = 0,
    e2D = 1,
    e3D = 2,
    Cube = 3,
    e1DArray = 4,
    e2DArray = 5,
    CubeArray = 6,
};
enum class SharingMode : uint32_t {
    Exclusive = 0,
    Concurrent = 1,
};
enum class IndexType : uint32_t {
    Uint16 = 0,
    Uint32 = 1,
    NoneKHR = 1000165000,
    Uint8EXT = 1000265000,
};
enum class LogicOp : uint32_t {
    Clear = 0,
    And = 1,
    AndReverse = 2,
    Copy = 3,
    AndInverted = 4,
    NoOp = 5,
    Xor = 6,
    Or = 7,
    Nor = 8,
    Equivalent = 9,
    Invert = 10,
    OrReverse = 11,
    CopyInverted = 12,
    OrInverted = 13,
    Nand = 14,
    Set = 15,
};
enum class PhysicalDeviceType : uint32_t {
    Other = 0,
    IntegratedGpu = 1,
    DiscreteGpu = 2,
    VirtualGpu = 3,
    Cpu = 4,
};
enum class PipelineBindPoint : uint32_t {
    Graphics = 0,
    Compute = 1,
    RayTracingKHR = 1000165000,
};
enum class PrimitiveTopology : uint32_t {
    PointList = 0,
    LineList = 1,
    LineStrip = 2,
    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,
    LineListWithAdjacency = 6,
    LineStripWithAdjacency = 7,
    TriangleListWithAdjacency = 8,
    TriangleStripWithAdjacency = 9,
    PatchList = 10,
};
enum class QueryType : uint32_t {
    Occlusion = 0,
    PipelineStatistics = 1,
    Timestamp = 2,
    TransformFeedbackStreamEXT = 1000028004,
    PerformanceQueryKHR = 1000116000,
    AccelerationStructureCompactedSizeKHR = 1000150000,
    AccelerationStructureSerializationSizeKHR = 1000150001,
    AccelerationStructureCompactedSizeNV = 1000165000,
    PerformanceQueryINTEL = 1000210000,
};
enum class SubpassContents : uint32_t {
    Inline = 0,
    SecondaryCommandBuffers = 1,
};
enum class Result : int32_t {
    Success = 0,
    NotReady = 1,
    Timeout = 2,
    EventSet = 3,
    EventReset = 4,
    Incomplete = 5,
    ErrorOutOfHostMemory = -1,
    ErrorOutOfDeviceMemory = -2,
    ErrorInitializationFailed = -3,
    ErrorDeviceLost = -4,
    ErrorMemoryMapFailed = -5,
    ErrorLayerNotPresent = -6,
    ErrorExtensionNotPresent = -7,
    ErrorFeatureNotPresent = -8,
    ErrorIncompatibleDriver = -9,
    ErrorTooManyObjects = -10,
    ErrorFormatNotSupported = -11,
    ErrorFragmentedPool = -12,
    ErrorUnknown = -13,
    ErrorSurfaceLostKHR = -1000000000,
    ErrorNativeWindowInUseKHR = -1000000001,
    SuboptimalKHR = 1000001003,
    ErrorOutOfDateKHR = -1000001004,
    ErrorIncompatibleDisplayKHR = -1000003001,
    ErrorValidationFailedEXT = -1000011001,
    ErrorInvalidShaderNV = -1000012000,
    ErrorInvalidDrmFormatModifierPlaneLayoutEXT = -1000158000,
    ErrorNotPermittedEXT = -1000174001,
    ErrorFullScreenExclusiveModeLostEXT = -1000255000,
    ThreadIdleKHR = 1000268000,
    ThreadDoneKHR = 1000268001,
    OperationDeferredKHR = 1000268002,
    OperationNotDeferredKHR = 1000268003,
    PipelineCompileRequiredEXT = 1000297000,
    ErrorOutOfPoolMemory = -1000069000,
    ErrorInvalidExternalHandle = -1000072003,
    ErrorFragmentation = -1000161000,
    ErrorInvalidOpaqueCaptureAddress = -1000257000,
};
enum class StencilOp : uint32_t {
    Keep = 0,
    Zero = 1,
    Replace = 2,
    IncrementAndClamp = 3,
    DecrementAndClamp = 4,
    Invert = 5,
    IncrementAndWrap = 6,
    DecrementAndWrap = 7,
};
enum class StructureType : uint32_t {
    ApplicationInfo = 0,
    InstanceCreateInfo = 1,
    DeviceQueueCreateInfo = 2,
    DeviceCreateInfo = 3,
    SubmitInfo = 4,
    MemoryAllocateInfo = 5,
    MappedMemoryRange = 6,
    BindSparseInfo = 7,
    FenceCreateInfo = 8,
    SemaphoreCreateInfo = 9,
    EventCreateInfo = 10,
    QueryPoolCreateInfo = 11,
    BufferCreateInfo = 12,
    BufferViewCreateInfo = 13,
    ImageCreateInfo = 14,
    ImageViewCreateInfo = 15,
    ShaderModuleCreateInfo = 16,
    PipelineCacheCreateInfo = 17,
    PipelineShaderStageCreateInfo = 18,
    PipelineVertexInputStateCreateInfo = 19,
    PipelineInputAssemblyStateCreateInfo = 20,
    PipelineTessellationStateCreateInfo = 21,
    PipelineViewportStateCreateInfo = 22,
    PipelineRasterizationStateCreateInfo = 23,
    PipelineMultisampleStateCreateInfo = 24,
    PipelineDepthStencilStateCreateInfo = 25,
    PipelineColorBlendStateCreateInfo = 26,
    PipelineDynamicStateCreateInfo = 27,
    GraphicsPipelineCreateInfo = 28,
    ComputePipelineCreateInfo = 29,
    PipelineLayoutCreateInfo = 30,
    SamplerCreateInfo = 31,
    DescriptorSetLayoutCreateInfo = 32,
    DescriptorPoolCreateInfo = 33,
    DescriptorSetAllocateInfo = 34,
    WriteDescriptorSet = 35,
    CopyDescriptorSet = 36,
    FramebufferCreateInfo = 37,
    RenderPassCreateInfo = 38,
    CommandPoolCreateInfo = 39,
    CommandBufferAllocateInfo = 40,
    CommandBufferInheritanceInfo = 41,
    CommandBufferBeginInfo = 42,
    RenderPassBeginInfo = 43,
    BufferMemoryBarrier = 44,
    ImageMemoryBarrier = 45,
    MemoryBarrier = 46,
    LoaderInstanceCreateInfo = 47,
    LoaderDeviceCreateInfo = 48,
    SwapchainCreateInfoKHR = 1000001000,
    PresentInfoKHR = 1000001001,
    DeviceGroupPresentCapabilitiesKHR = 1000060007,
    ImageSwapchainCreateInfoKHR = 1000060008,
    BindImageMemorySwapchainInfoKHR = 1000060009,
    AcquireNextImageInfoKHR = 1000060010,
    DeviceGroupPresentInfoKHR = 1000060011,
    DeviceGroupSwapchainCreateInfoKHR = 1000060012,
    DisplayModeCreateInfoKHR = 1000002000,
    DisplaySurfaceCreateInfoKHR = 1000002001,
    DisplayPresentInfoKHR = 1000003000,
    XlibSurfaceCreateInfoKHR = 1000004000,
    XcbSurfaceCreateInfoKHR = 1000005000,
    WaylandSurfaceCreateInfoKHR = 1000006000,
    AndroidSurfaceCreateInfoKHR = 1000008000,
    Win32SurfaceCreateInfoKHR = 1000009000,
    DebugReportCallbackCreateInfoEXT = 1000011000,
    PipelineRasterizationStateRasterizationOrderAMD = 1000018000,
    DebugMarkerObjectNameInfoEXT = 1000022000,
    DebugMarkerObjectTagInfoEXT = 1000022001,
    DebugMarkerMarkerInfoEXT = 1000022002,
    DedicatedAllocationImageCreateInfoNV = 1000026000,
    DedicatedAllocationBufferCreateInfoNV = 1000026001,
    DedicatedAllocationMemoryAllocateInfoNV = 1000026002,
    PhysicalDeviceTransformFeedbackFeaturesEXT = 1000028000,
    PhysicalDeviceTransformFeedbackPropertiesEXT = 1000028001,
    PipelineRasterizationStateStreamCreateInfoEXT = 1000028002,
    ImageViewHandleInfoNVX = 1000030000,
    ImageViewAddressPropertiesNVX = 1000030001,
    TextureLodGatherFormatPropertiesAMD = 1000041000,
    StreamDescriptorSurfaceCreateInfoGGP = 1000049000,
    PhysicalDeviceCornerSampledImageFeaturesNV = 1000050000,
    ExternalMemoryImageCreateInfoNV = 1000056000,
    ExportMemoryAllocateInfoNV = 1000056001,
    ImportMemoryWin32HandleInfoNV = 1000057000,
    ExportMemoryWin32HandleInfoNV = 1000057001,
    Win32KeyedMutexAcquireReleaseInfoNV = 1000058000,
    ValidationFlagsEXT = 1000061000,
    ViSurfaceCreateInfoNN = 1000062000,
    PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT = 1000066000,
    ImageViewAstcDecodeModeEXT = 1000067000,
    PhysicalDeviceAstcDecodeFeaturesEXT = 1000067001,
    ImportMemoryWin32HandleInfoKHR = 1000073000,
    ExportMemoryWin32HandleInfoKHR = 1000073001,
    MemoryWin32HandlePropertiesKHR = 1000073002,
    MemoryGetWin32HandleInfoKHR = 1000073003,
    ImportMemoryFdInfoKHR = 1000074000,
    MemoryFdPropertiesKHR = 1000074001,
    MemoryGetFdInfoKHR = 1000074002,
    Win32KeyedMutexAcquireReleaseInfoKHR = 1000075000,
    ImportSemaphoreWin32HandleInfoKHR = 1000078000,
    ExportSemaphoreWin32HandleInfoKHR = 1000078001,
    D3D12FenceSubmitInfoKHR = 1000078002,
    SemaphoreGetWin32HandleInfoKHR = 1000078003,
    ImportSemaphoreFdInfoKHR = 1000079000,
    SemaphoreGetFdInfoKHR = 1000079001,
    PhysicalDevicePushDescriptorPropertiesKHR = 1000080000,
    CommandBufferInheritanceConditionalRenderingInfoEXT = 1000081000,
    PhysicalDeviceConditionalRenderingFeaturesEXT = 1000081001,
    ConditionalRenderingBeginInfoEXT = 1000081002,
    PresentRegionsKHR = 1000084000,
    PipelineViewportWScalingStateCreateInfoNV = 1000087000,
    SurfaceCapabilities2EXT = 1000090000,
    DisplayPowerInfoEXT = 1000091000,
    DeviceEventInfoEXT = 1000091001,
    DisplayEventInfoEXT = 1000091002,
    SwapchainCounterCreateInfoEXT = 1000091003,
    PresentTimesInfoGOOGLE = 1000092000,
    PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX = 1000097000,
    PipelineViewportSwizzleStateCreateInfoNV = 1000098000,
    PhysicalDeviceDiscardRectanglePropertiesEXT = 1000099000,
    PipelineDiscardRectangleStateCreateInfoEXT = 1000099001,
    PhysicalDeviceConservativeRasterizationPropertiesEXT = 1000101000,
    PipelineRasterizationConservativeStateCreateInfoEXT = 1000101001,
    PhysicalDeviceDepthClipEnableFeaturesEXT = 1000102000,
    PipelineRasterizationDepthClipStateCreateInfoEXT = 1000102001,
    HdrMetadataEXT = 1000105000,
    SharedPresentSurfaceCapabilitiesKHR = 1000111000,
    ImportFenceWin32HandleInfoKHR = 1000114000,
    ExportFenceWin32HandleInfoKHR = 1000114001,
    FenceGetWin32HandleInfoKHR = 1000114002,
    ImportFenceFdInfoKHR = 1000115000,
    FenceGetFdInfoKHR = 1000115001,
    PhysicalDevicePerformanceQueryFeaturesKHR = 1000116000,
    PhysicalDevicePerformanceQueryPropertiesKHR = 1000116001,
    QueryPoolPerformanceCreateInfoKHR = 1000116002,
    PerformanceQuerySubmitInfoKHR = 1000116003,
    AcquireProfilingLockInfoKHR = 1000116004,
    PerformanceCounterKHR = 1000116005,
    PerformanceCounterDescriptionKHR = 1000116006,
    PhysicalDeviceSurfaceInfo2KHR = 1000119000,
    SurfaceCapabilities2KHR = 1000119001,
    SurfaceFormat2KHR = 1000119002,
    DisplayProperties2KHR = 1000121000,
    DisplayPlaneProperties2KHR = 1000121001,
    DisplayModeProperties2KHR = 1000121002,
    DisplayPlaneInfo2KHR = 1000121003,
    DisplayPlaneCapabilities2KHR = 1000121004,
    IosSurfaceCreateInfoMVK = 1000122000,
    MacosSurfaceCreateInfoMVK = 1000123000,
    DebugUtilsObjectNameInfoEXT = 1000128000,
    DebugUtilsObjectTagInfoEXT = 1000128001,
    DebugUtilsLabelEXT = 1000128002,
    DebugUtilsMessengerCallbackDataEXT = 1000128003,
    DebugUtilsMessengerCreateInfoEXT = 1000128004,
    AndroidHardwareBufferUsageANDROID = 1000129000,
    AndroidHardwareBufferPropertiesANDROID = 1000129001,
    AndroidHardwareBufferFormatPropertiesANDROID = 1000129002,
    ImportAndroidHardwareBufferInfoANDROID = 1000129003,
    MemoryGetAndroidHardwareBufferInfoANDROID = 1000129004,
    ExternalFormatANDROID = 1000129005,
    PhysicalDeviceInlineUniformBlockFeaturesEXT = 1000138000,
    PhysicalDeviceInlineUniformBlockPropertiesEXT = 1000138001,
    WriteDescriptorSetInlineUniformBlockEXT = 1000138002,
    DescriptorPoolInlineUniformBlockCreateInfoEXT = 1000138003,
    SampleLocationsInfoEXT = 1000143000,
    RenderPassSampleLocationsBeginInfoEXT = 1000143001,
    PipelineSampleLocationsStateCreateInfoEXT = 1000143002,
    PhysicalDeviceSampleLocationsPropertiesEXT = 1000143003,
    MultisamplePropertiesEXT = 1000143004,
    PhysicalDeviceBlendOperationAdvancedFeaturesEXT = 1000148000,
    PhysicalDeviceBlendOperationAdvancedPropertiesEXT = 1000148001,
    PipelineColorBlendAdvancedStateCreateInfoEXT = 1000148002,
    PipelineCoverageToColorStateCreateInfoNV = 1000149000,
    WriteDescriptorSetAccelerationStructureKHR = 1000150007,
    AccelerationStructureBuildGeometryInfoKHR = 1000150000,
    AccelerationStructureDeviceAddressInfoKHR = 1000150002,
    AccelerationStructureGeometryAabbsDataKHR = 1000150003,
    AccelerationStructureGeometryInstancesDataKHR = 1000150004,
    AccelerationStructureGeometryTrianglesDataKHR = 1000150005,
    AccelerationStructureGeometryKHR = 1000150006,
    AccelerationStructureVersionInfoKHR = 1000150009,
    CopyAccelerationStructureInfoKHR = 1000150010,
    CopyAccelerationStructureToMemoryInfoKHR = 1000150011,
    CopyMemoryToAccelerationStructureInfoKHR = 1000150012,
    PhysicalDeviceAccelerationStructureFeaturesKHR = 1000150013,
    PhysicalDeviceAccelerationStructurePropertiesKHR = 1000150014,
    AccelerationStructureCreateInfoKHR = 1000150017,
    AccelerationStructureBuildSizesInfoKHR = 1000150020,
    PhysicalDeviceRayTracingPipelineFeaturesKHR = 1000347000,
    PhysicalDeviceRayTracingPipelinePropertiesKHR = 1000347001,
    RayTracingPipelineCreateInfoKHR = 1000150015,
    RayTracingShaderGroupCreateInfoKHR = 1000150016,
    RayTracingPipelineInterfaceCreateInfoKHR = 1000150018,
    PhysicalDeviceRayQueryFeaturesKHR = 1000348013,
    PipelineCoverageModulationStateCreateInfoNV = 1000152000,
    PhysicalDeviceShaderSmBuiltinsFeaturesNV = 1000154000,
    PhysicalDeviceShaderSmBuiltinsPropertiesNV = 1000154001,
    DrmFormatModifierPropertiesListEXT = 1000158000,
    PhysicalDeviceImageDrmFormatModifierInfoEXT = 1000158002,
    ImageDrmFormatModifierListCreateInfoEXT = 1000158003,
    ImageDrmFormatModifierExplicitCreateInfoEXT = 1000158004,
    ImageDrmFormatModifierPropertiesEXT = 1000158005,
    ValidationCacheCreateInfoEXT = 1000160000,
    ShaderModuleValidationCacheCreateInfoEXT = 1000160001,
    PhysicalDevicePortabilitySubsetFeaturesKHR = 1000163000,
    PhysicalDevicePortabilitySubsetPropertiesKHR = 1000163001,
    PipelineViewportShadingRateImageStateCreateInfoNV = 1000164000,
    PhysicalDeviceShadingRateImageFeaturesNV = 1000164001,
    PhysicalDeviceShadingRateImagePropertiesNV = 1000164002,
    PipelineViewportCoarseSampleOrderStateCreateInfoNV = 1000164005,
    RayTracingPipelineCreateInfoNV = 1000165000,
    AccelerationStructureCreateInfoNV = 1000165001,
    GeometryNV = 1000165003,
    GeometryTrianglesNV = 1000165004,
    GeometryAabbNV = 1000165005,
    BindAccelerationStructureMemoryInfoNV = 1000165006,
    WriteDescriptorSetAccelerationStructureNV = 1000165007,
    AccelerationStructureMemoryRequirementsInfoNV = 1000165008,
    PhysicalDeviceRayTracingPropertiesNV = 1000165009,
    RayTracingShaderGroupCreateInfoNV = 1000165011,
    AccelerationStructureInfoNV = 1000165012,
    PhysicalDeviceRepresentativeFragmentTestFeaturesNV = 1000166000,
    PipelineRepresentativeFragmentTestStateCreateInfoNV = 1000166001,
    PhysicalDeviceImageViewImageFormatInfoEXT = 1000170000,
    FilterCubicImageViewImageFormatPropertiesEXT = 1000170001,
    DeviceQueueGlobalPriorityCreateInfoEXT = 1000174000,
    ImportMemoryHostPointerInfoEXT = 1000178000,
    MemoryHostPointerPropertiesEXT = 1000178001,
    PhysicalDeviceExternalMemoryHostPropertiesEXT = 1000178002,
    PhysicalDeviceShaderClockFeaturesKHR = 1000181000,
    PipelineCompilerControlCreateInfoAMD = 1000183000,
    CalibratedTimestampInfoEXT = 1000184000,
    PhysicalDeviceShaderCorePropertiesAMD = 1000185000,
    DeviceMemoryOverallocationCreateInfoAMD = 1000189000,
    PhysicalDeviceVertexAttributeDivisorPropertiesEXT = 1000190000,
    PipelineVertexInputDivisorStateCreateInfoEXT = 1000190001,
    PhysicalDeviceVertexAttributeDivisorFeaturesEXT = 1000190002,
    PresentFrameTokenGGP = 1000191000,
    PipelineCreationFeedbackCreateInfoEXT = 1000192000,
    PhysicalDeviceComputeShaderDerivativesFeaturesNV = 1000201000,
    PhysicalDeviceMeshShaderFeaturesNV = 1000202000,
    PhysicalDeviceMeshShaderPropertiesNV = 1000202001,
    PhysicalDeviceFragmentShaderBarycentricFeaturesNV = 1000203000,
    PhysicalDeviceShaderImageFootprintFeaturesNV = 1000204000,
    PipelineViewportExclusiveScissorStateCreateInfoNV = 1000205000,
    PhysicalDeviceExclusiveScissorFeaturesNV = 1000205002,
    CheckpointDataNV = 1000206000,
    QueueFamilyCheckpointPropertiesNV = 1000206001,
    PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL = 1000209000,
    QueryPoolPerformanceQueryCreateInfoINTEL = 1000210000,
    InitializePerformanceApiInfoINTEL = 1000210001,
    PerformanceMarkerInfoINTEL = 1000210002,
    PerformanceStreamMarkerInfoINTEL = 1000210003,
    PerformanceOverrideInfoINTEL = 1000210004,
    PerformanceConfigurationAcquireInfoINTEL = 1000210005,
    PhysicalDevicePciBusInfoPropertiesEXT = 1000212000,
    DisplayNativeHdrSurfaceCapabilitiesAMD = 1000213000,
    SwapchainDisplayNativeHdrCreateInfoAMD = 1000213001,
    ImagepipeSurfaceCreateInfoFUCHSIA = 1000214000,
    PhysicalDeviceShaderTerminateInvocationFeaturesKHR = 1000215000,
    MetalSurfaceCreateInfoEXT = 1000217000,
    PhysicalDeviceFragmentDensityMapFeaturesEXT = 1000218000,
    PhysicalDeviceFragmentDensityMapPropertiesEXT = 1000218001,
    RenderPassFragmentDensityMapCreateInfoEXT = 1000218002,
    PhysicalDeviceSubgroupSizeControlPropertiesEXT = 1000225000,
    PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT = 1000225001,
    PhysicalDeviceSubgroupSizeControlFeaturesEXT = 1000225002,
    FragmentShadingRateAttachmentInfoKHR = 1000226000,
    PipelineFragmentShadingRateStateCreateInfoKHR = 1000226001,
    PhysicalDeviceFragmentShadingRatePropertiesKHR = 1000226002,
    PhysicalDeviceFragmentShadingRateFeaturesKHR = 1000226003,
    PhysicalDeviceFragmentShadingRateKHR = 1000226004,
    PhysicalDeviceShaderCoreProperties2AMD = 1000227000,
    PhysicalDeviceCoherentMemoryFeaturesAMD = 1000229000,
    PhysicalDeviceShaderImageAtomicInt64FeaturesEXT = 1000234000,
    PhysicalDeviceMemoryBudgetPropertiesEXT = 1000237000,
    PhysicalDeviceMemoryPriorityFeaturesEXT = 1000238000,
    MemoryPriorityAllocateInfoEXT = 1000238001,
    SurfaceProtectedCapabilitiesKHR = 1000239000,
    PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV = 1000240000,
    PhysicalDeviceBufferDeviceAddressFeaturesEXT = 1000244000,
    BufferDeviceAddressCreateInfoEXT = 1000244002,
    PhysicalDeviceToolPropertiesEXT = 1000245000,
    ValidationFeaturesEXT = 1000247000,
    PhysicalDeviceCooperativeMatrixFeaturesNV = 1000249000,
    CooperativeMatrixPropertiesNV = 1000249001,
    PhysicalDeviceCooperativeMatrixPropertiesNV = 1000249002,
    PhysicalDeviceCoverageReductionModeFeaturesNV = 1000250000,
    PipelineCoverageReductionStateCreateInfoNV = 1000250001,
    FramebufferMixedSamplesCombinationNV = 1000250002,
    PhysicalDeviceFragmentShaderInterlockFeaturesEXT = 1000251000,
    PhysicalDeviceYcbcrImageArraysFeaturesEXT = 1000252000,
    SurfaceFullScreenExclusiveInfoEXT = 1000255000,
    SurfaceCapabilitiesFullScreenExclusiveEXT = 1000255002,
    SurfaceFullScreenExclusiveWin32InfoEXT = 1000255001,
    HeadlessSurfaceCreateInfoEXT = 1000256000,
    PhysicalDeviceLineRasterizationFeaturesEXT = 1000259000,
    PipelineRasterizationLineStateCreateInfoEXT = 1000259001,
    PhysicalDeviceLineRasterizationPropertiesEXT = 1000259002,
    PhysicalDeviceShaderAtomicFloatFeaturesEXT = 1000260000,
    PhysicalDeviceIndexTypeUint8FeaturesEXT = 1000265000,
    PhysicalDeviceExtendedDynamicStateFeaturesEXT = 1000267000,
    PhysicalDevicePipelineExecutablePropertiesFeaturesKHR = 1000269000,
    PipelineInfoKHR = 1000269001,
    PipelineExecutablePropertiesKHR = 1000269002,
    PipelineExecutableInfoKHR = 1000269003,
    PipelineExecutableStatisticKHR = 1000269004,
    PipelineExecutableInternalRepresentationKHR = 1000269005,
    PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT = 1000276000,
    PhysicalDeviceDeviceGeneratedCommandsPropertiesNV = 1000277000,
    GraphicsShaderGroupCreateInfoNV = 1000277001,
    GraphicsPipelineShaderGroupsCreateInfoNV = 1000277002,
    IndirectCommandsLayoutTokenNV = 1000277003,
    IndirectCommandsLayoutCreateInfoNV = 1000277004,
    GeneratedCommandsInfoNV = 1000277005,
    GeneratedCommandsMemoryRequirementsInfoNV = 1000277006,
    PhysicalDeviceDeviceGeneratedCommandsFeaturesNV = 1000277007,
    PhysicalDeviceTexelBufferAlignmentFeaturesEXT = 1000281000,
    PhysicalDeviceTexelBufferAlignmentPropertiesEXT = 1000281001,
    CommandBufferInheritanceRenderPassTransformInfoQCOM = 1000282000,
    RenderPassTransformBeginInfoQCOM = 1000282001,
    PhysicalDeviceDeviceMemoryReportFeaturesEXT = 1000284000,
    DeviceDeviceMemoryReportCreateInfoEXT = 1000284001,
    DeviceMemoryReportCallbackDataEXT = 1000284002,
    PhysicalDeviceRobustness2FeaturesEXT = 1000286000,
    PhysicalDeviceRobustness2PropertiesEXT = 1000286001,
    SamplerCustomBorderColorCreateInfoEXT = 1000287000,
    PhysicalDeviceCustomBorderColorPropertiesEXT = 1000287001,
    PhysicalDeviceCustomBorderColorFeaturesEXT = 1000287002,
    PipelineLibraryCreateInfoKHR = 1000290000,
    PhysicalDevicePrivateDataFeaturesEXT = 1000295000,
    DevicePrivateDataCreateInfoEXT = 1000295001,
    PrivateDataSlotCreateInfoEXT = 1000295002,
    PhysicalDevicePipelineCreationCacheControlFeaturesEXT = 1000297000,
    PhysicalDeviceDiagnosticsConfigFeaturesNV = 1000300000,
    DeviceDiagnosticsConfigCreateInfoNV = 1000300001,
    PhysicalDeviceFragmentShadingRateEnumsPropertiesNV = 1000326000,
    PhysicalDeviceFragmentShadingRateEnumsFeaturesNV = 1000326001,
    PipelineFragmentShadingRateEnumStateCreateInfoNV = 1000326002,
    PhysicalDeviceFragmentDensityMap2FeaturesEXT = 1000332000,
    PhysicalDeviceFragmentDensityMap2PropertiesEXT = 1000332001,
    CopyCommandTransformInfoQCOM = 1000333000,
    PhysicalDeviceImageRobustnessFeaturesEXT = 1000335000,
    CopyBufferInfo2KHR = 1000337000,
    CopyImageInfo2KHR = 1000337001,
    CopyBufferToImageInfo2KHR = 1000337002,
    CopyImageToBufferInfo2KHR = 1000337003,
    BlitImageInfo2KHR = 1000337004,
    ResolveImageInfo2KHR = 1000337005,
    BufferCopy2KHR = 1000337006,
    ImageCopy2KHR = 1000337007,
    ImageBlit2KHR = 1000337008,
    BufferImageCopy2KHR = 1000337009,
    ImageResolve2KHR = 1000337010,
    PhysicalDevice4444FormatsFeaturesEXT = 1000340000,
    DirectfbSurfaceCreateInfoEXT = 1000346000,
    PhysicalDeviceSubgroupProperties = 1000094000,
    BindBufferMemoryInfo = 1000157000,
    BindImageMemoryInfo = 1000157001,
    PhysicalDevice16BitStorageFeatures = 1000083000,
    MemoryDedicatedRequirements = 1000127000,
    MemoryDedicatedAllocateInfo = 1000127001,
    MemoryAllocateFlagsInfo = 1000060000,
    DeviceGroupRenderPassBeginInfo = 1000060003,
    DeviceGroupCommandBufferBeginInfo = 1000060004,
    DeviceGroupSubmitInfo = 1000060005,
    DeviceGroupBindSparseInfo = 1000060006,
    BindBufferMemoryDeviceGroupInfo = 1000060013,
    BindImageMemoryDeviceGroupInfo = 1000060014,
    PhysicalDeviceGroupProperties = 1000070000,
    DeviceGroupDeviceCreateInfo = 1000070001,
    BufferMemoryRequirementsInfo2 = 1000146000,
    ImageMemoryRequirementsInfo2 = 1000146001,
    ImageSparseMemoryRequirementsInfo2 = 1000146002,
    MemoryRequirements2 = 1000146003,
    SparseImageMemoryRequirements2 = 1000146004,
    PhysicalDeviceFeatures2 = 1000059000,
    PhysicalDeviceProperties2 = 1000059001,
    FormatProperties2 = 1000059002,
    ImageFormatProperties2 = 1000059003,
    PhysicalDeviceImageFormatInfo2 = 1000059004,
    QueueFamilyProperties2 = 1000059005,
    PhysicalDeviceMemoryProperties2 = 1000059006,
    SparseImageFormatProperties2 = 1000059007,
    PhysicalDeviceSparseImageFormatInfo2 = 1000059008,
    PhysicalDevicePointClippingProperties = 1000117000,
    RenderPassInputAttachmentAspectCreateInfo = 1000117001,
    ImageViewUsageCreateInfo = 1000117002,
    PipelineTessellationDomainOriginStateCreateInfo = 1000117003,
    RenderPassMultiviewCreateInfo = 1000053000,
    PhysicalDeviceMultiviewFeatures = 1000053001,
    PhysicalDeviceMultiviewProperties = 1000053002,
    PhysicalDeviceVariablePointersFeatures = 1000120000,
    ProtectedSubmitInfo = 1000145000,
    PhysicalDeviceProtectedMemoryFeatures = 1000145001,
    PhysicalDeviceProtectedMemoryProperties = 1000145002,
    DeviceQueueInfo2 = 1000145003,
    SamplerYcbcrConversionCreateInfo = 1000156000,
    SamplerYcbcrConversionInfo = 1000156001,
    BindImagePlaneMemoryInfo = 1000156002,
    ImagePlaneMemoryRequirementsInfo = 1000156003,
    PhysicalDeviceSamplerYcbcrConversionFeatures = 1000156004,
    SamplerYcbcrConversionImageFormatProperties = 1000156005,
    DescriptorUpdateTemplateCreateInfo = 1000085000,
    PhysicalDeviceExternalImageFormatInfo = 1000071000,
    ExternalImageFormatProperties = 1000071001,
    PhysicalDeviceExternalBufferInfo = 1000071002,
    ExternalBufferProperties = 1000071003,
    PhysicalDeviceIdProperties = 1000071004,
    ExternalMemoryBufferCreateInfo = 1000072000,
    ExternalMemoryImageCreateInfo = 1000072001,
    ExportMemoryAllocateInfo = 1000072002,
    PhysicalDeviceExternalFenceInfo = 1000112000,
    ExternalFenceProperties = 1000112001,
    ExportFenceCreateInfo = 1000113000,
    ExportSemaphoreCreateInfo = 1000077000,
    PhysicalDeviceExternalSemaphoreInfo = 1000076000,
    ExternalSemaphoreProperties = 1000076001,
    PhysicalDeviceMaintenance3Properties = 1000168000,
    DescriptorSetLayoutSupport = 1000168001,
    PhysicalDeviceShaderDrawParametersFeatures = 1000063000,
    PhysicalDeviceVulkan11Features = 49,
    PhysicalDeviceVulkan11Properties = 50,
    PhysicalDeviceVulkan12Features = 51,
    PhysicalDeviceVulkan12Properties = 52,
    ImageFormatListCreateInfo = 1000147000,
    AttachmentDescription2 = 1000109000,
    AttachmentReference2 = 1000109001,
    SubpassDescription2 = 1000109002,
    SubpassDependency2 = 1000109003,
    RenderPassCreateInfo2 = 1000109004,
    SubpassBeginInfo = 1000109005,
    SubpassEndInfo = 1000109006,
    PhysicalDevice8BitStorageFeatures = 1000177000,
    PhysicalDeviceDriverProperties = 1000196000,
    PhysicalDeviceShaderAtomicInt64Features = 1000180000,
    PhysicalDeviceShaderFloat16Int8Features = 1000082000,
    PhysicalDeviceFloatControlsProperties = 1000197000,
    DescriptorSetLayoutBindingFlagsCreateInfo = 1000161000,
    PhysicalDeviceDescriptorIndexingFeatures = 1000161001,
    PhysicalDeviceDescriptorIndexingProperties = 1000161002,
    DescriptorSetVariableDescriptorCountAllocateInfo = 1000161003,
    DescriptorSetVariableDescriptorCountLayoutSupport = 1000161004,
    PhysicalDeviceDepthStencilResolveProperties = 1000199000,
    SubpassDescriptionDepthStencilResolve = 1000199001,
    PhysicalDeviceScalarBlockLayoutFeatures = 1000221000,
    ImageStencilUsageCreateInfo = 1000246000,
    PhysicalDeviceSamplerFilterMinmaxProperties = 1000130000,
    SamplerReductionModeCreateInfo = 1000130001,
    PhysicalDeviceVulkanMemoryModelFeatures = 1000211000,
    PhysicalDeviceImagelessFramebufferFeatures = 1000108000,
    FramebufferAttachmentsCreateInfo = 1000108001,
    FramebufferAttachmentImageInfo = 1000108002,
    RenderPassAttachmentBeginInfo = 1000108003,
    PhysicalDeviceUniformBufferStandardLayoutFeatures = 1000253000,
    PhysicalDeviceShaderSubgroupExtendedTypesFeatures = 1000175000,
    PhysicalDeviceSeparateDepthStencilLayoutsFeatures = 1000241000,
    AttachmentReferenceStencilLayout = 1000241001,
    AttachmentDescriptionStencilLayout = 1000241002,
    PhysicalDeviceHostQueryResetFeatures = 1000261000,
    PhysicalDeviceTimelineSemaphoreFeatures = 1000207000,
    PhysicalDeviceTimelineSemaphoreProperties = 1000207001,
    SemaphoreTypeCreateInfo = 1000207002,
    TimelineSemaphoreSubmitInfo = 1000207003,
    SemaphoreWaitInfo = 1000207004,
    SemaphoreSignalInfo = 1000207005,
    PhysicalDeviceBufferDeviceAddressFeatures = 1000257000,
    BufferDeviceAddressInfo = 1000244001,
    BufferOpaqueCaptureAddressCreateInfo = 1000257002,
    MemoryOpaqueCaptureAddressAllocateInfo = 1000257003,
    DeviceMemoryOpaqueCaptureAddressInfo = 1000257004,
};
enum class SystemAllocationScope : uint32_t {
    Command = 0,
    Object = 1,
    Cache = 2,
    Device = 3,
    Instance = 4,
};
enum class InternalAllocationType : uint32_t {
    Executable = 0,
};
enum class SamplerAddressMode : uint32_t {
    Repeat = 0,
    MirroredRepeat = 1,
    ClampToEdge = 2,
    ClampToBorder = 3,
    MirrorClampToEdge = 4,
};
enum class Filter : uint32_t {
    Nearest = 0,
    Linear = 1,
    CubicIMG = 1000015000,
};
enum class SamplerMipmapMode : uint32_t {
    Nearest = 0,
    Linear = 1,
};
enum class VertexInputRate : uint32_t {
    Vertex = 0,
    Instance = 1,
};
enum class ObjectType : uint32_t {
    Unknown = 0,
    Instance = 1,
    PhysicalDevice = 2,
    Device = 3,
    Queue = 4,
    Semaphore = 5,
    CommandBuffer = 6,
    Fence = 7,
    DeviceMemory = 8,
    Buffer = 9,
    Image = 10,
    Event = 11,
    QueryPool = 12,
    BufferView = 13,
    ImageView = 14,
    ShaderModule = 15,
    PipelineCache = 16,
    PipelineLayout = 17,
    RenderPass = 18,
    Pipeline = 19,
    DescriptorSetLayout = 20,
    Sampler = 21,
    DescriptorPool = 22,
    DescriptorSet = 23,
    Framebuffer = 24,
    CommandPool = 25,
    SurfaceKHR = 1000000000,
    SwapchainKHR = 1000001000,
    DisplayKHR = 1000002000,
    DisplayModeKHR = 1000002001,
    DebugReportCallbackEXT = 1000011000,
    DebugUtilsMessengerEXT = 1000128000,
    AccelerationStructureKHR = 1000150000,
    ValidationCacheEXT = 1000160000,
    AccelerationStructureNV = 1000165000,
    PerformanceConfigurationINTEL = 1000210000,
    DeferredOperationKHR = 1000268000,
    IndirectCommandsLayoutNV = 1000277000,
    PrivateDataSlotEXT = 1000295000,
    SamplerYcbcrConversion = 1000156000,
    DescriptorUpdateTemplate = 1000085000,
};
enum class IndirectCommandsTokenTypeNV : uint32_t {
    ShaderGroupNV = 0,
    StateFlagsNV = 1,
    IndexBufferNV = 2,
    VertexBufferNV = 3,
    PushConstantNV = 4,
    DrawIndexedNV = 5,
    DrawNV = 6,
    DrawTasksNV = 7,
};
enum class DescriptorUpdateTemplateType : uint32_t {
    DescriptorSet = 0,
    PushDescriptorsKHR = 1,
};
using DescriptorUpdateTemplateTypeKHR = DescriptorUpdateTemplateType;
enum class ViewportCoordinateSwizzleNV : uint32_t {
    PositiveXNV = 0,
    NegativeXNV = 1,
    PositiveYNV = 2,
    NegativeYNV = 3,
    PositiveZNV = 4,
    NegativeZNV = 5,
    PositiveWNV = 6,
    NegativeWNV = 7,
};
enum class DiscardRectangleModeEXT : uint32_t {
    InclusiveEXT = 0,
    ExclusiveEXT = 1,
};
enum class PointClippingBehavior : uint32_t {
    AllClipPlanes = 0,
    UserClipPlanesOnly = 1,
};
using PointClippingBehaviorKHR = PointClippingBehavior;
enum class CoverageModulationModeNV : uint32_t {
    NoneNV = 0,
    RgbNV = 1,
    AlphaNV = 2,
    RgbaNV = 3,
};
enum class CoverageReductionModeNV : uint32_t {
    MergeNV = 0,
    TruncateNV = 1,
};
enum class ValidationCacheHeaderVersionEXT : uint32_t {
    OneEXT = 1,
};
enum class ShaderInfoTypeAMD : uint32_t {
    StatisticsAMD = 0,
    BinaryAMD = 1,
    DisassemblyAMD = 2,
};
enum class QueueGlobalPriorityEXT : uint32_t {
    LowEXT = 128,
    MediumEXT = 256,
    HighEXT = 512,
    RealtimeEXT = 1024,
};
enum class TimeDomainEXT : uint32_t {
    DeviceEXT = 0,
    ClockMonotonicEXT = 1,
    ClockMonotonicRawEXT = 2,
    QueryPerformanceCounterEXT = 3,
};
enum class ConservativeRasterizationModeEXT : uint32_t {
    DisabledEXT = 0,
    OverestimateEXT = 1,
    UnderestimateEXT = 2,
};
enum class SemaphoreType : uint32_t {
    Binary = 0,
    Timeline = 1,
};
using SemaphoreTypeKHR = SemaphoreType;
enum class BuildAccelerationStructureModeKHR : uint32_t {
    BuildKHR = 0,
    UpdateKHR = 1,
};
enum class CopyAccelerationStructureModeKHR : uint32_t {
    CloneKHR = 0,
    CompactKHR = 1,
    SerializeKHR = 2,
    DeserializeKHR = 3,
};
using CopyAccelerationStructureModeNV = CopyAccelerationStructureModeKHR;
enum class AccelerationStructureTypeKHR : uint32_t {
    TopLevelKHR = 0,
    BottomLevelKHR = 1,
    GenericKHR = 2,
};
using AccelerationStructureTypeNV = AccelerationStructureTypeKHR;
enum class GeometryTypeKHR : uint32_t {
    TrianglesKHR = 0,
    AabbsKHR = 1,
    InstancesKHR = 2,
};
using GeometryTypeNV = GeometryTypeKHR;
enum class RayTracingShaderGroupTypeKHR : uint32_t {
    GeneralKHR = 0,
    TrianglesHitGroupKHR = 1,
    ProceduralHitGroupKHR = 2,
};
using RayTracingShaderGroupTypeNV = RayTracingShaderGroupTypeKHR;
enum class AccelerationStructureMemoryRequirementsTypeNV : uint32_t {
    ObjectNV = 0,
    BuildScratchNV = 1,
    UpdateScratchNV = 2,
};
enum class AccelerationStructureBuildTypeKHR : uint32_t {
    HostKHR = 0,
    DeviceKHR = 1,
    HostOrDeviceKHR = 2,
};
enum class AccelerationStructureCompatibilityKHR : uint32_t {
    CompatibleKHR = 0,
    IncompatibleKHR = 1,
};
enum class ShaderGroupShaderKHR : uint32_t {
    GeneralKHR = 0,
    ClosestHitKHR = 1,
    AnyHitKHR = 2,
    IntersectionKHR = 3,
};
enum class MemoryOverallocationBehaviorAMD : uint32_t {
    DefaultAMD = 0,
    AllowedAMD = 1,
    DisallowedAMD = 2,
};
enum class ScopeNV : uint32_t {
    DeviceNV = 1,
    WorkgroupNV = 2,
    SubgroupNV = 3,
    QueueFamilyNV = 5,
};
enum class ComponentTypeNV : uint32_t {
    Float16NV = 0,
    Float32NV = 1,
    Float64NV = 2,
    Sint8NV = 3,
    Sint16NV = 4,
    Sint32NV = 5,
    Sint64NV = 6,
    Uint8NV = 7,
    Uint16NV = 8,
    Uint32NV = 9,
    Uint64NV = 10,
};
enum class PerformanceCounterScopeKHR : uint32_t {
    CommandBufferKHR = 0,
    RenderPassKHR = 1,
    CommandKHR = 2,
};
enum class PerformanceCounterUnitKHR : uint32_t {
    GenericKHR = 0,
    PercentageKHR = 1,
    NanosecondsKHR = 2,
    BytesKHR = 3,
    BytesPerSecondKHR = 4,
    KelvinKHR = 5,
    WattsKHR = 6,
    VoltsKHR = 7,
    AmpsKHR = 8,
    HertzKHR = 9,
    CyclesKHR = 10,
};
enum class PerformanceCounterStorageKHR : uint32_t {
    Int32KHR = 0,
    Int64KHR = 1,
    Uint32KHR = 2,
    Uint64KHR = 3,
    Float32KHR = 4,
    Float64KHR = 5,
};
enum class PerformanceConfigurationTypeINTEL : uint32_t {
    CommandQueueMetricsDiscoveryActivatedINTEL = 0,
};
enum class QueryPoolSamplingModeINTEL : uint32_t {
    ManualINTEL = 0,
};
enum class PerformanceOverrideTypeINTEL : uint32_t {
    NullHardwareINTEL = 0,
    FlushGpuCachesINTEL = 1,
};
enum class PerformanceParameterTypeINTEL : uint32_t {
    HwCountersSupportedINTEL = 0,
    StreamMarkerValidBitsINTEL = 1,
};
enum class PerformanceValueTypeINTEL : uint32_t {
    Uint32INTEL = 0,
    Uint64INTEL = 1,
    FloatINTEL = 2,
    BoolINTEL = 3,
    StringINTEL = 4,
};
enum class LineRasterizationModeEXT : uint32_t {
    DefaultEXT = 0,
    RectangularEXT = 1,
    BresenhamEXT = 2,
    RectangularSmoothEXT = 3,
};
enum class FragmentShadingRateNV : uint32_t {
    e1InvocationPerPixelNV = 0,
    e1InvocationPer1X2PixelsNV = 1,
    e1InvocationPer2X1PixelsNV = 4,
    e1InvocationPer2X2PixelsNV = 5,
    e1InvocationPer2X4PixelsNV = 6,
    e1InvocationPer4X2PixelsNV = 9,
    e1InvocationPer4X4PixelsNV = 10,
    e2InvocationsPerPixelNV = 11,
    e4InvocationsPerPixelNV = 12,
    e8InvocationsPerPixelNV = 13,
    e16InvocationsPerPixelNV = 14,
    NoInvocationsNV = 15,
};
enum class FragmentShadingRateTypeNV : uint32_t {
    FragmentSizeNV = 0,
    EnumsNV = 1,
};
enum class ColorSpaceKHR : uint32_t {
    SrgbNonlinearKHR = 0,
    DisplayP3NonlinearEXT = 1000104001,
    ExtendedSrgbLinearEXT = 1000104002,
    DisplayP3LinearEXT = 1000104003,
    DciP3NonlinearEXT = 1000104004,
    Bt709LinearEXT = 1000104005,
    Bt709NonlinearEXT = 1000104006,
    Bt2020LinearEXT = 1000104007,
    Hdr10St2084EXT = 1000104008,
    DolbyvisionEXT = 1000104009,
    Hdr10HlgEXT = 1000104010,
    AdobergbLinearEXT = 1000104011,
    AdobergbNonlinearEXT = 1000104012,
    PassThroughEXT = 1000104013,
    ExtendedSrgbNonlinearEXT = 1000104014,
    DisplayNativeAMD = 1000213000,
};
enum class PresentModeKHR : uint32_t {
    ImmediateKHR = 0,
    MailboxKHR = 1,
    FifoKHR = 2,
    FifoRelaxedKHR = 3,
    SharedDemandRefreshKHR = 1000111000,
    SharedContinuousRefreshKHR = 1000111001,
};
enum class DebugReportObjectTypeEXT : uint32_t {
    UnknownEXT = 0,
    InstanceEXT = 1,
    PhysicalDeviceEXT = 2,
    DeviceEXT = 3,
    QueueEXT = 4,
    SemaphoreEXT = 5,
    CommandBufferEXT = 6,
    FenceEXT = 7,
    DeviceMemoryEXT = 8,
    BufferEXT = 9,
    ImageEXT = 10,
    EventEXT = 11,
    QueryPoolEXT = 12,
    BufferViewEXT = 13,
    ImageViewEXT = 14,
    ShaderModuleEXT = 15,
    PipelineCacheEXT = 16,
    PipelineLayoutEXT = 17,
    RenderPassEXT = 18,
    PipelineEXT = 19,
    DescriptorSetLayoutEXT = 20,
    SamplerEXT = 21,
    DescriptorPoolEXT = 22,
    DescriptorSetEXT = 23,
    FramebufferEXT = 24,
    CommandPoolEXT = 25,
    SurfaceKhrEXT = 26,
    SwapchainKhrEXT = 27,
    DebugReportCallbackExtEXT = 28,
    DisplayKhrEXT = 29,
    DisplayModeKhrEXT = 30,
    ValidationCacheExtEXT = 33,
    SamplerYcbcrConversionEXT = 1000156000,
    DescriptorUpdateTemplateEXT = 1000085000,
    AccelerationStructureKhrEXT = 1000150000,
    AccelerationStructureNvEXT = 1000165000,
};
enum class DeviceMemoryReportEventTypeEXT : uint32_t {
    AllocateEXT = 0,
    FreeEXT = 1,
    ImportEXT = 2,
    UnimportEXT = 3,
    AllocationFailedEXT = 4,
};
enum class RasterizationOrderAMD : uint32_t {
    StrictAMD = 0,
    RelaxedAMD = 1,
};
enum class ValidationCheckEXT : uint32_t {
    AllEXT = 0,
    ShadersEXT = 1,
};
enum class ValidationFeatureEnableEXT : uint32_t {
    GpuAssistedEXT = 0,
    GpuAssistedReserveBindingSlotEXT = 1,
    BestPracticesEXT = 2,
    DebugPrintfEXT = 3,
    SynchronizationValidationEXT = 4,
};
enum class ValidationFeatureDisableEXT : uint32_t {
    AllEXT = 0,
    ShadersEXT = 1,
    ThreadSafetyEXT = 2,
    ApiParametersEXT = 3,
    ObjectLifetimesEXT = 4,
    CoreChecksEXT = 5,
    UniqueHandlesEXT = 6,
};
enum class DisplayPowerStateEXT : uint32_t {
    OffEXT = 0,
    SuspendEXT = 1,
    OnEXT = 2,
};
enum class DeviceEventTypeEXT : uint32_t {
    DisplayHotplugEXT = 0,
};
enum class DisplayEventTypeEXT : uint32_t {
    FirstPixelOutEXT = 0,
};
enum class TessellationDomainOrigin : uint32_t {
    UpperLeft = 0,
    LowerLeft = 1,
};
using TessellationDomainOriginKHR = TessellationDomainOrigin;
enum class SamplerYcbcrModelConversion : uint32_t {
    RgbIdentity = 0,
    YcbcrIdentity = 1,
    Ycbcr709 = 2,
    Ycbcr601 = 3,
    Ycbcr2020 = 4,
};
using SamplerYcbcrModelConversionKHR = SamplerYcbcrModelConversion;
enum class SamplerYcbcrRange : uint32_t {
    ItuFull = 0,
    ItuNarrow = 1,
};
using SamplerYcbcrRangeKHR = SamplerYcbcrRange;
enum class ChromaLocation : uint32_t {
    CositedEven = 0,
    Midpoint = 1,
};
using ChromaLocationKHR = ChromaLocation;
enum class SamplerReductionMode : uint32_t {
    WeightedAverage = 0,
    Min = 1,
    Max = 2,
};
using SamplerReductionModeEXT = SamplerReductionMode;
enum class BlendOverlapEXT : uint32_t {
    UncorrelatedEXT = 0,
    DisjointEXT = 1,
    ConjointEXT = 2,
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum class FullScreenExclusiveEXT : uint32_t {
    DefaultEXT = 0,
    AllowedEXT = 1,
    DisallowedEXT = 2,
    ApplicationControlledEXT = 3,
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
enum class ShaderFloatControlsIndependence : uint32_t {
    e32BitOnly = 0,
    All = 1,
    None = 2,
};
using ShaderFloatControlsIndependenceKHR = ShaderFloatControlsIndependence;
enum class FragmentShadingRateCombinerOpKHR : uint32_t {
    KeepKHR = 0,
    ReplaceKHR = 1,
    MinKHR = 2,
    MaxKHR = 3,
    MulKHR = 4,
};
enum class VendorId : uint32_t {
    VIV = 0x10001,
    VSI = 0x10002,
    Kazan = 0x10003,
    Codeplay = 0x10004,
    MESA = 0x10005,
};
enum class DriverId : uint32_t {
    AmdProprietary = 1,
    AmdOpenSource = 2,
    MesaRadv = 3,
    NvidiaProprietary = 4,
    IntelProprietaryWindows = 5,
    IntelOpenSourceMESA = 6,
    ImaginationProprietary = 7,
    QualcommProprietary = 8,
    ArmProprietary = 9,
    GoogleSwiftshader = 10,
    GgpProprietary = 11,
    BroadcomProprietary = 12,
    MesaLlvmpipe = 13,
    Moltenvk = 14,
};
using DriverIdKHR = DriverId;
enum class ShadingRatePaletteEntryNV : uint32_t {
    NoInvocationsNV = 0,
    e16InvocationsPerPixelNV = 1,
    e8InvocationsPerPixelNV = 2,
    e4InvocationsPerPixelNV = 3,
    e2InvocationsPerPixelNV = 4,
    e1InvocationPerPixelNV = 5,
    e1InvocationPer2X1PixelsNV = 6,
    e1InvocationPer1X2PixelsNV = 7,
    e1InvocationPer2X2PixelsNV = 8,
    e1InvocationPer4X2PixelsNV = 9,
    e1InvocationPer2X4PixelsNV = 10,
    e1InvocationPer4X4PixelsNV = 11,
};
enum class CoarseSampleOrderTypeNV : uint32_t {
    DefaultNV = 0,
    CustomNV = 1,
    PixelMajorNV = 2,
    SampleMajorNV = 3,
};
enum class PipelineExecutableStatisticFormatKHR : uint32_t {
    Bool32KHR = 0,
    Int64KHR = 1,
    Uint64KHR = 2,
    Float64KHR = 3,
};
enum class PipelineCacheCreateFlagBits: uint32_t {
    ExternallySynchronizedBitEXT = 1,
};
enum class QueueFlagBits: uint32_t {
    Graphics = 1,
    Compute = 2,
    Transfer = 4,
    SparseBinding = 8,
    Protected = 16,
};
enum class CullModeFlagBits: uint32_t {
    None = 0,
    Front = 1,
    Back = 2,
    FrontAndBack = 0x00000003,
};
enum class RenderPassCreateFlagBits: uint32_t {
    TransformBitQCOM = 2,
};
enum class DeviceQueueCreateFlagBits: uint32_t {
    Protected = 1,
};
enum class MemoryPropertyFlagBits: uint32_t {
    DeviceLocal = 1,
    HostVisible = 2,
    HostCoherent = 4,
    HostCached = 8,
    LazilyAllocated = 16,
    DeviceCoherentBitAMD = 64,
    DeviceUncachedBitAMD = 128,
    Protected = 32,
};
enum class MemoryHeapFlagBits: uint32_t {
    DeviceLocal = 1,
    MultiInstance = 2,
};
enum class AccessFlagBits: uint32_t {
    IndirectCommandRead = 1,
    IndexRead = 2,
    VertexAttributeRead = 4,
    UniformRead = 8,
    InputAttachmentRead = 16,
    ShaderRead = 32,
    ShaderWrite = 64,
    ColorAttachmentRead = 128,
    ColorAttachmentWrite = 256,
    DepthStencilAttachmentRead = 512,
    DepthStencilAttachmentWrite = 1024,
    TransferRead = 2048,
    TransferWrite = 4096,
    HostRead = 8192,
    HostWrite = 16384,
    MemoryRead = 32768,
    MemoryWrite = 65536,
    TransformFeedbackWriteBitEXT = 33554432,
    TransformFeedbackCounterReadBitEXT = 67108864,
    TransformFeedbackCounterWriteBitEXT = 134217728,
    ConditionalRenderingReadBitEXT = 1048576,
    ColorAttachmentReadNoncoherentBitEXT = 524288,
    AccelerationStructureReadBitKHR = 2097152,
    AccelerationStructureWriteBitKHR = 4194304,
    ShadingRateImageReadBitNV = 8388608,
    FragmentDensityMapReadBitEXT = 16777216,
    CommandPreprocessReadBitNV = 131072,
    CommandPreprocessWriteBitNV = 262144,
};
enum class BufferUsageFlagBits: uint32_t {
    TransferSrc = 1,
    TransferDst = 2,
    UniformTexelBuffer = 4,
    StorageTexelBuffer = 8,
    UniformBuffer = 16,
    StorageBuffer = 32,
    IndexBuffer = 64,
    VertexBuffer = 128,
    IndirectBuffer = 256,
    TransformFeedbackBufferBitEXT = 2048,
    TransformFeedbackCounterBufferBitEXT = 4096,
    ConditionalRenderingBitEXT = 512,
    AccelerationStructureBuildInputReadOnlyBitKHR = 524288,
    AccelerationStructureStorageBitKHR = 1048576,
    ShaderBindingTableBitKHR = 1024,
    ShaderDeviceAddress = 131072,
};
enum class BufferCreateFlagBits: uint32_t {
    SparseBinding = 1,
    SparseResidency = 2,
    SparseAliased = 4,
    Protected = 8,
    DeviceAddressCaptureReplay = 16,
};
enum class ShaderStageFlagBits: uint32_t {
    Vertex = 1,
    TessellationControl = 2,
    TessellationEvaluation = 4,
    Geometry = 8,
    Fragment = 16,
    Compute = 32,
    AllGraphics = 0x0000001F,
    All = 0x7FFFFFFF,
    RaygenBitKHR = 256,
    AnyHitBitKHR = 512,
    ClosestHitBitKHR = 1024,
    MissBitKHR = 2048,
    IntersectionBitKHR = 4096,
    CallableBitKHR = 8192,
    TaskBitNV = 64,
    MeshBitNV = 128,
};
enum class ImageUsageFlagBits: uint32_t {
    TransferSrc = 1,
    TransferDst = 2,
    Sampled = 4,
    Storage = 8,
    ColorAttachment = 16,
    DepthStencilAttachment = 32,
    TransientAttachment = 64,
    InputAttachment = 128,
    ShadingRateImageBitNV = 256,
    FragmentDensityMapBitEXT = 512,
};
enum class ImageCreateFlagBits: uint32_t {
    SparseBinding = 1,
    SparseResidency = 2,
    SparseAliased = 4,
    MutableFormat = 8,
    CubeCompatible = 16,
    CornerSampledBitNV = 8192,
    SampleLocationsCompatibleDepthBitEXT = 4096,
    SubsampledBitEXT = 16384,
    Alias = 1024,
    SplitInstanceBindRegions = 64,
    e2DArrayCompatible = 32,
    BlockTexelViewCompatible = 128,
    ExtendedUsage = 256,
    Protected = 2048,
    Disjoint = 512,
};
enum class ImageViewCreateFlagBits: uint32_t {
    FragmentDensityMapDynamicBitEXT = 1,
    FragmentDensityMapDeferredBitEXT = 2,
};
enum class SamplerCreateFlagBits: uint32_t {
    SubsampledBitEXT = 1,
    SubsampledCoarseReconstructionBitEXT = 2,
};
enum class PipelineCreateFlagBits: uint32_t {
    DisableOptimization = 1,
    AllowDerivatives = 2,
    Derivative = 4,
    RayTracingNoNullAnyHitShadersBitKHR = 16384,
    RayTracingNoNullClosestHitShadersBitKHR = 32768,
    RayTracingNoNullMissShadersBitKHR = 65536,
    RayTracingNoNullIntersectionShadersBitKHR = 131072,
    RayTracingSkipTrianglesBitKHR = 4096,
    RayTracingSkipAabbsBitKHR = 8192,
    RayTracingShaderGroupHandleCaptureReplayBitKHR = 524288,
    DeferCompileBitNV = 32,
    CaptureStatisticsBitKHR = 64,
    CaptureInternalRepresentationsBitKHR = 128,
    IndirectBindableBitNV = 262144,
    LibraryBitKHR = 2048,
    FailOnPipelineCompileRequiredBitEXT = 256,
    EarlyReturnOnFailureBitEXT = 512,
    ViewIndexFromDeviceIndex = 8,
    DispatchBase = 16,
};
enum class PipelineShaderStageCreateFlagBits: uint32_t {
    AllowVaryingSubgroupSizeBitEXT = 1,
    RequireFullSubgroupsBitEXT = 2,
};
enum class ColorComponentFlagBits: uint32_t {
    R = 1,
    G = 2,
    B = 4,
    A = 8,
};
enum class FenceCreateFlagBits: uint32_t {
    Signaled = 1,
};
enum class FormatFeatureFlagBits: uint32_t {
    SampledImage = 1,
    StorageImage = 2,
    StorageImageAtomic = 4,
    UniformTexelBuffer = 8,
    StorageTexelBuffer = 16,
    StorageTexelBufferAtomic = 32,
    VertexBuffer = 64,
    ColorAttachment = 128,
    ColorAttachmentBlend = 256,
    DepthStencilAttachment = 512,
    BlitSrc = 1024,
    BlitDst = 2048,
    SampledImageFilterLinear = 4096,
    SampledImageFilterCubicBitIMG = 8192,
    AccelerationStructureVertexBufferBitKHR = 536870912,
    FragmentDensityMapBitEXT = 16777216,
    FragmentShadingRateAttachmentBitKHR = 1073741824,
    TransferSrc = 16384,
    TransferDst = 32768,
    MidpointChromaSamples = 131072,
    SampledImageYcbcrConversionLinearFilter = 262144,
    SampledImageYcbcrConversionSeparateReconstructionFilter = 524288,
    SampledImageYcbcrConversionChromaReconstructionExplicit = 1048576,
    SampledImageYcbcrConversionChromaReconstructionExplicitForceable = 2097152,
    Disjoint = 4194304,
    CositedChromaSamples = 8388608,
    SampledImageFilterMinmax = 65536,
};
enum class QueryControlFlagBits: uint32_t {
    Precise = 1,
};
enum class QueryResultFlagBits: uint32_t {
    e64 = 1,
    Wait = 2,
    WithAvailability = 4,
    Partial = 8,
};
enum class CommandBufferUsageFlagBits: uint32_t {
    OneTimeSubmit = 1,
    RenderPassContinue = 2,
    SimultaneousUse = 4,
};
enum class QueryPipelineStatisticFlagBits: uint32_t {
    InputAssemblyVertices = 1,
    InputAssemblyPrimitives = 2,
    VertexShaderInvocations = 4,
    GeometryShaderInvocations = 8,
    GeometryShaderPrimitives = 16,
    ClippingInvocations = 32,
    ClippingPrimitives = 64,
    FragmentShaderInvocations = 128,
    TessellationControlShaderPatches = 256,
    TessellationEvaluationShaderInvocations = 512,
    ComputeShaderInvocations = 1024,
};
enum class ImageAspectFlagBits: uint32_t {
    Color = 1,
    Depth = 2,
    Stencil = 4,
    Metadata = 8,
    MemoryPlane0BitEXT = 128,
    MemoryPlane1BitEXT = 256,
    MemoryPlane2BitEXT = 512,
    MemoryPlane3BitEXT = 1024,
    Plane0 = 16,
    Plane1 = 32,
    Plane2 = 64,
};
enum class SparseImageFormatFlagBits: uint32_t {
    SingleMiptail = 1,
    AlignedMipSize = 2,
    NonstandardBlockSize = 4,
};
enum class SparseMemoryBindFlagBits: uint32_t {
    Metadata = 1,
};
enum class PipelineStageFlagBits: uint32_t {
    TopOfPipe = 1,
    DrawIndirect = 2,
    VertexInput = 4,
    VertexShader = 8,
    TessellationControlShader = 16,
    TessellationEvaluationShader = 32,
    GeometryShader = 64,
    FragmentShader = 128,
    EarlyFragmentTests = 256,
    LateFragmentTests = 512,
    ColorAttachmentOutput = 1024,
    ComputeShader = 2048,
    Transfer = 4096,
    BottomOfPipe = 8192,
    Host = 16384,
    AllGraphics = 32768,
    AllCommands = 65536,
    TransformFeedbackBitEXT = 16777216,
    ConditionalRenderingBitEXT = 262144,
    AccelerationStructureBuildBitKHR = 33554432,
    RayTracingShaderBitKHR = 2097152,
    ShadingRateImageBitNV = 4194304,
    TaskShaderBitNV = 524288,
    MeshShaderBitNV = 1048576,
    FragmentDensityProcessBitEXT = 8388608,
    CommandPreprocessBitNV = 131072,
};
enum class CommandPoolCreateFlagBits: uint32_t {
    Transient = 1,
    ResetCommandBuffer = 2,
    Protected = 4,
};
enum class CommandPoolResetFlagBits: uint32_t {
    ReleaseResources = 1,
};
enum class CommandBufferResetFlagBits: uint32_t {
    ReleaseResources = 1,
};
enum class SampleCountFlagBits: uint32_t {
    e1 = 1,
    e2 = 2,
    e4 = 4,
    e8 = 8,
    e16 = 16,
    e32 = 32,
    e64 = 64,
};
enum class AttachmentDescriptionFlagBits: uint32_t {
    MayAlias = 1,
};
enum class StencilFaceFlagBits: uint32_t {
    Front = 1,
    Back = 2,
    FrontAndBack = 0x00000003,
};
enum class DescriptorPoolCreateFlagBits: uint32_t {
    FreeDescriptorSet = 1,
    UpdateAfterBind = 2,
};
enum class DependencyFlagBits: uint32_t {
    ByRegion = 1,
    DeviceGroup = 4,
    ViewLocal = 2,
};
enum class SemaphoreWaitFlagBits: uint32_t {
    Any = 1,
};
enum class DisplayPlaneAlphaFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    GlobalBitKHR = 2,
    PerPixelBitKHR = 4,
    PerPixelPremultipliedBitKHR = 8,
};
enum class CompositeAlphaFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    PreMultipliedBitKHR = 2,
    PostMultipliedBitKHR = 4,
    InheritBitKHR = 8,
};
enum class SurfaceTransformFlagBitsKHR: uint32_t {
    IdentityBitKHR = 1,
    Rotate90BitKHR = 2,
    Rotate180BitKHR = 4,
    Rotate270BitKHR = 8,
    HorizontalMirrorBitKHR = 16,
    HorizontalMirrorRotate90BitKHR = 32,
    HorizontalMirrorRotate180BitKHR = 64,
    HorizontalMirrorRotate270BitKHR = 128,
    InheritBitKHR = 256,
};
enum class DebugReportFlagBitsEXT: uint32_t {
    InformationBitEXT = 1,
    WarningBitEXT = 2,
    PerformanceWarningBitEXT = 4,
    ErrorBitEXT = 8,
    DebugBitEXT = 16,
};
enum class ExternalMemoryHandleTypeFlagBitsNV: uint32_t {
    OpaqueWin32BitNV = 1,
    OpaqueWin32KmtBitNV = 2,
    D3D11ImageBitNV = 4,
    D3D11ImageKmtBitNV = 8,
};
enum class ExternalMemoryFeatureFlagBitsNV: uint32_t {
    DedicatedOnlyBitNV = 1,
    ExportableBitNV = 2,
    ImportableBitNV = 4,
};
enum class SubgroupFeatureFlagBits: uint32_t {
    Basic = 1,
    Vote = 2,
    Arithmetic = 4,
    Ballot = 8,
    Shuffle = 16,
    ShuffleRelative = 32,
    Clustered = 64,
    Quad = 128,
    PartitionedBitNV = 256,
};
enum class IndirectCommandsLayoutUsageFlagBitsNV: uint32_t {
    ExplicitPreprocessBitNV = 1,
    IndexedSequencesBitNV = 2,
    UnorderedSequencesBitNV = 4,
};
enum class IndirectStateFlagBitsNV: uint32_t {
    FlagFrontfaceBitNV = 1,
};
enum class PrivateDataSlotCreateFlagBitsEXT: uint32_t {
};
enum class DescriptorSetLayoutCreateFlagBits: uint32_t {
    PushDescriptorBitKHR = 1,
    UpdateAfterBindPool = 2,
};
enum class ExternalMemoryHandleTypeFlagBits: uint32_t {
    OpaqueFd = 1,
    OpaqueWin32 = 2,
    OpaqueWin32Kmt = 4,
    D3D11Texture = 8,
    D3D11TextureKmt = 16,
    D3D12Heap = 32,
    D3D12Resource = 64,
    DmaBufBitEXT = 512,
    AndroidHardwareBufferBitANDROID = 1024,
    HostAllocationBitEXT = 128,
    HostMappedForeignMemoryBitEXT = 256,
};
enum class ExternalMemoryFeatureFlagBits: uint32_t {
    DedicatedOnly = 1,
    Exportable = 2,
    Importable = 4,
};
enum class ExternalSemaphoreHandleTypeFlagBits: uint32_t {
    OpaqueFd = 1,
    OpaqueWin32 = 2,
    OpaqueWin32Kmt = 4,
    D3D12Fence = 8,
    D3D11Fence = D3D12Fence,
    SyncFd = 16,
};
enum class ExternalSemaphoreFeatureFlagBits: uint32_t {
    Exportable = 1,
    Importable = 2,
};
enum class SemaphoreImportFlagBits: uint32_t {
    Temporary = 1,
};
enum class ExternalFenceHandleTypeFlagBits: uint32_t {
    OpaqueFd = 1,
    OpaqueWin32 = 2,
    OpaqueWin32Kmt = 4,
    SyncFd = 8,
};
enum class ExternalFenceFeatureFlagBits: uint32_t {
    Exportable = 1,
    Importable = 2,
};
enum class FenceImportFlagBits: uint32_t {
    Temporary = 1,
};
enum class SurfaceCounterFlagBitsEXT: uint32_t {
    VblankBitEXT = 1,
    VblankEXT = VblankBitEXT,
};
enum class PeerMemoryFeatureFlagBits: uint32_t {
    CopySrc = 1,
    CopyDst = 2,
    GenericSrc = 4,
    GenericDst = 8,
};
enum class MemoryAllocateFlagBits: uint32_t {
    DeviceMask = 1,
    DeviceAddress = 2,
    DeviceAddressCaptureReplay = 4,
};
enum class DeviceGroupPresentModeFlagBitsKHR: uint32_t {
    LocalBitKHR = 1,
    RemoteBitKHR = 2,
    SumBitKHR = 4,
    LocalMultiDeviceBitKHR = 8,
};
enum class SwapchainCreateFlagBitsKHR: uint32_t {
    SplitInstanceBindRegionsBitKHR = 1,
    ProtectedBitKHR = 2,
    MutableFormatBitKHR = 4,
};
enum class SubpassDescriptionFlagBits: uint32_t {
    PerViewAttributesBitNVX = 1,
    PerViewPositionXOnlyBitNVX = 2,
    FragmentRegionBitQCOM = 4,
    ShaderResolveBitQCOM = 8,
};
enum class DebugUtilsMessageSeverityFlagBitsEXT: uint32_t {
    VerboseBitEXT = 1,
    InfoBitEXT = 16,
    WarningBitEXT = 256,
    ErrorBitEXT = 4096,
};
enum class DebugUtilsMessageTypeFlagBitsEXT: uint32_t {
    GeneralBitEXT = 1,
    ValidationBitEXT = 2,
    PerformanceBitEXT = 4,
};
enum class DescriptorBindingFlagBits: uint32_t {
    UpdateAfterBind = 1,
    UpdateUnusedWhilePending = 2,
    PartiallyBound = 4,
    VariableDescriptorCount = 8,
};
enum class ConditionalRenderingFlagBitsEXT: uint32_t {
    InvertedBitEXT = 1,
};
enum class ResolveModeFlagBits: uint32_t {
    None = 0,
    SampleZero = 1,
    Average = 2,
    Min = 4,
    Max = 8,
};
enum class GeometryInstanceFlagBitsKHR: uint32_t {
    TriangleFacingCullDisableBitKHR = 1,
    TriangleFrontCounterclockwiseBitKHR = 2,
    ForceOpaqueBitKHR = 4,
    ForceNoOpaqueBitKHR = 8,
};
enum class GeometryFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    NoDuplicateAnyHitInvocationBitKHR = 2,
};
enum class BuildAccelerationStructureFlagBitsKHR: uint32_t {
    AllowUpdateBitKHR = 1,
    AllowCompactionBitKHR = 2,
    PreferFastTraceBitKHR = 4,
    PreferFastBuildBitKHR = 8,
    LowMemoryBitKHR = 16,
};
enum class AccelerationStructureCreateFlagBitsKHR: uint32_t {
    DeviceAddressCaptureReplayBitKHR = 1,
};
enum class FramebufferCreateFlagBits: uint32_t {
    Imageless = 1,
};
enum class DeviceDiagnosticsConfigFlagBitsNV: uint32_t {
    EnableShaderDebugInfoBitNV = 1,
    EnableResourceTrackingBitNV = 2,
    EnableAutomaticCheckpointsBitNV = 4,
};
enum class PipelineCreationFeedbackFlagBitsEXT: uint32_t {
    ValidBitEXT = 1,
    ApplicationPipelineCacheHitBitEXT = 2,
    BasePipelineAccelerationBitEXT = 4,
};
enum class PerformanceCounterDescriptionFlagBitsKHR: uint32_t {
    PerformanceImpactingBitKHR = 1,
    PerformanceImpactingKHR = PerformanceImpactingBitKHR,
    ConcurrentlyImpactedBitKHR = 2,
    ConcurrentlyImpactedKHR = ConcurrentlyImpactedBitKHR,
};
enum class AcquireProfilingLockFlagBitsKHR: uint32_t {
};
enum class ShaderCorePropertiesFlagBitsAMD: uint32_t {
};
enum class ShaderModuleCreateFlagBits: uint32_t {
};
enum class PipelineCompilerControlFlagBitsAMD: uint32_t {
};
enum class ToolPurposeFlagBitsEXT: uint32_t {
    ValidationBitEXT = 1,
    ProfilingBitEXT = 2,
    TracingBitEXT = 4,
    AdditionalFeaturesBitEXT = 8,
    ModifyingFeaturesBitEXT = 16,
    DebugReportingBitEXT = 32,
    DebugMarkersBitEXT = 64,
};
enum class QueryPoolCreateFlagBits: uint32_t { };
enum class PipelineLayoutCreateFlagBits: uint32_t { };
enum class PipelineDepthStencilStateCreateFlagBits: uint32_t { };
enum class PipelineDynamicStateCreateFlagBits: uint32_t { };
enum class PipelineColorBlendStateCreateFlagBits: uint32_t { };
enum class PipelineMultisampleStateCreateFlagBits: uint32_t { };
enum class PipelineRasterizationStateCreateFlagBits: uint32_t { };
enum class PipelineViewportStateCreateFlagBits: uint32_t { };
enum class PipelineTessellationStateCreateFlagBits: uint32_t { };
enum class PipelineInputAssemblyStateCreateFlagBits: uint32_t { };
enum class PipelineVertexInputStateCreateFlagBits: uint32_t { };
enum class BufferViewCreateFlagBits: uint32_t { };
enum class InstanceCreateFlagBits: uint32_t { };
enum class DeviceCreateFlagBits: uint32_t { };
enum class SemaphoreCreateFlagBits: uint32_t { };
enum class EventCreateFlagBits: uint32_t { };
enum class MemoryMapFlagBits: uint32_t { };
enum class DescriptorPoolResetFlagBits: uint32_t { };
enum class DescriptorUpdateTemplateCreateFlagBits: uint32_t { };
enum class DisplayModeCreateFlagBitsKHR: uint32_t { };
enum class DisplaySurfaceCreateFlagBitsKHR: uint32_t { };
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
enum class AndroidSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
enum class ViSurfaceCreateFlagBitsNN: uint32_t { };
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
enum class WaylandSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum class Win32SurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
enum class XlibSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
enum class XcbSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
enum class DirectFBSurfaceCreateFlagBitsEXT: uint32_t { };
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
enum class IOSSurfaceCreateFlagBitsMVK: uint32_t { };
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
enum class MacOSSurfaceCreateFlagBitsMVK: uint32_t { };
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
enum class MetalSurfaceCreateFlagBitsEXT: uint32_t { };
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
enum class ImagePipeSurfaceCreateFlagBitsFUCHSIA: uint32_t { };
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
enum class StreamDescriptorSurfaceCreateFlagBitsGGP: uint32_t { };
#endif // defined(VK_USE_PLATFORM_GGP)
enum class HeadlessSurfaceCreateFlagBitsEXT: uint32_t { };
enum class CommandPoolTrimFlagBits: uint32_t { };
enum class PipelineViewportSwizzleStateCreateFlagBitsNV: uint32_t { };
enum class PipelineDiscardRectangleStateCreateFlagBitsEXT: uint32_t { };
enum class PipelineCoverageToColorStateCreateFlagBitsNV: uint32_t { };
enum class PipelineCoverageModulationStateCreateFlagBitsNV: uint32_t { };
enum class PipelineCoverageReductionStateCreateFlagBitsNV: uint32_t { };
enum class ValidationCacheCreateFlagBitsEXT: uint32_t { };
enum class DebugUtilsMessengerCreateFlagBitsEXT: uint32_t { };
enum class DebugUtilsMessengerCallbackDataFlagBitsEXT: uint32_t { };
enum class DeviceMemoryReportFlagBitsEXT: uint32_t { };
enum class PipelineRasterizationConservativeStateCreateFlagBitsEXT: uint32_t { };
enum class PipelineRasterizationStateStreamCreateFlagBitsEXT: uint32_t { };
enum class PipelineRasterizationDepthClipStateCreateFlagBitsEXT: uint32_t { };

#define DECLARE_ENUM_FLAG_OPERATORS(FLAG_TYPE, FLAG_BITS, BASE_TYPE)                       \
                                                                                           \
struct FLAG_TYPE {                                                                         \
    BASE_TYPE flags = static_cast<BASE_TYPE>(0);                                           \
                                                                                           \
    constexpr FLAG_TYPE() noexcept = default;                                              \
    constexpr explicit FLAG_TYPE(BASE_TYPE in) noexcept: flags(in){ }                      \
    constexpr FLAG_TYPE(FLAG_BITS in) noexcept: flags(static_cast<BASE_TYPE>(in)){ }       \
    constexpr bool operator==(FLAG_TYPE const& right) const { return flags == right.flags;}\
    constexpr bool operator!=(FLAG_TYPE const& right) const { return flags != right.flags;}\
    constexpr explicit operator BASE_TYPE() const { return flags;}                         \
    constexpr explicit operator bool() const noexcept {                                    \
      return flags != 0;                                                                   \
    }                                                                                      \
};                                                                                         \
constexpr FLAG_TYPE operator|(FLAG_TYPE a, FLAG_TYPE b) noexcept {                         \
    return static_cast<FLAG_TYPE>(a.flags | b.flags);                                      \
}                                                                                          \
constexpr FLAG_TYPE operator&(FLAG_TYPE a, FLAG_TYPE b) noexcept {                         \
    return static_cast<FLAG_TYPE>(a.flags & b.flags);                                      \
}                                                                                          \
constexpr FLAG_TYPE operator^(FLAG_TYPE a, FLAG_TYPE b) noexcept {                         \
    return static_cast<FLAG_TYPE>(a.flags ^ b.flags);                                      \
}                                                                                          \
constexpr FLAG_TYPE operator~(FLAG_TYPE a) noexcept {                                      \
    return static_cast<FLAG_TYPE>(~a.flags);                                               \
}                                                                                          \
constexpr FLAG_TYPE& operator|=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                      \
    a.flags = (a.flags | b.flags);                                                         \
    return a;                                                                              \
}                                                                                          \
constexpr FLAG_TYPE& operator&=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                      \
    a.flags = (a.flags & b.flags);                                                         \
    return a;                                                                              \
}                                                                                          \
constexpr FLAG_TYPE operator^=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                       \
    a.flags = (a.flags ^ b.flags);                                                         \
    return a;                                                                              \
}                                                                                          \
constexpr FLAG_TYPE operator|(FLAG_BITS a, FLAG_BITS b) noexcept {                         \
    return static_cast<FLAG_TYPE>(static_cast<BASE_TYPE>(a) | static_cast<BASE_TYPE>(b));  \
}                                                                                          \
constexpr FLAG_TYPE operator&(FLAG_BITS a, FLAG_BITS b) noexcept {                         \
    return static_cast<FLAG_TYPE>(static_cast<BASE_TYPE>(a) & static_cast<BASE_TYPE>(b));  \
}                                                                                          \
constexpr FLAG_TYPE operator~(FLAG_BITS key) noexcept {                                    \
    return static_cast<FLAG_TYPE>(~static_cast<BASE_TYPE>(key));                           \
}                                                                                          \
constexpr FLAG_TYPE operator^(FLAG_BITS a, FLAG_BITS b) noexcept {                         \
    return static_cast<FLAG_TYPE>(static_cast<BASE_TYPE>(a) ^ static_cast<BASE_TYPE>(b));  \
}                                                                                          \

DECLARE_ENUM_FLAG_OPERATORS(FramebufferCreateFlags, FramebufferCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(QueryPoolCreateFlags, QueryPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(RenderPassCreateFlags, RenderPassCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SamplerCreateFlags, SamplerCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineLayoutCreateFlags, PipelineLayoutCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineCacheCreateFlags, PipelineCacheCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineDepthStencilStateCreateFlags, PipelineDepthStencilStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineDynamicStateCreateFlags, PipelineDynamicStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineColorBlendStateCreateFlags, PipelineColorBlendStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineMultisampleStateCreateFlags, PipelineMultisampleStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineRasterizationStateCreateFlags, PipelineRasterizationStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineViewportStateCreateFlags, PipelineViewportStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineTessellationStateCreateFlags, PipelineTessellationStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineInputAssemblyStateCreateFlags, PipelineInputAssemblyStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineVertexInputStateCreateFlags, PipelineVertexInputStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineShaderStageCreateFlags, PipelineShaderStageCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DescriptorSetLayoutCreateFlags, DescriptorSetLayoutCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(BufferViewCreateFlags, BufferViewCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(InstanceCreateFlags, InstanceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DeviceCreateFlags, DeviceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DeviceQueueCreateFlags, DeviceQueueCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(QueueFlags, QueueFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(MemoryPropertyFlags, MemoryPropertyFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(MemoryHeapFlags, MemoryHeapFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(AccessFlags, AccessFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(BufferUsageFlags, BufferUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(BufferCreateFlags, BufferCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ShaderStageFlags, ShaderStageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ImageUsageFlags, ImageUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ImageCreateFlags, ImageCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ImageViewCreateFlags, ImageViewCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineCreateFlags, PipelineCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ColorComponentFlags, ColorComponentFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(FenceCreateFlags, FenceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SemaphoreCreateFlags, SemaphoreCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(FormatFeatureFlags, FormatFeatureFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(QueryControlFlags, QueryControlFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(QueryResultFlags, QueryResultFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ShaderModuleCreateFlags, ShaderModuleCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(EventCreateFlags, EventCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CommandPoolCreateFlags, CommandPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CommandPoolResetFlags, CommandPoolResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CommandBufferResetFlags, CommandBufferResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CommandBufferUsageFlags, CommandBufferUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(QueryPipelineStatisticFlags, QueryPipelineStatisticFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(MemoryMapFlags, MemoryMapFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ImageAspectFlags, ImageAspectFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SparseMemoryBindFlags, SparseMemoryBindFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SparseImageFormatFlags, SparseImageFormatFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SubpassDescriptionFlags, SubpassDescriptionFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineStageFlags, PipelineStageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SampleCountFlags, SampleCountFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(AttachmentDescriptionFlags, AttachmentDescriptionFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(StencilFaceFlags, StencilFaceFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CullModeFlags, CullModeFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DescriptorPoolCreateFlags, DescriptorPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DescriptorPoolResetFlags, DescriptorPoolResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DependencyFlags, DependencyFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SubgroupFeatureFlags, SubgroupFeatureFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(IndirectCommandsLayoutUsageFlagsNV, IndirectCommandsLayoutUsageFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(IndirectStateFlagsNV, IndirectStateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(GeometryFlagsKHR, GeometryFlagBitsKHR, uint32_t)
using GeometryFlagsNV = GeometryFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(GeometryInstanceFlagsKHR, GeometryInstanceFlagBitsKHR, uint32_t)
using GeometryInstanceFlagsNV = GeometryInstanceFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(BuildAccelerationStructureFlagsKHR, BuildAccelerationStructureFlagBitsKHR, uint32_t)
using BuildAccelerationStructureFlagsNV = BuildAccelerationStructureFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(PrivateDataSlotCreateFlagsEXT, PrivateDataSlotCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(AccelerationStructureCreateFlagsKHR, AccelerationStructureCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DescriptorUpdateTemplateCreateFlags, DescriptorUpdateTemplateCreateFlagBits, uint32_t)
using DescriptorUpdateTemplateCreateFlagsKHR = DescriptorUpdateTemplateCreateFlags;
DECLARE_ENUM_FLAG_OPERATORS(PipelineCreationFeedbackFlagsEXT, PipelineCreationFeedbackFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PerformanceCounterDescriptionFlagsKHR, PerformanceCounterDescriptionFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(AcquireProfilingLockFlagsKHR, AcquireProfilingLockFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SemaphoreWaitFlags, SemaphoreWaitFlagBits, uint32_t)
using SemaphoreWaitFlagsKHR = SemaphoreWaitFlags;
DECLARE_ENUM_FLAG_OPERATORS(PipelineCompilerControlFlagsAMD, PipelineCompilerControlFlagBitsAMD, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ShaderCorePropertiesFlagsAMD, ShaderCorePropertiesFlagBitsAMD, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DeviceDiagnosticsConfigFlagsNV, DeviceDiagnosticsConfigFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CompositeAlphaFlagsKHR, CompositeAlphaFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DisplayPlaneAlphaFlagsKHR, DisplayPlaneAlphaFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SurfaceTransformFlagsKHR, SurfaceTransformFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(SwapchainCreateFlagsKHR, SwapchainCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DisplayModeCreateFlagsKHR, DisplayModeCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DisplaySurfaceCreateFlagsKHR, DisplaySurfaceCreateFlagBitsKHR, uint32_t)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
DECLARE_ENUM_FLAG_OPERATORS(AndroidSurfaceCreateFlagsKHR, AndroidSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
DECLARE_ENUM_FLAG_OPERATORS(ViSurfaceCreateFlagsNN, ViSurfaceCreateFlagBitsNN, uint32_t)
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
DECLARE_ENUM_FLAG_OPERATORS(WaylandSurfaceCreateFlagsKHR, WaylandSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
DECLARE_ENUM_FLAG_OPERATORS(Win32SurfaceCreateFlagsKHR, Win32SurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
DECLARE_ENUM_FLAG_OPERATORS(XlibSurfaceCreateFlagsKHR, XlibSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
DECLARE_ENUM_FLAG_OPERATORS(XcbSurfaceCreateFlagsKHR, XcbSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
DECLARE_ENUM_FLAG_OPERATORS(DirectFBSurfaceCreateFlagsEXT, DirectFBSurfaceCreateFlagBitsEXT, uint32_t)
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
DECLARE_ENUM_FLAG_OPERATORS(IOSSurfaceCreateFlagsMVK, IOSSurfaceCreateFlagBitsMVK, uint32_t)
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
DECLARE_ENUM_FLAG_OPERATORS(MacOSSurfaceCreateFlagsMVK, MacOSSurfaceCreateFlagBitsMVK, uint32_t)
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
DECLARE_ENUM_FLAG_OPERATORS(MetalSurfaceCreateFlagsEXT, MetalSurfaceCreateFlagBitsEXT, uint32_t)
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
DECLARE_ENUM_FLAG_OPERATORS(ImagePipeSurfaceCreateFlagsFUCHSIA, ImagePipeSurfaceCreateFlagBitsFUCHSIA, uint32_t)
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
DECLARE_ENUM_FLAG_OPERATORS(StreamDescriptorSurfaceCreateFlagsGGP, StreamDescriptorSurfaceCreateFlagBitsGGP, uint32_t)
#endif // defined(VK_USE_PLATFORM_GGP)
DECLARE_ENUM_FLAG_OPERATORS(HeadlessSurfaceCreateFlagsEXT, HeadlessSurfaceCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PeerMemoryFeatureFlags, PeerMemoryFeatureFlagBits, uint32_t)
using PeerMemoryFeatureFlagsKHR = PeerMemoryFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(MemoryAllocateFlags, MemoryAllocateFlagBits, uint32_t)
using MemoryAllocateFlagsKHR = MemoryAllocateFlags;
DECLARE_ENUM_FLAG_OPERATORS(DeviceGroupPresentModeFlagsKHR, DeviceGroupPresentModeFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DebugReportFlagsEXT, DebugReportFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(CommandPoolTrimFlags, CommandPoolTrimFlagBits, uint32_t)
using CommandPoolTrimFlagsKHR = CommandPoolTrimFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalMemoryHandleTypeFlagsNV, ExternalMemoryHandleTypeFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ExternalMemoryFeatureFlagsNV, ExternalMemoryFeatureFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ExternalMemoryHandleTypeFlags, ExternalMemoryHandleTypeFlagBits, uint32_t)
using ExternalMemoryHandleTypeFlagsKHR = ExternalMemoryHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalMemoryFeatureFlags, ExternalMemoryFeatureFlagBits, uint32_t)
using ExternalMemoryFeatureFlagsKHR = ExternalMemoryFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalSemaphoreHandleTypeFlags, ExternalSemaphoreHandleTypeFlagBits, uint32_t)
using ExternalSemaphoreHandleTypeFlagsKHR = ExternalSemaphoreHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalSemaphoreFeatureFlags, ExternalSemaphoreFeatureFlagBits, uint32_t)
using ExternalSemaphoreFeatureFlagsKHR = ExternalSemaphoreFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(SemaphoreImportFlags, SemaphoreImportFlagBits, uint32_t)
using SemaphoreImportFlagsKHR = SemaphoreImportFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalFenceHandleTypeFlags, ExternalFenceHandleTypeFlagBits, uint32_t)
using ExternalFenceHandleTypeFlagsKHR = ExternalFenceHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(ExternalFenceFeatureFlags, ExternalFenceFeatureFlagBits, uint32_t)
using ExternalFenceFeatureFlagsKHR = ExternalFenceFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(FenceImportFlags, FenceImportFlagBits, uint32_t)
using FenceImportFlagsKHR = FenceImportFlags;
DECLARE_ENUM_FLAG_OPERATORS(SurfaceCounterFlagsEXT, SurfaceCounterFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineViewportSwizzleStateCreateFlagsNV, PipelineViewportSwizzleStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineDiscardRectangleStateCreateFlagsEXT, PipelineDiscardRectangleStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineCoverageToColorStateCreateFlagsNV, PipelineCoverageToColorStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineCoverageModulationStateCreateFlagsNV, PipelineCoverageModulationStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineCoverageReductionStateCreateFlagsNV, PipelineCoverageReductionStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ValidationCacheCreateFlagsEXT, ValidationCacheCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DebugUtilsMessageSeverityFlagsEXT, DebugUtilsMessageSeverityFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DebugUtilsMessageTypeFlagsEXT, DebugUtilsMessageTypeFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DebugUtilsMessengerCreateFlagsEXT, DebugUtilsMessengerCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DebugUtilsMessengerCallbackDataFlagsEXT, DebugUtilsMessengerCallbackDataFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DeviceMemoryReportFlagsEXT, DeviceMemoryReportFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineRasterizationConservativeStateCreateFlagsEXT, PipelineRasterizationConservativeStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(DescriptorBindingFlags, DescriptorBindingFlagBits, uint32_t)
using DescriptorBindingFlagsEXT = DescriptorBindingFlags;
DECLARE_ENUM_FLAG_OPERATORS(ConditionalRenderingFlagsEXT, ConditionalRenderingFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ResolveModeFlags, ResolveModeFlagBits, uint32_t)
using ResolveModeFlagsKHR = ResolveModeFlags;
DECLARE_ENUM_FLAG_OPERATORS(PipelineRasterizationStateStreamCreateFlagsEXT, PipelineRasterizationStateStreamCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(PipelineRasterizationDepthClipStateCreateFlagsEXT, PipelineRasterizationDepthClipStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(ToolPurposeFlagsEXT, ToolPurposeFlagBitsEXT, uint32_t)
} //namespace vk
VK_DEFINE_HANDLE(VkInstance)
VK_DEFINE_HANDLE(VkPhysicalDevice)
VK_DEFINE_HANDLE(VkDevice)
VK_DEFINE_HANDLE(VkQueue)
VK_DEFINE_HANDLE(VkCommandBuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkCommandPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkBufferView)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImage)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImageView)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkShaderModule)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipeline)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineLayout)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSampler)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSet)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorSetLayout)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFence)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSemaphore)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkEvent)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkQueryPool)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkFramebuffer)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkRenderPass)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPipelineCache)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkIndirectCommandsLayoutNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDescriptorUpdateTemplate)
using VkDescriptorUpdateTemplateKHR = VkDescriptorUpdateTemplate;
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSamplerYcbcrConversion)
using VkSamplerYcbcrConversionKHR = VkSamplerYcbcrConversion;
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkValidationCacheEXT)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkAccelerationStructureKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkAccelerationStructureNV)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPerformanceConfigurationINTEL)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeferredOperationKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkPrivateDataSlotEXT)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDisplayKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDisplayModeKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSurfaceKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkSwapchainKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugReportCallbackEXT)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDebugUtilsMessengerEXT)
namespace vk {

class Instance {
    VkInstance handle = 0;
    public:
    Instance() = default;
    Instance([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Instance(VkInstance handle) noexcept : handle(handle){}
    VkInstance get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class PhysicalDevice {
    VkPhysicalDevice handle = 0;
    public:
    PhysicalDevice() = default;
    PhysicalDevice([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit PhysicalDevice(VkPhysicalDevice handle) noexcept : handle(handle){}
    VkPhysicalDevice get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Device {
    VkDevice handle = 0;
    public:
    Device() = default;
    Device([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Device(VkDevice handle) noexcept : handle(handle){}
    VkDevice get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Queue {
    VkQueue handle = 0;
    public:
    Queue() = default;
    Queue([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Queue(VkQueue handle) noexcept : handle(handle){}
    VkQueue get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class CommandBuffer {
    VkCommandBuffer handle = 0;
    public:
    CommandBuffer() = default;
    CommandBuffer([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit CommandBuffer(VkCommandBuffer handle) noexcept : handle(handle){}
    VkCommandBuffer get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DeviceMemory {
    VkDeviceMemory handle = 0;
    public:
    DeviceMemory() = default;
    DeviceMemory([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DeviceMemory(VkDeviceMemory handle) noexcept : handle(handle){}
    VkDeviceMemory get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class CommandPool {
    VkCommandPool handle = 0;
    public:
    CommandPool() = default;
    CommandPool([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit CommandPool(VkCommandPool handle) noexcept : handle(handle){}
    VkCommandPool get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Buffer {
    VkBuffer handle = 0;
    public:
    Buffer() = default;
    Buffer([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Buffer(VkBuffer handle) noexcept : handle(handle){}
    VkBuffer get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class BufferView {
    VkBufferView handle = 0;
    public:
    BufferView() = default;
    BufferView([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit BufferView(VkBufferView handle) noexcept : handle(handle){}
    VkBufferView get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Image {
    VkImage handle = 0;
    public:
    Image() = default;
    Image([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Image(VkImage handle) noexcept : handle(handle){}
    VkImage get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class ImageView {
    VkImageView handle = 0;
    public:
    ImageView() = default;
    ImageView([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit ImageView(VkImageView handle) noexcept : handle(handle){}
    VkImageView get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class ShaderModule {
    VkShaderModule handle = 0;
    public:
    ShaderModule() = default;
    ShaderModule([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit ShaderModule(VkShaderModule handle) noexcept : handle(handle){}
    VkShaderModule get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Pipeline {
    VkPipeline handle = 0;
    public:
    Pipeline() = default;
    Pipeline([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Pipeline(VkPipeline handle) noexcept : handle(handle){}
    VkPipeline get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class PipelineLayout {
    VkPipelineLayout handle = 0;
    public:
    PipelineLayout() = default;
    PipelineLayout([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit PipelineLayout(VkPipelineLayout handle) noexcept : handle(handle){}
    VkPipelineLayout get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Sampler {
    VkSampler handle = 0;
    public:
    Sampler() = default;
    Sampler([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Sampler(VkSampler handle) noexcept : handle(handle){}
    VkSampler get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DescriptorSet {
    VkDescriptorSet handle = 0;
    public:
    DescriptorSet() = default;
    DescriptorSet([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DescriptorSet(VkDescriptorSet handle) noexcept : handle(handle){}
    VkDescriptorSet get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DescriptorSetLayout {
    VkDescriptorSetLayout handle = 0;
    public:
    DescriptorSetLayout() = default;
    DescriptorSetLayout([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DescriptorSetLayout(VkDescriptorSetLayout handle) noexcept : handle(handle){}
    VkDescriptorSetLayout get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DescriptorPool {
    VkDescriptorPool handle = 0;
    public:
    DescriptorPool() = default;
    DescriptorPool([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DescriptorPool(VkDescriptorPool handle) noexcept : handle(handle){}
    VkDescriptorPool get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Fence {
    VkFence handle = 0;
    public:
    Fence() = default;
    Fence([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Fence(VkFence handle) noexcept : handle(handle){}
    VkFence get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Semaphore {
    VkSemaphore handle = 0;
    public:
    Semaphore() = default;
    Semaphore([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Semaphore(VkSemaphore handle) noexcept : handle(handle){}
    VkSemaphore get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Event {
    VkEvent handle = 0;
    public:
    Event() = default;
    Event([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Event(VkEvent handle) noexcept : handle(handle){}
    VkEvent get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class QueryPool {
    VkQueryPool handle = 0;
    public:
    QueryPool() = default;
    QueryPool([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit QueryPool(VkQueryPool handle) noexcept : handle(handle){}
    VkQueryPool get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class Framebuffer {
    VkFramebuffer handle = 0;
    public:
    Framebuffer() = default;
    Framebuffer([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit Framebuffer(VkFramebuffer handle) noexcept : handle(handle){}
    VkFramebuffer get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class RenderPass {
    VkRenderPass handle = 0;
    public:
    RenderPass() = default;
    RenderPass([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit RenderPass(VkRenderPass handle) noexcept : handle(handle){}
    VkRenderPass get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class PipelineCache {
    VkPipelineCache handle = 0;
    public:
    PipelineCache() = default;
    PipelineCache([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit PipelineCache(VkPipelineCache handle) noexcept : handle(handle){}
    VkPipelineCache get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class IndirectCommandsLayoutNV {
    VkIndirectCommandsLayoutNV handle = 0;
    public:
    IndirectCommandsLayoutNV() = default;
    IndirectCommandsLayoutNV([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit IndirectCommandsLayoutNV(VkIndirectCommandsLayoutNV handle) noexcept : handle(handle){}
    VkIndirectCommandsLayoutNV get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DescriptorUpdateTemplate {
    VkDescriptorUpdateTemplate handle = 0;
    public:
    DescriptorUpdateTemplate() = default;
    DescriptorUpdateTemplate([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DescriptorUpdateTemplate(VkDescriptorUpdateTemplate handle) noexcept : handle(handle){}
    VkDescriptorUpdateTemplate get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};
using DescriptorUpdateTemplateKHR = DescriptorUpdateTemplate;

class SamplerYcbcrConversion {
    VkSamplerYcbcrConversion handle = 0;
    public:
    SamplerYcbcrConversion() = default;
    SamplerYcbcrConversion([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit SamplerYcbcrConversion(VkSamplerYcbcrConversion handle) noexcept : handle(handle){}
    VkSamplerYcbcrConversion get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};
using SamplerYcbcrConversionKHR = SamplerYcbcrConversion;

class ValidationCacheEXT {
    VkValidationCacheEXT handle = 0;
    public:
    ValidationCacheEXT() = default;
    ValidationCacheEXT([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit ValidationCacheEXT(VkValidationCacheEXT handle) noexcept : handle(handle){}
    VkValidationCacheEXT get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class AccelerationStructureKHR {
    VkAccelerationStructureKHR handle = 0;
    public:
    AccelerationStructureKHR() = default;
    AccelerationStructureKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit AccelerationStructureKHR(VkAccelerationStructureKHR handle) noexcept : handle(handle){}
    VkAccelerationStructureKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class AccelerationStructureNV {
    VkAccelerationStructureNV handle = 0;
    public:
    AccelerationStructureNV() = default;
    AccelerationStructureNV([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit AccelerationStructureNV(VkAccelerationStructureNV handle) noexcept : handle(handle){}
    VkAccelerationStructureNV get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class PerformanceConfigurationINTEL {
    VkPerformanceConfigurationINTEL handle = 0;
    public:
    PerformanceConfigurationINTEL() = default;
    PerformanceConfigurationINTEL([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit PerformanceConfigurationINTEL(VkPerformanceConfigurationINTEL handle) noexcept : handle(handle){}
    VkPerformanceConfigurationINTEL get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DeferredOperationKHR {
    VkDeferredOperationKHR handle = 0;
    public:
    DeferredOperationKHR() = default;
    DeferredOperationKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DeferredOperationKHR(VkDeferredOperationKHR handle) noexcept : handle(handle){}
    VkDeferredOperationKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class PrivateDataSlotEXT {
    VkPrivateDataSlotEXT handle = 0;
    public:
    PrivateDataSlotEXT() = default;
    PrivateDataSlotEXT([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit PrivateDataSlotEXT(VkPrivateDataSlotEXT handle) noexcept : handle(handle){}
    VkPrivateDataSlotEXT get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DisplayKHR {
    VkDisplayKHR handle = 0;
    public:
    DisplayKHR() = default;
    DisplayKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DisplayKHR(VkDisplayKHR handle) noexcept : handle(handle){}
    VkDisplayKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DisplayModeKHR {
    VkDisplayModeKHR handle = 0;
    public:
    DisplayModeKHR() = default;
    DisplayModeKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DisplayModeKHR(VkDisplayModeKHR handle) noexcept : handle(handle){}
    VkDisplayModeKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class SurfaceKHR {
    VkSurfaceKHR handle = 0;
    public:
    SurfaceKHR() = default;
    SurfaceKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit SurfaceKHR(VkSurfaceKHR handle) noexcept : handle(handle){}
    VkSurfaceKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class SwapchainKHR {
    VkSwapchainKHR handle = 0;
    public:
    SwapchainKHR() = default;
    SwapchainKHR([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit SwapchainKHR(VkSwapchainKHR handle) noexcept : handle(handle){}
    VkSwapchainKHR get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DebugReportCallbackEXT {
    VkDebugReportCallbackEXT handle = 0;
    public:
    DebugReportCallbackEXT() = default;
    DebugReportCallbackEXT([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DebugReportCallbackEXT(VkDebugReportCallbackEXT handle) noexcept : handle(handle){}
    VkDebugReportCallbackEXT get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};

class DebugUtilsMessengerEXT {
    VkDebugUtilsMessengerEXT handle = 0;
    public:
    DebugUtilsMessengerEXT() = default;
    DebugUtilsMessengerEXT([[maybe_unused]] std::nullptr_t none) noexcept {}
    explicit DebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT handle) noexcept : handle(handle){}
    VkDebugUtilsMessengerEXT get() { return handle; }
    explicit operator bool() const {return handle != 0;};
    bool operator!() { return handle == 0; }
};
struct DebugUtilsMessengerCallbackDataEXT;
struct DeviceMemoryReportCallbackDataEXT;
typedef void (VKAPI_PTR *PFN_InternalAllocationNotification)(
    void*                                       pUserData,
    size_t                                      size,
    InternalAllocationType                    allocationType,
    SystemAllocationScope                     allocationScope);
typedef void (VKAPI_PTR *PFN_InternalFreeNotification)(
    void*                                       pUserData,
    size_t                                      size,
    InternalAllocationType                    allocationType,
    SystemAllocationScope                     allocationScope);
typedef void* (VKAPI_PTR *PFN_ReallocationFunction)(
    void*                                       pUserData,
    void*                                       pOriginal,
    size_t                                      size,
    size_t                                      alignment,
    SystemAllocationScope                     allocationScope);
typedef void* (VKAPI_PTR *PFN_AllocationFunction)(
    void*                                       pUserData,
    size_t                                      size,
    size_t                                      alignment,
    SystemAllocationScope                     allocationScope);
typedef void (VKAPI_PTR *PFN_FreeFunction)(
    void*                                       pUserData,
    void*                                       pMemory);
typedef void (VKAPI_PTR *PFN_VoidFunction)(void);
typedef Bool32 (VKAPI_PTR *PFN_DebugReportCallbackEXT)(
    DebugReportFlagsEXT                       flags,
    DebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char*                                 pLayerPrefix,
    const char*                                 pMessage,
    void*                                       pUserData);
typedef Bool32 (VKAPI_PTR *PFN_DebugUtilsMessengerCallbackEXT)(
    DebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    DebugUtilsMessageTypeFlagsEXT                  messageTypes,
    const DebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    void*                                            pUserData);
typedef void (VKAPI_PTR *PFN_DeviceMemoryReportCallbackEXT)(
    const DeviceMemoryReportCallbackDataEXT*  pCallbackData,
    void*                                       pUserData);
struct BaseOutStructure {
    StructureType sType{static_cast<StructureType>(0)};
    BaseOutStructure* pNext = nullptr;
};
struct BaseInStructure {
    StructureType sType{static_cast<StructureType>(0)};
    const BaseInStructure* pNext = nullptr;
};
struct Offset2D {
    int32_t x{0};
    int32_t y{0};
    constexpr bool operator==(Offset2D const& value) const {
        return x == value.x && y == value.y ;}
    constexpr bool operator!=(Offset2D const& value) const {return !(*this == value);}
};
struct Offset3D {
    int32_t x{0};
    int32_t y{0};
    int32_t z{0};
    constexpr bool operator==(Offset3D const& value) const {
        return x == value.x && y == value.y && z == value.z ;}
    constexpr bool operator!=(Offset3D const& value) const {return !(*this == value);}
};
struct Extent2D {
    uint32_t width{0};
    uint32_t height{0};
    constexpr bool operator==(Extent2D const& value) const {
        return width == value.width && height == value.height ;}
    constexpr bool operator!=(Extent2D const& value) const {return !(*this == value);}
};
struct Extent3D {
    uint32_t width{0};
    uint32_t height{0};
    uint32_t depth{0};
    constexpr bool operator==(Extent3D const& value) const {
        return width == value.width && height == value.height && depth == value.depth ;}
    constexpr bool operator!=(Extent3D const& value) const {return !(*this == value);}
};
struct Viewport {
    float x{0.f};
    float y{0.f};
    float width{0.f};
    float height{0.f};
    float minDepth{0.f};
    float maxDepth{0.f};
    constexpr bool operator==(Viewport const& value) const {
        return x == value.x && y == value.y && width == value.width && height == value.height && minDepth == value.minDepth && maxDepth == value.maxDepth ;}
    constexpr bool operator!=(Viewport const& value) const {return !(*this == value);}
};
struct Rect2D {
    Offset2D offset{};
    Extent2D extent{};
    constexpr bool operator==(Rect2D const& value) const {
        return offset == value.offset && extent == value.extent ;}
    constexpr bool operator!=(Rect2D const& value) const {return !(*this == value);}
};
struct ClearRect {
    Rect2D rect{};
    uint32_t baseArrayLayer{0};
    uint32_t layerCount{0};
    constexpr bool operator==(ClearRect const& value) const {
        return rect == value.rect && baseArrayLayer == value.baseArrayLayer && layerCount == value.layerCount ;}
    constexpr bool operator!=(ClearRect const& value) const {return !(*this == value);}
};
struct ComponentMapping {
    ComponentSwizzle r{static_cast<ComponentSwizzle>(0)};
    ComponentSwizzle g{static_cast<ComponentSwizzle>(0)};
    ComponentSwizzle b{static_cast<ComponentSwizzle>(0)};
    ComponentSwizzle a{static_cast<ComponentSwizzle>(0)};
    constexpr bool operator==(ComponentMapping const& value) const {
        return r == value.r && g == value.g && b == value.b && a == value.a ;}
    constexpr bool operator!=(ComponentMapping const& value) const {return !(*this == value);}
};
struct PhysicalDeviceSparseProperties {
    Bool32 residencyStandard2DBlockShape{0};
    Bool32 residencyStandard2DMultisampleBlockShape{0};
    Bool32 residencyStandard3DBlockShape{0};
    Bool32 residencyAlignedMipSize{0};
    Bool32 residencyNonResidentStrict{0};
    constexpr bool operator==(PhysicalDeviceSparseProperties const& value) const {
        return residencyStandard2DBlockShape == value.residencyStandard2DBlockShape && residencyStandard2DMultisampleBlockShape == value.residencyStandard2DMultisampleBlockShape 
        && residencyStandard3DBlockShape == value.residencyStandard3DBlockShape && residencyAlignedMipSize == value.residencyAlignedMipSize 
        && residencyNonResidentStrict == value.residencyNonResidentStrict ;}
    constexpr bool operator!=(PhysicalDeviceSparseProperties const& value) const {return !(*this == value);}
};
struct PhysicalDeviceLimits {
    uint32_t maxImageDimension1D{0};
    uint32_t maxImageDimension2D{0};
    uint32_t maxImageDimension3D{0};
    uint32_t maxImageDimensionCube{0};
    uint32_t maxImageArrayLayers{0};
    uint32_t maxTexelBufferElements{0};
    uint32_t maxUniformBufferRange{0};
    uint32_t maxStorageBufferRange{0};
    uint32_t maxPushConstantsSize{0};
    uint32_t maxMemoryAllocationCount{0};
    uint32_t maxSamplerAllocationCount{0};
    DeviceSize bufferImageGranularity{0};
    DeviceSize sparseAddressSpaceSize{0};
    uint32_t maxBoundDescriptorSets{0};
    uint32_t maxPerStageDescriptorSamplers{0};
    uint32_t maxPerStageDescriptorUniformBuffers{0};
    uint32_t maxPerStageDescriptorStorageBuffers{0};
    uint32_t maxPerStageDescriptorSampledImages{0};
    uint32_t maxPerStageDescriptorStorageImages{0};
    uint32_t maxPerStageDescriptorInputAttachments{0};
    uint32_t maxPerStageResources{0};
    uint32_t maxDescriptorSetSamplers{0};
    uint32_t maxDescriptorSetUniformBuffers{0};
    uint32_t maxDescriptorSetUniformBuffersDynamic{0};
    uint32_t maxDescriptorSetStorageBuffers{0};
    uint32_t maxDescriptorSetStorageBuffersDynamic{0};
    uint32_t maxDescriptorSetSampledImages{0};
    uint32_t maxDescriptorSetStorageImages{0};
    uint32_t maxDescriptorSetInputAttachments{0};
    uint32_t maxVertexInputAttributes{0};
    uint32_t maxVertexInputBindings{0};
    uint32_t maxVertexInputAttributeOffset{0};
    uint32_t maxVertexInputBindingStride{0};
    uint32_t maxVertexOutputComponents{0};
    uint32_t maxTessellationGenerationLevel{0};
    uint32_t maxTessellationPatchSize{0};
    uint32_t maxTessellationControlPerVertexInputComponents{0};
    uint32_t maxTessellationControlPerVertexOutputComponents{0};
    uint32_t maxTessellationControlPerPatchOutputComponents{0};
    uint32_t maxTessellationControlTotalOutputComponents{0};
    uint32_t maxTessellationEvaluationInputComponents{0};
    uint32_t maxTessellationEvaluationOutputComponents{0};
    uint32_t maxGeometryShaderInvocations{0};
    uint32_t maxGeometryInputComponents{0};
    uint32_t maxGeometryOutputComponents{0};
    uint32_t maxGeometryOutputVertices{0};
    uint32_t maxGeometryTotalOutputComponents{0};
    uint32_t maxFragmentInputComponents{0};
    uint32_t maxFragmentOutputAttachments{0};
    uint32_t maxFragmentDualSrcAttachments{0};
    uint32_t maxFragmentCombinedOutputResources{0};
    uint32_t maxComputeSharedMemorySize{0};
    uint32_t maxComputeWorkGroupCount[3];
    uint32_t maxComputeWorkGroupInvocations{0};
    uint32_t maxComputeWorkGroupSize[3];
    uint32_t subPixelPrecisionBits{0};
    uint32_t subTexelPrecisionBits{0};
    uint32_t mipmapPrecisionBits{0};
    uint32_t maxDrawIndexedIndexValue{0};
    uint32_t maxDrawIndirectCount{0};
    float maxSamplerLodBias{0.f};
    float maxSamplerAnisotropy{0.f};
    uint32_t maxViewports{0};
    uint32_t maxViewportDimensions[2];
    float viewportBoundsRange[2];
    uint32_t viewportSubPixelBits{0};
    size_t minMemoryMapAlignment{0};
    DeviceSize minTexelBufferOffsetAlignment{0};
    DeviceSize minUniformBufferOffsetAlignment{0};
    DeviceSize minStorageBufferOffsetAlignment{0};
    int32_t minTexelOffset{0};
    uint32_t maxTexelOffset{0};
    int32_t minTexelGatherOffset{0};
    uint32_t maxTexelGatherOffset{0};
    float minInterpolationOffset{0.f};
    float maxInterpolationOffset{0.f};
    uint32_t subPixelInterpolationOffsetBits{0};
    uint32_t maxFramebufferWidth{0};
    uint32_t maxFramebufferHeight{0};
    uint32_t maxFramebufferLayers{0};
    SampleCountFlags framebufferColorSampleCounts{};
    SampleCountFlags framebufferDepthSampleCounts{};
    SampleCountFlags framebufferStencilSampleCounts{};
    SampleCountFlags framebufferNoAttachmentsSampleCounts{};
    uint32_t maxColorAttachments{0};
    SampleCountFlags sampledImageColorSampleCounts{};
    SampleCountFlags sampledImageIntegerSampleCounts{};
    SampleCountFlags sampledImageDepthSampleCounts{};
    SampleCountFlags sampledImageStencilSampleCounts{};
    SampleCountFlags storageImageSampleCounts{};
    uint32_t maxSampleMaskWords{0};
    Bool32 timestampComputeAndGraphics{0};
    float timestampPeriod{0.f};
    uint32_t maxClipDistances{0};
    uint32_t maxCullDistances{0};
    uint32_t maxCombinedClipAndCullDistances{0};
    uint32_t discreteQueuePriorities{0};
    float pointSizeRange[2];
    float lineWidthRange[2];
    float pointSizeGranularity{0.f};
    float lineWidthGranularity{0.f};
    Bool32 strictLines{0};
    Bool32 standardSampleLocations{0};
    DeviceSize optimalBufferCopyOffsetAlignment{0};
    DeviceSize optimalBufferCopyRowPitchAlignment{0};
    DeviceSize nonCoherentAtomSize{0};
    constexpr bool operator==(PhysicalDeviceLimits const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 3; i++)
            is_equal &= maxComputeWorkGroupCount[i] == value.maxComputeWorkGroupCount[i];
        for(uint32_t i = 0; i < 3; i++)
            is_equal &= maxComputeWorkGroupSize[i] == value.maxComputeWorkGroupSize[i];
        for(uint32_t i = 0; i < 2; i++)
            is_equal &= maxViewportDimensions[i] == value.maxViewportDimensions[i];
        for(uint32_t i = 0; i < 2; i++)
            is_equal &= viewportBoundsRange[i] == value.viewportBoundsRange[i];
        for(uint32_t i = 0; i < 2; i++)
            is_equal &= pointSizeRange[i] == value.pointSizeRange[i];
        for(uint32_t i = 0; i < 2; i++)
            is_equal &= lineWidthRange[i] == value.lineWidthRange[i];
        return is_equal && maxImageDimension1D == value.maxImageDimension1D && maxImageDimension2D == value.maxImageDimension2D && maxImageDimension3D == value.maxImageDimension3D 
        && maxImageDimensionCube == value.maxImageDimensionCube && maxImageArrayLayers == value.maxImageArrayLayers && maxTexelBufferElements == value.maxTexelBufferElements 
        && maxUniformBufferRange == value.maxUniformBufferRange && maxStorageBufferRange == value.maxStorageBufferRange && maxPushConstantsSize == value.maxPushConstantsSize 
        && maxMemoryAllocationCount == value.maxMemoryAllocationCount && maxSamplerAllocationCount == value.maxSamplerAllocationCount && bufferImageGranularity == value.bufferImageGranularity 
        && sparseAddressSpaceSize == value.sparseAddressSpaceSize && maxBoundDescriptorSets == value.maxBoundDescriptorSets && maxPerStageDescriptorSamplers == value.maxPerStageDescriptorSamplers 
        && maxPerStageDescriptorUniformBuffers == value.maxPerStageDescriptorUniformBuffers && maxPerStageDescriptorStorageBuffers == value.maxPerStageDescriptorStorageBuffers 
        && maxPerStageDescriptorSampledImages == value.maxPerStageDescriptorSampledImages && maxPerStageDescriptorStorageImages == value.maxPerStageDescriptorStorageImages 
        && maxPerStageDescriptorInputAttachments == value.maxPerStageDescriptorInputAttachments && maxPerStageResources == value.maxPerStageResources 
        && maxDescriptorSetSamplers == value.maxDescriptorSetSamplers && maxDescriptorSetUniformBuffers == value.maxDescriptorSetUniformBuffers 
        && maxDescriptorSetUniformBuffersDynamic == value.maxDescriptorSetUniformBuffersDynamic && maxDescriptorSetStorageBuffers == value.maxDescriptorSetStorageBuffers 
        && maxDescriptorSetStorageBuffersDynamic == value.maxDescriptorSetStorageBuffersDynamic && maxDescriptorSetSampledImages == value.maxDescriptorSetSampledImages 
        && maxDescriptorSetStorageImages == value.maxDescriptorSetStorageImages && maxDescriptorSetInputAttachments == value.maxDescriptorSetInputAttachments 
        && maxVertexInputAttributes == value.maxVertexInputAttributes && maxVertexInputBindings == value.maxVertexInputBindings && maxVertexInputAttributeOffset == value.maxVertexInputAttributeOffset 
        && maxVertexInputBindingStride == value.maxVertexInputBindingStride && maxVertexOutputComponents == value.maxVertexOutputComponents 
        && maxTessellationGenerationLevel == value.maxTessellationGenerationLevel && maxTessellationPatchSize == value.maxTessellationPatchSize 
        && maxTessellationControlPerVertexInputComponents == value.maxTessellationControlPerVertexInputComponents && maxTessellationControlPerVertexOutputComponents == value.maxTessellationControlPerVertexOutputComponents 
        && maxTessellationControlPerPatchOutputComponents == value.maxTessellationControlPerPatchOutputComponents && maxTessellationControlTotalOutputComponents == value.maxTessellationControlTotalOutputComponents 
        && maxTessellationEvaluationInputComponents == value.maxTessellationEvaluationInputComponents && maxTessellationEvaluationOutputComponents == value.maxTessellationEvaluationOutputComponents 
        && maxGeometryShaderInvocations == value.maxGeometryShaderInvocations && maxGeometryInputComponents == value.maxGeometryInputComponents 
        && maxGeometryOutputComponents == value.maxGeometryOutputComponents && maxGeometryOutputVertices == value.maxGeometryOutputVertices 
        && maxGeometryTotalOutputComponents == value.maxGeometryTotalOutputComponents && maxFragmentInputComponents == value.maxFragmentInputComponents 
        && maxFragmentOutputAttachments == value.maxFragmentOutputAttachments && maxFragmentDualSrcAttachments == value.maxFragmentDualSrcAttachments 
        && maxFragmentCombinedOutputResources == value.maxFragmentCombinedOutputResources && maxComputeSharedMemorySize == value.maxComputeSharedMemorySize 
        && maxComputeWorkGroupInvocations == value.maxComputeWorkGroupInvocations && subPixelPrecisionBits == value.subPixelPrecisionBits 
        && subTexelPrecisionBits == value.subTexelPrecisionBits && mipmapPrecisionBits == value.mipmapPrecisionBits && maxDrawIndexedIndexValue == value.maxDrawIndexedIndexValue 
        && maxDrawIndirectCount == value.maxDrawIndirectCount && maxSamplerLodBias == value.maxSamplerLodBias && maxSamplerAnisotropy == value.maxSamplerAnisotropy 
        && maxViewports == value.maxViewports && viewportSubPixelBits == value.viewportSubPixelBits && minMemoryMapAlignment == value.minMemoryMapAlignment 
        && minTexelBufferOffsetAlignment == value.minTexelBufferOffsetAlignment && minUniformBufferOffsetAlignment == value.minUniformBufferOffsetAlignment 
        && minStorageBufferOffsetAlignment == value.minStorageBufferOffsetAlignment && minTexelOffset == value.minTexelOffset && maxTexelOffset == value.maxTexelOffset 
        && minTexelGatherOffset == value.minTexelGatherOffset && maxTexelGatherOffset == value.maxTexelGatherOffset && minInterpolationOffset == value.minInterpolationOffset 
        && maxInterpolationOffset == value.maxInterpolationOffset && subPixelInterpolationOffsetBits == value.subPixelInterpolationOffsetBits 
        && maxFramebufferWidth == value.maxFramebufferWidth && maxFramebufferHeight == value.maxFramebufferHeight && maxFramebufferLayers == value.maxFramebufferLayers 
        && framebufferColorSampleCounts == value.framebufferColorSampleCounts && framebufferDepthSampleCounts == value.framebufferDepthSampleCounts 
        && framebufferStencilSampleCounts == value.framebufferStencilSampleCounts && framebufferNoAttachmentsSampleCounts == value.framebufferNoAttachmentsSampleCounts 
        && maxColorAttachments == value.maxColorAttachments && sampledImageColorSampleCounts == value.sampledImageColorSampleCounts && sampledImageIntegerSampleCounts == value.sampledImageIntegerSampleCounts 
        && sampledImageDepthSampleCounts == value.sampledImageDepthSampleCounts && sampledImageStencilSampleCounts == value.sampledImageStencilSampleCounts 
        && storageImageSampleCounts == value.storageImageSampleCounts && maxSampleMaskWords == value.maxSampleMaskWords && timestampComputeAndGraphics == value.timestampComputeAndGraphics 
        && timestampPeriod == value.timestampPeriod && maxClipDistances == value.maxClipDistances && maxCullDistances == value.maxCullDistances 
        && maxCombinedClipAndCullDistances == value.maxCombinedClipAndCullDistances && discreteQueuePriorities == value.discreteQueuePriorities 
        && pointSizeGranularity == value.pointSizeGranularity && lineWidthGranularity == value.lineWidthGranularity && strictLines == value.strictLines 
        && standardSampleLocations == value.standardSampleLocations && optimalBufferCopyOffsetAlignment == value.optimalBufferCopyOffsetAlignment 
        && optimalBufferCopyRowPitchAlignment == value.optimalBufferCopyRowPitchAlignment && nonCoherentAtomSize == value.nonCoherentAtomSize 
        ;}
    constexpr bool operator!=(PhysicalDeviceLimits const& value) const {return !(*this == value);}
};
struct PhysicalDeviceProperties {
    uint32_t apiVersion{0};
    uint32_t driverVersion{0};
    uint32_t vendorID{0};
    uint32_t deviceID{0};
    PhysicalDeviceType deviceType{static_cast<PhysicalDeviceType>(0)};
    char deviceName[MAX_PHYSICAL_DEVICE_NAME_SIZE];
    uint8_t pipelineCacheUUID[UUID_SIZE];
    PhysicalDeviceLimits limits{};
    PhysicalDeviceSparseProperties sparseProperties{};
    constexpr bool operator==(PhysicalDeviceProperties const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 256; i++)
            is_equal &= deviceName[i] == value.deviceName[i];
        for(uint32_t i = 0; i < 16; i++)
            is_equal &= pipelineCacheUUID[i] == value.pipelineCacheUUID[i];
        return is_equal && apiVersion == value.apiVersion && driverVersion == value.driverVersion && vendorID == value.vendorID && deviceID == value.deviceID && deviceType == value.deviceType 
        && limits == value.limits && sparseProperties == value.sparseProperties ;}
    constexpr bool operator!=(PhysicalDeviceProperties const& value) const {return !(*this == value);}
};
struct ExtensionProperties {
    char extensionName[MAX_EXTENSION_NAME_SIZE];
    uint32_t specVersion{0};
    constexpr bool operator==(ExtensionProperties const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 256; i++)
            is_equal &= extensionName[i] == value.extensionName[i];
        return is_equal && specVersion == value.specVersion ;}
    constexpr bool operator!=(ExtensionProperties const& value) const {return !(*this == value);}
};
struct LayerProperties {
    char layerName[MAX_EXTENSION_NAME_SIZE];
    uint32_t specVersion{0};
    uint32_t implementationVersion{0};
    char description[MAX_DESCRIPTION_SIZE];
    constexpr bool operator==(LayerProperties const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 256; i++)
            is_equal &= layerName[i] == value.layerName[i];
        for(uint32_t i = 0; i < 256; i++)
            is_equal &= description[i] == value.description[i];
        return is_equal && specVersion == value.specVersion && implementationVersion == value.implementationVersion ;}
    constexpr bool operator!=(LayerProperties const& value) const {return !(*this == value);}
};
struct ApplicationInfo {
    StructureType sType{StructureType::ApplicationInfo};
    const void* pNext = nullptr;
    const char* pApplicationName = nullptr;
    uint32_t applicationVersion{0};
    const char* pEngineName = nullptr;
    uint32_t engineVersion{0};
    uint32_t apiVersion{0};
};
struct AllocationCallbacks {
    void* pUserData = nullptr;
    PFN_AllocationFunction pfnAllocation{};
    PFN_ReallocationFunction pfnReallocation{};
    PFN_FreeFunction pfnFree{};
    PFN_InternalAllocationNotification pfnInternalAllocation{};
    PFN_InternalFreeNotification pfnInternalFree{};
};
struct DeviceQueueCreateInfo {
    StructureType sType{StructureType::DeviceQueueCreateInfo};
    const void* pNext = nullptr;
    DeviceQueueCreateFlags flags{};
    uint32_t queueFamilyIndex{0};
    uint32_t queueCount{0};
    const float* pQueuePriorities = nullptr;
};
struct PhysicalDeviceFeatures {
    Bool32 robustBufferAccess{0};
    Bool32 fullDrawIndexUint32{0};
    Bool32 imageCubeArray{0};
    Bool32 independentBlend{0};
    Bool32 geometryShader{0};
    Bool32 tessellationShader{0};
    Bool32 sampleRateShading{0};
    Bool32 dualSrcBlend{0};
    Bool32 logicOp{0};
    Bool32 multiDrawIndirect{0};
    Bool32 drawIndirectFirstInstance{0};
    Bool32 depthClamp{0};
    Bool32 depthBiasClamp{0};
    Bool32 fillModeNonSolid{0};
    Bool32 depthBounds{0};
    Bool32 wideLines{0};
    Bool32 largePoints{0};
    Bool32 alphaToOne{0};
    Bool32 multiViewport{0};
    Bool32 samplerAnisotropy{0};
    Bool32 textureCompressionETC2{0};
    Bool32 textureCompressionASTC_LDR{0};
    Bool32 textureCompressionBC{0};
    Bool32 occlusionQueryPrecise{0};
    Bool32 pipelineStatisticsQuery{0};
    Bool32 vertexPipelineStoresAndAtomics{0};
    Bool32 fragmentStoresAndAtomics{0};
    Bool32 shaderTessellationAndGeometryPointSize{0};
    Bool32 shaderImageGatherExtended{0};
    Bool32 shaderStorageImageExtendedFormats{0};
    Bool32 shaderStorageImageMultisample{0};
    Bool32 shaderStorageImageReadWithoutFormat{0};
    Bool32 shaderStorageImageWriteWithoutFormat{0};
    Bool32 shaderUniformBufferArrayDynamicIndexing{0};
    Bool32 shaderSampledImageArrayDynamicIndexing{0};
    Bool32 shaderStorageBufferArrayDynamicIndexing{0};
    Bool32 shaderStorageImageArrayDynamicIndexing{0};
    Bool32 shaderClipDistance{0};
    Bool32 shaderCullDistance{0};
    Bool32 shaderFloat64{0};
    Bool32 shaderInt64{0};
    Bool32 shaderInt16{0};
    Bool32 shaderResourceResidency{0};
    Bool32 shaderResourceMinLod{0};
    Bool32 sparseBinding{0};
    Bool32 sparseResidencyBuffer{0};
    Bool32 sparseResidencyImage2D{0};
    Bool32 sparseResidencyImage3D{0};
    Bool32 sparseResidency2Samples{0};
    Bool32 sparseResidency4Samples{0};
    Bool32 sparseResidency8Samples{0};
    Bool32 sparseResidency16Samples{0};
    Bool32 sparseResidencyAliased{0};
    Bool32 variableMultisampleRate{0};
    Bool32 inheritedQueries{0};
    constexpr bool operator==(PhysicalDeviceFeatures const& value) const {
        return robustBufferAccess == value.robustBufferAccess && fullDrawIndexUint32 == value.fullDrawIndexUint32 && imageCubeArray == value.imageCubeArray 
        && independentBlend == value.independentBlend && geometryShader == value.geometryShader && tessellationShader == value.tessellationShader 
        && sampleRateShading == value.sampleRateShading && dualSrcBlend == value.dualSrcBlend && logicOp == value.logicOp && multiDrawIndirect == value.multiDrawIndirect 
        && drawIndirectFirstInstance == value.drawIndirectFirstInstance && depthClamp == value.depthClamp && depthBiasClamp == value.depthBiasClamp 
        && fillModeNonSolid == value.fillModeNonSolid && depthBounds == value.depthBounds && wideLines == value.wideLines && largePoints == value.largePoints 
        && alphaToOne == value.alphaToOne && multiViewport == value.multiViewport && samplerAnisotropy == value.samplerAnisotropy && textureCompressionETC2 == value.textureCompressionETC2 
        && textureCompressionASTC_LDR == value.textureCompressionASTC_LDR && textureCompressionBC == value.textureCompressionBC && occlusionQueryPrecise == value.occlusionQueryPrecise 
        && pipelineStatisticsQuery == value.pipelineStatisticsQuery && vertexPipelineStoresAndAtomics == value.vertexPipelineStoresAndAtomics 
        && fragmentStoresAndAtomics == value.fragmentStoresAndAtomics && shaderTessellationAndGeometryPointSize == value.shaderTessellationAndGeometryPointSize 
        && shaderImageGatherExtended == value.shaderImageGatherExtended && shaderStorageImageExtendedFormats == value.shaderStorageImageExtendedFormats 
        && shaderStorageImageMultisample == value.shaderStorageImageMultisample && shaderStorageImageReadWithoutFormat == value.shaderStorageImageReadWithoutFormat 
        && shaderStorageImageWriteWithoutFormat == value.shaderStorageImageWriteWithoutFormat && shaderUniformBufferArrayDynamicIndexing == value.shaderUniformBufferArrayDynamicIndexing 
        && shaderSampledImageArrayDynamicIndexing == value.shaderSampledImageArrayDynamicIndexing && shaderStorageBufferArrayDynamicIndexing == value.shaderStorageBufferArrayDynamicIndexing 
        && shaderStorageImageArrayDynamicIndexing == value.shaderStorageImageArrayDynamicIndexing && shaderClipDistance == value.shaderClipDistance 
        && shaderCullDistance == value.shaderCullDistance && shaderFloat64 == value.shaderFloat64 && shaderInt64 == value.shaderInt64 && shaderInt16 == value.shaderInt16 
        && shaderResourceResidency == value.shaderResourceResidency && shaderResourceMinLod == value.shaderResourceMinLod && sparseBinding == value.sparseBinding 
        && sparseResidencyBuffer == value.sparseResidencyBuffer && sparseResidencyImage2D == value.sparseResidencyImage2D && sparseResidencyImage3D == value.sparseResidencyImage3D 
        && sparseResidency2Samples == value.sparseResidency2Samples && sparseResidency4Samples == value.sparseResidency4Samples && sparseResidency8Samples == value.sparseResidency8Samples 
        && sparseResidency16Samples == value.sparseResidency16Samples && sparseResidencyAliased == value.sparseResidencyAliased && variableMultisampleRate == value.variableMultisampleRate 
        && inheritedQueries == value.inheritedQueries ;}
    constexpr bool operator!=(PhysicalDeviceFeatures const& value) const {return !(*this == value);}
};
struct DeviceCreateInfo {
    StructureType sType{StructureType::DeviceCreateInfo};
    const void* pNext = nullptr;
    DeviceCreateFlags flags{};
    uint32_t queueCreateInfoCount{0};
    const DeviceQueueCreateInfo* pQueueCreateInfos = nullptr;
[[deprecated]]    uint32_t enabledLayerCount{0};
[[deprecated]]    const char* const* ppEnabledLayerNames = nullptr;
    uint32_t enabledExtensionCount{0};
    const char* const* ppEnabledExtensionNames = nullptr;
    const PhysicalDeviceFeatures* pEnabledFeatures = nullptr;
};
struct InstanceCreateInfo {
    StructureType sType{StructureType::InstanceCreateInfo};
    const void* pNext = nullptr;
    InstanceCreateFlags flags{};
    const ApplicationInfo* pApplicationInfo = nullptr;
    uint32_t enabledLayerCount{0};
    const char* const* ppEnabledLayerNames = nullptr;
    uint32_t enabledExtensionCount{0};
    const char* const* ppEnabledExtensionNames = nullptr;
};
struct QueueFamilyProperties {
    QueueFlags queueFlags{};
    uint32_t queueCount{0};
    uint32_t timestampValidBits{0};
    Extent3D minImageTransferGranularity{};
    constexpr bool operator==(QueueFamilyProperties const& value) const {
        return queueFlags == value.queueFlags && queueCount == value.queueCount && timestampValidBits == value.timestampValidBits && minImageTransferGranularity == value.minImageTransferGranularity 
        ;}
    constexpr bool operator!=(QueueFamilyProperties const& value) const {return !(*this == value);}
};
struct MemoryHeap {
    DeviceSize size{0};
    MemoryHeapFlags flags{};
    constexpr bool operator==(MemoryHeap const& value) const {
        return size == value.size && flags == value.flags ;}
    constexpr bool operator!=(MemoryHeap const& value) const {return !(*this == value);}
};
struct MemoryType {
    MemoryPropertyFlags propertyFlags{};
    uint32_t heapIndex{0};
    constexpr bool operator==(MemoryType const& value) const {
        return propertyFlags == value.propertyFlags && heapIndex == value.heapIndex ;}
    constexpr bool operator!=(MemoryType const& value) const {return !(*this == value);}
};
struct PhysicalDeviceMemoryProperties {
    uint32_t memoryTypeCount{0};
    MemoryType memoryTypes[MAX_MEMORY_TYPES];
    uint32_t memoryHeapCount{0};
    MemoryHeap memoryHeaps[MAX_MEMORY_HEAPS];
    constexpr bool operator==(PhysicalDeviceMemoryProperties const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 32; i++)
            is_equal &= memoryTypes[i] == value.memoryTypes[i];
        for(uint32_t i = 0; i < 16; i++)
            is_equal &= memoryHeaps[i] == value.memoryHeaps[i];
        return is_equal && memoryTypeCount == value.memoryTypeCount && memoryHeapCount == value.memoryHeapCount ;}
    constexpr bool operator!=(PhysicalDeviceMemoryProperties const& value) const {return !(*this == value);}
};
struct MemoryAllocateInfo {
    StructureType sType{StructureType::MemoryAllocateInfo};
    const void* pNext = nullptr;
    DeviceSize allocationSize{0};
    uint32_t memoryTypeIndex{0};
};
struct MemoryRequirements {
    DeviceSize size{0};
    DeviceSize alignment{0};
    uint32_t memoryTypeBits{0};
    constexpr bool operator==(MemoryRequirements const& value) const {
        return size == value.size && alignment == value.alignment && memoryTypeBits == value.memoryTypeBits ;}
    constexpr bool operator!=(MemoryRequirements const& value) const {return !(*this == value);}
};
struct SparseImageFormatProperties {
    ImageAspectFlags aspectMask{};
    Extent3D imageGranularity{};
    SparseImageFormatFlags flags{};
    constexpr bool operator==(SparseImageFormatProperties const& value) const {
        return aspectMask == value.aspectMask && imageGranularity == value.imageGranularity && flags == value.flags ;}
    constexpr bool operator!=(SparseImageFormatProperties const& value) const {return !(*this == value);}
};
struct SparseImageMemoryRequirements {
    SparseImageFormatProperties formatProperties{};
    uint32_t imageMipTailFirstLod{0};
    DeviceSize imageMipTailSize{0};
    DeviceSize imageMipTailOffset{0};
    DeviceSize imageMipTailStride{0};
    constexpr bool operator==(SparseImageMemoryRequirements const& value) const {
        return formatProperties == value.formatProperties && imageMipTailFirstLod == value.imageMipTailFirstLod && imageMipTailSize == value.imageMipTailSize 
        && imageMipTailOffset == value.imageMipTailOffset && imageMipTailStride == value.imageMipTailStride ;}
    constexpr bool operator!=(SparseImageMemoryRequirements const& value) const {return !(*this == value);}
};
struct MappedMemoryRange {
    StructureType sType{StructureType::MappedMemoryRange};
    const void* pNext = nullptr;
    DeviceMemory memory{};
    DeviceSize offset{0};
    DeviceSize size{0};
};
struct FormatProperties {
    FormatFeatureFlags linearTilingFeatures{};
    FormatFeatureFlags optimalTilingFeatures{};
    FormatFeatureFlags bufferFeatures{};
    constexpr bool operator==(FormatProperties const& value) const {
        return linearTilingFeatures == value.linearTilingFeatures && optimalTilingFeatures == value.optimalTilingFeatures && bufferFeatures == value.bufferFeatures 
        ;}
    constexpr bool operator!=(FormatProperties const& value) const {return !(*this == value);}
};
struct ImageFormatProperties {
    Extent3D maxExtent{};
    uint32_t maxMipLevels{0};
    uint32_t maxArrayLayers{0};
    SampleCountFlags sampleCounts{};
    DeviceSize maxResourceSize{0};
    constexpr bool operator==(ImageFormatProperties const& value) const {
        return maxExtent == value.maxExtent && maxMipLevels == value.maxMipLevels && maxArrayLayers == value.maxArrayLayers && sampleCounts == value.sampleCounts 
        && maxResourceSize == value.maxResourceSize ;}
    constexpr bool operator!=(ImageFormatProperties const& value) const {return !(*this == value);}
};
struct DescriptorBufferInfo {
    Buffer buffer{};
    DeviceSize offset{0};
    DeviceSize range{0};
};
struct DescriptorImageInfo {
    Sampler sampler{};
    ImageView imageView{};
    ImageLayout imageLayout{static_cast<ImageLayout>(0)};
};
struct WriteDescriptorSet {
    StructureType sType{StructureType::WriteDescriptorSet};
    const void* pNext = nullptr;
    DescriptorSet dstSet{};
    uint32_t dstBinding{0};
    uint32_t dstArrayElement{0};
    uint32_t descriptorCount{0};
    DescriptorType descriptorType{static_cast<DescriptorType>(0)};
    const DescriptorImageInfo* pImageInfo = nullptr;
    const DescriptorBufferInfo* pBufferInfo = nullptr;
    const BufferView* pTexelBufferView = nullptr;
};
struct CopyDescriptorSet {
    StructureType sType{StructureType::CopyDescriptorSet};
    const void* pNext = nullptr;
    DescriptorSet srcSet{};
    uint32_t srcBinding{0};
    uint32_t srcArrayElement{0};
    DescriptorSet dstSet{};
    uint32_t dstBinding{0};
    uint32_t dstArrayElement{0};
    uint32_t descriptorCount{0};
};
struct BufferCreateInfo {
    StructureType sType{StructureType::BufferCreateInfo};
    const void* pNext = nullptr;
    BufferCreateFlags flags{};
    DeviceSize size{0};
    BufferUsageFlags usage{};
    SharingMode sharingMode{static_cast<SharingMode>(0)};
    uint32_t queueFamilyIndexCount{0};
    const uint32_t* pQueueFamilyIndices = nullptr;
};
struct BufferViewCreateInfo {
    StructureType sType{StructureType::BufferViewCreateInfo};
    const void* pNext = nullptr;
    BufferViewCreateFlags flags{};
    Buffer buffer{};
    Format format{static_cast<Format>(0)};
    DeviceSize offset{0};
    DeviceSize range{0};
};
struct ImageSubresource {
    ImageAspectFlags aspectMask{};
    uint32_t mipLevel{0};
    uint32_t arrayLayer{0};
    constexpr bool operator==(ImageSubresource const& value) const {
        return aspectMask == value.aspectMask && mipLevel == value.mipLevel && arrayLayer == value.arrayLayer ;}
    constexpr bool operator!=(ImageSubresource const& value) const {return !(*this == value);}
};
struct ImageSubresourceLayers {
    ImageAspectFlags aspectMask{};
    uint32_t mipLevel{0};
    uint32_t baseArrayLayer{0};
    uint32_t layerCount{0};
    constexpr bool operator==(ImageSubresourceLayers const& value) const {
        return aspectMask == value.aspectMask && mipLevel == value.mipLevel && baseArrayLayer == value.baseArrayLayer && layerCount == value.layerCount 
        ;}
    constexpr bool operator!=(ImageSubresourceLayers const& value) const {return !(*this == value);}
};
struct ImageSubresourceRange {
    ImageAspectFlags aspectMask{};
    uint32_t baseMipLevel{0};
    uint32_t levelCount{0};
    uint32_t baseArrayLayer{0};
    uint32_t layerCount{0};
    constexpr bool operator==(ImageSubresourceRange const& value) const {
        return aspectMask == value.aspectMask && baseMipLevel == value.baseMipLevel && levelCount == value.levelCount && baseArrayLayer == value.baseArrayLayer 
        && layerCount == value.layerCount ;}
    constexpr bool operator!=(ImageSubresourceRange const& value) const {return !(*this == value);}
};
struct MemoryBarrier {
    StructureType sType{StructureType::MemoryBarrier};
    const void* pNext = nullptr;
    AccessFlags srcAccessMask{};
    AccessFlags dstAccessMask{};
};
struct BufferMemoryBarrier {
    StructureType sType{StructureType::BufferMemoryBarrier};
    const void* pNext = nullptr;
    AccessFlags srcAccessMask{};
    AccessFlags dstAccessMask{};
    uint32_t srcQueueFamilyIndex{0};
    uint32_t dstQueueFamilyIndex{0};
    Buffer buffer{};
    DeviceSize offset{0};
    DeviceSize size{0};
};
struct ImageMemoryBarrier {
    StructureType sType{StructureType::ImageMemoryBarrier};
    const void* pNext = nullptr;
    AccessFlags srcAccessMask{};
    AccessFlags dstAccessMask{};
    ImageLayout oldLayout{static_cast<ImageLayout>(0)};
    ImageLayout newLayout{static_cast<ImageLayout>(0)};
    uint32_t srcQueueFamilyIndex{0};
    uint32_t dstQueueFamilyIndex{0};
    Image image{};
    ImageSubresourceRange subresourceRange{};
};
struct ImageCreateInfo {
    StructureType sType{StructureType::ImageCreateInfo};
    const void* pNext = nullptr;
    ImageCreateFlags flags{};
    ImageType imageType{static_cast<ImageType>(0)};
    Format format{static_cast<Format>(0)};
    Extent3D extent{};
    uint32_t mipLevels{0};
    uint32_t arrayLayers{0};
    SampleCountFlagBits samples{static_cast<SampleCountFlagBits>(0)};
    ImageTiling tiling{static_cast<ImageTiling>(0)};
    ImageUsageFlags usage{};
    SharingMode sharingMode{static_cast<SharingMode>(0)};
    uint32_t queueFamilyIndexCount{0};
    const uint32_t* pQueueFamilyIndices = nullptr;
    ImageLayout initialLayout{static_cast<ImageLayout>(0)};
};
struct SubresourceLayout {
    DeviceSize offset{0};
    DeviceSize size{0};
    DeviceSize rowPitch{0};
    DeviceSize arrayPitch{0};
    DeviceSize depthPitch{0};
    constexpr bool operator==(SubresourceLayout const& value) const {
        return offset == value.offset && size == value.size && rowPitch == value.rowPitch && arrayPitch == value.arrayPitch && depthPitch == value.depthPitch 
        ;}
    constexpr bool operator!=(SubresourceLayout const& value) const {return !(*this == value);}
};
struct ImageViewCreateInfo {
    StructureType sType{StructureType::ImageViewCreateInfo};
    const void* pNext = nullptr;
    ImageViewCreateFlags flags{};
    Image image{};
    ImageViewType viewType{static_cast<ImageViewType>(0)};
    Format format{static_cast<Format>(0)};
    ComponentMapping components{};
    ImageSubresourceRange subresourceRange{};
};
struct BufferCopy {
    DeviceSize srcOffset{0};
    DeviceSize dstOffset{0};
    DeviceSize size{0};
    constexpr bool operator==(BufferCopy const& value) const {
        return srcOffset == value.srcOffset && dstOffset == value.dstOffset && size == value.size ;}
    constexpr bool operator!=(BufferCopy const& value) const {return !(*this == value);}
};
struct SparseMemoryBind {
    DeviceSize resourceOffset{0};
    DeviceSize size{0};
    DeviceMemory memory{};
    DeviceSize memoryOffset{0};
    SparseMemoryBindFlags flags{};
};
struct SparseImageMemoryBind {
    ImageSubresource subresource{};
    Offset3D offset{};
    Extent3D extent{};
    DeviceMemory memory{};
    DeviceSize memoryOffset{0};
    SparseMemoryBindFlags flags{};
};
struct SparseBufferMemoryBindInfo {
    Buffer buffer{};
    uint32_t bindCount{0};
    const SparseMemoryBind* pBinds = nullptr;
};
struct SparseImageOpaqueMemoryBindInfo {
    Image image{};
    uint32_t bindCount{0};
    const SparseMemoryBind* pBinds = nullptr;
};
struct SparseImageMemoryBindInfo {
    Image image{};
    uint32_t bindCount{0};
    const SparseImageMemoryBind* pBinds = nullptr;
};
struct BindSparseInfo {
    StructureType sType{StructureType::BindSparseInfo};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount{0};
    const Semaphore* pWaitSemaphores = nullptr;
    uint32_t bufferBindCount{0};
    const SparseBufferMemoryBindInfo* pBufferBinds = nullptr;
    uint32_t imageOpaqueBindCount{0};
    const SparseImageOpaqueMemoryBindInfo* pImageOpaqueBinds = nullptr;
    uint32_t imageBindCount{0};
    const SparseImageMemoryBindInfo* pImageBinds = nullptr;
    uint32_t signalSemaphoreCount{0};
    const Semaphore* pSignalSemaphores = nullptr;
};
struct ImageCopy {
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffset{};
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffset{};
    Extent3D extent{};
    constexpr bool operator==(ImageCopy const& value) const {
        return srcSubresource == value.srcSubresource && srcOffset == value.srcOffset && dstSubresource == value.dstSubresource && dstOffset == value.dstOffset 
        && extent == value.extent ;}
    constexpr bool operator!=(ImageCopy const& value) const {return !(*this == value);}
};
struct ImageBlit {
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffsets[2];
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffsets[2];
    constexpr bool operator==(ImageBlit const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 2; i++)
            is_equal &= srcOffsets[i] == value.srcOffsets[i];
        for(uint32_t i = 0; i < 2; i++)
            is_equal &= dstOffsets[i] == value.dstOffsets[i];
        return is_equal && srcSubresource == value.srcSubresource && dstSubresource == value.dstSubresource ;}
    constexpr bool operator!=(ImageBlit const& value) const {return !(*this == value);}
};
struct BufferImageCopy {
    DeviceSize bufferOffset{0};
    uint32_t bufferRowLength{0};
    uint32_t bufferImageHeight{0};
    ImageSubresourceLayers imageSubresource{};
    Offset3D imageOffset{};
    Extent3D imageExtent{};
    constexpr bool operator==(BufferImageCopy const& value) const {
        return bufferOffset == value.bufferOffset && bufferRowLength == value.bufferRowLength && bufferImageHeight == value.bufferImageHeight && imageSubresource == value.imageSubresource 
        && imageOffset == value.imageOffset && imageExtent == value.imageExtent ;}
    constexpr bool operator!=(BufferImageCopy const& value) const {return !(*this == value);}
};
struct ImageResolve {
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffset{};
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffset{};
    Extent3D extent{};
    constexpr bool operator==(ImageResolve const& value) const {
        return srcSubresource == value.srcSubresource && srcOffset == value.srcOffset && dstSubresource == value.dstSubresource && dstOffset == value.dstOffset 
        && extent == value.extent ;}
    constexpr bool operator!=(ImageResolve const& value) const {return !(*this == value);}
};
struct ShaderModuleCreateInfo {
    StructureType sType{StructureType::ShaderModuleCreateInfo};
    const void* pNext = nullptr;
    ShaderModuleCreateFlags flags{};
    size_t codeSize{0};
    const uint32_t* pCode = nullptr;
};
struct DescriptorSetLayoutBinding {
    uint32_t binding{0};
    DescriptorType descriptorType{static_cast<DescriptorType>(0)};
    uint32_t descriptorCount{0};
    ShaderStageFlags stageFlags{};
    const Sampler* pImmutableSamplers = nullptr;
};
struct DescriptorSetLayoutCreateInfo {
    StructureType sType{StructureType::DescriptorSetLayoutCreateInfo};
    const void* pNext = nullptr;
    DescriptorSetLayoutCreateFlags flags{};
    uint32_t bindingCount{0};
    const DescriptorSetLayoutBinding* pBindings = nullptr;
};
struct DescriptorPoolSize {
    DescriptorType type{static_cast<DescriptorType>(0)};
    uint32_t descriptorCount{0};
    constexpr bool operator==(DescriptorPoolSize const& value) const {
        return type == value.type && descriptorCount == value.descriptorCount ;}
    constexpr bool operator!=(DescriptorPoolSize const& value) const {return !(*this == value);}
};
struct DescriptorPoolCreateInfo {
    StructureType sType{StructureType::DescriptorPoolCreateInfo};
    const void* pNext = nullptr;
    DescriptorPoolCreateFlags flags{};
    uint32_t maxSets{0};
    uint32_t poolSizeCount{0};
    const DescriptorPoolSize* pPoolSizes = nullptr;
};
struct DescriptorSetAllocateInfo {
    StructureType sType{StructureType::DescriptorSetAllocateInfo};
    const void* pNext = nullptr;
    DescriptorPool descriptorPool{};
    uint32_t descriptorSetCount{0};
    const DescriptorSetLayout* pSetLayouts = nullptr;
};
struct SpecializationMapEntry {
    uint32_t constantID{0};
    uint32_t offset{0};
    size_t size{0};
    constexpr bool operator==(SpecializationMapEntry const& value) const {
        return constantID == value.constantID && offset == value.offset && size == value.size ;}
    constexpr bool operator!=(SpecializationMapEntry const& value) const {return !(*this == value);}
};
struct SpecializationInfo {
    uint32_t mapEntryCount{0};
    const SpecializationMapEntry* pMapEntries = nullptr;
    size_t dataSize{0};
    const void* pData = nullptr;
};
struct PipelineShaderStageCreateInfo {
    StructureType sType{StructureType::PipelineShaderStageCreateInfo};
    const void* pNext = nullptr;
    PipelineShaderStageCreateFlags flags{};
    ShaderStageFlagBits stage{static_cast<ShaderStageFlagBits>(0)};
    ShaderModule module{};
    const char* pName = nullptr;
    const SpecializationInfo* pSpecializationInfo = nullptr;
};
struct ComputePipelineCreateInfo {
    StructureType sType{StructureType::ComputePipelineCreateInfo};
    const void* pNext = nullptr;
    PipelineCreateFlags flags{};
    PipelineShaderStageCreateInfo stage{};
    PipelineLayout layout{};
    Pipeline basePipelineHandle{};
    int32_t basePipelineIndex{0};
};
struct VertexInputBindingDescription {
    uint32_t binding{0};
    uint32_t stride{0};
    VertexInputRate inputRate{static_cast<VertexInputRate>(0)};
    constexpr bool operator==(VertexInputBindingDescription const& value) const {
        return binding == value.binding && stride == value.stride && inputRate == value.inputRate ;}
    constexpr bool operator!=(VertexInputBindingDescription const& value) const {return !(*this == value);}
};
struct VertexInputAttributeDescription {
    uint32_t location{0};
    uint32_t binding{0};
    Format format{static_cast<Format>(0)};
    uint32_t offset{0};
    constexpr bool operator==(VertexInputAttributeDescription const& value) const {
        return location == value.location && binding == value.binding && format == value.format && offset == value.offset ;}
    constexpr bool operator!=(VertexInputAttributeDescription const& value) const {return !(*this == value);}
};
struct PipelineVertexInputStateCreateInfo {
    StructureType sType{StructureType::PipelineVertexInputStateCreateInfo};
    const void* pNext = nullptr;
    PipelineVertexInputStateCreateFlags flags{};
    uint32_t vertexBindingDescriptionCount{0};
    const VertexInputBindingDescription* pVertexBindingDescriptions = nullptr;
    uint32_t vertexAttributeDescriptionCount{0};
    const VertexInputAttributeDescription* pVertexAttributeDescriptions = nullptr;
};
struct PipelineInputAssemblyStateCreateInfo {
    StructureType sType{StructureType::PipelineInputAssemblyStateCreateInfo};
    const void* pNext = nullptr;
    PipelineInputAssemblyStateCreateFlags flags{};
    PrimitiveTopology topology{static_cast<PrimitiveTopology>(0)};
    Bool32 primitiveRestartEnable{0};
};
struct PipelineTessellationStateCreateInfo {
    StructureType sType{StructureType::PipelineTessellationStateCreateInfo};
    const void* pNext = nullptr;
    PipelineTessellationStateCreateFlags flags{};
    uint32_t patchControlPoints{0};
};
struct PipelineViewportStateCreateInfo {
    StructureType sType{StructureType::PipelineViewportStateCreateInfo};
    const void* pNext = nullptr;
    PipelineViewportStateCreateFlags flags{};
    uint32_t viewportCount{0};
    const Viewport* pViewports = nullptr;
    uint32_t scissorCount{0};
    const Rect2D* pScissors = nullptr;
};
struct PipelineRasterizationStateCreateInfo {
    StructureType sType{StructureType::PipelineRasterizationStateCreateInfo};
    const void* pNext = nullptr;
    PipelineRasterizationStateCreateFlags flags{};
    Bool32 depthClampEnable{0};
    Bool32 rasterizerDiscardEnable{0};
    PolygonMode polygonMode{static_cast<PolygonMode>(0)};
    CullModeFlags cullMode{};
    FrontFace frontFace{static_cast<FrontFace>(0)};
    Bool32 depthBiasEnable{0};
    float depthBiasConstantFactor{0.f};
    float depthBiasClamp{0.f};
    float depthBiasSlopeFactor{0.f};
    float lineWidth{0.f};
};
struct PipelineMultisampleStateCreateInfo {
    StructureType sType{StructureType::PipelineMultisampleStateCreateInfo};
    const void* pNext = nullptr;
    PipelineMultisampleStateCreateFlags flags{};
    SampleCountFlagBits rasterizationSamples{static_cast<SampleCountFlagBits>(0)};
    Bool32 sampleShadingEnable{0};
    float minSampleShading{0.f};
    const SampleMask* pSampleMask = nullptr;
    Bool32 alphaToCoverageEnable{0};
    Bool32 alphaToOneEnable{0};
};
struct PipelineColorBlendAttachmentState {
    Bool32 blendEnable{0};
    BlendFactor srcColorBlendFactor{static_cast<BlendFactor>(0)};
    BlendFactor dstColorBlendFactor{static_cast<BlendFactor>(0)};
    BlendOp colorBlendOp{static_cast<BlendOp>(0)};
    BlendFactor srcAlphaBlendFactor{static_cast<BlendFactor>(0)};
    BlendFactor dstAlphaBlendFactor{static_cast<BlendFactor>(0)};
    BlendOp alphaBlendOp{static_cast<BlendOp>(0)};
    ColorComponentFlags colorWriteMask{};
    constexpr bool operator==(PipelineColorBlendAttachmentState const& value) const {
        return blendEnable == value.blendEnable && srcColorBlendFactor == value.srcColorBlendFactor && dstColorBlendFactor == value.dstColorBlendFactor 
        && colorBlendOp == value.colorBlendOp && srcAlphaBlendFactor == value.srcAlphaBlendFactor && dstAlphaBlendFactor == value.dstAlphaBlendFactor 
        && alphaBlendOp == value.alphaBlendOp && colorWriteMask == value.colorWriteMask ;}
    constexpr bool operator!=(PipelineColorBlendAttachmentState const& value) const {return !(*this == value);}
};
struct PipelineColorBlendStateCreateInfo {
    StructureType sType{StructureType::PipelineColorBlendStateCreateInfo};
    const void* pNext = nullptr;
    PipelineColorBlendStateCreateFlags flags{};
    Bool32 logicOpEnable{0};
    LogicOp logicOp{static_cast<LogicOp>(0)};
    uint32_t attachmentCount{0};
    const PipelineColorBlendAttachmentState* pAttachments = nullptr;
    float blendConstants[4];
};
struct PipelineDynamicStateCreateInfo {
    StructureType sType{StructureType::PipelineDynamicStateCreateInfo};
    const void* pNext = nullptr;
    PipelineDynamicStateCreateFlags flags{};
    uint32_t dynamicStateCount{0};
    const DynamicState* pDynamicStates = nullptr;
};
struct StencilOpState {
    StencilOp failOp{static_cast<StencilOp>(0)};
    StencilOp passOp{static_cast<StencilOp>(0)};
    StencilOp depthFailOp{static_cast<StencilOp>(0)};
    CompareOp compareOp{static_cast<CompareOp>(0)};
    uint32_t compareMask{0};
    uint32_t writeMask{0};
    uint32_t reference{0};
    constexpr bool operator==(StencilOpState const& value) const {
        return failOp == value.failOp && passOp == value.passOp && depthFailOp == value.depthFailOp && compareOp == value.compareOp && compareMask == value.compareMask 
        && writeMask == value.writeMask && reference == value.reference ;}
    constexpr bool operator!=(StencilOpState const& value) const {return !(*this == value);}
};
struct PipelineDepthStencilStateCreateInfo {
    StructureType sType{StructureType::PipelineDepthStencilStateCreateInfo};
    const void* pNext = nullptr;
    PipelineDepthStencilStateCreateFlags flags{};
    Bool32 depthTestEnable{0};
    Bool32 depthWriteEnable{0};
    CompareOp depthCompareOp{static_cast<CompareOp>(0)};
    Bool32 depthBoundsTestEnable{0};
    Bool32 stencilTestEnable{0};
    StencilOpState front{};
    StencilOpState back{};
    float minDepthBounds{0.f};
    float maxDepthBounds{0.f};
};
struct GraphicsPipelineCreateInfo {
    StructureType sType{StructureType::GraphicsPipelineCreateInfo};
    const void* pNext = nullptr;
    PipelineCreateFlags flags{};
    uint32_t stageCount{0};
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    const PipelineVertexInputStateCreateInfo* pVertexInputState = nullptr;
    const PipelineInputAssemblyStateCreateInfo* pInputAssemblyState = nullptr;
    const PipelineTessellationStateCreateInfo* pTessellationState = nullptr;
    const PipelineViewportStateCreateInfo* pViewportState = nullptr;
    const PipelineRasterizationStateCreateInfo* pRasterizationState = nullptr;
    const PipelineMultisampleStateCreateInfo* pMultisampleState = nullptr;
    const PipelineDepthStencilStateCreateInfo* pDepthStencilState = nullptr;
    const PipelineColorBlendStateCreateInfo* pColorBlendState = nullptr;
    const PipelineDynamicStateCreateInfo* pDynamicState = nullptr;
    PipelineLayout layout{};
    RenderPass renderPass{};
    uint32_t subpass{0};
    Pipeline basePipelineHandle{};
    int32_t basePipelineIndex{0};
};
struct PipelineCacheCreateInfo {
    StructureType sType{StructureType::PipelineCacheCreateInfo};
    const void* pNext = nullptr;
    PipelineCacheCreateFlags flags{};
    size_t initialDataSize{0};
    const void* pInitialData = nullptr;
};
struct PushConstantRange {
    ShaderStageFlags stageFlags{};
    uint32_t offset{0};
    uint32_t size{0};
    constexpr bool operator==(PushConstantRange const& value) const {
        return stageFlags == value.stageFlags && offset == value.offset && size == value.size ;}
    constexpr bool operator!=(PushConstantRange const& value) const {return !(*this == value);}
};
struct PipelineLayoutCreateInfo {
    StructureType sType{StructureType::PipelineLayoutCreateInfo};
    const void* pNext = nullptr;
    PipelineLayoutCreateFlags flags{};
    uint32_t setLayoutCount{0};
    const DescriptorSetLayout* pSetLayouts = nullptr;
    uint32_t pushConstantRangeCount{0};
    const PushConstantRange* pPushConstantRanges = nullptr;
};
struct SamplerCreateInfo {
    StructureType sType{StructureType::SamplerCreateInfo};
    const void* pNext = nullptr;
    SamplerCreateFlags flags{};
    Filter magFilter{static_cast<Filter>(0)};
    Filter minFilter{static_cast<Filter>(0)};
    SamplerMipmapMode mipmapMode{static_cast<SamplerMipmapMode>(0)};
    SamplerAddressMode addressModeU{static_cast<SamplerAddressMode>(0)};
    SamplerAddressMode addressModeV{static_cast<SamplerAddressMode>(0)};
    SamplerAddressMode addressModeW{static_cast<SamplerAddressMode>(0)};
    float mipLodBias{0.f};
    Bool32 anisotropyEnable{0};
    float maxAnisotropy{0.f};
    Bool32 compareEnable{0};
    CompareOp compareOp{static_cast<CompareOp>(0)};
    float minLod{0.f};
    float maxLod{0.f};
    BorderColor borderColor{static_cast<BorderColor>(0)};
    Bool32 unnormalizedCoordinates{0};
};
struct CommandPoolCreateInfo {
    StructureType sType{StructureType::CommandPoolCreateInfo};
    const void* pNext = nullptr;
    CommandPoolCreateFlags flags{};
    uint32_t queueFamilyIndex{0};
};
struct CommandBufferAllocateInfo {
    StructureType sType{StructureType::CommandBufferAllocateInfo};
    const void* pNext = nullptr;
    CommandPool commandPool{};
    CommandBufferLevel level{static_cast<CommandBufferLevel>(0)};
    uint32_t commandBufferCount{0};
};
struct CommandBufferInheritanceInfo {
    StructureType sType{StructureType::CommandBufferInheritanceInfo};
    const void* pNext = nullptr;
    RenderPass renderPass{};
    uint32_t subpass{0};
    Framebuffer framebuffer{};
    Bool32 occlusionQueryEnable{0};
    QueryControlFlags queryFlags{};
    QueryPipelineStatisticFlags pipelineStatistics{};
};
struct CommandBufferBeginInfo {
    StructureType sType{StructureType::CommandBufferBeginInfo};
    const void* pNext = nullptr;
    CommandBufferUsageFlags flags{};
    const CommandBufferInheritanceInfo* pInheritanceInfo = nullptr;
};
struct ClearDepthStencilValue {
    float depth{0.f};
    uint32_t stencil{0};
    constexpr bool operator==(ClearDepthStencilValue const& value) const {
        return depth == value.depth && stencil == value.stencil ;}
    constexpr bool operator!=(ClearDepthStencilValue const& value) const {return !(*this == value);}
};
union ClearColorValue {
    float float32[4];
    int32_t int32[4];
    uint32_t uint32[4];
    constexpr bool operator==(ClearColorValue const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 4; i++)
            is_equal &= float32[i] == value.float32[i];
        for(uint32_t i = 0; i < 4; i++)
            is_equal &= int32[i] == value.int32[i];
        for(uint32_t i = 0; i < 4; i++)
            is_equal &= uint32[i] == value.uint32[i];
        return is_equal;}
    constexpr bool operator!=(ClearColorValue const& value) const {return !(*this == value);}
};
union ClearValue {
    ClearColorValue color;
    ClearDepthStencilValue depthStencil;
    constexpr bool operator==(ClearValue const& value) const {
        return color == value.color && depthStencil == value.depthStencil ;}
    constexpr bool operator!=(ClearValue const& value) const {return !(*this == value);}
};
struct RenderPassBeginInfo {
    StructureType sType{StructureType::RenderPassBeginInfo};
    const void* pNext = nullptr;
    RenderPass renderPass{};
    Framebuffer framebuffer{};
    Rect2D renderArea{};
    uint32_t clearValueCount{0};
    const ClearValue* pClearValues = nullptr;
};
struct ClearAttachment {
    ImageAspectFlags aspectMask{};
    uint32_t colorAttachment{0};
    ClearValue clearValue{};
    constexpr bool operator==(ClearAttachment const& value) const {
        return aspectMask == value.aspectMask && colorAttachment == value.colorAttachment && clearValue == value.clearValue ;}
    constexpr bool operator!=(ClearAttachment const& value) const {return !(*this == value);}
};
struct AttachmentDescription {
    AttachmentDescriptionFlags flags{};
    Format format{static_cast<Format>(0)};
    SampleCountFlagBits samples{static_cast<SampleCountFlagBits>(0)};
    AttachmentLoadOp loadOp{static_cast<AttachmentLoadOp>(0)};
    AttachmentStoreOp storeOp{static_cast<AttachmentStoreOp>(0)};
    AttachmentLoadOp stencilLoadOp{static_cast<AttachmentLoadOp>(0)};
    AttachmentStoreOp stencilStoreOp{static_cast<AttachmentStoreOp>(0)};
    ImageLayout initialLayout{static_cast<ImageLayout>(0)};
    ImageLayout finalLayout{static_cast<ImageLayout>(0)};
    constexpr bool operator==(AttachmentDescription const& value) const {
        return flags == value.flags && format == value.format && samples == value.samples && loadOp == value.loadOp && storeOp == value.storeOp && stencilLoadOp == value.stencilLoadOp 
        && stencilStoreOp == value.stencilStoreOp && initialLayout == value.initialLayout && finalLayout == value.finalLayout ;}
    constexpr bool operator!=(AttachmentDescription const& value) const {return !(*this == value);}
};
struct AttachmentReference {
    uint32_t attachment{0};
    ImageLayout layout{static_cast<ImageLayout>(0)};
    constexpr bool operator==(AttachmentReference const& value) const {
        return attachment == value.attachment && layout == value.layout ;}
    constexpr bool operator!=(AttachmentReference const& value) const {return !(*this == value);}
};
struct SubpassDescription {
    SubpassDescriptionFlags flags{};
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    uint32_t inputAttachmentCount{0};
    const AttachmentReference* pInputAttachments = nullptr;
    uint32_t colorAttachmentCount{0};
    const AttachmentReference* pColorAttachments = nullptr;
    const AttachmentReference* pResolveAttachments = nullptr;
    const AttachmentReference* pDepthStencilAttachment = nullptr;
    uint32_t preserveAttachmentCount{0};
    const uint32_t* pPreserveAttachments = nullptr;
};
struct SubpassDependency {
    uint32_t srcSubpass{0};
    uint32_t dstSubpass{0};
    PipelineStageFlags srcStageMask{};
    PipelineStageFlags dstStageMask{};
    AccessFlags srcAccessMask{};
    AccessFlags dstAccessMask{};
    DependencyFlags dependencyFlags{};
    constexpr bool operator==(SubpassDependency const& value) const {
        return srcSubpass == value.srcSubpass && dstSubpass == value.dstSubpass && srcStageMask == value.srcStageMask && dstStageMask == value.dstStageMask 
        && srcAccessMask == value.srcAccessMask && dstAccessMask == value.dstAccessMask && dependencyFlags == value.dependencyFlags ;}
    constexpr bool operator!=(SubpassDependency const& value) const {return !(*this == value);}
};
struct RenderPassCreateInfo {
    StructureType sType{StructureType::RenderPassCreateInfo};
    const void* pNext = nullptr;
    RenderPassCreateFlags flags{};
    uint32_t attachmentCount{0};
    const AttachmentDescription* pAttachments = nullptr;
    uint32_t subpassCount{0};
    const SubpassDescription* pSubpasses = nullptr;
    uint32_t dependencyCount{0};
    const SubpassDependency* pDependencies = nullptr;
};
struct EventCreateInfo {
    StructureType sType{StructureType::EventCreateInfo};
    const void* pNext = nullptr;
    EventCreateFlags flags{};
};
struct FenceCreateInfo {
    StructureType sType{StructureType::FenceCreateInfo};
    const void* pNext = nullptr;
    FenceCreateFlags flags{};
};
struct SemaphoreCreateInfo {
    StructureType sType{StructureType::SemaphoreCreateInfo};
    const void* pNext = nullptr;
    SemaphoreCreateFlags flags{};
};
struct QueryPoolCreateInfo {
    StructureType sType{StructureType::QueryPoolCreateInfo};
    const void* pNext = nullptr;
    QueryPoolCreateFlags flags{};
    QueryType queryType{static_cast<QueryType>(0)};
    uint32_t queryCount{0};
    QueryPipelineStatisticFlags pipelineStatistics{};
};
struct FramebufferCreateInfo {
    StructureType sType{StructureType::FramebufferCreateInfo};
    const void* pNext = nullptr;
    FramebufferCreateFlags flags{};
    RenderPass renderPass{};
    uint32_t attachmentCount{0};
    const ImageView* pAttachments = nullptr;
    uint32_t width{0};
    uint32_t height{0};
    uint32_t layers{0};
};
struct DrawIndirectCommand {
    uint32_t vertexCount{0};
    uint32_t instanceCount{0};
    uint32_t firstVertex{0};
    uint32_t firstInstance{0};
    constexpr bool operator==(DrawIndirectCommand const& value) const {
        return vertexCount == value.vertexCount && instanceCount == value.instanceCount && firstVertex == value.firstVertex && firstInstance == value.firstInstance 
        ;}
    constexpr bool operator!=(DrawIndirectCommand const& value) const {return !(*this == value);}
};
struct DrawIndexedIndirectCommand {
    uint32_t indexCount{0};
    uint32_t instanceCount{0};
    uint32_t firstIndex{0};
    int32_t vertexOffset{0};
    uint32_t firstInstance{0};
    constexpr bool operator==(DrawIndexedIndirectCommand const& value) const {
        return indexCount == value.indexCount && instanceCount == value.instanceCount && firstIndex == value.firstIndex && vertexOffset == value.vertexOffset 
        && firstInstance == value.firstInstance ;}
    constexpr bool operator!=(DrawIndexedIndirectCommand const& value) const {return !(*this == value);}
};
struct DispatchIndirectCommand {
    uint32_t x{0};
    uint32_t y{0};
    uint32_t z{0};
    constexpr bool operator==(DispatchIndirectCommand const& value) const {
        return x == value.x && y == value.y && z == value.z ;}
    constexpr bool operator!=(DispatchIndirectCommand const& value) const {return !(*this == value);}
};
struct SubmitInfo {
    StructureType sType{StructureType::SubmitInfo};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount{0};
    const Semaphore* pWaitSemaphores = nullptr;
    const PipelineStageFlags* pWaitDstStageMask = nullptr;
    uint32_t commandBufferCount{0};
    const CommandBuffer* pCommandBuffers = nullptr;
    uint32_t signalSemaphoreCount{0};
    const Semaphore* pSignalSemaphores = nullptr;
};
struct DisplayPropertiesKHR {
    DisplayKHR display{};
    const char* displayName = nullptr;
    Extent2D physicalDimensions{};
    Extent2D physicalResolution{};
    SurfaceTransformFlagsKHR supportedTransforms{};
    Bool32 planeReorderPossible{0};
    Bool32 persistentContent{0};
};
struct DisplayPlanePropertiesKHR {
    DisplayKHR currentDisplay{};
    uint32_t currentStackIndex{0};
};
struct DisplayModeParametersKHR {
    Extent2D visibleRegion{};
    uint32_t refreshRate{0};
    constexpr bool operator==(DisplayModeParametersKHR const& value) const {
        return visibleRegion == value.visibleRegion && refreshRate == value.refreshRate ;}
    constexpr bool operator!=(DisplayModeParametersKHR const& value) const {return !(*this == value);}
};
struct DisplayModePropertiesKHR {
    DisplayModeKHR displayMode{};
    DisplayModeParametersKHR parameters{};
};
struct DisplayModeCreateInfoKHR {
    StructureType sType{StructureType::DisplayModeCreateInfoKHR};
    const void* pNext = nullptr;
    DisplayModeCreateFlagsKHR flags{};
    DisplayModeParametersKHR parameters{};
};
struct DisplayPlaneCapabilitiesKHR {
    DisplayPlaneAlphaFlagsKHR supportedAlpha{};
    Offset2D minSrcPosition{};
    Offset2D maxSrcPosition{};
    Extent2D minSrcExtent{};
    Extent2D maxSrcExtent{};
    Offset2D minDstPosition{};
    Offset2D maxDstPosition{};
    Extent2D minDstExtent{};
    Extent2D maxDstExtent{};
    constexpr bool operator==(DisplayPlaneCapabilitiesKHR const& value) const {
        return supportedAlpha == value.supportedAlpha && minSrcPosition == value.minSrcPosition && maxSrcPosition == value.maxSrcPosition && minSrcExtent == value.minSrcExtent 
        && maxSrcExtent == value.maxSrcExtent && minDstPosition == value.minDstPosition && maxDstPosition == value.maxDstPosition && minDstExtent == value.minDstExtent 
        && maxDstExtent == value.maxDstExtent ;}
    constexpr bool operator!=(DisplayPlaneCapabilitiesKHR const& value) const {return !(*this == value);}
};
struct DisplaySurfaceCreateInfoKHR {
    StructureType sType{StructureType::DisplaySurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    DisplaySurfaceCreateFlagsKHR flags{};
    DisplayModeKHR displayMode{};
    uint32_t planeIndex{0};
    uint32_t planeStackIndex{0};
    SurfaceTransformFlagBitsKHR transform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
    float globalAlpha{0.f};
    DisplayPlaneAlphaFlagBitsKHR alphaMode{static_cast<DisplayPlaneAlphaFlagBitsKHR>(0)};
    Extent2D imageExtent{};
};
struct DisplayPresentInfoKHR {
    StructureType sType{StructureType::DisplayPresentInfoKHR};
    const void* pNext = nullptr;
    Rect2D srcRect{};
    Rect2D dstRect{};
    Bool32 persistent{0};
};
struct SurfaceCapabilitiesKHR {
    uint32_t minImageCount{0};
    uint32_t maxImageCount{0};
    Extent2D currentExtent{};
    Extent2D minImageExtent{};
    Extent2D maxImageExtent{};
    uint32_t maxImageArrayLayers{0};
    SurfaceTransformFlagsKHR supportedTransforms{};
    SurfaceTransformFlagBitsKHR currentTransform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
    CompositeAlphaFlagsKHR supportedCompositeAlpha{};
    ImageUsageFlags supportedUsageFlags{};
    constexpr bool operator==(SurfaceCapabilitiesKHR const& value) const {
        return minImageCount == value.minImageCount && maxImageCount == value.maxImageCount && currentExtent == value.currentExtent && minImageExtent == value.minImageExtent 
        && maxImageExtent == value.maxImageExtent && maxImageArrayLayers == value.maxImageArrayLayers && supportedTransforms == value.supportedTransforms 
        && currentTransform == value.currentTransform && supportedCompositeAlpha == value.supportedCompositeAlpha && supportedUsageFlags == value.supportedUsageFlags 
        ;}
    constexpr bool operator!=(SurfaceCapabilitiesKHR const& value) const {return !(*this == value);}
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct AndroidSurfaceCreateInfoKHR {
    StructureType sType{StructureType::AndroidSurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    AndroidSurfaceCreateFlagsKHR flags{};
    ANativeWindow* window = nullptr;
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
struct ViSurfaceCreateInfoNN {
    StructureType sType{StructureType::ViSurfaceCreateInfoNN};
    const void* pNext = nullptr;
    ViSurfaceCreateFlagsNN flags{};
    void* window = nullptr;
};
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
struct WaylandSurfaceCreateInfoKHR {
    StructureType sType{StructureType::WaylandSurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    WaylandSurfaceCreateFlagsKHR flags{};
    wl_display* display = nullptr;
    wl_surface* surface = nullptr;
};
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct Win32SurfaceCreateInfoKHR {
    StructureType sType{StructureType::Win32SurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    Win32SurfaceCreateFlagsKHR flags{};
    HINSTANCE hinstance{};
    HWND hwnd{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
struct XlibSurfaceCreateInfoKHR {
    StructureType sType{StructureType::XlibSurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    XlibSurfaceCreateFlagsKHR flags{};
    Display* dpy = nullptr;
    Window window{};
};
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
struct XcbSurfaceCreateInfoKHR {
    StructureType sType{StructureType::XcbSurfaceCreateInfoKHR};
    const void* pNext = nullptr;
    XcbSurfaceCreateFlagsKHR flags{};
    xcb_connection_t* connection = nullptr;
    xcb_window_t window{};
};
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
struct DirectFBSurfaceCreateInfoEXT {
    StructureType sType{StructureType::DirectfbSurfaceCreateInfoEXT};
    const void* pNext = nullptr;
    DirectFBSurfaceCreateFlagsEXT flags{};
    IDirectFB* dfb = nullptr;
    IDirectFBSurface* surface = nullptr;
};
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct ImagePipeSurfaceCreateInfoFUCHSIA {
    StructureType sType{StructureType::ImagepipeSurfaceCreateInfoFUCHSIA};
    const void* pNext = nullptr;
    ImagePipeSurfaceCreateFlagsFUCHSIA flags{};
    zx_handle_t imagePipeHandle{};
};
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
struct StreamDescriptorSurfaceCreateInfoGGP {
    StructureType sType{StructureType::StreamDescriptorSurfaceCreateInfoGGP};
    const void* pNext = nullptr;
    StreamDescriptorSurfaceCreateFlagsGGP flags{};
    GgpStreamDescriptor streamDescriptor{};
};
#endif // defined(VK_USE_PLATFORM_GGP)
struct SurfaceFormatKHR {
    Format format{static_cast<Format>(0)};
    ColorSpaceKHR colorSpace{static_cast<ColorSpaceKHR>(0)};
    constexpr bool operator==(SurfaceFormatKHR const& value) const {
        return format == value.format && colorSpace == value.colorSpace ;}
    constexpr bool operator!=(SurfaceFormatKHR const& value) const {return !(*this == value);}
};
struct SwapchainCreateInfoKHR {
    StructureType sType{StructureType::SwapchainCreateInfoKHR};
    const void* pNext = nullptr;
    SwapchainCreateFlagsKHR flags{};
    SurfaceKHR surface{};
    uint32_t minImageCount{0};
    Format imageFormat{static_cast<Format>(0)};
    ColorSpaceKHR imageColorSpace{static_cast<ColorSpaceKHR>(0)};
    Extent2D imageExtent{};
    uint32_t imageArrayLayers{0};
    ImageUsageFlags imageUsage{};
    SharingMode imageSharingMode{static_cast<SharingMode>(0)};
    uint32_t queueFamilyIndexCount{0};
    const uint32_t* pQueueFamilyIndices = nullptr;
    SurfaceTransformFlagBitsKHR preTransform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
    CompositeAlphaFlagBitsKHR compositeAlpha{static_cast<CompositeAlphaFlagBitsKHR>(0)};
    PresentModeKHR presentMode{static_cast<PresentModeKHR>(0)};
    Bool32 clipped{0};
    SwapchainKHR oldSwapchain{};
};
struct PresentInfoKHR {
    StructureType sType{StructureType::PresentInfoKHR};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount{0};
    const Semaphore* pWaitSemaphores = nullptr;
    uint32_t swapchainCount{0};
    const SwapchainKHR* pSwapchains = nullptr;
    const uint32_t* pImageIndices = nullptr;
    Result* pResults = nullptr;
};
struct DebugReportCallbackCreateInfoEXT {
    StructureType sType{StructureType::DebugReportCallbackCreateInfoEXT};
    const void* pNext = nullptr;
    DebugReportFlagsEXT flags{};
    PFN_DebugReportCallbackEXT pfnCallback{};
    void* pUserData = nullptr;
};
struct ValidationFlagsEXT {
    StructureType sType{StructureType::ValidationFlagsEXT};
    const void* pNext = nullptr;
    uint32_t disabledValidationCheckCount{0};
    const ValidationCheckEXT* pDisabledValidationChecks = nullptr;
};
struct ValidationFeaturesEXT {
    StructureType sType{StructureType::ValidationFeaturesEXT};
    const void* pNext = nullptr;
    uint32_t enabledValidationFeatureCount{0};
    const ValidationFeatureEnableEXT* pEnabledValidationFeatures = nullptr;
    uint32_t disabledValidationFeatureCount{0};
    const ValidationFeatureDisableEXT* pDisabledValidationFeatures = nullptr;
};
struct PipelineRasterizationStateRasterizationOrderAMD {
    StructureType sType{StructureType::PipelineRasterizationStateRasterizationOrderAMD};
    const void* pNext = nullptr;
    RasterizationOrderAMD rasterizationOrder{static_cast<RasterizationOrderAMD>(0)};
};
struct DebugMarkerObjectNameInfoEXT {
    StructureType sType{StructureType::DebugMarkerObjectNameInfoEXT};
    const void* pNext = nullptr;
    DebugReportObjectTypeEXT objectType{static_cast<DebugReportObjectTypeEXT>(0)};
    uint64_t object{0};
    const char* pObjectName = nullptr;
};
struct DebugMarkerObjectTagInfoEXT {
    StructureType sType{StructureType::DebugMarkerObjectTagInfoEXT};
    const void* pNext = nullptr;
    DebugReportObjectTypeEXT objectType{static_cast<DebugReportObjectTypeEXT>(0)};
    uint64_t object{0};
    uint64_t tagName{0};
    size_t tagSize{0};
    const void* pTag = nullptr;
};
struct DebugMarkerMarkerInfoEXT {
    StructureType sType{StructureType::DebugMarkerMarkerInfoEXT};
    const void* pNext = nullptr;
    const char* pMarkerName = nullptr;
    float color[4];
};
struct DedicatedAllocationImageCreateInfoNV {
    StructureType sType{StructureType::DedicatedAllocationImageCreateInfoNV};
    const void* pNext = nullptr;
    Bool32 dedicatedAllocation{0};
};
struct DedicatedAllocationBufferCreateInfoNV {
    StructureType sType{StructureType::DedicatedAllocationBufferCreateInfoNV};
    const void* pNext = nullptr;
    Bool32 dedicatedAllocation{0};
};
struct DedicatedAllocationMemoryAllocateInfoNV {
    StructureType sType{StructureType::DedicatedAllocationMemoryAllocateInfoNV};
    const void* pNext = nullptr;
    Image image{};
    Buffer buffer{};
};
struct ExternalImageFormatPropertiesNV {
    ImageFormatProperties imageFormatProperties{};
    ExternalMemoryFeatureFlagsNV externalMemoryFeatures{};
    ExternalMemoryHandleTypeFlagsNV exportFromImportedHandleTypes{};
    ExternalMemoryHandleTypeFlagsNV compatibleHandleTypes{};
    constexpr bool operator==(ExternalImageFormatPropertiesNV const& value) const {
        return imageFormatProperties == value.imageFormatProperties && externalMemoryFeatures == value.externalMemoryFeatures && exportFromImportedHandleTypes == value.exportFromImportedHandleTypes 
        && compatibleHandleTypes == value.compatibleHandleTypes ;}
    constexpr bool operator!=(ExternalImageFormatPropertiesNV const& value) const {return !(*this == value);}
};
struct ExternalMemoryImageCreateInfoNV {
    StructureType sType{StructureType::ExternalMemoryImageCreateInfoNV};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleTypes{};
};
struct ExportMemoryAllocateInfoNV {
    StructureType sType{StructureType::ExportMemoryAllocateInfoNV};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleTypes{};
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportMemoryWin32HandleInfoNV {
    StructureType sType{StructureType::ImportMemoryWin32HandleInfoNV};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleType{};
    HANDLE handle{};
};
struct ExportMemoryWin32HandleInfoNV {
    StructureType sType{StructureType::ExportMemoryWin32HandleInfoNV};
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess{};
};
struct Win32KeyedMutexAcquireReleaseInfoNV {
    StructureType sType{StructureType::Win32KeyedMutexAcquireReleaseInfoNV};
    const void* pNext = nullptr;
    uint32_t acquireCount{0};
    const DeviceMemory* pAcquireSyncs = nullptr;
    const uint64_t* pAcquireKeys = nullptr;
    const uint32_t* pAcquireTimeoutMilliseconds = nullptr;
    uint32_t releaseCount{0};
    const DeviceMemory* pReleaseSyncs = nullptr;
    const uint64_t* pReleaseKeys = nullptr;
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct PhysicalDeviceDeviceGeneratedCommandsFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceDeviceGeneratedCommandsFeaturesNV};
    void* pNext = nullptr;
    Bool32 deviceGeneratedCommands{0};
};
struct DevicePrivateDataCreateInfoEXT {
    StructureType sType{StructureType::DevicePrivateDataCreateInfoEXT};
    const void* pNext = nullptr;
    uint32_t privateDataSlotRequestCount{0};
};
struct PrivateDataSlotCreateInfoEXT {
    StructureType sType{StructureType::PrivateDataSlotCreateInfoEXT};
    const void* pNext = nullptr;
    PrivateDataSlotCreateFlagsEXT flags{};
};
struct PhysicalDevicePrivateDataFeaturesEXT {
    StructureType sType{StructureType::PhysicalDevicePrivateDataFeaturesEXT};
    void* pNext = nullptr;
    Bool32 privateData{0};
};
struct PhysicalDeviceDeviceGeneratedCommandsPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceDeviceGeneratedCommandsPropertiesNV};
    void* pNext = nullptr;
    uint32_t maxGraphicsShaderGroupCount{0};
    uint32_t maxIndirectSequenceCount{0};
    uint32_t maxIndirectCommandsTokenCount{0};
    uint32_t maxIndirectCommandsStreamCount{0};
    uint32_t maxIndirectCommandsTokenOffset{0};
    uint32_t maxIndirectCommandsStreamStride{0};
    uint32_t minSequencesCountBufferOffsetAlignment{0};
    uint32_t minSequencesIndexBufferOffsetAlignment{0};
    uint32_t minIndirectCommandsBufferOffsetAlignment{0};
};
struct GraphicsShaderGroupCreateInfoNV {
    StructureType sType{StructureType::GraphicsShaderGroupCreateInfoNV};
    const void* pNext = nullptr;
    uint32_t stageCount{0};
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    const PipelineVertexInputStateCreateInfo* pVertexInputState = nullptr;
    const PipelineTessellationStateCreateInfo* pTessellationState = nullptr;
};
struct GraphicsPipelineShaderGroupsCreateInfoNV {
    StructureType sType{StructureType::GraphicsPipelineShaderGroupsCreateInfoNV};
    const void* pNext = nullptr;
    uint32_t groupCount{0};
    const GraphicsShaderGroupCreateInfoNV* pGroups = nullptr;
    uint32_t pipelineCount{0};
    const Pipeline* pPipelines = nullptr;
};
struct BindShaderGroupIndirectCommandNV {
    uint32_t groupIndex{0};
    constexpr bool operator==(BindShaderGroupIndirectCommandNV const& value) const {
        return groupIndex == value.groupIndex ;}
    constexpr bool operator!=(BindShaderGroupIndirectCommandNV const& value) const {return !(*this == value);}
};
struct BindIndexBufferIndirectCommandNV {
    DeviceAddress bufferAddress{0};
    uint32_t size{0};
    IndexType indexType{static_cast<IndexType>(0)};
    constexpr bool operator==(BindIndexBufferIndirectCommandNV const& value) const {
        return bufferAddress == value.bufferAddress && size == value.size && indexType == value.indexType ;}
    constexpr bool operator!=(BindIndexBufferIndirectCommandNV const& value) const {return !(*this == value);}
};
struct BindVertexBufferIndirectCommandNV {
    DeviceAddress bufferAddress{0};
    uint32_t size{0};
    uint32_t stride{0};
    constexpr bool operator==(BindVertexBufferIndirectCommandNV const& value) const {
        return bufferAddress == value.bufferAddress && size == value.size && stride == value.stride ;}
    constexpr bool operator!=(BindVertexBufferIndirectCommandNV const& value) const {return !(*this == value);}
};
struct SetStateFlagsIndirectCommandNV {
    uint32_t data{0};
    constexpr bool operator==(SetStateFlagsIndirectCommandNV const& value) const {
        return data == value.data ;}
    constexpr bool operator!=(SetStateFlagsIndirectCommandNV const& value) const {return !(*this == value);}
};
struct IndirectCommandsStreamNV {
    Buffer buffer{};
    DeviceSize offset{0};
};
struct IndirectCommandsLayoutTokenNV {
    StructureType sType{StructureType::IndirectCommandsLayoutTokenNV};
    const void* pNext = nullptr;
    IndirectCommandsTokenTypeNV tokenType{static_cast<IndirectCommandsTokenTypeNV>(0)};
    uint32_t stream{0};
    uint32_t offset{0};
    uint32_t vertexBindingUnit{0};
    Bool32 vertexDynamicStride{0};
    PipelineLayout pushconstantPipelineLayout{};
    ShaderStageFlags pushconstantShaderStageFlags{};
    uint32_t pushconstantOffset{0};
    uint32_t pushconstantSize{0};
    IndirectStateFlagsNV indirectStateFlags{};
    uint32_t indexTypeCount{0};
    const IndexType* pIndexTypes = nullptr;
    const uint32_t* pIndexTypeValues = nullptr;
};
struct IndirectCommandsLayoutCreateInfoNV {
    StructureType sType{StructureType::IndirectCommandsLayoutCreateInfoNV};
    const void* pNext = nullptr;
    IndirectCommandsLayoutUsageFlagsNV flags{};
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    uint32_t tokenCount{0};
    const IndirectCommandsLayoutTokenNV* pTokens = nullptr;
    uint32_t streamCount{0};
    const uint32_t* pStreamStrides = nullptr;
};
struct GeneratedCommandsInfoNV {
    StructureType sType{StructureType::GeneratedCommandsInfoNV};
    const void* pNext = nullptr;
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    Pipeline pipeline{};
    IndirectCommandsLayoutNV indirectCommandsLayout{};
    uint32_t streamCount{0};
    const IndirectCommandsStreamNV* pStreams = nullptr;
    uint32_t sequencesCount{0};
    Buffer preprocessBuffer{};
    DeviceSize preprocessOffset{0};
    DeviceSize preprocessSize{0};
    Buffer sequencesCountBuffer{};
    DeviceSize sequencesCountOffset{0};
    Buffer sequencesIndexBuffer{};
    DeviceSize sequencesIndexOffset{0};
};
struct GeneratedCommandsMemoryRequirementsInfoNV {
    StructureType sType{StructureType::GeneratedCommandsMemoryRequirementsInfoNV};
    const void* pNext = nullptr;
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    Pipeline pipeline{};
    IndirectCommandsLayoutNV indirectCommandsLayout{};
    uint32_t maxSequencesCount{0};
};
struct PhysicalDeviceFeatures2 {
    StructureType sType{StructureType::PhysicalDeviceFeatures2};
    void* pNext = nullptr;
    PhysicalDeviceFeatures features{};
};
using PhysicalDeviceFeatures2KHR = PhysicalDeviceFeatures2;
struct PhysicalDeviceProperties2 {
    StructureType sType{StructureType::PhysicalDeviceProperties2};
    void* pNext = nullptr;
    PhysicalDeviceProperties properties{};
};
using PhysicalDeviceProperties2KHR = PhysicalDeviceProperties2;
struct FormatProperties2 {
    StructureType sType{StructureType::FormatProperties2};
    void* pNext = nullptr;
    FormatProperties formatProperties{};
};
using FormatProperties2KHR = FormatProperties2;
struct ImageFormatProperties2 {
    StructureType sType{StructureType::ImageFormatProperties2};
    void* pNext = nullptr;
    ImageFormatProperties imageFormatProperties{};
};
using ImageFormatProperties2KHR = ImageFormatProperties2;
struct PhysicalDeviceImageFormatInfo2 {
    StructureType sType{StructureType::PhysicalDeviceImageFormatInfo2};
    const void* pNext = nullptr;
    Format format{static_cast<Format>(0)};
    ImageType type{static_cast<ImageType>(0)};
    ImageTiling tiling{static_cast<ImageTiling>(0)};
    ImageUsageFlags usage{};
    ImageCreateFlags flags{};
};
using PhysicalDeviceImageFormatInfo2KHR = PhysicalDeviceImageFormatInfo2;
struct QueueFamilyProperties2 {
    StructureType sType{StructureType::QueueFamilyProperties2};
    void* pNext = nullptr;
    QueueFamilyProperties queueFamilyProperties{};
};
using QueueFamilyProperties2KHR = QueueFamilyProperties2;
struct PhysicalDeviceMemoryProperties2 {
    StructureType sType{StructureType::PhysicalDeviceMemoryProperties2};
    void* pNext = nullptr;
    PhysicalDeviceMemoryProperties memoryProperties{};
};
using PhysicalDeviceMemoryProperties2KHR = PhysicalDeviceMemoryProperties2;
struct SparseImageFormatProperties2 {
    StructureType sType{StructureType::SparseImageFormatProperties2};
    void* pNext = nullptr;
    SparseImageFormatProperties properties{};
};
using SparseImageFormatProperties2KHR = SparseImageFormatProperties2;
struct PhysicalDeviceSparseImageFormatInfo2 {
    StructureType sType{StructureType::PhysicalDeviceSparseImageFormatInfo2};
    const void* pNext = nullptr;
    Format format{static_cast<Format>(0)};
    ImageType type{static_cast<ImageType>(0)};
    SampleCountFlagBits samples{static_cast<SampleCountFlagBits>(0)};
    ImageUsageFlags usage{};
    ImageTiling tiling{static_cast<ImageTiling>(0)};
};
using PhysicalDeviceSparseImageFormatInfo2KHR = PhysicalDeviceSparseImageFormatInfo2;
struct PhysicalDevicePushDescriptorPropertiesKHR {
    StructureType sType{StructureType::PhysicalDevicePushDescriptorPropertiesKHR};
    void* pNext = nullptr;
    uint32_t maxPushDescriptors{0};
};
struct ConformanceVersion {
    uint8_t major{0};
    uint8_t minor{0};
    uint8_t subminor{0};
    uint8_t patch{0};
    constexpr bool operator==(ConformanceVersion const& value) const {
        return major == value.major && minor == value.minor && subminor == value.subminor && patch == value.patch ;}
    constexpr bool operator!=(ConformanceVersion const& value) const {return !(*this == value);}
};
using ConformanceVersionKHR = ConformanceVersion;
struct PhysicalDeviceDriverProperties {
    StructureType sType{StructureType::PhysicalDeviceDriverProperties};
    void* pNext = nullptr;
    DriverId driverID{static_cast<DriverId>(0)};
    char driverName[MAX_DRIVER_NAME_SIZE];
    char driverInfo[MAX_DRIVER_INFO_SIZE];
    ConformanceVersion conformanceVersion{};
};
using PhysicalDeviceDriverPropertiesKHR = PhysicalDeviceDriverProperties;
struct RectLayerKHR {
    Offset2D offset{};
    Extent2D extent{};
    uint32_t layer{0};
    constexpr bool operator==(RectLayerKHR const& value) const {
        return offset == value.offset && extent == value.extent && layer == value.layer ;}
    constexpr bool operator!=(RectLayerKHR const& value) const {return !(*this == value);}
};
struct PresentRegionKHR {
    uint32_t rectangleCount{0};
    const RectLayerKHR* pRectangles = nullptr;
};
struct PresentRegionsKHR {
    StructureType sType{StructureType::PresentRegionsKHR};
    const void* pNext = nullptr;
    uint32_t swapchainCount{0};
    const PresentRegionKHR* pRegions = nullptr;
};
struct PhysicalDeviceVariablePointersFeatures {
    StructureType sType{StructureType::PhysicalDeviceVariablePointersFeatures};
    void* pNext = nullptr;
    Bool32 variablePointersStorageBuffer{0};
    Bool32 variablePointers{0};
};
using PhysicalDeviceVariablePointersFeaturesKHR = PhysicalDeviceVariablePointersFeatures;
using PhysicalDeviceVariablePointerFeaturesKHR = PhysicalDeviceVariablePointersFeatures;
using PhysicalDeviceVariablePointerFeatures = PhysicalDeviceVariablePointersFeatures;
struct ExternalMemoryProperties {
    ExternalMemoryFeatureFlags externalMemoryFeatures{};
    ExternalMemoryHandleTypeFlags exportFromImportedHandleTypes{};
    ExternalMemoryHandleTypeFlags compatibleHandleTypes{};
    constexpr bool operator==(ExternalMemoryProperties const& value) const {
        return externalMemoryFeatures == value.externalMemoryFeatures && exportFromImportedHandleTypes == value.exportFromImportedHandleTypes 
        && compatibleHandleTypes == value.compatibleHandleTypes ;}
    constexpr bool operator!=(ExternalMemoryProperties const& value) const {return !(*this == value);}
};
using ExternalMemoryPropertiesKHR = ExternalMemoryProperties;
struct PhysicalDeviceExternalImageFormatInfo {
    StructureType sType{StructureType::PhysicalDeviceExternalImageFormatInfo};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
};
using PhysicalDeviceExternalImageFormatInfoKHR = PhysicalDeviceExternalImageFormatInfo;
struct ExternalImageFormatProperties {
    StructureType sType{StructureType::ExternalImageFormatProperties};
    void* pNext = nullptr;
    ExternalMemoryProperties externalMemoryProperties{};
};
using ExternalImageFormatPropertiesKHR = ExternalImageFormatProperties;
struct PhysicalDeviceExternalBufferInfo {
    StructureType sType{StructureType::PhysicalDeviceExternalBufferInfo};
    const void* pNext = nullptr;
    BufferCreateFlags flags{};
    BufferUsageFlags usage{};
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
};
using PhysicalDeviceExternalBufferInfoKHR = PhysicalDeviceExternalBufferInfo;
struct ExternalBufferProperties {
    StructureType sType{StructureType::ExternalBufferProperties};
    void* pNext = nullptr;
    ExternalMemoryProperties externalMemoryProperties{};
};
using ExternalBufferPropertiesKHR = ExternalBufferProperties;
struct PhysicalDeviceIDProperties {
    StructureType sType{StructureType::PhysicalDeviceIdProperties};
    void* pNext = nullptr;
    uint8_t deviceUUID[UUID_SIZE];
    uint8_t driverUUID[UUID_SIZE];
    uint8_t deviceLUID[LUID_SIZE];
    uint32_t deviceNodeMask{0};
    Bool32 deviceLUIDValid{0};
};
using PhysicalDeviceIDPropertiesKHR = PhysicalDeviceIDProperties;
struct ExternalMemoryImageCreateInfo {
    StructureType sType{StructureType::ExternalMemoryImageCreateInfo};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes{};
};
using ExternalMemoryImageCreateInfoKHR = ExternalMemoryImageCreateInfo;
struct ExternalMemoryBufferCreateInfo {
    StructureType sType{StructureType::ExternalMemoryBufferCreateInfo};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes{};
};
using ExternalMemoryBufferCreateInfoKHR = ExternalMemoryBufferCreateInfo;
struct ExportMemoryAllocateInfo {
    StructureType sType{StructureType::ExportMemoryAllocateInfo};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes{};
};
using ExportMemoryAllocateInfoKHR = ExportMemoryAllocateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportMemoryWin32HandleInfoKHR {
    StructureType sType{StructureType::ImportMemoryWin32HandleInfoKHR};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
    HANDLE handle{};
    LPCWSTR name{};
};
struct ExportMemoryWin32HandleInfoKHR {
    StructureType sType{StructureType::ExportMemoryWin32HandleInfoKHR};
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess{};
    LPCWSTR name{};
};
struct MemoryWin32HandlePropertiesKHR {
    StructureType sType{StructureType::MemoryWin32HandlePropertiesKHR};
    void* pNext = nullptr;
    uint32_t memoryTypeBits{0};
};
struct MemoryGetWin32HandleInfoKHR {
    StructureType sType{StructureType::MemoryGetWin32HandleInfoKHR};
    const void* pNext = nullptr;
    DeviceMemory memory{};
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportMemoryFdInfoKHR {
    StructureType sType{StructureType::ImportMemoryFdInfoKHR};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
    int fd{0};
};
struct MemoryFdPropertiesKHR {
    StructureType sType{StructureType::MemoryFdPropertiesKHR};
    void* pNext = nullptr;
    uint32_t memoryTypeBits{0};
};
struct MemoryGetFdInfoKHR {
    StructureType sType{StructureType::MemoryGetFdInfoKHR};
    const void* pNext = nullptr;
    DeviceMemory memory{};
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct Win32KeyedMutexAcquireReleaseInfoKHR {
    StructureType sType{StructureType::Win32KeyedMutexAcquireReleaseInfoKHR};
    const void* pNext = nullptr;
    uint32_t acquireCount{0};
    const DeviceMemory* pAcquireSyncs = nullptr;
    const uint64_t* pAcquireKeys = nullptr;
    const uint32_t* pAcquireTimeouts = nullptr;
    uint32_t releaseCount{0};
    const DeviceMemory* pReleaseSyncs = nullptr;
    const uint64_t* pReleaseKeys = nullptr;
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct PhysicalDeviceExternalSemaphoreInfo {
    StructureType sType{StructureType::PhysicalDeviceExternalSemaphoreInfo};
    const void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlagBits handleType{static_cast<ExternalSemaphoreHandleTypeFlagBits>(0)};
};
using PhysicalDeviceExternalSemaphoreInfoKHR = PhysicalDeviceExternalSemaphoreInfo;
struct ExternalSemaphoreProperties {
    StructureType sType{StructureType::ExternalSemaphoreProperties};
    void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlags exportFromImportedHandleTypes{};
    ExternalSemaphoreHandleTypeFlags compatibleHandleTypes{};
    ExternalSemaphoreFeatureFlags externalSemaphoreFeatures{};
};
using ExternalSemaphorePropertiesKHR = ExternalSemaphoreProperties;
struct ExportSemaphoreCreateInfo {
    StructureType sType{StructureType::ExportSemaphoreCreateInfo};
    const void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlags handleTypes{};
};
using ExportSemaphoreCreateInfoKHR = ExportSemaphoreCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportSemaphoreWin32HandleInfoKHR {
    StructureType sType{StructureType::ImportSemaphoreWin32HandleInfoKHR};
    const void* pNext = nullptr;
    Semaphore semaphore{};
    SemaphoreImportFlags flags{};
    ExternalSemaphoreHandleTypeFlagBits handleType{static_cast<ExternalSemaphoreHandleTypeFlagBits>(0)};
    HANDLE handle{};
    LPCWSTR name{};
};
struct ExportSemaphoreWin32HandleInfoKHR {
    StructureType sType{StructureType::ExportSemaphoreWin32HandleInfoKHR};
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess{};
    LPCWSTR name{};
};
struct D3D12FenceSubmitInfoKHR {
    StructureType sType{StructureType::D3D12FenceSubmitInfoKHR};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreValuesCount{0};
    const uint64_t* pWaitSemaphoreValues = nullptr;
    uint32_t signalSemaphoreValuesCount{0};
    const uint64_t* pSignalSemaphoreValues = nullptr;
};
struct SemaphoreGetWin32HandleInfoKHR {
    StructureType sType{StructureType::SemaphoreGetWin32HandleInfoKHR};
    const void* pNext = nullptr;
    Semaphore semaphore{};
    ExternalSemaphoreHandleTypeFlagBits handleType{static_cast<ExternalSemaphoreHandleTypeFlagBits>(0)};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportSemaphoreFdInfoKHR {
    StructureType sType{StructureType::ImportSemaphoreFdInfoKHR};
    const void* pNext = nullptr;
    Semaphore semaphore{};
    SemaphoreImportFlags flags{};
    ExternalSemaphoreHandleTypeFlagBits handleType{static_cast<ExternalSemaphoreHandleTypeFlagBits>(0)};
    int fd{0};
};
struct SemaphoreGetFdInfoKHR {
    StructureType sType{StructureType::SemaphoreGetFdInfoKHR};
    const void* pNext = nullptr;
    Semaphore semaphore{};
    ExternalSemaphoreHandleTypeFlagBits handleType{static_cast<ExternalSemaphoreHandleTypeFlagBits>(0)};
};
struct PhysicalDeviceExternalFenceInfo {
    StructureType sType{StructureType::PhysicalDeviceExternalFenceInfo};
    const void* pNext = nullptr;
    ExternalFenceHandleTypeFlagBits handleType{static_cast<ExternalFenceHandleTypeFlagBits>(0)};
};
using PhysicalDeviceExternalFenceInfoKHR = PhysicalDeviceExternalFenceInfo;
struct ExternalFenceProperties {
    StructureType sType{StructureType::ExternalFenceProperties};
    void* pNext = nullptr;
    ExternalFenceHandleTypeFlags exportFromImportedHandleTypes{};
    ExternalFenceHandleTypeFlags compatibleHandleTypes{};
    ExternalFenceFeatureFlags externalFenceFeatures{};
};
using ExternalFencePropertiesKHR = ExternalFenceProperties;
struct ExportFenceCreateInfo {
    StructureType sType{StructureType::ExportFenceCreateInfo};
    const void* pNext = nullptr;
    ExternalFenceHandleTypeFlags handleTypes{};
};
using ExportFenceCreateInfoKHR = ExportFenceCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportFenceWin32HandleInfoKHR {
    StructureType sType{StructureType::ImportFenceWin32HandleInfoKHR};
    const void* pNext = nullptr;
    Fence fence{};
    FenceImportFlags flags{};
    ExternalFenceHandleTypeFlagBits handleType{static_cast<ExternalFenceHandleTypeFlagBits>(0)};
    HANDLE handle{};
    LPCWSTR name{};
};
struct ExportFenceWin32HandleInfoKHR {
    StructureType sType{StructureType::ExportFenceWin32HandleInfoKHR};
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess{};
    LPCWSTR name{};
};
struct FenceGetWin32HandleInfoKHR {
    StructureType sType{StructureType::FenceGetWin32HandleInfoKHR};
    const void* pNext = nullptr;
    Fence fence{};
    ExternalFenceHandleTypeFlagBits handleType{static_cast<ExternalFenceHandleTypeFlagBits>(0)};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportFenceFdInfoKHR {
    StructureType sType{StructureType::ImportFenceFdInfoKHR};
    const void* pNext = nullptr;
    Fence fence{};
    FenceImportFlags flags{};
    ExternalFenceHandleTypeFlagBits handleType{static_cast<ExternalFenceHandleTypeFlagBits>(0)};
    int fd{0};
};
struct FenceGetFdInfoKHR {
    StructureType sType{StructureType::FenceGetFdInfoKHR};
    const void* pNext = nullptr;
    Fence fence{};
    ExternalFenceHandleTypeFlagBits handleType{static_cast<ExternalFenceHandleTypeFlagBits>(0)};
};
struct PhysicalDeviceMultiviewFeatures {
    StructureType sType{StructureType::PhysicalDeviceMultiviewFeatures};
    void* pNext = nullptr;
    Bool32 multiview{0};
    Bool32 multiviewGeometryShader{0};
    Bool32 multiviewTessellationShader{0};
};
using PhysicalDeviceMultiviewFeaturesKHR = PhysicalDeviceMultiviewFeatures;
struct PhysicalDeviceMultiviewProperties {
    StructureType sType{StructureType::PhysicalDeviceMultiviewProperties};
    void* pNext = nullptr;
    uint32_t maxMultiviewViewCount{0};
    uint32_t maxMultiviewInstanceIndex{0};
};
using PhysicalDeviceMultiviewPropertiesKHR = PhysicalDeviceMultiviewProperties;
struct RenderPassMultiviewCreateInfo {
    StructureType sType{StructureType::RenderPassMultiviewCreateInfo};
    const void* pNext = nullptr;
    uint32_t subpassCount{0};
    const uint32_t* pViewMasks = nullptr;
    uint32_t dependencyCount{0};
    const int32_t* pViewOffsets = nullptr;
    uint32_t correlationMaskCount{0};
    const uint32_t* pCorrelationMasks = nullptr;
};
using RenderPassMultiviewCreateInfoKHR = RenderPassMultiviewCreateInfo;
struct SurfaceCapabilities2EXT {
    StructureType sType{StructureType::SurfaceCapabilities2EXT};
    void* pNext = nullptr;
    uint32_t minImageCount{0};
    uint32_t maxImageCount{0};
    Extent2D currentExtent{};
    Extent2D minImageExtent{};
    Extent2D maxImageExtent{};
    uint32_t maxImageArrayLayers{0};
    SurfaceTransformFlagsKHR supportedTransforms{};
    SurfaceTransformFlagBitsKHR currentTransform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
    CompositeAlphaFlagsKHR supportedCompositeAlpha{};
    ImageUsageFlags supportedUsageFlags{};
    SurfaceCounterFlagsEXT supportedSurfaceCounters{};
};
struct DisplayPowerInfoEXT {
    StructureType sType{StructureType::DisplayPowerInfoEXT};
    const void* pNext = nullptr;
    DisplayPowerStateEXT powerState{static_cast<DisplayPowerStateEXT>(0)};
};
struct DeviceEventInfoEXT {
    StructureType sType{StructureType::DeviceEventInfoEXT};
    const void* pNext = nullptr;
    DeviceEventTypeEXT deviceEvent{static_cast<DeviceEventTypeEXT>(0)};
};
struct DisplayEventInfoEXT {
    StructureType sType{StructureType::DisplayEventInfoEXT};
    const void* pNext = nullptr;
    DisplayEventTypeEXT displayEvent{static_cast<DisplayEventTypeEXT>(0)};
};
struct SwapchainCounterCreateInfoEXT {
    StructureType sType{StructureType::SwapchainCounterCreateInfoEXT};
    const void* pNext = nullptr;
    SurfaceCounterFlagsEXT surfaceCounters{};
};
struct PhysicalDeviceGroupProperties {
    StructureType sType{StructureType::PhysicalDeviceGroupProperties};
    void* pNext = nullptr;
    uint32_t physicalDeviceCount{0};
    PhysicalDevice physicalDevices[MAX_DEVICE_GROUP_SIZE];
    Bool32 subsetAllocation{0};
};
using PhysicalDeviceGroupPropertiesKHR = PhysicalDeviceGroupProperties;
struct MemoryAllocateFlagsInfo {
    StructureType sType{StructureType::MemoryAllocateFlagsInfo};
    const void* pNext = nullptr;
    MemoryAllocateFlags flags{};
    uint32_t deviceMask{0};
};
using MemoryAllocateFlagsInfoKHR = MemoryAllocateFlagsInfo;
struct BindBufferMemoryInfo {
    StructureType sType{StructureType::BindBufferMemoryInfo};
    const void* pNext = nullptr;
    Buffer buffer{};
    DeviceMemory memory{};
    DeviceSize memoryOffset{0};
};
using BindBufferMemoryInfoKHR = BindBufferMemoryInfo;
struct BindBufferMemoryDeviceGroupInfo {
    StructureType sType{StructureType::BindBufferMemoryDeviceGroupInfo};
    const void* pNext = nullptr;
    uint32_t deviceIndexCount{0};
    const uint32_t* pDeviceIndices = nullptr;
};
using BindBufferMemoryDeviceGroupInfoKHR = BindBufferMemoryDeviceGroupInfo;
struct BindImageMemoryInfo {
    StructureType sType{StructureType::BindImageMemoryInfo};
    const void* pNext = nullptr;
    Image image{};
    DeviceMemory memory{};
    DeviceSize memoryOffset{0};
};
using BindImageMemoryInfoKHR = BindImageMemoryInfo;
struct BindImageMemoryDeviceGroupInfo {
    StructureType sType{StructureType::BindImageMemoryDeviceGroupInfo};
    const void* pNext = nullptr;
    uint32_t deviceIndexCount{0};
    const uint32_t* pDeviceIndices = nullptr;
    uint32_t splitInstanceBindRegionCount{0};
    const Rect2D* pSplitInstanceBindRegions = nullptr;
};
using BindImageMemoryDeviceGroupInfoKHR = BindImageMemoryDeviceGroupInfo;
struct DeviceGroupRenderPassBeginInfo {
    StructureType sType{StructureType::DeviceGroupRenderPassBeginInfo};
    const void* pNext = nullptr;
    uint32_t deviceMask{0};
    uint32_t deviceRenderAreaCount{0};
    const Rect2D* pDeviceRenderAreas = nullptr;
};
using DeviceGroupRenderPassBeginInfoKHR = DeviceGroupRenderPassBeginInfo;
struct DeviceGroupCommandBufferBeginInfo {
    StructureType sType{StructureType::DeviceGroupCommandBufferBeginInfo};
    const void* pNext = nullptr;
    uint32_t deviceMask{0};
};
using DeviceGroupCommandBufferBeginInfoKHR = DeviceGroupCommandBufferBeginInfo;
struct DeviceGroupSubmitInfo {
    StructureType sType{StructureType::DeviceGroupSubmitInfo};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount{0};
    const uint32_t* pWaitSemaphoreDeviceIndices = nullptr;
    uint32_t commandBufferCount{0};
    const uint32_t* pCommandBufferDeviceMasks = nullptr;
    uint32_t signalSemaphoreCount{0};
    const uint32_t* pSignalSemaphoreDeviceIndices = nullptr;
};
using DeviceGroupSubmitInfoKHR = DeviceGroupSubmitInfo;
struct DeviceGroupBindSparseInfo {
    StructureType sType{StructureType::DeviceGroupBindSparseInfo};
    const void* pNext = nullptr;
    uint32_t resourceDeviceIndex{0};
    uint32_t memoryDeviceIndex{0};
};
using DeviceGroupBindSparseInfoKHR = DeviceGroupBindSparseInfo;
struct DeviceGroupPresentCapabilitiesKHR {
    StructureType sType{StructureType::DeviceGroupPresentCapabilitiesKHR};
    const void* pNext = nullptr;
    uint32_t presentMask[MAX_DEVICE_GROUP_SIZE];
    DeviceGroupPresentModeFlagsKHR modes{};
};
struct ImageSwapchainCreateInfoKHR {
    StructureType sType{StructureType::ImageSwapchainCreateInfoKHR};
    const void* pNext = nullptr;
    SwapchainKHR swapchain{};
};
struct BindImageMemorySwapchainInfoKHR {
    StructureType sType{StructureType::BindImageMemorySwapchainInfoKHR};
    const void* pNext = nullptr;
    SwapchainKHR swapchain{};
    uint32_t imageIndex{0};
};
struct AcquireNextImageInfoKHR {
    StructureType sType{StructureType::AcquireNextImageInfoKHR};
    const void* pNext = nullptr;
    SwapchainKHR swapchain{};
    uint64_t timeout{0};
    Semaphore semaphore{};
    Fence fence{};
    uint32_t deviceMask{0};
};
struct DeviceGroupPresentInfoKHR {
    StructureType sType{StructureType::DeviceGroupPresentInfoKHR};
    const void* pNext = nullptr;
    uint32_t swapchainCount{0};
    const uint32_t* pDeviceMasks = nullptr;
    DeviceGroupPresentModeFlagBitsKHR mode{static_cast<DeviceGroupPresentModeFlagBitsKHR>(0)};
};
struct DeviceGroupDeviceCreateInfo {
    StructureType sType{StructureType::DeviceGroupDeviceCreateInfo};
    const void* pNext = nullptr;
    uint32_t physicalDeviceCount{0};
    const PhysicalDevice* pPhysicalDevices = nullptr;
};
using DeviceGroupDeviceCreateInfoKHR = DeviceGroupDeviceCreateInfo;
struct DeviceGroupSwapchainCreateInfoKHR {
    StructureType sType{StructureType::DeviceGroupSwapchainCreateInfoKHR};
    const void* pNext = nullptr;
    DeviceGroupPresentModeFlagsKHR modes{};
};
struct DescriptorUpdateTemplateEntry {
    uint32_t dstBinding{0};
    uint32_t dstArrayElement{0};
    uint32_t descriptorCount{0};
    DescriptorType descriptorType{static_cast<DescriptorType>(0)};
    size_t offset{0};
    size_t stride{0};
    constexpr bool operator==(DescriptorUpdateTemplateEntry const& value) const {
        return dstBinding == value.dstBinding && dstArrayElement == value.dstArrayElement && descriptorCount == value.descriptorCount && descriptorType == value.descriptorType 
        && offset == value.offset && stride == value.stride ;}
    constexpr bool operator!=(DescriptorUpdateTemplateEntry const& value) const {return !(*this == value);}
};
using DescriptorUpdateTemplateEntryKHR = DescriptorUpdateTemplateEntry;
struct DescriptorUpdateTemplateCreateInfo {
    StructureType sType{StructureType::DescriptorUpdateTemplateCreateInfo};
    const void* pNext = nullptr;
    DescriptorUpdateTemplateCreateFlags flags{};
    uint32_t descriptorUpdateEntryCount{0};
    const DescriptorUpdateTemplateEntry* pDescriptorUpdateEntries = nullptr;
    DescriptorUpdateTemplateType templateType{static_cast<DescriptorUpdateTemplateType>(0)};
    DescriptorSetLayout descriptorSetLayout{};
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    PipelineLayout pipelineLayout{};
    uint32_t set{0};
};
using DescriptorUpdateTemplateCreateInfoKHR = DescriptorUpdateTemplateCreateInfo;
struct XYColorEXT {
    float x{0.f};
    float y{0.f};
    constexpr bool operator==(XYColorEXT const& value) const {
        return x == value.x && y == value.y ;}
    constexpr bool operator!=(XYColorEXT const& value) const {return !(*this == value);}
};
struct HdrMetadataEXT {
    StructureType sType{StructureType::HdrMetadataEXT};
    const void* pNext = nullptr;
    XYColorEXT displayPrimaryRed{};
    XYColorEXT displayPrimaryGreen{};
    XYColorEXT displayPrimaryBlue{};
    XYColorEXT whitePoint{};
    float maxLuminance{0.f};
    float minLuminance{0.f};
    float maxContentLightLevel{0.f};
    float maxFrameAverageLightLevel{0.f};
};
struct DisplayNativeHdrSurfaceCapabilitiesAMD {
    StructureType sType{StructureType::DisplayNativeHdrSurfaceCapabilitiesAMD};
    void* pNext = nullptr;
    Bool32 localDimmingSupport{0};
};
struct SwapchainDisplayNativeHdrCreateInfoAMD {
    StructureType sType{StructureType::SwapchainDisplayNativeHdrCreateInfoAMD};
    const void* pNext = nullptr;
    Bool32 localDimmingEnable{0};
};
struct RefreshCycleDurationGOOGLE {
    uint64_t refreshDuration{0};
    constexpr bool operator==(RefreshCycleDurationGOOGLE const& value) const {
        return refreshDuration == value.refreshDuration ;}
    constexpr bool operator!=(RefreshCycleDurationGOOGLE const& value) const {return !(*this == value);}
};
struct PastPresentationTimingGOOGLE {
    uint32_t presentID{0};
    uint64_t desiredPresentTime{0};
    uint64_t actualPresentTime{0};
    uint64_t earliestPresentTime{0};
    uint64_t presentMargin{0};
    constexpr bool operator==(PastPresentationTimingGOOGLE const& value) const {
        return presentID == value.presentID && desiredPresentTime == value.desiredPresentTime && actualPresentTime == value.actualPresentTime && earliestPresentTime == value.earliestPresentTime 
        && presentMargin == value.presentMargin ;}
    constexpr bool operator!=(PastPresentationTimingGOOGLE const& value) const {return !(*this == value);}
};
struct PresentTimeGOOGLE {
    uint32_t presentID{0};
    uint64_t desiredPresentTime{0};
    constexpr bool operator==(PresentTimeGOOGLE const& value) const {
        return presentID == value.presentID && desiredPresentTime == value.desiredPresentTime ;}
    constexpr bool operator!=(PresentTimeGOOGLE const& value) const {return !(*this == value);}
};
struct PresentTimesInfoGOOGLE {
    StructureType sType{StructureType::PresentTimesInfoGOOGLE};
    const void* pNext = nullptr;
    uint32_t swapchainCount{0};
    const PresentTimeGOOGLE* pTimes = nullptr;
};
#if defined(VK_USE_PLATFORM_IOS_MVK)
struct IOSSurfaceCreateInfoMVK {
    StructureType sType{StructureType::IosSurfaceCreateInfoMVK};
    const void* pNext = nullptr;
    IOSSurfaceCreateFlagsMVK flags{};
    const void* pView = nullptr;
};
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
struct MacOSSurfaceCreateInfoMVK {
    StructureType sType{StructureType::MacosSurfaceCreateInfoMVK};
    const void* pNext = nullptr;
    MacOSSurfaceCreateFlagsMVK flags{};
    const void* pView = nullptr;
};
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
struct MetalSurfaceCreateInfoEXT {
    StructureType sType{StructureType::MetalSurfaceCreateInfoEXT};
    const void* pNext = nullptr;
    MetalSurfaceCreateFlagsEXT flags{};
    const CAMetalLayer* pLayer = nullptr;
};
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
struct ViewportWScalingNV {
    float xcoeff{0.f};
    float ycoeff{0.f};
    constexpr bool operator==(ViewportWScalingNV const& value) const {
        return xcoeff == value.xcoeff && ycoeff == value.ycoeff ;}
    constexpr bool operator!=(ViewportWScalingNV const& value) const {return !(*this == value);}
};
struct PipelineViewportWScalingStateCreateInfoNV {
    StructureType sType{StructureType::PipelineViewportWScalingStateCreateInfoNV};
    const void* pNext = nullptr;
    Bool32 viewportWScalingEnable{0};
    uint32_t viewportCount{0};
    const ViewportWScalingNV* pViewportWScalings = nullptr;
};
struct ViewportSwizzleNV {
    ViewportCoordinateSwizzleNV x{static_cast<ViewportCoordinateSwizzleNV>(0)};
    ViewportCoordinateSwizzleNV y{static_cast<ViewportCoordinateSwizzleNV>(0)};
    ViewportCoordinateSwizzleNV z{static_cast<ViewportCoordinateSwizzleNV>(0)};
    ViewportCoordinateSwizzleNV w{static_cast<ViewportCoordinateSwizzleNV>(0)};
    constexpr bool operator==(ViewportSwizzleNV const& value) const {
        return x == value.x && y == value.y && z == value.z && w == value.w ;}
    constexpr bool operator!=(ViewportSwizzleNV const& value) const {return !(*this == value);}
};
struct PipelineViewportSwizzleStateCreateInfoNV {
    StructureType sType{StructureType::PipelineViewportSwizzleStateCreateInfoNV};
    const void* pNext = nullptr;
    PipelineViewportSwizzleStateCreateFlagsNV flags{};
    uint32_t viewportCount{0};
    const ViewportSwizzleNV* pViewportSwizzles = nullptr;
};
struct PhysicalDeviceDiscardRectanglePropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceDiscardRectanglePropertiesEXT};
    void* pNext = nullptr;
    uint32_t maxDiscardRectangles{0};
};
struct PipelineDiscardRectangleStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineDiscardRectangleStateCreateInfoEXT};
    const void* pNext = nullptr;
    PipelineDiscardRectangleStateCreateFlagsEXT flags{};
    DiscardRectangleModeEXT discardRectangleMode{static_cast<DiscardRectangleModeEXT>(0)};
    uint32_t discardRectangleCount{0};
    const Rect2D* pDiscardRectangles = nullptr;
};
struct PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX {
    StructureType sType{StructureType::PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX};
    void* pNext = nullptr;
    Bool32 perViewPositionAllComponents{0};
};
struct InputAttachmentAspectReference {
    uint32_t subpass{0};
    uint32_t inputAttachmentIndex{0};
    ImageAspectFlags aspectMask{};
    constexpr bool operator==(InputAttachmentAspectReference const& value) const {
        return subpass == value.subpass && inputAttachmentIndex == value.inputAttachmentIndex && aspectMask == value.aspectMask ;}
    constexpr bool operator!=(InputAttachmentAspectReference const& value) const {return !(*this == value);}
};
using InputAttachmentAspectReferenceKHR = InputAttachmentAspectReference;
struct RenderPassInputAttachmentAspectCreateInfo {
    StructureType sType{StructureType::RenderPassInputAttachmentAspectCreateInfo};
    const void* pNext = nullptr;
    uint32_t aspectReferenceCount{0};
    const InputAttachmentAspectReference* pAspectReferences = nullptr;
};
using RenderPassInputAttachmentAspectCreateInfoKHR = RenderPassInputAttachmentAspectCreateInfo;
struct PhysicalDeviceSurfaceInfo2KHR {
    StructureType sType{StructureType::PhysicalDeviceSurfaceInfo2KHR};
    const void* pNext = nullptr;
    SurfaceKHR surface{};
};
struct SurfaceCapabilities2KHR {
    StructureType sType{StructureType::SurfaceCapabilities2KHR};
    void* pNext = nullptr;
    SurfaceCapabilitiesKHR surfaceCapabilities{};
};
struct SurfaceFormat2KHR {
    StructureType sType{StructureType::SurfaceFormat2KHR};
    void* pNext = nullptr;
    SurfaceFormatKHR surfaceFormat{};
};
struct DisplayProperties2KHR {
    StructureType sType{StructureType::DisplayProperties2KHR};
    void* pNext = nullptr;
    DisplayPropertiesKHR displayProperties{};
};
struct DisplayPlaneProperties2KHR {
    StructureType sType{StructureType::DisplayPlaneProperties2KHR};
    void* pNext = nullptr;
    DisplayPlanePropertiesKHR displayPlaneProperties{};
};
struct DisplayModeProperties2KHR {
    StructureType sType{StructureType::DisplayModeProperties2KHR};
    void* pNext = nullptr;
    DisplayModePropertiesKHR displayModeProperties{};
};
struct DisplayPlaneInfo2KHR {
    StructureType sType{StructureType::DisplayPlaneInfo2KHR};
    const void* pNext = nullptr;
    DisplayModeKHR mode{};
    uint32_t planeIndex{0};
};
struct DisplayPlaneCapabilities2KHR {
    StructureType sType{StructureType::DisplayPlaneCapabilities2KHR};
    void* pNext = nullptr;
    DisplayPlaneCapabilitiesKHR capabilities{};
};
struct SharedPresentSurfaceCapabilitiesKHR {
    StructureType sType{StructureType::SharedPresentSurfaceCapabilitiesKHR};
    void* pNext = nullptr;
    ImageUsageFlags sharedPresentSupportedUsageFlags{};
};
struct PhysicalDevice16BitStorageFeatures {
    StructureType sType{StructureType::PhysicalDevice16BitStorageFeatures};
    void* pNext = nullptr;
    Bool32 storageBuffer16BitAccess{0};
    Bool32 uniformAndStorageBuffer16BitAccess{0};
    Bool32 storagePushConstant16{0};
    Bool32 storageInputOutput16{0};
};
using PhysicalDevice16BitStorageFeaturesKHR = PhysicalDevice16BitStorageFeatures;
struct PhysicalDeviceSubgroupProperties {
    StructureType sType{StructureType::PhysicalDeviceSubgroupProperties};
    void* pNext = nullptr;
    uint32_t subgroupSize{0};
    ShaderStageFlags supportedStages{};
    SubgroupFeatureFlags supportedOperations{};
    Bool32 quadOperationsInAllStages{0};
};
struct PhysicalDeviceShaderSubgroupExtendedTypesFeatures {
    StructureType sType{StructureType::PhysicalDeviceShaderSubgroupExtendedTypesFeatures};
    void* pNext = nullptr;
    Bool32 shaderSubgroupExtendedTypes{0};
};
using PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR = PhysicalDeviceShaderSubgroupExtendedTypesFeatures;
struct BufferMemoryRequirementsInfo2 {
    StructureType sType{StructureType::BufferMemoryRequirementsInfo2};
    const void* pNext = nullptr;
    Buffer buffer{};
};
using BufferMemoryRequirementsInfo2KHR = BufferMemoryRequirementsInfo2;
struct ImageMemoryRequirementsInfo2 {
    StructureType sType{StructureType::ImageMemoryRequirementsInfo2};
    const void* pNext = nullptr;
    Image image{};
};
using ImageMemoryRequirementsInfo2KHR = ImageMemoryRequirementsInfo2;
struct ImageSparseMemoryRequirementsInfo2 {
    StructureType sType{StructureType::ImageSparseMemoryRequirementsInfo2};
    const void* pNext = nullptr;
    Image image{};
};
using ImageSparseMemoryRequirementsInfo2KHR = ImageSparseMemoryRequirementsInfo2;
struct MemoryRequirements2 {
    StructureType sType{StructureType::MemoryRequirements2};
    void* pNext = nullptr;
    MemoryRequirements memoryRequirements{};
};
using MemoryRequirements2KHR = MemoryRequirements2;
struct SparseImageMemoryRequirements2 {
    StructureType sType{StructureType::SparseImageMemoryRequirements2};
    void* pNext = nullptr;
    SparseImageMemoryRequirements memoryRequirements{};
};
using SparseImageMemoryRequirements2KHR = SparseImageMemoryRequirements2;
struct PhysicalDevicePointClippingProperties {
    StructureType sType{StructureType::PhysicalDevicePointClippingProperties};
    void* pNext = nullptr;
    PointClippingBehavior pointClippingBehavior{static_cast<PointClippingBehavior>(0)};
};
using PhysicalDevicePointClippingPropertiesKHR = PhysicalDevicePointClippingProperties;
struct MemoryDedicatedRequirements {
    StructureType sType{StructureType::MemoryDedicatedRequirements};
    void* pNext = nullptr;
    Bool32 prefersDedicatedAllocation{0};
    Bool32 requiresDedicatedAllocation{0};
};
using MemoryDedicatedRequirementsKHR = MemoryDedicatedRequirements;
struct MemoryDedicatedAllocateInfo {
    StructureType sType{StructureType::MemoryDedicatedAllocateInfo};
    const void* pNext = nullptr;
    Image image{};
    Buffer buffer{};
};
using MemoryDedicatedAllocateInfoKHR = MemoryDedicatedAllocateInfo;
struct ImageViewUsageCreateInfo {
    StructureType sType{StructureType::ImageViewUsageCreateInfo};
    const void* pNext = nullptr;
    ImageUsageFlags usage{};
};
using ImageViewUsageCreateInfoKHR = ImageViewUsageCreateInfo;
struct PipelineTessellationDomainOriginStateCreateInfo {
    StructureType sType{StructureType::PipelineTessellationDomainOriginStateCreateInfo};
    const void* pNext = nullptr;
    TessellationDomainOrigin domainOrigin{static_cast<TessellationDomainOrigin>(0)};
};
using PipelineTessellationDomainOriginStateCreateInfoKHR = PipelineTessellationDomainOriginStateCreateInfo;
struct SamplerYcbcrConversionInfo {
    StructureType sType{StructureType::SamplerYcbcrConversionInfo};
    const void* pNext = nullptr;
    SamplerYcbcrConversion conversion{};
};
using SamplerYcbcrConversionInfoKHR = SamplerYcbcrConversionInfo;
struct SamplerYcbcrConversionCreateInfo {
    StructureType sType{StructureType::SamplerYcbcrConversionCreateInfo};
    const void* pNext = nullptr;
    Format format{static_cast<Format>(0)};
    SamplerYcbcrModelConversion ycbcrModel{static_cast<SamplerYcbcrModelConversion>(0)};
    SamplerYcbcrRange ycbcrRange{static_cast<SamplerYcbcrRange>(0)};
    ComponentMapping components{};
    ChromaLocation xChromaOffset{static_cast<ChromaLocation>(0)};
    ChromaLocation yChromaOffset{static_cast<ChromaLocation>(0)};
    Filter chromaFilter{static_cast<Filter>(0)};
    Bool32 forceExplicitReconstruction{0};
};
using SamplerYcbcrConversionCreateInfoKHR = SamplerYcbcrConversionCreateInfo;
struct BindImagePlaneMemoryInfo {
    StructureType sType{StructureType::BindImagePlaneMemoryInfo};
    const void* pNext = nullptr;
    ImageAspectFlagBits planeAspect{static_cast<ImageAspectFlagBits>(0)};
};
using BindImagePlaneMemoryInfoKHR = BindImagePlaneMemoryInfo;
struct ImagePlaneMemoryRequirementsInfo {
    StructureType sType{StructureType::ImagePlaneMemoryRequirementsInfo};
    const void* pNext = nullptr;
    ImageAspectFlagBits planeAspect{static_cast<ImageAspectFlagBits>(0)};
};
using ImagePlaneMemoryRequirementsInfoKHR = ImagePlaneMemoryRequirementsInfo;
struct PhysicalDeviceSamplerYcbcrConversionFeatures {
    StructureType sType{StructureType::PhysicalDeviceSamplerYcbcrConversionFeatures};
    void* pNext = nullptr;
    Bool32 samplerYcbcrConversion{0};
};
using PhysicalDeviceSamplerYcbcrConversionFeaturesKHR = PhysicalDeviceSamplerYcbcrConversionFeatures;
struct SamplerYcbcrConversionImageFormatProperties {
    StructureType sType{StructureType::SamplerYcbcrConversionImageFormatProperties};
    void* pNext = nullptr;
    uint32_t combinedImageSamplerDescriptorCount{0};
};
using SamplerYcbcrConversionImageFormatPropertiesKHR = SamplerYcbcrConversionImageFormatProperties;
struct TextureLODGatherFormatPropertiesAMD {
    StructureType sType{StructureType::TextureLodGatherFormatPropertiesAMD};
    void* pNext = nullptr;
    Bool32 supportsTextureGatherLODBiasAMD{0};
};
struct ConditionalRenderingBeginInfoEXT {
    StructureType sType{StructureType::ConditionalRenderingBeginInfoEXT};
    const void* pNext = nullptr;
    Buffer buffer{};
    DeviceSize offset{0};
    ConditionalRenderingFlagsEXT flags{};
};
struct ProtectedSubmitInfo {
    StructureType sType{StructureType::ProtectedSubmitInfo};
    const void* pNext = nullptr;
    Bool32 protectedSubmit{0};
};
struct PhysicalDeviceProtectedMemoryFeatures {
    StructureType sType{StructureType::PhysicalDeviceProtectedMemoryFeatures};
    void* pNext = nullptr;
    Bool32 protectedMemory{0};
};
struct PhysicalDeviceProtectedMemoryProperties {
    StructureType sType{StructureType::PhysicalDeviceProtectedMemoryProperties};
    void* pNext = nullptr;
    Bool32 protectedNoFault{0};
};
struct DeviceQueueInfo2 {
    StructureType sType{StructureType::DeviceQueueInfo2};
    const void* pNext = nullptr;
    DeviceQueueCreateFlags flags{};
    uint32_t queueFamilyIndex{0};
    uint32_t queueIndex{0};
};
struct PipelineCoverageToColorStateCreateInfoNV {
    StructureType sType{StructureType::PipelineCoverageToColorStateCreateInfoNV};
    const void* pNext = nullptr;
    PipelineCoverageToColorStateCreateFlagsNV flags{};
    Bool32 coverageToColorEnable{0};
    uint32_t coverageToColorLocation{0};
};
struct PhysicalDeviceSamplerFilterMinmaxProperties {
    StructureType sType{StructureType::PhysicalDeviceSamplerFilterMinmaxProperties};
    void* pNext = nullptr;
    Bool32 filterMinmaxSingleComponentFormats{0};
    Bool32 filterMinmaxImageComponentMapping{0};
};
using PhysicalDeviceSamplerFilterMinmaxPropertiesEXT = PhysicalDeviceSamplerFilterMinmaxProperties;
struct SampleLocationEXT {
    float x{0.f};
    float y{0.f};
    constexpr bool operator==(SampleLocationEXT const& value) const {
        return x == value.x && y == value.y ;}
    constexpr bool operator!=(SampleLocationEXT const& value) const {return !(*this == value);}
};
struct SampleLocationsInfoEXT {
    StructureType sType{StructureType::SampleLocationsInfoEXT};
    const void* pNext = nullptr;
    SampleCountFlagBits sampleLocationsPerPixel{static_cast<SampleCountFlagBits>(0)};
    Extent2D sampleLocationGridSize{};
    uint32_t sampleLocationsCount{0};
    const SampleLocationEXT* pSampleLocations = nullptr;
};
struct AttachmentSampleLocationsEXT {
    uint32_t attachmentIndex{0};
    SampleLocationsInfoEXT sampleLocationsInfo{};
};
struct SubpassSampleLocationsEXT {
    uint32_t subpassIndex{0};
    SampleLocationsInfoEXT sampleLocationsInfo{};
};
struct RenderPassSampleLocationsBeginInfoEXT {
    StructureType sType{StructureType::RenderPassSampleLocationsBeginInfoEXT};
    const void* pNext = nullptr;
    uint32_t attachmentInitialSampleLocationsCount{0};
    const AttachmentSampleLocationsEXT* pAttachmentInitialSampleLocations = nullptr;
    uint32_t postSubpassSampleLocationsCount{0};
    const SubpassSampleLocationsEXT* pPostSubpassSampleLocations = nullptr;
};
struct PipelineSampleLocationsStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineSampleLocationsStateCreateInfoEXT};
    const void* pNext = nullptr;
    Bool32 sampleLocationsEnable{0};
    SampleLocationsInfoEXT sampleLocationsInfo{};
};
struct PhysicalDeviceSampleLocationsPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceSampleLocationsPropertiesEXT};
    void* pNext = nullptr;
    SampleCountFlags sampleLocationSampleCounts{};
    Extent2D maxSampleLocationGridSize{};
    float sampleLocationCoordinateRange[2];
    uint32_t sampleLocationSubPixelBits{0};
    Bool32 variableSampleLocations{0};
};
struct MultisamplePropertiesEXT {
    StructureType sType{StructureType::MultisamplePropertiesEXT};
    void* pNext = nullptr;
    Extent2D maxSampleLocationGridSize{};
};
struct SamplerReductionModeCreateInfo {
    StructureType sType{StructureType::SamplerReductionModeCreateInfo};
    const void* pNext = nullptr;
    SamplerReductionMode reductionMode{static_cast<SamplerReductionMode>(0)};
};
using SamplerReductionModeCreateInfoEXT = SamplerReductionModeCreateInfo;
struct PhysicalDeviceBlendOperationAdvancedFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceBlendOperationAdvancedFeaturesEXT};
    void* pNext = nullptr;
    Bool32 advancedBlendCoherentOperations{0};
};
struct PhysicalDeviceBlendOperationAdvancedPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceBlendOperationAdvancedPropertiesEXT};
    void* pNext = nullptr;
    uint32_t advancedBlendMaxColorAttachments{0};
    Bool32 advancedBlendIndependentBlend{0};
    Bool32 advancedBlendNonPremultipliedSrcColor{0};
    Bool32 advancedBlendNonPremultipliedDstColor{0};
    Bool32 advancedBlendCorrelatedOverlap{0};
    Bool32 advancedBlendAllOperations{0};
};
struct PipelineColorBlendAdvancedStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineColorBlendAdvancedStateCreateInfoEXT};
    const void* pNext = nullptr;
    Bool32 srcPremultiplied{0};
    Bool32 dstPremultiplied{0};
    BlendOverlapEXT blendOverlap{static_cast<BlendOverlapEXT>(0)};
};
struct PhysicalDeviceInlineUniformBlockFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceInlineUniformBlockFeaturesEXT};
    void* pNext = nullptr;
    Bool32 inlineUniformBlock{0};
    Bool32 descriptorBindingInlineUniformBlockUpdateAfterBind{0};
};
struct PhysicalDeviceInlineUniformBlockPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceInlineUniformBlockPropertiesEXT};
    void* pNext = nullptr;
    uint32_t maxInlineUniformBlockSize{0};
    uint32_t maxPerStageDescriptorInlineUniformBlocks{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks{0};
    uint32_t maxDescriptorSetInlineUniformBlocks{0};
    uint32_t maxDescriptorSetUpdateAfterBindInlineUniformBlocks{0};
};
struct WriteDescriptorSetInlineUniformBlockEXT {
    StructureType sType{StructureType::WriteDescriptorSetInlineUniformBlockEXT};
    const void* pNext = nullptr;
    uint32_t dataSize{0};
    const void* pData = nullptr;
};
struct DescriptorPoolInlineUniformBlockCreateInfoEXT {
    StructureType sType{StructureType::DescriptorPoolInlineUniformBlockCreateInfoEXT};
    const void* pNext = nullptr;
    uint32_t maxInlineUniformBlockBindings{0};
};
struct PipelineCoverageModulationStateCreateInfoNV {
    StructureType sType{StructureType::PipelineCoverageModulationStateCreateInfoNV};
    const void* pNext = nullptr;
    PipelineCoverageModulationStateCreateFlagsNV flags{};
    CoverageModulationModeNV coverageModulationMode{static_cast<CoverageModulationModeNV>(0)};
    Bool32 coverageModulationTableEnable{0};
    uint32_t coverageModulationTableCount{0};
    const float* pCoverageModulationTable = nullptr;
};
struct ImageFormatListCreateInfo {
    StructureType sType{StructureType::ImageFormatListCreateInfo};
    const void* pNext = nullptr;
    uint32_t viewFormatCount{0};
    const Format* pViewFormats = nullptr;
};
using ImageFormatListCreateInfoKHR = ImageFormatListCreateInfo;
struct ValidationCacheCreateInfoEXT {
    StructureType sType{StructureType::ValidationCacheCreateInfoEXT};
    const void* pNext = nullptr;
    ValidationCacheCreateFlagsEXT flags{};
    size_t initialDataSize{0};
    const void* pInitialData = nullptr;
};
struct ShaderModuleValidationCacheCreateInfoEXT {
    StructureType sType{StructureType::ShaderModuleValidationCacheCreateInfoEXT};
    const void* pNext = nullptr;
    ValidationCacheEXT validationCache{};
};
struct PhysicalDeviceMaintenance3Properties {
    StructureType sType{StructureType::PhysicalDeviceMaintenance3Properties};
    void* pNext = nullptr;
    uint32_t maxPerSetDescriptors{0};
    DeviceSize maxMemoryAllocationSize{0};
};
using PhysicalDeviceMaintenance3PropertiesKHR = PhysicalDeviceMaintenance3Properties;
struct DescriptorSetLayoutSupport {
    StructureType sType{StructureType::DescriptorSetLayoutSupport};
    void* pNext = nullptr;
    Bool32 supported{0};
};
using DescriptorSetLayoutSupportKHR = DescriptorSetLayoutSupport;
struct PhysicalDeviceShaderDrawParametersFeatures {
    StructureType sType{StructureType::PhysicalDeviceShaderDrawParametersFeatures};
    void* pNext = nullptr;
    Bool32 shaderDrawParameters{0};
};
using PhysicalDeviceShaderDrawParameterFeatures = PhysicalDeviceShaderDrawParametersFeatures;
struct PhysicalDeviceShaderFloat16Int8Features {
    StructureType sType{StructureType::PhysicalDeviceShaderFloat16Int8Features};
    void* pNext = nullptr;
    Bool32 shaderFloat16{0};
    Bool32 shaderInt8{0};
};
using PhysicalDeviceShaderFloat16Int8FeaturesKHR = PhysicalDeviceShaderFloat16Int8Features;
using PhysicalDeviceFloat16Int8FeaturesKHR = PhysicalDeviceShaderFloat16Int8Features;
struct PhysicalDeviceFloatControlsProperties {
    StructureType sType{StructureType::PhysicalDeviceFloatControlsProperties};
    void* pNext = nullptr;
    ShaderFloatControlsIndependence denormBehaviorIndependence{static_cast<ShaderFloatControlsIndependence>(0)};
    ShaderFloatControlsIndependence roundingModeIndependence{static_cast<ShaderFloatControlsIndependence>(0)};
    Bool32 shaderSignedZeroInfNanPreserveFloat16{0};
    Bool32 shaderSignedZeroInfNanPreserveFloat32{0};
    Bool32 shaderSignedZeroInfNanPreserveFloat64{0};
    Bool32 shaderDenormPreserveFloat16{0};
    Bool32 shaderDenormPreserveFloat32{0};
    Bool32 shaderDenormPreserveFloat64{0};
    Bool32 shaderDenormFlushToZeroFloat16{0};
    Bool32 shaderDenormFlushToZeroFloat32{0};
    Bool32 shaderDenormFlushToZeroFloat64{0};
    Bool32 shaderRoundingModeRTEFloat16{0};
    Bool32 shaderRoundingModeRTEFloat32{0};
    Bool32 shaderRoundingModeRTEFloat64{0};
    Bool32 shaderRoundingModeRTZFloat16{0};
    Bool32 shaderRoundingModeRTZFloat32{0};
    Bool32 shaderRoundingModeRTZFloat64{0};
};
using PhysicalDeviceFloatControlsPropertiesKHR = PhysicalDeviceFloatControlsProperties;
struct PhysicalDeviceHostQueryResetFeatures {
    StructureType sType{StructureType::PhysicalDeviceHostQueryResetFeatures};
    void* pNext = nullptr;
    Bool32 hostQueryReset{0};
};
using PhysicalDeviceHostQueryResetFeaturesEXT = PhysicalDeviceHostQueryResetFeatures;
struct ShaderResourceUsageAMD {
    uint32_t numUsedVgprs{0};
    uint32_t numUsedSgprs{0};
    uint32_t ldsSizePerLocalWorkGroup{0};
    size_t ldsUsageSizeInBytes{0};
    size_t scratchMemUsageInBytes{0};
    constexpr bool operator==(ShaderResourceUsageAMD const& value) const {
        return numUsedVgprs == value.numUsedVgprs && numUsedSgprs == value.numUsedSgprs && ldsSizePerLocalWorkGroup == value.ldsSizePerLocalWorkGroup 
        && ldsUsageSizeInBytes == value.ldsUsageSizeInBytes && scratchMemUsageInBytes == value.scratchMemUsageInBytes ;}
    constexpr bool operator!=(ShaderResourceUsageAMD const& value) const {return !(*this == value);}
};
struct ShaderStatisticsInfoAMD {
    ShaderStageFlags shaderStageMask{};
    ShaderResourceUsageAMD resourceUsage{};
    uint32_t numPhysicalVgprs{0};
    uint32_t numPhysicalSgprs{0};
    uint32_t numAvailableVgprs{0};
    uint32_t numAvailableSgprs{0};
    uint32_t computeWorkGroupSize[3];
    constexpr bool operator==(ShaderStatisticsInfoAMD const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 3; i++)
            is_equal &= computeWorkGroupSize[i] == value.computeWorkGroupSize[i];
        return is_equal && shaderStageMask == value.shaderStageMask && resourceUsage == value.resourceUsage && numPhysicalVgprs == value.numPhysicalVgprs && numPhysicalSgprs == value.numPhysicalSgprs 
        && numAvailableVgprs == value.numAvailableVgprs && numAvailableSgprs == value.numAvailableSgprs ;}
    constexpr bool operator!=(ShaderStatisticsInfoAMD const& value) const {return !(*this == value);}
};
struct DeviceQueueGlobalPriorityCreateInfoEXT {
    StructureType sType{StructureType::DeviceQueueGlobalPriorityCreateInfoEXT};
    const void* pNext = nullptr;
    QueueGlobalPriorityEXT globalPriority{static_cast<QueueGlobalPriorityEXT>(0)};
};
struct DebugUtilsObjectNameInfoEXT {
    StructureType sType{StructureType::DebugUtilsObjectNameInfoEXT};
    const void* pNext = nullptr;
    ObjectType objectType{static_cast<ObjectType>(0)};
    uint64_t objectHandle{0};
    const char* pObjectName = nullptr;
};
struct DebugUtilsObjectTagInfoEXT {
    StructureType sType{StructureType::DebugUtilsObjectTagInfoEXT};
    const void* pNext = nullptr;
    ObjectType objectType{static_cast<ObjectType>(0)};
    uint64_t objectHandle{0};
    uint64_t tagName{0};
    size_t tagSize{0};
    const void* pTag = nullptr;
};
struct DebugUtilsLabelEXT {
    StructureType sType{StructureType::DebugUtilsLabelEXT};
    const void* pNext = nullptr;
    const char* pLabelName = nullptr;
    float color[4];
};
struct DebugUtilsMessengerCreateInfoEXT {
    StructureType sType{StructureType::DebugUtilsMessengerCreateInfoEXT};
    const void* pNext = nullptr;
    DebugUtilsMessengerCreateFlagsEXT flags{};
    DebugUtilsMessageSeverityFlagsEXT messageSeverity{};
    DebugUtilsMessageTypeFlagsEXT messageType{};
    PFN_DebugUtilsMessengerCallbackEXT pfnUserCallback{};
    void* pUserData = nullptr;
};
struct DebugUtilsMessengerCallbackDataEXT {
    StructureType sType{StructureType::DebugUtilsMessengerCallbackDataEXT};
    const void* pNext = nullptr;
    DebugUtilsMessengerCallbackDataFlagsEXT flags{};
    const char* pMessageIdName = nullptr;
    int32_t messageIdNumber{0};
    const char* pMessage = nullptr;
    uint32_t queueLabelCount{0};
    const DebugUtilsLabelEXT* pQueueLabels = nullptr;
    uint32_t cmdBufLabelCount{0};
    const DebugUtilsLabelEXT* pCmdBufLabels = nullptr;
    uint32_t objectCount{0};
    const DebugUtilsObjectNameInfoEXT* pObjects = nullptr;
};
struct PhysicalDeviceDeviceMemoryReportFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceDeviceMemoryReportFeaturesEXT};
    void* pNext = nullptr;
    Bool32 deviceMemoryReport{0};
};
struct DeviceDeviceMemoryReportCreateInfoEXT {
    StructureType sType{StructureType::DeviceDeviceMemoryReportCreateInfoEXT};
    const void* pNext = nullptr;
    DeviceMemoryReportFlagsEXT flags{};
    PFN_DeviceMemoryReportCallbackEXT pfnUserCallback{};
    void* pUserData = nullptr;
};
struct DeviceMemoryReportCallbackDataEXT {
    StructureType sType{StructureType::DeviceMemoryReportCallbackDataEXT};
    const void* pNext = nullptr;
    DeviceMemoryReportFlagsEXT flags{};
    DeviceMemoryReportEventTypeEXT type{static_cast<DeviceMemoryReportEventTypeEXT>(0)};
    uint64_t memoryObjectId{0};
    DeviceSize size{0};
    ObjectType objectType{static_cast<ObjectType>(0)};
    uint64_t objectHandle{0};
    uint32_t heapIndex{0};
};
struct ImportMemoryHostPointerInfoEXT {
    StructureType sType{StructureType::ImportMemoryHostPointerInfoEXT};
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType{static_cast<ExternalMemoryHandleTypeFlagBits>(0)};
    void* pHostPointer = nullptr;
};
struct MemoryHostPointerPropertiesEXT {
    StructureType sType{StructureType::MemoryHostPointerPropertiesEXT};
    void* pNext = nullptr;
    uint32_t memoryTypeBits{0};
};
struct PhysicalDeviceExternalMemoryHostPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceExternalMemoryHostPropertiesEXT};
    void* pNext = nullptr;
    DeviceSize minImportedHostPointerAlignment{0};
};
struct PhysicalDeviceConservativeRasterizationPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceConservativeRasterizationPropertiesEXT};
    void* pNext = nullptr;
    float primitiveOverestimationSize{0.f};
    float maxExtraPrimitiveOverestimationSize{0.f};
    float extraPrimitiveOverestimationSizeGranularity{0.f};
    Bool32 primitiveUnderestimation{0};
    Bool32 conservativePointAndLineRasterization{0};
    Bool32 degenerateTrianglesRasterized{0};
    Bool32 degenerateLinesRasterized{0};
    Bool32 fullyCoveredFragmentShaderInputVariable{0};
    Bool32 conservativeRasterizationPostDepthCoverage{0};
};
struct CalibratedTimestampInfoEXT {
    StructureType sType{StructureType::CalibratedTimestampInfoEXT};
    const void* pNext = nullptr;
    TimeDomainEXT timeDomain{static_cast<TimeDomainEXT>(0)};
};
struct PhysicalDeviceShaderCorePropertiesAMD {
    StructureType sType{StructureType::PhysicalDeviceShaderCorePropertiesAMD};
    void* pNext = nullptr;
    uint32_t shaderEngineCount{0};
    uint32_t shaderArraysPerEngineCount{0};
    uint32_t computeUnitsPerShaderArray{0};
    uint32_t simdPerComputeUnit{0};
    uint32_t wavefrontsPerSimd{0};
    uint32_t wavefrontSize{0};
    uint32_t sgprsPerSimd{0};
    uint32_t minSgprAllocation{0};
    uint32_t maxSgprAllocation{0};
    uint32_t sgprAllocationGranularity{0};
    uint32_t vgprsPerSimd{0};
    uint32_t minVgprAllocation{0};
    uint32_t maxVgprAllocation{0};
    uint32_t vgprAllocationGranularity{0};
};
struct PhysicalDeviceShaderCoreProperties2AMD {
    StructureType sType{StructureType::PhysicalDeviceShaderCoreProperties2AMD};
    void* pNext = nullptr;
    ShaderCorePropertiesFlagsAMD shaderCoreFeatures{};
    uint32_t activeComputeUnitCount{0};
};
struct PipelineRasterizationConservativeStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineRasterizationConservativeStateCreateInfoEXT};
    const void* pNext = nullptr;
    PipelineRasterizationConservativeStateCreateFlagsEXT flags{};
    ConservativeRasterizationModeEXT conservativeRasterizationMode{static_cast<ConservativeRasterizationModeEXT>(0)};
    float extraPrimitiveOverestimationSize{0.f};
};
struct PhysicalDeviceDescriptorIndexingFeatures {
    StructureType sType{StructureType::PhysicalDeviceDescriptorIndexingFeatures};
    void* pNext = nullptr;
    Bool32 shaderInputAttachmentArrayDynamicIndexing{0};
    Bool32 shaderUniformTexelBufferArrayDynamicIndexing{0};
    Bool32 shaderStorageTexelBufferArrayDynamicIndexing{0};
    Bool32 shaderUniformBufferArrayNonUniformIndexing{0};
    Bool32 shaderSampledImageArrayNonUniformIndexing{0};
    Bool32 shaderStorageBufferArrayNonUniformIndexing{0};
    Bool32 shaderStorageImageArrayNonUniformIndexing{0};
    Bool32 shaderInputAttachmentArrayNonUniformIndexing{0};
    Bool32 shaderUniformTexelBufferArrayNonUniformIndexing{0};
    Bool32 shaderStorageTexelBufferArrayNonUniformIndexing{0};
    Bool32 descriptorBindingUniformBufferUpdateAfterBind{0};
    Bool32 descriptorBindingSampledImageUpdateAfterBind{0};
    Bool32 descriptorBindingStorageImageUpdateAfterBind{0};
    Bool32 descriptorBindingStorageBufferUpdateAfterBind{0};
    Bool32 descriptorBindingUniformTexelBufferUpdateAfterBind{0};
    Bool32 descriptorBindingStorageTexelBufferUpdateAfterBind{0};
    Bool32 descriptorBindingUpdateUnusedWhilePending{0};
    Bool32 descriptorBindingPartiallyBound{0};
    Bool32 descriptorBindingVariableDescriptorCount{0};
    Bool32 runtimeDescriptorArray{0};
};
using PhysicalDeviceDescriptorIndexingFeaturesEXT = PhysicalDeviceDescriptorIndexingFeatures;
struct PhysicalDeviceDescriptorIndexingProperties {
    StructureType sType{StructureType::PhysicalDeviceDescriptorIndexingProperties};
    void* pNext = nullptr;
    uint32_t maxUpdateAfterBindDescriptorsInAllPools{0};
    Bool32 shaderUniformBufferArrayNonUniformIndexingNative{0};
    Bool32 shaderSampledImageArrayNonUniformIndexingNative{0};
    Bool32 shaderStorageBufferArrayNonUniformIndexingNative{0};
    Bool32 shaderStorageImageArrayNonUniformIndexingNative{0};
    Bool32 shaderInputAttachmentArrayNonUniformIndexingNative{0};
    Bool32 robustBufferAccessUpdateAfterBind{0};
    Bool32 quadDivergentImplicitLod{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindSamplers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindUniformBuffers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageBuffers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindSampledImages{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageImages{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindInputAttachments{0};
    uint32_t maxPerStageUpdateAfterBindResources{0};
    uint32_t maxDescriptorSetUpdateAfterBindSamplers{0};
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffers{0};
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffersDynamic{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffers{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffersDynamic{0};
    uint32_t maxDescriptorSetUpdateAfterBindSampledImages{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageImages{0};
    uint32_t maxDescriptorSetUpdateAfterBindInputAttachments{0};
};
using PhysicalDeviceDescriptorIndexingPropertiesEXT = PhysicalDeviceDescriptorIndexingProperties;
struct DescriptorSetLayoutBindingFlagsCreateInfo {
    StructureType sType{StructureType::DescriptorSetLayoutBindingFlagsCreateInfo};
    const void* pNext = nullptr;
    uint32_t bindingCount{0};
    const DescriptorBindingFlags* pBindingFlags = nullptr;
};
using DescriptorSetLayoutBindingFlagsCreateInfoEXT = DescriptorSetLayoutBindingFlagsCreateInfo;
struct DescriptorSetVariableDescriptorCountAllocateInfo {
    StructureType sType{StructureType::DescriptorSetVariableDescriptorCountAllocateInfo};
    const void* pNext = nullptr;
    uint32_t descriptorSetCount{0};
    const uint32_t* pDescriptorCounts = nullptr;
};
using DescriptorSetVariableDescriptorCountAllocateInfoEXT = DescriptorSetVariableDescriptorCountAllocateInfo;
struct DescriptorSetVariableDescriptorCountLayoutSupport {
    StructureType sType{StructureType::DescriptorSetVariableDescriptorCountLayoutSupport};
    void* pNext = nullptr;
    uint32_t maxVariableDescriptorCount{0};
};
using DescriptorSetVariableDescriptorCountLayoutSupportEXT = DescriptorSetVariableDescriptorCountLayoutSupport;
struct AttachmentDescription2 {
    StructureType sType{StructureType::AttachmentDescription2};
    const void* pNext = nullptr;
    AttachmentDescriptionFlags flags{};
    Format format{static_cast<Format>(0)};
    SampleCountFlagBits samples{static_cast<SampleCountFlagBits>(0)};
    AttachmentLoadOp loadOp{static_cast<AttachmentLoadOp>(0)};
    AttachmentStoreOp storeOp{static_cast<AttachmentStoreOp>(0)};
    AttachmentLoadOp stencilLoadOp{static_cast<AttachmentLoadOp>(0)};
    AttachmentStoreOp stencilStoreOp{static_cast<AttachmentStoreOp>(0)};
    ImageLayout initialLayout{static_cast<ImageLayout>(0)};
    ImageLayout finalLayout{static_cast<ImageLayout>(0)};
};
using AttachmentDescription2KHR = AttachmentDescription2;
struct AttachmentReference2 {
    StructureType sType{StructureType::AttachmentReference2};
    const void* pNext = nullptr;
    uint32_t attachment{0};
    ImageLayout layout{static_cast<ImageLayout>(0)};
    ImageAspectFlags aspectMask{};
};
using AttachmentReference2KHR = AttachmentReference2;
struct SubpassDescription2 {
    StructureType sType{StructureType::SubpassDescription2};
    const void* pNext = nullptr;
    SubpassDescriptionFlags flags{};
    PipelineBindPoint pipelineBindPoint{static_cast<PipelineBindPoint>(0)};
    uint32_t viewMask{0};
    uint32_t inputAttachmentCount{0};
    const AttachmentReference2* pInputAttachments = nullptr;
    uint32_t colorAttachmentCount{0};
    const AttachmentReference2* pColorAttachments = nullptr;
    const AttachmentReference2* pResolveAttachments = nullptr;
    const AttachmentReference2* pDepthStencilAttachment = nullptr;
    uint32_t preserveAttachmentCount{0};
    const uint32_t* pPreserveAttachments = nullptr;
};
using SubpassDescription2KHR = SubpassDescription2;
struct SubpassDependency2 {
    StructureType sType{StructureType::SubpassDependency2};
    const void* pNext = nullptr;
    uint32_t srcSubpass{0};
    uint32_t dstSubpass{0};
    PipelineStageFlags srcStageMask{};
    PipelineStageFlags dstStageMask{};
    AccessFlags srcAccessMask{};
    AccessFlags dstAccessMask{};
    DependencyFlags dependencyFlags{};
    int32_t viewOffset{0};
};
using SubpassDependency2KHR = SubpassDependency2;
struct RenderPassCreateInfo2 {
    StructureType sType{StructureType::RenderPassCreateInfo2};
    const void* pNext = nullptr;
    RenderPassCreateFlags flags{};
    uint32_t attachmentCount{0};
    const AttachmentDescription2* pAttachments = nullptr;
    uint32_t subpassCount{0};
    const SubpassDescription2* pSubpasses = nullptr;
    uint32_t dependencyCount{0};
    const SubpassDependency2* pDependencies = nullptr;
    uint32_t correlatedViewMaskCount{0};
    const uint32_t* pCorrelatedViewMasks = nullptr;
};
using RenderPassCreateInfo2KHR = RenderPassCreateInfo2;
struct SubpassBeginInfo {
    StructureType sType{StructureType::SubpassBeginInfo};
    const void* pNext = nullptr;
    SubpassContents contents{static_cast<SubpassContents>(0)};
};
using SubpassBeginInfoKHR = SubpassBeginInfo;
struct SubpassEndInfo {
    StructureType sType{StructureType::SubpassEndInfo};
    const void* pNext = nullptr;
};
using SubpassEndInfoKHR = SubpassEndInfo;
struct PhysicalDeviceTimelineSemaphoreFeatures {
    StructureType sType{StructureType::PhysicalDeviceTimelineSemaphoreFeatures};
    void* pNext = nullptr;
    Bool32 timelineSemaphore{0};
};
using PhysicalDeviceTimelineSemaphoreFeaturesKHR = PhysicalDeviceTimelineSemaphoreFeatures;
struct PhysicalDeviceTimelineSemaphoreProperties {
    StructureType sType{StructureType::PhysicalDeviceTimelineSemaphoreProperties};
    void* pNext = nullptr;
    uint64_t maxTimelineSemaphoreValueDifference{0};
};
using PhysicalDeviceTimelineSemaphorePropertiesKHR = PhysicalDeviceTimelineSemaphoreProperties;
struct SemaphoreTypeCreateInfo {
    StructureType sType{StructureType::SemaphoreTypeCreateInfo};
    const void* pNext = nullptr;
    SemaphoreType semaphoreType{static_cast<SemaphoreType>(0)};
    uint64_t initialValue{0};
};
using SemaphoreTypeCreateInfoKHR = SemaphoreTypeCreateInfo;
struct TimelineSemaphoreSubmitInfo {
    StructureType sType{StructureType::TimelineSemaphoreSubmitInfo};
    const void* pNext = nullptr;
    uint32_t waitSemaphoreValueCount{0};
    const uint64_t* pWaitSemaphoreValues = nullptr;
    uint32_t signalSemaphoreValueCount{0};
    const uint64_t* pSignalSemaphoreValues = nullptr;
};
using TimelineSemaphoreSubmitInfoKHR = TimelineSemaphoreSubmitInfo;
struct SemaphoreWaitInfo {
    StructureType sType{StructureType::SemaphoreWaitInfo};
    const void* pNext = nullptr;
    SemaphoreWaitFlags flags{};
    uint32_t semaphoreCount{0};
    const Semaphore* pSemaphores = nullptr;
    const uint64_t* pValues = nullptr;
};
using SemaphoreWaitInfoKHR = SemaphoreWaitInfo;
struct SemaphoreSignalInfo {
    StructureType sType{StructureType::SemaphoreSignalInfo};
    const void* pNext = nullptr;
    Semaphore semaphore{};
    uint64_t value{0};
};
using SemaphoreSignalInfoKHR = SemaphoreSignalInfo;
struct VertexInputBindingDivisorDescriptionEXT {
    uint32_t binding{0};
    uint32_t divisor{0};
    constexpr bool operator==(VertexInputBindingDivisorDescriptionEXT const& value) const {
        return binding == value.binding && divisor == value.divisor ;}
    constexpr bool operator!=(VertexInputBindingDivisorDescriptionEXT const& value) const {return !(*this == value);}
};
struct PipelineVertexInputDivisorStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineVertexInputDivisorStateCreateInfoEXT};
    const void* pNext = nullptr;
    uint32_t vertexBindingDivisorCount{0};
    const VertexInputBindingDivisorDescriptionEXT* pVertexBindingDivisors = nullptr;
};
struct PhysicalDeviceVertexAttributeDivisorPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceVertexAttributeDivisorPropertiesEXT};
    void* pNext = nullptr;
    uint32_t maxVertexAttribDivisor{0};
};
struct PhysicalDevicePCIBusInfoPropertiesEXT {
    StructureType sType{StructureType::PhysicalDevicePciBusInfoPropertiesEXT};
    void* pNext = nullptr;
    uint32_t pciDomain{0};
    uint32_t pciBus{0};
    uint32_t pciDevice{0};
    uint32_t pciFunction{0};
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct ImportAndroidHardwareBufferInfoANDROID {
    StructureType sType{StructureType::ImportAndroidHardwareBufferInfoANDROID};
    const void* pNext = nullptr;
    AHardwareBuffer* buffer = nullptr;
};
struct AndroidHardwareBufferUsageANDROID {
    StructureType sType{StructureType::AndroidHardwareBufferUsageANDROID};
    void* pNext = nullptr;
    uint64_t androidHardwareBufferUsage{0};
};
struct AndroidHardwareBufferPropertiesANDROID {
    StructureType sType{StructureType::AndroidHardwareBufferPropertiesANDROID};
    void* pNext = nullptr;
    DeviceSize allocationSize{0};
    uint32_t memoryTypeBits{0};
};
struct MemoryGetAndroidHardwareBufferInfoANDROID {
    StructureType sType{StructureType::MemoryGetAndroidHardwareBufferInfoANDROID};
    const void* pNext = nullptr;
    DeviceMemory memory{};
};
struct AndroidHardwareBufferFormatPropertiesANDROID {
    StructureType sType{StructureType::AndroidHardwareBufferFormatPropertiesANDROID};
    void* pNext = nullptr;
    Format format{static_cast<Format>(0)};
    uint64_t externalFormat{0};
    FormatFeatureFlags formatFeatures{};
    ComponentMapping samplerYcbcrConversionComponents{};
    SamplerYcbcrModelConversion suggestedYcbcrModel{static_cast<SamplerYcbcrModelConversion>(0)};
    SamplerYcbcrRange suggestedYcbcrRange{static_cast<SamplerYcbcrRange>(0)};
    ChromaLocation suggestedXChromaOffset{static_cast<ChromaLocation>(0)};
    ChromaLocation suggestedYChromaOffset{static_cast<ChromaLocation>(0)};
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct CommandBufferInheritanceConditionalRenderingInfoEXT {
    StructureType sType{StructureType::CommandBufferInheritanceConditionalRenderingInfoEXT};
    const void* pNext = nullptr;
    Bool32 conditionalRenderingEnable{0};
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct ExternalFormatANDROID {
    StructureType sType{StructureType::ExternalFormatANDROID};
    void* pNext = nullptr;
    uint64_t externalFormat{0};
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct PhysicalDevice8BitStorageFeatures {
    StructureType sType{StructureType::PhysicalDevice8BitStorageFeatures};
    void* pNext = nullptr;
    Bool32 storageBuffer8BitAccess{0};
    Bool32 uniformAndStorageBuffer8BitAccess{0};
    Bool32 storagePushConstant8{0};
};
using PhysicalDevice8BitStorageFeaturesKHR = PhysicalDevice8BitStorageFeatures;
struct PhysicalDeviceConditionalRenderingFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceConditionalRenderingFeaturesEXT};
    void* pNext = nullptr;
    Bool32 conditionalRendering{0};
    Bool32 inheritedConditionalRendering{0};
};
struct PhysicalDeviceVulkanMemoryModelFeatures {
    StructureType sType{StructureType::PhysicalDeviceVulkanMemoryModelFeatures};
    void* pNext = nullptr;
    Bool32 vulkanMemoryModel{0};
    Bool32 vulkanMemoryModelDeviceScope{0};
    Bool32 vulkanMemoryModelAvailabilityVisibilityChains{0};
};
using PhysicalDeviceVulkanMemoryModelFeaturesKHR = PhysicalDeviceVulkanMemoryModelFeatures;
struct PhysicalDeviceShaderAtomicInt64Features {
    StructureType sType{StructureType::PhysicalDeviceShaderAtomicInt64Features};
    void* pNext = nullptr;
    Bool32 shaderBufferInt64Atomics{0};
    Bool32 shaderSharedInt64Atomics{0};
};
using PhysicalDeviceShaderAtomicInt64FeaturesKHR = PhysicalDeviceShaderAtomicInt64Features;
struct PhysicalDeviceShaderAtomicFloatFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceShaderAtomicFloatFeaturesEXT};
    void* pNext = nullptr;
    Bool32 shaderBufferFloat32Atomics{0};
    Bool32 shaderBufferFloat32AtomicAdd{0};
    Bool32 shaderBufferFloat64Atomics{0};
    Bool32 shaderBufferFloat64AtomicAdd{0};
    Bool32 shaderSharedFloat32Atomics{0};
    Bool32 shaderSharedFloat32AtomicAdd{0};
    Bool32 shaderSharedFloat64Atomics{0};
    Bool32 shaderSharedFloat64AtomicAdd{0};
    Bool32 shaderImageFloat32Atomics{0};
    Bool32 shaderImageFloat32AtomicAdd{0};
    Bool32 sparseImageFloat32Atomics{0};
    Bool32 sparseImageFloat32AtomicAdd{0};
};
struct PhysicalDeviceVertexAttributeDivisorFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceVertexAttributeDivisorFeaturesEXT};
    void* pNext = nullptr;
    Bool32 vertexAttributeInstanceRateDivisor{0};
    Bool32 vertexAttributeInstanceRateZeroDivisor{0};
};
struct QueueFamilyCheckpointPropertiesNV {
    StructureType sType{StructureType::QueueFamilyCheckpointPropertiesNV};
    void* pNext = nullptr;
    PipelineStageFlags checkpointExecutionStageMask{};
};
struct CheckpointDataNV {
    StructureType sType{StructureType::CheckpointDataNV};
    void* pNext = nullptr;
    PipelineStageFlagBits stage{static_cast<PipelineStageFlagBits>(0)};
    void* pCheckpointMarker = nullptr;
};
struct PhysicalDeviceDepthStencilResolveProperties {
    StructureType sType{StructureType::PhysicalDeviceDepthStencilResolveProperties};
    void* pNext = nullptr;
    ResolveModeFlags supportedDepthResolveModes{};
    ResolveModeFlags supportedStencilResolveModes{};
    Bool32 independentResolveNone{0};
    Bool32 independentResolve{0};
};
using PhysicalDeviceDepthStencilResolvePropertiesKHR = PhysicalDeviceDepthStencilResolveProperties;
struct SubpassDescriptionDepthStencilResolve {
    StructureType sType{StructureType::SubpassDescriptionDepthStencilResolve};
    const void* pNext = nullptr;
    ResolveModeFlagBits depthResolveMode{static_cast<ResolveModeFlagBits>(0)};
    ResolveModeFlagBits stencilResolveMode{static_cast<ResolveModeFlagBits>(0)};
    const AttachmentReference2* pDepthStencilResolveAttachment = nullptr;
};
using SubpassDescriptionDepthStencilResolveKHR = SubpassDescriptionDepthStencilResolve;
struct ImageViewASTCDecodeModeEXT {
    StructureType sType{StructureType::ImageViewAstcDecodeModeEXT};
    const void* pNext = nullptr;
    Format decodeMode{static_cast<Format>(0)};
};
struct PhysicalDeviceASTCDecodeFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceAstcDecodeFeaturesEXT};
    void* pNext = nullptr;
    Bool32 decodeModeSharedExponent{0};
};
struct PhysicalDeviceTransformFeedbackFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceTransformFeedbackFeaturesEXT};
    void* pNext = nullptr;
    Bool32 transformFeedback{0};
    Bool32 geometryStreams{0};
};
struct PhysicalDeviceTransformFeedbackPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceTransformFeedbackPropertiesEXT};
    void* pNext = nullptr;
    uint32_t maxTransformFeedbackStreams{0};
    uint32_t maxTransformFeedbackBuffers{0};
    DeviceSize maxTransformFeedbackBufferSize{0};
    uint32_t maxTransformFeedbackStreamDataSize{0};
    uint32_t maxTransformFeedbackBufferDataSize{0};
    uint32_t maxTransformFeedbackBufferDataStride{0};
    Bool32 transformFeedbackQueries{0};
    Bool32 transformFeedbackStreamsLinesTriangles{0};
    Bool32 transformFeedbackRasterizationStreamSelect{0};
    Bool32 transformFeedbackDraw{0};
};
struct PipelineRasterizationStateStreamCreateInfoEXT {
    StructureType sType{StructureType::PipelineRasterizationStateStreamCreateInfoEXT};
    const void* pNext = nullptr;
    PipelineRasterizationStateStreamCreateFlagsEXT flags{};
    uint32_t rasterizationStream{0};
};
struct PhysicalDeviceRepresentativeFragmentTestFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceRepresentativeFragmentTestFeaturesNV};
    void* pNext = nullptr;
    Bool32 representativeFragmentTest{0};
};
struct PipelineRepresentativeFragmentTestStateCreateInfoNV {
    StructureType sType{StructureType::PipelineRepresentativeFragmentTestStateCreateInfoNV};
    const void* pNext = nullptr;
    Bool32 representativeFragmentTestEnable{0};
};
struct PhysicalDeviceExclusiveScissorFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceExclusiveScissorFeaturesNV};
    void* pNext = nullptr;
    Bool32 exclusiveScissor{0};
};
struct PipelineViewportExclusiveScissorStateCreateInfoNV {
    StructureType sType{StructureType::PipelineViewportExclusiveScissorStateCreateInfoNV};
    const void* pNext = nullptr;
    uint32_t exclusiveScissorCount{0};
    const Rect2D* pExclusiveScissors = nullptr;
};
struct PhysicalDeviceCornerSampledImageFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceCornerSampledImageFeaturesNV};
    void* pNext = nullptr;
    Bool32 cornerSampledImage{0};
};
struct PhysicalDeviceComputeShaderDerivativesFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceComputeShaderDerivativesFeaturesNV};
    void* pNext = nullptr;
    Bool32 computeDerivativeGroupQuads{0};
    Bool32 computeDerivativeGroupLinear{0};
};
struct PhysicalDeviceFragmentShaderBarycentricFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceFragmentShaderBarycentricFeaturesNV};
    void* pNext = nullptr;
    Bool32 fragmentShaderBarycentric{0};
};
struct PhysicalDeviceShaderImageFootprintFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceShaderImageFootprintFeaturesNV};
    void* pNext = nullptr;
    Bool32 imageFootprint{0};
};
struct PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV};
    void* pNext = nullptr;
    Bool32 dedicatedAllocationImageAliasing{0};
};
struct ShadingRatePaletteNV {
    uint32_t shadingRatePaletteEntryCount{0};
    const ShadingRatePaletteEntryNV* pShadingRatePaletteEntries = nullptr;
};
struct PipelineViewportShadingRateImageStateCreateInfoNV {
    StructureType sType{StructureType::PipelineViewportShadingRateImageStateCreateInfoNV};
    const void* pNext = nullptr;
    Bool32 shadingRateImageEnable{0};
    uint32_t viewportCount{0};
    const ShadingRatePaletteNV* pShadingRatePalettes = nullptr;
};
struct PhysicalDeviceShadingRateImageFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceShadingRateImageFeaturesNV};
    void* pNext = nullptr;
    Bool32 shadingRateImage{0};
    Bool32 shadingRateCoarseSampleOrder{0};
};
struct PhysicalDeviceShadingRateImagePropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceShadingRateImagePropertiesNV};
    void* pNext = nullptr;
    Extent2D shadingRateTexelSize{};
    uint32_t shadingRatePaletteSize{0};
    uint32_t shadingRateMaxCoarseSamples{0};
};
struct CoarseSampleLocationNV {
    uint32_t pixelX{0};
    uint32_t pixelY{0};
    uint32_t sample{0};
    constexpr bool operator==(CoarseSampleLocationNV const& value) const {
        return pixelX == value.pixelX && pixelY == value.pixelY && sample == value.sample ;}
    constexpr bool operator!=(CoarseSampleLocationNV const& value) const {return !(*this == value);}
};
struct CoarseSampleOrderCustomNV {
    ShadingRatePaletteEntryNV shadingRate{static_cast<ShadingRatePaletteEntryNV>(0)};
    uint32_t sampleCount{0};
    uint32_t sampleLocationCount{0};
    const CoarseSampleLocationNV* pSampleLocations = nullptr;
};
struct PipelineViewportCoarseSampleOrderStateCreateInfoNV {
    StructureType sType{StructureType::PipelineViewportCoarseSampleOrderStateCreateInfoNV};
    const void* pNext = nullptr;
    CoarseSampleOrderTypeNV sampleOrderType{static_cast<CoarseSampleOrderTypeNV>(0)};
    uint32_t customSampleOrderCount{0};
    const CoarseSampleOrderCustomNV* pCustomSampleOrders = nullptr;
};
struct PhysicalDeviceMeshShaderFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceMeshShaderFeaturesNV};
    void* pNext = nullptr;
    Bool32 taskShader{0};
    Bool32 meshShader{0};
};
struct PhysicalDeviceMeshShaderPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceMeshShaderPropertiesNV};
    void* pNext = nullptr;
    uint32_t maxDrawMeshTasksCount{0};
    uint32_t maxTaskWorkGroupInvocations{0};
    uint32_t maxTaskWorkGroupSize[3];
    uint32_t maxTaskTotalMemorySize{0};
    uint32_t maxTaskOutputCount{0};
    uint32_t maxMeshWorkGroupInvocations{0};
    uint32_t maxMeshWorkGroupSize[3];
    uint32_t maxMeshTotalMemorySize{0};
    uint32_t maxMeshOutputVertices{0};
    uint32_t maxMeshOutputPrimitives{0};
    uint32_t maxMeshMultiviewViewCount{0};
    uint32_t meshOutputPerVertexGranularity{0};
    uint32_t meshOutputPerPrimitiveGranularity{0};
};
struct DrawMeshTasksIndirectCommandNV {
    uint32_t taskCount{0};
    uint32_t firstTask{0};
    constexpr bool operator==(DrawMeshTasksIndirectCommandNV const& value) const {
        return taskCount == value.taskCount && firstTask == value.firstTask ;}
    constexpr bool operator!=(DrawMeshTasksIndirectCommandNV const& value) const {return !(*this == value);}
};
struct RayTracingShaderGroupCreateInfoNV {
    StructureType sType{StructureType::RayTracingShaderGroupCreateInfoNV};
    const void* pNext = nullptr;
    RayTracingShaderGroupTypeKHR type{static_cast<RayTracingShaderGroupTypeKHR>(0)};
    uint32_t generalShader{0};
    uint32_t closestHitShader{0};
    uint32_t anyHitShader{0};
    uint32_t intersectionShader{0};
};
struct RayTracingShaderGroupCreateInfoKHR {
    StructureType sType{StructureType::RayTracingShaderGroupCreateInfoKHR};
    const void* pNext = nullptr;
    RayTracingShaderGroupTypeKHR type{static_cast<RayTracingShaderGroupTypeKHR>(0)};
    uint32_t generalShader{0};
    uint32_t closestHitShader{0};
    uint32_t anyHitShader{0};
    uint32_t intersectionShader{0};
    const void* pShaderGroupCaptureReplayHandle = nullptr;
};
struct RayTracingPipelineCreateInfoNV {
    StructureType sType{StructureType::RayTracingPipelineCreateInfoNV};
    const void* pNext = nullptr;
    PipelineCreateFlags flags{};
    uint32_t stageCount{0};
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    uint32_t groupCount{0};
    const RayTracingShaderGroupCreateInfoNV* pGroups = nullptr;
    uint32_t maxRecursionDepth{0};
    PipelineLayout layout{};
    Pipeline basePipelineHandle{};
    int32_t basePipelineIndex{0};
};
struct RayTracingPipelineInterfaceCreateInfoKHR {
    StructureType sType{StructureType::RayTracingPipelineInterfaceCreateInfoKHR};
    const void* pNext = nullptr;
    uint32_t maxPipelineRayPayloadSize{0};
    uint32_t maxPipelineRayHitAttributeSize{0};
};
struct PipelineLibraryCreateInfoKHR {
    StructureType sType{StructureType::PipelineLibraryCreateInfoKHR};
    const void* pNext = nullptr;
    uint32_t libraryCount{0};
    const Pipeline* pLibraries = nullptr;
};
struct RayTracingPipelineCreateInfoKHR {
    StructureType sType{StructureType::RayTracingPipelineCreateInfoKHR};
    const void* pNext = nullptr;
    PipelineCreateFlags flags{};
    uint32_t stageCount{0};
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    uint32_t groupCount{0};
    const RayTracingShaderGroupCreateInfoKHR* pGroups = nullptr;
    uint32_t maxPipelineRayRecursionDepth{0};
    const PipelineLibraryCreateInfoKHR* pLibraryInfo = nullptr;
    const RayTracingPipelineInterfaceCreateInfoKHR* pLibraryInterface = nullptr;
    const PipelineDynamicStateCreateInfo* pDynamicState = nullptr;
    PipelineLayout layout{};
    Pipeline basePipelineHandle{};
    int32_t basePipelineIndex{0};
};
struct GeometryTrianglesNV {
    StructureType sType{StructureType::GeometryTrianglesNV};
    const void* pNext = nullptr;
    Buffer vertexData{};
    DeviceSize vertexOffset{0};
    uint32_t vertexCount{0};
    DeviceSize vertexStride{0};
    Format vertexFormat{static_cast<Format>(0)};
    Buffer indexData{};
    DeviceSize indexOffset{0};
    uint32_t indexCount{0};
    IndexType indexType{static_cast<IndexType>(0)};
    Buffer transformData{};
    DeviceSize transformOffset{0};
};
struct GeometryAABBNV {
    StructureType sType{StructureType::GeometryAabbNV};
    const void* pNext = nullptr;
    Buffer aabbData{};
    uint32_t numAABBs{0};
    uint32_t stride{0};
    DeviceSize offset{0};
};
struct GeometryDataNV {
    GeometryTrianglesNV triangles{};
    GeometryAABBNV aabbs{};
};
struct GeometryNV {
    StructureType sType{StructureType::GeometryNV};
    const void* pNext = nullptr;
    GeometryTypeKHR geometryType{static_cast<GeometryTypeKHR>(0)};
    GeometryDataNV geometry{};
    GeometryFlagsKHR flags{};
};
struct AccelerationStructureInfoNV {
    StructureType sType{StructureType::AccelerationStructureInfoNV};
    const void* pNext = nullptr;
    AccelerationStructureTypeNV type{static_cast<AccelerationStructureTypeNV>(0)};
    BuildAccelerationStructureFlagsNV flags{};
    uint32_t instanceCount{0};
    uint32_t geometryCount{0};
    const GeometryNV* pGeometries = nullptr;
};
struct AccelerationStructureCreateInfoNV {
    StructureType sType{StructureType::AccelerationStructureCreateInfoNV};
    const void* pNext = nullptr;
    DeviceSize compactedSize{0};
    AccelerationStructureInfoNV info{};
};
struct BindAccelerationStructureMemoryInfoNV {
    StructureType sType{StructureType::BindAccelerationStructureMemoryInfoNV};
    const void* pNext = nullptr;
    AccelerationStructureNV accelerationStructure{};
    DeviceMemory memory{};
    DeviceSize memoryOffset{0};
    uint32_t deviceIndexCount{0};
    const uint32_t* pDeviceIndices = nullptr;
};
struct WriteDescriptorSetAccelerationStructureKHR {
    StructureType sType{StructureType::WriteDescriptorSetAccelerationStructureKHR};
    const void* pNext = nullptr;
    uint32_t accelerationStructureCount{0};
    const AccelerationStructureKHR* pAccelerationStructures = nullptr;
};
struct WriteDescriptorSetAccelerationStructureNV {
    StructureType sType{StructureType::WriteDescriptorSetAccelerationStructureNV};
    const void* pNext = nullptr;
    uint32_t accelerationStructureCount{0};
    const AccelerationStructureNV* pAccelerationStructures = nullptr;
};
struct AccelerationStructureMemoryRequirementsInfoNV {
    StructureType sType{StructureType::AccelerationStructureMemoryRequirementsInfoNV};
    const void* pNext = nullptr;
    AccelerationStructureMemoryRequirementsTypeNV type{static_cast<AccelerationStructureMemoryRequirementsTypeNV>(0)};
    AccelerationStructureNV accelerationStructure{};
};
struct PhysicalDeviceAccelerationStructureFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceAccelerationStructureFeaturesKHR};
    void* pNext = nullptr;
    Bool32 accelerationStructure{0};
    Bool32 accelerationStructureCaptureReplay{0};
    Bool32 accelerationStructureIndirectBuild{0};
    Bool32 accelerationStructureHostCommands{0};
    Bool32 descriptorBindingAccelerationStructureUpdateAfterBind{0};
};
struct PhysicalDeviceRayTracingPipelineFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceRayTracingPipelineFeaturesKHR};
    void* pNext = nullptr;
    Bool32 rayTracingPipeline{0};
    Bool32 rayTracingPipelineShaderGroupHandleCaptureReplay{0};
    Bool32 rayTracingPipelineShaderGroupHandleCaptureReplayMixed{0};
    Bool32 rayTracingPipelineTraceRaysIndirect{0};
    Bool32 rayTraversalPrimitiveCulling{0};
};
struct PhysicalDeviceRayQueryFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceRayQueryFeaturesKHR};
    void* pNext = nullptr;
    Bool32 rayQuery{0};
};
struct PhysicalDeviceAccelerationStructurePropertiesKHR {
    StructureType sType{StructureType::PhysicalDeviceAccelerationStructurePropertiesKHR};
    void* pNext = nullptr;
    uint64_t maxGeometryCount{0};
    uint64_t maxInstanceCount{0};
    uint64_t maxPrimitiveCount{0};
    uint32_t maxPerStageDescriptorAccelerationStructures{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindAccelerationStructures{0};
    uint32_t maxDescriptorSetAccelerationStructures{0};
    uint32_t maxDescriptorSetUpdateAfterBindAccelerationStructures{0};
    uint32_t minAccelerationStructureScratchOffsetAlignment{0};
};
struct PhysicalDeviceRayTracingPipelinePropertiesKHR {
    StructureType sType{StructureType::PhysicalDeviceRayTracingPipelinePropertiesKHR};
    void* pNext = nullptr;
    uint32_t shaderGroupHandleSize{0};
    uint32_t maxRayRecursionDepth{0};
    uint32_t maxShaderGroupStride{0};
    uint32_t shaderGroupBaseAlignment{0};
    uint32_t shaderGroupHandleCaptureReplaySize{0};
    uint32_t maxRayDispatchInvocationCount{0};
    uint32_t shaderGroupHandleAlignment{0};
    uint32_t maxRayHitAttributeSize{0};
};
struct PhysicalDeviceRayTracingPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceRayTracingPropertiesNV};
    void* pNext = nullptr;
    uint32_t shaderGroupHandleSize{0};
    uint32_t maxRecursionDepth{0};
    uint32_t maxShaderGroupStride{0};
    uint32_t shaderGroupBaseAlignment{0};
    uint64_t maxGeometryCount{0};
    uint64_t maxInstanceCount{0};
    uint64_t maxTriangleCount{0};
    uint32_t maxDescriptorSetAccelerationStructures{0};
};
struct StridedDeviceAddressRegionKHR {
    DeviceAddress deviceAddress{0};
    DeviceSize stride{0};
    DeviceSize size{0};
    constexpr bool operator==(StridedDeviceAddressRegionKHR const& value) const {
        return deviceAddress == value.deviceAddress && stride == value.stride && size == value.size ;}
    constexpr bool operator!=(StridedDeviceAddressRegionKHR const& value) const {return !(*this == value);}
};
struct TraceRaysIndirectCommandKHR {
    uint32_t width{0};
    uint32_t height{0};
    uint32_t depth{0};
    constexpr bool operator==(TraceRaysIndirectCommandKHR const& value) const {
        return width == value.width && height == value.height && depth == value.depth ;}
    constexpr bool operator!=(TraceRaysIndirectCommandKHR const& value) const {return !(*this == value);}
};
struct DrmFormatModifierPropertiesEXT {
    uint64_t drmFormatModifier{0};
    uint32_t drmFormatModifierPlaneCount{0};
    FormatFeatureFlags drmFormatModifierTilingFeatures{};
    constexpr bool operator==(DrmFormatModifierPropertiesEXT const& value) const {
        return drmFormatModifier == value.drmFormatModifier && drmFormatModifierPlaneCount == value.drmFormatModifierPlaneCount && drmFormatModifierTilingFeatures == value.drmFormatModifierTilingFeatures 
        ;}
    constexpr bool operator!=(DrmFormatModifierPropertiesEXT const& value) const {return !(*this == value);}
};
struct DrmFormatModifierPropertiesListEXT {
    StructureType sType{StructureType::DrmFormatModifierPropertiesListEXT};
    void* pNext = nullptr;
    uint32_t drmFormatModifierCount{0};
    DrmFormatModifierPropertiesEXT* pDrmFormatModifierProperties = nullptr;
};
struct PhysicalDeviceImageDrmFormatModifierInfoEXT {
    StructureType sType{StructureType::PhysicalDeviceImageDrmFormatModifierInfoEXT};
    const void* pNext = nullptr;
    uint64_t drmFormatModifier{0};
    SharingMode sharingMode{static_cast<SharingMode>(0)};
    uint32_t queueFamilyIndexCount{0};
    const uint32_t* pQueueFamilyIndices = nullptr;
};
struct ImageDrmFormatModifierListCreateInfoEXT {
    StructureType sType{StructureType::ImageDrmFormatModifierListCreateInfoEXT};
    const void* pNext = nullptr;
    uint32_t drmFormatModifierCount{0};
    const uint64_t* pDrmFormatModifiers = nullptr;
};
struct ImageDrmFormatModifierExplicitCreateInfoEXT {
    StructureType sType{StructureType::ImageDrmFormatModifierExplicitCreateInfoEXT};
    const void* pNext = nullptr;
    uint64_t drmFormatModifier{0};
    uint32_t drmFormatModifierPlaneCount{0};
    const SubresourceLayout* pPlaneLayouts = nullptr;
};
struct ImageDrmFormatModifierPropertiesEXT {
    StructureType sType{StructureType::ImageDrmFormatModifierPropertiesEXT};
    void* pNext = nullptr;
    uint64_t drmFormatModifier{0};
};
struct ImageStencilUsageCreateInfo {
    StructureType sType{StructureType::ImageStencilUsageCreateInfo};
    const void* pNext = nullptr;
    ImageUsageFlags stencilUsage{};
};
using ImageStencilUsageCreateInfoEXT = ImageStencilUsageCreateInfo;
struct DeviceMemoryOverallocationCreateInfoAMD {
    StructureType sType{StructureType::DeviceMemoryOverallocationCreateInfoAMD};
    const void* pNext = nullptr;
    MemoryOverallocationBehaviorAMD overallocationBehavior{static_cast<MemoryOverallocationBehaviorAMD>(0)};
};
struct PhysicalDeviceFragmentDensityMapFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT};
    void* pNext = nullptr;
    Bool32 fragmentDensityMap{0};
    Bool32 fragmentDensityMapDynamic{0};
    Bool32 fragmentDensityMapNonSubsampledImages{0};
};
struct PhysicalDeviceFragmentDensityMap2FeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT};
    void* pNext = nullptr;
    Bool32 fragmentDensityMapDeferred{0};
};
struct PhysicalDeviceFragmentDensityMapPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT};
    void* pNext = nullptr;
    Extent2D minFragmentDensityTexelSize{};
    Extent2D maxFragmentDensityTexelSize{};
    Bool32 fragmentDensityInvocations{0};
};
struct PhysicalDeviceFragmentDensityMap2PropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT};
    void* pNext = nullptr;
    Bool32 subsampledLoads{0};
    Bool32 subsampledCoarseReconstructionEarlyAccess{0};
    uint32_t maxSubsampledArrayLayers{0};
    uint32_t maxDescriptorSetSubsampledSamplers{0};
};
struct RenderPassFragmentDensityMapCreateInfoEXT {
    StructureType sType{StructureType::RenderPassFragmentDensityMapCreateInfoEXT};
    const void* pNext = nullptr;
    AttachmentReference fragmentDensityMapAttachment{};
};
struct PhysicalDeviceScalarBlockLayoutFeatures {
    StructureType sType{StructureType::PhysicalDeviceScalarBlockLayoutFeatures};
    void* pNext = nullptr;
    Bool32 scalarBlockLayout{0};
};
using PhysicalDeviceScalarBlockLayoutFeaturesEXT = PhysicalDeviceScalarBlockLayoutFeatures;
struct SurfaceProtectedCapabilitiesKHR {
    StructureType sType{StructureType::SurfaceProtectedCapabilitiesKHR};
    const void* pNext = nullptr;
    Bool32 supportsProtected{0};
};
struct PhysicalDeviceUniformBufferStandardLayoutFeatures {
    StructureType sType{StructureType::PhysicalDeviceUniformBufferStandardLayoutFeatures};
    void* pNext = nullptr;
    Bool32 uniformBufferStandardLayout{0};
};
using PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR = PhysicalDeviceUniformBufferStandardLayoutFeatures;
struct PhysicalDeviceDepthClipEnableFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceDepthClipEnableFeaturesEXT};
    void* pNext = nullptr;
    Bool32 depthClipEnable{0};
};
struct PipelineRasterizationDepthClipStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineRasterizationDepthClipStateCreateInfoEXT};
    const void* pNext = nullptr;
    PipelineRasterizationDepthClipStateCreateFlagsEXT flags{};
    Bool32 depthClipEnable{0};
};
struct PhysicalDeviceMemoryBudgetPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceMemoryBudgetPropertiesEXT};
    void* pNext = nullptr;
    DeviceSize heapBudget[MAX_MEMORY_HEAPS];
    DeviceSize heapUsage[MAX_MEMORY_HEAPS];
};
struct PhysicalDeviceMemoryPriorityFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceMemoryPriorityFeaturesEXT};
    void* pNext = nullptr;
    Bool32 memoryPriority{0};
};
struct MemoryPriorityAllocateInfoEXT {
    StructureType sType{StructureType::MemoryPriorityAllocateInfoEXT};
    const void* pNext = nullptr;
    float priority{0.f};
};
struct PhysicalDeviceBufferDeviceAddressFeatures {
    StructureType sType{StructureType::PhysicalDeviceBufferDeviceAddressFeatures};
    void* pNext = nullptr;
    Bool32 bufferDeviceAddress{0};
    Bool32 bufferDeviceAddressCaptureReplay{0};
    Bool32 bufferDeviceAddressMultiDevice{0};
};
using PhysicalDeviceBufferDeviceAddressFeaturesKHR = PhysicalDeviceBufferDeviceAddressFeatures;
struct PhysicalDeviceBufferDeviceAddressFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceBufferDeviceAddressFeaturesEXT};
    void* pNext = nullptr;
    Bool32 bufferDeviceAddress{0};
    Bool32 bufferDeviceAddressCaptureReplay{0};
    Bool32 bufferDeviceAddressMultiDevice{0};
};
using PhysicalDeviceBufferAddressFeaturesEXT = PhysicalDeviceBufferDeviceAddressFeaturesEXT;
struct BufferDeviceAddressInfo {
    StructureType sType{StructureType::BufferDeviceAddressInfo};
    const void* pNext = nullptr;
    Buffer buffer{};
};
using BufferDeviceAddressInfoKHR = BufferDeviceAddressInfo;
using BufferDeviceAddressInfoEXT = BufferDeviceAddressInfo;
struct BufferOpaqueCaptureAddressCreateInfo {
    StructureType sType{StructureType::BufferOpaqueCaptureAddressCreateInfo};
    const void* pNext = nullptr;
    uint64_t opaqueCaptureAddress{0};
};
using BufferOpaqueCaptureAddressCreateInfoKHR = BufferOpaqueCaptureAddressCreateInfo;
struct BufferDeviceAddressCreateInfoEXT {
    StructureType sType{StructureType::BufferDeviceAddressCreateInfoEXT};
    const void* pNext = nullptr;
    DeviceAddress deviceAddress{0};
};
struct PhysicalDeviceImageViewImageFormatInfoEXT {
    StructureType sType{StructureType::PhysicalDeviceImageViewImageFormatInfoEXT};
    void* pNext = nullptr;
    ImageViewType imageViewType{static_cast<ImageViewType>(0)};
};
struct FilterCubicImageViewImageFormatPropertiesEXT {
    StructureType sType{StructureType::FilterCubicImageViewImageFormatPropertiesEXT};
    void* pNext = nullptr;
    Bool32 filterCubic{0};
    Bool32 filterCubicMinmax{0};
};
struct PhysicalDeviceImagelessFramebufferFeatures {
    StructureType sType{StructureType::PhysicalDeviceImagelessFramebufferFeatures};
    void* pNext = nullptr;
    Bool32 imagelessFramebuffer{0};
};
using PhysicalDeviceImagelessFramebufferFeaturesKHR = PhysicalDeviceImagelessFramebufferFeatures;
struct FramebufferAttachmentImageInfo {
    StructureType sType{StructureType::FramebufferAttachmentImageInfo};
    const void* pNext = nullptr;
    ImageCreateFlags flags{};
    ImageUsageFlags usage{};
    uint32_t width{0};
    uint32_t height{0};
    uint32_t layerCount{0};
    uint32_t viewFormatCount{0};
    const Format* pViewFormats = nullptr;
};
struct FramebufferAttachmentsCreateInfo {
    StructureType sType{StructureType::FramebufferAttachmentsCreateInfo};
    const void* pNext = nullptr;
    uint32_t attachmentImageInfoCount{0};
    const FramebufferAttachmentImageInfo* pAttachmentImageInfos = nullptr;
};
using FramebufferAttachmentsCreateInfoKHR = FramebufferAttachmentsCreateInfo;
using FramebufferAttachmentImageInfoKHR = FramebufferAttachmentImageInfo;
struct RenderPassAttachmentBeginInfo {
    StructureType sType{StructureType::RenderPassAttachmentBeginInfo};
    const void* pNext = nullptr;
    uint32_t attachmentCount{0};
    const ImageView* pAttachments = nullptr;
};
using RenderPassAttachmentBeginInfoKHR = RenderPassAttachmentBeginInfo;
struct PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT};
    void* pNext = nullptr;
    Bool32 textureCompressionASTC_HDR{0};
};
struct PhysicalDeviceCooperativeMatrixFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceCooperativeMatrixFeaturesNV};
    void* pNext = nullptr;
    Bool32 cooperativeMatrix{0};
    Bool32 cooperativeMatrixRobustBufferAccess{0};
};
struct PhysicalDeviceCooperativeMatrixPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceCooperativeMatrixPropertiesNV};
    void* pNext = nullptr;
    ShaderStageFlags cooperativeMatrixSupportedStages{};
};
struct CooperativeMatrixPropertiesNV {
    StructureType sType{StructureType::CooperativeMatrixPropertiesNV};
    void* pNext = nullptr;
    uint32_t MSize{0};
    uint32_t NSize{0};
    uint32_t KSize{0};
    ComponentTypeNV AType{static_cast<ComponentTypeNV>(0)};
    ComponentTypeNV BType{static_cast<ComponentTypeNV>(0)};
    ComponentTypeNV CType{static_cast<ComponentTypeNV>(0)};
    ComponentTypeNV DType{static_cast<ComponentTypeNV>(0)};
    ScopeNV scope{static_cast<ScopeNV>(0)};
};
struct PhysicalDeviceYcbcrImageArraysFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceYcbcrImageArraysFeaturesEXT};
    void* pNext = nullptr;
    Bool32 ycbcrImageArrays{0};
};
struct ImageViewHandleInfoNVX {
    StructureType sType{StructureType::ImageViewHandleInfoNVX};
    const void* pNext = nullptr;
    ImageView imageView{};
    DescriptorType descriptorType{static_cast<DescriptorType>(0)};
    Sampler sampler{};
};
struct ImageViewAddressPropertiesNVX {
    StructureType sType{StructureType::ImageViewAddressPropertiesNVX};
    void* pNext = nullptr;
    DeviceAddress deviceAddress{0};
    DeviceSize size{0};
};
#if defined(VK_USE_PLATFORM_GGP)
struct PresentFrameTokenGGP {
    StructureType sType{StructureType::PresentFrameTokenGGP};
    const void* pNext = nullptr;
    GgpFrameToken frameToken{};
};
#endif // defined(VK_USE_PLATFORM_GGP)
struct PipelineCreationFeedbackEXT {
    PipelineCreationFeedbackFlagsEXT flags{};
    uint64_t duration{0};
    constexpr bool operator==(PipelineCreationFeedbackEXT const& value) const {
        return flags == value.flags && duration == value.duration ;}
    constexpr bool operator!=(PipelineCreationFeedbackEXT const& value) const {return !(*this == value);}
};
struct PipelineCreationFeedbackCreateInfoEXT {
    StructureType sType{StructureType::PipelineCreationFeedbackCreateInfoEXT};
    const void* pNext = nullptr;
    PipelineCreationFeedbackEXT* pPipelineCreationFeedback = nullptr;
    uint32_t pipelineStageCreationFeedbackCount{0};
    PipelineCreationFeedbackEXT* pPipelineStageCreationFeedbacks = nullptr;
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct SurfaceFullScreenExclusiveInfoEXT {
    StructureType sType{StructureType::SurfaceFullScreenExclusiveInfoEXT};
    void* pNext = nullptr;
    FullScreenExclusiveEXT fullScreenExclusive{static_cast<FullScreenExclusiveEXT>(0)};
};
struct SurfaceFullScreenExclusiveWin32InfoEXT {
    StructureType sType{StructureType::SurfaceFullScreenExclusiveWin32InfoEXT};
    const void* pNext = nullptr;
    HMONITOR hmonitor{};
};
struct SurfaceCapabilitiesFullScreenExclusiveEXT {
    StructureType sType{StructureType::SurfaceCapabilitiesFullScreenExclusiveEXT};
    void* pNext = nullptr;
    Bool32 fullScreenExclusiveSupported{0};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct PhysicalDevicePerformanceQueryFeaturesKHR {
    StructureType sType{StructureType::PhysicalDevicePerformanceQueryFeaturesKHR};
    void* pNext = nullptr;
    Bool32 performanceCounterQueryPools{0};
    Bool32 performanceCounterMultipleQueryPools{0};
};
struct PhysicalDevicePerformanceQueryPropertiesKHR {
    StructureType sType{StructureType::PhysicalDevicePerformanceQueryPropertiesKHR};
    void* pNext = nullptr;
    Bool32 allowCommandBufferQueryCopies{0};
};
struct PerformanceCounterKHR {
    StructureType sType{StructureType::PerformanceCounterKHR};
    const void* pNext = nullptr;
    PerformanceCounterUnitKHR unit{static_cast<PerformanceCounterUnitKHR>(0)};
    PerformanceCounterScopeKHR scope{static_cast<PerformanceCounterScopeKHR>(0)};
    PerformanceCounterStorageKHR storage{static_cast<PerformanceCounterStorageKHR>(0)};
    uint8_t uuid[UUID_SIZE];
};
struct PerformanceCounterDescriptionKHR {
    StructureType sType{StructureType::PerformanceCounterDescriptionKHR};
    const void* pNext = nullptr;
    PerformanceCounterDescriptionFlagsKHR flags{};
    char name[MAX_DESCRIPTION_SIZE];
    char category[MAX_DESCRIPTION_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
};
struct QueryPoolPerformanceCreateInfoKHR {
    StructureType sType{StructureType::QueryPoolPerformanceCreateInfoKHR};
    const void* pNext = nullptr;
    uint32_t queueFamilyIndex{0};
    uint32_t counterIndexCount{0};
    const uint32_t* pCounterIndices = nullptr;
};
union PerformanceCounterResultKHR {
    int32_t int32;
    int64_t int64;
    uint32_t uint32;
    uint64_t uint64;
    float float32;
    double float64;
    constexpr bool operator==(PerformanceCounterResultKHR const& value) const {
        return int32 == value.int32 && int64 == value.int64 && uint32 == value.uint32 && uint64 == value.uint64 && float32 == value.float32 && float64 == value.float64 
        ;}
    constexpr bool operator!=(PerformanceCounterResultKHR const& value) const {return !(*this == value);}
};
struct AcquireProfilingLockInfoKHR {
    StructureType sType{StructureType::AcquireProfilingLockInfoKHR};
    const void* pNext = nullptr;
    AcquireProfilingLockFlagsKHR flags{};
    uint64_t timeout{0};
};
struct PerformanceQuerySubmitInfoKHR {
    StructureType sType{StructureType::PerformanceQuerySubmitInfoKHR};
    const void* pNext = nullptr;
    uint32_t counterPassIndex{0};
};
struct HeadlessSurfaceCreateInfoEXT {
    StructureType sType{StructureType::HeadlessSurfaceCreateInfoEXT};
    const void* pNext = nullptr;
    HeadlessSurfaceCreateFlagsEXT flags{};
};
struct PhysicalDeviceCoverageReductionModeFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceCoverageReductionModeFeaturesNV};
    void* pNext = nullptr;
    Bool32 coverageReductionMode{0};
};
struct PipelineCoverageReductionStateCreateInfoNV {
    StructureType sType{StructureType::PipelineCoverageReductionStateCreateInfoNV};
    const void* pNext = nullptr;
    PipelineCoverageReductionStateCreateFlagsNV flags{};
    CoverageReductionModeNV coverageReductionMode{static_cast<CoverageReductionModeNV>(0)};
};
struct FramebufferMixedSamplesCombinationNV {
    StructureType sType{StructureType::FramebufferMixedSamplesCombinationNV};
    void* pNext = nullptr;
    CoverageReductionModeNV coverageReductionMode{static_cast<CoverageReductionModeNV>(0)};
    SampleCountFlagBits rasterizationSamples{static_cast<SampleCountFlagBits>(0)};
    SampleCountFlags depthStencilSamples{};
    SampleCountFlags colorSamples{};
};
struct PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL {
    StructureType sType{StructureType::PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL};
    void* pNext = nullptr;
    Bool32 shaderIntegerFunctions2{0};
};
union PerformanceValueDataINTEL {
    uint32_t value32;
    uint64_t value64;
    float valueFloat;
    Bool32 valueBool;
    const char* valueString;
};
struct PerformanceValueINTEL {
    PerformanceValueTypeINTEL type{static_cast<PerformanceValueTypeINTEL>(0)};
    PerformanceValueDataINTEL data{};
};
struct InitializePerformanceApiInfoINTEL {
    StructureType sType{StructureType::InitializePerformanceApiInfoINTEL};
    const void* pNext = nullptr;
    void* pUserData = nullptr;
};
struct QueryPoolPerformanceQueryCreateInfoINTEL {
    StructureType sType{StructureType::QueryPoolPerformanceQueryCreateInfoINTEL};
    const void* pNext = nullptr;
    QueryPoolSamplingModeINTEL performanceCountersSampling{static_cast<QueryPoolSamplingModeINTEL>(0)};
};
using QueryPoolCreateInfoINTEL = QueryPoolPerformanceQueryCreateInfoINTEL;
struct PerformanceMarkerInfoINTEL {
    StructureType sType{StructureType::PerformanceMarkerInfoINTEL};
    const void* pNext = nullptr;
    uint64_t marker{0};
};
struct PerformanceStreamMarkerInfoINTEL {
    StructureType sType{StructureType::PerformanceStreamMarkerInfoINTEL};
    const void* pNext = nullptr;
    uint32_t marker{0};
};
struct PerformanceOverrideInfoINTEL {
    StructureType sType{StructureType::PerformanceOverrideInfoINTEL};
    const void* pNext = nullptr;
    PerformanceOverrideTypeINTEL type{static_cast<PerformanceOverrideTypeINTEL>(0)};
    Bool32 enable{0};
    uint64_t parameter{0};
};
struct PerformanceConfigurationAcquireInfoINTEL {
    StructureType sType{StructureType::PerformanceConfigurationAcquireInfoINTEL};
    const void* pNext = nullptr;
    PerformanceConfigurationTypeINTEL type{static_cast<PerformanceConfigurationTypeINTEL>(0)};
};
struct PhysicalDeviceShaderClockFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceShaderClockFeaturesKHR};
    void* pNext = nullptr;
    Bool32 shaderSubgroupClock{0};
    Bool32 shaderDeviceClock{0};
};
struct PhysicalDeviceIndexTypeUint8FeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceIndexTypeUint8FeaturesEXT};
    void* pNext = nullptr;
    Bool32 indexTypeUint8{0};
};
struct PhysicalDeviceShaderSMBuiltinsPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV};
    void* pNext = nullptr;
    uint32_t shaderSMCount{0};
    uint32_t shaderWarpsPerSM{0};
};
struct PhysicalDeviceShaderSMBuiltinsFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV};
    void* pNext = nullptr;
    Bool32 shaderSMBuiltins{0};
};
struct PhysicalDeviceFragmentShaderInterlockFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceFragmentShaderInterlockFeaturesEXT};
    void* pNext = nullptr;
    Bool32 fragmentShaderSampleInterlock{0};
    Bool32 fragmentShaderPixelInterlock{0};
    Bool32 fragmentShaderShadingRateInterlock{0};
};
struct PhysicalDeviceSeparateDepthStencilLayoutsFeatures {
    StructureType sType{StructureType::PhysicalDeviceSeparateDepthStencilLayoutsFeatures};
    void* pNext = nullptr;
    Bool32 separateDepthStencilLayouts{0};
};
using PhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR = PhysicalDeviceSeparateDepthStencilLayoutsFeatures;
struct AttachmentReferenceStencilLayout {
    StructureType sType{StructureType::AttachmentReferenceStencilLayout};
    void* pNext = nullptr;
    ImageLayout stencilLayout{static_cast<ImageLayout>(0)};
};
using AttachmentReferenceStencilLayoutKHR = AttachmentReferenceStencilLayout;
struct AttachmentDescriptionStencilLayout {
    StructureType sType{StructureType::AttachmentDescriptionStencilLayout};
    void* pNext = nullptr;
    ImageLayout stencilInitialLayout{static_cast<ImageLayout>(0)};
    ImageLayout stencilFinalLayout{static_cast<ImageLayout>(0)};
};
using AttachmentDescriptionStencilLayoutKHR = AttachmentDescriptionStencilLayout;
struct PhysicalDevicePipelineExecutablePropertiesFeaturesKHR {
    StructureType sType{StructureType::PhysicalDevicePipelineExecutablePropertiesFeaturesKHR};
    void* pNext = nullptr;
    Bool32 pipelineExecutableInfo{0};
};
struct PipelineInfoKHR {
    StructureType sType{StructureType::PipelineInfoKHR};
    const void* pNext = nullptr;
    Pipeline pipeline{};
};
struct PipelineExecutablePropertiesKHR {
    StructureType sType{StructureType::PipelineExecutablePropertiesKHR};
    void* pNext = nullptr;
    ShaderStageFlags stages{};
    char name[MAX_DESCRIPTION_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    uint32_t subgroupSize{0};
};
struct PipelineExecutableInfoKHR {
    StructureType sType{StructureType::PipelineExecutableInfoKHR};
    const void* pNext = nullptr;
    Pipeline pipeline{};
    uint32_t executableIndex{0};
};
union PipelineExecutableStatisticValueKHR {
    Bool32 b32;
    int64_t i64;
    uint64_t u64;
    double f64;
    constexpr bool operator==(PipelineExecutableStatisticValueKHR const& value) const {
        return b32 == value.b32 && i64 == value.i64 && u64 == value.u64 && f64 == value.f64 ;}
    constexpr bool operator!=(PipelineExecutableStatisticValueKHR const& value) const {return !(*this == value);}
};
struct PipelineExecutableStatisticKHR {
    StructureType sType{StructureType::PipelineExecutableStatisticKHR};
    void* pNext = nullptr;
    char name[MAX_DESCRIPTION_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    PipelineExecutableStatisticFormatKHR format{static_cast<PipelineExecutableStatisticFormatKHR>(0)};
    PipelineExecutableStatisticValueKHR value{};
};
struct PipelineExecutableInternalRepresentationKHR {
    StructureType sType{StructureType::PipelineExecutableInternalRepresentationKHR};
    void* pNext = nullptr;
    char name[MAX_DESCRIPTION_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    Bool32 isText{0};
    size_t dataSize{0};
    void* pData = nullptr;
};
struct PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT};
    void* pNext = nullptr;
    Bool32 shaderDemoteToHelperInvocation{0};
};
struct PhysicalDeviceTexelBufferAlignmentFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceTexelBufferAlignmentFeaturesEXT};
    void* pNext = nullptr;
    Bool32 texelBufferAlignment{0};
};
struct PhysicalDeviceTexelBufferAlignmentPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceTexelBufferAlignmentPropertiesEXT};
    void* pNext = nullptr;
    DeviceSize storageTexelBufferOffsetAlignmentBytes{0};
    Bool32 storageTexelBufferOffsetSingleTexelAlignment{0};
    DeviceSize uniformTexelBufferOffsetAlignmentBytes{0};
    Bool32 uniformTexelBufferOffsetSingleTexelAlignment{0};
};
struct PhysicalDeviceSubgroupSizeControlFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT};
    void* pNext = nullptr;
    Bool32 subgroupSizeControl{0};
    Bool32 computeFullSubgroups{0};
};
struct PhysicalDeviceSubgroupSizeControlPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT};
    void* pNext = nullptr;
    uint32_t minSubgroupSize{0};
    uint32_t maxSubgroupSize{0};
    uint32_t maxComputeWorkgroupSubgroups{0};
    ShaderStageFlags requiredSubgroupSizeStages{};
};
struct PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT {
    StructureType sType{StructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT};
    void* pNext = nullptr;
    uint32_t requiredSubgroupSize{0};
};
struct MemoryOpaqueCaptureAddressAllocateInfo {
    StructureType sType{StructureType::MemoryOpaqueCaptureAddressAllocateInfo};
    const void* pNext = nullptr;
    uint64_t opaqueCaptureAddress{0};
};
using MemoryOpaqueCaptureAddressAllocateInfoKHR = MemoryOpaqueCaptureAddressAllocateInfo;
struct DeviceMemoryOpaqueCaptureAddressInfo {
    StructureType sType{StructureType::DeviceMemoryOpaqueCaptureAddressInfo};
    const void* pNext = nullptr;
    DeviceMemory memory{};
};
using DeviceMemoryOpaqueCaptureAddressInfoKHR = DeviceMemoryOpaqueCaptureAddressInfo;
struct PhysicalDeviceLineRasterizationFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceLineRasterizationFeaturesEXT};
    void* pNext = nullptr;
    Bool32 rectangularLines{0};
    Bool32 bresenhamLines{0};
    Bool32 smoothLines{0};
    Bool32 stippledRectangularLines{0};
    Bool32 stippledBresenhamLines{0};
    Bool32 stippledSmoothLines{0};
};
struct PhysicalDeviceLineRasterizationPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceLineRasterizationPropertiesEXT};
    void* pNext = nullptr;
    uint32_t lineSubPixelPrecisionBits{0};
};
struct PipelineRasterizationLineStateCreateInfoEXT {
    StructureType sType{StructureType::PipelineRasterizationLineStateCreateInfoEXT};
    const void* pNext = nullptr;
    LineRasterizationModeEXT lineRasterizationMode{static_cast<LineRasterizationModeEXT>(0)};
    Bool32 stippledLineEnable{0};
    uint32_t lineStippleFactor{0};
    uint16_t lineStipplePattern{0};
};
struct PhysicalDevicePipelineCreationCacheControlFeaturesEXT {
    StructureType sType{StructureType::PhysicalDevicePipelineCreationCacheControlFeaturesEXT};
    void* pNext = nullptr;
    Bool32 pipelineCreationCacheControl{0};
};
struct PhysicalDeviceVulkan11Features {
    StructureType sType{StructureType::PhysicalDeviceVulkan11Features};
    void* pNext = nullptr;
    Bool32 storageBuffer16BitAccess{0};
    Bool32 uniformAndStorageBuffer16BitAccess{0};
    Bool32 storagePushConstant16{0};
    Bool32 storageInputOutput16{0};
    Bool32 multiview{0};
    Bool32 multiviewGeometryShader{0};
    Bool32 multiviewTessellationShader{0};
    Bool32 variablePointersStorageBuffer{0};
    Bool32 variablePointers{0};
    Bool32 protectedMemory{0};
    Bool32 samplerYcbcrConversion{0};
    Bool32 shaderDrawParameters{0};
};
struct PhysicalDeviceVulkan11Properties {
    StructureType sType{StructureType::PhysicalDeviceVulkan11Properties};
    void* pNext = nullptr;
    uint8_t deviceUUID[UUID_SIZE];
    uint8_t driverUUID[UUID_SIZE];
    uint8_t deviceLUID[LUID_SIZE];
    uint32_t deviceNodeMask{0};
    Bool32 deviceLUIDValid{0};
    uint32_t subgroupSize{0};
    ShaderStageFlags subgroupSupportedStages{};
    SubgroupFeatureFlags subgroupSupportedOperations{};
    Bool32 subgroupQuadOperationsInAllStages{0};
    PointClippingBehavior pointClippingBehavior{static_cast<PointClippingBehavior>(0)};
    uint32_t maxMultiviewViewCount{0};
    uint32_t maxMultiviewInstanceIndex{0};
    Bool32 protectedNoFault{0};
    uint32_t maxPerSetDescriptors{0};
    DeviceSize maxMemoryAllocationSize{0};
};
struct PhysicalDeviceVulkan12Features {
    StructureType sType{StructureType::PhysicalDeviceVulkan12Features};
    void* pNext = nullptr;
    Bool32 samplerMirrorClampToEdge{0};
    Bool32 drawIndirectCount{0};
    Bool32 storageBuffer8BitAccess{0};
    Bool32 uniformAndStorageBuffer8BitAccess{0};
    Bool32 storagePushConstant8{0};
    Bool32 shaderBufferInt64Atomics{0};
    Bool32 shaderSharedInt64Atomics{0};
    Bool32 shaderFloat16{0};
    Bool32 shaderInt8{0};
    Bool32 descriptorIndexing{0};
    Bool32 shaderInputAttachmentArrayDynamicIndexing{0};
    Bool32 shaderUniformTexelBufferArrayDynamicIndexing{0};
    Bool32 shaderStorageTexelBufferArrayDynamicIndexing{0};
    Bool32 shaderUniformBufferArrayNonUniformIndexing{0};
    Bool32 shaderSampledImageArrayNonUniformIndexing{0};
    Bool32 shaderStorageBufferArrayNonUniformIndexing{0};
    Bool32 shaderStorageImageArrayNonUniformIndexing{0};
    Bool32 shaderInputAttachmentArrayNonUniformIndexing{0};
    Bool32 shaderUniformTexelBufferArrayNonUniformIndexing{0};
    Bool32 shaderStorageTexelBufferArrayNonUniformIndexing{0};
    Bool32 descriptorBindingUniformBufferUpdateAfterBind{0};
    Bool32 descriptorBindingSampledImageUpdateAfterBind{0};
    Bool32 descriptorBindingStorageImageUpdateAfterBind{0};
    Bool32 descriptorBindingStorageBufferUpdateAfterBind{0};
    Bool32 descriptorBindingUniformTexelBufferUpdateAfterBind{0};
    Bool32 descriptorBindingStorageTexelBufferUpdateAfterBind{0};
    Bool32 descriptorBindingUpdateUnusedWhilePending{0};
    Bool32 descriptorBindingPartiallyBound{0};
    Bool32 descriptorBindingVariableDescriptorCount{0};
    Bool32 runtimeDescriptorArray{0};
    Bool32 samplerFilterMinmax{0};
    Bool32 scalarBlockLayout{0};
    Bool32 imagelessFramebuffer{0};
    Bool32 uniformBufferStandardLayout{0};
    Bool32 shaderSubgroupExtendedTypes{0};
    Bool32 separateDepthStencilLayouts{0};
    Bool32 hostQueryReset{0};
    Bool32 timelineSemaphore{0};
    Bool32 bufferDeviceAddress{0};
    Bool32 bufferDeviceAddressCaptureReplay{0};
    Bool32 bufferDeviceAddressMultiDevice{0};
    Bool32 vulkanMemoryModel{0};
    Bool32 vulkanMemoryModelDeviceScope{0};
    Bool32 vulkanMemoryModelAvailabilityVisibilityChains{0};
    Bool32 shaderOutputViewportIndex{0};
    Bool32 shaderOutputLayer{0};
    Bool32 subgroupBroadcastDynamicId{0};
};
struct PhysicalDeviceVulkan12Properties {
    StructureType sType{StructureType::PhysicalDeviceVulkan12Properties};
    void* pNext = nullptr;
    DriverId driverID{static_cast<DriverId>(0)};
    char driverName[MAX_DRIVER_NAME_SIZE];
    char driverInfo[MAX_DRIVER_INFO_SIZE];
    ConformanceVersion conformanceVersion{};
    ShaderFloatControlsIndependence denormBehaviorIndependence{static_cast<ShaderFloatControlsIndependence>(0)};
    ShaderFloatControlsIndependence roundingModeIndependence{static_cast<ShaderFloatControlsIndependence>(0)};
    Bool32 shaderSignedZeroInfNanPreserveFloat16{0};
    Bool32 shaderSignedZeroInfNanPreserveFloat32{0};
    Bool32 shaderSignedZeroInfNanPreserveFloat64{0};
    Bool32 shaderDenormPreserveFloat16{0};
    Bool32 shaderDenormPreserveFloat32{0};
    Bool32 shaderDenormPreserveFloat64{0};
    Bool32 shaderDenormFlushToZeroFloat16{0};
    Bool32 shaderDenormFlushToZeroFloat32{0};
    Bool32 shaderDenormFlushToZeroFloat64{0};
    Bool32 shaderRoundingModeRTEFloat16{0};
    Bool32 shaderRoundingModeRTEFloat32{0};
    Bool32 shaderRoundingModeRTEFloat64{0};
    Bool32 shaderRoundingModeRTZFloat16{0};
    Bool32 shaderRoundingModeRTZFloat32{0};
    Bool32 shaderRoundingModeRTZFloat64{0};
    uint32_t maxUpdateAfterBindDescriptorsInAllPools{0};
    Bool32 shaderUniformBufferArrayNonUniformIndexingNative{0};
    Bool32 shaderSampledImageArrayNonUniformIndexingNative{0};
    Bool32 shaderStorageBufferArrayNonUniformIndexingNative{0};
    Bool32 shaderStorageImageArrayNonUniformIndexingNative{0};
    Bool32 shaderInputAttachmentArrayNonUniformIndexingNative{0};
    Bool32 robustBufferAccessUpdateAfterBind{0};
    Bool32 quadDivergentImplicitLod{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindSamplers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindUniformBuffers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageBuffers{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindSampledImages{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageImages{0};
    uint32_t maxPerStageDescriptorUpdateAfterBindInputAttachments{0};
    uint32_t maxPerStageUpdateAfterBindResources{0};
    uint32_t maxDescriptorSetUpdateAfterBindSamplers{0};
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffers{0};
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffersDynamic{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffers{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffersDynamic{0};
    uint32_t maxDescriptorSetUpdateAfterBindSampledImages{0};
    uint32_t maxDescriptorSetUpdateAfterBindStorageImages{0};
    uint32_t maxDescriptorSetUpdateAfterBindInputAttachments{0};
    ResolveModeFlags supportedDepthResolveModes{};
    ResolveModeFlags supportedStencilResolveModes{};
    Bool32 independentResolveNone{0};
    Bool32 independentResolve{0};
    Bool32 filterMinmaxSingleComponentFormats{0};
    Bool32 filterMinmaxImageComponentMapping{0};
    uint64_t maxTimelineSemaphoreValueDifference{0};
    SampleCountFlags framebufferIntegerColorSampleCounts{};
};
struct PipelineCompilerControlCreateInfoAMD {
    StructureType sType{StructureType::PipelineCompilerControlCreateInfoAMD};
    const void* pNext = nullptr;
    PipelineCompilerControlFlagsAMD compilerControlFlags{};
};
struct PhysicalDeviceCoherentMemoryFeaturesAMD {
    StructureType sType{StructureType::PhysicalDeviceCoherentMemoryFeaturesAMD};
    void* pNext = nullptr;
    Bool32 deviceCoherentMemory{0};
};
struct PhysicalDeviceToolPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceToolPropertiesEXT};
    void* pNext = nullptr;
    char name[MAX_EXTENSION_NAME_SIZE];
    char version[MAX_EXTENSION_NAME_SIZE];
    ToolPurposeFlagsEXT purposes{};
    char description[MAX_DESCRIPTION_SIZE];
    char layer[MAX_EXTENSION_NAME_SIZE];
};
struct SamplerCustomBorderColorCreateInfoEXT {
    StructureType sType{StructureType::SamplerCustomBorderColorCreateInfoEXT};
    const void* pNext = nullptr;
    ClearColorValue customBorderColor{};
    Format format{static_cast<Format>(0)};
};
struct PhysicalDeviceCustomBorderColorPropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceCustomBorderColorPropertiesEXT};
    void* pNext = nullptr;
    uint32_t maxCustomBorderColorSamplers{0};
};
struct PhysicalDeviceCustomBorderColorFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceCustomBorderColorFeaturesEXT};
    void* pNext = nullptr;
    Bool32 customBorderColors{0};
    Bool32 customBorderColorWithoutFormat{0};
};
union DeviceOrHostAddressKHR {
    DeviceAddress deviceAddress;
    void* hostAddress;
};
union DeviceOrHostAddressConstKHR {
    DeviceAddress deviceAddress;
    const void* hostAddress;
};
struct AccelerationStructureGeometryTrianglesDataKHR {
    StructureType sType{StructureType::AccelerationStructureGeometryTrianglesDataKHR};
    const void* pNext = nullptr;
    Format vertexFormat{static_cast<Format>(0)};
    DeviceOrHostAddressConstKHR vertexData{};
    DeviceSize vertexStride{0};
    uint32_t maxVertex{0};
    IndexType indexType{static_cast<IndexType>(0)};
    DeviceOrHostAddressConstKHR indexData{};
    DeviceOrHostAddressConstKHR transformData{};
};
struct AccelerationStructureGeometryAabbsDataKHR {
    StructureType sType{StructureType::AccelerationStructureGeometryAabbsDataKHR};
    const void* pNext = nullptr;
    DeviceOrHostAddressConstKHR data{};
    DeviceSize stride{0};
};
struct AccelerationStructureGeometryInstancesDataKHR {
    StructureType sType{StructureType::AccelerationStructureGeometryInstancesDataKHR};
    const void* pNext = nullptr;
    Bool32 arrayOfPointers{0};
    DeviceOrHostAddressConstKHR data{};
};
union AccelerationStructureGeometryDataKHR {
    AccelerationStructureGeometryTrianglesDataKHR triangles;
    AccelerationStructureGeometryAabbsDataKHR aabbs;
    AccelerationStructureGeometryInstancesDataKHR instances;
};
struct AccelerationStructureGeometryKHR {
    StructureType sType{StructureType::AccelerationStructureGeometryKHR};
    const void* pNext = nullptr;
    GeometryTypeKHR geometryType{static_cast<GeometryTypeKHR>(0)};
    AccelerationStructureGeometryDataKHR geometry{};
    GeometryFlagsKHR flags{};
};
struct AccelerationStructureBuildGeometryInfoKHR {
    StructureType sType{StructureType::AccelerationStructureBuildGeometryInfoKHR};
    const void* pNext = nullptr;
    AccelerationStructureTypeKHR type{static_cast<AccelerationStructureTypeKHR>(0)};
    BuildAccelerationStructureFlagsKHR flags{};
    BuildAccelerationStructureModeKHR mode{static_cast<BuildAccelerationStructureModeKHR>(0)};
    AccelerationStructureKHR srcAccelerationStructure{};
    AccelerationStructureKHR dstAccelerationStructure{};
    uint32_t geometryCount{0};
    const AccelerationStructureGeometryKHR* pGeometries = nullptr;
    const AccelerationStructureGeometryKHR* const* ppGeometries = nullptr;
    DeviceOrHostAddressKHR scratchData{};
};
struct AccelerationStructureBuildRangeInfoKHR {
    uint32_t primitiveCount{0};
    uint32_t primitiveOffset{0};
    uint32_t firstVertex{0};
    uint32_t transformOffset{0};
    constexpr bool operator==(AccelerationStructureBuildRangeInfoKHR const& value) const {
        return primitiveCount == value.primitiveCount && primitiveOffset == value.primitiveOffset && firstVertex == value.firstVertex && transformOffset == value.transformOffset 
        ;}
    constexpr bool operator!=(AccelerationStructureBuildRangeInfoKHR const& value) const {return !(*this == value);}
};
struct AccelerationStructureCreateInfoKHR {
    StructureType sType{StructureType::AccelerationStructureCreateInfoKHR};
    const void* pNext = nullptr;
    AccelerationStructureCreateFlagsKHR createFlags{};
    Buffer buffer{};
    DeviceSize offset{0};
    DeviceSize size{0};
    AccelerationStructureTypeKHR type{static_cast<AccelerationStructureTypeKHR>(0)};
    DeviceAddress deviceAddress{0};
};
struct AabbPositionsKHR {
    float minX{0.f};
    float minY{0.f};
    float minZ{0.f};
    float maxX{0.f};
    float maxY{0.f};
    float maxZ{0.f};
    constexpr bool operator==(AabbPositionsKHR const& value) const {
        return minX == value.minX && minY == value.minY && minZ == value.minZ && maxX == value.maxX && maxY == value.maxY && maxZ == value.maxZ ;}
    constexpr bool operator!=(AabbPositionsKHR const& value) const {return !(*this == value);}
};
using AabbPositionsNV = AabbPositionsKHR;
struct TransformMatrixKHR {
    float matrix[3][4];
    constexpr bool operator==(TransformMatrixKHR const& value) const {
        bool is_equal = true;
                for(uint32_t i = 0; i < 3; i++)
            for(uint32_t j = 0; j < 4; j++)
                is_equal &= matrix[i][j] == value.matrix[i][j];
        return is_equal;}
    constexpr bool operator!=(TransformMatrixKHR const& value) const {return !(*this == value);}
};
using TransformMatrixNV = TransformMatrixKHR;
struct AccelerationStructureInstanceKHR {
    TransformMatrixKHR transform{};
    uint32_t instanceCustomIndex:24;
    uint32_t mask:8;
    uint32_t instanceShaderBindingTableRecordOffset:24;
    uint32_t flags:8;
    uint64_t accelerationStructureReference{0};
    constexpr bool operator==(AccelerationStructureInstanceKHR const& value) const {
        return transform == value.transform && instanceCustomIndex == value.instanceCustomIndex && mask == value.mask && instanceShaderBindingTableRecordOffset == value.instanceShaderBindingTableRecordOffset 
        && flags == value.flags && accelerationStructureReference == value.accelerationStructureReference ;}
    constexpr bool operator!=(AccelerationStructureInstanceKHR const& value) const {return !(*this == value);}
};
using AccelerationStructureInstanceNV = AccelerationStructureInstanceKHR;
struct AccelerationStructureDeviceAddressInfoKHR {
    StructureType sType{StructureType::AccelerationStructureDeviceAddressInfoKHR};
    const void* pNext = nullptr;
    AccelerationStructureKHR accelerationStructure{};
};
struct AccelerationStructureVersionInfoKHR {
    StructureType sType{StructureType::AccelerationStructureVersionInfoKHR};
    const void* pNext = nullptr;
    const uint8_t* pVersionData = nullptr;
};
struct CopyAccelerationStructureInfoKHR {
    StructureType sType{StructureType::CopyAccelerationStructureInfoKHR};
    const void* pNext = nullptr;
    AccelerationStructureKHR src{};
    AccelerationStructureKHR dst{};
    CopyAccelerationStructureModeKHR mode{static_cast<CopyAccelerationStructureModeKHR>(0)};
};
struct CopyAccelerationStructureToMemoryInfoKHR {
    StructureType sType{StructureType::CopyAccelerationStructureToMemoryInfoKHR};
    const void* pNext = nullptr;
    AccelerationStructureKHR src{};
    DeviceOrHostAddressKHR dst{};
    CopyAccelerationStructureModeKHR mode{static_cast<CopyAccelerationStructureModeKHR>(0)};
};
struct CopyMemoryToAccelerationStructureInfoKHR {
    StructureType sType{StructureType::CopyMemoryToAccelerationStructureInfoKHR};
    const void* pNext = nullptr;
    DeviceOrHostAddressConstKHR src{};
    AccelerationStructureKHR dst{};
    CopyAccelerationStructureModeKHR mode{static_cast<CopyAccelerationStructureModeKHR>(0)};
};
struct PhysicalDeviceExtendedDynamicStateFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceExtendedDynamicStateFeaturesEXT};
    void* pNext = nullptr;
    Bool32 extendedDynamicState{0};
};
struct RenderPassTransformBeginInfoQCOM {
    StructureType sType{StructureType::RenderPassTransformBeginInfoQCOM};
    void* pNext = nullptr;
    SurfaceTransformFlagBitsKHR transform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
};
struct CopyCommandTransformInfoQCOM {
    StructureType sType{StructureType::CopyCommandTransformInfoQCOM};
    const void* pNext = nullptr;
    SurfaceTransformFlagBitsKHR transform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
};
struct CommandBufferInheritanceRenderPassTransformInfoQCOM {
    StructureType sType{StructureType::CommandBufferInheritanceRenderPassTransformInfoQCOM};
    void* pNext = nullptr;
    SurfaceTransformFlagBitsKHR transform{static_cast<SurfaceTransformFlagBitsKHR>(0)};
    Rect2D renderArea{};
};
struct PhysicalDeviceDiagnosticsConfigFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceDiagnosticsConfigFeaturesNV};
    void* pNext = nullptr;
    Bool32 diagnosticsConfig{0};
};
struct DeviceDiagnosticsConfigCreateInfoNV {
    StructureType sType{StructureType::DeviceDiagnosticsConfigCreateInfoNV};
    const void* pNext = nullptr;
    DeviceDiagnosticsConfigFlagsNV flags{};
};
struct PhysicalDeviceRobustness2FeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceRobustness2FeaturesEXT};
    void* pNext = nullptr;
    Bool32 robustBufferAccess2{0};
    Bool32 robustImageAccess2{0};
    Bool32 nullDescriptor{0};
};
struct PhysicalDeviceRobustness2PropertiesEXT {
    StructureType sType{StructureType::PhysicalDeviceRobustness2PropertiesEXT};
    void* pNext = nullptr;
    DeviceSize robustStorageBufferAccessSizeAlignment{0};
    DeviceSize robustUniformBufferAccessSizeAlignment{0};
};
struct PhysicalDeviceImageRobustnessFeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceImageRobustnessFeaturesEXT};
    void* pNext = nullptr;
    Bool32 robustImageAccess{0};
};
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct PhysicalDevicePortabilitySubsetFeaturesKHR {
    StructureType sType{StructureType::PhysicalDevicePortabilitySubsetFeaturesKHR};
    void* pNext = nullptr;
    Bool32 constantAlphaColorBlendFactors{0};
    Bool32 events{0};
    Bool32 imageViewFormatReinterpretation{0};
    Bool32 imageViewFormatSwizzle{0};
    Bool32 imageView2DOn3DImage{0};
    Bool32 multisampleArrayImage{0};
    Bool32 mutableComparisonSamplers{0};
    Bool32 pointPolygons{0};
    Bool32 samplerMipLodBias{0};
    Bool32 separateStencilMaskRef{0};
    Bool32 shaderSampleRateInterpolationFunctions{0};
    Bool32 tessellationIsolines{0};
    Bool32 tessellationPointMode{0};
    Bool32 triangleFans{0};
    Bool32 vertexAttributeAccessBeyondStride{0};
};
struct PhysicalDevicePortabilitySubsetPropertiesKHR {
    StructureType sType{StructureType::PhysicalDevicePortabilitySubsetPropertiesKHR};
    void* pNext = nullptr;
    uint32_t minVertexInputBindingStrideAlignment{0};
};
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct PhysicalDevice4444FormatsFeaturesEXT {
    StructureType sType{StructureType::PhysicalDevice4444FormatsFeaturesEXT};
    void* pNext = nullptr;
    Bool32 formatA4R4G4B4{0};
    Bool32 formatA4B4G4R4{0};
};
struct BufferCopy2KHR {
    StructureType sType{StructureType::BufferCopy2KHR};
    const void* pNext = nullptr;
    DeviceSize srcOffset{0};
    DeviceSize dstOffset{0};
    DeviceSize size{0};
};
struct ImageCopy2KHR {
    StructureType sType{StructureType::ImageCopy2KHR};
    const void* pNext = nullptr;
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffset{};
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffset{};
    Extent3D extent{};
};
struct ImageBlit2KHR {
    StructureType sType{StructureType::ImageBlit2KHR};
    const void* pNext = nullptr;
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffsets[2];
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffsets[2];
};
struct BufferImageCopy2KHR {
    StructureType sType{StructureType::BufferImageCopy2KHR};
    const void* pNext = nullptr;
    DeviceSize bufferOffset{0};
    uint32_t bufferRowLength{0};
    uint32_t bufferImageHeight{0};
    ImageSubresourceLayers imageSubresource{};
    Offset3D imageOffset{};
    Extent3D imageExtent{};
};
struct ImageResolve2KHR {
    StructureType sType{StructureType::ImageResolve2KHR};
    const void* pNext = nullptr;
    ImageSubresourceLayers srcSubresource{};
    Offset3D srcOffset{};
    ImageSubresourceLayers dstSubresource{};
    Offset3D dstOffset{};
    Extent3D extent{};
};
struct CopyBufferInfo2KHR {
    StructureType sType{StructureType::CopyBufferInfo2KHR};
    const void* pNext = nullptr;
    Buffer srcBuffer{};
    Buffer dstBuffer{};
    uint32_t regionCount{0};
    const BufferCopy2KHR* pRegions = nullptr;
};
struct CopyImageInfo2KHR {
    StructureType sType{StructureType::CopyImageInfo2KHR};
    const void* pNext = nullptr;
    Image srcImage{};
    ImageLayout srcImageLayout{static_cast<ImageLayout>(0)};
    Image dstImage{};
    ImageLayout dstImageLayout{static_cast<ImageLayout>(0)};
    uint32_t regionCount{0};
    const ImageCopy2KHR* pRegions = nullptr;
};
struct BlitImageInfo2KHR {
    StructureType sType{StructureType::BlitImageInfo2KHR};
    const void* pNext = nullptr;
    Image srcImage{};
    ImageLayout srcImageLayout{static_cast<ImageLayout>(0)};
    Image dstImage{};
    ImageLayout dstImageLayout{static_cast<ImageLayout>(0)};
    uint32_t regionCount{0};
    const ImageBlit2KHR* pRegions = nullptr;
    Filter filter{static_cast<Filter>(0)};
};
struct CopyBufferToImageInfo2KHR {
    StructureType sType{StructureType::CopyBufferToImageInfo2KHR};
    const void* pNext = nullptr;
    Buffer srcBuffer{};
    Image dstImage{};
    ImageLayout dstImageLayout{static_cast<ImageLayout>(0)};
    uint32_t regionCount{0};
    const BufferImageCopy2KHR* pRegions = nullptr;
};
struct CopyImageToBufferInfo2KHR {
    StructureType sType{StructureType::CopyImageToBufferInfo2KHR};
    const void* pNext = nullptr;
    Image srcImage{};
    ImageLayout srcImageLayout{static_cast<ImageLayout>(0)};
    Buffer dstBuffer{};
    uint32_t regionCount{0};
    const BufferImageCopy2KHR* pRegions = nullptr;
};
struct ResolveImageInfo2KHR {
    StructureType sType{StructureType::ResolveImageInfo2KHR};
    const void* pNext = nullptr;
    Image srcImage{};
    ImageLayout srcImageLayout{static_cast<ImageLayout>(0)};
    Image dstImage{};
    ImageLayout dstImageLayout{static_cast<ImageLayout>(0)};
    uint32_t regionCount{0};
    const ImageResolve2KHR* pRegions = nullptr;
};
struct PhysicalDeviceShaderImageAtomicInt64FeaturesEXT {
    StructureType sType{StructureType::PhysicalDeviceShaderImageAtomicInt64FeaturesEXT};
    void* pNext = nullptr;
    Bool32 shaderImageInt64Atomics{0};
    Bool32 sparseImageInt64Atomics{0};
};
struct FragmentShadingRateAttachmentInfoKHR {
    StructureType sType{StructureType::FragmentShadingRateAttachmentInfoKHR};
    const void* pNext = nullptr;
    const AttachmentReference2* pFragmentShadingRateAttachment = nullptr;
    Extent2D shadingRateAttachmentTexelSize{};
};
struct PipelineFragmentShadingRateStateCreateInfoKHR {
    StructureType sType{StructureType::PipelineFragmentShadingRateStateCreateInfoKHR};
    const void* pNext = nullptr;
    Extent2D fragmentSize{};
    FragmentShadingRateCombinerOpKHR combinerOps[2];
};
struct PhysicalDeviceFragmentShadingRateFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceFragmentShadingRateFeaturesKHR};
    void* pNext = nullptr;
    Bool32 pipelineFragmentShadingRate{0};
    Bool32 primitiveFragmentShadingRate{0};
    Bool32 attachmentFragmentShadingRate{0};
};
struct PhysicalDeviceFragmentShadingRatePropertiesKHR {
    StructureType sType{StructureType::PhysicalDeviceFragmentShadingRatePropertiesKHR};
    void* pNext = nullptr;
    Extent2D minFragmentShadingRateAttachmentTexelSize{};
    Extent2D maxFragmentShadingRateAttachmentTexelSize{};
    uint32_t maxFragmentShadingRateAttachmentTexelSizeAspectRatio{0};
    Bool32 primitiveFragmentShadingRateWithMultipleViewports{0};
    Bool32 layeredShadingRateAttachments{0};
    Bool32 fragmentShadingRateNonTrivialCombinerOps{0};
    Extent2D maxFragmentSize{};
    uint32_t maxFragmentSizeAspectRatio{0};
    uint32_t maxFragmentShadingRateCoverageSamples{0};
    SampleCountFlagBits maxFragmentShadingRateRasterizationSamples{static_cast<SampleCountFlagBits>(0)};
    Bool32 fragmentShadingRateWithShaderDepthStencilWrites{0};
    Bool32 fragmentShadingRateWithSampleMask{0};
    Bool32 fragmentShadingRateWithShaderSampleMask{0};
    Bool32 fragmentShadingRateWithConservativeRasterization{0};
    Bool32 fragmentShadingRateWithFragmentShaderInterlock{0};
    Bool32 fragmentShadingRateWithCustomSampleLocations{0};
    Bool32 fragmentShadingRateStrictMultiplyCombiner{0};
};
struct PhysicalDeviceFragmentShadingRateKHR {
    StructureType sType{StructureType::PhysicalDeviceFragmentShadingRateKHR};
    void* pNext = nullptr;
    SampleCountFlags sampleCounts{};
    Extent2D fragmentSize{};
};
struct PhysicalDeviceShaderTerminateInvocationFeaturesKHR {
    StructureType sType{StructureType::PhysicalDeviceShaderTerminateInvocationFeaturesKHR};
    void* pNext = nullptr;
    Bool32 shaderTerminateInvocation{0};
};
struct PhysicalDeviceFragmentShadingRateEnumsFeaturesNV {
    StructureType sType{StructureType::PhysicalDeviceFragmentShadingRateEnumsFeaturesNV};
    void* pNext = nullptr;
    Bool32 fragmentShadingRateEnums{0};
    Bool32 supersampleFragmentShadingRates{0};
    Bool32 noInvocationFragmentShadingRates{0};
};
struct PhysicalDeviceFragmentShadingRateEnumsPropertiesNV {
    StructureType sType{StructureType::PhysicalDeviceFragmentShadingRateEnumsPropertiesNV};
    void* pNext = nullptr;
    SampleCountFlagBits maxFragmentShadingRateInvocationCount{static_cast<SampleCountFlagBits>(0)};
};
struct PipelineFragmentShadingRateEnumStateCreateInfoNV {
    StructureType sType{StructureType::PipelineFragmentShadingRateEnumStateCreateInfoNV};
    const void* pNext = nullptr;
    FragmentShadingRateTypeNV shadingRateType{static_cast<FragmentShadingRateTypeNV>(0)};
    FragmentShadingRateNV shadingRate{static_cast<FragmentShadingRateNV>(0)};
    FragmentShadingRateCombinerOpKHR combinerOps[2];
};
struct AccelerationStructureBuildSizesInfoKHR {
    StructureType sType{StructureType::AccelerationStructureBuildSizesInfoKHR};
    const void* pNext = nullptr;
    DeviceSize accelerationStructureSize{0};
    DeviceSize updateScratchSize{0};
    DeviceSize buildScratchSize{0};
};
namespace detail {
using PFN_CreateInstance = Result (*) (const InstanceCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Instance* pInstance);
using PFN_DestroyInstance = void (*) (Instance instance, const AllocationCallbacks* pAllocator);
using PFN_EnumeratePhysicalDevices = Result (*) (Instance instance, uint32_t* pPhysicalDeviceCount, PhysicalDevice* pPhysicalDevices);
using PFN_GetDeviceProcAddr = PFN_VoidFunction (*) (Device device, const char* pName);
using PFN_GetInstanceProcAddr = PFN_VoidFunction (*) (Instance instance, const char* pName);
using PFN_GetPhysicalDeviceProperties = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceProperties* pProperties);
using PFN_GetPhysicalDeviceQueueFamilyProperties = void (*) (PhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, QueueFamilyProperties* pQueueFamilyProperties);
using PFN_GetPhysicalDeviceMemoryProperties = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceMemoryProperties* pMemoryProperties);
using PFN_GetPhysicalDeviceFeatures = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceFeatures* pFeatures);
using PFN_GetPhysicalDeviceFormatProperties = void (*) (PhysicalDevice physicalDevice, Format format, FormatProperties* pFormatProperties);
using PFN_GetPhysicalDeviceImageFormatProperties = Result (*) (PhysicalDevice physicalDevice, Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags, ImageFormatProperties* pImageFormatProperties);
using PFN_CreateDevice = Result (*) (PhysicalDevice physicalDevice, const DeviceCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Device* pDevice);
using PFN_DestroyDevice = void (*) (Device device, const AllocationCallbacks* pAllocator);
using PFN_EnumerateInstanceVersion = Result (*) (uint32_t* pApiVersion);
using PFN_EnumerateInstanceLayerProperties = Result (*) (uint32_t* pPropertyCount, LayerProperties* pProperties);
using PFN_EnumerateInstanceExtensionProperties = Result (*) (const char* pLayerName, uint32_t* pPropertyCount, ExtensionProperties* pProperties);
using PFN_EnumerateDeviceExtensionProperties = Result (*) (PhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, ExtensionProperties* pProperties);
using PFN_GetDeviceQueue = void (*) (Device device, uint32_t queueFamilyIndex, uint32_t queueIndex, Queue* pQueue);
using PFN_QueueSubmit = Result (*) (Queue queue, uint32_t submitCount, const SubmitInfo* pSubmits, Fence fence);
using PFN_QueueWaitIdle = Result (*) (Queue queue);
using PFN_DeviceWaitIdle = Result (*) (Device device);
using PFN_AllocateMemory = Result (*) (Device device, const MemoryAllocateInfo* pAllocateInfo, const AllocationCallbacks* pAllocator, DeviceMemory* pMemory);
using PFN_FreeMemory = void (*) (Device device, DeviceMemory memory, const AllocationCallbacks* pAllocator);
using PFN_MapMemory = Result (*) (Device device, DeviceMemory memory, DeviceSize offset, DeviceSize size, MemoryMapFlags flags, void** ppData);
using PFN_UnmapMemory = void (*) (Device device, DeviceMemory memory);
using PFN_FlushMappedMemoryRanges = Result (*) (Device device, uint32_t memoryRangeCount, const MappedMemoryRange* pMemoryRanges);
using PFN_InvalidateMappedMemoryRanges = Result (*) (Device device, uint32_t memoryRangeCount, const MappedMemoryRange* pMemoryRanges);
using PFN_GetDeviceMemoryCommitment = void (*) (Device device, DeviceMemory memory, DeviceSize* pCommittedMemoryInBytes);
using PFN_GetBufferMemoryRequirements = void (*) (Device device, Buffer buffer, MemoryRequirements* pMemoryRequirements);
using PFN_BindBufferMemory = Result (*) (Device device, Buffer buffer, DeviceMemory memory, DeviceSize memoryOffset);
using PFN_GetImageMemoryRequirements = void (*) (Device device, Image image, MemoryRequirements* pMemoryRequirements);
using PFN_BindImageMemory = Result (*) (Device device, Image image, DeviceMemory memory, DeviceSize memoryOffset);
using PFN_GetImageSparseMemoryRequirements = void (*) (Device device, Image image, uint32_t* pSparseMemoryRequirementCount, SparseImageMemoryRequirements* pSparseMemoryRequirements);
using PFN_GetPhysicalDeviceSparseImageFormatProperties = void (*) (PhysicalDevice physicalDevice, Format format, ImageType type, SampleCountFlagBits samples, ImageUsageFlags usage, ImageTiling tiling, uint32_t* pPropertyCount, SparseImageFormatProperties* pProperties);
using PFN_QueueBindSparse = Result (*) (Queue queue, uint32_t bindInfoCount, const BindSparseInfo* pBindInfo, Fence fence);
using PFN_CreateFence = Result (*) (Device device, const FenceCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Fence* pFence);
using PFN_DestroyFence = void (*) (Device device, Fence fence, const AllocationCallbacks* pAllocator);
using PFN_ResetFences = Result (*) (Device device, uint32_t fenceCount, const Fence* pFences);
using PFN_GetFenceStatus = Result (*) (Device device, Fence fence);
using PFN_WaitForFences = Result (*) (Device device, uint32_t fenceCount, const Fence* pFences, Bool32 waitAll, uint64_t timeout);
using PFN_CreateSemaphore = Result (*) (Device device, const SemaphoreCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Semaphore* pSemaphore);
using PFN_DestroySemaphore = void (*) (Device device, Semaphore semaphore, const AllocationCallbacks* pAllocator);
using PFN_CreateEvent = Result (*) (Device device, const EventCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Event* pEvent);
using PFN_DestroyEvent = void (*) (Device device, Event event, const AllocationCallbacks* pAllocator);
using PFN_GetEventStatus = Result (*) (Device device, Event event);
using PFN_SetEvent = Result (*) (Device device, Event event);
using PFN_ResetEvent = Result (*) (Device device, Event event);
using PFN_CreateQueryPool = Result (*) (Device device, const QueryPoolCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, QueryPool* pQueryPool);
using PFN_DestroyQueryPool = void (*) (Device device, QueryPool queryPool, const AllocationCallbacks* pAllocator);
using PFN_GetQueryPoolResults = Result (*) (Device device, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, DeviceSize stride, QueryResultFlags flags);
using PFN_ResetQueryPool = void (*) (Device device, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
using PFN_ResetQueryPoolEXT = PFN_ResetQueryPool;
using PFN_CreateBuffer = Result (*) (Device device, const BufferCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Buffer* pBuffer);
using PFN_DestroyBuffer = void (*) (Device device, Buffer buffer, const AllocationCallbacks* pAllocator);
using PFN_CreateBufferView = Result (*) (Device device, const BufferViewCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, BufferView* pView);
using PFN_DestroyBufferView = void (*) (Device device, BufferView bufferView, const AllocationCallbacks* pAllocator);
using PFN_CreateImage = Result (*) (Device device, const ImageCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Image* pImage);
using PFN_DestroyImage = void (*) (Device device, Image image, const AllocationCallbacks* pAllocator);
using PFN_GetImageSubresourceLayout = void (*) (Device device, Image image, const ImageSubresource* pSubresource, SubresourceLayout* pLayout);
using PFN_CreateImageView = Result (*) (Device device, const ImageViewCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, ImageView* pView);
using PFN_DestroyImageView = void (*) (Device device, ImageView imageView, const AllocationCallbacks* pAllocator);
using PFN_CreateShaderModule = Result (*) (Device device, const ShaderModuleCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, ShaderModule* pShaderModule);
using PFN_DestroyShaderModule = void (*) (Device device, ShaderModule shaderModule, const AllocationCallbacks* pAllocator);
using PFN_CreatePipelineCache = Result (*) (Device device, const PipelineCacheCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, PipelineCache* pPipelineCache);
using PFN_DestroyPipelineCache = void (*) (Device device, PipelineCache pipelineCache, const AllocationCallbacks* pAllocator);
using PFN_GetPipelineCacheData = Result (*) (Device device, PipelineCache pipelineCache, size_t* pDataSize, void* pData);
using PFN_MergePipelineCaches = Result (*) (Device device, PipelineCache dstCache, uint32_t srcCacheCount, const PipelineCache* pSrcCaches);
using PFN_CreateGraphicsPipelines = Result (*) (Device device, PipelineCache pipelineCache, uint32_t createInfoCount, const GraphicsPipelineCreateInfo* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines);
using PFN_CreateComputePipelines = Result (*) (Device device, PipelineCache pipelineCache, uint32_t createInfoCount, const ComputePipelineCreateInfo* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines);
using PFN_DestroyPipeline = void (*) (Device device, Pipeline pipeline, const AllocationCallbacks* pAllocator);
using PFN_CreatePipelineLayout = Result (*) (Device device, const PipelineLayoutCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, PipelineLayout* pPipelineLayout);
using PFN_DestroyPipelineLayout = void (*) (Device device, PipelineLayout pipelineLayout, const AllocationCallbacks* pAllocator);
using PFN_CreateSampler = Result (*) (Device device, const SamplerCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Sampler* pSampler);
using PFN_DestroySampler = void (*) (Device device, Sampler sampler, const AllocationCallbacks* pAllocator);
using PFN_CreateDescriptorSetLayout = Result (*) (Device device, const DescriptorSetLayoutCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, DescriptorSetLayout* pSetLayout);
using PFN_DestroyDescriptorSetLayout = void (*) (Device device, DescriptorSetLayout descriptorSetLayout, const AllocationCallbacks* pAllocator);
using PFN_CreateDescriptorPool = Result (*) (Device device, const DescriptorPoolCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, DescriptorPool* pDescriptorPool);
using PFN_DestroyDescriptorPool = void (*) (Device device, DescriptorPool descriptorPool, const AllocationCallbacks* pAllocator);
using PFN_ResetDescriptorPool = Result (*) (Device device, DescriptorPool descriptorPool, DescriptorPoolResetFlags flags);
using PFN_AllocateDescriptorSets = Result (*) (Device device, const DescriptorSetAllocateInfo* pAllocateInfo, DescriptorSet* pDescriptorSets);
using PFN_FreeDescriptorSets = Result (*) (Device device, DescriptorPool descriptorPool, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets);
using PFN_UpdateDescriptorSets = void (*) (Device device, uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const CopyDescriptorSet* pDescriptorCopies);
using PFN_CreateFramebuffer = Result (*) (Device device, const FramebufferCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, Framebuffer* pFramebuffer);
using PFN_DestroyFramebuffer = void (*) (Device device, Framebuffer framebuffer, const AllocationCallbacks* pAllocator);
using PFN_CreateRenderPass = Result (*) (Device device, const RenderPassCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, RenderPass* pRenderPass);
using PFN_DestroyRenderPass = void (*) (Device device, RenderPass renderPass, const AllocationCallbacks* pAllocator);
using PFN_GetRenderAreaGranularity = void (*) (Device device, RenderPass renderPass, Extent2D* pGranularity);
using PFN_CreateCommandPool = Result (*) (Device device, const CommandPoolCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, CommandPool* pCommandPool);
using PFN_DestroyCommandPool = void (*) (Device device, CommandPool commandPool, const AllocationCallbacks* pAllocator);
using PFN_ResetCommandPool = Result (*) (Device device, CommandPool commandPool, CommandPoolResetFlags flags);
using PFN_AllocateCommandBuffers = Result (*) (Device device, const CommandBufferAllocateInfo* pAllocateInfo, CommandBuffer* pCommandBuffers);
using PFN_FreeCommandBuffers = void (*) (Device device, CommandPool commandPool, uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers);
using PFN_BeginCommandBuffer = Result (*) (CommandBuffer commandBuffer, const CommandBufferBeginInfo* pBeginInfo);
using PFN_EndCommandBuffer = Result (*) (CommandBuffer commandBuffer);
using PFN_ResetCommandBuffer = Result (*) (CommandBuffer commandBuffer, CommandBufferResetFlags flags);
using PFN_CmdBindPipeline = void (*) (CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, Pipeline pipeline);
using PFN_CmdSetViewport = void (*) (CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const Viewport* pViewports);
using PFN_CmdSetScissor = void (*) (CommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const Rect2D* pScissors);
using PFN_CmdSetLineWidth = void (*) (CommandBuffer commandBuffer, float lineWidth);
using PFN_CmdSetDepthBias = void (*) (CommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor);
using PFN_CmdSetBlendConstants = void (*) (CommandBuffer commandBuffer, const float blendConstants[4]);
using PFN_CmdSetDepthBounds = void (*) (CommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds);
using PFN_CmdSetStencilCompareMask = void (*) (CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t compareMask);
using PFN_CmdSetStencilWriteMask = void (*) (CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t writeMask);
using PFN_CmdSetStencilReference = void (*) (CommandBuffer commandBuffer, StencilFaceFlags faceMask, uint32_t reference);
using PFN_CmdBindDescriptorSets = void (*) (CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const DescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets);
using PFN_CmdBindIndexBuffer = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, IndexType indexType);
using PFN_CmdBindVertexBuffers = void (*) (CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets);
using PFN_CmdDraw = void (*) (CommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
using PFN_CmdDrawIndexed = void (*) (CommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);
using PFN_CmdDrawIndirect = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride);
using PFN_CmdDrawIndexedIndirect = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride);
using PFN_CmdDispatch = void (*) (CommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
using PFN_CmdDispatchIndirect = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset);
using PFN_CmdCopyBuffer = void (*) (CommandBuffer commandBuffer, Buffer srcBuffer, Buffer dstBuffer, uint32_t regionCount, const BufferCopy* pRegions);
using PFN_CmdCopyImage = void (*) (CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageCopy* pRegions);
using PFN_CmdBlitImage = void (*) (CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageBlit* pRegions, Filter filter);
using PFN_CmdCopyBufferToImage = void (*) (CommandBuffer commandBuffer, Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const BufferImageCopy* pRegions);
using PFN_CmdCopyImageToBuffer = void (*) (CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, uint32_t regionCount, const BufferImageCopy* pRegions);
using PFN_CmdUpdateBuffer = void (*) (CommandBuffer commandBuffer, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize dataSize, const void* pData);
using PFN_CmdFillBuffer = void (*) (CommandBuffer commandBuffer, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize size, uint32_t data);
using PFN_CmdClearColorImage = void (*) (CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearColorValue* pColor, uint32_t rangeCount, const ImageSubresourceRange* pRanges);
using PFN_CmdClearDepthStencilImage = void (*) (CommandBuffer commandBuffer, Image image, ImageLayout imageLayout, const ClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const ImageSubresourceRange* pRanges);
using PFN_CmdClearAttachments = void (*) (CommandBuffer commandBuffer, uint32_t attachmentCount, const ClearAttachment* pAttachments, uint32_t rectCount, const ClearRect* pRects);
using PFN_CmdResolveImage = void (*) (CommandBuffer commandBuffer, Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, uint32_t regionCount, const ImageResolve* pRegions);
using PFN_CmdSetEvent = void (*) (CommandBuffer commandBuffer, Event event, PipelineStageFlags stageMask);
using PFN_CmdResetEvent = void (*) (CommandBuffer commandBuffer, Event event, PipelineStageFlags stageMask);
using PFN_CmdWaitEvents = void (*) (CommandBuffer commandBuffer, uint32_t eventCount, const Event* pEvents, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers);
using PFN_CmdPipelineBarrier = void (*) (CommandBuffer commandBuffer, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const MemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const BufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const ImageMemoryBarrier* pImageMemoryBarriers);
using PFN_CmdBeginQuery = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, QueryControlFlags flags);
using PFN_CmdEndQuery = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query);
using PFN_CmdBeginConditionalRenderingEXT = void (*) (CommandBuffer commandBuffer, const ConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin);
using PFN_CmdEndConditionalRenderingEXT = void (*) (CommandBuffer commandBuffer);
using PFN_CmdResetQueryPool = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
using PFN_CmdWriteTimestamp = void (*) (CommandBuffer commandBuffer, PipelineStageFlagBits pipelineStage, QueryPool queryPool, uint32_t query);
using PFN_CmdCopyQueryPoolResults = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize stride, QueryResultFlags flags);
using PFN_CmdPushConstants = void (*) (CommandBuffer commandBuffer, PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues);
using PFN_CmdBeginRenderPass = void (*) (CommandBuffer commandBuffer, const RenderPassBeginInfo* pRenderPassBegin, SubpassContents contents);
using PFN_CmdNextSubpass = void (*) (CommandBuffer commandBuffer, SubpassContents contents);
using PFN_CmdEndRenderPass = void (*) (CommandBuffer commandBuffer);
using PFN_CmdExecuteCommands = void (*) (CommandBuffer commandBuffer, uint32_t commandBufferCount, const CommandBuffer* pCommandBuffers);
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_CreateAndroidSurfaceKHR = Result (*) (Instance instance, const AndroidSurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_GetPhysicalDeviceDisplayPropertiesKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t* pPropertyCount, DisplayPropertiesKHR* pProperties);
using PFN_GetPhysicalDeviceDisplayPlanePropertiesKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t* pPropertyCount, DisplayPlanePropertiesKHR* pProperties);
using PFN_GetDisplayPlaneSupportedDisplaysKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, DisplayKHR* pDisplays);
using PFN_GetDisplayModePropertiesKHR = Result (*) (PhysicalDevice physicalDevice, DisplayKHR display, uint32_t* pPropertyCount, DisplayModePropertiesKHR* pProperties);
using PFN_CreateDisplayModeKHR = Result (*) (PhysicalDevice physicalDevice, DisplayKHR display, const DisplayModeCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, DisplayModeKHR* pMode);
using PFN_GetDisplayPlaneCapabilitiesKHR = Result (*) (PhysicalDevice physicalDevice, DisplayModeKHR mode, uint32_t planeIndex, DisplayPlaneCapabilitiesKHR* pCapabilities);
using PFN_CreateDisplayPlaneSurfaceKHR = Result (*) (Instance instance, const DisplaySurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_CreateSharedSwapchainsKHR = Result (*) (Device device, uint32_t swapchainCount, const SwapchainCreateInfoKHR* pCreateInfos, const AllocationCallbacks* pAllocator, SwapchainKHR* pSwapchains);
using PFN_DestroySurfaceKHR = void (*) (Instance instance, SurfaceKHR surface, const AllocationCallbacks* pAllocator);
using PFN_GetPhysicalDeviceSurfaceSupportKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, SurfaceKHR surface, Bool32* pSupported);
using PFN_GetPhysicalDeviceSurfaceCapabilitiesKHR = Result (*) (PhysicalDevice physicalDevice, SurfaceKHR surface, SurfaceCapabilitiesKHR* pSurfaceCapabilities);
using PFN_GetPhysicalDeviceSurfaceFormatsKHR = Result (*) (PhysicalDevice physicalDevice, SurfaceKHR surface, uint32_t* pSurfaceFormatCount, SurfaceFormatKHR* pSurfaceFormats);
using PFN_GetPhysicalDeviceSurfacePresentModesKHR = Result (*) (PhysicalDevice physicalDevice, SurfaceKHR surface, uint32_t* pPresentModeCount, PresentModeKHR* pPresentModes);
using PFN_CreateSwapchainKHR = Result (*) (Device device, const SwapchainCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SwapchainKHR* pSwapchain);
using PFN_DestroySwapchainKHR = void (*) (Device device, SwapchainKHR swapchain, const AllocationCallbacks* pAllocator);
using PFN_GetSwapchainImagesKHR = Result (*) (Device device, SwapchainKHR swapchain, uint32_t* pSwapchainImageCount, Image* pSwapchainImages);
using PFN_AcquireNextImageKHR = Result (*) (Device device, SwapchainKHR swapchain, uint64_t timeout, Semaphore semaphore, Fence fence, uint32_t* pImageIndex);
using PFN_QueuePresentKHR = Result (*) (Queue queue, const PresentInfoKHR* pPresentInfo);
#if defined(VK_USE_PLATFORM_VI_NN)
using PFN_CreateViSurfaceNN = Result (*) (Instance instance, const ViSurfaceCreateInfoNN* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
using PFN_CreateWaylandSurfaceKHR = Result (*) (Instance instance, const WaylandSurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceWaylandPresentationSupportKHR = Bool32 (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, wl_display* display);
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_CreateWin32SurfaceKHR = Result (*) (Instance instance, const Win32SurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceWin32PresentationSupportKHR = Bool32 (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
using PFN_CreateXlibSurfaceKHR = Result (*) (Instance instance, const XlibSurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceXlibPresentationSupportKHR = Bool32 (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID);
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
using PFN_CreateXcbSurfaceKHR = Result (*) (Instance instance, const XcbSurfaceCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceXcbPresentationSupportKHR = Bool32 (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id);
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
using PFN_CreateDirectFBSurfaceEXT = Result (*) (Instance instance, const DirectFBSurfaceCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceDirectFBPresentationSupportEXT = Bool32 (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb);
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
using PFN_CreateImagePipeSurfaceFUCHSIA = Result (*) (Instance instance, const ImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
using PFN_CreateStreamDescriptorSurfaceGGP = Result (*) (Instance instance, const StreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_GGP)
using PFN_CreateDebugReportCallbackEXT = Result (*) (Instance instance, const DebugReportCallbackCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, DebugReportCallbackEXT* pCallback);
using PFN_DestroyDebugReportCallbackEXT = void (*) (Instance instance, DebugReportCallbackEXT callback, const AllocationCallbacks* pAllocator);
using PFN_DebugReportMessageEXT = void (*) (Instance instance, DebugReportFlagsEXT flags, DebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage);
using PFN_DebugMarkerSetObjectNameEXT = Result (*) (Device device, const DebugMarkerObjectNameInfoEXT* pNameInfo);
using PFN_DebugMarkerSetObjectTagEXT = Result (*) (Device device, const DebugMarkerObjectTagInfoEXT* pTagInfo);
using PFN_CmdDebugMarkerBeginEXT = void (*) (CommandBuffer commandBuffer, const DebugMarkerMarkerInfoEXT* pMarkerInfo);
using PFN_CmdDebugMarkerEndEXT = void (*) (CommandBuffer commandBuffer);
using PFN_CmdDebugMarkerInsertEXT = void (*) (CommandBuffer commandBuffer, const DebugMarkerMarkerInfoEXT* pMarkerInfo);
using PFN_GetPhysicalDeviceExternalImageFormatPropertiesNV = Result (*) (PhysicalDevice physicalDevice, Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags, ExternalMemoryHandleTypeFlagsNV externalHandleType, ExternalImageFormatPropertiesNV* pExternalImageFormatProperties);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetMemoryWin32HandleNV = Result (*) (Device device, DeviceMemory memory, ExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_CmdExecuteGeneratedCommandsNV = void (*) (CommandBuffer commandBuffer, Bool32 isPreprocessed, const GeneratedCommandsInfoNV* pGeneratedCommandsInfo);
using PFN_CmdPreprocessGeneratedCommandsNV = void (*) (CommandBuffer commandBuffer, const GeneratedCommandsInfoNV* pGeneratedCommandsInfo);
using PFN_CmdBindPipelineShaderGroupNV = void (*) (CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, Pipeline pipeline, uint32_t groupIndex);
using PFN_GetGeneratedCommandsMemoryRequirementsNV = void (*) (Device device, const GeneratedCommandsMemoryRequirementsInfoNV* pInfo, MemoryRequirements2* pMemoryRequirements);
using PFN_CreateIndirectCommandsLayoutNV = Result (*) (Device device, const IndirectCommandsLayoutCreateInfoNV* pCreateInfo, const AllocationCallbacks* pAllocator, IndirectCommandsLayoutNV* pIndirectCommandsLayout);
using PFN_DestroyIndirectCommandsLayoutNV = void (*) (Device device, IndirectCommandsLayoutNV indirectCommandsLayout, const AllocationCallbacks* pAllocator);
using PFN_GetPhysicalDeviceFeatures2 = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceFeatures2* pFeatures);
using PFN_GetPhysicalDeviceFeatures2KHR = PFN_GetPhysicalDeviceFeatures2;
using PFN_GetPhysicalDeviceProperties2 = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceProperties2* pProperties);
using PFN_GetPhysicalDeviceProperties2KHR = PFN_GetPhysicalDeviceProperties2;
using PFN_GetPhysicalDeviceFormatProperties2 = void (*) (PhysicalDevice physicalDevice, Format format, FormatProperties2* pFormatProperties);
using PFN_GetPhysicalDeviceFormatProperties2KHR = PFN_GetPhysicalDeviceFormatProperties2;
using PFN_GetPhysicalDeviceImageFormatProperties2 = Result (*) (PhysicalDevice physicalDevice, const PhysicalDeviceImageFormatInfo2* pImageFormatInfo, ImageFormatProperties2* pImageFormatProperties);
using PFN_GetPhysicalDeviceImageFormatProperties2KHR = PFN_GetPhysicalDeviceImageFormatProperties2;
using PFN_GetPhysicalDeviceQueueFamilyProperties2 = void (*) (PhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, QueueFamilyProperties2* pQueueFamilyProperties);
using PFN_GetPhysicalDeviceQueueFamilyProperties2KHR = PFN_GetPhysicalDeviceQueueFamilyProperties2;
using PFN_GetPhysicalDeviceMemoryProperties2 = void (*) (PhysicalDevice physicalDevice, PhysicalDeviceMemoryProperties2* pMemoryProperties);
using PFN_GetPhysicalDeviceMemoryProperties2KHR = PFN_GetPhysicalDeviceMemoryProperties2;
using PFN_GetPhysicalDeviceSparseImageFormatProperties2 = void (*) (PhysicalDevice physicalDevice, const PhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, SparseImageFormatProperties2* pProperties);
using PFN_GetPhysicalDeviceSparseImageFormatProperties2KHR = PFN_GetPhysicalDeviceSparseImageFormatProperties2;
using PFN_CmdPushDescriptorSetKHR = void (*) (CommandBuffer commandBuffer, PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const WriteDescriptorSet* pDescriptorWrites);
using PFN_TrimCommandPool = void (*) (Device device, CommandPool commandPool, CommandPoolTrimFlags flags);
using PFN_TrimCommandPoolKHR = PFN_TrimCommandPool;
using PFN_GetPhysicalDeviceExternalBufferProperties = void (*) (PhysicalDevice physicalDevice, const PhysicalDeviceExternalBufferInfo* pExternalBufferInfo, ExternalBufferProperties* pExternalBufferProperties);
using PFN_GetPhysicalDeviceExternalBufferPropertiesKHR = PFN_GetPhysicalDeviceExternalBufferProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetMemoryWin32HandleKHR = Result (*) (Device device, const MemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
using PFN_GetMemoryWin32HandlePropertiesKHR = Result (*) (Device device, ExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, MemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetMemoryFdKHR = Result (*) (Device device, const MemoryGetFdInfoKHR* pGetFdInfo, int* pFd);
using PFN_GetMemoryFdPropertiesKHR = Result (*) (Device device, ExternalMemoryHandleTypeFlagBits handleType, int fd, MemoryFdPropertiesKHR* pMemoryFdProperties);
using PFN_GetPhysicalDeviceExternalSemaphoreProperties = void (*) (PhysicalDevice physicalDevice, const PhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, ExternalSemaphoreProperties* pExternalSemaphoreProperties);
using PFN_GetPhysicalDeviceExternalSemaphorePropertiesKHR = PFN_GetPhysicalDeviceExternalSemaphoreProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetSemaphoreWin32HandleKHR = Result (*) (Device device, const SemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
using PFN_ImportSemaphoreWin32HandleKHR = Result (*) (Device device, const ImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetSemaphoreFdKHR = Result (*) (Device device, const SemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd);
using PFN_ImportSemaphoreFdKHR = Result (*) (Device device, const ImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo);
using PFN_GetPhysicalDeviceExternalFenceProperties = void (*) (PhysicalDevice physicalDevice, const PhysicalDeviceExternalFenceInfo* pExternalFenceInfo, ExternalFenceProperties* pExternalFenceProperties);
using PFN_GetPhysicalDeviceExternalFencePropertiesKHR = PFN_GetPhysicalDeviceExternalFenceProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetFenceWin32HandleKHR = Result (*) (Device device, const FenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle);
using PFN_ImportFenceWin32HandleKHR = Result (*) (Device device, const ImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetFenceFdKHR = Result (*) (Device device, const FenceGetFdInfoKHR* pGetFdInfo, int* pFd);
using PFN_ImportFenceFdKHR = Result (*) (Device device, const ImportFenceFdInfoKHR* pImportFenceFdInfo);
using PFN_ReleaseDisplayEXT = Result (*) (PhysicalDevice physicalDevice, DisplayKHR display);
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
using PFN_AcquireXlibDisplayEXT = Result (*) (PhysicalDevice physicalDevice, Display* dpy, DisplayKHR display);
using PFN_GetRandROutputDisplayEXT = Result (*) (PhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, DisplayKHR* pDisplay);
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
using PFN_DisplayPowerControlEXT = Result (*) (Device device, DisplayKHR display, const DisplayPowerInfoEXT* pDisplayPowerInfo);
using PFN_RegisterDeviceEventEXT = Result (*) (Device device, const DeviceEventInfoEXT* pDeviceEventInfo, const AllocationCallbacks* pAllocator, Fence* pFence);
using PFN_RegisterDisplayEventEXT = Result (*) (Device device, DisplayKHR display, const DisplayEventInfoEXT* pDisplayEventInfo, const AllocationCallbacks* pAllocator, Fence* pFence);
using PFN_GetSwapchainCounterEXT = Result (*) (Device device, SwapchainKHR swapchain, SurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue);
using PFN_GetPhysicalDeviceSurfaceCapabilities2EXT = Result (*) (PhysicalDevice physicalDevice, SurfaceKHR surface, SurfaceCapabilities2EXT* pSurfaceCapabilities);
using PFN_EnumeratePhysicalDeviceGroups = Result (*) (Instance instance, uint32_t* pPhysicalDeviceGroupCount, PhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
using PFN_EnumeratePhysicalDeviceGroupsKHR = PFN_EnumeratePhysicalDeviceGroups;
using PFN_GetDeviceGroupPeerMemoryFeatures = void (*) (Device device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, PeerMemoryFeatureFlags* pPeerMemoryFeatures);
using PFN_GetDeviceGroupPeerMemoryFeaturesKHR = PFN_GetDeviceGroupPeerMemoryFeatures;
using PFN_BindBufferMemory2 = Result (*) (Device device, uint32_t bindInfoCount, const BindBufferMemoryInfo* pBindInfos);
using PFN_BindBufferMemory2KHR = PFN_BindBufferMemory2;
using PFN_BindImageMemory2 = Result (*) (Device device, uint32_t bindInfoCount, const BindImageMemoryInfo* pBindInfos);
using PFN_BindImageMemory2KHR = PFN_BindImageMemory2;
using PFN_CmdSetDeviceMask = void (*) (CommandBuffer commandBuffer, uint32_t deviceMask);
using PFN_CmdSetDeviceMaskKHR = PFN_CmdSetDeviceMask;
using PFN_GetDeviceGroupPresentCapabilitiesKHR = Result (*) (Device device, DeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities);
using PFN_GetDeviceGroupSurfacePresentModesKHR = Result (*) (Device device, SurfaceKHR surface, DeviceGroupPresentModeFlagsKHR* pModes);
using PFN_AcquireNextImage2KHR = Result (*) (Device device, const AcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex);
using PFN_CmdDispatchBase = void (*) (CommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
using PFN_CmdDispatchBaseKHR = PFN_CmdDispatchBase;
using PFN_GetPhysicalDevicePresentRectanglesKHR = Result (*) (PhysicalDevice physicalDevice, SurfaceKHR surface, uint32_t* pRectCount, Rect2D* pRects);
using PFN_CreateDescriptorUpdateTemplate = Result (*) (Device device, const DescriptorUpdateTemplateCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, DescriptorUpdateTemplate* pDescriptorUpdateTemplate);
using PFN_CreateDescriptorUpdateTemplateKHR = PFN_CreateDescriptorUpdateTemplate;
using PFN_DestroyDescriptorUpdateTemplate = void (*) (Device device, DescriptorUpdateTemplate descriptorUpdateTemplate, const AllocationCallbacks* pAllocator);
using PFN_DestroyDescriptorUpdateTemplateKHR = PFN_DestroyDescriptorUpdateTemplate;
using PFN_UpdateDescriptorSetWithTemplate = void (*) (Device device, DescriptorSet descriptorSet, DescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData);
using PFN_UpdateDescriptorSetWithTemplateKHR = PFN_UpdateDescriptorSetWithTemplate;
using PFN_CmdPushDescriptorSetWithTemplateKHR = void (*) (CommandBuffer commandBuffer, DescriptorUpdateTemplate descriptorUpdateTemplate, PipelineLayout layout, uint32_t set, const void* pData);
using PFN_SetHdrMetadataEXT = void (*) (Device device, uint32_t swapchainCount, const SwapchainKHR* pSwapchains, const HdrMetadataEXT* pMetadata);
using PFN_GetSwapchainStatusKHR = Result (*) (Device device, SwapchainKHR swapchain);
using PFN_GetRefreshCycleDurationGOOGLE = Result (*) (Device device, SwapchainKHR swapchain, RefreshCycleDurationGOOGLE* pDisplayTimingProperties);
using PFN_GetPastPresentationTimingGOOGLE = Result (*) (Device device, SwapchainKHR swapchain, uint32_t* pPresentationTimingCount, PastPresentationTimingGOOGLE* pPresentationTimings);
#if defined(VK_USE_PLATFORM_IOS_MVK)
using PFN_CreateIOSSurfaceMVK = Result (*) (Instance instance, const IOSSurfaceCreateInfoMVK* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
using PFN_CreateMacOSSurfaceMVK = Result (*) (Instance instance, const MacOSSurfaceCreateInfoMVK* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
using PFN_CreateMetalSurfaceEXT = Result (*) (Instance instance, const MetalSurfaceCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
using PFN_CmdSetViewportWScalingNV = void (*) (CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const ViewportWScalingNV* pViewportWScalings);
using PFN_CmdSetDiscardRectangleEXT = void (*) (CommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const Rect2D* pDiscardRectangles);
using PFN_CmdSetSampleLocationsEXT = void (*) (CommandBuffer commandBuffer, const SampleLocationsInfoEXT* pSampleLocationsInfo);
using PFN_GetPhysicalDeviceMultisamplePropertiesEXT = void (*) (PhysicalDevice physicalDevice, SampleCountFlagBits samples, MultisamplePropertiesEXT* pMultisampleProperties);
using PFN_GetPhysicalDeviceSurfaceCapabilities2KHR = Result (*) (PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, SurfaceCapabilities2KHR* pSurfaceCapabilities);
using PFN_GetPhysicalDeviceSurfaceFormats2KHR = Result (*) (PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, SurfaceFormat2KHR* pSurfaceFormats);
using PFN_GetPhysicalDeviceDisplayProperties2KHR = Result (*) (PhysicalDevice physicalDevice, uint32_t* pPropertyCount, DisplayProperties2KHR* pProperties);
using PFN_GetPhysicalDeviceDisplayPlaneProperties2KHR = Result (*) (PhysicalDevice physicalDevice, uint32_t* pPropertyCount, DisplayPlaneProperties2KHR* pProperties);
using PFN_GetDisplayModeProperties2KHR = Result (*) (PhysicalDevice physicalDevice, DisplayKHR display, uint32_t* pPropertyCount, DisplayModeProperties2KHR* pProperties);
using PFN_GetDisplayPlaneCapabilities2KHR = Result (*) (PhysicalDevice physicalDevice, const DisplayPlaneInfo2KHR* pDisplayPlaneInfo, DisplayPlaneCapabilities2KHR* pCapabilities);
using PFN_GetBufferMemoryRequirements2 = void (*) (Device device, const BufferMemoryRequirementsInfo2* pInfo, MemoryRequirements2* pMemoryRequirements);
using PFN_GetBufferMemoryRequirements2KHR = PFN_GetBufferMemoryRequirements2;
using PFN_GetImageMemoryRequirements2 = void (*) (Device device, const ImageMemoryRequirementsInfo2* pInfo, MemoryRequirements2* pMemoryRequirements);
using PFN_GetImageMemoryRequirements2KHR = PFN_GetImageMemoryRequirements2;
using PFN_GetImageSparseMemoryRequirements2 = void (*) (Device device, const ImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, SparseImageMemoryRequirements2* pSparseMemoryRequirements);
using PFN_GetImageSparseMemoryRequirements2KHR = PFN_GetImageSparseMemoryRequirements2;
using PFN_CreateSamplerYcbcrConversion = Result (*) (Device device, const SamplerYcbcrConversionCreateInfo* pCreateInfo, const AllocationCallbacks* pAllocator, SamplerYcbcrConversion* pYcbcrConversion);
using PFN_CreateSamplerYcbcrConversionKHR = PFN_CreateSamplerYcbcrConversion;
using PFN_DestroySamplerYcbcrConversion = void (*) (Device device, SamplerYcbcrConversion ycbcrConversion, const AllocationCallbacks* pAllocator);
using PFN_DestroySamplerYcbcrConversionKHR = PFN_DestroySamplerYcbcrConversion;
using PFN_GetDeviceQueue2 = void (*) (Device device, const DeviceQueueInfo2* pQueueInfo, Queue* pQueue);
using PFN_CreateValidationCacheEXT = Result (*) (Device device, const ValidationCacheCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, ValidationCacheEXT* pValidationCache);
using PFN_DestroyValidationCacheEXT = void (*) (Device device, ValidationCacheEXT validationCache, const AllocationCallbacks* pAllocator);
using PFN_GetValidationCacheDataEXT = Result (*) (Device device, ValidationCacheEXT validationCache, size_t* pDataSize, void* pData);
using PFN_MergeValidationCachesEXT = Result (*) (Device device, ValidationCacheEXT dstCache, uint32_t srcCacheCount, const ValidationCacheEXT* pSrcCaches);
using PFN_GetDescriptorSetLayoutSupport = void (*) (Device device, const DescriptorSetLayoutCreateInfo* pCreateInfo, DescriptorSetLayoutSupport* pSupport);
using PFN_GetDescriptorSetLayoutSupportKHR = PFN_GetDescriptorSetLayoutSupport;
using PFN_GetShaderInfoAMD = Result (*) (Device device, Pipeline pipeline, ShaderStageFlagBits shaderStage, ShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo);
using PFN_SetLocalDimmingAMD = void (*) (Device device, SwapchainKHR swapChain, Bool32 localDimmingEnable);
using PFN_GetPhysicalDeviceCalibrateableTimeDomainsEXT = Result (*) (PhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, TimeDomainEXT* pTimeDomains);
using PFN_GetCalibratedTimestampsEXT = Result (*) (Device device, uint32_t timestampCount, const CalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation);
using PFN_SetDebugUtilsObjectNameEXT = Result (*) (Device device, const DebugUtilsObjectNameInfoEXT* pNameInfo);
using PFN_SetDebugUtilsObjectTagEXT = Result (*) (Device device, const DebugUtilsObjectTagInfoEXT* pTagInfo);
using PFN_QueueBeginDebugUtilsLabelEXT = void (*) (Queue queue, const DebugUtilsLabelEXT* pLabelInfo);
using PFN_QueueEndDebugUtilsLabelEXT = void (*) (Queue queue);
using PFN_QueueInsertDebugUtilsLabelEXT = void (*) (Queue queue, const DebugUtilsLabelEXT* pLabelInfo);
using PFN_CmdBeginDebugUtilsLabelEXT = void (*) (CommandBuffer commandBuffer, const DebugUtilsLabelEXT* pLabelInfo);
using PFN_CmdEndDebugUtilsLabelEXT = void (*) (CommandBuffer commandBuffer);
using PFN_CmdInsertDebugUtilsLabelEXT = void (*) (CommandBuffer commandBuffer, const DebugUtilsLabelEXT* pLabelInfo);
using PFN_CreateDebugUtilsMessengerEXT = Result (*) (Instance instance, const DebugUtilsMessengerCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, DebugUtilsMessengerEXT* pMessenger);
using PFN_DestroyDebugUtilsMessengerEXT = void (*) (Instance instance, DebugUtilsMessengerEXT messenger, const AllocationCallbacks* pAllocator);
using PFN_SubmitDebugUtilsMessageEXT = void (*) (Instance instance, DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, DebugUtilsMessageTypeFlagsEXT messageTypes, const DebugUtilsMessengerCallbackDataEXT* pCallbackData);
using PFN_GetMemoryHostPointerPropertiesEXT = Result (*) (Device device, ExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, MemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties);
using PFN_CmdWriteBufferMarkerAMD = void (*) (CommandBuffer commandBuffer, PipelineStageFlagBits pipelineStage, Buffer dstBuffer, DeviceSize dstOffset, uint32_t marker);
using PFN_CreateRenderPass2 = Result (*) (Device device, const RenderPassCreateInfo2* pCreateInfo, const AllocationCallbacks* pAllocator, RenderPass* pRenderPass);
using PFN_CreateRenderPass2KHR = PFN_CreateRenderPass2;
using PFN_CmdBeginRenderPass2 = void (*) (CommandBuffer commandBuffer, const RenderPassBeginInfo* pRenderPassBegin, const SubpassBeginInfo* pSubpassBeginInfo);
using PFN_CmdBeginRenderPass2KHR = PFN_CmdBeginRenderPass2;
using PFN_CmdNextSubpass2 = void (*) (CommandBuffer commandBuffer, const SubpassBeginInfo* pSubpassBeginInfo, const SubpassEndInfo* pSubpassEndInfo);
using PFN_CmdNextSubpass2KHR = PFN_CmdNextSubpass2;
using PFN_CmdEndRenderPass2 = void (*) (CommandBuffer commandBuffer, const SubpassEndInfo* pSubpassEndInfo);
using PFN_CmdEndRenderPass2KHR = PFN_CmdEndRenderPass2;
using PFN_GetSemaphoreCounterValue = Result (*) (Device device, Semaphore semaphore, uint64_t* pValue);
using PFN_GetSemaphoreCounterValueKHR = PFN_GetSemaphoreCounterValue;
using PFN_WaitSemaphores = Result (*) (Device device, const SemaphoreWaitInfo* pWaitInfo, uint64_t timeout);
using PFN_WaitSemaphoresKHR = PFN_WaitSemaphores;
using PFN_SignalSemaphore = Result (*) (Device device, const SemaphoreSignalInfo* pSignalInfo);
using PFN_SignalSemaphoreKHR = PFN_SignalSemaphore;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_GetAndroidHardwareBufferPropertiesANDROID = Result (*) (Device device, const AHardwareBuffer* buffer, AndroidHardwareBufferPropertiesANDROID* pProperties);
using PFN_GetMemoryAndroidHardwareBufferANDROID = Result (*) (Device device, const MemoryGetAndroidHardwareBufferInfoANDROID* pInfo, AHardwareBuffer** pBuffer);
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
using PFN_CmdDrawIndirectCount = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
using PFN_CmdDrawIndirectCountKHR = PFN_CmdDrawIndirectCount;
using PFN_CmdDrawIndirectCountAMD = PFN_CmdDrawIndirectCount;
using PFN_CmdDrawIndexedIndirectCount = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
using PFN_CmdDrawIndexedIndirectCountKHR = PFN_CmdDrawIndexedIndirectCount;
using PFN_CmdDrawIndexedIndirectCountAMD = PFN_CmdDrawIndexedIndirectCount;
using PFN_CmdSetCheckpointNV = void (*) (CommandBuffer commandBuffer, const void* pCheckpointMarker);
using PFN_GetQueueCheckpointDataNV = void (*) (Queue queue, uint32_t* pCheckpointDataCount, CheckpointDataNV* pCheckpointData);
using PFN_CmdBindTransformFeedbackBuffersEXT = void (*) (CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes);
using PFN_CmdBeginTransformFeedbackEXT = void (*) (CommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets);
using PFN_CmdEndTransformFeedbackEXT = void (*) (CommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const Buffer* pCounterBuffers, const DeviceSize* pCounterBufferOffsets);
using PFN_CmdBeginQueryIndexedEXT = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, QueryControlFlags flags, uint32_t index);
using PFN_CmdEndQueryIndexedEXT = void (*) (CommandBuffer commandBuffer, QueryPool queryPool, uint32_t query, uint32_t index);
using PFN_CmdDrawIndirectByteCountEXT = void (*) (CommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, Buffer counterBuffer, DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride);
using PFN_CmdSetExclusiveScissorNV = void (*) (CommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const Rect2D* pExclusiveScissors);
using PFN_CmdBindShadingRateImageNV = void (*) (CommandBuffer commandBuffer, ImageView imageView, ImageLayout imageLayout);
using PFN_CmdSetViewportShadingRatePaletteNV = void (*) (CommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const ShadingRatePaletteNV* pShadingRatePalettes);
using PFN_CmdSetCoarseSampleOrderNV = void (*) (CommandBuffer commandBuffer, CoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const CoarseSampleOrderCustomNV* pCustomSampleOrders);
using PFN_CmdDrawMeshTasksNV = void (*) (CommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask);
using PFN_CmdDrawMeshTasksIndirectNV = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride);
using PFN_CmdDrawMeshTasksIndirectCountNV = void (*) (CommandBuffer commandBuffer, Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
using PFN_CompileDeferredNV = Result (*) (Device device, Pipeline pipeline, uint32_t shader);
using PFN_CreateAccelerationStructureNV = Result (*) (Device device, const AccelerationStructureCreateInfoNV* pCreateInfo, const AllocationCallbacks* pAllocator, AccelerationStructureNV* pAccelerationStructure);
using PFN_DestroyAccelerationStructureKHR = void (*) (Device device, AccelerationStructureKHR accelerationStructure, const AllocationCallbacks* pAllocator);
using PFN_DestroyAccelerationStructureNV = void (*) (Device device, AccelerationStructureNV accelerationStructure, const AllocationCallbacks* pAllocator);
using PFN_GetAccelerationStructureMemoryRequirementsNV = void (*) (Device device, const AccelerationStructureMemoryRequirementsInfoNV* pInfo, MemoryRequirements2KHR* pMemoryRequirements);
using PFN_BindAccelerationStructureMemoryNV = Result (*) (Device device, uint32_t bindInfoCount, const BindAccelerationStructureMemoryInfoNV* pBindInfos);
using PFN_CmdCopyAccelerationStructureNV = void (*) (CommandBuffer commandBuffer, AccelerationStructureNV dst, AccelerationStructureNV src, CopyAccelerationStructureModeKHR mode);
using PFN_CmdCopyAccelerationStructureKHR = void (*) (CommandBuffer commandBuffer, const CopyAccelerationStructureInfoKHR* pInfo);
using PFN_CopyAccelerationStructureKHR = Result (*) (Device device, DeferredOperationKHR deferredOperation, const CopyAccelerationStructureInfoKHR* pInfo);
using PFN_CmdCopyAccelerationStructureToMemoryKHR = void (*) (CommandBuffer commandBuffer, const CopyAccelerationStructureToMemoryInfoKHR* pInfo);
using PFN_CopyAccelerationStructureToMemoryKHR = Result (*) (Device device, DeferredOperationKHR deferredOperation, const CopyAccelerationStructureToMemoryInfoKHR* pInfo);
using PFN_CmdCopyMemoryToAccelerationStructureKHR = void (*) (CommandBuffer commandBuffer, const CopyMemoryToAccelerationStructureInfoKHR* pInfo);
using PFN_CopyMemoryToAccelerationStructureKHR = Result (*) (Device device, DeferredOperationKHR deferredOperation, const CopyMemoryToAccelerationStructureInfoKHR* pInfo);
using PFN_CmdWriteAccelerationStructuresPropertiesKHR = void (*) (CommandBuffer commandBuffer, uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery);
using PFN_CmdWriteAccelerationStructuresPropertiesNV = void (*) (CommandBuffer commandBuffer, uint32_t accelerationStructureCount, const AccelerationStructureNV* pAccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery);
using PFN_CmdBuildAccelerationStructureNV = void (*) (CommandBuffer commandBuffer, const AccelerationStructureInfoNV* pInfo, Buffer instanceData, DeviceSize instanceOffset, Bool32 update, AccelerationStructureNV dst, AccelerationStructureNV src, Buffer scratch, DeviceSize scratchOffset);
using PFN_WriteAccelerationStructuresPropertiesKHR = Result (*) (Device device, uint32_t accelerationStructureCount, const AccelerationStructureKHR* pAccelerationStructures, QueryType queryType, size_t dataSize, void* pData, size_t stride);
using PFN_CmdTraceRaysKHR = void (*) (CommandBuffer commandBuffer, const StridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const StridedDeviceAddressRegionKHR* pMissShaderBindingTable, const StridedDeviceAddressRegionKHR* pHitShaderBindingTable, const StridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth);
using PFN_CmdTraceRaysNV = void (*) (CommandBuffer commandBuffer, Buffer raygenShaderBindingTableBuffer, DeviceSize raygenShaderBindingOffset, Buffer missShaderBindingTableBuffer, DeviceSize missShaderBindingOffset, DeviceSize missShaderBindingStride, Buffer hitShaderBindingTableBuffer, DeviceSize hitShaderBindingOffset, DeviceSize hitShaderBindingStride, Buffer callableShaderBindingTableBuffer, DeviceSize callableShaderBindingOffset, DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
using PFN_GetRayTracingShaderGroupHandlesKHR = Result (*) (Device device, Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
using PFN_GetRayTracingShaderGroupHandlesNV = PFN_GetRayTracingShaderGroupHandlesKHR;
using PFN_GetRayTracingCaptureReplayShaderGroupHandlesKHR = Result (*) (Device device, Pipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData);
using PFN_GetAccelerationStructureHandleNV = Result (*) (Device device, AccelerationStructureNV accelerationStructure, size_t dataSize, void* pData);
using PFN_CreateRayTracingPipelinesNV = Result (*) (Device device, PipelineCache pipelineCache, uint32_t createInfoCount, const RayTracingPipelineCreateInfoNV* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines);
using PFN_CreateRayTracingPipelinesKHR = Result (*) (Device device, DeferredOperationKHR deferredOperation, PipelineCache pipelineCache, uint32_t createInfoCount, const RayTracingPipelineCreateInfoKHR* pCreateInfos, const AllocationCallbacks* pAllocator, Pipeline* pPipelines);
using PFN_GetPhysicalDeviceCooperativeMatrixPropertiesNV = Result (*) (PhysicalDevice physicalDevice, uint32_t* pPropertyCount, CooperativeMatrixPropertiesNV* pProperties);
using PFN_CmdTraceRaysIndirectKHR = void (*) (CommandBuffer commandBuffer, const StridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const StridedDeviceAddressRegionKHR* pMissShaderBindingTable, const StridedDeviceAddressRegionKHR* pHitShaderBindingTable, const StridedDeviceAddressRegionKHR* pCallableShaderBindingTable, DeviceAddress indirectDeviceAddress);
using PFN_GetDeviceAccelerationStructureCompatibilityKHR = void (*) (Device device, const AccelerationStructureVersionInfoKHR* pVersionInfo, AccelerationStructureCompatibilityKHR* pCompatibility);
using PFN_GetRayTracingShaderGroupStackSizeKHR = DeviceSize (*) (Device device, Pipeline pipeline, uint32_t group, ShaderGroupShaderKHR groupShader);
using PFN_CmdSetRayTracingPipelineStackSizeKHR = void (*) (CommandBuffer commandBuffer, uint32_t pipelineStackSize);
using PFN_GetImageViewHandleNVX = uint32_t (*) (Device device, const ImageViewHandleInfoNVX* pInfo);
using PFN_GetImageViewAddressNVX = Result (*) (Device device, ImageView imageView, ImageViewAddressPropertiesNVX* pProperties);
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_GetPhysicalDeviceSurfacePresentModes2EXT = Result (*) (PhysicalDevice physicalDevice, const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, PresentModeKHR* pPresentModes);
using PFN_GetDeviceGroupSurfacePresentModes2EXT = Result (*) (Device device, const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, DeviceGroupPresentModeFlagsKHR* pModes);
using PFN_AcquireFullScreenExclusiveModeEXT = Result (*) (Device device, SwapchainKHR swapchain);
using PFN_ReleaseFullScreenExclusiveModeEXT = Result (*) (Device device, SwapchainKHR swapchain);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, PerformanceCounterKHR* pCounters, PerformanceCounterDescriptionKHR* pCounterDescriptions);
using PFN_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = void (*) (PhysicalDevice physicalDevice, const QueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses);
using PFN_AcquireProfilingLockKHR = Result (*) (Device device, const AcquireProfilingLockInfoKHR* pInfo);
using PFN_ReleaseProfilingLockKHR = void (*) (Device device);
using PFN_GetImageDrmFormatModifierPropertiesEXT = Result (*) (Device device, Image image, ImageDrmFormatModifierPropertiesEXT* pProperties);
using PFN_GetBufferOpaqueCaptureAddress = uint64_t (*) (Device device, const BufferDeviceAddressInfo* pInfo);
using PFN_GetBufferOpaqueCaptureAddressKHR = PFN_GetBufferOpaqueCaptureAddress;
using PFN_GetBufferDeviceAddress = DeviceAddress (*) (Device device, const BufferDeviceAddressInfo* pInfo);
using PFN_GetBufferDeviceAddressKHR = PFN_GetBufferDeviceAddress;
using PFN_GetBufferDeviceAddressEXT = PFN_GetBufferDeviceAddress;
using PFN_CreateHeadlessSurfaceEXT = Result (*) (Instance instance, const HeadlessSurfaceCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, SurfaceKHR* pSurface);
using PFN_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = Result (*) (PhysicalDevice physicalDevice, uint32_t* pCombinationCount, FramebufferMixedSamplesCombinationNV* pCombinations);
using PFN_InitializePerformanceApiINTEL = Result (*) (Device device, const InitializePerformanceApiInfoINTEL* pInitializeInfo);
using PFN_UninitializePerformanceApiINTEL = void (*) (Device device);
using PFN_CmdSetPerformanceMarkerINTEL = Result (*) (CommandBuffer commandBuffer, const PerformanceMarkerInfoINTEL* pMarkerInfo);
using PFN_CmdSetPerformanceStreamMarkerINTEL = Result (*) (CommandBuffer commandBuffer, const PerformanceStreamMarkerInfoINTEL* pMarkerInfo);
using PFN_CmdSetPerformanceOverrideINTEL = Result (*) (CommandBuffer commandBuffer, const PerformanceOverrideInfoINTEL* pOverrideInfo);
using PFN_AcquirePerformanceConfigurationINTEL = Result (*) (Device device, const PerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, PerformanceConfigurationINTEL* pConfiguration);
using PFN_ReleasePerformanceConfigurationINTEL = Result (*) (Device device, PerformanceConfigurationINTEL configuration);
using PFN_QueueSetPerformanceConfigurationINTEL = Result (*) (Queue queue, PerformanceConfigurationINTEL configuration);
using PFN_GetPerformanceParameterINTEL = Result (*) (Device device, PerformanceParameterTypeINTEL parameter, PerformanceValueINTEL* pValue);
using PFN_GetDeviceMemoryOpaqueCaptureAddress = uint64_t (*) (Device device, const DeviceMemoryOpaqueCaptureAddressInfo* pInfo);
using PFN_GetDeviceMemoryOpaqueCaptureAddressKHR = PFN_GetDeviceMemoryOpaqueCaptureAddress;
using PFN_GetPipelineExecutablePropertiesKHR = Result (*) (Device device, const PipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, PipelineExecutablePropertiesKHR* pProperties);
using PFN_GetPipelineExecutableStatisticsKHR = Result (*) (Device device, const PipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, PipelineExecutableStatisticKHR* pStatistics);
using PFN_GetPipelineExecutableInternalRepresentationsKHR = Result (*) (Device device, const PipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, PipelineExecutableInternalRepresentationKHR* pInternalRepresentations);
using PFN_CmdSetLineStippleEXT = void (*) (CommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern);
using PFN_GetPhysicalDeviceToolPropertiesEXT = Result (*) (PhysicalDevice physicalDevice, uint32_t* pToolCount, PhysicalDeviceToolPropertiesEXT* pToolProperties);
using PFN_CreateAccelerationStructureKHR = Result (*) (Device device, const AccelerationStructureCreateInfoKHR* pCreateInfo, const AllocationCallbacks* pAllocator, AccelerationStructureKHR* pAccelerationStructure);
using PFN_CmdBuildAccelerationStructuresKHR = void (*) (CommandBuffer commandBuffer, uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
using PFN_CmdBuildAccelerationStructuresIndirectKHR = void (*) (CommandBuffer commandBuffer, uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const DeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts);
using PFN_BuildAccelerationStructuresKHR = Result (*) (Device device, DeferredOperationKHR deferredOperation, uint32_t infoCount, const AccelerationStructureBuildGeometryInfoKHR* pInfos, const AccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos);
using PFN_GetAccelerationStructureDeviceAddressKHR = DeviceAddress (*) (Device device, const AccelerationStructureDeviceAddressInfoKHR* pInfo);
using PFN_CreateDeferredOperationKHR = Result (*) (Device device, const AllocationCallbacks* pAllocator, DeferredOperationKHR* pDeferredOperation);
using PFN_DestroyDeferredOperationKHR = void (*) (Device device, DeferredOperationKHR operation, const AllocationCallbacks* pAllocator);
using PFN_GetDeferredOperationMaxConcurrencyKHR = uint32_t (*) (Device device, DeferredOperationKHR operation);
using PFN_GetDeferredOperationResultKHR = Result (*) (Device device, DeferredOperationKHR operation);
using PFN_DeferredOperationJoinKHR = Result (*) (Device device, DeferredOperationKHR operation);
using PFN_CmdSetCullModeEXT = void (*) (CommandBuffer commandBuffer, CullModeFlags cullMode);
using PFN_CmdSetFrontFaceEXT = void (*) (CommandBuffer commandBuffer, FrontFace frontFace);
using PFN_CmdSetPrimitiveTopologyEXT = void (*) (CommandBuffer commandBuffer, PrimitiveTopology primitiveTopology);
using PFN_CmdSetViewportWithCountEXT = void (*) (CommandBuffer commandBuffer, uint32_t viewportCount, const Viewport* pViewports);
using PFN_CmdSetScissorWithCountEXT = void (*) (CommandBuffer commandBuffer, uint32_t scissorCount, const Rect2D* pScissors);
using PFN_CmdBindVertexBuffers2EXT = void (*) (CommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const Buffer* pBuffers, const DeviceSize* pOffsets, const DeviceSize* pSizes, const DeviceSize* pStrides);
using PFN_CmdSetDepthTestEnableEXT = void (*) (CommandBuffer commandBuffer, Bool32 depthTestEnable);
using PFN_CmdSetDepthWriteEnableEXT = void (*) (CommandBuffer commandBuffer, Bool32 depthWriteEnable);
using PFN_CmdSetDepthCompareOpEXT = void (*) (CommandBuffer commandBuffer, CompareOp depthCompareOp);
using PFN_CmdSetDepthBoundsTestEnableEXT = void (*) (CommandBuffer commandBuffer, Bool32 depthBoundsTestEnable);
using PFN_CmdSetStencilTestEnableEXT = void (*) (CommandBuffer commandBuffer, Bool32 stencilTestEnable);
using PFN_CmdSetStencilOpEXT = void (*) (CommandBuffer commandBuffer, StencilFaceFlags faceMask, StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp);
using PFN_CreatePrivateDataSlotEXT = Result (*) (Device device, const PrivateDataSlotCreateInfoEXT* pCreateInfo, const AllocationCallbacks* pAllocator, PrivateDataSlotEXT* pPrivateDataSlot);
using PFN_DestroyPrivateDataSlotEXT = void (*) (Device device, PrivateDataSlotEXT privateDataSlot, const AllocationCallbacks* pAllocator);
using PFN_SetPrivateDataEXT = Result (*) (Device device, ObjectType objectType, uint64_t objectHandle, PrivateDataSlotEXT privateDataSlot, uint64_t data);
using PFN_GetPrivateDataEXT = void (*) (Device device, ObjectType objectType, uint64_t objectHandle, PrivateDataSlotEXT privateDataSlot, uint64_t* pData);
using PFN_CmdCopyBuffer2KHR = void (*) (CommandBuffer commandBuffer, const CopyBufferInfo2KHR* pCopyBufferInfo);
using PFN_CmdCopyImage2KHR = void (*) (CommandBuffer commandBuffer, const CopyImageInfo2KHR* pCopyImageInfo);
using PFN_CmdBlitImage2KHR = void (*) (CommandBuffer commandBuffer, const BlitImageInfo2KHR* pBlitImageInfo);
using PFN_CmdCopyBufferToImage2KHR = void (*) (CommandBuffer commandBuffer, const CopyBufferToImageInfo2KHR* pCopyBufferToImageInfo);
using PFN_CmdCopyImageToBuffer2KHR = void (*) (CommandBuffer commandBuffer, const CopyImageToBufferInfo2KHR* pCopyImageToBufferInfo);
using PFN_CmdResolveImage2KHR = void (*) (CommandBuffer commandBuffer, const ResolveImageInfo2KHR* pResolveImageInfo);
using PFN_CmdSetFragmentShadingRateKHR = void (*) (CommandBuffer commandBuffer, const Extent2D* pFragmentSize, const FragmentShadingRateCombinerOpKHR combinerOps[2]);
using PFN_GetPhysicalDeviceFragmentShadingRatesKHR = Result (*) (PhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, PhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates);
using PFN_CmdSetFragmentShadingRateEnumNV = void (*) (CommandBuffer commandBuffer, FragmentShadingRateNV shadingRate, const FragmentShadingRateCombinerOpKHR combinerOps[2]);
using PFN_GetAccelerationStructureBuildSizesKHR = void (*) (Device device, AccelerationStructureBuildTypeKHR buildType, const AccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, AccelerationStructureBuildSizesInfoKHR* pSizeInfo);
} //namespace detail

} // namespace vk 
#if !defined(VULKAN_CUSTOM_ASSERT)
#include <cassert>
#define VULKAN_CUSTOM_ASSERT assert
#endif

#if defined(_WIN32)
    typedef struct HINSTANCE__ * HINSTANCE;
    #if defined( _WIN64 )
    typedef int64_t( __stdcall * FARPROC )();
    #else
    typedef int( __stdcall * FARPROC )();
    #endif
    extern "C" __declspec( dllimport ) HINSTANCE __stdcall LoadLibraryA( char const * lpLibFileName );
    extern "C" __declspec( dllimport ) int __stdcall FreeLibrary( HINSTANCE hLibModule );
    extern "C" __declspec( dllimport ) FARPROC __stdcall GetProcAddress( HINSTANCE hModule, const char * lpProcName );
#elif defined(__linux__) || defined(__APPLE__)
    #include <dlfcn.h>
#endif
using PFN_vkVoidFunction = void (VKAPI_PTR *)(void);
using PFN_vkGetInstanceProcAddr = PFN_vkVoidFunction (VKAPI_PTR *)(VkInstance instance, const char* pName);
namespace vk {
class DynamicLibrary {
    public:
    // Used to enable RAII vk::DynamicLibrary behavior
    struct LoadAtConstruction {};

    explicit DynamicLibrary() noexcept {}
    explicit DynamicLibrary([[maybe_unused]] LoadAtConstruction load) noexcept {
        init();
    }
    explicit DynamicLibrary(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr) noexcept : 
        get_instance_proc_addr(pfn_vkGetInstanceProcAddr) { }
    ~DynamicLibrary() noexcept {
        close();
    }
    DynamicLibrary(DynamicLibrary const& other) = delete;
    DynamicLibrary& operator=(DynamicLibrary const& other) = delete;
    DynamicLibrary(DynamicLibrary && other) noexcept: library(other.library), get_instance_proc_addr(other.get_instance_proc_addr) {
        other.get_instance_proc_addr = 0;
        other.library = 0;
    }
    DynamicLibrary& operator=(DynamicLibrary && other) noexcept {
        if (this != &other)
        {
            close();
            library = other.library; 
            get_instance_proc_addr = other.get_instance_proc_addr;
            other.get_instance_proc_addr = 0;
            other.library = 0;
        }
        return *this;
    }

    vk::Result init(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr = nullptr) noexcept {
        if (pfn_vkGetInstanceProcAddr != nullptr) {
            get_instance_proc_addr = pfn_vkGetInstanceProcAddr;
            return vk::Result::Success;
        }
#if defined(__linux__)
        library = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
        if (!library) library = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
#elif defined(__APPLE__)
        library = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
#elif defined(_WIN32)
        library = ::LoadLibraryA("vulkan-1.dll");
#endif
        if (library == 0) return vk::Result::ErrorInitializationFailed;
        Load(get_instance_proc_addr, "vkGetInstanceProcAddr");
        if (get_instance_proc_addr == nullptr) return vk::Result::ErrorInitializationFailed;
        return vk::Result::Success;
    }
    void close() noexcept {
        if (library != nullptr) {
#if defined(__linux__) || defined(__APPLE__)
            dlclose(library);
#elif defined(_WIN32)
            ::FreeLibrary(library);
#endif
        library = 0;
        }
    }

    // Check if vulkan is loaded and ready for use
    [[nodiscard]] bool is_init() const noexcept { return get_instance_proc_addr != 0; }

    // Get `vkGetInstanceProcAddr` if it was loaded, 0 if not
    [[nodiscard]] PFN_vkGetInstanceProcAddr get() const noexcept {
        VULKAN_CUSTOM_ASSERT(get_instance_proc_addr != nullptr && "Must call init() before use");
        return get_instance_proc_addr;
    }

private:
    
    template <typename T>
    void Load(T &func_dest, const char *func_name) {
#if defined(__linux__) || defined(__APPLE__)
        func_dest = reinterpret_cast<T>(dlsym(library, func_name));
#elif defined(_WIN32)
        func_dest = reinterpret_cast<T>(::GetProcAddress(library, func_name));
#endif
    }

#if defined(__linux__) || defined(__APPLE__)
    void *library = nullptr;
#elif defined(_WIN32)
    ::HINSTANCE library = nullptr;
#endif

    PFN_vkGetInstanceProcAddr get_instance_proc_addr = nullptr;
    
};


namespace detail {
/* Array data structure where the length is determined at construction time.
 * Cannot resize, add, or delete elements from.
 * Used for returning a collection from the Vulkan API
 * Does not throw any exceptions
 */
template<typename T>
struct fixed_vector
{
    explicit fixed_vector() noexcept {}
    explicit fixed_vector(size_t count) noexcept
    {
        _count = count;
        _data = new (std::nothrow) T[count];
        for (size_t i = 0; i < count; i++)
            _data[i] = T(); // some vulkan structs have default values, so must be initialized
    }
    ~fixed_vector() noexcept { delete[] _data; }
    fixed_vector(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (size_t i = 0; i < value.count; i++)
            _data[i] = value[i];
    }
    fixed_vector& operator=(fixed_vector const& value) noexcept
    {
        _count = value._count;
        _data = new (std::nothrow) T[value.count];
        for (size_t i = 0; i < value.count; i++)
            _data[i] = value[i];
    }
    fixed_vector(fixed_vector&& other) noexcept
      : _count(std::exchange(other._count, 0))
      , _data(std::exchange(other._data, nullptr))
    {}
    fixed_vector& operator=(fixed_vector&& other) noexcept
    {
        if (this != &other) {
            delete _data;
            _count = std::exchange(other._count, 0);
            _data = std::exchange(other._data, nullptr);
        }
        return *this;
    }

    [[nodiscard]] size_t size() noexcept { return _count; }
    [[nodiscard]] size_t size() const noexcept { return _count; }
    [[nodiscard]] bool empty() noexcept { return _count == 0; }
    [[nodiscard]] bool empty() const noexcept { return _count == 0; }
    [[nodiscard]] T* data() noexcept { return _data; }
    [[nodiscard]] const T* data() const noexcept { return _data; }
    void shrink(size_t count) noexcept { if (count < _count) _count = count;}

    [[nodiscard]] T& operator[](size_t count) & noexcept { return _data[count]; }
    [[nodiscard]] T const& operator[](size_t count) const& noexcept { return _data[count]; }

    [[nodiscard]] const T* begin() const noexcept { return _data + 0; }
    [[nodiscard]] T* begin() noexcept { return _data + 0; }
    [[nodiscard]] const T* end() const noexcept { return _data + _count; }
    [[nodiscard]] T* end() noexcept { return _data + _count; }

  private:
    size_t _count = 0;
    T* _data = nullptr;
};
} // namespace detail



/* Return type for Vulkan Module API functions which return a value or values
 * Holds a T value or a vk::Result for indicating the error
 * Do not use with success codes other than zero
 * Example in function definition
 * vk::expected<vk::Buffer> CreateBuffer(const BufferCreateInfo& pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) { ... }
 * Example usage:
 * auto buffer_return  = CreateBuffer( ... );
 * if (!buffer_return)
 *     error_exit("Failed to create buffer", buffer_return.error());
 * vk::Buffer buffer = buffer_return.value(); //Get value now that we've check for errors
 */
template<typename T>
struct expected {
	explicit expected (T const& value, Result result) noexcept: _value{ value}, _result{ result } {}
	explicit expected (T&& value, Result result) noexcept: _value{ std::move(value) }, _result{ result } {}

    const T* operator-> () const noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return &_value; }
	T*       operator-> ()       noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return &_value; }
	const T& operator* () const& noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return _value; }
	T&       operator* () &      noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return _value; }
	T&&      operator* () &&	 noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return std::move (_value); }
	const T&  value () const&    noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return _value; }
	T&        value () &         noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return _value; }
	const T&& value () const&&   noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return std::move(_value); }
	T&&       value () &&        noexcept { VULKAN_CUSTOM_ASSERT (_result == Result::Success); return std::move(_value); }

    Result error() const noexcept { VULKAN_CUSTOM_ASSERT (_result != Result::Success); return _result; }
    Result raw_result() const noexcept { return _result; }

    bool has_value () const noexcept { return _result == Result::Success; }
	explicit operator bool () const noexcept { return _result == Result::Success; }
    bool operator!() const noexcept { return _result != Result::Success; }

    template <size_t N>
    auto const& get() const noexcept {
       if constexpr (N == 0) return _value;
       else if constexpr (N == 1) return _result;
    }
    template <size_t N>
    auto& get() noexcept {
       if constexpr (N == 0) return _value;
       else if constexpr (N == 1) return _result;
    }

private:
    T _value;
    Result _result = Result::Success;
};

} //namespace vk

namespace std {
    template<typename T>
    struct tuple_size<vk::expected<T>>: std::integral_constant<size_t, 2> {};
    template<typename T> struct tuple_element<0, vk::expected<T>> { using type = T; };
    template<typename T> struct tuple_element<1, vk::expected<T>> { using type = vk::Result; };
}

namespace vk {


namespace detail {
template<typename T>
class span {
public:
    constexpr span() noexcept = default;
    constexpr span(T const& value) noexcept : _data{&value}, _count{1} {}
    constexpr explicit span(T* data, uint32_t count) noexcept : _data{data}, _count{count} {}

    // requires std::data(Range const&)
    // requires std::size(Range const&)
    template <typename Range>
    explicit span(Range const& range) noexcept : 
        _data{std::data(range)}, _count{std::size(range)} {}
    
    template< std::size_t N >
    span(std::array<T, N>& arr ) noexcept : 
        _data{std::data(arr)}, _count{std::size(arr)} {}

    template< std::size_t N >
    span(std::array<T, N> const& arr ) noexcept : 
        _data{std::data(arr)}, _count{std::size(arr)} {}
    
    span( std::initializer_list<T>& data ) noexcept : 
        _data{data.begin()}, _count{static_cast<uint32_t>(data.size())} {}

    span( std::initializer_list<T> const& data ) noexcept : 
        _data{data.begin()}, _count{static_cast<uint32_t>(data.size())} {}

    template <typename A = T, typename std::enable_if<std::is_const<A>::value, int>::type = 0>
    span( std::initializer_list<typename std::remove_const<T>::type> const& data ) noexcept : 
        _data{data.begin()}, _count{static_cast<uint32_t>(data.size())} {}

    template <typename A = T, typename std::enable_if<std::is_const<A>::value, int>::type = 0>
    span( std::initializer_list<typename std::remove_const<T>::type> & data ) noexcept : 
        _data{data.begin()}, _count{static_cast<uint32_t>(data.size())} {}

    [[nodiscard]] uint32_t size() noexcept { return _count; }
    [[nodiscard]] uint32_t size() const noexcept { return _count; }
    [[nodiscard]] uint32_t size_bytes() const noexcept { return _count * sizeof(T); }

    [[nodiscard]] T* data() noexcept { return _data; }
    [[nodiscard]] const T* data() const noexcept { return _data; }
    [[nodiscard]] bool empty() noexcept { return _count == 0; }
    [[nodiscard]] bool empty() const noexcept { return _count == 0; }

    [[nodiscard]] T const& operator[](uint32_t count) & noexcept { return _data[count]; }
    [[nodiscard]] T const& operator[](uint32_t count) const& noexcept { return _data[count]; }

    [[nodiscard]] const T* begin() const noexcept { return _data + 0; }
    [[nodiscard]] const T* begin() noexcept { return _data + 0; }
    [[nodiscard]] const T* end() const noexcept { return _data + _count; }
    [[nodiscard]] const T* end() noexcept { return _data + _count; }
private:
    T* _data;
    uint32_t _count;
};
} // namespace detail


struct GlobalFunctions {
    detail::PFN_CreateInstance pfn_CreateInstance = nullptr;
    detail::PFN_GetInstanceProcAddr pfn_GetInstanceProcAddr = nullptr;
    detail::PFN_EnumerateInstanceExtensionProperties pfn_EnumerateInstanceExtensionProperties = nullptr;
    detail::PFN_EnumerateInstanceLayerProperties pfn_EnumerateInstanceLayerProperties = nullptr;
    detail::PFN_EnumerateInstanceVersion pfn_EnumerateInstanceVersion = nullptr;
[[nodiscard]] expected<Instance> CreateInstance(const InstanceCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Instance pInstance;
        Result result = pfn_CreateInstance(&pCreateInfo,
        pAllocator,
        &pInstance);
    return expected<Instance>(pInstance, result);
}
[[nodiscard]] PFN_VoidFunction GetInstanceProcAddr(Instance instance, 
    const char* pName) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetInstanceProcAddr(instance,
        pName);
}
[[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateInstanceExtensionProperties(const char* pLayerName = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_EnumerateInstanceExtensionProperties(pLayerName,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<ExtensionProperties>{}, result);
    detail::fixed_vector<ExtensionProperties> pProperties{pPropertyCount};
    result = pfn_EnumerateInstanceExtensionProperties(pLayerName,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<LayerProperties>> EnumerateInstanceLayerProperties() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_EnumerateInstanceLayerProperties(&pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<LayerProperties>{}, result);
    detail::fixed_vector<LayerProperties> pProperties{pPropertyCount};
    result = pfn_EnumerateInstanceLayerProperties(&pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<uint32_t> EnumerateInstanceVersion() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    if (pfn_EnumerateInstanceVersion == 0) return expected<uint32_t>(make_vk_version(1,0,0), Result::Success);
    uint32_t pApiVersion;
        Result result = pfn_EnumerateInstanceVersion(&pApiVersion);
    return expected<uint32_t>(pApiVersion, result);
}
GlobalFunctions() noexcept {}
explicit GlobalFunctions(DynamicLibrary const& library) noexcept {
    detail::PFN_GetInstanceProcAddr get_instance_proc_addr = reinterpret_cast<detail::PFN_GetInstanceProcAddr>(library.get());
    pfn_CreateInstance = reinterpret_cast<detail::PFN_CreateInstance>(get_instance_proc_addr(nullptr,"vkCreateInstance"));
    pfn_GetInstanceProcAddr = reinterpret_cast<detail::PFN_GetInstanceProcAddr>(get_instance_proc_addr(nullptr,"vkGetInstanceProcAddr"));
    pfn_EnumerateInstanceExtensionProperties = reinterpret_cast<detail::PFN_EnumerateInstanceExtensionProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceExtensionProperties"));
    pfn_EnumerateInstanceLayerProperties = reinterpret_cast<detail::PFN_EnumerateInstanceLayerProperties>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceLayerProperties"));
    pfn_EnumerateInstanceVersion = reinterpret_cast<detail::PFN_EnumerateInstanceVersion>(get_instance_proc_addr(nullptr,"vkEnumerateInstanceVersion"));
}
};
struct InstanceFunctions {
    Instance instance;
    detail::PFN_DestroyInstance pfn_DestroyInstance = nullptr;
    detail::PFN_EnumeratePhysicalDevices pfn_EnumeratePhysicalDevices = nullptr;
    detail::PFN_GetDeviceProcAddr pfn_GetDeviceProcAddr = nullptr;
    detail::PFN_GetInstanceProcAddr pfn_GetInstanceProcAddr = nullptr;
    detail::PFN_GetPhysicalDeviceProperties pfn_GetPhysicalDeviceProperties = nullptr;
    detail::PFN_GetPhysicalDeviceQueueFamilyProperties pfn_GetPhysicalDeviceQueueFamilyProperties = nullptr;
    detail::PFN_GetPhysicalDeviceMemoryProperties pfn_GetPhysicalDeviceMemoryProperties = nullptr;
    detail::PFN_GetPhysicalDeviceFeatures pfn_GetPhysicalDeviceFeatures = nullptr;
    detail::PFN_GetPhysicalDeviceFormatProperties pfn_GetPhysicalDeviceFormatProperties = nullptr;
    detail::PFN_GetPhysicalDeviceImageFormatProperties pfn_GetPhysicalDeviceImageFormatProperties = nullptr;
    detail::PFN_CreateDevice pfn_CreateDevice = nullptr;
    detail::PFN_EnumerateDeviceExtensionProperties pfn_EnumerateDeviceExtensionProperties = nullptr;
    detail::PFN_GetPhysicalDeviceSparseImageFormatProperties pfn_GetPhysicalDeviceSparseImageFormatProperties = nullptr;
    detail::PFN_EnumeratePhysicalDeviceGroups pfn_EnumeratePhysicalDeviceGroups = nullptr;
    detail::PFN_GetPhysicalDeviceFeatures2 pfn_GetPhysicalDeviceFeatures2 = nullptr;
    detail::PFN_GetPhysicalDeviceProperties2 pfn_GetPhysicalDeviceProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceFormatProperties2 pfn_GetPhysicalDeviceFormatProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceImageFormatProperties2 pfn_GetPhysicalDeviceImageFormatProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceQueueFamilyProperties2 pfn_GetPhysicalDeviceQueueFamilyProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceMemoryProperties2 pfn_GetPhysicalDeviceMemoryProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceSparseImageFormatProperties2 pfn_GetPhysicalDeviceSparseImageFormatProperties2 = nullptr;
    detail::PFN_GetPhysicalDeviceExternalBufferProperties pfn_GetPhysicalDeviceExternalBufferProperties = nullptr;
    detail::PFN_GetPhysicalDeviceExternalFenceProperties pfn_GetPhysicalDeviceExternalFenceProperties = nullptr;
    detail::PFN_GetPhysicalDeviceExternalSemaphoreProperties pfn_GetPhysicalDeviceExternalSemaphoreProperties = nullptr;
    detail::PFN_DestroySurfaceKHR pfn_DestroySurfaceKHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfaceSupportKHR pfn_GetPhysicalDeviceSurfaceSupportKHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfaceCapabilitiesKHR pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfaceFormatsKHR pfn_GetPhysicalDeviceSurfaceFormatsKHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfacePresentModesKHR pfn_GetPhysicalDeviceSurfacePresentModesKHR = nullptr;
    detail::PFN_GetPhysicalDevicePresentRectanglesKHR pfn_GetPhysicalDevicePresentRectanglesKHR = nullptr;
    detail::PFN_GetPhysicalDeviceDisplayPropertiesKHR pfn_GetPhysicalDeviceDisplayPropertiesKHR = nullptr;
    detail::PFN_GetPhysicalDeviceDisplayPlanePropertiesKHR pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR = nullptr;
    detail::PFN_GetDisplayPlaneSupportedDisplaysKHR pfn_GetDisplayPlaneSupportedDisplaysKHR = nullptr;
    detail::PFN_GetDisplayModePropertiesKHR pfn_GetDisplayModePropertiesKHR = nullptr;
    detail::PFN_CreateDisplayModeKHR pfn_CreateDisplayModeKHR = nullptr;
    detail::PFN_GetDisplayPlaneCapabilitiesKHR pfn_GetDisplayPlaneCapabilitiesKHR = nullptr;
    detail::PFN_CreateDisplayPlaneSurfaceKHR pfn_CreateDisplayPlaneSurfaceKHR = nullptr;
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    detail::PFN_CreateXlibSurfaceKHR pfn_CreateXlibSurfaceKHR = nullptr;
    detail::PFN_GetPhysicalDeviceXlibPresentationSupportKHR pfn_GetPhysicalDeviceXlibPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
    detail::PFN_CreateXcbSurfaceKHR pfn_CreateXcbSurfaceKHR = nullptr;
    detail::PFN_GetPhysicalDeviceXcbPresentationSupportKHR pfn_GetPhysicalDeviceXcbPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    detail::PFN_CreateWaylandSurfaceKHR pfn_CreateWaylandSurfaceKHR = nullptr;
    detail::PFN_GetPhysicalDeviceWaylandPresentationSupportKHR pfn_GetPhysicalDeviceWaylandPresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    detail::PFN_CreateAndroidSurfaceKHR pfn_CreateAndroidSurfaceKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_CreateWin32SurfaceKHR pfn_CreateWin32SurfaceKHR = nullptr;
    detail::PFN_GetPhysicalDeviceWin32PresentationSupportKHR pfn_GetPhysicalDeviceWin32PresentationSupportKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_CreateDebugReportCallbackEXT pfn_CreateDebugReportCallbackEXT = nullptr;
    detail::PFN_DestroyDebugReportCallbackEXT pfn_DestroyDebugReportCallbackEXT = nullptr;
    detail::PFN_DebugReportMessageEXT pfn_DebugReportMessageEXT = nullptr;
#if defined(VK_USE_PLATFORM_GGP)
    detail::PFN_CreateStreamDescriptorSurfaceGGP pfn_CreateStreamDescriptorSurfaceGGP = nullptr;
#endif // defined(VK_USE_PLATFORM_GGP)
    detail::PFN_GetPhysicalDeviceExternalImageFormatPropertiesNV pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV = nullptr;
#if defined(VK_USE_PLATFORM_VI_NN)
    detail::PFN_CreateViSurfaceNN pfn_CreateViSurfaceNN = nullptr;
#endif // defined(VK_USE_PLATFORM_VI_NN)
    detail::PFN_ReleaseDisplayEXT pfn_ReleaseDisplayEXT = nullptr;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    detail::PFN_AcquireXlibDisplayEXT pfn_AcquireXlibDisplayEXT = nullptr;
    detail::PFN_GetRandROutputDisplayEXT pfn_GetRandROutputDisplayEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    detail::PFN_GetPhysicalDeviceSurfaceCapabilities2EXT pfn_GetPhysicalDeviceSurfaceCapabilities2EXT = nullptr;
    detail::PFN_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = nullptr;
    detail::PFN_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfaceCapabilities2KHR pfn_GetPhysicalDeviceSurfaceCapabilities2KHR = nullptr;
    detail::PFN_GetPhysicalDeviceSurfaceFormats2KHR pfn_GetPhysicalDeviceSurfaceFormats2KHR = nullptr;
    detail::PFN_GetPhysicalDeviceDisplayProperties2KHR pfn_GetPhysicalDeviceDisplayProperties2KHR = nullptr;
    detail::PFN_GetPhysicalDeviceDisplayPlaneProperties2KHR pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR = nullptr;
    detail::PFN_GetDisplayModeProperties2KHR pfn_GetDisplayModeProperties2KHR = nullptr;
    detail::PFN_GetDisplayPlaneCapabilities2KHR pfn_GetDisplayPlaneCapabilities2KHR = nullptr;
#if defined(VK_USE_PLATFORM_IOS_MVK)
    detail::PFN_CreateIOSSurfaceMVK pfn_CreateIOSSurfaceMVK = nullptr;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    detail::PFN_CreateMacOSSurfaceMVK pfn_CreateMacOSSurfaceMVK = nullptr;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
    detail::PFN_CreateDebugUtilsMessengerEXT pfn_CreateDebugUtilsMessengerEXT = nullptr;
    detail::PFN_DestroyDebugUtilsMessengerEXT pfn_DestroyDebugUtilsMessengerEXT = nullptr;
    detail::PFN_SubmitDebugUtilsMessageEXT pfn_SubmitDebugUtilsMessageEXT = nullptr;
    detail::PFN_GetPhysicalDeviceMultisamplePropertiesEXT pfn_GetPhysicalDeviceMultisamplePropertiesEXT = nullptr;
    detail::PFN_GetPhysicalDeviceCalibrateableTimeDomainsEXT pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT = nullptr;
#if defined(VK_USE_PLATFORM_FUCHSIA)
    detail::PFN_CreateImagePipeSurfaceFUCHSIA pfn_CreateImagePipeSurfaceFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
    detail::PFN_CreateMetalSurfaceEXT pfn_CreateMetalSurfaceEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
    detail::PFN_GetPhysicalDeviceFragmentShadingRatesKHR pfn_GetPhysicalDeviceFragmentShadingRatesKHR = nullptr;
    detail::PFN_GetPhysicalDeviceToolPropertiesEXT pfn_GetPhysicalDeviceToolPropertiesEXT = nullptr;
    detail::PFN_GetPhysicalDeviceCooperativeMatrixPropertiesNV pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV = nullptr;
    detail::PFN_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetPhysicalDeviceSurfacePresentModes2EXT pfn_GetPhysicalDeviceSurfacePresentModes2EXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_CreateHeadlessSurfaceEXT pfn_CreateHeadlessSurfaceEXT = nullptr;
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    detail::PFN_CreateDirectFBSurfaceEXT pfn_CreateDirectFBSurfaceEXT = nullptr;
    detail::PFN_GetPhysicalDeviceDirectFBPresentationSupportEXT pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
void DestroyInstance(const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyInstance(instance,
        pAllocator);
}
[[nodiscard]] expected<detail::fixed_vector<PhysicalDevice>> EnumeratePhysicalDevices() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPhysicalDeviceCount = 0;
        Result result = pfn_EnumeratePhysicalDevices(instance,
        &pPhysicalDeviceCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDevice>{}, result);
    detail::fixed_vector<PhysicalDevice> pPhysicalDevices{pPhysicalDeviceCount};
    result = pfn_EnumeratePhysicalDevices(instance,
        &pPhysicalDeviceCount,
        pPhysicalDevices.data());
    if (pPhysicalDeviceCount < pPhysicalDevices.size()) pPhysicalDevices.shrink(pPhysicalDeviceCount);
    return expected(std::move(pPhysicalDevices), result);
}
[[nodiscard]] PFN_VoidFunction GetDeviceProcAddr(Device device, 
    const char* pName) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetDeviceProcAddr(device,
        pName);
}
[[nodiscard]] PFN_VoidFunction GetInstanceProcAddr(const char* pName) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetInstanceProcAddr(instance,
        pName);
}
[[nodiscard]] PhysicalDeviceProperties GetPhysicalDeviceProperties(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceProperties pProperties;
    pfn_GetPhysicalDeviceProperties(physicalDevice,
        &pProperties);
    return pProperties;
}
[[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pQueueFamilyPropertyCount = 0;
    pfn_GetPhysicalDeviceQueueFamilyProperties(physicalDevice,
        &pQueueFamilyPropertyCount,
        nullptr);
    detail::fixed_vector<QueueFamilyProperties> pQueueFamilyProperties{pQueueFamilyPropertyCount};
pfn_GetPhysicalDeviceQueueFamilyProperties(physicalDevice,
        &pQueueFamilyPropertyCount,
        pQueueFamilyProperties.data());
    if (pQueueFamilyPropertyCount < pQueueFamilyProperties.size()) pQueueFamilyProperties.shrink(pQueueFamilyPropertyCount);
    return pQueueFamilyProperties;
}
[[nodiscard]] PhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceMemoryProperties pMemoryProperties;
    pfn_GetPhysicalDeviceMemoryProperties(physicalDevice,
        &pMemoryProperties);
    return pMemoryProperties;
}
[[nodiscard]] PhysicalDeviceFeatures GetPhysicalDeviceFeatures(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceFeatures pFeatures;
    pfn_GetPhysicalDeviceFeatures(physicalDevice,
        &pFeatures);
    return pFeatures;
}
[[nodiscard]] FormatProperties GetPhysicalDeviceFormatProperties(PhysicalDevice physicalDevice, 
    Format format) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    FormatProperties pFormatProperties;
    pfn_GetPhysicalDeviceFormatProperties(physicalDevice,
        format,
        &pFormatProperties);
    return pFormatProperties;
}
[[nodiscard]] expected<ImageFormatProperties> GetPhysicalDeviceImageFormatProperties(PhysicalDevice physicalDevice, 
    Format format, 
    ImageType type, 
    ImageTiling tiling, 
    ImageUsageFlags usage, 
    ImageCreateFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ImageFormatProperties pImageFormatProperties;
        Result result = pfn_GetPhysicalDeviceImageFormatProperties(physicalDevice,
        format,
        type,
        tiling,
        usage,
        flags,
        &pImageFormatProperties);
    return expected<ImageFormatProperties>(pImageFormatProperties, result);
}
[[nodiscard]] expected<Device> CreateDevice(PhysicalDevice physicalDevice, 
    const DeviceCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Device pDevice;
        Result result = pfn_CreateDevice(physicalDevice,
        &pCreateInfo,
        pAllocator,
        &pDevice);
    return expected<Device>(pDevice, result);
}
[[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(PhysicalDevice physicalDevice, 
    const char* pLayerName = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_EnumerateDeviceExtensionProperties(physicalDevice,
        pLayerName,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<ExtensionProperties>{}, result);
    detail::fixed_vector<ExtensionProperties> pProperties{pPropertyCount};
    result = pfn_EnumerateDeviceExtensionProperties(physicalDevice,
        pLayerName,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetPhysicalDeviceSparseImageFormatProperties(PhysicalDevice physicalDevice, 
    Format format, 
    ImageType type, 
    SampleCountFlagBits samples, 
    ImageUsageFlags usage, 
    ImageTiling tiling) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
    pfn_GetPhysicalDeviceSparseImageFormatProperties(physicalDevice,
        format,
        type,
        samples,
        usage,
        tiling,
        &pPropertyCount,
        nullptr);
    detail::fixed_vector<SparseImageFormatProperties> pProperties{pPropertyCount};
pfn_GetPhysicalDeviceSparseImageFormatProperties(physicalDevice,
        format,
        type,
        samples,
        usage,
        tiling,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return pProperties;
}
[[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceGroupProperties>> EnumeratePhysicalDeviceGroups() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPhysicalDeviceGroupCount = 0;
        Result result = pfn_EnumeratePhysicalDeviceGroups(instance,
        &pPhysicalDeviceGroupCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDeviceGroupProperties>{}, result);
    detail::fixed_vector<PhysicalDeviceGroupProperties> pPhysicalDeviceGroupProperties{pPhysicalDeviceGroupCount};
    result = pfn_EnumeratePhysicalDeviceGroups(instance,
        &pPhysicalDeviceGroupCount,
        pPhysicalDeviceGroupProperties.data());
    if (pPhysicalDeviceGroupCount < pPhysicalDeviceGroupProperties.size()) pPhysicalDeviceGroupProperties.shrink(pPhysicalDeviceGroupCount);
    return expected(std::move(pPhysicalDeviceGroupProperties), result);
}
[[nodiscard]] PhysicalDeviceFeatures2 GetPhysicalDeviceFeatures2(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceFeatures2 pFeatures;
    pfn_GetPhysicalDeviceFeatures2(physicalDevice,
        &pFeatures);
    return pFeatures;
}
[[nodiscard]] PhysicalDeviceProperties2 GetPhysicalDeviceProperties2(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceProperties2 pProperties;
    pfn_GetPhysicalDeviceProperties2(physicalDevice,
        &pProperties);
    return pProperties;
}
[[nodiscard]] FormatProperties2 GetPhysicalDeviceFormatProperties2(PhysicalDevice physicalDevice, 
    Format format) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    FormatProperties2 pFormatProperties;
    pfn_GetPhysicalDeviceFormatProperties2(physicalDevice,
        format,
        &pFormatProperties);
    return pFormatProperties;
}
[[nodiscard]] expected<ImageFormatProperties2> GetPhysicalDeviceImageFormatProperties2(PhysicalDevice physicalDevice, 
    const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ImageFormatProperties2 pImageFormatProperties;
        Result result = pfn_GetPhysicalDeviceImageFormatProperties2(physicalDevice,
        &pImageFormatInfo,
        &pImageFormatProperties);
    return expected<ImageFormatProperties2>(pImageFormatProperties, result);
}
[[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetPhysicalDeviceQueueFamilyProperties2(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pQueueFamilyPropertyCount = 0;
    pfn_GetPhysicalDeviceQueueFamilyProperties2(physicalDevice,
        &pQueueFamilyPropertyCount,
        nullptr);
    detail::fixed_vector<QueueFamilyProperties2> pQueueFamilyProperties{pQueueFamilyPropertyCount};
pfn_GetPhysicalDeviceQueueFamilyProperties2(physicalDevice,
        &pQueueFamilyPropertyCount,
        pQueueFamilyProperties.data());
    if (pQueueFamilyPropertyCount < pQueueFamilyProperties.size()) pQueueFamilyProperties.shrink(pQueueFamilyPropertyCount);
    return pQueueFamilyProperties;
}
[[nodiscard]] PhysicalDeviceMemoryProperties2 GetPhysicalDeviceMemoryProperties2(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PhysicalDeviceMemoryProperties2 pMemoryProperties;
    pfn_GetPhysicalDeviceMemoryProperties2(physicalDevice,
        &pMemoryProperties);
    return pMemoryProperties;
}
[[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetPhysicalDeviceSparseImageFormatProperties2(PhysicalDevice physicalDevice, 
    const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
    pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice,
        &pFormatInfo,
        &pPropertyCount,
        nullptr);
    detail::fixed_vector<SparseImageFormatProperties2> pProperties{pPropertyCount};
pfn_GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice,
        &pFormatInfo,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return pProperties;
}
[[nodiscard]] ExternalBufferProperties GetPhysicalDeviceExternalBufferProperties(PhysicalDevice physicalDevice, 
    const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ExternalBufferProperties pExternalBufferProperties;
    pfn_GetPhysicalDeviceExternalBufferProperties(physicalDevice,
        &pExternalBufferInfo,
        &pExternalBufferProperties);
    return pExternalBufferProperties;
}
[[nodiscard]] ExternalFenceProperties GetPhysicalDeviceExternalFenceProperties(PhysicalDevice physicalDevice, 
    const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ExternalFenceProperties pExternalFenceProperties;
    pfn_GetPhysicalDeviceExternalFenceProperties(physicalDevice,
        &pExternalFenceInfo,
        &pExternalFenceProperties);
    return pExternalFenceProperties;
}
[[nodiscard]] ExternalSemaphoreProperties GetPhysicalDeviceExternalSemaphoreProperties(PhysicalDevice physicalDevice, 
    const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ExternalSemaphoreProperties pExternalSemaphoreProperties;
    pfn_GetPhysicalDeviceExternalSemaphoreProperties(physicalDevice,
        &pExternalSemaphoreInfo,
        &pExternalSemaphoreProperties);
    return pExternalSemaphoreProperties;
}
void DestroySurfaceKHR(SurfaceKHR surface = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroySurfaceKHR(instance,
        surface,
        pAllocator);
}
[[nodiscard]] expected<Bool32> GetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Bool32 pSupported;
        Result result = pfn_GetPhysicalDeviceSurfaceSupportKHR(physicalDevice,
        queueFamilyIndex,
        surface,
        &pSupported);
    return expected<Bool32>(pSupported, result);
}
[[nodiscard]] expected<SurfaceCapabilitiesKHR> GetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice physicalDevice, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceCapabilitiesKHR pSurfaceCapabilities;
        Result result = pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,
        surface,
        &pSurfaceCapabilities);
    return expected<SurfaceCapabilitiesKHR>(pSurfaceCapabilities, result);
}
[[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice physicalDevice, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pSurfaceFormatCount = 0;
        Result result = pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
        surface,
        &pSurfaceFormatCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<SurfaceFormatKHR>{}, result);
    detail::fixed_vector<SurfaceFormatKHR> pSurfaceFormats{pSurfaceFormatCount};
    result = pfn_GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,
        surface,
        &pSurfaceFormatCount,
        pSurfaceFormats.data());
    if (pSurfaceFormatCount < pSurfaceFormats.size()) pSurfaceFormats.shrink(pSurfaceFormatCount);
    return expected(std::move(pSurfaceFormats), result);
}
[[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModesKHR(PhysicalDevice physicalDevice, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPresentModeCount = 0;
        Result result = pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
        surface,
        &pPresentModeCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PresentModeKHR>{}, result);
    detail::fixed_vector<PresentModeKHR> pPresentModes{pPresentModeCount};
    result = pfn_GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice,
        surface,
        &pPresentModeCount,
        pPresentModes.data());
    if (pPresentModeCount < pPresentModes.size()) pPresentModes.shrink(pPresentModeCount);
    return expected(std::move(pPresentModes), result);
}
[[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPhysicalDevicePresentRectanglesKHR(PhysicalDevice physicalDevice, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pRectCount = 0;
        Result result = pfn_GetPhysicalDevicePresentRectanglesKHR(physicalDevice,
        surface,
        &pRectCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<Rect2D>{}, result);
    detail::fixed_vector<Rect2D> pRects{pRectCount};
    result = pfn_GetPhysicalDevicePresentRectanglesKHR(physicalDevice,
        surface,
        &pRectCount,
        pRects.data());
    if (pRectCount < pRects.size()) pRects.shrink(pRectCount);
    return expected(std::move(pRects), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetPhysicalDeviceDisplayPropertiesKHR(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayPropertiesKHR>{}, result);
    detail::fixed_vector<DisplayPropertiesKHR> pProperties{pPropertyCount};
    result = pfn_GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetPhysicalDeviceDisplayPlanePropertiesKHR(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayPlanePropertiesKHR>{}, result);
    detail::fixed_vector<DisplayPlanePropertiesKHR> pProperties{pPropertyCount};
    result = pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(PhysicalDevice physicalDevice, 
    uint32_t planeIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pDisplayCount = 0;
        Result result = pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice,
        planeIndex,
        &pDisplayCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayKHR>{}, result);
    detail::fixed_vector<DisplayKHR> pDisplays{pDisplayCount};
    result = pfn_GetDisplayPlaneSupportedDisplaysKHR(physicalDevice,
        planeIndex,
        &pDisplayCount,
        pDisplays.data());
    if (pDisplayCount < pDisplays.size()) pDisplays.shrink(pDisplayCount);
    return expected(std::move(pDisplays), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(PhysicalDevice physicalDevice, 
    DisplayKHR display) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetDisplayModePropertiesKHR(physicalDevice,
        display,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayModePropertiesKHR>{}, result);
    detail::fixed_vector<DisplayModePropertiesKHR> pProperties{pPropertyCount};
    result = pfn_GetDisplayModePropertiesKHR(physicalDevice,
        display,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(PhysicalDevice physicalDevice, 
    DisplayKHR display, 
    const DisplayModeCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DisplayModeKHR pMode;
        Result result = pfn_CreateDisplayModeKHR(physicalDevice,
        display,
        &pCreateInfo,
        pAllocator,
        &pMode);
    return expected<DisplayModeKHR>(pMode, result);
}
[[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(PhysicalDevice physicalDevice, 
    DisplayModeKHR mode, 
    uint32_t planeIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DisplayPlaneCapabilitiesKHR pCapabilities;
        Result result = pfn_GetDisplayPlaneCapabilitiesKHR(physicalDevice,
        mode,
        planeIndex,
        &pCapabilities);
    return expected<DisplayPlaneCapabilitiesKHR>(pCapabilities, result);
}
[[nodiscard]] expected<SurfaceKHR> CreateDisplayPlaneSurfaceKHR(const DisplaySurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateDisplayPlaneSurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#if defined(VK_USE_PLATFORM_XLIB_KHR)
[[nodiscard]] expected<SurfaceKHR> CreateXlibSurfaceKHR(const XlibSurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateXlibSurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
[[nodiscard]] Bool32 GetPhysicalDeviceXlibPresentationSupportKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex, 
    Display&  dpy, 
    VisualID visualID) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice,
        queueFamilyIndex,
        &dpy,
        visualID);
}
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
[[nodiscard]] expected<SurfaceKHR> CreateXcbSurfaceKHR(const XcbSurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateXcbSurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
[[nodiscard]] Bool32 GetPhysicalDeviceXcbPresentationSupportKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex, 
    xcb_connection_t&  connection, 
    xcb_visualid_t visual_id) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice,
        queueFamilyIndex,
        &connection,
        visual_id);
}
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
[[nodiscard]] expected<SurfaceKHR> CreateWaylandSurfaceKHR(const WaylandSurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateWaylandSurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
[[nodiscard]] expected<wl_display> GetPhysicalDeviceWaylandPresentationSupportKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    wl_display display;
        Result result = pfn_GetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice,
        queueFamilyIndex,
        &display);
    return expected<wl_display>(display, result);
}
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
[[nodiscard]] expected<SurfaceKHR> CreateAndroidSurfaceKHR(const AndroidSurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateAndroidSurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<SurfaceKHR> CreateWin32SurfaceKHR(const Win32SurfaceCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateWin32SurfaceKHR(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Bool32 GetPhysicalDeviceWin32PresentationSupportKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice,
        queueFamilyIndex);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
[[nodiscard]] expected<DebugReportCallbackEXT> CreateDebugReportCallbackEXT(const DebugReportCallbackCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DebugReportCallbackEXT pCallback;
        Result result = pfn_CreateDebugReportCallbackEXT(instance,
        &pCreateInfo,
        pAllocator,
        &pCallback);
    return expected<DebugReportCallbackEXT>(pCallback, result);
}
void DestroyDebugReportCallbackEXT(DebugReportCallbackEXT callback = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDebugReportCallbackEXT(instance,
        callback,
        pAllocator);
}
void DebugReportMessageEXT(DebugReportFlagsEXT flags, 
    DebugReportObjectTypeEXT objectType, 
    uint64_t object, 
    size_t location, 
    int32_t messageCode, 
    const char* pLayerPrefix, 
    const char* pMessage) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DebugReportMessageEXT(instance,
        flags,
        objectType,
        object,
        location,
        messageCode,
        pLayerPrefix,
        pMessage);
}
#if defined(VK_USE_PLATFORM_GGP)
[[nodiscard]] expected<SurfaceKHR> CreateStreamDescriptorSurfaceGGP(const StreamDescriptorSurfaceCreateInfoGGP&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateStreamDescriptorSurfaceGGP(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_GGP
[[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetPhysicalDeviceExternalImageFormatPropertiesNV(PhysicalDevice physicalDevice, 
    Format format, 
    ImageType type, 
    ImageTiling tiling, 
    ImageUsageFlags usage, 
    ImageCreateFlags flags = {}, 
    ExternalMemoryHandleTypeFlagsNV externalHandleType = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ExternalImageFormatPropertiesNV pExternalImageFormatProperties;
        Result result = pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice,
        format,
        type,
        tiling,
        usage,
        flags,
        externalHandleType,
        &pExternalImageFormatProperties);
    return expected<ExternalImageFormatPropertiesNV>(pExternalImageFormatProperties, result);
}
#if defined(VK_USE_PLATFORM_VI_NN)
[[nodiscard]] expected<SurfaceKHR> CreateViSurfaceNN(const ViSurfaceCreateInfoNN&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateViSurfaceNN(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_VI_NN
[[nodiscard]] Result ReleaseDisplayEXT(PhysicalDevice physicalDevice, 
    DisplayKHR display) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ReleaseDisplayEXT(physicalDevice,
        display);
}
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
[[nodiscard]] Result AcquireXlibDisplayEXT(PhysicalDevice physicalDevice, 
    Display&  dpy, 
    DisplayKHR display) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_AcquireXlibDisplayEXT(physicalDevice,
        &dpy,
        display);
}
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
[[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(PhysicalDevice physicalDevice, 
    Display&  dpy, 
    RROutput rrOutput) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DisplayKHR pDisplay;
        Result result = pfn_GetRandROutputDisplayEXT(physicalDevice,
        &dpy,
        rrOutput,
        &pDisplay);
    return expected<DisplayKHR>(pDisplay, result);
}
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
[[nodiscard]] expected<SurfaceCapabilities2EXT> GetPhysicalDeviceSurfaceCapabilities2EXT(PhysicalDevice physicalDevice, 
    SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceCapabilities2EXT pSurfaceCapabilities;
        Result result = pfn_GetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice,
        surface,
        &pSurfaceCapabilities);
    return expected<SurfaceCapabilities2EXT>(pSurfaceCapabilities, result);
}
[[nodiscard]] Result EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex, 
    uint32_t&  pCounterCount, 
    PerformanceCounterKHR* pCounters = nullptr, 
    PerformanceCounterDescriptionKHR* pCounterDescriptions = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice,
        queueFamilyIndex,
        &pCounterCount,
        pCounters,
        pCounterDescriptions);
}
[[nodiscard]] uint32_t GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(PhysicalDevice physicalDevice, 
    const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pNumPasses;
    pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice,
        &pPerformanceQueryCreateInfo,
        &pNumPasses);
    return pNumPasses;
}
[[nodiscard]] expected<SurfaceCapabilities2KHR> GetPhysicalDeviceSurfaceCapabilities2KHR(PhysicalDevice physicalDevice, 
    const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceCapabilities2KHR pSurfaceCapabilities;
        Result result = pfn_GetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice,
        &pSurfaceInfo,
        &pSurfaceCapabilities);
    return expected<SurfaceCapabilities2KHR>(pSurfaceCapabilities, result);
}
[[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetPhysicalDeviceSurfaceFormats2KHR(PhysicalDevice physicalDevice, 
    const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pSurfaceFormatCount = 0;
        Result result = pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice,
        &pSurfaceInfo,
        &pSurfaceFormatCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<SurfaceFormat2KHR>{}, result);
    detail::fixed_vector<SurfaceFormat2KHR> pSurfaceFormats{pSurfaceFormatCount};
    result = pfn_GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice,
        &pSurfaceInfo,
        &pSurfaceFormatCount,
        pSurfaceFormats.data());
    if (pSurfaceFormatCount < pSurfaceFormats.size()) pSurfaceFormats.shrink(pSurfaceFormatCount);
    return expected(std::move(pSurfaceFormats), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetPhysicalDeviceDisplayProperties2KHR(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayProperties2KHR>{}, result);
    detail::fixed_vector<DisplayProperties2KHR> pProperties{pPropertyCount};
    result = pfn_GetPhysicalDeviceDisplayProperties2KHR(physicalDevice,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetPhysicalDeviceDisplayPlaneProperties2KHR(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayPlaneProperties2KHR>{}, result);
    detail::fixed_vector<DisplayPlaneProperties2KHR> pProperties{pPropertyCount};
    result = pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(PhysicalDevice physicalDevice, 
    DisplayKHR display) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetDisplayModeProperties2KHR(physicalDevice,
        display,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<DisplayModeProperties2KHR>{}, result);
    detail::fixed_vector<DisplayModeProperties2KHR> pProperties{pPropertyCount};
    result = pfn_GetDisplayModeProperties2KHR(physicalDevice,
        display,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(PhysicalDevice physicalDevice, 
    const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DisplayPlaneCapabilities2KHR pCapabilities;
        Result result = pfn_GetDisplayPlaneCapabilities2KHR(physicalDevice,
        &pDisplayPlaneInfo,
        &pCapabilities);
    return expected<DisplayPlaneCapabilities2KHR>(pCapabilities, result);
}
#if defined(VK_USE_PLATFORM_IOS_MVK)
[[nodiscard]] expected<SurfaceKHR> CreateIOSSurfaceMVK(const IOSSurfaceCreateInfoMVK&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateIOSSurfaceMVK(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
[[nodiscard]] expected<SurfaceKHR> CreateMacOSSurfaceMVK(const MacOSSurfaceCreateInfoMVK&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateMacOSSurfaceMVK(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_MACOS_MVK
[[nodiscard]] expected<DebugUtilsMessengerEXT> CreateDebugUtilsMessengerEXT(const DebugUtilsMessengerCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DebugUtilsMessengerEXT pMessenger;
        Result result = pfn_CreateDebugUtilsMessengerEXT(instance,
        &pCreateInfo,
        pAllocator,
        &pMessenger);
    return expected<DebugUtilsMessengerEXT>(pMessenger, result);
}
void DestroyDebugUtilsMessengerEXT(DebugUtilsMessengerEXT messenger = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDebugUtilsMessengerEXT(instance,
        messenger,
        pAllocator);
}
void SubmitDebugUtilsMessageEXT(DebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
    DebugUtilsMessageTypeFlagsEXT messageTypes, 
    const DebugUtilsMessengerCallbackDataEXT&  pCallbackData) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_SubmitDebugUtilsMessageEXT(instance,
        messageSeverity,
        messageTypes,
        &pCallbackData);
}
[[nodiscard]] MultisamplePropertiesEXT GetPhysicalDeviceMultisamplePropertiesEXT(PhysicalDevice physicalDevice, 
    SampleCountFlagBits samples) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MultisamplePropertiesEXT pMultisampleProperties;
    pfn_GetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice,
        samples,
        &pMultisampleProperties);
    return pMultisampleProperties;
}
[[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetPhysicalDeviceCalibrateableTimeDomainsEXT(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pTimeDomainCount = 0;
        Result result = pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice,
        &pTimeDomainCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<TimeDomainEXT>{}, result);
    detail::fixed_vector<TimeDomainEXT> pTimeDomains{pTimeDomainCount};
    result = pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice,
        &pTimeDomainCount,
        pTimeDomains.data());
    if (pTimeDomainCount < pTimeDomains.size()) pTimeDomains.shrink(pTimeDomainCount);
    return expected(std::move(pTimeDomains), result);
}
#if defined(VK_USE_PLATFORM_FUCHSIA)
[[nodiscard]] expected<SurfaceKHR> CreateImagePipeSurfaceFUCHSIA(const ImagePipeSurfaceCreateInfoFUCHSIA&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateImagePipeSurfaceFUCHSIA(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_METAL_EXT)
[[nodiscard]] expected<SurfaceKHR> CreateMetalSurfaceEXT(const MetalSurfaceCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateMetalSurfaceEXT(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_METAL_EXT
[[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceFragmentShadingRateKHR>> GetPhysicalDeviceFragmentShadingRatesKHR(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pFragmentShadingRateCount = 0;
        Result result = pfn_GetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice,
        &pFragmentShadingRateCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDeviceFragmentShadingRateKHR>{}, result);
    detail::fixed_vector<PhysicalDeviceFragmentShadingRateKHR> pFragmentShadingRates{pFragmentShadingRateCount};
    result = pfn_GetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice,
        &pFragmentShadingRateCount,
        pFragmentShadingRates.data());
    if (pFragmentShadingRateCount < pFragmentShadingRates.size()) pFragmentShadingRates.shrink(pFragmentShadingRateCount);
    return expected(std::move(pFragmentShadingRates), result);
}
[[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetPhysicalDeviceToolPropertiesEXT(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pToolCount = 0;
        Result result = pfn_GetPhysicalDeviceToolPropertiesEXT(physicalDevice,
        &pToolCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>{}, result);
    detail::fixed_vector<PhysicalDeviceToolPropertiesEXT> pToolProperties{pToolCount};
    result = pfn_GetPhysicalDeviceToolPropertiesEXT(physicalDevice,
        &pToolCount,
        pToolProperties.data());
    if (pToolCount < pToolProperties.size()) pToolProperties.shrink(pToolCount);
    return expected(std::move(pToolProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetPhysicalDeviceCooperativeMatrixPropertiesNV(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPropertyCount = 0;
        Result result = pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice,
        &pPropertyCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<CooperativeMatrixPropertiesNV>{}, result);
    detail::fixed_vector<CooperativeMatrixPropertiesNV> pProperties{pPropertyCount};
    result = pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice,
        &pPropertyCount,
        pProperties.data());
    if (pPropertyCount < pProperties.size()) pProperties.shrink(pPropertyCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(PhysicalDevice physicalDevice) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pCombinationCount = 0;
        Result result = pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice,
        &pCombinationCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<FramebufferMixedSamplesCombinationNV>{}, result);
    detail::fixed_vector<FramebufferMixedSamplesCombinationNV> pCombinations{pCombinationCount};
    result = pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice,
        &pCombinationCount,
        pCombinations.data());
    if (pCombinationCount < pCombinations.size()) pCombinations.shrink(pCombinationCount);
    return expected(std::move(pCombinations), result);
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetPhysicalDeviceSurfacePresentModes2EXT(PhysicalDevice physicalDevice, 
    const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPresentModeCount = 0;
        Result result = pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice,
        &pSurfaceInfo,
        &pPresentModeCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PresentModeKHR>{}, result);
    detail::fixed_vector<PresentModeKHR> pPresentModes{pPresentModeCount};
    result = pfn_GetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice,
        &pSurfaceInfo,
        &pPresentModeCount,
        pPresentModes.data());
    if (pPresentModeCount < pPresentModes.size()) pPresentModes.shrink(pPresentModeCount);
    return expected(std::move(pPresentModes), result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
[[nodiscard]] expected<SurfaceKHR> CreateHeadlessSurfaceEXT(const HeadlessSurfaceCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateHeadlessSurfaceEXT(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
[[nodiscard]] expected<SurfaceKHR> CreateDirectFBSurfaceEXT(const DirectFBSurfaceCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SurfaceKHR pSurface;
        Result result = pfn_CreateDirectFBSurfaceEXT(instance,
        &pCreateInfo,
        pAllocator,
        &pSurface);
    return expected<SurfaceKHR>(pSurface, result);
}
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
[[nodiscard]] expected<IDirectFB> GetPhysicalDeviceDirectFBPresentationSupportEXT(PhysicalDevice physicalDevice, 
    uint32_t queueFamilyIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    IDirectFB dfb;
        Result result = pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT(physicalDevice,
        queueFamilyIndex,
        &dfb);
    return expected<IDirectFB>(dfb, result);
}
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
InstanceFunctions() noexcept {}
explicit InstanceFunctions(GlobalFunctions const& global_functions, Instance instance) noexcept 
    :instance(instance) { 
    detail::PFN_GetInstanceProcAddr get_instance_proc_addr = global_functions.pfn_GetInstanceProcAddr;
    pfn_DestroyInstance = reinterpret_cast<detail::PFN_DestroyInstance>(get_instance_proc_addr(instance,"vkDestroyInstance"));
    pfn_EnumeratePhysicalDevices = reinterpret_cast<detail::PFN_EnumeratePhysicalDevices>(get_instance_proc_addr(instance,"vkEnumeratePhysicalDevices"));
    pfn_GetDeviceProcAddr = reinterpret_cast<detail::PFN_GetDeviceProcAddr>(get_instance_proc_addr(instance,"vkGetDeviceProcAddr"));
    pfn_GetInstanceProcAddr = reinterpret_cast<detail::PFN_GetInstanceProcAddr>(get_instance_proc_addr(instance,"vkGetInstanceProcAddr"));
    pfn_GetPhysicalDeviceProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceProperties"));
    pfn_GetPhysicalDeviceQueueFamilyProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceQueueFamilyProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceQueueFamilyProperties"));
    pfn_GetPhysicalDeviceMemoryProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceMemoryProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceMemoryProperties"));
    pfn_GetPhysicalDeviceFeatures = reinterpret_cast<detail::PFN_GetPhysicalDeviceFeatures>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceFeatures"));
    pfn_GetPhysicalDeviceFormatProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceFormatProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceFormatProperties"));
    pfn_GetPhysicalDeviceImageFormatProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceImageFormatProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceImageFormatProperties"));
    pfn_CreateDevice = reinterpret_cast<detail::PFN_CreateDevice>(get_instance_proc_addr(instance,"vkCreateDevice"));
    pfn_EnumerateDeviceExtensionProperties = reinterpret_cast<detail::PFN_EnumerateDeviceExtensionProperties>(get_instance_proc_addr(instance,"vkEnumerateDeviceExtensionProperties"));
    pfn_GetPhysicalDeviceSparseImageFormatProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceSparseImageFormatProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSparseImageFormatProperties"));
    pfn_EnumeratePhysicalDeviceGroups = reinterpret_cast<detail::PFN_EnumeratePhysicalDeviceGroups>(get_instance_proc_addr(instance,"vkEnumeratePhysicalDeviceGroups"));
    pfn_GetPhysicalDeviceFeatures2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceFeatures2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceFeatures2"));
    pfn_GetPhysicalDeviceProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceProperties2"));
    pfn_GetPhysicalDeviceFormatProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceFormatProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceFormatProperties2"));
    pfn_GetPhysicalDeviceImageFormatProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceImageFormatProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceImageFormatProperties2"));
    pfn_GetPhysicalDeviceQueueFamilyProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceQueueFamilyProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceQueueFamilyProperties2"));
    pfn_GetPhysicalDeviceMemoryProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceMemoryProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceMemoryProperties2"));
    pfn_GetPhysicalDeviceSparseImageFormatProperties2 = reinterpret_cast<detail::PFN_GetPhysicalDeviceSparseImageFormatProperties2>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSparseImageFormatProperties2"));
    pfn_GetPhysicalDeviceExternalBufferProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceExternalBufferProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceExternalBufferProperties"));
    pfn_GetPhysicalDeviceExternalFenceProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceExternalFenceProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceExternalFenceProperties"));
    pfn_GetPhysicalDeviceExternalSemaphoreProperties = reinterpret_cast<detail::PFN_GetPhysicalDeviceExternalSemaphoreProperties>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceExternalSemaphoreProperties"));
    pfn_DestroySurfaceKHR = reinterpret_cast<detail::PFN_DestroySurfaceKHR>(get_instance_proc_addr(instance,"vkDestroySurfaceKHR"));
    pfn_GetPhysicalDeviceSurfaceSupportKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceSupportKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceSupportKHR"));
    pfn_GetPhysicalDeviceSurfaceCapabilitiesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceCapabilitiesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
    pfn_GetPhysicalDeviceSurfaceFormatsKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceFormatsKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceFormatsKHR"));
    pfn_GetPhysicalDeviceSurfacePresentModesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfacePresentModesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfacePresentModesKHR"));
    pfn_GetPhysicalDevicePresentRectanglesKHR = reinterpret_cast<detail::PFN_GetPhysicalDevicePresentRectanglesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDevicePresentRectanglesKHR"));
    pfn_GetPhysicalDeviceDisplayPropertiesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceDisplayPropertiesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceDisplayPropertiesKHR"));
    pfn_GetPhysicalDeviceDisplayPlanePropertiesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceDisplayPlanePropertiesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceDisplayPlanePropertiesKHR"));
    pfn_GetDisplayPlaneSupportedDisplaysKHR = reinterpret_cast<detail::PFN_GetDisplayPlaneSupportedDisplaysKHR>(get_instance_proc_addr(instance,"vkGetDisplayPlaneSupportedDisplaysKHR"));
    pfn_GetDisplayModePropertiesKHR = reinterpret_cast<detail::PFN_GetDisplayModePropertiesKHR>(get_instance_proc_addr(instance,"vkGetDisplayModePropertiesKHR"));
    pfn_CreateDisplayModeKHR = reinterpret_cast<detail::PFN_CreateDisplayModeKHR>(get_instance_proc_addr(instance,"vkCreateDisplayModeKHR"));
    pfn_GetDisplayPlaneCapabilitiesKHR = reinterpret_cast<detail::PFN_GetDisplayPlaneCapabilitiesKHR>(get_instance_proc_addr(instance,"vkGetDisplayPlaneCapabilitiesKHR"));
    pfn_CreateDisplayPlaneSurfaceKHR = reinterpret_cast<detail::PFN_CreateDisplayPlaneSurfaceKHR>(get_instance_proc_addr(instance,"vkCreateDisplayPlaneSurfaceKHR"));
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    pfn_CreateXlibSurfaceKHR = reinterpret_cast<detail::PFN_CreateXlibSurfaceKHR>(get_instance_proc_addr(instance,"vkCreateXlibSurfaceKHR"));
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    pfn_GetPhysicalDeviceXlibPresentationSupportKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceXlibPresentationSupportKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceXlibPresentationSupportKHR"));
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    pfn_CreateXcbSurfaceKHR = reinterpret_cast<detail::PFN_CreateXcbSurfaceKHR>(get_instance_proc_addr(instance,"vkCreateXcbSurfaceKHR"));
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    pfn_GetPhysicalDeviceXcbPresentationSupportKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceXcbPresentationSupportKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceXcbPresentationSupportKHR"));
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    pfn_CreateWaylandSurfaceKHR = reinterpret_cast<detail::PFN_CreateWaylandSurfaceKHR>(get_instance_proc_addr(instance,"vkCreateWaylandSurfaceKHR"));
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    pfn_GetPhysicalDeviceWaylandPresentationSupportKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceWaylandPresentationSupportKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceWaylandPresentationSupportKHR"));
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_CreateAndroidSurfaceKHR = reinterpret_cast<detail::PFN_CreateAndroidSurfaceKHR>(get_instance_proc_addr(instance,"vkCreateAndroidSurfaceKHR"));
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_CreateWin32SurfaceKHR = reinterpret_cast<detail::PFN_CreateWin32SurfaceKHR>(get_instance_proc_addr(instance,"vkCreateWin32SurfaceKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetPhysicalDeviceWin32PresentationSupportKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceWin32PresentationSupportKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceWin32PresentationSupportKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_CreateDebugReportCallbackEXT = reinterpret_cast<detail::PFN_CreateDebugReportCallbackEXT>(get_instance_proc_addr(instance,"vkCreateDebugReportCallbackEXT"));
    pfn_DestroyDebugReportCallbackEXT = reinterpret_cast<detail::PFN_DestroyDebugReportCallbackEXT>(get_instance_proc_addr(instance,"vkDestroyDebugReportCallbackEXT"));
    pfn_DebugReportMessageEXT = reinterpret_cast<detail::PFN_DebugReportMessageEXT>(get_instance_proc_addr(instance,"vkDebugReportMessageEXT"));
#if defined(VK_USE_PLATFORM_GGP)
    pfn_CreateStreamDescriptorSurfaceGGP = reinterpret_cast<detail::PFN_CreateStreamDescriptorSurfaceGGP>(get_instance_proc_addr(instance,"vkCreateStreamDescriptorSurfaceGGP"));
#endif // VK_USE_PLATFORM_GGP
    pfn_GetPhysicalDeviceExternalImageFormatPropertiesNV = reinterpret_cast<detail::PFN_GetPhysicalDeviceExternalImageFormatPropertiesNV>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceExternalImageFormatPropertiesNV"));
#if defined(VK_USE_PLATFORM_VI_NN)
    pfn_CreateViSurfaceNN = reinterpret_cast<detail::PFN_CreateViSurfaceNN>(get_instance_proc_addr(instance,"vkCreateViSurfaceNN"));
#endif // VK_USE_PLATFORM_VI_NN
    pfn_ReleaseDisplayEXT = reinterpret_cast<detail::PFN_ReleaseDisplayEXT>(get_instance_proc_addr(instance,"vkReleaseDisplayEXT"));
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    pfn_AcquireXlibDisplayEXT = reinterpret_cast<detail::PFN_AcquireXlibDisplayEXT>(get_instance_proc_addr(instance,"vkAcquireXlibDisplayEXT"));
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    pfn_GetRandROutputDisplayEXT = reinterpret_cast<detail::PFN_GetRandROutputDisplayEXT>(get_instance_proc_addr(instance,"vkGetRandROutputDisplayEXT"));
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
    pfn_GetPhysicalDeviceSurfaceCapabilities2EXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceCapabilities2EXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceCapabilities2EXT"));
    pfn_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = reinterpret_cast<detail::PFN_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR>(get_instance_proc_addr(instance,"vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR"));
    pfn_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR"));
    pfn_GetPhysicalDeviceSurfaceCapabilities2KHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceCapabilities2KHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceCapabilities2KHR"));
    pfn_GetPhysicalDeviceSurfaceFormats2KHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfaceFormats2KHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfaceFormats2KHR"));
    pfn_GetPhysicalDeviceDisplayProperties2KHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceDisplayProperties2KHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceDisplayProperties2KHR"));
    pfn_GetPhysicalDeviceDisplayPlaneProperties2KHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceDisplayPlaneProperties2KHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceDisplayPlaneProperties2KHR"));
    pfn_GetDisplayModeProperties2KHR = reinterpret_cast<detail::PFN_GetDisplayModeProperties2KHR>(get_instance_proc_addr(instance,"vkGetDisplayModeProperties2KHR"));
    pfn_GetDisplayPlaneCapabilities2KHR = reinterpret_cast<detail::PFN_GetDisplayPlaneCapabilities2KHR>(get_instance_proc_addr(instance,"vkGetDisplayPlaneCapabilities2KHR"));
#if defined(VK_USE_PLATFORM_IOS_MVK)
    pfn_CreateIOSSurfaceMVK = reinterpret_cast<detail::PFN_CreateIOSSurfaceMVK>(get_instance_proc_addr(instance,"vkCreateIOSSurfaceMVK"));
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    pfn_CreateMacOSSurfaceMVK = reinterpret_cast<detail::PFN_CreateMacOSSurfaceMVK>(get_instance_proc_addr(instance,"vkCreateMacOSSurfaceMVK"));
#endif // VK_USE_PLATFORM_MACOS_MVK
    pfn_CreateDebugUtilsMessengerEXT = reinterpret_cast<detail::PFN_CreateDebugUtilsMessengerEXT>(get_instance_proc_addr(instance,"vkCreateDebugUtilsMessengerEXT"));
    pfn_DestroyDebugUtilsMessengerEXT = reinterpret_cast<detail::PFN_DestroyDebugUtilsMessengerEXT>(get_instance_proc_addr(instance,"vkDestroyDebugUtilsMessengerEXT"));
    pfn_SubmitDebugUtilsMessageEXT = reinterpret_cast<detail::PFN_SubmitDebugUtilsMessageEXT>(get_instance_proc_addr(instance,"vkSubmitDebugUtilsMessageEXT"));
    pfn_GetPhysicalDeviceMultisamplePropertiesEXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceMultisamplePropertiesEXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceMultisamplePropertiesEXT"));
    pfn_GetPhysicalDeviceCalibrateableTimeDomainsEXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceCalibrateableTimeDomainsEXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceCalibrateableTimeDomainsEXT"));
#if defined(VK_USE_PLATFORM_FUCHSIA)
    pfn_CreateImagePipeSurfaceFUCHSIA = reinterpret_cast<detail::PFN_CreateImagePipeSurfaceFUCHSIA>(get_instance_proc_addr(instance,"vkCreateImagePipeSurfaceFUCHSIA"));
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_METAL_EXT)
    pfn_CreateMetalSurfaceEXT = reinterpret_cast<detail::PFN_CreateMetalSurfaceEXT>(get_instance_proc_addr(instance,"vkCreateMetalSurfaceEXT"));
#endif // VK_USE_PLATFORM_METAL_EXT
    pfn_GetPhysicalDeviceFragmentShadingRatesKHR = reinterpret_cast<detail::PFN_GetPhysicalDeviceFragmentShadingRatesKHR>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceFragmentShadingRatesKHR"));
    pfn_GetPhysicalDeviceToolPropertiesEXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceToolPropertiesEXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceToolPropertiesEXT"));
    pfn_GetPhysicalDeviceCooperativeMatrixPropertiesNV = reinterpret_cast<detail::PFN_GetPhysicalDeviceCooperativeMatrixPropertiesNV>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceCooperativeMatrixPropertiesNV"));
    pfn_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = reinterpret_cast<detail::PFN_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetPhysicalDeviceSurfacePresentModes2EXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceSurfacePresentModes2EXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceSurfacePresentModes2EXT"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_CreateHeadlessSurfaceEXT = reinterpret_cast<detail::PFN_CreateHeadlessSurfaceEXT>(get_instance_proc_addr(instance,"vkCreateHeadlessSurfaceEXT"));
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    pfn_CreateDirectFBSurfaceEXT = reinterpret_cast<detail::PFN_CreateDirectFBSurfaceEXT>(get_instance_proc_addr(instance,"vkCreateDirectFBSurfaceEXT"));
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    pfn_GetPhysicalDeviceDirectFBPresentationSupportEXT = reinterpret_cast<detail::PFN_GetPhysicalDeviceDirectFBPresentationSupportEXT>(get_instance_proc_addr(instance,"vkGetPhysicalDeviceDirectFBPresentationSupportEXT"));
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
}
};
struct DeviceFunctions {
    Device device;
    detail::PFN_DestroyDevice pfn_DestroyDevice = nullptr;
    detail::PFN_GetDeviceQueue pfn_GetDeviceQueue = nullptr;
    detail::PFN_QueueSubmit pfn_QueueSubmit = nullptr;
    detail::PFN_QueueWaitIdle pfn_QueueWaitIdle = nullptr;
    detail::PFN_DeviceWaitIdle pfn_DeviceWaitIdle = nullptr;
    detail::PFN_AllocateMemory pfn_AllocateMemory = nullptr;
    detail::PFN_FreeMemory pfn_FreeMemory = nullptr;
    detail::PFN_MapMemory pfn_MapMemory = nullptr;
    detail::PFN_UnmapMemory pfn_UnmapMemory = nullptr;
    detail::PFN_FlushMappedMemoryRanges pfn_FlushMappedMemoryRanges = nullptr;
    detail::PFN_InvalidateMappedMemoryRanges pfn_InvalidateMappedMemoryRanges = nullptr;
    detail::PFN_GetDeviceMemoryCommitment pfn_GetDeviceMemoryCommitment = nullptr;
    detail::PFN_GetBufferMemoryRequirements pfn_GetBufferMemoryRequirements = nullptr;
    detail::PFN_BindBufferMemory pfn_BindBufferMemory = nullptr;
    detail::PFN_GetImageMemoryRequirements pfn_GetImageMemoryRequirements = nullptr;
    detail::PFN_BindImageMemory pfn_BindImageMemory = nullptr;
    detail::PFN_GetImageSparseMemoryRequirements pfn_GetImageSparseMemoryRequirements = nullptr;
    detail::PFN_QueueBindSparse pfn_QueueBindSparse = nullptr;
    detail::PFN_CreateFence pfn_CreateFence = nullptr;
    detail::PFN_DestroyFence pfn_DestroyFence = nullptr;
    detail::PFN_ResetFences pfn_ResetFences = nullptr;
    detail::PFN_GetFenceStatus pfn_GetFenceStatus = nullptr;
    detail::PFN_WaitForFences pfn_WaitForFences = nullptr;
    detail::PFN_CreateSemaphore pfn_CreateSemaphore = nullptr;
    detail::PFN_DestroySemaphore pfn_DestroySemaphore = nullptr;
    detail::PFN_CreateEvent pfn_CreateEvent = nullptr;
    detail::PFN_DestroyEvent pfn_DestroyEvent = nullptr;
    detail::PFN_GetEventStatus pfn_GetEventStatus = nullptr;
    detail::PFN_SetEvent pfn_SetEvent = nullptr;
    detail::PFN_ResetEvent pfn_ResetEvent = nullptr;
    detail::PFN_CreateQueryPool pfn_CreateQueryPool = nullptr;
    detail::PFN_DestroyQueryPool pfn_DestroyQueryPool = nullptr;
    detail::PFN_GetQueryPoolResults pfn_GetQueryPoolResults = nullptr;
    detail::PFN_CreateBuffer pfn_CreateBuffer = nullptr;
    detail::PFN_DestroyBuffer pfn_DestroyBuffer = nullptr;
    detail::PFN_CreateBufferView pfn_CreateBufferView = nullptr;
    detail::PFN_DestroyBufferView pfn_DestroyBufferView = nullptr;
    detail::PFN_CreateImage pfn_CreateImage = nullptr;
    detail::PFN_DestroyImage pfn_DestroyImage = nullptr;
    detail::PFN_GetImageSubresourceLayout pfn_GetImageSubresourceLayout = nullptr;
    detail::PFN_CreateImageView pfn_CreateImageView = nullptr;
    detail::PFN_DestroyImageView pfn_DestroyImageView = nullptr;
    detail::PFN_CreateShaderModule pfn_CreateShaderModule = nullptr;
    detail::PFN_DestroyShaderModule pfn_DestroyShaderModule = nullptr;
    detail::PFN_CreatePipelineCache pfn_CreatePipelineCache = nullptr;
    detail::PFN_DestroyPipelineCache pfn_DestroyPipelineCache = nullptr;
    detail::PFN_GetPipelineCacheData pfn_GetPipelineCacheData = nullptr;
    detail::PFN_MergePipelineCaches pfn_MergePipelineCaches = nullptr;
    detail::PFN_CreateGraphicsPipelines pfn_CreateGraphicsPipelines = nullptr;
    detail::PFN_CreateComputePipelines pfn_CreateComputePipelines = nullptr;
    detail::PFN_DestroyPipeline pfn_DestroyPipeline = nullptr;
    detail::PFN_CreatePipelineLayout pfn_CreatePipelineLayout = nullptr;
    detail::PFN_DestroyPipelineLayout pfn_DestroyPipelineLayout = nullptr;
    detail::PFN_CreateSampler pfn_CreateSampler = nullptr;
    detail::PFN_DestroySampler pfn_DestroySampler = nullptr;
    detail::PFN_CreateDescriptorSetLayout pfn_CreateDescriptorSetLayout = nullptr;
    detail::PFN_DestroyDescriptorSetLayout pfn_DestroyDescriptorSetLayout = nullptr;
    detail::PFN_CreateDescriptorPool pfn_CreateDescriptorPool = nullptr;
    detail::PFN_DestroyDescriptorPool pfn_DestroyDescriptorPool = nullptr;
    detail::PFN_ResetDescriptorPool pfn_ResetDescriptorPool = nullptr;
    detail::PFN_AllocateDescriptorSets pfn_AllocateDescriptorSets = nullptr;
    detail::PFN_FreeDescriptorSets pfn_FreeDescriptorSets = nullptr;
    detail::PFN_UpdateDescriptorSets pfn_UpdateDescriptorSets = nullptr;
    detail::PFN_CreateFramebuffer pfn_CreateFramebuffer = nullptr;
    detail::PFN_DestroyFramebuffer pfn_DestroyFramebuffer = nullptr;
    detail::PFN_CreateRenderPass pfn_CreateRenderPass = nullptr;
    detail::PFN_DestroyRenderPass pfn_DestroyRenderPass = nullptr;
    detail::PFN_GetRenderAreaGranularity pfn_GetRenderAreaGranularity = nullptr;
    detail::PFN_CreateCommandPool pfn_CreateCommandPool = nullptr;
    detail::PFN_DestroyCommandPool pfn_DestroyCommandPool = nullptr;
    detail::PFN_ResetCommandPool pfn_ResetCommandPool = nullptr;
    detail::PFN_AllocateCommandBuffers pfn_AllocateCommandBuffers = nullptr;
    detail::PFN_FreeCommandBuffers pfn_FreeCommandBuffers = nullptr;
    detail::PFN_BeginCommandBuffer pfn_BeginCommandBuffer = nullptr;
    detail::PFN_EndCommandBuffer pfn_EndCommandBuffer = nullptr;
    detail::PFN_ResetCommandBuffer pfn_ResetCommandBuffer = nullptr;
    detail::PFN_CmdBindPipeline pfn_CmdBindPipeline = nullptr;
    detail::PFN_CmdSetViewport pfn_CmdSetViewport = nullptr;
    detail::PFN_CmdSetScissor pfn_CmdSetScissor = nullptr;
    detail::PFN_CmdSetLineWidth pfn_CmdSetLineWidth = nullptr;
    detail::PFN_CmdSetDepthBias pfn_CmdSetDepthBias = nullptr;
    detail::PFN_CmdSetBlendConstants pfn_CmdSetBlendConstants = nullptr;
    detail::PFN_CmdSetDepthBounds pfn_CmdSetDepthBounds = nullptr;
    detail::PFN_CmdSetStencilCompareMask pfn_CmdSetStencilCompareMask = nullptr;
    detail::PFN_CmdSetStencilWriteMask pfn_CmdSetStencilWriteMask = nullptr;
    detail::PFN_CmdSetStencilReference pfn_CmdSetStencilReference = nullptr;
    detail::PFN_CmdBindDescriptorSets pfn_CmdBindDescriptorSets = nullptr;
    detail::PFN_CmdBindIndexBuffer pfn_CmdBindIndexBuffer = nullptr;
    detail::PFN_CmdBindVertexBuffers pfn_CmdBindVertexBuffers = nullptr;
    detail::PFN_CmdDraw pfn_CmdDraw = nullptr;
    detail::PFN_CmdDrawIndexed pfn_CmdDrawIndexed = nullptr;
    detail::PFN_CmdDrawIndirect pfn_CmdDrawIndirect = nullptr;
    detail::PFN_CmdDrawIndexedIndirect pfn_CmdDrawIndexedIndirect = nullptr;
    detail::PFN_CmdDispatch pfn_CmdDispatch = nullptr;
    detail::PFN_CmdDispatchIndirect pfn_CmdDispatchIndirect = nullptr;
    detail::PFN_CmdCopyBuffer pfn_CmdCopyBuffer = nullptr;
    detail::PFN_CmdCopyImage pfn_CmdCopyImage = nullptr;
    detail::PFN_CmdBlitImage pfn_CmdBlitImage = nullptr;
    detail::PFN_CmdCopyBufferToImage pfn_CmdCopyBufferToImage = nullptr;
    detail::PFN_CmdCopyImageToBuffer pfn_CmdCopyImageToBuffer = nullptr;
    detail::PFN_CmdUpdateBuffer pfn_CmdUpdateBuffer = nullptr;
    detail::PFN_CmdFillBuffer pfn_CmdFillBuffer = nullptr;
    detail::PFN_CmdClearColorImage pfn_CmdClearColorImage = nullptr;
    detail::PFN_CmdClearDepthStencilImage pfn_CmdClearDepthStencilImage = nullptr;
    detail::PFN_CmdClearAttachments pfn_CmdClearAttachments = nullptr;
    detail::PFN_CmdResolveImage pfn_CmdResolveImage = nullptr;
    detail::PFN_CmdSetEvent pfn_CmdSetEvent = nullptr;
    detail::PFN_CmdResetEvent pfn_CmdResetEvent = nullptr;
    detail::PFN_CmdWaitEvents pfn_CmdWaitEvents = nullptr;
    detail::PFN_CmdPipelineBarrier pfn_CmdPipelineBarrier = nullptr;
    detail::PFN_CmdBeginQuery pfn_CmdBeginQuery = nullptr;
    detail::PFN_CmdEndQuery pfn_CmdEndQuery = nullptr;
    detail::PFN_CmdResetQueryPool pfn_CmdResetQueryPool = nullptr;
    detail::PFN_CmdWriteTimestamp pfn_CmdWriteTimestamp = nullptr;
    detail::PFN_CmdCopyQueryPoolResults pfn_CmdCopyQueryPoolResults = nullptr;
    detail::PFN_CmdPushConstants pfn_CmdPushConstants = nullptr;
    detail::PFN_CmdBeginRenderPass pfn_CmdBeginRenderPass = nullptr;
    detail::PFN_CmdNextSubpass pfn_CmdNextSubpass = nullptr;
    detail::PFN_CmdEndRenderPass pfn_CmdEndRenderPass = nullptr;
    detail::PFN_CmdExecuteCommands pfn_CmdExecuteCommands = nullptr;
    detail::PFN_BindBufferMemory2 pfn_BindBufferMemory2 = nullptr;
    detail::PFN_BindImageMemory2 pfn_BindImageMemory2 = nullptr;
    detail::PFN_GetDeviceGroupPeerMemoryFeatures pfn_GetDeviceGroupPeerMemoryFeatures = nullptr;
    detail::PFN_CmdSetDeviceMask pfn_CmdSetDeviceMask = nullptr;
    detail::PFN_CmdDispatchBase pfn_CmdDispatchBase = nullptr;
    detail::PFN_GetBufferMemoryRequirements2 pfn_GetBufferMemoryRequirements2 = nullptr;
    detail::PFN_GetImageMemoryRequirements2 pfn_GetImageMemoryRequirements2 = nullptr;
    detail::PFN_GetImageSparseMemoryRequirements2 pfn_GetImageSparseMemoryRequirements2 = nullptr;
    detail::PFN_TrimCommandPool pfn_TrimCommandPool = nullptr;
    detail::PFN_GetDeviceQueue2 pfn_GetDeviceQueue2 = nullptr;
    detail::PFN_CreateSamplerYcbcrConversion pfn_CreateSamplerYcbcrConversion = nullptr;
    detail::PFN_DestroySamplerYcbcrConversion pfn_DestroySamplerYcbcrConversion = nullptr;
    detail::PFN_CreateDescriptorUpdateTemplate pfn_CreateDescriptorUpdateTemplate = nullptr;
    detail::PFN_DestroyDescriptorUpdateTemplate pfn_DestroyDescriptorUpdateTemplate = nullptr;
    detail::PFN_UpdateDescriptorSetWithTemplate pfn_UpdateDescriptorSetWithTemplate = nullptr;
    detail::PFN_GetDescriptorSetLayoutSupport pfn_GetDescriptorSetLayoutSupport = nullptr;
    detail::PFN_CmdDrawIndirectCount pfn_CmdDrawIndirectCount = nullptr;
    detail::PFN_CmdDrawIndexedIndirectCount pfn_CmdDrawIndexedIndirectCount = nullptr;
    detail::PFN_CreateRenderPass2 pfn_CreateRenderPass2 = nullptr;
    detail::PFN_CmdBeginRenderPass2 pfn_CmdBeginRenderPass2 = nullptr;
    detail::PFN_CmdNextSubpass2 pfn_CmdNextSubpass2 = nullptr;
    detail::PFN_CmdEndRenderPass2 pfn_CmdEndRenderPass2 = nullptr;
    detail::PFN_ResetQueryPool pfn_ResetQueryPool = nullptr;
    detail::PFN_GetSemaphoreCounterValue pfn_GetSemaphoreCounterValue = nullptr;
    detail::PFN_WaitSemaphores pfn_WaitSemaphores = nullptr;
    detail::PFN_SignalSemaphore pfn_SignalSemaphore = nullptr;
    detail::PFN_GetBufferOpaqueCaptureAddress pfn_GetBufferOpaqueCaptureAddress = nullptr;
    detail::PFN_GetBufferDeviceAddress pfn_GetBufferDeviceAddress = nullptr;
    detail::PFN_GetDeviceMemoryOpaqueCaptureAddress pfn_GetDeviceMemoryOpaqueCaptureAddress = nullptr;
    detail::PFN_CreateSwapchainKHR pfn_CreateSwapchainKHR = nullptr;
    detail::PFN_DestroySwapchainKHR pfn_DestroySwapchainKHR = nullptr;
    detail::PFN_GetSwapchainImagesKHR pfn_GetSwapchainImagesKHR = nullptr;
    detail::PFN_AcquireNextImageKHR pfn_AcquireNextImageKHR = nullptr;
    detail::PFN_QueuePresentKHR pfn_QueuePresentKHR = nullptr;
    detail::PFN_GetDeviceGroupPresentCapabilitiesKHR pfn_GetDeviceGroupPresentCapabilitiesKHR = nullptr;
    detail::PFN_GetDeviceGroupSurfacePresentModesKHR pfn_GetDeviceGroupSurfacePresentModesKHR = nullptr;
    detail::PFN_AcquireNextImage2KHR pfn_AcquireNextImage2KHR = nullptr;
    detail::PFN_CreateSharedSwapchainsKHR pfn_CreateSharedSwapchainsKHR = nullptr;
    detail::PFN_DebugMarkerSetObjectNameEXT pfn_DebugMarkerSetObjectNameEXT = nullptr;
    detail::PFN_DebugMarkerSetObjectTagEXT pfn_DebugMarkerSetObjectTagEXT = nullptr;
    detail::PFN_CmdDebugMarkerBeginEXT pfn_CmdDebugMarkerBeginEXT = nullptr;
    detail::PFN_CmdDebugMarkerEndEXT pfn_CmdDebugMarkerEndEXT = nullptr;
    detail::PFN_CmdDebugMarkerInsertEXT pfn_CmdDebugMarkerInsertEXT = nullptr;
    detail::PFN_CmdBindTransformFeedbackBuffersEXT pfn_CmdBindTransformFeedbackBuffersEXT = nullptr;
    detail::PFN_CmdBeginTransformFeedbackEXT pfn_CmdBeginTransformFeedbackEXT = nullptr;
    detail::PFN_CmdEndTransformFeedbackEXT pfn_CmdEndTransformFeedbackEXT = nullptr;
    detail::PFN_CmdBeginQueryIndexedEXT pfn_CmdBeginQueryIndexedEXT = nullptr;
    detail::PFN_CmdEndQueryIndexedEXT pfn_CmdEndQueryIndexedEXT = nullptr;
    detail::PFN_CmdDrawIndirectByteCountEXT pfn_CmdDrawIndirectByteCountEXT = nullptr;
    detail::PFN_GetImageViewHandleNVX pfn_GetImageViewHandleNVX = nullptr;
    detail::PFN_GetImageViewAddressNVX pfn_GetImageViewAddressNVX = nullptr;
    detail::PFN_GetShaderInfoAMD pfn_GetShaderInfoAMD = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetMemoryWin32HandleNV pfn_GetMemoryWin32HandleNV = nullptr;
    detail::PFN_GetMemoryWin32HandleKHR pfn_GetMemoryWin32HandleKHR = nullptr;
    detail::PFN_GetMemoryWin32HandlePropertiesKHR pfn_GetMemoryWin32HandlePropertiesKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetMemoryFdKHR pfn_GetMemoryFdKHR = nullptr;
    detail::PFN_GetMemoryFdPropertiesKHR pfn_GetMemoryFdPropertiesKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetSemaphoreWin32HandleKHR pfn_GetSemaphoreWin32HandleKHR = nullptr;
    detail::PFN_ImportSemaphoreWin32HandleKHR pfn_ImportSemaphoreWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetSemaphoreFdKHR pfn_GetSemaphoreFdKHR = nullptr;
    detail::PFN_ImportSemaphoreFdKHR pfn_ImportSemaphoreFdKHR = nullptr;
    detail::PFN_CmdPushDescriptorSetKHR pfn_CmdPushDescriptorSetKHR = nullptr;
    detail::PFN_CmdPushDescriptorSetWithTemplateKHR pfn_CmdPushDescriptorSetWithTemplateKHR = nullptr;
    detail::PFN_CmdBeginConditionalRenderingEXT pfn_CmdBeginConditionalRenderingEXT = nullptr;
    detail::PFN_CmdEndConditionalRenderingEXT pfn_CmdEndConditionalRenderingEXT = nullptr;
    detail::PFN_CmdSetViewportWScalingNV pfn_CmdSetViewportWScalingNV = nullptr;
    detail::PFN_DisplayPowerControlEXT pfn_DisplayPowerControlEXT = nullptr;
    detail::PFN_RegisterDeviceEventEXT pfn_RegisterDeviceEventEXT = nullptr;
    detail::PFN_RegisterDisplayEventEXT pfn_RegisterDisplayEventEXT = nullptr;
    detail::PFN_GetSwapchainCounterEXT pfn_GetSwapchainCounterEXT = nullptr;
    detail::PFN_GetRefreshCycleDurationGOOGLE pfn_GetRefreshCycleDurationGOOGLE = nullptr;
    detail::PFN_GetPastPresentationTimingGOOGLE pfn_GetPastPresentationTimingGOOGLE = nullptr;
    detail::PFN_CmdSetDiscardRectangleEXT pfn_CmdSetDiscardRectangleEXT = nullptr;
    detail::PFN_SetHdrMetadataEXT pfn_SetHdrMetadataEXT = nullptr;
    detail::PFN_GetSwapchainStatusKHR pfn_GetSwapchainStatusKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetFenceWin32HandleKHR pfn_GetFenceWin32HandleKHR = nullptr;
    detail::PFN_ImportFenceWin32HandleKHR pfn_ImportFenceWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_GetFenceFdKHR pfn_GetFenceFdKHR = nullptr;
    detail::PFN_ImportFenceFdKHR pfn_ImportFenceFdKHR = nullptr;
    detail::PFN_AcquireProfilingLockKHR pfn_AcquireProfilingLockKHR = nullptr;
    detail::PFN_ReleaseProfilingLockKHR pfn_ReleaseProfilingLockKHR = nullptr;
    detail::PFN_SetDebugUtilsObjectNameEXT pfn_SetDebugUtilsObjectNameEXT = nullptr;
    detail::PFN_SetDebugUtilsObjectTagEXT pfn_SetDebugUtilsObjectTagEXT = nullptr;
    detail::PFN_QueueBeginDebugUtilsLabelEXT pfn_QueueBeginDebugUtilsLabelEXT = nullptr;
    detail::PFN_QueueEndDebugUtilsLabelEXT pfn_QueueEndDebugUtilsLabelEXT = nullptr;
    detail::PFN_QueueInsertDebugUtilsLabelEXT pfn_QueueInsertDebugUtilsLabelEXT = nullptr;
    detail::PFN_CmdBeginDebugUtilsLabelEXT pfn_CmdBeginDebugUtilsLabelEXT = nullptr;
    detail::PFN_CmdEndDebugUtilsLabelEXT pfn_CmdEndDebugUtilsLabelEXT = nullptr;
    detail::PFN_CmdInsertDebugUtilsLabelEXT pfn_CmdInsertDebugUtilsLabelEXT = nullptr;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    detail::PFN_GetAndroidHardwareBufferPropertiesANDROID pfn_GetAndroidHardwareBufferPropertiesANDROID = nullptr;
    detail::PFN_GetMemoryAndroidHardwareBufferANDROID pfn_GetMemoryAndroidHardwareBufferANDROID = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    detail::PFN_CmdSetSampleLocationsEXT pfn_CmdSetSampleLocationsEXT = nullptr;
    detail::PFN_DestroyAccelerationStructureKHR pfn_DestroyAccelerationStructureKHR = nullptr;
    detail::PFN_CmdCopyAccelerationStructureKHR pfn_CmdCopyAccelerationStructureKHR = nullptr;
    detail::PFN_CopyAccelerationStructureKHR pfn_CopyAccelerationStructureKHR = nullptr;
    detail::PFN_CmdCopyAccelerationStructureToMemoryKHR pfn_CmdCopyAccelerationStructureToMemoryKHR = nullptr;
    detail::PFN_CopyAccelerationStructureToMemoryKHR pfn_CopyAccelerationStructureToMemoryKHR = nullptr;
    detail::PFN_CmdCopyMemoryToAccelerationStructureKHR pfn_CmdCopyMemoryToAccelerationStructureKHR = nullptr;
    detail::PFN_CopyMemoryToAccelerationStructureKHR pfn_CopyMemoryToAccelerationStructureKHR = nullptr;
    detail::PFN_CmdWriteAccelerationStructuresPropertiesKHR pfn_CmdWriteAccelerationStructuresPropertiesKHR = nullptr;
    detail::PFN_WriteAccelerationStructuresPropertiesKHR pfn_WriteAccelerationStructuresPropertiesKHR = nullptr;
    detail::PFN_GetDeviceAccelerationStructureCompatibilityKHR pfn_GetDeviceAccelerationStructureCompatibilityKHR = nullptr;
    detail::PFN_CreateAccelerationStructureKHR pfn_CreateAccelerationStructureKHR = nullptr;
    detail::PFN_CmdBuildAccelerationStructuresKHR pfn_CmdBuildAccelerationStructuresKHR = nullptr;
    detail::PFN_CmdBuildAccelerationStructuresIndirectKHR pfn_CmdBuildAccelerationStructuresIndirectKHR = nullptr;
    detail::PFN_BuildAccelerationStructuresKHR pfn_BuildAccelerationStructuresKHR = nullptr;
    detail::PFN_GetAccelerationStructureDeviceAddressKHR pfn_GetAccelerationStructureDeviceAddressKHR = nullptr;
    detail::PFN_GetAccelerationStructureBuildSizesKHR pfn_GetAccelerationStructureBuildSizesKHR = nullptr;
    detail::PFN_CmdTraceRaysKHR pfn_CmdTraceRaysKHR = nullptr;
    detail::PFN_GetRayTracingShaderGroupHandlesKHR pfn_GetRayTracingShaderGroupHandlesKHR = nullptr;
    detail::PFN_GetRayTracingCaptureReplayShaderGroupHandlesKHR pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
    detail::PFN_CreateRayTracingPipelinesKHR pfn_CreateRayTracingPipelinesKHR = nullptr;
    detail::PFN_CmdTraceRaysIndirectKHR pfn_CmdTraceRaysIndirectKHR = nullptr;
    detail::PFN_GetRayTracingShaderGroupStackSizeKHR pfn_GetRayTracingShaderGroupStackSizeKHR = nullptr;
    detail::PFN_CmdSetRayTracingPipelineStackSizeKHR pfn_CmdSetRayTracingPipelineStackSizeKHR = nullptr;
    detail::PFN_GetImageDrmFormatModifierPropertiesEXT pfn_GetImageDrmFormatModifierPropertiesEXT = nullptr;
    detail::PFN_CreateValidationCacheEXT pfn_CreateValidationCacheEXT = nullptr;
    detail::PFN_DestroyValidationCacheEXT pfn_DestroyValidationCacheEXT = nullptr;
    detail::PFN_GetValidationCacheDataEXT pfn_GetValidationCacheDataEXT = nullptr;
    detail::PFN_MergeValidationCachesEXT pfn_MergeValidationCachesEXT = nullptr;
    detail::PFN_CmdBindShadingRateImageNV pfn_CmdBindShadingRateImageNV = nullptr;
    detail::PFN_CmdSetViewportShadingRatePaletteNV pfn_CmdSetViewportShadingRatePaletteNV = nullptr;
    detail::PFN_CmdSetCoarseSampleOrderNV pfn_CmdSetCoarseSampleOrderNV = nullptr;
    detail::PFN_CompileDeferredNV pfn_CompileDeferredNV = nullptr;
    detail::PFN_CreateAccelerationStructureNV pfn_CreateAccelerationStructureNV = nullptr;
    detail::PFN_DestroyAccelerationStructureNV pfn_DestroyAccelerationStructureNV = nullptr;
    detail::PFN_GetAccelerationStructureMemoryRequirementsNV pfn_GetAccelerationStructureMemoryRequirementsNV = nullptr;
    detail::PFN_BindAccelerationStructureMemoryNV pfn_BindAccelerationStructureMemoryNV = nullptr;
    detail::PFN_CmdCopyAccelerationStructureNV pfn_CmdCopyAccelerationStructureNV = nullptr;
    detail::PFN_CmdWriteAccelerationStructuresPropertiesNV pfn_CmdWriteAccelerationStructuresPropertiesNV = nullptr;
    detail::PFN_CmdBuildAccelerationStructureNV pfn_CmdBuildAccelerationStructureNV = nullptr;
    detail::PFN_CmdTraceRaysNV pfn_CmdTraceRaysNV = nullptr;
    detail::PFN_GetAccelerationStructureHandleNV pfn_GetAccelerationStructureHandleNV = nullptr;
    detail::PFN_CreateRayTracingPipelinesNV pfn_CreateRayTracingPipelinesNV = nullptr;
    detail::PFN_GetMemoryHostPointerPropertiesEXT pfn_GetMemoryHostPointerPropertiesEXT = nullptr;
    detail::PFN_CmdWriteBufferMarkerAMD pfn_CmdWriteBufferMarkerAMD = nullptr;
    detail::PFN_GetCalibratedTimestampsEXT pfn_GetCalibratedTimestampsEXT = nullptr;
    detail::PFN_CmdDrawMeshTasksNV pfn_CmdDrawMeshTasksNV = nullptr;
    detail::PFN_CmdDrawMeshTasksIndirectNV pfn_CmdDrawMeshTasksIndirectNV = nullptr;
    detail::PFN_CmdDrawMeshTasksIndirectCountNV pfn_CmdDrawMeshTasksIndirectCountNV = nullptr;
    detail::PFN_CmdSetExclusiveScissorNV pfn_CmdSetExclusiveScissorNV = nullptr;
    detail::PFN_CmdSetCheckpointNV pfn_CmdSetCheckpointNV = nullptr;
    detail::PFN_GetQueueCheckpointDataNV pfn_GetQueueCheckpointDataNV = nullptr;
    detail::PFN_InitializePerformanceApiINTEL pfn_InitializePerformanceApiINTEL = nullptr;
    detail::PFN_UninitializePerformanceApiINTEL pfn_UninitializePerformanceApiINTEL = nullptr;
    detail::PFN_CmdSetPerformanceMarkerINTEL pfn_CmdSetPerformanceMarkerINTEL = nullptr;
    detail::PFN_CmdSetPerformanceStreamMarkerINTEL pfn_CmdSetPerformanceStreamMarkerINTEL = nullptr;
    detail::PFN_CmdSetPerformanceOverrideINTEL pfn_CmdSetPerformanceOverrideINTEL = nullptr;
    detail::PFN_AcquirePerformanceConfigurationINTEL pfn_AcquirePerformanceConfigurationINTEL = nullptr;
    detail::PFN_ReleasePerformanceConfigurationINTEL pfn_ReleasePerformanceConfigurationINTEL = nullptr;
    detail::PFN_QueueSetPerformanceConfigurationINTEL pfn_QueueSetPerformanceConfigurationINTEL = nullptr;
    detail::PFN_GetPerformanceParameterINTEL pfn_GetPerformanceParameterINTEL = nullptr;
    detail::PFN_SetLocalDimmingAMD pfn_SetLocalDimmingAMD = nullptr;
    detail::PFN_CmdSetFragmentShadingRateKHR pfn_CmdSetFragmentShadingRateKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_AcquireFullScreenExclusiveModeEXT pfn_AcquireFullScreenExclusiveModeEXT = nullptr;
    detail::PFN_ReleaseFullScreenExclusiveModeEXT pfn_ReleaseFullScreenExclusiveModeEXT = nullptr;
    detail::PFN_GetDeviceGroupSurfacePresentModes2EXT pfn_GetDeviceGroupSurfacePresentModes2EXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    detail::PFN_CmdSetLineStippleEXT pfn_CmdSetLineStippleEXT = nullptr;
    detail::PFN_CmdSetCullModeEXT pfn_CmdSetCullModeEXT = nullptr;
    detail::PFN_CmdSetFrontFaceEXT pfn_CmdSetFrontFaceEXT = nullptr;
    detail::PFN_CmdSetPrimitiveTopologyEXT pfn_CmdSetPrimitiveTopologyEXT = nullptr;
    detail::PFN_CmdSetViewportWithCountEXT pfn_CmdSetViewportWithCountEXT = nullptr;
    detail::PFN_CmdSetScissorWithCountEXT pfn_CmdSetScissorWithCountEXT = nullptr;
    detail::PFN_CmdBindVertexBuffers2EXT pfn_CmdBindVertexBuffers2EXT = nullptr;
    detail::PFN_CmdSetDepthTestEnableEXT pfn_CmdSetDepthTestEnableEXT = nullptr;
    detail::PFN_CmdSetDepthWriteEnableEXT pfn_CmdSetDepthWriteEnableEXT = nullptr;
    detail::PFN_CmdSetDepthCompareOpEXT pfn_CmdSetDepthCompareOpEXT = nullptr;
    detail::PFN_CmdSetDepthBoundsTestEnableEXT pfn_CmdSetDepthBoundsTestEnableEXT = nullptr;
    detail::PFN_CmdSetStencilTestEnableEXT pfn_CmdSetStencilTestEnableEXT = nullptr;
    detail::PFN_CmdSetStencilOpEXT pfn_CmdSetStencilOpEXT = nullptr;
    detail::PFN_CreateDeferredOperationKHR pfn_CreateDeferredOperationKHR = nullptr;
    detail::PFN_DestroyDeferredOperationKHR pfn_DestroyDeferredOperationKHR = nullptr;
    detail::PFN_GetDeferredOperationMaxConcurrencyKHR pfn_GetDeferredOperationMaxConcurrencyKHR = nullptr;
    detail::PFN_GetDeferredOperationResultKHR pfn_GetDeferredOperationResultKHR = nullptr;
    detail::PFN_DeferredOperationJoinKHR pfn_DeferredOperationJoinKHR = nullptr;
    detail::PFN_GetPipelineExecutablePropertiesKHR pfn_GetPipelineExecutablePropertiesKHR = nullptr;
    detail::PFN_GetPipelineExecutableStatisticsKHR pfn_GetPipelineExecutableStatisticsKHR = nullptr;
    detail::PFN_GetPipelineExecutableInternalRepresentationsKHR pfn_GetPipelineExecutableInternalRepresentationsKHR = nullptr;
    detail::PFN_CmdExecuteGeneratedCommandsNV pfn_CmdExecuteGeneratedCommandsNV = nullptr;
    detail::PFN_CmdPreprocessGeneratedCommandsNV pfn_CmdPreprocessGeneratedCommandsNV = nullptr;
    detail::PFN_CmdBindPipelineShaderGroupNV pfn_CmdBindPipelineShaderGroupNV = nullptr;
    detail::PFN_GetGeneratedCommandsMemoryRequirementsNV pfn_GetGeneratedCommandsMemoryRequirementsNV = nullptr;
    detail::PFN_CreateIndirectCommandsLayoutNV pfn_CreateIndirectCommandsLayoutNV = nullptr;
    detail::PFN_DestroyIndirectCommandsLayoutNV pfn_DestroyIndirectCommandsLayoutNV = nullptr;
    detail::PFN_CreatePrivateDataSlotEXT pfn_CreatePrivateDataSlotEXT = nullptr;
    detail::PFN_DestroyPrivateDataSlotEXT pfn_DestroyPrivateDataSlotEXT = nullptr;
    detail::PFN_SetPrivateDataEXT pfn_SetPrivateDataEXT = nullptr;
    detail::PFN_GetPrivateDataEXT pfn_GetPrivateDataEXT = nullptr;
    detail::PFN_CmdSetFragmentShadingRateEnumNV pfn_CmdSetFragmentShadingRateEnumNV = nullptr;
    detail::PFN_CmdCopyBuffer2KHR pfn_CmdCopyBuffer2KHR = nullptr;
    detail::PFN_CmdCopyImage2KHR pfn_CmdCopyImage2KHR = nullptr;
    detail::PFN_CmdBlitImage2KHR pfn_CmdBlitImage2KHR = nullptr;
    detail::PFN_CmdCopyBufferToImage2KHR pfn_CmdCopyBufferToImage2KHR = nullptr;
    detail::PFN_CmdCopyImageToBuffer2KHR pfn_CmdCopyImageToBuffer2KHR = nullptr;
    detail::PFN_CmdResolveImage2KHR pfn_CmdResolveImage2KHR = nullptr;
void DestroyDevice(const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDevice(device,
        pAllocator);
}
[[nodiscard]] Queue GetDeviceQueue(uint32_t queueFamilyIndex, 
    uint32_t queueIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Queue pQueue;
    pfn_GetDeviceQueue(device,
        queueFamilyIndex,
        queueIndex,
        &pQueue);
    return pQueue;
}
[[nodiscard]] Result QueueSubmit(Queue queue, 
    detail::span<const SubmitInfo> Submits, 
    Fence fence = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t submitCount = Submits.size();
    return pfn_QueueSubmit(queue,
        submitCount,
        Submits.data(),
        fence);
}
[[nodiscard]] Result QueueWaitIdle(Queue queue) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_QueueWaitIdle(queue);
}
[[nodiscard]] Result DeviceWaitIdle() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_DeviceWaitIdle(device);
}
[[nodiscard]] expected<DeviceMemory> AllocateMemory(const MemoryAllocateInfo&  pAllocateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceMemory pMemory;
        Result result = pfn_AllocateMemory(device,
        &pAllocateInfo,
        pAllocator,
        &pMemory);
    return expected<DeviceMemory>(pMemory, result);
}
void FreeMemory(DeviceMemory memory = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_FreeMemory(device,
        memory,
        pAllocator);
}
[[nodiscard]] expected<void*> MapMemory(DeviceMemory memory, 
    DeviceSize offset, 
    DeviceSize size, 
    MemoryMapFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    void* ppData;
        Result result = pfn_MapMemory(device,
        memory,
        offset,
        size,
        flags,
        &ppData);
    return expected<void*>(ppData, result);
}
void UnmapMemory(DeviceMemory memory) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_UnmapMemory(device,
        memory);
}
[[nodiscard]] Result FlushMappedMemoryRanges(detail::span<const MappedMemoryRange> MemoryRanges) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t memoryRangeCount = MemoryRanges.size();
    return pfn_FlushMappedMemoryRanges(device,
        memoryRangeCount,
        MemoryRanges.data());
}
[[nodiscard]] Result InvalidateMappedMemoryRanges(detail::span<const MappedMemoryRange> MemoryRanges) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t memoryRangeCount = MemoryRanges.size();
    return pfn_InvalidateMappedMemoryRanges(device,
        memoryRangeCount,
        MemoryRanges.data());
}
[[nodiscard]] DeviceSize GetDeviceMemoryCommitment(DeviceMemory memory) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceSize pCommittedMemoryInBytes;
    pfn_GetDeviceMemoryCommitment(device,
        memory,
        &pCommittedMemoryInBytes);
    return pCommittedMemoryInBytes;
}
[[nodiscard]] MemoryRequirements GetBufferMemoryRequirements(Buffer buffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements pMemoryRequirements;
    pfn_GetBufferMemoryRequirements(device,
        buffer,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] Result BindBufferMemory(Buffer buffer, 
    DeviceMemory memory, 
    DeviceSize memoryOffset) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_BindBufferMemory(device,
        buffer,
        memory,
        memoryOffset);
}
[[nodiscard]] MemoryRequirements GetImageMemoryRequirements(Image image) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements pMemoryRequirements;
    pfn_GetImageMemoryRequirements(device,
        image,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] Result BindImageMemory(Image image, 
    DeviceMemory memory, 
    DeviceSize memoryOffset) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_BindImageMemory(device,
        image,
        memory,
        memoryOffset);
}
[[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements> GetImageSparseMemoryRequirements(Image image) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pSparseMemoryRequirementCount = 0;
    pfn_GetImageSparseMemoryRequirements(device,
        image,
        &pSparseMemoryRequirementCount,
        nullptr);
    detail::fixed_vector<SparseImageMemoryRequirements> pSparseMemoryRequirements{pSparseMemoryRequirementCount};
pfn_GetImageSparseMemoryRequirements(device,
        image,
        &pSparseMemoryRequirementCount,
        pSparseMemoryRequirements.data());
    if (pSparseMemoryRequirementCount < pSparseMemoryRequirements.size()) pSparseMemoryRequirements.shrink(pSparseMemoryRequirementCount);
    return pSparseMemoryRequirements;
}
[[nodiscard]] Result QueueBindSparse(Queue queue, 
    detail::span<const BindSparseInfo> BindInfo, 
    Fence fence = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindInfoCount = BindInfo.size();
    return pfn_QueueBindSparse(queue,
        bindInfoCount,
        BindInfo.data(),
        fence);
}
[[nodiscard]] expected<Fence> CreateFence(const FenceCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Fence pFence;
        Result result = pfn_CreateFence(device,
        &pCreateInfo,
        pAllocator,
        &pFence);
    return expected<Fence>(pFence, result);
}
void DestroyFence(Fence fence = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyFence(device,
        fence,
        pAllocator);
}
[[nodiscard]] Result ResetFences(detail::span<const Fence> Fences) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t fenceCount = Fences.size();
    return pfn_ResetFences(device,
        fenceCount,
        Fences.data());
}
[[nodiscard]] Result GetFenceStatus(Fence fence) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetFenceStatus(device,
        fence);
}
[[nodiscard]] Result WaitForFences(detail::span<const Fence> Fences, 
    Bool32 waitAll, 
    uint64_t timeout) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t fenceCount = Fences.size();
    return pfn_WaitForFences(device,
        fenceCount,
        Fences.data(),
        waitAll,
        timeout);
}
[[nodiscard]] expected<Semaphore> CreateSemaphore(const SemaphoreCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Semaphore pSemaphore;
        Result result = pfn_CreateSemaphore(device,
        &pCreateInfo,
        pAllocator,
        &pSemaphore);
    return expected<Semaphore>(pSemaphore, result);
}
void DestroySemaphore(Semaphore semaphore = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroySemaphore(device,
        semaphore,
        pAllocator);
}
[[nodiscard]] expected<Event> CreateEvent(const EventCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Event pEvent;
        Result result = pfn_CreateEvent(device,
        &pCreateInfo,
        pAllocator,
        &pEvent);
    return expected<Event>(pEvent, result);
}
void DestroyEvent(Event event = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyEvent(device,
        event,
        pAllocator);
}
[[nodiscard]] Result GetEventStatus(Event event) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetEventStatus(device,
        event);
}
[[nodiscard]] Result SetEvent(Event event) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_SetEvent(device,
        event);
}
[[nodiscard]] Result ResetEvent(Event event) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ResetEvent(device,
        event);
}
[[nodiscard]] expected<QueryPool> CreateQueryPool(const QueryPoolCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    QueryPool pQueryPool;
        Result result = pfn_CreateQueryPool(device,
        &pCreateInfo,
        pAllocator,
        &pQueryPool);
    return expected<QueryPool>(pQueryPool, result);
}
void DestroyQueryPool(QueryPool queryPool = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyQueryPool(device,
        queryPool,
        pAllocator);
}
[[nodiscard]] Result GetQueryPoolResults(QueryPool queryPool, 
    uint32_t firstQuery, 
    uint32_t queryCount, 
    detail::span<std::byte> Data, 
    DeviceSize stride, 
    QueryResultFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t dataSize = Data.size();
    return pfn_GetQueryPoolResults(device,
        queryPool,
        firstQuery,
        queryCount,
        dataSize,
        Data.data(),
        stride,
        flags);
}
[[nodiscard]] expected<Buffer> CreateBuffer(const BufferCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Buffer pBuffer;
        Result result = pfn_CreateBuffer(device,
        &pCreateInfo,
        pAllocator,
        &pBuffer);
    return expected<Buffer>(pBuffer, result);
}
void DestroyBuffer(Buffer buffer = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyBuffer(device,
        buffer,
        pAllocator);
}
[[nodiscard]] expected<BufferView> CreateBufferView(const BufferViewCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    BufferView pView;
        Result result = pfn_CreateBufferView(device,
        &pCreateInfo,
        pAllocator,
        &pView);
    return expected<BufferView>(pView, result);
}
void DestroyBufferView(BufferView bufferView = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyBufferView(device,
        bufferView,
        pAllocator);
}
[[nodiscard]] expected<Image> CreateImage(const ImageCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Image pImage;
        Result result = pfn_CreateImage(device,
        &pCreateInfo,
        pAllocator,
        &pImage);
    return expected<Image>(pImage, result);
}
void DestroyImage(Image image = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyImage(device,
        image,
        pAllocator);
}
[[nodiscard]] SubresourceLayout GetImageSubresourceLayout(Image image, 
    const ImageSubresource&  pSubresource) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SubresourceLayout pLayout;
    pfn_GetImageSubresourceLayout(device,
        image,
        &pSubresource,
        &pLayout);
    return pLayout;
}
[[nodiscard]] expected<ImageView> CreateImageView(const ImageViewCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ImageView pView;
        Result result = pfn_CreateImageView(device,
        &pCreateInfo,
        pAllocator,
        &pView);
    return expected<ImageView>(pView, result);
}
void DestroyImageView(ImageView imageView = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyImageView(device,
        imageView,
        pAllocator);
}
[[nodiscard]] expected<ShaderModule> CreateShaderModule(const ShaderModuleCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ShaderModule pShaderModule;
        Result result = pfn_CreateShaderModule(device,
        &pCreateInfo,
        pAllocator,
        &pShaderModule);
    return expected<ShaderModule>(pShaderModule, result);
}
void DestroyShaderModule(ShaderModule shaderModule = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyShaderModule(device,
        shaderModule,
        pAllocator);
}
[[nodiscard]] expected<PipelineCache> CreatePipelineCache(const PipelineCacheCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PipelineCache pPipelineCache;
        Result result = pfn_CreatePipelineCache(device,
        &pCreateInfo,
        pAllocator,
        &pPipelineCache);
    return expected<PipelineCache>(pPipelineCache, result);
}
void DestroyPipelineCache(PipelineCache pipelineCache = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyPipelineCache(device,
        pipelineCache,
        pAllocator);
}
[[nodiscard]] expected<detail::fixed_vector<void*>> GetPipelineCacheData(PipelineCache pipelineCache) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t pDataSize = 0;
        Result result = pfn_GetPipelineCacheData(device,
        pipelineCache,
        &pDataSize,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
    detail::fixed_vector<void*> pData{pDataSize};
    result = pfn_GetPipelineCacheData(device,
        pipelineCache,
        &pDataSize,
        pData.data());
    if (pDataSize < pData.size()) pData.shrink(pDataSize);
    return expected(std::move(pData), result);
}
[[nodiscard]] Result MergePipelineCaches(PipelineCache dstCache, 
    detail::span<const PipelineCache> SrcCaches) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t srcCacheCount = SrcCaches.size();
    return pfn_MergePipelineCaches(device,
        dstCache,
        srcCacheCount,
        SrcCaches.data());
}
[[nodiscard]] expected<detail::fixed_vector<Pipeline>> CreateGraphicsPipelines(PipelineCache pipelineCache, 
    detail::span<const GraphicsPipelineCreateInfo> CreateInfos, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t createInfoCount = CreateInfos.size();
    detail::fixed_vector<Pipeline> pPipelines{createInfoCount};
    Result result = pfn_CreateGraphicsPipelines(device,
        pipelineCache,
        createInfoCount,
        CreateInfos.data(),
        pAllocator,
        pPipelines.data());
    return expected<detail::fixed_vector<Pipeline>>(std::move(pPipelines), result);
}
[[nodiscard]] expected<detail::fixed_vector<Pipeline>> CreateComputePipelines(PipelineCache pipelineCache, 
    detail::span<const ComputePipelineCreateInfo> CreateInfos, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t createInfoCount = CreateInfos.size();
    detail::fixed_vector<Pipeline> pPipelines{createInfoCount};
    Result result = pfn_CreateComputePipelines(device,
        pipelineCache,
        createInfoCount,
        CreateInfos.data(),
        pAllocator,
        pPipelines.data());
    return expected<detail::fixed_vector<Pipeline>>(std::move(pPipelines), result);
}
void DestroyPipeline(Pipeline pipeline = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyPipeline(device,
        pipeline,
        pAllocator);
}
[[nodiscard]] expected<PipelineLayout> CreatePipelineLayout(const PipelineLayoutCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PipelineLayout pPipelineLayout;
        Result result = pfn_CreatePipelineLayout(device,
        &pCreateInfo,
        pAllocator,
        &pPipelineLayout);
    return expected<PipelineLayout>(pPipelineLayout, result);
}
void DestroyPipelineLayout(PipelineLayout pipelineLayout = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyPipelineLayout(device,
        pipelineLayout,
        pAllocator);
}
[[nodiscard]] expected<Sampler> CreateSampler(const SamplerCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Sampler pSampler;
        Result result = pfn_CreateSampler(device,
        &pCreateInfo,
        pAllocator,
        &pSampler);
    return expected<Sampler>(pSampler, result);
}
void DestroySampler(Sampler sampler = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroySampler(device,
        sampler,
        pAllocator);
}
[[nodiscard]] expected<DescriptorSetLayout> CreateDescriptorSetLayout(const DescriptorSetLayoutCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DescriptorSetLayout pSetLayout;
        Result result = pfn_CreateDescriptorSetLayout(device,
        &pCreateInfo,
        pAllocator,
        &pSetLayout);
    return expected<DescriptorSetLayout>(pSetLayout, result);
}
void DestroyDescriptorSetLayout(DescriptorSetLayout descriptorSetLayout = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDescriptorSetLayout(device,
        descriptorSetLayout,
        pAllocator);
}
[[nodiscard]] expected<DescriptorPool> CreateDescriptorPool(const DescriptorPoolCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DescriptorPool pDescriptorPool;
        Result result = pfn_CreateDescriptorPool(device,
        &pCreateInfo,
        pAllocator,
        &pDescriptorPool);
    return expected<DescriptorPool>(pDescriptorPool, result);
}
void DestroyDescriptorPool(DescriptorPool descriptorPool = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDescriptorPool(device,
        descriptorPool,
        pAllocator);
}
[[nodiscard]] Result ResetDescriptorPool(DescriptorPool descriptorPool, 
    DescriptorPoolResetFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ResetDescriptorPool(device,
        descriptorPool,
        flags);
}
[[nodiscard]] expected<detail::fixed_vector<DescriptorSet>> AllocateDescriptorSets(const DescriptorSetAllocateInfo&  pAllocateInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    detail::fixed_vector<DescriptorSet> pDescriptorSets{pAllocateInfo.descriptorSetCount};
    Result result = pfn_AllocateDescriptorSets(device,
        &pAllocateInfo,
        pDescriptorSets.data());
    return expected<detail::fixed_vector<DescriptorSet>>(std::move(pDescriptorSets), result);
}
[[nodiscard]] Result FreeDescriptorSets(DescriptorPool descriptorPool, 
    detail::span<const DescriptorSet> DescriptorSets) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t descriptorSetCount = DescriptorSets.size();
    return pfn_FreeDescriptorSets(device,
        descriptorPool,
        descriptorSetCount,
        DescriptorSets.data());
}
void UpdateDescriptorSets(detail::span<const WriteDescriptorSet> DescriptorWrites, 
    detail::span<const CopyDescriptorSet> DescriptorCopies) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t descriptorWriteCount = DescriptorWrites.size();
    uint32_t descriptorCopyCount = DescriptorCopies.size();
    pfn_UpdateDescriptorSets(device,
        descriptorWriteCount,
        DescriptorWrites.data(),
        descriptorCopyCount,
        DescriptorCopies.data());
}
[[nodiscard]] expected<Framebuffer> CreateFramebuffer(const FramebufferCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Framebuffer pFramebuffer;
        Result result = pfn_CreateFramebuffer(device,
        &pCreateInfo,
        pAllocator,
        &pFramebuffer);
    return expected<Framebuffer>(pFramebuffer, result);
}
void DestroyFramebuffer(Framebuffer framebuffer = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyFramebuffer(device,
        framebuffer,
        pAllocator);
}
[[nodiscard]] expected<RenderPass> CreateRenderPass(const RenderPassCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    RenderPass pRenderPass;
        Result result = pfn_CreateRenderPass(device,
        &pCreateInfo,
        pAllocator,
        &pRenderPass);
    return expected<RenderPass>(pRenderPass, result);
}
void DestroyRenderPass(RenderPass renderPass = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyRenderPass(device,
        renderPass,
        pAllocator);
}
[[nodiscard]] Extent2D GetRenderAreaGranularity(RenderPass renderPass) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Extent2D pGranularity;
    pfn_GetRenderAreaGranularity(device,
        renderPass,
        &pGranularity);
    return pGranularity;
}
[[nodiscard]] expected<CommandPool> CreateCommandPool(const CommandPoolCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    CommandPool pCommandPool;
        Result result = pfn_CreateCommandPool(device,
        &pCreateInfo,
        pAllocator,
        &pCommandPool);
    return expected<CommandPool>(pCommandPool, result);
}
void DestroyCommandPool(CommandPool commandPool = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyCommandPool(device,
        commandPool,
        pAllocator);
}
[[nodiscard]] Result ResetCommandPool(CommandPool commandPool, 
    CommandPoolResetFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ResetCommandPool(device,
        commandPool,
        flags);
}
[[nodiscard]] expected<detail::fixed_vector<CommandBuffer>> AllocateCommandBuffers(const CommandBufferAllocateInfo&  pAllocateInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    detail::fixed_vector<CommandBuffer> pCommandBuffers{pAllocateInfo.commandBufferCount};
    Result result = pfn_AllocateCommandBuffers(device,
        &pAllocateInfo,
        pCommandBuffers.data());
    return expected<detail::fixed_vector<CommandBuffer>>(std::move(pCommandBuffers), result);
}
void FreeCommandBuffers(CommandPool commandPool, 
    detail::span<const CommandBuffer> CommandBuffers) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t commandBufferCount = CommandBuffers.size();
    pfn_FreeCommandBuffers(device,
        commandPool,
        commandBufferCount,
        CommandBuffers.data());
}
[[nodiscard]] Result BeginCommandBuffer(CommandBuffer commandBuffer, 
    const CommandBufferBeginInfo&  pBeginInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_BeginCommandBuffer(commandBuffer,
        &pBeginInfo);
}
[[nodiscard]] Result EndCommandBuffer(CommandBuffer commandBuffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_EndCommandBuffer(commandBuffer);
}
[[nodiscard]] Result ResetCommandBuffer(CommandBuffer commandBuffer, 
    CommandBufferResetFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ResetCommandBuffer(commandBuffer,
        flags);
}
void CmdBindPipeline(CommandBuffer commandBuffer, 
    PipelineBindPoint pipelineBindPoint, 
    Pipeline pipeline) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBindPipeline(commandBuffer,
        pipelineBindPoint,
        pipeline);
}
void CmdSetViewport(CommandBuffer commandBuffer, 
    uint32_t firstViewport, 
    detail::span<const Viewport> Viewports) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t viewportCount = Viewports.size();
    pfn_CmdSetViewport(commandBuffer,
        firstViewport,
        viewportCount,
        Viewports.data());
}
void CmdSetScissor(CommandBuffer commandBuffer, 
    uint32_t firstScissor, 
    detail::span<const Rect2D> Scissors) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t scissorCount = Scissors.size();
    pfn_CmdSetScissor(commandBuffer,
        firstScissor,
        scissorCount,
        Scissors.data());
}
void CmdSetLineWidth(CommandBuffer commandBuffer, 
    float lineWidth) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetLineWidth(commandBuffer,
        lineWidth);
}
void CmdSetDepthBias(CommandBuffer commandBuffer, 
    float depthBiasConstantFactor, 
    float depthBiasClamp, 
    float depthBiasSlopeFactor) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthBias(commandBuffer,
        depthBiasConstantFactor,
        depthBiasClamp,
        depthBiasSlopeFactor);
}
void CmdSetBlendConstants(CommandBuffer commandBuffer, 
    const float blendConstants[4]) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetBlendConstants(commandBuffer,
        blendConstants);
}
void CmdSetDepthBounds(CommandBuffer commandBuffer, 
    float minDepthBounds, 
    float maxDepthBounds) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthBounds(commandBuffer,
        minDepthBounds,
        maxDepthBounds);
}
void CmdSetStencilCompareMask(CommandBuffer commandBuffer, 
    StencilFaceFlags faceMask, 
    uint32_t compareMask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetStencilCompareMask(commandBuffer,
        faceMask,
        compareMask);
}
void CmdSetStencilWriteMask(CommandBuffer commandBuffer, 
    StencilFaceFlags faceMask, 
    uint32_t writeMask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetStencilWriteMask(commandBuffer,
        faceMask,
        writeMask);
}
void CmdSetStencilReference(CommandBuffer commandBuffer, 
    StencilFaceFlags faceMask, 
    uint32_t reference) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetStencilReference(commandBuffer,
        faceMask,
        reference);
}
void CmdBindDescriptorSets(CommandBuffer commandBuffer, 
    PipelineBindPoint pipelineBindPoint, 
    PipelineLayout layout, 
    uint32_t firstSet, 
    detail::span<const DescriptorSet> DescriptorSets, 
    detail::span<const uint32_t> DynamicOffsets) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t descriptorSetCount = DescriptorSets.size();
    uint32_t dynamicOffsetCount = DynamicOffsets.size();
    pfn_CmdBindDescriptorSets(commandBuffer,
        pipelineBindPoint,
        layout,
        firstSet,
        descriptorSetCount,
        DescriptorSets.data(),
        dynamicOffsetCount,
        DynamicOffsets.data());
}
void CmdBindIndexBuffer(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    IndexType indexType) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBindIndexBuffer(commandBuffer,
        buffer,
        offset,
        indexType);
}
void CmdBindVertexBuffers(CommandBuffer commandBuffer, 
    uint32_t firstBinding, 
    detail::span<const Buffer> Buffers, 
    detail::span<const DeviceSize> Offsets) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindingCount = Buffers.size();
    pfn_CmdBindVertexBuffers(commandBuffer,
        firstBinding,
        bindingCount,
        Buffers.data(),
        Offsets.data());
}
void CmdDraw(CommandBuffer commandBuffer, 
    uint32_t vertexCount, 
    uint32_t instanceCount, 
    uint32_t firstVertex, 
    uint32_t firstInstance) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDraw(commandBuffer,
        vertexCount,
        instanceCount,
        firstVertex,
        firstInstance);
}
void CmdDrawIndexed(CommandBuffer commandBuffer, 
    uint32_t indexCount, 
    uint32_t instanceCount, 
    uint32_t firstIndex, 
    int32_t vertexOffset, 
    uint32_t firstInstance) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndexed(commandBuffer,
        indexCount,
        instanceCount,
        firstIndex,
        vertexOffset,
        firstInstance);
}
void CmdDrawIndirect(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    uint32_t drawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndirect(commandBuffer,
        buffer,
        offset,
        drawCount,
        stride);
}
void CmdDrawIndexedIndirect(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    uint32_t drawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndexedIndirect(commandBuffer,
        buffer,
        offset,
        drawCount,
        stride);
}
void CmdDispatch(CommandBuffer commandBuffer, 
    uint32_t groupCountX, 
    uint32_t groupCountY, 
    uint32_t groupCountZ) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDispatch(commandBuffer,
        groupCountX,
        groupCountY,
        groupCountZ);
}
void CmdDispatchIndirect(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDispatchIndirect(commandBuffer,
        buffer,
        offset);
}
void CmdCopyBuffer(CommandBuffer commandBuffer, 
    Buffer srcBuffer, 
    Buffer dstBuffer, 
    detail::span<const BufferCopy> Regions) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdCopyBuffer(commandBuffer,
        srcBuffer,
        dstBuffer,
        regionCount,
        Regions.data());
}
void CmdCopyImage(CommandBuffer commandBuffer, 
    Image srcImage, 
    ImageLayout srcImageLayout, 
    Image dstImage, 
    ImageLayout dstImageLayout, 
    detail::span<const ImageCopy> Regions) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdCopyImage(commandBuffer,
        srcImage,
        srcImageLayout,
        dstImage,
        dstImageLayout,
        regionCount,
        Regions.data());
}
void CmdBlitImage(CommandBuffer commandBuffer, 
    Image srcImage, 
    ImageLayout srcImageLayout, 
    Image dstImage, 
    ImageLayout dstImageLayout, 
    detail::span<const ImageBlit> Regions, 
    Filter filter) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdBlitImage(commandBuffer,
        srcImage,
        srcImageLayout,
        dstImage,
        dstImageLayout,
        regionCount,
        Regions.data(),
        filter);
}
void CmdCopyBufferToImage(CommandBuffer commandBuffer, 
    Buffer srcBuffer, 
    Image dstImage, 
    ImageLayout dstImageLayout, 
    detail::span<const BufferImageCopy> Regions) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdCopyBufferToImage(commandBuffer,
        srcBuffer,
        dstImage,
        dstImageLayout,
        regionCount,
        Regions.data());
}
void CmdCopyImageToBuffer(CommandBuffer commandBuffer, 
    Image srcImage, 
    ImageLayout srcImageLayout, 
    Buffer dstBuffer, 
    detail::span<const BufferImageCopy> Regions) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdCopyImageToBuffer(commandBuffer,
        srcImage,
        srcImageLayout,
        dstBuffer,
        regionCount,
        Regions.data());
}
void CmdUpdateBuffer(CommandBuffer commandBuffer, 
    Buffer dstBuffer, 
    DeviceSize dstOffset, 
    detail::span<const std::byte> Data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceSize dataSize = Data.size();
    pfn_CmdUpdateBuffer(commandBuffer,
        dstBuffer,
        dstOffset,
        dataSize,
        Data.data());
}
void CmdFillBuffer(CommandBuffer commandBuffer, 
    Buffer dstBuffer, 
    DeviceSize dstOffset, 
    DeviceSize size, 
    uint32_t data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdFillBuffer(commandBuffer,
        dstBuffer,
        dstOffset,
        size,
        data);
}
void CmdClearColorImage(CommandBuffer commandBuffer, 
    Image image, 
    ImageLayout imageLayout, 
    const ClearColorValue&  pColor, 
    detail::span<const ImageSubresourceRange> Ranges) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t rangeCount = Ranges.size();
    pfn_CmdClearColorImage(commandBuffer,
        image,
        imageLayout,
        &pColor,
        rangeCount,
        Ranges.data());
}
void CmdClearDepthStencilImage(CommandBuffer commandBuffer, 
    Image image, 
    ImageLayout imageLayout, 
    const ClearDepthStencilValue&  pDepthStencil, 
    detail::span<const ImageSubresourceRange> Ranges) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t rangeCount = Ranges.size();
    pfn_CmdClearDepthStencilImage(commandBuffer,
        image,
        imageLayout,
        &pDepthStencil,
        rangeCount,
        Ranges.data());
}
void CmdClearAttachments(CommandBuffer commandBuffer, 
    detail::span<const ClearAttachment> Attachments, 
    detail::span<const ClearRect> Rects) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t attachmentCount = Attachments.size();
    uint32_t rectCount = Rects.size();
    pfn_CmdClearAttachments(commandBuffer,
        attachmentCount,
        Attachments.data(),
        rectCount,
        Rects.data());
}
void CmdResolveImage(CommandBuffer commandBuffer, 
    Image srcImage, 
    ImageLayout srcImageLayout, 
    Image dstImage, 
    ImageLayout dstImageLayout, 
    detail::span<const ImageResolve> Regions) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t regionCount = Regions.size();
    pfn_CmdResolveImage(commandBuffer,
        srcImage,
        srcImageLayout,
        dstImage,
        dstImageLayout,
        regionCount,
        Regions.data());
}
void CmdSetEvent(CommandBuffer commandBuffer, 
    Event event, 
    PipelineStageFlags stageMask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetEvent(commandBuffer,
        event,
        stageMask);
}
void CmdResetEvent(CommandBuffer commandBuffer, 
    Event event, 
    PipelineStageFlags stageMask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdResetEvent(commandBuffer,
        event,
        stageMask);
}
void CmdWaitEvents(CommandBuffer commandBuffer, 
    detail::span<const Event> Events, 
    PipelineStageFlags srcStageMask, 
    PipelineStageFlags dstStageMask, 
    detail::span<const MemoryBarrier> MemoryBarriers, 
    detail::span<const BufferMemoryBarrier> BufferMemoryBarriers, 
    detail::span<const ImageMemoryBarrier> ImageMemoryBarriers) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t eventCount = Events.size();
    uint32_t memoryBarrierCount = MemoryBarriers.size();
    uint32_t bufferMemoryBarrierCount = BufferMemoryBarriers.size();
    uint32_t imageMemoryBarrierCount = ImageMemoryBarriers.size();
    pfn_CmdWaitEvents(commandBuffer,
        eventCount,
        Events.data(),
        srcStageMask,
        dstStageMask,
        memoryBarrierCount,
        MemoryBarriers.data(),
        bufferMemoryBarrierCount,
        BufferMemoryBarriers.data(),
        imageMemoryBarrierCount,
        ImageMemoryBarriers.data());
}
void CmdPipelineBarrier(CommandBuffer commandBuffer, 
    PipelineStageFlags srcStageMask, 
    PipelineStageFlags dstStageMask, 
    DependencyFlags dependencyFlags, 
    detail::span<const MemoryBarrier> MemoryBarriers, 
    detail::span<const BufferMemoryBarrier> BufferMemoryBarriers, 
    detail::span<const ImageMemoryBarrier> ImageMemoryBarriers) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t memoryBarrierCount = MemoryBarriers.size();
    uint32_t bufferMemoryBarrierCount = BufferMemoryBarriers.size();
    uint32_t imageMemoryBarrierCount = ImageMemoryBarriers.size();
    pfn_CmdPipelineBarrier(commandBuffer,
        srcStageMask,
        dstStageMask,
        dependencyFlags,
        memoryBarrierCount,
        MemoryBarriers.data(),
        bufferMemoryBarrierCount,
        BufferMemoryBarriers.data(),
        imageMemoryBarrierCount,
        ImageMemoryBarriers.data());
}
void CmdBeginQuery(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t query, 
    QueryControlFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginQuery(commandBuffer,
        queryPool,
        query,
        flags);
}
void CmdEndQuery(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t query) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndQuery(commandBuffer,
        queryPool,
        query);
}
void CmdResetQueryPool(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t firstQuery, 
    uint32_t queryCount) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdResetQueryPool(commandBuffer,
        queryPool,
        firstQuery,
        queryCount);
}
void CmdWriteTimestamp(CommandBuffer commandBuffer, 
    PipelineStageFlagBits pipelineStage, 
    QueryPool queryPool, 
    uint32_t query) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdWriteTimestamp(commandBuffer,
        pipelineStage,
        queryPool,
        query);
}
void CmdCopyQueryPoolResults(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t firstQuery, 
    uint32_t queryCount, 
    Buffer dstBuffer, 
    DeviceSize dstOffset, 
    DeviceSize stride, 
    QueryResultFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyQueryPoolResults(commandBuffer,
        queryPool,
        firstQuery,
        queryCount,
        dstBuffer,
        dstOffset,
        stride,
        flags);
}
void CmdPushConstants(CommandBuffer commandBuffer, 
    PipelineLayout layout, 
    ShaderStageFlags stageFlags, 
    uint32_t offset, 
    detail::span<const std::byte> Values) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t size = Values.size();
    pfn_CmdPushConstants(commandBuffer,
        layout,
        stageFlags,
        offset,
        size,
        Values.data());
}
void CmdBeginRenderPass(CommandBuffer commandBuffer, 
    const RenderPassBeginInfo&  pRenderPassBegin, 
    SubpassContents contents) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginRenderPass(commandBuffer,
        &pRenderPassBegin,
        contents);
}
void CmdNextSubpass(CommandBuffer commandBuffer, 
    SubpassContents contents) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdNextSubpass(commandBuffer,
        contents);
}
void CmdEndRenderPass(CommandBuffer commandBuffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndRenderPass(commandBuffer);
}
void CmdExecuteCommands(CommandBuffer commandBuffer, 
    detail::span<const CommandBuffer> CommandBuffers) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t commandBufferCount = CommandBuffers.size();
    pfn_CmdExecuteCommands(commandBuffer,
        commandBufferCount,
        CommandBuffers.data());
}
[[nodiscard]] Result BindBufferMemory2(detail::span<const BindBufferMemoryInfo> BindInfos) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindInfoCount = BindInfos.size();
    return pfn_BindBufferMemory2(device,
        bindInfoCount,
        BindInfos.data());
}
[[nodiscard]] Result BindImageMemory2(detail::span<const BindImageMemoryInfo> BindInfos) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindInfoCount = BindInfos.size();
    return pfn_BindImageMemory2(device,
        bindInfoCount,
        BindInfos.data());
}
[[nodiscard]] PeerMemoryFeatureFlags GetDeviceGroupPeerMemoryFeatures(uint32_t heapIndex, 
    uint32_t localDeviceIndex, 
    uint32_t remoteDeviceIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PeerMemoryFeatureFlags pPeerMemoryFeatures;
    pfn_GetDeviceGroupPeerMemoryFeatures(device,
        heapIndex,
        localDeviceIndex,
        remoteDeviceIndex,
        &pPeerMemoryFeatures);
    return pPeerMemoryFeatures;
}
void CmdSetDeviceMask(CommandBuffer commandBuffer, 
    uint32_t deviceMask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDeviceMask(commandBuffer,
        deviceMask);
}
void CmdDispatchBase(CommandBuffer commandBuffer, 
    uint32_t baseGroupX, 
    uint32_t baseGroupY, 
    uint32_t baseGroupZ, 
    uint32_t groupCountX, 
    uint32_t groupCountY, 
    uint32_t groupCountZ) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDispatchBase(commandBuffer,
        baseGroupX,
        baseGroupY,
        baseGroupZ,
        groupCountX,
        groupCountY,
        groupCountZ);
}
[[nodiscard]] MemoryRequirements2 GetBufferMemoryRequirements2(const BufferMemoryRequirementsInfo2&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements2 pMemoryRequirements;
    pfn_GetBufferMemoryRequirements2(device,
        &pInfo,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] MemoryRequirements2 GetImageMemoryRequirements2(const ImageMemoryRequirementsInfo2&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements2 pMemoryRequirements;
    pfn_GetImageMemoryRequirements2(device,
        &pInfo,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] detail::fixed_vector<SparseImageMemoryRequirements2> GetImageSparseMemoryRequirements2(const ImageSparseMemoryRequirementsInfo2&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pSparseMemoryRequirementCount = 0;
    pfn_GetImageSparseMemoryRequirements2(device,
        &pInfo,
        &pSparseMemoryRequirementCount,
        nullptr);
    detail::fixed_vector<SparseImageMemoryRequirements2> pSparseMemoryRequirements{pSparseMemoryRequirementCount};
pfn_GetImageSparseMemoryRequirements2(device,
        &pInfo,
        &pSparseMemoryRequirementCount,
        pSparseMemoryRequirements.data());
    if (pSparseMemoryRequirementCount < pSparseMemoryRequirements.size()) pSparseMemoryRequirements.shrink(pSparseMemoryRequirementCount);
    return pSparseMemoryRequirements;
}
void TrimCommandPool(CommandPool commandPool, 
    CommandPoolTrimFlags flags = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_TrimCommandPool(device,
        commandPool,
        flags);
}
[[nodiscard]] Queue GetDeviceQueue2(const DeviceQueueInfo2&  pQueueInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Queue pQueue;
    pfn_GetDeviceQueue2(device,
        &pQueueInfo,
        &pQueue);
    return pQueue;
}
[[nodiscard]] expected<SamplerYcbcrConversion> CreateSamplerYcbcrConversion(const SamplerYcbcrConversionCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SamplerYcbcrConversion pYcbcrConversion;
        Result result = pfn_CreateSamplerYcbcrConversion(device,
        &pCreateInfo,
        pAllocator,
        &pYcbcrConversion);
    return expected<SamplerYcbcrConversion>(pYcbcrConversion, result);
}
void DestroySamplerYcbcrConversion(SamplerYcbcrConversion ycbcrConversion = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroySamplerYcbcrConversion(device,
        ycbcrConversion,
        pAllocator);
}
[[nodiscard]] expected<DescriptorUpdateTemplate> CreateDescriptorUpdateTemplate(const DescriptorUpdateTemplateCreateInfo&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DescriptorUpdateTemplate pDescriptorUpdateTemplate;
        Result result = pfn_CreateDescriptorUpdateTemplate(device,
        &pCreateInfo,
        pAllocator,
        &pDescriptorUpdateTemplate);
    return expected<DescriptorUpdateTemplate>(pDescriptorUpdateTemplate, result);
}
void DestroyDescriptorUpdateTemplate(DescriptorUpdateTemplate descriptorUpdateTemplate = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDescriptorUpdateTemplate(device,
        descriptorUpdateTemplate,
        pAllocator);
}
void UpdateDescriptorSetWithTemplate(DescriptorSet descriptorSet, 
    DescriptorUpdateTemplate descriptorUpdateTemplate, 
    const void* pData) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_UpdateDescriptorSetWithTemplate(device,
        descriptorSet,
        descriptorUpdateTemplate,
        pData);
}
[[nodiscard]] DescriptorSetLayoutSupport GetDescriptorSetLayoutSupport(const DescriptorSetLayoutCreateInfo&  pCreateInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DescriptorSetLayoutSupport pSupport;
    pfn_GetDescriptorSetLayoutSupport(device,
        &pCreateInfo,
        &pSupport);
    return pSupport;
}
void CmdDrawIndirectCount(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    Buffer countBuffer, 
    DeviceSize countBufferOffset, 
    uint32_t maxDrawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndirectCount(commandBuffer,
        buffer,
        offset,
        countBuffer,
        countBufferOffset,
        maxDrawCount,
        stride);
}
void CmdDrawIndexedIndirectCount(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    Buffer countBuffer, 
    DeviceSize countBufferOffset, 
    uint32_t maxDrawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndexedIndirectCount(commandBuffer,
        buffer,
        offset,
        countBuffer,
        countBufferOffset,
        maxDrawCount,
        stride);
}
[[nodiscard]] expected<RenderPass> CreateRenderPass2(const RenderPassCreateInfo2&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    RenderPass pRenderPass;
        Result result = pfn_CreateRenderPass2(device,
        &pCreateInfo,
        pAllocator,
        &pRenderPass);
    return expected<RenderPass>(pRenderPass, result);
}
void CmdBeginRenderPass2(CommandBuffer commandBuffer, 
    const RenderPassBeginInfo&  pRenderPassBegin, 
    const SubpassBeginInfo&  pSubpassBeginInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginRenderPass2(commandBuffer,
        &pRenderPassBegin,
        &pSubpassBeginInfo);
}
void CmdNextSubpass2(CommandBuffer commandBuffer, 
    const SubpassBeginInfo&  pSubpassBeginInfo, 
    const SubpassEndInfo&  pSubpassEndInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdNextSubpass2(commandBuffer,
        &pSubpassBeginInfo,
        &pSubpassEndInfo);
}
void CmdEndRenderPass2(CommandBuffer commandBuffer, 
    const SubpassEndInfo&  pSubpassEndInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndRenderPass2(commandBuffer,
        &pSubpassEndInfo);
}
void ResetQueryPool(QueryPool queryPool, 
    uint32_t firstQuery, 
    uint32_t queryCount) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_ResetQueryPool(device,
        queryPool,
        firstQuery,
        queryCount);
}
[[nodiscard]] expected<uint64_t> GetSemaphoreCounterValue(Semaphore semaphore) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint64_t pValue;
        Result result = pfn_GetSemaphoreCounterValue(device,
        semaphore,
        &pValue);
    return expected<uint64_t>(pValue, result);
}
[[nodiscard]] Result WaitSemaphores(const SemaphoreWaitInfo&  pWaitInfo, 
    uint64_t timeout) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_WaitSemaphores(device,
        &pWaitInfo,
        timeout);
}
[[nodiscard]] Result SignalSemaphore(const SemaphoreSignalInfo&  pSignalInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_SignalSemaphore(device,
        &pSignalInfo);
}
[[nodiscard]] uint64_t GetBufferOpaqueCaptureAddress(const BufferDeviceAddressInfo&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetBufferOpaqueCaptureAddress(device,
        &pInfo);
}
[[nodiscard]] DeviceAddress GetBufferDeviceAddress(const BufferDeviceAddressInfo&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetBufferDeviceAddress(device,
        &pInfo);
}
[[nodiscard]] uint64_t GetDeviceMemoryOpaqueCaptureAddress(const DeviceMemoryOpaqueCaptureAddressInfo&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetDeviceMemoryOpaqueCaptureAddress(device,
        &pInfo);
}
[[nodiscard]] expected<SwapchainKHR> CreateSwapchainKHR(const SwapchainCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    SwapchainKHR pSwapchain;
        Result result = pfn_CreateSwapchainKHR(device,
        &pCreateInfo,
        pAllocator,
        &pSwapchain);
    return expected<SwapchainKHR>(pSwapchain, result);
}
void DestroySwapchainKHR(SwapchainKHR swapchain = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroySwapchainKHR(device,
        swapchain,
        pAllocator);
}
[[nodiscard]] expected<detail::fixed_vector<Image>> GetSwapchainImagesKHR(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pSwapchainImageCount = 0;
        Result result = pfn_GetSwapchainImagesKHR(device,
        swapchain,
        &pSwapchainImageCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<Image>{}, result);
    detail::fixed_vector<Image> pSwapchainImages{pSwapchainImageCount};
    result = pfn_GetSwapchainImagesKHR(device,
        swapchain,
        &pSwapchainImageCount,
        pSwapchainImages.data());
    if (pSwapchainImageCount < pSwapchainImages.size()) pSwapchainImages.shrink(pSwapchainImageCount);
    return expected(std::move(pSwapchainImages), result);
}
[[nodiscard]] expected<uint32_t> AcquireNextImageKHR(SwapchainKHR swapchain, 
    uint64_t timeout, 
    Semaphore semaphore = {}, 
    Fence fence = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pImageIndex;
        Result result = pfn_AcquireNextImageKHR(device,
        swapchain,
        timeout,
        semaphore,
        fence,
        &pImageIndex);
    return expected<uint32_t>(pImageIndex, result);
}
[[nodiscard]] Result QueuePresentKHR(Queue queue, 
    const PresentInfoKHR&  pPresentInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_QueuePresentKHR(queue,
        &pPresentInfo);
}
[[nodiscard]] expected<DeviceGroupPresentCapabilitiesKHR> GetDeviceGroupPresentCapabilitiesKHR() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceGroupPresentCapabilitiesKHR pDeviceGroupPresentCapabilities;
        Result result = pfn_GetDeviceGroupPresentCapabilitiesKHR(device,
        &pDeviceGroupPresentCapabilities);
    return expected<DeviceGroupPresentCapabilitiesKHR>(pDeviceGroupPresentCapabilities, result);
}
[[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModesKHR(SurfaceKHR surface) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceGroupPresentModeFlagsKHR pModes;
        Result result = pfn_GetDeviceGroupSurfacePresentModesKHR(device,
        surface,
        &pModes);
    return expected<DeviceGroupPresentModeFlagsKHR>(pModes, result);
}
[[nodiscard]] expected<uint32_t> AcquireNextImage2KHR(const AcquireNextImageInfoKHR&  pAcquireInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pImageIndex;
        Result result = pfn_AcquireNextImage2KHR(device,
        &pAcquireInfo,
        &pImageIndex);
    return expected<uint32_t>(pImageIndex, result);
}
[[nodiscard]] Result CreateSharedSwapchainsKHR(detail::span<const SwapchainCreateInfoKHR> CreateInfos, 
    const AllocationCallbacks* pAllocator, 
    detail::span<SwapchainKHR> Swapchains) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t swapchainCount = CreateInfos.size();
    return pfn_CreateSharedSwapchainsKHR(device,
        swapchainCount,
        CreateInfos.data(),
        pAllocator,
        Swapchains.data());
}
[[nodiscard]] Result DebugMarkerSetObjectNameEXT(const DebugMarkerObjectNameInfoEXT&  pNameInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_DebugMarkerSetObjectNameEXT(device,
        &pNameInfo);
}
[[nodiscard]] Result DebugMarkerSetObjectTagEXT(const DebugMarkerObjectTagInfoEXT&  pTagInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_DebugMarkerSetObjectTagEXT(device,
        &pTagInfo);
}
void CmdDebugMarkerBeginEXT(CommandBuffer commandBuffer, 
    const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDebugMarkerBeginEXT(commandBuffer,
        &pMarkerInfo);
}
void CmdDebugMarkerEndEXT(CommandBuffer commandBuffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDebugMarkerEndEXT(commandBuffer);
}
void CmdDebugMarkerInsertEXT(CommandBuffer commandBuffer, 
    const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDebugMarkerInsertEXT(commandBuffer,
        &pMarkerInfo);
}
void CmdBindTransformFeedbackBuffersEXT(CommandBuffer commandBuffer, 
    uint32_t firstBinding, 
    detail::span<const Buffer> Buffers, 
    detail::span<const DeviceSize> Offsets, 
    detail::span<const DeviceSize> Sizes = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindingCount = Buffers.size();
    pfn_CmdBindTransformFeedbackBuffersEXT(commandBuffer,
        firstBinding,
        bindingCount,
        Buffers.data(),
        Offsets.data(),
        Sizes.data());
}
void CmdBeginTransformFeedbackEXT(CommandBuffer commandBuffer, 
    uint32_t firstCounterBuffer, 
    detail::span<const Buffer> CounterBuffers, 
    detail::span<const DeviceSize> CounterBufferOffsets = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t counterBufferCount = CounterBuffers.size();
    pfn_CmdBeginTransformFeedbackEXT(commandBuffer,
        firstCounterBuffer,
        counterBufferCount,
        CounterBuffers.data(),
        CounterBufferOffsets.data());
}
void CmdEndTransformFeedbackEXT(CommandBuffer commandBuffer, 
    uint32_t firstCounterBuffer, 
    detail::span<const Buffer> CounterBuffers, 
    detail::span<const DeviceSize> CounterBufferOffsets = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t counterBufferCount = CounterBuffers.size();
    pfn_CmdEndTransformFeedbackEXT(commandBuffer,
        firstCounterBuffer,
        counterBufferCount,
        CounterBuffers.data(),
        CounterBufferOffsets.data());
}
void CmdBeginQueryIndexedEXT(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t query, 
    QueryControlFlags flags, 
    uint32_t index) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginQueryIndexedEXT(commandBuffer,
        queryPool,
        query,
        flags,
        index);
}
void CmdEndQueryIndexedEXT(CommandBuffer commandBuffer, 
    QueryPool queryPool, 
    uint32_t query, 
    uint32_t index) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndQueryIndexedEXT(commandBuffer,
        queryPool,
        query,
        index);
}
void CmdDrawIndirectByteCountEXT(CommandBuffer commandBuffer, 
    uint32_t instanceCount, 
    uint32_t firstInstance, 
    Buffer counterBuffer, 
    DeviceSize counterBufferOffset, 
    uint32_t counterOffset, 
    uint32_t vertexStride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawIndirectByteCountEXT(commandBuffer,
        instanceCount,
        firstInstance,
        counterBuffer,
        counterBufferOffset,
        counterOffset,
        vertexStride);
}
[[nodiscard]] uint32_t GetImageViewHandleNVX(const ImageViewHandleInfoNVX&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetImageViewHandleNVX(device,
        &pInfo);
}
[[nodiscard]] expected<ImageViewAddressPropertiesNVX> GetImageViewAddressNVX(ImageView imageView) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ImageViewAddressPropertiesNVX pProperties;
        Result result = pfn_GetImageViewAddressNVX(device,
        imageView,
        &pProperties);
    return expected<ImageViewAddressPropertiesNVX>(pProperties, result);
}
[[nodiscard]] expected<detail::fixed_vector<void*>> GetShaderInfoAMD(Pipeline pipeline, 
    ShaderStageFlagBits shaderStage, 
    ShaderInfoTypeAMD infoType) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t pInfoSize = 0;
        Result result = pfn_GetShaderInfoAMD(device,
        pipeline,
        shaderStage,
        infoType,
        &pInfoSize,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
    detail::fixed_vector<void*> pInfo{pInfoSize};
    result = pfn_GetShaderInfoAMD(device,
        pipeline,
        shaderStage,
        infoType,
        &pInfoSize,
        pInfo.data());
    if (pInfoSize < pInfo.size()) pInfo.shrink(pInfoSize);
    return expected(std::move(pInfo), result);
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<HANDLE> GetMemoryWin32HandleNV(DeviceMemory memory, 
    ExternalMemoryHandleTypeFlagsNV handleType) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    HANDLE pHandle;
        Result result = pfn_GetMemoryWin32HandleNV(device,
        memory,
        handleType,
        &pHandle);
    return expected<HANDLE>(pHandle, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<HANDLE> GetMemoryWin32HandleKHR(const MemoryGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    HANDLE pHandle;
        Result result = pfn_GetMemoryWin32HandleKHR(device,
        &pGetWin32HandleInfo,
        &pHandle);
    return expected<HANDLE>(pHandle, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<MemoryWin32HandlePropertiesKHR> GetMemoryWin32HandlePropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, 
    HANDLE handle) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryWin32HandlePropertiesKHR pMemoryWin32HandleProperties;
        Result result = pfn_GetMemoryWin32HandlePropertiesKHR(device,
        handleType,
        handle,
        &pMemoryWin32HandleProperties);
    return expected<MemoryWin32HandlePropertiesKHR>(pMemoryWin32HandleProperties, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
[[nodiscard]] expected<int> GetMemoryFdKHR(const MemoryGetFdInfoKHR&  pGetFdInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    int pFd;
        Result result = pfn_GetMemoryFdKHR(device,
        &pGetFdInfo,
        &pFd);
    return expected<int>(pFd, result);
}
[[nodiscard]] expected<MemoryFdPropertiesKHR> GetMemoryFdPropertiesKHR(ExternalMemoryHandleTypeFlagBits handleType, 
    int fd) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryFdPropertiesKHR pMemoryFdProperties;
        Result result = pfn_GetMemoryFdPropertiesKHR(device,
        handleType,
        fd,
        &pMemoryFdProperties);
    return expected<MemoryFdPropertiesKHR>(pMemoryFdProperties, result);
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<HANDLE> GetSemaphoreWin32HandleKHR(const SemaphoreGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    HANDLE pHandle;
        Result result = pfn_GetSemaphoreWin32HandleKHR(device,
        &pGetWin32HandleInfo,
        &pHandle);
    return expected<HANDLE>(pHandle, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Result ImportSemaphoreWin32HandleKHR(const ImportSemaphoreWin32HandleInfoKHR&  pImportSemaphoreWin32HandleInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ImportSemaphoreWin32HandleKHR(device,
        &pImportSemaphoreWin32HandleInfo);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
[[nodiscard]] expected<int> GetSemaphoreFdKHR(const SemaphoreGetFdInfoKHR&  pGetFdInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    int pFd;
        Result result = pfn_GetSemaphoreFdKHR(device,
        &pGetFdInfo,
        &pFd);
    return expected<int>(pFd, result);
}
[[nodiscard]] Result ImportSemaphoreFdKHR(const ImportSemaphoreFdInfoKHR&  pImportSemaphoreFdInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ImportSemaphoreFdKHR(device,
        &pImportSemaphoreFdInfo);
}
void CmdPushDescriptorSetKHR(CommandBuffer commandBuffer, 
    PipelineBindPoint pipelineBindPoint, 
    PipelineLayout layout, 
    uint32_t set, 
    detail::span<const WriteDescriptorSet> DescriptorWrites) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t descriptorWriteCount = DescriptorWrites.size();
    pfn_CmdPushDescriptorSetKHR(commandBuffer,
        pipelineBindPoint,
        layout,
        set,
        descriptorWriteCount,
        DescriptorWrites.data());
}
void CmdPushDescriptorSetWithTemplateKHR(CommandBuffer commandBuffer, 
    DescriptorUpdateTemplate descriptorUpdateTemplate, 
    PipelineLayout layout, 
    uint32_t set, 
    const void* pData) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdPushDescriptorSetWithTemplateKHR(commandBuffer,
        descriptorUpdateTemplate,
        layout,
        set,
        pData);
}
void CmdBeginConditionalRenderingEXT(CommandBuffer commandBuffer, 
    const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginConditionalRenderingEXT(commandBuffer,
        &pConditionalRenderingBegin);
}
void CmdEndConditionalRenderingEXT(CommandBuffer commandBuffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndConditionalRenderingEXT(commandBuffer);
}
void CmdSetViewportWScalingNV(CommandBuffer commandBuffer, 
    uint32_t firstViewport, 
    detail::span<const ViewportWScalingNV> ViewportWScalings) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t viewportCount = ViewportWScalings.size();
    pfn_CmdSetViewportWScalingNV(commandBuffer,
        firstViewport,
        viewportCount,
        ViewportWScalings.data());
}
[[nodiscard]] Result DisplayPowerControlEXT(DisplayKHR display, 
    const DisplayPowerInfoEXT&  pDisplayPowerInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_DisplayPowerControlEXT(device,
        display,
        &pDisplayPowerInfo);
}
[[nodiscard]] expected<Fence> RegisterDeviceEventEXT(const DeviceEventInfoEXT&  pDeviceEventInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Fence pFence;
        Result result = pfn_RegisterDeviceEventEXT(device,
        &pDeviceEventInfo,
        pAllocator,
        &pFence);
    return expected<Fence>(pFence, result);
}
[[nodiscard]] expected<Fence> RegisterDisplayEventEXT(DisplayKHR display, 
    const DisplayEventInfoEXT&  pDisplayEventInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    Fence pFence;
        Result result = pfn_RegisterDisplayEventEXT(device,
        display,
        &pDisplayEventInfo,
        pAllocator,
        &pFence);
    return expected<Fence>(pFence, result);
}
[[nodiscard]] expected<uint64_t> GetSwapchainCounterEXT(SwapchainKHR swapchain, 
    SurfaceCounterFlagBitsEXT counter) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint64_t pCounterValue;
        Result result = pfn_GetSwapchainCounterEXT(device,
        swapchain,
        counter,
        &pCounterValue);
    return expected<uint64_t>(pCounterValue, result);
}
[[nodiscard]] expected<RefreshCycleDurationGOOGLE> GetRefreshCycleDurationGOOGLE(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    RefreshCycleDurationGOOGLE pDisplayTimingProperties;
        Result result = pfn_GetRefreshCycleDurationGOOGLE(device,
        swapchain,
        &pDisplayTimingProperties);
    return expected<RefreshCycleDurationGOOGLE>(pDisplayTimingProperties, result);
}
[[nodiscard]] expected<detail::fixed_vector<PastPresentationTimingGOOGLE>> GetPastPresentationTimingGOOGLE(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pPresentationTimingCount = 0;
        Result result = pfn_GetPastPresentationTimingGOOGLE(device,
        swapchain,
        &pPresentationTimingCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PastPresentationTimingGOOGLE>{}, result);
    detail::fixed_vector<PastPresentationTimingGOOGLE> pPresentationTimings{pPresentationTimingCount};
    result = pfn_GetPastPresentationTimingGOOGLE(device,
        swapchain,
        &pPresentationTimingCount,
        pPresentationTimings.data());
    if (pPresentationTimingCount < pPresentationTimings.size()) pPresentationTimings.shrink(pPresentationTimingCount);
    return expected(std::move(pPresentationTimings), result);
}
void CmdSetDiscardRectangleEXT(CommandBuffer commandBuffer, 
    uint32_t firstDiscardRectangle, 
    detail::span<const Rect2D> DiscardRectangles) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t discardRectangleCount = DiscardRectangles.size();
    pfn_CmdSetDiscardRectangleEXT(commandBuffer,
        firstDiscardRectangle,
        discardRectangleCount,
        DiscardRectangles.data());
}
void SetHdrMetadataEXT(detail::span<const SwapchainKHR> Swapchains, 
    detail::span<const HdrMetadataEXT> Metadata) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t swapchainCount = Swapchains.size();
    pfn_SetHdrMetadataEXT(device,
        swapchainCount,
        Swapchains.data(),
        Metadata.data());
}
[[nodiscard]] Result GetSwapchainStatusKHR(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetSwapchainStatusKHR(device,
        swapchain);
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<HANDLE> GetFenceWin32HandleKHR(const FenceGetWin32HandleInfoKHR&  pGetWin32HandleInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    HANDLE pHandle;
        Result result = pfn_GetFenceWin32HandleKHR(device,
        &pGetWin32HandleInfo,
        &pHandle);
    return expected<HANDLE>(pHandle, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Result ImportFenceWin32HandleKHR(const ImportFenceWin32HandleInfoKHR&  pImportFenceWin32HandleInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ImportFenceWin32HandleKHR(device,
        &pImportFenceWin32HandleInfo);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
[[nodiscard]] expected<int> GetFenceFdKHR(const FenceGetFdInfoKHR&  pGetFdInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    int pFd;
        Result result = pfn_GetFenceFdKHR(device,
        &pGetFdInfo,
        &pFd);
    return expected<int>(pFd, result);
}
[[nodiscard]] Result ImportFenceFdKHR(const ImportFenceFdInfoKHR&  pImportFenceFdInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ImportFenceFdKHR(device,
        &pImportFenceFdInfo);
}
[[nodiscard]] Result AcquireProfilingLockKHR(const AcquireProfilingLockInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_AcquireProfilingLockKHR(device,
        &pInfo);
}
void ReleaseProfilingLockKHR() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_ReleaseProfilingLockKHR(device);
}
[[nodiscard]] Result SetDebugUtilsObjectNameEXT(const DebugUtilsObjectNameInfoEXT&  pNameInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_SetDebugUtilsObjectNameEXT(device,
        &pNameInfo);
}
[[nodiscard]] Result SetDebugUtilsObjectTagEXT(const DebugUtilsObjectTagInfoEXT&  pTagInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_SetDebugUtilsObjectTagEXT(device,
        &pTagInfo);
}
void QueueBeginDebugUtilsLabelEXT(Queue queue, 
    const DebugUtilsLabelEXT&  pLabelInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_QueueBeginDebugUtilsLabelEXT(queue,
        &pLabelInfo);
}
void QueueEndDebugUtilsLabelEXT(Queue queue) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_QueueEndDebugUtilsLabelEXT(queue);
}
void QueueInsertDebugUtilsLabelEXT(Queue queue, 
    const DebugUtilsLabelEXT&  pLabelInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_QueueInsertDebugUtilsLabelEXT(queue,
        &pLabelInfo);
}
void CmdBeginDebugUtilsLabelEXT(CommandBuffer commandBuffer, 
    const DebugUtilsLabelEXT&  pLabelInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBeginDebugUtilsLabelEXT(commandBuffer,
        &pLabelInfo);
}
void CmdEndDebugUtilsLabelEXT(CommandBuffer commandBuffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdEndDebugUtilsLabelEXT(commandBuffer);
}
void CmdInsertDebugUtilsLabelEXT(CommandBuffer commandBuffer, 
    const DebugUtilsLabelEXT&  pLabelInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdInsertDebugUtilsLabelEXT(commandBuffer,
        &pLabelInfo);
}
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
[[nodiscard]] expected<AndroidHardwareBufferPropertiesANDROID> GetAndroidHardwareBufferPropertiesANDROID(const AHardwareBuffer&  buffer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AndroidHardwareBufferPropertiesANDROID pProperties;
        Result result = pfn_GetAndroidHardwareBufferPropertiesANDROID(device,
        &buffer,
        &pProperties);
    return expected<AndroidHardwareBufferPropertiesANDROID>(pProperties, result);
}
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
[[nodiscard]] expected<AHardwareBuffer*> GetMemoryAndroidHardwareBufferANDROID(const MemoryGetAndroidHardwareBufferInfoANDROID&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AHardwareBuffer* pBuffer;
        Result result = pfn_GetMemoryAndroidHardwareBufferANDROID(device,
        &pInfo,
        &pBuffer);
    return expected<AHardwareBuffer*>(pBuffer, result);
}
#endif // VK_USE_PLATFORM_ANDROID_KHR
void CmdSetSampleLocationsEXT(CommandBuffer commandBuffer, 
    const SampleLocationsInfoEXT&  pSampleLocationsInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetSampleLocationsEXT(commandBuffer,
        &pSampleLocationsInfo);
}
void DestroyAccelerationStructureKHR(AccelerationStructureKHR accelerationStructure = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyAccelerationStructureKHR(device,
        accelerationStructure,
        pAllocator);
}
void CmdCopyAccelerationStructureKHR(CommandBuffer commandBuffer, 
    const CopyAccelerationStructureInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyAccelerationStructureKHR(commandBuffer,
        &pInfo);
}
[[nodiscard]] Result CopyAccelerationStructureKHR(DeferredOperationKHR deferredOperation, 
    const CopyAccelerationStructureInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CopyAccelerationStructureKHR(device,
        deferredOperation,
        &pInfo);
}
void CmdCopyAccelerationStructureToMemoryKHR(CommandBuffer commandBuffer, 
    const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyAccelerationStructureToMemoryKHR(commandBuffer,
        &pInfo);
}
[[nodiscard]] Result CopyAccelerationStructureToMemoryKHR(DeferredOperationKHR deferredOperation, 
    const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CopyAccelerationStructureToMemoryKHR(device,
        deferredOperation,
        &pInfo);
}
void CmdCopyMemoryToAccelerationStructureKHR(CommandBuffer commandBuffer, 
    const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyMemoryToAccelerationStructureKHR(commandBuffer,
        &pInfo);
}
[[nodiscard]] Result CopyMemoryToAccelerationStructureKHR(DeferredOperationKHR deferredOperation, 
    const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CopyMemoryToAccelerationStructureKHR(device,
        deferredOperation,
        &pInfo);
}
void CmdWriteAccelerationStructuresPropertiesKHR(CommandBuffer commandBuffer, 
    detail::span<const AccelerationStructureKHR> AccelerationStructures, 
    QueryType queryType, 
    QueryPool queryPool, 
    uint32_t firstQuery) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t accelerationStructureCount = AccelerationStructures.size();
    pfn_CmdWriteAccelerationStructuresPropertiesKHR(commandBuffer,
        accelerationStructureCount,
        AccelerationStructures.data(),
        queryType,
        queryPool,
        firstQuery);
}
[[nodiscard]] Result WriteAccelerationStructuresPropertiesKHR(detail::span<const AccelerationStructureKHR> AccelerationStructures, 
    QueryType queryType, 
    detail::span<std::byte> Data, 
    size_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t accelerationStructureCount = AccelerationStructures.size();
    size_t dataSize = Data.size();
    return pfn_WriteAccelerationStructuresPropertiesKHR(device,
        accelerationStructureCount,
        AccelerationStructures.data(),
        queryType,
        dataSize,
        Data.data(),
        stride);
}
[[nodiscard]] AccelerationStructureCompatibilityKHR GetDeviceAccelerationStructureCompatibilityKHR(const AccelerationStructureVersionInfoKHR&  pVersionInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AccelerationStructureCompatibilityKHR pCompatibility;
    pfn_GetDeviceAccelerationStructureCompatibilityKHR(device,
        &pVersionInfo,
        &pCompatibility);
    return pCompatibility;
}
[[nodiscard]] expected<AccelerationStructureKHR> CreateAccelerationStructureKHR(const AccelerationStructureCreateInfoKHR&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AccelerationStructureKHR pAccelerationStructure;
        Result result = pfn_CreateAccelerationStructureKHR(device,
        &pCreateInfo,
        pAllocator,
        &pAccelerationStructure);
    return expected<AccelerationStructureKHR>(pAccelerationStructure, result);
}
void CmdBuildAccelerationStructuresKHR(CommandBuffer commandBuffer, 
    detail::span<const AccelerationStructureBuildGeometryInfoKHR> Infos, 
    detail::span<const AccelerationStructureBuildRangeInfoKHR*> pBuildRangeInfos) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t infoCount = Infos.size();
    pfn_CmdBuildAccelerationStructuresKHR(commandBuffer,
        infoCount,
        Infos.data(),
        pBuildRangeInfos.data());
}
void CmdBuildAccelerationStructuresIndirectKHR(CommandBuffer commandBuffer, 
    detail::span<const AccelerationStructureBuildGeometryInfoKHR> Infos, 
    detail::span<const DeviceAddress> IndirectDeviceAddresses, 
    detail::span<const uint32_t> IndirectStrides, 
    detail::span<const uint32_t*> pMaxPrimitiveCounts) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t infoCount = Infos.size();
    pfn_CmdBuildAccelerationStructuresIndirectKHR(commandBuffer,
        infoCount,
        Infos.data(),
        IndirectDeviceAddresses.data(),
        IndirectStrides.data(),
        pMaxPrimitiveCounts.data());
}
[[nodiscard]] Result BuildAccelerationStructuresKHR(DeferredOperationKHR deferredOperation, 
    detail::span<const AccelerationStructureBuildGeometryInfoKHR> Infos, 
    detail::span<const AccelerationStructureBuildRangeInfoKHR*> pBuildRangeInfos) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t infoCount = Infos.size();
    return pfn_BuildAccelerationStructuresKHR(device,
        deferredOperation,
        infoCount,
        Infos.data(),
        pBuildRangeInfos.data());
}
[[nodiscard]] DeviceAddress GetAccelerationStructureDeviceAddressKHR(const AccelerationStructureDeviceAddressInfoKHR&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetAccelerationStructureDeviceAddressKHR(device,
        &pInfo);
}
[[nodiscard]] AccelerationStructureBuildSizesInfoKHR GetAccelerationStructureBuildSizesKHR(AccelerationStructureBuildTypeKHR buildType, 
    const AccelerationStructureBuildGeometryInfoKHR&  pBuildInfo, 
    const uint32_t* pMaxPrimitiveCounts) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AccelerationStructureBuildSizesInfoKHR pSizeInfo;
    pfn_GetAccelerationStructureBuildSizesKHR(device,
        buildType,
        &pBuildInfo,
        pMaxPrimitiveCounts,
        &pSizeInfo);
    return pSizeInfo;
}
void CmdTraceRaysKHR(CommandBuffer commandBuffer, 
    const StridedDeviceAddressRegionKHR&  pRaygenShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pMissShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pHitShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pCallableShaderBindingTable, 
    uint32_t width, 
    uint32_t height, 
    uint32_t depth) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdTraceRaysKHR(commandBuffer,
        &pRaygenShaderBindingTable,
        &pMissShaderBindingTable,
        &pHitShaderBindingTable,
        &pCallableShaderBindingTable,
        width,
        height,
        depth);
}
[[nodiscard]] Result GetRayTracingShaderGroupHandlesKHR(Pipeline pipeline, 
    uint32_t firstGroup, 
    uint32_t groupCount, 
    detail::span<std::byte> Data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t dataSize = Data.size();
    return pfn_GetRayTracingShaderGroupHandlesKHR(device,
        pipeline,
        firstGroup,
        groupCount,
        dataSize,
        Data.data());
}
[[nodiscard]] Result GetRayTracingCaptureReplayShaderGroupHandlesKHR(Pipeline pipeline, 
    uint32_t firstGroup, 
    uint32_t groupCount, 
    detail::span<std::byte> Data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t dataSize = Data.size();
    return pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR(device,
        pipeline,
        firstGroup,
        groupCount,
        dataSize,
        Data.data());
}
[[nodiscard]] Result CreateRayTracingPipelinesKHR(DeferredOperationKHR deferredOperation, 
    PipelineCache pipelineCache, 
    detail::span<const RayTracingPipelineCreateInfoKHR> CreateInfos, 
    const AllocationCallbacks* pAllocator, 
    detail::span<Pipeline> Pipelines) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t createInfoCount = CreateInfos.size();
    return pfn_CreateRayTracingPipelinesKHR(device,
        deferredOperation,
        pipelineCache,
        createInfoCount,
        CreateInfos.data(),
        pAllocator,
        Pipelines.data());
}
void CmdTraceRaysIndirectKHR(CommandBuffer commandBuffer, 
    const StridedDeviceAddressRegionKHR&  pRaygenShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pMissShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pHitShaderBindingTable, 
    const StridedDeviceAddressRegionKHR&  pCallableShaderBindingTable, 
    DeviceAddress indirectDeviceAddress) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdTraceRaysIndirectKHR(commandBuffer,
        &pRaygenShaderBindingTable,
        &pMissShaderBindingTable,
        &pHitShaderBindingTable,
        &pCallableShaderBindingTable,
        indirectDeviceAddress);
}
[[nodiscard]] DeviceSize GetRayTracingShaderGroupStackSizeKHR(Pipeline pipeline, 
    uint32_t group, 
    ShaderGroupShaderKHR groupShader) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetRayTracingShaderGroupStackSizeKHR(device,
        pipeline,
        group,
        groupShader);
}
void CmdSetRayTracingPipelineStackSizeKHR(CommandBuffer commandBuffer, 
    uint32_t pipelineStackSize) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetRayTracingPipelineStackSizeKHR(commandBuffer,
        pipelineStackSize);
}
[[nodiscard]] expected<ImageDrmFormatModifierPropertiesEXT> GetImageDrmFormatModifierPropertiesEXT(Image image) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ImageDrmFormatModifierPropertiesEXT pProperties;
        Result result = pfn_GetImageDrmFormatModifierPropertiesEXT(device,
        image,
        &pProperties);
    return expected<ImageDrmFormatModifierPropertiesEXT>(pProperties, result);
}
[[nodiscard]] expected<ValidationCacheEXT> CreateValidationCacheEXT(const ValidationCacheCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    ValidationCacheEXT pValidationCache;
        Result result = pfn_CreateValidationCacheEXT(device,
        &pCreateInfo,
        pAllocator,
        &pValidationCache);
    return expected<ValidationCacheEXT>(pValidationCache, result);
}
void DestroyValidationCacheEXT(ValidationCacheEXT validationCache = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyValidationCacheEXT(device,
        validationCache,
        pAllocator);
}
[[nodiscard]] expected<detail::fixed_vector<void*>> GetValidationCacheDataEXT(ValidationCacheEXT validationCache) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t pDataSize = 0;
        Result result = pfn_GetValidationCacheDataEXT(device,
        validationCache,
        &pDataSize,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<void*>{}, result);
    detail::fixed_vector<void*> pData{pDataSize};
    result = pfn_GetValidationCacheDataEXT(device,
        validationCache,
        &pDataSize,
        pData.data());
    if (pDataSize < pData.size()) pData.shrink(pDataSize);
    return expected(std::move(pData), result);
}
[[nodiscard]] Result MergeValidationCachesEXT(ValidationCacheEXT dstCache, 
    detail::span<const ValidationCacheEXT> SrcCaches) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t srcCacheCount = SrcCaches.size();
    return pfn_MergeValidationCachesEXT(device,
        dstCache,
        srcCacheCount,
        SrcCaches.data());
}
void CmdBindShadingRateImageNV(CommandBuffer commandBuffer, 
    ImageView imageView, 
    ImageLayout imageLayout) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBindShadingRateImageNV(commandBuffer,
        imageView,
        imageLayout);
}
void CmdSetViewportShadingRatePaletteNV(CommandBuffer commandBuffer, 
    uint32_t firstViewport, 
    detail::span<const ShadingRatePaletteNV> ShadingRatePalettes) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t viewportCount = ShadingRatePalettes.size();
    pfn_CmdSetViewportShadingRatePaletteNV(commandBuffer,
        firstViewport,
        viewportCount,
        ShadingRatePalettes.data());
}
void CmdSetCoarseSampleOrderNV(CommandBuffer commandBuffer, 
    CoarseSampleOrderTypeNV sampleOrderType, 
    detail::span<const CoarseSampleOrderCustomNV> CustomSampleOrders) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t customSampleOrderCount = CustomSampleOrders.size();
    pfn_CmdSetCoarseSampleOrderNV(commandBuffer,
        sampleOrderType,
        customSampleOrderCount,
        CustomSampleOrders.data());
}
[[nodiscard]] Result CompileDeferredNV(Pipeline pipeline, 
    uint32_t shader) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CompileDeferredNV(device,
        pipeline,
        shader);
}
[[nodiscard]] expected<AccelerationStructureNV> CreateAccelerationStructureNV(const AccelerationStructureCreateInfoNV&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    AccelerationStructureNV pAccelerationStructure;
        Result result = pfn_CreateAccelerationStructureNV(device,
        &pCreateInfo,
        pAllocator,
        &pAccelerationStructure);
    return expected<AccelerationStructureNV>(pAccelerationStructure, result);
}
void DestroyAccelerationStructureNV(AccelerationStructureNV accelerationStructure = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyAccelerationStructureNV(device,
        accelerationStructure,
        pAllocator);
}
[[nodiscard]] MemoryRequirements2KHR GetAccelerationStructureMemoryRequirementsNV(const AccelerationStructureMemoryRequirementsInfoNV&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements2KHR pMemoryRequirements;
    pfn_GetAccelerationStructureMemoryRequirementsNV(device,
        &pInfo,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] Result BindAccelerationStructureMemoryNV(detail::span<const BindAccelerationStructureMemoryInfoNV> BindInfos) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindInfoCount = BindInfos.size();
    return pfn_BindAccelerationStructureMemoryNV(device,
        bindInfoCount,
        BindInfos.data());
}
void CmdCopyAccelerationStructureNV(CommandBuffer commandBuffer, 
    AccelerationStructureNV dst, 
    AccelerationStructureNV src, 
    CopyAccelerationStructureModeKHR mode) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyAccelerationStructureNV(commandBuffer,
        dst,
        src,
        mode);
}
void CmdWriteAccelerationStructuresPropertiesNV(CommandBuffer commandBuffer, 
    detail::span<const AccelerationStructureNV> AccelerationStructures, 
    QueryType queryType, 
    QueryPool queryPool, 
    uint32_t firstQuery) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t accelerationStructureCount = AccelerationStructures.size();
    pfn_CmdWriteAccelerationStructuresPropertiesNV(commandBuffer,
        accelerationStructureCount,
        AccelerationStructures.data(),
        queryType,
        queryPool,
        firstQuery);
}
void CmdBuildAccelerationStructureNV(CommandBuffer commandBuffer, 
    const AccelerationStructureInfoNV&  pInfo, 
    Buffer instanceData, 
    DeviceSize instanceOffset, 
    Bool32 update, 
    AccelerationStructureNV dst, 
    AccelerationStructureNV src, 
    Buffer scratch, 
    DeviceSize scratchOffset) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBuildAccelerationStructureNV(commandBuffer,
        &pInfo,
        instanceData,
        instanceOffset,
        update,
        dst,
        src,
        scratch,
        scratchOffset);
}
void CmdTraceRaysNV(CommandBuffer commandBuffer, 
    Buffer raygenShaderBindingTableBuffer, 
    DeviceSize raygenShaderBindingOffset, 
    Buffer missShaderBindingTableBuffer, 
    DeviceSize missShaderBindingOffset, 
    DeviceSize missShaderBindingStride, 
    Buffer hitShaderBindingTableBuffer, 
    DeviceSize hitShaderBindingOffset, 
    DeviceSize hitShaderBindingStride, 
    Buffer callableShaderBindingTableBuffer, 
    DeviceSize callableShaderBindingOffset, 
    DeviceSize callableShaderBindingStride, 
    uint32_t width, 
    uint32_t height, 
    uint32_t depth) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdTraceRaysNV(commandBuffer,
        raygenShaderBindingTableBuffer,
        raygenShaderBindingOffset,
        missShaderBindingTableBuffer,
        missShaderBindingOffset,
        missShaderBindingStride,
        hitShaderBindingTableBuffer,
        hitShaderBindingOffset,
        hitShaderBindingStride,
        callableShaderBindingTableBuffer,
        callableShaderBindingOffset,
        callableShaderBindingStride,
        width,
        height,
        depth);
}
[[nodiscard]] Result GetAccelerationStructureHandleNV(AccelerationStructureNV accelerationStructure, 
    detail::span<std::byte> Data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    size_t dataSize = Data.size();
    return pfn_GetAccelerationStructureHandleNV(device,
        accelerationStructure,
        dataSize,
        Data.data());
}
[[nodiscard]] Result CreateRayTracingPipelinesNV(PipelineCache pipelineCache, 
    detail::span<const RayTracingPipelineCreateInfoNV> CreateInfos, 
    const AllocationCallbacks* pAllocator, 
    detail::span<Pipeline> Pipelines) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t createInfoCount = CreateInfos.size();
    return pfn_CreateRayTracingPipelinesNV(device,
        pipelineCache,
        createInfoCount,
        CreateInfos.data(),
        pAllocator,
        Pipelines.data());
}
[[nodiscard]] expected<MemoryHostPointerPropertiesEXT> GetMemoryHostPointerPropertiesEXT(ExternalMemoryHandleTypeFlagBits handleType, 
    const void* pHostPointer) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryHostPointerPropertiesEXT pMemoryHostPointerProperties;
        Result result = pfn_GetMemoryHostPointerPropertiesEXT(device,
        handleType,
        pHostPointer,
        &pMemoryHostPointerProperties);
    return expected<MemoryHostPointerPropertiesEXT>(pMemoryHostPointerProperties, result);
}
void CmdWriteBufferMarkerAMD(CommandBuffer commandBuffer, 
    PipelineStageFlagBits pipelineStage, 
    Buffer dstBuffer, 
    DeviceSize dstOffset, 
    uint32_t marker) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdWriteBufferMarkerAMD(commandBuffer,
        pipelineStage,
        dstBuffer,
        dstOffset,
        marker);
}
[[nodiscard]] expected<uint64_t> GetCalibratedTimestampsEXT(detail::span<const CalibratedTimestampInfoEXT> TimestampInfos, 
    detail::span<uint64_t> Timestamps) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t timestampCount = TimestampInfos.size();
    uint64_t pMaxDeviation;
        Result result = pfn_GetCalibratedTimestampsEXT(device,
        timestampCount,
        TimestampInfos.data(),
        Timestamps.data(),
        &pMaxDeviation);
    return expected<uint64_t>(pMaxDeviation, result);
}
void CmdDrawMeshTasksNV(CommandBuffer commandBuffer, 
    uint32_t taskCount, 
    uint32_t firstTask) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawMeshTasksNV(commandBuffer,
        taskCount,
        firstTask);
}
void CmdDrawMeshTasksIndirectNV(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    uint32_t drawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawMeshTasksIndirectNV(commandBuffer,
        buffer,
        offset,
        drawCount,
        stride);
}
void CmdDrawMeshTasksIndirectCountNV(CommandBuffer commandBuffer, 
    Buffer buffer, 
    DeviceSize offset, 
    Buffer countBuffer, 
    DeviceSize countBufferOffset, 
    uint32_t maxDrawCount, 
    uint32_t stride) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdDrawMeshTasksIndirectCountNV(commandBuffer,
        buffer,
        offset,
        countBuffer,
        countBufferOffset,
        maxDrawCount,
        stride);
}
void CmdSetExclusiveScissorNV(CommandBuffer commandBuffer, 
    uint32_t firstExclusiveScissor, 
    detail::span<const Rect2D> ExclusiveScissors) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t exclusiveScissorCount = ExclusiveScissors.size();
    pfn_CmdSetExclusiveScissorNV(commandBuffer,
        firstExclusiveScissor,
        exclusiveScissorCount,
        ExclusiveScissors.data());
}
void CmdSetCheckpointNV(CommandBuffer commandBuffer, 
    const void* pCheckpointMarker) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetCheckpointNV(commandBuffer,
        pCheckpointMarker);
}
[[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetQueueCheckpointDataNV(Queue queue) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pCheckpointDataCount = 0;
    pfn_GetQueueCheckpointDataNV(queue,
        &pCheckpointDataCount,
        nullptr);
    detail::fixed_vector<CheckpointDataNV> pCheckpointData{pCheckpointDataCount};
pfn_GetQueueCheckpointDataNV(queue,
        &pCheckpointDataCount,
        pCheckpointData.data());
    if (pCheckpointDataCount < pCheckpointData.size()) pCheckpointData.shrink(pCheckpointDataCount);
    return pCheckpointData;
}
[[nodiscard]] Result InitializePerformanceApiINTEL(const InitializePerformanceApiInfoINTEL&  pInitializeInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_InitializePerformanceApiINTEL(device,
        &pInitializeInfo);
}
void UninitializePerformanceApiINTEL() const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_UninitializePerformanceApiINTEL(device);
}
[[nodiscard]] Result CmdSetPerformanceMarkerINTEL(CommandBuffer commandBuffer, 
    const PerformanceMarkerInfoINTEL&  pMarkerInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CmdSetPerformanceMarkerINTEL(commandBuffer,
        &pMarkerInfo);
}
[[nodiscard]] Result CmdSetPerformanceStreamMarkerINTEL(CommandBuffer commandBuffer, 
    const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CmdSetPerformanceStreamMarkerINTEL(commandBuffer,
        &pMarkerInfo);
}
[[nodiscard]] Result CmdSetPerformanceOverrideINTEL(CommandBuffer commandBuffer, 
    const PerformanceOverrideInfoINTEL&  pOverrideInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_CmdSetPerformanceOverrideINTEL(commandBuffer,
        &pOverrideInfo);
}
[[nodiscard]] expected<PerformanceConfigurationINTEL> AcquirePerformanceConfigurationINTEL(const PerformanceConfigurationAcquireInfoINTEL&  pAcquireInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PerformanceConfigurationINTEL pConfiguration;
        Result result = pfn_AcquirePerformanceConfigurationINTEL(device,
        &pAcquireInfo,
        &pConfiguration);
    return expected<PerformanceConfigurationINTEL>(pConfiguration, result);
}
[[nodiscard]] Result ReleasePerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ReleasePerformanceConfigurationINTEL(device,
        configuration);
}
[[nodiscard]] Result QueueSetPerformanceConfigurationINTEL(Queue queue, 
    PerformanceConfigurationINTEL configuration) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_QueueSetPerformanceConfigurationINTEL(queue,
        configuration);
}
[[nodiscard]] expected<PerformanceValueINTEL> GetPerformanceParameterINTEL(PerformanceParameterTypeINTEL parameter) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PerformanceValueINTEL pValue;
        Result result = pfn_GetPerformanceParameterINTEL(device,
        parameter,
        &pValue);
    return expected<PerformanceValueINTEL>(pValue, result);
}
void SetLocalDimmingAMD(SwapchainKHR swapChain, 
    Bool32 localDimmingEnable) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_SetLocalDimmingAMD(device,
        swapChain,
        localDimmingEnable);
}
void CmdSetFragmentShadingRateKHR(CommandBuffer commandBuffer, 
    const Extent2D&  pFragmentSize, 
    const FragmentShadingRateCombinerOpKHR combinerOps[2]) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetFragmentShadingRateKHR(commandBuffer,
        &pFragmentSize,
        combinerOps);
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Result AcquireFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_AcquireFullScreenExclusiveModeEXT(device,
        swapchain);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Result ReleaseFullScreenExclusiveModeEXT(SwapchainKHR swapchain) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_ReleaseFullScreenExclusiveModeEXT(device,
        swapchain);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<DeviceGroupPresentModeFlagsKHR> GetDeviceGroupSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeviceGroupPresentModeFlagsKHR pModes;
        Result result = pfn_GetDeviceGroupSurfacePresentModes2EXT(device,
        &pSurfaceInfo,
        &pModes);
    return expected<DeviceGroupPresentModeFlagsKHR>(pModes, result);
}
#endif // VK_USE_PLATFORM_WIN32_KHR
void CmdSetLineStippleEXT(CommandBuffer commandBuffer, 
    uint32_t lineStippleFactor, 
    uint16_t lineStipplePattern) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetLineStippleEXT(commandBuffer,
        lineStippleFactor,
        lineStipplePattern);
}
void CmdSetCullModeEXT(CommandBuffer commandBuffer, 
    CullModeFlags cullMode = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetCullModeEXT(commandBuffer,
        cullMode);
}
void CmdSetFrontFaceEXT(CommandBuffer commandBuffer, 
    FrontFace frontFace) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetFrontFaceEXT(commandBuffer,
        frontFace);
}
void CmdSetPrimitiveTopologyEXT(CommandBuffer commandBuffer, 
    PrimitiveTopology primitiveTopology) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetPrimitiveTopologyEXT(commandBuffer,
        primitiveTopology);
}
void CmdSetViewportWithCountEXT(CommandBuffer commandBuffer, 
    detail::span<const Viewport> Viewports) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t viewportCount = Viewports.size();
    pfn_CmdSetViewportWithCountEXT(commandBuffer,
        viewportCount,
        Viewports.data());
}
void CmdSetScissorWithCountEXT(CommandBuffer commandBuffer, 
    detail::span<const Rect2D> Scissors) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t scissorCount = Scissors.size();
    pfn_CmdSetScissorWithCountEXT(commandBuffer,
        scissorCount,
        Scissors.data());
}
void CmdBindVertexBuffers2EXT(CommandBuffer commandBuffer, 
    uint32_t firstBinding, 
    detail::span<const Buffer> Buffers, 
    detail::span<const DeviceSize> Offsets, 
    detail::span<const DeviceSize> Sizes = {}, 
    detail::span<const DeviceSize> Strides = {}) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t bindingCount = Buffers.size();
    pfn_CmdBindVertexBuffers2EXT(commandBuffer,
        firstBinding,
        bindingCount,
        Buffers.data(),
        Offsets.data(),
        Sizes.data(),
        Strides.data());
}
void CmdSetDepthTestEnableEXT(CommandBuffer commandBuffer, 
    Bool32 depthTestEnable) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthTestEnableEXT(commandBuffer,
        depthTestEnable);
}
void CmdSetDepthWriteEnableEXT(CommandBuffer commandBuffer, 
    Bool32 depthWriteEnable) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthWriteEnableEXT(commandBuffer,
        depthWriteEnable);
}
void CmdSetDepthCompareOpEXT(CommandBuffer commandBuffer, 
    CompareOp depthCompareOp) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthCompareOpEXT(commandBuffer,
        depthCompareOp);
}
void CmdSetDepthBoundsTestEnableEXT(CommandBuffer commandBuffer, 
    Bool32 depthBoundsTestEnable) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetDepthBoundsTestEnableEXT(commandBuffer,
        depthBoundsTestEnable);
}
void CmdSetStencilTestEnableEXT(CommandBuffer commandBuffer, 
    Bool32 stencilTestEnable) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetStencilTestEnableEXT(commandBuffer,
        stencilTestEnable);
}
void CmdSetStencilOpEXT(CommandBuffer commandBuffer, 
    StencilFaceFlags faceMask, 
    StencilOp failOp, 
    StencilOp passOp, 
    StencilOp depthFailOp, 
    CompareOp compareOp) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetStencilOpEXT(commandBuffer,
        faceMask,
        failOp,
        passOp,
        depthFailOp,
        compareOp);
}
[[nodiscard]] expected<DeferredOperationKHR> CreateDeferredOperationKHR(const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    DeferredOperationKHR pDeferredOperation;
        Result result = pfn_CreateDeferredOperationKHR(device,
        pAllocator,
        &pDeferredOperation);
    return expected<DeferredOperationKHR>(pDeferredOperation, result);
}
void DestroyDeferredOperationKHR(DeferredOperationKHR operation = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyDeferredOperationKHR(device,
        operation,
        pAllocator);
}
[[nodiscard]] uint32_t GetDeferredOperationMaxConcurrencyKHR(DeferredOperationKHR operation) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetDeferredOperationMaxConcurrencyKHR(device,
        operation);
}
[[nodiscard]] Result GetDeferredOperationResultKHR(DeferredOperationKHR operation) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_GetDeferredOperationResultKHR(device,
        operation);
}
[[nodiscard]] Result DeferredOperationJoinKHR(DeferredOperationKHR operation) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_DeferredOperationJoinKHR(device,
        operation);
}
[[nodiscard]] expected<detail::fixed_vector<PipelineExecutablePropertiesKHR>> GetPipelineExecutablePropertiesKHR(const PipelineInfoKHR&  pPipelineInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pExecutableCount = 0;
        Result result = pfn_GetPipelineExecutablePropertiesKHR(device,
        &pPipelineInfo,
        &pExecutableCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutablePropertiesKHR>{}, result);
    detail::fixed_vector<PipelineExecutablePropertiesKHR> pProperties{pExecutableCount};
    result = pfn_GetPipelineExecutablePropertiesKHR(device,
        &pPipelineInfo,
        &pExecutableCount,
        pProperties.data());
    if (pExecutableCount < pProperties.size()) pProperties.shrink(pExecutableCount);
    return expected(std::move(pProperties), result);
}
[[nodiscard]] expected<detail::fixed_vector<PipelineExecutableStatisticKHR>> GetPipelineExecutableStatisticsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pStatisticCount = 0;
        Result result = pfn_GetPipelineExecutableStatisticsKHR(device,
        &pExecutableInfo,
        &pStatisticCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutableStatisticKHR>{}, result);
    detail::fixed_vector<PipelineExecutableStatisticKHR> pStatistics{pStatisticCount};
    result = pfn_GetPipelineExecutableStatisticsKHR(device,
        &pExecutableInfo,
        &pStatisticCount,
        pStatistics.data());
    if (pStatisticCount < pStatistics.size()) pStatistics.shrink(pStatisticCount);
    return expected(std::move(pStatistics), result);
}
[[nodiscard]] expected<detail::fixed_vector<PipelineExecutableInternalRepresentationKHR>> GetPipelineExecutableInternalRepresentationsKHR(const PipelineExecutableInfoKHR&  pExecutableInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint32_t pInternalRepresentationCount = 0;
        Result result = pfn_GetPipelineExecutableInternalRepresentationsKHR(device,
        &pExecutableInfo,
        &pInternalRepresentationCount,
        nullptr);
    if (result < Result::Success) return expected(detail::fixed_vector<PipelineExecutableInternalRepresentationKHR>{}, result);
    detail::fixed_vector<PipelineExecutableInternalRepresentationKHR> pInternalRepresentations{pInternalRepresentationCount};
    result = pfn_GetPipelineExecutableInternalRepresentationsKHR(device,
        &pExecutableInfo,
        &pInternalRepresentationCount,
        pInternalRepresentations.data());
    if (pInternalRepresentationCount < pInternalRepresentations.size()) pInternalRepresentations.shrink(pInternalRepresentationCount);
    return expected(std::move(pInternalRepresentations), result);
}
void CmdExecuteGeneratedCommandsNV(CommandBuffer commandBuffer, 
    Bool32 isPreprocessed, 
    const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdExecuteGeneratedCommandsNV(commandBuffer,
        isPreprocessed,
        &pGeneratedCommandsInfo);
}
void CmdPreprocessGeneratedCommandsNV(CommandBuffer commandBuffer, 
    const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdPreprocessGeneratedCommandsNV(commandBuffer,
        &pGeneratedCommandsInfo);
}
void CmdBindPipelineShaderGroupNV(CommandBuffer commandBuffer, 
    PipelineBindPoint pipelineBindPoint, 
    Pipeline pipeline, 
    uint32_t groupIndex) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBindPipelineShaderGroupNV(commandBuffer,
        pipelineBindPoint,
        pipeline,
        groupIndex);
}
[[nodiscard]] MemoryRequirements2 GetGeneratedCommandsMemoryRequirementsNV(const GeneratedCommandsMemoryRequirementsInfoNV&  pInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    MemoryRequirements2 pMemoryRequirements;
    pfn_GetGeneratedCommandsMemoryRequirementsNV(device,
        &pInfo,
        &pMemoryRequirements);
    return pMemoryRequirements;
}
[[nodiscard]] expected<IndirectCommandsLayoutNV> CreateIndirectCommandsLayoutNV(const IndirectCommandsLayoutCreateInfoNV&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    IndirectCommandsLayoutNV pIndirectCommandsLayout;
        Result result = pfn_CreateIndirectCommandsLayoutNV(device,
        &pCreateInfo,
        pAllocator,
        &pIndirectCommandsLayout);
    return expected<IndirectCommandsLayoutNV>(pIndirectCommandsLayout, result);
}
void DestroyIndirectCommandsLayoutNV(IndirectCommandsLayoutNV indirectCommandsLayout = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyIndirectCommandsLayoutNV(device,
        indirectCommandsLayout,
        pAllocator);
}
[[nodiscard]] expected<PrivateDataSlotEXT> CreatePrivateDataSlotEXT(const PrivateDataSlotCreateInfoEXT&  pCreateInfo, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    PrivateDataSlotEXT pPrivateDataSlot;
        Result result = pfn_CreatePrivateDataSlotEXT(device,
        &pCreateInfo,
        pAllocator,
        &pPrivateDataSlot);
    return expected<PrivateDataSlotEXT>(pPrivateDataSlot, result);
}
void DestroyPrivateDataSlotEXT(PrivateDataSlotEXT privateDataSlot = {}, 
    const AllocationCallbacks* pAllocator = nullptr) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_DestroyPrivateDataSlotEXT(device,
        privateDataSlot,
        pAllocator);
}
[[nodiscard]] Result SetPrivateDataEXT(ObjectType objectType, 
    uint64_t objectHandle, 
    PrivateDataSlotEXT privateDataSlot, 
    uint64_t data) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    return pfn_SetPrivateDataEXT(device,
        objectType,
        objectHandle,
        privateDataSlot,
        data);
}
[[nodiscard]] uint64_t GetPrivateDataEXT(ObjectType objectType, 
    uint64_t objectHandle, 
    PrivateDataSlotEXT privateDataSlot) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    uint64_t pData;
    pfn_GetPrivateDataEXT(device,
        objectType,
        objectHandle,
        privateDataSlot,
        &pData);
    return pData;
}
void CmdSetFragmentShadingRateEnumNV(CommandBuffer commandBuffer, 
    FragmentShadingRateNV shadingRate, 
    const FragmentShadingRateCombinerOpKHR combinerOps[2]) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdSetFragmentShadingRateEnumNV(commandBuffer,
        shadingRate,
        combinerOps);
}
void CmdCopyBuffer2KHR(CommandBuffer commandBuffer, 
    const CopyBufferInfo2KHR&  pCopyBufferInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyBuffer2KHR(commandBuffer,
        &pCopyBufferInfo);
}
void CmdCopyImage2KHR(CommandBuffer commandBuffer, 
    const CopyImageInfo2KHR&  pCopyImageInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyImage2KHR(commandBuffer,
        &pCopyImageInfo);
}
void CmdBlitImage2KHR(CommandBuffer commandBuffer, 
    const BlitImageInfo2KHR&  pBlitImageInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdBlitImage2KHR(commandBuffer,
        &pBlitImageInfo);
}
void CmdCopyBufferToImage2KHR(CommandBuffer commandBuffer, 
    const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyBufferToImage2KHR(commandBuffer,
        &pCopyBufferToImageInfo);
}
void CmdCopyImageToBuffer2KHR(CommandBuffer commandBuffer, 
    const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdCopyImageToBuffer2KHR(commandBuffer,
        &pCopyImageToBufferInfo);
}
void CmdResolveImage2KHR(CommandBuffer commandBuffer, 
    const ResolveImageInfo2KHR&  pResolveImageInfo) const {
    VK_MODULE_LEAK_SANITIZER_SUPPRESSION_CODE
    pfn_CmdResolveImage2KHR(commandBuffer,
        &pResolveImageInfo);
}
DeviceFunctions() noexcept {}
explicit DeviceFunctions(InstanceFunctions const& instance_functions, Device device) noexcept 
    :device(device) {
    detail::PFN_GetDeviceProcAddr get_device_proc_addr = instance_functions.pfn_GetDeviceProcAddr;
    pfn_DestroyDevice = reinterpret_cast<detail::PFN_DestroyDevice>(get_device_proc_addr(device,"vkDestroyDevice"));
    pfn_GetDeviceQueue = reinterpret_cast<detail::PFN_GetDeviceQueue>(get_device_proc_addr(device,"vkGetDeviceQueue"));
    pfn_QueueSubmit = reinterpret_cast<detail::PFN_QueueSubmit>(get_device_proc_addr(device,"vkQueueSubmit"));
    pfn_QueueWaitIdle = reinterpret_cast<detail::PFN_QueueWaitIdle>(get_device_proc_addr(device,"vkQueueWaitIdle"));
    pfn_DeviceWaitIdle = reinterpret_cast<detail::PFN_DeviceWaitIdle>(get_device_proc_addr(device,"vkDeviceWaitIdle"));
    pfn_AllocateMemory = reinterpret_cast<detail::PFN_AllocateMemory>(get_device_proc_addr(device,"vkAllocateMemory"));
    pfn_FreeMemory = reinterpret_cast<detail::PFN_FreeMemory>(get_device_proc_addr(device,"vkFreeMemory"));
    pfn_MapMemory = reinterpret_cast<detail::PFN_MapMemory>(get_device_proc_addr(device,"vkMapMemory"));
    pfn_UnmapMemory = reinterpret_cast<detail::PFN_UnmapMemory>(get_device_proc_addr(device,"vkUnmapMemory"));
    pfn_FlushMappedMemoryRanges = reinterpret_cast<detail::PFN_FlushMappedMemoryRanges>(get_device_proc_addr(device,"vkFlushMappedMemoryRanges"));
    pfn_InvalidateMappedMemoryRanges = reinterpret_cast<detail::PFN_InvalidateMappedMemoryRanges>(get_device_proc_addr(device,"vkInvalidateMappedMemoryRanges"));
    pfn_GetDeviceMemoryCommitment = reinterpret_cast<detail::PFN_GetDeviceMemoryCommitment>(get_device_proc_addr(device,"vkGetDeviceMemoryCommitment"));
    pfn_GetBufferMemoryRequirements = reinterpret_cast<detail::PFN_GetBufferMemoryRequirements>(get_device_proc_addr(device,"vkGetBufferMemoryRequirements"));
    pfn_BindBufferMemory = reinterpret_cast<detail::PFN_BindBufferMemory>(get_device_proc_addr(device,"vkBindBufferMemory"));
    pfn_GetImageMemoryRequirements = reinterpret_cast<detail::PFN_GetImageMemoryRequirements>(get_device_proc_addr(device,"vkGetImageMemoryRequirements"));
    pfn_BindImageMemory = reinterpret_cast<detail::PFN_BindImageMemory>(get_device_proc_addr(device,"vkBindImageMemory"));
    pfn_GetImageSparseMemoryRequirements = reinterpret_cast<detail::PFN_GetImageSparseMemoryRequirements>(get_device_proc_addr(device,"vkGetImageSparseMemoryRequirements"));
    pfn_QueueBindSparse = reinterpret_cast<detail::PFN_QueueBindSparse>(get_device_proc_addr(device,"vkQueueBindSparse"));
    pfn_CreateFence = reinterpret_cast<detail::PFN_CreateFence>(get_device_proc_addr(device,"vkCreateFence"));
    pfn_DestroyFence = reinterpret_cast<detail::PFN_DestroyFence>(get_device_proc_addr(device,"vkDestroyFence"));
    pfn_ResetFences = reinterpret_cast<detail::PFN_ResetFences>(get_device_proc_addr(device,"vkResetFences"));
    pfn_GetFenceStatus = reinterpret_cast<detail::PFN_GetFenceStatus>(get_device_proc_addr(device,"vkGetFenceStatus"));
    pfn_WaitForFences = reinterpret_cast<detail::PFN_WaitForFences>(get_device_proc_addr(device,"vkWaitForFences"));
    pfn_CreateSemaphore = reinterpret_cast<detail::PFN_CreateSemaphore>(get_device_proc_addr(device,"vkCreateSemaphore"));
    pfn_DestroySemaphore = reinterpret_cast<detail::PFN_DestroySemaphore>(get_device_proc_addr(device,"vkDestroySemaphore"));
    pfn_CreateEvent = reinterpret_cast<detail::PFN_CreateEvent>(get_device_proc_addr(device,"vkCreateEvent"));
    pfn_DestroyEvent = reinterpret_cast<detail::PFN_DestroyEvent>(get_device_proc_addr(device,"vkDestroyEvent"));
    pfn_GetEventStatus = reinterpret_cast<detail::PFN_GetEventStatus>(get_device_proc_addr(device,"vkGetEventStatus"));
    pfn_SetEvent = reinterpret_cast<detail::PFN_SetEvent>(get_device_proc_addr(device,"vkSetEvent"));
    pfn_ResetEvent = reinterpret_cast<detail::PFN_ResetEvent>(get_device_proc_addr(device,"vkResetEvent"));
    pfn_CreateQueryPool = reinterpret_cast<detail::PFN_CreateQueryPool>(get_device_proc_addr(device,"vkCreateQueryPool"));
    pfn_DestroyQueryPool = reinterpret_cast<detail::PFN_DestroyQueryPool>(get_device_proc_addr(device,"vkDestroyQueryPool"));
    pfn_GetQueryPoolResults = reinterpret_cast<detail::PFN_GetQueryPoolResults>(get_device_proc_addr(device,"vkGetQueryPoolResults"));
    pfn_CreateBuffer = reinterpret_cast<detail::PFN_CreateBuffer>(get_device_proc_addr(device,"vkCreateBuffer"));
    pfn_DestroyBuffer = reinterpret_cast<detail::PFN_DestroyBuffer>(get_device_proc_addr(device,"vkDestroyBuffer"));
    pfn_CreateBufferView = reinterpret_cast<detail::PFN_CreateBufferView>(get_device_proc_addr(device,"vkCreateBufferView"));
    pfn_DestroyBufferView = reinterpret_cast<detail::PFN_DestroyBufferView>(get_device_proc_addr(device,"vkDestroyBufferView"));
    pfn_CreateImage = reinterpret_cast<detail::PFN_CreateImage>(get_device_proc_addr(device,"vkCreateImage"));
    pfn_DestroyImage = reinterpret_cast<detail::PFN_DestroyImage>(get_device_proc_addr(device,"vkDestroyImage"));
    pfn_GetImageSubresourceLayout = reinterpret_cast<detail::PFN_GetImageSubresourceLayout>(get_device_proc_addr(device,"vkGetImageSubresourceLayout"));
    pfn_CreateImageView = reinterpret_cast<detail::PFN_CreateImageView>(get_device_proc_addr(device,"vkCreateImageView"));
    pfn_DestroyImageView = reinterpret_cast<detail::PFN_DestroyImageView>(get_device_proc_addr(device,"vkDestroyImageView"));
    pfn_CreateShaderModule = reinterpret_cast<detail::PFN_CreateShaderModule>(get_device_proc_addr(device,"vkCreateShaderModule"));
    pfn_DestroyShaderModule = reinterpret_cast<detail::PFN_DestroyShaderModule>(get_device_proc_addr(device,"vkDestroyShaderModule"));
    pfn_CreatePipelineCache = reinterpret_cast<detail::PFN_CreatePipelineCache>(get_device_proc_addr(device,"vkCreatePipelineCache"));
    pfn_DestroyPipelineCache = reinterpret_cast<detail::PFN_DestroyPipelineCache>(get_device_proc_addr(device,"vkDestroyPipelineCache"));
    pfn_GetPipelineCacheData = reinterpret_cast<detail::PFN_GetPipelineCacheData>(get_device_proc_addr(device,"vkGetPipelineCacheData"));
    pfn_MergePipelineCaches = reinterpret_cast<detail::PFN_MergePipelineCaches>(get_device_proc_addr(device,"vkMergePipelineCaches"));
    pfn_CreateGraphicsPipelines = reinterpret_cast<detail::PFN_CreateGraphicsPipelines>(get_device_proc_addr(device,"vkCreateGraphicsPipelines"));
    pfn_CreateComputePipelines = reinterpret_cast<detail::PFN_CreateComputePipelines>(get_device_proc_addr(device,"vkCreateComputePipelines"));
    pfn_DestroyPipeline = reinterpret_cast<detail::PFN_DestroyPipeline>(get_device_proc_addr(device,"vkDestroyPipeline"));
    pfn_CreatePipelineLayout = reinterpret_cast<detail::PFN_CreatePipelineLayout>(get_device_proc_addr(device,"vkCreatePipelineLayout"));
    pfn_DestroyPipelineLayout = reinterpret_cast<detail::PFN_DestroyPipelineLayout>(get_device_proc_addr(device,"vkDestroyPipelineLayout"));
    pfn_CreateSampler = reinterpret_cast<detail::PFN_CreateSampler>(get_device_proc_addr(device,"vkCreateSampler"));
    pfn_DestroySampler = reinterpret_cast<detail::PFN_DestroySampler>(get_device_proc_addr(device,"vkDestroySampler"));
    pfn_CreateDescriptorSetLayout = reinterpret_cast<detail::PFN_CreateDescriptorSetLayout>(get_device_proc_addr(device,"vkCreateDescriptorSetLayout"));
    pfn_DestroyDescriptorSetLayout = reinterpret_cast<detail::PFN_DestroyDescriptorSetLayout>(get_device_proc_addr(device,"vkDestroyDescriptorSetLayout"));
    pfn_CreateDescriptorPool = reinterpret_cast<detail::PFN_CreateDescriptorPool>(get_device_proc_addr(device,"vkCreateDescriptorPool"));
    pfn_DestroyDescriptorPool = reinterpret_cast<detail::PFN_DestroyDescriptorPool>(get_device_proc_addr(device,"vkDestroyDescriptorPool"));
    pfn_ResetDescriptorPool = reinterpret_cast<detail::PFN_ResetDescriptorPool>(get_device_proc_addr(device,"vkResetDescriptorPool"));
    pfn_AllocateDescriptorSets = reinterpret_cast<detail::PFN_AllocateDescriptorSets>(get_device_proc_addr(device,"vkAllocateDescriptorSets"));
    pfn_FreeDescriptorSets = reinterpret_cast<detail::PFN_FreeDescriptorSets>(get_device_proc_addr(device,"vkFreeDescriptorSets"));
    pfn_UpdateDescriptorSets = reinterpret_cast<detail::PFN_UpdateDescriptorSets>(get_device_proc_addr(device,"vkUpdateDescriptorSets"));
    pfn_CreateFramebuffer = reinterpret_cast<detail::PFN_CreateFramebuffer>(get_device_proc_addr(device,"vkCreateFramebuffer"));
    pfn_DestroyFramebuffer = reinterpret_cast<detail::PFN_DestroyFramebuffer>(get_device_proc_addr(device,"vkDestroyFramebuffer"));
    pfn_CreateRenderPass = reinterpret_cast<detail::PFN_CreateRenderPass>(get_device_proc_addr(device,"vkCreateRenderPass"));
    pfn_DestroyRenderPass = reinterpret_cast<detail::PFN_DestroyRenderPass>(get_device_proc_addr(device,"vkDestroyRenderPass"));
    pfn_GetRenderAreaGranularity = reinterpret_cast<detail::PFN_GetRenderAreaGranularity>(get_device_proc_addr(device,"vkGetRenderAreaGranularity"));
    pfn_CreateCommandPool = reinterpret_cast<detail::PFN_CreateCommandPool>(get_device_proc_addr(device,"vkCreateCommandPool"));
    pfn_DestroyCommandPool = reinterpret_cast<detail::PFN_DestroyCommandPool>(get_device_proc_addr(device,"vkDestroyCommandPool"));
    pfn_ResetCommandPool = reinterpret_cast<detail::PFN_ResetCommandPool>(get_device_proc_addr(device,"vkResetCommandPool"));
    pfn_AllocateCommandBuffers = reinterpret_cast<detail::PFN_AllocateCommandBuffers>(get_device_proc_addr(device,"vkAllocateCommandBuffers"));
    pfn_FreeCommandBuffers = reinterpret_cast<detail::PFN_FreeCommandBuffers>(get_device_proc_addr(device,"vkFreeCommandBuffers"));
    pfn_BeginCommandBuffer = reinterpret_cast<detail::PFN_BeginCommandBuffer>(get_device_proc_addr(device,"vkBeginCommandBuffer"));
    pfn_EndCommandBuffer = reinterpret_cast<detail::PFN_EndCommandBuffer>(get_device_proc_addr(device,"vkEndCommandBuffer"));
    pfn_ResetCommandBuffer = reinterpret_cast<detail::PFN_ResetCommandBuffer>(get_device_proc_addr(device,"vkResetCommandBuffer"));
    pfn_CmdBindPipeline = reinterpret_cast<detail::PFN_CmdBindPipeline>(get_device_proc_addr(device,"vkCmdBindPipeline"));
    pfn_CmdSetViewport = reinterpret_cast<detail::PFN_CmdSetViewport>(get_device_proc_addr(device,"vkCmdSetViewport"));
    pfn_CmdSetScissor = reinterpret_cast<detail::PFN_CmdSetScissor>(get_device_proc_addr(device,"vkCmdSetScissor"));
    pfn_CmdSetLineWidth = reinterpret_cast<detail::PFN_CmdSetLineWidth>(get_device_proc_addr(device,"vkCmdSetLineWidth"));
    pfn_CmdSetDepthBias = reinterpret_cast<detail::PFN_CmdSetDepthBias>(get_device_proc_addr(device,"vkCmdSetDepthBias"));
    pfn_CmdSetBlendConstants = reinterpret_cast<detail::PFN_CmdSetBlendConstants>(get_device_proc_addr(device,"vkCmdSetBlendConstants"));
    pfn_CmdSetDepthBounds = reinterpret_cast<detail::PFN_CmdSetDepthBounds>(get_device_proc_addr(device,"vkCmdSetDepthBounds"));
    pfn_CmdSetStencilCompareMask = reinterpret_cast<detail::PFN_CmdSetStencilCompareMask>(get_device_proc_addr(device,"vkCmdSetStencilCompareMask"));
    pfn_CmdSetStencilWriteMask = reinterpret_cast<detail::PFN_CmdSetStencilWriteMask>(get_device_proc_addr(device,"vkCmdSetStencilWriteMask"));
    pfn_CmdSetStencilReference = reinterpret_cast<detail::PFN_CmdSetStencilReference>(get_device_proc_addr(device,"vkCmdSetStencilReference"));
    pfn_CmdBindDescriptorSets = reinterpret_cast<detail::PFN_CmdBindDescriptorSets>(get_device_proc_addr(device,"vkCmdBindDescriptorSets"));
    pfn_CmdBindIndexBuffer = reinterpret_cast<detail::PFN_CmdBindIndexBuffer>(get_device_proc_addr(device,"vkCmdBindIndexBuffer"));
    pfn_CmdBindVertexBuffers = reinterpret_cast<detail::PFN_CmdBindVertexBuffers>(get_device_proc_addr(device,"vkCmdBindVertexBuffers"));
    pfn_CmdDraw = reinterpret_cast<detail::PFN_CmdDraw>(get_device_proc_addr(device,"vkCmdDraw"));
    pfn_CmdDrawIndexed = reinterpret_cast<detail::PFN_CmdDrawIndexed>(get_device_proc_addr(device,"vkCmdDrawIndexed"));
    pfn_CmdDrawIndirect = reinterpret_cast<detail::PFN_CmdDrawIndirect>(get_device_proc_addr(device,"vkCmdDrawIndirect"));
    pfn_CmdDrawIndexedIndirect = reinterpret_cast<detail::PFN_CmdDrawIndexedIndirect>(get_device_proc_addr(device,"vkCmdDrawIndexedIndirect"));
    pfn_CmdDispatch = reinterpret_cast<detail::PFN_CmdDispatch>(get_device_proc_addr(device,"vkCmdDispatch"));
    pfn_CmdDispatchIndirect = reinterpret_cast<detail::PFN_CmdDispatchIndirect>(get_device_proc_addr(device,"vkCmdDispatchIndirect"));
    pfn_CmdCopyBuffer = reinterpret_cast<detail::PFN_CmdCopyBuffer>(get_device_proc_addr(device,"vkCmdCopyBuffer"));
    pfn_CmdCopyImage = reinterpret_cast<detail::PFN_CmdCopyImage>(get_device_proc_addr(device,"vkCmdCopyImage"));
    pfn_CmdBlitImage = reinterpret_cast<detail::PFN_CmdBlitImage>(get_device_proc_addr(device,"vkCmdBlitImage"));
    pfn_CmdCopyBufferToImage = reinterpret_cast<detail::PFN_CmdCopyBufferToImage>(get_device_proc_addr(device,"vkCmdCopyBufferToImage"));
    pfn_CmdCopyImageToBuffer = reinterpret_cast<detail::PFN_CmdCopyImageToBuffer>(get_device_proc_addr(device,"vkCmdCopyImageToBuffer"));
    pfn_CmdUpdateBuffer = reinterpret_cast<detail::PFN_CmdUpdateBuffer>(get_device_proc_addr(device,"vkCmdUpdateBuffer"));
    pfn_CmdFillBuffer = reinterpret_cast<detail::PFN_CmdFillBuffer>(get_device_proc_addr(device,"vkCmdFillBuffer"));
    pfn_CmdClearColorImage = reinterpret_cast<detail::PFN_CmdClearColorImage>(get_device_proc_addr(device,"vkCmdClearColorImage"));
    pfn_CmdClearDepthStencilImage = reinterpret_cast<detail::PFN_CmdClearDepthStencilImage>(get_device_proc_addr(device,"vkCmdClearDepthStencilImage"));
    pfn_CmdClearAttachments = reinterpret_cast<detail::PFN_CmdClearAttachments>(get_device_proc_addr(device,"vkCmdClearAttachments"));
    pfn_CmdResolveImage = reinterpret_cast<detail::PFN_CmdResolveImage>(get_device_proc_addr(device,"vkCmdResolveImage"));
    pfn_CmdSetEvent = reinterpret_cast<detail::PFN_CmdSetEvent>(get_device_proc_addr(device,"vkCmdSetEvent"));
    pfn_CmdResetEvent = reinterpret_cast<detail::PFN_CmdResetEvent>(get_device_proc_addr(device,"vkCmdResetEvent"));
    pfn_CmdWaitEvents = reinterpret_cast<detail::PFN_CmdWaitEvents>(get_device_proc_addr(device,"vkCmdWaitEvents"));
    pfn_CmdPipelineBarrier = reinterpret_cast<detail::PFN_CmdPipelineBarrier>(get_device_proc_addr(device,"vkCmdPipelineBarrier"));
    pfn_CmdBeginQuery = reinterpret_cast<detail::PFN_CmdBeginQuery>(get_device_proc_addr(device,"vkCmdBeginQuery"));
    pfn_CmdEndQuery = reinterpret_cast<detail::PFN_CmdEndQuery>(get_device_proc_addr(device,"vkCmdEndQuery"));
    pfn_CmdResetQueryPool = reinterpret_cast<detail::PFN_CmdResetQueryPool>(get_device_proc_addr(device,"vkCmdResetQueryPool"));
    pfn_CmdWriteTimestamp = reinterpret_cast<detail::PFN_CmdWriteTimestamp>(get_device_proc_addr(device,"vkCmdWriteTimestamp"));
    pfn_CmdCopyQueryPoolResults = reinterpret_cast<detail::PFN_CmdCopyQueryPoolResults>(get_device_proc_addr(device,"vkCmdCopyQueryPoolResults"));
    pfn_CmdPushConstants = reinterpret_cast<detail::PFN_CmdPushConstants>(get_device_proc_addr(device,"vkCmdPushConstants"));
    pfn_CmdBeginRenderPass = reinterpret_cast<detail::PFN_CmdBeginRenderPass>(get_device_proc_addr(device,"vkCmdBeginRenderPass"));
    pfn_CmdNextSubpass = reinterpret_cast<detail::PFN_CmdNextSubpass>(get_device_proc_addr(device,"vkCmdNextSubpass"));
    pfn_CmdEndRenderPass = reinterpret_cast<detail::PFN_CmdEndRenderPass>(get_device_proc_addr(device,"vkCmdEndRenderPass"));
    pfn_CmdExecuteCommands = reinterpret_cast<detail::PFN_CmdExecuteCommands>(get_device_proc_addr(device,"vkCmdExecuteCommands"));
    pfn_BindBufferMemory2 = reinterpret_cast<detail::PFN_BindBufferMemory2>(get_device_proc_addr(device,"vkBindBufferMemory2"));
    pfn_BindImageMemory2 = reinterpret_cast<detail::PFN_BindImageMemory2>(get_device_proc_addr(device,"vkBindImageMemory2"));
    pfn_GetDeviceGroupPeerMemoryFeatures = reinterpret_cast<detail::PFN_GetDeviceGroupPeerMemoryFeatures>(get_device_proc_addr(device,"vkGetDeviceGroupPeerMemoryFeatures"));
    pfn_CmdSetDeviceMask = reinterpret_cast<detail::PFN_CmdSetDeviceMask>(get_device_proc_addr(device,"vkCmdSetDeviceMask"));
    pfn_CmdDispatchBase = reinterpret_cast<detail::PFN_CmdDispatchBase>(get_device_proc_addr(device,"vkCmdDispatchBase"));
    pfn_GetBufferMemoryRequirements2 = reinterpret_cast<detail::PFN_GetBufferMemoryRequirements2>(get_device_proc_addr(device,"vkGetBufferMemoryRequirements2"));
    pfn_GetImageMemoryRequirements2 = reinterpret_cast<detail::PFN_GetImageMemoryRequirements2>(get_device_proc_addr(device,"vkGetImageMemoryRequirements2"));
    pfn_GetImageSparseMemoryRequirements2 = reinterpret_cast<detail::PFN_GetImageSparseMemoryRequirements2>(get_device_proc_addr(device,"vkGetImageSparseMemoryRequirements2"));
    pfn_TrimCommandPool = reinterpret_cast<detail::PFN_TrimCommandPool>(get_device_proc_addr(device,"vkTrimCommandPool"));
    pfn_GetDeviceQueue2 = reinterpret_cast<detail::PFN_GetDeviceQueue2>(get_device_proc_addr(device,"vkGetDeviceQueue2"));
    pfn_CreateSamplerYcbcrConversion = reinterpret_cast<detail::PFN_CreateSamplerYcbcrConversion>(get_device_proc_addr(device,"vkCreateSamplerYcbcrConversion"));
    pfn_DestroySamplerYcbcrConversion = reinterpret_cast<detail::PFN_DestroySamplerYcbcrConversion>(get_device_proc_addr(device,"vkDestroySamplerYcbcrConversion"));
    pfn_CreateDescriptorUpdateTemplate = reinterpret_cast<detail::PFN_CreateDescriptorUpdateTemplate>(get_device_proc_addr(device,"vkCreateDescriptorUpdateTemplate"));
    pfn_DestroyDescriptorUpdateTemplate = reinterpret_cast<detail::PFN_DestroyDescriptorUpdateTemplate>(get_device_proc_addr(device,"vkDestroyDescriptorUpdateTemplate"));
    pfn_UpdateDescriptorSetWithTemplate = reinterpret_cast<detail::PFN_UpdateDescriptorSetWithTemplate>(get_device_proc_addr(device,"vkUpdateDescriptorSetWithTemplate"));
    pfn_GetDescriptorSetLayoutSupport = reinterpret_cast<detail::PFN_GetDescriptorSetLayoutSupport>(get_device_proc_addr(device,"vkGetDescriptorSetLayoutSupport"));
    pfn_CmdDrawIndirectCount = reinterpret_cast<detail::PFN_CmdDrawIndirectCount>(get_device_proc_addr(device,"vkCmdDrawIndirectCount"));
    pfn_CmdDrawIndexedIndirectCount = reinterpret_cast<detail::PFN_CmdDrawIndexedIndirectCount>(get_device_proc_addr(device,"vkCmdDrawIndexedIndirectCount"));
    pfn_CreateRenderPass2 = reinterpret_cast<detail::PFN_CreateRenderPass2>(get_device_proc_addr(device,"vkCreateRenderPass2"));
    pfn_CmdBeginRenderPass2 = reinterpret_cast<detail::PFN_CmdBeginRenderPass2>(get_device_proc_addr(device,"vkCmdBeginRenderPass2"));
    pfn_CmdNextSubpass2 = reinterpret_cast<detail::PFN_CmdNextSubpass2>(get_device_proc_addr(device,"vkCmdNextSubpass2"));
    pfn_CmdEndRenderPass2 = reinterpret_cast<detail::PFN_CmdEndRenderPass2>(get_device_proc_addr(device,"vkCmdEndRenderPass2"));
    pfn_ResetQueryPool = reinterpret_cast<detail::PFN_ResetQueryPool>(get_device_proc_addr(device,"vkResetQueryPool"));
    pfn_GetSemaphoreCounterValue = reinterpret_cast<detail::PFN_GetSemaphoreCounterValue>(get_device_proc_addr(device,"vkGetSemaphoreCounterValue"));
    pfn_WaitSemaphores = reinterpret_cast<detail::PFN_WaitSemaphores>(get_device_proc_addr(device,"vkWaitSemaphores"));
    pfn_SignalSemaphore = reinterpret_cast<detail::PFN_SignalSemaphore>(get_device_proc_addr(device,"vkSignalSemaphore"));
    pfn_GetBufferOpaqueCaptureAddress = reinterpret_cast<detail::PFN_GetBufferOpaqueCaptureAddress>(get_device_proc_addr(device,"vkGetBufferOpaqueCaptureAddress"));
    pfn_GetBufferDeviceAddress = reinterpret_cast<detail::PFN_GetBufferDeviceAddress>(get_device_proc_addr(device,"vkGetBufferDeviceAddress"));
    pfn_GetDeviceMemoryOpaqueCaptureAddress = reinterpret_cast<detail::PFN_GetDeviceMemoryOpaqueCaptureAddress>(get_device_proc_addr(device,"vkGetDeviceMemoryOpaqueCaptureAddress"));
    pfn_CreateSwapchainKHR = reinterpret_cast<detail::PFN_CreateSwapchainKHR>(get_device_proc_addr(device,"vkCreateSwapchainKHR"));
    pfn_DestroySwapchainKHR = reinterpret_cast<detail::PFN_DestroySwapchainKHR>(get_device_proc_addr(device,"vkDestroySwapchainKHR"));
    pfn_GetSwapchainImagesKHR = reinterpret_cast<detail::PFN_GetSwapchainImagesKHR>(get_device_proc_addr(device,"vkGetSwapchainImagesKHR"));
    pfn_AcquireNextImageKHR = reinterpret_cast<detail::PFN_AcquireNextImageKHR>(get_device_proc_addr(device,"vkAcquireNextImageKHR"));
    pfn_QueuePresentKHR = reinterpret_cast<detail::PFN_QueuePresentKHR>(get_device_proc_addr(device,"vkQueuePresentKHR"));
    pfn_GetDeviceGroupPresentCapabilitiesKHR = reinterpret_cast<detail::PFN_GetDeviceGroupPresentCapabilitiesKHR>(get_device_proc_addr(device,"vkGetDeviceGroupPresentCapabilitiesKHR"));
    pfn_GetDeviceGroupSurfacePresentModesKHR = reinterpret_cast<detail::PFN_GetDeviceGroupSurfacePresentModesKHR>(get_device_proc_addr(device,"vkGetDeviceGroupSurfacePresentModesKHR"));
    pfn_AcquireNextImage2KHR = reinterpret_cast<detail::PFN_AcquireNextImage2KHR>(get_device_proc_addr(device,"vkAcquireNextImage2KHR"));
    pfn_CreateSharedSwapchainsKHR = reinterpret_cast<detail::PFN_CreateSharedSwapchainsKHR>(get_device_proc_addr(device,"vkCreateSharedSwapchainsKHR"));
    pfn_DebugMarkerSetObjectNameEXT = reinterpret_cast<detail::PFN_DebugMarkerSetObjectNameEXT>(get_device_proc_addr(device,"vkDebugMarkerSetObjectNameEXT"));
    pfn_DebugMarkerSetObjectTagEXT = reinterpret_cast<detail::PFN_DebugMarkerSetObjectTagEXT>(get_device_proc_addr(device,"vkDebugMarkerSetObjectTagEXT"));
    pfn_CmdDebugMarkerBeginEXT = reinterpret_cast<detail::PFN_CmdDebugMarkerBeginEXT>(get_device_proc_addr(device,"vkCmdDebugMarkerBeginEXT"));
    pfn_CmdDebugMarkerEndEXT = reinterpret_cast<detail::PFN_CmdDebugMarkerEndEXT>(get_device_proc_addr(device,"vkCmdDebugMarkerEndEXT"));
    pfn_CmdDebugMarkerInsertEXT = reinterpret_cast<detail::PFN_CmdDebugMarkerInsertEXT>(get_device_proc_addr(device,"vkCmdDebugMarkerInsertEXT"));
    pfn_CmdBindTransformFeedbackBuffersEXT = reinterpret_cast<detail::PFN_CmdBindTransformFeedbackBuffersEXT>(get_device_proc_addr(device,"vkCmdBindTransformFeedbackBuffersEXT"));
    pfn_CmdBeginTransformFeedbackEXT = reinterpret_cast<detail::PFN_CmdBeginTransformFeedbackEXT>(get_device_proc_addr(device,"vkCmdBeginTransformFeedbackEXT"));
    pfn_CmdEndTransformFeedbackEXT = reinterpret_cast<detail::PFN_CmdEndTransformFeedbackEXT>(get_device_proc_addr(device,"vkCmdEndTransformFeedbackEXT"));
    pfn_CmdBeginQueryIndexedEXT = reinterpret_cast<detail::PFN_CmdBeginQueryIndexedEXT>(get_device_proc_addr(device,"vkCmdBeginQueryIndexedEXT"));
    pfn_CmdEndQueryIndexedEXT = reinterpret_cast<detail::PFN_CmdEndQueryIndexedEXT>(get_device_proc_addr(device,"vkCmdEndQueryIndexedEXT"));
    pfn_CmdDrawIndirectByteCountEXT = reinterpret_cast<detail::PFN_CmdDrawIndirectByteCountEXT>(get_device_proc_addr(device,"vkCmdDrawIndirectByteCountEXT"));
    pfn_GetImageViewHandleNVX = reinterpret_cast<detail::PFN_GetImageViewHandleNVX>(get_device_proc_addr(device,"vkGetImageViewHandleNVX"));
    pfn_GetImageViewAddressNVX = reinterpret_cast<detail::PFN_GetImageViewAddressNVX>(get_device_proc_addr(device,"vkGetImageViewAddressNVX"));
    pfn_GetShaderInfoAMD = reinterpret_cast<detail::PFN_GetShaderInfoAMD>(get_device_proc_addr(device,"vkGetShaderInfoAMD"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetMemoryWin32HandleNV = reinterpret_cast<detail::PFN_GetMemoryWin32HandleNV>(get_device_proc_addr(device,"vkGetMemoryWin32HandleNV"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetMemoryWin32HandleKHR = reinterpret_cast<detail::PFN_GetMemoryWin32HandleKHR>(get_device_proc_addr(device,"vkGetMemoryWin32HandleKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetMemoryWin32HandlePropertiesKHR = reinterpret_cast<detail::PFN_GetMemoryWin32HandlePropertiesKHR>(get_device_proc_addr(device,"vkGetMemoryWin32HandlePropertiesKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_GetMemoryFdKHR = reinterpret_cast<detail::PFN_GetMemoryFdKHR>(get_device_proc_addr(device,"vkGetMemoryFdKHR"));
    pfn_GetMemoryFdPropertiesKHR = reinterpret_cast<detail::PFN_GetMemoryFdPropertiesKHR>(get_device_proc_addr(device,"vkGetMemoryFdPropertiesKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetSemaphoreWin32HandleKHR = reinterpret_cast<detail::PFN_GetSemaphoreWin32HandleKHR>(get_device_proc_addr(device,"vkGetSemaphoreWin32HandleKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_ImportSemaphoreWin32HandleKHR = reinterpret_cast<detail::PFN_ImportSemaphoreWin32HandleKHR>(get_device_proc_addr(device,"vkImportSemaphoreWin32HandleKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_GetSemaphoreFdKHR = reinterpret_cast<detail::PFN_GetSemaphoreFdKHR>(get_device_proc_addr(device,"vkGetSemaphoreFdKHR"));
    pfn_ImportSemaphoreFdKHR = reinterpret_cast<detail::PFN_ImportSemaphoreFdKHR>(get_device_proc_addr(device,"vkImportSemaphoreFdKHR"));
    pfn_CmdPushDescriptorSetKHR = reinterpret_cast<detail::PFN_CmdPushDescriptorSetKHR>(get_device_proc_addr(device,"vkCmdPushDescriptorSetKHR"));
    pfn_CmdPushDescriptorSetWithTemplateKHR = reinterpret_cast<detail::PFN_CmdPushDescriptorSetWithTemplateKHR>(get_device_proc_addr(device,"vkCmdPushDescriptorSetWithTemplateKHR"));
    pfn_CmdBeginConditionalRenderingEXT = reinterpret_cast<detail::PFN_CmdBeginConditionalRenderingEXT>(get_device_proc_addr(device,"vkCmdBeginConditionalRenderingEXT"));
    pfn_CmdEndConditionalRenderingEXT = reinterpret_cast<detail::PFN_CmdEndConditionalRenderingEXT>(get_device_proc_addr(device,"vkCmdEndConditionalRenderingEXT"));
    pfn_CmdSetViewportWScalingNV = reinterpret_cast<detail::PFN_CmdSetViewportWScalingNV>(get_device_proc_addr(device,"vkCmdSetViewportWScalingNV"));
    pfn_DisplayPowerControlEXT = reinterpret_cast<detail::PFN_DisplayPowerControlEXT>(get_device_proc_addr(device,"vkDisplayPowerControlEXT"));
    pfn_RegisterDeviceEventEXT = reinterpret_cast<detail::PFN_RegisterDeviceEventEXT>(get_device_proc_addr(device,"vkRegisterDeviceEventEXT"));
    pfn_RegisterDisplayEventEXT = reinterpret_cast<detail::PFN_RegisterDisplayEventEXT>(get_device_proc_addr(device,"vkRegisterDisplayEventEXT"));
    pfn_GetSwapchainCounterEXT = reinterpret_cast<detail::PFN_GetSwapchainCounterEXT>(get_device_proc_addr(device,"vkGetSwapchainCounterEXT"));
    pfn_GetRefreshCycleDurationGOOGLE = reinterpret_cast<detail::PFN_GetRefreshCycleDurationGOOGLE>(get_device_proc_addr(device,"vkGetRefreshCycleDurationGOOGLE"));
    pfn_GetPastPresentationTimingGOOGLE = reinterpret_cast<detail::PFN_GetPastPresentationTimingGOOGLE>(get_device_proc_addr(device,"vkGetPastPresentationTimingGOOGLE"));
    pfn_CmdSetDiscardRectangleEXT = reinterpret_cast<detail::PFN_CmdSetDiscardRectangleEXT>(get_device_proc_addr(device,"vkCmdSetDiscardRectangleEXT"));
    pfn_SetHdrMetadataEXT = reinterpret_cast<detail::PFN_SetHdrMetadataEXT>(get_device_proc_addr(device,"vkSetHdrMetadataEXT"));
    pfn_GetSwapchainStatusKHR = reinterpret_cast<detail::PFN_GetSwapchainStatusKHR>(get_device_proc_addr(device,"vkGetSwapchainStatusKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetFenceWin32HandleKHR = reinterpret_cast<detail::PFN_GetFenceWin32HandleKHR>(get_device_proc_addr(device,"vkGetFenceWin32HandleKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_ImportFenceWin32HandleKHR = reinterpret_cast<detail::PFN_ImportFenceWin32HandleKHR>(get_device_proc_addr(device,"vkImportFenceWin32HandleKHR"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_GetFenceFdKHR = reinterpret_cast<detail::PFN_GetFenceFdKHR>(get_device_proc_addr(device,"vkGetFenceFdKHR"));
    pfn_ImportFenceFdKHR = reinterpret_cast<detail::PFN_ImportFenceFdKHR>(get_device_proc_addr(device,"vkImportFenceFdKHR"));
    pfn_AcquireProfilingLockKHR = reinterpret_cast<detail::PFN_AcquireProfilingLockKHR>(get_device_proc_addr(device,"vkAcquireProfilingLockKHR"));
    pfn_ReleaseProfilingLockKHR = reinterpret_cast<detail::PFN_ReleaseProfilingLockKHR>(get_device_proc_addr(device,"vkReleaseProfilingLockKHR"));
    pfn_SetDebugUtilsObjectNameEXT = reinterpret_cast<detail::PFN_SetDebugUtilsObjectNameEXT>(get_device_proc_addr(device,"vkSetDebugUtilsObjectNameEXT"));
    pfn_SetDebugUtilsObjectTagEXT = reinterpret_cast<detail::PFN_SetDebugUtilsObjectTagEXT>(get_device_proc_addr(device,"vkSetDebugUtilsObjectTagEXT"));
    pfn_QueueBeginDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_QueueBeginDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkQueueBeginDebugUtilsLabelEXT"));
    pfn_QueueEndDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_QueueEndDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkQueueEndDebugUtilsLabelEXT"));
    pfn_QueueInsertDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_QueueInsertDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkQueueInsertDebugUtilsLabelEXT"));
    pfn_CmdBeginDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_CmdBeginDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkCmdBeginDebugUtilsLabelEXT"));
    pfn_CmdEndDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_CmdEndDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkCmdEndDebugUtilsLabelEXT"));
    pfn_CmdInsertDebugUtilsLabelEXT = reinterpret_cast<detail::PFN_CmdInsertDebugUtilsLabelEXT>(get_device_proc_addr(device,"vkCmdInsertDebugUtilsLabelEXT"));
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_GetAndroidHardwareBufferPropertiesANDROID = reinterpret_cast<detail::PFN_GetAndroidHardwareBufferPropertiesANDROID>(get_device_proc_addr(device,"vkGetAndroidHardwareBufferPropertiesANDROID"));
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    pfn_GetMemoryAndroidHardwareBufferANDROID = reinterpret_cast<detail::PFN_GetMemoryAndroidHardwareBufferANDROID>(get_device_proc_addr(device,"vkGetMemoryAndroidHardwareBufferANDROID"));
#endif // VK_USE_PLATFORM_ANDROID_KHR
    pfn_CmdSetSampleLocationsEXT = reinterpret_cast<detail::PFN_CmdSetSampleLocationsEXT>(get_device_proc_addr(device,"vkCmdSetSampleLocationsEXT"));
    pfn_DestroyAccelerationStructureKHR = reinterpret_cast<detail::PFN_DestroyAccelerationStructureKHR>(get_device_proc_addr(device,"vkDestroyAccelerationStructureKHR"));
    pfn_CmdCopyAccelerationStructureKHR = reinterpret_cast<detail::PFN_CmdCopyAccelerationStructureKHR>(get_device_proc_addr(device,"vkCmdCopyAccelerationStructureKHR"));
    pfn_CopyAccelerationStructureKHR = reinterpret_cast<detail::PFN_CopyAccelerationStructureKHR>(get_device_proc_addr(device,"vkCopyAccelerationStructureKHR"));
    pfn_CmdCopyAccelerationStructureToMemoryKHR = reinterpret_cast<detail::PFN_CmdCopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device,"vkCmdCopyAccelerationStructureToMemoryKHR"));
    pfn_CopyAccelerationStructureToMemoryKHR = reinterpret_cast<detail::PFN_CopyAccelerationStructureToMemoryKHR>(get_device_proc_addr(device,"vkCopyAccelerationStructureToMemoryKHR"));
    pfn_CmdCopyMemoryToAccelerationStructureKHR = reinterpret_cast<detail::PFN_CmdCopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device,"vkCmdCopyMemoryToAccelerationStructureKHR"));
    pfn_CopyMemoryToAccelerationStructureKHR = reinterpret_cast<detail::PFN_CopyMemoryToAccelerationStructureKHR>(get_device_proc_addr(device,"vkCopyMemoryToAccelerationStructureKHR"));
    pfn_CmdWriteAccelerationStructuresPropertiesKHR = reinterpret_cast<detail::PFN_CmdWriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device,"vkCmdWriteAccelerationStructuresPropertiesKHR"));
    pfn_WriteAccelerationStructuresPropertiesKHR = reinterpret_cast<detail::PFN_WriteAccelerationStructuresPropertiesKHR>(get_device_proc_addr(device,"vkWriteAccelerationStructuresPropertiesKHR"));
    pfn_GetDeviceAccelerationStructureCompatibilityKHR = reinterpret_cast<detail::PFN_GetDeviceAccelerationStructureCompatibilityKHR>(get_device_proc_addr(device,"vkGetDeviceAccelerationStructureCompatibilityKHR"));
    pfn_CreateAccelerationStructureKHR = reinterpret_cast<detail::PFN_CreateAccelerationStructureKHR>(get_device_proc_addr(device,"vkCreateAccelerationStructureKHR"));
    pfn_CmdBuildAccelerationStructuresKHR = reinterpret_cast<detail::PFN_CmdBuildAccelerationStructuresKHR>(get_device_proc_addr(device,"vkCmdBuildAccelerationStructuresKHR"));
    pfn_CmdBuildAccelerationStructuresIndirectKHR = reinterpret_cast<detail::PFN_CmdBuildAccelerationStructuresIndirectKHR>(get_device_proc_addr(device,"vkCmdBuildAccelerationStructuresIndirectKHR"));
    pfn_BuildAccelerationStructuresKHR = reinterpret_cast<detail::PFN_BuildAccelerationStructuresKHR>(get_device_proc_addr(device,"vkBuildAccelerationStructuresKHR"));
    pfn_GetAccelerationStructureDeviceAddressKHR = reinterpret_cast<detail::PFN_GetAccelerationStructureDeviceAddressKHR>(get_device_proc_addr(device,"vkGetAccelerationStructureDeviceAddressKHR"));
    pfn_GetAccelerationStructureBuildSizesKHR = reinterpret_cast<detail::PFN_GetAccelerationStructureBuildSizesKHR>(get_device_proc_addr(device,"vkGetAccelerationStructureBuildSizesKHR"));
    pfn_CmdTraceRaysKHR = reinterpret_cast<detail::PFN_CmdTraceRaysKHR>(get_device_proc_addr(device,"vkCmdTraceRaysKHR"));
    pfn_GetRayTracingShaderGroupHandlesKHR = reinterpret_cast<detail::PFN_GetRayTracingShaderGroupHandlesKHR>(get_device_proc_addr(device,"vkGetRayTracingShaderGroupHandlesKHR"));
    pfn_GetRayTracingCaptureReplayShaderGroupHandlesKHR = reinterpret_cast<detail::PFN_GetRayTracingCaptureReplayShaderGroupHandlesKHR>(get_device_proc_addr(device,"vkGetRayTracingCaptureReplayShaderGroupHandlesKHR"));
    pfn_CreateRayTracingPipelinesKHR = reinterpret_cast<detail::PFN_CreateRayTracingPipelinesKHR>(get_device_proc_addr(device,"vkCreateRayTracingPipelinesKHR"));
    pfn_CmdTraceRaysIndirectKHR = reinterpret_cast<detail::PFN_CmdTraceRaysIndirectKHR>(get_device_proc_addr(device,"vkCmdTraceRaysIndirectKHR"));
    pfn_GetRayTracingShaderGroupStackSizeKHR = reinterpret_cast<detail::PFN_GetRayTracingShaderGroupStackSizeKHR>(get_device_proc_addr(device,"vkGetRayTracingShaderGroupStackSizeKHR"));
    pfn_CmdSetRayTracingPipelineStackSizeKHR = reinterpret_cast<detail::PFN_CmdSetRayTracingPipelineStackSizeKHR>(get_device_proc_addr(device,"vkCmdSetRayTracingPipelineStackSizeKHR"));
    pfn_GetImageDrmFormatModifierPropertiesEXT = reinterpret_cast<detail::PFN_GetImageDrmFormatModifierPropertiesEXT>(get_device_proc_addr(device,"vkGetImageDrmFormatModifierPropertiesEXT"));
    pfn_CreateValidationCacheEXT = reinterpret_cast<detail::PFN_CreateValidationCacheEXT>(get_device_proc_addr(device,"vkCreateValidationCacheEXT"));
    pfn_DestroyValidationCacheEXT = reinterpret_cast<detail::PFN_DestroyValidationCacheEXT>(get_device_proc_addr(device,"vkDestroyValidationCacheEXT"));
    pfn_GetValidationCacheDataEXT = reinterpret_cast<detail::PFN_GetValidationCacheDataEXT>(get_device_proc_addr(device,"vkGetValidationCacheDataEXT"));
    pfn_MergeValidationCachesEXT = reinterpret_cast<detail::PFN_MergeValidationCachesEXT>(get_device_proc_addr(device,"vkMergeValidationCachesEXT"));
    pfn_CmdBindShadingRateImageNV = reinterpret_cast<detail::PFN_CmdBindShadingRateImageNV>(get_device_proc_addr(device,"vkCmdBindShadingRateImageNV"));
    pfn_CmdSetViewportShadingRatePaletteNV = reinterpret_cast<detail::PFN_CmdSetViewportShadingRatePaletteNV>(get_device_proc_addr(device,"vkCmdSetViewportShadingRatePaletteNV"));
    pfn_CmdSetCoarseSampleOrderNV = reinterpret_cast<detail::PFN_CmdSetCoarseSampleOrderNV>(get_device_proc_addr(device,"vkCmdSetCoarseSampleOrderNV"));
    pfn_CompileDeferredNV = reinterpret_cast<detail::PFN_CompileDeferredNV>(get_device_proc_addr(device,"vkCompileDeferredNV"));
    pfn_CreateAccelerationStructureNV = reinterpret_cast<detail::PFN_CreateAccelerationStructureNV>(get_device_proc_addr(device,"vkCreateAccelerationStructureNV"));
    pfn_DestroyAccelerationStructureNV = reinterpret_cast<detail::PFN_DestroyAccelerationStructureNV>(get_device_proc_addr(device,"vkDestroyAccelerationStructureNV"));
    pfn_GetAccelerationStructureMemoryRequirementsNV = reinterpret_cast<detail::PFN_GetAccelerationStructureMemoryRequirementsNV>(get_device_proc_addr(device,"vkGetAccelerationStructureMemoryRequirementsNV"));
    pfn_BindAccelerationStructureMemoryNV = reinterpret_cast<detail::PFN_BindAccelerationStructureMemoryNV>(get_device_proc_addr(device,"vkBindAccelerationStructureMemoryNV"));
    pfn_CmdCopyAccelerationStructureNV = reinterpret_cast<detail::PFN_CmdCopyAccelerationStructureNV>(get_device_proc_addr(device,"vkCmdCopyAccelerationStructureNV"));
    pfn_CmdWriteAccelerationStructuresPropertiesNV = reinterpret_cast<detail::PFN_CmdWriteAccelerationStructuresPropertiesNV>(get_device_proc_addr(device,"vkCmdWriteAccelerationStructuresPropertiesNV"));
    pfn_CmdBuildAccelerationStructureNV = reinterpret_cast<detail::PFN_CmdBuildAccelerationStructureNV>(get_device_proc_addr(device,"vkCmdBuildAccelerationStructureNV"));
    pfn_CmdTraceRaysNV = reinterpret_cast<detail::PFN_CmdTraceRaysNV>(get_device_proc_addr(device,"vkCmdTraceRaysNV"));
    pfn_GetAccelerationStructureHandleNV = reinterpret_cast<detail::PFN_GetAccelerationStructureHandleNV>(get_device_proc_addr(device,"vkGetAccelerationStructureHandleNV"));
    pfn_CreateRayTracingPipelinesNV = reinterpret_cast<detail::PFN_CreateRayTracingPipelinesNV>(get_device_proc_addr(device,"vkCreateRayTracingPipelinesNV"));
    pfn_GetMemoryHostPointerPropertiesEXT = reinterpret_cast<detail::PFN_GetMemoryHostPointerPropertiesEXT>(get_device_proc_addr(device,"vkGetMemoryHostPointerPropertiesEXT"));
    pfn_CmdWriteBufferMarkerAMD = reinterpret_cast<detail::PFN_CmdWriteBufferMarkerAMD>(get_device_proc_addr(device,"vkCmdWriteBufferMarkerAMD"));
    pfn_GetCalibratedTimestampsEXT = reinterpret_cast<detail::PFN_GetCalibratedTimestampsEXT>(get_device_proc_addr(device,"vkGetCalibratedTimestampsEXT"));
    pfn_CmdDrawMeshTasksNV = reinterpret_cast<detail::PFN_CmdDrawMeshTasksNV>(get_device_proc_addr(device,"vkCmdDrawMeshTasksNV"));
    pfn_CmdDrawMeshTasksIndirectNV = reinterpret_cast<detail::PFN_CmdDrawMeshTasksIndirectNV>(get_device_proc_addr(device,"vkCmdDrawMeshTasksIndirectNV"));
    pfn_CmdDrawMeshTasksIndirectCountNV = reinterpret_cast<detail::PFN_CmdDrawMeshTasksIndirectCountNV>(get_device_proc_addr(device,"vkCmdDrawMeshTasksIndirectCountNV"));
    pfn_CmdSetExclusiveScissorNV = reinterpret_cast<detail::PFN_CmdSetExclusiveScissorNV>(get_device_proc_addr(device,"vkCmdSetExclusiveScissorNV"));
    pfn_CmdSetCheckpointNV = reinterpret_cast<detail::PFN_CmdSetCheckpointNV>(get_device_proc_addr(device,"vkCmdSetCheckpointNV"));
    pfn_GetQueueCheckpointDataNV = reinterpret_cast<detail::PFN_GetQueueCheckpointDataNV>(get_device_proc_addr(device,"vkGetQueueCheckpointDataNV"));
    pfn_InitializePerformanceApiINTEL = reinterpret_cast<detail::PFN_InitializePerformanceApiINTEL>(get_device_proc_addr(device,"vkInitializePerformanceApiINTEL"));
    pfn_UninitializePerformanceApiINTEL = reinterpret_cast<detail::PFN_UninitializePerformanceApiINTEL>(get_device_proc_addr(device,"vkUninitializePerformanceApiINTEL"));
    pfn_CmdSetPerformanceMarkerINTEL = reinterpret_cast<detail::PFN_CmdSetPerformanceMarkerINTEL>(get_device_proc_addr(device,"vkCmdSetPerformanceMarkerINTEL"));
    pfn_CmdSetPerformanceStreamMarkerINTEL = reinterpret_cast<detail::PFN_CmdSetPerformanceStreamMarkerINTEL>(get_device_proc_addr(device,"vkCmdSetPerformanceStreamMarkerINTEL"));
    pfn_CmdSetPerformanceOverrideINTEL = reinterpret_cast<detail::PFN_CmdSetPerformanceOverrideINTEL>(get_device_proc_addr(device,"vkCmdSetPerformanceOverrideINTEL"));
    pfn_AcquirePerformanceConfigurationINTEL = reinterpret_cast<detail::PFN_AcquirePerformanceConfigurationINTEL>(get_device_proc_addr(device,"vkAcquirePerformanceConfigurationINTEL"));
    pfn_ReleasePerformanceConfigurationINTEL = reinterpret_cast<detail::PFN_ReleasePerformanceConfigurationINTEL>(get_device_proc_addr(device,"vkReleasePerformanceConfigurationINTEL"));
    pfn_QueueSetPerformanceConfigurationINTEL = reinterpret_cast<detail::PFN_QueueSetPerformanceConfigurationINTEL>(get_device_proc_addr(device,"vkQueueSetPerformanceConfigurationINTEL"));
    pfn_GetPerformanceParameterINTEL = reinterpret_cast<detail::PFN_GetPerformanceParameterINTEL>(get_device_proc_addr(device,"vkGetPerformanceParameterINTEL"));
    pfn_SetLocalDimmingAMD = reinterpret_cast<detail::PFN_SetLocalDimmingAMD>(get_device_proc_addr(device,"vkSetLocalDimmingAMD"));
    pfn_CmdSetFragmentShadingRateKHR = reinterpret_cast<detail::PFN_CmdSetFragmentShadingRateKHR>(get_device_proc_addr(device,"vkCmdSetFragmentShadingRateKHR"));
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_AcquireFullScreenExclusiveModeEXT = reinterpret_cast<detail::PFN_AcquireFullScreenExclusiveModeEXT>(get_device_proc_addr(device,"vkAcquireFullScreenExclusiveModeEXT"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_ReleaseFullScreenExclusiveModeEXT = reinterpret_cast<detail::PFN_ReleaseFullScreenExclusiveModeEXT>(get_device_proc_addr(device,"vkReleaseFullScreenExclusiveModeEXT"));
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    pfn_GetDeviceGroupSurfacePresentModes2EXT = reinterpret_cast<detail::PFN_GetDeviceGroupSurfacePresentModes2EXT>(get_device_proc_addr(device,"vkGetDeviceGroupSurfacePresentModes2EXT"));
#endif // VK_USE_PLATFORM_WIN32_KHR
    pfn_CmdSetLineStippleEXT = reinterpret_cast<detail::PFN_CmdSetLineStippleEXT>(get_device_proc_addr(device,"vkCmdSetLineStippleEXT"));
    pfn_CmdSetCullModeEXT = reinterpret_cast<detail::PFN_CmdSetCullModeEXT>(get_device_proc_addr(device,"vkCmdSetCullModeEXT"));
    pfn_CmdSetFrontFaceEXT = reinterpret_cast<detail::PFN_CmdSetFrontFaceEXT>(get_device_proc_addr(device,"vkCmdSetFrontFaceEXT"));
    pfn_CmdSetPrimitiveTopologyEXT = reinterpret_cast<detail::PFN_CmdSetPrimitiveTopologyEXT>(get_device_proc_addr(device,"vkCmdSetPrimitiveTopologyEXT"));
    pfn_CmdSetViewportWithCountEXT = reinterpret_cast<detail::PFN_CmdSetViewportWithCountEXT>(get_device_proc_addr(device,"vkCmdSetViewportWithCountEXT"));
    pfn_CmdSetScissorWithCountEXT = reinterpret_cast<detail::PFN_CmdSetScissorWithCountEXT>(get_device_proc_addr(device,"vkCmdSetScissorWithCountEXT"));
    pfn_CmdBindVertexBuffers2EXT = reinterpret_cast<detail::PFN_CmdBindVertexBuffers2EXT>(get_device_proc_addr(device,"vkCmdBindVertexBuffers2EXT"));
    pfn_CmdSetDepthTestEnableEXT = reinterpret_cast<detail::PFN_CmdSetDepthTestEnableEXT>(get_device_proc_addr(device,"vkCmdSetDepthTestEnableEXT"));
    pfn_CmdSetDepthWriteEnableEXT = reinterpret_cast<detail::PFN_CmdSetDepthWriteEnableEXT>(get_device_proc_addr(device,"vkCmdSetDepthWriteEnableEXT"));
    pfn_CmdSetDepthCompareOpEXT = reinterpret_cast<detail::PFN_CmdSetDepthCompareOpEXT>(get_device_proc_addr(device,"vkCmdSetDepthCompareOpEXT"));
    pfn_CmdSetDepthBoundsTestEnableEXT = reinterpret_cast<detail::PFN_CmdSetDepthBoundsTestEnableEXT>(get_device_proc_addr(device,"vkCmdSetDepthBoundsTestEnableEXT"));
    pfn_CmdSetStencilTestEnableEXT = reinterpret_cast<detail::PFN_CmdSetStencilTestEnableEXT>(get_device_proc_addr(device,"vkCmdSetStencilTestEnableEXT"));
    pfn_CmdSetStencilOpEXT = reinterpret_cast<detail::PFN_CmdSetStencilOpEXT>(get_device_proc_addr(device,"vkCmdSetStencilOpEXT"));
    pfn_CreateDeferredOperationKHR = reinterpret_cast<detail::PFN_CreateDeferredOperationKHR>(get_device_proc_addr(device,"vkCreateDeferredOperationKHR"));
    pfn_DestroyDeferredOperationKHR = reinterpret_cast<detail::PFN_DestroyDeferredOperationKHR>(get_device_proc_addr(device,"vkDestroyDeferredOperationKHR"));
    pfn_GetDeferredOperationMaxConcurrencyKHR = reinterpret_cast<detail::PFN_GetDeferredOperationMaxConcurrencyKHR>(get_device_proc_addr(device,"vkGetDeferredOperationMaxConcurrencyKHR"));
    pfn_GetDeferredOperationResultKHR = reinterpret_cast<detail::PFN_GetDeferredOperationResultKHR>(get_device_proc_addr(device,"vkGetDeferredOperationResultKHR"));
    pfn_DeferredOperationJoinKHR = reinterpret_cast<detail::PFN_DeferredOperationJoinKHR>(get_device_proc_addr(device,"vkDeferredOperationJoinKHR"));
    pfn_GetPipelineExecutablePropertiesKHR = reinterpret_cast<detail::PFN_GetPipelineExecutablePropertiesKHR>(get_device_proc_addr(device,"vkGetPipelineExecutablePropertiesKHR"));
    pfn_GetPipelineExecutableStatisticsKHR = reinterpret_cast<detail::PFN_GetPipelineExecutableStatisticsKHR>(get_device_proc_addr(device,"vkGetPipelineExecutableStatisticsKHR"));
    pfn_GetPipelineExecutableInternalRepresentationsKHR = reinterpret_cast<detail::PFN_GetPipelineExecutableInternalRepresentationsKHR>(get_device_proc_addr(device,"vkGetPipelineExecutableInternalRepresentationsKHR"));
    pfn_CmdExecuteGeneratedCommandsNV = reinterpret_cast<detail::PFN_CmdExecuteGeneratedCommandsNV>(get_device_proc_addr(device,"vkCmdExecuteGeneratedCommandsNV"));
    pfn_CmdPreprocessGeneratedCommandsNV = reinterpret_cast<detail::PFN_CmdPreprocessGeneratedCommandsNV>(get_device_proc_addr(device,"vkCmdPreprocessGeneratedCommandsNV"));
    pfn_CmdBindPipelineShaderGroupNV = reinterpret_cast<detail::PFN_CmdBindPipelineShaderGroupNV>(get_device_proc_addr(device,"vkCmdBindPipelineShaderGroupNV"));
    pfn_GetGeneratedCommandsMemoryRequirementsNV = reinterpret_cast<detail::PFN_GetGeneratedCommandsMemoryRequirementsNV>(get_device_proc_addr(device,"vkGetGeneratedCommandsMemoryRequirementsNV"));
    pfn_CreateIndirectCommandsLayoutNV = reinterpret_cast<detail::PFN_CreateIndirectCommandsLayoutNV>(get_device_proc_addr(device,"vkCreateIndirectCommandsLayoutNV"));
    pfn_DestroyIndirectCommandsLayoutNV = reinterpret_cast<detail::PFN_DestroyIndirectCommandsLayoutNV>(get_device_proc_addr(device,"vkDestroyIndirectCommandsLayoutNV"));
    pfn_CreatePrivateDataSlotEXT = reinterpret_cast<detail::PFN_CreatePrivateDataSlotEXT>(get_device_proc_addr(device,"vkCreatePrivateDataSlotEXT"));
    pfn_DestroyPrivateDataSlotEXT = reinterpret_cast<detail::PFN_DestroyPrivateDataSlotEXT>(get_device_proc_addr(device,"vkDestroyPrivateDataSlotEXT"));
    pfn_SetPrivateDataEXT = reinterpret_cast<detail::PFN_SetPrivateDataEXT>(get_device_proc_addr(device,"vkSetPrivateDataEXT"));
    pfn_GetPrivateDataEXT = reinterpret_cast<detail::PFN_GetPrivateDataEXT>(get_device_proc_addr(device,"vkGetPrivateDataEXT"));
    pfn_CmdSetFragmentShadingRateEnumNV = reinterpret_cast<detail::PFN_CmdSetFragmentShadingRateEnumNV>(get_device_proc_addr(device,"vkCmdSetFragmentShadingRateEnumNV"));
    pfn_CmdCopyBuffer2KHR = reinterpret_cast<detail::PFN_CmdCopyBuffer2KHR>(get_device_proc_addr(device,"vkCmdCopyBuffer2KHR"));
    pfn_CmdCopyImage2KHR = reinterpret_cast<detail::PFN_CmdCopyImage2KHR>(get_device_proc_addr(device,"vkCmdCopyImage2KHR"));
    pfn_CmdBlitImage2KHR = reinterpret_cast<detail::PFN_CmdBlitImage2KHR>(get_device_proc_addr(device,"vkCmdBlitImage2KHR"));
    pfn_CmdCopyBufferToImage2KHR = reinterpret_cast<detail::PFN_CmdCopyBufferToImage2KHR>(get_device_proc_addr(device,"vkCmdCopyBufferToImage2KHR"));
    pfn_CmdCopyImageToBuffer2KHR = reinterpret_cast<detail::PFN_CmdCopyImageToBuffer2KHR>(get_device_proc_addr(device,"vkCmdCopyImageToBuffer2KHR"));
    pfn_CmdResolveImage2KHR = reinterpret_cast<detail::PFN_CmdResolveImage2KHR>(get_device_proc_addr(device,"vkCmdResolveImage2KHR"));
}
};
struct PhysicalDeviceFunctions {
    InstanceFunctions const* instance_functions;
    PhysicalDevice physicaldevice;
    PhysicalDeviceFunctions() noexcept {}
    PhysicalDeviceFunctions(InstanceFunctions const& instance_functions, PhysicalDevice const physicaldevice) noexcept:
    instance_functions{&instance_functions}, physicaldevice{physicaldevice} {}
[[nodiscard]] PhysicalDeviceProperties GetProperties() const {
    return instance_functions->GetPhysicalDeviceProperties(physicaldevice); }
[[nodiscard]] detail::fixed_vector<QueueFamilyProperties> GetQueueFamilyProperties() const {
    return instance_functions->GetPhysicalDeviceQueueFamilyProperties(physicaldevice); }
[[nodiscard]] PhysicalDeviceMemoryProperties GetMemoryProperties() const {
    return instance_functions->GetPhysicalDeviceMemoryProperties(physicaldevice); }
[[nodiscard]] PhysicalDeviceFeatures GetFeatures() const {
    return instance_functions->GetPhysicalDeviceFeatures(physicaldevice); }
[[nodiscard]] FormatProperties GetFormatProperties(Format format) const {
    return instance_functions->GetPhysicalDeviceFormatProperties(physicaldevice, format); }
[[nodiscard]] expected<ImageFormatProperties> GetImageFormatProperties(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags = {}) const {
    return instance_functions->GetPhysicalDeviceImageFormatProperties(physicaldevice, format, type, tiling, usage, flags); }
[[nodiscard]] expected<Device> CreateDevice(const DeviceCreateInfo&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const {
    return instance_functions->CreateDevice(physicaldevice, pCreateInfo, pAllocator); }
[[nodiscard]] expected<detail::fixed_vector<ExtensionProperties>> EnumerateDeviceExtensionProperties(const char* pLayerName = nullptr) const {
    return instance_functions->EnumerateDeviceExtensionProperties(physicaldevice, pLayerName); }
[[nodiscard]] detail::fixed_vector<SparseImageFormatProperties> GetSparseImageFormatProperties(Format format, ImageType type, SampleCountFlagBits samples, ImageUsageFlags usage, ImageTiling tiling) const {
    return instance_functions->GetPhysicalDeviceSparseImageFormatProperties(physicaldevice, format, type, samples, usage, tiling); }
[[nodiscard]] expected<detail::fixed_vector<DisplayPropertiesKHR>> GetDisplayPropertiesKHR() const {
    return instance_functions->GetPhysicalDeviceDisplayPropertiesKHR(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<DisplayPlanePropertiesKHR>> GetDisplayPlanePropertiesKHR() const {
    return instance_functions->GetPhysicalDeviceDisplayPlanePropertiesKHR(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<DisplayKHR>> GetDisplayPlaneSupportedDisplaysKHR(uint32_t planeIndex) const {
    return instance_functions->GetDisplayPlaneSupportedDisplaysKHR(physicaldevice, planeIndex); }
[[nodiscard]] expected<detail::fixed_vector<DisplayModePropertiesKHR>> GetDisplayModePropertiesKHR(DisplayKHR display) const {
    return instance_functions->GetDisplayModePropertiesKHR(physicaldevice, display); }
[[nodiscard]] expected<DisplayModeKHR> CreateDisplayModeKHR(DisplayKHR display, const DisplayModeCreateInfoKHR&  pCreateInfo, const AllocationCallbacks* pAllocator = nullptr) const {
    return instance_functions->CreateDisplayModeKHR(physicaldevice, display, pCreateInfo, pAllocator); }
[[nodiscard]] expected<DisplayPlaneCapabilitiesKHR> GetDisplayPlaneCapabilitiesKHR(DisplayModeKHR mode, uint32_t planeIndex) const {
    return instance_functions->GetDisplayPlaneCapabilitiesKHR(physicaldevice, mode, planeIndex); }
[[nodiscard]] expected<Bool32> GetSurfaceSupportKHR(uint32_t queueFamilyIndex, SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDeviceSurfaceSupportKHR(physicaldevice, queueFamilyIndex, surface); }
[[nodiscard]] expected<SurfaceCapabilitiesKHR> GetSurfaceCapabilitiesKHR(SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDeviceSurfaceCapabilitiesKHR(physicaldevice, surface); }
[[nodiscard]] expected<detail::fixed_vector<SurfaceFormatKHR>> GetSurfaceFormatsKHR(SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDeviceSurfaceFormatsKHR(physicaldevice, surface); }
[[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModesKHR(SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDeviceSurfacePresentModesKHR(physicaldevice, surface); }
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
[[nodiscard]] expected<wl_display> GetWaylandPresentationSupportKHR(uint32_t queueFamilyIndex) const {
    return instance_functions->GetPhysicalDeviceWaylandPresentationSupportKHR(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Bool32 GetWin32PresentationSupportKHR(uint32_t queueFamilyIndex) const {
    return instance_functions->GetPhysicalDeviceWin32PresentationSupportKHR(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
[[nodiscard]] Bool32 GetXlibPresentationSupportKHR(uint32_t queueFamilyIndex, Display&  dpy, VisualID visualID) const {
    return instance_functions->GetPhysicalDeviceXlibPresentationSupportKHR(physicaldevice, queueFamilyIndex, dpy, visualID); }
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
[[nodiscard]] Bool32 GetXcbPresentationSupportKHR(uint32_t queueFamilyIndex, xcb_connection_t&  connection, xcb_visualid_t visual_id) const {
    return instance_functions->GetPhysicalDeviceXcbPresentationSupportKHR(physicaldevice, queueFamilyIndex, connection, visual_id); }
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
[[nodiscard]] expected<IDirectFB> GetDirectFBPresentationSupportEXT(uint32_t queueFamilyIndex) const {
    return instance_functions->GetPhysicalDeviceDirectFBPresentationSupportEXT(physicaldevice, queueFamilyIndex); }
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
[[nodiscard]] expected<ExternalImageFormatPropertiesNV> GetExternalImageFormatPropertiesNV(Format format, ImageType type, ImageTiling tiling, ImageUsageFlags usage, ImageCreateFlags flags = {}, ExternalMemoryHandleTypeFlagsNV externalHandleType = {}) const {
    return instance_functions->GetPhysicalDeviceExternalImageFormatPropertiesNV(physicaldevice, format, type, tiling, usage, flags, externalHandleType); }
[[nodiscard]] PhysicalDeviceFeatures2 GetFeatures2() const {
    return instance_functions->GetPhysicalDeviceFeatures2(physicaldevice); }
[[nodiscard]] PhysicalDeviceProperties2 GetProperties2() const {
    return instance_functions->GetPhysicalDeviceProperties2(physicaldevice); }
[[nodiscard]] FormatProperties2 GetFormatProperties2(Format format) const {
    return instance_functions->GetPhysicalDeviceFormatProperties2(physicaldevice, format); }
[[nodiscard]] expected<ImageFormatProperties2> GetImageFormatProperties2(const PhysicalDeviceImageFormatInfo2&  pImageFormatInfo) const {
    return instance_functions->GetPhysicalDeviceImageFormatProperties2(physicaldevice, pImageFormatInfo); }
[[nodiscard]] detail::fixed_vector<QueueFamilyProperties2> GetQueueFamilyProperties2() const {
    return instance_functions->GetPhysicalDeviceQueueFamilyProperties2(physicaldevice); }
[[nodiscard]] PhysicalDeviceMemoryProperties2 GetMemoryProperties2() const {
    return instance_functions->GetPhysicalDeviceMemoryProperties2(physicaldevice); }
[[nodiscard]] detail::fixed_vector<SparseImageFormatProperties2> GetSparseImageFormatProperties2(const PhysicalDeviceSparseImageFormatInfo2&  pFormatInfo) const {
    return instance_functions->GetPhysicalDeviceSparseImageFormatProperties2(physicaldevice, pFormatInfo); }
[[nodiscard]] ExternalBufferProperties GetExternalBufferProperties(const PhysicalDeviceExternalBufferInfo&  pExternalBufferInfo) const {
    return instance_functions->GetPhysicalDeviceExternalBufferProperties(physicaldevice, pExternalBufferInfo); }
[[nodiscard]] ExternalSemaphoreProperties GetExternalSemaphoreProperties(const PhysicalDeviceExternalSemaphoreInfo&  pExternalSemaphoreInfo) const {
    return instance_functions->GetPhysicalDeviceExternalSemaphoreProperties(physicaldevice, pExternalSemaphoreInfo); }
[[nodiscard]] ExternalFenceProperties GetExternalFenceProperties(const PhysicalDeviceExternalFenceInfo&  pExternalFenceInfo) const {
    return instance_functions->GetPhysicalDeviceExternalFenceProperties(physicaldevice, pExternalFenceInfo); }
[[nodiscard]] Result ReleaseDisplayEXT(DisplayKHR display) const {
    return instance_functions->ReleaseDisplayEXT(physicaldevice, display); }
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
[[nodiscard]] Result AcquireXlibDisplayEXT(Display&  dpy, DisplayKHR display) const {
    return instance_functions->AcquireXlibDisplayEXT(physicaldevice, dpy, display); }
[[nodiscard]] expected<DisplayKHR> GetRandROutputDisplayEXT(Display&  dpy, RROutput rrOutput) const {
    return instance_functions->GetRandROutputDisplayEXT(physicaldevice, dpy, rrOutput); }
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
[[nodiscard]] expected<SurfaceCapabilities2EXT> GetSurfaceCapabilities2EXT(SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDeviceSurfaceCapabilities2EXT(physicaldevice, surface); }
[[nodiscard]] expected<detail::fixed_vector<Rect2D>> GetPresentRectanglesKHR(SurfaceKHR surface) const {
    return instance_functions->GetPhysicalDevicePresentRectanglesKHR(physicaldevice, surface); }
[[nodiscard]] MultisamplePropertiesEXT GetMultisamplePropertiesEXT(SampleCountFlagBits samples) const {
    return instance_functions->GetPhysicalDeviceMultisamplePropertiesEXT(physicaldevice, samples); }
[[nodiscard]] expected<SurfaceCapabilities2KHR> GetSurfaceCapabilities2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    return instance_functions->GetPhysicalDeviceSurfaceCapabilities2KHR(physicaldevice, pSurfaceInfo); }
[[nodiscard]] expected<detail::fixed_vector<SurfaceFormat2KHR>> GetSurfaceFormats2KHR(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    return instance_functions->GetPhysicalDeviceSurfaceFormats2KHR(physicaldevice, pSurfaceInfo); }
[[nodiscard]] expected<detail::fixed_vector<DisplayProperties2KHR>> GetDisplayProperties2KHR() const {
    return instance_functions->GetPhysicalDeviceDisplayProperties2KHR(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<DisplayPlaneProperties2KHR>> GetDisplayPlaneProperties2KHR() const {
    return instance_functions->GetPhysicalDeviceDisplayPlaneProperties2KHR(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<DisplayModeProperties2KHR>> GetDisplayModeProperties2KHR(DisplayKHR display) const {
    return instance_functions->GetDisplayModeProperties2KHR(physicaldevice, display); }
[[nodiscard]] expected<DisplayPlaneCapabilities2KHR> GetDisplayPlaneCapabilities2KHR(const DisplayPlaneInfo2KHR&  pDisplayPlaneInfo) const {
    return instance_functions->GetDisplayPlaneCapabilities2KHR(physicaldevice, pDisplayPlaneInfo); }
[[nodiscard]] expected<detail::fixed_vector<TimeDomainEXT>> GetCalibrateableTimeDomainsEXT() const {
    return instance_functions->GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<CooperativeMatrixPropertiesNV>> GetCooperativeMatrixPropertiesNV() const {
    return instance_functions->GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicaldevice); }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] expected<detail::fixed_vector<PresentModeKHR>> GetSurfacePresentModes2EXT(const PhysicalDeviceSurfaceInfo2KHR&  pSurfaceInfo) const {
    return instance_functions->GetPhysicalDeviceSurfacePresentModes2EXT(physicaldevice, pSurfaceInfo); }
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
[[nodiscard]] Result EnumerateQueueFamilyPerformanceQueryCountersKHR(uint32_t queueFamilyIndex, uint32_t&  pCounterCount, PerformanceCounterKHR* pCounters = nullptr, PerformanceCounterDescriptionKHR* pCounterDescriptions = nullptr) const {
    return instance_functions->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicaldevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions); }
[[nodiscard]] uint32_t GetQueueFamilyPerformanceQueryPassesKHR(const QueryPoolPerformanceCreateInfoKHR&  pPerformanceQueryCreateInfo) const {
    return instance_functions->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicaldevice, pPerformanceQueryCreateInfo); }
[[nodiscard]] expected<detail::fixed_vector<FramebufferMixedSamplesCombinationNV>> GetSupportedFramebufferMixedSamplesCombinationsNV() const {
    return instance_functions->GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceToolPropertiesEXT>> GetToolPropertiesEXT() const {
    return instance_functions->GetPhysicalDeviceToolPropertiesEXT(physicaldevice); }
[[nodiscard]] expected<detail::fixed_vector<PhysicalDeviceFragmentShadingRateKHR>> GetFragmentShadingRatesKHR() const {
    return instance_functions->GetPhysicalDeviceFragmentShadingRatesKHR(physicaldevice); }
};
struct QueueFunctions {
    DeviceFunctions const* device_functions;
    Queue queue;
    QueueFunctions() noexcept {}
    QueueFunctions(DeviceFunctions const& device_functions, Queue const queue) noexcept:
    device_functions{&device_functions}, queue{queue} {}
[[nodiscard]] Result Submit(detail::span<const SubmitInfo> Submits, Fence fence = {}) const {
    return device_functions->QueueSubmit(queue, Submits, fence); }
[[nodiscard]] Result WaitIdle() const {
    return device_functions->QueueWaitIdle(queue); }
[[nodiscard]] Result BindSparse(detail::span<const BindSparseInfo> BindInfo, Fence fence = {}) const {
    return device_functions->QueueBindSparse(queue, BindInfo, fence); }
[[nodiscard]] Result PresentKHR(const PresentInfoKHR&  pPresentInfo) const {
    return device_functions->QueuePresentKHR(queue, pPresentInfo); }
void BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
    device_functions->QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo); }
void EndDebugUtilsLabelEXT() const {
    device_functions->QueueEndDebugUtilsLabelEXT(queue); }
void InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
    device_functions->QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo); }
[[nodiscard]] detail::fixed_vector<CheckpointDataNV> GetCheckpointDataNV() const {
    return device_functions->GetQueueCheckpointDataNV(queue); }
[[nodiscard]] Result SetPerformanceConfigurationINTEL(PerformanceConfigurationINTEL configuration) const {
    return device_functions->QueueSetPerformanceConfigurationINTEL(queue, configuration); }
};
struct CommandBufferFunctions {
    DeviceFunctions const* device_functions;
    CommandBuffer commandbuffer;
    CommandBufferFunctions() noexcept {}
    CommandBufferFunctions(DeviceFunctions const& device_functions, CommandBuffer const commandbuffer) noexcept:
    device_functions{&device_functions}, commandbuffer{commandbuffer} {}
[[nodiscard]] Result Begin(const CommandBufferBeginInfo&  pBeginInfo) const {
    return device_functions->BeginCommandBuffer(commandbuffer, pBeginInfo); }
[[nodiscard]] Result End() const {
    return device_functions->EndCommandBuffer(commandbuffer); }
[[nodiscard]] Result Reset(CommandBufferResetFlags flags = {}) const {
    return device_functions->ResetCommandBuffer(commandbuffer, flags); }
CommandBufferFunctions const& BindPipeline(PipelineBindPoint pipelineBindPoint, Pipeline pipeline) const {
    device_functions->CmdBindPipeline(commandbuffer, pipelineBindPoint, pipeline);
    return *this; }
CommandBufferFunctions const& SetViewport(uint32_t firstViewport, detail::span<const Viewport> Viewports) const {
    device_functions->CmdSetViewport(commandbuffer, firstViewport, Viewports);
    return *this; }
CommandBufferFunctions const& SetScissor(uint32_t firstScissor, detail::span<const Rect2D> Scissors) const {
    device_functions->CmdSetScissor(commandbuffer, firstScissor, Scissors);
    return *this; }
CommandBufferFunctions const& SetLineWidth(float lineWidth) const {
    device_functions->CmdSetLineWidth(commandbuffer, lineWidth);
    return *this; }
CommandBufferFunctions const& SetDepthBias(float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) const {
    device_functions->CmdSetDepthBias(commandbuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
    return *this; }
CommandBufferFunctions const& SetBlendConstants(const float blendConstants[4]) const {
    device_functions->CmdSetBlendConstants(commandbuffer, blendConstants);
    return *this; }
CommandBufferFunctions const& SetDepthBounds(float minDepthBounds, float maxDepthBounds) const {
    device_functions->CmdSetDepthBounds(commandbuffer, minDepthBounds, maxDepthBounds);
    return *this; }
CommandBufferFunctions const& SetStencilCompareMask(StencilFaceFlags faceMask, uint32_t compareMask) const {
    device_functions->CmdSetStencilCompareMask(commandbuffer, faceMask, compareMask);
    return *this; }
CommandBufferFunctions const& SetStencilWriteMask(StencilFaceFlags faceMask, uint32_t writeMask) const {
    device_functions->CmdSetStencilWriteMask(commandbuffer, faceMask, writeMask);
    return *this; }
CommandBufferFunctions const& SetStencilReference(StencilFaceFlags faceMask, uint32_t reference) const {
    device_functions->CmdSetStencilReference(commandbuffer, faceMask, reference);
    return *this; }
CommandBufferFunctions const& BindDescriptorSets(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t firstSet, detail::span<const DescriptorSet> DescriptorSets, detail::span<const uint32_t> DynamicOffsets) const {
    device_functions->CmdBindDescriptorSets(commandbuffer, pipelineBindPoint, layout, firstSet, DescriptorSets, DynamicOffsets);
    return *this; }
CommandBufferFunctions const& BindIndexBuffer(Buffer buffer, DeviceSize offset, IndexType indexType) const {
    device_functions->CmdBindIndexBuffer(commandbuffer, buffer, offset, indexType);
    return *this; }
CommandBufferFunctions const& BindVertexBuffers(uint32_t firstBinding, detail::span<const Buffer> Buffers, detail::span<const DeviceSize> Offsets) const {
    device_functions->CmdBindVertexBuffers(commandbuffer, firstBinding, Buffers, Offsets);
    return *this; }
CommandBufferFunctions const& Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const {
    device_functions->CmdDraw(commandbuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    return *this; }
CommandBufferFunctions const& DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const {
    device_functions->CmdDrawIndexed(commandbuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
    return *this; }
CommandBufferFunctions const& DrawIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
    device_functions->CmdDrawIndirect(commandbuffer, buffer, offset, drawCount, stride);
    return *this; }
CommandBufferFunctions const& DrawIndexedIndirect(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
    device_functions->CmdDrawIndexedIndirect(commandbuffer, buffer, offset, drawCount, stride);
    return *this; }
CommandBufferFunctions const& Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const {
    device_functions->CmdDispatch(commandbuffer, groupCountX, groupCountY, groupCountZ);
    return *this; }
CommandBufferFunctions const& DispatchIndirect(Buffer buffer, DeviceSize offset) const {
    device_functions->CmdDispatchIndirect(commandbuffer, buffer, offset);
    return *this; }
CommandBufferFunctions const& CopyBuffer(Buffer srcBuffer, Buffer dstBuffer, detail::span<const BufferCopy> Regions) const {
    device_functions->CmdCopyBuffer(commandbuffer, srcBuffer, dstBuffer, Regions);
    return *this; }
CommandBufferFunctions const& CopyImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, detail::span<const ImageCopy> Regions) const {
    device_functions->CmdCopyImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, Regions);
    return *this; }
CommandBufferFunctions const& BlitImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, detail::span<const ImageBlit> Regions, Filter filter) const {
    device_functions->CmdBlitImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, Regions, filter);
    return *this; }
CommandBufferFunctions const& CopyBufferToImage(Buffer srcBuffer, Image dstImage, ImageLayout dstImageLayout, detail::span<const BufferImageCopy> Regions) const {
    device_functions->CmdCopyBufferToImage(commandbuffer, srcBuffer, dstImage, dstImageLayout, Regions);
    return *this; }
CommandBufferFunctions const& CopyImageToBuffer(Image srcImage, ImageLayout srcImageLayout, Buffer dstBuffer, detail::span<const BufferImageCopy> Regions) const {
    device_functions->CmdCopyImageToBuffer(commandbuffer, srcImage, srcImageLayout, dstBuffer, Regions);
    return *this; }
CommandBufferFunctions const& UpdateBuffer(Buffer dstBuffer, DeviceSize dstOffset, detail::span<const std::byte> Data) const {
    device_functions->CmdUpdateBuffer(commandbuffer, dstBuffer, dstOffset, Data);
    return *this; }
CommandBufferFunctions const& FillBuffer(Buffer dstBuffer, DeviceSize dstOffset, DeviceSize size, uint32_t data) const {
    device_functions->CmdFillBuffer(commandbuffer, dstBuffer, dstOffset, size, data);
    return *this; }
CommandBufferFunctions const& ClearColorImage(Image image, ImageLayout imageLayout, const ClearColorValue&  pColor, detail::span<const ImageSubresourceRange> Ranges) const {
    device_functions->CmdClearColorImage(commandbuffer, image, imageLayout, pColor, Ranges);
    return *this; }
CommandBufferFunctions const& ClearDepthStencilImage(Image image, ImageLayout imageLayout, const ClearDepthStencilValue&  pDepthStencil, detail::span<const ImageSubresourceRange> Ranges) const {
    device_functions->CmdClearDepthStencilImage(commandbuffer, image, imageLayout, pDepthStencil, Ranges);
    return *this; }
CommandBufferFunctions const& ClearAttachments(detail::span<const ClearAttachment> Attachments, detail::span<const ClearRect> Rects) const {
    device_functions->CmdClearAttachments(commandbuffer, Attachments, Rects);
    return *this; }
CommandBufferFunctions const& ResolveImage(Image srcImage, ImageLayout srcImageLayout, Image dstImage, ImageLayout dstImageLayout, detail::span<const ImageResolve> Regions) const {
    device_functions->CmdResolveImage(commandbuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, Regions);
    return *this; }
CommandBufferFunctions const& SetEvent(Event event, PipelineStageFlags stageMask) const {
    device_functions->CmdSetEvent(commandbuffer, event, stageMask);
    return *this; }
CommandBufferFunctions const& ResetEvent(Event event, PipelineStageFlags stageMask) const {
    device_functions->CmdResetEvent(commandbuffer, event, stageMask);
    return *this; }
CommandBufferFunctions const& WaitEvents(detail::span<const Event> Events, PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, detail::span<const MemoryBarrier> MemoryBarriers, detail::span<const BufferMemoryBarrier> BufferMemoryBarriers, detail::span<const ImageMemoryBarrier> ImageMemoryBarriers) const {
    device_functions->CmdWaitEvents(commandbuffer, Events, srcStageMask, dstStageMask, MemoryBarriers, BufferMemoryBarriers, ImageMemoryBarriers);
    return *this; }
CommandBufferFunctions const& PipelineBarrier(PipelineStageFlags srcStageMask, PipelineStageFlags dstStageMask, DependencyFlags dependencyFlags, detail::span<const MemoryBarrier> MemoryBarriers, detail::span<const BufferMemoryBarrier> BufferMemoryBarriers, detail::span<const ImageMemoryBarrier> ImageMemoryBarriers) const {
    device_functions->CmdPipelineBarrier(commandbuffer, srcStageMask, dstStageMask, dependencyFlags, MemoryBarriers, BufferMemoryBarriers, ImageMemoryBarriers);
    return *this; }
CommandBufferFunctions const& BeginQuery(QueryPool queryPool, uint32_t query, QueryControlFlags flags = {}) const {
    device_functions->CmdBeginQuery(commandbuffer, queryPool, query, flags);
    return *this; }
CommandBufferFunctions const& EndQuery(QueryPool queryPool, uint32_t query) const {
    device_functions->CmdEndQuery(commandbuffer, queryPool, query);
    return *this; }
CommandBufferFunctions const& BeginConditionalRenderingEXT(const ConditionalRenderingBeginInfoEXT&  pConditionalRenderingBegin) const {
    device_functions->CmdBeginConditionalRenderingEXT(commandbuffer, pConditionalRenderingBegin);
    return *this; }
CommandBufferFunctions const& EndConditionalRenderingEXT() const {
    device_functions->CmdEndConditionalRenderingEXT(commandbuffer);
    return *this; }
CommandBufferFunctions const& ResetQueryPool(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) const {
    device_functions->CmdResetQueryPool(commandbuffer, queryPool, firstQuery, queryCount);
    return *this; }
CommandBufferFunctions const& WriteTimestamp(PipelineStageFlagBits pipelineStage, QueryPool queryPool, uint32_t query) const {
    device_functions->CmdWriteTimestamp(commandbuffer, pipelineStage, queryPool, query);
    return *this; }
CommandBufferFunctions const& CopyQueryPoolResults(QueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, Buffer dstBuffer, DeviceSize dstOffset, DeviceSize stride, QueryResultFlags flags = {}) const {
    device_functions->CmdCopyQueryPoolResults(commandbuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
    return *this; }
CommandBufferFunctions const& PushConstants(PipelineLayout layout, ShaderStageFlags stageFlags, uint32_t offset, detail::span<const std::byte> Values) const {
    device_functions->CmdPushConstants(commandbuffer, layout, stageFlags, offset, Values);
    return *this; }
CommandBufferFunctions const& BeginRenderPass(const RenderPassBeginInfo&  pRenderPassBegin, SubpassContents contents) const {
    device_functions->CmdBeginRenderPass(commandbuffer, pRenderPassBegin, contents);
    return *this; }
CommandBufferFunctions const& NextSubpass(SubpassContents contents) const {
    device_functions->CmdNextSubpass(commandbuffer, contents);
    return *this; }
CommandBufferFunctions const& EndRenderPass() const {
    device_functions->CmdEndRenderPass(commandbuffer);
    return *this; }
CommandBufferFunctions const& ExecuteCommands(detail::span<const CommandBuffer> CommandBuffers) const {
    device_functions->CmdExecuteCommands(commandbuffer, CommandBuffers);
    return *this; }
CommandBufferFunctions const& DebugMarkerBeginEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
    device_functions->CmdDebugMarkerBeginEXT(commandbuffer, pMarkerInfo);
    return *this; }
CommandBufferFunctions const& DebugMarkerEndEXT() const {
    device_functions->CmdDebugMarkerEndEXT(commandbuffer);
    return *this; }
CommandBufferFunctions const& DebugMarkerInsertEXT(const DebugMarkerMarkerInfoEXT&  pMarkerInfo) const {
    device_functions->CmdDebugMarkerInsertEXT(commandbuffer, pMarkerInfo);
    return *this; }
CommandBufferFunctions const& ExecuteGeneratedCommandsNV(Bool32 isPreprocessed, const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
    device_functions->CmdExecuteGeneratedCommandsNV(commandbuffer, isPreprocessed, pGeneratedCommandsInfo);
    return *this; }
CommandBufferFunctions const& PreprocessGeneratedCommandsNV(const GeneratedCommandsInfoNV&  pGeneratedCommandsInfo) const {
    device_functions->CmdPreprocessGeneratedCommandsNV(commandbuffer, pGeneratedCommandsInfo);
    return *this; }
CommandBufferFunctions const& BindPipelineShaderGroupNV(PipelineBindPoint pipelineBindPoint, Pipeline pipeline, uint32_t groupIndex) const {
    device_functions->CmdBindPipelineShaderGroupNV(commandbuffer, pipelineBindPoint, pipeline, groupIndex);
    return *this; }
CommandBufferFunctions const& PushDescriptorSetKHR(PipelineBindPoint pipelineBindPoint, PipelineLayout layout, uint32_t set, detail::span<const WriteDescriptorSet> DescriptorWrites) const {
    device_functions->CmdPushDescriptorSetKHR(commandbuffer, pipelineBindPoint, layout, set, DescriptorWrites);
    return *this; }
CommandBufferFunctions const& SetDeviceMask(uint32_t deviceMask) const {
    device_functions->CmdSetDeviceMask(commandbuffer, deviceMask);
    return *this; }
CommandBufferFunctions const& DispatchBase(uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) const {
    device_functions->CmdDispatchBase(commandbuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
    return *this; }
CommandBufferFunctions const& PushDescriptorSetWithTemplateKHR(DescriptorUpdateTemplate descriptorUpdateTemplate, PipelineLayout layout, uint32_t set, const void* pData) const {
    device_functions->CmdPushDescriptorSetWithTemplateKHR(commandbuffer, descriptorUpdateTemplate, layout, set, pData);
    return *this; }
CommandBufferFunctions const& SetViewportWScalingNV(uint32_t firstViewport, detail::span<const ViewportWScalingNV> ViewportWScalings) const {
    device_functions->CmdSetViewportWScalingNV(commandbuffer, firstViewport, ViewportWScalings);
    return *this; }
CommandBufferFunctions const& SetDiscardRectangleEXT(uint32_t firstDiscardRectangle, detail::span<const Rect2D> DiscardRectangles) const {
    device_functions->CmdSetDiscardRectangleEXT(commandbuffer, firstDiscardRectangle, DiscardRectangles);
    return *this; }
CommandBufferFunctions const& SetSampleLocationsEXT(const SampleLocationsInfoEXT&  pSampleLocationsInfo) const {
    device_functions->CmdSetSampleLocationsEXT(commandbuffer, pSampleLocationsInfo);
    return *this; }
CommandBufferFunctions const& BeginDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
    device_functions->CmdBeginDebugUtilsLabelEXT(commandbuffer, pLabelInfo);
    return *this; }
CommandBufferFunctions const& EndDebugUtilsLabelEXT() const {
    device_functions->CmdEndDebugUtilsLabelEXT(commandbuffer);
    return *this; }
CommandBufferFunctions const& InsertDebugUtilsLabelEXT(const DebugUtilsLabelEXT&  pLabelInfo) const {
    device_functions->CmdInsertDebugUtilsLabelEXT(commandbuffer, pLabelInfo);
    return *this; }
CommandBufferFunctions const& WriteBufferMarkerAMD(PipelineStageFlagBits pipelineStage, Buffer dstBuffer, DeviceSize dstOffset, uint32_t marker) const {
    device_functions->CmdWriteBufferMarkerAMD(commandbuffer, pipelineStage, dstBuffer, dstOffset, marker);
    return *this; }
CommandBufferFunctions const& BeginRenderPass2(const RenderPassBeginInfo&  pRenderPassBegin, const SubpassBeginInfo&  pSubpassBeginInfo) const {
    device_functions->CmdBeginRenderPass2(commandbuffer, pRenderPassBegin, pSubpassBeginInfo);
    return *this; }
CommandBufferFunctions const& NextSubpass2(const SubpassBeginInfo&  pSubpassBeginInfo, const SubpassEndInfo&  pSubpassEndInfo) const {
    device_functions->CmdNextSubpass2(commandbuffer, pSubpassBeginInfo, pSubpassEndInfo);
    return *this; }
CommandBufferFunctions const& EndRenderPass2(const SubpassEndInfo&  pSubpassEndInfo) const {
    device_functions->CmdEndRenderPass2(commandbuffer, pSubpassEndInfo);
    return *this; }
CommandBufferFunctions const& DrawIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
    device_functions->CmdDrawIndirectCount(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    return *this; }
CommandBufferFunctions const& DrawIndexedIndirectCount(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
    device_functions->CmdDrawIndexedIndirectCount(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    return *this; }
CommandBufferFunctions const& SetCheckpointNV(const void* pCheckpointMarker) const {
    device_functions->CmdSetCheckpointNV(commandbuffer, pCheckpointMarker);
    return *this; }
CommandBufferFunctions const& BindTransformFeedbackBuffersEXT(uint32_t firstBinding, detail::span<const Buffer> Buffers, detail::span<const DeviceSize> Offsets, detail::span<const DeviceSize> Sizes = {}) const {
    device_functions->CmdBindTransformFeedbackBuffersEXT(commandbuffer, firstBinding, Buffers, Offsets, Sizes);
    return *this; }
CommandBufferFunctions const& BeginTransformFeedbackEXT(uint32_t firstCounterBuffer, detail::span<const Buffer> CounterBuffers, detail::span<const DeviceSize> CounterBufferOffsets = {}) const {
    device_functions->CmdBeginTransformFeedbackEXT(commandbuffer, firstCounterBuffer, CounterBuffers, CounterBufferOffsets);
    return *this; }
CommandBufferFunctions const& EndTransformFeedbackEXT(uint32_t firstCounterBuffer, detail::span<const Buffer> CounterBuffers, detail::span<const DeviceSize> CounterBufferOffsets = {}) const {
    device_functions->CmdEndTransformFeedbackEXT(commandbuffer, firstCounterBuffer, CounterBuffers, CounterBufferOffsets);
    return *this; }
CommandBufferFunctions const& BeginQueryIndexedEXT(QueryPool queryPool, uint32_t query, QueryControlFlags flags, uint32_t index) const {
    device_functions->CmdBeginQueryIndexedEXT(commandbuffer, queryPool, query, flags, index);
    return *this; }
CommandBufferFunctions const& EndQueryIndexedEXT(QueryPool queryPool, uint32_t query, uint32_t index) const {
    device_functions->CmdEndQueryIndexedEXT(commandbuffer, queryPool, query, index);
    return *this; }
CommandBufferFunctions const& DrawIndirectByteCountEXT(uint32_t instanceCount, uint32_t firstInstance, Buffer counterBuffer, DeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) const {
    device_functions->CmdDrawIndirectByteCountEXT(commandbuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
    return *this; }
CommandBufferFunctions const& SetExclusiveScissorNV(uint32_t firstExclusiveScissor, detail::span<const Rect2D> ExclusiveScissors) const {
    device_functions->CmdSetExclusiveScissorNV(commandbuffer, firstExclusiveScissor, ExclusiveScissors);
    return *this; }
CommandBufferFunctions const& BindShadingRateImageNV(ImageView imageView, ImageLayout imageLayout) const {
    device_functions->CmdBindShadingRateImageNV(commandbuffer, imageView, imageLayout);
    return *this; }
CommandBufferFunctions const& SetViewportShadingRatePaletteNV(uint32_t firstViewport, detail::span<const ShadingRatePaletteNV> ShadingRatePalettes) const {
    device_functions->CmdSetViewportShadingRatePaletteNV(commandbuffer, firstViewport, ShadingRatePalettes);
    return *this; }
CommandBufferFunctions const& SetCoarseSampleOrderNV(CoarseSampleOrderTypeNV sampleOrderType, detail::span<const CoarseSampleOrderCustomNV> CustomSampleOrders) const {
    device_functions->CmdSetCoarseSampleOrderNV(commandbuffer, sampleOrderType, CustomSampleOrders);
    return *this; }
CommandBufferFunctions const& DrawMeshTasksNV(uint32_t taskCount, uint32_t firstTask) const {
    device_functions->CmdDrawMeshTasksNV(commandbuffer, taskCount, firstTask);
    return *this; }
CommandBufferFunctions const& DrawMeshTasksIndirectNV(Buffer buffer, DeviceSize offset, uint32_t drawCount, uint32_t stride) const {
    device_functions->CmdDrawMeshTasksIndirectNV(commandbuffer, buffer, offset, drawCount, stride);
    return *this; }
CommandBufferFunctions const& DrawMeshTasksIndirectCountNV(Buffer buffer, DeviceSize offset, Buffer countBuffer, DeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) const {
    device_functions->CmdDrawMeshTasksIndirectCountNV(commandbuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
    return *this; }
CommandBufferFunctions const& CopyAccelerationStructureNV(AccelerationStructureNV dst, AccelerationStructureNV src, CopyAccelerationStructureModeKHR mode) const {
    device_functions->CmdCopyAccelerationStructureNV(commandbuffer, dst, src, mode);
    return *this; }
CommandBufferFunctions const& CopyAccelerationStructureKHR(const CopyAccelerationStructureInfoKHR&  pInfo) const {
    device_functions->CmdCopyAccelerationStructureKHR(commandbuffer, pInfo);
    return *this; }
CommandBufferFunctions const& CopyAccelerationStructureToMemoryKHR(const CopyAccelerationStructureToMemoryInfoKHR&  pInfo) const {
    device_functions->CmdCopyAccelerationStructureToMemoryKHR(commandbuffer, pInfo);
    return *this; }
CommandBufferFunctions const& CopyMemoryToAccelerationStructureKHR(const CopyMemoryToAccelerationStructureInfoKHR&  pInfo) const {
    device_functions->CmdCopyMemoryToAccelerationStructureKHR(commandbuffer, pInfo);
    return *this; }
CommandBufferFunctions const& WriteAccelerationStructuresPropertiesKHR(detail::span<const AccelerationStructureKHR> AccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const {
    device_functions->CmdWriteAccelerationStructuresPropertiesKHR(commandbuffer, AccelerationStructures, queryType, queryPool, firstQuery);
    return *this; }
CommandBufferFunctions const& WriteAccelerationStructuresPropertiesNV(detail::span<const AccelerationStructureNV> AccelerationStructures, QueryType queryType, QueryPool queryPool, uint32_t firstQuery) const {
    device_functions->CmdWriteAccelerationStructuresPropertiesNV(commandbuffer, AccelerationStructures, queryType, queryPool, firstQuery);
    return *this; }
CommandBufferFunctions const& BuildAccelerationStructureNV(const AccelerationStructureInfoNV&  pInfo, Buffer instanceData, DeviceSize instanceOffset, Bool32 update, AccelerationStructureNV dst, AccelerationStructureNV src, Buffer scratch, DeviceSize scratchOffset) const {
    device_functions->CmdBuildAccelerationStructureNV(commandbuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
    return *this; }
CommandBufferFunctions const& TraceRaysKHR(const StridedDeviceAddressRegionKHR&  pRaygenShaderBindingTable, const StridedDeviceAddressRegionKHR&  pMissShaderBindingTable, const StridedDeviceAddressRegionKHR&  pHitShaderBindingTable, const StridedDeviceAddressRegionKHR&  pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) const {
    device_functions->CmdTraceRaysKHR(commandbuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, width, height, depth);
    return *this; }
CommandBufferFunctions const& TraceRaysNV(Buffer raygenShaderBindingTableBuffer, DeviceSize raygenShaderBindingOffset, Buffer missShaderBindingTableBuffer, DeviceSize missShaderBindingOffset, DeviceSize missShaderBindingStride, Buffer hitShaderBindingTableBuffer, DeviceSize hitShaderBindingOffset, DeviceSize hitShaderBindingStride, Buffer callableShaderBindingTableBuffer, DeviceSize callableShaderBindingOffset, DeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) const {
    device_functions->CmdTraceRaysNV(commandbuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth);
    return *this; }
CommandBufferFunctions const& TraceRaysIndirectKHR(const StridedDeviceAddressRegionKHR&  pRaygenShaderBindingTable, const StridedDeviceAddressRegionKHR&  pMissShaderBindingTable, const StridedDeviceAddressRegionKHR&  pHitShaderBindingTable, const StridedDeviceAddressRegionKHR&  pCallableShaderBindingTable, DeviceAddress indirectDeviceAddress) const {
    device_functions->CmdTraceRaysIndirectKHR(commandbuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
    return *this; }
CommandBufferFunctions const& SetRayTracingPipelineStackSizeKHR(uint32_t pipelineStackSize) const {
    device_functions->CmdSetRayTracingPipelineStackSizeKHR(commandbuffer, pipelineStackSize);
    return *this; }
[[nodiscard]] Result SetPerformanceMarkerINTEL(const PerformanceMarkerInfoINTEL&  pMarkerInfo) const {
    return device_functions->CmdSetPerformanceMarkerINTEL(commandbuffer, pMarkerInfo); }
[[nodiscard]] Result SetPerformanceStreamMarkerINTEL(const PerformanceStreamMarkerInfoINTEL&  pMarkerInfo) const {
    return device_functions->CmdSetPerformanceStreamMarkerINTEL(commandbuffer, pMarkerInfo); }
[[nodiscard]] Result SetPerformanceOverrideINTEL(const PerformanceOverrideInfoINTEL&  pOverrideInfo) const {
    return device_functions->CmdSetPerformanceOverrideINTEL(commandbuffer, pOverrideInfo); }
CommandBufferFunctions const& SetLineStippleEXT(uint32_t lineStippleFactor, uint16_t lineStipplePattern) const {
    device_functions->CmdSetLineStippleEXT(commandbuffer, lineStippleFactor, lineStipplePattern);
    return *this; }
CommandBufferFunctions const& BuildAccelerationStructuresKHR(detail::span<const AccelerationStructureBuildGeometryInfoKHR> Infos, detail::span<const AccelerationStructureBuildRangeInfoKHR*> pBuildRangeInfos) const {
    device_functions->CmdBuildAccelerationStructuresKHR(commandbuffer, Infos, pBuildRangeInfos);
    return *this; }
CommandBufferFunctions const& BuildAccelerationStructuresIndirectKHR(detail::span<const AccelerationStructureBuildGeometryInfoKHR> Infos, detail::span<const DeviceAddress> IndirectDeviceAddresses, detail::span<const uint32_t> IndirectStrides, detail::span<const uint32_t*> pMaxPrimitiveCounts) const {
    device_functions->CmdBuildAccelerationStructuresIndirectKHR(commandbuffer, Infos, IndirectDeviceAddresses, IndirectStrides, pMaxPrimitiveCounts);
    return *this; }
CommandBufferFunctions const& SetCullModeEXT(CullModeFlags cullMode = {}) const {
    device_functions->CmdSetCullModeEXT(commandbuffer, cullMode);
    return *this; }
CommandBufferFunctions const& SetFrontFaceEXT(FrontFace frontFace) const {
    device_functions->CmdSetFrontFaceEXT(commandbuffer, frontFace);
    return *this; }
CommandBufferFunctions const& SetPrimitiveTopologyEXT(PrimitiveTopology primitiveTopology) const {
    device_functions->CmdSetPrimitiveTopologyEXT(commandbuffer, primitiveTopology);
    return *this; }
CommandBufferFunctions const& SetViewportWithCountEXT(detail::span<const Viewport> Viewports) const {
    device_functions->CmdSetViewportWithCountEXT(commandbuffer, Viewports);
    return *this; }
CommandBufferFunctions const& SetScissorWithCountEXT(detail::span<const Rect2D> Scissors) const {
    device_functions->CmdSetScissorWithCountEXT(commandbuffer, Scissors);
    return *this; }
CommandBufferFunctions const& BindVertexBuffers2EXT(uint32_t firstBinding, detail::span<const Buffer> Buffers, detail::span<const DeviceSize> Offsets, detail::span<const DeviceSize> Sizes = {}, detail::span<const DeviceSize> Strides = {}) const {
    device_functions->CmdBindVertexBuffers2EXT(commandbuffer, firstBinding, Buffers, Offsets, Sizes, Strides);
    return *this; }
CommandBufferFunctions const& SetDepthTestEnableEXT(Bool32 depthTestEnable) const {
    device_functions->CmdSetDepthTestEnableEXT(commandbuffer, depthTestEnable);
    return *this; }
CommandBufferFunctions const& SetDepthWriteEnableEXT(Bool32 depthWriteEnable) const {
    device_functions->CmdSetDepthWriteEnableEXT(commandbuffer, depthWriteEnable);
    return *this; }
CommandBufferFunctions const& SetDepthCompareOpEXT(CompareOp depthCompareOp) const {
    device_functions->CmdSetDepthCompareOpEXT(commandbuffer, depthCompareOp);
    return *this; }
CommandBufferFunctions const& SetDepthBoundsTestEnableEXT(Bool32 depthBoundsTestEnable) const {
    device_functions->CmdSetDepthBoundsTestEnableEXT(commandbuffer, depthBoundsTestEnable);
    return *this; }
CommandBufferFunctions const& SetStencilTestEnableEXT(Bool32 stencilTestEnable) const {
    device_functions->CmdSetStencilTestEnableEXT(commandbuffer, stencilTestEnable);
    return *this; }
CommandBufferFunctions const& SetStencilOpEXT(StencilFaceFlags faceMask, StencilOp failOp, StencilOp passOp, StencilOp depthFailOp, CompareOp compareOp) const {
    device_functions->CmdSetStencilOpEXT(commandbuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
    return *this; }
CommandBufferFunctions const& CopyBuffer2KHR(const CopyBufferInfo2KHR&  pCopyBufferInfo) const {
    device_functions->CmdCopyBuffer2KHR(commandbuffer, pCopyBufferInfo);
    return *this; }
CommandBufferFunctions const& CopyImage2KHR(const CopyImageInfo2KHR&  pCopyImageInfo) const {
    device_functions->CmdCopyImage2KHR(commandbuffer, pCopyImageInfo);
    return *this; }
CommandBufferFunctions const& BlitImage2KHR(const BlitImageInfo2KHR&  pBlitImageInfo) const {
    device_functions->CmdBlitImage2KHR(commandbuffer, pBlitImageInfo);
    return *this; }
CommandBufferFunctions const& CopyBufferToImage2KHR(const CopyBufferToImageInfo2KHR&  pCopyBufferToImageInfo) const {
    device_functions->CmdCopyBufferToImage2KHR(commandbuffer, pCopyBufferToImageInfo);
    return *this; }
CommandBufferFunctions const& CopyImageToBuffer2KHR(const CopyImageToBufferInfo2KHR&  pCopyImageToBufferInfo) const {
    device_functions->CmdCopyImageToBuffer2KHR(commandbuffer, pCopyImageToBufferInfo);
    return *this; }
CommandBufferFunctions const& ResolveImage2KHR(const ResolveImageInfo2KHR&  pResolveImageInfo) const {
    device_functions->CmdResolveImage2KHR(commandbuffer, pResolveImageInfo);
    return *this; }
CommandBufferFunctions const& SetFragmentShadingRateKHR(const Extent2D&  pFragmentSize, const FragmentShadingRateCombinerOpKHR combinerOps[2]) const {
    device_functions->CmdSetFragmentShadingRateKHR(commandbuffer, pFragmentSize, combinerOps);
    return *this; }
CommandBufferFunctions const& SetFragmentShadingRateEnumNV(FragmentShadingRateNV shadingRate, const FragmentShadingRateCombinerOpKHR combinerOps[2]) const {
    device_functions->CmdSetFragmentShadingRateEnumNV(commandbuffer, shadingRate, combinerOps);
    return *this; }
};
inline const char * to_string(AttachmentLoadOp val) {
    switch(val) {
        case(AttachmentLoadOp::Load): return "Load";
        case(AttachmentLoadOp::Clear): return "Clear";
        case(AttachmentLoadOp::DontCare): return "DontCare";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(AttachmentStoreOp val) {
    switch(val) {
        case(AttachmentStoreOp::Store): return "Store";
        case(AttachmentStoreOp::DontCare): return "DontCare";
        case(AttachmentStoreOp::NoneQCOM): return "NoneQCOM";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(BlendFactor val) {
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
inline const char * to_string(BlendOp val) {
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
inline const char * to_string(BorderColor val) {
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
inline const char * to_string(PipelineCacheHeaderVersion val) {
    switch(val) {
        case(PipelineCacheHeaderVersion::One): return "One";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ComponentSwizzle val) {
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
inline const char * to_string(CommandBufferLevel val) {
    switch(val) {
        case(CommandBufferLevel::Primary): return "Primary";
        case(CommandBufferLevel::Secondary): return "Secondary";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(CompareOp val) {
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
inline const char * to_string(DescriptorType val) {
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
        case(DescriptorType::AccelerationStructureNV): return "AccelerationStructureNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(DynamicState val) {
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
        case(DynamicState::RayTracingPipelineStackSizeKHR): return "RayTracingPipelineStackSizeKHR";
        case(DynamicState::ViewportShadingRatePaletteNV): return "ViewportShadingRatePaletteNV";
        case(DynamicState::ViewportCoarseSampleOrderNV): return "ViewportCoarseSampleOrderNV";
        case(DynamicState::ExclusiveScissorNV): return "ExclusiveScissorNV";
        case(DynamicState::FragmentShadingRateKHR): return "FragmentShadingRateKHR";
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
inline const char * to_string(PolygonMode val) {
    switch(val) {
        case(PolygonMode::Fill): return "Fill";
        case(PolygonMode::Line): return "Line";
        case(PolygonMode::Point): return "Point";
        case(PolygonMode::FillRectangleNV): return "FillRectangleNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(Format val) {
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
inline const char * to_string(FrontFace val) {
    switch(val) {
        case(FrontFace::CounterClockwise): return "CounterClockwise";
        case(FrontFace::Clockwise): return "Clockwise";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ImageLayout val) {
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
inline const char * to_string(ImageTiling val) {
    switch(val) {
        case(ImageTiling::Optimal): return "Optimal";
        case(ImageTiling::Linear): return "Linear";
        case(ImageTiling::DrmFormatModifierEXT): return "DrmFormatModifierEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ImageType val) {
    switch(val) {
        case(ImageType::e1D): return "e1D";
        case(ImageType::e2D): return "e2D";
        case(ImageType::e3D): return "e3D";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ImageViewType val) {
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
inline const char * to_string(SharingMode val) {
    switch(val) {
        case(SharingMode::Exclusive): return "Exclusive";
        case(SharingMode::Concurrent): return "Concurrent";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(IndexType val) {
    switch(val) {
        case(IndexType::Uint16): return "Uint16";
        case(IndexType::Uint32): return "Uint32";
        case(IndexType::NoneKHR): return "NoneKHR";
        case(IndexType::Uint8EXT): return "Uint8EXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(LogicOp val) {
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
inline const char * to_string(PhysicalDeviceType val) {
    switch(val) {
        case(PhysicalDeviceType::Other): return "Other";
        case(PhysicalDeviceType::IntegratedGpu): return "IntegratedGpu";
        case(PhysicalDeviceType::DiscreteGpu): return "DiscreteGpu";
        case(PhysicalDeviceType::VirtualGpu): return "VirtualGpu";
        case(PhysicalDeviceType::Cpu): return "Cpu";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PipelineBindPoint val) {
    switch(val) {
        case(PipelineBindPoint::Graphics): return "Graphics";
        case(PipelineBindPoint::Compute): return "Compute";
        case(PipelineBindPoint::RayTracingKHR): return "RayTracingKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PrimitiveTopology val) {
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
inline const char * to_string(QueryType val) {
    switch(val) {
        case(QueryType::Occlusion): return "Occlusion";
        case(QueryType::PipelineStatistics): return "PipelineStatistics";
        case(QueryType::Timestamp): return "Timestamp";
        case(QueryType::TransformFeedbackStreamEXT): return "TransformFeedbackStreamEXT";
        case(QueryType::PerformanceQueryKHR): return "PerformanceQueryKHR";
        case(QueryType::AccelerationStructureCompactedSizeKHR): return "AccelerationStructureCompactedSizeKHR";
        case(QueryType::AccelerationStructureSerializationSizeKHR): return "AccelerationStructureSerializationSizeKHR";
        case(QueryType::AccelerationStructureCompactedSizeNV): return "AccelerationStructureCompactedSizeNV";
        case(QueryType::PerformanceQueryINTEL): return "PerformanceQueryINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SubpassContents val) {
    switch(val) {
        case(SubpassContents::Inline): return "Inline";
        case(SubpassContents::SecondaryCommandBuffers): return "SecondaryCommandBuffers";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(Result val) {
    switch(val) {
        case(Result::Success): return "Success";
        case(Result::NotReady): return "NotReady";
        case(Result::Timeout): return "Timeout";
        case(Result::EventSet): return "EventSet";
        case(Result::EventReset): return "EventReset";
        case(Result::Incomplete): return "Incomplete";
        case(Result::ErrorOutOfHostMemory): return "ErrorOutOfHostMemory";
        case(Result::ErrorOutOfDeviceMemory): return "ErrorOutOfDeviceMemory";
        case(Result::ErrorInitializationFailed): return "ErrorInitializationFailed";
        case(Result::ErrorDeviceLost): return "ErrorDeviceLost";
        case(Result::ErrorMemoryMapFailed): return "ErrorMemoryMapFailed";
        case(Result::ErrorLayerNotPresent): return "ErrorLayerNotPresent";
        case(Result::ErrorExtensionNotPresent): return "ErrorExtensionNotPresent";
        case(Result::ErrorFeatureNotPresent): return "ErrorFeatureNotPresent";
        case(Result::ErrorIncompatibleDriver): return "ErrorIncompatibleDriver";
        case(Result::ErrorTooManyObjects): return "ErrorTooManyObjects";
        case(Result::ErrorFormatNotSupported): return "ErrorFormatNotSupported";
        case(Result::ErrorFragmentedPool): return "ErrorFragmentedPool";
        case(Result::ErrorUnknown): return "ErrorUnknown";
        case(Result::ErrorSurfaceLostKHR): return "ErrorSurfaceLostKHR";
        case(Result::ErrorNativeWindowInUseKHR): return "ErrorNativeWindowInUseKHR";
        case(Result::SuboptimalKHR): return "SuboptimalKHR";
        case(Result::ErrorOutOfDateKHR): return "ErrorOutOfDateKHR";
        case(Result::ErrorIncompatibleDisplayKHR): return "ErrorIncompatibleDisplayKHR";
        case(Result::ErrorValidationFailedEXT): return "ErrorValidationFailedEXT";
        case(Result::ErrorInvalidShaderNV): return "ErrorInvalidShaderNV";
        case(Result::ErrorInvalidDrmFormatModifierPlaneLayoutEXT): return "ErrorInvalidDrmFormatModifierPlaneLayoutEXT";
        case(Result::ErrorNotPermittedEXT): return "ErrorNotPermittedEXT";
        case(Result::ErrorFullScreenExclusiveModeLostEXT): return "ErrorFullScreenExclusiveModeLostEXT";
        case(Result::ThreadIdleKHR): return "ThreadIdleKHR";
        case(Result::ThreadDoneKHR): return "ThreadDoneKHR";
        case(Result::OperationDeferredKHR): return "OperationDeferredKHR";
        case(Result::OperationNotDeferredKHR): return "OperationNotDeferredKHR";
        case(Result::PipelineCompileRequiredEXT): return "PipelineCompileRequiredEXT";
        case(Result::ErrorOutOfPoolMemory): return "ErrorOutOfPoolMemory";
        case(Result::ErrorInvalidExternalHandle): return "ErrorInvalidExternalHandle";
        case(Result::ErrorFragmentation): return "ErrorFragmentation";
        case(Result::ErrorInvalidOpaqueCaptureAddress): return "ErrorInvalidOpaqueCaptureAddress";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(StencilOp val) {
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
inline const char * to_string(StructureType val) {
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
        case(StructureType::WriteDescriptorSetAccelerationStructureKHR): return "WriteDescriptorSetAccelerationStructureKHR";
        case(StructureType::AccelerationStructureBuildGeometryInfoKHR): return "AccelerationStructureBuildGeometryInfoKHR";
        case(StructureType::AccelerationStructureDeviceAddressInfoKHR): return "AccelerationStructureDeviceAddressInfoKHR";
        case(StructureType::AccelerationStructureGeometryAabbsDataKHR): return "AccelerationStructureGeometryAabbsDataKHR";
        case(StructureType::AccelerationStructureGeometryInstancesDataKHR): return "AccelerationStructureGeometryInstancesDataKHR";
        case(StructureType::AccelerationStructureGeometryTrianglesDataKHR): return "AccelerationStructureGeometryTrianglesDataKHR";
        case(StructureType::AccelerationStructureGeometryKHR): return "AccelerationStructureGeometryKHR";
        case(StructureType::AccelerationStructureVersionInfoKHR): return "AccelerationStructureVersionInfoKHR";
        case(StructureType::CopyAccelerationStructureInfoKHR): return "CopyAccelerationStructureInfoKHR";
        case(StructureType::CopyAccelerationStructureToMemoryInfoKHR): return "CopyAccelerationStructureToMemoryInfoKHR";
        case(StructureType::CopyMemoryToAccelerationStructureInfoKHR): return "CopyMemoryToAccelerationStructureInfoKHR";
        case(StructureType::PhysicalDeviceAccelerationStructureFeaturesKHR): return "PhysicalDeviceAccelerationStructureFeaturesKHR";
        case(StructureType::PhysicalDeviceAccelerationStructurePropertiesKHR): return "PhysicalDeviceAccelerationStructurePropertiesKHR";
        case(StructureType::AccelerationStructureCreateInfoKHR): return "AccelerationStructureCreateInfoKHR";
        case(StructureType::AccelerationStructureBuildSizesInfoKHR): return "AccelerationStructureBuildSizesInfoKHR";
        case(StructureType::PhysicalDeviceRayTracingPipelineFeaturesKHR): return "PhysicalDeviceRayTracingPipelineFeaturesKHR";
        case(StructureType::PhysicalDeviceRayTracingPipelinePropertiesKHR): return "PhysicalDeviceRayTracingPipelinePropertiesKHR";
        case(StructureType::RayTracingPipelineCreateInfoKHR): return "RayTracingPipelineCreateInfoKHR";
        case(StructureType::RayTracingShaderGroupCreateInfoKHR): return "RayTracingShaderGroupCreateInfoKHR";
        case(StructureType::RayTracingPipelineInterfaceCreateInfoKHR): return "RayTracingPipelineInterfaceCreateInfoKHR";
        case(StructureType::PhysicalDeviceRayQueryFeaturesKHR): return "PhysicalDeviceRayQueryFeaturesKHR";
        case(StructureType::PipelineCoverageModulationStateCreateInfoNV): return "PipelineCoverageModulationStateCreateInfoNV";
        case(StructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV): return "PhysicalDeviceShaderSmBuiltinsFeaturesNV";
        case(StructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV): return "PhysicalDeviceShaderSmBuiltinsPropertiesNV";
        case(StructureType::DrmFormatModifierPropertiesListEXT): return "DrmFormatModifierPropertiesListEXT";
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
        case(StructureType::BindAccelerationStructureMemoryInfoNV): return "BindAccelerationStructureMemoryInfoNV";
        case(StructureType::WriteDescriptorSetAccelerationStructureNV): return "WriteDescriptorSetAccelerationStructureNV";
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
        case(StructureType::PhysicalDeviceShaderTerminateInvocationFeaturesKHR): return "PhysicalDeviceShaderTerminateInvocationFeaturesKHR";
        case(StructureType::MetalSurfaceCreateInfoEXT): return "MetalSurfaceCreateInfoEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT): return "PhysicalDeviceFragmentDensityMapFeaturesEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT): return "PhysicalDeviceFragmentDensityMapPropertiesEXT";
        case(StructureType::RenderPassFragmentDensityMapCreateInfoEXT): return "RenderPassFragmentDensityMapCreateInfoEXT";
        case(StructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT): return "PhysicalDeviceSubgroupSizeControlPropertiesEXT";
        case(StructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT): return "PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT";
        case(StructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT): return "PhysicalDeviceSubgroupSizeControlFeaturesEXT";
        case(StructureType::FragmentShadingRateAttachmentInfoKHR): return "FragmentShadingRateAttachmentInfoKHR";
        case(StructureType::PipelineFragmentShadingRateStateCreateInfoKHR): return "PipelineFragmentShadingRateStateCreateInfoKHR";
        case(StructureType::PhysicalDeviceFragmentShadingRatePropertiesKHR): return "PhysicalDeviceFragmentShadingRatePropertiesKHR";
        case(StructureType::PhysicalDeviceFragmentShadingRateFeaturesKHR): return "PhysicalDeviceFragmentShadingRateFeaturesKHR";
        case(StructureType::PhysicalDeviceFragmentShadingRateKHR): return "PhysicalDeviceFragmentShadingRateKHR";
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
        case(StructureType::PhysicalDeviceFragmentShadingRateEnumsPropertiesNV): return "PhysicalDeviceFragmentShadingRateEnumsPropertiesNV";
        case(StructureType::PhysicalDeviceFragmentShadingRateEnumsFeaturesNV): return "PhysicalDeviceFragmentShadingRateEnumsFeaturesNV";
        case(StructureType::PipelineFragmentShadingRateEnumStateCreateInfoNV): return "PipelineFragmentShadingRateEnumStateCreateInfoNV";
        case(StructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT): return "PhysicalDeviceFragmentDensityMap2FeaturesEXT";
        case(StructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT): return "PhysicalDeviceFragmentDensityMap2PropertiesEXT";
        case(StructureType::CopyCommandTransformInfoQCOM): return "CopyCommandTransformInfoQCOM";
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
inline const char * to_string(SystemAllocationScope val) {
    switch(val) {
        case(SystemAllocationScope::Command): return "Command";
        case(SystemAllocationScope::Object): return "Object";
        case(SystemAllocationScope::Cache): return "Cache";
        case(SystemAllocationScope::Device): return "Device";
        case(SystemAllocationScope::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(InternalAllocationType val) {
    switch(val) {
        case(InternalAllocationType::Executable): return "Executable";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SamplerAddressMode val) {
    switch(val) {
        case(SamplerAddressMode::Repeat): return "Repeat";
        case(SamplerAddressMode::MirroredRepeat): return "MirroredRepeat";
        case(SamplerAddressMode::ClampToEdge): return "ClampToEdge";
        case(SamplerAddressMode::ClampToBorder): return "ClampToBorder";
        case(SamplerAddressMode::MirrorClampToEdge): return "MirrorClampToEdge";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(Filter val) {
    switch(val) {
        case(Filter::Nearest): return "Nearest";
        case(Filter::Linear): return "Linear";
        case(Filter::CubicIMG): return "CubicIMG";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SamplerMipmapMode val) {
    switch(val) {
        case(SamplerMipmapMode::Nearest): return "Nearest";
        case(SamplerMipmapMode::Linear): return "Linear";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(VertexInputRate val) {
    switch(val) {
        case(VertexInputRate::Vertex): return "Vertex";
        case(VertexInputRate::Instance): return "Instance";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ObjectType val) {
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
        case(ObjectType::AccelerationStructureNV): return "AccelerationStructureNV";
        case(ObjectType::PerformanceConfigurationINTEL): return "PerformanceConfigurationINTEL";
        case(ObjectType::DeferredOperationKHR): return "DeferredOperationKHR";
        case(ObjectType::IndirectCommandsLayoutNV): return "IndirectCommandsLayoutNV";
        case(ObjectType::PrivateDataSlotEXT): return "PrivateDataSlotEXT";
        case(ObjectType::SamplerYcbcrConversion): return "SamplerYcbcrConversion";
        case(ObjectType::DescriptorUpdateTemplate): return "DescriptorUpdateTemplate";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(IndirectCommandsTokenTypeNV val) {
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
inline const char * to_string(DescriptorUpdateTemplateType val) {
    switch(val) {
        case(DescriptorUpdateTemplateType::DescriptorSet): return "DescriptorSet";
        case(DescriptorUpdateTemplateType::PushDescriptorsKHR): return "PushDescriptorsKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ViewportCoordinateSwizzleNV val) {
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
inline const char * to_string(DiscardRectangleModeEXT val) {
    switch(val) {
        case(DiscardRectangleModeEXT::InclusiveEXT): return "InclusiveEXT";
        case(DiscardRectangleModeEXT::ExclusiveEXT): return "ExclusiveEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PointClippingBehavior val) {
    switch(val) {
        case(PointClippingBehavior::AllClipPlanes): return "AllClipPlanes";
        case(PointClippingBehavior::UserClipPlanesOnly): return "UserClipPlanesOnly";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(CoverageModulationModeNV val) {
    switch(val) {
        case(CoverageModulationModeNV::NoneNV): return "NoneNV";
        case(CoverageModulationModeNV::RgbNV): return "RgbNV";
        case(CoverageModulationModeNV::AlphaNV): return "AlphaNV";
        case(CoverageModulationModeNV::RgbaNV): return "RgbaNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(CoverageReductionModeNV val) {
    switch(val) {
        case(CoverageReductionModeNV::MergeNV): return "MergeNV";
        case(CoverageReductionModeNV::TruncateNV): return "TruncateNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ValidationCacheHeaderVersionEXT val) {
    switch(val) {
        case(ValidationCacheHeaderVersionEXT::OneEXT): return "OneEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ShaderInfoTypeAMD val) {
    switch(val) {
        case(ShaderInfoTypeAMD::StatisticsAMD): return "StatisticsAMD";
        case(ShaderInfoTypeAMD::BinaryAMD): return "BinaryAMD";
        case(ShaderInfoTypeAMD::DisassemblyAMD): return "DisassemblyAMD";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(QueueGlobalPriorityEXT val) {
    switch(val) {
        case(QueueGlobalPriorityEXT::LowEXT): return "LowEXT";
        case(QueueGlobalPriorityEXT::MediumEXT): return "MediumEXT";
        case(QueueGlobalPriorityEXT::HighEXT): return "HighEXT";
        case(QueueGlobalPriorityEXT::RealtimeEXT): return "RealtimeEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(TimeDomainEXT val) {
    switch(val) {
        case(TimeDomainEXT::DeviceEXT): return "DeviceEXT";
        case(TimeDomainEXT::ClockMonotonicEXT): return "ClockMonotonicEXT";
        case(TimeDomainEXT::ClockMonotonicRawEXT): return "ClockMonotonicRawEXT";
        case(TimeDomainEXT::QueryPerformanceCounterEXT): return "QueryPerformanceCounterEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ConservativeRasterizationModeEXT val) {
    switch(val) {
        case(ConservativeRasterizationModeEXT::DisabledEXT): return "DisabledEXT";
        case(ConservativeRasterizationModeEXT::OverestimateEXT): return "OverestimateEXT";
        case(ConservativeRasterizationModeEXT::UnderestimateEXT): return "UnderestimateEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SemaphoreType val) {
    switch(val) {
        case(SemaphoreType::Binary): return "Binary";
        case(SemaphoreType::Timeline): return "Timeline";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(BuildAccelerationStructureModeKHR val) {
    switch(val) {
        case(BuildAccelerationStructureModeKHR::BuildKHR): return "BuildKHR";
        case(BuildAccelerationStructureModeKHR::UpdateKHR): return "UpdateKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(CopyAccelerationStructureModeKHR val) {
    switch(val) {
        case(CopyAccelerationStructureModeKHR::CloneKHR): return "CloneKHR";
        case(CopyAccelerationStructureModeKHR::CompactKHR): return "CompactKHR";
        case(CopyAccelerationStructureModeKHR::SerializeKHR): return "SerializeKHR";
        case(CopyAccelerationStructureModeKHR::DeserializeKHR): return "DeserializeKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(AccelerationStructureTypeKHR val) {
    switch(val) {
        case(AccelerationStructureTypeKHR::TopLevelKHR): return "TopLevelKHR";
        case(AccelerationStructureTypeKHR::BottomLevelKHR): return "BottomLevelKHR";
        case(AccelerationStructureTypeKHR::GenericKHR): return "GenericKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(GeometryTypeKHR val) {
    switch(val) {
        case(GeometryTypeKHR::TrianglesKHR): return "TrianglesKHR";
        case(GeometryTypeKHR::AabbsKHR): return "AabbsKHR";
        case(GeometryTypeKHR::InstancesKHR): return "InstancesKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(RayTracingShaderGroupTypeKHR val) {
    switch(val) {
        case(RayTracingShaderGroupTypeKHR::GeneralKHR): return "GeneralKHR";
        case(RayTracingShaderGroupTypeKHR::TrianglesHitGroupKHR): return "TrianglesHitGroupKHR";
        case(RayTracingShaderGroupTypeKHR::ProceduralHitGroupKHR): return "ProceduralHitGroupKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(AccelerationStructureMemoryRequirementsTypeNV val) {
    switch(val) {
        case(AccelerationStructureMemoryRequirementsTypeNV::ObjectNV): return "ObjectNV";
        case(AccelerationStructureMemoryRequirementsTypeNV::BuildScratchNV): return "BuildScratchNV";
        case(AccelerationStructureMemoryRequirementsTypeNV::UpdateScratchNV): return "UpdateScratchNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(AccelerationStructureBuildTypeKHR val) {
    switch(val) {
        case(AccelerationStructureBuildTypeKHR::HostKHR): return "HostKHR";
        case(AccelerationStructureBuildTypeKHR::DeviceKHR): return "DeviceKHR";
        case(AccelerationStructureBuildTypeKHR::HostOrDeviceKHR): return "HostOrDeviceKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(AccelerationStructureCompatibilityKHR val) {
    switch(val) {
        case(AccelerationStructureCompatibilityKHR::CompatibleKHR): return "CompatibleKHR";
        case(AccelerationStructureCompatibilityKHR::IncompatibleKHR): return "IncompatibleKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ShaderGroupShaderKHR val) {
    switch(val) {
        case(ShaderGroupShaderKHR::GeneralKHR): return "GeneralKHR";
        case(ShaderGroupShaderKHR::ClosestHitKHR): return "ClosestHitKHR";
        case(ShaderGroupShaderKHR::AnyHitKHR): return "AnyHitKHR";
        case(ShaderGroupShaderKHR::IntersectionKHR): return "IntersectionKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(MemoryOverallocationBehaviorAMD val) {
    switch(val) {
        case(MemoryOverallocationBehaviorAMD::DefaultAMD): return "DefaultAMD";
        case(MemoryOverallocationBehaviorAMD::AllowedAMD): return "AllowedAMD";
        case(MemoryOverallocationBehaviorAMD::DisallowedAMD): return "DisallowedAMD";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ScopeNV val) {
    switch(val) {
        case(ScopeNV::DeviceNV): return "DeviceNV";
        case(ScopeNV::WorkgroupNV): return "WorkgroupNV";
        case(ScopeNV::SubgroupNV): return "SubgroupNV";
        case(ScopeNV::QueueFamilyNV): return "QueueFamilyNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ComponentTypeNV val) {
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
inline const char * to_string(PerformanceCounterScopeKHR val) {
    switch(val) {
        case(PerformanceCounterScopeKHR::CommandBufferKHR): return "CommandBufferKHR";
        case(PerformanceCounterScopeKHR::RenderPassKHR): return "RenderPassKHR";
        case(PerformanceCounterScopeKHR::CommandKHR): return "CommandKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PerformanceCounterUnitKHR val) {
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
inline const char * to_string(PerformanceCounterStorageKHR val) {
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
inline const char * to_string(PerformanceConfigurationTypeINTEL val) {
    switch(val) {
        case(PerformanceConfigurationTypeINTEL::CommandQueueMetricsDiscoveryActivatedINTEL): return "CommandQueueMetricsDiscoveryActivatedINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(QueryPoolSamplingModeINTEL val) {
    switch(val) {
        case(QueryPoolSamplingModeINTEL::ManualINTEL): return "ManualINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PerformanceOverrideTypeINTEL val) {
    switch(val) {
        case(PerformanceOverrideTypeINTEL::NullHardwareINTEL): return "NullHardwareINTEL";
        case(PerformanceOverrideTypeINTEL::FlushGpuCachesINTEL): return "FlushGpuCachesINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PerformanceParameterTypeINTEL val) {
    switch(val) {
        case(PerformanceParameterTypeINTEL::HwCountersSupportedINTEL): return "HwCountersSupportedINTEL";
        case(PerformanceParameterTypeINTEL::StreamMarkerValidBitsINTEL): return "StreamMarkerValidBitsINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PerformanceValueTypeINTEL val) {
    switch(val) {
        case(PerformanceValueTypeINTEL::Uint32INTEL): return "Uint32INTEL";
        case(PerformanceValueTypeINTEL::Uint64INTEL): return "Uint64INTEL";
        case(PerformanceValueTypeINTEL::FloatINTEL): return "FloatINTEL";
        case(PerformanceValueTypeINTEL::BoolINTEL): return "BoolINTEL";
        case(PerformanceValueTypeINTEL::StringINTEL): return "StringINTEL";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(LineRasterizationModeEXT val) {
    switch(val) {
        case(LineRasterizationModeEXT::DefaultEXT): return "DefaultEXT";
        case(LineRasterizationModeEXT::RectangularEXT): return "RectangularEXT";
        case(LineRasterizationModeEXT::BresenhamEXT): return "BresenhamEXT";
        case(LineRasterizationModeEXT::RectangularSmoothEXT): return "RectangularSmoothEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(FragmentShadingRateNV val) {
    switch(val) {
        case(FragmentShadingRateNV::e1InvocationPerPixelNV): return "e1InvocationPerPixelNV";
        case(FragmentShadingRateNV::e1InvocationPer1X2PixelsNV): return "e1InvocationPer1X2PixelsNV";
        case(FragmentShadingRateNV::e1InvocationPer2X1PixelsNV): return "e1InvocationPer2X1PixelsNV";
        case(FragmentShadingRateNV::e1InvocationPer2X2PixelsNV): return "e1InvocationPer2X2PixelsNV";
        case(FragmentShadingRateNV::e1InvocationPer2X4PixelsNV): return "e1InvocationPer2X4PixelsNV";
        case(FragmentShadingRateNV::e1InvocationPer4X2PixelsNV): return "e1InvocationPer4X2PixelsNV";
        case(FragmentShadingRateNV::e1InvocationPer4X4PixelsNV): return "e1InvocationPer4X4PixelsNV";
        case(FragmentShadingRateNV::e2InvocationsPerPixelNV): return "e2InvocationsPerPixelNV";
        case(FragmentShadingRateNV::e4InvocationsPerPixelNV): return "e4InvocationsPerPixelNV";
        case(FragmentShadingRateNV::e8InvocationsPerPixelNV): return "e8InvocationsPerPixelNV";
        case(FragmentShadingRateNV::e16InvocationsPerPixelNV): return "e16InvocationsPerPixelNV";
        case(FragmentShadingRateNV::NoInvocationsNV): return "NoInvocationsNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(FragmentShadingRateTypeNV val) {
    switch(val) {
        case(FragmentShadingRateTypeNV::FragmentSizeNV): return "FragmentSizeNV";
        case(FragmentShadingRateTypeNV::EnumsNV): return "EnumsNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ColorSpaceKHR val) {
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
inline const char * to_string(PresentModeKHR val) {
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
inline const char * to_string(DebugReportObjectTypeEXT val) {
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
        case(DebugReportObjectTypeEXT::AccelerationStructureNvEXT): return "AccelerationStructureNvEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(DeviceMemoryReportEventTypeEXT val) {
    switch(val) {
        case(DeviceMemoryReportEventTypeEXT::AllocateEXT): return "AllocateEXT";
        case(DeviceMemoryReportEventTypeEXT::FreeEXT): return "FreeEXT";
        case(DeviceMemoryReportEventTypeEXT::ImportEXT): return "ImportEXT";
        case(DeviceMemoryReportEventTypeEXT::UnimportEXT): return "UnimportEXT";
        case(DeviceMemoryReportEventTypeEXT::AllocationFailedEXT): return "AllocationFailedEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(RasterizationOrderAMD val) {
    switch(val) {
        case(RasterizationOrderAMD::StrictAMD): return "StrictAMD";
        case(RasterizationOrderAMD::RelaxedAMD): return "RelaxedAMD";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ValidationCheckEXT val) {
    switch(val) {
        case(ValidationCheckEXT::AllEXT): return "AllEXT";
        case(ValidationCheckEXT::ShadersEXT): return "ShadersEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ValidationFeatureEnableEXT val) {
    switch(val) {
        case(ValidationFeatureEnableEXT::GpuAssistedEXT): return "GpuAssistedEXT";
        case(ValidationFeatureEnableEXT::GpuAssistedReserveBindingSlotEXT): return "GpuAssistedReserveBindingSlotEXT";
        case(ValidationFeatureEnableEXT::BestPracticesEXT): return "BestPracticesEXT";
        case(ValidationFeatureEnableEXT::DebugPrintfEXT): return "DebugPrintfEXT";
        case(ValidationFeatureEnableEXT::SynchronizationValidationEXT): return "SynchronizationValidationEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ValidationFeatureDisableEXT val) {
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
inline const char * to_string(DisplayPowerStateEXT val) {
    switch(val) {
        case(DisplayPowerStateEXT::OffEXT): return "OffEXT";
        case(DisplayPowerStateEXT::SuspendEXT): return "SuspendEXT";
        case(DisplayPowerStateEXT::OnEXT): return "OnEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(DeviceEventTypeEXT val) {
    switch(val) {
        case(DeviceEventTypeEXT::DisplayHotplugEXT): return "DisplayHotplugEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(DisplayEventTypeEXT val) {
    switch(val) {
        case(DisplayEventTypeEXT::FirstPixelOutEXT): return "FirstPixelOutEXT";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(TessellationDomainOrigin val) {
    switch(val) {
        case(TessellationDomainOrigin::UpperLeft): return "UpperLeft";
        case(TessellationDomainOrigin::LowerLeft): return "LowerLeft";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SamplerYcbcrModelConversion val) {
    switch(val) {
        case(SamplerYcbcrModelConversion::RgbIdentity): return "RgbIdentity";
        case(SamplerYcbcrModelConversion::YcbcrIdentity): return "YcbcrIdentity";
        case(SamplerYcbcrModelConversion::Ycbcr709): return "Ycbcr709";
        case(SamplerYcbcrModelConversion::Ycbcr601): return "Ycbcr601";
        case(SamplerYcbcrModelConversion::Ycbcr2020): return "Ycbcr2020";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SamplerYcbcrRange val) {
    switch(val) {
        case(SamplerYcbcrRange::ItuFull): return "ItuFull";
        case(SamplerYcbcrRange::ItuNarrow): return "ItuNarrow";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(ChromaLocation val) {
    switch(val) {
        case(ChromaLocation::CositedEven): return "CositedEven";
        case(ChromaLocation::Midpoint): return "Midpoint";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(SamplerReductionMode val) {
    switch(val) {
        case(SamplerReductionMode::WeightedAverage): return "WeightedAverage";
        case(SamplerReductionMode::Min): return "Min";
        case(SamplerReductionMode::Max): return "Max";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(BlendOverlapEXT val) {
    switch(val) {
        case(BlendOverlapEXT::UncorrelatedEXT): return "UncorrelatedEXT";
        case(BlendOverlapEXT::DisjointEXT): return "DisjointEXT";
        case(BlendOverlapEXT::ConjointEXT): return "ConjointEXT";
        default: return "UNKNOWN";
    }
}
#if defined(VK_USE_PLATFORM_WIN32_KHR)
inline const char * to_string(FullScreenExclusiveEXT val) {
    switch(val) {
        case(FullScreenExclusiveEXT::DefaultEXT): return "DefaultEXT";
        case(FullScreenExclusiveEXT::AllowedEXT): return "AllowedEXT";
        case(FullScreenExclusiveEXT::DisallowedEXT): return "DisallowedEXT";
        case(FullScreenExclusiveEXT::ApplicationControlledEXT): return "ApplicationControlledEXT";
        default: return "UNKNOWN";
    }
}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
inline const char * to_string(ShaderFloatControlsIndependence val) {
    switch(val) {
        case(ShaderFloatControlsIndependence::e32BitOnly): return "e32BitOnly";
        case(ShaderFloatControlsIndependence::All): return "All";
        case(ShaderFloatControlsIndependence::None): return "None";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(FragmentShadingRateCombinerOpKHR val) {
    switch(val) {
        case(FragmentShadingRateCombinerOpKHR::KeepKHR): return "KeepKHR";
        case(FragmentShadingRateCombinerOpKHR::ReplaceKHR): return "ReplaceKHR";
        case(FragmentShadingRateCombinerOpKHR::MinKHR): return "MinKHR";
        case(FragmentShadingRateCombinerOpKHR::MaxKHR): return "MaxKHR";
        case(FragmentShadingRateCombinerOpKHR::MulKHR): return "MulKHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(VendorId val) {
    switch(val) {
        case(VendorId::VIV): return "VIV";
        case(VendorId::VSI): return "VSI";
        case(VendorId::Kazan): return "Kazan";
        case(VendorId::Codeplay): return "Codeplay";
        case(VendorId::MESA): return "MESA";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(DriverId val) {
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
inline const char * to_string(ShadingRatePaletteEntryNV val) {
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
inline const char * to_string(CoarseSampleOrderTypeNV val) {
    switch(val) {
        case(CoarseSampleOrderTypeNV::DefaultNV): return "DefaultNV";
        case(CoarseSampleOrderTypeNV::CustomNV): return "CustomNV";
        case(CoarseSampleOrderTypeNV::PixelMajorNV): return "PixelMajorNV";
        case(CoarseSampleOrderTypeNV::SampleMajorNV): return "SampleMajorNV";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PipelineExecutableStatisticFormatKHR val) {
    switch(val) {
        case(PipelineExecutableStatisticFormatKHR::Bool32KHR): return "Bool32KHR";
        case(PipelineExecutableStatisticFormatKHR::Int64KHR): return "Int64KHR";
        case(PipelineExecutableStatisticFormatKHR::Uint64KHR): return "Uint64KHR";
        case(PipelineExecutableStatisticFormatKHR::Float64KHR): return "Float64KHR";
        default: return "UNKNOWN";
    }
}
inline const char * to_string(PipelineCacheCreateFlagBits val) {
    switch(val) {
        case(PipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT): return "ExternallySynchronizedBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCacheCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT) out += "ExternallySynchronizedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(QueueFlagBits val) {
    switch(val) {
        case(QueueFlagBits::Graphics): return "Graphics";
        case(QueueFlagBits::Compute): return "Compute";
        case(QueueFlagBits::Transfer): return "Transfer";
        case(QueueFlagBits::SparseBinding): return "SparseBinding";
        case(QueueFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(QueueFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueueFlagBits::Graphics) out += "Graphics | ";
    if (flag & QueueFlagBits::Compute) out += "Compute | ";
    if (flag & QueueFlagBits::Transfer) out += "Transfer | ";
    if (flag & QueueFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & QueueFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CullModeFlagBits val) {
    switch(val) {
        case(CullModeFlagBits::None): return "None";
        case(CullModeFlagBits::Front): return "Front";
        case(CullModeFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CullModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CullModeFlagBits::None) out += "None | ";
    if (flag & CullModeFlagBits::Front) out += "Front | ";
    if (flag & CullModeFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(RenderPassCreateFlagBits val) {
    switch(val) {
        case(RenderPassCreateFlagBits::TransformBitQCOM): return "TransformBitQCOM";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(RenderPassCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & RenderPassCreateFlagBits::TransformBitQCOM) out += "TransformBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DeviceQueueCreateFlagBits val) {
    switch(val) {
        case(DeviceQueueCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DeviceQueueCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceQueueCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(MemoryPropertyFlagBits val) {
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
inline std::string to_string(MemoryPropertyFlags flag){
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
inline const char * to_string(MemoryHeapFlagBits val) {
    switch(val) {
        case(MemoryHeapFlagBits::DeviceLocal): return "DeviceLocal";
        case(MemoryHeapFlagBits::MultiInstance): return "MultiInstance";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(MemoryHeapFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryHeapFlagBits::DeviceLocal) out += "DeviceLocal | ";
    if (flag & MemoryHeapFlagBits::MultiInstance) out += "MultiInstance | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(AccessFlagBits val) {
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
inline std::string to_string(AccessFlags flag){
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
inline const char * to_string(BufferUsageFlagBits val) {
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
        case(BufferUsageFlagBits::AccelerationStructureBuildInputReadOnlyBitKHR): return "AccelerationStructureBuildInputReadOnlyBitKHR";
        case(BufferUsageFlagBits::AccelerationStructureStorageBitKHR): return "AccelerationStructureStorageBitKHR";
        case(BufferUsageFlagBits::ShaderBindingTableBitKHR): return "ShaderBindingTableBitKHR";
        case(BufferUsageFlagBits::ShaderDeviceAddress): return "ShaderDeviceAddress";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(BufferUsageFlags flag){
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
    if (flag & BufferUsageFlagBits::AccelerationStructureBuildInputReadOnlyBitKHR) out += "AccelerationStructureBuildInputReadOnlyBitKHR | ";
    if (flag & BufferUsageFlagBits::AccelerationStructureStorageBitKHR) out += "AccelerationStructureStorageBitKHR | ";
    if (flag & BufferUsageFlagBits::ShaderBindingTableBitKHR) out += "ShaderBindingTableBitKHR | ";
    if (flag & BufferUsageFlagBits::ShaderDeviceAddress) out += "ShaderDeviceAddress | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(BufferCreateFlagBits val) {
    switch(val) {
        case(BufferCreateFlagBits::SparseBinding): return "SparseBinding";
        case(BufferCreateFlagBits::SparseResidency): return "SparseResidency";
        case(BufferCreateFlagBits::SparseAliased): return "SparseAliased";
        case(BufferCreateFlagBits::Protected): return "Protected";
        case(BufferCreateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(BufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BufferCreateFlagBits::SparseBinding) out += "SparseBinding | ";
    if (flag & BufferCreateFlagBits::SparseResidency) out += "SparseResidency | ";
    if (flag & BufferCreateFlagBits::SparseAliased) out += "SparseAliased | ";
    if (flag & BufferCreateFlagBits::Protected) out += "Protected | ";
    if (flag & BufferCreateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ShaderStageFlagBits val) {
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
inline std::string to_string(ShaderStageFlags flag){
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
inline const char * to_string(ImageUsageFlagBits val) {
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
inline std::string to_string(ImageUsageFlags flag){
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
inline const char * to_string(ImageCreateFlagBits val) {
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
inline std::string to_string(ImageCreateFlags flag){
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
inline const char * to_string(ImageViewCreateFlagBits val) {
    switch(val) {
        case(ImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT): return "FragmentDensityMapDynamicBitEXT";
        case(ImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT): return "FragmentDensityMapDeferredBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ImageViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT) out += "FragmentDensityMapDynamicBitEXT | ";
    if (flag & ImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT) out += "FragmentDensityMapDeferredBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SamplerCreateFlagBits val) {
    switch(val) {
        case(SamplerCreateFlagBits::SubsampledBitEXT): return "SubsampledBitEXT";
        case(SamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT): return "SubsampledCoarseReconstructionBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SamplerCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SamplerCreateFlagBits::SubsampledBitEXT) out += "SubsampledBitEXT | ";
    if (flag & SamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT) out += "SubsampledCoarseReconstructionBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PipelineCreateFlagBits val) {
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
        case(PipelineCreateFlagBits::RayTracingShaderGroupHandleCaptureReplayBitKHR): return "RayTracingShaderGroupHandleCaptureReplayBitKHR";
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
inline std::string to_string(PipelineCreateFlags flag){
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
    if (flag & PipelineCreateFlagBits::RayTracingShaderGroupHandleCaptureReplayBitKHR) out += "RayTracingShaderGroupHandleCaptureReplayBitKHR | ";
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
inline const char * to_string(PipelineShaderStageCreateFlagBits val) {
    switch(val) {
        case(PipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT): return "AllowVaryingSubgroupSizeBitEXT";
        case(PipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT): return "RequireFullSubgroupsBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineShaderStageCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT) out += "AllowVaryingSubgroupSizeBitEXT | ";
    if (flag & PipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT) out += "RequireFullSubgroupsBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ColorComponentFlagBits val) {
    switch(val) {
        case(ColorComponentFlagBits::R): return "R";
        case(ColorComponentFlagBits::G): return "G";
        case(ColorComponentFlagBits::B): return "B";
        case(ColorComponentFlagBits::A): return "A";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ColorComponentFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ColorComponentFlagBits::R) out += "R | ";
    if (flag & ColorComponentFlagBits::G) out += "G | ";
    if (flag & ColorComponentFlagBits::B) out += "B | ";
    if (flag & ColorComponentFlagBits::A) out += "A | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(FenceCreateFlagBits val) {
    switch(val) {
        case(FenceCreateFlagBits::Signaled): return "Signaled";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(FenceCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceCreateFlagBits::Signaled) out += "Signaled | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(FormatFeatureFlagBits val) {
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
        case(FormatFeatureFlagBits::FragmentShadingRateAttachmentBitKHR): return "FragmentShadingRateAttachmentBitKHR";
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
inline std::string to_string(FormatFeatureFlags flag){
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
    if (flag & FormatFeatureFlagBits::FragmentShadingRateAttachmentBitKHR) out += "FragmentShadingRateAttachmentBitKHR | ";
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
inline const char * to_string(QueryControlFlagBits val) {
    switch(val) {
        case(QueryControlFlagBits::Precise): return "Precise";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(QueryControlFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryControlFlagBits::Precise) out += "Precise | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(QueryResultFlagBits val) {
    switch(val) {
        case(QueryResultFlagBits::e64): return "e64";
        case(QueryResultFlagBits::Wait): return "Wait";
        case(QueryResultFlagBits::WithAvailability): return "WithAvailability";
        case(QueryResultFlagBits::Partial): return "Partial";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(QueryResultFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & QueryResultFlagBits::e64) out += "e64 | ";
    if (flag & QueryResultFlagBits::Wait) out += "Wait | ";
    if (flag & QueryResultFlagBits::WithAvailability) out += "WithAvailability | ";
    if (flag & QueryResultFlagBits::Partial) out += "Partial | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CommandBufferUsageFlagBits val) {
    switch(val) {
        case(CommandBufferUsageFlagBits::OneTimeSubmit): return "OneTimeSubmit";
        case(CommandBufferUsageFlagBits::RenderPassContinue): return "RenderPassContinue";
        case(CommandBufferUsageFlagBits::SimultaneousUse): return "SimultaneousUse";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CommandBufferUsageFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferUsageFlagBits::OneTimeSubmit) out += "OneTimeSubmit | ";
    if (flag & CommandBufferUsageFlagBits::RenderPassContinue) out += "RenderPassContinue | ";
    if (flag & CommandBufferUsageFlagBits::SimultaneousUse) out += "SimultaneousUse | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(QueryPipelineStatisticFlagBits val) {
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
inline std::string to_string(QueryPipelineStatisticFlags flag){
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
inline const char * to_string(ImageAspectFlagBits val) {
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
inline std::string to_string(ImageAspectFlags flag){
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
inline const char * to_string(SparseImageFormatFlagBits val) {
    switch(val) {
        case(SparseImageFormatFlagBits::SingleMiptail): return "SingleMiptail";
        case(SparseImageFormatFlagBits::AlignedMipSize): return "AlignedMipSize";
        case(SparseImageFormatFlagBits::NonstandardBlockSize): return "NonstandardBlockSize";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SparseImageFormatFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseImageFormatFlagBits::SingleMiptail) out += "SingleMiptail | ";
    if (flag & SparseImageFormatFlagBits::AlignedMipSize) out += "AlignedMipSize | ";
    if (flag & SparseImageFormatFlagBits::NonstandardBlockSize) out += "NonstandardBlockSize | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SparseMemoryBindFlagBits val) {
    switch(val) {
        case(SparseMemoryBindFlagBits::Metadata): return "Metadata";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SparseMemoryBindFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SparseMemoryBindFlagBits::Metadata) out += "Metadata | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PipelineStageFlagBits val) {
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
        case(PipelineStageFlagBits::AccelerationStructureBuildBitKHR): return "AccelerationStructureBuildBitKHR";
        case(PipelineStageFlagBits::RayTracingShaderBitKHR): return "RayTracingShaderBitKHR";
        case(PipelineStageFlagBits::ShadingRateImageBitNV): return "ShadingRateImageBitNV";
        case(PipelineStageFlagBits::TaskShaderBitNV): return "TaskShaderBitNV";
        case(PipelineStageFlagBits::MeshShaderBitNV): return "MeshShaderBitNV";
        case(PipelineStageFlagBits::FragmentDensityProcessBitEXT): return "FragmentDensityProcessBitEXT";
        case(PipelineStageFlagBits::CommandPreprocessBitNV): return "CommandPreprocessBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineStageFlags flag){
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
    if (flag & PipelineStageFlagBits::AccelerationStructureBuildBitKHR) out += "AccelerationStructureBuildBitKHR | ";
    if (flag & PipelineStageFlagBits::RayTracingShaderBitKHR) out += "RayTracingShaderBitKHR | ";
    if (flag & PipelineStageFlagBits::ShadingRateImageBitNV) out += "ShadingRateImageBitNV | ";
    if (flag & PipelineStageFlagBits::TaskShaderBitNV) out += "TaskShaderBitNV | ";
    if (flag & PipelineStageFlagBits::MeshShaderBitNV) out += "MeshShaderBitNV | ";
    if (flag & PipelineStageFlagBits::FragmentDensityProcessBitEXT) out += "FragmentDensityProcessBitEXT | ";
    if (flag & PipelineStageFlagBits::CommandPreprocessBitNV) out += "CommandPreprocessBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CommandPoolCreateFlagBits val) {
    switch(val) {
        case(CommandPoolCreateFlagBits::Transient): return "Transient";
        case(CommandPoolCreateFlagBits::ResetCommandBuffer): return "ResetCommandBuffer";
        case(CommandPoolCreateFlagBits::Protected): return "Protected";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CommandPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolCreateFlagBits::Transient) out += "Transient | ";
    if (flag & CommandPoolCreateFlagBits::ResetCommandBuffer) out += "ResetCommandBuffer | ";
    if (flag & CommandPoolCreateFlagBits::Protected) out += "Protected | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CommandPoolResetFlagBits val) {
    switch(val) {
        case(CommandPoolResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CommandPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandPoolResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CommandBufferResetFlagBits val) {
    switch(val) {
        case(CommandBufferResetFlagBits::ReleaseResources): return "ReleaseResources";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CommandBufferResetFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CommandBufferResetFlagBits::ReleaseResources) out += "ReleaseResources | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SampleCountFlagBits val) {
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
inline std::string to_string(SampleCountFlags flag){
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
inline const char * to_string(AttachmentDescriptionFlagBits val) {
    switch(val) {
        case(AttachmentDescriptionFlagBits::MayAlias): return "MayAlias";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(AttachmentDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AttachmentDescriptionFlagBits::MayAlias) out += "MayAlias | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(StencilFaceFlagBits val) {
    switch(val) {
        case(StencilFaceFlagBits::Front): return "Front";
        case(StencilFaceFlagBits::Back): return "Back";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(StencilFaceFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & StencilFaceFlagBits::Front) out += "Front | ";
    if (flag & StencilFaceFlagBits::Back) out += "Back | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DescriptorPoolCreateFlagBits val) {
    switch(val) {
        case(DescriptorPoolCreateFlagBits::FreeDescriptorSet): return "FreeDescriptorSet";
        case(DescriptorPoolCreateFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DescriptorPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorPoolCreateFlagBits::FreeDescriptorSet) out += "FreeDescriptorSet | ";
    if (flag & DescriptorPoolCreateFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DependencyFlagBits val) {
    switch(val) {
        case(DependencyFlagBits::ByRegion): return "ByRegion";
        case(DependencyFlagBits::DeviceGroup): return "DeviceGroup";
        case(DependencyFlagBits::ViewLocal): return "ViewLocal";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DependencyFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DependencyFlagBits::ByRegion) out += "ByRegion | ";
    if (flag & DependencyFlagBits::DeviceGroup) out += "DeviceGroup | ";
    if (flag & DependencyFlagBits::ViewLocal) out += "ViewLocal | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SemaphoreWaitFlagBits val) {
    switch(val) {
        case(SemaphoreWaitFlagBits::Any): return "Any";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SemaphoreWaitFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreWaitFlagBits::Any) out += "Any | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DisplayPlaneAlphaFlagBitsKHR val) {
    switch(val) {
        case(DisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR): return "GlobalBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR): return "PerPixelBitKHR";
        case(DisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR): return "PerPixelPremultipliedBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DisplayPlaneAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR) out += "GlobalBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR) out += "PerPixelBitKHR | ";
    if (flag & DisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR) out += "PerPixelPremultipliedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(CompositeAlphaFlagBitsKHR val) {
    switch(val) {
        case(CompositeAlphaFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(CompositeAlphaFlagBitsKHR::PreMultipliedBitKHR): return "PreMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::PostMultipliedBitKHR): return "PostMultipliedBitKHR";
        case(CompositeAlphaFlagBitsKHR::InheritBitKHR): return "InheritBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CompositeAlphaFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & CompositeAlphaFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::PreMultipliedBitKHR) out += "PreMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::PostMultipliedBitKHR) out += "PostMultipliedBitKHR | ";
    if (flag & CompositeAlphaFlagBitsKHR::InheritBitKHR) out += "InheritBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SurfaceTransformFlagBitsKHR val) {
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
inline std::string to_string(SurfaceTransformFlagsKHR flag){
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
inline const char * to_string(DebugReportFlagBitsEXT val) {
    switch(val) {
        case(DebugReportFlagBitsEXT::InformationBitEXT): return "InformationBitEXT";
        case(DebugReportFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(DebugReportFlagBitsEXT::PerformanceWarningBitEXT): return "PerformanceWarningBitEXT";
        case(DebugReportFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        case(DebugReportFlagBitsEXT::DebugBitEXT): return "DebugBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DebugReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugReportFlagBitsEXT::InformationBitEXT) out += "InformationBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::PerformanceWarningBitEXT) out += "PerformanceWarningBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    if (flag & DebugReportFlagBitsEXT::DebugBitEXT) out += "DebugBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalMemoryHandleTypeFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV): return "OpaqueWin32BitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV): return "OpaqueWin32KmtBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV): return "D3D11ImageBitNV";
        case(ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV): return "D3D11ImageKmtBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalMemoryHandleTypeFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV) out += "OpaqueWin32BitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV) out += "OpaqueWin32KmtBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV) out += "D3D11ImageBitNV | ";
    if (flag & ExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV) out += "D3D11ImageKmtBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalMemoryFeatureFlagBitsNV val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV): return "DedicatedOnlyBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::ExportableBitNV): return "ExportableBitNV";
        case(ExternalMemoryFeatureFlagBitsNV::ImportableBitNV): return "ImportableBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalMemoryFeatureFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV) out += "DedicatedOnlyBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::ExportableBitNV) out += "ExportableBitNV | ";
    if (flag & ExternalMemoryFeatureFlagBitsNV::ImportableBitNV) out += "ImportableBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SubgroupFeatureFlagBits val) {
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
inline std::string to_string(SubgroupFeatureFlags flag){
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
inline const char * to_string(IndirectCommandsLayoutUsageFlagBitsNV val) {
    switch(val) {
        case(IndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV): return "ExplicitPreprocessBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV): return "IndexedSequencesBitNV";
        case(IndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV): return "UnorderedSequencesBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(IndirectCommandsLayoutUsageFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV) out += "ExplicitPreprocessBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV) out += "IndexedSequencesBitNV | ";
    if (flag & IndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV) out += "UnorderedSequencesBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(IndirectStateFlagBitsNV val) {
    switch(val) {
        case(IndirectStateFlagBitsNV::FlagFrontfaceBitNV): return "FlagFrontfaceBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(IndirectStateFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & IndirectStateFlagBitsNV::FlagFrontfaceBitNV) out += "FlagFrontfaceBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PrivateDataSlotCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PrivateDataSlotCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DescriptorSetLayoutCreateFlagBits val) {
    switch(val) {
        case(DescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR): return "PushDescriptorBitKHR";
        case(DescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool): return "UpdateAfterBindPool";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DescriptorSetLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR) out += "PushDescriptorBitKHR | ";
    if (flag & DescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool) out += "UpdateAfterBindPool | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalMemoryHandleTypeFlagBits val) {
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
inline std::string to_string(ExternalMemoryHandleTypeFlags flag){
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
inline const char * to_string(ExternalMemoryFeatureFlagBits val) {
    switch(val) {
        case(ExternalMemoryFeatureFlagBits::DedicatedOnly): return "DedicatedOnly";
        case(ExternalMemoryFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalMemoryFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalMemoryFeatureFlagBits::DedicatedOnly) out += "DedicatedOnly | ";
    if (flag & ExternalMemoryFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalMemoryFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalSemaphoreHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(ExternalSemaphoreHandleTypeFlagBits::D3D12Fence): return "D3D12Fence";
        case(ExternalSemaphoreHandleTypeFlagBits::SyncFd): return "SyncFd";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalSemaphoreHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::D3D12Fence) out += "D3D12Fence | ";
    if (flag & ExternalSemaphoreHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalSemaphoreFeatureFlagBits val) {
    switch(val) {
        case(ExternalSemaphoreFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalSemaphoreFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalSemaphoreFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalSemaphoreFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalSemaphoreFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SemaphoreImportFlagBits val) {
    switch(val) {
        case(SemaphoreImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SemaphoreImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SemaphoreImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalFenceHandleTypeFlagBits val) {
    switch(val) {
        case(ExternalFenceHandleTypeFlagBits::OpaqueFd): return "OpaqueFd";
        case(ExternalFenceHandleTypeFlagBits::OpaqueWin32): return "OpaqueWin32";
        case(ExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt): return "OpaqueWin32Kmt";
        case(ExternalFenceHandleTypeFlagBits::SyncFd): return "SyncFd";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalFenceHandleTypeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueFd) out += "OpaqueFd | ";
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueWin32) out += "OpaqueWin32 | ";
    if (flag & ExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt) out += "OpaqueWin32Kmt | ";
    if (flag & ExternalFenceHandleTypeFlagBits::SyncFd) out += "SyncFd | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ExternalFenceFeatureFlagBits val) {
    switch(val) {
        case(ExternalFenceFeatureFlagBits::Exportable): return "Exportable";
        case(ExternalFenceFeatureFlagBits::Importable): return "Importable";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ExternalFenceFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ExternalFenceFeatureFlagBits::Exportable) out += "Exportable | ";
    if (flag & ExternalFenceFeatureFlagBits::Importable) out += "Importable | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(FenceImportFlagBits val) {
    switch(val) {
        case(FenceImportFlagBits::Temporary): return "Temporary";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(FenceImportFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FenceImportFlagBits::Temporary) out += "Temporary | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SurfaceCounterFlagBitsEXT val) {
    switch(val) {
        case(SurfaceCounterFlagBitsEXT::VblankBitEXT): return "VblankBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SurfaceCounterFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SurfaceCounterFlagBitsEXT::VblankBitEXT) out += "VblankBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PeerMemoryFeatureFlagBits val) {
    switch(val) {
        case(PeerMemoryFeatureFlagBits::CopySrc): return "CopySrc";
        case(PeerMemoryFeatureFlagBits::CopyDst): return "CopyDst";
        case(PeerMemoryFeatureFlagBits::GenericSrc): return "GenericSrc";
        case(PeerMemoryFeatureFlagBits::GenericDst): return "GenericDst";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PeerMemoryFeatureFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PeerMemoryFeatureFlagBits::CopySrc) out += "CopySrc | ";
    if (flag & PeerMemoryFeatureFlagBits::CopyDst) out += "CopyDst | ";
    if (flag & PeerMemoryFeatureFlagBits::GenericSrc) out += "GenericSrc | ";
    if (flag & PeerMemoryFeatureFlagBits::GenericDst) out += "GenericDst | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(MemoryAllocateFlagBits val) {
    switch(val) {
        case(MemoryAllocateFlagBits::DeviceMask): return "DeviceMask";
        case(MemoryAllocateFlagBits::DeviceAddress): return "DeviceAddress";
        case(MemoryAllocateFlagBits::DeviceAddressCaptureReplay): return "DeviceAddressCaptureReplay";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(MemoryAllocateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & MemoryAllocateFlagBits::DeviceMask) out += "DeviceMask | ";
    if (flag & MemoryAllocateFlagBits::DeviceAddress) out += "DeviceAddress | ";
    if (flag & MemoryAllocateFlagBits::DeviceAddressCaptureReplay) out += "DeviceAddressCaptureReplay | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DeviceGroupPresentModeFlagBitsKHR val) {
    switch(val) {
        case(DeviceGroupPresentModeFlagBitsKHR::LocalBitKHR): return "LocalBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR): return "RemoteBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::SumBitKHR): return "SumBitKHR";
        case(DeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR): return "LocalMultiDeviceBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DeviceGroupPresentModeFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceGroupPresentModeFlagBitsKHR::LocalBitKHR) out += "LocalBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR) out += "RemoteBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::SumBitKHR) out += "SumBitKHR | ";
    if (flag & DeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR) out += "LocalMultiDeviceBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SwapchainCreateFlagBitsKHR val) {
    switch(val) {
        case(SwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR): return "SplitInstanceBindRegionsBitKHR";
        case(SwapchainCreateFlagBitsKHR::ProtectedBitKHR): return "ProtectedBitKHR";
        case(SwapchainCreateFlagBitsKHR::MutableFormatBitKHR): return "MutableFormatBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SwapchainCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR) out += "SplitInstanceBindRegionsBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::ProtectedBitKHR) out += "ProtectedBitKHR | ";
    if (flag & SwapchainCreateFlagBitsKHR::MutableFormatBitKHR) out += "MutableFormatBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(SubpassDescriptionFlagBits val) {
    switch(val) {
        case(SubpassDescriptionFlagBits::PerViewAttributesBitNVX): return "PerViewAttributesBitNVX";
        case(SubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX): return "PerViewPositionXOnlyBitNVX";
        case(SubpassDescriptionFlagBits::FragmentRegionBitQCOM): return "FragmentRegionBitQCOM";
        case(SubpassDescriptionFlagBits::ShaderResolveBitQCOM): return "ShaderResolveBitQCOM";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SubpassDescriptionFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & SubpassDescriptionFlagBits::PerViewAttributesBitNVX) out += "PerViewAttributesBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX) out += "PerViewPositionXOnlyBitNVX | ";
    if (flag & SubpassDescriptionFlagBits::FragmentRegionBitQCOM) out += "FragmentRegionBitQCOM | ";
    if (flag & SubpassDescriptionFlagBits::ShaderResolveBitQCOM) out += "ShaderResolveBitQCOM | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DebugUtilsMessageSeverityFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT): return "VerboseBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT): return "InfoBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT): return "WarningBitEXT";
        case(DebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT): return "ErrorBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DebugUtilsMessageSeverityFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT) out += "VerboseBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT) out += "InfoBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT) out += "WarningBitEXT | ";
    if (flag & DebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT) out += "ErrorBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DebugUtilsMessageTypeFlagBitsEXT val) {
    switch(val) {
        case(DebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT): return "GeneralBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT): return "ValidationBitEXT";
        case(DebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT): return "PerformanceBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DebugUtilsMessageTypeFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT) out += "GeneralBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT) out += "ValidationBitEXT | ";
    if (flag & DebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT) out += "PerformanceBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DescriptorBindingFlagBits val) {
    switch(val) {
        case(DescriptorBindingFlagBits::UpdateAfterBind): return "UpdateAfterBind";
        case(DescriptorBindingFlagBits::UpdateUnusedWhilePending): return "UpdateUnusedWhilePending";
        case(DescriptorBindingFlagBits::PartiallyBound): return "PartiallyBound";
        case(DescriptorBindingFlagBits::VariableDescriptorCount): return "VariableDescriptorCount";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DescriptorBindingFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DescriptorBindingFlagBits::UpdateAfterBind) out += "UpdateAfterBind | ";
    if (flag & DescriptorBindingFlagBits::UpdateUnusedWhilePending) out += "UpdateUnusedWhilePending | ";
    if (flag & DescriptorBindingFlagBits::PartiallyBound) out += "PartiallyBound | ";
    if (flag & DescriptorBindingFlagBits::VariableDescriptorCount) out += "VariableDescriptorCount | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ConditionalRenderingFlagBitsEXT val) {
    switch(val) {
        case(ConditionalRenderingFlagBitsEXT::InvertedBitEXT): return "InvertedBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ConditionalRenderingFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ConditionalRenderingFlagBitsEXT::InvertedBitEXT) out += "InvertedBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ResolveModeFlagBits val) {
    switch(val) {
        case(ResolveModeFlagBits::None): return "None";
        case(ResolveModeFlagBits::SampleZero): return "SampleZero";
        case(ResolveModeFlagBits::Average): return "Average";
        case(ResolveModeFlagBits::Min): return "Min";
        case(ResolveModeFlagBits::Max): return "Max";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ResolveModeFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & ResolveModeFlagBits::None) out += "None | ";
    if (flag & ResolveModeFlagBits::SampleZero) out += "SampleZero | ";
    if (flag & ResolveModeFlagBits::Average) out += "Average | ";
    if (flag & ResolveModeFlagBits::Min) out += "Min | ";
    if (flag & ResolveModeFlagBits::Max) out += "Max | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(GeometryInstanceFlagBitsKHR val) {
    switch(val) {
        case(GeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR): return "TriangleFacingCullDisableBitKHR";
        case(GeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR): return "TriangleFrontCounterclockwiseBitKHR";
        case(GeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR): return "ForceOpaqueBitKHR";
        case(GeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR): return "ForceNoOpaqueBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(GeometryInstanceFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR) out += "TriangleFacingCullDisableBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR) out += "TriangleFrontCounterclockwiseBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR) out += "ForceOpaqueBitKHR | ";
    if (flag & GeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR) out += "ForceNoOpaqueBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(GeometryFlagBitsKHR val) {
    switch(val) {
        case(GeometryFlagBitsKHR::OpaqueBitKHR): return "OpaqueBitKHR";
        case(GeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR): return "NoDuplicateAnyHitInvocationBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(GeometryFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & GeometryFlagBitsKHR::OpaqueBitKHR) out += "OpaqueBitKHR | ";
    if (flag & GeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR) out += "NoDuplicateAnyHitInvocationBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(BuildAccelerationStructureFlagBitsKHR val) {
    switch(val) {
        case(BuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR): return "AllowUpdateBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR): return "AllowCompactionBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR): return "PreferFastTraceBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR): return "PreferFastBuildBitKHR";
        case(BuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR): return "LowMemoryBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(BuildAccelerationStructureFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & BuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR) out += "AllowUpdateBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR) out += "AllowCompactionBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR) out += "PreferFastTraceBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR) out += "PreferFastBuildBitKHR | ";
    if (flag & BuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR) out += "LowMemoryBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(AccelerationStructureCreateFlagBitsKHR val) {
    switch(val) {
        case(AccelerationStructureCreateFlagBitsKHR::DeviceAddressCaptureReplayBitKHR): return "DeviceAddressCaptureReplayBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(AccelerationStructureCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & AccelerationStructureCreateFlagBitsKHR::DeviceAddressCaptureReplayBitKHR) out += "DeviceAddressCaptureReplayBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(FramebufferCreateFlagBits val) {
    switch(val) {
        case(FramebufferCreateFlagBits::Imageless): return "Imageless";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(FramebufferCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & FramebufferCreateFlagBits::Imageless) out += "Imageless | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(DeviceDiagnosticsConfigFlagBitsNV val) {
    switch(val) {
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV): return "EnableShaderDebugInfoBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV): return "EnableResourceTrackingBitNV";
        case(DeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV): return "EnableAutomaticCheckpointsBitNV";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DeviceDiagnosticsConfigFlagsNV flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV) out += "EnableShaderDebugInfoBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV) out += "EnableResourceTrackingBitNV | ";
    if (flag & DeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV) out += "EnableAutomaticCheckpointsBitNV | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PipelineCreationFeedbackFlagBitsEXT val) {
    switch(val) {
        case(PipelineCreationFeedbackFlagBitsEXT::ValidBitEXT): return "ValidBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT): return "ApplicationPipelineCacheHitBitEXT";
        case(PipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT): return "BasePipelineAccelerationBitEXT";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCreationFeedbackFlagsEXT flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PipelineCreationFeedbackFlagBitsEXT::ValidBitEXT) out += "ValidBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT) out += "ApplicationPipelineCacheHitBitEXT | ";
    if (flag & PipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT) out += "BasePipelineAccelerationBitEXT | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PerformanceCounterDescriptionFlagBitsKHR val) {
    switch(val) {
        case(PerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingBitKHR): return "PerformanceImpactingBitKHR";
        case(PerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedBitKHR): return "ConcurrentlyImpactedBitKHR";
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PerformanceCounterDescriptionFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingBitKHR) out += "PerformanceImpactingBitKHR | ";
    if (flag & PerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedBitKHR) out += "ConcurrentlyImpactedBitKHR | ";
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(AcquireProfilingLockFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(AcquireProfilingLockFlagsKHR flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ShaderCorePropertiesFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ShaderCorePropertiesFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ShaderModuleCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ShaderModuleCreateFlags flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(PipelineCompilerControlFlagBitsAMD val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCompilerControlFlagsAMD flag){
    if (flag.flags == 0) return "None";
    std::string out;
    return out.substr(0, out.size() - 3);
}
inline const char * to_string(ToolPurposeFlagBitsEXT val) {
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
inline std::string to_string(ToolPurposeFlagsEXT flag){
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
inline const char * to_string(QueryPoolCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(QueryPoolCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineLayoutCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineLayoutCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineDepthStencilStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineDepthStencilStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineDynamicStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineDynamicStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineColorBlendStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineColorBlendStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineMultisampleStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineMultisampleStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineRasterizationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineRasterizationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineViewportStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineViewportStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineTessellationStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineTessellationStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineInputAssemblyStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineInputAssemblyStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineVertexInputStateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineVertexInputStateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(BufferViewCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(BufferViewCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(InstanceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(InstanceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DeviceCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DeviceCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(SemaphoreCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(SemaphoreCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(EventCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(EventCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(MemoryMapFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(MemoryMapFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DescriptorPoolResetFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DescriptorPoolResetFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DescriptorUpdateTemplateCreateFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DescriptorUpdateTemplateCreateFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DisplayModeCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DisplayModeCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DisplaySurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DisplaySurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
inline const char * to_string(AndroidSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(AndroidSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
inline const char * to_string(ViSurfaceCreateFlagBitsNN val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ViSurfaceCreateFlagsNN flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
inline const char * to_string(WaylandSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(WaylandSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
inline const char * to_string(Win32SurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(Win32SurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
inline const char * to_string(XlibSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(XlibSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
inline const char * to_string(XcbSurfaceCreateFlagBitsKHR val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(XcbSurfaceCreateFlagsKHR flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
inline const char * to_string(DirectFBSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DirectFBSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
inline const char * to_string(IOSSurfaceCreateFlagBitsMVK val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(IOSSurfaceCreateFlagsMVK flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
inline const char * to_string(MacOSSurfaceCreateFlagBitsMVK val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(MacOSSurfaceCreateFlagsMVK flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
inline const char * to_string(MetalSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(MetalSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
inline const char * to_string(ImagePipeSurfaceCreateFlagBitsFUCHSIA val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ImagePipeSurfaceCreateFlagsFUCHSIA flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
inline const char * to_string(StreamDescriptorSurfaceCreateFlagBitsGGP val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(StreamDescriptorSurfaceCreateFlagsGGP flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
#endif // defined(VK_USE_PLATFORM_GGP)
inline const char * to_string(HeadlessSurfaceCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(HeadlessSurfaceCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(CommandPoolTrimFlagBits val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(CommandPoolTrimFlags flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineViewportSwizzleStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineViewportSwizzleStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineDiscardRectangleStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineDiscardRectangleStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineCoverageToColorStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCoverageToColorStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineCoverageModulationStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCoverageModulationStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineCoverageReductionStateCreateFlagBitsNV val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineCoverageReductionStateCreateFlagsNV flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(ValidationCacheCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(ValidationCacheCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DebugUtilsMessengerCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DebugUtilsMessengerCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DebugUtilsMessengerCallbackDataFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DebugUtilsMessengerCallbackDataFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(DeviceMemoryReportFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(DeviceMemoryReportFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineRasterizationConservativeStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineRasterizationConservativeStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineRasterizationStateStreamCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineRasterizationStateStreamCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
inline const char * to_string(PipelineRasterizationDepthClipStateCreateFlagBitsEXT val) {
    switch(val) {
        default: return "UNKNOWN";
    }
}
inline std::string to_string(PipelineRasterizationDepthClipStateCreateFlagsEXT flag){
    if (flag.flags == 0) return "None";
    return "Unknown";
}
} // namespace vk
// clang-format on
