#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

using LL = long long;
const int N = 12, S = 1 << 12;
inline int lowbit(int x) { return x & -x; }

int n, m;
int G[N][N], INF = 0x3f3f3f3f;
int f[N][S], g[S];

int main(void)
{
	cin >> n >> m;
	memset(G, 0x3f, sizeof G);
	for (int i = 0; i < n; ++i)
		G[i][i] = 0;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		G[u][v] = G[v][u] = min(G[u][v], w);
	}
	for (int i = 0; i < 1 << n; ++i)
		for (int j = 0; j < n; ++j)
			if (i >> j & 1)
				for (int k = 0; k < n; ++k) {
					if (G[j][k] != INF)
						g[i] |= 1 << k;
				}
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < n; ++i)
		f[0][1 << i] = 0;
	int ans = f[0][(1 << n) - 1];
	for (int i = 1; i < n; ++i)
		for (int state = 1; state < 1 << n; ++state)
			for (int ori = (state - 1) & state; ori; ori = (ori - 1) & state) {
				if (g[ori] & state != state) continue;
				int rest = ori ^ state;
				LL sum = 0;
				for (int k = 0; k < n; ++k)
					if (rest >> k & 1) {
						int minx = INT_MAX;
						for (int t = 0; t < n; ++t) {
							if (ori >> t & 1)
								minx = min(minx, G[t][k]);
						}
						sum += minx;
					}
				f[i][state] = min(0ll + f[i][state], f[i - 1][ori] + 1ll * sum * i);
				if (state == (1 << n) - 1)
					ans = min(ans, f[i][state]);
			}
	printf("%d\n", ans);
	return 0;
}
/*
   这个写法是错误的, 复杂度为 n^3*2^n, 开启 O2 优化之后才能过
   正确的写法复杂度应该是 n^2*2^n
*/
