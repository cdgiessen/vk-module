#include <iostream>
#include <vector>
#include "vkpp.h"

int main() {
    vk::FreeFunctions free_funcs(vkGetInstanceProcAddr);

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
    if (res != vk::Result::eSuccess)
        return static_cast<int>(res);

    vk::InstanceFunctions inst_funcs(vkGetInstanceProcAddr, inst);

    inst_funcs.EnumeratePhysicalDevices(inst, &count, nullptr);
    std::vector<vk::PhysicalDevice> phys_devs(count);
    inst_funcs.EnumeratePhysicalDevices(inst, &count, phys_devs.data());

    if (count == 0)
        return -100;

    vk::PhysicalDevice phys_dev = phys_devs.at(0);
    vk::ImageFormatProperties image_props;
    auto flag_bits = vk::ImageUsageFlagBits::eTransferDst;
    // vk::GetPhysicalDeviceImageFormatProperties(phys_dev, vk::Format::eUndefined, vk::ImageType::e1D, vk::ImageTiling::eOptimal,
    //                                           flag_bits, vk::ImageCreateFlagBits::eSparseBinding, &image_props);

    return 0;
}