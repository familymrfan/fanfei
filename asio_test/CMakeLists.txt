cmake_minimum_required (VERSION 2.8)

project (AsioTest)

# compiler and linker config
include("internal.cmake")
set_default_compiler_linker_config()  # Defined in internal.cmake.

add_definitions(-DBOOST_ALL_NO_LIB -DBOOST_EXCEPTION_DISABLE)

set(Boost_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/boost)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/date_time)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/regex)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/system)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost/libs/thread)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/boost)

add_executable(AsioTest main.cpp)

target_link_libraries(AsioTest boost_date_time boost_regex boost_system boost_thread)
