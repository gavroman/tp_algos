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

#include <assert.h>
#include <bits/stdc++.h>
#include <iomanip>
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
                distances[edge.to] = distances[currentVertex] + edge.weight;
                persistantQueue.emplace(std::make_pair(distances[edge.to], edge.to));
            } else if (distances[currentVertex] + edge.weight < distances[edge.to]) {
                // Decrease priority of next vertex from current vertex
                persistantQueue.erase(std::make_pair(distances[edge.to], edge.to));
                distances[edge.to] = distances[currentVertex] + edge.weight;
                persistantQueue.emplace(std::make_pair(distances[edge.to], edge.to));
            }
        }
    }

    return distances[endVertex];
}

void run(std::istream& input) {
    int graphSize = 0;
    input >> graphSize;
    assert(graphSize <= 50000);

    int edgesCount = 0;
    input >> edgesCount;
    assert(edgesCount <= 200000);

    ListGraph graph(graphSize);
    for (int i = 0; i != edgesCount; i++) {
        int from = 0;
        int to = 0;
        int time = 0;
        input >> from >> to >> time;
        graph.addEdge(from, to, time);
    }

    int startVertex = -1;
    int endVertex = -1;
    input >> startVertex >> endVertex;
    calculateShortestPath(graph, startVertex, endVertex);
}

void test() {
    {
        std::stringstream input;

        input << "6" << std::endl;   //  vertices
        input << "9" << std::endl;   //  edges
        input << "0 3 1" << std::endl;
        input << "0 4 2" << std::endl;
        input << "1 2 7" << std::endl;
        input << "1 3 2" << std::endl;
        input << "1 4 3" << std::endl;
        input << "1 5 3" << std::endl;
        input << "2 5 3" << std::endl;
        input << "3 4 4" << std::endl;
        input << "3 5 6" << std::endl;

        input << "0 2" << std::endl;   //  edges

        run(input);
    }
/*    {
        std::stringstream input;
        input << "6" << std::endl;  //  vertices
        input << "7" << std::endl;  //  edges

        input << "0 1" << std::endl;
        input << "0 2" << std::endl;
        input << "0 3" << std::endl;
        input << "1 4" << std::endl;
        input << "2 4" << std::endl;
        input << "3 4" << std::endl;
        input << "5 4" << std::endl;

        input << "0 5" << std::endl;  //  edges

        run(input);
    }*/
/*    {
        std::stringstream input;
        input << "7" << std::endl;  //  vertices
        input << "8" << std::endl;  //  edges

        input << "0 1" << std::endl;
        input << "0 2" << std::endl;
        input << "1 3" << std::endl;
        input << "2 3" << std::endl;
        input << "3 4" << std::endl;
        input << "3 5" << std::endl;
        input << "4 6" << std::endl;
        input << "5 6" << std::endl;

        input << "0 6" << std::endl;  // route

        run(input);
    }*/
}

int main(int argc, char const *argv[]) {
       int graphSize = 0;
    input >> graphSize;
    assert(graphSize <= 50000);

    int edgesCount = 0;
    input >> edgesCount;
    assert(edgesCount <= 200000);

    ListGraph graph(graphSize);
    for (int i = 0; i != edgesCount; i++) {
        int from = 0;
        int to = 0;
        int time = 0;
        input >> from >> to >> time;
        graph.addEdge(from, to, time);
    }

    int startVertex = -1;
    int endVertex = -1;
    input >> startVertex >> endVertex;
    std::cout << calculateShortestPath(graph, startVertex, endVertex) << std::endl;
    return 0;
}