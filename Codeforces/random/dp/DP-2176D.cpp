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

constexpr i64 MOD = 998'244'353;

struct mint {
    int v{};
    mint() = default;
    mint(i64 x)
        : v(int((x % MOD + MOD) % MOD)) {}
    mint& operator+=(mint o) {
        if ((v += o.v) >= MOD)
            v -= MOD;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, mint a) { return os << a.v; }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n);
    cin >> a;
    vector<int> src(m), dst(m);
    for (int i{}; i < m; ++i) {
        cin >> src[i] >> dst[i];
        --src[i], --dst[i];
    }

    vector<int> ord(m);
    rgs::iota(ord, 0);
    rgs::sort(ord, {}, [&](int e) { return pair{src[e], a[dst[e]]}; });

    vector<int> st(n + 1);
    for (int e : ord)
        ++st[src[e] + 1];
    for (int v{}; v < n; ++v)
        st[v + 1] += st[v];

    vector<int> grp(m);
    int g{};
    for (int i{}; i < m; ++i) {
        int e = ord[i], p = i ? ord[i - 1] : -1;
        if (i && (src[p] != src[e] || a[dst[p]] != a[dst[e]]))
            ++g;
        grp[e] = g;
    }

    vector<int> by(m);
    rgs::iota(by, 0);
    rgs::sort(by, std::greater{}, [&](int e) { return a[src[e]] + a[dst[e]]; });

    vector<mint> gs(g + 1);
    mint ans;
    for (int e : by) {
        int v = dst[e];
        i64 tg = a[src[e]] + a[v];
        auto beg = ord.begin() + st[v], end = ord.begin() + st[v + 1];
        auto it = rgs::lower_bound(beg, end, tg, {}, [&](int x) { return a[dst[x]]; });

        mint f = 1;
        if (it != end && a[dst[*it]] == tg)
            f += gs[grp[*it]];
        gs[grp[e]] += f;
        ans += f;
    }
    cout << ans << '\n';
} // shii ion even know atp cuh

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
