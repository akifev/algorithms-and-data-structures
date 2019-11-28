#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
ll r, sz;
class Node {
public:
	ll k = 1;
	ll l = 0;
	ll m = 0;
	ll n = 1;
	Node() {};
	Node(ll a, ll b, ll c, ll d) {
		k = a;
		l = b;
		m = c;
		n = d;
	}
};
ostream& operator<<(ostream& out, const Node &right) {
	out << right.k << ' ' << right.l << endl << right.m << ' ' << right.n << endl;
	return out;
}
Node mul(Node fi, Node se) {
	return Node(
		(fi.k * se.k + fi.l * se.m) % r,
		(fi.k * se.l + fi.l * se.n) % r,
		(fi.m * se.k + fi.n * se.m) % r,
		(fi.m * se.l + fi.n * se.n) % r
	);
}

void build(vector<Node> &t, vector<Node> &a, size_t ind) {
	if (ind >= a.size() - 1) {
		t[ind] = a[(ind + 1) % a.size()];
	}
	else {
		build(t, a, 2 * ind + 1);
		build(t, a, 2 * ind + 2);
		t[ind] = mul(t[2 * ind + 1], t[2 * ind + 2]);
	}
}
Node multiply(vector<Node> &t, size_t l, size_t r, size_t ind, size_t lb, size_t rb) {
	if (l <= lb && r >= rb) {
		return t[ind];
	}
	if (r < lb || l > rb) {
		return Node();
	}
	return mul(multiply(t, l, r, 2 * ind + 1, lb, rb - (rb - lb + 1) / 2), multiply(t, l, r, 2 * ind + 2, lb + (rb - lb + 1) / 2, rb));
}
int main() {
	ifstream cin("crypto.in");
	ofstream cout("crypto.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, m;
	cin >> r >> n >> m;
	sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	vector<Node>a(sz);
	vector<Node>t(2 * sz - 1);
	for (size_t i = 0; i < n; i++) {
		cin >> a[i].k >> a[i].l >> a[i].m >> a[i].n;
	}
	build(t, a, 0);
	for (size_t i = 0; i < m; i++) {
		ll q, p;
		cin >> q >> p;
		cout << multiply(t, q - 1 + sz - 1, p - 1 + sz - 1, 0, sz - 1, 2 * sz - 2);
	}
	return 0;
}