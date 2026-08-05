#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n;
    int k;
    std::cin >> n >> k;
    std::vector<char> str(n);
    for (int i = 0; i < n; i++)
        std::cin >> str[i];

    std::array<ll, 26> count{};
    ll distinct = 0;
    int best = 0;
    for (int left = 0, right = 0; right < n; right++) {
        if (count[str[right] - 'a']++ == 0) {
            distinct++;
        };
        while (distinct > k) {
            if (--count[str[left++] - 'a'] == 0) {
                distinct--;
            }
        }
        best = std::max(best, right - left + 1);
    }
    std::println("{}", best);
}
