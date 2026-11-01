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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    auto ok = [&](int x) {
        int tot{}, runs{};
        bool neg = false;
        for (int i{}; i < n; ++i) {
            int v = (a[i] >= x) + (b[i] >= x) - 1;
            if (v == 1) {
                ++tot;
                neg = false;
            } else if (v == -1) {
                if (!neg)
                    ++runs;
                neg = true;
            }
        }
        return tot - runs >= 1;
    };

    int lo = 1, hi = 2 * n;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (ok(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    cout << lo << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
}
