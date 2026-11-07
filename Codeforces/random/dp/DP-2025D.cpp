// new template as of oct 28 ^^
#include <bits/stdc++.h> // clang-format off
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
namespace rgs = std::ranges;

using std::cin, std::cout;
using std::string, std::vector, std::array, std::pair, std::deque, std::queue, std::priority_queue,
      std::set, std::multiset, std::map, std::unordered_map, std::unordered_set;

template <class T>
bool minmin(T& a, const std::type_identity_t<T>& b) { return b < a ? (a = b, true) : false; }
template <class T>
bool maxmax(T& a, const std::type_identity_t<T>& b) { return a < b ? (a = b, true) : false; }
void yes(bool ok = true) { cout << (ok ? "YES\n" : "NO\n"); }
void no() { yes(false); }

template <class T>
std::istream& operator>>(std::istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}
template <class T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
    for (int i{}; i < std::ssize(v); ++i) os << (i ? " " : "") << v[i];
    return os;
} // clang-format on

// ---------------------------------------------------------

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> dp(m + 2), diff(m + 2);
    int p{};

    auto flush = [&] {
        int run{};
        for (int i{}; i <= p; ++i) {
            run += diff[i];
            dp[i] += run;
        }
        std::fill(diff.begin(), diff.begin() + p + 2, 0);
    };

    for (int k{}; k < n; ++k) {
        int r;
        cin >> r;
        if (r == 0) {
            flush();
            ++p;
            dp[p] = dp[p - 1];
            for (int i = p - 1; i > 0; --i)
                maxmax(dp[i], dp[i - 1]);
        } else if (r > 0) {
            if (r <= p)
                ++diff[r], --diff[p + 1];
        } else {
            int s = -r;
            if (s <= p)
                ++diff[0], --diff[p - s + 1];
        }
    }
    flush();
    cout << *std::max_element(dp.begin(), dp.begin() + p + 1) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
