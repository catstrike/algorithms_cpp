cmake_minimum_required(VERSION 3.10)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

include_directories(../shared/)
add_executable(breadth_first_search breadth_first_search.cpp)
