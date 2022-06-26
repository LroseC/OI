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
	i64 a[3];
	std::cin >> a[0] >> a[1] >> a[2];
	i64 x = a[0] + a[1] + a[2];
	std::sort(a, a + 3);
	i64 res = 0;
	if (x & 1) {
		++res;
		for (int i = 0; i < 3; ++i)
			--a[i];
	}
	if (a[0] < 0) {
		puts("-1");
		return 0;
	}
	i64 k = (a[0] + a[1] - a[2]);
	if (k < 0) {
		puts("-1");
		return 0;
	}
	k = k / 2 * 2;
	res += k;
	for (int i = 0; i < 3; ++i)
		a[i] -= k;
	res += (a[0] + a[1] + a[2]) / 2;
	std::cout << res << '\n';
	return 0;
}
