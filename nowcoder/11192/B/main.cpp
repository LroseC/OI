#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int w[N];
int f[N][2510];
vector<int> G[N];

int dp(int u, int fa)
{
	int maxn = 0;
	for (int v : G[u]) {
		if (v == fa) continue;
		int t = dp(v, u);
		if (!maxn)
			for (int j = t; t >= 0; --t)
				f[u][j] = f[v][j];
	}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) w[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int maxn = dp(1, -1);
	int ans = INF;
	for (int i = 1; i <= maxn; ++i)
		ans = min(ans, f[1][i]);
	printf("%d\n", ans);
	return 0;
}