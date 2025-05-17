#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll prefixSum(ll i, ll k) {
    return i * k + i * (i - 1) / 2;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;

        ll total = n * k + n * (n - 1) / 2;

        ll l = 1, r = n;
        ll best = INT_MAX;

        while (r - l <= 3) {
            for (ll i = l; i <= r; ++i) {
                ll left = prefixSum(i, k);
                best = min(best, abs(2 * left - total));
            }
            break;
        }

        while (r - l > 3) {
            ll m1 = l + (r - l) / 3;
            ll m2 = r - (r - l) / 3;

            ll f1 = abs(2 * prefixSum(m1, k) - total);
            ll f2 = abs(2 * prefixSum(m2, k) - total);

            if (f1 < f2) r = m2;
            else l = m1;
        }

        for (ll i = l; i <= r; ++i) {
            ll left = prefixSum(i, k);
            best = min(best, abs(2 * left - total));
        }

        cout << best << '\n';
    }

    return 0;
}
