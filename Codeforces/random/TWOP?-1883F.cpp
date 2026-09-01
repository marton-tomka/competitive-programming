#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a)
        std::cin >> x;

    std::vector<bool> fst(n), lst(n);
    std::unordered_set<int> seen;
    seen.reserve(n * 2);

    for (int i{}; i < n; ++i)
        fst[i] = seen.insert(a[i]).second;

    seen.clear();

    for (int i = n - 1; i >= 0; --i)
        lst[i] = seen.insert(a[i]).second;

    ll ans{};
    int l{};

    for (int r{}; r < n; ++r) {
        l += fst[r];
        if (lst[r])
            ans += l;
    }

    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
