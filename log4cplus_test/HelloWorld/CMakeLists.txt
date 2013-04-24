cmake_minimum_required (VERSION 2.8)
project (HelloWorld)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")


link_directories(${HelloWorld_SOURCE_DIR})

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/log4cplus/include/log4cplus/config.h.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/log4cplus/config.h @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/log4cplus/include/log4cplus/config/defines.hxx.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/log4cplus/config/defines.hxx @ONLY)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include
		      ${CMAKE_CURRENT_BINARY_DIR}/include
		      )
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/log4cplus/include)
#log4cplus
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/log4cplus")

add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld log4cplus)
