#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, a, b;
		std::cin >> n >> a >> b;
		vint pos(n + 1);
		std::vector<i64> sum(n + 1);
		for (int i = 1; i <= n; ++i) {
			std::cin >> pos[i];
			sum[i] = sum[i - 1] + pos[i];
		}
		i64 ans = LLONG_MAX;
		for (int i = 0; i <= n; ++i) {
			i64 res = 0;
			res += 1ll * (a + b) * pos[i];
			res += 1ll * b * ((sum[n] - sum[i]) - 1ll * (n - i) * pos[i]);
			ans = std::min(ans, res);
		}
		std::cout << ans << '\n';
	}
	return 0;
}
