#include <iostream>
#include <vector>
#include <vulkan/vulkan.hpp>
int main() {
    uint32_t count = 0;
    vk::Instance instance;
    auto props = vk::enumerateInstanceLayerProperties();

    std::cout << "count " << count << "\n";
    for (auto &prop : props)
        std::cout << prop.layerName << "\n";

    vk::InstanceCreateInfo info;
    vk::Instance inst;
    auto res = vk::createInstance(&info, nullptr, &inst);
    if (res != vk::Result::eSuccess) {
        std::cout << "failed to create instance\n";
        return static_cast<int>(res);
    }
    vk::DispatchLoaderDynamic dldi(vkGetInstanceProcAddr);

    if (inst && !(!inst))
        std::cout << "should print this\n";
    else
        std::cout << "shouldn't print this\n";

    auto phys_devices = inst.enumeratePhysicalDevices(dldi);
    if (phys_devices.size() == 0) {
        std::cout << "failed to get phys devs\n";
        return -100;
    }
    vk::PhysicalDevice phys_dev = phys_devices.at(0);
    vk::ImageFormatProperties image_props;
    vk::BufferCreateFlags flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding | vk::BufferCreateFlagBits::eSparseResidency;
    std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 3
    flags = flags & vk::BufferCreateFlagBits::eSparseResidency;
    std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 2
    flags |= vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 3
    flags &= vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 1
    flags = ~vk::BufferCreateFlagBits::eSparseBinding;
    std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 4294967294
    // flags = vk::BufferCreateFlagBits::eSparseBinding ^ vk::BufferCreateFlagBits::eSparseResidency;
    // std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 3
    // flags ^= vk::BufferCreateFlagBits::eSparseAliased;
    // std::cout << static_cast<uint32_t>(flags) << " " << vk::to_string(flags) << "\n"; // 7

    flags = flags | vk::BufferCreateFlagBits::eSparseBinding;
    flags = flags & vk::BufferCreateFlagBits::eSparseBinding;
    flags = vk::BufferCreateFlagBits::eSparseBinding | flags;
    flags |= flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding & flags;
    flags &= flags;
    flags = ~flags;
    flags = vk::BufferCreateFlagBits::eSparseBinding ^ flags;
    // flags = flags ^ vk::BufferCreateFlagBits::eSparseBinding;
    // flags ^= flags;

    vk::ImageCreateFlags img_flags = vk::ImageCreateFlagBits::eSparseBinding;

    phys_dev.getImageFormatProperties(vk::Format::eUndefined, vk::ImageType::e1D, vk::ImageTiling::eOptimal,
                                      vk::ImageUsageFlagBits::eTransferDst, img_flags, &image_props, dldi);
    vk::SwapchainCreateInfoKHR swap_info;
    swap_info.preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
    /*
     Should not compile.
     vk::SurfaceTransformFlagsKHR transform_flags;
     swap_info.preTransform = transform_flags;
    */

    return 0;
}