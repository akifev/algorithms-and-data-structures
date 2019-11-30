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
ll n, m;
 
vector<set<pair<ll, ll>>> a;
 
ll f(ll qwe, ll rty, ll uio) {
    vector<ll> ans(n, 1e18);
    vector<bool> was(n, false);
    set<pair<ll, ll>> ver;
    forn(i, n) {
        if (i != qwe) {
            ver.insert(mp(1e18, i));
        }
    }
    ver.insert(mp(0, qwe));
    ll cur = qwe;
    ans[cur] = 0;
    forn(i, n - 1) {
        was[cur] = true;
        ver.erase(mp(ans[cur], cur));
        for (auto next : a[cur]) {
            if (!was[next.first] && ans[next.first] > ans[cur] + next.second) {
                ver.erase(mp(ans[next.first], next.first));
                ver.insert(mp(ans[cur] + next.second, next.first));
                ans[next.first] = ans[cur] + next.second;
            }
        }
        cur = ver.begin()->second;
    }
    return ans[rty] + ans[uio];
}
 
 
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    a.resize(n);
    forn(i, m) {
        ll q, w, e;
        cin >> q >> w >> e;
        q--;
        w--;
        a[q].insert(mp(w, e));
        a[w].insert(mp(q, e));
    }
    ll qwe, rty, uio;
    cin >> qwe >> rty >> uio;
    ll result = min(min(f(qwe - 1, rty - 1, uio - 1), f(rty - 1, qwe - 1, uio - 1)), f(uio - 1, rty - 1, qwe - 1));
    if (result >= 1e18)
        cout << -1;
    else
        cout << result;
}
