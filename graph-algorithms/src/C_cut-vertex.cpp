#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <set>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (int i = 0; i < n; i++)
#define forna(i, a, n) for (int i = a; i < n; i++)
#define rforn(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(a) (int)a.size()
int n, m;
int time = 0, cnt = 0;
vector<int> inTime;
vector<vector<pair<int, int>>> e;
vector<int> color;
vector<int> p;
vector<int> input;
vector<int> used;
vector<int> ret;
 
void dfs(int cur, int par) {
    //used[cur] = true;
    time++;
    inTime[cur] = ret[cur] = time;
    int h = 0;
    forn(i, sz(e[cur])) {
        int next = e[cur][i].first;
        if (next != par) {
            if (inTime[next] == -1) {
                dfs(next, cur);
                ret[cur] = min(ret[cur], ret[next]);
                h++;
                if (par != -1 && ret[next] >= inTime[cur]) {
                    input[cur] = 1;
                }
            } else {
                ret[cur] = min(ret[cur], inTime[next]);
            }
        }
    }
    if (h >= 2 && par == -1) {
        input[cur] = 1;
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    e.resize(n, vector<pair<int, int>>());
    input.resize(n, 0);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        e[a].push_back(make_pair(b, i));
        e[b].push_back(make_pair(a, i));
    }
    color.resize(n, 0);
    ret.resize(n, n + 1);
    p.resize(n, -1);
    inTime.resize(n, -1);
    forn(i, n) {
        if (inTime[i] == -1) {
            dfs(i, -1);
        }
    }
    forn(i, n) {
        if (input[i]) {
            cnt++;
        }
    }
    cout << cnt << endl;
    forn(i, n) {
        if (input[i]) {
            cout << i + 1 << ' ';
        }
    }
}