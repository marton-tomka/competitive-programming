#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    ll m;
    std::cin >> n >> m >> k;

    ll l = k - 1;
    ll r = n - k;

    auto ok = [&](ll s) {
        if (!s)
            return true;
        if (s > l + r)
            return false;

        ll side = std::max({(s + 1) / 2, s - l, s - r});
        return s + side - 1 <= m;
    };

    ll lo{}, hi = n;

    while (lo + 1 < hi) {
        ll mid = lo + (hi - lo) / 2;

        if (ok(mid))
            lo = mid;
        else
            hi = mid;
    }

    std::cout << lo + 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
