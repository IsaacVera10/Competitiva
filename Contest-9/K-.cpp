#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // Caso par: n/2 pasos
    if (n % 2 == 0) {
        cout << (n / 2) << "\n";
        return 0;
    }

    // n impar: buscamos su menor divisor primo d
    ll d = n;  // en caso de que n sea primo
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            d = i;
            break;
        }
    }

    // 1 paso para restar d, luego (n-d)/2 pasos con d=2
    ll pasos = 1 + (n - d) / 2;
    cout << pasos << "\n";
    return 0;
}
