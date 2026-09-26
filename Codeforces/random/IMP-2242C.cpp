#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> c;
    int prv = -1, cur{};

    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;

        if (x != prv) {
            if (cur)
                c.push_back(cur);
            prv = x;
            cur = 1;
        } else {
            ++cur;
        }
    }
    c.push_back(cur);

    std::ranges::sort(c);

    int m = c.size();
    std::vector<ll> suf(m + 1);
    for (int i = m - 1; i >= 0; --i)
        suf[i] = suf[i + 1] + c[i];

    int ans{};
    for (int i{}; i < m;) {
        int p = c[i];
        ll cnt = m - i;
        ll mn = suf[i] - cnt * (p - 1);

        if (k >= mn && (k - mn) % cnt == 0)
            ++ans;

        while (i < m && c[i] == p)
            ++i;
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
