#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, mod;
    std::cin >> n >> mod;

    std::vector<int> remainder_count(mod, 0);
    remainder_count[0] = 1;

    ll current_sum = 0;
    ll divisible_sub = 0;
    for (int i{}; i < n; ++i) {
        int value;
        std::cin >> value;
        current_sum += value;
        // % can be negative in C++, so push it back into [0, mod)
        int remainder = ((current_sum % mod) + mod) % mod;
        // every earlier prefix with this same remainder closes a divisible sub
        divisible_sub += remainder_count[remainder];
        remainder_count[remainder]++;
    }

    std::cout << divisible_sub << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
