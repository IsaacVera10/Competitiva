#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, n, m;
    cin>>T;

    while(T--){
        int N, M;
        cin >> N >> M;
        vector<int> a(N), b(M);
        for (int i = 0; i < N; ++i) cin >> a[i];
        for (int i = 0; i < M; ++i) cin >> b[i];

        vector<int> pi(M); //Matriz de prefijos
        pi[0] = 0;
        for (int i = 1, j = 0; i < M; ++i) {
            while (j > 0 && b[i] != b[j])
                j = pi[j-1];
            if (b[i] == b[j]) 
                ++j;
            pi[i] = j;
        }

        int j = 0, answer = -1;
        for (int i = 0; i < N; ++i) {//búsqueda de coincidencias
            while (j > 0 && a[i] != b[j])
                j = pi[j-1];
            if (a[i] == b[j])
                ++j;
            if (j == M) {
                answer = i - M + 2;
                break;
            }
        }

        cout << answer << "\n";
    }
    return 0;
}