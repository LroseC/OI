#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 105;

int n, m;
char grid[N][N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		read >> n >> m;
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			read >> grid[i] + 1;
			for (int j = 1; j <= m; ++j) {
				grid[i][j] -= '0';
				res += grid[i][j];
			}
		}
		if (grid[1][1] == 1) {
			puts("-1");
			continue;
		}
		printf("%d\n", res);
		for (int i = n; i > 1; --i) {
			for (int j = 1; j <= m; ++j)
				if (grid[i][j])
					printf("%d %d %d %d\n", i - 1, j, i, j);
		}
		for (int j = m; j > 1; --j)
			if (grid[1][j])
				printf("%d %d %d %d\n", 1, j - 1, 1, j);
	}
	return 0;
}
