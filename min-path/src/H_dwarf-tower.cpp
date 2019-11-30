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
 
vector<vector<pair<ll, ll>>> a;
vector<bool> was;
set<pair<ll, ll>> ver;
 
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ifstream cin("dwarf.in");
    ofstream cout("dwarf.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    a.resize(n);
    was.resize(n, false);
    vector<ll> r(n);
    ll start = 0;
    forn(i, n) {
        cin >> r[i];
        if (r[i] < r[start]) {
            start = i;
        }
    }
    forn(i, n) {
        ver.insert(mp(r[i], i));
    }
    forn(i, m) {
        ll q, w, e;
        cin >> q >> w >> e;
        q--;
        w--;
        e--;
        a[w].push_back(mp(q, e));
        a[e].push_back(mp(q, w));
    }
 
    ll cur = start;
    while(!ver.empty()) {
        was[cur] = true;
        ver.erase(mp(r[cur], cur));
        for (auto next: a[cur]) {
            if (!was[next.first]) {
                if(was[next.second]) {
                    if (r[cur] + r[next.second] < r[next.first]) {
                        ver.erase(mp(r[next.first], next.first));
                        ver.insert(mp(r[cur] + r[next.second], next.first));
                        r[next.first] = r[cur] + r[next.second];
                    }
                }
            }
        }
        cur = ver.begin()->second;
    }
    cout<<r[0];
}