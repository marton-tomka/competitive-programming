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
    vector adj(n, vector<int>{});
    for (int i{}; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root{};
    while (std::ssize(adj[root]) == 1)
        ++root;

    vector<int> par(n, -1), order, st{root};
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

    vector<int> cnt(n);
    for (int v{}; v < n; ++v)
        cnt[v] = std::ssize(adj[v]) == 1;
    for (int i = n - 1; i > 0; --i)
        cnt[par[order[i]]] += cnt[order[i]];

    int base{};
    for (int i = 1; i < n; ++i)
        base += cnt[order[i]] & 1;

    if (cnt[root] % 2 == 0) {
        cout << base << '\n';
        return;
    }

    vector<int> val(n);
    int best = std::numeric_limits<int>::max();
    for (int i = 1; i < n; ++i) {
        int u = order[i];
        val[u] = val[par[u]] + (cnt[u] & 1 ? -1 : 1);
        if (std::ssize(adj[u]) == 1)
            minmin(best, val[u]);
    }
    cout << base + best << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
