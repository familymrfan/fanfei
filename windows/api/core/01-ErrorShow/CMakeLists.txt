cmake_minimum_required(VERSION 2.8)

project (ErrorShow)
include("internal.cmake")
set_default_compiler_linker_config()

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"*.h"
    	"*.cpp"
	"*.ico"
	"*.rc"
	)

add_executable(ErrorShow ${source})

set_target_properties(ErrorShow PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")
