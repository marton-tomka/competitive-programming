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

struct DSU {
    vector<int> par, sz;
    int comps;

    DSU(int n)
        : par(n)
        , sz(n, 1)
        , comps(n) {
        rgs::iota(par, 0);
    }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            std::swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        --comps;
        return true;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> edges(m);
    i64 tot{};
    for (auto& [w, u, v] : edges) {
        cin >> u >> v >> w;
        --u, --v;
        tot += w;
    }

    rgs::sort(edges);
    DSU dsu(n);
    vector<i64> wt, pre{0};
    wt.reserve(n);
    pre.reserve(n);
    for (auto [w, u, v] : edges)
        if (dsu.unite(u, v)) {
            wt.push_back(w);
            pre.push_back(pre.back() + w);
        }

    int S = std::ssize(wt);
    vector<i64> ans(q);
    for (auto& r : ans) {
        i64 x;
        cin >> x;

        int lo{}, hi = S;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (wt[mid] >= x * (n - 1 - mid))
                hi = mid;
            else
                lo = mid + 1;
        }

        i64 k = n - 1 - lo;
        r = tot - pre[lo] - x * k * (k + 1) / 2;
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
