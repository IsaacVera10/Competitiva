#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    long long n;
    cin >> n;

    long long a = 0, b = 0, c = 0, d = 1;

    for (long long i = 0; i < n; ++i) {
        long long na = (b + c + d) % MOD;
        long long nb = (a + c + d) % MOD;
        long long nc = (a + b + d) % MOD;
        long long nd = (a + b + c) % MOD;
        a = na; b = nb; c = nc; d = nd;
    }

    cout << d << endl;
    return 0;
}
