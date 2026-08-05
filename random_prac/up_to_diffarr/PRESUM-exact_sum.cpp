#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll S;
    std::cin >> n >> S;

    std::map<ll, ll> seen_count;
    seen_count[0] = 1;

    ll current_sum = 0;
    ll matching = 0;
    for (int i{}; i < n; ++i) {
        int value;
        std::cin >> value;
        current_sum += value;
        // a subarray ending here sums to S iff some earlier prefix equals this
        ll needed = current_sum - S;
        auto found = seen_count.find(needed);
        if (found != seen_count.end())
            matching += found->second;
        seen_count[current_sum]++;
    }

    std::cout << matching << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
