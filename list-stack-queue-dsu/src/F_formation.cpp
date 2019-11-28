#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <fstream>
#include <map>
using namespace std;
int main() {
	ifstream cin("formation.in");
	ofstream cout("formation.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	map<int, pair<int, int>>a;
	a.insert({ 0, pair<int,int>(-1,-1) });
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		int x;
		cin >> x;
		x--;
		if (s == "left" || s[0] == 'r') {
			int y;
			cin >> y;
			y--;
			if (s[0] == 'l') {
				try {
					a[x].first = a[y].first;
					a[x].second = y;
				}
				catch (out_of_range e) {
					a.insert({ x,pair<int,int>(a[y].first,y) });
				}
				a[a[y].first].second = x;
				a[y].first = x;
			}
			else {
				try {
					a[x].first = y;
					a[x].second = a[y].second;
				}
				catch (out_of_range e) {
					a.insert({ x,pair<int,int>(y,a[y].second) });
				}
				a[a[y].second].first = x;
				a[y].second = x;
			}
		}
		else {
			if (s[0] == 'n') {
				cout << (a[x].first != -1 ? a[x].first + 1 : 0) << ' ' << (a[x].second != -1 ? a[x].second + 1 : 0) << '\n';
			}
			else {
				a[a[x].first].second = a[x].second;
				a[a[x].second].first = a[x].first;
				a[x].first = -1;
				a[x].second = -1;
			}
		}
	}
}