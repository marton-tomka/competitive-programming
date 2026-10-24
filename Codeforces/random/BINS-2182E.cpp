#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    ll k;
    std::cin >> n >> m >> k;
    std::vector<int> a(m);
    for (auto& x : a)
        std::cin >> x;
    std::ranges::sort(a);

    std::vector<std::pair<int, int>> fr(n);
    for (auto& [c, x] : fr) {
        int y, z;
        std::cin >> x >> y >> z;
        k -= y;
        c = z - y;
    }
    std::ranges::sort(fr, std::greater{});

    std::vector<int> nxt(m + 1);
    std::iota(nxt.begin(), nxt.end(), 0);
    auto find = [&](int u) {
        int r = u;
        while (nxt[r] != r)
            r = nxt[r];
        while (nxt[u] != r)
            u = std::exchange(nxt[u], r);
        return r;
    };

    int happy{};
    std::vector<int> rest;
    rest.reserve(n);
    for (auto [c, x] : fr) {
        int b = find(static_cast<int>(std::ranges::lower_bound(a, x) - a.begin()));
        if (b < m) {
            nxt[b] = b + 1;
            ++happy;
        } else {
            rest.push_back(c);
        }
    }

    for (int c : rest | std::views::reverse) {
        if (c > k)
            break;
        k -= c;
        ++happy;
    }
    std::cout << happy << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
