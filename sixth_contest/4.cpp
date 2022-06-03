// https://contest.yandex.ru/contest/37787/problems/4
// ID - 68756738	

/* Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”. Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает, что все обычные символы совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ. Гарантируется, что сам “?” в тексте не встречается.

Время работы - O(n + m + Z), где Z - общее число вхождений подстрок шаблона “между вопросиками” в исходном тексте. m ≤ 5000, n ≤ 2000000. */

#include <iostream>
#include <vector>

using namespace std;

const int ABC = 26;
const int N = 2000000;
const int M = 5000;

template<typename t>
void print(vector<t>& arr) {
	for (auto& a : arr) {
		cout << a << " ";
	}
}

struct node {
	bool is_terminal;
	int parent;
	char symbol;
	vector<int> types;
	int link;
	int edges[ABC];
	int links[ABC];

	node(int _parent, char _symbol) : parent(_parent), symbol(_symbol), link(-1), is_terminal(false) {
		for (int i = 0; i < ABC; i++) {
			edges[i] = -1;
			links[i] = -1;
		}
	}
};

class trie {
public:
	vector<node> tree;

	trie() : tree(1, node(0, -1)) {
		tree[0].link = 0;
	}

	void add_word(string& temp, pair<int, int> sub, int type) {
		int curr_node = 0;
		for (int i = sub.first; i <= sub.second; i++) {
			char sym = temp[i] - 'a';
			if (tree[curr_node].edges[sym] == -1) {
				tree.push_back(node(curr_node, temp[i]));
				tree[curr_node].edges[sym] = (tree.size() - 1);
			}
			curr_node = tree[curr_node].edges[sym];
		}
		tree[curr_node].is_terminal = true;
		tree[curr_node].types.push_back(type);
	}

	int get_link(int curr) {
		if (tree[curr].link != -1) return tree[curr].link;
		if (curr == 0 || tree[curr].parent == 0) {
			tree[curr].link = 0;
			return 0;
		}
		tree[curr].link = go(get_link(tree[curr].parent), tree[curr].symbol);
		return tree[curr].link;
	}

	int go(int curr, char _sym) {
		char sym = _sym - 'a';
		if (tree[curr].links[sym] != -1) return tree[curr].links[sym];
		if (tree[curr].edges[sym] != -1) {
			tree[curr].links[sym] = tree[curr].edges[sym];
			return tree[curr].links[sym];
		}
		tree[curr].links[sym] = ((curr == 0) ? 0 : go(get_link(curr), _sym));
		return tree[curr].links[sym];
	}
};

vector<pair<int, int>> split(const string& temp) {
	vector<pair<int, int>> templates;
	int start = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == '?' && i - start != 0) {
			templates.push_back({ start, i - 1 });
			start = i;
		}
		while (temp[i] == '?' && i < temp.size()) {
			i++;
			start++;
		}
	}
	if (start != temp.size())
		templates.push_back({ start, temp.size() - 1 });
	return templates;
}

vector<int> solve() {
	string temp, text;
	cin >> temp >> text;
	vector<pair<int, int>> templates = split(temp);
	trie tree;
	for (int i = 0; i < templates.size(); i++) {
		tree.add_word(temp, templates[i], i);
	}
	int curr = 0;
	vector<int> entries(text.size(), 0);
	int buffer_where;
	for (size_t i = 0; i < text.size(); i++) {
		curr = tree.go(curr, text[i]);
		int sub = curr;
		do {
			if (tree.tree[sub].is_terminal) {
				for (int j = 0; j < tree.tree[sub].types.size(); j++) {
					buffer_where = i - templates[tree.tree[sub].types[j]].second;
					if (buffer_where >= 0) {
						entries[buffer_where]++;
					}
				}
			}
			sub = tree.get_link(sub);
		} while (sub != 0);
	}
	vector<int> res;
	for (int i = 0; i < text.size(); i++) {
		if (entries[i] == templates.size() && i + temp.size() <= text.size()) {
			res.push_back(i);
		}
	}
	return res;
}

int main() {
	vector<int> ans = solve();
	print(ans);
	return 0;
}
