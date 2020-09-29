
include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(catch2)

add_executable(static_tests static_test.cpp)
target_link_libraries(static_tests vkpp)

find_package(Vulkan REQUIRED)

add_executable(vk-module-test main.cpp flags_test.cpp functions_test.cpp)
target_link_libraries(vk-module-test vkpp Vulkan::Vulkan Catch2)

