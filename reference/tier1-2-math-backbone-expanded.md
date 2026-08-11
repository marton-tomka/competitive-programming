# Tier 1 + Tier 2 — Expanded "Math Backbone" Sections

**What this is.** These are drop-in replacements for the sections of the study companion that fail the *"can I practice this standalone?"* test. Two pointers, monotonic stack/deque, DSU, BFS/DFS, sliding window — you can grind a themed problem set and the technique burns in. Modular arithmetic, inverses, `nCr`, stars-and-bars, Catalan, derangements, inclusion–exclusion, hashing — you can't. They live *inside* counting/geometry problems as complementary tooling, so with the original terse treatment they get memorized as formulas and evaporate.

Each section below keeps the original code and intuition and adds two things: **Where it lives** (recognition — how it actually surfaces, since you'll never see a problem literally titled "Modular Inverse"), and a **Worked example** — a short trace with real numbers you can redo by hand until the machinery feels inevitable rather than recalled. Do the traces on paper. That is the "implement from memory" step for material that has no clean problem set of its own.

Sections not here (§1.6, §1.7, §2.2–§2.10, etc.) are unchanged — use the original document for those.

---

## 1.15 Modular arithmetic

**Where it lives.** You never solve "a modular arithmetic problem." You solve a *counting* problem — "how many arrays / strings / configurations satisfy X" — whose true answer is astronomically large, and the statement ends with "output modulo `1e9+7`." That suffix is the entire trigger. It means: (1) the answer is a count, not a measurement, and (2) **every** `+`, `−`, `×` in your solution, from the first line to the last, happens mod `MOD`. You reduce continuously, not at the end — reducing at the end is impossible because the un-reduced value never fit in a machine integer in the first place.

```cpp
const ll MOD = 1'000'000'007;              // 998'244'353 in FFT-flavored problems
ll add(ll a, ll b) { a += b; return a >= MOD ? a - MOD : a; }
ll sub(ll a, ll b) { a -= b; return a < 0 ? a + MOD : a; }
ll mul(ll a, ll b) { return a * b % MOD; }  // safe if both already < MOD
```

**Intuition.** "Mod `m`" is arithmetic on a clock face with `m` positions. Addition, subtraction, and multiplication all commute with "take the remainder" — you may reduce before or after each of those operations and the result on the clock is identical. Division is the sole exception and does not exist here (that gap is what §2.21 fills). The whole discipline is: keep every stored value already reduced to `[0, MOD)`, and the three operations above keep it there.

> **Worked example — the sign trap, with numbers.** Take `m = 7` and compute `(2 − 5) mod 7`.
> The correct answer is `4`, because `2 − 5 = −3`, and `−3` on a 7-clock is `−3 + 7 = 4`.
> Now what C++ actually does: `(2 - 5) % 7` evaluates `-3 % 7`, and C++ truncates toward zero, giving **`-3`** — wrong, and worse, it's a *negative* value you'll later multiply into other things, poisoning everything downstream. `sub(2, 5)` fixes it: `a = -3`, which is `< 0`, so it returns `-3 + 7 = 4`. **Any subtraction mod `m` must pass through this correction.** This single bug — a subtraction that silently went negative — is the most frequent modular error, and it passes small samples because small subtractions often don't go negative.

> **Worked example — reduce-as-you-go, in a real formula.** Count arrays of length `n` with values in `[1, k]` where adjacent entries differ: the answer is `k · (k−1)^(n−1)`. Take `n = 3, k = 3`, so the true answer is `3 · 2² = 12`.
> In code with `MOD`: you can't write `pow`, you need binary exponentiation (§1.17) for `(k−1)^(n−1) mod MOD`, then `mul` it by `k`. Trace: `(k-1)^(n-1) = 2^2 = 4`; `mul(3, 4) = 12 % MOD = 12`. Small, so mod is invisible here — but now imagine `n = 10^9`: the exponent alone forces binary exponentiation, and every intermediate square is reduced. **The formula is exact arithmetic; the `% MOD` scattered through it is just keeping the numbers physically representable.**

- **The overflow guarantee.** If every value you store is already in `[0, MOD)`, then `a * b` in `mul` is at most `(10^9)² ≈ 10^18 < 9.2·10^18` (the `ll` ceiling), so `a * b % MOD` never overflows. Overflow appears *only* when you multiply two values you forgot to reduce first. Reduce religiously and `mul` is bulletproof.
- **Flag every division.** The moment your derivation has a fraction — a `/ 2`, a binomial coefficient, a probability `p/q` — mark it. "Divide by `a`" mod `m` means "multiply by `a⁻¹`" (§2.21), and you cannot proceed past that line until you've computed the inverse.

---

## 1.16 GCD and LCM

**Where it lives.** Rarely the whole problem; usually a one-liner inside something larger — "reduce a fraction," "will these two cyclic events ever coincide" (that's LCM), "the answer only depends on `gcd(a, b)`." The one structural fact worth carrying: **the gcd of a growing set of numbers only ever decreases or stays equal** — never increases as you fold in more elements. That monotonicity is occasionally the crux of a problem by itself.

```cpp
ll g = gcd(a, b);                     // <numeric>, C++17
ll l = a / gcd(a, b) * b;             // divide FIRST — a*b may overflow before /g
```

**Intuition.** Euclid in one sentence: any common divisor of `(a, b)` also divides `a mod b`, and conversely — so the pair `(b, a mod b)` has *exactly the same set of common divisors* as `(a, b)`, hence the same gcd. Replacing the pair with the smaller pair loses nothing and shrinks the numbers fast. Worst case is consecutive Fibonacci numbers (each step barely shrinks them), giving `O(log min(a, b))`.

> **Worked example.** `gcd(48, 18)`: `48 mod 18 = 12` → `gcd(18, 12)`; `18 mod 12 = 6` → `gcd(12, 6)`; `12 mod 6 = 0` → `gcd(6, 0) = 6`. Every pair in that chain — `(48,18), (18,12), (12,6), (6,0)` — shares the identical divisor set `{1,2,3,6}`. The chain stops the instant the remainder hits `0`, and the other number *is* the gcd. Then `lcm(48,18) = 48/6 · 18 = 8 · 18 = 144`. Note the order: `48 · 18 = 864` first would be fine here, but for inputs near `10^9` the product overflows `int`, so **always divide by the gcd before multiplying.**

- `gcd(x, 0) == x` is the fold identity, which lets you take the gcd of a whole array cleanly: start an accumulator at `0` and fold — `0` absorbs correctly on the first element.

---

## 1.17 Binary exponentiation

**Where it lives.** Anywhere you need `a^e` for a large `e` — most commonly `a^(MOD−2)` for a modular inverse via Fermat (§2.21), and later matrix powers for linear-recurrence DP. It is *the* engine underneath the inverse, so if this loop isn't automatic, half of §2.21 and §2.22 stall. Unlike the rest of this document it *is* directly practiceable (it's a self-contained algorithm), but a single trace cements why it's `O(log e)` and never lets you write it wrong again.

```cpp
ll power(ll b, ll e, ll mod) {
    ll r = 1; b %= mod;
    while (e > 0) {
        if (e & 1) r = r * b % mod;   // this binary digit of e is set
        b = b * b % mod;              // b^1 -> b^2 -> b^4 -> ...
        e >>= 1;
    }
    return r;
}
```

**Intuition.** Write the exponent in binary. `a^13 = a^(1101₂) = a^8 · a^4 · a^1` — you only need the *powers of two* of the base (`a¹, a², a⁴, a⁸, …`), each the square of the last, and you multiply into the answer exactly at the bits of `e` that are set. `log₂ e` squarings, hence `O(log e)`.

> **Worked example.** Compute `3^13 mod 100`. `13 = 1101₂`, so read the bits from the bottom while squaring `b`:
>
> | step | `e` | bit | action | `r` after | `b` after (mod 100) |
> |---|---|---|---|---|---|
> | 0 | 13 | 1 | `r = 1·3` | 3 | `3² = 9` |
> | 1 | 6 | 0 | — | 3 | `9² = 81` |
> | 2 | 3 | 1 | `r = 3·81 = 243 → 43` | 43 | `81² = 6561 → 61` |
> | 3 | 1 | 1 | `r = 43·61 = 2623 → 23` | 23 | (loop ends) |
>
> Result `23`. Check: `3^13 = 1 594 323`, and `1 594 323 mod 100 = 23`. ✓ Notice we did **4 iterations**, not 13 multiplications — that's the `log` in action, and it's the difference between feasible and hopeless when `e ≈ 10^18`.

- Memorize this exact loop. It reappears character-for-character for matrix exponentiation and any associative operation.

---

## 2.20 Extended Euclidean algorithm

**Where it lives.** Two situations. (1) You need `x, y` solving `a·x + b·y = c` — the "pay exactly `c` cents using coins worth `a` and `b`" flavor, or any linear Diophantine equation. (2) You need a modular inverse when the modulus is **not prime**, so Fermat is unavailable — extgcd is then the only route. Plain `gcd` tells you *whether* a solution exists; extgcd hands you the actual coefficients (the "certificate").

```cpp
// returns g = gcd(a, b) and fills x, y with a*x + b*y = g
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
```

**Intuition.** Plain Euclid shrinks `(a, b) → (b, a mod b)` and the gcd survives. Extended Euclid does the same descent but carries the coefficients back up on the return trip. Suppose the recursive call solved `b·x₁ + (a mod b)·y₁ = g`. Substitute the identity `a mod b = a − ⌊a/b⌋·b`, expand, and regroup by `a` and `b`: you get `a·y₁ + b·(x₁ − ⌊a/b⌋·y₁) = g`. Those two regrouped coefficients **are the two assignment lines** — the recursion is performing, one level at a time, the back-substitution you'd otherwise do by hand.

> **Worked example — coefficients bubbling up.** Solve `3·x + 11·y = 1` (equivalently: find `3⁻¹ mod 11`). The recursion descends `(3,11) → (11,3) → (3,2) → (2,1) → (1,0)`, hits the base `x=1, y=0`, and unwinds:
>
> | returning from | `(x₁, y₁)` received | `x = y₁` | `y = x₁ − ⌊a/b⌋·y₁` | check `a·x + b·y` |
> |---|---|---|---|---|
> | `(2, 1)` | `(1, 0)` | `0` | `1 − 2·0 = 1` | `2·0 + 1·1 = 1` ✓ |
> | `(3, 2)` | `(0, 1)` | `1` | `0 − 1·1 = −1` | `3·1 + 2·(−1) = 1` ✓ |
> | `(11, 3)` | `(1, −1)` | `−1` | `1 − 3·(−1) = 4` | `11·(−1) + 3·4 = 1` ✓ |
> | `(3, 11)` | `(−1, 4)` | `4` | `−1 − 0·4 = −1` | `3·4 + 11·(−1) = 1` ✓ |
>
> Final `x = 4`. And indeed `3·4 = 12 ≡ 1 (mod 11)`, so `3⁻¹ mod 11 = 4`. The value you want (the inverse) is the `x` coefficient, reduced into `[0, m)`. Redo this trace once and the two cryptic assignment lines stop being magic.

- **Solvability rule:** `a·x + b·y = c` has integer solutions **iff `g | c`** (where `g = gcd(a, b)`); if so, scale the found certificate by `c/g`.
- **All solutions:** `x = x₀ + (b/g)·t`, `y = y₀ − (a/g)·t` for any integer `t` — you shift "mass" between the two terms in the smallest step that keeps the sum fixed.

---

## 2.21 Modular inverse

**Where it lives.** The instant a mod-`p` computation contains a **division**: any formula with factorials or fractions, and the ubiquitous statement "*the answer is an irreducible fraction `p/q`; print `p · q⁻¹ mod 998244353`*." Division mod `m` = multiplication by the inverse. This is the section that makes §2.22 (`nCr`) possible, because a binomial coefficient is a fraction and you can't divide on the clock.

```cpp
// 1) prime modulus — Fermat: a^(MOD-2) is the inverse of a
ll inv(ll a) { return power(a, MOD - 2, MOD); }      // power from §1.17

// 2) any modulus with gcd(a, m) = 1 — extended Euclid:
ll inv_general(ll a, ll m) {
    ll x, y;
    extgcd(a, m, x, y);                               // a*x + m*y = 1 -> a*x ≡ 1 (mod m)
    return ((x % m) + m) % m;
}

// 3) all inverses 1..n in O(n) (handy for many divisions):
vector<ll> iv(n + 1); iv[1] = 1;
for (int i = 2; i <= n; i++) iv[i] = MOD - (MOD / i) * iv[MOD % i] % MOD;
```

**Intuition.** *Why Fermat works.* Multiplying the nonzero residues `{1, 2, …, p−1}` by a fixed `a` (with `p` prime, `a ≢ 0`) just **shuffles them** — it's a bijection, because `a·i ≡ a·j` would force `i ≡ j`, `a` having no factor of `p` to lose information through. Multiply the whole shuffled set together: you get the same product as the original set, but carrying an extra factor of `a^(p−1)`. Cancel the common product from both sides: `a^(p−1) ≡ 1`. Peel one factor off: `a · a^(p−2) ≡ 1` — so `a^(p−2)` **is** the inverse, computable by one binary exponentiation. The extGCD route is the more honest one about *existence*: `a·x + m·y = 1` is solvable iff `gcd(a, m) = 1`; read mod `m`, the `m·y` term vanishes and `x` is the inverse. No coprimality ⇒ no inverse, full stop.

> **Worked example — the shuffle, made concrete.** `p = 11`, `a = 3`. Multiply each of `{1,…,10}` by `3` mod `11`:
> `3, 6, 9, 1, 4, 7, 10, 2, 5, 8` — which is exactly `{1,…,10}` reordered. That reordering is the whole proof: it's why the product is preserved and the extra `3^(10)` must equal `1`.

> **Worked example — both routes agree.** Find `3⁻¹ mod 11`.
> *Fermat:* `3^(11−2) = 3^9`. Since `3^5 = 243 ≡ 1 (mod 11)`, `3^9 = 3^5 · 3^4 ≡ 1 · 81 ≡ 4`. So `3⁻¹ = 4`.
> *extGCD:* from §2.20's trace, `x = 4`.
> Both give **`4`**, and `3 · 4 = 12 ≡ 1`. ✓

> **Worked example — using it to divide.** Compute `C(5,2) mod 11`. As a fraction, `C(5,2) = 120 / 12 = 10`. On the clock you can't divide by `12`; you multiply by inverses. `120 ≡ 10`, `2⁻¹ ≡ 6` (since `2·6 = 12 ≡ 1`), `6⁻¹ ≡ 2`. So `C(5,2) ≡ 10 · 6 · 2 = 120 ≡ 10 (mod 11)`, matching the true `C(5,2) = 10`. **This is the mechanism every `nCr mod p` uses.**

- **Trap:** `0` has no inverse mod `p`. If a formula ever divides by something that could be a multiple of `p` (e.g. an input up to `10^18`), the clean formula breaks on exactly those inputs — handle them separately.
- **Never** call `inv` inside a hot loop (it's `O(log MOD)` each). Precompute anything that repeats — which is exactly what the next section does for factorials.

---

## 2.22 Factorials, inverse factorials, and nCr

**Where it lives.** Essentially every counting problem mod `p`. Anytime the answer involves "choose `k` of `n`," "arrange," "distribute," or "how many ways" — a binomial coefficient is lurking. You build three tables **once** at program start and then answer any `C(n, r)` in `O(1)`. It's pure infrastructure: unremarkable on its own, load-bearing for everything combinatorial.

```cpp
const int N = 1'000'006;                  // > max n you'll ever ask about
vector<ll> f(N), fi(N);
void build() {
    f[0] = 1;
    for (int i = 1; i < N; i++) f[i] = f[i-1] * i % MOD;
    fi[N-1] = power(f[N-1], MOD - 2, MOD);              // ONE inverse...
    for (int i = N - 1; i >= 1; i--) fi[i-1] = fi[i] * i % MOD;  // ...walked downward
}
ll C(ll n, ll r) {
    if (r < 0 || r > n) return 0;         // the guard that saves you in edge cases
    return f[n] * fi[r] % MOD * fi[n-r] % MOD;
}
```

**Intuition.** `C(n, r)` counts `r`-element choices from `n`. There are `n·(n−1)···(n−r+1)` *ordered* picks, but each unordered choice got counted `r!` times, so you divide the overcount away: `n! / (r!(n−r)!)`. On the clock, "divide" = "multiply by inverse factorials." The clever part is computing all the inverse factorials from **one** modular inverse: the identity `1/(i−1)! = i · (1/i!)` lets you seed `fi[N−1]` with a single expensive `power` call and then walk *downward*, each step one cheap multiply — `O(N)` total instead of `O(N log N)`.

> **Worked example — the downward walk.** Work mod a small prime `p = 13`, `N = 6`.
> Factorials: `f = [1, 1, 2, 6, 24≡11, 120≡3]` (i.e. `f[5] = 120 = 9·13 + 3 ≡ 3`).
> Seed the top inverse factorial: `fi[5] = f[5]⁻¹ = 3⁻¹ mod 13 = 9` (since `3·9 = 27 ≡ 1`).
> Now walk down with `fi[i-1] = fi[i] · i`:
> `fi[4] = fi[5]·5 = 9·5 = 45 ≡ 6`; `fi[3] = fi[4]·4 = 24 ≡ 11`; `fi[2] = fi[3]·3 = 33 ≡ 7`; `fi[1] = fi[2]·2 = 14 ≡ 1`; `fi[0] = fi[1]·1 = 1`.
> Sanity: `fi[i]` should be `f[i]⁻¹`. Check `fi[2] = 7` against `f[2] = 2`: `2·7 = 14 ≡ 1` ✓. One inverse computed, five derived.

> **Worked example — recognition.** "Number of monotone lattice paths from `(0,0)` to `(R,C)` moving only right/up" — a classic disguise. Every path is a sequence of `R+C` steps of which exactly `R` are "right," so the count is `C(R+C, R)`. For a `3×3` grid (`R=C=3`): `C(6, 3) = 20`. The problem never says "binomial coefficient"; you recognize it because the object is "an arrangement of two kinds of indistinct steps."

- **Make `C` return `0` out of range** rather than asserting — identities like Vandermonde run `r` over ranges where some terms are legitimately zero, and the guard makes those terms vanish cleanly.
- **Fallback:** if `n ≤ ~5000` or the modulus **isn't** prime (no inverses), use Pascal's rule `C(n,r) = C(n−1,r−1) + C(n−1,r)` — "the `n`-th item is in or out" — which needs only additions.

---

## 2.23 Stars and bars

**Where it lives.** "Number of ways to write `n` as an *ordered* sum of `k` non-negative integers," and its many costumes: "distribute `n` identical candies among `k` children," "count multisets of size `n` from `k` types," "non-decreasing sequences of length `k` with values in `[1, m]`." The tell is **identical items into distinct boxes** — the items are indistinguishable, the boxes are labeled. This is a formula that's near-impossible to keep straight by rote (which `−1` goes where?) but trivial to *reconstruct* once you've seen the picture once.

```cpp
// solutions of x1 + x2 + ... + xk = n, xi >= 0:   C(n + k - 1, k - 1)
// solutions with every xi >= 1:                   C(n - 1, k - 1)
// multisets of size n drawn from k types:          C(n + k - 1, n)   (same number)
ll ways     = C(n + k - 1, k - 1);
ll ways_pos = C(n - 1, k - 1);
```

**Intuition — the picture you never forget.** Draw the distribution as `n` **stars** in a row and `k−1` **bars** dropped between them, chopping the row into `k` segments; segment `i`'s star count is `xᵢ`. Every distribution draws exactly one such picture, and every picture decodes to exactly one distribution — a bijection. So instead of counting distributions, count pictures: you have `n + (k−1)` symbol slots total, and you choose which `k−1` of them hold bars → `C(n + k − 1, k − 1)`. That's the whole derivation, and it *builds* the formula rather than asking you to recall it.

> **Worked example — reconstruct the formula from the picture.** `x₁ + x₂ + x₃ = 5`, each `≥ 0`. Stars `= 5`, bars `= 2`, total slots `= 7`, choose `2` for bars: `C(7, 2) = 21`.
> Decode a few pictures to see the bijection is real: `★★|★|★★` → `(2,1,2)`; `||★★★★★` → `(0,0,5)`; `★★★★★||` → `(5,0,0)`. Each arrangement of the two bars among seven slots is one solution; there are `21` of them.

> **Worked example — a disguise + the ≥1 variant.** "How many ways to buy 5 fruits choosing from {apple, banana, cherry}?" This is `x_a + x_b + x_c = 5, xᵢ ≥ 0` = `C(7,2) = 21`, identical to above.
> Now "…with at least one of each fruit" (`xᵢ ≥ 1`): hand each variable one star up front (substitute `yᵢ = xᵢ − 1`), leaving `y₁ + y₂ + y₃ = 2` with `yᵢ ≥ 0` = `C(2 + 2, 2) = C(4,2) = 6`. The `≥1` formula `C(n−1, k−1) = C(4,2) = 6` is just this substitution baked in.

- **Upper bounds** (`xᵢ ≤ c`) have **no** one-shot formula — that's stars-and-bars *composed with* inclusion–exclusion (§2.26): subtract the distributions where some variable was overfed `c+1` in advance.
- Recognition drill: "non-decreasing sequences of length `k` with values in `[1, m]`" = multisets of size `k` from `m` types = `C(m + k − 1, k)`. Many problems reduce to "choose a multiset."

---

## 2.24 Catalan numbers

**Where it lives.** A specific menagerie of objects that all secretly count the same: balanced bracket sequences; up/down paths that never dip below zero; the "every prefix has ≥ as many opens as closes" condition; non-crossing chords/pairings; the number of binary trees; polygon triangulations. **The single strongest recognition tool is the sequence itself:** if you brute-force small cases (§0.3) and get `1, 1, 2, 5, 14, 42, 132, 429, …`, stop deriving — it's Catalan, and you're done.

```cpp
// Cat(n) = C(2n, n) / (n + 1) = C(2n, n) - C(2n, n + 1) = (2n)! / (n! (n+1)!)
ll cat(ll n) { return f[2*n] * fi[n] % MOD * fi[n+1] % MOD; }
```

**Intuition.** Anchor everything to one object: `n` correctly nested bracket pairs. Everything else is that object in costume — a `±1` path that never goes negative *is* a bracket sequence (`(` = `+1`, `)` = `−1`); a binary tree *is* a bracket sequence via "`(` left-subtree `)` right-subtree." The recurrence comes from the **first-return decomposition**: any nonempty balanced sequence is uniquely `(A)B`, where `A` is the balanced content inside the first bracket's matching partner and `B` is the balanced remainder — giving `Cat(n+1) = Σᵢ Cat(i)·Cat(n−i)`. The closed form `Cat(n) = C(2n, n) − C(2n, n+1)` reads as **good = all − bad**: of all `C(2n, n)` up/down paths, the "bad" ones that dip below zero correspond one-for-one (via the reflection principle, Tier 3) with arbitrary paths of a shifted step count, `C(2n, n+1)`.

> **Worked example — one object, count it by hand.** The balanced bracket sequences on `n = 3` pairs:
> `((()))`, `(()())`, `(())()`, `()(())`, `()()()` — that's **5**, and `Cat(3) = 5`. ✓
> Apply the first-return split to `(())()`: the first bracket closes at position 4, so `A = "()"` (inside) and `B = "()"` (after) — both balanced, as promised.

> **Worked example — same number, different costume.** Count full binary trees with `3` internal nodes (each internal node has exactly 2 children): there are also **5** of them. The "different objects, identical count" experience is the intuition — once you feel that brackets, trees, and non-crossing handshakes are one structure, you stop memorizing five separate facts.

- **Formula caution:** `C(2n, n+1)` needs `f`/`fi` built up to `2n`; and use the closed form `C(2n,n)/(n+1)` via a modular inverse of `(n+1)`, not integer division, when working mod `p`.

---

## 2.25 Derangements

**Where it lives.** "Permutations where **nothing** stays in its original place" — hats handed back so nobody gets their own, letters into wrong envelopes, secret-santa with no self-gifting. Written `!n`, sequence `1, 0, 1, 2, 9, 44, 265, …`. It's a named quantity you'll rarely derive under contest pressure, so internalize the *recurrence's story* — that's what survives.

```cpp
vector<ll> D(n + 1);
D[0] = 1; if (n >= 1) D[1] = 0;
for (int i = 2; i <= n; i++)
    D[i] = (i - 1) * ((D[i-1] + D[i-2]) % MOD) % MOD;
// closed form: !n = n! * Σ_{k=0..n} (-1)^k / k!  ≈  n!/e   (~36.8% of all permutations)
```

**Intuition — the two-case story.** Element `1` must land somewhere other than position `1` — say position `j`, and there are `(n−1)` choices for `j`. Now ask where element `j` goes. **Case A:** `j` goes to position `1` — the two swapped, and the remaining `n−2` elements just need their own derangement: `!(n−2)`. **Case B:** `j` does *not* go to position `1` — then `j` is an element forbidden from exactly one spot (position `1`), which is structurally identical to an ordinary element in a derangement of the remaining `n−1`: `!(n−1)`. Total: `!n = (n−1)·(!(n−1) + !(n−2))`.

> **Worked example — recurrence and sanity check.** `!4 = (4−1)·(!3 + !2) = 3·(2 + 1) = 9`.
> Cross-check against `n!/e`: `24 / e ≈ 24 / 2.718 ≈ 8.83 → 9` (the nearest integer, always). The `≈ n!/e` fact isn't decoration — it's a fast sanity check that your `!n` is in the right ballpark.

> **Worked example — recognition.** "4 people each draw a name for secret santa; how many assignments have nobody drawing themselves?" That's `!4 = 9`. The problem says nothing about "derangements"; you recognize it from "a permutation with **no fixed points**."

- The closed form is inclusion–exclusion (§2.26) verbatim: from all `n!` permutations, subtract those fixing at least one point; `C(n,k)·(n−k)!` permutations fix a chosen set of `k` points, and the alternating sum telescopes to `n!·Σ(−1)^k/k!`.

---

## 2.26 Inclusion–exclusion

**Where it lives.** "Count objects with **none** of these bad properties" (or "at least one"), where each bad property is easy to *force* but awkward to *forbid* — divisibility, containing a pattern, exceeding a cap. The move is complementary: `valid = total − |bad₁ ∪ bad₂ ∪ …|`, expanded with alternating signs. This is genuinely a *recognition* skill more than a coding one — the code is a loop over subsets; the hard part is seeing that a problem is "count things avoiding a small set of forbidden conditions."

```cpp
// |A1 ∪ A2 ∪ A3| = S1 - S2 + S3   (sizes of single / pairwise / triple intersections)
// general: count with NO property = Σ over subsets T of properties of (-1)^|T| · N(force all of T)

// example: how many x in [1, N] are divisible by NONE of the primes P[0..k)
ll ans = 0;
for (int m = 0; m < (1 << k); m++) {
    ll d = 1; bool skip = false;
    for (int i = 0; i < k; i++) if (m >> i & 1) {
        d *= P[i];
        if (d > N) { skip = true; break; }        // term contributes 0; also avoids overflow
    }
    if (skip) continue;
    ans += (popcount((unsigned)m) & 1 ? -1LL : 1LL) * (N / d);
}
```

**Intuition — why the alternating signs are exactly right.** Audit a single object that happens to have `t` of the bad properties. Across all `2^k` subset terms, it is counted only by subsets of the properties it *actually has*, each with sign `(−1)^|subset|` — total contribution `Σⱼ (−1)ʲ C(t, j) = (1 − 1)ᵗ`, which is `1` when `t = 0` and `0` when `t ≥ 1`. So the alternating sum is a **filter**: it keeps clean objects with weight exactly `1` and annihilates everything with at least one bad property. The "add singles, oops subtract pairs, oops add triples" Venn story is just this identity unrolled.

> **Worked example — count, then verify the intuition on one element.** How many integers in `[1, 30]` are divisible by **none** of `{2, 3, 5}`?
> Total `30`. Singles: `⌊30/2⌋ = 15`, `⌊30/3⌋ = 10`, `⌊30/5⌋ = 6`. Pairs: `⌊30/6⌋ = 5`, `⌊30/10⌋ = 3`, `⌊30/15⌋ = 2`. Triple: `⌊30/30⌋ = 1`.
> `ans = 30 − (15+10+6) + (5+3+2) − 1 = 30 − 31 + 10 − 1 = 8`.
> Verify: the integers in `[1,30]` coprime to `30` are `1, 7, 11, 13, 17, 19, 23, 29` — exactly **8** (this is `φ(30)`, tying IE to Euler's totient).
>
> Now audit **6** (which is divisible by `2` and `3`, so should be *excluded*): it's counted in `total` (`+1`), in `|÷2|` (`−1`), in `|÷3|` (`−1`), and in `|÷2,3|` (`+1`) — net `1 − 1 − 1 + 1 = 0`. Correctly killed. Audit **7** (divisible by none, should be *included*): counted only in `total` (`+1`), zero everywhere else — net `+1`. Correctly kept. *This per-element audit is the intuition made physical.*

- **Cost is `O(2^k · work)` over the *properties*, not the objects** — so IE wants *few* properties (`k ≤ ~20`) and tolerates arbitrarily many objects.
- **Workhorse combos at this level:** derangements (§2.25); stars-and-bars with upper bounds (§2.23); surjections ("every box non-empty"): `Σⱼ (−1)ʲ C(k,j)(k−j)ⁿ` — forbid `j` chosen boxes, then count freely.

---

## 2.27 Overflow awareness

**Where it lives.** Not a topic — a **pre-submit audit you run on every single problem**. It's here because you can't "practice overflow"; you can only build the reflex of asking, at design time, "what is the largest value each quantity can reach, and does it fit?" Limits to know cold: `int ≈ 2.1·10^9`, `long long ≈ 9.2·10^18`.

```cpp
int a = 1e9, b = 1e9;
ll bad  = a * b;                 // OVERFLOW: multiplied as int, THEN widened. UB.
ll good = (ll)a * b;             // widen first, then multiply
ll big  = 1LL << 40;             // 1 << 40 would be int UB (§1.3)

for (int i = 0; i + 1 < (int)v.size(); i++) ...  // v.size()-1 wraps to 2^64-1 when empty!
for (int i = 0; i + 1 < ssize(v); i++)  ...      // C++20: signed size, no trap

if ((__int128)a * b > (__int128)c * d) ...        // compute & compare huge products safely
```

**Intuition.** The trap isn't the *result* type — it's that the *operation* happens in the operands' type **before** any widening. `a * b` with two `int`s multiplies as `int` and overflows first; assigning the wreckage to a `ll` doesn't undo it. The fix is always to widen *one operand* before the operation: `(ll)a * b`. Signed overflow is **undefined behavior**, not wraparound — so it may pass samples and silently produce garbage on the judge; `-fsanitize=undefined` (§0.1) catches it locally.

> **Worked example — the audit in numbers.** `n = 2·10^5` values each up to `10^9`.
> A *sum* reaches `2·10^5 · 10^9 = 2·10^14` → fits in `ll` comfortably. Safe.
> A sum of *pairwise products* reaches `~(10^9)² · (number of pairs) ≈ 10^28` → fits in **nothing** native. That number is the problem *telling you* it must intend a modulus, or you've mis-designed and need to restructure. **Estimate the max magnitude of every quantity at design time**, and this whole class of "passes test 1, fails test 9" bugs disappears.

- Habit that prevents ~90% of these: any arithmetic that *could* exceed `int` range is carried in `ll` variables **end to end**. Mixed `int`/`ll` expressions are where the bugs breed.

---

## 2.30 Polynomial hashing

**Where it lives.** You need to compare substrings in `O(1)`, many times: "are these two ranges equal," "count positions where a pattern matches," "is this substring a palindrome" (compare it against its reverse's hash), "group equal strings." It's the all-purpose string tool *before* suffix structures enter your toolkit. The code is copyable, but the "read the string as a number" intuition is the sticky part — and it's what lets you derive the substring formula instead of memorizing the `h[r] − h[l]·B^(r−l)` incantation.

```cpp
struct Hash {
    static const ll M = 1'000'000'007;   // a large prime modulus
    ll B;                                 // RANDOM base — see pitfalls
    vector<ll> h, pw;                     // h[i] = hash of prefix s[0..i)
    Hash(const string& s) {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        B = uniform_int_distribution<ll>(300, M - 2)(rng);
        int n = s.size();
        h.assign(n + 1, 0); pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = (h[i] * B + s[i]) % M;
            pw[i + 1] = pw[i] * B % M;
        }
    }
    ll get(int l, int r) const {          // hash of s[l..r), O(1)
        return ((h[r] - h[l] * pw[r - l]) % M + M) % M;
    }
};
```

**Intuition.** Read the string as a **number written in base `B`**, one character per digit. The prefix hash grows by "shift left (×`B`), add next digit" — exactly how you'd read `4712` off its digits `4,7,1,2`. A substring's value is then extracted like the middle digits of a number: take the prefix ending at `r`, and subtract the prefix ending at `l` **shifted left by the substring's length** — `h[r] − h[l]·B^(r−l)`. Everything is mod `M` because the true numbers are astronomically long. Equal strings always hash equal; the price is that unequal strings collide with probability `≈ 1/M` per comparison.

> **Worked example — extract a substring by hand.** String `"aba"`, using values `a=1, b=2`, base `B=31`, modulus `M=101`.
> Prefix hashes: `h[1] = 0·31 + 1 = 1`; `h[2] = 1·31 + 2 = 33`; `h[3] = 33·31 + 1 = 1024 ≡ 14 (mod 101)`.
> Now pull out `"ba" = get(1, 3)`. Length `= 2`, so `pw[2] = 31² = 961 ≡ 52 (mod 101)`.
> `get(1,3) = (h[3] − h[1]·pw[2]) = (14 − 1·52) = −38 ≡ 63 (mod 101)`.
> Verify directly: `"ba"` in base `31` is `2·31 + 1 = 63`. ✓ **The formula is literally "chop off the high-order digits by subtracting the shifted prefix"** — trace it once and it stops being an incantation.

- **Randomize `B`.** On Codeforces, fixed published bases get hacked with crafted anti-tests; a random base per run blinds the adversary. Never use "mod `2^64` via unsigned overflow" with a fixed base — Thue–Morse strings break it deterministically.
- **Compare hashes only from the same `Hash` object** (same `B, M`). For two strings, build both with the *same* generated `B` — e.g. make `B` a global initialized once.
- **Equality of hashes is evidence, not proof.** Where a false positive is fatal and cheap to rule out, verify the candidate match directly, once.

---

## Using this supplement

The pattern that makes this material stick, per section: **read the "Where it lives" paragraph** (so you recognize the tool in disguise), **redo the worked example on paper** (so the machinery is reconstructed, not recalled), then **go find the tool inside a real problem** rather than looking for a problem "about" it. For the combinatorics sections especially (§2.23–§2.26), the fastest reinforcement is the brute-force check from §0.3: compute the first several values by hand or by a dumb loop, and confirm they match `1,1,2,5,14…` / `1,0,1,2,9…` / the stars-and-bars count. When your slow reference and the formula agree on small `n`, the identity is locked in — which is the closest thing this material has to a themed problem set.
