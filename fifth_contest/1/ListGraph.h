#pragma once

#include "IGraph.h"
#include <list>
#include <vector>

class ListGraph : public IGraph {
	int size;
	std::vector<std::list<int>> DirectList, ReverseList;

public:
	explicit ListGraph(int _size);

	explicit ListGraph(const IGraph* graph);

	void AddEdge(int from, int to) override;

	int VerticesCount() const override;

	void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
	void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

	~ListGraph() {};
};