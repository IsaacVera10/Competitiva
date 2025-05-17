#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, D, M; // T: minutos de descanso(minimo para estar bien), D: duración del viaje, M: número de comidas durante el vuelo
    cin >> T >> D >> M;

    vector<int> y(M); // y[i]: minutos en la que se sirve la comida i
    for(int i = 0; i < M; i++){ 
        cin >> y[i];
    }

    int prev = 0; // prev: tiempo de la última comida o el inicio del vuelo
    if (M == 0) { // Si no hay comidas, solo se puede descansar al inicio del vuelo
        cout << ( (D >= T) ? 'Y' : 'N' ) << "\n";
        return 0;
    }
    if (y[0] - prev >= T) {// Si el tiempo desde el inicio del vuelo hasta la primera comida es mayor o igual a T
        cout << 'Y' << "\n";
        return 0;
    }

    for(int i = 0; i + 1 < M; i++){ // Recorremos las comidas y verificamos los intervalos entre ellas
        int gap = y[i+1] - y[i];
        if (gap >= T) {
            cout << 'Y' << "\n";
            return 0;
        }
    }

    if (D - y[M-1] >= T) { // Verificamos el tiempo desde la última comida hasta el final del vuelo
        cout << 'Y' << "\n";
    } else {
        cout << 'N' << "\n";
    }
    return 0;
}
