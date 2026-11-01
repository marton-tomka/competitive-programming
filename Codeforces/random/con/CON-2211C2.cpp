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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    cin >> a >> b;

    vector<int> cnta(n + 1), fix(n + 1);
    for (int r{}; r < k; ++r) {
        bool cst = true;
        for (int j = r + k; j < n; j += k)
            if (a[j] != a[r]) {
                cst = false;
                break;
            }

        if (!cst) {
            for (int j = r; j < n; j += k)
                if (b[j] != -1 && b[j] != a[j]) {
                    no();
                    return;
                }
            continue;
        }

        int bv = -1;
        for (int j = r; j < n; j += k) {
            if (b[j] == -1)
                continue;
            if (bv != -1 && b[j] != bv) {
                no();
                return;
            }
            bv = b[j];
        }
        ++cnta[a[r]];
        if (bv != -1)
            ++fix[bv];
    }

    for (int v = 1; v <= n; ++v)
        if (fix[v] > cnta[v]) {
            no();
            return;
        }
    yes();
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
