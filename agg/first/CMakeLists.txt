cmake_minimum_required (VERSION 2.8)

project (AGGIMAGE)

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"*.h"
    	"*.cpp"
	)
find_library(xlib X11) 
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_executable(AGGIMAGE agg_platform_support.cpp image1.cpp)

include_directories(include)
target_link_libraries(AGGIMAGE libagg.a ${xlib})
