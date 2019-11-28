#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
vector<vector<ll>> tree;
vector<ll> p;
vector<ll> depth;
vector<ll> d;
vector<map<ll, ll>> graph;
vector<ll> parent;
vector<vector<ll>> dp;
vector<vector<ll>> mn;
ll dfs(ll current, ll sz, ll &node, ll parent = -1) {
	ll ans = 1;
	for (ll edge : tree[current])
		if (depth[edge] == -1 && edge != parent)
			ans += dfs(edge, sz, node, current);
	if (node == -1 && (2 * ans >= sz || parent == -1))
		node = current;
	return ans;
}
void build(ll v, ll size, ll d, ll last) {
	ll center = -1;
	dfs(v, size, center);
	depth[center] = d;
	p[center] = last;
	for (ll edge : tree[center])
		if (depth[edge] == -1)
			build(edge, size / 2, d + 1, center);
}
void pre() {
	for (ll diff = 0; diff < dp[0].size(); diff++)
		for (ll cur = 0; cur < dp.size(); cur++) {
			dp[cur][diff] = (diff ? dp[dp[cur][diff - 1]][diff - 1] : parent[cur]);
			mn[cur][diff] = (diff ? min(mn[cur][diff - 1], mn[dp[cur][diff - 1]][diff - 1]) : graph[parent[cur]][cur]);
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
}
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
}
int main() {
	//ifstream cin("minonpath.in");
	//ofstream cout("minonpath.out");
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n;
	cin >> n;
	tree.resize(n);
	p.resize(n, 0);
	depth.resize(n, -1);
	for (ll i = 1; i < n; i++) {
		ll u, v;
		cin >> u >> v;
		u--;
		v--;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	build(0, n, 0, -1);
	ll beg = -1;
	beg = (find(p.begin(), p.end(), -1) - p.begin());
	vector<vector<ll>> tree_res(n);
	for (ll i = 0; i < n; i++)
		if (i != beg)
			tree_res[p[i]].push_back(i);
	vector<ll> our_answer(n);
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < tree_res[i].size(); j++)
			our_answer[tree_res[i][j]] = i;
	for (ll i = 0; i < n; i++)
		cout << (i == beg ? our_answer[i] : our_answer[i] + 1) << ' ';
	return 0;
}