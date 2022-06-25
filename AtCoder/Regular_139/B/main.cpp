#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define int long long
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

signed main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, a, b, x, y, z;
		std::cin >> n >> a >> b >> z >> x >> y;
		bool flg1 = 1ll * a * z <= x;
		bool flg2 = 1ll * b * z <= y;
		if (flg1 && flg2) std::cout << 1ll * n * z << '\n';
		else if (flg1) std::cout << 1ll * (n / b) * y + 1ll * (n % b) * z << '\n';
		else if (flg2) std::cout << 1ll * (n / a) * x + 1ll * (n % a) * z << '\n';
		else {
			if (a < b) {
				std::swap(a, b);
				std::swap(x, y);
			}
			int o = n / a;
			if (1ll * x * b > 1ll * y * a) o %= b;
			i64 res = LLONG_MAX;
			for (int i = 0; i <= std::min(b, o); ++i) {
				int t1 = o - i;
				int t2 = (n - t1 * a) / b;
				res = std::min(res, 1ll * t1 * x + 1ll * t2 * y + 1ll * (n - t1 * a - t2 * b) * z);
			}
			std::cout << res << '\n';
		}
	}
	return 0;
}
