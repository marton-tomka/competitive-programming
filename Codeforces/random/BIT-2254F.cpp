#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    int xa{}, xb{};
    std::vector<int> a(n), b(n);
    for (int& x : a) {
        std::cin >> x;
        xa ^= x;
    }
    for (int& x : b) {
        std::cin >> x;
        xb ^= x;
    }

    std::vector<int> ca(n + 1), cb(n + 1);
    ca[0] = xa;
    cb[0] = xb;

    for (int i{}; i < n; ++i) {
        ca[i + 1] = xa ^ a[i];
        cb[i + 1] = xb ^ b[i];
    }

    std::ranges::sort(ca);
    std::ranges::sort(cb);

    std::cout << (ca == cb ? "YES\n" : "NO\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
