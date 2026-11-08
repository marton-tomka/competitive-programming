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

template<class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

void solve() {
    int m;
    i64 x;
    cin >> m >> x;
    vector<i64> c(m);
    vector<int> h(m);
    for (int i{}; i < m; ++i)
        cin >> c[i] >> h[i];

    int H = std::accumulate(h.begin(), h.end(), 0);
    vector<i64> dp(H + 1, inf<i64>);
    dp[0] = 0;

    for (int i{}; i < m; ++i) {
        i64 money = x * i;
        for (int s = H; s >= h[i]; --s)
            if (dp[s - h[i]] + c[i] <= money)
                minmin(dp[s], dp[s - h[i]] + c[i]);
    }

    int best{};
    for (int s{}; s <= H; ++s)
        if (dp[s] != inf<i64>)
            best = s;
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
