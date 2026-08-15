// https://www.youtube.com/watch?v=yo5CILhgvT4

#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 676767677;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& i : a)
        std::cin >> i;

    int cnt{};
    for (int i{}; i < n; ++i) {
        if (a[i] == 1)
            continue;

        cnt = (cnt + a[i]) % MOD;
    }

    if (a[n - 1] == 1)
        ++cnt;

    std::cout << cnt << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
