#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 998'244'353;
ll add(ll a, ll b) {
    a += b;
    return a >= MOD ? a - MOD : a;
}
ll sub(ll a, ll b) {
    a -= b;
    return a < 0 ? a + MOD : a;
}
ll mul(ll a, ll b) {
    return a * b % MOD;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> cnt(n + 1);
    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;
        ++cnt[x];
    }

    std::vector<int> f;
    int mx{};
    for (int c : cnt) {
        if (!c)
            continue;
        f.push_back(c);
        mx = std::max(mx, c);
    }

    std::vector<ll> dp(mx);
    dp[0] = 1;

    ll all = 1;
    for (int c : f) {
        all = mul(all, c + 1);
        for (int s = mx - 1; s >= c; --s)
            dp[s] = add(dp[s], mul(dp[s - c], c));
    }

    ll bad{};
    for (ll v : dp)
        bad = add(bad, v);

    std::cout << sub(all, bad) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
