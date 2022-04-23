// https://contest.yandex.ru/contest/36361/problems/2.3/
// ID - 67403474

/*Дан невзвешенный неориентированный граф. Определить, является ли он двудольным. Требуемая сложность O(V+E).*/


#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct vertex {
	int depth;
	int anc;
};

class graph {
private:
	vector<vector<int>> g;
	int size;

public:
	graph(int n) {
		size = n;
		g.resize(n);
	}

	void add_edge(int from, int to) {
		g[from].push_back(to);
		g[to].push_back(from);
	}

	bool is_bipartite() {
		int cycle_length;
		vector<vertex> vertices;
		for (int i = 0; i < size; i++) {
			cycle_length = BFS(vertices, i);
			if (cycle_length % 2 != 0) return false;
		}
		return true;
	}

	int BFS(vector<vertex> vertices, int v) {
		int res = 0;
		queue<int> q;
		vertices.resize(size, { (int)1e9, -1 });
		vertices[v].depth = 0;
		q.push(v);
		while (!q.empty()) {
			int curr_v = q.front();
			q.pop();
			for (int child : g[curr_v]) {
				if (vertices[child].depth == (int)1e9) {
					vertices[child].depth = 1 + vertices[curr_v].depth;
					vertices[child].anc = curr_v;
					q.push(child);
				}
				else if (vertices[curr_v].anc != child && vertices[child].anc != curr_v) {
					if (res == 0) res = vertices[curr_v].depth + vertices[child].depth + 1;
					else
						res = min(res, vertices[curr_v].depth + vertices[child].depth + 1);
				}
			}
		}
		return res;
	}
};

int main() {
	int n, m, in, out;
	cin >> n >> m;
	graph gr(n);
	for (int i = 0; i < m; i++) {
		cin >> in >> out;
		gr.add_edge(in, out);
	}
	cout << (gr.is_bipartite()?"YES":"NO");
	return 0;
}
