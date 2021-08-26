#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10, M = 2e5 + 10;

int n;
LL ans[N], sum;
int maxc, cnt[N];
int color[N], son[N], sz[N];
int idx, head[N], nex[M], to[M];

void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx; to[idx] = v;
}
int dfs_son(int u, int fa)
{
	sz[u] = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa) continue;
		sz[u] += dfs_son(v, u);
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
	return sz[u];
}
void update(int u, int fa, int f, int son)
{
	int c = color[u];
	cnt[c] += f;
	if (cnt[c] > cnt[maxc] || c == maxc) maxc = c, sum = c;
	else if (cnt[c] == cnt[maxc] && c != maxc) sum += c;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || v == son) continue;
		update(v, u, f, son);
	}
}
void dfs(int u, int fa, int op)
{
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (v == fa || v == son[u]) continue;
		dfs(v, u, 0);
	}
	if (son[u]) dfs(son[u], u, 1);

	update(u, fa, 1, son[u]);
	ans[u] = sum;
	if (!op) {
		update(u, fa, -1, 0);
		maxc = sum = 0;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> color[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		AddEdge(u, v), AddEdge(v, u);
	}
	dfs_son(1, -1);
	dfs(1, -1, 1);
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << endl;
	return 0;
}