// https://contest.yandex.ru/contest/37787/problems/1/
// ID - 68519237

/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
p ≤ 30000, n ≤ 300000. */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void z_func(vector<int>& z_val, int& l, int& r, string& temp) {
	for (int i = 1; i < temp.size(); ++i) {
		z_val[i] = max(0, min(r - i, z_val[i - l]));
		while (i + z_val[i] < temp.size() && temp[z_val[i]] == temp[i + z_val[i]]) {
			z_val[i]++;
		}
		if (i + z_val[i] > r) {
			l = i;
			r = i + z_val[i];
		}
	}
}

void z_next(vector<int>& z_val, int& l, int& r, int& i, string& temp, string& text) {
	int z_next = max(0, min(r - i, z_val[i - l]));
	while (z_next < temp.size() && temp[z_next] == text[i + z_next]) {
		z_next++;
	}
	if (i + z_next > r) {
		l = i;
		r = i + z_next;
	}
	if (z_next == temp.size() - 1) {
		cout << i << " ";
	}
}

int main() {
	string temp, text;
	cin >> temp >> text;
	temp += "$";

	vector<int> z_val(temp.size());
	z_val[0] = 0;
	int l = 0, r = 0;
	z_func(z_val, l, r, temp);

	l = 0, r = 0;
	for (int i = 0; i < text.size(); i++) {
		z_next(z_val, l, r, i, temp, text);
	}
}
