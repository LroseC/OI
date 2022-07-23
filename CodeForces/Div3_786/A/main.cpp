#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

int main(void)
{
	//Think twice, code once.;
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		i32 x, y; read >> x >> y;
		if (y % x != 0) puts("0 0");
		else {
			printf("1 %d\n", y / x);
		}
	}
	return 0;
}
