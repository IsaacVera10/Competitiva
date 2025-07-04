#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;
    vector<int64> a(n), b(w);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < w; i++) cin >> b[i];

    // Caso w=1: cualquier posición funciona
    if(w == 1){
        cout << n << "\n";
        return 0;
    }

    // Construimos patrones de diferencias
    int N = n-1, M = w-1;
    vector<int64> t(N), p(M);
    for(int i = 0; i < N; i++)
        t[i] = a[i+1] - a[i];
    for(int j = 0; j < M; j++)
        p[j] = b[j+1] - b[j];

    // Preprocesamiento KMP en p[]
    vector<int> pi(M, 0);
    for(int i = 1, j = 0; i < M; i++){
        while(j > 0 && p[i] != p[j])
            j = pi[j-1];
        if(p[i] == p[j]) 
            j++;
        pi[i] = j;
    }

    // Búsqueda de p[] en t[]
    int ans = 0, j = 0;
    for(int i = 0; i < N; i++){
        while(j > 0 && t[i] != p[j])
            j = pi[j-1];
        if(t[i] == p[j]) 
            j++;
        if(j == M){
            ans++;
            j = pi[j-1];
        }
    }

    cout << ans << "\n";
    return 0;
}
