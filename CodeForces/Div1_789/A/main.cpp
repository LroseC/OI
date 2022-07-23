#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 5005;

int n;
int a[N];
int presum[N][N], sufsum[N][N];

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			presum[i][j] = sufsum[i][j] = 0;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j)
			++presum[i][a[j]];
		for (int j = 1; j <= n; ++j)
			presum[i][j] += presum[i][j - 1];
		for (int j = n; j > i; --j)
			++sufsum[i][a[j]];
		for (int j = 1; j <= n; ++j)
			sufsum[i][j] += sufsum[i][j - 1];
	}
	i64 res = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			res += 1ll * presum[i][a[j]] * sufsum[j][a[i]];
		}
	printf("%lld\n", res);
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
