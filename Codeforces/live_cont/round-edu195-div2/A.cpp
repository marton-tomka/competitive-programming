#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int a, b;
    std::cin >> a >> b;

    std::cout << (a > b ? std::min(b, a - b) : -1) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
