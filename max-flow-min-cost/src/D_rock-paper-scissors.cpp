#include <fstream>
 
using namespace std;
 
int main() {
    ifstream cin("rps2.in");
    ofstream cout("rps2.out");
    int r1, s1, p1, r2, s2, p2;
    cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
    cout << max(p1 - p2 - s2, max(r1 - r2 - p2, max(s1 - s2 - r2, 0)));
}