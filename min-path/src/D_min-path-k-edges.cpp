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
 
struct ed{
    ll from, to, weight;
    ed(ll a, ll b, ll c) : from(a), to(b), weight(c){};
};
vector<ed> a;
vector<vector<ll>>mat;
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll m, s, _k;
    cin >> n >> m >> _k >> s;
    forn(i, m) {
        ll e, w, th;
        cin >> e >> w;
        e--;
        w--;
        cin >> th;
        a.emplace_back(e, w, th);
    }
    mat.resize(n, vector<ll>(_k+1, 1e18));
    mat[s-1][0] = 0;
    forn(k, _k) {
        for(auto e : a){
            if (mat[e.from][k] != 1e18) {
                mat[e.to][k+1] = min(mat[e.to][k+1], mat[e.from][k] + e.weight);
            }
        }
    }
    forn(i, n) {
        if (mat[i][_k] < 1e18) {
            cout << mat[i][_k] << endl;
        } else
            cout << -1 << '\n';
    }
}