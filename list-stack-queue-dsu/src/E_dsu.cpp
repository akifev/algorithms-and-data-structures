#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("dsu.in");
	ofstream cout("dsu.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<int>p(n), min(n), max(n);
	vector<vector<int>>l(n, vector<int>());
	for (int i = 0; i < n; i++) {
		p[i] = i;
		l[i].push_back(i);
		min[i] = i;
		max[i] = i;
	}
	string s;
	while (cin >> s) {
		if (s[0] == 'u') {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			x = p[x];
			y = p[y];
			if (x != y) {
				if (l[y].size() > l[x].size()) {
					swap(x, y);
				}
				for (int i = 0; i < l[y].size(); i++) {
					if (min[x] > l[y][i]) {
						min[x] = l[y][i];
					}
					if (max[x] < l[y][i]) {
						max[x] = l[y][i];
					}
					p[l[y][i]] = x;
					l[x].push_back(l[y][i]);
				}
				l[y].clear();
			}
		}
		else {
			int x;
			cin >> x;
			x--;
			cout << min[p[x]] + 1 << ' ' << max[p[x]] + 1 << ' ' << l[p[x]].size() << '\n';
		}
	}
}