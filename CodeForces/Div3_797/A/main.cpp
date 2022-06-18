#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int tt;
	std::cin >> tt;
	while (tt--) {
		int n;
		std::cin >> n;
		/*
			x + (x - 1) + (x - 2) >= n
			<=> 3x - 3 >= n
			x >= (n + 3) / 3
		*/
		int x = ((n + 3) % 3 != 0) + (n + 3) / 3;
		int y = x - 1, z = y - 1;
		n = x + y + z - n;
		int tmp = std::min(n, z - 1);
		z -= tmp, n -= tmp;
		y -= n;
		std::cout << y << ' ' << x << ' ' << z << '\n';
	}
	return 0;
}
