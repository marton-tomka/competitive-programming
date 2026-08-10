#include <bits/stdc++.h>
using ll = long long;

constexpr int MOD = 998'244'353;

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    auto calc = [&](int p) -> int {
        int val = -1;
        for (int i = p; i < n; i += 2) {
            if (s[i] != '?') {
                int k = i / 2;
                int req = ((s[i] - '0') - k) % 2;
                if (req < 0)
                    req += 2;
                if (val != -1 && val != req) {
                    return 0;
                }
                val = req;
            }
        }
        return (val == -1) ? 2 : 1;
    };

    ll ans = (1LL * calc(0) * calc(1)) % MOD;
    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t; // comment out if single test
    while (t--)
        solve();
}
