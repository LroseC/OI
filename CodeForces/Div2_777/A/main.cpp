#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; read >> tt;
	while (tt--) {
		int n; read >> n;
		if (n % 3 == 1) {
			for (int i = 0; i < n / 3; ++i)
				std::cout << "12";
			std::cout << "1\n";
		}
		else {
			for (int i = 0; i < n / 3; ++i)
				std::cout << "21";
			if (n % 3) std::cout << "2";
			std::cout << '\n';
		}
	}
	return 0;
}
