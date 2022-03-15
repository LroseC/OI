#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
bool vis[N];
int f[N];
int w[N], allw[N];
int dfn[N], low[N], tim;
vector<int> oG[N], G[N];
int stk[N], top;
int id[N], idx;

void tarjan(int u, int fa)
{
	vis[u] = 1;
	dfn[u] = ++tim;
	low[u] = dfn[u];
	stk[++top] = u;
	for (int v : oG[u]) {
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		++idx;
		while (stk[top] != u) {
			vis[stk[top]] = 0;
			id[stk[top]] = idx;
			allw[idx] += w[stk[top]];
			--top;
		}
		vis[stk[top]] = 0;
		id[stk[top]] = idx;
		allw[idx] += w[stk[top]];
		--top;
	}
}

int DFS(int x)
{
	if (f[x]) return f[x];
	f[x] = allw[x];
	for (int v : G[x]) {
		f[x] = max(f[x], allw[x] + DFS(v));
	}
	return f[x];
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) w[i] = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		oG[u].emplace_back(v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i, -1);
	for (int u = 1; u <= n; ++u) {
		for (int v : oG[u])
			if (id[v] != id[u])
				G[id[u]].emplace_back(id[v]);
	}
	int ans = 0;
	for (int u = idx; u; --u) {
		ans = max(ans, DFS(u));
	}
	printf("%d\n", ans);
	return 0;
}