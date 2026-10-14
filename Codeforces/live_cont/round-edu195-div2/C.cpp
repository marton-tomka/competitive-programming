#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        pref[i] = (pref[i - 1] + a) % k;
    }

    std::vector<int> cnt(k);
    ll ans{};
    for (int r = k + 1; r <= n; ++r) {
        ++cnt[pref[r - k - 1]];
        ans += cnt[pref[r]];
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
