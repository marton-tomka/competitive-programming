#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::string a;
    std::vector<std::string> b(m);
    std::string str;
    for (int i{}; i < n; ++i) {
        std::cin >> str;
        a += std::toupper(static_cast<unsigned char>(str[0]));
    }
    for (auto& i : b)
        std::cin >> i;

    bool ok = true;
    for (auto i : b) {
        for (auto j : i)
            if (!a.contains(j))
                ok = false;
    }

    std::cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
