cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(vulkan-module CXX)

find_package(PythonInterp 3 QUIET)

include(FetchContent)
FetchContent_Declare(
    vulkan_headers
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers
    GIT_TAG        v1.2.151
)
FetchContent_GetProperties(vulkan-headers)
if(NOT vulkan_headers_POPULATED)
    FetchContent_Populate(vulkan_headers)
    add_subdirectory(${vulkan_headers_SOURCE_DIR} ${vulkan_headers_BINARY_DIR})
    add_custom_target(copy-xml ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/registry/vk.xml ${CMAKE_SOURCE_DIR}/registry/vk.xml)
    add_custom_target(run_python_generator
        COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/generate.py)
    
endif()

add_custom_target(generate_source copy-xml)

add_library(vkpp_core INTERFACE)
target_include_directories(vkpp_core INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vkpp_core INTERFACE Vulkan::Headers)
target_compile_features(vkpp_core INTERFACE cxx_std_20)

add_library(vkpp_functions INTERFACE)
target_link_libraries(vkpp_functions INTERFACE vkpp_core)

add_library(vkpp INTERFACE)
target_link_libraries(vkpp INTERFACE Vulkan::Headers vkpp_core vkpp_functions)
target_compile_features(vkpp INTERFACE cxx_std_20)

add_library(vkpp_string include/vkpp_string.cpp)
target_include_directories(vkpp_string PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vkpp_string PUBLIC Vulkan::Headers vkpp)
target_compile_features(vkpp_string PUBLIC cxx_std_20)

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vkpp_string PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)

add_subdirectory(sample)

if (VK_MODULE_TESTS)
add_subdirectory(tests)
endif (VK_MODULE_TESTS)
