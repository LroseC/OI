#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using i64 = long long;
using PII = std::pair<int, int>;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n;
		std::cin >> n;
		std::string s;
		std::cin >> s;
		int cnt = 0;
		int mid = n >> 1;
		for (int i = mid; i < n; ++i) {
			if (s[i] != s[mid]) break;
			++cnt;
		}
		for (int i = mid - 1; i >= 0; --i) {
			if (s[i] != s[mid]) break;
			++cnt;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
