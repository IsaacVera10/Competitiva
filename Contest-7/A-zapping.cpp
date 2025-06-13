#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

const int MAX_TIME = 3600;

pair<int, int> resolverCaso(int n, int t, const vector<int>& botones) {
    vector<int> dist(MAX_TIME + 1, INT_MAX);  // Distancia mínima a cada tiempo
    queue<int> q;

    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int actual = q.front();
        q.pop();

        for (int b : botones) {
            int nuevoTiempo = actual + b;
            if (nuevoTiempo < 0) nuevoTiempo = 0;
            if (nuevoTiempo > MAX_TIME) nuevoTiempo = MAX_TIME;

            if (dist[nuevoTiempo] > dist[actual] + 1) {
                dist[nuevoTiempo] = dist[actual] + 1;
                q.push(nuevoTiempo);
            }
        }
    }

    
    for (int i = t; i <= MAX_TIME; ++i) {// Busca el tiempo más cercano >= t
        if (dist[i] != INT_MAX) {
            return {dist[i], i - t};
        }
    }
    return {-1, -1};
}

int main() {
    int casos;
    cin >> casos;

    while (casos--) {
        int n, t;
        cin >> n >> t;

        vector<int> botones(n);
        for (int i = 0; i < n; ++i) {
            cin >> botones[i];
        }

        pair<int, int> resultado = resolverCaso(n, t, botones);
        cout << resultado.first << " " << resultado.second << endl;
    }

    return 0;
}
