#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int x{};
    for (int& v : a) {
        std::cin >> v;
        x ^= v;
    }

    if (n == 1) {
        std::cout << 0 << '\n';
        return;
    }

    if (x == 0) {
        std::cout << 1 << '\n';
        return;
    }

    int ans{};
    for (int v : a)
        ans += (v ^ x) < v;

    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
