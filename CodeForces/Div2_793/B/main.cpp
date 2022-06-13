#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <algorithm>

using i64 = long long;
using uint = unsigned int;
using PII = std::pair<int, int>;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<uint> a(n), b(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			b[i] = a[i];
		}
		std::sort(b.begin(), b.end());
		uint res = UINT_MAX;
		for (int i = 0; i < n; ++i)
			if (a[i] != b[i]) res &= a[i];
		printf("%u\n", res);
	}
	return 0;
}
