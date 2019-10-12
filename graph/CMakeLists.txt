cmake_minimum_required(VERSION 3.10)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

include_directories(../shared/)
add_executable(breadth_first_search breadth_first_search.cpp)
add_executable(river_sizes river_sizes.cpp)
add_executable(bidirectional_bfs bidirectional_bfs.cpp)
add_executable(topological_sort topological_sort.cpp)
