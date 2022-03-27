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

using i64 = long long;
const int N = 1e4, M = 1e5;

int n, m, S = N - 1, T = N - 2;
char tmp[100010];
int idx = 1, head[N], nex[M], to[M];
i64 f[M];

void addEdge(int u, int v, i64 fi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, f[idx] = fi;
}
void addFlow(int u, int v, i64 f)
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
	i64 dfs(int u, i64 flow)
	{
		if (u == T)
			return flow;
		i64 rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (f[e] && d[to[e]] == d[u] + 1) {
				now[u] = e;
				i64 tmp = dfs(to[e], std::min(f[e], rest));
				if (!tmp) d[to[e]] = 0;
				rest -= tmp;
				f[e] -= tmp;
				f[e ^ 1] += tmp;
			}
		return flow - rest;
	}
	i64 main(void)
	{
		i64 res = 0;
		while (BFS())
			res += dfs(S, LLONG_MAX);
		return res;
	}
}

int main(void)
{
	read >> m >> n;
	i64 res = 0;
	for (int i = 1; i <= m; ++i) {
		int w; read >> w;
		addFlow(S, i, w);
		res += w;
		int top = 0;
		do tmp[++top] = getchar();
		while (tmp[top] != '\n' && tmp[top] != '\r');
		int pos = 0;
		while (pos < top) {
			int res = 0; int f = 1; char ch = tmp[++pos];
			while (pos < top && !isdigit(ch)) { if (ch == '-') f = -1; ch = tmp[++pos]; }
			while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = tmp[++pos]; }
			addFlow(i, m + res, 0x3f3f3f3f3f3f3f3f);
		}
	}
	for (int i = 1; i <= n; ++i) {
		int w; read >> w;
		addFlow(i + m, T, w);
	}
	res -= Dinic::main();
	for (int i = 1; i <= m; ++i)
		if (Dinic::d[i]) printf("%d ", i);
	puts("");
	for (int i = 1; i <= n; ++i)
		if (Dinic::d[i + m]) printf("%d ", i);
	puts("");
	printf("%lld\n", res);
	return 0;
}
