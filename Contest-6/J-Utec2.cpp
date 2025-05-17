#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// merge_count: cuenta inversiones en el rango [l, r) de v
//   - divide: calcula recursivamente en mitades
//   - mezcla: recorre ambas mitades ordenadas y acumula inversiones
// Parámetros:
//   v: vector de ll donde buscar inversiones
//   l, r: índices de inicio (incluido) y fin (excluido)
ll merge_count(vector<ll>& v, int l, int r) {
    // caso base: 0 o 1 elemento no genera inversiones
    if (r - l <= 1)
        return 0;
    int m = (l + r) >> 1;
    // contar inversiones en cada mitad
    ll count = merge_count(v, l, m) + merge_count(v, m, r);

    // mezcla de dos mitades ordenadas en [l,m) y [m,r)
    vector<ll> tmp;
    tmp.reserve(r - l);
    int i = l, j = m;
    while (i < m || j < r) {
        // si la mitad derecha quedó vacía, o el elemento izquierdo
        // es menor o igual, toma de la izquierda
        if (j == r || (i < m && v[i] <= v[j])) {
            tmp.push_back(v[i]);
            i++;
        } else {
            // v[j] < v[i]
            // cada v[k] con k en [i, m) forma inversión con v[j]
            count += (m - i);
            tmp.push_back(v[j]);
            j++;
        }
    }
    // copiar los valores mezclados de vuelta en v[l..r)
    for (int k = 0; k < (int)tmp.size(); k++) {
        v[l + k] = tmp[k];
    }
    return count;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<pair<ll,ll>> seg(n);
        for(int i = 0; i < n; i++){
            cin >> seg[i].first >> seg[i].second;  // a_i y b_i distintos
        }

        // Ordenación de parejas seg por valor de inicio a_i
        sort(seg.begin(), seg.end(),
             [](auto &A, auto &B){ return A.first < B.first; });

        // Extracción de valores b_i en array B
        vector<ll> B(n);
        for(int i = 0; i < n; i++){
            B[i] = seg[i].second;
        }

        // Cómputo de inversiones en B  ⇒ número de saludos
        ll ans = merge_count(B, 0, n);
        cout << ans << "\n";
    }
    return 0;
}
