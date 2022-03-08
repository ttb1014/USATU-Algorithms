// https://contest.yandex.ru/contest/35212/problems/2_2/
// ID - 65850370

/*В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. 
Ваша задача определить максимальное количество заявок, которое может быть удовлетворено. Число заявок ≤ 100000.*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct meeting {
	unsigned int start_time;
	unsigned int end_time;
	meeting(unsigned int& _start_time, unsigned int& _end_time) : start_time(_start_time),
		end_time(_end_time) {};
};

void read_timeline(vector<meeting>& timeline) {
	//ifstream fin("out.txt");
	unsigned int start, end;
	while (true) {
		if (cin.fail()) return;
		cin >> start >> end;
		timeline.push_back(meeting(start, end));
	}
}

void print_timeline(vector<meeting>& timeline) {
	for (auto& m : timeline) {
		cout << m.start_time << " -> " << m.end_time << "\n";
	}
}

int main() {
	vector<meeting> timeline;
	read_timeline(timeline);
	sort(timeline.begin(), timeline.end(), [](meeting& m1, meeting& m2) {
		if (m1.end_time == m2.end_time) return m1.start_time > m2.start_time;
		return m1.end_time < m2.end_time;
		});
	print_timeline(timeline);
	vector<unsigned int> dp(timeline[timeline.size() - 1].end_time + 1, 0);
	unsigned int current_time = timeline[0].end_time;
	dp[current_time] = 1;
	for (auto& m : timeline) {
		if (current_time <= m.start_time) {
			dp[m.end_time] = dp[current_time] + 1;
			current_time = m.end_time;
		}
	}
	unsigned int max = 0;
	for (auto& a : dp) {
		if (max < a) max = a;
	}
	cout << max << endl;
	return 0;
}
