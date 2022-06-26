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
		int n; std::cin >> n;
		vint a(n);
		int res = 0;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			if (a[i] != 0 && (i == 0 || a[i - 1] == 0)) ++res;
		}
		std::cout << std::min(res, 2) << '\n';
	}
	return 0;
}
