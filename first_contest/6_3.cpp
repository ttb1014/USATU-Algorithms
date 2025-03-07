//https://contest.yandex.ru/contest/29212/problems/6_3/
//54278319

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <queue>
//6_3
using namespace std;

int manage_deadends(int arr, int dep, priority_queue<int,vector<int>, greater<int>> &deadends) {
	//если у нас будет свободный тупик к моменту прибытия(arr)
	if (deadends.top() < arr) {
		deadends.pop();
		deadends.push(dep);
		return deadends.size();
	}
	//все места заняты
	deadends.push(dep);
	return deadends.size();
}

void solve(int n) {
	int arr, dep, ans;
	priority_queue<int,vector<int>,greater<int>> deadends;

	cin >> arr >> dep;
	deadends.push(dep);
	ans = 1;

	for (int i = 1; i < n; i++) {
		cin >> arr >> dep;
		ans = max(manage_deadends(arr, dep, deadends), ans);
	}

	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	solve(n);

	return 0;
}
