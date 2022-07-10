#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;


int main(void)
{
	std::ios::sync_with_stdio(false);
	int n; std::cin >> n;
	vint v(n + 1);
	std::vector<i64> sum(n + 1);
	for (int i = 1; i <= n; ++i) {
		std::cin >> v[i];
	}
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + v[i];
	}
	std::vector<i64> time(n);
	i64 x = 0;
	for (int i = 1; i <= n; ++i) {
		x = std::max(x, sum[i] % i == 0 ? sum[i] / i : sum[i] / i + 1);
		time[i - 1] = std::max(x, sum[n] % i == 0 ? sum[n] / i : sum[n] / i + 1);
	}
	int m; std::cin >> m;
	while (m--) {
		int t; std::cin >> t;
		int res = std::lower_bound(time.begin(), time.end(), t, std::greater<i64>()) - time.begin() + 1;
		std::cout << (res == time.size() + 1 ? -1 : res) << '\n';
	}
	return 0;
}
