#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (n < 3) {
        for (int i{}; i < n; ++i) {
            std::cout << a[i] << " ";
        }
        std::cout << '\n';
        return;
    }

    std::vector<ll> diff(n - 1);
    for (int i{}; i < n - 1; ++i) {
        diff[i] = a[i + 1] - a[i];
    }

    int i = 0;
    while (i < n - 1) {
        int j = i;
        while (j < n - 1 && std::abs(diff[j]) % 2 == std::abs(diff[i]) % 2) {
            j++;
        }

        std::sort(diff.begin() + i, diff.begin() + j);
        i = j;
    }

    std::cout << a[0];
    ll current_val = a[0];
    for (int k = 0; k < n - 1; ++k) {
        current_val += diff[k];
        std::cout << " " << current_val;
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
    return 0;
}
