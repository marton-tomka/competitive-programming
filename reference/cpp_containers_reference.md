# C++ Containers — Syntax, Internals & Gotchas

A reference for the containers you actually use in competitive programming: **how each one is built internally**, the **modern (C++17/20/23) syntax** for it, and the **traps** that cost contests. Everything here compiles on Codeforces' GCC toolchain.

A word on the layout of each section: the first paragraph is the internal model (what data structure, how it sits in memory, why the complexities are what they are), the code block is the syntax to memorize, and the bullets are the gotchas.

---

## Cross-cutting best practices

These apply to almost every container, so they're stated once here.

- **`emplace_*` vs `push_*`/`insert` — the honest version.** `push_back(obj)` takes an object you already have and copies or moves it in. `emplace_back(args...)` forwards *constructor arguments* and builds the element directly inside the container, skipping a temporary. So `v.emplace_back(a, b)` is better than `v.push_back({a, b})` (no temporary `pair` is built), but when you already hold an object, `push_back(x)` and `emplace_back(x)` do the same thing. Two caveats with emplace: it uses direct-initialization, so it can silently call `explicit` constructors and skip narrowing checks that `push_back` would catch. Practical rule for CP: **use `emplace_back`/`emplace` when constructing from arguments, `push_back` when you have a value** — and for `vector<int>` they're identical, so don't agonize.
- **`reserve(n)` when you know the final size.** Preallocates capacity and avoids repeated reallocation+copy. Cheap and almost always worth it for vectors and hash tables.
- **Range-based for + structured bindings + `auto`.** `for (auto& [k, v] : mp)` to iterate a map; `auto& x` to mutate in place, `auto x` (or `const auto&`) to read.
- **`contains` (C++20)** over `count(...) > 0` or `find(...) != end()` for membership tests — clearer and doesn't risk `operator[]` side effects.
- **`ssize(c)` (C++20)** returns a *signed* size. Prefer it in index arithmetic: `c.size() - 1` underflows to a huge number when `c` is empty, because `size()` is unsigned.
- **Transparent comparators:** write `greater<>` (empty angle brackets, C++14) rather than `greater<int>`.

---

## vector — the default container

**Internals.** A contiguous dynamic array: a single heap block holding the elements back-to-back, plus a size and a capacity. When you push past capacity it allocates a bigger block (libstdc++/GCC **doubles** it) and moves everything over, which is why `push_back` is *amortized* O(1) — the occasional O(n) copy is paid for by the many cheap pushes before it. Contiguity makes it the most cache-friendly container and lets you treat `&v[0]` as a plain array.

```cpp
vector<int> v;                       // empty
vector<int> v(n);                    // n value-initialized (zeros for int)
vector<int> v(n, x);                 // n copies of x
vector<int> v = {1, 2, 3};           // initializer list
vector<vector<int>> g(n);            // n empty rows -- adjacency list
vector dp(n, vector<ll>(m, 0));      // CTAD: 2D vector<vector<ll>>, C++17

v.push_back(x);                      // append a value you have
v.emplace_back(args...);             // construct in place from ctor args
v.pop_back();                        // remove last (returns void)
v.back(); v.front();                 // references to last / first
v[i];                                // unchecked element access
v.at(i);                             // bounds-checked (throws out_of_range)
v.size(); v.empty(); v.clear();
v.resize(k);  v.resize(k, x);        // grow/shrink (fill new slots with x)
v.assign(n, x);                      // replace contents with n copies of x
v.reserve(n);                        // preallocate capacity (no size change)
v.insert(v.begin() + i, x);          // O(n): shifts the tail
v.erase(v.begin() + i);              // O(n): shifts the tail
v.erase(v.begin() + l, v.begin() + r); // erase range [l, r)
sort(v.begin(), v.end());            // ranges::sort(v);
for (auto& x : v) x *= 2;            // mutate in place
```

**Gotchas.**
- **Reallocation invalidates everything.** Any pointer, reference, or iterator into a vector is dangling after a reallocation (a `push_back` that grows capacity). Never hold a reference across a push. `insert`/`erase` also invalidate iterators/references at and after the operation point.
- **`vector<bool>` is a special case** — it's bit-packed, so `v[i]` is a proxy object, not a real `bool&`. Fine for flags; if you need real references, use `vector<char>`.
- **`erase` of a single middle element is O(n).** To delete from the middle cheaply when order doesn't matter, swap with the last element and `pop_back()`.

---

## array — fixed-size, no heap

**Internals.** A thin wrapper over a C array whose size is a compile-time constant. It lives wherever you declare it (on the stack as a local), does **zero heap allocation**, and has no overhead over a raw array — but it knows its own size and works with STL algorithms.

```cpp
array<int, 5> a{};                   // all zeros (the {} matters -- a; alone is garbage)
array<int, 3> a = {1, 2, 3};
a[i]; a.at(i);
a.front(); a.back(); a.size();
a.fill(0);
sort(a.begin(), a.end());
auto [x, y, z] = a;                  // structured bindings work
```

**Gotchas.**
- `array<int, 5> a;` (no braces) leaves elements **uninitialized**; write `a{}` to zero them.
- The size is part of the type, so it can't change at runtime and two arrays of different sizes are different types.

---

## string — a char vector with two extras

**Internals.** Essentially a `vector<char>` with string operations bolted on, plus two important features. **Small String Optimization (SSO):** short strings (≤ ~15 chars in libstdc++) are stored *inside the string object itself* with no heap allocation. And it keeps a hidden null terminator so `c_str()` is free.

```cpp
string s = "hello";
s += 'c';  s += "abc";               // append char / string, amortized O(1)
s.push_back('x'); s.pop_back();
s.size(); s.empty();
s[i]; s.back();
s.substr(pos, len);                  // O(len), allocates a new string
s.find("ab");                        // first index, or string::npos if absent
s.contains("ell");                   // C++23
stoi(s); stoll(s); stod(s);          // parse
to_string(42);                       // format
sort(s.begin(), s.end());            // strings are just char ranges
```

**Gotchas.**
- **Building with `s = s + ch` in a loop is O(n²)** — each `+` copies the whole string. Always use `s += ch`, which appends in place (amortized O(1)).
- `find` returns `string::npos` (a huge unsigned value), **not** −1. Compare against `string::npos`.
- `s.size()` is unsigned — same underflow trap as vector.

---

## pair & tuple — aggregates you use constantly

**Internals.** Plain structs holding their members directly (a pair is two members, a tuple is N). No allocation, no overhead. Their key feature is **lexicographic comparison**: `<` compares the first element, then the second, and so on — which is why sorting a `vector<pair>` gives "sort by key, tie-break by value" for free.

```cpp
pair<int, string> p = {1, "a"};
pair p2{1, 2.5};                     // CTAD: pair<int, double>
p.first; p.second;
auto [x, y] = p;                     // structured bindings (unpack)
auto pr = make_pair(1, 2);

tuple<int, int, string> t{1, 2, "a"};
get<0>(t);                           // access by compile-time index
auto [a, b, c] = t;                  // unpack
tie(a, b, c) = t;                    // assign tuple into existing variables
tie(a, b) = pair{3, 4};              // works for pairs too
```

**Gotchas.**
- `get<i>(t)` needs a compile-time constant `i`; you can't index a tuple with a runtime variable.
- For more than 2–3 fields, a named `struct` is usually clearer than a tuple (you read `p.weight` instead of `get<2>(t)`).

---

## deque — double-ended queue

**Internals.** A segmented structure: a set of fixed-size blocks plus a "map" array of pointers to those blocks. This gives O(1) push/pop at **both** ends and O(1) random access (with one extra indirection to find the block). The price: elements are **not contiguous**, the constant factor is higher than vector, and per-element memory overhead is larger.

```cpp
deque<int> dq;
dq.push_back(x);  dq.push_front(x);
dq.emplace_back(args);  dq.emplace_front(args);
dq.pop_back();  dq.pop_front();
dq.front(); dq.back(); dq[i];
dq.size(); dq.empty();
```

**Gotchas.**
- **Not contiguous** — you can't pass `&dq[0]` as a buffer the way you can with vector, and the cache behavior is worse.
- `push_front`/`push_back` invalidate all *iterators*, but references and pointers to existing elements stay valid (unlike vector).
- The backbone of `0-1 BFS` and sliding-window-max in CP, but for a plain stack a vector is faster.

---

## stack — LIFO adapter

**Internals.** Not a container of its own — a thin **adapter** that wraps another container (default `deque`) and exposes only push/pop/top. It adds no data structure; it just restricts the interface.

```cpp
stack<int> st;                       // default: deque-backed
stack<int, vector<int>> st2;         // vector-backed -- usually faster in CP
st.push(x);  st.emplace(args);
st.pop();                            // removes top, returns void
st.top();                            // reference to top
st.size(); st.empty();
```

**Gotchas.**
- `pop()` returns **void**; read `top()` first, then `pop()`.
- Not iterable. If you need to scan the contents, use a `vector` directly as your stack (`push_back`/`back`/`pop_back`).

---

## queue — FIFO adapter

**Internals.** Same idea as stack: an adapter over `deque` (by default) exposing push at the back and pop at the front.

```cpp
queue<int> q;
q.push(x);  q.emplace(args);
q.pop();                             // removes front, returns void
q.front(); q.back();
q.size(); q.empty();
```

**Gotchas.**
- `pop()` returns void — read `front()` first.
- Not iterable. (In HFT this is exactly the container you'd swap for a ring buffer; in CP the deque-backed queue is fine.)

---

## priority_queue — a binary heap

**Internals.** An adapter over a `vector` maintained as a **binary heap** (via `make_heap`/`push_heap`/`pop_heap`): a complete tree, stored compactly in the array, where every parent outranks its children. That gives O(1) access to the top and O(log n) push/pop, because each operation only fixes one root-to-leaf path. **Max-heap by default.**

```cpp
priority_queue<int> pq;                                  // max on top
priority_queue<int, vector<int>, greater<>> minpq;       // min on top
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> dij; // Dijkstra: (dist, node)
pq.push(x);  pq.emplace(args);
pq.pop();                            // removes top, returns void
pq.top();                            // const reference to top
pq.size(); pq.empty();
```

**Gotchas.**
- **Default is a max-heap** — a frequent surprise. For a min-heap use `greater<>` and the full template, or push negated values.
- **Not iterable** and you can't peek at anything but the top, nor change an element's priority (no decrease-key — Dijkstra works around this by pushing duplicates and skipping stale ones).
- `top()` is read-only; `pop()` returns void.

---

## map & multimap — sorted, tree-based

**Internals.** A **red-black tree**: a self-balancing binary search tree, node-based (one heap allocation per element), keeping keys in sorted order. Every operation walks one root-to-leaf path, so insert/find/erase are O(log n). The trade-off versus a hash map is pointer chasing and per-node allocation, but you get ordered iteration and range queries for free.

```cpp
map<string, int> mp;
mp["key"] = 5;                       // inserts default (0) if absent, then assigns
mp.at("key");                        // bounds-checked: throws if absent
mp.count("key");                     // 0 or 1
mp.contains("key");                  // C++20 -- prefer for membership
mp.find("key");                      // iterator, or mp.end() if absent
mp.emplace("k", 1);                  // returns {iterator, inserted?}
mp.try_emplace("k", expensive());    // builds the value ONLY if key is absent
mp.insert_or_assign("k", 9);         // upsert: assign if present, insert if not
mp.erase("key");
for (auto& [k, v] : mp) ...          // iterates in sorted key order
mp.lower_bound("k");  mp.upper_bound("k");
mp.begin();  mp.rbegin();            // smallest key / largest key
```

**Gotchas.**
- **`operator[]` inserts a default value if the key is absent** — great for `cnt[x]++`, but it silently creates entries when you only meant to *read*. Query with `find`/`contains`/`at`, never `[]`.
- **`try_emplace` over `emplace` when the value is expensive to build** — `emplace` may construct the value and then throw it away if the key already exists; `try_emplace` doesn't construct it at all in that case.
- Iterators and references stay valid across inserts and erases of *other* elements (node-based). Only the erased element's iterator is invalidated.
- `multimap` allows duplicate keys; it has no `operator[]` (ambiguous), and you iterate equal keys via `equal_range(key)`.

---

## set & multiset — sorted, tree-based

**Internals.** The same red-black tree as `map`, but the element *is* the key. O(log n) everything, sorted iteration, and built-in `lower_bound`/`upper_bound`.

```cpp
set<int> s;
s.insert(x);                         // {iterator, inserted?}
s.emplace(args);
s.count(x);                          // 0 or 1
s.contains(x);                       // C++20
s.find(x);
s.erase(x);
s.lower_bound(x);  s.upper_bound(x); // use MEMBER versions on a set
*s.begin();  *s.rbegin();            // min / max
s.erase(s.begin());                  // erase the smallest

multiset<int> ms;                    // allows duplicates
ms.insert(x);
ms.count(x);                         // can be > 1; O(log n + occurrences)
ms.erase(x);                         // erases ALL copies of x
ms.erase(ms.find(x));                // erases ONE copy
```

**Gotchas.**
- **On a `set`, call the *member* `s.lower_bound(x)`, not `std::lower_bound(s.begin(), s.end(), x)`.** The free function is O(n) on a tree because it can't jump; the member is O(log n).
- **`multiset::erase(value)` removes every copy.** To remove a single copy, erase the iterator: `ms.erase(ms.find(value))`.
- You **cannot modify an element in place** (it would break the ordering invariant). Erase and re-insert instead.
- The comparator must be a strict weak ordering (strict `<`, never `<=`); a non-strict comparator is undefined behavior, exactly as with `sort`.

---

## unordered_map & unordered_set — hash tables

**Internals.** A hash table with **separate chaining**: keys are bucketed by hash value, and each bucket is a linked list of nodes. The standard *mandates* this node-based design (it guarantees reference stability and a bucket interface), which is why it's cache-unfriendly. Average O(1) for insert/find/erase; **worst case O(n)** when many keys land in the same bucket. When the load factor is exceeded it rehashes into more buckets.

```cpp
// the default integer hash is hackable on Codeforces -- supply a custom hash:
struct chash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t R = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + R);         // time-seeded -> adversary can't precompute collisions
  }
};

unordered_map<ll, int, chash> um;
um[k]++;                              // same insert-if-absent behavior as map
um.at(k); um.count(k); um.contains(k); um.find(k);
um.reserve(n);                        // preallocate buckets -> avoids rehashing
um.max_load_factor(0.25);            // trade memory for speed

unordered_set<int, chash> us;
us.insert(x); us.contains(x);
```

**Gotchas.**
- **The default hash for integer keys is public and gets anti-hashed on Codeforces** — crafted tests collide every key and turn O(1) into O(n) → TLE. Always plug in the `chash` above, or use `gp_hash_table` (below), or `map`.
- Iteration order is **unspecified** and can differ between runs.
- A rehash invalidates iterators (but not references/pointers to elements). `reserve(n)` up front avoids mid-run rehashing entirely.
- `operator[]` inserts on access, same as `map`.

---

## bitset — packed fixed-size bits

**Internals.** A compile-time-sized array of bits packed into machine words (64 bits each). Operations run in O(N / 64), so it's the standard way to get a 64× constant-factor speedup on boolean DP and set operations (the "O(n²/64)" trick).

```cpp
bitset<1000> b;                      // size N fixed at compile time, all zero
b.set();        b.set(i);            // all bits / bit i to 1
b.reset();      b.reset(i);          // to 0
b.flip();       b.flip(i);           // toggle
b.test(i);      b[i];                // read bit i
b.count();                           // number of set bits (popcount)
b.any(); b.none(); b.all();
b <<= k;  b >>= k;                   // whole-bitset shifts
auto c = b & d;  b | d;  b ^ d;      // bitwise set ops
b._Find_first();                     // GCC ext: index of lowest set bit (N if none)
b._Find_next(i);                     // GCC ext: next set bit after i
```

**Gotchas.**
- **N must be a compile-time constant.** If the size is only known at runtime, use `vector<bool>` (also bit-packed, but no whole-word bitwise ops) or `boost`-style dynamic bitsets (not available on CF).
- `_Find_first` / `_Find_next` are GCC extensions — handy on Codeforces, but not portable to other compilers.

---

## list — doubly-linked (rarely needed)

**Internals.** A doubly-linked list: each element is its own heap-allocated node with prev/next pointers. O(1) insert/erase/splice *given an iterator*, but no random access (O(n) to reach the k-th element) and heavy pointer chasing that wrecks cache performance.

```cpp
list<int> l;
l.push_back(x);  l.push_front(x);
l.pop_back();    l.pop_front();
l.splice(pos, other);                // O(1): move elements between lists
l.erase(it);                         // O(1) given the iterator
```

**Gotchas.**
- In CP you almost never need this — a `vector` or `deque` is faster for nearly every use. Reach for `list` only when O(1) splicing of nodes by iterator is genuinely the operation you need.

---

## GCC policy-based structures (`__gnu_pbds`)

These ship **with GCC's libstdc++**, so they work on Codeforces with no external library — exactly the gap you'd otherwise want absl for.

### gp_hash_table — fast hash map

**Internals.** An **open-addressing** hash table (probing): keys live in one contiguous array and collisions are resolved by probing nearby slots, so there's no per-node allocation and far less pointer chasing than `unordered_map`. Noticeably faster in practice; the trade-off is no reference stability across rehashes.

```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

gp_hash_table<ll, int, chash> mp;    // reuse the chash from above
mp[k] = v;  mp[k]++;
mp.find(k);                          // iterator or mp.end()
```

**Gotchas.**
- Still pair it with a custom hash (`chash`) — the default is hackable just like `unordered_map`.
- Fewer guarantees than `unordered_map`; treat it as a fast drop-in for the common `[]`/`find` use, not for anything relying on iterator/reference stability.

### tree (ordered set) — set with order statistics

**Internals.** A red-black tree (same as `set`) augmented so each node stores its subtree size. That extra bookkeeping adds two O(log n) queries that `set` lacks: the rank of a key, and the k-th smallest element.

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;

ordered_set<int> os;
os.insert(x);
os.erase(x);
os.order_of_key(x);                  // number of elements strictly less than x
*os.find_by_order(k);                // the k-th smallest element (0-indexed)
```

**Gotchas.**
- This is a *set*, so duplicates are rejected. For a multiset-with-order-statistics, people use `less_equal<T>` instead of `less<T>` — but then `erase(value)` and `find(value)` misbehave, so insert `pair<value, uniqueId>` into an `ordered_set` of pairs instead. That's the clean, bug-free way.

---

## Complexity cheat sheet

| Container | Internal structure | Access | Insert | Erase | Find | Ordered? | Contiguous? |
|---|---|---|---|---|---|---|---|
| `vector` | dynamic array | O(1) random | back amortized O(1); middle O(n) | back O(1); middle O(n) | O(n); O(log n) if sorted | insertion order | **yes** |
| `array` | fixed array | O(1) random | — (fixed size) | — | O(n) | no | **yes** |
| `deque` | block map | O(1) random | ends O(1); middle O(n) | ends O(1); middle O(n) | O(n) | no | no |
| `list` | doubly-linked | O(n) | O(1) at iterator | O(1) at iterator | O(n) | no | no |
| `stack` | adapter (deque) | top O(1) | O(1) | O(1) | — | LIFO | — |
| `queue` | adapter (deque) | front/back O(1) | O(1) | O(1) | — | FIFO | — |
| `priority_queue` | binary heap (vector) | top O(1) | O(log n) | O(log n) | — | by priority | — |
| `map` / `set` | red-black tree | — | O(log n) | O(log n) | O(log n) | **sorted** | no |
| `unordered_map` / `set` | hash table (chaining) | — | avg O(1), worst O(n) | avg O(1), worst O(n) | avg O(1), worst O(n) | no | no |
| `bitset` | packed bits | O(1) | set-bit O(1) | — | — | by index | **yes** |
| `gp_hash_table` | open-addressing hash | — | avg O(1) | avg O(1) | avg O(1) | no | flat |
| pbds `tree` | augmented RB-tree | — | O(log n) | O(log n) | O(log n) (+ rank/select O(log n)) | **sorted** | no |

---

*Defaults worth internalizing: `vector` unless you have a reason otherwise; `map`/`set` when you need order or want to avoid hash hacking; `gp_hash_table` + custom hash when you need hash-map speed; `priority_queue` for greedy/Dijkstra; `bitset` for the 64× boolean-DP speedup; pbds `tree` for order statistics.*
