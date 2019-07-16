#include <iostream>
#include "array_utility.h" // print_array
#include "bst.h"
#include "bst_traverse.h"

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

    auto inOrder = bstTraverseInOrder(bst);
    auto preOrder = bstTraversePreOrder(bst);
    auto postOrder = bstTraversePostOrder(bst);

    cout<<"In Order:"<<endl;
    print_array(inOrder);

    cout<<"Pre Order:"<<endl;
    print_array(preOrder);

    cout<<"Post Order:"<<endl;
    print_array(postOrder);
    
    return 0;
}