#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    // construimos una grilla con padding de 1 fila/columna de "agua" alrededor
    vector<string> G(N+2, string(M+2, '0'));
    for(int i = 1; i <= N; i++){
        string s;
        cin >> s;
        for(int j = 1; j <= M; j++){
            G[i][j] = s[j-1];
        }
    }

    // BFS para marcar qué celdas de agua son "mar" (conectadas al exterior)
    vector<vector<bool>> sea(N+2, vector<bool>(M+2, false));
    queue<pair<int,int>> q;
    // arrancamos desde (0,0), que es agua en el padding
    sea[0][0] = true;
    q.push({0,0});

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    while(!q.empty()){
        auto [r,c] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int nr = r + dr[d], nc = c + dc[d];
            if(nr < 0 || nr > N+1 || nc < 0 || nc > M+1) continue;
            if(sea[nr][nc]) continue;
            if(G[nr][nc] == '0'){  // agua
                sea[nr][nc] = true;
                q.push({nr,nc});
            }
        }
    }

    // Ahora contamos para cada celda de tierra cuántos vecinos son mar
    long long coast = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(G[i][j] == '1'){
                for(int d = 0; d < 4; d++){
                    int ni = i + dr[d], nj = j + dc[d];
                    if(sea[ni][nj]) coast++;
                }
            }
        }
    }

    cout << coast << "\n";
    return 0;
}
