#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // a[i] = 1 si el vértice i tiene un gato, 0 en caso contrario
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // Construimos la lista de adyacencia del árbol
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int answer = 0;
    // Cola para BFS: (vértice actual, padre, cantidad de gatos consecutivos hasta aquí)
    queue<tuple<int,int,int>> q;
    q.emplace(1, 0, a[1] == 1 ? 1 : 0);

    while (!q.empty()) {
        auto [u, parent, consec] = q.front(); 
        q.pop();

        // Si ya sobrepasamos el máximo de gatos consecutivos, abandonamos esta rama
        if (consec > m) 
            continue;

        bool isLeaf = true;
        for (int w : adj[u]) {
            if (w == parent) 
                continue;
            isLeaf = false;
            int nextConsec = (a[w] == 1 ? consec + 1 : 0);
            q.emplace(w, u, nextConsec);
        }

        // Si u no tiene hijos distintos al padre, es hoja (restaurante)
        if (isLeaf) 
            answer++;
    }

    cout << answer << "\n";
    return 0;
}
