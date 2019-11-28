#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;
typedef long long ll;
struct Node {
	ll priority;
	ll length;
	ll word_len;
	char letter;
	ll cnt_different;
	vector<bool> alp = vector<bool>(26, false);
	Node *lchild;
	Node *rchild;
	Node(char letter, ll len) : letter(letter), length(len), word_len(len), cnt_different(0), priority((rand() << 15) + rand()), lchild(nullptr), rchild(nullptr) {}
	Node(char letter, ll len, ll size, ll cnt, Node *left, Node *right, ll prior) : letter(letter), length(size), word_len(len), cnt_different(cnt), priority(prior), lchild(left), rchild(right) {}
};
ll get_length(Node *node) {
	return node != nullptr ? node->length : 0;
}
void upd_length(Node *&node) {
	if (node != nullptr)
		node->length = get_length(node->rchild) + get_length(node->lchild) + node->word_len;
}
ll get_cnt_different(Node *node) {
	return node != nullptr ? node->cnt_different : 0;
}
void upd_cnt_different(Node *&node) {
	if (node != nullptr) {
		ll cnt_different = 0;
		for (int i = 0; i < 26; i++) {
			node->alp[i] = (int)(node->letter - 'a') == i || node->lchild != nullptr && node->lchild->alp[i] || node->rchild != nullptr && node->rchild->alp[i] ? true : false;
			if (node->alp[i])
				cnt_different++;
		}
		node->cnt_different = cnt_different;
	}
}

void split_node(Node *&node) {
	if (node == nullptr) {
		return;
	}
	else {
		if (node->word_len == 1) {
			return;
		}
		else {
			Node *tmp;
			tmp = new Node(node->letter, 1, node->length, node->cnt_different, nullptr, node->rchild, node->priority + 1);
			if (node->word_len == 2) {
				tmp->lchild = new Node(node->letter, node->word_len - 1, node->length - 1, node->cnt_different, node->lchild, nullptr, node->priority);
			}
			else {
				tmp->lchild = new Node(node->letter, (node->word_len - 1) / 2, node->length - 1, node->cnt_different, node->lchild, nullptr, node->priority);
				tmp->rchild = new Node(node->letter, node->word_len - tmp->lchild->word_len - 1, node->length - 1, node->cnt_different, nullptr, node->rchild, node->priority - 1);
			}
			upd_length(tmp->lchild);
			upd_cnt_different(tmp->lchild);
			upd_length(tmp->rchild);
			upd_cnt_different(tmp->rchild);
			node = tmp;
			upd_length(node);
			upd_cnt_different(node);
		}
	}
}
void merge(Node *&node, Node *t1, Node *t2) {
	split_node(t1);
	split_node(t2);
	if (t1 == nullptr || t2 == nullptr) {
		node = (t1 == nullptr ? t2 : t1);
		return;
	}
	if (t1->priority > t2->priority) {
		merge(t1->rchild, t1->rchild, t2);
		node = t1;
	}
	else {
		merge(t2->lchild, t1, t2->lchild);
		node = t2;
	}
	upd_length(node);
	upd_cnt_different(node);
}
void split(Node *node, Node *&t1, Node *&t2, ll key) {
	split_node(node);
	if (node == nullptr) {
		t1 = t2 = nullptr;
		return;
	}
	ll l_length = get_length(node->lchild);
	if (l_length < key) {
		split(node->rchild, node->rchild, t2, key - l_length - 1);
		t1 = node;
		upd_length(t1);
		upd_cnt_different(t1);
		return;
	}
	else {
		split(node->lchild, t1, node->lchild, key);
		t2 = node;
		upd_length(t2);
		upd_cnt_different(t2);
		return;
	}
}
void insert(Node *&node, ll pos, Node *x) {
	Node *t1, *t2, *t3;
	split(node, t1, t2, pos);
	merge(node, t1, x);
	merge(t3, node, t2);
	node = t3;
	upd_length(node);
	upd_cnt_different(node);
}
void erase(Node *&root, ll l, ll r) {
	Node *t1, *t2, *t3, *t4;
	split(root, t1, t2, l);
	split(root, t3, t4, r - get_length(t1));
	merge(root, t1, t4);
	upd_length(root);
	upd_cnt_different(root);
}
void println(Node *node) {
	if (node == nullptr) {
		return;
	}
	if (node->lchild == nullptr&&node->rchild == nullptr) {
		cout << '[' << node->letter << ' ' << node->word_len /*<< ' ' << node->cnt_different << */ << ']';
	}
	if (node->lchild != nullptr) {
		println(node->lchild);
		cout << '[' << node->letter << ' ' << node->word_len /*<< ' ' << node->cnt_different << */ << ']';
		if (node->rchild != nullptr) {
			println(node->rchild);
		}
	}
	else if (node->rchild != nullptr) {
		cout << '[' << node->letter << ' ' << node->word_len /*<< ' ' << node->cnt_different << */ << ']';
		println(node->rchild);
	}
}
int main() {
	ifstream cin("log.in");
	ofstream cout("log.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	srand(time(0));
	Node *root = nullptr;
	ll n;
	cin >> n;
	for (ll i = 0; i < n; i++) {
		char op;
		cin >> op;
		if (op == '+') {
			ll ind, len;
			char letter;
			cin >> ind >> len >> letter;
			ind--;
			insert(root, ind, new Node(letter, len));
		}
		else if (op == '-') {
			ll ind, len;
			cin >> ind >> len;
			ind--;
			erase(root, ind, ind + len);
		}
		else {
			ll ind, len;
			cin >> ind >> len;
			ind--;
			Node *t1, *t2, *t3, *t4;
			split(root, t1, t2, ind);
			split(t2, t3, t4, ind + len - get_length(t1) - 1);
			ll ans = t3->cnt_different;
			merge(t1, t1, t3);
			merge(root, t1, t4);
			cout << ans << endl;
		}
		println(root);
		cout << endl;
	}
}