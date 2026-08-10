#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i{}; i < n; ++i) {
        std::cin >> a[i];
    }

    if (n & 1) {
        std::cout << "NO\n";
        return;
    }

    int cnt{};
    for (auto i : a) {
        if (i == 1)
            ++cnt;
    }

    if (cnt % 2 == (n / 2) % 2) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
