#include <vector>
#include "IGraph.hpp"

struct Edge {
    int from;
    int to;
    explicit Edge() : from(0), to(0) {}
    Edge(int vertexA, int vertexB) : from(vertexA), to(vertexB) {}
};

class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(int size);
    ~ArcGraph() override;

    void addEdge(int from, int to) override;
    int verticesCount() const override;
    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;


 private:
    std::vector<Edge> graph;
    int vertices_count;
};
