cmake_minimum_required (VERSION 2.8)
project (HelloWorld)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

configure_file(include/log4cplus/config.h.cmake.in
  ${HelloWorld_BINARY_DIR}/include/log4cplus/config.h @ONLY)
configure_file(include/log4cplus/config/defines.hxx.cmake.in
  ${HelloWorld_BINARY_DIR}/include/log4cplus/config/defines.hxx @ONLY)

include_directories (${HelloWorld_SOURCE_DIR}/include
		      ${HelloWorld_BINARY_DIR}/include
		      )
link_directories(${HelloWorld_SOURCE_DIR})

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

#log4cplus
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/log4cplus")

add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld log4cplus)
