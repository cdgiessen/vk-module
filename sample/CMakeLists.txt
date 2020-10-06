
find_package(Vulkan REQUIRED)

add_executable(basic_sample_usage basic.cpp)
target_link_libraries(basic_sample_usage Vulkan::Headers vkm20 vkm20_string Vulkan::Vulkan)
set_target_properties(basic_sample_usage PROPERTIES CXX_STANDARD 20)

add_executable(test_vkhpp_compilation test_vkhpp.cpp)
target_link_libraries(test_vkhpp_compilation Vulkan::Headers Vulkan::Vulkan)
set_target_properties(test_vkhpp_compilation PROPERTIES CXX_STANDARD 17)

option(SET_COMPILE_TIME_TRACE "enable clang's -ftime-trace " OFF)
if (SET_COMPILE_TIME_TRACE)
target_compile_options(basic_sample_usage PUBLIC -ftime-trace)
target_compile_options(test_vkhpp_compilation PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)