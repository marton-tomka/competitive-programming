#include <bits/stdc++.h>
using ll = long long;

void solve() {
    std::array<ll, 3> a;
    std::cin >> a[0] >> a[1] >> a[2];
    std::ranges::sort(a);
    std::cout << std::min(a[2] - a[0], a[0] + a[1] - a[0]) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
