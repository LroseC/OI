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
const int N = 2e5 + 10;

i32 n, lim;
i32 a[N];

void work(void)
{
	read >> n >> lim;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	std::sort(a + 1, a + 1 + n);
	i32 tot = 0;
	i32 cnt = 0;
	while (cnt + 1 <= n) {
		if (tot + a[cnt + 1] > lim) break;
		cnt += 1;
		tot += a[cnt];
	}
	i64 res = 0;
	for (int l = 0, r; cnt; cnt -= 1, l = r + 1) {
		r = (lim - tot) / cnt;
		res += (r - l + 1) * cnt;
		tot -= a[cnt];
	}
	printf("%lld\n", res);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
