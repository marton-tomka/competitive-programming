# kots CF templates

[-- SKELETON](#skeleton)
[-- MODULAR ARITHMETIC](#mod)
[-- BASICS](#basics)
[-- GRAPHS](#graphs)
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
    std::cin >> t; // comment out if single test
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

---- **binary search** (predicate template) ---- [*[ dip ]*](#kots-cf-templates)

```cpp
int lo{}, hi = n;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (pred(mid)) hi = mid;
    else lo = mid + 1;
}
// lo == hi == first index where pred holds
```

---- **two pointers** (sorted pair sum) ---- [*[ dip ]*](#kots-cf-templates)

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

---- **sliding window** (longest subarray, sum <= k) ---- [*[ dip ]*](#kots-cf-templates)

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

// sum of v[l..r) : pref[r] - prefl]
```

---- 1D **difference array** (range update) ---- [*[ dip ]*](#kots-cf-templates)

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



