// 58784521 - ID(TL error)
// без сортировки вставками проходило все тесты
// https://contest.yandex.ru/contest/30914/problems/?success=57652794#194179/2016_10_05/4DrsObKEog - link

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void read_vector(vector<pair<vector<int>, int>>& arr, int n) {
	int iter = 0;
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

template<typename T>
void insertion_sort(vector<T>& arr, bool compare(T t1, T t2)) {

	for (size_t i = 1; i < arr.size(); i++) {
		int j = i - 1;

		for (; j >= 0 && !compare(arr[j], arr[j + 1]); j--) {
			swap(arr[j], arr[j + 1]);
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<pair<vector<int>, int>> boxes(n);
	read_vector(boxes, n);

	insertion_sort<pair<vector<int>, int>>(boxes, [](pair<vector<int>, int> x, pair<vector<int>, int> y) {
		return (x.first[0] < y.first[0] && (x.first[1] < y.first[1] || x.first[2] < y.first[2]) ||
			(x.first[1] < y.first[1] && (x.first[2] < y.first[2] || x.first[0] < y.first[0])) ||
			(x.first[2] < y.first[2] && (x.first[1] < y.first[1] || x.first[0] < y.first[0]))
			);
		});

	print_ans(boxes, n);

	return 0;
}
