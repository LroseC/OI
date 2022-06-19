#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int dis[3][110];

int main(void)
{
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	int ans = -1, ans2 = 0x3f3f3f3f;
	for (int i = 3; i <= n; ++i) {
		std::cout << "? " << 1 << ' ' << i << std::endl;
		std::cin >> dis[1][i];
		std::cout << "? " << 2 << ' ' << i << std::endl;
		std::cin >> dis[2][i];
		ans = std::max(ans, abs(dis[1][i] - dis[2][i]));
		ans2 = std::min(ans2, dis[1][i] + dis[2][i]);
	}
	if (ans != ans2) {
		if (ans == 1 && ans2 == 3) {
			if (n != 4) {
				std::cout << "! 1" << std::endl;
				return 0;
			}
			int d1, d2;
			for (int i = 3; i <= n; ++i) {
				if (dis[1][i] == 1) d1 = i;
				if (dis[2][i] == 1) d2 = i;
			}
			std::cout << "? " << d1 << ' ' << d2 << std::endl;
			int ndis;
			std::cin >> ndis;
			if (ndis == 1) {
				std::cout << "! 3" << std::endl;
			}
			else {
				std::cout << "! 1" << std::endl;
			}
			return 0;
		}
		else {
			std::cout << "! " << ans2 << std::endl;
		}
		return 0;
	}
	std::cout << "! " << ans << std::endl;
	return 0;
}
