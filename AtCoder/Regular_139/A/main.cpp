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
	int n; std::cin >> n;
	std::vector<i64> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	b[0] = 1ll << a[0];
	for (int i = 1; i < n; ++i) {
		b[i] = 1ll << a[i];
		b[i] |= (b[i - 1] >> (a[i] + 1) << (a[i] + 1));
		if (b[i] <= b[i - 1]) {
			b[i] += 1ll << (a[i] + 1);
		}
	}
	std::cout << b[n - 1] << '\n';
	return 0;
}
