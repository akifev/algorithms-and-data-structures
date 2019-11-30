#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
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
 
vector <edge> edges;
 
vector <vector<edge *>> fast_run;
 
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
 
int main() {
    cin >> n;
    cin >> m;
    s = 0;
    t = m + n + 1;
    for (int from = 1; from <= n; ++from) {
        int to = 1;
        cin >> to;
        while (to != 0) {
            to += n;
            edges.emplace_back(edge(from, to, 1));
            edges.emplace_back(edge(to, from, 0));
            cin >> to;
        };
    }
 
    for (int i = 1; i <= n; ++i) {
        edges.emplace_back(edge(0, i, 1));
        edges.emplace_back(edge(i, 0, 0));
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
    used.resize(m + n + 2, false);
    cout.precision(20);
    cout << f() << endl;
 
    std::vector<edge *> ps;
 
    for (int i = 0; i < edges.size(); i += 2) {
        edge *e = &edges[i];
        if (e->f == 1 && e->from != 0 && e->to != n + m + 1) {
            ps.emplace_back(e);
        }
    }
 
    for (auto e:ps) {
        cout << e->from << ' ' << e->to - n << endl;
    }
    return 0;
}