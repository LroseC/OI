#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		i32 n; read >> n;
		printf("%d ", n);
		for (int i = 1; i < n; i += 1)
			printf("%d ", i);
		puts("");
	}
	return 0;
}
