cmake_minimum_required (VERSION 2.8)
project (JSONTEST CXX C)

include_directories(../../include)
include_directories(../../thirdparty)
include_directories(../../thirdparty/jsoncpp/include)
include_directories(../../thirdparty/yajl/include)
include_directories(../../thirdparty/gtest/include)

link_directories(${JSONTEST_SOURCE_DIR})

option(gtest_disable_pthreads "Disable uses of pthreads in gtest." OFF)

# Define helper functions and macros used by Google Test.
include(cmake/internal_utils.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.

if(MSVC)
    add_definitions(-D_VARIADIC_MAX=10)
endif(MSVC)

add_executable(JSONTEST jsoncpptest.cpp perftest.cpp yajl_all.c yajltest.cpp rapidjsontest.cpp)

if(UNIX)
	target_link_libraries(JSONTEST libgtest.a ${CMAKE_THREAD_LIBS_INIT})
elseif (WIN32)
	target_link_libraries(JSONTEST gtest.lib)
endif()
