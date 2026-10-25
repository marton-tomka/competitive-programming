#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 998'244'353;

ll bexp(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1)
            r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return r;
}

void solve() {
    ll n, m, r, c;
    std::cin >> n >> m >> r >> c;

    ll eq = (n - r + 1) * (m - c + 1);
    ll dim = n * m - eq;

    std::cout << bexp(2, dim) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
