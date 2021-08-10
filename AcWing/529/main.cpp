#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 12, S = 1 << 12;
const int INF = 0x3f3f3f3f;

int n, m;
int d[N][N];
int g[S];
int f[S][N];

int main(void)
{
	scanf("%d%d", &n, &m);
	memset(d, 0x3f, sizeof d);
	for (int i = 0; i < n; ++i) d[i][i] = 0;

	for (int i = 0; i < m; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		--u, --v;
		d[u][v] = d[v][u] = min(d[u][v], w);
	}

	memset(f, 0x3f, sizeof f);

	for (int i = 0; i < 1 << n; ++i)
		for (int j = 0; j < n; ++j)
			if (i >> j & 1)
				for (int k = 0; k < n; ++k)
					if (d[j][k] != INF) {
						g[i] |= 1 << k;
					}
	
	for (int i = 0; i < n; ++i)
		f[1 << i][0] = 0;
	
	for (int i = 0; i < 1 << n; ++i) {
		for (int j = (i - 1) & i; j; j = (j - 1) & i) {
			if ((g[j] & i) != i) continue;
			int rest = i ^ j, res = 0;
			for (int k = 0; k < n; ++k)
				if (rest >> k & 1) {
					int minn = INF;
					for (int t = 0; t < n; ++t)
						if (j >> t & 1)
							minn = min(minn, d[t][k]);
					res += minn;
				}
			for (int k = 1; k < n; ++k)
				f[i][k] = min(f[i][k], f[j][k - 1] + res * k);
		}
	}
	int ans = INF;
	for (int i = 0; i < n; ++i)
		ans = min(ans, f[(1 << n) - 1][i]);
	// printf("%d\n", g[1]);
	printf("%d\n", ans);
	return 0;
}