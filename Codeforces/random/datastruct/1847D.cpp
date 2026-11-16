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

struct BIT {
    int n;
    vector<i64> t;
    BIT(int n)
        : n(n)
        , t(n + 1) {}
    void add(int i, i64 x) {
        for (++i; i <= n; i += i & -i)
            t[i] += x;
    }
    i64 sum(int r) const {
        i64 s{};
        for (; r > 0; r -= r & -r)
            s += t[r];
        return s;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    string s;
    cin >> s;

    vector<int> nxt(n + 1);
    rgs::iota(nxt, 0);
    auto find = [&](int u) {
        int r = u;
        while (nxt[r] != r)
            r = nxt[r];
        while (nxt[u] != r)
            u = std::exchange(nxt[u], r);
        return r;
    };

    vector<int> ord(n, -1);
    int K{};
    for (int i{}; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        for (int p = find(l); p <= r; p = find(p)) {
            ord[p] = K++;
            nxt[p] = p + 1;
        }
    }

    BIT bit(K);
    int c{};
    for (int i{}; i < n; ++i)
        if (s[i] == '1') {
            ++c;
            if (ord[i] != -1)
                bit.add(ord[i], 1);
        }

    while (q--) {
        int x;
        cin >> x;
        --x;
        int d = s[x] == '1' ? -1 : 1;
        s[x] ^= 1;
        c += d;
        if (ord[x] != -1)
            bit.add(ord[x], d);

        int L = std::min(c, K);
        cout << L - bit.sum(L) << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
