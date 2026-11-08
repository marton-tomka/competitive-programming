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
    int n, a, b;
    cin >> n >> a >> b;
    --a, --b;
    vector adj(n, vector<int>{});
    for (int i{}; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs = [&](int s, vector<int>& par) {
        vector<int> dt(n, -1);
        queue<int> q;
        dt[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dt[v] != -1)
                    continue;
                dt[v] = dt[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
        return dt;
    };

    vector<int> par(n, -1);
    auto da = bfs(a, par);
    int d = da[b];

    int c = b;
    for (int s{}; s < (d + 1) / 2; ++s)
        c = par[c];

    vector<int> tmp(n, -1);
    auto dc = bfs(c, tmp);
    cout << (d + 1) / 2 + 2 * (n - 1) - rgs::max(dc) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
