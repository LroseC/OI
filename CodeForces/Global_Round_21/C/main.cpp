#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, i64>;

std::vector<PII> getDiv(vint &v, int m)
{
	std::vector<std::pair<int, i64>> res;
	for (auto x : v) {
		i64 cnt = 1;
		while (x % m == 0) {
			cnt *= m;
			x /= m;
		}
		if (!res.size() || x != res.back().first)
			res.emplace_back(x, cnt);
		else {
			res[res.size() - 1].second += cnt;
		}
	}
	return res;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, m;
		std::cin >> n >> m;
		vint a(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		std::cin >> n;
		vint b(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> b[i];
		}
		puts(getDiv(a, m) == getDiv(b, m) ? "Yes" : "No");
	}
	return 0;
}
