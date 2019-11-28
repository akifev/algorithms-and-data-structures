#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

enum operations {
	NOOPERATIONS,
	SET
};
struct Node {
	ll min = 0;
	ll ind;
	ll rightBorder;
	ll leftBorder;
	operations op = NOOPERATIONS;
	Node() {};
	Node(ll x) {
		min = x;
	};
};
void build(vector<Node> &t, ll ind, ll leftBorder, ll rightBorder) {
	t[ind].ind = ind;
	t[ind].leftBorder = leftBorder;
	t[ind].rightBorder = rightBorder;
	if (leftBorder == rightBorder) {
		return;
	}
	build(t, 2 * ind + 1, leftBorder, (leftBorder + rightBorder) / 2);
	build(t, 2 * ind + 2, (leftBorder + rightBorder) / 2 + 1, rightBorder);
}

void propagate(vector <Node> &t, ll ind) {
	if (t[ind].op == NOOPERATIONS) {
		return;
	}
	if (t[ind].leftBorder != t[ind].rightBorder) {
		t[2 * ind + 1].min = max(t[2 * ind + 1].min, t[ind].min);
		t[2 * ind + 2].min = max(t[2 * ind + 2].min, t[ind].min);
		t[2 * ind + 1].op = SET;
		t[2 * ind + 2].op = SET;
	}
	t[ind].op = NOOPERATIONS;
}

Node f(Node fi, Node se) {
	return (fi.min < se.min ? fi : se);
}

Node min(vector<Node> &t, ll ind, ll l, ll r) {
	propagate(t, ind);
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		return t[ind];
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return Node(LLONG_MAX);
	}
	return f(min(t, 2 * ind + 1, l, r), min(t, 2 * ind + 2, l, r));
}

void set(vector<Node> &t, ll ind, ll l, ll r, ll value) {
	propagate(t, ind);
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		t[ind].min = max(t[ind].min, value);
		t[ind].op = SET;
		return;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return;
	}
	set(t, 2 * ind + 1, l, r, value);
	set(t, 2 * ind + 2, l, r, value);
	t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
}

ll positionMin(vector <Node> &t, Node minNode) {
	if (minNode.leftBorder != minNode.rightBorder) {
		propagate(t, minNode.ind);
		if (t[2 * minNode.ind + 1].min == minNode.min) {
			return positionMin(t, t[2 * minNode.ind + 1]);
		}
		else {
			return positionMin(t, t[2 * minNode.ind + 2]);
		}
	}
	else {
		return minNode.ind;
	}
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, m;
	cin >> n >> m;
	ll sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	vector<Node> t(2 * sz - 1);
	build(t, 0, sz - 1, 2 * sz - 2);

	for (ll i = 0; i < m; i++) {
		string op;
		cin >> op;
		if (op == "defend") {
			ll l, r, val;
			cin >> l >> r >> val;
			set(t, 0, sz - 1 + l - 1, sz - 1 + r - 1, val);
		}
		else {
			ll l, r;
			cin >> l >> r;
			Node ans = min(t, 0, sz - 1 + l - 1, sz - 1 + r - 1);
			cout << ans.min << ' ' << positionMin(t, ans) + 1 - sz + 1 << endl;
		}
	}
	return 0;
}