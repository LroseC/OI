#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

// #define DEBUG

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

typedef long long LL;
const int Mod = 1e9 + 7;
const int N = 1e5 + 10, M = 110;

int n, m;
vector<int> G[N];
int f[N][M][2][2], g[M][2][2];
int sz[N];
/*
第一维表示当前节点
第二维表示当前子树（包括自己）使用的监听设备数量
第三维表示当前节点是否放了监听设备
第四维表示当前节点是否被监听
*/
/*
f[i][j][a][b] 表示当前当前状态能使子树被完全监听的方案数
目标：f[1][m][0/1][1];
边界：当节点 i 是叶节点时，f[i][0][0][0] = 1, f[i][1][1][0] = 1;
性质：方案数
转移方程：（写错了。。。)
f[u][j][0][0] += f[u][j - k][0][0] * f[v][k][0][1];
f[u][j][0][1] += f[u][j - k][0][0] * f[v][k][1][1] + f[u][j - k][0][1] * (f[v][k][0][1] + f[v][k][1][1]);
f[u][j][1][0] += f[u][j - k][1][0] * (f[v][k][0][0] + f[v][k][0][1]);
f[u][j][1][1] += f[u][j - k][1][0] * (f[v][k][1][0] + f[v][k][1][1]) + f[u][j - k][1][1] * (f[v][k][0][0] + f[v][k][0][1] + f[v][k][1][0] + f[v][k][1][1]);
*/

bool flag = 0;

void dfs(int u, int fa)
{
	sz[u] = 1;
	f[u][0][0][0] = f[u][1][1][0] = 1;
	f[u][1][1][0] = 1;
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);

		sz[u] += sz[v];

		for (int i = 0; i <= min(sz[u], m); ++i)
			for (int p = 0; p < 2; ++p)
				for (int q = 0; q < 2; ++q) {
					g[i][p][q] = f[u][i][p][q];
					f[u][i][p][q] = 0;
				}

		for (int j = min(sz[u], m); j >= 0; --j)
			for (int k = min(sz[v], j); k >= 0; --k) {
				f[u][j][0][0] = ((LL)f[u][j][0][0] + 1ll * g[j - k][0][0] * f[v][k][0][1] % Mod) % Mod;
				f[u][j][0][1] = ((LL)f[u][j][0][1] + (1ll * g[j - k][0][0] * f[v][k][1][1] % Mod + 1ll * g[j - k][0][1] * ((LL)f[v][k][0][1] + f[v][k][1][1])) % Mod) % Mod;
				f[u][j][1][0] = ((LL)f[u][j][1][0] + 1ll * g[j - k][1][0] * (f[v][k][0][0] + f[v][k][0][1]) % Mod) % Mod;
				f[u][j][1][1] = ((LL)f[u][j][1][1] + (1ll * g[j - k][1][0] * ((LL)f[v][k][1][0] + f[v][k][1][1]) % Mod + 1ll * g[j - k][1][1] * ((LL)f[v][k][0][0] + f[v][k][0][1] + f[v][k][1][0] + f[v][k][1][1]) % Mod) % Mod) % Mod;
			}
	}
}


int main(void)
{
	n = read(), m = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1);
	#ifdef DEBUG
	// for (int i = 1; i <= n; ++i, puts(""))
	// 	for (int j = 0; j <= m; ++j)
	// 		for (int p = 0; p < 2; ++p)
	// 			for (int q = 0; q < 2; ++q)
	// 				printf("f[%d][%d][%d][%d] = %d\n", i, j, p, q, f[i][j][p][q]);
	// puts("...");
	#endif
	printf("%d\n", ((LL)f[1][m][0][1] + f[1][m][1][1]) % Mod);
	return 0;
}