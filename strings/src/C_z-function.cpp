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
 
int main() {
    std::ostream::sync_with_stdio(false);
    cin.tie(nullptr);
    string stroka;
    cin >> stroka;
    vector<ll> ans(stroka.size());
 
    ll l = 0;
    ll r = 0;
    forna(dif, 1, stroka.size()) {
        ans[dif] = max(min(r - dif, ans[dif - l]), 0LL);
        while (((ans[dif] + dif) < stroka.size()) && stroka[dif + ans[dif]] == stroka[ans[dif]]) {
            ans[dif]++;
        }
        if (r < ans[dif] + dif) {
            r = dif + ans[dif];
            l = dif;
        }
    }
    forna(i, 1, stroka.size()) {
        cout << ans[i] << ' ';
    }
}