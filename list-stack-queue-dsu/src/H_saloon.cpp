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
	ifstream cin("saloon.in");
	ofstream cout("saloon.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	deque<int>a;
	for (int i = 0; i < n; i++) {
		int h, m, w;
		cin >> h >> m >> w;
		m += (h * 60) + 20;
		while (!a.empty() && a.front() <= (m - 20)) {
			a.pop_front();
		}
		if (w >= a.size()) {
			a.push_back((!a.empty() ? a.back() + 20 : m));
			cout << a.back() / 60 << ' ' << a.back() % 60 << '\n';
		}
		else {
			cout << (m - 20) / 60 << ' ' << (m - 20) % 60 << '\n';
		}
	}
}