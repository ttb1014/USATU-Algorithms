#pragma once

#include "IGraph.h"

class MatrixGraph : public IGraph {
private:
    int size;
    std::vector<std::vector<bool>> matrix;

public:
    explicit MatrixGraph(int _size);

    explicit MatrixGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

    ~MatrixGraph() {};
};