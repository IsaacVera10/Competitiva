#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; // número de llegadas
    cin >> N;
    vector<pair<ll,int>> llegadas(N); // (tiempo de llegada, dirección: 0 o 1)
    for (int i = 0; i < N; i++) {
        cin >> llegadas[i].first >> llegadas[i].second;
    }

    const ll INF = LLONG_MAX / 4; // Usamos un valor grande para evitar overflow
    priority_queue<ll, vector<ll>, greater<ll>> exit_heap;// Cola de prioridad para manejar las salidas
    ll current_time = 0; // Tiempo actual en la escalera
    int escalator_dir = -1; // Dirección de la escalera (-1: parada, 0: hacia abajo, 1: hacia arriba)
    int count_on = 0; // Contador de personas en la escalera
    ll last_stop_time = 0;   // Último tiempo en que la escalera se detuvo
    array<int,2> waiting_count = {0, 0}; // Contadores de personas esperando en cada dirección (0 y 1)
    int i = 0;

    while (i < N || !exit_heap.empty() || waiting_count[0] > 0 || waiting_count[1] > 0) {
        ll next_arrival = (i < N ? llegadas[i].first : INF);
        ll next_exit    = (!exit_heap.empty() ? exit_heap.top() : INF);

        if (next_arrival <= next_exit) {// Si hay una llegada antes o al mismo tiempo que una salida
            current_time = next_arrival;
            int d = llegadas[i].second;
            if (count_on == 0) {
                escalator_dir = d;
                count_on = 1;
                exit_heap.push(current_time + 10);
            } 
            else if (escalator_dir == d) {
                count_on++;
                exit_heap.push(current_time + 10);
            } 
            else {
                waiting_count[d]++;
            }
            i++;
        } 
        else { // Si hay una salida antes de la siguiente llegada
            current_time = next_exit;
            exit_heap.pop();
            count_on--;
            if (count_on == 0) {
                last_stop_time = current_time;
                escalator_dir = -1;
                int to_dir = (waiting_count[0] > 0 ? 0 : (waiting_count[1] > 0 ? 1 : -1));
                if (to_dir != -1) {
                    escalator_dir = to_dir;
                    int wc = waiting_count[to_dir];
                    for (int k = 0; k < wc; ++k) {
                        exit_heap.push(current_time + 10);
                    }
                    count_on = wc;
                    waiting_count[to_dir] = 0;
                }
            }
        }
    }

    cout << last_stop_time << "\n";
    return 0;
}
