#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
vector<vector<ll>>trans;
vector<ll>parent;
vector<ll>position;
vector<ll>king;
vector<ll>s;
vector<bool>used;
vector<ll>depth;
ll n, index;
enum operation {
	NO, ADD
};
struct Node {
	operation op = NO;
	ll val = 0;
	ll add = 0;
};
vector<Node>tree;
void lazy_propagation(ll current) {
	if (current < pow(2, ceil(log2(n))) - 1)
		if (tree[current].op == ADD) {
			ll left_child = current * 2 + 1;
			ll right_child = current * 2 + 2;
			tree[left_child].val += tree[current].add;
			tree[right_child].val += tree[current].add;
			tree[left_child].add += tree[current].add;
			tree[right_child].add += tree[current].add;
			tree[current].op = NO;
			tree[current].add = 0;
		}
}
ll find_ans(ll current, ll left_border, ll right_border) {
	lazy_propagation(current);
	return (right_border - left_border == 1 ? tree[current].val : (index < (left_border + right_border) / 2 ? find_ans(current * 2 + 1, left_border, (left_border + right_border) / 2) : find_ans(current * 2 + 2, (left_border + right_border) / 2, right_border)));
}
ll query_get(ll node) {
	index = position[node];
	return find_ans(0, 0, n);
}
void build_dfs(ll current) {
	used[current] = true;
	for (ll i = 0; i < trans[current].size(); i++) {
		ll next = trans[current][i];
		if (!used[next]) {
			parent[next] = current;
			depth[next] = depth[current] + 1;
			build_dfs(next);
		}
	}
}
void build_second_dfs(ll current, ll kng) {
	king[current] = kng;
	static ll c = 0;
	position[current] = c++;
	ll heavy = -1;
	ll sz = 0;
	for (auto next : trans[current])
		if (parent[current] != next)
			if (sz < s[next]) {
				sz = s[next];
				heavy = next;
			}
	if (heavy != -1)
		build_second_dfs(heavy, kng);
	for (auto next : trans[current])
		if (next != parent[current] && next != heavy)
			build_second_dfs(next, next);
}
void add_in_tree(ll current, ll left_border, ll right_border, ll left_index, ll right_index, ll d) {
	if (right_border == right_index && left_border == left_index) {
		tree[current].val += d;
		tree[current].add += d;
		tree[current].op = ADD;
	}
	else {
		ll middle_border = (left_border + right_border) / 2;
		ll left_child = current * 2 + 1;
		ll right_child = current * 2 + 2;
		lazy_propagation(current);
		if (left_index < middle_border)
			add_in_tree(left_child, left_border, middle_border, left_index, min(right_index, middle_border), d);
		if (right_index > middle_border) {
			add_in_tree(right_child, middle_border, right_border, max(middle_border, left_index), right_index, d);
		}
		lazy_propagation(left_child);
		lazy_propagation(right_child);
		tree[current].val = tree[left_child].val + tree[right_child].val;
	}
}
ll pre_dfs(ll current) {
	ll sz = 0;
	for (ll i = 0; i < trans[current].size(); ++i)
		if (parent[current] != trans[current][i])
			sz += pre_dfs(trans[current][i]);
	s[current] = (sz != 0 ? sz : 0) + 1;
	return s[current];
}
void query_add(ll v, ll u, ll d) {
	while (true) {
		if (king[v] == king[u]) {
			if (depth[v] > depth[u])
				swap(v, u);
			add_in_tree(0, 0, n, position[v], position[u] + 1, d);
			break;
		}
		if (depth[king[v]] < depth[king[u]])
			swap(v, u);
		add_in_tree(0, 0, n, position[king[v]], position[v] + 1, d);
		v = parent[king[v]];
	}
}
void build_hld() {
	build_dfs(0);
	pre_dfs(0);
	build_second_dfs(0, 0);
}

void resize() {
	trans.resize(n);
	used.resize(n, false);
	parent.resize(n, 0);
	position.resize(n);
	s.resize(n);
	king.resize(n);
	tree.resize(n * 4);
	depth.resize(n, 0);
}
void read_edges() {
	for (ll i = 1; i < n; i++) {
		ll u, v;
		cin >> u >> v;
		trans[u - 1].push_back(v - 1);
		trans[v - 1].push_back(u - 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	resize();
	read_edges();
	build_hld();
	ll m;
	cin >> m;
	for (ll i = 0; i < m; ++i) {
		ll v, u, depth;
		char op;
		cin >> op >> v;
		if (op == '?')
			cout << query_get(v - 1) << endl;
		else {
			cin >> u >> depth;
			query_add(v - 1, u - 1, depth);
		}
	}
	return 0;
}