cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

file(GLOB SRC_FILES "Source/*.cpp")
add_library(tsp_core "${SRC_FILES}")

target_link_libraries(tsp_core fmt stdc++fs)