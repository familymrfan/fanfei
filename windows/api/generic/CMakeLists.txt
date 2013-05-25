cmake_minimum_required(VERSION 2.8)

project (generic)
include("internal.cmake")
set_default_compiler_linker_config()

set(source main.cpp controller.h controller.cpp view.h view.cpp model.h model.cpp canvas.h canvas.cpp)

add_executable(generic ${source})

set_target_properties(generic PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")


