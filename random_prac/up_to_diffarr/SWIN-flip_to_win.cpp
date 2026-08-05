#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int i{}; i < n; ++i) {
        std::cin >> arr[i];
    }

    int zeros = 0;
    int best = 0;
    for (int left{}, right{}; right < n; ++right) {
        if (arr[right] == 0) {
            zeros++;
        }
        while (zeros > k) {
            if (arr[left++] == 0) {
                zeros--;
            }
        }
        std::max(best, right - left + 1);
    }

    std::cout << best << "\n";
}

// 1 0 1 1 0 1
