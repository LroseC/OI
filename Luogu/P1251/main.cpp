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

using i64 = long long;
const int N = 4010, M = 48010, INF = 0x3f3f3f3f;

int n, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], f[M], w[M];

void addEdge(int u, int v, int ci, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
	f[idx] = ci, w[idx] = wi;
}
void addFlow(int u, int v, int c, int w)
{
	addEdge(u, v, c, +w);
	addEdge(v, u, 0, -w);
}

namespace Dinic
{
	int now[N];
	i64 dis[N];
	bool vis[N];

	bool SPFA(void)
	{
		std::queue<int> q;
		std::memset(dis, 0x3f, sizeof dis);
		std::memcpy(now, head, sizeof head);
		dis[S] = 0;
		q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (f[e] && dis[u] + w[e] < dis[to[e]]) {
					int v = to[e];
					dis[v] = dis[u] + w[e];
					if (!vis[v]) {
						vis[v] = 1;
						q.emplace(v);
					}
				}
		}
		return dis[T] != dis[0];
	}
	int dfs(int u, int flow, i64 &cost)
	{
		if (u == T) {
			cost += dis[T] * flow;
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (f[e] && dis[to[e]] == dis[u] + w[e] && !vis[to[e]]) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(rest, f[e]), cost);
				if (!tmp) dis[to[e]] = 0x3f3f3f3f3f3f3f3f;
				rest -= tmp;
				f[e] -= tmp;
				f[e ^ 1] += tmp;
			}
		vis[u] = 0;
		return flow - rest;
	}
	std::pair<i64, i64> main(void)
	{
		i64 res = 0, cost = 0;
		while (SPFA())
			res += dfs(S, INT_MAX, cost);
		return std::make_pair(res, cost);
	}
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		int x; read >> x;
		addFlow(i, T, x, 0);
		addFlow(S, i + n, x, 0);
	}
	int p, m, f, nn, s;
	read >> p >> m >> f >> nn >> s;
	for (int i = 1; i <= n; ++i) {
		addFlow(S, i, INF, p);
		if (i + m <= n)
			addFlow(i + n, i + m, INF, f);
		if (i + nn <= n)
			addFlow(i + n, i + nn, INF, s);
		if (i != n)
			addFlow(i + n, i + n + 1, INF, 0);
	}
	auto res = Dinic::main();
	printf("%lld\n", res.second);
	return 0;
}
