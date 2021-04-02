cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(vulkan-module CXX)

option(VK_MODULE_GENERATE_SOURCE "Get dependencies necessary for generating the bindings" off)
option(VK_MODULE_SAMPLES "Build samples for the bindings, will download glfw" off)
option(VK_MODULE_TESTS "Build tests for the bindings, will download catch2" off)

if (VK_MODULE_TESTS)
option(SET_COMPILE_TIME_TRACE "enable clang's -ftime-trace " OFF)
endif(VK_MODULE_TESTS)

if (VK_MODULE_GENERATE_SOURCE)
    find_package(PythonInterp 3 QUIET)

    include(FetchContent)
    FetchContent_Declare(
        vulkan_headers
        GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers
        GIT_TAG        v1.2.162
    )
    FetchContent_GetProperties(vulkan-headers)
    if(NOT vulkan_headers_POPULATED)
        FetchContent_Populate(vulkan_headers)
        add_subdirectory(${vulkan_headers_SOURCE_DIR} ${vulkan_headers_BINARY_DIR})
        add_custom_target(copy-xml ALL
            COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/registry/vk.xml ${CMAKE_SOURCE_DIR}/registry/vk.xml)
        add_custom_target(run_python_generator
            COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/generate.py)
        add_custom_target(copy-vk-platform-simple-cpp ALL
            COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/include/vulkan/vk_platform.h ${CMAKE_SOURCE_DIR}/include/vulkan/vk_platform.h)
        add_custom_target(copy-vk-platform-cpp-20 ALL
            COMMAND ${CMAKE_COMMAND} -E copy ${vulkan_headers_SOURCE_DIR}/include/vulkan/vk_platform.h ${CMAKE_SOURCE_DIR}/cpp20/vk_platform.h)
    endif()

endif()

add_library(vk-module-compiler-warnings INTERFACE)

# Determine whether we're compiling with clang++
string(FIND "${CMAKE_CXX_COMPILER}" "clang++" VK_MODULE_COMPILER_CLANGPP)
if(VK_MODULE_COMPILER_CLANGPP GREATER -1)
    set(VK_MODULE_COMPILER_CLANGPP 1)
else()
    set(VK_MODULE_COMPILER_CLANGPP 0)
endif()

target_compile_options(vk-module-compiler-warnings
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
if (VK_MODULE_GENERATE_SOURCE)
add_custom_target(generate_source copy-xml copy-vk-platform-simple-cpp copy-vk-platform-cpp-20)
endif()

add_library(vk_module_20 STATIC ${CMAKE_SOURCE_DIR}/cpp20/vk_module.h ${VerifyCXX})
target_include_directories(vk_module_20 PUBLIC ${CMAKE_SOURCE_DIR}/cpp20)
target_link_libraries(vk_module_20 PUBLIC vk-module-compiler-warnings)
target_compile_features(vk_module_20 PUBLIC cxx_std_20)
set_target_properties(vk_module_20 PROPERTIES CXX_STANDARD 20)
set_target_properties(vk_module_20 PROPERTIES LINKER_LANGUAGE CXX)

if (NOT WIN32)
    target_link_libraries(vk_module_20 PUBLIC ${CMAKE_DL_LIBS})
endif()

add_library(vulkan-simple-cpp STATIC ${CMAKE_SOURCE_DIR}/include/vulkan/vulkan.h ${VerifyCXX})
target_include_directories(vulkan-simple-cpp PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(vulkan-simple-cpp PUBLIC vk-module-compiler-warnings)
target_compile_features(vulkan-simple-cpp PUBLIC cxx_std_11)
target_compile_options(vulkan-simple-cpp PRIVATE VULKAN_SIMPLE_CPP_IMPLEMENTATION)
set_target_properties(vulkan-simple-cpp PROPERTIES CXX_STANDARD 11)
set_target_properties(vulkan-simple-cpp PROPERTIES LINKER_LANGUAGE CXX)

if (NOT WIN32)
    target_link_libraries(vk_module_20 PUBLIC ${CMAKE_DL_LIBS})
endif()

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vk_module_20 PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)

if (VK_MODULE_SAMPLES)
    add_subdirectory(sample)
endif(VK_MODULE_SAMPLES)

if (VK_MODULE_TESTS)
    add_subdirectory(tests)
endif (VK_MODULE_TESTS)

