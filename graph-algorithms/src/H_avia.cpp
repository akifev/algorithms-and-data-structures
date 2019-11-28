#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <set>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (int i = 0; i < n; i++)
#define forna(i, a, n) for (int i = a; i < n; i++)
#define rforn(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(a) (int)a.size()
#define mp(a, b) make_pair(a, b)
vector<char> used;
 
int n;
vector<vector<int>> e;
vector<vector<int>> r;
 
void dfs(int cur, int b, vector<vector<int>> &vec) {
    used[cur] = 1;
    forn(i, n) {
        if (vec[cur][i] > b)
            continue;
        if (!used[i])
            dfs(i, b, vec);
    }
}
 
bool f(int b) {
    forn(i, n) {
        used[i] = 0;
    }
    dfs(0, b, e);
    forn(i, n) {
        if (!used[i])
            return false;
    }
    forn(i, n) {
        used[i] = 0;
    }
    dfs(0, b, r);
    forn(i, n) {
        if (!used[i])
            return false;
    }
    return true;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("avia.in");
    ofstream cout("avia.out");
    cin >> n;
    r.resize(n, vector<int>(n));
    e.resize(n, vector<int>(n));
    forn(i, n) {
        forn(j, n) {
            cin >> e[i][j];
            r[j][i] = e[i][j];
        }
    }
    used.resize(n);
    int ans;
    int l = -1, r = 1e9;
    int m;
    while (r - l > 1) {
        m = (r + l) / 2;
        if (f(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
}