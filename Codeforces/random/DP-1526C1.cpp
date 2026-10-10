#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> dp(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        ll a;
        std::cin >> a;

        for (int j = i; j >= 1; --j) {
            if (dp[j - 1] == -1 || dp[j - 1] + a < 0)
                continue;

            dp[j] = std::max(dp[j], dp[j - 1] + a);
        }
    }

    for (int j = n; j >= 0; --j) {
        if (dp[j] == -1)
            continue;
        std::cout << j << '\n';
        break;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
