#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MOD16 = (1 << 16) - 1;
const ll MOD30 = (1 << 30) - 1;

int main() {
	ifstream cin("sum0.in");
	ofstream cout("sum0.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	vector<ll>a(1), b(1), sumPref, c;
	ll n, x, y;
	cin >> n >> x >> y >> a[0];
	a.resize(n);
	sumPref.resize(n);
	for (size_t i = 1; i < n; i++) {
		a[i] = (x*a[i - 1] + y) & MOD16;
	}
	ll m, z, t;
	cin >> m >> z >> t >> b[0];
	b.resize(2 * m);
	c.resize(2 * m);
	for (size_t i = 1; i < 2 * m; i++) {
		b[i] = (z*b[i - 1] + t) & MOD30;
	}
	for (size_t i = 0; i < 2 * m; i++) {
		c[i] = b[i] % n;
	}
	sumPref[0] = a[0];
	for (size_t i = 1; i < n; i++) {
		sumPref[i] = sumPref[i - 1] + a[i];
	}
	ll ans = 0;
	for (size_t i = 0; i < m; i++) {
		ll l = min(c[2 * i], c[2 * i + 1]);
		ll r = max(c[2 * i], c[2 * i + 1]);
		ans += sumPref[r] - (l != 0 ? sumPref[l - 1] : 0);
	}
	cout << ans;
	return 0;
}