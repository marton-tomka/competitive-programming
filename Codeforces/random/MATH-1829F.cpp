#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cnt(n);
    for (int i{}; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        cnt[--u]++;
        cnt[--v]++;
    }

    std::map<int, int> seen{};
    for (int i : cnt) {
        if (i == 1)
            continue;
        seen[i]++;
    }

    int x{}, y{};
    for (auto [k, v] : seen) {
        if (v == 1)
            x = k;
        else
            y = k - 1;
    }

    if (seen.size() == 1) {
        x = seen.begin()->first;
        y = x - 1;
    }

    std::cout << x << ' ' << y << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
