#include <bits/stdc++.h>
using ll = long long;

constexpr int MX = 1'000'000;
std::array<int, MX + 1> mark{};
int tag{};

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> a(n);

    for (int i{}; i < n; ++i) {
        int l;
        std::cin >> l;

        std::vector<int> v(l);
        for (int& x : v)
            std::cin >> x;

        int id = ++tag;

        for (int j = l - 1; j >= 0; --j) {
            int x = v[j];
            if (mark[x] == id)
                continue;

            mark[x] = id;
            a[i].push_back(x);
        }
    }

    int got = ++tag;

    std::vector<uint8_t> used(n);
    std::vector<int> ans;

    for (int step{}; step < n; ++step) {
        int best = -1;

        for (int i{}; i < n; ++i) {
            if (used[i])
                continue;

            std::erase_if(a[i], [&](int x) { return mark[x] == got; });

            if (best == -1 || a[i] < a[best])
                best = i;
        }

        used[best] = 1;

        for (int x : a[best]) {
            mark[x] = got;
            ans.push_back(x);
        }
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
