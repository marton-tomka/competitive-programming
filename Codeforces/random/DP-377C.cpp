#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n), d(n);
    for (int& x : a)
        std::cin >> x;

    int neg{}, pos{};
    for (int i{}; i < n; ++i) {
        int b;
        std::cin >> b;

        d[i] = a[i] - k * b;

        if (d[i] < 0)
            neg -= d[i];
        else
            pos += d[i];
    }

    int lim = neg + pos;
    std::vector<int> dp(lim + 1, -1);
    dp[neg] = 0;

    for (int i{}; i < n; ++i) {
        int x = d[i];

        if (x >= 0) {
            for (int j = lim - x; j >= 0; --j) {
                if (dp[j] == -1)
                    continue;
                dp[j + x] = std::max(dp[j + x], dp[j] + a[i]);
            }
        } else {
            for (int j = -x; j <= lim; ++j) {
                if (dp[j] == -1)
                    continue;
                dp[j + x] = std::max(dp[j + x], dp[j] + a[i]);
            }
        }
    }

    std::cout << (dp[neg] > 0 ? dp[neg] : -1) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
