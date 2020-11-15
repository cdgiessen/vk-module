
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
FetchContent_MakeAvailable(glfw_repo)

find_package(Vulkan REQUIRED)

add_executable(basic_sample_usage basic.cpp)
target_link_libraries(basic_sample_usage vkm20)
set_target_properties(basic_sample_usage PROPERTIES CXX_STANDARD 20)

# add_executable(test_vkhpp_compilation test_vkhpp.cpp)
# target_link_libraries(test_vkhpp_compilation Vulkan::Vulkan)
# set_target_properties(test_vkhpp_compilation PROPERTIES CXX_STANDARD 17)


add_executable(vk-module-triangle-header triangle.cpp)
target_link_libraries(vk-module-triangle-header
    PRIVATE
    Vulkan::Headers
    glfw
    vkm20_function
    vk-module-compiler-warnings )

add_custom_target(copy-shader-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sample/shaders ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS vk-module-triangle-header)

if (SET_COMPILE_TIME_TRACE)
target_compile_options(basic_sample_usage PUBLIC -ftime-trace)
target_compile_options(vk-module-triangle-header PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)