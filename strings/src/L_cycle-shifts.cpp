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
#define re(n) resize(n)
#define fi first
#define se second
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
struct suff {
    ll pos;
    pair<ll, ll> fs;
};
 
int main() {
    ifstream cin("shifts.in");
    ofstream cout("shifts.out");
    cin.tie(0);
    cout.sync_with_stdio(0);
    string s;
    cin >> s;
    ll number;
    cin >> number;
    s += s;
    vector<ll> suff_mas(s.sz);
    vector<ll> lcp(s.sz - 1);
    vector<suff> suf(s.sz);
    vector<ll> poses(s.sz);
    vector<ll> beg(s.sz);
    forn(i, s.sz - 1) {
        suf[i].pos = i;
        suf[i].fs = {s[i] - 32, s[i + 1] - 32};
    }
    suf[s.sz - 1].fs = {*s.rbegin() - 32, -1};
    suf[s.sz - 1].pos = s.sz - 1;
    sort(all(suf), [](suff a, suff b) { return a.fs < b.fs; });
    ll step = 2 * 2;
    while (step < 2 * s.sz) {
        ll q = 0, p = suf.begin()->fs.fi;
        suf.begin()->fs.fi = 0;
        poses[suf.begin()->pos] = 0;
        forn(i, s.sz - 1) {
            poses[suf[i + 1].pos] = i + 1;
            q += ((suf[i + 1].fs.se != suf[i].fs.se || suf[i + 1].fs.fi != p) ? 1 : 0);
            p = suf[i + 1].fs.fi;
            suf[i + 1].fs.fi = q;
        }
        forn(i, s.sz) suf[i].fs.se = ((suf[i].pos + step / 2 < s.sz) ? suf[poses[suf[i].pos + step / 2]].fs.fi : -1);
        sort(all(suf), [](suff a, suff b) { return a.fs < b.fs; });
        step <<= 1;
    }
    forn(i, s.sz) suff_mas[i] = suf[i].pos;
    ll cur_lcp = 0;
    forn(i, s.sz) beg[suff_mas[i]] = i;
    forn(p, s.sz) {
        if (beg[p] == s.sz - 1) {
            cur_lcp = 0;
            continue;
        }
        ll q = suff_mas[beg[p] + 1];
        while (cur_lcp + p < s.sz && cur_lcp + q < s.sz && s[cur_lcp + p] == s[cur_lcp + q]) cur_lcp++;
        lcp[beg[p]] = cur_lcp;
        cur_lcp -= (cur_lcp ? 1 : 0);
    }
    ll ans = 0;
    if (suff_mas[0] <= s.sz / 2) ++ans;
    if (ans == number) {
        cout << s.substr(suff_mas[0], s.sz / 2);
        return 0;
    }
    forna(i, 1, s.sz) {
        if (suff_mas[i] <= s.sz / 2 && lcp[i - 1] < s.sz / 2) ++ans;
        if (ans == number) {
            cout << s.substr(suff_mas[i], s.sz / 2);
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
}