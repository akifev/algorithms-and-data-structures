#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;
struct Node {
	ll priority;
	ll size;
	ll val;
	ll cntEbolik;
	Node *lchild;
	Node *rchild;
	Node(ll x) : val(x), cntEbolik(x == 0 ? 1 : 0), priority((rand() << 15) + rand()), size(1), lchild(nullptr), rchild(nullptr) {}
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
ll get_ebolik(Node *node) {
	if (node == nullptr) {
		return 0;
	}
	else {
		return node->cntEbolik;
	}
}
void upd_ebolik(Node *&node) {
	if (node != nullptr)
		node->cntEbolik = get_ebolik(node->rchild) + get_ebolik(node->lchild) + (node->val == 0 ? 1 : 0);
}
void split(Node *node, Node *&t1, Node *&t2, ll key) {
	if (node == nullptr) {
		t1 = t2 = nullptr;
		return;
	}
	ll l_size = get_sz(node->lchild);
	if (l_size < key) {
		split(node->rchild, node->rchild, t2, key - l_size - 1);
		t1 = node;
		upd_sz(t1);
		upd_ebolik(t1);
		return;
	}
	else {
		split(node->lchild, t1, node->lchild, key);
		t2 = node;
		upd_sz(t2);
		upd_ebolik(t2);
		return;
	}
}
void merge(Node *&node, Node *t1, Node *t2) {
	if (t1 == nullptr || t2 == nullptr) {
		node = (t1 == nullptr ? t2 : t1);
		//upd_sz(node);
		//upd_ebolik(node);
		return;
	}
	if (t1->priority > t2->priority) {
		merge(t1->rchild, t1->rchild, t2);
		//upd_sz(t1);
		//upd_ebolik(t1);
		node = t1;
	}
	else {
		merge(t2->lchild, t1, t2->lchild);
		//upd_sz(t2);
		//upd_ebolik(t2);
		node = t2;
	}
	upd_sz(node);
	upd_ebolik(node);
}
void insert(Node *&node, ll pos, Node*x) {
	Node *t1, *t2, *t3;
	split(node, t1, t2, pos);
	merge(node, t1, x);
	merge(t3, node, t2);
	node = t3;
}
vector<ll>ans;
void print(Node *node) {
	if (node->lchild == nullptr&&node->rchild == nullptr) {
		ans.push_back(node->val);
	}
	if (node->lchild != nullptr) {
		print(node->lchild);
		ans.push_back(node->val);
		if (node->rchild != nullptr) {
			print(node->rchild);
		}
	}
	else if (node->rchild != nullptr) {
		ans.push_back(node->val);
		print(node->rchild);
	}
}
void erase_ebolik(Node *&node) {
	if (node == nullptr) {
		return;
	}
	if (node->cntEbolik > 0) {
		if (node->lchild != nullptr && node->lchild->cntEbolik > 0) {
			erase_ebolik(node->lchild);
			upd_sz(node);
			upd_ebolik(node);
		}
		else {
			if (node->val == 0) {
				merge(node, node->lchild, node->rchild);
				return;
			}
			erase_ebolik(node->rchild);
			upd_sz(node);
			upd_ebolik(node);
		}
	}
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	srand(time(0));
	Node *root = nullptr;
	ll n, m;
	cin >> n >> m;
	for (ll i = 1; i <= m + n + 1; i++) {
		insert(root, i, new Node(0));
	}
	for (ll i = 1; i <= n; i++) {
		ll pos;
		cin >> pos;
		pos--;
		Node *t1 = nullptr, *t2 = nullptr;
		split(root, t1, t2, pos);
		erase_ebolik(t2);
		merge(root, t1, t2);
		insert(root, pos, new Node(i));
	}
	print(root);
	ll en = 0;
	for (ll i = 0; i < ans.size(); i++) {
		if (ans[i] != 0) {
			en = i;
		}
	}
	cout << en + 1 << endl;
	for (ll i = 0; i <= en; i++) {
		cout << ans[i] << ' ';
	}
}