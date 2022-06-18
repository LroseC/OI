#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

std::stack<int> num[1011];

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, K; std::cin >> n >> K;
		std::vector<int> a(n), del(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		auto cmp = [=](int a, int b) { return (a % K) < (b % K); };
		std::sort(a.begin(), a.end(), cmp);
		i64 res = 0;
		for (int i = 0, j = n - 1; i < j; ++i) {
			if (a[i] % K + a[j] % K >= K) {
				del[i] = del[j] = 1;
				res += (a[i] + a[j--]) / K;
			}
		}
		std::vector<int> tmp;
		for (int i = 0; i < n; ++i) {
			if (!del[i]) tmp.emplace_back(i);
		}
		for (int i = 0; i < tmp.size(); i += 2) {
			res += (a[tmp[i]] + a[tmp[i + 1]]) / K;
		}
		std::cout << res << '\n';
	}
	return 0;
}
