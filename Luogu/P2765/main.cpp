#include <queue>
#include <cmath>
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

const int N = 1e5, M = 1e6;

int n, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], f[M];
bool vis[M];

void clear(void)
{
	idx = 1;
	std::memset(head, 0, sizeof head);
	std::memset(nex, 0, sizeof head);
	std::memset(to, 0, sizeof head);
	std::memset(f, 0, sizeof head);
}
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
			res += dfs(S, 0x3f3f3f3f);
		return res;
	}
}
void getPath(int u)
{
	vis[u] = 1;
	printf("%d ", u);
	for (int e = head[u << 1]; e; e = nex[e])
		if (to[e] != S && !f[e]) getPath(to[e] >> 1);
}

int main(void)
{
	read >> n;
	int res = 0, ans = 0;
	while (ans - res <= n) {
		++ans;
		int tmp = sqrt(ans) + 1;
		addFlow(S, ans << 1, 1);
		addFlow(ans << 1 | 1, T, 1);
		while (tmp * tmp < ans * 2) {
			int t = tmp * tmp - ans;
			addFlow(t << 1, ans << 1 | 1, 1);
			++tmp;
		}
		res += Dinic::main();
	}
	--ans;
	clear();
	for (int i = 1; i <= ans; ++i) {
		int tmp = sqrt(i) + 1;
		addFlow(S, i << 1, 1);
		addFlow(i << 1 | 1, T, 1);
		while (tmp * tmp < i * 2) {
			int t = tmp * tmp - i;
			addFlow(t << 1, i << 1 | 1, 1);
			++tmp;
		}
	}
	Dinic::main();
	printf("%d\n", ans);
	for (int i = 1; i <= ans; ++i)
		if (!vis[i]) {
			getPath(i);
			puts("");
		}
	return 0;
}
