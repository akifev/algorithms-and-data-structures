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
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    ll _cost = -1;
    vector<vector<pair<ll, ll>>> edge(n);
    forn(i, m) {
        ll q, w, e;
        cin >> q >> w >> e;
        q--;
        w--;
        edge[q].push_back({w, e});
        edge[w].push_back({q, e});
        if (q == 0 || q == n - 1 || w == 0 || w == n - 1) {
            _cost = e;
        }
    }
    if (_cost == -1) {
        cout << "Impossible";
        return 0;
    }
    ll t;
    cin >> t;
    vector<vector<ll>> d(n, vector<ll>(2 * _cost, 2e18));
    set<pair<ll, pair<ll, ll>>> ver;
    ver.insert({0, {0, 0}});
    d[0][0] = 0;
    while (!ver.empty()) {
        ll i = ver.begin()->second.first;
        ll j = ver.begin()->second.second;
        ver.erase(ver.begin());
        for (auto _next : edge[i]) {
            ll weight = _next.second;
            ll kuda = _next.first;
            ll ostatok = (j + weight) % (2 * _cost);
            if (d[kuda][ostatok] > d[i][j] + weight) {
                if (ver.count({d[kuda][ostatok], {kuda, ostatok}}))
                    ver.erase({d[kuda][ostatok], {kuda, ostatok}});
                d[kuda][ostatok] = d[i][j] + weight;
                ver.insert({d[kuda][ostatok], {kuda, ostatok}});
            }
        }
    }
    cout << (d[n - 1][t % (2 * _cost)] <= t ? "Possible" : "Impossible");
}
