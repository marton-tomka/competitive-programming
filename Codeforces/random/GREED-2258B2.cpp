#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> cnt(m + 2);
    ll sum{};
    int mx{};
    for (int i{}; i < n; ++i) {
        int a;
        std::cin >> a;
        ++cnt[a];
        sum += a;
        mx = std::max(mx, a);
    }

    std::vector<int> suf(m + 2);
    for (int i = mx; i >= 1; --i)
        suf[i] = suf[i + 1] + cnt[i];

    std::vector<ll> ans(m + 1, sum);

    int k = 1;
    for (int p = 2; p < mx; p <<= 1, ++k) {
        ll best{};

        for (int d = 1; d <= mx; ++d) {
            ll cur{};

            for (int j = 1, v = d; j < p && v <= mx; ++j, v += d)
                cur += suf[v];
            if (1LL * p * d <= mx)
                cur += cnt[p * d];

            best = std::max(best, cur);
        }
        ans[k] = best;
    }

    for (int k = 1; k <= m; ++k)
        std::cout << ans[k] << " \n"[k == m];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
