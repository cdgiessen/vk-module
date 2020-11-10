add_library(vkm20_core INTERFACE)
target_include_directories(vkm20_core INTERFACE ${CMAKE_SOURCE_DIR}/cpp20)
target_link_libraries(vkm20_core INTERFACE vk-module-compiler-warnings)
target_compile_features(vkm20_core INTERFACE cxx_std_20)

add_library(vkm20_function STATIC vkm_function.cpp)
target_link_libraries(vkm20_function PUBLIC vkm20_core)
if (NOT WIN32)
    target_link_libraries(vkm20_function PUBLIC ${CMAKE_DL_LIBS})
endif()
target_compile_features(vkm20_function PUBLIC cxx_std_20)

add_library(vkm20_string STATIC vkm_string.cpp)
target_link_libraries(vkm20_string PUBLIC vkm20_core)
target_compile_features(vkm20_string PUBLIC cxx_std_20)

add_library(vkm20 INTERFACE)
target_link_libraries(vkm20 INTERFACE vkm20_core vkm20_function vkm20_string)
target_compile_features(vkm20 INTERFACE cxx_std_20)

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vkm20_function PUBLIC -ftime-trace)
target_compile_options(vkm20_string PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)