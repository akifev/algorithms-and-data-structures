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
int time = 0, cnt = 0;
vector<int> inTime;
vector<int> ret;
vector<vector<pair<int, int>>> e;
vector<int> color;
vector<int> p;
vector<int> input;
 
void dfs(int cur, int par) {
    time++;
    inTime[cur] = ret[cur] = time;
    forn(i, sz(e[cur])) {
        int next = e[cur][i].first;
        if (next != par) {
            if (inTime[next] == -1) {
                dfs(next, cur);
                ret[cur] = min(ret[cur], ret[next]);
                if (ret[next] > inTime[cur]) {
                    e[cur][i].second = 1;
                    forn(j, sz(e[e[cur][i].first])) {
                        if (e[e[cur][i].first][j].first == cur) {
                            e[e[cur][i].first][j].second = 1;
                            break;
                        }
                    }
                }
            } else {
                ret[cur] = min(ret[cur], inTime[next]);
            }
        }
    }
}
 
int k = 1;
vector<bool> used;
 
void dfs1(int cur) {
    used[cur] = true;
    input[cur] = k;
    forn(i, sz(e[cur])) {
        if (e[cur][i].second)
            continue;
        int next = e[cur][i].first;
        if (!used[next]) {
            dfs1(next);
        }
    }
}
 
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    e.resize(n, vector<pair<int, int>>());
    input.resize(n, 0);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        e[a].push_back(make_pair(b, 0));
        e[b].push_back(make_pair(a, 0));
    }
    color.resize(n, 0);
    ret.resize(n, n + 1);
    p.resize(n, -1);
    inTime.resize(n, -1);
    forn(i, n) {
        if (inTime[i] == -1) {
            dfs(i, -1);
        }
    }
    used.resize(n, false);
    forn(i, n) {
        if (!used[i]) {
            dfs1(i);
            k++;
        }
    }
    cout << k - 1 << endl;
    forn(i, n) {
        cout << input[i] << ' ';
    }
}