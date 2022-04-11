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
const int N = 10100, M = 30100, LG = 16;

struct Edge
{
	int v, w;

	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n, m, S, T;
int idx = 1, head[N], nex[M], to[M], ofl[M], fl[M];
int dep[N], fa[N][LG], minx[N][LG];
std::vector<Edge> G[N];

void addEdge(int u, int v, int f)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, ofl[idx] = f;
}
void addFlow(int u, int v, int f)
{
	addEdge(u, v, f);
	addEdge(v, u, 0);
}
void addTree(int u, int v, int w)
{
	G[u].emplace_back(v, w);
	G[v].emplace_back(u, w);
}

namespace dinic
{
	int now[N], d[N];
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
				int tmp = dfs(to[e], std::min(fl[e], rest));
				if (!tmp) d[to[e]] = 0;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		return flow - rest;
	}
	int main(void)
	{
		std::memcpy(fl, ofl, sizeof ofl);
		int res = 0;
		while (BFS())
			res += dfs(S, INT_MAX);
		return res;
	}
}

int a[N], a1[N], a2[N];
void build(int l, int r)
{
	if (l == r) return;
	S = a[l], T = a[r];
	addTree(S, T, dinic::main());
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
void initLCA(int u, int depth)
{
	dep[u] = depth;
	for (int i = 1; i < LG; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		minx[u][i] = std::min(minx[u][i - 1], minx[fa[u][i - 1]][i - 1]);
	}
	for (auto t : G[u])
		if (t.v != fa[u][0]) {
			fa[t.v][0] = u;
			minx[t.v][0] = t.w;
			initLCA(t.v, depth + 1);
		}
}
int query(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	int res = INT_MAX;
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) {
			res = std::min(res, minx[u][i]);
			u = fa[u][i];
		}
	if (u == v) return res;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			res = std::min(res, minx[u][i]);
			res = std::min(res, minx[v][i]);
			u = fa[u][i], v = fa[v][i];
		}
	res = std::min(res, minx[u][0]);
	res = std::min(res, minx[v][0]);
	return res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		addFlow(u, v, w);
		addFlow(v, u, w);
	}
	for (int i = 0; i <= n; ++i)
		a[i] = i;
	build(1, n);
	initLCA(1, 1);
	int Q; read >> Q;
	while (Q--) {
		int u, v;
		read >> u >> v;
		printf("%d\n", query(u, v));
	}
	return 0;
}
