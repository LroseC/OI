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

const int N = 1e5 + 10, M = 1e6 + 10, INF = 1e9;

int n, m, S = N - 1, T = N - 2;
int G[50][50];
int idx = 1, head[N], nex[M], to[M], fl[M], w[M];

inline int getId(int x, int y, int type)
{
	int res = (x - 1) * m + y;
	return res << 1 | type;
}
inline std::pair<int, int> getPos(int id)
{
	id >>= 1;
	int x = id / m, y = id - x * m;
	if (!y) --x, y = m;
	return std::make_pair(x + 1, y);
}
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

namespace Dinic
{
	bool vis[N];
	int dis[N], now[N];

	bool SPFA(void)
	{
		std::queue<int> q;
		std::memset(dis, 0xcf, sizeof dis);
		std::memcpy(now, head, sizeof head);
		dis[S] = 0;
		q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && dis[to[e]] < dis[u] + w[e]) {
					dis[to[e]] = dis[u] + w[e];
					if (!vis[to[e]]) {
						vis[to[e]] = 1;
						q.emplace(to[e]);
					}
				}
		}
		return dis[T] != 0xcfcfcfcf;
	}
	int dfs(int u, int flow, int &cost)
	{
		if (u == T) {
			cost += dis[T] * flow;
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && dis[to[e]] == dis[u] + w[e] && !vis[to[e]]) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(rest, fl[e]), cost);
				if (!tmp) dis[to[e]] = 0xcfcfcfcf;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		vis[u] = 0;
		return flow - rest;
	}
	int main(int &res, int &cost)
	{
		while (SPFA())
			res += dfs(S, INT_MAX, cost);
		return 0;
	}
}

void dfs(int id, int x, int y)
{
	if (x == n && y == m)
		return;
	int u = getId(x, y, 1);
	for (int e = head[u]; e; e = nex[e])
		if (fl[e ^ 1]) {
			auto t = getPos(to[e]);
			if (t.first == x && t.second == y + 1) printf("%d 1\n", id);
			else if (t.second == y && t.first == x + 1) printf("%d 0\n", id);
			else continue;
			--fl[e ^ 1];
			dfs(id, t.first, t.second);
			return;
		}
}

int main(void)
{
	int x; read >> x;
	addFlow(S, getId(1, 1, 0), x, 0);
	read >> m >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			read >> G[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			auto t1 = getPos(getId(i, j, 0));
			auto t2 = getPos(getId(i, j, 1));
			if (t1 != t2) return -1;
			if (t1.first != i && t1.second != j) return -1;
			if (G[i][j] == 1) continue;
			if (G[i][j] == 2) addFlow(getId(i, j, 0), getId(i, j, 1), 1, 1);
			addFlow(getId(i, j, 0), getId(i, j, 1), INF, 0);
			if (i != n && G[i + 1][j] != 1)
				addFlow(getId(i, j, 1), getId(i + 1, j, 0), INF, 0);
			if (j != m && G[i][j + 1] != 1)
				addFlow(getId(i, j, 1), getId(i, j + 1, 0), INF, 0);
		}
	addFlow(getId(n, m, 1), T, x, 0);
	int res = 0, cost = 0;
	Dinic::main(res, cost);
	for (int i = 1; i <= res; ++i)
		dfs(i, 1, 1);
	return 0;
}
