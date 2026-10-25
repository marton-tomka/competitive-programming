#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    int cnt{};
    int cost = 1;
    while (cost <= n) {
        ll x = std::min(k, n / cost);
        cnt += x;
        n -= x * cost;
        cost *= 2;
    }

    std::cout << cnt << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
