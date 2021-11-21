// 58812537 - ID(TL)
// https://contest.yandex.ru/contest/30914/problems/3/ - link

#include <iostream>

using namespace std;

void find_median(int* arr, int i1, int i2, int i3) {
	if ((arr[i1] > arr[i2] && arr[i3] > arr[i1]) ||
		arr[i1] < arr[i2] && arr[i1] > arr[i3])
		swap(arr[i1], arr[i3]);
	else if ((arr[i1] > arr[i2] && arr[i2] > arr[i3]) ||
		arr[i1] < arr[i2] && arr[i2] < arr[i3])
		swap(arr[i2], arr[i3]);
}

int partition(int* arr, int left, int right) {
	if (right - left <= 1) return left;

	int middle = (left + right) / 2;

	find_median(arr, left, middle, right - 1);

	int pivot = arr[right - 1];

	int i = right - 2, j = right - 2;
	while (j >= 0) {
		if (arr[j] > pivot) {
			swap(arr[i], arr[j]);
			i--;
		}
		j--;
	}
	swap(arr[++i], arr[right - 1]);

	return i;
}

void solve(int* arr, int len, int k) {
	int left = 0;
	int right = len;

	while (true) {
		int part = partition(arr, left, right);
		if (part == k) {
			cout << arr[part];
			return;
		}
		if (part > k) right = part;
		if (part < k) left = part + 1;
	}
}

void read_arr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k;
	cin >> n >> k;

	int* arr = new int[n];

	read_arr(arr, n);

	solve(arr, n, k);

	return 0;
}
