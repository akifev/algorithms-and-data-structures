#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
vector<ll> d;
vector<map<ll, ll>> graph;
vector<ll> parent;
vector<vector<ll>> dp;
//vector<vector<ll>> mn;
void pre() {
	for (ll diff = 0; diff < dp[0].size(); diff++)
		for (ll cur = 0; cur < dp.size(); cur++) {
			dp[cur][diff] = (diff ? dp[dp[cur][diff - 1]][diff - 1] : parent[cur]);
			//mn[cur][diff] = (diff ? min(mn[cur][diff - 1], mn[dp[cur][diff - 1]][diff - 1]) : graph[parent[cur]][cur]);
		}
}
vector<bool> used;
void dfs(ll current) {
	used[current] = true;
	for (auto x : graph[current]) {
		ll next = x.first;
		d[next] = d[current] + 1;
		parent[next] = current;
		if (!used[next])
			dfs(next);
	}
}
vector<bool> to_bin(ll n) {
	vector<bool> res;
	while (n > 0) {
		res.push_back((bool)(n % 2));
		n /= 2;
	}
	return res;
}
ll lca(ll hi, ll lo) {
	if (d[lo] < d[hi])
		swap(hi, lo);
	vector<bool> jmp = to_bin(d[lo] - d[hi]);
	for (ll i = 0; i < jmp.size(); i++)
		if (jmp[i])
			lo = dp[lo][i];
	while (parent[hi] != parent[lo]) {
		ll ind = 1;
		while (dp[hi][ind] != dp[lo][ind])
			ind++;
		hi = dp[hi][ind - 1];
		lo = dp[lo][ind - 1];
	}
	return lo == hi ? hi : parent[hi];
}/*
ll get_min(ll lca, ll v, ll u) {
	ll result = INT_MAX;
	vector<bool> lca_v = to_bin(d[v] - d[lca]);
	for (ll i = 0; i < lca_v.size(); i++)
		if (lca_v[i]) {
			result = min(result, mn[v][i]);
			v = dp[v][i];
		}
	vector<bool> lca_u = to_bin(d[u] - d[lca]);
	for (ll i = 0; i < lca_u.size(); i++)
		if (lca_u[i]) {
			result = min(result, mn[u][i]);
			u = dp[u][i];
		}
	return result;
}*/
int main() {
	//ifstream cin("minonpath.in");
	//ofstream cout("minonpath.out");
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n, m;
	cin >> n;
	d.resize(n, 0);
	graph.resize(n);
	parent.resize(n);
	//mn.resize(n, vector<ll>(ceil(log2(n)), INT_MAX));
	dp.resize(n, vector<ll>(ceil(log2(n)), 0));
	used.resize(n, false);
	for (ll i = 1; i < n; i++) {
		ll p;
		cin >> p;
		graph[p - 1][i] = 1;
	}
	dfs(0);
	pre();
	cin >> m;
	for (ll i = 0; i < m; i++) {
		ll v, u;
		cin >> v >> u;
		cout << lca(v - 1, u - 1) + 1 << endl;
	}
	return 0;
}