#pragma once
// clang-format off
#include <stdint.h>
#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>

namespace vk {
#define VK_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))
#define VK_VERSION_MAJOR(version) ((uint32_t)(version) >> 22)
#define VK_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3ff)
#define VK_VERSION_PATCH(version) ((uint32_t)(version) & 0xfff)
// DEPRECATED: This define has been removed. Specific version defines (e.g. VK_API_VERSION_1_0), or the VK_MAKE_VERSION macro, should be used instead.
//#define VK_API_VERSION VK_MAKE_VERSION(1, 0, 0) // Patch version should always be set to 0
// Vulkan 1.0 version number
#define VK_API_VERSION_1_0 VK_MAKE_VERSION(1, 0, 0)// Patch version should always be set to 0
// Vulkan 1.1 version number
#define VK_API_VERSION_1_1 VK_MAKE_VERSION(1, 1, 0)// Patch version should always be set to 0
// Vulkan 1.2 version number
#define VK_API_VERSION_1_2 VK_MAKE_VERSION(1, 2, 0)// Patch version should always be set to 0
// Version of this file
#define VK_HEADER_VERSION 135
// Complete version of this file
#define VK_HEADER_VERSION_COMPLETE VK_MAKE_VERSION(1, 2, VK_HEADER_VERSION)

#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;

#if !defined(VK_DEFINE_NON_DISPATCHABLE_HANDLE)
#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T *object;
#else
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object;
#endif
#endif

#define VK_NULL_HANDLE 0
struct ANativeWindow;
struct AHardwareBuffer;

#ifdef __OBJC__
@class CAMetalLayer;
#else
typedef void CAMetalLayer;
#endif
constexpr size_t LOD_CLAMP_NONE = 1000.0f;
constexpr size_t REMAINING_MIP_LEVELS = (~0U);
constexpr size_t REMAINING_ARRAY_LAYERS = (~0U);
constexpr size_t WHOLE_SIZE = (~0ULL);
constexpr size_t ATTACHMENT_UNUSED = (~0U);
constexpr size_t QUEUE_FAMILY_IGNORED = (~0U);
constexpr size_t SUBPASS_EXTERNAL = (~0U);
constexpr size_t MAX_DEVICE_GROUP_SIZE = 32;
constexpr size_t LUID_SIZE = 8;
constexpr size_t QUEUE_FAMILY_EXTERNAL = (~0U-1);
constexpr size_t MAX_DRIVER_NAME_SIZE = 256;
constexpr size_t MAX_DRIVER_INFO_SIZE = 256;
constexpr size_t MAX_PHYSICAL_DEVICE_NAME_SIZE = 256;
constexpr size_t UUID_SIZE = 16;
constexpr auto LUID_SIZE_KHR = LUID_SIZE;
constexpr size_t MAX_EXTENSION_NAME_SIZE = 256;
constexpr size_t MAX_DESCRIPTION_SIZE = 256;
constexpr size_t MAX_MEMORY_TYPES = 32;
constexpr size_t MAX_MEMORY_HEAPS = 16;
constexpr auto QUEUE_FAMILY_EXTERNAL_KHR = QUEUE_FAMILY_EXTERNAL;
constexpr size_t QUEUE_FAMILY_FOREIGN_EXT = (~0U-2);
constexpr auto MAX_DEVICE_GROUP_SIZE_KHR = MAX_DEVICE_GROUP_SIZE;
constexpr auto MAX_DRIVER_NAME_SIZE_KHR = MAX_DRIVER_NAME_SIZE;
constexpr auto MAX_DRIVER_INFO_SIZE_KHR = MAX_DRIVER_INFO_SIZE;
constexpr size_t SHADER_UNUSED_KHR = (~0U);
constexpr auto SHADER_UNUSED_NV = SHADER_UNUSED_KHR;
using SampleMask = uint32_t;
using Bool32 = uint32_t;
using Flags = uint32_t;
using DeviceSize = uint64_t;
using DeviceAddress = uint64_t;
enum class ImageLayout: uint32_t{
    eUndefined = 0,
    eGeneral = 1,
    eColorAttachmentOptimal = 2,
    eDepthStencilAttachmentOptimal = 3,
    eDepthStencilReadOnlyOptimal = 4,
    eShaderReadOnlyOptimal = 5,
    eTransferSrcOptimal = 6,
    eTransferDstOptimal = 7,
    ePreinitialized = 8,
    ePresentSrcKHR = 1000001002,
    eSharedPresentKHR = 1000111000,
    eShadingRateOptimalNV = 1000164003,
    eFragmentDensityMapOptimalEXT = 1000218000,
    eDepthReadOnlyStencilAttachmentOptimal = 1000117000,
    eDepthAttachmentStencilReadOnlyOptimal = 1000117001,
    eDepthAttachmentOptimal = 1000241000,
    eDepthReadOnlyOptimal = 1000241001,
    eStencilAttachmentOptimal = 1000241002,
    eStencilReadOnlyOptimal = 1000241003,
};
enum class AttachmentLoadOp: uint32_t{
    eLoad = 0,
    eClear = 1,
    eDontCare = 2,
};
enum class AttachmentStoreOp: uint32_t{
    eStore = 0,
    eDontCare = 1,
};
enum class ImageType: uint32_t{
    e1D = 0,
    e2D = 1,
    e3D = 2,
};
enum class ImageTiling: uint32_t{
    eOptimal = 0,
    eLinear = 1,
    eDrmFormatModifierEXT = 1000158000,
};
enum class ImageViewType: uint32_t{
    e1D = 0,
    e2D = 1,
    e3D = 2,
    eCube = 3,
    e1DArray = 4,
    e2DArray = 5,
    eCubeArray = 6,
};
enum class CommandBufferLevel: uint32_t{
    ePrimary = 0,
    eSecondary = 1,
};
enum class ComponentSwizzle: uint32_t{
    eIdentity = 0,
    eZero = 1,
    eOne = 2,
    eR = 3,
    eG = 4,
    eB = 5,
    eA = 6,
};
enum class DescriptorType: uint32_t{
    eSampler = 0,
    eCombinedImageSampler = 1,
    eSampledImage = 2,
    eStorageImage = 3,
    eUniformTexelBuffer = 4,
    eStorageTexelBuffer = 5,
    eUniformBuffer = 6,
    eStorageBuffer = 7,
    eUniformBufferDynamic = 8,
    eStorageBufferDynamic = 9,
    eInputAttachment = 10,
    eInlineUniformBlockEXT = 1000138000,
    eAccelerationStructureKHR = 1000150000,
};
enum class QueryType: uint32_t{
    eOcclusion = 0,
    ePipelineStatistics = 1,
    eTimestamp = 2,
    eReserved8 = 1000023008,
    eReserved4 = 1000024004,
    eTransformFeedbackStreamEXT = 1000028004,
    ePerformanceQueryKHR = 1000116000,
    eAccelerationStructureCompactedSizeKHR = 1000150000,
    eAccelerationStructureSerializationSizeKHR = 1000150000,
    ePerformanceQueryINTEL = 1000210000,
};
enum class BorderColor: uint32_t{
    eFloatTransparentBlack = 0,
    eIntTransparentBlack = 1,
    eFloatOpaqueBlack = 2,
    eIntOpaqueBlack = 3,
    eFloatOpaqueWhite = 4,
    eIntOpaqueWhite = 5,
};
enum class PipelineBindPoint: uint32_t{
    eGraphics = 0,
    eCompute = 1,
    eRayTracingKHR = 1000150000,
};
enum class PipelineCacheHeaderVersion: uint32_t{
    eOne = 1,
};
enum class PrimitiveTopology: uint32_t{
    ePointList = 0,
    eLineList = 1,
    eLineStrip = 2,
    eTriangleList = 3,
    eTriangleStrip = 4,
    eTriangleFan = 5,
    eLineListWithAdjacency = 6,
    eLineStripWithAdjacency = 7,
    eTriangleListWithAdjacency = 8,
    eTriangleStripWithAdjacency = 9,
    ePatchList = 10,
};
enum class SharingMode: uint32_t{
    eExclusive = 0,
    eConcurrent = 1,
};
enum class IndexType: uint32_t{
    eUint16 = 0,
    eUint32 = 1,
    eNoneKHR = 1000150000,
    eUint8EXT = 1000265000,
};
enum class Filter: uint32_t{
    eNearest = 0,
    eLinear = 1,
    eCubicIMG = 1000015000,
};
enum class SamplerMipmapMode: uint32_t{
    eNearest = 0,
    eLinear = 1,
};
enum class SamplerAddressMode: uint32_t{
    eRepeat = 0,
    eMirroredRepeat = 1,
    eClampToEdge = 2,
    eClampToBorder = 3,
    eMirrorClampToEdge = 4,
};
enum class CompareOp: uint32_t{
    eNever = 0,
    eLess = 1,
    eEqual = 2,
    eLessOrEqual = 3,
    eGreater = 4,
    eNotEqual = 5,
    eGreaterOrEqual = 6,
    eAlways = 7,
};
enum class PolygonMode: uint32_t{
    eFill = 0,
    eLine = 1,
    ePoint = 2,
    eFillRectangleNV = 1000153000,
};
enum class FrontFace: uint32_t{
    eCounterClockwise = 0,
    eClockwise = 1,
};
enum class BlendFactor: uint32_t{
    eZero = 0,
    eOne = 1,
    eSrcColor = 2,
    eOneMinusSrcColor = 3,
    eDstColor = 4,
    eOneMinusDstColor = 5,
    eSrcAlpha = 6,
    eOneMinusSrcAlpha = 7,
    eDstAlpha = 8,
    eOneMinusDstAlpha = 9,
    eConstantColor = 10,
    eOneMinusConstantColor = 11,
    eConstantAlpha = 12,
    eOneMinusConstantAlpha = 13,
    eSrcAlphaSaturate = 14,
    eSrc1Color = 15,
    eOneMinusSrc1Color = 16,
    eSrc1Alpha = 17,
    eOneMinusSrc1Alpha = 18,
};
enum class BlendOp: uint32_t{
    eAdd = 0,
    eSubtract = 1,
    eReverseSubtract = 2,
    eMin = 3,
    eMax = 4,
    eZeroEXT = 1000148000,
    eSrcEXT = 1000148001,
    eDstEXT = 1000148002,
    eSrcOverEXT = 1000148003,
    eDstOverEXT = 1000148004,
    eSrcInEXT = 1000148005,
    eDstInEXT = 1000148006,
    eSrcOutEXT = 1000148007,
    eDstOutEXT = 1000148008,
    eSrcAtopEXT = 1000148009,
    eDstAtopEXT = 1000148010,
    eXorEXT = 1000148011,
    eMultiplyEXT = 1000148012,
    eScreenEXT = 1000148013,
    eOverlayEXT = 1000148014,
    eDarkenEXT = 1000148015,
    eLightenEXT = 1000148016,
    eColordodgeEXT = 1000148017,
    eColorburnEXT = 1000148018,
    eHardlightEXT = 1000148019,
    eSoftlightEXT = 1000148020,
    eDifferenceEXT = 1000148021,
    eExclusionEXT = 1000148022,
    eInvertEXT = 1000148023,
    eInvertRgbEXT = 1000148024,
    eLineardodgeEXT = 1000148025,
    eLinearburnEXT = 1000148026,
    eVividlightEXT = 1000148027,
    eLinearlightEXT = 1000148028,
    ePinlightEXT = 1000148029,
    eHardmixEXT = 1000148030,
    eHslHueEXT = 1000148031,
    eHslSaturationEXT = 1000148032,
    eHslColorEXT = 1000148033,
    eHslLuminosityEXT = 1000148034,
    ePlusEXT = 1000148035,
    ePlusClampedEXT = 1000148036,
    ePlusClampedAlphaEXT = 1000148037,
    ePlusDarkerEXT = 1000148038,
    eMinusEXT = 1000148039,
    eMinusClampedEXT = 1000148040,
    eContrastEXT = 1000148041,
    eInvertOvgEXT = 1000148042,
    eRedEXT = 1000148043,
    eGreenEXT = 1000148044,
    eBlueEXT = 1000148045,
};
enum class StencilOp: uint32_t{
    eKeep = 0,
    eZero = 1,
    eReplace = 2,
    eIncrementAndClamp = 3,
    eDecrementAndClamp = 4,
    eInvert = 5,
    eIncrementAndWrap = 6,
    eDecrementAndWrap = 7,
};
enum class LogicOp: uint32_t{
    eClear = 0,
    eAnd = 1,
    eAndReverse = 2,
    eCopy = 3,
    eAndInverted = 4,
    eNoOp = 5,
    eXor = 6,
    eOr = 7,
    eNor = 8,
    eEquivalent = 9,
    eInvert = 10,
    eOrReverse = 11,
    eCopyInverted = 12,
    eOrInverted = 13,
    eNand = 14,
    eSet = 15,
};
enum class InternalAllocationType: uint32_t{
    eExecutable = 0,
};
enum class SystemAllocationScope: uint32_t{
    eCommand = 0,
    eObject = 1,
    eCache = 2,
    eDevice = 3,
    eInstance = 4,
};
enum class PhysicalDeviceType: uint32_t{
    eOther = 0,
    eIntegratedGpu = 1,
    eDiscreteGpu = 2,
    eVirtualGpu = 3,
    eCpu = 4,
};
enum class VertexInputRate: uint32_t{
    eVertex = 0,
    eInstance = 1,
};
enum class Format: uint32_t{
    eUndefined = 0,
    eR4G4UnormPack8 = 1,
    eR4G4B4A4UnormPack16 = 2,
    eB4G4R4A4UnormPack16 = 3,
    eR5G6B5UnormPack16 = 4,
    eB5G6R5UnormPack16 = 5,
    eR5G5B5A1UnormPack16 = 6,
    eB5G5R5A1UnormPack16 = 7,
    eA1R5G5B5UnormPack16 = 8,
    eR8Unorm = 9,
    eR8Snorm = 10,
    eR8Uscaled = 11,
    eR8Sscaled = 12,
    eR8Uint = 13,
    eR8Sint = 14,
    eR8Srgb = 15,
    eR8G8Unorm = 16,
    eR8G8Snorm = 17,
    eR8G8Uscaled = 18,
    eR8G8Sscaled = 19,
    eR8G8Uint = 20,
    eR8G8Sint = 21,
    eR8G8Srgb = 22,
    eR8G8B8Unorm = 23,
    eR8G8B8Snorm = 24,
    eR8G8B8Uscaled = 25,
    eR8G8B8Sscaled = 26,
    eR8G8B8Uint = 27,
    eR8G8B8Sint = 28,
    eR8G8B8Srgb = 29,
    eB8G8R8Unorm = 30,
    eB8G8R8Snorm = 31,
    eB8G8R8Uscaled = 32,
    eB8G8R8Sscaled = 33,
    eB8G8R8Uint = 34,
    eB8G8R8Sint = 35,
    eB8G8R8Srgb = 36,
    eR8G8B8A8Unorm = 37,
    eR8G8B8A8Snorm = 38,
    eR8G8B8A8Uscaled = 39,
    eR8G8B8A8Sscaled = 40,
    eR8G8B8A8Uint = 41,
    eR8G8B8A8Sint = 42,
    eR8G8B8A8Srgb = 43,
    eB8G8R8A8Unorm = 44,
    eB8G8R8A8Snorm = 45,
    eB8G8R8A8Uscaled = 46,
    eB8G8R8A8Sscaled = 47,
    eB8G8R8A8Uint = 48,
    eB8G8R8A8Sint = 49,
    eB8G8R8A8Srgb = 50,
    eA8B8G8R8UnormPack32 = 51,
    eA8B8G8R8SnormPack32 = 52,
    eA8B8G8R8UscaledPack32 = 53,
    eA8B8G8R8SscaledPack32 = 54,
    eA8B8G8R8UintPack32 = 55,
    eA8B8G8R8SintPack32 = 56,
    eA8B8G8R8SrgbPack32 = 57,
    eA2R10G10B10UnormPack32 = 58,
    eA2R10G10B10SnormPack32 = 59,
    eA2R10G10B10UscaledPack32 = 60,
    eA2R10G10B10SscaledPack32 = 61,
    eA2R10G10B10UintPack32 = 62,
    eA2R10G10B10SintPack32 = 63,
    eA2B10G10R10UnormPack32 = 64,
    eA2B10G10R10SnormPack32 = 65,
    eA2B10G10R10UscaledPack32 = 66,
    eA2B10G10R10SscaledPack32 = 67,
    eA2B10G10R10UintPack32 = 68,
    eA2B10G10R10SintPack32 = 69,
    eR16Unorm = 70,
    eR16Snorm = 71,
    eR16Uscaled = 72,
    eR16Sscaled = 73,
    eR16Uint = 74,
    eR16Sint = 75,
    eR16Sfloat = 76,
    eR16G16Unorm = 77,
    eR16G16Snorm = 78,
    eR16G16Uscaled = 79,
    eR16G16Sscaled = 80,
    eR16G16Uint = 81,
    eR16G16Sint = 82,
    eR16G16Sfloat = 83,
    eR16G16B16Unorm = 84,
    eR16G16B16Snorm = 85,
    eR16G16B16Uscaled = 86,
    eR16G16B16Sscaled = 87,
    eR16G16B16Uint = 88,
    eR16G16B16Sint = 89,
    eR16G16B16Sfloat = 90,
    eR16G16B16A16Unorm = 91,
    eR16G16B16A16Snorm = 92,
    eR16G16B16A16Uscaled = 93,
    eR16G16B16A16Sscaled = 94,
    eR16G16B16A16Uint = 95,
    eR16G16B16A16Sint = 96,
    eR16G16B16A16Sfloat = 97,
    eR32Uint = 98,
    eR32Sint = 99,
    eR32Sfloat = 100,
    eR32G32Uint = 101,
    eR32G32Sint = 102,
    eR32G32Sfloat = 103,
    eR32G32B32Uint = 104,
    eR32G32B32Sint = 105,
    eR32G32B32Sfloat = 106,
    eR32G32B32A32Uint = 107,
    eR32G32B32A32Sint = 108,
    eR32G32B32A32Sfloat = 109,
    eR64Uint = 110,
    eR64Sint = 111,
    eR64Sfloat = 112,
    eR64G64Uint = 113,
    eR64G64Sint = 114,
    eR64G64Sfloat = 115,
    eR64G64B64Uint = 116,
    eR64G64B64Sint = 117,
    eR64G64B64Sfloat = 118,
    eR64G64B64A64Uint = 119,
    eR64G64B64A64Sint = 120,
    eR64G64B64A64Sfloat = 121,
    eB10G11R11UfloatPack32 = 122,
    eE5B9G9R9UfloatPack32 = 123,
    eD16Unorm = 124,
    eX8D24UnormPack32 = 125,
    eD32Sfloat = 126,
    eS8Uint = 127,
    eD16UnormS8Uint = 128,
    eD24UnormS8Uint = 129,
    eD32SfloatS8Uint = 130,
    eBc1RgbUnormBlock = 131,
    eBc1RgbSrgbBlock = 132,
    eBc1RgbaUnormBlock = 133,
    eBc1RgbaSrgbBlock = 134,
    eBc2UnormBlock = 135,
    eBc2SrgbBlock = 136,
    eBc3UnormBlock = 137,
    eBc3SrgbBlock = 138,
    eBc4UnormBlock = 139,
    eBc4SnormBlock = 140,
    eBc5UnormBlock = 141,
    eBc5SnormBlock = 142,
    eBc6HUfloatBlock = 143,
    eBc6HSfloatBlock = 144,
    eBc7UnormBlock = 145,
    eBc7SrgbBlock = 146,
    eEtc2R8G8B8UnormBlock = 147,
    eEtc2R8G8B8SrgbBlock = 148,
    eEtc2R8G8B8A1UnormBlock = 149,
    eEtc2R8G8B8A1SrgbBlock = 150,
    eEtc2R8G8B8A8UnormBlock = 151,
    eEtc2R8G8B8A8SrgbBlock = 152,
    eEacR11UnormBlock = 153,
    eEacR11SnormBlock = 154,
    eEacR11G11UnormBlock = 155,
    eEacR11G11SnormBlock = 156,
    eAstc4X4UnormBlock = 157,
    eAstc4X4SrgbBlock = 158,
    eAstc5X4UnormBlock = 159,
    eAstc5X4SrgbBlock = 160,
    eAstc5X5UnormBlock = 161,
    eAstc5X5SrgbBlock = 162,
    eAstc6X5UnormBlock = 163,
    eAstc6X5SrgbBlock = 164,
    eAstc6X6UnormBlock = 165,
    eAstc6X6SrgbBlock = 166,
    eAstc8X5UnormBlock = 167,
    eAstc8X5SrgbBlock = 168,
    eAstc8X6UnormBlock = 169,
    eAstc8X6SrgbBlock = 170,
    eAstc8X8UnormBlock = 171,
    eAstc8X8SrgbBlock = 172,
    eAstc10X5UnormBlock = 173,
    eAstc10X5SrgbBlock = 174,
    eAstc10X6UnormBlock = 175,
    eAstc10X6SrgbBlock = 176,
    eAstc10X8UnormBlock = 177,
    eAstc10X8SrgbBlock = 178,
    eAstc10X10UnormBlock = 179,
    eAstc10X10SrgbBlock = 180,
    eAstc12X10UnormBlock = 181,
    eAstc12X10SrgbBlock = 182,
    eAstc12X12UnormBlock = 183,
    eAstc12X12SrgbBlock = 184,
    ePvrtc12BppUnormBlockIMG = 1000054000,
    ePvrtc14BppUnormBlockIMG = 1000054001,
    ePvrtc22BppUnormBlockIMG = 1000054002,
    ePvrtc24BppUnormBlockIMG = 1000054003,
    ePvrtc12BppSrgbBlockIMG = 1000054004,
    ePvrtc14BppSrgbBlockIMG = 1000054005,
    ePvrtc22BppSrgbBlockIMG = 1000054006,
    ePvrtc24BppSrgbBlockIMG = 1000054007,
    eAstc4X4SfloatBlockEXT = 1000066000,
    eAstc5X4SfloatBlockEXT = 1000066001,
    eAstc5X5SfloatBlockEXT = 1000066002,
    eAstc6X5SfloatBlockEXT = 1000066003,
    eAstc6X6SfloatBlockEXT = 1000066004,
    eAstc8X5SfloatBlockEXT = 1000066005,
    eAstc8X6SfloatBlockEXT = 1000066006,
    eAstc8X8SfloatBlockEXT = 1000066007,
    eAstc10X5SfloatBlockEXT = 1000066008,
    eAstc10X6SfloatBlockEXT = 1000066009,
    eAstc10X8SfloatBlockEXT = 1000066010,
    eAstc10X10SfloatBlockEXT = 1000066011,
    eAstc12X10SfloatBlockEXT = 1000066012,
    eAstc12X12SfloatBlockEXT = 1000066013,
    eG8B8G8R8422Unorm = 1000156000,
    eB8G8R8G8422Unorm = 1000156001,
    eG8B8R83Plane420Unorm = 1000156002,
    eG8B8R82Plane420Unorm = 1000156003,
    eG8B8R83Plane422Unorm = 1000156004,
    eG8B8R82Plane422Unorm = 1000156005,
    eG8B8R83Plane444Unorm = 1000156006,
    eR10X6UnormPack16 = 1000156007,
    eR10X6G10X6Unorm2Pack16 = 1000156008,
    eR10X6G10X6B10X6A10X6Unorm4Pack16 = 1000156009,
    eG10X6B10X6G10X6R10X6422Unorm4Pack16 = 1000156010,
    eB10X6G10X6R10X6G10X6422Unorm4Pack16 = 1000156011,
    eG10X6B10X6R10X63Plane420Unorm3Pack16 = 1000156012,
    eG10X6B10X6R10X62Plane420Unorm3Pack16 = 1000156013,
    eG10X6B10X6R10X63Plane422Unorm3Pack16 = 1000156014,
    eG10X6B10X6R10X62Plane422Unorm3Pack16 = 1000156015,
    eG10X6B10X6R10X63Plane444Unorm3Pack16 = 1000156016,
    eR12X4UnormPack16 = 1000156017,
    eR12X4G12X4Unorm2Pack16 = 1000156018,
    eR12X4G12X4B12X4A12X4Unorm4Pack16 = 1000156019,
    eG12X4B12X4G12X4R12X4422Unorm4Pack16 = 1000156020,
    eB12X4G12X4R12X4G12X4422Unorm4Pack16 = 1000156021,
    eG12X4B12X4R12X43Plane420Unorm3Pack16 = 1000156022,
    eG12X4B12X4R12X42Plane420Unorm3Pack16 = 1000156023,
    eG12X4B12X4R12X43Plane422Unorm3Pack16 = 1000156024,
    eG12X4B12X4R12X42Plane422Unorm3Pack16 = 1000156025,
    eG12X4B12X4R12X43Plane444Unorm3Pack16 = 1000156026,
    eG16B16G16R16422Unorm = 1000156027,
    eB16G16R16G16422Unorm = 1000156028,
    eG16B16R163Plane420Unorm = 1000156029,
    eG16B16R162Plane420Unorm = 1000156030,
    eG16B16R163Plane422Unorm = 1000156031,
    eG16B16R162Plane422Unorm = 1000156032,
    eG16B16R163Plane444Unorm = 1000156033,
};
enum class StructureType: uint32_t{
    eApplicationInfo = 0,
    eInstanceCreateInfo = 1,
    eDeviceQueueCreateInfo = 2,
    eDeviceCreateInfo = 3,
    eSubmitInfo = 4,
    eMemoryAllocateInfo = 5,
    eMappedMemoryRange = 6,
    eBindSparseInfo = 7,
    eFenceCreateInfo = 8,
    eSemaphoreCreateInfo = 9,
    eEventCreateInfo = 10,
    eQueryPoolCreateInfo = 11,
    eBufferCreateInfo = 12,
    eBufferViewCreateInfo = 13,
    eImageCreateInfo = 14,
    eImageViewCreateInfo = 15,
    eShaderModuleCreateInfo = 16,
    ePipelineCacheCreateInfo = 17,
    ePipelineShaderStageCreateInfo = 18,
    ePipelineVertexInputStateCreateInfo = 19,
    ePipelineInputAssemblyStateCreateInfo = 20,
    ePipelineTessellationStateCreateInfo = 21,
    ePipelineViewportStateCreateInfo = 22,
    ePipelineRasterizationStateCreateInfo = 23,
    ePipelineMultisampleStateCreateInfo = 24,
    ePipelineDepthStencilStateCreateInfo = 25,
    ePipelineColorBlendStateCreateInfo = 26,
    ePipelineDynamicStateCreateInfo = 27,
    eGraphicsPipelineCreateInfo = 28,
    eComputePipelineCreateInfo = 29,
    ePipelineLayoutCreateInfo = 30,
    eSamplerCreateInfo = 31,
    eDescriptorSetLayoutCreateInfo = 32,
    eDescriptorPoolCreateInfo = 33,
    eDescriptorSetAllocateInfo = 34,
    eWriteDescriptorSet = 35,
    eCopyDescriptorSet = 36,
    eFramebufferCreateInfo = 37,
    eRenderPassCreateInfo = 38,
    eCommandPoolCreateInfo = 39,
    eCommandBufferAllocateInfo = 40,
    eCommandBufferInheritanceInfo = 41,
    eCommandBufferBeginInfo = 42,
    eRenderPassBeginInfo = 43,
    eBufferMemoryBarrier = 44,
    eImageMemoryBarrier = 45,
    eMemoryBarrier = 46,
    eLoaderInstanceCreateInfo = 47,
    eLoaderDeviceCreateInfo = 48,
    eSwapchainCreateInfoKHR = 1000001000,
    ePresentInfoKHR = 1000001001,
    eDeviceGroupPresentCapabilitiesKHR = 1000001007,
    eImageSwapchainCreateInfoKHR = 1000001008,
    eBindImageMemorySwapchainInfoKHR = 1000001009,
    eAcquireNextImageInfoKHR = 1000001010,
    eDeviceGroupPresentInfoKHR = 1000001011,
    eDeviceGroupSwapchainCreateInfoKHR = 1000001012,
    eDisplayModeCreateInfoKHR = 1000002000,
    eDisplaySurfaceCreateInfoKHR = 1000002001,
    eDisplayPresentInfoKHR = 1000003000,
    eXlibSurfaceCreateInfoKHR = 1000004000,
    eXcbSurfaceCreateInfoKHR = 1000005000,
    eWaylandSurfaceCreateInfoKHR = 1000006000,
    eAndroidSurfaceCreateInfoKHR = 1000008000,
    eWin32SurfaceCreateInfoKHR = 1000009000,
    eNativeBufferANDROID = 1000010000,
    eSwapchainImageCreateInfoANDROID = 1000010001,
    ePhysicalDevicePresentationPropertiesANDROID = 1000010002,
    eDebugReportCallbackCreateInfoEXT = 1000011000,
    ePipelineRasterizationStateRasterizationOrderAMD = 1000018000,
    eDebugMarkerObjectNameInfoEXT = 1000022000,
    eDebugMarkerObjectTagInfoEXT = 1000022001,
    eDebugMarkerMarkerInfoEXT = 1000022002,
    eDedicatedAllocationImageCreateInfoNV = 1000026000,
    eDedicatedAllocationBufferCreateInfoNV = 1000026001,
    eDedicatedAllocationMemoryAllocateInfoNV = 1000026002,
    ePhysicalDeviceTransformFeedbackFeaturesEXT = 1000028000,
    ePhysicalDeviceTransformFeedbackPropertiesEXT = 1000028001,
    ePipelineRasterizationStateStreamCreateInfoEXT = 1000028002,
    eImageViewHandleInfoNVX = 1000030000,
    eTextureLodGatherFormatPropertiesAMD = 1000041000,
    eStreamDescriptorSurfaceCreateInfoGGP = 1000049000,
    ePhysicalDeviceCornerSampledImageFeaturesNV = 1000050000,
    eExternalMemoryImageCreateInfoNV = 1000056000,
    eExportMemoryAllocateInfoNV = 1000056001,
    eImportMemoryWin32HandleInfoNV = 1000057000,
    eExportMemoryWin32HandleInfoNV = 1000057001,
    eWin32KeyedMutexAcquireReleaseInfoNV = 1000058000,
    eDeviceGroupPresentCapabilitiesKHR = 1000060007,
    eImageSwapchainCreateInfoKHR = 1000060008,
    eBindImageMemorySwapchainInfoKHR = 1000060009,
    eAcquireNextImageInfoKHR = 1000060010,
    eDeviceGroupPresentInfoKHR = 1000060011,
    eDeviceGroupSwapchainCreateInfoKHR = 1000060012,
    eValidationFlagsEXT = 1000061000,
    eViSurfaceCreateInfoNN = 1000062000,
    ePhysicalDeviceTextureCompressionAstcHdrFeaturesEXT = 1000066000,
    eImageViewAstcDecodeModeEXT = 1000067000,
    ePhysicalDeviceAstcDecodeFeaturesEXT = 1000067001,
    eImportMemoryWin32HandleInfoKHR = 1000073000,
    eExportMemoryWin32HandleInfoKHR = 1000073001,
    eMemoryWin32HandlePropertiesKHR = 1000073002,
    eMemoryGetWin32HandleInfoKHR = 1000073003,
    eImportMemoryFdInfoKHR = 1000074000,
    eMemoryFdPropertiesKHR = 1000074001,
    eMemoryGetFdInfoKHR = 1000074002,
    eWin32KeyedMutexAcquireReleaseInfoKHR = 1000075000,
    eImportSemaphoreWin32HandleInfoKHR = 1000078000,
    eExportSemaphoreWin32HandleInfoKHR = 1000078001,
    eD3D12FenceSubmitInfoKHR = 1000078002,
    eSemaphoreGetWin32HandleInfoKHR = 1000078003,
    eImportSemaphoreFdInfoKHR = 1000079000,
    eSemaphoreGetFdInfoKHR = 1000079001,
    ePhysicalDevicePushDescriptorPropertiesKHR = 1000080000,
    eCommandBufferInheritanceConditionalRenderingInfoEXT = 1000081000,
    ePhysicalDeviceConditionalRenderingFeaturesEXT = 1000081001,
    eConditionalRenderingBeginInfoEXT = 1000081002,
    ePresentRegionsKHR = 1000084000,
    ePipelineViewportWScalingStateCreateInfoNV = 1000087000,
    eSurfaceCapabilities2EXT = 1000090000,
    eDisplayPowerInfoEXT = 1000091000,
    eDeviceEventInfoEXT = 1000091001,
    eDisplayEventInfoEXT = 1000091002,
    eSwapchainCounterCreateInfoEXT = 1000091003,
    ePresentTimesInfoGOOGLE = 1000092000,
    ePhysicalDeviceMultiviewPerViewAttributesPropertiesNVX = 1000097000,
    ePipelineViewportSwizzleStateCreateInfoNV = 1000098000,
    ePhysicalDeviceDiscardRectanglePropertiesEXT = 1000099000,
    ePipelineDiscardRectangleStateCreateInfoEXT = 1000099001,
    ePhysicalDeviceConservativeRasterizationPropertiesEXT = 1000101000,
    ePipelineRasterizationConservativeStateCreateInfoEXT = 1000101001,
    ePhysicalDeviceDepthClipEnableFeaturesEXT = 1000102000,
    ePipelineRasterizationDepthClipStateCreateInfoEXT = 1000102001,
    eHdrMetadataEXT = 1000105000,
    eSharedPresentSurfaceCapabilitiesKHR = 1000111000,
    eImportFenceWin32HandleInfoKHR = 1000114000,
    eExportFenceWin32HandleInfoKHR = 1000114001,
    eFenceGetWin32HandleInfoKHR = 1000114002,
    eImportFenceFdInfoKHR = 1000115000,
    eFenceGetFdInfoKHR = 1000115001,
    ePhysicalDevicePerformanceQueryFeaturesKHR = 1000116000,
    ePhysicalDevicePerformanceQueryPropertiesKHR = 1000116001,
    eQueryPoolPerformanceCreateInfoKHR = 1000116002,
    ePerformanceQuerySubmitInfoKHR = 1000116003,
    eAcquireProfilingLockInfoKHR = 1000116004,
    ePerformanceCounterKHR = 1000116005,
    ePerformanceCounterDescriptionKHR = 1000116006,
    ePhysicalDeviceSurfaceInfo2KHR = 1000119000,
    eSurfaceCapabilities2KHR = 1000119001,
    eSurfaceFormat2KHR = 1000119002,
    eDisplayProperties2KHR = 1000121000,
    eDisplayPlaneProperties2KHR = 1000121001,
    eDisplayModeProperties2KHR = 1000121002,
    eDisplayPlaneInfo2KHR = 1000121003,
    eDisplayPlaneCapabilities2KHR = 1000121004,
    eIosSurfaceCreateInfoMVK = 1000122000,
    eMacosSurfaceCreateInfoMVK = 1000123000,
    eDebugUtilsObjectNameInfoEXT = 1000128000,
    eDebugUtilsObjectTagInfoEXT = 1000128001,
    eDebugUtilsLabelEXT = 1000128002,
    eDebugUtilsMessengerCallbackDataEXT = 1000128003,
    eDebugUtilsMessengerCreateInfoEXT = 1000128004,
    eAndroidHardwareBufferUsageANDROID = 1000129000,
    eAndroidHardwareBufferPropertiesANDROID = 1000129001,
    eAndroidHardwareBufferFormatPropertiesANDROID = 1000129002,
    eImportAndroidHardwareBufferInfoANDROID = 1000129003,
    eMemoryGetAndroidHardwareBufferInfoANDROID = 1000129004,
    eExternalFormatANDROID = 1000129005,
    ePhysicalDeviceInlineUniformBlockFeaturesEXT = 1000138000,
    ePhysicalDeviceInlineUniformBlockPropertiesEXT = 1000138001,
    eWriteDescriptorSetInlineUniformBlockEXT = 1000138002,
    eDescriptorPoolInlineUniformBlockCreateInfoEXT = 1000138003,
    eSampleLocationsInfoEXT = 1000143000,
    eRenderPassSampleLocationsBeginInfoEXT = 1000143001,
    ePipelineSampleLocationsStateCreateInfoEXT = 1000143002,
    ePhysicalDeviceSampleLocationsPropertiesEXT = 1000143003,
    eMultisamplePropertiesEXT = 1000143004,
    ePhysicalDeviceBlendOperationAdvancedFeaturesEXT = 1000148000,
    ePhysicalDeviceBlendOperationAdvancedPropertiesEXT = 1000148001,
    ePipelineColorBlendAdvancedStateCreateInfoEXT = 1000148002,
    ePipelineCoverageToColorStateCreateInfoNV = 1000149000,
    eBindAccelerationStructureMemoryInfoKHR = 1000150006,
    eWriteDescriptorSetAccelerationStructureKHR = 1000150007,
    eAccelerationStructureBuildGeometryInfoKHR = 1000150000,
    eAccelerationStructureCreateGeometryTypeInfoKHR = 1000150001,
    eAccelerationStructureDeviceAddressInfoKHR = 1000150002,
    eAccelerationStructureGeometryAabbsDataKHR = 1000150003,
    eAccelerationStructureGeometryInstancesDataKHR = 1000150004,
    eAccelerationStructureGeometryTrianglesDataKHR = 1000150005,
    eAccelerationStructureGeometryKHR = 1000150006,
    eAccelerationStructureInfoKHR = 1000150007,
    eAccelerationStructureMemoryRequirementsInfoKHR = 1000150008,
    eAccelerationStructureVersionKHR = 1000150009,
    eCopyAccelerationStructureInfoKHR = 1000150010,
    eCopyAccelerationStructureToMemoryInfoKHR = 1000150011,
    eCopyMemoryToAccelerationStructureInfoKHR = 1000150012,
    ePhysicalDeviceRayTracingFeaturesKHR = 1000150013,
    ePhysicalDeviceRayTracingPropertiesKHR = 1000150014,
    eRayTracingPipelineCreateInfoKHR = 1000150015,
    eRayTracingShaderGroupCreateInfoKHR = 1000150016,
    eAccelerationStructureCreateInfoKHR = 1000150017,
    eRayTracingPipelineInterfaceCreateInfoKHR = 1000150018,
    ePipelineCoverageModulationStateCreateInfoNV = 1000152000,
    ePhysicalDeviceShaderSmBuiltinsFeaturesNV = 1000154000,
    ePhysicalDeviceShaderSmBuiltinsPropertiesNV = 1000154001,
    eDrmFormatModifierPropertiesListEXT = 1000158000,
    eDrmFormatModifierPropertiesEXT = 1000158001,
    ePhysicalDeviceImageDrmFormatModifierInfoEXT = 1000158002,
    eImageDrmFormatModifierListCreateInfoEXT = 1000158003,
    eImageDrmFormatModifierExplicitCreateInfoEXT = 1000158004,
    eImageDrmFormatModifierPropertiesEXT = 1000158005,
    eValidationCacheCreateInfoEXT = 1000160000,
    eShaderModuleValidationCacheCreateInfoEXT = 1000160001,
    ePipelineViewportShadingRateImageStateCreateInfoNV = 1000164000,
    ePhysicalDeviceShadingRateImageFeaturesNV = 1000164001,
    ePhysicalDeviceShadingRateImagePropertiesNV = 1000164002,
    ePipelineViewportCoarseSampleOrderStateCreateInfoNV = 1000164005,
    eRayTracingPipelineCreateInfoNV = 1000165000,
    eAccelerationStructureCreateInfoNV = 1000165001,
    eGeometryNV = 1000165003,
    eGeometryTrianglesNV = 1000165004,
    eGeometryAabbNV = 1000165005,
    eAccelerationStructureMemoryRequirementsInfoNV = 1000165008,
    ePhysicalDeviceRayTracingPropertiesNV = 1000165009,
    eRayTracingShaderGroupCreateInfoNV = 1000165011,
    eAccelerationStructureInfoNV = 1000165012,
    ePhysicalDeviceRepresentativeFragmentTestFeaturesNV = 1000166000,
    ePipelineRepresentativeFragmentTestStateCreateInfoNV = 1000166001,
    ePhysicalDeviceImageViewImageFormatInfoEXT = 1000170000,
    eFilterCubicImageViewImageFormatPropertiesEXT = 1000170001,
    eDeviceQueueGlobalPriorityCreateInfoEXT = 1000174000,
    eImportMemoryHostPointerInfoEXT = 1000178000,
    eMemoryHostPointerPropertiesEXT = 1000178001,
    ePhysicalDeviceExternalMemoryHostPropertiesEXT = 1000178002,
    ePhysicalDeviceShaderClockFeaturesKHR = 1000181000,
    ePipelineCompilerControlCreateInfoAMD = 1000183000,
    eCalibratedTimestampInfoEXT = 1000184000,
    ePhysicalDeviceShaderCorePropertiesAMD = 1000185000,
    eDeviceMemoryOverallocationCreateInfoAMD = 1000189000,
    ePhysicalDeviceVertexAttributeDivisorPropertiesEXT = 1000190000,
    ePipelineVertexInputDivisorStateCreateInfoEXT = 1000190001,
    ePhysicalDeviceVertexAttributeDivisorFeaturesEXT = 1000190002,
    ePresentFrameTokenGGP = 1000191000,
    ePipelineCreationFeedbackCreateInfoEXT = 1000192000,
    ePhysicalDeviceComputeShaderDerivativesFeaturesNV = 1000201000,
    ePhysicalDeviceMeshShaderFeaturesNV = 1000202000,
    ePhysicalDeviceMeshShaderPropertiesNV = 1000202001,
    ePhysicalDeviceFragmentShaderBarycentricFeaturesNV = 1000203000,
    ePhysicalDeviceShaderImageFootprintFeaturesNV = 1000204000,
    ePipelineViewportExclusiveScissorStateCreateInfoNV = 1000205000,
    ePhysicalDeviceExclusiveScissorFeaturesNV = 1000205002,
    eCheckpointDataNV = 1000206000,
    eQueueFamilyCheckpointPropertiesNV = 1000206001,
    ePhysicalDeviceShaderIntegerFunctions2FeaturesINTEL = 1000209000,
    eQueryPoolCreateInfoINTEL = 1000210000,
    eInitializePerformanceApiInfoINTEL = 1000210001,
    ePerformanceMarkerInfoINTEL = 1000210002,
    ePerformanceStreamMarkerInfoINTEL = 1000210003,
    ePerformanceOverrideInfoINTEL = 1000210004,
    ePerformanceConfigurationAcquireInfoINTEL = 1000210005,
    ePhysicalDevicePciBusInfoPropertiesEXT = 1000212000,
    eDisplayNativeHdrSurfaceCapabilitiesAMD = 1000213000,
    eSwapchainDisplayNativeHdrCreateInfoAMD = 1000213001,
    eImagepipeSurfaceCreateInfoFUCHSIA = 1000214000,
    eMetalSurfaceCreateInfoEXT = 1000217000,
    ePhysicalDeviceFragmentDensityMapFeaturesEXT = 1000218000,
    ePhysicalDeviceFragmentDensityMapPropertiesEXT = 1000218001,
    eRenderPassFragmentDensityMapCreateInfoEXT = 1000218002,
    ePhysicalDeviceSubgroupSizeControlPropertiesEXT = 1000225000,
    ePipelineShaderStageRequiredSubgroupSizeCreateInfoEXT = 1000225001,
    ePhysicalDeviceSubgroupSizeControlFeaturesEXT = 1000225002,
    ePhysicalDeviceShaderCoreProperties2AMD = 1000227000,
    ePhysicalDeviceCoherentMemoryFeaturesAMD = 1000229000,
    ePhysicalDeviceMemoryBudgetPropertiesEXT = 1000237000,
    ePhysicalDeviceMemoryPriorityFeaturesEXT = 1000238000,
    eMemoryPriorityAllocateInfoEXT = 1000238001,
    eSurfaceProtectedCapabilitiesKHR = 1000239000,
    ePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV = 1000240000,
    ePhysicalDeviceBufferDeviceAddressFeaturesEXT = 1000244000,
    eBufferDeviceAddressCreateInfoEXT = 1000244002,
    ePhysicalDeviceToolPropertiesEXT = 1000245000,
    eValidationFeaturesEXT = 1000247000,
    ePhysicalDeviceCooperativeMatrixFeaturesNV = 1000249000,
    eCooperativeMatrixPropertiesNV = 1000249001,
    ePhysicalDeviceCooperativeMatrixPropertiesNV = 1000249002,
    ePhysicalDeviceCoverageReductionModeFeaturesNV = 1000250000,
    ePipelineCoverageReductionStateCreateInfoNV = 1000250001,
    eFramebufferMixedSamplesCombinationNV = 1000250002,
    ePhysicalDeviceFragmentShaderInterlockFeaturesEXT = 1000251000,
    ePhysicalDeviceYcbcrImageArraysFeaturesEXT = 1000252000,
    eSurfaceFullScreenExclusiveInfoEXT = 1000255000,
    eSurfaceCapabilitiesFullScreenExclusiveEXT = 1000255002,
    eSurfaceFullScreenExclusiveWin32InfoEXT = 1000255001,
    eHeadlessSurfaceCreateInfoEXT = 1000256000,
    ePhysicalDeviceLineRasterizationFeaturesEXT = 1000259000,
    ePipelineRasterizationLineStateCreateInfoEXT = 1000259001,
    ePhysicalDeviceLineRasterizationPropertiesEXT = 1000259002,
    ePhysicalDeviceIndexTypeUint8FeaturesEXT = 1000265000,
    eDeferredOperationInfoKHR = 1000268000,
    ePhysicalDevicePipelineExecutablePropertiesFeaturesKHR = 1000269000,
    ePipelineInfoKHR = 1000269001,
    ePipelineExecutablePropertiesKHR = 1000269002,
    ePipelineExecutableInfoKHR = 1000269003,
    ePipelineExecutableStatisticKHR = 1000269004,
    ePipelineExecutableInternalRepresentationKHR = 1000269005,
    ePhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT = 1000276000,
    ePhysicalDeviceDeviceGeneratedCommandsPropertiesNV = 1000277000,
    eGraphicsShaderGroupCreateInfoNV = 1000277001,
    eGraphicsPipelineShaderGroupsCreateInfoNV = 1000277002,
    eIndirectCommandsLayoutTokenNV = 1000277003,
    eIndirectCommandsLayoutCreateInfoNV = 1000277004,
    eGeneratedCommandsInfoNV = 1000277005,
    eGeneratedCommandsMemoryRequirementsInfoNV = 1000277006,
    ePhysicalDeviceDeviceGeneratedCommandsFeaturesNV = 1000277007,
    ePhysicalDeviceTexelBufferAlignmentFeaturesEXT = 1000281000,
    ePhysicalDeviceTexelBufferAlignmentPropertiesEXT = 1000281001,
    eCommandBufferInheritanceRenderPassTransformInfoQCOM = 1000282000,
    eRenderPassTransformBeginInfoQCOM = 1000282001,
    ePipelineLibraryCreateInfoKHR = 1000290000,
    ePhysicalDevicePipelineCreationCacheControlFeaturesEXT = 1000297000,
    ePhysicalDeviceDiagnosticsConfigFeaturesNV = 1000300000,
    eDeviceDiagnosticsConfigCreateInfoNV = 1000300001,
    eReservedQCOM = 1000309000,
    ePhysicalDeviceSubgroupProperties = 1000094000,
    eBindBufferMemoryInfo = 1000157000,
    eBindImageMemoryInfo = 1000157001,
    ePhysicalDevice16BitStorageFeatures = 1000083000,
    eMemoryDedicatedRequirements = 1000127000,
    eMemoryDedicatedAllocateInfo = 1000127001,
    eMemoryAllocateFlagsInfo = 1000060000,
    eDeviceGroupRenderPassBeginInfo = 1000060003,
    eDeviceGroupCommandBufferBeginInfo = 1000060004,
    eDeviceGroupSubmitInfo = 1000060005,
    eDeviceGroupBindSparseInfo = 1000060006,
    eBindBufferMemoryDeviceGroupInfo = 1000060013,
    eBindImageMemoryDeviceGroupInfo = 1000060014,
    ePhysicalDeviceGroupProperties = 1000070000,
    eDeviceGroupDeviceCreateInfo = 1000070001,
    eBufferMemoryRequirementsInfo2 = 1000146000,
    eImageMemoryRequirementsInfo2 = 1000146001,
    eImageSparseMemoryRequirementsInfo2 = 1000146002,
    eMemoryRequirements2 = 1000146003,
    eSparseImageMemoryRequirements2 = 1000146004,
    ePhysicalDeviceFeatures2 = 1000059000,
    ePhysicalDeviceProperties2 = 1000059001,
    eFormatProperties2 = 1000059002,
    eImageFormatProperties2 = 1000059003,
    ePhysicalDeviceImageFormatInfo2 = 1000059004,
    eQueueFamilyProperties2 = 1000059005,
    ePhysicalDeviceMemoryProperties2 = 1000059006,
    eSparseImageFormatProperties2 = 1000059007,
    ePhysicalDeviceSparseImageFormatInfo2 = 1000059008,
    ePhysicalDevicePointClippingProperties = 1000117000,
    eRenderPassInputAttachmentAspectCreateInfo = 1000117001,
    eImageViewUsageCreateInfo = 1000117002,
    ePipelineTessellationDomainOriginStateCreateInfo = 1000117003,
    eRenderPassMultiviewCreateInfo = 1000053000,
    ePhysicalDeviceMultiviewFeatures = 1000053001,
    ePhysicalDeviceMultiviewProperties = 1000053002,
    ePhysicalDeviceVariablePointersFeatures = 1000120000,
    eProtectedSubmitInfo = 1000145000,
    ePhysicalDeviceProtectedMemoryFeatures = 1000145001,
    ePhysicalDeviceProtectedMemoryProperties = 1000145002,
    eDeviceQueueInfo2 = 1000145003,
    eSamplerYcbcrConversionCreateInfo = 1000156000,
    eSamplerYcbcrConversionInfo = 1000156001,
    eBindImagePlaneMemoryInfo = 1000156002,
    eImagePlaneMemoryRequirementsInfo = 1000156003,
    ePhysicalDeviceSamplerYcbcrConversionFeatures = 1000156004,
    eSamplerYcbcrConversionImageFormatProperties = 1000156005,
    eDescriptorUpdateTemplateCreateInfo = 1000085000,
    ePhysicalDeviceExternalImageFormatInfo = 1000071000,
    eExternalImageFormatProperties = 1000071001,
    ePhysicalDeviceExternalBufferInfo = 1000071002,
    eExternalBufferProperties = 1000071003,
    ePhysicalDeviceIdProperties = 1000071004,
    eExternalMemoryBufferCreateInfo = 1000072000,
    eExternalMemoryImageCreateInfo = 1000072001,
    eExportMemoryAllocateInfo = 1000072002,
    ePhysicalDeviceExternalFenceInfo = 1000112000,
    eExternalFenceProperties = 1000112001,
    eExportFenceCreateInfo = 1000113000,
    eExportSemaphoreCreateInfo = 1000077000,
    ePhysicalDeviceExternalSemaphoreInfo = 1000076000,
    eExternalSemaphoreProperties = 1000076001,
    ePhysicalDeviceMaintenance3Properties = 1000168000,
    eDescriptorSetLayoutSupport = 1000168001,
    ePhysicalDeviceShaderDrawParametersFeatures = 1000063000,
    ePhysicalDeviceVulkan11Features = 49,
    ePhysicalDeviceVulkan11Properties = 50,
    ePhysicalDeviceVulkan12Features = 51,
    ePhysicalDeviceVulkan12Properties = 52,
    eImageFormatListCreateInfo = 1000147000,
    eAttachmentDescription2 = 1000109000,
    eAttachmentReference2 = 1000109001,
    eSubpassDescription2 = 1000109002,
    eSubpassDependency2 = 1000109003,
    eRenderPassCreateInfo2 = 1000109004,
    eSubpassBeginInfo = 1000109005,
    eSubpassEndInfo = 1000109006,
    ePhysicalDevice8BitStorageFeatures = 1000177000,
    ePhysicalDeviceDriverProperties = 1000196000,
    ePhysicalDeviceShaderAtomicInt64Features = 1000180000,
    ePhysicalDeviceShaderFloat16Int8Features = 1000082000,
    ePhysicalDeviceFloatControlsProperties = 1000197000,
    eDescriptorSetLayoutBindingFlagsCreateInfo = 1000161000,
    ePhysicalDeviceDescriptorIndexingFeatures = 1000161001,
    ePhysicalDeviceDescriptorIndexingProperties = 1000161002,
    eDescriptorSetVariableDescriptorCountAllocateInfo = 1000161003,
    eDescriptorSetVariableDescriptorCountLayoutSupport = 1000161004,
    ePhysicalDeviceDepthStencilResolveProperties = 1000199000,
    eSubpassDescriptionDepthStencilResolve = 1000199001,
    ePhysicalDeviceScalarBlockLayoutFeatures = 1000221000,
    eImageStencilUsageCreateInfo = 1000246000,
    ePhysicalDeviceSamplerFilterMinmaxProperties = 1000130000,
    eSamplerReductionModeCreateInfo = 1000130001,
    ePhysicalDeviceVulkanMemoryModelFeatures = 1000211000,
    ePhysicalDeviceImagelessFramebufferFeatures = 1000108000,
    eFramebufferAttachmentsCreateInfo = 1000108001,
    eFramebufferAttachmentImageInfo = 1000108002,
    eRenderPassAttachmentBeginInfo = 1000108003,
    ePhysicalDeviceUniformBufferStandardLayoutFeatures = 1000253000,
    ePhysicalDeviceShaderSubgroupExtendedTypesFeatures = 1000175000,
    ePhysicalDeviceSeparateDepthStencilLayoutsFeatures = 1000241000,
    eAttachmentReferenceStencilLayout = 1000241001,
    eAttachmentDescriptionStencilLayout = 1000241002,
    ePhysicalDeviceHostQueryResetFeatures = 1000261000,
    ePhysicalDeviceTimelineSemaphoreFeatures = 1000207000,
    ePhysicalDeviceTimelineSemaphoreProperties = 1000207001,
    eSemaphoreTypeCreateInfo = 1000207002,
    eTimelineSemaphoreSubmitInfo = 1000207003,
    eSemaphoreWaitInfo = 1000207004,
    eSemaphoreSignalInfo = 1000207005,
    ePhysicalDeviceBufferDeviceAddressFeatures = 1000257000,
    eBufferDeviceAddressInfo = 1000244001,
    eBufferOpaqueCaptureAddressCreateInfo = 1000257002,
    eMemoryOpaqueCaptureAddressAllocateInfo = 1000257003,
    eDeviceMemoryOpaqueCaptureAddressInfo = 1000257004,
};
enum class SubpassContents: uint32_t{
    eInline = 0,
    eSecondaryCommandBuffers = 1,
};
enum class Result: int32_t{
    eSuccess = 0,
    eNotReady = 1,
    eTimeout = 2,
    eEventSet = 3,
    eEventReset = 4,
    eIncomplete = 5,
    eErrorOutOfHostMemory = -1,
    eErrorOutOfDeviceMemory = -2,
    eErrorInitializationFailed = -3,
    eErrorDeviceLost = -4,
    eErrorMemoryMapFailed = -5,
    eErrorLayerNotPresent = -6,
    eErrorExtensionNotPresent = -7,
    eErrorFeatureNotPresent = -8,
    eErrorIncompatibleDriver = -9,
    eErrorTooManyObjects = -10,
    eErrorFormatNotSupported = -11,
    eErrorFragmentedPool = -12,
    eErrorUnknown = -13,
    eErrorSurfaceLostKHR = -1000000000,
    eErrorNativeWindowInUseKHR = -1000000001,
    eSuboptimalKHR = 1000001003,
    eErrorOutOfDateKHR = -1000001004,
    eErrorIncompatibleDisplayKHR = -1000003001,
    eErrorValidationFailedEXT = -1000011001,
    eErrorInvalidShaderNV = -1000012000,
    eErrorIncompatibleVersionKHR = -1000150000,
    eErrorInvalidDrmFormatModifierPlaneLayoutEXT = -1000158000,
    eErrorNotPermittedEXT = -1000174001,
    eErrorFullScreenExclusiveModeLostEXT = -1000255000,
    eThreadIdleKHR = 1000268000,
    eThreadDoneKHR = 1000268001,
    eOperationDeferredKHR = 1000268002,
    eOperationNotDeferredKHR = 1000268003,
    eErrorPipelineCompileRequiredEXT = 1000297000,
    eErrorOutOfPoolMemory = -1000069000,
    eErrorInvalidExternalHandle = -1000072003,
    eErrorFragmentation = -1000161000,
    eErrorInvalidOpaqueCaptureAddress = -1000257000,
};
enum class DynamicState: uint32_t{
    eViewport = 0,
    eScissor = 1,
    eLineWidth = 2,
    eDepthBias = 3,
    eBlendConstants = 4,
    eDepthBounds = 5,
    eStencilCompareMask = 6,
    eStencilWriteMask = 7,
    eStencilReference = 8,
    eViewportWScalingNV = 1000087000,
    eDiscardRectangleEXT = 1000099000,
    eSampleLocationsEXT = 1000143000,
    eViewportShadingRatePaletteNV = 1000164004,
    eViewportCoarseSampleOrderNV = 1000164006,
    eExclusiveScissorNV = 1000205001,
    eLineStippleEXT = 1000259000,
};
enum class DescriptorUpdateTemplateType: uint32_t{
    eDescriptorSet = 0,
};
enum class ObjectType: uint32_t{
    eUnknown = 0,
    eInstance = 1,
    ePhysicalDevice = 2,
    eDevice = 3,
    eQueue = 4,
    eSemaphore = 5,
    eCommandBuffer = 6,
    eFence = 7,
    eDeviceMemory = 8,
    eBuffer = 9,
    eImage = 10,
    eEvent = 11,
    eQueryPool = 12,
    eBufferView = 13,
    eImageView = 14,
    eShaderModule = 15,
    ePipelineCache = 16,
    ePipelineLayout = 17,
    eRenderPass = 18,
    ePipeline = 19,
    eDescriptorSetLayout = 20,
    eSampler = 21,
    eDescriptorPool = 22,
    eDescriptorSet = 23,
    eFramebuffer = 24,
    eCommandPool = 25,
    eSurfaceKHR = 1000000000,
    eSwapchainKHR = 1000001000,
    eDisplayKHR = 1000002000,
    eDisplayModeKHR = 1000002001,
    eDebugReportCallbackEXT = 1000011000,
    eDebugUtilsMessengerEXT = 1000128000,
    eAccelerationStructureKHR = 1000150000,
    eValidationCacheEXT = 1000160000,
    ePerformanceConfigurationINTEL = 1000210000,
    eDeferredOperationKHR = 1000268000,
    eIndirectCommandsLayoutNV = 1000277000,
    eSamplerYcbcrConversion = 1000156000,
    eDescriptorUpdateTemplate = 1000085000,
};
enum class SemaphoreType: uint32_t{
    eBinary = 0,
    eTimeline = 1,
};
enum class PresentModeKHR: uint32_t{
    eImmediateKHR = 0,
    eMailboxKHR = 1,
    eFifoKHR = 2,
    eFifoRelaxedKHR = 3,
    eSharedDemandRefreshKHR = 1000111000,
    eSharedContinuousRefreshKHR = 1000111001,
};
enum class ColorSpaceKHR: uint32_t{
    eSrgbNonlinearKHR = 0,
    eDisplayP3NonlinearEXT = 1000104001,
    eExtendedSrgbLinearEXT = 1000104002,
    eDisplayP3LinearEXT = 1000104003,
    eDciP3NonlinearEXT = 1000104004,
    eBt709LinearEXT = 1000104005,
    eBt709NonlinearEXT = 1000104006,
    eBt2020LinearEXT = 1000104007,
    eHdr10St2084EXT = 1000104008,
    eDolbyvisionEXT = 1000104009,
    eHdr10HlgEXT = 1000104010,
    eAdobergbLinearEXT = 1000104011,
    eAdobergbNonlinearEXT = 1000104012,
    ePassThroughEXT = 1000104013,
    eExtendedSrgbNonlinearEXT = 1000104014,
    eDisplayNativeAMD = 1000213000,
};
enum class TimeDomainEXT: uint32_t{
    eDeviceEXT = 0,
    eClockMonotonicEXT = 1,
    eClockMonotonicRawEXT = 2,
    eQueryPerformanceCounterEXT = 3,
};
enum class DebugReportObjectTypeEXT: uint32_t{
    eUnknownEXT = 0,
    eInstanceEXT = 1,
    ePhysicalDeviceEXT = 2,
    eDeviceEXT = 3,
    eQueueEXT = 4,
    eSemaphoreEXT = 5,
    eCommandBufferEXT = 6,
    eFenceEXT = 7,
    eDeviceMemoryEXT = 8,
    eBufferEXT = 9,
    eImageEXT = 10,
    eEventEXT = 11,
    eQueryPoolEXT = 12,
    eBufferViewEXT = 13,
    eImageViewEXT = 14,
    eShaderModuleEXT = 15,
    ePipelineCacheEXT = 16,
    ePipelineLayoutEXT = 17,
    eRenderPassEXT = 18,
    ePipelineEXT = 19,
    eDescriptorSetLayoutEXT = 20,
    eSamplerEXT = 21,
    eDescriptorPoolEXT = 22,
    eDescriptorSetEXT = 23,
    eFramebufferEXT = 24,
    eCommandPoolEXT = 25,
    eSurfaceKhrEXT = 26,
    eSwapchainKhrEXT = 27,
    eDebugReportCallbackExtEXT = 28,
    eDisplayKhrEXT = 29,
    eDisplayModeKhrEXT = 30,
    eValidationCacheExtEXT = 33,
    eSamplerYcbcrConversionEXT = 1000011000,
    eDescriptorUpdateTemplateEXT = 1000011000,
    eAccelerationStructureKhrEXT = 1000150000,
    eSamplerYcbcrConversionEXT = 1000156000,
};
enum class RasterizationOrderAMD: uint32_t{
    eStrictAMD = 0,
    eRelaxedAMD = 1,
};
enum class ValidationCheckEXT: uint32_t{
    eAllEXT = 0,
    eShadersEXT = 1,
};
enum class ValidationFeatureEnableEXT: uint32_t{
    eGpuAssistedEXT = 0,
    eGpuAssistedReserveBindingSlotEXT = 1,
    eBestPracticesEXT = 2,
    eDebugPrintfEXT = 3,
};
enum class ValidationFeatureDisableEXT: uint32_t{
    eAllEXT = 0,
    eShadersEXT = 1,
    eThreadSafetyEXT = 2,
    eApiParametersEXT = 3,
    eObjectLifetimesEXT = 4,
    eCoreChecksEXT = 5,
    eUniqueHandlesEXT = 6,
};
enum class IndirectCommandsTokenTypeNV: uint32_t{
    eShaderGroupNV = 0,
    eStateFlagsNV = 1,
    eIndexBufferNV = 2,
    eVertexBufferNV = 3,
    ePushConstantNV = 4,
    eDrawIndexedNV = 5,
    eDrawNV = 6,
    eDrawTasksNV = 7,
};
enum class DisplayPowerStateEXT: uint32_t{
    eOffEXT = 0,
    eSuspendEXT = 1,
    eOnEXT = 2,
};
enum class DeviceEventTypeEXT: uint32_t{
    eDisplayHotplugEXT = 0,
};
enum class DisplayEventTypeEXT: uint32_t{
    eFirstPixelOutEXT = 0,
};
enum class ViewportCoordinateSwizzleNV: uint32_t{
    ePositiveXNV = 0,
    eNegativeXNV = 1,
    ePositiveYNV = 2,
    eNegativeYNV = 3,
    ePositiveZNV = 4,
    eNegativeZNV = 5,
    ePositiveWNV = 6,
    eNegativeWNV = 7,
};
enum class DiscardRectangleModeEXT: uint32_t{
    eInclusiveEXT = 0,
    eExclusiveEXT = 1,
};
enum class PointClippingBehavior: uint32_t{
    eAllClipPlanes = 0,
    eUserClipPlanesOnly = 1,
};
enum class SamplerReductionMode: uint32_t{
    eWeightedAverage = 0,
    eMin = 1,
    eMax = 2,
};
enum class TessellationDomainOrigin: uint32_t{
    eUpperLeft = 0,
    eLowerLeft = 1,
};
enum class SamplerYcbcrModelConversion: uint32_t{
    eRgbIdentity = 0,
    eYcbcrIdentity = 1,
    eYcbcr709 = 2,
    eYcbcr601 = 3,
    eYcbcr2020 = 4,
};
enum class SamplerYcbcrRange: uint32_t{
    eItuFull = 0,
    eItuNarrow = 1,
};
enum class ChromaLocation: uint32_t{
    eCositedEven = 0,
    eMidpoint = 1,
};
enum class BlendOverlapEXT: uint32_t{
    eUncorrelatedEXT = 0,
    eDisjointEXT = 1,
    eConjointEXT = 2,
};
enum class CoverageModulationModeNV: uint32_t{
    eNoneNV = 0,
    eRgbNV = 1,
    eAlphaNV = 2,
    eRgbaNV = 3,
};
enum class CoverageReductionModeNV: uint32_t{
    eMergeNV = 0,
    eTruncateNV = 1,
};
enum class ValidationCacheHeaderVersionEXT: uint32_t{
    eOneEXT = 1,
};
enum class ShaderInfoTypeAMD: uint32_t{
    eStatisticsAMD = 0,
    eBinaryAMD = 1,
    eDisassemblyAMD = 2,
};
enum class QueueGlobalPriorityEXT: uint32_t{
    eLowEXT = 128,
    eMediumEXT = 256,
    eHighEXT = 512,
    eRealtimeEXT = 1024,
};
enum class ConservativeRasterizationModeEXT: uint32_t{
    eDisabledEXT = 0,
    eOverestimateEXT = 1,
    eUnderestimateEXT = 2,
};
enum class VendorId: uint32_t{
    eVIV = 0x10001,
    eVSI = 0x10002,
    eKazan = 0x10003,
    eCodeplay = 0x10004,
};
enum class DriverId: uint32_t{
    eAmdProprietary = 1,
    eAmdOpenSource = 2,
    eMesaRadv = 3,
    eNvidiaProprietary = 4,
    eIntelProprietaryWindows = 5,
    eIntelOpenSourceMESA = 6,
    eImaginationProprietary = 7,
    eQualcommProprietary = 8,
    eArmProprietary = 9,
    eGoogleSwiftshader = 10,
    eGgpProprietary = 11,
    eBroadcomProprietary = 12,
};
enum class ShadingRatePaletteEntryNV: uint32_t{
    eNoInvocationsNV = 0,
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
enum class CoarseSampleOrderTypeNV: uint32_t{
    eDefaultNV = 0,
    eCustomNV = 1,
    ePixelMajorNV = 2,
    eSampleMajorNV = 3,
};
enum class CopyAccelerationStructureModeKHR: uint32_t{
    eCloneKHR = 0,
    eCompactKHR = 1,
    eSerializeKHR = 2,
    eDeserializeKHR = 3,
};
enum class AccelerationStructureTypeKHR: uint32_t{
    eTopLevelKHR = 0,
    eBottomLevelKHR = 1,
};
enum class GeometryTypeKHR: uint32_t{
    eTrianglesKHR = 0,
    eAabbsKHR = 1,
    eInstancesKHR = 1000150000,
};
enum class AccelerationStructureMemoryRequirementsTypeKHR: uint32_t{
    eObjectKHR = 0,
    eBuildScratchKHR = 1,
    eUpdateScratchKHR = 2,
};
enum class AccelerationStructureBuildTypeKHR: uint32_t{
    eHostKHR = 0,
    eDeviceKHR = 1,
    eHostOrDeviceKHR = 2,
};
enum class RayTracingShaderGroupTypeKHR: uint32_t{
    eGeneralKHR = 0,
    eTrianglesHitGroupKHR = 1,
    eProceduralHitGroupKHR = 2,
};
enum class MemoryOverallocationBehaviorAMD: uint32_t{
    eDefaultAMD = 0,
    eAllowedAMD = 1,
    eDisallowedAMD = 2,
};
enum class ScopeNV: uint32_t{
    eDeviceNV = 1,
    eWorkgroupNV = 2,
    eSubgroupNV = 3,
    eQueueFamilyNV = 5,
};
enum class ComponentTypeNV: uint32_t{
    eFloat16NV = 0,
    eFloat32NV = 1,
    eFloat64NV = 2,
    eSint8NV = 3,
    eSint16NV = 4,
    eSint32NV = 5,
    eSint64NV = 6,
    eUint8NV = 7,
    eUint16NV = 8,
    eUint32NV = 9,
    eUint64NV = 10,
};
enum class FullScreenExclusiveEXT: uint32_t{
    eDefaultEXT = 0,
    eAllowedEXT = 1,
    eDisallowedEXT = 2,
    eApplicationControlledEXT = 3,
};
enum class PerformanceCounterScopeKHR: uint32_t{
    eCommandBufferKHR = 0,
    eRenderPassKHR = 1,
    eCommandKHR = 2,
};
enum class PerformanceCounterUnitKHR: uint32_t{
    eGenericKHR = 0,
    ePercentageKHR = 1,
    eNanosecondsKHR = 2,
    eBytesKHR = 3,
    eBytesPerSecondKHR = 4,
    eKelvinKHR = 5,
    eWattsKHR = 6,
    eVoltsKHR = 7,
    eAmpsKHR = 8,
    eHertzKHR = 9,
    eCyclesKHR = 10,
};
enum class PerformanceCounterStorageKHR: uint32_t{
    eInt32KHR = 0,
    eInt64KHR = 1,
    eUint32KHR = 2,
    eUint64KHR = 3,
    eFloat32KHR = 4,
    eFloat64KHR = 5,
};
enum class PerformanceConfigurationTypeINTEL: uint32_t{
    eCommandQueueMetricsDiscoveryActivatedINTEL = 0,
};
enum class QueryPoolSamplingModeINTEL: uint32_t{
    eManualINTEL = 0,
};
enum class PerformanceOverrideTypeINTEL: uint32_t{
    eNullHardwareINTEL = 0,
    eFlushGpuCachesINTEL = 1,
};
enum class PerformanceParameterTypeINTEL: uint32_t{
    eHwCountersSupportedINTEL = 0,
    eStreamMarkerValidBitsINTEL = 1,
};
enum class PerformanceValueTypeINTEL: uint32_t{
    eUint32INTEL = 0,
    eUint64INTEL = 1,
    eFloatINTEL = 2,
    eBoolINTEL = 3,
    eStringINTEL = 4,
};
enum class ShaderFloatControlsIndependence: uint32_t{
    e32BitOnly = 0,
    eAll = 1,
    eNone = 2,
};
enum class PipelineExecutableStatisticFormatKHR: uint32_t{
    eBool32KHR = 0,
    eInt64KHR = 1,
    eUint64KHR = 2,
    eFloat64KHR = 3,
};
enum class LineRasterizationModeEXT: uint32_t{
    eDefaultEXT = 0,
    eRectangularEXT = 1,
    eBresenhamEXT = 2,
    eRectangularSmoothEXT = 3,
};
using DescriptorUpdateTemplateTypeKHR = DescriptorUpdateTemplateType;
using PointClippingBehaviorKHR = PointClippingBehavior;
using ResolveModeFlagBitsKHR = ResolveModeFlagBits;
using DescriptorBindingFlagBitsEXT = DescriptorBindingFlagBits;
using SemaphoreTypeKHR = SemaphoreType;
using GeometryFlagBitsNV = GeometryFlagBitsKHR;
using GeometryInstanceFlagBitsNV = GeometryInstanceFlagBitsKHR;
using BuildAccelerationStructureFlagBitsNV = BuildAccelerationStructureFlagBitsKHR;
using CopyAccelerationStructureModeNV = CopyAccelerationStructureModeKHR;
using AccelerationStructureTypeNV = AccelerationStructureTypeKHR;
using GeometryTypeNV = GeometryTypeKHR;
using RayTracingShaderGroupTypeNV = RayTracingShaderGroupTypeKHR;
using AccelerationStructureMemoryRequirementsTypeNV = AccelerationStructureMemoryRequirementsTypeKHR;
using SemaphoreWaitFlagBitsKHR = SemaphoreWaitFlagBits;
using ExternalMemoryHandleTypeFlagBitsKHR = ExternalMemoryHandleTypeFlagBits;
using ExternalMemoryFeatureFlagBitsKHR = ExternalMemoryFeatureFlagBits;
using ExternalSemaphoreHandleTypeFlagBitsKHR = ExternalSemaphoreHandleTypeFlagBits;
using ExternalSemaphoreFeatureFlagBitsKHR = ExternalSemaphoreFeatureFlagBits;
using SemaphoreImportFlagBitsKHR = SemaphoreImportFlagBits;
using ExternalFenceHandleTypeFlagBitsKHR = ExternalFenceHandleTypeFlagBits;
using ExternalFenceFeatureFlagBitsKHR = ExternalFenceFeatureFlagBits;
using FenceImportFlagBitsKHR = FenceImportFlagBits;
using PeerMemoryFeatureFlagBitsKHR = PeerMemoryFeatureFlagBits;
using MemoryAllocateFlagBitsKHR = MemoryAllocateFlagBits;
using TessellationDomainOriginKHR = TessellationDomainOrigin;
using SamplerYcbcrModelConversionKHR = SamplerYcbcrModelConversion;
using SamplerYcbcrRangeKHR = SamplerYcbcrRange;
using ChromaLocationKHR = ChromaLocation;
using SamplerReductionModeEXT = SamplerReductionMode;
using ShaderFloatControlsIndependenceKHR = ShaderFloatControlsIndependence;
using DriverIdKHR = DriverId;
enum class PipelineCacheCreateFlagBits: uint32_t {
    eExternallySynchronizedBitEXT = 1,
};
enum class CullModeFlagBits: uint32_t {
    eNone = 0,
    eFront = 1,
    eBack = 2,
    eFrontAndBack = 0x00000003,
};
enum class QueueFlagBits: uint32_t {
    eGraphics = 1,
    eCompute = 2,
    eTransfer = 4,
    eSparseBinding = 8,
    eReserved6BitKHR = 64,
    eReserved5BitKHR = 32,
    eProtected = 16,
};
enum class RenderPassCreateFlagBits: uint32_t {
    eReserved0BitKHR = 1,
    eTransformBitQCOM = 2,
};
enum class DeviceQueueCreateFlagBits: uint32_t {
    eProtected = 1,
};
enum class MemoryPropertyFlagBits: uint32_t {
    eDeviceLocal = 1,
    eHostVisible = 2,
    eHostCoherent = 4,
    eHostCached = 8,
    eLazilyAllocated = 16,
    eDeviceCoherentBitAMD = 64,
    eDeviceUncachedBitAMD = 128,
    eProtected = 32,
};
enum class MemoryHeapFlagBits: uint32_t {
    eDeviceLocal = 1,
    eReserved2BitKHR = 4,
    eMultiInstance = 2,
};
enum class AccessFlagBits: uint32_t {
    eIndirectCommandRead = 1,
    eIndexRead = 2,
    eVertexAttributeRead = 4,
    eUniformRead = 8,
    eInputAttachmentRead = 16,
    eShaderRead = 32,
    eShaderWrite = 64,
    eColorAttachmentRead = 128,
    eColorAttachmentWrite = 256,
    eDepthStencilAttachmentRead = 512,
    eDepthStencilAttachmentWrite = 1024,
    eTransferRead = 2048,
    eTransferWrite = 4096,
    eHostRead = 8192,
    eHostWrite = 16384,
    eMemoryRead = 32768,
    eMemoryWrite = 65536,
    eReserved30BitKHR = 1073741824,
    eReserved31BitKHR = 2147483648,
    eReserved28BitKHR = 268435456,
    eReserved29BitKHR = 536870912,
    eTransformFeedbackWriteBitEXT = 33554432,
    eTransformFeedbackCounterReadBitEXT = 67108864,
    eTransformFeedbackCounterWriteBitEXT = 134217728,
    eConditionalRenderingReadBitEXT = 1048576,
    eColorAttachmentReadNoncoherentBitEXT = 524288,
    eAccelerationStructureReadBitKHR = 2097152,
    eAccelerationStructureWriteBitKHR = 4194304,
    eShadingRateImageReadBitNV = 8388608,
    eFragmentDensityMapReadBitEXT = 16777216,
    eCommandPreprocessReadBitNV = 131072,
    eCommandPreprocessWriteBitNV = 262144,
};
enum class BufferUsageFlagBits: uint32_t {
    eTransferSrc = 1,
    eTransferDst = 2,
    eUniformTexelBuffer = 4,
    eStorageTexelBuffer = 8,
    eUniformBuffer = 16,
    eStorageBuffer = 32,
    eIndexBuffer = 64,
    eVertexBuffer = 128,
    eIndirectBuffer = 256,
    eReserved15BitKHR = 32768,
    eReserved16BitKHR = 65536,
    eReserved13BitKHR = 8192,
    eReserved14BitKHR = 16384,
    eTransformFeedbackBufferBitEXT = 2048,
    eTransformFeedbackCounterBufferBitEXT = 4096,
    eConditionalRenderingBitEXT = 512,
    eRayTracingBitKHR = 1024,
    eReserved18BitQCOM = 262144,
    eShaderDeviceAddress = 131072,
};
enum class BufferCreateFlagBits: uint32_t {
    eSparseBinding = 1,
    eSparseResidency = 2,
    eSparseAliased = 4,
    eProtected = 8,
    eDeviceAddressCaptureReplay = 16,
};
enum class ShaderStageFlagBits: uint32_t {
    eVertex = 1,
    eTessellationControl = 2,
    eTessellationEvaluation = 4,
    eGeometry = 8,
    eFragment = 16,
    eCompute = 32,
    eAllGraphics = 0x0000001F,
    eAll = 0x7FFFFFFF,
    eRaygenBitKHR = 256,
    eAnyHitBitKHR = 512,
    eClosestHitBitKHR = 1024,
    eMissBitKHR = 2048,
    eIntersectionBitKHR = 4096,
    eCallableBitKHR = 8192,
    eTaskBitNV = 64,
    eMeshBitNV = 128,
};
enum class ImageUsageFlagBits: uint32_t {
    eTransferSrc = 1,
    eTransferDst = 2,
    eSampled = 4,
    eStorage = 8,
    eColorAttachment = 16,
    eDepthStencilAttachment = 32,
    eTransientAttachment = 64,
    eInputAttachment = 128,
    eReserved13BitKHR = 8192,
    eReserved14BitKHR = 16384,
    eReserved15BitKHR = 32768,
    eReserved10BitKHR = 1024,
    eReserved11BitKHR = 2048,
    eReserved12BitKHR = 4096,
    eShadingRateImageBitNV = 256,
    eReserved16BitQCOM = 65536,
    eReserved17BitQCOM = 131072,
    eFragmentDensityMapBitEXT = 512,
};
enum class ImageCreateFlagBits: uint32_t {
    eSparseBinding = 1,
    eSparseResidency = 2,
    eSparseAliased = 4,
    eMutableFormat = 8,
    eCubeCompatible = 16,
    eCornerSampledBitNV = 8192,
    eSampleLocationsCompatibleDepthBitEXT = 4096,
    eSubsampledBitEXT = 16384,
    eAlias = 1024,
    eSplitInstanceBindRegions = 64,
    e2DArrayCompatible = 32,
    eBlockTexelViewCompatible = 128,
    eExtendedUsage = 256,
    eProtected = 2048,
    eDisjoint = 512,
};
enum class ImageViewCreateFlagBits: uint32_t {
    eFragmentDensityMapDynamicBitEXT = 1,
};
enum class SamplerCreateFlagBits: uint32_t {
    eSubsampledBitEXT = 1,
    eSubsampledCoarseReconstructionBitEXT = 2,
};
enum class PipelineCreateFlagBits: uint32_t {
    eDisableOptimization = 1,
    eAllowDerivatives = 2,
    eDerivative = 4,
    eRayTracingNoNullAnyHitShadersBitKHR = 16384,
    eRayTracingNoNullClosestHitShadersBitKHR = 32768,
    eRayTracingNoNullMissShadersBitKHR = 65536,
    eRayTracingNoNullIntersectionShadersBitKHR = 131072,
    eRayTracingSkipTrianglesBitKHR = 4096,
    eRayTracingSkipAabbsBitKHR = 8192,
    eDeferCompileBitNV = 32,
    eCaptureStatisticsBitKHR = 64,
    eCaptureInternalRepresentationsBitKHR = 128,
    eIndirectBindableBitNV = 262144,
    eLibraryBitKHR = 2048,
    eFailOnPipelineCompileRequiredBitEXT = 256,
    eEarlyReturnOnFailureBitEXT = 512,
    eViewIndexFromDeviceIndex = 8,
    eDispatchBase = 16,
};
enum class PipelineShaderStageCreateFlagBits: uint32_t {
    eReserved2BitNV = 4,
    eAllowVaryingSubgroupSizeBitEXT = 1,
    eRequireFullSubgroupsBitEXT = 2,
    eReserved3BitKHR = 8,
};
enum class ColorComponentFlagBits: uint32_t {
    eR = 1,
    eG = 2,
    eB = 4,
    eA = 8,
};
enum class FenceCreateFlagBits: uint32_t {
    eSignaled = 1,
};
enum class SemaphoreCreateFlagBits: uint32_t {
};
enum class FormatFeatureFlagBits: uint32_t {
    eSampledImage = 1,
    eStorageImage = 2,
    eStorageImageAtomic = 4,
    eUniformTexelBuffer = 8,
    eStorageTexelBuffer = 16,
    eStorageTexelBufferAtomic = 32,
    eVertexBuffer = 64,
    eColorAttachment = 128,
    eColorAttachmentBlend = 256,
    eDepthStencilAttachment = 512,
    eBlitSrc = 1024,
    eBlitDst = 2048,
    eSampledImageFilterLinear = 4096,
    eSampledImageFilterCubicBitIMG = 8192,
    eReserved27BitKHR = 134217728,
    eReserved28BitKHR = 268435456,
    eReserved25BitKHR = 33554432,
    eReserved26BitKHR = 67108864,
    eAccelerationStructureVertexBufferBitKHR = 536870912,
    eFragmentDensityMapBitEXT = 16777216,
    eTransferSrc = 16384,
    eTransferDst = 32768,
    eMidpointChromaSamples = 131072,
    eSampledImageYcbcrConversionLinearFilter = 262144,
    eSampledImageYcbcrConversionSeparateReconstructionFilter = 524288,
    eSampledImageYcbcrConversionChromaReconstructionExplicit = 1048576,
    eSampledImageYcbcrConversionChromaReconstructionExplicitForceable = 2097152,
    eDisjoint = 4194304,
    eCositedChromaSamples = 8388608,
    eSampledImageFilterMinmax = 65536,
};
enum class QueryControlFlagBits: uint32_t {
    ePrecise = 1,
};
enum class QueryResultFlagBits: uint32_t {
    e64 = 1,
    eWait = 2,
    eWithAvailability = 4,
    ePartial = 8,
};
enum class CommandBufferUsageFlagBits: uint32_t {
    eOneTimeSubmit = 1,
    eRenderPassContinue = 2,
    eSimultaneousUse = 4,
};
enum class QueryPipelineStatisticFlagBits: uint32_t {
    eInputAssemblyVertices = 1,
    eInputAssemblyPrimitives = 2,
    eVertexShaderInvocations = 4,
    eGeometryShaderInvocations = 8,
    eGeometryShaderPrimitives = 16,
    eClippingInvocations = 32,
    eClippingPrimitives = 64,
    eFragmentShaderInvocations = 128,
    eTessellationControlShaderPatches = 256,
    eTessellationEvaluationShaderInvocations = 512,
    eComputeShaderInvocations = 1024,
};
enum class ImageAspectFlagBits: uint32_t {
    eColor = 1,
    eDepth = 2,
    eStencil = 4,
    eMetadata = 8,
    eMemoryPlane0BitEXT = 128,
    eMemoryPlane1BitEXT = 256,
    eMemoryPlane2BitEXT = 512,
    eMemoryPlane3BitEXT = 1024,
    ePlane0 = 16,
    ePlane1 = 32,
    ePlane2 = 64,
};
enum class SparseImageFormatFlagBits: uint32_t {
    eSingleMiptail = 1,
    eAlignedMipSize = 2,
    eNonstandardBlockSize = 4,
};
enum class SparseMemoryBindFlagBits: uint32_t {
    eMetadata = 1,
};
enum class PipelineStageFlagBits: uint32_t {
    eTopOfPipe = 1,
    eDrawIndirect = 2,
    eVertexInput = 4,
    eVertexShader = 8,
    eTessellationControlShader = 16,
    eTessellationEvaluationShader = 32,
    eGeometryShader = 64,
    eFragmentShader = 128,
    eEarlyFragmentTests = 256,
    eLateFragmentTests = 512,
    eColorAttachmentOutput = 1024,
    eComputeShader = 2048,
    eTransfer = 4096,
    eBottomOfPipe = 8192,
    eHost = 16384,
    eAllGraphics = 32768,
    eAllCommands = 65536,
    eReserved27BitKHR = 134217728,
    eReserved26BitKHR = 67108864,
    eTransformFeedbackBitEXT = 16777216,
    eConditionalRenderingBitEXT = 262144,
    eRayTracingShaderBitKHR = 2097152,
    eAccelerationStructureBuildBitKHR = 33554432,
    eShadingRateImageBitNV = 4194304,
    eTaskShaderBitNV = 524288,
    eMeshShaderBitNV = 1048576,
    eFragmentDensityProcessBitEXT = 8388608,
    eCommandPreprocessBitNV = 131072,
};
enum class CommandPoolCreateFlagBits: uint32_t {
    eTransient = 1,
    eResetCommandBuffer = 2,
    eProtected = 4,
};
enum class CommandPoolResetFlagBits: uint32_t {
    eReleaseResources = 1,
};
enum class CommandBufferResetFlagBits: uint32_t {
    eReleaseResources = 1,
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
    eMayAlias = 1,
};
enum class StencilFaceFlagBits: uint32_t {
    eFront = 1,
    eBack = 2,
    eFrontAndBack = 0x00000003,
    eAndBack = eFrontAndBack,
};
enum class DescriptorPoolCreateFlagBits: uint32_t {
    eFreeDescriptorSet = 1,
    eUpdateAfterBind = 2,
};
enum class DependencyFlagBits: uint32_t {
    eByRegion = 1,
    eDeviceGroup = 4,
    eViewLocal = 2,
};
enum class SemaphoreWaitFlagBits: uint32_t {
    eAny = 1,
};
enum class DisplayPlaneAlphaFlagBitsKHR: uint32_t {
    eBitKHR = 1,
    eBitKHR = 2,
    ePixelBitKHR = 4,
    ePixelPremultipliedBitKHR = 8,
};
enum class CompositeAlphaFlagBitsKHR: uint32_t {
    eBitKHR = 1,
    eMultipliedBitKHR = 2,
    eMultipliedBitKHR = 4,
    eBitKHR = 8,
};
enum class SurfaceTransformFlagBitsKHR: uint32_t {
    eBitKHR = 1,
    e90BitKHR = 2,
    e180BitKHR = 4,
    e270BitKHR = 8,
    eMirrorBitKHR = 16,
    eMirrorRotate90BitKHR = 32,
    eMirrorRotate180BitKHR = 64,
    eMirrorRotate270BitKHR = 128,
    eBitKHR = 256,
};
enum class SwapchainImageUsageFlagBitsANDROID: uint32_t {
    eBitANDROID = 1,
};
enum class DebugReportFlagBitsEXT: uint32_t {
    eBitEXT = 1,
    eBitEXT = 2,
    eWarningBitEXT = 4,
    eBitEXT = 8,
    eBitEXT = 16,
};
enum class ExternalMemoryHandleTypeFlagBitsNV: uint32_t {
    eWin32BitNV = 1,
    eWin32KmtBitNV = 2,
    eImageBitNV = 4,
    eImageKmtBitNV = 8,
};
enum class ExternalMemoryFeatureFlagBitsNV: uint32_t {
    eOnlyBitNV = 1,
    eBitNV = 2,
    eBitNV = 4,
};
enum class SubgroupFeatureFlagBits: uint32_t {
    eBasic = 1,
    eVote = 2,
    eArithmetic = 4,
    eBallot = 8,
    eShuffle = 16,
    eShuffleRelative = 32,
    eClustered = 64,
    eQuad = 128,
    ePartitionedBitNV = 256,
};
enum class IndirectCommandsLayoutUsageFlagBitsNV: uint32_t {
    ePreprocessBitNV = 1,
    eSequencesBitNV = 2,
    eSequencesBitNV = 4,
};
enum class IndirectStateFlagBitsNV: uint32_t {
    eFrontfaceBitNV = 1,
};
enum class DescriptorSetLayoutCreateFlagBits: uint32_t {
    ePushDescriptorBitKHR = 1,
    eUpdateAfterBindPool = 2,
};
enum class ExternalMemoryHandleTypeFlagBits: uint32_t {
    eOpaqueFd = 1,
    eOpaqueWin32 = 2,
    eOpaqueWin32Kmt = 4,
    eD3D11Texture = 8,
    eD3D11TextureKmt = 16,
    eD3D12Heap = 32,
    eD3D12Resource = 64,
    eDmaBufBitEXT = 512,
    eAndroidHardwareBufferBitANDROID = 1024,
    eHostAllocationBitEXT = 128,
    eHostMappedForeignMemoryBitEXT = 256,
};
enum class ExternalMemoryFeatureFlagBits: uint32_t {
    eDedicatedOnly = 1,
    eExportable = 2,
    eImportable = 4,
};
enum class ExternalSemaphoreHandleTypeFlagBits: uint32_t {
    eOpaqueFd = 1,
    eOpaqueWin32 = 2,
    eOpaqueWin32Kmt = 4,
    eD3D12Fence = 8,
    eSyncFd = 16,
};
enum class ExternalSemaphoreFeatureFlagBits: uint32_t {
    eExportable = 1,
    eImportable = 2,
};
enum class SemaphoreImportFlagBits: uint32_t {
    eTemporary = 1,
};
enum class ExternalFenceHandleTypeFlagBits: uint32_t {
    eOpaqueFd = 1,
    eOpaqueWin32 = 2,
    eOpaqueWin32Kmt = 4,
    eSyncFd = 8,
};
enum class ExternalFenceFeatureFlagBits: uint32_t {
    eExportable = 1,
    eImportable = 2,
};
enum class FenceImportFlagBits: uint32_t {
    eTemporary = 1,
};
enum class SurfaceCounterFlagBitsEXT: uint32_t {
    eEXT = 1,
};
enum class PeerMemoryFeatureFlagBits: uint32_t {
    eCopySrc = 1,
    eCopyDst = 2,
    eGenericSrc = 4,
    eGenericDst = 8,
};
enum class MemoryAllocateFlagBits: uint32_t {
    eDeviceMask = 1,
    eDeviceAddress = 2,
    eDeviceAddressCaptureReplay = 4,
};
enum class DeviceGroupPresentModeFlagBitsKHR: uint32_t {
    eBitKHR = 1,
    eBitKHR = 2,
    eBitKHR = 4,
    eMultiDeviceBitKHR = 8,
};
enum class SwapchainCreateFlagBitsKHR: uint32_t {
    eInstanceBindRegionsBitKHR = 1,
    eBitKHR = 2,
    eFormatBitKHR = 4,
};
enum class SubpassDescriptionFlagBits: uint32_t {
    ePerViewAttributesBitNVX = 1,
    ePerViewPositionXOnlyBitNVX = 2,
    eReserved2BitQCOM = 4,
    eReserved3BitQCOM = 8,
};
enum class DebugUtilsMessageSeverityFlagBitsEXT: uint32_t {
    eBitEXT = 1,
    eBitEXT = 16,
    eBitEXT = 256,
    eBitEXT = 4096,
};
enum class DebugUtilsMessageTypeFlagBitsEXT: uint32_t {
    eBitEXT = 1,
    eBitEXT = 2,
    eBitEXT = 4,
};
enum class DescriptorBindingFlagBits: uint32_t {
    eUpdateAfterBind = 1,
    eUpdateUnusedWhilePending = 2,
    ePartiallyBound = 4,
    eVariableDescriptorCount = 8,
};
enum class ConditionalRenderingFlagBitsEXT: uint32_t {
    eBitEXT = 1,
};
enum class ResolveModeFlagBits: uint32_t {
    eNone = 0,
    eSampleZero = 1,
    eAverage = 2,
    eMin = 4,
    eMax = 8,
};
enum class GeometryInstanceFlagBitsKHR: uint32_t {
    eFacingCullDisableBitKHR = 1,
    eFrontCounterclockwiseBitKHR = 2,
    eOpaqueBitKHR = 4,
    eNoOpaqueBitKHR = 8,
};
enum class GeometryFlagBitsKHR: uint32_t {
    eBitKHR = 1,
    eDuplicateAnyHitInvocationBitKHR = 2,
};
enum class BuildAccelerationStructureFlagBitsKHR: uint32_t {
    eUpdateBitKHR = 1,
    eCompactionBitKHR = 2,
    eFastTraceBitKHR = 4,
    eFastBuildBitKHR = 8,
    eMemoryBitKHR = 16,
};
enum class FramebufferCreateFlagBits: uint32_t {
    eImageless = 1,
};
enum class DeviceDiagnosticsConfigFlagBitsNV: uint32_t {
    eShaderDebugInfoBitNV = 1,
    eResourceTrackingBitNV = 2,
    eAutomaticCheckpointsBitNV = 4,
};
enum class PipelineCreationFeedbackFlagBitsEXT: uint32_t {
    eBitEXT = 1,
    ePipelineCacheHitBitEXT = 2,
    ePipelineAccelerationBitEXT = 4,
};
enum class PerformanceCounterDescriptionFlagBitsKHR: uint32_t {
    eImpactingKHR = 1,
    eImpactedKHR = 2,
};
enum class AcquireProfilingLockFlagBitsKHR: uint32_t {
};
enum class ShaderCorePropertiesFlagBitsAMD: uint32_t {
};
enum class ShaderModuleCreateFlagBits: uint32_t {
    eReserved0BitNV = 1,
};
enum class PipelineCompilerControlFlagBitsAMD: uint32_t {
};
enum class ToolPurposeFlagBitsEXT: uint32_t {
    eBitEXT = 1,
    eBitEXT = 2,
    eBitEXT = 4,
    eFeaturesBitEXT = 8,
    eFeaturesBitEXT = 16,
    eReportingBitEXT = 32,
    eMarkersBitEXT = 64,
};
using FramebufferCreateFlags = uint32_t;
using QueryPoolCreateFlags = uint32_t;
using RenderPassCreateFlags = uint32_t;
using SamplerCreateFlags = uint32_t;
using PipelineLayoutCreateFlags = uint32_t;
using PipelineCacheCreateFlags = uint32_t;
using PipelineDepthStencilStateCreateFlags = uint32_t;
using PipelineDynamicStateCreateFlags = uint32_t;
using PipelineColorBlendStateCreateFlags = uint32_t;
using PipelineMultisampleStateCreateFlags = uint32_t;
using PipelineRasterizationStateCreateFlags = uint32_t;
using PipelineViewportStateCreateFlags = uint32_t;
using PipelineTessellationStateCreateFlags = uint32_t;
using PipelineInputAssemblyStateCreateFlags = uint32_t;
using PipelineVertexInputStateCreateFlags = uint32_t;
using PipelineShaderStageCreateFlags = uint32_t;
using DescriptorSetLayoutCreateFlags = uint32_t;
using BufferViewCreateFlags = uint32_t;
using InstanceCreateFlags = uint32_t;
using DeviceCreateFlags = uint32_t;
using DeviceQueueCreateFlags = uint32_t;
using QueueFlags = uint32_t;
using MemoryPropertyFlags = uint32_t;
using MemoryHeapFlags = uint32_t;
using AccessFlags = uint32_t;
using BufferUsageFlags = uint32_t;
using BufferCreateFlags = uint32_t;
using ShaderStageFlags = uint32_t;
using ImageUsageFlags = uint32_t;
using ImageCreateFlags = uint32_t;
using ImageViewCreateFlags = uint32_t;
using PipelineCreateFlags = uint32_t;
using ColorComponentFlags = uint32_t;
using FenceCreateFlags = uint32_t;
using SemaphoreCreateFlags = uint32_t;
using FormatFeatureFlags = uint32_t;
using QueryControlFlags = uint32_t;
using QueryResultFlags = uint32_t;
using ShaderModuleCreateFlags = uint32_t;
using EventCreateFlags = uint32_t;
using CommandPoolCreateFlags = uint32_t;
using CommandPoolResetFlags = uint32_t;
using CommandBufferResetFlags = uint32_t;
using CommandBufferUsageFlags = uint32_t;
using QueryPipelineStatisticFlags = uint32_t;
using MemoryMapFlags = uint32_t;
using ImageAspectFlags = uint32_t;
using SparseMemoryBindFlags = uint32_t;
using SparseImageFormatFlags = uint32_t;
using SubpassDescriptionFlags = uint32_t;
using PipelineStageFlags = uint32_t;
using SampleCountFlags = uint32_t;
using AttachmentDescriptionFlags = uint32_t;
using StencilFaceFlags = uint32_t;
using CullModeFlags = uint32_t;
using DescriptorPoolCreateFlags = uint32_t;
using DescriptorPoolResetFlags = uint32_t;
using DependencyFlags = uint32_t;
using SubgroupFeatureFlags = uint32_t;
using IndirectCommandsLayoutUsageFlagsNV = uint32_t;
using IndirectStateFlagsNV = uint32_t;
using GeometryFlagsKHR = uint32_t;
using GeometryFlagsNV = uint32_t;
using GeometryInstanceFlagsKHR = uint32_t;
using GeometryInstanceFlagsNV = uint32_t;
using BuildAccelerationStructureFlagsKHR = uint32_t;
using BuildAccelerationStructureFlagsNV = uint32_t;
using DescriptorUpdateTemplateCreateFlags = uint32_t;
using DescriptorUpdateTemplateCreateFlagsKHR = uint32_t;
using PipelineCreationFeedbackFlagsEXT = uint32_t;
using PerformanceCounterDescriptionFlagsKHR = uint32_t;
using AcquireProfilingLockFlagsKHR = uint32_t;
using SemaphoreWaitFlags = uint32_t;
using SemaphoreWaitFlagsKHR = uint32_t;
using PipelineCompilerControlFlagsAMD = uint32_t;
using ShaderCorePropertiesFlagsAMD = uint32_t;
using DeviceDiagnosticsConfigFlagsNV = uint32_t;
using CompositeAlphaFlagsKHR = uint32_t;
using DisplayPlaneAlphaFlagsKHR = uint32_t;
using SurfaceTransformFlagsKHR = uint32_t;
using SwapchainCreateFlagsKHR = uint32_t;
using DisplayModeCreateFlagsKHR = uint32_t;
using DisplaySurfaceCreateFlagsKHR = uint32_t;
using AndroidSurfaceCreateFlagsKHR = uint32_t;
using ViSurfaceCreateFlagsNN = uint32_t;
using WaylandSurfaceCreateFlagsKHR = uint32_t;
using Win32SurfaceCreateFlagsKHR = uint32_t;
using XlibSurfaceCreateFlagsKHR = uint32_t;
using XcbSurfaceCreateFlagsKHR = uint32_t;
using IOSSurfaceCreateFlagsMVK = uint32_t;
using MacOSSurfaceCreateFlagsMVK = uint32_t;
using MetalSurfaceCreateFlagsEXT = uint32_t;
using ImagePipeSurfaceCreateFlagsFUCHSIA = uint32_t;
using StreamDescriptorSurfaceCreateFlagsGGP = uint32_t;
using HeadlessSurfaceCreateFlagsEXT = uint32_t;
using PeerMemoryFeatureFlags = uint32_t;
using PeerMemoryFeatureFlagsKHR = uint32_t;
using MemoryAllocateFlags = uint32_t;
using MemoryAllocateFlagsKHR = uint32_t;
using DeviceGroupPresentModeFlagsKHR = uint32_t;
using DebugReportFlagsEXT = uint32_t;
using CommandPoolTrimFlags = uint32_t;
using CommandPoolTrimFlagsKHR = uint32_t;
using ExternalMemoryHandleTypeFlagsNV = uint32_t;
using ExternalMemoryFeatureFlagsNV = uint32_t;
using ExternalMemoryHandleTypeFlags = uint32_t;
using ExternalMemoryHandleTypeFlagsKHR = uint32_t;
using ExternalMemoryFeatureFlags = uint32_t;
using ExternalMemoryFeatureFlagsKHR = uint32_t;
using ExternalSemaphoreHandleTypeFlags = uint32_t;
using ExternalSemaphoreHandleTypeFlagsKHR = uint32_t;
using ExternalSemaphoreFeatureFlags = uint32_t;
using ExternalSemaphoreFeatureFlagsKHR = uint32_t;
using SemaphoreImportFlags = uint32_t;
using SemaphoreImportFlagsKHR = uint32_t;
using ExternalFenceHandleTypeFlags = uint32_t;
using ExternalFenceHandleTypeFlagsKHR = uint32_t;
using ExternalFenceFeatureFlags = uint32_t;
using ExternalFenceFeatureFlagsKHR = uint32_t;
using FenceImportFlags = uint32_t;
using FenceImportFlagsKHR = uint32_t;
using SurfaceCounterFlagsEXT = uint32_t;
using PipelineViewportSwizzleStateCreateFlagsNV = uint32_t;
using PipelineDiscardRectangleStateCreateFlagsEXT = uint32_t;
using PipelineCoverageToColorStateCreateFlagsNV = uint32_t;
using PipelineCoverageModulationStateCreateFlagsNV = uint32_t;
using PipelineCoverageReductionStateCreateFlagsNV = uint32_t;
using ValidationCacheCreateFlagsEXT = uint32_t;
using DebugUtilsMessageSeverityFlagsEXT = uint32_t;
using DebugUtilsMessageTypeFlagsEXT = uint32_t;
using DebugUtilsMessengerCreateFlagsEXT = uint32_t;
using DebugUtilsMessengerCallbackDataFlagsEXT = uint32_t;
using PipelineRasterizationConservativeStateCreateFlagsEXT = uint32_t;
using DescriptorBindingFlags = uint32_t;
using DescriptorBindingFlagsEXT = uint32_t;
using ConditionalRenderingFlagsEXT = uint32_t;
using ResolveModeFlags = uint32_t;
using ResolveModeFlagsKHR = uint32_t;
using PipelineRasterizationStateStreamCreateFlagsEXT = uint32_t;
using PipelineRasterizationDepthClipStateCreateFlagsEXT = uint32_t;
using SwapchainImageUsageFlagsANDROID = uint32_t;
using ToolPurposeFlagsEXT = uint32_t;
class DeviceMemory {
   VkDeviceMemory handle = VK_NULL_HANDLE;
   public:
   VkDeviceMemory get() { return handle; }
};
class CommandPool {
   VkCommandPool handle = VK_NULL_HANDLE;
   public:
   VkCommandPool get() { return handle; }
};
class Buffer {
   VkBuffer handle = VK_NULL_HANDLE;
   public:
   VkBuffer get() { return handle; }
};
class BufferView {
   VkBufferView handle = VK_NULL_HANDLE;
   public:
   VkBufferView get() { return handle; }
};
class Image {
   VkImage handle = VK_NULL_HANDLE;
   public:
   VkImage get() { return handle; }
};
class ImageView {
   VkImageView handle = VK_NULL_HANDLE;
   public:
   VkImageView get() { return handle; }
};
class ShaderModule {
   VkShaderModule handle = VK_NULL_HANDLE;
   public:
   VkShaderModule get() { return handle; }
};
class Pipeline {
   VkPipeline handle = VK_NULL_HANDLE;
   public:
   VkPipeline get() { return handle; }
};
class PipelineLayout {
   VkPipelineLayout handle = VK_NULL_HANDLE;
   public:
   VkPipelineLayout get() { return handle; }
};
class Sampler {
   VkSampler handle = VK_NULL_HANDLE;
   public:
   VkSampler get() { return handle; }
};
class DescriptorSet {
   VkDescriptorSet handle = VK_NULL_HANDLE;
   public:
   VkDescriptorSet get() { return handle; }
};
class DescriptorSetLayout {
   VkDescriptorSetLayout handle = VK_NULL_HANDLE;
   public:
   VkDescriptorSetLayout get() { return handle; }
};
class DescriptorPool {
   VkDescriptorPool handle = VK_NULL_HANDLE;
   public:
   VkDescriptorPool get() { return handle; }
};
class Fence {
   VkFence handle = VK_NULL_HANDLE;
   public:
   VkFence get() { return handle; }
};
class Semaphore {
   VkSemaphore handle = VK_NULL_HANDLE;
   public:
   VkSemaphore get() { return handle; }
};
class Event {
   VkEvent handle = VK_NULL_HANDLE;
   public:
   VkEvent get() { return handle; }
};
class QueryPool {
   VkQueryPool handle = VK_NULL_HANDLE;
   public:
   VkQueryPool get() { return handle; }
};
class Framebuffer {
   VkFramebuffer handle = VK_NULL_HANDLE;
   public:
   VkFramebuffer get() { return handle; }
};
class RenderPass {
   VkRenderPass handle = VK_NULL_HANDLE;
   public:
   VkRenderPass get() { return handle; }
};
class PipelineCache {
   VkPipelineCache handle = VK_NULL_HANDLE;
   public:
   VkPipelineCache get() { return handle; }
};
class IndirectCommandsLayoutNV {
   VkIndirectCommandsLayoutNV handle = VK_NULL_HANDLE;
   public:
   VkIndirectCommandsLayoutNV get() { return handle; }
};
class DescriptorUpdateTemplate {
   VkDescriptorUpdateTemplate handle = VK_NULL_HANDLE;
   public:
   VkDescriptorUpdateTemplate get() { return handle; }
};
class SamplerYcbcrConversion {
   VkSamplerYcbcrConversion handle = VK_NULL_HANDLE;
   public:
   VkSamplerYcbcrConversion get() { return handle; }
};
class ValidationCacheEXT {
   VkValidationCacheEXT handle = VK_NULL_HANDLE;
   public:
   VkValidationCacheEXT get() { return handle; }
};
class AccelerationStructureKHR {
   VkAccelerationStructureKHR handle = VK_NULL_HANDLE;
   public:
   VkAccelerationStructureKHR get() { return handle; }
};
class PerformanceConfigurationINTEL {
   VkPerformanceConfigurationINTEL handle = VK_NULL_HANDLE;
   public:
   VkPerformanceConfigurationINTEL get() { return handle; }
};
class DeferredOperationKHR {
   VkDeferredOperationKHR handle = VK_NULL_HANDLE;
   public:
   VkDeferredOperationKHR get() { return handle; }
};
class DisplayKHR {
   VkDisplayKHR handle = VK_NULL_HANDLE;
   public:
   VkDisplayKHR get() { return handle; }
};
class DisplayModeKHR {
   VkDisplayModeKHR handle = VK_NULL_HANDLE;
   public:
   VkDisplayModeKHR get() { return handle; }
};
class SurfaceKHR {
   VkSurfaceKHR handle = VK_NULL_HANDLE;
   public:
   VkSurfaceKHR get() { return handle; }
};
class SwapchainKHR {
   VkSwapchainKHR handle = VK_NULL_HANDLE;
   public:
   VkSwapchainKHR get() { return handle; }
};
class DebugReportCallbackEXT {
   VkDebugReportCallbackEXT handle = VK_NULL_HANDLE;
   public:
   VkDebugReportCallbackEXT get() { return handle; }
};
class DebugUtilsMessengerEXT {
   VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
   public:
   VkDebugUtilsMessengerEXT get() { return handle; }
};
using DescriptorUpdateTemplateKHR = DescriptorUpdateTemplate;
using SamplerYcbcrConversionKHR = SamplerYcbcrConversion;
using AccelerationStructureNV = AccelerationStructureKHR;
union ClearColorValue {
    float float32[4];
    int32_t int32[4];
    uint32_t uint32[4];
};
union ClearValue {
    ClearColorValue color;
    ClearDepthStencilValue depthStencil;
};
union PerformanceCounterResultKHR {
    int32_t int32;
    int64_t int64;
    uint32_t uint32;
    uint64_t uint64;
    float float32;
    double float64;
};
union PerformanceValueDataINTEL {
    uint32_t value32;
    uint64_t value64;
    float valueFloat;
    bool valueBool;
    const char* valueString;
};
union PipelineExecutableStatisticValueKHR {
    bool b32;
    int64_t i64;
    uint64_t u64;
    double f64;
};
union DeviceOrHostAddressKHR {
    DeviceAddress deviceAddress;
    void* hostAddress;
};
union DeviceOrHostAddressConstKHR {
    DeviceAddress deviceAddress;
    const void* hostAddress;
};
union AccelerationStructureGeometryDataKHR {
    AccelerationStructureGeometryTrianglesDataKHR triangles;
    AccelerationStructureGeometryAabbsDataKHR aabbs;
    AccelerationStructureGeometryInstancesDataKHR instances;
};
struct BaseOutStructure {
    StructureType sType = static_cast<StructureType>(0);
    BaseOutStructure* pNext = nullptr;
};
struct BaseInStructure {
    StructureType sType = static_cast<StructureType>(0);
    const BaseInStructure* pNext = nullptr;
};
struct Offset2D {
    int32_t x = 0;
    int32_t y = 0;
};
struct Offset3D {
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
};
struct Extent2D {
    uint32_t width = 0;
    uint32_t height = 0;
};
struct Extent3D {
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
};
struct Viewport {
    float x = 0.f;
    float y = 0.f;
    float width = 0.f;
    float height = 0.f;
    float minDepth = 0.f;
    float maxDepth = 0.f;
};
struct Rect2D {
    Offset2D offset;
    Extent2D extent;
};
struct ClearRect {
    Rect2D rect;
    uint32_t baseArrayLayer = 0;
    uint32_t layerCount = 0;
};
struct ComponentMapping {
    ComponentSwizzle r = static_cast<ComponentSwizzle>(0);
    ComponentSwizzle g = static_cast<ComponentSwizzle>(0);
    ComponentSwizzle b = static_cast<ComponentSwizzle>(0);
    ComponentSwizzle a = static_cast<ComponentSwizzle>(0);
};
struct PhysicalDeviceProperties {
    uint32_t apiVersion = 0;
    uint32_t driverVersion = 0;
    uint32_t vendorID = 0;
    uint32_t deviceID = 0;
    PhysicalDeviceType deviceType = static_cast<PhysicalDeviceType>(0);
    char deviceName[MAX_PHYSICAL_DEVICE_NAME_SIZE] = {};
    uint8_t pipelineCacheUUID[UUID_SIZE] = {};
    PhysicalDeviceLimits limits;
    PhysicalDeviceSparseProperties sparseProperties;
};
struct ExtensionProperties {
    char extensionName[MAX_EXTENSION_NAME_SIZE] = {};
    uint32_t specVersion = 0;
};
struct LayerProperties {
    char layerName[MAX_EXTENSION_NAME_SIZE] = {};
    uint32_t specVersion = 0;
    uint32_t implementationVersion = 0;
    char description[MAX_DESCRIPTION_SIZE] = {};
};
struct ApplicationInfo {
    StructureType sType = StructureType::eApplicationInfo;
    const void* pNext = nullptr;
    const char* pApplicationName = nullptr;
    uint32_t applicationVersion = 0;
    const char* pEngineName = nullptr;
    uint32_t engineVersion = 0;
    uint32_t apiVersion = 0;
};
struct AllocationCallbacks {
    void* pUserData = nullptr;
    PFN_vkAllocationFunction pfnAllocation;
    PFN_vkReallocationFunction pfnReallocation;
    PFN_vkFreeFunction pfnFree;
    PFN_vkInternalAllocationNotification pfnInternalAllocation;
    PFN_vkInternalFreeNotification pfnInternalFree;
};
struct DeviceQueueCreateInfo {
    StructureType sType = StructureType::eDeviceQueueCreateInfo;
    const void* pNext = nullptr;
    DeviceQueueCreateFlags flags = static_cast<DeviceQueueCreateFlags>(0);
    uint32_t queueFamilyIndex = 0;
    uint32_t queueCount = 0;
    const float* pQueuePriorities = nullptr;
};
struct DeviceCreateInfo {
    StructureType sType = StructureType::eDeviceCreateInfo;
    const void* pNext = nullptr;
    DeviceCreateFlags flags = static_cast<DeviceCreateFlags>(0);
    uint32_t queueCreateInfoCount = 0;
    const DeviceQueueCreateInfo* pQueueCreateInfos = nullptr;
    uint32_t enabledLayerCount = 0;
    const char* const* ppEnabledLayerNames = nullptr;
    uint32_t enabledExtensionCount = 0;
    const char* const* ppEnabledExtensionNames = nullptr;
    const PhysicalDeviceFeatures* pEnabledFeatures = nullptr;
};
struct InstanceCreateInfo {
    StructureType sType = StructureType::eInstanceCreateInfo;
    const void* pNext = nullptr;
    InstanceCreateFlags flags = static_cast<InstanceCreateFlags>(0);
    const ApplicationInfo* pApplicationInfo = nullptr;
    uint32_t enabledLayerCount = 0;
    const char* const* ppEnabledLayerNames = nullptr;
    uint32_t enabledExtensionCount = 0;
    const char* const* ppEnabledExtensionNames = nullptr;
};
struct QueueFamilyProperties {
    QueueFlags queueFlags = static_cast<QueueFlags>(0);
    uint32_t queueCount = 0;
    uint32_t timestampValidBits = 0;
    Extent3D minImageTransferGranularity;
};
struct PhysicalDeviceMemoryProperties {
    uint32_t memoryTypeCount = 0;
    MemoryType memoryTypes[MAX_MEMORY_TYPES];
    uint32_t memoryHeapCount = 0;
    MemoryHeap memoryHeaps[MAX_MEMORY_HEAPS];
};
struct MemoryAllocateInfo {
    StructureType sType = StructureType::eMemoryAllocateInfo;
    const void* pNext = nullptr;
    DeviceSize allocationSize = 0;
    uint32_t memoryTypeIndex = 0;
};
struct MemoryRequirements {
    DeviceSize size = 0;
    DeviceSize alignment = 0;
    uint32_t memoryTypeBits = 0;
};
struct SparseImageFormatProperties {
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
    Extent3D imageGranularity;
    SparseImageFormatFlags flags = static_cast<SparseImageFormatFlags>(0);
};
struct SparseImageMemoryRequirements {
    SparseImageFormatProperties formatProperties;
    uint32_t imageMipTailFirstLod = 0;
    DeviceSize imageMipTailSize = 0;
    DeviceSize imageMipTailOffset = 0;
    DeviceSize imageMipTailStride = 0;
};
struct MemoryType {
    MemoryPropertyFlags propertyFlags = static_cast<MemoryPropertyFlags>(0);
    uint32_t heapIndex = 0;
};
struct MemoryHeap {
    DeviceSize size = 0;
    MemoryHeapFlags flags = static_cast<MemoryHeapFlags>(0);
};
struct MappedMemoryRange {
    StructureType sType = StructureType::eMappedMemoryRange;
    const void* pNext = nullptr;
    DeviceMemory memory;
    DeviceSize offset = 0;
    DeviceSize size = 0;
};
struct FormatProperties {
    FormatFeatureFlags linearTilingFeatures = static_cast<FormatFeatureFlags>(0);
    FormatFeatureFlags optimalTilingFeatures = static_cast<FormatFeatureFlags>(0);
    FormatFeatureFlags bufferFeatures = static_cast<FormatFeatureFlags>(0);
};
struct ImageFormatProperties {
    Extent3D maxExtent;
    uint32_t maxMipLevels = 0;
    uint32_t maxArrayLayers = 0;
    SampleCountFlags sampleCounts = static_cast<SampleCountFlags>(0);
    DeviceSize maxResourceSize = 0;
};
struct DescriptorBufferInfo {
    Buffer buffer;
    DeviceSize offset = 0;
    DeviceSize range = 0;
};
struct DescriptorImageInfo {
    Sampler sampler;
    ImageView imageView;
    ImageLayout imageLayout = static_cast<ImageLayout>(0);
};
struct WriteDescriptorSet {
    StructureType sType = StructureType::eWriteDescriptorSet;
    const void* pNext = nullptr;
    DescriptorSet dstSet;
    uint32_t dstBinding = 0;
    uint32_t dstArrayElement = 0;
    uint32_t descriptorCount = 0;
    DescriptorType descriptorType = static_cast<DescriptorType>(0);
    const DescriptorImageInfo* pImageInfo = nullptr;
    const DescriptorBufferInfo* pBufferInfo = nullptr;
    const BufferView* pTexelBufferView = nullptr;
};
struct CopyDescriptorSet {
    StructureType sType = StructureType::eCopyDescriptorSet;
    const void* pNext = nullptr;
    DescriptorSet srcSet;
    uint32_t srcBinding = 0;
    uint32_t srcArrayElement = 0;
    DescriptorSet dstSet;
    uint32_t dstBinding = 0;
    uint32_t dstArrayElement = 0;
    uint32_t descriptorCount = 0;
};
struct BufferCreateInfo {
    StructureType sType = StructureType::eBufferCreateInfo;
    const void* pNext = nullptr;
    BufferCreateFlags flags = static_cast<BufferCreateFlags>(0);
    DeviceSize size = 0;
    BufferUsageFlags usage = static_cast<BufferUsageFlags>(0);
    SharingMode sharingMode = static_cast<SharingMode>(0);
    uint32_t queueFamilyIndexCount = 0;
    const uint32_t* pQueueFamilyIndices = nullptr;
};
struct BufferViewCreateInfo {
    StructureType sType = StructureType::eBufferViewCreateInfo;
    const void* pNext = nullptr;
    BufferViewCreateFlags flags = static_cast<BufferViewCreateFlags>(0);
    Buffer buffer;
    Format format = static_cast<Format>(0);
    DeviceSize offset = 0;
    DeviceSize range = 0;
};
struct ImageSubresource {
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
    uint32_t mipLevel = 0;
    uint32_t arrayLayer = 0;
};
struct ImageSubresourceLayers {
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
    uint32_t mipLevel = 0;
    uint32_t baseArrayLayer = 0;
    uint32_t layerCount = 0;
};
struct ImageSubresourceRange {
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
    uint32_t baseMipLevel = 0;
    uint32_t levelCount = 0;
    uint32_t baseArrayLayer = 0;
    uint32_t layerCount = 0;
};
struct MemoryBarrier {
    StructureType sType = StructureType::eMemoryBarrier;
    const void* pNext = nullptr;
    AccessFlags srcAccessMask = static_cast<AccessFlags>(0);
    AccessFlags dstAccessMask = static_cast<AccessFlags>(0);
};
struct BufferMemoryBarrier {
    StructureType sType = StructureType::eBufferMemoryBarrier;
    const void* pNext = nullptr;
    AccessFlags srcAccessMask = static_cast<AccessFlags>(0);
    AccessFlags dstAccessMask = static_cast<AccessFlags>(0);
    uint32_t srcQueueFamilyIndex = 0;
    uint32_t dstQueueFamilyIndex = 0;
    Buffer buffer;
    DeviceSize offset = 0;
    DeviceSize size = 0;
};
struct ImageMemoryBarrier {
    StructureType sType = StructureType::eImageMemoryBarrier;
    const void* pNext = nullptr;
    AccessFlags srcAccessMask = static_cast<AccessFlags>(0);
    AccessFlags dstAccessMask = static_cast<AccessFlags>(0);
    ImageLayout oldLayout = static_cast<ImageLayout>(0);
    ImageLayout newLayout = static_cast<ImageLayout>(0);
    uint32_t srcQueueFamilyIndex = 0;
    uint32_t dstQueueFamilyIndex = 0;
    Image image;
    ImageSubresourceRange subresourceRange;
};
struct ImageCreateInfo {
    StructureType sType = StructureType::eImageCreateInfo;
    const void* pNext = nullptr;
    ImageCreateFlags flags = static_cast<ImageCreateFlags>(0);
    ImageType imageType = static_cast<ImageType>(0);
    Format format = static_cast<Format>(0);
    Extent3D extent;
    uint32_t mipLevels = 0;
    uint32_t arrayLayers = 0;
    SampleCountFlagBits samples = static_cast<SampleCountFlagBits>(0);
    ImageTiling tiling = static_cast<ImageTiling>(0);
    ImageUsageFlags usage = static_cast<ImageUsageFlags>(0);
    SharingMode sharingMode = static_cast<SharingMode>(0);
    uint32_t queueFamilyIndexCount = 0;
    const uint32_t* pQueueFamilyIndices = nullptr;
    ImageLayout initialLayout = static_cast<ImageLayout>(0);
};
struct SubresourceLayout {
    DeviceSize offset = 0;
    DeviceSize size = 0;
    DeviceSize rowPitch = 0;
    DeviceSize arrayPitch = 0;
    DeviceSize depthPitch = 0;
};
struct ImageViewCreateInfo {
    StructureType sType = StructureType::eImageViewCreateInfo;
    const void* pNext = nullptr;
    ImageViewCreateFlags flags = static_cast<ImageViewCreateFlags>(0);
    Image image;
    ImageViewType viewType = static_cast<ImageViewType>(0);
    Format format = static_cast<Format>(0);
    ComponentMapping components;
    ImageSubresourceRange subresourceRange;
};
struct BufferCopy {
    DeviceSize srcOffset = 0;
    DeviceSize dstOffset = 0;
    DeviceSize size = 0;
};
struct SparseMemoryBind {
    DeviceSize resourceOffset = 0;
    DeviceSize size = 0;
    DeviceMemory memory;
    DeviceSize memoryOffset = 0;
    SparseMemoryBindFlags flags = static_cast<SparseMemoryBindFlags>(0);
};
struct SparseImageMemoryBind {
    ImageSubresource subresource;
    Offset3D offset;
    Extent3D extent;
    DeviceMemory memory;
    DeviceSize memoryOffset = 0;
    SparseMemoryBindFlags flags = static_cast<SparseMemoryBindFlags>(0);
};
struct SparseBufferMemoryBindInfo {
    Buffer buffer;
    uint32_t bindCount = 0;
    const SparseMemoryBind* pBinds = nullptr;
};
struct SparseImageOpaqueMemoryBindInfo {
    Image image;
    uint32_t bindCount = 0;
    const SparseMemoryBind* pBinds = nullptr;
};
struct SparseImageMemoryBindInfo {
    Image image;
    uint32_t bindCount = 0;
    const SparseImageMemoryBind* pBinds = nullptr;
};
struct BindSparseInfo {
    StructureType sType = StructureType::eBindSparseInfo;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount = 0;
    const Semaphore* pWaitSemaphores = nullptr;
    uint32_t bufferBindCount = 0;
    const SparseBufferMemoryBindInfo* pBufferBinds = nullptr;
    uint32_t imageOpaqueBindCount = 0;
    const SparseImageOpaqueMemoryBindInfo* pImageOpaqueBinds = nullptr;
    uint32_t imageBindCount = 0;
    const SparseImageMemoryBindInfo* pImageBinds = nullptr;
    uint32_t signalSemaphoreCount = 0;
    const Semaphore* pSignalSemaphores = nullptr;
};
struct ImageCopy {
    ImageSubresourceLayers srcSubresource;
    Offset3D srcOffset;
    ImageSubresourceLayers dstSubresource;
    Offset3D dstOffset;
    Extent3D extent;
};
struct ImageBlit {
    ImageSubresourceLayers srcSubresource;
    Offset3D srcOffsets[2];
    ImageSubresourceLayers dstSubresource;
    Offset3D dstOffsets[2];
};
struct BufferImageCopy {
    DeviceSize bufferOffset = 0;
    uint32_t bufferRowLength = 0;
    uint32_t bufferImageHeight = 0;
    ImageSubresourceLayers imageSubresource;
    Offset3D imageOffset;
    Extent3D imageExtent;
};
struct ImageResolve {
    ImageSubresourceLayers srcSubresource;
    Offset3D srcOffset;
    ImageSubresourceLayers dstSubresource;
    Offset3D dstOffset;
    Extent3D extent;
};
struct ShaderModuleCreateInfo {
    StructureType sType = StructureType::eShaderModuleCreateInfo;
    const void* pNext = nullptr;
    ShaderModuleCreateFlags flags = static_cast<ShaderModuleCreateFlags>(0);
    size_t codeSize = 0;
    const uint32_t* pCode = nullptr;
};
struct DescriptorSetLayoutBinding {
    uint32_t binding = 0;
    DescriptorType descriptorType = static_cast<DescriptorType>(0);
    uint32_t descriptorCount = 0;
    ShaderStageFlags stageFlags = static_cast<ShaderStageFlags>(0);
    const Sampler* pImmutableSamplers = nullptr;
};
struct DescriptorSetLayoutCreateInfo {
    StructureType sType = StructureType::eDescriptorSetLayoutCreateInfo;
    const void* pNext = nullptr;
    DescriptorSetLayoutCreateFlags flags = static_cast<DescriptorSetLayoutCreateFlags>(0);
    uint32_t bindingCount = 0;
    const DescriptorSetLayoutBinding* pBindings = nullptr;
};
struct DescriptorPoolSize {
    DescriptorType type = static_cast<DescriptorType>(0);
    uint32_t descriptorCount = 0;
};
struct DescriptorPoolCreateInfo {
    StructureType sType = StructureType::eDescriptorPoolCreateInfo;
    const void* pNext = nullptr;
    DescriptorPoolCreateFlags flags = static_cast<DescriptorPoolCreateFlags>(0);
    uint32_t maxSets = 0;
    uint32_t poolSizeCount = 0;
    const DescriptorPoolSize* pPoolSizes = nullptr;
};
struct DescriptorSetAllocateInfo {
    StructureType sType = StructureType::eDescriptorSetAllocateInfo;
    const void* pNext = nullptr;
    DescriptorPool descriptorPool;
    uint32_t descriptorSetCount = 0;
    const DescriptorSetLayout* pSetLayouts = nullptr;
};
struct SpecializationMapEntry {
    uint32_t constantID = 0;
    uint32_t offset = 0;
    size_t size = 0;
};
struct SpecializationInfo {
    uint32_t mapEntryCount = 0;
    const SpecializationMapEntry* pMapEntries = nullptr;
    size_t dataSize = 0;
    const void* pData = nullptr;
};
struct PipelineShaderStageCreateInfo {
    StructureType sType = StructureType::ePipelineShaderStageCreateInfo;
    const void* pNext = nullptr;
    PipelineShaderStageCreateFlags flags = static_cast<PipelineShaderStageCreateFlags>(0);
    ShaderStageFlagBits stage = static_cast<ShaderStageFlagBits>(0);
    ShaderModule module;
    const char* pName = nullptr;
    const SpecializationInfo* pSpecializationInfo = nullptr;
};
struct ComputePipelineCreateInfo {
    StructureType sType = StructureType::eComputePipelineCreateInfo;
    const void* pNext = nullptr;
    PipelineCreateFlags flags = static_cast<PipelineCreateFlags>(0);
    PipelineShaderStageCreateInfo stage;
    PipelineLayout layout;
    Pipeline basePipelineHandle;
    int32_t basePipelineIndex = 0;
};
struct VertexInputBindingDescription {
    uint32_t binding = 0;
    uint32_t stride = 0;
    VertexInputRate inputRate = static_cast<VertexInputRate>(0);
};
struct VertexInputAttributeDescription {
    uint32_t location = 0;
    uint32_t binding = 0;
    Format format = static_cast<Format>(0);
    uint32_t offset = 0;
};
struct PipelineVertexInputStateCreateInfo {
    StructureType sType = StructureType::ePipelineVertexInputStateCreateInfo;
    const void* pNext = nullptr;
    PipelineVertexInputStateCreateFlags flags = static_cast<PipelineVertexInputStateCreateFlags>(0);
    uint32_t vertexBindingDescriptionCount = 0;
    const VertexInputBindingDescription* pVertexBindingDescriptions = nullptr;
    uint32_t vertexAttributeDescriptionCount = 0;
    const VertexInputAttributeDescription* pVertexAttributeDescriptions = nullptr;
};
struct PipelineInputAssemblyStateCreateInfo {
    StructureType sType = StructureType::ePipelineInputAssemblyStateCreateInfo;
    const void* pNext = nullptr;
    PipelineInputAssemblyStateCreateFlags flags = static_cast<PipelineInputAssemblyStateCreateFlags>(0);
    PrimitiveTopology topology = static_cast<PrimitiveTopology>(0);
    bool primitiveRestartEnable = false;
};
struct PipelineTessellationStateCreateInfo {
    StructureType sType = StructureType::ePipelineTessellationStateCreateInfo;
    const void* pNext = nullptr;
    PipelineTessellationStateCreateFlags flags = static_cast<PipelineTessellationStateCreateFlags>(0);
    uint32_t patchControlPoints = 0;
};
struct PipelineViewportStateCreateInfo {
    StructureType sType = StructureType::ePipelineViewportStateCreateInfo;
    const void* pNext = nullptr;
    PipelineViewportStateCreateFlags flags = static_cast<PipelineViewportStateCreateFlags>(0);
    uint32_t viewportCount = 0;
    const Viewport* pViewports = nullptr;
    uint32_t scissorCount = 0;
    const Rect2D* pScissors = nullptr;
};
struct PipelineRasterizationStateCreateInfo {
    StructureType sType = StructureType::ePipelineRasterizationStateCreateInfo;
    const void* pNext = nullptr;
    PipelineRasterizationStateCreateFlags flags = static_cast<PipelineRasterizationStateCreateFlags>(0);
    bool depthClampEnable = false;
    bool rasterizerDiscardEnable = false;
    PolygonMode polygonMode = static_cast<PolygonMode>(0);
    CullModeFlags cullMode = static_cast<CullModeFlags>(0);
    FrontFace frontFace = static_cast<FrontFace>(0);
    bool depthBiasEnable = false;
    float depthBiasConstantFactor = 0.f;
    float depthBiasClamp = 0.f;
    float depthBiasSlopeFactor = 0.f;
    float lineWidth = 0.f;
};
struct PipelineMultisampleStateCreateInfo {
    StructureType sType = StructureType::ePipelineMultisampleStateCreateInfo;
    const void* pNext = nullptr;
    PipelineMultisampleStateCreateFlags flags = static_cast<PipelineMultisampleStateCreateFlags>(0);
    SampleCountFlagBits rasterizationSamples = static_cast<SampleCountFlagBits>(0);
    bool sampleShadingEnable = false;
    float minSampleShading = 0.f;
    const SampleMask* pSampleMask = nullptr;
    bool alphaToCoverageEnable = false;
    bool alphaToOneEnable = false;
};
struct PipelineColorBlendAttachmentState {
    bool blendEnable = false;
    BlendFactor srcColorBlendFactor = static_cast<BlendFactor>(0);
    BlendFactor dstColorBlendFactor = static_cast<BlendFactor>(0);
    BlendOp colorBlendOp = static_cast<BlendOp>(0);
    BlendFactor srcAlphaBlendFactor = static_cast<BlendFactor>(0);
    BlendFactor dstAlphaBlendFactor = static_cast<BlendFactor>(0);
    BlendOp alphaBlendOp = static_cast<BlendOp>(0);
    ColorComponentFlags colorWriteMask = static_cast<ColorComponentFlags>(0);
};
struct PipelineColorBlendStateCreateInfo {
    StructureType sType = StructureType::ePipelineColorBlendStateCreateInfo;
    const void* pNext = nullptr;
    PipelineColorBlendStateCreateFlags flags = static_cast<PipelineColorBlendStateCreateFlags>(0);
    bool logicOpEnable = false;
    LogicOp logicOp = static_cast<LogicOp>(0);
    uint32_t attachmentCount = 0;
    const PipelineColorBlendAttachmentState* pAttachments = nullptr;
    float blendConstants[4] = {};
};
struct PipelineDynamicStateCreateInfo {
    StructureType sType = StructureType::ePipelineDynamicStateCreateInfo;
    const void* pNext = nullptr;
    PipelineDynamicStateCreateFlags flags = static_cast<PipelineDynamicStateCreateFlags>(0);
    uint32_t dynamicStateCount = 0;
    const DynamicState* pDynamicStates = nullptr;
};
struct StencilOpState {
    StencilOp failOp = static_cast<StencilOp>(0);
    StencilOp passOp = static_cast<StencilOp>(0);
    StencilOp depthFailOp = static_cast<StencilOp>(0);
    CompareOp compareOp = static_cast<CompareOp>(0);
    uint32_t compareMask = 0;
    uint32_t writeMask = 0;
    uint32_t reference = 0;
};
struct PipelineDepthStencilStateCreateInfo {
    StructureType sType = StructureType::ePipelineDepthStencilStateCreateInfo;
    const void* pNext = nullptr;
    PipelineDepthStencilStateCreateFlags flags = static_cast<PipelineDepthStencilStateCreateFlags>(0);
    bool depthTestEnable = false;
    bool depthWriteEnable = false;
    CompareOp depthCompareOp = static_cast<CompareOp>(0);
    bool depthBoundsTestEnable = false;
    bool stencilTestEnable = false;
    StencilOpState front;
    StencilOpState back;
    float minDepthBounds = 0.f;
    float maxDepthBounds = 0.f;
};
struct GraphicsPipelineCreateInfo {
    StructureType sType = StructureType::eGraphicsPipelineCreateInfo;
    const void* pNext = nullptr;
    PipelineCreateFlags flags = static_cast<PipelineCreateFlags>(0);
    uint32_t stageCount = 0;
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
    PipelineLayout layout;
    RenderPass renderPass;
    uint32_t subpass = 0;
    Pipeline basePipelineHandle;
    int32_t basePipelineIndex = 0;
};
struct PipelineCacheCreateInfo {
    StructureType sType = StructureType::ePipelineCacheCreateInfo;
    const void* pNext = nullptr;
    PipelineCacheCreateFlags flags = static_cast<PipelineCacheCreateFlags>(0);
    size_t initialDataSize = 0;
    const void* pInitialData = nullptr;
};
struct PushConstantRange {
    ShaderStageFlags stageFlags = static_cast<ShaderStageFlags>(0);
    uint32_t offset = 0;
    uint32_t size = 0;
};
struct PipelineLayoutCreateInfo {
    StructureType sType = StructureType::ePipelineLayoutCreateInfo;
    const void* pNext = nullptr;
    PipelineLayoutCreateFlags flags = static_cast<PipelineLayoutCreateFlags>(0);
    uint32_t setLayoutCount = 0;
    const DescriptorSetLayout* pSetLayouts = nullptr;
    uint32_t pushConstantRangeCount = 0;
    const PushConstantRange* pPushConstantRanges = nullptr;
};
struct SamplerCreateInfo {
    StructureType sType = StructureType::eSamplerCreateInfo;
    const void* pNext = nullptr;
    SamplerCreateFlags flags = static_cast<SamplerCreateFlags>(0);
    Filter magFilter = static_cast<Filter>(0);
    Filter minFilter = static_cast<Filter>(0);
    SamplerMipmapMode mipmapMode = static_cast<SamplerMipmapMode>(0);
    SamplerAddressMode addressModeU = static_cast<SamplerAddressMode>(0);
    SamplerAddressMode addressModeV = static_cast<SamplerAddressMode>(0);
    SamplerAddressMode addressModeW = static_cast<SamplerAddressMode>(0);
    float mipLodBias = 0.f;
    bool anisotropyEnable = false;
    float maxAnisotropy = 0.f;
    bool compareEnable = false;
    CompareOp compareOp = static_cast<CompareOp>(0);
    float minLod = 0.f;
    float maxLod = 0.f;
    BorderColor borderColor = static_cast<BorderColor>(0);
    bool unnormalizedCoordinates = false;
};
struct CommandPoolCreateInfo {
    StructureType sType = StructureType::eCommandPoolCreateInfo;
    const void* pNext = nullptr;
    CommandPoolCreateFlags flags = static_cast<CommandPoolCreateFlags>(0);
    uint32_t queueFamilyIndex = 0;
};
struct CommandBufferAllocateInfo {
    StructureType sType = StructureType::eCommandBufferAllocateInfo;
    const void* pNext = nullptr;
    CommandPool commandPool;
    CommandBufferLevel level = static_cast<CommandBufferLevel>(0);
    uint32_t commandBufferCount = 0;
};
struct CommandBufferInheritanceInfo {
    StructureType sType = StructureType::eCommandBufferInheritanceInfo;
    const void* pNext = nullptr;
    RenderPass renderPass;
    uint32_t subpass = 0;
    Framebuffer framebuffer;
    bool occlusionQueryEnable = false;
    QueryControlFlags queryFlags = static_cast<QueryControlFlags>(0);
    QueryPipelineStatisticFlags pipelineStatistics = static_cast<QueryPipelineStatisticFlags>(0);
};
struct CommandBufferBeginInfo {
    StructureType sType = StructureType::eCommandBufferBeginInfo;
    const void* pNext = nullptr;
    CommandBufferUsageFlags flags = static_cast<CommandBufferUsageFlags>(0);
    const CommandBufferInheritanceInfo* pInheritanceInfo = nullptr;
};
struct RenderPassBeginInfo {
    StructureType sType = StructureType::eRenderPassBeginInfo;
    const void* pNext = nullptr;
    RenderPass renderPass;
    Framebuffer framebuffer;
    Rect2D renderArea;
    uint32_t clearValueCount = 0;
    const ClearValue* pClearValues = nullptr;
};
struct ClearDepthStencilValue {
    float depth = 0.f;
    uint32_t stencil = 0;
};
struct ClearAttachment {
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
    uint32_t colorAttachment = 0;
    ClearValue clearValue;
};
struct AttachmentDescription {
    AttachmentDescriptionFlags flags = static_cast<AttachmentDescriptionFlags>(0);
    Format format = static_cast<Format>(0);
    SampleCountFlagBits samples = static_cast<SampleCountFlagBits>(0);
    AttachmentLoadOp loadOp = static_cast<AttachmentLoadOp>(0);
    AttachmentStoreOp storeOp = static_cast<AttachmentStoreOp>(0);
    AttachmentLoadOp stencilLoadOp = static_cast<AttachmentLoadOp>(0);
    AttachmentStoreOp stencilStoreOp = static_cast<AttachmentStoreOp>(0);
    ImageLayout initialLayout = static_cast<ImageLayout>(0);
    ImageLayout finalLayout = static_cast<ImageLayout>(0);
};
struct AttachmentReference {
    uint32_t attachment = 0;
    ImageLayout layout = static_cast<ImageLayout>(0);
};
struct SubpassDescription {
    SubpassDescriptionFlags flags = static_cast<SubpassDescriptionFlags>(0);
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    uint32_t inputAttachmentCount = 0;
    const AttachmentReference* pInputAttachments = nullptr;
    uint32_t colorAttachmentCount = 0;
    const AttachmentReference* pColorAttachments = nullptr;
    const AttachmentReference* pResolveAttachments = nullptr;
    const AttachmentReference* pDepthStencilAttachment = nullptr;
    uint32_t preserveAttachmentCount = 0;
    const uint32_t* pPreserveAttachments = nullptr;
};
struct SubpassDependency {
    uint32_t srcSubpass = 0;
    uint32_t dstSubpass = 0;
    PipelineStageFlags srcStageMask = static_cast<PipelineStageFlags>(0);
    PipelineStageFlags dstStageMask = static_cast<PipelineStageFlags>(0);
    AccessFlags srcAccessMask = static_cast<AccessFlags>(0);
    AccessFlags dstAccessMask = static_cast<AccessFlags>(0);
    DependencyFlags dependencyFlags = static_cast<DependencyFlags>(0);
};
struct RenderPassCreateInfo {
    StructureType sType = StructureType::eRenderPassCreateInfo;
    const void* pNext = nullptr;
    RenderPassCreateFlags flags = static_cast<RenderPassCreateFlags>(0);
    uint32_t attachmentCount = 0;
    const AttachmentDescription* pAttachments = nullptr;
    uint32_t subpassCount = 0;
    const SubpassDescription* pSubpasses = nullptr;
    uint32_t dependencyCount = 0;
    const SubpassDependency* pDependencies = nullptr;
};
struct EventCreateInfo {
    StructureType sType = StructureType::eEventCreateInfo;
    const void* pNext = nullptr;
    EventCreateFlags flags = static_cast<EventCreateFlags>(0);
};
struct FenceCreateInfo {
    StructureType sType = StructureType::eFenceCreateInfo;
    const void* pNext = nullptr;
    FenceCreateFlags flags = static_cast<FenceCreateFlags>(0);
};
struct PhysicalDeviceFeatures {
    bool robustBufferAccess = false;
    bool fullDrawIndexUint32 = false;
    bool imageCubeArray = false;
    bool independentBlend = false;
    bool geometryShader = false;
    bool tessellationShader = false;
    bool sampleRateShading = false;
    bool dualSrcBlend = false;
    bool logicOp = false;
    bool multiDrawIndirect = false;
    bool drawIndirectFirstInstance = false;
    bool depthClamp = false;
    bool depthBiasClamp = false;
    bool fillModeNonSolid = false;
    bool depthBounds = false;
    bool wideLines = false;
    bool largePoints = false;
    bool alphaToOne = false;
    bool multiViewport = false;
    bool samplerAnisotropy = false;
    bool textureCompressionETC2 = false;
    bool textureCompressionASTC_LDR = false;
    bool textureCompressionBC = false;
    bool occlusionQueryPrecise = false;
    bool pipelineStatisticsQuery = false;
    bool vertexPipelineStoresAndAtomics = false;
    bool fragmentStoresAndAtomics = false;
    bool shaderTessellationAndGeometryPointSize = false;
    bool shaderImageGatherExtended = false;
    bool shaderStorageImageExtendedFormats = false;
    bool shaderStorageImageMultisample = false;
    bool shaderStorageImageReadWithoutFormat = false;
    bool shaderStorageImageWriteWithoutFormat = false;
    bool shaderUniformBufferArrayDynamicIndexing = false;
    bool shaderSampledImageArrayDynamicIndexing = false;
    bool shaderStorageBufferArrayDynamicIndexing = false;
    bool shaderStorageImageArrayDynamicIndexing = false;
    bool shaderClipDistance = false;
    bool shaderCullDistance = false;
    bool shaderFloat64 = false;
    bool shaderInt64 = false;
    bool shaderInt16 = false;
    bool shaderResourceResidency = false;
    bool shaderResourceMinLod = false;
    bool sparseBinding = false;
    bool sparseResidencyBuffer = false;
    bool sparseResidencyImage2D = false;
    bool sparseResidencyImage3D = false;
    bool sparseResidency2Samples = false;
    bool sparseResidency4Samples = false;
    bool sparseResidency8Samples = false;
    bool sparseResidency16Samples = false;
    bool sparseResidencyAliased = false;
    bool variableMultisampleRate = false;
    bool inheritedQueries = false;
};
struct PhysicalDeviceSparseProperties {
    bool residencyStandard2DBlockShape = false;
    bool residencyStandard2DMultisampleBlockShape = false;
    bool residencyStandard3DBlockShape = false;
    bool residencyAlignedMipSize = false;
    bool residencyNonResidentStrict = false;
};
struct PhysicalDeviceLimits {
    uint32_t maxImageDimension1D = 0;
    uint32_t maxImageDimension2D = 0;
    uint32_t maxImageDimension3D = 0;
    uint32_t maxImageDimensionCube = 0;
    uint32_t maxImageArrayLayers = 0;
    uint32_t maxTexelBufferElements = 0;
    uint32_t maxUniformBufferRange = 0;
    uint32_t maxStorageBufferRange = 0;
    uint32_t maxPushConstantsSize = 0;
    uint32_t maxMemoryAllocationCount = 0;
    uint32_t maxSamplerAllocationCount = 0;
    DeviceSize bufferImageGranularity = 0;
    DeviceSize sparseAddressSpaceSize = 0;
    uint32_t maxBoundDescriptorSets = 0;
    uint32_t maxPerStageDescriptorSamplers = 0;
    uint32_t maxPerStageDescriptorUniformBuffers = 0;
    uint32_t maxPerStageDescriptorStorageBuffers = 0;
    uint32_t maxPerStageDescriptorSampledImages = 0;
    uint32_t maxPerStageDescriptorStorageImages = 0;
    uint32_t maxPerStageDescriptorInputAttachments = 0;
    uint32_t maxPerStageResources = 0;
    uint32_t maxDescriptorSetSamplers = 0;
    uint32_t maxDescriptorSetUniformBuffers = 0;
    uint32_t maxDescriptorSetUniformBuffersDynamic = 0;
    uint32_t maxDescriptorSetStorageBuffers = 0;
    uint32_t maxDescriptorSetStorageBuffersDynamic = 0;
    uint32_t maxDescriptorSetSampledImages = 0;
    uint32_t maxDescriptorSetStorageImages = 0;
    uint32_t maxDescriptorSetInputAttachments = 0;
    uint32_t maxVertexInputAttributes = 0;
    uint32_t maxVertexInputBindings = 0;
    uint32_t maxVertexInputAttributeOffset = 0;
    uint32_t maxVertexInputBindingStride = 0;
    uint32_t maxVertexOutputComponents = 0;
    uint32_t maxTessellationGenerationLevel = 0;
    uint32_t maxTessellationPatchSize = 0;
    uint32_t maxTessellationControlPerVertexInputComponents = 0;
    uint32_t maxTessellationControlPerVertexOutputComponents = 0;
    uint32_t maxTessellationControlPerPatchOutputComponents = 0;
    uint32_t maxTessellationControlTotalOutputComponents = 0;
    uint32_t maxTessellationEvaluationInputComponents = 0;
    uint32_t maxTessellationEvaluationOutputComponents = 0;
    uint32_t maxGeometryShaderInvocations = 0;
    uint32_t maxGeometryInputComponents = 0;
    uint32_t maxGeometryOutputComponents = 0;
    uint32_t maxGeometryOutputVertices = 0;
    uint32_t maxGeometryTotalOutputComponents = 0;
    uint32_t maxFragmentInputComponents = 0;
    uint32_t maxFragmentOutputAttachments = 0;
    uint32_t maxFragmentDualSrcAttachments = 0;
    uint32_t maxFragmentCombinedOutputResources = 0;
    uint32_t maxComputeSharedMemorySize = 0;
    uint32_t maxComputeWorkGroupCount[3] = {};
    uint32_t maxComputeWorkGroupInvocations = 0;
    uint32_t maxComputeWorkGroupSize[3] = {};
    uint32_t subPixelPrecisionBits = 0;
    uint32_t subTexelPrecisionBits = 0;
    uint32_t mipmapPrecisionBits = 0;
    uint32_t maxDrawIndexedIndexValue = 0;
    uint32_t maxDrawIndirectCount = 0;
    float maxSamplerLodBias = 0.f;
    float maxSamplerAnisotropy = 0.f;
    uint32_t maxViewports = 0;
    uint32_t maxViewportDimensions[2] = {};
    float viewportBoundsRange[2] = {};
    uint32_t viewportSubPixelBits = 0;
    size_t minMemoryMapAlignment = 0;
    DeviceSize minTexelBufferOffsetAlignment = 0;
    DeviceSize minUniformBufferOffsetAlignment = 0;
    DeviceSize minStorageBufferOffsetAlignment = 0;
    int32_t minTexelOffset = 0;
    uint32_t maxTexelOffset = 0;
    int32_t minTexelGatherOffset = 0;
    uint32_t maxTexelGatherOffset = 0;
    float minInterpolationOffset = 0.f;
    float maxInterpolationOffset = 0.f;
    uint32_t subPixelInterpolationOffsetBits = 0;
    uint32_t maxFramebufferWidth = 0;
    uint32_t maxFramebufferHeight = 0;
    uint32_t maxFramebufferLayers = 0;
    SampleCountFlags framebufferColorSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags framebufferDepthSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags framebufferStencilSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags framebufferNoAttachmentsSampleCounts = static_cast<SampleCountFlags>(0);
    uint32_t maxColorAttachments = 0;
    SampleCountFlags sampledImageColorSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags sampledImageIntegerSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags sampledImageDepthSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags sampledImageStencilSampleCounts = static_cast<SampleCountFlags>(0);
    SampleCountFlags storageImageSampleCounts = static_cast<SampleCountFlags>(0);
    uint32_t maxSampleMaskWords = 0;
    bool timestampComputeAndGraphics = false;
    float timestampPeriod = 0.f;
    uint32_t maxClipDistances = 0;
    uint32_t maxCullDistances = 0;
    uint32_t maxCombinedClipAndCullDistances = 0;
    uint32_t discreteQueuePriorities = 0;
    float pointSizeRange[2] = {};
    float lineWidthRange[2] = {};
    float pointSizeGranularity = 0.f;
    float lineWidthGranularity = 0.f;
    bool strictLines = false;
    bool standardSampleLocations = false;
    DeviceSize optimalBufferCopyOffsetAlignment = 0;
    DeviceSize optimalBufferCopyRowPitchAlignment = 0;
    DeviceSize nonCoherentAtomSize = 0;
};
struct SemaphoreCreateInfo {
    StructureType sType = StructureType::eSemaphoreCreateInfo;
    const void* pNext = nullptr;
    SemaphoreCreateFlags flags = static_cast<SemaphoreCreateFlags>(0);
};
struct QueryPoolCreateInfo {
    StructureType sType = StructureType::eQueryPoolCreateInfo;
    const void* pNext = nullptr;
    QueryPoolCreateFlags flags = static_cast<QueryPoolCreateFlags>(0);
    QueryType queryType = static_cast<QueryType>(0);
    uint32_t queryCount = 0;
    QueryPipelineStatisticFlags pipelineStatistics = static_cast<QueryPipelineStatisticFlags>(0);
};
struct FramebufferCreateInfo {
    StructureType sType = StructureType::eFramebufferCreateInfo;
    const void* pNext = nullptr;
    FramebufferCreateFlags flags = static_cast<FramebufferCreateFlags>(0);
    RenderPass renderPass;
    uint32_t attachmentCount = 0;
    const ImageView* pAttachments = nullptr;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layers = 0;
};
struct DrawIndirectCommand {
    uint32_t vertexCount = 0;
    uint32_t instanceCount = 0;
    uint32_t firstVertex = 0;
    uint32_t firstInstance = 0;
};
struct DrawIndexedIndirectCommand {
    uint32_t indexCount = 0;
    uint32_t instanceCount = 0;
    uint32_t firstIndex = 0;
    int32_t vertexOffset = 0;
    uint32_t firstInstance = 0;
};
struct DispatchIndirectCommand {
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
};
struct SubmitInfo {
    StructureType sType = StructureType::eSubmitInfo;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount = 0;
    const Semaphore* pWaitSemaphores = nullptr;
    const PipelineStageFlags* pWaitDstStageMask = nullptr;
    uint32_t commandBufferCount = 0;
    const CommandBuffer* pCommandBuffers = nullptr;
    uint32_t signalSemaphoreCount = 0;
    const Semaphore* pSignalSemaphores = nullptr;
};
struct DisplayPropertiesKHR {
    DisplayKHR display;
    const char* displayName = nullptr;
    Extent2D physicalDimensions;
    Extent2D physicalResolution;
    SurfaceTransformFlagsKHR supportedTransforms = static_cast<SurfaceTransformFlagsKHR>(0);
    bool planeReorderPossible = false;
    bool persistentContent = false;
};
struct DisplayPlanePropertiesKHR {
    DisplayKHR currentDisplay;
    uint32_t currentStackIndex = 0;
};
struct DisplayModeParametersKHR {
    Extent2D visibleRegion;
    uint32_t refreshRate = 0;
};
struct DisplayModePropertiesKHR {
    DisplayModeKHR displayMode;
    DisplayModeParametersKHR parameters;
};
struct DisplayModeCreateInfoKHR {
    StructureType sType = StructureType::eDisplayModeCreateInfoKHR;
    const void* pNext = nullptr;
    DisplayModeCreateFlagsKHR flags = static_cast<DisplayModeCreateFlagsKHR>(0);
    DisplayModeParametersKHR parameters;
};
struct DisplayPlaneCapabilitiesKHR {
    DisplayPlaneAlphaFlagsKHR supportedAlpha = static_cast<DisplayPlaneAlphaFlagsKHR>(0);
    Offset2D minSrcPosition;
    Offset2D maxSrcPosition;
    Extent2D minSrcExtent;
    Extent2D maxSrcExtent;
    Offset2D minDstPosition;
    Offset2D maxDstPosition;
    Extent2D minDstExtent;
    Extent2D maxDstExtent;
};
struct DisplaySurfaceCreateInfoKHR {
    StructureType sType = StructureType::eDisplaySurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    DisplaySurfaceCreateFlagsKHR flags = static_cast<DisplaySurfaceCreateFlagsKHR>(0);
    DisplayModeKHR displayMode;
    uint32_t planeIndex = 0;
    uint32_t planeStackIndex = 0;
    SurfaceTransformFlagBitsKHR transform = static_cast<SurfaceTransformFlagBitsKHR>(0);
    float globalAlpha = 0.f;
    DisplayPlaneAlphaFlagBitsKHR alphaMode = static_cast<DisplayPlaneAlphaFlagBitsKHR>(0);
    Extent2D imageExtent;
};
struct DisplayPresentInfoKHR {
    StructureType sType = StructureType::eDisplayPresentInfoKHR;
    const void* pNext = nullptr;
    Rect2D srcRect;
    Rect2D dstRect;
    bool persistent = false;
};
struct SurfaceCapabilitiesKHR {
    uint32_t minImageCount = 0;
    uint32_t maxImageCount = 0;
    Extent2D currentExtent;
    Extent2D minImageExtent;
    Extent2D maxImageExtent;
    uint32_t maxImageArrayLayers = 0;
    SurfaceTransformFlagsKHR supportedTransforms = static_cast<SurfaceTransformFlagsKHR>(0);
    SurfaceTransformFlagBitsKHR currentTransform = static_cast<SurfaceTransformFlagBitsKHR>(0);
    CompositeAlphaFlagsKHR supportedCompositeAlpha = static_cast<CompositeAlphaFlagsKHR>(0);
    ImageUsageFlags supportedUsageFlags = static_cast<ImageUsageFlags>(0);
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct AndroidSurfaceCreateInfoKHR {
    StructureType sType = StructureType::eAndroidSurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    AndroidSurfaceCreateFlagsKHR flags = static_cast<AndroidSurfaceCreateFlagsKHR>(0);
    ANativeWindow* window = nullptr;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_VI_NN)
struct ViSurfaceCreateInfoNN {
    StructureType sType = StructureType::eViSurfaceCreateInfoNN;
    const void* pNext = nullptr;
    ViSurfaceCreateFlagsNN flags = static_cast<ViSurfaceCreateFlagsNN>(0);
    void* window = nullptr;
};
#endif // VK_USE_PLATFORM_VI_NN
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
struct WaylandSurfaceCreateInfoKHR {
    StructureType sType = StructureType::eWaylandSurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    WaylandSurfaceCreateFlagsKHR flags = static_cast<WaylandSurfaceCreateFlagsKHR>(0);
    wl_display* display = nullptr;
    wl_surface* surface = nullptr;
};
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct Win32SurfaceCreateInfoKHR {
    StructureType sType = StructureType::eWin32SurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    Win32SurfaceCreateFlagsKHR flags = static_cast<Win32SurfaceCreateFlagsKHR>(0);
    HINSTANCE hinstance;
    HWND hwnd;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
struct XlibSurfaceCreateInfoKHR {
    StructureType sType = StructureType::eXlibSurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    XlibSurfaceCreateFlagsKHR flags = static_cast<XlibSurfaceCreateFlagsKHR>(0);
    Display* dpy = nullptr;
    Window window;
};
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
struct XcbSurfaceCreateInfoKHR {
    StructureType sType = StructureType::eXcbSurfaceCreateInfoKHR;
    const void* pNext = nullptr;
    XcbSurfaceCreateFlagsKHR flags = static_cast<XcbSurfaceCreateFlagsKHR>(0);
    xcb_connection_t* connection = nullptr;
    xcb_window_t window;
};
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct ImagePipeSurfaceCreateInfoFUCHSIA {
    StructureType sType = StructureType::eImagepipeSurfaceCreateInfoFUCHSIA;
    const void* pNext = nullptr;
    ImagePipeSurfaceCreateFlagsFUCHSIA flags = static_cast<ImagePipeSurfaceCreateFlagsFUCHSIA>(0);
    zx_handle_t imagePipeHandle;
};
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_GGP)
struct StreamDescriptorSurfaceCreateInfoGGP {
    StructureType sType = StructureType::eStreamDescriptorSurfaceCreateInfoGGP;
    const void* pNext = nullptr;
    StreamDescriptorSurfaceCreateFlagsGGP flags = static_cast<StreamDescriptorSurfaceCreateFlagsGGP>(0);
    GgpStreamDescriptor streamDescriptor;
};
#endif // VK_USE_PLATFORM_GGP
struct SurfaceFormatKHR {
    Format format = static_cast<Format>(0);
    ColorSpaceKHR colorSpace = static_cast<ColorSpaceKHR>(0);
};
struct SwapchainCreateInfoKHR {
    StructureType sType = StructureType::eSwapchainCreateInfoKHR;
    const void* pNext = nullptr;
    SwapchainCreateFlagsKHR flags = static_cast<SwapchainCreateFlagsKHR>(0);
    SurfaceKHR surface;
    uint32_t minImageCount = 0;
    Format imageFormat = static_cast<Format>(0);
    ColorSpaceKHR imageColorSpace = static_cast<ColorSpaceKHR>(0);
    Extent2D imageExtent;
    uint32_t imageArrayLayers = 0;
    ImageUsageFlags imageUsage = static_cast<ImageUsageFlags>(0);
    SharingMode imageSharingMode = static_cast<SharingMode>(0);
    uint32_t queueFamilyIndexCount = 0;
    const uint32_t* pQueueFamilyIndices = nullptr;
    SurfaceTransformFlagBitsKHR preTransform = static_cast<SurfaceTransformFlagBitsKHR>(0);
    CompositeAlphaFlagBitsKHR compositeAlpha = static_cast<CompositeAlphaFlagBitsKHR>(0);
    PresentModeKHR presentMode = static_cast<PresentModeKHR>(0);
    bool clipped = false;
    SwapchainKHR oldSwapchain;
};
struct PresentInfoKHR {
    StructureType sType = StructureType::ePresentInfoKHR;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount = 0;
    const Semaphore* pWaitSemaphores = nullptr;
    uint32_t swapchainCount = 0;
    const SwapchainKHR* pSwapchains = nullptr;
    const uint32_t* pImageIndices = nullptr;
    Result* pResults = nullptr;
};
struct DebugReportCallbackCreateInfoEXT {
    StructureType sType = StructureType::eDebugReportCallbackCreateInfoEXT;
    const void* pNext = nullptr;
    DebugReportFlagsEXT flags = static_cast<DebugReportFlagsEXT>(0);
    PFN_vkDebugReportCallbackEXT pfnCallback;
    void* pUserData = nullptr;
};
struct ValidationFlagsEXT {
    StructureType sType = StructureType::eValidationFlagsEXT;
    const void* pNext = nullptr;
    uint32_t disabledValidationCheckCount = 0;
    const ValidationCheckEXT* pDisabledValidationChecks = nullptr;
};
struct ValidationFeaturesEXT {
    StructureType sType = StructureType::eValidationFeaturesEXT;
    const void* pNext = nullptr;
    uint32_t enabledValidationFeatureCount = 0;
    const ValidationFeatureEnableEXT* pEnabledValidationFeatures = nullptr;
    uint32_t disabledValidationFeatureCount = 0;
    const ValidationFeatureDisableEXT* pDisabledValidationFeatures = nullptr;
};
struct PipelineRasterizationStateRasterizationOrderAMD {
    StructureType sType = StructureType::ePipelineRasterizationStateRasterizationOrderAMD;
    const void* pNext = nullptr;
    RasterizationOrderAMD rasterizationOrder = static_cast<RasterizationOrderAMD>(0);
};
struct DebugMarkerObjectNameInfoEXT {
    StructureType sType = StructureType::eDebugMarkerObjectNameInfoEXT;
    const void* pNext = nullptr;
    DebugReportObjectTypeEXT objectType = static_cast<DebugReportObjectTypeEXT>(0);
    uint64_t object = 0;
    const char* pObjectName = nullptr;
};
struct DebugMarkerObjectTagInfoEXT {
    StructureType sType = StructureType::eDebugMarkerObjectTagInfoEXT;
    const void* pNext = nullptr;
    DebugReportObjectTypeEXT objectType = static_cast<DebugReportObjectTypeEXT>(0);
    uint64_t object = 0;
    uint64_t tagName = 0;
    size_t tagSize = 0;
    const void* pTag = nullptr;
};
struct DebugMarkerMarkerInfoEXT {
    StructureType sType = StructureType::eDebugMarkerMarkerInfoEXT;
    const void* pNext = nullptr;
    const char* pMarkerName = nullptr;
    float color[4] = {};
};
struct DedicatedAllocationImageCreateInfoNV {
    StructureType sType = StructureType::eDedicatedAllocationImageCreateInfoNV;
    const void* pNext = nullptr;
    bool dedicatedAllocation = false;
};
struct DedicatedAllocationBufferCreateInfoNV {
    StructureType sType = StructureType::eDedicatedAllocationBufferCreateInfoNV;
    const void* pNext = nullptr;
    bool dedicatedAllocation = false;
};
struct DedicatedAllocationMemoryAllocateInfoNV {
    StructureType sType = StructureType::eDedicatedAllocationMemoryAllocateInfoNV;
    const void* pNext = nullptr;
    Image image;
    Buffer buffer;
};
struct ExternalImageFormatPropertiesNV {
    ImageFormatProperties imageFormatProperties;
    ExternalMemoryFeatureFlagsNV externalMemoryFeatures = static_cast<ExternalMemoryFeatureFlagsNV>(0);
    ExternalMemoryHandleTypeFlagsNV exportFromImportedHandleTypes = static_cast<ExternalMemoryHandleTypeFlagsNV>(0);
    ExternalMemoryHandleTypeFlagsNV compatibleHandleTypes = static_cast<ExternalMemoryHandleTypeFlagsNV>(0);
};
struct ExternalMemoryImageCreateInfoNV {
    StructureType sType = StructureType::eExternalMemoryImageCreateInfoNV;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleTypes = static_cast<ExternalMemoryHandleTypeFlagsNV>(0);
};
struct ExportMemoryAllocateInfoNV {
    StructureType sType = StructureType::eExportMemoryAllocateInfoNV;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleTypes = static_cast<ExternalMemoryHandleTypeFlagsNV>(0);
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportMemoryWin32HandleInfoNV {
    StructureType sType = StructureType::eImportMemoryWin32HandleInfoNV;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagsNV handleType = static_cast<ExternalMemoryHandleTypeFlagsNV>(0);
    HANDLE handle;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ExportMemoryWin32HandleInfoNV {
    StructureType sType = StructureType::eExportMemoryWin32HandleInfoNV;
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct Win32KeyedMutexAcquireReleaseInfoNV {
    StructureType sType = StructureType::eWin32KeyedMutexAcquireReleaseInfoNV;
    const void* pNext = nullptr;
    uint32_t acquireCount = 0;
    const DeviceMemory* pAcquireSyncs = nullptr;
    const uint64_t* pAcquireKeys = nullptr;
    const uint32_t* pAcquireTimeoutMilliseconds = nullptr;
    uint32_t releaseCount = 0;
    const DeviceMemory* pReleaseSyncs = nullptr;
    const uint64_t* pReleaseKeys = nullptr;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct PhysicalDeviceDeviceGeneratedCommandsFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceDeviceGeneratedCommandsFeaturesNV;
    void* pNext = nullptr;
    bool deviceGeneratedCommands = false;
};
struct PhysicalDeviceDeviceGeneratedCommandsPropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceDeviceGeneratedCommandsPropertiesNV;
    const void* pNext = nullptr;
    uint32_t maxGraphicsShaderGroupCount = 0;
    uint32_t maxIndirectSequenceCount = 0;
    uint32_t maxIndirectCommandsTokenCount = 0;
    uint32_t maxIndirectCommandsStreamCount = 0;
    uint32_t maxIndirectCommandsTokenOffset = 0;
    uint32_t maxIndirectCommandsStreamStride = 0;
    uint32_t minSequencesCountBufferOffsetAlignment = 0;
    uint32_t minSequencesIndexBufferOffsetAlignment = 0;
    uint32_t minIndirectCommandsBufferOffsetAlignment = 0;
};
struct GraphicsShaderGroupCreateInfoNV {
    StructureType sType = StructureType::eGraphicsShaderGroupCreateInfoNV;
    const void* pNext = nullptr;
    uint32_t stageCount = 0;
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    const PipelineVertexInputStateCreateInfo* pVertexInputState = nullptr;
    const PipelineTessellationStateCreateInfo* pTessellationState = nullptr;
};
struct GraphicsPipelineShaderGroupsCreateInfoNV {
    StructureType sType = StructureType::eGraphicsPipelineShaderGroupsCreateInfoNV;
    const void* pNext = nullptr;
    uint32_t groupCount = 0;
    const GraphicsShaderGroupCreateInfoNV* pGroups = nullptr;
    uint32_t pipelineCount = 0;
    const Pipeline* pPipelines = nullptr;
};
struct BindShaderGroupIndirectCommandNV {
    uint32_t groupIndex = 0;
};
struct BindIndexBufferIndirectCommandNV {
    DeviceAddress bufferAddress = 0;
    uint32_t size = 0;
    IndexType indexType = static_cast<IndexType>(0);
};
struct BindVertexBufferIndirectCommandNV {
    DeviceAddress bufferAddress = 0;
    uint32_t size = 0;
    uint32_t stride = 0;
};
struct SetStateFlagsIndirectCommandNV {
    uint32_t data = 0;
};
struct IndirectCommandsStreamNV {
    Buffer buffer;
    DeviceSize offset = 0;
};
struct IndirectCommandsLayoutTokenNV {
    StructureType sType = StructureType::eIndirectCommandsLayoutTokenNV;
    const void* pNext = nullptr;
    IndirectCommandsTokenTypeNV tokenType = static_cast<IndirectCommandsTokenTypeNV>(0);
    uint32_t stream = 0;
    uint32_t offset = 0;
    uint32_t vertexBindingUnit = 0;
    bool vertexDynamicStride = false;
    PipelineLayout pushconstantPipelineLayout;
    ShaderStageFlags pushconstantShaderStageFlags = static_cast<ShaderStageFlags>(0);
    uint32_t pushconstantOffset = 0;
    uint32_t pushconstantSize = 0;
    IndirectStateFlagsNV indirectStateFlags = static_cast<IndirectStateFlagsNV>(0);
    uint32_t indexTypeCount = 0;
    const IndexType* pIndexTypes = nullptr;
    const uint32_t* pIndexTypeValues = nullptr;
};
struct IndirectCommandsLayoutCreateInfoNV {
    StructureType sType = StructureType::eIndirectCommandsLayoutCreateInfoNV;
    const void* pNext = nullptr;
    IndirectCommandsLayoutUsageFlagsNV flags = static_cast<IndirectCommandsLayoutUsageFlagsNV>(0);
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    uint32_t tokenCount = 0;
    const IndirectCommandsLayoutTokenNV* pTokens = nullptr;
    uint32_t streamCount = 0;
    const uint32_t* pStreamStrides = nullptr;
};
struct GeneratedCommandsInfoNV {
    StructureType sType = StructureType::eGeneratedCommandsInfoNV;
    const void* pNext = nullptr;
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    Pipeline pipeline;
    IndirectCommandsLayoutNV indirectCommandsLayout;
    uint32_t streamCount = 0;
    const IndirectCommandsStreamNV* pStreams = nullptr;
    uint32_t sequencesCount = 0;
    Buffer preprocessBuffer;
    DeviceSize preprocessOffset = 0;
    DeviceSize preprocessSize = 0;
    Buffer sequencesCountBuffer;
    DeviceSize sequencesCountOffset = 0;
    Buffer sequencesIndexBuffer;
    DeviceSize sequencesIndexOffset = 0;
};
struct GeneratedCommandsMemoryRequirementsInfoNV {
    StructureType sType = StructureType::eGeneratedCommandsMemoryRequirementsInfoNV;
    const void* pNext = nullptr;
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    Pipeline pipeline;
    IndirectCommandsLayoutNV indirectCommandsLayout;
    uint32_t maxSequencesCount = 0;
};
struct PhysicalDeviceFeatures2 {
    StructureType sType = StructureType::ePhysicalDeviceFeatures2;
    void* pNext = nullptr;
    PhysicalDeviceFeatures features;
};
using PhysicalDeviceFeatures2KHR = PhysicalDeviceFeatures2;
struct PhysicalDeviceProperties2 {
    StructureType sType = StructureType::ePhysicalDeviceProperties2;
    void* pNext = nullptr;
    PhysicalDeviceProperties properties;
};
using PhysicalDeviceProperties2KHR = PhysicalDeviceProperties2;
struct FormatProperties2 {
    StructureType sType = StructureType::eFormatProperties2;
    void* pNext = nullptr;
    FormatProperties formatProperties;
};
using FormatProperties2KHR = FormatProperties2;
struct ImageFormatProperties2 {
    StructureType sType = StructureType::eImageFormatProperties2;
    void* pNext = nullptr;
    ImageFormatProperties imageFormatProperties;
};
using ImageFormatProperties2KHR = ImageFormatProperties2;
struct PhysicalDeviceImageFormatInfo2 {
    StructureType sType = StructureType::ePhysicalDeviceImageFormatInfo2;
    const void* pNext = nullptr;
    Format format = static_cast<Format>(0);
    ImageType type = static_cast<ImageType>(0);
    ImageTiling tiling = static_cast<ImageTiling>(0);
    ImageUsageFlags usage = static_cast<ImageUsageFlags>(0);
    ImageCreateFlags flags = static_cast<ImageCreateFlags>(0);
};
using PhysicalDeviceImageFormatInfo2KHR = PhysicalDeviceImageFormatInfo2;
struct QueueFamilyProperties2 {
    StructureType sType = StructureType::eQueueFamilyProperties2;
    void* pNext = nullptr;
    QueueFamilyProperties queueFamilyProperties;
};
using QueueFamilyProperties2KHR = QueueFamilyProperties2;
struct PhysicalDeviceMemoryProperties2 {
    StructureType sType = StructureType::ePhysicalDeviceMemoryProperties2;
    void* pNext = nullptr;
    PhysicalDeviceMemoryProperties memoryProperties;
};
using PhysicalDeviceMemoryProperties2KHR = PhysicalDeviceMemoryProperties2;
struct SparseImageFormatProperties2 {
    StructureType sType = StructureType::eSparseImageFormatProperties2;
    void* pNext = nullptr;
    SparseImageFormatProperties properties;
};
using SparseImageFormatProperties2KHR = SparseImageFormatProperties2;
struct PhysicalDeviceSparseImageFormatInfo2 {
    StructureType sType = StructureType::ePhysicalDeviceSparseImageFormatInfo2;
    const void* pNext = nullptr;
    Format format = static_cast<Format>(0);
    ImageType type = static_cast<ImageType>(0);
    SampleCountFlagBits samples = static_cast<SampleCountFlagBits>(0);
    ImageUsageFlags usage = static_cast<ImageUsageFlags>(0);
    ImageTiling tiling = static_cast<ImageTiling>(0);
};
using PhysicalDeviceSparseImageFormatInfo2KHR = PhysicalDeviceSparseImageFormatInfo2;
struct PhysicalDevicePushDescriptorPropertiesKHR {
    StructureType sType = StructureType::ePhysicalDevicePushDescriptorPropertiesKHR;
    void* pNext = nullptr;
    uint32_t maxPushDescriptors = 0;
};
struct ConformanceVersion {
    uint8_t major = 0;
    uint8_t minor = 0;
    uint8_t subminor = 0;
    uint8_t patch = 0;
};
using ConformanceVersionKHR = ConformanceVersion;
struct PhysicalDeviceDriverProperties {
    StructureType sType = StructureType::ePhysicalDeviceDriverProperties;
    void* pNext = nullptr;
    DriverId driverID = static_cast<DriverId>(0);
    char driverName[MAX_DRIVER_NAME_SIZE] = {};
    char driverInfo[MAX_DRIVER_INFO_SIZE] = {};
    ConformanceVersion conformanceVersion;
};
using PhysicalDeviceDriverPropertiesKHR = PhysicalDeviceDriverProperties;
struct PresentRegionsKHR {
    StructureType sType = StructureType::ePresentRegionsKHR;
    const void* pNext = nullptr;
    uint32_t swapchainCount = 0;
    const PresentRegionKHR* pRegions = nullptr;
};
struct PresentRegionKHR {
    uint32_t rectangleCount = 0;
    const RectLayerKHR* pRectangles = nullptr;
};
struct RectLayerKHR {
    Offset2D offset;
    Extent2D extent;
    uint32_t layer = 0;
};
struct PhysicalDeviceVariablePointersFeatures {
    StructureType sType = StructureType::ePhysicalDeviceVariablePointersFeatures;
    void* pNext = nullptr;
    bool variablePointersStorageBuffer = false;
    bool variablePointers = false;
};
using PhysicalDeviceVariablePointersFeaturesKHR = PhysicalDeviceVariablePointersFeatures;
using PhysicalDeviceVariablePointerFeaturesKHR = PhysicalDeviceVariablePointersFeatures;
using PhysicalDeviceVariablePointerFeatures = PhysicalDeviceVariablePointersFeatures;
struct ExternalMemoryProperties {
    ExternalMemoryFeatureFlags externalMemoryFeatures = static_cast<ExternalMemoryFeatureFlags>(0);
    ExternalMemoryHandleTypeFlags exportFromImportedHandleTypes = static_cast<ExternalMemoryHandleTypeFlags>(0);
    ExternalMemoryHandleTypeFlags compatibleHandleTypes = static_cast<ExternalMemoryHandleTypeFlags>(0);
};
using ExternalMemoryPropertiesKHR = ExternalMemoryProperties;
struct PhysicalDeviceExternalImageFormatInfo {
    StructureType sType = StructureType::ePhysicalDeviceExternalImageFormatInfo;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
};
using PhysicalDeviceExternalImageFormatInfoKHR = PhysicalDeviceExternalImageFormatInfo;
struct ExternalImageFormatProperties {
    StructureType sType = StructureType::eExternalImageFormatProperties;
    void* pNext = nullptr;
    ExternalMemoryProperties externalMemoryProperties;
};
using ExternalImageFormatPropertiesKHR = ExternalImageFormatProperties;
struct PhysicalDeviceExternalBufferInfo {
    StructureType sType = StructureType::ePhysicalDeviceExternalBufferInfo;
    const void* pNext = nullptr;
    BufferCreateFlags flags = static_cast<BufferCreateFlags>(0);
    BufferUsageFlags usage = static_cast<BufferUsageFlags>(0);
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
};
using PhysicalDeviceExternalBufferInfoKHR = PhysicalDeviceExternalBufferInfo;
struct ExternalBufferProperties {
    StructureType sType = StructureType::eExternalBufferProperties;
    void* pNext = nullptr;
    ExternalMemoryProperties externalMemoryProperties;
};
using ExternalBufferPropertiesKHR = ExternalBufferProperties;
struct PhysicalDeviceIDProperties {
    StructureType sType = StructureType::ePhysicalDeviceIdProperties;
    void* pNext = nullptr;
    uint8_t deviceUUID[UUID_SIZE] = {};
    uint8_t driverUUID[UUID_SIZE] = {};
    uint8_t deviceLUID[LUID_SIZE] = {};
    uint32_t deviceNodeMask = 0;
    bool deviceLUIDValid = false;
};
using PhysicalDeviceIDPropertiesKHR = PhysicalDeviceIDProperties;
struct ExternalMemoryImageCreateInfo {
    StructureType sType = StructureType::eExternalMemoryImageCreateInfo;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes = static_cast<ExternalMemoryHandleTypeFlags>(0);
};
using ExternalMemoryImageCreateInfoKHR = ExternalMemoryImageCreateInfo;
struct ExternalMemoryBufferCreateInfo {
    StructureType sType = StructureType::eExternalMemoryBufferCreateInfo;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes = static_cast<ExternalMemoryHandleTypeFlags>(0);
};
using ExternalMemoryBufferCreateInfoKHR = ExternalMemoryBufferCreateInfo;
struct ExportMemoryAllocateInfo {
    StructureType sType = StructureType::eExportMemoryAllocateInfo;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlags handleTypes = static_cast<ExternalMemoryHandleTypeFlags>(0);
};
using ExportMemoryAllocateInfoKHR = ExportMemoryAllocateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportMemoryWin32HandleInfoKHR {
    StructureType sType = StructureType::eImportMemoryWin32HandleInfoKHR;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
    HANDLE handle;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ExportMemoryWin32HandleInfoKHR {
    StructureType sType = StructureType::eExportMemoryWin32HandleInfoKHR;
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct MemoryWin32HandlePropertiesKHR {
    StructureType sType = StructureType::eMemoryWin32HandlePropertiesKHR;
    void* pNext = nullptr;
    uint32_t memoryTypeBits = 0;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct MemoryGetWin32HandleInfoKHR {
    StructureType sType = StructureType::eMemoryGetWin32HandleInfoKHR;
    const void* pNext = nullptr;
    DeviceMemory memory;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct ImportMemoryFdInfoKHR {
    StructureType sType = StructureType::eImportMemoryFdInfoKHR;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
    int fd = 0;
};
struct MemoryFdPropertiesKHR {
    StructureType sType = StructureType::eMemoryFdPropertiesKHR;
    void* pNext = nullptr;
    uint32_t memoryTypeBits = 0;
};
struct MemoryGetFdInfoKHR {
    StructureType sType = StructureType::eMemoryGetFdInfoKHR;
    const void* pNext = nullptr;
    DeviceMemory memory;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct Win32KeyedMutexAcquireReleaseInfoKHR {
    StructureType sType = StructureType::eWin32KeyedMutexAcquireReleaseInfoKHR;
    const void* pNext = nullptr;
    uint32_t acquireCount = 0;
    const DeviceMemory* pAcquireSyncs = nullptr;
    const uint64_t* pAcquireKeys = nullptr;
    const uint32_t* pAcquireTimeouts = nullptr;
    uint32_t releaseCount = 0;
    const DeviceMemory* pReleaseSyncs = nullptr;
    const uint64_t* pReleaseKeys = nullptr;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct PhysicalDeviceExternalSemaphoreInfo {
    StructureType sType = StructureType::ePhysicalDeviceExternalSemaphoreInfo;
    const void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlagBits handleType = static_cast<ExternalSemaphoreHandleTypeFlagBits>(0);
};
using PhysicalDeviceExternalSemaphoreInfoKHR = PhysicalDeviceExternalSemaphoreInfo;
struct ExternalSemaphoreProperties {
    StructureType sType = StructureType::eExternalSemaphoreProperties;
    void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlags exportFromImportedHandleTypes = static_cast<ExternalSemaphoreHandleTypeFlags>(0);
    ExternalSemaphoreHandleTypeFlags compatibleHandleTypes = static_cast<ExternalSemaphoreHandleTypeFlags>(0);
    ExternalSemaphoreFeatureFlags externalSemaphoreFeatures = static_cast<ExternalSemaphoreFeatureFlags>(0);
};
using ExternalSemaphorePropertiesKHR = ExternalSemaphoreProperties;
struct ExportSemaphoreCreateInfo {
    StructureType sType = StructureType::eExportSemaphoreCreateInfo;
    const void* pNext = nullptr;
    ExternalSemaphoreHandleTypeFlags handleTypes = static_cast<ExternalSemaphoreHandleTypeFlags>(0);
};
using ExportSemaphoreCreateInfoKHR = ExportSemaphoreCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportSemaphoreWin32HandleInfoKHR {
    StructureType sType = StructureType::eImportSemaphoreWin32HandleInfoKHR;
    const void* pNext = nullptr;
    Semaphore semaphore;
    SemaphoreImportFlags flags = static_cast<SemaphoreImportFlags>(0);
    ExternalSemaphoreHandleTypeFlagBits handleType = static_cast<ExternalSemaphoreHandleTypeFlagBits>(0);
    HANDLE handle;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ExportSemaphoreWin32HandleInfoKHR {
    StructureType sType = StructureType::eExportSemaphoreWin32HandleInfoKHR;
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct D3D12FenceSubmitInfoKHR {
    StructureType sType = StructureType::eD3D12FenceSubmitInfoKHR;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreValuesCount = 0;
    const uint64_t* pWaitSemaphoreValues = nullptr;
    uint32_t signalSemaphoreValuesCount = 0;
    const uint64_t* pSignalSemaphoreValues = nullptr;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct SemaphoreGetWin32HandleInfoKHR {
    StructureType sType = StructureType::eSemaphoreGetWin32HandleInfoKHR;
    const void* pNext = nullptr;
    Semaphore semaphore;
    ExternalSemaphoreHandleTypeFlagBits handleType = static_cast<ExternalSemaphoreHandleTypeFlagBits>(0);
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct ImportSemaphoreFdInfoKHR {
    StructureType sType = StructureType::eImportSemaphoreFdInfoKHR;
    const void* pNext = nullptr;
    Semaphore semaphore;
    SemaphoreImportFlags flags = static_cast<SemaphoreImportFlags>(0);
    ExternalSemaphoreHandleTypeFlagBits handleType = static_cast<ExternalSemaphoreHandleTypeFlagBits>(0);
    int fd = 0;
};
struct SemaphoreGetFdInfoKHR {
    StructureType sType = StructureType::eSemaphoreGetFdInfoKHR;
    const void* pNext = nullptr;
    Semaphore semaphore;
    ExternalSemaphoreHandleTypeFlagBits handleType = static_cast<ExternalSemaphoreHandleTypeFlagBits>(0);
};
struct PhysicalDeviceExternalFenceInfo {
    StructureType sType = StructureType::ePhysicalDeviceExternalFenceInfo;
    const void* pNext = nullptr;
    ExternalFenceHandleTypeFlagBits handleType = static_cast<ExternalFenceHandleTypeFlagBits>(0);
};
using PhysicalDeviceExternalFenceInfoKHR = PhysicalDeviceExternalFenceInfo;
struct ExternalFenceProperties {
    StructureType sType = StructureType::eExternalFenceProperties;
    void* pNext = nullptr;
    ExternalFenceHandleTypeFlags exportFromImportedHandleTypes = static_cast<ExternalFenceHandleTypeFlags>(0);
    ExternalFenceHandleTypeFlags compatibleHandleTypes = static_cast<ExternalFenceHandleTypeFlags>(0);
    ExternalFenceFeatureFlags externalFenceFeatures = static_cast<ExternalFenceFeatureFlags>(0);
};
using ExternalFencePropertiesKHR = ExternalFenceProperties;
struct ExportFenceCreateInfo {
    StructureType sType = StructureType::eExportFenceCreateInfo;
    const void* pNext = nullptr;
    ExternalFenceHandleTypeFlags handleTypes = static_cast<ExternalFenceHandleTypeFlags>(0);
};
using ExportFenceCreateInfoKHR = ExportFenceCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ImportFenceWin32HandleInfoKHR {
    StructureType sType = StructureType::eImportFenceWin32HandleInfoKHR;
    const void* pNext = nullptr;
    Fence fence;
    FenceImportFlags flags = static_cast<FenceImportFlags>(0);
    ExternalFenceHandleTypeFlagBits handleType = static_cast<ExternalFenceHandleTypeFlagBits>(0);
    HANDLE handle;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct ExportFenceWin32HandleInfoKHR {
    StructureType sType = StructureType::eExportFenceWin32HandleInfoKHR;
    const void* pNext = nullptr;
    const SECURITY_ATTRIBUTES* pAttributes = nullptr;
    DWORD dwAccess;
    LPCWSTR name;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct FenceGetWin32HandleInfoKHR {
    StructureType sType = StructureType::eFenceGetWin32HandleInfoKHR;
    const void* pNext = nullptr;
    Fence fence;
    ExternalFenceHandleTypeFlagBits handleType = static_cast<ExternalFenceHandleTypeFlagBits>(0);
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct ImportFenceFdInfoKHR {
    StructureType sType = StructureType::eImportFenceFdInfoKHR;
    const void* pNext = nullptr;
    Fence fence;
    FenceImportFlags flags = static_cast<FenceImportFlags>(0);
    ExternalFenceHandleTypeFlagBits handleType = static_cast<ExternalFenceHandleTypeFlagBits>(0);
    int fd = 0;
};
struct FenceGetFdInfoKHR {
    StructureType sType = StructureType::eFenceGetFdInfoKHR;
    const void* pNext = nullptr;
    Fence fence;
    ExternalFenceHandleTypeFlagBits handleType = static_cast<ExternalFenceHandleTypeFlagBits>(0);
};
struct PhysicalDeviceMultiviewFeatures {
    StructureType sType = StructureType::ePhysicalDeviceMultiviewFeatures;
    void* pNext = nullptr;
    bool multiview = false;
    bool multiviewGeometryShader = false;
    bool multiviewTessellationShader = false;
};
using PhysicalDeviceMultiviewFeaturesKHR = PhysicalDeviceMultiviewFeatures;
struct PhysicalDeviceMultiviewProperties {
    StructureType sType = StructureType::ePhysicalDeviceMultiviewProperties;
    void* pNext = nullptr;
    uint32_t maxMultiviewViewCount = 0;
    uint32_t maxMultiviewInstanceIndex = 0;
};
using PhysicalDeviceMultiviewPropertiesKHR = PhysicalDeviceMultiviewProperties;
struct RenderPassMultiviewCreateInfo {
    StructureType sType = StructureType::eRenderPassMultiviewCreateInfo;
    const void* pNext = nullptr;
    uint32_t subpassCount = 0;
    const uint32_t* pViewMasks = nullptr;
    uint32_t dependencyCount = 0;
    const int32_t* pViewOffsets = nullptr;
    uint32_t correlationMaskCount = 0;
    const uint32_t* pCorrelationMasks = nullptr;
};
using RenderPassMultiviewCreateInfoKHR = RenderPassMultiviewCreateInfo;
struct SurfaceCapabilities2EXT {
    StructureType sType = StructureType::eSurfaceCapabilities2EXT;
    void* pNext = nullptr;
    uint32_t minImageCount = 0;
    uint32_t maxImageCount = 0;
    Extent2D currentExtent;
    Extent2D minImageExtent;
    Extent2D maxImageExtent;
    uint32_t maxImageArrayLayers = 0;
    SurfaceTransformFlagsKHR supportedTransforms = static_cast<SurfaceTransformFlagsKHR>(0);
    SurfaceTransformFlagBitsKHR currentTransform = static_cast<SurfaceTransformFlagBitsKHR>(0);
    CompositeAlphaFlagsKHR supportedCompositeAlpha = static_cast<CompositeAlphaFlagsKHR>(0);
    ImageUsageFlags supportedUsageFlags = static_cast<ImageUsageFlags>(0);
    SurfaceCounterFlagsEXT supportedSurfaceCounters = static_cast<SurfaceCounterFlagsEXT>(0);
};
struct DisplayPowerInfoEXT {
    StructureType sType = StructureType::eDisplayPowerInfoEXT;
    const void* pNext = nullptr;
    DisplayPowerStateEXT powerState = static_cast<DisplayPowerStateEXT>(0);
};
struct DeviceEventInfoEXT {
    StructureType sType = StructureType::eDeviceEventInfoEXT;
    const void* pNext = nullptr;
    DeviceEventTypeEXT deviceEvent = static_cast<DeviceEventTypeEXT>(0);
};
struct DisplayEventInfoEXT {
    StructureType sType = StructureType::eDisplayEventInfoEXT;
    const void* pNext = nullptr;
    DisplayEventTypeEXT displayEvent = static_cast<DisplayEventTypeEXT>(0);
};
struct SwapchainCounterCreateInfoEXT {
    StructureType sType = StructureType::eSwapchainCounterCreateInfoEXT;
    const void* pNext = nullptr;
    SurfaceCounterFlagsEXT surfaceCounters = static_cast<SurfaceCounterFlagsEXT>(0);
};
struct PhysicalDeviceGroupProperties {
    StructureType sType = StructureType::ePhysicalDeviceGroupProperties;
    void* pNext = nullptr;
    uint32_t physicalDeviceCount = 0;
    PhysicalDevice physicalDevices[MAX_DEVICE_GROUP_SIZE];
    bool subsetAllocation = false;
};
using PhysicalDeviceGroupPropertiesKHR = PhysicalDeviceGroupProperties;
struct MemoryAllocateFlagsInfo {
    StructureType sType = StructureType::eMemoryAllocateFlagsInfo;
    const void* pNext = nullptr;
    MemoryAllocateFlags flags = static_cast<MemoryAllocateFlags>(0);
    uint32_t deviceMask = 0;
};
using MemoryAllocateFlagsInfoKHR = MemoryAllocateFlagsInfo;
struct BindBufferMemoryInfo {
    StructureType sType = StructureType::eBindBufferMemoryInfo;
    const void* pNext = nullptr;
    Buffer buffer;
    DeviceMemory memory;
    DeviceSize memoryOffset = 0;
};
using BindBufferMemoryInfoKHR = BindBufferMemoryInfo;
struct BindBufferMemoryDeviceGroupInfo {
    StructureType sType = StructureType::eBindBufferMemoryDeviceGroupInfo;
    const void* pNext = nullptr;
    uint32_t deviceIndexCount = 0;
    const uint32_t* pDeviceIndices = nullptr;
};
using BindBufferMemoryDeviceGroupInfoKHR = BindBufferMemoryDeviceGroupInfo;
struct BindImageMemoryInfo {
    StructureType sType = StructureType::eBindImageMemoryInfo;
    const void* pNext = nullptr;
    Image image;
    DeviceMemory memory;
    DeviceSize memoryOffset = 0;
};
using BindImageMemoryInfoKHR = BindImageMemoryInfo;
struct BindImageMemoryDeviceGroupInfo {
    StructureType sType = StructureType::eBindImageMemoryDeviceGroupInfo;
    const void* pNext = nullptr;
    uint32_t deviceIndexCount = 0;
    const uint32_t* pDeviceIndices = nullptr;
    uint32_t splitInstanceBindRegionCount = 0;
    const Rect2D* pSplitInstanceBindRegions = nullptr;
};
using BindImageMemoryDeviceGroupInfoKHR = BindImageMemoryDeviceGroupInfo;
struct DeviceGroupRenderPassBeginInfo {
    StructureType sType = StructureType::eDeviceGroupRenderPassBeginInfo;
    const void* pNext = nullptr;
    uint32_t deviceMask = 0;
    uint32_t deviceRenderAreaCount = 0;
    const Rect2D* pDeviceRenderAreas = nullptr;
};
using DeviceGroupRenderPassBeginInfoKHR = DeviceGroupRenderPassBeginInfo;
struct DeviceGroupCommandBufferBeginInfo {
    StructureType sType = StructureType::eDeviceGroupCommandBufferBeginInfo;
    const void* pNext = nullptr;
    uint32_t deviceMask = 0;
};
using DeviceGroupCommandBufferBeginInfoKHR = DeviceGroupCommandBufferBeginInfo;
struct DeviceGroupSubmitInfo {
    StructureType sType = StructureType::eDeviceGroupSubmitInfo;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreCount = 0;
    const uint32_t* pWaitSemaphoreDeviceIndices = nullptr;
    uint32_t commandBufferCount = 0;
    const uint32_t* pCommandBufferDeviceMasks = nullptr;
    uint32_t signalSemaphoreCount = 0;
    const uint32_t* pSignalSemaphoreDeviceIndices = nullptr;
};
using DeviceGroupSubmitInfoKHR = DeviceGroupSubmitInfo;
struct DeviceGroupBindSparseInfo {
    StructureType sType = StructureType::eDeviceGroupBindSparseInfo;
    const void* pNext = nullptr;
    uint32_t resourceDeviceIndex = 0;
    uint32_t memoryDeviceIndex = 0;
};
using DeviceGroupBindSparseInfoKHR = DeviceGroupBindSparseInfo;
struct DeviceGroupPresentCapabilitiesKHR {
    StructureType sType = StructureType::eDeviceGroupPresentCapabilitiesKHR;
    const void* pNext = nullptr;
    uint32_t presentMask[MAX_DEVICE_GROUP_SIZE] = {};
    DeviceGroupPresentModeFlagsKHR modes = static_cast<DeviceGroupPresentModeFlagsKHR>(0);
};
struct ImageSwapchainCreateInfoKHR {
    StructureType sType = StructureType::eImageSwapchainCreateInfoKHR;
    const void* pNext = nullptr;
    SwapchainKHR swapchain;
};
struct BindImageMemorySwapchainInfoKHR {
    StructureType sType = StructureType::eBindImageMemorySwapchainInfoKHR;
    const void* pNext = nullptr;
    SwapchainKHR swapchain;
    uint32_t imageIndex = 0;
};
struct AcquireNextImageInfoKHR {
    StructureType sType = StructureType::eAcquireNextImageInfoKHR;
    const void* pNext = nullptr;
    SwapchainKHR swapchain;
    uint64_t timeout = 0;
    Semaphore semaphore;
    Fence fence;
    uint32_t deviceMask = 0;
};
struct DeviceGroupPresentInfoKHR {
    StructureType sType = StructureType::eDeviceGroupPresentInfoKHR;
    const void* pNext = nullptr;
    uint32_t swapchainCount = 0;
    const uint32_t* pDeviceMasks = nullptr;
    DeviceGroupPresentModeFlagBitsKHR mode = static_cast<DeviceGroupPresentModeFlagBitsKHR>(0);
};
struct DeviceGroupDeviceCreateInfo {
    StructureType sType = StructureType::eDeviceGroupDeviceCreateInfo;
    const void* pNext = nullptr;
    uint32_t physicalDeviceCount = 0;
    const PhysicalDevice* pPhysicalDevices = nullptr;
};
using DeviceGroupDeviceCreateInfoKHR = DeviceGroupDeviceCreateInfo;
struct DeviceGroupSwapchainCreateInfoKHR {
    StructureType sType = StructureType::eDeviceGroupSwapchainCreateInfoKHR;
    const void* pNext = nullptr;
    DeviceGroupPresentModeFlagsKHR modes = static_cast<DeviceGroupPresentModeFlagsKHR>(0);
};
struct DescriptorUpdateTemplateEntry {
    uint32_t dstBinding = 0;
    uint32_t dstArrayElement = 0;
    uint32_t descriptorCount = 0;
    DescriptorType descriptorType = static_cast<DescriptorType>(0);
    size_t offset = 0;
    size_t stride = 0;
};
using DescriptorUpdateTemplateEntryKHR = DescriptorUpdateTemplateEntry;
struct DescriptorUpdateTemplateCreateInfo {
    StructureType sType = StructureType::eDescriptorUpdateTemplateCreateInfo;
    const void* pNext = nullptr;
    DescriptorUpdateTemplateCreateFlags flags = static_cast<DescriptorUpdateTemplateCreateFlags>(0);
    uint32_t descriptorUpdateEntryCount = 0;
    const DescriptorUpdateTemplateEntry* pDescriptorUpdateEntries = nullptr;
    DescriptorUpdateTemplateType templateType = static_cast<DescriptorUpdateTemplateType>(0);
    DescriptorSetLayout descriptorSetLayout;
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    PipelineLayout pipelineLayout;
    uint32_t set = 0;
};
using DescriptorUpdateTemplateCreateInfoKHR = DescriptorUpdateTemplateCreateInfo;
struct XYColorEXT {
    float x = 0.f;
    float y = 0.f;
};
struct HdrMetadataEXT {
    StructureType sType = StructureType::eHdrMetadataEXT;
    const void* pNext = nullptr;
    XYColorEXT displayPrimaryRed;
    XYColorEXT displayPrimaryGreen;
    XYColorEXT displayPrimaryBlue;
    XYColorEXT whitePoint;
    float maxLuminance = 0.f;
    float minLuminance = 0.f;
    float maxContentLightLevel = 0.f;
    float maxFrameAverageLightLevel = 0.f;
};
struct DisplayNativeHdrSurfaceCapabilitiesAMD {
    StructureType sType = StructureType::eDisplayNativeHdrSurfaceCapabilitiesAMD;
    void* pNext = nullptr;
    bool localDimmingSupport = false;
};
struct SwapchainDisplayNativeHdrCreateInfoAMD {
    StructureType sType = StructureType::eSwapchainDisplayNativeHdrCreateInfoAMD;
    const void* pNext = nullptr;
    bool localDimmingEnable = false;
};
struct RefreshCycleDurationGOOGLE {
    uint64_t refreshDuration = 0;
};
struct PastPresentationTimingGOOGLE {
    uint32_t presentID = 0;
    uint64_t desiredPresentTime = 0;
    uint64_t actualPresentTime = 0;
    uint64_t earliestPresentTime = 0;
    uint64_t presentMargin = 0;
};
struct PresentTimesInfoGOOGLE {
    StructureType sType = StructureType::ePresentTimesInfoGOOGLE;
    const void* pNext = nullptr;
    uint32_t swapchainCount = 0;
    const PresentTimeGOOGLE* pTimes = nullptr;
};
struct PresentTimeGOOGLE {
    uint32_t presentID = 0;
    uint64_t desiredPresentTime = 0;
};
#if defined(VK_USE_PLATFORM_IOS_MVK)
struct IOSSurfaceCreateInfoMVK {
    StructureType sType = StructureType::eIosSurfaceCreateInfoMVK;
    const void* pNext = nullptr;
    IOSSurfaceCreateFlagsMVK flags = static_cast<IOSSurfaceCreateFlagsMVK>(0);
    const void* pView = nullptr;
};
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
struct MacOSSurfaceCreateInfoMVK {
    StructureType sType = StructureType::eMacosSurfaceCreateInfoMVK;
    const void* pNext = nullptr;
    MacOSSurfaceCreateFlagsMVK flags = static_cast<MacOSSurfaceCreateFlagsMVK>(0);
    const void* pView = nullptr;
};
#endif // VK_USE_PLATFORM_MACOS_MVK
#if defined(VK_USE_PLATFORM_METAL_EXT)
struct MetalSurfaceCreateInfoEXT {
    StructureType sType = StructureType::eMetalSurfaceCreateInfoEXT;
    const void* pNext = nullptr;
    MetalSurfaceCreateFlagsEXT flags = static_cast<MetalSurfaceCreateFlagsEXT>(0);
    const CAMetalLayer* pLayer = nullptr;
};
#endif // VK_USE_PLATFORM_METAL_EXT
struct ViewportWScalingNV {
    float xcoeff = 0.f;
    float ycoeff = 0.f;
};
struct PipelineViewportWScalingStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineViewportWScalingStateCreateInfoNV;
    const void* pNext = nullptr;
    bool viewportWScalingEnable = false;
    uint32_t viewportCount = 0;
    const ViewportWScalingNV* pViewportWScalings = nullptr;
};
struct ViewportSwizzleNV {
    ViewportCoordinateSwizzleNV x = static_cast<ViewportCoordinateSwizzleNV>(0);
    ViewportCoordinateSwizzleNV y = static_cast<ViewportCoordinateSwizzleNV>(0);
    ViewportCoordinateSwizzleNV z = static_cast<ViewportCoordinateSwizzleNV>(0);
    ViewportCoordinateSwizzleNV w = static_cast<ViewportCoordinateSwizzleNV>(0);
};
struct PipelineViewportSwizzleStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineViewportSwizzleStateCreateInfoNV;
    const void* pNext = nullptr;
    PipelineViewportSwizzleStateCreateFlagsNV flags = static_cast<PipelineViewportSwizzleStateCreateFlagsNV>(0);
    uint32_t viewportCount = 0;
    const ViewportSwizzleNV* pViewportSwizzles = nullptr;
};
struct PhysicalDeviceDiscardRectanglePropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceDiscardRectanglePropertiesEXT;
    void* pNext = nullptr;
    uint32_t maxDiscardRectangles = 0;
};
struct PipelineDiscardRectangleStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineDiscardRectangleStateCreateInfoEXT;
    const void* pNext = nullptr;
    PipelineDiscardRectangleStateCreateFlagsEXT flags = static_cast<PipelineDiscardRectangleStateCreateFlagsEXT>(0);
    DiscardRectangleModeEXT discardRectangleMode = static_cast<DiscardRectangleModeEXT>(0);
    uint32_t discardRectangleCount = 0;
    const Rect2D* pDiscardRectangles = nullptr;
};
struct PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX {
    StructureType sType = StructureType::ePhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;
    void* pNext = nullptr;
    bool perViewPositionAllComponents = false;
};
struct InputAttachmentAspectReference {
    uint32_t subpass = 0;
    uint32_t inputAttachmentIndex = 0;
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
};
using InputAttachmentAspectReferenceKHR = InputAttachmentAspectReference;
struct RenderPassInputAttachmentAspectCreateInfo {
    StructureType sType = StructureType::eRenderPassInputAttachmentAspectCreateInfo;
    const void* pNext = nullptr;
    uint32_t aspectReferenceCount = 0;
    const InputAttachmentAspectReference* pAspectReferences = nullptr;
};
using RenderPassInputAttachmentAspectCreateInfoKHR = RenderPassInputAttachmentAspectCreateInfo;
struct PhysicalDeviceSurfaceInfo2KHR {
    StructureType sType = StructureType::ePhysicalDeviceSurfaceInfo2KHR;
    const void* pNext = nullptr;
    SurfaceKHR surface;
};
struct SurfaceCapabilities2KHR {
    StructureType sType = StructureType::eSurfaceCapabilities2KHR;
    void* pNext = nullptr;
    SurfaceCapabilitiesKHR surfaceCapabilities;
};
struct SurfaceFormat2KHR {
    StructureType sType = StructureType::eSurfaceFormat2KHR;
    void* pNext = nullptr;
    SurfaceFormatKHR surfaceFormat;
};
struct DisplayProperties2KHR {
    StructureType sType = StructureType::eDisplayProperties2KHR;
    void* pNext = nullptr;
    DisplayPropertiesKHR displayProperties;
};
struct DisplayPlaneProperties2KHR {
    StructureType sType = StructureType::eDisplayPlaneProperties2KHR;
    void* pNext = nullptr;
    DisplayPlanePropertiesKHR displayPlaneProperties;
};
struct DisplayModeProperties2KHR {
    StructureType sType = StructureType::eDisplayModeProperties2KHR;
    void* pNext = nullptr;
    DisplayModePropertiesKHR displayModeProperties;
};
struct DisplayPlaneInfo2KHR {
    StructureType sType = StructureType::eDisplayPlaneInfo2KHR;
    const void* pNext = nullptr;
    DisplayModeKHR mode;
    uint32_t planeIndex = 0;
};
struct DisplayPlaneCapabilities2KHR {
    StructureType sType = StructureType::eDisplayPlaneCapabilities2KHR;
    void* pNext = nullptr;
    DisplayPlaneCapabilitiesKHR capabilities;
};
struct SharedPresentSurfaceCapabilitiesKHR {
    StructureType sType = StructureType::eSharedPresentSurfaceCapabilitiesKHR;
    void* pNext = nullptr;
    ImageUsageFlags sharedPresentSupportedUsageFlags = static_cast<ImageUsageFlags>(0);
};
struct PhysicalDevice16BitStorageFeatures {
    StructureType sType = StructureType::ePhysicalDevice16BitStorageFeatures;
    void* pNext = nullptr;
    bool storageBuffer16BitAccess = false;
    bool uniformAndStorageBuffer16BitAccess = false;
    bool storagePushConstant16 = false;
    bool storageInputOutput16 = false;
};
using PhysicalDevice16BitStorageFeaturesKHR = PhysicalDevice16BitStorageFeatures;
struct PhysicalDeviceSubgroupProperties {
    StructureType sType = StructureType::ePhysicalDeviceSubgroupProperties;
    void* pNext = nullptr;
    uint32_t subgroupSize = 0;
    ShaderStageFlags supportedStages = static_cast<ShaderStageFlags>(0);
    SubgroupFeatureFlags supportedOperations = static_cast<SubgroupFeatureFlags>(0);
    bool quadOperationsInAllStages = false;
};
struct PhysicalDeviceShaderSubgroupExtendedTypesFeatures {
    StructureType sType = StructureType::ePhysicalDeviceShaderSubgroupExtendedTypesFeatures;
    void* pNext = nullptr;
    bool shaderSubgroupExtendedTypes = false;
};
using PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR = PhysicalDeviceShaderSubgroupExtendedTypesFeatures;
struct BufferMemoryRequirementsInfo2 {
    StructureType sType = StructureType::eBufferMemoryRequirementsInfo2;
    const void* pNext = nullptr;
    Buffer buffer;
};
using BufferMemoryRequirementsInfo2KHR = BufferMemoryRequirementsInfo2;
struct ImageMemoryRequirementsInfo2 {
    StructureType sType = StructureType::eImageMemoryRequirementsInfo2;
    const void* pNext = nullptr;
    Image image;
};
using ImageMemoryRequirementsInfo2KHR = ImageMemoryRequirementsInfo2;
struct ImageSparseMemoryRequirementsInfo2 {
    StructureType sType = StructureType::eImageSparseMemoryRequirementsInfo2;
    const void* pNext = nullptr;
    Image image;
};
using ImageSparseMemoryRequirementsInfo2KHR = ImageSparseMemoryRequirementsInfo2;
struct MemoryRequirements2 {
    StructureType sType = StructureType::eMemoryRequirements2;
    void* pNext = nullptr;
    MemoryRequirements memoryRequirements;
};
using MemoryRequirements2KHR = MemoryRequirements2;
struct SparseImageMemoryRequirements2 {
    StructureType sType = StructureType::eSparseImageMemoryRequirements2;
    void* pNext = nullptr;
    SparseImageMemoryRequirements memoryRequirements;
};
using SparseImageMemoryRequirements2KHR = SparseImageMemoryRequirements2;
struct PhysicalDevicePointClippingProperties {
    StructureType sType = StructureType::ePhysicalDevicePointClippingProperties;
    void* pNext = nullptr;
    PointClippingBehavior pointClippingBehavior = static_cast<PointClippingBehavior>(0);
};
using PhysicalDevicePointClippingPropertiesKHR = PhysicalDevicePointClippingProperties;
struct MemoryDedicatedRequirements {
    StructureType sType = StructureType::eMemoryDedicatedRequirements;
    void* pNext = nullptr;
    bool prefersDedicatedAllocation = false;
    bool requiresDedicatedAllocation = false;
};
using MemoryDedicatedRequirementsKHR = MemoryDedicatedRequirements;
struct MemoryDedicatedAllocateInfo {
    StructureType sType = StructureType::eMemoryDedicatedAllocateInfo;
    const void* pNext = nullptr;
    Image image;
    Buffer buffer;
};
using MemoryDedicatedAllocateInfoKHR = MemoryDedicatedAllocateInfo;
struct ImageViewUsageCreateInfo {
    StructureType sType = StructureType::eImageViewUsageCreateInfo;
    const void* pNext = nullptr;
    ImageUsageFlags usage = static_cast<ImageUsageFlags>(0);
};
using ImageViewUsageCreateInfoKHR = ImageViewUsageCreateInfo;
struct PipelineTessellationDomainOriginStateCreateInfo {
    StructureType sType = StructureType::ePipelineTessellationDomainOriginStateCreateInfo;
    const void* pNext = nullptr;
    TessellationDomainOrigin domainOrigin = static_cast<TessellationDomainOrigin>(0);
};
using PipelineTessellationDomainOriginStateCreateInfoKHR = PipelineTessellationDomainOriginStateCreateInfo;
struct SamplerYcbcrConversionInfo {
    StructureType sType = StructureType::eSamplerYcbcrConversionInfo;
    const void* pNext = nullptr;
    SamplerYcbcrConversion conversion;
};
using SamplerYcbcrConversionInfoKHR = SamplerYcbcrConversionInfo;
struct SamplerYcbcrConversionCreateInfo {
    StructureType sType = StructureType::eSamplerYcbcrConversionCreateInfo;
    const void* pNext = nullptr;
    Format format = static_cast<Format>(0);
    SamplerYcbcrModelConversion ycbcrModel = static_cast<SamplerYcbcrModelConversion>(0);
    SamplerYcbcrRange ycbcrRange = static_cast<SamplerYcbcrRange>(0);
    ComponentMapping components;
    ChromaLocation xChromaOffset = static_cast<ChromaLocation>(0);
    ChromaLocation yChromaOffset = static_cast<ChromaLocation>(0);
    Filter chromaFilter = static_cast<Filter>(0);
    bool forceExplicitReconstruction = false;
};
using SamplerYcbcrConversionCreateInfoKHR = SamplerYcbcrConversionCreateInfo;
struct BindImagePlaneMemoryInfo {
    StructureType sType = StructureType::eBindImagePlaneMemoryInfo;
    const void* pNext = nullptr;
    ImageAspectFlagBits planeAspect = static_cast<ImageAspectFlagBits>(0);
};
using BindImagePlaneMemoryInfoKHR = BindImagePlaneMemoryInfo;
struct ImagePlaneMemoryRequirementsInfo {
    StructureType sType = StructureType::eImagePlaneMemoryRequirementsInfo;
    const void* pNext = nullptr;
    ImageAspectFlagBits planeAspect = static_cast<ImageAspectFlagBits>(0);
};
using ImagePlaneMemoryRequirementsInfoKHR = ImagePlaneMemoryRequirementsInfo;
struct PhysicalDeviceSamplerYcbcrConversionFeatures {
    StructureType sType = StructureType::ePhysicalDeviceSamplerYcbcrConversionFeatures;
    void* pNext = nullptr;
    bool samplerYcbcrConversion = false;
};
using PhysicalDeviceSamplerYcbcrConversionFeaturesKHR = PhysicalDeviceSamplerYcbcrConversionFeatures;
struct SamplerYcbcrConversionImageFormatProperties {
    StructureType sType = StructureType::eSamplerYcbcrConversionImageFormatProperties;
    void* pNext = nullptr;
    uint32_t combinedImageSamplerDescriptorCount = 0;
};
using SamplerYcbcrConversionImageFormatPropertiesKHR = SamplerYcbcrConversionImageFormatProperties;
struct TextureLODGatherFormatPropertiesAMD {
    StructureType sType = StructureType::eTextureLodGatherFormatPropertiesAMD;
    void* pNext = nullptr;
    bool supportsTextureGatherLODBiasAMD = false;
};
struct ConditionalRenderingBeginInfoEXT {
    StructureType sType = StructureType::eConditionalRenderingBeginInfoEXT;
    const void* pNext = nullptr;
    Buffer buffer;
    DeviceSize offset = 0;
    ConditionalRenderingFlagsEXT flags = static_cast<ConditionalRenderingFlagsEXT>(0);
};
struct ProtectedSubmitInfo {
    StructureType sType = StructureType::eProtectedSubmitInfo;
    const void* pNext = nullptr;
    bool protectedSubmit = false;
};
struct PhysicalDeviceProtectedMemoryFeatures {
    StructureType sType = StructureType::ePhysicalDeviceProtectedMemoryFeatures;
    void* pNext = nullptr;
    bool protectedMemory = false;
};
struct PhysicalDeviceProtectedMemoryProperties {
    StructureType sType = StructureType::ePhysicalDeviceProtectedMemoryProperties;
    void* pNext = nullptr;
    bool protectedNoFault = false;
};
struct DeviceQueueInfo2 {
    StructureType sType = StructureType::eDeviceQueueInfo2;
    const void* pNext = nullptr;
    DeviceQueueCreateFlags flags = static_cast<DeviceQueueCreateFlags>(0);
    uint32_t queueFamilyIndex = 0;
    uint32_t queueIndex = 0;
};
struct PipelineCoverageToColorStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineCoverageToColorStateCreateInfoNV;
    const void* pNext = nullptr;
    PipelineCoverageToColorStateCreateFlagsNV flags = static_cast<PipelineCoverageToColorStateCreateFlagsNV>(0);
    bool coverageToColorEnable = false;
    uint32_t coverageToColorLocation = 0;
};
struct PhysicalDeviceSamplerFilterMinmaxProperties {
    StructureType sType = StructureType::ePhysicalDeviceSamplerFilterMinmaxProperties;
    void* pNext = nullptr;
    bool filterMinmaxSingleComponentFormats = false;
    bool filterMinmaxImageComponentMapping = false;
};
using PhysicalDeviceSamplerFilterMinmaxPropertiesEXT = PhysicalDeviceSamplerFilterMinmaxProperties;
struct SampleLocationEXT {
    float x = 0.f;
    float y = 0.f;
};
struct SampleLocationsInfoEXT {
    StructureType sType = StructureType::eSampleLocationsInfoEXT;
    const void* pNext = nullptr;
    SampleCountFlagBits sampleLocationsPerPixel = static_cast<SampleCountFlagBits>(0);
    Extent2D sampleLocationGridSize;
    uint32_t sampleLocationsCount = 0;
    const SampleLocationEXT* pSampleLocations = nullptr;
};
struct AttachmentSampleLocationsEXT {
    uint32_t attachmentIndex = 0;
    SampleLocationsInfoEXT sampleLocationsInfo;
};
struct SubpassSampleLocationsEXT {
    uint32_t subpassIndex = 0;
    SampleLocationsInfoEXT sampleLocationsInfo;
};
struct RenderPassSampleLocationsBeginInfoEXT {
    StructureType sType = StructureType::eRenderPassSampleLocationsBeginInfoEXT;
    const void* pNext = nullptr;
    uint32_t attachmentInitialSampleLocationsCount = 0;
    const AttachmentSampleLocationsEXT* pAttachmentInitialSampleLocations = nullptr;
    uint32_t postSubpassSampleLocationsCount = 0;
    const SubpassSampleLocationsEXT* pPostSubpassSampleLocations = nullptr;
};
struct PipelineSampleLocationsStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineSampleLocationsStateCreateInfoEXT;
    const void* pNext = nullptr;
    bool sampleLocationsEnable = false;
    SampleLocationsInfoEXT sampleLocationsInfo;
};
struct PhysicalDeviceSampleLocationsPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceSampleLocationsPropertiesEXT;
    void* pNext = nullptr;
    SampleCountFlags sampleLocationSampleCounts = static_cast<SampleCountFlags>(0);
    Extent2D maxSampleLocationGridSize;
    float sampleLocationCoordinateRange[2] = {};
    uint32_t sampleLocationSubPixelBits = 0;
    bool variableSampleLocations = false;
};
struct MultisamplePropertiesEXT {
    StructureType sType = StructureType::eMultisamplePropertiesEXT;
    void* pNext = nullptr;
    Extent2D maxSampleLocationGridSize;
};
struct SamplerReductionModeCreateInfo {
    StructureType sType = StructureType::eSamplerReductionModeCreateInfo;
    const void* pNext = nullptr;
    SamplerReductionMode reductionMode = static_cast<SamplerReductionMode>(0);
};
using SamplerReductionModeCreateInfoEXT = SamplerReductionModeCreateInfo;
struct PhysicalDeviceBlendOperationAdvancedFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceBlendOperationAdvancedFeaturesEXT;
    void* pNext = nullptr;
    bool advancedBlendCoherentOperations = false;
};
struct PhysicalDeviceBlendOperationAdvancedPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceBlendOperationAdvancedPropertiesEXT;
    void* pNext = nullptr;
    uint32_t advancedBlendMaxColorAttachments = 0;
    bool advancedBlendIndependentBlend = false;
    bool advancedBlendNonPremultipliedSrcColor = false;
    bool advancedBlendNonPremultipliedDstColor = false;
    bool advancedBlendCorrelatedOverlap = false;
    bool advancedBlendAllOperations = false;
};
struct PipelineColorBlendAdvancedStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineColorBlendAdvancedStateCreateInfoEXT;
    const void* pNext = nullptr;
    bool srcPremultiplied = false;
    bool dstPremultiplied = false;
    BlendOverlapEXT blendOverlap = static_cast<BlendOverlapEXT>(0);
};
struct PhysicalDeviceInlineUniformBlockFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceInlineUniformBlockFeaturesEXT;
    void* pNext = nullptr;
    bool inlineUniformBlock = false;
    bool descriptorBindingInlineUniformBlockUpdateAfterBind = false;
};
struct PhysicalDeviceInlineUniformBlockPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceInlineUniformBlockPropertiesEXT;
    void* pNext = nullptr;
    uint32_t maxInlineUniformBlockSize = 0;
    uint32_t maxPerStageDescriptorInlineUniformBlocks = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks = 0;
    uint32_t maxDescriptorSetInlineUniformBlocks = 0;
    uint32_t maxDescriptorSetUpdateAfterBindInlineUniformBlocks = 0;
};
struct WriteDescriptorSetInlineUniformBlockEXT {
    StructureType sType = StructureType::eWriteDescriptorSetInlineUniformBlockEXT;
    const void* pNext = nullptr;
    uint32_t dataSize = 0;
    const void* pData = nullptr;
};
struct DescriptorPoolInlineUniformBlockCreateInfoEXT {
    StructureType sType = StructureType::eDescriptorPoolInlineUniformBlockCreateInfoEXT;
    const void* pNext = nullptr;
    uint32_t maxInlineUniformBlockBindings = 0;
};
struct PipelineCoverageModulationStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineCoverageModulationStateCreateInfoNV;
    const void* pNext = nullptr;
    PipelineCoverageModulationStateCreateFlagsNV flags = static_cast<PipelineCoverageModulationStateCreateFlagsNV>(0);
    CoverageModulationModeNV coverageModulationMode = static_cast<CoverageModulationModeNV>(0);
    bool coverageModulationTableEnable = false;
    uint32_t coverageModulationTableCount = 0;
    const float* pCoverageModulationTable = nullptr;
};
struct ImageFormatListCreateInfo {
    StructureType sType = StructureType::eImageFormatListCreateInfo;
    const void* pNext = nullptr;
    uint32_t viewFormatCount = 0;
    const Format* pViewFormats = nullptr;
};
using ImageFormatListCreateInfoKHR = ImageFormatListCreateInfo;
struct ValidationCacheCreateInfoEXT {
    StructureType sType = StructureType::eValidationCacheCreateInfoEXT;
    const void* pNext = nullptr;
    ValidationCacheCreateFlagsEXT flags = static_cast<ValidationCacheCreateFlagsEXT>(0);
    size_t initialDataSize = 0;
    const void* pInitialData = nullptr;
};
struct ShaderModuleValidationCacheCreateInfoEXT {
    StructureType sType = StructureType::eShaderModuleValidationCacheCreateInfoEXT;
    const void* pNext = nullptr;
    ValidationCacheEXT validationCache;
};
struct PhysicalDeviceMaintenance3Properties {
    StructureType sType = StructureType::ePhysicalDeviceMaintenance3Properties;
    void* pNext = nullptr;
    uint32_t maxPerSetDescriptors = 0;
    DeviceSize maxMemoryAllocationSize = 0;
};
using PhysicalDeviceMaintenance3PropertiesKHR = PhysicalDeviceMaintenance3Properties;
struct DescriptorSetLayoutSupport {
    StructureType sType = StructureType::eDescriptorSetLayoutSupport;
    void* pNext = nullptr;
    bool supported = false;
};
using DescriptorSetLayoutSupportKHR = DescriptorSetLayoutSupport;
struct PhysicalDeviceShaderDrawParametersFeatures {
    StructureType sType = StructureType::ePhysicalDeviceShaderDrawParametersFeatures;
    void* pNext = nullptr;
    bool shaderDrawParameters = false;
};
using PhysicalDeviceShaderDrawParameterFeatures = PhysicalDeviceShaderDrawParametersFeatures;
struct PhysicalDeviceShaderFloat16Int8Features {
    StructureType sType = StructureType::ePhysicalDeviceShaderFloat16Int8Features;
    void* pNext = nullptr;
    bool shaderFloat16 = false;
    bool shaderInt8 = false;
};
using PhysicalDeviceShaderFloat16Int8FeaturesKHR = PhysicalDeviceShaderFloat16Int8Features;
using PhysicalDeviceFloat16Int8FeaturesKHR = PhysicalDeviceShaderFloat16Int8Features;
struct PhysicalDeviceFloatControlsProperties {
    StructureType sType = StructureType::ePhysicalDeviceFloatControlsProperties;
    void* pNext = nullptr;
    ShaderFloatControlsIndependence denormBehaviorIndependence = static_cast<ShaderFloatControlsIndependence>(0);
    ShaderFloatControlsIndependence roundingModeIndependence = static_cast<ShaderFloatControlsIndependence>(0);
    bool shaderSignedZeroInfNanPreserveFloat16 = false;
    bool shaderSignedZeroInfNanPreserveFloat32 = false;
    bool shaderSignedZeroInfNanPreserveFloat64 = false;
    bool shaderDenormPreserveFloat16 = false;
    bool shaderDenormPreserveFloat32 = false;
    bool shaderDenormPreserveFloat64 = false;
    bool shaderDenormFlushToZeroFloat16 = false;
    bool shaderDenormFlushToZeroFloat32 = false;
    bool shaderDenormFlushToZeroFloat64 = false;
    bool shaderRoundingModeRTEFloat16 = false;
    bool shaderRoundingModeRTEFloat32 = false;
    bool shaderRoundingModeRTEFloat64 = false;
    bool shaderRoundingModeRTZFloat16 = false;
    bool shaderRoundingModeRTZFloat32 = false;
    bool shaderRoundingModeRTZFloat64 = false;
};
using PhysicalDeviceFloatControlsPropertiesKHR = PhysicalDeviceFloatControlsProperties;
struct PhysicalDeviceHostQueryResetFeatures {
    StructureType sType = StructureType::ePhysicalDeviceHostQueryResetFeatures;
    void* pNext = nullptr;
    bool hostQueryReset = false;
};
using PhysicalDeviceHostQueryResetFeaturesEXT = PhysicalDeviceHostQueryResetFeatures;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct NativeBufferUsage2ANDROID {
    uint64_t consumer = 0;
    uint64_t producer = 0;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct NativeBufferANDROID {
    StructureType sType = StructureType::eNativeBufferANDROID;
    const void* pNext = nullptr;
    const void* handle = nullptr;
    int stride = 0;
    int format = 0;
    int usage = 0;
    NativeBufferUsage2ANDROID usage2;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct SwapchainImageCreateInfoANDROID {
    StructureType sType = StructureType::eSwapchainImageCreateInfoANDROID;
    const void* pNext = nullptr;
    SwapchainImageUsageFlagsANDROID usage = static_cast<SwapchainImageUsageFlagsANDROID>(0);
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct PhysicalDevicePresentationPropertiesANDROID {
    StructureType sType = StructureType::ePhysicalDevicePresentationPropertiesANDROID;
    const void* pNext = nullptr;
    bool sharedImage = false;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
struct ShaderResourceUsageAMD {
    uint32_t numUsedVgprs = 0;
    uint32_t numUsedSgprs = 0;
    uint32_t ldsSizePerLocalWorkGroup = 0;
    size_t ldsUsageSizeInBytes = 0;
    size_t scratchMemUsageInBytes = 0;
};
struct ShaderStatisticsInfoAMD {
    ShaderStageFlags shaderStageMask = static_cast<ShaderStageFlags>(0);
    ShaderResourceUsageAMD resourceUsage;
    uint32_t numPhysicalVgprs = 0;
    uint32_t numPhysicalSgprs = 0;
    uint32_t numAvailableVgprs = 0;
    uint32_t numAvailableSgprs = 0;
    uint32_t computeWorkGroupSize[3] = {};
};
struct DeviceQueueGlobalPriorityCreateInfoEXT {
    StructureType sType = StructureType::eDeviceQueueGlobalPriorityCreateInfoEXT;
    const void* pNext = nullptr;
    QueueGlobalPriorityEXT globalPriority = static_cast<QueueGlobalPriorityEXT>(0);
};
struct DebugUtilsObjectNameInfoEXT {
    StructureType sType = StructureType::eDebugUtilsObjectNameInfoEXT;
    const void* pNext = nullptr;
    ObjectType objectType = static_cast<ObjectType>(0);
    uint64_t objectHandle = 0;
    const char* pObjectName = nullptr;
};
struct DebugUtilsObjectTagInfoEXT {
    StructureType sType = StructureType::eDebugUtilsObjectTagInfoEXT;
    const void* pNext = nullptr;
    ObjectType objectType = static_cast<ObjectType>(0);
    uint64_t objectHandle = 0;
    uint64_t tagName = 0;
    size_t tagSize = 0;
    const void* pTag = nullptr;
};
struct DebugUtilsLabelEXT {
    StructureType sType = StructureType::eDebugUtilsLabelEXT;
    const void* pNext = nullptr;
    const char* pLabelName = nullptr;
    float color[4] = {};
};
struct DebugUtilsMessengerCreateInfoEXT {
    StructureType sType = StructureType::eDebugUtilsMessengerCreateInfoEXT;
    const void* pNext = nullptr;
    DebugUtilsMessengerCreateFlagsEXT flags = static_cast<DebugUtilsMessengerCreateFlagsEXT>(0);
    DebugUtilsMessageSeverityFlagsEXT messageSeverity = static_cast<DebugUtilsMessageSeverityFlagsEXT>(0);
    DebugUtilsMessageTypeFlagsEXT messageType = static_cast<DebugUtilsMessageTypeFlagsEXT>(0);
    PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback;
    void* pUserData = nullptr;
};
struct DebugUtilsMessengerCallbackDataEXT {
    StructureType sType = StructureType::eDebugUtilsMessengerCallbackDataEXT;
    const void* pNext = nullptr;
    DebugUtilsMessengerCallbackDataFlagsEXT flags = static_cast<DebugUtilsMessengerCallbackDataFlagsEXT>(0);
    const char* pMessageIdName = nullptr;
    int32_t messageIdNumber = 0;
    const char* pMessage = nullptr;
    uint32_t queueLabelCount = 0;
    const DebugUtilsLabelEXT* pQueueLabels = nullptr;
    uint32_t cmdBufLabelCount = 0;
    const DebugUtilsLabelEXT* pCmdBufLabels = nullptr;
    uint32_t objectCount = 0;
    const DebugUtilsObjectNameInfoEXT* pObjects = nullptr;
};
struct ImportMemoryHostPointerInfoEXT {
    StructureType sType = StructureType::eImportMemoryHostPointerInfoEXT;
    const void* pNext = nullptr;
    ExternalMemoryHandleTypeFlagBits handleType = static_cast<ExternalMemoryHandleTypeFlagBits>(0);
    void* pHostPointer = nullptr;
};
struct MemoryHostPointerPropertiesEXT {
    StructureType sType = StructureType::eMemoryHostPointerPropertiesEXT;
    void* pNext = nullptr;
    uint32_t memoryTypeBits = 0;
};
struct PhysicalDeviceExternalMemoryHostPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceExternalMemoryHostPropertiesEXT;
    void* pNext = nullptr;
    DeviceSize minImportedHostPointerAlignment = 0;
};
struct PhysicalDeviceConservativeRasterizationPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceConservativeRasterizationPropertiesEXT;
    void* pNext = nullptr;
    float primitiveOverestimationSize = 0.f;
    float maxExtraPrimitiveOverestimationSize = 0.f;
    float extraPrimitiveOverestimationSizeGranularity = 0.f;
    bool primitiveUnderestimation = false;
    bool conservativePointAndLineRasterization = false;
    bool degenerateTrianglesRasterized = false;
    bool degenerateLinesRasterized = false;
    bool fullyCoveredFragmentShaderInputVariable = false;
    bool conservativeRasterizationPostDepthCoverage = false;
};
struct CalibratedTimestampInfoEXT {
    StructureType sType = StructureType::eCalibratedTimestampInfoEXT;
    const void* pNext = nullptr;
    TimeDomainEXT timeDomain = static_cast<TimeDomainEXT>(0);
};
struct PhysicalDeviceShaderCorePropertiesAMD {
    StructureType sType = StructureType::ePhysicalDeviceShaderCorePropertiesAMD;
    void* pNext = nullptr;
    uint32_t shaderEngineCount = 0;
    uint32_t shaderArraysPerEngineCount = 0;
    uint32_t computeUnitsPerShaderArray = 0;
    uint32_t simdPerComputeUnit = 0;
    uint32_t wavefrontsPerSimd = 0;
    uint32_t wavefrontSize = 0;
    uint32_t sgprsPerSimd = 0;
    uint32_t minSgprAllocation = 0;
    uint32_t maxSgprAllocation = 0;
    uint32_t sgprAllocationGranularity = 0;
    uint32_t vgprsPerSimd = 0;
    uint32_t minVgprAllocation = 0;
    uint32_t maxVgprAllocation = 0;
    uint32_t vgprAllocationGranularity = 0;
};
struct PhysicalDeviceShaderCoreProperties2AMD {
    StructureType sType = StructureType::ePhysicalDeviceShaderCoreProperties2AMD;
    void* pNext = nullptr;
    ShaderCorePropertiesFlagsAMD shaderCoreFeatures = static_cast<ShaderCorePropertiesFlagsAMD>(0);
    uint32_t activeComputeUnitCount = 0;
};
struct PipelineRasterizationConservativeStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineRasterizationConservativeStateCreateInfoEXT;
    const void* pNext = nullptr;
    PipelineRasterizationConservativeStateCreateFlagsEXT flags = static_cast<PipelineRasterizationConservativeStateCreateFlagsEXT>(0);
    ConservativeRasterizationModeEXT conservativeRasterizationMode = static_cast<ConservativeRasterizationModeEXT>(0);
    float extraPrimitiveOverestimationSize = 0.f;
};
struct PhysicalDeviceDescriptorIndexingFeatures {
    StructureType sType = StructureType::ePhysicalDeviceDescriptorIndexingFeatures;
    void* pNext = nullptr;
    bool shaderInputAttachmentArrayDynamicIndexing = false;
    bool shaderUniformTexelBufferArrayDynamicIndexing = false;
    bool shaderStorageTexelBufferArrayDynamicIndexing = false;
    bool shaderUniformBufferArrayNonUniformIndexing = false;
    bool shaderSampledImageArrayNonUniformIndexing = false;
    bool shaderStorageBufferArrayNonUniformIndexing = false;
    bool shaderStorageImageArrayNonUniformIndexing = false;
    bool shaderInputAttachmentArrayNonUniformIndexing = false;
    bool shaderUniformTexelBufferArrayNonUniformIndexing = false;
    bool shaderStorageTexelBufferArrayNonUniformIndexing = false;
    bool descriptorBindingUniformBufferUpdateAfterBind = false;
    bool descriptorBindingSampledImageUpdateAfterBind = false;
    bool descriptorBindingStorageImageUpdateAfterBind = false;
    bool descriptorBindingStorageBufferUpdateAfterBind = false;
    bool descriptorBindingUniformTexelBufferUpdateAfterBind = false;
    bool descriptorBindingStorageTexelBufferUpdateAfterBind = false;
    bool descriptorBindingUpdateUnusedWhilePending = false;
    bool descriptorBindingPartiallyBound = false;
    bool descriptorBindingVariableDescriptorCount = false;
    bool runtimeDescriptorArray = false;
};
using PhysicalDeviceDescriptorIndexingFeaturesEXT = PhysicalDeviceDescriptorIndexingFeatures;
struct PhysicalDeviceDescriptorIndexingProperties {
    StructureType sType = StructureType::ePhysicalDeviceDescriptorIndexingProperties;
    void* pNext = nullptr;
    uint32_t maxUpdateAfterBindDescriptorsInAllPools = 0;
    bool shaderUniformBufferArrayNonUniformIndexingNative = false;
    bool shaderSampledImageArrayNonUniformIndexingNative = false;
    bool shaderStorageBufferArrayNonUniformIndexingNative = false;
    bool shaderStorageImageArrayNonUniformIndexingNative = false;
    bool shaderInputAttachmentArrayNonUniformIndexingNative = false;
    bool robustBufferAccessUpdateAfterBind = false;
    bool quadDivergentImplicitLod = false;
    uint32_t maxPerStageDescriptorUpdateAfterBindSamplers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindUniformBuffers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageBuffers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindSampledImages = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageImages = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindInputAttachments = 0;
    uint32_t maxPerStageUpdateAfterBindResources = 0;
    uint32_t maxDescriptorSetUpdateAfterBindSamplers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = 0;
    uint32_t maxDescriptorSetUpdateAfterBindSampledImages = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageImages = 0;
    uint32_t maxDescriptorSetUpdateAfterBindInputAttachments = 0;
};
using PhysicalDeviceDescriptorIndexingPropertiesEXT = PhysicalDeviceDescriptorIndexingProperties;
struct DescriptorSetLayoutBindingFlagsCreateInfo {
    StructureType sType = StructureType::eDescriptorSetLayoutBindingFlagsCreateInfo;
    const void* pNext = nullptr;
    uint32_t bindingCount = 0;
    const DescriptorBindingFlags* pBindingFlags = nullptr;
};
using DescriptorSetLayoutBindingFlagsCreateInfoEXT = DescriptorSetLayoutBindingFlagsCreateInfo;
struct DescriptorSetVariableDescriptorCountAllocateInfo {
    StructureType sType = StructureType::eDescriptorSetVariableDescriptorCountAllocateInfo;
    const void* pNext = nullptr;
    uint32_t descriptorSetCount = 0;
    const uint32_t* pDescriptorCounts = nullptr;
};
using DescriptorSetVariableDescriptorCountAllocateInfoEXT = DescriptorSetVariableDescriptorCountAllocateInfo;
struct DescriptorSetVariableDescriptorCountLayoutSupport {
    StructureType sType = StructureType::eDescriptorSetVariableDescriptorCountLayoutSupport;
    void* pNext = nullptr;
    uint32_t maxVariableDescriptorCount = 0;
};
using DescriptorSetVariableDescriptorCountLayoutSupportEXT = DescriptorSetVariableDescriptorCountLayoutSupport;
struct AttachmentDescription2 {
    StructureType sType = StructureType::eAttachmentDescription2;
    const void* pNext = nullptr;
    AttachmentDescriptionFlags flags = static_cast<AttachmentDescriptionFlags>(0);
    Format format = static_cast<Format>(0);
    SampleCountFlagBits samples = static_cast<SampleCountFlagBits>(0);
    AttachmentLoadOp loadOp = static_cast<AttachmentLoadOp>(0);
    AttachmentStoreOp storeOp = static_cast<AttachmentStoreOp>(0);
    AttachmentLoadOp stencilLoadOp = static_cast<AttachmentLoadOp>(0);
    AttachmentStoreOp stencilStoreOp = static_cast<AttachmentStoreOp>(0);
    ImageLayout initialLayout = static_cast<ImageLayout>(0);
    ImageLayout finalLayout = static_cast<ImageLayout>(0);
};
using AttachmentDescription2KHR = AttachmentDescription2;
struct AttachmentReference2 {
    StructureType sType = StructureType::eAttachmentReference2;
    const void* pNext = nullptr;
    uint32_t attachment = 0;
    ImageLayout layout = static_cast<ImageLayout>(0);
    ImageAspectFlags aspectMask = static_cast<ImageAspectFlags>(0);
};
using AttachmentReference2KHR = AttachmentReference2;
struct SubpassDescription2 {
    StructureType sType = StructureType::eSubpassDescription2;
    const void* pNext = nullptr;
    SubpassDescriptionFlags flags = static_cast<SubpassDescriptionFlags>(0);
    PipelineBindPoint pipelineBindPoint = static_cast<PipelineBindPoint>(0);
    uint32_t viewMask = 0;
    uint32_t inputAttachmentCount = 0;
    const AttachmentReference2* pInputAttachments = nullptr;
    uint32_t colorAttachmentCount = 0;
    const AttachmentReference2* pColorAttachments = nullptr;
    const AttachmentReference2* pResolveAttachments = nullptr;
    const AttachmentReference2* pDepthStencilAttachment = nullptr;
    uint32_t preserveAttachmentCount = 0;
    const uint32_t* pPreserveAttachments = nullptr;
};
using SubpassDescription2KHR = SubpassDescription2;
struct SubpassDependency2 {
    StructureType sType = StructureType::eSubpassDependency2;
    const void* pNext = nullptr;
    uint32_t srcSubpass = 0;
    uint32_t dstSubpass = 0;
    PipelineStageFlags srcStageMask = static_cast<PipelineStageFlags>(0);
    PipelineStageFlags dstStageMask = static_cast<PipelineStageFlags>(0);
    AccessFlags srcAccessMask = static_cast<AccessFlags>(0);
    AccessFlags dstAccessMask = static_cast<AccessFlags>(0);
    DependencyFlags dependencyFlags = static_cast<DependencyFlags>(0);
    int32_t viewOffset = 0;
};
using SubpassDependency2KHR = SubpassDependency2;
struct RenderPassCreateInfo2 {
    StructureType sType = StructureType::eRenderPassCreateInfo2;
    const void* pNext = nullptr;
    RenderPassCreateFlags flags = static_cast<RenderPassCreateFlags>(0);
    uint32_t attachmentCount = 0;
    const AttachmentDescription2* pAttachments = nullptr;
    uint32_t subpassCount = 0;
    const SubpassDescription2* pSubpasses = nullptr;
    uint32_t dependencyCount = 0;
    const SubpassDependency2* pDependencies = nullptr;
    uint32_t correlatedViewMaskCount = 0;
    const uint32_t* pCorrelatedViewMasks = nullptr;
};
using RenderPassCreateInfo2KHR = RenderPassCreateInfo2;
struct SubpassBeginInfo {
    StructureType sType = StructureType::eSubpassBeginInfo;
    const void* pNext = nullptr;
    SubpassContents contents = static_cast<SubpassContents>(0);
};
using SubpassBeginInfoKHR = SubpassBeginInfo;
struct SubpassEndInfo {
    StructureType sType = StructureType::eSubpassEndInfo;
    const void* pNext = nullptr;
};
using SubpassEndInfoKHR = SubpassEndInfo;
struct PhysicalDeviceTimelineSemaphoreFeatures {
    StructureType sType = StructureType::ePhysicalDeviceTimelineSemaphoreFeatures;
    void* pNext = nullptr;
    bool timelineSemaphore = false;
};
using PhysicalDeviceTimelineSemaphoreFeaturesKHR = PhysicalDeviceTimelineSemaphoreFeatures;
struct PhysicalDeviceTimelineSemaphoreProperties {
    StructureType sType = StructureType::ePhysicalDeviceTimelineSemaphoreProperties;
    void* pNext = nullptr;
    uint64_t maxTimelineSemaphoreValueDifference = 0;
};
using PhysicalDeviceTimelineSemaphorePropertiesKHR = PhysicalDeviceTimelineSemaphoreProperties;
struct SemaphoreTypeCreateInfo {
    StructureType sType = StructureType::eSemaphoreTypeCreateInfo;
    const void* pNext = nullptr;
    SemaphoreType semaphoreType = static_cast<SemaphoreType>(0);
    uint64_t initialValue = 0;
};
using SemaphoreTypeCreateInfoKHR = SemaphoreTypeCreateInfo;
struct TimelineSemaphoreSubmitInfo {
    StructureType sType = StructureType::eTimelineSemaphoreSubmitInfo;
    const void* pNext = nullptr;
    uint32_t waitSemaphoreValueCount = 0;
    const uint64_t* pWaitSemaphoreValues = nullptr;
    uint32_t signalSemaphoreValueCount = 0;
    const uint64_t* pSignalSemaphoreValues = nullptr;
};
using TimelineSemaphoreSubmitInfoKHR = TimelineSemaphoreSubmitInfo;
struct SemaphoreWaitInfo {
    StructureType sType = StructureType::eSemaphoreWaitInfo;
    const void* pNext = nullptr;
    SemaphoreWaitFlags flags = static_cast<SemaphoreWaitFlags>(0);
    uint32_t semaphoreCount = 0;
    const Semaphore* pSemaphores = nullptr;
    const uint64_t* pValues = nullptr;
};
using SemaphoreWaitInfoKHR = SemaphoreWaitInfo;
struct SemaphoreSignalInfo {
    StructureType sType = StructureType::eSemaphoreSignalInfo;
    const void* pNext = nullptr;
    Semaphore semaphore;
    uint64_t value = 0;
};
using SemaphoreSignalInfoKHR = SemaphoreSignalInfo;
struct VertexInputBindingDivisorDescriptionEXT {
    uint32_t binding = 0;
    uint32_t divisor = 0;
};
struct PipelineVertexInputDivisorStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineVertexInputDivisorStateCreateInfoEXT;
    const void* pNext = nullptr;
    uint32_t vertexBindingDivisorCount = 0;
    const VertexInputBindingDivisorDescriptionEXT* pVertexBindingDivisors = nullptr;
};
struct PhysicalDeviceVertexAttributeDivisorPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceVertexAttributeDivisorPropertiesEXT;
    void* pNext = nullptr;
    uint32_t maxVertexAttribDivisor = 0;
};
struct PhysicalDevicePCIBusInfoPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDevicePciBusInfoPropertiesEXT;
    void* pNext = nullptr;
    uint32_t pciDomain = 0;
    uint32_t pciBus = 0;
    uint32_t pciDevice = 0;
    uint32_t pciFunction = 0;
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct ImportAndroidHardwareBufferInfoANDROID {
    StructureType sType = StructureType::eImportAndroidHardwareBufferInfoANDROID;
    const void* pNext = nullptr;
    AHardwareBuffer* buffer = nullptr;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct AndroidHardwareBufferUsageANDROID {
    StructureType sType = StructureType::eAndroidHardwareBufferUsageANDROID;
    void* pNext = nullptr;
    uint64_t androidHardwareBufferUsage = 0;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct AndroidHardwareBufferPropertiesANDROID {
    StructureType sType = StructureType::eAndroidHardwareBufferPropertiesANDROID;
    void* pNext = nullptr;
    DeviceSize allocationSize = 0;
    uint32_t memoryTypeBits = 0;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct MemoryGetAndroidHardwareBufferInfoANDROID {
    StructureType sType = StructureType::eMemoryGetAndroidHardwareBufferInfoANDROID;
    const void* pNext = nullptr;
    DeviceMemory memory;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct AndroidHardwareBufferFormatPropertiesANDROID {
    StructureType sType = StructureType::eAndroidHardwareBufferFormatPropertiesANDROID;
    void* pNext = nullptr;
    Format format = static_cast<Format>(0);
    uint64_t externalFormat = 0;
    FormatFeatureFlags formatFeatures = static_cast<FormatFeatureFlags>(0);
    ComponentMapping samplerYcbcrConversionComponents;
    SamplerYcbcrModelConversion suggestedYcbcrModel = static_cast<SamplerYcbcrModelConversion>(0);
    SamplerYcbcrRange suggestedYcbcrRange = static_cast<SamplerYcbcrRange>(0);
    ChromaLocation suggestedXChromaOffset = static_cast<ChromaLocation>(0);
    ChromaLocation suggestedYChromaOffset = static_cast<ChromaLocation>(0);
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
struct CommandBufferInheritanceConditionalRenderingInfoEXT {
    StructureType sType = StructureType::eCommandBufferInheritanceConditionalRenderingInfoEXT;
    const void* pNext = nullptr;
    bool conditionalRenderingEnable = false;
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct ExternalFormatANDROID {
    StructureType sType = StructureType::eExternalFormatANDROID;
    void* pNext = nullptr;
    uint64_t externalFormat = 0;
};
#endif // VK_USE_PLATFORM_ANDROID_KHR
struct PhysicalDevice8BitStorageFeatures {
    StructureType sType = StructureType::ePhysicalDevice8BitStorageFeatures;
    void* pNext = nullptr;
    bool storageBuffer8BitAccess = false;
    bool uniformAndStorageBuffer8BitAccess = false;
    bool storagePushConstant8 = false;
};
using PhysicalDevice8BitStorageFeaturesKHR = PhysicalDevice8BitStorageFeatures;
struct PhysicalDeviceConditionalRenderingFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceConditionalRenderingFeaturesEXT;
    void* pNext = nullptr;
    bool conditionalRendering = false;
    bool inheritedConditionalRendering = false;
};
struct PhysicalDeviceVulkanMemoryModelFeatures {
    StructureType sType = StructureType::ePhysicalDeviceVulkanMemoryModelFeatures;
    void* pNext = nullptr;
    bool vulkanMemoryModel = false;
    bool vulkanMemoryModelDeviceScope = false;
    bool vulkanMemoryModelAvailabilityVisibilityChains = false;
};
using PhysicalDeviceVulkanMemoryModelFeaturesKHR = PhysicalDeviceVulkanMemoryModelFeatures;
struct PhysicalDeviceShaderAtomicInt64Features {
    StructureType sType = StructureType::ePhysicalDeviceShaderAtomicInt64Features;
    void* pNext = nullptr;
    bool shaderBufferInt64Atomics = false;
    bool shaderSharedInt64Atomics = false;
};
using PhysicalDeviceShaderAtomicInt64FeaturesKHR = PhysicalDeviceShaderAtomicInt64Features;
struct PhysicalDeviceVertexAttributeDivisorFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceVertexAttributeDivisorFeaturesEXT;
    void* pNext = nullptr;
    bool vertexAttributeInstanceRateDivisor = false;
    bool vertexAttributeInstanceRateZeroDivisor = false;
};
struct QueueFamilyCheckpointPropertiesNV {
    StructureType sType = StructureType::eQueueFamilyCheckpointPropertiesNV;
    void* pNext = nullptr;
    PipelineStageFlags checkpointExecutionStageMask = static_cast<PipelineStageFlags>(0);
};
struct CheckpointDataNV {
    StructureType sType = StructureType::eCheckpointDataNV;
    void* pNext = nullptr;
    PipelineStageFlagBits stage = static_cast<PipelineStageFlagBits>(0);
    void* pCheckpointMarker = nullptr;
};
struct PhysicalDeviceDepthStencilResolveProperties {
    StructureType sType = StructureType::ePhysicalDeviceDepthStencilResolveProperties;
    void* pNext = nullptr;
    ResolveModeFlags supportedDepthResolveModes = static_cast<ResolveModeFlags>(0);
    ResolveModeFlags supportedStencilResolveModes = static_cast<ResolveModeFlags>(0);
    bool independentResolveNone = false;
    bool independentResolve = false;
};
using PhysicalDeviceDepthStencilResolvePropertiesKHR = PhysicalDeviceDepthStencilResolveProperties;
struct SubpassDescriptionDepthStencilResolve {
    StructureType sType = StructureType::eSubpassDescriptionDepthStencilResolve;
    const void* pNext = nullptr;
    ResolveModeFlagBits depthResolveMode = static_cast<ResolveModeFlagBits>(0);
    ResolveModeFlagBits stencilResolveMode = static_cast<ResolveModeFlagBits>(0);
    const AttachmentReference2* pDepthStencilResolveAttachment = nullptr;
};
using SubpassDescriptionDepthStencilResolveKHR = SubpassDescriptionDepthStencilResolve;
struct ImageViewASTCDecodeModeEXT {
    StructureType sType = StructureType::eImageViewAstcDecodeModeEXT;
    const void* pNext = nullptr;
    Format decodeMode = static_cast<Format>(0);
};
struct PhysicalDeviceASTCDecodeFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceAstcDecodeFeaturesEXT;
    void* pNext = nullptr;
    bool decodeModeSharedExponent = false;
};
struct PhysicalDeviceTransformFeedbackFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceTransformFeedbackFeaturesEXT;
    void* pNext = nullptr;
    bool transformFeedback = false;
    bool geometryStreams = false;
};
struct PhysicalDeviceTransformFeedbackPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceTransformFeedbackPropertiesEXT;
    void* pNext = nullptr;
    uint32_t maxTransformFeedbackStreams = 0;
    uint32_t maxTransformFeedbackBuffers = 0;
    DeviceSize maxTransformFeedbackBufferSize = 0;
    uint32_t maxTransformFeedbackStreamDataSize = 0;
    uint32_t maxTransformFeedbackBufferDataSize = 0;
    uint32_t maxTransformFeedbackBufferDataStride = 0;
    bool transformFeedbackQueries = false;
    bool transformFeedbackStreamsLinesTriangles = false;
    bool transformFeedbackRasterizationStreamSelect = false;
    bool transformFeedbackDraw = false;
};
struct PipelineRasterizationStateStreamCreateInfoEXT {
    StructureType sType = StructureType::ePipelineRasterizationStateStreamCreateInfoEXT;
    const void* pNext = nullptr;
    PipelineRasterizationStateStreamCreateFlagsEXT flags = static_cast<PipelineRasterizationStateStreamCreateFlagsEXT>(0);
    uint32_t rasterizationStream = 0;
};
struct PhysicalDeviceRepresentativeFragmentTestFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceRepresentativeFragmentTestFeaturesNV;
    void* pNext = nullptr;
    bool representativeFragmentTest = false;
};
struct PipelineRepresentativeFragmentTestStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineRepresentativeFragmentTestStateCreateInfoNV;
    const void* pNext = nullptr;
    bool representativeFragmentTestEnable = false;
};
struct PhysicalDeviceExclusiveScissorFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceExclusiveScissorFeaturesNV;
    void* pNext = nullptr;
    bool exclusiveScissor = false;
};
struct PipelineViewportExclusiveScissorStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineViewportExclusiveScissorStateCreateInfoNV;
    const void* pNext = nullptr;
    uint32_t exclusiveScissorCount = 0;
    const Rect2D* pExclusiveScissors = nullptr;
};
struct PhysicalDeviceCornerSampledImageFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceCornerSampledImageFeaturesNV;
    void* pNext = nullptr;
    bool cornerSampledImage = false;
};
struct PhysicalDeviceComputeShaderDerivativesFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceComputeShaderDerivativesFeaturesNV;
    void* pNext = nullptr;
    bool computeDerivativeGroupQuads = false;
    bool computeDerivativeGroupLinear = false;
};
struct PhysicalDeviceFragmentShaderBarycentricFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceFragmentShaderBarycentricFeaturesNV;
    void* pNext = nullptr;
    bool fragmentShaderBarycentric = false;
};
struct PhysicalDeviceShaderImageFootprintFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceShaderImageFootprintFeaturesNV;
    void* pNext = nullptr;
    bool imageFootprint = false;
};
struct PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;
    void* pNext = nullptr;
    bool dedicatedAllocationImageAliasing = false;
};
struct ShadingRatePaletteNV {
    uint32_t shadingRatePaletteEntryCount = 0;
    const ShadingRatePaletteEntryNV* pShadingRatePaletteEntries = nullptr;
};
struct PipelineViewportShadingRateImageStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineViewportShadingRateImageStateCreateInfoNV;
    const void* pNext = nullptr;
    bool shadingRateImageEnable = false;
    uint32_t viewportCount = 0;
    const ShadingRatePaletteNV* pShadingRatePalettes = nullptr;
};
struct PhysicalDeviceShadingRateImageFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceShadingRateImageFeaturesNV;
    void* pNext = nullptr;
    bool shadingRateImage = false;
    bool shadingRateCoarseSampleOrder = false;
};
struct PhysicalDeviceShadingRateImagePropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceShadingRateImagePropertiesNV;
    void* pNext = nullptr;
    Extent2D shadingRateTexelSize;
    uint32_t shadingRatePaletteSize = 0;
    uint32_t shadingRateMaxCoarseSamples = 0;
};
struct CoarseSampleLocationNV {
    uint32_t pixelX = 0;
    uint32_t pixelY = 0;
    uint32_t sample = 0;
};
struct CoarseSampleOrderCustomNV {
    ShadingRatePaletteEntryNV shadingRate = static_cast<ShadingRatePaletteEntryNV>(0);
    uint32_t sampleCount = 0;
    uint32_t sampleLocationCount = 0;
    const CoarseSampleLocationNV* pSampleLocations = nullptr;
};
struct PipelineViewportCoarseSampleOrderStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineViewportCoarseSampleOrderStateCreateInfoNV;
    const void* pNext = nullptr;
    CoarseSampleOrderTypeNV sampleOrderType = static_cast<CoarseSampleOrderTypeNV>(0);
    uint32_t customSampleOrderCount = 0;
    const CoarseSampleOrderCustomNV* pCustomSampleOrders = nullptr;
};
struct PhysicalDeviceMeshShaderFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceMeshShaderFeaturesNV;
    void* pNext = nullptr;
    bool taskShader = false;
    bool meshShader = false;
};
struct PhysicalDeviceMeshShaderPropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceMeshShaderPropertiesNV;
    void* pNext = nullptr;
    uint32_t maxDrawMeshTasksCount = 0;
    uint32_t maxTaskWorkGroupInvocations = 0;
    uint32_t maxTaskWorkGroupSize[3] = {};
    uint32_t maxTaskTotalMemorySize = 0;
    uint32_t maxTaskOutputCount = 0;
    uint32_t maxMeshWorkGroupInvocations = 0;
    uint32_t maxMeshWorkGroupSize[3] = {};
    uint32_t maxMeshTotalMemorySize = 0;
    uint32_t maxMeshOutputVertices = 0;
    uint32_t maxMeshOutputPrimitives = 0;
    uint32_t maxMeshMultiviewViewCount = 0;
    uint32_t meshOutputPerVertexGranularity = 0;
    uint32_t meshOutputPerPrimitiveGranularity = 0;
};
struct DrawMeshTasksIndirectCommandNV {
    uint32_t taskCount = 0;
    uint32_t firstTask = 0;
};
struct RayTracingShaderGroupCreateInfoNV {
    StructureType sType = StructureType::eRayTracingShaderGroupCreateInfoNV;
    const void* pNext = nullptr;
    RayTracingShaderGroupTypeKHR type = static_cast<RayTracingShaderGroupTypeKHR>(0);
    uint32_t generalShader = 0;
    uint32_t closestHitShader = 0;
    uint32_t anyHitShader = 0;
    uint32_t intersectionShader = 0;
};
struct RayTracingShaderGroupCreateInfoKHR {
    StructureType sType = StructureType::eRayTracingShaderGroupCreateInfoKHR;
    const void* pNext = nullptr;
    RayTracingShaderGroupTypeKHR type = static_cast<RayTracingShaderGroupTypeKHR>(0);
    uint32_t generalShader = 0;
    uint32_t closestHitShader = 0;
    uint32_t anyHitShader = 0;
    uint32_t intersectionShader = 0;
    const void* pShaderGroupCaptureReplayHandle = nullptr;
};
struct RayTracingPipelineCreateInfoNV {
    StructureType sType = StructureType::eRayTracingPipelineCreateInfoNV;
    const void* pNext = nullptr;
    PipelineCreateFlags flags = static_cast<PipelineCreateFlags>(0);
    uint32_t stageCount = 0;
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    uint32_t groupCount = 0;
    const RayTracingShaderGroupCreateInfoNV* pGroups = nullptr;
    uint32_t maxRecursionDepth = 0;
    PipelineLayout layout;
    Pipeline basePipelineHandle;
    int32_t basePipelineIndex = 0;
};
struct RayTracingPipelineCreateInfoKHR {
    StructureType sType = StructureType::eRayTracingPipelineCreateInfoKHR;
    const void* pNext = nullptr;
    PipelineCreateFlags flags = static_cast<PipelineCreateFlags>(0);
    uint32_t stageCount = 0;
    const PipelineShaderStageCreateInfo* pStages = nullptr;
    uint32_t groupCount = 0;
    const RayTracingShaderGroupCreateInfoKHR* pGroups = nullptr;
    uint32_t maxRecursionDepth = 0;
    PipelineLibraryCreateInfoKHR libraries;
    const RayTracingPipelineInterfaceCreateInfoKHR* pLibraryInterface = nullptr;
    PipelineLayout layout;
    Pipeline basePipelineHandle;
    int32_t basePipelineIndex = 0;
};
struct GeometryTrianglesNV {
    StructureType sType = StructureType::eGeometryTrianglesNV;
    const void* pNext = nullptr;
    Buffer vertexData;
    DeviceSize vertexOffset = 0;
    uint32_t vertexCount = 0;
    DeviceSize vertexStride = 0;
    Format vertexFormat = static_cast<Format>(0);
    Buffer indexData;
    DeviceSize indexOffset = 0;
    uint32_t indexCount = 0;
    IndexType indexType = static_cast<IndexType>(0);
    Buffer transformData;
    DeviceSize transformOffset = 0;
};
struct GeometryAABBNV {
    StructureType sType = StructureType::eGeometryAabbNV;
    const void* pNext = nullptr;
    Buffer aabbData;
    uint32_t numAABBs = 0;
    uint32_t stride = 0;
    DeviceSize offset = 0;
};
struct GeometryDataNV {
    GeometryTrianglesNV triangles;
    GeometryAABBNV aabbs;
};
struct GeometryNV {
    StructureType sType = StructureType::eGeometryNV;
    const void* pNext = nullptr;
    GeometryTypeKHR geometryType = static_cast<GeometryTypeKHR>(0);
    GeometryDataNV geometry;
    GeometryFlagsKHR flags = static_cast<GeometryFlagsKHR>(0);
};
struct AccelerationStructureInfoNV {
    StructureType sType = StructureType::eAccelerationStructureInfoNV;
    const void* pNext = nullptr;
    AccelerationStructureTypeNV type;
    BuildAccelerationStructureFlagsNV flags = static_cast<BuildAccelerationStructureFlagsNV>(0);
    uint32_t instanceCount = 0;
    uint32_t geometryCount = 0;
    const GeometryNV* pGeometries = nullptr;
};
struct AccelerationStructureCreateInfoNV {
    StructureType sType = StructureType::eAccelerationStructureCreateInfoNV;
    const void* pNext = nullptr;
    DeviceSize compactedSize = 0;
    AccelerationStructureInfoNV info;
};
struct BindAccelerationStructureMemoryInfoKHR {
    StructureType sType = StructureType::eBindAccelerationStructureMemoryInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureKHR accelerationStructure;
    DeviceMemory memory;
    DeviceSize memoryOffset = 0;
    uint32_t deviceIndexCount = 0;
    const uint32_t* pDeviceIndices = nullptr;
};
using BindAccelerationStructureMemoryInfoNV = BindAccelerationStructureMemoryInfoKHR;
struct WriteDescriptorSetAccelerationStructureKHR {
    StructureType sType = StructureType::eWriteDescriptorSetAccelerationStructureKHR;
    const void* pNext = nullptr;
    uint32_t accelerationStructureCount = 0;
    const AccelerationStructureKHR* pAccelerationStructures = nullptr;
};
using WriteDescriptorSetAccelerationStructureNV = WriteDescriptorSetAccelerationStructureKHR;
struct AccelerationStructureMemoryRequirementsInfoKHR {
    StructureType sType = StructureType::eAccelerationStructureMemoryRequirementsInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureMemoryRequirementsTypeKHR type = static_cast<AccelerationStructureMemoryRequirementsTypeKHR>(0);
    AccelerationStructureBuildTypeKHR buildType = static_cast<AccelerationStructureBuildTypeKHR>(0);
    AccelerationStructureKHR accelerationStructure;
};
struct AccelerationStructureMemoryRequirementsInfoNV {
    StructureType sType = StructureType::eAccelerationStructureMemoryRequirementsInfoNV;
    const void* pNext = nullptr;
    AccelerationStructureMemoryRequirementsTypeNV type;
    AccelerationStructureNV accelerationStructure;
};
struct PhysicalDeviceRayTracingFeaturesKHR {
    StructureType sType = StructureType::ePhysicalDeviceRayTracingFeaturesKHR;
    void* pNext = nullptr;
    bool rayTracing = false;
    bool rayTracingShaderGroupHandleCaptureReplay = false;
    bool rayTracingShaderGroupHandleCaptureReplayMixed = false;
    bool rayTracingAccelerationStructureCaptureReplay = false;
    bool rayTracingIndirectTraceRays = false;
    bool rayTracingIndirectAccelerationStructureBuild = false;
    bool rayTracingHostAccelerationStructureCommands = false;
    bool rayQuery = false;
    bool rayTracingPrimitiveCulling = false;
};
struct PhysicalDeviceRayTracingPropertiesKHR {
    StructureType sType = StructureType::ePhysicalDeviceRayTracingPropertiesKHR;
    void* pNext = nullptr;
    uint32_t shaderGroupHandleSize = 0;
    uint32_t maxRecursionDepth = 0;
    uint32_t maxShaderGroupStride = 0;
    uint32_t shaderGroupBaseAlignment = 0;
    uint64_t maxGeometryCount = 0;
    uint64_t maxInstanceCount = 0;
    uint64_t maxPrimitiveCount = 0;
    uint32_t maxDescriptorSetAccelerationStructures = 0;
    uint32_t shaderGroupHandleCaptureReplaySize = 0;
};
struct PhysicalDeviceRayTracingPropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceRayTracingPropertiesNV;
    void* pNext = nullptr;
    uint32_t shaderGroupHandleSize = 0;
    uint32_t maxRecursionDepth = 0;
    uint32_t maxShaderGroupStride = 0;
    uint32_t shaderGroupBaseAlignment = 0;
    uint64_t maxGeometryCount = 0;
    uint64_t maxInstanceCount = 0;
    uint64_t maxTriangleCount = 0;
    uint32_t maxDescriptorSetAccelerationStructures = 0;
};
struct StridedBufferRegionKHR {
    Buffer buffer;
    DeviceSize offset = 0;
    DeviceSize stride = 0;
    DeviceSize size = 0;
};
struct TraceRaysIndirectCommandKHR {
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
};
struct DrmFormatModifierPropertiesListEXT {
    StructureType sType = StructureType::eDrmFormatModifierPropertiesListEXT;
    void* pNext = nullptr;
    uint32_t drmFormatModifierCount = 0;
    DrmFormatModifierPropertiesEXT* pDrmFormatModifierProperties = nullptr;
};
struct DrmFormatModifierPropertiesEXT {
    uint64_t drmFormatModifier = 0;
    uint32_t drmFormatModifierPlaneCount = 0;
    FormatFeatureFlags drmFormatModifierTilingFeatures = static_cast<FormatFeatureFlags>(0);
};
struct PhysicalDeviceImageDrmFormatModifierInfoEXT {
    StructureType sType = StructureType::ePhysicalDeviceImageDrmFormatModifierInfoEXT;
    const void* pNext = nullptr;
    uint64_t drmFormatModifier = 0;
    SharingMode sharingMode = static_cast<SharingMode>(0);
    uint32_t queueFamilyIndexCount = 0;
    const uint32_t* pQueueFamilyIndices = nullptr;
};
struct ImageDrmFormatModifierListCreateInfoEXT {
    StructureType sType = StructureType::eImageDrmFormatModifierListCreateInfoEXT;
    const void* pNext = nullptr;
    uint32_t drmFormatModifierCount = 0;
    const uint64_t* pDrmFormatModifiers = nullptr;
};
struct ImageDrmFormatModifierExplicitCreateInfoEXT {
    StructureType sType = StructureType::eImageDrmFormatModifierExplicitCreateInfoEXT;
    const void* pNext = nullptr;
    uint64_t drmFormatModifier = 0;
    uint32_t drmFormatModifierPlaneCount = 0;
    const SubresourceLayout* pPlaneLayouts = nullptr;
};
struct ImageDrmFormatModifierPropertiesEXT {
    StructureType sType = StructureType::eImageDrmFormatModifierPropertiesEXT;
    void* pNext = nullptr;
    uint64_t drmFormatModifier = 0;
};
struct ImageStencilUsageCreateInfo {
    StructureType sType = StructureType::eImageStencilUsageCreateInfo;
    const void* pNext = nullptr;
    ImageUsageFlags stencilUsage = static_cast<ImageUsageFlags>(0);
};
using ImageStencilUsageCreateInfoEXT = ImageStencilUsageCreateInfo;
struct DeviceMemoryOverallocationCreateInfoAMD {
    StructureType sType = StructureType::eDeviceMemoryOverallocationCreateInfoAMD;
    const void* pNext = nullptr;
    MemoryOverallocationBehaviorAMD overallocationBehavior = static_cast<MemoryOverallocationBehaviorAMD>(0);
};
struct PhysicalDeviceFragmentDensityMapFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceFragmentDensityMapFeaturesEXT;
    void* pNext = nullptr;
    bool fragmentDensityMap = false;
    bool fragmentDensityMapDynamic = false;
    bool fragmentDensityMapNonSubsampledImages = false;
};
struct PhysicalDeviceFragmentDensityMapPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceFragmentDensityMapPropertiesEXT;
    void* pNext = nullptr;
    Extent2D minFragmentDensityTexelSize;
    Extent2D maxFragmentDensityTexelSize;
    bool fragmentDensityInvocations = false;
};
struct RenderPassFragmentDensityMapCreateInfoEXT {
    StructureType sType = StructureType::eRenderPassFragmentDensityMapCreateInfoEXT;
    const void* pNext = nullptr;
    AttachmentReference fragmentDensityMapAttachment;
};
struct PhysicalDeviceScalarBlockLayoutFeatures {
    StructureType sType = StructureType::ePhysicalDeviceScalarBlockLayoutFeatures;
    void* pNext = nullptr;
    bool scalarBlockLayout = false;
};
using PhysicalDeviceScalarBlockLayoutFeaturesEXT = PhysicalDeviceScalarBlockLayoutFeatures;
struct SurfaceProtectedCapabilitiesKHR {
    StructureType sType = StructureType::eSurfaceProtectedCapabilitiesKHR;
    const void* pNext = nullptr;
    bool supportsProtected = false;
};
struct PhysicalDeviceUniformBufferStandardLayoutFeatures {
    StructureType sType = StructureType::ePhysicalDeviceUniformBufferStandardLayoutFeatures;
    void* pNext = nullptr;
    bool uniformBufferStandardLayout = false;
};
using PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR = PhysicalDeviceUniformBufferStandardLayoutFeatures;
struct PhysicalDeviceDepthClipEnableFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceDepthClipEnableFeaturesEXT;
    void* pNext = nullptr;
    bool depthClipEnable = false;
};
struct PipelineRasterizationDepthClipStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineRasterizationDepthClipStateCreateInfoEXT;
    const void* pNext = nullptr;
    PipelineRasterizationDepthClipStateCreateFlagsEXT flags = static_cast<PipelineRasterizationDepthClipStateCreateFlagsEXT>(0);
    bool depthClipEnable = false;
};
struct PhysicalDeviceMemoryBudgetPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceMemoryBudgetPropertiesEXT;
    void* pNext = nullptr;
    DeviceSize heapBudget[MAX_MEMORY_HEAPS] = {};
    DeviceSize heapUsage[MAX_MEMORY_HEAPS] = {};
};
struct PhysicalDeviceMemoryPriorityFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceMemoryPriorityFeaturesEXT;
    void* pNext = nullptr;
    bool memoryPriority = false;
};
struct MemoryPriorityAllocateInfoEXT {
    StructureType sType = StructureType::eMemoryPriorityAllocateInfoEXT;
    const void* pNext = nullptr;
    float priority = 0.f;
};
struct PhysicalDeviceBufferDeviceAddressFeatures {
    StructureType sType = StructureType::ePhysicalDeviceBufferDeviceAddressFeatures;
    void* pNext = nullptr;
    bool bufferDeviceAddress = false;
    bool bufferDeviceAddressCaptureReplay = false;
    bool bufferDeviceAddressMultiDevice = false;
};
using PhysicalDeviceBufferDeviceAddressFeaturesKHR = PhysicalDeviceBufferDeviceAddressFeatures;
struct PhysicalDeviceBufferDeviceAddressFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceBufferDeviceAddressFeaturesEXT;
    void* pNext = nullptr;
    bool bufferDeviceAddress = false;
    bool bufferDeviceAddressCaptureReplay = false;
    bool bufferDeviceAddressMultiDevice = false;
};
using PhysicalDeviceBufferAddressFeaturesEXT = PhysicalDeviceBufferDeviceAddressFeaturesEXT;
struct BufferDeviceAddressInfo {
    StructureType sType = StructureType::eBufferDeviceAddressInfo;
    const void* pNext = nullptr;
    Buffer buffer;
};
using BufferDeviceAddressInfoKHR = BufferDeviceAddressInfo;
using BufferDeviceAddressInfoEXT = BufferDeviceAddressInfo;
struct BufferOpaqueCaptureAddressCreateInfo {
    StructureType sType = StructureType::eBufferOpaqueCaptureAddressCreateInfo;
    const void* pNext = nullptr;
    uint64_t opaqueCaptureAddress = 0;
};
using BufferOpaqueCaptureAddressCreateInfoKHR = BufferOpaqueCaptureAddressCreateInfo;
struct BufferDeviceAddressCreateInfoEXT {
    StructureType sType = StructureType::eBufferDeviceAddressCreateInfoEXT;
    const void* pNext = nullptr;
    DeviceAddress deviceAddress = 0;
};
struct PhysicalDeviceImageViewImageFormatInfoEXT {
    StructureType sType = StructureType::ePhysicalDeviceImageViewImageFormatInfoEXT;
    void* pNext = nullptr;
    ImageViewType imageViewType = static_cast<ImageViewType>(0);
};
struct FilterCubicImageViewImageFormatPropertiesEXT {
    StructureType sType = StructureType::eFilterCubicImageViewImageFormatPropertiesEXT;
    void* pNext = nullptr;
    bool filterCubic = false;
    bool filterCubicMinmax = false;
};
struct PhysicalDeviceImagelessFramebufferFeatures {
    StructureType sType = StructureType::ePhysicalDeviceImagelessFramebufferFeatures;
    void* pNext = nullptr;
    bool imagelessFramebuffer = false;
};
using PhysicalDeviceImagelessFramebufferFeaturesKHR = PhysicalDeviceImagelessFramebufferFeatures;
struct FramebufferAttachmentsCreateInfo {
    StructureType sType = StructureType::eFramebufferAttachmentsCreateInfo;
    const void* pNext = nullptr;
    uint32_t attachmentImageInfoCount = 0;
    const FramebufferAttachmentImageInfo* pAttachmentImageInfos = nullptr;
};
using FramebufferAttachmentsCreateInfoKHR = FramebufferAttachmentsCreateInfo;
struct FramebufferAttachmentImageInfo {
    StructureType sType = StructureType::eFramebufferAttachmentImageInfo;
    const void* pNext = nullptr;
    ImageCreateFlags flags = static_cast<ImageCreateFlags>(0);
    ImageUsageFlags usage = static_cast<ImageUsageFlags>(0);
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t layerCount = 0;
    uint32_t viewFormatCount = 0;
    const Format* pViewFormats = nullptr;
};
using FramebufferAttachmentImageInfoKHR = FramebufferAttachmentImageInfo;
struct RenderPassAttachmentBeginInfo {
    StructureType sType = StructureType::eRenderPassAttachmentBeginInfo;
    const void* pNext = nullptr;
    uint32_t attachmentCount = 0;
    const ImageView* pAttachments = nullptr;
};
using RenderPassAttachmentBeginInfoKHR = RenderPassAttachmentBeginInfo;
struct PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceTextureCompressionAstcHdrFeaturesEXT;
    void* pNext = nullptr;
    bool textureCompressionASTC_HDR = false;
};
struct PhysicalDeviceCooperativeMatrixFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceCooperativeMatrixFeaturesNV;
    void* pNext = nullptr;
    bool cooperativeMatrix = false;
    bool cooperativeMatrixRobustBufferAccess = false;
};
struct PhysicalDeviceCooperativeMatrixPropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceCooperativeMatrixPropertiesNV;
    void* pNext = nullptr;
    ShaderStageFlags cooperativeMatrixSupportedStages = static_cast<ShaderStageFlags>(0);
};
struct CooperativeMatrixPropertiesNV {
    StructureType sType = StructureType::eCooperativeMatrixPropertiesNV;
    void* pNext = nullptr;
    uint32_t MSize = 0;
    uint32_t NSize = 0;
    uint32_t KSize = 0;
    ComponentTypeNV AType = static_cast<ComponentTypeNV>(0);
    ComponentTypeNV BType = static_cast<ComponentTypeNV>(0);
    ComponentTypeNV CType = static_cast<ComponentTypeNV>(0);
    ComponentTypeNV DType = static_cast<ComponentTypeNV>(0);
    ScopeNV scope = static_cast<ScopeNV>(0);
};
struct PhysicalDeviceYcbcrImageArraysFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceYcbcrImageArraysFeaturesEXT;
    void* pNext = nullptr;
    bool ycbcrImageArrays = false;
};
struct ImageViewHandleInfoNVX {
    StructureType sType = StructureType::eImageViewHandleInfoNVX;
    const void* pNext = nullptr;
    ImageView imageView;
    DescriptorType descriptorType = static_cast<DescriptorType>(0);
    Sampler sampler;
};
#if defined(VK_USE_PLATFORM_GGP)
struct PresentFrameTokenGGP {
    StructureType sType = StructureType::ePresentFrameTokenGGP;
    const void* pNext = nullptr;
    GgpFrameToken frameToken;
};
#endif // VK_USE_PLATFORM_GGP
struct PipelineCreationFeedbackEXT {
    PipelineCreationFeedbackFlagsEXT flags = static_cast<PipelineCreationFeedbackFlagsEXT>(0);
    uint64_t duration = 0;
};
struct PipelineCreationFeedbackCreateInfoEXT {
    StructureType sType = StructureType::ePipelineCreationFeedbackCreateInfoEXT;
    const void* pNext = nullptr;
    PipelineCreationFeedbackEXT* pPipelineCreationFeedback = nullptr;
    uint32_t pipelineStageCreationFeedbackCount = 0;
    PipelineCreationFeedbackEXT* pPipelineStageCreationFeedbacks = nullptr;
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct SurfaceFullScreenExclusiveInfoEXT {
    StructureType sType = StructureType::eSurfaceFullScreenExclusiveInfoEXT;
    void* pNext = nullptr;
    FullScreenExclusiveEXT fullScreenExclusive = static_cast<FullScreenExclusiveEXT>(0);
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct SurfaceFullScreenExclusiveWin32InfoEXT {
    StructureType sType = StructureType::eSurfaceFullScreenExclusiveWin32InfoEXT;
    const void* pNext = nullptr;
    HMONITOR hmonitor;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct SurfaceCapabilitiesFullScreenExclusiveEXT {
    StructureType sType = StructureType::eSurfaceCapabilitiesFullScreenExclusiveEXT;
    void* pNext = nullptr;
    bool fullScreenExclusiveSupported = false;
};
#endif // VK_USE_PLATFORM_WIN32_KHR
struct PhysicalDevicePerformanceQueryFeaturesKHR {
    StructureType sType = StructureType::ePhysicalDevicePerformanceQueryFeaturesKHR;
    void* pNext = nullptr;
    bool performanceCounterQueryPools = false;
    bool performanceCounterMultipleQueryPools = false;
};
struct PhysicalDevicePerformanceQueryPropertiesKHR {
    StructureType sType = StructureType::ePhysicalDevicePerformanceQueryPropertiesKHR;
    void* pNext = nullptr;
    bool allowCommandBufferQueryCopies = false;
};
struct PerformanceCounterKHR {
    StructureType sType = StructureType::ePerformanceCounterKHR;
    const void* pNext = nullptr;
    PerformanceCounterUnitKHR unit = static_cast<PerformanceCounterUnitKHR>(0);
    PerformanceCounterScopeKHR scope = static_cast<PerformanceCounterScopeKHR>(0);
    PerformanceCounterStorageKHR storage = static_cast<PerformanceCounterStorageKHR>(0);
    uint8_t uuid[UUID_SIZE] = {};
};
struct PerformanceCounterDescriptionKHR {
    StructureType sType = StructureType::ePerformanceCounterDescriptionKHR;
    const void* pNext = nullptr;
    PerformanceCounterDescriptionFlagsKHR flags = static_cast<PerformanceCounterDescriptionFlagsKHR>(0);
    char name[MAX_DESCRIPTION_SIZE] = {};
    char category[MAX_DESCRIPTION_SIZE] = {};
    char description[MAX_DESCRIPTION_SIZE] = {};
};
struct QueryPoolPerformanceCreateInfoKHR {
    StructureType sType = StructureType::eQueryPoolPerformanceCreateInfoKHR;
    const void* pNext = nullptr;
    uint32_t queueFamilyIndex = 0;
    uint32_t counterIndexCount = 0;
    const uint32_t* pCounterIndices = nullptr;
};
struct AcquireProfilingLockInfoKHR {
    StructureType sType = StructureType::eAcquireProfilingLockInfoKHR;
    const void* pNext = nullptr;
    AcquireProfilingLockFlagsKHR flags = static_cast<AcquireProfilingLockFlagsKHR>(0);
    uint64_t timeout = 0;
};
struct PerformanceQuerySubmitInfoKHR {
    StructureType sType = StructureType::ePerformanceQuerySubmitInfoKHR;
    const void* pNext = nullptr;
    uint32_t counterPassIndex = 0;
};
struct HeadlessSurfaceCreateInfoEXT {
    StructureType sType = StructureType::eHeadlessSurfaceCreateInfoEXT;
    const void* pNext = nullptr;
    HeadlessSurfaceCreateFlagsEXT flags = static_cast<HeadlessSurfaceCreateFlagsEXT>(0);
};
struct PhysicalDeviceCoverageReductionModeFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceCoverageReductionModeFeaturesNV;
    void* pNext = nullptr;
    bool coverageReductionMode = false;
};
struct PipelineCoverageReductionStateCreateInfoNV {
    StructureType sType = StructureType::ePipelineCoverageReductionStateCreateInfoNV;
    const void* pNext = nullptr;
    PipelineCoverageReductionStateCreateFlagsNV flags = static_cast<PipelineCoverageReductionStateCreateFlagsNV>(0);
    CoverageReductionModeNV coverageReductionMode = static_cast<CoverageReductionModeNV>(0);
};
struct FramebufferMixedSamplesCombinationNV {
    StructureType sType = StructureType::eFramebufferMixedSamplesCombinationNV;
    void* pNext = nullptr;
    CoverageReductionModeNV coverageReductionMode = static_cast<CoverageReductionModeNV>(0);
    SampleCountFlagBits rasterizationSamples = static_cast<SampleCountFlagBits>(0);
    SampleCountFlags depthStencilSamples = static_cast<SampleCountFlags>(0);
    SampleCountFlags colorSamples = static_cast<SampleCountFlags>(0);
};
struct PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL {
    StructureType sType = StructureType::ePhysicalDeviceShaderIntegerFunctions2FeaturesINTEL;
    void* pNext = nullptr;
    bool shaderIntegerFunctions2 = false;
};
struct PerformanceValueINTEL {
    PerformanceValueTypeINTEL type = static_cast<PerformanceValueTypeINTEL>(0);
    PerformanceValueDataINTEL data;
};
struct InitializePerformanceApiInfoINTEL {
    StructureType sType = StructureType::eInitializePerformanceApiInfoINTEL;
    const void* pNext = nullptr;
    void* pUserData = nullptr;
};
struct QueryPoolPerformanceQueryCreateInfoINTEL {
    StructureType sType = StructureType::eQueryPoolCreateInfoINTEL;
    const void* pNext = nullptr;
    QueryPoolSamplingModeINTEL performanceCountersSampling = static_cast<QueryPoolSamplingModeINTEL>(0);
};
using QueryPoolCreateInfoINTEL = QueryPoolPerformanceQueryCreateInfoINTEL;
struct PerformanceMarkerInfoINTEL {
    StructureType sType = StructureType::ePerformanceMarkerInfoINTEL;
    const void* pNext = nullptr;
    uint64_t marker = 0;
};
struct PerformanceStreamMarkerInfoINTEL {
    StructureType sType = StructureType::ePerformanceStreamMarkerInfoINTEL;
    const void* pNext = nullptr;
    uint32_t marker = 0;
};
struct PerformanceOverrideInfoINTEL {
    StructureType sType = StructureType::ePerformanceOverrideInfoINTEL;
    const void* pNext = nullptr;
    PerformanceOverrideTypeINTEL type = static_cast<PerformanceOverrideTypeINTEL>(0);
    bool enable = false;
    uint64_t parameter = 0;
};
struct PerformanceConfigurationAcquireInfoINTEL {
    StructureType sType = StructureType::ePerformanceConfigurationAcquireInfoINTEL;
    const void* pNext = nullptr;
    PerformanceConfigurationTypeINTEL type = static_cast<PerformanceConfigurationTypeINTEL>(0);
};
struct PhysicalDeviceShaderClockFeaturesKHR {
    StructureType sType = StructureType::ePhysicalDeviceShaderClockFeaturesKHR;
    void* pNext = nullptr;
    bool shaderSubgroupClock = false;
    bool shaderDeviceClock = false;
};
struct PhysicalDeviceIndexTypeUint8FeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceIndexTypeUint8FeaturesEXT;
    void* pNext = nullptr;
    bool indexTypeUint8 = false;
};
struct PhysicalDeviceShaderSMBuiltinsPropertiesNV {
    StructureType sType = StructureType::ePhysicalDeviceShaderSmBuiltinsPropertiesNV;
    void* pNext = nullptr;
    uint32_t shaderSMCount = 0;
    uint32_t shaderWarpsPerSM = 0;
};
struct PhysicalDeviceShaderSMBuiltinsFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceShaderSmBuiltinsFeaturesNV;
    void* pNext = nullptr;
    bool shaderSMBuiltins = false;
};
struct PhysicalDeviceFragmentShaderInterlockFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceFragmentShaderInterlockFeaturesEXT;
    void* pNext = nullptr;
    bool fragmentShaderSampleInterlock = false;
    bool fragmentShaderPixelInterlock = false;
    bool fragmentShaderShadingRateInterlock = false;
};
struct PhysicalDeviceSeparateDepthStencilLayoutsFeatures {
    StructureType sType = StructureType::ePhysicalDeviceSeparateDepthStencilLayoutsFeatures;
    void* pNext = nullptr;
    bool separateDepthStencilLayouts = false;
};
using PhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR = PhysicalDeviceSeparateDepthStencilLayoutsFeatures;
struct AttachmentReferenceStencilLayout {
    StructureType sType = StructureType::eAttachmentReferenceStencilLayout;
    void* pNext = nullptr;
    ImageLayout stencilLayout = static_cast<ImageLayout>(0);
};
using AttachmentReferenceStencilLayoutKHR = AttachmentReferenceStencilLayout;
struct AttachmentDescriptionStencilLayout {
    StructureType sType = StructureType::eAttachmentDescriptionStencilLayout;
    void* pNext = nullptr;
    ImageLayout stencilInitialLayout = static_cast<ImageLayout>(0);
    ImageLayout stencilFinalLayout = static_cast<ImageLayout>(0);
};
using AttachmentDescriptionStencilLayoutKHR = AttachmentDescriptionStencilLayout;
struct PhysicalDevicePipelineExecutablePropertiesFeaturesKHR {
    StructureType sType = StructureType::ePhysicalDevicePipelineExecutablePropertiesFeaturesKHR;
    void* pNext = nullptr;
    bool pipelineExecutableInfo = false;
};
struct PipelineInfoKHR {
    StructureType sType = StructureType::ePipelineInfoKHR;
    const void* pNext = nullptr;
    Pipeline pipeline;
};
struct PipelineExecutablePropertiesKHR {
    StructureType sType = StructureType::ePipelineExecutablePropertiesKHR;
    void* pNext = nullptr;
    ShaderStageFlags stages = static_cast<ShaderStageFlags>(0);
    char name[MAX_DESCRIPTION_SIZE] = {};
    char description[MAX_DESCRIPTION_SIZE] = {};
    uint32_t subgroupSize = 0;
};
struct PipelineExecutableInfoKHR {
    StructureType sType = StructureType::ePipelineExecutableInfoKHR;
    const void* pNext = nullptr;
    Pipeline pipeline;
    uint32_t executableIndex = 0;
};
struct PipelineExecutableStatisticKHR {
    StructureType sType = StructureType::ePipelineExecutableStatisticKHR;
    void* pNext = nullptr;
    char name[MAX_DESCRIPTION_SIZE] = {};
    char description[MAX_DESCRIPTION_SIZE] = {};
    PipelineExecutableStatisticFormatKHR format = static_cast<PipelineExecutableStatisticFormatKHR>(0);
    PipelineExecutableStatisticValueKHR value;
};
struct PipelineExecutableInternalRepresentationKHR {
    StructureType sType = StructureType::ePipelineExecutableInternalRepresentationKHR;
    void* pNext = nullptr;
    char name[MAX_DESCRIPTION_SIZE] = {};
    char description[MAX_DESCRIPTION_SIZE] = {};
    bool isText = false;
    size_t dataSize = 0;
    void* pData = nullptr;
};
struct PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
    void* pNext = nullptr;
    bool shaderDemoteToHelperInvocation = false;
};
struct PhysicalDeviceTexelBufferAlignmentFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceTexelBufferAlignmentFeaturesEXT;
    void* pNext = nullptr;
    bool texelBufferAlignment = false;
};
struct PhysicalDeviceTexelBufferAlignmentPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceTexelBufferAlignmentPropertiesEXT;
    void* pNext = nullptr;
    DeviceSize storageTexelBufferOffsetAlignmentBytes = 0;
    bool storageTexelBufferOffsetSingleTexelAlignment = false;
    DeviceSize uniformTexelBufferOffsetAlignmentBytes = 0;
    bool uniformTexelBufferOffsetSingleTexelAlignment = false;
};
struct PhysicalDeviceSubgroupSizeControlFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceSubgroupSizeControlFeaturesEXT;
    void* pNext = nullptr;
    bool subgroupSizeControl = false;
    bool computeFullSubgroups = false;
};
struct PhysicalDeviceSubgroupSizeControlPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceSubgroupSizeControlPropertiesEXT;
    void* pNext = nullptr;
    uint32_t minSubgroupSize = 0;
    uint32_t maxSubgroupSize = 0;
    uint32_t maxComputeWorkgroupSubgroups = 0;
    ShaderStageFlags requiredSubgroupSizeStages = static_cast<ShaderStageFlags>(0);
};
struct PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT {
    StructureType sType = StructureType::ePipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
    void* pNext = nullptr;
    uint32_t requiredSubgroupSize = 0;
};
struct MemoryOpaqueCaptureAddressAllocateInfo {
    StructureType sType = StructureType::eMemoryOpaqueCaptureAddressAllocateInfo;
    const void* pNext = nullptr;
    uint64_t opaqueCaptureAddress = 0;
};
using MemoryOpaqueCaptureAddressAllocateInfoKHR = MemoryOpaqueCaptureAddressAllocateInfo;
struct DeviceMemoryOpaqueCaptureAddressInfo {
    StructureType sType = StructureType::eDeviceMemoryOpaqueCaptureAddressInfo;
    const void* pNext = nullptr;
    DeviceMemory memory;
};
using DeviceMemoryOpaqueCaptureAddressInfoKHR = DeviceMemoryOpaqueCaptureAddressInfo;
struct PhysicalDeviceLineRasterizationFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDeviceLineRasterizationFeaturesEXT;
    void* pNext = nullptr;
    bool rectangularLines = false;
    bool bresenhamLines = false;
    bool smoothLines = false;
    bool stippledRectangularLines = false;
    bool stippledBresenhamLines = false;
    bool stippledSmoothLines = false;
};
struct PhysicalDeviceLineRasterizationPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceLineRasterizationPropertiesEXT;
    void* pNext = nullptr;
    uint32_t lineSubPixelPrecisionBits = 0;
};
struct PipelineRasterizationLineStateCreateInfoEXT {
    StructureType sType = StructureType::ePipelineRasterizationLineStateCreateInfoEXT;
    const void* pNext = nullptr;
    LineRasterizationModeEXT lineRasterizationMode = static_cast<LineRasterizationModeEXT>(0);
    bool stippledLineEnable = false;
    uint32_t lineStippleFactor = 0;
    uint16_t lineStipplePattern = 0;
};
struct PhysicalDevicePipelineCreationCacheControlFeaturesEXT {
    StructureType sType = StructureType::ePhysicalDevicePipelineCreationCacheControlFeaturesEXT;
    void* pNext = nullptr;
    bool pipelineCreationCacheControl = false;
};
struct PhysicalDeviceVulkan11Features {
    StructureType sType = StructureType::ePhysicalDeviceVulkan11Features;
    void* pNext = nullptr;
    bool storageBuffer16BitAccess = false;
    bool uniformAndStorageBuffer16BitAccess = false;
    bool storagePushConstant16 = false;
    bool storageInputOutput16 = false;
    bool multiview = false;
    bool multiviewGeometryShader = false;
    bool multiviewTessellationShader = false;
    bool variablePointersStorageBuffer = false;
    bool variablePointers = false;
    bool protectedMemory = false;
    bool samplerYcbcrConversion = false;
    bool shaderDrawParameters = false;
};
struct PhysicalDeviceVulkan11Properties {
    StructureType sType = StructureType::ePhysicalDeviceVulkan11Properties;
    void* pNext = nullptr;
    uint8_t deviceUUID[UUID_SIZE] = {};
    uint8_t driverUUID[UUID_SIZE] = {};
    uint8_t deviceLUID[LUID_SIZE] = {};
    uint32_t deviceNodeMask = 0;
    bool deviceLUIDValid = false;
    uint32_t subgroupSize = 0;
    ShaderStageFlags subgroupSupportedStages = static_cast<ShaderStageFlags>(0);
    SubgroupFeatureFlags subgroupSupportedOperations = static_cast<SubgroupFeatureFlags>(0);
    bool subgroupQuadOperationsInAllStages = false;
    PointClippingBehavior pointClippingBehavior = static_cast<PointClippingBehavior>(0);
    uint32_t maxMultiviewViewCount = 0;
    uint32_t maxMultiviewInstanceIndex = 0;
    bool protectedNoFault = false;
    uint32_t maxPerSetDescriptors = 0;
    DeviceSize maxMemoryAllocationSize = 0;
};
struct PhysicalDeviceVulkan12Features {
    StructureType sType = StructureType::ePhysicalDeviceVulkan12Features;
    void* pNext = nullptr;
    bool samplerMirrorClampToEdge = false;
    bool drawIndirectCount = false;
    bool storageBuffer8BitAccess = false;
    bool uniformAndStorageBuffer8BitAccess = false;
    bool storagePushConstant8 = false;
    bool shaderBufferInt64Atomics = false;
    bool shaderSharedInt64Atomics = false;
    bool shaderFloat16 = false;
    bool shaderInt8 = false;
    bool descriptorIndexing = false;
    bool shaderInputAttachmentArrayDynamicIndexing = false;
    bool shaderUniformTexelBufferArrayDynamicIndexing = false;
    bool shaderStorageTexelBufferArrayDynamicIndexing = false;
    bool shaderUniformBufferArrayNonUniformIndexing = false;
    bool shaderSampledImageArrayNonUniformIndexing = false;
    bool shaderStorageBufferArrayNonUniformIndexing = false;
    bool shaderStorageImageArrayNonUniformIndexing = false;
    bool shaderInputAttachmentArrayNonUniformIndexing = false;
    bool shaderUniformTexelBufferArrayNonUniformIndexing = false;
    bool shaderStorageTexelBufferArrayNonUniformIndexing = false;
    bool descriptorBindingUniformBufferUpdateAfterBind = false;
    bool descriptorBindingSampledImageUpdateAfterBind = false;
    bool descriptorBindingStorageImageUpdateAfterBind = false;
    bool descriptorBindingStorageBufferUpdateAfterBind = false;
    bool descriptorBindingUniformTexelBufferUpdateAfterBind = false;
    bool descriptorBindingStorageTexelBufferUpdateAfterBind = false;
    bool descriptorBindingUpdateUnusedWhilePending = false;
    bool descriptorBindingPartiallyBound = false;
    bool descriptorBindingVariableDescriptorCount = false;
    bool runtimeDescriptorArray = false;
    bool samplerFilterMinmax = false;
    bool scalarBlockLayout = false;
    bool imagelessFramebuffer = false;
    bool uniformBufferStandardLayout = false;
    bool shaderSubgroupExtendedTypes = false;
    bool separateDepthStencilLayouts = false;
    bool hostQueryReset = false;
    bool timelineSemaphore = false;
    bool bufferDeviceAddress = false;
    bool bufferDeviceAddressCaptureReplay = false;
    bool bufferDeviceAddressMultiDevice = false;
    bool vulkanMemoryModel = false;
    bool vulkanMemoryModelDeviceScope = false;
    bool vulkanMemoryModelAvailabilityVisibilityChains = false;
    bool shaderOutputViewportIndex = false;
    bool shaderOutputLayer = false;
    bool subgroupBroadcastDynamicId = false;
};
struct PhysicalDeviceVulkan12Properties {
    StructureType sType = StructureType::ePhysicalDeviceVulkan12Properties;
    void* pNext = nullptr;
    DriverId driverID = static_cast<DriverId>(0);
    char driverName[MAX_DRIVER_NAME_SIZE] = {};
    char driverInfo[MAX_DRIVER_INFO_SIZE] = {};
    ConformanceVersion conformanceVersion;
    ShaderFloatControlsIndependence denormBehaviorIndependence = static_cast<ShaderFloatControlsIndependence>(0);
    ShaderFloatControlsIndependence roundingModeIndependence = static_cast<ShaderFloatControlsIndependence>(0);
    bool shaderSignedZeroInfNanPreserveFloat16 = false;
    bool shaderSignedZeroInfNanPreserveFloat32 = false;
    bool shaderSignedZeroInfNanPreserveFloat64 = false;
    bool shaderDenormPreserveFloat16 = false;
    bool shaderDenormPreserveFloat32 = false;
    bool shaderDenormPreserveFloat64 = false;
    bool shaderDenormFlushToZeroFloat16 = false;
    bool shaderDenormFlushToZeroFloat32 = false;
    bool shaderDenormFlushToZeroFloat64 = false;
    bool shaderRoundingModeRTEFloat16 = false;
    bool shaderRoundingModeRTEFloat32 = false;
    bool shaderRoundingModeRTEFloat64 = false;
    bool shaderRoundingModeRTZFloat16 = false;
    bool shaderRoundingModeRTZFloat32 = false;
    bool shaderRoundingModeRTZFloat64 = false;
    uint32_t maxUpdateAfterBindDescriptorsInAllPools = 0;
    bool shaderUniformBufferArrayNonUniformIndexingNative = false;
    bool shaderSampledImageArrayNonUniformIndexingNative = false;
    bool shaderStorageBufferArrayNonUniformIndexingNative = false;
    bool shaderStorageImageArrayNonUniformIndexingNative = false;
    bool shaderInputAttachmentArrayNonUniformIndexingNative = false;
    bool robustBufferAccessUpdateAfterBind = false;
    bool quadDivergentImplicitLod = false;
    uint32_t maxPerStageDescriptorUpdateAfterBindSamplers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindUniformBuffers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageBuffers = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindSampledImages = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindStorageImages = 0;
    uint32_t maxPerStageDescriptorUpdateAfterBindInputAttachments = 0;
    uint32_t maxPerStageUpdateAfterBindResources = 0;
    uint32_t maxDescriptorSetUpdateAfterBindSamplers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindUniformBuffersDynamic = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffers = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageBuffersDynamic = 0;
    uint32_t maxDescriptorSetUpdateAfterBindSampledImages = 0;
    uint32_t maxDescriptorSetUpdateAfterBindStorageImages = 0;
    uint32_t maxDescriptorSetUpdateAfterBindInputAttachments = 0;
    ResolveModeFlags supportedDepthResolveModes = static_cast<ResolveModeFlags>(0);
    ResolveModeFlags supportedStencilResolveModes = static_cast<ResolveModeFlags>(0);
    bool independentResolveNone = false;
    bool independentResolve = false;
    bool filterMinmaxSingleComponentFormats = false;
    bool filterMinmaxImageComponentMapping = false;
    uint64_t maxTimelineSemaphoreValueDifference = 0;
    SampleCountFlags framebufferIntegerColorSampleCounts = static_cast<SampleCountFlags>(0);
};
struct PipelineCompilerControlCreateInfoAMD {
    StructureType sType = StructureType::ePipelineCompilerControlCreateInfoAMD;
    const void* pNext = nullptr;
    PipelineCompilerControlFlagsAMD compilerControlFlags = static_cast<PipelineCompilerControlFlagsAMD>(0);
};
struct PhysicalDeviceCoherentMemoryFeaturesAMD {
    StructureType sType = StructureType::ePhysicalDeviceCoherentMemoryFeaturesAMD;
    void* pNext = nullptr;
    bool deviceCoherentMemory = false;
};
struct PhysicalDeviceToolPropertiesEXT {
    StructureType sType = StructureType::ePhysicalDeviceToolPropertiesEXT;
    void* pNext = nullptr;
    char name[MAX_EXTENSION_NAME_SIZE] = {};
    char version[MAX_EXTENSION_NAME_SIZE] = {};
    ToolPurposeFlagsEXT purposes = static_cast<ToolPurposeFlagsEXT>(0);
    char description[MAX_DESCRIPTION_SIZE] = {};
    char layer[MAX_EXTENSION_NAME_SIZE] = {};
};
struct AccelerationStructureGeometryTrianglesDataKHR {
    StructureType sType = StructureType::eAccelerationStructureGeometryTrianglesDataKHR;
    const void* pNext = nullptr;
    Format vertexFormat = static_cast<Format>(0);
    DeviceOrHostAddressConstKHR vertexData;
    DeviceSize vertexStride = 0;
    IndexType indexType = static_cast<IndexType>(0);
    DeviceOrHostAddressConstKHR indexData;
    DeviceOrHostAddressConstKHR transformData;
};
struct AccelerationStructureGeometryAabbsDataKHR {
    StructureType sType = StructureType::eAccelerationStructureGeometryAabbsDataKHR;
    const void* pNext = nullptr;
    DeviceOrHostAddressConstKHR data;
    DeviceSize stride = 0;
};
struct AccelerationStructureGeometryInstancesDataKHR {
    StructureType sType = StructureType::eAccelerationStructureGeometryInstancesDataKHR;
    const void* pNext = nullptr;
    bool arrayOfPointers = false;
    DeviceOrHostAddressConstKHR data;
};
struct AccelerationStructureGeometryKHR {
    StructureType sType = StructureType::eAccelerationStructureGeometryKHR;
    const void* pNext = nullptr;
    GeometryTypeKHR geometryType = static_cast<GeometryTypeKHR>(0);
    AccelerationStructureGeometryDataKHR geometry;
    GeometryFlagsKHR flags = static_cast<GeometryFlagsKHR>(0);
};
struct AccelerationStructureBuildGeometryInfoKHR {
    StructureType sType = StructureType::eAccelerationStructureBuildGeometryInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureTypeKHR type = static_cast<AccelerationStructureTypeKHR>(0);
    BuildAccelerationStructureFlagsKHR flags = static_cast<BuildAccelerationStructureFlagsKHR>(0);
    bool update = false;
    AccelerationStructureKHR srcAccelerationStructure;
    AccelerationStructureKHR dstAccelerationStructure;
    bool geometryArrayOfPointers = false;
    uint32_t geometryCount = 0;
    const AccelerationStructureGeometryKHR* const* ppGeometries = nullptr;
    DeviceOrHostAddressKHR scratchData;
};
struct AccelerationStructureBuildOffsetInfoKHR {
    uint32_t primitiveCount = 0;
    uint32_t primitiveOffset = 0;
    uint32_t firstVertex = 0;
    uint32_t transformOffset = 0;
};
struct AccelerationStructureCreateGeometryTypeInfoKHR {
    StructureType sType = StructureType::eAccelerationStructureCreateGeometryTypeInfoKHR;
    const void* pNext = nullptr;
    GeometryTypeKHR geometryType = static_cast<GeometryTypeKHR>(0);
    uint32_t maxPrimitiveCount = 0;
    IndexType indexType = static_cast<IndexType>(0);
    uint32_t maxVertexCount = 0;
    Format vertexFormat = static_cast<Format>(0);
    bool allowsTransforms = false;
};
struct AccelerationStructureCreateInfoKHR {
    StructureType sType = StructureType::eAccelerationStructureCreateInfoKHR;
    const void* pNext = nullptr;
    DeviceSize compactedSize = 0;
    AccelerationStructureTypeKHR type = static_cast<AccelerationStructureTypeKHR>(0);
    BuildAccelerationStructureFlagsKHR flags = static_cast<BuildAccelerationStructureFlagsKHR>(0);
    uint32_t maxGeometryCount = 0;
    const AccelerationStructureCreateGeometryTypeInfoKHR* pGeometryInfos = nullptr;
    DeviceAddress deviceAddress = 0;
};
struct AabbPositionsKHR {
    float minX = 0.f;
    float minY = 0.f;
    float minZ = 0.f;
    float maxX = 0.f;
    float maxY = 0.f;
    float maxZ = 0.f;
};
using AabbPositionsNV = AabbPositionsKHR;
struct TransformMatrixKHR {
    float matrix[3][4] = {};
};
using TransformMatrixNV = TransformMatrixKHR;
struct AccelerationStructureInstanceKHR {
    TransformMatrixKHR transform;
    uint32_t instanceCustomIndex = 0;
    uint32_t mask = 0;
    uint32_t instanceShaderBindingTableRecordOffset = 0;
    GeometryInstanceFlagsKHR flags = static_cast<GeometryInstanceFlagsKHR>(0);
    uint64_t accelerationStructureReference = 0;
};
using AccelerationStructureInstanceNV = AccelerationStructureInstanceKHR;
struct AccelerationStructureDeviceAddressInfoKHR {
    StructureType sType = StructureType::eAccelerationStructureDeviceAddressInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureKHR accelerationStructure;
};
struct AccelerationStructureVersionKHR {
    StructureType sType = StructureType::eAccelerationStructureVersionKHR;
    const void* pNext = nullptr;
    const uint8_t* versionData = nullptr;
};
struct CopyAccelerationStructureInfoKHR {
    StructureType sType = StructureType::eCopyAccelerationStructureInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureKHR src;
    AccelerationStructureKHR dst;
    CopyAccelerationStructureModeKHR mode = static_cast<CopyAccelerationStructureModeKHR>(0);
};
struct CopyAccelerationStructureToMemoryInfoKHR {
    StructureType sType = StructureType::eCopyAccelerationStructureToMemoryInfoKHR;
    const void* pNext = nullptr;
    AccelerationStructureKHR src;
    DeviceOrHostAddressKHR dst;
    CopyAccelerationStructureModeKHR mode = static_cast<CopyAccelerationStructureModeKHR>(0);
};
struct CopyMemoryToAccelerationStructureInfoKHR {
    StructureType sType = StructureType::eCopyMemoryToAccelerationStructureInfoKHR;
    const void* pNext = nullptr;
    DeviceOrHostAddressConstKHR src;
    AccelerationStructureKHR dst;
    CopyAccelerationStructureModeKHR mode = static_cast<CopyAccelerationStructureModeKHR>(0);
};
struct RayTracingPipelineInterfaceCreateInfoKHR {
    StructureType sType = StructureType::eRayTracingPipelineInterfaceCreateInfoKHR;
    const void* pNext = nullptr;
    uint32_t maxPayloadSize = 0;
    uint32_t maxAttributeSize = 0;
    uint32_t maxCallableSize = 0;
};
struct DeferredOperationInfoKHR {
    StructureType sType = StructureType::eDeferredOperationInfoKHR;
    const void* pNext = nullptr;
    DeferredOperationKHR operationHandle;
};
struct PipelineLibraryCreateInfoKHR {
    StructureType sType = StructureType::ePipelineLibraryCreateInfoKHR;
    const void* pNext = nullptr;
    uint32_t libraryCount = 0;
    const Pipeline* pLibraries = nullptr;
};
struct RenderPassTransformBeginInfoQCOM {
    StructureType sType = StructureType::eRenderPassTransformBeginInfoQCOM;
    void* pNext = nullptr;
    SurfaceTransformFlagBitsKHR transform = static_cast<SurfaceTransformFlagBitsKHR>(0);
};
struct CommandBufferInheritanceRenderPassTransformInfoQCOM {
    StructureType sType = StructureType::eCommandBufferInheritanceRenderPassTransformInfoQCOM;
    void* pNext = nullptr;
    SurfaceTransformFlagBitsKHR transform = static_cast<SurfaceTransformFlagBitsKHR>(0);
    Rect2D renderArea;
};
struct PhysicalDeviceDiagnosticsConfigFeaturesNV {
    StructureType sType = StructureType::ePhysicalDeviceDiagnosticsConfigFeaturesNV;
    void* pNext = nullptr;
    bool diagnosticsConfig = false;
};
struct DeviceDiagnosticsConfigCreateInfoNV {
    StructureType sType = StructureType::eDeviceDiagnosticsConfigCreateInfoNV;
    const void* pNext = nullptr;
    DeviceDiagnosticsConfigFlagsNV flags = static_cast<DeviceDiagnosticsConfigFlagsNV>(0);
};
VkResult CreateInstance(
    const InstanceCreateInfo* pCreateInfo,
    const AllocationCallbacks* pAllocator,
    Instance* pInstance) {
    return vkCreateInstance( reinterpret_cast<const InstanceCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Instance*>(pInstance));
}
VkResult EnumerateInstanceVersion(
    uint32_t* pApiVersion) {
    return vkEnumerateInstanceVersion( reinterpret_cast<uint32_t*>(pApiVersion));
}
VkResult EnumerateInstanceLayerProperties(
    uint32_t* pPropertyCount,
    LayerProperties* pProperties) {
    return vkEnumerateInstanceLayerProperties( reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<LayerProperties*>(pProperties));
}
VkResult EnumerateInstanceExtensionProperties(
    const char* pLayerName,
    uint32_t* pPropertyCount,
    ExtensionProperties* pProperties) {
    return vkEnumerateInstanceExtensionProperties( reinterpret_cast<const char*>(pLayerName), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<ExtensionProperties*>(pProperties));
}
const auto ResetQueryPoolEXT = ResetQueryPool;
const auto GetPhysicalDeviceFeatures2KHR = GetPhysicalDeviceFeatures2;
const auto GetPhysicalDeviceProperties2KHR = GetPhysicalDeviceProperties2;
const auto GetPhysicalDeviceFormatProperties2KHR = GetPhysicalDeviceFormatProperties2;
const auto GetPhysicalDeviceImageFormatProperties2KHR = GetPhysicalDeviceImageFormatProperties2;
const auto GetPhysicalDeviceQueueFamilyProperties2KHR = GetPhysicalDeviceQueueFamilyProperties2;
const auto GetPhysicalDeviceMemoryProperties2KHR = GetPhysicalDeviceMemoryProperties2;
const auto GetPhysicalDeviceSparseImageFormatProperties2KHR = GetPhysicalDeviceSparseImageFormatProperties2;
const auto TrimCommandPoolKHR = TrimCommandPool;
const auto GetPhysicalDeviceExternalBufferPropertiesKHR = GetPhysicalDeviceExternalBufferProperties;
const auto GetPhysicalDeviceExternalSemaphorePropertiesKHR = GetPhysicalDeviceExternalSemaphoreProperties;
const auto GetPhysicalDeviceExternalFencePropertiesKHR = GetPhysicalDeviceExternalFenceProperties;
const auto EnumeratePhysicalDeviceGroupsKHR = EnumeratePhysicalDeviceGroups;
const auto GetDeviceGroupPeerMemoryFeaturesKHR = GetDeviceGroupPeerMemoryFeatures;
const auto BindBufferMemory2KHR = BindBufferMemory2;
const auto BindImageMemory2KHR = BindImageMemory2;
const auto CmdSetDeviceMaskKHR = CmdSetDeviceMask;
const auto CmdDispatchBaseKHR = CmdDispatchBase;
const auto CreateDescriptorUpdateTemplateKHR = CreateDescriptorUpdateTemplate;
const auto DestroyDescriptorUpdateTemplateKHR = DestroyDescriptorUpdateTemplate;
const auto UpdateDescriptorSetWithTemplateKHR = UpdateDescriptorSetWithTemplate;
const auto GetBufferMemoryRequirements2KHR = GetBufferMemoryRequirements2;
const auto GetImageMemoryRequirements2KHR = GetImageMemoryRequirements2;
const auto GetImageSparseMemoryRequirements2KHR = GetImageSparseMemoryRequirements2;
const auto CreateSamplerYcbcrConversionKHR = CreateSamplerYcbcrConversion;
const auto DestroySamplerYcbcrConversionKHR = DestroySamplerYcbcrConversion;
const auto GetDescriptorSetLayoutSupportKHR = GetDescriptorSetLayoutSupport;
const auto CreateRenderPass2KHR = CreateRenderPass2;
const auto CmdBeginRenderPass2KHR = CmdBeginRenderPass2;
const auto CmdNextSubpass2KHR = CmdNextSubpass2;
const auto CmdEndRenderPass2KHR = CmdEndRenderPass2;
const auto GetSemaphoreCounterValueKHR = GetSemaphoreCounterValue;
const auto WaitSemaphoresKHR = WaitSemaphores;
const auto SignalSemaphoreKHR = SignalSemaphore;
const auto CmdDrawIndirectCountKHR = CmdDrawIndirectCount;
const auto CmdDrawIndirectCountAMD = CmdDrawIndirectCount;
const auto CmdDrawIndexedIndirectCountKHR = CmdDrawIndexedIndirectCount;
const auto CmdDrawIndexedIndirectCountAMD = CmdDrawIndexedIndirectCount;
const auto DestroyAccelerationStructureNV = DestroyAccelerationStructureKHR;
const auto BindAccelerationStructureMemoryNV = BindAccelerationStructureMemoryKHR;
const auto CmdWriteAccelerationStructuresPropertiesNV = CmdWriteAccelerationStructuresPropertiesKHR;
const auto GetRayTracingShaderGroupHandlesNV = GetRayTracingShaderGroupHandlesKHR;
const auto GetBufferOpaqueCaptureAddressKHR = GetBufferOpaqueCaptureAddress;
const auto GetBufferDeviceAddressKHR = GetBufferDeviceAddress;
const auto GetBufferDeviceAddressEXT = GetBufferDeviceAddress;
const auto GetDeviceMemoryOpaqueCaptureAddressKHR = GetDeviceMemoryOpaqueCaptureAddress;
struct Instance {
    VkInstance handle;
    VkInstance get() { return handle; }
    void DestroyInstance(
        const AllocationCallbacks* pAllocator) {
        return vkDestroyInstance(get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult EnumeratePhysicalDevices(
        uint32_t* pPhysicalDeviceCount,    
        PhysicalDevice* pPhysicalDevices) {
        return vkEnumeratePhysicalDevices(get(), reinterpret_cast<uint32_t*>(pPhysicalDeviceCount), reinterpret_cast<PhysicalDevice*>(pPhysicalDevices));
    }
    PFN_vkVoidFunction GetInstanceProcAddr(
        const char* pName) {
        return vkGetInstanceProcAddr(get(), reinterpret_cast<const char*>(pName));
    }
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult CreateAndroidSurfaceKHR(
        const AndroidSurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateAndroidSurfaceKHR(get(), reinterpret_cast<const AndroidSurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
    VkResult CreateDisplayPlaneSurfaceKHR(
        const DisplaySurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateDisplayPlaneSurfaceKHR(get(), reinterpret_cast<const DisplaySurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
    void DestroySurfaceKHR(
        SurfaceKHR surface,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroySurfaceKHR(get(),surface.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
#if defined(VK_USE_PLATFORM_VI_NN)
    VkResult CreateViSurfaceNN(
        const ViSurfaceCreateInfoNN* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateViSurfaceNN(get(), reinterpret_cast<const ViSurfaceCreateInfoNN*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_VI_NN
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkResult CreateWaylandSurfaceKHR(
        const WaylandSurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateWaylandSurfaceKHR(get(), reinterpret_cast<const WaylandSurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult CreateWin32SurfaceKHR(
        const Win32SurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateWin32SurfaceKHR(get(), reinterpret_cast<const Win32SurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    VkResult CreateXlibSurfaceKHR(
        const XlibSurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateXlibSurfaceKHR(get(), reinterpret_cast<const XlibSurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    VkResult CreateXcbSurfaceKHR(
        const XcbSurfaceCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateXcbSurfaceKHR(get(), reinterpret_cast<const XcbSurfaceCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_FUCHSIA)
    VkResult CreateImagePipeSurfaceFUCHSIA(
        const ImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateImagePipeSurfaceFUCHSIA(get(), reinterpret_cast<const ImagePipeSurfaceCreateInfoFUCHSIA*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_FUCHSIA
#if defined(VK_USE_PLATFORM_GGP)
    VkResult CreateStreamDescriptorSurfaceGGP(
        const StreamDescriptorSurfaceCreateInfoGGP* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateStreamDescriptorSurfaceGGP(get(), reinterpret_cast<const StreamDescriptorSurfaceCreateInfoGGP*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_GGP
    VkResult CreateDebugReportCallbackEXT(
        const DebugReportCallbackCreateInfoEXT* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DebugReportCallbackEXT* pCallback) {
        return vkCreateDebugReportCallbackEXT(get(), reinterpret_cast<const DebugReportCallbackCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DebugReportCallbackEXT*>(pCallback));
    }
    void DestroyDebugReportCallbackEXT(
        DebugReportCallbackEXT callback,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDebugReportCallbackEXT(get(),callback.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void DebugReportMessageEXT(
        DebugReportFlagsEXT flags,    
        DebugReportObjectTypeEXT objectType,    
        uint64_t object,    
        size_t location,    
        int32_t messageCode,    
        const char* pLayerPrefix,    
        const char* pMessage) {
        return vkDebugReportMessageEXT(get(), static_cast<DebugReportFlagsEXT>(flags), static_cast<DebugReportObjectTypeEXT>(objectType), static_cast<uint64_t>(object), static_cast<size_t>(location), static_cast<int32_t>(messageCode), reinterpret_cast<const char*>(pLayerPrefix), reinterpret_cast<const char*>(pMessage));
    }
    VkResult EnumeratePhysicalDeviceGroups(
        uint32_t* pPhysicalDeviceGroupCount,    
        PhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) {
        return vkEnumeratePhysicalDeviceGroups(get(), reinterpret_cast<uint32_t*>(pPhysicalDeviceGroupCount), reinterpret_cast<PhysicalDeviceGroupProperties*>(pPhysicalDeviceGroupProperties));
    }
#if defined(VK_USE_PLATFORM_IOS_MVK)
    VkResult CreateIOSSurfaceMVK(
        const IOSSurfaceCreateInfoMVK* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateIOSSurfaceMVK(get(), reinterpret_cast<const IOSSurfaceCreateInfoMVK*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    VkResult CreateMacOSSurfaceMVK(
        const MacOSSurfaceCreateInfoMVK* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateMacOSSurfaceMVK(get(), reinterpret_cast<const MacOSSurfaceCreateInfoMVK*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_MACOS_MVK
#if defined(VK_USE_PLATFORM_METAL_EXT)
    VkResult CreateMetalSurfaceEXT(
        const MetalSurfaceCreateInfoEXT* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateMetalSurfaceEXT(get(), reinterpret_cast<const MetalSurfaceCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
#endif // VK_USE_PLATFORM_METAL_EXT
    VkResult CreateDebugUtilsMessengerEXT(
        const DebugUtilsMessengerCreateInfoEXT* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DebugUtilsMessengerEXT* pMessenger) {
        return vkCreateDebugUtilsMessengerEXT(get(), reinterpret_cast<const DebugUtilsMessengerCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DebugUtilsMessengerEXT*>(pMessenger));
    }
    void DestroyDebugUtilsMessengerEXT(
        DebugUtilsMessengerEXT messenger,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDebugUtilsMessengerEXT(get(),messenger.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void SubmitDebugUtilsMessageEXT(
        DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,    
        DebugUtilsMessageTypeFlagsEXT messageTypes,    
        const DebugUtilsMessengerCallbackDataEXT* pCallbackData) {
        return vkSubmitDebugUtilsMessageEXT(get(), static_cast<DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity), static_cast<DebugUtilsMessageTypeFlagsEXT>(messageTypes), reinterpret_cast<const DebugUtilsMessengerCallbackDataEXT*>(pCallbackData));
    }
    VkResult CreateHeadlessSurfaceEXT(
        const HeadlessSurfaceCreateInfoEXT* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SurfaceKHR* pSurface) {
        return vkCreateHeadlessSurfaceEXT(get(), reinterpret_cast<const HeadlessSurfaceCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SurfaceKHR*>(pSurface));
    }
};
struct PhysicalDevice {
    VkPhysicalDevice handle;
    VkPhysicalDevice get() { return handle; }
    void GetPhysicalDeviceProperties(
        PhysicalDeviceProperties* pProperties) {
        return vkGetPhysicalDeviceProperties(get(), reinterpret_cast<PhysicalDeviceProperties*>(pProperties));
    }
    void GetPhysicalDeviceQueueFamilyProperties(
        uint32_t* pQueueFamilyPropertyCount,    
        QueueFamilyProperties* pQueueFamilyProperties) {
        return vkGetPhysicalDeviceQueueFamilyProperties(get(), reinterpret_cast<uint32_t*>(pQueueFamilyPropertyCount), reinterpret_cast<QueueFamilyProperties*>(pQueueFamilyProperties));
    }
    void GetPhysicalDeviceMemoryProperties(
        PhysicalDeviceMemoryProperties* pMemoryProperties) {
        return vkGetPhysicalDeviceMemoryProperties(get(), reinterpret_cast<PhysicalDeviceMemoryProperties*>(pMemoryProperties));
    }
    void GetPhysicalDeviceFeatures(
        PhysicalDeviceFeatures* pFeatures) {
        return vkGetPhysicalDeviceFeatures(get(), reinterpret_cast<PhysicalDeviceFeatures*>(pFeatures));
    }
    void GetPhysicalDeviceFormatProperties(
        Format format,    
        FormatProperties* pFormatProperties) {
        return vkGetPhysicalDeviceFormatProperties(get(), static_cast<Format>(format), reinterpret_cast<FormatProperties*>(pFormatProperties));
    }
    VkResult GetPhysicalDeviceImageFormatProperties(
        Format format,    
        ImageType type,    
        ImageTiling tiling,    
        ImageUsageFlags usage,    
        ImageCreateFlags flags,    
        ImageFormatProperties* pImageFormatProperties) {
        return vkGetPhysicalDeviceImageFormatProperties(get(), static_cast<Format>(format), static_cast<ImageType>(type), static_cast<ImageTiling>(tiling), static_cast<ImageUsageFlags>(usage), static_cast<ImageCreateFlags>(flags), reinterpret_cast<ImageFormatProperties*>(pImageFormatProperties));
    }
    VkResult CreateDevice(
        const DeviceCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Device* pDevice) {
        return vkCreateDevice(get(), reinterpret_cast<const DeviceCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Device*>(pDevice));
    }
    VkResult EnumerateDeviceLayerProperties(
        uint32_t* pPropertyCount,    
        LayerProperties* pProperties) {
        return vkEnumerateDeviceLayerProperties(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<LayerProperties*>(pProperties));
    }
    VkResult EnumerateDeviceExtensionProperties(
        const char* pLayerName,    
        uint32_t* pPropertyCount,    
        ExtensionProperties* pProperties) {
        return vkEnumerateDeviceExtensionProperties(get(), reinterpret_cast<const char*>(pLayerName), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<ExtensionProperties*>(pProperties));
    }
    void GetPhysicalDeviceSparseImageFormatProperties(
        Format format,    
        ImageType type,    
        SampleCountFlagBits samples,    
        ImageUsageFlags usage,    
        ImageTiling tiling,    
        uint32_t* pPropertyCount,    
        SparseImageFormatProperties* pProperties) {
        return vkGetPhysicalDeviceSparseImageFormatProperties(get(), static_cast<Format>(format), static_cast<ImageType>(type), static_cast<SampleCountFlagBits>(samples), static_cast<ImageUsageFlags>(usage), static_cast<ImageTiling>(tiling), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<SparseImageFormatProperties*>(pProperties));
    }
    VkResult GetPhysicalDeviceDisplayPropertiesKHR(
        uint32_t* pPropertyCount,    
        DisplayPropertiesKHR* pProperties) {
        return vkGetPhysicalDeviceDisplayPropertiesKHR(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayPropertiesKHR*>(pProperties));
    }
    VkResult GetPhysicalDeviceDisplayPlanePropertiesKHR(
        uint32_t* pPropertyCount,    
        DisplayPlanePropertiesKHR* pProperties) {
        return vkGetPhysicalDeviceDisplayPlanePropertiesKHR(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayPlanePropertiesKHR*>(pProperties));
    }
    VkResult GetDisplayPlaneSupportedDisplaysKHR(
        uint32_t planeIndex,    
        uint32_t* pDisplayCount,    
        DisplayKHR* pDisplays) {
        return vkGetDisplayPlaneSupportedDisplaysKHR(get(), static_cast<uint32_t>(planeIndex), reinterpret_cast<uint32_t*>(pDisplayCount), reinterpret_cast<DisplayKHR*>(pDisplays));
    }
    VkResult GetDisplayModePropertiesKHR(
        DisplayKHR display,    
        uint32_t* pPropertyCount,    
        DisplayModePropertiesKHR* pProperties) {
        return vkGetDisplayModePropertiesKHR(get(),display.get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayModePropertiesKHR*>(pProperties));
    }
    VkResult CreateDisplayModeKHR(
        DisplayKHR display,    
        const DisplayModeCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DisplayModeKHR* pMode) {
        return vkCreateDisplayModeKHR(get(),display.get(), reinterpret_cast<const DisplayModeCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DisplayModeKHR*>(pMode));
    }
    VkResult GetDisplayPlaneCapabilitiesKHR(
        DisplayModeKHR mode,    
        uint32_t planeIndex,    
        DisplayPlaneCapabilitiesKHR* pCapabilities) {
        return vkGetDisplayPlaneCapabilitiesKHR(get(),mode.get(), static_cast<uint32_t>(planeIndex), reinterpret_cast<DisplayPlaneCapabilitiesKHR*>(pCapabilities));
    }
    VkResult GetPhysicalDeviceSurfaceSupportKHR(
        uint32_t queueFamilyIndex,    
        SurfaceKHR surface,    
        bool* pSupported) {
        return vkGetPhysicalDeviceSurfaceSupportKHR(get(), static_cast<uint32_t>(queueFamilyIndex),surface.get(), reinterpret_cast<bool*>(pSupported));
    }
    VkResult GetPhysicalDeviceSurfaceCapabilitiesKHR(
        SurfaceKHR surface,    
        SurfaceCapabilitiesKHR* pSurfaceCapabilities) {
        return vkGetPhysicalDeviceSurfaceCapabilitiesKHR(get(),surface.get(), reinterpret_cast<SurfaceCapabilitiesKHR*>(pSurfaceCapabilities));
    }
    VkResult GetPhysicalDeviceSurfaceFormatsKHR(
        SurfaceKHR surface,    
        uint32_t* pSurfaceFormatCount,    
        SurfaceFormatKHR* pSurfaceFormats) {
        return vkGetPhysicalDeviceSurfaceFormatsKHR(get(),surface.get(), reinterpret_cast<uint32_t*>(pSurfaceFormatCount), reinterpret_cast<SurfaceFormatKHR*>(pSurfaceFormats));
    }
    VkResult GetPhysicalDeviceSurfacePresentModesKHR(
        SurfaceKHR surface,    
        uint32_t* pPresentModeCount,    
        PresentModeKHR* pPresentModes) {
        return vkGetPhysicalDeviceSurfacePresentModesKHR(get(),surface.get(), reinterpret_cast<uint32_t*>(pPresentModeCount), reinterpret_cast<PresentModeKHR*>(pPresentModes));
    }
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkBool32 GetPhysicalDeviceWaylandPresentationSupportKHR(
        uint32_t queueFamilyIndex,    
        wl_display* display) {
        return vkGetPhysicalDeviceWaylandPresentationSupportKHR(get(), static_cast<uint32_t>(queueFamilyIndex), reinterpret_cast<wl_display*>(display));
    }
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkBool32 GetPhysicalDeviceWin32PresentationSupportKHR(
        uint32_t queueFamilyIndex) {
        return vkGetPhysicalDeviceWin32PresentationSupportKHR(get(), static_cast<uint32_t>(queueFamilyIndex));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)
    VkBool32 GetPhysicalDeviceXlibPresentationSupportKHR(
        uint32_t queueFamilyIndex,    
        Display* dpy,    
        VisualID visualID) {
        return vkGetPhysicalDeviceXlibPresentationSupportKHR(get(), static_cast<uint32_t>(queueFamilyIndex), reinterpret_cast<Display*>(dpy), static_cast<VisualID>(visualID));
    }
#endif // VK_USE_PLATFORM_XLIB_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)
    VkBool32 GetPhysicalDeviceXcbPresentationSupportKHR(
        uint32_t queueFamilyIndex,    
        xcb_connection_t* connection,    
        xcb_visualid_t visual_id) {
        return vkGetPhysicalDeviceXcbPresentationSupportKHR(get(), static_cast<uint32_t>(queueFamilyIndex), reinterpret_cast<xcb_connection_t*>(connection), static_cast<xcb_visualid_t>(visual_id));
    }
#endif // VK_USE_PLATFORM_XCB_KHR
    VkResult GetPhysicalDeviceExternalImageFormatPropertiesNV(
        Format format,    
        ImageType type,    
        ImageTiling tiling,    
        ImageUsageFlags usage,    
        ImageCreateFlags flags,    
        ExternalMemoryHandleTypeFlagsNV externalHandleType,    
        ExternalImageFormatPropertiesNV* pExternalImageFormatProperties) {
        return vkGetPhysicalDeviceExternalImageFormatPropertiesNV(get(), static_cast<Format>(format), static_cast<ImageType>(type), static_cast<ImageTiling>(tiling), static_cast<ImageUsageFlags>(usage), static_cast<ImageCreateFlags>(flags), static_cast<ExternalMemoryHandleTypeFlagsNV>(externalHandleType), reinterpret_cast<ExternalImageFormatPropertiesNV*>(pExternalImageFormatProperties));
    }
    void GetPhysicalDeviceFeatures2(
        PhysicalDeviceFeatures2* pFeatures) {
        return vkGetPhysicalDeviceFeatures2(get(), reinterpret_cast<PhysicalDeviceFeatures2*>(pFeatures));
    }
    void GetPhysicalDeviceProperties2(
        PhysicalDeviceProperties2* pProperties) {
        return vkGetPhysicalDeviceProperties2(get(), reinterpret_cast<PhysicalDeviceProperties2*>(pProperties));
    }
    void GetPhysicalDeviceFormatProperties2(
        Format format,    
        FormatProperties2* pFormatProperties) {
        return vkGetPhysicalDeviceFormatProperties2(get(), static_cast<Format>(format), reinterpret_cast<FormatProperties2*>(pFormatProperties));
    }
    VkResult GetPhysicalDeviceImageFormatProperties2(
        const PhysicalDeviceImageFormatInfo2* pImageFormatInfo,    
        ImageFormatProperties2* pImageFormatProperties) {
        return vkGetPhysicalDeviceImageFormatProperties2(get(), reinterpret_cast<const PhysicalDeviceImageFormatInfo2*>(pImageFormatInfo), reinterpret_cast<ImageFormatProperties2*>(pImageFormatProperties));
    }
    void GetPhysicalDeviceQueueFamilyProperties2(
        uint32_t* pQueueFamilyPropertyCount,    
        QueueFamilyProperties2* pQueueFamilyProperties) {
        return vkGetPhysicalDeviceQueueFamilyProperties2(get(), reinterpret_cast<uint32_t*>(pQueueFamilyPropertyCount), reinterpret_cast<QueueFamilyProperties2*>(pQueueFamilyProperties));
    }
    void GetPhysicalDeviceMemoryProperties2(
        PhysicalDeviceMemoryProperties2* pMemoryProperties) {
        return vkGetPhysicalDeviceMemoryProperties2(get(), reinterpret_cast<PhysicalDeviceMemoryProperties2*>(pMemoryProperties));
    }
    void GetPhysicalDeviceSparseImageFormatProperties2(
        const PhysicalDeviceSparseImageFormatInfo2* pFormatInfo,    
        uint32_t* pPropertyCount,    
        SparseImageFormatProperties2* pProperties) {
        return vkGetPhysicalDeviceSparseImageFormatProperties2(get(), reinterpret_cast<const PhysicalDeviceSparseImageFormatInfo2*>(pFormatInfo), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<SparseImageFormatProperties2*>(pProperties));
    }
    void GetPhysicalDeviceExternalBufferProperties(
        const PhysicalDeviceExternalBufferInfo* pExternalBufferInfo,    
        ExternalBufferProperties* pExternalBufferProperties) {
        return vkGetPhysicalDeviceExternalBufferProperties(get(), reinterpret_cast<const PhysicalDeviceExternalBufferInfo*>(pExternalBufferInfo), reinterpret_cast<ExternalBufferProperties*>(pExternalBufferProperties));
    }
    void GetPhysicalDeviceExternalSemaphoreProperties(
        const PhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,    
        ExternalSemaphoreProperties* pExternalSemaphoreProperties) {
        return vkGetPhysicalDeviceExternalSemaphoreProperties(get(), reinterpret_cast<const PhysicalDeviceExternalSemaphoreInfo*>(pExternalSemaphoreInfo), reinterpret_cast<ExternalSemaphoreProperties*>(pExternalSemaphoreProperties));
    }
    void GetPhysicalDeviceExternalFenceProperties(
        const PhysicalDeviceExternalFenceInfo* pExternalFenceInfo,    
        ExternalFenceProperties* pExternalFenceProperties) {
        return vkGetPhysicalDeviceExternalFenceProperties(get(), reinterpret_cast<const PhysicalDeviceExternalFenceInfo*>(pExternalFenceInfo), reinterpret_cast<ExternalFenceProperties*>(pExternalFenceProperties));
    }
    VkResult ReleaseDisplayEXT(
        DisplayKHR display) {
        return vkReleaseDisplayEXT(get(),display.get());
    }
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    VkResult AcquireXlibDisplayEXT(
        Display* dpy,    
        DisplayKHR display) {
        return vkAcquireXlibDisplayEXT(get(), reinterpret_cast<Display*>(dpy),display.get());
    }
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
    VkResult GetRandROutputDisplayEXT(
        Display* dpy,    
        RROutput rrOutput,    
        DisplayKHR* pDisplay) {
        return vkGetRandROutputDisplayEXT(get(), reinterpret_cast<Display*>(dpy), static_cast<RROutput>(rrOutput), reinterpret_cast<DisplayKHR*>(pDisplay));
    }
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
    VkResult GetPhysicalDeviceSurfaceCapabilities2EXT(
        SurfaceKHR surface,    
        SurfaceCapabilities2EXT* pSurfaceCapabilities) {
        return vkGetPhysicalDeviceSurfaceCapabilities2EXT(get(),surface.get(), reinterpret_cast<SurfaceCapabilities2EXT*>(pSurfaceCapabilities));
    }
    VkResult GetPhysicalDevicePresentRectanglesKHR(
        SurfaceKHR surface,    
        uint32_t* pRectCount,    
        Rect2D* pRects) {
        return vkGetPhysicalDevicePresentRectanglesKHR(get(),surface.get(), reinterpret_cast<uint32_t*>(pRectCount), reinterpret_cast<Rect2D*>(pRects));
    }
    void GetPhysicalDeviceMultisamplePropertiesEXT(
        SampleCountFlagBits samples,    
        MultisamplePropertiesEXT* pMultisampleProperties) {
        return vkGetPhysicalDeviceMultisamplePropertiesEXT(get(), static_cast<SampleCountFlagBits>(samples), reinterpret_cast<MultisamplePropertiesEXT*>(pMultisampleProperties));
    }
    VkResult GetPhysicalDeviceSurfaceCapabilities2KHR(
        const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,    
        SurfaceCapabilities2KHR* pSurfaceCapabilities) {
        return vkGetPhysicalDeviceSurfaceCapabilities2KHR(get(), reinterpret_cast<const PhysicalDeviceSurfaceInfo2KHR*>(pSurfaceInfo), reinterpret_cast<SurfaceCapabilities2KHR*>(pSurfaceCapabilities));
    }
    VkResult GetPhysicalDeviceSurfaceFormats2KHR(
        const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,    
        uint32_t* pSurfaceFormatCount,    
        SurfaceFormat2KHR* pSurfaceFormats) {
        return vkGetPhysicalDeviceSurfaceFormats2KHR(get(), reinterpret_cast<const PhysicalDeviceSurfaceInfo2KHR*>(pSurfaceInfo), reinterpret_cast<uint32_t*>(pSurfaceFormatCount), reinterpret_cast<SurfaceFormat2KHR*>(pSurfaceFormats));
    }
    VkResult GetPhysicalDeviceDisplayProperties2KHR(
        uint32_t* pPropertyCount,    
        DisplayProperties2KHR* pProperties) {
        return vkGetPhysicalDeviceDisplayProperties2KHR(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayProperties2KHR*>(pProperties));
    }
    VkResult GetPhysicalDeviceDisplayPlaneProperties2KHR(
        uint32_t* pPropertyCount,    
        DisplayPlaneProperties2KHR* pProperties) {
        return vkGetPhysicalDeviceDisplayPlaneProperties2KHR(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayPlaneProperties2KHR*>(pProperties));
    }
    VkResult GetDisplayModeProperties2KHR(
        DisplayKHR display,    
        uint32_t* pPropertyCount,    
        DisplayModeProperties2KHR* pProperties) {
        return vkGetDisplayModeProperties2KHR(get(),display.get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<DisplayModeProperties2KHR*>(pProperties));
    }
    VkResult GetDisplayPlaneCapabilities2KHR(
        const DisplayPlaneInfo2KHR* pDisplayPlaneInfo,    
        DisplayPlaneCapabilities2KHR* pCapabilities) {
        return vkGetDisplayPlaneCapabilities2KHR(get(), reinterpret_cast<const DisplayPlaneInfo2KHR*>(pDisplayPlaneInfo), reinterpret_cast<DisplayPlaneCapabilities2KHR*>(pCapabilities));
    }
    VkResult GetPhysicalDeviceCalibrateableTimeDomainsEXT(
        uint32_t* pTimeDomainCount,    
        TimeDomainEXT* pTimeDomains) {
        return vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(get(), reinterpret_cast<uint32_t*>(pTimeDomainCount), reinterpret_cast<TimeDomainEXT*>(pTimeDomains));
    }
    VkResult GetPhysicalDeviceCooperativeMatrixPropertiesNV(
        uint32_t* pPropertyCount,    
        CooperativeMatrixPropertiesNV* pProperties) {
        return vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(get(), reinterpret_cast<uint32_t*>(pPropertyCount), reinterpret_cast<CooperativeMatrixPropertiesNV*>(pProperties));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetPhysicalDeviceSurfacePresentModes2EXT(
        const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,    
        uint32_t* pPresentModeCount,    
        PresentModeKHR* pPresentModes) {
        return vkGetPhysicalDeviceSurfacePresentModes2EXT(get(), reinterpret_cast<const PhysicalDeviceSurfaceInfo2KHR*>(pSurfaceInfo), reinterpret_cast<uint32_t*>(pPresentModeCount), reinterpret_cast<PresentModeKHR*>(pPresentModes));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    VkResult EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
        uint32_t queueFamilyIndex,    
        uint32_t* pCounterCount,    
        PerformanceCounterKHR* pCounters,    
        PerformanceCounterDescriptionKHR* pCounterDescriptions) {
        return vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(get(), static_cast<uint32_t>(queueFamilyIndex), reinterpret_cast<uint32_t*>(pCounterCount), reinterpret_cast<PerformanceCounterKHR*>(pCounters), reinterpret_cast<PerformanceCounterDescriptionKHR*>(pCounterDescriptions));
    }
    void GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
        const QueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo,    
        uint32_t* pNumPasses) {
        return vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(get(), reinterpret_cast<const QueryPoolPerformanceCreateInfoKHR*>(pPerformanceQueryCreateInfo), reinterpret_cast<uint32_t*>(pNumPasses));
    }
    VkResult GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
        uint32_t* pCombinationCount,    
        FramebufferMixedSamplesCombinationNV* pCombinations) {
        return vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(get(), reinterpret_cast<uint32_t*>(pCombinationCount), reinterpret_cast<FramebufferMixedSamplesCombinationNV*>(pCombinations));
    }
    VkResult GetPhysicalDeviceToolPropertiesEXT(
        uint32_t* pToolCount,    
        PhysicalDeviceToolPropertiesEXT* pToolProperties) {
        return vkGetPhysicalDeviceToolPropertiesEXT(get(), reinterpret_cast<uint32_t*>(pToolCount), reinterpret_cast<PhysicalDeviceToolPropertiesEXT*>(pToolProperties));
    }
};
struct Device {
    VkDevice handle;
    VkDevice get() { return handle; }
    PFN_vkVoidFunction GetDeviceProcAddr(
        const char* pName) {
        return vkGetDeviceProcAddr(get(), reinterpret_cast<const char*>(pName));
    }
    void DestroyDevice(
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDevice(get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void GetDeviceQueue(
        uint32_t queueFamilyIndex,    
        uint32_t queueIndex,    
        Queue* pQueue) {
        return vkGetDeviceQueue(get(), static_cast<uint32_t>(queueFamilyIndex), static_cast<uint32_t>(queueIndex), reinterpret_cast<Queue*>(pQueue));
    }
    VkResult DeviceWaitIdle() {
        return vkDeviceWaitIdle(get());
    }
    VkResult AllocateMemory(
        const MemoryAllocateInfo* pAllocateInfo,    
        const AllocationCallbacks* pAllocator,    
        DeviceMemory* pMemory) {
        return vkAllocateMemory(get(), reinterpret_cast<const MemoryAllocateInfo*>(pAllocateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DeviceMemory*>(pMemory));
    }
    void FreeMemory(
        DeviceMemory memory,    
        const AllocationCallbacks* pAllocator) {
        return vkFreeMemory(get(),memory.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult MapMemory(
        DeviceMemory memory,    
        DeviceSize offset,    
        DeviceSize size,    
        MemoryMapFlags flags,    
        void** ppData) {
        return vkMapMemory(get(),memory.get(), static_cast<DeviceSize>(offset), static_cast<DeviceSize>(size), static_cast<MemoryMapFlags>(flags), static_cast<void**>(ppData));
    }
    void UnmapMemory(
        DeviceMemory memory) {
        return vkUnmapMemory(get(),memory.get());
    }
    VkResult FlushMappedMemoryRanges(
        uint32_t memoryRangeCount,    
        const MappedMemoryRange* pMemoryRanges) {
        return vkFlushMappedMemoryRanges(get(), static_cast<uint32_t>(memoryRangeCount), reinterpret_cast<const MappedMemoryRange*>(pMemoryRanges));
    }
    VkResult InvalidateMappedMemoryRanges(
        uint32_t memoryRangeCount,    
        const MappedMemoryRange* pMemoryRanges) {
        return vkInvalidateMappedMemoryRanges(get(), static_cast<uint32_t>(memoryRangeCount), reinterpret_cast<const MappedMemoryRange*>(pMemoryRanges));
    }
    void GetDeviceMemoryCommitment(
        DeviceMemory memory,    
        DeviceSize* pCommittedMemoryInBytes) {
        return vkGetDeviceMemoryCommitment(get(),memory.get(), reinterpret_cast<DeviceSize*>(pCommittedMemoryInBytes));
    }
    void GetBufferMemoryRequirements(
        Buffer buffer,    
        MemoryRequirements* pMemoryRequirements) {
        return vkGetBufferMemoryRequirements(get(),buffer.get(), reinterpret_cast<MemoryRequirements*>(pMemoryRequirements));
    }
    VkResult BindBufferMemory(
        Buffer buffer,    
        DeviceMemory memory,    
        DeviceSize memoryOffset) {
        return vkBindBufferMemory(get(),buffer.get(),memory.get(), static_cast<DeviceSize>(memoryOffset));
    }
    void GetImageMemoryRequirements(
        Image image,    
        MemoryRequirements* pMemoryRequirements) {
        return vkGetImageMemoryRequirements(get(),image.get(), reinterpret_cast<MemoryRequirements*>(pMemoryRequirements));
    }
    VkResult BindImageMemory(
        Image image,    
        DeviceMemory memory,    
        DeviceSize memoryOffset) {
        return vkBindImageMemory(get(),image.get(),memory.get(), static_cast<DeviceSize>(memoryOffset));
    }
    void GetImageSparseMemoryRequirements(
        Image image,    
        uint32_t* pSparseMemoryRequirementCount,    
        SparseImageMemoryRequirements* pSparseMemoryRequirements) {
        return vkGetImageSparseMemoryRequirements(get(),image.get(), reinterpret_cast<uint32_t*>(pSparseMemoryRequirementCount), reinterpret_cast<SparseImageMemoryRequirements*>(pSparseMemoryRequirements));
    }
    VkResult CreateFence(
        const FenceCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Fence* pFence) {
        return vkCreateFence(get(), reinterpret_cast<const FenceCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Fence*>(pFence));
    }
    void DestroyFence(
        Fence fence,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyFence(get(),fence.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult ResetFences(
        uint32_t fenceCount,    
        const Fence* pFences) {
        return vkResetFences(get(), static_cast<uint32_t>(fenceCount), reinterpret_cast<const Fence*>(pFences));
    }
    VkResult GetFenceStatus(
        Fence fence) {
        return vkGetFenceStatus(get(),fence.get());
    }
    VkResult WaitForFences(
        uint32_t fenceCount,    
        const Fence* pFences,    
        bool waitAll,    
        uint64_t timeout) {
        return vkWaitForFences(get(), static_cast<uint32_t>(fenceCount), reinterpret_cast<const Fence*>(pFences), static_cast<bool>(waitAll), static_cast<uint64_t>(timeout));
    }
    VkResult CreateSemaphore(
        const SemaphoreCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Semaphore* pSemaphore) {
        return vkCreateSemaphore(get(), reinterpret_cast<const SemaphoreCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Semaphore*>(pSemaphore));
    }
    void DestroySemaphore(
        Semaphore semaphore,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroySemaphore(get(),semaphore.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateEvent(
        const EventCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Event* pEvent) {
        return vkCreateEvent(get(), reinterpret_cast<const EventCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Event*>(pEvent));
    }
    void DestroyEvent(
        Event event,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyEvent(get(),event.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult GetEventStatus(
        Event event) {
        return vkGetEventStatus(get(),event.get());
    }
    VkResult SetEvent(
        Event event) {
        return vkSetEvent(get(),event.get());
    }
    VkResult ResetEvent(
        Event event) {
        return vkResetEvent(get(),event.get());
    }
    VkResult CreateQueryPool(
        const QueryPoolCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        QueryPool* pQueryPool) {
        return vkCreateQueryPool(get(), reinterpret_cast<const QueryPoolCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<QueryPool*>(pQueryPool));
    }
    void DestroyQueryPool(
        QueryPool queryPool,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyQueryPool(get(),queryPool.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult GetQueryPoolResults(
        QueryPool queryPool,    
        uint32_t firstQuery,    
        uint32_t queryCount,    
        size_t dataSize,    
        void* pData,    
        DeviceSize stride,    
        QueryResultFlags flags) {
        return vkGetQueryPoolResults(get(),queryPool.get(), static_cast<uint32_t>(firstQuery), static_cast<uint32_t>(queryCount), static_cast<size_t>(dataSize), reinterpret_cast<void*>(pData), static_cast<DeviceSize>(stride), static_cast<QueryResultFlags>(flags));
    }
    void ResetQueryPool(
        QueryPool queryPool,    
        uint32_t firstQuery,    
        uint32_t queryCount) {
        return vkResetQueryPool(get(),queryPool.get(), static_cast<uint32_t>(firstQuery), static_cast<uint32_t>(queryCount));
    }
    VkResult CreateBuffer(
        const BufferCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Buffer* pBuffer) {
        return vkCreateBuffer(get(), reinterpret_cast<const BufferCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Buffer*>(pBuffer));
    }
    void DestroyBuffer(
        Buffer buffer,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyBuffer(get(),buffer.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateBufferView(
        const BufferViewCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        BufferView* pView) {
        return vkCreateBufferView(get(), reinterpret_cast<const BufferViewCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<BufferView*>(pView));
    }
    void DestroyBufferView(
        BufferView bufferView,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyBufferView(get(),bufferView.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateImage(
        const ImageCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Image* pImage) {
        return vkCreateImage(get(), reinterpret_cast<const ImageCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Image*>(pImage));
    }
    void DestroyImage(
        Image image,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyImage(get(),image.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void GetImageSubresourceLayout(
        Image image,    
        const ImageSubresource* pSubresource,    
        SubresourceLayout* pLayout) {
        return vkGetImageSubresourceLayout(get(),image.get(), reinterpret_cast<const ImageSubresource*>(pSubresource), reinterpret_cast<SubresourceLayout*>(pLayout));
    }
    VkResult CreateImageView(
        const ImageViewCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        ImageView* pView) {
        return vkCreateImageView(get(), reinterpret_cast<const ImageViewCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<ImageView*>(pView));
    }
    void DestroyImageView(
        ImageView imageView,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyImageView(get(),imageView.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateShaderModule(
        const ShaderModuleCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        ShaderModule* pShaderModule) {
        return vkCreateShaderModule(get(), reinterpret_cast<const ShaderModuleCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<ShaderModule*>(pShaderModule));
    }
    void DestroyShaderModule(
        ShaderModule shaderModule,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyShaderModule(get(),shaderModule.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreatePipelineCache(
        const PipelineCacheCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        PipelineCache* pPipelineCache) {
        return vkCreatePipelineCache(get(), reinterpret_cast<const PipelineCacheCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<PipelineCache*>(pPipelineCache));
    }
    void DestroyPipelineCache(
        PipelineCache pipelineCache,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyPipelineCache(get(),pipelineCache.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult GetPipelineCacheData(
        PipelineCache pipelineCache,    
        size_t* pDataSize,    
        void* pData) {
        return vkGetPipelineCacheData(get(),pipelineCache.get(), reinterpret_cast<size_t*>(pDataSize), reinterpret_cast<void*>(pData));
    }
    VkResult MergePipelineCaches(
        PipelineCache dstCache,    
        uint32_t srcCacheCount,    
        const PipelineCache* pSrcCaches) {
        return vkMergePipelineCaches(get(),dstCache.get(), static_cast<uint32_t>(srcCacheCount), reinterpret_cast<const PipelineCache*>(pSrcCaches));
    }
    VkResult CreateGraphicsPipelines(
        PipelineCache pipelineCache,    
        uint32_t createInfoCount,    
        const GraphicsPipelineCreateInfo* pCreateInfos,    
        const AllocationCallbacks* pAllocator,    
        Pipeline* pPipelines) {
        return vkCreateGraphicsPipelines(get(),pipelineCache.get(), static_cast<uint32_t>(createInfoCount), reinterpret_cast<const GraphicsPipelineCreateInfo*>(pCreateInfos), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Pipeline*>(pPipelines));
    }
    VkResult CreateComputePipelines(
        PipelineCache pipelineCache,    
        uint32_t createInfoCount,    
        const ComputePipelineCreateInfo* pCreateInfos,    
        const AllocationCallbacks* pAllocator,    
        Pipeline* pPipelines) {
        return vkCreateComputePipelines(get(),pipelineCache.get(), static_cast<uint32_t>(createInfoCount), reinterpret_cast<const ComputePipelineCreateInfo*>(pCreateInfos), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Pipeline*>(pPipelines));
    }
    void DestroyPipeline(
        Pipeline pipeline,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyPipeline(get(),pipeline.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreatePipelineLayout(
        const PipelineLayoutCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        PipelineLayout* pPipelineLayout) {
        return vkCreatePipelineLayout(get(), reinterpret_cast<const PipelineLayoutCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<PipelineLayout*>(pPipelineLayout));
    }
    void DestroyPipelineLayout(
        PipelineLayout pipelineLayout,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyPipelineLayout(get(),pipelineLayout.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateSampler(
        const SamplerCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Sampler* pSampler) {
        return vkCreateSampler(get(), reinterpret_cast<const SamplerCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Sampler*>(pSampler));
    }
    void DestroySampler(
        Sampler sampler,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroySampler(get(),sampler.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateDescriptorSetLayout(
        const DescriptorSetLayoutCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DescriptorSetLayout* pSetLayout) {
        return vkCreateDescriptorSetLayout(get(), reinterpret_cast<const DescriptorSetLayoutCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DescriptorSetLayout*>(pSetLayout));
    }
    void DestroyDescriptorSetLayout(
        DescriptorSetLayout descriptorSetLayout,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDescriptorSetLayout(get(),descriptorSetLayout.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateDescriptorPool(
        const DescriptorPoolCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DescriptorPool* pDescriptorPool) {
        return vkCreateDescriptorPool(get(), reinterpret_cast<const DescriptorPoolCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DescriptorPool*>(pDescriptorPool));
    }
    void DestroyDescriptorPool(
        DescriptorPool descriptorPool,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDescriptorPool(get(),descriptorPool.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult ResetDescriptorPool(
        DescriptorPool descriptorPool,    
        DescriptorPoolResetFlags flags) {
        return vkResetDescriptorPool(get(),descriptorPool.get(), static_cast<DescriptorPoolResetFlags>(flags));
    }
    VkResult AllocateDescriptorSets(
        const DescriptorSetAllocateInfo* pAllocateInfo,    
        DescriptorSet* pDescriptorSets) {
        return vkAllocateDescriptorSets(get(), reinterpret_cast<const DescriptorSetAllocateInfo*>(pAllocateInfo), reinterpret_cast<DescriptorSet*>(pDescriptorSets));
    }
    VkResult FreeDescriptorSets(
        DescriptorPool descriptorPool,    
        uint32_t descriptorSetCount,    
        const DescriptorSet* pDescriptorSets) {
        return vkFreeDescriptorSets(get(),descriptorPool.get(), static_cast<uint32_t>(descriptorSetCount), reinterpret_cast<const DescriptorSet*>(pDescriptorSets));
    }
    void UpdateDescriptorSets(
        uint32_t descriptorWriteCount,    
        const WriteDescriptorSet* pDescriptorWrites,    
        uint32_t descriptorCopyCount,    
        const CopyDescriptorSet* pDescriptorCopies) {
        return vkUpdateDescriptorSets(get(), static_cast<uint32_t>(descriptorWriteCount), reinterpret_cast<const WriteDescriptorSet*>(pDescriptorWrites), static_cast<uint32_t>(descriptorCopyCount), reinterpret_cast<const CopyDescriptorSet*>(pDescriptorCopies));
    }
    VkResult CreateFramebuffer(
        const FramebufferCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        Framebuffer* pFramebuffer) {
        return vkCreateFramebuffer(get(), reinterpret_cast<const FramebufferCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Framebuffer*>(pFramebuffer));
    }
    void DestroyFramebuffer(
        Framebuffer framebuffer,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyFramebuffer(get(),framebuffer.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult CreateRenderPass(
        const RenderPassCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        RenderPass* pRenderPass) {
        return vkCreateRenderPass(get(), reinterpret_cast<const RenderPassCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<RenderPass*>(pRenderPass));
    }
    void DestroyRenderPass(
        RenderPass renderPass,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyRenderPass(get(),renderPass.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void GetRenderAreaGranularity(
        RenderPass renderPass,    
        Extent2D* pGranularity) {
        return vkGetRenderAreaGranularity(get(),renderPass.get(), reinterpret_cast<Extent2D*>(pGranularity));
    }
    VkResult CreateCommandPool(
        const CommandPoolCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        CommandPool* pCommandPool) {
        return vkCreateCommandPool(get(), reinterpret_cast<const CommandPoolCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<CommandPool*>(pCommandPool));
    }
    void DestroyCommandPool(
        CommandPool commandPool,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyCommandPool(get(),commandPool.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult ResetCommandPool(
        CommandPool commandPool,    
        CommandPoolResetFlags flags) {
        return vkResetCommandPool(get(),commandPool.get(), static_cast<CommandPoolResetFlags>(flags));
    }
    VkResult AllocateCommandBuffers(
        const CommandBufferAllocateInfo* pAllocateInfo,    
        CommandBuffer* pCommandBuffers) {
        return vkAllocateCommandBuffers(get(), reinterpret_cast<const CommandBufferAllocateInfo*>(pAllocateInfo), reinterpret_cast<CommandBuffer*>(pCommandBuffers));
    }
    void FreeCommandBuffers(
        CommandPool commandPool,    
        uint32_t commandBufferCount,    
        const CommandBuffer* pCommandBuffers) {
        return vkFreeCommandBuffers(get(),commandPool.get(), static_cast<uint32_t>(commandBufferCount), reinterpret_cast<const CommandBuffer*>(pCommandBuffers));
    }
    VkResult CreateSharedSwapchainsKHR(
        uint32_t swapchainCount,    
        const SwapchainCreateInfoKHR* pCreateInfos,    
        const AllocationCallbacks* pAllocator,    
        SwapchainKHR* pSwapchains) {
        return vkCreateSharedSwapchainsKHR(get(), static_cast<uint32_t>(swapchainCount), reinterpret_cast<const SwapchainCreateInfoKHR*>(pCreateInfos), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SwapchainKHR*>(pSwapchains));
    }
    VkResult CreateSwapchainKHR(
        const SwapchainCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SwapchainKHR* pSwapchain) {
        return vkCreateSwapchainKHR(get(), reinterpret_cast<const SwapchainCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SwapchainKHR*>(pSwapchain));
    }
    void DestroySwapchainKHR(
        SwapchainKHR swapchain,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroySwapchainKHR(get(),swapchain.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult GetSwapchainImagesKHR(
        SwapchainKHR swapchain,    
        uint32_t* pSwapchainImageCount,    
        Image* pSwapchainImages) {
        return vkGetSwapchainImagesKHR(get(),swapchain.get(), reinterpret_cast<uint32_t*>(pSwapchainImageCount), reinterpret_cast<Image*>(pSwapchainImages));
    }
    VkResult AcquireNextImageKHR(
        SwapchainKHR swapchain,    
        uint64_t timeout,    
        Semaphore semaphore,    
        Fence fence,    
        uint32_t* pImageIndex) {
        return vkAcquireNextImageKHR(get(),swapchain.get(), static_cast<uint64_t>(timeout),semaphore.get(),fence.get(), reinterpret_cast<uint32_t*>(pImageIndex));
    }
    VkResult DebugMarkerSetObjectNameEXT(
        const DebugMarkerObjectNameInfoEXT* pNameInfo) {
        return vkDebugMarkerSetObjectNameEXT(get(), reinterpret_cast<const DebugMarkerObjectNameInfoEXT*>(pNameInfo));
    }
    VkResult DebugMarkerSetObjectTagEXT(
        const DebugMarkerObjectTagInfoEXT* pTagInfo) {
        return vkDebugMarkerSetObjectTagEXT(get(), reinterpret_cast<const DebugMarkerObjectTagInfoEXT*>(pTagInfo));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetMemoryWin32HandleNV(
        DeviceMemory memory,    
        ExternalMemoryHandleTypeFlagsNV handleType,    
        HANDLE* pHandle) {
        return vkGetMemoryWin32HandleNV(get(),memory.get(), static_cast<ExternalMemoryHandleTypeFlagsNV>(handleType), reinterpret_cast<HANDLE*>(pHandle));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    void GetGeneratedCommandsMemoryRequirementsNV(
        const GeneratedCommandsMemoryRequirementsInfoNV* pInfo,    
        MemoryRequirements2* pMemoryRequirements) {
        return vkGetGeneratedCommandsMemoryRequirementsNV(get(), reinterpret_cast<const GeneratedCommandsMemoryRequirementsInfoNV*>(pInfo), reinterpret_cast<MemoryRequirements2*>(pMemoryRequirements));
    }
    VkResult CreateIndirectCommandsLayoutNV(
        const IndirectCommandsLayoutCreateInfoNV* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        IndirectCommandsLayoutNV* pIndirectCommandsLayout) {
        return vkCreateIndirectCommandsLayoutNV(get(), reinterpret_cast<const IndirectCommandsLayoutCreateInfoNV*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<IndirectCommandsLayoutNV*>(pIndirectCommandsLayout));
    }
    void DestroyIndirectCommandsLayoutNV(
        IndirectCommandsLayoutNV indirectCommandsLayout,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyIndirectCommandsLayoutNV(get(),indirectCommandsLayout.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void TrimCommandPool(
        CommandPool commandPool,    
        CommandPoolTrimFlags flags) {
        return vkTrimCommandPool(get(),commandPool.get(), static_cast<CommandPoolTrimFlags>(flags));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetMemoryWin32HandleKHR(
        const MemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo,    
        HANDLE* pHandle) {
        return vkGetMemoryWin32HandleKHR(get(), reinterpret_cast<const MemoryGetWin32HandleInfoKHR*>(pGetWin32HandleInfo), reinterpret_cast<HANDLE*>(pHandle));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetMemoryWin32HandlePropertiesKHR(
        ExternalMemoryHandleTypeFlagBits handleType,    
        HANDLE handle,    
        MemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) {
        return vkGetMemoryWin32HandlePropertiesKHR(get(), static_cast<ExternalMemoryHandleTypeFlagBits>(handleType), static_cast<HANDLE>(handle), reinterpret_cast<MemoryWin32HandlePropertiesKHR*>(pMemoryWin32HandleProperties));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    VkResult GetMemoryFdKHR(
        const MemoryGetFdInfoKHR* pGetFdInfo,    
        int* pFd) {
        return vkGetMemoryFdKHR(get(), reinterpret_cast<const MemoryGetFdInfoKHR*>(pGetFdInfo), reinterpret_cast<int*>(pFd));
    }
    VkResult GetMemoryFdPropertiesKHR(
        ExternalMemoryHandleTypeFlagBits handleType,    
        int fd,    
        MemoryFdPropertiesKHR* pMemoryFdProperties) {
        return vkGetMemoryFdPropertiesKHR(get(), static_cast<ExternalMemoryHandleTypeFlagBits>(handleType), static_cast<int>(fd), reinterpret_cast<MemoryFdPropertiesKHR*>(pMemoryFdProperties));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetSemaphoreWin32HandleKHR(
        const SemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo,    
        HANDLE* pHandle) {
        return vkGetSemaphoreWin32HandleKHR(get(), reinterpret_cast<const SemaphoreGetWin32HandleInfoKHR*>(pGetWin32HandleInfo), reinterpret_cast<HANDLE*>(pHandle));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult ImportSemaphoreWin32HandleKHR(
        const ImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) {
        return vkImportSemaphoreWin32HandleKHR(get(), reinterpret_cast<const ImportSemaphoreWin32HandleInfoKHR*>(pImportSemaphoreWin32HandleInfo));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    VkResult GetSemaphoreFdKHR(
        const SemaphoreGetFdInfoKHR* pGetFdInfo,    
        int* pFd) {
        return vkGetSemaphoreFdKHR(get(), reinterpret_cast<const SemaphoreGetFdInfoKHR*>(pGetFdInfo), reinterpret_cast<int*>(pFd));
    }
    VkResult ImportSemaphoreFdKHR(
        const ImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) {
        return vkImportSemaphoreFdKHR(get(), reinterpret_cast<const ImportSemaphoreFdInfoKHR*>(pImportSemaphoreFdInfo));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetFenceWin32HandleKHR(
        const FenceGetWin32HandleInfoKHR* pGetWin32HandleInfo,    
        HANDLE* pHandle) {
        return vkGetFenceWin32HandleKHR(get(), reinterpret_cast<const FenceGetWin32HandleInfoKHR*>(pGetWin32HandleInfo), reinterpret_cast<HANDLE*>(pHandle));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult ImportFenceWin32HandleKHR(
        const ImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) {
        return vkImportFenceWin32HandleKHR(get(), reinterpret_cast<const ImportFenceWin32HandleInfoKHR*>(pImportFenceWin32HandleInfo));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    VkResult GetFenceFdKHR(
        const FenceGetFdInfoKHR* pGetFdInfo,    
        int* pFd) {
        return vkGetFenceFdKHR(get(), reinterpret_cast<const FenceGetFdInfoKHR*>(pGetFdInfo), reinterpret_cast<int*>(pFd));
    }
    VkResult ImportFenceFdKHR(
        const ImportFenceFdInfoKHR* pImportFenceFdInfo) {
        return vkImportFenceFdKHR(get(), reinterpret_cast<const ImportFenceFdInfoKHR*>(pImportFenceFdInfo));
    }
    VkResult DisplayPowerControlEXT(
        DisplayKHR display,    
        const DisplayPowerInfoEXT* pDisplayPowerInfo) {
        return vkDisplayPowerControlEXT(get(),display.get(), reinterpret_cast<const DisplayPowerInfoEXT*>(pDisplayPowerInfo));
    }
    VkResult RegisterDeviceEventEXT(
        const DeviceEventInfoEXT* pDeviceEventInfo,    
        const AllocationCallbacks* pAllocator,    
        Fence* pFence) {
        return vkRegisterDeviceEventEXT(get(), reinterpret_cast<const DeviceEventInfoEXT*>(pDeviceEventInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Fence*>(pFence));
    }
    VkResult RegisterDisplayEventEXT(
        DisplayKHR display,    
        const DisplayEventInfoEXT* pDisplayEventInfo,    
        const AllocationCallbacks* pAllocator,    
        Fence* pFence) {
        return vkRegisterDisplayEventEXT(get(),display.get(), reinterpret_cast<const DisplayEventInfoEXT*>(pDisplayEventInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Fence*>(pFence));
    }
    VkResult GetSwapchainCounterEXT(
        SwapchainKHR swapchain,    
        SurfaceCounterFlagBitsEXT counter,    
        uint64_t* pCounterValue) {
        return vkGetSwapchainCounterEXT(get(),swapchain.get(), static_cast<SurfaceCounterFlagBitsEXT>(counter), reinterpret_cast<uint64_t*>(pCounterValue));
    }
    void GetDeviceGroupPeerMemoryFeatures(
        uint32_t heapIndex,    
        uint32_t localDeviceIndex,    
        uint32_t remoteDeviceIndex,    
        PeerMemoryFeatureFlags* pPeerMemoryFeatures) {
        return vkGetDeviceGroupPeerMemoryFeatures(get(), static_cast<uint32_t>(heapIndex), static_cast<uint32_t>(localDeviceIndex), static_cast<uint32_t>(remoteDeviceIndex), reinterpret_cast<PeerMemoryFeatureFlags*>(pPeerMemoryFeatures));
    }
    VkResult BindBufferMemory2(
        uint32_t bindInfoCount,    
        const BindBufferMemoryInfo* pBindInfos) {
        return vkBindBufferMemory2(get(), static_cast<uint32_t>(bindInfoCount), reinterpret_cast<const BindBufferMemoryInfo*>(pBindInfos));
    }
    VkResult BindImageMemory2(
        uint32_t bindInfoCount,    
        const BindImageMemoryInfo* pBindInfos) {
        return vkBindImageMemory2(get(), static_cast<uint32_t>(bindInfoCount), reinterpret_cast<const BindImageMemoryInfo*>(pBindInfos));
    }
    VkResult GetDeviceGroupPresentCapabilitiesKHR(
        DeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) {
        return vkGetDeviceGroupPresentCapabilitiesKHR(get(), reinterpret_cast<DeviceGroupPresentCapabilitiesKHR*>(pDeviceGroupPresentCapabilities));
    }
    VkResult GetDeviceGroupSurfacePresentModesKHR(
        SurfaceKHR surface,    
        DeviceGroupPresentModeFlagsKHR* pModes) {
        return vkGetDeviceGroupSurfacePresentModesKHR(get(),surface.get(), reinterpret_cast<DeviceGroupPresentModeFlagsKHR*>(pModes));
    }
    VkResult AcquireNextImage2KHR(
        const AcquireNextImageInfoKHR* pAcquireInfo,    
        uint32_t* pImageIndex) {
        return vkAcquireNextImage2KHR(get(), reinterpret_cast<const AcquireNextImageInfoKHR*>(pAcquireInfo), reinterpret_cast<uint32_t*>(pImageIndex));
    }
    VkResult CreateDescriptorUpdateTemplate(
        const DescriptorUpdateTemplateCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        DescriptorUpdateTemplate* pDescriptorUpdateTemplate) {
        return vkCreateDescriptorUpdateTemplate(get(), reinterpret_cast<const DescriptorUpdateTemplateCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DescriptorUpdateTemplate*>(pDescriptorUpdateTemplate));
    }
    void DestroyDescriptorUpdateTemplate(
        DescriptorUpdateTemplate descriptorUpdateTemplate,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDescriptorUpdateTemplate(get(),descriptorUpdateTemplate.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void UpdateDescriptorSetWithTemplate(
        DescriptorSet descriptorSet,    
        DescriptorUpdateTemplate descriptorUpdateTemplate,    
        const void* pData) {
        return vkUpdateDescriptorSetWithTemplate(get(),descriptorSet.get(),descriptorUpdateTemplate.get(), reinterpret_cast<const void*>(pData));
    }
    void SetHdrMetadataEXT(
        uint32_t swapchainCount,    
        const SwapchainKHR* pSwapchains,    
        const HdrMetadataEXT* pMetadata) {
        return vkSetHdrMetadataEXT(get(), static_cast<uint32_t>(swapchainCount), reinterpret_cast<const SwapchainKHR*>(pSwapchains), reinterpret_cast<const HdrMetadataEXT*>(pMetadata));
    }
    VkResult GetSwapchainStatusKHR(
        SwapchainKHR swapchain) {
        return vkGetSwapchainStatusKHR(get(),swapchain.get());
    }
    VkResult GetRefreshCycleDurationGOOGLE(
        SwapchainKHR swapchain,    
        RefreshCycleDurationGOOGLE* pDisplayTimingProperties) {
        return vkGetRefreshCycleDurationGOOGLE(get(),swapchain.get(), reinterpret_cast<RefreshCycleDurationGOOGLE*>(pDisplayTimingProperties));
    }
    VkResult GetPastPresentationTimingGOOGLE(
        SwapchainKHR swapchain,    
        uint32_t* pPresentationTimingCount,    
        PastPresentationTimingGOOGLE* pPresentationTimings) {
        return vkGetPastPresentationTimingGOOGLE(get(),swapchain.get(), reinterpret_cast<uint32_t*>(pPresentationTimingCount), reinterpret_cast<PastPresentationTimingGOOGLE*>(pPresentationTimings));
    }
    void GetBufferMemoryRequirements2(
        const BufferMemoryRequirementsInfo2* pInfo,    
        MemoryRequirements2* pMemoryRequirements) {
        return vkGetBufferMemoryRequirements2(get(), reinterpret_cast<const BufferMemoryRequirementsInfo2*>(pInfo), reinterpret_cast<MemoryRequirements2*>(pMemoryRequirements));
    }
    void GetImageMemoryRequirements2(
        const ImageMemoryRequirementsInfo2* pInfo,    
        MemoryRequirements2* pMemoryRequirements) {
        return vkGetImageMemoryRequirements2(get(), reinterpret_cast<const ImageMemoryRequirementsInfo2*>(pInfo), reinterpret_cast<MemoryRequirements2*>(pMemoryRequirements));
    }
    void GetImageSparseMemoryRequirements2(
        const ImageSparseMemoryRequirementsInfo2* pInfo,    
        uint32_t* pSparseMemoryRequirementCount,    
        SparseImageMemoryRequirements2* pSparseMemoryRequirements) {
        return vkGetImageSparseMemoryRequirements2(get(), reinterpret_cast<const ImageSparseMemoryRequirementsInfo2*>(pInfo), reinterpret_cast<uint32_t*>(pSparseMemoryRequirementCount), reinterpret_cast<SparseImageMemoryRequirements2*>(pSparseMemoryRequirements));
    }
    VkResult CreateSamplerYcbcrConversion(
        const SamplerYcbcrConversionCreateInfo* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        SamplerYcbcrConversion* pYcbcrConversion) {
        return vkCreateSamplerYcbcrConversion(get(), reinterpret_cast<const SamplerYcbcrConversionCreateInfo*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<SamplerYcbcrConversion*>(pYcbcrConversion));
    }
    void DestroySamplerYcbcrConversion(
        SamplerYcbcrConversion ycbcrConversion,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroySamplerYcbcrConversion(get(),ycbcrConversion.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void GetDeviceQueue2(
        const DeviceQueueInfo2* pQueueInfo,    
        Queue* pQueue) {
        return vkGetDeviceQueue2(get(), reinterpret_cast<const DeviceQueueInfo2*>(pQueueInfo), reinterpret_cast<Queue*>(pQueue));
    }
    VkResult CreateValidationCacheEXT(
        const ValidationCacheCreateInfoEXT* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        ValidationCacheEXT* pValidationCache) {
        return vkCreateValidationCacheEXT(get(), reinterpret_cast<const ValidationCacheCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<ValidationCacheEXT*>(pValidationCache));
    }
    void DestroyValidationCacheEXT(
        ValidationCacheEXT validationCache,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyValidationCacheEXT(get(),validationCache.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    VkResult GetValidationCacheDataEXT(
        ValidationCacheEXT validationCache,    
        size_t* pDataSize,    
        void* pData) {
        return vkGetValidationCacheDataEXT(get(),validationCache.get(), reinterpret_cast<size_t*>(pDataSize), reinterpret_cast<void*>(pData));
    }
    VkResult MergeValidationCachesEXT(
        ValidationCacheEXT dstCache,    
        uint32_t srcCacheCount,    
        const ValidationCacheEXT* pSrcCaches) {
        return vkMergeValidationCachesEXT(get(),dstCache.get(), static_cast<uint32_t>(srcCacheCount), reinterpret_cast<const ValidationCacheEXT*>(pSrcCaches));
    }
    void GetDescriptorSetLayoutSupport(
        const DescriptorSetLayoutCreateInfo* pCreateInfo,    
        DescriptorSetLayoutSupport* pSupport) {
        return vkGetDescriptorSetLayoutSupport(get(), reinterpret_cast<const DescriptorSetLayoutCreateInfo*>(pCreateInfo), reinterpret_cast<DescriptorSetLayoutSupport*>(pSupport));
    }
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult GetSwapchainGrallocUsageANDROID(
        Format format,    
        ImageUsageFlags imageUsage,    
        int* grallocUsage) {
        return vkGetSwapchainGrallocUsageANDROID(get(), static_cast<Format>(format), static_cast<ImageUsageFlags>(imageUsage), reinterpret_cast<int*>(grallocUsage));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult GetSwapchainGrallocUsage2ANDROID(
        Format format,    
        ImageUsageFlags imageUsage,    
        SwapchainImageUsageFlagsANDROID swapchainImageUsage,    
        uint64_t* grallocConsumerUsage,    
        uint64_t* grallocProducerUsage) {
        return vkGetSwapchainGrallocUsage2ANDROID(get(), static_cast<Format>(format), static_cast<ImageUsageFlags>(imageUsage), static_cast<SwapchainImageUsageFlagsANDROID>(swapchainImageUsage), reinterpret_cast<uint64_t*>(grallocConsumerUsage), reinterpret_cast<uint64_t*>(grallocProducerUsage));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult AcquireImageANDROID(
        Image image,    
        int nativeFenceFd,    
        Semaphore semaphore,    
        Fence fence) {
        return vkAcquireImageANDROID(get(),image.get(), static_cast<int>(nativeFenceFd),semaphore.get(),fence.get());
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
    VkResult GetShaderInfoAMD(
        Pipeline pipeline,    
        ShaderStageFlagBits shaderStage,    
        ShaderInfoTypeAMD infoType,    
        size_t* pInfoSize,    
        void* pInfo) {
        return vkGetShaderInfoAMD(get(),pipeline.get(), static_cast<ShaderStageFlagBits>(shaderStage), static_cast<ShaderInfoTypeAMD>(infoType), reinterpret_cast<size_t*>(pInfoSize), reinterpret_cast<void*>(pInfo));
    }
    void SetLocalDimmingAMD(
        SwapchainKHR swapChain,    
        bool localDimmingEnable) {
        return vkSetLocalDimmingAMD(get(),swapChain.get(), static_cast<bool>(localDimmingEnable));
    }
    VkResult GetCalibratedTimestampsEXT(
        uint32_t timestampCount,    
        const CalibratedTimestampInfoEXT* pTimestampInfos,    
        uint64_t* pTimestamps,    
        uint64_t* pMaxDeviation) {
        return vkGetCalibratedTimestampsEXT(get(), static_cast<uint32_t>(timestampCount), reinterpret_cast<const CalibratedTimestampInfoEXT*>(pTimestampInfos), reinterpret_cast<uint64_t*>(pTimestamps), reinterpret_cast<uint64_t*>(pMaxDeviation));
    }
    VkResult SetDebugUtilsObjectNameEXT(
        const DebugUtilsObjectNameInfoEXT* pNameInfo) {
        return vkSetDebugUtilsObjectNameEXT(get(), reinterpret_cast<const DebugUtilsObjectNameInfoEXT*>(pNameInfo));
    }
    VkResult SetDebugUtilsObjectTagEXT(
        const DebugUtilsObjectTagInfoEXT* pTagInfo) {
        return vkSetDebugUtilsObjectTagEXT(get(), reinterpret_cast<const DebugUtilsObjectTagInfoEXT*>(pTagInfo));
    }
    VkResult GetMemoryHostPointerPropertiesEXT(
        ExternalMemoryHandleTypeFlagBits handleType,    
        const void* pHostPointer,    
        MemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) {
        return vkGetMemoryHostPointerPropertiesEXT(get(), static_cast<ExternalMemoryHandleTypeFlagBits>(handleType), reinterpret_cast<const void*>(pHostPointer), reinterpret_cast<MemoryHostPointerPropertiesEXT*>(pMemoryHostPointerProperties));
    }
    VkResult CreateRenderPass2(
        const RenderPassCreateInfo2* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        RenderPass* pRenderPass) {
        return vkCreateRenderPass2(get(), reinterpret_cast<const RenderPassCreateInfo2*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<RenderPass*>(pRenderPass));
    }
    VkResult GetSemaphoreCounterValue(
        Semaphore semaphore,    
        uint64_t* pValue) {
        return vkGetSemaphoreCounterValue(get(),semaphore.get(), reinterpret_cast<uint64_t*>(pValue));
    }
    VkResult WaitSemaphores(
        const SemaphoreWaitInfo* pWaitInfo,    
        uint64_t timeout) {
        return vkWaitSemaphores(get(), reinterpret_cast<const SemaphoreWaitInfo*>(pWaitInfo), static_cast<uint64_t>(timeout));
    }
    VkResult SignalSemaphore(
        const SemaphoreSignalInfo* pSignalInfo) {
        return vkSignalSemaphore(get(), reinterpret_cast<const SemaphoreSignalInfo*>(pSignalInfo));
    }
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult GetAndroidHardwareBufferPropertiesANDROID(
        const AHardwareBuffer* buffer,    
        AndroidHardwareBufferPropertiesANDROID* pProperties) {
        return vkGetAndroidHardwareBufferPropertiesANDROID(get(), reinterpret_cast<const AHardwareBuffer*>(buffer), reinterpret_cast<AndroidHardwareBufferPropertiesANDROID*>(pProperties));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult GetMemoryAndroidHardwareBufferANDROID(
        const MemoryGetAndroidHardwareBufferInfoANDROID* pInfo,    
        AHardwareBuffer** pBuffer) {
        return vkGetMemoryAndroidHardwareBufferANDROID(get(), reinterpret_cast<const MemoryGetAndroidHardwareBufferInfoANDROID*>(pInfo), static_cast<AHardwareBuffer**>(pBuffer));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
    VkResult CompileDeferredNV(
        Pipeline pipeline,    
        uint32_t shader) {
        return vkCompileDeferredNV(get(),pipeline.get(), static_cast<uint32_t>(shader));
    }
    VkResult CreateAccelerationStructureNV(
        const AccelerationStructureCreateInfoNV* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        AccelerationStructureNV* pAccelerationStructure) {
        return vkCreateAccelerationStructureNV(get(), reinterpret_cast<const AccelerationStructureCreateInfoNV*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<AccelerationStructureNV*>(pAccelerationStructure));
    }
    void DestroyAccelerationStructureKHR(
        AccelerationStructureKHR accelerationStructure,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyAccelerationStructureKHR(get(),accelerationStructure.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    void GetAccelerationStructureMemoryRequirementsKHR(
        const AccelerationStructureMemoryRequirementsInfoKHR* pInfo,    
        MemoryRequirements2* pMemoryRequirements) {
        return vkGetAccelerationStructureMemoryRequirementsKHR(get(), reinterpret_cast<const AccelerationStructureMemoryRequirementsInfoKHR*>(pInfo), reinterpret_cast<MemoryRequirements2*>(pMemoryRequirements));
    }
    void GetAccelerationStructureMemoryRequirementsNV(
        const AccelerationStructureMemoryRequirementsInfoNV* pInfo,    
        MemoryRequirements2KHR* pMemoryRequirements) {
        return vkGetAccelerationStructureMemoryRequirementsNV(get(), reinterpret_cast<const AccelerationStructureMemoryRequirementsInfoNV*>(pInfo), reinterpret_cast<MemoryRequirements2KHR*>(pMemoryRequirements));
    }
    VkResult BindAccelerationStructureMemoryKHR(
        uint32_t bindInfoCount,    
        const BindAccelerationStructureMemoryInfoKHR* pBindInfos) {
        return vkBindAccelerationStructureMemoryKHR(get(), static_cast<uint32_t>(bindInfoCount), reinterpret_cast<const BindAccelerationStructureMemoryInfoKHR*>(pBindInfos));
    }
    VkResult CopyAccelerationStructureKHR(
        const CopyAccelerationStructureInfoKHR* pInfo) {
        return vkCopyAccelerationStructureKHR(get(), reinterpret_cast<const CopyAccelerationStructureInfoKHR*>(pInfo));
    }
    VkResult CopyAccelerationStructureToMemoryKHR(
        const CopyAccelerationStructureToMemoryInfoKHR* pInfo) {
        return vkCopyAccelerationStructureToMemoryKHR(get(), reinterpret_cast<const CopyAccelerationStructureToMemoryInfoKHR*>(pInfo));
    }
    VkResult CopyMemoryToAccelerationStructureKHR(
        const CopyMemoryToAccelerationStructureInfoKHR* pInfo) {
        return vkCopyMemoryToAccelerationStructureKHR(get(), reinterpret_cast<const CopyMemoryToAccelerationStructureInfoKHR*>(pInfo));
    }
    VkResult WriteAccelerationStructuresPropertiesKHR(
        uint32_t accelerationStructureCount,    
        const AccelerationStructureKHR* pAccelerationStructures,    
        QueryType queryType,    
        size_t dataSize,    
        void* pData,    
        size_t stride) {
        return vkWriteAccelerationStructuresPropertiesKHR(get(), static_cast<uint32_t>(accelerationStructureCount), reinterpret_cast<const AccelerationStructureKHR*>(pAccelerationStructures), static_cast<QueryType>(queryType), static_cast<size_t>(dataSize), reinterpret_cast<void*>(pData), static_cast<size_t>(stride));
    }
    VkResult GetRayTracingShaderGroupHandlesKHR(
        Pipeline pipeline,    
        uint32_t firstGroup,    
        uint32_t groupCount,    
        size_t dataSize,    
        void* pData) {
        return vkGetRayTracingShaderGroupHandlesKHR(get(),pipeline.get(), static_cast<uint32_t>(firstGroup), static_cast<uint32_t>(groupCount), static_cast<size_t>(dataSize), reinterpret_cast<void*>(pData));
    }
    VkResult GetRayTracingCaptureReplayShaderGroupHandlesKHR(
        Pipeline pipeline,    
        uint32_t firstGroup,    
        uint32_t groupCount,    
        size_t dataSize,    
        void* pData) {
        return vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(get(),pipeline.get(), static_cast<uint32_t>(firstGroup), static_cast<uint32_t>(groupCount), static_cast<size_t>(dataSize), reinterpret_cast<void*>(pData));
    }
    VkResult GetAccelerationStructureHandleNV(
        AccelerationStructureKHR accelerationStructure,    
        size_t dataSize,    
        void* pData) {
        return vkGetAccelerationStructureHandleNV(get(),accelerationStructure.get(), static_cast<size_t>(dataSize), reinterpret_cast<void*>(pData));
    }
    VkResult CreateRayTracingPipelinesNV(
        PipelineCache pipelineCache,    
        uint32_t createInfoCount,    
        const RayTracingPipelineCreateInfoNV* pCreateInfos,    
        const AllocationCallbacks* pAllocator,    
        Pipeline* pPipelines) {
        return vkCreateRayTracingPipelinesNV(get(),pipelineCache.get(), static_cast<uint32_t>(createInfoCount), reinterpret_cast<const RayTracingPipelineCreateInfoNV*>(pCreateInfos), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Pipeline*>(pPipelines));
    }
    VkResult CreateRayTracingPipelinesKHR(
        PipelineCache pipelineCache,    
        uint32_t createInfoCount,    
        const RayTracingPipelineCreateInfoKHR* pCreateInfos,    
        const AllocationCallbacks* pAllocator,    
        Pipeline* pPipelines) {
        return vkCreateRayTracingPipelinesKHR(get(),pipelineCache.get(), static_cast<uint32_t>(createInfoCount), reinterpret_cast<const RayTracingPipelineCreateInfoKHR*>(pCreateInfos), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<Pipeline*>(pPipelines));
    }
    VkResult GetDeviceAccelerationStructureCompatibilityKHR(
        const AccelerationStructureVersionKHR* version) {
        return vkGetDeviceAccelerationStructureCompatibilityKHR(get(), reinterpret_cast<const AccelerationStructureVersionKHR*>(version));
    }
    uint32_t GetImageViewHandleNVX(
        const ImageViewHandleInfoNVX* pInfo) {
        return vkGetImageViewHandleNVX(get(), reinterpret_cast<const ImageViewHandleInfoNVX*>(pInfo));
    }
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult GetDeviceGroupSurfacePresentModes2EXT(
        const PhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo,    
        DeviceGroupPresentModeFlagsKHR* pModes) {
        return vkGetDeviceGroupSurfacePresentModes2EXT(get(), reinterpret_cast<const PhysicalDeviceSurfaceInfo2KHR*>(pSurfaceInfo), reinterpret_cast<DeviceGroupPresentModeFlagsKHR*>(pModes));
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult AcquireFullScreenExclusiveModeEXT(
        SwapchainKHR swapchain) {
        return vkAcquireFullScreenExclusiveModeEXT(get(),swapchain.get());
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkResult ReleaseFullScreenExclusiveModeEXT(
        SwapchainKHR swapchain) {
        return vkReleaseFullScreenExclusiveModeEXT(get(),swapchain.get());
    }
#endif // VK_USE_PLATFORM_WIN32_KHR
    VkResult AcquireProfilingLockKHR(
        const AcquireProfilingLockInfoKHR* pInfo) {
        return vkAcquireProfilingLockKHR(get(), reinterpret_cast<const AcquireProfilingLockInfoKHR*>(pInfo));
    }
    void ReleaseProfilingLockKHR() {
        return vkReleaseProfilingLockKHR(get());
    }
    VkResult GetImageDrmFormatModifierPropertiesEXT(
        Image image,    
        ImageDrmFormatModifierPropertiesEXT* pProperties) {
        return vkGetImageDrmFormatModifierPropertiesEXT(get(),image.get(), reinterpret_cast<ImageDrmFormatModifierPropertiesEXT*>(pProperties));
    }
    uint64_t GetBufferOpaqueCaptureAddress(
        const BufferDeviceAddressInfo* pInfo) {
        return vkGetBufferOpaqueCaptureAddress(get(), reinterpret_cast<const BufferDeviceAddressInfo*>(pInfo));
    }
    VkDeviceAddress GetBufferDeviceAddress(
        const BufferDeviceAddressInfo* pInfo) {
        return vkGetBufferDeviceAddress(get(), reinterpret_cast<const BufferDeviceAddressInfo*>(pInfo));
    }
    VkResult InitializePerformanceApiINTEL(
        const InitializePerformanceApiInfoINTEL* pInitializeInfo) {
        return vkInitializePerformanceApiINTEL(get(), reinterpret_cast<const InitializePerformanceApiInfoINTEL*>(pInitializeInfo));
    }
    void UninitializePerformanceApiINTEL() {
        return vkUninitializePerformanceApiINTEL(get());
    }
    VkResult AcquirePerformanceConfigurationINTEL(
        const PerformanceConfigurationAcquireInfoINTEL* pAcquireInfo,    
        PerformanceConfigurationINTEL* pConfiguration) {
        return vkAcquirePerformanceConfigurationINTEL(get(), reinterpret_cast<const PerformanceConfigurationAcquireInfoINTEL*>(pAcquireInfo), reinterpret_cast<PerformanceConfigurationINTEL*>(pConfiguration));
    }
    VkResult ReleasePerformanceConfigurationINTEL(
        PerformanceConfigurationINTEL configuration) {
        return vkReleasePerformanceConfigurationINTEL(get(),configuration.get());
    }
    VkResult GetPerformanceParameterINTEL(
        PerformanceParameterTypeINTEL parameter,    
        PerformanceValueINTEL* pValue) {
        return vkGetPerformanceParameterINTEL(get(), static_cast<PerformanceParameterTypeINTEL>(parameter), reinterpret_cast<PerformanceValueINTEL*>(pValue));
    }
    uint64_t GetDeviceMemoryOpaqueCaptureAddress(
        const DeviceMemoryOpaqueCaptureAddressInfo* pInfo) {
        return vkGetDeviceMemoryOpaqueCaptureAddress(get(), reinterpret_cast<const DeviceMemoryOpaqueCaptureAddressInfo*>(pInfo));
    }
    VkResult GetPipelineExecutablePropertiesKHR(
        const PipelineInfoKHR* pPipelineInfo,    
        uint32_t* pExecutableCount,    
        PipelineExecutablePropertiesKHR* pProperties) {
        return vkGetPipelineExecutablePropertiesKHR(get(), reinterpret_cast<const PipelineInfoKHR*>(pPipelineInfo), reinterpret_cast<uint32_t*>(pExecutableCount), reinterpret_cast<PipelineExecutablePropertiesKHR*>(pProperties));
    }
    VkResult GetPipelineExecutableStatisticsKHR(
        const PipelineExecutableInfoKHR* pExecutableInfo,    
        uint32_t* pStatisticCount,    
        PipelineExecutableStatisticKHR* pStatistics) {
        return vkGetPipelineExecutableStatisticsKHR(get(), reinterpret_cast<const PipelineExecutableInfoKHR*>(pExecutableInfo), reinterpret_cast<uint32_t*>(pStatisticCount), reinterpret_cast<PipelineExecutableStatisticKHR*>(pStatistics));
    }
    VkResult GetPipelineExecutableInternalRepresentationsKHR(
        const PipelineExecutableInfoKHR* pExecutableInfo,    
        uint32_t* pInternalRepresentationCount,    
        PipelineExecutableInternalRepresentationKHR* pInternalRepresentations) {
        return vkGetPipelineExecutableInternalRepresentationsKHR(get(), reinterpret_cast<const PipelineExecutableInfoKHR*>(pExecutableInfo), reinterpret_cast<uint32_t*>(pInternalRepresentationCount), reinterpret_cast<PipelineExecutableInternalRepresentationKHR*>(pInternalRepresentations));
    }
    VkResult CreateAccelerationStructureKHR(
        const AccelerationStructureCreateInfoKHR* pCreateInfo,    
        const AllocationCallbacks* pAllocator,    
        AccelerationStructureKHR* pAccelerationStructure) {
        return vkCreateAccelerationStructureKHR(get(), reinterpret_cast<const AccelerationStructureCreateInfoKHR*>(pCreateInfo), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<AccelerationStructureKHR*>(pAccelerationStructure));
    }
    VkResult BuildAccelerationStructureKHR(
        uint32_t infoCount,    
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,    
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return vkBuildAccelerationStructureKHR(get(), static_cast<uint32_t>(infoCount), reinterpret_cast<const AccelerationStructureBuildGeometryInfoKHR*>(pInfos), reinterpret_cast<const AccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    VkDeviceAddress GetAccelerationStructureDeviceAddressKHR(
        const AccelerationStructureDeviceAddressInfoKHR* pInfo) {
        return vkGetAccelerationStructureDeviceAddressKHR(get(), reinterpret_cast<const AccelerationStructureDeviceAddressInfoKHR*>(pInfo));
    }
    VkResult CreateDeferredOperationKHR(
        const AllocationCallbacks* pAllocator,    
        DeferredOperationKHR* pDeferredOperation) {
        return vkCreateDeferredOperationKHR(get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator), reinterpret_cast<DeferredOperationKHR*>(pDeferredOperation));
    }
    void DestroyDeferredOperationKHR(
        DeferredOperationKHR operation,    
        const AllocationCallbacks* pAllocator) {
        return vkDestroyDeferredOperationKHR(get(),operation.get(), reinterpret_cast<const AllocationCallbacks*>(pAllocator));
    }
    uint32_t GetDeferredOperationMaxConcurrencyKHR(
        DeferredOperationKHR operation) {
        return vkGetDeferredOperationMaxConcurrencyKHR(get(),operation.get());
    }
    VkResult GetDeferredOperationResultKHR(
        DeferredOperationKHR operation) {
        return vkGetDeferredOperationResultKHR(get(),operation.get());
    }
    VkResult DeferredOperationJoinKHR(
        DeferredOperationKHR operation) {
        return vkDeferredOperationJoinKHR(get(),operation.get());
    }
};
struct Queue {
    VkQueue handle;
    VkQueue get() { return handle; }
    VkResult QueueSubmit(
        uint32_t submitCount,    
        const SubmitInfo* pSubmits,    
        Fence fence) {
        return vkQueueSubmit(get(), static_cast<uint32_t>(submitCount), reinterpret_cast<const SubmitInfo*>(pSubmits),fence.get());
    }
    VkResult QueueWaitIdle() {
        return vkQueueWaitIdle(get());
    }
    VkResult QueueBindSparse(
        uint32_t bindInfoCount,    
        const BindSparseInfo* pBindInfo,    
        Fence fence) {
        return vkQueueBindSparse(get(), static_cast<uint32_t>(bindInfoCount), reinterpret_cast<const BindSparseInfo*>(pBindInfo),fence.get());
    }
    VkResult QueuePresentKHR(
        const PresentInfoKHR* pPresentInfo) {
        return vkQueuePresentKHR(get(), reinterpret_cast<const PresentInfoKHR*>(pPresentInfo));
    }
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkResult QueueSignalReleaseImageANDROID(
        uint32_t waitSemaphoreCount,    
        const Semaphore* pWaitSemaphores,    
        Image image,    
        int* pNativeFenceFd) {
        return vkQueueSignalReleaseImageANDROID(get(), static_cast<uint32_t>(waitSemaphoreCount), reinterpret_cast<const Semaphore*>(pWaitSemaphores),image.get(), reinterpret_cast<int*>(pNativeFenceFd));
    }
#endif // VK_USE_PLATFORM_ANDROID_KHR
    void QueueBeginDebugUtilsLabelEXT(
        const DebugUtilsLabelEXT* pLabelInfo) {
        return vkQueueBeginDebugUtilsLabelEXT(get(), reinterpret_cast<const DebugUtilsLabelEXT*>(pLabelInfo));
    }
    void QueueEndDebugUtilsLabelEXT() {
        return vkQueueEndDebugUtilsLabelEXT(get());
    }
    void QueueInsertDebugUtilsLabelEXT(
        const DebugUtilsLabelEXT* pLabelInfo) {
        return vkQueueInsertDebugUtilsLabelEXT(get(), reinterpret_cast<const DebugUtilsLabelEXT*>(pLabelInfo));
    }
    void GetQueueCheckpointDataNV(
        uint32_t* pCheckpointDataCount,    
        CheckpointDataNV* pCheckpointData) {
        return vkGetQueueCheckpointDataNV(get(), reinterpret_cast<uint32_t*>(pCheckpointDataCount), reinterpret_cast<CheckpointDataNV*>(pCheckpointData));
    }
    VkResult QueueSetPerformanceConfigurationINTEL(
        PerformanceConfigurationINTEL configuration) {
        return vkQueueSetPerformanceConfigurationINTEL(get(),configuration.get());
    }
};
struct CommandBuffer {
    VkCommandBuffer handle;
    VkCommandBuffer get() { return handle; }
    VkResult BeginCommandBuffer(
        const CommandBufferBeginInfo* pBeginInfo) {
        return vkBeginCommandBuffer(get(), reinterpret_cast<const CommandBufferBeginInfo*>(pBeginInfo));
    }
    VkResult EndCommandBuffer() {
        return vkEndCommandBuffer(get());
    }
    VkResult ResetCommandBuffer(
        CommandBufferResetFlags flags) {
        return vkResetCommandBuffer(get(), static_cast<CommandBufferResetFlags>(flags));
    }
    void CmdBindPipeline(
        PipelineBindPoint pipelineBindPoint,    
        Pipeline pipeline) {
        return vkCmdBindPipeline(get(), static_cast<PipelineBindPoint>(pipelineBindPoint),pipeline.get());
    }
    void CmdSetViewport(
        uint32_t firstViewport,    
        uint32_t viewportCount,    
        const Viewport* pViewports) {
        return vkCmdSetViewport(get(), static_cast<uint32_t>(firstViewport), static_cast<uint32_t>(viewportCount), reinterpret_cast<const Viewport*>(pViewports));
    }
    void CmdSetScissor(
        uint32_t firstScissor,    
        uint32_t scissorCount,    
        const Rect2D* pScissors) {
        return vkCmdSetScissor(get(), static_cast<uint32_t>(firstScissor), static_cast<uint32_t>(scissorCount), reinterpret_cast<const Rect2D*>(pScissors));
    }
    void CmdSetLineWidth(
        float lineWidth) {
        return vkCmdSetLineWidth(get(), static_cast<float>(lineWidth));
    }
    void CmdSetDepthBias(
        float depthBiasConstantFactor,    
        float depthBiasClamp,    
        float depthBiasSlopeFactor) {
        return vkCmdSetDepthBias(get(), static_cast<float>(depthBiasConstantFactor), static_cast<float>(depthBiasClamp), static_cast<float>(depthBiasSlopeFactor));
    }
    void CmdSetBlendConstants(
        const float blendConstants[4]) {
        return vkCmdSetBlendConstants(get(), static_cast<const float[4]>(blendConstants));
    }
    void CmdSetDepthBounds(
        float minDepthBounds,    
        float maxDepthBounds) {
        return vkCmdSetDepthBounds(get(), static_cast<float>(minDepthBounds), static_cast<float>(maxDepthBounds));
    }
    void CmdSetStencilCompareMask(
        StencilFaceFlags faceMask,    
        uint32_t compareMask) {
        return vkCmdSetStencilCompareMask(get(), static_cast<StencilFaceFlags>(faceMask), static_cast<uint32_t>(compareMask));
    }
    void CmdSetStencilWriteMask(
        StencilFaceFlags faceMask,    
        uint32_t writeMask) {
        return vkCmdSetStencilWriteMask(get(), static_cast<StencilFaceFlags>(faceMask), static_cast<uint32_t>(writeMask));
    }
    void CmdSetStencilReference(
        StencilFaceFlags faceMask,    
        uint32_t reference) {
        return vkCmdSetStencilReference(get(), static_cast<StencilFaceFlags>(faceMask), static_cast<uint32_t>(reference));
    }
    void CmdBindDescriptorSets(
        PipelineBindPoint pipelineBindPoint,    
        PipelineLayout layout,    
        uint32_t firstSet,    
        uint32_t descriptorSetCount,    
        const DescriptorSet* pDescriptorSets,    
        uint32_t dynamicOffsetCount,    
        const uint32_t* pDynamicOffsets) {
        return vkCmdBindDescriptorSets(get(), static_cast<PipelineBindPoint>(pipelineBindPoint),layout.get(), static_cast<uint32_t>(firstSet), static_cast<uint32_t>(descriptorSetCount), reinterpret_cast<const DescriptorSet*>(pDescriptorSets), static_cast<uint32_t>(dynamicOffsetCount), reinterpret_cast<const uint32_t*>(pDynamicOffsets));
    }
    void CmdBindIndexBuffer(
        Buffer buffer,    
        DeviceSize offset,    
        IndexType indexType) {
        return vkCmdBindIndexBuffer(get(),buffer.get(), static_cast<DeviceSize>(offset), static_cast<IndexType>(indexType));
    }
    void CmdBindVertexBuffers(
        uint32_t firstBinding,    
        uint32_t bindingCount,    
        const Buffer* pBuffers,    
        const DeviceSize* pOffsets) {
        return vkCmdBindVertexBuffers(get(), static_cast<uint32_t>(firstBinding), static_cast<uint32_t>(bindingCount), reinterpret_cast<const Buffer*>(pBuffers), reinterpret_cast<const DeviceSize*>(pOffsets));
    }
    void CmdDraw(
        uint32_t vertexCount,    
        uint32_t instanceCount,    
        uint32_t firstVertex,    
        uint32_t firstInstance) {
        return vkCmdDraw(get(), static_cast<uint32_t>(vertexCount), static_cast<uint32_t>(instanceCount), static_cast<uint32_t>(firstVertex), static_cast<uint32_t>(firstInstance));
    }
    void CmdDrawIndexed(
        uint32_t indexCount,    
        uint32_t instanceCount,    
        uint32_t firstIndex,    
        int32_t vertexOffset,    
        uint32_t firstInstance) {
        return vkCmdDrawIndexed(get(), static_cast<uint32_t>(indexCount), static_cast<uint32_t>(instanceCount), static_cast<uint32_t>(firstIndex), static_cast<int32_t>(vertexOffset), static_cast<uint32_t>(firstInstance));
    }
    void CmdDrawIndirect(
        Buffer buffer,    
        DeviceSize offset,    
        uint32_t drawCount,    
        uint32_t stride) {
        return vkCmdDrawIndirect(get(),buffer.get(), static_cast<DeviceSize>(offset), static_cast<uint32_t>(drawCount), static_cast<uint32_t>(stride));
    }
    void CmdDrawIndexedIndirect(
        Buffer buffer,    
        DeviceSize offset,    
        uint32_t drawCount,    
        uint32_t stride) {
        return vkCmdDrawIndexedIndirect(get(),buffer.get(), static_cast<DeviceSize>(offset), static_cast<uint32_t>(drawCount), static_cast<uint32_t>(stride));
    }
    void CmdDispatch(
        uint32_t groupCountX,    
        uint32_t groupCountY,    
        uint32_t groupCountZ) {
        return vkCmdDispatch(get(), static_cast<uint32_t>(groupCountX), static_cast<uint32_t>(groupCountY), static_cast<uint32_t>(groupCountZ));
    }
    void CmdDispatchIndirect(
        Buffer buffer,    
        DeviceSize offset) {
        return vkCmdDispatchIndirect(get(),buffer.get(), static_cast<DeviceSize>(offset));
    }
    void CmdCopyBuffer(
        Buffer srcBuffer,    
        Buffer dstBuffer,    
        uint32_t regionCount,    
        const BufferCopy* pRegions) {
        return vkCmdCopyBuffer(get(),srcBuffer.get(),dstBuffer.get(), static_cast<uint32_t>(regionCount), reinterpret_cast<const BufferCopy*>(pRegions));
    }
    void CmdCopyImage(
        Image srcImage,    
        ImageLayout srcImageLayout,    
        Image dstImage,    
        ImageLayout dstImageLayout,    
        uint32_t regionCount,    
        const ImageCopy* pRegions) {
        return vkCmdCopyImage(get(),srcImage.get(), static_cast<ImageLayout>(srcImageLayout),dstImage.get(), static_cast<ImageLayout>(dstImageLayout), static_cast<uint32_t>(regionCount), reinterpret_cast<const ImageCopy*>(pRegions));
    }
    void CmdBlitImage(
        Image srcImage,    
        ImageLayout srcImageLayout,    
        Image dstImage,    
        ImageLayout dstImageLayout,    
        uint32_t regionCount,    
        const ImageBlit* pRegions,    
        Filter filter) {
        return vkCmdBlitImage(get(),srcImage.get(), static_cast<ImageLayout>(srcImageLayout),dstImage.get(), static_cast<ImageLayout>(dstImageLayout), static_cast<uint32_t>(regionCount), reinterpret_cast<const ImageBlit*>(pRegions), static_cast<Filter>(filter));
    }
    void CmdCopyBufferToImage(
        Buffer srcBuffer,    
        Image dstImage,    
        ImageLayout dstImageLayout,    
        uint32_t regionCount,    
        const BufferImageCopy* pRegions) {
        return vkCmdCopyBufferToImage(get(),srcBuffer.get(),dstImage.get(), static_cast<ImageLayout>(dstImageLayout), static_cast<uint32_t>(regionCount), reinterpret_cast<const BufferImageCopy*>(pRegions));
    }
    void CmdCopyImageToBuffer(
        Image srcImage,    
        ImageLayout srcImageLayout,    
        Buffer dstBuffer,    
        uint32_t regionCount,    
        const BufferImageCopy* pRegions) {
        return vkCmdCopyImageToBuffer(get(),srcImage.get(), static_cast<ImageLayout>(srcImageLayout),dstBuffer.get(), static_cast<uint32_t>(regionCount), reinterpret_cast<const BufferImageCopy*>(pRegions));
    }
    void CmdUpdateBuffer(
        Buffer dstBuffer,    
        DeviceSize dstOffset,    
        DeviceSize dataSize,    
        const void* pData) {
        return vkCmdUpdateBuffer(get(),dstBuffer.get(), static_cast<DeviceSize>(dstOffset), static_cast<DeviceSize>(dataSize), reinterpret_cast<const void*>(pData));
    }
    void CmdFillBuffer(
        Buffer dstBuffer,    
        DeviceSize dstOffset,    
        DeviceSize size,    
        uint32_t data) {
        return vkCmdFillBuffer(get(),dstBuffer.get(), static_cast<DeviceSize>(dstOffset), static_cast<DeviceSize>(size), static_cast<uint32_t>(data));
    }
    void CmdClearColorImage(
        Image image,    
        ImageLayout imageLayout,    
        const ClearColorValue* pColor,    
        uint32_t rangeCount,    
        const ImageSubresourceRange* pRanges) {
        return vkCmdClearColorImage(get(),image.get(), static_cast<ImageLayout>(imageLayout), reinterpret_cast<const ClearColorValue*>(pColor), static_cast<uint32_t>(rangeCount), reinterpret_cast<const ImageSubresourceRange*>(pRanges));
    }
    void CmdClearDepthStencilImage(
        Image image,    
        ImageLayout imageLayout,    
        const ClearDepthStencilValue* pDepthStencil,    
        uint32_t rangeCount,    
        const ImageSubresourceRange* pRanges) {
        return vkCmdClearDepthStencilImage(get(),image.get(), static_cast<ImageLayout>(imageLayout), reinterpret_cast<const ClearDepthStencilValue*>(pDepthStencil), static_cast<uint32_t>(rangeCount), reinterpret_cast<const ImageSubresourceRange*>(pRanges));
    }
    void CmdClearAttachments(
        uint32_t attachmentCount,    
        const ClearAttachment* pAttachments,    
        uint32_t rectCount,    
        const ClearRect* pRects) {
        return vkCmdClearAttachments(get(), static_cast<uint32_t>(attachmentCount), reinterpret_cast<const ClearAttachment*>(pAttachments), static_cast<uint32_t>(rectCount), reinterpret_cast<const ClearRect*>(pRects));
    }
    void CmdResolveImage(
        Image srcImage,    
        ImageLayout srcImageLayout,    
        Image dstImage,    
        ImageLayout dstImageLayout,    
        uint32_t regionCount,    
        const ImageResolve* pRegions) {
        return vkCmdResolveImage(get(),srcImage.get(), static_cast<ImageLayout>(srcImageLayout),dstImage.get(), static_cast<ImageLayout>(dstImageLayout), static_cast<uint32_t>(regionCount), reinterpret_cast<const ImageResolve*>(pRegions));
    }
    void CmdSetEvent(
        Event event,    
        PipelineStageFlags stageMask) {
        return vkCmdSetEvent(get(),event.get(), static_cast<PipelineStageFlags>(stageMask));
    }
    void CmdResetEvent(
        Event event,    
        PipelineStageFlags stageMask) {
        return vkCmdResetEvent(get(),event.get(), static_cast<PipelineStageFlags>(stageMask));
    }
    void CmdWaitEvents(
        uint32_t eventCount,    
        const Event* pEvents,    
        PipelineStageFlags srcStageMask,    
        PipelineStageFlags dstStageMask,    
        uint32_t memoryBarrierCount,    
        const MemoryBarrier* pMemoryBarriers,    
        uint32_t bufferMemoryBarrierCount,    
        const BufferMemoryBarrier* pBufferMemoryBarriers,    
        uint32_t imageMemoryBarrierCount,    
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return vkCmdWaitEvents(get(), static_cast<uint32_t>(eventCount), reinterpret_cast<const Event*>(pEvents), static_cast<PipelineStageFlags>(srcStageMask), static_cast<PipelineStageFlags>(dstStageMask), static_cast<uint32_t>(memoryBarrierCount), reinterpret_cast<const MemoryBarrier*>(pMemoryBarriers), static_cast<uint32_t>(bufferMemoryBarrierCount), reinterpret_cast<const BufferMemoryBarrier*>(pBufferMemoryBarriers), static_cast<uint32_t>(imageMemoryBarrierCount), reinterpret_cast<const ImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void CmdPipelineBarrier(
        PipelineStageFlags srcStageMask,    
        PipelineStageFlags dstStageMask,    
        DependencyFlags dependencyFlags,    
        uint32_t memoryBarrierCount,    
        const MemoryBarrier* pMemoryBarriers,    
        uint32_t bufferMemoryBarrierCount,    
        const BufferMemoryBarrier* pBufferMemoryBarriers,    
        uint32_t imageMemoryBarrierCount,    
        const ImageMemoryBarrier* pImageMemoryBarriers) {
        return vkCmdPipelineBarrier(get(), static_cast<PipelineStageFlags>(srcStageMask), static_cast<PipelineStageFlags>(dstStageMask), static_cast<DependencyFlags>(dependencyFlags), static_cast<uint32_t>(memoryBarrierCount), reinterpret_cast<const MemoryBarrier*>(pMemoryBarriers), static_cast<uint32_t>(bufferMemoryBarrierCount), reinterpret_cast<const BufferMemoryBarrier*>(pBufferMemoryBarriers), static_cast<uint32_t>(imageMemoryBarrierCount), reinterpret_cast<const ImageMemoryBarrier*>(pImageMemoryBarriers));
    }
    void CmdBeginQuery(
        QueryPool queryPool,    
        uint32_t query,    
        QueryControlFlags flags) {
        return vkCmdBeginQuery(get(),queryPool.get(), static_cast<uint32_t>(query), static_cast<QueryControlFlags>(flags));
    }
    void CmdEndQuery(
        QueryPool queryPool,    
        uint32_t query) {
        return vkCmdEndQuery(get(),queryPool.get(), static_cast<uint32_t>(query));
    }
    void CmdBeginConditionalRenderingEXT(
        const ConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) {
        return vkCmdBeginConditionalRenderingEXT(get(), reinterpret_cast<const ConditionalRenderingBeginInfoEXT*>(pConditionalRenderingBegin));
    }
    void CmdEndConditionalRenderingEXT() {
        return vkCmdEndConditionalRenderingEXT(get());
    }
    void CmdResetQueryPool(
        QueryPool queryPool,    
        uint32_t firstQuery,    
        uint32_t queryCount) {
        return vkCmdResetQueryPool(get(),queryPool.get(), static_cast<uint32_t>(firstQuery), static_cast<uint32_t>(queryCount));
    }
    void CmdWriteTimestamp(
        PipelineStageFlagBits pipelineStage,    
        QueryPool queryPool,    
        uint32_t query) {
        return vkCmdWriteTimestamp(get(), static_cast<PipelineStageFlagBits>(pipelineStage),queryPool.get(), static_cast<uint32_t>(query));
    }
    void CmdCopyQueryPoolResults(
        QueryPool queryPool,    
        uint32_t firstQuery,    
        uint32_t queryCount,    
        Buffer dstBuffer,    
        DeviceSize dstOffset,    
        DeviceSize stride,    
        QueryResultFlags flags) {
        return vkCmdCopyQueryPoolResults(get(),queryPool.get(), static_cast<uint32_t>(firstQuery), static_cast<uint32_t>(queryCount),dstBuffer.get(), static_cast<DeviceSize>(dstOffset), static_cast<DeviceSize>(stride), static_cast<QueryResultFlags>(flags));
    }
    void CmdPushConstants(
        PipelineLayout layout,    
        ShaderStageFlags stageFlags,    
        uint32_t offset,    
        uint32_t size,    
        const void* pValues) {
        return vkCmdPushConstants(get(),layout.get(), static_cast<ShaderStageFlags>(stageFlags), static_cast<uint32_t>(offset), static_cast<uint32_t>(size), reinterpret_cast<const void*>(pValues));
    }
    void CmdBeginRenderPass(
        const RenderPassBeginInfo* pRenderPassBegin,    
        SubpassContents contents) {
        return vkCmdBeginRenderPass(get(), reinterpret_cast<const RenderPassBeginInfo*>(pRenderPassBegin), static_cast<SubpassContents>(contents));
    }
    void CmdNextSubpass(
        SubpassContents contents) {
        return vkCmdNextSubpass(get(), static_cast<SubpassContents>(contents));
    }
    void CmdEndRenderPass() {
        return vkCmdEndRenderPass(get());
    }
    void CmdExecuteCommands(
        uint32_t commandBufferCount,    
        const CommandBuffer* pCommandBuffers) {
        return vkCmdExecuteCommands(get(), static_cast<uint32_t>(commandBufferCount), reinterpret_cast<const CommandBuffer*>(pCommandBuffers));
    }
    void CmdDebugMarkerBeginEXT(
        const DebugMarkerMarkerInfoEXT* pMarkerInfo) {
        return vkCmdDebugMarkerBeginEXT(get(), reinterpret_cast<const DebugMarkerMarkerInfoEXT*>(pMarkerInfo));
    }
    void CmdDebugMarkerEndEXT() {
        return vkCmdDebugMarkerEndEXT(get());
    }
    void CmdDebugMarkerInsertEXT(
        const DebugMarkerMarkerInfoEXT* pMarkerInfo) {
        return vkCmdDebugMarkerInsertEXT(get(), reinterpret_cast<const DebugMarkerMarkerInfoEXT*>(pMarkerInfo));
    }
    void CmdExecuteGeneratedCommandsNV(
        bool isPreprocessed,    
        const GeneratedCommandsInfoNV* pGeneratedCommandsInfo) {
        return vkCmdExecuteGeneratedCommandsNV(get(), static_cast<bool>(isPreprocessed), reinterpret_cast<const GeneratedCommandsInfoNV*>(pGeneratedCommandsInfo));
    }
    void CmdPreprocessGeneratedCommandsNV(
        const GeneratedCommandsInfoNV* pGeneratedCommandsInfo) {
        return vkCmdPreprocessGeneratedCommandsNV(get(), reinterpret_cast<const GeneratedCommandsInfoNV*>(pGeneratedCommandsInfo));
    }
    void CmdBindPipelineShaderGroupNV(
        PipelineBindPoint pipelineBindPoint,    
        Pipeline pipeline,    
        uint32_t groupIndex) {
        return vkCmdBindPipelineShaderGroupNV(get(), static_cast<PipelineBindPoint>(pipelineBindPoint),pipeline.get(), static_cast<uint32_t>(groupIndex));
    }
    void CmdPushDescriptorSetKHR(
        PipelineBindPoint pipelineBindPoint,    
        PipelineLayout layout,    
        uint32_t set,    
        uint32_t descriptorWriteCount,    
        const WriteDescriptorSet* pDescriptorWrites) {
        return vkCmdPushDescriptorSetKHR(get(), static_cast<PipelineBindPoint>(pipelineBindPoint),layout.get(), static_cast<uint32_t>(set), static_cast<uint32_t>(descriptorWriteCount), reinterpret_cast<const WriteDescriptorSet*>(pDescriptorWrites));
    }
    void CmdSetDeviceMask(
        uint32_t deviceMask) {
        return vkCmdSetDeviceMask(get(), static_cast<uint32_t>(deviceMask));
    }
    void CmdDispatchBase(
        uint32_t baseGroupX,    
        uint32_t baseGroupY,    
        uint32_t baseGroupZ,    
        uint32_t groupCountX,    
        uint32_t groupCountY,    
        uint32_t groupCountZ) {
        return vkCmdDispatchBase(get(), static_cast<uint32_t>(baseGroupX), static_cast<uint32_t>(baseGroupY), static_cast<uint32_t>(baseGroupZ), static_cast<uint32_t>(groupCountX), static_cast<uint32_t>(groupCountY), static_cast<uint32_t>(groupCountZ));
    }
    void CmdPushDescriptorSetWithTemplateKHR(
        DescriptorUpdateTemplate descriptorUpdateTemplate,    
        PipelineLayout layout,    
        uint32_t set,    
        const void* pData) {
        return vkCmdPushDescriptorSetWithTemplateKHR(get(),descriptorUpdateTemplate.get(),layout.get(), static_cast<uint32_t>(set), reinterpret_cast<const void*>(pData));
    }
    void CmdSetViewportWScalingNV(
        uint32_t firstViewport,    
        uint32_t viewportCount,    
        const ViewportWScalingNV* pViewportWScalings) {
        return vkCmdSetViewportWScalingNV(get(), static_cast<uint32_t>(firstViewport), static_cast<uint32_t>(viewportCount), reinterpret_cast<const ViewportWScalingNV*>(pViewportWScalings));
    }
    void CmdSetDiscardRectangleEXT(
        uint32_t firstDiscardRectangle,    
        uint32_t discardRectangleCount,    
        const Rect2D* pDiscardRectangles) {
        return vkCmdSetDiscardRectangleEXT(get(), static_cast<uint32_t>(firstDiscardRectangle), static_cast<uint32_t>(discardRectangleCount), reinterpret_cast<const Rect2D*>(pDiscardRectangles));
    }
    void CmdSetSampleLocationsEXT(
        const SampleLocationsInfoEXT* pSampleLocationsInfo) {
        return vkCmdSetSampleLocationsEXT(get(), reinterpret_cast<const SampleLocationsInfoEXT*>(pSampleLocationsInfo));
    }
    void CmdBeginDebugUtilsLabelEXT(
        const DebugUtilsLabelEXT* pLabelInfo) {
        return vkCmdBeginDebugUtilsLabelEXT(get(), reinterpret_cast<const DebugUtilsLabelEXT*>(pLabelInfo));
    }
    void CmdEndDebugUtilsLabelEXT() {
        return vkCmdEndDebugUtilsLabelEXT(get());
    }
    void CmdInsertDebugUtilsLabelEXT(
        const DebugUtilsLabelEXT* pLabelInfo) {
        return vkCmdInsertDebugUtilsLabelEXT(get(), reinterpret_cast<const DebugUtilsLabelEXT*>(pLabelInfo));
    }
    void CmdWriteBufferMarkerAMD(
        PipelineStageFlagBits pipelineStage,    
        Buffer dstBuffer,    
        DeviceSize dstOffset,    
        uint32_t marker) {
        return vkCmdWriteBufferMarkerAMD(get(), static_cast<PipelineStageFlagBits>(pipelineStage),dstBuffer.get(), static_cast<DeviceSize>(dstOffset), static_cast<uint32_t>(marker));
    }
    void CmdBeginRenderPass2(
        const RenderPassBeginInfo* pRenderPassBegin,    
        const SubpassBeginInfo* pSubpassBeginInfo) {
        return vkCmdBeginRenderPass2(get(), reinterpret_cast<const RenderPassBeginInfo*>(pRenderPassBegin), reinterpret_cast<const SubpassBeginInfo*>(pSubpassBeginInfo));
    }
    void CmdNextSubpass2(
        const SubpassBeginInfo* pSubpassBeginInfo,    
        const SubpassEndInfo* pSubpassEndInfo) {
        return vkCmdNextSubpass2(get(), reinterpret_cast<const SubpassBeginInfo*>(pSubpassBeginInfo), reinterpret_cast<const SubpassEndInfo*>(pSubpassEndInfo));
    }
    void CmdEndRenderPass2(
        const SubpassEndInfo* pSubpassEndInfo) {
        return vkCmdEndRenderPass2(get(), reinterpret_cast<const SubpassEndInfo*>(pSubpassEndInfo));
    }
    void CmdDrawIndirectCount(
        Buffer buffer,    
        DeviceSize offset,    
        Buffer countBuffer,    
        DeviceSize countBufferOffset,    
        uint32_t maxDrawCount,    
        uint32_t stride) {
        return vkCmdDrawIndirectCount(get(),buffer.get(), static_cast<DeviceSize>(offset),countBuffer.get(), static_cast<DeviceSize>(countBufferOffset), static_cast<uint32_t>(maxDrawCount), static_cast<uint32_t>(stride));
    }
    void CmdDrawIndexedIndirectCount(
        Buffer buffer,    
        DeviceSize offset,    
        Buffer countBuffer,    
        DeviceSize countBufferOffset,    
        uint32_t maxDrawCount,    
        uint32_t stride) {
        return vkCmdDrawIndexedIndirectCount(get(),buffer.get(), static_cast<DeviceSize>(offset),countBuffer.get(), static_cast<DeviceSize>(countBufferOffset), static_cast<uint32_t>(maxDrawCount), static_cast<uint32_t>(stride));
    }
    void CmdSetCheckpointNV(
        const void* pCheckpointMarker) {
        return vkCmdSetCheckpointNV(get(), reinterpret_cast<const void*>(pCheckpointMarker));
    }
    void CmdBindTransformFeedbackBuffersEXT(
        uint32_t firstBinding,    
        uint32_t bindingCount,    
        const Buffer* pBuffers,    
        const DeviceSize* pOffsets,    
        const DeviceSize* pSizes) {
        return vkCmdBindTransformFeedbackBuffersEXT(get(), static_cast<uint32_t>(firstBinding), static_cast<uint32_t>(bindingCount), reinterpret_cast<const Buffer*>(pBuffers), reinterpret_cast<const DeviceSize*>(pOffsets), reinterpret_cast<const DeviceSize*>(pSizes));
    }
    void CmdBeginTransformFeedbackEXT(
        uint32_t firstCounterBuffer,    
        uint32_t counterBufferCount,    
        const Buffer* pCounterBuffers,    
        const DeviceSize* pCounterBufferOffsets) {
        return vkCmdBeginTransformFeedbackEXT(get(), static_cast<uint32_t>(firstCounterBuffer), static_cast<uint32_t>(counterBufferCount), reinterpret_cast<const Buffer*>(pCounterBuffers), reinterpret_cast<const DeviceSize*>(pCounterBufferOffsets));
    }
    void CmdEndTransformFeedbackEXT(
        uint32_t firstCounterBuffer,    
        uint32_t counterBufferCount,    
        const Buffer* pCounterBuffers,    
        const DeviceSize* pCounterBufferOffsets) {
        return vkCmdEndTransformFeedbackEXT(get(), static_cast<uint32_t>(firstCounterBuffer), static_cast<uint32_t>(counterBufferCount), reinterpret_cast<const Buffer*>(pCounterBuffers), reinterpret_cast<const DeviceSize*>(pCounterBufferOffsets));
    }
    void CmdBeginQueryIndexedEXT(
        QueryPool queryPool,    
        uint32_t query,    
        QueryControlFlags flags,    
        uint32_t index) {
        return vkCmdBeginQueryIndexedEXT(get(),queryPool.get(), static_cast<uint32_t>(query), static_cast<QueryControlFlags>(flags), static_cast<uint32_t>(index));
    }
    void CmdEndQueryIndexedEXT(
        QueryPool queryPool,    
        uint32_t query,    
        uint32_t index) {
        return vkCmdEndQueryIndexedEXT(get(),queryPool.get(), static_cast<uint32_t>(query), static_cast<uint32_t>(index));
    }
    void CmdDrawIndirectByteCountEXT(
        uint32_t instanceCount,    
        uint32_t firstInstance,    
        Buffer counterBuffer,    
        DeviceSize counterBufferOffset,    
        uint32_t counterOffset,    
        uint32_t vertexStride) {
        return vkCmdDrawIndirectByteCountEXT(get(), static_cast<uint32_t>(instanceCount), static_cast<uint32_t>(firstInstance),counterBuffer.get(), static_cast<DeviceSize>(counterBufferOffset), static_cast<uint32_t>(counterOffset), static_cast<uint32_t>(vertexStride));
    }
    void CmdSetExclusiveScissorNV(
        uint32_t firstExclusiveScissor,    
        uint32_t exclusiveScissorCount,    
        const Rect2D* pExclusiveScissors) {
        return vkCmdSetExclusiveScissorNV(get(), static_cast<uint32_t>(firstExclusiveScissor), static_cast<uint32_t>(exclusiveScissorCount), reinterpret_cast<const Rect2D*>(pExclusiveScissors));
    }
    void CmdBindShadingRateImageNV(
        ImageView imageView,    
        ImageLayout imageLayout) {
        return vkCmdBindShadingRateImageNV(get(),imageView.get(), static_cast<ImageLayout>(imageLayout));
    }
    void CmdSetViewportShadingRatePaletteNV(
        uint32_t firstViewport,    
        uint32_t viewportCount,    
        const ShadingRatePaletteNV* pShadingRatePalettes) {
        return vkCmdSetViewportShadingRatePaletteNV(get(), static_cast<uint32_t>(firstViewport), static_cast<uint32_t>(viewportCount), reinterpret_cast<const ShadingRatePaletteNV*>(pShadingRatePalettes));
    }
    void CmdSetCoarseSampleOrderNV(
        CoarseSampleOrderTypeNV sampleOrderType,    
        uint32_t customSampleOrderCount,    
        const CoarseSampleOrderCustomNV* pCustomSampleOrders) {
        return vkCmdSetCoarseSampleOrderNV(get(), static_cast<CoarseSampleOrderTypeNV>(sampleOrderType), static_cast<uint32_t>(customSampleOrderCount), reinterpret_cast<const CoarseSampleOrderCustomNV*>(pCustomSampleOrders));
    }
    void CmdDrawMeshTasksNV(
        uint32_t taskCount,    
        uint32_t firstTask) {
        return vkCmdDrawMeshTasksNV(get(), static_cast<uint32_t>(taskCount), static_cast<uint32_t>(firstTask));
    }
    void CmdDrawMeshTasksIndirectNV(
        Buffer buffer,    
        DeviceSize offset,    
        uint32_t drawCount,    
        uint32_t stride) {
        return vkCmdDrawMeshTasksIndirectNV(get(),buffer.get(), static_cast<DeviceSize>(offset), static_cast<uint32_t>(drawCount), static_cast<uint32_t>(stride));
    }
    void CmdDrawMeshTasksIndirectCountNV(
        Buffer buffer,    
        DeviceSize offset,    
        Buffer countBuffer,    
        DeviceSize countBufferOffset,    
        uint32_t maxDrawCount,    
        uint32_t stride) {
        return vkCmdDrawMeshTasksIndirectCountNV(get(),buffer.get(), static_cast<DeviceSize>(offset),countBuffer.get(), static_cast<DeviceSize>(countBufferOffset), static_cast<uint32_t>(maxDrawCount), static_cast<uint32_t>(stride));
    }
    void CmdCopyAccelerationStructureNV(
        AccelerationStructureKHR dst,    
        AccelerationStructureKHR src,    
        CopyAccelerationStructureModeKHR mode) {
        return vkCmdCopyAccelerationStructureNV(get(),dst.get(),src.get(), static_cast<CopyAccelerationStructureModeKHR>(mode));
    }
    void CmdCopyAccelerationStructureKHR(
        const CopyAccelerationStructureInfoKHR* pInfo) {
        return vkCmdCopyAccelerationStructureKHR(get(), reinterpret_cast<const CopyAccelerationStructureInfoKHR*>(pInfo));
    }
    void CmdCopyAccelerationStructureToMemoryKHR(
        const CopyAccelerationStructureToMemoryInfoKHR* pInfo) {
        return vkCmdCopyAccelerationStructureToMemoryKHR(get(), reinterpret_cast<const CopyAccelerationStructureToMemoryInfoKHR*>(pInfo));
    }
    void CmdCopyMemoryToAccelerationStructureKHR(
        const CopyMemoryToAccelerationStructureInfoKHR* pInfo) {
        return vkCmdCopyMemoryToAccelerationStructureKHR(get(), reinterpret_cast<const CopyMemoryToAccelerationStructureInfoKHR*>(pInfo));
    }
    void CmdWriteAccelerationStructuresPropertiesKHR(
        uint32_t accelerationStructureCount,    
        const AccelerationStructureKHR* pAccelerationStructures,    
        QueryType queryType,    
        QueryPool queryPool,    
        uint32_t firstQuery) {
        return vkCmdWriteAccelerationStructuresPropertiesKHR(get(), static_cast<uint32_t>(accelerationStructureCount), reinterpret_cast<const AccelerationStructureKHR*>(pAccelerationStructures), static_cast<QueryType>(queryType),queryPool.get(), static_cast<uint32_t>(firstQuery));
    }
    void CmdBuildAccelerationStructureNV(
        const AccelerationStructureInfoNV* pInfo,    
        Buffer instanceData,    
        DeviceSize instanceOffset,    
        bool update,    
        AccelerationStructureKHR dst,    
        AccelerationStructureKHR src,    
        Buffer scratch,    
        DeviceSize scratchOffset) {
        return vkCmdBuildAccelerationStructureNV(get(), reinterpret_cast<const AccelerationStructureInfoNV*>(pInfo),instanceData.get(), static_cast<DeviceSize>(instanceOffset), static_cast<bool>(update),dst.get(),src.get(),scratch.get(), static_cast<DeviceSize>(scratchOffset));
    }
    void CmdTraceRaysKHR(
        const StridedBufferRegionKHR* pRaygenShaderBindingTable,    
        const StridedBufferRegionKHR* pMissShaderBindingTable,    
        const StridedBufferRegionKHR* pHitShaderBindingTable,    
        const StridedBufferRegionKHR* pCallableShaderBindingTable,    
        uint32_t width,    
        uint32_t height,    
        uint32_t depth) {
        return vkCmdTraceRaysKHR(get(), reinterpret_cast<const StridedBufferRegionKHR*>(pRaygenShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pMissShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pHitShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pCallableShaderBindingTable), static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(depth));
    }
    void CmdTraceRaysNV(
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
        uint32_t depth) {
        return vkCmdTraceRaysNV(get(),raygenShaderBindingTableBuffer.get(), static_cast<DeviceSize>(raygenShaderBindingOffset),missShaderBindingTableBuffer.get(), static_cast<DeviceSize>(missShaderBindingOffset), static_cast<DeviceSize>(missShaderBindingStride),hitShaderBindingTableBuffer.get(), static_cast<DeviceSize>(hitShaderBindingOffset), static_cast<DeviceSize>(hitShaderBindingStride),callableShaderBindingTableBuffer.get(), static_cast<DeviceSize>(callableShaderBindingOffset), static_cast<DeviceSize>(callableShaderBindingStride), static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(depth));
    }
    void CmdTraceRaysIndirectKHR(
        const StridedBufferRegionKHR* pRaygenShaderBindingTable,    
        const StridedBufferRegionKHR* pMissShaderBindingTable,    
        const StridedBufferRegionKHR* pHitShaderBindingTable,    
        const StridedBufferRegionKHR* pCallableShaderBindingTable,    
        Buffer buffer,    
        DeviceSize offset) {
        return vkCmdTraceRaysIndirectKHR(get(), reinterpret_cast<const StridedBufferRegionKHR*>(pRaygenShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pMissShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pHitShaderBindingTable), reinterpret_cast<const StridedBufferRegionKHR*>(pCallableShaderBindingTable),buffer.get(), static_cast<DeviceSize>(offset));
    }
    VkResult CmdSetPerformanceMarkerINTEL(
        const PerformanceMarkerInfoINTEL* pMarkerInfo) {
        return vkCmdSetPerformanceMarkerINTEL(get(), reinterpret_cast<const PerformanceMarkerInfoINTEL*>(pMarkerInfo));
    }
    VkResult CmdSetPerformanceStreamMarkerINTEL(
        const PerformanceStreamMarkerInfoINTEL* pMarkerInfo) {
        return vkCmdSetPerformanceStreamMarkerINTEL(get(), reinterpret_cast<const PerformanceStreamMarkerInfoINTEL*>(pMarkerInfo));
    }
    VkResult CmdSetPerformanceOverrideINTEL(
        const PerformanceOverrideInfoINTEL* pOverrideInfo) {
        return vkCmdSetPerformanceOverrideINTEL(get(), reinterpret_cast<const PerformanceOverrideInfoINTEL*>(pOverrideInfo));
    }
    void CmdSetLineStippleEXT(
        uint32_t lineStippleFactor,    
        uint16_t lineStipplePattern) {
        return vkCmdSetLineStippleEXT(get(), static_cast<uint32_t>(lineStippleFactor), static_cast<uint16_t>(lineStipplePattern));
    }
    void CmdBuildAccelerationStructureKHR(
        uint32_t infoCount,    
        const AccelerationStructureBuildGeometryInfoKHR* pInfos,    
        const AccelerationStructureBuildOffsetInfoKHR* const* ppOffsetInfos) {
        return vkCmdBuildAccelerationStructureKHR(get(), static_cast<uint32_t>(infoCount), reinterpret_cast<const AccelerationStructureBuildGeometryInfoKHR*>(pInfos), reinterpret_cast<const AccelerationStructureBuildOffsetInfoKHR* const*>(ppOffsetInfos));
    }
    void CmdBuildAccelerationStructureIndirectKHR(
        const AccelerationStructureBuildGeometryInfoKHR* pInfo,    
        Buffer indirectBuffer,    
        DeviceSize indirectOffset,    
        uint32_t indirectStride) {
        return vkCmdBuildAccelerationStructureIndirectKHR(get(), reinterpret_cast<const AccelerationStructureBuildGeometryInfoKHR*>(pInfo),indirectBuffer.get(), static_cast<DeviceSize>(indirectOffset), static_cast<uint32_t>(indirectStride));
    }
};
} // namespace vk
// clang-format on
