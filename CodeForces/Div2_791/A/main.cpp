#include <vector>
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
		i64 n; std::cin >> n;
		if (n & 1) {
			std::cout << "-1\n";
			continue;
		}
		n /= 2;
		if (n == 1) {
			std::cout << "-1\n";
			continue;
		}
		i64 max = n / 2;
		i64 min = n % 3 == 0 ? n / 3 : n / 3 + 1;
		std::cout << min << ' ' << max << '\n';
	}
	return 0;
}
