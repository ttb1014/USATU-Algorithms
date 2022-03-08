// https://contest.yandex.ru/contest/35212/problems/4_2/
// 65852330

/*Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду. 
Каждый вышележащий слой пирамиды должен быть не больше нижележащего.*/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void print(vector<vector<unsigned long long>> &arr) {
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr.size(); j++) {
			cout << left << setw(4) << arr[i][j];
		}
		cout << endl;
	}
}

int main() {
	unsigned long long n;
	cin >> n;
	vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(n + 1));
	//dp[i][j] - кол-во различных пирамид из i кубиков с максимальной высотой j
	//dp[i][0] = 0, dp[i][1] = 1 - база
	for (size_t i = 0; i <= n; i++) {
		dp[i][0] = 0;
		dp[i][1] = 1;
	}
	for (size_t i = 0; i <= n; i++) {
		for (size_t j = 2; j <= n; j++) {
			dp[i][j] = dp[i][j - 1];
			if (i > j - 1 && j >= 1)
				dp[i][j] += dp[i - j][j];
		}
	}
	cout << dp[n][n];
	return 0;
}
