#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = 1e9;

int main() {
    string s, t;
    cin >> s >> t;

    if (s.length() != t.length()) {
        cout << -1 << '\n';
        return 0;
    }

    int n;
    cin >> n;

    // Matriz de distancias entre letras
    // dist[i][j] será el costo mínimo para convertir 'a' + i a 'a' + j
    vector<vector<int>> dist(26, vector<int>(26, INF));
    for (int i = 0; i < 26; ++i) dist[i][i] = 0;

    // Reglas de transformación
    for (int i = 0; i < n; ++i) {
        char a, b;
        int w;
        cin >> a >> b >> w;
        int u = a - 'a';
        int v = b - 'a';
        dist[u][v] = min(dist[u][v], w);  // se queda con el menor costo si hay duplicados
    }

    // Aplicamos Floyd-Warshall para hallar costo mínimo entre cualquier par
    for (int k = 0; k < 26; ++k)
        for (int i = 0; i < 26; ++i)
            for (int j = 0; j < 26; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int total_cost = 0;
    string result = "";

    for (size_t i = 0; i < s.size(); ++i) {
        int u = s[i] - 'a';
        int v = t[i] - 'a';

        if (u == v) {
            result += s[i];
            continue;
        }

        int best_cost = INF;
        char best_char = '?';

        // Fuerza bruta para encontrar el mejor carácter
        for (int c = 0; c < 26; ++c) {
            if (dist[u][c] < INF && dist[v][c] < INF) {
                int cost = dist[u][c] + dist[v][c];
                if (cost < best_cost) {
                    best_cost = cost;
                    best_char = char(c + 'a');
                }
            }
        }

        if (best_cost == INF) {
            cout << -1 << '\n';
            return 0;
        }

        total_cost += best_cost;
        result += best_char;
    }

    cout << total_cost << '\n';
    cout << result << '\n';

    return 0;
}
