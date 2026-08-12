#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    int o{}, k{};
    int temp = n;

    for (int d = 2; d * d <= temp; ++d) {
        if (temp % d != 0)
            continue;
        ++k;
        while (temp % d == 0) {
            ++o;
            temp /= d;
        }
    }

    if (temp > 1) {
        ++k;
        ++o;
    }

    std::cout << o + k - 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
