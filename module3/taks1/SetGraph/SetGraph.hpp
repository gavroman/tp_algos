#include <vector>
#include <set>
#include "IGraph.hpp"

class SetGraph : public IGraph {
 public:
    explicit SetGraph(int size);
    SetGraph(const IGraph& g);
    ~SetGraph() override;

    void addEdge(int from, int to) override;
    int verticesCount() const override;
    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;


 private:
    std::vector<std::set<int>> graph;
    int vertices_count;
};
