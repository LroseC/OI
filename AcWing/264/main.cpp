#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10, M = N << 1, S = 1e6 + 10;

int n, m, ans = INT_MAX, all_node;
int idx, head[N], nex[M], to[M], w[M];
bool vis[N]; int f[S], sz[N];

void Add_Edge(int u, int v, int wi)
{
	nex[++idx] = head[u]; w[idx] = wi;
	head[u] = idx, to[idx] = v;
}

int get_root(int u, int fa, int &root, int &minsize)
{
	int maxson = 0; sz[u] = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		int tmp = get_root(v, u, root, minsize);
		maxson = max(maxson, tmp);
		sz[u] += tmp;
	}
	maxson = max(maxson, all_node - sz[u]);
	if (maxson < minsize) {
		minsize = maxson;
		root = u;
	}
	return sz[u];
}
void calc(int u, int fa, int dist, int edgecnt)
{
	if (dist <= m)
		ans = min(ans, f[m - dist] + edgecnt);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		calc(v, u, dist + w[e], edgecnt + 1);
	}
}
void get_dis(int u, int fa, int dist, int edgecnt)
{
	if (dist <= m)
		f[dist] = min(f[dist], edgecnt);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		get_dis(v, u, dist + w[e], edgecnt + 1);
	}
}
void resume(int u, int fa, int dist, int edgecnt)
{
	if (dist <= m)
		f[dist] = 0x3f3f3f3f;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		resume(v, u, dist + w[e], edgecnt + 1);
	}
}
void dfs(int u)
{
	vis[u] = 1;
	f[0] = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		calc(v, u, w[e], 1);
		get_dis(v, u, w[e], 1);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		resume(v, u, w[e], 1);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		all_node = sz[v];
		int root, minsize = INT_MAX;
		get_root(v, u, root, minsize);
		dfs(root);
	}
}

int main(void)
{
	memset(f, 0x3f, sizeof f);
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; ++i) {
		int u, v, wi;
		scanf("%d%d%d", &u, &v, &wi);
		++u, ++v;
		Add_Edge(u, v, wi);
		Add_Edge(v, u, wi);
	}
	int root, minsize = INT_MAX;
	all_node = n;
	get_root(1, -1, root, minsize);
	dfs(root);
	printf("%d\n", ans >= 0x3f3f3f3f ? -1 : ans);
	return 0;
}