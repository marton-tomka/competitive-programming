#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& i : a)
        std::cin >> i;

    std::ranges::sort(a, std::greater{});

    if (n == 2) {
        std::cout << a[0] << ' ' << a[1] << '\n';
        return;
    }

    for (int i = 2; i < n; ++i)
        if (a[i - 2] % a[i - 1] != a[i]) {
            std::cout << "-1\n";
            return;
        }

    std::cout << a[0] << ' ' << a[1] << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
