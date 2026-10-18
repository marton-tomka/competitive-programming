#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    int mn = INT_MAX, mx{};
    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;
        mn = std::min(mn, x);
        mx = std::max(mx, x);
    }

    int bits = std::bit_width(static_cast<unsigned>(mn ^ mx));
    std::cout << (mx | ((1 << bits) - 1)) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
