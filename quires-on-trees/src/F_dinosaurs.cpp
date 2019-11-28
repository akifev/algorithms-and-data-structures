#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
ll max_n = 200000;
ll _qval = 0;
ll log_n = ceil(log2(max_n));
vector<vector<ll>>trans;
vector<vector<ll>>dp;
vector<ll>par;
vector<ll>d;
vector<ll>_2;
struct foo {
	vector<ll>par;
	vector<ll>rg;
	vector<ll>tr;
	vector<bool>is_broke;
	foo(ll sz) {
		rg.resize(sz, 0);
		par.resize(sz);
		tr.resize(sz);
		is_broke.resize(sz);
		for (ll i = 0; i < sz; i++) {
			par[i] = i;
			tr[i] = i;
		}
	}
	void _un(ll x, ll y) {
		ll _x = x;
		ll _y = y;
		x = _par(x);
		y = _par(y);
		ll next = d[_x] < d[_y] ? tr[x] : tr[y];
		if (x == y) return;
		if (rg[x] == rg[y])
			rg[x]++;
		if (rg[x] > rg[y]) {
			par[y] = x;
			tr[x] = next;
		}
		else {
			par[x] = y;
			tr[y] = next;
		}
	}
	ll _par(ll x) {
		return x == par[x] ? par[x] : _par(par[x]);
	}
	ll _next(ll x) {
		return tr[_par(x)];
	}
};
foo DSU_tree(max_n);
void resize() {
	par.resize(max_n);
	d.resize(max_n);
	trans.resize(max_n);
	dp.resize(max_n, vector<ll>(log_n + 1));
	_2.resize(ceil(log2(max_n)) + 1);
}
void pre() {
	_2[0] = 1;
	for (int i = 1; i < log_n + 1; i++) {
		_2[i] = _2[i - 1] * 2;
	}
}
void add(ll v) {
	par[++_qval] = v;
	dp[_qval][0] = v;
	d[_qval] = d[v] + 1;
	trans[v].push_back(_qval);
	for (int j = 1; j < log_n; j++)
		dp[_qval][j] = dp[dp[_qval][j - 1]][j - 1];
}
void del(ll v) {
	DSU_tree.is_broke[v] = true;
	DSU_tree.tr[v] = DSU_tree.tr[par[v]];
	if (DSU_tree.is_broke[par[v]])
		DSU_tree._un(v, par[v]);
	for (int u : trans[v])
		if (DSU_tree.is_broke[u])
			DSU_tree._un(u, v);
}
ll lca(ll fi, ll se) {
	if (d[fi] > d[se])
		swap(fi, se);
	for (int i = log_n - 1; i >= 0; i--)
		if (d[se] - d[fi] >= _2[i])
			se = dp[se][i];
	if (fi == se)
		return fi;
	for (int i = log_n - 1; i >= 0; i--)
		if (dp[fi][i] != dp[se][i]) {
			fi = dp[fi][i];
			se = dp[se][i];
		}
	return DSU_tree._next(par[fi]);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll m;
	cin >> m;
	resize();
	pre();
	for (int i = 0; i < m; i++) {
		char op;
		ll val;
		cin >> op >> val;
		if (op == '+')
			add(val - 1);
		else if (op == '-')
			del(val - 1);
		else {
			ll rb;
			cin >> rb;
			cout << (lca(val - 1, rb - 1) + 1) << endl;
		}
	}
	return 0;
}