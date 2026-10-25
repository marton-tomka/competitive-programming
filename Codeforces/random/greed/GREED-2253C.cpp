#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m, x, y;
    std::cin >> n >> m >> x >> y;

    int s = n + m;
    std::vector<uint8_t> src(s + 1);
    for (int i{}; i < x; ++i) {
        int v;
        std::cin >> v;
        src[v] |= 1;
    }
    for (int i{}; i < y; ++i) {
        int v;
        std::cin >> v;
        src[v] |= 2;
    }

    ll ans{};
    int ca{}, cb{}, u{};
    int mn = s + 1;

    for (int v = 1; v <= s; ++v) {
        if (!src[v])
            continue;

        ans += v;
        ++u;
        mn = std::min(mn, v);

        if (src[v] == 1)
            ++ca;
        else if (src[v] == 2)
            ++cb;
    }

    int ra = std::max(0, ca - n);
    int rb = std::max(0, cb - m);

    if (ra || rb) {
        for (int v = 1; v <= s && (ra || rb); ++v) {
            if (src[v] == 1 && ra) {
                ans -= v;
                --ra;
            } else if (src[v] == 2 && rb) {
                ans -= v;
                --rb;
            }
        }
    } else if (u == s) {
        ans -= mn;
    }

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
