#include <iostream>
#include <vector>
 
using namespace std;
 
typedef long long ll;
 
ll n, w, start, finish;
 
struct item {
    pair<ll, ll> down;
    pair<ll, ll> up;
 
    item(pair<ll, ll> down = {0, 0}, pair<ll, ll> up = {0, 0}) : down(down), up(up) {}
};
 
 
vector<item> items;
vector<vector<ll>> table;
vector<ll> len;
vector<bool> was;
 
void resize() {
    items.resize(start);
    was.resize(finish + 1, false);
    table.resize(finish + 1, vector<ll>(finish + 1, 0));
    len.resize(finish + 1, 9023372036854775807);
    len[start] = 0;
}
 
int main() {
    cin >> n >> w;
    start = n;
    finish = n + 1;
    resize();
    for (ll i = 0; i < n; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        items[i] = item({a, b}, {c, d});
    }
 
    table[start][finish] = w;
    table[finish][start] = w;
    for (ll i = 0; i < start; ++i) {
        table[start][i] = w - max(items[i].down.second, items[i].up.second);
        table[i][start] = w - max(items[i].down.second, items[i].up.second);
        table[finish][i] = min(items[i].down.second, items[i].up.second);
        table[i][finish] = min(items[i].down.second, items[i].up.second);
        for (ll j = 0; j < n; ++j)
            if (i != j) {
                ll tmp;
                if (items[i].down.first > items[j].down.first) {
                    tmp = items[i].down.first - items[j].up.first;
                } else {
                    tmp = items[j].down.first - items[i].up.first;
                }
                tmp = max(tmp, items[i].down.second > items[j].down.second ? items[i].down.second - items[j].up.second :
                               items[j].down.second - items[i].up.second);
                if (tmp < 0) {
                    tmp = 0;
                }
                table[i][j] = tmp;
                table[j][i] = tmp;
            }
        
 
    }
    for (ll i = 0; i < finish + 1; ++i) {
        ll ver = -1;
        for (ll j = 0; j < finish + 1; ++j)
            if (!was[j] && (ver == -1 || len[ver] > len[j]))
                ver = j;
        was[ver] = true;
        for (ll j = 0; j < finish + 1; ++j)
            len[j] = min(len[j], len[ver] + table[ver][j]);
    }
    cout << (len[finish] == 9023372036854775807 ? 0 : len[finish]) << endl;
}