#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>

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

const int N = 1010, M = 1e6 + N + 10;

int S, T;
int n, m, edgecnt;
int idx = 1, head[N], nex[M], to[M], w[M];

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v; w[idx] = wi;
}

namespace Dinic
{
	queue<int> q, EMPTY;
	int now[N], dis[N];
	bool BFS(void)
	{
		memset(dis, 0, sizeof dis);
		q = EMPTY; q.emplace(S);
		dis[S] = 1; now[S] = head[S];
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int e = head[u]; e; e = nex[e])
				if (!dis[to[e]] && w[e]) {
					q.emplace(to[e]);
					dis[to[e]] = dis[u] + 1;
					now[to[e]] = head[to[e]];
					if (to[e] == T) return 1;
				}
		}
		return 0;
	}
	int dfs(int u, int flow)
	{
		if (u == T) return flow;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e]) {
			now[u] = e;
			if (w[e] && dis[to[e]] == dis[u] + 1) {
				int tmp = dfs(to[e], min(rest, w[e]));
				if (tmp == 0) dis[to[e]] = 0;
				w[e] -= tmp;
				w[e ^ 1] += tmp;
				rest -= tmp;
			}
		}
		return flow - rest;
	}
	int main(void)
	{
		int res = 0;
		while (BFS()) {
			res += dfs(S, INT_MAX);
		}
		return res;
	}
}

int main(void)
{
	IO >> n >> m >> edgecnt;
	m += n;
	S = m + 1, T = m + 2;
	for (int i = 1; i <= n; ++i) {
		AddEdge(S, i, 1);
		AddEdge(i, S, 0);
	}
	for (int i = n + 1; i <= m; ++i) {
		AddEdge(i, T, 1);
		AddEdge(T, i, 0);
	}
	for (int i = 1; i <= edgecnt; ++i) {
		int u, v; IO >> u >> v;
		AddEdge(u, v + n, 1);
		AddEdge(v + n, u, 0);
	}
	printf("%d\n", Dinic::main());
	return 0;
}
