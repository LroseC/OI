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
		int n, z; std::cin >> n >> z;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			int x; std::cin >> x;
			res = std::max(res, x | z);
		}
		std::cout << res << '\n';
	}
	return 0;
}
