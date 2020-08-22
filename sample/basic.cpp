#include <vector>
#include <iostream>
#include "vkpp.h"

int main() {
    uint32_t count = 0;
    vk::EnumerateInstanceLayerProperties(&count, nullptr);
    std::vector<vk::LayerProperties> props(count);
    vk::EnumerateInstanceLayerProperties(&count, props.data());
    std::cout << "count " << count << "\n";
    for (auto &prop : props)
        std::cout << prop.layerName << "\n";
    return 0;
}