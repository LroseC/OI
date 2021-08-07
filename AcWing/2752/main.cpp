#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = N * 3;

int n, m, new_node, ans;
int idx = 1, origin_head[N], head[N], nex[M], to[M], w[M];
int d[N], s[N];
int low[N], dfn[N], cnt;
int fu[N], fw[N];
int q[N], f[N];

void AddEdge(int *h, int u, int v, int val)
{
	nex[++idx] = h[u], w[idx] = val;
	h[u] = idx; to[idx] = v;
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
	for (int i = v; i != u; i = fu[i])
		AddEdge(head, new_node, i, min(s[i], sum - s[i]));
}

void tarjan(int u, int from)
{
	dfn[u] = low[u] = ++cnt;
	for (int e = origin_head[u]; e; e = nex[e]) {
		int v = to[e];
		if (!dfn[v]) {
			fu[v] = u, fw[v] = w[e];
			tarjan(v, e);
			low[u] = min(low[u], low[v]);
			if (dfn[u] < low[v]) AddEdge(head, u, v, w[e]);
		}
		else if (e != (from ^ 1)) low[u] = min(low[u], dfn[v]);
	}
	for (int e = origin_head[u]; e; e = nex[e]) {
		int v = to[e];
		if (dfn[u] < dfn[v] && fu[v] != u) build_circle(u, v, w[e]);
	}
}

int dfs(int u)
{
	int d1 = 0, d2 = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		int tmp = dfs(v) + w[e];
		if (tmp >= d1) d2 = d1, d1 = tmp;
		else if (tmp > d2) d2 = tmp;
	}

	f[u] = d1;

	if (u <= n) ans = max(ans, d1 + d2);
	else {
		int sz = 0;
		int hh = 0, tt = -1;
		d[++sz] = -1e9;
		for (int e = head[u]; e; e = nex[e]) {
			int v = to[e];
			d[++sz] = f[v];
		}
		for (int i = 1; i <= sz; ++i) d[i + sz] = d[i];
		for (int i = 1; i <= (sz << 1); ++i) {
			while (hh <= tt && i - q[hh] > sz / 2) ++hh;
			if (hh <= tt) ans = max(ans, d[i] + i + d[q[hh]] - q[hh]);
			while (hh <= tt && d[i] - i >= d[q[tt]] - q[tt]) --tt;
			q[++tt] = i;
		}
	}

	return f[u];
}

int main(void)
{
	scanf("%d%d", &n, &m);
	new_node = n;
	for (int i = 1; i <= m; ++i) {
		int k, x, y;
		scanf("%d%d", &k, &x);
		for (int i = 1; i < k; ++i) {
			scanf("%d", &y);
			AddEdge(origin_head, x, y, 1);
			AddEdge(origin_head, y, x, 1);
			x = y;
		}
	}
	tarjan(1, 0);
	dfs(1);

	printf("%d\n", ans);
	return 0;
}