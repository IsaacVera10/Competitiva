#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    double tt;
    if(!(cin >> n >> tt)) return 0;z
    vector<long double> d(n), s(n);
    for(int i = 0; i < n; i++){
        cin >> d[i] >> s[i];
    }

    long double T = tt;

    long double sigma = s[0];
    for(int i = 1; i < n; i++){
        sigma = min(sigma, s[i]);
    }

    auto f = [&](long double c){
        long double sum = 0;
        for(int i = 0; i < n; i++){
            sum += d[i] / (s[i] + c);
        }
        return sum - T;
    };

    long double L = -sigma + 1e-15L;

    long double width = 1.0L;
    while (f(L + width) > 0) {
        width *= 2.0L;
    }
    long double R = L + width;

    for(int it = 0; it < 80; it++){
        long double M = (L + R) * 0.5L;
        if (f(M) > 0)
            L = M;
        else
            R = M;
    }

    long double c = (L + R) * 0.5L;

    // Imprimir con 9 decimales
    cout << fixed << setprecision(9) << (double)c << "\n";
    return 0;
}
