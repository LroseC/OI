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
const int N = 5005;

i32 n;
i32 a[N];
i64 b[N];

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	i64 ans = LLONG_MAX;
	for (int i = 1; i <= n; ++i) {
		i64 res = 0;
		b[i] = 0;
		for (int j = i + 1; j <= n; ++j) {
			i64 t = (b[j - 1] + 1) / a[j] + ((b[j - 1] + 1) % a[j] != 0);
			res += t;
			b[j] = t * a[j];
		}
		for (int j = i - 1; j >= 1; --j) {
			i64 t = (b[j + 1] + 1) / a[j] + ((b[j + 1] + 1) % a[j] != 0);
			res += t;
			b[j] = t * a[j];
		}
		ans = std::min(ans, res);
	}
	printf("%lld\n", ans);
	return 0;
}
