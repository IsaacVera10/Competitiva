#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 100005;
vector<ll> lengths;

char solve(int n, ll k) {
    while (true) {
        if (n == 1) return 'N';
        if (n == 2) return 'A';

        if (k <= lengths[n - 2]) {
            n = n - 2;
        } else {
            k -= lengths[n - 2];
            n = n - 1;
        }
    }
}

int main() {
    int N;
    ll K;
    cin >> N >> K;

    lengths.resize(N + 2);
    lengths[1] = lengths[2] = 1;

    for (int i = 3; i <= N; ++i) {
        lengths[i] = lengths[i - 1] + lengths[i - 2];
        if (lengths[i] > 1e18) lengths[i] = 1e18;
    }

    cout << solve(N, K) << '\n';
    return 0;
}
