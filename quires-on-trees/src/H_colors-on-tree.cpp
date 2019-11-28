#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
vector<ll> depth;
vector<map<ll, ll>> graph;
vector<ll> parent;
vector<vector<ll>> dp;
vector<int>last_node;
vector<int>node_color;
vector<int>sum;
void pre() {
	for (ll diff = 0; diff < dp[0].size(); diff++)
		for (ll cur = 0; cur < dp.size(); cur++)
			dp[cur][diff] = (diff ? dp[dp[cur][diff - 1]][diff - 1] : parent[cur]);
}
vector<bool> used;
void dfs(ll current) {
	used[current] = true;
	for (auto trans : graph[current]) {
		ll next = trans.first;
		depth[next] = depth[current] + 1;
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
	if (depth[lo] < depth[hi])
		swap(hi, lo);
	vector<bool> jmp = to_bin(depth[lo] - depth[hi]);
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
void dfs1(int current) {
	used[current] = true;
	for (auto trans : graph[current]) {
		ll next = trans.first;
		if (!used[next]) {
			dfs1(next);
			sum[current] += sum[next];
		}
	}
	if (last_node[node_color[current]] != -1)
		sum[lca(current, last_node[node_color[current]])]--;
	last_node[node_color[current]] = current;
}
int main() {
	//ifstream cin("minonpath.in");
	//ofstream cout("minonpath.out");
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n;
	cin >> n;
	n++;
	depth.resize(n, 0);
	graph.resize(n);
	parent.resize(n, 0);
	dp.resize(n, vector<ll>(ceil(log2(n)), 0));
	used.resize(n, false);
	last_node.resize(n, -1);
	node_color.resize(n);
	sum.resize(n, 1);
	for (ll i = 1; i < n; i++) {
		ll p, color;
		cin >> p >> color;
		graph[p][i] = 1;
		node_color[i] = color;
	}
	node_color[0] = 0;
	dfs(0);
	pre();
	fill(used.begin(), used.end(), false);
	dfs1(0);
	for (ll i = 1; i < n; i++)
		cout << sum[i] << ' ';
	return 0;
}