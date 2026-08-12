#include <bits/stdc++.h>
using ll = long long;

void solve() {
    std::string a, b;
    std::cin >> a >> b;

    int n = a.length();
    int m = b.length();

    std::vector<int> pa(n);
    pa[0] = (a[0] - '0') % 10;
    for (int i = 1; i < n; ++i) {
        pa[i] = (pa[i - 1] + a[i] - '0') % 10;
    }

    std::vector<int> pb(m);
    pb[0] = (b[0] - '0') % 10;
    for (int j = 1; j < m; ++j) {
        pb[j] = (pb[j - 1] + b[j] - '0') % 10;
    }

    if (pa[n - 1] != pb[m - 1]) {
        std::cout << -1 << '\n';
        return;
    }

    std::vector<int> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int prev{};
        for (int j = 1; j <= m; ++j) {
            int temp = dp[j];
            if (pa[i - 1] == pb[j - 1])
                dp[j] = prev + 1;
            else
                dp[j] = std::max(dp[j], dp[j - 1]);

            prev = temp;
        }
    }

    std::cout << dp[m] << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
