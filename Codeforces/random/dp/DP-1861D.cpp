#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& x : a)
        std::cin >> x;

    std::vector<int> suf(n + 1, 0);
    for (int i = n - 2; i >= 0; --i)
        suf[i] = suf[i + 1] + (a[i] >= a[i + 1]);

    int best = suf[0];
    int neg{};
    for (int k = 1; k <= n; ++k) {
        if (k >= 2 && a[k - 2] <= a[k - 1])
            ++neg;
        best = std::min(best, neg + 1 + suf[k]);
    }
    std::cout << best << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
