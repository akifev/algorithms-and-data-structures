#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("hemoglobin.in");
	ofstream cout("hemoglobin.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<long>a;
	vector<int>s;
	string act;
	int n, size = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> act;
		if (act[0] == '+') {
			a.push(stol(act));
			if (s.size() == size)
				s.push_back(a.top());
			else
				s[size] = a.top();
			size++;
			if (size > 1) {
				s[size - 1] += s[size - 2];
			}
		}
		else {
			if (act[0] == '-') {
				cout << a.top() << '\n';
				size--;
				a.pop();
			}
			else {
				long k = stol(act.substr(1, act.size() - 1));
				cout << s[size - 1] - (size - k - 1 < 0 ? 0 : s[size - k - 1]) << '\n';
			}
		}
	}
}