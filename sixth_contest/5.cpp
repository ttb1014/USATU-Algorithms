// https://contest.yandex.ru/contest/37787/problems/5/
// 68668651	

/* Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.

Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n). */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int ALPHABET = 128;

void build_suffix_array(string& s, vector<int>& suffix_array, vector<int>& lcp) {
	s.push_back('\0');
	int size = s.size();
	suffix_array.resize(size);
	vector<int> cnt(ALPHABET);
	vector<vector<int>> classes(1, vector<int>(size));
	for (int i = 0; i < size; i++) {
		cnt[s[i]]++;
	}
	for (int i = 1; i < ALPHABET; i++) {
		cnt[i] += cnt[i - 1];
	}
	for (int i = 0; i < size; i++) {
		suffix_array[--cnt[s[i]]] = i;
	}
	classes[0][suffix_array[0]] = 0;
	int classes_num = 1;
	for (int i = 1; i < size; i++) {
		if (s[suffix_array[i]] != s[suffix_array[i - 1]])  ++classes_num;
		classes[0][suffix_array[i]] = classes_num - 1;
	}
	vector<int> suffix_array_new(size);
	for (int h = 0; (1 << h) < size; h++) {
		classes.push_back(vector<int>(size));
		for (int i = 0; i < size; i++) {
			suffix_array_new[i] = suffix_array[i] - (1 << h);
			if (suffix_array_new[i] < 0) suffix_array_new[i] += size;
		}
		cnt.clear();
		cnt.resize(classes_num);
		for (int i = 0; i < size; i++) {
			cnt[classes[h][suffix_array_new[i]]]++;
		}
		for (int i = 1; i < classes_num; i++) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = size - 1; i >= 0; i--) {
			suffix_array[--cnt[classes[h][suffix_array_new[i]]]] = suffix_array_new[i];
		}
		classes[h + 1][suffix_array[0]] = 0;
		classes_num = 1;
		for (int i = 1; i < size; i++) {
			int mid1 = (suffix_array[i] + (1 << h)) % size, mid2 = (suffix_array[i - 1] + (1 << h)) % size;
			if (classes[h][suffix_array[i]] != classes[h][suffix_array[i - 1]] || classes[h][mid1] != classes[h][mid2])
				classes_num++;
			classes[h + 1][suffix_array[i]] = classes_num - 1;
		}
	}
	lcp.resize(size - 2);
	for (int i = 1; i < size - 1; i++) {
		int first = suffix_array[i];
		int second = suffix_array[i + 1];
		for (int j = classes.size() - 1; j >= 0; j--) {
			if (classes[j][first] == classes[j][second]) {
				lcp[i - 1] += 1 << j;
				first += 1 << j;
				second += 1 << j;
			}
		}
	}
}

void solve() {
	string s;
	cin >> s;
	vector<int> suffix_array, lcp;
	build_suffix_array(s, suffix_array, lcp);
	int result = 0;
	int size = s.size();
	for (int i = 0; i < size; i++) {
		result += size - 1 - suffix_array[i];
	}
	for (int i = 0; i < size - 2; i++) {
		result -= lcp[i];
	}
	cout << result;
}

int main() {
	solve();
	return 0;
}
