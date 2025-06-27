#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---- Sparse Table para GCD en rango ----
struct GcdSparse {
    int n, L;
    vector<vector<ll>> st;
    vector<int> lg;
    GcdSparse(const vector<ll>& a) {
        n = a.size();
        L = 32 - __builtin_clz(n);
        st.assign(L, vector<ll>(n));
        lg.assign(n+1, 0);
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i/2] + 1;
        st[0] = a;
        for (int k = 1; k < L; k++) {
            for (int i = 0; i + (1<<k) <= n; i++) {
                st[k][i] = gcd(st[k-1][i], st[k-1][i + (1<<(k-1))]);
            }
        }
    }
    // gcd en [l..r], 0-based
    ll query(int l, int r) const {
        int k = lg[r - l + 1];
        return gcd(st[k][l], st[k][r - (1<<k) + 1]);
    }
};

// ---- Criba de primos hasta 31623 ----
static vector<int> sieve_primes() {
    const int M = 31623;
    vector<bool> is(M+1, true);
    vector<int> primes;
    is[0] = is[1] = false;
    for (int i = 2; i <= M; i++) {
        if (is[i]) {
            primes.push_back(i);
            if ((ll)i*i <= M)
                for (int j = i*i; j <= M; j += i)
                    is[j] = false;
        }
    }
    return primes;
}

// ---- Factoriza x por trial division usando la lista de primos ----
static void factor(ll x, const vector<int>& primes,
                   vector<pair<ll,int>>& fac) {
    fac.clear();
    for (int p : primes) {
        if ((ll)p * p > x) break;
        if (x % p == 0) {
            int e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            fac.emplace_back(p, e);
        }
    }
    if (x > 1) fac.emplace_back(x, 1);
}

// ---- Genera todos los divisores a partir de la factorización recursivamente ----
static void gen_divs(int idx, ll cur,
    const vector<pair<ll,int>>& fac, vector<ll>& divs) {
    if (idx == (int)fac.size()) {
        divs.push_back(cur);
        return;
    }
    ll p = fac[idx].first;
    int e = fac[idx].second;
    for (int k = 0; k <= e; k++) {
        gen_divs(idx+1, cur, fac, divs);
        cur *= p;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> f(n);
    for (int i = 0; i < n; i++)
        cin >> f[i];

    // 1) Preparamos sparse table de GCD
    GcdSparse st(f);

    // 2) Asociamos cada valor v a la lista de posiciones donde aparece
    unordered_map<ll, vector<int>> pos;
    pos.reserve(n*2);
    for (int i = 0; i < n; i++) {
        pos[f[i]].push_back(i);
    }
    for (auto& [v, vec] : pos) {
        sort(vec.begin(), vec.end());
    }

    // 3) Criba de primos
    vector<int> primes = sieve_primes();

    int q;
    cin >> q;
    vector<pair<ll,int>> fac;
    vector<ll> divisores;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;              // pasamos a 0-based
        ll G = st.query(l, r);

        // Factorizamos G y generamos sus divisores
        factor(G, primes, fac);
        divisores.clear();
        gen_divs(0, 1, fac, divisores);

        // Para cada divisor d contamos cuántas posiciones en [l..r]
        ll cnt = 0;
        for (ll d : divisores) {
            auto it = pos.find(d);
            if (it == pos.end()) continue;
            // en it->second tenemos la lista ordenada de índices
            auto& vec = it->second;
            // contamos cuántos x en vec cumplen l <= x <= r
            int c = int(upper_bound(vec.begin(), vec.end(), r)
                       - lower_bound(vec.begin(), vec.end(), l));
            cnt += c;
        }

        // total en el segmento = (r-l+1), los demás los come Jorge
        cout << (r - l + 1 - cnt) << "\n";
    }

    return 0;
}
