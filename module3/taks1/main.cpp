#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <vector>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"

#define TEST_GRAPH_SIZE 19

template <class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T>& v) {
    for (const auto elem : v) {
        out << std::setw(3) << elem << " ";
    }
    return out;
}

void constructTestGraph(IGraph* graph) {
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
}

std::array<IGraph*, 4> createGraphs(bool chain) {
    IGraph* listGraph = nullptr;
    IGraph* matrixGraph = nullptr;
    IGraph* setGraph = nullptr;
    IGraph* arcGraph = nullptr;
    std::array<IGraph*,4> graphs;
    if (chain) {
        IGraph* graph = new ArcGraph(TEST_GRAPH_SIZE);
        constructTestGraph(graph);
        listGraph = new ListGraph(*graph);
        matrixGraph = new MatrixGraph(*listGraph);
        setGraph = new SetGraph(*matrixGraph);
        arcGraph = new ArcGraph(*setGraph);
        graphs = {listGraph, matrixGraph, setGraph, arcGraph};
        delete graph;
    } else {
        listGraph = new ListGraph(TEST_GRAPH_SIZE);
        matrixGraph = new MatrixGraph(TEST_GRAPH_SIZE);
        setGraph = new SetGraph(TEST_GRAPH_SIZE);
        arcGraph = new ArcGraph(TEST_GRAPH_SIZE);
        graphs = {listGraph, matrixGraph, setGraph, arcGraph};
        for (int i = 0; i != 4; i++) {
            constructTestGraph(graphs[i]);
        }
    }
    return graphs;
}

std::vector<int> getRightVertexes(int vertex, bool prev) {
    std::vector<int> result;
    switch (vertex) {
        case  0: {
            result = prev ? std::vector<int>{1, 7, 15}      :  std::vector<int>{1};
            break;
        }
        case  1: {
            result = prev ? std::vector<int>{0}             :  std::vector<int>{0, 15, 18, 9};
            break;
        }
        case  2: {
            result = prev ? std::vector<int>{3, 10, 12}     :  std::vector<int>{18, 3};
            break;
        }
        case  3: {
            result = prev ? std::vector<int>{2}             :  std::vector<int>{12, 13, 2};
            break;
        }
        case  4: {
            result = prev ? std::vector<int>{5, 13}         :  std::vector<int>{10, 17};
            break;
        }
        case  5: {
            result = prev ? std::vector<int>{6, 8}          :  std::vector<int>{17, 4, 8};
            break;
        }
        case  6: {
            result = prev ? std::vector<int>{7, 8}          :  std::vector<int>{5};
            break;
        }
        case  7: {
            result = prev ? std::vector<int>{14}            :  std::vector<int>{0, 16, 6};
            break;
        }
        case  8: {
            result = prev ? std::vector<int>{5, 9, 16, 17}  :  std::vector<int>{5, 6};
            break;
        }
        case  9: {
            result = prev ? std::vector<int>{1, 16, 17, 18} :  std::vector<int>{8};
            break;
        }
        case 10: {
            result = prev ? std::vector<int>{4, 17}         :  std::vector<int>{13, 2};
            break;
        }
        case 11: {
            result = prev ? std::vector<int>{15}            :  std::vector<int>{12, 15};
            break;
        }
        case 12: {
            result = prev ? std::vector<int>{3, 11, 18}     :  std::vector<int>{13, 2};
            break;
        }
        case 13: {
            result = prev ? std::vector<int>{3, 10, 12}     :  std::vector<int>{4};
            break;
        }
        case 14: {
            result = prev ? std::vector<int>{}              :  std::vector<int>{15, 7};
            break;
        }
        case 15: {
            result = prev ? std::vector<int>{1, 11, 14}     :  std::vector<int>{0, 11};
            break;
        }
        case 16: {
            result = prev ? std::vector<int>{7}             :  std::vector<int>{8, 9};
            break;
        }
        case 17: {
            result = prev ? std::vector<int>{4, 5}          :  std::vector<int>{10, 8, 9};
            break;
        }
        case 18: {
            result = prev ? std::vector<int>{1, 2}          :  std::vector<int>{12, 9};
            break;
        }
        default:
            break;
    }

    return result;
}

void runTests() {
    {
        std::cout << "\nChecking graphs created by addEdge" << std::endl;
        std::array<IGraph*,4> graphs = createGraphs(false);
        for (int i = 0; i != TEST_GRAPH_SIZE; i++) {
            std::vector<int> goldPrevVertices = getRightVertexes(i, true);
            std::vector<int> goldNextVertices = getRightVertexes(i, false);
            std::sort(goldPrevVertices.begin(), goldPrevVertices.end());
            std::sort(goldNextVertices.begin(), goldNextVertices.end());
            std::cout << "    Cheking vertex" << std::setw(3) << i << ":"<< std::endl;
            for (int j = 0; j != graphs.size(); j++) {
                std::vector<int> prevVertices = graphs[j]->getPrevVertices(i);
                std::sort(prevVertices.begin(), prevVertices.end());
                assert(prevVertices == goldPrevVertices);
                std::cout << "        graph" << std::setw(2) << j << " prev : OK"<< std::endl;

                std::vector<int> nextVertices = graphs[j]->getNextVertices(i);
                std::sort(nextVertices.begin(), nextVertices.end());
                assert(nextVertices == goldNextVertices);
                std::cout << "        graph" << std::setw(2) << j << " next : OK"<< std::endl;
                //std::cout << "Vertex " << std::setw(3) << i << " prev : " << graph->getPrevVertices(i) << std::endl;
            }
            //std::cout << "============================================" << std::endl;
        }

        delete graphs[0];
        delete graphs[1];
        delete graphs[2];
        delete graphs[3];
    }
    {
        std::cout << "\nChecking graphs created one from another" << std::endl;
        std::array<IGraph*,4> graphs = createGraphs(true);
        for (int i = 0; i != TEST_GRAPH_SIZE; i++) {
            std::vector<int> goldPrevVertices = getRightVertexes(i, true);
            std::vector<int> goldNextVertices = getRightVertexes(i, false);
            std::sort(goldPrevVertices.begin(), goldPrevVertices.end());
            std::sort(goldNextVertices.begin(), goldNextVertices.end());
            std::cout << "    Cheking vertex" << std::setw(3) << i << ":"<< std::endl;
            for (int j = 0; j != graphs.size(); j++) {
                std::vector<int> prevVertices = graphs[j]->getPrevVertices(i);
                std::sort(prevVertices.begin(), prevVertices.end());
                assert(prevVertices == goldPrevVertices);
                std::cout << "        graph" << std::setw(2) << j << " prev : OK"<< std::endl;

                std::vector<int> nextVertices = graphs[j]->getNextVertices(i);
                std::sort(nextVertices.begin(), nextVertices.end());
                assert(nextVertices == goldNextVertices);
                std::cout << "        graph" << std::setw(2) << j << " next : OK"<< std::endl;
                //std::cout << "Vertex " << std::setw(3) << i << " prev : " << graph->getPrevVertices(i) << std::endl;
            }
            //std::cout << "============================================" << std::endl;
        }

        delete graphs[0];
        delete graphs[1];
        delete graphs[2];
        delete graphs[3];
    }
}

int main(int argc, char const *argv[]) {
    runTests();
    return 0;
}
