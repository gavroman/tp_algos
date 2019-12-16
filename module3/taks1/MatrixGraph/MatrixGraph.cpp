#include "MatrixGraph.hpp"


MatrixGraph::MatrixGraph(int size) :
    vertices_count(size) {
    std::vector<bool> lineOfZero(size, false);
    graph = std::vector<std::vector<bool>>(size, lineOfZero);
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::addEdge(int from, int to) {
    graph[from][to] = true;
}

int MatrixGraph::verticesCount() const {
    return vertices_count;
}

std::vector<int> MatrixGraph::getNextVertices(int vertex) const {
    std::vector<int> result;

    for (int i = 0; i != vertices_count; i++) {
        if (graph[vertex][i]) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> MatrixGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i != vertices_count; i++) {
        if (graph[i][vertex]) {
            result.push_back(i);
        }
    }

    return result;
}