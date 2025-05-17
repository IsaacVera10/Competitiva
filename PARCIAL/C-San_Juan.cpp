#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Para almacenar un bitmask de hasta 40 aristas
using Mask = unsigned long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Leemos las 5 ubicaciones
    vector<pair<int,int>> T(5);
    for(int i = 0; i < 5; i++){
        cin >> T[i].first >> T[i].second;
    }

    // 2) Construimos las coordenadas únicas Xs, Ys (rejilla de Hanan)
    vector<int> Xs, Ys;
    for(auto &p: T){
        Xs.push_back(p.first);
        Ys.push_back(p.second);
    }
    sort(Xs.begin(), Xs.end());
    Xs.erase(unique(Xs.begin(), Xs.end()), Xs.end());
    sort(Ys.begin(), Ys.end());
    Ys.erase(unique(Ys.begin(), Ys.end()), Ys.end());
    int nx = Xs.size(), ny = Ys.size();

    // 3) Enumeramos **todas** las aristas unitarias de Hanan (lotes)
    //    y les damos un ID 0..E-1, guardando su “peso” (número de tramos reales)
    map<pair<pair<int,int>,pair<int,int>>,int> edge_id;
    vector<ll> edge_w;
    auto add_edge = [&](int x1,int y1,int x2,int y2){
        auto A = make_pair(x1,y1), B = make_pair(x2,y2);
        if(A > B) swap(A,B);
        if(!edge_id.count({A,B})){
            int id = edge_w.size();
            edge_id[{A,B}] = id;
            // peso = |x2-x1| + |y2-y1|
            edge_w.push_back( ll(abs(x2-x1) + abs(y2-y1)) );
        }
    };
    // horizontales
    for(int j = 0; j < ny; j++){
        for(int i = 0; i+1 < nx; i++){
            add_edge(Xs[i], Ys[j], Xs[i+1], Ys[j]);
        }
    }
    // verticales
    for(int i = 0; i < nx; i++){
        for(int j = 0; j+1 < ny; j++){
            add_edge(Xs[i], Ys[j], Xs[i],   Ys[j+1]);
        }
    }
    int E = edge_w.size();

    // 4) Preparamos un grafo de nodos = índices (ix,iy) -> id = ix*ny+iy
    auto node_id = [&](int ix,int iy){ return ix*ny + iy; };
    int Nnodes = nx*ny;
    // guardamos adyacencia “sin dirigir”
    vector<vector<pair<int,int>>> adj(Nnodes);
    for(auto &kv : edge_id){
        auto A = kv.first.first;
        auto B = kv.first.second;
        int id = kv.second;
        // convertimos A y B a ids
        int ixA = int(lower_bound(Xs.begin(), Xs.end(), A.first) - Xs.begin());
        int iyA = int(lower_bound(Ys.begin(), Ys.end(), A.second)- Ys.begin());
        int ixB = int(lower_bound(Xs.begin(), Xs.end(), B.first) - Xs.begin());
        int iyB = int(lower_bound(Ys.begin(), Ys.end(), B.second)- Ys.begin());
        int u = node_id(ixA,iyA);
        int v = node_id(ixB,iyB);
        adj[u].push_back({v,id});
        adj[v].push_back({u,id});
    }

    // 5) Para cada uno de los 10 pares de terminales, enumeramos **todas**
    //    las rutas de peso mínimo en la rejilla de Hanan, guardándolas como
    //    bit‐masks de aristas.
    vector<pair<int,int>> pairs;
    for(int i=0;i<5;i++)
      for(int j=i+1;j<5;j++)
        pairs.emplace_back(i,j);
    int P = pairs.size(); // 10
    vector<vector<Mask>> opts(P);

    for(int k=0;k<P;k++){
        auto [i,j] = pairs[k];
        int xi = T[i].first,  yi = T[i].second;
        int xj = T[j].first,  yj = T[j].second;
        // índices en Xs, Ys
        int ix0 = int(lower_bound(Xs.begin(), Xs.end(), xi) - Xs.begin());
        int iy0 = int(lower_bound(Ys.begin(), Ys.end(), yi) - Ys.begin());
        int ixT = int(lower_bound(Xs.begin(), Xs.end(), xj) - Xs.begin());
        int iyT = int(lower_bound(Ys.begin(), Ys.end(), yj) - Ys.begin());
        ll D = ll(abs(xi-xj) + abs(yi-yj));  // peso total requerido

        // direcciones permitidas
        int dx = (xj>xi? +1 : (xj<xi? -1:0));
        int dy = (yj>yi? +1 : (yj<yi? -1:0));

        // DFS en DAG implícito
        function<void(int,int,Mask,ll)> dfs = [&](int ix,int iy,Mask used,ll acc){
            if(ix==ixT && iy==iyT){
                // llegamos con peso exacto
                opts[k].push_back(used);
                return;
            }
            int u = node_id(ix,iy);
            for(auto [v,eid]: adj[u]){
                int nix = v / ny, niy = v % ny;
                // permitimos sólo avanzar en la dirección correcta
                if(nix-ix == dx && niy==iy){ 
                    // horizontal válida
                } else if(niy-iy == dy && nix==ix){
                    // vertical válida
                } else continue;
                ll w = edge_w[eid];
                ll nxt = acc + w;
                if(nxt > D) continue;
                // distancia restante mínima (Hanan grid) = |Xs[nix]-xj| + |Ys[niy]-yj|
                ll rem = ll(abs(Xs[nix]-xj) + abs(Ys[niy]-yj));
                if(nxt + rem != D) continue;
                dfs(nix,niy, used | (Mask(1)<<eid), nxt);
            }
        };

        dfs(ix0, iy0, 0ULL, 0LL);
        // quitamos posibles duplicados (con bitmask iguales)
        sort(opts[k].begin(), opts[k].end());
        opts[k].erase(unique(opts[k].begin(), opts[k].end()), opts[k].end());
    }

    // 6) Ahora probamos **todas** las combinaciones de elegir 1 ruta de cada par
    //    con un backtracking muy directo y pruning por coste actual >= mejor
    ll best = LLONG_MAX;
    function<void(int,Mask,ll)> go = [&](int k, Mask used, ll cost){
        if(cost >= best) return;
        if(k==P){
            best = cost;
            return;
        }
        for(Mask m : opts[k]){
            Mask uni = used | m;
            // incrementamos coste sólo de las aristas añadidas en este paso
            Mask added = uni ^ used;
            ll c2 = cost;
            // sumamos los pesos de los bits en 'added'
            while(added){
                int e = __builtin_ctzll(added);
                added &= added-1;
                c2 += edge_w[e];
                if(c2 >= best) break;
            }
            if(c2 < best)
                go(k+1, uni, c2);
        }
    };
    go(0,0ULL,0LL);

    cout << best << "\n";
    return 0;
}
