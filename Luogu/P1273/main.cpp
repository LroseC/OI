#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 3010;

struct Edge
{
	int v, w;
};

int n, m;
int f[N][N];
vector<Edge> G[N];

int dfs(int u, int fa)
{
	f[u][0] = 0;
	if (G[u].size() == 1) return 1;
	int sum = 0;
	for (auto t : G[u]) {
		int v = t.v, w = t.w;
		if (v == fa) continue;
		int tmp;
		sum += (tmp = dfs(v, u));
		for (int j = sum; j >= 0; --j)
			for (int k = tmp; k >= 0; --k)
				if (j - k >= 0)
					f[u][j] = max(f[u][j], f[u][j - k] - w + f[v][k]);
	}
	return sum;
}

int main(void)
{
	n = read(), m = read();
	for (int u = 1; u <= n - m; ++u) {
		int x = read();
		while (x--) {
			int v = read(), w = read();
			G[u].emplace_back(Edge({v, w}));
			G[v].emplace_back(Edge({u, w}));
		}
	}
	memset(f, 0xcf, sizeof f);
	for (int i = n - m + 1; i <= n; ++i) f[i][1] = read();
	dfs(1, -1);
	for (int i = m; i >= 0; --i) {
		if (f[1][i] >= 0) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}