//https://contest.yandex.ru/contest/29212/problems/5_2/
//54277182	

#include <iostream>
#include <stack>
#include <string>
//5_2
using namespace std;

void solve(string input, string res) {
	stack<char> st;
	int it = 0;
	st.push(input[it++]);

	for (auto sym : res) {
		//если стек пустой и можно что-то положить туда, то кладем
		if (st.empty() && it < input.size()) {
			st.push(input[it++]);
		}
		//если последовательности разной длины, программа завершит работу
		if (st.empty() && it == input.size()) {
			cout << "NO";
			return;
		}
		//пока есть что класть и наш верхний элемент не равен нужному, кладем
		while (st.top() != sym && it < input.size()) st.push(input[it++]);
		if (st.top() == sym) {
			st.pop();
			continue;
		}
		cout << "NO";
		return;
	}

	cout << "YES";
}

int main() {
	string input, res;
	cin >> input >> res;

	solve(input, res);

	return 0;
}
