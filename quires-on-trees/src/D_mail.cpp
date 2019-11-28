#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
typedef long long ll;
using namespace std;
ll n;
vector<ll>roditel;
vector<ll>glubina;
vector<ll>shirina;
vector<ll>visota;
vector<ll>way;
vector<vector<ll>>rebra;
vector<bool>heavy_node;
void resize(ll n) {
	rebra.resize(n);
	glubina.resize(n, 0);
	roditel.resize(n, 0);
	way.resize(n, 0);
	heavy_node.resize(n, false);
	shirina.resize(n, 0);
	visota.resize(n, 0);
}
class Tree {
public:
	ll king;
	ll tree_size;
	vector<ll> tree;
	map<ll, ll> trans;
	Tree(vector<ll> tr) {
		tree_size = tr.size();
		for (ll i = 0; i < tree_size; ++i) {
			trans.insert(make_pair(tr[i], i));
		}
		king = tr[tree_size - 1];
		tree_size = pow(2, ceil(log2(tree_size)));
		tree.resize(2 * tree_size - 1, 0);
		for (ll i = 0; i < tr.size(); i++)
			tree[tree_size - 1 + i] = visota[tr[i]];
		for (ll i = tree_size - 1; i > 0; i--)
			tree[i - 1] = max(tree[(i - 1) * 2 + 1], tree[(i - 1) * 2 + 2]);
	}
	void query(ll current, ll val) {
		ll index = tree_size - 1 + trans.at(current);
		tree[index] = val;
		while (index > 0) {
			index = (index - 1) / 2;
			tree[index] = max(tree[index * 2 + 1], tree[index * 2 + 2]);
		}
	}
	ll get_max(ll l, ll r) {
		return find_max(0, 0, tree_size, trans.at(l), trans.at(r));
	}
private:
	ll find_max(ll node, ll left_border, ll right_border, ll l, ll r) {
		if (left_border >= r || l >= right_border)
			return 0;
		if (l <= left_border && right_border <= r)
			return tree[node];
		ll middle_border = left_border + (right_border - left_border) / 2;
		return max(find_max(node * 2 + 1, left_border, middle_border, l, r), find_max(node * 2 + 2, middle_border, right_border, l, r));
	}
};
vector<Tree> ivec;

ll get_lca(ll u, ll v) {
	return (way[u] == way[v] ? (glubina[u] < glubina[v] ? u : v) : glubina[ivec[way[u]].king] > glubina[ivec[way[v]].king] ? get_lca(ivec[way[u]].king, v) : get_lca(u, ivec[way[v]].king));
}

ll build_dfs(ll current, ll par, ll d) {
	roditel[current] = par;
	glubina[current] = d;
	ll m_w = 0;
	ll heavy = 0;
	ll w = 0;
	for (auto next : rebra[current])
		if (next != par) {
			w = build_dfs(next, current, d + 1);
			shirina[current] += w;
			if (m_w < w) {
				heavy = next;
				m_w = w;
			}
		}
	if (d == 0 || rebra[current].size() > 1)
		heavy_node[heavy] = true;
	shirina[current]++;
	return shirina[current];
}

void build() {
	build_dfs(0, 0, 0);
	for (ll i = 1; i < rebra.size(); ++i) {
		if (rebra[i].size() == 1) {
			ll node = i;
			vector<ll> my_vec;
			while (heavy_node[node]) {
				my_vec.push_back(node);
				way[node] = ivec.size();
				node = roditel[node];
			}
			way[node] = ivec.size();
			my_vec.push_back(node);
			if (node)
				my_vec.push_back(node = roditel[node]);
			ivec.push_back(Tree(move(my_vec)));
		}
	}

	way[0] = way[1];
}

void set(ll v, ll h) {
	ivec[way[v]].query(v, h);
}
void function(ll &res, ll &node, ll &myLCA, ll&myTOP) {
	while (way[node] != way[myLCA]) {
		res = max(res, ivec[way[node]].get_max(node, myTOP));
		node = myTOP;
		myTOP = ivec[way[node]].king;
	}
}
ll get(ll u, ll v) {
	ll answer = 0;
	ll lca_uv = get_lca(u, v);
	ll kng = ivec[way[u]].king;
	if (way[u] != way[v])
		function(answer, u, lca_uv, kng);
	if (way[u] != way[v]) {
		kng = ivec[way[v]].king;
		function(answer, v, lca_uv, kng);
	}
	answer = max(visota[lca_uv], max(answer, ivec[way[lca_uv]].get_max(glubina[u] > glubina[v] ? u : v, glubina[u] < glubina[v] ? u : v)));
	return answer;
}
int main() {
	ifstream cin("mail.in");
	ofstream cout("mail.out");
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n;
	cin >> n;
	resize(4 * n);
	for (ll i = 1; i <= n; i++)
		cin >> visota[i];
	rebra[0].push_back(1);
	rebra[1].push_back(0);
	for (ll i = 1; i < n; ++i) {
		ll u, v;
		cin >> u >> v;
		rebra[u].push_back(v);
		rebra[v].push_back(u);
	}
	build();
	ll m;
	cin >> m;
	for (ll i = 0; i < m; ++i) {
		ll u, v;
		char op;
		cin >> op >> u >> v;
		if (op != '?') {
			set(u, v);
			visota[u] = v;
		}
		else
			cout << get(u, v) << endl;
	}
	return 0;
}