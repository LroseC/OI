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

const int N = 1e4, M = 1e5;

int n, m, S = N - 1, T = N - 2;
int idx = 1, head[N], to[M], nex[M], f[M];

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
				if (!tmp) d[to[e]] = 0;
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
	int tot = 0;
	read >> m >> n;
	for (int i = 1; i <= m; ++i) {
		int x; read >> x;
		tot += x;
		addFlow(n + i, T, x);
	}
	for (int i = 1; i <= n; ++i) {
		addFlow(S, i, 1);
		int x; read >> x;
		for (int j = 1; j <= x; ++j) {
			int v; read >> v;
			addFlow(i, v + n, 1);
		}
	}
	if (Dinic::main() != tot)
		puts("No Solution!");
	else {
		for (int i = 1; i <= m; ++i) {
			printf("%d: ", i);
			for (int e = head[n + i]; e; e = nex[e])
				if (to[e] != T && f[e]) printf("%d ", to[e]);
			puts("");
		}
	}
	return 0;
}
