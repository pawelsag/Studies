cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

include_directories("tsp_lib/Include")

add_subdirectory(tsp_lib)

add_executable(tsp main.cpp)

target_link_libraries(tsp PUBLIC tsp_core fmt)
