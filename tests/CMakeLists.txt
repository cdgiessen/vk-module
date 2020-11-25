
include(FetchContent)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG        v2.13.1
)
FetchContent_MakeAvailable(catch2)

add_executable(static_tests_17 static_test.cpp)
target_link_libraries(static_tests_17 vk_module_17 Vulkan::Headers)

add_executable(static_tests_20 static_test.cpp)
target_link_libraries(static_tests_20 vk_module_20 Vulkan::Headers)

find_package(Vulkan REQUIRED)

add_executable(vk-module-test_17 main.cpp flags_test.cpp functions_test.cpp)
target_link_libraries(vk-module-test_17 vk_module_17 Vulkan::Vulkan Catch2)

add_executable(vk-module-test_20 main.cpp flags_test.cpp functions_test.cpp)
target_link_libraries(vk-module-test_20 vk_module_20 Vulkan::Vulkan Catch2)
