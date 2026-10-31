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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    vector adj(n, vector<int>{});
    for (int i{}; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> par(n, -1), order, st{0};
    order.reserve(n);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v == par[u])
                continue;
            par[v] = u;
            st.push_back(v);
        }
    }

    vector<int> sz(n, 1);
    for (int i = n - 1; i > 0; --i)
        sz[par[order[i]]] += sz[order[i]];

    auto sq = [](int x) {
        int r = static_cast<int>(std::sqrt(static_cast<double>(x)));
        while (r * r > x)
            --r;
        while ((r + 1) * (r + 1) <= x)
            ++r;
        return r * r == x;
    };

    i64 ans{};
    for (int m{}; m < n; ++m) {
        if (!sq(a[m]))
            continue;
        i64 e1{}, e2{}, e3{};
        for (int v : adj[m]) {
            i64 s = v == par[m] ? n - sz[m] : sz[v];
            e3 += e2 * s;
            e2 += e1 * s;
            e1 += s;
        }
        ans += e2 + e3;
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
