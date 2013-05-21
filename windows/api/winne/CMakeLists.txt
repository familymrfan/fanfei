cmake_minimum_required(VERSION 2.8)

project (winne)
include("internal.cmake")
set_default_compiler_linker_config()

add_executable(winne winne.cpp)

set_target_properties(winne PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")


