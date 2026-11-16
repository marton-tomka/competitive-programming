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

constexpr i64 MOD = 1'000'000'007;

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
    mint& operator-=(mint o) {
        if ((v -= o.v) < 0)
            v += MOD;
        return *this;
    }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend std::ostream& operator<<(std::ostream& os, mint a) { return os << a.v; }
};

constexpr int MX = 200'000;
const vector<mint> pw = [] {
    vector<mint> p(MX + 1);
    p[0] = 1;
    for (int i = 1; i <= MX; ++i)
        p[i] = p[i - 1] + p[i - 1];
    return p;
}();

void solve() {
    int n, k;
    cin >> n >> k;
    array<int, 64> f{};
    for (int i{}; i < n; ++i) {
        int x;
        cin >> x;
        ++f[x];
    }

    for (int b{}; b < 6; ++b)
        for (int mask{}; mask < 64; ++mask)
            if (!(mask >> b & 1))
                f[mask] += f[mask | (1 << b)];

    array<mint, 64> h{};
    for (int mask{}; mask < 64; ++mask)
        h[mask] = pw[f[mask]] - 1;

    for (int b{}; b < 6; ++b)
        for (int mask{}; mask < 64; ++mask)
            if (!(mask >> b & 1))
                h[mask] -= h[mask | (1 << b)];

    mint ans;
    for (int mask{}; mask < 64; ++mask)
        if (std::popcount(u32(mask)) == k)
            ans += h[mask];
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
