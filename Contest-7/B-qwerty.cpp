#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;

        vector<vector<int>> adj(26);
        for (int i = 0; i + 1 < (int)s.size(); ++i) {
            int u = s[i]   - 'a';
            int v = s[i+1] - 'a';
            if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }

        bool ok = true;
        for (int c = 0; c < 26; ++c) {
            if (adj[c].size() > 2) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "NO\n";
            continue;
        }

        vector<bool> seen(26, false), in_path(26, false);
        vector<string> segments;

        for (int c = 0; c < 26; ++c) {
            if (!seen[c] && !adj[c].empty()) {
                // BFS to collect this component
                vector<int> comp;
                queue<int> q;
                q.push(c);
                seen[c] = true;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    comp.push_back(u);
                    for (int v : adj[u]) {
                        if (!seen[v]) {
                            seen[v] = true;
                            q.push(v);
                        }
                    }
                }

                int endpoints = 0;
                for (int u : comp) {
                    if (adj[u].size() == 1) 
                        endpoints++;
                }
                if ((int)comp.size() > 1 && endpoints != 2) {
                    ok = false;
                    break;
                }

                int start = comp[0];
                if ((int)comp.size() > 1) {
                    // pick the endpoint
                    for (int u : comp) {
                        if (adj[u].size() == 1) {
                            start = u;
                            break;
                        }
                    }
                }
                string path;
                int prev = -1, cur = start;
                while (true) {
                    path.push_back(char('a' + cur));
                    in_path[cur] = true;
                    int next = -1;
                    for (int v : adj[cur]) {
                        if (v != prev) {
                            next = v;
                            break;
                        }
                    }
                    if (next == -1) break;
                    prev = cur;
                    cur  = next;
                }
                segments.push_back(path);
            }
        }

        if (!ok) {
            cout << "NO\n";
            continue;
        }

        for (int c = 0; c < 26; ++c) {
            if (!in_path[c]) {
                segments.push_back(string(1, char('a' + c)));
            }
        }
        string keyboard;
        for (auto &seg : segments) {
            keyboard += seg;
        }

        cout << "YES\n"
             << keyboard << "\n";
    }
    return 0;
}
