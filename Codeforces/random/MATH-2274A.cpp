#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    ll p{};
    for (int i{}; i < n; ++i) {
        ll x;
        std::cin >> x;
        p += i & 1 ? -x : x;
    }

    std::cout << p << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
