#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    int ans{};
    for (int& x : a) {
        std::cin >> x;
        ans += std::popcount(static_cast<unsigned>(x)) % 2 == 0;
    }

    std::cout << ans;

    while (q--) {
        int p, x;
        std::cin >> p >> x;
        --p;

        ans -= std::popcount(static_cast<unsigned>(a[p])) % 2 == 0;
        a[p] = x;
        ans += std::popcount(static_cast<unsigned>(a[p])) % 2 == 0;

        std::cout << ' ' << ans;
    }

    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
