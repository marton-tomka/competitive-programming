#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m, h;
    std::cin >> n >> m >> h;
    std::vector<uint8_t> hrs(n, 0);
    for (int i{}; i < h; ++i) {
        int x;
        std::cin >> x;
        hrs[x - 1] = 1;
    }

    std::vector adj(n, std::vector<std::pair<int, int>>{});
    for (int i{}; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u;
        --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    constexpr ll INF = std::numeric_limits<ll>::max() / 4;

    auto dijk = [&](int s) -> std::vector<ll> {
        std::vector<ll> d(2 * n, INF);
        std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<>> pq;
        d[2 * s] = 0;
        pq.push({0, 2 * s});

        while (!pq.empty()) {
            auto [du, st] = pq.top();
            pq.pop();
            if (du != d[st])
                continue;

            int u = st >> 1, f = st & 1;
            if (!f && hrs[u] && du < d[st | 1]) {
                d[st | 1] = du;
                pq.push({du, st | 1});
            }
            for (auto [v, w] : adj[u]) {
                ll nd = du + (f ? w / 2 : w);
                int ns = 2 * v + f;
                if (nd < d[ns]) {
                    d[ns] = nd;
                    pq.push({nd, ns});
                }
            }
        }

        std::vector<ll> r(n);
        for (int i{}; i < n; ++i)
            r[i] = std::min(d[2 * i], d[2 * i + 1]);
        return r;
    };

    auto da = dijk(0);
    auto db = dijk(n - 1);

    ll best = INF;
    for (int i{}; i < n; ++i)
        best = std::min(best, std::max(da[i], db[i]));

    std::cout << (best == INF ? -1 : best) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
