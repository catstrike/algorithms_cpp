#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "tree.h"

using namespace std;

template <class TKey, class TValue>
class Trees
{
    using TNode = Node<TKey, TValue>;
    using TNodePtr = shared_ptr<TNode>;

    unordered_map<TKey, TNodePtr> nodes;
    unordered_map<TKey, TNodePtr> roots;
public: // - Properties
    vector<TNodePtr> getRoots()
    {
        vector<TNodePtr> result;

        for (auto root : roots) {
            result.push_back(root.second);
        }

        return result;
    }

public: // - Public
    Trees& addEdge(TKey parentKey, TKey childKey)
    {
        auto parent_it = nodes.find(parentKey);
        TNodePtr parent;

        if (parent_it != nodes.end()) {
            parent = parent_it->second;
        } else {
            parent = make_shared<TNode>(parentKey, TValue());
            nodes.insert({parentKey, parent});
            roots.insert({parentKey, parent});
        }

        auto child_it = nodes.find(childKey);
        TNodePtr child;

        if (child_it != nodes.end()) {
            child = child_it->second;

            auto childInRoots_it = roots.find(childKey);
            if (childInRoots_it != roots.end()) {
                roots.erase(childInRoots_it);
            }
        } else {
            child = make_shared<TNode>(childKey, TValue());
            nodes.insert({childKey, child});
        }

        parent->insert(child);

        return *this;
    }
};

int main()
{
    Trees<int, string> trees;

    trees
        .addEdge(1, 2)
        .addEdge(1, 3)
        .addEdge(2, 4)
        .addEdge(2, 5)
        .addEdge(3, 6)
        .addEdge(3, 7)

        .addEdge(8, 9)
        .addEdge(8, 10)
        .addEdge(8, 11);

    trees.addEdge(3, 8);

    auto roots = trees.getRoots();

    for (auto& root : roots) {
        cout<<"Root: "<<root->getKey()<<endl;

        for (auto& node : *root) {
            cout<<node.getKey()<<": "<<node.getValue()<<endl;
        }
    }

    return 0;
}