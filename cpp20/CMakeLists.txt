add_library(vk_module_20 STATIC vk_module.h ${VerifyCXX})
target_include_directories(vk_module_20 PUBLIC ${CMAKE_SOURCE_DIR}/cpp20)
target_link_libraries(vk_module_20 PUBLIC vk-module-compiler-warnings)
target_compile_features(vk_module_20 PUBLIC cxx_std_20)
set_target_properties(vk_module_20 PROPERTIES CXX_STANDARD 20)
set_target_properties(vk_module_20 PROPERTIES LINKER_LANGUAGE CXX)

if (NOT WIN32)
    target_link_libraries(vk_module_20 PUBLIC ${CMAKE_DL_LIBS})
endif()

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vk_module_20 PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)