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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1610, M = 3e5 + 10;

int n, m, S = N - 1, T = N - 2, idx = 1;
int a[N];
int head[N], nex[M], to[M], fl[M], w[M];

void addEdge(int u, int v, int f, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, fl[idx] = f, w[idx] = wi;
}
void addFlow(int u, int v, int f, int w)
{
	addEdge(u, v, f, w);
	addEdge(v, u, 0, -w);
}

namespace dinic
{
	bool vis[N];
	int now[N];
	i64 dis[N];
	bool SPFA(void)
	{
		std::queue<int> q;
		std::memcpy(now, head, sizeof head);
		std::memset(dis, 0x3f ,sizeof dis);
		dis[S] = 0; q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && dis[to[e]] > dis[u] + w[e]) {
					dis[to[e]] = dis[u] + w[e];
					if (!vis[to[e]]) {
						vis[to[e]] = 1;
						q.emplace(to[e]);
					}
				}
		}
		return dis[T] != 0x3f3f3f3f3f3f3f3f;
	}
	int dfs(int u, int flow, i64 &cost)
	{
		if (u == T) {
			cost += 1ll * flow * dis[T];
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && !vis[to[e]] && dis[to[e]] == dis[u] + w[e]) {
				int tmp = dfs(to[e], std::min(rest, fl[e]), cost);
				if (!tmp) dis[to[e]] = 0x3f3f3f3f3f3f3f3f;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		vis[u] = 0;
		return flow - rest;
	}
	void main(int &res, i64 &cost)
	{
		while (SPFA()) {
			res += dfs(S, INT_MAX, cost);
		}
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		addFlow(S, i << 1, 1, 0);
		addFlow(i << 1 | 1, T, 1, 0);
	}
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		addFlow(S, i << 1 | 1, 1, a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		if (u > v) std::swap(u, v);
		addFlow(u << 1, v << 1 | 1, 1, w);
	}
	int res = 0; i64 cost = 0;
	dinic::main(res, cost);
	printf("%lld\n", cost);
	return 0;
}
