/*
 * Требуется отыскать самый выгодный маршрут между городами.
 * Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
 * Формат входных данных:
 * Первая строка содержит число N – количество городов.
 * Вторая строка содержит число M - количество дорог.
 * Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
 * Последняя строка содержит маршрут (откуда и куда нужно доехать).
 * Формат выходных данных:
 * Вывести длину самого выгодного маршрута.
 */

#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <vector>

struct Edge {
    int to;
    int weight;
    explicit Edge() : to(-1), weight(-1) {}
    Edge(int vertex, int w) : to(vertex), weight(w) {}
};

class ListGraph{
 public:
    explicit ListGraph(int size) :
        verticesCount(size) {
        graph.resize(size);
    }

    ~ListGraph() = default;

    void addEdge(int from, int to, int weight) {
        graph[from].push_back(Edge(to, weight));
        graph[to].push_back(Edge(from, weight));
    }

    int size() const {
        return verticesCount;
    }
    std::vector<Edge> getEdgesFromVertex(int vertex) const {
        std::vector<Edge> result(graph[vertex].size());
        std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
        return result;
    }

 private:
    std::vector<std::vector<Edge>> graph;
    int verticesCount;
};


int calculateShortestPath(ListGraph& graph, int startVertex, int endVertex) {
    int verticesCount = graph.size();
    std::vector<int> distances(verticesCount, INT_MAX);
    distances[startVertex] = 0;

    std::set<std::pair<int, int>> persistantQueue;
    persistantQueue.emplace(std::make_pair(distances[startVertex], startVertex));

    while(!persistantQueue.empty()) {
        int currentVertex = (persistantQueue.begin())->second;
        persistantQueue.erase(std::make_pair(distances[currentVertex], currentVertex));
        std::vector<Edge> edges = graph.getEdgesFromVertex(currentVertex);

        for (const auto& edge : edges) {
            if (distances[edge.to] == INT_MAX) {
                // Vertex is visited first time
                distances[edge.to] = distances[currentVertex] + edge.weight;
                persistantQueue.emplace(std::make_pair(distances[edge.to], edge.to));
            } else if (distances[currentVertex] + edge.weight < distances[edge.to]) {
                // Shortest path found, decreasing key
                persistantQueue.erase(std::make_pair(distances[edge.to], edge.to));
                distances[edge.to] = distances[currentVertex] + edge.weight;
                persistantQueue.emplace(std::make_pair(distances[edge.to], edge.to));
            }
        }
    }

    return distances[endVertex];
}

int main(int argc, char const *argv[]) {
    int graphSize = 0;
    std::cin >> graphSize;

    int edgesCount = 0;
    std::cin >> edgesCount;

    ListGraph graph(graphSize);
    for (int i = 0; i != edgesCount; i++) {
        int from = 0;
        int to = 0;
        int time = 0;
        std::cin >> from >> to >> time;
        graph.addEdge(from, to, time);
    }

    int startVertex = -1;
    int endVertex = -1;
    std::cin >> startVertex >> endVertex;
    std::cout << calculateShortestPath(graph, startVertex, endVertex) << std::endl;
    return 0;
}