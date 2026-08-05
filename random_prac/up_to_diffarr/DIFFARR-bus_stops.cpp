#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m, C;
    std::cin >> n >> m >> C;

    std::vector<int> diff(n + 1, 0);
    for (int i{}; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        diff[a] += 1;
        diff[b] -= 1;
    }

    int current_seats = 0;
    bool over_capacity = false;
    for (int segment = 1; segment < n; ++segment) {
        current_seats += diff[segment];
        if (current_seats > C) {
            over_capacity = true;
            break;
        }
    }

    std::cout << (over_capacity ? "YES" : "NO") << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
