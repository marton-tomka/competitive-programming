#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector grid(n, std::vector<char>(m));
    for (auto& i : grid)
        for (auto& j : i)
            std::cin >> j;

    constexpr std::array<int, 4> dr{1, -1, 0, 0};
    constexpr std::array<int, 4> dc{0, 0, 1, -1};

    std::vector vis(n, std::vector<uint8_t>(m, 0));
    bool cycle = false;

    auto dfs = [&](this auto&& self, int r, int c, int parr, int parc) -> void {
        vis[r][c] = 1;
        for (int k{}; k < 4 && !cycle; ++k) {
            int nr = r + dr[k], nc = c + dc[k];

            if (nr == parr && nc == parc)
                continue;

            if (nr < 0 || nr >= n || nc < 0 || nc >= m || grid[nr][nc] != grid[r][c])
                continue;

            if (vis[nr][nc]) {
                cycle = true;
                return;
            }
            self(nr, nc, r, c);
        }
    };

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            if (!vis[r][c])
                dfs(r, c, -1, -1);

    std::cout << (cycle ? "Yes\n" : "No\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while (t--)
        solve();
}
