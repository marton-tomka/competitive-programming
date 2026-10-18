#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    int k = n == 1 ? 0 : (n + 1) / 2;
    std::cout << k << '\n';

    for (int i = 1; i <= k; ++i)
        std::cout << i << ' ' << std::min(n, i + k - 1) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
