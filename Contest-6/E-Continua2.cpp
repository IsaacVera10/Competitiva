#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; // Número de casos de prueba
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        //Llenado de posiciones
        vector<ll> xs(n), ys(n);
        for (int i = 0; i < n; i++) {
            cin >> xs[i] >> ys[i];
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        // Minimizar sum |xi - x|:
        // -> x debe estar entre
        // -> la mediana baja y la mediana alta:
        // -> índices lo = (n-1)/2, hi = n/2
        ll x_low = xs[(n - 1) / 2];
        ll x_high = xs[n / 2];
        ll y_low = ys[(n - 1) / 2];
        ll y_high = ys[n / 2];

        // Cantidad de valores enteros en esos intervalos:
        ll cnt_x = x_high - x_low + 1;
        ll cnt_y = y_high - y_low + 1;

        // El número total de puntos óptimos es el producto:
        cout << (cnt_x * cnt_y) << "\n";
    }

    return 0;
}
