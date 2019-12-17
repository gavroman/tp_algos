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
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
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

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T>& v) {
    for (const auto elem : v) {
        out << std::setw(3) << elem << " ";
    }
    return out;
}

int countShortestPaths(ListGraph& graph, int startVertex, int endVertex) {
    int verticesCount = graph.size();
    std::vector<int> distances(verticesCount, INT_MAX);
    std::vector<int> paths_number(verticesCount, 0);
    std::vector<int> parents(verticesCount, -1);
    std::queue<int> q;
    q.push(startVertex);
    distances[startVertex] = 0;
    while(!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        std::vector<int> nextVertices = graph.getVertices(currentVertex);
        for (const auto& nextVertex : nextVertices) {
            if (distances[nextVertex] == INT_MAX) {
                distances[nextVertex] = distances[currentVertex] + 1;
                paths_number[nextVertex] = paths_number[currentVertex];
                parents[nextVertex] = currentVertex;
                q.push(nextVertex);
            } else if (distances[currentVertex] + 1 == distances[nextVertex]) {
                distances[nextVertex] = distances[currentVertex] + 1;
                paths_number[nextVertex] += paths_number[currentVertex];
                parents[nextVertex] = currentVertex;
            }
        }
    }
    // std::cout << "parents: " << parents << std::endl;
    // std::cout << "distances: " << distances << std::endl;

    // std::cout << "shortest distance : " << distances[endVertex] << std::endl;
    // std::cout << "paths count : " << paths_number[endVertex] << std::endl;

    std::cout << paths_number[endVertex] << std::endl;

    // int currentVertex = endVertex;
    // while (currentVertex != startVertex) {
    //     std::cout << currentVertex << "<-";
    //     currentVertex = parents[currentVertex];
    // }
    // std::cout << startVertex << std::endl;

    return 0;
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
        input >> from >> to;
        graph.addEdge(from, to);
    }

    int startVertex = -1;
    int endVertex = -1;
    input >> startVertex >> endVertex;
    int ShortestPathsNumber = countShortestPaths(graph, startVertex, endVertex);
    // for (int i = 0; i != graph.size(); i++) {
    //     std::cout << std::setw(3) << i << " vertecies: " << graph.getVertices(i) << std::endl;
    // }
}

void test() {
    run(std::cin);
/*    {
        std::stringstream input;
        input << "19" << std::endl;  //  vertices
        input << "37" << std::endl;  //  edges

        input << "0 16" << std::endl;
        input << "1 0" << std::endl;
        input << "1 15" << std::endl;
        input << "1 18" << std::endl;
        input << "1 9" << std::endl;
        input << "2 18" << std::endl;
        input << "3 12" << std::endl;
        input << "3 13" << std::endl;
        input << "3 2" << std::endl;
        input << "4 10" << std::endl;
        input << "4 17" << std::endl;
        input << "5 17" << std::endl;
        input << "5 4" << std::endl;
        input << "6 5" << std::endl;
        input << "7 0" << std::endl;
        input << "7 16" << std::endl;
        input << "7 6" << std::endl;
        input << "8 5" << std::endl;
        input << "8 6" << std::endl;
        input << "9 8" << std::endl;
        input << "10 13" << std::endl;
        input << "10 2" << std::endl;
        input << "11 12" << std::endl;
        input << "11 15" << std::endl;
        input << "12 13" << std::endl;
        input << "12 2" << std::endl;
        input << "13 4" << std::endl;
        input << "14 15" << std::endl;
        input << "14 7" << std::endl;
        input << "15 0" << std::endl;
        input << "16 8" << std::endl;
        input << "16 9" << std::endl;
        input << "17 10" << std::endl;
        input << "17 8" << std::endl;
        input << "17 9" << std::endl;
        input << "18 12" << std::endl;
        input << "18 9" << std::endl;

        input << "14 10" << std::endl;

        run(input);
    }*/
    /*{
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

        input << "0 5" << std::endl;  // route

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
    test();
    return 0;
}