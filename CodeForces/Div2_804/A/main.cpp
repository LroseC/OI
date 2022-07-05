#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

inline int lowbit(int x) { return x & -x; }

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		if (n & 1) {
			std::cout << "-1\n";
		}
		else {
			n /= 2;
			std::cout << lowbit(n) << ' ' << (n ^ lowbit(n)) << ' ' << (n ^ lowbit(n)) << '\n';
		}
	}
	return 0;
}
