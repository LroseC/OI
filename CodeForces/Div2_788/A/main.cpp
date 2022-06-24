#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<int> a(n), b(n);
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
			if (a[i] < 0) ++cnt;
		}
		for (int i = 0; i < cnt; ++i) {
			a[i] = -std::abs(a[i]);
		}
		for (int i = cnt; i < n; ++i) {
			a[i] = std::abs(a[i]);
		}
		bool flag = 1;
		for (int i = 0; i < n - 1; ++i) {
			if (a[i] > a[i + 1]) flag = 0;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
