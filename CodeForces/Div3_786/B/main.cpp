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
		static char str[10];
		read >> str + 1;
		i32 res = 0;
		res += (str[1] - 'a') * 25 + (str[2] - 'a') - (str[2] > str[1]) + 1;
		printf("%d\n", res);
	}
	return 0;
}
