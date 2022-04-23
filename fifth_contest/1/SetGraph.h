#pragma once

#include "IGraph.h"
#include <vector>
#include <unordered_set>

class SetGraph : public IGraph {
    int size;
    std::vector<std::unordered_set<int>>  DirectSet, ReverseSet;

public:
    explicit SetGraph(int _size);

    explicit SetGraph(const IGraph* graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
    void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

    ~SetGraph() {};
};