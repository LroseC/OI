#include <queue>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>

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

using LL = long long;
const int N = 210, M = 1e4 + 10;

int idx = 1;
int head[N], nex[M], to[M], w[M];
int n, m, S, T;

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v; w[idx] = wi;
}

namespace Dinic
{
	int dis[N], now[N];
	queue<int> q;
	bool BFS(void)
	{
		memset(dis, 0, sizeof dis);
		while (q.size()) q.pop();
		dis[S] = 1; now[S] = head[S]; q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int e = head[u]; e; e = nex[e])
				if (!dis[to[e]] && w[e]) {
					q.emplace(to[e]);
					now[to[e]] = head[to[e]];
					dis[to[e]] = dis[u] + 1;
					if (to[e] == T) return 1;
				}
		}
		return 0;
	}
	int dfs(int u, int flow)
	{
		if (u == T) return flow;
		int rest = flow;
		for (int e = now[u]; e && rest; e = nex[e])
			if (w[e] && dis[u] + 1 == dis[to[e]]) {
				int tmp = dfs(to[e], min(rest, w[e]));
				if (!tmp) dis[to[e]] = 0;
				w[e] -= tmp;
				w[e ^ 1] += tmp;
				rest -= tmp;
			}
		return flow - rest;
	}
	LL main(void)
	{
		LL res = 0;
		while (BFS()) res += dfs(S, INT_MAX);
		return res;
	}
}

int main(void)
{
	IO >> n >> m >> S >> T;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		IO >> u >> v >> w;
		AddEdge(u, v, w);
		AddEdge(v, u, 0);
	}
	printf("%lld\n", Dinic::main());
	return 0;
}
