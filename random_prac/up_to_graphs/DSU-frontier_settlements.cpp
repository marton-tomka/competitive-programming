#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector adj(n, std::vector<int>{});

    struct DSU {
        std::vector<int> par, sz;
        int comps;

        DSU(int n)
            : par(n)
            , sz(n, 1)
            , comps(n) {
            std::iota(par.begin(), par.end(), 0);
        }

        int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

        bool same(int a, int b) { return find(a) == find(b); }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b)
                return false;
            if (sz[a] < sz[b])
                std::swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
            --comps;
            return true;
        }
    };

    DSU dsu(n);

    for (int i{}; i < m; ++i) {
        int t, u, v;
        std::cin >> t >> u >> v;
        --u;
        --v;
        if (t == 1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            dsu.unite(u, v);
        } else {
            std::cout << (dsu.same(u, v) ? "YES\n" : "NO\n");
        }
    }

    std::cout << dsu.comps << " " << std::ranges::max(dsu.sz);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // std::cin >> t;
    while (t--)
        solve();
}
