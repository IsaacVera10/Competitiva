#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

ll mod_pow(ll a, ll b) {
    if (a == 0 && b == 0) return 1;
    ll result = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        ll a, b;
        cin >> a >> b;
        cout << mod_pow(a, b) << '\n';
    }

    return 0;
}
