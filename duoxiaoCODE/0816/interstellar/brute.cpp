#include <vector>
#include <cctype>
#include <cstdio>
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
const int N = 1e5 + 10, mod = 998244353;

i32 n;
i64 f[N];
i32 maxson[N];
std::vector<PII> G[N];

void dp(i32 u)
{
	i64 mx = 0;
	f[u] = 0;
	for (auto e : G[u]) {
		dp(e.first);
		if (f[e.first] + (i64(1) << e.second) > mx) {
			mx = f[e.first] + (i64(1) << e.second);
			maxson[u] = e.first;
		}
		f[u] += f[e.first] + (i64(1) << e.second);
	}
	f[u] += mx;
}

int main(void)
{
	read >> n;
	for (int i = 2; i <= n; ++i) {
		i32 u, w;
		read >> u >> w;
		G[u].emplace_back(i, w);
	}
	dp(1);
//	for (int i = 1; i <= n; ++i) {
//		printf("%ld ", f[i]);
//	}
//	puts("");
//	for (int i = 1; i <= n; ++i)
//		printf("%d ", maxson[i]);
//	puts("");
	printf("%d\n", f[1] % mod);
	//Think twice, code once.
	return 0;
}
