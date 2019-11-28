#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
struct point {
	ll x;
	ll y;
	point() {}
	point(ll a, ll b) {
		x = a;
		y = b;
	}
};

struct rect {
	point fi;
	point se;
};

struct line {
	ll pos = 0;
	ll type = 0;
	ll up = 0;
	ll dwn = 0;
	line() {}
	line(ll a, ll b, ll c, ll d) {
		pos = a;
		type = b;
		up = c;
		dwn = d;
	}
};

enum operations {
	NOOPERATIONS,
	ADD
};
struct Node {
	ll max = 0;
	ll add = 0;
	ll ind_max = 0;
	ll ind;
	ll rightBorder;
	ll leftBorder;
	operations op = NOOPERATIONS;
	Node() {};
	Node(ll x) {
		max = x;
	};
};

bool cmp(line first, line second) {
	if (first.pos != second.pos) {
		return first.pos < second.pos;
	}
	else {
		return first.type > second.type;
	}
}

void build(vector<Node> &t, ll ind, ll leftBorder, ll rightBorder) {
	t[ind].ind = ind;
	t[ind].leftBorder = leftBorder;
	t[ind].rightBorder = rightBorder;
	t[ind].ind_max = leftBorder;
	if (leftBorder == rightBorder) {
		return;
	}
	build(t, 2 * ind + 1, leftBorder, (leftBorder + rightBorder) / 2);
	build(t, 2 * ind + 2, (leftBorder + rightBorder) / 2 + 1, rightBorder);
}

void propagate(vector <Node> &t, ll ind) {
	if (t[ind].op == NOOPERATIONS) {
		return;
	}
	if (t[ind].leftBorder != t[ind].rightBorder) {
		t[2 * ind + 1].max += t[ind].add;
		t[2 * ind + 2].max += t[ind].add;
		t[2 * ind + 1].add += t[ind].add;
		t[2 * ind + 2].add += t[ind].add;
		t[2 * ind + 1].op = ADD;
		t[2 * ind + 2].op = ADD;
	}
	t[ind].add = 0;
	t[ind].op = NOOPERATIONS;
}

void add(vector<Node> &t, ll ind, ll l, ll r, ll value) {
	propagate(t, ind);
	if (l <= t[ind].leftBorder && t[ind].rightBorder <= r) {
		t[ind].max += value;
		t[ind].add = value;
		t[ind].op = ADD;
		return;
	}
	if (t[ind].rightBorder < l || t[ind].leftBorder > r) {
		return;
	}
	add(t, 2 * ind + 1, l, r, value);
	add(t, 2 * ind + 2, l, r, value);
	if (t[2 * ind + 1].max > t[2 * ind + 2].max) {
		t[ind].max = t[2 * ind + 1].max;
		t[ind].ind_max = t[2 * ind + 1].ind_max;
	}
	else {
		t[ind].max = t[2 * ind + 2].max;
		t[ind].ind_max = t[2 * ind + 2].ind_max;
	}
}

ll positionMax(vector <Node> &t, Node maxNode) {
	if (maxNode.leftBorder != maxNode.rightBorder) {
		propagate(t, maxNode.ind);
		if (t[2 * maxNode.ind + 1].max == maxNode.max) {
			return positionMax(t, t[2 * maxNode.ind + 1]);
		}
		else {
			return positionMax(t, t[2 * maxNode.ind + 2]);
		}
	}
	else {
		return maxNode.ind;
	}
}

int main() {
	//ifstream in("sparse.in");
	//ofstream out("sparse.out");
	cin.tie(0);
	ios::sync_with_stdio(0);
	ll n;
	cin >> n;
	//ll minx = LLONG_MAX, maxx = LLONG_MIN;
	ll miny = LLONG_MAX, maxy = LLONG_MIN;
	vector<rect>r(n);
	for (ll i = 0; i < n; i++) {
		cin >> r[i].fi.x >> r[i].fi.y >> r[i].se.x >> r[i].se.y;
		//minx = min(minx, r[i].fi.x);
		//maxx = max(maxx, r[i].se.x);
		miny = min(miny, r[i].fi.y);
		maxy = max(maxy, r[i].se.y);
	}
	vector<line>sl;
	for (ll i = 0; i < n; i++) {
		sl.push_back(line(r[i].fi.x, 1, -miny + r[i].fi.y, -miny + r[i].se.y));
		sl.push_back(line(r[i].se.x, -1, -miny + r[i].fi.y, -miny + r[i].se.y));
	}
	sort(sl.begin(), sl.end(), cmp);
	ll sz = 1;
	while (sz < maxy - miny + 1) {
		sz <<= 1;
	}
	vector<Node>t(2 * sz - 1);
	build(t, 0, sz - 1, 2 * sz - 2);
	ll ans = LLONG_MIN;
	point maxPos = point(0, 0);
	//propagate(t, 0);
	ll mx = t[0].max;
	for (line i : sl) {
		add(t, 0, i.up + sz - 1, i.dwn + sz - 1, i.type);
		//propagate(t, 0);
		mx = t[0].max;
		//cout << mx << ' ';
		if (ans < mx) {
			ans = mx;
			maxPos = point(i.pos, t[0].ind_max);
		}
	}
	//cout << endl;
	cout << ans << endl << maxPos.x << ' ' << maxPos.y - sz + 1 + miny;

	return 0;
}