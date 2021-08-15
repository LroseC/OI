#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

struct Edge
{
	int u, v, w;
	bool operator<(const Edge &b)
	{
		return w < b.w;
	}
};

int n;
Edge edge[N];
int fa[N], sz[N];
LL ans;

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = {u, v, w};
	}
	sort(edge + 1, edge + n);
	for (int i = 1; i < n; ++i) {
		int u = edge[i].u, v = edge[i].v;
		ans += 1ll * edge[i].w * sz[find(u)] * sz[find(v)];
		int x = find(u), y = find(v);
		fa[x] = y;
		sz[y] += sz[x];
	}
	printf("%lld\n", ans);
}