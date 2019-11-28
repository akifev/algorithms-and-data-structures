#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
enum operations {
	NOOPERATIONS,
	SET,
	ADD
};
struct Node {
	ll min = 0;
	ll add = 0;
	operations op = NOOPERATIONS;
};
void build(vector<Node> &t, vector<ll> &a, size_t ind) {
	if (ind >= a.size() - 1) {
		t[ind].min = a[(ind + 1) % a.size()];
	}
	else {
		build(t, a, 2 * ind + 1);
		build(t, a, 2 * ind + 2);
		t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
	}
}
void lazy_propagation(vector<Node> &t, size_t p) {
	if (2 * p + 2 < t.size()) {
		switch (t[p].op) {
		case SET:
			t[2 * p + 1].min = t[p].min;
			t[2 * p + 2].min = t[p].min;
			t[2 * p + 1].op = SET;
			t[2 * p + 2].op = SET;
			break;
		case ADD:
			t[2 * p + 1].min += t[p].add;
			t[2 * p + 2].min += t[p].add;
			if (t[2 * p + 1].op != SET) {
				t[2 * p + 1].add += t[p].add;
				t[2 * p + 1].op = ADD;
			}
			if (t[2 * p + 2].op != SET) {
				t[2 * p + 2].add += t[p].add;
				t[2 * p + 2].op = ADD;
			}
			break;
		}
	}
	t[p].op = NOOPERATIONS;
	t[p].add = 0;
}
ll min(vector<Node> &t, size_t l, size_t r, size_t ind, size_t lb, size_t rb) {
	lazy_propagation(t, ind);
	if (l <= (lb + 1) % ((t.size() + 1) / 2) && r >= (rb + 1) % ((t.size() + 1) / 2)) {
		return t[ind].min;
	}
	if ((lb + 1) % ((t.size() + 1) / 2) > r || (rb + 1) % ((t.size() + 1) / 2) < l) {
		return LLONG_MAX;
	}
	return min(min(t, l, r, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2), min(t, l, r, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb));
}
void set(vector<Node> &t, size_t l, size_t r, ll val, size_t ind, size_t lb, size_t rb) {
	lazy_propagation(t, ind);
	if (l <= (lb + 1) % ((t.size() + 1) / 2) && r >= (rb + 1) % ((t.size() + 1) / 2)) {
		t[ind].min = val;
		t[ind].op = SET;
		return;
	}
	if ((lb + 1) % ((t.size() + 1) / 2) > r || (rb + 1) % ((t.size() + 1) / 2) < l) {
		return;
	}
	set(t, l, r, val, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2);
	set(t, l, r, val, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb);
	t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
}
void add(vector<Node> &t, size_t l, size_t r, ll val, size_t ind, size_t lb, size_t rb) {
	lazy_propagation(t, ind);
	if (l <= (lb + 1) % ((t.size() + 1) / 2) && r >= (rb + 1) % ((t.size() + 1) / 2)) {
		t[ind].min += val;
		t[ind].op = ADD;
		t[ind].add = val;
		return;
	}
	if ((lb + 1) % ((t.size() + 1) / 2) > r || (rb + 1) % ((t.size() + 1) / 2) < l) {
		return;
	}
	add(t, l, r, val, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2);
	add(t, l, r, val, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb);
	t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
}
int main() {
	ifstream cin("rmq2.in");
	ofstream cout("rmq2.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	ll size = 1;
	while (size < n) {
		size <<= 1;
	}
	vector<ll>a(size, LLONG_MAX);
	vector<Node>t(2 * size - 1);
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(t, a, 0);
	string op;
	while (cin >> op) {
		if (op == "min") {
			size_t i, j;
			cin >> i >> j;
			cout << min(t, i - 1, j - 1, 0, size - 1, 2 * size - 2) << endl;
		}
		else {
			if (op == "set") {
				size_t i, j;
				ll x;
				cin >> i >> j >> x;
				set(t, i - 1, j - 1, x, 0, size - 1, 2 * size - 2);
			}
			else {
				size_t i, j;
				ll x;
				cin >> i >> j >> x;
				add(t, i - 1, j - 1, x, 0, size - 1, 2 * size - 2);
			}
		}
	}
	return 0;
}