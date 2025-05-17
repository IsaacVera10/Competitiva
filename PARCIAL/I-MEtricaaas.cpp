#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

//No tiene sentido hacer calculos forzosos las coordenadas de las fichas, ya que
// no está definido la dimensión del tablero y si así fuera, hay varias combinaciones
// de fichas que pueden tener la misma cantidad de fichas en el tablero.
// La solución es encontrar el patrón de fichas que se puede formar con la cantidad de fichas n.
/*
Sabemos que: {(x,y): |x| + |y| <= R} es un conjunto de puntos en el plano cartesiano que forman un cuadrado
con centro en el origen y lados paralelos a los ejes coordenados, donde R es un entero positivo.
Por lo tanto, con un coste máximo R 
podemos colocar a lo sumo (R+1)^2 fichas manteniendo la distancia >1.

(R+1)^2 >= n => R = floor(sqrt(n)) - 1
*/

ull floor_sqrt(ull n) {  // retorna el entero mayor r tal que r*r <= n
    long double d = sqrtl((long double)n); // calculamos la raiz cuadrada
    ull r = (ull)floor(d); // redondeamos hacia abajo
    while (r > 0 && r > n / r) --r; // aseguramos que r*r <= n
    while ((r + 1) <= n / (r + 1)) ++r; // aseguramos que (r+1)*(r+1) > n
    return r; // r es el entero mayor tal que r*r <= n
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; //numero de casos de prueba
    cin >> t;
    while (t--) {
        ull n; //numero de fichas
        cin >> n;
        ull f = floor_sqrt(n); // Obtenemos la raiz cuadrada entera de n tal que f*f <= n
        ull k = (f * f == n ? f : f + 1); // Si f*f == n, entonces k = f, sino k = f + 1
        cout << (k - 1) << "\n";
    }
    return 0;
}
