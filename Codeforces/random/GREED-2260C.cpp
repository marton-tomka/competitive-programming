#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int x, y;
    std::cin >> x >> y;

    int sum = x + y;
    int ops = x;

    for (int b = 1 << 30; b; b >>= 1)
        if ((sum & b) && ops >= b)
            ops -= b;

    std::cout << sum << ' ' << ops << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
