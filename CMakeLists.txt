cmake_minimum_required(VERSION 3.9)
project(kron)

set(CMAKE_CXX_STANDARD 11)
set(LINKER_LIBS "")

# gflags
include("cmake/FindGFlags.cmake")
include_directories(SYSTEM ${GFLAGS_INCLUDE_DIRS})
list(APPEND LINKER_LIBS ${GFLAGS_LIBRARIES})

add_executable(kron main.cpp
        make_graph.c
        graph_generator.c
        utils.c
        splittable_mrg.c)
target_link_libraries(kron ${LINKER_LIBS})