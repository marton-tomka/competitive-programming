#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll m, k;
    std::cin >> n >> m >> k;
    std::vector<ll> l(n), r(n), pre(n + 1, 0);
    for (int i{}; i < n; ++i) {
        std::cin >> l[i] >> r[i];
        pre[i + 1] = pre[i] + r[i] - l[i] + 1;
    }

    auto g = [&](ll x) -> ll {
        int i = static_cast<int>(std::ranges::upper_bound(l, x) - l.begin());
        if (i == 0)
            return 0;
        return pre[i - 1] + std::min(r[i - 1], x) - l[i - 1] + 1;
    };
    auto f = [&](ll s) -> ll { return g(s + m - 1) - g(s - 1); };

    if (k == 0) {
        std::cout << r[n - 1] + 1 << '\n';
        return;
    }

    ll smax = l[0], fmax = -1;
    for (int i{}; i < n; ++i) {
        ll v = f(l[i]);
        if (v > fmax) {
            fmax = v;
            smax = l[i];
        }
    }

    if (k > fmax) {
        std::cout << -1 << '\n';
        return;
    }

    ll lo = smax, hi = r[n - 1] + 1;
    while (hi - lo > 1) {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid) >= k)
            lo = mid;
        else
            hi = mid;
    }
    std::cout << lo << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
