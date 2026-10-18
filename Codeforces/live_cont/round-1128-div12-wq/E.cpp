#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    std::vector<int> st;
    st.reserve(n / 2);

    int left{}, clos{}, best{};
    for (char c : s) {
        if (c == ')') {
            st.pop_back();
            left = std::min(left, static_cast<int>(st.size()));
            ++clos;
            continue;
        }

        st.push_back(clos);
        int dep = st.size();

        while (st[left] < clos - k)
            ++left;

        best = std::max(best, dep - left);

        if (clos <= k)
            best = std::max(best, std::min(n / 2, k + dep));
    }

    std::cout << best << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
