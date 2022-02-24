#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

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
} IO;

const int N = 1e4 + 10, M = 1e6 + 10;

int n, m, S, T;
int idx = 1, head[N], nex[M], to[M], w[M], c[M];

void AddEdge(int u, int v, int wi, int ci)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, w[idx] = wi, c[idx] = ci;
}

namespace Dinic
{
	int ans, res;
	bool vis[N];
	int dis[N], now[N];
	queue<int> q, EMPTY;
	bool SPFA(void)
	{
		memset(vis, 0, sizeof vis);
		memcpy(now, head, sizeof now);
		memset(dis, 0x3f, sizeof dis);
		q = EMPTY; q.emplace(S); dis[S] = 0;
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (c[e] && dis[to[e]] > dis[u] + w[e]) {
					dis[to[e]] = dis[u] + w[e];
					if (!vis[to[e]]) {
						vis[to[e]] = 1;
						q.emplace(to[e]);
					}
				}
		}
		return dis[T] != 0x3f3f3f3f;
	}
	int dfs(int u, int flow)
	{
		if (u == T) {
			ans += dis[T] * flow;
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (c[e] && dis[to[e]] == dis[u] + w[e]) {
				now[u] = e;
				if (vis[to[e]]) continue;
				int tmp = dfs(to[e], min(c[e], rest));
				if (!tmp) dis[to[e]] = INT_MAX;
				else {
					rest -= tmp;
					c[e] -= tmp;
					c[e ^ 1] += tmp;
				}
			}
		vis[u] = 0;
		return flow - rest;
	}
	int main(void)
	{
		ans = 0, res = 0;
		while (SPFA())
			res += dfs(S, INT_MAX);
		return 0;
	}
}

int main(void)
{
	IO >> n >> m >> S >> T;
	for (int i = 1; i <= m; ++i) {
		int u, v, wi, ci; IO >> u >> v >> ci >> wi;
		AddEdge(u, v, wi, ci);
		AddEdge(v, u, -wi, 0);
	}
	Dinic::main();
	printf("%d %d\n", Dinic::res, Dinic::ans);
	return 0;
}
