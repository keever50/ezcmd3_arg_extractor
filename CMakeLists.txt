cmake_minimum_required(VERSION 3.10)
project(EZCMD3Test C)

# option(EZCMD3_TEST "Build EZCMD3 test program" ON)

if(EZCMD3_TEST)
    add_executable(ezcmd3_test test.c ezcmd3.c)
    target_compile_definitions(ezcmd3_test PRIVATE EZCMD3_TEST)
    target_include_directories(ezcmd3_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()
