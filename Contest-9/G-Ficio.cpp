#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    int count_par = 0;// Contador de ciclos pares

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        if (a % 2 == 0) {
            // si el ciclo añadido es par, cambiamos la paridad
            count_par ^= 1;
        }
        // Si la paridad de la cantidad de ciclos pares es 1, gana el primer jugador
        // en otro caso pierde
        cout << (count_par ? 1 : 2) << "\n";
    }

    return 0;
}
