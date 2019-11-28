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
#define pb(a) push_back(a)
 
using namespace std;
 
struct boo {
    ll a;
    ll b;
    ll w;
 
    boo() = default;
 
    boo(ll fi, ll se, ll d) : a(fi), b(se), w(d) {}
};
 
vector<ll> pred;
 
ll get_pred(ll current) {
    if (current != pred[current]) {
        pred[current] = get_pred(pred[current]);
        return pred[current];
    } else
        return current;
}
 
void unite(ll from, ll to) {
    static ll salt = 1516616131;
    from = get_pred(from);
    to = get_pred(to);
    if (salt % 2)
        swap(from, to);
    if (from != to)
        pred[from] = to;
    salt *= from * to * to * 1564366;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    pred.resize(n);
    vector<boo> e(m);
    forn(i, m) {
        cin >> e[i].a >> e[i].b >> e[i].w;
        e[i].a--;
        e[i].b--;
    }
    sort(e.begin(), e.end(), [](boo _a, boo _b) {
        return _a.w < _b.w;
    });
    ll ans = 0;
    forn(i, n) {
        pred[i] = i;
    }
    forn(i, m) {
        if (get_pred(e[i].b) != get_pred(e[i].a)) {
            unite(e[i].a, e[i].b);
            ans += e[i].w;
        }
    }
    cout << ans;
}