#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    if (s[0] == '1') {
        std::cout << std::ranges::count(s, '0') << '\n';
        return;
    }

    int z = std::ranges::count(s, '0');
    int one{};
    int ans = n;

    for (char c : s) {
        if (c == '0')
            --z;
        else
            ++one;

        ans = std::min(ans, one + z);
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
