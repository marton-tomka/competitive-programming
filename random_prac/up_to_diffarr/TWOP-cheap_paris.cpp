#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int n;
    ll x;
    std::cin >> n >> x;
    std::vector<ll> arr(n);
    for (int i{}; i < n; ++i) {
        std::cin >> arr[i];
    }

    ll pairs = 0;
    int left = 0;
    int right = n - 1;
    while (left < right) {
        ll sum = arr[left] + arr[right];
        if (sum >= x) {
            right--;
        } else {
            pairs += (right - left);
            left++;
        }
    }

    std::cout << pairs << "\n";
}
