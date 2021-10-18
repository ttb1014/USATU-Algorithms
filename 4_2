//https://contest.yandex.ru/contest/29212/problems/4_2/
//54276672

#include <iostream>

using namespace std;

const int START_BUFFER_SIZE = 2;

class MyDeque {
private:
	int head, tail, size, buffer_size;
	int* buffer;

	void doubleBufferSize() {
		int* new_buffer = new int[buffer_size * 2];
		for (int i = 0; i < buffer_size; i++) {
			new_buffer[i] = buffer[(head++) % buffer_size];
		}
		buffer = new_buffer;
		head = 0;
		tail = buffer_size;
		buffer_size *= 2;
	}

	void clear() {
		buffer_size = START_BUFFER_SIZE;
		buffer = new int[buffer_size];
		size = 0;
		head = 0;
		tail = 0;
	}

public:
	MyDeque() {
		buffer_size = START_BUFFER_SIZE;
		buffer = new int[buffer_size];
		size = 0;
		head = 0;
		tail = 0;
	}

	void push_back(int el) {
		if (size == buffer_size) {
			doubleBufferSize();
		}

		buffer[tail] = el;
		tail = (tail + 1) % buffer_size;
		size++;
	}

	int pop_back() {
		if (size == 0) return -1;
		if (size == 1) {
			int res_buffer = buffer[(tail + buffer_size - 1) % buffer_size];
			clear();
			return res_buffer;
		}
		int res_buffer = buffer[(tail + buffer_size - 1) % buffer_size];
		tail = (tail + buffer_size - 1) % buffer_size;
		size--;
		return res_buffer;
	}

	void push_front(int el) {
		if (size == buffer_size) {
			doubleBufferSize();
		}

		head = ((head + buffer_size - 1) % buffer_size);
		buffer[head] = el;
		size++;
	}

	int pop_front() {
		if (size == 0) return -1;
		if (size == 1) {
			int res_buffer = buffer[head];
			clear();
			return res_buffer;
		}
		int res_buffer = buffer[head];
		head = (head + 1) % buffer_size;
		size--;
		return res_buffer;
	}

	void print() {
		cout << "deque: ";
		int it = head;
		for (int i = 0; i < size; i++) {
			cout << buffer[(it++)%buffer_size] << " ";
		}
		cout << endl;
	}

	void printStats() {
		cout << "buffer: ";
		for (int i = 0; i < buffer_size; i++) {
			cout << buffer[i] << " ";
		}
		cout << "\n head: " << head << " tail: " << tail << " size:" << size << "\n";
	}
};

void solve(int n) {
	MyDeque* deque = new MyDeque();

	int flag = NULL, el = NULL;
	for (int i = 0; i < n; i++) {
		cin >> flag >> el;

		switch (flag) {
		case 1:
			deque->push_front(el);
			break;
		case 2:
			if (deque->pop_front() != el) {
				cout << "NO";
				return;
			}
			break;
		case 3:
			deque->push_back(el);
			break;
		case 4:
			if (deque->pop_back() != el) {
				cout << "NO";
				return;
			}
			break;
		}

		//deque->print();
		//deque->printStats();
	}

	cout << "YES";
}

int main() {
	int n;
	cin >> n;

	solve(n);

	return 0;
}
