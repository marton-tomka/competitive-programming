#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector ch(n, std::vector<int>{});
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        --p;
        ch[p].push_back(i);
    }
    std::vector<int> a(n);
    for (int& x : a)
        std::cin >> x;

    std::vector<int> ord;
    ord.reserve(n);
    ord.push_back(0);

    for (int i{}; i < static_cast<int>(ord.size()); ++i) {
        int u = ord[i];
        for (int v : ch[u])
            ord.push_back(v);
    }

    std::vector<int> mn(n), mx(n), cnt(n);
    bool ok = true;

    for (int z = n - 1; z >= 0; --z) {
        int u = ord[z];

        if (ch[u].empty()) {
            mn[u] = mx[u] = a[u];
            cnt[u] = 1;
            continue;
        }

        mn[u] = n + 1;
        mx[u] = 0;

        for (int v : ch[u]) {
            mn[u] = std::min(mn[u], mn[v]);
            mx[u] = std::max(mx[u], mx[v]);
            cnt[u] += cnt[v];
        }

        if (mx[u] - mn[u] + 1 != cnt[u]) {
            ok = false;
            continue;
        }

        int m = ch[u].size();

        if (m > 1) {
            int bad{};
            for (int i{}; i < m; ++i) {
                int v = ch[u][i];
                int w = ch[u][(i + 1) % m];

                if (mn[v] > mn[w])
                    ++bad;
            }

            if (bad != 1)
                ok = false;
        }
    }

    std::cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
