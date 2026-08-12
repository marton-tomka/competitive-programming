#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, c;
    std::cin >> n >> c;
    std::vector<int> a(n);
    std::vector<int> b(n);
    for (auto& i : a)
        std::cin >> i;
    for (auto& i : b)
        std::cin >> i;

    int cnt{};
    int ok{};
    for (int i{}; i < n; ++i) {
        if (a[i] < b[i]) {
            std::ranges::sort(a);
            std::ranges::sort(b);
            cnt = c;
            i = -1;
            ++ok;
        } else if (a[i] > b[i])
            cnt += (a[i] - b[i]);

        if (ok > 1) {
            std::cout << "-1\n";
            return;
        };
    }

    std::cout << cnt << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
