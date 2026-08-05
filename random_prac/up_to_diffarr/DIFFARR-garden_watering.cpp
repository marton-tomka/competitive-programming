#include <bits/stdc++.h>
using ll = long long;

void solve() {
    ll n, m;
    std::cin >> n >> m;

    std::vector<ll> diff(n + 1, 0);
    for (int i{}; i < m; ++i) {
        int lefts, rights, values;
        std::cin >> lefts >> rights >> values;
        --lefts;
        --rights;
        diff[lefts] += values;
        diff[rights] -= values;
    }

    std::vector<ll> complete(n, 0);
    ll run = 0;
    for (int i{}; i < n; ++i) {
        run += diff[i];
        complete[i] = run;
    }

    for (auto x : complete) {
        std::cout << x << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // cin >> t;   // single-test problem: leave this out
    while (t--)
        solve();
}

// run with
// g++ -std=c++23 -O2 -o sol sol.cpp
// ./sol < in.txt
