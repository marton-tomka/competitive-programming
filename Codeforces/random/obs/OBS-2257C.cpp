#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> par(n + 1); // we dont actually need this do we?
    for (int i = 2; i <= n; ++i)
        std::cin >> par[i];
    int m;
    std::cin >> m;
    std::vector<int> a(m);
    for (int& x : a)
        std::cin >> x;

    int skip = *std::ranges::min_element(a);

    std::cout << m - 1;
    for (int x : a)
        if (x != skip)
            std::cout << ' ' << x;
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
