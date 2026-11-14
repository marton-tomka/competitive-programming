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

void solve() { // ts is techy ngl
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> st;
    st.reserve(n);
    i64 ans{};
    int lb = -1;
    for (int j{}; j < n; ++j) {
        if (j && a[j] > a[j - 1] + 1)
            lb = j;
        while (!st.empty() && a[st.back()] >= a[j])
            st.pop_back();
        int p = st.empty() ? -1 : st.back();
        int L = lb <= p ? p : -1;
        ans += i64(j - L) * (n - j);
        st.push_back(j);
    }
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
