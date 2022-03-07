#include <iostream>
#include <string>
#include <vector>

using namespace std;

class my_hash_table {
private:
	struct hash_table_node {
		string key;
		bool is_deleted;
		hash_table_node(const string& _key = "") : key(_key), is_deleted(false) {};
	};
	unsigned int table_size;
	unsigned int size;
	const unsigned int A = 11;
	vector<hash_table_node>table;

	unsigned int hash(const string& key);
	void reconstruct();
	double load_factor();
	unsigned int hash_next(unsigned int prev_hash, unsigned int probe);

public:
	my_hash_table();
	bool add(const string& key);
	bool erase(const string& key);
	bool find(const string& key);
	void print();

};

//horner's method for hashing
unsigned int my_hash_table::hash(const string& key) {
	unsigned int hash_value = 0;
	for (unsigned int i = 0; i < key.size(); i++) {
		hash_value = (hash_value * A + key[i]) % table_size;
	}
	return hash_value;
}

void my_hash_table::reconstruct() {
	vector<hash_table_node> buffer;
	table_size *= 2;
	for (auto& node : table) {
		if (node.key != "") buffer.push_back(node.key);
	}
	table.clear();
	table.resize(table_size, hash_table_node());
	for (auto& node : buffer) {
		add(node.key);
	}
	size = buffer.size();
}

double my_hash_table::load_factor() {
	return static_cast<double>(size) / static_cast<double>(table_size);
}

unsigned int my_hash_table::hash_next(unsigned int prev_hash, unsigned int probe) {
	return (prev_hash + probe) % table_size;
}

my_hash_table::my_hash_table() {
	size = 0;
	table_size = 8;
	table.resize(8, hash_table_node());
}

bool my_hash_table::add(const string& key) {
	if (find(key)) return false;
	if (load_factor() >= 0.75) reconstruct();
	unsigned int hash_value = hash(key);
	unsigned int probe = 0;
	//looking for the first free slot for key value
	while (table[hash_value].key != "") {
		//key value already consists in table
		if (table[hash_value].key == key && !table[hash_value].is_deleted) return false;
		//quadratic probing
		hash_value = hash_next(hash_value, ++probe);
	}
	//if key value is inserted in 'deleted' slot
	if (table[hash_value].is_deleted) table[hash_value].is_deleted = false;
	size++;
	table[hash_value].key = key;
	return true;
}

bool my_hash_table::erase(const string& key) {
	unsigned int hash_value = hash(key);
	unsigned int probe = 0;
	while (table[hash_value].key != "" || table[hash_value].is_deleted) {
		if (table[hash_value].key == key && !table[hash_value].is_deleted) {
			table[hash_value].is_deleted = true;
			table[hash_value].key = "";
			size--;
			return true;
		}
		//quadratic probing
		hash_value = hash_next(hash_value, ++probe);
	}
	return false;
}

bool my_hash_table::find(const string& key) {
	unsigned int hash_value = hash(key);
	unsigned int probe = 0;
	while (probe < table_size) {
		if (table[hash_value].key == "" && !table[hash_value].is_deleted) return false;
		if (table[hash_value].key == key) return true;
		//quadratic probing
		hash_value = hash_next(hash_value, ++probe);
	}
	return false;
}

void my_hash_table::print() {
	for (auto& node : table) {
		cout << node.key << " -> ";
	}
	cout << "\n";
}

void solve(char todo, string key, my_hash_table& hash_table) {
	switch (todo) {
	case '?':
		cout << (hash_table.find(key) ? "OK" : "FAIL") << std::endl;
		break;
	case '+':
		cout << (hash_table.add(key) ? "OK" : "FAIL") << std::endl;
		break;
	case '-':
		cout << (hash_table.erase(key) ? "OK" : "FAIL") << std::endl;
		break;
	}
}

int main() {
	my_hash_table hash_table;
	char todo;
	string key;
	while (cin >> todo >> key) {
		solve(todo, key, hash_table);
	}
	return 0;
}
