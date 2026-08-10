# kots CF templates

[-- SKELETON](#skeleton)
[-- MODULAR ARITHMETIC](#mod)
[-- BASICS](#basics)
[-- GRAPHS](#graphs)
[-- DP](#dp)
[-- GRIDS](#grids)

---

## skeleton

```cpp
#include <bits/stdc++.h>
using ll = long long;

void solve() {

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    while (t--) solve();
}
```

---

## kots I/O

Refer to the doc detailing most cases, here: [OPEN I/O PLUMBING](kots_io_plumbing.md).

---

## mod

```cpp
// 1'000'000'007 is better sometimes
const ll MOD = 998'244'353;
ll add(ll a, ll b) { a += b; return a >= MOD ? a - MOD : a; }
ll sub(ll a, ll b) { a -= b; return a < 0 ? a + MOD : a; }
ll mul(ll a, ll b) { return a * b % MOD; }

(x % MOD + MOD) % MOD // true mathematical mod for negative x
```

---

## basics

---- **binary search** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
int lo{}, hi = n;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (pred(mid)) hi = mid;
    else lo = mid + 1;
}
// lo == hi == first index where pred holds
```

---- **two pointers** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::ranges::sort(v);

int i{}, j = n - 1;
while (i < j) {
    ll s = v[i] + v[j];
    if (s == tgt) break;
    if (s < tgt) ++i;
    else --j;
}
```

---- **sliding window** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
ll sum{};
int best{};

for (int l{}, r{}; r < n; ++r) {
    sum += v[r];
    while (sum > k)
        sum -= v[l++];
    best = std::max(best, r - l + 1);
}
```

---- 1D **prefix sums** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<ll> pref(n + 1, 0);
for (int i{}; i < n; ++i)
    pref[i + 1] = pref[i] + v[i];

// sum of v[l..r) : pref[r] - pref[l]
```

---- 1D **difference array** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<ll> diff(n + 1, 0);
diff[l] += x;
diff[r + 1] -= x; // range add x on [l, r] inclusive

std::vector<ll> v(n);
ll run{};
for (int i{}; i < n; ++i) {
    run += diff[i]; v[i] = run;
}
```

---- **gcd / lcm** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::gcd(a, b)
std::lcm(a, b)

ll gcd(ll a, ll b) { while (b) { a %= b; std::swap(a, b); } return a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
```

---- **binary exp**onentiation ---- [*[ dip ]*](#kots-cf-templates)

```cpp
ll bexp(ll b, ll e, ll mod) {
    ll r = 1;
    b %= mod;
    while (e > 0) {
        if (e & 1) r = r * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return r;
}
```

---- **sieve** + smallest prime factor ---- [*[ dip ]*](#kots-cf-templates)

```cpp
int mx = 1'000'000;
std::vector<int> spf(mx + 1, 0);

for (int i = 2; i <= mx; ++i) {
    if (spf[i]) continue;
    for (int j = i; j <= mx; j += i)
        if (!spf[j]) spf[j] = i;
}

auto factor = [&](int x) {
    std::vector<std::pair<int, int>> f;
    while (x > 1) {
        int p = spf[x], e{};
        while (x % p == 0) { x /= p; ++e; }
        f.push_back({p, e});
    }
    return f;
};
```

---- **trial division** (up to ~1e12) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<std::pair<ll, int>> factor(ll n) {
    std::vector<std::pair<ll, int>> f;
    for (ll d = 2; d * d <= n; ++d) {
        if (n % d) continue;
        int e{};
        while (n % d == 0) { n /= d; ++e; }
        f.push_back({d, e});
    }
    if (n > 1) f.push_back({n, 1}); // leftover prime factor
    return f;
}
```

---- **monotonic stack** (prev/next smaller & histogram) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// prev_smaller[i] = nearest j<i with a[j]<a[i] (else -1)
// next_smaller[i] = nearest j>i with a[j]<=a[i] (else n)
std::vector<int> prev(n, -1), next(n, n);
std::vector<int> st;
st.reserve(n);
for (int i{}; i < n; ++i) {
    while (!st.empty() && a[st.back()] >= a[i]) {
        next[st.back()] = i;
        st.pop_back();
    }
    if (!st.empty()) prev[i] = st.back();
    st.push_back(i);
}

// largest rectangle in histogram O(n)
ll max_area{};
for (int i{}; i < n; ++i) {
    max_area = std::max(max_area, static_cast<ll>(a[i]) * (next_smaller[i] - prev_smaller[i] - 1));
}
```

---- **monotonic deque** (sliding window max) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::deque<int> dq;
std::vector<int> window_max;
if (n >= k) window_max.reserve(n - k + 1);

for (int i{}; i < n; ++i) {
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
    dq.push_back(i);
    if (dq.front() <= i - k) dq.pop_front();
    if (i >= k - 1) window_max.push_back(a[dq.front()]);
}
```

---

## graphs

---- basic **adjacency list** build ---- [*[ dip ]*](#kots-cf-templates)

```cpp
int n, m;
std::cin >> n >> m;

std::vector adj(n, std::vector<int>{});

for (int i{}; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u; --v; // only if 1 indexed testc
    adj[u].push_back(v);
    adj[v].push_back(u); // remove for directed gr (u -> v)
}
```

---- simple 1D **DFS** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<bool> vis(n, false);

auto dfs = [&](this auto&& self, int u) -> void {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            self(v);
        }
    }
};

for (int i{}; i < n; ++i) {
    if (!vis[i]) {
        dfs(i);
    }
}
```

---- simple 1D **BFS** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<int> dt(n, -1); // doubles as 'visited' tracking
std::vector<int> par(n, -1); // for path reconstr if needed
std::queue<int> q;

dt[start] = 0;
q.push(start);

while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
        if (dt[v] == -1) {
            dt[v] = dt[u] + 1;
            par[v] = u;
            q.push(v);
        }
    }
}
```

---- [grid](#grids) 2D **DFS** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
constexpr std::array<int, 4> dr{1, -1, 0, 0};
constexpr std::array<int, 4> dc{0, 0, 1, -1};

std::vector vis(R, std::vector<uint8_t>(C, 0));

auto dfs = [&](this auto&& self, int r, int c) -> void {
    vis[r][c] = 1;
    for (int k{}; k < 4; ++k) {

        int nr = (r + dr[k] + R) % R; // torodial behaviour
        int nc = (c + dc[k] + C) % C;

        if (vis[nr][nc]) continue;
        self(nr, nc);
    }
};
```

---- [grid](#grids) 2D **BFS** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
constexpr std::array<int, 4> dx{1, -1, 0, 0};
constexpr std::array<int, 4> dy{0, 0, 1, -1};

std::vector dt(R, std::vector<int>(C, -1));

std::queue<std::pair<int, int>> q;
dt[startr][startc] = 0;
q.push({startr, startc});

while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    for (int k{}; k < 4; ++k) {
        int newr = r + dx[k];
        int newc = c + dy[k];

        if (newr < 0 || newr >= R || newc < 0 || newc >= C) continue;
        if (grid[newr][newc] == '#' || dt[newr][newc] != -1) continue;

        dt[newr][newc] = dt[r][c] + 1;
        q.push({newr, newc});
    }
}
```

---- connected **componenets** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<int> comp(n, -1);
int C{};

for (int i{}; i < n; ++i) {
    std::queue<int> q;

    comp[i] = 0;
    q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (comp[v] == -1) {
                comp[v] = comp[u];
                q.push(v);
            }
        }
    }
    ++C;
}
```

---- **bipartite** check ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<int> col(n, -1);
bool ok = true;

for (int i{}; i < n; ++i){
    if (ok == false) break;
    if (col[i] != -1) continue;

    std::queue<int> q;

    col[i] = 0;
    q.push(i);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (col[v] == -1 && ok) {
                col[v] = col[u] ^ 1;
                q.push(v);
            } else if (col[v] == col[u]) {
                ok = false; break;
            }
        }
    }
}
```

---- undirected **cycle detection** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<bool> vis(n, false);
bool cycle = false;

auto dfs = [&](this auto&& self, int u, int par) -> void {
    vis[u] = true;
    for (int v : adj[u]) {
        if (v == par) continue;

        if (vis[v]) {
            cycle = true;
        } else {
            self(v, u);
        }
    }
};

for (int i{}; i < n; ++i) {
    if (!vis[i]) {
        dfs(i, -1);
    }
}
```

---- directed **cycle detection** (Kahn's) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<int> in_degree(n, 0);
for (int u{}; u < n; ++u) {
    for (int v : adj[u]) {
        ++in_degree[v];
    }
}

std::queue<int> q;
for (int i{}; i < n; ++i) {
    if (in_degree[i] == 0) {
        q.push(i);
    }
}

std::vector<int> order;
order.reserve(n);

while (!q.empty()) {
    int u = q.front();
    q.pop();
    order.push_back(u);

    for (int v : adj[u]) {
        if (--in_degree[v] == 0) {
            q.push(v);
        }
    }
}

bool cycle = (order.size() != static_cast<size_t>(n));
```

---- **union find** (dsu) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
struct DSU {
    std::vector<int> par, sz;
    int comps;

    DSU(int n) : par(n), sz(n, 1), comps(n) {
        std::iota(par.begin(), par.end(), 0);
    }

    int find(int x) {
        return par[x] == x ? x : par[x] = find(par[x]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) std::swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        --comps;
        return true;
    }
};
```

---

## dp

---- **memo / tabulation** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// top-down (memo)
std::vector<ll> memo(n + 1, -1);
auto f = [&](this auto&& self, int i) -> ll {
    if (/* base case */) return /* base value */;
    ll& r = memo[i];
    if (r != -1) return r;
    return r = /* recurrence: self(...) */;
};
ll ans = f(n);

// bottom-up (tabulation)
std::vector<ll> dp(n + 1);
dp[0] = /* base */;
for (int i = 1; i <= n; ++i)
    dp[i] = /* recurrence: dp[i - 1], dp[i - 2], ... */;
// answer: dp[n]
```

---- **kadane** (max subarray sum) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
ll cur = a[0], best = a[0];
for (int i = 1; i < n; ++i) {
    cur = std::max(static_cast<ll>(a[i]), cur + a[i]);
    best = std::max(best, cur);
}
```

---- **house robber** (no adjacent) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
ll skip{}, take = a[0];
for (int i = 1; i < n; ++i) {
    ll nskip = std::max(skip, take);
    ll ntake = skip + a[i];
    skip = nskip;
    take = ntake;
}
ll best = std::max(skip, take);
```

---- **knapsack** (0/1 + unbounded + subset-sum) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// 0/1: each item once -- capacity loop DOWNWARD
std::vector<ll> dp(W + 1, 0);
for (auto [w, val] : items)
    for (int c = W; c >= w; --c)
        dp[c] = std::max(dp[c], dp[c - w] + val);

// unbounded: unlimited copies -- only the loop direction flips, UPWARD
for (auto [w, val] : items)
    for (int c = w; c <= W; ++c)
        dp[c] = std::max(dp[c], dp[c - w] + val);

// subset-sum feasibility (0/1, values irrelevant)
std::vector<bool> can(W + 1, false);
can[0] = true;
for (int w : wts)
    for (int c = W; c >= w; --c)
        can[c] = can[c] || can[c - w];
```

---- **knapsack** (bounded) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// item available k times -> binary-split into 0/1 bundles
std::vector<std::pair<int, ll>> flat;
for (auto [w, val, k] : items)
    for (int take = 1; k > 0; take *= 2) {
        int t = std::min(take, k);
        k -= t;
        flat.push_back({w * t, val * t});
    }
// then 0/1 knapsack over flat
```

---- **coin change** (min coins + counting ways) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// min coins (unbounded)
std::vector<int> dp(A + 1, INT_MAX / 2);
dp[0] = 0;
for (int x = 1; x <= A; ++x)
    for (int c : coins)
        if (c <= x)
            dp[x] = std::min(dp[x], dp[x - c] + 1);

// count ways, UNORDERED (combinations) -- coin OUTER
std::vector<ll> ways(A + 1, 0);
ways[0] = 1;
for (int c : coins)
    for (int x = c; x <= A; ++x)
        ways[x] = add(ways[x], ways[x - c]);

// count ways, ORDERED (sequences) -- amount OUTER
std::vector<ll> seq(A + 1, 0);
seq[0] = 1;
for (int x = 1; x <= A; ++x)
    for (int c : coins)
        if (c <= x)
            seq[x] = add(seq[x], seq[x - c]);
```

---- **LIS** (O(n^2) + O(n log n)) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// O(n^2): dp[i] = LIS length ending exactly at i
std::vector<int> dp(n, 1);
int best{};
for (int i{}; i < n; ++i) {
    for (int j{}; j < i; ++j)
        if (a[j] < a[i]) dp[i] = std::max(dp[i], dp[j] + 1);
    best = std::max(best, dp[i]);
}

// O(n log n): tail[k] = smallest possible last element of a length-(k+1) subsequence
std::vector<int> tail;
for (int x : a) {
    auto it = std::ranges::lower_bound(tail, x); // upper_bound -> non-decreasing
    if (it == tail.end()) tail.push_back(x);
    else *it = x;
}
best = tail.size(); // tail itself is NOT the actual subsequence
```

---- **LCS** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector dp(n + 1, std::vector<int>(m + 1, 0));
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
        dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : std::max(dp[i - 1][j], dp[i][j - 1]);
int best = dp[n][m];

// reconstruction: walk back from (n, m)
std::string res;
for (int i = n, j = m; i > 0 && j > 0;) {
    if (a[i - 1] == b[j - 1]) { res += a[i - 1]; --i; --j; }
    else if (dp[i - 1][j] >= dp[i][j - 1]) --i;
    else --j;
}
std::ranges::reverse(res);
```

---- [grid](#grids) 2D **dp** (path count, obstacles) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector dp(R, std::vector<ll>(C, 0));
dp[0][0] = grid[0][0] != '#';
for (int r{}; r < R; ++r)
    for (int c{}; c < C; ++c) {
        if (grid[r][c] == '#') { dp[r][c] = 0; continue; }
        if (r) dp[r][c] = add(dp[r][c], dp[r - 1][c]);
        if (c) dp[r][c] = add(dp[r][c], dp[r][c - 1]);
    }
```

---- 2D **prefix sums / diff** ---- [*[ dip ]*](#kots-cf-templates)

```cpp
// build: p[i][j] = sum of the i x j top-left subgrid (1-based padding)
std::vector p(n + 1, std::vector<ll>(m + 1, 0));
for (int i{}; i < n; ++i)
    for (int j{}; j < m; ++j)
        p[i + 1][j + 1] = a[i][j] + p[i][j + 1] + p[i + 1][j] - p[i][j];

// query: sum over rows [r1, r2) x cols [c1, c2)
ll s = p[r2][c2] - p[r1][c2] - p[r2][c1] + p[r1][c1];

// 2D difference: range add x on rows [r1, r2) x cols [c1, c2)
std::vector d(n + 1, std::vector<ll>(m + 1, 0));
d[r1][c1] += x; d[r1][c2] -= x;
d[r2][c1] -= x; d[r2][c2] += x;
// finalize: 2D prefix sum of d (as above) -- result is the grid
```

---- **range-sum dp** (prefix optimization) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
std::vector<ll> dp(n + 1), pref(n + 2);
dp[0] = 1;
pref[1] = 1;
for (int i = 1; i <= n; ++i) {
    int lo = std::max(0, i - k);
    dp[i] = sub(pref[i], pref[lo]);     // sum dp[lo..i-1] in O(1)
    pref[i + 1] = add(pref[i], dp[i]);
}
```

---

## grids

---- grid adjacency matrix build ---- [*[ dip ]*](#kots-cf-templates)
```cpp
auto id = [&](int r, int c) { return r * C + c; };

std::vector<std::vector<int>> adj(R * C);
for (int r{}; r < R; ++r)
    for (int c{}; c < C; ++c)
        for (auto [nr, nc] : nbrs(r, c))      // whichever variant below
            adj[id(r, c)].push_back(id(nr, nc));
```

##### neighbor function variants ([back to graphs](#graphs))

---- **bounded** ---- [*[ dip ]*](#kots-cf-templates)
```cpp
constexpr std::array<int, 4> dr{1, -1, 0, 0};
constexpr std::array<int, 4> dc{0, 0, 1, -1};
for (int k{}; k < 4; ++k) {

    int nr = r + dr[k], nc = c + dc[k];
    if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;

}
```

-- **toroidal** (wraparound) -- [*[ dip ]*](#kots-cf-templates)
```cpp
int nr = (r + dr[k] + R) % R;
int nc = (c + dc[k] + C) % C;
```

---- **cylinder** (different per axis) ---- [*[ dip ]*](#kots-cf-templates)
```cpp
int nr = (r + dr[k] + R) % R;      // wraps
int nc = c + dc[k];
if (nc < 0 || nc >= C) continue;   // bounded
```

---- **maze** (bounded, plus impassable cells) ---- [*[ dip ]*](#kots-cf-templates)
```cpp
int nr = r + dr[k], nc = c + dc[k];
if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
if (grid[nr][nc] == '#') continue;
```

---- **8-directional** — same mechanism, more offsets ---- [*[ dip ]*](#kots-cf-templates)
```cpp
constexpr std::array<int, 8> dr{1, -1, 0, 0, 1, 1, -1, -1};
constexpr std::array<int, 8> dc{0, 0, 1, -1, 1, -1, 1, -1};
```

---- **custom jumps** (knight moves, etc.) ---- [*[ dip ]*](#kots-cf-templates)
```cpp
constexpr std::array<int, 8> dr{1, 1, -1, -1, 2, 2, -2, -2};
constexpr std::array<int, 8> dc{2, -2, 2, -2, 1, -1, 1, -1};
```

---



