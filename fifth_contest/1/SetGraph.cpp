#include "SetGraph.h"

SetGraph::SetGraph(int _size) : size(_size) {
	DirectSet.resize(size);
	ReverseSet.resize(size);
}

SetGraph::SetGraph(const IGraph* graph) : size(graph->VerticesCount()) {
	DirectSet.resize(size);
	ReverseSet.resize(size);
	for (int i = 0; i < size; i++) {
		std::vector<int> iter;
		graph->FindAllAdjacentIn(i, iter);
		for (int j : iter)
			AddEdge(i, j);
	}
}

void SetGraph::AddEdge(int from, int to) {
	DirectSet[from].insert(to);
	DirectSet[to].insert(from);
}

int SetGraph::VerticesCount() const {
	return size;
}

void SetGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	for (auto& i : ReverseSet[vertex]) {
		vertices.push_back(i);
	}
}

void SetGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	for (auto& i : DirectSet[vertex]) {
		vertices.push_back(i);
	}
}