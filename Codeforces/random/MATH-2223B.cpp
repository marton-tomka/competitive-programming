#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 998'244'353;

ll bexp(ll b, ll e, ll mod) {
    ll r = 1;
    b %= mod;
    while (e > 0) {
        if (e & 1)
            r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> a(n), b(n);
    for (ll& x : a)
        std::cin >> x;
    for (ll& x : b)
        std::cin >> x;

    if (n == 1) {
        std::cout << 0 << '\n';
        return;
    }

    using fr = std::pair<ll, ll>;
    auto less = [](const fr& u, const fr& v) { return u.first * v.second < v.first * u.second; };

    std::vector<fr> xs, ys;
    xs.reserve(static_cast<size_t>(n) * (n - 1) / 2);
    ys.reserve(static_cast<size_t>(n) * (n - 1));
    for (int i{}; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            xs.push_back({a[i], a[j]});
            ys.push_back({b[j], b[i]});
            ys.push_back({b[i], b[j]});
        }

    std::ranges::sort(xs, less);
    std::ranges::sort(ys, less);

    ll cnt{};
    size_t p{};
    for (const auto& x : xs) {
        while (p < ys.size() && less(ys[p], x))
            ++p;
        cnt += static_cast<ll>(p);
    }

    ll den = static_cast<ll>(n) * (n - 1) % MOD;
    std::cout << cnt % MOD * bexp(den, MOD - 2, MOD) % MOD << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
