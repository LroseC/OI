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
		int n; std::cin >> n;
		vint a(n);
		for (int i = 0; i < n; ++i) std::cin >> a[i];
		if (n & 1) {
			std::cout << "NO\n";
			continue;
		}
		std::sort(a.begin(), a.end());
		vint b(n);
		for (int i = 0, j = n / 2; i < n / 2; ++i, ++j) {
			b[i * 2] = a[i];
			b[i * 2 + 1] = a[j];
		}
		bool fail = 0;
		for (int i = 0; i < n; ++i) {
			int last = (i - 1 + n) % n;
			int next = (i + 1) % n;
			if (b[i] > b[last] && !(b[i] > b[next])) {
				fail = 1;
			}
			if (b[i] < b[last] && !(b[i] < b[next])) {
				fail = 1;
			}
		}
		if (fail) {
			std::cout << "NO\n";
		}
		else {
			std::cout << "YES\n";
			for (int i = 0; i < n; ++i) std::cout << b[i] << ' ';
			std::cout << '\n';
		}
	}
	return 0;
}
