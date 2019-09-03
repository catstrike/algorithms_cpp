#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int value;
    vector<int> connections;
};

class Graph {
    vector<Node> nodes;

public: // - Lifecycle
    Graph(int size)
        : nodes(size + 1)
    {}

public: // - Public
    void connect(int first, int second)
    {
        nodes[first].connections.push_back(second);
        nodes[second].connections.push_back(first);
    }

    int minDistance(vector<int> nodesOfInterest)
    {
        vector<int> visited(nodes.size());
        queue<int> toVisit;

        for (auto nodeIndex : nodesOfInterest) {
            if (visited[nodeIndex] != 0) {
                return 0;
            }

            visited[nodeIndex] = nodeIndex;
            toVisit.push(nodeIndex);
        }

        for (int depth = 0; !toVisit.empty(); ++depth) {
            auto itemsCount = toVisit.size();

            for (; itemsCount > 0; --itemsCount) {
                auto nodeIndex = toVisit.front();
                toVisit.pop();

                auto nodeParentIndex = visited[nodeIndex];
                auto& nodeConnections = nodes[nodeIndex].connections;

                for (auto connection : nodeConnections) {
                    auto& visitedParent = visited[connection];
                    if (visitedParent == nodeParentIndex) {
                        continue;
                    }

                    if (visitedParent != 0) {
                        return depth * 2 + 1;
                    }

                    visitedParent = nodeParentIndex;
                    toVisit.push(connection);
                }
            }
        }

        return -1;

    }
};

int main()
{
    auto size = 4;

    Graph graph(size);
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(4, 2);

    cout << "distance(3, 4) = " << graph.minDistance({3, 4}) << endl;
    cout << "distance(1, 1) = " << graph.minDistance({1, 1}) << endl;
    cout << "distance(1, 2) = " << graph.minDistance({1, 2}) << endl;

    return 0;
}