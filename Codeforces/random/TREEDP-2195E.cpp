#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 1'000'000'007;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> l(n), r(n);
    for (int i{}; i < n; ++i) {
        std::cin >> l[i] >> r[i];
        --l[i];
        --r[i];
    }

    std::vector<int> ord;
    ord.reserve(n);
    ord.push_back(0);

    for (int i{}; i < n; ++i) {
        int u = ord[i];

        if (l[u] == -1)
            continue;
        ord.push_back(l[u]);
        ord.push_back(r[u]);
    }

    std::vector<ll> dp(n);

    for (int i = n - 1; i >= 0; --i) {
        int u = ord[i];

        if (l[u] == -1)
            dp[u] = 1;
        else
            dp[u] = (dp[l[u]] + dp[r[u]] + 3) % MOD;
    }

    for (int u : ord) {
        if (l[u] == -1)
            continue;

        dp[l[u]] = (dp[l[u]] + dp[u]) % MOD;
        dp[r[u]] = (dp[r[u]] + dp[u]) % MOD;
    }

    for (ll x : dp)
        std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
