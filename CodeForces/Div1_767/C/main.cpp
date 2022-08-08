#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 1010;

i32 n;
i32 grid[N][N];

void work(void)
{
	read >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			read >> grid[i][j];
	if (n % 4) {
		i32 res = 0;
		for (int x = 0; x < n; x += 4) {
			for (int y = 0; y < n; y += 4) {
				res ^= grid[x][y] ^ grid[x][y + 1] ^ grid[x + 1][y] ^ grid[x + 1][y + 1];
			}
		}
		printf("%d\n", res);
	}
	else {
		i32 res = 0;
		for (int x = 2; x < n; x += 4) {
			for (int y = 2; y < n; y += 4) {
				res ^= grid[x][y] ^ grid[x][y + 1] ^ grid[x + 1][y] ^ grid[x + 1][y + 1];
			}
		}
		printf("%d\n", res);
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
