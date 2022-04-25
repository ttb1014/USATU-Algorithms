// https://contest.yandex.ru/contest/36361/problems/5/
// ID - 67775452

/*Необходимо написать торгового советника для поиска арбитража.
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02
Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4*/

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

template <typename T>
struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int, int, T) = 0;

	virtual int VerticesCount() const = 0;

	virtual void FindAllAdjacentOut(int vertex, std::vector<pair<int, T>>& vertices) const = 0;
};

template <typename T>
class MatrixGraph : public IGraph<T> {
public:
	int size;
	std::vector<std::vector<T>> matrix;

public:
	explicit MatrixGraph(int _size);

	explicit MatrixGraph(const IGraph<T>* graph);

	void AddEdge(int from, int to, T weight) override;

	int VerticesCount() const override;

	void FindAllAdjacentOut(int vertex, std::vector<pair<int, T>>& vertices) const override;

	~MatrixGraph() {};
};

template <typename T>
MatrixGraph<T>::MatrixGraph(int _size) : matrix(size), size(_size) {
	for (auto& iter : matrix)
		iter = std::vector<T>(size);
}

template <typename T>
MatrixGraph<T>::MatrixGraph(const IGraph<T>* graph) : size(graph->VerticesCount()), matrix(graph->VerticesCount()) {
	for (auto& iter : matrix)
		iter = std::vector<T>(size);

	for (int i = 0; i < size; i++) {
		std::vector<pair<int, T>> iter;
		graph->FindAllAdjacentOut(i, iter);
		for (pair<int, T> j : iter)
			AddEdge(i, j.first, j.second);
	}
}

template <typename T>
void MatrixGraph<T>::AddEdge(int from, int to, T weight) {
	matrix[from][to] = weight;
}

template <typename T>
int MatrixGraph<T>::VerticesCount() const {
	return size;
}

template <typename T>
void MatrixGraph<T>::FindAllAdjacentOut(int vertex, std::vector<pair<int, T>>& vertices) const {
	for (int i = 0; i < size; i++) {
		if (matrix[vertex][i] != -1 && vertex != i)
			vertices.push_back({ i, matrix[vertex][i] });
	}
}

template <typename T>
IGraph<T>* read() {
	int n;
	T weight;
	cin >> n;
	IGraph<double>* graph = new MatrixGraph<T>(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				cin >> weight;
				graph->AddEdge(i, j, weight);
			}
		}
	}
	return graph;
}

template<typename T>
struct comp {
	bool operator() (pair<int, T>& from, pair<int, T>& to) {
		return from.second < to.second;
	}
};

template <typename T>
struct solution {
	bool trade(IGraph<T>* graph) {
		for (int vertex = 0; vertex < graph->VerticesCount(); vertex++) {
			priority_queue<std::pair<int, T>, vector<std::pair<int, T>>, comp<T>> arbitrage;
			vector<T> coef(graph->VerticesCount(), 1);
			arbitrage.push({ vertex, 1 });
			while (!arbitrage.empty()) {
				pair<int, T> top = arbitrage.top();
				arbitrage.pop();
				if (vertex == top.first && coef[vertex] > 1)
					return true;
				vector<pair<int, T>> vertices;
				graph->FindAllAdjacentOut(top.first, vertices);
				for (auto& v : vertices) {
					T new_coef = coef[top.first] * v.second;
					if (new_coef > coef[vertex]) {
						coef[v.first] = new_coef;
						arbitrage.push({ v.first, new_coef });
					}
				}
			}
		}
		return false;
	}
	void solve() {
		IGraph<double>* graph = read<double>();
		cout << (trade(graph) ? "YES" : "NO");
	}
};

int main() {
	solution<double> sol;
	sol.solve();
	return 0;
}
