// https://contest.yandex.ru/contest/37787/problems/3/
// ID - 68535847

/* Строка называется палиндромом, если она одинаково читается как слева направо, так и справа налево. Например, «abba» – палиндром, а «roman» – нет.

Для заданной строки s длины n (1 ≤ n ≤ 105) требуется подсчитать число пар (i, j), 1 ≤ i < j ≤ n, таких что подстрока s[i..j] является палиндромом. */

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

void odd_size_pal_init(string& s, vector<long long>& odd_pal) {
	long long l = 0, r = -1;
	for (long long i = 0; i < s.size(); ++i) {
		long long pals_count = (i > r) ? 1 : min(odd_pal[l + r - i], r - i + 1);
		while (i + pals_count < s.size() && i - pals_count >= 0 && s[i + pals_count] == s[i - pals_count])  ++pals_count;
		odd_pal[i] = pals_count;
		if (i + pals_count - 1 > r)
			l = i - pals_count + 1, r = i + pals_count - 1;
	}
}

void even_size_pal_init(string& s, vector<long long>& even_pal) {
	long long l = 0, r = -1;
	for (long long i = 0; i < s.size(); ++i) {
		long long pals_count = i > r ? 0 : min(even_pal[l + r - i + 1], r - i + 1);
		while (i + pals_count < s.size() && i - pals_count - 1 >= 0 && s[i + pals_count] == s[i - pals_count - 1])  ++pals_count;
		even_pal[i] = pals_count;
		if (i + pals_count - 1 > r)
			l = i - pals_count, r = i + pals_count - 1;
	}
}

void manaker(string& s, long long& counter) {
	vector<long long> odd_pal(s.size());
	odd_size_pal_init(s, odd_pal);
	vector<long long> even_pal(s.size());
	even_size_pal_init(s, even_pal);
	for (long long i = 0; i < s.size(); i++) {
		counter += odd_pal[i];
		counter += even_pal[i];
	}
	counter -= s.size();
}

void solve() {
	string s;
	cin >> s;

	long long counter = 0;
	manaker(s, counter);
	cout << counter;
}

int main() {
	solve();
	return 0;
}
