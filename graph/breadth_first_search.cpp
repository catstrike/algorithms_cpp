#include <vector>
#include <string>
#include <queue>

#include "array_utility.h" // print_array

using namespace std;

// Breadth first search
//
// Time complexity: O(v + e)
// Space complexity: v

class Node
{
public:
    string name;
    vector<Node *> children;

    Node(string str)
    {
        name = str;
    }

    vector<string> breadthFirstSearch(vector<string> *array)
    {
        queue<Node *> line;

        line.push(this);

        while(!line.empty()) {
            auto item = line.front();
            line.pop();

            array->push_back(item->name);

            for (auto child : item->children) {
                line.push(child);
            }
        }

        return *array;
    }

    Node *addChild(string name)
    {
        Node *child = new Node(name);
        children.push_back(child);
        return this;
    }
};

int main()
{
    Node root("a");
    root.addChild("b")
        ->addChild("c")
        ->addChild("d");

    root.children[0]->addChild("e");

    vector<string> array;

    root.breadthFirstSearch(&array);

    print_array(array);

    return 0;
}