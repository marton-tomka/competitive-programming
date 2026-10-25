#include <bits/stdc++.h>
using ll = long long;

struct DSU {
    std::vector<int> par, sz;

    DSU(int n)
        : par(n)
        , sz(n, 1) {
        std::iota(par.begin(), par.end(), 0);
    }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (sz[a] < sz[b])
            std::swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> a(n);
    for (auto& s : a)
        std::cin >> s;

    DSU dsu(n + m);

    for (int i{}; i < n; ++i)
        for (int j{}; j < m; ++j)
            if (a[i][j] == '=')
                dsu.unite(i, n + j);

    std::vector adj(n + m, std::vector<int>{});

    for (int i{}; i < n; ++i) {
        for (int j{}; j < m; ++j) {
            if (a[i][j] == '=')
                continue;

            int x = dsu.find(i);
            int y = dsu.find(n + j);

            if (x == y) {
                std::cout << "No\n";
                return;
            }

            if (a[i][j] == '>')
                adj[x].push_back(y);
            else
                adj[y].push_back(x);
        }
    }

    std::vector<int> col(n + m), dp(n + m);

    auto dfs = [&](this auto&& self, int u) -> bool {
        if (col[u] == 1)
            return false;
        if (col[u] == 2)
            return true;

        col[u] = 1;
        dp[u] = 1;

        for (int v : adj[u]) {
            if (!self(v))
                return false;
            dp[u] = std::max(dp[u], dp[v] + 1);
        }

        col[u] = 2;
        return true;
    };

    for (int i{}; i < n + m; ++i) {
        if (dsu.find(i) == i && !dfs(i)) {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";

    for (int i{}; i < n; ++i)
        std::cout << dp[dsu.find(i)] << " \n"[i + 1 == n];

    for (int j{}; j < m; ++j)
        std::cout << dp[dsu.find(n + j)] << " \n"[j + 1 == m];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while (t--)
        solve();
}
