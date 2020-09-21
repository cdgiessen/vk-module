#include <iostream>
#include <vector>
#include "vkpp.h"
#include "vkpp_string.h"

int main() {
    vk::GlobalFunctions free_funcs(vkGetInstanceProcAddr);

    uint32_t count = 0;
    free_funcs.EnumerateInstanceLayerProperties(&count, nullptr);
    std::vector<vk::LayerProperties> props(count);
    free_funcs.EnumerateInstanceLayerProperties(&count, props.data());
    std::cout << "count " << count << "\n";
    for (auto &prop : props)
        std::cout << prop.layerName << "\n";

    vk::InstanceCreateInfo info;
    vk::Instance inst;
    auto res = free_funcs.CreateInstance(&info, nullptr, &inst);
    if (res != vk::Result::eSuccess) {
        std::cout << "failed to create instance\n";
        return static_cast<int>(res);
    }

    if (inst && !(!inst))
        std::cout << "should print this\n";
    else
        std::cout << "shouldn't print this\n";

    vk::InstanceFunctions inst_funcs(vkGetInstanceProcAddr, inst);
    inst_funcs.EnumeratePhysicalDevices(&count, nullptr);

    std::vector<vk::PhysicalDevice> phys_devices(count);
    inst_funcs.EnumeratePhysicalDevices(&count, phys_devices.data());

    if (count == 0) {
        std::cout << "failed to get phys devs\n";
        return -100;
    }

    vk::PhysicalDevice phys_dev = phys_devices.at(0);
    vk::ImageFormatProperties image_props;
    vk::BufferCreateFlags flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding | vk::BufferCreateFlagBits::eSparseResidency;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 3
    flags = flags & vk::BufferCreateFlagBits::eSparseResidency;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 2
    flags = vk::BufferCreateFlagBits::eSparseBinding ^ vk::BufferCreateFlagBits::eSparseResidency;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 3
    flags = ~vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 1
    flags |= vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 4294967294
    flags &= vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 3
    flags ^= vk::BufferCreateFlagBits::eSparseAliased;
    std::cout << flags.flags << " " << vk::to_string(flags) << "\n"; // 7

    flags = flags | vk::BufferCreateFlagBits::eSparseBinding;
    flags = flags & vk::BufferCreateFlagBits::eSparseBinding;
    flags = vk::BufferCreateFlagBits::eSparseBinding | flags;
    flags |= flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding & flags;
    flags &= flags;
    flags = ~flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding ^ flags;
    flags = flags ^ vk::BufferCreateFlagBits::eSparseBinding;
    flags ^= flags;

    vk::ImageCreateFlags img_flags = vk::ImageCreateFlagBits::eSparseBinding;
    vk::PhysicalDeviceDispatchTable phys_dev_funcs(phys_dev, inst_funcs);

    phys_dev_funcs.GetImageFormatProperties(vk::Format::eUndefined, vk::ImageType::e1D, vk::ImageTiling::eOptimal,
                                            vk::ImageUsageFlagBits::eTransferDst, img_flags, &image_props);
    vk::SwapchainCreateInfoKHR swap_info;
    swap_info.preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentityBitKHR;
    /*
     Should not compile.
     vk::SurfaceTransformFlagsKHR transform_flags;
     swap_info.preTransform = transform_flags;
    */

    return 0;
}