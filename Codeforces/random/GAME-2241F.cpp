#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    int zeros = std::ranges::count(s, '0');
    int one{};
    ll inv{};
    bool odd{};

    for (char c : s) {
        if (c == '1') {
            odd |= zeros & 1;
            ++one;
        } else {
            inv += one;
            odd |= one & 1;
            --zeros;
        }
    }

    std::cout << ((inv & 1) || odd ? "Alice\n" : "Bob\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--)
        solve();
}
