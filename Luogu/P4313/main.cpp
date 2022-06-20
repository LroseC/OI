#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>

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
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};
const int N = 1e5 + 10, M = 1e6 + 10;

int n, m, S = N - 1, T = N - 2, idx = 1, cnt;
int head[N], to[M], fl[M], nex[M];

namespace dinic
{
	int d[N], now[N];

	bool BFS(void)
	{
		std::queue<int> q;
		std::memset(d, 0, sizeof d);
		std::memcpy(now, head, sizeof head);
		q.emplace(S); d[S] = 1;
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && d[to[e]] == 0) {
					d[to[e]] = d[u] + 1;
					if (to[e] == T) return 1;
					q.emplace(to[e]);
				}
		}
		return 0;
	}
	i64 dfs(int u, i64 flow)
	{
		if (u == T) return flow;
		i64 rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && d[to[e]] == d[u] + 1) {
				now[u] = e;
				i64 tmp = dfs(to[e], std::min((i64)fl[e], rest));
				if (!tmp) d[to[e]] = 0;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		return flow - rest;
	}
	i64 main(void)
	{
		i64 res = 0;
		while (BFS()) {
			res += dfs(S, LLONG_MAX);
		}
		return res;
	}
}

inline int getId(int x, int y) { return (x - 1) * m + y; }
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
int main(void)
{
	read >> n >> m;
	i64 res = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int x; read >> x;
			res += x;
			addFlow(S, getId(i, j), x);
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int x; read >> x;
			res += x;
			addFlow(getId(i, j), T, x);
		}
	cnt = getId(n, m);
	const int inf = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int x; read >> x;
			res += x;
			int u = ++cnt;
			addFlow(S, u, x);
			addFlow(u, getId(i, j), inf);
			for (int k = 0; k < 4; ++k) {
				int xx = i + gox[k];
				int yy = j + goy[k];
				if (xx >= 1 && xx <= n && yy >= 1 && yy <= m) {
					addFlow(u, getId(xx, yy), inf);
				}
			}
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int x; read >> x;
			res += x;
			int u = ++cnt;
			addFlow(u, T, x);
			addFlow(getId(i, j), u, inf);
			for (int k = 0; k < 4; ++k) {
				int xx = i + gox[k];
				int yy = j	 + goy[k];
				if (xx >= 1 && xx <= n && yy >= 1 && yy <= m) {
					addFlow(getId(xx, yy), u, inf);
				}
			}
		}
	printf("%lld\n", res - dinic::main());
	return 0;
}
