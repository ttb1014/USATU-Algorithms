#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int _size) : matrix(size), size(_size) {
	for (auto &iter : matrix)
		iter = std::vector<bool>(size, false);
}

MatrixGraph::MatrixGraph(const IGraph* graph) : size(graph->VerticesCount()), matrix(graph->VerticesCount()) {
	for (auto &iter : matrix)
		iter = std::vector<bool>(size, false);

	for (int i = 0; i < size; i++) {
		std::vector<int> iter;
		graph->FindAllAdjacentIn(i, iter);
		for (int j : iter)
			AddEdge(i, j);
	}
}

void MatrixGraph::AddEdge(int from, int to) {
	matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
	return size;
}

void MatrixGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	for (int i = 0; i < size; i++) {
		if (matrix[vertex][i])
			vertices.push_back(i);
	}
}

void MatrixGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	for (int i = 0; i < size; i++) {
		if (matrix[i][vertex])
			vertices.push_back(i);
	}
}