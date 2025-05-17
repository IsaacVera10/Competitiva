#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, d;
        int m;
        cin >> n >> m >> d;
        vector<ll> s(m+1);
        for (int i = 1; i <= m; ++i) {
            cin >> s[i];
        }

        // extra[i] = número de galletas "extra" que Petya comería
        // en el segmento i:
        //   i=0: antes del primer vendedor (bancas 1..s[1]-1), uso ceil
        //   i=1..m-1: entre s[i] y s[i+1], uso floor
        //   i=m: después del último vendedor (bancas s[m]+1..n), uso floor
        vector<ll> extra(m+1);
        extra[0] = (s[1] - 1 + d - 1) / d;               // ceil((s1-1) / d)
        for (int i = 1; i < m; ++i) {
            extra[i] = (s[i+1] - s[i] - 1) / d;          // floor((s[i+1]-s[i]-1) / d)
        }
        extra[m] = (n - s[m]) / d;                       // floor((n - s[m]) / d)

        // Total de galletas sin eliminar ninguno
        // = m (una por cada vendedor) + suma de los extra
        ll E_orig = m;
        for (int i = 0; i <= m; ++i) {
            E_orig += extra[i];
        }

        ll best = LLONG_MAX;
        int ways = 0;

        // Probamos removiendo cada vendedor k = 1..m
        for (int k = 1; k <= m; ++k) {
            // Eliminamos:
            //   extra[k-1], extra[k] y la galleta del vendedor k (1)
            ll removed = extra[k-1] + extra[k] + 1;
            // Y añadimos el segmento fusionado
            ll merged;
            if (k == 1) {
                // fusiona pre-primer y entre s[1],s[2]
                merged = (s[2] - 1 + d - 1) / d;
            } else if (k == m) {
                // fusiona entre s[m-1],s[m] y post-último
                merged = (n - s[m-1]) / d;
            } else {
                // fusiona entre s[k-1] y s[k+1]
                merged = (s[k+1] - s[k-1] - 1) / d;
            }
            ll Ek = E_orig - removed + merged;

            if (Ek < best) {
                best = Ek;
                ways = 1;
            } else if (Ek == best) {
                ++ways;
            }
        }

        cout << best << " " << ways << "\n";
    }

    return 0;
}
