#include <iostream>
#include <vector>

#include "graph.h"

using namespace std;

void dfs(const vector<vector<int>>& graph, int vertexIndex, vector<bool>& visited, vector<int>& result)
{
    if (visited[vertexIndex]) {
        return;
    }
    visited[vertexIndex] = true;

    auto& vertex = graph[vertexIndex];

    for (auto& adjecentIndex : vertex) {
        if (visited[adjecentIndex]) {
            continue;
        }

        dfs(graph, adjecentIndex, visited, result);
    }

    result.push_back(vertexIndex);
}

vector<int> topologicalSort(const vector<vector<int>>& graph)
{
    vector<int> result;
    vector<bool> visited(graph.size());

    for (size_t i = 0; i < graph.size(); ++i) {
        if (visited[i]) {
            continue;
        }

        dfs(graph, i, visited, result);
    }

    reverse(begin(result), end(result));

    return result;
}

int main()
{
    auto graph = createGraph({
        {0, 6}, {1, 2}, {1, 4},
        {1, 6}, {3, 0}, {3, 4},
		{5, 1}, {7, 0}, {7, 1}
    });

    auto order = topologicalSort(graph);

    for (auto& item : order) {
        cout << item << " ";
    }

    cout << endl;

    return 0;
}