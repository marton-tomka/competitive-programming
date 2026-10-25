#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int b = 1;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[i - 1])
            ++b;
    }

    if (b == 2)
        std::cout << 2 << '\n';
    else
        std::cout << 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
