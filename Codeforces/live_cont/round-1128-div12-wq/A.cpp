#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int cnt = std::ranges::count(s, '1');
    if (cnt <= 2) {
        std::cout << (cnt == 2) << '\n';
        return;
    }

    int last = s.rfind('1');
    int first = s.find('1');
    std::cout << last - first << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
