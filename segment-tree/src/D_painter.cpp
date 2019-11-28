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
	DREW
};
struct Node {
	ll sum = 0;
	ll cnt = 0;
	ll left = 0;
	ll right = 0;
	operations op = NOOPERATIONS;
};
void lazy_propagation(vector<Node> &t, size_t p) {
	if (2 * p + 2 < t.size()) {
		if (t[p].op == NOOPERATIONS) return;
		t[2 * p + 1] = t[p];
		t[2 * p + 2] = t[p];
		t[2 * p + 1].sum /= 2;
		t[2 * p + 2].sum /= 2;
	}
	t[p].op = NOOPERATIONS;
}
void set(vector<Node> &t, size_t l, size_t r, ll val, size_t ind, size_t lb, size_t rb) {
	lazy_propagation(t, ind);
	if (l <= (lb + 1) % ((t.size() + 1) / 2) && r >= (rb + 1) % ((t.size() + 1) / 2)) {
		t[ind].sum = (rb - lb + 1)*val;
		t[ind].cnt = val;
		t[ind].left = val;
		t[ind].right = val;
		t[ind].op = DREW;
		return;
	}
	if ((lb + 1) % ((t.size() + 1) / 2) > r || (rb + 1) % ((t.size() + 1) / 2) < l) {
		return;
	}
	set(t, l, r, val, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2);
	set(t, l, r, val, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb);
	t[ind].sum = t[2 * ind + 1].sum + t[2 * ind + 2].sum;
	t[ind].cnt = t[2 * ind + 1].cnt + t[2 * ind + 2].cnt - (t[2 * ind + 1].right && t[2 * ind + 2].left ? 1 : 0);
	t[ind].left = t[2 * ind + 1].left;
	t[ind].right = t[2 * ind + 2].right;
}
int main() {
	ifstream cin("painter.in");
	ofstream cout("painter.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	vector <pair<char, pair<ll, ll>>>r(n);
	ll mi = LLONG_MAX, mx = LLONG_MIN;
	for (int i = 0; i < n; i++) {
		cin >> r[i].first >> r[i].second.first >> r[i].second.second;
		mi = min(mi, r[i].second.first);
		mx = max(mx, r[i].second.first + r[i].second.second);
	}
	ll size = 1;
	while (size < mx - mi + 1) {
		size <<= 1;
	}
	vector<Node>t(2 * size - 1);
	for (int i = 0; i < n; i++) {
		set(t, r[i].second.first - mi, r[i].second.first + r[i].second.second - 1 - mi, (r[i].first == 'B' ? 1 : 0), 0, size - 1, 2 * size - 2);
		cout << t[0].cnt << ' ' << t[0].sum << endl;
	}
	return 0;
}