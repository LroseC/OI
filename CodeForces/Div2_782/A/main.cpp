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
		int n, r, l;
		std::cin >> n >> r >> l;
		int x = r / (l + 1), y = r % (l + 1);
		for (int i = 0; i < l + 1; ++i) {
			for (int i = 0; i < x; ++i) putchar('R');
			if (y) {
				putchar('R');
				--y;
			}
			if (i != l) putchar('B');
		}
		putchar('\n');
	}
	return 0;
}
