#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define forna(i, a, n) for(ll i = a; i < n; ++i)
 
#define INF (ll)1e18
 
struct edge {
    ll from = 0;
    ll to = 0;
    ll capacity = 0;
    ll cost = 0;
    ll flow = 0;
    edge *reverse = nullptr;
 
    edge() = default;
 
    edge(ll from, ll to, ll capacity, ll cost) : from(from), to(to), capacity(capacity), cost(cost) {}
 
    ~edge() = default;
};
 
 
struct node {
    ll ind = 0;
    vector<edge *> list; // outgoing edges
 
    node() = default;
 
    node(ll ind) : ind(ind) {}
 
    ~node() = default;
 
    void add_edge(edge *e) {
        list.push_back(e);
    }
};
 
struct node2 {
    ll ind;
    ll d;
    ll pred;
    vector<ll> list; // outgoing edges
    vector<ll> costs;
};
 
struct graph {
    ll n = 0; // count of vertex
    ll m = 0; // count of edges
    ll k = 0;
    ll p = 0;
    ll size = 0;
    ll start = 0;
    ll finish = 0;
    vector<node> nodes;
    vector<edge> edges;
    vector<ll> potential;
    vector<edge *> previous;
    vector<node2> g;
    vector<ll> degree;
    vector<int> used;
 
    graph() = default;
 
    ~graph() = default;
 
    void resize() {
        g.resize(n);
        degree.resize(n, 0);
        used.resize(n, 0);
    }
 
    void resize2() {
        nodes.clear();
        previous.clear();
        potential.clear();
        nodes.resize(1 + size + k + 1);
        previous.resize(1 + size + k + 1);
        potential.resize(1 + size + k + 1, INF);
    }
 
    void make(ll col, ll index) {
        size = g[index].list.size();
        start = 0;
        finish = 1 + size + k;
        edges.clear();
        forn(i, size) {
            ll to = i + 1;
            edges.emplace_back(start, to, 1, 0);
            edges.emplace_back(to, start, 0, 0);
        }
        forn(i, size) {
            ll from = i + 1;
            forn(j, k) {
                ll to = 1 + size + j;
                if (from != to) {
                    if (j != col) {
                        edges.emplace_back(from, to, 1, g[g[index].list[i]].costs[j]);
                        edges.emplace_back(to, from, 0, -g[g[index].list[i]].costs[j]);
                    } else {
                        edges.emplace_back(from, to, 0, 0);
                        edges.emplace_back(to, from, 0, 0);
                    }
                }
            }
        }
        forn(i, k) {
            ll from = 1 + size + i;
            edges.emplace_back(from, finish, 1, 0);
            edges.emplace_back(finish, from, 0, 0);
        }
        m = edges.size() / 2;
        forn(i, m) {
            ll ind = 2 * i; // edge[ind] - cur edge ; edge[ind + 1] - reverse edge
            edges[ind].reverse = &edges[ind + 1];
            edges[ind + 1].reverse = &edges[ind];
        }
        resize2();
        forn(i, m) {
            ll ind = 2 * i;
            ll from = edges[ind].from;
            ll to = edges[ind].to;
            nodes[from].add_edge(&edges[ind]);
            nodes[to].add_edge(&edges[ind + 1]);
        }
    }
 
    void erase_pred(ll ind) {
        ll pred = 0;
        while (g[ind].list[pred] != g[ind].pred) {
            ++pred;
        }
        g[ind].list.erase(g[ind].list.begin() + pred);
    }
 
 
    ll dfs(ll ind) {
        if (used[g[ind].ind] == 0) {
            used[g[ind].ind] = 1;
        } else {
            return g[ind].d;
        }
        ll value = 0;
        forn(i, g[ind].list.size()) {
            if (g[g[ind].list[i]].ind != g[ind].pred) {
                g[g[ind].list[i]].pred = g[ind].ind;
                if (g[g[ind].list[i]].list.size() == 1) {
                    g[g[ind].list[i]].d = 0;
                } else {
                    value = max(value, dfs(g[ind].list[i]));
                }
            }
        }
        if (g[ind].pred != -1) {
            erase_pred(ind);
        }
        g[ind].d = ++value;
 
        if (value == 1) {
            return value;
        }
        forn(i, g[ind].list.size()) {
            if (g[g[ind].list[i]].d != 0) {
                ll cost = p;
                forn(r, g[g[ind].list[i]].list.size()) {
                    ll tmp = INF;
                    forn(j, g[g[g[ind].list[i]].list[r]].costs.size()) {
                        if (tmp > g[g[g[ind].list[i]].list[r]].costs[j]) {
                            tmp = g[g[g[ind].list[i]].list[r]].costs[j];
                        }
                    }
                    cost += tmp;
                }
                forn(j, k) {
                    ll min_cost = INF;
                    if (g[g[ind].list[i]].list.size() < k) {
                        make(j, g[ind].list[i]);
                        min_cost = mincost();
                    }
                    g[ind].costs[j] += min(cost, min_cost);
                }
            }
        }
        return value;
    }
 
    void read() {
        cin >> n >> k >> p;
        resize();
        forn(i, n) {
            g[i].ind = i;
            forn(j, k) {
                ll cost;
                cin >> cost;
                g[i].costs.push_back(cost);
            }
        }
        if (n == 1) {
            ll result = INF;
            forn(i, g[0].costs.size()) {
                if (result > g[0].costs[i]) {
                    result = g[0].costs[i];
                }
            }
            cout << result;
            return;
        }
 
        forn(i, n - 1) {
            ll from;
            ll to;
            cin >> from;
            cin >> to;
            from--;
            to--;
            degree[from]++;
            degree[to]++;
            g[from].list.push_back(to);
            g[to].list.push_back(from);
            g[from].pred = to;
            g[to].pred = from;
        }
        solve();
    }
 
    void solve() {
        ll index_max = 0;
        ll fake_max = degree[0];
        forn(i, degree.size()) {
            if (fake_max < degree[i]) {
                fake_max = degree[i];
                index_max = i;
            }
        }
        ll cost_top = p;
        g[index_max].pred = -1;
        dfs(index_max);
        ll result = INF;
        forn(i, g[index_max].costs.size()) {
            if (result > g[index_max].costs[i]) {
                result = g[index_max].costs[i];
            }
        }
        forn(i, g[index_max].list.size()) {
            ll tmp = INF;
            forn(j, g[g[index_max].list[i]].costs.size()) {
                if (tmp > g[g[index_max].list[i]].costs[j]) {
                    tmp = g[g[index_max].list[i]].costs[j];
                }
            }
            cost_top += tmp;
        }
        ll min_cost = INF;
        if (g[index_max].list.size() <= k) {
            make(-1, index_max);
            min_cost = mincost();
        }
        result += (cost_top < min_cost ? cost_top : min_cost);
        cout << result;
    }
 
    void ford_bellman() {
        forn(i, 1 + size + k + 1) {
            forn(j, 1 + size + k + 1) {
                if (potential[j] < INF) {
                    forn(qwe, nodes[j].list.size()) {
                        edge *e = nodes[j].list[qwe];
                        if (e->capacity > 0 && potential[e->to] > potential[j] + e->cost) {
                            potential[e->to] = potential[j] + e->cost;
                        }
                    }
                }
            }
        }
    }
 
    void init_potential() {
        potential[start] = 0;
        ford_bellman();
    }
 
    ll dijskra() {
        vector<ll> dist(1 + size + k + 1, INF);
        vector<int> used2(1 + size + k + 1, 0);
        dist[start] = 0;
        while (true) {
            ll cur = -1;
            forn(i, 1 + size + k + 1) {
                if (!used2[i] && dist[i] < INF && (cur == -1 || dist[i] < dist[cur])) {
                    cur = i;
                }
            }
            if (cur == -1) {
                break;
            }
            used2[cur] = 1;
            forn(i, nodes[cur].list.size()) {
                edge *e = nodes[cur].list[i];
                if (e->flow < e->capacity && !used2[e->to] &&
                    dist[cur] + e->cost + potential[cur] - potential[e->to] < dist[e->to]) {
                    dist[e->to] = dist[cur] + e->cost + potential[cur] - potential[e->to];
                    previous[e->to] = e;
                }
            }
        }
        forn(i, 1 + size + k + 1) {
            potential[i] += (dist[i] < INF ? dist[i] : dist[finish]);
        }
        return dist[finish];
    }
 
    pair<ll, ll> find_flow_cost() {
        ll cur = finish;
        ll cur_flow = INF;
        ll cur_cost = 0;
        while (cur != start) {
            cur_flow = min(cur_flow, previous[cur]->capacity - previous[cur]->flow);
            cur_cost += previous[cur]->cost;
            cur = previous[cur]->from;
        }
        return {cur_flow, cur_cost};
    }
 
    void update_flow(ll flow) {
        if (flow != 0) {
            ll cur = finish;
            while (cur != start) {
                previous[cur]->flow += flow;
                previous[cur]->reverse->flow -= flow;
                cur = previous[cur]->from;
            }
        }
    }
 
    ll mincost() {
        init_potential();
        ll distance = dijskra();
        ll min_cost = 0;
        while (distance != INF) {
            auto tmp = find_flow_cost();
            ll flow = tmp.first;
            ll cost = tmp.second;
            min_cost += flow * cost;
            update_flow(flow);
            distance = dijskra();
        }
        return min_cost;
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    graph task;
    task.read();
    return 0;
}