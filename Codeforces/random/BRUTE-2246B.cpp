#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> out(n);

    if (n == 1) {
        std::cout << "1\n";
        return;
    }
    if (n == 2) {
        std::cout << "-1\n";
        return;
    }

    out[0] = 1, out[1] = 2;
    ll s = 3;
    for (ll i = 2; i < n; ++i) {
        out[i] = s;
        s += out[i];
    }

    for (auto i : out)
        std::cout << i << ' ';
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
