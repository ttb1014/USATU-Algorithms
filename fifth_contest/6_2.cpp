// https://contest.yandex.ru/contest/36361/problems/6/
// ID - 67700518

/* Найти в связном графе остовное дерево минимального весе. Использовать алгортим Крускала */

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
	int from, to, cost;
	bool operator< (Edge a) {
		return this->cost < a.cost;
	}
};

class DSU {
private:
	vector<int> dsu, len;

public:
	DSU(int size);
	int dsu_get(int v);
	void dsu_unite(int a, int b);
};

DSU::DSU(int size) {
	dsu.resize(size);
	len.resize(size);
	for (int i = 0; i < size; i++) {
		dsu[i] = i;
		len[i] = 1;
	}
}

int DSU::dsu_get(int v) {
	if (v == dsu[v]) {
		return v;
	}
	else {
		return dsu[v] = dsu_get(dsu[v]);
	}
}

void DSU::dsu_unite(int a, int b) {
	a = dsu_get(a);
	b = dsu_get(b);
	if (len[b] > len[a]) {
		dsu[b] = a;
	}
	else {
		dsu[a] = b;
	}
	if (len[b] == len[a]) {
		len[b]++;
		if (a != b)
			dsu[a] = b;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<Edge> edges;
	int from, to, cost;
	for (size_t i = 0; i < m; i++) {
		cin >> from >> to >> cost;
		Edge edge;
		edge.cost = cost;
		edge.from = from;
		edge.to = to;
		edges.push_back(edge);
	}

	int ans = 0;
	int min_cost = 0;
	sort(edges.begin(), edges.end());
	DSU dsu(n + 1);
	for (int i = 0; i < m; ++i) {
		from = edges[i].from;
		to = edges[i].to;
		cost = edges[i].cost;
		if (dsu.dsu_get(from) != dsu.dsu_get(to)) {
			min_cost += cost;
			ans += cost;
			dsu.dsu_unite(from, to);
		}
	}
	cout << ans;
}
