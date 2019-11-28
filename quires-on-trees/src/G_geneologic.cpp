//_CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
ll n;
vector<ll> vhod;
vector<ll> depth;
vector<vector<ll>> dp;
vector<ll> parent;
vector<vector<ll>> graph;
void pre() {
	for (ll diff = 0; diff < dp[0].size(); diff++)
		for (ll current = 0; current < dp.size(); current++)
			dp[current][diff] = (diff != 0 ? dp[dp[current][diff - 1]][diff - 1] : parent[current]);
}
vector<bool> used;
void dfs(ll current) {
	static ll time = 0;
	vhod[current] = time++;
	used[current] = true;
	for (auto x : graph[current]) {
		ll next = x;
		depth[next] = depth[current] + 1;
		parent[next] = current;
		if (!used[next])
			dfs(next);
	}
}

ll lca(ll hi, ll lo) {
	if (depth[lo] < depth[hi])
		swap(hi, lo);
	ll jmp = depth[lo] - depth[hi];
	for (int i = 0; jmp > 0; i++) {
		if (jmp % 2 == 1) {
			lo = dp[lo][i];
		}
		jmp /= 2;
	}
	while (parent[hi] != parent[lo]) {
		ll ind = 1;
		while (dp[hi][ind] != dp[lo][ind])
			ind++;
		hi = dp[hi][ind - 1];
		lo = dp[lo][ind - 1];
	}
	return lo == hi ? hi : parent[hi];
}

void read(ll &start) {
	for (ll i = 0; i < n; ++i) {
		ll par;
		//cin >> parent;
		scanf("%lld", &par);
		if (par == -1) {
			start = i;
		}
		else {
			graph[par - 1].push_back(i);
		}
	}
}
int main() {
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cin >> n;
	scanf("%lld", &n);
	ll start = 0;
	ll m;
	vhod.resize(n, 0);
	graph.resize(n);
	used.resize(n, false);
	parent.resize(n, 0);
	dp.resize(n, vector<ll>(ceil(log2(n + 1))));
	depth.resize(n, 0);
	read(start);
	dfs(start);
	pre();
	//cin >> m;
	scanf("%lld", &m);
	ll cnt, nmbr;
	vector<pair<ll, ll>> m_set;
	for (ll q = 0; q < m; q++) {
		//cin >> cnt;
		scanf("%lld", &cnt);
		for (ll i = 0; i < cnt; ++i) {
			//cin >> nmbr;
			scanf("%lld", &nmbr);
			m_set.push_back(make_pair(vhod[nmbr - 1], nmbr - 1));
		}
		sort(m_set.begin(), m_set.end());
		ll result = 0;
		ll p = 0;
		for (ll i = 0; i < cnt; ++i) {
			result += (i != 0 ? depth[m_set[i].second] - depth[lca(p, m_set[i].second)] : depth[m_set[i].second]);
			p = m_set[i].second;
		}
		m_set.clear();
		//cout << result + 1 << endl;
		printf("%d\n", result + 1);
	}
	return 0;
}