cmake_minimum_required(VERSION 2.8)

project (canvas)
include("internal.cmake")
set_default_compiler_linker_config()

file(GLOB source RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	"*.h"
    "*.cpp"
	"*.rc")

file(GLOB window RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "window/*.h"
	"window/*.cpp")

source_group(window FILES ${window})

file(GLOB canvas RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "canvas/*.h"
	"canvas/*.cpp")

source_group(canvas FILES ${canvas})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/window)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/canvas)

add_executable(canvas ${source} ${canvas} ${window})

set_target_properties(canvas PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")


