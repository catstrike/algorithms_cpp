#include <iostream>
#include <limits>
#include "bst.h"
#include "validate_bst.h"

using namespace std;

int main()
{
    BST<int> bst;

    bst
        .insert(10)
        .insert(5)
        .insert(15)
        .insert(2)
        .insert(5)
        .insert(13)
        .insert(22)
        .insert(1)
        .insert(14);

    bst.getRoot()->left->right->right = new BSTNode<int>(11);

    auto result = validateBst(bst);

    cout<<"BST is "<<(result ? "valid" : "invalid")<<endl;
    
    return 0;
}