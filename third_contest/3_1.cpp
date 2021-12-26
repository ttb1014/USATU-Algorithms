// https://contest.yandex.ru/contest/32613/problems/3_1/
// 63077337

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class AVL_tree {
private:
	struct tree_node {
		int key;
		int height;
		int count;
		tree_node* left;
		tree_node* right;

		tree_node(int key) {
			this->key = key;
			left = nullptr;
			right = nullptr;
			height = 1;
			count = 1;
		}

	};

	tree_node* root;

	int height(tree_node* node) {
		return node ? node->height : 0;
	}

	int count(tree_node* node) {
		return node ? node->count : 0;
	}

	int balance_factor(tree_node* node) {
		return height(node->right) - height(node->left);
	}

	void fix_height(tree_node* node) {
		int h_left = height(node->left);
		int h_right = height(node->right);
		node->height = (h_left > h_right ? h_left : h_right) + 1;
	}

	void fix_count(tree_node* node) {
		node->count = count(node->right) + count(node->left) + 1;
	}

	void fix_stats(tree_node* node) {
		fix_height(node);
		fix_count(node);
	}

	tree_node* rotate_left(tree_node* node) {
		tree_node* tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;
		fix_stats(node);
		fix_stats(tmp);
		return tmp;
	}

	tree_node* rotate_right(tree_node* node) {
		tree_node* tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;
		fix_stats(node);
		fix_stats(tmp);
		return tmp;
	}

	tree_node* balance(tree_node* node) {
		fix_height(node);
		if (balance_factor(node) == 2) {
			if (balance_factor(node->right) < 0) {
				node->right = rotate_right(node->right);
			}
			return rotate_left(node);
		}
		if (balance_factor(node) == -2) {
			if (balance_factor(node->left) > 0) {
				node->left = rotate_left(node->left);
			}
			return rotate_right(node);
		}
		return node;
	}

	tree_node* _insert(tree_node* node, int key, int& pos) {
		if (!node) {
			return new tree_node(key);
		}
		++(node->count);
		if (key < node->key) {
			pos += count(node->right) + 1;
			node->left = _insert(node->left, key, pos);
		}
		else {
			node->right = _insert(node->right, key, pos);
		}
		return balance(node);
	}

	tree_node* find_min(tree_node* node) {
		return node->left ? find_min(node->left) : node;
	}

	tree_node* remove_min(tree_node* node) {
		if (node->left == 0)
			return node->right;
		node->left = remove_min(node->left);
		--node->count;
		return balance(node);
	}

	tree_node* _erase(tree_node* node, int pos) {
		if (!node) {
			return 0;
		}
		if (pos >= node->count) {
			return node;
		}
		int sum = 0;
		std::stack<tree_node*> nodes;
		while (true) {
			int r_count = count(node->right);
			if (pos - sum > r_count) {
				nodes.push(node);
				node = node->left;
				sum += r_count + 1;
			}
			else if (pos - sum < r_count) {
				if (node->right != 0) {
					nodes.push(node);
					node = node->right;
				}
				else {
					break;
				}
			}
			else {
				tree_node* l_node = node->left;
				tree_node* r_node = node->right;
				int key = node->key;
				delete node;
				if (r_node == 0) {
					if (l_node == 0) {
						if (!nodes.empty()) {
							node = nodes.top();
							nodes.pop();
							if (node->key > key) {
								node->left = 0;
							}
							else {
								node->right = 0;
							}
							--node->count;
						}
						else {
							return 0;
						}
					}
					else {
						node = l_node;
					}
				}
				else {
					tree_node* min = find_min(r_node);
					min->right = remove_min(r_node);
					min->left = l_node;
					fix_count(min);
					node = balance(min);
				}
				break;
			}
		}
		tree_node* tmp;
		while (!nodes.empty()) {
			tmp = nodes.top();
			nodes.pop();
			--tmp->count;
			if (tmp->key > node->key) {
				tmp->left = node;
			}
			else {
				tmp->right = node;
			}
			node = balance(tmp);
		}
		return node;
	}

public:
	AVL_tree() {
		root = nullptr;
	}

	int insert(int key) {
		int pos = 0;
		root = _insert(root, key, pos);
		return pos;
	}

	void erase(int pos) {
		root = _erase(root, pos);
	}
};

void print_arr(vector<int>& arr) {
	for (auto& a : arr) cout << a << endl;
}

void solve() {
	int n;
	cin >> n;
	AVL_tree tree;
	int comm, key;
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		cin >> comm >> key;
		switch (comm) {
		case 1:
			ans.push_back(tree.insert(key));
			break;
		case 2:
			tree.erase(key);
			break;
		}
	}
	print_arr(ans);
}

int main() {
	solve();
	return 0;
}
