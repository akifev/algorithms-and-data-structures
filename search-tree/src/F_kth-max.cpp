#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Node {
	ll key;
	ll priority;
	ll size = 0;
	Node *lchild;
	Node *rchild;
	Node(ll x) : key(x), priority(rand()), size(0), lchild(nullptr), rchild(nullptr) {}
};

ll get_sz(Node *node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		return node->size;
	}
}

void upd_sz(Node *&node) {
	if (node != nullptr)
		node->size = get_sz(node->rchild) + get_sz(node->lchild) + 1;
}

void split(Node *node, Node *&t1, Node *&t2, ll key) {
	if (node == nullptr) {
		t1 = t2 = nullptr;
		return;
	}
	if (node->key < key) {
		split(node->rchild, node->rchild, t2, key);
		t1 = node;
		upd_sz(t1);
		return;
	}
	else {
		split(node->lchild, t1, node->lchild, key);
		t2 = node;
		upd_sz(t2);
		return;
	}
}
void merge(Node *&node, Node *t1, Node *t2) {
	if (t1 == nullptr || t2 == nullptr) {
		node = (t1 == nullptr ? t2 : t1);
		upd_sz(node);
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
	upd_sz(node);
}
void insert(Node *&node, ll x) {
	Node *t1, *t2;
	split(node, t1, t2, x);
	merge(node, t1, new Node(x));
	merge(node, node, t2);
	upd_sz(node);
}
void erase(Node *&node, ll key) {
	if (key < node->key)
		erase(node->lchild, key), upd_sz(node);
	else if (key > node->key)
		erase(node->rchild, key), upd_sz(node);
	else {
		merge(node, node->lchild, node->rchild);
		upd_sz(node);
	}
}
Node* get(Node *node, ll key) {
	if (node == nullptr)
		return nullptr;
	if (node->key == key)
		return node;
	if (key < node->key)
		return get(node->lchild, key);
	else
		return get(node->rchild, key);
}
Node* next(Node *node, ll key) {
	Node *ans = nullptr;
	while (node != nullptr)
		if (key < node->key) {
			ans = node;
			node = node->lchild;
		}
		else
			node = node->rchild;
	return ans;
}
Node* prev(Node *node, ll key) {
	Node *ans = nullptr;
	while (node != nullptr)
		if (key > node->key) {
			ans = node;
			node = node->rchild;
		}
		else
			node = node->lchild;
	return ans;
}
bool exists(Node *node, ll key) {
	return (get(node, key) != nullptr ? true : false);
}
Node* find_kth(Node *node, ll k) {
	if (k == get_sz(node->lchild)) {
		return node;
	}
	if (k <= get_sz(node->lchild)) {
		return find_kth(node->lchild, k);
	}
	else {
		return find_kth(node->rchild, k - get_sz(node->lchild) - 1);
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	Node *root = nullptr;
	ll n;
	cin >> n;
	for (ll i = 0; i < n; i++) {
		ll op, x;
		cin >> op >> x;
		if (op == 1) {
			insert(root, x);
		}
		else if (op == -1) {
			erase(root, x);
		}
		else {
			cout << find_kth(root, get_sz(root) - x)->key << endl;
		}
	}
}