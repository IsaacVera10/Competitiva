#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){

    //Llenado de posiciones: x_1, y_1, x_2, y_2
    vector<ll> x1(3), y1(3), x2(3), y2(3); //[0]=blanco, [1]=negro1, [2]=negro2
    for (int i = 0; i < 3; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    ll A_blanca = (x1[0] - x2[0]) * (y1[0] - y2[0]); //Área del cuadrado blanco

    // Intersección blanca ∩ negro 1
    ll ix1 = max(0LL, min(x2[0], x2[1]) - max(x1[0], x1[1]));
    ll iy1 = max(0LL, min(y2[0], y2[1]) - max(y1[0], y1[1]));
    ll A1 = ix1 * iy1;

    // Intersección blanca ∩ negro 2
    ll ix2 = max(0LL, min(x2[0], x2[2]) - max(x1[0], x1[2]));
    ll iy2 = max(0LL, min(y2[0], y2[2]) - max(y1[0], y1[2]));
    ll A2 = ix2 * iy2;

    // Intersección negro1 ∩ negro2
    ll ixB = max(0LL, min(x2[1], x2[2]) - max(x1[1], x1[2]));
    ll iyB = max(0LL, min(y2[1], y2[2]) - max(y1[1], y1[2]));
    
    // Intersección blanca ∩ (negro1 ∩ negro2)
    ll A12 = 0;
    if (ixB > 0 && iyB > 0) {
        // rectángulo intermedio
        ll bx_lo = max(x1[1], x1[2]);
        ll by_lo = max(y1[1], y1[2]);
        ll bx_hi = min(x2[1], x2[2]);
        ll by_hi = min(y2[1], y2[2]);

        ll ix12 = max(0LL, min(x2[0], bx_hi) - max(x1[0], bx_lo));
        ll iy12 = max(0LL, min(y2[0], by_hi) - max(y1[0], by_lo));
        A12 = ix12 * iy12;
    }

    // Área total cubierta sobre la hoja blanca
    ll A_cubierta = A1 + A2 - A12;

    // Si cubren toda el área blanca → NO se ve nada; de lo contrario → YES
    cout << (A_cubierta == A_blanca ? "NO\n" : "YES\n");
    return 0;
}