#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int n;
int m;
 
struct edge {
    int from = 0;
    int to = 0;
    long double f = 0;
    long double c = 0;
    edge *rev = nullptr;
 
    edge() = default;
 
    edge(int from, int to, long double c) : from(from), to(to), f(0), c(c) {}
};
 
vector<edge> edges;
 
vector<vector<edge *>> fast_run;
 
vector<bool> used;
 
long double dfs(int cur, long double c) {
    if (cur == n - 1) {
        return c;
    }
    used[cur] = true;
    for (int i = 0; i < fast_run[cur].size(); ++i) {
        int next = fast_run[cur][i]->to;
        edge *e = fast_run[cur][i];
        if (!used[next] && e->f < e->c) {
            long double diff = dfs(next, min(e->c - e->f, c));
            if (diff > 1e-5) {
                e->f += diff;
                e->rev->f -= diff;
                return diff;
            }
        }
    }
    return 0;
}
 
long double f() {
    long double ans = 0;
    long double maxans = 0;
    do {
        ans = dfs(0, 1e9);
        fill(used.begin(), used.end(), false);
        maxans += ans;
    } while (ans > 1e-5);
    return maxans;
}
 
int main() {
    cin >> n;
    cin >> m;
    fast_run.resize(n, vector<edge *>());
 
    edges.resize(16 * m);
 
    for (int i = 0; i < 2 * m; i += 2) {
        int from;
        int to;
        long double c;
        cin >> from >> to >> c;
        from--;
        to--;
        edges[i] = edge(from, to, c);
        edges[i + 1] = edge(to, from, c);
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        fast_run[from].emplace_back(&edges[i]);
        fast_run[to].emplace_back(&edges[i + 1]);
    }
    used.resize(n, false);
    cout.precision(20);
    cout << f() << endl;
    for (int i = 0; i < 2 * m; i += 2) {
        cout << edges[i].f << '\n';
    }
    return 0;
}