#include <vector>
#include <fstream>
#include <queue>
#include <set>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define forna(i, a, n) for(ll i = a; i < n; ++i)
 
#define INF (ll)1e18
 
ifstream cin("mincost.in");
ofstream cout("mincost.out");
 
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
 
    vector<edge *> previous;
 
    graph() {}
 
    graph(ll n, ll m, ll start, ll finish) : n(n), m(m), start(start), finish(finish) {}
 
    void resize() {
        nodes.resize(n);
        previous.resize(n);
    }
 
    void read() {
        cin >> n;
        cin >> m;
        start = 0;
        finish = n - 1;
        resize();
        forn(i, m) {
            ll from, to, capacity, cost;
            cin >> from >> to >> capacity >> cost;
            --from;
            --to;
            edges.emplace_back(from, to, capacity, cost);
            edges.emplace_back(to, from, 0, -cost);
        }
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
 
    ll dijskra() {
        vector<ll> dist(n, INF);
        dist[start] = 0;
        set<pair<ll, ll>> vertexes;
        vertexes.insert({dist[start], start});
        while (!vertexes.empty()) {
            auto top = vertexes.begin();
            ll cur = top->second;
            ll cost = top->first;
            vertexes.erase(top);
            forn(i, nodes[cur].list.size()) {
                edge *e = nodes[cur].list[i];
                if (dist[cur] != INF && e->flow < e->capacity && dist[cur] + e->cost < dist[e->to]) {
                    dist[e->to] = dist[cur] + e->cost;
                    previous[e->to] = e;
                    vertexes.insert({dist[e->to], e->to});
                }
            }
        }
        return dist[finish];
    }
 
    ll find_flow() {
        ll cur = finish;
        ll cur_flow = INF;
        while (cur != start) {
            cur_flow = min(cur_flow, previous[cur]->capacity - previous[cur]->flow);
            cur = previous[cur]->from;
        }
        return cur_flow;
    }
 
    void update_flow(ll &flow) {
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
        ll distance = dijskra();
        ll min_cost = 0;
        while (distance != INF) {
            ll flow = find_flow();
            min_cost += flow * distance;
            update_flow(flow);
            distance = dijskra();
        }
        return min_cost;
    }
 
    void accepted() {
        cout << mincost();
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    graph taskA;
    taskA.accepted();
    return 0;
}