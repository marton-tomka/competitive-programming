#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    int odd{};
    for (int i{}; i < n; ++i) {
        int x;
        std::cin >> x;
        odd += x & 1;
    }

    bool larp = (n == 2 && odd == 1) || (n == 3 && odd == 3);
    std::cout << (larp ? "Larpity" : "Moggity") << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
