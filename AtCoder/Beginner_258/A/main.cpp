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
	int n; std::cin >> n;
	int h = 21, m = 0;
	h += n / 60;
	m += n % 60;
	printf("%02d:%02d\n", h, m);
	return 0;
}
