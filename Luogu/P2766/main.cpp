#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

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
} read;

const int N = 5010, M = 5e4 + 10;

int n, S = N - 1, T = N - 2, gn;
int val[510], g[510];
int idx = 1, head[N], nex[M], to[M], f[M];

void clear(void)
{
	idx = 1;
	std::memset(head, 0, sizeof head);
}
void addEdge(int u, int v, int fi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, f[idx] = fi;
}
void addFlow(int u, int v, int f)
{
	addEdge(u, v, f);
	addEdge(v, u, 0);
}

namespace Dinic
{
	int d[N], now[N];

	bool BFS(void)
	{
		std::queue<int> q;
		std::memset(d, 0, sizeof d);
		std::memcpy(now, head, sizeof head);
		d[S] = 1;
		q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int e = head[u]; e; e = nex[e])
				if (f[e] && !d[to[e]]) {
					d[to[e]] = d[u] + 1;
					if (to[e] == T) return 1;
					q.emplace(to[e]);
				}
		}
		return 0;
	}
	int dfs(int u, int flow)
	{
		if (u == T)
			return flow;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (f[e] && d[to[e]] == d[u] + 1) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(rest, f[e]));
				if (tmp == 0) d[to[e]] = 0;
				rest -= tmp;
				f[e] -= tmp;
				f[e ^ 1] += tmp;
			}
		return flow - rest;
	}
	int main(void)
	{
		int res = 0;
		while (BFS())
			res += dfs(S, INT_MAX);
		return res;
	}
}

int main(void)
{
	read >> n;
	if (n == 1) {
		printf("1\n1\n1\n");
		return 0;
	}
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	for (int i = 1; i <= n; ++i) {
		g[i] = 1;
		for (int j = 1; j < i; ++j)
			if (val[j] <= val[i]) g[i] = std::max(g[i], g[j] + 1);
		gn = std::max(gn, g[i]);
	}
	printf("%d\n", gn);
	for (int i = 1; i <= n; ++i) {
		if (g[i] == 1)
			addFlow(S, i, 1);
		addFlow(i, i + n, 1);
		for (int j = i + 1; j <= n; ++j)
			if (g[j] == g[i] + 1 && val[i] <= val[j]) addFlow(i + n, j, 1);
		if (g[i] == gn)
			addFlow(i + n, T, 1);
	}
	printf("%d\n", Dinic::main());
	clear();
	for (int i = 1; i <= n; ++i) {
		if (g[i] == 1)
			addFlow(S, i, i == 1 ? 0x3f3f3f3f : 1);
		if (g[i] == gn)
			addFlow(i + n, T, i == n ? 0x3f3f3f3f : 1);
		addFlow(i, i + n, (i == 1 || i == n) ? 0x3f3f3f3f : 1);
		for (int j = i + 1; j <= n; ++j)
			if (g[j] == g[i] + 1 && val[i] <= val[j]) addFlow(i + n, j, 1);
	}
	printf("%d\n", Dinic::main());
	return 0;
}
