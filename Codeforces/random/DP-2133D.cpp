#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> h(n);
    for (ll& x : h)
        std::cin >> x;

    ll p2{};
    ll p1 = h[0];

    for (int i = 1; i < n; ++i) {
        ll one = p1 + h[i] - 1;
        ll maxf = p2 + h[i - 1] + std::max(0LL, h[i] - i);
        ll cur = std::min(one, maxf);

        p2 = p1;
        p1 = cur;
    }

    std::cout << p1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
