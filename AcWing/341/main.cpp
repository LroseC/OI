#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 2e6 + 10;

int n, m;
int price[N];
int ans = 0;
int idx, h1[N], h2[N], nex[M], to[M];
int dmin[N], dmax[N];
queue<int> q;
bool inque[N];

void AddEdge(int u, int v, int h[])
{
	nex[++idx] = h[u];
	h[u] = idx; to[idx] = v;
}
void spfa(int S, int flag, int d[], int head[])
{
	while (q.size()) q.pop();
	memset(inque, 0, sizeof inque);
	d[S] = price[S];
	q.push(S), inque[S] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		for (int e = head[u]; e; e = nex[e]) {
			int v = to[e];
			if (flag && max(price[v], d[u]) > d[v]) {
				d[v] = max(price[v], d[u]);
				if (!inque[v]) q.push(v), inque[v] = 1;
			}
			if (!flag && min(price[v], d[u]) < d[v]) {
				d[v] = min(price[v], d[u]);
				if (!inque[v]) q.push(v), inque[v] = 1;
			}
		}
	}
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", &price[i]);
	for (int i = 1; i <= m; ++i) {
		int u, v, op; scanf("%d%d%d", &u, &v, &op);
		AddEdge(u, v, h1);
		AddEdge(v, u, h2);
		if (op == 2) AddEdge(v, u, h1), AddEdge(u, v, h2);
	}
	memset(dmin, 0x3f, sizeof dmin);
	spfa(1, 0, dmin, h1);
	spfa(n, 1, dmax, h2);
	for (int i = 1; i <= n; ++i) {
		ans = max(ans, dmax[i] - dmin[i]);
	}
	printf("%d\n", ans);
	return 0;
}