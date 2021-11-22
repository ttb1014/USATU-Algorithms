// 58845453 - ID
// https://contest.yandex.ru/contest/30914/problems/2_1/ - link

#include <iostream>

using namespace std;

struct Customer {
	int in;
	int out;
	int ads;

	Customer(int in = 0, int out = 0) : in(in), out(out), ads(0) {}

	bool operator<(const Customer&) const;
};

bool Customer::operator<(const Customer& other) const {
	if (out < other.out)
		return true;
	if (out == other.out)
		return in > other.in;
	return false;
}

class Customers_queue {
public:
	Customers_queue(int n) : array(new Customer[n]), size(0) {}
	void add(Customer);
	void sort(int begin, int end);
	int advertisement_counter();
	Customer* array;	
	int size;
	void adverts_inc(int, int);
	
};

void Customers_queue::add(Customer customer) {
	array[size++] = customer;
}

void sift_down(Customer* arr, int size, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < size && !(arr[left] < arr[largest]))
		largest = left;
	if (right < size && !(arr[right] < arr[largest]))
		largest = right;
	if (largest != i) {
		swap(arr[i], arr[largest]);
		sift_down(arr, size, largest);
	}
}

void build_heap(Customer* arr, int arr_size) {
	for (int i = arr_size / 2 - 1; i >= 0; --i) {
		sift_down(arr, arr_size, i);
	}
}

void heap_sort(Customer* arr, int arr_size) {
	int heap_size = arr_size;
	build_heap(arr, arr_size);
	while (heap_size > 1) {
		swap(arr[0], arr[heap_size - 1]);
		--heap_size;
		sift_down(arr, heap_size, 0);
	}
}

void Customers_queue::sort(int begin, int end) {
	heap_sort(array, size);
}

void Customers_queue::adverts_inc(int customer, int time_moment) {
	for (int i = customer; i < size &&
		array[i].in <= time_moment; ++i)
		++array[i].ads;
}

int Customers_queue::advertisement_counter() {
	int ads = 0;
	for (int i = 0; i < size; i++) {
		if (array[i].ads == 0) {
			adverts_inc(i, array[i].out - 1);
			ads++;
		}
		if (array[i].ads == 1) {
			adverts_inc(i, array[i].out);
			ads++;
		}
	}
	return ads;
}

void read_queue(Customers_queue &q, int size) {
	for (int i = 0; i < size; ++i) {
		int in, out;
		cin >> in >> out;

		Customer new_customer(in, out);
		q.add(new_customer);
	}
}

void solve(Customers_queue& q, int size) {
	q.sort(0, size);
	cout << q.advertisement_counter();
}

int main() {
	int n = 0;
	cin >> n;
	Customers_queue customers_queue(n);

	read_queue(customers_queue, n);

	solve(customers_queue, n);

	return 0;
}
