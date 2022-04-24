// https://contest.yandex.ru/contest/36361/problems/3/
// ID - 67728185

/*Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const = 0;
	virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const = 0;
};

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

void DFS(IGraph* graph, int vertex, std::vector<bool>& used, std::vector<int>& res) {
	used[vertex] = true;
	std::vector<int> vertices;
	graph->FindAllAdjacentIn(vertex, vertices);
	for (auto to : vertices) {
		if (!used[to]) {
			DFS(graph, to, used, res);
		}
	}
	res.push_back(vertex);
}

std::vector<int> top_sort(IGraph* graph) {
	std::vector<int> res(0);
	std::vector<bool> used(graph->VerticesCount(), false);
	for (int i = 0; i < graph->VerticesCount(); i++) {
		if (!used[i]) {
			DFS(graph, i, used, res);
		}
	}
	return res;
}

void reversed_graph_DFS(IGraph* graph, int vertex, std::vector<int>& curr_component, std::vector<bool>& used) {
	curr_component.push_back(vertex);
	used[vertex] = true;
	std::vector<int> vertices;
	graph->FindAllAdjacentOut(vertex, vertices);
	for (auto to : vertices) {
		if (!used[to]) {
			reversed_graph_DFS(graph, to, curr_component, used);
		}
	}
}

std::vector<std::vector<int>> _kosarajyu(IGraph* graph, std::vector<int> sorted_edges) {
	std::vector<std::vector<int>> components;
	std::vector<bool> used(graph->VerticesCount());
	std::reverse(sorted_edges.begin(), sorted_edges.end());
	for (int vertex : sorted_edges) {
		if (!used[vertex]) {
			components.push_back(std::vector<int>(0));
			reversed_graph_DFS(graph, vertex, components.back(), used);
		}
	}
	return components;
}

std::vector<std::vector<int>> kosarajyu(IGraph* graph) {
	std::vector<int> sorted_edges = top_sort(graph);
	return _kosarajyu(graph, sorted_edges);
}

int count_missing_edges(IGraph* g, std::vector<std::vector<int>> components) {
	if (components.size() == 1) 
		return 0;
	std::vector<bool> any_out_edges(g->VerticesCount(), false); 
	std::vector<bool> any_in_edges(g->VerticesCount(), false);
	for (auto component : components) {
		std::vector<bool> in_cur_comp(g->VerticesCount());
		for (int vertex : component) {
			in_cur_comp[vertex] = true;
		}
		for (int vertex : component) {
			std::vector<int> to;
			g->FindAllAdjacentOut(vertex, to);
			std::vector<int> from;
			g->FindAllAdjacentIn(vertex, from);
			for (int _to : to) {
				if (!in_cur_comp[_to]) {
					any_out_edges[_to] = true;
				}
			}
			for (int _from : from) {
				if (!in_cur_comp[_from]) {
					any_in_edges[_from] = true;
				}
			}
		}
	}
	int missing_out = 0;
	int missing_in = 0;
	for (auto component : components) {
		bool has_out_edges = false;
		bool has_in_edges = false;
		for (int vertex : component) {
			if (any_out_edges[vertex]) {
				has_out_edges = true;
			}
			if (any_in_edges[vertex]) {
				has_in_edges = true;
			}
		}
		if (!has_out_edges) {
			missing_out++;
		}
		if (!has_in_edges) {
			missing_in++;
		}
	}
	return std::max(missing_in, missing_out);
}

IGraph* read() {
	int n, m;
	std::cin >> n >> m;
	IGraph* graph = new ListGraph(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		graph->AddEdge(x - 1, y - 1);
	}
	return graph;
}

int main() {
	IGraph* graph = read();
	std::vector<std::vector<int>> components = kosarajyu(graph);
	std::cout << count_missing_edges(graph, components);
	return 0;
}
