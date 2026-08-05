#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> l(n), r(n), u(n), v(n);
    for (int i = 0; i < n; ++i)
        std::cin >> l[i] >> r[i] >> u[i] >> v[i];

    if (n <= 1) {
        std::println("{}", 0);
        return;
    }

    int best = 0;
    for (int m = n; m >= 1; --m) {
        int ptr = 0;
        bool ok = true;
        for (int j = 1; j <= m; ++j) {
            int lr = j;
            int rr = m - j + 1;
            while (ptr < n && ((l[ptr] <= lr && lr <= r[ptr]) || (u[ptr] <= rr && rr <= v[ptr]))) {
                ++ptr;
            }
            if (ptr == n) {
                ok = false;
                break;
            }
            ++ptr;
        }
        if (ok) {
            best = m;
            break;
        }
    }

    std::println("{}", best);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--)
        solve();
}
