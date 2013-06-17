cmake_minimum_required(VERSION 2.8)

project (Array)
#include("internal.cmake")
#set_default_compiler_linker_config()

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"*.h"
    	"*.cpp"
	)

add_executable(Array ${source})

