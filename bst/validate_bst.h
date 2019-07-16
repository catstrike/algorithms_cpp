#ifndef _BST_VALIDATE_BST_H_
#define _BST_VALIDATE_BST_H_

#include <limits>

template <class TValue>
bool inRange(const BSTNode<TValue> * node, TValue min, TValue max)
{
    if (node == nullptr) {
        return true;
    }

    if (node->value < min || node->value >= max) {
        return false;
    }

    return inRange(node->left, min, node->value) && inRange(node->right, node->value, max);
}

template <class TValue>
bool validateBst(const BST<TValue> & tree)
{
    return inRange(
        tree.getRoot(),
         std::numeric_limits<TValue>::min(),
         std::numeric_limits<TValue>::max()
    );
}

#endif // _BST_VALIDATE_BST_H_