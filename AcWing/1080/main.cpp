#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10;

int n;
int w[N];
int idx, head[N], nex[N], to[N], rm[N];
bool vis[N], instk[N];
LL ans, f1[N][2], f2[N][2];

void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
}

void dfs_s(int u, int ban, LL f[N][2])
{
	for (int e = head[u]; e; e = nex[e]) {
		if (rm[e]) continue;
		int v = to[e];
		dfs_s(v, ban, f);
		f[u][0] += max(f[v][0], f[v][1]);
	}
	if (u == ban) f[u][1] = INT_MIN;
	else {
		f[u][1] = w[u];
		for (int e = head[u]; e; e = nex[e]) {
			if (rm[e]) continue;
			int v = to[e];
			f[u][1] += f[v][0];
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
			dfs_s(v, -1, f1);
			dfs_s(v, u, f2);
			ans += max(f1[v][0], f2[v][1]);
		}
	}
	instk[u] = 0;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int u;
		scanf("%d%d", &w[i], &u);
		AddEdge(u, i);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs_c(i);

	printf("%lld\n", ans);
	return 0;
}