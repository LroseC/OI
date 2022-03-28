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

const int N = 1e6 + 10, M = 3e6 + 10;
int gox[] = {1, 2, 2, 1, -1, -2, -2, -1};
int goy[] = {2, 1, -1, -2, -2, -1, 1, 2};

int n, m, S = N - 1, T = N - 2;
bool block[310][310];
int idx = 1, head[N], nex[M], to[M], fl[M];

void addEdge(int u, int v, int f)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, fl[idx] = f;
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
				if (fl[e] && !d[to[e]]) {
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
			if (fl[e] && d[to[e]] == d[u] + 1) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(rest, fl[e]));
				if (!tmp) d[to[e]] = 0;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
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
inline int getId(int x, int y) { return (x - 1) * n + y; }

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y; read >> x >> y;
		block[x][y] = 1;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (block[i][j]) continue;
			if (i + j & 1) {
				addFlow(S, getId(i, j), 1);
				for (int t = 0; t < 8; ++t) {
					int xx = i + gox[t];
					int yy = j + goy[t];
					if (xx < 1 || yy < 1 || xx > n || yy > n || block[xx][yy]) continue;
					addFlow(getId(i, j), getId(xx, yy), 0x3f3f3f3f);
				}
			}
			else addFlow(getId(i, j), T, 1);
		}
	printf("%d\n", n * n - Dinic::main() - m);
	return 0;
}
