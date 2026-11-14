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

template<class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    cin >> a;

    vector<i64> c(n), dp(n + 1);
    i64 best = inf<i64>;
    for (int sh{}; sh < 3; ++sh) {
        for (int i{}; i < n; ++i)
            c[i] = a[(i - sh + n) % n];
        dp[0] = 0;
        dp[1] = inf<i64>;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 2] + std::abs(c[i - 1] - c[i - 2]);
            if (i >= 3)
                minmin(dp[i],
                       dp[i - 3] + std::max({c[i - 1], c[i - 2], c[i - 3]}) -
                           std::min({c[i - 1], c[i - 2], c[i - 3]}));
        }
        minmin(best, dp[n]);
    }
    cout << best << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
