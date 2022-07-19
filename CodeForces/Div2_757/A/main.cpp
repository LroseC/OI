#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		int n, l, r, k;
		read >> n >> l >> r >> k;
		vint v;
		for (int i = 0; i < n; ++i) {
			int x;
			read >> x;
			if (l <= x && x <= r) v.emplace_back(x);
		}
		std::sort(v.begin(), v.end());
		int res = 0;
		for (auto t : v) {
			if (t <= k) {
				++res;
				k -= t;
			}
		}
		std::cout << res << '\n';
	}
	return 0;
}
