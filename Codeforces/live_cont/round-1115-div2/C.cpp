#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<ll> v(n);
    for (int i{}; i < n; ++i) {
        std::cin >> v[i];
    }

    std::vector a(n, std::vector<ll>(m));
    for (int i{}; i < n; ++i) {
        for (int j{}; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    int ans = m;
    int sz = ans - 1;

    std::priority_queue<ll, std::vector<ll>, std::greater<ll>> topK;
    ll sum_topK = 0;

    for (int i = n - 1; i >= 0; --i) {
        if (sz == 0)
            break;

        for (int j{}; j < m; ++j) {
            topK.push(a[i][j]);
            sum_topK += a[i][j];

            while (topK.size() > sz) {
                sum_topK -= topK.top();
                topK.pop();
            }
        }

        if (sum_topK >= v[i]) {
            while (!topK.empty() && sum_topK - topK.top() >= v[i]) {
                sum_topK -= topK.top();
                topK.pop();
            }

            ans = std::min(ans, static_cast<int>(topK.size()));
            sz = ans - 1;

            while (topK.size() > sz) {
                sum_topK -= topK.top();
                topK.pop();
            }
        }
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
