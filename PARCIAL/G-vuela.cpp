#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // número de rayos
    cin >> n;
    vector<pair<ll,ll>> v(n); // (posición, poder)
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end()); // ordenamos por posición

    vector<ll> a(n), b(n); // a[i]: posición del rayo i, b[i]: poder del rayo i
    for(int i = 0; i < n; i++){
        a[i] = v[i].first;
        b[i] = v[i].second;
    }

    //Aplicamos dp es parecido al reconocido problema de ADA de longest increasing subsequence pero
    //no es exactamente lo mismo, ya que no se puede usar el mismo rayo dos veces.
    vector<int> dp(n, 0);
    int best = 0;
    for(int m = 0; m < n; m++){
        ll limit = a[m] - b[m];
        // buscamos el primer índice p en [0..m-1] tal que a[p] >= limit
        int p = int(lower_bound(a.begin(), a.begin() + m, limit) - a.begin());
        int prev = p - 1;  // si p==0, prev = -1
        dp[m] = 1 + (prev >= 0 ? dp[prev] : 0);
        best = max(best, dp[m]);
    }

    //n - (máximo de cadenas que sobreviven)
    cout << (n - best) << "\n";
    return 0;
}
