#ifndef _GRAPH_GRAPH_H_
#define _GRAPH_GRAPH_H_

#include <vector>

struct Edge {
    int start;
    int end;
    int weight;
};

struct GraphLink {
    int index;
    int weight;
};

std::vector<std::vector<int>> createGraph(const std::vector<Edge>& edges);
std::vector<std::vector<GraphLink>> createWeightedGraph(const std::vector<Edge>& edges, bool undirected = false);

#endif // _GRAPH_GRAPH_H_
