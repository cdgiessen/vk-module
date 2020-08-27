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

add_library(vkpp INTERFACE)
target_include_directories(vkpp INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vkpp INTERFACE Vulkan-Headers)

add_subdirectory(sample)
