cmake_minimum_required (VERSION 2.8)
project (gflags)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/windows)

set(GFLAGS_SRC windows/port.cc gflags.cc gflags_reporting.cc gflags_completions.cc)

endif()

if(UNIX)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/linux)

set(GFLAGS_SRC gflags.cc gflags_reporting.cc gflags_completions.cc)

endif()

add_library(gflags ${GFLAGS_SRC})
