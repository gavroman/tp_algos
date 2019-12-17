/* Задача 2
 * Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
 * Найдите количество различных кратчайших путей между зад анными вершинами.
 * Требования: сложность O(V+E).
 * Формат ввода.
 * v: кол-во вершин (макс. 50000),
 * n: кол-во ребер (макс. 200000),
 * n пар реберных вершин,
 * пара вершин u, w для запроса.
 * Формат вывода.
 * Количество кратчайших путей от u к w.
 */

#include <assert.h>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>

class ListGraph{
 public:
    explicit ListGraph(int size) :
        verticesCount(size) {
        graph.resize(size);
    }

    ~ListGraph() = default;

    void addEdge(int from, int to) {
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    int size() const {
        return verticesCount;
    }
    std::vector<int> getVertices(int vertex) const {
        std::vector<int> result(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }

 private:
    std::vector<std::vector<int>> graph;
    int verticesCount;
};


int countShortestPaths(ListGraph& graph, int startVertex, int endVertex) {
    int verticesCount = graph.size();
    std::vector<int> pathsNumber(verticesCount, 0);
    std::vector<int> distances(verticesCount, INT_MAX);
    distances[startVertex] = 0;
    pathsNumber[startVertex] = 1;
    std::queue<int> q;
    q.push(startVertex);
    while(!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        std::vector<int> nextVertices = graph.getVertices(currentVertex);
        for (const auto& nextVertex : nextVertices) {
            if (distances[nextVertex] == INT_MAX) {
                distances[nextVertex] = distances[currentVertex] + 1;
                pathsNumber[nextVertex] = pathsNumber[currentVertex];
                q.push(nextVertex);
            } else if (distances[currentVertex] + 1 == distances[nextVertex]) {
                pathsNumber[nextVertex] += pathsNumber[currentVertex];
            }
        }
    }

    return pathsNumber[endVertex];
}

int main(int argc, char const *argv[]) {
    int graphSize = 0;
    std::cin >> graphSize;
    assert(graphSize <= 50000);

    int edgesCount = 0;
    std::cin >> edgesCount;
    assert(edgesCount <= 200000);

    ListGraph graph(graphSize);
    for (int i = 0; i != edgesCount; i++) {
        int from = 0;
        int to = 0;
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    int startVertex = -1;
    int endVertex = -1;
    std::cin >> startVertex >> endVertex;
    std::cout << countShortestPaths(graph, startVertex, endVertex) << std::endl;
    return 0;
}