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
		int n, m;
		std::cin >> n >> m;
		std::vector<std::vector<int>> grid(n);
		std::vector<std::vector<PII>> f(n);
		for (int i = 0; i < n; ++i) {
			grid[i].resize(m);
			f[i].resize(m);
			for (int j = 0; j < m; ++j) {
				std::cin >> grid[i][j];
				f[i][j] = std::make_pair(0x3f3f3f3f, 0);
				if (i == 0 && j == 0)
					f[i][j] = std::make_pair(0, 0);
				if (i != 0) {
					f[i][j].first = std::min(f[i - 1][j].first, f[i][j].first);
					f[i][j].second = std::max(f[i - 1][j].second, f[i][j].second);
				}
				if (j != 0) {
					f[i][j].first = std::min(f[i][j - 1].first, f[i][j].first);
					f[i][j].second = std::max(f[i][j - 1].second, f[i][j].second);
				}
				f[i][j].first += grid[i][j] == 1;
				f[i][j].second += grid[i][j] == 1;
			}
		}
		if ((n + m) % 2 == 0)
			puts("NO");
		else {
			int x = (n + m - 1) / 2;
			if (f[n - 1][m - 1].first <= x && f[n - 1][m - 1].second >= x)
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
