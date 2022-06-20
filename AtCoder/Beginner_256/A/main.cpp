#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

int main(void)
{
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	std::cout << (1 << n) << '\n';
	return 0;
}
