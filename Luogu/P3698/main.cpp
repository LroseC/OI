#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}
template<typename INT>
INT max(INT a, INT b, INT c)
{
	return max(a, max(b, c));
}

const int N = 110;

int n, m;
vector<int> G[N];
int f[N][N][2];

void dfs(int u, int fa)
{
	f[u][0][0] = f[u][0][1] = 1;
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		for (int j = m; j >= 0; --j)
			for (int k = 1; k <= j; ++k) {
				if (k == 1)
					f[u][j][0] = max(f[u][j][0], f[u][j - k][1] + f[v][k - 1][0]);
				else
					f[u][j][0] = max(f[u][j][0], f[u][j - k][1] + f[v][k - 1][0], f[u][j - k][0] + f[v][k - 2][1]);
				f[u][j][1] = max(f[u][j][1], f[u][j - k][1] + f[v][k - 2][1]);
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
	dfs(0, -1);
	int ans = 0;
	for (int i = 0; i <= m; ++i) ans = max(ans, f[0][i][0]);
	printf("%d\n", ans);
	return 0;
}