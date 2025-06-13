#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long n, k;
        cin >> n >> k;

        bool firstWins;
        if (k % 3 != 0) {
            // Si k ≢ 0 (mod 3), P-posiciones son n ≡ 0 (mod 3)
            firstWins = (n % 3 != 0);
        } else {
            // Si k ≡ 0 (mod 3), usamos r = n % (k+1)
            long long r = n % (k + 1);
            // P-posición si r ≠ k y r ≡ 0 (mod 3)
            firstWins = !(r != k && r % 3 == 0);
        }

        cout << (firstWins ? "Alice" : "Bob") << "\n";
    }

    return 0;
}
