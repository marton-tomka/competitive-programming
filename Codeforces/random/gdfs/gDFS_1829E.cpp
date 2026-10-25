#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int R, C;
    std::cin >> R >> C;
    std::vector grid(R, std::vector<int>(C, 0));
    for (int i{}; i < R; i++) {
        for (int j{}; j < C; j++) {
            std::cin >> grid[i][j];
        }
    }

    std::vector vis(R, std::vector<uint8_t>(C, 0));

    constexpr std::array<int, 4> dr{1, -1, 0, 0};
    constexpr std::array<int, 4> dc{0, 0, 1, -1};

    int best = 0;
    int cur = 0;
    auto dfs = [&](this auto&& self, int r, int c) -> void {
        vis[r][c] = 1;
        cur += grid[r][c];
        for (int k{}; k < 4; ++k) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;
            if (grid[nr][nc] == 0 || vis[nr][nc])
                continue;
            self(nr, nc);
        }
    };

    for (int i{}; i < R; ++i) {
        for (int j{}; j < C; ++j) {
            if (vis[i][j] == 0 && grid[i][j] != 0) {
                cur = 0;
                dfs(i, j);
                best = std::max(best, cur);
            }
        }
    }

    std::cout << best << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
