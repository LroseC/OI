#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> grid(n);
	for (int i = 0; i < n; ++i) {
		grid[i].resize(n);
		int t = i * n;
		for (int j = 0; j < n; j += 2) {
			grid[i][j] = ++t;
		}
		for (int j = 1; j < n; j += 2) {
			grid[i][j] = ++t;
		}
		for (int j = 0; j < n; ++j)
			std::cout << grid[i][j] << ' ';
		std::cout << '\n';
	}
	return 0;
}
