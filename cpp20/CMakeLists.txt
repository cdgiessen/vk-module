add_library(vkm20_core INTERFACE)
target_include_directories(vkm20_core INTERFACE ${CMAKE_SOURCE_DIR}/cpp20)
target_link_libraries(vkm20_core INTERFACE Vulkan::Headers vk-module-compiler-warnings)
target_compile_features(vkm20_core INTERFACE cxx_std_20)

add_library(vkm20_functions INTERFACE)
target_link_libraries(vkm20_functions INTERFACE vkm20_core)
if (NOT WIN32)
    target_link_libraries(vkm20_functions INTERFACE ${CMAKE_DL_LIBS})
endif()

add_library(vkm20 INTERFACE)
target_link_libraries(vkm20 INTERFACE Vulkan::Headers vkm20_core vkm20_functions)
target_compile_features(vkm20 INTERFACE cxx_std_20)

add_library(vkm20_string vkm_string.cpp)
target_include_directories(vkm20_string PUBLIC ${CMAKE_SOURCE_DIR}/cpp20)
target_link_libraries(vkm20_string PUBLIC Vulkan::Headers vkm20)
target_compile_features(vkm20_string PUBLIC cxx_std_20)