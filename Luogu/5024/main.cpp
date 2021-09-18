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
LL f[N][2];
LL sum[N][2];
LL invf[N][2];
LL g[N][M][2][2];
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
	memset(g, 0x3f, sizeof g);
	for (int i = 1; i <= n; ++i) {
		g[i][0][0][0] = 0x3f3f3f3f;
		g[i][0][0][1] = f[fa[i][0]][1] - min(f[i][0], f[i][1]);
		g[i][0][1][0] = f[fa[i][1]][0] - f[i][1];
		g[i][0][1][1] = f[fa[i][0]][1] - min(f[i][0], f[i][1]);
	}
	for (int k = 1; k < M; ++k)
		for (int i = 1; i <= n; ++i)
			for (int p = 0; p < 2; ++p)
				for (int q = 0; q < 2; ++q)
					for (int t = 0; t < 2; ++t)
						g[i][k][p][q] = min(g[i][k][p][q], g[i][k - 1][p][t] + g[fa[i][k - 1]][k - 1][t][q]);
}
LL Solve(int a, int b, int x, int y)
{
	int u = a, v = b;
	sum[a][x] = f[a][x]; sum[b][y] = f[b][y];
	sum[a][!x] = sum[b][!y] = 0x3f3f3f3f;
	for (int k = 16; k >= 0; --k) {
		int F = fa[u][k];
		if (dep[F] >= dep[v]) {
			sum[F][0] = min(sum[u][0] + g[u][k][0][0], sum[u][1] + g[u][k][1][0]);
			sum[F][1] = min(sum[u][0] + g[u][k][0][1], sum[u][1] + g[u][k][1][1]);
			u = F;
		}
	}
	if (u == v) return sum[v][y];
	for (int k = 16; k >= 0; --k) {
		int F1 = fa[u][k], F2 = fa[v][k];
		if (F1 != F2) {
			sum
		}
	}
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
		int a = read(), x = read(), b = read(), y = read();
		if (dep[a] < dep[b]) swap(a, b), swap(x, y);
		printf("%lld\n", Solve(a, b, x, y));
	}
	return 0;
}