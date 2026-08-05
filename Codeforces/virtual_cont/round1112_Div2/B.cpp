#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    int k;
    std::cin >> n >> k;

    if (n - k <= 1) {
        std::string ret = "-1";
        std::println("{}", ret);
        return;
    }

    int zeros = (n + 1) / 2;
    int ones = n / 2;
    int runs = n - k;
    int zruns = (runs + 1) / 2;
    int oruns = runs / 2;

    std::string s;
    s.reserve(n);
    for (int i{}; i < runs; ++i) {
        if (i % 2 == 0) {
            int len = (i == 0) ? zeros - zruns + 1 : 1;
            s.append(len, '0');
        } else {
            int len = (i == 1) ? ones - oruns + 1 : 1;
            s.append(len, '1');
        }
    }

    std::println("{}", s);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--)
        solve();
}
