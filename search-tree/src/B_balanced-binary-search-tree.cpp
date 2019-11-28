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
	Node *lchild;
	Node *rchild;
	Node(ll x) : key(x), priority(rand()), lchild(nullptr), rchild(nullptr) {}
};
void split(Node *node, Node *&t1, Node *&t2, ll key) {
	if (node == nullptr) {
		t1 = t2 = nullptr;
		return;
	}
	if (node->key < key) {
		split(node->rchild, node->rchild, t2, key);
		t1 = node;
		return;
	}
	else {
		split(node->lchild, t1, node->lchild, key);
		t2 = node;
		return;
	}
}
void merge(Node *&node, Node *t1, Node *t2) {
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
}
void insert(Node *&node, ll key) {
	Node *t1, *t2;
	split(node, t1, t2, key);
	merge(node, t1, new Node(key));
	merge(node, node, t2);
}
void erase(Node *&node, ll key) {
	if (key < node->key)
		erase(node->lchild, key);
	else if (key > node->key)
		erase(node->rchild, key);
	else
		merge(node, node->lchild, node->rchild);
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
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	srand(time(0));
	Node *root = nullptr;
	string operation;
	while (cin >> operation) {
		ll x;
		cin >> x;
		switch (operation[0]) {
		case 'i':
			if (get(root, x) == nullptr)
				insert(root, x);
			break;
		case 'd':
			if (get(root, x) != nullptr)
				erase(root, x);
			break;
		case 'e':
			cout << (exists(root, x) ? "true" : "false");
			cout << endl;
			break;
		case 'n':
		{
			Node *ans = next(root, x);
			if (ans != nullptr)
				cout << ans->key;
			else
				cout << "none";
			cout << endl;
		}
		break;
		case 'p':
		{
			Node *ans = prev(root, x);
			if (ans != nullptr)
				cout << ans->key;
			else
				cout << "none";
			cout << endl;
		}
		}
	}
}