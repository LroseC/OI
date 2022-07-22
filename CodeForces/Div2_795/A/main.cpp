#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		int n;
		read >> n;
		vint a(n);
		vint cnt(2);
		for (int i = 0; i < n; ++i) {
			read >> a[i];
			++cnt[a[i] & 1];
		}
		printf("%d\n", std::min(cnt[0], cnt[1]));
	}
	return 0;
}
