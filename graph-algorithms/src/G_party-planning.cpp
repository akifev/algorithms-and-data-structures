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
#define forn(i, n) for (ll i = 0; i < n; i++)
#define forna(i, a, n) for (ll i = a; i < n; i++)
#define rforn(i, n) for (ll i = n - 1; i >= 0; i--)
#define sz(a) (ll)a.size()
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
 
using namespace std;
 
 
map<string, ll> g;
vector<vector<ll>> e;
vector<vector<ll>> r;
 
vector<bool> used;
vector<ll> o_O;
 
void dfs_r(ll cur) {
    used[cur] = true;
    forn(i, sz(r[cur])) {
        int next = r[cur][i];
        if (!used[next]) {
            dfs_r(next);
        }
    }
    o_O.push_back(cur);
}
 
vector<ll> color;
ll group = 0;
 
void dfs_e(ll cur) {
    used[cur] = true;
    color[cur] = group;
    //cond[sz(cond) - 1].push_back(cur);
    forn(i, sz(e[cur])) {
        ll next = e[cur][i];
        if (!used[next]) {
            dfs_e(next);
        }
    }
}
 
ll n;
 
ll ind(string user) {
    string name = user.substr(1, sz(user) - 1);
    if (user[0] == '-') {
        return g[name] + n;
    } else {
        return g[name];
    }
}
 
string rev(string user) {
    if (user[0] == '-') {
        user[0] = '+';
    } else {
        user[0] = '-';
    }
    return user;
}
 
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll m;
    cin >> n >> m;
    forn(i, n) {
        string name;
        cin >> name;
        g[name] = i;
    }
    e.resize(2 * n, vector<ll>());
    r.resize(2 * n, vector<ll>());
    forn(i, m) {
        string a, s, b;
        cin >> a >> s >> b;
        e[ind(a)].pb(ind(b));
        e[ind(rev(b))].pb(ind(rev(a)));
        r[ind(b)].pb(ind(a));
        r[ind(rev(a))].pb(ind(rev(b)));
    }
    n *= 2;
    used.resize(n, 0);
    color.resize(n);
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
    n /= 2;
    vector<bool> will(n, false);
    forn(i, n) {
        if (color[i] == color[i + n]) {
            cout << -1;
            return 0;
        }
        if (color[i] < color[i + n]) {
            will[i] = true;
        }
    }
    ll cnt = 0;
    for (auto it : g) {
        if (will[it.second])
            cnt++;
    }
    cout << cnt << endl;
    for (auto it:g) {
        if (will[it.second])
            cout << it.first << endl;
    }
}