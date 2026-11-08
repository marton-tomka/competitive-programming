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
    int n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<i64> cost(n), dp(m);
    vector<int> a(m);
    deque<int> dq;
    for (int r{}; r < n; ++r) {
        cin >> a;
        dq.clear();
        dp[0] = 1;
        dq.push_back(0);
        for (int j = 1; j < m; ++j) {
            while (dq.front() < j - d - 1)
                dq.pop_front();
            dp[j] = dp[dq.front()] + a[j] + 1;
            while (!dq.empty() && dp[dq.back()] >= dp[j])
                dq.pop_back();
            dq.push_back(j);
        }
        cost[r] = dp[m - 1];
    }

    i64 sum{};
    for (int r{}; r < k; ++r)
        sum += cost[r];
    i64 best = sum;
    for (int r = k; r < n; ++r) {
        sum += cost[r] - cost[r - k];
        minmin(best, sum);
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
