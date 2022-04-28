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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

const int N = 50010, M = N << 1;

int n, m, S = N - 1, T = N - 2;
int idx = 1;
int head[N], nex[M], to[M], fl[M];
int dfnCnt, dfn[N], low[N];
int top, stk[N];
bool instk[N], isKey[N];
int sccCnt, id[N];

void addEdge(int u, int v, int f)
{
	nex[++idx] = head[u];
	head[u] = idx;
	fl[idx] = f, to[idx] = v;
}
void addFlow(int u, int v, int f)
{
	addEdge(u, v, f);
	addEdge(v, u, 0);
}

namespace dinic
{
	int d[N], now[N];

	bool BFS(void)
	{
		std::queue<int> q;
		std::memset(d, 0, sizeof d);
		std::memcpy(now, head, sizeof head);
		d[S] = 1; q.emplace(S);
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

void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++dfnCnt;
	instk[u] = 1;
	stk[++top] = u;
	for (int e = head[u]; e; e = nex[e])
		if (fl[e] && to[e] != fa) {
			if (!dfn[to[e]]) {
				tarjan(to[e], u);
				low[u] = std::min(low[u], low[to[e]]);
			}
			else if (instk[to[e]])
				low[u] = std::min(low[u], dfn[to[e]]);
		}
	if (low[u] == dfn[u]) {
		int tmp;
		++sccCnt;
		do {
			tmp = stk[top--];
			instk[tmp] = 0;
			id[tmp] = sccCnt;
		} while(tmp != u);
	}
}

int main(void)
{
	read >> n >> m;
	S = n * 2 + 1, T = S + 1;
	for (int i = 1, u, v; i <= m; ++i) {
		read >> u >> v;
		addFlow(u, v + n, 1);
	}
	for (int i = 1; i <= n; ++i) {
		addFlow(S, i, 1);
		addFlow(i + n, T, 1);
	}
	dinic::main();
	for (int i = 1; i <= T; ++i)
		if (!dfn[i])
			tarjan(i, i);
	for (int e = head[S]; e; e = nex[e])
		if (!fl[e] && id[S] != id[to[e]])
			isKey[to[e]] = 1;
	for (int i = 1; i <= n; ++i)
		puts(isKey[i] ? "Slavko" : "Mirko");
	return 0;
}
