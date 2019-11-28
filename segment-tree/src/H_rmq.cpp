#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

struct Node {
	ll min = LLONG_MAX;
	ll ind;
	ll rightBorder;
	ll leftBorder;
	//	operations op = NOOPERATIONS;
	Node() {};
	Node(ll x) {
		min = x;
	};
};

void build(vector<Node> &t, ll ind, ll leftBorder, ll rightBorder) {
	t[ind].ind = ind;
	t[ind].leftBorder = leftBorder;
	t[ind].rightBorder = rightBorder;
	//t[ind].op = NOOPERATIONS;
	if (leftBorder == rightBorder) {
		return;
	}
	build(t, 2 * ind + 1, leftBorder, (leftBorder + rightBorder) / 2);
	build(t, 2 * ind + 2, (leftBorder + rightBorder) / 2 + 1, rightBorder);
	t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
}
void propagate(vector <Node> &t, ll ind) {
	//if (t[ind].op == NOOPERATIONS) {
	//	return;
	//}
	if (t[ind].leftBorder != t[ind].rightBorder) {
		if (t[2 * ind + 1].min == LLONG_MAX) {
			t[2 * ind + 1].min = t[ind].min;
			//t[2 * ind + 1].op = SET;
		}
		else {
			if (t[2 * ind + 1].min < t[ind].min) {
				//		t[2 * ind + 1].op = SET;
				t[2 * ind + 1].min = t[ind].min;
			}
		}
		if (t[2 * ind + 2].min == LLONG_MAX) {
			t[2 * ind + 2].min = t[ind].min;
			//t[2 * ind + 2].op = SET;
		}
		else {
			if (t[2 * ind + 2].min < t[ind].min) {
				//t[2 * ind + 2].op = SET;
				t[2 * ind + 2].min = t[ind].min;
			}
		}
	}
	//t[ind].op = NOOPERATIONS;
}

void set(vector<Node> &t, ll ind, ll l, ll r, ll value) {
	//propagate(t, ind);
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		t[ind].min = (t[ind].min != LLONG_MAX ? max(t[ind].min, value) : value);
		//t[ind].op = SET;
		return;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return;
	}
	set(t, 2 * ind + 1, l, r, value);
	set(t, 2 * ind + 2, l, r, value);
	//t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
}

ll min(vector<Node> &t, ll ind, ll l, ll r) {
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		return t[ind].min;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return LLONG_MAX;
	}
	return min(min(t, 2 * ind + 1, l, r), min(t, 2 * ind + 2, l, r));
}

void MEGA_propagate(vector<Node> &t, Node node) {
	propagate(t, node.ind);
	if (node.leftBorder != node.rightBorder) {
		MEGA_propagate(t, t[2 * node.ind + 1]);
		MEGA_propagate(t, t[2 * node.ind + 2]);
	}
}
struct tr {
	ll a, b, res;
};
int main() {
	ifstream cin("rmq.in");
	ofstream cout("rmq.out");

	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, m;
	cin >> n >> m;
	ll sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	vector<Node>t(2 * sz - 1);
	build(t, 0, sz - 1, 2 * sz - 2);
	vector<tr>r(m);
	for (ll i = 0; i < m; i++) {
		cin >> r[i].a >> r[i].b >> r[i].res;
		set(t, 0, r[i].a - 1 + sz - 1, r[i].b - 1 + sz - 1, r[i].res);
	}

	MEGA_propagate(t, t[0]);

	build(t, 0, sz - 1, 2 * sz - 2);

	for (ll i = 0; i < m; i++) {
		if (min(t, 0, r[i].a - 1 + sz - 1, r[i].b - 1 + sz - 1) != r[i].res) {
			cout << "inconsistent";
			return 0;
		}
	}
	cout << "consistent" << endl;
	for (ll i = sz - 1; i < sz - 1 + n; i++) {
		cout << (t[i].min == LLONG_MAX ? INT_MAX : t[i].min) << ' ';
	}

	return 0;
}