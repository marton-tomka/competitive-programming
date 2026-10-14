#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> deg(n);
    for (int i{}; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        ++deg[--u];
        ++deg[--v];
    }

    if (std::ranges::count(deg, 0)) {
        std::cout << "Brain Melt\n";
    } else if (m == n - 1 && std::ranges::max(deg) == n - 1) {
        std::cout << "2\n";
    } else {
        std::cout << "Many\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
