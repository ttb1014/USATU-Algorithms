//https://contest.yandex.ru/contest/32613/problems/2_1/
//61880063

#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class bynary_search_tree {
public:
	struct binary_node {
		T key;
		binary_node* left;
		binary_node* right;

		binary_node(T key) {
			this->key = key;
			left = nullptr;
			right = nullptr;
		}
	};

	binary_node* root;
	int depth;

	bynary_search_tree() {
		this->root = nullptr;
		depth = NULL;
	}

	int DFS(binary_node* node) {
		if (node == nullptr) return 0;
		return 1 + max(DFS(node->left), DFS(node->right));
	}

	void update_depth() {
		depth = DFS(root);
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

	void insert(T key) {
		_insert(root, key);
	}

	void _insert(binary_node*& node, T key) {
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

template <typename T, typename P>
class treap {
public:

	struct treap_node {
		T key;
		P priority;
		treap_node* left;
		treap_node* right;

		treap_node(T key, P priority) {
			this->key = key;
			this->priority = priority;
			left = nullptr;
			right = nullptr;
		}
	};

	treap_node* root;
	int depth;

	treap() {
		root = nullptr;
		depth = NULL;
	}

	void split(treap_node* current_node, T key, treap_node*& left, treap_node*& right) {
		if (current_node == nullptr) {
			left = nullptr;
			right = nullptr;
		}
		else if (current_node->key < key) {
			split(current_node->right, key, current_node->right, right);
			left = current_node;
		}
		else {
			split(current_node->left, key, left, current_node->left);
			right = current_node;
		}
	}

	treap_node* merge(treap_node* left, treap_node* right) {
		if (left == nullptr || right == nullptr) {
			return left == nullptr ? right : left;
		}
		if (left->priority > right->priority) {
			left->right = merge(left->right, right);
			return left;
		}
		else {
			right->left = merge(left, right->left);
			return right;
		}
	}

	int DFS(treap_node* node) {
		if (node == nullptr) return 0;
		return 1 + max(DFS(node->left), DFS(node->right));
	}

	void update_depth() {
		depth = DFS(root);
	}

	void insert(T key, P priority) {
		treap_node* node = root;
		treap_node* prev = nullptr;
		if (root == nullptr) {
			root = new treap_node(key, priority);
			return;
		}
		while (node->priority > priority) {
			if (node->key > key)
				if (node->left != nullptr) {
					prev = node;
					node = node->left;
				}
				else {
					node->left = new treap_node(key, priority);
					return;
				}
			else
				if (node->right != nullptr) {
					prev = node;
					node = node->right;
				}
				else {
					node->right = new treap_node(key, priority);
					return;
				}
		}

		treap_node* sub_treap_left;
		treap_node* sub_treap_right;
		split(node, key, sub_treap_left, sub_treap_right);
		node = new treap_node(key, priority);
		node->left = sub_treap_left;
		node->right = sub_treap_right;
		if (prev == nullptr) {
			root = node;
			return;
		}
		if (prev->key > node->key)
			prev->left = node;
		else
			prev->right = node;
	}

	void print(treap_node* node) {
		cout << node->key << " ";
	}

	void BFS_print() {
		queue<treap_node*> q;
		if (root != nullptr) q.push(root);
		while (!q.empty()) {
			treap_node* node = q.front();
			q.pop();
			print(node);
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
		}
	}
};

int main() {
	int n;
	cin >> n;
	bynary_search_tree<int> tree1;
	treap<int, int> tree2;
	int key, priority;
	for (int i = 0; i < n; i++) {
		cin >> key >> priority;
		tree1.insert(key);
		tree2.insert(key, priority);
	}
	tree1.update_depth();
	tree2.update_depth();
	cout << abs(tree1.depth - tree2.depth);
	return 0;
}
