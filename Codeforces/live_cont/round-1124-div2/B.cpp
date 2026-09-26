#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    std::array<ll, 730> cnt{};
    ll ans{};

    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;

        for (int j{}; j < 730; ++j) {
            int s{};
            while (x) {
                int d = x % 10;
                s += d * d;
                x /= 10;
            }
            x = s;
        }
        ans += cnt[x]++;
    }

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
