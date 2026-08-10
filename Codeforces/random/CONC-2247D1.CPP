#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::vector<int> g(n);
    for (int i{}; i < n; ++i) {
        std::cin >> g[i];
        a[i] = g[i];
    }
    std::ranges::sort(g);

    std::map<int, int> diff;
    int mtz = -1;
    for (int i{}; i < n - 1; ++i) {
        ++diff[a[i]];
        if (diff[a[i]] == 0)
            diff.erase(a[i]);

        --diff[g[i]];
        if (diff[g[i]] == 0)
            diff.erase(g[i]);

        if (!diff.empty()) {
            int length = i + 1;
            int zeros{};

            while (length % 2 == 0) {
                ++zeros;
                length /= 2;
            }

            if (zeros > mtz)
                mtz = zeros;
        }
    }

    if (mtz == -1)
        std::cout << "0\n";
    else
        std::cout << (1LL << mtz) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
