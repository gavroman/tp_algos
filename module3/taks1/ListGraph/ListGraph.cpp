#include "ListGraph.hpp"

ListGraph::ListGraph(int size) : vertices_count(size) {
    graph.resize(size);
}

ListGraph::~ListGraph() {}

void ListGraph::addEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::verticesCount() const {
    return vertices_count;
}

std::vector<int> ListGraph::getNextVertices(int vertex) const {
    std::vector<int> result(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (size_t i = 0; i != graph.size(); i++) {
        const auto& children = graph[i];
        for (const auto& child : children) {
            if (child == vertex) {
                result.push_back(i);
            }
        }
    }
    return result;
}