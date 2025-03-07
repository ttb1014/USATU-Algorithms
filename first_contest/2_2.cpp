//https://contest.yandex.ru/contest/29212/problems/2_2/
//53832233	

#include <iostream>
#include <vector>
//2_2
using namespace std;

struct Coor {
	int x, y;

	Coor(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Triangle {
private:
	Coor* a, * b, * c;
	double area;

	void computeAreaOfTriangle() {
		area = 1 / 2.0 * abs(((b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y)));
	}

public:
	Triangle(Coor* a, Coor* b, Coor* c) {
		this->a = a;
		this->b = b;
		this->c = c;
		computeAreaOfTriangle();
	}

	double getArea() {
		return area;
	}
};

void readCoors(int n, vector<Coor>& arr) {
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		Coor* coor = new Coor(x, y);
		arr.push_back(*coor);
	}
}

void solve(int n) {
	vector <Coor> coors;
	readCoors(n, coors);

	double res = 0;

	for (int i = 2; i < n; i++) {
		Triangle* triangle = new Triangle(&coors[0], &coors[i - 1], &coors[i]);
		res += triangle->getArea();
	}

	cout << res;
}

int main() {
	int n;
	cin >> n;

	solve(n);

	return 0;
}
