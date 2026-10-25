#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector adj(n, std::vector<int>{});
    for (int i{}; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> par(n, -1), col(n);
    std::vector<int> ord;
    ord.reserve(n);

    std::queue<int> q;
    int root = n - 1;
    par[root] = root;
    q.push(root);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : adj[u]) {
            if (par[v] != -1)
                continue;
            par[v] = u;
            col[v] = col[u] ^ 1;
            q.push(v);
        }
    }

    std::vector<int> ops;
    ops.reserve(3 * n);
    int cur = col[0];
    bool fst = true;

    for (int i = n - 1; i >= 0; --i) {
        int u = ord[i];
        if (u == root)
            continue;

        if (!fst) {
            ops.push_back(0);
            cur ^= 1;
        }

        if (cur == col[u]) {
            ops.push_back(0);
            cur ^= 1;
        }

        ops.push_back(u + 1);
        fst = false;
    }

    std::cout << ops.size() << '\n';

    for (int op : ops) {
        if (op == 0)
            std::cout << "1\n";
        else
            std::cout << "2 " << op << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
