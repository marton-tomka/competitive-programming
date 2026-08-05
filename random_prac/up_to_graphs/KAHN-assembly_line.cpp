#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::priority_queue<int, std::vector<int>, std::greater<>> q{};
    std::vector adj(n, std::vector<int>{});
    std::vector<int> in_degree(n, 0);
    std::vector<int> order;
    order.reserve(n);

    for (int i{}; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
    }

    for (int u{}; u < n; ++u)
        for (int v : adj[u])
            ++in_degree[v];

    for (int i{}; i < n; ++i)
        if (in_degree[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.top();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    std::string out;
    for (auto i : order) {
        out += (std::to_string(++i) + " ");
    }
    std::cout << (order.size() == static_cast<size_t>(n) ? out += "\n" : "IMPOSSIBLE\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
