#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;
int main() {
	ifstream cin("postfix.in");
	ofstream cout("postfix.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<long long>a;
	string s;
	while (cin >> s) {
		if (s[0] == '+' || s[0] == '-' || s[0] == '*') {
			long long r = a.top();
			a.pop();
			long long l = a.top();
			a.pop();
			if (s[0] == '+' || s[0] == '-') {
				if (s[0] == '-') {
					r = -r;
				}
				a.push(l + r);
			}
			else {
				a.push(l*r);
			}
		}
		else {
			a.push(stoll(s));
		}
	}
	cout << a.top();
}