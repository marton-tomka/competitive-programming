#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll s;
    int q;
    std::cin >> s >> q;

    std::vector<ll> d;
    for (ll i = 1; i * i <= s; ++i) {
        if (s % i)
            continue;

        d.push_back(i);
        if (i * i != s)
            d.push_back(s / i);
    }

    std::ranges::sort(d);
    int n = d.size();
    std::vector<ll> pref(n + 1);

    for (int i{}; i < n; ++i) {
        ll prv = i ? d[i - 1] : 0;
        pref[i + 1] = pref[i] + (d[i] - prv) * (s / d[i]);
    }

    auto area = [&](ll x) {
        int i = std::ranges::lower_bound(d, x) - d.begin();
        ll prv = i ? d[i - 1] : 0;

        return pref[i] + (x - prv) * (s / d[i]);
    };

    while (q--) {
        ll x, y;
        std::cin >> x >> y;

        int i = std::ranges::upper_bound(d, s / y) - d.begin() - 1;
        ll cut = d[i];

        if (x <= cut) {
            std::cout << x * y << '\n';
            continue;
        }

        ll ans = cut * y + area(x) - pref[i + 1];
        std::cout << ans << '\n';
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
