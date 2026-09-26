#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a)
        std::cin >> x;

    for (int len = n / 2; len >= 1; --len) {
        std::vector<int> fst(n + 2, -1), lst(n + 2, -1);
        std::vector<int> cnt(n + 1);

        std::deque<int> mn, mx;
        int dup{};

        for (int r{}; r < n; ++r) {
            int x = a[r];
            if (++cnt[x] == 2)
                ++dup;

            while (!mn.empty() && a[mn.back()] >= x)
                mn.pop_back();
            mn.push_back(r);

            while (!mx.empty() && a[mx.back()] <= x)
                mx.pop_back();
            mx.push_back(r);

            if (r >= len) {
                int rem = r - len;
                int y = a[rem];

                if (cnt[y]-- == 2)
                    --dup;

                if (mn.front() == rem)
                    mn.pop_front();

                if (mx.front() == rem)
                    mx.pop_front();
            }

            if (r < len - 1 || dup)
                continue;

            if (a[mx.front()] - a[mn.front()] != len - 1)
                continue;

            int l = r - len + 1;
            int v = a[mn.front()];
            if (fst[v] == -1)
                fst[v] = l;
            lst[v] = l;
        }

        for (int v = 1; v + 2 * len - 1 <= n; ++v) {
            if (fst[v] == -1 || fst[v + len] == -1)
                continue;

            if (fst[v] + len <= lst[v + len] || fst[v + len] + len <= lst[v]) {
                std::cout << len << '\n';
                return;
            }
        }
    }

    std::cout << 0 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
