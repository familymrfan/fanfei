cmake_minimum_required(VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

project(sqlite3 C)
if (MSVC11)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MTd") # link to multi thread static library
    set(common_c_release_flag "${common_cxx_release_flag} -MT") # link to multi thread static library
endif()

add_library(sqlite3 sqlite3.c)

if(UNIX)
	target_link_libraries(sqlite3 pthread)
	target_link_libraries(sqlite3 dl)
endif(UNIX)