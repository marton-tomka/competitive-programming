#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> a(n);
    for (ll& i : a)
        std::cin >> i;

    int r = std::sqrt(n);
    ll ans{};
    for (int i = 1; i <= r; ++i) {
        for (int j{}; j < n; ++j) {
            ll i = j - 1LL * i * a[j];

            if (i >= 0 && a[i] == i)
                ++ans;

            if (a[j] <= r)
                continue;

            ll k = j + 1LL * i * a[j];

            if (k < n && a[k] == i)
                ++ans;
        }
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
