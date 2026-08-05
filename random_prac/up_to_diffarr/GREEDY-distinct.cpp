#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n;
    std::cin >> n;
    std::vector<int> str(n);
    for (int i = 0; i < n; i++)
        std::cin >> str[i];

    std::ranges::sort(str);

    ll incr = 0;
    for (int i = 1; i < n; ++i) {
        if (str[i] <= str[i - 1]) {
            int req = str[i - 1] + 1;
            incr += (req - str[i]);
            str[i] = req;
        }
    }
    std::println("{}", incr);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
