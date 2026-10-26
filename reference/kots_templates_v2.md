# kots CF templates v2

[-- SKELETON](#skeleton)
[-- I/O](#kots-io)
[-- MODULAR ARITHMETIC](#mod)
[-- BASICS](#basics)
[-- DATA STRUCTURES](#data-structures)
[-- GRAPHS](#graphs)
[-- TREES](#trees)
[-- DP](#dp)
[-- STRINGS](#strings)
[-- GRIDS](#grids)
[-- RANDOM](#random)

---

## skeleton

```cpp
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

}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
```

---- **std one-liners** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
rgs::sort(v);  rgs::sort(v, std::greater{});  rgs::reverse(v);
rgs::max(v);  rgs::min(v);  rgs::count(v, x);                  // values, not iterators
int i = rgs::lower_bound(v, x) - v.begin();                    // first >= x (upper_bound: first > x)
v.erase(rgs::unique(v).begin(), v.end());                      // dedupe, after sorting
rgs::iota(p, 0);  rgs::shuffle(v, rng);                        // rng: see [random]
std::accumulate(v.begin(), v.end(), 0LL);                      // 0LL, or the sum is computed in int
std::ssize(v)                                                  // signed size: i < std::ssize(v), no casts
std::max<i64>(a, b);  1LL * a * b;                             // mixing int and i64
__int128(a) * b <= lim                                         // overflow-safe check; cin / cout can't do __int128
std::popcount(u64(x));  std::countr_zero(u64(x));  std::bit_width(u64(x)) - 1;  // x >= 0; last = floor(log2 x)
__builtin_popcountll(x);  std::__lg(x);                        // GCC versions, take signed values
(a + b - 1) / b                                                // ceil(a / b) for a >= 0, b > 0
s.lower_bound(x)                                               // set/map: the MEMBER (std:: one is O(n))
```

---

## kots I/O

[I/O plumbing](kots_io_plumbing.md)

```cpp
vector<int> a(n);
cin >> a;                              // n values
vector<pair<int, int>> e(m);
for (auto& [u, v] : e) cin >> u >> v;  // m pairs (--u, --v here if 1-indexed)
vector<string> g(R);
cin >> g;                              // char grid, g[r][c]
cout << a << '\n';                     // space-separated
// interactive: cout << query << std::endl;  (endl flushes; the untied cin no longer does)
```

---

## mod

---- **mod** basics ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
constexpr i64 MOD = 998'244'353; // 1'000'000'007 is better sometimes
i64 add(i64 a, i64 b) { a += b; return a >= MOD ? a - MOD : a; }
i64 sub(i64 a, i64 b) { a -= b; return a < 0 ? a + MOD : a; }
i64 mul(i64 a, i64 b) { return a * b % MOD; }

// (x % MOD + MOD) % MOD   true mathematical mod for negative x
```

---- **mint** (modular int) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: MOD above*

```cpp
// ---- global ----
struct mint {
    int v{};
    mint() = default;
    mint(i64 x) : v(int((x % MOD + MOD) % MOD)) {}
    mint& operator+=(mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int(i64(v) * o.v % MOD); return *this; }
    mint& operator/=(mint o) { return *this *= o.inv(); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    mint operator-() const { return mint() - *this; }
    bool operator==(const mint&) const = default;
    mint pow(i64 e) const { mint r = 1, b = *this; for (; e > 0; e >>= 1, b *= b) if (e & 1) r *= b; return r; }
    mint inv() const { return pow(MOD - 2); } // MOD must be prime
    friend std::ostream& operator<<(std::ostream& os, mint a) { return os << a.v; }
    friend std::istream& operator>>(std::istream& is, mint& a) { i64 x; is >> x; a = x; return is; }
};
// mint x = 5;  x += y * 3;  x / 2;  x.pow(n);  cout << x;  vector<mint> dp(n + 1);
// probability / expected value p/q "mod MOD"  ->  mint(p) / q
```

---- **binomials** (nCr) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: mint*

```cpp
// ---- global ----
struct Binom {
    vector<mint> f, fi; // n!, 1/n!
    Binom(int n) : f(n + 1, 1), fi(n + 1, 1) {
        for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i;
        fi[n] = f[n].inv();
        for (int i = n; i > 0; --i) fi[i - 1] = fi[i] * i;
    }
    mint operator()(int n, int k) const { return k < 0 || k > n ? 0 : f[n] * fi[k] * fi[n - k]; }
} binom(1'000'000); // >= the largest n you'll ask for; built once at startup (~12 ms)

// binom(n, k);  binom.f[n] = n!;  binom.fi[n] = 1 / n!
// n identical balls into k boxes: binom(n + k - 1, k - 1)      catalan(n) = binom(2n, n) / (n + 1)
```

---

## basics

---- **binary search** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// FIRST x in [lo, hi) with pred(x); pred looks like F F F T T T; hi itself = "none"
int lo{}, hi = n;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (pred(mid)) hi = mid;
    else lo = mid + 1;
}
```

```cpp
// LAST x in [lo, hi] with pred(x); pred looks like T T T F F F; pred(lo) must hold
int lo{}, hi = n - 1;
while (lo < hi) {
    int mid = lo + (hi - lo + 1) / 2;
    if (pred(mid)) lo = mid;
    else hi = mid - 1;
}
```

---- **two pointers** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
rgs::sort(v);

int i{}, j = n - 1;
while (i < j) {
    i64 s = i64(v[i]) + v[j];
    if (s == tgt) break;
    if (s < tgt) ++i;
    else --j;
}
```

---- **sliding window** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// longest window with sum <= k (non-negative values)
i64 sum{};
int best{};

for (int l{}, r{}; r < n; ++r) {
    sum += v[r];
    while (sum > k)
        sum -= v[l++];
    maxmax(best, r - l + 1);
}
```

---- 1D **prefix sums** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<i64> pref(n + 1);
for (int i{}; i < n; ++i)
    pref[i + 1] = pref[i] + v[i];

// sum of v[l..r) : pref[r] - pref[l]
```

---- 1D **difference array** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<i64> diff(n + 1);
diff[l] += x;
diff[r + 1] -= x; // range add x on [l, r] inclusive

vector<i64> v(n);
i64 run{};
for (int i{}; i < n; ++i) {
    run += diff[i];
    v[i] = run;
}
```

---- **coordinate compression** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<int> xs = a; // every value that matters (append other arrays if they share the axis)
rgs::sort(xs);
xs.erase(rgs::unique(xs).begin(), xs.end());
auto id = [&](int x) { return int(rgs::lower_bound(xs, x) - xs.begin()); }; // value -> [0, |xs|)

for (int& x : a) x = id(x);
```

---- **gcd / lcm** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----  hand-rolled; std::gcd / std::lcm do the same
i64 gcd(i64 a, i64 b) { while (b) { a %= b; std::swap(a, b); } return a; }
i64 lcm(i64 a, i64 b) { return a / gcd(a, b) * b; }

// ---- solve() ----
i64 g = std::gcd(a, b), l = std::lcm(a, b); // gcd(0, x) == x; lcm can overflow: check a / g > LIM / b first
```

---- **binary exp**onentiation ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
i64 bexp(i64 b, i64 e, i64 mod) { // b^e % mod; mod up to ~3e9 (b * b must fit in i64)
    i64 r = 1 % mod;
    b = (b % mod + mod) % mod;
    while (e > 0) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}
// with mint: mint(b).pow(e)
```

---- **sieve** + smallest prime factor ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----  built once at startup (~7 ms), NOT per test case
constexpr int MX = 1'000'000;
const vector<int> spf = [] {
    vector<int> s(MX + 1);
    for (int i = 2; i <= MX; ++i) {
        if (s[i]) continue;
        for (int j = i; j <= MX; j += i)
            if (!s[j]) s[j] = i;
    }
    return s;
}();
// prime  <=>  x >= 2 && spf[x] == x

// ---- solve() ---- O(log x)
auto factor = [&](int x) {
    vector<pair<int, int>> f;
    while (x > 1) {
        int p = spf[x], e{};
        while (x % p == 0) { x /= p; ++e; }
        f.push_back({p, e});
    }
    return f;
};
```

---- **multiples / divisors** (harmonic loop) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// gcd counting, divisor sums: for every d visit all multiples of d -> O(MX log MX)
vector<int> freq(MX + 1), cnt(MX + 1); // freq[v] = how many times v occurs
for (int d = 1; d <= MX; ++d)
    for (int m = d; m <= MX; m += d) cnt[d] += freq[m]; // cnt[d] = # elements divisible by d

// all divisors of one x in O(sqrt x)
vector<i64> divs;
for (i64 d = 1; d * d <= x; ++d) {
    if (x % d) continue;
    divs.push_back(d);
    if (d != x / d) divs.push_back(x / d);
}
```

---- **trial division** (up to ~1e12) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
vector<pair<i64, int>> factor(i64 n) {
    vector<pair<i64, int>> f;
    for (i64 d = 2; d * d <= n; ++d) {
        if (n % d) continue;
        int e{};
        while (n % d == 0) { n /= d; ++e; }
        f.push_back({d, e});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}
```

---- **monotonic stack** (prev/next smaller & histogram) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// prv[i] = nearest j < i with a[j] < a[i]  (else -1)
// nxt[i] = nearest j > i with a[j] <= a[i] (else n)
vector<int> prv(n, -1), nxt(n, n), st;
st.reserve(n);
for (int i{}; i < n; ++i) {
    while (!st.empty() && a[st.back()] >= a[i]) {
        nxt[st.back()] = i;
        st.pop_back();
    }
    if (!st.empty()) prv[i] = st.back();
    st.push_back(i);
}

// largest rectangle in histogram O(n)
i64 max_area{};
for (int i{}; i < n; ++i)
    maxmax(max_area, 1LL * a[i] * (nxt[i] - prv[i] - 1));

// a[i] is the min of exactly (i - prv[i]) * (nxt[i] - i) subarrays, each counted once even with duplicates
// (n ~ 2e5 with a ~ 1e9 can pass 9.2e18: use mint, or __int128, then)
i64 sum_of_mins{};
for (int i{}; i < n; ++i)
    sum_of_mins += 1LL * a[i] * (i - prv[i]) * (nxt[i] - i);
```

---- **monotonic deque** (sliding window max) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
deque<int> dq;
vector<int> window_max;
if (n >= k) window_max.reserve(n - k + 1);

for (int i{}; i < n; ++i) {
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
    dq.push_back(i);
    if (dq.front() <= i - k) dq.pop_front();
    if (i >= k - 1) window_max.push_back(a[dq.front()]);
}
```

---

## data structures

---- **Fenwick tree** (BIT) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----  // point add, range sum, 0-indexed, O(log n)
struct BIT {
    int n;
    vector<i64> t;
    BIT(int n) : n(n), t(n + 1) {}
    void add(int i, i64 x) { for (++i; i <= n; i += i & -i) t[i] += x; }
    i64 sum(int r) const { i64 s{}; for (; r > 0; r -= r & -r) s += t[r]; return s; }
    i64 sum(int l, int r) const { return sum(r) - sum(l); }
};

// ---- solve() ----
// inversions (a compressed to [0, n)): pairs j < i with a[j] > a[i]
BIT bit(n);
i64 inv{};
for (int i{}; i < n; ++i) {
    inv += bit.sum(a[i] + 1, n);
    bit.add(a[i], 1);
}
```

---- **segment tree** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----  // point set, range query; op must be associative, e = its identity
template <class T, class F>
struct Seg {
    int n;
    F op;
    T e;
    vector<T> t;
    Seg(int n, F op, T e) : n(n), op(op), e(e), t(2 * n, e) {}
    Seg(const vector<T>& a, F op, T e) : Seg(std::ssize(a), op, e) {
        for (int i{}; i < n; ++i) t[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    void set(int i, T x) { for (t[i += n] = x; i >>= 1;) t[i] = op(t[2 * i], t[2 * i + 1]); }
    T get(int i) const { return t[i + n]; }
    T query(int l, int r) const {
        T L = e, R = e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = op(L, t[l++]);
            if (r & 1) R = op(t[--r], R);
        }
        return op(L, R);
    }
};

// ---- solve() ----
// the type of e picks T: 0 -> int, 0LL -> i64; the lambda's parameter types must match it
Seg mx(n, [](i64 x, i64 y) { return std::max(x, y); }, std::numeric_limits<i64>::min());
Seg sm(a, [](i64 x, i64 y) { return x + y; }, 0LL);
mx.set(i, x);
i64 best = mx.query(l, r), total = sm.query(0, n);
```

---- **lazy segment tree** (range add; range sum / min / max) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----  // all ranges are [l, r), 0-indexed
struct LazySeg {
    struct Node { i64 sum = 0, mn = 0, mx = 0; };
    static constexpr i64 INF = std::numeric_limits<i64>::max();
    int n;
    vector<Node> t;
    vector<i64> lz;
    LazySeg(int n) : n(n), t(4 * n), lz(4 * n) {}
    LazySeg(const vector<i64>& a) : LazySeg(std::ssize(a)) { if (n) build(1, 0, n, a); }

    static Node pull(const Node& a, const Node& b) {
        return {a.sum + b.sum, std::min(a.mn, b.mn), std::max(a.mx, b.mx)};
    }
    void put(int p, int len, i64 x) { t[p].sum += x * len, t[p].mn += x, t[p].mx += x, lz[p] += x; }
    void push(int p, int l, int m, int r) {
        if (lz[p]) put(2 * p, m - l, lz[p]), put(2 * p + 1, r - m, lz[p]), lz[p] = 0;
    }
    void build(int p, int l, int r, const vector<i64>& a) {
        if (r - l == 1) { t[p] = {a[l], a[l], a[l]}; return; }
        int m = (l + r) / 2;
        build(2 * p, l, m, a), build(2 * p + 1, m, r, a);
        t[p] = pull(t[2 * p], t[2 * p + 1]);
    }
    void add(int ql, int qr, i64 x, int p, int l, int r) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) return put(p, r - l, x);
        int m = (l + r) / 2;
        push(p, l, m, r);
        add(ql, qr, x, 2 * p, l, m), add(ql, qr, x, 2 * p + 1, m, r);
        t[p] = pull(t[2 * p], t[2 * p + 1]);
    }
    Node query(int ql, int qr, int p, int l, int r) {
        if (qr <= l || r <= ql) return {0, INF, -INF};
        if (ql <= l && r <= qr) return t[p];
        int m = (l + r) / 2;
        push(p, l, m, r);
        return pull(query(ql, qr, 2 * p, l, m), query(ql, qr, 2 * p + 1, m, r));
    }
    void add(int l, int r, i64 x) { add(l, r, x, 1, 0, n); }
    Node query(int l, int r) { return query(l, r, 1, 0, n); }
};

// ---- solve() ----
LazySeg seg(a);
seg.add(l, r, x);
auto [sum, mn, mx] = seg.query(l, r);
// other lazy ops (range assign, ...): change Node, put(), pull() and the identity in query()
```

---- **sparse table** (static range min / max / gcd) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ---- // O(n log n) build, O(1) query; op must be idempotent: min, max, gcd, &, |
template <class T, class F>
struct Sparse {
    vector<vector<T>> t;
    F op;
    Sparse(const vector<T>& a, F op) : t{a}, op(op) {
        for (int k = 1; 1 << k <= std::ssize(a); ++k) {
            t.emplace_back(std::ssize(a) - (1 << k) + 1);
            for (int i{}; i < std::ssize(t[k]); ++i)
                t[k][i] = op(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
        }
    }
    T query(int l, int r) const {
        int k = std::bit_width(u32(r - l)) - 1;
        return op(t[k][l], t[k][r - (1 << k)]);
    }
};

// ---- solve() ----
Sparse rmq(a, [](int x, int y) { return std::min(x, y); });
int lo = rmq.query(l, r);
```

---- **ordered set** (k-th element, rank) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <class T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

// ---- solve() ----
ordered_set<int> os;
os.insert(x);
os.erase(x);
int below = os.order_of_key(x); // # elements < x
int kth = *os.find_by_order(k); // k-th smallest, 0-based
// duplicates: ordered_set<pair<int, int>> holding {value, unique id}
```

---

## graphs

---- basic **adjacency list** build ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
int n, m;
cin >> n >> m;

vector adj(n, vector<int>{});
for (int i{}; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// weighted:  vector adj(n, vector<pair<int, int>>{});  adj[u].emplace_back(v, w);
// tree as parents p_2..p_n:  for (int i = 1; i < n; ++i) { int p; cin >> p; adj[p - 1].push_back(i); }  (children lists)
```

---- simple 1D **DFS** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<bool> vis(n);

auto dfs = [&](this auto&& self, int u) -> void {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v]) self(v);
};

for (int i{}; i < n; ++i)
    if (!vis[i]) dfs(i);
```

---- simple 1D **BFS** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<int> dt(n, -1);
vector<int> par(n, -1);
queue<int> q;

dt[start] = 0;
q.push(start);

while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : adj[u]) {
        if (dt[v] != -1) continue;
        dt[v] = dt[u] + 1;
        par[v] = u;
        q.push(v);
    }
}

// path start -> tgt (if dt[tgt] != -1)
vector<int> path;
for (int v = tgt; v != -1; v = par[v]) path.push_back(v);
rgs::reverse(path);
```

---- **0-1 BFS** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
template <class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

// ---- solve() ----
// every edge weight is 0 or 1: a deque instead of a heap, O(n + m)
vector<int> d(n, inf<int>);
deque<int> dq{s};
d[s] = 0;

while (!dq.empty()) {
    int u = dq.front();
    dq.pop_front();
    for (auto [v, w] : adj[u]) {
        if (!minmin(d[v], d[u] + w)) continue;
        if (w) dq.push_back(v);
        else dq.push_front(v);
    }
}
```

---- **Dijkstra** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
template <class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
template <class T>
using min_pq = priority_queue<T, vector<T>, std::greater<T>>;

// ---- solve() ----  adj[u] = {v, w}, w >= 0
vector<i64> d(n, inf<i64>);
min_pq<pair<i64, int>> pq;
d[s] = 0;
pq.push({0, s});

while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (du != d[u]) continue;
    for (auto [v, w] : adj[u])
        if (minmin(d[v], du + w)) pq.push({d[v], v});
}
// unreachable: d[v] == inf<i64>.  extra state (vertex, flag): node id 2 * v + flag
```

---- [grid](#grids) 2D **DFS** ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: [grids](#grids)*

```cpp
vector vis(R, vector<bool>(C));

auto dfs = [&](this auto&& self, int r, int c) -> void {
    vis[r][c] = true;
    for (auto [dr, dc] : dir4) {
        int nr = r + dr, nc = c + dc; // swap in any neighbor rule from [grids]
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (g[nr][nc] == '#' || vis[nr][nc]) continue;
        self(nr, nc);
    }
};
// recursion depth can reach R * C: fine on CF; for ~1e6 cells the BFS below is safer
```

---- [grid](#grids) 2D **BFS** ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: [grids](#grids)*

```cpp
vector dt(R, vector<int>(C, -1));

queue<pair<int, int>> q;
dt[sr][sc] = 0;
q.push({sr, sc});

while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    for (auto [dr, dc] : dir4) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
        if (g[nr][nc] == '#' || dt[nr][nc] != -1) continue;

        dt[nr][nc] = dt[r][c] + 1;
        q.push({nr, nc});
    }
}
```

---- connected **components** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<int> comp(n, -1);
int comps{};

for (int i{}; i < n; ++i) {
    if (comp[i] != -1) continue;
    queue<int> q;
    comp[i] = comps;
    q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (comp[v] != -1) continue;
            comp[v] = comps;
            q.push(v);
        }
    }
    ++comps;
}
```

---- **bipartite** check ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<int> col(n, -1);
bool ok = true;

for (int i{}; i < n && ok; ++i) {
    if (col[i] != -1) continue;

    queue<int> q;
    col[i] = 0;
    q.push(i);

    while (!q.empty() && ok) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (col[v] == -1) {
                col[v] = col[u] ^ 1;
                q.push(v);
            } else if (col[v] == col[u]) {
                ok = false;
            }
        }
    }
}
```

---- undirected **cycle detection** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector<int> vis(n);
bool cycle = false;

auto dfs = [&](this auto&& self, int u, int par) -> void {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (v == par) continue;
        if (vis[v]) { cycle = true; return; }
        self(v, u);

        if (cycle) return;
    }
};

for (int i{}; i < n; ++i)
    if (!vis[i]) dfs(i, -1);
// or DSU: an edge whose endpoints are already united closes a cycle
```

---- directed **cycle detection** (Kahn's) + **topological order** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// min_pq<int> instead of q -> lexicographically smallest order
vector<int> indeg(n);
for (int u{}; u < n; ++u)
    for (int v : adj[u])
        ++indeg[v];

queue<int> q;
for (int i{}; i < n; ++i)
    if (indeg[i] == 0) q.push(i);

vector<int> order;
order.reserve(n);

while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);

    for (int v : adj[u])
        if (--indeg[v] == 0) q.push(v);
}

bool cycle = std::ssize(order) != n;
// DP on a DAG: walk `order` forwards (sources first) or backwards (sinks first)
```

---- **union find** (dsu) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
struct DSU {
    vector<int> par, sz;
    int comps;

    DSU(int n) : par(n), sz(n, 1), comps(n) { rgs::iota(par, 0); }

    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    bool same(int a, int b) { return find(a) == find(b); }
    int size(int x) { return sz[find(x)]; }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) std::swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        --comps;
        return true;
    }
};
```

---- **Kruskal** (minimum spanning tree) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: DSU*

```cpp
vector<array<int, 3>> edges(m);
for (auto& [w, u, v] : edges) {
    cin >> u >> v >> w;
    --u, --v;
}

rgs::sort(edges);
DSU dsu(n);
i64 mst{};
for (auto [w, u, v] : edges)
    if (dsu.unite(u, v)) mst += w;
// dsu.comps > 1  ->  the graph was disconnected (this is then a min spanning forest)
```

---

## trees

---- tree **backbone** (parent, depth, order, subtree size, Euler tour) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// iterative DFS, no recursion. root = 0, adj = undirected tree
vector<int> par(n, -1), dep(n), order, st{0};
order.reserve(n);
while (!st.empty()) {
    int u = st.back();
    st.pop_back();
    order.push_back(u);
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        dep[v] = dep[u] + 1;
        st.push_back(v);
    }
}

vector<int> sz(n, 1), tin(n);
for (int i = n - 1; i > 0; --i)
    sz[par[order[i]]] += sz[order[i]];
for (int i{}; i < n; ++i)
    tin[order[i]] = i;

// order: parents before children -> bottom-up DP = walk order backwards
// subtree of u = order[tin[u] .. tin[u] + sz[u])  -> subtree queries = range queries (BIT / Seg over tin)
// u is an ancestor of v  <=>  tin[u] <= tin[v] && tin[v] < tin[u] + sz[u]
```

---- **rerooting** (answer for every root) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: backbone*

```cpp
// example: ans[u] = sum of distances from u to every vertex. Shape: 2 passes over `order`
// down[u] = sum of distances from u into its own subtree
// pass 1, children before parents
// pass 2, parents before children: move the root from par[u] to u
// sz[u] vertices get 1 closer, n - sz[u] get 1 farther
vector<i64> down(n), ans(n);

for (int i = n - 1; i > 0; --i) {
    int u = order[i];
    down[par[u]] += down[u] + sz[u];
}

ans[0] = down[0];
for (int i = 1; i < n; ++i) {
    int u = order[i];
    ans[u] = ans[par[u]] - sz[u] + (n - sz[u]);
}
```

---- **LCA** (binary lifting) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: backbone*

```cpp
int LOG = std::bit_width(u32(n));
vector up(LOG, par);
up[0][0] = 0;
for (int k = 1; k < LOG; ++k)
    for (int v{}; v < n; ++v)
        up[k][v] = up[k - 1][up[k - 1][v]];

auto lca = [&](int a, int b) {
    if (dep[a] < dep[b]) std::swap(a, b);
    for (int k = LOG - 1; k >= 0; --k)
        if (dep[a] - (1 << k) >= dep[b]) a = up[k][a];
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; --k)
        if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
    return up[0][a];
};
auto dist = [&](int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; };

// k-th ancestor of v (k <= dep[v]):  for (int j{}; j < LOG; ++j) if (k >> j & 1) v = up[j][v];
```

---

## dp

---- **memo / tabulation** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// top-down (memo)
vector<i64> memo(n + 1, -1);
auto f = [&](this auto&& self, int i) -> i64 {
    if (/* base case */) return /* base value */;
    i64& r = memo[i];
    if (r != -1) return r;
    return r = /* recurrence: self(...) */;
};
i64 ans = f(n);

// bottom-up (tabulation)
vector<i64> dp(n + 1);
dp[0] = /* base */;
for (int i = 1; i <= n; ++i)
    dp[i] = /* recurrence: dp[i - 1], dp[i - 2], ... */;
// answer: dp[n]
```

---- **kadane** (max subarray sum) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
i64 cur = a[0], best = a[0];
for (int i = 1; i < n; ++i) {
    cur = std::max<i64>(a[i], cur + a[i]);
    maxmax(best, cur);
}
```

---- **house robber** (no adjacent) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
i64 skip{}, take = a[0];
for (int i = 1; i < n; ++i) {
    i64 nskip = std::max(skip, take);
    i64 ntake = skip + a[i];
    skip = nskip;
    take = ntake;
}
i64 best = std::max(skip, take);
```

---- **knapsack** (0/1 + unbounded + subset-sum) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// 0/1: each item once -- capacity loop DOWNWARD
vector<i64> dp(W + 1);
for (auto [w, val] : items)
    for (int c = W; c >= w; --c)
        maxmax(dp[c], dp[c - w] + val);

// unbounded: unlimited copies -- only the loop direction flips, UPWARD
for (auto [w, val] : items)
    for (int c = w; c <= W; ++c)
        maxmax(dp[c], dp[c - w] + val);

// subset-sum feasibility (0/1, values irrelevant)
vector<bool> can(W + 1);
can[0] = true;
for (int w : wts)
    for (int c = W; c >= w; --c)
        can[c] = can[c] || can[c - w];

// the same with a bitset: ~64x faster, the go-to when W * n ~ 1e9
// size must be a compile-time constant >= W + 1
std::bitset<100'001> bs;
bs[0] = 1;
for (int w : wts) bs |= bs << w;
// bs[c] == 1  <=>  some subset sums to c
```

---- **knapsack** (bounded) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// item available k times -> binary-split into 0/1 bundles
vector<pair<int, i64>> flat;
for (auto [w, val, k] : items)
    for (int take = 1; k > 0; take *= 2) {
        int t = std::min(take, k);
        k -= t;
        flat.push_back({w * t, val * t});
    }
// then 0/1 knapsack over flat
```

---- **coin change** (min coins + counting ways) ---- [*[ dip ]*](#kots-cf-templates-v2) *counting needs: mint*

```cpp
// ---- global ----
template <class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

// ---- solve() ----
// min coins (unbounded); dp[A] == inf<int> -> impossible
vector<int> dp(A + 1, inf<int>);
dp[0] = 0;
for (int x = 1; x <= A; ++x)
    for (int c : coins)
        if (c <= x) minmin(dp[x], dp[x - c] + 1);

// count ways, UNORDERED (combinations) -- coin OUTER
vector<mint> ways(A + 1);
ways[0] = 1;
for (int c : coins)
    for (int x = c; x <= A; ++x)
        ways[x] += ways[x - c];

// count ways, ORDERED (sequences) -- amount OUTER
vector<mint> seq(A + 1);
seq[0] = 1;
for (int x = 1; x <= A; ++x)
    for (int c : coins)
        if (c <= x) seq[x] += seq[x - c];
```

---- **LIS** (O(n^2) + O(n log n)) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// O(n^2): dp[i] = LIS length ending exactly at i
vector<int> dp(n, 1);
for (int i{}; i < n; ++i)
    for (int j{}; j < i; ++j)
        if (a[j] < a[i]) maxmax(dp[i], dp[j] + 1);
int best = rgs::max(dp);

// O(n log n): tail[k] = smallest possible last element of an increasing subsequence of length k + 1
// upper_bound -> non-decreasing
// tail itself is NOT the actual subsequence
vector<int> tail;
for (int x : a) {
    auto it = rgs::lower_bound(tail, x);
    if (it == tail.end()) tail.push_back(x);
    else *it = x;
}
best = std::ssize(tail);
```

---- **LCS** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
vector dp(n + 1, vector<int>(m + 1));
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
        dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : std::max(dp[i - 1][j], dp[i][j - 1]);
int best = dp[n][m];

// reconstruction: walk back from (n, m)
string res;
for (int i = n, j = m; i > 0 && j > 0;) {
    if (a[i - 1] == b[j - 1]) { res += a[i - 1]; --i, --j; }
    else if (dp[i - 1][j] >= dp[i][j - 1]) --i;
    else --j;
}
rgs::reverse(res);
```

---- [grid](#grids) 2D **dp** (path count, obstacles) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: mint*

```cpp
vector dp(R, vector<mint>(C));
dp[0][0] = g[0][0] != '#';
for (int r{}; r < R; ++r)
    for (int c{}; c < C; ++c) {
        if (g[r][c] == '#') { dp[r][c] = 0; continue; }
        if (r) dp[r][c] += dp[r - 1][c];
        if (c) dp[r][c] += dp[r][c - 1];
    }
```

---- 2D **prefix sums / diff** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// build: p[i][j] = sum of the i x j top-left subgrid (1-based padding)
vector p(n + 1, vector<i64>(m + 1));
for (int i{}; i < n; ++i)
    for (int j{}; j < m; ++j)
        p[i + 1][j + 1] = a[i][j] + p[i][j + 1] + p[i + 1][j] - p[i][j];

// query: sum over rows [r1, r2) x cols [c1, c2)
i64 s = p[r2][c2] - p[r1][c2] - p[r2][c1] + p[r1][c1];

// 2D difference: range add x on rows [r1, r2) x cols [c1, c2)
vector d(n + 1, vector<i64>(m + 1));
d[r1][c1] += x, d[r1][c2] -= x;
d[r2][c1] -= x, d[r2][c2] += x;
// finalize: prefix-sum along rows, then along columns -> d[i][j] = value of cell (i, j)
for (int i{}; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
        d[i][j] += d[i][j - 1];
for (int i = 1; i <= n; ++i)
    for (int j{}; j <= m; ++j)
        d[i][j] += d[i - 1][j];
```

---- **range-sum dp** (prefix optimization) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: mint*

```cpp
// dp[i] = dp[i - k] + ... + dp[i - 1]
// sum dp[lo..i-1] in O(1)
vector<mint> dp(n + 1), pref(n + 2);
dp[0] = 1;
pref[1] = 1;
for (int i = 1; i <= n; ++i) {
    int lo = std::max(0, i - k);
    dp[i] = pref[i] - pref[lo];
    pref[i + 1] = pref[i] + dp[i];
}
```

---- **dp + segment tree** (best earlier state, by value) ---- [*[ dip ]*](#kots-cf-templates-v2) *needs: Seg*

```cpp
// dp[i] = w[i] + max{ dp[j] : j < i, a[j] < a[i] }  (a compressed to [0, k), w >= 0) -- weighted LIS
// any "best earlier j with a value condition" dp: O(n^2) -> O(n log n)
Seg best(k, [](i64 x, i64 y) { return std::max(x, y); }, 0LL);
i64 ans{};
for (int i{}; i < n; ++i) {
    i64 cur = best.query(0, a[i]) + w[i];
    best.set(a[i], std::max(best.get(a[i]), cur));
    maxmax(ans, cur);
}
```

---- **bitmask dp** (subsets, submasks, SOS) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
template <class T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

// ---- solve() ----
// n <= ~20. dp[mask][v] = cheapest way to visit exactly the set mask, ending at v (TSP shape)
vector dp(1 << n, vector<i64>(n, inf<i64>));
for (int v{}; v < n; ++v)
    dp[1 << v][v] = 0;
for (int mask = 1; mask < (1 << n); ++mask)
    for (int u{}; u < n; ++u) {
        if (!(mask >> u & 1) || dp[mask][u] == inf<i64>) continue;
        for (int v{}; v < n; ++v)
            if (!(mask >> v & 1)) minmin(dp[mask | (1 << v)][v], dp[mask][u] + w[u][v]);
    }

// all non-empty submasks s of mask, descending (over every mask together: O(3^n))
for (int s = mask; s > 0; s = (s - 1) & mask) { /* ... */ }

// SOS: f[msk] = sum of a[s] over all submasks s of msk, O(n 2^n)   (a.size() == 1 << n)
vector<i64> f = a;
for (int b{}; b < n; ++b)
    for (int msk{}; msk < (1 << n); ++msk)
        if (msk >> b & 1) f[msk] += f[msk ^ (1 << b)];
```

---

## strings

---- **prefix function** (KMP) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// pi[i] = length of the longest proper prefix of s[0..i] that is also a suffix of it
vector<int> pi(std::ssize(s));
for (int i = 1; i < std::ssize(s); ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    pi[i] = j + (s[i] == s[j]);
}
// find p in t: run on s = p + '#' + t; every i with pi[i] == |p| is a match starting at t[i - 2|p|]
// smallest period of s: |s| - pi.back()   (s is a power of it iff that length divides |s|)
```

---- **Z-function** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// z[i] = length of the longest common prefix of s and s[i..]   (z[0] = 0 by convention)
vector<int> z(std::ssize(s));
for (int i = 1, l = 0, r = 0; i < std::ssize(s); ++i) { // [l, r) = rightmost window matching a prefix
    if (i < r) z[i] = std::min(r - i, z[i - l]);
    while (i + z[i] < std::ssize(s) && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i];
}
```

---- string **hashing** (mod 2^61 - 1) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
struct Hash { // O(1) substring hash; collision chance ~ len / 2^61 per comparison; random base -> unhackable
    static constexpr u64 M = (1ULL << 61) - 1;
    static inline const u64 B = [] {
        std::mt19937_64 g(std::chrono::steady_clock::now().time_since_epoch().count());
        return g() % (M - 256) + 256;
    }();
    static u64 mul(u64 a, u64 b) {
        __uint128_t c = __uint128_t(a) * b;
        u64 r = u64(c & M) + u64(c >> 61);
        return r >= M ? r - M : r;
    }
    vector<u64> h, pw;
    Hash(const string& s) : h(s.size() + 1), pw(s.size() + 1, 1) {
        for (int i{}; i < std::ssize(s); ++i) {
            h[i + 1] = (mul(h[i], B) + uint8_t(s[i])) % M;
            pw[i + 1] = mul(pw[i], B);
        }
    }
    u64 get(int l, int r) const { // hash of s[l..r)
        u64 x = h[r] + M - mul(h[l], pw[r - l]);
        return x >= M ? x - M : x;
    }
};

// ---- solve() ----
Hash hs(s);
bool same = hs.get(l1, r1) == hs.get(l2, r2); // B is shared, so hashes of different strings compare too
// palindrome s[l..r): Hash hr(string(s.rbegin(), s.rend()));  hs.get(l, r) == hr.get(n - r, n - l)
```

---

## grids

---- direction tables ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
constexpr pair<int, int> dir4[]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
constexpr pair<int, int> dir8[]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
constexpr pair<int, int> knight[]{{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

// ---- solve() ----
for (auto [dr, dc] : dir4) {
    int nr = r + dr, nc = c + dc;
    // + one neighbor rule from below
}
```

---- grid **adjacency list** build ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// usually unnecessary: BFS/DFS can walk (r, c) directly. Useful for DSU / Dijkstra on cells
auto id = [&](int r, int c) { return r * C + c; };

vector adj(R * C, vector<int>{});
for (int r{}; r < R; ++r)
    for (int c{}; c < C; ++c)
        for (auto [dr, dc] : dir4) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue; // whichever rule below
            adj[id(r, c)].push_back(id(nr, nc));
        }
```

##### neighbor rules ([back to graphs](#graphs))

---- **bounded** ---- [*[ dip ]*](#kots-cf-templates-v2)
```cpp
int nr = r + dr, nc = c + dc;
if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
```

---- **toroidal** (wraparound) ---- [*[ dip ]*](#kots-cf-templates-v2)
```cpp
int nr = (r + dr + R) % R;
int nc = (c + dc + C) % C;
```

---- **cylinder** (different per axis) ---- [*[ dip ]*](#kots-cf-templates-v2)
```cpp
int nr = (r + dr + R) % R;       // wraps
int nc = c + dc;
if (nc < 0 || nc >= C) continue; // bounded
```

---- **maze** (bounded, plus impassable cells) ---- [*[ dip ]*](#kots-cf-templates-v2)
```cpp
int nr = r + dr, nc = c + dc;
if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
if (g[nr][nc] == '#') continue;
```

---- **8-directional** / **custom jumps** (knight moves, etc.) ---- [*[ dip ]*](#kots-cf-templates-v2)
```cpp
for (auto [dr, dc] : dir8)   { /* same rules */ }
for (auto [dr, dc] : knight) { /* same rules */ }
```

---

## random

---- is **number palindrome** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
bool pal(int x) {
    i64 rev{};
    i64 o = x;

    while (x > 0) {
        rev = rev * 10 + (x % 10);
        x /= 10;
    }

    return o == rev;
}
```

---- **rng** ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// ---- solve() ----
i64 r = std::uniform_int_distribution<i64>(lo, hi)(rng); // uniform in [lo, hi]
rgs::shuffle(v, rng);
```

---- **anti-hack hash** for unordered_map / unordered_set ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// ---- global ----
struct chash { // splitmix64 + a per-run random offset: precomputed anti-hash tests can't hit it
    size_t operator()(u64 x) const {
        static const u64 R = std::chrono::steady_clock::now().time_since_epoch().count();
        x += R + 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

// ---- solve() ----
unordered_map<i64, int, chash> cnt;
unordered_set<i64, chash> seen;
// pair key: encode as i64(a) << 32 | b   (a, b >= 0)
```

---- **stress test** (find the failing case) ---- [*[ dip ]*](#kots-cf-templates-v2)

```cpp
// gen.cpp -- one random small test per seed
#include <bits/stdc++.h>

int main(int argc, char** argv) {
    std::mt19937 rng(std::atoi(argv[1]));
    auto rnd = [&](int lo, int hi) { return int(rng() % (hi - lo + 1)) + lo; }; // [lo, hi]
    int n = rnd(1, 8);
    std::cout << 1 << '\n' << n << '\n'; // t = 1
    for (int i = 0; i < n; ++i) std::cout << rnd(1, 10) << ' ';
    std::cout << '\n';
}
```

```bash
# sol.cpp = your solution, brute.cpp = slow but obviously correct
g++-14 -std=c++23 -O2 sol.cpp -o sol && g++-14 -std=c++23 -O2 brute.cpp -o brute && g++-14 -std=c++23 gen.cpp -o gen
for i in $(seq 1 2000); do
    ./gen $i > in.txt; ./sol < in.txt > o1.txt; ./brute < in.txt > o2.txt
    if ! diff -bq o1.txt o2.txt > /dev/null; then echo "seed $i"; cat in.txt; break; fi
done
```
