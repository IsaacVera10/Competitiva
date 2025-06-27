#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}

    // suma de prefijo [1..i]
    ll query(int i) const {
        ll s = 0;
        while (i > 0) {
            s += f[i];
            i -= i & -i;
        }
        return s;
    }

    // añade v en la posición i
    void update(int i, ll v) {
        while (i <= n) {
            f[i] += v;
            i += i & -i;
        }
    }

    // suma en rango [l..r]
    ll rangeQuery(int l, int r) const {
        return query(r) - query(l-1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Fenwick fw(n);
    // construimos el Fenwick tree
    for (int i = 1; i <= n; i++) {
        fw.update(i, a[i]);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            ll u;
            cin >> k >> u;
            ll delta = u - a[k];
            a[k] = u;
            fw.update(k, delta);
        } else {
            int l, r;
            cin >> l >> r;
            cout << fw.rangeQuery(l, r) << "\n";
        }
    }

    return 0;
}
