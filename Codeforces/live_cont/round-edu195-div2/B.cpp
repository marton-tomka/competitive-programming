#include <bits/stdc++.h>
using ll = long long;

void solve() {
    std::string s;
    std::cin >> s;
    bool up{}, down{};

    for (size_t i = 1; i + 1 < s.size(); ++i) {
        if (s[i - 1] != s[i + 1])
            continue;

        if (s[i] == s[i - 1])
            up = true;
        else
            down = true;
    }

    std::cout << 1 + up + down << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
