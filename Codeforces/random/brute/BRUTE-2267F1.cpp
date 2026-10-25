#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int& x : a)
        std::cin >> x;

    std::ranges::sort(a);

    std::vector<int> ans;
    ans.push_back(a.back() - a.front());

    while (a.back()) {
        std::vector<int> v;
        v.reserve(n * (n - 1) / 2);

        for (int i{}; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                v.push_back(a[i] ^ a[j]);

        std::nth_element(v.begin(), v.begin() + n, v.end());
        v.resize(n);
        std::ranges::sort(v);
        a = std::move(v);

        ans.push_back(a.back() - a.front());
    }

    int lim = ans.size() - 1;

    while (q--) {
        int x;
        std::cin >> x;
        std::cout << ans[std::min(x, lim)] << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
