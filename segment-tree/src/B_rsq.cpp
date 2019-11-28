#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
void build(vector<ll> &t, vector<ll> &a, size_t ind) {
	if (ind >= a.size() - 1) {
		t[ind] = a[(ind + 1) % a.size()];
	}
	else {
		build(t, a, 2 * ind + 1);
		build(t, a, 2 * ind + 2);
		t[ind] = t[2 * ind + 1] + t[2 * ind + 2];
	}
}
ll sum(vector<ll> &t, size_t l, size_t r, size_t ind, size_t lb, size_t rb) {
	if (l <= (lb + 1) % ((t.size() + 1) / 2) && r >= (rb + 1) % ((t.size() + 1) / 2)) {
		return t[ind];
	}
	if ((lb + 1) % ((t.size() + 1) / 2) > r || (rb + 1) % ((t.size() + 1) / 2) < l) {
		return 0;
	}
	return sum(t, l, r, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2) + sum(t, l, r, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb);
}
void update(vector<ll>&, size_t);
void set(vector<ll> &t, size_t ind, ll val) {
	t[(t.size() + 1) / 2 - 1 + ind] = val;
	update(t, (t.size() + 1) / 2 - 1 + ind);
}
void update(vector<ll> &t, size_t ind) {
	if (ind != 0) {
		t[(ind - 1) / 2] = t[2 * ((ind - 1) / 2) + 1] + t[2 * ((ind - 1) / 2) + 2];
		update(t, (ind - 1) / 2);
	}
}
int main() {
	ifstream cin("rsq.in");
	ofstream cout("rsq.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	ll size = 1;
	while (size < n) {
		size <<= 1;
	}
	vector<ll>a(size, 0), t(2 * size - 1);
	for (size_t i = 0; i < n; i++) {
		cin >> a[i];
	}
	build(t, a, 0);
	string op;
	while (cin >> op) {
		if (op == "sum") {
			size_t i, j;
			cin >> i >> j;
			cout << sum(t, i - 1, j - 1, 0, size - 1, 2 * size - 2) << endl;
		}
		else {
			size_t i;
			ll x;
			cin >> i >> x;
			set(t, i - 1, x);
		}
	}
	return 0;
}