#include "ArcGraph.hpp"

ArcGraph::ArcGraph(int size) : vertices_count(size) {}

ArcGraph::~ArcGraph() {}

void ArcGraph::addEdge(int from, int to) {
    Edge newEdge(from, to);
    graph.push_back(newEdge);
}

int ArcGraph::verticesCount() const {
    return vertices_count;
}

std::vector<int> ArcGraph::getNextVertices(int vertex) const {
    std::vector<int> result;
    for (const auto& Edge : graph) {
        if (Edge.from == vertex) {
            result.push_back(Edge.to);
        }
    }
    return result;
}

std::vector<int> ArcGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (const auto& Edge : graph) {
        if (Edge.to == vertex) {
            result.push_back(Edge.from);
        }
    }
    return result;
}