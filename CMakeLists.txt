cmake_minimum_required(VERSION 3.9)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
project(kron)

set(CMAKE_CXX_STANDARD 11)

# GFlags
add_subdirectory(deps/gflags)
include_directories(${PROJECT_BINARY_DIR}/deps/gflags/include)
link_directories(${PROJECT_BINARY_DIR}/deps/gflags/lib)

add_executable(kron main.cpp
        make_graph.c
        graph_generator.c
        utils.c
        splittable_mrg.c)
target_link_libraries(kron gflags_static)
