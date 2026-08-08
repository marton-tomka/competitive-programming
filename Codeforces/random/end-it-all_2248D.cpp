// if ts works i will genuinely lose my shit

#include <bits/stdc++.h>
using ll = long long;

int mode(std::string_view str) {
    size_t ones = std::count(str.begin(), str.end(), '1');
    if (ones > (str.length() - ones)) {
        return 1;
    } else if (ones == (str.length() - ones)) {
        return 2;
    } else {
        return 0;
    }
}

bool equal(int x, int y) {
    if (x == y || x == 2 || y == 2)
        return true;
    else
        return false;
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::string s, t;
    std::cin >> s >> t;
    std::vector<std::pair<int, int>> qs;
    for (int i{}; i < q; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        qs.push_back({u, v});
    }

    for (auto i : qs) {
        std::vector<int> match(n, -1);
        std::string temp1;
        std::string temp2;
        for (int l = i.first, r = i.first; r <= i.second; ++r) {
            temp1 += s[r];
            temp2 += t[r];
            if (equal(mode(temp1), mode(temp2))) {
                match[r] += 1;
            }
            if (r == i.second)
                while (l <= r) {
                    if (equal(mode(temp1), mode(temp2))) {
                        int ahhh = (l == 0) ? r : (l - 1);
                        match[ahhh] += 1;
                    }
                    temp1.erase(0, 1);
                    temp2.erase(0, 1);
                    ++l;
                }
        }

        bool ok = false;
        for (auto y : match)
            if (y == 1) {
                ok = true;
                break;
            }
        std::cout << (ok ? "YES\n" : "NO\n");
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
