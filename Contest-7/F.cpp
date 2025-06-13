#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> G(n);
    for(int i = 0; i < n; i++) 
        cin >> G[i];

    // Buscamos la 'X' donde arranca el robot
    int sx=-1, sy=-1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(G[i][j]=='X'){
                sx = i;
                sy = j;
            }
        }
    }

    // Si k es impar, no hay ciclo posible (paridad del grafo cuadriculado)
    if(k % 2 == 1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // 1) BFS desde (sx,sy) para distancias mínimas a cada celda
    vector<vector<int>> dist(n, vector<int>(m, INF));
    queue<pii> q;
    dist[sx][sy] = 0;
    q.push({sx,sy});
    int drBFS[4] = {1, 0, 0, -1};
    int dcBFS[4] = {0, -1, 1, 0};
    while(!q.empty()){
        auto [r,c] = q.front(); q.pop();
        for(int d = 0; d < 4; d++){
            int nr = r + drBFS[d];
            int nc = c + dcBFS[d];
            if(nr<0||nr>=n||nc<0||nc>=m) continue;
            if(G[nr][nc]=='*') continue;
            if(dist[nr][nc] > dist[r][c] + 1){
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr,nc});
            }
        }
    }

    // 2) Construimos el ciclo de forma greedily paso a paso
    //    en orden alfabético de las letras: 'D' < 'L' < 'R' < 'U'.
    static const vector<pair<char,pii>> MOV = {
        {'D',{ 1,  0}},
        {'L',{ 0, -1}},
        {'R',{ 0,  1}},
        {'U',{-1,  0}}
    };

    int rem = k;
    int r = sx, c = sy;
    string ans;
    ans.reserve(k);

    for(int step = 0; step < k; step++){
        bool moved = false;
        // probamos cada dirección en orden lexicográfico
        for(auto &mv : MOV){
            char  ch = mv.first;
            int dr = mv.second.first;
            int dc = mv.second.second;
            int nr = r + dr;
            int nc = c + dc;
            // debe quedar dentro, no ser obstáculo,
            // y desde allí poder volver en EXACTAMENTE rem-1 pasos
            if(nr<0||nr>=n||nc<0||nc>=m) continue;
            if(G[nr][nc]=='*') continue;
            int d_back = dist[nr][nc];
            if(d_back <= rem-1 && ((rem-1) - d_back) % 2 == 0){
                // podemos elegir este paso
                ans.push_back(ch);
                r = nr;  c = nc;
                rem--;
                moved = true;
                break;
            }
        }
        if(!moved){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // Si llegamos aquí, hemos construido k movimientos
    // y por invariante rem=0 estamos de vuelta en la 'X'.
    cout << ans << "\n";
    return 0;
}
