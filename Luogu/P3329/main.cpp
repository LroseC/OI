#include <queue>
#include <vector>
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
const int N = 200, M = 12010;

struct Edge
{
	int u, v;
	i64 w;

	Edge(void) {}
	Edge(int _u, int _v, int _w) { u = _u, v = _v, w = _w; }
	bool operator<(const Edge &other) const { return w > other.w; }
};

int n, m, S, T;
int a[N], a1[N], a2[N], sz[N], fa[N];
int idx = 1, head[N], nex[M], to[M];
i64 ofl[M], fl[M];
std::vector<Edge> edge;

void clear(void)
{
	idx = 1;
	std::memset(head, 0, sizeof head);
	edge.clear();
}
void addEdge(int u, int v, i64 f)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, fl[idx] = f;
}
void addFlow(int u, int v, i64 f)
{
	addEdge(u, v, f);
	addEdge(v, u, 0);
}
void addTree(int u, int v, i64 w)
{
	edge.emplace_back(u, v, w);
}

namespace dinic
{
	int now[N], d[N];

	bool BFS(void)
	{
		std::queue<int> q;
		std::memset(d, 0, sizeof d);
		std::memcpy(now, head, sizeof head);
		q.emplace(S); d[S] = 1;
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
	i64 dfs(int u, i64 flow)
	{
		if (u == T)
			return flow;
		i64 rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && d[to[e]] == d[u] + 1) {
				now[u] = e;
				i64 tmp = dfs(to[e], std::min(fl[e], rest));
				if (!tmp) d[to[e]] = 0;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		return flow - rest;
	}
	i64 main(void)
	{
		std::memcpy(fl, ofl, sizeof ofl);
		i64 res = 0;
		while (BFS())
			res += dfs(S, LLONG_MAX);
		return res;
	}
}

void build(int l, int r)
{
	if (l == r)
		return;
	S = a[l], T = a[r];
	addTree(a[l], a[r], dinic::main());
	int cnt1 = 0, cnt2 = 0;
	for (int i = l; i <= r; ++i) {
		if (dinic::d[a[i]]) a1[++cnt1] = a[i];
		else a2[++cnt2] = a[i];
	}
	int mid = l + cnt1 - 1;
	for (int i = l; i <= r; ++i) {
		if (cnt1) a[i] = a1[cnt1--];
		else a[i] = a2[cnt2--];
	}
	build(l, mid);
	build(mid + 1, r);
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int query(i64 x)
{
	for (int i = 1; i <= n; ++i) {
		sz[i] = 1;
		fa[i] = i;
	}
	int res = 0;
	return res;
	for (auto e : edge) {
		int u = find(e.u), v = find(e.v);
		if (e.w <= x)
			res += sz[u] * sz[v];
		fa[u] = v;
		sz[v] += sz[u];
	}
	return res;
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n >> m;
		for (int i = 1; i <= m; ++i) {
			int u, v; i64 w;
			read >> u >> v >> w;
			addFlow(u, v, w);
			addFlow(v, u, w);
		}
		for (int i = 1; i <= n; ++i)
			a[i] = i;
		build(1, n);
		std::sort(edge.begin(), edge.end());
		int Q; read >> Q;
		while (Q--) {
			int x; read >> x;
			printf("%d\n", query(x));
		}
		clear();
		puts("");
	}
	return 0;
}
