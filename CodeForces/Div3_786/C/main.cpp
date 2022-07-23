#include <vector>
#include <cstring>
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
		static char str[2][100];
		read >> str[0] + 1;
		read >> str[1] + 1;
		i32 len0 = strlen(str[0] + 1);
		i32 len1 = strlen(str[1] + 1);
		if (len1 == 1 && str[1][1] == 'a') {
			puts("1");
			continue;
		}
		bool fail = 0;
		for (int i = 1; i <= len1; ++i)
			if (str[1][i] == 'a') fail = 1;
		if (fail) {
			puts("-1");
			continue;
		}
		printf("%lld\n", 1ll << len0);
	}
	return 0;
}
