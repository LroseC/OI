#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1e5 + 10;

int n, k;
vector<int> G[N];
int f[N][30];

void dfs1(int u, int fa)
{
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs1(v, u);
		for (int i = 1; i <= k; ++i)
			f[u][i] += f[v][i - 1];
	}
}
void dfs2(int u, int fa)
{
	for (auto v : G[u]) {
		if (v == fa) continue;
		for (int i = k; i >= 1; --i) {
			f[v][i] += f[u][i - 1];
			if (i - 2 >= 0)
				f[v][i] -= f[v][i - 2];
		}
		dfs2(v, u);
	}
}

int main(void)
{
	n = read(), k = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i) f[i][0] = read();
	dfs1(1, -1);
	dfs2(1, -1);
	for (int i = 1; i <= n; ++i) {
		int ans = 0;
		for (int j = 0; j <= k; ++j) ans += f[i][j];
		printf("%d\n", ans);
	}
	return 0;
}