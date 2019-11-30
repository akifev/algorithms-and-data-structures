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
 
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll m, s, _k;
    cin >> n;
    forn(i, n) {
        forn(j, n) {
            ll tmp;
            cin >> tmp;
            if (tmp != 100000)
                a.emplace_back(i, j, tmp);
        }
    }
    mat.resize(n, 1e18);
    pred.resize(n, -1);
    mat[0] = 0;
    forn(k, n) {
        for (auto e : a) {
            if (mat[e.from] + e.weight < mat[e.to]) {
                mat[e.to] = mat[e.from] + e.weight;
                pred[e.to] = e.from;
            }
        }
    }
    for (auto e : a) {
        if (mat[e.from] + e.weight < mat[e.to]) {
            ll v = e.to, w = e.from;
            forn(k, 2 * n) {
                v = pred[v];
            }
            w = v;
            vector<ll> ans;
            while (w != pred[v]) {
                ans.push_back(v);
                v = pred[v];
            }
            ans.push_back(v);
            cout << "YES\n";
            cout << ans.size() << endl;
            for (ll i = ans.size() - 1; i >= 0; i--) {
                cout << ans[i] + 1 << ' ';
            }
            return 0;
        }
    }
    cout << "NO";
}