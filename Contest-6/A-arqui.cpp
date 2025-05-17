#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; // Número de casos de prueba
    cin >> t;
    while(t--){
        int n; // Número de elementos para cada arreglo(caso de prueba)
        cin >> n;
        vector<int> a(n);
        for(int &x : a) 
            cin >> x;

        // Paso 1: Contamos cuántos números tienen el bit b en 1 (para cada b en 0..30)
        // Esto permite calcular  el XOR de cualquier a_k con todos los demás
        array<ll, 31> cnt1{}; //Crea un arreglo de 31 valores long long inicializados a 0
        cnt1.fill(0);
        for(int x : a){
            for(int b = 0; b < 31; ++b){ //CAda número decimal tendrá 31 bits en binario, tal como lo dice el enunciado 0<a_i<2^31
                if (x & (1<<b)) 
                    cnt1[b]++;
            }
        }

        ll ans = 0;
        // Paso 2: Para cada candidato a_k, calculamos la suma S_k = sum(a_k ^ a_i)
        // Lo hacemos bit a bit en O(31) tiempo por candidato
        for(int x : a){
            ll Sk = 0;
            for(int b = 0; b < 31; ++b){
                ll mask = 1LL << b;
                if (x & mask) {
                    // Si el bit b de a_k es 1, el XOR será 1 solo si el bit b de a_i es 0
                    Sk += mask * (n - cnt1[b]);  // n - cnt1[b] es la cantidad de a_i con bit b = 0
                } else {
                    // Si el bit b de a_k es 0, el XOR será 1 solo si el bit b de a_i es 1
                    Sk += mask * cnt1[b];        // cnt1[b] es la cantidad de a_i con bit b = 1
                }
            }
            
            ans = max(ans, Sk); // Nos quedamos con el valor máximo de S_k
        }

        cout << ans << "\n";
    }
    return 0;
}
