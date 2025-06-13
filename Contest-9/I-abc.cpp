#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        ll n0;
        cin >> n0;
        ll n = n0;

        // Factorizamos n0 en primos
        vector<pair<ll,int>> fac;
        // factor 2
        if(n % 2 == 0){
            int cnt = 0;
            while(n % 2 == 0){
                n /= 2;
                cnt++;
            }
            fac.emplace_back(2, cnt);
        }
        // factores impares
        for(ll d = 3; d*d <= n; d += 2){
            if(n % d == 0){
                int cnt = 0;
                while(n % d == 0){
                    n /= d;
                    cnt++;
                }
                fac.emplace_back(d, cnt);
            }
        }
        if(n > 1){
            fac.emplace_back(n, 1);
        }

        // Intentamos construir a, b, c
        bool ok = false;
        ll a=0, b=0, c=0;

        if(fac.size() >= 3){
            // tres (o más) primos distintos
            a = fac[0].first;
            b = fac[1].first;
            c = n0 / (a*b);
            ok = true;
        }
        else if(fac.size() == 2){
            // dos primos distintos p^e1 * q^e2
            int e1 = fac[0].second;
            int e2 = fac[1].second;
            if(e1 + e2 >= 4){
                // basta con tomar a = p, b = q, c = resto = p^(e1-1)*q^(e2-1)
                a = fac[0].first;
                b = fac[1].first;
                c = n0 / (a*b);
                ok = true;
            }
        }
        else if(fac.size() == 1){
            // sólo un primo p^e
            ll p = fac[0].first;
            int e = fac[0].second;
            if(e >= 6){
                // podemos hacer a = p, b = p^2, c = p^(e-3)
                a = p;
                b = p*p;
                c = n0 / (a*b);  // == p^(e-3)
                ok = true;
            }
        }

        if(!ok){
            cout << "NO\n";
        } else {
            // a, b, c son >1 y distintos por construcción
            cout << "YES\n"
                 << a << " " << b << " " << c << "\n";
        }
    }
    return 0;
}
