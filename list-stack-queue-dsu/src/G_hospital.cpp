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
	ifstream cin("hospital.in");
	ofstream cout("hospital.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	deque<int>f, s;
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if (c == '+') {
			int val;
			cin >> val;
			s.push_back(val);
			if (f.size() < (f.size() + s.size() + 1) / 2) {
				f.push_back(s.front());
				s.pop_front();
			}
		}
		else {
			if (c == '*') {
				int val;
				cin >> val;
				s.push_front(val);
				if (f.size() < (f.size() + s.size() + 1) / 2) {
					f.push_back(s.front());
					s.pop_front();
				}
			}
			else {
				cout << f.front() << '\n';
				f.pop_front();
				if (f.size() < (f.size() + s.size() + 1) / 2) {
					f.push_back(s.front());
					s.pop_front();
				}
			}
		}
	}
}