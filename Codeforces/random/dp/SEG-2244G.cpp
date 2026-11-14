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

template<class T, class F>
struct Seg {
    int n;
    F op;
    T e;
    vector<T> t;
    Seg(int n, F op, T e)
        : n(n)
        , op(op)
        , e(e)
        , t(2 * n, e) {}
    void set(int i, T x) {
        for (t[i += n] = x; i >>= 1;)
            t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    T query(int l, int r) const {
        T L = e, R = e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                L = op(L, t[l++]);
            if (r & 1)
                R = op(t[--r], R);
        }
        return op(L, R);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    cin >> a;

    vector<int> head(n, -1), nxt(n, -1);
    for (int i{}; i < n; ++i) {
        i64 t = i + a[i] + 1;
        if (t < n) {
            nxt[i] = head[t];
            head[t] = i;
        }
    }

    Seg best(n, [](i64 x, i64 y) -> i64 { return std::max(x, y); }, 0LL);
    vector<i64> dp(n);
    i64 ans{};
    for (int j{}; j < n; ++j) {
        for (int i = head[j]; i != -1; i = nxt[i])
            best.set(i, dp[i]);
        i64 lim = j - a[j];
        dp[j] = a[j] + (lim > 0 ? best.query(0, static_cast<int>(lim)) : 0);
        maxmax(ans, dp[j]);
    }
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
