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

    vector<int> deg(n), cnt(n);
    for (int v{}; v < n; ++v) {
        deg[v] = std::ssize(adj[v]);
        ++cnt[deg[v]];
    }
    int mx = rgs::max(deg);

    int best{};
    for (int u{}; u < n; ++u) {
        --cnt[deg[u]];
        for (int v : adj[u])
            --cnt[deg[v]], ++cnt[deg[v] - 1];

        int x = mx;
        while (x > 0 && cnt[x] == 0)
            --x;
        maxmax(best, deg[u] + x - 1);

        ++cnt[deg[u]];
        for (int v : adj[u])
            ++cnt[deg[v]], --cnt[deg[v] - 1];
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
