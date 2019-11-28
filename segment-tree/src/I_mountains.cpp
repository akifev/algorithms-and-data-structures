#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

enum operations {
	NOOPERATIONS,
	SET
};
struct Node {
	ll max = 0;
	ll sum = 0;
	ll leftBorder;
	ll rightBorder;
	operations op = NOOPERATIONS;
	Node *lchild = nullptr;
	Node *rchild = nullptr;
	Node(ll leftBorder, ll rightBorder) {
		this->leftBorder = leftBorder;
		this->rightBorder = rightBorder;
	}
};

void lazy_propagation(Node* &node) {
	if (node->leftBorder < node->rightBorder) {
		if (node->lchild == nullptr) {
			node->lchild = new Node(node->leftBorder, (node->leftBorder + node->rightBorder) / 2);
			node->rchild = new Node((node->leftBorder + node->rightBorder) / 2 + 1, node->rightBorder);
		}
		if (node->op == NOOPERATIONS) {
			return;
		}
		node->lchild->max = node->max >> 1;
		node->lchild->sum = node->sum >> 1;
		node->lchild->op = SET;
		node->rchild->max = node->max >> 1;
		node->rchild->sum = node->sum >> 1;
		node->rchild->op = SET;
	}
	node->op = NOOPERATIONS;
}
void set(Node* &node, ll l, ll r, ll value) {
	lazy_propagation(node);
	if (node->rightBorder < l || r < node->leftBorder) {
		return;
	}
	if (l <= node->leftBorder && node->rightBorder <= r) {
		node->max = (node->rightBorder - node->leftBorder + 1) * value;
		node->sum = (node->rightBorder - node->leftBorder + 1) * value;
		node->op = SET;
		//lazy_propagation(node);
		return;
	}
	set(node->lchild, l, r, value);
	set(node->rchild, l, r, value);
	node->sum = node->lchild->sum + node->rchild->sum;
	node->max = max(node->lchild->max, node->lchild->sum + node->rchild->max);
}

ll findAns(Node* &node, ll height) {
	lazy_propagation(node);
	if (node->leftBorder == node->rightBorder) {
		if (height - node->max >= 0)
			return node->leftBorder;
		else
			return node->leftBorder - 1;
	}
	if (node->lchild->max > height) {
		return findAns(node->lchild, height);
	}
	else {
		return findAns(node->rchild, height - node->lchild->sum);
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	ll sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	Node* root = new Node(sz - 1, 2 * sz - 2);
	char op;
	while (cin >> op && op != 'E') {
		if (op == 'Q') {
			ll h;
			cin >> h;
			ll ans = findAns(root, h) - sz + 2;
			cout << (ans == sz ? n : ans) << endl;
		}
		else {
			ll l, r, val;
			cin >> l >> r >> val;
			set(root, l + sz - 2, r + sz - 2, val);
		}
	}
	return 0;
}