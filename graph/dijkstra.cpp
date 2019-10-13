#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

#include "graph.h"
#include "heap/heap_map.h"

using namespace std;

vector<int> dijkstra(const vector<vector<GraphLink>>& graph, int fromIndex, int toIndex)
{
    vector<int> distance(graph.size(), INT_MAX);
    vector<int> previousIndex(graph.size(), -1);
    vector<bool> visited(graph.size());

    distance[fromIndex] = 0;

    heap_map<int, int, greater<int>> vertexQueue;

    vertexQueue.insert({fromIndex, 0});

    while (!vertexQueue.empty()) {
        int index, weight;
        tie(index, weight) = vertexQueue.top();
        vertexQueue.pop();
        auto& edges = graph[index];

        // relaxation
        auto currentDistance = distance[index];

        for (auto& edge : edges) {
            auto& targetIndex = edge.index;
            if (visited[targetIndex]) {
                continue;
            }

            auto& targetDistance = distance[targetIndex];
            auto newDistance = currentDistance + edge.weight;
            if (targetDistance < newDistance) {
                continue;
            }

            targetDistance = newDistance;
            previousIndex[targetIndex] = index;
            vertexQueue.insert_or_assign(targetIndex, newDistance);
        }

        visited[index] = true;
    }


    vector<int> result;

    while (toIndex >= 0) {
        result.push_back(toIndex);
        toIndex = previousIndex[toIndex];
    }

    reverse(begin(result), end(result));

    return result;
}

int main()
{
    auto graph = createWeightedGraph({
        {0, 1, 6},
        {0, 3, 1},
        {1, 3, 2},
        {1, 4, 2},
        {1, 2, 3},
        {3, 4, 1},
        {4, 2, 5}
    }, true);

    auto path = dijkstra(graph, 0, 2);

    for (auto& item : path) {
        cout << item << " ";
    }

    cout << endl;

    return 0;
}