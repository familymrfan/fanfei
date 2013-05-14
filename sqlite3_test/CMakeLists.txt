cmake_minimum_required (VERSION 2.8)

project (Sqlite3Test)

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/sqlite3)

add_library(Sqlite3Test db_sqlite3.cpp)

set(SQL_LIBS sqlite3)

if(UNIX)
message("add pthread on linux")
set(SQL_LIBS ${SQL_LIBS} pthread)
endif()

target_link_libraries(Sqlite3Test ${SQL_LIBS})
