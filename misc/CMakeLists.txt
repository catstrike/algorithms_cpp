project(Misc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_executable(sudoku_check sudoku_check.cpp)
add_executable(sudoku_solver sudoku_solver.cpp)