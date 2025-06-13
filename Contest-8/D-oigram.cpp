#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e15;

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> original(n, vector<long long>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> original[i][j];

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        x[i]--;  // Convertimos a índice 0
    }

    vector<vector<long long>> d = original;
    vector<bool> added(n, false);
    vector<long long> result;

    for (int step = n - 1; step >= 0; --step) {
        int k = x[step];
        added[k] = true;

        // AActualizamos caminos mínimos usando el nuevo nodo agregado k
        for (int i = 0; i < n; ++i) {
            if (!added[i]) continue;
            for (int j = 0; j < n; ++j) {
                if (!added[j]) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }

        // Sumamos distancias entre todos los pares distintos (i ≠ j)
        long long total = 0;
        for (int i = 0; i < n; ++i) {
            if (!added[i]) continue;
            for (int j = 0; j < n; ++j) {
                if (!added[j] || i == j) continue;
                total += d[i][j];
            }
        }

        result.push_back(total);
    }

    reverse(result.begin(), result.end());
    for (long long val : result)
        cout << val << ' ';
    cout << '\n';

    return 0;
}
