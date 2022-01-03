#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

struct PII
{
	int x, y;
	PII(void) { x = y = 0; }
	PII(int x, int y) : x(x), y(y) {}
	bool operator<(const PII &other) const
	{
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};
struct Edge
{
	int u, v, length, height;
	Edge(void) { u = v = length = height = 0; }
	Edge(int u, int v, int length, int height) : u(u), v(v), length(length), height(height) {}
	bool operator<(const Edge &other) const
	{
		return height > other.height;
	}
};

const int N = 2e6 + 10, M = 4e6 + 10, LOG = 22;

int T;
int n, m, nodecnt;
int dep[N + M], dis[N + M], fa[N + M][LOG];
int oriid[N + M];
Edge edge[M];
vector<PII> G[N + M];

namespace UnionFind
{
	int fa[N + M];
	void init(int n)
	{
		for (int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if (x == y) return;
		fa[x] = y;
	}
}

void Dijkstra(void)
{
	priority_queue<PII> heap;
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0; heap.emplace(0, 1);
	while (heap.size()) {
		auto t = heap.top(); heap.pop();
		int u = t.y;
		for (auto e : G[u]) {
			int v = e.x, w = e.y;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				heap.emplace(dis[v], v);
			}
		}
	}
}

namespace Kruskal
{
	int LCA(int u, int limit)
	{
		for (int k = LOG - 1; k >= 0; --k)
			if (dep[fa[u][k]] && edge[oriid[fa[u][k]]].height > limit)
				u = fa[u][k];
		return dis[u];
	}
	void dfs(int u, int fath, int depth)
	{
		dep[u] = depth;
		for (int k = 1; k < LOG; ++k)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];
		for (auto t : G[u]) {
			int v = t.x;
			if (v == fath) continue;
			fa[v][0] = u;
			dfs(v, u, depth + 1);
			dis[u] = min(dis[u], dis[v]);
		}
	}
	int build(void)
	{
		for (int i = 1; i <= n + m; ++i) G[i].clear();
		for (int i = 1; i <= m; ++i) {
			int u = UnionFind::find(edge[i].u), v = UnionFind::find(edge[i].v);
			if (u != v) {
				++nodecnt;
				UnionFind::merge(u, nodecnt);
				UnionFind::merge(v, nodecnt);
				G[nodecnt].emplace_back(u, 0);
				G[nodecnt].emplace_back(v, 0);
				oriid[nodecnt] = i;
			}
		}
		dfs(nodecnt, nodecnt, 1);
		return 0;
	}
}

int work(void)
{
	cin >> n >> m;
	nodecnt = n;
	UnionFind::init(n + m);
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
	}
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].u >> edge[i].v >> edge[i].length >> edge[i].height;
		G[edge[i].u].emplace_back(edge[i].v, edge[i].length);
		G[edge[i].v].emplace_back(edge[i].u, edge[i].length);
	}
	Dijkstra();
	sort(edge + 1, edge + 1 + m);
	Kruskal::build();
	int Q, K, S; cin >> Q >> K >> S;
	int lastans = 0;
	for (int i = 1; i <= Q; ++i) {
		int v, p; cin >> v >> p;
		v = (v + 1ll * K * lastans - 1) % n + 1;
		p = (p + 1ll * K * lastans) % (S + 1);
		printf("%d\n", lastans = Kruskal::LCA(v, p));
	}
	return 0;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> T;
	while (T--) work();
	return 0;
}
