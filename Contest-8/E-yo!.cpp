#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N;

    vector<string> items(N);
    unordered_map<string, int> name_to_index;

    for (int i = 0; i < N; ++i) {
        cin >> items[i];
        name_to_index[items[i]] = i;
    }

    cin >> M;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        string a, b;
        cin >> a >> b;
        int u = name_to_index[a];
        int v = name_to_index[b];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(N, -1);
    for (int i = 0; i < N; ++i) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        cout << "impossible\n";
                        return 0;
                    }
                }
            }
        }
    }

    // Imprimir artículos de cada grupo en el orden original
    vector<string> walter, jesse;
    for (int i = 0; i < N; ++i) {
        if (color[i] == 0)
            walter.push_back(items[i]);
        else
            jesse.push_back(items[i]);
    }

    for (const string& name : walter)
        cout << name << ' ';
    cout << '\n';
    for (const string& name : jesse)
        cout << name << ' ';
    cout << '\n';

    return 0;
}
