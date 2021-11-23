// 59007667 - ID
// https://contest.yandex.ru/contest/30914/problems/4_3/ - link


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int64_t merge(int* arr, int left, int right, int* buffer) {
	if (right == left) return 0;

	// last element of first subarray
	int middle = left + (right - left) / 2;

	int64_t inv1 = merge(arr, left, middle, buffer);
	int64_t inv2 = merge(arr, middle + 1, right, buffer);
	int64_t inv3 = 0;

	int i = left, j = middle + 1;
	int iter = 0;
	while (i <= middle && j <= right) {
		if (arr[i] <= arr[j]) {
			buffer[iter++] = arr[i++];
		}
		else {
			inv3 += (middle - i + 1);
			buffer[iter++] = arr[j++];
		}
	}

	while (i <= middle) {
		buffer[iter++] = arr[i++];
	}

	while (j <= right) {
		buffer[iter++] = arr[j++];
	}

	for (int i = left; i <= right; i++) {
		arr[i] = buffer[i - left];
	}

	return inv1 + inv2 + inv3;
}

int64_t merge_sort(int* arr, int size) {
	int* buffer = new int[size];
	int64_t inversions = merge(arr, 0, size - 1, buffer);
	return inversions;
}

int main() {
	int alloc = 100, size = 0;
	int* arr = (int*)malloc(alloc * sizeof(int));

	while (scanf("%d", &arr[size]) != -1) {
		size++;
		if (size > alloc) {
			alloc *= 2;
			arr = (int*)realloc(arr, alloc * sizeof(int));
		}
	}

	cout << merge_sort(arr, size);
	free(arr);
  
	return 0;
}
