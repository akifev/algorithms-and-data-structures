#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
 
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define forn(i, n) for (ll i = 0; i < n; i++)
#define forna(i, a, n) for (ll i = a; i < n; i++)
const ld EPS = 1e-9;
const ll INF = static_cast<const ll>(1e18);
string s;
vector<ull> k;
vector<ull> pref;
 
ull f(ll len) {
    return pref[len - 1] + s[len] * k[len];
}
 
int main() {
    std::ostream::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> s;
    pref.resize(s.size());
    k.resize(s.size());
    k[0] = 65577;
    forna(i, 1, s.size()) {
        k[i] = k[i - 1] * k[0];
    }
    pref[0] = (ull)(s[0]);
    forna(i, 1, s.size()) {
        pref[i] = pref[i - 1] + (ull)s[i] * k[i-1];
    }
    ll n;
    cin >> n;
    forn(i, n) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << (b - a == d - c && (k[c - 1] * (pref[b - 1] - (a > 1 ? pref[a - 2] : 0)) ==
                                    k[a - 1] * (pref[d - 1] - (c > 1 ? pref[c - 2] : 0))) ? "Yes\n" : "No\n");
    }
}