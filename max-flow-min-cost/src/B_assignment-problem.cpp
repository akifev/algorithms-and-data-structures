#include <vector>
#include <fstream>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define forna(i, a, n) for(ll i = a; i < n; ++i)
 
#define INF (ll)1e18
 
ifstream cin("assignment.in");
ofstream cout("assignment.out");
 
struct edge {
    ll from = 0;
    ll to = 0;
    ll capacity = 0;
    ll cost = 0;
    ll flow = 0;
    edge *reverse = nullptr;
 
    edge() {}
 
    edge(ll from, ll to, ll capacity, ll cost) : from(from), to(to), capacity(capacity), cost(cost) {}
};
 
 
struct node {
    ll ind = 0;
    vector<edge *> list; // outgoing edges
 
    node() {}
 
    node(ll ind) : ind(ind) {}
 
    void add_edge(edge *e) {
        list.push_back(e);
    }
};
 
struct graph {
    ll n = 0; // count of vertex
    ll m = 0; // count of edges
    ll start = 0;
    ll finish = 0;
    vector<node> nodes;
    vector<edge> edges;
    vector<ll> potential;
    vector<vector<ll>> w;
 
 
    vector<edge *> previous;
 
    graph() {}
 
    graph(ll n, ll m, ll start, ll finish) : n(n), m(m), start(start), finish(finish) {}
 
    void resize() {
        nodes.resize(2 * n + 2);
        previous.resize(2 * n + 2);
        w.resize(n, vector<ll>(n, 0));
        potential.resize(2 * n + 2, INF);
    }
 
    void read() {
        cin >> n;
        start = 0;
        finish = 2 * n + 1;
        resize();
        forn(i, n) {
            forn(j, n) {
                cin >> w[i][j];
            }
        }
        forna(i, start + 1, 1 + n) {
            edges.emplace_back(start, i, 1, 0);
            edges.emplace_back(i, start, 0, 0);
        }
        forna(i, start + 1, 1 + n) {
            forna(j, 1 + n, finish) {
                ll from = i;
                ll to = j;
                ll ind_from = i - 1;
                ll ind_to = j - 1 - n;
                edges.emplace_back(from, to, 1, w[ind_from][ind_to]);
                edges.emplace_back(to, from, 0, -w[ind_from][ind_to]);
            }
        }
        forna(i, 1 + n, finish) {
            edges.emplace_back(i, finish, 1, 0);
            edges.emplace_back(finish, i, 0, 0);
        }
        m = edges.size() / 2;
        forn(i, m) {
            ll ind = 2 * i; // edge[ind] - cur edge ; edge[ind + 1] - reverse edge
            edges[ind].reverse = &edges[ind + 1];
            edges[ind + 1].reverse = &edges[ind];
        }
        forn(i, m) {
            ll ind = 2 * i;
            ll from = edges[ind].from;
            ll to = edges[ind].to;
            nodes[from].add_edge(&edges[ind]);
            nodes[to].add_edge(&edges[ind + 1]);
        }
    }
 
    void ford_bellman() {
        forn(i, 2 * n + 2) {
            forn(j, 2 * n + 2) {
                if (potential[j] < INF) {
                    forn(k, nodes[j].list.size()) {
                        edge *e = nodes[j].list[k];
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
        vector<ll> dist(2 * n + 2, INF);
        vector<int> used(2 * n + 2, 0);
        dist[start] = 0;
        while (true) {
            ll cur = -1;
            forn(i, 2 * n + 2) {
                if (!used[i] && dist[i] < INF && (cur == -1 || dist[i] < dist[cur])) {
                    cur = i;
                }
            }
            if (cur == -1) {
                break;
            }
            used[cur] = 1;
            forn(i, nodes[cur].list.size()) {
                edge *e = nodes[cur].list[i];
                if (e->flow < e->capacity && !used[e->to] &&
                    dist[cur] + e->cost + potential[cur] - potential[e->to] < dist[e->to]) {
                    dist[e->to] = dist[cur] + e->cost + potential[cur] - potential[e->to];
                    previous[e->to] = e;
                }
            }
        }
        forn(i, 2 * n + 2) {
            potential[i] += dist[i];
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
        read();
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
 
    void accepted() {
        cout << mincost() << endl;
        forna(i, start + 1, 1 + n) {
            forn(j, nodes[i].list.size()) {
                edge *e = nodes[i].list[j];
                ll from = e->from;
                ll to = e->to;
                ll ind_from = from - 1;
                ll ind_to = to - 1 - n;
                if (e->flow == 1) {
                    cout << ind_from + 1 << ' ' << ind_to + 1 << '\n';
                }
            }
        }
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    graph taskA;
    taskA.accepted();
    return 0;
}