#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;

    // Vector AB y BC
    ll dx1 = bx - ax, dy1 = by - ay;
    ll dx2 = cx - bx, dy2 = cy - by;

    // 1) compruebo que no sean colineares: cross != 0
    ll cross = dx1*dy2 - dy1*dx2;
    // 2) compruebo que tengan la misma longitud cuadrada
    ll l1 = dx1*dx1 + dy1*dy1;
    ll l2 = dx2*dx2 + dy2*dy2;

    if (cross != 0 && l1 == l2) 
        cout << "Yes\n";
    else 
        cout << "No\n";

    return 0;
}
