#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> deg(n+1, 0);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            deg[u]++;
            deg[v]++;
        }

        // Contamos hojas (grado = 1) y vértices de grado > 1
        int leafs = 0, bigs = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1)       leafs++;
            else if (deg[i] > 1)   bigs++;
        }

        // En un "snowflake" válido:
        //   bigs = x (hubs) + 1 (centro)  ⇒  x = bigs - 1
        //   leafs = x * y                ⇒  y = leafs / x
        int x = bigs - 1;
        int y = leafs / x;

        cout << x << " " << y << "\n";
    }
    return 0;
}
