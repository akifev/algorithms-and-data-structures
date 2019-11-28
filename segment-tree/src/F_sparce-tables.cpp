#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int main() {
	ifstream cin("sparse.in");
	ofstream cout("sparse.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n, m, fi, u, v;
	cin >> n >> m >> fi >> u >> v;
	vector<ll> ivec(n + 5), power(25), log(n + 10);
	ivec[1] = fi;
	power[0] = 1;
	for (ll i = 1; i < 25; i++) {
		power[i] = power[i - 1] * 2;
	}
	for (ll i = 1; i < n + 10; i++) {
		log[i] = (ll)log2(i);
	}
	for (ll i = 2; i <= n; i++) {
		ivec[i] = (23 * ivec[i - 1] + 21563) % 16714589;
	}
	vector<vector<ll>>sparseTable(n + 10, vector<ll>(25));
	for (ll j = 0; j < 25; j++) {
		for (ll i = 1; i < n + 1; i++) {
			sparseTable[i][j] = (j == 0 ? ivec[i] : (i + power[j - 1] < n + 1 ? min(sparseTable[i][j - 1], sparseTable[i + power[j - 1]][j - 1]) : sparseTable[i][j - 1]));
		}
	}
	ll ans = 0, pu = u, pv = v;
	for (ll i = 1; i <= m; i++) {
		bool check = false;
		if (v < u) {
			check = true;
			swap(u, v);
		}
		ll j = log[v - u + 1];
		ans = min(sparseTable[u][j], sparseTable[v - power[j] + 1][j]);
		if (check) {
			swap(u, v);
		}
		pu = u;
		pv = v;
		u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
		v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
	}
	cout << pu << ' ' << pv << ' ' << ans << endl;
	return 0;
}