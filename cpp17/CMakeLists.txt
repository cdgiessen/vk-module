add_library(vkm17_core INTERFACE)
target_include_directories(vkm17_core INTERFACE ${CMAKE_SOURCE_DIR}/cpp17)
target_link_libraries(vkm17_core INTERFACE Vulkan::Headers vk-module-compiler-warnings)
target_compile_features(vkm17_core INTERFACE cxx_std_17)

add_library(vkm17_functions INTERFACE)
target_link_libraries(vkm17_functions INTERFACE vkm17_core)
if (NOT WIN32)
    target_link_libraries(vkm17_functions INTERFACE ${CMAKE_DL_LIBS})
endif()

add_library(vkm17 INTERFACE)
target_link_libraries(vkm17 INTERFACE Vulkan::Headers vkm17_core vkm17_functions)
target_compile_features(vkm17 INTERFACE cxx_std_17)

add_library(vkm17_string vkm_string.cpp)
target_include_directories(vkm17_string PUBLIC ${CMAKE_SOURCE_DIR}/cpp17)
target_link_libraries(vkm17_string PUBLIC Vulkan::Headers vkm17)
target_compile_features(vkm17_string PUBLIC cxx_std_17)