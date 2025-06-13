#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x1,y1,x2,y2;
    ll x3,y3,x4,y4;
    ll x5,y5,x6,y6;
    cin >> x1 >> y1 >> x2 >> y2
        >> x3 >> y3 >> x4 >> y4
        >> x5 >> y5 >> x6 >> y6;

    ll ix1 = max(x1, x3), ix2 = min(x2, x4);
    ll iy1 = max(y1, y3), iy2 = min(y2, y4);

    auto insideB2 = [&](ll rx1, ll ry1, ll rx2, ll ry2){
        return (x5 <= rx1 && x6 >= rx2
             && y5 <= ry1 && y6 >= ry2);
    };

    bool covered = false;


    if (!(ix1 < ix2 && iy1 < iy2)) {
        covered = (x5 <= x1 && x6 >= x2
                && y5 <= y1 && y6 >= y2);
    } 
    else {
        covered = true; 
        if (ix1 > x1)
            covered &= insideB2(x1, y1, ix1, y2);

        if (ix2 < x2)
            covered &= insideB2(ix2, y1, x2, y2);

        if (iy1 > y1)
            covered &= insideB2(ix1, y1, ix2, iy1);

        if (iy2 < y2)
            covered &= insideB2(ix1, iy2, ix2, y2);
    }

    cout << (covered ? "NO\n" : "YES\n");
    return 0;
}
