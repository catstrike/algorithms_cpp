#include <iostream>

using namespace std;

template <class TKey, class TValue>
class BSTNode;

template <class TKey, class TValue>
class BST {
    BSTNode<TKey, TValue> * _root;

public: // - Lifecycle
    BST()
        : _root(nullptr)
    {
        cout<<"BST()"<<endl;
    }

    ~BST()
    {
        cout<<"~BST()"<<endl;
        delete _root;
    }

public: // - Public
    void add(TKey key, TValue value)
    {
        _root = _root->add(_root, key, value);
    }
};

template <class TKey, class TValue>
class BSTNode {
private: // - State
    TKey _key;
    TValue _value;
    BSTNode<TKey, TValue> * _left;
    BSTNode<TKey, TValue> * _right;

public: // - Lifecycle
    BSTNode(TKey key, TValue value)
        : _key(key)
        , _value(value)
        , _left(nullptr)
        , _right(nullptr)
    { 
        cout<<"BSTNode("<<_key<<", "<<_value<<")"<<endl;
    }

    ~BSTNode()
    {
        cout<<"~BSTNode("<<_key<<", "<<_value<<")"<<endl;

        delete _left;
        delete _right;
    }

public: // - Public
    const TKey & key() const
    {
        return _key;
    }

    const TValue & value() const
    {
        return _value;
    }

    void setValue(TValue value)
    {
        _value = value;
    }

    BSTNode * add(BSTNode * parent, TKey key, TValue value)
    {
        if (parent == nullptr) {
            return new BSTNode(key, value);
        }

        if (key < _key) {
            _left = add(_left, key, value);
        } else {
            _right = add(_right, key, value);
        }

        return parent;
    }
};

int main()
{
    BST<int, string> bst;

    bst.add(10, "Vasiliy");
    bst.add(7, "Katija");
    bst.add(12, "Petia");

    cout << "Hello!" << endl;
}