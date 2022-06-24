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
		PII pos;
		int maxval = -1e9 - 10;
		for (int i = 0; i < n; ++i) {
			grid[i].resize(m);
			for (int j = 0; j < m; ++j) {
				std::cin >> grid[i][j];
				if (grid[i][j] > maxval) {
					maxval = grid[i][j];
					pos = std::make_pair(i, j);
				}
			}
		}
		int maxx = std::max(pos.first + 1, n - pos.first);
		int maxy = std::max(pos.second + 1, m - pos.second);
		printf("%d\n", maxx * maxy);
	}
	return 0;
}
