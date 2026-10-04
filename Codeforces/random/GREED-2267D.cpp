#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> pos(n + 1);
    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;
        pos[x] = i;
    }

    bool ok = true;

    for (int x = n; x > 1; x -= 2) {
        if ((pos[x] & 1) == (pos[x - 1] & 1)) {
            ok = false;
            break;
        }
    }

    std::cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
