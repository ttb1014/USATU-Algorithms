#include "ListGraph.h"

ListGraph::ListGraph(int _size) : size(_size) {
	DirectList.resize(size);
	ReverseList.resize(size);
}

ListGraph::ListGraph(const IGraph* graph) : size(graph->VerticesCount()) {
	DirectList.resize(size);
	ReverseList.resize(size);
	for (int i = 0; i < size; i++) {
		std::vector<int> iter;
		graph->FindAllAdjacentIn(i, iter);
		for (int j : iter)
			AddEdge(i, j);
	}
}

void ListGraph::AddEdge(int from, int to) {
	if (!DirectList[to].empty())
		for (int i : DirectList[to])
			if (i == from)
				return;
	DirectList[to].push_back(from);
	ReverseList[from].push_back(to);
}

int ListGraph::VerticesCount() const {
	return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	for (auto& i : ReverseList[vertex]) {
		vertices.push_back(i);
	}
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	for (auto& i : DirectList[vertex]) {
		vertices.push_back(i);
	}
}
