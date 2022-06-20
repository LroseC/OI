#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<i64> a(n), b(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		b[0] = a[0];
		for (int i = 1; i < n; ++i) {
			b[i] = a[i] - a[i - 1];
		}
		i64 res = 0;
		for (int i = 1; i < n; ++i) {
			if (b[i] < 0) {
				b[0] -= std::abs(b[i]);
				res += std::abs(b[i]);
			}
			else {
				res += std::abs(b[i]);
			}
		}
		res += std::abs(b[0]);
		std::cout << res << '\n';
	}
	return 0;
}
