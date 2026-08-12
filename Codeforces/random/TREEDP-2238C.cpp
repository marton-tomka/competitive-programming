#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    std::vector<int> d(n, 0);
    for (int i = 1; i < n; ++i) {
        std::cin >> p[i];
        --p[i];
        d[i] = d[p[i]] + 1;
    }

    std::vector<int> m1 = d;
    std::vector<int> m2 = d;
    std::vector<int> deg(n, 0);

    for (int i = n - 1; i >= 1; --i) {
        int pa = p[i];
        ++deg[pa];

        int cur = m1[i];
        if (cur > m1[pa]) {
            m2[pa] = m1[pa];
            m1[pa] = cur;
        } else if (cur > m2[pa]) {
            m2[pa] = cur;
        }
    }

    ll ans = n;
    for (int i{}; i < n; ++i) {
        if (deg[i] >= 2)
            ans += m2[i] - d[i];
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
