#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::string> a(n);
    for (auto& s : a)
        std::cin >> s;

    std::vector<std::pair<int, int>> e;

    for (int u{}; u < n; ++u) {
        for (int v{}; v < n; ++v) {
            if (u == v || a[u][v] == '0')
                continue;

            bool mid{};
            for (int k{}; k < n; ++k) {
                if (k != u && k != v && a[u][k] == '1' && a[k][v] == '1') {
                    mid = true;
                    break;
                }
            }

            if (!mid)
                e.push_back({u, v});
        }
    }

    if (e.size() != n - 1) {
        std::cout << "No\n";
        return;
    }

    std::vector adj(n, std::vector<int>{});
    std::vector dir(n, std::vector<int>{});
    for (auto [u, v] : e) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        dir[u].push_back(v);
    }

    std::vector<int> vis(n);
    std::vector<int> st{0};
    vis[0] = 1;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (int v : adj[u]) {
            if (vis[v])
                continue;
            vis[v] = 1;
            st.push_back(v);
        }
    }

    if (std::ranges::find(vis, 0) != vis.end()) {
        std::cout << "No\n";
        return;
    }

    for (int s{}; s < n; ++s) {
        std::ranges::fill(vis, 0);
        st = {s};
        vis[s] = 1;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            for (int v : dir[u]) {
                if (vis[v])
                    continue;
                vis[v] = 1;
                st.push_back(v);
            }
        }

        for (int v{}; v < n; ++v) {
            if (vis[v] != a[s][v] - '0') {
                std::cout << "No\n";
                return;
            }
        }
    }

    std::cout << "Yes\n";
    for (auto [u, v] : e)
        std::cout << u + 1 << ' ' << v + 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
