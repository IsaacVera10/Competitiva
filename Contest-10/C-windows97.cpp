#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}

    // Suma de prefijo [1..i]
    int query(int i) const {
        int s = 0;
        while (i > 0) {
            s += f[i];
            i -= i & -i;
        }
        return s;
    }

    // Incrementa A[i] en v (v puede ser negativo)
    void update(int i, int v) {
        while (i <= n) {
            f[i] += v;
            i += i & -i;
        }
    }

    // Suma en rango [l..r]
    int rangeQuery(int l, int r) const {
        return query(r) - query(l-1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    Fenwick fw(N);
    vector<char> bit(N+1, 0);  // bit[i]=0 o 1

    while (K--) {
        char op;
        cin >> op;
        if (op == 'F') {
            int i;
            cin >> i;
            // Flipping: si era 0 → 1, si era 1 → 0
            if (bit[i] == 0) {
                bit[i] = 1;
                fw.update(i, +1);
            } else {
                bit[i] = 0;
                fw.update(i, -1);
            }
        } else if (op == 'C') {
            int l, r;
            cin >> l >> r;
            int ans = fw.rangeQuery(l, r);
            cout << ans << "\n";
        }
    }

    return 0;
}
