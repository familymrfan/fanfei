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
		      
add_executable(HelloWorld main.cpp)

if(UNIX)
	target_link_libraries(HelloWorld -llog4cplus)
elseif (WIN32)
	target_link_libraries(HelloWorld log4cplusUD.lib)
endif()

