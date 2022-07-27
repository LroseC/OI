#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

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
		i32 n, k; read >> n >> k;
		if (__builtin_popcount(k) > n / 4) {
			puts("-1");
			continue;
		}
		i32 lg = 0;
		for (i32 x = n; x; x >>= 1, lg += 1);
		int pos = 0;
		vi32 vis(n);
		for (i32 i = 0; i < lg; ++i)
			if (k >> i & 1) {
				while (vis[pos]) ++pos;
			}
	}
}
