#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int main(void)
{
	int tt; std::cin >> tt;
	while (tt--) {
		int n, m;
		std::cin >> n >> m;
		printf("%lld\n", (1ll + m) * m / 2 + (2ll * m + 1ll * m * n) * (n - 1) / 2);
	}
	return 0;
}
