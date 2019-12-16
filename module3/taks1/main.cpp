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
    IGraph* listGraph = new ListGraph(graphSize);

    //for (auto& graph : graphs) {
        listGraph->addEdge(0, 1);
        listGraph->addEdge(1, 0);
        listGraph->addEdge(1, 15);
        listGraph->addEdge(1, 18);
        listGraph->addEdge(1, 9);
        listGraph->addEdge(2, 18);
        listGraph->addEdge(2, 3);
        listGraph->addEdge(3, 12);
        listGraph->addEdge(3, 13);
        listGraph->addEdge(3, 2);
        listGraph->addEdge(4, 10);
        listGraph->addEdge(4, 17);
        listGraph->addEdge(5, 17);
        listGraph->addEdge(5, 4);
        listGraph->addEdge(5, 8);
        listGraph->addEdge(6, 5);
        listGraph->addEdge(7, 0);
        listGraph->addEdge(7, 16);
        listGraph->addEdge(7, 6);
        listGraph->addEdge(8, 5);
        listGraph->addEdge(8, 6);
        listGraph->addEdge(9, 8);
        listGraph->addEdge(10, 13);
        listGraph->addEdge(10, 2);
        listGraph->addEdge(11, 12);
        listGraph->addEdge(11, 15);
        listGraph->addEdge(12, 13);
        listGraph->addEdge(12, 2);
        listGraph->addEdge(13, 4);
        listGraph->addEdge(14, 15);
        listGraph->addEdge(14, 7);
        listGraph->addEdge(15, 0);
        listGraph->addEdge(15, 11);
        listGraph->addEdge(16, 8);
        listGraph->addEdge(16, 9);
        listGraph->addEdge(17, 10);
        listGraph->addEdge(17, 8);
        listGraph->addEdge(17, 9);
        listGraph->addEdge(18, 12);
        listGraph->addEdge(18, 9);
    //}


    IGraph* arcGraph = new ArcGraph(*listGraph);
    IGraph* matrixGraph = new MatrixGraph(*listGraph);
    IGraph* setGraph = new SetGraph(*listGraph);

    std::array<IGraph*,4> graphs = {listGraph ,arcGraph ,matrixGraph ,setGraph};




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
