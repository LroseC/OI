#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		vint a(n), pos(n), fac(n + 1);
		fac[0] = 1;
		for (int i = 1; i <= n; ++i)
			fac[i] = 1ll * fac[i - 1] * i % mod;
		std::set<int> S, S2;
		int res = 1;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			pos[a[i]] = i;
		}
		for (int i = 0; i < n; ++i) {
			S.insert(i);
		}
		if (n == 1) {
			std::cout << 1 << '\n';
			continue;
		}
		int l = pos[0], r = pos[1];
		if (l > r) std::swap(l, r);
		int rest = r - l - 1;
		for (int i = l; i <= r; ++i) {
			S.erase(a[i]);
		}
		for (int i = l + 1; i < r; ++i)
			S2.insert(a[i]);
		while (S.size()) {
			int t = *S.begin();
			while (S2.size() && *S2.begin() < t) {
				S2.erase(S2.begin());
				res = 1ll * res * rest % mod;
				--rest;
			}
			S.erase(S.begin());
			t = pos[t];
			if (t < l) {
				for (int i = t + 1; i < l; ++i) {
					++rest;
					S.erase(a[i]);
					S2.insert(a[i]);
				}
				l = t;
			}
			else {
				for (int i = r + 1; i < t; ++i) {
					++rest;
					S.erase(a[i]);
					S2.insert(a[i]);
				}
				r = t;
			}
		}
		while (S2.size()) {
			S2.erase(S2.begin());
			res = 1ll * res * rest % mod;
			--rest;
		}
		std::cout << res << '\n';
	}
	return 0;
}
