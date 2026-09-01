#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int q;
    std::cin >> q;
    std::multiset<int> lft, rgt;

    while (q--) {
        char op;
        int l, r;
        std::cin >> op >> l >> r;

        if (op == '+') {
            lft.insert(l);
            rgt.insert(r);
        } else {
            lft.erase(lft.find(l));
            rgt.erase(rgt.find(r));
        }

        std::cout << (!lft.empty() && *lft.rbegin() > *rgt.begin() ? "YES\n" : "NO\n");
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    while (t--)
        solve();
}
