# CP input plumbing — C++ reference

All patterns use the structure from your B: `main` handles the test-case loop, `solve()` handles one test case and never reads `t`.

---

## Skeleton

```cpp
#include <bits/stdc++.h>
using ll = long long;

void solve() {
    // one test case only
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) solve();
}
```

Single-test problem: replace the two `t` lines with `int t = 1;`.

**The one rule:** `t` is read in exactly one place. Reading it in both `main` and `solve` is what happened in your A.

---

## The fact that removes most plumbing

`>>` skips **all** leading whitespace — spaces, tabs, newlines — then reads one token. It does not care about line structure.

So `n` integers spread over one line, `n` lines, or any mix all read identically. If the input has no spaces *inside* a value you care about, you never need `getline`.

---

## 1. `n`, then `n` integers

```cpp
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) std::cin >> x;
}
```

## 2. `n` pairs, one per line

```cpp
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::pair<ll, ll>> a(n);
    for (auto& [p, d] : a) std::cin >> p >> d;
}
```

## 3. One string per test case

```cpp
void solve() {
    std::string s;
    std::cin >> s;
}
```

## 4. `n` strings

```cpp
void solve() {
    int n;
    std::cin >> n;
    std::vector<std::string> v(n);
    for (auto& s : v) std::cin >> s;
}
```

## 5. Chars separated by spaces

```cpp
void solve() {
    int n;
    std::cin >> n;
    std::vector<char> c(n);
    for (char& x : c) std::cin >> x;
}
```

`>>` into a `char` reads exactly one non-whitespace character. So `a b c` and `abc` both produce `{'a','b','c'}` — identical code either way.

## 6. Char grid, no spaces

```cpp
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> g(n);
    for (auto& row : g) std::cin >> row;
    // g[i][j]
}
```

Each row is one whitespace-free token. `std::string` rows beat `vector<vector<char>>` — contiguous, and `g[i][j]` still works.

If `m` isn't given, read the rows and use `g[0].size()`.

## 7. Integer grid

```cpp
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector g(n, std::vector<int>(m));
    for (auto& row : g)
        for (int& x : row) std::cin >> x;
}
```

## 8. Full lines with meaningful spaces — the only real `getline` case

```cpp
void solve() {
    std::string line;
    std::getline(std::cin, line);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (t--) solve();
}
```

`cin >> t` stops at the newline and leaves it in the buffer. Without the `ignore`, the first `getline` returns an empty string.

Use `ignore(max, '\n')`, not bare `cin.ignore()` — the bare form discards exactly one character, so it breaks on `\r\n` line endings or a trailing space.

## 9. Mixed within one test case

```cpp
void solve() {
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string line;
    std::getline(std::cin, line);
}
```

Flush the newline every time you switch from `>>` to `getline`.

## 10. Read until EOF (no `t` given)

```cpp
int a, b;
while (std::cin >> a >> b) {
    // ...
}
```

Or line-based: `while (std::getline(std::cin, line))`.

---

## Output

```cpp
std::println("{}", x);
std::println("{} {}", a, b);
std::println("{}", ok ? "YES" : "NO");
std::println();                          // blank line
```

Vector on one line:

```cpp
for (int x : a) std::print("{} ", x);
std::println();
```

Trailing whitespace is accepted by every judge.

**Never use `std::endl`** — it flushes on every call. `'\n'` or `println` instead.

---

## Traps

**Reading `t` twice.** Once in `main`, once in `solve`. Pick one.

**`>>` then `getline` without flushing.** Empty string, silently.

**Global state not reset between test cases.** Global arrays, `visited[]`, accumulators, counters. Prefer local `vector`s sized to the actual `n` — resetting is automatic and it costs nothing.

**Allocating `MAXN` per test case.** Constraints say *sum of n over all test cases* ≤ 2·10⁵, so per-test allocation of size `n` is total O(2·10⁵). Allocating 2·10⁵ per test across 10⁴ tests is 2·10⁹ and TLEs.

**Overflow.** Check the largest value each variable can hold before choosing `int`. Your B: max final value ≈ 1.0002·10⁹ against `INT_MAX` ≈ 2.147·10⁹ — safe, but by one constraint change.

**`int` vs `.size()`.** `i < v.size()` compares signed to `size_t` and warns. Use `int` with a cached `int n = v.size();`, or `size_t` throughout.

**Mixing output streams.** `std::print`/`println` write to C `stdout`; `std::cout` with `sync_with_stdio(false)` has its own buffer. Mixing them can interleave out of order. Pick one and stay with it.

**Same for `printf`/`scanf` after `sync_with_stdio(false)`.** Don't mix with `cin`/`cout`.

**`<print>` availability.** Needs GCC 14+. Check your judge compiles it before relying on it in a round — have `cout << x << '\n'` as the fallback.
