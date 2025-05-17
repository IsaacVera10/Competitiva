#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MOD = 10000007;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ll n, k;
    while ( (cin >> n >> k) ) {
        if (n == 0 && k == 0) 
            break;

        // Z_n + Z_{n-1} - 2 Z_{n-2}
        // = [n^k + 2*(n-1)^k] + [n^n + 2*(n-1)^(n-1)]   (todo mod MOD)
        ll t1 = mod_pow(n,   k);
        ll t2 = mod_pow(n-1, k);
        ll t3 = mod_pow(n,   n);
        ll t4 = mod_pow(n-1, n-1);

        ll ans = (
               t1
             + 2 * (t2 % MOD)
             + t3
             + 2 * (t4 % MOD)
        ) % MOD;

        cout << ans << "\n";
    }
    return 0;
}
