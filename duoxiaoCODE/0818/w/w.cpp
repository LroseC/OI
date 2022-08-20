#include <cctype>
#include <cstdio>
#include <cstdint>
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
const int N = 1e5 + 10;

i32 n, m;
i32 a[N];
i64 f[N];

int main(void)
{
#ifndef DEBUG
	freopen("w.in", "r", stdin);
	freopen("w.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	i64 ans = 0;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		for (int j = m - i * 2; j >= 1ll * i * a[i]; --j) {
			f[j] = std::max(f[j], f[j - 1ll * i * a[i]] + a[i]);
			ans = std::max(ans, f[j]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
