#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

vint res;
int cnt[3], tot;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int now = 0;
	res.emplace_back(0);
	while (res.back() < 1e9) {
		++tot;
		++cnt[now];
		res.emplace_back(res.back() + 2 * (tot - cnt[now]));
		++now;
		now = now == 3 ? 0 : now;
	}
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::cout << std::lower_bound(res.begin(), res.end(), n) - res.begin() << '\n';
	}
	return 0;
}
