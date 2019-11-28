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
	ll sum = 0;
	Node *lchild;
	Node *rchild;
	Node(ll x) : key(x), sum(x), priority(rand()), lchild(nullptr), rchild(nullptr) {}
	Node(Node *x) : key(x->key), sum(x->sum), priority(x->priority), lchild(x->lchild), rchild(x->rchild) {}
};

ll node_sum(Node *node) {
	return node == nullptr ? 0 : node->sum;
}

void upd_sum(Node *node) {
	if (node == nullptr) {
		return;
	}
	node->sum = node_sum(node->lchild) + node_sum(node->rchild) + node->key;
}
void split(Node *node, Node *&t1, Node *&t2, ll key) {
	if (node == nullptr) {
		t1 = t2 = nullptr;
		return;
	}
	if (node->key < key) {
		split(node->rchild, node->rchild, t2, key);
		upd_sum(node);
		t1 = node;
		//upd_sum(t1);
		return;
	}
	else {
		split(node->lchild, t1, node->lchild, key);
		upd_sum(node);
		t2 = node;
		//upd_sum(t2);
		return;
	}
}
void merge(Node *&node, Node *t1, Node *t2) {
	if (t1 == nullptr || t2 == nullptr) {
		node = (t1 == nullptr ? t2 : t1);
		//upd_sum(node);
		return;
	}
	if (t1->priority > t2->priority) {
		merge(t1->rchild, t1->rchild, t2);
		upd_sum(t1);
		node = t1;
	}
	else {
		merge(t2->lchild, t1, t2->lchild);
		upd_sum(t2);
		node = t2;
	}
	//upd_sum(node);
}
void insert(Node *&node, ll x) {
	Node *t1 = nullptr, *t2 = nullptr;
	split(node, t1, t2, x);
	merge(node, t1, new Node(x));
	merge(node, node, t2);
}
bool get(Node *node, ll key) {
	if (node == nullptr)
		return false;
	if (node->key == key)
		return true;
	if (key < node->key)
		return get(node->lchild, key);
	else
		return get(node->rchild, key);
}
ll sum(Node *node, ll l, ll r) {
	Node *t1 = nullptr, *t2 = nullptr, *t3 = nullptr, *t4 = nullptr;
	//Node newNode = *node;
	//Node* u = &newNode;
	auto u = new Node(node);
	split(u, t1, t2, l);
	split(t2, t3, t4, r + 1);
	ll temp = node_sum(t3);
	//Node *tmp = nullptr;
	//merge(tmp, t3, t4);
	//merge(node, t1, tmp);
	return temp;
}
const ll SH = 1000000000;
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	srand(time(0));
	Node *root = nullptr;
	ll n;
	cin >> n;
	bool wasSum = false;
	ll lastSum = 0;
	for (ll i = 0; i < n; i++) {
		char op;
		cin >> op;
		if (op == '+') {
			ll x;
			cin >> x;
			if (wasSum) {
				x = (x + lastSum) % SH;
			}
			if (!get(root, x))
				insert(root, x);
			wasSum = false;
		}
		else {
			ll l, r;
			cin >> l >> r;
			lastSum = sum(root, l, r);
			wasSum = true;
			cout << lastSum << endl;
		}
	}
}