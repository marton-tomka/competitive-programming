#include <bits/stdc++.h>
using ll = long long;

void solve() {
    int t;
    std::cin >> t;
    std::cin.ignore();

    std::vector<std::string> lines;
    lines.reserve(t);

    std::string buffer;
    for (int i{}; i < t && std::getline(std::cin, buffer); ++i) {
        lines.push_back(std::move(buffer));
    }

    for (int i{}; i < t; ++i) {
        int deleted = 0;

        // i am aware the inner loop couldve been just a normal loop not 2 pointers
        for (int left = 0, right = 1; right < lines[i].size(); ++left, ++right) {
            if (lines[i][left] == lines[i][right]) {
                ++deleted;
            }
        }

        std::println("{}", deleted);
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
