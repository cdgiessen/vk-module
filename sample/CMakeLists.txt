
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
target_link_libraries(basic_sample_usage vk_module_20)

add_executable(vk-module-triangle-header triangle.cpp)
target_link_libraries(vk-module-triangle-header
    PRIVATE
    Vulkan::Headers
    glfw
    vk_module_20
    vk-module-compiler-warnings )


target_compile_options(vk-module-triangle-header PUBLIC -fsanitize=address)
target_link_options(vk-module-triangle-header PUBLIC -fsanitize=address)

add_custom_target(copy-shader-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sample/shaders ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS vk-module-triangle-header)

if (SET_COMPILE_TIME_TRACE)
target_compile_options(basic_sample_usage PUBLIC -ftime-trace)
target_compile_options(vk-module-triangle-header PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)