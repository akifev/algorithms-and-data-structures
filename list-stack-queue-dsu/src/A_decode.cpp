#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("decode.in");
	ofstream cout("decode.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<char>a;
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (a.empty() || a.top() != s[i])
			a.push(s[i]);
		else
			a.pop();
	}
	int sz = a.size();
	for (int i = sz - 1; i >= 0; i--) {
		s[i] = a.top();
		a.pop();
	}
	for (int i = 0; i < sz; i++) {
		cout << s[i];
	}
}