// https://contest.yandex.ru/contest/36361/problems/4/
// ID - 67728738	

/*Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.*/

#include <iostream>
#include <queue>
#include <list>

struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int, int, int) = 0;

	virtual int VerticesCount() const = 0;

	virtual void FindAllAdjacentIn(int, std::vector<std::pair<int, int>>&) const = 0;
	virtual void FindAllAdjacentOut(int, std::vector<std::pair<int, int>>&) const = 0;
};

class ListGraph : public IGraph {
private:
	int size;
	std::vector<std::list<std::pair<int, int>>> DirectList, ReverseList;

public:
	explicit ListGraph(int _size);

	explicit ListGraph(const IGraph* graph);

	void AddEdge(int from, int to, int weight) override;

	int VerticesCount() const override;

	void FindAllAdjacentIn(int vertex, std::vector<std::pair<int, int>>& vertices) const override;
	void FindAllAdjacentOut(int vertex, std::vector<std::pair<int, int>>& vertices) const override;

	~ListGraph() {}
};

ListGraph::ListGraph(int _size) : size(_size) {
	DirectList.resize(size);
	ReverseList.resize(size);
}

ListGraph::ListGraph(const IGraph* graph) : size(graph->VerticesCount()) {
	DirectList.resize(size);
	ReverseList.resize(size);
	for (int i = 0; i < size; i++) {
		std::vector<std::pair<int, int>> iter;
		graph->FindAllAdjacentOut(i, iter);
		for (std::pair<int, int> j : iter)
			AddEdge(i, j.first, j.second);
	}
}

void ListGraph::AddEdge(int from, int to, int weight) {
	DirectList[to].push_back({ from, weight });
	DirectList[from].push_back({ to, weight });
}

int ListGraph::VerticesCount() const {
	return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<std::pair<int, int>>& vertices) const {
	for (auto& i : ReverseList[vertex]) {
		vertices.push_back(i);
	}
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<std::pair<int, int>>& vertices) const {
	for (auto& i : DirectList[vertex]) {
		vertices.push_back(i);
	}
}

struct comp {
	bool operator()(std::pair<int, int>& from, std::pair<int, int>& to) const {
		return from.second > to.second;
	}
};

int Dijkstra(IGraph* graph, int from, int to) {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comp> q;
	std::vector<bool> is_used(graph->VerticesCount(), false);
	std::vector<int> dist(graph->VerticesCount(), 0);
	q.push({ from, 0 });
	while (!q.empty()) {
		std::pair<int, int> curr_vertex = q.top();
		q.pop();
		if (is_used[curr_vertex.first]) {
			continue;
		}
		is_used[curr_vertex.first] = true;
		dist[curr_vertex.first] = curr_vertex.second;
		std::vector<std::pair<int, int>> vertices;
		graph->FindAllAdjacentOut(curr_vertex.first, vertices);
		for (auto iter : vertices) {
			if (!is_used[iter.first]) {
				q.push({ iter.first, curr_vertex.second + iter.second });
			}
		}
	}
	return dist[to];
}

IGraph* read() {
	int n, m, from, to, weight;
	std::cin >> n >> m;
	IGraph* graph = new ListGraph(n);
	for (int i = 0; i < m; i++) {
		std::cin >> from >> to >> weight;
		graph->AddEdge(from, to, weight);
	}
	return graph;
}

void solve(IGraph* graph) {
	int start, finish;
	std::cin >> start >> finish;
	std::cout << Dijkstra(graph, start, finish);
}

int main() {
	IGraph* graph = read();
	solve(graph);
}
