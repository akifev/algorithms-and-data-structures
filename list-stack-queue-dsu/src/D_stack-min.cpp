#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("stack-min.in");
	ofstream cout("stack-min.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<long>a, m;
	char act;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> act;
		if (act == '1') {
			long val;
			cin >> val;
			if (!m.empty())
				m.push(min(m.top(), val));
			else
				m.push(val);
			a.push(val);
		}
		else {
			if (act == '2') {
				a.pop();
				m.pop();
			}
			else {
				cout << m.top() << '\n';
			}
		}
	}
}