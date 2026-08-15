#include <bits/stdc++.h>
using ll = long long;

constexpr ll MOD = 998244353;
constexpr int MX = 1000000;
std::vector<ll> fac(MX + 1), ifac(MX + 1);

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll bexp(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1)
            r = mul(r, b);
        b = mul(b, b);
        e >>= 1;
    }
    return r;
}

void pre() {
    fac[0] = 1;
    for (int i = 1; i <= MX; ++i)
        fac[i] = mul(fac[i - 1], i);

    ifac[MX] = bexp(fac[MX], MOD - 2);
    for (int i = MX; i > 0; --i)
        ifac[i - 1] = mul(ifac[i], i);
}

ll comb(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return mul(fac[n], mul(ifac[k], ifac[n - k]));
}

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int z = std::ranges::count(s, '0');
    int o = n - z;
    int r = 1;
    for (int i = 1; i < n; ++i)
        if (s[i] != s[i - 1])
            ++r;

    int r0{}, r1{};
    if (s[0] == '0') {
        r0 = (r + 1) / 2;
        r1 = r / 2;
    } else {
        r1 = (r + 1) / 2;
        r0 = r / 2;
    }

    ll wz = r0 == 0 ? z == 0 : comb(z - 1, r0 - 1);
    ll wo = r1 == 0 ? o == 0 : comb(o - 1, r1 - 1);

    std::cout << mul(wz, wo) << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    pre();
    int t = 1;
    std::cin >> t;
    while (t--)
        solve();
}
