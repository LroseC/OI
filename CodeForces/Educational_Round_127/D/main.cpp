#include <cmath>
#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	i32 tt; read >> tt;
	while (tt--) {
		i32 n, x; read >> n >> x;
		vi32 a(n);
		i64 res = 0;
		i32 min = INT_MAX, max = INT_MIN;
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			if (i != 0)
				res += std::abs(a[i] - a[i - 1]);
			max = std::max(max, a[i]);
			min = std::min(min, a[i]);
		}
		i32 nmin = std::min(1, min);
		i32 nmax = std::max(x, max);
		res += std::min(2 * (nmax - max), std::min(std::abs(a[0] - nmax), std::abs(a[n - 1] - nmax)));
		res += std::min(2 * (min - nmin), std::min(std::abs(a[0] - nmin), std::abs(a[n - 1] - nmin)));
		printf("%lld\n", res);
	}
	return 0;
}
