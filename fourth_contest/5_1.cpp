// https://contest.yandex.ru/contest/35212/problems/5_1/
// ID - 66196268	

/* Дано невзвешенное дерево. 
Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины. 
Для каждой вершины определите расстояние до самой удаленной от нее вершины.
Время работы должно быть O(n). */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class graph {
private:
	vector<vector<int>> gr;
	int size;

public:
	void resize(int& size) {
		gr.resize(size, vector<int>());
		this->size = size;
	}

	void add_edge(int from, int to) {
		gr[from].push_back(to);
		gr[to].push_back(from);
	}

	friend istream& operator>> (istream& in, graph& gr) {
		int from, to;
		in >> from >> to;
		gr.add_edge(from, to);
		return in;
	}

	void DFS(int prev, vector<int>& distances, int parent = -1, int depth = 0) {
		distances[prev] = depth;
		for (auto vertex : gr[prev]) {
			if (vertex != parent) {
				DFS(vertex, distances, prev, depth + 1);
			}
		}
	}

};

void solve() {
	int size;
	cin >> size;
	graph gr;
	gr.resize(size);
	for (int i = 0; i < size - 1; i++) {
		cin >> gr;
	}

	vector<int> distance_to_diam1(size, 1e9);
	vector<int> distance_to_diam2(size, 1e9);
	int diam1 = 0, diam2 = 0;

	gr.DFS(0, distance_to_diam1);
	for (int i = 0; i < size; i++) {
		if (distance_to_diam1[diam1] < distance_to_diam1[i]) {
			diam1 = i;
		}
	}
	gr.DFS(diam1, distance_to_diam1);
	for (int i = 0; i < size; i++) {
		if (distance_to_diam1.at(diam2) < distance_to_diam1.at(i)) {
			diam2 = i;
		}
	}
	gr.DFS(diam2, distance_to_diam2);
	for (int i = 0; i < size; i++) {
		cout << max(distance_to_diam1.at(i), distance_to_diam2.at(i)) << "\n";
	}
}

int main() {
	solve();
	return 0;
}
