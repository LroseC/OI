#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 12010, M = N * 3;

int n, m, q;
int idx = 1, origin_head[N], head[N], nex[M], to[M], w[M];
int new_node;
int cnt, low[N], dfn[N], fu[N], fw[N];
int s[N];
int fa[N][14], d[N], dep[N];
int A, B;

void AddEdge(int *h, int u, int v, int wi)
{
	nex[++idx] = h[u], to[idx] = v;
	h[u] = idx, w[idx] = wi;
}

void build_circle(int u, int v, int sum)
{
	for (int i = v; i != u; i = fu[i]) {
		s[i] = sum;
		sum += fw[i];
	}
	s[u] = sum;
	AddEdge(head, u, ++new_node, 0);
	s[new_node] = sum;
	for (int i = v; i != u; i = fu[i]) {
		AddEdge(head, new_node, i, min(s[i], sum - s[i]));
	}
}

void tarjan_dfs(int u, int from)
{
	low[u] = dfn[u] = ++cnt;
	for (int e = origin_head[u]; e; e = nex[e]) {
		int v = to[e];
		if (!dfn[v]) {
			fu[v] = u, fw[v] = w[e];
			tarjan_dfs(v, e);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) AddEdge(head, u, v, w[e]);
		}
		else if (e != (from ^ 1)) low[u] = min(low[u], dfn[v]);
	}
	for (int e = origin_head[u]; e; e = nex[e]) {
		int v = to[e];
		if (fu[v] != u && dfn[u] < dfn[v])
			build_circle(u, v, w[e]);
	}
}
void lca_dfs(int u, int father)
{
	fa[u][0] = father;
	for (int k = 1; k <= 13; ++k)
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		d[v] = d[u] + w[e];
		dep[v] = dep[u] + 1;
		lca_dfs(v, u);
	}
}
int lca(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	for (int k = 13; k >= 0; --k)
		if (dep[fa[a][k]] >= dep[b]) a = fa[a][k];
	if (a == b) return a;
	for (int k = 13; k >= 0; --k)
		if (fa[a][k] != fa[b][k]) a = fa[a][k], b = fa[b][k];
	A = a, B = b;
	return fa[a][0];
}

int main(void)
{
	scanf("%d%d%d", &n, &m, &q);
	new_node = n;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(origin_head, u, v, w);
		AddEdge(origin_head, v, u, w);
	}
	tarjan_dfs(1, 0);
	lca_dfs(1, 0);

	for (int i = 1; i <= q; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		int p = lca(u, v);
		if (p <= n) printf("%d\n", d[u] + d[v] - 2 * d[p]);
		else {
			int res = d[u] + d[v] - d[A] - d[B];
			int l = abs(s[A] - s[B]);
			res += min(l, s[p] - l);
			printf("%d\n", res);
		}
	}

	return 0;
}