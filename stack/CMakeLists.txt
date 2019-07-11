cmake_minimum_required(VERSION 3.10)
project(Stack)

set(CMAKE_CXX_STANDARD 14)

include_directories(../shared/)

add_executable(balanced_brackets balanced_brackets.cpp)
add_executable(min_max_stack min_max_stack.cpp)
