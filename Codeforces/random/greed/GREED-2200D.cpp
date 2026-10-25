#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;
    std::vector<int> p(n);
    for (int& i : p) {
        std::cin >> i;
    }

    std::vector<int> b(p.begin() + x, p.begin() + y);
    p.erase(p.begin() + x, p.begin() + y);

    auto min = std::ranges::min_element(b);
    std::ranges::rotate(b, min);

    auto pos = std::ranges::find_if(p, [&](int val) { return val > b[0]; });
    p.insert(pos, b.begin(), b.end());

    for (int i : p)
        std::cout << i << ' ';
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
