#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

char str[N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n, m;
		std::cin >> n >> m >> str;
		for (int i = 0; i < n; ++i) {
			str[i] -= '0';
			str[i] ^= (m & 1);
		}
		vint cnt(n);
		for (int i = 0; i < n; ++i) {
			if (m && str[i] == 0) {
				--m;
				++cnt[i];
				str[i] ^= 1;
			}
		}
		if (m) {
			cnt[n - 1] += m;
			str[n - 1] ^= (m & 1);
		}
		for (int i = 0; i < n; ++i)
			std::cout << (char)(str[i] + '0');
		std::cout << '\n';
		for (int i = 0; i < n; ++i)
			std::cout << cnt[i] << ' ';
		std::cout << '\n';
	}
	return 0;
}
