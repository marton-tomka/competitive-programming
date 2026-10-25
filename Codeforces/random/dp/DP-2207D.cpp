#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k, v;
    std::cin >> n >> k >> v;
    --v;
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a;
        --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    std::vector<int> par(n, -1), ord;
    ord.reserve(n);
    par[v] = v;
    ord.push_back(v);

    for (int i{}; i < n; ++i) {
        int u = ord[i];

        for (int w : adj[u]) {
            if (w == par[u])
                continue;
            par[w] = u;
            ord.push_back(w);
        }
    }

    constexpr int INF = 1'000'000'000;
    std::vector<int> dp(n);

    for (int i = n - 1; i >= 0; --i) {
        int u = ord[i];
        int a = INF, b = INF;

        for (int w : adj[u]) {
            if (par[w] != u)
                continue;

            int d = dp[w];

            if (d < a) {
                b = a;
                a = d;
            } else if (d < b) {
                b = d;
            }
        }

        if (a == INF)
            dp[u] = 0;
        else if (b != INF && a + b < k)
            dp[u] = 0;
        else
            dp[u] = a + 1;
    }

    std::cout << (dp[v] == 0 ? "YES\n" : "NO\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
