#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 1'000'000'007;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> dif(n + 1);
    std::vector<int> need(n + 1, -1);

    for (int k = 1; k <= n; ++k) {
        int a;
        std::cin >> a;

        int l = std::min<ll>(n, 1LL * a * k);
        int r = std::min<ll>(n, 1LL * (a + 1) * k);

        ++dif[l];
        --dif[r];

        for (int j{}; j < a; ++j) {
            int r = std::min<ll>(n, 1LL * (j + 1) * k);
            need[r] = std::max(need[r], j * k);
        }
    }

    std::vector<ll> dp(n + 1);
    dp[0] = 1;
    ll ways = 1;
    int ban{}, ptr{}, req = -1;

    for (int i{}; i <= n; ++i) {
        req = std::max(req, need[i]);

        while (ptr <= req) {
            ways -= dp[ptr++];
            if (ways < 0)
                ways += MOD;
        }

        if (i == n)
            break;

        ban += dif[i];
        if (ban)
            continue;

        dp[i + 1] = ways;
        ways += ways;
        if (ways >= MOD)
            ways -= MOD;
    }

    std::cout << ways << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
