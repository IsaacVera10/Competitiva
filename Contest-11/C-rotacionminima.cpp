#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n];
        char b = s[(j + k) % n];
        if (a == b) {
            ++k;
        } else if (a > b) {
            i = i + k + 1;
            if (i <= j) i = j + 1;
            k = 0;
        } else {
            // i produce una rotación menor, descartamos j..j+k
            j = j + k + 1;
            if (j <= i) j = i + 1;
            k = 0;
        }
    }

    int start = min(i, j);
    // Imprimimos la rotación mínima
    for (int t = 0; t < n; ++t) {
        cout << s[(start + t) % n];
    }
    cout << "\n";

    return 0;
}
