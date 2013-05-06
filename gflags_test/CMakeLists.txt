cmake_minimum_required (VERSION 2.8)
project (gflagsTest)

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/gflags)

if(WIN32)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/gflags/windows)

endif()

if(UNIX)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/gflags/linux)

endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gflags")
add_executable(gflagsTest main.cpp)

target_link_libraries(gflagsTest gflags)
