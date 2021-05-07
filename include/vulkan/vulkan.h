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
#ifndef SIMPLE_VULKAN_H_
#ifdef VULKAN_H_
#error "Must include these bindings first, not official C vulkan headers (vulkan.h)"
#endif
#endif
#ifndef VULKAN_H_
#define VULKAN_H_ 1
#define SIMPLE_VULKAN_H_ 1

#define VK_VERSION_1_0 1
#define VK_VERSION_1_1 1
#define VK_VERSION_1_2 1
#include <stdint.h>
#include "vk_platform.h"


#if defined(VK_USE_PLATFORM_FUCHSIA)
#include <zircon/types.h>
#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
#include <wayland-client.h>
#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
#include <xcb/xcb.h>
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
#include <X11/Xlib.h>
#endif

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#include <directfb.h>
#endif

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#endif

#if defined(VK_USE_PLATFORM_GGP)
#include <ggp_c/vulkan_types.h>
#endif

// DEPRECATED: This define is deprecated. VK_MAKE_API_VERSION should be used instead.
#define VK_MAKE_VERSION(major, minor, patch) \
    ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

// DEPRECATED: This define is deprecated. VK_API_VERSION_MAJOR should be used instead.
#define VK_VERSION_MAJOR(version) ((uint32_t)(version) >> 22)

// DEPRECATED: This define is deprecated. VK_API_VERSION_MINOR should be used instead.
#define VK_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3FFU)

// DEPRECATED: This define is deprecated. VK_API_VERSION_PATCH should be used instead.
#define VK_VERSION_PATCH(version) ((uint32_t)(version) & 0xFFFU)

#define VK_MAKE_API_VERSION(variant, major, minor, patch) \
    ((((uint32_t)(variant)) << 29) | (((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#define VK_API_VERSION_VARIANT(version) ((uint32_t)(version) >> 29)

#define VK_API_VERSION_MAJOR(version) (((uint32_t)(version) >> 22) & 0x7FU)

#define VK_API_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3FFU)

#define VK_API_VERSION_PATCH(version) ((uint32_t)(version) & 0xFFFU)

// DEPRECATED: This define has been removed. Specific version defines (e.g. VK_API_VERSION_1_0), or the VK_MAKE_VERSION macro, should be used instead.
//#define VK_API_VERSION VK_MAKE_VERSION(1, 0, 0) // Patch version should always be set to 0

// Vulkan 1.0 version number
#define VK_API_VERSION_1_0 VK_MAKE_API_VERSION(0, 1, 0, 0)// Patch version should always be set to 0

// Vulkan 1.1 version number
#define VK_API_VERSION_1_1 VK_MAKE_API_VERSION(0, 1, 1, 0)// Patch version should always be set to 0

// Vulkan 1.2 version number
#define VK_API_VERSION_1_2 VK_MAKE_API_VERSION(0, 1, 2, 0)// Patch version should always be set to 0

// Version of this file
#define VK_HEADER_VERSION 176

// Complete version of this file
#define VK_HEADER_VERSION_COMPLETE VK_MAKE_API_VERSION(0, 1, 2, VK_HEADER_VERSION)


#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;


#ifndef VK_USE_64_BIT_PTR_DEFINES
    #if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
        #define VK_USE_64_BIT_PTR_DEFINES 1
    #else
        #define VK_USE_64_BIT_PTR_DEFINES 0
    #endif
#endif


#ifndef VK_DEFINE_NON_DISPATCHABLE_HANDLE
    #if (VK_USE_64_BIT_PTR_DEFINES==1)
        #if __cplusplus >= 201103L || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201103L))
            #define VK_NULL_HANDLE nullptr
        #else
            #define VK_NULL_HANDLE ((void*)0)
        #endif
    #else
        #define VK_NULL_HANDLE 0ULL
    #endif
#endif
#ifndef VK_NULL_HANDLE
    #define VK_NULL_HANDLE 0
#endif


#ifndef VK_DEFINE_NON_DISPATCHABLE_HANDLE
    #if (VK_USE_64_BIT_PTR_DEFINES==1)
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T *object;
    #else
        #define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object;
    #endif
#endif

constexpr uint32_t VK_MAX_PHYSICAL_DEVICE_NAME_SIZE = 256;
constexpr uint32_t VK_UUID_SIZE = 16;
constexpr uint32_t VK_LUID_SIZE = 8;
constexpr auto VK_LUID_SIZE_KHR = VK_LUID_SIZE;
constexpr uint32_t VK_MAX_EXTENSION_NAME_SIZE = 256;
constexpr uint32_t VK_MAX_DESCRIPTION_SIZE = 256;
constexpr uint32_t VK_MAX_MEMORY_TYPES = 32;
constexpr uint32_t VK_MAX_MEMORY_HEAPS = 16;
constexpr float VK_LOD_CLAMP_NONE = 1000.0F;
constexpr uint32_t VK_REMAINING_MIP_LEVELS = (~0U);
constexpr uint32_t VK_REMAINING_ARRAY_LAYERS = (~0U);
constexpr uint64_t VK_WHOLE_SIZE = (~0ULL);
constexpr uint32_t VK_ATTACHMENT_UNUSED = (~0U);
constexpr uint32_t VK_QUEUE_FAMILY_IGNORED = (~0U);
constexpr uint32_t VK_QUEUE_FAMILY_EXTERNAL = (~1U);
constexpr auto VK_QUEUE_FAMILY_EXTERNAL_KHR = VK_QUEUE_FAMILY_EXTERNAL;
constexpr uint32_t VK_QUEUE_FAMILY_FOREIGN_EXT = (~2U);
constexpr uint32_t VK_SUBPASS_EXTERNAL = (~0U);
constexpr uint32_t VK_MAX_DEVICE_GROUP_SIZE = 32;
constexpr auto VK_MAX_DEVICE_GROUP_SIZE_KHR = VK_MAX_DEVICE_GROUP_SIZE;
constexpr uint32_t VK_MAX_DRIVER_NAME_SIZE = 256;
constexpr auto VK_MAX_DRIVER_NAME_SIZE_KHR = VK_MAX_DRIVER_NAME_SIZE;
constexpr uint32_t VK_MAX_DRIVER_INFO_SIZE = 256;
constexpr auto VK_MAX_DRIVER_INFO_SIZE_KHR = VK_MAX_DRIVER_INFO_SIZE;
constexpr uint32_t VK_SHADER_UNUSED_KHR = (~0U);
constexpr auto VK_SHADER_UNUSED_NV = VK_SHADER_UNUSED_KHR;
using VkSampleMask = uint32_t;
using VkBool32 = uint32_t;
using VkFlags = uint32_t;
using VkFlags64 = uint64_t;
using VkDeviceSize = uint64_t;
using VkDeviceAddress = uint64_t;
enum class VkAttachmentLoadOp : uint32_t {
    Load = 0,
    Clear = 1,
    DontCare = 2,
};
const VkAttachmentLoadOp VK_ATTACHMENT_LOAD_OP_LOAD = VkAttachmentLoadOp::Load;
const VkAttachmentLoadOp VK_ATTACHMENT_LOAD_OP_CLEAR = VkAttachmentLoadOp::Clear;
const VkAttachmentLoadOp VK_ATTACHMENT_LOAD_OP_DONT_CARE = VkAttachmentLoadOp::DontCare;
enum class VkAttachmentStoreOp : uint32_t {
    Store = 0,
    DontCare = 1,
    NoneQCOM = 1000301000,
};
const VkAttachmentStoreOp VK_ATTACHMENT_STORE_OP_STORE = VkAttachmentStoreOp::Store;
const VkAttachmentStoreOp VK_ATTACHMENT_STORE_OP_DONT_CARE = VkAttachmentStoreOp::DontCare;
const VkAttachmentStoreOp VK_ATTACHMENT_STORE_OP_NONE_QCOM = VkAttachmentStoreOp::NoneQCOM;
enum class VkBlendFactor : uint32_t {
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
const VkBlendFactor VK_BLEND_FACTOR_ZERO = VkBlendFactor::Zero;
const VkBlendFactor VK_BLEND_FACTOR_ONE = VkBlendFactor::One;
const VkBlendFactor VK_BLEND_FACTOR_SRC_COLOR = VkBlendFactor::SrcColor;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR = VkBlendFactor::OneMinusSrcColor;
const VkBlendFactor VK_BLEND_FACTOR_DST_COLOR = VkBlendFactor::DstColor;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR = VkBlendFactor::OneMinusDstColor;
const VkBlendFactor VK_BLEND_FACTOR_SRC_ALPHA = VkBlendFactor::SrcAlpha;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = VkBlendFactor::OneMinusSrcAlpha;
const VkBlendFactor VK_BLEND_FACTOR_DST_ALPHA = VkBlendFactor::DstAlpha;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA = VkBlendFactor::OneMinusDstAlpha;
const VkBlendFactor VK_BLEND_FACTOR_CONSTANT_COLOR = VkBlendFactor::ConstantColor;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = VkBlendFactor::OneMinusConstantColor;
const VkBlendFactor VK_BLEND_FACTOR_CONSTANT_ALPHA = VkBlendFactor::ConstantAlpha;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA = VkBlendFactor::OneMinusConstantAlpha;
const VkBlendFactor VK_BLEND_FACTOR_SRC_ALPHA_SATURATE = VkBlendFactor::SrcAlphaSaturate;
const VkBlendFactor VK_BLEND_FACTOR_SRC1_COLOR = VkBlendFactor::Src1Color;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR = VkBlendFactor::OneMinusSrc1Color;
const VkBlendFactor VK_BLEND_FACTOR_SRC1_ALPHA = VkBlendFactor::Src1Alpha;
const VkBlendFactor VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA = VkBlendFactor::OneMinusSrc1Alpha;
enum class VkBlendOp : uint32_t {
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
const VkBlendOp VK_BLEND_OP_ADD = VkBlendOp::Add;
const VkBlendOp VK_BLEND_OP_SUBTRACT = VkBlendOp::Subtract;
const VkBlendOp VK_BLEND_OP_REVERSE_SUBTRACT = VkBlendOp::ReverseSubtract;
const VkBlendOp VK_BLEND_OP_MIN = VkBlendOp::Min;
const VkBlendOp VK_BLEND_OP_MAX = VkBlendOp::Max;
const VkBlendOp VK_BLEND_OP_ZERO_EXT = VkBlendOp::ZeroEXT;
const VkBlendOp VK_BLEND_OP_SRC_EXT = VkBlendOp::SrcEXT;
const VkBlendOp VK_BLEND_OP_DST_EXT = VkBlendOp::DstEXT;
const VkBlendOp VK_BLEND_OP_SRC_OVER_EXT = VkBlendOp::SrcOverEXT;
const VkBlendOp VK_BLEND_OP_DST_OVER_EXT = VkBlendOp::DstOverEXT;
const VkBlendOp VK_BLEND_OP_SRC_IN_EXT = VkBlendOp::SrcInEXT;
const VkBlendOp VK_BLEND_OP_DST_IN_EXT = VkBlendOp::DstInEXT;
const VkBlendOp VK_BLEND_OP_SRC_OUT_EXT = VkBlendOp::SrcOutEXT;
const VkBlendOp VK_BLEND_OP_DST_OUT_EXT = VkBlendOp::DstOutEXT;
const VkBlendOp VK_BLEND_OP_SRC_ATOP_EXT = VkBlendOp::SrcAtopEXT;
const VkBlendOp VK_BLEND_OP_DST_ATOP_EXT = VkBlendOp::DstAtopEXT;
const VkBlendOp VK_BLEND_OP_XOR_EXT = VkBlendOp::XorEXT;
const VkBlendOp VK_BLEND_OP_MULTIPLY_EXT = VkBlendOp::MultiplyEXT;
const VkBlendOp VK_BLEND_OP_SCREEN_EXT = VkBlendOp::ScreenEXT;
const VkBlendOp VK_BLEND_OP_OVERLAY_EXT = VkBlendOp::OverlayEXT;
const VkBlendOp VK_BLEND_OP_DARKEN_EXT = VkBlendOp::DarkenEXT;
const VkBlendOp VK_BLEND_OP_LIGHTEN_EXT = VkBlendOp::LightenEXT;
const VkBlendOp VK_BLEND_OP_COLORDODGE_EXT = VkBlendOp::ColordodgeEXT;
const VkBlendOp VK_BLEND_OP_COLORBURN_EXT = VkBlendOp::ColorburnEXT;
const VkBlendOp VK_BLEND_OP_HARDLIGHT_EXT = VkBlendOp::HardlightEXT;
const VkBlendOp VK_BLEND_OP_SOFTLIGHT_EXT = VkBlendOp::SoftlightEXT;
const VkBlendOp VK_BLEND_OP_DIFFERENCE_EXT = VkBlendOp::DifferenceEXT;
const VkBlendOp VK_BLEND_OP_EXCLUSION_EXT = VkBlendOp::ExclusionEXT;
const VkBlendOp VK_BLEND_OP_INVERT_EXT = VkBlendOp::InvertEXT;
const VkBlendOp VK_BLEND_OP_INVERT_RGB_EXT = VkBlendOp::InvertRgbEXT;
const VkBlendOp VK_BLEND_OP_LINEARDODGE_EXT = VkBlendOp::LineardodgeEXT;
const VkBlendOp VK_BLEND_OP_LINEARBURN_EXT = VkBlendOp::LinearburnEXT;
const VkBlendOp VK_BLEND_OP_VIVIDLIGHT_EXT = VkBlendOp::VividlightEXT;
const VkBlendOp VK_BLEND_OP_LINEARLIGHT_EXT = VkBlendOp::LinearlightEXT;
const VkBlendOp VK_BLEND_OP_PINLIGHT_EXT = VkBlendOp::PinlightEXT;
const VkBlendOp VK_BLEND_OP_HARDMIX_EXT = VkBlendOp::HardmixEXT;
const VkBlendOp VK_BLEND_OP_HSL_HUE_EXT = VkBlendOp::HslHueEXT;
const VkBlendOp VK_BLEND_OP_HSL_SATURATION_EXT = VkBlendOp::HslSaturationEXT;
const VkBlendOp VK_BLEND_OP_HSL_COLOR_EXT = VkBlendOp::HslColorEXT;
const VkBlendOp VK_BLEND_OP_HSL_LUMINOSITY_EXT = VkBlendOp::HslLuminosityEXT;
const VkBlendOp VK_BLEND_OP_PLUS_EXT = VkBlendOp::PlusEXT;
const VkBlendOp VK_BLEND_OP_PLUS_CLAMPED_EXT = VkBlendOp::PlusClampedEXT;
const VkBlendOp VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT = VkBlendOp::PlusClampedAlphaEXT;
const VkBlendOp VK_BLEND_OP_PLUS_DARKER_EXT = VkBlendOp::PlusDarkerEXT;
const VkBlendOp VK_BLEND_OP_MINUS_EXT = VkBlendOp::MinusEXT;
const VkBlendOp VK_BLEND_OP_MINUS_CLAMPED_EXT = VkBlendOp::MinusClampedEXT;
const VkBlendOp VK_BLEND_OP_CONTRAST_EXT = VkBlendOp::ContrastEXT;
const VkBlendOp VK_BLEND_OP_INVERT_OVG_EXT = VkBlendOp::InvertOvgEXT;
const VkBlendOp VK_BLEND_OP_RED_EXT = VkBlendOp::RedEXT;
const VkBlendOp VK_BLEND_OP_GREEN_EXT = VkBlendOp::GreenEXT;
const VkBlendOp VK_BLEND_OP_BLUE_EXT = VkBlendOp::BlueEXT;
enum class VkBorderColor : uint32_t {
    FloatTransparentBlack = 0,
    IntTransparentBlack = 1,
    FloatOpaqueBlack = 2,
    IntOpaqueBlack = 3,
    FloatOpaqueWhite = 4,
    IntOpaqueWhite = 5,
    FloatCustomEXT = 1000287003,
    IntCustomEXT = 1000287004,
};
const VkBorderColor VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK = VkBorderColor::FloatTransparentBlack;
const VkBorderColor VK_BORDER_COLOR_INT_TRANSPARENT_BLACK = VkBorderColor::IntTransparentBlack;
const VkBorderColor VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK = VkBorderColor::FloatOpaqueBlack;
const VkBorderColor VK_BORDER_COLOR_INT_OPAQUE_BLACK = VkBorderColor::IntOpaqueBlack;
const VkBorderColor VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE = VkBorderColor::FloatOpaqueWhite;
const VkBorderColor VK_BORDER_COLOR_INT_OPAQUE_WHITE = VkBorderColor::IntOpaqueWhite;
const VkBorderColor VK_BORDER_COLOR_FLOAT_CUSTOM_EXT = VkBorderColor::FloatCustomEXT;
const VkBorderColor VK_BORDER_COLOR_INT_CUSTOM_EXT = VkBorderColor::IntCustomEXT;
enum class VkPipelineCacheHeaderVersion : uint32_t {
    One = 1,
};
const VkPipelineCacheHeaderVersion VK_PIPELINE_CACHE_HEADER_VERSION_ONE = VkPipelineCacheHeaderVersion::One;
enum class VkComponentSwizzle : uint32_t {
    Identity = 0,
    Zero = 1,
    One = 2,
    R = 3,
    G = 4,
    B = 5,
    A = 6,
};
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_IDENTITY = VkComponentSwizzle::Identity;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_ZERO = VkComponentSwizzle::Zero;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_ONE = VkComponentSwizzle::One;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_R = VkComponentSwizzle::R;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_G = VkComponentSwizzle::G;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_B = VkComponentSwizzle::B;
const VkComponentSwizzle VK_COMPONENT_SWIZZLE_A = VkComponentSwizzle::A;
enum class VkCommandBufferLevel : uint32_t {
    Primary = 0,
    Secondary = 1,
};
const VkCommandBufferLevel VK_COMMAND_BUFFER_LEVEL_PRIMARY = VkCommandBufferLevel::Primary;
const VkCommandBufferLevel VK_COMMAND_BUFFER_LEVEL_SECONDARY = VkCommandBufferLevel::Secondary;
enum class VkCompareOp : uint32_t {
    Never = 0,
    Less = 1,
    Equal = 2,
    LessOrEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterOrEqual = 6,
    Always = 7,
};
const VkCompareOp VK_COMPARE_OP_NEVER = VkCompareOp::Never;
const VkCompareOp VK_COMPARE_OP_LESS = VkCompareOp::Less;
const VkCompareOp VK_COMPARE_OP_EQUAL = VkCompareOp::Equal;
const VkCompareOp VK_COMPARE_OP_LESS_OR_EQUAL = VkCompareOp::LessOrEqual;
const VkCompareOp VK_COMPARE_OP_GREATER = VkCompareOp::Greater;
const VkCompareOp VK_COMPARE_OP_NOT_EQUAL = VkCompareOp::NotEqual;
const VkCompareOp VK_COMPARE_OP_GREATER_OR_EQUAL = VkCompareOp::GreaterOrEqual;
const VkCompareOp VK_COMPARE_OP_ALWAYS = VkCompareOp::Always;
enum class VkDescriptorType : uint32_t {
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
    MutableVALVE = 1000351000,
};
const VkDescriptorType VK_DESCRIPTOR_TYPE_SAMPLER = VkDescriptorType::Sampler;
const VkDescriptorType VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER = VkDescriptorType::CombinedImageSampler;
const VkDescriptorType VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE = VkDescriptorType::SampledImage;
const VkDescriptorType VK_DESCRIPTOR_TYPE_STORAGE_IMAGE = VkDescriptorType::StorageImage;
const VkDescriptorType VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER = VkDescriptorType::UniformTexelBuffer;
const VkDescriptorType VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER = VkDescriptorType::StorageTexelBuffer;
const VkDescriptorType VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER = VkDescriptorType::UniformBuffer;
const VkDescriptorType VK_DESCRIPTOR_TYPE_STORAGE_BUFFER = VkDescriptorType::StorageBuffer;
const VkDescriptorType VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC = VkDescriptorType::UniformBufferDynamic;
const VkDescriptorType VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC = VkDescriptorType::StorageBufferDynamic;
const VkDescriptorType VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT = VkDescriptorType::InputAttachment;
const VkDescriptorType VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT = VkDescriptorType::InlineUniformBlockEXT;
const VkDescriptorType VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR = VkDescriptorType::AccelerationStructureKHR;
const VkDescriptorType VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV = VkDescriptorType::AccelerationStructureNV;
const VkDescriptorType VK_DESCRIPTOR_TYPE_MUTABLE_VALVE = VkDescriptorType::MutableVALVE;
enum class VkDynamicState : uint32_t {
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
    VertexInputEXT = 1000352000,
    PatchControlPointsEXT = 1000377000,
    RasterizerDiscardEnableEXT = 1000377001,
    DepthBiasEnableEXT = 1000377002,
    LogicOpEXT = 1000377003,
    PrimitiveRestartEnableEXT = 1000377004,
    ColorWriteEnableEXT = 1000381000,
};
const VkDynamicState VK_DYNAMIC_STATE_VIEWPORT = VkDynamicState::Viewport;
const VkDynamicState VK_DYNAMIC_STATE_SCISSOR = VkDynamicState::Scissor;
const VkDynamicState VK_DYNAMIC_STATE_LINE_WIDTH = VkDynamicState::LineWidth;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_BIAS = VkDynamicState::DepthBias;
const VkDynamicState VK_DYNAMIC_STATE_BLEND_CONSTANTS = VkDynamicState::BlendConstants;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_BOUNDS = VkDynamicState::DepthBounds;
const VkDynamicState VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK = VkDynamicState::StencilCompareMask;
const VkDynamicState VK_DYNAMIC_STATE_STENCIL_WRITE_MASK = VkDynamicState::StencilWriteMask;
const VkDynamicState VK_DYNAMIC_STATE_STENCIL_REFERENCE = VkDynamicState::StencilReference;
const VkDynamicState VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV = VkDynamicState::ViewportWScalingNV;
const VkDynamicState VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT = VkDynamicState::DiscardRectangleEXT;
const VkDynamicState VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT = VkDynamicState::SampleLocationsEXT;
const VkDynamicState VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR = VkDynamicState::RayTracingPipelineStackSizeKHR;
const VkDynamicState VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV = VkDynamicState::ViewportShadingRatePaletteNV;
const VkDynamicState VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV = VkDynamicState::ViewportCoarseSampleOrderNV;
const VkDynamicState VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV = VkDynamicState::ExclusiveScissorNV;
const VkDynamicState VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR = VkDynamicState::FragmentShadingRateKHR;
const VkDynamicState VK_DYNAMIC_STATE_LINE_STIPPLE_EXT = VkDynamicState::LineStippleEXT;
const VkDynamicState VK_DYNAMIC_STATE_CULL_MODE_EXT = VkDynamicState::CullModeEXT;
const VkDynamicState VK_DYNAMIC_STATE_FRONT_FACE_EXT = VkDynamicState::FrontFaceEXT;
const VkDynamicState VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT = VkDynamicState::PrimitiveTopologyEXT;
const VkDynamicState VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT = VkDynamicState::ViewportWithCountEXT;
const VkDynamicState VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT = VkDynamicState::ScissorWithCountEXT;
const VkDynamicState VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT = VkDynamicState::VertexInputBindingStrideEXT;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT = VkDynamicState::DepthTestEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT = VkDynamicState::DepthWriteEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT = VkDynamicState::DepthCompareOpEXT;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT = VkDynamicState::DepthBoundsTestEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT = VkDynamicState::StencilTestEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_STENCIL_OP_EXT = VkDynamicState::StencilOpEXT;
const VkDynamicState VK_DYNAMIC_STATE_VERTEX_INPUT_EXT = VkDynamicState::VertexInputEXT;
const VkDynamicState VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT = VkDynamicState::PatchControlPointsEXT;
const VkDynamicState VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE_EXT = VkDynamicState::RasterizerDiscardEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE_EXT = VkDynamicState::DepthBiasEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_LOGIC_OP_EXT = VkDynamicState::LogicOpEXT;
const VkDynamicState VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE_EXT = VkDynamicState::PrimitiveRestartEnableEXT;
const VkDynamicState VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT = VkDynamicState::ColorWriteEnableEXT;
enum class VkPolygonMode : uint32_t {
    Fill = 0,
    Line = 1,
    Point = 2,
    FillRectangleNV = 1000153000,
};
const VkPolygonMode VK_POLYGON_MODE_FILL = VkPolygonMode::Fill;
const VkPolygonMode VK_POLYGON_MODE_LINE = VkPolygonMode::Line;
const VkPolygonMode VK_POLYGON_MODE_POINT = VkPolygonMode::Point;
const VkPolygonMode VK_POLYGON_MODE_FILL_RECTANGLE_NV = VkPolygonMode::FillRectangleNV;
enum class VkFormat : uint32_t {
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
    G8B8R82Plane444UnormEXT = 1000330000,
    G10X6B10X6R10X62Plane444Unorm3Pack16EXT = 1000330001,
    G12X4B12X4R12X42Plane444Unorm3Pack16EXT = 1000330002,
    G16B16R162Plane444UnormEXT = 1000330003,
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
const VkFormat VK_FORMAT_UNDEFINED = VkFormat::Undefined;
const VkFormat VK_FORMAT_R4G4_UNORM_PACK8 = VkFormat::R4G4UnormPack8;
const VkFormat VK_FORMAT_R4G4B4A4_UNORM_PACK16 = VkFormat::R4G4B4A4UnormPack16;
const VkFormat VK_FORMAT_B4G4R4A4_UNORM_PACK16 = VkFormat::B4G4R4A4UnormPack16;
const VkFormat VK_FORMAT_R5G6B5_UNORM_PACK16 = VkFormat::R5G6B5UnormPack16;
const VkFormat VK_FORMAT_B5G6R5_UNORM_PACK16 = VkFormat::B5G6R5UnormPack16;
const VkFormat VK_FORMAT_R5G5B5A1_UNORM_PACK16 = VkFormat::R5G5B5A1UnormPack16;
const VkFormat VK_FORMAT_B5G5R5A1_UNORM_PACK16 = VkFormat::B5G5R5A1UnormPack16;
const VkFormat VK_FORMAT_A1R5G5B5_UNORM_PACK16 = VkFormat::A1R5G5B5UnormPack16;
const VkFormat VK_FORMAT_R8_UNORM = VkFormat::R8Unorm;
const VkFormat VK_FORMAT_R8_SNORM = VkFormat::R8Snorm;
const VkFormat VK_FORMAT_R8_USCALED = VkFormat::R8Uscaled;
const VkFormat VK_FORMAT_R8_SSCALED = VkFormat::R8Sscaled;
const VkFormat VK_FORMAT_R8_UINT = VkFormat::R8Uint;
const VkFormat VK_FORMAT_R8_SINT = VkFormat::R8Sint;
const VkFormat VK_FORMAT_R8_SRGB = VkFormat::R8Srgb;
const VkFormat VK_FORMAT_R8G8_UNORM = VkFormat::R8G8Unorm;
const VkFormat VK_FORMAT_R8G8_SNORM = VkFormat::R8G8Snorm;
const VkFormat VK_FORMAT_R8G8_USCALED = VkFormat::R8G8Uscaled;
const VkFormat VK_FORMAT_R8G8_SSCALED = VkFormat::R8G8Sscaled;
const VkFormat VK_FORMAT_R8G8_UINT = VkFormat::R8G8Uint;
const VkFormat VK_FORMAT_R8G8_SINT = VkFormat::R8G8Sint;
const VkFormat VK_FORMAT_R8G8_SRGB = VkFormat::R8G8Srgb;
const VkFormat VK_FORMAT_R8G8B8_UNORM = VkFormat::R8G8B8Unorm;
const VkFormat VK_FORMAT_R8G8B8_SNORM = VkFormat::R8G8B8Snorm;
const VkFormat VK_FORMAT_R8G8B8_USCALED = VkFormat::R8G8B8Uscaled;
const VkFormat VK_FORMAT_R8G8B8_SSCALED = VkFormat::R8G8B8Sscaled;
const VkFormat VK_FORMAT_R8G8B8_UINT = VkFormat::R8G8B8Uint;
const VkFormat VK_FORMAT_R8G8B8_SINT = VkFormat::R8G8B8Sint;
const VkFormat VK_FORMAT_R8G8B8_SRGB = VkFormat::R8G8B8Srgb;
const VkFormat VK_FORMAT_B8G8R8_UNORM = VkFormat::B8G8R8Unorm;
const VkFormat VK_FORMAT_B8G8R8_SNORM = VkFormat::B8G8R8Snorm;
const VkFormat VK_FORMAT_B8G8R8_USCALED = VkFormat::B8G8R8Uscaled;
const VkFormat VK_FORMAT_B8G8R8_SSCALED = VkFormat::B8G8R8Sscaled;
const VkFormat VK_FORMAT_B8G8R8_UINT = VkFormat::B8G8R8Uint;
const VkFormat VK_FORMAT_B8G8R8_SINT = VkFormat::B8G8R8Sint;
const VkFormat VK_FORMAT_B8G8R8_SRGB = VkFormat::B8G8R8Srgb;
const VkFormat VK_FORMAT_R8G8B8A8_UNORM = VkFormat::R8G8B8A8Unorm;
const VkFormat VK_FORMAT_R8G8B8A8_SNORM = VkFormat::R8G8B8A8Snorm;
const VkFormat VK_FORMAT_R8G8B8A8_USCALED = VkFormat::R8G8B8A8Uscaled;
const VkFormat VK_FORMAT_R8G8B8A8_SSCALED = VkFormat::R8G8B8A8Sscaled;
const VkFormat VK_FORMAT_R8G8B8A8_UINT = VkFormat::R8G8B8A8Uint;
const VkFormat VK_FORMAT_R8G8B8A8_SINT = VkFormat::R8G8B8A8Sint;
const VkFormat VK_FORMAT_R8G8B8A8_SRGB = VkFormat::R8G8B8A8Srgb;
const VkFormat VK_FORMAT_B8G8R8A8_UNORM = VkFormat::B8G8R8A8Unorm;
const VkFormat VK_FORMAT_B8G8R8A8_SNORM = VkFormat::B8G8R8A8Snorm;
const VkFormat VK_FORMAT_B8G8R8A8_USCALED = VkFormat::B8G8R8A8Uscaled;
const VkFormat VK_FORMAT_B8G8R8A8_SSCALED = VkFormat::B8G8R8A8Sscaled;
const VkFormat VK_FORMAT_B8G8R8A8_UINT = VkFormat::B8G8R8A8Uint;
const VkFormat VK_FORMAT_B8G8R8A8_SINT = VkFormat::B8G8R8A8Sint;
const VkFormat VK_FORMAT_B8G8R8A8_SRGB = VkFormat::B8G8R8A8Srgb;
const VkFormat VK_FORMAT_A8B8G8R8_UNORM_PACK32 = VkFormat::A8B8G8R8UnormPack32;
const VkFormat VK_FORMAT_A8B8G8R8_SNORM_PACK32 = VkFormat::A8B8G8R8SnormPack32;
const VkFormat VK_FORMAT_A8B8G8R8_USCALED_PACK32 = VkFormat::A8B8G8R8UscaledPack32;
const VkFormat VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = VkFormat::A8B8G8R8SscaledPack32;
const VkFormat VK_FORMAT_A8B8G8R8_UINT_PACK32 = VkFormat::A8B8G8R8UintPack32;
const VkFormat VK_FORMAT_A8B8G8R8_SINT_PACK32 = VkFormat::A8B8G8R8SintPack32;
const VkFormat VK_FORMAT_A8B8G8R8_SRGB_PACK32 = VkFormat::A8B8G8R8SrgbPack32;
const VkFormat VK_FORMAT_A2R10G10B10_UNORM_PACK32 = VkFormat::A2R10G10B10UnormPack32;
const VkFormat VK_FORMAT_A2R10G10B10_SNORM_PACK32 = VkFormat::A2R10G10B10SnormPack32;
const VkFormat VK_FORMAT_A2R10G10B10_USCALED_PACK32 = VkFormat::A2R10G10B10UscaledPack32;
const VkFormat VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = VkFormat::A2R10G10B10SscaledPack32;
const VkFormat VK_FORMAT_A2R10G10B10_UINT_PACK32 = VkFormat::A2R10G10B10UintPack32;
const VkFormat VK_FORMAT_A2R10G10B10_SINT_PACK32 = VkFormat::A2R10G10B10SintPack32;
const VkFormat VK_FORMAT_A2B10G10R10_UNORM_PACK32 = VkFormat::A2B10G10R10UnormPack32;
const VkFormat VK_FORMAT_A2B10G10R10_SNORM_PACK32 = VkFormat::A2B10G10R10SnormPack32;
const VkFormat VK_FORMAT_A2B10G10R10_USCALED_PACK32 = VkFormat::A2B10G10R10UscaledPack32;
const VkFormat VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = VkFormat::A2B10G10R10SscaledPack32;
const VkFormat VK_FORMAT_A2B10G10R10_UINT_PACK32 = VkFormat::A2B10G10R10UintPack32;
const VkFormat VK_FORMAT_A2B10G10R10_SINT_PACK32 = VkFormat::A2B10G10R10SintPack32;
const VkFormat VK_FORMAT_R16_UNORM = VkFormat::R16Unorm;
const VkFormat VK_FORMAT_R16_SNORM = VkFormat::R16Snorm;
const VkFormat VK_FORMAT_R16_USCALED = VkFormat::R16Uscaled;
const VkFormat VK_FORMAT_R16_SSCALED = VkFormat::R16Sscaled;
const VkFormat VK_FORMAT_R16_UINT = VkFormat::R16Uint;
const VkFormat VK_FORMAT_R16_SINT = VkFormat::R16Sint;
const VkFormat VK_FORMAT_R16_SFLOAT = VkFormat::R16Sfloat;
const VkFormat VK_FORMAT_R16G16_UNORM = VkFormat::R16G16Unorm;
const VkFormat VK_FORMAT_R16G16_SNORM = VkFormat::R16G16Snorm;
const VkFormat VK_FORMAT_R16G16_USCALED = VkFormat::R16G16Uscaled;
const VkFormat VK_FORMAT_R16G16_SSCALED = VkFormat::R16G16Sscaled;
const VkFormat VK_FORMAT_R16G16_UINT = VkFormat::R16G16Uint;
const VkFormat VK_FORMAT_R16G16_SINT = VkFormat::R16G16Sint;
const VkFormat VK_FORMAT_R16G16_SFLOAT = VkFormat::R16G16Sfloat;
const VkFormat VK_FORMAT_R16G16B16_UNORM = VkFormat::R16G16B16Unorm;
const VkFormat VK_FORMAT_R16G16B16_SNORM = VkFormat::R16G16B16Snorm;
const VkFormat VK_FORMAT_R16G16B16_USCALED = VkFormat::R16G16B16Uscaled;
const VkFormat VK_FORMAT_R16G16B16_SSCALED = VkFormat::R16G16B16Sscaled;
const VkFormat VK_FORMAT_R16G16B16_UINT = VkFormat::R16G16B16Uint;
const VkFormat VK_FORMAT_R16G16B16_SINT = VkFormat::R16G16B16Sint;
const VkFormat VK_FORMAT_R16G16B16_SFLOAT = VkFormat::R16G16B16Sfloat;
const VkFormat VK_FORMAT_R16G16B16A16_UNORM = VkFormat::R16G16B16A16Unorm;
const VkFormat VK_FORMAT_R16G16B16A16_SNORM = VkFormat::R16G16B16A16Snorm;
const VkFormat VK_FORMAT_R16G16B16A16_USCALED = VkFormat::R16G16B16A16Uscaled;
const VkFormat VK_FORMAT_R16G16B16A16_SSCALED = VkFormat::R16G16B16A16Sscaled;
const VkFormat VK_FORMAT_R16G16B16A16_UINT = VkFormat::R16G16B16A16Uint;
const VkFormat VK_FORMAT_R16G16B16A16_SINT = VkFormat::R16G16B16A16Sint;
const VkFormat VK_FORMAT_R16G16B16A16_SFLOAT = VkFormat::R16G16B16A16Sfloat;
const VkFormat VK_FORMAT_R32_UINT = VkFormat::R32Uint;
const VkFormat VK_FORMAT_R32_SINT = VkFormat::R32Sint;
const VkFormat VK_FORMAT_R32_SFLOAT = VkFormat::R32Sfloat;
const VkFormat VK_FORMAT_R32G32_UINT = VkFormat::R32G32Uint;
const VkFormat VK_FORMAT_R32G32_SINT = VkFormat::R32G32Sint;
const VkFormat VK_FORMAT_R32G32_SFLOAT = VkFormat::R32G32Sfloat;
const VkFormat VK_FORMAT_R32G32B32_UINT = VkFormat::R32G32B32Uint;
const VkFormat VK_FORMAT_R32G32B32_SINT = VkFormat::R32G32B32Sint;
const VkFormat VK_FORMAT_R32G32B32_SFLOAT = VkFormat::R32G32B32Sfloat;
const VkFormat VK_FORMAT_R32G32B32A32_UINT = VkFormat::R32G32B32A32Uint;
const VkFormat VK_FORMAT_R32G32B32A32_SINT = VkFormat::R32G32B32A32Sint;
const VkFormat VK_FORMAT_R32G32B32A32_SFLOAT = VkFormat::R32G32B32A32Sfloat;
const VkFormat VK_FORMAT_R64_UINT = VkFormat::R64Uint;
const VkFormat VK_FORMAT_R64_SINT = VkFormat::R64Sint;
const VkFormat VK_FORMAT_R64_SFLOAT = VkFormat::R64Sfloat;
const VkFormat VK_FORMAT_R64G64_UINT = VkFormat::R64G64Uint;
const VkFormat VK_FORMAT_R64G64_SINT = VkFormat::R64G64Sint;
const VkFormat VK_FORMAT_R64G64_SFLOAT = VkFormat::R64G64Sfloat;
const VkFormat VK_FORMAT_R64G64B64_UINT = VkFormat::R64G64B64Uint;
const VkFormat VK_FORMAT_R64G64B64_SINT = VkFormat::R64G64B64Sint;
const VkFormat VK_FORMAT_R64G64B64_SFLOAT = VkFormat::R64G64B64Sfloat;
const VkFormat VK_FORMAT_R64G64B64A64_UINT = VkFormat::R64G64B64A64Uint;
const VkFormat VK_FORMAT_R64G64B64A64_SINT = VkFormat::R64G64B64A64Sint;
const VkFormat VK_FORMAT_R64G64B64A64_SFLOAT = VkFormat::R64G64B64A64Sfloat;
const VkFormat VK_FORMAT_B10G11R11_UFLOAT_PACK32 = VkFormat::B10G11R11UfloatPack32;
const VkFormat VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = VkFormat::E5B9G9R9UfloatPack32;
const VkFormat VK_FORMAT_D16_UNORM = VkFormat::D16Unorm;
const VkFormat VK_FORMAT_X8_D24_UNORM_PACK32 = VkFormat::X8D24UnormPack32;
const VkFormat VK_FORMAT_D32_SFLOAT = VkFormat::D32Sfloat;
const VkFormat VK_FORMAT_S8_UINT = VkFormat::S8Uint;
const VkFormat VK_FORMAT_D16_UNORM_S8_UINT = VkFormat::D16UnormS8Uint;
const VkFormat VK_FORMAT_D24_UNORM_S8_UINT = VkFormat::D24UnormS8Uint;
const VkFormat VK_FORMAT_D32_SFLOAT_S8_UINT = VkFormat::D32SfloatS8Uint;
const VkFormat VK_FORMAT_BC1_RGB_UNORM_BLOCK = VkFormat::Bc1RgbUnormBlock;
const VkFormat VK_FORMAT_BC1_RGB_SRGB_BLOCK = VkFormat::Bc1RgbSrgbBlock;
const VkFormat VK_FORMAT_BC1_RGBA_UNORM_BLOCK = VkFormat::Bc1RgbaUnormBlock;
const VkFormat VK_FORMAT_BC1_RGBA_SRGB_BLOCK = VkFormat::Bc1RgbaSrgbBlock;
const VkFormat VK_FORMAT_BC2_UNORM_BLOCK = VkFormat::Bc2UnormBlock;
const VkFormat VK_FORMAT_BC2_SRGB_BLOCK = VkFormat::Bc2SrgbBlock;
const VkFormat VK_FORMAT_BC3_UNORM_BLOCK = VkFormat::Bc3UnormBlock;
const VkFormat VK_FORMAT_BC3_SRGB_BLOCK = VkFormat::Bc3SrgbBlock;
const VkFormat VK_FORMAT_BC4_UNORM_BLOCK = VkFormat::Bc4UnormBlock;
const VkFormat VK_FORMAT_BC4_SNORM_BLOCK = VkFormat::Bc4SnormBlock;
const VkFormat VK_FORMAT_BC5_UNORM_BLOCK = VkFormat::Bc5UnormBlock;
const VkFormat VK_FORMAT_BC5_SNORM_BLOCK = VkFormat::Bc5SnormBlock;
const VkFormat VK_FORMAT_BC6H_UFLOAT_BLOCK = VkFormat::Bc6HUfloatBlock;
const VkFormat VK_FORMAT_BC6H_SFLOAT_BLOCK = VkFormat::Bc6HSfloatBlock;
const VkFormat VK_FORMAT_BC7_UNORM_BLOCK = VkFormat::Bc7UnormBlock;
const VkFormat VK_FORMAT_BC7_SRGB_BLOCK = VkFormat::Bc7SrgbBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = VkFormat::Etc2R8G8B8UnormBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = VkFormat::Etc2R8G8B8SrgbBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = VkFormat::Etc2R8G8B8A1UnormBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = VkFormat::Etc2R8G8B8A1SrgbBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = VkFormat::Etc2R8G8B8A8UnormBlock;
const VkFormat VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = VkFormat::Etc2R8G8B8A8SrgbBlock;
const VkFormat VK_FORMAT_EAC_R11_UNORM_BLOCK = VkFormat::EacR11UnormBlock;
const VkFormat VK_FORMAT_EAC_R11_SNORM_BLOCK = VkFormat::EacR11SnormBlock;
const VkFormat VK_FORMAT_EAC_R11G11_UNORM_BLOCK = VkFormat::EacR11G11UnormBlock;
const VkFormat VK_FORMAT_EAC_R11G11_SNORM_BLOCK = VkFormat::EacR11G11SnormBlock;
const VkFormat VK_FORMAT_ASTC_4x4_UNORM_BLOCK = VkFormat::Astc4X4UnormBlock;
const VkFormat VK_FORMAT_ASTC_4x4_SRGB_BLOCK = VkFormat::Astc4X4SrgbBlock;
const VkFormat VK_FORMAT_ASTC_5x4_UNORM_BLOCK = VkFormat::Astc5X4UnormBlock;
const VkFormat VK_FORMAT_ASTC_5x4_SRGB_BLOCK = VkFormat::Astc5X4SrgbBlock;
const VkFormat VK_FORMAT_ASTC_5x5_UNORM_BLOCK = VkFormat::Astc5X5UnormBlock;
const VkFormat VK_FORMAT_ASTC_5x5_SRGB_BLOCK = VkFormat::Astc5X5SrgbBlock;
const VkFormat VK_FORMAT_ASTC_6x5_UNORM_BLOCK = VkFormat::Astc6X5UnormBlock;
const VkFormat VK_FORMAT_ASTC_6x5_SRGB_BLOCK = VkFormat::Astc6X5SrgbBlock;
const VkFormat VK_FORMAT_ASTC_6x6_UNORM_BLOCK = VkFormat::Astc6X6UnormBlock;
const VkFormat VK_FORMAT_ASTC_6x6_SRGB_BLOCK = VkFormat::Astc6X6SrgbBlock;
const VkFormat VK_FORMAT_ASTC_8x5_UNORM_BLOCK = VkFormat::Astc8X5UnormBlock;
const VkFormat VK_FORMAT_ASTC_8x5_SRGB_BLOCK = VkFormat::Astc8X5SrgbBlock;
const VkFormat VK_FORMAT_ASTC_8x6_UNORM_BLOCK = VkFormat::Astc8X6UnormBlock;
const VkFormat VK_FORMAT_ASTC_8x6_SRGB_BLOCK = VkFormat::Astc8X6SrgbBlock;
const VkFormat VK_FORMAT_ASTC_8x8_UNORM_BLOCK = VkFormat::Astc8X8UnormBlock;
const VkFormat VK_FORMAT_ASTC_8x8_SRGB_BLOCK = VkFormat::Astc8X8SrgbBlock;
const VkFormat VK_FORMAT_ASTC_10x5_UNORM_BLOCK = VkFormat::Astc10X5UnormBlock;
const VkFormat VK_FORMAT_ASTC_10x5_SRGB_BLOCK = VkFormat::Astc10X5SrgbBlock;
const VkFormat VK_FORMAT_ASTC_10x6_UNORM_BLOCK = VkFormat::Astc10X6UnormBlock;
const VkFormat VK_FORMAT_ASTC_10x6_SRGB_BLOCK = VkFormat::Astc10X6SrgbBlock;
const VkFormat VK_FORMAT_ASTC_10x8_UNORM_BLOCK = VkFormat::Astc10X8UnormBlock;
const VkFormat VK_FORMAT_ASTC_10x8_SRGB_BLOCK = VkFormat::Astc10X8SrgbBlock;
const VkFormat VK_FORMAT_ASTC_10x10_UNORM_BLOCK = VkFormat::Astc10X10UnormBlock;
const VkFormat VK_FORMAT_ASTC_10x10_SRGB_BLOCK = VkFormat::Astc10X10SrgbBlock;
const VkFormat VK_FORMAT_ASTC_12x10_UNORM_BLOCK = VkFormat::Astc12X10UnormBlock;
const VkFormat VK_FORMAT_ASTC_12x10_SRGB_BLOCK = VkFormat::Astc12X10SrgbBlock;
const VkFormat VK_FORMAT_ASTC_12x12_UNORM_BLOCK = VkFormat::Astc12X12UnormBlock;
const VkFormat VK_FORMAT_ASTC_12x12_SRGB_BLOCK = VkFormat::Astc12X12SrgbBlock;
const VkFormat VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG = VkFormat::Pvrtc12BppUnormBlockIMG;
const VkFormat VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG = VkFormat::Pvrtc14BppUnormBlockIMG;
const VkFormat VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG = VkFormat::Pvrtc22BppUnormBlockIMG;
const VkFormat VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG = VkFormat::Pvrtc24BppUnormBlockIMG;
const VkFormat VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG = VkFormat::Pvrtc12BppSrgbBlockIMG;
const VkFormat VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG = VkFormat::Pvrtc14BppSrgbBlockIMG;
const VkFormat VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG = VkFormat::Pvrtc22BppSrgbBlockIMG;
const VkFormat VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG = VkFormat::Pvrtc24BppSrgbBlockIMG;
const VkFormat VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT = VkFormat::Astc4X4SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT = VkFormat::Astc5X4SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT = VkFormat::Astc5X5SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT = VkFormat::Astc6X5SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT = VkFormat::Astc6X6SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT = VkFormat::Astc8X5SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT = VkFormat::Astc8X6SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT = VkFormat::Astc8X8SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT = VkFormat::Astc10X5SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT = VkFormat::Astc10X6SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT = VkFormat::Astc10X8SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT = VkFormat::Astc10X10SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT = VkFormat::Astc12X10SfloatBlockEXT;
const VkFormat VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT = VkFormat::Astc12X12SfloatBlockEXT;
const VkFormat VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT = VkFormat::G8B8R82Plane444UnormEXT;
const VkFormat VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT = VkFormat::G10X6B10X6R10X62Plane444Unorm3Pack16EXT;
const VkFormat VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT = VkFormat::G12X4B12X4R12X42Plane444Unorm3Pack16EXT;
const VkFormat VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT = VkFormat::G16B16R162Plane444UnormEXT;
const VkFormat VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT = VkFormat::A4R4G4B4UnormPack16EXT;
const VkFormat VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT = VkFormat::A4B4G4R4UnormPack16EXT;
const VkFormat VK_FORMAT_G8B8G8R8_422_UNORM = VkFormat::G8B8G8R8422Unorm;
const VkFormat VK_FORMAT_B8G8R8G8_422_UNORM = VkFormat::B8G8R8G8422Unorm;
const VkFormat VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM = VkFormat::G8B8R83Plane420Unorm;
const VkFormat VK_FORMAT_G8_B8R8_2PLANE_420_UNORM = VkFormat::G8B8R82Plane420Unorm;
const VkFormat VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM = VkFormat::G8B8R83Plane422Unorm;
const VkFormat VK_FORMAT_G8_B8R8_2PLANE_422_UNORM = VkFormat::G8B8R82Plane422Unorm;
const VkFormat VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM = VkFormat::G8B8R83Plane444Unorm;
const VkFormat VK_FORMAT_R10X6_UNORM_PACK16 = VkFormat::R10X6UnormPack16;
const VkFormat VK_FORMAT_R10X6G10X6_UNORM_2PACK16 = VkFormat::R10X6G10X6Unorm2Pack16;
const VkFormat VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 = VkFormat::R10X6G10X6B10X6A10X6Unorm4Pack16;
const VkFormat VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = VkFormat::G10X6B10X6G10X6R10X6422Unorm4Pack16;
const VkFormat VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = VkFormat::B10X6G10X6R10X6G10X6422Unorm4Pack16;
const VkFormat VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = VkFormat::G10X6B10X6R10X63Plane420Unorm3Pack16;
const VkFormat VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = VkFormat::G10X6B10X6R10X62Plane420Unorm3Pack16;
const VkFormat VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = VkFormat::G10X6B10X6R10X63Plane422Unorm3Pack16;
const VkFormat VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = VkFormat::G10X6B10X6R10X62Plane422Unorm3Pack16;
const VkFormat VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = VkFormat::G10X6B10X6R10X63Plane444Unorm3Pack16;
const VkFormat VK_FORMAT_R12X4_UNORM_PACK16 = VkFormat::R12X4UnormPack16;
const VkFormat VK_FORMAT_R12X4G12X4_UNORM_2PACK16 = VkFormat::R12X4G12X4Unorm2Pack16;
const VkFormat VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 = VkFormat::R12X4G12X4B12X4A12X4Unorm4Pack16;
const VkFormat VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = VkFormat::G12X4B12X4G12X4R12X4422Unorm4Pack16;
const VkFormat VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = VkFormat::B12X4G12X4R12X4G12X4422Unorm4Pack16;
const VkFormat VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = VkFormat::G12X4B12X4R12X43Plane420Unorm3Pack16;
const VkFormat VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = VkFormat::G12X4B12X4R12X42Plane420Unorm3Pack16;
const VkFormat VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = VkFormat::G12X4B12X4R12X43Plane422Unorm3Pack16;
const VkFormat VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = VkFormat::G12X4B12X4R12X42Plane422Unorm3Pack16;
const VkFormat VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = VkFormat::G12X4B12X4R12X43Plane444Unorm3Pack16;
const VkFormat VK_FORMAT_G16B16G16R16_422_UNORM = VkFormat::G16B16G16R16422Unorm;
const VkFormat VK_FORMAT_B16G16R16G16_422_UNORM = VkFormat::B16G16R16G16422Unorm;
const VkFormat VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM = VkFormat::G16B16R163Plane420Unorm;
const VkFormat VK_FORMAT_G16_B16R16_2PLANE_420_UNORM = VkFormat::G16B16R162Plane420Unorm;
const VkFormat VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM = VkFormat::G16B16R163Plane422Unorm;
const VkFormat VK_FORMAT_G16_B16R16_2PLANE_422_UNORM = VkFormat::G16B16R162Plane422Unorm;
const VkFormat VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM = VkFormat::G16B16R163Plane444Unorm;
enum class VkFrontFace : uint32_t {
    CounterClockwise = 0,
    Clockwise = 1,
};
const VkFrontFace VK_FRONT_FACE_COUNTER_CLOCKWISE = VkFrontFace::CounterClockwise;
const VkFrontFace VK_FRONT_FACE_CLOCKWISE = VkFrontFace::Clockwise;
enum class VkImageLayout : uint32_t {
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
    VideoDecodeDstKHR = 1000024000,
    VideoDecodeSrcKHR = 1000024001,
    VideoDecodeDpbKHR = 1000024002,
    VideoEncodeDstKHR = 1000299000,
    VideoEncodeSrcKHR = 1000299001,
    VideoEncodeDpbKHR = 1000299002,
    SharedPresentKHR = 1000111000,
    ShadingRateOptimalNV = 1000164003,
    FragmentDensityMapOptimalEXT = 1000218000,
    ReadOnlyOptimalKHR = 1000314000,
    AttachmentOptimalKHR = 1000314001,
    DepthReadOnlyStencilAttachmentOptimal = 1000117000,
    DepthAttachmentStencilReadOnlyOptimal = 1000117001,
    DepthAttachmentOptimal = 1000241000,
    DepthReadOnlyOptimal = 1000241001,
    StencilAttachmentOptimal = 1000241002,
    StencilReadOnlyOptimal = 1000241003,
};
const VkImageLayout VK_IMAGE_LAYOUT_UNDEFINED = VkImageLayout::Undefined;
const VkImageLayout VK_IMAGE_LAYOUT_GENERAL = VkImageLayout::General;
const VkImageLayout VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL = VkImageLayout::ColorAttachmentOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = VkImageLayout::DepthStencilAttachmentOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL = VkImageLayout::DepthStencilReadOnlyOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL = VkImageLayout::ShaderReadOnlyOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL = VkImageLayout::TransferSrcOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL = VkImageLayout::TransferDstOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_PREINITIALIZED = VkImageLayout::Preinitialized;
const VkImageLayout VK_IMAGE_LAYOUT_PRESENT_SRC_KHR = VkImageLayout::PresentSrcKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR = VkImageLayout::VideoDecodeDstKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_DECODE_SRC_KHR = VkImageLayout::VideoDecodeSrcKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR = VkImageLayout::VideoDecodeDpbKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_ENCODE_DST_KHR = VkImageLayout::VideoEncodeDstKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_ENCODE_SRC_KHR = VkImageLayout::VideoEncodeSrcKHR;
const VkImageLayout VK_IMAGE_LAYOUT_VIDEO_ENCODE_DPB_KHR = VkImageLayout::VideoEncodeDpbKHR;
const VkImageLayout VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR = VkImageLayout::SharedPresentKHR;
const VkImageLayout VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV = VkImageLayout::ShadingRateOptimalNV;
const VkImageLayout VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT = VkImageLayout::FragmentDensityMapOptimalEXT;
const VkImageLayout VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR = VkImageLayout::ReadOnlyOptimalKHR;
const VkImageLayout VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR = VkImageLayout::AttachmentOptimalKHR;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL = VkImageLayout::DepthReadOnlyStencilAttachmentOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL = VkImageLayout::DepthAttachmentStencilReadOnlyOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL = VkImageLayout::DepthAttachmentOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL = VkImageLayout::DepthReadOnlyOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL = VkImageLayout::StencilAttachmentOptimal;
const VkImageLayout VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL = VkImageLayout::StencilReadOnlyOptimal;
enum class VkImageTiling : uint32_t {
    Optimal = 0,
    Linear = 1,
    DrmFormatModifierEXT = 1000158000,
};
const VkImageTiling VK_IMAGE_TILING_OPTIMAL = VkImageTiling::Optimal;
const VkImageTiling VK_IMAGE_TILING_LINEAR = VkImageTiling::Linear;
const VkImageTiling VK_IMAGE_TILING_DRM_FORMAT_MODIFIER_EXT = VkImageTiling::DrmFormatModifierEXT;
enum class VkImageType : uint32_t {
    e1D = 0,
    e2D = 1,
    e3D = 2,
};
const VkImageType VK_IMAGE_TYPE_1D = VkImageType::e1D;
const VkImageType VK_IMAGE_TYPE_2D = VkImageType::e2D;
const VkImageType VK_IMAGE_TYPE_3D = VkImageType::e3D;
enum class VkImageViewType : uint32_t {
    e1D = 0,
    e2D = 1,
    e3D = 2,
    Cube = 3,
    e1DArray = 4,
    e2DArray = 5,
    CubeArray = 6,
};
const VkImageViewType VK_IMAGE_VIEW_TYPE_1D = VkImageViewType::e1D;
const VkImageViewType VK_IMAGE_VIEW_TYPE_2D = VkImageViewType::e2D;
const VkImageViewType VK_IMAGE_VIEW_TYPE_3D = VkImageViewType::e3D;
const VkImageViewType VK_IMAGE_VIEW_TYPE_CUBE = VkImageViewType::Cube;
const VkImageViewType VK_IMAGE_VIEW_TYPE_1D_ARRAY = VkImageViewType::e1DArray;
const VkImageViewType VK_IMAGE_VIEW_TYPE_2D_ARRAY = VkImageViewType::e2DArray;
const VkImageViewType VK_IMAGE_VIEW_TYPE_CUBE_ARRAY = VkImageViewType::CubeArray;
enum class VkSharingMode : uint32_t {
    Exclusive = 0,
    Concurrent = 1,
};
const VkSharingMode VK_SHARING_MODE_EXCLUSIVE = VkSharingMode::Exclusive;
const VkSharingMode VK_SHARING_MODE_CONCURRENT = VkSharingMode::Concurrent;
enum class VkIndexType : uint32_t {
    Uint16 = 0,
    Uint32 = 1,
    NoneKHR = 1000165000,
    Uint8EXT = 1000265000,
};
const VkIndexType VK_INDEX_TYPE_UINT16 = VkIndexType::Uint16;
const VkIndexType VK_INDEX_TYPE_UINT32 = VkIndexType::Uint32;
const VkIndexType VK_INDEX_TYPE_NONE_KHR = VkIndexType::NoneKHR;
const VkIndexType VK_INDEX_TYPE_UINT8_EXT = VkIndexType::Uint8EXT;
enum class VkLogicOp : uint32_t {
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
const VkLogicOp VK_LOGIC_OP_CLEAR = VkLogicOp::Clear;
const VkLogicOp VK_LOGIC_OP_AND = VkLogicOp::And;
const VkLogicOp VK_LOGIC_OP_AND_REVERSE = VkLogicOp::AndReverse;
const VkLogicOp VK_LOGIC_OP_COPY = VkLogicOp::Copy;
const VkLogicOp VK_LOGIC_OP_AND_INVERTED = VkLogicOp::AndInverted;
const VkLogicOp VK_LOGIC_OP_NO_OP = VkLogicOp::NoOp;
const VkLogicOp VK_LOGIC_OP_XOR = VkLogicOp::Xor;
const VkLogicOp VK_LOGIC_OP_OR = VkLogicOp::Or;
const VkLogicOp VK_LOGIC_OP_NOR = VkLogicOp::Nor;
const VkLogicOp VK_LOGIC_OP_EQUIVALENT = VkLogicOp::Equivalent;
const VkLogicOp VK_LOGIC_OP_INVERT = VkLogicOp::Invert;
const VkLogicOp VK_LOGIC_OP_OR_REVERSE = VkLogicOp::OrReverse;
const VkLogicOp VK_LOGIC_OP_COPY_INVERTED = VkLogicOp::CopyInverted;
const VkLogicOp VK_LOGIC_OP_OR_INVERTED = VkLogicOp::OrInverted;
const VkLogicOp VK_LOGIC_OP_NAND = VkLogicOp::Nand;
const VkLogicOp VK_LOGIC_OP_SET = VkLogicOp::Set;
enum class VkPhysicalDeviceType : uint32_t {
    Other = 0,
    IntegratedGpu = 1,
    DiscreteGpu = 2,
    VirtualGpu = 3,
    Cpu = 4,
};
const VkPhysicalDeviceType VK_PHYSICAL_DEVICE_TYPE_OTHER = VkPhysicalDeviceType::Other;
const VkPhysicalDeviceType VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU = VkPhysicalDeviceType::IntegratedGpu;
const VkPhysicalDeviceType VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU = VkPhysicalDeviceType::DiscreteGpu;
const VkPhysicalDeviceType VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU = VkPhysicalDeviceType::VirtualGpu;
const VkPhysicalDeviceType VK_PHYSICAL_DEVICE_TYPE_CPU = VkPhysicalDeviceType::Cpu;
enum class VkPipelineBindPoint : uint32_t {
    Graphics = 0,
    Compute = 1,
    RayTracingKHR = 1000165000,
};
const VkPipelineBindPoint VK_PIPELINE_BIND_POINT_GRAPHICS = VkPipelineBindPoint::Graphics;
const VkPipelineBindPoint VK_PIPELINE_BIND_POINT_COMPUTE = VkPipelineBindPoint::Compute;
const VkPipelineBindPoint VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR = VkPipelineBindPoint::RayTracingKHR;
enum class VkPrimitiveTopology : uint32_t {
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
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_POINT_LIST = VkPrimitiveTopology::PointList;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_LINE_LIST = VkPrimitiveTopology::LineList;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = VkPrimitiveTopology::LineStrip;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = VkPrimitiveTopology::TriangleList;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = VkPrimitiveTopology::TriangleStrip;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = VkPrimitiveTopology::TriangleFan;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = VkPrimitiveTopology::LineListWithAdjacency;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = VkPrimitiveTopology::LineStripWithAdjacency;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = VkPrimitiveTopology::TriangleListWithAdjacency;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = VkPrimitiveTopology::TriangleStripWithAdjacency;
const VkPrimitiveTopology VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = VkPrimitiveTopology::PatchList;
enum class VkQueryType : uint32_t {
    Occlusion = 0,
    PipelineStatistics = 1,
    Timestamp = 2,
    ResultStatusOnlyKHR = 1000023000,
    VideoEncodeBitstreamBufferRangeKHR = 1000299000,
    TransformFeedbackStreamEXT = 1000028004,
    PerformanceQueryKHR = 1000116000,
    AccelerationStructureCompactedSizeKHR = 1000150000,
    AccelerationStructureSerializationSizeKHR = 1000150001,
    AccelerationStructureCompactedSizeNV = 1000165000,
    PerformanceQueryINTEL = 1000210000,
};
const VkQueryType VK_QUERY_TYPE_OCCLUSION = VkQueryType::Occlusion;
const VkQueryType VK_QUERY_TYPE_PIPELINE_STATISTICS = VkQueryType::PipelineStatistics;
const VkQueryType VK_QUERY_TYPE_TIMESTAMP = VkQueryType::Timestamp;
const VkQueryType VK_QUERY_TYPE_RESULT_STATUS_ONLY_KHR = VkQueryType::ResultStatusOnlyKHR;
const VkQueryType VK_QUERY_TYPE_VIDEO_ENCODE_BITSTREAM_BUFFER_RANGE_KHR = VkQueryType::VideoEncodeBitstreamBufferRangeKHR;
const VkQueryType VK_QUERY_TYPE_TRANSFORM_FEEDBACK_STREAM_EXT = VkQueryType::TransformFeedbackStreamEXT;
const VkQueryType VK_QUERY_TYPE_PERFORMANCE_QUERY_KHR = VkQueryType::PerformanceQueryKHR;
const VkQueryType VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR = VkQueryType::AccelerationStructureCompactedSizeKHR;
const VkQueryType VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR = VkQueryType::AccelerationStructureSerializationSizeKHR;
const VkQueryType VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV = VkQueryType::AccelerationStructureCompactedSizeNV;
const VkQueryType VK_QUERY_TYPE_PERFORMANCE_QUERY_INTEL = VkQueryType::PerformanceQueryINTEL;
enum class VkSubpassContents : uint32_t {
    Inline = 0,
    SecondaryCommandBuffers = 1,
};
const VkSubpassContents VK_SUBPASS_CONTENTS_INLINE = VkSubpassContents::Inline;
const VkSubpassContents VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS = VkSubpassContents::SecondaryCommandBuffers;
enum class VkResult : int32_t {
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
const VkResult VK_SUCCESS = VkResult::Success;
const VkResult VK_NOT_READY = VkResult::NotReady;
const VkResult VK_TIMEOUT = VkResult::Timeout;
const VkResult VK_EVENT_SET = VkResult::EventSet;
const VkResult VK_EVENT_RESET = VkResult::EventReset;
const VkResult VK_INCOMPLETE = VkResult::Incomplete;
const VkResult VK_ERROR_OUT_OF_HOST_MEMORY = VkResult::ErrorOutOfHostMemory;
const VkResult VK_ERROR_OUT_OF_DEVICE_MEMORY = VkResult::ErrorOutOfDeviceMemory;
const VkResult VK_ERROR_INITIALIZATION_FAILED = VkResult::ErrorInitializationFailed;
const VkResult VK_ERROR_DEVICE_LOST = VkResult::ErrorDeviceLost;
const VkResult VK_ERROR_MEMORY_MAP_FAILED = VkResult::ErrorMemoryMapFailed;
const VkResult VK_ERROR_LAYER_NOT_PRESENT = VkResult::ErrorLayerNotPresent;
const VkResult VK_ERROR_EXTENSION_NOT_PRESENT = VkResult::ErrorExtensionNotPresent;
const VkResult VK_ERROR_FEATURE_NOT_PRESENT = VkResult::ErrorFeatureNotPresent;
const VkResult VK_ERROR_INCOMPATIBLE_DRIVER = VkResult::ErrorIncompatibleDriver;
const VkResult VK_ERROR_TOO_MANY_OBJECTS = VkResult::ErrorTooManyObjects;
const VkResult VK_ERROR_FORMAT_NOT_SUPPORTED = VkResult::ErrorFormatNotSupported;
const VkResult VK_ERROR_FRAGMENTED_POOL = VkResult::ErrorFragmentedPool;
const VkResult VK_ERROR_UNKNOWN = VkResult::ErrorUnknown;
const VkResult VK_ERROR_SURFACE_LOST_KHR = VkResult::ErrorSurfaceLostKHR;
const VkResult VK_ERROR_NATIVE_WINDOW_IN_USE_KHR = VkResult::ErrorNativeWindowInUseKHR;
const VkResult VK_SUBOPTIMAL_KHR = VkResult::SuboptimalKHR;
const VkResult VK_ERROR_OUT_OF_DATE_KHR = VkResult::ErrorOutOfDateKHR;
const VkResult VK_ERROR_INCOMPATIBLE_DISPLAY_KHR = VkResult::ErrorIncompatibleDisplayKHR;
const VkResult VK_ERROR_VALIDATION_FAILED_EXT = VkResult::ErrorValidationFailedEXT;
const VkResult VK_ERROR_INVALID_SHADER_NV = VkResult::ErrorInvalidShaderNV;
const VkResult VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT = VkResult::ErrorInvalidDrmFormatModifierPlaneLayoutEXT;
const VkResult VK_ERROR_NOT_PERMITTED_EXT = VkResult::ErrorNotPermittedEXT;
const VkResult VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT = VkResult::ErrorFullScreenExclusiveModeLostEXT;
const VkResult VK_THREAD_IDLE_KHR = VkResult::ThreadIdleKHR;
const VkResult VK_THREAD_DONE_KHR = VkResult::ThreadDoneKHR;
const VkResult VK_OPERATION_DEFERRED_KHR = VkResult::OperationDeferredKHR;
const VkResult VK_OPERATION_NOT_DEFERRED_KHR = VkResult::OperationNotDeferredKHR;
const VkResult VK_PIPELINE_COMPILE_REQUIRED_EXT = VkResult::PipelineCompileRequiredEXT;
const VkResult VK_ERROR_OUT_OF_POOL_MEMORY = VkResult::ErrorOutOfPoolMemory;
const VkResult VK_ERROR_INVALID_EXTERNAL_HANDLE = VkResult::ErrorInvalidExternalHandle;
const VkResult VK_ERROR_FRAGMENTATION = VkResult::ErrorFragmentation;
const VkResult VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS = VkResult::ErrorInvalidOpaqueCaptureAddress;
enum class VkStencilOp : uint32_t {
    Keep = 0,
    Zero = 1,
    Replace = 2,
    IncrementAndClamp = 3,
    DecrementAndClamp = 4,
    Invert = 5,
    IncrementAndWrap = 6,
    DecrementAndWrap = 7,
};
const VkStencilOp VK_STENCIL_OP_KEEP = VkStencilOp::Keep;
const VkStencilOp VK_STENCIL_OP_ZERO = VkStencilOp::Zero;
const VkStencilOp VK_STENCIL_OP_REPLACE = VkStencilOp::Replace;
const VkStencilOp VK_STENCIL_OP_INCREMENT_AND_CLAMP = VkStencilOp::IncrementAndClamp;
const VkStencilOp VK_STENCIL_OP_DECREMENT_AND_CLAMP = VkStencilOp::DecrementAndClamp;
const VkStencilOp VK_STENCIL_OP_INVERT = VkStencilOp::Invert;
const VkStencilOp VK_STENCIL_OP_INCREMENT_AND_WRAP = VkStencilOp::IncrementAndWrap;
const VkStencilOp VK_STENCIL_OP_DECREMENT_AND_WRAP = VkStencilOp::DecrementAndWrap;
enum class VkStructureType : uint32_t {
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
    VideoProfileKHR = 1000023000,
    VideoCapabilitiesKHR = 1000023001,
    VideoPictureResourceKHR = 1000023002,
    VideoGetMemoryPropertiesKHR = 1000023003,
    VideoBindMemoryKHR = 1000023004,
    VideoSessionCreateInfoKHR = 1000023005,
    VideoSessionParametersCreateInfoKHR = 1000023006,
    VideoSessionParametersUpdateInfoKHR = 1000023007,
    VideoBeginCodingInfoKHR = 1000023008,
    VideoEndCodingInfoKHR = 1000023009,
    VideoCodingControlInfoKHR = 1000023010,
    VideoReferenceSlotKHR = 1000023011,
    VideoQueueFamilyProperties2KHR = 1000023012,
    VideoProfilesKHR = 1000023013,
    PhysicalDeviceVideoFormatInfoKHR = 1000023014,
    VideoFormatPropertiesKHR = 1000023015,
    VideoDecodeInfoKHR = 1000024000,
    VideoEncodeInfoKHR = 1000299000,
    VideoEncodeRateControlInfoKHR = 1000299001,
    DedicatedAllocationImageCreateInfoNV = 1000026000,
    DedicatedAllocationBufferCreateInfoNV = 1000026001,
    DedicatedAllocationMemoryAllocateInfoNV = 1000026002,
    PhysicalDeviceTransformFeedbackFeaturesEXT = 1000028000,
    PhysicalDeviceTransformFeedbackPropertiesEXT = 1000028001,
    PipelineRasterizationStateStreamCreateInfoEXT = 1000028002,
    ImageViewHandleInfoNVX = 1000030000,
    ImageViewAddressPropertiesNVX = 1000030001,
    VideoEncodeH264CapabilitiesEXT = 1000038000,
    VideoEncodeH264SessionCreateInfoEXT = 1000038001,
    VideoEncodeH264SessionParametersCreateInfoEXT = 1000038002,
    VideoEncodeH264SessionParametersAddInfoEXT = 1000038003,
    VideoEncodeH264VclFrameInfoEXT = 1000038004,
    VideoEncodeH264DpbSlotInfoEXT = 1000038005,
    VideoEncodeH264NaluSliceEXT = 1000038006,
    VideoEncodeH264EmitPictureParametersEXT = 1000038007,
    VideoEncodeH264ProfileEXT = 1000038008,
    VideoDecodeH264CapabilitiesEXT = 1000040000,
    VideoDecodeH264SessionCreateInfoEXT = 1000040001,
    VideoDecodeH264PictureInfoEXT = 1000040002,
    VideoDecodeH264MvcEXT = 1000040003,
    VideoDecodeH264ProfileEXT = 1000040004,
    VideoDecodeH264SessionParametersCreateInfoEXT = 1000040005,
    VideoDecodeH264SessionParametersAddInfoEXT = 1000040006,
    VideoDecodeH264DpbSlotInfoEXT = 1000040007,
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
    VideoDecodeH265CapabilitiesEXT = 1000187000,
    VideoDecodeH265SessionCreateInfoEXT = 1000187001,
    VideoDecodeH265SessionParametersCreateInfoEXT = 1000187002,
    VideoDecodeH265SessionParametersAddInfoEXT = 1000187003,
    VideoDecodeH265ProfileEXT = 1000187004,
    VideoDecodeH265PictureInfoEXT = 1000187005,
    VideoDecodeH265DpbSlotInfoEXT = 1000187006,
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
    PhysicalDeviceInheritedViewportScissorFeaturesNV = 1000278000,
    CommandBufferInheritanceViewportScissorInfoNV = 1000278001,
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
    MemoryBarrier2KHR = 1000314000,
    BufferMemoryBarrier2KHR = 1000314001,
    ImageMemoryBarrier2KHR = 1000314002,
    DependencyInfoKHR = 1000314003,
    SubmitInfo2KHR = 1000314004,
    SemaphoreSubmitInfoKHR = 1000314005,
    CommandBufferSubmitInfoKHR = 1000314006,
    PhysicalDeviceSynchronization2FeaturesKHR = 1000314007,
    QueueFamilyCheckpointProperties2NV = 1000314008,
    CheckpointData2NV = 1000314009,
    PhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR = 1000325000,
    PhysicalDeviceFragmentShadingRateEnumsPropertiesNV = 1000326000,
    PhysicalDeviceFragmentShadingRateEnumsFeaturesNV = 1000326001,
    PipelineFragmentShadingRateEnumStateCreateInfoNV = 1000326002,
    PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT = 1000330000,
    PhysicalDeviceFragmentDensityMap2FeaturesEXT = 1000332000,
    PhysicalDeviceFragmentDensityMap2PropertiesEXT = 1000332001,
    CopyCommandTransformInfoQCOM = 1000333000,
    PhysicalDeviceImageRobustnessFeaturesEXT = 1000335000,
    PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR = 1000336000,
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
    PhysicalDeviceMutableDescriptorTypeFeaturesVALVE = 1000351000,
    MutableDescriptorTypeCreateInfoVALVE = 1000351002,
    PhysicalDeviceVertexInputDynamicStateFeaturesEXT = 1000352000,
    VertexInputBindingDescription2EXT = 1000352001,
    VertexInputAttributeDescription2EXT = 1000352002,
    ImportMemoryZirconHandleInfoFUCHSIA = 1000364000,
    MemoryZirconHandlePropertiesFUCHSIA = 1000364001,
    MemoryGetZirconHandleInfoFUCHSIA = 1000364002,
    ImportSemaphoreZirconHandleInfoFUCHSIA = 1000365000,
    SemaphoreGetZirconHandleInfoFUCHSIA = 1000365001,
    PhysicalDeviceExtendedDynamicState2FeaturesEXT = 1000377000,
    ScreenSurfaceCreateInfoQNX = 1000378000,
    PhysicalDeviceColorWriteEnableFeaturesEXT = 1000381000,
    PipelineColorWriteCreateInfoEXT = 1000381001,
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
const VkStructureType VK_STRUCTURE_TYPE_APPLICATION_INFO = VkStructureType::ApplicationInfo;
const VkStructureType VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO = VkStructureType::InstanceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO = VkStructureType::DeviceQueueCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO = VkStructureType::DeviceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SUBMIT_INFO = VkStructureType::SubmitInfo;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO = VkStructureType::MemoryAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE = VkStructureType::MappedMemoryRange;
const VkStructureType VK_STRUCTURE_TYPE_BIND_SPARSE_INFO = VkStructureType::BindSparseInfo;
const VkStructureType VK_STRUCTURE_TYPE_FENCE_CREATE_INFO = VkStructureType::FenceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO = VkStructureType::SemaphoreCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_EVENT_CREATE_INFO = VkStructureType::EventCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO = VkStructureType::QueryPoolCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO = VkStructureType::BufferCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO = VkStructureType::BufferViewCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO = VkStructureType::ImageCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO = VkStructureType::ImageViewCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO = VkStructureType::ShaderModuleCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO = VkStructureType::PipelineCacheCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO = VkStructureType::PipelineShaderStageCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO = VkStructureType::PipelineVertexInputStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO = VkStructureType::PipelineInputAssemblyStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO = VkStructureType::PipelineTessellationStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO = VkStructureType::PipelineViewportStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO = VkStructureType::PipelineRasterizationStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO = VkStructureType::PipelineMultisampleStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO = VkStructureType::PipelineDepthStencilStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO = VkStructureType::PipelineColorBlendStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO = VkStructureType::PipelineDynamicStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO = VkStructureType::GraphicsPipelineCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO = VkStructureType::ComputePipelineCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO = VkStructureType::PipelineLayoutCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO = VkStructureType::SamplerCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO = VkStructureType::DescriptorSetLayoutCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO = VkStructureType::DescriptorPoolCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO = VkStructureType::DescriptorSetAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET = VkStructureType::WriteDescriptorSet;
const VkStructureType VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET = VkStructureType::CopyDescriptorSet;
const VkStructureType VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO = VkStructureType::FramebufferCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO = VkStructureType::RenderPassCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO = VkStructureType::CommandPoolCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO = VkStructureType::CommandBufferAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO = VkStructureType::CommandBufferInheritanceInfo;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO = VkStructureType::CommandBufferBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO = VkStructureType::RenderPassBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER = VkStructureType::BufferMemoryBarrier;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER = VkStructureType::ImageMemoryBarrier;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_BARRIER = VkStructureType::MemoryBarrier;
const VkStructureType VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO = VkStructureType::LoaderInstanceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO = VkStructureType::LoaderDeviceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR = VkStructureType::SwapchainCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PRESENT_INFO_KHR = VkStructureType::PresentInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_CAPABILITIES_KHR = VkStructureType::DeviceGroupPresentCapabilitiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_SWAPCHAIN_CREATE_INFO_KHR = VkStructureType::ImageSwapchainCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_SWAPCHAIN_INFO_KHR = VkStructureType::BindImageMemorySwapchainInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR = VkStructureType::AcquireNextImageInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_PRESENT_INFO_KHR = VkStructureType::DeviceGroupPresentInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR = VkStructureType::DeviceGroupSwapchainCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR = VkStructureType::DisplayModeCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR = VkStructureType::DisplaySurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_PRESENT_INFO_KHR = VkStructureType::DisplayPresentInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR = VkStructureType::XlibSurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR = VkStructureType::XcbSurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR = VkStructureType::WaylandSurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR = VkStructureType::AndroidSurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR = VkStructureType::Win32SurfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT = VkStructureType::DebugReportCallbackCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_RASTERIZATION_ORDER_AMD = VkStructureType::PipelineRasterizationStateRasterizationOrderAMD;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT = VkStructureType::DebugMarkerObjectNameInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT = VkStructureType::DebugMarkerObjectTagInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT = VkStructureType::DebugMarkerMarkerInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_PROFILE_KHR = VkStructureType::VideoProfileKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR = VkStructureType::VideoCapabilitiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_KHR = VkStructureType::VideoPictureResourceKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_GET_MEMORY_PROPERTIES_KHR = VkStructureType::VideoGetMemoryPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_BIND_MEMORY_KHR = VkStructureType::VideoBindMemoryKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR = VkStructureType::VideoSessionCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR = VkStructureType::VideoSessionParametersCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR = VkStructureType::VideoSessionParametersUpdateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR = VkStructureType::VideoBeginCodingInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR = VkStructureType::VideoEndCodingInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR = VkStructureType::VideoCodingControlInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_KHR = VkStructureType::VideoReferenceSlotKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_QUEUE_FAMILY_PROPERTIES_2_KHR = VkStructureType::VideoQueueFamilyProperties2KHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_PROFILES_KHR = VkStructureType::VideoProfilesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR = VkStructureType::PhysicalDeviceVideoFormatInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR = VkStructureType::VideoFormatPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR = VkStructureType::VideoDecodeInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_INFO_KHR = VkStructureType::VideoEncodeInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_RATE_CONTROL_INFO_KHR = VkStructureType::VideoEncodeRateControlInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_IMAGE_CREATE_INFO_NV = VkStructureType::DedicatedAllocationImageCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_BUFFER_CREATE_INFO_NV = VkStructureType::DedicatedAllocationBufferCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_DEDICATED_ALLOCATION_MEMORY_ALLOCATE_INFO_NV = VkStructureType::DedicatedAllocationMemoryAllocateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_FEATURES_EXT = VkStructureType::PhysicalDeviceTransformFeedbackFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TRANSFORM_FEEDBACK_PROPERTIES_EXT = VkStructureType::PhysicalDeviceTransformFeedbackPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT = VkStructureType::PipelineRasterizationStateStreamCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX = VkStructureType::ImageViewHandleInfoNVX;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX = VkStructureType::ImageViewAddressPropertiesNVX;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_EXT = VkStructureType::VideoEncodeH264CapabilitiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_CREATE_INFO_EXT = VkStructureType::VideoEncodeH264SessionCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT = VkStructureType::VideoEncodeH264SessionParametersCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT = VkStructureType::VideoEncodeH264SessionParametersAddInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_VCL_FRAME_INFO_EXT = VkStructureType::VideoEncodeH264VclFrameInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_DPB_SLOT_INFO_EXT = VkStructureType::VideoEncodeH264DpbSlotInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_NALU_SLICE_EXT = VkStructureType::VideoEncodeH264NaluSliceEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_EMIT_PICTURE_PARAMETERS_EXT = VkStructureType::VideoEncodeH264EmitPictureParametersEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_PROFILE_EXT = VkStructureType::VideoEncodeH264ProfileEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_EXT = VkStructureType::VideoDecodeH264CapabilitiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_CREATE_INFO_EXT = VkStructureType::VideoDecodeH264SessionCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_EXT = VkStructureType::VideoDecodeH264PictureInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_MVC_EXT = VkStructureType::VideoDecodeH264MvcEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_EXT = VkStructureType::VideoDecodeH264ProfileEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_EXT = VkStructureType::VideoDecodeH264SessionParametersCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_EXT = VkStructureType::VideoDecodeH264SessionParametersAddInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_EXT = VkStructureType::VideoDecodeH264DpbSlotInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_TEXTURE_LOD_GATHER_FORMAT_PROPERTIES_AMD = VkStructureType::TextureLodGatherFormatPropertiesAMD;
const VkStructureType VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP = VkStructureType::StreamDescriptorSurfaceCreateInfoGGP;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CORNER_SAMPLED_IMAGE_FEATURES_NV = VkStructureType::PhysicalDeviceCornerSampledImageFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_NV = VkStructureType::ExternalMemoryImageCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO_NV = VkStructureType::ExportMemoryAllocateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_NV = VkStructureType::ImportMemoryWin32HandleInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_NV = VkStructureType::ExportMemoryWin32HandleInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV = VkStructureType::Win32KeyedMutexAcquireReleaseInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_VALIDATION_FLAGS_EXT = VkStructureType::ValidationFlagsEXT;
const VkStructureType VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN = VkStructureType::ViSurfaceCreateInfoNN;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXTURE_COMPRESSION_ASTC_HDR_FEATURES_EXT = VkStructureType::PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_VIEW_ASTC_DECODE_MODE_EXT = VkStructureType::ImageViewAstcDecodeModeEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ASTC_DECODE_FEATURES_EXT = VkStructureType::PhysicalDeviceAstcDecodeFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR = VkStructureType::ImportMemoryWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR = VkStructureType::ExportMemoryWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_WIN32_HANDLE_PROPERTIES_KHR = VkStructureType::MemoryWin32HandlePropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_GET_WIN32_HANDLE_INFO_KHR = VkStructureType::MemoryGetWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR = VkStructureType::ImportMemoryFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR = VkStructureType::MemoryFdPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR = VkStructureType::MemoryGetFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR = VkStructureType::Win32KeyedMutexAcquireReleaseInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR = VkStructureType::ImportSemaphoreWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR = VkStructureType::ExportSemaphoreWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR = VkStructureType::D3D12FenceSubmitInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_GET_WIN32_HANDLE_INFO_KHR = VkStructureType::SemaphoreGetWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR = VkStructureType::ImportSemaphoreFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR = VkStructureType::SemaphoreGetFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR = VkStructureType::PhysicalDevicePushDescriptorPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_CONDITIONAL_RENDERING_INFO_EXT = VkStructureType::CommandBufferInheritanceConditionalRenderingInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONDITIONAL_RENDERING_FEATURES_EXT = VkStructureType::PhysicalDeviceConditionalRenderingFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_CONDITIONAL_RENDERING_BEGIN_INFO_EXT = VkStructureType::ConditionalRenderingBeginInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PRESENT_REGIONS_KHR = VkStructureType::PresentRegionsKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_W_SCALING_STATE_CREATE_INFO_NV = VkStructureType::PipelineViewportWScalingStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_EXT = VkStructureType::SurfaceCapabilities2EXT;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_POWER_INFO_EXT = VkStructureType::DisplayPowerInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_EVENT_INFO_EXT = VkStructureType::DeviceEventInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_EVENT_INFO_EXT = VkStructureType::DisplayEventInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_SWAPCHAIN_COUNTER_CREATE_INFO_EXT = VkStructureType::SwapchainCounterCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PRESENT_TIMES_INFO_GOOGLE = VkStructureType::PresentTimesInfoGOOGLE;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PER_VIEW_ATTRIBUTES_PROPERTIES_NVX = VkStructureType::PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SWIZZLE_STATE_CREATE_INFO_NV = VkStructureType::PipelineViewportSwizzleStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DISCARD_RECTANGLE_PROPERTIES_EXT = VkStructureType::PhysicalDeviceDiscardRectanglePropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_DISCARD_RECTANGLE_STATE_CREATE_INFO_EXT = VkStructureType::PipelineDiscardRectangleStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CONSERVATIVE_RASTERIZATION_PROPERTIES_EXT = VkStructureType::PhysicalDeviceConservativeRasterizationPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_CONSERVATIVE_STATE_CREATE_INFO_EXT = VkStructureType::PipelineRasterizationConservativeStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_CLIP_ENABLE_FEATURES_EXT = VkStructureType::PhysicalDeviceDepthClipEnableFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_DEPTH_CLIP_STATE_CREATE_INFO_EXT = VkStructureType::PipelineRasterizationDepthClipStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_HDR_METADATA_EXT = VkStructureType::HdrMetadataEXT;
const VkStructureType VK_STRUCTURE_TYPE_SHARED_PRESENT_SURFACE_CAPABILITIES_KHR = VkStructureType::SharedPresentSurfaceCapabilitiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_FENCE_WIN32_HANDLE_INFO_KHR = VkStructureType::ImportFenceWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_FENCE_WIN32_HANDLE_INFO_KHR = VkStructureType::ExportFenceWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_FENCE_GET_WIN32_HANDLE_INFO_KHR = VkStructureType::FenceGetWin32HandleInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_FENCE_FD_INFO_KHR = VkStructureType::ImportFenceFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_FENCE_GET_FD_INFO_KHR = VkStructureType::FenceGetFdInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_FEATURES_KHR = VkStructureType::PhysicalDevicePerformanceQueryFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PERFORMANCE_QUERY_PROPERTIES_KHR = VkStructureType::PhysicalDevicePerformanceQueryPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_CREATE_INFO_KHR = VkStructureType::QueryPoolPerformanceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR = VkStructureType::PerformanceQuerySubmitInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACQUIRE_PROFILING_LOCK_INFO_KHR = VkStructureType::AcquireProfilingLockInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_KHR = VkStructureType::PerformanceCounterKHR;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_COUNTER_DESCRIPTION_KHR = VkStructureType::PerformanceCounterDescriptionKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR = VkStructureType::PhysicalDeviceSurfaceInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR = VkStructureType::SurfaceCapabilities2KHR;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR = VkStructureType::SurfaceFormat2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_PROPERTIES_2_KHR = VkStructureType::DisplayProperties2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_PLANE_PROPERTIES_2_KHR = VkStructureType::DisplayPlaneProperties2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_MODE_PROPERTIES_2_KHR = VkStructureType::DisplayModeProperties2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_PLANE_INFO_2_KHR = VkStructureType::DisplayPlaneInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_PLANE_CAPABILITIES_2_KHR = VkStructureType::DisplayPlaneCapabilities2KHR;
const VkStructureType VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK = VkStructureType::IosSurfaceCreateInfoMVK;
const VkStructureType VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK = VkStructureType::MacosSurfaceCreateInfoMVK;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT = VkStructureType::DebugUtilsObjectNameInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT = VkStructureType::DebugUtilsObjectTagInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT = VkStructureType::DebugUtilsLabelEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT = VkStructureType::DebugUtilsMessengerCallbackDataEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT = VkStructureType::DebugUtilsMessengerCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_USAGE_ANDROID = VkStructureType::AndroidHardwareBufferUsageANDROID;
const VkStructureType VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID = VkStructureType::AndroidHardwareBufferPropertiesANDROID;
const VkStructureType VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID = VkStructureType::AndroidHardwareBufferFormatPropertiesANDROID;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID = VkStructureType::ImportAndroidHardwareBufferInfoANDROID;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_GET_ANDROID_HARDWARE_BUFFER_INFO_ANDROID = VkStructureType::MemoryGetAndroidHardwareBufferInfoANDROID;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_FORMAT_ANDROID = VkStructureType::ExternalFormatANDROID;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_FEATURES_EXT = VkStructureType::PhysicalDeviceInlineUniformBlockFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INLINE_UNIFORM_BLOCK_PROPERTIES_EXT = VkStructureType::PhysicalDeviceInlineUniformBlockPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT = VkStructureType::WriteDescriptorSetInlineUniformBlockEXT;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_INLINE_UNIFORM_BLOCK_CREATE_INFO_EXT = VkStructureType::DescriptorPoolInlineUniformBlockCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLE_LOCATIONS_INFO_EXT = VkStructureType::SampleLocationsInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_SAMPLE_LOCATIONS_BEGIN_INFO_EXT = VkStructureType::RenderPassSampleLocationsBeginInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_SAMPLE_LOCATIONS_STATE_CREATE_INFO_EXT = VkStructureType::PipelineSampleLocationsStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLE_LOCATIONS_PROPERTIES_EXT = VkStructureType::PhysicalDeviceSampleLocationsPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_MULTISAMPLE_PROPERTIES_EXT = VkStructureType::MultisamplePropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_FEATURES_EXT = VkStructureType::PhysicalDeviceBlendOperationAdvancedFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BLEND_OPERATION_ADVANCED_PROPERTIES_EXT = VkStructureType::PhysicalDeviceBlendOperationAdvancedPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_ADVANCED_STATE_CREATE_INFO_EXT = VkStructureType::PipelineColorBlendAdvancedStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_TO_COLOR_STATE_CREATE_INFO_NV = VkStructureType::PipelineCoverageToColorStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR = VkStructureType::WriteDescriptorSetAccelerationStructureKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR = VkStructureType::AccelerationStructureBuildGeometryInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR = VkStructureType::AccelerationStructureDeviceAddressInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR = VkStructureType::AccelerationStructureGeometryAabbsDataKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR = VkStructureType::AccelerationStructureGeometryInstancesDataKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR = VkStructureType::AccelerationStructureGeometryTrianglesDataKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR = VkStructureType::AccelerationStructureGeometryKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR = VkStructureType::AccelerationStructureVersionInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR = VkStructureType::CopyAccelerationStructureInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_TO_MEMORY_INFO_KHR = VkStructureType::CopyAccelerationStructureToMemoryInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR = VkStructureType::CopyMemoryToAccelerationStructureInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR = VkStructureType::PhysicalDeviceAccelerationStructureFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR = VkStructureType::PhysicalDeviceAccelerationStructurePropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR = VkStructureType::AccelerationStructureCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR = VkStructureType::AccelerationStructureBuildSizesInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR = VkStructureType::PhysicalDeviceRayTracingPipelineFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR = VkStructureType::PhysicalDeviceRayTracingPipelinePropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR = VkStructureType::RayTracingPipelineCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR = VkStructureType::RayTracingShaderGroupCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR = VkStructureType::RayTracingPipelineInterfaceCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR = VkStructureType::PhysicalDeviceRayQueryFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_MODULATION_STATE_CREATE_INFO_NV = VkStructureType::PipelineCoverageModulationStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV = VkStructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_PROPERTIES_NV = VkStructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_DRM_FORMAT_MODIFIER_PROPERTIES_LIST_EXT = VkStructureType::DrmFormatModifierPropertiesListEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_DRM_FORMAT_MODIFIER_INFO_EXT = VkStructureType::PhysicalDeviceImageDrmFormatModifierInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_LIST_CREATE_INFO_EXT = VkStructureType::ImageDrmFormatModifierListCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_EXPLICIT_CREATE_INFO_EXT = VkStructureType::ImageDrmFormatModifierExplicitCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_DRM_FORMAT_MODIFIER_PROPERTIES_EXT = VkStructureType::ImageDrmFormatModifierPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VALIDATION_CACHE_CREATE_INFO_EXT = VkStructureType::ValidationCacheCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_SHADER_MODULE_VALIDATION_CACHE_CREATE_INFO_EXT = VkStructureType::ShaderModuleValidationCacheCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_FEATURES_KHR = VkStructureType::PhysicalDevicePortabilitySubsetFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PORTABILITY_SUBSET_PROPERTIES_KHR = VkStructureType::PhysicalDevicePortabilitySubsetPropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_SHADING_RATE_IMAGE_STATE_CREATE_INFO_NV = VkStructureType::PipelineViewportShadingRateImageStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_FEATURES_NV = VkStructureType::PhysicalDeviceShadingRateImageFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADING_RATE_IMAGE_PROPERTIES_NV = VkStructureType::PhysicalDeviceShadingRateImagePropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_COARSE_SAMPLE_ORDER_STATE_CREATE_INFO_NV = VkStructureType::PipelineViewportCoarseSampleOrderStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_NV = VkStructureType::RayTracingPipelineCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_NV = VkStructureType::AccelerationStructureCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_GEOMETRY_NV = VkStructureType::GeometryNV;
const VkStructureType VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV = VkStructureType::GeometryTrianglesNV;
const VkStructureType VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV = VkStructureType::GeometryAabbNV;
const VkStructureType VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV = VkStructureType::BindAccelerationStructureMemoryInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV = VkStructureType::WriteDescriptorSetAccelerationStructureNV;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV = VkStructureType::AccelerationStructureMemoryRequirementsInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PROPERTIES_NV = VkStructureType::PhysicalDeviceRayTracingPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_NV = VkStructureType::RayTracingShaderGroupCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_INFO_NV = VkStructureType::AccelerationStructureInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_REPRESENTATIVE_FRAGMENT_TEST_FEATURES_NV = VkStructureType::PhysicalDeviceRepresentativeFragmentTestFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_REPRESENTATIVE_FRAGMENT_TEST_STATE_CREATE_INFO_NV = VkStructureType::PipelineRepresentativeFragmentTestStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_VIEW_IMAGE_FORMAT_INFO_EXT = VkStructureType::PhysicalDeviceImageViewImageFormatInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_FILTER_CUBIC_IMAGE_VIEW_IMAGE_FORMAT_PROPERTIES_EXT = VkStructureType::FilterCubicImageViewImageFormatPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_QUEUE_GLOBAL_PRIORITY_CREATE_INFO_EXT = VkStructureType::DeviceQueueGlobalPriorityCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT = VkStructureType::ImportMemoryHostPointerInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_HOST_POINTER_PROPERTIES_EXT = VkStructureType::MemoryHostPointerPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT = VkStructureType::PhysicalDeviceExternalMemoryHostPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR = VkStructureType::PhysicalDeviceShaderClockFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COMPILER_CONTROL_CREATE_INFO_AMD = VkStructureType::PipelineCompilerControlCreateInfoAMD;
const VkStructureType VK_STRUCTURE_TYPE_CALIBRATED_TIMESTAMP_INFO_EXT = VkStructureType::CalibratedTimestampInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD = VkStructureType::PhysicalDeviceShaderCorePropertiesAMD;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_EXT = VkStructureType::VideoDecodeH265CapabilitiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_CREATE_INFO_EXT = VkStructureType::VideoDecodeH265SessionCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_EXT = VkStructureType::VideoDecodeH265SessionParametersCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_EXT = VkStructureType::VideoDecodeH265SessionParametersAddInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_EXT = VkStructureType::VideoDecodeH265ProfileEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_EXT = VkStructureType::VideoDecodeH265PictureInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_DPB_SLOT_INFO_EXT = VkStructureType::VideoDecodeH265DpbSlotInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_MEMORY_OVERALLOCATION_CREATE_INFO_AMD = VkStructureType::DeviceMemoryOverallocationCreateInfoAMD;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_PROPERTIES_EXT = VkStructureType::PhysicalDeviceVertexAttributeDivisorPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_DIVISOR_STATE_CREATE_INFO_EXT = VkStructureType::PipelineVertexInputDivisorStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_ATTRIBUTE_DIVISOR_FEATURES_EXT = VkStructureType::PhysicalDeviceVertexAttributeDivisorFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PRESENT_FRAME_TOKEN_GGP = VkStructureType::PresentFrameTokenGGP;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_CREATION_FEEDBACK_CREATE_INFO_EXT = VkStructureType::PipelineCreationFeedbackCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COMPUTE_SHADER_DERIVATIVES_FEATURES_NV = VkStructureType::PhysicalDeviceComputeShaderDerivativesFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV = VkStructureType::PhysicalDeviceMeshShaderFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_PROPERTIES_NV = VkStructureType::PhysicalDeviceMeshShaderPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV = VkStructureType::PhysicalDeviceFragmentShaderBarycentricFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_FOOTPRINT_FEATURES_NV = VkStructureType::PhysicalDeviceShaderImageFootprintFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_EXCLUSIVE_SCISSOR_STATE_CREATE_INFO_NV = VkStructureType::PipelineViewportExclusiveScissorStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXCLUSIVE_SCISSOR_FEATURES_NV = VkStructureType::PhysicalDeviceExclusiveScissorFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV = VkStructureType::CheckpointDataNV;
const VkStructureType VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_NV = VkStructureType::QueueFamilyCheckpointPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_INTEGER_FUNCTIONS_2_FEATURES_INTEL = VkStructureType::PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL;
const VkStructureType VK_STRUCTURE_TYPE_QUERY_POOL_PERFORMANCE_QUERY_CREATE_INFO_INTEL = VkStructureType::QueryPoolPerformanceQueryCreateInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_INITIALIZE_PERFORMANCE_API_INFO_INTEL = VkStructureType::InitializePerformanceApiInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_MARKER_INFO_INTEL = VkStructureType::PerformanceMarkerInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_STREAM_MARKER_INFO_INTEL = VkStructureType::PerformanceStreamMarkerInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_OVERRIDE_INFO_INTEL = VkStructureType::PerformanceOverrideInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_PERFORMANCE_CONFIGURATION_ACQUIRE_INFO_INTEL = VkStructureType::PerformanceConfigurationAcquireInfoINTEL;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PCI_BUS_INFO_PROPERTIES_EXT = VkStructureType::PhysicalDevicePciBusInfoPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_DISPLAY_NATIVE_HDR_SURFACE_CAPABILITIES_AMD = VkStructureType::DisplayNativeHdrSurfaceCapabilitiesAMD;
const VkStructureType VK_STRUCTURE_TYPE_SWAPCHAIN_DISPLAY_NATIVE_HDR_CREATE_INFO_AMD = VkStructureType::SwapchainDisplayNativeHdrCreateInfoAMD;
const VkStructureType VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA = VkStructureType::ImagepipeSurfaceCreateInfoFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_TERMINATE_INVOCATION_FEATURES_KHR = VkStructureType::PhysicalDeviceShaderTerminateInvocationFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT = VkStructureType::MetalSurfaceCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_FEATURES_EXT = VkStructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_PROPERTIES_EXT = VkStructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_FRAGMENT_DENSITY_MAP_CREATE_INFO_EXT = VkStructureType::RenderPassFragmentDensityMapCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES_EXT = VkStructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_REQUIRED_SUBGROUP_SIZE_CREATE_INFO_EXT = VkStructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES_EXT = VkStructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_FRAGMENT_SHADING_RATE_ATTACHMENT_INFO_KHR = VkStructureType::FragmentShadingRateAttachmentInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_STATE_CREATE_INFO_KHR = VkStructureType::PipelineFragmentShadingRateStateCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR = VkStructureType::PhysicalDeviceFragmentShadingRatePropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR = VkStructureType::PhysicalDeviceFragmentShadingRateFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_KHR = VkStructureType::PhysicalDeviceFragmentShadingRateKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD = VkStructureType::PhysicalDeviceShaderCoreProperties2AMD;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COHERENT_MEMORY_FEATURES_AMD = VkStructureType::PhysicalDeviceCoherentMemoryFeaturesAMD;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT = VkStructureType::PhysicalDeviceShaderImageAtomicInt64FeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_BUDGET_PROPERTIES_EXT = VkStructureType::PhysicalDeviceMemoryBudgetPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PRIORITY_FEATURES_EXT = VkStructureType::PhysicalDeviceMemoryPriorityFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_PRIORITY_ALLOCATE_INFO_EXT = VkStructureType::MemoryPriorityAllocateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR = VkStructureType::SurfaceProtectedCapabilitiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEDICATED_ALLOCATION_IMAGE_ALIASING_FEATURES_NV = VkStructureType::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES_EXT = VkStructureType::PhysicalDeviceBufferDeviceAddressFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT = VkStructureType::BufferDeviceAddressCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TOOL_PROPERTIES_EXT = VkStructureType::PhysicalDeviceToolPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT = VkStructureType::ValidationFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV = VkStructureType::PhysicalDeviceCooperativeMatrixFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_COOPERATIVE_MATRIX_PROPERTIES_NV = VkStructureType::CooperativeMatrixPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_PROPERTIES_NV = VkStructureType::PhysicalDeviceCooperativeMatrixPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COVERAGE_REDUCTION_MODE_FEATURES_NV = VkStructureType::PhysicalDeviceCoverageReductionModeFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COVERAGE_REDUCTION_STATE_CREATE_INFO_NV = VkStructureType::PipelineCoverageReductionStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_FRAMEBUFFER_MIXED_SAMPLES_COMBINATION_NV = VkStructureType::FramebufferMixedSamplesCombinationNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT = VkStructureType::PhysicalDeviceFragmentShaderInterlockFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_IMAGE_ARRAYS_FEATURES_EXT = VkStructureType::PhysicalDeviceYcbcrImageArraysFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT = VkStructureType::SurfaceFullScreenExclusiveInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_FULL_SCREEN_EXCLUSIVE_EXT = VkStructureType::SurfaceCapabilitiesFullScreenExclusiveEXT;
const VkStructureType VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT = VkStructureType::SurfaceFullScreenExclusiveWin32InfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT = VkStructureType::HeadlessSurfaceCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_FEATURES_EXT = VkStructureType::PhysicalDeviceLineRasterizationFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT = VkStructureType::PipelineRasterizationLineStateCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_LINE_RASTERIZATION_PROPERTIES_EXT = VkStructureType::PhysicalDeviceLineRasterizationPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT = VkStructureType::PhysicalDeviceShaderAtomicFloatFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INDEX_TYPE_UINT8_FEATURES_EXT = VkStructureType::PhysicalDeviceIndexTypeUint8FeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT = VkStructureType::PhysicalDeviceExtendedDynamicStateFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_EXECUTABLE_PROPERTIES_FEATURES_KHR = VkStructureType::PhysicalDevicePipelineExecutablePropertiesFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_INFO_KHR = VkStructureType::PipelineInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_PROPERTIES_KHR = VkStructureType::PipelineExecutablePropertiesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INFO_KHR = VkStructureType::PipelineExecutableInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_STATISTIC_KHR = VkStructureType::PipelineExecutableStatisticKHR;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_EXECUTABLE_INTERNAL_REPRESENTATION_KHR = VkStructureType::PipelineExecutableInternalRepresentationKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DEMOTE_TO_HELPER_INVOCATION_FEATURES_EXT = VkStructureType::PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_PROPERTIES_NV = VkStructureType::PhysicalDeviceDeviceGeneratedCommandsPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_GRAPHICS_SHADER_GROUP_CREATE_INFO_NV = VkStructureType::GraphicsShaderGroupCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_SHADER_GROUPS_CREATE_INFO_NV = VkStructureType::GraphicsPipelineShaderGroupsCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_TOKEN_NV = VkStructureType::IndirectCommandsLayoutTokenNV;
const VkStructureType VK_STRUCTURE_TYPE_INDIRECT_COMMANDS_LAYOUT_CREATE_INFO_NV = VkStructureType::IndirectCommandsLayoutCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_GENERATED_COMMANDS_INFO_NV = VkStructureType::GeneratedCommandsInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_GENERATED_COMMANDS_MEMORY_REQUIREMENTS_INFO_NV = VkStructureType::GeneratedCommandsMemoryRequirementsInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_GENERATED_COMMANDS_FEATURES_NV = VkStructureType::PhysicalDeviceDeviceGeneratedCommandsFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_INHERITED_VIEWPORT_SCISSOR_FEATURES_NV = VkStructureType::PhysicalDeviceInheritedViewportScissorFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_VIEWPORT_SCISSOR_INFO_NV = VkStructureType::CommandBufferInheritanceViewportScissorInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_FEATURES_EXT = VkStructureType::PhysicalDeviceTexelBufferAlignmentFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TEXEL_BUFFER_ALIGNMENT_PROPERTIES_EXT = VkStructureType::PhysicalDeviceTexelBufferAlignmentPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_RENDER_PASS_TRANSFORM_INFO_QCOM = VkStructureType::CommandBufferInheritanceRenderPassTransformInfoQCOM;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_TRANSFORM_BEGIN_INFO_QCOM = VkStructureType::RenderPassTransformBeginInfoQCOM;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEVICE_MEMORY_REPORT_FEATURES_EXT = VkStructureType::PhysicalDeviceDeviceMemoryReportFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_DEVICE_MEMORY_REPORT_CREATE_INFO_EXT = VkStructureType::DeviceDeviceMemoryReportCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_MEMORY_REPORT_CALLBACK_DATA_EXT = VkStructureType::DeviceMemoryReportCallbackDataEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT = VkStructureType::PhysicalDeviceRobustness2FeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_PROPERTIES_EXT = VkStructureType::PhysicalDeviceRobustness2PropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_CUSTOM_BORDER_COLOR_CREATE_INFO_EXT = VkStructureType::SamplerCustomBorderColorCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_PROPERTIES_EXT = VkStructureType::PhysicalDeviceCustomBorderColorPropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUSTOM_BORDER_COLOR_FEATURES_EXT = VkStructureType::PhysicalDeviceCustomBorderColorFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR = VkStructureType::PipelineLibraryCreateInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRIVATE_DATA_FEATURES_EXT = VkStructureType::PhysicalDevicePrivateDataFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_PRIVATE_DATA_CREATE_INFO_EXT = VkStructureType::DevicePrivateDataCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PRIVATE_DATA_SLOT_CREATE_INFO_EXT = VkStructureType::PrivateDataSlotCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PIPELINE_CREATION_CACHE_CONTROL_FEATURES_EXT = VkStructureType::PhysicalDevicePipelineCreationCacheControlFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DIAGNOSTICS_CONFIG_FEATURES_NV = VkStructureType::PhysicalDeviceDiagnosticsConfigFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_DIAGNOSTICS_CONFIG_CREATE_INFO_NV = VkStructureType::DeviceDiagnosticsConfigCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_BARRIER_2_KHR = VkStructureType::MemoryBarrier2KHR;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER_2_KHR = VkStructureType::BufferMemoryBarrier2KHR;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2_KHR = VkStructureType::ImageMemoryBarrier2KHR;
const VkStructureType VK_STRUCTURE_TYPE_DEPENDENCY_INFO_KHR = VkStructureType::DependencyInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_SUBMIT_INFO_2_KHR = VkStructureType::SubmitInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO_KHR = VkStructureType::SemaphoreSubmitInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO_KHR = VkStructureType::CommandBufferSubmitInfoKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES_KHR = VkStructureType::PhysicalDeviceSynchronization2FeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_QUEUE_FAMILY_CHECKPOINT_PROPERTIES_2_NV = VkStructureType::QueueFamilyCheckpointProperties2NV;
const VkStructureType VK_STRUCTURE_TYPE_CHECKPOINT_DATA_2_NV = VkStructureType::CheckpointData2NV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ZERO_INITIALIZE_WORKGROUP_MEMORY_FEATURES_KHR = VkStructureType::PhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV = VkStructureType::PhysicalDeviceFragmentShadingRateEnumsPropertiesNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_FEATURES_NV = VkStructureType::PhysicalDeviceFragmentShadingRateEnumsFeaturesNV;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_FRAGMENT_SHADING_RATE_ENUM_STATE_CREATE_INFO_NV = VkStructureType::PipelineFragmentShadingRateEnumStateCreateInfoNV;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_YCBCR_2_PLANE_444_FORMATS_FEATURES_EXT = VkStructureType::PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_FEATURES_EXT = VkStructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_DENSITY_MAP_2_PROPERTIES_EXT = VkStructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT;
const VkStructureType VK_STRUCTURE_TYPE_COPY_COMMAND_TRANSFORM_INFO_QCOM = VkStructureType::CopyCommandTransformInfoQCOM;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_ROBUSTNESS_FEATURES_EXT = VkStructureType::PhysicalDeviceImageRobustnessFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_FEATURES_KHR = VkStructureType::PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_BUFFER_INFO_2_KHR = VkStructureType::CopyBufferInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_IMAGE_INFO_2_KHR = VkStructureType::CopyImageInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_BUFFER_TO_IMAGE_INFO_2_KHR = VkStructureType::CopyBufferToImageInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_COPY_IMAGE_TO_BUFFER_INFO_2_KHR = VkStructureType::CopyImageToBufferInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2_KHR = VkStructureType::BlitImageInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_RESOLVE_IMAGE_INFO_2_KHR = VkStructureType::ResolveImageInfo2KHR;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_COPY_2_KHR = VkStructureType::BufferCopy2KHR;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_COPY_2_KHR = VkStructureType::ImageCopy2KHR;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_BLIT_2_KHR = VkStructureType::ImageBlit2KHR;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_IMAGE_COPY_2_KHR = VkStructureType::BufferImageCopy2KHR;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_RESOLVE_2_KHR = VkStructureType::ImageResolve2KHR;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_4444_FORMATS_FEATURES_EXT = VkStructureType::PhysicalDevice4444FormatsFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT = VkStructureType::DirectfbSurfaceCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_VALVE = VkStructureType::PhysicalDeviceMutableDescriptorTypeFeaturesVALVE;
const VkStructureType VK_STRUCTURE_TYPE_MUTABLE_DESCRIPTOR_TYPE_CREATE_INFO_VALVE = VkStructureType::MutableDescriptorTypeCreateInfoVALVE;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VERTEX_INPUT_DYNAMIC_STATE_FEATURES_EXT = VkStructureType::PhysicalDeviceVertexInputDynamicStateFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_VERTEX_INPUT_BINDING_DESCRIPTION_2_EXT = VkStructureType::VertexInputBindingDescription2EXT;
const VkStructureType VK_STRUCTURE_TYPE_VERTEX_INPUT_ATTRIBUTE_DESCRIPTION_2_EXT = VkStructureType::VertexInputAttributeDescription2EXT;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_MEMORY_ZIRCON_HANDLE_INFO_FUCHSIA = VkStructureType::ImportMemoryZirconHandleInfoFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_ZIRCON_HANDLE_PROPERTIES_FUCHSIA = VkStructureType::MemoryZirconHandlePropertiesFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_GET_ZIRCON_HANDLE_INFO_FUCHSIA = VkStructureType::MemoryGetZirconHandleInfoFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_ZIRCON_HANDLE_INFO_FUCHSIA = VkStructureType::ImportSemaphoreZirconHandleInfoFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_GET_ZIRCON_HANDLE_INFO_FUCHSIA = VkStructureType::SemaphoreGetZirconHandleInfoFUCHSIA;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT = VkStructureType::PhysicalDeviceExtendedDynamicState2FeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX = VkStructureType::ScreenSurfaceCreateInfoQNX;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COLOR_WRITE_ENABLE_FEATURES_EXT = VkStructureType::PhysicalDeviceColorWriteEnableFeaturesEXT;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_COLOR_WRITE_CREATE_INFO_EXT = VkStructureType::PipelineColorWriteCreateInfoEXT;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES = VkStructureType::PhysicalDeviceSubgroupProperties;
const VkStructureType VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO = VkStructureType::BindBufferMemoryInfo;
const VkStructureType VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO = VkStructureType::BindImageMemoryInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES = VkStructureType::PhysicalDevice16BitStorageFeatures;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS = VkStructureType::MemoryDedicatedRequirements;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO = VkStructureType::MemoryDedicatedAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO = VkStructureType::MemoryAllocateFlagsInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO = VkStructureType::DeviceGroupRenderPassBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_COMMAND_BUFFER_BEGIN_INFO = VkStructureType::DeviceGroupCommandBufferBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO = VkStructureType::DeviceGroupSubmitInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_BIND_SPARSE_INFO = VkStructureType::DeviceGroupBindSparseInfo;
const VkStructureType VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_DEVICE_GROUP_INFO = VkStructureType::BindBufferMemoryDeviceGroupInfo;
const VkStructureType VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_DEVICE_GROUP_INFO = VkStructureType::BindImageMemoryDeviceGroupInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES = VkStructureType::PhysicalDeviceGroupProperties;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO = VkStructureType::DeviceGroupDeviceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 = VkStructureType::BufferMemoryRequirementsInfo2;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_MEMORY_REQUIREMENTS_INFO_2 = VkStructureType::ImageMemoryRequirementsInfo2;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_SPARSE_MEMORY_REQUIREMENTS_INFO_2 = VkStructureType::ImageSparseMemoryRequirementsInfo2;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 = VkStructureType::MemoryRequirements2;
const VkStructureType VK_STRUCTURE_TYPE_SPARSE_IMAGE_MEMORY_REQUIREMENTS_2 = VkStructureType::SparseImageMemoryRequirements2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 = VkStructureType::PhysicalDeviceFeatures2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 = VkStructureType::PhysicalDeviceProperties2;
const VkStructureType VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2 = VkStructureType::FormatProperties2;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2 = VkStructureType::ImageFormatProperties2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2 = VkStructureType::PhysicalDeviceImageFormatInfo2;
const VkStructureType VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 = VkStructureType::QueueFamilyProperties2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MEMORY_PROPERTIES_2 = VkStructureType::PhysicalDeviceMemoryProperties2;
const VkStructureType VK_STRUCTURE_TYPE_SPARSE_IMAGE_FORMAT_PROPERTIES_2 = VkStructureType::SparseImageFormatProperties2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SPARSE_IMAGE_FORMAT_INFO_2 = VkStructureType::PhysicalDeviceSparseImageFormatInfo2;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_POINT_CLIPPING_PROPERTIES = VkStructureType::PhysicalDevicePointClippingProperties;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO = VkStructureType::RenderPassInputAttachmentAspectCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO = VkStructureType::ImageViewUsageCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO = VkStructureType::PipelineTessellationDomainOriginStateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO = VkStructureType::RenderPassMultiviewCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_FEATURES = VkStructureType::PhysicalDeviceMultiviewFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MULTIVIEW_PROPERTIES = VkStructureType::PhysicalDeviceMultiviewProperties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VARIABLE_POINTERS_FEATURES = VkStructureType::PhysicalDeviceVariablePointersFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO = VkStructureType::ProtectedSubmitInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_FEATURES = VkStructureType::PhysicalDeviceProtectedMemoryFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROTECTED_MEMORY_PROPERTIES = VkStructureType::PhysicalDeviceProtectedMemoryProperties;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2 = VkStructureType::DeviceQueueInfo2;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO = VkStructureType::SamplerYcbcrConversionCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO = VkStructureType::SamplerYcbcrConversionInfo;
const VkStructureType VK_STRUCTURE_TYPE_BIND_IMAGE_PLANE_MEMORY_INFO = VkStructureType::BindImagePlaneMemoryInfo;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_PLANE_MEMORY_REQUIREMENTS_INFO = VkStructureType::ImagePlaneMemoryRequirementsInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_YCBCR_CONVERSION_FEATURES = VkStructureType::PhysicalDeviceSamplerYcbcrConversionFeatures;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_IMAGE_FORMAT_PROPERTIES = VkStructureType::SamplerYcbcrConversionImageFormatProperties;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO = VkStructureType::DescriptorUpdateTemplateCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO = VkStructureType::PhysicalDeviceExternalImageFormatInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES = VkStructureType::ExternalImageFormatProperties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_BUFFER_INFO = VkStructureType::PhysicalDeviceExternalBufferInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_BUFFER_PROPERTIES = VkStructureType::ExternalBufferProperties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ID_PROPERTIES = VkStructureType::PhysicalDeviceIdProperties;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_BUFFER_CREATE_INFO = VkStructureType::ExternalMemoryBufferCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO = VkStructureType::ExternalMemoryImageCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO = VkStructureType::ExportMemoryAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_FENCE_INFO = VkStructureType::PhysicalDeviceExternalFenceInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_FENCE_PROPERTIES = VkStructureType::ExternalFenceProperties;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_FENCE_CREATE_INFO = VkStructureType::ExportFenceCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO = VkStructureType::ExportSemaphoreCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO = VkStructureType::PhysicalDeviceExternalSemaphoreInfo;
const VkStructureType VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES = VkStructureType::ExternalSemaphoreProperties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MAINTENANCE_3_PROPERTIES = VkStructureType::PhysicalDeviceMaintenance3Properties;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_SUPPORT = VkStructureType::DescriptorSetLayoutSupport;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES = VkStructureType::PhysicalDeviceShaderDrawParametersFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES = VkStructureType::PhysicalDeviceVulkan11Features;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_PROPERTIES = VkStructureType::PhysicalDeviceVulkan11Properties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES = VkStructureType::PhysicalDeviceVulkan12Features;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_PROPERTIES = VkStructureType::PhysicalDeviceVulkan12Properties;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO = VkStructureType::ImageFormatListCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_2 = VkStructureType::AttachmentDescription2;
const VkStructureType VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_2 = VkStructureType::AttachmentReference2;
const VkStructureType VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_2 = VkStructureType::SubpassDescription2;
const VkStructureType VK_STRUCTURE_TYPE_SUBPASS_DEPENDENCY_2 = VkStructureType::SubpassDependency2;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO_2 = VkStructureType::RenderPassCreateInfo2;
const VkStructureType VK_STRUCTURE_TYPE_SUBPASS_BEGIN_INFO = VkStructureType::SubpassBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_SUBPASS_END_INFO = VkStructureType::SubpassEndInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES = VkStructureType::PhysicalDevice8BitStorageFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES = VkStructureType::PhysicalDeviceDriverProperties;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES = VkStructureType::PhysicalDeviceShaderAtomicInt64Features;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES = VkStructureType::PhysicalDeviceShaderFloat16Int8Features;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES = VkStructureType::PhysicalDeviceFloatControlsProperties;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO = VkStructureType::DescriptorSetLayoutBindingFlagsCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES = VkStructureType::PhysicalDeviceDescriptorIndexingFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_PROPERTIES = VkStructureType::PhysicalDeviceDescriptorIndexingProperties;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO = VkStructureType::DescriptorSetVariableDescriptorCountAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_LAYOUT_SUPPORT = VkStructureType::DescriptorSetVariableDescriptorCountLayoutSupport;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DEPTH_STENCIL_RESOLVE_PROPERTIES = VkStructureType::PhysicalDeviceDepthStencilResolveProperties;
const VkStructureType VK_STRUCTURE_TYPE_SUBPASS_DESCRIPTION_DEPTH_STENCIL_RESOLVE = VkStructureType::SubpassDescriptionDepthStencilResolve;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES = VkStructureType::PhysicalDeviceScalarBlockLayoutFeatures;
const VkStructureType VK_STRUCTURE_TYPE_IMAGE_STENCIL_USAGE_CREATE_INFO = VkStructureType::ImageStencilUsageCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SAMPLER_FILTER_MINMAX_PROPERTIES = VkStructureType::PhysicalDeviceSamplerFilterMinmaxProperties;
const VkStructureType VK_STRUCTURE_TYPE_SAMPLER_REDUCTION_MODE_CREATE_INFO = VkStructureType::SamplerReductionModeCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_MEMORY_MODEL_FEATURES = VkStructureType::PhysicalDeviceVulkanMemoryModelFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGELESS_FRAMEBUFFER_FEATURES = VkStructureType::PhysicalDeviceImagelessFramebufferFeatures;
const VkStructureType VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO = VkStructureType::FramebufferAttachmentsCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO = VkStructureType::FramebufferAttachmentImageInfo;
const VkStructureType VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO = VkStructureType::RenderPassAttachmentBeginInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES = VkStructureType::PhysicalDeviceUniformBufferStandardLayoutFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES = VkStructureType::PhysicalDeviceShaderSubgroupExtendedTypesFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SEPARATE_DEPTH_STENCIL_LAYOUTS_FEATURES = VkStructureType::PhysicalDeviceSeparateDepthStencilLayoutsFeatures;
const VkStructureType VK_STRUCTURE_TYPE_ATTACHMENT_REFERENCE_STENCIL_LAYOUT = VkStructureType::AttachmentReferenceStencilLayout;
const VkStructureType VK_STRUCTURE_TYPE_ATTACHMENT_DESCRIPTION_STENCIL_LAYOUT = VkStructureType::AttachmentDescriptionStencilLayout;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES = VkStructureType::PhysicalDeviceHostQueryResetFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES = VkStructureType::PhysicalDeviceTimelineSemaphoreFeatures;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_PROPERTIES = VkStructureType::PhysicalDeviceTimelineSemaphoreProperties;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO = VkStructureType::SemaphoreTypeCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO = VkStructureType::TimelineSemaphoreSubmitInfo;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO = VkStructureType::SemaphoreWaitInfo;
const VkStructureType VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO = VkStructureType::SemaphoreSignalInfo;
const VkStructureType VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES = VkStructureType::PhysicalDeviceBufferDeviceAddressFeatures;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO = VkStructureType::BufferDeviceAddressInfo;
const VkStructureType VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO = VkStructureType::BufferOpaqueCaptureAddressCreateInfo;
const VkStructureType VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO = VkStructureType::MemoryOpaqueCaptureAddressAllocateInfo;
const VkStructureType VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO = VkStructureType::DeviceMemoryOpaqueCaptureAddressInfo;
enum class VkSystemAllocationScope : uint32_t {
    Command = 0,
    Object = 1,
    Cache = 2,
    Device = 3,
    Instance = 4,
};
const VkSystemAllocationScope VK_SYSTEM_ALLOCATION_SCOPE_COMMAND = VkSystemAllocationScope::Command;
const VkSystemAllocationScope VK_SYSTEM_ALLOCATION_SCOPE_OBJECT = VkSystemAllocationScope::Object;
const VkSystemAllocationScope VK_SYSTEM_ALLOCATION_SCOPE_CACHE = VkSystemAllocationScope::Cache;
const VkSystemAllocationScope VK_SYSTEM_ALLOCATION_SCOPE_DEVICE = VkSystemAllocationScope::Device;
const VkSystemAllocationScope VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE = VkSystemAllocationScope::Instance;
enum class VkInternalAllocationType : uint32_t {
    Executable = 0,
};
const VkInternalAllocationType VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE = VkInternalAllocationType::Executable;
enum class VkSamplerAddressMode : uint32_t {
    Repeat = 0,
    MirroredRepeat = 1,
    ClampToEdge = 2,
    ClampToBorder = 3,
    MirrorClampToEdge = 4,
};
const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODE_REPEAT = VkSamplerAddressMode::Repeat;
const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT = VkSamplerAddressMode::MirroredRepeat;
const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE = VkSamplerAddressMode::ClampToEdge;
const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER = VkSamplerAddressMode::ClampToBorder;
const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE = VkSamplerAddressMode::MirrorClampToEdge;
enum class VkFilter : uint32_t {
    Nearest = 0,
    Linear = 1,
    CubicIMG = 1000015000,
};
const VkFilter VK_FILTER_NEAREST = VkFilter::Nearest;
const VkFilter VK_FILTER_LINEAR = VkFilter::Linear;
const VkFilter VK_FILTER_CUBIC_IMG = VkFilter::CubicIMG;
enum class VkSamplerMipmapMode : uint32_t {
    Nearest = 0,
    Linear = 1,
};
const VkSamplerMipmapMode VK_SAMPLER_MIPMAP_MODE_NEAREST = VkSamplerMipmapMode::Nearest;
const VkSamplerMipmapMode VK_SAMPLER_MIPMAP_MODE_LINEAR = VkSamplerMipmapMode::Linear;
enum class VkVertexInputRate : uint32_t {
    Vertex = 0,
    Instance = 1,
};
const VkVertexInputRate VK_VERTEX_INPUT_RATE_VERTEX = VkVertexInputRate::Vertex;
const VkVertexInputRate VK_VERTEX_INPUT_RATE_INSTANCE = VkVertexInputRate::Instance;
enum class VkObjectType : uint32_t {
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
    VideoSessionKHR = 1000023000,
    VideoSessionParametersKHR = 1000023001,
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
const VkObjectType VK_OBJECT_TYPE_UNKNOWN = VkObjectType::Unknown;
const VkObjectType VK_OBJECT_TYPE_INSTANCE = VkObjectType::Instance;
const VkObjectType VK_OBJECT_TYPE_PHYSICAL_DEVICE = VkObjectType::PhysicalDevice;
const VkObjectType VK_OBJECT_TYPE_DEVICE = VkObjectType::Device;
const VkObjectType VK_OBJECT_TYPE_QUEUE = VkObjectType::Queue;
const VkObjectType VK_OBJECT_TYPE_SEMAPHORE = VkObjectType::Semaphore;
const VkObjectType VK_OBJECT_TYPE_COMMAND_BUFFER = VkObjectType::CommandBuffer;
const VkObjectType VK_OBJECT_TYPE_FENCE = VkObjectType::Fence;
const VkObjectType VK_OBJECT_TYPE_DEVICE_MEMORY = VkObjectType::DeviceMemory;
const VkObjectType VK_OBJECT_TYPE_BUFFER = VkObjectType::Buffer;
const VkObjectType VK_OBJECT_TYPE_IMAGE = VkObjectType::Image;
const VkObjectType VK_OBJECT_TYPE_EVENT = VkObjectType::Event;
const VkObjectType VK_OBJECT_TYPE_QUERY_POOL = VkObjectType::QueryPool;
const VkObjectType VK_OBJECT_TYPE_BUFFER_VIEW = VkObjectType::BufferView;
const VkObjectType VK_OBJECT_TYPE_IMAGE_VIEW = VkObjectType::ImageView;
const VkObjectType VK_OBJECT_TYPE_SHADER_MODULE = VkObjectType::ShaderModule;
const VkObjectType VK_OBJECT_TYPE_PIPELINE_CACHE = VkObjectType::PipelineCache;
const VkObjectType VK_OBJECT_TYPE_PIPELINE_LAYOUT = VkObjectType::PipelineLayout;
const VkObjectType VK_OBJECT_TYPE_RENDER_PASS = VkObjectType::RenderPass;
const VkObjectType VK_OBJECT_TYPE_PIPELINE = VkObjectType::Pipeline;
const VkObjectType VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT = VkObjectType::DescriptorSetLayout;
const VkObjectType VK_OBJECT_TYPE_SAMPLER = VkObjectType::Sampler;
const VkObjectType VK_OBJECT_TYPE_DESCRIPTOR_POOL = VkObjectType::DescriptorPool;
const VkObjectType VK_OBJECT_TYPE_DESCRIPTOR_SET = VkObjectType::DescriptorSet;
const VkObjectType VK_OBJECT_TYPE_FRAMEBUFFER = VkObjectType::Framebuffer;
const VkObjectType VK_OBJECT_TYPE_COMMAND_POOL = VkObjectType::CommandPool;
const VkObjectType VK_OBJECT_TYPE_SURFACE_KHR = VkObjectType::SurfaceKHR;
const VkObjectType VK_OBJECT_TYPE_SWAPCHAIN_KHR = VkObjectType::SwapchainKHR;
const VkObjectType VK_OBJECT_TYPE_DISPLAY_KHR = VkObjectType::DisplayKHR;
const VkObjectType VK_OBJECT_TYPE_DISPLAY_MODE_KHR = VkObjectType::DisplayModeKHR;
const VkObjectType VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT = VkObjectType::DebugReportCallbackEXT;
const VkObjectType VK_OBJECT_TYPE_VIDEO_SESSION_KHR = VkObjectType::VideoSessionKHR;
const VkObjectType VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR = VkObjectType::VideoSessionParametersKHR;
const VkObjectType VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT = VkObjectType::DebugUtilsMessengerEXT;
const VkObjectType VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR = VkObjectType::AccelerationStructureKHR;
const VkObjectType VK_OBJECT_TYPE_VALIDATION_CACHE_EXT = VkObjectType::ValidationCacheEXT;
const VkObjectType VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV = VkObjectType::AccelerationStructureNV;
const VkObjectType VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL = VkObjectType::PerformanceConfigurationINTEL;
const VkObjectType VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR = VkObjectType::DeferredOperationKHR;
const VkObjectType VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV = VkObjectType::IndirectCommandsLayoutNV;
const VkObjectType VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT = VkObjectType::PrivateDataSlotEXT;
const VkObjectType VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION = VkObjectType::SamplerYcbcrConversion;
const VkObjectType VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE = VkObjectType::DescriptorUpdateTemplate;
enum class VkIndirectCommandsTokenTypeNV : uint32_t {
    ShaderGroupNV = 0,
    StateFlagsNV = 1,
    IndexBufferNV = 2,
    VertexBufferNV = 3,
    PushConstantNV = 4,
    DrawIndexedNV = 5,
    DrawNV = 6,
    DrawTasksNV = 7,
};
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_SHADER_GROUP_NV = VkIndirectCommandsTokenTypeNV::ShaderGroupNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_STATE_FLAGS_NV = VkIndirectCommandsTokenTypeNV::StateFlagsNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NV = VkIndirectCommandsTokenTypeNV::IndexBufferNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NV = VkIndirectCommandsTokenTypeNV::VertexBufferNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NV = VkIndirectCommandsTokenTypeNV::PushConstantNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NV = VkIndirectCommandsTokenTypeNV::DrawIndexedNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NV = VkIndirectCommandsTokenTypeNV::DrawNV;
const VkIndirectCommandsTokenTypeNV VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_TASKS_NV = VkIndirectCommandsTokenTypeNV::DrawTasksNV;
enum class VkDescriptorUpdateTemplateType : uint32_t {
    DescriptorSet = 0,
    PushDescriptorsKHR = 1,
};
const VkDescriptorUpdateTemplateType VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET = VkDescriptorUpdateTemplateType::DescriptorSet;
const VkDescriptorUpdateTemplateType VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_PUSH_DESCRIPTORS_KHR = VkDescriptorUpdateTemplateType::PushDescriptorsKHR;
using VkDescriptorUpdateTemplateTypeKHR = VkDescriptorUpdateTemplateType;
enum class VkViewportCoordinateSwizzleNV : uint32_t {
    PositiveXNV = 0,
    NegativeXNV = 1,
    PositiveYNV = 2,
    NegativeYNV = 3,
    PositiveZNV = 4,
    NegativeZNV = 5,
    PositiveWNV = 6,
    NegativeWNV = 7,
};
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV = VkViewportCoordinateSwizzleNV::PositiveXNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV = VkViewportCoordinateSwizzleNV::NegativeXNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV = VkViewportCoordinateSwizzleNV::PositiveYNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV = VkViewportCoordinateSwizzleNV::NegativeYNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV = VkViewportCoordinateSwizzleNV::PositiveZNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV = VkViewportCoordinateSwizzleNV::NegativeZNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV = VkViewportCoordinateSwizzleNV::PositiveWNV;
const VkViewportCoordinateSwizzleNV VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV = VkViewportCoordinateSwizzleNV::NegativeWNV;
enum class VkDiscardRectangleModeEXT : uint32_t {
    InclusiveEXT = 0,
    ExclusiveEXT = 1,
};
const VkDiscardRectangleModeEXT VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT = VkDiscardRectangleModeEXT::InclusiveEXT;
const VkDiscardRectangleModeEXT VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT = VkDiscardRectangleModeEXT::ExclusiveEXT;
enum class VkPointClippingBehavior : uint32_t {
    AllClipPlanes = 0,
    UserClipPlanesOnly = 1,
};
const VkPointClippingBehavior VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES = VkPointClippingBehavior::AllClipPlanes;
const VkPointClippingBehavior VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY = VkPointClippingBehavior::UserClipPlanesOnly;
using VkPointClippingBehaviorKHR = VkPointClippingBehavior;
enum class VkCoverageModulationModeNV : uint32_t {
    NoneNV = 0,
    RgbNV = 1,
    AlphaNV = 2,
    RgbaNV = 3,
};
const VkCoverageModulationModeNV VK_COVERAGE_MODULATION_MODE_NONE_NV = VkCoverageModulationModeNV::NoneNV;
const VkCoverageModulationModeNV VK_COVERAGE_MODULATION_MODE_RGB_NV = VkCoverageModulationModeNV::RgbNV;
const VkCoverageModulationModeNV VK_COVERAGE_MODULATION_MODE_ALPHA_NV = VkCoverageModulationModeNV::AlphaNV;
const VkCoverageModulationModeNV VK_COVERAGE_MODULATION_MODE_RGBA_NV = VkCoverageModulationModeNV::RgbaNV;
enum class VkCoverageReductionModeNV : uint32_t {
    MergeNV = 0,
    TruncateNV = 1,
};
const VkCoverageReductionModeNV VK_COVERAGE_REDUCTION_MODE_MERGE_NV = VkCoverageReductionModeNV::MergeNV;
const VkCoverageReductionModeNV VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV = VkCoverageReductionModeNV::TruncateNV;
enum class VkValidationCacheHeaderVersionEXT : uint32_t {
    OneEXT = 1,
};
const VkValidationCacheHeaderVersionEXT VK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT = VkValidationCacheHeaderVersionEXT::OneEXT;
enum class VkShaderInfoTypeAMD : uint32_t {
    StatisticsAMD = 0,
    BinaryAMD = 1,
    DisassemblyAMD = 2,
};
const VkShaderInfoTypeAMD VK_SHADER_INFO_TYPE_STATISTICS_AMD = VkShaderInfoTypeAMD::StatisticsAMD;
const VkShaderInfoTypeAMD VK_SHADER_INFO_TYPE_BINARY_AMD = VkShaderInfoTypeAMD::BinaryAMD;
const VkShaderInfoTypeAMD VK_SHADER_INFO_TYPE_DISASSEMBLY_AMD = VkShaderInfoTypeAMD::DisassemblyAMD;
enum class VkQueueGlobalPriorityEXT : uint32_t {
    LowEXT = 128,
    MediumEXT = 256,
    HighEXT = 512,
    RealtimeEXT = 1024,
};
const VkQueueGlobalPriorityEXT VK_QUEUE_GLOBAL_PRIORITY_LOW_EXT = VkQueueGlobalPriorityEXT::LowEXT;
const VkQueueGlobalPriorityEXT VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT = VkQueueGlobalPriorityEXT::MediumEXT;
const VkQueueGlobalPriorityEXT VK_QUEUE_GLOBAL_PRIORITY_HIGH_EXT = VkQueueGlobalPriorityEXT::HighEXT;
const VkQueueGlobalPriorityEXT VK_QUEUE_GLOBAL_PRIORITY_REALTIME_EXT = VkQueueGlobalPriorityEXT::RealtimeEXT;
enum class VkTimeDomainEXT : uint32_t {
    DeviceEXT = 0,
    ClockMonotonicEXT = 1,
    ClockMonotonicRawEXT = 2,
    QueryPerformanceCounterEXT = 3,
};
const VkTimeDomainEXT VK_TIME_DOMAIN_DEVICE_EXT = VkTimeDomainEXT::DeviceEXT;
const VkTimeDomainEXT VK_TIME_DOMAIN_CLOCK_MONOTONIC_EXT = VkTimeDomainEXT::ClockMonotonicEXT;
const VkTimeDomainEXT VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_EXT = VkTimeDomainEXT::ClockMonotonicRawEXT;
const VkTimeDomainEXT VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_EXT = VkTimeDomainEXT::QueryPerformanceCounterEXT;
enum class VkConservativeRasterizationModeEXT : uint32_t {
    DisabledEXT = 0,
    OverestimateEXT = 1,
    UnderestimateEXT = 2,
};
const VkConservativeRasterizationModeEXT VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT = VkConservativeRasterizationModeEXT::DisabledEXT;
const VkConservativeRasterizationModeEXT VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT = VkConservativeRasterizationModeEXT::OverestimateEXT;
const VkConservativeRasterizationModeEXT VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT = VkConservativeRasterizationModeEXT::UnderestimateEXT;
enum class VkSemaphoreType : uint32_t {
    Binary = 0,
    Timeline = 1,
};
const VkSemaphoreType VK_SEMAPHORE_TYPE_BINARY = VkSemaphoreType::Binary;
const VkSemaphoreType VK_SEMAPHORE_TYPE_TIMELINE = VkSemaphoreType::Timeline;
using VkSemaphoreTypeKHR = VkSemaphoreType;
enum class VkBuildAccelerationStructureModeKHR : uint32_t {
    BuildKHR = 0,
    UpdateKHR = 1,
};
const VkBuildAccelerationStructureModeKHR VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR = VkBuildAccelerationStructureModeKHR::BuildKHR;
const VkBuildAccelerationStructureModeKHR VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR = VkBuildAccelerationStructureModeKHR::UpdateKHR;
enum class VkCopyAccelerationStructureModeKHR : uint32_t {
    CloneKHR = 0,
    CompactKHR = 1,
    SerializeKHR = 2,
    DeserializeKHR = 3,
};
const VkCopyAccelerationStructureModeKHR VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_KHR = VkCopyAccelerationStructureModeKHR::CloneKHR;
const VkCopyAccelerationStructureModeKHR VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR = VkCopyAccelerationStructureModeKHR::CompactKHR;
const VkCopyAccelerationStructureModeKHR VK_COPY_ACCELERATION_STRUCTURE_MODE_SERIALIZE_KHR = VkCopyAccelerationStructureModeKHR::SerializeKHR;
const VkCopyAccelerationStructureModeKHR VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR = VkCopyAccelerationStructureModeKHR::DeserializeKHR;
using VkCopyAccelerationStructureModeNV = VkCopyAccelerationStructureModeKHR;
enum class VkAccelerationStructureTypeKHR : uint32_t {
    TopLevelKHR = 0,
    BottomLevelKHR = 1,
    GenericKHR = 2,
};
const VkAccelerationStructureTypeKHR VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR = VkAccelerationStructureTypeKHR::TopLevelKHR;
const VkAccelerationStructureTypeKHR VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR = VkAccelerationStructureTypeKHR::BottomLevelKHR;
const VkAccelerationStructureTypeKHR VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR = VkAccelerationStructureTypeKHR::GenericKHR;
using VkAccelerationStructureTypeNV = VkAccelerationStructureTypeKHR;
enum class VkGeometryTypeKHR : uint32_t {
    TrianglesKHR = 0,
    AabbsKHR = 1,
    InstancesKHR = 2,
};
const VkGeometryTypeKHR VK_GEOMETRY_TYPE_TRIANGLES_KHR = VkGeometryTypeKHR::TrianglesKHR;
const VkGeometryTypeKHR VK_GEOMETRY_TYPE_AABBS_KHR = VkGeometryTypeKHR::AabbsKHR;
const VkGeometryTypeKHR VK_GEOMETRY_TYPE_INSTANCES_KHR = VkGeometryTypeKHR::InstancesKHR;
using VkGeometryTypeNV = VkGeometryTypeKHR;
enum class VkRayTracingShaderGroupTypeKHR : uint32_t {
    GeneralKHR = 0,
    TrianglesHitGroupKHR = 1,
    ProceduralHitGroupKHR = 2,
};
const VkRayTracingShaderGroupTypeKHR VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR = VkRayTracingShaderGroupTypeKHR::GeneralKHR;
const VkRayTracingShaderGroupTypeKHR VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR = VkRayTracingShaderGroupTypeKHR::TrianglesHitGroupKHR;
const VkRayTracingShaderGroupTypeKHR VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR = VkRayTracingShaderGroupTypeKHR::ProceduralHitGroupKHR;
using VkRayTracingShaderGroupTypeNV = VkRayTracingShaderGroupTypeKHR;
enum class VkAccelerationStructureMemoryRequirementsTypeNV : uint32_t {
    ObjectNV = 0,
    BuildScratchNV = 1,
    UpdateScratchNV = 2,
};
const VkAccelerationStructureMemoryRequirementsTypeNV VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV = VkAccelerationStructureMemoryRequirementsTypeNV::ObjectNV;
const VkAccelerationStructureMemoryRequirementsTypeNV VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV = VkAccelerationStructureMemoryRequirementsTypeNV::BuildScratchNV;
const VkAccelerationStructureMemoryRequirementsTypeNV VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV = VkAccelerationStructureMemoryRequirementsTypeNV::UpdateScratchNV;
enum class VkAccelerationStructureBuildTypeKHR : uint32_t {
    HostKHR = 0,
    DeviceKHR = 1,
    HostOrDeviceKHR = 2,
};
const VkAccelerationStructureBuildTypeKHR VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_KHR = VkAccelerationStructureBuildTypeKHR::HostKHR;
const VkAccelerationStructureBuildTypeKHR VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR = VkAccelerationStructureBuildTypeKHR::DeviceKHR;
const VkAccelerationStructureBuildTypeKHR VK_ACCELERATION_STRUCTURE_BUILD_TYPE_HOST_OR_DEVICE_KHR = VkAccelerationStructureBuildTypeKHR::HostOrDeviceKHR;
enum class VkAccelerationStructureCompatibilityKHR : uint32_t {
    CompatibleKHR = 0,
    IncompatibleKHR = 1,
};
const VkAccelerationStructureCompatibilityKHR VK_ACCELERATION_STRUCTURE_COMPATIBILITY_COMPATIBLE_KHR = VkAccelerationStructureCompatibilityKHR::CompatibleKHR;
const VkAccelerationStructureCompatibilityKHR VK_ACCELERATION_STRUCTURE_COMPATIBILITY_INCOMPATIBLE_KHR = VkAccelerationStructureCompatibilityKHR::IncompatibleKHR;
enum class VkShaderGroupShaderKHR : uint32_t {
    GeneralKHR = 0,
    ClosestHitKHR = 1,
    AnyHitKHR = 2,
    IntersectionKHR = 3,
};
const VkShaderGroupShaderKHR VK_SHADER_GROUP_SHADER_GENERAL_KHR = VkShaderGroupShaderKHR::GeneralKHR;
const VkShaderGroupShaderKHR VK_SHADER_GROUP_SHADER_CLOSEST_HIT_KHR = VkShaderGroupShaderKHR::ClosestHitKHR;
const VkShaderGroupShaderKHR VK_SHADER_GROUP_SHADER_ANY_HIT_KHR = VkShaderGroupShaderKHR::AnyHitKHR;
const VkShaderGroupShaderKHR VK_SHADER_GROUP_SHADER_INTERSECTION_KHR = VkShaderGroupShaderKHR::IntersectionKHR;
enum class VkMemoryOverallocationBehaviorAMD : uint32_t {
    DefaultAMD = 0,
    AllowedAMD = 1,
    DisallowedAMD = 2,
};
const VkMemoryOverallocationBehaviorAMD VK_MEMORY_OVERALLOCATION_BEHAVIOR_DEFAULT_AMD = VkMemoryOverallocationBehaviorAMD::DefaultAMD;
const VkMemoryOverallocationBehaviorAMD VK_MEMORY_OVERALLOCATION_BEHAVIOR_ALLOWED_AMD = VkMemoryOverallocationBehaviorAMD::AllowedAMD;
const VkMemoryOverallocationBehaviorAMD VK_MEMORY_OVERALLOCATION_BEHAVIOR_DISALLOWED_AMD = VkMemoryOverallocationBehaviorAMD::DisallowedAMD;
enum class VkScopeNV : uint32_t {
    DeviceNV = 1,
    WorkgroupNV = 2,
    SubgroupNV = 3,
    QueueFamilyNV = 5,
};
const VkScopeNV VK_SCOPE_DEVICE_NV = VkScopeNV::DeviceNV;
const VkScopeNV VK_SCOPE_WORKGROUP_NV = VkScopeNV::WorkgroupNV;
const VkScopeNV VK_SCOPE_SUBGROUP_NV = VkScopeNV::SubgroupNV;
const VkScopeNV VK_SCOPE_QUEUE_FAMILY_NV = VkScopeNV::QueueFamilyNV;
enum class VkComponentTypeNV : uint32_t {
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
const VkComponentTypeNV VK_COMPONENT_TYPE_FLOAT16_NV = VkComponentTypeNV::Float16NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_FLOAT32_NV = VkComponentTypeNV::Float32NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_FLOAT64_NV = VkComponentTypeNV::Float64NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_SINT8_NV = VkComponentTypeNV::Sint8NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_SINT16_NV = VkComponentTypeNV::Sint16NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_SINT32_NV = VkComponentTypeNV::Sint32NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_SINT64_NV = VkComponentTypeNV::Sint64NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_UINT8_NV = VkComponentTypeNV::Uint8NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_UINT16_NV = VkComponentTypeNV::Uint16NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_UINT32_NV = VkComponentTypeNV::Uint32NV;
const VkComponentTypeNV VK_COMPONENT_TYPE_UINT64_NV = VkComponentTypeNV::Uint64NV;
enum class VkPerformanceCounterScopeKHR : uint32_t {
    CommandBufferKHR = 0,
    RenderPassKHR = 1,
    CommandKHR = 2,
};
const VkPerformanceCounterScopeKHR VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_BUFFER_KHR = VkPerformanceCounterScopeKHR::CommandBufferKHR;
const VkPerformanceCounterScopeKHR VK_PERFORMANCE_COUNTER_SCOPE_RENDER_PASS_KHR = VkPerformanceCounterScopeKHR::RenderPassKHR;
const VkPerformanceCounterScopeKHR VK_PERFORMANCE_COUNTER_SCOPE_COMMAND_KHR = VkPerformanceCounterScopeKHR::CommandKHR;
enum class VkPerformanceCounterUnitKHR : uint32_t {
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
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_GENERIC_KHR = VkPerformanceCounterUnitKHR::GenericKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_PERCENTAGE_KHR = VkPerformanceCounterUnitKHR::PercentageKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_NANOSECONDS_KHR = VkPerformanceCounterUnitKHR::NanosecondsKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_BYTES_KHR = VkPerformanceCounterUnitKHR::BytesKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_BYTES_PER_SECOND_KHR = VkPerformanceCounterUnitKHR::BytesPerSecondKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_KELVIN_KHR = VkPerformanceCounterUnitKHR::KelvinKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_WATTS_KHR = VkPerformanceCounterUnitKHR::WattsKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_VOLTS_KHR = VkPerformanceCounterUnitKHR::VoltsKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_AMPS_KHR = VkPerformanceCounterUnitKHR::AmpsKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_HERTZ_KHR = VkPerformanceCounterUnitKHR::HertzKHR;
const VkPerformanceCounterUnitKHR VK_PERFORMANCE_COUNTER_UNIT_CYCLES_KHR = VkPerformanceCounterUnitKHR::CyclesKHR;
enum class VkPerformanceCounterStorageKHR : uint32_t {
    Int32KHR = 0,
    Int64KHR = 1,
    Uint32KHR = 2,
    Uint64KHR = 3,
    Float32KHR = 4,
    Float64KHR = 5,
};
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_INT32_KHR = VkPerformanceCounterStorageKHR::Int32KHR;
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_INT64_KHR = VkPerformanceCounterStorageKHR::Int64KHR;
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_UINT32_KHR = VkPerformanceCounterStorageKHR::Uint32KHR;
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_UINT64_KHR = VkPerformanceCounterStorageKHR::Uint64KHR;
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_FLOAT32_KHR = VkPerformanceCounterStorageKHR::Float32KHR;
const VkPerformanceCounterStorageKHR VK_PERFORMANCE_COUNTER_STORAGE_FLOAT64_KHR = VkPerformanceCounterStorageKHR::Float64KHR;
enum class VkPerformanceConfigurationTypeINTEL : uint32_t {
    CommandQueueMetricsDiscoveryActivatedINTEL = 0,
};
const VkPerformanceConfigurationTypeINTEL VK_PERFORMANCE_CONFIGURATION_TYPE_COMMAND_QUEUE_METRICS_DISCOVERY_ACTIVATED_INTEL = VkPerformanceConfigurationTypeINTEL::CommandQueueMetricsDiscoveryActivatedINTEL;
enum class VkQueryPoolSamplingModeINTEL : uint32_t {
    ManualINTEL = 0,
};
const VkQueryPoolSamplingModeINTEL VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTEL = VkQueryPoolSamplingModeINTEL::ManualINTEL;
enum class VkPerformanceOverrideTypeINTEL : uint32_t {
    NullHardwareINTEL = 0,
    FlushGpuCachesINTEL = 1,
};
const VkPerformanceOverrideTypeINTEL VK_PERFORMANCE_OVERRIDE_TYPE_NULL_HARDWARE_INTEL = VkPerformanceOverrideTypeINTEL::NullHardwareINTEL;
const VkPerformanceOverrideTypeINTEL VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL = VkPerformanceOverrideTypeINTEL::FlushGpuCachesINTEL;
enum class VkPerformanceParameterTypeINTEL : uint32_t {
    HwCountersSupportedINTEL = 0,
    StreamMarkerValidBitsINTEL = 1,
};
const VkPerformanceParameterTypeINTEL VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL = VkPerformanceParameterTypeINTEL::HwCountersSupportedINTEL;
const VkPerformanceParameterTypeINTEL VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL = VkPerformanceParameterTypeINTEL::StreamMarkerValidBitsINTEL;
enum class VkPerformanceValueTypeINTEL : uint32_t {
    Uint32INTEL = 0,
    Uint64INTEL = 1,
    FloatINTEL = 2,
    BoolINTEL = 3,
    StringINTEL = 4,
};
const VkPerformanceValueTypeINTEL VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL = VkPerformanceValueTypeINTEL::Uint32INTEL;
const VkPerformanceValueTypeINTEL VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL = VkPerformanceValueTypeINTEL::Uint64INTEL;
const VkPerformanceValueTypeINTEL VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL = VkPerformanceValueTypeINTEL::FloatINTEL;
const VkPerformanceValueTypeINTEL VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL = VkPerformanceValueTypeINTEL::BoolINTEL;
const VkPerformanceValueTypeINTEL VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL = VkPerformanceValueTypeINTEL::StringINTEL;
enum class VkLineRasterizationModeEXT : uint32_t {
    DefaultEXT = 0,
    RectangularEXT = 1,
    BresenhamEXT = 2,
    RectangularSmoothEXT = 3,
};
const VkLineRasterizationModeEXT VK_LINE_RASTERIZATION_MODE_DEFAULT_EXT = VkLineRasterizationModeEXT::DefaultEXT;
const VkLineRasterizationModeEXT VK_LINE_RASTERIZATION_MODE_RECTANGULAR_EXT = VkLineRasterizationModeEXT::RectangularEXT;
const VkLineRasterizationModeEXT VK_LINE_RASTERIZATION_MODE_BRESENHAM_EXT = VkLineRasterizationModeEXT::BresenhamEXT;
const VkLineRasterizationModeEXT VK_LINE_RASTERIZATION_MODE_RECTANGULAR_SMOOTH_EXT = VkLineRasterizationModeEXT::RectangularSmoothEXT;
enum class VkFragmentShadingRateNV : uint32_t {
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
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV = VkFragmentShadingRateNV::e1InvocationPerPixelNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer1X2PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer2X1PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer2X2PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer2X4PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer4X2PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV = VkFragmentShadingRateNV::e1InvocationPer4X4PixelsNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV = VkFragmentShadingRateNV::e2InvocationsPerPixelNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV = VkFragmentShadingRateNV::e4InvocationsPerPixelNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV = VkFragmentShadingRateNV::e8InvocationsPerPixelNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV = VkFragmentShadingRateNV::e16InvocationsPerPixelNV;
const VkFragmentShadingRateNV VK_FRAGMENT_SHADING_RATE_NO_INVOCATIONS_NV = VkFragmentShadingRateNV::NoInvocationsNV;
enum class VkFragmentShadingRateTypeNV : uint32_t {
    FragmentSizeNV = 0,
    EnumsNV = 1,
};
const VkFragmentShadingRateTypeNV VK_FRAGMENT_SHADING_RATE_TYPE_FRAGMENT_SIZE_NV = VkFragmentShadingRateTypeNV::FragmentSizeNV;
const VkFragmentShadingRateTypeNV VK_FRAGMENT_SHADING_RATE_TYPE_ENUMS_NV = VkFragmentShadingRateTypeNV::EnumsNV;
enum class VkColorSpaceKHR : uint32_t {
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
const VkColorSpaceKHR VK_COLOR_SPACE_SRGB_NONLINEAR_KHR = VkColorSpaceKHR::SrgbNonlinearKHR;
const VkColorSpaceKHR VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT = VkColorSpaceKHR::DisplayP3NonlinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT = VkColorSpaceKHR::ExtendedSrgbLinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT = VkColorSpaceKHR::DisplayP3LinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT = VkColorSpaceKHR::DciP3NonlinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_BT709_LINEAR_EXT = VkColorSpaceKHR::Bt709LinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_BT709_NONLINEAR_EXT = VkColorSpaceKHR::Bt709NonlinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_BT2020_LINEAR_EXT = VkColorSpaceKHR::Bt2020LinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_HDR10_ST2084_EXT = VkColorSpaceKHR::Hdr10St2084EXT;
const VkColorSpaceKHR VK_COLOR_SPACE_DOLBYVISION_EXT = VkColorSpaceKHR::DolbyvisionEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_HDR10_HLG_EXT = VkColorSpaceKHR::Hdr10HlgEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT = VkColorSpaceKHR::AdobergbLinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT = VkColorSpaceKHR::AdobergbNonlinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_PASS_THROUGH_EXT = VkColorSpaceKHR::PassThroughEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT = VkColorSpaceKHR::ExtendedSrgbNonlinearEXT;
const VkColorSpaceKHR VK_COLOR_SPACE_DISPLAY_NATIVE_AMD = VkColorSpaceKHR::DisplayNativeAMD;
enum class VkPresentModeKHR : uint32_t {
    ImmediateKHR = 0,
    MailboxKHR = 1,
    FifoKHR = 2,
    FifoRelaxedKHR = 3,
    SharedDemandRefreshKHR = 1000111000,
    SharedContinuousRefreshKHR = 1000111001,
};
const VkPresentModeKHR VK_PRESENT_MODE_IMMEDIATE_KHR = VkPresentModeKHR::ImmediateKHR;
const VkPresentModeKHR VK_PRESENT_MODE_MAILBOX_KHR = VkPresentModeKHR::MailboxKHR;
const VkPresentModeKHR VK_PRESENT_MODE_FIFO_KHR = VkPresentModeKHR::FifoKHR;
const VkPresentModeKHR VK_PRESENT_MODE_FIFO_RELAXED_KHR = VkPresentModeKHR::FifoRelaxedKHR;
const VkPresentModeKHR VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR = VkPresentModeKHR::SharedDemandRefreshKHR;
const VkPresentModeKHR VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR = VkPresentModeKHR::SharedContinuousRefreshKHR;
enum class VkDebugReportObjectTypeEXT : uint32_t {
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
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT = VkDebugReportObjectTypeEXT::UnknownEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT = VkDebugReportObjectTypeEXT::InstanceEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT = VkDebugReportObjectTypeEXT::PhysicalDeviceEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT = VkDebugReportObjectTypeEXT::DeviceEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT = VkDebugReportObjectTypeEXT::QueueEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT = VkDebugReportObjectTypeEXT::SemaphoreEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT = VkDebugReportObjectTypeEXT::CommandBufferEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT = VkDebugReportObjectTypeEXT::FenceEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT = VkDebugReportObjectTypeEXT::DeviceMemoryEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT = VkDebugReportObjectTypeEXT::BufferEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT = VkDebugReportObjectTypeEXT::ImageEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT = VkDebugReportObjectTypeEXT::EventEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT = VkDebugReportObjectTypeEXT::QueryPoolEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT = VkDebugReportObjectTypeEXT::BufferViewEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT = VkDebugReportObjectTypeEXT::ImageViewEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT = VkDebugReportObjectTypeEXT::ShaderModuleEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT = VkDebugReportObjectTypeEXT::PipelineCacheEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT = VkDebugReportObjectTypeEXT::PipelineLayoutEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT = VkDebugReportObjectTypeEXT::RenderPassEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT = VkDebugReportObjectTypeEXT::PipelineEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT = VkDebugReportObjectTypeEXT::DescriptorSetLayoutEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT = VkDebugReportObjectTypeEXT::SamplerEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT = VkDebugReportObjectTypeEXT::DescriptorPoolEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT = VkDebugReportObjectTypeEXT::DescriptorSetEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT = VkDebugReportObjectTypeEXT::FramebufferEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT = VkDebugReportObjectTypeEXT::CommandPoolEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT = VkDebugReportObjectTypeEXT::SurfaceKhrEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT = VkDebugReportObjectTypeEXT::SwapchainKhrEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT = VkDebugReportObjectTypeEXT::DebugReportCallbackExtEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT = VkDebugReportObjectTypeEXT::DisplayKhrEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT = VkDebugReportObjectTypeEXT::DisplayModeKhrEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT = VkDebugReportObjectTypeEXT::ValidationCacheExtEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION_EXT = VkDebugReportObjectTypeEXT::SamplerYcbcrConversionEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_EXT = VkDebugReportObjectTypeEXT::DescriptorUpdateTemplateEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR_EXT = VkDebugReportObjectTypeEXT::AccelerationStructureKhrEXT;
const VkDebugReportObjectTypeEXT VK_DEBUG_REPORT_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV_EXT = VkDebugReportObjectTypeEXT::AccelerationStructureNvEXT;
enum class VkDeviceMemoryReportEventTypeEXT : uint32_t {
    AllocateEXT = 0,
    FreeEXT = 1,
    ImportEXT = 2,
    UnimportEXT = 3,
    AllocationFailedEXT = 4,
};
const VkDeviceMemoryReportEventTypeEXT VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATE_EXT = VkDeviceMemoryReportEventTypeEXT::AllocateEXT;
const VkDeviceMemoryReportEventTypeEXT VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_FREE_EXT = VkDeviceMemoryReportEventTypeEXT::FreeEXT;
const VkDeviceMemoryReportEventTypeEXT VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_IMPORT_EXT = VkDeviceMemoryReportEventTypeEXT::ImportEXT;
const VkDeviceMemoryReportEventTypeEXT VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_UNIMPORT_EXT = VkDeviceMemoryReportEventTypeEXT::UnimportEXT;
const VkDeviceMemoryReportEventTypeEXT VK_DEVICE_MEMORY_REPORT_EVENT_TYPE_ALLOCATION_FAILED_EXT = VkDeviceMemoryReportEventTypeEXT::AllocationFailedEXT;
enum class VkRasterizationOrderAMD : uint32_t {
    StrictAMD = 0,
    RelaxedAMD = 1,
};
const VkRasterizationOrderAMD VK_RASTERIZATION_ORDER_STRICT_AMD = VkRasterizationOrderAMD::StrictAMD;
const VkRasterizationOrderAMD VK_RASTERIZATION_ORDER_RELAXED_AMD = VkRasterizationOrderAMD::RelaxedAMD;
enum class VkValidationCheckEXT : uint32_t {
    AllEXT = 0,
    ShadersEXT = 1,
};
const VkValidationCheckEXT VK_VALIDATION_CHECK_ALL_EXT = VkValidationCheckEXT::AllEXT;
const VkValidationCheckEXT VK_VALIDATION_CHECK_SHADERS_EXT = VkValidationCheckEXT::ShadersEXT;
enum class VkValidationFeatureEnableEXT : uint32_t {
    GpuAssistedEXT = 0,
    GpuAssistedReserveBindingSlotEXT = 1,
    BestPracticesEXT = 2,
    DebugPrintfEXT = 3,
    SynchronizationValidationEXT = 4,
};
const VkValidationFeatureEnableEXT VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT = VkValidationFeatureEnableEXT::GpuAssistedEXT;
const VkValidationFeatureEnableEXT VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT = VkValidationFeatureEnableEXT::GpuAssistedReserveBindingSlotEXT;
const VkValidationFeatureEnableEXT VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT = VkValidationFeatureEnableEXT::BestPracticesEXT;
const VkValidationFeatureEnableEXT VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT = VkValidationFeatureEnableEXT::DebugPrintfEXT;
const VkValidationFeatureEnableEXT VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT = VkValidationFeatureEnableEXT::SynchronizationValidationEXT;
enum class VkValidationFeatureDisableEXT : uint32_t {
    AllEXT = 0,
    ShadersEXT = 1,
    ThreadSafetyEXT = 2,
    ApiParametersEXT = 3,
    ObjectLifetimesEXT = 4,
    CoreChecksEXT = 5,
    UniqueHandlesEXT = 6,
};
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_ALL_EXT = VkValidationFeatureDisableEXT::AllEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT = VkValidationFeatureDisableEXT::ShadersEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT = VkValidationFeatureDisableEXT::ThreadSafetyEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT = VkValidationFeatureDisableEXT::ApiParametersEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT = VkValidationFeatureDisableEXT::ObjectLifetimesEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT = VkValidationFeatureDisableEXT::CoreChecksEXT;
const VkValidationFeatureDisableEXT VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT = VkValidationFeatureDisableEXT::UniqueHandlesEXT;
enum class VkDisplayPowerStateEXT : uint32_t {
    OffEXT = 0,
    SuspendEXT = 1,
    OnEXT = 2,
};
const VkDisplayPowerStateEXT VK_DISPLAY_POWER_STATE_OFF_EXT = VkDisplayPowerStateEXT::OffEXT;
const VkDisplayPowerStateEXT VK_DISPLAY_POWER_STATE_SUSPEND_EXT = VkDisplayPowerStateEXT::SuspendEXT;
const VkDisplayPowerStateEXT VK_DISPLAY_POWER_STATE_ON_EXT = VkDisplayPowerStateEXT::OnEXT;
enum class VkDeviceEventTypeEXT : uint32_t {
    DisplayHotplugEXT = 0,
};
const VkDeviceEventTypeEXT VK_DEVICE_EVENT_TYPE_DISPLAY_HOTPLUG_EXT = VkDeviceEventTypeEXT::DisplayHotplugEXT;
enum class VkDisplayEventTypeEXT : uint32_t {
    FirstPixelOutEXT = 0,
};
const VkDisplayEventTypeEXT VK_DISPLAY_EVENT_TYPE_FIRST_PIXEL_OUT_EXT = VkDisplayEventTypeEXT::FirstPixelOutEXT;
enum class VkTessellationDomainOrigin : uint32_t {
    UpperLeft = 0,
    LowerLeft = 1,
};
const VkTessellationDomainOrigin VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT = VkTessellationDomainOrigin::UpperLeft;
const VkTessellationDomainOrigin VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT = VkTessellationDomainOrigin::LowerLeft;
using VkTessellationDomainOriginKHR = VkTessellationDomainOrigin;
enum class VkSamplerYcbcrModelConversion : uint32_t {
    RgbIdentity = 0,
    YcbcrIdentity = 1,
    Ycbcr709 = 2,
    Ycbcr601 = 3,
    Ycbcr2020 = 4,
};
const VkSamplerYcbcrModelConversion VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY = VkSamplerYcbcrModelConversion::RgbIdentity;
const VkSamplerYcbcrModelConversion VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY = VkSamplerYcbcrModelConversion::YcbcrIdentity;
const VkSamplerYcbcrModelConversion VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709 = VkSamplerYcbcrModelConversion::Ycbcr709;
const VkSamplerYcbcrModelConversion VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601 = VkSamplerYcbcrModelConversion::Ycbcr601;
const VkSamplerYcbcrModelConversion VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020 = VkSamplerYcbcrModelConversion::Ycbcr2020;
using VkSamplerYcbcrModelConversionKHR = VkSamplerYcbcrModelConversion;
enum class VkSamplerYcbcrRange : uint32_t {
    ItuFull = 0,
    ItuNarrow = 1,
};
const VkSamplerYcbcrRange VK_SAMPLER_YCBCR_RANGE_ITU_FULL = VkSamplerYcbcrRange::ItuFull;
const VkSamplerYcbcrRange VK_SAMPLER_YCBCR_RANGE_ITU_NARROW = VkSamplerYcbcrRange::ItuNarrow;
using VkSamplerYcbcrRangeKHR = VkSamplerYcbcrRange;
enum class VkChromaLocation : uint32_t {
    CositedEven = 0,
    Midpoint = 1,
};
const VkChromaLocation VK_CHROMA_LOCATION_COSITED_EVEN = VkChromaLocation::CositedEven;
const VkChromaLocation VK_CHROMA_LOCATION_MIDPOINT = VkChromaLocation::Midpoint;
using VkChromaLocationKHR = VkChromaLocation;
enum class VkSamplerReductionMode : uint32_t {
    WeightedAverage = 0,
    Min = 1,
    Max = 2,
};
const VkSamplerReductionMode VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE = VkSamplerReductionMode::WeightedAverage;
const VkSamplerReductionMode VK_SAMPLER_REDUCTION_MODE_MIN = VkSamplerReductionMode::Min;
const VkSamplerReductionMode VK_SAMPLER_REDUCTION_MODE_MAX = VkSamplerReductionMode::Max;
using VkSamplerReductionModeEXT = VkSamplerReductionMode;
enum class VkBlendOverlapEXT : uint32_t {
    UncorrelatedEXT = 0,
    DisjointEXT = 1,
    ConjointEXT = 2,
};
const VkBlendOverlapEXT VK_BLEND_OVERLAP_UNCORRELATED_EXT = VkBlendOverlapEXT::UncorrelatedEXT;
const VkBlendOverlapEXT VK_BLEND_OVERLAP_DISJOINT_EXT = VkBlendOverlapEXT::DisjointEXT;
const VkBlendOverlapEXT VK_BLEND_OVERLAP_CONJOINT_EXT = VkBlendOverlapEXT::ConjointEXT;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum class VkFullScreenExclusiveEXT : uint32_t {
    DefaultEXT = 0,
    AllowedEXT = 1,
    DisallowedEXT = 2,
    ApplicationControlledEXT = 3,
};
const VkFullScreenExclusiveEXT VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT = VkFullScreenExclusiveEXT::DefaultEXT;
const VkFullScreenExclusiveEXT VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT = VkFullScreenExclusiveEXT::AllowedEXT;
const VkFullScreenExclusiveEXT VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT = VkFullScreenExclusiveEXT::DisallowedEXT;
const VkFullScreenExclusiveEXT VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT = VkFullScreenExclusiveEXT::ApplicationControlledEXT;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
enum class VkShaderFloatControlsIndependence : uint32_t {
    e32BitOnly = 0,
    All = 1,
    None = 2,
};
const VkShaderFloatControlsIndependence VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY = VkShaderFloatControlsIndependence::e32BitOnly;
const VkShaderFloatControlsIndependence VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_ALL = VkShaderFloatControlsIndependence::All;
const VkShaderFloatControlsIndependence VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_NONE = VkShaderFloatControlsIndependence::None;
using VkShaderFloatControlsIndependenceKHR = VkShaderFloatControlsIndependence;
enum class VkFragmentShadingRateCombinerOpKHR : uint32_t {
    KeepKHR = 0,
    ReplaceKHR = 1,
    MinKHR = 2,
    MaxKHR = 3,
    MulKHR = 4,
};
const VkFragmentShadingRateCombinerOpKHR VK_FRAGMENT_SHADING_RATE_COMBINER_OP_KEEP_KHR = VkFragmentShadingRateCombinerOpKHR::KeepKHR;
const VkFragmentShadingRateCombinerOpKHR VK_FRAGMENT_SHADING_RATE_COMBINER_OP_REPLACE_KHR = VkFragmentShadingRateCombinerOpKHR::ReplaceKHR;
const VkFragmentShadingRateCombinerOpKHR VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MIN_KHR = VkFragmentShadingRateCombinerOpKHR::MinKHR;
const VkFragmentShadingRateCombinerOpKHR VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MAX_KHR = VkFragmentShadingRateCombinerOpKHR::MaxKHR;
const VkFragmentShadingRateCombinerOpKHR VK_FRAGMENT_SHADING_RATE_COMBINER_OP_MUL_KHR = VkFragmentShadingRateCombinerOpKHR::MulKHR;
enum class VkVendorId : uint32_t {
    VIV = 0x10001,
    VSI = 0x10002,
    Kazan = 0x10003,
    Codeplay = 0x10004,
    MESA = 0x10005,
    Pocl = 0x10006,
};
const VkVendorId VK_VENDOR_ID_VIV = VkVendorId::VIV;
const VkVendorId VK_VENDOR_ID_VSI = VkVendorId::VSI;
const VkVendorId VK_VENDOR_ID_KAZAN = VkVendorId::Kazan;
const VkVendorId VK_VENDOR_ID_CODEPLAY = VkVendorId::Codeplay;
const VkVendorId VK_VENDOR_ID_MESA = VkVendorId::MESA;
const VkVendorId VK_VENDOR_ID_POCL = VkVendorId::Pocl;
enum class VkDriverId : uint32_t {
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
    CoreaviProprietary = 15,
};
const VkDriverId VK_DRIVER_ID_AMD_PROPRIETARY = VkDriverId::AmdProprietary;
const VkDriverId VK_DRIVER_ID_AMD_OPEN_SOURCE = VkDriverId::AmdOpenSource;
const VkDriverId VK_DRIVER_ID_MESA_RADV = VkDriverId::MesaRadv;
const VkDriverId VK_DRIVER_ID_NVIDIA_PROPRIETARY = VkDriverId::NvidiaProprietary;
const VkDriverId VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS = VkDriverId::IntelProprietaryWindows;
const VkDriverId VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA = VkDriverId::IntelOpenSourceMESA;
const VkDriverId VK_DRIVER_ID_IMAGINATION_PROPRIETARY = VkDriverId::ImaginationProprietary;
const VkDriverId VK_DRIVER_ID_QUALCOMM_PROPRIETARY = VkDriverId::QualcommProprietary;
const VkDriverId VK_DRIVER_ID_ARM_PROPRIETARY = VkDriverId::ArmProprietary;
const VkDriverId VK_DRIVER_ID_GOOGLE_SWIFTSHADER = VkDriverId::GoogleSwiftshader;
const VkDriverId VK_DRIVER_ID_GGP_PROPRIETARY = VkDriverId::GgpProprietary;
const VkDriverId VK_DRIVER_ID_BROADCOM_PROPRIETARY = VkDriverId::BroadcomProprietary;
const VkDriverId VK_DRIVER_ID_MESA_LLVMPIPE = VkDriverId::MesaLlvmpipe;
const VkDriverId VK_DRIVER_ID_MOLTENVK = VkDriverId::Moltenvk;
const VkDriverId VK_DRIVER_ID_COREAVI_PROPRIETARY = VkDriverId::CoreaviProprietary;
using VkDriverIdKHR = VkDriverId;
enum class VkShadingRatePaletteEntryNV : uint32_t {
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
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV = VkShadingRatePaletteEntryNV::NoInvocationsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV = VkShadingRatePaletteEntryNV::e16InvocationsPerPixelNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV = VkShadingRatePaletteEntryNV::e8InvocationsPerPixelNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV = VkShadingRatePaletteEntryNV::e4InvocationsPerPixelNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV = VkShadingRatePaletteEntryNV::e2InvocationsPerPixelNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV = VkShadingRatePaletteEntryNV::e1InvocationPerPixelNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer2X1PixelsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer1X2PixelsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer2X2PixelsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer4X2PixelsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer2X4PixelsNV;
const VkShadingRatePaletteEntryNV VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV = VkShadingRatePaletteEntryNV::e1InvocationPer4X4PixelsNV;
enum class VkCoarseSampleOrderTypeNV : uint32_t {
    DefaultNV = 0,
    CustomNV = 1,
    PixelMajorNV = 2,
    SampleMajorNV = 3,
};
const VkCoarseSampleOrderTypeNV VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV = VkCoarseSampleOrderTypeNV::DefaultNV;
const VkCoarseSampleOrderTypeNV VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV = VkCoarseSampleOrderTypeNV::CustomNV;
const VkCoarseSampleOrderTypeNV VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV = VkCoarseSampleOrderTypeNV::PixelMajorNV;
const VkCoarseSampleOrderTypeNV VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV = VkCoarseSampleOrderTypeNV::SampleMajorNV;
enum class VkPipelineExecutableStatisticFormatKHR : uint32_t {
    Bool32KHR = 0,
    Int64KHR = 1,
    Uint64KHR = 2,
    Float64KHR = 3,
};
const VkPipelineExecutableStatisticFormatKHR VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_BOOL32_KHR = VkPipelineExecutableStatisticFormatKHR::Bool32KHR;
const VkPipelineExecutableStatisticFormatKHR VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_INT64_KHR = VkPipelineExecutableStatisticFormatKHR::Int64KHR;
const VkPipelineExecutableStatisticFormatKHR VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_UINT64_KHR = VkPipelineExecutableStatisticFormatKHR::Uint64KHR;
const VkPipelineExecutableStatisticFormatKHR VK_PIPELINE_EXECUTABLE_STATISTIC_FORMAT_FLOAT64_KHR = VkPipelineExecutableStatisticFormatKHR::Float64KHR;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum class VkQueryResultStatusKHR : uint32_t {
    ErrorKHR = -1,
    NotReadyKHR = 0,
    CompleteKHR = 1,
};
const VkQueryResultStatusKHR VK_QUERY_RESULT_STATUS_ERROR_KHR = VkQueryResultStatusKHR::ErrorKHR;
const VkQueryResultStatusKHR VK_QUERY_RESULT_STATUS_NOT_READY_KHR = VkQueryResultStatusKHR::NotReadyKHR;
const VkQueryResultStatusKHR VK_QUERY_RESULT_STATUS_COMPLETE_KHR = VkQueryResultStatusKHR::CompleteKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
enum class VkPipelineCacheCreateFlagBits: uint32_t {
    ExternallySynchronizedBitEXT = 1,
};
const VkPipelineCacheCreateFlagBits VK_PIPELINE_CACHE_CREATE_EXTERNALLY_SYNCHRONIZED_BIT_EXT = VkPipelineCacheCreateFlagBits::ExternallySynchronizedBitEXT;
enum class VkQueueFlagBits: uint32_t {
    Graphics = 1,
    Compute = 2,
    Transfer = 4,
    SparseBinding = 8,
    VideoDecodeBitKHR = 32,
    VideoEncodeBitKHR = 64,
    Protected = 16,
};
const VkQueueFlagBits VK_QUEUE_GRAPHICS_BIT = VkQueueFlagBits::Graphics;
const VkQueueFlagBits VK_QUEUE_COMPUTE_BIT = VkQueueFlagBits::Compute;
const VkQueueFlagBits VK_QUEUE_TRANSFER_BIT = VkQueueFlagBits::Transfer;
const VkQueueFlagBits VK_QUEUE_SPARSE_BINDING_BIT = VkQueueFlagBits::SparseBinding;
const VkQueueFlagBits VK_QUEUE_VIDEO_DECODE_BIT_KHR = VkQueueFlagBits::VideoDecodeBitKHR;
const VkQueueFlagBits VK_QUEUE_VIDEO_ENCODE_BIT_KHR = VkQueueFlagBits::VideoEncodeBitKHR;
const VkQueueFlagBits VK_QUEUE_PROTECTED_BIT = VkQueueFlagBits::Protected;
enum class VkCullModeFlagBits: uint32_t {
    None = 0,
    Front = 1,
    Back = 2,
    FrontAndBack = 0x00000003,
};
const VkCullModeFlagBits VK_CULL_MODE_NONE = VkCullModeFlagBits::None;
const VkCullModeFlagBits VK_CULL_MODE_FRONT_BIT = VkCullModeFlagBits::Front;
const VkCullModeFlagBits VK_CULL_MODE_BACK_BIT = VkCullModeFlagBits::Back;
const VkCullModeFlagBits VK_CULL_MODE_FRONT_AND_BACK = VkCullModeFlagBits::FrontAndBack;
enum class VkRenderPassCreateFlagBits: uint32_t {
    TransformBitQCOM = 2,
};
const VkRenderPassCreateFlagBits VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM = VkRenderPassCreateFlagBits::TransformBitQCOM;
enum class VkDeviceQueueCreateFlagBits: uint32_t {
    Protected = 1,
};
const VkDeviceQueueCreateFlagBits VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT = VkDeviceQueueCreateFlagBits::Protected;
enum class VkMemoryPropertyFlagBits: uint32_t {
    DeviceLocal = 1,
    HostVisible = 2,
    HostCoherent = 4,
    HostCached = 8,
    LazilyAllocated = 16,
    DeviceCoherentBitAMD = 64,
    DeviceUncachedBitAMD = 128,
    Protected = 32,
};
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT = VkMemoryPropertyFlagBits::DeviceLocal;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT = VkMemoryPropertyFlagBits::HostVisible;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_HOST_COHERENT_BIT = VkMemoryPropertyFlagBits::HostCoherent;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_HOST_CACHED_BIT = VkMemoryPropertyFlagBits::HostCached;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT = VkMemoryPropertyFlagBits::LazilyAllocated;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD = VkMemoryPropertyFlagBits::DeviceCoherentBitAMD;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD = VkMemoryPropertyFlagBits::DeviceUncachedBitAMD;
const VkMemoryPropertyFlagBits VK_MEMORY_PROPERTY_PROTECTED_BIT = VkMemoryPropertyFlagBits::Protected;
enum class VkMemoryHeapFlagBits: uint32_t {
    DeviceLocal = 1,
    MultiInstance = 2,
};
const VkMemoryHeapFlagBits VK_MEMORY_HEAP_DEVICE_LOCAL_BIT = VkMemoryHeapFlagBits::DeviceLocal;
const VkMemoryHeapFlagBits VK_MEMORY_HEAP_MULTI_INSTANCE_BIT = VkMemoryHeapFlagBits::MultiInstance;
enum class VkAccessFlagBits: uint32_t {
    NoneKHR = 1,
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
const VkAccessFlagBits VK_ACCESS_NONE_KHR = VkAccessFlagBits::NoneKHR;
const VkAccessFlagBits VK_ACCESS_INDEX_READ_BIT = VkAccessFlagBits::IndexRead;
const VkAccessFlagBits VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT = VkAccessFlagBits::VertexAttributeRead;
const VkAccessFlagBits VK_ACCESS_UNIFORM_READ_BIT = VkAccessFlagBits::UniformRead;
const VkAccessFlagBits VK_ACCESS_INPUT_ATTACHMENT_READ_BIT = VkAccessFlagBits::InputAttachmentRead;
const VkAccessFlagBits VK_ACCESS_SHADER_READ_BIT = VkAccessFlagBits::ShaderRead;
const VkAccessFlagBits VK_ACCESS_SHADER_WRITE_BIT = VkAccessFlagBits::ShaderWrite;
const VkAccessFlagBits VK_ACCESS_COLOR_ATTACHMENT_READ_BIT = VkAccessFlagBits::ColorAttachmentRead;
const VkAccessFlagBits VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT = VkAccessFlagBits::ColorAttachmentWrite;
const VkAccessFlagBits VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = VkAccessFlagBits::DepthStencilAttachmentRead;
const VkAccessFlagBits VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = VkAccessFlagBits::DepthStencilAttachmentWrite;
const VkAccessFlagBits VK_ACCESS_TRANSFER_READ_BIT = VkAccessFlagBits::TransferRead;
const VkAccessFlagBits VK_ACCESS_TRANSFER_WRITE_BIT = VkAccessFlagBits::TransferWrite;
const VkAccessFlagBits VK_ACCESS_HOST_READ_BIT = VkAccessFlagBits::HostRead;
const VkAccessFlagBits VK_ACCESS_HOST_WRITE_BIT = VkAccessFlagBits::HostWrite;
const VkAccessFlagBits VK_ACCESS_MEMORY_READ_BIT = VkAccessFlagBits::MemoryRead;
const VkAccessFlagBits VK_ACCESS_MEMORY_WRITE_BIT = VkAccessFlagBits::MemoryWrite;
const VkAccessFlagBits VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT = VkAccessFlagBits::TransformFeedbackWriteBitEXT;
const VkAccessFlagBits VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = VkAccessFlagBits::TransformFeedbackCounterReadBitEXT;
const VkAccessFlagBits VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = VkAccessFlagBits::TransformFeedbackCounterWriteBitEXT;
const VkAccessFlagBits VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT = VkAccessFlagBits::ConditionalRenderingReadBitEXT;
const VkAccessFlagBits VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = VkAccessFlagBits::ColorAttachmentReadNoncoherentBitEXT;
const VkAccessFlagBits VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR = VkAccessFlagBits::AccelerationStructureReadBitKHR;
const VkAccessFlagBits VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR = VkAccessFlagBits::AccelerationStructureWriteBitKHR;
const VkAccessFlagBits VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV = VkAccessFlagBits::ShadingRateImageReadBitNV;
const VkAccessFlagBits VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT = VkAccessFlagBits::FragmentDensityMapReadBitEXT;
const VkAccessFlagBits VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV = VkAccessFlagBits::CommandPreprocessReadBitNV;
const VkAccessFlagBits VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV = VkAccessFlagBits::CommandPreprocessWriteBitNV;
enum class VkBufferUsageFlagBits: uint32_t {
    TransferSrc = 1,
    TransferDst = 2,
    UniformTexelBuffer = 4,
    StorageTexelBuffer = 8,
    UniformBuffer = 16,
    StorageBuffer = 32,
    IndexBuffer = 64,
    VertexBuffer = 128,
    IndirectBuffer = 256,
    VideoDecodeSrcBitKHR = 8192,
    VideoDecodeDstBitKHR = 16384,
    VideoEncodeDstBitKHR = 32768,
    VideoEncodeSrcBitKHR = 65536,
    TransformFeedbackBufferBitEXT = 2048,
    TransformFeedbackCounterBufferBitEXT = 4096,
    ConditionalRenderingBitEXT = 512,
    AccelerationStructureBuildInputReadOnlyBitKHR = 524288,
    AccelerationStructureStorageBitKHR = 1048576,
    ShaderBindingTableBitKHR = 1024,
    ShaderDeviceAddress = 131072,
};
const VkBufferUsageFlagBits VK_BUFFER_USAGE_TRANSFER_SRC_BIT = VkBufferUsageFlagBits::TransferSrc;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_TRANSFER_DST_BIT = VkBufferUsageFlagBits::TransferDst;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = VkBufferUsageFlagBits::UniformTexelBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = VkBufferUsageFlagBits::StorageTexelBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT = VkBufferUsageFlagBits::UniformBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_STORAGE_BUFFER_BIT = VkBufferUsageFlagBits::StorageBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_INDEX_BUFFER_BIT = VkBufferUsageFlagBits::IndexBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_VERTEX_BUFFER_BIT = VkBufferUsageFlagBits::VertexBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT = VkBufferUsageFlagBits::IndirectBuffer;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR = VkBufferUsageFlagBits::VideoDecodeSrcBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR = VkBufferUsageFlagBits::VideoDecodeDstBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR = VkBufferUsageFlagBits::VideoEncodeDstBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR = VkBufferUsageFlagBits::VideoEncodeSrcBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT = VkBufferUsageFlagBits::TransformFeedbackBufferBitEXT;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT = VkBufferUsageFlagBits::TransformFeedbackCounterBufferBitEXT;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT = VkBufferUsageFlagBits::ConditionalRenderingBitEXT;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR = VkBufferUsageFlagBits::AccelerationStructureBuildInputReadOnlyBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR = VkBufferUsageFlagBits::AccelerationStructureStorageBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR = VkBufferUsageFlagBits::ShaderBindingTableBitKHR;
const VkBufferUsageFlagBits VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT = VkBufferUsageFlagBits::ShaderDeviceAddress;
enum class VkBufferCreateFlagBits: uint32_t {
    SparseBinding = 1,
    SparseResidency = 2,
    SparseAliased = 4,
    Protected = 8,
    DeviceAddressCaptureReplay = 16,
};
const VkBufferCreateFlagBits VK_BUFFER_CREATE_SPARSE_BINDING_BIT = VkBufferCreateFlagBits::SparseBinding;
const VkBufferCreateFlagBits VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT = VkBufferCreateFlagBits::SparseResidency;
const VkBufferCreateFlagBits VK_BUFFER_CREATE_SPARSE_ALIASED_BIT = VkBufferCreateFlagBits::SparseAliased;
const VkBufferCreateFlagBits VK_BUFFER_CREATE_PROTECTED_BIT = VkBufferCreateFlagBits::Protected;
const VkBufferCreateFlagBits VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT = VkBufferCreateFlagBits::DeviceAddressCaptureReplay;
enum class VkShaderStageFlagBits: uint32_t {
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
const VkShaderStageFlagBits VK_SHADER_STAGE_VERTEX_BIT = VkShaderStageFlagBits::Vertex;
const VkShaderStageFlagBits VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT = VkShaderStageFlagBits::TessellationControl;
const VkShaderStageFlagBits VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT = VkShaderStageFlagBits::TessellationEvaluation;
const VkShaderStageFlagBits VK_SHADER_STAGE_GEOMETRY_BIT = VkShaderStageFlagBits::Geometry;
const VkShaderStageFlagBits VK_SHADER_STAGE_FRAGMENT_BIT = VkShaderStageFlagBits::Fragment;
const VkShaderStageFlagBits VK_SHADER_STAGE_COMPUTE_BIT = VkShaderStageFlagBits::Compute;
const VkShaderStageFlagBits VK_SHADER_STAGE_ALL_GRAPHICS = VkShaderStageFlagBits::AllGraphics;
const VkShaderStageFlagBits VK_SHADER_STAGE_ALL = VkShaderStageFlagBits::All;
const VkShaderStageFlagBits VK_SHADER_STAGE_RAYGEN_BIT_KHR = VkShaderStageFlagBits::RaygenBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_ANY_HIT_BIT_KHR = VkShaderStageFlagBits::AnyHitBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR = VkShaderStageFlagBits::ClosestHitBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_MISS_BIT_KHR = VkShaderStageFlagBits::MissBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_INTERSECTION_BIT_KHR = VkShaderStageFlagBits::IntersectionBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_CALLABLE_BIT_KHR = VkShaderStageFlagBits::CallableBitKHR;
const VkShaderStageFlagBits VK_SHADER_STAGE_TASK_BIT_NV = VkShaderStageFlagBits::TaskBitNV;
const VkShaderStageFlagBits VK_SHADER_STAGE_MESH_BIT_NV = VkShaderStageFlagBits::MeshBitNV;
enum class VkImageUsageFlagBits: uint32_t {
    TransferSrc = 1,
    TransferDst = 2,
    Sampled = 4,
    Storage = 8,
    ColorAttachment = 16,
    DepthStencilAttachment = 32,
    TransientAttachment = 64,
    InputAttachment = 128,
    VideoDecodeDstBitKHR = 1024,
    VideoDecodeSrcBitKHR = 2048,
    VideoDecodeDpbBitKHR = 4096,
    VideoEncodeDstBitKHR = 8192,
    VideoEncodeSrcBitKHR = 16384,
    VideoEncodeDpbBitKHR = 32768,
    ShadingRateImageBitNV = 256,
    FragmentDensityMapBitEXT = 512,
};
const VkImageUsageFlagBits VK_IMAGE_USAGE_TRANSFER_SRC_BIT = VkImageUsageFlagBits::TransferSrc;
const VkImageUsageFlagBits VK_IMAGE_USAGE_TRANSFER_DST_BIT = VkImageUsageFlagBits::TransferDst;
const VkImageUsageFlagBits VK_IMAGE_USAGE_SAMPLED_BIT = VkImageUsageFlagBits::Sampled;
const VkImageUsageFlagBits VK_IMAGE_USAGE_STORAGE_BIT = VkImageUsageFlagBits::Storage;
const VkImageUsageFlagBits VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = VkImageUsageFlagBits::ColorAttachment;
const VkImageUsageFlagBits VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = VkImageUsageFlagBits::DepthStencilAttachment;
const VkImageUsageFlagBits VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = VkImageUsageFlagBits::TransientAttachment;
const VkImageUsageFlagBits VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = VkImageUsageFlagBits::InputAttachment;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR = VkImageUsageFlagBits::VideoDecodeDstBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR = VkImageUsageFlagBits::VideoDecodeSrcBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR = VkImageUsageFlagBits::VideoDecodeDpbBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR = VkImageUsageFlagBits::VideoEncodeDstBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR = VkImageUsageFlagBits::VideoEncodeSrcBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR = VkImageUsageFlagBits::VideoEncodeDpbBitKHR;
const VkImageUsageFlagBits VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV = VkImageUsageFlagBits::ShadingRateImageBitNV;
const VkImageUsageFlagBits VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT = VkImageUsageFlagBits::FragmentDensityMapBitEXT;
enum class VkImageCreateFlagBits: uint32_t {
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
const VkImageCreateFlagBits VK_IMAGE_CREATE_SPARSE_BINDING_BIT = VkImageCreateFlagBits::SparseBinding;
const VkImageCreateFlagBits VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT = VkImageCreateFlagBits::SparseResidency;
const VkImageCreateFlagBits VK_IMAGE_CREATE_SPARSE_ALIASED_BIT = VkImageCreateFlagBits::SparseAliased;
const VkImageCreateFlagBits VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT = VkImageCreateFlagBits::MutableFormat;
const VkImageCreateFlagBits VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT = VkImageCreateFlagBits::CubeCompatible;
const VkImageCreateFlagBits VK_IMAGE_CREATE_CORNER_SAMPLED_BIT_NV = VkImageCreateFlagBits::CornerSampledBitNV;
const VkImageCreateFlagBits VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT = VkImageCreateFlagBits::SampleLocationsCompatibleDepthBitEXT;
const VkImageCreateFlagBits VK_IMAGE_CREATE_SUBSAMPLED_BIT_EXT = VkImageCreateFlagBits::SubsampledBitEXT;
const VkImageCreateFlagBits VK_IMAGE_CREATE_ALIAS_BIT = VkImageCreateFlagBits::Alias;
const VkImageCreateFlagBits VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT = VkImageCreateFlagBits::SplitInstanceBindRegions;
const VkImageCreateFlagBits VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT = VkImageCreateFlagBits::e2DArrayCompatible;
const VkImageCreateFlagBits VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT = VkImageCreateFlagBits::BlockTexelViewCompatible;
const VkImageCreateFlagBits VK_IMAGE_CREATE_EXTENDED_USAGE_BIT = VkImageCreateFlagBits::ExtendedUsage;
const VkImageCreateFlagBits VK_IMAGE_CREATE_PROTECTED_BIT = VkImageCreateFlagBits::Protected;
const VkImageCreateFlagBits VK_IMAGE_CREATE_DISJOINT_BIT = VkImageCreateFlagBits::Disjoint;
enum class VkImageViewCreateFlagBits: uint32_t {
    FragmentDensityMapDynamicBitEXT = 1,
    FragmentDensityMapDeferredBitEXT = 2,
};
const VkImageViewCreateFlagBits VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT = VkImageViewCreateFlagBits::FragmentDensityMapDynamicBitEXT;
const VkImageViewCreateFlagBits VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT = VkImageViewCreateFlagBits::FragmentDensityMapDeferredBitEXT;
enum class VkSamplerCreateFlagBits: uint32_t {
    SubsampledBitEXT = 1,
    SubsampledCoarseReconstructionBitEXT = 2,
};
const VkSamplerCreateFlagBits VK_SAMPLER_CREATE_SUBSAMPLED_BIT_EXT = VkSamplerCreateFlagBits::SubsampledBitEXT;
const VkSamplerCreateFlagBits VK_SAMPLER_CREATE_SUBSAMPLED_COARSE_RECONSTRUCTION_BIT_EXT = VkSamplerCreateFlagBits::SubsampledCoarseReconstructionBitEXT;
enum class VkPipelineCreateFlagBits: uint32_t {
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
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT = VkPipelineCreateFlagBits::DisableOptimization;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT = VkPipelineCreateFlagBits::AllowDerivatives;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_DERIVATIVE_BIT = VkPipelineCreateFlagBits::Derivative;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR = VkPipelineCreateFlagBits::RayTracingNoNullAnyHitShadersBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR = VkPipelineCreateFlagBits::RayTracingNoNullClosestHitShadersBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR = VkPipelineCreateFlagBits::RayTracingNoNullMissShadersBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR = VkPipelineCreateFlagBits::RayTracingNoNullIntersectionShadersBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR = VkPipelineCreateFlagBits::RayTracingSkipTrianglesBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR = VkPipelineCreateFlagBits::RayTracingSkipAabbsBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR = VkPipelineCreateFlagBits::RayTracingShaderGroupHandleCaptureReplayBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV = VkPipelineCreateFlagBits::DeferCompileBitNV;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR = VkPipelineCreateFlagBits::CaptureStatisticsBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR = VkPipelineCreateFlagBits::CaptureInternalRepresentationsBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV = VkPipelineCreateFlagBits::IndirectBindableBitNV;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_LIBRARY_BIT_KHR = VkPipelineCreateFlagBits::LibraryBitKHR;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT = VkPipelineCreateFlagBits::FailOnPipelineCompileRequiredBitEXT;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT_EXT = VkPipelineCreateFlagBits::EarlyReturnOnFailureBitEXT;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT = VkPipelineCreateFlagBits::ViewIndexFromDeviceIndex;
const VkPipelineCreateFlagBits VK_PIPELINE_CREATE_DISPATCH_BASE_BIT = VkPipelineCreateFlagBits::DispatchBase;
enum class VkPipelineShaderStageCreateFlagBits: uint32_t {
    AllowVaryingSubgroupSizeBitEXT = 1,
    RequireFullSubgroupsBitEXT = 2,
};
const VkPipelineShaderStageCreateFlagBits VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT = VkPipelineShaderStageCreateFlagBits::AllowVaryingSubgroupSizeBitEXT;
const VkPipelineShaderStageCreateFlagBits VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT = VkPipelineShaderStageCreateFlagBits::RequireFullSubgroupsBitEXT;
enum class VkColorComponentFlagBits: uint32_t {
    R = 1,
    G = 2,
    B = 4,
    A = 8,
};
const VkColorComponentFlagBits VK_COLOR_COMPONENT_R_BIT = VkColorComponentFlagBits::R;
const VkColorComponentFlagBits VK_COLOR_COMPONENT_G_BIT = VkColorComponentFlagBits::G;
const VkColorComponentFlagBits VK_COLOR_COMPONENT_B_BIT = VkColorComponentFlagBits::B;
const VkColorComponentFlagBits VK_COLOR_COMPONENT_A_BIT = VkColorComponentFlagBits::A;
enum class VkFenceCreateFlagBits: uint32_t {
    Signaled = 1,
};
const VkFenceCreateFlagBits VK_FENCE_CREATE_SIGNALED_BIT = VkFenceCreateFlagBits::Signaled;
enum class VkFormatFeatureFlagBits: uint32_t {
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
    VideoDecodeOutputBitKHR = 33554432,
    VideoDecodeDpbBitKHR = 67108864,
    VideoEncodeInputBitKHR = 134217728,
    VideoEncodeDpbBitKHR = 268435456,
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
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT = VkFormatFeatureFlagBits::SampledImage;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT = VkFormatFeatureFlagBits::StorageImage;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT = VkFormatFeatureFlagBits::StorageImageAtomic;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT = VkFormatFeatureFlagBits::UniformTexelBuffer;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT = VkFormatFeatureFlagBits::StorageTexelBuffer;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT = VkFormatFeatureFlagBits::StorageTexelBufferAtomic;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT = VkFormatFeatureFlagBits::VertexBuffer;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT = VkFormatFeatureFlagBits::ColorAttachment;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT = VkFormatFeatureFlagBits::ColorAttachmentBlend;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT = VkFormatFeatureFlagBits::DepthStencilAttachment;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_BLIT_SRC_BIT = VkFormatFeatureFlagBits::BlitSrc;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_BLIT_DST_BIT = VkFormatFeatureFlagBits::BlitDst;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT = VkFormatFeatureFlagBits::SampledImageFilterLinear;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_IMG = VkFormatFeatureFlagBits::SampledImageFilterCubicBitIMG;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_VIDEO_DECODE_OUTPUT_BIT_KHR = VkFormatFeatureFlagBits::VideoDecodeOutputBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_VIDEO_DECODE_DPB_BIT_KHR = VkFormatFeatureFlagBits::VideoDecodeDpbBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_VIDEO_ENCODE_INPUT_BIT_KHR = VkFormatFeatureFlagBits::VideoEncodeInputBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_VIDEO_ENCODE_DPB_BIT_KHR = VkFormatFeatureFlagBits::VideoEncodeDpbBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR = VkFormatFeatureFlagBits::AccelerationStructureVertexBufferBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_FRAGMENT_DENSITY_MAP_BIT_EXT = VkFormatFeatureFlagBits::FragmentDensityMapBitEXT;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = VkFormatFeatureFlagBits::FragmentShadingRateAttachmentBitKHR;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_TRANSFER_SRC_BIT = VkFormatFeatureFlagBits::TransferSrc;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_TRANSFER_DST_BIT = VkFormatFeatureFlagBits::TransferDst;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT = VkFormatFeatureFlagBits::MidpointChromaSamples;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT = VkFormatFeatureFlagBits::SampledImageYcbcrConversionLinearFilter;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT = VkFormatFeatureFlagBits::SampledImageYcbcrConversionSeparateReconstructionFilter;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT = VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicit;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT = VkFormatFeatureFlagBits::SampledImageYcbcrConversionChromaReconstructionExplicitForceable;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_DISJOINT_BIT = VkFormatFeatureFlagBits::Disjoint;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT = VkFormatFeatureFlagBits::CositedChromaSamples;
const VkFormatFeatureFlagBits VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT = VkFormatFeatureFlagBits::SampledImageFilterMinmax;
enum class VkQueryControlFlagBits: uint32_t {
    Precise = 1,
};
const VkQueryControlFlagBits VK_QUERY_CONTROL_PRECISE_BIT = VkQueryControlFlagBits::Precise;
enum class VkQueryResultFlagBits: uint32_t {
    e64 = 1,
    Wait = 2,
    WithAvailability = 4,
    Partial = 8,
    WithStatusBitKHR = 16,
};
const VkQueryResultFlagBits VK_QUERY_RESULT_64_BIT = VkQueryResultFlagBits::e64;
const VkQueryResultFlagBits VK_QUERY_RESULT_WAIT_BIT = VkQueryResultFlagBits::Wait;
const VkQueryResultFlagBits VK_QUERY_RESULT_WITH_AVAILABILITY_BIT = VkQueryResultFlagBits::WithAvailability;
const VkQueryResultFlagBits VK_QUERY_RESULT_PARTIAL_BIT = VkQueryResultFlagBits::Partial;
const VkQueryResultFlagBits VK_QUERY_RESULT_WITH_STATUS_BIT_KHR = VkQueryResultFlagBits::WithStatusBitKHR;
enum class VkCommandBufferUsageFlagBits: uint32_t {
    OneTimeSubmit = 1,
    RenderPassContinue = 2,
    SimultaneousUse = 4,
};
const VkCommandBufferUsageFlagBits VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT = VkCommandBufferUsageFlagBits::OneTimeSubmit;
const VkCommandBufferUsageFlagBits VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT = VkCommandBufferUsageFlagBits::RenderPassContinue;
const VkCommandBufferUsageFlagBits VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT = VkCommandBufferUsageFlagBits::SimultaneousUse;
enum class VkQueryPipelineStatisticFlagBits: uint32_t {
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
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT = VkQueryPipelineStatisticFlagBits::InputAssemblyVertices;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT = VkQueryPipelineStatisticFlagBits::InputAssemblyPrimitives;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::VertexShaderInvocations;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::GeometryShaderInvocations;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT = VkQueryPipelineStatisticFlagBits::GeometryShaderPrimitives;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::ClippingInvocations;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT = VkQueryPipelineStatisticFlagBits::ClippingPrimitives;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::FragmentShaderInvocations;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT = VkQueryPipelineStatisticFlagBits::TessellationControlShaderPatches;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::TessellationEvaluationShaderInvocations;
const VkQueryPipelineStatisticFlagBits VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT = VkQueryPipelineStatisticFlagBits::ComputeShaderInvocations;
enum class VkImageAspectFlagBits: uint32_t {
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
const VkImageAspectFlagBits VK_IMAGE_ASPECT_COLOR_BIT = VkImageAspectFlagBits::Color;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_DEPTH_BIT = VkImageAspectFlagBits::Depth;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_STENCIL_BIT = VkImageAspectFlagBits::Stencil;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_METADATA_BIT = VkImageAspectFlagBits::Metadata;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT = VkImageAspectFlagBits::MemoryPlane0BitEXT;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT = VkImageAspectFlagBits::MemoryPlane1BitEXT;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT = VkImageAspectFlagBits::MemoryPlane2BitEXT;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT = VkImageAspectFlagBits::MemoryPlane3BitEXT;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_PLANE_0_BIT = VkImageAspectFlagBits::Plane0;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_PLANE_1_BIT = VkImageAspectFlagBits::Plane1;
const VkImageAspectFlagBits VK_IMAGE_ASPECT_PLANE_2_BIT = VkImageAspectFlagBits::Plane2;
enum class VkSparseImageFormatFlagBits: uint32_t {
    SingleMiptail = 1,
    AlignedMipSize = 2,
    NonstandardBlockSize = 4,
};
const VkSparseImageFormatFlagBits VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT = VkSparseImageFormatFlagBits::SingleMiptail;
const VkSparseImageFormatFlagBits VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT = VkSparseImageFormatFlagBits::AlignedMipSize;
const VkSparseImageFormatFlagBits VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT = VkSparseImageFormatFlagBits::NonstandardBlockSize;
enum class VkSparseMemoryBindFlagBits: uint32_t {
    Metadata = 1,
};
const VkSparseMemoryBindFlagBits VK_SPARSE_MEMORY_BIND_METADATA_BIT = VkSparseMemoryBindFlagBits::Metadata;
enum class VkPipelineStageFlagBits: uint32_t {
    NoneKHR = 1,
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
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_NONE_KHR = VkPipelineStageFlagBits::NoneKHR;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT = VkPipelineStageFlagBits::DrawIndirect;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_VERTEX_INPUT_BIT = VkPipelineStageFlagBits::VertexInput;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_VERTEX_SHADER_BIT = VkPipelineStageFlagBits::VertexShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = VkPipelineStageFlagBits::TessellationControlShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = VkPipelineStageFlagBits::TessellationEvaluationShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT = VkPipelineStageFlagBits::GeometryShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT = VkPipelineStageFlagBits::FragmentShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = VkPipelineStageFlagBits::EarlyFragmentTests;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = VkPipelineStageFlagBits::LateFragmentTests;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = VkPipelineStageFlagBits::ColorAttachmentOutput;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT = VkPipelineStageFlagBits::ComputeShader;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_TRANSFER_BIT = VkPipelineStageFlagBits::Transfer;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = VkPipelineStageFlagBits::BottomOfPipe;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_HOST_BIT = VkPipelineStageFlagBits::Host;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT = VkPipelineStageFlagBits::AllGraphics;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_ALL_COMMANDS_BIT = VkPipelineStageFlagBits::AllCommands;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT = VkPipelineStageFlagBits::TransformFeedbackBitEXT;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT = VkPipelineStageFlagBits::ConditionalRenderingBitEXT;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR = VkPipelineStageFlagBits::AccelerationStructureBuildBitKHR;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR = VkPipelineStageFlagBits::RayTracingShaderBitKHR;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV = VkPipelineStageFlagBits::ShadingRateImageBitNV;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV = VkPipelineStageFlagBits::TaskShaderBitNV;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV = VkPipelineStageFlagBits::MeshShaderBitNV;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT = VkPipelineStageFlagBits::FragmentDensityProcessBitEXT;
const VkPipelineStageFlagBits VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV = VkPipelineStageFlagBits::CommandPreprocessBitNV;
enum class VkCommandPoolCreateFlagBits: uint32_t {
    Transient = 1,
    ResetCommandBuffer = 2,
    Protected = 4,
};
const VkCommandPoolCreateFlagBits VK_COMMAND_POOL_CREATE_TRANSIENT_BIT = VkCommandPoolCreateFlagBits::Transient;
const VkCommandPoolCreateFlagBits VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT = VkCommandPoolCreateFlagBits::ResetCommandBuffer;
const VkCommandPoolCreateFlagBits VK_COMMAND_POOL_CREATE_PROTECTED_BIT = VkCommandPoolCreateFlagBits::Protected;
enum class VkCommandPoolResetFlagBits: uint32_t {
    ReleaseResources = 1,
};
const VkCommandPoolResetFlagBits VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT = VkCommandPoolResetFlagBits::ReleaseResources;
enum class VkCommandBufferResetFlagBits: uint32_t {
    ReleaseResources = 1,
};
const VkCommandBufferResetFlagBits VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT = VkCommandBufferResetFlagBits::ReleaseResources;
enum class VkSampleCountFlagBits: uint32_t {
    e1 = 1,
    e2 = 2,
    e4 = 4,
    e8 = 8,
    e16 = 16,
    e32 = 32,
    e64 = 64,
};
const VkSampleCountFlagBits VK_SAMPLE_COUNT_1_BIT = VkSampleCountFlagBits::e1;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_2_BIT = VkSampleCountFlagBits::e2;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_4_BIT = VkSampleCountFlagBits::e4;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_8_BIT = VkSampleCountFlagBits::e8;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_16_BIT = VkSampleCountFlagBits::e16;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_32_BIT = VkSampleCountFlagBits::e32;
const VkSampleCountFlagBits VK_SAMPLE_COUNT_64_BIT = VkSampleCountFlagBits::e64;
enum class VkAttachmentDescriptionFlagBits: uint32_t {
    MayAlias = 1,
};
const VkAttachmentDescriptionFlagBits VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT = VkAttachmentDescriptionFlagBits::MayAlias;
enum class VkStencilFaceFlagBits: uint32_t {
    Front = 1,
    Back = 2,
    FrontAndBack = 0x00000003,
};
const VkStencilFaceFlagBits VK_STENCIL_FACE_FRONT_BIT = VkStencilFaceFlagBits::Front;
const VkStencilFaceFlagBits VK_STENCIL_FACE_BACK_BIT = VkStencilFaceFlagBits::Back;
const VkStencilFaceFlagBits VK_STENCIL_FACE_FRONT_AND_BACK = VkStencilFaceFlagBits::FrontAndBack;
enum class VkDescriptorPoolCreateFlagBits: uint32_t {
    FreeDescriptorSet = 1,
    HostOnlyBitVALVE = 4,
    UpdateAfterBind = 2,
};
const VkDescriptorPoolCreateFlagBits VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT = VkDescriptorPoolCreateFlagBits::FreeDescriptorSet;
const VkDescriptorPoolCreateFlagBits VK_DESCRIPTOR_POOL_CREATE_HOST_ONLY_BIT_VALVE = VkDescriptorPoolCreateFlagBits::HostOnlyBitVALVE;
const VkDescriptorPoolCreateFlagBits VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT = VkDescriptorPoolCreateFlagBits::UpdateAfterBind;
enum class VkDependencyFlagBits: uint32_t {
    ByRegion = 1,
    DeviceGroup = 4,
    ViewLocal = 2,
};
const VkDependencyFlagBits VK_DEPENDENCY_BY_REGION_BIT = VkDependencyFlagBits::ByRegion;
const VkDependencyFlagBits VK_DEPENDENCY_DEVICE_GROUP_BIT = VkDependencyFlagBits::DeviceGroup;
const VkDependencyFlagBits VK_DEPENDENCY_VIEW_LOCAL_BIT = VkDependencyFlagBits::ViewLocal;
enum class VkSemaphoreWaitFlagBits: uint32_t {
    Any = 1,
};
const VkSemaphoreWaitFlagBits VK_SEMAPHORE_WAIT_ANY_BIT = VkSemaphoreWaitFlagBits::Any;
enum class VkDisplayPlaneAlphaFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    GlobalBitKHR = 2,
    PerPixelBitKHR = 4,
    PerPixelPremultipliedBitKHR = 8,
};
const VkDisplayPlaneAlphaFlagBitsKHR VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR = VkDisplayPlaneAlphaFlagBitsKHR::OpaqueBitKHR;
const VkDisplayPlaneAlphaFlagBitsKHR VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR = VkDisplayPlaneAlphaFlagBitsKHR::GlobalBitKHR;
const VkDisplayPlaneAlphaFlagBitsKHR VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR = VkDisplayPlaneAlphaFlagBitsKHR::PerPixelBitKHR;
const VkDisplayPlaneAlphaFlagBitsKHR VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR = VkDisplayPlaneAlphaFlagBitsKHR::PerPixelPremultipliedBitKHR;
enum class VkCompositeAlphaFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    PreMultipliedBitKHR = 2,
    PostMultipliedBitKHR = 4,
    InheritBitKHR = 8,
};
const VkCompositeAlphaFlagBitsKHR VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR = VkCompositeAlphaFlagBitsKHR::OpaqueBitKHR;
const VkCompositeAlphaFlagBitsKHR VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR = VkCompositeAlphaFlagBitsKHR::PreMultipliedBitKHR;
const VkCompositeAlphaFlagBitsKHR VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR = VkCompositeAlphaFlagBitsKHR::PostMultipliedBitKHR;
const VkCompositeAlphaFlagBitsKHR VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR = VkCompositeAlphaFlagBitsKHR::InheritBitKHR;
enum class VkSurfaceTransformFlagBitsKHR: uint32_t {
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
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR = VkSurfaceTransformFlagBitsKHR::IdentityBitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR = VkSurfaceTransformFlagBitsKHR::Rotate90BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR = VkSurfaceTransformFlagBitsKHR::Rotate180BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR = VkSurfaceTransformFlagBitsKHR::Rotate270BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR = VkSurfaceTransformFlagBitsKHR::HorizontalMirrorBitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR = VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate90BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR = VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate180BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR = VkSurfaceTransformFlagBitsKHR::HorizontalMirrorRotate270BitKHR;
const VkSurfaceTransformFlagBitsKHR VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR = VkSurfaceTransformFlagBitsKHR::InheritBitKHR;
enum class VkDebugReportFlagBitsEXT: uint32_t {
    InformationBitEXT = 1,
    WarningBitEXT = 2,
    PerformanceWarningBitEXT = 4,
    ErrorBitEXT = 8,
    DebugBitEXT = 16,
};
const VkDebugReportFlagBitsEXT VK_DEBUG_REPORT_INFORMATION_BIT_EXT = VkDebugReportFlagBitsEXT::InformationBitEXT;
const VkDebugReportFlagBitsEXT VK_DEBUG_REPORT_WARNING_BIT_EXT = VkDebugReportFlagBitsEXT::WarningBitEXT;
const VkDebugReportFlagBitsEXT VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT = VkDebugReportFlagBitsEXT::PerformanceWarningBitEXT;
const VkDebugReportFlagBitsEXT VK_DEBUG_REPORT_ERROR_BIT_EXT = VkDebugReportFlagBitsEXT::ErrorBitEXT;
const VkDebugReportFlagBitsEXT VK_DEBUG_REPORT_DEBUG_BIT_EXT = VkDebugReportFlagBitsEXT::DebugBitEXT;
enum class VkExternalMemoryHandleTypeFlagBitsNV: uint32_t {
    OpaqueWin32BitNV = 1,
    OpaqueWin32KmtBitNV = 2,
    D3D11ImageBitNV = 4,
    D3D11ImageKmtBitNV = 8,
};
const VkExternalMemoryHandleTypeFlagBitsNV VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV = VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32BitNV;
const VkExternalMemoryHandleTypeFlagBitsNV VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV = VkExternalMemoryHandleTypeFlagBitsNV::OpaqueWin32KmtBitNV;
const VkExternalMemoryHandleTypeFlagBitsNV VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV = VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageBitNV;
const VkExternalMemoryHandleTypeFlagBitsNV VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV = VkExternalMemoryHandleTypeFlagBitsNV::D3D11ImageKmtBitNV;
enum class VkExternalMemoryFeatureFlagBitsNV: uint32_t {
    DedicatedOnlyBitNV = 1,
    ExportableBitNV = 2,
    ImportableBitNV = 4,
};
const VkExternalMemoryFeatureFlagBitsNV VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV = VkExternalMemoryFeatureFlagBitsNV::DedicatedOnlyBitNV;
const VkExternalMemoryFeatureFlagBitsNV VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV = VkExternalMemoryFeatureFlagBitsNV::ExportableBitNV;
const VkExternalMemoryFeatureFlagBitsNV VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV = VkExternalMemoryFeatureFlagBitsNV::ImportableBitNV;
enum class VkSubgroupFeatureFlagBits: uint32_t {
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
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_BASIC_BIT = VkSubgroupFeatureFlagBits::Basic;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_VOTE_BIT = VkSubgroupFeatureFlagBits::Vote;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_ARITHMETIC_BIT = VkSubgroupFeatureFlagBits::Arithmetic;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_BALLOT_BIT = VkSubgroupFeatureFlagBits::Ballot;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_SHUFFLE_BIT = VkSubgroupFeatureFlagBits::Shuffle;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT = VkSubgroupFeatureFlagBits::ShuffleRelative;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_CLUSTERED_BIT = VkSubgroupFeatureFlagBits::Clustered;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_QUAD_BIT = VkSubgroupFeatureFlagBits::Quad;
const VkSubgroupFeatureFlagBits VK_SUBGROUP_FEATURE_PARTITIONED_BIT_NV = VkSubgroupFeatureFlagBits::PartitionedBitNV;
enum class VkIndirectCommandsLayoutUsageFlagBitsNV: uint32_t {
    ExplicitPreprocessBitNV = 1,
    IndexedSequencesBitNV = 2,
    UnorderedSequencesBitNV = 4,
};
const VkIndirectCommandsLayoutUsageFlagBitsNV VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EXPLICIT_PREPROCESS_BIT_NV = VkIndirectCommandsLayoutUsageFlagBitsNV::ExplicitPreprocessBitNV;
const VkIndirectCommandsLayoutUsageFlagBitsNV VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NV = VkIndirectCommandsLayoutUsageFlagBitsNV::IndexedSequencesBitNV;
const VkIndirectCommandsLayoutUsageFlagBitsNV VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NV = VkIndirectCommandsLayoutUsageFlagBitsNV::UnorderedSequencesBitNV;
enum class VkIndirectStateFlagBitsNV: uint32_t {
    FlagFrontfaceBitNV = 1,
};
const VkIndirectStateFlagBitsNV VK_INDIRECT_STATE_FLAG_FRONTFACE_BIT_NV = VkIndirectStateFlagBitsNV::FlagFrontfaceBitNV;
enum class VkPrivateDataSlotCreateFlagBitsEXT: uint32_t {
};
enum class VkDescriptorSetLayoutCreateFlagBits: uint32_t {
    PushDescriptorBitKHR = 1,
    HostOnlyPoolBitVALVE = 4,
    UpdateAfterBindPool = 2,
};
const VkDescriptorSetLayoutCreateFlagBits VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR = VkDescriptorSetLayoutCreateFlagBits::PushDescriptorBitKHR;
const VkDescriptorSetLayoutCreateFlagBits VK_DESCRIPTOR_SET_LAYOUT_CREATE_HOST_ONLY_POOL_BIT_VALVE = VkDescriptorSetLayoutCreateFlagBits::HostOnlyPoolBitVALVE;
const VkDescriptorSetLayoutCreateFlagBits VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT = VkDescriptorSetLayoutCreateFlagBits::UpdateAfterBindPool;
enum class VkExternalMemoryHandleTypeFlagBits: uint32_t {
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
    ZirconVmoBitFUCHSIA = 2048,
};
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT = VkExternalMemoryHandleTypeFlagBits::OpaqueFd;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT = VkExternalMemoryHandleTypeFlagBits::OpaqueWin32;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT = VkExternalMemoryHandleTypeFlagBits::OpaqueWin32Kmt;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT = VkExternalMemoryHandleTypeFlagBits::D3D11Texture;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT = VkExternalMemoryHandleTypeFlagBits::D3D11TextureKmt;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT = VkExternalMemoryHandleTypeFlagBits::D3D12Heap;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT = VkExternalMemoryHandleTypeFlagBits::D3D12Resource;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_DMA_BUF_BIT_EXT = VkExternalMemoryHandleTypeFlagBits::DmaBufBitEXT;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID = VkExternalMemoryHandleTypeFlagBits::AndroidHardwareBufferBitANDROID;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_ALLOCATION_BIT_EXT = VkExternalMemoryHandleTypeFlagBits::HostAllocationBitEXT;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_HOST_MAPPED_FOREIGN_MEMORY_BIT_EXT = VkExternalMemoryHandleTypeFlagBits::HostMappedForeignMemoryBitEXT;
const VkExternalMemoryHandleTypeFlagBits VK_EXTERNAL_MEMORY_HANDLE_TYPE_ZIRCON_VMO_BIT_FUCHSIA = VkExternalMemoryHandleTypeFlagBits::ZirconVmoBitFUCHSIA;
enum class VkExternalMemoryFeatureFlagBits: uint32_t {
    DedicatedOnly = 1,
    Exportable = 2,
    Importable = 4,
};
const VkExternalMemoryFeatureFlagBits VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT = VkExternalMemoryFeatureFlagBits::DedicatedOnly;
const VkExternalMemoryFeatureFlagBits VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT = VkExternalMemoryFeatureFlagBits::Exportable;
const VkExternalMemoryFeatureFlagBits VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT = VkExternalMemoryFeatureFlagBits::Importable;
enum class VkExternalSemaphoreHandleTypeFlagBits: uint32_t {
    OpaqueFd = 1,
    OpaqueWin32 = 2,
    OpaqueWin32Kmt = 4,
    D3D12Fence = 8,
    D3D11Fence = D3D12Fence,
    SyncFd = 16,
    ZirconEventBitFUCHSIA = 128,
};
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT = VkExternalSemaphoreHandleTypeFlagBits::OpaqueFd;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT = VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT = VkExternalSemaphoreHandleTypeFlagBits::OpaqueWin32Kmt;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT = VkExternalSemaphoreHandleTypeFlagBits::D3D12Fence;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D11_FENCE_BIT = VkExternalSemaphoreHandleTypeFlagBits::D3D11Fence;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT = VkExternalSemaphoreHandleTypeFlagBits::SyncFd;
const VkExternalSemaphoreHandleTypeFlagBits VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_ZIRCON_EVENT_BIT_FUCHSIA = VkExternalSemaphoreHandleTypeFlagBits::ZirconEventBitFUCHSIA;
enum class VkExternalSemaphoreFeatureFlagBits: uint32_t {
    Exportable = 1,
    Importable = 2,
};
const VkExternalSemaphoreFeatureFlagBits VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT = VkExternalSemaphoreFeatureFlagBits::Exportable;
const VkExternalSemaphoreFeatureFlagBits VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT = VkExternalSemaphoreFeatureFlagBits::Importable;
enum class VkSemaphoreImportFlagBits: uint32_t {
    Temporary = 1,
};
const VkSemaphoreImportFlagBits VK_SEMAPHORE_IMPORT_TEMPORARY_BIT = VkSemaphoreImportFlagBits::Temporary;
enum class VkExternalFenceHandleTypeFlagBits: uint32_t {
    OpaqueFd = 1,
    OpaqueWin32 = 2,
    OpaqueWin32Kmt = 4,
    SyncFd = 8,
};
const VkExternalFenceHandleTypeFlagBits VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT = VkExternalFenceHandleTypeFlagBits::OpaqueFd;
const VkExternalFenceHandleTypeFlagBits VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT = VkExternalFenceHandleTypeFlagBits::OpaqueWin32;
const VkExternalFenceHandleTypeFlagBits VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT = VkExternalFenceHandleTypeFlagBits::OpaqueWin32Kmt;
const VkExternalFenceHandleTypeFlagBits VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT = VkExternalFenceHandleTypeFlagBits::SyncFd;
enum class VkExternalFenceFeatureFlagBits: uint32_t {
    Exportable = 1,
    Importable = 2,
};
const VkExternalFenceFeatureFlagBits VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT = VkExternalFenceFeatureFlagBits::Exportable;
const VkExternalFenceFeatureFlagBits VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT = VkExternalFenceFeatureFlagBits::Importable;
enum class VkFenceImportFlagBits: uint32_t {
    Temporary = 1,
};
const VkFenceImportFlagBits VK_FENCE_IMPORT_TEMPORARY_BIT = VkFenceImportFlagBits::Temporary;
enum class VkSurfaceCounterFlagBitsEXT: uint32_t {
    VblankBitEXT = 1,
    VblankEXT = VblankBitEXT,
};
const VkSurfaceCounterFlagBitsEXT VK_SURFACE_COUNTER_VBLANK_BIT_EXT = VkSurfaceCounterFlagBitsEXT::VblankBitEXT;
const VkSurfaceCounterFlagBitsEXT VK_SURFACE_COUNTER_VBLANK_EXT = VkSurfaceCounterFlagBitsEXT::VblankEXT;
enum class VkPeerMemoryFeatureFlagBits: uint32_t {
    CopySrc = 1,
    CopyDst = 2,
    GenericSrc = 4,
    GenericDst = 8,
};
const VkPeerMemoryFeatureFlagBits VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT = VkPeerMemoryFeatureFlagBits::CopySrc;
const VkPeerMemoryFeatureFlagBits VK_PEER_MEMORY_FEATURE_COPY_DST_BIT = VkPeerMemoryFeatureFlagBits::CopyDst;
const VkPeerMemoryFeatureFlagBits VK_PEER_MEMORY_FEATURE_GENERIC_SRC_BIT = VkPeerMemoryFeatureFlagBits::GenericSrc;
const VkPeerMemoryFeatureFlagBits VK_PEER_MEMORY_FEATURE_GENERIC_DST_BIT = VkPeerMemoryFeatureFlagBits::GenericDst;
enum class VkMemoryAllocateFlagBits: uint32_t {
    DeviceMask = 1,
    DeviceAddress = 2,
    DeviceAddressCaptureReplay = 4,
};
const VkMemoryAllocateFlagBits VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT = VkMemoryAllocateFlagBits::DeviceMask;
const VkMemoryAllocateFlagBits VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT = VkMemoryAllocateFlagBits::DeviceAddress;
const VkMemoryAllocateFlagBits VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT = VkMemoryAllocateFlagBits::DeviceAddressCaptureReplay;
enum class VkDeviceGroupPresentModeFlagBitsKHR: uint32_t {
    LocalBitKHR = 1,
    RemoteBitKHR = 2,
    SumBitKHR = 4,
    LocalMultiDeviceBitKHR = 8,
};
const VkDeviceGroupPresentModeFlagBitsKHR VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR = VkDeviceGroupPresentModeFlagBitsKHR::LocalBitKHR;
const VkDeviceGroupPresentModeFlagBitsKHR VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR = VkDeviceGroupPresentModeFlagBitsKHR::RemoteBitKHR;
const VkDeviceGroupPresentModeFlagBitsKHR VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR = VkDeviceGroupPresentModeFlagBitsKHR::SumBitKHR;
const VkDeviceGroupPresentModeFlagBitsKHR VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR = VkDeviceGroupPresentModeFlagBitsKHR::LocalMultiDeviceBitKHR;
enum class VkSwapchainCreateFlagBitsKHR: uint32_t {
    SplitInstanceBindRegionsBitKHR = 1,
    ProtectedBitKHR = 2,
    MutableFormatBitKHR = 4,
};
const VkSwapchainCreateFlagBitsKHR VK_SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR = VkSwapchainCreateFlagBitsKHR::SplitInstanceBindRegionsBitKHR;
const VkSwapchainCreateFlagBitsKHR VK_SWAPCHAIN_CREATE_PROTECTED_BIT_KHR = VkSwapchainCreateFlagBitsKHR::ProtectedBitKHR;
const VkSwapchainCreateFlagBitsKHR VK_SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR = VkSwapchainCreateFlagBitsKHR::MutableFormatBitKHR;
enum class VkSubpassDescriptionFlagBits: uint32_t {
    PerViewAttributesBitNVX = 1,
    PerViewPositionXOnlyBitNVX = 2,
    FragmentRegionBitQCOM = 4,
    ShaderResolveBitQCOM = 8,
};
const VkSubpassDescriptionFlagBits VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX = VkSubpassDescriptionFlagBits::PerViewAttributesBitNVX;
const VkSubpassDescriptionFlagBits VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX = VkSubpassDescriptionFlagBits::PerViewPositionXOnlyBitNVX;
const VkSubpassDescriptionFlagBits VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM = VkSubpassDescriptionFlagBits::FragmentRegionBitQCOM;
const VkSubpassDescriptionFlagBits VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM = VkSubpassDescriptionFlagBits::ShaderResolveBitQCOM;
enum class VkDebugUtilsMessageSeverityFlagBitsEXT: uint32_t {
    VerboseBitEXT = 1,
    InfoBitEXT = 16,
    WarningBitEXT = 256,
    ErrorBitEXT = 4096,
};
const VkDebugUtilsMessageSeverityFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT = VkDebugUtilsMessageSeverityFlagBitsEXT::VerboseBitEXT;
const VkDebugUtilsMessageSeverityFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT = VkDebugUtilsMessageSeverityFlagBitsEXT::InfoBitEXT;
const VkDebugUtilsMessageSeverityFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT = VkDebugUtilsMessageSeverityFlagBitsEXT::WarningBitEXT;
const VkDebugUtilsMessageSeverityFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT = VkDebugUtilsMessageSeverityFlagBitsEXT::ErrorBitEXT;
enum class VkDebugUtilsMessageTypeFlagBitsEXT: uint32_t {
    GeneralBitEXT = 1,
    ValidationBitEXT = 2,
    PerformanceBitEXT = 4,
};
const VkDebugUtilsMessageTypeFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT = VkDebugUtilsMessageTypeFlagBitsEXT::GeneralBitEXT;
const VkDebugUtilsMessageTypeFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT = VkDebugUtilsMessageTypeFlagBitsEXT::ValidationBitEXT;
const VkDebugUtilsMessageTypeFlagBitsEXT VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT = VkDebugUtilsMessageTypeFlagBitsEXT::PerformanceBitEXT;
enum class VkDescriptorBindingFlagBits: uint32_t {
    UpdateAfterBind = 1,
    UpdateUnusedWhilePending = 2,
    PartiallyBound = 4,
    VariableDescriptorCount = 8,
};
const VkDescriptorBindingFlagBits VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT = VkDescriptorBindingFlagBits::UpdateAfterBind;
const VkDescriptorBindingFlagBits VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT = VkDescriptorBindingFlagBits::UpdateUnusedWhilePending;
const VkDescriptorBindingFlagBits VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT = VkDescriptorBindingFlagBits::PartiallyBound;
const VkDescriptorBindingFlagBits VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT = VkDescriptorBindingFlagBits::VariableDescriptorCount;
enum class VkConditionalRenderingFlagBitsEXT: uint32_t {
    InvertedBitEXT = 1,
};
const VkConditionalRenderingFlagBitsEXT VK_CONDITIONAL_RENDERING_INVERTED_BIT_EXT = VkConditionalRenderingFlagBitsEXT::InvertedBitEXT;
enum class VkResolveModeFlagBits: uint32_t {
    None = 0,
    SampleZero = 1,
    Average = 2,
    Min = 4,
    Max = 8,
};
const VkResolveModeFlagBits VK_RESOLVE_MODE_NONE = VkResolveModeFlagBits::None;
const VkResolveModeFlagBits VK_RESOLVE_MODE_SAMPLE_ZERO_BIT = VkResolveModeFlagBits::SampleZero;
const VkResolveModeFlagBits VK_RESOLVE_MODE_AVERAGE_BIT = VkResolveModeFlagBits::Average;
const VkResolveModeFlagBits VK_RESOLVE_MODE_MIN_BIT = VkResolveModeFlagBits::Min;
const VkResolveModeFlagBits VK_RESOLVE_MODE_MAX_BIT = VkResolveModeFlagBits::Max;
enum class VkGeometryInstanceFlagBitsKHR: uint32_t {
    TriangleFacingCullDisableBitKHR = 1,
    TriangleFrontCounterclockwiseBitKHR = 2,
    ForceOpaqueBitKHR = 4,
    ForceNoOpaqueBitKHR = 8,
};
const VkGeometryInstanceFlagBitsKHR VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR = VkGeometryInstanceFlagBitsKHR::TriangleFacingCullDisableBitKHR;
const VkGeometryInstanceFlagBitsKHR VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_KHR = VkGeometryInstanceFlagBitsKHR::TriangleFrontCounterclockwiseBitKHR;
const VkGeometryInstanceFlagBitsKHR VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR = VkGeometryInstanceFlagBitsKHR::ForceOpaqueBitKHR;
const VkGeometryInstanceFlagBitsKHR VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR = VkGeometryInstanceFlagBitsKHR::ForceNoOpaqueBitKHR;
enum class VkGeometryFlagBitsKHR: uint32_t {
    OpaqueBitKHR = 1,
    NoDuplicateAnyHitInvocationBitKHR = 2,
};
const VkGeometryFlagBitsKHR VK_GEOMETRY_OPAQUE_BIT_KHR = VkGeometryFlagBitsKHR::OpaqueBitKHR;
const VkGeometryFlagBitsKHR VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR = VkGeometryFlagBitsKHR::NoDuplicateAnyHitInvocationBitKHR;
enum class VkBuildAccelerationStructureFlagBitsKHR: uint32_t {
    AllowUpdateBitKHR = 1,
    AllowCompactionBitKHR = 2,
    PreferFastTraceBitKHR = 4,
    PreferFastBuildBitKHR = 8,
    LowMemoryBitKHR = 16,
};
const VkBuildAccelerationStructureFlagBitsKHR VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR = VkBuildAccelerationStructureFlagBitsKHR::AllowUpdateBitKHR;
const VkBuildAccelerationStructureFlagBitsKHR VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR = VkBuildAccelerationStructureFlagBitsKHR::AllowCompactionBitKHR;
const VkBuildAccelerationStructureFlagBitsKHR VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR = VkBuildAccelerationStructureFlagBitsKHR::PreferFastTraceBitKHR;
const VkBuildAccelerationStructureFlagBitsKHR VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR = VkBuildAccelerationStructureFlagBitsKHR::PreferFastBuildBitKHR;
const VkBuildAccelerationStructureFlagBitsKHR VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR = VkBuildAccelerationStructureFlagBitsKHR::LowMemoryBitKHR;
enum class VkAccelerationStructureCreateFlagBitsKHR: uint32_t {
    DeviceAddressCaptureReplayBitKHR = 1,
};
const VkAccelerationStructureCreateFlagBitsKHR VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR = VkAccelerationStructureCreateFlagBitsKHR::DeviceAddressCaptureReplayBitKHR;
enum class VkFramebufferCreateFlagBits: uint32_t {
    Imageless = 1,
};
const VkFramebufferCreateFlagBits VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT = VkFramebufferCreateFlagBits::Imageless;
enum class VkDeviceDiagnosticsConfigFlagBitsNV: uint32_t {
    EnableShaderDebugInfoBitNV = 1,
    EnableResourceTrackingBitNV = 2,
    EnableAutomaticCheckpointsBitNV = 4,
};
const VkDeviceDiagnosticsConfigFlagBitsNV VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_SHADER_DEBUG_INFO_BIT_NV = VkDeviceDiagnosticsConfigFlagBitsNV::EnableShaderDebugInfoBitNV;
const VkDeviceDiagnosticsConfigFlagBitsNV VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_RESOURCE_TRACKING_BIT_NV = VkDeviceDiagnosticsConfigFlagBitsNV::EnableResourceTrackingBitNV;
const VkDeviceDiagnosticsConfigFlagBitsNV VK_DEVICE_DIAGNOSTICS_CONFIG_ENABLE_AUTOMATIC_CHECKPOINTS_BIT_NV = VkDeviceDiagnosticsConfigFlagBitsNV::EnableAutomaticCheckpointsBitNV;
enum class VkPipelineCreationFeedbackFlagBitsEXT: uint32_t {
    ValidBitEXT = 1,
    ApplicationPipelineCacheHitBitEXT = 2,
    BasePipelineAccelerationBitEXT = 4,
};
const VkPipelineCreationFeedbackFlagBitsEXT VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT_EXT = VkPipelineCreationFeedbackFlagBitsEXT::ValidBitEXT;
const VkPipelineCreationFeedbackFlagBitsEXT VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT_EXT = VkPipelineCreationFeedbackFlagBitsEXT::ApplicationPipelineCacheHitBitEXT;
const VkPipelineCreationFeedbackFlagBitsEXT VK_PIPELINE_CREATION_FEEDBACK_BASE_PIPELINE_ACCELERATION_BIT_EXT = VkPipelineCreationFeedbackFlagBitsEXT::BasePipelineAccelerationBitEXT;
enum class VkPerformanceCounterDescriptionFlagBitsKHR: uint32_t {
    PerformanceImpactingBitKHR = 1,
    PerformanceImpactingKHR = PerformanceImpactingBitKHR,
    ConcurrentlyImpactedBitKHR = 2,
    ConcurrentlyImpactedKHR = ConcurrentlyImpactedBitKHR,
};
const VkPerformanceCounterDescriptionFlagBitsKHR VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_BIT_KHR = VkPerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingBitKHR;
const VkPerformanceCounterDescriptionFlagBitsKHR VK_PERFORMANCE_COUNTER_DESCRIPTION_PERFORMANCE_IMPACTING_KHR = VkPerformanceCounterDescriptionFlagBitsKHR::PerformanceImpactingKHR;
const VkPerformanceCounterDescriptionFlagBitsKHR VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_BIT_KHR = VkPerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedBitKHR;
const VkPerformanceCounterDescriptionFlagBitsKHR VK_PERFORMANCE_COUNTER_DESCRIPTION_CONCURRENTLY_IMPACTED_KHR = VkPerformanceCounterDescriptionFlagBitsKHR::ConcurrentlyImpactedKHR;
enum class VkAcquireProfilingLockFlagBitsKHR: uint32_t {
};
enum class VkShaderCorePropertiesFlagBitsAMD: uint32_t {
};
enum class VkShaderModuleCreateFlagBits: uint32_t {
};
enum class VkPipelineCompilerControlFlagBitsAMD: uint32_t {
};
enum class VkToolPurposeFlagBitsEXT: uint32_t {
    ValidationBitEXT = 1,
    ProfilingBitEXT = 2,
    TracingBitEXT = 4,
    AdditionalFeaturesBitEXT = 8,
    ModifyingFeaturesBitEXT = 16,
    DebugReportingBitEXT = 32,
    DebugMarkersBitEXT = 64,
};
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_VALIDATION_BIT_EXT = VkToolPurposeFlagBitsEXT::ValidationBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_PROFILING_BIT_EXT = VkToolPurposeFlagBitsEXT::ProfilingBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_TRACING_BIT_EXT = VkToolPurposeFlagBitsEXT::TracingBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_ADDITIONAL_FEATURES_BIT_EXT = VkToolPurposeFlagBitsEXT::AdditionalFeaturesBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_MODIFYING_FEATURES_BIT_EXT = VkToolPurposeFlagBitsEXT::ModifyingFeaturesBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_DEBUG_REPORTING_BIT_EXT = VkToolPurposeFlagBitsEXT::DebugReportingBitEXT;
const VkToolPurposeFlagBitsEXT VK_TOOL_PURPOSE_DEBUG_MARKERS_BIT_EXT = VkToolPurposeFlagBitsEXT::DebugMarkersBitEXT;
enum class VkAccessFlagBits2KHR: uint64_t {
    e2NoneKHR = 0,
    e2IndirectCommandReadBitKHR = 1,
    e2IndexReadBitKHR = 2,
    e2VertexAttributeReadBitKHR = 4,
    e2UniformReadBitKHR = 8,
    e2InputAttachmentReadBitKHR = 16,
    e2ShaderReadBitKHR = 32,
    e2ShaderWriteBitKHR = 64,
    e2ColorAttachmentReadBitKHR = 128,
    e2ColorAttachmentWriteBitKHR = 256,
    e2DepthStencilAttachmentReadBitKHR = 512,
    e2DepthStencilAttachmentWriteBitKHR = 1024,
    e2TransferReadBitKHR = 2048,
    e2TransferWriteBitKHR = 4096,
    e2HostReadBitKHR = 8192,
    e2HostWriteBitKHR = 16384,
    e2MemoryReadBitKHR = 32768,
    e2MemoryWriteBitKHR = 65536,
    e2ShaderSampledReadBitKHR = 4294967296,
    e2ShaderStorageReadBitKHR = 8589934592,
    e2ShaderStorageWriteBitKHR = 17179869184,
    e2VideoDecodeReadBitKHR = 34359738368,
    e2VideoDecodeWriteBitKHR = 68719476736,
    e2VideoEncodeReadBitKHR = 137438953472,
    e2VideoEncodeWriteBitKHR = 274877906944,
    e2TransformFeedbackWriteBitEXT = 33554432,
    e2TransformFeedbackCounterReadBitEXT = 67108864,
    e2TransformFeedbackCounterWriteBitEXT = 134217728,
    e2ConditionalRenderingReadBitEXT = 1048576,
    e2CommandPreprocessReadBitNV = 131072,
    e2CommandPreprocessWriteBitNV = 262144,
    e2FragmentShadingRateAttachmentReadBitKHR = 8388608,
    e2AccelerationStructureReadBitKHR = 2097152,
    e2AccelerationStructureWriteBitKHR = 4194304,
    e2FragmentDensityMapReadBitEXT = 16777216,
    e2ColorAttachmentReadNoncoherentBitEXT = 524288,
};
const VkAccessFlagBits2KHR VK_ACCESS_2_NONE_KHR = VkAccessFlagBits2KHR::e2NoneKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_INDIRECT_COMMAND_READ_BIT_KHR = VkAccessFlagBits2KHR::e2IndirectCommandReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_INDEX_READ_BIT_KHR = VkAccessFlagBits2KHR::e2IndexReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_VERTEX_ATTRIBUTE_READ_BIT_KHR = VkAccessFlagBits2KHR::e2VertexAttributeReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_UNIFORM_READ_BIT_KHR = VkAccessFlagBits2KHR::e2UniformReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_INPUT_ATTACHMENT_READ_BIT_KHR = VkAccessFlagBits2KHR::e2InputAttachmentReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_SHADER_READ_BIT_KHR = VkAccessFlagBits2KHR::e2ShaderReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_SHADER_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2ShaderWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_COLOR_ATTACHMENT_READ_BIT_KHR = VkAccessFlagBits2KHR::e2ColorAttachmentReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2ColorAttachmentWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT_KHR = VkAccessFlagBits2KHR::e2DepthStencilAttachmentReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2DepthStencilAttachmentWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_TRANSFER_READ_BIT_KHR = VkAccessFlagBits2KHR::e2TransferReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_TRANSFER_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2TransferWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_HOST_READ_BIT_KHR = VkAccessFlagBits2KHR::e2HostReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_HOST_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2HostWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_MEMORY_READ_BIT_KHR = VkAccessFlagBits2KHR::e2MemoryReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_MEMORY_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2MemoryWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_SHADER_SAMPLED_READ_BIT_KHR = VkAccessFlagBits2KHR::e2ShaderSampledReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_SHADER_STORAGE_READ_BIT_KHR = VkAccessFlagBits2KHR::e2ShaderStorageReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_SHADER_STORAGE_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2ShaderStorageWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_VIDEO_DECODE_READ_BIT_KHR = VkAccessFlagBits2KHR::e2VideoDecodeReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_VIDEO_DECODE_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2VideoDecodeWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_VIDEO_ENCODE_READ_BIT_KHR = VkAccessFlagBits2KHR::e2VideoEncodeReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_VIDEO_ENCODE_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2VideoEncodeWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_TRANSFORM_FEEDBACK_WRITE_BIT_EXT = VkAccessFlagBits2KHR::e2TransformFeedbackWriteBitEXT;
const VkAccessFlagBits2KHR VK_ACCESS_2_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = VkAccessFlagBits2KHR::e2TransformFeedbackCounterReadBitEXT;
const VkAccessFlagBits2KHR VK_ACCESS_2_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = VkAccessFlagBits2KHR::e2TransformFeedbackCounterWriteBitEXT;
const VkAccessFlagBits2KHR VK_ACCESS_2_CONDITIONAL_RENDERING_READ_BIT_EXT = VkAccessFlagBits2KHR::e2ConditionalRenderingReadBitEXT;
const VkAccessFlagBits2KHR VK_ACCESS_2_COMMAND_PREPROCESS_READ_BIT_NV = VkAccessFlagBits2KHR::e2CommandPreprocessReadBitNV;
const VkAccessFlagBits2KHR VK_ACCESS_2_COMMAND_PREPROCESS_WRITE_BIT_NV = VkAccessFlagBits2KHR::e2CommandPreprocessWriteBitNV;
const VkAccessFlagBits2KHR VK_ACCESS_2_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR = VkAccessFlagBits2KHR::e2FragmentShadingRateAttachmentReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_ACCELERATION_STRUCTURE_READ_BIT_KHR = VkAccessFlagBits2KHR::e2AccelerationStructureReadBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_ACCELERATION_STRUCTURE_WRITE_BIT_KHR = VkAccessFlagBits2KHR::e2AccelerationStructureWriteBitKHR;
const VkAccessFlagBits2KHR VK_ACCESS_2_FRAGMENT_DENSITY_MAP_READ_BIT_EXT = VkAccessFlagBits2KHR::e2FragmentDensityMapReadBitEXT;
const VkAccessFlagBits2KHR VK_ACCESS_2_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = VkAccessFlagBits2KHR::e2ColorAttachmentReadNoncoherentBitEXT;
enum class VkPipelineStageFlagBits2KHR: uint64_t {
    e2NoneKHR = 0,
    e2TopOfPipeBitKHR = 1,
    e2DrawIndirectBitKHR = 2,
    e2VertexInputBitKHR = 4,
    e2VertexShaderBitKHR = 8,
    e2TessellationControlShaderBitKHR = 16,
    e2TessellationEvaluationShaderBitKHR = 32,
    e2GeometryShaderBitKHR = 64,
    e2FragmentShaderBitKHR = 128,
    e2EarlyFragmentTestsBitKHR = 256,
    e2LateFragmentTestsBitKHR = 512,
    e2ColorAttachmentOutputBitKHR = 1024,
    e2ComputeShaderBitKHR = 2048,
    e2AllTransferBitKHR = 4096,
    e2TransferBitKHR = e2AllTransferBitKHR,
    e2BottomOfPipeBitKHR = 8192,
    e2HostBitKHR = 16384,
    e2AllGraphicsBitKHR = 32768,
    e2AllCommandsBitKHR = 65536,
    e2CopyBitKHR = 4294967296,
    e2ResolveBitKHR = 8589934592,
    e2BlitBitKHR = 17179869184,
    e2ClearBitKHR = 34359738368,
    e2IndexInputBitKHR = 68719476736,
    e2VertexAttributeInputBitKHR = 137438953472,
    e2PreRasterizationShadersBitKHR = 274877906944,
    e2VideoDecodeBitKHR = 67108864,
    e2VideoEncodeBitKHR = 134217728,
    e2TransformFeedbackBitEXT = 16777216,
    e2ConditionalRenderingBitEXT = 262144,
    e2CommandPreprocessBitNV = 131072,
    e2FragmentShadingRateAttachmentBitKHR = 4194304,
    e2AccelerationStructureBuildBitKHR = 33554432,
    e2RayTracingShaderBitKHR = 2097152,
    e2FragmentDensityProcessBitEXT = 8388608,
    e2TaskShaderBitNV = 524288,
    e2MeshShaderBitNV = 1048576,
};
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_NONE_KHR = VkPipelineStageFlagBits2KHR::e2NoneKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TOP_OF_PIPE_BIT_KHR = VkPipelineStageFlagBits2KHR::e2TopOfPipeBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_DRAW_INDIRECT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2DrawIndirectBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_VERTEX_INPUT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2VertexInputBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_VERTEX_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2VertexShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TESSELLATION_CONTROL_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2TessellationControlShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TESSELLATION_EVALUATION_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2TessellationEvaluationShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_GEOMETRY_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2GeometryShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2FragmentShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT_KHR = VkPipelineStageFlagBits2KHR::e2EarlyFragmentTestsBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT_KHR = VkPipelineStageFlagBits2KHR::e2LateFragmentTestsBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2ColorAttachmentOutputBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_COMPUTE_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2ComputeShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_ALL_TRANSFER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2AllTransferBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TRANSFER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2TransferBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_BOTTOM_OF_PIPE_BIT_KHR = VkPipelineStageFlagBits2KHR::e2BottomOfPipeBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_HOST_BIT_KHR = VkPipelineStageFlagBits2KHR::e2HostBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT_KHR = VkPipelineStageFlagBits2KHR::e2AllGraphicsBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT_KHR = VkPipelineStageFlagBits2KHR::e2AllCommandsBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_COPY_BIT_KHR = VkPipelineStageFlagBits2KHR::e2CopyBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_RESOLVE_BIT_KHR = VkPipelineStageFlagBits2KHR::e2ResolveBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_BLIT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2BlitBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_CLEAR_BIT_KHR = VkPipelineStageFlagBits2KHR::e2ClearBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_INDEX_INPUT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2IndexInputBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_VERTEX_ATTRIBUTE_INPUT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2VertexAttributeInputBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_PRE_RASTERIZATION_SHADERS_BIT_KHR = VkPipelineStageFlagBits2KHR::e2PreRasterizationShadersBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_VIDEO_DECODE_BIT_KHR = VkPipelineStageFlagBits2KHR::e2VideoDecodeBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_VIDEO_ENCODE_BIT_KHR = VkPipelineStageFlagBits2KHR::e2VideoEncodeBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TRANSFORM_FEEDBACK_BIT_EXT = VkPipelineStageFlagBits2KHR::e2TransformFeedbackBitEXT;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_CONDITIONAL_RENDERING_BIT_EXT = VkPipelineStageFlagBits2KHR::e2ConditionalRenderingBitEXT;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_COMMAND_PREPROCESS_BIT_NV = VkPipelineStageFlagBits2KHR::e2CommandPreprocessBitNV;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = VkPipelineStageFlagBits2KHR::e2FragmentShadingRateAttachmentBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_ACCELERATION_STRUCTURE_BUILD_BIT_KHR = VkPipelineStageFlagBits2KHR::e2AccelerationStructureBuildBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_RAY_TRACING_SHADER_BIT_KHR = VkPipelineStageFlagBits2KHR::e2RayTracingShaderBitKHR;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_FRAGMENT_DENSITY_PROCESS_BIT_EXT = VkPipelineStageFlagBits2KHR::e2FragmentDensityProcessBitEXT;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_TASK_SHADER_BIT_NV = VkPipelineStageFlagBits2KHR::e2TaskShaderBitNV;
const VkPipelineStageFlagBits2KHR VK_PIPELINE_STAGE_2_MESH_SHADER_BIT_NV = VkPipelineStageFlagBits2KHR::e2MeshShaderBitNV;
enum class VkSubmitFlagBitsKHR: uint32_t {
    ProtectedBitKHR = 1,
};
const VkSubmitFlagBitsKHR VK_SUBMIT_PROTECTED_BIT_KHR = VkSubmitFlagBitsKHR::ProtectedBitKHR;
enum class VkEventCreateFlagBits: uint32_t {
    DeviceOnlyBitKHR = 1,
};
const VkEventCreateFlagBits VK_EVENT_CREATE_DEVICE_ONLY_BIT_KHR = VkEventCreateFlagBits::DeviceOnlyBitKHR;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum class VkVideoCodecOperationFlagBitsKHR: uint32_t {
    InvalidBitKHR = 0,
    EncodeH264BitEXT = 65536,
    DecodeH264BitEXT = 1,
    DecodeH265BitEXT = 2,
};
const VkVideoCodecOperationFlagBitsKHR VK_VIDEO_CODEC_OPERATION_INVALID_BIT_KHR = VkVideoCodecOperationFlagBitsKHR::InvalidBitKHR;
const VkVideoCodecOperationFlagBitsKHR VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_EXT = VkVideoCodecOperationFlagBitsKHR::EncodeH264BitEXT;
const VkVideoCodecOperationFlagBitsKHR VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_EXT = VkVideoCodecOperationFlagBitsKHR::DecodeH264BitEXT;
const VkVideoCodecOperationFlagBitsKHR VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_EXT = VkVideoCodecOperationFlagBitsKHR::DecodeH265BitEXT;
enum class VkVideoChromaSubsamplingFlagBitsKHR: uint32_t {
    InvalidBitKHR = 0,
    MonochromeBitKHR = 1,
    e420BitKHR = 2,
    e422BitKHR = 4,
    e444BitKHR = 8,
};
const VkVideoChromaSubsamplingFlagBitsKHR VK_VIDEO_CHROMA_SUBSAMPLING_INVALID_BIT_KHR = VkVideoChromaSubsamplingFlagBitsKHR::InvalidBitKHR;
const VkVideoChromaSubsamplingFlagBitsKHR VK_VIDEO_CHROMA_SUBSAMPLING_MONOCHROME_BIT_KHR = VkVideoChromaSubsamplingFlagBitsKHR::MonochromeBitKHR;
const VkVideoChromaSubsamplingFlagBitsKHR VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR = VkVideoChromaSubsamplingFlagBitsKHR::e420BitKHR;
const VkVideoChromaSubsamplingFlagBitsKHR VK_VIDEO_CHROMA_SUBSAMPLING_422_BIT_KHR = VkVideoChromaSubsamplingFlagBitsKHR::e422BitKHR;
const VkVideoChromaSubsamplingFlagBitsKHR VK_VIDEO_CHROMA_SUBSAMPLING_444_BIT_KHR = VkVideoChromaSubsamplingFlagBitsKHR::e444BitKHR;
enum class VkVideoComponentBitDepthFlagBitsKHR: uint32_t {
    InvalidKHR = 0,
    e8BitKHR = 1,
    e10BitKHR = 4,
    e12BitKHR = 16,
};
const VkVideoComponentBitDepthFlagBitsKHR VK_VIDEO_COMPONENT_BIT_DEPTH_INVALID_KHR = VkVideoComponentBitDepthFlagBitsKHR::InvalidKHR;
const VkVideoComponentBitDepthFlagBitsKHR VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR = VkVideoComponentBitDepthFlagBitsKHR::e8BitKHR;
const VkVideoComponentBitDepthFlagBitsKHR VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR = VkVideoComponentBitDepthFlagBitsKHR::e10BitKHR;
const VkVideoComponentBitDepthFlagBitsKHR VK_VIDEO_COMPONENT_BIT_DEPTH_12_BIT_KHR = VkVideoComponentBitDepthFlagBitsKHR::e12BitKHR;
enum class VkVideoCapabilitiesFlagBitsKHR: uint32_t {
    ProtectedContentBitKHR = 1,
    SeparateReferenceImagesBitKHR = 2,
};
const VkVideoCapabilitiesFlagBitsKHR VK_VIDEO_CAPABILITIES_PROTECTED_CONTENT_BIT_KHR = VkVideoCapabilitiesFlagBitsKHR::ProtectedContentBitKHR;
const VkVideoCapabilitiesFlagBitsKHR VK_VIDEO_CAPABILITIES_SEPARATE_REFERENCE_IMAGES_BIT_KHR = VkVideoCapabilitiesFlagBitsKHR::SeparateReferenceImagesBitKHR;
enum class VkVideoSessionCreateFlagBitsKHR: uint32_t {
    DefaultKHR = 0,
    ProtectedContentBitKHR = 1,
};
const VkVideoSessionCreateFlagBitsKHR VK_VIDEO_SESSION_CREATE_DEFAULT_KHR = VkVideoSessionCreateFlagBitsKHR::DefaultKHR;
const VkVideoSessionCreateFlagBitsKHR VK_VIDEO_SESSION_CREATE_PROTECTED_CONTENT_BIT_KHR = VkVideoSessionCreateFlagBitsKHR::ProtectedContentBitKHR;
enum class VkVideoCodingQualityPresetFlagBitsKHR: uint32_t {
    DefaultBitKHR = 0,
    NormalBitKHR = 1,
    PowerBitKHR = 2,
    QualityBitKHR = 4,
};
const VkVideoCodingQualityPresetFlagBitsKHR VK_VIDEO_CODING_QUALITY_PRESET_DEFAULT_BIT_KHR = VkVideoCodingQualityPresetFlagBitsKHR::DefaultBitKHR;
const VkVideoCodingQualityPresetFlagBitsKHR VK_VIDEO_CODING_QUALITY_PRESET_NORMAL_BIT_KHR = VkVideoCodingQualityPresetFlagBitsKHR::NormalBitKHR;
const VkVideoCodingQualityPresetFlagBitsKHR VK_VIDEO_CODING_QUALITY_PRESET_POWER_BIT_KHR = VkVideoCodingQualityPresetFlagBitsKHR::PowerBitKHR;
const VkVideoCodingQualityPresetFlagBitsKHR VK_VIDEO_CODING_QUALITY_PRESET_QUALITY_BIT_KHR = VkVideoCodingQualityPresetFlagBitsKHR::QualityBitKHR;
enum class VkVideoDecodeH264FieldLayoutFlagBitsEXT: uint32_t {
    OnlyEXT = 0,
    LineInterlacedPlaneBitEXT = 1,
    SeparateInterlacedPlaneBitEXT = 2,
};
const VkVideoDecodeH264FieldLayoutFlagBitsEXT VK_VIDEO_DECODE_H264_PROGRESSIVE_PICTURES_ONLY_EXT = VkVideoDecodeH264FieldLayoutFlagBitsEXT::OnlyEXT;
const VkVideoDecodeH264FieldLayoutFlagBitsEXT VK_VIDEO_DECODE_H264_FIELD_LAYOUT_LINE_INTERLACED_PLANE_BIT_EXT = VkVideoDecodeH264FieldLayoutFlagBitsEXT::LineInterlacedPlaneBitEXT;
const VkVideoDecodeH264FieldLayoutFlagBitsEXT VK_VIDEO_DECODE_H264_FIELD_LAYOUT_SEPARATE_INTERLACED_PLANE_BIT_EXT = VkVideoDecodeH264FieldLayoutFlagBitsEXT::SeparateInterlacedPlaneBitEXT;
enum class VkVideoCodingControlFlagBitsKHR: uint32_t {
    DefaultKHR = 0,
    ResetBitKHR = 1,
};
const VkVideoCodingControlFlagBitsKHR VK_VIDEO_CODING_CONTROL_DEFAULT_KHR = VkVideoCodingControlFlagBitsKHR::DefaultKHR;
const VkVideoCodingControlFlagBitsKHR VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR = VkVideoCodingControlFlagBitsKHR::ResetBitKHR;
enum class VkVideoDecodeFlagBitsKHR: uint32_t {
    DefaultKHR = 0,
    Reserved0BitKHR = 1,
};
const VkVideoDecodeFlagBitsKHR VK_VIDEO_DECODE_DEFAULT_KHR = VkVideoDecodeFlagBitsKHR::DefaultKHR;
const VkVideoDecodeFlagBitsKHR VK_VIDEO_DECODE_RESERVED_0_BIT_KHR = VkVideoDecodeFlagBitsKHR::Reserved0BitKHR;
enum class VkVideoEncodeFlagBitsKHR: uint32_t {
    DefaultKHR = 0,
    Reserved0BitKHR = 1,
};
const VkVideoEncodeFlagBitsKHR VK_VIDEO_ENCODE_DEFAULT_KHR = VkVideoEncodeFlagBitsKHR::DefaultKHR;
const VkVideoEncodeFlagBitsKHR VK_VIDEO_ENCODE_RESERVED_0_BIT_KHR = VkVideoEncodeFlagBitsKHR::Reserved0BitKHR;
enum class VkVideoEncodeRateControlFlagBitsKHR: uint32_t {
    DefaultKHR = 0,
    ResetBitKHR = 1,
};
const VkVideoEncodeRateControlFlagBitsKHR VK_VIDEO_ENCODE_RATE_CONTROL_DEFAULT_KHR = VkVideoEncodeRateControlFlagBitsKHR::DefaultKHR;
const VkVideoEncodeRateControlFlagBitsKHR VK_VIDEO_ENCODE_RATE_CONTROL_RESET_BIT_KHR = VkVideoEncodeRateControlFlagBitsKHR::ResetBitKHR;
enum class VkVideoEncodeRateControlModeFlagBitsKHR: uint32_t {
    NoneBitKHR = 0,
    CbrBitKHR = 1,
    VbrBitKHR = 2,
};
const VkVideoEncodeRateControlModeFlagBitsKHR VK_VIDEO_ENCODE_RATE_CONTROL_MODE_NONE_BIT_KHR = VkVideoEncodeRateControlModeFlagBitsKHR::NoneBitKHR;
const VkVideoEncodeRateControlModeFlagBitsKHR VK_VIDEO_ENCODE_RATE_CONTROL_MODE_CBR_BIT_KHR = VkVideoEncodeRateControlModeFlagBitsKHR::CbrBitKHR;
const VkVideoEncodeRateControlModeFlagBitsKHR VK_VIDEO_ENCODE_RATE_CONTROL_MODE_VBR_BIT_KHR = VkVideoEncodeRateControlModeFlagBitsKHR::VbrBitKHR;
enum class VkVideoEncodeH264CapabilitiesFlagBitsEXT: uint32_t {
    CabacBitEXT = 1,
    CavlcBitEXT = 2,
    WeightedBiPredImplicitBitEXT = 4,
    Transform8X8BitEXT = 8,
    ChromaQpOffsetBitEXT = 16,
    SecondChromaQpOffsetBitEXT = 32,
    DeblockingFilterDisabledBitEXT = 64,
    DeblockingFilterEnabledBitEXT = 128,
    DeblockingFilterPartialBitEXT = 256,
    MultipleSlicePerFrameBitEXT = 512,
    EvenlyDistributedSliceSizeBitEXT = 1024,
};
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_CABAC_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::CabacBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_CAVLC_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::CavlcBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_WEIGHTED_BI_PRED_IMPLICIT_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::WeightedBiPredImplicitBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_TRANSFORM_8X8_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::Transform8X8BitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_CHROMA_QP_OFFSET_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::ChromaQpOffsetBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_SECOND_CHROMA_QP_OFFSET_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::SecondChromaQpOffsetBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_DEBLOCKING_FILTER_DISABLED_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterDisabledBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_DEBLOCKING_FILTER_ENABLED_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterEnabledBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_DEBLOCKING_FILTER_PARTIAL_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::DeblockingFilterPartialBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_MULTIPLE_SLICE_PER_FRAME_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::MultipleSlicePerFrameBitEXT;
const VkVideoEncodeH264CapabilitiesFlagBitsEXT VK_VIDEO_ENCODE_H264_CAPABILITY_EVENLY_DISTRIBUTED_SLICE_SIZE_BIT_EXT = VkVideoEncodeH264CapabilitiesFlagBitsEXT::EvenlyDistributedSliceSizeBitEXT;
enum class VkVideoEncodeH264InputModeFlagBitsEXT: uint32_t {
    FrameBitEXT = 1,
    SliceBitEXT = 2,
    NonVclBitEXT = 4,
};
const VkVideoEncodeH264InputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_INPUT_MODE_FRAME_BIT_EXT = VkVideoEncodeH264InputModeFlagBitsEXT::FrameBitEXT;
const VkVideoEncodeH264InputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_INPUT_MODE_SLICE_BIT_EXT = VkVideoEncodeH264InputModeFlagBitsEXT::SliceBitEXT;
const VkVideoEncodeH264InputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_INPUT_MODE_NON_VCL_BIT_EXT = VkVideoEncodeH264InputModeFlagBitsEXT::NonVclBitEXT;
enum class VkVideoEncodeH264OutputModeFlagBitsEXT: uint32_t {
    FrameBitEXT = 1,
    SliceBitEXT = 2,
    NonVclBitEXT = 4,
};
const VkVideoEncodeH264OutputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_OUTPUT_MODE_FRAME_BIT_EXT = VkVideoEncodeH264OutputModeFlagBitsEXT::FrameBitEXT;
const VkVideoEncodeH264OutputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_OUTPUT_MODE_SLICE_BIT_EXT = VkVideoEncodeH264OutputModeFlagBitsEXT::SliceBitEXT;
const VkVideoEncodeH264OutputModeFlagBitsEXT VK_VIDEO_ENCODE_H264_OUTPUT_MODE_NON_VCL_BIT_EXT = VkVideoEncodeH264OutputModeFlagBitsEXT::NonVclBitEXT;
enum class VkVideoEncodeH264CreateFlagBitsEXT: uint32_t {
    DefaultEXT = 0,
    Reserved0BitEXT = 1,
};
const VkVideoEncodeH264CreateFlagBitsEXT VK_VIDEO_ENCODE_H264_CREATE_DEFAULT_EXT = VkVideoEncodeH264CreateFlagBitsEXT::DefaultEXT;
const VkVideoEncodeH264CreateFlagBitsEXT VK_VIDEO_ENCODE_H264_CREATE_RESERVED_0_BIT_EXT = VkVideoEncodeH264CreateFlagBitsEXT::Reserved0BitEXT;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
enum class VkQueryPoolCreateFlagBits: uint32_t { };
enum class VkPipelineLayoutCreateFlagBits: uint32_t { };
enum class VkPipelineDepthStencilStateCreateFlagBits: uint32_t { };
enum class VkPipelineDynamicStateCreateFlagBits: uint32_t { };
enum class VkPipelineColorBlendStateCreateFlagBits: uint32_t { };
enum class VkPipelineMultisampleStateCreateFlagBits: uint32_t { };
enum class VkPipelineRasterizationStateCreateFlagBits: uint32_t { };
enum class VkPipelineViewportStateCreateFlagBits: uint32_t { };
enum class VkPipelineTessellationStateCreateFlagBits: uint32_t { };
enum class VkPipelineInputAssemblyStateCreateFlagBits: uint32_t { };
enum class VkPipelineVertexInputStateCreateFlagBits: uint32_t { };
enum class VkBufferViewCreateFlagBits: uint32_t { };
enum class VkInstanceCreateFlagBits: uint32_t { };
enum class VkDeviceCreateFlagBits: uint32_t { };
enum class VkSemaphoreCreateFlagBits: uint32_t { };
enum class VkMemoryMapFlagBits: uint32_t { };
enum class VkDescriptorPoolResetFlagBits: uint32_t { };
enum class VkDescriptorUpdateTemplateCreateFlagBits: uint32_t { };
enum class VkDisplayModeCreateFlagBitsKHR: uint32_t { };
enum class VkDisplaySurfaceCreateFlagBitsKHR: uint32_t { };
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
enum class VkAndroidSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
enum class VkViSurfaceCreateFlagBitsNN: uint32_t { };
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
enum class VkWaylandSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
enum class VkWin32SurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
enum class VkXlibSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
enum class VkXcbSurfaceCreateFlagBitsKHR: uint32_t { };
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
enum class VkDirectFBSurfaceCreateFlagBitsEXT: uint32_t { };
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
enum class VkIOSSurfaceCreateFlagBitsMVK: uint32_t { };
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
enum class VkMacOSSurfaceCreateFlagBitsMVK: uint32_t { };
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
enum class VkMetalSurfaceCreateFlagBitsEXT: uint32_t { };
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
enum class VkImagePipeSurfaceCreateFlagBitsFUCHSIA: uint32_t { };
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
enum class VkStreamDescriptorSurfaceCreateFlagBitsGGP: uint32_t { };
#endif // defined(VK_USE_PLATFORM_GGP)
enum class VkHeadlessSurfaceCreateFlagBitsEXT: uint32_t { };
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
enum class VkScreenSurfaceCreateFlagBitsQNX: uint32_t { };
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
enum class VkCommandPoolTrimFlagBits: uint32_t { };
enum class VkPipelineViewportSwizzleStateCreateFlagBitsNV: uint32_t { };
enum class VkPipelineDiscardRectangleStateCreateFlagBitsEXT: uint32_t { };
enum class VkPipelineCoverageToColorStateCreateFlagBitsNV: uint32_t { };
enum class VkPipelineCoverageModulationStateCreateFlagBitsNV: uint32_t { };
enum class VkPipelineCoverageReductionStateCreateFlagBitsNV: uint32_t { };
enum class VkValidationCacheCreateFlagBitsEXT: uint32_t { };
enum class VkDebugUtilsMessengerCreateFlagBitsEXT: uint32_t { };
enum class VkDebugUtilsMessengerCallbackDataFlagBitsEXT: uint32_t { };
enum class VkDeviceMemoryReportFlagBitsEXT: uint32_t { };
enum class VkPipelineRasterizationConservativeStateCreateFlagBitsEXT: uint32_t { };
enum class VkPipelineRasterizationStateStreamCreateFlagBitsEXT: uint32_t { };
enum class VkPipelineRasterizationDepthClipStateCreateFlagBitsEXT: uint32_t { };
#if defined(VK_ENABLE_BETA_EXTENSIONS)
enum class VkVideoBeginCodingFlagBitsKHR: uint32_t { };
enum class VkVideoEndCodingFlagBitsKHR: uint32_t { };
enum class VkVideoDecodeH264CreateFlagBitsEXT: uint32_t { };
enum class VkVideoDecodeH265CreateFlagBitsEXT: uint32_t { };
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)

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
    return a.flags = (a.flags | b.flags), a;                                                                              \
}                                                                                          \
constexpr FLAG_TYPE& operator&=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                      \
    return a.flags = (a.flags & b.flags), a;                                                                              \
}                                                                                          \
constexpr FLAG_TYPE operator^=(FLAG_TYPE& a, FLAG_TYPE b) noexcept {                       \
    return  a.flags = (a.flags ^ b.flags), a;                                                                              \
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

DECLARE_ENUM_FLAG_OPERATORS(VkFramebufferCreateFlags, VkFramebufferCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkQueryPoolCreateFlags, VkQueryPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkRenderPassCreateFlags, VkRenderPassCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSamplerCreateFlags, VkSamplerCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineLayoutCreateFlags, VkPipelineLayoutCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCacheCreateFlags, VkPipelineCacheCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineDepthStencilStateCreateFlags, VkPipelineDepthStencilStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineDynamicStateCreateFlags, VkPipelineDynamicStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineColorBlendStateCreateFlags, VkPipelineColorBlendStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineMultisampleStateCreateFlags, VkPipelineMultisampleStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineRasterizationStateCreateFlags, VkPipelineRasterizationStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineViewportStateCreateFlags, VkPipelineViewportStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineTessellationStateCreateFlags, VkPipelineTessellationStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineInputAssemblyStateCreateFlags, VkPipelineInputAssemblyStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineVertexInputStateCreateFlags, VkPipelineVertexInputStateCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineShaderStageCreateFlags, VkPipelineShaderStageCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDescriptorSetLayoutCreateFlags, VkDescriptorSetLayoutCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkBufferViewCreateFlags, VkBufferViewCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkInstanceCreateFlags, VkInstanceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDeviceCreateFlags, VkDeviceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDeviceQueueCreateFlags, VkDeviceQueueCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkQueueFlags, VkQueueFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkMemoryPropertyFlags, VkMemoryPropertyFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkMemoryHeapFlags, VkMemoryHeapFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkAccessFlags, VkAccessFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkBufferUsageFlags, VkBufferUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkBufferCreateFlags, VkBufferCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkShaderStageFlags, VkShaderStageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkImageUsageFlags, VkImageUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkImageCreateFlags, VkImageCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkImageViewCreateFlags, VkImageViewCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCreateFlags, VkPipelineCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkColorComponentFlags, VkColorComponentFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkFenceCreateFlags, VkFenceCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSemaphoreCreateFlags, VkSemaphoreCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkFormatFeatureFlags, VkFormatFeatureFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkQueryControlFlags, VkQueryControlFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkQueryResultFlags, VkQueryResultFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkShaderModuleCreateFlags, VkShaderModuleCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkEventCreateFlags, VkEventCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCommandPoolCreateFlags, VkCommandPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCommandPoolResetFlags, VkCommandPoolResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCommandBufferResetFlags, VkCommandBufferResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCommandBufferUsageFlags, VkCommandBufferUsageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkQueryPipelineStatisticFlags, VkQueryPipelineStatisticFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkMemoryMapFlags, VkMemoryMapFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkImageAspectFlags, VkImageAspectFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSparseMemoryBindFlags, VkSparseMemoryBindFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSparseImageFormatFlags, VkSparseImageFormatFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSubpassDescriptionFlags, VkSubpassDescriptionFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineStageFlags, VkPipelineStageFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSampleCountFlags, VkSampleCountFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkAttachmentDescriptionFlags, VkAttachmentDescriptionFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkStencilFaceFlags, VkStencilFaceFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCullModeFlags, VkCullModeFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDescriptorPoolCreateFlags, VkDescriptorPoolCreateFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDescriptorPoolResetFlags, VkDescriptorPoolResetFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDependencyFlags, VkDependencyFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSubgroupFeatureFlags, VkSubgroupFeatureFlagBits, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkIndirectCommandsLayoutUsageFlagsNV, VkIndirectCommandsLayoutUsageFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkIndirectStateFlagsNV, VkIndirectStateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkGeometryFlagsKHR, VkGeometryFlagBitsKHR, uint32_t)
using VkGeometryFlagsNV = VkGeometryFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(VkGeometryInstanceFlagsKHR, VkGeometryInstanceFlagBitsKHR, uint32_t)
using VkGeometryInstanceFlagsNV = VkGeometryInstanceFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(VkBuildAccelerationStructureFlagsKHR, VkBuildAccelerationStructureFlagBitsKHR, uint32_t)
using VkBuildAccelerationStructureFlagsNV = VkBuildAccelerationStructureFlagsKHR;
DECLARE_ENUM_FLAG_OPERATORS(VkPrivateDataSlotCreateFlagsEXT, VkPrivateDataSlotCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkAccelerationStructureCreateFlagsKHR, VkAccelerationStructureCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDescriptorUpdateTemplateCreateFlags, VkDescriptorUpdateTemplateCreateFlagBits, uint32_t)
using VkDescriptorUpdateTemplateCreateFlagsKHR = VkDescriptorUpdateTemplateCreateFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCreationFeedbackFlagsEXT, VkPipelineCreationFeedbackFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPerformanceCounterDescriptionFlagsKHR, VkPerformanceCounterDescriptionFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkAcquireProfilingLockFlagsKHR, VkAcquireProfilingLockFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSemaphoreWaitFlags, VkSemaphoreWaitFlagBits, uint32_t)
using VkSemaphoreWaitFlagsKHR = VkSemaphoreWaitFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCompilerControlFlagsAMD, VkPipelineCompilerControlFlagBitsAMD, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkShaderCorePropertiesFlagsAMD, VkShaderCorePropertiesFlagBitsAMD, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDeviceDiagnosticsConfigFlagsNV, VkDeviceDiagnosticsConfigFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkAccessFlags2KHR, VkAccessFlagBits2KHR, uint64_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineStageFlags2KHR, VkPipelineStageFlagBits2KHR, uint64_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCompositeAlphaFlagsKHR, VkCompositeAlphaFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDisplayPlaneAlphaFlagsKHR, VkDisplayPlaneAlphaFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSurfaceTransformFlagsKHR, VkSurfaceTransformFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSwapchainCreateFlagsKHR, VkSwapchainCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDisplayModeCreateFlagsKHR, VkDisplayModeCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDisplaySurfaceCreateFlagsKHR, VkDisplaySurfaceCreateFlagBitsKHR, uint32_t)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
DECLARE_ENUM_FLAG_OPERATORS(VkAndroidSurfaceCreateFlagsKHR, VkAndroidSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
DECLARE_ENUM_FLAG_OPERATORS(VkViSurfaceCreateFlagsNN, VkViSurfaceCreateFlagBitsNN, uint32_t)
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
DECLARE_ENUM_FLAG_OPERATORS(VkWaylandSurfaceCreateFlagsKHR, VkWaylandSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
DECLARE_ENUM_FLAG_OPERATORS(VkWin32SurfaceCreateFlagsKHR, VkWin32SurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
DECLARE_ENUM_FLAG_OPERATORS(VkXlibSurfaceCreateFlagsKHR, VkXlibSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
DECLARE_ENUM_FLAG_OPERATORS(VkXcbSurfaceCreateFlagsKHR, VkXcbSurfaceCreateFlagBitsKHR, uint32_t)
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
DECLARE_ENUM_FLAG_OPERATORS(VkDirectFBSurfaceCreateFlagsEXT, VkDirectFBSurfaceCreateFlagBitsEXT, uint32_t)
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_IOS_MVK)
DECLARE_ENUM_FLAG_OPERATORS(VkIOSSurfaceCreateFlagsMVK, VkIOSSurfaceCreateFlagBitsMVK, uint32_t)
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
DECLARE_ENUM_FLAG_OPERATORS(VkMacOSSurfaceCreateFlagsMVK, VkMacOSSurfaceCreateFlagBitsMVK, uint32_t)
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
DECLARE_ENUM_FLAG_OPERATORS(VkMetalSurfaceCreateFlagsEXT, VkMetalSurfaceCreateFlagBitsEXT, uint32_t)
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
DECLARE_ENUM_FLAG_OPERATORS(VkImagePipeSurfaceCreateFlagsFUCHSIA, VkImagePipeSurfaceCreateFlagBitsFUCHSIA, uint32_t)
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
DECLARE_ENUM_FLAG_OPERATORS(VkStreamDescriptorSurfaceCreateFlagsGGP, VkStreamDescriptorSurfaceCreateFlagBitsGGP, uint32_t)
#endif // defined(VK_USE_PLATFORM_GGP)
DECLARE_ENUM_FLAG_OPERATORS(VkHeadlessSurfaceCreateFlagsEXT, VkHeadlessSurfaceCreateFlagBitsEXT, uint32_t)
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
DECLARE_ENUM_FLAG_OPERATORS(VkScreenSurfaceCreateFlagsQNX, VkScreenSurfaceCreateFlagBitsQNX, uint32_t)
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
DECLARE_ENUM_FLAG_OPERATORS(VkPeerMemoryFeatureFlags, VkPeerMemoryFeatureFlagBits, uint32_t)
using VkPeerMemoryFeatureFlagsKHR = VkPeerMemoryFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkMemoryAllocateFlags, VkMemoryAllocateFlagBits, uint32_t)
using VkMemoryAllocateFlagsKHR = VkMemoryAllocateFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkDeviceGroupPresentModeFlagsKHR, VkDeviceGroupPresentModeFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDebugReportFlagsEXT, VkDebugReportFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkCommandPoolTrimFlags, VkCommandPoolTrimFlagBits, uint32_t)
using VkCommandPoolTrimFlagsKHR = VkCommandPoolTrimFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalMemoryHandleTypeFlagsNV, VkExternalMemoryHandleTypeFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkExternalMemoryFeatureFlagsNV, VkExternalMemoryFeatureFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkExternalMemoryHandleTypeFlags, VkExternalMemoryHandleTypeFlagBits, uint32_t)
using VkExternalMemoryHandleTypeFlagsKHR = VkExternalMemoryHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalMemoryFeatureFlags, VkExternalMemoryFeatureFlagBits, uint32_t)
using VkExternalMemoryFeatureFlagsKHR = VkExternalMemoryFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalSemaphoreHandleTypeFlags, VkExternalSemaphoreHandleTypeFlagBits, uint32_t)
using VkExternalSemaphoreHandleTypeFlagsKHR = VkExternalSemaphoreHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalSemaphoreFeatureFlags, VkExternalSemaphoreFeatureFlagBits, uint32_t)
using VkExternalSemaphoreFeatureFlagsKHR = VkExternalSemaphoreFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkSemaphoreImportFlags, VkSemaphoreImportFlagBits, uint32_t)
using VkSemaphoreImportFlagsKHR = VkSemaphoreImportFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalFenceHandleTypeFlags, VkExternalFenceHandleTypeFlagBits, uint32_t)
using VkExternalFenceHandleTypeFlagsKHR = VkExternalFenceHandleTypeFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkExternalFenceFeatureFlags, VkExternalFenceFeatureFlagBits, uint32_t)
using VkExternalFenceFeatureFlagsKHR = VkExternalFenceFeatureFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkFenceImportFlags, VkFenceImportFlagBits, uint32_t)
using VkFenceImportFlagsKHR = VkFenceImportFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkSurfaceCounterFlagsEXT, VkSurfaceCounterFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineViewportSwizzleStateCreateFlagsNV, VkPipelineViewportSwizzleStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineDiscardRectangleStateCreateFlagsEXT, VkPipelineDiscardRectangleStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCoverageToColorStateCreateFlagsNV, VkPipelineCoverageToColorStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCoverageModulationStateCreateFlagsNV, VkPipelineCoverageModulationStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineCoverageReductionStateCreateFlagsNV, VkPipelineCoverageReductionStateCreateFlagBitsNV, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkValidationCacheCreateFlagsEXT, VkValidationCacheCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDebugUtilsMessageSeverityFlagsEXT, VkDebugUtilsMessageSeverityFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDebugUtilsMessageTypeFlagsEXT, VkDebugUtilsMessageTypeFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDebugUtilsMessengerCreateFlagsEXT, VkDebugUtilsMessengerCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDebugUtilsMessengerCallbackDataFlagsEXT, VkDebugUtilsMessengerCallbackDataFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDeviceMemoryReportFlagsEXT, VkDeviceMemoryReportFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineRasterizationConservativeStateCreateFlagsEXT, VkPipelineRasterizationConservativeStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkDescriptorBindingFlags, VkDescriptorBindingFlagBits, uint32_t)
using VkDescriptorBindingFlagsEXT = VkDescriptorBindingFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkConditionalRenderingFlagsEXT, VkConditionalRenderingFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkResolveModeFlags, VkResolveModeFlagBits, uint32_t)
using VkResolveModeFlagsKHR = VkResolveModeFlags;
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineRasterizationStateStreamCreateFlagsEXT, VkPipelineRasterizationStateStreamCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkPipelineRasterizationDepthClipStateCreateFlagsEXT, VkPipelineRasterizationDepthClipStateCreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkToolPurposeFlagsEXT, VkToolPurposeFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkSubmitFlagsKHR, VkSubmitFlagBitsKHR, uint32_t)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoCodecOperationFlagsKHR, VkVideoCodecOperationFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoCapabilitiesFlagsKHR, VkVideoCapabilitiesFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoSessionCreateFlagsKHR, VkVideoSessionCreateFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoBeginCodingFlagsKHR, VkVideoBeginCodingFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEndCodingFlagsKHR, VkVideoEndCodingFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoCodingQualityPresetFlagsKHR, VkVideoCodingQualityPresetFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoCodingControlFlagsKHR, VkVideoCodingControlFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoDecodeFlagsKHR, VkVideoDecodeFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoDecodeH264FieldLayoutFlagsEXT, VkVideoDecodeH264FieldLayoutFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoDecodeH264CreateFlagsEXT, VkVideoDecodeH264CreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoDecodeH265CreateFlagsEXT, VkVideoDecodeH265CreateFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeFlagsKHR, VkVideoEncodeFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeRateControlFlagsKHR, VkVideoEncodeRateControlFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeRateControlModeFlagsKHR, VkVideoEncodeRateControlModeFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoChromaSubsamplingFlagsKHR, VkVideoChromaSubsamplingFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoComponentBitDepthFlagsKHR, VkVideoComponentBitDepthFlagBitsKHR, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeH264CapabilitiesFlagsEXT, VkVideoEncodeH264CapabilitiesFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeH264InputModeFlagsEXT, VkVideoEncodeH264InputModeFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeH264OutputModeFlagsEXT, VkVideoEncodeH264OutputModeFlagBitsEXT, uint32_t)
DECLARE_ENUM_FLAG_OPERATORS(VkVideoEncodeH264CreateFlagsEXT, VkVideoEncodeH264CreateFlagBitsEXT, uint32_t)
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
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
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkVideoSessionKHR)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkVideoSessionParametersKHR)
struct VkDebugUtilsMessengerCallbackDataEXT;
struct VkDeviceMemoryReportCallbackDataEXT;

#ifdef __cplusplus
extern "C" {
#endif
typedef void (VKAPI_PTR * PFN_vkInternalAllocationNotification )(
     void *                                       pUserData,
     size_t                                       size,
     VkInternalAllocationType                     allocationType,
     VkSystemAllocationScope                      allocationScope);
typedef void (VKAPI_PTR * PFN_vkInternalFreeNotification )(
     void *                                       pUserData,
     size_t                                       size,
     VkInternalAllocationType                     allocationType,
     VkSystemAllocationScope                      allocationScope);
typedef void* (VKAPI_PTR * PFN_vkReallocationFunction )(
     void *                                       pUserData,
     void *                                       pOriginal,
     size_t                                       size,
     size_t                                       alignment,
     VkSystemAllocationScope                      allocationScope);
typedef void* (VKAPI_PTR * PFN_vkAllocationFunction )(
     void *                                       pUserData,
     size_t                                       size,
     size_t                                       alignment,
     VkSystemAllocationScope                      allocationScope);
typedef void (VKAPI_PTR * PFN_vkFreeFunction )(
     void *                                       pUserData,
     void *                                       pMemory);
typedef void (VKAPI_PTR * PFN_vkVoidFunction )(void);
typedef VkBool32 (VKAPI_PTR * PFN_vkDebugReportCallbackEXT )(
     VkDebugReportFlagsEXT                        flags,
     VkDebugReportObjectTypeEXT                   objectType,
     uint64_t                                     object,
     size_t                                       location,
     int32_t                                      messageCode,
    const  char *                                 pLayerPrefix,
    const  char *                                 pMessage,
     void *                                       pUserData);
typedef VkBool32 (VKAPI_PTR * PFN_vkDebugUtilsMessengerCallbackEXT )(
     VkDebugUtilsMessageSeverityFlagBitsEXT            messageSeverity,
     VkDebugUtilsMessageTypeFlagsEXT                   messageTypes,
    const  VkDebugUtilsMessengerCallbackDataEXT *      pCallbackData,
     void *                                            pUserData);
typedef void (VKAPI_PTR * PFN_vkDeviceMemoryReportCallbackEXT )(
    const  VkDeviceMemoryReportCallbackDataEXT *  pCallbackData,
     void *                                       pUserData);
struct VkBaseOutStructure {
    VkStructureType   sType{};
    struct  VkBaseOutStructure *  pNext{};
};
struct VkBaseInStructure {
    VkStructureType   sType{};
    const struct  VkBaseInStructure *  pNext{};
};
struct VkOffset2D {
    int32_t          x{};
    int32_t          y{};
};
struct VkOffset3D {
    int32_t          x{};
    int32_t          y{};
    int32_t          z{};
};
struct VkExtent2D {
    uint32_t          width{};
    uint32_t          height{};
};
struct VkExtent3D {
    uint32_t          width{};
    uint32_t          height{};
    uint32_t          depth{};
};
struct VkViewport {
    float   x{};
    float   y{};
    float   width{};
    float   height{};
    float                         minDepth{};
    float                         maxDepth{};
};
struct VkRect2D {
    VkOffset2D       offset{};
    VkExtent2D       extent{};
};
struct VkClearRect {
    VkRect2D         rect{};
    uint32_t         baseArrayLayer{};
    uint32_t         layerCount{};
};
struct VkComponentMapping {
    VkComponentSwizzle   r{};
    VkComponentSwizzle   g{};
    VkComponentSwizzle   b{};
    VkComponentSwizzle   a{};
};
struct VkPhysicalDeviceSparseProperties {
    VkBool32                 residencyStandard2DBlockShape{};
    VkBool32                 residencyStandard2DMultisampleBlockShape{};
    VkBool32                 residencyStandard3DBlockShape{};
    VkBool32                 residencyAlignedMipSize{};
    VkBool32                 residencyNonResidentStrict{};
};
struct VkPhysicalDeviceLimits {
    uint32_t                 maxImageDimension1D{};
    uint32_t                 maxImageDimension2D{};
    uint32_t                 maxImageDimension3D{};
    uint32_t                 maxImageDimensionCube{};
    uint32_t                 maxImageArrayLayers{};
    uint32_t                 maxTexelBufferElements{};
    uint32_t                 maxUniformBufferRange{};
    uint32_t                 maxStorageBufferRange{};
    uint32_t                 maxPushConstantsSize{};
    uint32_t                 maxMemoryAllocationCount{};
    uint32_t                 maxSamplerAllocationCount{};
    VkDeviceSize             bufferImageGranularity{};
    VkDeviceSize             sparseAddressSpaceSize{};
    uint32_t                 maxBoundDescriptorSets{};
    uint32_t                 maxPerStageDescriptorSamplers{};
    uint32_t                 maxPerStageDescriptorUniformBuffers{};
    uint32_t                 maxPerStageDescriptorStorageBuffers{};
    uint32_t                 maxPerStageDescriptorSampledImages{};
    uint32_t                 maxPerStageDescriptorStorageImages{};
    uint32_t                 maxPerStageDescriptorInputAttachments{};
    uint32_t                 maxPerStageResources{};
    uint32_t                 maxDescriptorSetSamplers{};
    uint32_t                 maxDescriptorSetUniformBuffers{};
    uint32_t                 maxDescriptorSetUniformBuffersDynamic{};
    uint32_t                 maxDescriptorSetStorageBuffers{};
    uint32_t                 maxDescriptorSetStorageBuffersDynamic{};
    uint32_t                 maxDescriptorSetSampledImages{};
    uint32_t                 maxDescriptorSetStorageImages{};
    uint32_t                 maxDescriptorSetInputAttachments{};
    uint32_t                 maxVertexInputAttributes{};
    uint32_t                 maxVertexInputBindings{};
    uint32_t                 maxVertexInputAttributeOffset{};
    uint32_t                 maxVertexInputBindingStride{};
    uint32_t                 maxVertexOutputComponents{};
    uint32_t                 maxTessellationGenerationLevel{};
    uint32_t                 maxTessellationPatchSize{};
    uint32_t                 maxTessellationControlPerVertexInputComponents{};
    uint32_t                 maxTessellationControlPerVertexOutputComponents{};
    uint32_t                 maxTessellationControlPerPatchOutputComponents{};
    uint32_t                 maxTessellationControlTotalOutputComponents{};
    uint32_t                 maxTessellationEvaluationInputComponents{};
    uint32_t                 maxTessellationEvaluationOutputComponents{};
    uint32_t                 maxGeometryShaderInvocations{};
    uint32_t                 maxGeometryInputComponents{};
    uint32_t                 maxGeometryOutputComponents{};
    uint32_t                 maxGeometryOutputVertices{};
    uint32_t                 maxGeometryTotalOutputComponents{};
    uint32_t                 maxFragmentInputComponents{};
    uint32_t                 maxFragmentOutputAttachments{};
    uint32_t                 maxFragmentDualSrcAttachments{};
    uint32_t                 maxFragmentCombinedOutputResources{};
    uint32_t                 maxComputeSharedMemorySize{};
    uint32_t                 maxComputeWorkGroupCount [3]{};
    uint32_t                 maxComputeWorkGroupInvocations{};
    uint32_t                 maxComputeWorkGroupSize [3]{};
    uint32_t                 subPixelPrecisionBits{};
    uint32_t                 subTexelPrecisionBits{};
    uint32_t                 mipmapPrecisionBits{};
    uint32_t                 maxDrawIndexedIndexValue{};
    uint32_t                 maxDrawIndirectCount{};
    float                    maxSamplerLodBias{};
    float                    maxSamplerAnisotropy{};
    uint32_t                 maxViewports{};
    uint32_t                 maxViewportDimensions [2]{};
    float                    viewportBoundsRange [2]{};
    uint32_t                 viewportSubPixelBits{};
    size_t                   minMemoryMapAlignment{};
    VkDeviceSize             minTexelBufferOffsetAlignment{};
    VkDeviceSize             minUniformBufferOffsetAlignment{};
    VkDeviceSize             minStorageBufferOffsetAlignment{};
    int32_t                  minTexelOffset{};
    uint32_t                 maxTexelOffset{};
    int32_t                  minTexelGatherOffset{};
    uint32_t                 maxTexelGatherOffset{};
    float                    minInterpolationOffset{};
    float                    maxInterpolationOffset{};
    uint32_t                 subPixelInterpolationOffsetBits{};
    uint32_t                 maxFramebufferWidth{};
    uint32_t                 maxFramebufferHeight{};
    uint32_t                 maxFramebufferLayers{};
    VkSampleCountFlags       framebufferColorSampleCounts{};
    VkSampleCountFlags       framebufferDepthSampleCounts{};
    VkSampleCountFlags       framebufferStencilSampleCounts{};
    VkSampleCountFlags       framebufferNoAttachmentsSampleCounts{};
    uint32_t                 maxColorAttachments{};
    VkSampleCountFlags       sampledImageColorSampleCounts{};
    VkSampleCountFlags       sampledImageIntegerSampleCounts{};
    VkSampleCountFlags       sampledImageDepthSampleCounts{};
    VkSampleCountFlags       sampledImageStencilSampleCounts{};
    VkSampleCountFlags       storageImageSampleCounts{};
    uint32_t                 maxSampleMaskWords{};
    VkBool32                 timestampComputeAndGraphics{};
    float                    timestampPeriod{};
    uint32_t                 maxClipDistances{};
    uint32_t                 maxCullDistances{};
    uint32_t                 maxCombinedClipAndCullDistances{};
    uint32_t                 discreteQueuePriorities{};
    float                    pointSizeRange [2]{};
    float                    lineWidthRange [2]{};
    float                    pointSizeGranularity{};
    float                    lineWidthGranularity{};
    VkBool32                 strictLines{};
    VkBool32                 standardSampleLocations{};
    VkDeviceSize             optimalBufferCopyOffsetAlignment{};
    VkDeviceSize             optimalBufferCopyRowPitchAlignment{};
    VkDeviceSize             nonCoherentAtomSize{};
};
struct VkPhysicalDeviceProperties {
    uint32_t         apiVersion{};
    uint32_t         driverVersion{};
    uint32_t         vendorID{};
    uint32_t         deviceID{};
    VkPhysicalDeviceType   deviceType{};
    char             deviceName [ VK_MAX_PHYSICAL_DEVICE_NAME_SIZE ]{};
    uint8_t          pipelineCacheUUID [ VK_UUID_SIZE ]{};
    VkPhysicalDeviceLimits   limits{};
    VkPhysicalDeviceSparseProperties   sparseProperties{};
};
struct VkExtensionProperties {
    char              extensionName [ VK_MAX_EXTENSION_NAME_SIZE ]{};
    uint32_t          specVersion{};
};
struct VkLayerProperties {
    char              layerName [ VK_MAX_EXTENSION_NAME_SIZE ]{};
    uint32_t          specVersion{};
    uint32_t          implementationVersion{};
    char              description [ VK_MAX_DESCRIPTION_SIZE ]{};
};
struct VkApplicationInfo {
    VkStructureType   sType = VkStructureType::ApplicationInfo;
    const  void *      pNext{};
    const  char *      pApplicationName{};
    uint32_t          applicationVersion{};
    const  char *      pEngineName{};
    uint32_t          engineVersion{};
    uint32_t          apiVersion{};
};
struct VkAllocationCallbacks {
    void *            pUserData{};
    PFN_vkAllocationFunction     pfnAllocation{};
    PFN_vkReallocationFunction   pfnReallocation{};
    PFN_vkFreeFunction      pfnFree{};
    PFN_vkInternalAllocationNotification   pfnInternalAllocation{};
    PFN_vkInternalFreeNotification   pfnInternalFree{};
};
struct VkDeviceQueueCreateInfo {
    VkStructureType   sType = VkStructureType::DeviceQueueCreateInfo;
    const  void *      pNext{};
    VkDeviceQueueCreateFlags      flags{};
    uint32_t          queueFamilyIndex{};
    uint32_t          queueCount{};
    const  float *     pQueuePriorities{};
};
struct VkPhysicalDeviceFeatures {
    VkBool32                 robustBufferAccess{};
    VkBool32                 fullDrawIndexUint32{};
    VkBool32                 imageCubeArray{};
    VkBool32                 independentBlend{};
    VkBool32                 geometryShader{};
    VkBool32                 tessellationShader{};
    VkBool32                 sampleRateShading{};
    VkBool32                 dualSrcBlend{};
    VkBool32                 logicOp{};
    VkBool32                 multiDrawIndirect{};
    VkBool32                 drawIndirectFirstInstance{};
    VkBool32                 depthClamp{};
    VkBool32                 depthBiasClamp{};
    VkBool32                 fillModeNonSolid{};
    VkBool32                 depthBounds{};
    VkBool32                 wideLines{};
    VkBool32                 largePoints{};
    VkBool32                 alphaToOne{};
    VkBool32                 multiViewport{};
    VkBool32                 samplerAnisotropy{};
    VkBool32                 textureCompressionETC2{};
    VkBool32                 textureCompressionASTC_LDR{};
    VkBool32                 textureCompressionBC{};
    VkBool32                 occlusionQueryPrecise{};
    VkBool32                 pipelineStatisticsQuery{};
    VkBool32                 vertexPipelineStoresAndAtomics{};
    VkBool32                 fragmentStoresAndAtomics{};
    VkBool32                 shaderTessellationAndGeometryPointSize{};
    VkBool32                 shaderImageGatherExtended{};
    VkBool32                 shaderStorageImageExtendedFormats{};
    VkBool32                 shaderStorageImageMultisample{};
    VkBool32                 shaderStorageImageReadWithoutFormat{};
    VkBool32                 shaderStorageImageWriteWithoutFormat{};
    VkBool32                 shaderUniformBufferArrayDynamicIndexing{};
    VkBool32                 shaderSampledImageArrayDynamicIndexing{};
    VkBool32                 shaderStorageBufferArrayDynamicIndexing{};
    VkBool32                 shaderStorageImageArrayDynamicIndexing{};
    VkBool32                 shaderClipDistance{};
    VkBool32                 shaderCullDistance{};
    VkBool32                 shaderFloat64{};
    VkBool32                 shaderInt64{};
    VkBool32                 shaderInt16{};
    VkBool32                 shaderResourceResidency{};
    VkBool32                 shaderResourceMinLod{};
    VkBool32                 sparseBinding{};
    VkBool32                 sparseResidencyBuffer{};
    VkBool32                 sparseResidencyImage2D{};
    VkBool32                 sparseResidencyImage3D{};
    VkBool32                 sparseResidency2Samples{};
    VkBool32                 sparseResidency4Samples{};
    VkBool32                 sparseResidency8Samples{};
    VkBool32                 sparseResidency16Samples{};
    VkBool32                 sparseResidencyAliased{};
    VkBool32                 variableMultisampleRate{};
    VkBool32                 inheritedQueries{};
};
struct VkDeviceCreateInfo {
    VkStructureType   sType = VkStructureType::DeviceCreateInfo;
    const  void *      pNext{};
    VkDeviceCreateFlags      flags{};
    uint32_t          queueCreateInfoCount{};
    const  VkDeviceQueueCreateInfo *  pQueueCreateInfos{};
    uint32_t                 enabledLayerCount{};
    const  char * const*       ppEnabledLayerNames{};
    uint32_t                 enabledExtensionCount{};
    const  char * const*       ppEnabledExtensionNames{};
    const  VkPhysicalDeviceFeatures *  pEnabledFeatures{};
};
struct VkInstanceCreateInfo {
    VkStructureType   sType = VkStructureType::InstanceCreateInfo;
    const  void *      pNext{};
    VkInstanceCreateFlags    flags{};
    const  VkApplicationInfo *  pApplicationInfo{};
    uint32_t                 enabledLayerCount{};
    const  char * const*       ppEnabledLayerNames{};
    uint32_t                 enabledExtensionCount{};
    const  char * const*       ppEnabledExtensionNames{};
};
struct VkQueueFamilyProperties {
    VkQueueFlags             queueFlags{};
    uint32_t                 queueCount{};
    uint32_t                 timestampValidBits{};
    VkExtent3D               minImageTransferGranularity{};
};
struct VkMemoryHeap {
    VkDeviceSize             size{};
    VkMemoryHeapFlags        flags{};
};
struct VkMemoryType {
    VkMemoryPropertyFlags    propertyFlags{};
    uint32_t                 heapIndex{};
};
struct VkPhysicalDeviceMemoryProperties {
    uint32_t                 memoryTypeCount{};
    VkMemoryType             memoryTypes [ VK_MAX_MEMORY_TYPES ]{};
    uint32_t                 memoryHeapCount{};
    VkMemoryHeap             memoryHeaps [ VK_MAX_MEMORY_HEAPS ]{};
};
struct VkMemoryAllocateInfo {
    VkStructureType   sType = VkStructureType::MemoryAllocateInfo;
    const  void *             pNext{};
    VkDeviceSize             allocationSize{};
    uint32_t                 memoryTypeIndex{};
};
struct VkMemoryRequirements {
    VkDeviceSize             size{};
    VkDeviceSize             alignment{};
    uint32_t                 memoryTypeBits{};
};
struct VkSparseImageFormatProperties {
    VkImageAspectFlags       aspectMask{};
    VkExtent3D               imageGranularity{};
    VkSparseImageFormatFlags   flags{};
};
struct VkSparseImageMemoryRequirements {
    VkSparseImageFormatProperties   formatProperties{};
    uint32_t                 imageMipTailFirstLod{};
    VkDeviceSize             imageMipTailSize{};
    VkDeviceSize             imageMipTailOffset{};
    VkDeviceSize             imageMipTailStride{};
};
struct VkMappedMemoryRange {
    VkStructureType   sType = VkStructureType::MappedMemoryRange;
    const  void *             pNext{};
    VkDeviceMemory           memory{};
    VkDeviceSize             offset{};
    VkDeviceSize             size{};
};
struct VkFormatProperties {
    VkFormatFeatureFlags     linearTilingFeatures{};
    VkFormatFeatureFlags     optimalTilingFeatures{};
    VkFormatFeatureFlags     bufferFeatures{};
};
struct VkImageFormatProperties {
    VkExtent3D               maxExtent{};
    uint32_t                 maxMipLevels{};
    uint32_t                 maxArrayLayers{};
    VkSampleCountFlags       sampleCounts{};
    VkDeviceSize             maxResourceSize{};
};
struct VkDescriptorBufferInfo {
    VkBuffer                 buffer{};
    VkDeviceSize             offset{};
    VkDeviceSize             range{};
};
struct VkDescriptorImageInfo {
    VkSampler         sampler{};
    VkImageView       imageView{};
    VkImageLayout     imageLayout{};
};
struct VkWriteDescriptorSet {
    VkStructureType   sType = VkStructureType::WriteDescriptorSet;
    const  void *             pNext{};
    VkDescriptorSet          dstSet{};
    uint32_t                 dstBinding{};
    uint32_t                 dstArrayElement{};
    uint32_t                 descriptorCount{};
    VkDescriptorType         descriptorType{};
    const  VkDescriptorImageInfo *  pImageInfo{};
    const  VkDescriptorBufferInfo *  pBufferInfo{};
    const  VkBufferView *     pTexelBufferView{};
};
struct VkCopyDescriptorSet {
    VkStructureType   sType = VkStructureType::CopyDescriptorSet;
    const  void *             pNext{};
    VkDescriptorSet          srcSet{};
    uint32_t                 srcBinding{};
    uint32_t                 srcArrayElement{};
    VkDescriptorSet          dstSet{};
    uint32_t                 dstBinding{};
    uint32_t                 dstArrayElement{};
    uint32_t                 descriptorCount{};
};
struct VkBufferCreateInfo {
    VkStructureType   sType = VkStructureType::BufferCreateInfo;
    const  void *             pNext{};
    VkBufferCreateFlags      flags{};
    VkDeviceSize             size{};
    VkBufferUsageFlags       usage{};
    VkSharingMode            sharingMode{};
    uint32_t                 queueFamilyIndexCount{};
    const  uint32_t *         pQueueFamilyIndices{};
};
struct VkBufferViewCreateInfo {
    VkStructureType   sType = VkStructureType::BufferViewCreateInfo;
    const  void *             pNext{};
    VkBufferViewCreateFlags flags{};
    VkBuffer                 buffer{};
    VkFormat                 format{};
    VkDeviceSize             offset{};
    VkDeviceSize             range{};
};
struct VkImageSubresource {
    VkImageAspectFlags       aspectMask{};
    uint32_t                 mipLevel{};
    uint32_t                 arrayLayer{};
};
struct VkImageSubresourceLayers {
    VkImageAspectFlags       aspectMask{};
    uint32_t                 mipLevel{};
    uint32_t                 baseArrayLayer{};
    uint32_t                 layerCount{};
};
struct VkImageSubresourceRange {
    VkImageAspectFlags       aspectMask{};
    uint32_t                 baseMipLevel{};
    uint32_t                 levelCount{};
    uint32_t                 baseArrayLayer{};
    uint32_t                 layerCount{};
};
struct VkMemoryBarrier {
    VkStructureType   sType = VkStructureType::MemoryBarrier;
    const  void *             pNext{};
    VkAccessFlags            srcAccessMask{};
    VkAccessFlags            dstAccessMask{};
};
struct VkBufferMemoryBarrier {
    VkStructureType   sType = VkStructureType::BufferMemoryBarrier;
    const  void *             pNext{};
    VkAccessFlags            srcAccessMask{};
    VkAccessFlags            dstAccessMask{};
    uint32_t                 srcQueueFamilyIndex{};
    uint32_t                 dstQueueFamilyIndex{};
    VkBuffer                 buffer{};
    VkDeviceSize             offset{};
    VkDeviceSize             size{};
};
struct VkImageMemoryBarrier {
    VkStructureType   sType = VkStructureType::ImageMemoryBarrier;
    const  void *             pNext{};
    VkAccessFlags            srcAccessMask{};
    VkAccessFlags            dstAccessMask{};
    VkImageLayout            oldLayout{};
    VkImageLayout            newLayout{};
    uint32_t                 srcQueueFamilyIndex{};
    uint32_t                 dstQueueFamilyIndex{};
    VkImage                  image{};
    VkImageSubresourceRange   subresourceRange{};
};
struct VkImageCreateInfo {
    VkStructureType   sType = VkStructureType::ImageCreateInfo;
    const  void *             pNext{};
    VkImageCreateFlags       flags{};
    VkImageType              imageType{};
    VkFormat                 format{};
    VkExtent3D               extent{};
    uint32_t                 mipLevels{};
    uint32_t                 arrayLayers{};
    VkSampleCountFlagBits    samples{};
    VkImageTiling            tiling{};
    VkImageUsageFlags        usage{};
    VkSharingMode            sharingMode{};
    uint32_t                 queueFamilyIndexCount{};
    const  uint32_t *         pQueueFamilyIndices{};
    VkImageLayout            initialLayout{};
};
struct VkSubresourceLayout {
    VkDeviceSize             offset{};
    VkDeviceSize             size{};
    VkDeviceSize             rowPitch{};
    VkDeviceSize             arrayPitch{};
    VkDeviceSize             depthPitch{};
};
struct VkImageViewCreateInfo {
    VkStructureType   sType = VkStructureType::ImageViewCreateInfo;
    const  void *             pNext{};
    VkImageViewCreateFlags   flags{};
    VkImage                  image{};
    VkImageViewType          viewType{};
    VkFormat                 format{};
    VkComponentMapping       components{};
    VkImageSubresourceRange   subresourceRange{};
};
struct VkBufferCopy {
    VkDeviceSize                         srcOffset{};
    VkDeviceSize                         dstOffset{};
    VkDeviceSize   size{};
};
struct VkSparseMemoryBind {
    VkDeviceSize             resourceOffset{};
    VkDeviceSize             size{};
    VkDeviceMemory           memory{};
    VkDeviceSize             memoryOffset{};
    VkSparseMemoryBindFlags flags{};
};
struct VkSparseImageMemoryBind {
    VkImageSubresource       subresource{};
    VkOffset3D               offset{};
    VkExtent3D               extent{};
    VkDeviceMemory           memory{};
    VkDeviceSize             memoryOffset{};
    VkSparseMemoryBindFlags flags{};
};
struct VkSparseBufferMemoryBindInfo {
    VkBuffer   buffer{};
    uint32_t                 bindCount{};
    const  VkSparseMemoryBind *  pBinds{};
};
struct VkSparseImageOpaqueMemoryBindInfo {
    VkImage   image{};
    uint32_t                 bindCount{};
    const  VkSparseMemoryBind *  pBinds{};
};
struct VkSparseImageMemoryBindInfo {
    VkImage   image{};
    uint32_t                 bindCount{};
    const  VkSparseImageMemoryBind *  pBinds{};
};
struct VkBindSparseInfo {
    VkStructureType   sType = VkStructureType::BindSparseInfo;
    const  void *             pNext{};
    uint32_t                 waitSemaphoreCount{};
    const  VkSemaphore *      pWaitSemaphores{};
    uint32_t                 bufferBindCount{};
    const  VkSparseBufferMemoryBindInfo *  pBufferBinds{};
    uint32_t                 imageOpaqueBindCount{};
    const  VkSparseImageOpaqueMemoryBindInfo *  pImageOpaqueBinds{};
    uint32_t                 imageBindCount{};
    const  VkSparseImageMemoryBindInfo *  pImageBinds{};
    uint32_t                 signalSemaphoreCount{};
    const  VkSemaphore *      pSignalSemaphores{};
};
struct VkImageCopy {
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D               srcOffset{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D               dstOffset{};
    VkExtent3D               extent{};
};
struct VkImageBlit {
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D               srcOffsets [2]{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D               dstOffsets [2]{};
};
struct VkBufferImageCopy {
    VkDeviceSize             bufferOffset{};
    uint32_t                 bufferRowLength{};
    uint32_t                 bufferImageHeight{};
    VkImageSubresourceLayers   imageSubresource{};
    VkOffset3D               imageOffset{};
    VkExtent3D               imageExtent{};
};
struct VkImageResolve {
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D               srcOffset{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D               dstOffset{};
    VkExtent3D               extent{};
};
struct VkShaderModuleCreateInfo {
    VkStructureType   sType = VkStructureType::ShaderModuleCreateInfo;
    const  void *             pNext{};
    VkShaderModuleCreateFlags   flags{};
    size_t                   codeSize{};
    const  uint32_t *             pCode{};
};
struct VkDescriptorSetLayoutBinding {
    uint32_t                 binding{};
    VkDescriptorType         descriptorType{};
    uint32_t   descriptorCount{};
    VkShaderStageFlags       stageFlags{};
    const  VkSampler *        pImmutableSamplers{};
};
struct VkDescriptorSetLayoutCreateInfo {
    VkStructureType   sType = VkStructureType::DescriptorSetLayoutCreateInfo;
    const  void *             pNext{};
    VkDescriptorSetLayoutCreateFlags      flags{};
    uint32_t                 bindingCount{};
    const  VkDescriptorSetLayoutBinding *  pBindings{};
};
struct VkDescriptorPoolSize {
    VkDescriptorType         type{};
    uint32_t                 descriptorCount{};
};
struct VkDescriptorPoolCreateInfo {
    VkStructureType   sType = VkStructureType::DescriptorPoolCreateInfo;
    const  void *             pNext{};
    VkDescriptorPoolCreateFlags    flags{};
    uint32_t                 maxSets{};
    uint32_t                 poolSizeCount{};
    const  VkDescriptorPoolSize *  pPoolSizes{};
};
struct VkDescriptorSetAllocateInfo {
    VkStructureType   sType = VkStructureType::DescriptorSetAllocateInfo;
    const  void *             pNext{};
    VkDescriptorPool         descriptorPool{};
    uint32_t                 descriptorSetCount{};
    const  VkDescriptorSetLayout *  pSetLayouts{};
};
struct VkSpecializationMapEntry {
    uint32_t                       constantID{};
    uint32_t                       offset{};
    size_t   size{};
};
struct VkSpecializationInfo {
    uint32_t                 mapEntryCount{};
    const  VkSpecializationMapEntry *  pMapEntries{};
    size_t                   dataSize{};
    const  void *             pData{};
};
struct VkPipelineShaderStageCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineShaderStageCreateInfo;
    const  void *             pNext{};
    VkPipelineShaderStageCreateFlags      flags{};
    VkShaderStageFlagBits    stage{};
    VkShaderModule           module{};
    const  char *             pName{};
    const  VkSpecializationInfo *  pSpecializationInfo{};
};
struct VkComputePipelineCreateInfo {
    VkStructureType   sType = VkStructureType::ComputePipelineCreateInfo;
    const  void *             pNext{};
    VkPipelineCreateFlags    flags{};
    VkPipelineShaderStageCreateInfo   stage{};
    VkPipelineLayout         layout{};
    VkPipeline        basePipelineHandle{};
    int32_t                  basePipelineIndex{};
};
struct VkVertexInputBindingDescription {
    uint32_t                 binding{};
    uint32_t                 stride{};
    VkVertexInputRate        inputRate{};
};
struct VkVertexInputAttributeDescription {
    uint32_t                 location{};
    uint32_t                 binding{};
    VkFormat                 format{};
    uint32_t                 offset{};
};
struct VkPipelineVertexInputStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineVertexInputStateCreateInfo;
    const  void *             pNext{};
    VkPipelineVertexInputStateCreateFlags      flags{};
    uint32_t                 vertexBindingDescriptionCount{};
    const  VkVertexInputBindingDescription *  pVertexBindingDescriptions{};
    uint32_t                 vertexAttributeDescriptionCount{};
    const  VkVertexInputAttributeDescription *  pVertexAttributeDescriptions{};
};
struct VkPipelineInputAssemblyStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineInputAssemblyStateCreateInfo;
    const  void *             pNext{};
    VkPipelineInputAssemblyStateCreateFlags      flags{};
    VkPrimitiveTopology      topology{};
    VkBool32                 primitiveRestartEnable{};
};
struct VkPipelineTessellationStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineTessellationStateCreateInfo;
    const  void *             pNext{};
    VkPipelineTessellationStateCreateFlags      flags{};
    uint32_t                 patchControlPoints{};
};
struct VkPipelineViewportStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineViewportStateCreateInfo;
    const  void *             pNext{};
    VkPipelineViewportStateCreateFlags      flags{};
    uint32_t                 viewportCount{};
    const  VkViewport *       pViewports{};
    uint32_t                 scissorCount{};
    const  VkRect2D *         pScissors{};
};
struct VkPipelineRasterizationStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineRasterizationStateCreateInfo;
    const  void *  pNext{};
    VkPipelineRasterizationStateCreateFlags      flags{};
    VkBool32                 depthClampEnable{};
    VkBool32                 rasterizerDiscardEnable{};
    VkPolygonMode            polygonMode{};
    VkCullModeFlags          cullMode{};
    VkFrontFace              frontFace{};
    VkBool32                 depthBiasEnable{};
    float                    depthBiasConstantFactor{};
    float                    depthBiasClamp{};
    float                    depthBiasSlopeFactor{};
    float                    lineWidth{};
};
struct VkPipelineMultisampleStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineMultisampleStateCreateInfo;
    const  void *             pNext{};
    VkPipelineMultisampleStateCreateFlags      flags{};
    VkSampleCountFlagBits    rasterizationSamples{};
    VkBool32                 sampleShadingEnable{};
    float                    minSampleShading{};
    const  VkSampleMask *     pSampleMask{};
    VkBool32                 alphaToCoverageEnable{};
    VkBool32                 alphaToOneEnable{};
};
struct VkPipelineColorBlendAttachmentState {
    VkBool32                 blendEnable{};
    VkBlendFactor            srcColorBlendFactor{};
    VkBlendFactor            dstColorBlendFactor{};
    VkBlendOp                colorBlendOp{};
    VkBlendFactor            srcAlphaBlendFactor{};
    VkBlendFactor            dstAlphaBlendFactor{};
    VkBlendOp                alphaBlendOp{};
    VkColorComponentFlags    colorWriteMask{};
};
struct VkPipelineColorBlendStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineColorBlendStateCreateInfo;
    const  void *             pNext{};
    VkPipelineColorBlendStateCreateFlags      flags{};
    VkBool32                 logicOpEnable{};
    VkLogicOp                logicOp{};
    uint32_t                 attachmentCount{};
    const  VkPipelineColorBlendAttachmentState *  pAttachments{};
    float                    blendConstants [4]{};
};
struct VkPipelineDynamicStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineDynamicStateCreateInfo;
    const  void *             pNext{};
    VkPipelineDynamicStateCreateFlags      flags{};
    uint32_t                 dynamicStateCount{};
    const  VkDynamicState *   pDynamicStates{};
};
struct VkStencilOpState {
    VkStencilOp              failOp{};
    VkStencilOp              passOp{};
    VkStencilOp              depthFailOp{};
    VkCompareOp              compareOp{};
    uint32_t                 compareMask{};
    uint32_t                 writeMask{};
    uint32_t                 reference{};
};
struct VkPipelineDepthStencilStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineDepthStencilStateCreateInfo;
    const  void *             pNext{};
    VkPipelineDepthStencilStateCreateFlags      flags{};
    VkBool32                 depthTestEnable{};
    VkBool32                 depthWriteEnable{};
    VkCompareOp              depthCompareOp{};
    VkBool32                 depthBoundsTestEnable{};
    VkBool32                 stencilTestEnable{};
    VkStencilOpState         front{};
    VkStencilOpState         back{};
    float                    minDepthBounds{};
    float                    maxDepthBounds{};
};
struct VkGraphicsPipelineCreateInfo {
    VkStructureType   sType = VkStructureType::GraphicsPipelineCreateInfo;
    const  void *             pNext{};
    VkPipelineCreateFlags    flags{};
    uint32_t                 stageCount{};
    const  VkPipelineShaderStageCreateInfo *  pStages{};
    const  VkPipelineVertexInputStateCreateInfo *  pVertexInputState{};
    const  VkPipelineInputAssemblyStateCreateInfo *  pInputAssemblyState{};
    const  VkPipelineTessellationStateCreateInfo *  pTessellationState{};
    const  VkPipelineViewportStateCreateInfo *  pViewportState{};
    const  VkPipelineRasterizationStateCreateInfo *  pRasterizationState{};
    const  VkPipelineMultisampleStateCreateInfo *  pMultisampleState{};
    const  VkPipelineDepthStencilStateCreateInfo *  pDepthStencilState{};
    const  VkPipelineColorBlendStateCreateInfo *  pColorBlendState{};
    const  VkPipelineDynamicStateCreateInfo *  pDynamicState{};
    VkPipelineLayout         layout{};
    VkRenderPass             renderPass{};
    uint32_t                 subpass{};
    VkPipeline        basePipelineHandle{};
    int32_t                  basePipelineIndex{};
};
struct VkPipelineCacheCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineCacheCreateInfo;
    const  void *             pNext{};
    VkPipelineCacheCreateFlags      flags{};
    size_t                   initialDataSize{};
    const  void *             pInitialData{};
};
struct VkPushConstantRange {
    VkShaderStageFlags       stageFlags{};
    uint32_t                 offset{};
    uint32_t                 size{};
};
struct VkPipelineLayoutCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineLayoutCreateInfo;
    const  void *             pNext{};
    VkPipelineLayoutCreateFlags      flags{};
    uint32_t                 setLayoutCount{};
    const  VkDescriptorSetLayout *  pSetLayouts{};
    uint32_t                 pushConstantRangeCount{};
    const  VkPushConstantRange *  pPushConstantRanges{};
};
struct VkSamplerCreateInfo {
    VkStructureType   sType = VkStructureType::SamplerCreateInfo;
    const  void *             pNext{};
    VkSamplerCreateFlags     flags{};
    VkFilter                 magFilter{};
    VkFilter                 minFilter{};
    VkSamplerMipmapMode      mipmapMode{};
    VkSamplerAddressMode     addressModeU{};
    VkSamplerAddressMode     addressModeV{};
    VkSamplerAddressMode     addressModeW{};
    float                    mipLodBias{};
    VkBool32                 anisotropyEnable{};
    float                    maxAnisotropy{};
    VkBool32                 compareEnable{};
    VkCompareOp              compareOp{};
    float                    minLod{};
    float                    maxLod{};
    VkBorderColor            borderColor{};
    VkBool32                 unnormalizedCoordinates{};
};
struct VkCommandPoolCreateInfo {
    VkStructureType   sType = VkStructureType::CommandPoolCreateInfo;
    const  void *             pNext{};
    VkCommandPoolCreateFlags     flags{};
    uint32_t                 queueFamilyIndex{};
};
struct VkCommandBufferAllocateInfo {
    VkStructureType   sType = VkStructureType::CommandBufferAllocateInfo;
    const  void *             pNext{};
    VkCommandPool            commandPool{};
    VkCommandBufferLevel     level{};
    uint32_t                 commandBufferCount{};
};
struct VkCommandBufferInheritanceInfo {
    VkStructureType   sType = VkStructureType::CommandBufferInheritanceInfo;
    const  void *             pNext{};
    VkRenderPass      renderPass{};
    uint32_t                 subpass{};
    VkFramebuffer     framebuffer{};
    VkBool32                 occlusionQueryEnable{};
    VkQueryControlFlags      queryFlags{};
    VkQueryPipelineStatisticFlags   pipelineStatistics{};
};
struct VkCommandBufferBeginInfo {
    VkStructureType   sType = VkStructureType::CommandBufferBeginInfo;
    const  void *             pNext{};
    VkCommandBufferUsageFlags    flags{};
    const  VkCommandBufferInheritanceInfo *        pInheritanceInfo{};
};
struct VkClearDepthStencilValue {
    float                    depth{};
    uint32_t                 stencil{};
};
union VkClearColorValue {
    float                    float32 [4];
    int32_t                  int32 [4];
    uint32_t                 uint32 [4];
};
union VkClearValue {
    VkClearColorValue        color;
    VkClearDepthStencilValue   depthStencil;
};
struct VkRenderPassBeginInfo {
    VkStructureType   sType = VkStructureType::RenderPassBeginInfo;
    const  void *             pNext{};
    VkRenderPass             renderPass{};
    VkFramebuffer            framebuffer{};
    VkRect2D                 renderArea{};
    uint32_t                 clearValueCount{};
    const  VkClearValue *     pClearValues{};
};
struct VkClearAttachment {
    VkImageAspectFlags       aspectMask{};
    uint32_t                 colorAttachment{};
    VkClearValue             clearValue{};
};
struct VkAttachmentDescription {
    VkAttachmentDescriptionFlags   flags{};
    VkFormat                 format{};
    VkSampleCountFlagBits    samples{};
    VkAttachmentLoadOp       loadOp{};
    VkAttachmentStoreOp      storeOp{};
    VkAttachmentLoadOp       stencilLoadOp{};
    VkAttachmentStoreOp      stencilStoreOp{};
    VkImageLayout            initialLayout{};
    VkImageLayout            finalLayout{};
};
struct VkAttachmentReference {
    uint32_t                 attachment{};
    VkImageLayout            layout{};
};
struct VkSubpassDescription {
    VkSubpassDescriptionFlags   flags{};
    VkPipelineBindPoint      pipelineBindPoint{};
    uint32_t                 inputAttachmentCount{};
    const  VkAttachmentReference *  pInputAttachments{};
    uint32_t                 colorAttachmentCount{};
    const  VkAttachmentReference *  pColorAttachments{};
    const  VkAttachmentReference *  pResolveAttachments{};
    const  VkAttachmentReference *  pDepthStencilAttachment{};
    uint32_t                 preserveAttachmentCount{};
    const  uint32_t *  pPreserveAttachments{};
};
struct VkSubpassDependency {
    uint32_t                 srcSubpass{};
    uint32_t                 dstSubpass{};
    VkPipelineStageFlags     srcStageMask{};
    VkPipelineStageFlags     dstStageMask{};
    VkAccessFlags            srcAccessMask{};
    VkAccessFlags            dstAccessMask{};
    VkDependencyFlags        dependencyFlags{};
};
struct VkRenderPassCreateInfo {
    VkStructureType   sType = VkStructureType::RenderPassCreateInfo;
    const  void *             pNext{};
    VkRenderPassCreateFlags   flags{};
    uint32_t     attachmentCount{};
    const  VkAttachmentDescription *  pAttachments{};
    uint32_t                 subpassCount{};
    const  VkSubpassDescription *  pSubpasses{};
    uint32_t         dependencyCount{};
    const  VkSubpassDependency *  pDependencies{};
};
struct VkEventCreateInfo {
    VkStructureType   sType = VkStructureType::EventCreateInfo;
    const  void *             pNext{};
    VkEventCreateFlags       flags{};
};
struct VkFenceCreateInfo {
    VkStructureType   sType = VkStructureType::FenceCreateInfo;
    const  void *             pNext{};
    VkFenceCreateFlags       flags{};
};
struct VkSemaphoreCreateInfo {
    VkStructureType   sType = VkStructureType::SemaphoreCreateInfo;
    const  void *             pNext{};
    VkSemaphoreCreateFlags   flags{};
};
struct VkQueryPoolCreateInfo {
    VkStructureType   sType = VkStructureType::QueryPoolCreateInfo;
    const  void *             pNext{};
    VkQueryPoolCreateFlags   flags{};
    VkQueryType              queryType{};
    uint32_t                 queryCount{};
    VkQueryPipelineStatisticFlags   pipelineStatistics{};
};
struct VkFramebufferCreateInfo {
    VkStructureType   sType = VkStructureType::FramebufferCreateInfo;
    const  void *             pNext{};
    VkFramebufferCreateFlags      flags{};
    VkRenderPass             renderPass{};
    uint32_t                 attachmentCount{};
    const  VkImageView *      pAttachments{};
    uint32_t                 width{};
    uint32_t                 height{};
    uint32_t                 layers{};
};
struct VkDrawIndirectCommand {
    uint32_t                         vertexCount{};
    uint32_t                         instanceCount{};
    uint32_t                         firstVertex{};
    uint32_t   firstInstance{};
};
struct VkDrawIndexedIndirectCommand {
    uint32_t                         indexCount{};
    uint32_t                         instanceCount{};
    uint32_t                         firstIndex{};
    int32_t                          vertexOffset{};
    uint32_t   firstInstance{};
};
struct VkDispatchIndirectCommand {
    uint32_t   x{};
    uint32_t   y{};
    uint32_t   z{};
};
struct VkSubmitInfo {
    VkStructureType   sType = VkStructureType::SubmitInfo;
    const  void *  pNext{};
    uint32_t         waitSemaphoreCount{};
    const  VkSemaphore *      pWaitSemaphores{};
    const  VkPipelineStageFlags *            pWaitDstStageMask{};
    uint32_t         commandBufferCount{};
    const  VkCommandBuffer *      pCommandBuffers{};
    uint32_t         signalSemaphoreCount{};
    const  VkSemaphore *      pSignalSemaphores{};
};
struct VkDisplayPropertiesKHR {
    VkDisplayKHR                       display{};
    const  char *                       displayName{};
    VkExtent2D                         physicalDimensions{};
    VkExtent2D                         physicalResolution{};
    VkSurfaceTransformFlagsKHR         supportedTransforms{};
    VkBool32                           planeReorderPossible{};
    VkBool32                           persistentContent{};
};
struct VkDisplayPlanePropertiesKHR {
    VkDisplayKHR                       currentDisplay{};
    uint32_t                           currentStackIndex{};
};
struct VkDisplayModeParametersKHR {
    VkExtent2D                         visibleRegion{};
    uint32_t     refreshRate{};
};
struct VkDisplayModePropertiesKHR {
    VkDisplayModeKHR                   displayMode{};
    VkDisplayModeParametersKHR         parameters{};
};
struct VkDisplayModeCreateInfoKHR {
    VkStructureType   sType = VkStructureType::DisplayModeCreateInfoKHR;
    const  void *                       pNext{};
    VkDisplayModeCreateFlagsKHR        flags{};
    VkDisplayModeParametersKHR         parameters{};
};
struct VkDisplayPlaneCapabilitiesKHR {
    VkDisplayPlaneAlphaFlagsKHR        supportedAlpha{};
    VkOffset2D                         minSrcPosition{};
    VkOffset2D                         maxSrcPosition{};
    VkExtent2D                         minSrcExtent{};
    VkExtent2D                         maxSrcExtent{};
    VkOffset2D                         minDstPosition{};
    VkOffset2D                         maxDstPosition{};
    VkExtent2D                         minDstExtent{};
    VkExtent2D                         maxDstExtent{};
};
struct VkDisplaySurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::DisplaySurfaceCreateInfoKHR;
    const  void *                       pNext{};
    VkDisplaySurfaceCreateFlagsKHR     flags{};
    VkDisplayModeKHR                   displayMode{};
    uint32_t                           planeIndex{};
    uint32_t                           planeStackIndex{};
    VkSurfaceTransformFlagBitsKHR      transform{};
    float                              globalAlpha{};
    VkDisplayPlaneAlphaFlagBitsKHR     alphaMode{};
    VkExtent2D                         imageExtent{};
};
struct VkDisplayPresentInfoKHR {
    VkStructureType   sType = VkStructureType::DisplayPresentInfoKHR;
    const  void *                       pNext{};
    VkRect2D                           srcRect{};
    VkRect2D                           dstRect{};
    VkBool32                           persistent{};
};
struct VkSurfaceCapabilitiesKHR {
    uint32_t                           minImageCount{};
    uint32_t                           maxImageCount{};
    VkExtent2D                         currentExtent{};
    VkExtent2D                         minImageExtent{};
    VkExtent2D                         maxImageExtent{};
    uint32_t                           maxImageArrayLayers{};
    VkSurfaceTransformFlagsKHR         supportedTransforms{};
    VkSurfaceTransformFlagBitsKHR      currentTransform{};
    VkCompositeAlphaFlagsKHR           supportedCompositeAlpha{};
    VkImageUsageFlags                  supportedUsageFlags{};
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkAndroidSurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::AndroidSurfaceCreateInfoKHR;
    const  void *                                     pNext{};
    VkAndroidSurfaceCreateFlagsKHR   flags{};
    struct  ANativeWindow *     window{};
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_VI_NN)
struct VkViSurfaceCreateInfoNN {
    VkStructureType   sType = VkStructureType::ViSurfaceCreateInfoNN;
    const  void *                       pNext{};
    VkViSurfaceCreateFlagsNN     flags{};
    void *                             window{};
};
#endif // defined(VK_USE_PLATFORM_VI_NN)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
struct VkWaylandSurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::WaylandSurfaceCreateInfoKHR;
    const  void *                       pNext{};
    VkWaylandSurfaceCreateFlagsKHR     flags{};
    struct  wl_display *                display{};
    struct  wl_surface *                surface{};
};
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkWin32SurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::Win32SurfaceCreateInfoKHR;
    const  void *                       pNext{};
    VkWin32SurfaceCreateFlagsKHR     flags{};
    HINSTANCE                          hinstance{};
    HWND                               hwnd{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_XLIB_KHR)
struct VkXlibSurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::XlibSurfaceCreateInfoKHR;
    const  void *                       pNext{};
    VkXlibSurfaceCreateFlagsKHR     flags{};
    Display *                          dpy{};
    Window                             window{};
};
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
struct VkXcbSurfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::XcbSurfaceCreateInfoKHR;
    const  void *                       pNext{};
    VkXcbSurfaceCreateFlagsKHR     flags{};
    xcb_connection_t *                 connection{};
    xcb_window_t                       window{};
};
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
struct VkDirectFBSurfaceCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DirectfbSurfaceCreateInfoEXT;
    const  void *                       pNext{};
    VkDirectFBSurfaceCreateFlagsEXT     flags{};
    IDirectFB *                        dfb{};
    IDirectFBSurface *                 surface{};
};
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct VkImagePipeSurfaceCreateInfoFUCHSIA {
    VkStructureType   sType = VkStructureType::ImagepipeSurfaceCreateInfoFUCHSIA;
    const  void *                       pNext{};
    VkImagePipeSurfaceCreateFlagsFUCHSIA     flags{};
    zx_handle_t                        imagePipeHandle{};
};
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_GGP)
struct VkStreamDescriptorSurfaceCreateInfoGGP {
    VkStructureType   sType = VkStructureType::StreamDescriptorSurfaceCreateInfoGGP;
    const  void *                       pNext{};
    VkStreamDescriptorSurfaceCreateFlagsGGP   flags{};
    GgpStreamDescriptor                streamDescriptor{};
};
#endif // defined(VK_USE_PLATFORM_GGP)
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
struct VkScreenSurfaceCreateInfoQNX {
    VkStructureType   sType = VkStructureType::ScreenSurfaceCreateInfoQNX;
    const  void *                       pNext{};
    VkScreenSurfaceCreateFlagsQNX      flags{};
    struct  _screen_context *     context{};
    struct  _screen_window *      window{};
};
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
struct VkSurfaceFormatKHR {
    VkFormat                           format{};
    VkColorSpaceKHR                    colorSpace{};
};
struct VkSwapchainCreateInfoKHR {
    VkStructureType   sType = VkStructureType::SwapchainCreateInfoKHR;
    const  void *                       pNext{};
    VkSwapchainCreateFlagsKHR          flags{};
    VkSurfaceKHR                       surface{};
    uint32_t                           minImageCount{};
    VkFormat                           imageFormat{};
    VkColorSpaceKHR                    imageColorSpace{};
    VkExtent2D                         imageExtent{};
    uint32_t                           imageArrayLayers{};
    VkImageUsageFlags                  imageUsage{};
    VkSharingMode                      imageSharingMode{};
    uint32_t           queueFamilyIndexCount{};
    const  uint32_t *                   pQueueFamilyIndices{};
    VkSurfaceTransformFlagBitsKHR      preTransform{};
    VkCompositeAlphaFlagBitsKHR        compositeAlpha{};
    VkPresentModeKHR                   presentMode{};
    VkBool32                           clipped{};
    VkSwapchainKHR     oldSwapchain{};
};
struct VkPresentInfoKHR {
    VkStructureType   sType = VkStructureType::PresentInfoKHR;
    const  void *   pNext{};
    uint32_t           waitSemaphoreCount{};
    const  VkSemaphore *  pWaitSemaphores{};
    uint32_t                           swapchainCount{};
    const  VkSwapchainKHR *  pSwapchains{};
    const  uint32_t *  pImageIndices{};
    VkResult *  pResults{};
};
struct VkDebugReportCallbackCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DebugReportCallbackCreateInfoEXT;
    const  void *                       pNext{};
    VkDebugReportFlagsEXT              flags{};
    PFN_vkDebugReportCallbackEXT       pfnCallback{};
    void *             pUserData{};
};
struct VkValidationFlagsEXT {
    VkStructureType                    sType = VkStructureType::ValidationFlagsEXT;
    const  void *                       pNext{};
    uint32_t                           disabledValidationCheckCount{};
    const  VkValidationCheckEXT *  pDisabledValidationChecks{};
};
struct VkValidationFeaturesEXT {
    VkStructureType    sType = VkStructureType::ValidationFeaturesEXT;
    const  void *                       pNext{};
    uint32_t                           enabledValidationFeatureCount{};
    const  VkValidationFeatureEnableEXT *  pEnabledValidationFeatures{};
    uint32_t                           disabledValidationFeatureCount{};
    const  VkValidationFeatureDisableEXT *  pDisabledValidationFeatures{};
};
struct VkPipelineRasterizationStateRasterizationOrderAMD {
    VkStructureType   sType = VkStructureType::PipelineRasterizationStateRasterizationOrderAMD;
    const  void *                       pNext{};
    VkRasterizationOrderAMD            rasterizationOrder{};
};
struct VkDebugMarkerObjectNameInfoEXT {
    VkStructureType   sType = VkStructureType::DebugMarkerObjectNameInfoEXT;
    const  void *                       pNext{};
    VkDebugReportObjectTypeEXT         objectType{};
    uint64_t                           object{};
    const  char *  pObjectName{};
};
struct VkDebugMarkerObjectTagInfoEXT {
    VkStructureType   sType = VkStructureType::DebugMarkerObjectTagInfoEXT;
    const  void *                       pNext{};
    VkDebugReportObjectTypeEXT         objectType{};
    uint64_t                           object{};
    uint64_t                           tagName{};
    size_t                             tagSize{};
    const  void *         pTag{};
};
struct VkDebugMarkerMarkerInfoEXT {
    VkStructureType   sType = VkStructureType::DebugMarkerMarkerInfoEXT;
    const  void *                       pNext{};
    const  char *  pMarkerName{};
    float              color [4]{};
};
struct VkDedicatedAllocationImageCreateInfoNV {
    VkStructureType   sType = VkStructureType::DedicatedAllocationImageCreateInfoNV;
    const  void *                       pNext{};
    VkBool32                           dedicatedAllocation{};
};
struct VkDedicatedAllocationBufferCreateInfoNV {
    VkStructureType   sType = VkStructureType::DedicatedAllocationBufferCreateInfoNV;
    const  void *                       pNext{};
    VkBool32                           dedicatedAllocation{};
};
struct VkDedicatedAllocationMemoryAllocateInfoNV {
    VkStructureType   sType = VkStructureType::DedicatedAllocationMemoryAllocateInfoNV;
    const  void *                       pNext{};
    VkImage            image{};
    VkBuffer           buffer{};
};
struct VkExternalImageFormatPropertiesNV {
    VkImageFormatProperties            imageFormatProperties{};
    VkExternalMemoryFeatureFlagsNV     externalMemoryFeatures{};
    VkExternalMemoryHandleTypeFlagsNV   exportFromImportedHandleTypes{};
    VkExternalMemoryHandleTypeFlagsNV   compatibleHandleTypes{};
};
struct VkExternalMemoryImageCreateInfoNV {
    VkStructureType   sType = VkStructureType::ExternalMemoryImageCreateInfoNV;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagsNV   handleTypes{};
};
struct VkExportMemoryAllocateInfoNV {
    VkStructureType   sType = VkStructureType::ExportMemoryAllocateInfoNV;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagsNV   handleTypes{};
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryWin32HandleInfoNV {
    VkStructureType   sType = VkStructureType::ImportMemoryWin32HandleInfoNV;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagsNV   handleType{};
    HANDLE                             handle{};
};
struct VkExportMemoryWin32HandleInfoNV {
    VkStructureType   sType = VkStructureType::ExportMemoryWin32HandleInfoNV;
    const  void *                       pNext{};
    const  SECURITY_ATTRIBUTES *        pAttributes{};
    DWORD                              dwAccess{};
};
struct VkWin32KeyedMutexAcquireReleaseInfoNV {
    VkStructureType   sType = VkStructureType::Win32KeyedMutexAcquireReleaseInfoNV;
    const  void *                       pNext{};
    uint32_t                           acquireCount{};
    const  VkDeviceMemory *             pAcquireSyncs{};
    const  uint64_t *                   pAcquireKeys{};
    const  uint32_t *                   pAcquireTimeoutMilliseconds{};
    uint32_t                           releaseCount{};
    const  VkDeviceMemory *             pReleaseSyncs{};
    const  uint64_t *                   pReleaseKeys{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDeviceDeviceGeneratedCommandsFeaturesNV {
    VkStructureType sType = VkStructureType::PhysicalDeviceDeviceGeneratedCommandsFeaturesNV;
    void *     pNext{};
    VkBool32                         deviceGeneratedCommands{};
};
struct VkDevicePrivateDataCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DevicePrivateDataCreateInfoEXT;
    const  void *                             pNext{};
    uint32_t                                 privateDataSlotRequestCount{};
};
struct VkPrivateDataSlotCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PrivateDataSlotCreateInfoEXT;
    const  void *                             pNext{};
    VkPrivateDataSlotCreateFlagsEXT          flags{};
};
struct VkPhysicalDevicePrivateDataFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDevicePrivateDataFeaturesEXT;
    void *                                   pNext{};
    VkBool32                                 privateData{};
};
struct VkPhysicalDeviceDeviceGeneratedCommandsPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDeviceGeneratedCommandsPropertiesNV;
    void *     pNext{};
    uint32_t           maxGraphicsShaderGroupCount{};
    uint32_t           maxIndirectSequenceCount{};
    uint32_t           maxIndirectCommandsTokenCount{};
    uint32_t           maxIndirectCommandsStreamCount{};
    uint32_t           maxIndirectCommandsTokenOffset{};
    uint32_t           maxIndirectCommandsStreamStride{};
    uint32_t           minSequencesCountBufferOffsetAlignment{};
    uint32_t           minSequencesIndexBufferOffsetAlignment{};
    uint32_t           minIndirectCommandsBufferOffsetAlignment{};
};
struct VkGraphicsShaderGroupCreateInfoNV {
    VkStructureType   sType = VkStructureType::GraphicsShaderGroupCreateInfoNV;
    const  void *                                                 pNext{};
    uint32_t                                                     stageCount{};
    const  VkPipelineShaderStageCreateInfo *     pStages{};
    const  VkPipelineVertexInputStateCreateInfo *                 pVertexInputState{};
    const  VkPipelineTessellationStateCreateInfo *                pTessellationState{};
};
struct VkGraphicsPipelineShaderGroupsCreateInfoNV {
    VkStructureType   sType = VkStructureType::GraphicsPipelineShaderGroupsCreateInfoNV;
    const  void *                                                 pNext{};
    uint32_t                                                     groupCount{};
    const  VkGraphicsShaderGroupCreateInfoNV *   pGroups{};
    uint32_t                                     pipelineCount{};
    const  VkPipeline *                       pPipelines{};
};
struct VkBindShaderGroupIndirectCommandNV {
    uint32_t           groupIndex{};
};
struct VkBindIndexBufferIndirectCommandNV {
    VkDeviceAddress    bufferAddress{};
    uint32_t           size{};
    VkIndexType        indexType{};
};
struct VkBindVertexBufferIndirectCommandNV {
    VkDeviceAddress    bufferAddress{};
    uint32_t           size{};
    uint32_t           stride{};
};
struct VkSetStateFlagsIndirectCommandNV {
    uint32_t            data{};
};
struct VkIndirectCommandsStreamNV {
    VkBuffer        buffer{};
    VkDeviceSize    offset{};
};
struct VkIndirectCommandsLayoutTokenNV {
    VkStructureType   sType = VkStructureType::IndirectCommandsLayoutTokenNV;
    const  void *                     pNext{};
    VkIndirectCommandsTokenTypeNV    tokenType{};
    uint32_t                         stream{};
    uint32_t                         offset{};
    uint32_t                                  vertexBindingUnit{};
    VkBool32                                  vertexDynamicStride{};
    VkPipelineLayout          pushconstantPipelineLayout{};
    VkShaderStageFlags        pushconstantShaderStageFlags{};
    uint32_t                                  pushconstantOffset{};
    uint32_t                                  pushconstantSize{};
    VkIndirectStateFlagsNV    indirectStateFlags{};
    uint32_t                  indexTypeCount{};
    const  VkIndexType *  pIndexTypes{};
    const  uint32_t *     pIndexTypeValues{};
};
struct VkIndirectCommandsLayoutCreateInfoNV {
    VkStructureType   sType = VkStructureType::IndirectCommandsLayoutCreateInfoNV;
    const  void *                              pNext{};
    VkIndirectCommandsLayoutUsageFlagsNV      flags{};
    VkPipelineBindPoint                       pipelineBindPoint{};
    uint32_t                                  tokenCount{};
    const  VkIndirectCommandsLayoutTokenNV *   pTokens{};
    uint32_t                                  streamCount{};
    const  uint32_t *        pStreamStrides{};
};
struct VkGeneratedCommandsInfoNV {
    VkStructureType   sType = VkStructureType::GeneratedCommandsInfoNV;
    const  void *                         pNext{};
    VkPipelineBindPoint                  pipelineBindPoint{};
    VkPipeline                           pipeline{};
    VkIndirectCommandsLayoutNV           indirectCommandsLayout{};
    uint32_t                             streamCount{};
    const  VkIndirectCommandsStreamNV *   pStreams{};
    uint32_t                             sequencesCount{};
    VkBuffer                             preprocessBuffer{};
    VkDeviceSize                         preprocessOffset{};
    VkDeviceSize                         preprocessSize{};
    VkBuffer             sequencesCountBuffer{};
    VkDeviceSize                         sequencesCountOffset{};
    VkBuffer             sequencesIndexBuffer{};
    VkDeviceSize                         sequencesIndexOffset{};
};
struct VkGeneratedCommandsMemoryRequirementsInfoNV {
    VkStructureType   sType = VkStructureType::GeneratedCommandsMemoryRequirementsInfoNV;
    const  void *                  pNext{};
    VkPipelineBindPoint           pipelineBindPoint{};
    VkPipeline                    pipeline{};
    VkIndirectCommandsLayoutNV    indirectCommandsLayout{};
    uint32_t                      maxSequencesCount{};
};
struct VkPhysicalDeviceFeatures2 {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFeatures2;
    void *                             pNext{};
    VkPhysicalDeviceFeatures           features{};
};
using VkPhysicalDeviceFeatures2KHR = VkPhysicalDeviceFeatures2;
struct VkPhysicalDeviceProperties2 {
    VkStructureType   sType = VkStructureType::PhysicalDeviceProperties2;
    void *                             pNext{};
    VkPhysicalDeviceProperties         properties{};
};
using VkPhysicalDeviceProperties2KHR = VkPhysicalDeviceProperties2;
struct VkFormatProperties2 {
    VkStructureType   sType = VkStructureType::FormatProperties2;
    void *                             pNext{};
    VkFormatProperties                 formatProperties{};
};
using VkFormatProperties2KHR = VkFormatProperties2;
struct VkImageFormatProperties2 {
    VkStructureType   sType = VkStructureType::ImageFormatProperties2;
    void *  pNext{};
    VkImageFormatProperties            imageFormatProperties{};
};
using VkImageFormatProperties2KHR = VkImageFormatProperties2;
struct VkPhysicalDeviceImageFormatInfo2 {
    VkStructureType   sType = VkStructureType::PhysicalDeviceImageFormatInfo2;
    const  void *  pNext{};
    VkFormat                           format{};
    VkImageType                        type{};
    VkImageTiling                      tiling{};
    VkImageUsageFlags                  usage{};
    VkImageCreateFlags   flags{};
};
using VkPhysicalDeviceImageFormatInfo2KHR = VkPhysicalDeviceImageFormatInfo2;
struct VkQueueFamilyProperties2 {
    VkStructureType   sType = VkStructureType::QueueFamilyProperties2;
    void *                             pNext{};
    VkQueueFamilyProperties            queueFamilyProperties{};
};
using VkQueueFamilyProperties2KHR = VkQueueFamilyProperties2;
struct VkPhysicalDeviceMemoryProperties2 {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMemoryProperties2;
    void *                             pNext{};
    VkPhysicalDeviceMemoryProperties   memoryProperties{};
};
using VkPhysicalDeviceMemoryProperties2KHR = VkPhysicalDeviceMemoryProperties2;
struct VkSparseImageFormatProperties2 {
    VkStructureType   sType = VkStructureType::SparseImageFormatProperties2;
    void *                             pNext{};
    VkSparseImageFormatProperties      properties{};
};
using VkSparseImageFormatProperties2KHR = VkSparseImageFormatProperties2;
struct VkPhysicalDeviceSparseImageFormatInfo2 {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSparseImageFormatInfo2;
    const  void *                       pNext{};
    VkFormat                           format{};
    VkImageType                        type{};
    VkSampleCountFlagBits              samples{};
    VkImageUsageFlags                  usage{};
    VkImageTiling                      tiling{};
};
using VkPhysicalDeviceSparseImageFormatInfo2KHR = VkPhysicalDeviceSparseImageFormatInfo2;
struct VkPhysicalDevicePushDescriptorPropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePushDescriptorPropertiesKHR;
    void *                             pNext{};
    uint32_t                           maxPushDescriptors{};
};
struct VkConformanceVersion {
    uint8_t                            major{};
    uint8_t                            minor{};
    uint8_t                            subminor{};
    uint8_t                            patch{};
};
using VkConformanceVersionKHR = VkConformanceVersion;
struct VkPhysicalDeviceDriverProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDriverProperties;
    void *                             pNext{};
    VkDriverId                         driverID{};
    char                               driverName [ VK_MAX_DRIVER_NAME_SIZE ]{};
    char                               driverInfo [ VK_MAX_DRIVER_INFO_SIZE ]{};
    VkConformanceVersion               conformanceVersion{};
};
using VkPhysicalDeviceDriverPropertiesKHR = VkPhysicalDeviceDriverProperties;
struct VkRectLayerKHR {
    VkOffset2D                         offset{};
    VkExtent2D   extent{};
    uint32_t                           layer{};
};
struct VkPresentRegionKHR {
    uint32_t           rectangleCount{};
    const  VkRectLayerKHR *    pRectangles{};
};
struct VkPresentRegionsKHR {
    VkStructureType   sType = VkStructureType::PresentRegionsKHR;
    const  void *                       pNext{};
    uint32_t                           swapchainCount{};
    const  VkPresentRegionKHR *    pRegions{};
};
struct VkPhysicalDeviceVariablePointersFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceVariablePointersFeatures;
    void *                             pNext{};
    VkBool32                           variablePointersStorageBuffer{};
    VkBool32                           variablePointers{};
};
using VkPhysicalDeviceVariablePointersFeaturesKHR = VkPhysicalDeviceVariablePointersFeatures;
using VkPhysicalDeviceVariablePointerFeaturesKHR = VkPhysicalDeviceVariablePointersFeatures;
using VkPhysicalDeviceVariablePointerFeatures = VkPhysicalDeviceVariablePointersFeatures;
struct VkExternalMemoryProperties {
    VkExternalMemoryFeatureFlags    externalMemoryFeatures{};
    VkExternalMemoryHandleTypeFlags   exportFromImportedHandleTypes{};
    VkExternalMemoryHandleTypeFlags   compatibleHandleTypes{};
};
using VkExternalMemoryPropertiesKHR = VkExternalMemoryProperties;
struct VkPhysicalDeviceExternalImageFormatInfo {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExternalImageFormatInfo;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
};
using VkPhysicalDeviceExternalImageFormatInfoKHR = VkPhysicalDeviceExternalImageFormatInfo;
struct VkExternalImageFormatProperties {
    VkStructureType   sType = VkStructureType::ExternalImageFormatProperties;
    void *                             pNext{};
    VkExternalMemoryProperties   externalMemoryProperties{};
};
using VkExternalImageFormatPropertiesKHR = VkExternalImageFormatProperties;
struct VkPhysicalDeviceExternalBufferInfo {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExternalBufferInfo;
    const  void *                       pNext{};
    VkBufferCreateFlags   flags{};
    VkBufferUsageFlags                 usage{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
};
using VkPhysicalDeviceExternalBufferInfoKHR = VkPhysicalDeviceExternalBufferInfo;
struct VkExternalBufferProperties {
    VkStructureType   sType = VkStructureType::ExternalBufferProperties;
    void *                             pNext{};
    VkExternalMemoryProperties      externalMemoryProperties{};
};
using VkExternalBufferPropertiesKHR = VkExternalBufferProperties;
struct VkPhysicalDeviceIDProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceIdProperties;
    void *                             pNext{};
    uint8_t                            deviceUUID [ VK_UUID_SIZE ]{};
    uint8_t                            driverUUID [ VK_UUID_SIZE ]{};
    uint8_t                            deviceLUID [ VK_LUID_SIZE ]{};
    uint32_t                           deviceNodeMask{};
    VkBool32                           deviceLUIDValid{};
};
using VkPhysicalDeviceIDPropertiesKHR = VkPhysicalDeviceIDProperties;
struct VkExternalMemoryImageCreateInfo {
    VkStructureType   sType = VkStructureType::ExternalMemoryImageCreateInfo;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlags   handleTypes{};
};
using VkExternalMemoryImageCreateInfoKHR = VkExternalMemoryImageCreateInfo;
struct VkExternalMemoryBufferCreateInfo {
    VkStructureType   sType = VkStructureType::ExternalMemoryBufferCreateInfo;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlags   handleTypes{};
};
using VkExternalMemoryBufferCreateInfoKHR = VkExternalMemoryBufferCreateInfo;
struct VkExportMemoryAllocateInfo {
    VkStructureType   sType = VkStructureType::ExportMemoryAllocateInfo;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlags   handleTypes{};
};
using VkExportMemoryAllocateInfoKHR = VkExportMemoryAllocateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ImportMemoryWin32HandleInfoKHR;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
    HANDLE             handle{};
    LPCWSTR            name{};
};
struct VkExportMemoryWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ExportMemoryWin32HandleInfoKHR;
    const  void *                       pNext{};
    const  SECURITY_ATTRIBUTES *  pAttributes{};
    DWORD                              dwAccess{};
    LPCWSTR                            name{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct VkImportMemoryZirconHandleInfoFUCHSIA {
    VkStructureType   sType = VkStructureType::ImportMemoryZirconHandleInfoFUCHSIA;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
    zx_handle_t             handle{};
};
struct VkMemoryZirconHandlePropertiesFUCHSIA {
    VkStructureType   sType = VkStructureType::MemoryZirconHandlePropertiesFUCHSIA;
    void *                             pNext{};
    uint32_t                           memoryTypeBits{};
};
struct VkMemoryGetZirconHandleInfoFUCHSIA {
    VkStructureType   sType = VkStructureType::MemoryGetZirconHandleInfoFUCHSIA;
    const  void *                       pNext{};
    VkDeviceMemory                     memory{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
};
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkMemoryWin32HandlePropertiesKHR {
    VkStructureType   sType = VkStructureType::MemoryWin32HandlePropertiesKHR;
    void *                             pNext{};
    uint32_t                           memoryTypeBits{};
};
struct VkMemoryGetWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::MemoryGetWin32HandleInfoKHR;
    const  void *                       pNext{};
    VkDeviceMemory                     memory{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportMemoryFdInfoKHR {
    VkStructureType   sType = VkStructureType::ImportMemoryFdInfoKHR;
    const  void *                       pNext{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
    int                                fd{};
};
struct VkMemoryFdPropertiesKHR {
    VkStructureType   sType = VkStructureType::MemoryFdPropertiesKHR;
    void *                             pNext{};
    uint32_t                           memoryTypeBits{};
};
struct VkMemoryGetFdInfoKHR {
    VkStructureType   sType = VkStructureType::MemoryGetFdInfoKHR;
    const  void *                       pNext{};
    VkDeviceMemory                     memory{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkWin32KeyedMutexAcquireReleaseInfoKHR {
    VkStructureType   sType = VkStructureType::Win32KeyedMutexAcquireReleaseInfoKHR;
    const  void *                       pNext{};
    uint32_t           acquireCount{};
    const  VkDeviceMemory *  pAcquireSyncs{};
    const  uint64_t *  pAcquireKeys{};
    const  uint32_t *  pAcquireTimeouts{};
    uint32_t           releaseCount{};
    const  VkDeviceMemory *  pReleaseSyncs{};
    const  uint64_t *  pReleaseKeys{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDeviceExternalSemaphoreInfo {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExternalSemaphoreInfo;
    const  void *                       pNext{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
};
using VkPhysicalDeviceExternalSemaphoreInfoKHR = VkPhysicalDeviceExternalSemaphoreInfo;
struct VkExternalSemaphoreProperties {
    VkStructureType   sType = VkStructureType::ExternalSemaphoreProperties;
    void *                             pNext{};
    VkExternalSemaphoreHandleTypeFlags   exportFromImportedHandleTypes{};
    VkExternalSemaphoreHandleTypeFlags   compatibleHandleTypes{};
    VkExternalSemaphoreFeatureFlags   externalSemaphoreFeatures{};
};
using VkExternalSemaphorePropertiesKHR = VkExternalSemaphoreProperties;
struct VkExportSemaphoreCreateInfo {
    VkStructureType   sType = VkStructureType::ExportSemaphoreCreateInfo;
    const  void *                       pNext{};
    VkExternalSemaphoreHandleTypeFlags   handleTypes{};
};
using VkExportSemaphoreCreateInfoKHR = VkExportSemaphoreCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportSemaphoreWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ImportSemaphoreWin32HandleInfoKHR;
    const  void *                       pNext{};
    VkSemaphore      semaphore{};
    VkSemaphoreImportFlags   flags{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
    HANDLE             handle{};
    LPCWSTR            name{};
};
struct VkExportSemaphoreWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ExportSemaphoreWin32HandleInfoKHR;
    const  void *                       pNext{};
    const  SECURITY_ATTRIBUTES *        pAttributes{};
    DWORD                              dwAccess{};
    LPCWSTR                            name{};
};
struct VkD3D12FenceSubmitInfoKHR {
    VkStructureType   sType = VkStructureType::D3D12FenceSubmitInfoKHR;
    const  void *                       pNext{};
    uint32_t           waitSemaphoreValuesCount{};
    const  uint64_t *  pWaitSemaphoreValues{};
    uint32_t           signalSemaphoreValuesCount{};
    const  uint64_t *  pSignalSemaphoreValues{};
};
struct VkSemaphoreGetWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::SemaphoreGetWin32HandleInfoKHR;
    const  void *                       pNext{};
    VkSemaphore                        semaphore{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportSemaphoreFdInfoKHR {
    VkStructureType   sType = VkStructureType::ImportSemaphoreFdInfoKHR;
    const  void *                       pNext{};
    VkSemaphore      semaphore{};
    VkSemaphoreImportFlags   flags{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
    int                                fd{};
};
struct VkSemaphoreGetFdInfoKHR {
    VkStructureType   sType = VkStructureType::SemaphoreGetFdInfoKHR;
    const  void *                       pNext{};
    VkSemaphore                        semaphore{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
};
#if defined(VK_USE_PLATFORM_FUCHSIA)
struct VkImportSemaphoreZirconHandleInfoFUCHSIA {
    VkStructureType   sType = VkStructureType::ImportSemaphoreZirconHandleInfoFUCHSIA;
    const  void *                       pNext{};
    VkSemaphore      semaphore{};
    VkSemaphoreImportFlags   flags{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
    zx_handle_t                                zirconHandle{};
};
struct VkSemaphoreGetZirconHandleInfoFUCHSIA {
    VkStructureType   sType = VkStructureType::SemaphoreGetZirconHandleInfoFUCHSIA;
    const  void *                       pNext{};
    VkSemaphore                        semaphore{};
    VkExternalSemaphoreHandleTypeFlagBits   handleType{};
};
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
struct VkPhysicalDeviceExternalFenceInfo {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExternalFenceInfo;
    const  void *                       pNext{};
    VkExternalFenceHandleTypeFlagBits   handleType{};
};
using VkPhysicalDeviceExternalFenceInfoKHR = VkPhysicalDeviceExternalFenceInfo;
struct VkExternalFenceProperties {
    VkStructureType   sType = VkStructureType::ExternalFenceProperties;
    void *                             pNext{};
    VkExternalFenceHandleTypeFlags   exportFromImportedHandleTypes{};
    VkExternalFenceHandleTypeFlags   compatibleHandleTypes{};
    VkExternalFenceFeatureFlags   externalFenceFeatures{};
};
using VkExternalFencePropertiesKHR = VkExternalFenceProperties;
struct VkExportFenceCreateInfo {
    VkStructureType   sType = VkStructureType::ExportFenceCreateInfo;
    const  void *                       pNext{};
    VkExternalFenceHandleTypeFlags   handleTypes{};
};
using VkExportFenceCreateInfoKHR = VkExportFenceCreateInfo;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportFenceWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ImportFenceWin32HandleInfoKHR;
    const  void *                                         pNext{};
    VkFence                            fence{};
    VkFenceImportFlags                flags{};
    VkExternalFenceHandleTypeFlagBits    handleType{};
    HANDLE                               handle{};
    LPCWSTR                              name{};
};
struct VkExportFenceWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::ExportFenceWin32HandleInfoKHR;
    const  void *                                 pNext{};
    const  SECURITY_ATTRIBUTES *  pAttributes{};
    DWORD                                        dwAccess{};
    LPCWSTR                                      name{};
};
struct VkFenceGetWin32HandleInfoKHR {
    VkStructureType   sType = VkStructureType::FenceGetWin32HandleInfoKHR;
    const  void *                             pNext{};
    VkFence                                  fence{};
    VkExternalFenceHandleTypeFlagBits     handleType{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkImportFenceFdInfoKHR {
    VkStructureType   sType = VkStructureType::ImportFenceFdInfoKHR;
    const  void *                             pNext{};
    VkFence                fence{};
    VkFenceImportFlags    flags{};
    VkExternalFenceHandleTypeFlagBits     handleType{};
    int                                      fd{};
};
struct VkFenceGetFdInfoKHR {
    VkStructureType   sType = VkStructureType::FenceGetFdInfoKHR;
    const  void *                             pNext{};
    VkFence                                  fence{};
    VkExternalFenceHandleTypeFlagBits     handleType{};
};
struct VkPhysicalDeviceMultiviewFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMultiviewFeatures;
    void *                             pNext{};
    VkBool32                           multiview{};
    VkBool32                           multiviewGeometryShader{};
    VkBool32                           multiviewTessellationShader{};
};
using VkPhysicalDeviceMultiviewFeaturesKHR = VkPhysicalDeviceMultiviewFeatures;
struct VkPhysicalDeviceMultiviewProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMultiviewProperties;
    void *                             pNext{};
    uint32_t                           maxMultiviewViewCount{};
    uint32_t                           maxMultiviewInstanceIndex{};
};
using VkPhysicalDeviceMultiviewPropertiesKHR = VkPhysicalDeviceMultiviewProperties;
struct VkRenderPassMultiviewCreateInfo {
    VkStructureType          sType = VkStructureType::RenderPassMultiviewCreateInfo;
    const  void *             pNext{};
    uint32_t                 subpassCount{};
    const  uint32_t *      pViewMasks{};
    uint32_t                 dependencyCount{};
    const  int32_t *    pViewOffsets{};
    uint32_t                 correlationMaskCount{};
    const  uint32_t *  pCorrelationMasks{};
};
using VkRenderPassMultiviewCreateInfoKHR = VkRenderPassMultiviewCreateInfo;
struct VkSurfaceCapabilities2EXT {
    VkStructureType   sType = VkStructureType::SurfaceCapabilities2EXT;
    void *                             pNext{};
    uint32_t                           minImageCount{};
    uint32_t                           maxImageCount{};
    VkExtent2D                         currentExtent{};
    VkExtent2D                         minImageExtent{};
    VkExtent2D                         maxImageExtent{};
    uint32_t                           maxImageArrayLayers{};
    VkSurfaceTransformFlagsKHR         supportedTransforms{};
    VkSurfaceTransformFlagBitsKHR      currentTransform{};
    VkCompositeAlphaFlagsKHR           supportedCompositeAlpha{};
    VkImageUsageFlags                  supportedUsageFlags{};
    VkSurfaceCounterFlagsEXT   supportedSurfaceCounters{};
};
struct VkDisplayPowerInfoEXT {
    VkStructureType   sType = VkStructureType::DisplayPowerInfoEXT;
    const  void *                       pNext{};
    VkDisplayPowerStateEXT             powerState{};
};
struct VkDeviceEventInfoEXT {
    VkStructureType   sType = VkStructureType::DeviceEventInfoEXT;
    const  void *                       pNext{};
    VkDeviceEventTypeEXT               deviceEvent{};
};
struct VkDisplayEventInfoEXT {
    VkStructureType   sType = VkStructureType::DisplayEventInfoEXT;
    const  void *                       pNext{};
    VkDisplayEventTypeEXT              displayEvent{};
};
struct VkSwapchainCounterCreateInfoEXT {
    VkStructureType   sType = VkStructureType::SwapchainCounterCreateInfoEXT;
    const  void *                       pNext{};
    VkSurfaceCounterFlagsEXT           surfaceCounters{};
};
struct VkPhysicalDeviceGroupProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceGroupProperties;
    void *                             pNext{};
    uint32_t                           physicalDeviceCount{};
    VkPhysicalDevice                   physicalDevices [ VK_MAX_DEVICE_GROUP_SIZE ]{};
    VkBool32                           subsetAllocation{};
};
using VkPhysicalDeviceGroupPropertiesKHR = VkPhysicalDeviceGroupProperties;
struct VkMemoryAllocateFlagsInfo {
    VkStructureType   sType = VkStructureType::MemoryAllocateFlagsInfo;
    const  void *                       pNext{};
    VkMemoryAllocateFlags   flags{};
    uint32_t                           deviceMask{};
};
using VkMemoryAllocateFlagsInfoKHR = VkMemoryAllocateFlagsInfo;
struct VkBindBufferMemoryInfo {
    VkStructureType   sType = VkStructureType::BindBufferMemoryInfo;
    const  void *                       pNext{};
    VkBuffer                           buffer{};
    VkDeviceMemory                     memory{};
    VkDeviceSize                       memoryOffset{};
};
using VkBindBufferMemoryInfoKHR = VkBindBufferMemoryInfo;
struct VkBindBufferMemoryDeviceGroupInfo {
    VkStructureType   sType = VkStructureType::BindBufferMemoryDeviceGroupInfo;
    const  void *                       pNext{};
    uint32_t           deviceIndexCount{};
    const  uint32_t *   pDeviceIndices{};
};
using VkBindBufferMemoryDeviceGroupInfoKHR = VkBindBufferMemoryDeviceGroupInfo;
struct VkBindImageMemoryInfo {
    VkStructureType   sType = VkStructureType::BindImageMemoryInfo;
    const  void *                       pNext{};
    VkImage                            image{};
    VkDeviceMemory                     memory{};
    VkDeviceSize                       memoryOffset{};
};
using VkBindImageMemoryInfoKHR = VkBindImageMemoryInfo;
struct VkBindImageMemoryDeviceGroupInfo {
    VkStructureType   sType = VkStructureType::BindImageMemoryDeviceGroupInfo;
    const  void *                       pNext{};
    uint32_t           deviceIndexCount{};
    const  uint32_t *   pDeviceIndices{};
    uint32_t           splitInstanceBindRegionCount{};
    const  VkRect2D *   pSplitInstanceBindRegions{};
};
using VkBindImageMemoryDeviceGroupInfoKHR = VkBindImageMemoryDeviceGroupInfo;
struct VkDeviceGroupRenderPassBeginInfo {
    VkStructureType   sType = VkStructureType::DeviceGroupRenderPassBeginInfo;
    const  void *                       pNext{};
    uint32_t                           deviceMask{};
    uint32_t           deviceRenderAreaCount{};
    const  VkRect2D *   pDeviceRenderAreas{};
};
using VkDeviceGroupRenderPassBeginInfoKHR = VkDeviceGroupRenderPassBeginInfo;
struct VkDeviceGroupCommandBufferBeginInfo {
    VkStructureType   sType = VkStructureType::DeviceGroupCommandBufferBeginInfo;
    const  void *                       pNext{};
    uint32_t                           deviceMask{};
};
using VkDeviceGroupCommandBufferBeginInfoKHR = VkDeviceGroupCommandBufferBeginInfo;
struct VkDeviceGroupSubmitInfo {
    VkStructureType   sType = VkStructureType::DeviceGroupSubmitInfo;
    const  void *                       pNext{};
    uint32_t           waitSemaphoreCount{};
    const  uint32_t *     pWaitSemaphoreDeviceIndices{};
    uint32_t           commandBufferCount{};
    const  uint32_t *     pCommandBufferDeviceMasks{};
    uint32_t           signalSemaphoreCount{};
    const  uint32_t *   pSignalSemaphoreDeviceIndices{};
};
using VkDeviceGroupSubmitInfoKHR = VkDeviceGroupSubmitInfo;
struct VkDeviceGroupBindSparseInfo {
    VkStructureType   sType = VkStructureType::DeviceGroupBindSparseInfo;
    const  void *                       pNext{};
    uint32_t                           resourceDeviceIndex{};
    uint32_t                           memoryDeviceIndex{};
};
using VkDeviceGroupBindSparseInfoKHR = VkDeviceGroupBindSparseInfo;
struct VkDeviceGroupPresentCapabilitiesKHR {
    VkStructureType   sType = VkStructureType::DeviceGroupPresentCapabilitiesKHR;
    const  void *                       pNext{};
    uint32_t                           presentMask [ VK_MAX_DEVICE_GROUP_SIZE ]{};
    VkDeviceGroupPresentModeFlagsKHR   modes{};
};
struct VkImageSwapchainCreateInfoKHR {
    VkStructureType   sType = VkStructureType::ImageSwapchainCreateInfoKHR;
    const  void *                       pNext{};
    VkSwapchainKHR     swapchain{};
};
struct VkBindImageMemorySwapchainInfoKHR {
    VkStructureType   sType = VkStructureType::BindImageMemorySwapchainInfoKHR;
    const  void *                       pNext{};
    VkSwapchainKHR   swapchain{};
    uint32_t                           imageIndex{};
};
struct VkAcquireNextImageInfoKHR {
    VkStructureType   sType = VkStructureType::AcquireNextImageInfoKHR;
    const  void *                       pNext{};
    VkSwapchainKHR   swapchain{};
    uint64_t                           timeout{};
    VkSemaphore   semaphore{};
    VkFence   fence{};
    uint32_t                           deviceMask{};
};
struct VkDeviceGroupPresentInfoKHR {
    VkStructureType   sType = VkStructureType::DeviceGroupPresentInfoKHR;
    const  void *                       pNext{};
    uint32_t           swapchainCount{};
    const  uint32_t *  pDeviceMasks{};
    VkDeviceGroupPresentModeFlagBitsKHR   mode{};
};
struct VkDeviceGroupDeviceCreateInfo {
    VkStructureType   sType = VkStructureType::DeviceGroupDeviceCreateInfo;
    const  void *                       pNext{};
    uint32_t                           physicalDeviceCount{};
    const  VkPhysicalDevice *   pPhysicalDevices{};
};
using VkDeviceGroupDeviceCreateInfoKHR = VkDeviceGroupDeviceCreateInfo;
struct VkDeviceGroupSwapchainCreateInfoKHR {
    VkStructureType   sType = VkStructureType::DeviceGroupSwapchainCreateInfoKHR;
    const  void *                       pNext{};
    VkDeviceGroupPresentModeFlagsKHR                           modes{};
};
struct VkDescriptorUpdateTemplateEntry {
    uint32_t                           dstBinding{};
    uint32_t                           dstArrayElement{};
    uint32_t                           descriptorCount{};
    VkDescriptorType                   descriptorType{};
    size_t                             offset{};
    size_t                             stride{};
};
using VkDescriptorUpdateTemplateEntryKHR = VkDescriptorUpdateTemplateEntry;
struct VkDescriptorUpdateTemplateCreateInfo {
    VkStructureType   sType = VkStructureType::DescriptorUpdateTemplateCreateInfo;
    const  void *                                pNext{};
    VkDescriptorUpdateTemplateCreateFlags      flags{};
    uint32_t                   descriptorUpdateEntryCount{};
    const  VkDescriptorUpdateTemplateEntry *  pDescriptorUpdateEntries{};
    VkDescriptorUpdateTemplateType   templateType{};
    VkDescriptorSetLayout   descriptorSetLayout{};
    VkPipelineBindPoint   pipelineBindPoint{};
    VkPipelineLayout pipelineLayout{};
    uint32_t   set{};
};
using VkDescriptorUpdateTemplateCreateInfoKHR = VkDescriptorUpdateTemplateCreateInfo;
struct VkXYColorEXT {
    float     x{};
    float     y{};
};
struct VkHdrMetadataEXT {
    VkStructureType   sType = VkStructureType::HdrMetadataEXT;
    const  void *     pNext{};
    VkXYColorEXT     displayPrimaryRed{};
    VkXYColorEXT     displayPrimaryGreen{};
    VkXYColorEXT     displayPrimaryBlue{};
    VkXYColorEXT     whitePoint{};
    float            maxLuminance{};
    float            minLuminance{};
    float            maxContentLightLevel{};
    float            maxFrameAverageLightLevel{};
};
struct VkDisplayNativeHdrSurfaceCapabilitiesAMD {
    VkStructureType   sType = VkStructureType::DisplayNativeHdrSurfaceCapabilitiesAMD;
    void *           pNext{};
    VkBool32         localDimmingSupport{};
};
struct VkSwapchainDisplayNativeHdrCreateInfoAMD {
    VkStructureType   sType = VkStructureType::SwapchainDisplayNativeHdrCreateInfoAMD;
    const  void *     pNext{};
    VkBool32         localDimmingEnable{};
};
struct VkRefreshCycleDurationGOOGLE {
    uint64_t                           refreshDuration{};
};
struct VkPastPresentationTimingGOOGLE {
    uint32_t                           presentID{};
    uint64_t                           desiredPresentTime{};
    uint64_t                           actualPresentTime{};
    uint64_t                           earliestPresentTime{};
    uint64_t                           presentMargin{};
};
struct VkPresentTimeGOOGLE {
    uint32_t                           presentID{};
    uint64_t                           desiredPresentTime{};
};
struct VkPresentTimesInfoGOOGLE {
    VkStructureType   sType = VkStructureType::PresentTimesInfoGOOGLE;
    const  void *                       pNext{};
    uint32_t                           swapchainCount{};
    const  VkPresentTimeGOOGLE *    pTimes{};
};
#if defined(VK_USE_PLATFORM_IOS_MVK)
struct VkIOSSurfaceCreateInfoMVK {
    VkStructureType   sType = VkStructureType::IosSurfaceCreateInfoMVK;
    const  void *                                     pNext{};
    VkIOSSurfaceCreateFlagsMVK       flags{};
    const  void *                                     pView{};
};
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
struct VkMacOSSurfaceCreateInfoMVK {
    VkStructureType   sType = VkStructureType::MacosSurfaceCreateInfoMVK;
    const  void *                                     pNext{};
    VkMacOSSurfaceCreateFlagsMVK     flags{};
    const  void *                                     pView{};
};
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
#if defined(VK_USE_PLATFORM_METAL_EXT)
struct VkMetalSurfaceCreateInfoEXT {
    VkStructureType   sType = VkStructureType::MetalSurfaceCreateInfoEXT;
    const  void *                                     pNext{};
    VkMetalSurfaceCreateFlagsEXT     flags{};
    const  CAMetalLayer *       pLayer{};
};
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
struct VkViewportWScalingNV {
    float            xcoeff{};
    float            ycoeff{};
};
struct VkPipelineViewportWScalingStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineViewportWScalingStateCreateInfoNV;
    const  void *                       pNext{};
    VkBool32                 viewportWScalingEnable{};
    uint32_t                 viewportCount{};
    const  VkViewportWScalingNV *       pViewportWScalings{};
};
struct VkViewportSwizzleNV {
    VkViewportCoordinateSwizzleNV            x{};
    VkViewportCoordinateSwizzleNV            y{};
    VkViewportCoordinateSwizzleNV            z{};
    VkViewportCoordinateSwizzleNV            w{};
};
struct VkPipelineViewportSwizzleStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineViewportSwizzleStateCreateInfoNV;
    const  void *             pNext{};
    VkPipelineViewportSwizzleStateCreateFlagsNV      flags{};
    uint32_t                 viewportCount{};
    const  VkViewportSwizzleNV *       pViewportSwizzles{};
};
struct VkPhysicalDeviceDiscardRectanglePropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDiscardRectanglePropertiesEXT;
    void *                   pNext{};
    uint32_t                 maxDiscardRectangles{};
};
struct VkPipelineDiscardRectangleStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineDiscardRectangleStateCreateInfoEXT;
    const  void *                                                        pNext{};
    VkPipelineDiscardRectangleStateCreateFlagsEXT       flags{};
    VkDiscardRectangleModeEXT                                           discardRectangleMode{};
    uint32_t                                            discardRectangleCount{};
    const  VkRect2D *  pDiscardRectangles{};
};
struct VkPhysicalDeviceMultiviewPerViewAttributesPropertiesNVX {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX;
    void *                             pNext{};
    VkBool32                           perViewPositionAllComponents{};
};
struct VkInputAttachmentAspectReference {
    uint32_t                          subpass{};
    uint32_t                          inputAttachmentIndex{};
    VkImageAspectFlags                aspectMask{};
};
using VkInputAttachmentAspectReferenceKHR = VkInputAttachmentAspectReference;
struct VkRenderPassInputAttachmentAspectCreateInfo {
    VkStructureType   sType = VkStructureType::RenderPassInputAttachmentAspectCreateInfo;
    const  void *                      pNext{};
    uint32_t                          aspectReferenceCount{};
    const  VkInputAttachmentAspectReference *  pAspectReferences{};
};
using VkRenderPassInputAttachmentAspectCreateInfoKHR = VkRenderPassInputAttachmentAspectCreateInfo;
struct VkPhysicalDeviceSurfaceInfo2KHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSurfaceInfo2KHR;
    const  void *  pNext{};
    VkSurfaceKHR   surface{};
};
struct VkSurfaceCapabilities2KHR {
    VkStructureType   sType = VkStructureType::SurfaceCapabilities2KHR;
    void *    pNext{};
    VkSurfaceCapabilitiesKHR   surfaceCapabilities{};
};
struct VkSurfaceFormat2KHR {
    VkStructureType   sType = VkStructureType::SurfaceFormat2KHR;
    void *  pNext{};
    VkSurfaceFormatKHR   surfaceFormat{};
};
struct VkDisplayProperties2KHR {
    VkStructureType   sType = VkStructureType::DisplayProperties2KHR;
    void *  pNext{};
    VkDisplayPropertiesKHR   displayProperties{};
};
struct VkDisplayPlaneProperties2KHR {
    VkStructureType   sType = VkStructureType::DisplayPlaneProperties2KHR;
    void *  pNext{};
    VkDisplayPlanePropertiesKHR   displayPlaneProperties{};
};
struct VkDisplayModeProperties2KHR {
    VkStructureType   sType = VkStructureType::DisplayModeProperties2KHR;
    void *  pNext{};
    VkDisplayModePropertiesKHR   displayModeProperties{};
};
struct VkDisplayPlaneInfo2KHR {
    VkStructureType   sType = VkStructureType::DisplayPlaneInfo2KHR;
    const  void *  pNext{};
    VkDisplayModeKHR   mode{};
    uint32_t   planeIndex{};
};
struct VkDisplayPlaneCapabilities2KHR {
    VkStructureType   sType = VkStructureType::DisplayPlaneCapabilities2KHR;
    void *  pNext{};
    VkDisplayPlaneCapabilitiesKHR   capabilities{};
};
struct VkSharedPresentSurfaceCapabilitiesKHR {
    VkStructureType   sType = VkStructureType::SharedPresentSurfaceCapabilitiesKHR;
    void *                             pNext{};
    VkImageUsageFlags   sharedPresentSupportedUsageFlags{};
};
struct VkPhysicalDevice16BitStorageFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDevice16BitStorageFeatures;
    void *       pNext{};
    VkBool32                           storageBuffer16BitAccess{};
    VkBool32                           uniformAndStorageBuffer16BitAccess{};
    VkBool32                           storagePushConstant16{};
    VkBool32                           storageInputOutput16{};
};
using VkPhysicalDevice16BitStorageFeaturesKHR = VkPhysicalDevice16BitStorageFeatures;
struct VkPhysicalDeviceSubgroupProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSubgroupProperties;
    void *                    pNext{};
    uint32_t                        subgroupSize{};
    VkShaderStageFlags              supportedStages{};
    VkSubgroupFeatureFlags          supportedOperations{};
    VkBool32   quadOperationsInAllStages{};
};
struct VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderSubgroupExtendedTypesFeatures;
    void *                           pNext{};
    VkBool32   shaderSubgroupExtendedTypes{};
};
using VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR = VkPhysicalDeviceShaderSubgroupExtendedTypesFeatures;
struct VkBufferMemoryRequirementsInfo2 {
    VkStructureType   sType = VkStructureType::BufferMemoryRequirementsInfo2;
    const  void *                                                           pNext{};
    VkBuffer                                                               buffer{};
};
using VkBufferMemoryRequirementsInfo2KHR = VkBufferMemoryRequirementsInfo2;
struct VkImageMemoryRequirementsInfo2 {
    VkStructureType   sType = VkStructureType::ImageMemoryRequirementsInfo2;
    const  void *                                                           pNext{};
    VkImage                                                                image{};
};
using VkImageMemoryRequirementsInfo2KHR = VkImageMemoryRequirementsInfo2;
struct VkImageSparseMemoryRequirementsInfo2 {
    VkStructureType   sType = VkStructureType::ImageSparseMemoryRequirementsInfo2;
    const  void *                                                           pNext{};
    VkImage                                                                image{};
};
using VkImageSparseMemoryRequirementsInfo2KHR = VkImageSparseMemoryRequirementsInfo2;
struct VkMemoryRequirements2 {
    VkStructureType   sType = VkStructureType::MemoryRequirements2;
    void *  pNext{};
    VkMemoryRequirements                                                   memoryRequirements{};
};
using VkMemoryRequirements2KHR = VkMemoryRequirements2;
struct VkSparseImageMemoryRequirements2 {
    VkStructureType   sType = VkStructureType::SparseImageMemoryRequirements2;
    void *                                        pNext{};
    VkSparseImageMemoryRequirements                                        memoryRequirements{};
};
using VkSparseImageMemoryRequirements2KHR = VkSparseImageMemoryRequirements2;
struct VkPhysicalDevicePointClippingProperties {
    VkStructureType   sType = VkStructureType::PhysicalDevicePointClippingProperties;
    void *                             pNext{};
    VkPointClippingBehavior        pointClippingBehavior{};
};
using VkPhysicalDevicePointClippingPropertiesKHR = VkPhysicalDevicePointClippingProperties;
struct VkMemoryDedicatedRequirements {
    VkStructureType   sType = VkStructureType::MemoryDedicatedRequirements;
    void *                             pNext{};
    VkBool32                           prefersDedicatedAllocation{};
    VkBool32                           requiresDedicatedAllocation{};
};
using VkMemoryDedicatedRequirementsKHR = VkMemoryDedicatedRequirements;
struct VkMemoryDedicatedAllocateInfo {
    VkStructureType   sType = VkStructureType::MemoryDedicatedAllocateInfo;
    const  void *                       pNext{};
    VkImage            image{};
    VkBuffer           buffer{};
};
using VkMemoryDedicatedAllocateInfoKHR = VkMemoryDedicatedAllocateInfo;
struct VkImageViewUsageCreateInfo {
    VkStructureType   sType = VkStructureType::ImageViewUsageCreateInfo;
    const  void *  pNext{};
    VkImageUsageFlags   usage{};
};
using VkImageViewUsageCreateInfoKHR = VkImageViewUsageCreateInfo;
struct VkPipelineTessellationDomainOriginStateCreateInfo {
    VkStructureType   sType = VkStructureType::PipelineTessellationDomainOriginStateCreateInfo;
    const  void *                       pNext{};
    VkTessellationDomainOrigin      domainOrigin{};
};
using VkPipelineTessellationDomainOriginStateCreateInfoKHR = VkPipelineTessellationDomainOriginStateCreateInfo;
struct VkSamplerYcbcrConversionInfo {
    VkStructureType   sType = VkStructureType::SamplerYcbcrConversionInfo;
    const  void *                       pNext{};
    VkSamplerYcbcrConversion        conversion{};
};
using VkSamplerYcbcrConversionInfoKHR = VkSamplerYcbcrConversionInfo;
struct VkSamplerYcbcrConversionCreateInfo {
    VkStructureType   sType = VkStructureType::SamplerYcbcrConversionCreateInfo;
    const  void *                       pNext{};
    VkFormat                           format{};
    VkSamplerYcbcrModelConversion   ycbcrModel{};
    VkSamplerYcbcrRange             ycbcrRange{};
    VkComponentMapping                 components{};
    VkChromaLocation                xChromaOffset{};
    VkChromaLocation                yChromaOffset{};
    VkFilter                           chromaFilter{};
    VkBool32                           forceExplicitReconstruction{};
};
using VkSamplerYcbcrConversionCreateInfoKHR = VkSamplerYcbcrConversionCreateInfo;
struct VkBindImagePlaneMemoryInfo {
    VkStructureType   sType = VkStructureType::BindImagePlaneMemoryInfo;
    const  void *                       pNext{};
    VkImageAspectFlagBits              planeAspect{};
};
using VkBindImagePlaneMemoryInfoKHR = VkBindImagePlaneMemoryInfo;
struct VkImagePlaneMemoryRequirementsInfo {
    VkStructureType   sType = VkStructureType::ImagePlaneMemoryRequirementsInfo;
    const  void *                       pNext{};
    VkImageAspectFlagBits              planeAspect{};
};
using VkImagePlaneMemoryRequirementsInfoKHR = VkImagePlaneMemoryRequirementsInfo;
struct VkPhysicalDeviceSamplerYcbcrConversionFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSamplerYcbcrConversionFeatures;
    void *       pNext{};
    VkBool32                           samplerYcbcrConversion{};
};
using VkPhysicalDeviceSamplerYcbcrConversionFeaturesKHR = VkPhysicalDeviceSamplerYcbcrConversionFeatures;
struct VkSamplerYcbcrConversionImageFormatProperties {
    VkStructureType   sType = VkStructureType::SamplerYcbcrConversionImageFormatProperties;
    void *       pNext{};
    uint32_t                           combinedImageSamplerDescriptorCount{};
};
using VkSamplerYcbcrConversionImageFormatPropertiesKHR = VkSamplerYcbcrConversionImageFormatProperties;
struct VkTextureLODGatherFormatPropertiesAMD {
    VkStructureType   sType = VkStructureType::TextureLodGatherFormatPropertiesAMD;
    void *                             pNext{};
    VkBool32                           supportsTextureGatherLODBiasAMD{};
};
struct VkConditionalRenderingBeginInfoEXT {
    VkStructureType   sType = VkStructureType::ConditionalRenderingBeginInfoEXT;
    const  void *                       pNext{};
    VkBuffer                           buffer{};
    VkDeviceSize                       offset{};
    VkConditionalRenderingFlagsEXT      flags{};
};
struct VkProtectedSubmitInfo {
    VkStructureType   sType = VkStructureType::ProtectedSubmitInfo;
    const  void *                      pNext{};
    VkBool32                          protectedSubmit{};
};
struct VkPhysicalDeviceProtectedMemoryFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceProtectedMemoryFeatures;
    void *                                pNext{};
    VkBool32                              protectedMemory{};
};
struct VkPhysicalDeviceProtectedMemoryProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceProtectedMemoryProperties;
    void *                                pNext{};
    VkBool32                              protectedNoFault{};
};
struct VkDeviceQueueInfo2 {
    VkStructureType   sType = VkStructureType::DeviceQueueInfo2;
    const  void *                          pNext{};
    VkDeviceQueueCreateFlags              flags{};
    uint32_t                              queueFamilyIndex{};
    uint32_t                              queueIndex{};
};
struct VkPipelineCoverageToColorStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineCoverageToColorStateCreateInfoNV;
    const  void *                                                                       pNext{};
    VkPipelineCoverageToColorStateCreateFlagsNV                      flags{};
    VkBool32                           coverageToColorEnable{};
    uint32_t           coverageToColorLocation{};
};
struct VkPhysicalDeviceSamplerFilterMinmaxProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSamplerFilterMinmaxProperties;
    void *                   pNext{};
    VkBool32                 filterMinmaxSingleComponentFormats{};
    VkBool32                 filterMinmaxImageComponentMapping{};
};
using VkPhysicalDeviceSamplerFilterMinmaxPropertiesEXT = VkPhysicalDeviceSamplerFilterMinmaxProperties;
struct VkSampleLocationEXT {
    float                              x{};
    float                              y{};
};
struct VkSampleLocationsInfoEXT {
    VkStructureType   sType = VkStructureType::SampleLocationsInfoEXT;
    const  void *                             pNext{};
    VkSampleCountFlagBits    sampleLocationsPerPixel{};
    VkExtent2D                               sampleLocationGridSize{};
    uint32_t                 sampleLocationsCount{};
    const  VkSampleLocationEXT *  pSampleLocations{};
};
struct VkAttachmentSampleLocationsEXT {
    uint32_t                           attachmentIndex{};
    VkSampleLocationsInfoEXT           sampleLocationsInfo{};
};
struct VkSubpassSampleLocationsEXT {
    uint32_t                           subpassIndex{};
    VkSampleLocationsInfoEXT           sampleLocationsInfo{};
};
struct VkRenderPassSampleLocationsBeginInfoEXT {
    VkStructureType   sType = VkStructureType::RenderPassSampleLocationsBeginInfoEXT;
    const  void *                       pNext{};
    uint32_t           attachmentInitialSampleLocationsCount{};
    const  VkAttachmentSampleLocationsEXT *  pAttachmentInitialSampleLocations{};
    uint32_t           postSubpassSampleLocationsCount{};
    const  VkSubpassSampleLocationsEXT *  pPostSubpassSampleLocations{};
};
struct VkPipelineSampleLocationsStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineSampleLocationsStateCreateInfoEXT;
    const  void *                       pNext{};
    VkBool32                           sampleLocationsEnable{};
    VkSampleLocationsInfoEXT           sampleLocationsInfo{};
};
struct VkPhysicalDeviceSampleLocationsPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSampleLocationsPropertiesEXT;
    void *                             pNext{};
    VkSampleCountFlags                 sampleLocationSampleCounts{};
    VkExtent2D                         maxSampleLocationGridSize{};
    float                              sampleLocationCoordinateRange [2]{};
    uint32_t                           sampleLocationSubPixelBits{};
    VkBool32                           variableSampleLocations{};
};
struct VkMultisamplePropertiesEXT {
    VkStructureType   sType = VkStructureType::MultisamplePropertiesEXT;
    void *                             pNext{};
    VkExtent2D                         maxSampleLocationGridSize{};
};
struct VkSamplerReductionModeCreateInfo {
    VkStructureType   sType = VkStructureType::SamplerReductionModeCreateInfo;
    const  void *                       pNext{};
    VkSamplerReductionMode             reductionMode{};
};
using VkSamplerReductionModeCreateInfoEXT = VkSamplerReductionModeCreateInfo;
struct VkPhysicalDeviceBlendOperationAdvancedFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceBlendOperationAdvancedFeaturesEXT;
    void *                             pNext{};
    VkBool32                           advancedBlendCoherentOperations{};
};
struct VkPhysicalDeviceBlendOperationAdvancedPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceBlendOperationAdvancedPropertiesEXT;
    void *                             pNext{};
    uint32_t                           advancedBlendMaxColorAttachments{};
    VkBool32                           advancedBlendIndependentBlend{};
    VkBool32                           advancedBlendNonPremultipliedSrcColor{};
    VkBool32                           advancedBlendNonPremultipliedDstColor{};
    VkBool32                           advancedBlendCorrelatedOverlap{};
    VkBool32                           advancedBlendAllOperations{};
};
struct VkPipelineColorBlendAdvancedStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineColorBlendAdvancedStateCreateInfoEXT;
    const  void *             pNext{};
    VkBool32                 srcPremultiplied{};
    VkBool32                 dstPremultiplied{};
    VkBlendOverlapEXT        blendOverlap{};
};
struct VkPhysicalDeviceInlineUniformBlockFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceInlineUniformBlockFeaturesEXT;
    void *                   pNext{};
    VkBool32                 inlineUniformBlock{};
    VkBool32                 descriptorBindingInlineUniformBlockUpdateAfterBind{};
};
struct VkPhysicalDeviceInlineUniformBlockPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceInlineUniformBlockPropertiesEXT;
    void *                   pNext{};
    uint32_t                 maxInlineUniformBlockSize{};
    uint32_t                 maxPerStageDescriptorInlineUniformBlocks{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks{};
    uint32_t                 maxDescriptorSetInlineUniformBlocks{};
    uint32_t                 maxDescriptorSetUpdateAfterBindInlineUniformBlocks{};
};
struct VkWriteDescriptorSetInlineUniformBlockEXT {
    VkStructureType   sType = VkStructureType::WriteDescriptorSetInlineUniformBlockEXT;
    const  void *             pNext{};
    uint32_t                 dataSize{};
    const  void *  pData{};
};
struct VkDescriptorPoolInlineUniformBlockCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DescriptorPoolInlineUniformBlockCreateInfoEXT;
    const  void *             pNext{};
    uint32_t                 maxInlineUniformBlockBindings{};
};
struct VkPipelineCoverageModulationStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineCoverageModulationStateCreateInfoNV;
    const  void *                                                                       pNext{};
    VkPipelineCoverageModulationStateCreateFlagsNV                     flags{};
    VkCoverageModulationModeNV                                                         coverageModulationMode{};
    VkBool32                                                                           coverageModulationTableEnable{};
    uint32_t                                                           coverageModulationTableCount{};
    const  float *  pCoverageModulationTable{};
};
struct VkImageFormatListCreateInfo {
    VkStructureType   sType = VkStructureType::ImageFormatListCreateInfo;
    const  void *                             pNext{};
    uint32_t                 viewFormatCount{};
    const  VkFormat *   pViewFormats{};
};
using VkImageFormatListCreateInfoKHR = VkImageFormatListCreateInfo;
struct VkValidationCacheCreateInfoEXT {
    VkStructureType   sType = VkStructureType::ValidationCacheCreateInfoEXT;
    const  void *             pNext{};
    VkValidationCacheCreateFlagsEXT      flags{};
    size_t                   initialDataSize{};
    const  void *             pInitialData{};
};
struct VkShaderModuleValidationCacheCreateInfoEXT {
    VkStructureType   sType = VkStructureType::ShaderModuleValidationCacheCreateInfoEXT;
    const  void *             pNext{};
    VkValidationCacheEXT      validationCache{};
};
struct VkPhysicalDeviceMaintenance3Properties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMaintenance3Properties;
    void *                             pNext{};
    uint32_t                           maxPerSetDescriptors{};
    VkDeviceSize                       maxMemoryAllocationSize{};
};
using VkPhysicalDeviceMaintenance3PropertiesKHR = VkPhysicalDeviceMaintenance3Properties;
struct VkDescriptorSetLayoutSupport {
    VkStructureType   sType = VkStructureType::DescriptorSetLayoutSupport;
    void *             pNext{};
    VkBool32           supported{};
};
using VkDescriptorSetLayoutSupportKHR = VkDescriptorSetLayoutSupport;
struct VkPhysicalDeviceShaderDrawParametersFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderDrawParametersFeatures;
    void *                             pNext{};
    VkBool32                           shaderDrawParameters{};
};
using VkPhysicalDeviceShaderDrawParameterFeatures = VkPhysicalDeviceShaderDrawParametersFeatures;
struct VkPhysicalDeviceShaderFloat16Int8Features {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderFloat16Int8Features;
    void *       pNext{};
    VkBool32                           shaderFloat16{};
    VkBool32                           shaderInt8{};
};
using VkPhysicalDeviceShaderFloat16Int8FeaturesKHR = VkPhysicalDeviceShaderFloat16Int8Features;
using VkPhysicalDeviceFloat16Int8FeaturesKHR = VkPhysicalDeviceShaderFloat16Int8Features;
struct VkPhysicalDeviceFloatControlsProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFloatControlsProperties;
    void *                             pNext{};
    VkShaderFloatControlsIndependence   denormBehaviorIndependence{};
    VkShaderFloatControlsIndependence   roundingModeIndependence{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat16{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat32{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat64{};
    VkBool32                           shaderDenormPreserveFloat16{};
    VkBool32                           shaderDenormPreserveFloat32{};
    VkBool32                           shaderDenormPreserveFloat64{};
    VkBool32                           shaderDenormFlushToZeroFloat16{};
    VkBool32                           shaderDenormFlushToZeroFloat32{};
    VkBool32                           shaderDenormFlushToZeroFloat64{};
    VkBool32                           shaderRoundingModeRTEFloat16{};
    VkBool32                           shaderRoundingModeRTEFloat32{};
    VkBool32                           shaderRoundingModeRTEFloat64{};
    VkBool32                           shaderRoundingModeRTZFloat16{};
    VkBool32                           shaderRoundingModeRTZFloat32{};
    VkBool32                           shaderRoundingModeRTZFloat64{};
};
using VkPhysicalDeviceFloatControlsPropertiesKHR = VkPhysicalDeviceFloatControlsProperties;
struct VkPhysicalDeviceHostQueryResetFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceHostQueryResetFeatures;
    void *         pNext{};
    VkBool32                             hostQueryReset{};
};
using VkPhysicalDeviceHostQueryResetFeaturesEXT = VkPhysicalDeviceHostQueryResetFeatures;
struct VkShaderResourceUsageAMD {
    uint32_t   numUsedVgprs{};
    uint32_t   numUsedSgprs{};
    uint32_t   ldsSizePerLocalWorkGroup{};
    size_t   ldsUsageSizeInBytes{};
    size_t   scratchMemUsageInBytes{};
};
struct VkShaderStatisticsInfoAMD {
    VkShaderStageFlags   shaderStageMask{};
    VkShaderResourceUsageAMD   resourceUsage{};
    uint32_t   numPhysicalVgprs{};
    uint32_t   numPhysicalSgprs{};
    uint32_t   numAvailableVgprs{};
    uint32_t   numAvailableSgprs{};
    uint32_t   computeWorkGroupSize [3]{};
};
struct VkDeviceQueueGlobalPriorityCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DeviceQueueGlobalPriorityCreateInfoEXT;
    const  void *                     pNext{};
    VkQueueGlobalPriorityEXT         globalPriority{};
};
struct VkDebugUtilsObjectNameInfoEXT {
    VkStructureType   sType = VkStructureType::DebugUtilsObjectNameInfoEXT;
    const  void *                                             pNext{};
    VkObjectType                                             objectType{};
    uint64_t                                                 objectHandle{};
    const  char *       pObjectName{};
};
struct VkDebugUtilsObjectTagInfoEXT {
    VkStructureType   sType = VkStructureType::DebugUtilsObjectTagInfoEXT;
    const  void *                             pNext{};
    VkObjectType                             objectType{};
    uint64_t                                 objectHandle{};
    uint64_t                                 tagName{};
    size_t                                   tagSize{};
    const  void *               pTag{};
};
struct VkDebugUtilsLabelEXT {
    VkStructureType   sType = VkStructureType::DebugUtilsLabelEXT;
    const  void *                             pNext{};
    const  char *       pLabelName{};
    float                    color [4]{};
};
struct VkDebugUtilsMessengerCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DebugUtilsMessengerCreateInfoEXT;
    const  void *                                           pNext{};
    VkDebugUtilsMessengerCreateFlagsEXT    flags{};
    VkDebugUtilsMessageSeverityFlagsEXT                    messageSeverity{};
    VkDebugUtilsMessageTypeFlagsEXT                        messageType{};
    PFN_vkDebugUtilsMessengerCallbackEXT                   pfnUserCallback{};
    void *                                 pUserData{};
};
struct VkDebugUtilsMessengerCallbackDataEXT {
    VkStructureType   sType = VkStructureType::DebugUtilsMessengerCallbackDataEXT;
    const  void *                                                         pNext{};
    VkDebugUtilsMessengerCallbackDataFlagsEXT                            flags{};
    const  char *                                   pMessageIdName{};
    int32_t                                                              messageIdNumber{};
    const  char *                                                   pMessage{};
    uint32_t                                                             queueLabelCount{};
    const  VkDebugUtilsLabelEXT *                   pQueueLabels{};
    uint32_t                                                             cmdBufLabelCount{};
    const  VkDebugUtilsLabelEXT *                  pCmdBufLabels{};
    uint32_t                                                             objectCount{};
    const  VkDebugUtilsObjectNameInfoEXT *              pObjects{};
};
struct VkPhysicalDeviceDeviceMemoryReportFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDeviceMemoryReportFeaturesEXT;
    void *  pNext{};
    VkBool32                      deviceMemoryReport{};
};
struct VkDeviceDeviceMemoryReportCreateInfoEXT {
    VkStructureType   sType = VkStructureType::DeviceDeviceMemoryReportCreateInfoEXT;
    const  void *          pNext{};
    VkDeviceMemoryReportFlagsEXT          flags{};
    PFN_vkDeviceMemoryReportCallbackEXT   pfnUserCallback{};
    void *                                pUserData{};
};
struct VkDeviceMemoryReportCallbackDataEXT {
    VkStructureType   sType = VkStructureType::DeviceMemoryReportCallbackDataEXT;
    const  void *                       pNext{};
    VkDeviceMemoryReportFlagsEXT       flags{};
    VkDeviceMemoryReportEventTypeEXT   type{};
    uint64_t                           memoryObjectId{};
    VkDeviceSize                       size{};
    VkObjectType                       objectType{};
    uint64_t                           objectHandle{};
    uint32_t                           heapIndex{};
};
struct VkImportMemoryHostPointerInfoEXT {
    VkStructureType   sType = VkStructureType::ImportMemoryHostPointerInfoEXT;
    const  void *  pNext{};
    VkExternalMemoryHandleTypeFlagBits   handleType{};
    void *  pHostPointer{};
};
struct VkMemoryHostPointerPropertiesEXT {
    VkStructureType   sType = VkStructureType::MemoryHostPointerPropertiesEXT;
    void *  pNext{};
    uint32_t   memoryTypeBits{};
};
struct VkPhysicalDeviceExternalMemoryHostPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExternalMemoryHostPropertiesEXT;
    void *  pNext{};
    VkDeviceSize   minImportedHostPointerAlignment{};
};
struct VkPhysicalDeviceConservativeRasterizationPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceConservativeRasterizationPropertiesEXT;
    void *                   pNext{};
    float                    primitiveOverestimationSize{};
    float                    maxExtraPrimitiveOverestimationSize{};
    float                    extraPrimitiveOverestimationSizeGranularity{};
    VkBool32                 primitiveUnderestimation{};
    VkBool32                 conservativePointAndLineRasterization{};
    VkBool32                 degenerateTrianglesRasterized{};
    VkBool32                 degenerateLinesRasterized{};
    VkBool32                 fullyCoveredFragmentShaderInputVariable{};
    VkBool32                 conservativeRasterizationPostDepthCoverage{};
};
struct VkCalibratedTimestampInfoEXT {
    VkStructureType   sType = VkStructureType::CalibratedTimestampInfoEXT;
    const  void *             pNext{};
    VkTimeDomainEXT          timeDomain{};
};
struct VkPhysicalDeviceShaderCorePropertiesAMD {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderCorePropertiesAMD;
    void *     pNext{};
    uint32_t   shaderEngineCount{};
    uint32_t   shaderArraysPerEngineCount{};
    uint32_t   computeUnitsPerShaderArray{};
    uint32_t   simdPerComputeUnit{};
    uint32_t   wavefrontsPerSimd{};
    uint32_t   wavefrontSize{};
    uint32_t   sgprsPerSimd{};
    uint32_t   minSgprAllocation{};
    uint32_t   maxSgprAllocation{};
    uint32_t   sgprAllocationGranularity{};
    uint32_t   vgprsPerSimd{};
    uint32_t   minVgprAllocation{};
    uint32_t   maxVgprAllocation{};
    uint32_t   vgprAllocationGranularity{};
};
struct VkPhysicalDeviceShaderCoreProperties2AMD {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderCoreProperties2AMD;
    void *     pNext{};
    VkShaderCorePropertiesFlagsAMD   shaderCoreFeatures{};
    uint32_t   activeComputeUnitCount{};
};
struct VkPipelineRasterizationConservativeStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineRasterizationConservativeStateCreateInfoEXT;
    const  void *                                                                       pNext{};
    VkPipelineRasterizationConservativeStateCreateFlagsEXT             flags{};
    VkConservativeRasterizationModeEXT                                                 conservativeRasterizationMode{};
    float                                                                              extraPrimitiveOverestimationSize{};
};
struct VkPhysicalDeviceDescriptorIndexingFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDescriptorIndexingFeatures;
    void *                             pNext{};
    VkBool32                 shaderInputAttachmentArrayDynamicIndexing{};
    VkBool32                 shaderUniformTexelBufferArrayDynamicIndexing{};
    VkBool32                 shaderStorageTexelBufferArrayDynamicIndexing{};
    VkBool32                 shaderUniformBufferArrayNonUniformIndexing{};
    VkBool32                 shaderSampledImageArrayNonUniformIndexing{};
    VkBool32                 shaderStorageBufferArrayNonUniformIndexing{};
    VkBool32                 shaderStorageImageArrayNonUniformIndexing{};
    VkBool32                 shaderInputAttachmentArrayNonUniformIndexing{};
    VkBool32                 shaderUniformTexelBufferArrayNonUniformIndexing{};
    VkBool32                 shaderStorageTexelBufferArrayNonUniformIndexing{};
    VkBool32                 descriptorBindingUniformBufferUpdateAfterBind{};
    VkBool32                 descriptorBindingSampledImageUpdateAfterBind{};
    VkBool32                 descriptorBindingStorageImageUpdateAfterBind{};
    VkBool32                 descriptorBindingStorageBufferUpdateAfterBind{};
    VkBool32                 descriptorBindingUniformTexelBufferUpdateAfterBind{};
    VkBool32                 descriptorBindingStorageTexelBufferUpdateAfterBind{};
    VkBool32                 descriptorBindingUpdateUnusedWhilePending{};
    VkBool32                 descriptorBindingPartiallyBound{};
    VkBool32                 descriptorBindingVariableDescriptorCount{};
    VkBool32                 runtimeDescriptorArray{};
};
using VkPhysicalDeviceDescriptorIndexingFeaturesEXT = VkPhysicalDeviceDescriptorIndexingFeatures;
struct VkPhysicalDeviceDescriptorIndexingProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDescriptorIndexingProperties;
    void *                             pNext{};
    uint32_t                 maxUpdateAfterBindDescriptorsInAllPools{};
    VkBool32                 shaderUniformBufferArrayNonUniformIndexingNative{};
    VkBool32                 shaderSampledImageArrayNonUniformIndexingNative{};
    VkBool32                 shaderStorageBufferArrayNonUniformIndexingNative{};
    VkBool32                 shaderStorageImageArrayNonUniformIndexingNative{};
    VkBool32                 shaderInputAttachmentArrayNonUniformIndexingNative{};
    VkBool32                 robustBufferAccessUpdateAfterBind{};
    VkBool32                 quadDivergentImplicitLod{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindSamplers{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindUniformBuffers{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindStorageBuffers{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindSampledImages{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindStorageImages{};
    uint32_t                 maxPerStageDescriptorUpdateAfterBindInputAttachments{};
    uint32_t                 maxPerStageUpdateAfterBindResources{};
    uint32_t                 maxDescriptorSetUpdateAfterBindSamplers{};
    uint32_t                 maxDescriptorSetUpdateAfterBindUniformBuffers{};
    uint32_t                 maxDescriptorSetUpdateAfterBindUniformBuffersDynamic{};
    uint32_t                 maxDescriptorSetUpdateAfterBindStorageBuffers{};
    uint32_t                 maxDescriptorSetUpdateAfterBindStorageBuffersDynamic{};
    uint32_t                 maxDescriptorSetUpdateAfterBindSampledImages{};
    uint32_t                 maxDescriptorSetUpdateAfterBindStorageImages{};
    uint32_t                 maxDescriptorSetUpdateAfterBindInputAttachments{};
};
using VkPhysicalDeviceDescriptorIndexingPropertiesEXT = VkPhysicalDeviceDescriptorIndexingProperties;
struct VkDescriptorSetLayoutBindingFlagsCreateInfo {
    VkStructureType   sType = VkStructureType::DescriptorSetLayoutBindingFlagsCreateInfo;
    const  void *                                                         pNext{};
    uint32_t                                             bindingCount{};
    const  VkDescriptorBindingFlags *  pBindingFlags{};
};
using VkDescriptorSetLayoutBindingFlagsCreateInfoEXT = VkDescriptorSetLayoutBindingFlagsCreateInfo;
struct VkDescriptorSetVariableDescriptorCountAllocateInfo {
    VkStructureType   sType = VkStructureType::DescriptorSetVariableDescriptorCountAllocateInfo;
    const  void *                             pNext{};
    uint32_t                 descriptorSetCount{};
    const  uint32_t *  pDescriptorCounts{};
};
using VkDescriptorSetVariableDescriptorCountAllocateInfoEXT = VkDescriptorSetVariableDescriptorCountAllocateInfo;
struct VkDescriptorSetVariableDescriptorCountLayoutSupport {
    VkStructureType   sType = VkStructureType::DescriptorSetVariableDescriptorCountLayoutSupport;
    void *             pNext{};
    uint32_t           maxVariableDescriptorCount{};
};
using VkDescriptorSetVariableDescriptorCountLayoutSupportEXT = VkDescriptorSetVariableDescriptorCountLayoutSupport;
struct VkAttachmentDescription2 {
    VkStructureType   sType = VkStructureType::AttachmentDescription2;
    const  void *             pNext{};
    VkAttachmentDescriptionFlags   flags{};
    VkFormat                                       format{};
    VkSampleCountFlagBits                          samples{};
    VkAttachmentLoadOp                             loadOp{};
    VkAttachmentStoreOp                            storeOp{};
    VkAttachmentLoadOp                             stencilLoadOp{};
    VkAttachmentStoreOp                            stencilStoreOp{};
    VkImageLayout                                  initialLayout{};
    VkImageLayout                                  finalLayout{};
};
using VkAttachmentDescription2KHR = VkAttachmentDescription2;
struct VkAttachmentReference2 {
    VkStructureType   sType = VkStructureType::AttachmentReference2;
    const  void *  pNext{};
    uint32_t                            attachment{};
    VkImageLayout                       layout{};
    VkImageAspectFlags   aspectMask{};
};
using VkAttachmentReference2KHR = VkAttachmentReference2;
struct VkSubpassDescription2 {
    VkStructureType   sType = VkStructureType::SubpassDescription2;
    const  void *                            pNext{};
    VkSubpassDescriptionFlags                     flags{};
    VkPipelineBindPoint                                           pipelineBindPoint{};
    uint32_t                                                      viewMask{};
    uint32_t                                      inputAttachmentCount{};
    const  VkAttachmentReference2 *     pInputAttachments{};
    uint32_t                                      colorAttachmentCount{};
    const  VkAttachmentReference2 *     pColorAttachments{};
    const  VkAttachmentReference2 *  pResolveAttachments{};
    const  VkAttachmentReference2 *                pDepthStencilAttachment{};
    uint32_t                                      preserveAttachmentCount{};
    const  uint32_t *                pPreserveAttachments{};
};
using VkSubpassDescription2KHR = VkSubpassDescription2;
struct VkSubpassDependency2 {
    VkStructureType   sType = VkStructureType::SubpassDependency2;
    const  void *  pNext{};
    uint32_t                            srcSubpass{};
    uint32_t                            dstSubpass{};
    VkPipelineStageFlags   srcStageMask{};
    VkPipelineStageFlags   dstStageMask{};
    VkAccessFlags       srcAccessMask{};
    VkAccessFlags       dstAccessMask{};
    VkDependencyFlags   dependencyFlags{};
    int32_t                             viewOffset{};
};
using VkSubpassDependency2KHR = VkSubpassDependency2;
struct VkRenderPassCreateInfo2 {
    VkStructureType   sType = VkStructureType::RenderPassCreateInfo2;
    const  void *                                               pNext{};
    VkRenderPassCreateFlags                    flags{};
    uint32_t                                   attachmentCount{};
    const  VkAttachmentDescription2 *     pAttachments{};
    uint32_t                                                   subpassCount{};
    const  VkSubpassDescription2 *           pSubpasses{};
    uint32_t                                   dependencyCount{};
    const  VkSubpassDependency2 *         pDependencies{};
    uint32_t                                   correlatedViewMaskCount{};
    const  uint32_t *             pCorrelatedViewMasks{};
};
using VkRenderPassCreateInfo2KHR = VkRenderPassCreateInfo2;
struct VkSubpassBeginInfo {
    VkStructureType   sType = VkStructureType::SubpassBeginInfo;
    const  void *             pNext{};
    VkSubpassContents        contents{};
};
using VkSubpassBeginInfoKHR = VkSubpassBeginInfo;
struct VkSubpassEndInfo {
    VkStructureType   sType = VkStructureType::SubpassEndInfo;
    const  void *             pNext{};
};
using VkSubpassEndInfoKHR = VkSubpassEndInfo;
struct VkPhysicalDeviceTimelineSemaphoreFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTimelineSemaphoreFeatures;
    void *                   pNext{};
    VkBool32                 timelineSemaphore{};
};
using VkPhysicalDeviceTimelineSemaphoreFeaturesKHR = VkPhysicalDeviceTimelineSemaphoreFeatures;
struct VkPhysicalDeviceTimelineSemaphoreProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTimelineSemaphoreProperties;
    void *                   pNext{};
    uint64_t                 maxTimelineSemaphoreValueDifference{};
};
using VkPhysicalDeviceTimelineSemaphorePropertiesKHR = VkPhysicalDeviceTimelineSemaphoreProperties;
struct VkSemaphoreTypeCreateInfo {
    VkStructureType   sType = VkStructureType::SemaphoreTypeCreateInfo;
    const  void *             pNext{};
    VkSemaphoreType          semaphoreType{};
    uint64_t                 initialValue{};
};
using VkSemaphoreTypeCreateInfoKHR = VkSemaphoreTypeCreateInfo;
struct VkTimelineSemaphoreSubmitInfo {
    VkStructureType   sType = VkStructureType::TimelineSemaphoreSubmitInfo;
    const  void *                       pNext{};
    uint32_t           waitSemaphoreValueCount{};
    const  uint64_t *  pWaitSemaphoreValues{};
    uint32_t           signalSemaphoreValueCount{};
    const  uint64_t *  pSignalSemaphoreValues{};
};
using VkTimelineSemaphoreSubmitInfoKHR = VkTimelineSemaphoreSubmitInfo;
struct VkSemaphoreWaitInfo {
    VkStructureType   sType = VkStructureType::SemaphoreWaitInfo;
    const  void *             pNext{};
    VkSemaphoreWaitFlags   flags{};
    uint32_t                 semaphoreCount{};
    const  VkSemaphore *  pSemaphores{};
    const  uint64_t *     pValues{};
};
using VkSemaphoreWaitInfoKHR = VkSemaphoreWaitInfo;
struct VkSemaphoreSignalInfo {
    VkStructureType   sType = VkStructureType::SemaphoreSignalInfo;
    const  void *             pNext{};
    VkSemaphore              semaphore{};
    uint64_t                 value{};
};
using VkSemaphoreSignalInfoKHR = VkSemaphoreSignalInfo;
struct VkVertexInputBindingDivisorDescriptionEXT {
    uint32_t            binding{};
    uint32_t            divisor{};
};
struct VkPipelineVertexInputDivisorStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineVertexInputDivisorStateCreateInfoEXT;
    const  void *                          pNext{};
    uint32_t                              vertexBindingDivisorCount{};
    const  VkVertexInputBindingDivisorDescriptionEXT *       pVertexBindingDivisors{};
};
struct VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceVertexAttributeDivisorPropertiesEXT;
    void *                   pNext{};
    uint32_t                 maxVertexAttribDivisor{};
};
struct VkPhysicalDevicePCIBusInfoPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDevicePciBusInfoPropertiesEXT;
    void *                   pNext{};
    uint32_t                 pciDomain{};
    uint32_t                 pciBus{};
    uint32_t                 pciDevice{};
    uint32_t                 pciFunction{};
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkImportAndroidHardwareBufferInfoANDROID {
    VkStructureType   sType = VkStructureType::ImportAndroidHardwareBufferInfoANDROID;
    const  void *                         pNext{};
    struct  AHardwareBuffer *             buffer{};
};
struct VkAndroidHardwareBufferUsageANDROID {
    VkStructureType   sType = VkStructureType::AndroidHardwareBufferUsageANDROID;
    void *                               pNext{};
    uint64_t                             androidHardwareBufferUsage{};
};
struct VkAndroidHardwareBufferPropertiesANDROID {
    VkStructureType   sType = VkStructureType::AndroidHardwareBufferPropertiesANDROID;
    void *                               pNext{};
    VkDeviceSize                         allocationSize{};
    uint32_t                             memoryTypeBits{};
};
struct VkMemoryGetAndroidHardwareBufferInfoANDROID {
    VkStructureType   sType = VkStructureType::MemoryGetAndroidHardwareBufferInfoANDROID;
    const  void *                         pNext{};
    VkDeviceMemory                       memory{};
};
struct VkAndroidHardwareBufferFormatPropertiesANDROID {
    VkStructureType   sType = VkStructureType::AndroidHardwareBufferFormatPropertiesANDROID;
    void *                               pNext{};
    VkFormat                             format{};
    uint64_t                             externalFormat{};
    VkFormatFeatureFlags                 formatFeatures{};
    VkComponentMapping                   samplerYcbcrConversionComponents{};
    VkSamplerYcbcrModelConversion        suggestedYcbcrModel{};
    VkSamplerYcbcrRange                  suggestedYcbcrRange{};
    VkChromaLocation                     suggestedXChromaOffset{};
    VkChromaLocation                     suggestedYChromaOffset{};
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkCommandBufferInheritanceConditionalRenderingInfoEXT {
    VkStructureType   sType = VkStructureType::CommandBufferInheritanceConditionalRenderingInfoEXT;
    const  void *                          pNext{};
    VkBool32                              conditionalRenderingEnable{};
};
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkExternalFormatANDROID {
    VkStructureType   sType = VkStructureType::ExternalFormatANDROID;
    void *                               pNext{};
    uint64_t                             externalFormat{};
};
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
struct VkPhysicalDevice8BitStorageFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDevice8BitStorageFeatures;
    void *       pNext{};
    VkBool32                           storageBuffer8BitAccess{};
    VkBool32                           uniformAndStorageBuffer8BitAccess{};
    VkBool32                           storagePushConstant8{};
};
using VkPhysicalDevice8BitStorageFeaturesKHR = VkPhysicalDevice8BitStorageFeatures;
struct VkPhysicalDeviceConditionalRenderingFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceConditionalRenderingFeaturesEXT;
    void *         pNext{};
    VkBool32                             conditionalRendering{};
    VkBool32                             inheritedConditionalRendering{};
};
struct VkPhysicalDeviceVulkanMemoryModelFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceVulkanMemoryModelFeatures;
    void *       pNext{};
    VkBool32                           vulkanMemoryModel{};
    VkBool32                           vulkanMemoryModelDeviceScope{};
    VkBool32                           vulkanMemoryModelAvailabilityVisibilityChains{};
};
using VkPhysicalDeviceVulkanMemoryModelFeaturesKHR = VkPhysicalDeviceVulkanMemoryModelFeatures;
struct VkPhysicalDeviceShaderAtomicInt64Features {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderAtomicInt64Features;
    void *                                pNext{};
    VkBool32                              shaderBufferInt64Atomics{};
    VkBool32                              shaderSharedInt64Atomics{};
};
using VkPhysicalDeviceShaderAtomicInt64FeaturesKHR = VkPhysicalDeviceShaderAtomicInt64Features;
struct VkPhysicalDeviceShaderAtomicFloatFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderAtomicFloatFeaturesEXT;
    void *                                pNext{};
    VkBool32                              shaderBufferFloat32Atomics{};
    VkBool32                              shaderBufferFloat32AtomicAdd{};
    VkBool32                              shaderBufferFloat64Atomics{};
    VkBool32                              shaderBufferFloat64AtomicAdd{};
    VkBool32                              shaderSharedFloat32Atomics{};
    VkBool32                              shaderSharedFloat32AtomicAdd{};
    VkBool32                              shaderSharedFloat64Atomics{};
    VkBool32                              shaderSharedFloat64AtomicAdd{};
    VkBool32                              shaderImageFloat32Atomics{};
    VkBool32                              shaderImageFloat32AtomicAdd{};
    VkBool32                              sparseImageFloat32Atomics{};
    VkBool32                              sparseImageFloat32AtomicAdd{};
};
struct VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceVertexAttributeDivisorFeaturesEXT;
    void *         pNext{};
    VkBool32                             vertexAttributeInstanceRateDivisor{};
    VkBool32                             vertexAttributeInstanceRateZeroDivisor{};
};
struct VkQueueFamilyCheckpointPropertiesNV {
    VkStructureType   sType = VkStructureType::QueueFamilyCheckpointPropertiesNV;
    void *            pNext{};
    VkPipelineStageFlags   checkpointExecutionStageMask{};
};
struct VkCheckpointDataNV {
    VkStructureType   sType = VkStructureType::CheckpointDataNV;
    void *                   pNext{};
    VkPipelineStageFlagBits     stage{};
    void *  pCheckpointMarker{};
};
struct VkPhysicalDeviceDepthStencilResolveProperties {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDepthStencilResolveProperties;
    void *                                 pNext{};
    VkResolveModeFlags                     supportedDepthResolveModes{};
    VkResolveModeFlags                     supportedStencilResolveModes{};
    VkBool32                               independentResolveNone{};
    VkBool32                               independentResolve{};
};
using VkPhysicalDeviceDepthStencilResolvePropertiesKHR = VkPhysicalDeviceDepthStencilResolveProperties;
struct VkSubpassDescriptionDepthStencilResolve {
    VkStructureType   sType = VkStructureType::SubpassDescriptionDepthStencilResolve;
    const  void *                               pNext{};
    VkResolveModeFlagBits                depthResolveMode{};
    VkResolveModeFlagBits                stencilResolveMode{};
    const  VkAttachmentReference2 *             pDepthStencilResolveAttachment{};
};
using VkSubpassDescriptionDepthStencilResolveKHR = VkSubpassDescriptionDepthStencilResolve;
struct VkImageViewASTCDecodeModeEXT {
    VkStructureType   sType = VkStructureType::ImageViewAstcDecodeModeEXT;
    const  void *                       pNext{};
    VkFormat                           decodeMode{};
};
struct VkPhysicalDeviceASTCDecodeFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceAstcDecodeFeaturesEXT;
    void *       pNext{};
    VkBool32                           decodeModeSharedExponent{};
};
struct VkPhysicalDeviceTransformFeedbackFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTransformFeedbackFeaturesEXT;
    void *                   pNext{};
    VkBool32                 transformFeedback{};
    VkBool32                 geometryStreams{};
};
struct VkPhysicalDeviceTransformFeedbackPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTransformFeedbackPropertiesEXT;
    void *                   pNext{};
    uint32_t                 maxTransformFeedbackStreams{};
    uint32_t                 maxTransformFeedbackBuffers{};
    VkDeviceSize             maxTransformFeedbackBufferSize{};
    uint32_t                 maxTransformFeedbackStreamDataSize{};
    uint32_t                 maxTransformFeedbackBufferDataSize{};
    uint32_t                 maxTransformFeedbackBufferDataStride{};
    VkBool32                 transformFeedbackQueries{};
    VkBool32                 transformFeedbackStreamsLinesTriangles{};
    VkBool32                 transformFeedbackRasterizationStreamSelect{};
    VkBool32                 transformFeedbackDraw{};
};
struct VkPipelineRasterizationStateStreamCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineRasterizationStateStreamCreateInfoEXT;
    const  void *                                                                       pNext{};
    VkPipelineRasterizationStateStreamCreateFlagsEXT                   flags{};
    uint32_t                                                                           rasterizationStream{};
};
struct VkPhysicalDeviceRepresentativeFragmentTestFeaturesNV {
    VkStructureType sType = VkStructureType::PhysicalDeviceRepresentativeFragmentTestFeaturesNV;
    void *     pNext{};
    VkBool32                         representativeFragmentTest{};
};
struct VkPipelineRepresentativeFragmentTestStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineRepresentativeFragmentTestStateCreateInfoNV;
    const  void *     pNext{};
    VkBool32         representativeFragmentTestEnable{};
};
struct VkPhysicalDeviceExclusiveScissorFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExclusiveScissorFeaturesNV;
    void *                             pNext{};
    VkBool32                           exclusiveScissor{};
};
struct VkPipelineViewportExclusiveScissorStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineViewportExclusiveScissorStateCreateInfoNV;
    const  void *                                                        pNext{};
    uint32_t                                            exclusiveScissorCount{};
    const  VkRect2D *  pExclusiveScissors{};
};
struct VkPhysicalDeviceCornerSampledImageFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCornerSampledImageFeaturesNV;
    void *                               pNext{};
    VkBool32                             cornerSampledImage{};
};
struct VkPhysicalDeviceComputeShaderDerivativesFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceComputeShaderDerivativesFeaturesNV;
    void *                             pNext{};
    VkBool32                           computeDerivativeGroupQuads{};
    VkBool32                           computeDerivativeGroupLinear{};
};
struct VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShaderBarycentricFeaturesNV;
    void *                             pNext{};
    VkBool32                           fragmentShaderBarycentric{};
};
struct VkPhysicalDeviceShaderImageFootprintFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderImageFootprintFeaturesNV;
    void *                               pNext{};
    VkBool32                             imageFootprint{};
};
struct VkPhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV;
    void *                             pNext{};
    VkBool32                           dedicatedAllocationImageAliasing{};
};
struct VkShadingRatePaletteNV {
    uint32_t                                                                 shadingRatePaletteEntryCount{};
    const  VkShadingRatePaletteEntryNV *   pShadingRatePaletteEntries{};
};
struct VkPipelineViewportShadingRateImageStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineViewportShadingRateImageStateCreateInfoNV;
    const  void *                                                              pNext{};
    VkBool32                                                                  shadingRateImageEnable{};
    uint32_t                                                  viewportCount{};
    const  VkShadingRatePaletteNV *  pShadingRatePalettes{};
};
struct VkPhysicalDeviceShadingRateImageFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShadingRateImageFeaturesNV;
    void *                                pNext{};
    VkBool32                              shadingRateImage{};
    VkBool32                              shadingRateCoarseSampleOrder{};
};
struct VkPhysicalDeviceShadingRateImagePropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShadingRateImagePropertiesNV;
    void *                                pNext{};
    VkExtent2D                            shadingRateTexelSize{};
    uint32_t                              shadingRatePaletteSize{};
    uint32_t                              shadingRateMaxCoarseSamples{};
};
struct VkCoarseSampleLocationNV {
    uint32_t                              pixelX{};
    uint32_t                              pixelY{};
    uint32_t                              sample{};
};
struct VkCoarseSampleOrderCustomNV {
    VkShadingRatePaletteEntryNV           shadingRate{};
    uint32_t                              sampleCount{};
    uint32_t                              sampleLocationCount{};
    const  VkCoarseSampleLocationNV *  pSampleLocations{};
};
struct VkPipelineViewportCoarseSampleOrderStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineViewportCoarseSampleOrderStateCreateInfoNV;
    const  void *                                                             pNext{};
    VkCoarseSampleOrderTypeNV                                                sampleOrderType{};
    uint32_t                                                 customSampleOrderCount{};
    const  VkCoarseSampleOrderCustomNV *         pCustomSampleOrders{};
};
struct VkPhysicalDeviceMeshShaderFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMeshShaderFeaturesNV;
    void *                                pNext{};
    VkBool32                              taskShader{};
    VkBool32                              meshShader{};
};
struct VkPhysicalDeviceMeshShaderPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMeshShaderPropertiesNV;
    void *                                pNext{};
    uint32_t                              maxDrawMeshTasksCount{};
    uint32_t                              maxTaskWorkGroupInvocations{};
    uint32_t                              maxTaskWorkGroupSize [3]{};
    uint32_t                              maxTaskTotalMemorySize{};
    uint32_t                              maxTaskOutputCount{};
    uint32_t                              maxMeshWorkGroupInvocations{};
    uint32_t                              maxMeshWorkGroupSize [3]{};
    uint32_t                              maxMeshTotalMemorySize{};
    uint32_t                              maxMeshOutputVertices{};
    uint32_t                              maxMeshOutputPrimitives{};
    uint32_t                              maxMeshMultiviewViewCount{};
    uint32_t                              meshOutputPerVertexGranularity{};
    uint32_t                              meshOutputPerPrimitiveGranularity{};
};
struct VkDrawMeshTasksIndirectCommandNV {
    uint32_t                 taskCount{};
    uint32_t                 firstTask{};
};
struct VkRayTracingShaderGroupCreateInfoNV {
    VkStructureType   sType = VkStructureType::RayTracingShaderGroupCreateInfoNV;
    const  void *             pNext{};
    VkRayTracingShaderGroupTypeKHR   type{};
    uint32_t                 generalShader{};
    uint32_t                 closestHitShader{};
    uint32_t                 anyHitShader{};
    uint32_t                 intersectionShader{};
};
struct VkRayTracingShaderGroupCreateInfoKHR {
    VkStructureType   sType = VkStructureType::RayTracingShaderGroupCreateInfoKHR;
    const  void *             pNext{};
    VkRayTracingShaderGroupTypeKHR   type{};
    uint32_t                 generalShader{};
    uint32_t                 closestHitShader{};
    uint32_t                 anyHitShader{};
    uint32_t                 intersectionShader{};
    const  void *  pShaderGroupCaptureReplayHandle{};
};
struct VkRayTracingPipelineCreateInfoNV {
    VkStructureType   sType = VkStructureType::RayTracingPipelineCreateInfoNV;
    const  void *             pNext{};
    VkPipelineCreateFlags    flags{};
    uint32_t                 stageCount{};
    const  VkPipelineShaderStageCreateInfo *  pStages{};
    uint32_t                 groupCount{};
    const  VkRayTracingShaderGroupCreateInfoNV *  pGroups{};
    uint32_t                 maxRecursionDepth{};
    VkPipelineLayout         layout{};
    VkPipeline        basePipelineHandle{};
    int32_t                  basePipelineIndex{};
};
struct VkRayTracingPipelineInterfaceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::RayTracingPipelineInterfaceCreateInfoKHR;
    const  void *                             pNext{};
    uint32_t                                                 maxPipelineRayPayloadSize{};
    uint32_t                                                 maxPipelineRayHitAttributeSize{};
};
struct VkPipelineLibraryCreateInfoKHR {
    VkStructureType   sType = VkStructureType::PipelineLibraryCreateInfoKHR;
    const  void *                                             pNext{};
    uint32_t                                 libraryCount{};
    const  VkPipeline *                    pLibraries{};
};
struct VkRayTracingPipelineCreateInfoKHR {
    VkStructureType   sType = VkStructureType::RayTracingPipelineCreateInfoKHR;
    const  void *             pNext{};
    VkPipelineCreateFlags    flags{};
    uint32_t   stageCount{};
    const  VkPipelineShaderStageCreateInfo *  pStages{};
    uint32_t   groupCount{};
    const  VkRayTracingShaderGroupCreateInfoKHR *  pGroups{};
    uint32_t                 maxPipelineRayRecursionDepth{};
    const  VkPipelineLibraryCreateInfoKHR *  pLibraryInfo{};
    const  VkRayTracingPipelineInterfaceCreateInfoKHR *  pLibraryInterface{};
    const  VkPipelineDynamicStateCreateInfo *  pDynamicState{};
    VkPipelineLayout         layout{};
    VkPipeline        basePipelineHandle{};
    int32_t                  basePipelineIndex{};
};
struct VkGeometryTrianglesNV {
    VkStructureType   sType = VkStructureType::GeometryTrianglesNV;
    const  void *                 pNext{};
    VkBuffer     vertexData{};
    VkDeviceSize                 vertexOffset{};
    uint32_t                     vertexCount{};
    VkDeviceSize                 vertexStride{};
    VkFormat                     vertexFormat{};
    VkBuffer     indexData{};
    VkDeviceSize                 indexOffset{};
    uint32_t                     indexCount{};
    VkIndexType                  indexType{};
    VkBuffer     transformData{};
    VkDeviceSize                 transformOffset{};
};
struct VkGeometryAABBNV {
    VkStructureType   sType = VkStructureType::GeometryAabbNV;
    const  void *                 pNext{};
    VkBuffer     aabbData{};
    uint32_t                     numAABBs{};
    uint32_t                     stride{};
    VkDeviceSize                 offset{};
};
struct VkGeometryDataNV {
    VkGeometryTrianglesNV                    triangles{};
    VkGeometryAABBNV                         aabbs{};
};
struct VkGeometryNV {
    VkStructureType   sType = VkStructureType::GeometryNV;
    const  void *                                    pNext{};
    VkGeometryTypeKHR                    geometryType{};
    VkGeometryDataNV                                geometry{};
    VkGeometryFlagsKHR   flags{};
};
struct VkAccelerationStructureInfoNV {
    VkStructureType   sType = VkStructureType::AccelerationStructureInfoNV;
    const  void *                             pNext{};
    VkAccelerationStructureTypeNV           type{};
    VkBuildAccelerationStructureFlagsNV flags{};
    uint32_t                 instanceCount{};
    uint32_t                 geometryCount{};
    const  VkGeometryNV *  pGeometries{};
};
struct VkAccelerationStructureCreateInfoNV {
    VkStructureType   sType = VkStructureType::AccelerationStructureCreateInfoNV;
    const  void *                             pNext{};
    VkDeviceSize                             compactedSize{};
    VkAccelerationStructureInfoNV            info{};
};
struct VkBindAccelerationStructureMemoryInfoNV {
    VkStructureType   sType = VkStructureType::BindAccelerationStructureMemoryInfoNV;
    const  void *      pNext{};
    VkAccelerationStructureNV         accelerationStructure{};
    VkDeviceMemory                     memory{};
    VkDeviceSize                       memoryOffset{};
    uint32_t           deviceIndexCount{};
    const  uint32_t *   pDeviceIndices{};
};
struct VkWriteDescriptorSetAccelerationStructureKHR {
    VkStructureType   sType = VkStructureType::WriteDescriptorSetAccelerationStructureKHR;
    const  void *                       pNext{};
    uint32_t                           accelerationStructureCount{};
    const  VkAccelerationStructureKHR *  pAccelerationStructures{};
};
struct VkWriteDescriptorSetAccelerationStructureNV {
    VkStructureType   sType = VkStructureType::WriteDescriptorSetAccelerationStructureNV;
    const  void *       pNext{};
    uint32_t                           accelerationStructureCount{};
    const  VkAccelerationStructureNV *  pAccelerationStructures{};
};
struct VkAccelerationStructureMemoryRequirementsInfoNV {
    VkStructureType   sType = VkStructureType::AccelerationStructureMemoryRequirementsInfoNV;
    const  void *                                                           pNext{};
    VkAccelerationStructureMemoryRequirementsTypeNV                       type{};
    VkAccelerationStructureNV                                             accelerationStructure{};
};
struct VkPhysicalDeviceAccelerationStructureFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceAccelerationStructureFeaturesKHR;
    void *                             pNext{};
    VkBool32                           accelerationStructure{};
    VkBool32                           accelerationStructureCaptureReplay{};
    VkBool32                           accelerationStructureIndirectBuild{};
    VkBool32                           accelerationStructureHostCommands{};
    VkBool32                           descriptorBindingAccelerationStructureUpdateAfterBind{};
};
struct VkPhysicalDeviceRayTracingPipelineFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRayTracingPipelineFeaturesKHR;
    void *             pNext{};
    VkBool32                           rayTracingPipeline{};
    VkBool32                           rayTracingPipelineShaderGroupHandleCaptureReplay{};
    VkBool32                           rayTracingPipelineShaderGroupHandleCaptureReplayMixed{};
    VkBool32                           rayTracingPipelineTraceRaysIndirect{};
    VkBool32                           rayTraversalPrimitiveCulling{};
};
struct VkPhysicalDeviceRayQueryFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRayQueryFeaturesKHR;
    void *             pNext{};
    VkBool32                           rayQuery{};
};
struct VkPhysicalDeviceAccelerationStructurePropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceAccelerationStructurePropertiesKHR;
    void *             pNext{};
    uint64_t                           maxGeometryCount{};
    uint64_t                           maxInstanceCount{};
    uint64_t                           maxPrimitiveCount{};
    uint32_t                           maxPerStageDescriptorAccelerationStructures{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindAccelerationStructures{};
    uint32_t                           maxDescriptorSetAccelerationStructures{};
    uint32_t                           maxDescriptorSetUpdateAfterBindAccelerationStructures{};
    uint32_t                           minAccelerationStructureScratchOffsetAlignment{};
};
struct VkPhysicalDeviceRayTracingPipelinePropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRayTracingPipelinePropertiesKHR;
    void *             pNext{};
    uint32_t                           shaderGroupHandleSize{};
    uint32_t                           maxRayRecursionDepth{};
    uint32_t                           maxShaderGroupStride{};
    uint32_t                           shaderGroupBaseAlignment{};
    uint32_t                           shaderGroupHandleCaptureReplaySize{};
    uint32_t                           maxRayDispatchInvocationCount{};
    uint32_t                           shaderGroupHandleAlignment{};
    uint32_t                           maxRayHitAttributeSize{};
};
struct VkPhysicalDeviceRayTracingPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRayTracingPropertiesNV;
    void *                             pNext{};
    uint32_t                           shaderGroupHandleSize{};
    uint32_t                           maxRecursionDepth{};
    uint32_t                           maxShaderGroupStride{};
    uint32_t                           shaderGroupBaseAlignment{};
    uint64_t                           maxGeometryCount{};
    uint64_t                           maxInstanceCount{};
    uint64_t                           maxTriangleCount{};
    uint32_t                           maxDescriptorSetAccelerationStructures{};
};
struct VkStridedDeviceAddressRegionKHR {
    VkDeviceAddress    deviceAddress{};
    VkDeviceSize                       stride{};
    VkDeviceSize                       size{};
};
struct VkTraceRaysIndirectCommandKHR {
    uint32_t                 width{};
    uint32_t                 height{};
    uint32_t                 depth{};
};
struct VkDrmFormatModifierPropertiesEXT {
    uint64_t   drmFormatModifier{};
    uint32_t   drmFormatModifierPlaneCount{};
    VkFormatFeatureFlags   drmFormatModifierTilingFeatures{};
};
struct VkDrmFormatModifierPropertiesListEXT {
    VkStructureType   sType = VkStructureType::DrmFormatModifierPropertiesListEXT;
    void *  pNext{};
    uint32_t   drmFormatModifierCount{};
    VkDrmFormatModifierPropertiesEXT *  pDrmFormatModifierProperties{};
};
struct VkPhysicalDeviceImageDrmFormatModifierInfoEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceImageDrmFormatModifierInfoEXT;
    const  void *  pNext{};
    uint64_t   drmFormatModifier{};
    VkSharingMode   sharingMode{};
    uint32_t   queueFamilyIndexCount{};
    const  uint32_t *  pQueueFamilyIndices{};
};
struct VkImageDrmFormatModifierListCreateInfoEXT {
    VkStructureType   sType = VkStructureType::ImageDrmFormatModifierListCreateInfoEXT;
    const  void *  pNext{};
    uint32_t   drmFormatModifierCount{};
    const  uint64_t *  pDrmFormatModifiers{};
};
struct VkImageDrmFormatModifierExplicitCreateInfoEXT {
    VkStructureType   sType = VkStructureType::ImageDrmFormatModifierExplicitCreateInfoEXT;
    const  void *  pNext{};
    uint64_t   drmFormatModifier{};
    uint32_t   drmFormatModifierPlaneCount{};
    const  VkSubresourceLayout *  pPlaneLayouts{};
};
struct VkImageDrmFormatModifierPropertiesEXT {
    VkStructureType   sType = VkStructureType::ImageDrmFormatModifierPropertiesEXT;
    void *  pNext{};
    uint64_t   drmFormatModifier{};
};
struct VkImageStencilUsageCreateInfo {
    VkStructureType   sType = VkStructureType::ImageStencilUsageCreateInfo;
    const  void *  pNext{};
    VkImageUsageFlags   stencilUsage{};
};
using VkImageStencilUsageCreateInfoEXT = VkImageStencilUsageCreateInfo;
struct VkDeviceMemoryOverallocationCreateInfoAMD {
    VkStructureType   sType = VkStructureType::DeviceMemoryOverallocationCreateInfoAMD;
    const  void *                       pNext{};
    VkMemoryOverallocationBehaviorAMD   overallocationBehavior{};
};
struct VkPhysicalDeviceFragmentDensityMapFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentDensityMapFeaturesEXT;
    void *                             pNext{};
    VkBool32                           fragmentDensityMap{};
    VkBool32                           fragmentDensityMapDynamic{};
    VkBool32                           fragmentDensityMapNonSubsampledImages{};
};
struct VkPhysicalDeviceFragmentDensityMap2FeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentDensityMap2FeaturesEXT;
    void *                             pNext{};
    VkBool32                           fragmentDensityMapDeferred{};
};
struct VkPhysicalDeviceFragmentDensityMapPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentDensityMapPropertiesEXT;
    void *                             pNext{};
    VkExtent2D                         minFragmentDensityTexelSize{};
    VkExtent2D                         maxFragmentDensityTexelSize{};
    VkBool32                           fragmentDensityInvocations{};
};
struct VkPhysicalDeviceFragmentDensityMap2PropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentDensityMap2PropertiesEXT;
    void *                           pNext{};
    VkBool32                         subsampledLoads{};
    VkBool32                         subsampledCoarseReconstructionEarlyAccess{};
    uint32_t                         maxSubsampledArrayLayers{};
    uint32_t                         maxDescriptorSetSubsampledSamplers{};
};
struct VkRenderPassFragmentDensityMapCreateInfoEXT {
    VkStructureType   sType = VkStructureType::RenderPassFragmentDensityMapCreateInfoEXT;
    const  void *                       pNext{};
    VkAttachmentReference              fragmentDensityMapAttachment{};
};
struct VkPhysicalDeviceScalarBlockLayoutFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceScalarBlockLayoutFeatures;
    void *                                pNext{};
    VkBool32                              scalarBlockLayout{};
};
using VkPhysicalDeviceScalarBlockLayoutFeaturesEXT = VkPhysicalDeviceScalarBlockLayoutFeatures;
struct VkSurfaceProtectedCapabilitiesKHR {
    VkStructureType   sType = VkStructureType::SurfaceProtectedCapabilitiesKHR;
    const  void *  pNext{};
    VkBool32   supportsProtected{};
};
struct VkPhysicalDeviceUniformBufferStandardLayoutFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceUniformBufferStandardLayoutFeatures;
    void *                                pNext{};
    VkBool32                              uniformBufferStandardLayout{};
};
using VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR = VkPhysicalDeviceUniformBufferStandardLayoutFeatures;
struct VkPhysicalDeviceDepthClipEnableFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceDepthClipEnableFeaturesEXT;
    void *                   pNext{};
    VkBool32                 depthClipEnable{};
};
struct VkPipelineRasterizationDepthClipStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineRasterizationDepthClipStateCreateInfoEXT;
    const  void *                                                                  pNext{};
    VkPipelineRasterizationDepthClipStateCreateFlagsEXT           flags{};
    VkBool32                                                                      depthClipEnable{};
};
struct VkPhysicalDeviceMemoryBudgetPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMemoryBudgetPropertiesEXT;
    void *         pNext{};
    VkDeviceSize                         heapBudget [ VK_MAX_MEMORY_HEAPS ]{};
    VkDeviceSize                         heapUsage [ VK_MAX_MEMORY_HEAPS ]{};
};
struct VkPhysicalDeviceMemoryPriorityFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMemoryPriorityFeaturesEXT;
    void *         pNext{};
    VkBool32                             memoryPriority{};
};
struct VkMemoryPriorityAllocateInfoEXT {
    VkStructureType   sType = VkStructureType::MemoryPriorityAllocateInfoEXT;
    const  void *                         pNext{};
    float                                priority{};
};
struct VkPhysicalDeviceBufferDeviceAddressFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceBufferDeviceAddressFeatures;
    void *         pNext{};
    VkBool32                             bufferDeviceAddress{};
    VkBool32                             bufferDeviceAddressCaptureReplay{};
    VkBool32                             bufferDeviceAddressMultiDevice{};
};
using VkPhysicalDeviceBufferDeviceAddressFeaturesKHR = VkPhysicalDeviceBufferDeviceAddressFeatures;
struct VkPhysicalDeviceBufferDeviceAddressFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceBufferDeviceAddressFeaturesEXT;
    void *         pNext{};
    VkBool32                             bufferDeviceAddress{};
    VkBool32                             bufferDeviceAddressCaptureReplay{};
    VkBool32                             bufferDeviceAddressMultiDevice{};
};
using VkPhysicalDeviceBufferAddressFeaturesEXT = VkPhysicalDeviceBufferDeviceAddressFeaturesEXT;
struct VkBufferDeviceAddressInfo {
    VkStructureType   sType = VkStructureType::BufferDeviceAddressInfo;
    const  void *                                             pNext{};
    VkBuffer                                                 buffer{};
};
using VkBufferDeviceAddressInfoKHR = VkBufferDeviceAddressInfo;
using VkBufferDeviceAddressInfoEXT = VkBufferDeviceAddressInfo;
struct VkBufferOpaqueCaptureAddressCreateInfo {
    VkStructureType   sType = VkStructureType::BufferOpaqueCaptureAddressCreateInfo;
    const  void *                       pNext{};
    uint64_t                           opaqueCaptureAddress{};
};
using VkBufferOpaqueCaptureAddressCreateInfoKHR = VkBufferOpaqueCaptureAddressCreateInfo;
struct VkBufferDeviceAddressCreateInfoEXT {
    VkStructureType   sType = VkStructureType::BufferDeviceAddressCreateInfoEXT;
    const  void *                       pNext{};
    VkDeviceAddress                    deviceAddress{};
};
struct VkPhysicalDeviceImageViewImageFormatInfoEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceImageViewImageFormatInfoEXT;
    void *                             pNext{};
    VkImageViewType                    imageViewType{};
};
struct VkFilterCubicImageViewImageFormatPropertiesEXT {
    VkStructureType   sType = VkStructureType::FilterCubicImageViewImageFormatPropertiesEXT;
    void *                             pNext{};
    VkBool32                           filterCubic{};
    VkBool32                           filterCubicMinmax{};
};
struct VkPhysicalDeviceImagelessFramebufferFeatures {
    VkStructureType   sType = VkStructureType::PhysicalDeviceImagelessFramebufferFeatures;
    void *                                     pNext{};
    VkBool32                                   imagelessFramebuffer{};
};
using VkPhysicalDeviceImagelessFramebufferFeaturesKHR = VkPhysicalDeviceImagelessFramebufferFeatures;
struct VkFramebufferAttachmentImageInfo {
    VkStructureType   sType = VkStructureType::FramebufferAttachmentImageInfo;
    const  void *                               pNext{};
    VkImageCreateFlags         flags{};
    VkImageUsageFlags                          usage{};
    uint32_t                                   width{};
    uint32_t                                   height{};
    uint32_t                                   layerCount{};
    uint32_t                   viewFormatCount{};
    const  VkFormat *     pViewFormats{};
};
struct VkFramebufferAttachmentsCreateInfo {
    VkStructureType   sType = VkStructureType::FramebufferAttachmentsCreateInfo;
    const  void *                               pNext{};
    uint32_t                   attachmentImageInfoCount{};
    const  VkFramebufferAttachmentImageInfo *  pAttachmentImageInfos{};
};
using VkFramebufferAttachmentsCreateInfoKHR = VkFramebufferAttachmentsCreateInfo;
using VkFramebufferAttachmentImageInfoKHR = VkFramebufferAttachmentImageInfo;
struct VkRenderPassAttachmentBeginInfo {
    VkStructureType   sType = VkStructureType::RenderPassAttachmentBeginInfo;
    const  void *                               pNext{};
    uint32_t                   attachmentCount{};
    const  VkImageView *  pAttachments{};
};
using VkRenderPassAttachmentBeginInfoKHR = VkRenderPassAttachmentBeginInfo;
struct VkPhysicalDeviceTextureCompressionASTCHDRFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTextureCompressionAstcHdrFeaturesEXT;
    void *                   pNext{};
    VkBool32                 textureCompressionASTC_HDR{};
};
struct VkPhysicalDeviceCooperativeMatrixFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCooperativeMatrixFeaturesNV;
    void *                                pNext{};
    VkBool32                              cooperativeMatrix{};
    VkBool32                              cooperativeMatrixRobustBufferAccess{};
};
struct VkPhysicalDeviceCooperativeMatrixPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCooperativeMatrixPropertiesNV;
    void *                                pNext{};
    VkShaderStageFlags                    cooperativeMatrixSupportedStages{};
};
struct VkCooperativeMatrixPropertiesNV {
    VkStructureType   sType = VkStructureType::CooperativeMatrixPropertiesNV;
    void *                                pNext{};
    uint32_t                              MSize{};
    uint32_t                              NSize{};
    uint32_t                              KSize{};
    VkComponentTypeNV                     AType{};
    VkComponentTypeNV                     BType{};
    VkComponentTypeNV                     CType{};
    VkComponentTypeNV                     DType{};
    VkScopeNV                             scope{};
};
struct VkPhysicalDeviceYcbcrImageArraysFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceYcbcrImageArraysFeaturesEXT;
    void *         pNext{};
    VkBool32                             ycbcrImageArrays{};
};
struct VkImageViewHandleInfoNVX {
    VkStructureType   sType = VkStructureType::ImageViewHandleInfoNVX;
    const  void *             pNext{};
    VkImageView                           imageView{};
    VkDescriptorType                      descriptorType{};
    VkSampler             sampler{};
};
struct VkImageViewAddressPropertiesNVX {
    VkStructureType   sType = VkStructureType::ImageViewAddressPropertiesNVX;
    void *               pNext{};
    VkDeviceAddress      deviceAddress{};
    VkDeviceSize         size{};
};
#if defined(VK_USE_PLATFORM_GGP)
struct VkPresentFrameTokenGGP {
    VkStructureType   sType = VkStructureType::PresentFrameTokenGGP;
    const  void *                       pNext{};
    GgpFrameToken                      frameToken{};
};
#endif // defined(VK_USE_PLATFORM_GGP)
struct VkPipelineCreationFeedbackEXT {
    VkPipelineCreationFeedbackFlagsEXT    flags{};
    uint64_t                              duration{};
};
struct VkPipelineCreationFeedbackCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineCreationFeedbackCreateInfoEXT;
    const  void *                          pNext{};
    VkPipelineCreationFeedbackEXT *       pPipelineCreationFeedback{};
    uint32_t                              pipelineStageCreationFeedbackCount{};
    VkPipelineCreationFeedbackEXT *  pPipelineStageCreationFeedbacks{};
};
#if defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkSurfaceFullScreenExclusiveInfoEXT {
    VkStructureType   sType = VkStructureType::SurfaceFullScreenExclusiveInfoEXT;
    void *                             pNext{};
    VkFullScreenExclusiveEXT           fullScreenExclusive{};
};
struct VkSurfaceFullScreenExclusiveWin32InfoEXT {
    VkStructureType   sType = VkStructureType::SurfaceFullScreenExclusiveWin32InfoEXT;
    const  void *       pNext{};
    HMONITOR           hmonitor{};
};
struct VkSurfaceCapabilitiesFullScreenExclusiveEXT {
    VkStructureType   sType = VkStructureType::SurfaceCapabilitiesFullScreenExclusiveEXT;
    void *             pNext{};
    VkBool32           fullScreenExclusiveSupported{};
};
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
struct VkPhysicalDevicePerformanceQueryFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePerformanceQueryFeaturesKHR;
    void *       pNext{};
    VkBool32                           performanceCounterQueryPools{};
    VkBool32                           performanceCounterMultipleQueryPools{};
};
struct VkPhysicalDevicePerformanceQueryPropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePerformanceQueryPropertiesKHR;
    void *  pNext{};
    VkBool32   allowCommandBufferQueryCopies{};
};
struct VkPerformanceCounterKHR {
    VkStructureType   sType = VkStructureType::PerformanceCounterKHR;
    const  void *                              pNext{};
    VkPerformanceCounterUnitKHR          unit{};
    VkPerformanceCounterScopeKHR         scope{};
    VkPerformanceCounterStorageKHR       storage{};
    uint8_t   uuid [ VK_UUID_SIZE ]{};
};
struct VkPerformanceCounterDescriptionKHR {
    VkStructureType   sType = VkStructureType::PerformanceCounterDescriptionKHR;
    const  void *                              pNext{};
    VkPerformanceCounterDescriptionFlagsKHR   flags{};
    char                                      name [ VK_MAX_DESCRIPTION_SIZE ]{};
    char                                      category [ VK_MAX_DESCRIPTION_SIZE ]{};
    char                                      description [ VK_MAX_DESCRIPTION_SIZE ]{};
};
struct VkQueryPoolPerformanceCreateInfoKHR {
    VkStructureType   sType = VkStructureType::QueryPoolPerformanceCreateInfoKHR;
    const  void *                              pNext{};
    uint32_t                                  queueFamilyIndex{};
    uint32_t                                  counterIndexCount{};
    const  uint32_t *  pCounterIndices{};
};
union VkPerformanceCounterResultKHR {
    int32_t    int32;
    int64_t    int64;
    uint32_t   uint32;
    uint64_t   uint64;
    float      float32;
    double     float64;
};
struct VkAcquireProfilingLockInfoKHR {
    VkStructureType   sType = VkStructureType::AcquireProfilingLockInfoKHR;
    const  void *             pNext{};
    VkAcquireProfilingLockFlagsKHR   flags{};
    uint64_t   timeout{};
};
struct VkPerformanceQuerySubmitInfoKHR {
    VkStructureType   sType = VkStructureType::PerformanceQuerySubmitInfoKHR;
    const  void *          pNext{};
    uint32_t              counterPassIndex{};
};
struct VkHeadlessSurfaceCreateInfoEXT {
    VkStructureType   sType = VkStructureType::HeadlessSurfaceCreateInfoEXT;
    const  void *             pNext{};
    VkHeadlessSurfaceCreateFlagsEXT     flags{};
};
struct VkPhysicalDeviceCoverageReductionModeFeaturesNV {
    VkStructureType sType = VkStructureType::PhysicalDeviceCoverageReductionModeFeaturesNV;
    void *     pNext{};
    VkBool32                         coverageReductionMode{};
};
struct VkPipelineCoverageReductionStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineCoverageReductionStateCreateInfoNV;
    const  void *                                                         pNext{};
    VkPipelineCoverageReductionStateCreateFlagsNV        flags{};
    VkCoverageReductionModeNV                                            coverageReductionMode{};
};
struct VkFramebufferMixedSamplesCombinationNV {
    VkStructureType   sType = VkStructureType::FramebufferMixedSamplesCombinationNV;
    void *                       pNext{};
    VkCoverageReductionModeNV    coverageReductionMode{};
    VkSampleCountFlagBits        rasterizationSamples{};
    VkSampleCountFlags           depthStencilSamples{};
    VkSampleCountFlags           colorSamples{};
};
struct VkPhysicalDeviceShaderIntegerFunctions2FeaturesINTEL {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL;
    void *                             pNext{};
    VkBool32                           shaderIntegerFunctions2{};
};
union VkPerformanceValueDataINTEL {
    uint32_t                             value32;
    uint64_t                             value64;
    float                                 valueFloat;
    VkBool32                               valueBool;
    const  char *   valueString;
};
struct VkPerformanceValueINTEL {
    VkPerformanceValueTypeINTEL          type{};
    VkPerformanceValueDataINTEL          data{};
};
struct VkInitializePerformanceApiInfoINTEL {
    VkStructureType   sType = VkStructureType::InitializePerformanceApiInfoINTEL;
    const  void *                          pNext{};
    void *                pUserData{};
};
struct VkQueryPoolPerformanceQueryCreateInfoINTEL {
    VkStructureType   sType = VkStructureType::QueryPoolPerformanceQueryCreateInfoINTEL;
    const  void *                          pNext{};
    VkQueryPoolSamplingModeINTEL          performanceCountersSampling{};
};
using VkQueryPoolCreateInfoINTEL = VkQueryPoolPerformanceQueryCreateInfoINTEL;
struct VkPerformanceMarkerInfoINTEL {
    VkStructureType   sType = VkStructureType::PerformanceMarkerInfoINTEL;
    const  void *                          pNext{};
    uint64_t                              marker{};
};
struct VkPerformanceStreamMarkerInfoINTEL {
    VkStructureType   sType = VkStructureType::PerformanceStreamMarkerInfoINTEL;
    const  void *                          pNext{};
    uint32_t                              marker{};
};
struct VkPerformanceOverrideInfoINTEL {
    VkStructureType   sType = VkStructureType::PerformanceOverrideInfoINTEL;
    const  void *                          pNext{};
    VkPerformanceOverrideTypeINTEL        type{};
    VkBool32                              enable{};
    uint64_t                              parameter{};
};
struct VkPerformanceConfigurationAcquireInfoINTEL {
    VkStructureType   sType = VkStructureType::PerformanceConfigurationAcquireInfoINTEL;
    const  void *                          pNext{};
    VkPerformanceConfigurationTypeINTEL   type{};
};
struct VkPhysicalDeviceShaderClockFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderClockFeaturesKHR;
    void *                                pNext{};
    VkBool32                              shaderSubgroupClock{};
    VkBool32                              shaderDeviceClock{};
};
struct VkPhysicalDeviceIndexTypeUint8FeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceIndexTypeUint8FeaturesEXT;
    void *         pNext{};
    VkBool32                             indexTypeUint8{};
};
struct VkPhysicalDeviceShaderSMBuiltinsPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderSmBuiltinsPropertiesNV;
    void *                           pNext{};
    uint32_t                         shaderSMCount{};
    uint32_t                         shaderWarpsPerSM{};
};
struct VkPhysicalDeviceShaderSMBuiltinsFeaturesNV {
    VkStructureType sType = VkStructureType::PhysicalDeviceShaderSmBuiltinsFeaturesNV;
    void *     pNext{};
    VkBool32                         shaderSMBuiltins{};
};
struct VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShaderInterlockFeaturesEXT;
    void *                   pNext{};
    VkBool32                 fragmentShaderSampleInterlock{};
    VkBool32                 fragmentShaderPixelInterlock{};
    VkBool32                 fragmentShaderShadingRateInterlock{};
};
struct VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures {
    VkStructureType sType = VkStructureType::PhysicalDeviceSeparateDepthStencilLayoutsFeatures;
    void *     pNext{};
    VkBool32                         separateDepthStencilLayouts{};
};
using VkPhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR = VkPhysicalDeviceSeparateDepthStencilLayoutsFeatures;
struct VkAttachmentReferenceStencilLayout {
    VkStructureType sType = VkStructureType::AttachmentReferenceStencilLayout;
    void *     pNext{};
    VkImageLayout                    stencilLayout{};
};
using VkAttachmentReferenceStencilLayoutKHR = VkAttachmentReferenceStencilLayout;
struct VkAttachmentDescriptionStencilLayout {
    VkStructureType sType = VkStructureType::AttachmentDescriptionStencilLayout;
    void *     pNext{};
    VkImageLayout                    stencilInitialLayout{};
    VkImageLayout                    stencilFinalLayout{};
};
using VkAttachmentDescriptionStencilLayoutKHR = VkAttachmentDescriptionStencilLayout;
struct VkPhysicalDevicePipelineExecutablePropertiesFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePipelineExecutablePropertiesFeaturesKHR;
    void *               pNext{};
    VkBool32             pipelineExecutableInfo{};
};
struct VkPipelineInfoKHR {
    VkStructureType   sType = VkStructureType::PipelineInfoKHR;
    const  void *         pNext{};
    VkPipeline           pipeline{};
};
struct VkPipelineExecutablePropertiesKHR {
    VkStructureType   sType = VkStructureType::PipelineExecutablePropertiesKHR;
    void *               pNext{};
    VkShaderStageFlags   stages{};
    char                 name [ VK_MAX_DESCRIPTION_SIZE ]{};
    char                 description [ VK_MAX_DESCRIPTION_SIZE ]{};
    uint32_t             subgroupSize{};
};
struct VkPipelineExecutableInfoKHR {
    VkStructureType   sType = VkStructureType::PipelineExecutableInfoKHR;
    const  void *         pNext{};
    VkPipeline           pipeline{};
    uint32_t             executableIndex{};
};
union VkPipelineExecutableStatisticValueKHR {
    VkBool32             b32;
    int64_t              i64;
    uint64_t             u64;
    double               f64;
};
struct VkPipelineExecutableStatisticKHR {
    VkStructureType   sType = VkStructureType::PipelineExecutableStatisticKHR;
    void *               pNext{};
    char                 name [ VK_MAX_DESCRIPTION_SIZE ]{};
    char                 description [ VK_MAX_DESCRIPTION_SIZE ]{};
    VkPipelineExecutableStatisticFormatKHR   format{};
    VkPipelineExecutableStatisticValueKHR    value{};
};
struct VkPipelineExecutableInternalRepresentationKHR {
    VkStructureType   sType = VkStructureType::PipelineExecutableInternalRepresentationKHR;
    void *               pNext{};
    char                 name [ VK_MAX_DESCRIPTION_SIZE ]{};
    char                 description [ VK_MAX_DESCRIPTION_SIZE ]{};
    VkBool32             isText{};
    size_t               dataSize{};
    void *  pData{};
};
struct VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT;
    void *         pNext{};
    VkBool32                             shaderDemoteToHelperInvocation{};
};
struct VkPhysicalDeviceTexelBufferAlignmentFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTexelBufferAlignmentFeaturesEXT;
    void *         pNext{};
    VkBool32                             texelBufferAlignment{};
};
struct VkPhysicalDeviceTexelBufferAlignmentPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceTexelBufferAlignmentPropertiesEXT;
    void *               pNext{};
    VkDeviceSize                         storageTexelBufferOffsetAlignmentBytes{};
    VkBool32                             storageTexelBufferOffsetSingleTexelAlignment{};
    VkDeviceSize                         uniformTexelBufferOffsetAlignmentBytes{};
    VkBool32                             uniformTexelBufferOffsetSingleTexelAlignment{};
};
struct VkPhysicalDeviceSubgroupSizeControlFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSubgroupSizeControlFeaturesEXT;
    void *                           pNext{};
    VkBool32   subgroupSizeControl{};
    VkBool32   computeFullSubgroups{};
};
struct VkPhysicalDeviceSubgroupSizeControlPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSubgroupSizeControlPropertiesEXT;
    void *                           pNext{};
    uint32_t   minSubgroupSize{};
    uint32_t   maxSubgroupSize{};
    uint32_t   maxComputeWorkgroupSubgroups{};
    VkShaderStageFlags               requiredSubgroupSizeStages{};
};
struct VkPipelineShaderStageRequiredSubgroupSizeCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT;
    void *                   pNext{};
    uint32_t                 requiredSubgroupSize{};
};
struct VkMemoryOpaqueCaptureAddressAllocateInfo {
    VkStructureType   sType = VkStructureType::MemoryOpaqueCaptureAddressAllocateInfo;
    const  void *                    pNext{};
    uint64_t                        opaqueCaptureAddress{};
};
using VkMemoryOpaqueCaptureAddressAllocateInfoKHR = VkMemoryOpaqueCaptureAddressAllocateInfo;
struct VkDeviceMemoryOpaqueCaptureAddressInfo {
    VkStructureType   sType = VkStructureType::DeviceMemoryOpaqueCaptureAddressInfo;
    const  void *                       pNext{};
    VkDeviceMemory                     memory{};
};
using VkDeviceMemoryOpaqueCaptureAddressInfoKHR = VkDeviceMemoryOpaqueCaptureAddressInfo;
struct VkPhysicalDeviceLineRasterizationFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceLineRasterizationFeaturesEXT;
    void *         pNext{};
    VkBool32                             rectangularLines{};
    VkBool32                             bresenhamLines{};
    VkBool32                             smoothLines{};
    VkBool32                             stippledRectangularLines{};
    VkBool32                             stippledBresenhamLines{};
    VkBool32                             stippledSmoothLines{};
};
struct VkPhysicalDeviceLineRasterizationPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceLineRasterizationPropertiesEXT;
    void *                                pNext{};
    uint32_t                              lineSubPixelPrecisionBits{};
};
struct VkPipelineRasterizationLineStateCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineRasterizationLineStateCreateInfoEXT;
    const  void *                                                       pNext{};
    VkLineRasterizationModeEXT                                         lineRasterizationMode{};
    VkBool32                                                           stippledLineEnable{};
    uint32_t                                                           lineStippleFactor{};
    uint16_t                                                           lineStipplePattern{};
};
struct VkPhysicalDevicePipelineCreationCacheControlFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDevicePipelineCreationCacheControlFeaturesEXT;
    void *  pNext{};
    VkBool32                                                           pipelineCreationCacheControl{};
};
struct VkPhysicalDeviceVulkan11Features {
    VkStructureType sType = VkStructureType::PhysicalDeviceVulkan11Features;
    void *     pNext{};
    VkBool32                           storageBuffer16BitAccess{};
    VkBool32                           uniformAndStorageBuffer16BitAccess{};
    VkBool32                           storagePushConstant16{};
    VkBool32                           storageInputOutput16{};
    VkBool32                           multiview{};
    VkBool32                           multiviewGeometryShader{};
    VkBool32                           multiviewTessellationShader{};
    VkBool32                           variablePointersStorageBuffer{};
    VkBool32                           variablePointers{};
    VkBool32                           protectedMemory{};
    VkBool32                           samplerYcbcrConversion{};
    VkBool32                           shaderDrawParameters{};
};
struct VkPhysicalDeviceVulkan11Properties {
    VkStructureType sType = VkStructureType::PhysicalDeviceVulkan11Properties;
    void *       pNext{};
    uint8_t                            deviceUUID [ VK_UUID_SIZE ]{};
    uint8_t                            driverUUID [ VK_UUID_SIZE ]{};
    uint8_t                            deviceLUID [ VK_LUID_SIZE ]{};
    uint32_t                           deviceNodeMask{};
    VkBool32                           deviceLUIDValid{};
    uint32_t                        subgroupSize{};
    VkShaderStageFlags              subgroupSupportedStages{};
    VkSubgroupFeatureFlags          subgroupSupportedOperations{};
    VkBool32                        subgroupQuadOperationsInAllStages{};
    VkPointClippingBehavior            pointClippingBehavior{};
    uint32_t                           maxMultiviewViewCount{};
    uint32_t                           maxMultiviewInstanceIndex{};
    VkBool32                           protectedNoFault{};
    uint32_t                           maxPerSetDescriptors{};
    VkDeviceSize                       maxMemoryAllocationSize{};
};
struct VkPhysicalDeviceVulkan12Features {
    VkStructureType sType = VkStructureType::PhysicalDeviceVulkan12Features;
    void *     pNext{};
    VkBool32                           samplerMirrorClampToEdge{};
    VkBool32                           drawIndirectCount{};
    VkBool32                           storageBuffer8BitAccess{};
    VkBool32                           uniformAndStorageBuffer8BitAccess{};
    VkBool32                           storagePushConstant8{};
    VkBool32                           shaderBufferInt64Atomics{};
    VkBool32                           shaderSharedInt64Atomics{};
    VkBool32                           shaderFloat16{};
    VkBool32                           shaderInt8{};
    VkBool32                           descriptorIndexing{};
    VkBool32                           shaderInputAttachmentArrayDynamicIndexing{};
    VkBool32                           shaderUniformTexelBufferArrayDynamicIndexing{};
    VkBool32                           shaderStorageTexelBufferArrayDynamicIndexing{};
    VkBool32                           shaderUniformBufferArrayNonUniformIndexing{};
    VkBool32                           shaderSampledImageArrayNonUniformIndexing{};
    VkBool32                           shaderStorageBufferArrayNonUniformIndexing{};
    VkBool32                           shaderStorageImageArrayNonUniformIndexing{};
    VkBool32                           shaderInputAttachmentArrayNonUniformIndexing{};
    VkBool32                           shaderUniformTexelBufferArrayNonUniformIndexing{};
    VkBool32                           shaderStorageTexelBufferArrayNonUniformIndexing{};
    VkBool32                           descriptorBindingUniformBufferUpdateAfterBind{};
    VkBool32                           descriptorBindingSampledImageUpdateAfterBind{};
    VkBool32                           descriptorBindingStorageImageUpdateAfterBind{};
    VkBool32                           descriptorBindingStorageBufferUpdateAfterBind{};
    VkBool32                           descriptorBindingUniformTexelBufferUpdateAfterBind{};
    VkBool32                           descriptorBindingStorageTexelBufferUpdateAfterBind{};
    VkBool32                           descriptorBindingUpdateUnusedWhilePending{};
    VkBool32                           descriptorBindingPartiallyBound{};
    VkBool32                           descriptorBindingVariableDescriptorCount{};
    VkBool32                           runtimeDescriptorArray{};
    VkBool32                           samplerFilterMinmax{};
    VkBool32                           scalarBlockLayout{};
    VkBool32                           imagelessFramebuffer{};
    VkBool32                           uniformBufferStandardLayout{};
    VkBool32                           shaderSubgroupExtendedTypes{};
    VkBool32                           separateDepthStencilLayouts{};
    VkBool32                           hostQueryReset{};
    VkBool32                           timelineSemaphore{};
    VkBool32                           bufferDeviceAddress{};
    VkBool32                           bufferDeviceAddressCaptureReplay{};
    VkBool32                           bufferDeviceAddressMultiDevice{};
    VkBool32                           vulkanMemoryModel{};
    VkBool32                           vulkanMemoryModelDeviceScope{};
    VkBool32                           vulkanMemoryModelAvailabilityVisibilityChains{};
    VkBool32                           shaderOutputViewportIndex{};
    VkBool32                           shaderOutputLayer{};
    VkBool32                           subgroupBroadcastDynamicId{};
};
struct VkPhysicalDeviceVulkan12Properties {
    VkStructureType sType = VkStructureType::PhysicalDeviceVulkan12Properties;
    void *     pNext{};
    VkDriverId                         driverID{};
    char                               driverName [ VK_MAX_DRIVER_NAME_SIZE ]{};
    char                               driverInfo [ VK_MAX_DRIVER_INFO_SIZE ]{};
    VkConformanceVersion               conformanceVersion{};
    VkShaderFloatControlsIndependence denormBehaviorIndependence{};
    VkShaderFloatControlsIndependence roundingModeIndependence{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat16{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat32{};
    VkBool32                           shaderSignedZeroInfNanPreserveFloat64{};
    VkBool32                           shaderDenormPreserveFloat16{};
    VkBool32                           shaderDenormPreserveFloat32{};
    VkBool32                           shaderDenormPreserveFloat64{};
    VkBool32                           shaderDenormFlushToZeroFloat16{};
    VkBool32                           shaderDenormFlushToZeroFloat32{};
    VkBool32                           shaderDenormFlushToZeroFloat64{};
    VkBool32                           shaderRoundingModeRTEFloat16{};
    VkBool32                           shaderRoundingModeRTEFloat32{};
    VkBool32                           shaderRoundingModeRTEFloat64{};
    VkBool32                           shaderRoundingModeRTZFloat16{};
    VkBool32                           shaderRoundingModeRTZFloat32{};
    VkBool32                           shaderRoundingModeRTZFloat64{};
    uint32_t                           maxUpdateAfterBindDescriptorsInAllPools{};
    VkBool32                           shaderUniformBufferArrayNonUniformIndexingNative{};
    VkBool32                           shaderSampledImageArrayNonUniformIndexingNative{};
    VkBool32                           shaderStorageBufferArrayNonUniformIndexingNative{};
    VkBool32                           shaderStorageImageArrayNonUniformIndexingNative{};
    VkBool32                           shaderInputAttachmentArrayNonUniformIndexingNative{};
    VkBool32                           robustBufferAccessUpdateAfterBind{};
    VkBool32                           quadDivergentImplicitLod{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindSamplers{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindUniformBuffers{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindStorageBuffers{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindSampledImages{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindStorageImages{};
    uint32_t                           maxPerStageDescriptorUpdateAfterBindInputAttachments{};
    uint32_t                           maxPerStageUpdateAfterBindResources{};
    uint32_t                           maxDescriptorSetUpdateAfterBindSamplers{};
    uint32_t                           maxDescriptorSetUpdateAfterBindUniformBuffers{};
    uint32_t                           maxDescriptorSetUpdateAfterBindUniformBuffersDynamic{};
    uint32_t                           maxDescriptorSetUpdateAfterBindStorageBuffers{};
    uint32_t                           maxDescriptorSetUpdateAfterBindStorageBuffersDynamic{};
    uint32_t                           maxDescriptorSetUpdateAfterBindSampledImages{};
    uint32_t                           maxDescriptorSetUpdateAfterBindStorageImages{};
    uint32_t                           maxDescriptorSetUpdateAfterBindInputAttachments{};
    VkResolveModeFlags                 supportedDepthResolveModes{};
    VkResolveModeFlags                 supportedStencilResolveModes{};
    VkBool32                           independentResolveNone{};
    VkBool32                           independentResolve{};
    VkBool32                           filterMinmaxSingleComponentFormats{};
    VkBool32                           filterMinmaxImageComponentMapping{};
    uint64_t                           maxTimelineSemaphoreValueDifference{};
    VkSampleCountFlags   framebufferIntegerColorSampleCounts{};
};
struct VkPipelineCompilerControlCreateInfoAMD {
    VkStructureType     sType = VkStructureType::PipelineCompilerControlCreateInfoAMD;
    const  void *                                                                             pNext{};
    VkPipelineCompilerControlFlagsAMD                                        compilerControlFlags{};
};
struct VkPhysicalDeviceCoherentMemoryFeaturesAMD {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCoherentMemoryFeaturesAMD;
    void *         pNext{};
    VkBool32                             deviceCoherentMemory{};
};
struct VkPhysicalDeviceToolPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceToolPropertiesEXT;
    void *  pNext{};
    char              name [ VK_MAX_EXTENSION_NAME_SIZE ]{};
    char              version [ VK_MAX_EXTENSION_NAME_SIZE ]{};
    VkToolPurposeFlagsEXT   purposes{};
    char              description [ VK_MAX_DESCRIPTION_SIZE ]{};
    char              layer [ VK_MAX_EXTENSION_NAME_SIZE ]{};
};
struct VkSamplerCustomBorderColorCreateInfoEXT {
    VkStructureType   sType = VkStructureType::SamplerCustomBorderColorCreateInfoEXT;
    const  void *                                                                             pNext{};
    VkClearColorValue                                                                        customBorderColor{};
    VkFormat                                                                                 format{};
};
struct VkPhysicalDeviceCustomBorderColorPropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCustomBorderColorPropertiesEXT;
    void *                                                                    pNext{};
    uint32_t                                                                                        maxCustomBorderColorSamplers{};
};
struct VkPhysicalDeviceCustomBorderColorFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceCustomBorderColorFeaturesEXT;
    void *         pNext{};
    VkBool32                             customBorderColors{};
    VkBool32                             customBorderColorWithoutFormat{};
};
union VkDeviceOrHostAddressKHR {
    VkDeviceAddress              deviceAddress;
    void *                       hostAddress;
};
union VkDeviceOrHostAddressConstKHR {
    VkDeviceAddress              deviceAddress;
    const  void *                 hostAddress;
};
struct VkAccelerationStructureGeometryTrianglesDataKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureGeometryTrianglesDataKHR;
    const  void *                    pNext{};
    VkFormat                                        vertexFormat{};
    VkDeviceOrHostAddressConstKHR                   vertexData{};
    VkDeviceSize                                    vertexStride{};
    uint32_t                                        maxVertex{};
    VkIndexType                                     indexType{};
    VkDeviceOrHostAddressConstKHR                   indexData{};
    VkDeviceOrHostAddressConstKHR                   transformData{};
};
struct VkAccelerationStructureGeometryAabbsDataKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureGeometryAabbsDataKHR;
    const  void *                            pNext{};
    VkDeviceOrHostAddressConstKHR           data{};
    VkDeviceSize                            stride{};
};
struct VkAccelerationStructureGeometryInstancesDataKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureGeometryInstancesDataKHR;
    const  void *                            pNext{};
    VkBool32                                arrayOfPointers{};
    VkDeviceOrHostAddressConstKHR           data{};
};
union VkAccelerationStructureGeometryDataKHR {
    VkAccelerationStructureGeometryTrianglesDataKHR   triangles;
    VkAccelerationStructureGeometryAabbsDataKHR           aabbs;
    VkAccelerationStructureGeometryInstancesDataKHR   instances;
};
struct VkAccelerationStructureGeometryKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureGeometryKHR;
    const  void *                             pNext{};
    VkGeometryTypeKHR                        geometryType{};
    VkAccelerationStructureGeometryDataKHR   geometry{};
    VkGeometryFlagsKHR       flags{};
};
struct VkAccelerationStructureBuildGeometryInfoKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureBuildGeometryInfoKHR;
    const  void *                                                         pNext{};
    VkAccelerationStructureTypeKHR                                       type{};
    VkBuildAccelerationStructureFlagsKHR                 flags{};
    VkBuildAccelerationStructureModeKHR            mode{};
    VkAccelerationStructureKHR                     srcAccelerationStructure{};
    VkAccelerationStructureKHR                     dstAccelerationStructure{};
    uint32_t                                             geometryCount{};
    const  VkAccelerationStructureGeometryKHR *     pGeometries{};
    const  VkAccelerationStructureGeometryKHR * const*    ppGeometries{};
    VkDeviceOrHostAddressKHR                                             scratchData{};
};
struct VkAccelerationStructureBuildRangeInfoKHR {
    uint32_t                                                  primitiveCount{};
    uint32_t                                                  primitiveOffset{};
    uint32_t                                                  firstVertex{};
    uint32_t                                                  transformOffset{};
};
struct VkAccelerationStructureCreateInfoKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureCreateInfoKHR;
    const  void *                              pNext{};
    VkAccelerationStructureCreateFlagsKHR     createFlags{};
    VkBuffer                                                  buffer{};
    VkDeviceSize                                              offset{};
    VkDeviceSize                                              size{};
    VkAccelerationStructureTypeKHR                            type{};
    VkDeviceAddress                           deviceAddress{};
};
struct VkAabbPositionsKHR {
    float                                                     minX{};
    float                                                     minY{};
    float                                                     minZ{};
    float                                                     maxX{};
    float                                                     maxY{};
    float                                                     maxZ{};
};
using VkAabbPositionsNV = VkAabbPositionsKHR;
struct VkTransformMatrixKHR {
    float                                                     matrix [3][4]{};
};
using VkTransformMatrixNV = VkTransformMatrixKHR;
struct VkAccelerationStructureInstanceKHR {
    VkTransformMatrixKHR                                      transform{};
    uint32_t                                                  instanceCustomIndex :24;
    uint32_t                                                  mask :8;
    uint32_t                                                  instanceShaderBindingTableRecordOffset :24;
    uint32_t                flags :8;
    uint64_t                                                  accelerationStructureReference{};
};
using VkAccelerationStructureInstanceNV = VkAccelerationStructureInstanceKHR;
struct VkAccelerationStructureDeviceAddressInfoKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureDeviceAddressInfoKHR;
    const  void *                                             pNext{};
    VkAccelerationStructureKHR                               accelerationStructure{};
};
struct VkAccelerationStructureVersionInfoKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureVersionInfoKHR;
    const  void *                                             pNext{};
    const  uint8_t *                     pVersionData{};
};
struct VkCopyAccelerationStructureInfoKHR {
    VkStructureType   sType = VkStructureType::CopyAccelerationStructureInfoKHR;
    const  void *                                             pNext{};
    VkAccelerationStructureKHR                               src{};
    VkAccelerationStructureKHR                               dst{};
    VkCopyAccelerationStructureModeKHR                       mode{};
};
struct VkCopyAccelerationStructureToMemoryInfoKHR {
    VkStructureType   sType = VkStructureType::CopyAccelerationStructureToMemoryInfoKHR;
    const  void *                                             pNext{};
    VkAccelerationStructureKHR                               src{};
    VkDeviceOrHostAddressKHR                                 dst{};
    VkCopyAccelerationStructureModeKHR                       mode{};
};
struct VkCopyMemoryToAccelerationStructureInfoKHR {
    VkStructureType   sType = VkStructureType::CopyMemoryToAccelerationStructureInfoKHR;
    const  void *                                             pNext{};
    VkDeviceOrHostAddressConstKHR                            src{};
    VkAccelerationStructureKHR                               dst{};
    VkCopyAccelerationStructureModeKHR                       mode{};
};
struct VkPhysicalDeviceExtendedDynamicStateFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExtendedDynamicStateFeaturesEXT;
    void *         pNext{};
    VkBool32                             extendedDynamicState{};
};
struct VkPhysicalDeviceExtendedDynamicState2FeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceExtendedDynamicState2FeaturesEXT;
    void *         pNext{};
    VkBool32                       extendedDynamicState2{};
    VkBool32                       extendedDynamicState2LogicOp{};
    VkBool32                       extendedDynamicState2PatchControlPoints{};
};
struct VkRenderPassTransformBeginInfoQCOM {
    VkStructureType   sType = VkStructureType::RenderPassTransformBeginInfoQCOM;
    void *                            pNext{};
    VkSurfaceTransformFlagBitsKHR     transform{};
};
struct VkCopyCommandTransformInfoQCOM {
    VkStructureType   sType = VkStructureType::CopyCommandTransformInfoQCOM;
    const  void *      pNext{};
    VkSurfaceTransformFlagBitsKHR     transform{};
};
struct VkCommandBufferInheritanceRenderPassTransformInfoQCOM {
    VkStructureType   sType = VkStructureType::CommandBufferInheritanceRenderPassTransformInfoQCOM;
    void *                            pNext{};
    VkSurfaceTransformFlagBitsKHR     transform{};
    VkRect2D                          renderArea{};
};
struct VkPhysicalDeviceDiagnosticsConfigFeaturesNV {
    VkStructureType sType = VkStructureType::PhysicalDeviceDiagnosticsConfigFeaturesNV;
    void *     pNext{};
    VkBool32                         diagnosticsConfig{};
};
struct VkDeviceDiagnosticsConfigCreateInfoNV {
    VkStructureType   sType = VkStructureType::DeviceDiagnosticsConfigCreateInfoNV;
    const  void *                                          pNext{};
    VkDeviceDiagnosticsConfigFlagsNV      flags{};
};
struct VkPhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceZeroInitializeWorkgroupMemoryFeaturesKHR;
    void *           pNext{};
    VkBool32         shaderZeroInitializeWorkgroupMemory{};
};
struct VkPhysicalDeviceRobustness2FeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRobustness2FeaturesEXT;
    void *         pNext{};
    VkBool32                             robustBufferAccess2{};
    VkBool32                             robustImageAccess2{};
    VkBool32                             nullDescriptor{};
};
struct VkPhysicalDeviceRobustness2PropertiesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceRobustness2PropertiesEXT;
    void *         pNext{};
    VkDeviceSize                         robustStorageBufferAccessSizeAlignment{};
    VkDeviceSize                         robustUniformBufferAccessSizeAlignment{};
};
struct VkPhysicalDeviceImageRobustnessFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceImageRobustnessFeaturesEXT;
    void *         pNext{};
    VkBool32                             robustImageAccess{};
};
struct VkPhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR;
    void *         pNext{};
    VkBool32                             workgroupMemoryExplicitLayout{};
    VkBool32                             workgroupMemoryExplicitLayoutScalarBlockLayout{};
    VkBool32                             workgroupMemoryExplicitLayout8BitAccess{};
    VkBool32                             workgroupMemoryExplicitLayout16BitAccess{};
};
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDevicePortabilitySubsetFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePortabilitySubsetFeaturesKHR;
    void *         pNext{};
    VkBool32                             constantAlphaColorBlendFactors{};
    VkBool32                             events{};
    VkBool32                             imageViewFormatReinterpretation{};
    VkBool32                             imageViewFormatSwizzle{};
    VkBool32                             imageView2DOn3DImage{};
    VkBool32                             multisampleArrayImage{};
    VkBool32                             mutableComparisonSamplers{};
    VkBool32                             pointPolygons{};
    VkBool32                             samplerMipLodBias{};
    VkBool32                             separateStencilMaskRef{};
    VkBool32                             shaderSampleRateInterpolationFunctions{};
    VkBool32                             tessellationIsolines{};
    VkBool32                             tessellationPointMode{};
    VkBool32                             triangleFans{};
    VkBool32                             vertexAttributeAccessBeyondStride{};
};
struct VkPhysicalDevicePortabilitySubsetPropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDevicePortabilitySubsetPropertiesKHR;
    void *         pNext{};
    uint32_t                             minVertexInputBindingStrideAlignment{};
};
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDevice4444FormatsFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDevice4444FormatsFeaturesEXT;
    void *         pNext{};
    VkBool32                             formatA4R4G4B4{};
    VkBool32                             formatA4B4G4R4{};
};
struct VkBufferCopy2KHR {
    VkStructureType   sType = VkStructureType::BufferCopy2KHR;
    const  void *   pNext{};
    VkDeviceSize   srcOffset{};
    VkDeviceSize   dstOffset{};
    VkDeviceSize   size{};
};
struct VkImageCopy2KHR {
    VkStructureType   sType = VkStructureType::ImageCopy2KHR;
    const  void *  pNext{};
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D   srcOffset{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D   dstOffset{};
    VkExtent3D   extent{};
};
struct VkImageBlit2KHR {
    VkStructureType   sType = VkStructureType::ImageBlit2KHR;
    const  void *   pNext{};
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D   srcOffsets [2]{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D   dstOffsets [2]{};
};
struct VkBufferImageCopy2KHR {
    VkStructureType   sType = VkStructureType::BufferImageCopy2KHR;
    const  void *   pNext{};
    VkDeviceSize   bufferOffset{};
    uint32_t   bufferRowLength{};
    uint32_t   bufferImageHeight{};
    VkImageSubresourceLayers   imageSubresource{};
    VkOffset3D   imageOffset{};
    VkExtent3D   imageExtent{};
};
struct VkImageResolve2KHR {
    VkStructureType   sType = VkStructureType::ImageResolve2KHR;
    const  void *   pNext{};
    VkImageSubresourceLayers   srcSubresource{};
    VkOffset3D   srcOffset{};
    VkImageSubresourceLayers   dstSubresource{};
    VkOffset3D   dstOffset{};
    VkExtent3D   extent{};
};
struct VkCopyBufferInfo2KHR {
    VkStructureType   sType = VkStructureType::CopyBufferInfo2KHR;
    const  void *  pNext{};
    VkBuffer   srcBuffer{};
    VkBuffer   dstBuffer{};
    uint32_t   regionCount{};
    const  VkBufferCopy2KHR *  pRegions{};
};
struct VkCopyImageInfo2KHR {
    VkStructureType   sType = VkStructureType::CopyImageInfo2KHR;
    const  void *  pNext{};
    VkImage   srcImage{};
    VkImageLayout   srcImageLayout{};
    VkImage   dstImage{};
    VkImageLayout   dstImageLayout{};
    uint32_t   regionCount{};
    const  VkImageCopy2KHR *  pRegions{};
};
struct VkBlitImageInfo2KHR {
    VkStructureType   sType = VkStructureType::BlitImageInfo2KHR;
    const  void *  pNext{};
    VkImage   srcImage{};
    VkImageLayout   srcImageLayout{};
    VkImage   dstImage{};
    VkImageLayout   dstImageLayout{};
    uint32_t   regionCount{};
    const  VkImageBlit2KHR *  pRegions{};
    VkFilter   filter{};
};
struct VkCopyBufferToImageInfo2KHR {
    VkStructureType   sType = VkStructureType::CopyBufferToImageInfo2KHR;
    const  void *  pNext{};
    VkBuffer   srcBuffer{};
    VkImage   dstImage{};
    VkImageLayout   dstImageLayout{};
    uint32_t   regionCount{};
    const  VkBufferImageCopy2KHR *  pRegions{};
};
struct VkCopyImageToBufferInfo2KHR {
    VkStructureType   sType = VkStructureType::CopyImageToBufferInfo2KHR;
    const  void *  pNext{};
    VkImage   srcImage{};
    VkImageLayout   srcImageLayout{};
    VkBuffer   dstBuffer{};
    uint32_t   regionCount{};
    const  VkBufferImageCopy2KHR *  pRegions{};
};
struct VkResolveImageInfo2KHR {
    VkStructureType   sType = VkStructureType::ResolveImageInfo2KHR;
    const  void *  pNext{};
    VkImage   srcImage{};
    VkImageLayout   srcImageLayout{};
    VkImage   dstImage{};
    VkImageLayout   dstImageLayout{};
    uint32_t   regionCount{};
    const  VkImageResolve2KHR *  pRegions{};
};
struct VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceShaderImageAtomicInt64FeaturesEXT;
    void *                                pNext{};
    VkBool32                              shaderImageInt64Atomics{};
    VkBool32                              sparseImageInt64Atomics{};
};
struct VkFragmentShadingRateAttachmentInfoKHR {
    VkStructureType   sType = VkStructureType::FragmentShadingRateAttachmentInfoKHR;
    const  void *                 pNext{};
    const  VkAttachmentReference2 *  pFragmentShadingRateAttachment{};
    VkExtent2D                   shadingRateAttachmentTexelSize{};
};
struct VkPipelineFragmentShadingRateStateCreateInfoKHR {
    VkStructureType   sType = VkStructureType::PipelineFragmentShadingRateStateCreateInfoKHR;
    const  void *                                 pNext{};
    VkExtent2D                                   fragmentSize{};
    VkFragmentShadingRateCombinerOpKHR           combinerOps [2]{};
};
struct VkPhysicalDeviceFragmentShadingRateFeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShadingRateFeaturesKHR;
    void *               pNext{};
    VkBool32             pipelineFragmentShadingRate{};
    VkBool32             primitiveFragmentShadingRate{};
    VkBool32             attachmentFragmentShadingRate{};
};
struct VkPhysicalDeviceFragmentShadingRatePropertiesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShadingRatePropertiesKHR;
    void *                   pNext{};
    VkExtent2D               minFragmentShadingRateAttachmentTexelSize{};
    VkExtent2D               maxFragmentShadingRateAttachmentTexelSize{};
    uint32_t                 maxFragmentShadingRateAttachmentTexelSizeAspectRatio{};
    VkBool32                 primitiveFragmentShadingRateWithMultipleViewports{};
    VkBool32                 layeredShadingRateAttachments{};
    VkBool32                 fragmentShadingRateNonTrivialCombinerOps{};
    VkExtent2D               maxFragmentSize{};
    uint32_t                 maxFragmentSizeAspectRatio{};
    uint32_t                 maxFragmentShadingRateCoverageSamples{};
    VkSampleCountFlagBits    maxFragmentShadingRateRasterizationSamples{};
    VkBool32                 fragmentShadingRateWithShaderDepthStencilWrites{};
    VkBool32                 fragmentShadingRateWithSampleMask{};
    VkBool32                 fragmentShadingRateWithShaderSampleMask{};
    VkBool32                 fragmentShadingRateWithConservativeRasterization{};
    VkBool32                 fragmentShadingRateWithFragmentShaderInterlock{};
    VkBool32                 fragmentShadingRateWithCustomSampleLocations{};
    VkBool32                 fragmentShadingRateStrictMultiplyCombiner{};
};
struct VkPhysicalDeviceFragmentShadingRateKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShadingRateKHR;
    void *               pNext{};
    VkSampleCountFlags   sampleCounts{};
    VkExtent2D           fragmentSize{};
};
struct VkPhysicalDeviceShaderTerminateInvocationFeaturesKHR {
    VkStructureType sType = VkStructureType::PhysicalDeviceShaderTerminateInvocationFeaturesKHR;
    void *     pNext{};
    VkBool32                         shaderTerminateInvocation{};
};
struct VkPhysicalDeviceFragmentShadingRateEnumsFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShadingRateEnumsFeaturesNV;
    void *                               pNext{};
    VkBool32                             fragmentShadingRateEnums{};
    VkBool32                             supersampleFragmentShadingRates{};
    VkBool32                             noInvocationFragmentShadingRates{};
};
struct VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceFragmentShadingRateEnumsPropertiesNV;
    void *                               pNext{};
    VkSampleCountFlagBits                maxFragmentShadingRateInvocationCount{};
};
struct VkPipelineFragmentShadingRateEnumStateCreateInfoNV {
    VkStructureType   sType = VkStructureType::PipelineFragmentShadingRateEnumStateCreateInfoNV;
    const  void *                         pNext{};
    VkFragmentShadingRateTypeNV          shadingRateType{};
    VkFragmentShadingRateNV              shadingRate{};
    VkFragmentShadingRateCombinerOpKHR   combinerOps [2]{};
};
struct VkAccelerationStructureBuildSizesInfoKHR {
    VkStructureType   sType = VkStructureType::AccelerationStructureBuildSizesInfoKHR;
    const  void *         pNext{};
    VkDeviceSize                         accelerationStructureSize{};
    VkDeviceSize                         updateScratchSize{};
    VkDeviceSize                         buildScratchSize{};
};
struct VkPhysicalDeviceMutableDescriptorTypeFeaturesVALVE {
    VkStructureType   sType = VkStructureType::PhysicalDeviceMutableDescriptorTypeFeaturesVALVE;
    void *                      pNext{};
    VkBool32                                          mutableDescriptorType{};
};
struct VkMutableDescriptorTypeListVALVE {
    uint32_t                                            descriptorTypeCount{};
    const  VkDescriptorType *  pDescriptorTypes{};
};
struct VkMutableDescriptorTypeCreateInfoVALVE {
    VkStructureType   sType = VkStructureType::MutableDescriptorTypeCreateInfoVALVE;
    const  void *                                                                       pNext{};
    uint32_t                                                           mutableDescriptorTypeListCount{};
    const  VkMutableDescriptorTypeListVALVE *  pMutableDescriptorTypeLists{};
};
struct VkPhysicalDeviceVertexInputDynamicStateFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceVertexInputDynamicStateFeaturesEXT;
    void *         pNext{};
    VkBool32                             vertexInputDynamicState{};
};
struct VkVertexInputBindingDescription2EXT {
    VkStructureType sType = VkStructureType::VertexInputBindingDescription2EXT;
    void *     pNext{};
    uint32_t                         binding{};
    uint32_t                         stride{};
    VkVertexInputRate                inputRate{};
    uint32_t                         divisor{};
};
struct VkVertexInputAttributeDescription2EXT {
    VkStructureType sType = VkStructureType::VertexInputAttributeDescription2EXT;
    void *     pNext{};
    uint32_t                         location{};
    uint32_t                         binding{};
    VkFormat                         format{};
    uint32_t                         offset{};
};
struct VkPhysicalDeviceColorWriteEnableFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceColorWriteEnableFeaturesEXT;
    void *         pNext{};
    VkBool32                       colorWriteEnable{};
};
struct VkPipelineColorWriteCreateInfoEXT {
    VkStructureType   sType = VkStructureType::PipelineColorWriteCreateInfoEXT;
    const  void *             pNext{};
    uint32_t                 attachmentCount{};
    const  VkBool32 *   pColorWriteEnables{};
};
struct VkMemoryBarrier2KHR {
    VkStructureType   sType = VkStructureType::MemoryBarrier2KHR;
    const  void *                                pNext{};
    VkPipelineStageFlags2KHR    srcStageMask{};
    VkAccessFlags2KHR           srcAccessMask{};
    VkPipelineStageFlags2KHR    dstStageMask{};
    VkAccessFlags2KHR           dstAccessMask{};
};
struct VkImageMemoryBarrier2KHR {
    VkStructureType   sType = VkStructureType::ImageMemoryBarrier2KHR;
    const  void *                                pNext{};
    VkPipelineStageFlags2KHR    srcStageMask{};
    VkAccessFlags2KHR           srcAccessMask{};
    VkPipelineStageFlags2KHR    dstStageMask{};
    VkAccessFlags2KHR           dstAccessMask{};
    VkImageLayout                               oldLayout{};
    VkImageLayout                               newLayout{};
    uint32_t                                    srcQueueFamilyIndex{};
    uint32_t                                    dstQueueFamilyIndex{};
    VkImage                                     image{};
    VkImageSubresourceRange                     subresourceRange{};
};
struct VkBufferMemoryBarrier2KHR {
    VkStructureType   sType = VkStructureType::BufferMemoryBarrier2KHR;
    const  void *                                pNext{};
    VkPipelineStageFlags2KHR    srcStageMask{};
    VkAccessFlags2KHR           srcAccessMask{};
    VkPipelineStageFlags2KHR    dstStageMask{};
    VkAccessFlags2KHR           dstAccessMask{};
    uint32_t                                    srcQueueFamilyIndex{};
    uint32_t                                    dstQueueFamilyIndex{};
    VkBuffer                                    buffer{};
    VkDeviceSize                                offset{};
    VkDeviceSize                                size{};
};
struct VkDependencyInfoKHR {
    VkStructureType   sType = VkStructureType::DependencyInfoKHR;
    const  void *                                pNext{};
    VkDependencyFlags           dependencyFlags{};
    uint32_t                    memoryBarrierCount{};
    const  VkMemoryBarrier2KHR *  pMemoryBarriers{};
    uint32_t                    bufferMemoryBarrierCount{};
    const  VkBufferMemoryBarrier2KHR *  pBufferMemoryBarriers{};
    uint32_t                    imageMemoryBarrierCount{};
    const  VkImageMemoryBarrier2KHR *  pImageMemoryBarriers{};
};
struct VkSemaphoreSubmitInfoKHR {
    VkStructureType         sType = VkStructureType::SemaphoreSubmitInfoKHR;
    const  void *                                                                 pNext{};
    VkSemaphore                                                                  semaphore{};
    uint64_t                                                                     value{};
    VkPipelineStageFlags2KHR                                     stageMask{};
    uint32_t                                                                     deviceIndex{};
};
struct VkCommandBufferSubmitInfoKHR {
    VkStructureType    sType = VkStructureType::CommandBufferSubmitInfoKHR;
    const  void *                                                                 pNext{};
    VkCommandBuffer                                                              commandBuffer{};
    uint32_t                                                                     deviceMask{};
};
struct VkSubmitInfo2KHR {
    VkStructureType                 sType = VkStructureType::SubmitInfo2KHR;
    const  void *                                                                 pNext{};
    VkSubmitFlagsKHR                                             flags{};
    uint32_t                                                     waitSemaphoreInfoCount{};
    const  VkSemaphoreSubmitInfoKHR *                pWaitSemaphoreInfos{};
    uint32_t                                                     commandBufferInfoCount{};
    const  VkCommandBufferSubmitInfoKHR *            pCommandBufferInfos{};
    uint32_t                                                     signalSemaphoreInfoCount{};
    const  VkSemaphoreSubmitInfoKHR *              pSignalSemaphoreInfos{};
};
struct VkQueueFamilyCheckpointProperties2NV {
    VkStructureType   sType = VkStructureType::QueueFamilyCheckpointProperties2NV;
    void *            pNext{};
    VkPipelineStageFlags2KHR   checkpointExecutionStageMask{};
};
struct VkCheckpointData2NV {
    VkStructureType   sType = VkStructureType::CheckpointData2NV;
    void *                   pNext{};
    VkPipelineStageFlags2KHR     stage{};
    void *  pCheckpointMarker{};
};
struct VkPhysicalDeviceSynchronization2FeaturesKHR {
    VkStructureType   sType = VkStructureType::PhysicalDeviceSynchronization2FeaturesKHR;
    void *         pNext{};
    VkBool32                             synchronization2{};
};
#if defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkVideoQueueFamilyProperties2KHR {
    VkStructureType sType = VkStructureType::VideoQueueFamilyProperties2KHR;
    void *                               pNext{};
    VkVideoCodecOperationFlagsKHR        videoCodecOperations{};
};
struct VkVideoProfileKHR {
    VkStructureType sType = VkStructureType::VideoProfileKHR;
    void *                               pNext{};
    VkVideoCodecOperationFlagBitsKHR     videoCodecOperation{};
    VkVideoChromaSubsamplingFlagsKHR     chromaSubsampling{};
    VkVideoComponentBitDepthFlagsKHR     lumaBitDepth{};
    VkVideoComponentBitDepthFlagsKHR     chromaBitDepth{};
};
struct VkVideoProfilesKHR {
    VkStructureType sType = VkStructureType::VideoProfilesKHR;
    void *                               pNext{};
    uint32_t                             profileCount{};
    const  VkVideoProfileKHR *            pProfiles{};
};
struct VkPhysicalDeviceVideoFormatInfoKHR {
    VkStructureType sType = VkStructureType::PhysicalDeviceVideoFormatInfoKHR;
    const  void *                         pNext{};
    VkImageUsageFlags                    imageUsage{};
    const  VkVideoProfilesKHR *           pVideoProfiles{};
};
struct VkVideoFormatPropertiesKHR {
    VkStructureType sType = VkStructureType::VideoFormatPropertiesKHR;
    void *                               pNext{};
    VkFormat                             format{};
};
struct VkVideoCapabilitiesKHR {
    VkStructureType sType = VkStructureType::VideoCapabilitiesKHR;
    void *                             pNext{};
    VkVideoCapabilitiesFlagsKHR        capabilityFlags{};
    VkDeviceSize                       minBitstreamBufferOffsetAlignment{};
    VkDeviceSize                       minBitstreamBufferSizeAlignment{};
    VkExtent2D                         videoPictureExtentGranularity{};
    VkExtent2D                         minExtent{};
    VkExtent2D                         maxExtent{};
    uint32_t                           maxReferencePicturesSlotsCount{};
    uint32_t                           maxReferencePicturesActiveCount{};
};
struct VkVideoGetMemoryPropertiesKHR {
    VkStructureType sType = VkStructureType::VideoGetMemoryPropertiesKHR;
    const  void *                        pNext{};
    uint32_t                            memoryBindIndex{};
    VkMemoryRequirements2 *             pMemoryRequirements{};
};
struct VkVideoBindMemoryKHR {
    VkStructureType sType = VkStructureType::VideoBindMemoryKHR;
    const  void *                        pNext{};
    uint32_t                            memoryBindIndex{};
    VkDeviceMemory                      memory{};
    VkDeviceSize                        memoryOffset{};
    VkDeviceSize                        memorySize{};
};
struct VkVideoPictureResourceKHR {
    VkStructureType sType = VkStructureType::VideoPictureResourceKHR;
    const  void *         pNext{};
    VkOffset2D           codedOffset{};
    VkExtent2D           codedExtent{};
    uint32_t             baseArrayLayer{};
    VkImageView          imageViewBinding{};
};
struct VkVideoReferenceSlotKHR {
    VkStructureType sType = VkStructureType::VideoReferenceSlotKHR;
    const  void *         pNext{};
    int8_t               slotIndex{};
    const  VkVideoPictureResourceKHR *  pPictureResource{};
};
struct VkVideoDecodeInfoKHR {
    VkStructureType sType = VkStructureType::VideoDecodeInfoKHR;
    const  void *                             pNext{};
    VkVideoDecodeFlagsKHR    flags{};
    VkOffset2D                               codedOffset{};
    VkExtent2D                               codedExtent{};
    VkBuffer                                 srcBuffer{};
    VkDeviceSize                             srcBufferOffset{};
    VkDeviceSize                             srcBufferRange{};
    VkVideoPictureResourceKHR                dstPictureResource{};
    const  VkVideoReferenceSlotKHR *          pSetupReferenceSlot{};
    uint32_t                                 referenceSlotCount{};
    const  VkVideoReferenceSlotKHR *  pReferenceSlots{};
};
struct VkVideoDecodeH264ProfileEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264ProfileEXT;
    const  void *                           pNext{};
    StdVideoH264ProfileIdc                 stdProfileIdc{};
    VkVideoDecodeH264FieldLayoutFlagsEXT   fieldLayout{};
};
struct VkVideoDecodeH264CapabilitiesEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264CapabilitiesEXT;
    void *                             pNext{};
    uint32_t                           maxLevel{};
    VkOffset2D                         fieldOffsetGranularity{};
    VkExtensionProperties              stdExtensionVersion{};
};
struct VkVideoDecodeH264SessionCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264SessionCreateInfoEXT;
    const  void *                       pNext{};
    VkVideoDecodeH264CreateFlagsEXT    flags{};
    const  VkExtensionProperties *      pStdExtensionVersion{};
};
struct VkVideoDecodeH264SessionParametersAddInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264SessionParametersAddInfoEXT;
    const  void *                                                                pNext{};
    uint32_t                                                                    spsStdCount{};
    const  StdVideoH264SequenceParameterSet *  pSpsStd{};
    uint32_t                                                                    ppsStdCount{};
    const  StdVideoH264PictureParameterSet *   pPpsStd{};
};
struct VkVideoDecodeH264SessionParametersCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264SessionParametersCreateInfoEXT;
    const  void *                                                                pNext{};
    uint32_t                                                                    maxSpsStdCount{};
    uint32_t                                                                    maxPpsStdCount{};
    const  VkVideoDecodeH264SessionParametersAddInfoEXT *        pParametersAddInfo{};
};
struct VkVideoDecodeH264PictureInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264PictureInfoEXT;
    const  void *      pNext{};
    const  StdVideoDecodeH264PictureInfo *   pStdPictureInfo{};
    uint32_t                                slicesCount{};
    const  uint32_t *      pSlicesDataOffsets{};
};
struct VkVideoDecodeH264DpbSlotInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264DpbSlotInfoEXT;
    const  void *                             pNext{};
    const  StdVideoDecodeH264ReferenceInfo *  pStdReferenceInfo{};
};
struct VkVideoDecodeH264MvcEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH264MvcEXT;
    const  void * pNext{};
    const  StdVideoDecodeH264Mvc *    pStdMvc{};
};
struct VkVideoDecodeH265ProfileEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265ProfileEXT;
    const  void *                     pNext{};
    StdVideoH265ProfileIdc           stdProfileIdc{};
};
struct VkVideoDecodeH265CapabilitiesEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265CapabilitiesEXT;
    void *                             pNext{};
    uint32_t                           maxLevel{};
    VkExtensionProperties              stdExtensionVersion{};
};
struct VkVideoDecodeH265SessionCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265SessionCreateInfoEXT;
    const  void *                       pNext{};
    VkVideoDecodeH265CreateFlagsEXT    flags{};
    const  VkExtensionProperties *      pStdExtensionVersion{};
};
struct VkVideoDecodeH265SessionParametersAddInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265SessionParametersAddInfoEXT;
    const  void *                                                                pNext{};
    uint32_t                                                                    spsStdCount{};
    const  StdVideoH265SequenceParameterSet *  pSpsStd{};
    uint32_t                                                                    ppsStdCount{};
    const  StdVideoH265PictureParameterSet *   pPpsStd{};
};
struct VkVideoDecodeH265SessionParametersCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265SessionParametersCreateInfoEXT;
    const  void *                                                          pNext{};
    uint32_t                                                              maxSpsStdCount{};
    uint32_t                                                              maxPpsStdCount{};
    const  VkVideoDecodeH265SessionParametersAddInfoEXT *  pParametersAddInfo{};
};
struct VkVideoDecodeH265PictureInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265PictureInfoEXT;
    const  void *                         pNext{};
    StdVideoDecodeH265PictureInfo *      pStdPictureInfo{};
    uint32_t                             slicesCount{};
    const  uint32_t *   pSlicesDataOffsets{};
};
struct VkVideoDecodeH265DpbSlotInfoEXT {
    VkStructureType sType = VkStructureType::VideoDecodeH265DpbSlotInfoEXT;
    const  void *                              pNext{};
    const  StdVideoDecodeH265ReferenceInfo *   pStdReferenceInfo{};
};
struct VkVideoSessionCreateInfoKHR {
    VkStructureType sType = VkStructureType::VideoSessionCreateInfoKHR;
    const  void *                                    pNext{};
    uint32_t                                        queueFamilyIndex{};
    VkVideoSessionCreateFlagsKHR    flags{};
    const  VkVideoProfileKHR *                       pVideoProfile{};
    VkFormat                                        pictureFormat{};
    VkExtent2D                                      maxCodedExtent{};
    VkFormat                                        referencePicturesFormat{};
    uint32_t                                        maxReferencePicturesSlotsCount{};
    uint32_t                                        maxReferencePicturesActiveCount{};
};
struct VkVideoSessionParametersCreateInfoKHR {
    VkStructureType sType = VkStructureType::VideoSessionParametersCreateInfoKHR;
    const  void *                                             pNext{};
    VkVideoSessionParametersKHR                              videoSessionParametersTemplate{};
    VkVideoSessionKHR                                        videoSession{};
};
struct VkVideoSessionParametersUpdateInfoKHR {
    VkStructureType sType = VkStructureType::VideoSessionParametersUpdateInfoKHR;
    const  void *                                             pNext{};
    uint32_t                                                 updateSequenceCount{};
};
struct VkVideoBeginCodingInfoKHR {
    VkStructureType sType = VkStructureType::VideoBeginCodingInfoKHR;
    const  void *                                              pNext{};
    VkVideoBeginCodingFlagsKHR                flags{};
    VkVideoCodingQualityPresetFlagsKHR                        codecQualityPreset{};
    VkVideoSessionKHR                                         videoSession{};
    VkVideoSessionParametersKHR               videoSessionParameters{};
    uint32_t                                                  referenceSlotCount{};
    const  VkVideoReferenceSlotKHR *  pReferenceSlots{};
};
struct VkVideoEndCodingInfoKHR {
    VkStructureType sType = VkStructureType::VideoEndCodingInfoKHR;
    const  void *                               pNext{};
    VkVideoEndCodingFlagsKHR   flags{};
};
struct VkVideoCodingControlInfoKHR {
    VkStructureType sType = VkStructureType::VideoCodingControlInfoKHR;
    const  void *                                   pNext{};
    VkVideoCodingControlFlagsKHR   flags{};
};
struct VkVideoEncodeInfoKHR {
    VkStructureType sType = VkStructureType::VideoEncodeInfoKHR;
    const  void *                             pNext{};
    VkVideoEncodeFlagsKHR    flags{};
    uint32_t                                 qualityLevel{};
    VkExtent2D                               codedExtent{};
    VkBuffer                                 dstBitstreamBuffer{};
    VkDeviceSize                             dstBitstreamBufferOffset{};
    VkDeviceSize                             dstBitstreamBufferMaxRange{};
    VkVideoPictureResourceKHR                srcPictureResource{};
    const  VkVideoReferenceSlotKHR *          pSetupReferenceSlot{};
    uint32_t                                 referenceSlotCount{};
    const  VkVideoReferenceSlotKHR *  pReferenceSlots{};
};
struct VkVideoEncodeRateControlInfoKHR {
    VkStructureType sType = VkStructureType::VideoEncodeRateControlInfoKHR;
    const  void *                               pNext{};
    VkVideoEncodeRateControlFlagsKHR           flags{};
    VkVideoEncodeRateControlModeFlagBitsKHR    rateControlMode{};
    uint32_t                                   averageBitrate{};
    uint16_t                                   peakToAverageBitrateRatio{};
    uint16_t                                   frameRateNumerator{};
    uint16_t                                   frameRateDenominator{};
    uint32_t                                   virtualBufferSizeInMs{};
};
struct VkVideoEncodeH264CapabilitiesEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264CapabilitiesEXT;
    const  void *                            pNext{};
    VkVideoEncodeH264CapabilitiesFlagsEXT   flags{};
    VkVideoEncodeH264InputModeFlagsEXT      inputModeFlags{};
    VkVideoEncodeH264OutputModeFlagsEXT     outputModeFlags{};
    VkExtent2D                              minPictureSizeInMbs{};
    VkExtent2D                              maxPictureSizeInMbs{};
    VkExtent2D                              inputImageDataAlignment{};
    uint8_t                                 maxNumL0ReferenceForP{};
    uint8_t                                 maxNumL0ReferenceForB{};
    uint8_t                                 maxNumL1Reference{};
    uint8_t                                 qualityLevelCount{};
    VkExtensionProperties                   stdExtensionVersion{};
};
struct VkVideoEncodeH264SessionCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264SessionCreateInfoEXT;
    const  void *                      pNext{};
    VkVideoEncodeH264CreateFlagsEXT   flags{};
    VkExtent2D                        maxPictureSizeInMbs{};
    const  VkExtensionProperties *     pStdExtensionVersion{};
};
struct VkVideoEncodeH264SessionParametersAddInfoEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264SessionParametersAddInfoEXT;
    const  void *                                                                pNext{};
    uint32_t                                                                    spsStdCount{};
    const  StdVideoH264SequenceParameterSet *  pSpsStd{};
    uint32_t                                                                    ppsStdCount{};
    const  StdVideoH264PictureParameterSet *   pPpsStd{};
};
struct VkVideoEncodeH264SessionParametersCreateInfoEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264SessionParametersCreateInfoEXT;
    const  void *                                                          pNext{};
    uint32_t                                                              maxSpsStdCount{};
    uint32_t                                                              maxPpsStdCount{};
    const  VkVideoEncodeH264SessionParametersAddInfoEXT *  pParametersAddInfo{};
};
struct VkVideoEncodeH264DpbSlotInfoEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264DpbSlotInfoEXT;
    const  void *                                                           pNext{};
    int8_t                                                                 slotIndex{};
    const  StdVideoEncodeH264PictureInfo *                                  pStdPictureInfo{};
};
struct VkVideoEncodeH264NaluSliceEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264NaluSliceEXT;
    const  void *                                      pNext{};
    const  StdVideoEncodeH264SliceHeader *             pSliceHeaderStd{};
    uint32_t                                          mbCount{};
    uint8_t                                           refFinalList0EntryCount{};
    const  VkVideoEncodeH264DpbSlotInfoEXT *  pRefFinalList0Entries{};
    uint8_t                                           refFinalList1EntryCount{};
    const  VkVideoEncodeH264DpbSlotInfoEXT *  pRefFinalList1Entries{};
    uint32_t                                          precedingNaluBytes{};
    uint8_t                                           minQp{};
    uint8_t                                           maxQp{};
};
struct VkVideoEncodeH264VclFrameInfoEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264VclFrameInfoEXT;
    const  void *                                                           pNext{};
    uint8_t                                                                refDefaultFinalList0EntryCount{};
    const  VkVideoEncodeH264DpbSlotInfoEXT *  pRefDefaultFinalList0Entries{};
    uint8_t                                                                refDefaultFinalList1EntryCount{};
    const  VkVideoEncodeH264DpbSlotInfoEXT *  pRefDefaultFinalList1Entries{};
    uint32_t                                                               naluSliceEntryCount{};
    const  VkVideoEncodeH264NaluSliceEXT *      pNaluSliceEntries{};
    const  VkVideoEncodeH264DpbSlotInfoEXT *                                pCurrentPictureInfo{};
};
struct VkVideoEncodeH264EmitPictureParametersEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264EmitPictureParametersEXT;
    const  void *                              pNext{};
    uint8_t                                   spsId{};
    VkBool32                                  emitSpsEnable{};
    uint32_t                                  ppsIdEntryCount{};
    const  uint8_t *   ppsIdEntries{};
};
struct VkVideoEncodeH264ProfileEXT {
    VkStructureType sType = VkStructureType::VideoEncodeH264ProfileEXT;
    const  void *                     pNext{};
    StdVideoH264ProfileIdc           stdProfileIdc{};
};
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
struct VkPhysicalDeviceInheritedViewportScissorFeaturesNV {
    VkStructureType   sType = VkStructureType::PhysicalDeviceInheritedViewportScissorFeaturesNV;
    void *                                pNext{};
    VkBool32                              inheritedViewportScissor2D{};
};
struct VkCommandBufferInheritanceViewportScissorInfoNV {
    VkStructureType   sType = VkStructureType::CommandBufferInheritanceViewportScissorInfoNV;
    const  void *                                     pNext{};
    VkBool32                                         viewportScissor2D{};
    uint32_t                                         viewportDepthCount{};
    const  VkViewport *         pViewportDepths{};
};
struct VkPhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT {
    VkStructureType   sType = VkStructureType::PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT;
    void *         pNext{};
    VkBool32                       ycbcr2plane444Formats{};
};
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
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
using PFN_vkCreateScreenSurfaceQNX = VkResult (*) (VkInstance   instance, const  VkScreenSurfaceCreateInfoQNX *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkSurfaceKHR *  pSurface);
using PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX = VkBool32 (*) (VkPhysicalDevice   physicalDevice, uint32_t   queueFamilyIndex, struct  _screen_window *  window);
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
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
#if defined(VK_USE_PLATFORM_FUCHSIA)
using PFN_vkGetMemoryZirconHandleFUCHSIA = VkResult (*) (VkDevice   device, const  VkMemoryGetZirconHandleInfoFUCHSIA *  pGetZirconHandleInfo, zx_handle_t *  pZirconHandle);
using PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA = VkResult (*) (VkDevice   device, VkExternalMemoryHandleTypeFlagBits   handleType, zx_handle_t   zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA *  pMemoryZirconHandleProperties);
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
using PFN_vkGetPhysicalDeviceExternalSemaphoreProperties = void (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceExternalSemaphoreInfo *  pExternalSemaphoreInfo, VkExternalSemaphoreProperties *  pExternalSemaphoreProperties);
using PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = PFN_vkGetPhysicalDeviceExternalSemaphoreProperties;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetSemaphoreWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkSemaphoreGetWin32HandleInfoKHR *  pGetWin32HandleInfo, HANDLE *  pHandle);
using PFN_vkImportSemaphoreWin32HandleKHR = VkResult (*) (VkDevice   device, const  VkImportSemaphoreWin32HandleInfoKHR *  pImportSemaphoreWin32HandleInfo);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkGetSemaphoreFdKHR = VkResult (*) (VkDevice   device, const  VkSemaphoreGetFdInfoKHR *  pGetFdInfo, int *  pFd);
using PFN_vkImportSemaphoreFdKHR = VkResult (*) (VkDevice   device, const  VkImportSemaphoreFdInfoKHR *  pImportSemaphoreFdInfo);
#if defined(VK_USE_PLATFORM_FUCHSIA)
using PFN_vkGetSemaphoreZirconHandleFUCHSIA = VkResult (*) (VkDevice   device, const  VkSemaphoreGetZirconHandleInfoFUCHSIA *  pGetZirconHandleInfo, zx_handle_t *  pZirconHandle);
using PFN_vkImportSemaphoreZirconHandleFUCHSIA = VkResult (*) (VkDevice   device, const  VkImportSemaphoreZirconHandleInfoFUCHSIA *  pImportSemaphoreZirconHandleInfo);
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
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
#if defined(VK_USE_PLATFORM_WIN32_KHR)
using PFN_vkAcquireWinrtDisplayNV = VkResult (*) (VkPhysicalDevice   physicalDevice, VkDisplayKHR   display);
using PFN_vkGetWinrtDisplayNV = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t   deviceRelativeId, VkDisplayKHR *  pDisplay);
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
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
using PFN_vkDestroyAccelerationStructureKHR = void (*) (VkDevice   device, VkAccelerationStructureKHR   accelerationStructure, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkDestroyAccelerationStructureNV = void (*) (VkDevice   device, VkAccelerationStructureNV   accelerationStructure, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetAccelerationStructureMemoryRequirementsNV = void (*) (VkDevice   device, const  VkAccelerationStructureMemoryRequirementsInfoNV *  pInfo, VkMemoryRequirements2KHR *  pMemoryRequirements);
using PFN_vkBindAccelerationStructureMemoryNV = VkResult (*) (VkDevice   device, uint32_t   bindInfoCount, const  VkBindAccelerationStructureMemoryInfoNV *  pBindInfos);
using PFN_vkCmdCopyAccelerationStructureNV = void (*) (VkCommandBuffer   commandBuffer, VkAccelerationStructureNV   dst, VkAccelerationStructureNV   src, VkCopyAccelerationStructureModeKHR   mode);
using PFN_vkCmdCopyAccelerationStructureKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCopyAccelerationStructureKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   deferredOperation, const  VkCopyAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCmdCopyAccelerationStructureToMemoryKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyAccelerationStructureToMemoryInfoKHR *  pInfo);
using PFN_vkCopyAccelerationStructureToMemoryKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   deferredOperation, const  VkCopyAccelerationStructureToMemoryInfoKHR *  pInfo);
using PFN_vkCmdCopyMemoryToAccelerationStructureKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkCopyMemoryToAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCopyMemoryToAccelerationStructureKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   deferredOperation, const  VkCopyMemoryToAccelerationStructureInfoKHR *  pInfo);
using PFN_vkCmdWriteAccelerationStructuresPropertiesKHR = void (*) (VkCommandBuffer   commandBuffer, uint32_t   accelerationStructureCount, const  VkAccelerationStructureKHR *  pAccelerationStructures, VkQueryType   queryType, VkQueryPool   queryPool, uint32_t   firstQuery);
using PFN_vkCmdWriteAccelerationStructuresPropertiesNV = void (*) (VkCommandBuffer   commandBuffer, uint32_t   accelerationStructureCount, const  VkAccelerationStructureNV *  pAccelerationStructures, VkQueryType   queryType, VkQueryPool   queryPool, uint32_t   firstQuery);
using PFN_vkCmdBuildAccelerationStructureNV = void (*) (VkCommandBuffer   commandBuffer, const  VkAccelerationStructureInfoNV *  pInfo, VkBuffer   instanceData, VkDeviceSize   instanceOffset, VkBool32   update, VkAccelerationStructureNV   dst, VkAccelerationStructureNV   src, VkBuffer   scratch, VkDeviceSize   scratchOffset);
using PFN_vkWriteAccelerationStructuresPropertiesKHR = VkResult (*) (VkDevice   device, uint32_t   accelerationStructureCount, const  VkAccelerationStructureKHR *  pAccelerationStructures, VkQueryType    queryType, size_t         dataSize, void *  pData, size_t   stride);
using PFN_vkCmdTraceRaysKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkStridedDeviceAddressRegionKHR *  pRaygenShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pMissShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pHitShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pCallableShaderBindingTable, uint32_t   width, uint32_t   height, uint32_t   depth);
using PFN_vkCmdTraceRaysNV = void (*) (VkCommandBuffer   commandBuffer, VkBuffer   raygenShaderBindingTableBuffer, VkDeviceSize   raygenShaderBindingOffset, VkBuffer   missShaderBindingTableBuffer, VkDeviceSize   missShaderBindingOffset, VkDeviceSize   missShaderBindingStride, VkBuffer   hitShaderBindingTableBuffer, VkDeviceSize   hitShaderBindingOffset, VkDeviceSize   hitShaderBindingStride, VkBuffer   callableShaderBindingTableBuffer, VkDeviceSize   callableShaderBindingOffset, VkDeviceSize   callableShaderBindingStride, uint32_t   width, uint32_t   height, uint32_t   depth);
using PFN_vkGetRayTracingShaderGroupHandlesKHR = VkResult (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   firstGroup, uint32_t   groupCount, size_t   dataSize, void *  pData);
using PFN_vkGetRayTracingShaderGroupHandlesNV = PFN_vkGetRayTracingShaderGroupHandlesKHR;
using PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = VkResult (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   firstGroup, uint32_t   groupCount, size_t   dataSize, void *  pData);
using PFN_vkGetAccelerationStructureHandleNV = VkResult (*) (VkDevice   device, VkAccelerationStructureNV   accelerationStructure, size_t   dataSize, void *  pData);
using PFN_vkCreateRayTracingPipelinesNV = VkResult (*) (VkDevice   device, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkRayTracingPipelineCreateInfoNV *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
using PFN_vkCreateRayTracingPipelinesKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   deferredOperation, VkPipelineCache   pipelineCache, uint32_t   createInfoCount, const  VkRayTracingPipelineCreateInfoKHR *  pCreateInfos, const  VkAllocationCallbacks *  pAllocator, VkPipeline *  pPipelines);
using PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pPropertyCount, VkCooperativeMatrixPropertiesNV *  pProperties);
using PFN_vkCmdTraceRaysIndirectKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkStridedDeviceAddressRegionKHR *  pRaygenShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pMissShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pHitShaderBindingTable, const  VkStridedDeviceAddressRegionKHR *  pCallableShaderBindingTable, VkDeviceAddress   indirectDeviceAddress);
using PFN_vkGetDeviceAccelerationStructureCompatibilityKHR = void (*) (VkDevice   device, const  VkAccelerationStructureVersionInfoKHR *  pVersionInfo, VkAccelerationStructureCompatibilityKHR *  pCompatibility);
using PFN_vkGetRayTracingShaderGroupStackSizeKHR = VkDeviceSize (*) (VkDevice   device, VkPipeline   pipeline, uint32_t   group, VkShaderGroupShaderKHR   groupShader);
using PFN_vkCmdSetRayTracingPipelineStackSizeKHR = void (*) (VkCommandBuffer   commandBuffer, uint32_t   pipelineStackSize);
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
using PFN_vkCreateAccelerationStructureKHR = VkResult (*) (VkDevice                                             device, const  VkAccelerationStructureCreateInfoKHR *         pCreateInfo, const  VkAllocationCallbacks *        pAllocator, VkAccelerationStructureKHR *                         pAccelerationStructure);
using PFN_vkCmdBuildAccelerationStructuresKHR = void (*) (VkCommandBuffer                                      commandBuffer, uint32_t   infoCount, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfos, const  VkAccelerationStructureBuildRangeInfoKHR * const*  ppBuildRangeInfos);
using PFN_vkCmdBuildAccelerationStructuresIndirectKHR = void (*) (VkCommandBuffer                    commandBuffer, uint32_t                                             infoCount, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfos, const  VkDeviceAddress *              pIndirectDeviceAddresses, const  uint32_t *                     pIndirectStrides, const  uint32_t * const*              ppMaxPrimitiveCounts);
using PFN_vkBuildAccelerationStructuresKHR = VkResult (*) (VkDevice                                             device, VkDeferredOperationKHR   deferredOperation, uint32_t   infoCount, const  VkAccelerationStructureBuildGeometryInfoKHR *  pInfos, const  VkAccelerationStructureBuildRangeInfoKHR * const*  ppBuildRangeInfos);
using PFN_vkGetAccelerationStructureDeviceAddressKHR = VkDeviceAddress (*) (VkDevice   device, const  VkAccelerationStructureDeviceAddressInfoKHR *  pInfo);
using PFN_vkCreateDeferredOperationKHR = VkResult (*) (VkDevice   device, const  VkAllocationCallbacks *  pAllocator, VkDeferredOperationKHR *  pDeferredOperation);
using PFN_vkDestroyDeferredOperationKHR = void (*) (VkDevice   device, VkDeferredOperationKHR   operation, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetDeferredOperationMaxConcurrencyKHR = uint32_t (*) (VkDevice   device, VkDeferredOperationKHR   operation);
using PFN_vkGetDeferredOperationResultKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   operation);
using PFN_vkDeferredOperationJoinKHR = VkResult (*) (VkDevice   device, VkDeferredOperationKHR   operation);
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
using PFN_vkCmdSetPatchControlPointsEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   patchControlPoints);
using PFN_vkCmdSetRasterizerDiscardEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   rasterizerDiscardEnable);
using PFN_vkCmdSetDepthBiasEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   depthBiasEnable);
using PFN_vkCmdSetLogicOpEXT = void (*) (VkCommandBuffer   commandBuffer, VkLogicOp   logicOp);
using PFN_vkCmdSetPrimitiveRestartEnableEXT = void (*) (VkCommandBuffer   commandBuffer, VkBool32   primitiveRestartEnable);
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
using PFN_vkCmdSetFragmentShadingRateKHR = void (*) (VkCommandBuffer             commandBuffer, const  VkExtent2D *                            pFragmentSize, const  VkFragmentShadingRateCombinerOpKHR      combinerOps [2]);
using PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, uint32_t *  pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR *  pFragmentShadingRates);
using PFN_vkCmdSetFragmentShadingRateEnumNV = void (*) (VkCommandBuffer             commandBuffer, VkFragmentShadingRateNV                       shadingRate, const  VkFragmentShadingRateCombinerOpKHR      combinerOps [2]);
using PFN_vkGetAccelerationStructureBuildSizesKHR = void (*) (VkDevice                                              device, VkAccelerationStructureBuildTypeKHR                   buildType, const  VkAccelerationStructureBuildGeometryInfoKHR *   pBuildInfo, const  uint32_t *   pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR *            pSizeInfo);
using PFN_vkCmdSetVertexInputEXT = void (*) (VkCommandBuffer   commandBuffer, uint32_t   vertexBindingDescriptionCount, const  VkVertexInputBindingDescription2EXT *  pVertexBindingDescriptions, uint32_t   vertexAttributeDescriptionCount, const  VkVertexInputAttributeDescription2EXT *  pVertexAttributeDescriptions);
using PFN_vkCmdSetColorWriteEnableEXT = void (*) (VkCommandBuffer         commandBuffer, uint32_t                                  attachmentCount, const  VkBool32 *    pColorWriteEnables);
using PFN_vkCmdSetEvent2KHR = void (*) (VkCommandBuffer                     commandBuffer, VkEvent                                               event, const  VkDependencyInfoKHR *                           pDependencyInfo);
using PFN_vkCmdResetEvent2KHR = void (*) (VkCommandBuffer                     commandBuffer, VkEvent                                               event, VkPipelineStageFlags2KHR                              stageMask);
using PFN_vkCmdWaitEvents2KHR = void (*) (VkCommandBuffer                     commandBuffer, uint32_t                                              eventCount, const  VkEvent *                      pEvents, const  VkDependencyInfoKHR *          pDependencyInfos);
using PFN_vkCmdPipelineBarrier2KHR = void (*) (VkCommandBuffer                     commandBuffer, const  VkDependencyInfoKHR *                                 pDependencyInfo);
using PFN_vkQueueSubmit2KHR = VkResult (*) (VkQueue                             queue, uint32_t                              submitCount, const  VkSubmitInfo2KHR *            pSubmits, VkFence             fence);
using PFN_vkCmdWriteTimestamp2KHR = void (*) (VkCommandBuffer                     commandBuffer, VkPipelineStageFlags2KHR                              stage, VkQueryPool                                           queryPool, uint32_t                                              query);
using PFN_vkCmdWriteBufferMarker2AMD = void (*) (VkCommandBuffer                     commandBuffer, VkPipelineStageFlags2KHR                              stage, VkBuffer                                              dstBuffer, VkDeviceSize                                          dstOffset, uint32_t                                              marker);
using PFN_vkGetQueueCheckpointData2NV = void (*) (VkQueue   queue, uint32_t *  pCheckpointDataCount, VkCheckpointData2NV *  pCheckpointData);
#if defined(VK_ENABLE_BETA_EXTENSIONS)
using PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkVideoProfileKHR *  pVideoProfile, VkVideoCapabilitiesKHR *  pCapabilities);
using PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR = VkResult (*) (VkPhysicalDevice   physicalDevice, const  VkPhysicalDeviceVideoFormatInfoKHR *  pVideoFormatInfo, uint32_t *  pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR *  pVideoFormatProperties);
using PFN_vkCreateVideoSessionKHR = VkResult (*) (VkDevice   device, const  VkVideoSessionCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkVideoSessionKHR *  pVideoSession);
using PFN_vkDestroyVideoSessionKHR = void (*) (VkDevice   device, VkVideoSessionKHR   videoSession, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkCreateVideoSessionParametersKHR = VkResult (*) (VkDevice   device, const  VkVideoSessionParametersCreateInfoKHR *  pCreateInfo, const  VkAllocationCallbacks *  pAllocator, VkVideoSessionParametersKHR *  pVideoSessionParameters);
using PFN_vkUpdateVideoSessionParametersKHR = VkResult (*) (VkDevice   device, VkVideoSessionParametersKHR   videoSessionParameters, const  VkVideoSessionParametersUpdateInfoKHR *  pUpdateInfo);
using PFN_vkDestroyVideoSessionParametersKHR = void (*) (VkDevice   device, VkVideoSessionParametersKHR   videoSessionParameters, const  VkAllocationCallbacks *  pAllocator);
using PFN_vkGetVideoSessionMemoryRequirementsKHR = VkResult (*) (VkDevice   device, VkVideoSessionKHR   videoSession, uint32_t *  pVideoSessionMemoryRequirementsCount, VkVideoGetMemoryPropertiesKHR *  pVideoSessionMemoryRequirements);
using PFN_vkBindVideoSessionMemoryKHR = VkResult (*) (VkDevice   device, VkVideoSessionKHR   videoSession, uint32_t   videoSessionBindMemoryCount, const  VkVideoBindMemoryKHR *  pVideoSessionBindMemories);
using PFN_vkCmdDecodeVideoKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkVideoDecodeInfoKHR *  pFrameInfo);
using PFN_vkCmdBeginVideoCodingKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkVideoBeginCodingInfoKHR *  pBeginInfo);
using PFN_vkCmdControlVideoCodingKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkVideoCodingControlInfoKHR *  pCodingControlInfo);
using PFN_vkCmdEndVideoCodingKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkVideoEndCodingInfoKHR *  pEndCodingInfo);
using PFN_vkCmdEncodeVideoKHR = void (*) (VkCommandBuffer   commandBuffer, const  VkVideoEncodeInfoKHR *  pEncodeInfo);
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
extern PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
extern PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
extern PFN_vkDestroyInstance vkDestroyInstance;
extern PFN_vkEnumeratePhysicalDevices vkEnumeratePhysicalDevices;
extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
extern PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
extern PFN_vkGetPhysicalDeviceMemoryProperties vkGetPhysicalDeviceMemoryProperties;
extern PFN_vkGetPhysicalDeviceFeatures vkGetPhysicalDeviceFeatures;
extern PFN_vkGetPhysicalDeviceFormatProperties vkGetPhysicalDeviceFormatProperties;
extern PFN_vkGetPhysicalDeviceImageFormatProperties vkGetPhysicalDeviceImageFormatProperties;
extern PFN_vkCreateDevice vkCreateDevice;
extern PFN_vkEnumerateDeviceExtensionProperties vkEnumerateDeviceExtensionProperties;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties;
extern PFN_vkEnumeratePhysicalDeviceGroups vkEnumeratePhysicalDeviceGroups;
extern PFN_vkGetPhysicalDeviceFeatures2 vkGetPhysicalDeviceFeatures2;
extern PFN_vkGetPhysicalDeviceProperties2 vkGetPhysicalDeviceProperties2;
extern PFN_vkGetPhysicalDeviceFormatProperties2 vkGetPhysicalDeviceFormatProperties2;
extern PFN_vkGetPhysicalDeviceImageFormatProperties2 vkGetPhysicalDeviceImageFormatProperties2;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties2 vkGetPhysicalDeviceQueueFamilyProperties2;
extern PFN_vkGetPhysicalDeviceMemoryProperties2 vkGetPhysicalDeviceMemoryProperties2;
extern PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2;
extern PFN_vkGetPhysicalDeviceExternalBufferProperties vkGetPhysicalDeviceExternalBufferProperties;
extern PFN_vkGetPhysicalDeviceExternalFenceProperties vkGetPhysicalDeviceExternalFenceProperties;
extern PFN_vkGetPhysicalDeviceExternalSemaphoreProperties vkGetPhysicalDeviceExternalSemaphoreProperties;
extern PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
extern PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
extern PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
extern PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR;
extern PFN_vkGetPhysicalDeviceDisplayPropertiesKHR vkGetPhysicalDeviceDisplayPropertiesKHR;
extern PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR;
extern PFN_vkGetDisplayPlaneSupportedDisplaysKHR vkGetDisplayPlaneSupportedDisplaysKHR;
extern PFN_vkGetDisplayModePropertiesKHR vkGetDisplayModePropertiesKHR;
extern PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
extern PFN_vkGetDisplayPlaneCapabilitiesKHR vkGetDisplayPlaneCapabilitiesKHR;
extern PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
#if defined(VK_USE_PLATFORM_XLIB_KHR)
extern PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
#if defined(VK_USE_PLATFORM_XCB_KHR)
extern PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
extern PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
extern PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
extern PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
extern PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
extern PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
extern PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
extern PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
extern PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR vkGetPhysicalDeviceVideoCapabilitiesKHR;
extern PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_USE_PLATFORM_GGP)
extern PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP;
#endif // defined(VK_USE_PLATFORM_GGP)
extern PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV;
#if defined(VK_USE_PLATFORM_VI_NN)
extern PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN;
#endif // defined(VK_USE_PLATFORM_VI_NN)
extern PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT;
#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
extern PFN_vkAcquireXlibDisplayEXT vkAcquireXlibDisplayEXT;
extern PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT;
#endif // defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT;
extern PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
extern PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
extern PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR;
extern PFN_vkGetPhysicalDeviceSurfaceFormats2KHR vkGetPhysicalDeviceSurfaceFormats2KHR;
extern PFN_vkGetPhysicalDeviceDisplayProperties2KHR vkGetPhysicalDeviceDisplayProperties2KHR;
extern PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR;
extern PFN_vkGetDisplayModeProperties2KHR vkGetDisplayModeProperties2KHR;
extern PFN_vkGetDisplayPlaneCapabilities2KHR vkGetDisplayPlaneCapabilities2KHR;
#if defined(VK_USE_PLATFORM_IOS_MVK)
extern PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK;
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
#if defined(VK_USE_PLATFORM_MACOS_MVK)
extern PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
extern PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
extern PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
extern PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;
extern PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT;
extern PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
#if defined(VK_USE_PLATFORM_FUCHSIA)
extern PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_METAL_EXT)
extern PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT;
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
extern PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR;
extern PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT;
extern PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV;
extern PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV;
extern PFN_vkGetWinrtDisplayNV vkGetWinrtDisplayNV;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
extern PFN_vkCreateDirectFBSurfaceEXT vkCreateDirectFBSurfaceEXT;
extern PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT;
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
extern PFN_vkCreateScreenSurfaceQNX vkCreateScreenSurfaceQNX;
extern PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX;
#endif // defined(VK_USE_PLATFORM_SCREEN_QNX)
extern PFN_vkDestroyDevice vkDestroyDevice;
extern PFN_vkGetDeviceQueue vkGetDeviceQueue;
extern PFN_vkQueueSubmit vkQueueSubmit;
extern PFN_vkQueueWaitIdle vkQueueWaitIdle;
extern PFN_vkDeviceWaitIdle vkDeviceWaitIdle;
extern PFN_vkAllocateMemory vkAllocateMemory;
extern PFN_vkFreeMemory vkFreeMemory;
extern PFN_vkMapMemory vkMapMemory;
extern PFN_vkUnmapMemory vkUnmapMemory;
extern PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
extern PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges;
extern PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment;
extern PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements;
extern PFN_vkBindBufferMemory vkBindBufferMemory;
extern PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements;
extern PFN_vkBindImageMemory vkBindImageMemory;
extern PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements;
extern PFN_vkQueueBindSparse vkQueueBindSparse;
extern PFN_vkCreateFence vkCreateFence;
extern PFN_vkDestroyFence vkDestroyFence;
extern PFN_vkResetFences vkResetFences;
extern PFN_vkGetFenceStatus vkGetFenceStatus;
extern PFN_vkWaitForFences vkWaitForFences;
extern PFN_vkCreateSemaphore vkCreateSemaphore;
extern PFN_vkDestroySemaphore vkDestroySemaphore;
extern PFN_vkCreateEvent vkCreateEvent;
extern PFN_vkDestroyEvent vkDestroyEvent;
extern PFN_vkGetEventStatus vkGetEventStatus;
extern PFN_vkSetEvent vkSetEvent;
extern PFN_vkResetEvent vkResetEvent;
extern PFN_vkCreateQueryPool vkCreateQueryPool;
extern PFN_vkDestroyQueryPool vkDestroyQueryPool;
extern PFN_vkGetQueryPoolResults vkGetQueryPoolResults;
extern PFN_vkCreateBuffer vkCreateBuffer;
extern PFN_vkDestroyBuffer vkDestroyBuffer;
extern PFN_vkCreateBufferView vkCreateBufferView;
extern PFN_vkDestroyBufferView vkDestroyBufferView;
extern PFN_vkCreateImage vkCreateImage;
extern PFN_vkDestroyImage vkDestroyImage;
extern PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout;
extern PFN_vkCreateImageView vkCreateImageView;
extern PFN_vkDestroyImageView vkDestroyImageView;
extern PFN_vkCreateShaderModule vkCreateShaderModule;
extern PFN_vkDestroyShaderModule vkDestroyShaderModule;
extern PFN_vkCreatePipelineCache vkCreatePipelineCache;
extern PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
extern PFN_vkGetPipelineCacheData vkGetPipelineCacheData;
extern PFN_vkMergePipelineCaches vkMergePipelineCaches;
extern PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
extern PFN_vkCreateComputePipelines vkCreateComputePipelines;
extern PFN_vkDestroyPipeline vkDestroyPipeline;
extern PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
extern PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
extern PFN_vkCreateSampler vkCreateSampler;
extern PFN_vkDestroySampler vkDestroySampler;
extern PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
extern PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
extern PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
extern PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
extern PFN_vkResetDescriptorPool vkResetDescriptorPool;
extern PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets;
extern PFN_vkFreeDescriptorSets vkFreeDescriptorSets;
extern PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets;
extern PFN_vkCreateFramebuffer vkCreateFramebuffer;
extern PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
extern PFN_vkCreateRenderPass vkCreateRenderPass;
extern PFN_vkDestroyRenderPass vkDestroyRenderPass;
extern PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity;
extern PFN_vkCreateCommandPool vkCreateCommandPool;
extern PFN_vkDestroyCommandPool vkDestroyCommandPool;
extern PFN_vkResetCommandPool vkResetCommandPool;
extern PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers;
extern PFN_vkFreeCommandBuffers vkFreeCommandBuffers;
extern PFN_vkBeginCommandBuffer vkBeginCommandBuffer;
extern PFN_vkEndCommandBuffer vkEndCommandBuffer;
extern PFN_vkResetCommandBuffer vkResetCommandBuffer;
extern PFN_vkCmdBindPipeline vkCmdBindPipeline;
extern PFN_vkCmdSetViewport vkCmdSetViewport;
extern PFN_vkCmdSetScissor vkCmdSetScissor;
extern PFN_vkCmdSetLineWidth vkCmdSetLineWidth;
extern PFN_vkCmdSetDepthBias vkCmdSetDepthBias;
extern PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants;
extern PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds;
extern PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask;
extern PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask;
extern PFN_vkCmdSetStencilReference vkCmdSetStencilReference;
extern PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets;
extern PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer;
extern PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers;
extern PFN_vkCmdDraw vkCmdDraw;
extern PFN_vkCmdDrawIndexed vkCmdDrawIndexed;
extern PFN_vkCmdDrawIndirect vkCmdDrawIndirect;
extern PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect;
extern PFN_vkCmdDispatch vkCmdDispatch;
extern PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect;
extern PFN_vkCmdCopyBuffer vkCmdCopyBuffer;
extern PFN_vkCmdCopyImage vkCmdCopyImage;
extern PFN_vkCmdBlitImage vkCmdBlitImage;
extern PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage;
extern PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer;
extern PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer;
extern PFN_vkCmdFillBuffer vkCmdFillBuffer;
extern PFN_vkCmdClearColorImage vkCmdClearColorImage;
extern PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage;
extern PFN_vkCmdClearAttachments vkCmdClearAttachments;
extern PFN_vkCmdResolveImage vkCmdResolveImage;
extern PFN_vkCmdSetEvent vkCmdSetEvent;
extern PFN_vkCmdResetEvent vkCmdResetEvent;
extern PFN_vkCmdWaitEvents vkCmdWaitEvents;
extern PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier;
extern PFN_vkCmdBeginQuery vkCmdBeginQuery;
extern PFN_vkCmdEndQuery vkCmdEndQuery;
extern PFN_vkCmdResetQueryPool vkCmdResetQueryPool;
extern PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp;
extern PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
extern PFN_vkCmdPushConstants vkCmdPushConstants;
extern PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass;
extern PFN_vkCmdNextSubpass vkCmdNextSubpass;
extern PFN_vkCmdEndRenderPass vkCmdEndRenderPass;
extern PFN_vkCmdExecuteCommands vkCmdExecuteCommands;
extern PFN_vkBindBufferMemory2 vkBindBufferMemory2;
extern PFN_vkBindImageMemory2 vkBindImageMemory2;
extern PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures;
extern PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask;
extern PFN_vkCmdDispatchBase vkCmdDispatchBase;
extern PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2;
extern PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2;
extern PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2;
extern PFN_vkTrimCommandPool vkTrimCommandPool;
extern PFN_vkGetDeviceQueue2 vkGetDeviceQueue2;
extern PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion;
extern PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion;
extern PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate;
extern PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate;
extern PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate;
extern PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport;
extern PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount;
extern PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount;
extern PFN_vkCreateRenderPass2 vkCreateRenderPass2;
extern PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2;
extern PFN_vkCmdNextSubpass2 vkCmdNextSubpass2;
extern PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2;
extern PFN_vkResetQueryPool vkResetQueryPool;
extern PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue;
extern PFN_vkWaitSemaphores vkWaitSemaphores;
extern PFN_vkSignalSemaphore vkSignalSemaphore;
extern PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress;
extern PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress;
extern PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress;
extern PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
extern PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
extern PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR;
extern PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR;
extern PFN_vkQueuePresentKHR vkQueuePresentKHR;
extern PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR;
extern PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR;
extern PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR;
extern PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR;
extern PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT;
extern PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT;
extern PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT;
extern PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT;
extern PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
extern PFN_vkCreateVideoSessionKHR vkCreateVideoSessionKHR;
extern PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR;
extern PFN_vkCreateVideoSessionParametersKHR vkCreateVideoSessionParametersKHR;
extern PFN_vkUpdateVideoSessionParametersKHR vkUpdateVideoSessionParametersKHR;
extern PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR;
extern PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR;
extern PFN_vkBindVideoSessionMemoryKHR vkBindVideoSessionMemoryKHR;
extern PFN_vkCmdBeginVideoCodingKHR vkCmdBeginVideoCodingKHR;
extern PFN_vkCmdControlVideoCodingKHR vkCmdControlVideoCodingKHR;
extern PFN_vkCmdEndVideoCodingKHR vkCmdEndVideoCodingKHR;
extern PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR;
extern PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
extern PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT;
extern PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT;
extern PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT;
extern PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT;
extern PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT;
extern PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT;
extern PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX;
extern PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX;
extern PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV;
extern PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR;
extern PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR;
extern PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR;
extern PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR;
extern PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR;
extern PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR;
extern PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR;
extern PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT;
extern PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT;
extern PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV;
extern PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT;
extern PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT;
extern PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT;
extern PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT;
extern PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE;
extern PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE;
extern PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT;
extern PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT;
extern PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR;
extern PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkGetFenceFdKHR vkGetFenceFdKHR;
extern PFN_vkImportFenceFdKHR vkImportFenceFdKHR;
extern PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR;
extern PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR;
extern PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT;
extern PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT;
extern PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT;
extern PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT;
extern PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
extern PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT;
extern PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT;
extern PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
extern PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID;
extern PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
extern PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT;
extern PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
extern PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR;
extern PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR;
extern PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR;
extern PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR;
extern PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR;
extern PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR;
extern PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
extern PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
extern PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR;
extern PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
extern PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
extern PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
extern PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
extern PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
extern PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR;
extern PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;
extern PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR;
extern PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR;
extern PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR;
extern PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT;
extern PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT;
extern PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT;
extern PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT;
extern PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT;
extern PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV;
extern PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV;
extern PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV;
extern PFN_vkCompileDeferredNV vkCompileDeferredNV;
extern PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV;
extern PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV;
extern PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV;
extern PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV;
extern PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV;
extern PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV;
extern PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV;
extern PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV;
extern PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV;
extern PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV;
extern PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT;
extern PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD;
extern PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT;
extern PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV;
extern PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV;
extern PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV;
extern PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV;
extern PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV;
extern PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV;
extern PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL;
extern PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL;
extern PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL;
extern PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL;
extern PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL;
extern PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL;
extern PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL;
extern PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL;
extern PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL;
extern PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD;
extern PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT;
extern PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT;
extern PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
extern PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT;
extern PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT;
extern PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT;
extern PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT;
extern PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT;
extern PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT;
extern PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT;
extern PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT;
extern PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT;
extern PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT;
extern PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT;
extern PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT;
extern PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT;
extern PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR;
extern PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR;
extern PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR;
extern PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR;
extern PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR;
extern PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR;
extern PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR;
extern PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR;
extern PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV;
extern PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV;
extern PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV;
extern PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV;
extern PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV;
extern PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV;
extern PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT;
extern PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT;
extern PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT;
extern PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT;
extern PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR;
extern PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR;
extern PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR;
extern PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR;
extern PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR;
extern PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR;
extern PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD;
extern PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV;
extern PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV;
extern PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR;
extern PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR;
extern PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR;
extern PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR;
extern PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR;
extern PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR;
extern PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT;
#if defined(VK_USE_PLATFORM_FUCHSIA)
extern PFN_vkGetMemoryZirconHandleFUCHSIA vkGetMemoryZirconHandleFUCHSIA;
extern PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA;
extern PFN_vkGetSemaphoreZirconHandleFUCHSIA vkGetSemaphoreZirconHandleFUCHSIA;
extern PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
extern PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT;
extern PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT;
extern PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT;
extern PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT;
extern PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT;
extern PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT;
struct VkDeviceDispatchTable {
    PFN_vkDestroyDevice vkDestroyDevice = nullptr;
    PFN_vkGetDeviceQueue vkGetDeviceQueue = nullptr;
    PFN_vkQueueSubmit vkQueueSubmit = nullptr;
    PFN_vkQueueWaitIdle vkQueueWaitIdle = nullptr;
    PFN_vkDeviceWaitIdle vkDeviceWaitIdle = nullptr;
    PFN_vkAllocateMemory vkAllocateMemory = nullptr;
    PFN_vkFreeMemory vkFreeMemory = nullptr;
    PFN_vkMapMemory vkMapMemory = nullptr;
    PFN_vkUnmapMemory vkUnmapMemory = nullptr;
    PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges = nullptr;
    PFN_vkInvalidateMappedMemoryRanges vkInvalidateMappedMemoryRanges = nullptr;
    PFN_vkGetDeviceMemoryCommitment vkGetDeviceMemoryCommitment = nullptr;
    PFN_vkGetBufferMemoryRequirements vkGetBufferMemoryRequirements = nullptr;
    PFN_vkBindBufferMemory vkBindBufferMemory = nullptr;
    PFN_vkGetImageMemoryRequirements vkGetImageMemoryRequirements = nullptr;
    PFN_vkBindImageMemory vkBindImageMemory = nullptr;
    PFN_vkGetImageSparseMemoryRequirements vkGetImageSparseMemoryRequirements = nullptr;
    PFN_vkQueueBindSparse vkQueueBindSparse = nullptr;
    PFN_vkCreateFence vkCreateFence = nullptr;
    PFN_vkDestroyFence vkDestroyFence = nullptr;
    PFN_vkResetFences vkResetFences = nullptr;
    PFN_vkGetFenceStatus vkGetFenceStatus = nullptr;
    PFN_vkWaitForFences vkWaitForFences = nullptr;
    PFN_vkCreateSemaphore vkCreateSemaphore = nullptr;
    PFN_vkDestroySemaphore vkDestroySemaphore = nullptr;
    PFN_vkCreateEvent vkCreateEvent = nullptr;
    PFN_vkDestroyEvent vkDestroyEvent = nullptr;
    PFN_vkGetEventStatus vkGetEventStatus = nullptr;
    PFN_vkSetEvent vkSetEvent = nullptr;
    PFN_vkResetEvent vkResetEvent = nullptr;
    PFN_vkCreateQueryPool vkCreateQueryPool = nullptr;
    PFN_vkDestroyQueryPool vkDestroyQueryPool = nullptr;
    PFN_vkGetQueryPoolResults vkGetQueryPoolResults = nullptr;
    PFN_vkCreateBuffer vkCreateBuffer = nullptr;
    PFN_vkDestroyBuffer vkDestroyBuffer = nullptr;
    PFN_vkCreateBufferView vkCreateBufferView = nullptr;
    PFN_vkDestroyBufferView vkDestroyBufferView = nullptr;
    PFN_vkCreateImage vkCreateImage = nullptr;
    PFN_vkDestroyImage vkDestroyImage = nullptr;
    PFN_vkGetImageSubresourceLayout vkGetImageSubresourceLayout = nullptr;
    PFN_vkCreateImageView vkCreateImageView = nullptr;
    PFN_vkDestroyImageView vkDestroyImageView = nullptr;
    PFN_vkCreateShaderModule vkCreateShaderModule = nullptr;
    PFN_vkDestroyShaderModule vkDestroyShaderModule = nullptr;
    PFN_vkCreatePipelineCache vkCreatePipelineCache = nullptr;
    PFN_vkDestroyPipelineCache vkDestroyPipelineCache = nullptr;
    PFN_vkGetPipelineCacheData vkGetPipelineCacheData = nullptr;
    PFN_vkMergePipelineCaches vkMergePipelineCaches = nullptr;
    PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines = nullptr;
    PFN_vkCreateComputePipelines vkCreateComputePipelines = nullptr;
    PFN_vkDestroyPipeline vkDestroyPipeline = nullptr;
    PFN_vkCreatePipelineLayout vkCreatePipelineLayout = nullptr;
    PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout = nullptr;
    PFN_vkCreateSampler vkCreateSampler = nullptr;
    PFN_vkDestroySampler vkDestroySampler = nullptr;
    PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout = nullptr;
    PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout = nullptr;
    PFN_vkCreateDescriptorPool vkCreateDescriptorPool = nullptr;
    PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool = nullptr;
    PFN_vkResetDescriptorPool vkResetDescriptorPool = nullptr;
    PFN_vkAllocateDescriptorSets vkAllocateDescriptorSets = nullptr;
    PFN_vkFreeDescriptorSets vkFreeDescriptorSets = nullptr;
    PFN_vkUpdateDescriptorSets vkUpdateDescriptorSets = nullptr;
    PFN_vkCreateFramebuffer vkCreateFramebuffer = nullptr;
    PFN_vkDestroyFramebuffer vkDestroyFramebuffer = nullptr;
    PFN_vkCreateRenderPass vkCreateRenderPass = nullptr;
    PFN_vkDestroyRenderPass vkDestroyRenderPass = nullptr;
    PFN_vkGetRenderAreaGranularity vkGetRenderAreaGranularity = nullptr;
    PFN_vkCreateCommandPool vkCreateCommandPool = nullptr;
    PFN_vkDestroyCommandPool vkDestroyCommandPool = nullptr;
    PFN_vkResetCommandPool vkResetCommandPool = nullptr;
    PFN_vkAllocateCommandBuffers vkAllocateCommandBuffers = nullptr;
    PFN_vkFreeCommandBuffers vkFreeCommandBuffers = nullptr;
    PFN_vkBeginCommandBuffer vkBeginCommandBuffer = nullptr;
    PFN_vkEndCommandBuffer vkEndCommandBuffer = nullptr;
    PFN_vkResetCommandBuffer vkResetCommandBuffer = nullptr;
    PFN_vkCmdBindPipeline vkCmdBindPipeline = nullptr;
    PFN_vkCmdSetViewport vkCmdSetViewport = nullptr;
    PFN_vkCmdSetScissor vkCmdSetScissor = nullptr;
    PFN_vkCmdSetLineWidth vkCmdSetLineWidth = nullptr;
    PFN_vkCmdSetDepthBias vkCmdSetDepthBias = nullptr;
    PFN_vkCmdSetBlendConstants vkCmdSetBlendConstants = nullptr;
    PFN_vkCmdSetDepthBounds vkCmdSetDepthBounds = nullptr;
    PFN_vkCmdSetStencilCompareMask vkCmdSetStencilCompareMask = nullptr;
    PFN_vkCmdSetStencilWriteMask vkCmdSetStencilWriteMask = nullptr;
    PFN_vkCmdSetStencilReference vkCmdSetStencilReference = nullptr;
    PFN_vkCmdBindDescriptorSets vkCmdBindDescriptorSets = nullptr;
    PFN_vkCmdBindIndexBuffer vkCmdBindIndexBuffer = nullptr;
    PFN_vkCmdBindVertexBuffers vkCmdBindVertexBuffers = nullptr;
    PFN_vkCmdDraw vkCmdDraw = nullptr;
    PFN_vkCmdDrawIndexed vkCmdDrawIndexed = nullptr;
    PFN_vkCmdDrawIndirect vkCmdDrawIndirect = nullptr;
    PFN_vkCmdDrawIndexedIndirect vkCmdDrawIndexedIndirect = nullptr;
    PFN_vkCmdDispatch vkCmdDispatch = nullptr;
    PFN_vkCmdDispatchIndirect vkCmdDispatchIndirect = nullptr;
    PFN_vkCmdCopyBuffer vkCmdCopyBuffer = nullptr;
    PFN_vkCmdCopyImage vkCmdCopyImage = nullptr;
    PFN_vkCmdBlitImage vkCmdBlitImage = nullptr;
    PFN_vkCmdCopyBufferToImage vkCmdCopyBufferToImage = nullptr;
    PFN_vkCmdCopyImageToBuffer vkCmdCopyImageToBuffer = nullptr;
    PFN_vkCmdUpdateBuffer vkCmdUpdateBuffer = nullptr;
    PFN_vkCmdFillBuffer vkCmdFillBuffer = nullptr;
    PFN_vkCmdClearColorImage vkCmdClearColorImage = nullptr;
    PFN_vkCmdClearDepthStencilImage vkCmdClearDepthStencilImage = nullptr;
    PFN_vkCmdClearAttachments vkCmdClearAttachments = nullptr;
    PFN_vkCmdResolveImage vkCmdResolveImage = nullptr;
    PFN_vkCmdSetEvent vkCmdSetEvent = nullptr;
    PFN_vkCmdResetEvent vkCmdResetEvent = nullptr;
    PFN_vkCmdWaitEvents vkCmdWaitEvents = nullptr;
    PFN_vkCmdPipelineBarrier vkCmdPipelineBarrier = nullptr;
    PFN_vkCmdBeginQuery vkCmdBeginQuery = nullptr;
    PFN_vkCmdEndQuery vkCmdEndQuery = nullptr;
    PFN_vkCmdResetQueryPool vkCmdResetQueryPool = nullptr;
    PFN_vkCmdWriteTimestamp vkCmdWriteTimestamp = nullptr;
    PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults = nullptr;
    PFN_vkCmdPushConstants vkCmdPushConstants = nullptr;
    PFN_vkCmdBeginRenderPass vkCmdBeginRenderPass = nullptr;
    PFN_vkCmdNextSubpass vkCmdNextSubpass = nullptr;
    PFN_vkCmdEndRenderPass vkCmdEndRenderPass = nullptr;
    PFN_vkCmdExecuteCommands vkCmdExecuteCommands = nullptr;
    PFN_vkBindBufferMemory2 vkBindBufferMemory2 = nullptr;
    PFN_vkBindImageMemory2 vkBindImageMemory2 = nullptr;
    PFN_vkGetDeviceGroupPeerMemoryFeatures vkGetDeviceGroupPeerMemoryFeatures = nullptr;
    PFN_vkCmdSetDeviceMask vkCmdSetDeviceMask = nullptr;
    PFN_vkCmdDispatchBase vkCmdDispatchBase = nullptr;
    PFN_vkGetBufferMemoryRequirements2 vkGetBufferMemoryRequirements2 = nullptr;
    PFN_vkGetImageMemoryRequirements2 vkGetImageMemoryRequirements2 = nullptr;
    PFN_vkGetImageSparseMemoryRequirements2 vkGetImageSparseMemoryRequirements2 = nullptr;
    PFN_vkTrimCommandPool vkTrimCommandPool = nullptr;
    PFN_vkGetDeviceQueue2 vkGetDeviceQueue2 = nullptr;
    PFN_vkCreateSamplerYcbcrConversion vkCreateSamplerYcbcrConversion = nullptr;
    PFN_vkDestroySamplerYcbcrConversion vkDestroySamplerYcbcrConversion = nullptr;
    PFN_vkCreateDescriptorUpdateTemplate vkCreateDescriptorUpdateTemplate = nullptr;
    PFN_vkDestroyDescriptorUpdateTemplate vkDestroyDescriptorUpdateTemplate = nullptr;
    PFN_vkUpdateDescriptorSetWithTemplate vkUpdateDescriptorSetWithTemplate = nullptr;
    PFN_vkGetDescriptorSetLayoutSupport vkGetDescriptorSetLayoutSupport = nullptr;
    PFN_vkCmdDrawIndirectCount vkCmdDrawIndirectCount = nullptr;
    PFN_vkCmdDrawIndexedIndirectCount vkCmdDrawIndexedIndirectCount = nullptr;
    PFN_vkCreateRenderPass2 vkCreateRenderPass2 = nullptr;
    PFN_vkCmdBeginRenderPass2 vkCmdBeginRenderPass2 = nullptr;
    PFN_vkCmdNextSubpass2 vkCmdNextSubpass2 = nullptr;
    PFN_vkCmdEndRenderPass2 vkCmdEndRenderPass2 = nullptr;
    PFN_vkResetQueryPool vkResetQueryPool = nullptr;
    PFN_vkGetSemaphoreCounterValue vkGetSemaphoreCounterValue = nullptr;
    PFN_vkWaitSemaphores vkWaitSemaphores = nullptr;
    PFN_vkSignalSemaphore vkSignalSemaphore = nullptr;
    PFN_vkGetBufferOpaqueCaptureAddress vkGetBufferOpaqueCaptureAddress = nullptr;
    PFN_vkGetBufferDeviceAddress vkGetBufferDeviceAddress = nullptr;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress = nullptr;
    PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR = nullptr;
    PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR = nullptr;
    PFN_vkGetSwapchainImagesKHR vkGetSwapchainImagesKHR = nullptr;
    PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR = nullptr;
    PFN_vkQueuePresentKHR vkQueuePresentKHR = nullptr;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR vkGetDeviceGroupPresentCapabilitiesKHR = nullptr;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR vkGetDeviceGroupSurfacePresentModesKHR = nullptr;
    PFN_vkAcquireNextImage2KHR vkAcquireNextImage2KHR = nullptr;
    PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR = nullptr;
    PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT = nullptr;
    PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT = nullptr;
    PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT = nullptr;
    PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT = nullptr;
    PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT = nullptr;
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCreateVideoSessionKHR vkCreateVideoSessionKHR = nullptr;
#else
    void* z_padding_vkCreateVideoSessionKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR = nullptr;
#else
    void* z_padding_vkDestroyVideoSessionKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCreateVideoSessionParametersKHR vkCreateVideoSessionParametersKHR = nullptr;
#else
    void* z_padding_vkCreateVideoSessionParametersKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkUpdateVideoSessionParametersKHR vkUpdateVideoSessionParametersKHR = nullptr;
#else
    void* z_padding_vkUpdateVideoSessionParametersKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR = nullptr;
#else
    void* z_padding_vkDestroyVideoSessionParametersKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkGetVideoSessionMemoryRequirementsKHR vkGetVideoSessionMemoryRequirementsKHR = nullptr;
#else
    void* z_padding_vkGetVideoSessionMemoryRequirementsKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkBindVideoSessionMemoryKHR vkBindVideoSessionMemoryKHR = nullptr;
#else
    void* z_padding_vkBindVideoSessionMemoryKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdBeginVideoCodingKHR vkCmdBeginVideoCodingKHR = nullptr;
#else
    void* z_padding_vkCmdBeginVideoCodingKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdControlVideoCodingKHR vkCmdControlVideoCodingKHR = nullptr;
#else
    void* z_padding_vkCmdControlVideoCodingKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdEndVideoCodingKHR vkCmdEndVideoCodingKHR = nullptr;
#else
    void* z_padding_vkCmdEndVideoCodingKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR = nullptr;
#else
    void* z_padding_vkCmdDecodeVideoKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
#if defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdEncodeVideoKHR vkCmdEncodeVideoKHR = nullptr;
#else
    void* z_padding_vkCmdEncodeVideoKHR = nullptr;
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
    PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT = nullptr;
    PFN_vkCmdBeginTransformFeedbackEXT vkCmdBeginTransformFeedbackEXT = nullptr;
    PFN_vkCmdEndTransformFeedbackEXT vkCmdEndTransformFeedbackEXT = nullptr;
    PFN_vkCmdBeginQueryIndexedEXT vkCmdBeginQueryIndexedEXT = nullptr;
    PFN_vkCmdEndQueryIndexedEXT vkCmdEndQueryIndexedEXT = nullptr;
    PFN_vkCmdDrawIndirectByteCountEXT vkCmdDrawIndirectByteCountEXT = nullptr;
    PFN_vkGetImageViewHandleNVX vkGetImageViewHandleNVX = nullptr;
    PFN_vkGetImageViewAddressNVX vkGetImageViewAddressNVX = nullptr;
    PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV = nullptr;
#else
    void* z_padding_vkGetMemoryWin32HandleNV = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryWin32HandleKHR vkGetMemoryWin32HandleKHR = nullptr;
#else
    void* z_padding_vkGetMemoryWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR = nullptr;
#else
    void* z_padding_vkGetMemoryWin32HandlePropertiesKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetMemoryFdKHR vkGetMemoryFdKHR = nullptr;
    PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetSemaphoreWin32HandleKHR vkGetSemaphoreWin32HandleKHR = nullptr;
#else
    void* z_padding_vkGetSemaphoreWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR = nullptr;
#else
    void* z_padding_vkImportSemaphoreWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetSemaphoreFdKHR vkGetSemaphoreFdKHR = nullptr;
    PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR = nullptr;
    PFN_vkCmdPushDescriptorSetKHR vkCmdPushDescriptorSetKHR = nullptr;
    PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR = nullptr;
    PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT = nullptr;
    PFN_vkCmdEndConditionalRenderingEXT vkCmdEndConditionalRenderingEXT = nullptr;
    PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV = nullptr;
    PFN_vkDisplayPowerControlEXT vkDisplayPowerControlEXT = nullptr;
    PFN_vkRegisterDeviceEventEXT vkRegisterDeviceEventEXT = nullptr;
    PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT = nullptr;
    PFN_vkGetSwapchainCounterEXT vkGetSwapchainCounterEXT = nullptr;
    PFN_vkGetRefreshCycleDurationGOOGLE vkGetRefreshCycleDurationGOOGLE = nullptr;
    PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE = nullptr;
    PFN_vkCmdSetDiscardRectangleEXT vkCmdSetDiscardRectangleEXT = nullptr;
    PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT = nullptr;
    PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetFenceWin32HandleKHR vkGetFenceWin32HandleKHR = nullptr;
#else
    void* z_padding_vkGetFenceWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR = nullptr;
#else
    void* z_padding_vkImportFenceWin32HandleKHR = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetFenceFdKHR vkGetFenceFdKHR = nullptr;
    PFN_vkImportFenceFdKHR vkImportFenceFdKHR = nullptr;
    PFN_vkAcquireProfilingLockKHR vkAcquireProfilingLockKHR = nullptr;
    PFN_vkReleaseProfilingLockKHR vkReleaseProfilingLockKHR = nullptr;
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT = nullptr;
    PFN_vkSetDebugUtilsObjectTagEXT vkSetDebugUtilsObjectTagEXT = nullptr;
    PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT = nullptr;
    PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT = nullptr;
    PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT = nullptr;
    PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT = nullptr;
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID = nullptr;
#else
    void* z_padding_vkGetAndroidHardwareBufferPropertiesANDROID = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkGetMemoryAndroidHardwareBufferANDROID vkGetMemoryAndroidHardwareBufferANDROID = nullptr;
#else
    void* z_padding_vkGetMemoryAndroidHardwareBufferANDROID = nullptr;
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
    PFN_vkCmdSetSampleLocationsEXT vkCmdSetSampleLocationsEXT = nullptr;
    PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR = nullptr;
    PFN_vkCmdCopyAccelerationStructureKHR vkCmdCopyAccelerationStructureKHR = nullptr;
    PFN_vkCopyAccelerationStructureKHR vkCopyAccelerationStructureKHR = nullptr;
    PFN_vkCmdCopyAccelerationStructureToMemoryKHR vkCmdCopyAccelerationStructureToMemoryKHR = nullptr;
    PFN_vkCopyAccelerationStructureToMemoryKHR vkCopyAccelerationStructureToMemoryKHR = nullptr;
    PFN_vkCmdCopyMemoryToAccelerationStructureKHR vkCmdCopyMemoryToAccelerationStructureKHR = nullptr;
    PFN_vkCopyMemoryToAccelerationStructureKHR vkCopyMemoryToAccelerationStructureKHR = nullptr;
    PFN_vkCmdWriteAccelerationStructuresPropertiesKHR vkCmdWriteAccelerationStructuresPropertiesKHR = nullptr;
    PFN_vkWriteAccelerationStructuresPropertiesKHR vkWriteAccelerationStructuresPropertiesKHR = nullptr;
    PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR = nullptr;
    PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR = nullptr;
    PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR = nullptr;
    PFN_vkCmdBuildAccelerationStructuresIndirectKHR vkCmdBuildAccelerationStructuresIndirectKHR = nullptr;
    PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR = nullptr;
    PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR = nullptr;
    PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR = nullptr;
    PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR = nullptr;
    PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR = nullptr;
    PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = nullptr;
    PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR = nullptr;
    PFN_vkCmdTraceRaysIndirectKHR vkCmdTraceRaysIndirectKHR = nullptr;
    PFN_vkGetRayTracingShaderGroupStackSizeKHR vkGetRayTracingShaderGroupStackSizeKHR = nullptr;
    PFN_vkCmdSetRayTracingPipelineStackSizeKHR vkCmdSetRayTracingPipelineStackSizeKHR = nullptr;
    PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT = nullptr;
    PFN_vkCreateValidationCacheEXT vkCreateValidationCacheEXT = nullptr;
    PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT = nullptr;
    PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT = nullptr;
    PFN_vkMergeValidationCachesEXT vkMergeValidationCachesEXT = nullptr;
    PFN_vkCmdBindShadingRateImageNV vkCmdBindShadingRateImageNV = nullptr;
    PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV = nullptr;
    PFN_vkCmdSetCoarseSampleOrderNV vkCmdSetCoarseSampleOrderNV = nullptr;
    PFN_vkCompileDeferredNV vkCompileDeferredNV = nullptr;
    PFN_vkCreateAccelerationStructureNV vkCreateAccelerationStructureNV = nullptr;
    PFN_vkDestroyAccelerationStructureNV vkDestroyAccelerationStructureNV = nullptr;
    PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV = nullptr;
    PFN_vkBindAccelerationStructureMemoryNV vkBindAccelerationStructureMemoryNV = nullptr;
    PFN_vkCmdCopyAccelerationStructureNV vkCmdCopyAccelerationStructureNV = nullptr;
    PFN_vkCmdWriteAccelerationStructuresPropertiesNV vkCmdWriteAccelerationStructuresPropertiesNV = nullptr;
    PFN_vkCmdBuildAccelerationStructureNV vkCmdBuildAccelerationStructureNV = nullptr;
    PFN_vkCmdTraceRaysNV vkCmdTraceRaysNV = nullptr;
    PFN_vkGetAccelerationStructureHandleNV vkGetAccelerationStructureHandleNV = nullptr;
    PFN_vkCreateRayTracingPipelinesNV vkCreateRayTracingPipelinesNV = nullptr;
    PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT = nullptr;
    PFN_vkCmdWriteBufferMarkerAMD vkCmdWriteBufferMarkerAMD = nullptr;
    PFN_vkGetCalibratedTimestampsEXT vkGetCalibratedTimestampsEXT = nullptr;
    PFN_vkCmdDrawMeshTasksNV vkCmdDrawMeshTasksNV = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectNV vkCmdDrawMeshTasksIndirectNV = nullptr;
    PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV = nullptr;
    PFN_vkCmdSetExclusiveScissorNV vkCmdSetExclusiveScissorNV = nullptr;
    PFN_vkCmdSetCheckpointNV vkCmdSetCheckpointNV = nullptr;
    PFN_vkGetQueueCheckpointDataNV vkGetQueueCheckpointDataNV = nullptr;
    PFN_vkInitializePerformanceApiINTEL vkInitializePerformanceApiINTEL = nullptr;
    PFN_vkUninitializePerformanceApiINTEL vkUninitializePerformanceApiINTEL = nullptr;
    PFN_vkCmdSetPerformanceMarkerINTEL vkCmdSetPerformanceMarkerINTEL = nullptr;
    PFN_vkCmdSetPerformanceStreamMarkerINTEL vkCmdSetPerformanceStreamMarkerINTEL = nullptr;
    PFN_vkCmdSetPerformanceOverrideINTEL vkCmdSetPerformanceOverrideINTEL = nullptr;
    PFN_vkAcquirePerformanceConfigurationINTEL vkAcquirePerformanceConfigurationINTEL = nullptr;
    PFN_vkReleasePerformanceConfigurationINTEL vkReleasePerformanceConfigurationINTEL = nullptr;
    PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL = nullptr;
    PFN_vkGetPerformanceParameterINTEL vkGetPerformanceParameterINTEL = nullptr;
    PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD = nullptr;
    PFN_vkCmdSetFragmentShadingRateKHR vkCmdSetFragmentShadingRateKHR = nullptr;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkAcquireFullScreenExclusiveModeEXT vkAcquireFullScreenExclusiveModeEXT = nullptr;
#else
    void* z_padding_vkAcquireFullScreenExclusiveModeEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkReleaseFullScreenExclusiveModeEXT vkReleaseFullScreenExclusiveModeEXT = nullptr;
#else
    void* z_padding_vkReleaseFullScreenExclusiveModeEXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetDeviceGroupSurfacePresentModes2EXT vkGetDeviceGroupSurfacePresentModes2EXT = nullptr;
#else
    void* z_padding_vkGetDeviceGroupSurfacePresentModes2EXT = nullptr;
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT = nullptr;
    PFN_vkCmdSetCullModeEXT vkCmdSetCullModeEXT = nullptr;
    PFN_vkCmdSetFrontFaceEXT vkCmdSetFrontFaceEXT = nullptr;
    PFN_vkCmdSetPrimitiveTopologyEXT vkCmdSetPrimitiveTopologyEXT = nullptr;
    PFN_vkCmdSetViewportWithCountEXT vkCmdSetViewportWithCountEXT = nullptr;
    PFN_vkCmdSetScissorWithCountEXT vkCmdSetScissorWithCountEXT = nullptr;
    PFN_vkCmdBindVertexBuffers2EXT vkCmdBindVertexBuffers2EXT = nullptr;
    PFN_vkCmdSetDepthTestEnableEXT vkCmdSetDepthTestEnableEXT = nullptr;
    PFN_vkCmdSetDepthWriteEnableEXT vkCmdSetDepthWriteEnableEXT = nullptr;
    PFN_vkCmdSetDepthCompareOpEXT vkCmdSetDepthCompareOpEXT = nullptr;
    PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT = nullptr;
    PFN_vkCmdSetStencilTestEnableEXT vkCmdSetStencilTestEnableEXT = nullptr;
    PFN_vkCmdSetStencilOpEXT vkCmdSetStencilOpEXT = nullptr;
    PFN_vkCreateDeferredOperationKHR vkCreateDeferredOperationKHR = nullptr;
    PFN_vkDestroyDeferredOperationKHR vkDestroyDeferredOperationKHR = nullptr;
    PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR = nullptr;
    PFN_vkGetDeferredOperationResultKHR vkGetDeferredOperationResultKHR = nullptr;
    PFN_vkDeferredOperationJoinKHR vkDeferredOperationJoinKHR = nullptr;
    PFN_vkGetPipelineExecutablePropertiesKHR vkGetPipelineExecutablePropertiesKHR = nullptr;
    PFN_vkGetPipelineExecutableStatisticsKHR vkGetPipelineExecutableStatisticsKHR = nullptr;
    PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR = nullptr;
    PFN_vkCmdExecuteGeneratedCommandsNV vkCmdExecuteGeneratedCommandsNV = nullptr;
    PFN_vkCmdPreprocessGeneratedCommandsNV vkCmdPreprocessGeneratedCommandsNV = nullptr;
    PFN_vkCmdBindPipelineShaderGroupNV vkCmdBindPipelineShaderGroupNV = nullptr;
    PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV = nullptr;
    PFN_vkCreateIndirectCommandsLayoutNV vkCreateIndirectCommandsLayoutNV = nullptr;
    PFN_vkDestroyIndirectCommandsLayoutNV vkDestroyIndirectCommandsLayoutNV = nullptr;
    PFN_vkCreatePrivateDataSlotEXT vkCreatePrivateDataSlotEXT = nullptr;
    PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT = nullptr;
    PFN_vkSetPrivateDataEXT vkSetPrivateDataEXT = nullptr;
    PFN_vkGetPrivateDataEXT vkGetPrivateDataEXT = nullptr;
    PFN_vkCmdSetEvent2KHR vkCmdSetEvent2KHR = nullptr;
    PFN_vkCmdResetEvent2KHR vkCmdResetEvent2KHR = nullptr;
    PFN_vkCmdWaitEvents2KHR vkCmdWaitEvents2KHR = nullptr;
    PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR = nullptr;
    PFN_vkQueueSubmit2KHR vkQueueSubmit2KHR = nullptr;
    PFN_vkCmdWriteTimestamp2KHR vkCmdWriteTimestamp2KHR = nullptr;
    PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD = nullptr;
    PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV = nullptr;
    PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV = nullptr;
    PFN_vkCmdCopyBuffer2KHR vkCmdCopyBuffer2KHR = nullptr;
    PFN_vkCmdCopyImage2KHR vkCmdCopyImage2KHR = nullptr;
    PFN_vkCmdBlitImage2KHR vkCmdBlitImage2KHR = nullptr;
    PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR = nullptr;
    PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR = nullptr;
    PFN_vkCmdResolveImage2KHR vkCmdResolveImage2KHR = nullptr;
    PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT = nullptr;
#if defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkGetMemoryZirconHandleFUCHSIA vkGetMemoryZirconHandleFUCHSIA = nullptr;
#else
    void* z_padding_vkGetMemoryZirconHandleFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA = nullptr;
#else
    void* z_padding_vkGetMemoryZirconHandlePropertiesFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkGetSemaphoreZirconHandleFUCHSIA vkGetSemaphoreZirconHandleFUCHSIA = nullptr;
#else
    void* z_padding_vkGetSemaphoreZirconHandleFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
#if defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA = nullptr;
#else
    void* z_padding_vkImportSemaphoreZirconHandleFUCHSIA = nullptr;
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
    PFN_vkCmdSetPatchControlPointsEXT vkCmdSetPatchControlPointsEXT = nullptr;
    PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT = nullptr;
    PFN_vkCmdSetDepthBiasEnableEXT vkCmdSetDepthBiasEnableEXT = nullptr;
    PFN_vkCmdSetLogicOpEXT vkCmdSetLogicOpEXT = nullptr;
    PFN_vkCmdSetPrimitiveRestartEnableEXT vkCmdSetPrimitiveRestartEnableEXT = nullptr;
    PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT = nullptr;
};

// This function finds the Vulkan-Loader (vulkan-1.dll, libvulkan.so, libvulkan.dylib, etc) on a system, loads it,
// and loads the follwing functions:
//  * vkGetInstanceProcAddr
//  * vkCreateInstance
//  * vkEnumerateInstanceExtensionProperties
//  * vkEnumerateInstanceLayerProperties
//  * vkEnumerateInstanceVersion
//
// Note:
// This function must be called before all other vulkan calls!
//
// Return Codes:
// VkResult::Success -- Successful initialization & loading of functions
// VkResult::ErrorInitializationFailed -- failure [unable to find Vulkan-Loader]
//
// Optional Parameter:
// PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr = VK_NULL_HANDLE
VkResult vkInitializeLoaderLibrary(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr = VK_NULL_HANDLE);

// Close the Vulkan-Loader and assigns VK_NULL_HANDLE to vkGetInstanceProcAddr
//
// Note:
// After this function is called, no further vulkan calls can be made, except for `vkInitializeLoaderLibrary()`
void vkCloseLoaderLibrary();

// Initialize the instance and physical device functions into the global function pointers
// (all functions which take a VkInstance or VkPhysicalDevice as the first parameter)
//
// Note: This must only be called after the application has created a valid VkInstance with vkCreateInstance
//
// Parameter:
// VkInstance instance
// The VkInstance handle which the application has created. Must not be VK_NULL_HANDLE
void vkInitializeInstanceFunctions(VkInstance instance);

// Loads device functions into the global function pointers
//
// Notes:
//  * This function must not be used for any application which creates multiple VkDevices.
//    Instead, the application should use a VkDeviceDispatchTable per device created.
//  * This must only be called after the application has created a valid VkDevice with vkCreateDevice
//
// Parameter:
// VkDevice device
// The VkDevice handle which the application has created. Must not be VK_NULL_HANDLE
void vkInitializeGlobalDeviceFunctions(VkDevice device);

// Loads device functions into the provided VkDeviceDispatchTable
//
// Notes:
//  *
//  * This must only be called after the application has created a valid VkDevice with vkCreateDevice
//
// Parameters:
//  * VkDevice device
// The VkDevice handle which the application has created. Must not be VK_NULL_HANDLE
//  * VkDeviceDispatchTable& table
// The table in which holds all loaded device function pointers.
void vkInitializeDeviceDispatchTable(VkDevice device, VkDeviceDispatchTable& table);

#ifdef __cplusplus
} // extern "C"
#endif

#if defined(VULKAN_CPP_IMPLEMENTATION)
#include "vulkan.cpp"
#endif //defined(VULKAN_CPP_IMPLEMENTATION)

#endif // VULKAN_H_
// clang-format on
