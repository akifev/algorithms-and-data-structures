#include <iostream>
#include<cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <set>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (int i = 0; i < n; i++)
#define forna(i, a, n) for (int i = a; i < n; i++)
#define rforn(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(a) (int)a.size()
#define mp(a, b) make_pair(a, b)
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    //vector<vector<long double>> e(n, vector<long double>(n, 0.0));
    vector<pair<int, int>> input;
    long double ans_w = 0.0;
    forn(i, n) {
        int a, b;
        cin >> a >> b;
        input.emplace_back(a + 10000, b + 10000);
    }
    vector<long double> minimal_edge(n, 1000000000.0);
    vector<int> ans(n, -9);
    vector<char> check(n, 0);
    minimal_edge[0] = 0.0;
    forn(i, n) {
        int current = -9;
        forn(num, n) {
            if (!check[num]) {
                if (current == -9 || minimal_edge[current] > minimal_edge[num]) {
                    current = num;
                }
            }
        }
        if (ans[current] != -9) {
            long double dist = sqrt(
                    (long double) (input[current].first - input[ans[current]].first) *
                    (input[current].first - input[ans[current]].first) +
                    (long double) (input[current].second - input[ans[current]].second) *
                    (input[current].second - input[ans[current]].second));
            ans_w += dist;
        }
        forn(next, n) {
            long double dist = sqrt(
                    (long double) (input[current].first - input[next].first) *
                    (input[current].first - input[next].first) +
                    (long double) (input[current].second - input[next].second) *
                    (input[current].second - input[next].second));
            if (minimal_edge[next] > dist) {
                ans[next] = current;
                minimal_edge[next] = dist;
            }
        }
        check[current] = 1;
    }
    cout << ans_w;
}