#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char key;
    string s;

    while ( (cin >> key >> s) ) {
        int n = s.size();

        string t(n, ' ');
        for (int i = 0; i < n; ++i) {
            t[i] = char((s[i] - key + 26) % 26 + 'a');
        }

        vector<int> d1(n);
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
            while (i - k >= 0 && i + k < n && t[i - k] == t[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }

        vector<int> d2(n);
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
            while (i - k - 1 >= 0 && i + k < n && t[i - k - 1] == t[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }

        int bestLen = 0, bestL = 0, bestR = -1;
        for (int i = 0; i < n; ++i) {
            int len = 2*d1[i] - 1;
            if (len >= 2) {
                int l = i - d1[i] + 1;
                int r = i + d1[i] - 1;
                if (len > bestLen || (len == bestLen && l < bestL)) {
                    bestLen = len;
                    bestL = l;
                    bestR = r;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            int len = 2*d2[i];
            if (len >= 2) {
                int l = i - d2[i];
                int r = i + d2[i] - 1;
                if (len > bestLen || (len == bestLen && l < bestL)) {
                    bestLen = len;
                    bestL = l;
                    bestR = r;
                }
            }
        }

        if (bestLen < 2) {
            cout << "No solution!\n";
        } else {
            cout << bestL << ' ' << bestR << "\n"
                 << t.substr(bestL, bestLen) << "\n";
        }
    }

    return 0;
}
