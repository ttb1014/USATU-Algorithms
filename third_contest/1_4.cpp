#include <iostream>
#include <queue>

using namespace std;

class bynary_search_tree {
public:
	struct binary_node {
		int key;
		binary_node* left;
		binary_node* right;
		binary_node* parent;

		binary_node(int key) {
			this->key = key;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
	};

	binary_node* root;

	bynary_search_tree() {
		this->root = nullptr;
	}

	void print(binary_node* node) {
		cout << node->key << " ";
	}
    
	void BFS_print() {
		queue<binary_node*> q;
		if (root != nullptr) q.push(root);
		while (!q.empty()) {
			binary_node* node = q.front();
			q.pop();
			print(node);
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
		}
	}

	void insert(int key) {
		_insert(root, key);
	}

	void _insert(binary_node*& node, int key) {
		if (node == nullptr) {
			node = new binary_node(key);
			return;
		}
		if (key < node->key)
			_insert(node->left, key);
		else
			_insert(node->right, key);
	}
};

void solve(int n) {
	bynary_search_tree bst;
	int buffer;
	for (int i = 0; i < n; i++) {
		cin >> buffer;
		bst.insert(buffer);
	}
	bst.BFS_print();
}

int main() {
	int n;
	cin >> n;
	solve(n);
	return 0;
}
