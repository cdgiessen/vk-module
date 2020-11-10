// clang-format off
#include "vkm_string.h"
namespace vk {
#if defined(WIN32)
#pragma warning( disable : 4065 )
#endif //defined(WIN32)
const char * to_string(Result val) {
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
        case(Result::ErrorIncompatibleVersionKHR): return "ErrorIncompatibleVersionKHR";
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
#endif // defined(VK_ENABLE_BETA_EXTENSIONS)
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
#endif // defined(VK_USE_PLATFORM_ANDROID_KHR)
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
#endif // defined(VK_USE_PLATFORM_VI_NN)
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
#endif // defined(VK_USE_PLATFORM_WAYLAND_KHR)
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
#endif // defined(VK_USE_PLATFORM_WIN32_KHR)
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
#endif // defined(VK_USE_PLATFORM_XLIB_KHR)
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
#endif // defined(VK_USE_PLATFORM_XCB_KHR)
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
#endif // defined(VK_USE_PLATFORM_DIRECTFB_EXT)
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
#endif // defined(VK_USE_PLATFORM_IOS_MVK)
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
#endif // defined(VK_USE_PLATFORM_MACOS_MVK)
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
#endif // defined(VK_USE_PLATFORM_METAL_EXT)
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
#endif // defined(VK_USE_PLATFORM_FUCHSIA)
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
#endif // defined(VK_USE_PLATFORM_GGP)
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
