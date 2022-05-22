// https://contest.yandex.ru/contest/37787/problems/2_2/
// ID - 68536056

/* Найти лексикографически-минимальную строку, построенную по z-функции, в алфавите a-z. */

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

string to_string(vector<int>& z_val) {
	if (z_val.empty())
		return "";

	string ans = "a";
	int iter = 1;
	int prefix_iter = 0;
	char next_sym;
	int prefix_size;
	set<char> used_syms;

	while (iter < z_val.size()) {
		if (z_val[iter] == 0) {
			next_sym = 'b';
			while (used_syms.find(next_sym) != used_syms.end()) {
				next_sym++;
			}

			ans += next_sym;
			used_syms.clear();
			iter++;
			continue;
		}
		prefix_size = z_val[iter];
		prefix_iter = 0;
		while (prefix_size > 0) {
			if (z_val[iter] > prefix_size) {
				prefix_size = z_val[iter];
				prefix_iter = 0;
				used_syms.insert(ans[z_val[iter]]);
			}
			if (z_val[iter] == prefix_size) {
				used_syms.insert(ans[z_val[iter]]);
			}

			ans += ans[prefix_iter++];
			prefix_size--;
			iter++;
		}
	}
	return ans;
}

void read(vector<int>& arr) {
	int num;
	while (cin >> num) {
		arr.push_back(num);
	}
}

int main() {
	vector<int> z_val;
	read(z_val);
	cout << to_string(z_val);
}
