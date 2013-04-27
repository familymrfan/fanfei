cmake_minimum_required (VERSION 2.8)
project (PugiTest)

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/docs/samples")
add_executable(PugiTest main.cpp)

target_link_libraries(PugiTest pugi)
