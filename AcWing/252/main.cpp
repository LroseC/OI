#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = N * 2;

int n, m;
int ans, all_node;
bool vis[N];
int idx, head[N], nex[M], to[M], w[M];
int f[N], dis[N];

void Add_Edge(int u, int v, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
	w[idx] = wi;
}
int get_root(int u, int fa, int &root, int &minsize)
{
	int size = 0; f[u] = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		int tmp = get_root(v, u, root, minsize);
		size = max(tmp, size);
		f[u] += tmp;
	}
	size = max(size, all_node - f[u]);
	if (size < minsize) {
		root = u;
		minsize = size;
	}
	return f[u];
}
void get_dis(int u, int fa, int dist)
{
	dis[++dis[0]] = dist;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		get_dis(v, u, dist + w[e]);
	}
}
int calc(int u, int d)
{
	int res = 0;
	dis[0] = 0;
	get_dis(u, -1, d);
	sort(dis + 1, dis + 1 + dis[0]);
	int l = 1, r = dis[0];
	while (l < r) {
		if (dis[r] + dis[l] <= m) {
			res += r - l;
			++l;
		}
		else --r;
	}
	return res;
}
void dfs(int u)
{
	vis[u] = 1;
	ans += calc(u, 0);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		ans -= calc(v, w[e]);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		int root, minsize = INT_MAX;
		all_node = f[v];
		get_root(v, u, root, minsize);
		dfs(root);
	}
}

int main(void)
{
	while (scanf("%d%d", &n, &m), n || m) {
		ans = 0;
		memset(f, 0, sizeof f);
		memset(vis, 0, sizeof vis);
		memset(head, 0, sizeof head);
		all_node = n;
		int root, minsize = INT_MAX;
		for (int i = 1; i < n; ++i) {
			int u, v, wi;
			scanf("%d%d%d", &u, &v, &wi);
			Add_Edge(u, v, wi);
			Add_Edge(v, u, wi);
		}
		get_root(1, -1, root, minsize);
		dfs(root);
		printf("%d\n", ans);
	}
	return 0;
}