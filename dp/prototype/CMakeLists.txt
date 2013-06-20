cmake_minimum_required(VERSION 2.8)

project (ProtoType)
include("internal.cmake")
set_default_compiler_linker_config()

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"*.h"
    	"*.cpp"
	)

add_executable(ProtoType ${source})

