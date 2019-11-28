#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;
struct three {
	ll pos;
	ll left;
	ll right;
	ll par;
	three() {}
	three(ll pos, ll left, ll right, ll par) : pos(pos), left(left), right(right), par(par) {}
};
struct Node {
	ll left_pos = 0;
	ll right_pos = 0;
	ll pos;
	Node *lchild = nullptr;
	Node *rchild = nullptr;
	Node *par = nullptr;
	Node() {}
	Node(ll num) : left_pos(num), right_pos(rand() << 15 + rand()) {}
	Node(three thriple) : left_pos(thriple.left), right_pos(thriple.right), pos(thriple.pos) {}
};
Node* prev_node;
void insert(Node *&node, three new_node) {
	if (prev_node->right_pos >= new_node.right) {
		Node *cur_node = prev_node;
		Node *next_node = new Node(new_node);
		while (cur_node->par != nullptr && cur_node->par->right_pos >= new_node.right) {
			cur_node = cur_node->par;
		}
		if (cur_node->par == nullptr) {
			cur_node->par = next_node;
			next_node->lchild = cur_node;
			node = next_node;
		}
		else {
			cur_node->par->rchild = next_node;
			next_node->par = cur_node->par;
			cur_node->par = next_node;
			next_node->lchild = cur_node;
		}
		prev_node = next_node;
	}
	else {
		prev_node->rchild = new Node(new_node);
		prev_node->rchild->par = prev_node;
		prev_node = prev_node->rchild;
	}
}
vector <three> res;
void print(Node* &node, ll p) {
	ll a, b;
	a = node->lchild != nullptr ? node->lchild->pos : 0;
	b = node->rchild != nullptr ? node->rchild->pos : 0;
	res.push_back(three(node->pos, a, b, p));
	if (node->lchild != nullptr) {
		print(node->lchild, node->pos);
	}
	if (node->rchild != nullptr) {
		print(node->rchild, node->pos);
	}
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	srand(time(0));
	vector<three>r(n);
	for (ll i = 1; i <= n; i++) {
		three triple;
		triple.pos = i;
		cin >> triple.left >> triple.right;
		r[i - 1] = triple;
	}
	sort(r.begin(), r.end(), [](three fi, three se) {return fi.left < se.left; });
	Node *root = new Node(r[0]);
	prev_node = root;
	for (ll i = 1; i < n; i++) {
		insert(root, r[i]);
	}
	cout << "YES" << endl;
	print(root, 0);
	sort(res.begin(), res.end(), [](three fi, three se) {return fi.pos < se.pos; });
	for (ll i = 0; i < res.size(); i++) {
		cout << res[i].par << ' ' << res[i].left << ' ' << res[i].right << endl;
	}
}