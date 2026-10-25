#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (int& x : a)
        std::cin >> x;
    for (int& x : b)
        std::cin >> x;

    std::vector<int> st(n + 3, 0);
    for (int i{}; i < n; ++i) {
        ++st[a[i] + 1];
        if (b[i] != a[i])
            ++st[b[i] + 1];
    }
    for (int v = 1; v < n + 3; ++v)
        st[v] += st[v - 1];

    std::vector<int> pos(st[n + 2]);
    std::vector<int> fp = st;
    for (int i{}; i < n; ++i) {
        pos[fp[a[i]]++] = i;
        if (b[i] != a[i])
            pos[fp[b[i]]++] = i;
    }

    std::vector<int> e(n, n);

    auto res = [&](int i, int v) -> int {
        if (v > n)
            return n;
        auto beg = pos.begin() + st[v], end = pos.begin() + st[v + 1];
        auto it = std::lower_bound(beg, end, i);
        if (it == end)
            return n;
        int d = *it;
        return a[d] == v && b[d] == v ? e[d] : d;
    };

    for (int d = n - 1; d >= 0; --d)
        if (a[d] == b[d])
            e[d] = res(d + 1, a[d] + 1);

    ll ans{};
    for (int l{}; l < n; ++l)
        ans += res(l, 1) - l;
    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
