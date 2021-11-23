// 59009905 - ID
// https://contest.yandex.ru/contest/30914/problems/5_4/

#include <algorithm>
#include <iostream>

using namespace std;

const int LAST_POS = 63;

void read_arr(unsigned long long* arr, int size) {
	for (size_t i = 0; i < size; i++) {
		cin >> arr[i];
	}
}

void print_arr(unsigned long long* arr, int size) {
	for (size_t i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
}

bool digit(unsigned long long num, int pos) {
	return (num >> pos) & 1;
}

void _MSD(unsigned long long* arr, int left, int right, int pos) {
	if (pos < 0) return;
	if (left >= right) return;

	int i = left, j = right;
	while (i < j) {

		for (;!digit(arr[i], pos) && (i < j); i++) {}

		for (;digit(arr[j], pos) && (j > i); j--) {}

		swap(arr[i], arr[j]);
	}

	if (!digit(arr[right], pos)) j++;

	_MSD(arr, left, j - 1, pos - 1);
	_MSD(arr, j, right, pos - 1);
}

void MSD(unsigned long long* arr, int n) {
	_MSD(arr, 0, n - 1, LAST_POS);
}

int main() {
	int n;
	cin >> n;

	unsigned long long* arr = new unsigned long long[n];
	read_arr(arr, n);

	MSD(arr, n);

	print_arr(arr, n);

	return 0;
}
