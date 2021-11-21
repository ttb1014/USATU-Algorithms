// 58792169 - ID
// https://contest.yandex.ru/contest/30914/problems/1_1/ - link

#include <iostream>

using namespace std;

void read_arr(int** arr, int n) {
	int iter = 0;
	for (size_t i = 0; i < n; i++) {
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
		arr[i][3] = iter++;
	}
}

void print_arr(int** arr, int n) {
	for (size_t i = 0; i < n; i++) {
		cout << arr[i][3] << " ";
	}
}

// сравнение по двум сторонам
bool compare(int case1[3], int case2[3]) { 
	if (case1[0] > case2[0] && (case1[1] > case2[1]) || (case1[2] > case2[2])) return true;
	if (case1[1] > case2[1] && (case1[0] > case2[0]) || (case1[2] > case2[2])) return true;
	if (case1[2] > case2[2] && (case1[0] > case2[0]) || (case1[1] > case2[1])) return true;
	return false;
}

void insertion_sort(int** arr, int n) {
	for (int i = 1; i < n; i++) {
		int j = i - 1;

		for (; j >= 0 && compare(arr[j], arr[j + 1]); j--) {
			swap(arr[j], arr[j + 1]);
		}
	}
}

int main() {
	int n; 
	cin >> n;
	int** arr = new int*[n];
	for (size_t i = 0; i < n; i++) {
		arr[i] = new int[4];
	}

	read_arr(arr, n);

	insertion_sort(arr, n);

	print_arr(arr, n);
		
	return 0;
}
