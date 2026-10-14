#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::array<int, 4> p5, p6;
    p5.fill(n + 1);
    p6.fill(n + 1);
    std::vector<ll> dc(n + 2), dm(n + 2);

    for (int i = n; i >= 1; --i) {
        for (int j{}; j < 4; ++j) {
            if (s[i - 1] == "2025"[j])
                p5[j] = j == 3 ? i : p5[j + 1];

            if (s[i - 1] == "2026"[j])
                p6[j] = j == 3 ? i : p6[j + 1];
        }

        int l = p5[0], r = std::min(n, p6[0] - 1);
        if (l > r)
            continue;

        dc[i] += r - l + 1;
        dc[l + 1] += l;
        dc[r + 1] -= r + 1;

        --dm[l + 1];
        ++dm[r + 1];
    }

    ll c{}, d{};
    for (int i = 1; i <= n; ++i) {
        c += dc[i];
        d += dm[i];

        ll ans = 1LL * i * (n - i + 1) - c - d * i;
        std::cout << ans << " \n"[i == n];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
