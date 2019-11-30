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
 
vector<vector<ll>> a, b;
vector<ll> ans;
vector<ll> time_to;
 
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    a.resize(n, vector<ll>(n));
    b.resize(n, vector<ll>(n));
    forn(i, n) {
        forn(j, n) {
            cin >> a[i][j];
            b[i][j]=a[i][j];
        }
    }
    forn(i, n) {
        forn(j, n) {
            forn(k, n) {
                b[j][k] = min(b[j][k], b[j][i] + b[i][k]);
            }
        }
    }
    forn(i, n) {
        forn(j, n) {
            cout << b[i][j]<<' ';
        }
        cout << endl;
    }
}