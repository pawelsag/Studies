cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

include_directories("Include")
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3 -fpic -flto")

file(GLOB SRC_FILES "Source/*.cpp")
add_library(tsp_core "${SRC_FILES}")

target_link_libraries(tsp_core fmt)