#include <iostream>
#include <vector>

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

struct Edge {
    int start;
    int end;
};

vector<vector<int>> createGraph(const vector<Edge>& edges)
{
    auto maxIt = max_element(
        begin(edges),
        end(edges),
        [](const Edge& a, const Edge& b) {
            return max(a.start, a.end) < max(b.start, b.end);
        }
    );

    auto totalVertices = max(maxIt->start, maxIt->end) + 1;

    cout << totalVertices << endl;

    vector<vector<int>> graph(totalVertices);

    for (auto& edge : edges) {
        graph[edge.start].push_back(edge.end);
    }

    return graph;
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