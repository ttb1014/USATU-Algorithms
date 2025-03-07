//https://contest.yandex.ru/contest/29212/problems/1_6/
//53261634	

#include <iostream>
#include <vector>
//1_6
using namespace std;

void print(vector<int>& arr) {
	for (auto& a : arr) {
		cout << a << " ";
	}
}

void solve(vector<int> &arr) {
	for (int i = 0; i < arr.size() / 2; i++) {
		swap(arr[arr.size() - i - 1], arr[i]);
	}

	print(arr);
}

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (auto& a : arr) {
		cin >> a;
	}

	solve(arr);

	return 0;
}
