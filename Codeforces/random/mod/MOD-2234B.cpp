#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n;
    std::cin >> n;

    if (n == 10) {
        std::cout << -1 << '\n';
        return;
    }

    ll a = n % 12;
    if (a == 10)
        a = 22;

    std::cout << a << ' ' << n - a << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
