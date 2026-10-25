#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> out(n);

    int no = 0;
    int ne = 1;
    for (int i = 1; i < (n + 1); ++i) {
        if (i & 1) {
            out[ne] = i;
            ne += 2;
        } else {
            out[no] = i;
            no += 2;
        }
    }
    for (auto i : out)
        std::cout << i << ' ';
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
