#pragma once

#include "IGraph.h"

class ArcGraph : public IGraph {
	int size;
	std::vector<std::pair<int, int>> arcs;

public:
	explicit ArcGraph(int _size);

	explicit ArcGraph(const IGraph* graph);

	void AddEdge(int from, int to) override;

	int VerticesCount() const override;

	void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
	void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

	~ArcGraph() {};
};