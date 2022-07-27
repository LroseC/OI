#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	i32 tt; read >> tt;
	while (tt--) {
		static char str[10000];
		read >> str + 1;
		int len = strlen(str + 1);
		bool fail = 0;
		int cnt = 1;
		for (int i = 2; i <= len; ++i) {
			if (str[i] != str[i - 1]) {
				if (cnt < 2) {
					fail = 1;
				}
				cnt = 0;
			}
			++cnt;
		}
		if (cnt < 2) fail = 1;
		puts(fail ? "No" : "Yes");
	}
	return 0;
}
