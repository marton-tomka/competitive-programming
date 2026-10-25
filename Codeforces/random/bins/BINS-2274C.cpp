#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    auto can = [&](int c) -> bool {
        ll sum{};
        for (int i = 1; i <= c && sum < n; ++i)
            sum += 1LL * i * (c / i);
        return sum >= n;
    };

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (can(mid))
            hi = mid;
        else
            lo = mid + 1;
    }

    std::cout << lo << '\n';

    int rem = n, bag = 1;
    for (int i = lo; i >= 1; --i) {
        int cnt = std::min(lo / i, rem / i);

        for (int j{}; j < cnt; ++j) {
            for (int k{}; k < i; ++k)
                std::cout << bag << ' ';
            ++bag;
        }

        rem -= cnt * i;
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
