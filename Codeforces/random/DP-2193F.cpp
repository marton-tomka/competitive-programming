#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll ax, ay, bx, by;
    std::cin >> n >> ax >> ay >> bx >> by;
    std::vector<ll> x(n), y(n);
    for (ll& i : x)
        std::cin >> i;
    for (ll& i : y)
        std::cin >> i;

    std::vector<std::pair<ll, ll>> p(n);
    for (int i{}; i < n; ++i)
        p[i] = {x[i], y[i]};

    std::ranges::sort(p);

    ll dl{}, dh{};
    ll pl = ay, ph = ay;

    for (int i{}; i < n;) {
        int j = i;
        ll lo = p[i].second;
        ll hi = p[i].second;

        while (j < n && p[j].first == p[i].first) {
            lo = std::min(lo, p[j].second);
            hi = std::max(hi, p[j].second);
            ++j;
        }

        ll d = hi - lo;

        ll nl = std::min(dl + std::abs(pl - hi), dh + std::abs(ph - hi)) + d;

        ll nh = std::min(dl + std::abs(pl - lo), dh + std::abs(ph - lo)) + d;

        dl = nl;
        dh = nh;
        pl = lo;
        ph = hi;

        i = j;
    }

    ll v = std::min(dl + std::abs(pl - by), dh + std::abs(ph - by));

    std::cout << bx - ax + v << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
