#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    s = ' ' + s;
    std::vector<ll> a(n + 1), c(n + 1), b(n + 1), p(n + 1);
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];

    for (int i = 2; i <= n; ++i) {
        if (c[i] < c[i - 1]) {
            std::cout << "No\n";
            return;
        }
    }

    bool ok = true;
    for (int l{}; l <= n && ok;) {
        int r = l;
        while (r < n && s[r + 1] == '1')
            ++r;

        p[l] = 0;
        for (int i = l + 1; i <= r; ++i)
            p[i] = p[i - 1] + a[i];

        ll sh{};
        bool fix = l == 0;

        for (int i = std::max(1, l); i <= r; ++i) {
            if (i != 1 && c[i] == c[i - 1])
                continue;

            ll cur = c[i] - p[i];

            if (!fix) {
                sh = cur;
                fix = true;
            } else if (sh != cur) {
                ok = false;
                break;
            }
        }

        if (!ok)
            break;

        if (!fix) {
            sh = c[l] - p[l];

            for (int i = l + 1; i <= r; ++i)
                sh = std::min(sh, c[i] - p[i]);
        }

        for (int i = std::max(1, l); i <= r; ++i) {
            b[i] = sh + p[i];

            if (b[i] > c[i]) {
                ok = false;
                break;
            }
        }

        if (!ok)
            break;

        if (l > 0)
            a[l] = b[l] - b[l - 1];

        l = r + 1;
    }

    if (!ok) {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";

    for (int i = 1; i <= n; ++i) {
        if (i > 1)
            std::cout << ' ';
        std::cout << a[i];
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
