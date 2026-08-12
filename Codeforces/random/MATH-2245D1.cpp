#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int8_t> M(n * n);
    for (int k{}; k < m; ++k) {
        int o, i, j;
        std::cin >> o >> i >> j;
        --i;
        --j;
        int8_t val = (o == 1) ? 1 : 0;
        M[i * n + j] = val;
        M[j * n + i] = val;
    }

    std::vector<int> c(n, 0);
    for (int i{}; i < n; ++i) {
        for (int j{}; j < n; ++j) {
            c[i] += M[i * n + j];
        }
    }

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::ranges::sort(p, [&](int a, int b) { return c[a] < c[b]; });

    std::vector<ll> v(n);
    for (int k{}; k < n; ++k) {
        v[p[k]] = 2LL * (k + 1 + c[p[k]]) - 2LL * n - 1;
    }

    bool ok = true;
    for (int i{}; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            bool expected = M[i * n + j];
            bool actual = (v[i] + v[j] >= 0);
            if (expected != actual) {
                ok = false;
                break;
            }
        }
        if (!ok)
            break;
    }

    if (ok) {
        std::cout << "YES\n";
        for (int i{}; i < n; ++i) {
            std::cout << v[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << '\n';
    } else
        std::cout << "NO\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
