#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
ll sz = 1;
vector<ll>hashs;
struct Node {
	ll sum = 0;
	ll hashsum = 0;
	ll min = LLONG_MAX;
	ll max = LLONG_MIN;
	ll ind;
	ll rightBorder;
	ll leftBorder;
};
/*
ll hash_function(ll x) {
	return pow(x, 5);
}*/
void build(vector<Node> &t, vector <ll> &v, ll ind, ll leftBorder, ll rightBorder) {
	t[ind].ind = ind;
	t[ind].leftBorder = leftBorder;
	t[ind].rightBorder = rightBorder;
	if (leftBorder == rightBorder) {
		if (ind - sz + 1 < v.size()) {
			t[ind].sum = v[ind - sz + 1];
			t[ind].hashsum = hashs[v[ind - sz + 1]];
			t[ind].min = v[ind - sz + 1];
			t[ind].max = v[ind - sz + 1];
		}
		return;
	}
	build(t, v, 2 * ind + 1, leftBorder, (leftBorder + rightBorder) / 2);
	build(t, v, 2 * ind + 2, (leftBorder + rightBorder) / 2 + 1, rightBorder);
	t[ind].min = min(t[2 * ind + 1].min, t[2 * ind + 2].min);
	t[ind].max = max(t[2 * ind + 1].max, t[2 * ind + 2].max);
	t[ind].sum = t[2 * ind + 1].sum + t[2 * ind + 2].sum;
	t[ind].hashsum = t[2 * ind + 1].hashsum + t[2 * ind + 2].hashsum;
}
void update(vector<Node> &t, ll ind) {
	if (ind != 0) {
		t[(ind - 1) / 2].sum = t[((ind - 1) / 2) * 2 + 1].sum + t[((ind - 1) / 2) * 2 + 2].sum;
		t[(ind - 1) / 2].hashsum = t[((ind - 1) / 2) * 2 + 1].hashsum + t[((ind - 1) / 2) * 2 + 2].hashsum;
		t[(ind - 1) / 2].min = min(t[((ind - 1) / 2) * 2 + 1].min, t[((ind - 1) / 2) * 2 + 2].min);
		t[(ind - 1) / 2].max = max(t[((ind - 1) / 2) * 2 + 1].max, t[((ind - 1) / 2) * 2 + 2].max);
		update(t, (ind - 1) / 2);
	}
}
void set(vector<Node> &t, ll ind, ll value) {
	t[ind].sum = value;
	t[ind].hashsum = hashs[value];
	t[ind].min = value;
	t[ind].max = value;
	update(t, ind);
}
ll sum(vector<Node> &t, ll ind, ll l, ll r) {
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		return t[ind].sum;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return 0;
	}
	return sum(t, 2 * ind + 1, l, r) + sum(t, 2 * ind + 2, l, r);
}
ll hashsum(vector<Node> &t, ll ind, ll l, ll r) {
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		return t[ind].hashsum;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return 0;
	}
	return hashsum(t, 2 * ind + 1, l, r) + hashsum(t, 2 * ind + 2, l, r);
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
ll max(vector<Node> &t, ll ind, ll l, ll r) {
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		return t[ind].max;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return LLONG_MIN;
	}
	return max(max(t, 2 * ind + 1, l, r), max(t, 2 * ind + 2, l, r));
}
struct tr {
	ll t;
	ll x;
	ll y;
};
int main() {
	ifstream cin("permutation.in");
	ofstream cout("permutation.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	hashs.resize(n + 1);
	hashs[1] = 19;
	for (ll i = 2; i <= n; i++) {
		//	hashs[i] = hash_function(i);
		hashs[i] = hashs[i - 1] * 19;
	}
	vector<ll>a(n), pref_sum(n + 1), pref_hash_sum(n + 1);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	pref_sum[0] = 0;
	pref_hash_sum[0] = 0;
	for (ll i = 1; i <= n; i++) {
		pref_sum[i] = pref_sum[i - 1] + i;
		pref_hash_sum[i] = pref_hash_sum[i - 1] + hashs[i];
	}
	while (sz < n) {
		sz <<= 1;
	}
	vector<Node>t(2 * sz - 1);
	build(t, a, 0, sz - 1, 2 * sz - 2);
	ll m;
	cin >> m;
	for (ll i = 0; i < m; i++) {
		ll type, x, y;
		cin >> type >> x >> y;
		if (type == 1) {
			set(t, x - 1 + sz - 1, y);
		}
		else {
			ll diff = y - x + 1;
			cout << ((min(t, 0, x - 1 + sz - 1, y - 1 + sz - 1) == 1 && max(t, 0, x - 1 + sz - 1, y - 1 + sz - 1) == diff && sum(t, 0, x - 1 + sz - 1, y - 1 + sz - 1) == pref_sum[diff] && hashsum(t, 0, x - 1 + sz - 1, y - 1 + sz - 1) == pref_hash_sum[diff]) ? "YES" : "NO");
			cout << endl;
		}
	}
	return 0;
}