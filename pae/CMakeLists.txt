cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

include_directories("Include")
set (CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES "Source/*.cpp")
add_executable(tsp "${SRC_FILES}")

target_link_libraries(tsp fmt)