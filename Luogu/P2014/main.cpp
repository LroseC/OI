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

const int N = 310;

int n, m;
vector<int> G[N];
int f[N][N];
bool isroot[N];

void dfs(int u, int fa)
{
	for (auto v : G[u]) {
		dfs(v, u);
		if (v == fa) continue;
		for (int j = m; j >= 0; --j)
			for (int k = 0; k <= j; ++k)
				f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
	}
	f[u][0] = 0;
}

int main(void)
{
	n = read(), m = read();
	memset(f, 0xcf, sizeof f);
	for (int i = 1; i <= n; ++i)
	{
		int u = read();
		f[i][1] = read();
		G[u].emplace_back(i);
	}
	f[0][0] = 0;
	dfs(0, -1);
	printf("%d\n", f[0][m]);
	return 0;
}