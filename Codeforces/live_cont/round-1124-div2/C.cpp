#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<ll> a(n);
    for (ll& x : a)
        std::cin >> x;

    int geeg = n - k + 1;
    int stay = k - 1;
    int p = std::min(geeg, stay);
    ll ans{};

    for (int i{}; i < p; ++i)
        ans += std::max(a[i], a[n - i - 1]);

    if (geeg > stay)
        for (int i = p; i < n - p; ++i)
            ans += a[i];

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
