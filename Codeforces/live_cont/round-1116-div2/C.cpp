#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n, k;
    std::cin >> n >> k;
    std::string str;
    std::cin >> str;

    ll r{};
    ll b{};

    for (ll i{}; i < (2 * n); ++i) {
        if (str[i] == '1') {
            if (((i & 1) == 0 && str[(i + 1) % (2 * n)] == '0') ||
                ((i & 1) != 0 && str[(i + 1) % (2 * n)] == '1')) {
                r++;
            } else {
                b++;
            }
        }
    }

    std::cout << r << ' ' << b << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
