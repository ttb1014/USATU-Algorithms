//https://contest.yandex.ru/contest/29212/problems/3_1/
//53833112

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
//3_1
using namespace std;

int myBinarySearch(vector<int> &arr, int length, int element) {
	int start = 0;
	int end = length;
	int mid;

	while (start < end) {
		mid = (start + end) / 2;
		if (arr[mid] < element) {
			start = ++mid;
			continue;
		}
		end = mid;
	}

	return((start == length || arr[start] < element) ? arr.size() : start); //edited
}

void readArr(vector <int>& arr) {
	for (auto& el : arr) {
		cin >> el;
	}
}

void solve(int &n, int &m) {
	vector<int> arrA(n);
	vector<int> arrB(m);
	readArr(arrA);
	readArr(arrB);

	for (auto& b : arrB) {
		cout << myBinarySearch(arrA, arrA.size(), b) << " ";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	solve(n, m);

	return 0;
}
