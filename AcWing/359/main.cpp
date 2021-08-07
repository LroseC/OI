#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10, M = N;

int n;
int idx, head[N], nex[M], to[M], rm[M];
LL ans;
bool vis[N], instk[N];
LL f1[N][2], f2[N][2];

void dfs_f(int u, int must, LL f[N][2])
{
	for (int e = head[u]; e; e = nex[e]) {
		if (rm[e]) continue;
		int v = to[e];
		dfs_f(v, must, f);
		f[u][0] += max(f[v][0], f[v][1]);
	}
	if (u == must) f[u][1] = f[u][0] + 1, f[u][0] = LONG_LONG_MIN;
	else {
		f[u][1] = LONG_LONG_MIN;
		for (int e = head[u]; e; e = nex[e]) {
			if (rm[e]) continue;
			int v = to[e];
			f[u][1] = max(f[u][1], f[u][0] - max(f[v][0], f[v][1]) + f[v][0] + 1);
		}
	}
}

void dfs_c(int u)
{
	vis[u] = instk[u] = 1;
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (!vis[v]) dfs_c(v);
		else if (instk[v]) {
			rm[e] = 1;
			dfs_f(v, -1, f1);
			dfs_f(v, u, f2);
			ans += max(f1[v][0], max(f1[v][1], f2[v][0]));
		}
	}
	instk[u] = 0;
}

void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx; to[idx] = v;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int u;
		scanf("%d", &u);
		AddEdge(u, i);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs_c(i);

	printf("%lld\n", ans);
	return 0;
}