#include <set>
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

i32 n;
char str[100];

void work(void)
{
	std::set<i32> S2, S3;
	read >> n;
	bool sec = 0;
	for (int i = 1; i <= n; ++i) {
		read >> str + 1;
		i32 len = strlen(str + 1);
		for (int i = 1; i <= len; ++i)
			str[i] -= 'a' - 1;
		if (len == 1) {
			sec = 1;
		}
		else {
			if (len == 2) {
				i32 hash = str[1] * 131 + str[2];
				S2.insert(hash);
			}
			else {
				i32 hash = str[1] * 131 * 131 + str[2] * 131 + str[3];
				S3.insert(hash);
				i32 hash2 = str[1] * 131 + str[2];
				S3.insert(hash2);
			}
			std::reverse(str + 1, str + 1 + len);
			if (len == 2) {
				i32 hash = str[1] * 131 + str[2];
				if (S2.count(hash) || S3.count(hash))
					sec = 1;
			}
			else {
				i32 hash = str[1] * 131 * 131 + str[2] * 131 + str[3];
				if (S3.count(hash))
					sec = 1;
				i32 hash2 = str[1] * 131 + str[2];
				if (S2.count(hash2))
					sec = 1;
			}
		}
	}
	puts(sec ? "Yes" : "No");
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
