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
	int tt; std::cin >> tt;
	while (tt--) {
		std::string s;
		std::cin >> s;
		if (s.size() % 2 == 0) {
			int res = 0;
			for (char c : s) {
				res += c - 'a' + 1;
			}
			std::cout << "Alice " << res << '\n';
		}
		else {
			int del = 0;
			for (char c : s) {
				del += c - 'a' + 1;
			}
			del = del - 2 * (std::min(s.back(), *s.begin()) - 'a' + 1);
			std::cout << (del < 0 ? "Bob" : "Alice") << ' ' << std::abs(del) << '\n';
		}
	}
	return 0;
}
