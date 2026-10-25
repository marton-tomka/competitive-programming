#include <bits/stdc++.h>
using ll = long long;

void solve() {
    std::string s;
    std::cin >> s;

    std::vector<char> c(2);
    std::string out;
    for (auto i : s) {
        if (c[i - '0'] == 0) {
            c[i - '0'] = 1;
            continue;
        }
        out += i;
    }

    std::cout << out << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
