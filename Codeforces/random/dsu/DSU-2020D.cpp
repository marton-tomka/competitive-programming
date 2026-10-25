#include <bits/stdc++.h>
using ll = long long;

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

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::array<std::vector<int>, 11> best;
    for (int d = 1; d <= 10; ++d)
        best[d].assign(n, -1);

    for (int i{}; i < m; ++i) {
        int a, d, k;
        std::cin >> a >> d >> k;
        --a;

        best[d][a] = std::max(best[d][a], a + k * d);
    }

    DSU dsu(n);

    for (int d = 1; d <= 10; ++d) {
        std::vector<int> far(d, -1);

        for (int i{}; i < n; ++i) {
            int r = i % d;
            far[r] = std::max(far[r], best[d][i]);

            if (i + d < n && far[r] >= i + d)
                dsu.unite(i, i + d);
        }
    }

    std::cout << dsu.comps << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
