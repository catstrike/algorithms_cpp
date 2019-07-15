#include <iostream> // std::cout
#include "bst.h"
#include "bst_utility.h"

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

    cout<<"bst.contains(7) = "<<bst.contains(7)<<endl;
    cout<<"bst.contains(13) = "<<bst.contains(13)<<endl;

    bst_print(bst);

    cout<<endl;
    cout<<"Remove 10"<<endl;
    bst.remove(10);
    bst_print(bst);

    cout<<endl;
    cout<<"Remove 15"<<endl;
    bst.remove(15);
    bst_print(bst);

    return 0;
}