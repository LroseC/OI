#include <cmath>
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

const int INF = 1e8;
const int N = 1e4 + 10;

int n, m;
vector<int> G[N];
int f[N][20];

void dfs(int u, int fa)
{
	for (int i = 1; i <= m; ++i) f[u][i] = i;
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		for (int i = 1; i <= m; ++i) {
			int minx = INF;
			for (int j = 1; j <= m; ++j)
				if (j != i)
					minx = min(minx, f[v][j]);
			f[u][i] += minx;
		}
	}
}

int main(void)
{
	n = read(); m = log2(n);
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1);
	int res = INF;
	for (int i = 1; i <= m; ++i)
		res = min(res, f[1][i]);
	printf("%d\n", res);
	return 0;
}