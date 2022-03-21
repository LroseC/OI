#include <vector>
#include <cctype>
#include <cstdio>
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

const int N = 1e4 + 10, M = 5e4 + 10, LG = 20;

namespace UnionFind
{
	int fa[N + M];
	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i;
	}
}
int find(int x)
{
	using namespace UnionFind;
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

struct Edge
{
	int u, v, w;
	bool operator<(const Edge &other) const
	{
		return w > other.w;
	}
};

int n, m, q, idx;
bool vis[N + M];
int dep[N + M], w[N + M];
int fa[N + M][LG];
std::vector<Edge> edge;
std::vector<int> G[N + M];

void getFa(int u)
{
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			getFa(v);
		}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}

int main(void)
{
	read >> n >> m;
	idx = n;
	UnionFind::init(n);
	edge.resize(m);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		read >> edge[i].u >> edge[i].v >> edge[i].w;
	}
	std::sort(edge.begin(), edge.end());
	for (int i = 0; i < m; ++i) {
		int u = find(edge[i].u), v = find(edge[i].v);
		if (u != v) {
			UnionFind::fa[u] = UnionFind::fa[v] = ++idx;
			UnionFind::fa[idx] = idx;
			G[idx].emplace_back(u);
			G[idx].emplace_back(v);
			w[idx] = edge[i].w;
		}
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[find(i)]) {
			vis[find(i)] = 1;
			getFa(find(i));
		}
	read >> q;
	for (int i = 0; i < q; ++i) {
		int u, v; read >> u >> v;
		if (find(u) != find(v)) {
			puts("-1");
			continue;
		}
		int d = LCA(u, v);
		printf("%d\n", w[d]);
	}
	return 0;
}
