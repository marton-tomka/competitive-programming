#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int sum{};
    for (int& x : a) {
        std::cin >> x;
        sum += x;
    }

    if (sum & 1) {
        std::cout << "0\n\n";
        return;
    }

    int half = sum / 2;
    std::vector<bool> dp(half + 1);
    dp[0] = true;

    for (int x : a) {
        for (int j = half; j >= x; --j)
            dp[j] = dp[j] || dp[j - x];
    }

    if (!dp[half]) {
        std::cout << "0\n\n";
        return;
    }

    int best{};
    for (int i = 1; i < n; ++i) {
        if (std::countr_zero(static_cast<unsigned>(a[i])) <
            std::countr_zero(static_cast<unsigned>(a[best])))
            best = i;
    }

    std::cout << "1\n" << best + 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
}
