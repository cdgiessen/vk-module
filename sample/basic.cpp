#include <iostream>
#include <vector>
#include "vkm.h"
#include "vkm_string.h"

int
main()
{
    vk::DynamicLibrary library;
    vk::Result res = library.init();
    if (res != vk::Result::Success)
        return -1;
    vk::GlobalFunctions free_funcs(library);

    uint32_t count = 0;
    res = free_funcs.EnumerateInstanceLayerProperties(count, nullptr);
    std::vector<vk::LayerProperties> props(count);
    res = free_funcs.EnumerateInstanceLayerProperties(count, props.data());
    std::cout << "count " << count << "\n";
    for (auto& prop : props)
        std::cout << prop.layerName << "\n";

    vk::Instance inst = free_funcs.CreateInstance({}).value();
    if (res != vk::Result::Success) {
        std::cout << "failed to create instance\n";
        return static_cast<int>(res);
    }

    if (inst && !(!inst))
        std::cout << "should print this\n";
    else
        std::cout << "shouldn't print this\n";

    vk::InstanceFunctions inst_funcs(free_funcs, inst);
    res = inst_funcs.EnumeratePhysicalDevices(count, nullptr);

    std::vector<vk::PhysicalDevice> phys_devices(count);
    res = inst_funcs.EnumeratePhysicalDevices(count, phys_devices.data());

    if (count == 0) {
        std::cout << "failed to get phys devices\n";
        return -100;
    }

    vk::PhysicalDevice phys_dev = phys_devices.at(0);
    vk::PhysicalDeviceFunctions phys_dev_funcs(inst_funcs, phys_dev);

    vk::ImageCreateFlags img_flags = vk::ImageCreateFlagBits::SparseBinding;
    auto img_props_res = phys_dev_funcs.GetImageFormatProperties(
      vk::Format::Undefined, vk::ImageType::e1D, vk::ImageTiling::Optimal, vk::ImageUsageFlagBits::TransferDst, img_flags);
    if (!img_props_res)
        return -1;
    vk::ImageFormatProperties image_props = img_props_res.value();
    vk::SwapchainCreateInfoKHR swap_info;
    swap_info.preTransform = vk::SurfaceTransformFlagBitsKHR::IdentityBitKHR;
    /*
     Should not compile.
     vk::SurfaceTransformFlagsKHR transform_flags;
     swap_info.preTransform = transform_flags;
    */

    float priority;
    vk::DeviceQueueCreateInfo queue_info;
    queue_info.queueCount = 1;
    queue_info.pQueuePriorities = &priority;
    vk::DeviceCreateInfo dev_create_info;
    dev_create_info.queueCreateInfoCount = 1;
    dev_create_info.pQueueCreateInfos = &queue_info;
    auto dev_res = inst_funcs.CreateDevice(phys_dev, dev_create_info);
    if (!dev_res)
        return -1;
    vk::Device device = dev_res.value();
    vk::DeviceFunctions device_functions(inst_funcs, device);

    uint32_t queue_indices = 0;
    vk::BufferCreateInfo buffer_info{ .size = 100,
                                      .usage = vk::BufferUsageFlagBits::IndexBuffer,
                                      .sharingMode = vk::SharingMode::Exclusive,
                                      .queueFamilyIndexCount = 1,
                                      .pQueueFamilyIndices = &queue_indices };
    auto buf_res = device_functions.CreateBuffer(buffer_info, nullptr);
    if (!buf_res)
        return -1;
    vk::Buffer buffer = buf_res.value();

    return 0;
}