cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -fpic -flto")

include_directories("tsp_lib/Include")
include_directories("tsp_test/Include")


add_subdirectory(tsp_lib)
add_subdirectory(tsp_test)

add_executable(tsp main.cpp)

target_link_libraries(tsp PUBLIC tsp_core tsp_tester fmt)
