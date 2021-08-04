#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e4 + 10, M = 2e4 + 10;
inline int max(int a, int b) { return a > b ? a : b; }

namespace DFZ
{
	int ans = 0, all_node;
	int dis[N], t[N];
	bool vis[N];
	
	int dfs_getroot(int p, int fa, int *root, int *minsize);
	void dfs_getdis(int p, int fa, int d);
	int calc(int p, int d);
	int dfs(int p);
	int main(void);
}

int n, k, idx;
int head[N], nex[M], to[M], w[M];

void Add_Edge(int u, int v, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v;
	w[idx] = wi;
	return;
}

int DFZ::dfs_getroot(int p, int fa, int *root, int *minsize)
{
	#define dfs dfs_getroot
	int size = 0, tot = 1;
	for (int e = head[p]; e; e = nex[e]) {
		if (to[e] == fa || vis[to[e]]) continue;
		int tmp = dfs(to[e], p, root, minsize);
		size = max(size, tmp);
		tot += tmp;
	}
	size = max(size, all_node - tot);
	if (size < *minsize) {
		*minsize = size;
		*root = p;
	}
	return t[p] = tot;
	#undef dfs
}
void DFZ::dfs_getdis(int p, int fa, int d)
{
	#define dfs dfs_getdis
	dis[++dis[0]] = d;
	for (int e = head[p]; e; e = nex[e]) {
		if (to[e] == fa || vis[to[e]]) continue;
		dfs(to[e], p, d + w[e]);
	}
	return;
	#undef dfs
}
int DFZ::calc(int p, int d)
{
	int res = 0;
	memset(dis, 0, sizeof dis);
	dfs_getdis(p, 0, d);
	sort(dis + 1, dis + 1 + dis[0]);
	int l = 1, r = dis[0];
	while (l < r) {
		if (dis[l] + dis[r] <= k) {
			res += r - l;
			++l;
		}
		else --r;
	}
	return res;
}
int DFZ::dfs(int p)
{
	vis[p] = 1;
	ans += calc(p, 0);
	for (int e = head[p]; e; e = nex[e]) {
		if (vis[to[e]]) continue;
		ans -= calc(to[e], w[e]);
		int root, minsize = INT_MAX;
		dfs_getroot(p, 0, &root, &minsize);
		all_node = t[to[e]];
		minsize = INT_MAX;
		dfs_getroot(to[e], p, &root, &minsize);
		dfs(root);
	}
	return 0;
}
int DFZ::main(void)
{
	ans = 0;
	memset(vis, 0, sizeof vis);
	all_node = n;
	int root, minsize = INT_MAX;
	dfs_getroot(1, 0, &root, &minsize);
	dfs(root);
	return ans;
}
int main()
{
	while (~scanf("%d%d", &n, &k), n || k) {
		idx = 0;
		memset(head, 0, sizeof head);
		for (int i = 1; i < n; ++i) {
			int sti, edi, wi;
			scanf("%d%d%d", &sti, &edi, &wi);
			++sti, ++edi;
			Add_Edge(sti, edi, wi);
			Add_Edge(edi, sti, wi);
		}
		printf("%d\n", DFZ::main());
	}
	return 0;
}