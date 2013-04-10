cmake_minimum_required (VERSION 2.8)
project (HelloWorld)

configure_file(include/log4cplus/config.h.cmake.in
  ${HelloWorld_BINARY_DIR}/include/log4cplus/config.h @ONLY)
configure_file(include/log4cplus/config/defines.hxx.cmake.in
  ${HelloWorld_BINARY_DIR}/include/log4cplus/config/defines.hxx @ONLY)

include_directories (${HelloWorld_SOURCE_DIR}/include
		      ${HelloWorld_BINARY_DIR}/include
		      )
link_directories(${HelloWorld_SOURCE_DIR})
		      
add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld -llog4cplus)
