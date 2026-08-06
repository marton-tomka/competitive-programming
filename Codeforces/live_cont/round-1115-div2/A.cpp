#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    std::map<int, int> freq;
    ll total_sum = 0;

    for (int i{}; i < n; ++i) {
        int a;
        std::cin >> a;
        freq[a]++;
        total_sum += a;
    }

    int M = 0;
    int X = 0;
    for (auto const& [val, count] : freq) {
        if (count > M) {
            M = count;
            X = val;
        }
    }

    int S = n - M;

    if (M > S + 1) {
        ll wasted_count = M - S - 2;
        total_sum -= wasted_count * X;
    }

    std::cout << total_sum << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
