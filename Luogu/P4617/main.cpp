#include <cctype>
#include <cstdio>

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

namespace dinic
{
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
			else
				low[u] = std::min(low[u], dfn[to[e]]);
		}
	if (low[u] == dfn[u]) {
		int tmp;
		++sccCnt;
		do {
			tmp = stk[top--];
			id[tmp] = sccCnt;
		} while(tmp != u);
	}
}

int main(void)
{
	read >> n >> m;
	S = n * 2 + 1, T = S + 1;
	for (int i = 1; i <= m; ++i) {
		read >> u >> v;
		addFlow(u, v + n, 1);
	}
	for (int i = 1; i <= n; ++i) {
		addFlow(S, u, 1);
		addFlow(v, T, 1);
	}
	dinic::main();
	for (int i = 1; i <= T; ++i)
		if (!dfn[i])
			tarjan(i, i);
	return 0;
}
