#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
 
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
    vector<ll> a(n);
    forn(i, n) {
        cin >> a[i];
    }
    ll max = *max_element(a.begin(), a.end());
    vector<bool> b(max + 1, true);
    b[0] = false;
    b[1] = false;
    forna(i, 2, b.size()) {
        if (b[i]) {
            forna(j, i * i, b.size()) {
                b[j] = false;
                j+=i-1;
            }
        }
    }
    forn(i, n) {
        cout << (b[a[i]] ? "YES\n" : "NO\n");
    }
}