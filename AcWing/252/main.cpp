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
int f[N];

void Add_Edge(int u, int v, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
	w[idx] = wi;
}
int get_root(int u, int fa, int &root, int &minsize)
{
	if (vis[u]) return;;
	f[u] = 1; int maxson = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		int tmp = get_root(v, u, root, minsize);
		maxson = max(tmp, maxson);
		f[u] += tmp;
	}
	maxson = max(maxson, all_node - f[u]);
	return f[u];
}
void dfs(int u)
{
	if (st[u]) return;
	vis[u] = 1;
	ans += calc(0, u);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		ans -= calc(w[e], v);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		dfs(v);
	}
}

int main(void)
{
	while (scanf("%d%d", &n, &m), n || m) {
		ans = 0;
		memset(vis, 0, sizeof vis);
		all_node = n;
		int root, minsize = INT_MAX;
		for (int i = 1; i < n; ++i) {
			int u, v, wi;
			scanf("%d%d%d", &u, &v, &wi);
			Add_Edge(u, v, wi);
		}
		get_root(1, -1, root, minsize);
		dfs(root);
		printf("%d\n", ans);
	}
	return 0;
}