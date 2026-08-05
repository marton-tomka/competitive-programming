#include <bits/stdc++.h>
#include <climits>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a)
        std::cin >> x;

    if (n % 2 != 0) {
        std::println("NO");
        return;
    }

    int min_odd = INT_MAX, max_even = INT_MIN;
    for (int i{}; i < n; ++i) {
        if ((i + 1) % 2 == 1)
            min_odd = std::min(min_odd, a[i]);
        else
            max_even = std::max(max_even, a[i]);
    }

    std::println("{}", min_odd - max_even >= 2 ? "YES" : "NO");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--)
        solve();
}
