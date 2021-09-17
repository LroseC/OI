#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10, M = 17;
inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int w[N];
char type[5];
int dep[N];
int fa[N][M];
int f[N][2];
int invf[N][2];
int g[N][M][2][2];
vector<int> G[N];

void dfs(int u, int father, int depth)
{
	f[u][0] = 0, f[u][1] = w[u];
	dep[u] = depth;
	for (int v : G[u]) {
		if (v == father) continue;
		dfs(v, u, depth + 1);
		fa[v][0] = u;
		f[u][0] += f[v][1];
		f[u][1] += min(f[v][0], f[v][1]);
	}
}
void GetFa(void)
{
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i)
			fa[i][k] = fa[fa[i][k - 1]][k - 1];
}
void GetInv(int u, int father)
{
	for (int v : G[u]) {
		if (v == father) continue;
		invf[v][0] = invf[u][1] + invf[u][1] - min(f[v][0], f[v][1]);
		invf[v][1] = min(invf[v][0], invf[u][0] + f[u][0] - f[v][1]);
		GetInv(v, u);
	}
}
void GetG(void)
{
}

int main(void)
{
	n = read(), m = read();
	scanf("%s", type);
	for (int i = 1; i <= n; ++i) w[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1, 1);
	GetFa();
	GetInv(1, -1);
	GetG();

	while (m--) {
		//先求 lca
		int u = read(), x = read(), v = read(), y = read();
		if (dep[u] < dep[v]) swap(u, v), swap(x, y);
		int uu = u, vv = v;
		for (int k = 16; k >= 0; --k)
			if (fa[uu][k] && dep[fa[uu][k]] <= dep[vv]) uu = fa[uu][k];
		for (int k = 16; k >= 0; --k)
			if (fa[uu][k] != fa[vv][k]) uu = fa[uu][k], vv = fa[vv][k];
		int lca = fa[uu][0];
		//然后按照要求倍增转移到 lca，两种情况取 min
		uu = u, vv = v;
		sum[u][x] = f[u][x]; sum[v][y] = f[v][y];
		for (int k = 16; k >= 0; --k) {
			if (dep[fa[uu][k]] < lca)
				for (int q = 0, flag = 1; q < 2; ++q)
					for (int p = 0; p < 2; ++p)
						if (uu != u || p == x) {
							if (flag) sum[fa[uu][k]][q] = sum[uu][p] + g[uu][k][p][q], flag = 0;
							else sum[fa[uu][k]][q] = min(sum[fa[uu][k]][q], sum[uu][p] + g[uu][k][p][q]);
						}
			if (dep[fa[vv][k]] < lca)
				for (int q = 0; flag = 1; q < 2; ++q)
					for (int p = 0; p < 2; ++p)
						if (vv != v || p == y) {
							if (flag) sum[fa[vv][k]][q] = sum[vv][p] + g[vv][k][q][p], flag = 0;
							else sum[fa[vv][k]][q] = min(sum[fa[vv][k]][q], sum[vv][p] + g[vv][k][p][q]);
						}
		}
		LL ans = 0x3f3f3f3f3f3f3f3f;
		for (int i = 0; i < 2; ++i)
			for (int q = 0; q < 2; ++q)
				for (int p = 0; p < 2; ++p)
					ans = min(ans, sum[uu][q] + g[uu][0][q][i] + sum[vv][p] + g[vv][0][p][i] + ndp[lca][i]);
		printf("%lld\n", ans);
	}
	return 0;
}