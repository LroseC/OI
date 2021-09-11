#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

struct Edge
{
	int v, w;
	bool operator<(const Edge &b) const
	{
		return w < b.w;
	}
};

const int N = 5e5 + 10;

int n, m;
LL ans = 0x3f3f3f3f3f3f3f3f;
vector<Edge> G[N];
int vis[30][30];

void dfs(int u, LL dis)
{
	if (dis > ans) return;
	if (!m && u == 1) { ans = min(ans, dis); }
	for (auto ed : G[u]) {
		int v = ed.v;
		LL w = ed.w;
		if (vis[u][v] > 3) continue;
		if (!vis[u][v]) --m;
		++vis[u][v]; ++vis[v][u];
		dfs(v, dis + w);
		--vis[u][v], --vis[v][u];
		if (!vis[u][v]) ++m;
	}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(Edge({v, 1 << i}));
		G[v].emplace_back(Edge({u, 1 << i}));
	}
	for (int i = 1; i <= n; ++i) sort(G[i].begin(), G[i].end());
	if (n <= 20) {
		dfs(1, 0);
		printf("%lld\n", ans);
		return 0;
	}
	return 0;
}