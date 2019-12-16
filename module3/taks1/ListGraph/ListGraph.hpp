#include <iostream>
#include <vector>
#include "IGraph.hpp"

class ListGraph : public IGraph {
 public:
    explicit ListGraph(int size);
    ~ListGraph() override;

    void addEdge(int from, int to) override;
    int verticesCount() const override;
    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

 private:
    std::vector< std::vector<int>> graph;
    int vertices_count;
};

