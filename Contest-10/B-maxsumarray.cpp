#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum;      // suma total del segmento
    ll pref;     // mejor suma de prefijo
    ll suff;     // mejor suma de sufijo
    ll best;     // mejor suma de subarray interno
    Node(): sum(0), pref(0), suff(0), best(0) {}
    Node(ll x): sum(x), pref(max(0LL,x)), suff(max(0LL,x)), best(max(0LL,x)) {}
};

Node merge(const Node &L, const Node &R) {
    Node res;
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.best = max({L.best, R.best, L.suff + R.pref});
    return res;
}

struct SegTree {
    int n;
    vector<Node> st;
    SegTree(const vector<ll> &a) {
        n = a.size();
        st.resize(4*n);
        build(1, 0, n-1, a);
    }
    void build(int p, int l, int r, const vector<ll> &a) {
        if (l == r) {
            st[p] = Node(a[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1,   l,   m, a);
        build(p<<1|1, m+1, r, a);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    void update(int p, int l, int r, int idx, ll val) {
        if (l == r) {
            st[p] = Node(val);
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx, val);
        else         update(p<<1|1, m+1, r, idx, val);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }
    // actualiza posición idx (0-based) a val
    void update(int idx, ll val) {
        update(1, 0, n-1, idx, val);
    }
    // devuelve la mejor suma de subarray (≥ 0)
    ll query_max_subarray() const {
        return st[1].best;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    SegTree st(a);
    while (m--) {
        int k;
        ll x;
        cin >> k >> x;
        --k; // pasar a 0-based
        st.update(k, x);
        cout << st.query_max_subarray() << "\n";
    }

    return 0;
}
