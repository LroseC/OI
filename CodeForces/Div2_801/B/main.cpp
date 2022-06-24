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
		int n; std::cin >> n;
		std::vector<int> a(n);
		int min = 0x3f3f3f3f, pos = 0;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			if (a[i] < min) {
				min = a[i];
				pos = i;
			}
		}
		if (n % 2 == 0)
			puts(pos % 2 ? "Mike" : "Joe");
		else
			puts("Mike");
	}
	return 0;
}
