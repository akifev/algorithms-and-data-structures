#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("brackets.in");
	ofstream cout("brackets.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<char>a;
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (!a.empty() && ((a.top() == '('&&s[i] == ')') || (a.top() == '['&&s[i] == ']') || (a.top() == '{'&&s[i] == '}')))
			a.pop();
		else {
			if (!(s[i] == ')' || s[i] == ']' || s[i] == ']'))
				a.push(s[i]);
			else {
				cout << "NO";
				return 0;
			}
		}
	}
	cout << (a.size() > 0 ? "NO" : "YES");
}