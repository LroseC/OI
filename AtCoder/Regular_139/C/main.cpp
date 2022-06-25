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
	int n, m;
	std::cin >> n >> m;
	bool rev = 0;
	int r = n + 3 * m, R = m + 3 * n;
	if (r > R) {
		rev = 1;
		std::swap(r, R);
	}
	for (int i = r, j = 4; i >= 4; --i, ++j) {
	}
	return 0;
}
