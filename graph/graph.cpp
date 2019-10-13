#include "graph.h"

auto getMaxIndex(const std::vector<Edge>& edges) -> decltype(Edge::start)
{
    auto maxIt = std::max_element(
        std::begin(edges),
        std::end(edges),
        [](const Edge& a, const Edge& b) {
            return std::max(a.start, a.end) < std::max(b.start, b.end);
        }
    );

    return std::max(maxIt->start, maxIt->end) + 1;
}

std::vector<std::vector<int>> createGraph(const std::vector<Edge>& edges)
{
    auto totalVertices = getMaxIndex(edges);

    std::vector<std::vector<int>> graph(totalVertices);

    for (auto& edge : edges) {
        graph[edge.start].push_back(edge.end);
    }

    return graph;
}

std::vector<std::vector<GraphLink>> createWeightedGraph(const std::vector<Edge>& edges, bool undirected)
{
    auto totalVertices = getMaxIndex(edges);

    std::vector<std::vector<GraphLink>> graph(totalVertices);

    for (auto& edge : edges) {
        graph[edge.start].push_back({edge.end, edge.weight});
        
        if (undirected) {
            graph[edge.end].push_back({edge.start, edge.weight});
        }
    }

    return graph;
}