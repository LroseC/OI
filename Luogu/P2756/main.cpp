#include <queue>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
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

const int N = 1e5, M = 1e6;

int n, m, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], f[M];

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
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		addFlow(S, i, 1);
	for (int i = n + 1; i <= m; ++i)
		addFlow(i, T, 1);
	while (true) {
		int u, v;
		read >> u >> v;
		if (u == -1 && v == -1)
			break;
		addFlow(u, v, 1);
	}
	printf("%d\n", Dinic::main());
	for (int i = 1; i <= n; ++i)
		for (int e = head[i]; e; e = nex[e])
			if (to[e] != S && f[e] == 0) {
				printf("%d %d\n", i, to[e]);
				break;
			}
	return 0;
}
