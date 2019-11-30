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
    int index = 0;
 
    edge() = default;
 
    edge(int from, int to, long double c, int index) : from(from), to(to), f(0), c(c), index(index) {}
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
    cin >> s;
    cin >> t;
    s--;
    t--;
    fast_run.resize(n, vector<edge *>());
 
    edges.resize(16 * m);
 
    for (int i = 0; i < 2 * m; i += 2) {
        int from;
        int to;
        long double c;
        cin >> from >> to;
        from--;
        to--;
        edges[i] = edge(from, to, 1, i);
        edges[i + 1] = edge(to, from, 0, i + 1);
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        fast_run[from].emplace_back(&edges[i]);
        fast_run[to].emplace_back(&edges[i + 1]);
    }
    used.resize(n, false);
    cout.precision(20);
    long double F = f();
    if (F < 2) {
        cout << "NO";
        return 0;
    }
    //fill(used.begin(), used.end(), false);
    cout << "YES\n";
    find_pred(s);
    for (auto it : pred) {
        cout << it + 1 << ' ';
    }
    pred.clear();
    find_pred(s);
    cout << endl;
    for (auto it : pred) {
        cout << it + 1 << ' ';
    }
    //sort(incut.begin(), incut.end(), [](edge *e1, edge *e2) { return e1->index < e2->index; });
//    cout << incut.size() << ' ' << F << endl;
//    for (auto it : incut) {
//        cout << it->index / 2 + 1 << ' ';
//    }
    return 0;
}