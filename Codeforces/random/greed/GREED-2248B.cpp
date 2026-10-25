#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    std::vector<int> b(m);
    for (int i{}; i < n; ++i)
        std::cin >> a[i];
    for (int i{}; i < m; ++i)
        std::cin >> b[i];

    if (n < (2 * m)) {
        std::cout << "NO\n";
        return;
    }

    std::ranges::sort(a);
    std::ranges::sort(b);

    bool ok = true;
    for (int i{}; i < m; ++i) {
        if (!(a[i] <= b[i] && b[i] <= a[n - m + i])) {
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
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
