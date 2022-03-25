#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>

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

const int N = 1e5, M = 1e6, INF = 1e9;

int n, m, K, S = N - 1, T = N - 2;
int fa[100];
int shipLimit[100];
std::vector<int> shipStop[100];
int idx = 1, head[N], nex[M], to[M], f[M];

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
			res += dfs(S, INT_MAX);
		return res;
	}
}

void build(int tim)
{
	for (int i = 0; i < n; ++i)
		addFlow(i + n * (tim - 1), i + n * tim, INF);
	for (int i = 1; i <= m; ++i) {
		int vpos = tim % shipStop[i].size();
		int upos = vpos - 1 == -1 ? shipStop[i].size() - 1 : vpos - 1;
		int u = shipStop[i][upos], v = shipStop[i][vpos];
		if (u != n)
			addFlow(u + n * (tim - 1), v == n ? T : v + n * tim, shipLimit[i]);
	}
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int u, int v) { fa[find(u)] = find(v); }
int main(void)
{
	read >> n >> m >> K;
	++n;
	for (int i = 0; i < 100; ++i)
		fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		read >> shipLimit[i];
		int x; read >> x;
		shipStop[i].resize(x);
		for (int j = 0; j < x; ++j) {
			read >> shipStop[i][j];
			if (shipStop[i][j] == -1)
				shipStop[i][j] = n;
		}
		for (int j = 1; j < x; ++j)
			merge(shipStop[i][j], shipStop[i][j - 1]);
	}
	if (find(0) != find(n)) {
		puts("0");
		return 0;
	}
	int tim = 0, res = 0;
	addFlow(S, 0, K);
	while (res < K) {
		build(++tim);
		res += Dinic::main();
	}
	printf("%d\n", tim);
	return 0;
}
