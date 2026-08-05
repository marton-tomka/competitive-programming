#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    ll sum = 0;
    int best = 0;
    for (int left = 0, right = 0; right < n; right++) {
        sum += a[right];
        while (sum > k)
            sum -= a[left++];
        best = std::max(best, right - left + 1);
    }
    std::cout << best << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // cin >> t;   // single-test problem: leave this out
    while (t--)
        solve();
}

// in case of input (in.txt)
// 5 7
// 2 1 5 1 3

// run with
// g++ -std=c++23 -O2 -o sol sol.cpp
// ./sol < in.txt
