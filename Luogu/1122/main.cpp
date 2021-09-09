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

const int N = 16010, M = N * 2;

int n;
int val[N];
int f[N];
int ans = 0xcfcfcfcf;
vector<int> G[N];

void dfs(int u, int fa)
{
	f[u] = val[u];
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		f[u] += f[v] < 0 ? 0 : f[v];
	}
	ans = max(f[u], ans);
	return;
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	dfs(1, -1);
	printf("%d\n", ans);
	return 0;
}