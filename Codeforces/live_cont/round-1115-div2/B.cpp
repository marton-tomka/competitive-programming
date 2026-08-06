#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int cnt0 = 0, cnt1 = 0;
    for (char c : s) {
        if (c == '0')
            cnt0++;
        else
            cnt1++;
    }

    int delta = cnt0 - cnt1;
    if (std::abs(delta) > 2) {
        std::cout << -1 << '\n';
        return;
    }

    int k = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i - 1]) {
            k++;
        }
    }

    int tc = 0;
    if (k % 2 != 0) {
        tc = (s[0] == '0') ? 1 : -1;
    }

    int d = 1e9;
    for (int v = -1; v <= 1; ++v) {
        if (std::abs(delta - v) <= 1) {
            d = std::min(d, std::abs(tc - v));
        }
    }

    std::cout << n - k + d << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
