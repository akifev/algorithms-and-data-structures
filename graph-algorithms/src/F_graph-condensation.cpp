#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <set>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (int i = 0; i < n; i++)
#define forna(i, a, n) for (int i = a; i < n; i++)
#define rforn(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(a) (int)a.size()
int n, m;
int time = 0;
vector<vector<int>> e;
vector<vector<int>> r;
vector<bool> used;
vector<int> o_O;
 
void dfs_r(int cur) {
    used[cur] = true;
    forn(i, sz(r[cur])) {
        int next = r[cur][i];
        if (!used[next]) {
            dfs_r(next);
        }
    }
    o_O.push_back(cur);
}
 
vector<int> ver;
int group = 0;
 
void dfs_e(int cur) {
    used[cur] = true;
    ver[cur] = group;
    //cond[sz(cond) - 1].push_back(cur);
    forn(i, sz(e[cur])) {
        int next = e[cur][i];
        if (!used[next]) {
            dfs_e(next);
        }
    }
}
 
void resize() {
    used.resize(n, false);
    ver.resize(n);
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    e.resize(n, vector<int>());
    r.resize(n, vector<int>());
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        e[a].push_back(b);
        r[b].push_back(a);
    }
    resize();
    forn(i, n) {
        if (!used[i]) {
            dfs_r(i);
        }
    }
    forn(i, sz(used)) {
        used[i] = false;
    }
    rforn(i, n) {
        if (!used[o_O[i]]) {
            group++;
            dfs_e(o_O[i]);
        }
    }
    set<pair<int, int>> ans;
    forn(i, sz(e)) {
        forn(j, sz(e[i])) {
            int next = e[i][j];
            if (ver[i] != ver[next])
                ans.insert(make_pair(ver[i], ver[next]));
        }
    }
    cout << sz(ans);
}
