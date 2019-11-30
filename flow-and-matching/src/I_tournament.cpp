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
 
    edge() = default;
 
    edge(int from, int to, long double c) : from(from), to(to), f(0), c(c) {}
};
 
vector<edge> edges;
 
vector<int> massiv;
 
vector<int> points;
 
vector<vector<char>> w;
 
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
 
vector<int> omg;
 
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
 
void g() {
    for (int i = 1; i <= n; ++i) {
        edges.emplace_back(edge(0, i, omg[i]));
        edges.emplace_back(edge(i, 0, 0));
        edges.emplace_back(edge(i, t, massiv[i] - points[i]));
        edges.emplace_back(edge(t, i, 0));
    }
    for (int i = 0; i < edges.size(); i += 2) {
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        fast_run[edges[i].from].emplace_back(&edges[i]);
        fast_run[edges[i].to].emplace_back(&edges[i + 1]);
    }
}
 
long double binary_search() {
    long double l = 0;
    long double r = 1e5;
    for (int i = 0; i < 100; ++i) {
        long double m = (r + l) / 2;
    }
    return l;
}
 
void func() {
    f();
}
 
void sw(int i, int j) {
    int tmp = 0;
    if (w[i][j] == 'w') {
        tmp = 2;
    } else if (w[i][j] == 'l') {
        tmp = 1;
    } else if (w[i][j] == 'W') {
        tmp = 3;
    } else if (w[i][j] == 'L') {
        string s = "YOU LOOSER";
        tmp = 0;
    } else if (i < j && w[i][j] == '.') {
        edges.emplace_back(i, j, 3);
        edges.emplace_back(j, i, 0);
        ++omg[i];
    } else {
        string s = "FUCKING LABS";
    }
    points[i] += tmp;
}
 
int main() {
    cin >> n;
    m = n;
    s = 0;
    t = n + 1;
 
    used.resize(t + 1, false);
    //speed.resize(m + n + 2, 0);
    //items.resize(m + n + 2);
 
    w.resize(t + 1, vector<char>(t + 1));
    points.resize(t + 1, 0);
    omg.resize(t + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> w[i][j];
            sw(i, j);
        }
    }
    massiv.resize(t + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> massiv[i];
    }
    fast_run.resize(t + 1);
    for (int i = 0; i < omg.size(); ++i)
        omg[i] *= 3;
    g();
    func();
 
    vector<pair<char, char>> cnst = {{'W', 'L'},
                                     {'w', 'l'},
                                     {'l', 'w'},
                                     {'L', 'W'}};
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (w[i][j] == '.') {
                for (int k = 0; k < fast_run[i].size(); ++k) {
                    edge *e = fast_run[i][k];
                    if (e->to == j) {
                        w[i][j] = cnst[(int) (e->f)].first;
                        w[j][i] = cnst[(int) (e->f)].second;
                    }
                }
            }
 
        }
    }
 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << w[i][j];
        }
        cout << endl;
    }
    return 0;
}