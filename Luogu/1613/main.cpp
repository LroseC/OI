#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 60;

int n, m;
bool G[N][N][64];
int dis[N][N];

signed main(void)
{
	n = read(), m = read();
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= n; ++i)
		dis[i][i] = 0;
	for (int i = 0; i < m; ++i) {
		int u = read(), v = read();
		G[u][v][0] = 1;
		dis[u][v] = 1;
	}

	for (int t = 1; t < 64; ++t)
		for (int k = 1; k <= n; ++k)
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					if (G[i][k][t - 1] && G[k][j][t - 1]) {
						G[i][j][t] = 1;
						dis[i][j] = 1;
					}
	
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	printf("%lld\n", dis[1][n]);
	return 0;
}