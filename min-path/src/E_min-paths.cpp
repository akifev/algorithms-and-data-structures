#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <stack>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (ll i = 0; i < n; i++)
#define forna(i, a, n) for (ll i = a; i < n; i++)
#define rforn(i, n) for (ll i = n - 1; i >= 0; i--)
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
ll n;
 
struct ed {
    ll from, to, weight;
 
    ed(ll a, ll b, ll c) : from(a), to(b), weight(c) {};
};
 
vector<ed> a;
vector<ll> mat;
vector<ll> pred;
vector<vector<ll>>edge;
vector<bool>was;
void dfs(ll cur){
    was[cur] = true;
    forn(i, edge[cur].size()){
        if(!was[edge[cur][i]])
        dfs(edge[cur][i]);
    }
}
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll m, s, _k;
    cin >> n >> m >> s;
    edge.resize(n);
    forn(i, m) {
        ll e, w, th;
        cin >> e >> w;
        e--;
        w--;
        cin >> th;
        a.emplace_back(e, w, th);
        edge[e].push_back(w);
    }
    mat.resize(n, 1e18);
    mat[s - 1] = 0;
    forn(k, n - 1) {
        for (auto e : a) {
            if (mat[e.from] != 1e18 && mat[e.from] + e.weight < mat[e.to]) {
                mat[e.to] = mat[e.from] + e.weight;
            }
        }
    }
    was.resize(n, false);
    for (auto e : a) {
        if (mat[e.from] != 1e18 && mat[e.from] + e.weight < mat[e.to]) {
            dfs(e.to);
        }
    }
    forn(i, n) {
        if (was[i])
            cout << "-";
        else if (mat[i] < 1e18)
            cout << mat[i];
        else
            cout << '*';
        cout << endl;
    }
}