#ifndef _BST_BST_UTILITY_H_
#define _BST_BST_UTILITY_H_

#define COUNT 5

template <class TValue>
void bst_print(const BSTNode<TValue> * root, int space)
{  
    // Base case  
    if (root == nullptr)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    bst_print(root->right, space);  
  
    // Print current node after space  
    // count  
    std::cout<<std::endl;  
    for (int i = COUNT; i < space; i++)  
        std::cout<<" ";  
    std::cout<<root->value<<"\n";  
  
    // Process left child  
    bst_print(root->left, space);  
}  
  
template <class TValue>
void bst_print(const BST<TValue> &bst)  
{  
    bst_print(bst.getRoot(), 0);  
}

#endif // _BST_BST_UTILITY_H_