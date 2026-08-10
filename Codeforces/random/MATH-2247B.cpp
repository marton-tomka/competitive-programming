#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n, k, m;
    std::cin >> n >> k >> m;

    if (k > m) {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
    for (int i = 1; i <= n; ++i) {
        if (i % k == 0) {
            std::cout << m + 1 - k << (i == n ? "" : " ");
        } else {
            std::cout << 1 << (i == n ? "" : " ");
        }
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
