#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define forn(i, n) for(ll i = 0; i < n; ++i)
#define forna(i, a, n) for(ll i = a; i < n; ++i)
 
#define INF (ll)1e18
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>());
    vector<ll> w(n);
    forn(i, n) {
        cin >> w[i];
    }
    ll max = *max_element(w.begin(), w.end());
    vector<ll> b(max + 1);
    forn(i, max + 1) {
        b[i] = i;
    }
    forna(i, 2, max + 1) {
        if (b[i] == i) {
            forna(j, i * i, b.size()) {
                b[j] = i;
                j += i - 1;
            }
        }
    }
    forn(i, n) {
        while (w[i] != 1) {
            a[i].push_back(b[w[i]]);
            w[i] /= b[w[i]];
        }
    }
    forn(i, n) {
        sort(a[i].begin(), a[i].end());
        forn(j, a[i].size()) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
}