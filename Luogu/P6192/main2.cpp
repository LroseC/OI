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
const int N = 110, S = 1 << 10;

int n, m, K;
int f[S][N];
bool vis[N];
int G[N][N], key[N];

void dijkstra(int id)
{
	std::memset(vis, 0, sizeof vis);
	int *dis = f[id];
	for (int i = 1; i < n; ++i) {
		int u = 0;
		for (int j = 1; j <= n; ++j)
			if (!vis[j] && dis[j] < dis[u])
				u = j;
		vis[u] = 1;
		for (int v = 1; v <= n; ++v)
			dis[v] = std::min(dis[v], dis[u] + G[u][v]);
	}
}

int main(void)
{
	read >> n >> m >> K;
	std::memset(G, 0x3f, sizeof G);
	for (int i = 1, u, v, w; i <= m; ++i) {
		read >> u >> v >> w;
		G[u][v] = G[v][u] = std::min(G[u][v], w);
	}
	std::memset(f, 0x3f, sizeof f);
	for (int i = 0; i < K; ++i) {
		read >> key[i];
		f[1 << i][key[i]] = 0;
	}
	for (int s = 1; s < 1 << K; ++s) {
		for (int i = 1; i <= n; ++i) {
			for (int sj = (s - 1) & s; sj; sj = (sj - 1) & s)
				f[s][i] = std::min(f[s][i], f[sj][i] + f[s ^ sj][i]);
		}
		dijkstra(s);
	}
	printf("%d\n", f[(1 << K) - 1][key[0]]);
	return 0;
}
