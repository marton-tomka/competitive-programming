#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    ll mn;
    std::cin >> mn;

    ll mx = mn, best = mn;
    for (int i = 1; i < n; ++i) {
        ll x;
        std::cin >> x;

        best = std::max(best, x + std::max(mx, -mn));
        mn = std::min(x, x + 2 * mn);
        mx = std::max(x, x + 2 * mx);
    }

    std::cout << best << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
