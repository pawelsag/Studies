cmake_minimum_required(VERSION 3.13)
project("pae_project_2019")

exec_program(nproc
			 OUTPUT_VARIABLE RETURN_THREAD_COUNT)

message(STATUS "Found ${RETURN_THREAD_COUNT} active threads")

add_compile_definitions(THREAD_COUNT=${RETURN_THREAD_COUNT})


file(GLOB SRC_FILES "Source/*.cpp")
add_library(tsp_tester "${SRC_FILES}")

target_link_libraries(tsp_tester tsp_core fmt)