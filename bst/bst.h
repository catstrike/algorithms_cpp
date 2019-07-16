#ifndef _BST_BST_H_
#define _BST_BST_H_

// include <iostream>
// include "bst.h"

template<class TValue>
struct BSTNode
{
    TValue value;
    BSTNode<TValue> * left = nullptr;
    BSTNode<TValue> * right = nullptr;

    BSTNode(TValue value) 
        : value(value)
    {}

    ~BSTNode()
    {
        delete left;
        delete right;
    }
};

template<class TValue>
class BST {
    BSTNode<TValue> * root = nullptr;

public:
    const BSTNode<TValue> * getRoot() const
    {
        return root;
    }

public:
    BST& insert(TValue value)
    {
        if (!root) {
            root = new BSTNode<TValue>(value);
            return *this;
        }

        auto node = root;

        while (true) {
            if (value < node->value) {
                if (node->left == nullptr) {
                    node->left = new BSTNode<TValue>(value);
                    break;
                }
                node = node->left;
            } else {
                if (node->right == nullptr) {
                    node->right = new BSTNode<TValue>(value);
                    break;
                }
                node = node->right;
            }
        }

        return *this;
    }

    bool contains(TValue value)
    {
        auto node = root;

        while (node) {
            if (node->value == value) {
                return true;
            }

            if (value < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return false;
    }

    BST& remove(TValue value)
    {
        auto nodePointer = &root;

        while (*nodePointer) {
            auto node = *nodePointer;

            if (value < node->value) {
                nodePointer = &node->left;
                continue;
            } 
            if (value > node->value) {
                nodePointer = &node->right;
                continue;
            }

            if (!node->left && !node->right) {
                delete node;
                *nodePointer = nullptr;
                break;
            }

            if (node->left && node->right) {
                auto minPointer = findMinPointer(&node->right);
                auto min = *minPointer;
                node->value = min->value;
                // remove min node
                nodePointer = minPointer;
                value = min->value;
                continue;
            }

            auto nextNode = node->left ? node->left : node->right;
            *nodePointer = nextNode;
            node->left = node->right = nullptr;
            delete node;
        }

        return *this;
    }

private:
    BSTNode<TValue>** findMinPointer(BSTNode<TValue> ** node)
    {
        while ((*node)->left) {
            node = &(*node)->left;
        }
        
        return node;
    }
};

#endif // _BST_BST_H_