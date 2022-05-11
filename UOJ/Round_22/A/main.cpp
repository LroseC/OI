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

using i64 = long long;
#define int long long
const int N = 2.5e5 + 10, M = 61;

int n, m, T;
i64 a[N];
i64 f[M][N];

void init(int id)
{
	int idx = 0;
	i64 *g = f[id];
	if (id == 0) {
		for (int i = 1; i <= n; ++i)
			if ((a[i] & 1) == 0)
				g[++idx] = i;
		for (int i = 1; i <= n; ++i)
			if ((a[i] & 1) == 1)
				g[++idx] = i;
		return;
	}
	init(id - 1);
	i64 *lst = f[id - 1];
	for (int i = 1; i <= n; ++i)
		if ((a[lst[i]] >> id & 1) == 0)
			g[++idx] = lst[i];
	for (int i = 1; i <= n; ++i)
		if ((a[lst[i]] >> id & 1) == 1)
			g[++idx] = lst[i];
}
namespace SubTask2
{
	int query(int id, i64 x)
	{
		i64 *g = f[id];
		int t = std::lower_bound(g + 1, g + 1 + n, x) - g;
		return n - (t - 1);
	}
	int main(void)
	{
		i64 res = 0, lastans = 0;
		for (int i = 1; i <= n; ++i)
			res ^= a[i];
		while (m--) {
			i64 x; read >> x;
			x ^= (lastans >> 20);
			lastans = res ^ (n & 1 ? x : 0);
			for (int i = 1; i < M; ++i) {
				i64 cnt = query(i - 1, (1ll << i) - (x & ((1ll << i) - 1))) & 1;
				lastans ^= cnt << i;
			}
			printf("%lld\n", lastans);
		}
		return 0;
	}
}
namespace SubTask3
{
	int main(void)
	{
		i64 res = 0, lastans = 0;
		for (int i = 1; i <= n; ++i)
			res ^= a[i];
		for (int tim = 1; tim <= m; ++tim) {
			i64 x; read >> x;
			x ^= (lastans >> 20);
			lastans = res ^ (n & 1 ? x : 0);
			for (int i = 1; i < M; ++i) {
				i64 cnt = query(i - 1, (1ll << i) - (x & ((1ll << i) - 1))) & 1;
				lastans ^= cnt << i;
			}
			printf("%lld\n", lastans);
		}
		return 0;
	}
}

signed main(void)
{
	read >> n >> m >> T;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	init(M - 1);
	for (int id = 0; id < M; ++id)
		for (int i = 1; i <= n; ++i)
			f[id][i] = a[f[id][i]] & (1ll << id + 1) - 1;
	if (T == 0) {
		SubTask3::main();
		return 0;
	}
	else {
		SubTask2::main();
		return 0;
	}
	return 0;
}
