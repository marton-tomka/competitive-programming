#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::multiset<ll> b;
    ll sum{};
    for (int i{}; i < n; ++i) {
        ll x;
        std::cin >> x;
        b.insert(x);
        sum += x;
    }

    if (sum <= 0) {
        std::cout << "-1\n";
        return;
    }

    std::vector<ll> a;
    a.reserve(n);
    ll s{};

    while (!b.empty()) {
        auto it = b.lower_bound(1 - s);

        ll x = *it;
        b.erase(it);

        s += x;
        a.push_back(s);
    }

    for (int i{}; i < n; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
