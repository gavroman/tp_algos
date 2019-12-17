#ifndef INCLUDE_IGRAPH_
#define INCLUDE_IGRAPH_

class IGraph {
 public:
    virtual ~IGraph() {}
    virtual void addEdge(int from, int to) = 0;

    virtual int verticesCount() const  = 0;

    virtual std::vector<int> getNextVertices(int vertex) const = 0;
    virtual std::vector<int> getPrevVertices(int vertex) const = 0;
};

#endif
