# Copyright 2021 Charles Giessen (cdgiessen@gmail.com)

# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
# FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(vulkan-module CXX)

option(VK_MODULE_GENERATE_SOURCE "Get dependencies necessary for generating the bindings" off)
option(VK_MODULE_SAMPLES "Build samples for the bindings, will download glfw" off)
option(VK_MODULE_TESTS "Build tests for the bindings, will download catch2" off)
option(VK_MODULE_ENABLE_ADDRESS_SANITIZER "Enable Address Sanitizer. Mainly for developers only" off)

if (VK_MODULE_TESTS)
option(SET_COMPILE_TIME_TRACE "enable clang's -ftime-trace " OFF)
endif(VK_MODULE_TESTS)

if (VK_MODULE_GENERATE_SOURCE OR VK_MODULE_SAMPLES OR VK_MODULE_TESTS)
    find_package(PythonInterp 3 QUIET)

    include(FetchContent)
    FetchContent_Declare(
        vulkan_headers
        GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers
        GIT_TAG        v1.2.186
    )
    FetchContent_GetProperties(vulkan-headers)
    if(NOT vulkan_headers_POPULATED)
        FetchContent_Populate(vulkan_headers)
        add_subdirectory(${vulkan_headers_SOURCE_DIR} ${vulkan_headers_BINARY_DIR})
    endif()
    add_custom_target(copy_source ALL
        COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/registry/vk.xml ${CMAKE_CURRENT_LIST_DIR}/registry/vk.xml
        COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/include/vulkan/vk_platform.h ${CMAKE_CURRENT_LIST_DIR}/include/vulkan/vk_platform.h
        COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/include/vulkan/vk_platform.h ${CMAKE_CURRENT_LIST_DIR}/module/vk_platform.h)
    add_custom_target(generate_source
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/generate.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    add_dependencies(generate_source copy_source)

endif()


# Determine whether we're compiling with clang++
string(FIND "${CMAKE_CXX_COMPILER}" "clang++" VK_MODULE_COMPILER_CLANGPP)
if(VK_MODULE_COMPILER_CLANGPP GREATER -1)
set(VK_MODULE_COMPILER_CLANGPP 1)
else()
set(VK_MODULE_COMPILER_CLANGPP 0)
endif()

add_library(vk-module-compiler-options INTERFACE)
target_compile_options(vk-module-compiler-options
    INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>,${VK_MODULE_COMPILER_CLANGPP}>:
    -Wall
    -Wextra
    -pedantic-errors
    -Wconversion
    -Wsign-conversion>
    $<$<CXX_COMPILER_ID:MSVC>:
    /WX
    /W4>
    )

if (VK_MODULE_ENABLE_ADDRESS_SANITIZER)
    if (UNIX and not APPLE)
        target_compile_options(vk-module-compiler-options INTERFACE -fsanitize=address)
        target_link_options(vk-module-compiler-options INTERFACE -fsanitize=address)
    elseif(WIN32)
        target_compile_options(vk-module-compiler-options INTERFACE /fsanitize=address)
        target_link_options(vk-module-compiler-options INTERFACE /fsanitize=address)
    endif()
endif()

add_library(vk-platform-defines INTERFACE)
target_compile_options(vk-platform-defines INTERFACE
    $<$<PLATFORM_ID:WIN32>:-DVK_USE_PLATFORM_WIN32_KHR>
    $<$<PLATFORM_ID:ANDROID>:-DVK_USE_PLATFORM_ANDROID_KHR>
    $<$<PLATFORM_ID:APPLE>:-DVK_USE_PLATFORM_MACOS_MVK>
    $<$<AND:$<PLATFORM_ID:UNIX>,$<NOT:$<PLATFORM_ID:APPLE>>>:
        $<$<BUILD_WSI_XCB_SUPPORT>:-DVK_USE_PLATFORM_XCB_KHR>
        $<$<BUILD_WSI_XLIB_SUPPORT>:-DVK_USE_PLATFORM_XLIB_KHR>
        $<$<BUILD_WSI_WAYLAND_SUPPORT>:-DVK_USE_PLATFORM_WAYLAND_KHR>>
    )

add_library(vk-module-cpp INTERFACE)
target_include_directories(vk-module-cpp INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/module)
target_link_libraries(vk-module-cpp INTERFACE vk-module-compiler-options)
target_compile_features(vk-module-cpp INTERFACE cxx_std_20)

if (NOT WIN32)
    target_link_libraries(vk-module-cpp INTERFACE ${CMAKE_DL_LIBS})
endif()

add_library(vulkan-simple-cpp STATIC
    ${CMAKE_CURRENT_LIST_DIR}/include/vulkan/vulkan.h
    ${CMAKE_CURRENT_LIST_DIR}/include/vulkan/vulkan.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/vulkan/vulkan_string.h
    ${CMAKE_CURRENT_LIST_DIR}/include/vulkan/vulkan_string.cpp)
target_include_directories(vulkan-simple-cpp BEFORE PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(vulkan-simple-cpp PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/vulkan)
target_link_libraries(vulkan-simple-cpp PUBLIC vk-module-compiler-options)
target_compile_features(vulkan-simple-cpp PUBLIC cxx_std_11)
set_target_properties(vulkan-simple-cpp PROPERTIES CXX_STANDARD 11)
set_target_properties(vulkan-simple-cpp PROPERTIES LINKER_LANGUAGE CXX)

if (NOT WIN32)
    target_link_libraries(vulkan-simple-cpp PUBLIC ${CMAKE_DL_LIBS})
endif()

if (SET_COMPILE_TIME_TRACE)
    target_compile_options(vk-module-cpp INTERFACE -ftime-trace)
    target_compile_options(vulkan-simple-cpp PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)

if (VK_MODULE_SAMPLES)
    add_subdirectory(sample)
endif(VK_MODULE_SAMPLES)

if (VK_MODULE_TESTS)
    add_subdirectory(test)
endif (VK_MODULE_TESTS)


if (VK_MODULE_GENERATE_SOURCE OR VK_MODULE_SAMPLES OR VK_MODULE_TESTS)
    add_dependencies(vulkan-simple-cpp generate_source)
    add_dependencies(vk-module-cpp generate_source)
endif()