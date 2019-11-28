#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n;
void build(vector <ll> &t, ll ind, ll lb, ll rb) {
	if (2 * ind + 2 < t.size()) {
		build(t, 2 * ind + 1, lb, (lb + rb) / 2);
		build(t, 2 * ind + 2, (lb + rb) / 2 + 1, rb);
		t[ind] = t[2 * ind + 1] + t[2 * ind + 2];
	}
	else {
		if (lb < n)
			t[ind] = 1;
	}
}
void update(vector<ll> &t, ll ind) {
	if (ind != 0) {
		t[(ind - 1) / 2] = t[2 * ((ind - 1) / 2) + 1] + t[2 * ((ind - 1) / 2) + 2];
		update(t, (ind - 1) / 2);
	}
}
void set(vector <ll> &t, ll ind, ll val) {
	t[ind] = val;
	update(t, ind);
}
ll sum(vector <ll> &t, ll ind, ll lb, ll rb, ll l, ll r) {
	if (lb >= l && rb <= r) {
		return t[ind];
	}
	if (rb < l || r < lb) {
		return 0;
	}
	return sum(t, 2 * ind + 1, lb, (lb + rb) / 2, l, r) + sum(t, 2 * ind + 2, (lb + rb) / 2 + 1, rb, l, r);
}

ll findK(vector <ll> &t, ll ind, ll lb, ll rb, ll k) {
	if (2 * ind + 2 < t.size()) {
		if (t[2 * ind + 1] >= k) {
			return findK(t, 2 * ind + 1, lb, (lb + rb) / 2, k);
		}
		else {
			return findK(t, 2 * ind + 2, (lb + rb) / 2 + 1,
				rb, k - t[2 * ind + 1]);
		}
	}
	else {
		return ind;
	}
}

int main() {
	ifstream cin("parking.in");
	ofstream cout("parking.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll m;
	cin >> n >> m;
	ll sz = 1;
	while (sz < n) {
		sz <<= 1;
	}
	vector <ll> t(2 * sz - 1);
	build(t, 0, 0, sz - 1);
	for (ll i = 0; i < m; i++) {
		string op;
		cin >> op;
		ll index;
		cin >> index;
		if (op == "enter") {
			ll pref = sum(t, 0, sz - 1, 2 * sz - 2, sz - 1, sz - 1 + index - 2);
			ll suff = sum(t, 0, sz - 1, 2 * sz - 2, sz - 1 + index - 1, 2 * sz - 2);
			if (suff > 0) {
				ll ans = findK(t, 0, sz - 1, 2 * sz - 2, pref + 1);
				cout << ans - sz + 2;
				set(t, ans, 0);
			}
			else {
				ll ans = findK(t, 0, sz - 1, 2 * sz - 2, 1);
				cout << ans - sz + 2;
				set(t, ans, 0);
			}
			cout << endl;
		}
		else {
			set(t, sz + index - 2, 1);
		}
	}
	return 0;
}