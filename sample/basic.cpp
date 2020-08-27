#include <iostream>
#include <vector>
#include "vkpp.h"

int main() {
    uint32_t count = 0;
    vk::EnumerateInstanceLayerProperties(&count, nullptr);
    std::vector<vk::LayerProperties> props(count);
    vk::EnumerateInstanceLayerProperties(&count, props.data());
    std::cout << "count " << count << "\n";
    for (auto &prop : props)
        std::cout << prop.layerName << "\n";

    vk::InstanceCreateInfo info;
    vk::Instance inst;
    auto res = vk::CreateInstance(&info, nullptr, &inst);
    if (res != vk::Result::eSuccess)
        return static_cast<int>(res);

    return 0;
}