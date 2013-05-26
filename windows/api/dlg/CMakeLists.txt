cmake_minimum_required(VERSION 2.8)

project (dialog)
include("internal.cmake")
set_default_compiler_linker_config()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/window)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dialog)

file(GLOB window RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "window/view.h"
    "window/view.cpp"
    "window/model.h"
    "window/model.cpp"
    "window/window.h"
	"window/window.cpp")

source_group(window FILES ${window})


file(GLOB dialog RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "dialog/dialog_view.h"
    "dialog/dialog_view.cpp"
    "dialog/dialog_model.h"
    "dialog/dialog_model.cpp"
    "dialog/dialog.h"
	"dialog/dialog.cpp")

source_group(dialog FILES ${dialog})

set(source main.cpp canvas.h canvas.cpp res.h generic.rc ${window} ${dialog})


add_executable(dialog ${source})

set_target_properties(dialog PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")


