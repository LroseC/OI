#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<int> a(n), b(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		int pos = -1;
		for (int i = 0; i < n; ++i) {
			std::cin >> b[i];
			if (b[i] != 0) pos = i;
		}
		if (pos == -1) {
			puts("YES");
			continue;
		}
		else {
			int decTime = a[pos] - b[pos];
			if (decTime < 0) {
				puts("NO");
				continue;
			}
			bool fail = 0;
			for (int i = 0; i < n; ++i) {
				a[i] = std::max(0, a[i] - decTime);
				if (a[i] != b[i]) fail = 1;
			}
			puts(fail ? "NO" : "YES");
		}
	}
	return 0;
}
