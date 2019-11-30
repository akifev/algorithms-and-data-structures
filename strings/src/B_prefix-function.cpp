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
    ans[0] = 0;
    ll pos;
    forna(i, 1, stroka.size()) {
        pos = ans[i - 1];
        while (pos > 0 && stroka[i] != stroka[pos]) {
            pos = ans[pos - 1];
        }
        ans[i] = (stroka[i] == stroka[pos] ? pos + 1 : pos);
    }
    forn(i, stroka.size()) {
        cout << ans[i] << ' ';
    }
}