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

option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)

include(FetchContent)
FetchContent_Declare(
    glfw_repo
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.3.2
)
FetchContent_Declare(
    vma_repo
    GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
    GIT_TAG        59ec0809a7176ce6b9fa3d6341b477102ac3d3aa
)
FetchContent_Declare(
    vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        511cac8db4f9d9d5eda95a6e16af74e0731f5f32
)
FetchContent_MakeAvailable(glfw_repo vk_bootstrap)

FetchContent_GetProperties(vma_repo)
if(NOT vma_repoPOPULATED)
    FetchContent_Populate(vma_repo)
    add_library(VulkanMemoryAllocator INTERFACE)
    target_include_directories(VulkanMemoryAllocator INTERFACE ${vma_repo_SOURCE_DIR}/include)
endif()

find_package(Vulkan REQUIRED)

add_executable(basic_sample_usage basic.cpp)
target_link_libraries(basic_sample_usage vk-module-cpp)

add_executable(vk-module-triangle-header triangle.cpp)
target_link_libraries(vk-module-triangle-header
    PRIVATE
    vk-module-compiler-options
    vk-module-cpp
    glfw
    )

add_executable(vk-simple-triangle simple_triangle.cpp)
target_link_libraries(vk-simple-triangle
    PRIVATE
    vulkan-simple-cpp
    glfw
    VulkanMemoryAllocator
    vk-module-compiler-options)

add_custom_target(copy-shader-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sample/shaders ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS vk-module-triangle-header vk-simple-triangle)

if (SET_COMPILE_TIME_TRACE)
    target_compile_options(basic_sample_usage PUBLIC -ftime-trace)
    target_compile_options(vk-module-triangle-header PUBLIC -ftime-trace)
    target_compile_options(vk-simple-triangle PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)