#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;
const int M = N << 1;

int n, idx, all_node;
int head[N], nex[M], to[M], w[M];
bool vis[N];
LL ans;

void AddEdge(int u, int v, int wi)
{
	nex[++idx] = head[u], to[idx] = v;
	head[u] = idx, w[idx] = wi;
}
int get_sz(int u, int fa)
{
	int res = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		res += get_sz(v, u);
	}
	return res;
}
int get_root(int u, int fa, int &root, int &minsize)
{
	int res = 1, max_son = 0;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || vis[v]) continue;
		int tmp = get_root(v, u, root, minsize);
		max_son = max(max_son, tmp);
		res += tmp;
	}
	max_son = max(max_son, all_node - res);
	if (max_son < minsize) {
		root = u;
		minsize = max_son;
	}
	return res;
}
void get_sum(int u, int v)
{
}

void dfs(int u)
{
	vis[u] = 1;
	nums.clear();
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		get_sum(v, u);
		get_dis(v, u);
	}
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		int root, minsize = INT_MAX;
		all_node = get_sz(v, u);
		get_root(v, u, root, minsize);
		dfs(root);
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	int root, minsize = INT_MAX;
	all_node = get_sz(1, -1);
	get_root(1, -1, root, minsize);
	dfs(root);
	printf("%lld\n", ans);
}