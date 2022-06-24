#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline int sq(int x) { return 1ll * x * x % mod; }

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int a, d1, K1;
		std::cin >> a >> d1 >> K1;
		int b, d2, K2;
		std::cin >> b >> d2 >> K2;
		if (d2 % d1 || (b - a) % d1) {
			puts("0");
			continue;
		}
		if (b < a || b + 1ll * d2 * (K2 - 1) > a + 1ll * d1 * (K1 - 1)) {
			puts("0");
			continue;
		}
		if (b - K2 < a) {
			puts("-1");
			continue;
		}
		if (b + 1ll * d2 * K2 > a + 1ll * d1 * (K1 - 1)) {
			puts("-1");
			continue;
		}
		int res = 0;
		for (int o = 1; o * o <= d1; ++o)
			if (d1 % o == 0) {
				int t = o;
				int d = d2 / d1 * t;
				if (std::__gcd(d, d1) == t)
					res = Mod(res + sq(d2 / d));
				if (o * o != d1) {
					int t = d1 / o;
					int d = d2 / d1 * t;
					if (std::__gcd(d, d1) == t)
						res = Mod(res + sq(d2 / d));
				}
			}
		printf("%d\n", res);
	}
	return 0;
}
