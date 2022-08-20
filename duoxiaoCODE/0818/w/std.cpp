#include <cctype>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;
const int N = 1e6 + 10;

i32 n, m;
i32 a[N], f[2][N];

int main(void)
{
#ifndef DEBUG
	freopen("w.in", "r", stdin);
	freopen("w.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	std::memset(f, 0x3f, sizeof f);
	for (int i = n; i >= 1; --i) {
		for (int j = 0; j < m / i; ++j) f[i & 1][j] = 0x3f3f3f3f;
		f[i & 1][a[i]] = std::min(i64(f[i & 1][a[i]]), i * 2 + i64(a[i]) * i);
		for (int j = m / i; j >= a[i]; --j) {
			f[i & 1][j] = std::min(f[i & 1][j], f[i + 1 & 1][j]);
			f[i & 1][j] = std::min(f[i & 1][j], f[i + 1 & 1][j - a[i]] + a[i] * i);
		}
		for (int j = std::min(m / i, a[i] - 1); j >= 0; --j) {
			f[i & 1][j] = std::min(f[i & 1][j], f[i + 1 & 1][j]);
		}
	}
	for (int i = m; i >= 0; --i) {
		if (f[1][i] <= m) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
/*
	f[i][j] 表示不选 i 之前的, 吃了 j 的最小花费.
	f[i][j] = f[i + 1][j - a[i]] + a[i] * i, f[i + 1][j];
	显然, 若 i * j > m, 花费必然大于 m.
	<=> i * j <= m <=> j <= m / i;
*/
