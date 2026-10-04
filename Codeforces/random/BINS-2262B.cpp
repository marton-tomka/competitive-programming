#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<ll> a(n);
    for (ll& x : a)
        std::cin >> x;
    std::vector<int> p(n);
    for (int& x : p) {
        std::cin >> x;
        --x;
    }

    std::vector<ll> bit(n + 1);

    auto add = [&](int i, ll x) -> void {
        for (++i; i <= n; i += i & -i)
            bit[i] += x;
    };

    auto pref = [&](int i) -> ll {
        ll sum{};
        for (; i; i -= i & -i)
            sum += bit[i];
        return sum;
    };

    auto sum = [&](int l, int r) -> ll { return pref(r) - pref(l); };

    std::set<int> st;
    std::vector<int> ans(n);
    int blocks{};

    for (int j = n - 1; j >= 0; --j) {
        int i = p[j];
        add(i, a[i]);

        int start = i;
        auto it = st.lower_bound(i);

        if (it == st.begin()) {
            st.insert(i);
            ++blocks;
        } else {
            int b = *std::prev(it);

            if (sum(b, i) < a[i]) {
                st.insert(i);
                ++blocks;
            } else {
                start = b;
            }
        }

        it = st.upper_bound(start);

        while (it != st.end()) {
            int nxt = *it;

            if (sum(start, nxt) < a[nxt])
                break;

            it = st.erase(it);
            --blocks;
        }

        ans[j] = blocks - 1;
    }

    for (int x : ans)
        std::cout << x << ' ';
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
