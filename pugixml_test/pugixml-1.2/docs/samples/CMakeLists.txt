cmake_minimum_required (VERSION 2.8)
project (PugiExample)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)


file (GLOB TEST_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    )

add_executable(PugiExample ${TEST_SOURCE})

target_link_libraries(PugiExample pugi)
