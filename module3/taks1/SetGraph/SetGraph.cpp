#include "SetGraph.hpp"
#include <iostream>


SetGraph::SetGraph(int size) :
    vertices_count(size) {
    graph.resize(size);
}

SetGraph::~SetGraph() {}

void SetGraph::addEdge(int from, int to) {
    graph[from].emplace(to);
}

int SetGraph::verticesCount() const {
    return vertices_count;
}

std::vector<int> SetGraph::getNextVertices(int vertex) const {
    std::vector<int> result(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> SetGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i != vertices_count; i++) {
        if (graph[i].find(vertex) != graph[i].end()) {
            result.push_back(i);
        }
    }
    return result;
}