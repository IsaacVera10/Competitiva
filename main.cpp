#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        unordered_map<int, vector<int>> pos;

        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }

        // Guardar segmentos [l, r] por color
        vector<pair<int, int>> seg(n);
        unordered_map<int, int> color_id;
        int idx = 0;
        for (auto& [color, v] : pos) {
            seg[idx] = {v[0], v[1]};
            color_id[color] = idx;
            idx++;
        }

        // Construir grafo por intersección cruzada
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) {
            auto [l1, r1] = seg[i];
            for (int j = i + 1; j < n; j++) {
                auto [l2, r2] = seg[j];
                if ((l1 < l2 && l2 < r1 && r1 < r2) || (l2 < l1 && l1 < r2 && r2 < r1)) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }

        // Contar componentes conectados
        vector<bool> visited(n, false);
        int components = 0;

        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            for (int v : g[u]) {
                if (!visited[v]) dfs(v);
            }
        };

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i);
                components++;
            }
        }

        // Resultado
        int minOn = components;
        int ways = 1;
        for (int i = 0; i < components; i++)
            ways = (ways * 2) % MOD;

        cout << minOn << " " << ways << '\n';
    }

    return 0;
}
