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
	ifstream cin("kenobi.in");
	ofstream cout("kenobi.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	list<int>f, s;
	for (int i = 0; i < n; i++) {
		string c;
		cin >> c;
		if (c[0] == 'a') {
			int val;
			cin >> val;
			s.push_back(val);
			if (f.size() < (f.size() + s.size()) / 2) {
				f.push_back(s.front());
				s.pop_front();
			}
		}
		else {
			if (c[0] == 'm') {
				if (f.size() + s.size() > 1) {
					swap(f, s);
					if (f.size() > (f.size() + s.size()) / 2) {
						s.push_front(f.back());
						f.pop_back();
					}
				}
			}
			else {
				if (f.size() + s.size() > 0) {
					s.pop_back();
					if (f.size() > (f.size() + s.size()) / 2) {
						s.push_front(f.back());
						f.pop_back();
					}
				}
			}
		}
	}
	cout << f.size() + s.size() << '\n';
	for (list<int>::iterator it = f.begin(); it != f.end(); it++)
		cout << *it << ' ';
	for (list<int>::iterator it = s.begin(); it != s.end(); it++)
		cout << *it << ' ';
}