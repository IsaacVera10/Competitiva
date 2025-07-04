#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int tc = 0;
    while (true) {
        if (!getline(cin, s)) break;
        if (s.rfind("END", 0) == 0)  // línea empieza con "END"
            break;
        ++tc;
        int n = s.size();

        // Manacher: palíndromos impares
        vector<int> d1(n);
        for(int i = 0, l = 0, r = -1; i < n; ++i){
            int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
            while (0 <= i-k && i+k < n && s[i-k] == s[i+k]) 
                ++k;
            d1[i] = k--;
            if (i + k > r){
                l = i - k;
                r = i + k;
            }
        }

        // Manacher: palíndromos pares
        vector<int> d2(n);
        for(int i = 0, l = 0, r = -1; i < n; ++i){
            int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
            while (0 <= i-k-1 && i+k < n && s[i-k-1] == s[i+k]) 
                ++k;
            d2[i] = k--;
            if (i + k > r){
                l = i - k - 1;
                r = i + k;
            }
        }

        // Buscamos la longitud máxima
        int ans = 1;  // al menos 1 (cualquier caracter)
        for(int i = 0; i < n; ++i){
            ans = max(ans, 2*d1[i] - 1);
            ans = max(ans, 2*d2[i]);
        }

        cout << "Case " << tc << ": " << ans << "\n";
    }

    return 0;
}
