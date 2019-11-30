#include <bits/stdc++.h>
 
using namespace std;
 
#define forn(i, n) for (long long i = 0; i < n; ++i)
#define forna(i, a, n) for (long long i = a; i < n; ++i)
#define fornr(i, n) for (long long i = n - 1; i >= 0; --i)
#define forab(i, a, b) for (long long i = a; i < b; ++i)
#define forba(i, a, b) for (long long i = b - 1; i >= a; --i)
#define forit(it, c) for(auto it = c.begin(); it != c.end(); ++it)
#define foritr(it, c) for(auto it = c.rbegin(); it != c.rend(); ++it)
#define all(c) c.begin(), c.end()
#define sz size()
#define se second
#define re(n) resize(n)
#define fi first
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
struct suff {
    ll pos;
    pair<ll, ll> fs;
};
 
int main() {
//    ifstream cin("common.in");
//    ofstream cout("common.out");
    cin.tie(0);
    cout.sync_with_stdio(0);
    string a, b, stroka;
    cin >> a >> b;
    stroka = a + "#" + b;
    vector<ll> ans(stroka.sz);
    ans[0] = 0;
    ll pos;
    forna(i, 1, stroka.sz) {
        pos = ans[i - 1];
        while (pos > 0 && stroka[i] != stroka[pos]) {
            pos = ans[pos - 1];
        }
        ans[i] = (stroka[i] == stroka[pos] ? pos + 1 : pos);
    }
    vector<ll> res;
    forna(i, a.sz + 1, stroka.sz) {
        if (ans[i] == a.sz) {
            res.push_back(i - 2 * a.sz + 1);
        }
    cout << res.sz << endl;
    forn(i, res.sz) {
    }
        cout << res[i] << ' ';
    }
}