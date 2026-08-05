#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    auto adv = std::views::iota(0, n) | std::ranges::to<std::vector<int>>();
    std::vector adj(n, std::vector<int>{});
    std::vector<int> col(n, -1);
    bool ok = true;

    for (int i{}; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i{}; i < n; ++i) {
        if (ok == false)
            break;
        if (col[i] != -1)
            continue;

        std::queue<int> q;

        col[i] = 0;
        q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (col[v] == -1 && ok) {
                    col[v] = col[u] ^ 1;
                    q.push(v);
                } else if (col[v] == col[u]) {
                    ok = false;
                    break;
                }
            }
        }
    }

    std::cout << (ok ? "YES\n" : "NO\n");
    if (ok)
        for (auto i : col)
            std::cout << ++i << " ";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
