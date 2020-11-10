add_library(vkm17_core INTERFACE)
target_include_directories(vkm17_core INTERFACE ${CMAKE_SOURCE_DIR}/cpp17)
target_link_libraries(vkm17_core INTERFACE vk-module-compiler-warnings)
target_compile_features(vkm17_core INTERFACE cxx_std_17)

add_library(vkm17_function STATIC vkm_function.cpp)
target_link_libraries(vkm17_function PUBLIC vkm17_core)
if (NOT WIN32)
    target_link_libraries(vkm17_function PUBLIC ${CMAKE_DL_LIBS})
endif()
target_compile_features(vkm17_function PUBLIC cxx_std_17)

add_library(vkm17_string STATIC vkm_string.cpp)
target_link_libraries(vkm17_string PUBLIC vkm17_core)
target_compile_features(vkm17_string PUBLIC cxx_std_17)

add_library(vkm17 INTERFACE)
target_link_libraries(vkm17 INTERFACE vkm17_core vkm17_function vkm17_string)
target_compile_features(vkm17 INTERFACE cxx_std_17)

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vkm17_function PUBLIC -ftime-trace)
target_compile_options(vkm17_string PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)