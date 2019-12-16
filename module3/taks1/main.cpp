#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T>& v) {
    for (const auto elem : v) {
        out << std::setw(3) << elem << " ";
    }
    return out;
}

int main(int argc, char const *argv[]) {
    const int graphSize = 19;
    IGraph* arcGraph = new ArcGraph(graphSize);
    IGraph* listGraph = new ListGraph(graphSize);
    IGraph* matrixGraph = new MatrixGraph(graphSize);
    IGraph* setGraph = new SetGraph(graphSize);

    std::array<IGraph*,4> graphs = {arcGraph, listGraph, matrixGraph, setGraph};

    for (auto& graph : graphs) {
        graph->addEdge(0, 1);
        graph->addEdge(1, 0);
        graph->addEdge(1, 15);
        graph->addEdge(1, 18);
        graph->addEdge(1, 9);
        graph->addEdge(2, 18);
        graph->addEdge(2, 3);
        graph->addEdge(3, 12);
        graph->addEdge(3, 13);
        graph->addEdge(3, 2);
        graph->addEdge(4, 10);
        graph->addEdge(4, 17);
        graph->addEdge(5, 17);
        graph->addEdge(5, 4);
        graph->addEdge(5, 8);
        graph->addEdge(6, 5);
        graph->addEdge(7, 0);
        graph->addEdge(7, 16);
        graph->addEdge(7, 6);
        graph->addEdge(8, 5);
        graph->addEdge(8, 6);
        graph->addEdge(9, 8);
        graph->addEdge(10, 13);
        graph->addEdge(10, 2);
        graph->addEdge(11, 12);
        graph->addEdge(11, 15);
        graph->addEdge(12, 13);
        graph->addEdge(12, 2);
        graph->addEdge(13, 4);
        graph->addEdge(14, 15);
        graph->addEdge(14, 7);
        graph->addEdge(15, 0);
        graph->addEdge(15, 11);
        graph->addEdge(16, 8);
        graph->addEdge(16, 9);
        graph->addEdge(17, 10);
        graph->addEdge(17, 8);
        graph->addEdge(17, 9);
        graph->addEdge(18, 12);
        graph->addEdge(18, 9);

        assert(graph->verticesCount() == graphSize);
    }


    for (int i = 0; i != graphSize; i++) {
        for (auto& graph : graphs) {
            std::cout << "Vertex " << std::setw(3) << i << " prev : " << graph->getPrevVertices(i) << std::endl;
        }
        std::cout << "============================================" << std::endl;
    }

    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

    for (int i = 0; i != graphSize; i++) {
        for (auto& graph : graphs) {
            std::cout << "Vertex " << std::setw(3) << i << " next : " << graph->getNextVertices(i) << std::endl;
        }
        std::cout << "---------------------------------------------" << std::endl;
    }






    delete listGraph;
    delete matrixGraph;
    return 0;
}
