#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n+1);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        // grafo no dirigido
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // dist[i] = distancia mínima desde 1 hasta i
    vector<ll> dist(n+1, INF);
    // parent[i] = vértice anterior en el camino óptimo hacia i
    vector<int> parent(n+1, -1);

    // (dist, nodo)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    dist[1] = 0;
    pq.emplace(0, 1);

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        if(u == n) break; 
        for(auto [v, w] : adj[u]){
            ll nd = d + w;
            if(nd < dist[v]){
                dist[v] = nd;
                parent[v] = u;
                pq.emplace(nd, v);
            }
        }
    }

    if(dist[n] == INF){
        cout << -1 << "\n";
        return 0;
    }

    // Reconstruimos del camino de n hacia 1
    vector<int> path;
    for(int v = n; v != -1; v = parent[v]){
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    // Imprimimos la secuencia de vértices
    for(int i = 0; i < (int)path.size(); i++){
        cout << path[i] << (i+1 < (int)path.size() ? ' ' : '\n');
    }
    return 0;
}
