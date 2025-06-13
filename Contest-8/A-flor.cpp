#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();
typedef pair<int, int> PII;

vector<int> dijkstra(int start, const vector<vector<PII>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);
    priority_queue<PII, vector<PII>, greater<PII>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, T;
    cin >> P >> T;

    vector<vector<PII>> graph(P);
    vector<tuple<int, int, int>> edges;

    for (int i = 0; i < T; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        graph[u].emplace_back(v, l);
        graph[v].emplace_back(u, l);
        edges.emplace_back(u, v, l);
    }

    // Dijkstra desde la entrada (0) y desde el pico (P-1)
    vector<int> distStart = dijkstra(0, graph);
    vector<int> distEnd = dijkstra(P - 1, graph);
    int minDist = distStart[P - 1];

    long long total = 0;

    for (const auto& [u, v, l] : edges) {
        if ((distStart[u] + l + distEnd[v] == minDist) ||
            (distStart[v] + l + distEnd[u] == minDist)) {
            total += l;
        }
    }

    cout << (2 * total) << '\n';
    return 0;
}
