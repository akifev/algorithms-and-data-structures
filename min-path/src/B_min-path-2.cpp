#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <stack>
 
using namespace std;
typedef long long ll;
#define forn(i, n) for (ll i = 0; i < n; i++)
#define forna(i, a, n) for (ll i = a; i < n; i++)
#define rforn(i, n) for (ll i = n - 1; i >= 0; i--)
#define mp(a, b) make_pair(a, b)
#define pb(a) push_back(a)
ll n, m;
 
vector<set<pair<ll, ll>>> a;
vector<ll> ans;
vector<bool> was;
set<pair<ll, ll>>ver;
int main() {
    //ifstream cin("fullham.in");
    //ofstream cout("fullham.out");
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    ans.resize(n, 1e18);
    a.resize(n);
    was.resize(n, false);
    ver.insert(mp(0, 0));
    forn(i, m){
        ll q, w, e;
        cin>>q>>w>>e;
        q--;
        w--;
        a[q].insert(mp(w, e));
        a[w].insert(mp(q, e));
    }
    ll cur = 0;
    ans[cur] = 0;
    while(!ver.empty()){
        ver.erase(mp(ans[cur], cur));
        cur = ver.begin()->second;
        for(auto next: a[cur]){
            if(ans[next.first] > ans[cur] + next.second){
                if(ver.count(mp(ans[next.first], next.first)))
                ver.erase(mp(ans[next.first], next.first));
                ver.insert(mp(ans[cur] + next.second, next.first));
                ans[next.first] = ans[cur] + next.second;
            }
        }
    }
    forn(i, n){
        cout<<ans[i]<<' ';
    }
}