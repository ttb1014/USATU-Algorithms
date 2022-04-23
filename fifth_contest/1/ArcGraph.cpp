#include "ArcGraph.h"

ArcGraph::ArcGraph(int _size) : size(_size) {}

ArcGraph::ArcGraph(const IGraph* graph) : size(graph->VerticesCount()) {
	for (int i = 0; i < size; i++) {
		std::vector<int> iter;
		graph->FindAllAdjacentIn(i, iter);
		for (int j : iter)
			AddEdge(i, j);
	}
}

void ArcGraph::AddEdge(int from, int to) {
	for (auto& arc : arcs)
		if (arc.first == from && arc.second == to)
			return;
	arcs.push_back({ from, to });
}

int ArcGraph::VerticesCount() const {
	return size;
}

void ArcGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	for (auto& arc : arcs) {
		if (arc.first == vertex)
			vertices.push_back(arc.second);
	}
}

void ArcGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	for (auto& arc : arcs) {
		if (arc.second == vertex)
			vertices.push_back(arc.first);
	}
}
