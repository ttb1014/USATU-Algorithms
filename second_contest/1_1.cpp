// 57652794 - ID
// https://contest.yandex.ru/contest/30914/problems/?success=57652794#194179/2016_10_05/4DrsObKEog - link

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void read_vector(vector<pair<vector<int>, int>>& arr, int n) {
	int iter = 0, buffer;
	for (auto& a : arr) {
		a.first = vector<int>(3);
		for (auto& b : a.first) {
			cin >> b;
		}
		a.second = iter++;
	}
}

void print_ans(vector<pair<vector<int>, int>>& arr, int n) {
	for (auto& a : arr) {
		cout << a.second << " ";
	}
}

int main() {
	int n;
	cin >> n;
	vector<pair<vector<int>, int>> boxes(n);
	read_vector(boxes, n);

	sort(boxes.begin(), boxes.end(), [](pair<vector<int>, int> x, pair<vector<int>, int> y) {
		return (x.first[0] < y.first[0] && (x.first[1] < y.first[1] || x.first[2] < y.first[2]) ||
			(x.first[1] < y.first[1] && (x.first[2] < y.first[2] || x.first[0] < y.first[0])) ||
			(x.first[2] < y.first[2] && (x.first[1] < y.first[1] || x.first[0] < y.first[0]))
		);
	});

	print_ans(boxes, n);

	return 0;
}
