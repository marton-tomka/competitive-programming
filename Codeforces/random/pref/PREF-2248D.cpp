#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::string s, t;
    std::cin >> s >> t;

    std::vector<int> pref_same(n + 1, 0);
    std::vector<int> pref_z_s(n + 1, 0);
    std::vector<int> pref_z_t(n + 1, 0);

    for (int i{}; i < n; ++i) {
        pref_same[i + 1] = pref_same[i] + (s[i] == t[i] ? 1 : 0);
        pref_z_s[i + 1] = pref_z_s[i] + (s[i] == '0' ? 1 : 0);
        pref_z_t[i + 1] = pref_z_t[i] + (t[i] == '0' ? 1 : 0);
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;

        int same = pref_same[r] - pref_same[l - 1];
        int zero_s = pref_z_s[r] - pref_z_s[l - 1];
        int zero_t = pref_z_t[r] - pref_z_t[l - 1];
        int diff = std::abs(zero_s - zero_t);

        if (same >= diff) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
