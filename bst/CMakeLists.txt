project(BST)

set(CMAKE_CXX_STANDARD 14)

include_directories(../shared/)

add_executable(find_closest find_closest.cpp)
add_executable(bst bst.cpp)
add_executable(bst_validate bst_validate.cpp)
add_executable(bst_traverse bst_traverse.cpp)