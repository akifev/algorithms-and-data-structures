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
bool check_cycles = false;
ll n, m;
vector<int>used;
vector<vector<int>>e;
vector<int>ts;
vector<int>color;
void dfs(int cur) {
	used[cur] = 1;
	color[cur] = 1;
	forn(i, sz(e[cur])) {
		int next = e[cur][i];
		if (color[next] == 1 && !check_cycles) {
			cout << -1;
			check_cycles = true;
			return;
		}
		if (used[next] != 1) {
			dfs(next);
		}
	}
	ts.push_back(cur);
	color[cur] = 2;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	e.resize(n, vector<int>());
	forn(i, m) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		e[a].push_back(b);
	}
	color.resize(n, 0);
	used.resize(n, 0);
	forn(i, n) {
		if (used[i] != 1) {
			dfs(i);
			if (check_cycles)
				return 0;
		}
	}
	rforn(i, sz(ts)) {
		cout << ts[i] + 1 << ' ';
	}
}