#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, acnt{}, bcnt{};
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> b(n);
    for (int i{}; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] == 1) {
            ++acnt;
        }
    }
    for (int i{}; i < n; ++i) {
        std::cin >> b[i];
        if (b[i] == 1) {
            ++bcnt;
        }
    }

    int d{};
    int cnt10{};
    for (int i{}; i < n; ++i) {
        if (a[i] != b[i]) {
            ++d;
            if (a[i] == 1) {
                ++cnt10;
            }
        }
    }

    if (d == 0) {
        std::cout << 0 << "\n";
    } else if (acnt == 0 || bcnt == n) {
        std::cout << -1 << "\n";
    } else if (cnt10 % 2 != 0) {
        std::cout << 1 << "\n";
    } else {
        std::cout << 2 << "\n";
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
