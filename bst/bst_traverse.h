#ifndef _BST_BST_TRAVERSE_H_
#define _BST_BST_TRAVERSE_H_

template <class TValue>
void __bstTraverseInOrder(const BSTNode<TValue> * node, std::vector<TValue>& result)
{
    if (node == nullptr) {
        return;
    }

    __bstTraverseInOrder(node->left, result);
    result.push_back(node->value);
    __bstTraverseInOrder(node->right, result);
}

template <class TValue>
void __bstTraversePreOrder(const BSTNode<TValue> * node, std::vector<TValue>& result)
{
    if (node == nullptr) {
        return;
    }

    result.push_back(node->value);

    __bstTraversePreOrder(node->left, result);
    __bstTraversePreOrder(node->right, result);
}

template <class TValue>
void __bstTraversePostOrder(const BSTNode<TValue> * node, std::vector<TValue>& result)
{
    if (node == nullptr) {
        return;
    }

    __bstTraversePostOrder(node->left, result);
    __bstTraversePostOrder(node->right, result);

    result.push_back(node->value);
}

template <class TValue>
std::vector<TValue> bstTraverseInOrder(const BST<TValue>& bst)
{
    std::vector<TValue> result;
    __bstTraverseInOrder(bst.getRoot(), result);
    return result;
}

template <class TValue>
std::vector<TValue> bstTraversePreOrder(const BST<TValue>& bst)
{
    std::vector<TValue> result;
    __bstTraversePreOrder(bst.getRoot(), result);
    return result;
}

template <class TValue>
std::vector<TValue> bstTraversePostOrder(const BST<TValue>& bst)
{
    std::vector<TValue> result;
    __bstTraversePostOrder(bst.getRoot(), result);
    return result;
}

#endif // _BST_BST_TRAVERSE_H_