#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, x;
    std::cin >> n >> x;
    std::vector<int> p;
    int v = x;

    for (int d = 2; 1LL * d * d <= v; ++d) {
        if (v % d)
            continue;

        p.push_back(d);
        while (v % d == 0)
            v /= d;
    }

    if (v > 1)
        p.push_back(v);

    std::vector<ll> sum(p.size());
    for (int i{}; i < n; ++i) {
        int a;
        std::cin >> a;

        for (size_t j{}; j < p.size(); ++j)
            if (a % p[j] == 0)
                sum[j] += a;
    }

    ll ans{};
    for (ll s : sum)
        ans = std::max(ans, s);
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
