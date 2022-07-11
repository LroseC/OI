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
	int n, m, now;
	std::cin >> n >> m;
	vint a(n), tim(n);
	i64 sum = 0, tick = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		sum += a[i];
	}
	while (m--) {
		int t, pos, x;
		std::cin >> t;
		if (t == 1) {
			std::cin >> pos >> x;
			--pos;
			if (tim[pos] != tick) {
				a[pos] = now;
				tim[pos] = tick;
			}
			sum -= a[pos];
			a[pos] = x;
			sum += a[pos];
		}
		else {
			++tick;
			std::cin >> now;
			sum = 1ll * now * n;
		}
		std::cout << sum << '\n';
	}
	return 0;
}
