cmake_minimum_required(VERSION 3.12)
project(Sorting)

set(CMAKE_CXX_STANDARD 14)

add_executable(bubble_sort bubble_sort.cpp)
add_executable(insertion_sort insertion_sort.cpp)
add_executable(selection_sort selection_sort.cpp)