
find_package(Vulkan REQUIRED)

add_executable(basic_sample_usage basic.cpp)
target_link_libraries(basic_sample_usage vkpp vulkan)
set_target_properties(basic_sample_usage PROPERTIES CXX_STANDARD 20)
