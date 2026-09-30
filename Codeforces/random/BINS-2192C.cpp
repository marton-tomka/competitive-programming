#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll h, k;
    std::cin >> n >> h >> k;
    std::vector<ll> a(n), suf(n + 1);
    ll sum{};
    for (ll& x : a) {
        std::cin >> x;
        sum += x;
    }

    for (int i = n - 1; i >= 0; --i)
        suf[i] = std::max(suf[i + 1], a[i]);

    ll cyc = (h - 1) / sum;
    ll rem = h - cyc * sum;
    ll pref{}, mn = a[0];

    for (int i{}; i < n; ++i) {
        pref += a[i];
        mn = std::min(mn, a[i]);

        ll best = pref + std::max(0LL, suf[i + 1] - mn);

        if (best >= rem) {
            std::cout << cyc * (n + k) + i + 1 << '\n';
            return;
        }
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
