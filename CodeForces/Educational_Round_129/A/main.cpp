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
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		i32 n, m, a = INT_MIN, b = INT_MIN;
		read >> n;
		for (int i = 0; i < n; ++i) {
			i32 x; read >> x;
			a = std::max(a, x);
		}
		read >> m;
		for (i32 i = 0; i < m; i += 1) {
			i32 x; read >> x;
			b = std::max(b, x);
		}
		if (a == b) {
			puts("Alice\nBob");
		}
		else if (a < b) {
			puts("Bob\nBob");
		}
		else {
			puts("Alice\nAlice");
		}
	}
	return 0;
}
