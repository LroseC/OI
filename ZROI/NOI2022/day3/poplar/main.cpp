#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 55, M = 2005;

int n, m, Q;
vint G[N];
int a[N], b[N];
int sz[N];
i64 sum[N];
i64 f[N][N][M], g[N][N][M];
i64 tmpf[N][M], tmpg[N][M];
int ff[N], gg[N];

void DP(int u, int fa)
{
	ff[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			DP(v, u);
			sz[u] += sz[v];
			sum[u] += sum[v];
			ff[u] = std::max(ff[u] + ff[v] - 1, ff[u] + gg[v]);
			gg[u] = std::max(gg[u] + ff[v], gg[u] + gg[v]);
			std::memset(tmpf, 0, sizeof tmpf);
			std::memset(tmpg, 0, sizeof tmpg);
			for (int i = 0; i <= std::max(ff[u], gg[u]); ++i)
				for (int j = 0; j <= std::max(ff[u], gg[u]) && j <= i; ++j)
					for (int s = std::min(sum[u], (i64)m); s >= 1; --s)
						for (int sp = 0; sp <= s && sp <= sum[v]; ++sp) {
							if (i != 0) {
								if (i - j + 1 >= 1 && (f[u][i - j + 1][s - sp] || (i - j + 1 == 1 && s - sp == 0)) && f[v][j][sp]) {
									tmpf[i][s] = std::max(tmpf[i][s], f[u][i - j + 1][s - sp] + f[v][j][sp]);
								}
								if (i - j >= 1 && (f[u][i - j][s - sp] || (i - j == 1 && s - sp == 0)) && g[v][j][sp]) {
									tmpf[i][s] = std::max(tmpf[i][s], f[u][i - j][s - sp] + g[v][j][sp]);
								}
							}
							if ((g[u][i - j][s - sp] || (i - j == 0 && s - sp == 0)) && f[v][j][sp])
								tmpg[i][s] = std::max(tmpg[i][s], g[u][i - j][s - sp] + f[v][j][sp]);
							if ((g[u][i - j][s - sp] || (i - j == 0 && s - sp == 0)) && g[v][j][sp])
								tmpg[i][s] = std::max(tmpg[i][s], g[u][i - j][s - sp] + g[v][j][sp]);
						}
			for (int i = 1; i <= std::max(ff[u], gg[u]); ++i)
				for (int j = 1; j <= std::min(sum[u], (i64)m); ++j) {
					f[u][i][j] = std::max(f[u][i][j], tmpf[i][j]);
					g[u][i][j] = std::max(g[u][i][j], tmpg[i][j]);
				}
		}
	sz[u] += 1;
	sum[u] += a[u];
	for (int i = 1; i <= ff[u]; ++i)
		for (int j = std::min(sum[u], (i64)m); j >= a[u]; --j)
			if (f[u][i][j - a[u]] || (i == 1 && j - a[u] == 0)) {
				f[u][i][j] = f[u][i][j - a[u]] + b[u];
				f[u][i][j - a[u]] = 0;
			}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m >> Q;
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		read >> a[i] >> b[i];
	}
	DP(1, 0);
	for (int i = 1; i <= Q; ++i) {
		int t, x;
		read >> t >> x;
		i64 res = std::max(f[1][t][x], g[1][t][x]);
		if (res == 0) puts("-1");
		else printf("%lld\n", res);
	}
	return 0;
}
/*
   f[u][i][k] 表示强制选点 u, 已经选了 i 个连通块, ai 的和为 k 的最大 bi 和.
   g[u][i][k] 表示强制不选点 u, ...
*/
