#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <fstream>
#include <map>
#include <list>
using namespace std;
int main() {
	ifstream cin("bureaucracy.in");
	ofstream cout("bureaucracy.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long long n, m;
	cin >> n >> m;
	vector<long long>p(n);
	vector<long long>count(1e6 + 3);
	long long sz = 0, sm = 0;
	for (long long i = 0; i < n; i++) {
		cin >> p[i];
		sm += p[i];
		count[p[i]]++;
	}
	if (sm <= m) {
		cout << -1;
		return 0;
	}
	long long sum = 0, cnt = 0, q = 1;
	while (m >= (n - sum) && q - 3 < 1e6 && m > 0) {
		m -= (n - sum);
		sum += count[q++];
		cnt++;
	}
	for (long long i = 0; i < n; i++) {
		p[i] = (p[i] <= cnt ? 0 : p[i] - cnt);
	}
	long long ans = 0, pnt = 0;
	for (long long i = 0; i < n; i++) {
		if (m > 0) {
			if (p[i] > 0) {
				p[i]--;
				m--;
				pnt = i + 1;
			}
		}
		else {
			break;
		}
	}
	for (long long i = 0; i < n; i++) {
		if (p[i] > 0) {
			ans++;
		}
	}
	cout << ans << '\n';
	for (long long i = pnt; i < n; i++) {
		if (p[i] > 0) {
			cout << p[i] << ' ';
		}
	}
	for (long long i = 0; i < pnt; i++) {
		if (p[i] > 0) {
			cout << p[i] << ' ';
		}
	}
	return 0;
}