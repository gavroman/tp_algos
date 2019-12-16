#include <vector>
#include "IGraph.hpp"

class MatrixGraph : public IGraph {
 public:
    explicit MatrixGraph(int size);
    MatrixGraph(const IGraph& g);
    ~MatrixGraph() override;

    void addEdge(int from, int to) override;
    int verticesCount() const override;
    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

 private:
    std::vector<std::vector<bool>> graph;
    int vertices_count;
};
