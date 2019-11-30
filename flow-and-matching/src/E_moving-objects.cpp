#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
 
int n;
int m;
int s;
int t;
 
enum class color {
    RED, WHITE
};
 
struct edge {
    int from = 0;
    int to = 0;
    long double f = 0;
    long double c = 0;
    edge *rev = nullptr;
//    int index = 0;
 
    edge() = default;
 
    edge(int from, int to, long double c) : from(from), to(to), f(0), c(c) {}
};
 
vector<edge> edges;
 
vector<vector<edge *>> fast_run;
 
vector<bool> used;
 
long double dfs(int cur, long double c) {
    if (cur == t) {
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
        ans = dfs(s, 1e12);
        fill(used.begin(), used.end(), false);
        maxans += ans;
    } while (ans > 1e-5);
    return maxans;
}
 
void draw(int cur) {
    used[cur] = true;
    for (int i = 0; i < fast_run[cur].size(); ++i) {
        edge *e = fast_run[cur][i];
        int next = e->to;
        if (!used[next] && e->c - e->f > 1e-5) {
            draw(next);
        }
    }
}
 
 
vector<edge *> incut;
 
vector<long double> speed;
vector<pair<long double, long double>> items;
 
void find_edges() {
    for (int i = 0; i < 2 * m; i += 2) {
        if (used[edges[i].from] ^ used[edges[i].to]) {
            incut.emplace_back(&edges[i]);
        }
    }
}
 
vector<int> pred;
 
void find_pred(int cur) {
    pred.emplace_back(cur);
    if (cur == t) {
        return;
    }
    for (auto it : fast_run[cur]) {
        int next = it->to;
        if (it->f == 1) {
            it->f = 0;
            find_pred(next);
            return;
        }
    }
}
 
vector<long double> dists;
 
long double dist(int a, int b) {
    long double dx = (items[a].first - items[b].first);
    long double dy = (items[a].second - items[b].second);
    return sqrt(dx * dx + dy * dy);
}
 
bool g(long double time) {
    edges.clear();
    fast_run.clear();
    fill(used.begin(), used.end(), false);
    for (int i = 1; i <= n; ++i) {
        edges.emplace_back(edge(0, i, 1));
        edges.emplace_back(edge(i, 0, 0));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (time - (dist(i, n + j + 1) / speed[i]) > 1e-5) {
                edges.emplace_back(edge(i, n + j + 1, 1));
                edges.emplace_back(edge(n + j + 1, i, 0));
            }
        }
    }
    for (int i = 1 + n; i <= m + n; ++i) {
        edges.emplace_back(edge(i, m + n + 1, 1));
        edges.emplace_back(edge(m + n + 1, i, 0));
    }
    fast_run.resize(m + n + 2);
    for (int i = 0; i < edges.size(); i += 2) {
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        fast_run[edges[i].from].emplace_back(&edges[i]);
        fast_run[edges[i].to].emplace_back(&edges[i + 1]);
    }
    return fabs(f() - n) < 1e-5;
}
 
long double binary_search() {
    long double l = 0;
    long double r = 1e5;
    for (int i = 0; i < 100; ++i) {
        long double m = (r + l) / 2;
        if (g(m)) r = m;
        else l = m;
    }
    return l;
}
 
 
int main() {
    cin >> n;
    m = n;
    s = 0;
    t = m + n + 1;
 
    used.resize(m + n + 2, false);
    speed.resize(m + n + 2, 0);
    items.resize(m + n + 2);
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            dists[i * n + j] = dist(i + 1, n + j + 1);
//        }
//    }
    for (int i = 0; i < n; ++i) {
        long double x;
        long double y;
        long double s;
        cin >> x;
        cin >> y;
        cin >> s;
        items[i + 1] = {x, y};
        speed[i + 1] = s;
    }
    for (int i = 0; i < n; ++i) {
        long double x;
        long double y;
        cin >> x;
        cin >> y;
        items[i + n + 1] = {x, y};
    }
 
 
    cout.precision(20);
    cout << binary_search();
    return 0;
}