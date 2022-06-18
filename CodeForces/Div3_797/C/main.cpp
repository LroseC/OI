#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		std::vector<int> s(n), ed(n), bg(n);
		std::queue<int> q;
		for (int i = 0; i < n; ++i) {
			std::cin >> s[i];
		}
		for (int i = 0; i < n; ++i) {
			std::cin >> ed[i];
		}
		bg[0] = s[0];
		for (int i = 1; i < n; ++i) {
			bg[i] = std::max(s[i], ed[i - 1]);
		}
		for (int i = 0; i < n; ++i) {
			std::cout << ed[i] - bg[i] << ' ';
		}
		std::cout << '\n';
	}
	return 0;
}
