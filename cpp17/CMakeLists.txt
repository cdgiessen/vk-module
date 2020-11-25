add_library(vk_module_17 STATIC vk_module.h ${VerifyCXX})
target_include_directories(vk_module_17 PUBLIC ${CMAKE_SOURCE_DIR}/cpp17)
target_link_libraries(vk_module_17 PUBLIC vk-module-compiler-warnings)
target_compile_features(vk_module_17 PUBLIC cxx_std_17)
set_target_properties(vk_module_17 PROPERTIES CXX_STANDARD 17)
set_target_properties(vk_module_17 PROPERTIES LINKER_LANGUAGE CXX)

if (NOT WIN32)
    target_link_libraries(vk_module_17 PUBLIC ${CMAKE_DL_LIBS})
endif()

if (SET_COMPILE_TIME_TRACE)
target_compile_options(vk_module_17 PUBLIC -ftime-trace)
endif(SET_COMPILE_TIME_TRACE)